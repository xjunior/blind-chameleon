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

#include "passaalta.h"
#include "fft.h"
#include <math.h>

QImage* PassaAlta::run(Complex* dft, int value, SimpleFilteredImage* img)
{
    int width = img->spectrum()->width();
    int height = img->spectrum()->height();
    int i, j, size = width * height;

    dft = Fourier::cp(dft, size);

    for (i = 0; i < width; i++)
        for (j = 0; j < height; j++)
            if (H(i, j, value, img->x0(), img->y0(), true))
                dft[(i * height) + j].set(0.0, 0.0);
    
    Complex* inv = Fourier::inverse(dft, size);
    QImage *im = Fourier::toImage(inv, width, height);
    delete[] dft;
    delete[] inv;
    
    return im;
}

PassaAlta::~PassaAlta()
{ }

