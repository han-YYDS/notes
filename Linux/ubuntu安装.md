



###### root

[(144条消息) Ubuntu18.04设置root密码（初始密码）_跳舞的皮埃尔的博客-CSDN博客_root的初始密码](https://blog.csdn.net/a6661314/article/details/124391440)



###### tools

如果 tools 是灰色不能安装,需要重新安装 iso镜像

[(144条消息) VMware Tools安装教程_东路的尽头的博客-CSDN博客_安装vmwaretools](https://blog.csdn.net/qq_41892825/article/details/122464113)



###### 网络设置

```
sudo apt install net-tools
```



- 桥接网络
  - 采用桥接网络要用手机热点而不能直接连接校园网
  - [记录\]Ubuntu18.04使用桥接模式实现上网_.ByeBye的博客-CSDN博客](https://blog.csdn.net/weixin_43843847/article/details/90938308)
  -  









###### root用户设置

[(144条消息) Ubuntu18.04设置root密码（初始密码）_跳舞的皮埃尔的博客-CSDN博客_root的初始密码](https://blog.csdn.net/a6661314/article/details/124391440)

sudo passwd root

###### 换源

[(145条消息) Ubuntu18.04切换阿里源_初来乍到程序dot的博客-CSDN博客](https://blog.csdn.net/BruceFei1/article/details/110312722)



###### 配置SSH

```shell
sudo apt-get install openssh-server

#E: Could not get lock /var/lib/dpkg/lock - open (11: Resource temporarily unavailable)
#E: Unable to lock the administration directory (/var/lib/dpkg/), is another process using it?

解决error - 删除lock文件
sudo rm /var/lib/dpkg/lock
```









###### vim插件

[技术|如何安装 Vim 插件 (linux.cn)](https://linux.cn/article-11923-1.html)

[Vim配置及说明——IDE编程环境 - zhongcq - 博客园 (cnblogs.com)](https://www.cnblogs.com/zhongcq/p/3642794.html)





```
mkdir -p ~/.vim/pack/vendor/start

  git clone --depth 1 \
  https://github.com/preservim/nerdtree.git \
  ~/.vim/pack/vendor/start/nerdtree
  
  
mkdir -p ~/.vim/pack/NERDTree/start/

git clone --depth 1 \
  https://github.com/preservim/nerdtree.git \
  ~/.vim/pack/NERDTree/start/NERDTree
  
  
curl -sL install-node.now.sh/lts | bash
```





























#### shell



###### vscode 连接 虚拟机

[(178条消息) VsCode配置ssh免密远程登录_vscode ssh 免密_czy1219的博客-CSDN博客](https://blog.csdn.net/qq_44571245/article/details/123031276)

