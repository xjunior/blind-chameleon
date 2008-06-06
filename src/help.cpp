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

#include "help.h"
#include <QListWidgetItem>
#include <QIcon>
#include <QTextBrowser>
#include <QStackedWidget>
#include <QDebug>

Help::Help(PidMain *parent) : QDialog(parent)
{
    setupUi(this);

    QListWidgetItem *usage = new QListWidgetItem(helpList);
    usage->setIcon(QIcon(":/images/usage.png"));
    usage->setText("Usage");
    usage->setTextAlignment(Qt::AlignHCenter);
    usage->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    QListWidgetItem *filters = new QListWidgetItem(helpList);
    filters->setIcon(QIcon(":/images/star.png"));
    filters->setText("Filters");
    filters->setTextAlignment(Qt::AlignHCenter);
    filters->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    QListWidgetItem *impl = new QListWidgetItem(helpList);
    impl->setIcon(QIcon(":/images/impl.png"));
    impl->setText("Implementation");
    impl->setTextAlignment(Qt::AlignHCenter);
    impl->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    helps[0] = QUrl("qrc:/html/usage.html");
    helps[1] = QUrl("qrc:/html/filters.html");
    helps[2] = QUrl("qrc:/html/impl.html");

    connect(helpList, SIGNAL(currentItemChanged(QListWidgetItem*, QListWidgetItem*)),
                this, SLOT(changePage(QListWidgetItem*, QListWidgetItem*)));

    helpList->setCurrentRow(0);
    helpList->setFlow(QListView::TopToBottom);
}

void Help::changePage(QListWidgetItem *current, QListWidgetItem* prev)
{
    if (!current)
        current = prev;
    
    helpBrowser->clear();
    helpBrowser->setSource(helps[helpList->row(current)]);
    helpBrowser->reload();
}
