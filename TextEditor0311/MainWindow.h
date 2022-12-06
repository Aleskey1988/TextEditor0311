#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include "FindDialog.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = Q_NULLPTR);

private:
	void onOpen();
	void onSave();
	void onSaveAs();
	void onFind();

	void save(QString fileName);
	void onTextFound(int index, int length);

	Ui::MainWindowClass ui;
	QString lastFile;
	FindDialog dlg;
};
