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

#include "butterworth.h"
#include "fft.h"
#include <math.h>
#include <QInputDialog>

Butterworth::Butterworth(bool low)
{
    this->low = low; // low is true
}

char* Butterworth::desc()
{
    /*char *d;
    sprintf(d, "Butterworth (passa %s)", low ? "baixa" : "alta");*/
    return "Butterworth";
}

QImage* Butterworth::run(Complex* dft, int value, SimpleFilteredImage* img)
{
    int width = img->spectrum()->width();
    int height = img->spectrum()->height();
    int i, j, pos, size = width * height;
    double h;
    int n = QInputDialog::getInteger(img, "Butterworth filter", "n=");

    dft = Fourier::cp(dft, size);

    for (i = 0; i < width; i++)
        for (j = 0; j < height; j++)
        {
            h = H(i, j, value, img->x0(), img->y0(), low, n);
            pos = (i * height) + j;
            dft[pos].setIm(dft[pos].im() * h);
            dft[pos].setRe(dft[pos].re() * h);
        }
    
    Complex* inv = Fourier::inverse(dft, size);
    QImage *im = Fourier::toImage(inv, width, height);
    delete[] dft;
    delete[] inv;
    
    return im;
}

Butterworth::~Butterworth()
{ }

double Butterworth::H(int u, int v, int r, int x0, int y0, bool a, int n)
{
    double t = !a ? hypot(u - x0, v - y0) / r : r / hypot(u - x0, v - y0);
    double hypo = 1 / (1 + (sqrt(2) - 1) * pow(t, 2*n) );
    
    return hypo;
}

