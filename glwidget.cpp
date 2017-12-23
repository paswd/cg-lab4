#include "glwidget.h"
#include <QtCore/qmath.h>
#include <QVector3D>
#include <QDebug>
#include <qmath.h>
#include <QMouseEvent>

const double LARGE_SIDE = 1.6;
const qreal GL_PI = 3.1415926;

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent)
{
    resize(300,300);
    xRotation = 0;
    yRotation = 0;
    zRotation = 0;
    scale = 2;
    Approximation = 30.;
    functionLen = 4;
}

void GLWidget::initializeGL() {
    qglClearColor(Qt::white);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_FLAT);
    glEnable(GL_CULL_FACE);
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    //fillCoordinateMatrix();
}

void GLWidget::paintGL() {
    //drawPiramide();
    drawParaboloide();
}

void GLWidget::resizeGL(int w, int h) {
    glViewport(0, 0, h, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
}

void GLWidget::mousePressEvent(QMouseEvent* pe)
{
    mousePos = pe->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent* pe)
{
    xRotation += (pe->y() - mousePos.y()) * 1.1 * GL_PI / 180;
    zRotation += (pe->x() - mousePos.x()) * 1.1 * GL_PI / 180;

    updateGL();
}

void GLWidget::mouseReleaseEvent(QMouseEvent *pe)
{
}

void GLWidget::drawAxis()
{
    glLineWidth(3.0f);

    glColor4f(1.00f, 0.00f, 0.00f, 1.0f);
    glBegin(GL_LINES);
        glVertex3f( 1.0f,  0.0f,  0.0f);
        glVertex3f(-1.0f,  0.0f,  0.0f);
    glEnd();

    QColor halfGreen(0, 128, 0, 255);
    qglColor(halfGreen);
    glBegin(GL_LINES);
        glVertex3f( 0.0f,  1.0f,  0.0f);
        glVertex3f( 0.0f, -1.0f,  0.0f);

        glColor4f(0.00f, 0.00f, 1.00f, 1.0f);
        glVertex3f( 0.0f,  0.0f,  1.0f);
        glVertex3f( 0.0f,  0.0f, -1.0f);
    glEnd();
}

void GLWidget::wheelEvent(QWheelEvent* pe)
{
    if ((pe->delta()) > 0) {
        scale *= 1.1;
    } else if ((pe->delta())<0) {
        scale /= 1.1;
    }
    updateGL();
}

/*void Widget::drawPiramide() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glScalef(scale, scale, scale);
    glRotatef(xRotation, 1.0f, 0.0f, 0.0f);
    glRotatef(yRotation, 0.0f, 1.0f, 0.0f);
    glRotatef(zRotation, 0.0f, 0.0f, 1.0f);

    //drawAxis();

    QColor clr(0, 64, 128, 255);
    //QColor clr_lines(0, 0, 0, 255);
    qglColor(clr);

    currentScale = .3;

    for (size_t i = 0; i < SIDES_NUM; i++) {
        if (!isVisibleSide(i)) {
            continue;
        }
        glBegin(GL_LINE_LOOP);
        //glBegin(GL_POLYGON);
            for (size_t j = 0; j < VERTEX_NUM; j++) {
                glVertex3f(currentScale * Coordinates[i][j][0], currentScale * Coordinates[i][j][1],
                        currentScale * Coordinates[i][j][2]);
                //qDebug() << "[" << i << ", " << j << "]\n";
                //qDebug() << "{" << Coordinates[i][j][0] << ", " << Coordinates[i][j][1] << ", " << Coordinates[i][j][2] << "}\n";
            }
        glEnd();
    }
}*/

qreal getFunctionValue(qreal x) {
    return 10 * x * x;
}

QVector3D getVector(qreal pos_in, qreal angle) {
    qreal pos = pos_in * .1;

    QVector3D res(pos * qCos(angle), pos * qSin(angle), getFunctionValue(pos));

    return res;
}
QVector3D getNormalZero(qreal pos_in) {
    qreal pos = pos_in * .1;
    QVector3D res(0., 0., getFunctionValue(pos));

    return res;
}

void GLWidget::drawParaboloide() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glScalef(scale, scale, scale);
    glRotatef(xRotation, 1.0f, 0.0f, 0.0f);
    glRotatef(yRotation, 0.0f, 1.0f, 0.0f);
    glRotatef(zRotation, 0.0f, 0.0f, 1.0f);
    float ambient[4] = {0.5, 0.5, 0.5, 1};

    QColor clr(0, 64, 128, 255);
    //QColor clr_lines(0, 0, 0, 255);
    qglColor(clr);

    /*glBegin(GL_LINE_LOOP);
    glVertex3f(0., 0., 0.);
    glVertex3f(.1, .1, .1);
    glEnd();*/

    currentScale = .3;
    qreal stepRotate = 2 * GL_PI / Approximation;
    qreal stepFunction = functionLen / Approximation;
    qreal halfLen = functionLen / 2;

    for (qreal current = 0.; current < 2. * GL_PI; current += stepRotate) {
        qreal i;
        for (i = 0.; i < halfLen; i += stepFunction) {
            glBegin(GL_LINE_LOOP);
            //glBegin(GL_POLYGON);
            qDebug() << current << " " << i;
            QVector3D currentPoly[4];
            currentPoly[3] = getVector(i, current);
            currentPoly[2] = getVector(i + stepFunction, current);
            currentPoly[1] = getVector(i + stepFunction, current + stepRotate);
            currentPoly[0] = getVector(i, current + stepRotate);
            glVertex3f(currentPoly[0].x(), currentPoly[0].y(), currentPoly[0].z());
            glVertex3f(currentPoly[1].x(), currentPoly[1].y(), currentPoly[1].z());
            glVertex3f(currentPoly[2].x(), currentPoly[2].y(), currentPoly[2].z());
            glVertex3f(currentPoly[3].x(), currentPoly[3].y(), currentPoly[3].z());
            glEnd();
        }
        QVector3D topPoly[3];
        topPoly[0] = getNormalZero(i);
        topPoly[1] = getVector(i, current);
        topPoly[2] = getVector(i, current + stepRotate);
        glBegin(GL_LINE_LOOP);
        //glBegin(GL_POLYGON);
        glVertex3f(topPoly[0].x(), topPoly[0].y(), topPoly[0].z());
        glVertex3f(topPoly[1].x(), topPoly[1].y(), topPoly[1].z());
        glVertex3f(topPoly[2].x(), topPoly[2].y(), topPoly[2].z());
        qDebug() << topPoly[0].x() << " " << topPoly[0].y() << " " << topPoly[0].z();
        qDebug() << topPoly[1].x() << " " << topPoly[1].y() << " " << topPoly[1].z();
        qDebug() << topPoly[2].x() << " " << topPoly[2].y() << " " << topPoly[2].z();
        glEnd();
    }
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);

}
