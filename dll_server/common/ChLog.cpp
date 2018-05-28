#include "ChLog.h"
#include <QMutex>
#include <QDir>
#include <QTextStream>
#include <QFile>
#include <QDateTime>
#include "ChGlobalPara.h"

// ��ʽ�������־
void Logger(QtMsgType type, const QMessageLogContext& context, const QString& strMsg)
{
	static QMutex mutex;
	mutex.lock();
	QString strText = qFormatLogMessage(type, context, strMsg);
	QString strCurDate = QDateTime::currentDateTime().toString("yyyy-MM-dd");
	QString strFileName = QString("%1/Server_log_%2.txt").arg(gChLog->logPath()).arg(strCurDate);
	QFile file(strFileName);	// �����ļ�
	if (file.open(QIODevice::WriteOnly | QIODevice::Append))
	{
		QTextStream textStream(&file);
		textStream << strText << "\r\n";
		file.flush();
	}
	file.close();
	mutex.unlock();
}


static QMutex g_mutex;
ChLog::CGarbo ChLog::m_Garbo;	// ��ʼ��
ChLog* ChLog::m_pInstance = nullptr;
ChLog* ChLog::instance()
{
	if (!m_pInstance)
	{
		g_mutex.lock();
		if (!m_pInstance)
		{
			m_pInstance = new ChLog();
		}
		g_mutex.unlock();
	}

	return m_pInstance;
}


void ChLog::init()
{
	// ������־�ļ���
	QDir dir(m_strLogPath);
	if (!dir.exists())
	{
		dir.mkpath(m_strLogPath);
	}

	// ע��
	qSetMessagePattern(m_strLogFormat);
	qInstallMessageHandler(Logger);
}

ChLog::ChLog()
{
	m_strLogPath = gChGlobalPara->getLogPath();
	m_strLogFormat = gChGlobalPara->getLogFormat();
}

ChLog::~ChLog()
{

}
