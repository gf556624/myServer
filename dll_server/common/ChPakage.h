/**
*
* File Name : ChPakage.h
*
* Description : tcp协议包
*
* Author : guofchina@163.com
*
* Create Date : 2018-05-10 10:00
*
* Update Date : 2018-05-10 10:00
*
* Version : 1.0
*
**/

#ifndef _CH_PAKAGE_H_
#define _CH_PAKAGE_H_


const int MaxSize = 2048;

// 数据包类型
enum ChPakageType
{
	PAKAGE_NONE,
	PAKAGE_UPDATE,	// 升级
	PAKAGE_MESSAGE,	// 消息
	PAKAGE_FILE_SEND_END,	// 文件发送完毕
	PAKAGE_FILE_RECV_END,	// 文件接收完成
	PAKAGE_RESTART,			// 重启
};

// 数据包
typedef struct CHPAKAGE
{
	ChPakageType m_type{ PAKAGE_NONE };		// 类型
	char m_Msg[MaxSize]{ '\0' };
}ChPakage;



#endif // !_CH_PAKAGE_H_