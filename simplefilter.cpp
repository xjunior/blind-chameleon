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

#include "simplefilter.h"
#include "simplefilteredimage.h"
#include <math.h>
#include <QPainter>

SimpleFilter::SimpleFilter(PidMain *parent, ImageTabs* imgs, BasicFilter* filter) : QDialog(parent),
images(imgs)
{
    setupUi(this);
    this->filter = filter;
    scrollArea->setWidget(imageLabel);
    imageLabel->setSpectrum(image());
    filterPosition->setMaximum((int) round(hypot(imageLabel->x0(), imageLabel->y0())));
    filterPosition->setMinimum(0);

    connect(imageLabel, SIGNAL( imageClicked() ), this, SLOT( setFilterPosition() ));
    connect(filterPosition, SIGNAL( valueChanged(int) ), this, SLOT( setFilterPosition(int) ));
    connect(applyButton, SIGNAL( clicked() ), this, SLOT( applyFilter() ));
}

void SimpleFilter::setFilterPosition()
{
    filterPosition->setValue(imageLabel->z());
    imageLabel->update();
}

void SimpleFilter::setFilterPosition(int p)
{
    imageLabel->setZ(p);
    imageLabel->update();
}

void SimpleFilter::applyFilter()
{
    char *desc = filter->desc();
    images->addImage(QString().sprintf("%s [%d]", desc, filterPosition->value()), filter->run(images->getDFT(), filterPosition->value(), imageLabel));
    delete[] desc;
    close();
}

QImage* SimpleFilter::image()
{
    return images->getSpectrum();
}

SimpleFilter::~SimpleFilter()
{
    delete filter;
}

