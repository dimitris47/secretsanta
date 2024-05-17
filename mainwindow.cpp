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
#include "ui_mainwindow.h"
#include "langdialog.h"
#include "global.h"

#include <chrono>
#include <random>
#include <algorithm>
#include <QtMath>

#include <QLineEdit>
#include <QMessageBox>
#include <QProcess>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QScrollArea>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    readPreferences();
    ui->spinBox->setMinimum(3);
    ui->spinBox->setMaximum(99);
}


MainWindow::~MainWindow()
{
    delete ui;
}


bool MainWindow::calculate(int N)
{
    if (++calcCount == 65535) {
        return false;
    }

    players.clear();
    for (int i = 0; i < N; i++) {
        players.append(i);
    }

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle (players.begin(), players.end(), std::default_random_engine(seed));
    for (int i = 0; i < (int) sizeof(players); i++) {
        if (players[i] == i) {
            calculate(N);
        }
    }

    return true;
}


void MainWindow::on_actionEnter_Names_triggered()
{
    QDialog dialog(this);
    dialog.setWindowTitle(tr("Player Names"));
    auto layout = new QGridLayout(&dialog);
    auto frame = new QFrame(&dialog);
    frame->setLayout(layout);
    auto area = new QScrollArea(&dialog);
    area->setWidgetResizable(true);
    area->setWidget(frame);
    auto box = new QVBoxLayout(&dialog);
    dialog.setLayout(box);
    box->addWidget(area);

    int N = ui->spinBox->text().toInt();
    int columns = qCeil((float) N / 15);
    int rowsPerColumn = qCeil((float) N / columns);
    for (int i = 0; i < N; i++) {
        int column = i / rowsPerColumn;
        int row = i % rowsPerColumn;
        auto line = new QLineEdit(&dialog);
        line->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        line->setPlaceholderText(tr("Name of player no.") + QString::number(i + 1));
        line->setMinimumWidth(192);
        line->setAlignment(Qt::AlignCenter);
        layout->addWidget(line, row, column);
        line->show();
    }

    auto btnBox = new QDialogButtonBox(&dialog);
    btnBox->addButton(QDialogButtonBox::Cancel);
    btnBox->addButton(QDialogButtonBox::Ok);
    box->addWidget(btnBox);

    connect(btnBox, SIGNAL(rejected()), &dialog, SLOT(reject()));
    connect(btnBox, SIGNAL(accepted()), &dialog, SLOT(accept()));

    int hFactor, vFactor;
    columns == 1 ? hFactor = 320 : hFactor = 256;
    rowsPerColumn < 8 ? vFactor = 56 : vFactor = 42;
    dialog.resize(columns * hFactor, rowsPerColumn * vFactor);

    calcCount = 0;

    if (dialog.exec() == QDialog::Accepted) {
        if (calculate(N)) {
            names.clear();
            ui->comboBox->clear();
            auto lines = dialog.findChildren<QLineEdit *>();
            for (int i = 0; i < lines.count(); i++) {
                QString name;
                lines.at(i)->text() != "" ? name = lines.at(i)->text()
                        : name = tr("Player no.") + QString::number(i + 1);
                names.append(name);
                ui->comboBox->addItem(name);
            }
            QMessageBox::information(this, tr("Success"), tr("Lots shuffled successfully!"));
        } else {
            QMessageBox::warning(this, tr("Failure"), tr("Failed to shuffle the lots. Please try again."));
        }
    } else {
        QMessageBox::warning(this, tr("No players"), tr("No players added."));
    }
}


void MainWindow::on_actionGet_Result_triggered()
{
    if (!names.isEmpty()) {
        int currIdx = ui->comboBox->currentIndex();
        QString currStr = names.at(currIdx);
        QString currRes = names.at(players.at(currIdx));
        QMessageBox::about(this, tr("Your result"),
                           currStr + tr(", you are getting present for ") + currRes + "!");
    } else {
        QMessageBox::warning(this, tr("No players"), tr("There are no players yet."));
    }
}


void MainWindow::on_actionChange_Language_triggered()
{
    LangDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        if (dialog.greek != isGreek) {
            isGreek = dialog.greek;
            QSettings settings;
            settings.setValue("isGreek", isGreek);
            settings.sync();
            auto box = QMessageBox::question(this,
                                             tr("Language change"),
                                             tr("Changes will take effect after application restart. Restart now?"));
            if (box == QMessageBox::No) {
                return;
            } else {
                QProcess::startDetached(QApplication::applicationFilePath(), {});
                qApp->quit();
            }
        }
    }
}


void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, tr("Program Info"),
                       (QApplication::applicationName() + " " + QApplication::applicationVersion() + br.repeated(2) +
                        APPINFO));
}


void MainWindow::readPreferences()
{
    QSettings settings;

    bool isMax = settings.value("isMaximized", false).toBool();
    if (isMax) {
        showMaximized();
    } else {
        const QByteArray geometry = settings.value("geometry", QByteArray()).toByteArray();
        restoreGeometry(geometry);
    }

    isGreek = settings.value("isGreek", false).toBool();
}


void MainWindow::savePreferences()
{
    QSettings settings;

    settings.setValue("isMaximized", isMaximized());
    if (!isMaximized()) {
        settings.setValue("geometry", saveGeometry());
    }
    settings.sync();
}


void MainWindow::closeEvent(QCloseEvent *event)
{
    savePreferences();
    event->accept();
}
