

[源码分析C++的string实现 - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/267896855)

- string的常见的实现方式有几种？
- string类的内部结构是什么样子？
- string内部使用的内存是如何分配管理的？
- string是如何拷贝构造，如何析构的，有引用计数的概念吗？
- string的data()和c_str()函数有什么区别？
- std::to_string()是如何实现的？





- size: 表示真实数据的大小，一般resize函数改变的就是这个值。
- capacity：表示内部实际已经分配的内存大小，capacity一定大于等于size，当size超过这个容量时会触发重新分配机制，一般reserve函数改变的就是这个值。















































##### 构造方式





```cpp
#include<iostream>
#include<string>

using namespace std;

int main(){
    string s;               //  默认初始化，一个空白的字符串
    string s1("ssss");      // s1是字面值"ssss"的副本
    string s2(s1);          // s2是s1的副本
    string s3 = s2;         // s3是s2的副本
    string s4(10, '4');     // s4初始化
    string s5 = "Andre";    // 拷贝初始化
    string s6 = string(10, 'c');    // 可拷贝初始化，生成一个初始化好的对象，拷贝给s6

    char cs[] = "12345";
    string s7(cs, 3);       // 复制字符串cs的前三个字符到s当中

    string s8 = "abcde";
    string s9(s8, 2);

    string s10 = "asdsfasdgf";
    string s11(s10, 3, 4);  // s4是s3从下标s开始4个字符的拷贝，超出s10.size出现未定义
    return 0;
}
```



###### 采用 加号 构造

当string采用+进行拼接时,要保证 +两侧至少有一个是stirng类型的

所以 string s = "hello" + "b"时, 是会产生错误的

> 这里的"hello"并不是string类,而是字符串字面值

 











###### 流构造

```cpp
while(cin >> word)
    cout << word << endl;
	func(word);
// 对于输入的一段文本,逐词处理
```

> 需要注意的是, string对于流的输入, 会自动忽略开头和结尾的空格
>
> 即输入 "    hello word" , s1会读取"hello",如果是 `cin >> s1 >> s2`,那么s2会读取到"word"























##### 相关api















###### string转换为int

```cpp
template <typename T>
inline bool FromString(const std::string& sString, T &tX)
{
    std::istringstream iStream(sString);
    return !(iStream >> tX).fail(); // extract value into tX, return success or not
}

int main()
{
    double dX;
    if (FromString("3.4", dX))
        cout << dX << '\n';
    if (FromString("ABC", dX))
        cout << dX << '\n';
}

// 无论是number→string 还是string→number,都需要调用 sstream
```



###### split

