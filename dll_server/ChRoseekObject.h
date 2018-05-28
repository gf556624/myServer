/**
*
* File Name : ChRoseekObject.h
*
* Description : 相机执行升级线程 函数声明
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

#include <QObject>
#include <windows.h>

class ChRoseekObject : public QObject
{
	Q_OBJECT

public:
	ChRoseekObject(QObject *parent = Q_NULLPTR);
	~ChRoseekObject();

	QString getDevInfo() const { return m_strDevInfo; }
	QString getCurrentDevInfo() const { return m_strCurrentInfo; }

	// 设置/获取选择的升级文件
	QString getUpdateFile() const { return m_strFile; }
	void setUpdateFile(const QString& strFile) { m_strFile = strFile; }

	// 窗口句柄
	void setHwnd(HWND hWnd) { m_hWnd = hWnd; }

	// 校验版本
	bool checkVersion();
	// 获取版本
	QString getVersion(const QString& str) const;

	// 重启相机
	bool restartCamera();

signals:
	void sigUpdateFailed(const QString& msg);

public slots:
	// 执行更新
	void execUpdate();

private:
	// 初始化 参数 主库等
	void initMember();

	// 释放内存
	void freeMem();

	// 查找匹配的固件文件
	bool findFirmwares();

private slots:

private:
	void* m_pNetCmd{ nullptr };
	QString m_strDevInfo{""};	// 固件信息
	QString m_strFile{ "" };	// 选择的升级固件文件
	QString m_strCurrentInfo{ "" };	// 当前版本信息
	HWND m_hWnd{nullptr};

	QString m_strMainCoreVer{""};	// 主库版本
	bool m_bInitMainSuccess{ false };	// 初始化主库
};
