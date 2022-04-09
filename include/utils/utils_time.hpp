#pragma once
#include <codecvt>
#include <string>
#include <vector>

namespace gateway
{
	namespace utils
	{
		time_t StrToTime(const std::string & str)
		{
			char* ptr = (char*)str.c_str();
			tm tmTemp;
			int year = 0, month = 0, day = 0, hour = 0, minute = 0, second = 0;
			sscanf(ptr, "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second);
			tmTemp.tm_year = year - 1900;                 // �꣬����tm�ṹ��洢���Ǵ�1900�꿪ʼ��ʱ�䣬����tm_yearΪint��ʱ������ȥ1900��
			tmTemp.tm_mon = month - 1;                    // �£�����tm�ṹ����·ݴ洢��ΧΪ0-11������tm_monΪint��ʱ������ȥ1��
			tmTemp.tm_mday = day;                         // �ա�
			tmTemp.tm_hour = hour;                        // ʱ��
			tmTemp.tm_min = minute;                       // �֡�
			tmTemp.tm_sec = second;                       // �롣
			tmTemp.tm_isdst = 0;
			time_t tTemp = mktime(&tmTemp);
			return tTemp;
		}

		std::string TimetToMisStr(const time_t time_t_time)
		{
			char szTime[100] = { '\0' };
			tm pTm;
			localtime_s(&pTm, &time_t_time);
			pTm.tm_year += 1900;
			pTm.tm_mon += 1;
			sprintf_s(szTime, "%04d-%02d-%02d %02d:%02d:%02d.000",
				pTm.tm_year,
				pTm.tm_mon,
				pTm.tm_mday,
				pTm.tm_hour,
				pTm.tm_min,
				pTm.tm_sec);
			std::string strTime = szTime;
			return strTime;
		}

		std::string time_tToString(const time_t time_t_time)
		{
			char szTime[100] = { '\0' };
			tm pTm;
			localtime_s(&pTm, &time_t_time);
			pTm.tm_year += 1900;
			pTm.tm_mon += 1;
			sprintf_s(szTime, "%04d/%02d/%02d %02d:%02d:%02d",
				pTm.tm_year,
				pTm.tm_mon,
				pTm.tm_mday,
				pTm.tm_hour,
				pTm.tm_min,
				pTm.tm_sec);
			std::string strTime = szTime;
			return strTime;
		}
	}//utils
	
}//gateway