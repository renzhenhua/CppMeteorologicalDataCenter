/*
 * 程序名：webserver.cpp，数据服务总线服务。
 * 最简单的web服务器，收到客户请求的，返回html文件。
 * 作者：任振华
 */
#include "_public.h"
#include "_ooci.h"

CLogFile logfile;     // 服务程序的运行日志。
CTcpServer TcpServer; // 创建服务端对象。

void EXIT(int sig); // 进程的退出函数。

pthread_spinlock_t vthidlock; // 用于锁定vthid的自旋锁。
vector<pthread_t> vthid;      // 存放全部线程id的容器。
void *thmain(void *arg);      // 线程主函数。

void thcleanup(void *arg); // 线程清理函数。

struct st_arg
{
    char connstr[101]; // 数据库的连接参数。
    char charset[51];  // 数据库的字符集。
    int port;          // web服务监听的端口。
} starg;

// 显示程序的帮助
void _help(char *argv[]);

// 把xml解析到参数starg结构中
bool _xmltoarg(char *strxmlbuffer);

// 读取客户端的报文。
int ReadT(const int sockfd, char *buffer, const int size, const int itimeout);

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        _help(argv);
        return -1;
    }

    // 关闭全部的信号和输入输出。
    // 设置信号,在shell状态下可用 "kill + 进程号" 正常终止些进程
    // 但请不要用 "kill -9 +进程号" 强行终止
    CloseIOAndSignal();
    signal(SIGINT, EXIT);
    signal(SIGTERM, EXIT);

    if (logfile.Open(argv[1], "a+") == false)
    {
        printf("logfile.Open(%s) failed.\n", argv[2]);
        return -1;
    }

    if (_xmltoarg(argv[2]) == false)
        EXIT(-1);

    // 服务端初始化。
    if (TcpServer.InitServer(starg.port) == false)
    {
        logfile.Write("TcpServer.InitServer(%d) failed.\n", starg.port);
        EXIT(-1);
    }

    pthread_spin_init(&vthidlock, 0);

    while (true)
    {
        // 等待客户端的连接请求。
        if (TcpServer.Accept() == false)
        {
            logfile.Write("TcpServer.Accept() failed.\n");
            EXIT(-1);
        }

        logfile.Write("客户端（%s）已连接。\n", TcpServer.GetIP());

        // 创建一个新的线程，让它与客户端通讯。
        pthread_t thid;
        if (pthread_create(&thid, NULL, thmain, (void *)(long)TcpServer.m_connfd) != 0)
        {
            logfile.Write("pthread_create() failed.\n");
            TcpServer.CloseListen();
            continue;
        }

        pthread_spin_lock(&vthidlock);
        vthid.push_back(thid); // 把线程id放入容器。
        pthread_spin_unlock(&vthidlock);
    }
}

void *thmain(void *arg) // 线程主函数。
{
    pthread_cleanup_push(thcleanup, arg); // 把线程清理函数入栈（关闭客户端的socket）。

    int connfd = (int)(long)arg; // 客户端的socket。

    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL); // 线程取消方式为立即取消。

    pthread_detach(pthread_self()); // 把线程分离出去。

    char strrecvbuf[1024]; // 接收客户端请求报文的buffer。
    memset(strrecvbuf, 0, sizeof(strrecvbuf));

    // 读取客户端的报文，如果超时或失败，线程退出。
    if (ReadT(connfd, strrecvbuf, sizeof(strrecvbuf), 3) <= 0)
        pthread_exit(0);

    // 如果不是GET请求报文不处理，线程退出。
    if (strncmp(strrecvbuf, "GET", 3) != 0)
        pthread_exit(0);

    logfile.Write("%s\n", strrecvbuf);

    // 连接数据库。
    connection conn;
    if (conn.connecttodb(starg.connstr, starg.charset) != 0)
    {
        logfile.Write("connect, database(%s) failed.\n%s\n", starg.connstr, conn.m_cda.message);
        pthread_exit(0);
    }

    // 判断URL中用户名和密码，如果不正确，返回认证失败的响应报文，线程退出。
    if (Login(&conn, strrecvbuf, connfd) == false)
        pthread_exit(0);

    // 判断用户是否有调用接口的权限，如果没有，返回没有权限的响应报文，线程退出。

    // 先把响应报文头部发送给客户端。

    // 再执行接口的sql语句，把数据返回给客户端。

    // 把本线程id从存放线程id的容器中删除。
    pthread_spin_lock(&vthidlock);
    for (int ii = 0; ii < vthid.size(); ii++)
    {
        if (pthread_equal(pthread_self(), vthid[ii]))
        {
            vthid.erase(vthid.begin() + ii);
            break;
        }
    }
    pthread_spin_unlock(&vthidlock);

    pthread_cleanup_pop(1); // 把线程清理函数出栈。
}

