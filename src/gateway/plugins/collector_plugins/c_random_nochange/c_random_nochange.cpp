#include "c_random_nochange.h"
#include <random>
#include <spdlog/sinks/daily_file_sink.h>

using namespace gateway::common;
using namespace spdlog::level;

ErrorInfo RandomActivePlugin::Init(const std::vector<TagInfo> &tagInfos, const std::map<std::string, PluginParam> &pluginCfg, const std::shared_ptr<spdlog::logger> &logPtr)
{
	InitTags(tagInfos);
	logPtr_ = logPtr;
	SPDLOG_LOGGER_CALL(logPtr_, level_enum::debug, "Init plugin success");
	return ErrorInfo();
}

ErrorInfo RandomActivePlugin::Connect()
{
	return ErrorInfo();
}

ErrorInfo RandomActivePlugin::ReConnect()
{
	return ErrorInfo();
}

ErrorInfo RandomActivePlugin::GetRunInfo(std::vector<gateway::common::SourceCollectInfo> &collectInfos)
{
	collectInfos.clear();
	SourceCollectInfo collectInfo;
	collectInfo.sourceAddr = "127.0.0.1";
	collectInfo.sourceName = "Ëæ»úÊý";
	collectInfo.sourceCollectStatus = SourceCollectStatus::kOk;
	collectInfo.sourceCollectMsg = "";
	collectInfos.push_back(collectInfo);
	return ErrorInfo();
}

PluginRunModel RandomActivePlugin::GetPluginRunModel()
{
	return PluginRunModel::kActive;
}

ErrorInfo RandomActivePlugin::Read(std::vector<TagInfo> &tagNames, std::vector<TagValue> &tagValues)
{
	TagValue tempValue;
	for (const auto &sTag : tagValueMap_)
	{
		tempValue.SetValue(sTag.first, time(NULL), ValueStatus::kCollectGood);
		tagNames.push_back(sTag.second);
		tagValues.push_back(tempValue);
	}

	SPDLOG_LOGGER_CALL(logPtr_, level_enum::debug, "read random plugin success");
	return ErrorInfo();
}

ErrorInfo RandomActivePlugin::Run(
	std::function<ErrorInfo( std::vector<TagInfo>&,  std::vector<TagValue>&)> SetValueFunc,
	std::function<ErrorInfo()> updateNotifyMqttFunc)
{
	return ErrorInfo();
}

bool RandomActivePlugin::ControlEnable()
{
	return false;
}

ErrorInfo RandomActivePlugin::Write(const std::vector<TagInfo> &tagNames, const std::vector<TagValue> &tagValues)
{
	return ErrorInfo();
}

bool RandomActivePlugin::IsInternalPlugin()
{
	return false;
}


void RandomActivePlugin::InitTags(const std::vector<TagInfo> &tagInfos)
{
	int index = 0;
	for (const auto &tag : tagInfos)
	{
		tagValueMap_[++index] = tag;
	}
}
