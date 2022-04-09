#pragma once
#include <spdlog/spdlog.h>
#include <map>
#include "vibration_tag.hpp"
#include "tag_info.hpp"
#include "error_info.hpp"
namespace gateway
{
	namespace common
	{
		class VibrationCollectorPlugin
		{
		public:
			/*
			*功能：初始化协议插件
			*入参：
			*pluginCfg:协议参数数据，key为参数标识，value为协议基础信息
			*logPtr:日志的智能指针
			*出参：
			*无
			*返回值：
			* CollectErrorInfo.retCode:错误码，返回0为正常值，非0为异常值
			* CollectErrorInfo.systemCode:系统错误码
			* CollectErrorInfo.errorMsg:错误信息，正常返回空，异常返回异常信息
			* CollectErrorInfo.errType;错误类型枚举
			*/
			virtual ErrorInfo Init(const std::map<std::string, PluginParam> &pluginCfg, const std::shared_ptr<spdlog::logger> &logPtr) = 0;

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
			*功能：下发采集器配置
			*入参：
			*channelDefInfoMaps:采集器与通道信息
			*出参：
			*无
			*返回值：
			* CollectErrorInfo.retCode:错误码，返回0为正常值，非0为异常值
			* CollectErrorInfo.systemCode:系统错误码
			* CollectErrorInfo.errorMsg:错误信息，正常返回空，异常返回异常信息
			* CollectErrorInfo.errType;错误类型枚举
			*/
			virtual ErrorInfo CollectCfgSet(const std::map<gateway::common::CollectorInfo, std::vector<gateway::common::ChannelInfoDef>> &channelDefInfoMaps) = 0;

			/*
			*功能：采集器是否正处于通讯运行状态
			*入参：
			*无
			*出参：
			*无
			*返回值：
			* true:采集器正在运行
			* false:采集器停止采集，可进行采集器配置更新
			*/
			virtual bool IsRunnig() = 0;


			/*
			*功能：是否具备转发功能，具备时则不写入缓存，由采集协议内部进行数据转发
			*入参：
			*无
			*出参：
			*无
			*返回值：
			* true:具备转发功能
			* false:不具备转发功能
			*/
			virtual bool TransEnable() = 0;


			/*
			*功能：获取采集器的通讯状态
			*入参：
			*无
			*出参：
			*collectInfo.sourceName:采集器名称
			*collectInfo.sourceAddr:采集器地址/端口号/串口号
			*collectInfo.sourceCollectStatus:采集器采集状态
			*collectInfo.sourceCollectMsg:采集器采集信息
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
			*channelInfos:通道信息数组
			*channelData:通道数据
			*返回值：
			* CollectErrorInfo.retCode:错误码，返回0为正常值，非0为异常值
			* CollectErrorInfo.systemCode:系统错误码
			* CollectErrorInfo.errorMsg:错误信息，正常返回空，异常返回异常信息
			* CollectErrorInfo.errType;错误类型枚举
			*/
			virtual ErrorInfo Read(std::vector<gateway::common::ChannelInfoDef> &channelInfos, std::vector<gateway::common::TagValue> &channelData) = 0;

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
				std::function<ErrorInfo(const std::vector<gateway::common::ChannelInfoDef>&, const std::vector<gateway::common::TagValue>&)> SetValueFunc,
				std::function<ErrorInfo(const std::vector<gateway::common::ChannelInfoDef> &)> updateNotifyMqttFunc) = 0;


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
