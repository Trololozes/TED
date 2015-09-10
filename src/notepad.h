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
    bool fileSaveAs();
    void paste();
    void about();

private:
    QPlainTextEdit *textEdit;
    void createActions();
    void createMenus();

    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *formatMenu;
    QMenu *helpMenu;
    QActionGroup *alignmentGroup;
    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
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

    QString fileName;
};

#endif // NOTEPAD_H
