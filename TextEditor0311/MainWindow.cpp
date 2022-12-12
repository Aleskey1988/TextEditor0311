#include "MainWindow.h"

#include <QFileDialog>
#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	QPalette pal = ui.textEdit->palette();
	pal.setColor(QPalette::HighlightedText, Qt::blue);
	pal.setColor(QPalette::Highlight, QColor(192, 192, 255));
	ui.textEdit->setPalette(pal);

	connect(ui.actionOpen, &QAction::triggered, this, &MainWindow::onOpen);
	connect(ui.actionSave, &QAction::triggered, this, &MainWindow::onSave);
	connect(ui.actionSaveAs, &QAction::triggered, this, &MainWindow::onSaveAs);
	connect(ui.actionFind, &QAction::triggered, this, &MainWindow::onFind);
	connect(ui.actionReplace, &QAction::triggered, this, &MainWindow::onReplace);
	
	connect(&findDialog, &FindDialog::textFound, this, &MainWindow::onTextFound);
	connect(&replaceDialog, &ReplaceDialog::textReplaced,
		this, &MainWindow::onTextReplaced);
}

void MainWindow::onOpen()
{
	QString fileName = QFileDialog::getOpenFileName(this,
		"Open file", "", "Text files (*.txt)");
	QFile file(fileName);
	file.open(QIODevice::ReadOnly);
	QString str(file.readAll());
	file.close();
	ui.textEdit->setText(str);
}
void MainWindow::onSave()
{
	if (lastFile.isEmpty())
	{
		QString fileName = QFileDialog::getSaveFileName(this,
			"Save file", "", "Text files (*.txt)");
		lastFile = fileName;
		save(lastFile);
	}
	else
		save(lastFile);
}
void MainWindow::onSaveAs()
{
	QString fileName = QFileDialog::getSaveFileName(this,
		"Save file", "", "Text files (*.txt)");
	lastFile = fileName;
	save(lastFile);
}
void MainWindow::onFind()
{
	findDialog.SetText(ui.textEdit->toPlainText());
	findDialog.show();
}

void MainWindow::onReplace()
{
	replaceDialog.SetText(ui.textEdit->toPlainText());
	replaceDialog.show();
}

void MainWindow::save(QString fileName)
{
	QFile file(fileName);
	file.open(QIODevice::WriteOnly);
	QTextStream s(&file);
	QString str = ui.textEdit->toPlainText();
	s << str;
	file.close();
}
void MainWindow::onTextFound(int index, int length)
{
	QTextCursor c = ui.textEdit->textCursor();
	c.setPosition(index);
	c.setPosition(index + length, QTextCursor::KeepAnchor);
	ui.textEdit->setTextCursor(c);
}

void MainWindow::onTextReplaced(QString text)
{
	ui.textEdit->setPlainText(text);
}
