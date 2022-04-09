#pragma once

#include <map>
#include <nlohmann/json.hpp>
#include <fstream>
#include "task_info.hpp"
namespace gateway
{
	namespace common
	{
		constexpr auto CONFIG_FILE_NAME = "gateway_config.json";

		struct SystemConfig 
		{
			std::string address;	//网关软件连接地址，不可设置为0.0.0.0
			int listenPort;			//"网关软件监听端口，用于访问网页页面"
			std::string logLevel;	//"网关软件jar包日志等级"
			bool guardEnable;		//"是否启用任务守护"
			int guardTime;			//"任务守护超时时间，单位为秒"
			std::string addressAndPort;
			SystemConfig():
				address("127.0.0.1"),
				listenPort(6688),
				logLevel("error"),
				guardEnable(true),
				guardTime(300),
				addressAndPort("127.0.0.1:6688")
			{}
		};

		struct RealCacheConfig
		{
			std::string address;	//"缓存服务连接地址，不可设置为0.0.0.0",
			int listenPort;			//"缓存服务监听端口",
			int logLevel;	//"缓存服务日志等级",
			int defaultSize;		//"默认缓存数组大小",
			float maxMemMbSize;		//"默认缓存最大内存限制，单位MB"
			std::string addressAndPort;
			RealCacheConfig() :
				address("127.0.0.1"),
				listenPort(6677),
				logLevel(3),
				defaultSize(1000000),
				maxMemMbSize(1024*1.8),
				addressAndPort("127.0.0.1:6688") {}
		};

		struct CollectorTaskConfig
		{
			int logLevel;	//"采集任务日志等级",
			CollectorTaskConfig() :logLevel(3) {}
		};

		struct TransmitterTaskConfig
		{
			int logLevel;		//"转发任务日志等级",
			TransmitterTaskConfig() :logLevel(3) {}
		};

		struct VibrationCollectorTaskConfig
		{
			int logLevel;		//"振动采集日志等级",
			VibrationCollectorTaskConfig() :logLevel(3) {}
		};

		struct VibrationTransmitterTaskConfig
		{
			int logLevel;		//"振动转发日志等级",
			VibrationTransmitterTaskConfig() :logLevel(3) {}
		};

		struct ServerInstallConfig
		{
			std::string systemUser;
			std::string systemPassword;
			std::string javaRunParams;
			std::string jarRunParams;
			int logLevel;		//"服务安装日志等级",
			ServerInstallConfig() :logLevel(3) {}
		};
		struct CofigFileInfo
		{
			SystemConfig systemCofig;
			RealCacheConfig realcacheConfig;
			CollectorTaskConfig collectorConfig;
			TransmitterTaskConfig transmitterConfig;
			VibrationCollectorTaskConfig vibrationCollectorConfig;
			VibrationTransmitterTaskConfig vibrationTransmitterConfig;
			ServerInstallConfig installConfig;
		};


		class TopicConfig
		{
		public:
			static std::string GetClientId(const std::string &taskName, const TaskType &taskType)
			{
				switch (taskType)
				{
				case TaskType::kCollector:
					return std::string("collector_" + taskName);
				case TaskType::kTransmitter:
					return std::string("transmitter_" + taskName);
				case TaskType::kVibrationCollector:
					return std::string("vibration_collector_" + taskName);
				case TaskType::kVibrationTrans:
					return std::string("vibration_transmitter_" + taskName);
				}
			}
			
			static std::string GetUpdateTopic(const std::string &taskName, const TaskType &taskType)
			{
				switch (taskType)
				{
				case TaskType::kCollector:
					return std::string("gateway/collector/" + taskName + "/update");
				case TaskType::kVibrationCollector:
					return std::string("gateway/vibration_collector/" + taskName + "/update");
				}
			}

