#include "resizeobject.h"

resizeObject::resizeObject(QWidget *parent = 0)
    : QDialog(parent), m_resize(0)
{
    this->setWindowModality(Qt::WindowModal);

    explain = new QLabel(tr("Resize an object between 0.3 to 3"));

    resizeSlid = new QSlider(Qt::Horizontal);
    resizeSlid->setRange(3, 30);
    resizeSlid->setValue(10);

    okButton = new QPushButton(tr("Ok"));
    cancelButton = new QPushButton(tr("Cancel"));

    gridLayout = new QGridLayout(this);
    gridLayout->addWidget(explain);
    gridLayout->addWidget(resizeSlid);
    gridLayout->addWidget(okButton);
    gridLayout->addWidget(cancelButton);

    connect(okButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
    connect(resizeSlid, SIGNAL(valueChanged(int)), this, SLOT(setResize(int)));
}

bool    resizeObject::isSet() const
{
    if (m_resize != 0)
        return (true);

    return (false);
}

void    resizeObject::setResize(int resize)
{
    m_resize = (float)(resize / 10);
}

QList<triangleStl>  resizeObject::call_resize(QList<triangleStl> m_objectTriangles)
{
    for (int i = 0; i < m_objectTriangles.size(); ++i)
    {
        m_objectTriangles[i].vertex1.resizeCoords(m_resize);
        m_objectTriangles[i].vertex2.resizeCoords(m_resize);
        m_objectTriangles[i].vertex3.resizeCoords(m_resize);
    }

    return (m_objectTriangles);
}
