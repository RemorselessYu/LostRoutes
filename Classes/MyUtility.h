#pragma once
#ifndef __MY_UTILITY_H__
#define __MY_UTILITY_H__

#include "cocos2d.h"

using namespace std;

class MyUtility
{
public:
	//获取当前系统时间
	static string getCurrentTime();

	//将 GBK 编码转为 UTF8 编码
	static string gbk_2_utf8(const string text);

	//从属性列表中按照键读取 UTF8 字符串
	static string getUTF8Char(const string key);
};

#endif // __MY_UTILITY_H__
