#pragma once

#include "multi_value.hpp"
#include <string>

namespace gateway
{
	namespace common
	{
		//�������ö��
		enum class TagType :int8_t
		{
			kSwitch = 0,		//������
			kAnalog,			//ģ����
			kControl			//������
		};

		//��λ��/����Դ�ɼ�״̬ö��
		enum class SourceCollectStatus :int8_t
		{
			kStop = 0,          //����ֹͣ
			kOk,				//�ɼ�����
			kNetworkError,      //�����쳣��ping��ͨ
			kConnectPortError,	//�����쳣��pingͨ�����Ӳ��϶�Ӧ�˿�
			kCollectError,		//�����������ɼ��쳣
			kCollectApartError	//һ���ֲɼ��쳣
		};

		//����ȼ�ö��
		enum class PluginAlarmLevel :int8_t
		{
			kOk = 0,			//����
			kWarn,				//����
			kError,				//����
		};


		//����Դ/��λ������״̬
		struct SourceCollectInfo
		{
			std::string nodeId;						//����udp����Э��ʱ��ǰһ�ڵ㷢�͵�ת�������Ӧ��nodeId
			std::string sourceName;						//��λ��/����Դ����
			std::string sourceAddr;						//��λ��/����Դ�ĵ�ַ/�˿ں�/���ں�
			std::string pluginName;						//��������Э����
			std::string sourceCollectMsg;				//����Դ�ɼ���Ϣ
			std::string sourceOperator;					//��������
			SourceCollectStatus sourceCollectStatus;	//����Դ�ɼ�״̬
			PluginAlarmLevel pluginAlarmLevel;
			bool gapExist;								//������Դ֮���Ƿ������բ
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

		//Э���������ö��
		enum class ParamValueType :int8_t
		{
			kInt = 0,		//��ֵ
			kString,		//�ַ���
			kBool,			//����/��ѡ
			kCheckBox,		//��ѡ
		};

		//Э������ģʽö��
		enum class PluginRunModel :int8_t
		{
			kActive = 0,		//����ģʽ
			kPassive			//����ģʽ
		};

		//Э�����
		struct PluginParam
		{
			ParamValueType valueType;		//Э�����ֵ����
			std::string paramValue;			//Э�����ֵ
			std::string defaultValue;		//Э�����Ĭ��ֵ
			std::string paramDesc;			//Э���������
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

		//��������Ϣ
		struct TagInfo
		{
			std::string standardName;		//��׼����
			std::string originalName;	//ԭʼ����
			std::string tagDesc;		//�������
			std::string taskIdentifier;		//����Ӧ�Ĳɼ������ʶ
			TagType tagType;			//�������
			ValueType valueType;		//���ֵ����
			float offset;				//ƫ����
			float rate;					//����
			bool  filterEnable;			//�Ƿ����ù���
			float maxFilterValue;		//������ֵ��������ֵ�����
			float minFilterValue;		//��С����ֵ�����ڸ�ֵ�����
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

