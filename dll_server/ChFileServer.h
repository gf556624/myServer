/**
*
* File Name : ChFileServer.h
*
* Description : 文件server
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

	// 重置
	void resetMember();

private slots:
	// 新连接
	void slotNewConnection();

	// 接收文件
	void slotFileReadyRead();

private:
	int m_iPort{-1};						// 监听的端口号
	QTcpServer* m_pFileServer{ nullptr };	// file server
	QTcpSocket* m_pSocket{ nullptr };		// client socket
	QTcpSocket* m_pFileSocket{ nullptr };	// file socket

	qint64 m_totalSize{ 0 };	// 接收总大小
	qint64 m_recvedSize{ 0 };	// 已接收的大小
	QFile m_file;				// 接收的文件
	QByteArray m_recvBlock;		// 接收的数据缓存区
	qint64 m_fileNameSize{ 0 };	// 文件名大小
	QString m_strFileName{ "" };	// 文件名
};

