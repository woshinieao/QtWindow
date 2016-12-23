#include "mainWindow.h"

#include <time.h>

mainWindow::mainWindow(QWidget *parent): QMainWindow(parent)
{
	setupUi(this);

	tableServerWidget->horizontalHeader()->setResizeMode(QHeaderView::Stretch );
	tableServerWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);  
	tableServerWidget->horizontalHeader()->setStretchLastSection(true); 




formtableWidget->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents );
formtableWidget->horizontalHeader()->setStretchLastSection(true); 



	connect(btnQueryBack,SIGNAL(clicked()),this,SLOT(calculate_mode()));
		

	connect(btnCalc,SIGNAL(clicked()),this,SLOT(calculate()));
	connect(btnSave,SIGNAL(clicked()),this,SLOT(save_to_file()));
	connect(btnDel,SIGNAL(clicked()),this,SLOT(del_resualt()));	
	connect(btnSetPara,SIGNAL(clicked()),this,SLOT(set_para()));
	connect(btnSavePara,SIGNAL(clicked()),this,SLOT(save_para()));
	connect(btnDelPara,SIGNAL(clicked()),this,SLOT(del_para()));
	connect(btnParaCancel,SIGNAL(clicked()),this,SLOT(cancel_para()));
	
		

	connect(comboBox,SIGNAL(currentIndexChanged ( int)),this,SLOT(choose_window_tpye(int )));
	connect(cbox_material_type,SIGNAL(currentIndexChanged ( int)),this,SLOT(material_type_change(int )));
	connect(btnPrint,SIGNAL(clicked()),this,SLOT(print_view()));
	connect(btnQueryMode,SIGNAL(clicked()),this,SLOT(query_mode()));
	connect(btnQuery,SIGNAL(clicked()),this,SLOT(query_history()));
	connect(btnQureyData,SIGNAL(clicked()),this,SLOT(query_data()));
	connect(btnDataClose,SIGNAL(clicked()),this,SLOT(query_data_clean()));

	

	le_width->setValidator(new QIntValidator(0,99999,this));
	le_height->setValidator(new QIntValidator(0,99999,this));
	le_bottom_height->setValidator(new QIntValidator(0,99999,this));
	le_zhong_feng_num->setValidator(new QIntValidator(0,99,this));
	
	le_material_type->setValidator(new QIntValidator(0,99999,this));
	le_gou_guang_qi_constant->setValidator(new QIntValidator(0,999,this));
	le_shang_xia_fang_constant->setValidator(new QIntValidator(0,999,this));
	le_bian_feng_hou_du->setValidator(new QIntValidator(0,999,this));
	le_zhong_feng_hou->setValidator(new QIntValidator(0,999,this));
	le_shang_gu_hou_du->setValidator(new QIntValidator(0,999,this));
	le_tangshu->setValidator(new QIntValidator(0,999,this));

	le_zhong_zhu_hou->setValidator(new QIntValidator(0,999,this));
	le_shan_bo_gao->setValidator(new QIntValidator(0,999,this));
	le_shan_bo_kuan->setValidator(new QIntValidator(0,999,this));
	le_pao_mao->setValidator(new QIntValidator(0,999,this));
	le_gu_bo_kuan->setValidator(new QIntValidator(0,999,this));
	pDb_ops = db_init_mysql();
	init_ui();
	init_data();
	calculate_mode();
	ckbox_gaiban->setChecked(false);
}
void mainWindow::init_ui()
{
	comboBox->setEnabled(false);
	cbox_material_type->setEnabled(false);
	
	le_material_type->setEnabled(false);
	le_gou_guang_qi_constant->setEnabled(false);
	cbox_operator->setEnabled(false);
	le_shang_xia_fang_constant->setEnabled(false);
	le_bian_feng_hou_du->setEnabled(false);	
	le_zhong_feng_hou->setEnabled(false);
	le_shang_gu_hou_du->setEnabled(false);
	le_zhong_zhu_hou->setEnabled(false);
	le_shan_bo_gao->setEnabled(false);
	le_shan_bo_kuan->setEnabled(false);	
	le_pao_mao->setEnabled(false);
	le_gu_bo_kuan->setEnabled(false);
	deStartTime->setCalendarPopup(true);
	deEndTime->setCalendarPopup(true);
	gbQuery->hide();
	for(;tableServerWidget->rowCount()>0;)
	{
		tableServerWidget->removeRow(0); 
				
	}
	for(;formtableWidget->rowCount()>0;)
	{
		formtableWidget->removeRow(0); 
				
	}
	btnSavePara->setEnabled(false);
	btnParaCancel->setEnabled(false);
	QDesktopWidget *desk = QApplication::desktop();
	int screenWidth=1100;
	int screenHeight=450;
	screenWidth = desk->width();
	screenHeight = desk->height();
	this->setFixedSize(QSize(screenWidth, screenHeight));

	le_width->clear();
	le_height->clear();
	le_bottom_height->clear();
	le_zhong_feng_num->setText("0");
	le_tangshu->setText("1");
	
	tableServerWidget->setColumnWidth (11, 30);

	btnSavePara->setEnabled(false);



}

int mainWindow::init_data()
{

	query_date.setDate(0,0,0);
	save_time = 0;
	new_data_exist = true;
	old_data_clean = true;
	deStartTime->setDateTime(QDateTime::currentDateTime());
	deEndTime->setDateTime(QDateTime::currentDateTime());
	window_area=0;
	gu_bo_area=0;
	shan_bo_area=0;
	memset(wind_param,0,24*sizeof(wind_content_t));
	void *result;
	char **row;
	char sql[320];
	int iRow=0;
	int iParam = 0;
	wind_content_t *pList = NULL;
	sprintf(sql,"SELECT materal_id,shang_xia_fang_input,plus_minus_symbol,gou_guang_qi_input,shang_gu_hou,bian_feng_hou,zhong_feng_hou,zhong_zhu_hou,shan_bo_gao_input,shan_bo_kuan_input,pao_mao,gu_bo_kuan_input	FROM table_wind_param order by log_time desc");
	result = pDb_ops->getfirst(sql);
	while (result)
	{
		pList   = &wind_param[iParam];
		row   = (char **)result;
		iRow  = 0;

	
		/*materal_id*/
		if(row[iRow] == NULL)
			continue;
		strcpy(pList->material_type,row[iRow]);
		iRow++;
		
		/*shang_xia_fang_input*/
		if(row[iRow] == NULL)
			continue;
		pList->shang_xia_fang_input = atoi(row[iRow]);
		iRow++;

		/*plus_minus_symbol*/
		if(row[iRow] == NULL)
			continue;
		pList->plus_minus_symbol = atoi(row[iRow]);
		iRow++;

		/*gou_guang_qi_input*/
		if(row[iRow] == NULL)
			continue;
		pList->gou_guang_qi_input = atoi(row[iRow]);
		iRow++;
		
		/*shang_gu_hou*/
		if(row[iRow] == NULL)
			continue;
		pList->shang_gu_hou = atoi(row[iRow]);
		iRow++;

		/*bian_feng_hou*/
		if(row[iRow] == NULL)
			continue;
		pList->bian_feng_hou = atoi(row[iRow]);
		iRow++;


		/*zhong_feng_hou*/
		if(row[iRow] == NULL)
			continue;
		pList->zhong_feng_hou = atoi(row[iRow]);
		iRow++;

		/*zhong_zhu_hou*/
		if(row[iRow] == NULL)
			continue;
		pList->zhong_zhu_hou = atoi(row[iRow]);
		iRow++;
		/*shan_bo_gao_input*/
		if(row[iRow] == NULL)
			continue;
		pList->shan_bo_gao_input = atoi(row[iRow]);
		iRow++;
		/*shan_bo_kuan_input*/
		if(row[iRow] == NULL)
			continue;
		pList->shan_bo_kuan_input = atoi(row[iRow]);
		iRow++;
		/*pao_mao*/
		if(row[iRow] == NULL)
			continue;
		pList->pao_mao = atoi(row[iRow]);
		iRow++;
		/*gu_bo_kuan_input*/
		if(row[iRow] == NULL)
			continue;
		pList->gu_bo_kuan_input = atoi(row[iRow]);
		iRow++;
		cbox_material_type->addItem(pList->material_type,QVariant(iParam));
			iParam++;
		if(iParam>24)
			break;
		result = pDb_ops->getnext();
	}
	


	
#if 0	 //之前参数保存在配置文件中
	fp = fopen(FILE_NAME,"a+");
	if(fp == NULL)
	{
	printf(" open failed !\n");
		return -1 ;
	}
	
	char sss[54];
	 

	struct wind_list * plast = NULL;
	plast = &wid_list_head;
	memset(sss,'\0',54);
	printf("-------------init ----------------|\n");
	while(fgets(sss,54,fp) !=NULL)	
	{
		struct wind_list * ptmp;
		ptmp = (struct wind_list *)malloc(sizeof(struct wind_list ));
			
		memset(ptmp,'\0',sizeof(struct wind_list ));
		
		memcpy((char *)&(ptmp->wid_content),sss,sizeof(wind_content_t));
		printf("|     %d  %d  %d  %d  %d  %d %d %d\n",ptmp->wid_content.material_type,ptmp->wid_content.plus_minus_symbol,ptmp->wid_content.shang_xia_fang_input,
									ptmp->wid_content.gou_guang_qi_input ,ptmp->wid_content.shang_gu_hou,
									ptmp->wid_content.bian_feng_hou,ptmp->wid_content.zhong_feng_hou,ptmp->wid_content.zhong_zhu_hou);
		ptmp->prev = plast;
		ptmp->next =plast->next ;
		plast->next = ptmp;
		plast = ptmp;
		cbox_material_type->addItem(QString::number( plast->wid_content.material_type));
		ptmp = NULL;
		memset(sss,'\0',32);

	}
	
	fclose(fp);
	printf("----------------------------------|\n");

#endif
	cbox_material_type->setCurrentIndex(0);
	le_zhong_feng_num->setText("0");
	le_tangshu->setText("1");
	choose_window_tpye(0);

	tittle = tr("嘉运铝材");
	return 0;


}


