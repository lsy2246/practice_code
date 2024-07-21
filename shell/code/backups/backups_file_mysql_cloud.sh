#!/bin/bash

web_path="/var/www" # 数据路径
web_arry=("alist" "bitwarden" "blog") # 网站根目录名称
mysql_arry=("blog") # 数据库名称
date_time=$(date +"%Y_%m_%d") # 日期格式
year=$(date +"%Y") #年份
user="root" # 数据库用户名
password="lsy22.com" # 数据库密码
original_dir=$(pwd) # 记录原始目录

# 激活百度网盘环境
source ~/myvenv/bin/activate

# 组合备份
for item in "${mysql_arry[@]}"; do
    # 创建SQL备份
    mysqldump -u $user -p$password ${item} > "${item}_${date_time}.sql"
    
    # 检查是否有同名的网站目录
    if [[ " ${web_arry[@]} " =~ " ${item} " ]]; then
        # 切换到网站目录进行压缩
        cd "${web_path}/${item}/" || exit
        zip -r "${item}_web_${date_time}.zip" .
        # 将数据库SQL文件和网站压缩包一起压缩
        zip "${item}_${date_time}.zip" "${item}_${date_time}.sql" "${item}_web_${date_time}.zip"
        # 删除临时的网站压缩包
        rm "${item}_web_${date_time}.zip"
        # 返回原始目录
        cd "$original_dir" || exit
    else
        # 否则，只压缩数据库
        zip "${item}_${date_time}.zip" "${item}_${date_time}.sql"
    fi
    rm "${item}_${date_time}.sql"
    # 上传到云存储
    bypy upload "${item}_${date_time}.zip" "/${item}/${year}/"
    # 上传到百度网盘存储
    bypy upload "${item}_${date_time}.zip" "/${item}/"
    # 上传到阿里云盘
    aliyunpan upload "${item}_${date_time}.zip" "/网站/${item}/${year}/"
    # 删除文件
    rm "${item}_${date_time}.zip"
done

# 单独备份那些没有同名数据库的网站目录
for item in "${web_arry[@]}"; do
    if [[ ! " ${mysql_arry[@]} " =~ " ${item} " ]]; then
        # 切换到网站目录进行压缩
        cd "${web_path}/${item}/" || exit
        zip -r "${item}_${date_time}_data.zip" .
        # 上传到百度网盘存储
        bypy upload "${item}_${date_time}.zip" "/${item}/"
        # 上传到阿里云盘
        aliyunpan upload "${item}_${date_time}.zip" "/网站/${item}/${year}/"
        # 删除文件
        rm "${item}_${date_time}_data.zip"
        # 返回原始目录
        cd "$original_dir" || exit
    fi
done