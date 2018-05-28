#include <QtWidgets/QApplication>
#include "ChTcpServer.h"
#include "ChLog.h"
#include <QProcess>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	// 日志初始化
	gChLog->init();
	
	// 关闭K盘
	bool bRes = QProcess::startDetached("mtUninit.exe");
	if (!bRes)
	{
		qCritical() << QStringLiteral("关闭K盘失败");
	}
	else
	{
		qInfo() << QStringLiteral("关闭K盘成功");
	}

	// 启动服务监听
	ChTcpServer sever;
	sever.startListen();

	return a.exec();
}