			static std::string GetControlTopic(const std::string &taskName, const TaskType &taskType)
			{
				switch (taskType)
				{
				case TaskType::kCollector:
					return std::string("gateway/collector/" + taskName + "/control");
				case TaskType::kVibrationCollector:
					return std::string("gateway/vibration_collector/" + taskName + "/control");
				}
			}
		};

		
		class Config
		{
		public:
			static bool GetCofigInfo(const std::string &cfgPath, CofigFileInfo& cfg)
			{
				try
				{
					std::ifstream inputData(cfgPath);
					if (inputData.is_open())
					{
						nlohmann::json tempJson;
						inputData >> tempJson;
						FromJson(tempJson, cfg);
						inputData.close();
						return true;
					}
					else
					{
						return false;
					}
				}
				catch (std::exception& e)
				{
					printf("%s", e.what());
				}
			}
		private:
			static int StrLogToSpdlogLevel(const std::string& strLog)
			{
				std::map<std::string, int> logStrToEnumMap = { { "Trace",0 },{"trace",0},{"TRACE",0},
						{ "Debug",1 },{"debug",1},{"DEBUG",1},
						{ "Info",2 },{"info",2},{"INFO",2},
						{ "Warning",3 },{"warn",3},{"warning",3},{"WARN",0},{"WARNING",3},
						{ "Error",4 },{"error",4},{"ERROR",4},
						{ "Critical",5 },{"critical",5},{"CRITICAL",5},
						{ "Off",6 },{"off",6},{"OFF",6} };

				if (logStrToEnumMap.count(strLog) > 0)
				{
					return logStrToEnumMap[strLog];
				}
				//默认返回Warning
				return 3;
			}

			static bool FromJson(const nlohmann::json &tempJson, CofigFileInfo& cfg)
			{
				try
				{
					//系统配置
					cfg.systemCofig.address = tempJson["system_config"]["address"].get<std::string>();
					cfg.systemCofig.listenPort = tempJson["system_config"]["listen_port"].get<int>();
					cfg.systemCofig.logLevel = tempJson["system_config"]["log_level"].get<std::string>();
					cfg.systemCofig.guardEnable = tempJson["system_config"]["guard_enable"].get<bool>();
					cfg.systemCofig.guardTime = tempJson["system_config"]["guard_time"].get<int>();
					cfg.systemCofig.addressAndPort = cfg.systemCofig.address+":"+std::to_string(cfg.systemCofig.listenPort);
					//缓存配置
					cfg.realcacheConfig.address = tempJson["realcache_config"]["address"].get<std::string>();
					cfg.realcacheConfig.listenPort = tempJson["realcache_config"]["listen_port"].get<int>();
					cfg.realcacheConfig.logLevel = StrLogToSpdlogLevel(tempJson["realcache_config"]["log_level"].get<std::string>());
					cfg.realcacheConfig.defaultSize = tempJson["realcache_config"]["default_size"].get<int>();
					cfg.realcacheConfig.maxMemMbSize = tempJson["realcache_config"]["max_mem_size"].get<float>();
					cfg.realcacheConfig.addressAndPort = cfg.realcacheConfig.address + ":" + std::to_string(cfg.realcacheConfig.listenPort);
					//采集任务配置
					cfg.collectorConfig.logLevel = StrLogToSpdlogLevel(tempJson["collector"]["log_level"].get<std::string>());
					//转发任务配置
					cfg.transmitterConfig.logLevel = StrLogToSpdlogLevel(tempJson["transmitter"]["log_level"].get<std::string>());
					//振动采集任务配置
					cfg.vibrationCollectorConfig.logLevel = StrLogToSpdlogLevel(tempJson["vibration_collector"]["log_level"].get<std::string>());
					//振动转发任务配置
					cfg.vibrationTransmitterConfig.logLevel = StrLogToSpdlogLevel(tempJson["vibration_transmitter"]["log_level"].get<std::string>());
					cfg.installConfig.systemUser = tempJson["server_install"]["system_username"].get<std::string>();
					cfg.installConfig.systemPassword = tempJson["server_install"]["system_password"].get<std::string>();
					cfg.installConfig.logLevel = StrLogToSpdlogLevel(tempJson["server_install"]["log_level"].get<std::string>());
					cfg.installConfig.javaRunParams = tempJson["server_install"]["java_run_params"].get<std::string>();
					cfg.installConfig.jarRunParams = tempJson["server_install"]["jar_run_params"].get<std::string>();
					return true;
				}
				catch (std::exception &e)
				{
					printf("%s", e.what());
					return true;
				}
			}
		};
		
	}//common
	
}//gateway
