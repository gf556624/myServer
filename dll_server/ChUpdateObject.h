/**
*
* File Name : ChUpdateObject.h
*
* Description : 相机升级固件对话框 实现固件升级功能
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

#pragma once

#include <QtWidgets/QWidget>
#include "ChRoseekObject.h"

QT_BEGIN_NAMESPACE
class QThread;
QT_END_NAMESPACE

class ChUpdateObject : public QWidget
{
	Q_OBJECT

public:
	ChUpdateObject(QWidget *parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
	~ChUpdateObject();

	QString getCurrentDevInfo() const;

	// 校验版本
	bool checkDevVersion() const;

	// 重启相机
	void restartCamera();

protected:
	virtual bool nativeEvent(const QByteArray &eventType, void *message, long *result);

private:
	void initMember();
	void createConnections();

signals:
	void sigUpdateMsg(const QString& msg);

public slots:
	void slotExec();
	// 更新信息
	void slotUpdateInfo(const QString& msg);

private:
	void* m_pNetCmd{ nullptr };
	ChRoseekObject* m_pRoseekObj{ nullptr };
	QThread* m_pThread{nullptr};
	bool m_bUpdateSuccess{true};	// 固件更新是否成功
};
