/*
 * This file is part of Blind Camaleon.
 *
 * Blind Camaleon is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Blind Camaleon is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Blind Camaleon.  If not, see <http://www.gnu.org/licenses/lgpl-3.0.txt>.
 */

#include "imagetabs.h"
#include "histogram.h"
#include "fft.h"
#include <math.h>
#include <QLabel>
#include <QColor>
#include <QScrollArea>

ImageTabs::ImageTabs(QWidget *parent, QString imageLocation) : QTabWidget(parent)
{
    original = new QImage(imageLocation);
    bool grayScale = original->isGrayscale();
    gray = (grayScale) ? original : NULL;
    dft = NULL;
    spectrum = NULL;

    addImage("Original" + QString((grayScale) ? " (Grayscale)" : ""), original);
}

QImage*
ImageTabs::getOriginal()
{
    return original;
}

QImage*
ImageTabs::getGray()
{
    generateGrayScale();
    return gray;
}

QImage*
ImageTabs::getSpectrum()
{
    if (dft == NULL)
        dft = Fourier::fromImage(getGray(), spectX, spectY);
    if (spectrum == NULL)
    {
        spectrum = new QImage(spectX, spectY, QImage::Format_RGB32);
        int bright;
        int pos;

        for (int i = 0; i < spectX; i++)
            for (int j = 0; j < spectY; j++)
            {
                pos = (i * spectY) + j;
                bright = (int) log(dft[pos].magnitude());
                spectrum->setPixel(i, j, qRgb(bright, bright, bright));
            }
    }

    return spectrum;
}

QImage
ImageTabs::getCurrent()
{
    QScrollArea *scroll = (QScrollArea*)currentWidget();
    return ((QLabel*)scroll->widget())->pixmap()->toImage();
}

void
ImageTabs::generateGrayScale()
{
    if (gray == NULL)
    {
        gray = new QImage(*original);
        QRgb grayPix;
        int bright;
    
        for (int i = 0; i < gray->width(); i++)
            for (int j = 0; j < gray->height(); j++)
            {
                QColor curPix = QColor::fromRgba(gray->pixel(i, j));
                bright = qRound(0.3 * curPix.red() + 0.5 * curPix.green() + 0.2 * curPix.blue());
                grayPix = qRgb(bright, bright, bright);
                gray->setPixel(i, j, grayPix);
            }
    
        addImage("Gray Scale", gray);
    }
}

void
ImageTabs::generateHistogram()
{
    generateGrayScale();

    int indexes[256];
    for (int i = 0; i < 256; i++)
        indexes[i] = 0;

    for (int i = 0; i < gray->width(); i++)
        for (int j = 0; j < gray->height(); j++)
        {
            QColor curPix = QColor::fromRgba(gray->pixel(i, j));
            indexes[curPix.red()]++;
        }

    QLabel *hView = new QLabel(this);
    hView->setPixmap(Histogram(indexes));

    QScrollArea *scroll = new QScrollArea;
    scroll->setWidget(hView);

    addTab(scroll, "Histogram");
    setCurrentWidget(scroll);
}

void
ImageTabs::addImage(QString label, QImage *img)
{
    QLabel *view = new QLabel(this);
    view->setPixmap(QPixmap::fromImage(*img));

    QScrollArea *scroll = new QScrollArea;
    scroll->setWidget(view);

    addTab(scroll, label);
    setCurrentWidget(scroll);
}

Complex*
ImageTabs::getDFT()
{
    return dft;
}

ImageTabs::~ImageTabs()
{
    if (dft != NULL)
        delete[] dft;

    if (gray != original)
        delete gray;
    delete original;

    if (spectrum != NULL)
        delete spectrum;
}

