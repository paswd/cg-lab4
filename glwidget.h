#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QVector3D>

class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);
    void mousePressEvent(QMouseEvent* pe);
    void mouseMoveEvent(QMouseEvent* pe);
    void mouseReleaseEvent(QMouseEvent* pe);
    void wheelEvent(QWheelEvent *);


private:
    int xRotation, yRotation, zRotation, scale;
    QPoint mousePos;
    qreal currentScale;
    qreal Approximation;
    qreal functionLen;

    void drawAxis();
    void drawParaboloide();
};

#endif // GLWIDGET_H
