/**
*
* File Name : ChRoseekObject.h
*
* Description : ���ִ�������߳� ��������
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

	// ����/��ȡѡ��������ļ�
	QString getUpdateFile() const { return m_strFile; }
	void setUpdateFile(const QString& strFile) { m_strFile = strFile; }

	// ���ھ��
	void setHwnd(HWND hWnd) { m_hWnd = hWnd; }

	// У��汾
	bool checkVersion();
	// ��ȡ�汾
	QString getVersion(const QString& str) const;

	// �������
	bool restartCamera();

signals:
	void sigUpdateFailed(const QString& msg);

public slots:
	// ִ�и���
	void execUpdate();

private:
	// ��ʼ�� ���� �����
	void initMember();

	// �ͷ��ڴ�
	void freeMem();

	// ����ƥ��Ĺ̼��ļ�
	bool findFirmwares();

private slots:

private:
	void* m_pNetCmd{ nullptr };
	QString m_strDevInfo{""};	// �̼���Ϣ
	QString m_strFile{ "" };	// ѡ��������̼��ļ�
	QString m_strCurrentInfo{ "" };	// ��ǰ�汾��Ϣ
	HWND m_hWnd{nullptr};

	QString m_strMainCoreVer{""};	// ����汾
	bool m_bInitMainSuccess{ false };	// ��ʼ������
};
