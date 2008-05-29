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

#include "simplefilteredimage.h"
#include <math.h>
#include <QPainter>

SimpleFilteredImage::SimpleFilteredImage(QDialog*)
{ }

SimpleFilteredImage::SimpleFilteredImage(QWidget *parent) : QLabel(parent)
{ }

void
SimpleFilteredImage::mouseReleaseEvent(QMouseEvent *event)
{
    QPoint p = event->pos();
    _z = (int) round(hypot(p.x() - _x0, p.y() - _y0));
    emit imageClicked();
}

void
SimpleFilteredImage::setSpectrum(QImage* s)
{
    spec = s;
    setPixmap(QPixmap::fromImage(*spec));
    _x0 = (int) round(spec->width() / 2.f);
    _y0 = (int) round(spec->height() / 2.f);
    setFixedHeight(spec->height());
    setFixedWidth(spec->width());
}

void
SimpleFilteredImage::setZ(int z)
{
    _z = z;
}

int SimpleFilteredImage::y0()
{
    return _y0;
}

int SimpleFilteredImage::x0()
{
    return _x0;
}

int SimpleFilteredImage::z()
{
    return _z;
}

void SimpleFilteredImage::paintEvent(QPaintEvent* ev)
{
    QLabel::paintEvent(ev);
    QPainter painter(this);
    int d = _z * 2;
    painter.setPen(Qt::red);
    painter.drawEllipse(_x0 - _z, _y0 - _z, d, d);
}

QImage* SimpleFilteredImage::spectrum()
{
    return spec;
}

