#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QVector3D>

class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);
    void setScalePercent(int percent);
    void setHeightPercent(int percent);
    void setDiameterPercent(int percent);
    void setApproximationPercent(int percent);
    void setPolyFillState(bool status);

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);
    void mousePressEvent(QMouseEvent* pe);
    void mouseMoveEvent(QMouseEvent* pe);
    void mouseReleaseEvent(QMouseEvent* pe);
    void wheelEvent(QWheelEvent *);


private:
    int xRotation, yRotation, zRotation;
    bool polyFillStatus;
    QPoint mousePos;
    qreal scale;
    qreal currentScale;
    int Approximation;
    qreal functionLen;
    qreal heightParam;
    qreal getFunctionValue(qreal x);
    QVector3D getVector(qreal pos_in, qreal angle);
    QVector3D getNormalZero(qreal pos_in);

    void drawAxis();
    void drawParaboloide();
};

#endif // GLWIDGET_H
