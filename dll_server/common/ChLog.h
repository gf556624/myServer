/**
*
* File Name : ChLog.h
*
* Description : 日志类
*
* Author : guofchina@163.com
*
* Create Date : 2018-05-25 12:50
*
* Update Date : 2018-05-25 12:50
*
* Version : 1.0
*
**/

#ifndef _CH_LOG_H
#define  _CH_LOG_H

#include <QString>

class ChLog
{
public:
	~ChLog();

	static ChLog* instance();
	void init();
	QString logPath() const { return m_strLogPath; }

private:
	explicit ChLog();
	ChLog(const ChLog& obj);
	ChLog& operator=(const ChLog& obj);

	// 单例内存回收类
	class CGarbo
	{
	public:
		CGarbo() {}
		~CGarbo()
		{
			if (ChLog::m_pInstance)
			{
				delete ChLog::m_pInstance;
				ChLog::m_pInstance = nullptr;
			}
		}
	};
	static CGarbo m_Garbo;

private:
	static ChLog* m_pInstance;
	QString m_strLogPath{ "" };	// 日志路径
	QString m_strLogFormat{ "" }; // 日志格式
};

#ifndef gChLog
#define gChLog ChLog::instance()
#endif

#endif