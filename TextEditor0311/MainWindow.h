#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include "FindDialog.h"
#include "ReplaceDialog.h"

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
	void onReplace();

	void save(QString fileName);
	void onTextFound(int index, int length);
	void onTextReplaced(QString text);

	Ui::MainWindowClass ui;
	QString lastFile;
	FindDialog findDialog;
	ReplaceDialog replaceDialog;
};
