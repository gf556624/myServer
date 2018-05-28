#include "ChGlobalPara.h"
#include <QSettings>
#include <QMutex>
#include <QTextStream>
#include <QFile>
#include <QDateTime>


static QMutex g_mutex;
ChGlobalPara::CGarbo ChGlobalPara::m_Garbo;	// ��ʼ��
ChGlobalPara* ChGlobalPara::m_pInstance = nullptr;
ChGlobalPara* ChGlobalPara::instance()
{
	if (!m_pInstance)
	{
		g_mutex.lock();
		if (!m_pInstance)
		{
			m_pInstance = new ChGlobalPara();
		}
		g_mutex.unlock();
	}

	return m_pInstance;
}


void ChGlobalPara::init()
{
	initConfig();
}

ChGlobalPara::ChGlobalPara()
{
	init();
}

ChGlobalPara::~ChGlobalPara()
{

}

// ���ö�ȡ
void ChGlobalPara::initConfig()
{
	QSettings *pConfigIniRead = new QSettings("serverConfig.ini", QSettings::IniFormat); 
	// ��־
	m_strLogPath = pConfigIniRead->value("log/path").toString();
	m_strLogFormat = pConfigIniRead->value("log/format").toString();

	// port
	m_iServerPort = pConfigIniRead->value("server/serverPort").toInt();
	m_iFileServerPort = pConfigIniRead->value("server/filePort").toInt();

	pConfigIniRead->deleteLater();
	pConfigIniRead = nullptr;
}
