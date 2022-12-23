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
	~MainWindow();

private:
	void onOpen();
	void onSave();
	void onSaveAs();
	void onExit();
	void onUndo();
	void onRedo();
	void onCut();
	void onCopy();
	void onPaste();
	void onDelete();
	void onSelectAll();
	void onFind();
	void onReplace();
	void onDateTime();
	void onIncreaseFontSize();
	void onDecreaseFontSize();
	void onFont();
	void onABout();

	void save(QString fileName);
	void onTextFound(int index, int length);
	void onTextReplaced(QString text);

	void saveSettings();
	void restoreSettings();

	Ui::MainWindowClass ui;
	QString lastFile;
	FindDialog findDialog;
	ReplaceDialog replaceDialog;
};
