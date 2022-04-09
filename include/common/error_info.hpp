#pragma once


namespace gateway
{
	namespace common
	{
		//��������ö��
		enum class ErrorType :int8_t
		{
			kOk = 0,			//����
			kUnDefineError,		//δ�������
			kConnectError,		//���Ӵ��󣬵����ӳ���ʱ�����������
			kLoadDllError,		//���ض�̬�����
			kMemOverMax,		//�ڴ�ﵽ���ֵ
			kGetWebConfigError, //��ȡƽ̨���ô���
			kBindPortError, //����˰󶨶˿ڴ���
			kParamError, //Э���������
			//�����������ʹ���չ
		};

		
		struct ErrorInfo
		{
			int retCode;			//0��������0�쳣
			int systemCode;			//ϵͳ������
			ErrorType errType;		//��������ö��
			std::string errorMsg;	//������Ϣ
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
