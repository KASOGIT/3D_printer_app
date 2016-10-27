#include "mainwindow.h"

MainWindow::MainWindow(QString const &titleApp, int widthApp, int heightApp)
    : guiProjectConfig(this)
{
    setWindowTitle(titleApp);
    configureGeometry(widthApp, heightApp);
    m_sceneObjects = new SceneObjects(this, 60);
    createIco();
    createActions();
    createMenuBar();
    createStatusBar();
    createToolBar();
    createDockTools();
    setCentralWidget(m_sceneObjects);
}

MainWindow::~MainWindow()
{
    guiProjectConfig.close();
    delete  m_sceneObjects;
}

void    MainWindow::configureGeometry(int widthApp, int heightApp)
{
    QDesktopWidget  *deskWidget;
    int widthScreen, heightScreen, x, y;

    deskWidget = QApplication::desktop();
    widthScreen = deskWidget->width();
    heightScreen = deskWidget->height();
    x = (widthScreen - widthApp) / 2;
    y = (heightScreen - heightApp) / 2;
    resize(widthApp, heightApp);
    move(x, y);
}

void    MainWindow::createStatusBar()
{
    SlicingProgressBar = new QProgressBar(this);
    SlicingProgressBar->setRange(0, 100);
    statusBar()->addPermanentWidget(SlicingProgressBar, 1);

    connect(this->m_sceneObjects->m_objectSlices, SIGNAL(valueChanged(int)), SlicingProgressBar, SLOT(setValue(int)));
    connect(this->m_sceneObjects->m_objectSlices, SIGNAL(statusBarShow()), statusBar(), SLOT(show()));
    connect(this->m_sceneObjects->m_objectSlices, SIGNAL(statusBarHide()), statusBar(), SLOT(hide()));

    statusBar()->hide();
}

void    MainWindow::createIco()
{
    QString pathIco("ICONS/");

    newIco = QIcon(QPixmap(pathIco + "new_project.png"));
    openIco = QIcon(QPixmap(pathIco + "open_project.png"));
    saveIco = QIcon(QPixmap(pathIco + "save_project.png"));
    undoIco = QIcon(QPixmap(pathIco + "undo.png"));
    redoIco = QIcon(QPixmap(pathIco + "redo.png"));
    selectIco = QIcon(QPixmap(pathIco + "select.png"));
    moveIco = QIcon(QPixmap(pathIco + "move.png"));
    rotateIco = QIcon(QPixmap(pathIco + "rotate.png"));
    resizeIco = QIcon(QPixmap(pathIco + "resize.png"));
    duplicateIco = QIcon(QPixmap(pathIco + "duplicate.png"));
    deleteIco = QIcon(QPixmap(pathIco + "delete.png"));
    zoomInIco = QIcon(QPixmap(pathIco + "zoomIn.png"));
    zoomOutIco = QIcon(QPixmap(pathIco + "zoomOut.png"));
    printIco = QIcon(QPixmap(pathIco + "print.png"));
}

void    MainWindow::createMenuBar()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addSeparator();
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAsAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(undoAct);
    editMenu->addAction(redoAct);

    graphMenu = menuBar()->addMenu(tr("&Graph"));
    graphMenu->addAction(selectAct);
    graphMenu->addSeparator();
    graphMenu->addAction(moveAct);
    graphMenu->addAction(rotateAct);
    graphMenu->addSeparator();
    graphMenu->addAction(resizeAct);
    graphMenu->addSeparator();
    graphMenu->addAction(duplicateAct);
    graphMenu->addAction(deleteAct);

    viewMenu = menuBar()->addMenu(tr("&View"));
    viewMenu->addAction(zoomInAct);
    viewMenu->addAction(zoomOutAct);
    viewMenu->addAction(originalSizeAct);
    viewMenu->addSeparator();
    viewMenu->addAction(hide_show_dockToolsAct);
    viewMenu->addAction(hide_show_dockConfigureAct);

    runMenu = menuBar()->addMenu(tr("&Run"));
    runMenu->addAction(printAct);

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(docAct);
    helpMenu->addAction(requestAct);
}

