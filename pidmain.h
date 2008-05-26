#ifndef PID_H
#define PID_H

#include "imagetabs.h"
#include "ui_main.h"

class PidMain : public QMainWindow, public Ui::PIDMainWindow
{
    Q_OBJECT

public:
    PidMain(QWidget *parent = 0);
    ImageTabs* getCurrentImageWindow();

public slots:
    void openImage();
    void generateGrayScale();
    void generateHistogram();
    void saveCurrentAs();
    void openAboutDialog();
    void openHelpDialog();

    // Filters
    void openPassaAltaIdeal();
    void openPassaBaixaIdeal();
    void openIdeal();
    void openButterworthAlta();
    void openButterworthBaixa();
};

#endif
