#pragma once
#include <string>
#include <vector>
#ifdef WIN32
#include <Windows.h>

#endif


namespace gateway
{
	namespace utils
	{
		class UdpClient
		{
		public :
			UdpClient():srcPort_(0), dstPort_(0), serSock_(-1), recvBuff_(nullptr), recvBuffLen_(1024)
			{

			}

			/*
			*���ܣ���ʼ������������Ϣ
			*��Σ�
			*srcIp:����������ַ��Ϊ��ʱ�Զ���ȡIP��ַ
			*srcPort:�ͻ��˰󶨶˿ڣ�Ϊ0ʱ�Զ�����˿�
			*dstIp:Ŀ�����˵�ַ
			*dstPort:Ŀ�����˶˿�
			*���Σ�
			*��
			*����ֵ��
			* ����0Ϊ����ֵ����0Ϊϵͳ������
			*/
			int Init(const std::string &srcIp, const int &srcPort, const std::string &dstIp, const int &dstPort)
			{
				srcIp_ = srcIp;
				srcPort_ = srcPort;
				dstIp_ = dstIp;
				dstPort_ = dstPort;
#ifdef WIN32
				WORD versionReq = MAKEWORD(2, 2);
				WSAData wsa;

				if (WSAStartup(versionReq, &wsa) != 0)
				{
					return GetLastError();
				}
				int af = AF_INET;
				int type = SOCK_DGRAM;
				int protocol = IPPROTO_UDP;

				cliSock_ = socket(af, type, protocol);
				if (cliSock_ == INVALID_SOCKET)
				{
					return WSAGetLastError();
				}

				sockaddr_in servAddr;
				memset(&servAddr, 0, sizeof(servAddr));  //ÿ���ֽڶ���0���
				servAddr.sin_family = PF_INET;  //ʹ��IPv4��ַ
				servAddr.sin_addr.s_addr = htonl(INADDR_ANY); //�Զ���ȡIP��ַ
				servAddr.sin_port = htons(srcPort);  //�˿�
				if (bind(cliSock_, (SOCKADDR*)&servAddr, sizeof(SOCKADDR)) == SOCKET_ERROR)
				{
					closesocket(cliSock_);
					return GetLastError();
				}

				dstAddr_.sin_family = AF_INET;
				dstAddr_.sin_port = htons(port_);
				dstAddr_.sin_addr.S_un.S_addr = inet_addr(ip_.c_str());
#endif
				return 0;
			}

			/*
			*���ܣ������׽�������
			*��Σ�
			*sendOutTime:���÷������ݳ�ʱʱ�䣬��λ���룬����0ʱ��Ч������ʹ��Ĭ��ֵ
			*recvOutTime:���ý������ݳ�ʱʱ�䣬��λ���룬����0ʱ��Ч������ʹ��Ĭ��ֵ
			*sendBuffSize:���÷������ݻ�������С����λ�ֽ�
			*recvBuffSize:���ý������ݻ�������С����λ�ֽ�
			*���Σ�
			*��
			*����ֵ��
			* ����0Ϊ����ֵ����0Ϊϵͳ������
			*/
			int Config(const int &sendOutTime, const int &recvOutTime, const int &sendBuffSize, const int &recvBuffSize)
			{
#ifdef WIN32
				BOOL bReuseaddr = TRUE;
				setsockopt(cliSock_, SOL_SOCKET, SO_REUSEADDR, (const char*)&bReuseaddr, sizeof(BOOL));
				BOOL bDontLinger = FALSE;
				setsockopt(cliSock_, SOL_SOCKET, SO_DONTLINGER, (const char*)&bDontLinger, sizeof(BOOL));

				if (sendOutTime > 0)
				{
					setsockopt(cliSock_, SOL_SOCKET, SO_SNDTIMEO, (char *)&sendOutTime, sizeof(int));
				}

				if (recvOutTime > 0)
				{
					setsockopt(cliSock_, SOL_SOCKET, SO_RCVTIMEO, (char *)&recvOutTime, sizeof(int));
				}
				
				if (recvBuffSize > 0)
				{
					setsockopt(cliSock_, SOL_SOCKET, SO_RCVBUF, (const char*)&recvBuffSize, sizeof(int));
					recvBuffLen_ = recvBuffSize;
				}

				recvBuff_ = new char[recvBuffLen_] {0};
#endif
				return 0;
			}

