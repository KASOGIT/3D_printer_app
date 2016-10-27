#include "rotateobject.h"

rotateObject::rotateObject(QWidget *parent = 0)
    : QDialog(parent), m_angle(0), m_axis(0)
{
    this->setWindowModality(Qt::WindowModal);

    explain = new QLabel(tr("Move an object on an axis between -/+ 360 degree"));

    axesCombo = new QComboBox();
    axesCombo->addItem(" ");
    axesCombo->addItem("X");
    axesCombo->addItem("Y");
    axesCombo->addItem("Z");

    angleSlid = new QSlider(Qt::Horizontal);
    angleSlid->setRange(-360, 360);
    angleSlid->setValue(0);

    okButton = new QPushButton(tr("Ok"));
    cancelButton = new QPushButton(tr("Cancel"));

    gridLayout = new QGridLayout(this);
    gridLayout->addWidget(explain);
    gridLayout->addWidget(axesCombo);
    gridLayout->addWidget(angleSlid);
    gridLayout->addWidget(okButton);
    gridLayout->addWidget(cancelButton);

    connect(okButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
    connect(axesCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(setAxis(int)));
    connect(angleSlid, SIGNAL(valueChanged(int)), this, SLOT(setAngle(int)));
}

QList<triangleStl>  rotateObject::call_rotate(QList<triangleStl> m_objectTriangles)
{
    for (int i = 0; i < m_objectTriangles.size(); ++i)
    {
        m_objectTriangles[i].vertex1.rotateOnAxis(m_axis, m_angle);
        m_objectTriangles[i].vertex2.rotateOnAxis(m_axis, m_angle);
        m_objectTriangles[i].vertex3.rotateOnAxis(m_axis, m_angle);
    }

    return (m_objectTriangles);
}

bool    rotateObject::isSet() const
{
    if (m_axis > 0 && m_angle != 0)
        return (true);

    return (false);
}

void    rotateObject::setAxis(int index)
{
    m_axis = index;
}

void    rotateObject::setAngle(int new_angle)
{
    m_angle = new_angle;
}
