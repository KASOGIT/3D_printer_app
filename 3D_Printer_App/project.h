#ifndef PROJECT_H
#define PROJECT_H

#include<QDesktopServices>
#include<QtGui>
#include<QString>
#include<QList>
#include<QDialog>
#include<fstream>
#include"slicer.h"
#include"layer.h"

class project : public QDialog
{
    Q_OBJECT

public:
    project(QWidget *parent);

    void    projectSave(const QList<layer> &objectLayers);
    bool    isProjectEmpty() const;
    void    setProjectEmpty(bool state);
    void    resetDisplay();

    QString getPathSourceStl() const;
    QString getPathProjectStl() const;
    QString getConcatFullPathProject() const;
    QString getFullPathProject() const;
    QString getPathFolderProject() const;
    QString getNameProject() const;

    void    setFullPathProject(QString  path);
    void    setPathProjectStl(QString path);

    QList<triangleStl>    STL_parsFile(const std::string &filePath);

private slots:
    void    setNameProject(QString name);
    void    setLocationFolderProject(QString location);
    void    selectLocationFolderProject();
    void    selectStlFile();

private:
    bool    empty;

    float   mantisseToFloat(const QString &mantisse);

    QString fullPathProject;
    QString pathFolderProject;
    QString nameProject;
    QString pathSourceStl;
    QString pathProjectStl;

    QGridLayout *gridLayout;

    QLabel  *nameLabel;
    QLabel  *locationFolderLabel;
    QLabel  *locationStlLabel;

    QLineEdit   *nameLineEdit;
    QLineEdit   *locationFolderLineEdit;
    QLineEdit   *locationStlLineEdit;

    QPushButton *locationFolderButton;
    QPushButton *locationStlButton;
    QPushButton *okButton;
    QPushButton *cancelButton;
};

#endif // PROJECT_H
