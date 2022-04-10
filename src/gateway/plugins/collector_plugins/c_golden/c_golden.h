#pragma once
#include <collector_plugin.h>
#include <boost/dll.hpp>
#include <memory>
#include <Windows.h>
#include "goldenapi.h"

class GoldenActivePlugin:public gateway::common::CollectorPlugin
{
public:
	GoldenActivePlugin();

	gateway::common::ErrorInfo Init(const std::vector<gateway::common::TagInfo> &tagInfos, const std::map<std::string, gateway::common::PluginParam> &pluginCfg, const std::shared_ptr<spdlog::logger> &logPtr) override;

	gateway::common::ErrorInfo Connect() override;

	gateway::common::ErrorInfo ReConnect() override;

	gateway::common::ErrorInfo GetRunInfo(std::vector<gateway::common::SourceCollectInfo> &collectInfos) override;

	gateway::common::PluginRunModel GetPluginRunModel() override;

	gateway::common::ErrorInfo Read(std::vector<gateway::common::TagInfo> &tagNames, std::vector<gateway::common::TagValue> &tagValues) override;

	gateway::common::ErrorInfo Run(
		std::function<gateway::common::ErrorInfo( std::vector<gateway::common::TagInfo>&,  std::vector<gateway::common::TagValue>&)> SetValueFunc,
		std::function<gateway::common::ErrorInfo()> updateNotifyMqttFunc) override;

	bool ControlEnable() override;

	bool IsInternalPlugin() override;

	gateway::common::ErrorInfo Write(const std::vector<gateway::common::TagInfo> &tagNames, const std::vector<gateway::common::TagValue> &tagValues) override;

	static std::shared_ptr<CollectorPlugin> CreateCollectorPlugin()
	{
		return std::make_shared<GoldenActivePlugin>();
	}
private:
	void InitTags();
	void InitCfg(std::map<std::string, gateway::common::PluginParam> pluginCfg);
	std::shared_ptr<spdlog::logger> logPtr_;
	golden_int32 handle_;
	std::string ip_;
	int port_;
	std::string username_;
	std::string password_;
	std::vector<gateway::common::TagInfo> tagInfos_;
	std::vector<gateway::common::TagInfo> existTagInfos_;
	std::vector<golden_int32> existTagIds_;
	gateway::common::SourceCollectInfo collectInfos_;
	golden_int32* datetimes_; // 输出，时间戳，秒
	golden_int16* ms_; // 输出，时间戳，毫秒部分
	golden_float64* values_; // 输出，浮点型数值列表
	golden_int64* states_; // 输出，实时整型数值列表
	golden_int16* qualities_; // 输出，质量码
	golden_error* errors_; // 输出，对应错误码列表
	int errorCount_;//读取失败计数
};

BOOST_DLL_ALIAS(
	GoldenActivePlugin::CreateCollectorPlugin,
	CreateCollectorPlugin
)
