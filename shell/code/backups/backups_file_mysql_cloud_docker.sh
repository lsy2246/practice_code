#!/bin/bash

web_path="/var/www" # 数据路径
date_time=$(date +"%Y_%m_%d") # 日期格式
year=$(date +"%Y") #年份
original_dir=$(pwd) # 记录原始目录

# 激活百度网盘环境
source ~/myvenv/bin/activate

for item in "$web_path"/*; do
    item_name=$(basename "$item")
    # 切换到网站目录进行压缩
    cd "$item" || exit
    zip -r "${item_name}_${date_time}.zip" .
    # 移动压缩文件回原始目录
    mv "${item_name}_${date_time}.zip" "$original_dir"
    # 返回原始目录
    cd "$original_dir" || exit
    # 上传到百度网盘存储
    bypy upload "${item_name}_${date_time}.zip" "/${item_name}/"
    # 上传到阿里云盘
    aliyunpan upload "${item_name}_${date_time}.zip" "/网站/${item_name}/${year}/"
    # 删除文件
    rm "${item_name}_${date_time}.zip"
done