#include "ChTcpServer.h"
#include "ChClientSocket.h"
#include "ChGlobalPara.h"
//#include <QThread>

ChTcpServer::ChTcpServer(QObject *parent/* = 0*/)
	: QObject(parent)
{
	initServer();
	createConnection();
}


ChTcpServer::~ChTcpServer()
{
	freeMem();
}

// 启动监听
bool ChTcpServer::startListen()
{
	qInfo() << "server listening...";
	return m_pServer->listen(QHostAddress::Any, m_iPort);
}

// 初始化服务
void ChTcpServer::initServer()
{
	m_pServer = new QTcpServer(this);
	m_iPort = gChGlobalPara->getServerPort();
}

// 信号槽连接
void ChTcpServer::createConnection()
{
	connect(m_pServer, &QTcpServer::newConnection, this, &ChTcpServer::slotNewConnection);
}

// 释放
void ChTcpServer::freeMem()
{
	
}

// 新连接
void ChTcpServer::slotNewConnection()
{
	//为连接进来的客户端创建新的套接字
	QTcpSocket* pSocket = m_pServer->nextPendingConnection();
	ChClientSocket* pClientSocket = new ChClientSocket(pSocket);
}