bool mainWindow::check_state()
{
	
	if(le_width->text().isEmpty() || le_height->text().isEmpty()
	     ||  le_gou_guang_qi_constant->text().isEmpty()
	     || le_shang_xia_fang_constant->text().isEmpty())
	     return false ;
	return true;


	
}


void mainWindow::choose_window_tpye(int curIdx)
{

	if(curIdx != 0)
	{

		cbox_material_type->setEnabled(true);

	}
	else
	{
		calculate_mode();
	}
	
	widTpye = curIdx;
	qDebug()<<"widType = "<<widTpye;
	QString str ;
	str = QString::number(curIdx);
	str.append(".png");
	QPixmap pixmap(str);
	pic_lb->setScaledContents(true);
 	pic_lb->setPixmap(pixmap);
	
}

int mainWindow::material_type_change(int index)
{
	le_material_type->clear();
	le_gou_guang_qi_constant->clear();
	le_shang_xia_fang_constant->clear();
	le_bian_feng_hou_du->clear();
	le_zhong_feng_hou->clear();
	le_shang_gu_hou_du->clear();
	le_zhong_zhu_hou->clear();
	le_shan_bo_gao->clear();
	le_shan_bo_kuan->clear();
	le_pao_mao->clear();
	le_gu_bo_kuan->clear();

	if(cbox_material_type->count() == 0)
		return 0;
	le_material_type->setText(wind_param[index].material_type); 
	le_gou_guang_qi_constant->setText(QString::number(wind_param[index].gou_guang_qi_input));
	le_shang_xia_fang_constant->setText(QString::number(wind_param[index].shang_xia_fang_input));
	le_shang_gu_hou_du->setText(QString::number(wind_param[index].shang_gu_hou));
	le_zhong_feng_hou->setText(QString::number(wind_param[index].zhong_feng_hou));
	le_bian_feng_hou_du->setText(QString::number(wind_param[index].bian_feng_hou));
	le_zhong_zhu_hou->setText(QString::number(wind_param[index].zhong_zhu_hou));
	le_shan_bo_gao->setText(QString::number(wind_param[index].shan_bo_gao_input));
	le_shan_bo_kuan->setText(QString::number(wind_param[index].shan_bo_kuan_input));
	le_pao_mao->setText(QString::number(wind_param[index].pao_mao));
	le_gu_bo_kuan->setText(QString::number(wind_param[index].gu_bo_kuan_input));

	cbox_operator->setCurrentIndex(wind_param[index].plus_minus_symbol);

	le_material_type->setEnabled(false);
	le_gou_guang_qi_constant->setEnabled(false);
	cbox_operator->setEnabled(false);
	le_shang_xia_fang_constant->setEnabled(false);
	le_bian_feng_hou_du->setEnabled(false);	
	le_zhong_feng_hou->setEnabled(false);
	le_shang_gu_hou_du->setEnabled(false);
	le_zhong_zhu_hou->setEnabled(false);
	le_shan_bo_gao->setEnabled(false);
	le_shan_bo_kuan->setEnabled(false);	
	le_pao_mao->setEnabled(false);
	le_gu_bo_kuan->setEnabled(false);
	return 0;
}


void mainWindow::para_mode()
{
	init_ui();
	
}


int mainWindow::set_para()
{
	
	le_material_type->setEnabled(true);
	le_gou_guang_qi_constant->setEnabled(true);
	cbox_operator->setEnabled(true);
	le_shang_xia_fang_constant->setEnabled(true);
	le_bian_feng_hou_du->setEnabled(true);	
	le_zhong_feng_hou->setEnabled(true);
	le_shang_gu_hou_du->setEnabled(true);
	le_zhong_zhu_hou->setEnabled(true);
	le_shan_bo_gao->setEnabled(true);
	le_shan_bo_kuan->setEnabled(true);	
	le_pao_mao->setEnabled(true);
	le_gu_bo_kuan->setEnabled(true);

	le_material_type->clear();
	le_gou_guang_qi_constant->clear();
	le_shang_xia_fang_constant->clear();
	le_bian_feng_hou_du->clear();
	le_zhong_feng_hou->clear();
	le_shang_gu_hou_du->clear();
	le_zhong_zhu_hou->clear();
	le_zhong_zhu_hou->clear();
	le_shan_bo_gao->clear();
	le_shan_bo_kuan->clear();
	le_pao_mao->clear();
	le_gu_bo_kuan->clear();
	btnSavePara->setEnabled(true);
	btnParaCancel->setEnabled(true);
	btnDelPara->setEnabled(false);

	return 0;

}

bool mainWindow::save_para()
{
	char sql[512];
	time_t currentTime = time(NULL);
	int id =0;
	for(id = 0;id<24;id++)
	{
		if(wind_param[id].shang_xia_fang_input == 0 && wind_param[id].gou_guang_qi_input == 0)
			break;
	}
	
	strcpy(wind_param[id].material_type,le_material_type->text().toAscii());  
	wind_param[id].shang_xia_fang_input = le_shang_xia_fang_constant->text().toUInt(); 
	wind_param[id].gou_guang_qi_input = le_gou_guang_qi_constant->text().toUInt(); 
	wind_param[id].shang_gu_hou = le_shang_gu_hou_du->text().toUInt();  
	wind_param[id].zhong_feng_hou = le_zhong_feng_hou->text().toUInt(); 
	wind_param[id].bian_feng_hou = le_bian_feng_hou_du->text().toUInt();
	wind_param[id].zhong_zhu_hou = le_zhong_zhu_hou->text().toUInt(); 
	wind_param[id].shan_bo_gao_input = le_shan_bo_gao->text().toUInt();  
	wind_param[id].shan_bo_kuan_input = le_shan_bo_kuan->text().toUInt(); 
	wind_param[id].pao_mao = le_pao_mao->text().toUInt(); 
	wind_param[id].gu_bo_kuan_input = le_gu_bo_kuan->text().toUInt(); 


	if(cbox_operator->currentIndex() == 0)
		wind_param[id].plus_minus_symbol = 0;
	else
		wind_param[id].plus_minus_symbol= 1;

	sprintf(sql,"insert into table_wind_param(materal_id,shang_xia_fang_input,plus_minus_symbol,gou_guang_qi_input,shang_gu_hou,bian_feng_hou,zhong_feng_hou,zhong_zhu_hou,shan_bo_gao_input,shan_bo_kuan_input,pao_mao,gu_bo_kuan_input,log_time) value(%s,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%lu)",
		wind_param[id].material_type,
		wind_param[id].shang_xia_fang_input,
		wind_param[id].plus_minus_symbol,
		wind_param[id].gou_guang_qi_input,
		wind_param[id].shang_gu_hou,
		wind_param[id].bian_feng_hou,
		wind_param[id].zhong_feng_hou,
		wind_param[id].zhong_zhu_hou,
		wind_param[id].shan_bo_gao_input,
		wind_param[id].shan_bo_kuan_input,
		wind_param[id].pao_mao,
		wind_param[id].gu_bo_kuan_input,
		currentTime);	
	
	int ret = pDb_ops->excute(sql);
	if(ret<0)
	{
		QMessageBox::warning(this,tr("警告"),tr("参数保存失败\n"),tr("确定"));
		memset(&wind_param[id],0,sizeof(wind_content_t));
		return false;

	}
	else
		QMessageBox::warning(this,tr("警告"),tr("参数保存成功\n"),tr("确定"));
		
	cbox_material_type->addItem(wind_param[id].material_type,QVariant(id));
	le_material_type->setEnabled(false);
	le_gou_guang_qi_constant->setEnabled(false);
	cbox_operator->setEnabled(false);
	le_shang_xia_fang_constant->setEnabled(false);
	le_bian_feng_hou_du->setEnabled(false);	
	le_zhong_feng_hou->setEnabled(false);
	le_shang_gu_hou_du->setEnabled(false);
	le_zhong_zhu_hou->setEnabled(false);
	le_shan_bo_gao->setEnabled(false);
	le_shan_bo_kuan->setEnabled(false);	
	le_pao_mao->setEnabled(false);
	le_gu_bo_kuan->setEnabled(false);
	cbox_material_type->setCurrentIndex(id);
	btnSavePara->setEnabled(false);


	for(int i = 0;i<cbox_material_type->count();i++)
	{
		int id1=0;
		QVariant varId1;
		varId1 = cbox_material_type->itemData(i,Qt::UserRole);
		if (varId1.canConvert<int>())
			id1 = varId1.value<int>();
		qDebug()<<i<<"----id1: "<<id1<<"------num: "<<wind_param[id1].material_type;

	}
	btnDelPara->setEnabled(true);
	return true;
	

}

