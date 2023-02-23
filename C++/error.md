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



























