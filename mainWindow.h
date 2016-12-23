#ifndef MAINWINDOW_H
#define MAINWINDOW_H


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
#include <QDialogButtonBox>

#include "mydb.h"
#include "formDlg.h"
#include "ui_mainWindow.h"

#define  FILE_NAME 		"parameter.ini"
#define  FILE_NAMEBAK 	"parameter_bak.ini"
typedef struct _wind_device{
	unsigned int iheight;//宽
	unsigned int iwidth;//高
	unsigned int zhong_feng_num;
	unsigned int bian_feng_hou;//边封厚度
	unsigned int bian_feng;//边封
	unsigned int di_gao; //底高
	
	unsigned int zhong_zhu; //中柱
	unsigned int shang_gu_hou;	//上固厚度
	unsigned int shang_gu;	//上固
	unsigned int gu_shang_hua;//固上滑
	unsigned int zhong_feng_hou;//中封厚度
	unsigned int gou_guang_qi_input;
	unsigned int shang_xia_fang_input;

	unsigned int ping_shang_xia_hua;
	unsigned int gai_ban;
	unsigned int zhong_feng;
	unsigned int gou_guang_qi;
	unsigned int shang_xia_fang;

	unsigned int zhong_zhu_num;
	unsigned int bian_feng_num;
	unsigned int gu_shang_hua_num;
	unsigned int shang_gu_num;
	unsigned int ping_shang_hua_num;
	unsigned int gai_ban_num;
	unsigned int gou_guang_qi_num;



}wind_dev_t;

typedef struct _wind_content{

	char material_type[32];
	unsigned int shang_xia_fang_input;
	unsigned int plus_minus_symbol ;
	unsigned int gou_guang_qi_input;
	unsigned int shang_gu_hou;	//上固厚度
	unsigned int bian_feng_hou;
	unsigned int zhong_feng_hou;//中封厚度
	unsigned int zhong_zhu_hou;
	unsigned int shan_bo_gao_input;
	unsigned int shan_bo_kuan_input;
	unsigned int pao_mao;
	unsigned int gu_bo_kuan_input;
	
}wind_content_t;


class FormDlg;

class mainWindow: public QMainWindow, public Ui_MainWindow
{
	Q_OBJECT
public :
	mainWindow(QWidget *parent = 0);
	bool check_state();
	void init_ui();
	int init_data();

	~mainWindow();
public slots:
	void choose_window_tpye(int curIdx);
	int material_type_change(int index);

	void para_mode();
	int set_para();
	bool save_para();
	bool del_para();
	int cancel_para();
	
	void calculate_mode();
	void calculate();
	
	void query_mode();
	void query_history();
	void query_data();
	void query_data_clean();
	void save_to_file();
	void del_resualt();
	void print_view();
	
	void print(QPrinter *printer);
private:
	
	int widTpye;
	wind_content_t wind_param[24];
	wind_dev_t wind_dev;
	QDate query_date;
	unsigned int save_time;

	bool new_data_exist;
	bool old_data_clean;
	QString tittle ;
	QString tel;
	QString addr;
	FormDlg form;

	
	QLabel *lb_pic;
unsigned int iheight;//高 
unsigned int iwidth;//宽
unsigned int zhong_feng_num;
unsigned int bian_feng_hou;//边封厚度
unsigned int bian_feng;//边封
unsigned int di_gao; //底高
unsigned int tang_shu; //

unsigned int zhong_zhu; //中柱
unsigned int shang_gu_hou;	//上固厚度
unsigned int shang_gu;	//上固
unsigned int gu_shang_hua;//固上滑
unsigned int zhong_feng_hou;//中封厚度
unsigned int gou_guang_qi_input;
unsigned int shang_xia_fang_input;

unsigned int ping_shang_xia_hua;
unsigned int gai_ban;
unsigned int zhong_feng;
unsigned int gou_guang_qi;
unsigned int shang_xia_fang;

unsigned int zhong_zhu_num;
unsigned int bian_feng_num;
unsigned int gu_shang_hua_num;
unsigned int shang_gu_num;
unsigned int ping_shang_hua_num;
unsigned int gai_ban_num;
unsigned int gou_guang_qi_num;

unsigned int shan_bo_gao_input;
unsigned int shan_bo_kuan_input;
//unsigned int gu_bo_gao_input;
unsigned int pao_mao;
unsigned int gu_bo_kuan_input;

unsigned int shan_bo_gao;
unsigned int shan_bo_kuan;
unsigned int gu_bo_gao;
unsigned int gu_bo_kuan;
unsigned int zhong_zhu_hou;
unsigned int gu_bo_num;

qint64 window_area;
qint64 gu_bo_area;
qint64 shan_bo_area;

db_ops *pDb_ops;


};

#endif
