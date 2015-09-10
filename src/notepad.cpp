
#include <QtWidgets>
#include <QMenuBar>
#include <QWidget>
#include <QLayout>

class QMenu;
#include "notepad.h"

TextEditor::TextEditor( QWidget *parent ) : QMainWindow( parent )
{


    QVBoxLayout *layout = new QVBoxLayout();

    textEdit = new QPlainTextEdit(this);
    setCentralWidget( textEdit );


    // QWidget *topFiller = new QWidget;
    // topFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    createActions();
    createMenus();

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

void TextEditor::newFile()
{
    infoLabel->setText(tr("Invoked <b>File|New</b>"));
}

void TextEditor::open()
{
    infoLabel->setText(tr("Invoked <b>File|Open</b>"));
}

bool TextEditor::save()
{
    infoLabel->setText(tr("Invoked <b>File|Save</b>"));
}

bool TextEditor::fileSaveAs()
{
   infoLabel->setText(tr("Invoked <b>File|Save As</b>"));
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
    infoLabel->setText(tr("Invoked <b>Help|About</b>"));
    QMessageBox::about(this, tr("About"),
            tr("TED Text Editor v0.0.1."));
}

void TextEditor::createActions()
{
    newAct = new QAction(tr("&New"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Create a new file"));
    connect(newAct, SIGNAL(triggered()), this, SLOT(newFile()));

    openAct = new QAction(tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an existing file"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

    saveAct = new QAction(tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save the document to disk"));
    connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit the application"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    undoAct = new QAction(tr("&Undo"), this);
    undoAct->setShortcuts(QKeySequence::Undo);
    undoAct->setStatusTip(tr("Undo the last operation"));
    connect(undoAct, SIGNAL(triggered()), this, SLOT(undo()));

    redoAct = new QAction(tr("&Redo"), this);
    redoAct->setShortcuts(QKeySequence::Redo);
    redoAct->setStatusTip(tr("Redo the last operation"));
    connect(redoAct, SIGNAL(triggered()), this, SLOT(redo()));

    cutAct = new QAction(tr("Cu&t"), this);
    cutAct->setShortcuts(QKeySequence::Cut);
    cutAct->setStatusTip(tr("Cut the current selection's contents to the "
                            "clipboard"));
    connect(cutAct, SIGNAL(triggered()), this, SLOT(cut()));

    copyAct = new QAction(tr("&Copy"), this);
    copyAct->setShortcuts(QKeySequence::Copy);
    copyAct->setStatusTip(tr("Copy the current selection's contents to the "
                             "clipboard"));
    connect(copyAct, SIGNAL(triggered()), this, SLOT(copy()));

    pasteAct = new QAction(tr("&Paste"), this);
    pasteAct->setShortcuts(QKeySequence::Paste);
    pasteAct->setStatusTip(tr("Paste the clipboard's contents into the current "
                              "selection"));
    connect(pasteAct, SIGNAL(triggered()), this, SLOT(paste()));

    aboutAct = new QAction(tr("&About"), this);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));
}

void TextEditor::createMenus()
{
    QMenu *menu;
    QAction *savesss;



    savesss = new QAction(tr("&Save As"), this);
    savesss->setShortcuts(QKeySequence::SaveAs);
    savesss->setStatusTip(tr("Save the document to disk"));
    connect(savesss, SIGNAL(triggered()), this, SLOT(save()));



   menu = menuBar()->addMenu( tr("&Test") );
   menu->addAction( savesss );
   menu->addSeparator();


    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(undoAct);
    editMenu->addAction(redoAct);
    editMenu->addSeparator();
    editMenu->addAction(cutAct);
    editMenu->addAction(copyAct);
    editMenu->addAction(pasteAct);
    editMenu->addSeparator();

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
}
