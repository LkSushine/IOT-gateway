#pragma once

#include <string>

namespace gateway
{
	namespace common
	{
		//任务类型枚举
		enum class TaskType :int8_t
		{
			kCollector = 0,		//采集任务
			kTransmitter,		//转发任务
			kVibrationCollector,//振动采集任务
			kVibrationTrans		//振动转发任务
		};
		
		//网关软件任务基础信息
		struct TaskInfo
		{
			std::string taskName;		//任务名称
			std::string pluginName;		//协议名称
			std::string taskId;			//任务标识
			std::string taskDesc;		//任务描述
			int timeCycle;			//采集/转发周期
			TaskType taskType;			//任务类型
			TaskInfo():timeCycle(1000){}
		};

		//网关软件系统配置信息
		struct SystemInfo
		{
			std::string siteId;				//站点ID
			std::string siteName;			//站点名称
			bool gapExistFlag;				//下级节点是否存在网闸
			std::string gatewayAddrPort;	//网关软件java后台监听地址端口
			bool mqttEnable;				//是否启用mqtt
			std::string mqttAddr;			//mqtt地址
			int mqttPort;					//mqtt端口
			std::string mqttUserName;			//mqtt用户名
			std::string mqttPassWord;			//mqtt密码
			bool cacheEnable;				//是否启用缓存
			int saveDays;					//缓存的天数
			std::string localIP;           //本地IP
			int saveLogDays;              //日志保存的天数
			SystemInfo():mqttEnable(false),
				mqttPort(1883),
				cacheEnable(false),
				saveDays(3),
				gapExistFlag(false)
			{}
		};


		//节点类型枚举
		enum class NodeRunStatus :int8_t
		{
			kStarting = 0,//starting	String	启动中
			kRunning,//running	String	运行中
			kStopped,//stopped	String	已停止
			kWarning,//warning	String	警告中
			kFault//fault	String	故障中
		};

		//节点基础信息
		struct NodeBaseInfo
		{
			std::string nodeName;
			std::string pluginName;
			std::string addr;
			std::string status;
		};

		//节点详细信息
		struct NodeDetailInfo
		{
			std::string statusMsg;
			std::string operatorStr;
			std::string mem;
			std::string netRecvSpeed;
			std::string netSendSpeed;
			std::string cacheInfo;
			std::string cpuInfo;
			uint64_t date;
			NodeDetailInfo():date(0){}
		};

		//节点类型枚举
		enum class NodeType :int8_t
		{
			kSite = 0,			//site	String	站点类型
			kDataSource,		//dataSource	String	数据源类型
			kNetsBrake,			//netsBrake	String	网闸节点类型
			kDestination,		//destination	String	目的地节点类型
			kCollectionTaskNode,//collectionTaskNode	String	采集任务节点类型
			kForwardTaskNode,	//forwardTaskNode	String	转发任务节点类型
			kComputingTaskNode,	//computingTaskNode	String	计算任务节点类型
			kModelTaskNode,		//modelTaskNode	String	模型任务节点类型
			kVibrationAcquistionNode,//vibrationAcquisitionNode	String	振动采集节点类型
			kVibrationForwardNode	//vibrationForwardNode	String	振动转发节点类型
		};

		//节点信息
		struct NodeInfo
		{
			std::string siteId;
			std::string siteName;
			std::string nodeId;
			NodeType nodeType;
			NodeBaseInfo baseInfo;
			NodeDetailInfo detailInfo;

			std::string GetNodeType()
			{
				switch (nodeType)
				{
				case NodeType::kSite: return "site";
				case NodeType::kDataSource: return "dataSource";
				case NodeType::kNetsBrake: return "netsBrake";
				case NodeType::kDestination: return "destination";
				case NodeType::kCollectionTaskNode: return "collectionTaskNode";
				case NodeType::kForwardTaskNode: return "forwardTaskNode";
				case NodeType::kComputingTaskNode: return "computingTaskNode";
				case NodeType::kModelTaskNode: return "modelTaskNode";
				case NodeType::kVibrationAcquistionNode: return "vibrationAcquisitionNode";
				case NodeType::kVibrationForwardNode: return "vibrationForwardNode";
				default:
					return "";
				}
			}

