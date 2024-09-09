[(107条消息) 跟我一起写 Makefile（一）_haoel的博客-CSDN博客_makefile](https://blog.csdn.net/haoel/article/details/2886)

[(109条消息) Makefile教程（绝对经典，所有问题看这一篇足够了）_GUYUEZHICHENG的博客-CSDN博客_makefile](https://blog.csdn.net/weixin_38391755/article/details/80380786?ops_request_misc=%7B%22request%5Fid%22%3A%22165905575416782350823422%22%2C%22scm%22%3A%2220140713.130102334..%22%7D&request_id=165905575416782350823422&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~top_positive~default-1-80380786-null-null.142^v35^control&utm_term=makefile&spm=1018.2226.3001.4187)





##### 基本规则

[Makefile](https://so.csdn.net/so/search?q=Makefile&spm=1001.2101.3001.7020)里主要包含了：显式规则、隐晦规则、变量定义、文件指示和注释。

> 1. 显式规则。显式规则说明了，如何生成一个或多的的目标文件。这是由Makefile的书写者明显指出，要生成的文件，文件的依赖文件，生成的命令。(基本的语法)
>
> 2. 隐晦规则。由于我们的make有**自动推导**的功能，所以隐晦的规则可以让我们比较粗糙地简略地书写Makefile，这是由make所支持的。
>
> 3. 变量的定义。在Makefile中我们要定义一系列的变量，变量一般都是字符串，这个有点你C语言中的宏，当Makefile被执行时，其中的变量都会被扩展到相应的引用位置上。(字符串的替换)
>
> 4. 文件指示。其包括了三个部分，
>
>    1. 一个是在一个Makefile中引用另一个Makefile，就像C语言中的include一样；(makefile的文件包含)
>    2. 另一个是指根据某些情况指定Makefile中的有效部分，就像C语言中的预编译#if一样；(条件make)
>    3. 还有就是定义一个多行的命令。有关这一部分的内容，我会在后续的部分中讲述。
>
> 5.  注释。Makefile中只有行注释，和UNIX的Shell脚本一样，其注释是用“#”字符，这个就像C/C++中的“//”一样。如果你要在你的Makefile中使用“#”字符，可以用反斜框进行转义，如：“\#”。
>
>    **最后，还值得一提的是，在Makefile中的命令command，必须要以[Tab]键开始。**



##### GNU的make工作时的执行步骤

\1.    读入所有的Makefile。

\2.    读入被include的其它Makefile。

\3.    初始化文件中的变量。

\4.    推导隐晦规则，并分析所有规则。

\5.    为所有的目标文件创建依赖关系链。

\6.    根据依赖关系，决定哪些目标要重新生成。

\7.    执行生成命令。

1-5步为第一个阶段，6-7为第二个阶段。

第一个阶段中，如果定义的变量被使用了，那么，make会把其展开在使用的位置。但make并不会完全马上展开，make使用的是拖延战术，如果变量出现在依赖关系的规则中，那么仅当这条依赖被决定要使用了，变量才会在其内部展开。



makefile书写规则



 规则包含两个部分，一个是***\*依赖关系\****，一个是***\*生成目标的方法\****。

***\*在Makefile中，规则的顺序是很重要的\****，因为，***\*Makefile中只应该有一个最终目标\****，其它的目标都是被这个目标所连带出来的，所以一定要让make知道你的最终目标是什么。一般来说，定义在Makefile中的目标可能会有很多**，但是第一条规则中的目标将被确立为最终的目标。**如果第一条规则中的目标有很多个，那么，第一个目标会成为最终的目标。make所完成的也就是这个目标。



###### 最基础的写法

```makefile
foo.o: foo.c defs.h       # foo模块
	cc -c -g foo.c
#foo.o是我们的目标，foo.c和defs.h是目标所依赖的源文件，而只有一个命令“cc -c -g foo.c”（以Tab键开头）。

targets : prerequisites ; command
	command
           
#targets是文件名，以空格分开，可以使用通配符。一般来说，我们的目标基本上是一个文件，但也有可能是多个文件。

#command是命令行，如果其不与“target:prerequisites”在一行，那么，必须以[Tab键]开头，如果和prerequisites在一行，那么可以用分号做为分隔。（见上）

#prerequisites也就是目标所依赖的文件（或依赖目标）。如果其中的某个文件要比目标文件要新，那么，目标就被认为是“过时的”，被认为是需要重生成的。这个在前面已经讲过了。
```





\1.    文件的依赖关系，foo.o依赖于foo.c和defs.h的文件，如果foo.c和defs.h的文件日期要比foo.o文件日期要新，或是foo.o不存在，那么依赖关系发生。

\2.    如果生成（或更新）foo.o文件。也就是那个cc命令，其说明了，如何生成foo.o这个文件。（当然foo.c文件include了defs.h文件(??? 为什么包含了.h文件?)）







##### 通配符

make支持三各通配符：“*”，“?”和“[...]”



###### ~

波浪号（“~ ”）字符在文件名中也有比较特殊的用途 - 用户目录。

如果是“~ /test”，这就表示**当前用户的$HOME目录下的test目录**。

而“~hchen/test”则表示用户hchen的宿主目录下的test目录。（这些都是Unix下的小知识了，make也支持）

而在Windows或是MS-DOS下，用户没有宿主目录，那么波浪号所指的目录则根据环境变量“HOME”而定。



###### *

通配符代替了你一系列的文件，如“*.c”表示所以后缀为c的文件。一个需要我们注意的是，如果我们的文件名中有通配符，如：“ * ”，那么可以用转义字符“\”，如“ \ * ”来表示真实的“*”字符，而不是任意长度的字符串。

好吧，还是先来看几个例子吧：

```makefile
clean:
	rm -f *.o

# 上面这个例子我不不多说了，这是操作系统Shell所支持的通配符。这是在命令中的通配符。


print: *.c
	lpr -p $?
	touch print

# 上面这个例子说明了通配符也可以在我们的规则中，
# 目标print依赖于所有的[.c]文件。其中的“$?”是一个自动化变量


objects = *.o

#上面这个例子，表示了，通符同样可以用在变量中。并不是说[*.o]会展开，不！objects的值就是“*.o”。Makefile中的变量其实就是C/C++中的宏。如果你要让通配符在变量中展开，也就是让objects的值是所有[.o]的文件名的集合，那么，你可以这样：

objects := $(wildcard *.o)
#这种用法由关键字“wildcard”指出，关于Makefile的关键字，我们将在后面讨论。

```



##### 文件搜寻: 

###### VPATH



```makefile
VPATH = src:../headers
# 上面的的定义指定两个目录，“src”和“../headers”，make会按照这个顺序进行搜索。
# 目录由“冒号”分隔。（当然，当前目录永远是最高优先搜索的地方）
```



###### vpath

另一个设置文件搜索路径的方法是使用make的“vpath”关键字（注意，它是全小写的）

这不是变量，这是一个make的关键字，这和上面提到的那个VPATH变量很类似，但是它更为灵活。

它可以指定不同的文件在不同的搜索目录中。这是一个很灵活的功能。它的使用方法有三种：

> \1.    vpath < pattern> < directories>   为符合模式< pattern>的文件指定搜索目录<directories>。
>
> \2.    vpath < pattern>                 清除符合模式< pattern>的文件的搜索目录。
>
> \3.    vpath                           清除所有已被设置好了的文件搜索目录。



vapth使用方法中的< pattern>需要包含“%”字符。

“%”的意思是匹配零或若干字符，例如，“%.h”表示所有以“.h”结尾的文件。

< pattern>指定了要搜索的文件集，而< directories>则指定了的文件集的搜索的目录。

例如：

>  vpath %.h ../headers
>
> 该语句表示，要求make在“../headers”目录下搜索所有以“.h”结尾的文件。



>   vpath %.c foo
>
>   vpath %  blish
>
>   vpath %.c bar
>
> 其表示“.c”结尾的文件，先在“foo”目录，然后是“blish”，最后是“bar”目录。



>  vpath %.c foo:bar
>
>  vpath %  blish
>
> 而上面的语句则表示“.c”结尾的文件，先在“foo”目录，然后是“bar”目录(目录由冒号分隔)，最后才是“blish”目录。



##### 伪目标



最早先的一个例子中，我们提到过一个“clean”的目标，这是一个“伪目标”，

  clean:

​      rm *.o temp

以“make clean”来使用该目标

因为，我们并不生成“clean”这个文件。

“伪目标”并不是一个文件，只是一个标签，由于“伪目标”不是文件，所以make无法生成它的依赖关系和决定它是否要执行。

我们只有通过显示地指明这个“目标”才能让其生效。

当然，“伪目标”的取名不能和文件名重名，不然其就失去了“伪目标”的意义了。

###### 最常用的伪目标:clean

> 当然，为了避免和文件重名的这种情况，我们可以使用一个特殊的标记“.PHONY”来显示地指明一个目标是“伪目标”，向make说明，不管是否有这个文件，这个目标就是“伪目标”。
>
>   .PHONY: clean
>
>   clean:
>
> ​      rm *.o temp



###### 伪目标指定所依赖的文件

> 伪目标一般没有依赖的文件。但是，我们也可以为伪目标指定所依赖的文件。
>
> 伪目标同样可以作为“默认目标”，只要将其放在第一个。
>
> 一个示例就是，如果你的Makefile需要一口气生成若干个可执行文件，但你只想简单地敲一个make完事，并且，所有的目标文件都写在一个Makefile中，那么你可以使用“伪目标”这个特性：
>
>   all : prog1 prog2 prog3
>
>   .PHONY : all
>
>  
>
>   prog1 : prog1.o utils.o
>
> ​      cc -o prog1 prog1.o utils.o
>
>  
>
>   prog2 : prog2.o
>
> ​      cc -o prog2 prog2.o
>
> 
>
>   prog3 : prog3.o sort.o utils.o
>
> ​      cc -o prog3 prog3.o sort.o utils.o
>
> 我们知道，Makefile中的第一个目标会被作为其默认目标。
>
> 我们声明了一个“all”的伪目标，其依赖于其它三个目标。
>
> 由于伪目标的特性是，总是被执行的，所以其依赖的那三个目标就总是不如“all”这个目标新。
>
> 所以，其它三个目标的规则总是会被决议。也就达到了我们一口气生成多个目标的目的。
>
> “.PHONY : all”声明了“all”这个目标为“伪目标”。



###### 伪目标同样也可成为依赖

> 随便提一句，从上面的例子我们可以看出，目标也可以成为依赖。所以，伪目标同样也可成为依赖。看下面的例子：
>
>   .PHONY: cleanall cleanobj cleandiff
>
>  
>
>   cleanall : cleanobj cleandiff
>
> ​      rm program
>
>  
>
>   cleanobj :
>
> ​      rm *.o
>
>  
>
>   cleandiff :
>
> ​      rm *.diff
>
> 
>
> “makeclean”将清除所有要被清除的文件。
>
> “cleanobj”和“cleandiff”这两个伪目标有点像“子程序”的意思。
>
> 我们可以输入“make cleanall”和“make cleanobj”和“makecleandiff”命令来达到清除不同种类文件的目的





##### 多目标



Makefile的规则中的目标可以不止一个，其支持多目标

有可能我们的多个目标同时依赖于一个文件，并且其生成的命令大体类似。于是我们就能把其合并起来。

当然，多个目标的生成规则的执行命令是同一个，这可能会可我们带来麻烦，不过好在我们的可以使用一个自动化变量“$@”（关于自动化变量，将在后面讲述），**`这个变量表示着目前规则中所有的目标的集合`**



```makefile
bigoutput littleoutput : text.g
	generate text.g -$(subst output,,$@) > $@

#上述规则等价于：
bigoutput : text.g
	generate text.g -big > bigoutput

littleoutput : text.g
	generate text.g -little > littleoutput
	
# 其中，-$(subst output,,$@)中的“$”表示执行subst函数，后面的为参数,是截取字符串的意思，
# “$@”表示目标的集合，就像一个数组，“$@”依次取出目标，并执于命令。
```



##### 静态模式 

静态模式可以更加容易地定义多目标的规则，可以让我们的规则变得更加的有弹性和灵活。

```makefile
<targets...>: <target-pattern>: <prereq-patterns ...>
	<commands>
# targets定义了一系列的目标文件，可以有通配符。是目标的一个集合。

# target-parrtern是指明了targets的模式，也就是的目标集模式。

# prereq-parrterns是目标的依赖模式，它对target-parrtern形成的模式再进行一次依赖目标的定义。

如果我们的<target-parrtern>定义成“%.o”，意思是我们的集合中都是以“.o”结尾的，
而如果我们的<prereq-parrterns>定义成“%.c”，意思是对<target-parrtern>所形成的目标集进行二次定义(???)，其计算方法是，取<target-parrtern>模式中的“%”（也就是去掉了[.o]这个结尾），并为其加上[.c]这个结尾，形成的新集合。
```



###### %< %@

```makefile
<targets...>: <target-pattern>: <prereq-patterns ...>
	<commands>

objects = foo.o bar.o
	all: $(objects)

如果只要一个 : 的话 那就是  目标:依赖

目标文件      :     目标集模式   :     依赖模式 
<targets...> : <target-pattern> : <prereq-patterns ...>
$(objects)   :       %.o        :      %.c
	$(CC) -c $(CFLAGS) $< -o $@
	
# 上面的例子中，指明了我们的目标从$object中获取，
# “%.o”表明要所有以“.o”结尾的目标，也就是“foo.o bar.o”，也就是变量$object集合的模式，

# 而依赖模式“%.c”则取模式“%.o”的“%”，也就是“foo bar”，并为其加下“.c”的后缀(从前到后有一个一一对应的映射关系)
# 于是，我们的依赖目标就是“foo.c bar.c”。

# 而命令中的“$<”和“$@”则是自动化变量 
	# “$<”表示所有的依赖目标集（也就是“foo.c bar.c”） - 所有的.c文件
	# “$@”表示目标集（也就是 foo.o bar.o”） - 所对应的同名.o文件
	

于是，上面的规则展开后等价于下面的规则：
	为所有的.c文件, 生成其对应的.o文件

foo.o : foo.c
	$(CC) -c $(CFLAGS) foo.c -o foo.o

bar.o : bar.c
	$(CC) -c $(CFLAGS) bar.c -o bar.o
```



###### filter

```makefile
files = foo.elc bar.o lose.o

$(filter %.o,$(files)): %.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@
	
$(filter %.elc,$(files)): %.elc: %.el
	emacs -f batch-byte-compile $<

# $(filter%.o,$(files))  	表示调用Makefile的filter函数，过滤“$filter”集，只要其中模式为“%.o”的内容。
	# 即只要求files中的.o文件
```



##### 自动生成依赖(没看明白这个.d文件有啥用)



在Makefile中，我们的依赖关系可能会需要包含一系列的头文件，比如，如果我们的main.c中有一句“#include "defs.h"”，那么我们的依赖关系应该是：

  main.o : main.c defs.h

但是，如果是一个比较大型的工程，你必需清楚哪些C文件包含了哪些头文件，并且，你在加入或删除头文件时，也需要小心地修改Makefile，这是一个很没有维护性的工作。

为了避免这种繁重而又容易出错的事情，我们可以使用C/C++编译的一个功能。大多数的C/C++编译器都支持一个“-M”的选项，即自动找寻源文件中包含的头文件，并生成一个依赖关系。

为什么我们自己编译个时候直接  g++ *.c就ok了?感觉平时没有用到.h文件



于是由编译器自动生成的依赖关系，这样一来，你就不必再手动书写若干文件的依赖关系，而由编译器自动生成了。需要提醒一句的是，如果你使用GNU的C/C++编译器，你得用“**`-MM`**”参数，



> GNU组织建议把编译器为每一个源文件的自动生成的依赖关系放到一个文件中，为每一个“name.c”的文件都生成一个“name.d”的Makefile文件，[.d]文件中就存放对应[.c]文件的依赖关系。

于是，我们可以写出[.c]文件和[.d]文件的依赖关系，并让make自动更新或自成[.d]文件，并把其包含在我们的主Makefile中，这样，我们就可以自动化地生成每个文件的依赖关系了。



```makefile
%.d: %.c
	@set -e; rm -f $@; \
	$(CC) -M $(CPPFLAGS) $< > $@.; \
	sed 's,\
	.o[ :]*,\1.o $@ : ,g' < $@.> $@; \
	rm -f $@.	
	
	这个规则的意思是，所有的[.d]文件依赖于[.c]文件
	“rm-f $@”的意思是删除所有的目标，也就是[.d]文件，
	第二行的意思是，为每个依赖文件“$<”，也就是[.c]文件生成依赖文件，“$@”表示模式“%.d”文件，如果有一个C文件是name.c，那么“%”就是“name”，“”意为一个随机编号(好像漏了)，第二行生成的文件有可能是“name.d.12345”，
	# @set什么意思?
	# -e啥意思?
	# -M 自动寻找 .h文件
	# > 是啥意思?	
	第三行使用sed命令做了一个替换，关于sed命令的用法请参看相关的使用文档。
	#sed 
	第四行就是删除临时文件。

	
#总而言之，这个模式要做的事就是在编译器生成的依赖关系中加入[.d]文件的依赖，即把依赖关系：

   main.o : main.c defs.h

转成：

   main.o main.d : main.c defs.h
   
   于是，我们的[.d]文件也会自动更新了，并会自动生成了
   当然，你还可以在这个[.d]文件中加入的不只是依赖关系，包括生成的命令也可一并加入，让每个[.d]文件都包含一个完赖的规则。
   一旦我们完成这个工作，接下来，我们就要把这些自动生成的规则放进我们的主Makefile中。我们可以使用Makefile的“include”命令，来引入别的Makefile文件（前面讲过），
   sources = foo.c bar.c
   include $(sources:.c=.d)

上述语句中的“$(sources:.c=.d)”中的“.c=.d”的意思是做一个替换，把变量$(sources)所有[.c]的字串都替换成[.d]，关于这个“替换”的内容，在后面我会有更为详细的讲述。
当然，你得注意次序，因为include是按次来载入文件，最先载入的[.d]文件中的目标会成为默认目标
```



#### 命令



##### 显示命令（linux命令）

当我们用“@”字符在命令行前，那么，这个命令将不被make显示出来

如果make执行时，带入make参数“**`-n`**”或“--just-print”，那么其只是显示命令，但不会执行命令，这个功能很有利于我们调试我们的Makefile，看看我们书写的命令是执行起来是什么样子的或是什么顺序的。

而make参数“**`-s`**”或“--slient”则是全面禁止命令的显示。



忽略命令的出错，我们可以在Makefile的命令行前加一个减号“-”（在Tab键之后），标记为不管命令出不出错都认为是成功的



##### 执行命令（顺序执行）



需要注意的是，如果你要让上一条命令的结果应用在下一条命令时，你应该使用分号分隔这两条命令。比如你的第一条命令是cd命令，你希望第二条命令得在cd之后的基础上运行，那么你就不能把这两条命令写在两行上，而应该把这两条命令写在一行上，用分号分隔。







命令出错



例如mkdir命令，我们一定需要建立一个目录，如果目录不存在，那么mkdir就成功执行，万事大吉，如果目录存在，那么就出错了。我们之所以使用mkdir的意思就是一定要有这样的一个目录，于是我们就不希望mkdir出错而终止规则的运行。



为了做到这一点，忽略命令的出错，我们可以在Makefile的命令行前加一个减号“-”（在Tab键之后），标记为不管命令出不出错都认为是成功的。

 clean:

​      -rm -f *.o



还有一个全局的办法是，给make加上“-i”或是“--ignore-errors”参数，那么，Makefile中所有命令都会忽略错误。而如果一个规则是以“.IGNORE”作为目标的，那么这个规则中的所有命令将会忽略错误。这些是不同级别的防止命令出错的方法



make的参数的是“-k”或是“--keep-going”，这个参数的意思是，如果某规则中的命令出错了，那么就终目该规则的执行，但继续执行其它规则。



##### 嵌套执行make



  例如，我们有一个子目录叫subdir，这个目录下有个Makefile文件，来指明了这个目录下文件的编译规则。那么我们总控的Makefile可以这样书写：

  subsystem:

​      cd subdir && $(MAKE)

其等价于：

   subsystem:

​      $(MAKE) -C subdir

定义$(MAKE)宏变量的意思是，也许我们的make需要一些参数，所以定义成一个变量比较利于维护。这两个例子的意思都是先进入“subdir”目录，然后执行make命令。











### cmake





CMake是一个用于管理跨平台项目构建的工具，它使用CMakeLists.txt文件来描述项目的配置和构建过程。以下是一个简单的CMakeLists.txt文件的示例，展示了如何构建一个项目：

```
cmakeCopy code# 指定最低的CMake版本
cmake_minimum_required(VERSION 3.10)

# 设置项目名称
project(MyProject)

# 添加可执行文件
add_executable(my_executable main.cpp)

# 添加库文件（如果有的话）
# add_library(my_library source1.cpp source2.cpp)

# 如果需要链接外部库，可以使用以下命令
# target_link_libraries(my_executable my_library)

# 如果有头文件，可以将头文件的路径包含在项目中
# target_include_directories(my_executable PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
```

上述示例中，`CMakeLists.txt`文件指定了项目的名称为"MyProject"，并创建了一个可执行文件`my_executable`，该可执行文件的源代码位于`main.cpp`中。如果项目包含库文件，可以使用`add_library`命令添加库文件，并使用`target_link_libraries`命令将库文件链接到可执行文件中。

在实际项目中，你需要根据项目的结构和依赖关系进行调整。你可能需要在`CMakeLists.txt`中包含更多的源文件、库文件，以及其他配置选项。你可以在CMake官方文档中找到更详细的信息：[CMake Documentation](https://cmake.org/documentation/)

要构建项目，可以按照以下步骤：

1. 在项目的根目录创建一个`CMakeLists.txt`文件。

2. 打开终端，导航到项目根目录。

3. 运行以下命令：

   ```
   bashCopy code
   cmake .
   ```

4. 运行生成的构建系统（如Makefile、Visual Studio项目等），具体命令取决于你的平台和配置。

5. 构建项目：

   ```
   bashCopy code
   make  # 对于Makefile
   ```

这些步骤将根据`CMakeLists.txt`文件中的配置信息生成构建系统，并使用该构建系统构建项目。

