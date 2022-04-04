# CPP数据中心

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
  * ftpputfiles.cpp ftp上传文件
  * tcpputfiles.cpp 采用tcp协议，实现文件上传的客户端
  * fileserver.cpp 文件传输的服务
  * diminingmysql.cpp 本程序是数据中心的公共功能模块，用于从mysql数据库源表抽取数据，生成xml文件
  * xmltodb.cpp，本程序是数据中心的公共功能模块，用于把xml文件入库到MySQL的表中。
  * deletetable.cpp，本程序是数据中心的公共功能模块，采用增量的方法同步MySQL数据库之间的表
  * syncupdate.cpp，本程序是数据中心的公共功能模块，采用刷新的方法同步MySQL数据库之间的表
  