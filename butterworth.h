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

#ifndef BUTTERWORTH_H
#define BUTTERWORTH_H

#include "basicfilter.h"
#include "complex.h"
#include <QImage>

class Butterworth : public BasicFilter
{
    bool low;
public:
    Butterworth(bool);
    QImage* run(Complex*, int, SimpleFilteredImage*);
    char* desc();
    ~Butterworth();
protected:
    double H(int u, int v, int r, int x0, int y0, bool a, int n);
};

#endif
