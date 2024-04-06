#!/bin/bash

web_path="/var/www"
web_arry=("alist" "bitwarden" "blog")
mysql_arry=("blog" "study")
date_time=$(date +"%Y_%m_%d")
year=$(date +"%Y") 
user=""
password=""

for item in ${mysql_arry[@]};do
	mkdir -p "$item/$year"	
	mysqldump -u $user -p$password ${item} > "${item}_${date_time}.sql"
	zip "./$item/$year/${item}_${date_time}.zip"  "./${item}_${date_time}.sql"
done

for item in ${web_arry[@]};do
	mkdir -p "./$item/$year"
	zip -r "./${item}_${date_time}_data.zip" "/${item}"
	if [ -f "./$item/$year/${item}_${date_time}.zip" ];then
		zip -u "./${item}_${date_time}.zip" "./${item}_${date_time}_data.zip"
	else
		 zip "./$item/$year/${item}_${date_time}.zip" "./${item}_${date_time}_data.zip"
	fi
done