			/*
			*���ܣ���������
			*��Σ�
			*sendData:����������
			*���Σ�
			*��
			*����ֵ��
			* �ɹ��������ݵĳ���
			*/
			int Send(const std::string &sendData)
			{
#ifdef WIN32
				int ret = sendto(cliSock_, sendData.c_str(), sendData.size(), 0, (sockaddr*)&dstAddr_, sizeof(dstAddr_));
#endif
				return ret;
			}

			/*
			*���ܣ���������
			*��Σ�
			*sendData:����������ָ��
			*len:���������ݳ���
			*���Σ�
			*��
			*����ֵ��
			* �ɹ��������ݵĳ���
			*/
			int Send(const char* sendData,const int &len)
			{
#ifdef WIN32
				int ret = sendto(cliSock_, sendData, len, 0, (sockaddr*)&dstAddr_, sizeof(dstAddr_));
#endif
				return ret;
			}

			/*
			*���ܣ���������
			*��Σ�
			*recvData:���յ�������
			*���Σ�
			*��
			*����ֵ��
			* �ɹ��������ݵĳ���
			*/
			int Recv(std::string &recvData)
			{
#ifdef WIN32
				SOCKADDR recvAddr;  //���ն˵�ַ��Ϣ
				int nSize = sizeof(SOCKADDR);
				int ret = recvfrom(cliSock_, recvBuff_, recvBuffLen_, 0, &clntAddr, &nSize);
#endif
				if (ret > 0)
				{
					recvData.append()
				}
				recvData.clear();
				return ret;
			}

			/*
			*���ܣ������׽�������
			*��Σ�
			*sendOutTime:���÷������ݳ�ʱʱ�䣬��λ���룬����0ʱ��Ч������ʹ��Ĭ��ֵ
			*recvOutTime:���ý������ݳ�ʱʱ�䣬��λ���룬����0ʱ��Ч������ʹ��Ĭ��ֵ
			*sendBuffSize:���÷������ݻ�������С����λ�ֽ�
			*recvBuffSize:���ý������ݻ�������С����λ�ֽ�
			*���Σ�
			*��
			*����ֵ��
			* ����0Ϊ����ֵ����0Ϊϵͳ������
			*/
			int Recv(char* recvData, const int &len)
			{
#ifdef WIN32
				SOCKADDR recvAddr;  //���ն˵�ַ��Ϣ
				int nSize = sizeof(SOCKADDR);
				int ret = recvfrom(cliSock_, recvData, len, 0, &recvAddr, &nSize);
#endif
				return ret;
			}

			/*
			*���ܣ������׽�������
			*��Σ�
			*sendOutTime:���÷������ݳ�ʱʱ�䣬��λ���룬����0ʱ��Ч������ʹ��Ĭ��ֵ
			*recvOutTime:���ý������ݳ�ʱʱ�䣬��λ���룬����0ʱ��Ч������ʹ��Ĭ��ֵ
			*sendBuffSize:���÷������ݻ�������С����λ�ֽ�
			*recvBuffSize:���ý������ݻ�������С����λ�ֽ�
			*���Σ�
			*��
			*����ֵ��
			* ����0Ϊ����ֵ����0Ϊϵͳ������
			*/
			int Destory()
			{
#ifdef WIN32
				closesocket(serSock_);
				if (WSACleanup() != 0)
				{
					return GetLastError();
				}
#endif
				return 0;
			}
		private:
			std::string srcIp_;
			std::string dstIp_;
			int srcPort_;
			int dstPort_;
			int selectMS_;//��ʱ������
			int recvBuffLen_;
			char* recvBuff_;
#ifdef WIN32
			sockaddr_in dstAddr_;
			SOCKET cliSock_;
#endif


		};

	}//utils

}//gateway