/**
 * Copyright 2021 Dimitris Psathas <dimitrisinbox@gmail.com>
 *
 * This file is part of Secret Santa.
 *
 * Secret Santa is free software: you can redistribute it and/or modify it under the
 * terms of the GNU General Public License  as  published by  the  Free Software
 * Foundation,  either version 3 of the License,  or (at your option)  any later
 * version.
 *
 * Secret Santa is distributed in the hope that it will be useful,  but  WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE.  See the  GNU General Public License  for more details.
 *
 * You should have received a copy of the  GNU General Public License along with
 * Secret Santa. If not, see <http://www.gnu.org/licenses/>.
 */


#include "langdialog.h"
#include "ui_langdialog.h"

#include <QSettings>


LangDialog::LangDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LangDialog)
{
    ui->setupUi(this);

    QSettings settings;
    bool isGreek = settings.value("isGreek", false).toBool();
    if (isGreek) {
        ui->greBtn->setChecked(true);
        greek = true;
    } else {
        ui->engBtn->setChecked(true);
        greek = false;
    }
}


LangDialog::~LangDialog()
{
    delete ui;
}


void LangDialog::on_engBtn_clicked()
{
    greek = false;
}


void LangDialog::on_greBtn_clicked()
{
    greek = true;
}
