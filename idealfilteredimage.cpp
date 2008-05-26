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

#include "idealfilteredimage.h"
#include <math.h>
#include <QPainter>

IdealFilteredImage::IdealFilteredImage(QWidget *parent) : QLabel(parent)
{
    rubberBand = NULL;
    showGuideLines = true;
}

void IdealFilteredImage::mousePressEvent(QMouseEvent *event)
{
    selOrigin = event->pos();
    if (!rubberBand)
        rubberBand = new QRubberBand(QRubberBand::Rectangle, this);
    rubberBand->setGeometry(QRect(selOrigin, QSize()));
    rubberBand->show();
}

void IdealFilteredImage::mouseMoveEvent(QMouseEvent *event)
{
    rubberBand->setGeometry(QRect(selOrigin, event->pos()).normalized());
}

void IdealFilteredImage::mouseReleaseEvent(QMouseEvent *event)
{
    rubberBand->hide();
    selDest = event->pos();
    int deltaX = selOrigin.x() - selDest.x();
    int deltaY = selOrigin.y() - selDest.y();

    if (!(deltaX < 0 && deltaY < 0))
    {
        if (deltaX > 0 && deltaY > 0)
        {
            //      \<
            QPoint tmp = selDest;
            selDest = selOrigin;
            selOrigin = tmp;
        }
        else if (deltaX < 0 && deltaY > 0)
        {
            //      />
            int tmp = selOrigin.y();
            selOrigin.setY(selDest.y());
            selDest.setY(tmp);
        }
        else if (deltaX > 0 && deltaY < 0)
        {
            //      /<
            int tmp = selOrigin.x();
            selOrigin.setX(selDest.x());
            selDest.setX(tmp);
        }
    }

    _selections << QRect(selOrigin, selDest);

    // reflex
    int width  = abs(deltaX);
    int height = abs(deltaY);
    int rx = _x0 + _x0 - selOrigin.x() - width;
    int ry = _y0 + _y0 - selOrigin.y() - height;
    _selections << QRect(QPoint(rx, ry), QPoint(rx + width, ry + height));

    update();
    // determine selection, for example using QRect::intersects()
    // and QRect::contains().
}

void
IdealFilteredImage::setSpectrum(QImage* s)
{
    spec = s;
    setPixmap(QPixmap::fromImage(*spec));
    _x0 = (int) round(spec->width() / 2.f);
    _y0 = (int) round(spec->height() / 2.f);
    setFixedHeight(spec->height());
    setFixedWidth(spec->width());
}

int IdealFilteredImage::y0()
{
    return _y0;
}

int IdealFilteredImage::x0()
{
    return _x0;
}

void IdealFilteredImage::paintEvent(QPaintEvent* ev)
{
    QLabel::paintEvent(ev);
    QPainter painter(this);

    painter.setPen(Qt::black);
    painter.setBrush(Qt::black);

    for (int i = 0; i < _selections.size(); i++)
        painter.drawRect(_selections[i]);

    if (showGuideLines)
    {
        painter.setPen(Qt::red);
        painter.drawLine(0, _y0, spectrum()->width() - 1, _y0);
        painter.drawLine(_x0, 0, _x0, spectrum()->height() - 1);
    }
}

void IdealFilteredImage::setShowGuideLines(bool a)
{
    showGuideLines = a;
}

QImage* IdealFilteredImage::spectrum()
{
    return spec;
}

QList<QRect> IdealFilteredImage::selections()
{
    return _selections;
}

