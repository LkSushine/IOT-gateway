#pragma once

#include "multi_value.hpp"
#include <string>

namespace gateway
{
	namespace common
	{
		//测点类型枚举
		enum class TagType :int8_t
		{
			kSwitch = 0,		//开关量
			kAnalog,			//模拟量
			kControl			//控制量
		};

		//上位机/数据源采集状态枚举
		enum class SourceCollectStatus :int8_t
		{
			kStop = 0,          //任务停止
			kOk,				//采集正常
			kNetworkError,      //网络异常，ping不通
			kConnectPortError,	//网络异常，ping通，连接不上对应端口
			kCollectError,		//网络正常，采集异常
			kCollectApartError	//一部分采集异常
		};

		//错误等级枚举
		enum class PluginAlarmLevel :int8_t
		{
			kOk = 0,			//正常
			kWarn,				//警告
			kError,				//错误
		};


		//数据源/上位机运行状态
		struct SourceCollectInfo
		{
			std::string nodeId;						//内置udp传输协议时，前一节点发送的转发任务对应的nodeId
			std::string sourceName;						//上位机/数据源名称
			std::string sourceAddr;						//上位机/数据源的地址/端口号/串口号
			std::string pluginName;						//采用所用协议名
			std::string sourceCollectMsg;				//数据源采集信息
			std::string sourceOperator;					//操作建议
			SourceCollectStatus sourceCollectStatus;	//数据源采集状态
			PluginAlarmLevel pluginAlarmLevel;
			bool gapExist;								//与数据源之间是否存在网闸
			SourceCollectInfo():
				sourceCollectStatus(SourceCollectStatus::kOk),
				pluginAlarmLevel(PluginAlarmLevel::kOk),gapExist(false)
			{
			}

			std::string GetStatus()
			{
				std::string statusStr;
				switch (pluginAlarmLevel)
				{
				case PluginAlarmLevel::kOk:
				{
					statusStr = "normal";
					break;
				}
				case PluginAlarmLevel::kWarn:
				{
					statusStr = "warning";
					break;
				}
				case PluginAlarmLevel::kError:
				{
					statusStr = "fault";
					break;
				}
				default:
					statusStr = "normal";
					break;
				}
				return statusStr;
			}
		};

		//协议参数类型枚举
		enum class ParamValueType :int8_t
		{
			kInt = 0,		//数值
			kString,		//字符串
			kBool,			//布尔/单选
			kCheckBox,		//多选
		};

		//协议运行模式枚举
		enum class PluginRunModel :int8_t
		{
			kActive = 0,		//主动模式
			kPassive			//被动模式
		};

		//协议参数
		struct PluginParam
		{
			ParamValueType valueType;		//协议参数值类型
			std::string paramValue;			//协议参数值
			std::string defaultValue;		//协议参数默认值
			std::string paramDesc;			//协议参数描述
			void TypeFromStr(const std::string &str)
			{
				if(str == "str")
				{
					valueType = ParamValueType::kString;
				}
				else if(str == "bool" || str == "radio")
				{
					valueType = ParamValueType::kBool;
				}
				else if (str == "number")
				{
					valueType = ParamValueType::kInt;
				}
				else if (str == "checkbox")
				{
					valueType = ParamValueType::kCheckBox;
				}
			}
		};

		//测点基础信息
		struct TagInfo
		{
			std::string standardName;		//标准点名
			std::string originalName;	//原始点名
			std::string tagDesc;		//测点描述
			std::string taskIdentifier;		//测点对应的采集任务标识
			TagType tagType;			//测点类型
			ValueType valueType;		//测点值类型
			float offset;				//偏移量
			float rate;					//倍率
			bool  filterEnable;			//是否启用过滤
			float maxFilterValue;		//最大过滤值，超过该值则过滤
			float minFilterValue;		//最小过滤值，低于该值则过滤
			int sortId;
			TagInfo():offset(0),
				rate(1),
				filterEnable(false),
				maxFilterValue(0),
				minFilterValue(0)
			{}

			bool operator<(const TagInfo& tagR) const
			{
				return this->standardName < tagR.standardName; 
			};

			bool operator==(const TagInfo& tagR) const
			{
				return this->standardName == tagR.standardName;
			};
			
			bool operator==(const std::string& standardName) const
			{
				return this->standardName == standardName;
			};

			void TagTypeFromStr(const std::string tagTypeStr)
			{
				if(tagTypeStr == "ANALOG")
				{
					tagType = TagType::kAnalog;
				}
				else if (tagTypeStr == "SWITCH")
				{
					tagType = TagType::kSwitch;
				}
				else if (tagTypeStr == "CONTROL")
				{
					tagType = TagType::kControl;
				}
			}
			void ValueTypeFromStr(const std::string valueTypeStr)
			{
				if (valueTypeStr == "float")
				{
					valueType = ValueType::kFloat;
				}
				else if(valueTypeStr == "double")
				{
					valueType = ValueType::kDouble;
				}
				else if (valueTypeStr == "bool")
				{
					valueType = ValueType::kBool;
				}
				else if (valueTypeStr == "int8_t")
				{
					valueType = ValueType::kChar;
				}
				else if (valueTypeStr == "uint8_t")
				{
					valueType = ValueType::kByte;
				}
				else if (valueTypeStr == "int16_t")
				{
					valueType = ValueType::kShort;
				}
				else if (valueTypeStr == "uint16_t")
				{
					valueType = ValueType::kWord;
				}
				else if (valueTypeStr == "int32_t")
				{
					valueType = ValueType::kInt;
				}
				else if (valueTypeStr == "uint32_t")
				{
					valueType = ValueType::kDWord;
				}
				else if (valueTypeStr == "int64_t")
				{
					valueType = ValueType::kLong;
				}
				else if (valueTypeStr == "uint64_t")
				{
					valueType = ValueType::kULong;
				}
				else if (valueTypeStr == "string")
				{
					valueType = ValueType::kString;
				}
				else if (valueTypeStr == "float array")
				{
					valueType = ValueType::kFloatArray;
				}
				else if (valueTypeStr == "double array")
				{
					valueType = ValueType::kDoubleArray;
				}
			}
		};

		struct DeviceGroupInfo
		{
			std::string groupName;
			std::string groupDesc;
			std::string transTopic;
			bool transEnable;
			DeviceGroupInfo() {}
			DeviceGroupInfo(std::string gName) :groupName(gName) {}

			bool operator<(const DeviceGroupInfo& groupR) const
			{
				return this->groupName < groupR.groupName;
			};
		};
	}//common
	
}//gateway

