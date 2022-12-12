#pragma once

#include <QWidget>
#include "ui_ReplaceDialog.h"

class ReplaceDialog : public QWidget
{
	Q_OBJECT

public:
	ReplaceDialog(QWidget *parent = Q_NULLPTR);
	~ReplaceDialog();

	void SetText(QString text) { this->text = text; }

signals:
	void textReplaced(QString text);

private:
	void onReplace();

	Ui::ReplaceDialog ui;
	QString text;
};
