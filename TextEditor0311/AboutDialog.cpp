#include "AboutDialog.h"

AboutDialog::AboutDialog(QDialog *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	connect(ui.buttonBox, &QDialogButtonBox::accepted, this, [=] { close(); });
}
AboutDialog::~AboutDialog()
{
}
