/**
*
* File Name :
*
* Description :
*
* Author :
*
* Create Date :
*
* Update Date :
*
* Version : 1.0
*
**/

#pragma once

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
class ChClientSocket;
QT_END_NAMESPACE

class ChTcpServer : public QObject
{
	Q_OBJECT

public:
	ChTcpServer(QObject *parent = 0);
	~ChTcpServer();
	
	void setPort(const int& iPort) { m_iPort = iPort; }
	bool startListen();

private:
	void initServer();
	void createConnection();
	void freeMem();

private slots:
	void slotNewConnection();

private:
	int m_iPort{-1};	// ¼àÌýµÄ¶Ë¿ÚºÅ
	QTcpServer* m_pServer{ nullptr };
};