bool mainWindow::del_para()
{
	char sql[512];
	int delIndex = cbox_material_type->currentIndex();
	int id=0;
	QVariant varId;
	varId = cbox_material_type->itemData(delIndex,Qt::UserRole);
	if (varId.canConvert<int>())
			id = varId.value<int>();
		qDebug()<<"del:"<<delIndex<<"-------"<<id;
	
	sprintf(sql,"delete from table_wind_param where materal_id = %s",wind_param[id].material_type);
	
	memset(&wind_param[id],0,sizeof(wind_content_t));
	pDb_ops->excute(sql);
	 
	cbox_material_type->removeItem(delIndex);

	
	for(int i = 0;i<cbox_material_type->count();i++)
	{
		int id1=0;
		QVariant varId1;
		varId1 = cbox_material_type->itemData(i,Qt::UserRole);
		if (varId1.canConvert<int>())
			id1 = varId.value<int>();
		qDebug()<<"left:"<<i<<"-------"<<id1;

	}
	cbox_material_type->setCurrentIndex(0);

	return true;
}

int mainWindow::cancel_para()
{

	le_material_type->clear();
	le_gou_guang_qi_constant->clear();
	le_shang_xia_fang_constant->clear();
	le_bian_feng_hou_du->clear();
	le_zhong_feng_hou->clear();
	le_shang_gu_hou_du->clear();
	le_zhong_zhu_hou->clear();
	le_shan_bo_gao->clear();
	le_shan_bo_kuan->clear();
	le_pao_mao->clear();
	le_gu_bo_kuan->clear();

	
	le_material_type->setEnabled(false);
	le_gou_guang_qi_constant->setEnabled(false);
	cbox_operator->setEnabled(false);
	le_shang_xia_fang_constant->setEnabled(false);
	le_bian_feng_hou_du->setEnabled(false);	
	le_zhong_feng_hou->setEnabled(false);
	le_shang_gu_hou_du->setEnabled(false);
	le_zhong_zhu_hou->setEnabled(false);
	le_shan_bo_gao->setEnabled(false);
	le_shan_bo_kuan->setEnabled(false);	
	le_pao_mao->setEnabled(false);
	le_gu_bo_kuan->setEnabled(false);
	material_type_change(cbox_material_type->currentIndex());
	btnSavePara->setEnabled(false);
	btnParaCancel->setEnabled(false);
	btnDelPara->setEnabled(true);

	return 0;

}