// 进程的退出函数。
void EXIT(int sig)
{
    // 以下代码是为了防止信号处理函数在执行的过程中被信号中断。
    signal(SIGINT, SIG_IGN);
    signal(SIGTERM, SIG_IGN);

    logfile.Write("进程退出，sig=%d。\n", sig);

    TcpServer.CloseListen(); // 关闭监听的socket。

    // 取消全部的线程。
    for (int ii = 0; ii < vthid.size(); ii++)
    {
        pthread_cancel(vthid[ii]);
    }

    sleep(1); // 让子线程有足够的时间退出。

    pthread_spin_destroy(&vthidlock);

    exit(0);
}

void thcleanup(void *arg) // 线程清理函数。
{
    close((int)(long)arg); // 关闭客户端的socket。

    logfile.Write("线程%lu退出。\n", pthread_self());
}

// 显示程序的帮助
void _help(char *argv[])
{
    printf("Using:/project/tools1/bin/webserver logfilename xmlbuffer\n\n");

    printf("Sample:/project/tools1/bin/procctl 10 /project/tools1/bin/webserver /log/idc/webserver.log \"<connstr>scott/tiger@snorcl11g_gz</connstr><charset>Simplified Chinese_China.AL32UTF8</charset><port>8080</port>\"\n\n");

    printf("本程序是数据总线的服务端程序，为数据中心提供http协议的数据访问接口。\n");
    printf("logfilename 本程序运行的日志文件。\n");
    printf("xmlbuffer   本程序运行的参数，用xml表示，具体如下：\n\n");

    printf("connstr     数据库的连接参数，格式：username/password@tnsname。\n");
    printf("charset     数据库的字符集，这个参数要与数据源数据库保持一致，否则会出现中文乱码的情况。\n");
    printf("port        web服务监听的端口。\n\n");
}

// 把xml解析到参数starg结构中
bool _xmltoarg(char *strxmlbuffer)
{
    memset(&starg, 0, sizeof(struct st_arg));

    GetXMLBuffer(strxmlbuffer, "connstr", starg.connstr, 100);
    if (strlen(starg.connstr) == 0)
    {
        logfile.Write("connstr is null.\n");
        return false;
    }

    GetXMLBuffer(strxmlbuffer, "charset", starg.charset, 50);
    if (strlen(starg.charset) == 0)
    {
        logfile.Write("charset is null.\n");
        return false;
    }

    GetXMLBuffer(strxmlbuffer, "port", &starg.port);
    if (starg.port == 0)
    {
        logfile.Write("port is null.\n");
        return false;
    }

    return true;
}

// 读取客户端的报文
int ReadT(const int sockfd, char *buffer, const int size, const int itimeout)
{
    if (itimeout > 0)
    {
        struct pollfd fds;
        fds.fd = sockfd;
        fds.events = POLLIN;
        int iret;
        if ((iret = poll(&fds, 1, itimeout * 1000)) <= 0)
            return iret;
    }

    return recv(sockfd, buffer, size, 0);
}

// 判断URL中用户名和密码，如果不正确，返回认证失败的响应报文。
bool Login(connection *conn, const char *buffer, const int sockfd)
{
    char username[31], passwd[31];

    getvalue(buffer, "username", username, 30); // 获取用户名。
    getvalue(buffer, "passwd", passwd, 30);     // 获取密码

    // 查询T_USERINFO表，判断用户名和密码是否存在。
    sqlstatement stmt;
    stmt.connect(conn);
    stmt.prepare("select count(*) from T_USERINFO where username=:1 and passwd=:2 and rsts=1");
    stmt.bindin(1, username, 30);
    stmt.bindin(2, passwd, 30);
    int icount = 0;
    stmt.bindout(1, &icount);
    stmt.execute();
    stmt.next();

    if (icount == 0) // 认证失败，返回认证失败的响应报文。
    {
        char strbuffer[256];
        memset(strbuffer, 0, sizeof(strbuffer));

        sprintf(strbuffer,\
                "HTTP/1.1 200 OK\r\n"\
                "Server: webserver\r\n"\
                "Content-Type: text/html;charset=utf-8\r\n\r\n"\
                "<retcode>-1</retcode><message>username or passwd is invalied</message>");

        return false;
    }

    return true;
}

bool getvalue(const char *buffer, const char *name, char *value, const int len)
{
    value[0] = 0;

    char *start, *end;
    start = end = 0;

    start = strstr((char *)buffer, (char *)name);
    if (start == 0)
        return false;

    end = strstr(start, "&");
    if (end == 0)
        end = strstr(start, " ");

    if (end == 0)
        return false;

    int ilen = end - (start + strlen(name) + 1);
    if (ilen > len)
        ilen = len;

    strncpy(value, start + strlen(name) + 1, ilen);

    value[ilen] = 0;

    return true;
}
