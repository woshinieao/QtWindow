#include "ui_formDlg.h"
#include "formDlg.h"


FormDlg::FormDlg(QWidget *parent):QDialog(parent)
{
	 setupUi(this);
	 buttonBox->button(QDialogButtonBox::Ok)->setText("确定");
	 buttonBox->button(QDialogButtonBox::Cancel)->setText("取消");
	
}

void FormDlg::setFormId(unsigned int id)
{
	form_id = id;
	leId->setText(QString::number(form_id));
	leName->clear();
	lePhone->clear();
	lineEdit->clear();
}


FormDlg::~FormDlg()
{



}



