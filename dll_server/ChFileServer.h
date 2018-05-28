/**
*
* File Name : ChFileServer.h
*
* Description : �ļ�server
*
* Author : GuoFeng
*
* Create Date : 2018-05-07 14:50
*
* Update Date : 2018-05-07 14:50
*
* Version : 1.0
*
**/

#pragma once

#include <QObject>
#include <QFile>

QT_BEGIN_NAMESPACE
class QTcpServer;
class QTcpSocket;
QT_END_NAMESPACE

class ChFileServer : public QObject
{
	Q_OBJECT

public:
	explicit ChFileServer(QTcpSocket* pSocket, QObject *parent = 0);
	~ChFileServer();
	
	void setPort(const int& iPort) { m_iPort = iPort; }
	bool startListen();

private:
	void initServer();
	void createConnection();
	void freeMem();

	// ����
	void resetMember();

private slots:
	// ������
	void slotNewConnection();

	// �����ļ�
	void slotFileReadyRead();

private:
	int m_iPort{-1};						// �����Ķ˿ں�
	QTcpServer* m_pFileServer{ nullptr };	// file server
	QTcpSocket* m_pSocket{ nullptr };		// client socket
	QTcpSocket* m_pFileSocket{ nullptr };	// file socket

	qint64 m_totalSize{ 0 };	// �����ܴ�С
	qint64 m_recvedSize{ 0 };	// �ѽ��յĴ�С
	QFile m_file;				// ���յ��ļ�
	QByteArray m_recvBlock;		// ���յ����ݻ�����
	qint64 m_fileNameSize{ 0 };	// �ļ�����С
	QString m_strFileName{ "" };	// �ļ���
};

