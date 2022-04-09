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
			*功能：初始化网络连接信息
			*入参：
			*srcIp:发送网卡地址，为空时自动获取IP地址
			*srcPort:客户端绑定端口，为0时自动分配端口
			*dstIp:目标服务端地址
			*dstPort:目标服务端端口
			*出参：
			*无
			*返回值：
			* 返回0为正常值，非0为系统错误码
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
				memset(&servAddr, 0, sizeof(servAddr));  //每个字节都用0填充
				servAddr.sin_family = PF_INET;  //使用IPv4地址
				servAddr.sin_addr.s_addr = htonl(INADDR_ANY); //自动获取IP地址
				servAddr.sin_port = htons(srcPort);  //端口
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
			*功能：设置套接字配置
			*入参：
			*sendOutTime:设置发送数据超时时间，单位毫秒，大于0时生效，否则使用默认值
			*recvOutTime:设置接收数据超时时间，单位毫秒，大于0时生效，否则使用默认值
			*sendBuffSize:设置发送数据缓冲区大小，单位字节
			*recvBuffSize:设置接收数据缓冲区大小，单位字节
			*出参：
			*无
			*返回值：
			* 返回0为正常值，非0为系统错误码
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
			*功能：发送数据
			*入参：
			*sendData:待发送数据
			*出参：
			*无
			*返回值：
			* 成功发送数据的长度
			*/
			int Send(const std::string &sendData)
			{
#ifdef WIN32
				int ret = sendto(cliSock_, sendData.c_str(), sendData.size(), 0, (sockaddr*)&dstAddr_, sizeof(dstAddr_));
#endif
				return ret;
			}

			/*
			*功能：发送数据
			*入参：
			*sendData:待发送数据指针
			*len:待发送数据长度
			*出参：
			*无
			*返回值：
			* 成功发送数据的长度
			*/
			int Send(const char* sendData,const int &len)
			{
#ifdef WIN32
				int ret = sendto(cliSock_, sendData, len, 0, (sockaddr*)&dstAddr_, sizeof(dstAddr_));
#endif
				return ret;
			}

			/*
			*功能：接收数据
			*入参：
			*recvData:接收到的数据
			*出参：
			*无
			*返回值：
			* 成功接收数据的长度
			*/
			int Recv(std::string &recvData)
			{
#ifdef WIN32
				SOCKADDR recvAddr;  //接收端地址信息
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
			*功能：设置套接字配置
			*入参：
			*sendOutTime:设置发送数据超时时间，单位毫秒，大于0时生效，否则使用默认值
			*recvOutTime:设置接收数据超时时间，单位毫秒，大于0时生效，否则使用默认值
			*sendBuffSize:设置发送数据缓冲区大小，单位字节
			*recvBuffSize:设置接收数据缓冲区大小，单位字节
			*出参：
			*无
			*返回值：
			* 返回0为正常值，非0为系统错误码
			*/
			int Recv(char* recvData, const int &len)
			{
#ifdef WIN32
				SOCKADDR recvAddr;  //接收端地址信息
				int nSize = sizeof(SOCKADDR);
				int ret = recvfrom(cliSock_, recvData, len, 0, &recvAddr, &nSize);
#endif
				return ret;
			}

			/*
			*功能：设置套接字配置
			*入参：
			*sendOutTime:设置发送数据超时时间，单位毫秒，大于0时生效，否则使用默认值
			*recvOutTime:设置接收数据超时时间，单位毫秒，大于0时生效，否则使用默认值
			*sendBuffSize:设置发送数据缓冲区大小，单位字节
			*recvBuffSize:设置接收数据缓冲区大小，单位字节
			*出参：
			*无
			*返回值：
			* 返回0为正常值，非0为系统错误码
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
			int selectMS_;//超时毫秒数
			int recvBuffLen_;
			char* recvBuff_;
#ifdef WIN32
			sockaddr_in dstAddr_;
			SOCKET cliSock_;
#endif


		};

	}//utils

}//gateway