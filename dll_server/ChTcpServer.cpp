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

// ��������
bool ChTcpServer::startListen()
{
	qInfo() << "server listening...";
	return m_pServer->listen(QHostAddress::Any, m_iPort);
}

// ��ʼ������
void ChTcpServer::initServer()
{
	m_pServer = new QTcpServer(this);
	m_iPort = gChGlobalPara->getServerPort();
}

// �źŲ�����
void ChTcpServer::createConnection()
{
	connect(m_pServer, &QTcpServer::newConnection, this, &ChTcpServer::slotNewConnection);
}

// �ͷ�
void ChTcpServer::freeMem()
{
	
}

// ������
void ChTcpServer::slotNewConnection()
{
	//Ϊ���ӽ����Ŀͻ��˴����µ��׽���
	QTcpSocket* pSocket = m_pServer->nextPendingConnection();
	ChClientSocket* pClientSocket = new ChClientSocket(pSocket);
}
