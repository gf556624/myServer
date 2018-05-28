#include "ChClientSocket.h"
#include "ChDefine.h"
#include "ChSendManager.h"

#include <QtGlobal>
#include <QDataStream>

ChClientSocket::ChClientSocket(QTcpSocket* socket, QObject *parent /*= 0*/)
	: m_pSocket(socket)
	, QObject(parent)
{
	init();
	createConnection();
	slotConnected();

	// 开始监听文件传输
	createFileServer();
}

ChClientSocket::~ChClientSocket()
{
	disConnection();
	if (m_pSocket)
	{
		m_pSocket->close();
		m_pSocket->deleteLater();
		m_pSocket = nullptr;
	}
}

// 初始化
void ChClientSocket::init()
{
	m_pUpdateObj = new ChUpdateObject();
}

// 信号槽连接
void ChClientSocket::createConnection()
{
	if (m_pSocket)
	{
		connect(m_pSocket, &QTcpSocket::readyRead, this, &ChClientSocket::slotReadyRead);
		connect(m_pSocket, &QTcpSocket::disconnected, this, &ChClientSocket::deleteLater);
	}

	if (m_pUpdateObj)
	{
		connect(m_pUpdateObj, &ChUpdateObject::sigUpdateMsg, this, &ChClientSocket::slotUpdateMsg);
	}
}

// 断开信号槽
void ChClientSocket::disConnection()
{
	if (m_pSocket)
	{
		disconnect(m_pSocket, &QTcpSocket::readyRead, this, &ChClientSocket::slotReadyRead);
		disconnect(m_pSocket, &QTcpSocket::disconnected, this, &ChClientSocket::deleteLater);
	}

	if (m_pUpdateObj)
	{
		disconnect(m_pUpdateObj, &ChUpdateObject::sigUpdateMsg, this, &ChClientSocket::slotUpdateMsg);
	}
}

// 校验升级固件
void ChClientSocket::checkUpdateDev()
{
	// 文件接收完成
	if (!m_pUpdateObj->checkDevVersion())
	{
		// 版本不匹配 开始升级固件
		m_pUpdateObj->slotExec();
	}
	else
	{	// 重启
		gChSendManager->sendMessage(m_pSocket, PAKAGE_RESTART);
	}
}

// 初始化文件接收
void ChClientSocket::createFileServer()
{
	m_pFileServer = new ChFileServer(m_pSocket, this);
	
	// 启动监听
	bool bRes = m_pFileServer->startListen();
	qDebug() << "file server listening...";
	if (!bRes)
	{
		qCritical("m_pFileServer listen error");
	}

	// 开始监听 告诉client 建立文件传输链接
	gChSendManager->sendMessage(m_pSocket, PAKAGE_UPDATE);
}

// 读取
void ChClientSocket::slotReadyRead()
{
	qDebug() << "read msg";
	
	// 循环接收 一次接收到多个包，以防没有读取完毕，造成丢包
	while (m_pSocket->bytesAvailable() > 0)
	{
		ChPakage oRecvPakage;
		m_pSocket->read((char*)&oRecvPakage, sizeof(ChPakage));
		switch (oRecvPakage.m_type)
		{
		case PAKAGE_UPDATE:	// 升级 传输文件
		{
			qDebug() << "update msg = " << oRecvPakage.m_Msg;
		}
		break;
		case PAKAGE_MESSAGE:	// 消息
		{
			qDebug() << "return message = " << oRecvPakage.m_Msg;
		}
		break;
		case PAKAGE_FILE_SEND_END:	// 发送完成
		{
			qDebug() << "client send files end";
			// 校验升级固件
			checkUpdateDev();
		}
		break;
		case PAKAGE_FILE_RECV_END:	// 接收完成
		{
			qDebug() << "recv file end";
		}
		break;
		case PAKAGE_RESTART:	// 重启
		{
			qDebug() << "restart";
			m_pUpdateObj->restartCamera();
		}
		break;
		default:
			break;
		}
	}
}

// 发送相机信息
void ChClientSocket::slotConnected()
{
	if (m_pSocket && m_pUpdateObj)
	{
		// 返回相机信息
		QString strDevInfo = m_pUpdateObj->getCurrentDevInfo();
		gChSendManager->sendMessage(m_pSocket, PAKAGE_MESSAGE, strDevInfo);

		// 校验版本
		QString strMsg("");
		if (m_pUpdateObj->checkDevVersion())
		{
			// 版本匹配
			strMsg = QStringLiteral("固件版本匹配，请选择相应的升级文件进行升级");
		}
		else
		{
			strMsg = QStringLiteral("固件版本不匹配，请选择匹配的固件文件和相应的升级文件进行升级");
		}
		gChSendManager->sendMessage(m_pSocket, PAKAGE_MESSAGE, strMsg);
	}
}

// 更新信息
void ChClientSocket::slotUpdateMsg(const QString& strMsg)
{
	qInfo() << strMsg;
	if ("WM_MSG_UPDATE_FINISH" == strMsg)	// 固件升级完成
	{
		// 升级完成 重启相机
		gChSendManager->sendMessage(m_pSocket, PAKAGE_RESTART);
	}
	else
	{
		// 返回升级过程中的信息
		gChSendManager->sendMessage(m_pSocket, PAKAGE_MESSAGE, strMsg);
	}
}
