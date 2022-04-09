#pragma once

#include <string>
#include <vector>
#include "vibration_tag.hpp"

namespace gateway
{
	namespace common
	{
		//������ö��
		enum class SensorType :int8_t
		{
			kSpeed = 0,		//����ͨ��
			kVibration,		//��ͨ��
			kTemperature	//�¶�ͨ��
		};

		//�ɼ�����Ϣ
		struct CollectorInfo
		{
			std::string collectionId;				//�ɼ������
			std::string collectionNo;				//�ɼ���No
			std::string collectorSerialNo;			//�ɼ������к�
			std::string collectionModel;			//�ɼ��������ͺ�
			bool validStaFlag;						//�Ƿ����
			std::string collectionIP;				//�ɼ���IP
			std::string collectionFactoryname;		//�ɼ��������ͺ�
			std::string hardwareVersion;			//Ӳ���汾��
			std::string collectionName;				//�ɼ�������
			std::string softwareVersion;			//����汾��
			int channelsCnt;						//���ͨ����
			std::string collectionDbIP;				//���ͨ����
			bool operator<(const CollectorInfo& tagR) const
			{
				return this->collectionId < tagR.collectionId;
			};

			bool operator==(const CollectorInfo& tagR) const
			{
				return this->collectionId == tagR.collectionId;
			};

			bool operator==(const std::string& collectionId) const
			{
				return this->collectionId == collectionId;
			};

			void ValidFromStr(const std::string &str)
			{
				if (str == "I")
				{
					validStaFlag = false;
				}
				else
				{
					validStaFlag = true;
				}
			}
		};


		//�ɼ�������Ϣ
		struct CollectionDefInfo
		{
			std::string avgCount;			
			std::string avgType;			
			std::string bandWidthDown;		
			std::string bandWidthTop;		
			std::string fenxiHz;			
			std::string functionType;		
			std::string groupNam;			
			std::string lvboHz;				
			std::string measureType;		
			std::string onceIntegral;		
			std::string ovlapPercent;
			std::string pointNo;
			std::string puxianNum;
			std::string sampleHz;
			std::string secondIntegral;
			std::string signalType;
			std::string singlewaveLength;
			std::string strategyOne; 
			std::string secondIntegra;
			std::string strategyThree;
			std::string strategyTwo;
			std::string strategyoneSpeeddown;
			std::string strategyoneSpeedup;
		};

		//ʸ��������Ϣ
		struct VectorDefInfo
		{
			std::string dipinHz;
			std::string fenxiHz;
			std::string gaopinHz;
			std::string jiebicaiyangHz;
			std::string jiediaoHz;
			std::string lvboHz;
			std::string onceIntegral;
			std::string secondIntegral;
			std::string strategyOne;
			std::string strategyThree;
			std::string strategyTwo;
			std::string strategyoneSpeeddown;
			std::string strategyoneSpeedup;
			std::string vectorDefineName;
			std::string equVdNo;
			std::string vectorNo;
		};

		//ͨ����Ϣ����
		struct ChannelInfoDef
		{
			std::string collectionId;				//�ɼ������
			bool can;
			std::string channelId;
			std::string channelNo;
			std::string direcRota;
			std::string installAngle;
			std::string pointId;
			std::string pointNam;
			std::string pointNo;
			std::string linkPointId;
			bool power;
			std::string sensorTyp;
			std::string sensitivity;
			std::string type;
			std::string channelSerialNo;
			std::string channelTyp;
			std::string collectionName;
			//����������
			std::string backPoor;
			std::string bondSpeed;
			std::string maxSpeed;
			std::string minSpeed;
			std::string threValue;
			std::string autoCalcThre;
			std::string keyTyp;
			std::string edgeTyp;
			
			float sf;//������ 
			std::vector<CollectionDefInfo> collectionDefInfos;
			VectorDefInfo vectorDefInfo;
			bool operator<(const ChannelInfoDef& tagR) const
			{
				return this->channelId < tagR.channelId;
			};

			bool operator==(const ChannelInfoDef& tagR) const
			{
				return this->channelId == tagR.channelId;
			};

			void operator=(const ChannelInfoDef& tagR)
			{
				collectionId = tagR.collectionId;
				can = tagR.can;
				channelId = tagR.channelId;
				channelNo = tagR.channelNo;
				direcRota = tagR.direcRota;
				installAngle = tagR.installAngle;
				pointId = tagR.pointId;
				pointNam = tagR.pointNam;
				pointNo = tagR.pointNo;
				linkPointId = tagR.linkPointId;
				power = tagR.power;
				sensorTyp = tagR.sensorTyp;
				sensitivity = tagR.sensitivity;
				collectionName= tagR.collectionName;
				type = tagR.type;
				channelSerialNo = tagR.channelSerialNo;
				channelTyp = tagR.channelTyp;
				sf = tagR.sf;
				collectionDefInfos = tagR.collectionDefInfos;
				vectorDefInfo = tagR.vectorDefInfo;
			};

			bool operator==(const std::string& channelId) const
			{
				return this->channelId == channelId;
			};
			ChannelInfoDef()
				:sf(12800)
			{}
		};

		//ͨ�����ݶ���
		struct ChannelDataDef
		{
			std::vector<double> values;
			uint64_t timestamp;
			int status;
		};

		struct SpectData
		{
			float overallHf;	//��Ƶ��ֵ
			float overallLf;	//��Ƶ��ֵ
			double speedAll;	//�ٶ���ֵ
			double overallDem;	//�������ֵ
			double dc;			//ֱ����gap
			double ppk;			//���ֵ
			double pk;			//��ֵ
			double rms;			//��Чֵoverall���ٶ���ֵ
			double crestor;		//��ֵ����
			double ske;			//ƫ��
			double kurtosis;	//�Ͷ�����
			float speed;		//�ٶ�
			float amp_1x;		//һ��Ƶ
			float amp_2x;		//����Ƶ
			float temp;		//�¶�
			float battery;		//��ص���
			std::string vectorChannelNo;//ʸ������ͨ����
		};

	}//common

}//gateway