void mainWindow::calculate_mode()
{
	
	tableServerWidget->show();
	gbQuery->hide();
	comboBox->setEnabled(true);
	cbox_material_type->setEnabled(true);
	comboBox->setCurrentIndex(0);
	if(cbox_material_type->currentIndex() !=0)
	{
		le_width->setEnabled(true);
		le_height->setEnabled(true);
		le_bottom_height->setEnabled(true);
		le_zhong_feng_num->setEnabled(true);
		le_tangshu->setEnabled(true);
		cbox_material_type->setEnabled(true);

	}
	
	
	le_width->clear();
	le_height->clear();
	le_bottom_height->clear();
	le_zhong_feng_num->setText("0");
	le_tangshu->setText("1");
}
void mainWindow::calculate()
{

	
	
	if(check_state()== false ||comboBox->currentIndex() == 0)
	{
		QMessageBox::warning(this,tr("警告"),tr("数值不能为空值!\n"),tr("确定"));
			return;
	}
	

	zhong_feng_num=0;
	gai_ban=0;
	ping_shang_hua_num	=0;
	iwidth= le_width->text().toUInt();
	iheight = le_height->text().toUInt(); 
	tang_shu= le_tangshu->text().toUInt(); 
	gou_guang_qi_input = le_gou_guang_qi_constant->text().toUInt();  
	shang_xia_fang_input = le_shang_xia_fang_constant->text().toUInt();  

	bian_feng_hou = le_bian_feng_hou_du->text().toUInt();
	di_gao=le_bottom_height->text().toUInt();  
	shang_gu_hou = le_shang_gu_hou_du->text().toUInt();  
	zhong_feng_hou = le_zhong_feng_hou->text().toUInt();  
	zhong_feng_num = le_zhong_feng_num->text().toUInt();  
	zhong_zhu_hou = le_zhong_zhu_hou->text().toUInt();  

	shan_bo_gao_input = le_shan_bo_gao->text().toUInt();  
	shan_bo_kuan_input = le_shan_bo_kuan->text().toUInt(); 
	pao_mao = le_pao_mao->text().toUInt(); 
	gu_bo_kuan_input = le_gu_bo_kuan->text().toUInt(); 


	bian_feng = iheight;
	if(di_gao>iheight)
	{
		QMessageBox::warning(this,tr("警告"),tr("底高高于高度!\n"),tr("确定"));
			return;
	}
	

	switch(widTpye)
	{
		case 1:
		{
			di_gao = 0;
			zhong_zhu_num 		= 0;
			bian_feng_num		=2;
			gu_shang_hua_num	=zhong_zhu_num+1;
			shang_gu_num		=0;
			ping_shang_hua_num	=zhong_zhu_num+1;
			 gai_ban_num			=0;
			 gou_guang_qi_num	=2;
			gu_bo_num = 0;
			
			zhong_zhu = 0;
			gu_shang_hua = 0;
			shang_gu = 0;
			ping_shang_xia_hua =(iwidth-  (2*bian_feng_hou)-zhong_feng_num*zhong_feng_hou)/(zhong_feng_num+1);
			gai_ban = 0;
			zhong_feng = 0;
			gou_guang_qi = iheight-gou_guang_qi_input;
			if(cbox_operator->currentIndex() == 0)
				shang_xia_fang = (ping_shang_xia_hua/2)-shang_xia_fang_input;
			else
				shang_xia_fang = (ping_shang_xia_hua/2)+shang_xia_fang_input;

			gu_bo_gao = 0;
			gu_bo_kuan = 0;
			break;
		}

		case 2:
		{
			zhong_zhu = 0;
			zhong_zhu_num 		= 0;
			bian_feng_num		=2;
			gu_shang_hua_num	=1;
			shang_gu_num		=1;
			 gai_ban_num			=2;
			 gou_guang_qi_num	=2;
			 ping_shang_xia_hua 	= 0;
			gu_bo_num			=1;
			
			gu_shang_hua = iwidth-(2*bian_feng_hou);
			shang_gu = gu_shang_hua;

			if( ckbox_gaiban->isChecked())
				gai_ban = 0;
			else
				gai_ban = iheight-di_gao-shang_gu_hou-2;
			zhong_feng = 0;
			gou_guang_qi = di_gao-gou_guang_qi_input;
		//	shang_xia_fang = gu_shang_hua/2 + - shang_xia_fang_input;
			if(cbox_operator->currentIndex() == 0)
				shang_xia_fang = (gu_shang_hua/2)-shang_xia_fang_input;
			else
				shang_xia_fang = (gu_shang_hua/2)+shang_xia_fang_input;



			gu_bo_kuan = gu_shang_hua-gu_bo_kuan_input-pao_mao ;
			gu_bo_gao = iheight-di_gao-shang_gu_hou-pao_mao;
			break;
		}
		case 3:
		{
		
			zhong_zhu_num 		= 1;
			bian_feng_num		=2;
			gu_shang_hua_num	=1;
			shang_gu_num		=1;
			 gai_ban_num			=2;
			 gou_guang_qi_num	=2;
			 gu_bo_num			= 2;
			zhong_zhu = iheight - di_gao - shang_gu_hou;
			gu_shang_hua = iwidth-(2*bian_feng_hou);
			shang_gu = gu_shang_hua;
			ping_shang_xia_hua = 0;
			if( ckbox_gaiban->isChecked())
				gai_ban = 0;
			else
				gai_ban = zhong_zhu-2;
			zhong_feng = 0;
			gou_guang_qi = di_gao-gou_guang_qi_input;
			if(cbox_operator->currentIndex() == 0)
				shang_xia_fang = (gu_shang_hua/2)-shang_xia_fang_input;
			else
				shang_xia_fang = (gu_shang_hua/2)+shang_xia_fang_input;
			//shang_xia_fang = gu_shang_hua/2 + - shang_xia_fang_input;

			gu_bo_kuan = (gu_shang_hua-gu_bo_kuan_input-zhong_zhu_hou)/2-pao_mao ;
			gu_bo_gao = zhong_zhu-pao_mao;
			break;
		}

		case 4:
		{	
			zhong_zhu_num 		= 1;
			bian_feng_num		=2;
			gu_shang_hua_num	=1;
			shang_gu_num		=1;
			gai_ban_num			=2;
			gou_guang_qi_num	=4; 
			gu_bo_num			= 2;
			
			zhong_zhu =  iheight- di_gao - shang_gu_hou;
			gu_shang_hua = iwidth-(2*bian_feng_hou);
			shang_gu = gu_shang_hua;
			ping_shang_xia_hua = 0;

			if( ckbox_gaiban->isChecked())
				gai_ban = 0;
			else
				gai_ban = zhong_zhu-2;
			zhong_feng = 0;
			gou_guang_qi = di_gao-gou_guang_qi_input;
			if(cbox_operator->currentIndex() == 0)
				shang_xia_fang = (gu_shang_hua/4)-shang_xia_fang_input;
			else
				shang_xia_fang = (gu_shang_hua/4)+shang_xia_fang_input;
			//shang_xia_fang = gu_shang_hua/2 + - shang_xia_fang_input;
			gu_bo_kuan = (gu_shang_hua-gu_bo_kuan_input-zhong_zhu_hou)/2-pao_mao ;
			gu_bo_gao = zhong_zhu-pao_mao;
			break;
		}

		case 5:
		{	
			zhong_zhu = 0;
			zhong_zhu_num 		= 0;
			bian_feng_num		=2;
			gu_shang_hua_num	=zhong_feng_num+1;
			shang_gu_num		=zhong_feng_num+1;
			gai_ban_num			=2*zhong_feng_num+2;
			gou_guang_qi_num	=2*zhong_feng_num+2;
			gu_bo_num			= zhong_feng_num+1;
			gu_shang_hua =(unsigned int) ((iwidth-(2*bian_feng_hou)-zhong_feng_hou*zhong_feng_num)/(zhong_feng_num+1));
			shang_gu = gu_shang_hua;
			ping_shang_xia_hua = 0;
			if( ckbox_gaiban->isChecked())
				gai_ban = 0;
			else
				gai_ban = iheight-di_gao-shang_gu_hou-2;
			zhong_feng = iheight;
			gou_guang_qi = di_gao-gou_guang_qi_input;
			if(cbox_operator->currentIndex() == 0)
				shang_xia_fang = (gu_shang_hua/2)-shang_xia_fang_input;
			else
				shang_xia_fang = (gu_shang_hua/2)+shang_xia_fang_input;
			//shang_xia_fang =(unsigned int)( gu_shang_hua/2 +  shang_xia_fang_input);
			gu_bo_kuan = gu_shang_hua-gu_bo_kuan_input-pao_mao ;
			gu_bo_gao = iheight-di_gao-shang_gu_hou-pao_mao;
			break;
		}
		case 6:
		{			
			zhong_zhu_num 		= 3;
			bian_feng_num		=2;
			gu_shang_hua_num	=1;
			shang_gu_num		=1;
			gai_ban_num			=2;
			gou_guang_qi_num	=4;
			gu_bo_num 			=4;
			zhong_zhu = iheight - di_gao - shang_gu_hou;
			gu_shang_hua = iwidth-(2*bian_feng_hou);
			shang_gu = gu_shang_hua;
			ping_shang_xia_hua = 0;
			if( ckbox_gaiban->isChecked())
				gai_ban = 0;
			else
				gai_ban = zhong_zhu-2;
			zhong_feng = 0;
			gou_guang_qi = di_gao-gou_guang_qi_input;
			//shang_xia_fang =(unsigned int)( gu_shang_hua/2 +  shang_xia_fang_input);
			if(cbox_operator->currentIndex() == 0)  // -号
				shang_xia_fang = (gu_shang_hua/4)-shang_xia_fang_input;
			else
				shang_xia_fang = (gu_shang_hua/4)+shang_xia_fang_input;

			gu_bo_kuan = (gu_shang_hua-gu_bo_kuan_input-zhong_zhu_hou*zhong_zhu_num)/4-pao_mao ;
			gu_bo_gao = zhong_zhu-pao_mao;
			break;
		}

		case 7:
		{	
			
			zhong_zhu_num 		= zhong_feng_num+1;
			bian_feng_num		=2;
			gu_shang_hua_num	=zhong_feng_num+1;
			shang_gu_num		=zhong_feng_num+1;
			gai_ban_num			=2;
			gou_guang_qi_num	=zhong_feng_num*2+2;
			gu_bo_num			=(zhong_feng_num+1)*2;
				
			zhong_zhu = iheight - di_gao - shang_gu_hou;
			gu_shang_hua =(unsigned int)( (iwidth-(2*bian_feng_hou)-zhong_feng_hou*zhong_feng_num)/(zhong_feng_num+1));
			shang_gu = gu_shang_hua;
			ping_shang_xia_hua = 0;
			if( ckbox_gaiban->isChecked())
				gai_ban = 0;
			else
				gai_ban = zhong_zhu-2;
			zhong_feng = iheight;
			gou_guang_qi = di_gao-gou_guang_qi_input;
			//shang_xia_fang =(unsigned int)( gu_shang_hua/2 +  shang_xia_fang_input);
			if(cbox_operator->currentIndex() == 0)
				shang_xia_fang = (gu_shang_hua/2)-shang_xia_fang_input;
			else
				shang_xia_fang = (gu_shang_hua/2)+shang_xia_fang_input;
			gu_bo_kuan = (gu_shang_hua-gu_bo_kuan_input-zhong_zhu_hou)/2-pao_mao ;
			gu_bo_gao = zhong_zhu-pao_mao;
			break;
		}
	}


	shan_bo_gao= gou_guang_qi - shan_bo_gao_input;
	shan_bo_kuan = shang_xia_fang - shan_bo_kuan_input;

	QFont ft;	
	ft.setPointSize(8);
	int i = tableServerWidget->rowCount();
	tableServerWidget->insertRow(i);
	QTableWidgetItem *temp0 = new  QTableWidgetItem(QString::number(iwidth)+"x"+QString::number(iheight)+"\r\n"+QString::number(tang_shu)+tr("樘"));
	QTableWidgetItem *temp1 = new QTableWidgetItem(QString::number(di_gao));
	QTableWidgetItem *temp2 = new QTableWidgetItem(QString::number(zhong_zhu)+"\r\n"+QString::number(zhong_zhu_num*tang_shu)+tr("支"));
	QTableWidgetItem *temp3 = new QTableWidgetItem(QString::number(bian_feng)+"\r\n"+QString::number(bian_feng_num*tang_shu)+tr("支"));
	QTableWidgetItem *temp4 = new QTableWidgetItem(QString::number(gu_shang_hua)+"\r\n"+QString::number(gu_shang_hua_num*tang_shu)+tr("套"));
	QTableWidgetItem *temp5 = new QTableWidgetItem(QString::number(shang_gu)+"\r\n"+QString::number(shang_gu_num*tang_shu)+tr("支"));
	QTableWidgetItem *temp6 = new QTableWidgetItem(QString::number(ping_shang_xia_hua)+"\r\n"+QString::number(ping_shang_hua_num*tang_shu)+tr("套"));
	QTableWidgetItem *temp7 = new QTableWidgetItem;
	if( ckbox_gaiban->isChecked())
		temp7->setText(QString::number(gai_ban));
	else
		temp7->setText(QString::number(gai_ban)+"\r\n"+QString::number(gai_ban_num*tang_shu)+tr("支"));
	QTableWidgetItem *temp8 = new QTableWidgetItem(QString::number(zhong_feng)+"\r\n"+QString::number(zhong_feng_num*tang_shu)+tr("支"));
	QTableWidgetItem *temp9 = new QTableWidgetItem(QString::number(gou_guang_qi)+"x"+QString::number(shang_xia_fang)+"\r\n"+QString::number(gou_guang_qi_num*tang_shu)+tr("套"));

	//QTableWidgetItem *tempNum = new QTableWidgetItem();
	QTableWidgetItem *tempNum = new QTableWidgetItem(QString::number(i+1));
	QTableWidgetItem *temp11 = new QTableWidgetItem(QString::number(shan_bo_gao)+"x"+QString::number(shan_bo_kuan)+"\r\n"+QString::number(gou_guang_qi_num*tang_shu)+tr("块"));
	QTableWidgetItem *temp12 = new QTableWidgetItem(QString::number(gu_bo_gao)+"x"+QString::number(gu_bo_kuan)+"\r\n"+QString::number(gu_bo_num*tang_shu)+tr("块 "));
	temp0->setFont(ft);
	temp1->setFont(ft);
	temp2->setFont(ft);
	temp3->setFont(ft);
	temp4->setFont(ft);
	temp5->setFont(ft);
	temp6->setFont(ft);
	temp7->setFont(ft);
	temp8->setFont(ft);
	temp9->setFont(ft);
	tempNum->setFont(ft);
	temp11->setFont(ft);
	temp12->setFont(ft);
	tableServerWidget->setWordWrap(true);
	temp0->setTextAlignment(Qt::AlignVCenter  |Qt::AlignHCenter |Qt::TextWordWrap);
	temp1->setTextAlignment(Qt::AlignVCenter  |Qt::AlignHCenter |Qt::TextWordWrap);
	temp2->setTextAlignment(Qt::AlignVCenter  |Qt::AlignHCenter |Qt::TextWordWrap);
	temp3->setTextAlignment(Qt::AlignVCenter  |Qt::AlignHCenter |Qt::TextWordWrap);
	temp4->setTextAlignment(Qt::AlignVCenter  |Qt::AlignHCenter |Qt::TextWordWrap);
	temp5->setTextAlignment(Qt::AlignVCenter  |Qt::AlignHCenter |Qt::TextWordWrap);
	temp6->setTextAlignment(Qt::AlignVCenter  |Qt::AlignHCenter |Qt::TextWordWrap);
	temp7->setTextAlignment(Qt::AlignVCenter  |Qt::AlignHCenter |Qt::TextWordWrap);
	temp8->setTextAlignment(Qt::AlignVCenter  |Qt::AlignHCenter |Qt::TextWordWrap);
	temp9->setTextAlignment(Qt::AlignVCenter  |Qt::AlignHCenter |Qt::TextWordWrap);
	tempNum->setTextAlignment(Qt::AlignVCenter  |Qt::AlignHCenter |Qt::TextWordWrap);
	temp11->setTextAlignment(Qt::AlignVCenter  |Qt::AlignHCenter |Qt::TextWordWrap);
	temp12->setTextAlignment(Qt::AlignVCenter  |Qt::AlignHCenter |Qt::TextWordWrap);
	lb_pic = new QLabel(tableServerWidget);
	QString str ;
	str = QString::number(widTpye);
	str.append(".png");
	lb_pic->setWhatsThis(str);
	QPixmap pixmap(str);
	lb_pic->setScaledContents(true);
 	lb_pic->setPixmap(pixmap);
	tableServerWidget->setItem(i, 0, temp0);
	tableServerWidget->setCellWidget(i,1,lb_pic);
	tableServerWidget->setItem(i, 2, temp1);
	tableServerWidget->setItem(i, 3, temp2);
	tableServerWidget->setItem(i, 4, temp3);
	tableServerWidget->setItem(i, 5, temp4);
	tableServerWidget->setItem(i, 6, temp5);
	tableServerWidget->setItem(i, 7, temp6);
	tableServerWidget->setItem(i, 8, temp7);
	tableServerWidget->setItem(i, 9, temp8);	
	tableServerWidget->setItem(i, 10, temp9);
	tableServerWidget->setItem(i, 11, tempNum);
	tableServerWidget->setItem(i, 12, temp11);	
	tableServerWidget->setItem(i, 13, temp12);
	tableServerWidget->setWordWrap(true);

	window_area += iheight *iwidth*tang_shu;
	gu_bo_area +=(gu_bo_gao*gu_bo_kuan*gu_bo_num*tang_shu);
	shan_bo_area +=(shan_bo_gao*shan_bo_kuan*gou_guang_qi_num*tang_shu);
	lb_window_area->setText(QString::number(window_area/1000000.0, 'f', 4));
	lb_shan_bo_area->setText(QString::number((shan_bo_area+gu_bo_area)/1000000.0,'f',4));
	new_data_exist = true;

calculate_mode();
	
}


