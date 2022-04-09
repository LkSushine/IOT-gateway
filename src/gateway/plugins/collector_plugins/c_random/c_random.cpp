#include "c_random.h"
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
	collectInfo.pluginAlarmLevel = gateway::common::PluginAlarmLevel::kOk;
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
	tagNames.clear();
	tagValues.clear();

	TagValue tempValue;

	auto timestamp = time(0);
	std::default_random_engine e(timestamp);
	std::uniform_real_distribution<float> floatRandomV(0, 100);
	std::vector<float> dataList;
	for (int i = 0; i < 100; ++i)
	{
		dataList.push_back(floatRandomV(e));
	}

	for (const auto &sTag : switchTags_)
	{
		tempValue.SetValue((bool)rand()%2, timestamp, ValueStatus::kCollectGood);
		tagNames.push_back(sTag);
		tagValues.push_back(tempValue);
	}
	int j = 0;
	for (const auto &aTag : analogTags_)
	{
		tempValue.SetValue(dataList[j], timestamp, ValueStatus::kCollectGood);
		tagNames.push_back(aTag);
		tagValues.push_back(tempValue);
		if (j == 99)
		{
			j = 0;
		}
		else
		{
			++j;
		}
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
	for (const auto &tag : tagInfos)
	{
		switch (tag.tagType)
		{
		case TagType::kSwitch:
		{
			switchTags_.push_back(tag);
			break;
		}
		case TagType::kAnalog:
		{
			analogTags_.push_back(tag);
			break;
		}
		case TagType::kControl:
		{
			controlTags_.push_back(tag);
			break;
		}
		default:
		{
			analogTags_.push_back(tag);
			break;
		}
		}
	}
}
