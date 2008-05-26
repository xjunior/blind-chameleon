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

#ifndef BASICFILTER_H
#define BASICFILTER_H

#include <QImage>
#include "complex.h"
#include "simplefilteredimage.h"

class BasicFilter
{
public:
    virtual QImage* run(Complex*, int, SimpleFilteredImage*)=0;
    virtual char* desc()=0;
    virtual ~BasicFilter();
protected:
    bool H(int, int, int, int, int, bool);
};

#endif