void mainWindow::save_to_file()
{


	int ret ;
	char sql[1024];
	char sqlform[256];
	if(tableServerWidget->rowCount() == 0)
			return;

	//没有新计算的数据
	if(new_data_exist== false)
		return ; 
	QDateTime dt;
	save_time = dt.currentDateTime().toTime_t();

	form.setFormId(save_time);
	if( form.exec() == QDialog::Rejected)
	{	
		return;
	}

	
	//如果前一次还有数据
	if(old_data_clean == false)
	{
		sprintf(sql,"delete from table_wind_data where log_time = %lu limit 100 order by log_time desc");
		pDb_ops->excute(sql);
		sprintf(sqlform,"delete from table_form_list where log_time = %lu  order by log_time desc");
		pDb_ops->excute(sqlform);
	}

	sprintf(sqlform,"insert into table_form_list(form_id,name,tel,information)  value(%d,'%s','%s','%s')"
					,save_time,form.leName->text().toAscii().data(),form.lePhone->text().toAscii().data(),form.lineEdit->text().toAscii().data());
	qDebug()<<sqlform;
	ret = pDb_ops->excute(sqlform);
	if(ret<0)
	{
		 QMessageBox::warning(this,tr("警告"),tr("保存文件失败，请重新保存!111111111111\n"),tr("确定"));
		return;
	}
	
	for(;tableServerWidget->rowCount()>0;)
	{												
		sprintf(sql,"insert into table_wind_data(windnum,kuanandgao,chuangti,digao,zhongzhu,bianfeng,gushangxiahua,shanggu,pingshangxiahua,gaiban,zhongfeng,gongguangqi,shanbo,gubo,log_time) value(%d,'%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s',%lu)" \
									,tableServerWidget->item(0,11)->text().toInt()
									,tableServerWidget->item(0,0)->text().toAscii().data()
									,tableServerWidget->cellWidget(0,1)->whatsThis().toAscii().data()
									,tableServerWidget->item(0,2)->text().toAscii().data()
									,tableServerWidget->item(0,3)->text().toAscii().data()
									,tableServerWidget->item(0,4)->text().toAscii().data()
									,tableServerWidget->item(0,5)->text().toAscii().data()
									,tableServerWidget->item(0,6)->text().toAscii().data()
									,tableServerWidget->item(0,7)->text().toAscii().data()
									,tableServerWidget->item(0,8)->text().toAscii().data()
									,tableServerWidget->item(0,9)->text().toAscii().data()
									,tableServerWidget->item(0,10)->text().toAscii().data()
									,tableServerWidget->item(0,12)->text().toAscii().data()
									,tableServerWidget->item(0,13)->text().toAscii().data()
									,save_time);
					
									
		
		ret = pDb_ops->excute(sql);
		
		if(ret >=0)
		{
				tableServerWidget->removeRow(0); 
				new_data_exist = false;
		}
		else
			 QMessageBox::warning(this,tr("警告"),tr("保存文件失败，请重新保存!2222222222\n"),tr("确定"));
	}


}

void mainWindow::del_resualt()
{
	

 QList<QTableWidgetSelectionRange>ranges=tableServerWidget->selectedRanges();
   int count=ranges.count();
    for(int i=0;i<count;i++)
    {

       int topRow=ranges.at(i).topRow();
       int bottomRow=ranges.at(i).bottomRow();
	   QString str1,str2,str3;
       for(int j=topRow;j<=bottomRow;j++)
       {
		
		   /*
			QString text = tableServerWidget->itemAt(0,0)->text();
			for(int i=0;i<text.length();i++)
			{
				if(text.at(i) == 'x')
				{
					str1 = text.left(i);
					
				}
				if(text.at(i) == '\r'|| text.at(i)=='\n' )
				str2 = text.mid(str1.length(),i-str1.length());
			}
			window_area -= str1.toInt()*str2.toInt();
			
			QString text1 = tableServerWidget->itemAt(0,12)->text();
			for(int i=0;i<text1.length();i++)
			{
				if(text.at(i) == 'x')
				{
					str1 = text1.left(i);
					
				}
				if(text1.at(i) == '\r'|| text1.at(i)=='\n' )
				str2 = text1.mid(str1.length(),i-str1.length());
			}
			shan_bo_area -= str1.toInt()*str2.toInt();

			QString text2 = tableServerWidget->itemAt(0,13)->text();
			for(int i=0;i<text2.length();i++)
			{
				if(text.at(i) == 'x')
				{
					str1 = text2.left(i);
					
				}
				if(text2.at(i) == '\r'|| text2.at(i)=='\n' )
				str2 = text2.mid(str1.length(),i-str1.length());
			}
			gu_bo_area -= str1.toInt()*str2.toInt();
			lb_window_area->setText(QString::number(window_area/1000000.0, 'f', 4));
			lb_shan_bo_area->setText(QString::number((shan_bo_area+gu_bo_area)/1000000.0,'f',4));
			*/

			tableServerWidget->removeRow(topRow); 
        }


	if(tableServerWidget->rowCount() == 0)
	{
		old_data_clean= true;
		lb_window_area->clear();
		lb_shan_bo_area->clear();
		return ;
	}
	else
		old_data_clean = false;

	  for(int i=0;i<tableServerWidget->rowCount();i++)
	  		tableServerWidget->item(i,11)->setText(QString::number(i+1));
		

}

	

}