[C++常见问题: 字符串分割函数 split - dfcao - 博客园 (cnblogs.com)](https://www.cnblogs.com/dfcao/p/cpp-FAQ-split.html)

```cpp
#include <vector>
#include <string>
#include <iostream>
using namespace std;

vector<string> split(const string &s, const string &seperator){
  	vector<string> result;
 	typedef string::size_type string_size;
  	string_size i = 0;
  
  	while(i != s.size()){
    	//找到字符串中首个不等于分隔符的字母；
    	int flag = 0;
    	while(i != s.size() && flag == 0){
      	flag = 1;
      	for(string_size x = 0; x < seperator.size(); ++x)
    　　	 if(s[i] == seperator[x]){
      　　	++i;
      　　	flag = 0;
     　　 	break;
    　　}
    }
    
    //找到又一个分隔符，将两个分隔符之间的字符串取出；
    flag = 0;
    string_size j = i;
    while(j != s.size() && flag == 0){
      for(string_size x = 0; x < seperator.size(); ++x)
    　　if(s[j] == seperator[x]){
      　　flag = 1;
     　　 break;
    　　}
      if(flag == 0) 
    　　++j;
    }
    if(i != j){
      result.push_back(s.substr(i, j-i));
      i = j;
    }
  }
  return result;
}

int main(){
  string s = "a,b*c*d,e";
  vector<string> v = split(s, ",*"); //可按多个字符来分隔;
  for(vector<string>::size_type i = 0; i != v.size(); ++i)
    cout << v[i] << " ";
  cout << endl;
  //输出: a b c d
}


void SplitString(const std::string& s, std::vector<std::string>& v, const std::string& c)
{
  std::string::size_type pos1, pos2;
  pos2 = s.find(c);
  pos1 = 0;
  while(std::string::npos != pos2)
  {
    v.push_back(s.substr(pos1, pos2-pos1));
 
    pos1 = pos2 + c.size();
    pos2 = s.find(c, pos1);
  }
  if(pos1 != s.length())
    v.push_back(s.substr(pos1));
}
```









- std::ws - 输入时忽略句首的空格(防止上次不读完,下次读错的)

```cpp
 std::getline(std::cin >> std::ws, name); // note: added 
```

















##### 混用int和s.size()

> 由于size返回的类型为 无符号的 size_type 类型
>
> 所以当遇到 s.size()-3 这种情况, 可能会使得该值为int中的负数,解释为无符号之后成为一个很大的正值

[C++错误：s.size()与int混用_北冥有鱼wyh的博客-CSDN博客](https://blog.csdn.net/qq_34801642/article/details/109466539)





##### 浅拷贝所导致的重复析构



[ string类的深拷贝和浅拷贝_string浅拷贝与深拷贝_Young_LAS的博客-CSDN博客](https://blog.csdn.net/xiaozuo666/article/details/80203259)

> 复制时只是将指针复制了过去,而不是复制了其指针指向的内容
>
> - 可能会由于多个指针指向了同一片内存,导致指针对象的析构产生重复析构
> - 由于指针的赋值导致原本指向的空间产生内存泄漏







需要重写 **拷贝构造函数** 和 **赋值运算符** 

```cpp
//拷贝构造函数
String::String(const String& s)
    :_str(new char[strlen(s._str)+1])
{
    if (s._str != NULL)
        strcpy(_str, s._str);
}

//赋值运算符重载
String& String::operator=(const String& s)
{
    if (NULL != s._str)
    {
        delete[] _str;
        _str = new char[strlen(s._str) + 1];
        strcpy(_str, s._str);
    }

    return *this;
}
```









##### string的实现方式

> - 深拷贝(eager copy)
>   - 缺陷 - 做只读操作时,用深拷贝是没必要的
> - 写时复制(COW)
>   - 单核
>   - 原理 - 浅拷贝 + 引用计数
>   - 引用计数
> - 短字符串优化(SSO)
>   - 多核
>









###### 浅拷贝+引用计数



对于计数

应当设置为所有引用共享

设置为static变量,共享引用计数

- 但是当需要写时复制时, 此时需要一个新的,面向写之后的str的count

引用计数必须要放置在堆中,用int * 指向

- 放置在string的前四个字节

  - ```cpp
    String(const char * pstr)
    : _pstr(new char[strlen(pstr) + 5]() + 4) // pstr需要指向str的内容
    ```








如果调用了下标访问运算符则判断为需要进行深拷贝(写时复制)

这种方案的缺陷在于 - 将下标访问一律视为需要进行写操作,而其中是存在有不需要写只进行读的情况的

解决方案: 如果要区分出读操作和写操作需要重载赋值运算符,和输出流运算符操作

但由于下标访问运算符的返回值是一个char&类型,即内置类型而不是自定义类型,无法去重载运算符

因此为解决该问题,需要下标运算符返回一个自定义的类型 charProxy,然后再去重载相应的运算符

由于该类仅仅是为了解决读写分歧,因此不适合作为全局类来定义,只适合采用嵌套类的方式去定义



如果将charProxy作为普通类去定义,想要去访问String中的值都需要将string对象作为参数传入



char = (charproxy) str[i] - 调用的是 char类型的赋值语句

(charproxy) str[i] = char - 调用的是 插入Proxy的赋值语句



###### string类的缺陷

[(26 封私信 / 86 条消息) C++ 更常用 string 还是 char* 呢？ - 知乎 (zhihu.com)](https://www.zhihu.com/question/483774144)

STL文件都没有实现多线程安全 

std::string是字节流而不是字符流,并不支持字符集

所以在时机开发中,都要去自定义字符串的库,或者直接使用第三方库





##### string类的遍历

1. operator[] 下标运算符
2. iterator 迭代器
3. 增强for循环