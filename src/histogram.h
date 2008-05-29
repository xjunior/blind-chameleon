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

#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include <QWidget>
#include <QPaintEvent>
#define _HISTOGRAM_CLASSES 32
#define BAR_WIDTH 15
#define BAR_SPACE 3
#define ZERO_POINT 400
#define TOP_SPACE 20
#define SIDE_SPACE 40
#define HISTOGRAM_WIDTH (SIDE_SPACE + ((BAR_WIDTH + BAR_SPACE) * _HISTOGRAM_CLASSES))
#define HISTOGRAM_HEIGHT (HISTOGRAM_WIDTH, ZERO_POINT + TOP_SPACE + 20)

class Histogram : public QPixmap
{
    int indexes[_HISTOGRAM_CLASSES];
    int perClass;
public:
    Histogram(int[255]);
    void generate();
private:
    void paintGraphBase(QPainter*, int);
    void paintBar(QPainter*, int, int);
};

#endif
