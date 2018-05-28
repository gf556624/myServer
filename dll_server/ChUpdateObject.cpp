/**
*
* File Name : ChUpdateObject.cpp
*
* Description : 相机升级固件对话框 实现固件升级功能 函数实现
*
* Author : GuoFeng
*
* Create Date : 2018-05-02 10:00:00
*
* Update Date : 2018-05-02 10:00:00
*
* Version : 1.0
*
**/
#include "ChUpdateObject.h"
#include <windows.h>
#include "ChameleonRemoteUpdate.h"

#include <atlconv.h>
#include <QThread>
#include <QtGlobal>
#include <QDebug>

ChUpdateObject::ChUpdateObject(QWidget *parent, Qt::WindowFlags f)
	: QWidget(parent, f)
{
	qInfo() << "Init...";
	initMember();
	createConnections();
}

ChUpdateObject::~ChUpdateObject()
{
	m_pThread->quit();
	m_pThread->wait();
	if (m_pThread)
	{
		m_pThread->deleteLater();
		m_pThread = nullptr;
	}
}

QString ChUpdateObject::getCurrentDevInfo() const
{
	return m_pRoseekObj->getCurrentDevInfo();
}

// 校验固件版本
bool ChUpdateObject::checkDevVersion() const
{
	if (m_pRoseekObj)
	{
		return m_pRoseekObj->checkVersion();
	}

	return false;
}

// 重启相机
void ChUpdateObject::restartCamera()
{
	qInfo() << QStringLiteral("重启相机...");
	m_pRoseekObj->restartCamera();
}

bool ChUpdateObject::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
	MSG* msg = (MSG*)message;
	if (msg)
	{
		WPARAM wParam = msg->wParam;
		//LPARAM lParam = msg->lParam;
		switch (msg->message)
		{
		case WM_MSG_UPDATE_MESSAGEOUT:
		{
			QString strTmp;
			strTmp = QString::fromWCharArray((TCHAR*)wParam);
			qDebug() << "WM_MSG_UPDATE_MESSAGEOUT==>" << strTmp;
			//ui.textBrowserMsg->append(strTmp);
			emit sigUpdateMsg(strTmp);
		}
		break;
		case WM_MSG_UPDATE_FINISH:
		{
			qDebug() << "WM_MSG_UPDATE_FINISH";
			emit sigUpdateMsg(QStringLiteral("WM_MSG_UPDATE_FINISH"));
			//ui.btnExec->setEnabled(true);
			// 固件更新完成 线程退出
			m_bUpdateSuccess = true;
			m_pThread->quit();
		}
		break;
		default:
			break;
		}
	}

	return QWidget::nativeEvent(eventType, message, result);
}

// 初始化程序 变量 
void ChUpdateObject::initMember()
{
	m_pRoseekObj = new ChRoseekObject();
	m_pThread = new QThread();
	m_pRoseekObj->moveToThread(m_pThread);
}

void ChUpdateObject::createConnections()
{
	connect(m_pThread, &QThread::started, m_pRoseekObj, &ChRoseekObject::execUpdate);
	connect(m_pRoseekObj, &ChRoseekObject::sigUpdateFailed, m_pThread, &QThread::quit);
	connect(m_pThread, &QThread::finished, m_pRoseekObj, &ChRoseekObject::deleteLater);
	connect(m_pRoseekObj, &ChRoseekObject::sigUpdateFailed, this, &ChUpdateObject::slotUpdateInfo);
}

// 执行
void ChUpdateObject::slotExec()
{
	// 版本不匹配固件升级
	if (!m_pRoseekObj->checkVersion())
	{
		m_pRoseekObj->setHwnd((HWND)this->winId());
		m_pThread->start();
	}
}



// 更新信息
void ChUpdateObject::slotUpdateInfo(const QString& msg)
{
	m_bUpdateSuccess = false;
	emit sigUpdateMsg(msg);
}