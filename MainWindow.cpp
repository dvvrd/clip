/* Copyright 2015 CyberTech Labs Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License. */

#include <QFile>
#include <QClipboard>

#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::start);
	connect(ui->stopButton, &QPushButton::clicked, this, &MainWindow::stop);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::writeToFile(const QString &fileName, const QString &text) {
	QFile file(fileName);
	QIODevice::OpenModeFlag mode = ui->append->isChecked() ? QIODevice::Append : QIODevice::Truncate;
	if (file.open(QIODevice::WriteOnly | mode)) {
		file.write(("\n"+text).toUtf8());
		file.close();
	}
}

void MainWindow::listen(QClipboard::Mode m)
{
	if (m == QClipboard::Clipboard) {
		writeToFile(ui->fileName->text(), QApplication::clipboard()->text());
	}
}

void MainWindow::start()
{
	connect(QApplication::clipboard(), &QClipboard::changed, this, &MainWindow::listen);
}

void MainWindow::stop()
{
	disconnect(QApplication::clipboard(), &QClipboard::changed, this, &MainWindow::listen);
}
