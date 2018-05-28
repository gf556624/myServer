#include "ChSendManager.h"
#include "ChDefine.h"
#include <QMutex>

static QMutex g_mutex;
ChSendManager::CGarbo ChSendManager::m_Garbo;
ChSendManager* ChSendManager::m_pInstance = nullptr;
ChSendManager* ChSendManager::instance()
{
	if (!m_pInstance)
	{
		g_mutex.lock();
		if (!m_pInstance)
		{
			m_pInstance = new ChSendManager();
		}
		g_mutex.unlock();
	}

	return m_pInstance;
}

// 发送消息
void ChSendManager::sendMessage(QTcpSocket* pSocket, const ChPakageType& pakageType, const QString& strMsg /*= QString()*/)
{
	ChPakage oSendPakage = sendPakage(pakageType, strMsg);
	pSocket->write((char*)&oSendPakage, sizeof(ChPakage));
}

// 组包
ChPakage ChSendManager::sendPakage(const ChPakageType& pakageType, const QString& strMsg /*= QString()*/)
{
	ChPakage oPakage;
	oPakage.m_type = pakageType;
	strcpy(oPakage.m_Msg, strMsg.toUtf8().data());

	return oPakage;
}

ChSendManager::ChSendManager()
{

}


ChSendManager::~ChSendManager()
{

}
