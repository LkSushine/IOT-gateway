#pragma once
#include <spdlog/spdlog.h>
#include <map>
#include "tag_info.hpp"
#include "error_info.hpp"

namespace gateway
{
	namespace common
	{
		class CollectorPlugin
		{
		public:
			/*
			*���ܣ���ʼ��Э����
			*��Σ�
			*tagInfos:�����Ϣ�б�������������ģ���������������
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
			virtual ErrorInfo Init(const std::vector<TagInfo> &tagInfos, const std::map<std::string, PluginParam> &pluginCfg, const std::shared_ptr<spdlog::logger> &logPtr) = 0;

			/*
			*���ܣ���������Դ/��λ�����вɼ�
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
			*���ܣ������쳣ʱ����������Դ/��λ��
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
			*���ܣ���ȡ����Դ/��λ���ɼ�ͨѶ״̬
			*��Σ�
			*��
			*���Σ�
			*collectInfo.sourceName:��λ��/����Դ����
			*collectInfo.sourceAddr:��λ��/����Դ�ĵ�ַ/�˿ں�/���ں�
			*collectInfo.sourceCollectStatus:����Դ�ɼ�״̬
			*collectInfo.sourceCollectMsg:����Դ�ɼ���Ϣ
			*����ֵ��
			* CollectErrorInfo.retCode:�����룬����0Ϊ����ֵ����0Ϊ�쳣ֵ
			* CollectErrorInfo.systemCode:ϵͳ������
			* CollectErrorInfo.errorMsg:������Ϣ���������ؿգ��쳣�����쳣��Ϣ
			* CollectErrorInfo.errType;��������ö��
			*/
			virtual ErrorInfo GetRunInfo(std::vector<SourceCollectInfo> &collectInfos) = 0;

			/*
			*���ܣ���ȡ�ɼ��������ģʽ������ģʽ/����ģʽ
			*��Σ�
			*��
			*���Σ�
			*��
			*����ֵ��
			* gateway::PluginRunModel:
			*	kActive��ʱ����Read������ȡ����
			*	kPassive��������Run����
			*/
			virtual PluginRunModel GetPluginRunModel() = 0;

			/*
			*���ܣ�����ģʽ��ȡ����
			*��Σ�
			*��
			*���Σ�
			*tagInfos:�����Ϣ����
			*tagValues:���ֵ���飬�����������±��Ӧһ��
			*����ֵ��
			* CollectErrorInfo.retCode:�����룬����0Ϊ����ֵ����0Ϊ�쳣ֵ
			* CollectErrorInfo.systemCode:ϵͳ������
			* CollectErrorInfo.errorMsg:������Ϣ���������ؿգ��쳣�����쳣��Ϣ
			* CollectErrorInfo.errType;��������ö��
			*/
			virtual ErrorInfo Read(std::vector<TagInfo> &tagInfos, std::vector<TagValue> &tagValues) = 0;

			/*
			*���ܣ�����ģʽ��ȡ����
			*��Σ�
			*SetValueFunc:ʵʱ����д�뺯��ָ��
			*updateNotifyMqttFunc:���ݸ��£�mqtt֪ͨ����ָ��
			*���Σ�
			*��
			*����ֵ��
			* CollectErrorInfo.retCode:�����룬����0Ϊ����ֵ����0Ϊ�쳣ֵ
			* CollectErrorInfo.systemCode:ϵͳ������
			* CollectErrorInfo.errorMsg:������Ϣ���������ؿգ��쳣�����쳣��Ϣ
			* CollectErrorInfo.errType;��������ö��
			*/
			virtual ErrorInfo Run(
				std::function<ErrorInfo( std::vector<TagInfo>&,  std::vector<TagValue>&)> SetValueFunc,
				std::function<ErrorInfo()> updateNotifyMqttFunc) = 0;

			/*
			*���ܣ��Ƿ�֧���¿ع���
			*��Σ�
			*��
			*���Σ�
			*��
			*����ֵ��
			* true:֧���¿�
			* false:��֧���¿�
			*/
			virtual bool ControlEnable() = 0;

			/*
			*���ܣ��¿�����
			*��Σ�
			*tagNames�����Ƶ������ڲ����ݿ��Ƶ����ҵ���Ӧ�Ĳɼ�����
			*tagValues���¿ص�ֵ�����ɼ���������д��
			*���Σ�
			*��
			*����ֵ��
			* CollectErrorInfo.retCode:�����룬����0Ϊ����ֵ����0Ϊ�쳣ֵ
			* CollectErrorInfo.systemCode:ϵͳ������
			* CollectErrorInfo.errorMsg:������Ϣ���������ؿգ��쳣�����쳣��Ϣ
			* CollectErrorInfo.errType;��������ö��
			*/
			virtual ErrorInfo Write(const std::vector<TagInfo> &tagInfos, const std::vector<TagValue> &tagValues) = 0;



			/*
			*���ܣ��Ƿ����ڲ�Э�飬�����Ƿ��������Դ��Ŀ�ĵ�
			* ����ֵ��
			*true�����ڲ�Э��,�򲻻�������Դ
			*false:���ڲ�Э�飬���������Դ
			*/
			virtual bool IsInternalPlugin() = 0;

		};

	}//common
	
}//gateway
