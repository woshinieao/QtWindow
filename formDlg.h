#ifndef FORM_H
#define FORM_H


#include <stdio.h>
#include <QList>
#include <QTimer>
#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QTextEdit>
#include <QTableWidgetItem>
#include <QMessageBox>
#include <QFile>
#include <QDebug>
#include <QPrinter>
#include <QPrintDialog>
#include <QPainter>
#include <QPrintPreviewDialog>
#include <QTextStream>
#include <QDesktopWidget>
#include <QDateTime>
#include <QTime>
#include <QDate>
#include <QFont>
#include <QStringList>
#include <QDir>
#include <QFileInfo>
#include <QScrollBar>
#include <QPen>
#include <QDialog>

#include "ui_formDlg.h"



class FormDlg: public QDialog,public Ui_FormDlg
{
	Q_OBJECT
public :
	FormDlg(QWidget *parent = 0);
	~FormDlg();
	void setFormId(unsigned int id);
private:
	unsigned int form_id;

};

#endif