#pragma once


namespace gateway
{
	namespace common
	{
		//错误类型枚举
		enum class ErrorType :int8_t
		{
			kOk = 0,			//正常
			kUnDefineError,		//未定义错误
			kConnectError,		//连接错误，当连接出错时，需进行重连
			kLoadDllError,		//加载动态库出错
			kMemOverMax,		//内存达到最大值
			kGetWebConfigError, //获取平台配置错误
			kBindPortError, //服务端绑定端口错误
			kParamError, //协议参数错误
			//其他错误类型待拓展
		};

		
		struct ErrorInfo
		{
			int retCode;			//0正常，非0异常
			int systemCode;			//系统错误码
			ErrorType errType;		//错误类型枚举
			std::string errorMsg;	//错误信息
			ErrorInfo() :retCode(0), systemCode(0), errType(ErrorType::kOk) {}

			ErrorInfo(const int &errCode, const int &sysCode, const std::string &errMsg, const ErrorType &errType)
				:retCode(errCode),
				systemCode(sysCode),
				errType(errType),
				errorMsg(errMsg)
			{
			}

			bool Ok() const
			{
				return errType == ErrorType::kOk;
			}
		};
		
	}//common
	
}//gateway
