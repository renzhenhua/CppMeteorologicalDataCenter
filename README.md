# CPP数据中心

* public:存放框架
* pthread1:演示线程使用
* idc1:生成数据
  * start.sh 启动脚本
  * killall.sh 删除服务脚本
  * crtsurfdata5.cpp 用于生成全国气象站点观察的分钟数据
  * obtcodetodb.cpp，本程序用于把全国站点参数数据保存到数据库T_ZHOBTCODE表中
  * obtmindtodb.cpp，本程序用于把全国站点分钟观测数据入库到T_ZHOBTMIND表中，支持xml和csv两种文件格式
* tools1:工具程序
  * checproc.cpp 守护进程
  * deletefiles.cpp 用于删除历史的数据文件或日志文件
  * gzipfiles.cpp 用于压缩历史的数据文件或日志文件
  * procctl.cpp 服务程序的调度程序，周期性启动服务程序或shell脚本
  * ftp模块
    * ftpgetfiles.cpp 调用ftp获取服务器文件
    * ftpputfiles.cpp ftp上传文件
  * tcp模块
    * tcpputfiles.cpp 采用tcp协议，实现文件上传的客户端
    * fileserver.cpp 文件传输的服务
  * mysql模块
    * diminingmysql.cpp 本程序是数据中心的公共功能模块，用于从mysql数据库源表抽取数据，生成xml文件
    * xmltodb.cpp，本程序是数据中心的公共功能模块，用于把xml文件入库到MySQL的表中
    * migratetable.cpp，本程序是数据中心的公共功能模块，用于迁移表中的数据
    * deletetable.cpp，本程序是数据中心的公共功能模块，用于定时清理表中的数据
    * syncupdate.cpp，本程序是数据中心的公共功能模块，采用刷新的方法同步MySQL数据库之间的表
    * syncincrement.cpp，本程序是数据中心的公共功能模块，采用增量的方法同步MySQL数据库之间的表
    * syncincrementex.cpp 本程序是数据中心的公共功能模块，采用增量的方法同步MySQL数据库之间的表
      * 本程序不使用Federated引擎
  * oracle模块
    * dminingoracle.cpp，本程序是数据中心的公共功能模块，用于从Oracle数据库源表抽取数据，生成xml文件
    * xmltodb_oracle.cpp，本程序是数据中心的公共功能模块，用于把xml文件入库到Oracle的表中
    * migratetable_oracle.cpp，本程序是数据中心的公共功能模块，用于迁移表中的数据
    * deletetable_oracle.cpp，本程序是数据中心的公共功能模块，用于定时清理表中的数据
    * syncupdate_oracle.cpp，本程序是数据中心的公共功能模块，采用刷新的方法同步Oracle数据库之间的表
    * syncincrement_oracle.cpp，本程序是数据中心的公共功能模块，采用增量的方法同步Oracle数据库之间的表。
    * syncincrementex_oracle.cpp，本程序是数据中心的公共功能模块，采用增量的方法同步Oracle数据库之间的表。
      *  注意，本程序不使用dblink。
  