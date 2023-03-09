



###### 安装

```shell
sudo apt-get install mysql-server-5.7
```





###### 首次登陆



首次登陆时，

```shell
# 采用UNIX的用户认证方式进行登陆
sudo mysql -u root
```

如果想要使用用户密码登陆，首次登陆可能会遇到 Access denied for user 的错误信息

[ERROR 1698 (28000): Access denied for user 'root'@'localhost' (gxlsystem.com)](https://www.gxlsystem.com/mysql-124208.html#:~:text=%24 mysql -u root ERROR 1698 (28000)%3A Access,root 用户使用了 UNIX 的用户认证方式。 下面使用 sudo 权限登录 mysql，验证这一点：)







###### 设置密码

MySQL会有自己的插件，需要对密码强度进行修改，否则密码可能无法通过

[修改mysql用户密码强度等级策略 - 园来是伱 - 博客园 (cnblogs.com)](https://www.cnblogs.com/YuanLei888/p/13719662.html)



```mysql
#使mysql数据库
use mysql; 

#查看对应的user到host的信息
select host,user from user;

# 修改host,使得外部用户可以访问root
update user set host='%' where user='root';

# 开放root用户权限
grant all privileges on *.* to 'root'@'%' identified by '123456';

# 显示mysql中的密码等级
SHOW VARIABLES LIKE 'validate_password%'

# 修改密码要求
set global validate_password_policy=LOW;
set global validate_password_length=6; 

# 使得权限设置生效
flush privileges;
```







###### navicat

[Navicat Premium 15 永久破解激活工具及安装教程(亲测可用) - MarchXD - 博客园 (cnblogs.com)](https://www.cnblogs.com/marchxd/p/15580739.html)