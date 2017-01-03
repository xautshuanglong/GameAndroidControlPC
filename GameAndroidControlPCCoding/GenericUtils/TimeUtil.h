#pragma once

/**************************************************************************\
 *  FileName: TimeUtil.h
 *
 *  Author  : JiangShuanglong
 *  Date    : 2017-01-03 22:31:56
 *
 *  Description: some operation about time include get current timestamp
 *  and format time string.
 *
 *   %a ���ڼ��ļ�д
 *   %A ���ڼ���ȫ��
 *   %b �·ֵļ�д
 *   %B �·ݵ�ȫ��
 *   %c ��׼�����ڵ�ʱ�䴮
 *   %C ��ݵĺ���λ����
 *   %d ʮ���Ʊ�ʾ��ÿ�µĵڼ���
 *   %D ��/��/��
 *   %e �����ַ����У�ʮ���Ʊ�ʾ��ÿ�µĵڼ���
 *   %F ��-��-��
 *   %g ��ݵĺ���λ���֣�ʹ�û����ܵ���
 *   %G ��֣�ʹ�û����ܵ���
 *   %h ��д���·���
 *   %H 24Сʱ�Ƶ�Сʱ
 *   %I 12Сʱ�Ƶ�Сʱ
 *   %j ʮ���Ʊ�ʾ��ÿ��ĵڼ���
 *   %m ʮ���Ʊ�ʾ���·�
 *   %M ʮʱ�Ʊ�ʾ�ķ�����
 *   %n ���з�
 *   %p ���ص�AM��PM�ĵȼ���ʾ
 *   %r 12Сʱ��ʱ��
 *   %R ��ʾСʱ�ͷ��ӣ�hh:mm
 *   %S ʮ���Ƶ�����
 *   %t ˮƽ�Ʊ��
 *   %T ��ʾʱ���룺hh:mm:ss
 *   %u ÿ�ܵĵڼ��죬����һΪ��һ�� ��ֵ��0��6������һΪ0��
 *   %U ����ĵڼ��ܣ�����������Ϊ��һ�죨ֵ��0��53��
 *   %V ÿ��ĵڼ��ܣ�ʹ�û����ܵ���
 *   %w ʮ���Ʊ�ʾ�����ڼ���ֵ��0��6��������Ϊ0��
 *   %W ÿ��ĵڼ��ܣ�������һ��Ϊ��һ�죨ֵ��0��53��
 *   %x ��׼�����ڴ�
 *   %X ��׼��ʱ�䴮
 *   %y �������͵�ʮ������ݣ�ֵ��0��99��
 *   %Y �����Ͳ��ֵ�ʮ�����
 *   %z��%Z ʱ�����ƣ�������ܵõ�ʱ�������򷵻ؿ��ַ���
 *   %% �ٷֺ�
\**************************************************************************/

#include "CommonDefines.h"

#include <windows.h>
#include <ctime>
#include <iostream>

namespace ShuangLong
{
	namespace Utils
	{
		class EXPORT_API TimeUtil sealed
		{
		private:
			static tm m_tmCurTime;
			static time_t m_tCurTime;
			static SYSTEMTIME m_systemTime;

		public:
			TimeUtil();
			~TimeUtil();

			static std::string GetFullTimeString();
			static std::string GetSimpleTimeString();
			static std::string GetFormatTimeString(const char* timeFormat);

			static std::string GetFullTimestamp();
			static std::string GetSimpleTimestamp();

		private:
			static void GetCurrentTime();
		};
	}
}
