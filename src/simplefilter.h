#ifndef SIMPLE_FILTER_H
#define SIMPLE_FILTER_H

#include <QDialog>
#include "simplefilteredimage.h"
#include "ui_simplefilter.h"
#include "pidmain.h"
#include "imagetabs.h"
#include "basicfilter.h"

class SimpleFilter : public QDialog, public Ui::SimpleFilterDialog
{
    Q_OBJECT
    ImageTabs* images;
    BasicFilter* filter;
public:
    SimpleFilter(PidMain*, ImageTabs*, BasicFilter*);
    ~SimpleFilter();
public slots:
    void setFilterPosition();
    void setFilterPosition(int);
    void applyFilter();
private:
    QImage* image();
};

#endif
