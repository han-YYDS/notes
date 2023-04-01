

#### effective stl 50条建议

[《Effective STL 》全书阅读笔记 - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/458156007)



##### 第 1 条: 容器类型 - 挑选合适的容器

> 简要介绍了容器的使用场景

区分关联式容器和序列容器: 区别在于是否会因为增删改而导致需要对其余的元素进行移动来保证内存的连续性



- **是否需要在容器的==任意位置插入新元素==？** 如果需要，就选择序列容器否则选择关联容器。
- **是否关心容器中元素是==排序==的？** 如果不关心则哈希容器是一个可行选择方案；否则你要避免哈希容器。
- **需要哪种类型的==迭代器==？** 如果必须是随机访问迭代器(通过下标访问)，则对容器的选择就限定为vector、deque和string。如果要求使用双向迭代器，则避免使用slist和哈希容器。
- **当发生元素的插入和删除操作时候，避免移动容器中原来的元素是否重要？** 如果是就要避免选择序列容器。
- **容器中数据布局是否需要和C保持兼容？** 如果是是只能选择 vector。
- **元素的==查找速度==是否是关键的考虑因素？** 如果是考虑哈希容器。
- **如果容器内部使用==引用计数技术==是否介意？** 如果是则避免使用string因为许多string的实现都是用了引用计数。如果需要表示某种字符串的方法，可以使用vector方法。
- **对插入和删除操作，需要==事务语义==么** 在插入和操作失败的时需要回滚的能力么？如果需要就有使用基于节点的容器，如果需要对多个元素插入操作需要事务，则可以选择list。因为在标准容器中，只有list提供了多个元素的事务语义。但注意：事务语义对编写异常安全代码很重要但同时付出性能上代价。
- **需要使用迭代器、指针和引用失效的次数最少么** 如果是就需要使用基于节点的容器，因为这类对容器的插入和删除从来不会使用迭代器和指针和引用无效；而对连续内存的容器的插入和删除一般会对指向该容器的迭代器和指针、引用变为无效。
- **如果在容器上使用swap使得迭代器失效了会在意吗** 如果在意那么避免使用 string，因为 string 是唯一在STL中 swap 操作过程中导致迭代器、指针和引用无效唯一的容器。
- **如果序列容器迭代器是随机访问，而且只要没有删除操作发生，且插入操作只发生容器末尾，则指向数据的指针和引用就不会变为无效，这样容器是否考虑** 这是一种很特殊的情况，如果是则 deque 满足你的需求，deque 是唯一的迭代器可能会变为无效和指针和引用不会变为无效的 STL 标准容器。





##### 第 2 条: 不要编写独立于容器的代码

> 意思是要写针对于容器的代码,而不要去实现泛型的代码

==试图编写对序列式容器和关联式容器都适用的代码几乎是毫无意义的。==面对实际情况，不同容器是不同的，它们有非常明显的优缺点，不同的适用场景适合选择不同的容器。



##### **第 3 条：确保容器中的对象拷贝正确而高效**

###### copy in, copy out 

> 文章中说, 存入容器和从容器取出的都是拷贝的对象(copy in, copy out) 在这一点上和 深浅拷贝的联系在于?



###### 剥离问题

如果你创建了一个存放基类对象的容器，却向其中插入派生类的对象，那么在派生类对象(通过基类的拷贝构造函数)被拷贝进容器时，它所特有的部分(即派生类中的信息)将会丢失。**剥离问题**意味着向基类对象的容器中插入派生类对象几乎总是错误的。

> 使拷贝动作高效、正确，并防止剥离问题发生的一个简单办法是使容器包含指针而不是对象。



##### **第 4 条：调用 empty 而不是检查 size() 是否为 0**



在一些容器实现中, size()和empty()的实现的特点,可能导致其两者之间的效率存在差距



list源码

1、Aix

```cpp
size_type size() const

​            {return (_Size); }

 


bool empty() const

​            {return (size() == 0); }
```

 