void    MainWindow::createToolBar()
{
    QSize   iconSize(35, 35);

    fileToolBar = addToolBar(tr("File"));
    fileToolBar->setIconSize(iconSize);
    fileToolBar->addAction(newAct);
    fileToolBar->addAction(saveAct);

    editToolBar = addToolBar(tr("Edit"));
    editToolBar->setIconSize(iconSize);
    editToolBar->addAction(undoAct);
    editToolBar->addAction(redoAct);

    viewToolBar = addToolBar(tr("View"));
    viewToolBar->setIconSize(iconSize);
    viewToolBar->addAction(zoomInAct);
    viewToolBar->addAction(zoomOutAct);

    runToolBar = addToolBar(tr("Run"));
    runToolBar->setIconSize(iconSize);
    runToolBar->addAction(printAct);
}

void    MainWindow::createDockTools()
{
    QSize   iconSize(50, 50);

    dockTools = new QDockWidget(tr("Graph actions"), this);
    dockTools->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    dockTools->setFeatures(QDockWidget::DockWidgetMovable);
    dockTools->setWindowTitle(tr(""));

    graphToolBar = addToolBar(tr("Graph"));
    graphToolBar->setIconSize(iconSize);
    graphToolBar->addAction(selectAct);
    graphToolBar->addSeparator();
    graphToolBar->addAction(moveAct);
    graphToolBar->addAction(rotateAct);
    graphToolBar->addSeparator();
    graphToolBar->addAction(resizeAct);
    graphToolBar->addSeparator();
    graphToolBar->addAction(duplicateAct);
    graphToolBar->addAction(deleteAct);

    graphToolBar->setParent(dockTools);
    graphToolBar->setOrientation(Qt::Vertical);
    dockTools->setWidget(graphToolBar);
    addDockWidget(Qt::LeftDockWidgetArea, dockTools);
}