			static std::string GetNodeType(NodeType nodeTempType)
			{
				switch (nodeTempType)
				{
				case NodeType::kSite: return "site";
				case NodeType::kDataSource: return "dataSource";
				case NodeType::kNetsBrake: return "netsBrake";
				case NodeType::kDestination: return "destination";
				case NodeType::kCollectionTaskNode: return "collectionTaskNode";
				case NodeType::kForwardTaskNode: return "forwardTaskNode";
				case NodeType::kComputingTaskNode: return "computingTaskNode";
				case NodeType::kModelTaskNode: return "modelTaskNode";
				case NodeType::kVibrationAcquistionNode: return "vibrationAcquisitionNode";
				case NodeType::kVibrationForwardNode: return "vibrationForwardNode";
				default:
					return "";
				}
			}

			static std::string GenNodeId(std::string &siteId, NodeType nodeType, std::string taskId,int index =0)
			{
				switch (nodeType)
				{
				case gateway::common::NodeType::kSite:
					return siteId;
				case gateway::common::NodeType::kDataSource:
					return siteId + "_" + GetNodeType(nodeType) + "_" + taskId + "_source_" + std::to_string(index);
				case gateway::common::NodeType::kNetsBrake:
					break;
				case gateway::common::NodeType::kDestination:
					return siteId + "_" + GetNodeType(nodeType) + "_" + taskId + "_target_" + std::to_string(index);
				case gateway::common::NodeType::kCollectionTaskNode:
				case gateway::common::NodeType::kForwardTaskNode:
				case gateway::common::NodeType::kComputingTaskNode:
				case gateway::common::NodeType::kModelTaskNode:
				case gateway::common::NodeType::kVibrationAcquistionNode:
				case gateway::common::NodeType::kVibrationForwardNode:
					return siteId + "_" + GetNodeType(nodeType) + "_" + taskId;
				default:
					return "";
				}
			}

			std::string GetNodeRunStatus()
			{
				return baseInfo.status;
				/*switch (baseInfo.status)
				{
					case NodeRunStatus::kStarting: return "starting";
					case NodeRunStatus::kRunning: return "running";
					case NodeRunStatus::kStopped: return "stopped";
					case NodeRunStatus::kWarning: return "warning";
					case NodeRunStatus::kFault: return "fault";
					default:
						return "";
				}*/
			}
		};

		//连线状态枚举
		enum class EdgeStatus :int8_t
		{
			kOnline =0,		//在线，网络通讯正常online
			kOffline		//离线，网络异常offline
		};

		//连线信息
		struct EdgeInfo
		{
			std::string source;			//源节点nodeID
			std::string target;			//目标节点nodeID
			EdgeStatus status;			//连线状态
			std::string label;			//连线网速信息
			bool gapExistFlag;			//是否存在网闸
			std::string GetEdgeStatus()
			{
				switch (status)
				{
				case EdgeStatus::kOnline: return "online";
				case EdgeStatus::kOffline: return "offline";
				}
			}
		};

		//上报节点状态结构
		struct NodePostInfo
		{
			std::string siteId;
			uint64_t dataTime;
			std::vector<NodeInfo> nodes;
			std::vector<EdgeInfo> edges;
		};

		//节点上报错误枚举
		enum class NodeErrorLevel :int8_t
		{
			kInfo = 0,		//信息information
			kWarn,			//警告warning
			kFault			//故障fault
		};

		//报警信息上报信息
		struct NodeAlarmInfo
		{
			std::string siteId;
			std::string siteName;
			std::string nodeId;
			std::string nodeName;
			NodeErrorLevel errorLevel;
			std::string errorDesc;
			uint64_t errorTime;
			std::string operatorSuggest;
		};

		//任务运行状态报警等级枚举
		enum class TaskRunAlarmLevel :int8_t
		{
			kOk = 0,		//运行正常
			kWarn,			//警告
			kError			//错误
		};