void mainWindow::query_mode()
{
	QDateTime dt;
	
	unsigned int time ; 
	time  = dt.currentDateTime().toTime_t()-3600*24;
	
	init_ui();
	tableServerWidget->hide();
	gbQuery->show();
	dt.setTime_t(time);
	deStartTime->setDateTime(dt);
	
}
void mainWindow::query_history()
{

	char sql[512];
	void *result;
	char **row;
	int iRow=0;
	int form_num=0;
	unsigned int start,end;
	
	start = deStartTime->dateTime().toTime_t();
	end = deEndTime->dateTime().toTime_t()+3600*24;
	
	for(;formtableWidget->rowCount()>0;)
	{
		formtableWidget->removeRow(0); 
				
	}

	sprintf(sql,"select form_id,name,tel,information from table_form_list where form_id>=%lu and form_id <%lu order by form_id desc",start,end);
	qDebug()<<sql;
	result =  pDb_ops->getfirst(sql);
	while (result)
	{
		formtableWidget->insertRow(form_num);
		formtableWidget->setItem(form_num, 0, new QTableWidgetItem(deStartTime->dateTime().toString("yyyy.MM.dd")));
	
		row   = (char **)result;
		iRow  = 0;
		/*form_id*/
		if(row[iRow] == NULL)
			continue;
		formtableWidget->setItem(form_num, 1, new QTableWidgetItem(row[iRow]));
		iRow++;
		
		/*name*/
		if(row[iRow] == NULL)
			continue;
		formtableWidget->setItem(form_num, 2, new QTableWidgetItem(row[iRow]));
		iRow++;
		/*tel*/
		if(row[iRow] == NULL)
			continue;
		formtableWidget->setItem(form_num, 3, new QTableWidgetItem(row[iRow]));
		iRow++;

		/*information*/
		if(row[iRow] == NULL)
			continue;
		formtableWidget->setItem(form_num, 4, new QTableWidgetItem(row[iRow]));
		iRow++;
		form_num++;
		result =  pDb_ops->getnext();
	}

}

void mainWindow::query_data()
{

	char sql[512];
	void *result;
	char **row;
	int iRow=0;
	int form_num=0;
	unsigned int log_time;
	QString str= formtableWidget->item(formtableWidget->currentRow(),1)->text();
	le_width->setText(str);
	log_time=str.toUInt();


	for(;tableServerWidget->rowCount()>0;)
	{
		tableServerWidget->removeRow(0); 
				
	}
	tableServerWidget->show();
	sprintf(sql,"select kuanandgao,chuangti,digao,zhongzhu,bianfeng,gushangxiahua,shanggu,pingshangxiahua,gaiban,zhongfeng,gongguangqi,windnum,shanbo,gubo from table_wind_data where log_time =%lu order by windnum asc",log_time);
	qDebug()<<sql;
	result =  pDb_ops->getfirst(sql);
	while (result)
	{
		tableServerWidget->insertRow(form_num);		
		row   = (char **)result;
		iRow  = 0;
		/*windnum*/
		if(row[iRow] == NULL)
			continue;
		QTableWidgetItem *temp0 = new QTableWidgetItem(row[iRow]);
		tableServerWidget->setItem(form_num, 0, temp0);
		iRow++;
		
		/*kuanandgao*/
		if(row[iRow] == NULL)
			continue;

		lb_pic = new QLabel(tableServerWidget);
		lb_pic->setWhatsThis(row[iRow]);
		QPixmap pixmap(row[iRow]);
		lb_pic->setScaledContents(true);
	 	lb_pic->setPixmap(pixmap);

		tableServerWidget->setCellWidget(form_num,1,lb_pic);
		//tableServerWidget->setItem(form_num, 2, new QTableWidgetItem(row[iRow]));
		iRow++;
		/*chuangti*/
		if(row[iRow] == NULL)
			continue;
		QTableWidgetItem *temp2 = new QTableWidgetItem(row[iRow]);
		tableServerWidget->setItem(form_num, 2, temp2);
		iRow++;

		/*digao*/
		if(row[iRow] == NULL)
			continue;
		QTableWidgetItem *temp3 = new QTableWidgetItem(row[iRow]);
		tableServerWidget->setItem(form_num, 3, temp3);
		iRow++;


		/*zhongzhu*/
			if(row[iRow] == NULL)
				continue;
			QTableWidgetItem *temp4 = new QTableWidgetItem(row[iRow]);
			tableServerWidget->setItem(form_num, 4, temp4);
			iRow++;
			/*bianfeng*/
		if(row[iRow] == NULL)
			continue;
			QTableWidgetItem *temp5 = new QTableWidgetItem(row[iRow]);
		tableServerWidget->setItem(form_num, 5, temp5);
		iRow++;
			/*gushangxiahua*/
		if(row[iRow] == NULL)
			continue;
		QTableWidgetItem *temp6 = new QTableWidgetItem(row[iRow]);
		tableServerWidget->setItem(form_num, 6, temp6);
		iRow++;
			/*shanggu*/
		if(row[iRow] == NULL)
			continue;
		QTableWidgetItem *temp7 = new QTableWidgetItem(row[iRow]);
		tableServerWidget->setItem(form_num, 7, temp7);
		iRow++;
			/*pingshangxiahua*/
		if(row[iRow] == NULL)
			continue;
		QTableWidgetItem *temp8 = new QTableWidgetItem(row[iRow]);
		tableServerWidget->setItem(form_num, 8, temp8);
		iRow++;
			/*gaiban*/
		if(row[iRow] == NULL)
			continue;
		QTableWidgetItem *temp9 = new QTableWidgetItem(row[iRow]);
		tableServerWidget->setItem(form_num, 9, temp9);
		iRow++;
			/*zhongfeng*/
		if(row[iRow] == NULL)
			continue;
		QTableWidgetItem *temp10 = new QTableWidgetItem(row[iRow]);
		tableServerWidget->setItem(form_num, 10, temp10);
		iRow++;


		/*gongguangqi*/
		if(row[iRow] == NULL)
			continue;
		QTableWidgetItem *temp11 = new QTableWidgetItem(row[iRow]);
		tableServerWidget->setItem(form_num, 11, temp11);
		iRow++;
				/*shanbo*/
		if(row[iRow] == NULL)
			continue;
		QTableWidgetItem *temp12 = new QTableWidgetItem(row[iRow]);
		tableServerWidget->setItem(form_num, 12,temp12);
		iRow++;
				/*gubo*/
		if(row[iRow] == NULL)
			continue;
		QTableWidgetItem *temp13 = new QTableWidgetItem(row[iRow]);
		tableServerWidget->setItem(form_num, 13, temp13);
		iRow++;

	tableServerWidget->setWordWrap(true);
	temp0->setTextAlignment(Qt::AlignVCenter  |Qt::AlignHCenter |Qt::TextWordWrap);
	temp2->setTextAlignment(Qt::AlignVCenter  |Qt::AlignHCenter |Qt::TextWordWrap);
	temp3->setTextAlignment(Qt::AlignVCenter  |Qt::AlignHCenter |Qt::TextWordWrap);
	temp4->setTextAlignment(Qt::AlignVCenter  |Qt::AlignHCenter |Qt::TextWordWrap);
	temp5->setTextAlignment(Qt::AlignVCenter  |Qt::AlignHCenter |Qt::TextWordWrap);
	temp6->setTextAlignment(Qt::AlignVCenter  |Qt::AlignHCenter |Qt::TextWordWrap);
	temp7->setTextAlignment(Qt::AlignVCenter  |Qt::AlignHCenter |Qt::TextWordWrap);
	temp8->setTextAlignment(Qt::AlignVCenter  |Qt::AlignHCenter |Qt::TextWordWrap);
	temp9->setTextAlignment(Qt::AlignVCenter  |Qt::AlignHCenter |Qt::TextWordWrap);
	temp11->setTextAlignment(Qt::AlignVCenter  |Qt::AlignHCenter |Qt::TextWordWrap);
	temp12->setTextAlignment(Qt::AlignVCenter  |Qt::AlignHCenter |Qt::TextWordWrap);
	temp13->setTextAlignment(Qt::AlignVCenter  |Qt::AlignHCenter |Qt::TextWordWrap);
		form_num++;
		result =  pDb_ops->getnext();
	}

}



void mainWindow::query_data_clean()
{
	tableServerWidget->hide();
	

}




