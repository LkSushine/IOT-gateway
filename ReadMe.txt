目录结构：
根目录
	include   		//存放网关软件头文件目录
		common		//通用数据结构、纯虚类定义
		utils		//通用方法封装，平台相关代码需使用宏定义区分开
	src				//存放网关软件代码目录
		gateway		//网关核心模块目录
			cachedir	//缓存模块目录
				realcache_client		//C++缓存客户端封装库
				realcache_client_java	//java缓存客户端封装库
				realcache_client_py		//python缓存客户端封装库
				realcache_server		//缓存服务端模块
			calculator	//暂未实现，边缘计算模块
			collector	//采集执行器模块
			transmitter //转发执行器模块
			plugins		//协议插件目录
				collector_plugins	//采集协议库目录
					modbus_active	//modbus协议
					udp_passive		//udp协议
					collector_trenddb	//实时库采集同步协议
				transmiter_plugins	//转发协议库目录
					trans_trenddb	//实时库转发写入协议
				vibration_plugins	//振动采集协议
		unit_test	//单元测试目录
	third_party		//三方库存放目录
		include		//三方库依赖头文件目录
		lib32		//三方库依赖静态库、动态库目录
			Windows	//windows平台库目录
				Debug	//debug库
				RelWithDebInfo	//release库
	tools	//工具目录
		grpc	//grpc生成工具
	Windows	//生成输出目录