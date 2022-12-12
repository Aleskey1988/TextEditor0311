#include "FindDialog.h"

FindDialog::FindDialog(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setWindowFlags(Qt::MSWindowsFixedSizeDialogHint | Qt::Dialog);

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
	bool matchCase = ui.checkMatchCase->isChecked();
	int index = text.indexOf(str, 0, matchCase ? Qt::CaseSensitive : Qt::CaseInsensitive);
	emit textFound(index, str.length());
}