void mainWindow::print(QPrinter *printer)
{  

	if(tableServerWidget->isHidden())
		return;
#if 1
printer->setOrientation(QPrinter::Landscape); 
	QPrintDialog printDialog(printer, tableServerWidget);
	QPainter painter(printer);
	QPixmap image0;
	QSize size0;
	QFont fnt;
	
	QRect rectPage = painter.viewport();
	QDateTime datetime;
	QString time = datetime.currentDateTime().toString("yyyy.MM.dd-hh:mm");
	int itemRowNum = tableServerWidget->rowCount();
	int itemColumnNum = tableServerWidget->columnCount() ;
	int pagenum = itemRowNum/16;
	int pagewidth = rectPage.width();
	int pageheight= rectPage.height();



	int rectwidth=rectPage.width()/(itemColumnNum*2+2);
	int rectHeihgt =rectPage.height()/23 ;


	//QRect rectx(rectPage.x()+50,rectPage.y()+50,rectPage.width()-10,rectPage.height());
	//painter.setViewport(0, 0,rectx.width(), rectx.height());
	
 
for(int num=0;num<=pagenum;num++)
{


	if(num>0)
		printer->newPage();

	QRect rectx(rectPage.x()+50,rectPage.y()+50,rectPage.width()-50,rectPage.height()-50);
	painter.setViewport(0, 0,500, 500);

	painter.setWindow(rectPage.x(),rectPage.y(),pagewidth, pageheight);
	painter.setViewport(rectPage.x(),rectPage.y(),pagewidth, pageheight);
	painter.drawRect(0,1,rectPage.width()-1,rectPage.height());

//画表格
	for(int i = 4; i<=27;i++)
		painter.drawLine(0,i*rectHeihgt,rectPage.width(),i*rectHeihgt);
	for(int i = 0; i<=30;i++)
	{
		if(i ==0 ||i ==1 || i ==4 || i ==6 || i ==8 || i ==10 || i ==12 || i ==14 || i==17 || i ==20|| i ==24|| i == 27 || i ==30)
			painter.drawLine(i*rectwidth,6*rectHeihgt,i*rectwidth,rectPage.height());
	}


	painter.drawLine(15*rectwidth+rectwidth/2,6*rectHeihgt,15*rectwidth+rectwidth/2,rectPage.height() );
	painter.drawLine(18*rectwidth+rectwidth/2,6*rectHeihgt,18*rectwidth+rectwidth/2,rectPage.height());
	

	painter.drawLine(23*rectwidth+10,0,23*rectwidth+10,rectPage.height());
	painter.drawLine(23*rectwidth,0,23*rectwidth,rectPage.height());


	//主标题
	fnt.setPointSize(34);
	painter.setFont (fnt);
	painter.drawText(0*rectwidth,0,23*rectwidth,4*rectHeihgt,Qt::AlignVCenter  |Qt::AlignHCenter  , tittle,0);
	fnt.setPointSize(24);
	painter.setFont (fnt);
	painter.drawText(23*rectwidth,0,7*rectwidth,2*rectHeihgt,Qt::AlignVCenter  |Qt::AlignHCenter  , tittle,0);



	fnt.setPointSize(14);
	painter.setFont (fnt);
	painter.drawText(0,4*rectHeihgt,2*rectwidth,rectHeihgt,Qt::AlignVCenter  |Qt::AlignHCenter  , tr("客户:"),0); 
	painter.drawText(0,5*rectHeihgt,2*rectwidth,rectHeihgt,Qt::AlignVCenter  |Qt::AlignHCenter  , tr("面积:"),0); 
	//painter.drawText(0,6*rectHeihgt,rectwidth,rectHeihgt,Qt::AlignVCenter  |Qt::AlignHCenter  , tr("经销商:"),0); 

	painter.drawText(8*rectwidth,4*rectHeihgt,2*rectwidth,rectHeihgt,Qt::AlignVCenter  |Qt::AlignHCenter  , tr("电话:"),0); 
	painter.drawText(8*rectwidth,5*rectHeihgt,2*rectwidth,rectHeihgt,Qt::AlignVCenter  |Qt::AlignHCenter  , tr("重量:"),0); 
	//painter.drawText(4*rectwidth,6*rectHeihgt,rectwidth,rectHeihgt,Qt::AlignVCenter  |Qt::AlignHCenter  , tr("地址"),0); 

	painter.drawText(16*rectwidth,4*rectHeihgt,2*rectwidth,rectHeihgt,Qt::AlignVCenter  |Qt::AlignHCenter  , tr("型材:"),0); 
	painter.drawText(16*rectwidth,5*rectHeihgt,2*rectwidth,rectHeihgt,Qt::AlignVCenter  |Qt::AlignHCenter  , tr("日期:"),0); 
	painter.drawText(17*rectwidth,5*rectHeihgt,6*rectwidth,rectHeihgt,Qt::AlignVCenter  |Qt::AlignHCenter|Qt::TextWordWrap  , time,0); 


	//副标题
	painter.drawText(23*rectwidth,2*rectHeihgt,2*rectwidth,rectHeihgt,Qt::AlignVCenter  |Qt::AlignRight   , tr("面积:"),0); 
	painter.drawText(23*rectwidth,3*rectHeihgt,2*rectwidth,rectHeihgt,Qt::AlignVCenter  |Qt::AlignRight   , tr("重量:"),0);
	painter.drawText(23*rectwidth,4*rectHeihgt,2*rectwidth,rectHeihgt,Qt::AlignVCenter  |Qt::AlignRight  , tr("日期:"),0);
	painter.drawText(24*rectwidth+50,4*rectHeihgt,6*rectwidth,rectHeihgt,Qt::AlignVCenter  |Qt::AlignHCenter|Qt::TextWordWrap  , time,0);
	painter.drawText(23*rectwidth,5*rectHeihgt,2*rectwidth,rectHeihgt,Qt::AlignVCenter  |Qt::AlignRight  , tr("电话:"),0); 
	//painter.drawText(14*rectwidth,2*rectHeihgt,rectwidth,rectHeihgt,Qt::AlignVCenter  |Qt::AlignHCenter  , tr("面积:"),0); 	
	//painter.drawText(14*rectwidth,3*rectHeihgt,rectwidth,rectHeihgt,Qt::AlignVCenter  |Qt::AlignHCenter  , tr("日期:"),0); 



	//表头
	fnt.setPointSize(8);
	painter.setFont (fnt);

	painter.drawText(rectwidth,6*rectHeihgt,3*rectwidth,rectHeihgt,Qt::AlignVCenter  |Qt::AlignHCenter |Qt::TextWordWrap  ,tableServerWidget->horizontalHeaderItem(0)->text(),0);
	for(int i=3;i<7;i++)	
		painter.drawText(2*i*rectwidth,6*rectHeihgt,2*rectwidth,rectHeihgt,Qt::AlignVCenter  |Qt::AlignHCenter |Qt::TextWordWrap  ,tableServerWidget->horizontalHeaderItem(i-1)->text(),0);
	
	
	painter.drawText(14*rectwidth,6*rectHeihgt,rectwidth*3/2,rectHeihgt,Qt::AlignVCenter  |Qt::AlignHCenter |Qt::TextWordWrap  ,tableServerWidget->horizontalHeaderItem(6)->text(),0);
	painter.drawText(15*rectwidth+rectwidth/2,6*rectHeihgt,rectwidth*3/2,rectHeihgt,Qt::AlignVCenter  |Qt::AlignHCenter |Qt::TextWordWrap  ,tableServerWidget->horizontalHeaderItem(7)->text(),0);
	painter.drawText(17*rectwidth,6*rectHeihgt,rectwidth*3/2,rectHeihgt,Qt::AlignVCenter  |Qt::AlignHCenter |Qt::TextWordWrap  ,tableServerWidget->horizontalHeaderItem(8)->text(),0);
	painter.drawText(18*rectwidth+rectwidth/2,6*rectHeihgt,rectwidth*3/2,rectHeihgt,Qt::AlignVCenter  |Qt::AlignHCenter |Qt::TextWordWrap  ,tableServerWidget->horizontalHeaderItem(9)->text(),0);


	painter.drawText(20*rectwidth,6*rectHeihgt,3*rectwidth,rectHeihgt,Qt::AlignVCenter  |Qt::AlignHCenter |Qt::TextWordWrap  ,tableServerWidget->horizontalHeaderItem(10)->text(),0);
	painter.drawText(23*rectwidth,6*rectHeihgt,rectwidth,rectHeihgt,Qt::AlignVCenter  |Qt::AlignHCenter |Qt::TextWordWrap  ,tableServerWidget->horizontalHeaderItem(11)->text(),0);
	painter.drawText(24*rectwidth,6*rectHeihgt,3*rectwidth,rectHeihgt,Qt::AlignVCenter  |Qt::AlignHCenter |Qt::TextWordWrap  ,tableServerWidget->horizontalHeaderItem(12)->text(),0);
	painter.drawText(27*rectwidth,6*rectHeihgt,3*rectwidth,rectHeihgt,Qt::AlignVCenter  |Qt::AlignHCenter |Qt::TextWordWrap  ,tableServerWidget->horizontalHeaderItem(13)->text(),0);
	
	fnt.setPointSize(11);
	painter.setFont (fnt);

	
	for(int iItem=0;iItem<16;iItem++)
	{
		qDebug()<<"iItem :"<<iItem<<"    num:"<<num;
		if(16*num+iItem >=itemRowNum)
					break;
		painter.drawText(0,(iItem+7)*rectHeihgt,rectwidth,rectHeihgt,Qt::AlignVCenter  |Qt::AlignHCenter |Qt::TextWordWrap  ,QString::number(16*num+iItem+1));
		painter.drawText(rectwidth,(iItem+7)*rectHeihgt,3*rectwidth,rectHeihgt,Qt::AlignVCenter  |Qt::AlignHCenter |Qt::TextWordWrap  ,tableServerWidget->item(16*num+iItem,0)->text());
	for(int i=3;i<7;i++)	
		painter.drawText(2*i*rectwidth,(iItem+7)*rectHeihgt,2*rectwidth,rectHeihgt,Qt::AlignVCenter  |Qt::AlignHCenter |Qt::TextWordWrap  ,tableServerWidget->item(16*num+iItem,i-1)->text());
	
	painter.drawText(14*rectwidth,(iItem+7)*rectHeihgt,rectwidth+rectwidth/2,rectHeihgt,  Qt::AlignVCenter  |Qt::AlignHCenter |Qt::TextWordWrap  ,tableServerWidget->item(20*num+iItem,6)->text());
	painter.drawText(15*rectwidth+rectwidth/2,(iItem+7)*rectHeihgt,rectwidth+rectwidth/2,rectHeihgt,  Qt::AlignVCenter  |Qt::AlignHCenter |Qt::TextWordWrap  ,tableServerWidget->item(20*num+iItem,7)->text());
	painter.drawText(17*rectwidth,(iItem+7)*rectHeihgt,rectwidth*3/2,rectHeihgt,Qt::AlignVCenter  |Qt::AlignHCenter |Qt::TextWordWrap  ,tableServerWidget->item(16*num+iItem,8)->text());
	painter.drawText(18*rectwidth+rectwidth/2,(iItem+7)*rectHeihgt,rectwidth*3/2,rectHeihgt,  Qt::AlignVCenter  |Qt::AlignHCenter |Qt::TextWordWrap  ,tableServerWidget->item(16*num+iItem,9)->text());
	
	painter.drawText(20*rectwidth,(iItem+7)*rectHeihgt,3*rectwidth,rectHeihgt,Qt::AlignVCenter  |Qt::AlignHCenter |Qt::TextWordWrap  ,tableServerWidget->item(16*num+iItem,10)->text());
	painter.drawText(23*rectwidth,(iItem+7)*rectHeihgt,rectwidth,rectHeihgt,  Qt::AlignVCenter  |Qt::AlignHCenter |Qt::TextWordWrap  ,tableServerWidget->item(16*num+iItem,11)->text());
	painter.drawText(24*rectwidth,(iItem+7)*rectHeihgt,3*rectwidth,rectHeihgt,Qt::AlignVCenter  |Qt::AlignHCenter |Qt::TextWordWrap  ,tableServerWidget->item(16*num+iItem,12)->text());
	painter.drawText(27*rectwidth,(iItem+7)*rectHeihgt,3*rectwidth,rectHeihgt,Qt::AlignVCenter  |Qt::AlignHCenter |Qt::TextWordWrap  ,tableServerWidget->item(16*num+iItem,13)->text());
	
	
	}

	
	for(int iItem=0;iItem<16;iItem++)
	{
		
		if(16*num+iItem >=itemRowNum)
						break;
				QString winType = tableServerWidget->cellWidget(16*num+iItem,1)->whatsThis();
				QImage image(winType);
				QRect rectx(0,0,2*rectwidth,2*rectHeihgt);
				QSize size = image.size();
				size.scale(rectx.size(), Qt::KeepAspectRatio);     //此处保证图片显示完整
				painter.setViewport(rectPage.x()+4*rectwidth,rectPage.y()+(iItem+7)*rectHeihgt,2*rectwidth, rectHeihgt);
				painter.setWindow(image.rect());
				painter.drawImage(0,0,image);


		

	}
	
}


#endif


#if 0
	printer->setOrientation(QPrinter::Landscape); 
	QPrintDialog printDialog(printer, tableServerWidget);
	QPainter painter(printer);
	QPixmap image0;
	QSize size0;
	
	QFont fnt;
	QRect rect = painter.viewport();
	
	//QRect rect=printer->paperRect();

	int y_start = 0;
	int draw_xstart = 0;
	int draw_ystart = 0;
	int draw_xRightStart = 0;
//	int draw_yRightStart = 0;
//	int line_width = 0;
	
	int width=0;
//	int height = tableServerWidget->rowHeight(0);
	int tbl_contain_height = tableServerWidget->height()-tableServerWidget->horizontalHeader()->height() ;
	int tbl_verticalHeader_width =tableServerWidget->verticalHeader()->width() ;
	
	int page_width =rect.width()-50;
	int page_height = rect.height()-50;

	int rHeight = tbl_contain_height/20;
	int iItem = 0;
for(iItem=0;iItem<tableServerWidget->rowCount();iItem++)
{
	tableServerWidget->setRowHeight(iItem,rHeight);
}

int jlast = tableServerWidget->rowCount()%20;
if(jlast>0)
	for(int j = 0;j<20-jlast;j++)
	{
		tableServerWidget->insertRow(iItem);
		tableServerWidget->setRowHeight(iItem,rHeight);
		
	}



	draw_xstart=rect.x()+50;
	draw_ystart=rect.y()+50;
	for(int x=0;x<tableServerWidget->columnCount();x++)
	{
		
	 	width+= tableServerWidget->columnWidth(x);
	//	if(x<11)
		 
	//		line_width = width;
	}
width = width+tbl_verticalHeader_width;


painter.setViewport(draw_xstart,draw_ystart,page_width-10,page_height-10);

painter.drawRect(rect);
//painter.drawRect(draw_xstart,draw_ystart,page_width,page_height/4);
//painter.drawLine(draw_xstart,page_height/8,page_width,page_height/8);



QRect rect1(draw_xstart,draw_ystart,page_width/2,page_height/4);
//painter.drawRect(rect1);

//画主标头
fnt.setPointSize(34);
painter.setFont (fnt);
painter.drawText(draw_xstart,draw_ystart,page_width/2,page_height/7,Qt::AlignVCenter  |Qt::AlignHCenter  , tittle,0);
//画副标头
fnt.setPointSize(24);
painter.setFont (fnt);
draw_xRightStart =page_width-1000;
painter.drawText(draw_xRightStart,draw_ystart,page_width-draw_xRightStart,page_height/7,Qt::AlignVCenter  |Qt::AlignHCenter  , tittle,0);



fnt.setPointSize(13);
painter.setFont (fnt);
painter.drawText(draw_xstart,page_height/7, tr("型材:"));
painter.drawText(draw_xstart+page_width/4,page_height/7,  tr("客户:"));

painter.drawText(draw_xRightStart+200,page_height/7, tr("客户:"));



painter.drawText(draw_xstart,page_height/5,  tr("电话:"));
painter.drawText(draw_xstart+page_height/4,page_height/5,  tr("重量:"));
painter.drawText(draw_xstart+page_height/2,page_height/5,  tr("面积:"));
painter.drawText(draw_xRightStart+200,page_height/5,  tr("面积:"));
draw_ystart=page_height/5+50;

//画表格表头
	image0=image0.grabWidget(tableServerWidget,0,0,width,tableServerWidget->horizontalHeader()->height() );
	size0 = image0.size();

	size0.scale(rect.size(), Qt::KeepAspectRatio);     //此处保证图片显示完整

	painter.setViewport(80,draw_ystart,size0.width()-80, size0.height());
	painter.setWindow(image0.rect());

	painter.drawPixmap(0,0 ,image0);

	size0.scale(rect.size(), Qt::KeepAspectRatio);    
	painter.setWindow(rect);
	y_start = tableServerWidget->horizontalHeader()->height() ;
	draw_ystart =draw_ystart +size0.height() ;



	int page_num  =0;
	page_num = tableServerWidget->rowCount()/20 ;
	for(int t = 0;t<page_num;t++)
	{
		QPixmap image;
		if(t>0)
			printer->newPage();
		tableServerWidget->verticalScrollBar()->setValue((t)*20);
		image=image.grabWidget(tableServerWidget,0,y_start,width,tableServerWidget->height());
		QSize size = image.size();
		QRect rectx(rect.x()+50,rect.y()+50,rect.width()-50,rect.height()-draw_ystart);
		size.scale(rectx.size(), Qt::KeepAspectRatio);     //此处保证图片显示完整
		painter.setViewport(80, draw_ystart,rectx.width()-80, rectx.height());
		painter.setWindow(image.rect());
		painter.drawPixmap(0,0,image);
		
		draw_ystart = 0;

		qDebug()<<"*************** : t= "<<t;
	
	
	}

	if(jlast>0)
		for(int j = 0;j<20-jlast;j++)
			tableServerWidget->removeRow(iItem);
		

	tableServerWidget->verticalScrollBar()->setValue(0);

#endif
	
	
}





