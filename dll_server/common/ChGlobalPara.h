/**
*
* File Name : ChGlobalPara.h
*
* Description : 读写配置文件类
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

#ifndef _CH_GLOBAL_PARA_H_
#define  _CH_GLOBAL_PARA_H_

#include <QString>

class ChGlobalPara
{
public:
	~ChGlobalPara();

	static ChGlobalPara* instance();
	void init();
	// 存储log路径
	QString getLogPath() const { return m_strLogPath; }
	// log 输出格式
	QString getLogFormat() const { return m_strLogFormat; }
	// server Port
	int getServerPort() const { return m_iServerPort; }
	// file port
	int getFileServerPort() const { return m_iFileServerPort; }

private:
	explicit ChGlobalPara();
	ChGlobalPara(const ChGlobalPara& obj);
	ChGlobalPara& operator=(const ChGlobalPara& obj);

	// 单例内存回收类
	class CGarbo
	{
	public:
		CGarbo() {}
		~CGarbo()
		{
			if (ChGlobalPara::m_pInstance)
			{
				delete ChGlobalPara::m_pInstance;
				ChGlobalPara::m_pInstance = nullptr;
			}
		}
	};
	static CGarbo m_Garbo;
	// 配置读取
	void initConfig();

private:
	static ChGlobalPara* m_pInstance;
	// 日志路径
	QString m_strLogPath{ "" };
	// 输出日志格式
	QString m_strLogFormat{ "" };

	// Port
	int m_iServerPort{ -1 };
	int m_iFileServerPort{ -1 };

};

#ifndef gChGlobalPara
#define gChGlobalPara ChGlobalPara::instance()
#endif

#endif