​    Aix上对于在list中的处理方式依然和vector一样，维护了一个_Size变量，empty()多了一层函数调用，效率较低。




2、Centos

```cpp
size_type size() const

​            { return std::distance(begin(), end()); }

 


bool empty() const

​            { return this->_M_impl._M_node._M_next ==&this->_M_impl._M_node; }
```

 

​    size()函数调用了distance函数用遍历的方法取得两个指针间的元素个数，然后返回。而empty()函数则是判断头指针的下一个节点是否是自己本身，只需要进行一次判断。所以，当list容器元素个数较多的时候，这里的empty()效率远大于size() == 0。



##### **第 5 条：区间成员函数优先于与之对应的单元素成员函数**

> 即对于容器中一段范围内的元素进行操作的两种方式
>
> 1. 通过描述范围来操作
> 2. 通过遍历这段范围内的每个元素,依次进行操作



优点

- 明智地使用区间插入而不是单元素重复插入会提高程序的性能问题，比如对于vector来说如果内存已满再插入新元素会触发两倍扩容，区间插入不必多次重新分配内存。



有哪些区间成员函数?

​	insert、erase、assign





##### **第 6 条：当心 C++ 编译器最烦人的分析机制**

> 指的是 double() 和 (double)的区别,前者指的是函数指针,后者的括号则无伤大雅











##### **第 7 条：如果容器中包含了通过 new 操作创建的指针，切记在容器对象析构前将指针 delete 掉**

> 当容器中存在通过new创建的指针时,对容器进行析构只会析构其指针,而不会析构指针指向的内存空间,这样就会产生内存泄漏



通过 智能引用计数指针对象 来代替指针,可以避免由于异常造成来不及释放从而导致内存泄漏







##### **第 8 条：切勿创建包含 auto_ptr 的容器对象**

- 缺点之一: COAPs不可移植

当你拷贝一个auto_ptr时，auto_ptr所指向对象的所有权被转移到拷贝的auto_ptr，而被拷贝的auto_ptr被设为 NULL。 换句话说, 拷贝一个auto_ptr会改变其值















##### **第 9 条：慎重选择删除元素的方法**



如果容器是 vector，string 或deque，则使用 erase-remove 习惯用法；

如果容器是list，则使用 list::remove；

如果容器是一个标准关联容器，则使用它的 erase 成员函数。  



如果需要做一些除了删除之外的事情的话, 需要在循环遍历中每次调用erase时, 用其返回值来更新迭代器











##### **第 10 条：了解分配子(allocator)的约定和限制**

分配器有一些不好的地方

可移植的分配器不可以有任何非静态的数据成员



里面的一大段我都不是很能看懂











