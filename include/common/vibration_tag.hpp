#pragma once

#include <string>
#include <vector>
#include "vibration_tag.hpp"

namespace gateway
{
	namespace common
	{
		//振动类型枚举
		enum class SensorType :int8_t
		{
			kSpeed = 0,		//键相通道
			kVibration,		//振动通道
			kTemperature	//温度通道
		};

		//采集器信息
		struct CollectorInfo
		{
			std::string collectionId;				//采集器编号
			std::string collectionNo;				//采集器No
			std::string collectorSerialNo;			//采集器序列号
			std::string collectionModel;			//采集器生产型号
			bool validStaFlag;						//是否可用
			std::string collectionIP;				//采集器IP
			std::string collectionFactoryname;		//采集器生产型号
			std::string hardwareVersion;			//硬件版本号
			std::string collectionName;				//采集器名称
			std::string softwareVersion;			//软件版本号
			int channelsCnt;						//最大通道数
			std::string collectionDbIP;				//最大通道数
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


		//采集定义信息
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

		//矢量定义信息
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

		//通道信息定义
		struct ChannelInfoDef
		{
			std::string collectionId;				//采集器编号
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
			//键相测点属性
			std::string backPoor;
			std::string bondSpeed;
			std::string maxSpeed;
			std::string minSpeed;
			std::string threValue;
			std::string autoCalcThre;
			std::string keyTyp;
			std::string edgeTyp;
			
			float sf;//采样率 
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

		//通道数据定义
		struct ChannelDataDef
		{
			std::vector<double> values;
			uint64_t timestamp;
			int status;
		};

		struct SpectData
		{
			float overallHf;	//高频总值
			float overallLf;	//低频总值
			double speedAll;	//速度总值
			double overallDem;	//解调能量值
			double dc;			//直流量gap
			double ppk;			//峰峰值
			double pk;			//峰值
			double rms;			//有效值overall加速度总值
			double crestor;		//峰值因子
			double ske;			//偏度
			double kurtosis;	//峭度因子
			float speed;		//速度
			float amp_1x;		//一倍频
			float amp_2x;		//二倍频
			float temp;		//温度
			float battery;		//电池电量
			std::string vectorChannelNo;//矢量定义通道号
		};

	}//common

}//gateway

