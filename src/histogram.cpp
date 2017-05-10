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

#include <QPainter>
#include <QColor>
#include <QBrush>
#include "histogram.h"

Histogram::Histogram(int idx[256]) : QPixmap(HISTOGRAM_WIDTH, HISTOGRAM_HEIGHT)
{
    perClass = 256 / _HISTOGRAM_CLASSES;

    for (int i = 0; i < _HISTOGRAM_CLASSES; i++)
    {
        int val = 0;
        for (int j = i * perClass; j < (i+1) * perClass - 1; j++)
            val = val + idx[j];
        indexes[i] = val;
    }

    generate();
}

void Histogram::generate()
{
    fill();
    QPainter painter(this);
    int max = indexes[0];
    for (int i = 0; i < _HISTOGRAM_CLASSES; i++)
        if (indexes[i] > max)
            max = indexes[i];

    max = max + (100 - max % 100);

    paintGraphBase(&painter, max);

    for (int i = 0; i < _HISTOGRAM_CLASSES; i++)
        paintBar(&painter, max, i);
}

void Histogram::paintGraphBase(QPainter *painter, int max)
{
    int interval = max / 10;
    int posInterval = ZERO_POINT / 10;
    for (int i = 0; i <= 10; i++)
    {
        int val = max - i * interval;
        int pos = posInterval * i + TOP_SPACE;
        painter->drawText(0, pos - 5, QString::number(val));
        painter->drawLine(0, pos, (BAR_WIDTH + BAR_SPACE) * _HISTOGRAM_CLASSES + SIDE_SPACE, pos);
    }
}

void Histogram::paintBar(QPainter *painter, int max, int i)
{
    int size = qRound(double(indexes[i] * (ZERO_POINT - TOP_SPACE) / max)) + 1;

    QLinearGradient color;
    int starting_color = i * perClass;
    int ending_color   = (i + 1) * perClass - 1;
    color.setColorAt(0, QColor(starting_color, starting_color, starting_color));
    color.setColorAt(1, QColor(ending_color, ending_color, ending_color));
    painter->setBrush(color);
    painter->drawRect(i * (BAR_WIDTH + BAR_SPACE) + SIDE_SPACE, ZERO_POINT - size + TOP_SPACE, BAR_WIDTH, size);
    painter->drawText(i * (BAR_WIDTH + BAR_SPACE) + SIDE_SPACE, ZERO_POINT + 12 + TOP_SPACE, QString::number(i));

    painter->drawText(_HISTOGRAM_CLASSES * (BAR_WIDTH + BAR_SPACE) + SIDE_SPACE + 10,  i * 13 + 20, QString::number(i) + " = " + QString::number(starting_color) + " - " + QString::number(ending_color));
}
