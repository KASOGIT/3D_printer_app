#include "moveobject.h"

moveObject::moveObject(QWidget *parent = 0)
    : QDialog(parent), m_value(0), axis(0)
{
    this->setWindowModality(Qt::WindowModal);

    explain = new QLabel(tr("Move an object on an axis between -/+ 10cm"));

    axesCombo = new QComboBox();
    axesCombo->addItem(" ");
    axesCombo->addItem("X");
    axesCombo->addItem("Y");
    axesCombo->addItem("Z");

    valueEdit = new QLineEdit();

    okButton = new QPushButton(tr("Ok"));
    cancelButton = new QPushButton(tr("Cancel"));

    gridLayout = new QGridLayout(this);
    gridLayout->addWidget(explain);
    gridLayout->addWidget(axesCombo);
    gridLayout->addWidget(valueEdit);
    gridLayout->addWidget(okButton);
    gridLayout->addWidget(cancelButton);

    connect(axesCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(setAxis(int)));
    connect(valueEdit, SIGNAL(textEdited(QString)), this, SLOT(setValue(QString)));
    connect(okButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
}

void    moveObject::setAxis(int index)
{
    axis = index;
}

void    moveObject::setValue(QString strValue)
{
    m_value = strValue.toFloat();
}

bool    moveObject::isSet() const
{
    if (axis > 0 && m_value <= 10)
        return (true);

    return (false);
}

QList<triangleStl>  moveObject::call_move(QList<triangleStl> m_objectTriangles)
{
    for (int i = 0; i < m_objectTriangles.size(); ++i)
    {
        m_objectTriangles[i].vertex1.setCoord(axis, m_objectTriangles.at(i).vertex1.getCoord(axis) + m_value);
        m_objectTriangles[i].vertex2.setCoord(axis, m_objectTriangles.at(i).vertex2.getCoord(axis) + m_value);
        m_objectTriangles[i].vertex3.setCoord(axis, m_objectTriangles.at(i).vertex3.getCoord(axis) + m_value);
    }

    return (m_objectTriangles);
}
