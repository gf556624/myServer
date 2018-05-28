/**
*
* File Name : ChRoseekObject.cpp
*
* Description : ���ִ�������߳� ����ʵ��
*
* Author :GuoFeng
*
* Create Date : 2018-05-02 10:00:00
*
* Update Date : 2018-05-02 10:00:00
*
* Version : 1.0
*
**/

#include "ChRoseekObject.h"
//#include <windows.h>
#include "WPMainCore.h"
#include "ChameleonRemoteUpdate.h"
#include "WPNetCmd.h"

#include <atlconv.h>
#include <QtGlobal>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QThread>
#include <QDir>
#include <QFileInfo>

#pragma comment(lib, "WPMainCore.lib")
#pragma comment(lib, "ChameleonRemoteUpdate.lib")
#pragma comment(lib, "WPNetCmd.lib")

ChRoseekObject::ChRoseekObject(QObject *parent /*= Q_NULLPTR*/)
	: QObject(parent)
{
	initMember();
	//checkVersion();
}

ChRoseekObject::~ChRoseekObject()
{
	freeMem();
}

// У��汾
bool ChRoseekObject::checkVersion()
{
	QTextStream in(&m_strCurrentInfo);
	QString str("");
	while (!(str = in.readLine()).isNull())
	{
		qDebug() << str;
		if (str.contains("roseek_wp1_maincore"))	// ����汾
		{
			m_strMainCoreVer = getVersion(str);
			qInfo() << "MainCore:" + m_strMainCoreVer;
		}
		else if (str.contains("roseek_wp1_fpga"))
		{
		}
		else if (str.contains("roseek_wp1_peripheral"))
		{
		}
		else if (str.contains("roseek_wp1_extension"))
		{
		}
		else if (str.contains("roseek_wp1_dll_netcmd"))
		{
		}
		else if (str.contains("roseek_ct1_dll_stream"))
		{
		}
		else if (str.contains("roseek_ct1_dll_media"))
		{
		}
		else if (str.contains("roseek_ct1_dll_osd"))
		{
		}
	}
	if ("1.19" == m_strMainCoreVer)
	{
		return true;
	}

	return false;
}

// ��ȡ�汾
QString ChRoseekObject::getVersion(const QString& str) const
{
	QStringList slst = str.split(" ");
	for (int i = 0; i < slst.size(); ++i)
	{
		if ("Version:" == slst.at(i))
		{
			if (i + 1 < slst.size())
			{
				qDebug() << slst.at(i + 1);
				return slst.at(i + 1);
			}
		}
	}

	return "";
}

// �������
bool ChRoseekObject::restartCamera()
{
	// 0Ϊ�������� 1Ϊ������
	int iRes = -1;
	bool bRes = false;
	iRes = Roseek_System_Reset(0);
	if (!iRes)
	{
		qInfo() << QStringLiteral("�����ɹ�");
		bRes = true;
	}
	else
	{
		qInfo() << QStringLiteral("����ʧ��");
	}

	return bRes;
}

// ִ�и���
void ChRoseekObject::execUpdate()
{
	qInfo() << "execUpdate...";

	if (m_bInitMainSuccess && !findFirmwares())
	{
		QString strMsg = QStringLiteral("����ʧ��, û���ҵ�ƥ�������Ĺ̼��ļ�");
		qCritical() << strMsg;
		emit sigUpdateFailed(strMsg);
		return;
	}

	USES_CONVERSION;
	char UserName[MAX_PATH];
	char Password[MAX_PATH];

	Roseek_System_GetUserAccount(UserName, MAX_PATH, Password, MAX_PATH);
	//qInfo() << UserName;
	//qInfo() << Password;

	if (m_strFile.isEmpty())
	{
		return;
	}
	QByteArray byteArray = m_strFile.toLocal8Bit();
	char* fileName = byteArray.data();
	qInfo() << fileName;
	int iRes = Roseek_CMRemoteUpdate(fileName, UserName, Password, "127.0.0.1", 7432, FALSE, NULL, m_hWnd, 1);
}

// ��ʼ��
void ChRoseekObject::initMember()
{
	// ��ʼ������ 0��ʾ��������־���ڣ���0��ʾ������־����
	int iRes = Roseek_MainCore_Init(0);
	qInfo() << "MainCore Init: " << iRes;
	qInfo() << QString::number(iRes);

	if (!iRes)
	{
		m_bInitMainSuccess = true;
		QString strMsg = QStringLiteral("��ʼ������ɹ�");
		qInfo() << strMsg;

		// ��ȡ�̼��汾��Ϣ
		char devModel[256] = { '\0' };
		iRes = Roseek_System_GetDevModel(devModel, sizeof(devModel));
		if (!iRes)
		{
			m_strDevInfo = QString(devModel);
			qInfo() << devModel;
		}

		char pInfoBuff[10 * 1024] = { '\0' };
		iRes = Roseek_System_ReadDevInfo(pInfoBuff, 10 * 1024);
		if (0 == iRes)
		{
			m_strCurrentInfo = QString(pInfoBuff);
			qInfo() << pInfoBuff;
		}

		//Net command Service
		m_pNetCmd = Roseek_NetCmd_Open("roseek", "roseek", 36000, 46046, 7432, 10 * 1024, 10000, NULL);
	}
	else
	{
		QString strMsg = QStringLiteral("��ʼ������ʧ��");
		qCritical() << strMsg;
	}
}

// �ͷ��ڴ�
void ChRoseekObject::freeMem()
{
	if (m_pNetCmd)
	{
		Roseek_NetCmd_Close(m_pNetCmd);
		m_pNetCmd = nullptr;
	}
	// �ͷ�����
	Roseek_MainCore_UnInit();
}

// ����ƥ��Ĺ̼��ļ�
bool ChRoseekObject::findFirmwares()
{
	QString strDir = QDir::currentPath();
	QDir oDir(strDir);
	if (oDir.exists())
	{
		QFileInfoList lstFileInfo = oDir.entryInfoList(QDir::Files);
		QString strDevInfo = m_strDevInfo.mid(0, 8);
		qInfo() << strDevInfo;
		for (auto fileInfo : lstFileInfo)
		{
			QString strFileName = fileInfo.fileName();
			qInfo() << strFileName;
			if (strFileName.startsWith(strDevInfo))
			{
				qInfo() << "find";
				m_strFile = strDir + "/" + strFileName;
				qInfo() << m_strFile;
				return true;
			}
		}
	}

	return false;
}
