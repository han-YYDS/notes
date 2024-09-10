# Nginx 简介

## Ngnix 特点

- 模块化设计：良好的扩展性，可以通过模块方式进行功能扩展。
- 高可靠性：主控进程和 worker 是同步实现的，一个 worker 出现问题，会立刻启动另一个 worker。
- 内存消耗低：一万个长连接（keep-alive）,仅消耗 2.5MB 内存。
- 支持热部署：不用停止服务器，实现更新配置文件，更换日志文件、更新服务器程序版本。
- 并发能力强：官方数据每秒支持 5 万并发；
- 功能丰富：优秀的反向代理功能和灵活的负载均衡策略

## Nginx 功能

- 支持静态资源的 web 服务器。
- http,smtp,pop3 协议的反向代理服务器、缓存、负载均衡；
- 支持 FASTCGI（fpm）
- 支持模块化，过滤器（让文本可以实现压缩，节约带宽）,ssl 及图像大小调整。
- 内置的健康检查功能
- 基于名称和 ip 的虚拟主机
- 定制访问日志
- 支持平滑升级
- 支持 KEEPALIVE
- 支持 url rewrite
- 支持路径别名
- 支持基于 IP 和用户名的访问控制。
- 支持传输速率限制，支持并发数限制。

## Nginx 性能

Nginx 的高并发，官方测试支持 5 万并发连接。实际生产环境能到 2-3 万并发连接数。10000 个非活跃的 HTTP keep-alive 连接仅占用约 2.5MB 内存。三万并发连接下，10 个 Nginx 进程，消耗内存 150M。淘宝 tengine 团队测试结果是“24G 内存机器上，处理并发请求可达 200 万”。

## Ngnix 架构

### 主从模式

