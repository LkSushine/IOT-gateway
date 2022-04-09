#include "c_random_passive.h"
#include <random>
#include <spdlog/sinks/daily_file_sink.h>

using namespace gateway::common;
using namespace spdlog::level;

ErrorInfo RandomPassivePlugin::Init(const std::vector<TagInfo> &tagInfos, const std::map<std::string, PluginParam> &pluginCfg, const std::shared_ptr<spdlog::logger> &logPtr)
{
	InitTags(tagInfos);
	logPtr_ = logPtr;
	SPDLOG_LOGGER_CALL(logPtr_, level_enum::debug, "Init plugin success");
	return ErrorInfo();
}

ErrorInfo RandomPassivePlugin::Connect()
{
	return ErrorInfo();
}

ErrorInfo RandomPassivePlugin::ReConnect()
{
	return ErrorInfo();
}

ErrorInfo RandomPassivePlugin::GetRunInfo(std::vector<gateway::common::SourceCollectInfo> &collectInfos)
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

PluginRunModel RandomPassivePlugin::GetPluginRunModel()
{
	return PluginRunModel::kPassive;
}

ErrorInfo RandomPassivePlugin::Read(std::vector<TagInfo> &tagNames, std::vector<TagValue> &tagValues)
{
	
	return ErrorInfo();
}

ErrorInfo RandomPassivePlugin::Run(
	std::function<ErrorInfo( std::vector<TagInfo>&,  std::vector<TagValue>&)> SetValueFunc,
	std::function<ErrorInfo()> updateNotifyMqttFunc)
{
	int test = 0;
	std::string dataStr;
	while(true)
	{
		std::vector<TagInfo> tagNames;
		std::vector<TagValue> tagValues;
		TagValue tempValue;

		auto timestamp = time(0);
		//std::default_random_engine e(timestamp);
		//std::uniform_real_distribution<float> floatRandomV(0, 100);
		if (test == 0)
		{
			test = 5;
		}
		else if(test==5)
		{
			test = 0;
		}

		for (const auto &sTag : switchTags_)
		{
			tempValue.SetValue((bool)rand() % 2, timestamp, ValueStatus::kCollectGood);
			tagNames.push_back(sTag);
			tagValues.push_back(tempValue);
		}

		for (const auto &aTag : analogTags_)
		{
			tempValue.SetValue(test, timestamp, ValueStatus::kCollectGood);
			tagNames.push_back(aTag);
			tagValues.push_back(tempValue);
		}
		SetValueFunc(tagNames, tagValues);
		updateNotifyMqttFunc();
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}

	
	SPDLOG_LOGGER_CALL(logPtr_, level_enum::debug, "read random plugin success");
	return ErrorInfo();
}

bool RandomPassivePlugin::ControlEnable()
{
	return false;
}

ErrorInfo RandomPassivePlugin::Write(const std::vector<TagInfo> &tagNames, const std::vector<TagValue> &tagValues)
{
	return ErrorInfo();
}

bool RandomPassivePlugin::IsInternalPlugin()
{
	return false;
}


void RandomPassivePlugin::InitTags(const std::vector<TagInfo> &tagInfos)
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
