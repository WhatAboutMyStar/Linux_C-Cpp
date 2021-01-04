## 创建套接字
### int socket(int family,int type,int protocol);
- 功能：创建一个用于网络通信的socket套接字（描述符）
- 参数：<br>
family:协议族(AF_INET、AF_INET6、PF_PACKET等)<br>
type:套接字类(SOCK_STREAM、SOCK_DGRAM、SOCK_RAW等)<br>
protocol:协议类别(0、IPPROTO_TCP、IPPROTO_UDP等<br>

- 返回值：套接字
- 头文件：#include <sys/socket.h>

### 地址结构
- 头文件#include <netinet/in.h>
```
struct in_addr
{
	in_addr_t s_addr;//4字节
};
struct sockaddr_in
{
	sa_family_t sin_family;//2字节
	in_port_t sin_port;//2字节
	struct in_addr sin_addr;//4字节
	char sin_zero[8]//8字节
};

为了使不同格式地址能被传入套接字函数,地址须要强制转换成通用套接字地址结构
struct sockaddr
{
	sa_family_t sa_family;	// 2字节
	char sa_data[14]	//14字节
};

```

### 发送数据—sendto函数
```
ssize_t sendto(int sockfd，const void *buf,
                 size_t nbytes,int flags,
                 const struct sockaddr *to,        
                 socklen_t addrlen);
功能：
  向to结构体指针中指定的ip，发送UDP数据
参数：
  sockfd：套接字
  buf：	 发送数据缓冲区
  nbytes: 发送数据缓冲区的大小

  flags：一般为0
  to：	指向目的主机地址结构体的指针
  addrlen：to所指向内容的长度
注意：
  通过to和addrlen确定目的地址
  可以发送0长度的UDP数据包
返回值：
  成功:发送数据的字符数
  失败: -1

```
### 绑定 bind函数
```
int bind(int sockfd, const struct sockaddr *myaddr, socklen_t addrlen);
功能：
  将本地协议地址与sockfd绑定
参数：
  sockfd： socket套接字
  myaddr： 指向特定协议的地址结构指针
  addrlen：该地址结构的长度
返回值：
  成功：返回0
  失败：其他
头文件:
  #include <sys/socket.h>
```

### 接收数据—recvfrom 函数
```
ssize_t recvfrom(int sockfd, void *buf,
                size_t nbytes,int flags,
		     		    struct sockaddr *from, 
           		  socklen_t *addrlen);
功能：
  接收UDP数据，并将源地址信息保存在from指向的结构中
参数：
  sockfd:	套接字
  buf：接收数据缓冲区
  nbytes:接收数据缓冲区的大小
  flags：	 套接字标志(常为0)
  from：	 源地址结构体指针，用来保存数据的来源
  addrlen: from所指内容的长度
注意：
  通过from和addrlen参数存放数据来源信息
  from和addrlen可以为NULL, 表示不保存数据来源
返回值：
  成功:接收到的字符数
  失败: -1
```
### connect函数
```
int connect(int sockfd,
      		 const struct sockaddr *addr,
     		 	 socklen_t len);
功能：
  主动跟服务器建立链接
参数：
  sockfd：socket套接字
  addr:   连接的服务器地址结构
  len：	 地址结构体长度
返回值：
  成功：0    失败：其他
头文件：
  #include <sys/socket.h>
```
### send函数
```
ssize_t send(int sockfd, const void* buf,size_t nbytes, int flags);
功能：
  用于发送数据
参数：
  sockfd： 已建立连接的套接字
  buf：	   发送数据的地址
  nbytes:  发送缓数据的大小(以字节为单位)
  flags:	   套接字标志(常为0)
返回值：
  成功发送的字节数
头文件：
  #include <sys/socket.h>
```

### recv函数
```
ssize_t recv(int sockfd, void *buf, size_t nbytes, int flags);
功能：
  用于接收网络数据
参数：
  sockfd：套接字
  buf:	接收网络数据的缓冲区的地址
  nbytes:	接收缓冲区的大小(以字节为单位)
  flags:	套接字标志(常为0)
返回值：
  成功接收到字节数
头文件：
  #include <sys/socket.h>
```

### listen 函数
```
int listen(int sockfd, int backlog);
功能：
  将套接字由主动修改为被动
  使操作系统为该套接字设置一个连接队列，用来记录所有连接到该套接字的连接
参数：
  sockfd： socket监听套接字
  backlog：连接队列的长度
返回值：
  成功：返回0
  失败：其他
头文件：
  #include <sys/socket.h>
```
### accept函数
```
int accept(int sockfd,struct sockaddr *cliaddr, socklen_t *addrlen);
功能：
  从已连接队列中取出一个已经建立的连接，如果没有任何连接可用，则进入睡眠等待(阻塞)
参数：
  sockfd： socket监听套接字
  cliaddr: 用于存放客户端套接字地址结构
  addrlen：套接字地址结构体长度的地址
返回值：
  已连接套接字
头文件：
  #include <sys/socket.h>
```


