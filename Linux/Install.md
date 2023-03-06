> 此文用于linux下对于第三方库的安装



#### 安装方法

在Linux下安装软件通常有几种方法，具体取决于软件的类型和来源。以下是一些常见的方法：

1. 使用包管理器：大多数Linux发行版都有自己的包管理器，可以用来安装、升级、删除软件。常见的包管理器有：APT（Debian、Ubuntu）、yum（RedHat、CentOS）、pacman（Arch Linux）。可以通过命令行输入相应的命令来使用包管理器，例如：

- APT：sudo apt-get install [软件名]
- yum：sudo yum install [软件名]
- pacman：sudo pacman -S [软件名]

1. 从源代码编译安装：有些软件可能没有被打包成Linux发行版的包，可以从源代码编译安装。这需要先下载软件的源代码，然后使用编译器编译，生成可执行文件。具体步骤可以参考软件的官方文档。
2. 使用软件中心：一些Linux发行版也提供了图形化的软件中心，用户可以通过搜索、浏览等方式找到需要的软件，并直接安装。常见的软件中心有：Ubuntu软件中心、GNOME软件、Discover（KDE软件中心）等。

















##### 生成makefile之前的文件依赖

[Configure，Makefile.am, Makefile.in, Makefile文... (360doc.com)](http://www.360doc.com/content/12/0314/19/7982302_194349182.shtml)





![image-20230306110504396](https://test4projectwf.oss-cn-hangzhou.aliyuncs.com/image/202303061105499.png)















> ##### 源代码编译安装
>
> 一般的编译安装过程如下：
>
> 1. 下载源代码包：用户需要先从软件官网或其他可信来源下载源代码包。下载完成后，将源代码包解压到某个目录。
> 2. 安装编译工具：Linux系统自带了一些基本的编译工具，如GCC编译器、make命令等，但是有些软件需要使用特定版本的编译工具。用户可以通过包管理器安装相应的编译工具，例如gcc、g++、make、autoconf、automake等。
> 3. 配置：进入源代码目录，运行`./configure命令`进行配置。这个命令将检查系统环境和依赖项，并生成Makefile文件。如果有缺少的依赖项，需要先安装它们。(==安装依赖项见上面,即在生成makefile之前所需要的操作==)
> 4. 编译：运行`make`命令开始编译源代码。这个过程可能需要一些时间，取决于源代码包的大小和复杂性。如果出现编译错误，需要根据错误信息调整配置或代码。
> 5. 安装：编译完成后，运行 `sudo make install`命令将软件安装到系统中。需要注意的是，使用make install会将软件安装到系统的标准路径中，可能会与包管理器中的软件包冲突。因此，建议将编译后的软件安装到非标准路径中，例如/opt目录。
> 6. 修改配置文件: `sudo ldconfig`
> 7. 清理：如果不再需要编译的源代码，可以使用make clean命令清理编译生成的文件。
>





编译过程中显示语法错误,或者是在linux环境下出现x86,x64等信息时,可能是由于设置为在windows环境下进行编译

```
make -f Makefile.unx
sudo make install -f Makefile.unx

```



##### 名词解释

- configure
- SDK









##### 下载

[(117条消息) yum和apt-get的区别_非著名JAVA程序员的博客-CSDN博客_apt-get yum](https://blog.csdn.net/qq_39132177/article/details/108447229)

[(117条消息) yum到底是干什么的？_做1个快乐的程序员的博客-CSDN博客_yum是什么](https://blog.csdn.net/weixin_43202123/article/details/119948927)





#### 正常的编译安装/卸载：

源码的安装一般由3个步骤组成：

- 配置(configure)
- 编译(make)
- 安装(make install)。

 

##### configure配置

configure文件是一个可执行的脚本文件

它有很多选项，在待安装的源码目录下使用命令./configure –help可以输出详细的选项列表。

 

其中--prefix选项是配置安装目录

- 如果不配置该选项，
  - 安装后可执行文件默认放在/usr/local/bin
  - 库文件默认放在/usr/local/lib
  - 配置文件默认放在/usr/local/etc
  - 其它的资源文件放在/usr/local/share，比较凌乱。

- 如果配置了--prefix，如： $ ./configure --prefix=/usr/local/test
  
  - 安装后的所有资源文件都会被放在/usr/local/test目录中，不会分散到其他目录。
  
    

./autogen.sh

autoconf命令的主要作用是创建`configure`。它基于`configure.ac`文件生成`configure`文件。



##### 安装

安装 C++ OSS sdk

- [(117条消息) 什么是SDK? SDK是什么意思？_FaithMai的博客-CSDN博客_sdk](https://blog.csdn.net/FaithMai/article/details/61202534)
- SDK 就是 Software Development Kit 的缩写，中文意思就是“软件开发工具包”。这是一个覆盖面相当广泛的名词





###### 安装动态库(shared library)

1. 下载源代码

2. 生成makefile

   1. mkdir build
   2. cd build
   3. cmake ..

   > cmake .. 用于生成makefile文件
   >
   > cmake用于描述**`跨平台`**下的编译过程
   >
   > [(117条消息) CMake是什么？有什么用？_AndrewZhou924的博客-CSDN博客_cmake是干什么的](https://blog.csdn.net/Torres_10/article/details/80371425)

3. make

4. sudo make install

   > 用于将make编译生成的二进制文件,移动到操作系统中合适的路径中去
   >
   > 将 .so文件, .a文件移动到 /usr/local/lib 目录下
   >
   > - so文件 - 动态链接库 [(117条消息) 什么是.so文件_dahaibeibe的博客-CSDN博客_.so是什么文件](https://blog.csdn.net/dahaibeibe/article/details/8095035)
   >
   > - .a文件 - 静态库  静态库是一些目标文件(后缀名为.o)的集合体
   >
   >   [(117条消息) Linux环境下静态库的生成和使用 (.a文件)_cloud-2014的博客-CSDN博客](https://blog.csdn.net/u012592062/article/details/51942026)

5. sudo ldconfig

   仅仅是将文件移动过去,是找不到的,还需要修改config文件

   > 1. 在默认搜寻目录 **`/lib`** 和 **`/usr/lib`** 以及 动态库配置文件**`/etc/ld.so.conf`**内所列的目录下(/usr/local/lib就在该文件中)，搜索出可共享的动态链接库（格式如lib*.so*）
   >
   > 2. 进而创建出动态装入程序(ld.so)所需的连接和缓存文件，缓存文件默认为/etc/ld.so.cache
   >
   > ​	此文件保存已排好序的动态链接库名字列表。
   >
   > 3. linux下的共享库机制采用了类似高速缓存机制，将库信息保存在/etc/ld.so.cache，程序连接的时候首先从这个文件里查找，然后再到ld.so.conf的路径中查找。为了让动态链接库为系统所共享，需运行动态链接库的管理命令ldconfig，此执行程序存放在/sbin目录下。
   >
   > ```
   > 如果没有这一步的话,会有如下报错
   > error while loading shared libraries: libgf_complete.so.1: cannot open shared object file: No such file or directory
   > 但你在 /usr/local/lib中是能够找到该.so文件的
   > ```
   >
   > 





- .git文件要用 git clone下载而不是 wget



















Linux软件安装方式：

[Linux下安装软件的3种方式 - 简书 (jianshu.com)](https://www.jianshu.com/p/0490e5208442)

1. apt，rpm，yum；
   1. 当你在执行安装操作时，首先apt-get 工具会在本地的一个数据库中搜索关于 w3m 软件的相关信息，并根据这些信息在相关的服务器上下载软件安装
      1. 本地数据库是什么?

2. 源代码安装；

3. 二进制安装。





















