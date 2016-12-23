
#include <QtGui/QApplication>
#include <QtCore/QTextCodec>
#include <QStyleFactory>
#include "mainWindow.h"

int main(int argc, char *argv[])
{
	  QApplication app(argc, argv);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB18030"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("GB18030"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GB18030"));
	 QApplication::setStyle("windowsxp");

	mainWindow MD;


	MD.show();
	   return app.exec();

}
