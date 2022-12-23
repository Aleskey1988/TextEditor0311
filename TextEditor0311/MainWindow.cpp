#include "MainWindow.h"
#include "AboutDialog.h"

#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QFontDialog>
#include <QSettings>

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
	connect(ui.actionExit, &QAction::triggered, this, &MainWindow::onExit);
	
	connect(ui.actionUndo, &QAction::triggered, this, &MainWindow::onUndo);
	connect(ui.actionRedo, &QAction::triggered, this, &MainWindow::onRedo);
	connect(ui.actionCut, &QAction::triggered, this, &MainWindow::onCut);
	connect(ui.actionCopy, &QAction::triggered, this, &MainWindow::onCopy);
	connect(ui.actionPaste, &QAction::triggered, this, &MainWindow::onPaste);
	connect(ui.actionDelete, &QAction::triggered, this, &MainWindow::onDelete);
	connect(ui.actionSelectAll, &QAction::triggered, this, &MainWindow::onSelectAll);
	connect(ui.actionFind, &QAction::triggered, this, &MainWindow::onFind);
	connect(ui.actionReplace, &QAction::triggered, this, &MainWindow::onReplace);
	connect(ui.actionDateAndTime, &QAction::triggered, this, &MainWindow::onDateTime);

	connect(ui.actionIncreaseFontSize, &QAction::triggered, this, &MainWindow::onIncreaseFontSize);
	connect(ui.actionDecreaseFontSize, &QAction::triggered, this, &MainWindow::onDecreaseFontSize);
	connect(ui.actionFont, &QAction::triggered, this, &MainWindow::onFont);

	connect(ui.actionAbout, &QAction::triggered, this, &MainWindow::onABout);
	
	connect(&findDialog, &FindDialog::textFound, this, &MainWindow::onTextFound);
	connect(&replaceDialog, &ReplaceDialog::textReplaced, this, &MainWindow::onTextReplaced);

	restoreSettings();
}
MainWindow::~MainWindow()
{
	saveSettings();
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
void MainWindow::onExit()
{
	close();
}
void MainWindow::onUndo()
{
	ui.textEdit->undo();
}
void MainWindow::onRedo()
{
	ui.textEdit->redo();
}
void MainWindow::onCut()
{
	ui.textEdit->cut();
}
void MainWindow::onCopy()
{
	ui.textEdit->copy();
}
void MainWindow::onPaste()
{
	ui.textEdit->paste();
}
void MainWindow::onDelete()
{
	QTextCursor cursor = ui.textEdit->textCursor();
	int pos1 = cursor.anchor();
	int pos2 = cursor.position();
	if (pos1 > pos2)
		qSwap(pos1, pos2);
	QString str = ui.textEdit->toPlainText();
	QString newStr;
	for (int i = 0; i < pos1; ++i)
		newStr += str[i];
	for (int i = pos2; i < str.length(); ++i)
		newStr += str[i];
	ui.textEdit->setPlainText(newStr);
}
void MainWindow::onSelectAll()
{
	ui.textEdit->selectAll();
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
void MainWindow::onDateTime()
{
	// 10:35 13.12.2022
	QDateTime dt = QDateTime::currentDateTime();
	QString str = dt.toString("hh:mm dd.MM.yyyy");
	ui.textEdit->setPlainText(ui.textEdit->toPlainText() + str);
}
void MainWindow::onIncreaseFontSize()
{
	QFont font = ui.textEdit->font();
	double fontSize = font.pointSizeF();
	fontSize *= 1.1;
	font.setPointSizeF(fontSize);
	ui.textEdit->setFont(font);
}
void MainWindow::onDecreaseFontSize()
{
	QFont font = ui.textEdit->font();
	double fontSize = font.pointSizeF();
	fontSize /= 1.1;
	font.setPointSizeF(fontSize);
	ui.textEdit->setFont(font);
}
void MainWindow::onFont()
{
	bool ok = false;
	QFont font = QFontDialog::getFont(&ok, ui.textEdit->font(), nullptr, "Select font");
	ui.textEdit->setFont(font);
}
void MainWindow::onABout()
{
	AboutDialog dlg;
	dlg.exec();
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

void MainWindow::saveSettings()
{
	QSettings s("settings.ini", QSettings::IniFormat);
	s.beginGroup("Main");
	s.setValue("mainWindowGeometry", saveGeometry());
	s.setValue("findDialogGeometry", findDialog.saveGeometry());
	s.setValue("replaceDialogGeometry", replaceDialog.saveGeometry());
	QFont font = ui.textEdit->font();
	s.setValue("fontFamily", font.family());
	s.setValue("fontSize", font.pointSizeF());
}
void MainWindow::restoreSettings()
{
	QSettings s("settings.ini", QSettings::IniFormat);
	s.beginGroup("Main");
	QByteArray mainWindowGeometry = s.value("mainWindowGeometry").toByteArray();
	QByteArray findDialogGeometry = s.value("findDialogGeometry").toByteArray();
	QByteArray replaceDialogGeometry = s.value("replaceDialogGeometry").toByteArray();
	QString fontFamily = s.value("fontFamily").toString();
	double fontSize = s.value("fontSize").toDouble();
	restoreGeometry(mainWindowGeometry);
	findDialog.restoreGeometry(findDialogGeometry);
	replaceDialog.restoreGeometry(replaceDialogGeometry);
	QFont font = ui.textEdit->font();
	font.setFamily(fontFamily);
	font.setPointSizeF(fontSize);
	ui.textEdit->setFont(font);
}
