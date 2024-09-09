#### epoll: IO多路复用

源码: [eventpoll.c - fs/eventpoll.c - Linux source code (v5.5-rc2) - Bootlin](https://elixir.bootlin.com/linux/v5.5-rc2/source/fs/eventpoll.c)

解析: [图解 | 深入揭秘 epoll 是如何实现 IO 多路复用的！ (qq.com)](https://mp.weixin.qq.com/s?__biz=MjM5Njg5NDgwNA==&mid=2247484905&idx=1&sn=a74ed5d7551c4fb80a8abe057405ea5e&scene=21#wechat_redirect)

> **场景**
>
> 当一个进程能同时处理很多个 tcp 连接时,如何发现哪条连接上有数据可读了、哪条连接可写了？





1. 低级方式: 轮询
2. 高级方式: IO多路复用
   1. select
   2. poll
   3. ==epoll==





epoll 相关的函数是如下三个：

- epoll_create：创建一个 epoll 对象
- epoll_ctl：向 epoll 对象中添加要管理的连接
- epoll_wait：等待其管理的连接上的 IO 事件















##### accept: 创建socket

当 accept 之后，进程会创建一个新的 socket 出来，专门用于和对应的客户端通信，然后把它放到当前进程的打开文件列表中。



###### 源码

accept 的系统调用代码位于源文件 `net/socket.c` 下

```cpp
//file: net/socket.c
SYSCALL_DEFINE4(accept4, int, fd, struct sockaddr __user *, upeer_sockaddr,
        int __user *, upeer_addrlen, int, flags)
{
    struct socket *sock, *newsock;

    //根据 fd 查找到监听的 socket
    sock = sockfd_lookup_light(fd, &err, &fput_needed);

    //1.1 申请并初始化新的 socket
    newsock = sock_alloc();
    newsock->type = sock->type;
    newsock->ops = sock->ops; // ops:协议操作函数集合

    //1.2 alloc申请新的 file 对象，并设置到新 socket 上
    newfile = sock_alloc_file(newsock, flags, sock->sk->sk_prot_creator->name);
    ......

    //1.3 接收连接,从sock的握手队列中获取创建好的socket
    err = sock->ops->accept(sock, newsock, sock->file->f_flags);

    //1.4 添加新文件到当前进程的打开文件列表
    fd_install(newfd, newfile);
```







##### epoll_create: 创建epoll对象

```cpp
// file：fs/eventpoll.c
struct eventpoll {
    //sys_epoll_wait用到的等待队列,阻塞在epoll对象上的用户进程
    wait_queue_head_t wq;

    //接收就绪的描述符都会放到这里,
    struct list_head rdllist;

    //每个epoll对象中都有一颗红黑树, 管理该进程所添加的socket连接
    struct rb_root rbr;
    ......
}

static int ep_alloc(struct eventpoll **pep)
{
    struct eventpoll *ep;

    //申请 epollevent 内存
    ep = kzalloc(sizeof(*ep), GFP_KERNEL);

    //初始化等待队列头
    init_waitqueue_head(&ep->wq);

    //初始化就绪列表
    INIT_LIST_HEAD(&ep->rdllist);

    //初始化红黑树指针
    ep->rbr = RB_ROOT;
    ......
}

SYSCALL_DEFINE1(epoll_create1, int, flags)
{
    struct eventpoll *ep = NULL;

    //创建一个 eventpoll 对象
    error = ep_alloc(&ep); // 初始化工作
}
```













##### epoll_ctl: 添加socket



在使用 epoll_ctl 注册每一个 socket 的时候，内核会做如下三件事情

- 1.分配一个红黑树节点对象 epitem，
- 2.添加等待事件到 socket 的等待队列中，其回调函数是 ep_poll_callback
- 3.将 epitem 插入到 epoll 对象的红黑树里

```cpp
// file：fs/eventpoll.c
struct epitem {
    //红黑树节点
    struct rb_node rbn;

    //socket文件描述符信息
    struct epoll_filefd ffd;

    //所归属的 eventpoll 对象
    struct eventpoll *ep;

    //等待队列
    struct list_head pwqlist;
}

static int ep_insert(struct eventpoll *ep, 
                struct epoll_event *event,
                struct file *tfile, int fd)
{
    //3.1 分配并初始化 红黑树节点 epitem 
    //分配一个epi对象
    struct epitem *epi;
    if (!(epi = kmem_cache_alloc(epi_cache, GFP_KERNEL)))
        return -ENOMEM;

    //对分配的epi进行初始化
    //epi->ffd中存了句柄号和struct file对象地址
    INIT_LIST_HEAD(&epi->pwqlist);
    epi->ep = ep;
    ep_set_ffd(&epi->ffd, tfile, fd);

    //3.2 设置 socket 等待队列
    //定义并初始化 ep_pqueue 对象
    struct ep_pqueue epq;
    epq.epi = epi;
    init_poll_funcptr(&epq.pt, ep_ptable_queue_proc);

    //调用 ep_ptable_queue_proc 注册回调函数 
    //实际注入的函数为 ep_poll_callback
    revents = ep_item_poll(epi, &epq.pt);

    ......
    //3.3 将epi插入到 eventpoll 对象中的红黑树中
    ep_rbtree_insert(ep, epi);
    ......
}

SYSCALL_DEFINE4(epoll_ctl, int, epfd, int, op, int, fd,
        struct epoll_event __user *, event)
{
    struct eventpoll *ep;
    struct file *file, *tfile;

    //根据 epfd 找到 eventpoll 内核对象
    file = fget(epfd);
    ep = file->private_data;

    //根据 socket 句柄号， 找到其 file 内核对象
    tfile = fget(fd);

    switch (op) {
    case EPOLL_CTL_ADD:
        if (!epi) {
            epds.events |= POLLERR | POLLHUP;
            error = ep_insert(ep, &epds, tfile, fd); // 注册事件
        } else
            error = -EEXIST;
        clear_tfile_check_list();
        break;
}
```



**在 ep_ptable_queue_proc 函数中，新建了一个等待队列项，并注册其回调函数为 ep_poll_callback 函数。然后再将这个等待项添加到 socket 的等待队列中**。









