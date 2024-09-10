> 该文档用于记录发生的错误,以及debug过程,后续会在其他文档中补充其相关的知识















###### 未定义标识符 "sockaddr_in"C/C++(20)

当采用库中的struct作为函数参数时,需要加上 struct前缀









###### undefined reference to `Word::~Word()'

- 类中声明没有实现
- 没有引用库文件, 比如: 在mylog4cpp.cc中,你需要 g++ mylog4cpp.cc -llog4cpp -lpthread来链接库













###### 缺少 类模板 "std::front_insert_iterator" 的参数列表

- 对于类模板所需要的 类型参数 没有提供

  - 解决的话需要去源码看其class声明处所需要提供的类型参数

    - ```cpp
      front_insert_iterator<deque<int>>(que);
      // 这里对于 迭代器适配器而言,就需要去提供<deque<int>>这个类型参数,才可
      ```













###### const版本

​	成员函数中采用const版本,则const和非const对象都有可以调用,而如果是非const版本,则只有非const版本才可以调用

> - 先把成员函数声明为const版本

后面有“::”的名称一定是类名或命名空间名C/C++(276)



类名之后需要填入类型参数 < T >









###### C/C++(413) 不存在从 "__gnu_cxx::__normal_iterator<epoll_event *, std::vector<epoll_event, std::allocator<epoll_event>>>" 到 "epoll_event *" 的适当转换函数

[(109条消息) c++将vector迭代器转换为指针的方法_百口可乐__的博客-CSDN博客_vector 转指针](https://blog.csdn.net/m0_60352504/article/details/123411929)

迭代器和指针存在差异,不能直接作为参数传入,需要显式地转换







###### [ C++什么时候需要将#include写到头文件，什么时候需要写到cpp文件？ - 知乎 (zhihu.com)](https://www.zhihu.com/question/270945429)

















###### 20231131-hiredis中头文件和静态库的版本不符合

- 问题描述: client调用hiredis中的appendcommand,向coordinator发送消息,在coordinator节点可以通过redis-cli查到,但是在coordinator程序中用hiredis接收到的的内容为空



- 错误定位:
  1. 首先确定是redis的错误还是hiredis的错误
     1. 检查redis的log文件 - 发现没有问题
     2. 尝试调用redis-cli复现问题 - 发现redis-cli能够接收到
     3. 于是判断问题不在redis,而是在hiredis
  2. 定位到hiredis之后
     1. 前往该文件的文档里看见是不是有什么对此的记录, 于是==在github的issue中找到了相同的问题描述== - elements=0
     2. 检查发现,项目对于hiredis的要求,于是尝试查看自己机器中所使用的hiredis版本
     3. 好吧妈的,==在他们的项目中的第一个issue就是elements=0!==,这个问题就是他们自己造成的
  3. hiredis版本检查
     1. hiredis其实相当于是静态库 [linux hiredis 静态库编译 linux编译链接静态库_mob6454cc780924的技术博客_51CTO博客](https://blog.51cto.com/u_16099324/7590920)
     2. 在程序中的hiredis.h相当于是对静态库的使用介绍,



































###### 20231131-C++中赋值拷贝中没有return *this导致的bad_cast

- 问题描述, 在赋值拷贝函数中由于没有return *this而导致的bad_cast错误,但是比较奇怪的是,这个错误本应该是在链式赋值时产生的,但使用时并没有链式赋值,对比了ca集群和de集群,发现ca里的C++版本是8.0的,可能是这个导致的差异







**段错误的排查**

1. 其实这次严格意义上并没有深入到gdb调试, 因为在脚本中执行的语句没有能够ulimited,导致无法生成core文件













