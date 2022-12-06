#include "FindDialog.h"

FindDialog::FindDialog(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	connect(ui.buttonFind, &QPushButton::clicked, this, &FindDialog::onFind);
}

FindDialog::~FindDialog()
{
}

void FindDialog::SetText(QString text)
{
	this->text = text;
}

void FindDialog::onFind()
{
	QString str = ui.lineEdit->text();
	int index = text.indexOf(str);
	emit textFound(index, str.length());
}
