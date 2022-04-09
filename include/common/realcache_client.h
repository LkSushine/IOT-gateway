#pragma once

#include "multi_value.hpp"
#include "error_info.hpp"
#include "tag_info.hpp"

namespace gateway
{
	namespace common
	{
		class RealCacheClient
		{
		public:
			/*
			 *功能：连接缓存服务端
			 *入参：
			 *connectIp:服务端地址
			 *connectPort:服务端端口
			 *出参：
			 *返回值：
			 * CacheErrorInfo.errorCode:错误码，返回0为正常值，非0为异常值
			 * CacheErrorInfo.errorMsg:错误信息，正常返回空，异常返回异常信息
			 */
			virtual ErrorInfo Connect(const std::string &connectAddrPort) = 0;

			/*
			 *功能：创建测点
			 *入参：
			 *tagInfos：测点信息数组
			 *出参：
			 *无
			 *返回值：
			 * CacheErrorInfo.errorCode:错误码，返回0为正常值，非0为异常值
			 * CacheErrorInfo.errorMsg:错误信息，正常返回空，异常返回异常信息
			 */
			virtual ErrorInfo CreateTags(const std::vector<TagInfo> &tagInfos) = 0;

			/*
			 *功能：写入测点数据
			 *入参：
			 *tagInfos：待写入数据测点数组
			 *tagValues：待写入数据数组
			 *出参：
			 *无
			 *返回值：
			 * CacheErrorInfo.errorCode:错误码，返回0为正常值，非0为异常值
			 * CacheErrorInfo.errorMsg:错误信息，正常返回空，异常返回异常信息
			 */
			virtual ErrorInfo SetValues(const std::vector<TagInfo> &tagInfos, const std::vector<TagValue> &tagValues) = 0;

			/*
			 *功能：写入测点数据
			 *入参：
			 *tagInfo：待写入数据测点数组
			 *tagValue：待写入数据数组
			 *出参：
			 *无
			 *返回值：
			 * CacheErrorInfo.errorCode:错误码，返回0为正常值，非0为异常值
			 * CacheErrorInfo.errorMsg:错误信息，正常返回空，异常返回异常信息
			 */
			virtual ErrorInfo SetValue(const TagInfo &tagInfo, const TagValue &tagValue) = 0;

			/*
			 *功能：读取测点数据
			 *入参：
			 *tagInfos：待写入数据测点数组
			 *出参：
			 *tagValues：返回测点数据数组
			 *返回值：
			 * CacheErrorInfo.errorCode:错误码，返回0为正常值，非0为异常值
			 * CacheErrorInfo.errorMsg:错误信息，正常返回空，异常返回异常信息
			 */
			virtual ErrorInfo GetValues(const std::vector<TagInfo> &tagInfos, std::vector<TagValue> &tagValues) = 0;
			
			/*
			 *功能：读取测点数据
			 *入参：
			 *tagInfo：待写入数据测点数组
			 *出参：
			 *tagValue：返回测点数据数组
			 *返回值：
			 * CacheErrorInfo.errorCode:错误码，返回0为正常值，非0为异常值
			 * CacheErrorInfo.errorMsg:错误信息，正常返回空，异常返回异常信息
			 */
			virtual ErrorInfo GetValue(const TagInfo &tagInfo, TagValue &tagValue) = 0;

		};
	}//common
	
}//gateway