void mainWindow::print_view()
{
	if(tableServerWidget->isHidden())
		return;

 QPrinter printer(QPrinter::HighResolution);
    QPrintPreviewDialog preview(&printer,this);
	preview.resize(800,500);
  connect(&preview, SIGNAL(paintRequested(QPrinter *)),this,SLOT(print(QPrinter *)));
//	preview.exec();

	if (preview.exec() == QDialog::Accepted)
	{
		  
	}
	/*
	  if (printDialog.exec() == QDialog::Accepted)
    {
    	QPainter painter(&printer);           
    	QPixmap image;
		image=image.grabWidget(tableServerWidget,0,0,-1,-1);
    	QRect rect = painter.viewport();
    	QSize size = image.size();
    	size.scale(rect.size()/2, Qt::KeepAspectRatio);     //此处保证图片显示完整
    	painter.setViewport(rect.x()+5, rect.y()+50,size.width(), size.height());
    	painter.setWindow(image.rect());
    	painter.drawPixmap(0,0,image);
    }

    QMessageBox msgBox;
    msgBox.setText(tr("请选择打印方式"));
    msgBox.addButton(tr("输出到文档"),QMessageBox::AcceptRole);
    msgBox.addButton(tr("输出到打印机"),QMessageBox::RejectRole);
    if(msgBox.exec()==QMessageBox::AcceptRole)
        printer.setOutputFormat(QPrinter::PdfFormat);
    preview.exec();
	*/
}
mainWindow::~mainWindow()
{
	
	




}


