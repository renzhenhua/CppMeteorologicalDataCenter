# CPP气象数据中心
* public:存放框架
* idc1:生成数据
    * start.sh 启动脚本
    * killall.sh 删除服务脚本
    * crtsurfdata5.cpp 用于生成全国气象站点观察的分钟数据
* tools1:工具程序
    * checproc.cpp 守护进程
    * deletefiles.cpp 用于删除历史的数据文件或日志文件
    * gzipfiles.cpp 用于压缩历史的数据文件或日志文件
    * procctl.cpp 服务程序的调度程序，周期性启动服务程序或shell脚本
    * ftpgetfiles.cpp 调用ftp获取服务器文件