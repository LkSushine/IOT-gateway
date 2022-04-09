#pragma once
#include <spdlog/spdlog.h>
#include <map>
#include "tag_info.hpp"
#include "error_info.hpp"
#include "task_info.hpp"

namespace gateway
{
	namespace common
	{
		class TransmitterPlugin
		{
		public:
			/*
			*���ܣ���ʼ��Э����
			*��Σ�
			*taskId:ת������ID
			*tagInfos:ת����ʼ������б�
			*pluginCfg:Э��������ݣ�keyΪ������ʶ��valueΪЭ�������Ϣ
			logPtr:��־������ָ��
			*���Σ�
			*��
			*����ֵ��
			* CollectErrorInfo.retCode:�����룬����0Ϊ����ֵ����0Ϊ�쳣ֵ
			* CollectErrorInfo.systemCode:ϵͳ������
			* CollectErrorInfo.errorMsg:������Ϣ���������ؿգ��쳣�����쳣��Ϣ
			* CollectErrorInfo.errType;��������ö��
			*/
			virtual ErrorInfo Init(const gateway::common::TaskInfo &taskInfo, const gateway::common::SystemInfo &sysInfo, const std::vector<TagInfo> &tagInfos, const std::map<std::string, PluginParam> &pluginCfg, const std::shared_ptr<spdlog::logger> &logPtr) = 0;

			/*
			*���ܣ������¿ػص�����
			*��Σ�
			*controlFunc:�¿ػص�����
			*���Σ�
			*��
			*����ֵ��
			*��
			*/
			virtual void SetControlCallBack(const std::function<void (const TagInfo&,const TagValue&)> controlFunc) = 0;

			
			/*
			*���ܣ�����Ŀ�ĵ�
			*��Σ�
			*��
			*���Σ�
			*��
			*����ֵ��
			* CollectErrorInfo.retCode:�����룬����0Ϊ����ֵ����0Ϊ�쳣ֵ
			* CollectErrorInfo.systemCode:ϵͳ������
			* CollectErrorInfo.errorMsg:������Ϣ���������ؿգ��쳣�����쳣��Ϣ
			* CollectErrorInfo.errType;��������ö��
			*/
			virtual ErrorInfo Connect() = 0;

			/*
			*���ܣ������쳣ʱ������Ŀ�ĵ�
			*��Σ�
			*��
			*���Σ�
			*��
			*����ֵ��
			* CollectErrorInfo.retCode:�����룬����0Ϊ����ֵ����0Ϊ�쳣ֵ
			* CollectErrorInfo.systemCode:ϵͳ������
			* CollectErrorInfo.errorMsg:������Ϣ���������ؿգ��쳣�����쳣��Ϣ
			* CollectErrorInfo.errType;��������ö��
			*/
			virtual ErrorInfo ReConnect() = 0;

			/*
			*���ܣ���ȡĿ�ĵ�ͨѶ״̬
			*��Σ�
			*��
			*���Σ�
			*collectInfo.sourceName:Ŀ�ĵ�����
			*collectInfo.sourceAddr:Ŀ�ĵصĵ�ַ/�˿ں�/���ں�
			*collectInfo.sourceCollectStatus:Ŀ�ĵ�ת��״̬
			*collectInfo.sourceCollectMsg:Ŀ�ĵ�ת����Ϣ
			*����ֵ��
			* CollectErrorInfo.retCode:�����룬����0Ϊ����ֵ����0Ϊ�쳣ֵ
			* CollectErrorInfo.systemCode:ϵͳ������
			* CollectErrorInfo.errorMsg:������Ϣ���������ؿգ��쳣�����쳣��Ϣ
			* CollectErrorInfo.errType;��������ö��
			*/
			virtual ErrorInfo GetRunInfo(std::vector<SourceCollectInfo> &collectInfos) = 0;

			/*
			*���ܣ���������
			*��Σ�
			*transTopic:ת���豸�����Ӧ��topic
			*tagInfos:���豸�µĲ������
			*tagValues:���ֵ���飬�����������±��Ӧһ��
			*���Σ�
			*��
			*����ֵ��
			* CollectErrorInfo.retCode:�����룬����0Ϊ����ֵ����0Ϊ�쳣ֵ
			* CollectErrorInfo.systemCode:ϵͳ������
			* CollectErrorInfo.errorMsg:������Ϣ���������ؿգ��쳣�����쳣��Ϣ
			* CollectErrorInfo.errType;��������ö��
			*/
			virtual ErrorInfo Send(const DeviceGroupInfo &transTopic, const std::vector<TagInfo> &tagInfos, const std::vector<TagValue> &tagValues) = 0;

			/*
			*���ܣ�������ʷ��������
			*��Σ�
			*transTopic:ת���豸�����Ӧ��topic
			*tagInfos:���豸�µĲ������
			*tagValues:���ֵ���飬�����������±��Ӧһ��
			*���Σ�
			*��
			*����ֵ��
			* CollectErrorInfo.retCode:�����룬����0Ϊ����ֵ����0Ϊ�쳣ֵ
			* CollectErrorInfo.systemCode:ϵͳ������
			* CollectErrorInfo.errorMsg:������Ϣ���������ؿգ��쳣�����쳣��Ϣ
			* CollectErrorInfo.errType;��������ö��
			*/
			virtual ErrorInfo SendHisValues(const DeviceGroupInfo &transTopic, const std::vector<TagInfo> &tagInfos, const std::vector<TagValue> &tagValues) = 0;

			/*
			*���ܣ��Ƿ����ڲ�Э�飬�����Ƿ��������Դ��Ŀ�ĵ�
			* ����ֵ��
			*true�����ڲ�Э��,�򲻻���Ŀ�ĵ�
			*false:���ڲ�Э�飬�����Ŀ�ĵ�
			*/
			virtual bool IsInternalPlugin() = 0;
		};
		
	}//common
	
}//gateway