void    MainWindow::createActions()
{
    newAct = new QAction(newIco, tr("&New project"), this);
    newAct->setShortcut(QKeySequence::New);
    newAct->setToolTip(tr("Create a new 3D print project"));
    connect(newAct, SIGNAL(triggered()), this, SLOT(newProject()));

    openAct = new QAction(openIco, tr("&Open project"), this);
    openAct->setShortcut(QKeySequence::Open);
    openAct->setToolTip(tr("Open a 3D print project"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(openProject()));

    saveAct = new QAction(saveIco, tr("&Save"), this);
    saveAct->setShortcut(QKeySequence::Save);
    saveAct->setToolTip(tr("Save your actual project"));
    connect(saveAct, SIGNAL(triggered()), this, SLOT(saveProject()));

    saveAsAct = new QAction(saveIco, tr("&Save As"), this);
    saveAsAct->setShortcut(QKeySequence::SaveAs);
    saveAsAct->setToolTip(tr("Save your actual project as a new location"));
    connect(saveAsAct, SIGNAL(triggered()), this, SLOT(saveAsProject()));

    exitAct = new QAction(deleteIco, tr("&Exit app"), this);
    exitAct->setShortcut(QKeySequence::Close);
    exitAct->setToolTip(tr("Exit the application"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(exitApp()));

    undoAct = new QAction(undoIco, tr("&Undo"), this);
    undoAct->setShortcut(QKeySequence::Undo);
    undoAct->setToolTip(tr("Undo this action"));
    connect(undoAct, SIGNAL(triggered()), this, SLOT(undo()));

    redoAct = new QAction(redoIco, tr("&Redo"), this);
    redoAct->setShortcut(QKeySequence::Redo);
    redoAct->setToolTip(tr("Redo this action"));
    connect(redoAct, SIGNAL(triggered()), this, SLOT(redo()));

    selectAct = new QAction(selectIco, tr("&Select"), this);
    selectAct->setToolTip(tr("Select an object for acting on it"));
    connect(selectAct, SIGNAL(triggered()), this, SLOT(selectObj()));

    moveAct = new QAction(moveIco, tr("&Move"), this);
    moveAct->setToolTip(tr("Move an object"));
    connect(moveAct, SIGNAL(triggered()), this, SLOT(moveObj()));

    rotateAct = new QAction(rotateIco, tr("&Rotate"), this);
    rotateAct->setToolTip(tr("Rotate an object"));
    connect(rotateAct, SIGNAL(triggered()), this, SLOT(rotateObj()));

    duplicateAct = new QAction(duplicateIco, tr("&Duplicate"), this);
    duplicateAct->setToolTip(tr("Duplicate an object"));
    connect(duplicateAct, SIGNAL(triggered()), this, SLOT(duplicateObj()));

    resizeAct = new QAction(resizeIco, tr("&Resize"), this);
    resizeAct->setToolTip(tr("Resize an object"));
    connect(resizeAct, SIGNAL(triggered()), this, SLOT(resizeObj()));

    deleteAct = new QAction(deleteIco, tr("&Delete"), this);
    deleteAct->setToolTip(tr("Delete an object"));
    connect(deleteAct, SIGNAL(triggered()), this, SLOT(deleteObj()));

    zoomInAct = new QAction(zoomInIco, tr("&Zoom in"), this);
    zoomInAct->setToolTip(tr("Zoom in on the 3D view"));
    zoomInAct->setShortcut(QKeySequence::ZoomIn);
    connect(zoomInAct, SIGNAL(triggered()), this, SLOT(zoomInView()));

    zoomOutAct = new QAction(zoomOutIco, tr("&Zoom out"), this);
    zoomOutAct->setToolTip(tr("Zoom out on the 3D veiw"));
    zoomOutAct->setShortcut(QKeySequence::ZoomOut);
    connect(zoomOutAct, SIGNAL(triggered()), this, SLOT(zoomOutView()));

    originalSizeAct = new QAction(tr("&Original size"), this);
    originalSizeAct->setToolTip(tr("Set object to the original size"));
    connect(originalSizeAct, SIGNAL(triggered()), this, SLOT(originalSizeView()));

    hide_show_dockToolsAct = new QAction(tr("&hide show dock tools"), this);
    hide_show_dockToolsAct->setToolTip(tr("Hide or show the dock tools"));
    connect(hide_show_dockToolsAct, SIGNAL(triggered()), this, SLOT(hide_show_dockTools()));

    hide_show_dockConfigureAct = new QAction(tr("&Hide show dock configure"), this);
    hide_show_dockConfigureAct->setToolTip(tr("Hide or show the dock configure"));
    connect(hide_show_dockConfigureAct, SIGNAL(triggered()), this, SLOT(hide_show_dockConfigure()));

    printAct = new QAction(printIco, tr("&Print (3D)"), this);
    printAct->setShortcut(QKeySequence::Print);
    printAct->setToolTip(tr("Launch 3D printing"));
    connect(printAct, SIGNAL(triggered()), this, SLOT(print()));

    aboutAct = new QAction(tr("&About"), this);
    aboutAct->setToolTip(tr("See more details about the application"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(aboutApp()));

    docAct = new QAction(tr("&Documentation"), this);
    docAct->setToolTip(tr("See the documentation"));
    connect(docAct, SIGNAL(triggered()), this, SLOT(docApp()));

    requestAct = new QAction(tr("&Request"), this);
    requestAct->setToolTip(tr("If you have any request to do"));
    connect(requestAct, SIGNAL(triggered()), this, SLOT(requestApp()));
}

void    MainWindow::cut_and_save()
{
    m_sceneObjects->m_objectSlices->createSlices(m_sceneObjects->getObjectTriangles());
    guiProjectConfig.projectSave(m_sceneObjects->m_objectSlices->objectLayers);
}

void    MainWindow::newProject()
{
    if (guiProjectConfig.isProjectEmpty() == false)
    {
        guiProjectConfig.resetDisplay();
    }
    if (guiProjectConfig.exec() == QDialog::Accepted)
    {
        if (guiProjectConfig.getNameProject().isEmpty() || guiProjectConfig.getPathSourceStl().isEmpty() || !QDir(guiProjectConfig.getPathFolderProject()).exists())
        {
            QMessageBox::warning(this, tr("Error : project create"), tr("Provides you bad information or forgot to provide"));
            this->newProject();
        }
        else
        {
            guiProjectConfig.setProjectEmpty(false);
            guiProjectConfig.setFullPathProject(guiProjectConfig.getConcatFullPathProject());
            QDir().mkpath(guiProjectConfig.getFullPathProject());
            guiProjectConfig.setPathProjectStl(guiProjectConfig.getFullPathProject() + "/" + guiProjectConfig.getNameProject() + ".stl");
            QFile::copy(guiProjectConfig.getPathSourceStl(), guiProjectConfig.getPathProjectStl());
            m_sceneObjects->setObjectTriangles(guiProjectConfig.STL_parsFile(guiProjectConfig.getPathProjectStl().toStdString()));
            QtConcurrent::run(this, &MainWindow::cut_and_save);
            m_sceneObjects->updateGL();
        }
    }
}

void    MainWindow::openProject()
{
}

void    MainWindow::saveProject()
{
    if (!guiProjectConfig.isProjectEmpty())
    {
        QtConcurrent::run(this, &MainWindow::cut_and_save);
    }
}

void    MainWindow::saveAsProject()
{

}

void    MainWindow::exitApp()
{
    close();
}

void    MainWindow::undo()
{

}

void    MainWindow::redo()
{

}

void    MainWindow::selectObj()
{

}

void    MainWindow::moveObj()
{
    if (guiProjectConfig.isProjectEmpty())
        return ;

    moveObject  objmove(this);

    if (objmove.exec() == QDialog::Accepted && objmove.isSet())
    {
        m_sceneObjects->setObjectTriangles(objmove.call_move(m_sceneObjects->getObjectTriangles()));
        m_sceneObjects->updateGL();
    }
}

void    MainWindow::rotateObj()
{
    if (guiProjectConfig.isProjectEmpty())
        return ;

    rotateObject    objrotate(this);

    if (objrotate.exec() == QDialog::Accepted && objrotate.isSet())
    {
        m_sceneObjects->setObjectTriangles(objrotate.call_rotate(m_sceneObjects->getObjectTriangles()));
        m_sceneObjects->updateGL();
    }
}

void    MainWindow::duplicateObj()
{

}

void    MainWindow::resizeObj()
{
    if (guiProjectConfig.isProjectEmpty())
        return ;

    resizeObject    objresize(this);

    if (objresize.exec() == QDialog::Accepted && objresize.isSet())
    {
        m_sceneObjects->setObjectTriangles(objresize.call_resize(m_sceneObjects->getObjectTriangles()));
        m_sceneObjects->updateGL();
    }
}

void    MainWindow::deleteObj()
{
    if (!m_sceneObjects->getObjectTriangles().isEmpty())
    {
        m_sceneObjects->resetObjectTriangles();
        m_sceneObjects->updateGL();
    }
}

void    MainWindow::zoomInView()
{
    m_sceneObjects->setZoom(0.3);
}

void    MainWindow::zoomOutView()
{
    m_sceneObjects->setZoom(-0.3);
}

void    MainWindow::originalSizeView()
{
    m_sceneObjects->setZoom(-m_sceneObjects->getZoom());
}

void    MainWindow::hide_show_dockTools()
{

}

void    MainWindow::hide_show_dockConfigure()
{

}

void    MainWindow::print()
{

}

void    MainWindow::aboutApp()
{

}

void    MainWindow::docApp()
{

}

void    MainWindow::requestApp()
{

}
