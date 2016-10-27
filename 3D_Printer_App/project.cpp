#include "project.h"

project::project(QWidget    *parent = 0)
    : QDialog(parent)
{
    this->setWindowModality(Qt::WindowModal);

    empty = true;

    nameProject = tr("untilted");
    pathFolderProject = QDesktopServices::storageLocation(QDesktopServices::DesktopLocation);

    nameLabel = new QLabel(tr("Name : "));
    locationFolderLabel = new QLabel(tr("Create in : "));
    locationStlLabel = new QLabel(tr("STL 3D file : "));

    nameLineEdit = new QLineEdit(tr("untilted"));
    locationFolderLineEdit = new QLineEdit(QDesktopServices::storageLocation(QDesktopServices::DesktopLocation));
    locationStlLineEdit = new QLineEdit();
    locationStlLineEdit->setReadOnly(true);

    locationFolderButton = new QPushButton(tr("Browse.."));
    locationStlButton = new QPushButton(tr("Browse.."));
    okButton = new QPushButton(tr("Ok"));
    cancelButton = new QPushButton(tr("Cancel"));

    gridLayout = new QGridLayout(this);
    gridLayout->addWidget(nameLabel, 0, 0, 1, 1);
    gridLayout->addWidget(locationFolderLabel, 1, 0, 1, 1);
    gridLayout->addWidget(locationStlLabel, 2, 0, 1, 1);
    gridLayout->addWidget(nameLineEdit, 0, 2, 1, 3);
    gridLayout->addWidget(locationFolderLineEdit, 1, 2, 1, 2);
    gridLayout->addWidget(locationStlLineEdit, 2, 2, 1, 2);
    gridLayout->addWidget(locationFolderButton, 1, 4, 1, 1);
    gridLayout->addWidget(locationStlButton, 2, 4, 1, 1);
    gridLayout->addWidget(okButton, 3, 3, 1, 1);
    gridLayout->addWidget(cancelButton, 3, 4, 1, 1);

    connect(nameLineEdit, SIGNAL(textEdited(QString)), this, SLOT(setNameProject(QString)));
    connect(locationFolderLineEdit, SIGNAL(textEdited(QString)), this, SLOT(setLocationFolderProject(QString)));

    connect(locationFolderButton, SIGNAL(clicked()), this, SLOT(selectLocationFolderProject()));
    connect(locationStlButton, SIGNAL(clicked()), this, SLOT(selectStlFile()));
    connect(okButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
}

float   project::mantisseToFloat(const QString &mantisse)
{
    float   result_number(0);
    QStringList split_mantisse(mantisse.split("e"));

    if (split_mantisse.size() == 2)
        result_number = split_mantisse.at(0).toFloat() * qPow(10, split_mantisse.at(1).toFloat());

    return (result_number);
}

QList<triangleStl>    project::STL_parsFile(const std::string &filePath)
{
    bool    testConvert;
    QStringList split_vertex;

    QList<triangleStl>  objectTriangles;
    triangleStl tmpTriangle;
    pointstl    tmpVertex;
    short   countCoord(0);
    short   countVertex(0);

    std::ifstream    STL_file(filePath.c_str(), std::ios_base::in);

    if (STL_file)
    {
        std::string line;

        while (std::getline(STL_file, line))
        {
            if (line.find("vertex") != std::string::npos)
            {
                QString Qline = QString::fromStdString(line);
                split_vertex = Qline.split(" ");
                for(int i = 0; i < split_vertex.size(); ++i)
                {
                    if (split_vertex.at(i).contains("e")  && (split_vertex.at(i).contains("+") || split_vertex.at(i).contains("-")))
                    {
                        countCoord++;
                        tmpVertex.setCoord(countCoord, mantisseToFloat(split_vertex.at(i)));
                    }
                    else if (split_vertex.at(i).toFloat(&testConvert) && testConvert)
                    {
                        countCoord++;
                        tmpVertex.setCoord(countCoord, split_vertex.at(i).toFloat());
                    }
                    else
                    {
                        if (split_vertex.at(i).contains("0") && split_vertex.at(i).size() ==  1)
                        {
                            countCoord++;
                            tmpVertex.setCoord(countCoord, 0.0f);
                        }
                    }
                }
                if (countCoord == 3)
                {
                    countCoord = 0;
                    countVertex++;
                    tmpTriangle.setVertex(countVertex, tmpVertex);
                    if (countVertex == 3)
                    {
                        countVertex = 0;
                        objectTriangles.append(tmpTriangle);
                    }
                }
            }
        }
        STL_file.close();
    }
    return (objectTriangles);
}

bool    project::isProjectEmpty() const
{
    return (empty);
}

void    project::setNameProject(QString name)
{
    nameProject.clear();
    nameProject = name;
}

void    project::setLocationFolderProject(QString location)
{
    pathFolderProject.clear();
    pathFolderProject = location;
}

void    project::selectLocationFolderProject()
{
    pathFolderProject = QFileDialog::getExistingDirectory(this, tr("Select a folder for the project"), QString());
    if (!pathFolderProject.isEmpty())
    {
        locationFolderLineEdit->clear();
        locationFolderLineEdit->setText(pathFolderProject);
    }
}

void    project::selectStlFile()
{
    pathSourceStl = QFileDialog::getOpenFileName(this, tr("Select a STL file"), QString(), tr("STL Files (*.stl)"));
    if (!pathSourceStl.isEmpty())
    {
        locationStlLineEdit->clear();
        locationStlLineEdit->setText(pathSourceStl);
    }
}

void    project::projectSave(const QList<layer> &objectLayers)
{
    QFile   slicesFile(this->getFullPathProject() + "/" + this->getNameProject() + ".slices");

    if (slicesFile.open(QIODevice::WriteOnly))
    {
        QTextStream out(&slicesFile);
        for (int i = 0; i < objectLayers.size(); ++i)
        {
            out << "Layer n: " << i << "\n\n";
            for (int y = 0; y < objectLayers.at(i).linesLayer.size(); ++y)
            {
                out << "Line n: " << y << "\n ";
                for (int k = 0; k < objectLayers.at(i).linesLayer.at(y).size(); ++k)
                {
                    out << "( " << objectLayers.at(i).linesLayer.at(y).at(k).m_lineDef.first.x << ", "
                        << objectLayers.at(i).linesLayer.at(y).at(k).m_lineDef.first.y << ", "
                        << objectLayers.at(i).linesLayer.at(y).at(k).m_lineDef.first.z << " ) ---> ( "
                        << objectLayers.at(i).linesLayer.at(y).at(k).m_lineDef.second.x << ", "
                        << objectLayers.at(i).linesLayer.at(y).at(k).m_lineDef.second.y << ", "
                        << objectLayers.at(i).linesLayer.at(y).at(k).m_lineDef.second.z << " )\n";
                }
            }
        }
        slicesFile.close();
    }
    else
        qDebug() << "failed open file";
}

QString project::getPathSourceStl() const
{
    return (pathSourceStl);
}

QString project::getPathFolderProject() const
{
    return (pathFolderProject);
}

QString project::getConcatFullPathProject() const
{
    return (pathFolderProject + "/" + nameProject);
}

QString project::getFullPathProject() const
{
    return (fullPathProject);
}

QString project::getNameProject() const
{
    return (nameProject);
}

void    project::setProjectEmpty(bool state)
{
    empty = state;
}

void    project::setFullPathProject(QString path)
{
    fullPathProject.clear();
    fullPathProject = path;
}

void    project::setPathProjectStl(QString path)
{
    pathProjectStl.clear();
    pathProjectStl = path;
}

QString project::getPathProjectStl() const
{
    return (pathProjectStl);
}

void    project::resetDisplay()
{
    nameLineEdit->clear();
    nameLineEdit->setText(tr("untilted"));
    locationFolderLineEdit->clear();
    locationFolderLineEdit->setText(QDesktopServices::storageLocation(QDesktopServices::DesktopLocation));
    locationStlLineEdit->clear();
}
