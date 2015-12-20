/*
 *  Copyright (C) 2015  Pierluigi Lazzari
 *  Copyright (C) 2015  Carlos Millett
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QtWidgets>
#include <QMenuBar>
#include <QWidget>
#include <QLayout>
#include <QShortcut>

#include "notepad.h"
#include "crypto.h"

class QMenu;

TextEditor::TextEditor( QWidget *parent ) : QMainWindow( parent )
{


    QVBoxLayout *layout = new QVBoxLayout();

    textEdit = new QPlainTextEdit(this);
    setCentralWidget( textEdit );


    // QWidget *topFiller = new QWidget;
    // topFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    createActions();
    createMenus();
    createStatusBar();

    readSettings();

    connect(textEdit->document(), SIGNAL(contentsChanged()),
            this, SLOT(documentWasModified()));

    setCurrentFile("");

    layout->setMargin(0);

}

void TextEditor::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    menu.addAction(cutAct);
    menu.addAction(copyAct);
    menu.addAction(pasteAct);
    menu.exec(event->globalPos());
}

void TextEditor::closeEvent(QCloseEvent *event)
{
    if (maybeSave()) {
        writeSettings();
        event->accept();
    } else {
        event->ignore();
    }
}

void TextEditor::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
}

void TextEditor::readSettings()
{
    QSettings settings("QtProject", "Application Example");
    QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
    QSize size = settings.value("size", QSize(400, 400)).toSize();
    resize(size);
    move(pos);
}

void TextEditor::writeSettings()
{
    QSettings settings("QtProject", "Application Example");
    settings.setValue("pos", pos());
    settings.setValue("size", size());
}

void TextEditor::newFile()
{
    if (maybeSave()) {
        textEdit->clear();
        setCurrentFile("");
    }
}

QString TextEditor::getPassw()
{
    bool ok;
    QString passw = QInputDialog::getText(
        this,
        tr("Password"),
        tr("Digite a senha:\n"
           "Para não usar criptografia, deixe em branco."),
        QLineEdit::Password,
        QString(),
        &ok
    );

    return passw;
}

void TextEditor::open()
{
    if (maybeSave()) {
        QString fileName = QFileDialog::getOpenFileName(
                            this,
                            tr("Open File"),
                            QString(),
                            "TED File (*.ted);;Text File (*.txt);;All Files (*.*)",
                            0,
                            0
                           );
        if (!fileName.isEmpty()) {
            QString passw = getPassw();

            if( passw.isEmpty() )
                loadFile(fileName);
            else
                loadFile(fileName, passw);
        }
    }
}

bool TextEditor::save()
{
    if (curFile.isEmpty()) {
        return saveAs();
    } else {
        QString passw = getPassw();

        if( passw.isEmpty() )
            return saveFile(curFile);

        return saveFile(curFile, passw);
    }
}

bool TextEditor::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(
                        this,
                        tr("Save File"),
                        QString(),
                        "TED File (*.ted);;Text File (*.txt);;All Files (*.*)",
                        0,
                        0
                       );
    if( fileName.isEmpty() )
        return false;

    QFileInfo file(fileName);
    if( file.suffix().isEmpty() )
        fileName += ".ted";

    QString passw = getPassw();
    if( passw.isEmpty() )
        return saveFile(fileName);

    return saveFile(fileName, passw);
}

void TextEditor::undo()
{
    infoLabel->setText(tr("Invoked <b>Edit|Undo</b>"));
}

void TextEditor::redo()
{
    infoLabel->setText(tr("Invoked <b>Edit|Redo</b>"));
}

void TextEditor::cut()
{
    infoLabel->setText(tr("Invoked <b>Edit|Cut</b>"));
}

void TextEditor::copy()
{
    infoLabel->setText(tr("Invoked <b>Edit|Copy</b>"));
}

void TextEditor::paste()
{
    infoLabel->setText(tr("Invoked <b>Edit|Paste</b>"));
}

void TextEditor::about()
{
    QMessageBox about(this);

    about.setWindowTitle(tr("About"));
    about.setText(tr("TEDitor"));
    about.setInformativeText(tr("Editor de texto com segurança criptográfica\n"
                                "\n"));
    about.setDetailedText(tr("Créditos:\n"
                             "Carlos Millett,\n"
                             "Miguel Nunes,\n"
                             "Pierluigi Lazzari."));

    about.exec();
}

bool TextEditor::maybeSave()
{
    if (textEdit->document()->isModified()) {
        QMessageBox::StandardButton ret;
        ret = QMessageBox::warning(this, tr("TEDitor"),
                     tr("O documento foi modificado.\n"
                        "Deseja salvar suas alterações?"),
                     QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        if (ret == QMessageBox::Save)
            return save();
        else if (ret == QMessageBox::Cancel)
            return false;
    }
    return true;
}

void TextEditor::setCurrentFile(const QString &fileName)
{
    curFile = fileName;
    textEdit->document()->setModified(false);
    setWindowModified(false);

    QString shownName = curFile;
    if (curFile.isEmpty())
        shownName = "untitled.txt";
    setWindowFilePath(shownName);
}

void TextEditor::loadFile(const QString &fileName)
{
    QFile file(fileName);

    if ( ! file.open(QFile::ReadOnly | QFile::Text) ) {
        QMessageBox::warning(this, tr("TEDitor"),
                             tr("O TED encontrou problemas para ler o arquivo %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return;
    }

    QTextStream in(&file);

#ifndef QT_NO_CURSOR
    QApplication::setOverrideCursor(Qt::WaitCursor);
#endif

    textEdit->setPlainText(in.readAll());

#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif

    setCurrentFile(fileName);
}

void TextEditor::loadFile(const QString &fileName, const QString &passw)
{
    char *buffer;
    crypto::AES crypt;

    crypt.setKey(passw.toStdString().c_str());
    if( ! ( crypt.readFile(fileName.toStdString().c_str()) && crypt.decrypt() ) )
    {
        QMessageBox::warning(this, tr("TEDitor"),
                             tr("O TED encontrou problemas para ler o arquivo %1:\n.")
                             .arg(fileName));
        return;
    }

    buffer = crypt.getBuffer();

    textEdit->setPlainText(QString(buffer));
    setCurrentFile(fileName);
}

bool TextEditor::saveFile(const QString &fileName)
{
    QFile file(fileName);

    if ( ! file.open(QFile::WriteOnly | QFile::Text) ) {
        QMessageBox::warning(this, tr("TEDitor"),
                             tr("O TED encontrou problemas para salvar o arquivo %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return false;
    }

    QTextStream out(&file);

#ifndef QT_NO_CURSOR
    QApplication::setOverrideCursor(Qt::WaitCursor);
#endif

    out << textEdit->toPlainText();

#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif

    setCurrentFile(fileName);

    return true;
}

bool TextEditor::saveFile(const QString &fileName, const QString &passw)
{
    QString buffer;
    crypto::AES crypt;

    crypt.setKey(passw.toStdString().c_str());
    buffer = textEdit->toPlainText();
    crypt.setBuffer(buffer.toStdString().c_str(), buffer.toStdString().size());
    if( ! ( crypt.encrypt() && crypt.saveFile(fileName.toStdString().c_str()) ) )
    {
        QMessageBox::warning(this, tr("TEDitor"),
                             tr("O TED encontrou problemas para salvar o arquivo %1:\n.")
                             .arg(fileName));
        return false;
    }

    setCurrentFile(fileName);
    return true;
}

void TextEditor::documentWasModified()
{
    setWindowModified(textEdit->document()->isModified());
}


void TextEditor::createActions()
{
    //QKeySequence SaveAs não funciona no windows, criando manualmente
    QShortcut *shortcutSaveAs = new QShortcut(QKeySequence(tr("Ctrl+Shift+S")), textEdit);

    newAct = new QAction(tr("&Novo"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Cria um novo arquivo"));
    connect(newAct, SIGNAL(triggered()), this, SLOT(newFile()));

    openAct = new QAction(tr("&Abrir..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Abre um arquivo existente"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));


    saveAct = new QAction(tr("&Salvar"), this);
    saveAct->setShortcuts(QKeySequence::Save); // why no work?!
    saveAct->setStatusTip(tr("Salva o documento para o disco"));
    connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

    saveAsAct = new QAction(tr("&Salvar como"), this);
    saveAsAct->setShortcuts(QKeySequence::SaveAs);
    saveAsAct->setStatusTip(tr("Salva o documento para o disco"));
    connect(saveAsAct, SIGNAL(triggered()), this, SLOT(saveAs()));
    //Linkando o atalho
    connect(shortcutSaveAs, SIGNAL(activated()), this, SLOT(saveAs()));

    exitAct = new QAction(tr("&Sair"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Sair do programa"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    undoAct = new QAction(tr("&Desfazer"), this);
    undoAct->setShortcuts(QKeySequence::Undo);
    undoAct->setStatusTip(tr("Desfazer a última operação"));
    connect(undoAct, SIGNAL(triggered()), this, SLOT(undo()));

    redoAct = new QAction(tr("&Refazer"), this);
    redoAct->setShortcuts(QKeySequence::Redo);
    redoAct->setStatusTip(tr("Refazer a última operação"));
    connect(redoAct, SIGNAL(triggered()), this, SLOT(redo()));

    cutAct = new QAction(tr("&Cortar"), this);
    cutAct->setShortcuts(QKeySequence::Cut);
    cutAct->setStatusTip(tr("Cortar seleção"));
    connect(cutAct, SIGNAL(triggered()), this, SLOT(cut()));
    cutAct->setEnabled(false);
    connect(textEdit, SIGNAL(copyAvailable(bool)),
            cutAct, SLOT(setEnabled(bool)));


    copyAct = new QAction(tr("&Copiar"), this);
    copyAct->setShortcuts(QKeySequence::Copy);
    copyAct->setStatusTip(tr("Copiar seleção"));
    connect(copyAct, SIGNAL(triggered()), this, SLOT(copy()));
    copyAct->setEnabled(false);
    connect(textEdit, SIGNAL(copyAvailable(bool)),
            copyAct, SLOT(setEnabled(bool)));

    pasteAct = new QAction(tr("&Colar"), this);
    pasteAct->setShortcuts(QKeySequence::Paste);
    pasteAct->setStatusTip(tr("Colar a seleção"));
    connect(pasteAct, SIGNAL(triggered()), this, SLOT(paste()));

    aboutAct = new QAction(tr("&Sobre"), this);
    aboutAct->setStatusTip(tr("Sobre a aplicação"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));


}

void TextEditor::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&Arquivo"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAsAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    editMenu = menuBar()->addMenu(tr("&Editar"));
    editMenu->addAction(undoAct);
    editMenu->addAction(redoAct);
    editMenu->addSeparator();
    editMenu->addAction(cutAct);
    editMenu->addAction(copyAct);
    editMenu->addAction(pasteAct);
    editMenu->addSeparator();

    helpMenu = menuBar()->addMenu(tr("&Ajuda"));
    helpMenu->addAction(aboutAct);
}