[C++中虚析构函数的作用及其原理分析_逐鹿之城的博客-CSDN博客](https://blog.csdn.net/derkampf/article/details/62093252)

虚析构函数使得在删除 指向子类对象的基类指针 时可以调用子类的析构函数(而不是基类的析构函数)从而达到释放子类中堆内存的目的，而防止内存泄露的



















##### **第 11 条：理解并自定义分配子的合理用法**



默认的STL allocator可能有一些特点不是适合于我的适用场景,需要自定义allocator



里面的一大堆都看得不是很懂











##### 第 12 条：对STL容器线程安全性的期待现实一些  



一般如何实现一个线程安全的容器?

1. 调用成员函数时需要上锁
2. 返回的迭代器的生存期之内都需要上锁
3. 容器上调用算法执行期间上锁



###### RAII

使用一个类（像Lock）来管理资源的生存期（例如互斥量）的办法通常称为  资源获得即初始化  



> [c++经验之谈一：RAII原理介绍 - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/34660259)
>
> 由操作系统来管理的生命周期与资源的释放相绑定,实现自动释放
>
> 在构造函数中初始化,在析构函数中进行资源的销毁



而且这么做是异常安全的, 当因为异常而导致局部对象销毁时,Lock也会调用其析构函数,但如果是手动释放,就会因为异常而导致错过





##### **第 13 条：vector和string优先于动态分配的数组**



尽量使用vector和string 而不是 char* 即C风格的数组和字符串



当使用数组通过new进行动态分配时

1. 确保会被delete
2. 确保正确地new和delete, 即delete和delete[],前者是对一个单独的对象,后者是对一个数组
3. 确保只会delete一次



vector和string能够满足动态的内存增长,并且当析构时,能够自动释放容器中的元素



采用了引用计数的string,虽然能够在内存分配和字符串拷贝上产生优化,但如果是在多线程中使用该string,会由于线程安全所带来性能下降问题

如果想要避免这个问题

1. 查看库中能否关闭引用计数
2. 查看是否能用其他实现方式的string
3. 使用vector<char>来代替string









##### **第 14 条：使用 reserve 来避免不必要的重新分配**

realloc [realloc()函数解析_c语言realloc函数_hackerain的博客-CSDN博客](https://blog.csdn.net/hackerain/article/details/7954006)

> [realloc](https://so.csdn.net/so/search?q=realloc&spm=1001.2101.3001.7020)(void *__ptr, size_t __size)：更改已经配置的内存空间，即更改由malloc()函数分配的内存空间的大小。

如果将分配的内存减少，realloc仅仅是改变索引的信息。

如果是将分配的内存扩大，则有以下情况：
1）如果当前内存段后面有需要的内存空间，则直接扩展这段内存空间，realloc()将返回原指针。
2）如果当前内存段后面的空闲字节不够，那么就使用堆中的第一个能够满足这一要求的内存块，将目前的数据==复制==到新的位置，并将原来的数据块释放掉，返回新的内存块位置。
3）如果申请失败，将返回NULL，此时，原来的指针仍然有效



> vector和string的扩容类似于realloc操作, 其扩容的因数为2
>
> 但这样有可能仅仅因为insert一个元素,就导致扩容为2倍,并有可能由于需要重新分配而导致之前的迭代器,指针,引用都失效
>
> reserve成员函数允许你最小化必须进行的重新分配的次数 
>
> - size() - 有效大小
>
> - capacity() - 分配的大小,包括未使用到的预留空间
> - resize(Container::size_type n)强制把容器改为容纳n个元素。调用resize之后，size将会返回n(就是输入的参数)。
>   - 如果n小于当前大小，容器尾部的元素会被销毁。
>   - 如果n大于当前大小，新默认构造的元素会添加到容器尾部。如果n大于当前容量，在元素加入之前会发生重新分配。
> - reserve(Container::size_type n) - 预留
>   - 强制容器把它的容量改为至少n，提供的n不小于当前大小。这一般强迫进行一次重新分配，因为容量需要增加,如果n小于当前容量，vector忽略它，这个调用什么都不做
>
> [vector中resize()和reserve()区别_Jocodeoe的博客-CSDN博客](https://blog.csdn.net/jocodeoe/article/details/9230879)
>
> - resize(n)之后,size即为n
>
> - reserve(n)之后
>
>   - 如果capacity<n，则重新分配内存空间，从而使得capacity等于n。
>
>   - 如果capacity>=n呢？capacity无变化。
>
> - resize之后,空间已经被初始化,访问不会产生越界
>
> - reverse之后,预分配的空间不可访问
>
>   



防止重新分配的关键在于, 使用 reserve尽快把容器的容量设置为足够大，最好在容器被构造之后立刻进行。 

```cpp
// 代码1
vector<int> v;
for (int i = 1; i <= 1000; ++i) v.push_back(i);

// 代码2
vector<int> v;
v.reserve(1000);
for (int i = 1; i <= 1000; ++i) v.push_back(i);

// 代码2中不会发生重新分配, 伴随着的, 其迭代器也不会有失效的情况
```

 















##### **第 15 条：注意 string 实现的多样性**

string对象中包含的信息

1. 字符串大小
2. 字符串的字符
3. 字符串容量

可能包含有引用计数

> 主要讲的是,string中可能因为 需要维持线程安全,可能由于采用了短字符串优化, 从而导致string对象和char*的大小很不一样
>
> - string 的值可能会被引用计数，也可能不会。很多实现在默认情况下会使用引用计数，但它们通常提供了关闭默认选择的方法，往往是通过预处理宏来做到这一点。
> - string 对象大小的范围可以是一个 char* 指针大小的 1 倍到 7 倍。
> - 创建一个新的字符串值可能需要零次、一次或两次动态分配内存。
> - string 对象可能共享，也可能不共享其大小和容量信息。
> - string 可能支持，也可能不支持针对单个对象的分配子。
> - 不同的实现对字符内存的最小分配单位有不同的策略。













##### **第 16 条：了解如何把 vector 和 string 数据传给旧的 API**(C)

> 1. vector -> T* : &v[0]
> 2. string -> char* : c_str()
> 3. T* -> vector : &v[0] 以及配合resize
> 4. char* -> string: 如上先转换为 vector<char> 再构造为string

###### vector -> T*

vector<T> v -> T* : &v[0] 对首元素取地址即为C风格数组

需要注意的是,对v需要有判空操作,以免产生越界访问



v.begin() 和 &v[0]

- begin是迭代器而不是指针,如果需要一个直接指向内存数据的指针时绝不该使用iterator, 可以调用&*v.begin()来达到与&v[0]相同的效果



###### string -> char*

但是这种用于vector的方法放到string上不一定可靠,因为

1. string并没有保证数据连续存储
2. stirng内部并没有承诺都以null字符结尾

调用string中的c_str()成员函数来进行到char*的转换

没有承诺说,c_str()返回的char*指针指向string的内部数据内存区域



> 通常,上述两种转换为指针的方法,都是作为const参数传入函数的,函数对其只读而不做修改.
>
> 比如对于参数为数组指针的函数,如果当其capacity=size时,通过指针append一个新的元素,可能会产生预想不到的后果,针对于size和capacity的限制是需要满足的



###### T* -> vector

如果将C风格数组转化为vector

```cpp
// C API：此函数需要一个指向数组的指针，数组最多有arraySize个double
// 而且会对数组写入数据。它返回写入的double数，不会大于arraySize
size_t fillArray(double *pArray, size_t arraySize); // double* -> vector
vector<double> vd(maxNumDoubles);
vd.resize(fillArray(&vd[0], vd.size())); // 让fillArray把数据写入vd，然后调整vd的大小为fillArray写入的元素个数
```

这个技巧只能工作于vector，因为==只有vector承诺了与数组具有相同的潜在内存分布==。



###### char* -> string

但是，如果你想用来自C风格API的数据初始化string对象，也很简单。只要让API将数据放入一个vector<char>，然后从vector中将数据拷到string  

```cpp
// C API：此函数需要一个指向数组的指针，数组最多有arraySize个char

size_t fillString(char *pArray, size_t arraySize); // 而且会对数组写入数据。它返回写入的char数，不会大于arraySize
vector<char> vc(maxNumChars); // 建立一个vector，
// 它的大小是maxNumChars
size_t charsWritten = fillString(&vc[0], vc.size()); // 让fillString把数据写入vc
string s(vc.begin(), vc.begin()+charsWritten); // 从vc通过范围构造函数
```



事实上,从C风格数组指针转换为任何STL容器,都可以先转换为vector,然后再调用其api进行转换构造

























##### **第 17 条：使用”swap技巧”除去多余的容量**



> 当vector的size减小,但是capacity依然很大时,需要将capacity减小到现在需要的合适大小 (shrink to fit)



```cpp
class Contestant {...};
vector<Contestant> contestants;

vector<Contestant>(contestants).swap(contestants);
// 表达式vector<Contestant>(contestants)建立一个临时vector，它是contestants的一份拷贝：vector的拷贝构造函数做了这个工作。
// 但是，vector的拷贝构造函数只分配拷贝的元素需要的内存，所以这个临时vector没有多余的容量。
// 然后我们让临时vector和contestants交换数据，这时我们完成了，contestants只有临时变量的修整过的容量，而这个临时变量则持有了曾经在contestants中的发胀的容量。
// 在这里（这个语句结尾），临时vector被销毁，因此释放了以前contestants使用的内存。 瞧！ 收缩到合适
```



是收缩到合适,而不是收缩到尽可能小















##### **第 18 条： 避免使用 vector < bool> 类型**



> vector<bool>
>
> 1. 并不是一个stl容器
> 2. 并不容纳bool



满足成为STL容器的必要条件:

如果c是一个T类型对象的容器，且c支持operator[]，那么以下代码必须能够编译：  

```cpp
T *p = &c[0]; // 无论operator[]返回什么，都可以用这个地址初始化一个T*
// 即, 如果采用 下标运算符[] 得到vector中的一个元素对象,需要能够通过取地址来获得指向该元素的指针
```

但是vector<bool>不能, 因为他实际上是一个伪容器,并不保存真正的bool,而是打包bool以节省空间 

在一个典型的实现中，每个保存在“vector”中的“bool”占用一个单独的比特，而一个8比特的字节将容纳8个“bool”。在内部vector<bool>使用了与位域（bitfield）等价的思想来表示它假装容纳的bool。  

和上述的stl必要条件冲突的点在于,不存在指向单个bite的指针,引用单个bite也是禁止的

vector<bool>::operator[] 返回一个对象,即代理对象,

```cpp
template <typename Allocator>
vector<bool, Allocator> {
public:
class reference {...}; // 用于产生引用独立比特的代理类 reference
reference operator[](size_type n); // operator[]返回一个代理
...
}
```



替代方法

1. deque<bool> 其中存储了真正的bool值
2. bitset













##### **第 19 条：关联容器中:理解相等(equality)和等价(equivalence)的区别**



find和insert的不同之处

- find基于相等 -> operator==
- insert基于等价 -> operator<
  - 等价基于在有序区间中对象值的相对位置, 在排序方面的意义(set,map), 即谁也不在谁前面意味着等价



由于标准关联容器保持有序,所以每个容器需要有一个比较函数来定义顺序,等价就是根据这个顺序来定义的.

所以当我们定义了一个忽略大小写的set时,即需要自定义一个compare,在其中实现忽略大小写的逻辑,然后在申明set时作为参数传入

set<string,compare> stringSet

当我们向这个set插入string时,只有大小写存在区别的string会被视为等价,但是当通过 == 来判断时,这两个string自然是不相等的

















##### **第 20 条：为包含指针的关联容器指定比较类型**



```cpp
set<string*> ssp; // ssp = “set of string ptrs”
ssp.insert(new string("Anteater"));
ssp.insert(new string("Wombat"));
ssp.insert(new string("Lemur"));
ssp.insert(new string("Penguin"));
for (set<string*>::const_iterator i = ssp.begin(); // 你希望看到
i != ssp.end();++i)
	cout << **i << endl; 
```

因为set容纳指针,所以其迭代器指向的是指向string的指针

输出的set其顺序是按字符串的地址决定,而不是其内容,所以如果想要其按照字符串内容输出,需要为其指针指定比较

因为本质上,`set<string*>即为 set<string,less<string*>>`

```cpp
struct StringPtrLess:
public binary_function<const string*, const string*, bool> {
    bool operator()(const string *ps1, const string *ps2) const
    {
        return *ps1 < *ps2;
    }
};

typedef set<string*, StringPtrLess> StringPtrSet;
StringPtrSet ssp;
// 注意,传递给set的参数是一个对象,一个能在内部实例化建立函数的对象,而不是一个函数
```

















##### **第 21 条：总是让比较函数在等值情况下返回 false**



如果将 less定义为小于等于

则当判断10A和10B是否等价时,需要判断

`!(10A <= 10B) && !(10B <= 10A)`, `两边都为!(true)&&!(true)`,所以, 结果为false,即10A和10B不等价

于是set中能够insert两个10而不会去重复,为了提防这一点, 所有比较函数对于相同值应当返回false



那么对于multi_set&map这两种允许重复的容器而言呢?

也是不行的,因为equal_range所指向的是等价元素的范围,这两个在less中是不等价的

















##### **第 22 条：切勿直接修改 set 或 multiset 中的键**



因为原本容器中,元素的值是有序的,如果改变了其key值,会不在其应在的位置上,

对 `myset.begin()->first = 10`,对其直接赋值会产生编译错误

因为map的元素实际上是 pari<const K,V>













##### **第 23 条：考虑用有序vector替代关联容器**



关联容器的典型实现是平衡二叉查找树,其特点在于(查找,删除,插入)的混合操作

但如果是针对于(建立->查找->重建)这样的使用场景,即并不经常变动,在这种使用场景下,关联容器可能并不是最优的选择

但只有有序容器有这种性质,因为只有有序的vector才能使用查找算法



- 关联容器中,存储每个对象的同时,需要对其指针进行存储,以此带来的开销会导致同一个内存页中的对象数量减少,以此导致的缺页异常
- 但同时,有序vector的代价是其增删所带来的开销很大,因为需要维护有序



当用vector代替map时,vector中存储的是pair<K,V>,其中K不能像map中是const的,因为其元素的值会通过赋值移动?(没看懂什么意思)

同时,需要自己定义一个pair的比较函数用于vector的有序化,



















##### **第 24 条：当效率至关重要的时候，请在 map::operator[] 和 map::insert 之间作慎重选择**



map的operator[]函数是个奇怪的东西。它与vector、deque和string的operator[]函数无关，也和内建的数组 operator[]无关。相反，map::operator[]被设计为简化“添加或更新”功能



```cpp 
m[k] = v

// 如果m[v] 存在, 对其进行更新
// 如果m[v] 不存在, 对其进行添加
    
// operator[] 返回一个于k关联的值的引用
    // 如果没有m[v],则使用 默认构造函数建立一个新的,然后返回这个对象的引用
    
m.insert(IntWidgetMap::value_type(1, 1.50));
// 如果是采用insert的话, 采用的构造函数时有参的
	// 这样节省了三次系统调用: 1.默认构造临时对象 2.销毁临时对象 3.对V进行赋值

// 添加用insert, 更新用operator[]

// 当我们调用insert时,需要构造和析构一个pair对象,调用[]作为更新时,本来就有这么一个pair对象,所以不需要构造和析构

```















##### **第 25 条：熟悉非标准的散列容器**



C++11 中新增了四种关联容器，使用哈希函数组织的，即 unordered_map、unordered_multimap、unordered_set、unordered_multiset。

- set：集合。底层为红黑树，元素有序，不重复；multiset：底层为红黑树，元素有序，可重复
- map：底层为红黑树，键有序，不重复；multimap：底层为红黑树，键有序，可重复
- unordered_set：底层为哈希表，无序，不重复；unordered_multiset：底层为哈希表，无序，可重复
- unordered_map：底层为哈希表，无序，不重复；unordered_multiap：底层为哈希表，无序，可重复









SGI和Dinkumware的实现方法非常不同。SGI利用常用的一个元素的单链表的指针数组（桶）组成的开放散列法。

Dinkumware也利用了开放散列法，但是它的设计是基于一种新颖的数据结构——由迭代器（本质是桶）的数组组成的元素双向链表，迭代器的相邻对表示在每个桶里元素的范围  











##### **第 26 条：iterator 优先于 const_iterator、reverse_iterator 以及 const_reverse_iterator**



- const_iterator 相当于 const T *
- reverse_iterator与const_reverse_iterator同样相当于对应的T*和const T*，所不同的是，增加reverse_iterator或者const_reverse_iterator会在从尾到头的遍历中让你移动到容器的下一个元素。  



虽然有4中iterator,但是只有iterator比较特殊,拥有一些特权

insert和erase的一些版本要求iterator。如果你需要调用这些函数，你就必须产生iterator，而不能用const或reverse iterators。

● 不可能把const_iterator隐式转换成iterator，我们将会在条款27中讨论从一个const_iterator产生一个iterator的技术并不普遍适用，而且不保证高效。

● 从reverse_iterator转换而来的iterator在转换之后可能需要相应的调整，在条款28中我们会讨论何时需要调整以及调整的原因  





```cpp
Iter i;
ConstIter ci;
... // 同一个容器
if (i == ci) ... // 比较iterator和const_iterator
// iterator i 应该在比较之前转换为const_iterator
    
    // 可能编译出错的原因: const_iterator的operator==作为const_iterator的一个成员函数而不是非成员函数
    
 if (ci == i)... // 当上面比较无法通过编译时的解决方法
```



不管比较是否相等,在同一个表达式中比较iterator和const_iterator就会产生这种问题

解决方法是 `static_cast<ConstIter>(i)  `





##### **第 27 条： 使用 distance 和 advance 将容器的 const_iterator 转换成 iterator**



const_cast是不能够胜任的, vector和string之所以能够成功是因为他们大多会采用真实的指针作为容器的迭代器, 因为const_iterator与iterator之间的const_cast映射被最终解释成`const T*到T*`的映射  





```cpp
Iter i(d.begin()); // 初始化i为d.begin()
advance(i, distance(i, ci)); // 把i移到指向ci位置

// distance返回两个指向同一个容器的iterator之间的距离；
// advance则用于将一个iterator移动指定的距离。
// 如果i和ci指向同一个容器，那么表达式advance(i, distance(i, ci))会将i移动到与ci相同的位置上。

// distance的定义
template<typename InputIterator>
typename iterator_traits<InputIterator>::difference_type
distance(InputIterator first, InputIterator last);


advance(i, distance(i, ci));
有两个参数传递给distance，i和ci。
    i的类型是Iter，即deque<int>::iterator的typedef。对编译器来说，这表明调用distance的InputIterator是deque<int>::iterator。
	但ci是ConstIter，即deque<int>::const_iterator的typedef。这表明那个InputIterator是deque<int>::const_iterator。
InputIterator不可能同时有两种不同的类型，所以调用distance失败。一般会造成一些冗长的出错信息，可能会也可能不会说明是编译器无法得出InputIterator是什么类型。
        
// 所以需要自己排除歧义
advance(i, distance<ConstIter>(i, ci));
```





##### **第 28 条：正确理解由 reverse_iterator 的 base() 成员函数所产生的 iterator 的用法**



> 反向迭代器适配器（reverse_iterator），可简称为反向迭代器或逆向迭代器，常用来对容器进行反向遍历，即从容器中存储的最后一个元素开始，一直遍历到第一个元素。
>
> - 当反向迭代器执行 ++ 运算时，底层的基础迭代器实则在执行 -- 操作，意味着反向迭代器在反向遍历容器；
> - 当反向迭代器执行 -- 运算时，底层的基础迭代器实则在执行 ++ 操作，意味着反向迭代器在正向遍历容器。

[C++浅谈reverse_iterator的base()函数_c++ .base()_strivinging的博客-CSDN博客](https://blog.csdn.net/qq_22194315/article/details/57144854)

这篇博客里面的内容就是copy的书里面的





看这个图就能够明白大半了, ri.base() 指向的内容并不是 ri指向的内容, 而是具有1个offset的位置

<img src="C:/Users/84221/AppData/Roaming/Typora/typora-user-images/image-20230331231531736.png" alt="image-20230331231531736" style="zoom:67%;" />

这一点所带来的影响有:

1. insert(): 对ri进行insert和对i执行insert的结果是一样的, 原因是insert的逻辑是将参数插入到iterator指向的地方,然后原先该iterator所指的内容被挤到"下一个"位置
2. erase(): 如果要删除的话,自然这两个所指向不同位置的iterator删除的结果自然是不一样的
   1. 所以应当删除 ri.base()的前一个,才能使得结果一样
      1. 但同时需要注意的是,由于ri.base()返回的是一个指针,所以如果是 --ri.base() 会无法通过编译,因为C++规定了不能直接修改函数返回的指针.(目前在vs中执行能够通过编译)





##### **第 29 条：对于逐个字符的输入请考虑使用 istreambuf_iterator**



```cpp
ifstream inputFile("interestingData.txt");
string fileData((istream_iterator<char>(inputFile)), // 把inputFile读入
istream_iterator<char>()); // fileData；
```

在这种情况下,无法将文件中的空格拷贝到字符串中,那是因为istream_iterators使用operator>>函数来进行读取，而且operator>>函数在默认情况下忽略空格。  

假如你想保留空格，你要的做就是覆盖默认情况。只要清除输入流的skipws标志就行了 

```cpp
ifstream inputFile("interestingData.txt");
inputFile.unset(ios::skipws); // 关闭inputFile的忽略空格标志
string fileData((istream_iterator<char>(inputFile)), istream_iterator<char>());
```

istream_iterators所依靠的operator>>函数进行的是格式化输入，这意味着每次你调用的时候它们都必须做大量工作  

1. 它们必须建立和销毁岗哨（sentry）对象（为每个operator>>调用进行建立和清除活动的特殊的iostream对象）  
2. 它们必须检查可能影响它们行为的流标志（比如skipws）
3. 它们必须进行全面的读取错误检查，而且如果它们遇到问题，它们必须检查流的异常掩码来决定是否该抛出一个异常。



一个更有效的方法: istreambuf_iterators  

istream_iterator<char>对象使用operator>>来从输入流中读取单个字符。
istreambuf_iterator<char>对象进入流的缓冲区并直接读取下一个字符, istreambuf_iterator<char> 对象从一个istream s中读取会调用s.rdbuf()->sgetc()来读s的下一个字符  

```cpp
string fileData((istreambuf_iterator<char>(inputFile)), istreambuf_iterator<char>());
//注意这里不需要“unset”skipws标志，istreambuf_iterator不忽略任何字符。它们只抓取流缓冲区的下一个字符
```



















##### **第 30 条：确保目标区间足够大**,transform的使用



当我们通过transform函数, 将一个vector的范围内元素, 添加到另一个vector的end()时

由于在 end处没有对象,所以这样调用transform是错误的,给不存在的对象赋值

在这里我们不能使用.end()来指定插入位置,而应该调用back_inserter来实现尾部的插入.

back_inserter返回的迭代器会调用push_back，所以你可以在任何提供push_back的容器上使用 back_inserter（也就是任何标准序列容器：vector、string、deque和list）  

如果你想让一个算法在容器的前端插入东西，你可以使用front_inserter。在内部，front_inserter利用了push_front，所以front_insert 只和提供那个成员函数的容器配合（也就是deque和list,vector不提供push_front）

调用inserter可以在任意位置执行插入



transfrom函数虽然是对一个范围进行拼接插入,但是每次只会插入一个元素,由于每一次插入都会需要挪动后续的所有元素,所以这样造成的开销比较大

我们可以预先掉用reserve函数,至少省去重新分配内存的开销











##### **第 31 条：了解各种与排序有关的选择**



- partial_sort: 找出序列中最好的前20个,前20个是有序的, 其余元素无序
- nth_sort: 这次,前20个最好的,但是这20个里面也是无序的
- stable_sort: 稳定排序, 等价元素之间的顺序不会被改变
- partition: 它重排区间中的元素以使所有满足某个标准的元素都在区间的开头。  















#### 序列式容器



##### list

> 概念：list将数据进行链式存储, 即链表

[ C++ list容器详解_c++list容器详解_＆不逝的博客-CSDN博客](https://blog.csdn.net/qq_52324409/article/details/121046388)









