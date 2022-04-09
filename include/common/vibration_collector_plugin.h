#pragma once
#include <spdlog/spdlog.h>
#include <map>
#include "vibration_tag.hpp"
#include "tag_info.hpp"
#include "error_info.hpp"
namespace gateway
{
	namespace common
	{
		class VibrationCollectorPlugin
		{
		public:
			/*
			*���ܣ���ʼ��Э����
			*��Σ�
			*pluginCfg:Э��������ݣ�keyΪ������ʶ��valueΪЭ�������Ϣ
			*logPtr:��־������ָ��
			*���Σ�
			*��
			*����ֵ��
			* CollectErrorInfo.retCode:�����룬����0Ϊ����ֵ����0Ϊ�쳣ֵ
			* CollectErrorInfo.systemCode:ϵͳ������
			* CollectErrorInfo.errorMsg:������Ϣ���������ؿգ��쳣�����쳣��Ϣ
			* CollectErrorInfo.errType;��������ö��
			*/
			virtual ErrorInfo Init(const std::map<std::string, PluginParam> &pluginCfg, const std::shared_ptr<spdlog::logger> &logPtr) = 0;

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
			*���ܣ��·��ɼ�������
			*��Σ�
			*channelDefInfoMaps:�ɼ�����ͨ����Ϣ
			*���Σ�
			*��
			*����ֵ��
			* CollectErrorInfo.retCode:�����룬����0Ϊ����ֵ����0Ϊ�쳣ֵ
			* CollectErrorInfo.systemCode:ϵͳ������
			* CollectErrorInfo.errorMsg:������Ϣ���������ؿգ��쳣�����쳣��Ϣ
			* CollectErrorInfo.errType;��������ö��
			*/
			virtual ErrorInfo CollectCfgSet(const std::map<gateway::common::CollectorInfo, std::vector<gateway::common::ChannelInfoDef>> &channelDefInfoMaps) = 0;

			/*
			*���ܣ��ɼ����Ƿ�������ͨѶ����״̬
			*��Σ�
			*��
			*���Σ�
			*��
			*����ֵ��
			* true:�ɼ�����������
			* false:�ɼ���ֹͣ�ɼ����ɽ��вɼ������ø���
			*/
			virtual bool IsRunnig() = 0;


			/*
			*���ܣ��Ƿ�߱�ת�����ܣ��߱�ʱ��д�뻺�棬�ɲɼ�Э���ڲ���������ת��
			*��Σ�
			*��
			*���Σ�
			*��
			*����ֵ��
			* true:�߱�ת������
			* false:���߱�ת������
			*/
			virtual bool TransEnable() = 0;


			/*
			*���ܣ���ȡ�ɼ�����ͨѶ״̬
			*��Σ�
			*��
			*���Σ�
			*collectInfo.sourceName:�ɼ�������
			*collectInfo.sourceAddr:�ɼ�����ַ/�˿ں�/���ں�
			*collectInfo.sourceCollectStatus:�ɼ����ɼ�״̬
			*collectInfo.sourceCollectMsg:�ɼ����ɼ���Ϣ
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
			*channelInfos:ͨ����Ϣ����
			*channelData:ͨ������
			*����ֵ��
			* CollectErrorInfo.retCode:�����룬����0Ϊ����ֵ����0Ϊ�쳣ֵ
			* CollectErrorInfo.systemCode:ϵͳ������
			* CollectErrorInfo.errorMsg:������Ϣ���������ؿգ��쳣�����쳣��Ϣ
			* CollectErrorInfo.errType;��������ö��
			*/
			virtual ErrorInfo Read(std::vector<gateway::common::ChannelInfoDef> &channelInfos, std::vector<gateway::common::TagValue> &channelData) = 0;

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
				std::function<ErrorInfo(const std::vector<gateway::common::ChannelInfoDef>&, const std::vector<gateway::common::TagValue>&)> SetValueFunc,
				std::function<ErrorInfo(const std::vector<gateway::common::ChannelInfoDef> &)> updateNotifyMqttFunc) = 0;


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
