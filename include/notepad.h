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

#ifndef NOTEPAD_H
#define NOTEPAD_H

#include <QtWidgets>
#include <QtGui>

class QAction;
class QActionGroup;
class QLabel;
class QMenu;

class TextEditor : public QMainWindow
{
    Q_OBJECT

protected:
    void contextMenuEvent(QContextMenuEvent *event) Q_DECL_OVERRIDE;
    void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;

public:
    TextEditor(QWidget *parent = 0);

private slots:
    void newFile();
    void open();
    void undo();
    void redo();
    void cut();
    void copy();
    bool save();
    bool saveAs();
    void paste();
    void about();
    void documentWasModified();


private:
    QPlainTextEdit *textEdit;

    QString curFile;
    QString fileName;

    void createStatusBar();
    void createActions();
    void createMenus();
    QString getPassw();
    bool maybeSave();
    void setCurrentFile(const QString &fileName);
    void loadFile(const QString &fileName);
    void loadFile(const QString &fileName, const QString &passw);
    bool saveFile(const QString &fileName);
    bool saveFile(const QString &fileName, const QString &passw);
    void readSettings();
    void writeSettings();

    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *formatMenu;
    QMenu *helpMenu;
    QActionGroup *alignmentGroup;
    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *saveAsAct;
    QAction *printAct;
    QAction *exitAct;
    QAction *undoAct;
    QAction *redoAct;
    QAction *cutAct;
    QAction *copyAct;
    QAction *pasteAct;
    QAction *boldAct;
    QAction *italicAct;
    QAction *leftAlignAct;
    QAction *rightAlignAct;
    QAction *justifyAct;
    QAction *centerAct;
    QAction *setLineSpacingAct;
    QAction *setParagraphSpacingAct;
    QAction *aboutAct;
    QAction *aboutQtAct;
    QLabel *infoLabel;

};

#endif // NOTEPAD_H
