#pragma once
#include <spdlog/spdlog.h>
#include <map>
#include "tag_info.hpp"
#include "error_info.hpp"

namespace gateway
{
	namespace common
	{
		class CollectorPlugin
		{
		public:
			/*
			*功能：初始化协议插件
			*入参：
			*tagInfos:测点信息列表，包括开关量、模拟量、控制量测点
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
			virtual ErrorInfo Init(const std::vector<TagInfo> &tagInfos, const std::map<std::string, PluginParam> &pluginCfg, const std::shared_ptr<spdlog::logger> &logPtr) = 0;

			/*
			*功能：连接数据源/上位机进行采集
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
			*功能：连接异常时，重连数据源/上位机
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
			*功能：获取数据源/上位机采集通讯状态
			*入参：
			*无
			*出参：
			*collectInfo.sourceName:上位机/数据源名称
			*collectInfo.sourceAddr:上位机/数据源的地址/端口号/串口号
			*collectInfo.sourceCollectStatus:数据源采集状态
			*collectInfo.sourceCollectMsg:数据源采集信息
			*返回值：
			* CollectErrorInfo.retCode:错误码，返回0为正常值，非0为异常值
			* CollectErrorInfo.systemCode:系统错误码
			* CollectErrorInfo.errorMsg:错误信息，正常返回空，异常返回异常信息
			* CollectErrorInfo.errType;错误类型枚举
			*/
			virtual ErrorInfo GetRunInfo(std::vector<SourceCollectInfo> &collectInfos) = 0;

			/*
			*功能：获取采集插件运行模式，被动模式/主动模式
			*入参：
			*无
			*出参：
			*无
			*返回值：
			* gateway::PluginRunModel:
			*	kActive定时调用Read函数获取数据
			*	kPassive调用运行Run函数
			*/
			virtual PluginRunModel GetPluginRunModel() = 0;

			/*
			*功能：主动模式读取数据
			*入参：
			*无
			*出参：
			*tagInfos:测点信息数组
			*tagValues:测点值数组，与测点名数组下标对应一致
			*返回值：
			* CollectErrorInfo.retCode:错误码，返回0为正常值，非0为异常值
			* CollectErrorInfo.systemCode:系统错误码
			* CollectErrorInfo.errorMsg:错误信息，正常返回空，异常返回异常信息
			* CollectErrorInfo.errType;错误类型枚举
			*/
			virtual ErrorInfo Read(std::vector<TagInfo> &tagInfos, std::vector<TagValue> &tagValues) = 0;

			/*
			*功能：被动模式读取数据
			*入参：
			*SetValueFunc:实时缓存写入函数指针
			*updateNotifyMqttFunc:数据更新，mqtt通知函数指针
			*出参：
			*无
			*返回值：
			* CollectErrorInfo.retCode:错误码，返回0为正常值，非0为异常值
			* CollectErrorInfo.systemCode:系统错误码
			* CollectErrorInfo.errorMsg:错误信息，正常返回空，异常返回异常信息
			* CollectErrorInfo.errType;错误类型枚举
			*/
			virtual ErrorInfo Run(
				std::function<ErrorInfo( std::vector<TagInfo>&,  std::vector<TagValue>&)> SetValueFunc,
				std::function<ErrorInfo()> updateNotifyMqttFunc) = 0;

			/*
			*功能：是否支持下控功能
			*入参：
			*无
			*出参：
			*无
			*返回值：
			* true:支持下控
			* false:不支持下控
			*/
			virtual bool ControlEnable() = 0;

			/*
			*功能：下控数据
			*入参：
			*tagNames：控制点名，内部根据控制点名找到对应的采集点名
			*tagValues：下控的值，按采集点名进行写入
			*出参：
			*无
			*返回值：
			* CollectErrorInfo.retCode:错误码，返回0为正常值，非0为异常值
			* CollectErrorInfo.systemCode:系统错误码
			* CollectErrorInfo.errorMsg:错误信息，正常返回空，异常返回异常信息
			* CollectErrorInfo.errType;错误类型枚举
			*/
			virtual ErrorInfo Write(const std::vector<TagInfo> &tagInfos, const std::vector<TagValue> &tagValues) = 0;



			/*
			*功能：是否是内部协议，决定是否绘制数据源与目的地
			* 返回值：
			*true：是内部协议,则不绘制数据源
			*false:非内部协议，则绘制数据源
			*/
			virtual bool IsInternalPlugin() = 0;

		};

	}//common
	
}//gateway
