/**
*
* File Name : ChClientSocket.h
*
* Description :	连接到服务的socket
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

	// 信号槽
	void createConnection();
	void disConnection();

	// 校验升级固件
	void checkUpdateDev();

	// 初始化文件接收
	void createFileServer();

signals:
	void sigDisconnect();

public slots:
	void slotReadyRead();//读取客户端消息槽函数
	void slotConnected();

	// 更新信息
	void slotUpdateMsg(const QString& strMsg);

private:
	QTcpSocket* m_pSocket{nullptr};		// 链接的client

	ChUpdateObject* m_pUpdateObj{ nullptr };	// 相机更新
	ChFileServer* m_pFileServer{nullptr};	// 传输文件的server
};