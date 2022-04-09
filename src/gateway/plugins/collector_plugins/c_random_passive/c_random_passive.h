#pragma once

#include <collector_plugin.h>
#include <boost/dll.hpp>
#include <memory>

class RandomPassivePlugin:public gateway::common::CollectorPlugin
{
public:

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

	gateway::common::ErrorInfo Write(const std::vector<gateway::common::TagInfo> &tagNames, const std::vector<gateway::common::TagValue> &tagValues) override;

	bool IsInternalPlugin() override;
	
	static std::shared_ptr<CollectorPlugin> CreateCollectorPlugin()
	{
		return std::make_shared<RandomPassivePlugin>();
	}
private:
	void InitTags(const std::vector<gateway::common::TagInfo> &tagInfos);

	std::vector<gateway::common::TagInfo> switchTags_;
	std::vector<gateway::common::TagInfo> analogTags_;
	std::vector<gateway::common::TagInfo> controlTags_;

	std::shared_ptr<spdlog::logger> logPtr_;



};

BOOST_DLL_ALIAS(
	RandomPassivePlugin::CreateCollectorPlugin,
	CreateCollectorPlugin
)
