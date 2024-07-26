#!/bin/bash

web_path="/var/www" # 数据路径
date_time=$(date +"%Y_%m_%d") # 日期格式
year=$(date +"%Y") #年份
aliyunpan="/var/script/aliyunpan/aliyunpan" #阿里云盘可执行文件路径

# 激活百度网盘环境
source "/var/script/venv/bin/activate"

for item in "$web_path"/*; do
    item_name=$(basename "$item")
    # 切换到网站目录进行压缩
    cd "$item" || exit
    tar -czf "${item_name}_${date_time}.tar.gz" .
    # 上传到百度网盘存储
    bypy upload "${item_name}_${date_time}.tar.gz" "/${item_name}/"
    # 上传到阿里云盘
    $aliyunpan upload "${item_name}_${date_time}.tar.gz" "/网站/${item_name}/${year}/"
    # 删除文件
    rm "${item_name}_${date_time}.tar.gz"
done