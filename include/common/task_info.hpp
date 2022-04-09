#pragma once

#include <string>

namespace gateway
{
	namespace common
	{
		//��������ö��
		enum class TaskType :int8_t
		{
			kCollector = 0,		//�ɼ�����
			kTransmitter,		//ת������
			kVibrationCollector,//�񶯲ɼ�����
			kVibrationTrans		//��ת������
		};
		
		//����������������Ϣ
		struct TaskInfo
		{
			std::string taskName;		//��������
			std::string pluginName;		//Э������
			std::string taskId;			//�����ʶ
			std::string taskDesc;		//��������
			int timeCycle;			//�ɼ�/ת������
			TaskType taskType;			//��������
			TaskInfo():timeCycle(1000){}
		};

		//�������ϵͳ������Ϣ
		struct SystemInfo
		{
			std::string siteId;				//վ��ID
			std::string siteName;			//վ������
			bool gapExistFlag;				//�¼��ڵ��Ƿ������բ
			std::string gatewayAddrPort;	//�������java��̨������ַ�˿�
			bool mqttEnable;				//�Ƿ�����mqtt
			std::string mqttAddr;			//mqtt��ַ
			int mqttPort;					//mqtt�˿�
			std::string mqttUserName;			//mqtt�û���
			std::string mqttPassWord;			//mqtt����
			bool cacheEnable;				//�Ƿ����û���
			int saveDays;					//���������
			std::string localIP;           //����IP
			int saveLogDays;              //��־���������
			SystemInfo():mqttEnable(false),
				mqttPort(1883),
				cacheEnable(false),
				saveDays(3),
				gapExistFlag(false)
			{}
		};


		//�ڵ�����ö��
		enum class NodeRunStatus :int8_t
		{
			kStarting = 0,//starting	String	������
			kRunning,//running	String	������
			kStopped,//stopped	String	��ֹͣ
			kWarning,//warning	String	������
			kFault//fault	String	������
		};

		//�ڵ������Ϣ
		struct NodeBaseInfo
		{
			std::string nodeName;
			std::string pluginName;
			std::string addr;
			std::string status;
		};

		//�ڵ���ϸ��Ϣ
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

		//�ڵ�����ö��
		enum class NodeType :int8_t
		{
			kSite = 0,			//site	String	վ������
			kDataSource,		//dataSource	String	����Դ����
			kNetsBrake,			//netsBrake	String	��բ�ڵ�����
			kDestination,		//destination	String	Ŀ�ĵؽڵ�����
			kCollectionTaskNode,//collectionTaskNode	String	�ɼ�����ڵ�����
			kForwardTaskNode,	//forwardTaskNode	String	ת������ڵ�����
			kComputingTaskNode,	//computingTaskNode	String	��������ڵ�����
			kModelTaskNode,		//modelTaskNode	String	ģ������ڵ�����
			kVibrationAcquistionNode,//vibrationAcquisitionNode	String	�񶯲ɼ��ڵ�����
			kVibrationForwardNode	//vibrationForwardNode	String	��ת���ڵ�����
		};

		//�ڵ���Ϣ
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

		//����״̬ö��
		enum class EdgeStatus :int8_t
		{
			kOnline =0,		//���ߣ�����ͨѶ����online
			kOffline		//���ߣ������쳣offline
		};

		//������Ϣ
		struct EdgeInfo
		{
			std::string source;			//Դ�ڵ�nodeID
			std::string target;			//Ŀ��ڵ�nodeID
			EdgeStatus status;			//����״̬
			std::string label;			//����������Ϣ
			bool gapExistFlag;			//�Ƿ������բ
			std::string GetEdgeStatus()
			{
				switch (status)
				{
				case EdgeStatus::kOnline: return "online";
				case EdgeStatus::kOffline: return "offline";
				}
			}
		};

		//�ϱ��ڵ�״̬�ṹ
		struct NodePostInfo
		{
			std::string siteId;
			uint64_t dataTime;
			std::vector<NodeInfo> nodes;
			std::vector<EdgeInfo> edges;
		};

		//�ڵ��ϱ�����ö��
		enum class NodeErrorLevel :int8_t
		{
			kInfo = 0,		//��Ϣinformation
			kWarn,			//����warning
			kFault			//����fault
		};

		//������Ϣ�ϱ���Ϣ
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

		//��������״̬�����ȼ�ö��
		enum class TaskRunAlarmLevel :int8_t
		{
			kOk = 0,		//��������
			kWarn,			//����
			kError			//����
		};

		//���������������״̬��Ϣ
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
			bool isFirstReport;	//�Ƿ��ǵ�һ���ϴ�����״̬��Ϣ
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