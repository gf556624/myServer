/**
*
* File Name : ChPakage.h
*
* Description : tcpЭ���
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

// ���ݰ�����
enum ChPakageType
{
	PAKAGE_NONE,
	PAKAGE_UPDATE,	// ����
	PAKAGE_MESSAGE,	// ��Ϣ
	PAKAGE_FILE_SEND_END,	// �ļ��������
	PAKAGE_FILE_RECV_END,	// �ļ��������
	PAKAGE_RESTART,			// ����
};

// ���ݰ�
typedef struct CHPAKAGE
{
	ChPakageType m_type{ PAKAGE_NONE };		// ����
	char m_Msg[MaxSize]{ '\0' };
}ChPakage;



#endif // !_CH_PAKAGE_H_