		//网关软件任务运行状态信息
		struct TaskRunInfo
		{
			TaskRunAlarmLevel mqttAlarmLevel;
			std::string mqttAlarmMsg;
			std::string mqttOperatorStr;

			TaskRunAlarmLevel cacheAlarmLevel;
			std::string cacheAlarmMsg;
			std::string cacheOperatorStr;

			TaskRunAlarmLevel pluginAlarmLevel;
			std::string pluginAlarmMsg;
			std::string pluginOperatorStr;

			float cpuUsage;
			float memUsage;
			int pid;
			bool isFirstReport;	//是否是第一次上传运行状态信息
			TaskRunInfo() :
			mqttAlarmLevel(TaskRunAlarmLevel::kOk),
			cacheAlarmLevel(TaskRunAlarmLevel::kOk),
			pluginAlarmLevel(TaskRunAlarmLevel::kOk),
			cpuUsage(0),
			memUsage(0),
			pid(0),
			isFirstReport(true){};
			friend std::ostream& operator << (std::ostream& os, const TaskRunInfo &value)
			{
				os << "mqtt alarm level = " << static_cast<int>(value.mqttAlarmLevel) << ",msg = " << value.mqttAlarmMsg << std::endl;
				os << "cache alarm level = " << static_cast<int>(value.cacheAlarmLevel) << ",msg = " << value.cacheAlarmMsg << std::endl;
				os << "plugin alarm level = " << static_cast<int>(value.pluginAlarmLevel) << ",msg = " << value.pluginAlarmMsg << std::endl;
				return os;
			}

			inline bool operator == (const TaskRunInfo &value)
			{
				return (this->cacheAlarmLevel == value.cacheAlarmLevel) && (this->mqttAlarmLevel == value.mqttAlarmLevel) && (this->pluginAlarmLevel == value.pluginAlarmLevel);
			}

			std::pair<std::string, std::string> GetTaskAlarmMsg()
			{
				TaskRunAlarmLevel tempLevel;
				std::string tempMsg;
				std::string statusStr;

				tempLevel = mqttAlarmLevel;
				tempMsg = mqttAlarmMsg;

				if(tempLevel< cacheAlarmLevel)
				{
					tempLevel = cacheAlarmLevel;
					tempMsg = cacheAlarmMsg;
				}

				if(tempLevel< pluginAlarmLevel)
				{
					tempLevel = pluginAlarmLevel;
					tempMsg = pluginAlarmMsg;
				}

				switch (tempLevel)
				{
					case TaskRunAlarmLevel::kOk:
					{
						statusStr = "running";
						break;
					}
					case TaskRunAlarmLevel::kWarn:
					{
						statusStr = "warning";
						break;
					}
					case TaskRunAlarmLevel::kError:
					{
						statusStr = "fault";
						break;
					}
					default:
						statusStr = "running";
						break;
				}
				return std::make_pair(statusStr, tempMsg);
			}


			void GetTaskAlarmReportMsg(std::string &tempLevelStr,std::string &tempMsg,std::string &operatorStr)
			{
				TaskRunAlarmLevel tempLevel;
				tempLevel = mqttAlarmLevel;
				tempMsg = mqttAlarmMsg;
				operatorStr = mqttOperatorStr;
				if (tempLevel < cacheAlarmLevel)
				{
					tempLevel = cacheAlarmLevel;
					tempMsg = cacheAlarmMsg;
					operatorStr = cacheOperatorStr;
				}

				if (tempLevel < pluginAlarmLevel)
				{
					tempLevel = pluginAlarmLevel;
					tempMsg = pluginAlarmMsg;
					operatorStr = pluginOperatorStr;
				}

				switch (tempLevel)
				{
					case TaskRunAlarmLevel::kOk:
						{
						tempLevelStr = "normal";
						break;
						}
					case TaskRunAlarmLevel::kWarn:
					{
						tempLevelStr = "warning";
						break;
					}
					case TaskRunAlarmLevel::kError:
					{
						tempLevelStr = "fault";
						break;
					}
				}
			}
		};
	}//common
}