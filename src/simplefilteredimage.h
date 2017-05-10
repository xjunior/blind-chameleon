#ifndef SIMPLE_FILTERED_IMAGE_H
#define SIMPLE_FILTERED_IMAGE_H

#include <QLabel>
#include <QPoint>
#include <QMouseEvent>
#include <QPaintEvent>

class SimpleFilteredImage : public QLabel
{
    Q_OBJECT
    QImage *spec;
    int _x0, _y0, _z;
public:
    SimpleFilteredImage(QDialog* dlg);
    SimpleFilteredImage(QWidget* parent=nullptr);
    void setSpectrum(QImage*);
    QImage* spectrum();
    int y0();
    int x0();
    int z();
    void setZ(int);
    void paintEvent(QPaintEvent*);
protected:
    void mouseReleaseEvent(QMouseEvent*);
signals:
    void imageClicked();
};

#endif
