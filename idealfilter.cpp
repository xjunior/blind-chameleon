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

#include "idealfilter.h"
#include "complex.h"
#include "fft.h"
#include <math.h>
#include <QPainter>

IdealFilter::IdealFilter(PidMain *parent, ImageTabs* imgs) : QDialog(parent),
images(imgs)
{
    setupUi(this);
    scrollArea->setWidget(imageLabel);
    imageLabel->setSpectrum(image());

    connect(applyButton, SIGNAL( clicked() ), this, SLOT( applyFilter() ));
    connect(showGuideLines, SIGNAL( toggled(bool) ), this, SLOT( toggleShowGuideLines(bool) ));
}

void IdealFilter::applyFilter()
{
    int width = image()->width();
    int height = image()->height();
    int i, j, k, size = width * height;

    Complex* dft = Fourier::cp(images->getDFT(), size);

    for (i = 0; i < width; i++)
        for (j = 0; j < height; j++)
            for (k = 0; k < imageLabel->selections().size(); k++)
                if (imageLabel->selections().at(k).contains(i, j))
                {
                    dft[(i * height) + j].set(0.0, 0.0);
                    break;
                }
    
    Complex* inv = Fourier::inverse(dft, size);
    QImage *im = Fourier::toImage(inv, width, height);
    delete[] dft;
    delete[] inv;

    images->addImage("Special Filter", im);
    close();
}

QImage* IdealFilter::image()
{
    return images->getSpectrum();
}

void IdealFilter::toggleShowGuideLines(bool a)
{
    imageLabel->setShowGuideLines(a);
    imageLabel->update();
}

