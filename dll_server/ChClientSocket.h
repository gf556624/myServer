/**
*
* File Name : ChClientSocket.h
*
* Description :	���ӵ������socket
*
* Author :	GuoFeng
*
* Create Date : 2018-05-07
*
* Update Date : 2018-05-07
*
* Version : 1.0
*
**/
#pragma once

#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>
#include <QFile>
#include "ChUpdateObject.h"
#include "ChPakage.h"
#include "ChFileServer.h"

class ChClientSocket : public QObject
{
	Q_OBJECT

public:
	explicit ChClientSocket(QTcpSocket* socket, QObject *parent = 0);
	~ChClientSocket();

private:
	void init();

	// �źŲ�
	void createConnection();
	void disConnection();

	// У�������̼�
	void checkUpdateDev();

	// ��ʼ���ļ�����
	void createFileServer();

signals:
	void sigDisconnect();

public slots:
	void slotReadyRead();//��ȡ�ͻ�����Ϣ�ۺ���
	void slotConnected();

	// ������Ϣ
	void slotUpdateMsg(const QString& strMsg);

private:
	QTcpSocket* m_pSocket{nullptr};		// ���ӵ�client

	ChUpdateObject* m_pUpdateObj{ nullptr };	// �������
	ChFileServer* m_pFileServer{nullptr};	// �����ļ���server
};