#!/bin/bash

round=0 #记录算了多少次

while [ "$symbol" != '=' ] #用于持续接收用户输入的数字
do
	read -p "请输入数字:" number #用于接收用户数字
	#计算乘除取余
	if [ "$symbol" == "/" ];
	then
		number=$[ ${numberarr[$round]} / number ]
	elif [ "$symbol" == "*" ];
	then
		number=$[ ${numberarr[$round]} * number ]
	elif [ "$symbol" == "%" ];
	then
		number=$[ ${numberarr[$round]} % number ]
	fi
	#如果计算了就覆盖刚刚的结果
	if [[ "$symbol" == "*" || "$symbol" == "/" || "$symbol" == "%" ]];
	then
		round=$[$round-1]
	fi

	read -p "请输入符号:" symbol #接收符号

	#判断符号有没有出错
	while [[ "$symbol" != "+" && "$symbol" != "-" && "$symbol" != "/" && "$symbol" != "*" && "$symbol" != "%" && "$symbol" != "=" ]];
	do
		read -p "请重新输入符号( + - * / % = )" symbol
	done
	#储存刚刚接收的数据
	symbolarr[$[round]]=$symbol
	numberarr[$[round]]=$number
	round=$[$round+1]
done
 
round=0 #重置次数

sum=${numberarr[$round]} #获取第一位数

#进行最后的计算
while [ "${symbolarr[$round]}" != "=" ]
do
	if [ "${symbolarr[$round]}" == "+" ];
	then
		sum=$[ "$sum" + "${numberarr[$[$round+1]]}" ]
	else
		sum=$[ "$sum" - "${numberarr[$[$round+1]]}" ]
	fi
	round=$[$round+1] #进行次数增加
done

echo "计算结果为$sum"
