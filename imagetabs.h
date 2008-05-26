#ifndef IMAGETABS_H
#define IMAGETABS_H

#include <QTabWidget>
#include <QStatusBar>
#include <QImage>
#include "complex.h"

class ImageTabs : public QTabWidget
{
    Q_OBJECT

    QImage *original, *gray, *spectrum;
    int spectX, spectY;
    Complex* dft;

public:
    ImageTabs(QWidget *parent, QString imageLocation);
    QImage* getOriginal();
    QImage* getGray();
    QImage* getSpectrum();
    Complex* getDFT();
    QImage getCurrent();
    void generateGrayScale();
    void generateHistogram();
    void addImage(QString, QImage*);
    ~ImageTabs();
};

#endif
