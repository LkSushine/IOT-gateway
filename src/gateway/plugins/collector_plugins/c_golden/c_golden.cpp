#include "c_golden.h"
#include <spdlog/sinks/daily_file_sink.h>

using namespace spdlog::level;
using namespace gateway::common;

GoldenActivePlugin::GoldenActivePlugin()
	:handle_(-1),
	datetimes_(nullptr),
	ms_(nullptr),
	values_(nullptr),
	states_(nullptr),
	qualities_(nullptr),
	errors_(nullptr),
	errorCount_(0)
{
}

gateway::common::ErrorInfo GoldenActivePlugin::Init(const std::vector<gateway::common::TagInfo> &tagInfos, const std::map<std::string, gateway::common::PluginParam> &pluginCfg, const std::shared_ptr<spdlog::logger> &logPtr)
{
	logPtr_ = logPtr;
	InitCfg(pluginCfg);
	tagInfos_ = tagInfos;
	SPDLOG_LOGGER_CALL(logPtr_, level_enum::debug, "Init plugin success ip={},port={},user={},password={}", ip_,port_,username_,password_);
	return gateway::common::ErrorInfo();
}

gateway::common::ErrorInfo GoldenActivePlugin::Connect()
{
	golden_int32 priv = 0;
	golden_error ret_val = GoE_OK;
	const golden_int32 str_size = 256;
	char name[str_size] = { 0 };
	char msg[str_size] = { 0 };
	ret_val = go_connect(ip_.c_str(), port_, &handle_);
	if (ret_val != GoE_OK) {
		//连接失败...
		go_format_message(ret_val, msg, name, str_size);
		SPDLOG_LOGGER_CALL(logPtr_, level_enum::err, "连接失败 ip={},port={},user={},password={}，ret={},msg={},name={}", ip_, port_,
			username_, password_, ret_val, msg, name);
		collectInfos_.sourceCollectStatus = gateway::common::SourceCollectStatus::kCollectError;
		collectInfos_.sourceCollectMsg = msg;
		collectInfos_.sourceOperator = "检查网络端口是否开通,ip="+ ip_+",port="+std::to_string(port_);
		return gateway::common::ErrorInfo(-1, GetLastError(), "连接失败", gateway::common::ErrorType::kConnectError);
	}
	ret_val = go_login(handle_, username_.c_str(),password_.c_str(), &priv);
	if (ret_val != GoE_OK) {
		//登陆失败...
		go_format_message(ret_val, msg, name, str_size);
		SPDLOG_LOGGER_CALL(logPtr_, level_enum::err, "登陆失败 ip={},port={},user={},password={}，ret={},msg={},name={}", ip_, port_,
			username_, password_, ret_val, msg, name);
		collectInfos_.sourceCollectStatus = SourceCollectStatus::kCollectError;
		collectInfos_.sourceCollectMsg = msg;
		collectInfos_.sourceOperator = "检查用户名密码是否正确,user=" + username_ + ",password=" + password_;
		return gateway::common::ErrorInfo(-1, GetLastError(), "登陆失败", gateway::common::ErrorType::kConnectError);
	}
	collectInfos_.sourceCollectStatus = SourceCollectStatus::kOk;
	collectInfos_.sourceCollectMsg = "";
	collectInfos_.sourceOperator ="";
	SPDLOG_LOGGER_CALL(logPtr_, level_enum::debug, "当前用户权限等级={}", priv);
	InitTags();
	return gateway::common::ErrorInfo();
}

gateway::common::ErrorInfo GoldenActivePlugin::ReConnect()
{
	SPDLOG_LOGGER_CALL(logPtr_, level_enum::err, "重新连接");
	go_disconnect(handle_);
	Connect();
	return gateway::common::ErrorInfo();
}

gateway::common::ErrorInfo GoldenActivePlugin::GetRunInfo(std::vector<gateway::common::SourceCollectInfo> &collectInfos)
{
	collectInfos_.sourceAddr = ip_;
	collectInfos_.sourceName = "庚顿实时库";
	collectInfos.push_back(collectInfos_);
	return gateway::common::ErrorInfo();
}

gateway::common::PluginRunModel GoldenActivePlugin::GetPluginRunModel()
{
	return gateway::common::PluginRunModel::kActive;
}

gateway::common::ErrorInfo GoldenActivePlugin::Read(std::vector<gateway::common::TagInfo> &tagNames, std::vector<gateway::common::TagValue> &tagValues)
{
	try
	{
		auto beignTime = clock();
		if (handle_ < 0)
		{
			SPDLOG_LOGGER_CALL(logPtr_, level_enum::err, " Read connect db error ret ={}", handle_);
			collectInfos_.sourceCollectStatus = gateway::common::SourceCollectStatus::kNetworkError;
			collectInfos_.sourceCollectMsg = "数据库连接失败";
			return gateway::common::ErrorInfo(-1, GetLastError(), "collector_trenddb Reconnect failed", gateway::common::ErrorType::kConnectError);
		}
		
		golden_error retVal = GoE_OK;
		golden_int32 count = existTagIds_.size(); // 需要查询测点数量

		retVal = gos_get_snapshots(handle_, &count, existTagIds_.data(), datetimes_, ms_,
			values_, states_, qualities_, errors_);
		if (retVal != GoE_OK)
		{
			//查询失败
			const golden_int32 str_size = 256;
			char name[str_size] = { 0 };
			char msg[str_size] = { 0 };
			go_format_message(retVal, msg, name, str_size);
			SPDLOG_LOGGER_CALL(logPtr_, level_enum::err, "读取数据失败ret={},msg={},name={}", retVal, msg, name);
			++errorCount_;
			if (errorCount_ < 60)
			{
				return gateway::common::ErrorInfo();
			}
			collectInfos_.sourceCollectStatus = SourceCollectStatus::kCollectError;
			collectInfos_.sourceCollectMsg = msg;
			collectInfos_.sourceOperator = "读取数据失败";
			return gateway::common::ErrorInfo(-1, GetLastError(), "连接失败", gateway::common::ErrorType::kConnectError);
		}

		errorCount_ = 0;
		gateway::common::TagValue tempValue;
		for (int i = 0; i < count; ++i)
		{
			if (errors_[i] != GoE_OK)
			{
				SPDLOG_LOGGER_CALL(logPtr_, level_enum::err, "读取数据失败tagname={},value={},error={}", tagInfos_[i].originalName, values_[i], errors_[i]);
				continue;
			}
			tempValue.SetValue(values_[i], datetimes_[i], ValueStatus::kCollectGood);
			tagNames.push_back(existTagInfos_[i]);
			tagValues.push_back(tempValue);
		}
		SPDLOG_LOGGER_CALL(logPtr_, level_enum::debug, " read over, cost time {}ms ", clock()-beignTime);
		return gateway::common::ErrorInfo();
	}
	catch (std::exception &e)
	{
		SPDLOG_LOGGER_CALL(logPtr_, level_enum::err, " ReadToTrendDB exception = {} ", e.what());
	}
}

