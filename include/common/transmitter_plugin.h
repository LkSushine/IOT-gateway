#pragma once
#include <spdlog/spdlog.h>
#include <map>
#include "tag_info.hpp"
#include "error_info.hpp"
#include "task_info.hpp"

namespace gateway
{
	namespace common
	{
		class TransmitterPlugin
		{
		public:
			/*
			*功能：初始化协议插件
			*入参：
			*taskId:转发任务ID
			*tagInfos:转发初始化测点列表
			*pluginCfg:协议参数数据，key为参数标识，value为协议基础信息
			logPtr:日志的智能指针
			*出参：
			*无
			*返回值：
			* CollectErrorInfo.retCode:错误码，返回0为正常值，非0为异常值
			* CollectErrorInfo.systemCode:系统错误码
			* CollectErrorInfo.errorMsg:错误信息，正常返回空，异常返回异常信息
			* CollectErrorInfo.errType;错误类型枚举
			*/
			virtual ErrorInfo Init(const gateway::common::TaskInfo &taskInfo, const gateway::common::SystemInfo &sysInfo, const std::vector<TagInfo> &tagInfos, const std::map<std::string, PluginParam> &pluginCfg, const std::shared_ptr<spdlog::logger> &logPtr) = 0;

			/*
			*功能：设置下控回调函数
			*入参：
			*controlFunc:下控回调函数
			*出参：
			*无
			*返回值：
			*无
			*/
			virtual void SetControlCallBack(const std::function<void (const TagInfo&,const TagValue&)> controlFunc) = 0;

			
			/*
			*功能：连接目的地
			*入参：
			*无
			*出参：
			*无
			*返回值：
			* CollectErrorInfo.retCode:错误码，返回0为正常值，非0为异常值
			* CollectErrorInfo.systemCode:系统错误码
			* CollectErrorInfo.errorMsg:错误信息，正常返回空，异常返回异常信息
			* CollectErrorInfo.errType;错误类型枚举
			*/
			virtual ErrorInfo Connect() = 0;

			/*
			*功能：连接异常时，重连目的地
			*入参：
			*无
			*出参：
			*无
			*返回值：
			* CollectErrorInfo.retCode:错误码，返回0为正常值，非0为异常值
			* CollectErrorInfo.systemCode:系统错误码
			* CollectErrorInfo.errorMsg:错误信息，正常返回空，异常返回异常信息
			* CollectErrorInfo.errType;错误类型枚举
			*/
			virtual ErrorInfo ReConnect() = 0;

			/*
			*功能：获取目的地通讯状态
			*入参：
			*无
			*出参：
			*collectInfo.sourceName:目的地名称
			*collectInfo.sourceAddr:目的地的地址/端口号/串口号
			*collectInfo.sourceCollectStatus:目的地转发状态
			*collectInfo.sourceCollectMsg:目的地转发信息
			*返回值：
			* CollectErrorInfo.retCode:错误码，返回0为正常值，非0为异常值
			* CollectErrorInfo.systemCode:系统错误码
			* CollectErrorInfo.errorMsg:错误信息，正常返回空，异常返回异常信息
			* CollectErrorInfo.errType;错误类型枚举
			*/
			virtual ErrorInfo GetRunInfo(std::vector<SourceCollectInfo> &collectInfos) = 0;

			/*
			*功能：发送数据
			*入参：
			*transTopic:转发设备分组对应的topic
			*tagInfos:该设备下的测点数组
			*tagValues:测点值数组，与测点名数组下标对应一致
			*出参：
			*无
			*返回值：
			* CollectErrorInfo.retCode:错误码，返回0为正常值，非0为异常值
			* CollectErrorInfo.systemCode:系统错误码
			* CollectErrorInfo.errorMsg:错误信息，正常返回空，异常返回异常信息
			* CollectErrorInfo.errType;错误类型枚举
			*/
			virtual ErrorInfo Send(const DeviceGroupInfo &transTopic, const std::vector<TagInfo> &tagInfos, const std::vector<TagValue> &tagValues) = 0;

			/*
			*功能：发送历史缓存数据
			*入参：
			*transTopic:转发设备分组对应的topic
			*tagInfos:该设备下的测点数组
			*tagValues:测点值数组，与测点名数组下标对应一致
			*出参：
			*无
			*返回值：
			* CollectErrorInfo.retCode:错误码，返回0为正常值，非0为异常值
			* CollectErrorInfo.systemCode:系统错误码
			* CollectErrorInfo.errorMsg:错误信息，正常返回空，异常返回异常信息
			* CollectErrorInfo.errType;错误类型枚举
			*/
			virtual ErrorInfo SendHisValues(const DeviceGroupInfo &transTopic, const std::vector<TagInfo> &tagInfos, const std::vector<TagValue> &tagValues) = 0;

			/*
			*功能：是否是内部协议，决定是否绘制数据源与目的地
			* 返回值：
			*true：是内部协议,则不绘制目的地
			*false:非内部协议，则绘制目的地
			*/
			virtual bool IsInternalPlugin() = 0;
		};
		
	}//common
	
}//gateway
