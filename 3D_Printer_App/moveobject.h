#ifndef MOVEOBJECT_H
#define MOVEOBJECT_H

#include<QPushButton>
#include<QLabel>
#include<QComboBox>
#include<QLineEdit>
#include<QDialog>
#include<QGridLayout>
#include"trianglestl.h"

class moveObject : public QDialog
{
    Q_OBJECT

public:
    moveObject(QWidget *parent);
    QList<triangleStl>  call_move(QList<triangleStl> m_objectTriangles);
    bool    isSet() const;

private slots:
    void    setValue(QString strValue);
    void    setAxis(int index);

private:
    QGridLayout *gridLayout;

    QLabel      *explain;
    QComboBox   *axesCombo;
    QLineEdit   *valueEdit;

    QPushButton *okButton;
    QPushButton *cancelButton;

    float   m_value;
    int     axis;
};

#endif // MOVEOBJECT_H
