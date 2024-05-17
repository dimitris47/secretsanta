/**
 * Copyright 2020-2024 Dimitris Psathas <dimitrisinbox@gmail.com>
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


#include "mainwindow.h"
#include "global.h"

#include <QApplication>
#include <QTranslator>
#include <QSettings>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setOrganizationName("DP Software");
    QApplication::setApplicationName(APPNAME);
    QApplication::setApplicationVersion(VERSION);

    QSettings settings;
    bool isGreek = settings.value("isGreek", false).toBool();
    QTranslator translator;
    if (isGreek) {
        const QString baseName = "secretsanta_el_GR.ts";
        translator.load(":/i18n/" + baseName);
        a.installTranslator(&translator);
    }

    MainWindow w;
    w.show();

    return a.exec();
}
