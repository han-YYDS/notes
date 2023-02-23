#!/bin/bash
# 上面中的 #! 是一种约定标记, 它可以告诉系统这个脚本需要什么样的解释器来执行;


time=$(date "+%Y-%m-%d %H:%M:%S")
git add .

read -t 30 -p "请输入提交注释(进入项目文件夹下进行提交):" msg

if  [ ! "$msg" ] ;then
    echo "[commit message] 默认提交, 提交人: han, 提交时间: ${time}"
	git commit -m "默认提交, 提交人: han, 提交时间: ${time}"
else
    echo "[commit message] $msg, 提交人: han, 提交时间: ${time}"
	git commit -m "$msg, 提交人: han, 提交时间: ${time}"
fi

	
git push origin main
read -p "press enter end to exit"

