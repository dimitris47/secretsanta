#ifndef GLOBAL_H
#define GLOBAL_H

#include <QString>

const QString br("<br/>");
const QString APPNAME("Secret Santa");
const QString VERSION("1.0");
const QString CONTRIBUTORS("Dimitris Psathas");

const QString APPINFO("Program created by Dimitris Psathas" + br.repeated(2) +
                      "Written in C++, built against Qt" + br.repeated(2) +
                      "Published under the GNU Public License v3.0" + br +
                      "Qt libraries used under (L)GPL3" + br +
                      "Application icon by <a href='https://icons8.com'>icons8.com</a>" + br +
                      "In-app icons by the Ubuntu Yaru theme community" + br.repeated(2) +
                      "&copy; 2020-2024 Dimitris Psathas");

#endif // GLOBAL_H
