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

#ifndef IDEAL_FILTERED_IMAGE_H
#define IDEAL_FILTERED_IMAGE_H

#include <QLabel>
#include <QPoint>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QRubberBand>
#include <QList>

class IdealFilteredImage : public QLabel
{
    Q_OBJECT
    QImage *spec;
    int _x0, _y0; // image center
    QList<QRect> _selections;
    bool showGuideLines;
    
    // current selection
    QRubberBand *rubberBand;
    QPoint selOrigin, selDest;
public:
    IdealFilteredImage(QWidget* parent=nullptr);
    void setSpectrum(QImage*);
    QImage* spectrum();
    int y0();
    int x0();
    void paintEvent(QPaintEvent*);
    void setShowGuideLines(bool);
    QList<QRect> selections();
protected:
    void mousePressEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);
};

#endif
