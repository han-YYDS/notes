[(171条消息) Git教程 Git Bash详细教程_LolitaAnn的博客-CSDN博客_git-bash](https://blog.csdn.net/qq_36667170/article/details/79085301)





[(171条消息) 删除本地文件后 Git pull从远程仓库重新获取不到解决办法_我若安好那还得了的博客-CSDN博客_git 删除本地文件再pull没有](https://blog.csdn.net/wzs1160250712/article/details/109233241)



[✨✨✨git教程](https://github.com/geeeeeeeeek/git-recipes/wiki)

#### 基本操作



##### 根据已有代码创建仓库

1. git init 创建本地仓库
2. git add . 将当前目录的文件加入到git中
3. git commit -m ""
4. git remote add origin <git url>
5. git push origin master
   1. 输入username和token




##### 上传代码

1. git add .
2. git commit -m "备注"
3. git push 

上传到仓库之前需要pull





##### 删除

[(180条消息) Git删除本地文件后，如何同步到远程(代码文件名包含中文)_诸葛飞飞的博客-CSDN博客](https://blog.csdn.net/L_Y_Fei/article/details/107433089)





##### 登录 access key



[(180条消息) github开发人员在七夕搞事情：remote: Support for password authentication was removed on August 13, 2021._点亮～黑夜的博客-CSDN博客](https://shliang.blog.csdn.net/article/details/119698015?spm=1001.2101.3001.6650.2&utm_medium=distribute.pc_relevant.none-task-blog-2~default~CTRLIST~Rate-2-119698015-blog-119744116.pc_relevant_3mothn_strategy_and_data_recovery&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2~default~CTRLIST~Rate-2-119698015-blog-119744116.pc_relevant_3mothn_strategy_and_data_recovery&utm_relevant_index=5)

[(205条消息) github的token使用方法_github token_chengwenyang的博客-CSDN博客](https://blog.csdn.net/chengwenyang/article/details/120060010)



在现版本的github中,登录需要的是 token而不是password,

所以当执行push命令时,需要输入username和password,这里的password就是token



##### merge

[(180条消息) 详解Git合并冲突——原因及解决 “Automatic merge failed； fix conflicts and then commit the result.“_JiangHao Lan的博客-CSDN博客](https://blog.csdn.net/u010393510/article/details/127121169)

当在两个客户端同时进行操作同一份文件时,一端修改完push之后另一端再pull然后再修改



1. git pull, 拉取代码,并automerge
2. 文件产生冲突,在文件中解决冲突.
3. git add .
4. git commit 
