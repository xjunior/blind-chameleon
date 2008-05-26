#ifndef IDEALFILTER_H
#define IDEALFILTER_H

#include <QDialog>
#include "ui_ideal.h"
#include "pidmain.h"
#include "imagetabs.h"

class IdealFilter : public QDialog, public Ui::IdealFilterDialog
{
    Q_OBJECT
    ImageTabs* images;
public:
    IdealFilter(PidMain*, ImageTabs*);
public slots:
    void applyFilter();
    void toggleShowGuideLines(bool);
private:
    QImage* image();
};

#endif
