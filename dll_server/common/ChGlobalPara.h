/**
*
* File Name : ChGlobalPara.h
*
* Description : ��д�����ļ���
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
	// �洢log·��
	QString getLogPath() const { return m_strLogPath; }
	// log �����ʽ
	QString getLogFormat() const { return m_strLogFormat; }
	// server Port
	int getServerPort() const { return m_iServerPort; }
	// file port
	int getFileServerPort() const { return m_iFileServerPort; }

private:
	explicit ChGlobalPara();
	ChGlobalPara(const ChGlobalPara& obj);
	ChGlobalPara& operator=(const ChGlobalPara& obj);

	// �����ڴ������
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
	// ���ö�ȡ
	void initConfig();

private:
	static ChGlobalPara* m_pInstance;
	// ��־·��
	QString m_strLogPath{ "" };
	// �����־��ʽ
	QString m_strLogFormat{ "" };

	// Port
	int m_iServerPort{ -1 };
	int m_iFileServerPort{ -1 };

};

#ifndef gChGlobalPara
#define gChGlobalPara ChGlobalPara::instance()
#endif

#endif