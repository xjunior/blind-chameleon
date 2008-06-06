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

#ifndef HELP_H
#define HELP_H

#include "ui_help.h"
#include "pidmain.h"

class QDialog;
class QStackedWidget;
class QListWidgetItem;

class Help : public QDialog, public Ui::HelpDialog
{
    Q_OBJECT

    QUrl helps[3];

public:
    Help(PidMain*);

public slots:
    void changePage(QListWidgetItem*, QListWidgetItem*);
};

#endif