gateway::common::ErrorInfo GoldenActivePlugin::Run(
	std::function<gateway::common::ErrorInfo( std::vector<gateway::common::TagInfo>&,  std::vector<gateway::common::TagValue>&)> SetValueFunc,
	std::function<gateway::common::ErrorInfo()> updateNotifyMqttFunc)
{
	return gateway::common::ErrorInfo();
}

bool GoldenActivePlugin::ControlEnable()
{
	return false;
}

bool GoldenActivePlugin::IsInternalPlugin()
{
	return false;
}

gateway::common::ErrorInfo GoldenActivePlugin::Write(const std::vector<gateway::common::TagInfo> &tagNames, const std::vector<gateway::common::TagValue> &tagValues)
{
	return gateway::common::ErrorInfo();
}

void GoldenActivePlugin::InitTags()
{
	golden_int32 count = tagInfos_.size();
	std::vector<golden_int32> existTagIds;
	existTagIds.resize(count);
	std::vector<char*> table_dot_tags(count);
	std::vector<golden_int32> types(count);
	std::vector<golden_int32> classof(count);
	std::vector<golden_int16> useMs(count);
	for (int i = 0; i < count; ++i)
	{
		table_dot_tags[i] = tagInfos_[i].originalName.data();
	}

	golden_error ret_val = gob_find_points(handle_, &count, table_dot_tags.data(), existTagIds.data(),
		types.data(), classof.data(), useMs.data());
	if (ret_val != GoE_OK) {
		//查询失败
		const golden_int32 str_size = 256;
		char name[str_size] = { 0 };
		char msg[str_size] = { 0 };
		go_format_message(ret_val, msg, name, str_size);
		SPDLOG_LOGGER_CALL(logPtr_, level_enum::err, "查询失败ret={},msg={},name={}", ret_val, msg, name);
	}
	else
	{
		delete[] datetimes_;
		delete[] ms_;
		delete[] values_;
		delete[] states_;
		delete[] qualities_;
		delete[] errors_;
		for (int i = 0; i < existTagIds.size(); ++i)
		{
			SPDLOG_LOGGER_CALL(logPtr_, level_enum::trace, "测点name={},tagid={}", table_dot_tags[i], existTagIds[i]);
			if (existTagIds[i] > 0)
			{
				existTagIds_.push_back(existTagIds[i]);
				existTagInfos_.push_back(tagInfos_[i]);
			}
			else
			{
				SPDLOG_LOGGER_CALL(logPtr_, level_enum::err, "测点不存在name={},tagid={}", table_dot_tags[i], existTagIds[i]);
			}
		}
		datetimes_ = new golden_int32[count]{0}; // 输出，时间戳，秒
		ms_ = new golden_int16[count]{ 0 }; // 输出，时间戳，毫秒部分
		values_ = new golden_float64[count]{ 0 }; // 输出，浮点型数值列表
		states_ = new golden_int64[count]{ 0 }; // 输出，实时整型数值列表
		qualities_ = new golden_int16[count]{ 0 }; // 输出，质量码
		errors_ = new golden_error[count]{ 0 }; // 输出，对应错误码列表
	}
}

void GoldenActivePlugin::InitCfg(std::map<std::string, gateway::common::PluginParam> pluginCfg)
{
	if (pluginCfg.count("ip") > 0)
	{
		ip_ = pluginCfg["ip"].paramValue;
	}
	else
	{
		SPDLOG_LOGGER_CALL(logPtr_, level_enum::err, "config loss ip,use default value 127.0.0.1");
	}

	if (pluginCfg.count("port") > 0)
	{
		port_ = std::atoi(pluginCfg["port"].paramValue.c_str());
	}
	else
	{
		SPDLOG_LOGGER_CALL(logPtr_, level_enum::err, "config loss trenddbPort_ ,use default value 20010");
	}

	if (pluginCfg.count("username") > 0)
	{
		username_ = pluginCfg["username"].paramValue;
	}
	else
	{
		SPDLOG_LOGGER_CALL(logPtr_, level_enum::err, "config loss username");
	}

	if (pluginCfg.count("password") > 0)
	{
		password_ = pluginCfg["password"].paramValue;
	}
	else
	{
		SPDLOG_LOGGER_CALL(logPtr_, level_enum::err, "config loss password");
	}
}

