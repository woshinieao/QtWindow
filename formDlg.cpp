#include "ui_formDlg.h"
#include "formDlg.h"


FormDlg::FormDlg(QWidget *parent):QDialog(parent)
{
	 setupUi(this);
	 buttonBox->button(QDialogButtonBox::Ok)->setText("ȷ��");
	 buttonBox->button(QDialogButtonBox::Cancel)->setText("ȡ��");
	
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