![img](https://raw.githubusercontent.com/dunwu/images/master/snap/20200125161055.png)

**Nginx 采用一主多从的主从架构**。

但是这里 master 是使用 root 身份启动的，因为 nginx 要工作在 80 端口。而只有管理员才有权限启动小于低于 1023 的端口。master 主要是负责的作用只是启动 worker，加载配置文件，负责系统的平滑升级。其它的工作是交给 worker。那么当 worker 被启动之后，也只是负责一些 web 最简单的工作，而其他的工作都是有 worker 中调用的模块来实现的。

模块之间是以流水线的方式实现功能的。流水线，指的是一个用户请求，由多个模块组合各自的功能依次实现完成的。比如：第一个模块只负责分析请求首部，第二个模块只负责查找数据，第三个模块只负责压缩数据，依次完成各自工作。来实现整个工作的完成。

他们是如何实现热部署的呢？其实是这样的，我们前面说 master 不负责具体的工作，而是调用 worker 工作，他只是负责读取配置文件，因此当一个模块修改或者配置文件发生变化，是由 master 进行读取，因此此时不会影响到 worker 工作。在 master 进行读取配置文件之后，不会立即的把修改的配置文件告知 worker。而是让被修改的 worker 继续使用老的配置文件工作，当 worker 工作完毕之后，直接当掉这个子进程，更换新的子进程，使用新的规则。

### sendfile 机制

**Nginx 支持 sendfile 机制**。

所谓 Sendfile 机制，是指：用户将请求发给内核，内核根据用户的请求调用相应用户进程，进程在处理时需要资源。此时再把请求发给内核（进程没有直接 IO 的能力），由内核加载数据。内核查找到数据之后，会把数据复制给用户进程，由用户进程对数据进行封装，之后交给内核，内核在进行 tcp/ip 首部的封装，最后再发给客户端。这个功能用户进程只是发生了一个封装报文的过程，却要绕一大圈。因此 nginx 引入了 sendfile 机制，使得内核在接受到数据之后，不再依靠用户进程给予封装，而是自己查找自己封装，减少了一个很长一段时间的浪费，这是一个提升性能的核心点。

<div align="center"><img src="https://images2015.cnblogs.com/blog/820332/201512/820332-20151227195957171-1801771404.jpg"/></div>

以上内容摘自网友发布的文章，简单一句话是资源的处理，直接通过内核层进行数据传递，避免了数据传递到应用层，应用层再传递到内核层的开销。

目前高并发的处理，一般都采用 sendfile 模式。通过直接操作内核层数据，减少应用与内核层数据传递。

### I/O 复用机制

**Nginx 通信模型采用 I/O 复用机制**。

开发模型：epoll 和 kqueue。

支持的事件机制：kqueue、epoll、rt signals、/dev/poll 、event ports、select 以及 poll。

支持的 kqueue 特性包括 EV_CLEAR、EV_DISABLE、NOTE_LOWAT、EV_EOF，可用数据的数量，错误代码.

支持 sendfile、sendfile64 和 sendfilev;文件 AIO；DIRECTIO;支持 Accept-filters 和 TCP_DEFER_ACCEP.

以上概念较多，大家自行百度或谷歌，知识领域是网络通信（BIO,NIO,AIO）和多线程方面的知识。

## Nginx 负载均衡

nginx 的负载均衡策略可以划分为两大类：内置策略和扩展策略。内置策略包含加权轮询和 ip hash，在默认情况下这两种策略会编译进 nginx 内核，只需在 nginx 配置中指明参数即可。扩展策略有很多，如 fair、通用 hash、consistent hash 等，默认不编译进 nginx 内核。由于在 nginx 版本升级中负载均衡的代码没有本质性的变化，因此下面将以 nginx1.0.15 稳定版为例，从源码角度分析各个策略。

### 加权轮询

**Nginx 支持加权轮询（Weighted Round Robin）负载均衡**。

轮询的原理很简单，首先我们介绍一下轮询的基本流程。如下是处理一次请求的流程图：

<div align="center"><img src="https://images2015.cnblogs.com/blog/820332/201512/820332-20151227201913984-412518987.jpg"/></div>

图中有两点需要注意，第一，如果可以把加权轮询算法分为先深搜索和先广搜索，那么 nginx 采用的是先深搜索算法，即将首先将请求都分给高权重的机器，直到该机器的权值降到了比其他机器低，才开始将请求分给下一个高权重的机器；第二，当所有后端机器都 down 掉时，nginx 会立即将所有机器的标志位清成初始状态，以避免造成所有的机器都处在 timeout 的状态，从而导致整个前端被夯住。

### Ip Hash

**Nginx 支持 Ip Hash 负载均衡**。

通过 Ip Hash 这种负载均衡策略，可以实现会话粘滞。

### Fair

fair 策略是扩展策略，默认不被编译进 nginx 内核。其原理是根据后端服务器的响应时间判断负载情况，从中选出负载最轻的机器进行分流。这种策略具有很强的自适应性，但是实际的网络环境往往不是那么简单，因此要慎用。

### 通用 Hash、一致性 Hash

这两种也是扩展策略，在具体的实现上有些差别，通用 hash 比较简单，可以以 nginx 内置的变量为 key 进行 hash，一致性 hash 采用了 nginx 内置的一致性 hash 环，可以支持 memcache。

## Nginx 场景

Ngnix 一般作为入口负载均衡或内部负载均衡，结合反向代理服务器使用。以下架构示例，仅供参考，具体使用根据场景而定。

### 入口负载均衡架构

<div align="center"><img src="https://images2015.cnblogs.com/blog/820332/201512/820332-20151227202044781-2116477406.png"/></div>

Ngnix 服务器在用户访问的最前端。根据用户请求再转发到具体的应用服务器或二级负载均衡服务器（LVS）

### 内部负载均衡架构

<div align="center"><img src="https://images2015.cnblogs.com/blog/820332/201512/820332-20151227202054421-2015542569.png"/></div>

LVS 作为入口负载均衡，将请求转发到二级 Ngnix 服务器，Ngnix 再根据请求转发到具体的应用服务器。

### Ngnix 高可用

<div align="center"><img src="https://images2015.cnblogs.com/blog/820332/201512/820332-20151227202100921-915093452.png"/></div>

分布式系统中，应用只部署一台服务器会存在单点故障，负载均衡同样有类似的问题。一般可采用主备或负载均衡设备集群的方式节约单点故障或高并发请求分流。

Ngnix 高可用，至少包含两个 Ngnix 服务器，一台主服务器，一台备服务器，之间使用 Keepalived 做健康监控和故障检测。开放 VIP 端口，通过防火墙进行外部映射。

DNS 解析公网的 IP 实际为 VIP。