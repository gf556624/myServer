#include <QtWidgets/QApplication>
#include "ChTcpServer.h"
#include "ChLog.h"
#include <QProcess>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	// ��־��ʼ��
	gChLog->init();
	
	// �ر�K��
	bool bRes = QProcess::startDetached("mtUninit.exe");
	if (!bRes)
	{
		qCritical() << QStringLiteral("�ر�K��ʧ��");
	}
	else
	{
		qInfo() << QStringLiteral("�ر�K�̳ɹ�");
	}

	// �����������
	ChTcpServer sever;
	sever.startListen();

	return a.exec();
}
