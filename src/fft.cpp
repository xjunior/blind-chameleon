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

#include "fft.h"
#include <math.h>
#include <QColor>

Complex* Fourier::transform(Complex* x, int N)
{
    if (N == 1)
    {
	Complex* r = new Complex[1];
        r[0].set(x[0]);
        return r;
    }
    if (N % 2 != 0) { throw NotPowerOfTwo(); }

    Complex* even = new Complex[N / 2];
    for (int k = 0; k < N / 2; k++)
        even[k].set(x[2 * k]);
    Complex* q = transform(even, N / 2);

    Complex* odd = even;
    for (int k = 0; k < N / 2; k++)
        odd[k].set(x[2 * k + 1]);
    Complex* r = transform(odd, N / 2);

    Complex* y = new Complex[N];
    for (int k = 0; k < N / 2; k++)
    {
        double kth = -2 * k * M_PI / N;
        Complex wk(cos(kth), sin(kth));
        y[k] = q[k].plus(wk.times(r[k]));
        y[k + N / 2] = q[k].minus(wk.times(r[k]));
    }

    delete[] r;
    delete[] q;

    return y;
}

Complex* Fourier::inverse(Complex* x, int N)
{
    Complex* y = new Complex[N];
 
    // take conjugate
    for (int i = 0; i < N; i++)
        y[i] = x[i].conjugate();
 
    // compute forward FFT
    y = transform(y, N);
 
    // take conjugate again
    for (int i = 0; i < N; i++)
        y[i] = y[i].conjugate();
    
 
    // divide by N
    for (int i = 0; i < N; i++)
        y[i] = y[i].times(1.0 / N);
    
    return y;
}

Complex* Fourier::fromImage(QImage *img, int &x, int &y)
{
    int i, j, k = 0, size;
    // TODO: always increase the size to decrease after filters
    /*x = (int) pow(2, round(log10(img->width()) / log10(2)));
    y = (int) pow(2, round(log10(img->height()) / log10(2)));*/
    x = img->width(); y = img->height();
    size = x * y;

    Complex* result = new Complex[size];
    Complex* res;
    double pix;

    for (i = 0; i < x; i++)
        for (j = 0; j < y; j++)
        {
            pix = QColor::fromRgba(img->pixel(i, j)).red() * pow(-1, i + j);
            result[k].set(pix, 0.0);
            k++;
        }

    res = transform(result, size);
    delete[] result;

    return res;
}

QImage* Fourier::toImage(Complex* inv, int width, int height)
{
    QImage *im = new QImage(width, height, QImage::Format_RGB32);
    int i, j, bright;
    for (i = 0; i < width; i++)
        for (j = 0; j < height; j++)
        {
            bright = (int)round(abs((int)inv[(i * height) + j].re()));
            im->setPixel(i, j, qRgb(bright, bright, bright));
        }

    return im;
}

Complex* Fourier::cp(Complex* dft, int size)
{
    Complex* ndft = new Complex[size];

    for (int i = 0; i < size; i++)
        ndft[i].set(dft[i]);

    return ndft;
}

