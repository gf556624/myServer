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

	// ��ʼ�����ļ�����
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

// ��ʼ��
void ChClientSocket::init()
{
	m_pUpdateObj = new ChUpdateObject();
}

// �źŲ�����
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

// �Ͽ��źŲ�
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

// У�������̼�
void ChClientSocket::checkUpdateDev()
{
	// �ļ��������
	if (!m_pUpdateObj->checkDevVersion())
	{
		// �汾��ƥ�� ��ʼ�����̼�
		m_pUpdateObj->slotExec();
	}
	else
	{	// ����
		gChSendManager->sendMessage(m_pSocket, PAKAGE_RESTART);
	}
}

// ��ʼ���ļ�����
void ChClientSocket::createFileServer()
{
	m_pFileServer = new ChFileServer(m_pSocket, this);
	
	// ��������
	bool bRes = m_pFileServer->startListen();
	qDebug() << "file server listening...";
	if (!bRes)
	{
		qCritical("m_pFileServer listen error");
	}

	// ��ʼ���� ����client �����ļ���������
	gChSendManager->sendMessage(m_pSocket, PAKAGE_UPDATE);
}

// ��ȡ
void ChClientSocket::slotReadyRead()
{
	qDebug() << "read msg";
	
	// ѭ������ һ�ν��յ���������Է�û�ж�ȡ��ϣ���ɶ���
	while (m_pSocket->bytesAvailable() > 0)
	{
		ChPakage oRecvPakage;
		m_pSocket->read((char*)&oRecvPakage, sizeof(ChPakage));
		switch (oRecvPakage.m_type)
		{
		case PAKAGE_UPDATE:	// ���� �����ļ�
		{
			qDebug() << "update msg = " << oRecvPakage.m_Msg;
		}
		break;
		case PAKAGE_MESSAGE:	// ��Ϣ
		{
			qDebug() << "return message = " << oRecvPakage.m_Msg;
		}
		break;
		case PAKAGE_FILE_SEND_END:	// �������
		{
			qDebug() << "client send files end";
			// У�������̼�
			checkUpdateDev();
		}
		break;
		case PAKAGE_FILE_RECV_END:	// �������
		{
			qDebug() << "recv file end";
		}
		break;
		case PAKAGE_RESTART:	// ����
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

// ���������Ϣ
void ChClientSocket::slotConnected()
{
	if (m_pSocket && m_pUpdateObj)
	{
		// ���������Ϣ
		QString strDevInfo = m_pUpdateObj->getCurrentDevInfo();
		gChSendManager->sendMessage(m_pSocket, PAKAGE_MESSAGE, strDevInfo);

		// У��汾
		QString strMsg("");
		if (m_pUpdateObj->checkDevVersion())
		{
			// �汾ƥ��
			strMsg = QStringLiteral("�̼��汾ƥ�䣬��ѡ����Ӧ�������ļ���������");
		}
		else
		{
			strMsg = QStringLiteral("�̼��汾��ƥ�䣬��ѡ��ƥ��Ĺ̼��ļ�����Ӧ�������ļ���������");
		}
		gChSendManager->sendMessage(m_pSocket, PAKAGE_MESSAGE, strMsg);
	}
}

// ������Ϣ
void ChClientSocket::slotUpdateMsg(const QString& strMsg)
{
	qInfo() << strMsg;
	if ("WM_MSG_UPDATE_FINISH" == strMsg)	// �̼��������
	{
		// ������� �������
		gChSendManager->sendMessage(m_pSocket, PAKAGE_RESTART);
	}
	else
	{
		// �������������е���Ϣ
		gChSendManager->sendMessage(m_pSocket, PAKAGE_MESSAGE, strMsg);
	}
}
