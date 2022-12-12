#include "ReplaceDialog.h"

ReplaceDialog::ReplaceDialog(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setWindowFlags(Qt::MSWindowsFixedSizeDialogHint | Qt::Dialog);

	connect(ui.buttonReplace, &QPushButton::clicked, this, &ReplaceDialog::onReplace);
}

ReplaceDialog::~ReplaceDialog()
{
}

void ReplaceDialog::onReplace()
{
	QString source = text;
	QString findStr = ui.editReplaceWhat->text();
	QString replaceStr = ui.editReplaceTo->text();
	bool matchCase = ui.checkMatchCase->isChecked();

	int i = 0;
	while (i < source.length() - (findStr.length() - 1))
	{
		int l1 = source.length();
		int l2 = findStr.length();
		int l3 = source.length() - findStr.length() - 1;
		bool condition = false;
		if (matchCase)
			condition = source[i] == findStr[0];
		else
			condition = source[i].toUpper() == findStr[0].toUpper();
		if (condition)
		{
			int l = 1;
			for (int j = 1; j < findStr.length(); ++j)
			{
				if (matchCase)
					condition = source[j + i] == findStr[j];
				else
					condition = source[j + i].toUpper() == findStr[j].toUpper();
				if (condition)
					++l;
			}
			if (l == findStr.length())
			{
				QString left;
				for (int j = 0; j < i; ++j)
					left += source[j];
				QString right;
				for (int j = i + findStr.length(); j < source.length(); ++j)
					right += source[j];
				QString result = left + replaceStr + right;
				source = result;
			}
			else
				++i;
		}
		else
			++i;
	}
	emit textReplaced(source);
}
