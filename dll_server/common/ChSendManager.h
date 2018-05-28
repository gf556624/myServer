/**
*
* File Name : ChSendManager.h
*
* Description : 发送消息管理
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

#ifndef _CH_SEND_MANAGER_H
#define  _CH_SEND_MANAGER_H

#include <QTcpSocket>
#include "ChPakage.h"
#include <QString>

class ChSendManager
{
public:
	~ChSendManager();
	static ChSendManager* instance();

	// 发送消息
	void sendMessage(QTcpSocket* pSocket, const ChPakageType& pakageType, const QString& strMsg = QString());

	// 组包 发送的消息
	ChPakage sendPakage(const ChPakageType& pakageType, const QString& strMsg = QString());

private:
	explicit ChSendManager();
	ChSendManager(const ChSendManager& obj);
	ChSendManager& operator=(const ChSendManager& obj);

	// 单例内存回收类
	class CGarbo
	{
	public:
		CGarbo() {}
		~CGarbo()
		{
			if (ChSendManager::m_pInstance)
			{
				delete ChSendManager::m_pInstance;
				ChSendManager::m_pInstance = nullptr;
			}
		}
	};
	static CGarbo m_Garbo;

private:
	static ChSendManager* m_pInstance;
};

#ifndef gChSendManager
#define gChSendManager ChSendManager::instance()
#endif

#endif