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
			tmTemp.tm_year = year - 1900;                 // 年，由于tm结构体存储的是从1900年开始的时间，所以tm_year为int临时变量减去1900。
			tmTemp.tm_mon = month - 1;                    // 月，由于tm结构体的月份存储范围为0-11，所以tm_mon为int临时变量减去1。
			tmTemp.tm_mday = day;                         // 日。
			tmTemp.tm_hour = hour;                        // 时。
			tmTemp.tm_min = minute;                       // 分。
			tmTemp.tm_sec = second;                       // 秒。
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