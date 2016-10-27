#ifndef ROTATEOBJECT_H
#define ROTATEOBJECT_H

#include<QLabel>
#include<QGridLayout>
#include<QComboBox>
#include<QSlider>
#include<QPushButton>
#include<QDialog>
#include"trianglestl.h"

class rotateObject : public QDialog
{
    Q_OBJECT

public:
    rotateObject(QWidget *parent);
    QList<triangleStl>  call_rotate(QList<triangleStl> m_objectTriangles);
    bool    isSet() const;

private slots:
    void    setAngle(int new_angle);
    void    setAxis(int index);

private:
    QGridLayout *gridLayout;

    QLabel      *explain;
    QComboBox   *axesCombo;
    QSlider     *angleSlid;

    QPushButton *okButton;
    QPushButton *cancelButton;

    int     m_angle;
    int     m_axis;
};

#endif // ROTATEOBJECT_H
