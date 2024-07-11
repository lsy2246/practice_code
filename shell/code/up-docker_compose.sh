#!/bin/bash  
 
# 包含docker-compose.yml文件的目录的父目录  
docker_path="/var/www"
  
for dir in "$docker_path"/*/; do
	cd "$dir" || exit  
   	pwd
	sudo docker compose pull  
        sudo docker compose up -d  
done
