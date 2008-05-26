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

#include <QtGui>
#include <QMdiArea>
#include <QMdiSubWindow>
#include "pidmain.h"
#include "about.h"
#include "help.h"
#include "imagetabs.h"
#include "simplefilter.h"
#include "idealfilter.h"
#include "butterworth.h"
#include "passaalta.h"
#include "passabaixa.h"

PidMain::PidMain(QWidget *parent) : QMainWindow(parent)
{
    setupUi(this);

    // Connect signals
    // File
    connect(menuOpenImage, SIGNAL( triggered() ), this, SLOT( openImage() ));
    connect(menuSaveCurrent, SIGNAL( triggered() ), this, SLOT( saveCurrentAs() ));

    // Image
    connect(menuGenerateGrayScale, SIGNAL( triggered() ), this, SLOT( generateGrayScale() ));
    connect(menuGenerateHistogram, SIGNAL( triggered() ), this, SLOT( generateHistogram() ));

    // Help
    connect(menuOpenAbout, SIGNAL( triggered() ), this, SLOT( openAboutDialog() ));
    connect(menuOpenHelp, SIGNAL( triggered() ), this, SLOT( openHelpDialog() ));

    // Filters
    connect(menuFiltersAltaIdeal, SIGNAL( triggered() ), this, SLOT( openPassaAltaIdeal() ));
    connect(menuFiltersBaixaIdeal, SIGNAL( triggered() ), this, SLOT( openPassaBaixaIdeal() ));
    connect(menuFiltersIdeal, SIGNAL( triggered() ), this, SLOT( openIdeal() ));
    connect(menuButterworthBaixa, SIGNAL( triggered() ), this, SLOT( openButterworthBaixa() ));
    connect(menuButterworthAlta, SIGNAL( triggered() ), this, SLOT( openButterworthAlta() ));

    // initializing some widgets
    mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
}

void
PidMain::openImage()
{
    QString path;

    path = QFileDialog::getOpenFileName(this,
        "Choose an image file to open",
        QString::null,
        "*.jpg *.jpeg");

    if (path != NULL)
    {
        ImageTabs *img = new ImageTabs(mdiArea, path);
        QMdiSubWindow *imgWindow = mdiArea->addSubWindow(img);
        imgWindow->setWindowTitle(path);
        imgWindow->show();
    }
}

void
PidMain::openHelpDialog()
{
    Help a(this);
    a.exec();
}

void
PidMain::openAboutDialog()
{
    About a(this);
    a.exec();
}

void
PidMain::generateGrayScale()
{
    ImageTabs* current = getCurrentImageWindow();

    if (current != NULL)
        current->generateGrayScale();
}

void
PidMain::generateHistogram()
{
    ImageTabs* current = getCurrentImageWindow();

    if (current != NULL)
        current->generateHistogram();
}

void
PidMain::saveCurrentAs()
{
    ImageTabs* current = getCurrentImageWindow();

    if (current != NULL)
    {
        QString path;

        path = QFileDialog::getSaveFileName(this,
            "Choose an image file to open",
            QString::null,
            "Images (*.jpg *.png)");

        if (path != NULL)
            current->getCurrent().save(path);
    }
}

void
PidMain::openPassaAltaIdeal()
{
    ImageTabs* current = getCurrentImageWindow();
    if (current != NULL)
    {
        SimpleFilter *filter = new SimpleFilter(this, current, new PassaAlta);
        filter->setAttribute(Qt::WA_DeleteOnClose);
        filter->exec();
    }
}

void
PidMain::openPassaBaixaIdeal()
{
    ImageTabs* current = getCurrentImageWindow();
    if (current != NULL)
    {
        SimpleFilter *filter = new SimpleFilter(this, current, new PassaBaixa);
        filter->setAttribute(Qt::WA_DeleteOnClose);
        filter->exec();
    }
}

void
PidMain::openButterworthBaixa()
{
    ImageTabs* current = getCurrentImageWindow();
    if (current != NULL)
    {
        SimpleFilter *filter = new SimpleFilter(this, current, new Butterworth(false));
        filter->setAttribute(Qt::WA_DeleteOnClose);
        filter->exec();
    }
}

void
PidMain::openButterworthAlta()
{
    ImageTabs* current = getCurrentImageWindow();
    if (current != NULL)
    {
        SimpleFilter *filter = new SimpleFilter(this, current, new Butterworth(true));
        filter->setAttribute(Qt::WA_DeleteOnClose);
        filter->exec();
    }
}

void
PidMain::openIdeal()
{
    ImageTabs* current = getCurrentImageWindow();
    if (current != NULL)
    {
        IdealFilter *filter = new IdealFilter(this, current);
        //filter->setAttribute(Qt::WA_DeleteOnClose);
        filter->exec();
    }
}

ImageTabs*
PidMain::getCurrentImageWindow()
{
    QMdiSubWindow *activeWindow = mdiArea->activeSubWindow();

    if (activeWindow == NULL)
        return NULL;
    else
        return (ImageTabs*)activeWindow->widget();
}
