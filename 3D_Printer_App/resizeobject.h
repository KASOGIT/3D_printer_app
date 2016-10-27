#ifndef RESIZEOBJECT_H
#define RESIZEOBJECT_H

#include<QGridLayout>
#include<QLabel>
#include<QSlider>
#include<QPushButton>
#include<QDialog>
#include"trianglestl.h"

class resizeObject : public QDialog
{
    Q_OBJECT

public:
    resizeObject(QWidget *parent);
    bool    isSet() const;
    QList<triangleStl>  call_resize(QList<triangleStl>  m_objectTriangles);

private slots:
    void    setResize(int resize);

private:
    QGridLayout *gridLayout;

    QLabel      *explain;
    QSlider     *resizeSlid;

    QPushButton *okButton;
    QPushButton *cancelButton;

    float   m_resize;
};

#endif // RESIZEOBJECT_H
