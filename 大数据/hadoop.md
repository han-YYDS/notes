配置hadoop需要采用桥接模式

我之前采用的是 NAT模式, 静态IP地址为192.168.159.133





安装: [Hadoop3.1.3安装教程_单机/伪分布式配置_Hadoop3.1.3/Ubuntu18.04(16.04)_厦大数据库实验室博客 (xmu.edu.cn)](http://dblab.xmu.edu.cn/blog/2441-2/)







```c
hadoop用户
密码: hadoop
```



Master : 192.168.159.133

Slave : 192.168.2.122



g++ -std=c++11 -O3  -o ECHelper src/ECHelper.cc 

obj/CC_BlockReporter.o obj/CC_Computation.o obj/CC_Config.o obj/CC_ConvCoordinator.o obj/CC_ConvDRWorker.o obj/CC_Coordinator.o obj/CC_CyclCoordinator.o obj/CC_CyclDRWorker.o obj/CC_CyclMulFRWorker.o obj/CC_DRWorker.o obj/CC_ECPipeInputStream.o obj/CC_HDFS3_MetadataBase.o obj/CC_HDFS_MetadataBase.o obj/CC_PathSelection.o obj/CC_PipeCoordinator.o obj/CC_PipeDRWorker.o obj/CC_PipeMulCoordinator.o obj/CC_PipeMulDRWorker.o obj/CC_PPRCoordinator.o obj/CC_PPRPullDRWorker.o obj/CC_QFS_MetadataBase.o obj/CC_RSUtil.o obj/UTIL_gettime.o obj/UTIL_tinyxml2.o obj/J_galois.o obj/J_jerasure.o -pthread -lgf_complete lib/libhiredis.a





桥接模式和NAT模式切换

1. 编辑 - 虚拟编辑器 - 将 VMnet0 设置为 桥接网络 (需要点管理员权限)
2. 关闭虚拟机后 - 在设置虚拟机中 - 网络选择桥接网络
3. 进入VMware中后 - 点击右上角状态栏中 - 将网络配置选择为(192.168.43)这个网段的设置





