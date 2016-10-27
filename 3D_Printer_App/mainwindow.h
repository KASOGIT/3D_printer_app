#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<QtGui>
#include<QtCore>
#include"moveobject.h"
#include"rotateobject.h"
#include"resizeobject.h"
#include"sceneobjects.h"
#include"project.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QString const &titleApp, int widthApp = 500, int heightApp = 500);
    ~MainWindow();
    void    initializeGL();
    void    resizeGL(int w, int h);
    void    paintGL();

private slots:
    void    newProject();
    void    openProject();
    void    saveProject();
    void    saveAsProject();
    void    exitApp();

    void    undo();
    void    redo();

    void    selectObj();
    void    moveObj();
    void    rotateObj();
    void    duplicateObj();
    void    deleteObj();
    void    resizeObj();

    void    zoomInView();
    void    zoomOutView();
    void    originalSizeView();
    void    hide_show_dockConfigure();
    void    hide_show_dockTools();

    void    print();

    void    aboutApp();
    void    docApp();
    void    requestApp();

private:
    void    configureGeometry(int widthApp, int heightApp);
    void    createActions();
    void    createMenuBar();
    void    createToolBar();
    void    createStatusBar();
    void    createDockTools();
    void    createDockConfigure();
    void    createIco();

    void    cut_and_save();

    QProgressBar    *SlicingProgressBar;

    SceneObjects    *m_sceneObjects;

    project guiProjectConfig;

    QDockWidget *dockTools;
    QDockWidget *dockConfigure;

    QMenu   *fileMenu;
    QMenu   *editMenu;
    QMenu   *graphMenu;
    QMenu   *viewMenu;
    QMenu   *runMenu;
    QMenu   *helpMenu;

    QToolBar    *fileToolBar;
    QToolBar    *editToolBar;
    QToolBar    *graphToolBar;
    QToolBar    *viewToolBar;
    QToolBar    *runToolBar;

    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *saveAsAct;
    QAction *exitAct;

    QAction *undoAct;
    QAction *redoAct;

    QAction *selectAct;
    QAction *moveAct;
    QAction *rotateAct;
    QAction *duplicateAct;
    QAction *deleteAct;
    QAction *resizeAct;

    QAction *zoomInAct;
    QAction *zoomOutAct;
    QAction *originalSizeAct;
    QAction *hide_show_dockToolsAct;
    QAction *hide_show_dockConfigureAct;

    QAction *printAct;

    QAction *aboutAct;
    QAction *docAct;
    QAction *requestAct;

    QIcon   newIco;
    QIcon   openIco;
    QIcon   saveIco;
    QIcon   undoIco;
    QIcon   redoIco;
    QIcon   selectIco;
    QIcon   moveIco;
    QIcon   rotateIco;
    QIcon   duplicateIco;
    QIcon   deleteIco;
    QIcon   resizeIco;
    QIcon   zoomInIco;
    QIcon   zoomOutIco;
    QIcon   printIco;
};

#endif // MAINWINDOW_H
