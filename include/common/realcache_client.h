#pragma once

#include "multi_value.hpp"
#include "error_info.hpp"
#include "tag_info.hpp"

namespace gateway
{
	namespace common
	{
		class RealCacheClient
		{
		public:
			/*
			 *���ܣ����ӻ�������
			 *��Σ�
			 *connectIp:����˵�ַ
			 *connectPort:����˶˿�
			 *���Σ�
			 *����ֵ��
			 * CacheErrorInfo.errorCode:�����룬����0Ϊ����ֵ����0Ϊ�쳣ֵ
			 * CacheErrorInfo.errorMsg:������Ϣ���������ؿգ��쳣�����쳣��Ϣ
			 */
			virtual ErrorInfo Connect(const std::string &connectAddrPort) = 0;

			/*
			 *���ܣ��������
			 *��Σ�
			 *tagInfos�������Ϣ����
			 *���Σ�
			 *��
			 *����ֵ��
			 * CacheErrorInfo.errorCode:�����룬����0Ϊ����ֵ����0Ϊ�쳣ֵ
			 * CacheErrorInfo.errorMsg:������Ϣ���������ؿգ��쳣�����쳣��Ϣ
			 */
			virtual ErrorInfo CreateTags(const std::vector<TagInfo> &tagInfos) = 0;

			/*
			 *���ܣ�д��������
			 *��Σ�
			 *tagInfos����д�����ݲ������
			 *tagValues����д����������
			 *���Σ�
			 *��
			 *����ֵ��
			 * CacheErrorInfo.errorCode:�����룬����0Ϊ����ֵ����0Ϊ�쳣ֵ
			 * CacheErrorInfo.errorMsg:������Ϣ���������ؿգ��쳣�����쳣��Ϣ
			 */
			virtual ErrorInfo SetValues(const std::vector<TagInfo> &tagInfos, const std::vector<TagValue> &tagValues) = 0;

			/*
			 *���ܣ�д��������
			 *��Σ�
			 *tagInfo����д�����ݲ������
			 *tagValue����д����������
			 *���Σ�
			 *��
			 *����ֵ��
			 * CacheErrorInfo.errorCode:�����룬����0Ϊ����ֵ����0Ϊ�쳣ֵ
			 * CacheErrorInfo.errorMsg:������Ϣ���������ؿգ��쳣�����쳣��Ϣ
			 */
			virtual ErrorInfo SetValue(const TagInfo &tagInfo, const TagValue &tagValue) = 0;

			/*
			 *���ܣ���ȡ�������
			 *��Σ�
			 *tagInfos����д�����ݲ������
			 *���Σ�
			 *tagValues�����ز����������
			 *����ֵ��
			 * CacheErrorInfo.errorCode:�����룬����0Ϊ����ֵ����0Ϊ�쳣ֵ
			 * CacheErrorInfo.errorMsg:������Ϣ���������ؿգ��쳣�����쳣��Ϣ
			 */
			virtual ErrorInfo GetValues(const std::vector<TagInfo> &tagInfos, std::vector<TagValue> &tagValues) = 0;
			
			/*
			 *���ܣ���ȡ�������
			 *��Σ�
			 *tagInfo����д�����ݲ������
			 *���Σ�
			 *tagValue�����ز����������
			 *����ֵ��
			 * CacheErrorInfo.errorCode:�����룬����0Ϊ����ֵ����0Ϊ�쳣ֵ
			 * CacheErrorInfo.errorMsg:������Ϣ���������ؿգ��쳣�����쳣��Ϣ
			 */
			virtual ErrorInfo GetValue(const TagInfo &tagInfo, TagValue &tagValue) = 0;

		};
	}//common
	
}//gateway
