#!/bin/bash

# 定义主域名及其附属域名列表
declare -A DOMAIN_CERTS=(
    ["blog"]="lsy22.com www.lsy22.com"
    ["siyun"]="s.lsy22.com"
    ["alist"]="o.lsy22.com"
    ["gitea"]="g.lsy22.com"
    ["bitwarden"]="b.lsy22.com"
)

# 定义要映射的 IP 地址
MAPPED_IP="121.4.180.183"
# 邮箱地址（用于 Let's Encrypt 通知）
EMAIL="lsy22@vip.qq.com"
# ACME.sh 脚本的路径
ACME_SH_PATH="/root/.acme.sh/acme.sh"
# hosts 文件路径
HOSTS_FILE="/etc/hosts"

# 更新 hosts 文件
for GROUP in "${!DOMAIN_CERTS[@]}"; do
    for DOMAIN in ${DOMAIN_CERTS[$GROUP]}; do
        if ! grep -q "$DOMAIN" "$HOSTS_FILE"; then
            echo "$MAPPED_IP $DOMAIN" >> $HOSTS_FILE
        fi
    done
done

# 更新证书
ANY_SUCCESS=false
for GROUP in "${!DOMAIN_CERTS[@]}"; do
    ADDITIONAL_DOMAINS=""
    
    for DOMAIN in ${DOMAIN_CERTS[$GROUP]}; do
        ADDITIONAL_DOMAINS="$ADDITIONAL_DOMAINS -d $DOMAIN"
    done

    # 更新证书
    $ACME_SH_PATH --issue $ADDITIONAL_DOMAINS --webroot /var/www/html --email $EMAIL --renew-hook "systemctl reload nginx"

    # 检查证书更新结果
    if [ $? -eq 0 ]; then
        ANY_SUCCESS=true
    fi
done

# 如果至少有一个证书更新成功，则重启 Web 服务器（例如 Nginx）
if [ "$ANY_SUCCESS" = true ]; then
    systemctl reload nginx
fi

exit 0