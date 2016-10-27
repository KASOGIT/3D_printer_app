#include "sceneobjects.h"

float MatSpec[4] = {1.0f, 1.0f, 1.0f, 1.0f};
float MatDif[4] = {0.8f, 0.8f, 0.8f, 1.0f};
float MatAmb[4] = {0.4f, 0.4f, 0.4f, 1.0f};
float Light1Pos[4] = {0.0f, 0.0f, -5.0f, 1.0f};
float Light1Dif[4] = {1.0f, 0.2f, 0.2f, 1.0f};
float Light1Spec[4] = {1.0f, 0.2f, 0.2f, 1.0f};
float Light1Amb[4] = {0.5f, 0.5f, 0.5f, 1.0f};
float Spot1Dir[3] = {0.0f, 0.0f, 1.0f};

SceneObjects::SceneObjects(QWidget *parent, int framePerSecond)
    : MyGLWidget_abstract(parent, framePerSecond)
{
    m_objectSlices = new slicer();
    xRot = 0;
    yRot = 0;
    zRot = 0;
    zoom = 0;
    m_objectTriangles.clear();
}

SceneObjects::~SceneObjects()
{
    delete m_objectSlices;
}

void    SceneObjects::enableLights()
{
    //gluLookAt(10,10,10,0,0,0,0,1,0);
    glLightfv(GL_LIGHT0, GL_POSITION, Light1Pos);
    glNormal3i(0,0,1);
}

void    SceneObjects::initializeGL()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    qglClearColor(Qt::gray);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_SMOOTH);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,MatSpec); 	//On applique les paramètres du matériau
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,MatDif);
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,MatAmb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, Light1Dif); 	//Et ceux de la lumière
    glLightfv(GL_LIGHT0, GL_SPECULAR, Light1Spec);
    glLightfv(GL_LIGHT0, GL_AMBIENT, Light1Amb);
    glLighti(GL_LIGHT0, GL_SPOT_CUTOFF, 40);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, Spot1Dir);
    glLightModelf(GL_LIGHT_MODEL_AMBIENT, 0.7);
    glEnable(GL_LIGHTING); 	//Et on allume la lumière
    glEnable(GL_LIGHT0);
}

void    SceneObjects::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -5.0f + zoom);
    glRotatef(xRot / 16.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot / 16.0f, 0.0f, 1.0f, 0.0f);
    glRotatef(zRot / 16.0f, 0.0f, 0.0f, 1.0f);
    enableLights();
    drawGrid(30);
    draw();
}

void    SceneObjects::setZoom(float value)
{
    zoom += value;
}

float   SceneObjects::getZoom() const
{
    return (zoom);
}

void    SceneObjects::drawGrid(float unit) const
{
    unit /= 2;
    glBegin(GL_LINES);
    for(int i = -unit; i <= unit; ++i)
    {
        glVertex3f(-unit, -0.1, i);
        glVertex3f(unit, -0.1, i);
        glVertex3f(i, -0.1, -unit);
        glVertex3f(i, -0.1, unit);
    }
    glEnd();
}

void    SceneObjects::draw()
{
    if (!m_objectTriangles.isEmpty())
    {
        glBegin(GL_TRIANGLES);
        for (int i = 0; i < m_objectTriangles.size(); ++i)
        {
            glVertex3f(m_objectTriangles.at(i).vertex1.x, m_objectTriangles.at(i).vertex1.y, m_objectTriangles.at(i).vertex1.z);
            glVertex3f(m_objectTriangles.at(i).vertex2.x, m_objectTriangles.at(i).vertex2.y, m_objectTriangles.at(i).vertex2.z);
            glVertex3f(m_objectTriangles.at(i).vertex3.x, m_objectTriangles.at(i).vertex3.y, m_objectTriangles.at(i).vertex3.z);
        }
        glEnd();
    }
}

void    SceneObjects::setObjectTriangles(const QList<triangleStl> &objectTriangles)
{
    if (!m_objectTriangles.isEmpty())
        m_objectTriangles.clear();
    m_objectTriangles = objectTriangles;
}

QList<triangleStl>  SceneObjects::getObjectTriangles() const
{
    return (m_objectTriangles);
}

void    SceneObjects::resetObjectTriangles()
{
    if (!m_objectTriangles.isEmpty())
        m_objectTriangles.clear();
}

void    SceneObjects::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
    lastButton = event->button();
}

void    SceneObjects::mouseMoveEvent(QMouseEvent *event)
{
    int dx(event->x() - lastPos.x()), dy(event->y() - lastPos.y());

    if (lastButton & Qt::LeftButton)
    {
        setXRotation(xRot + 8 * dy);
        setYRotation(yRot + 8 * dx);
    }
    else if (lastButton & Qt::RightButton)
    {
        setXRotation(xRot + 8 * dy);
        setZRotation(zRot + 8 * dx);
    }
    lastPos = event->pos();
}

void    SceneObjects::setXRotation(int angle)
{
    normalizeAngle(angle);
    if (angle != xRot)
    {
        xRot = angle;
        updateGL();
    }
}

void    SceneObjects::setYRotation(int angle)
{
    normalizeAngle(angle);
    if (angle != yRot)
    {
        yRot = angle;
        updateGL();
    }
}

void    SceneObjects::setZRotation(int angle)
{
    normalizeAngle(angle);
    if (angle != zRot)
    {
        zRot = angle;
        updateGL();
    }
}

int SceneObjects::getXRotation() const
{
    return (xRot);
}

int SceneObjects::getYRotation() const
{
    return (yRot);
}

int SceneObjects::getZRotation() const
{
    return (zRot);
}
