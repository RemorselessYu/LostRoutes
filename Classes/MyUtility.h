#pragma once
#ifndef __MY_UTILITY_H__
#define __MY_UTILITY_H__

#include "cocos2d.h"

using namespace std;

class MyUtility
{
public:
	//��ȡ��ǰϵͳʱ��
	static string getCurrentTime();

	//�� GBK ����תΪ UTF8 ����
	static string gbk_2_utf8(const string text);

	//�������б��а��ռ���ȡ UTF8 �ַ���
	static string getUTF8Char(const string key);
};

#endif // __MY_UTILITY_H__
