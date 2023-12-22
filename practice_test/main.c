#include<stdio.h>
#include<stdlib.h>
#include<errno.h>

struct Contact//每个联系人的结构体
{
	char sex[10];//性别
	char name[15];//名字
	char email[30];//email
};

enum Operate//选择的枚举函数
{
	view=1,find,add,delete,quit//查看,查看个人,新增,删除,退出
}oprate;

void view_mode(void)//查看所有联系人函数
{
	FILE *file=fopen("contact.txt","rb");//打开文件
	int  test_file=fgetc(file);//测试是否为空
	if(test_file == EOF)
	{
		printf("通讯录不存在联系人\n");
		fclose(file);//关闭文件
		return;//结束程序
	}
	struct Contact contact;//声明一块结构体临时储存读取到的通讯录
	while(fread (&contact , sizeof(struct Contact) , 1 , file) == 1)
	{
		printf("姓名:%s",contact.name);
		printf(" 性别:%s",contact.sex);
		printf(" email:%s\n",contact.email);
	}
	fclose(file);//关闭文件
}

void find_mode(void)//查找联系人函数
{
	printf("find\n");
}

void add_mode(void)//新增联系人函数
{
	printf("add\n");
}

void delete_mode(void)//删除联系人函数
{
	printf("delete\n");
}

int main(void)
{	
	start://主页面标签
	printf("\n———————通讯录——————\n");
	printf("%d.查看全部联系人\n",view);
	printf("%d.查找联系人\n",find);
	printf("%d.新增联系人\n",add);
	printf("%d.删除联系人\n",delete);
	printf("%d.退出程序\n",quit);
	printf("请输入需要进入的模式:");
	while( (scanf("%d",&oprate)) != 1 || oprate < 1|| oprate > 5)
	{
		while(getchar()!='\n');//清除缓存
		printf("请输入正确的数字:");
		scanf("%d",&oprate);//重新获取数字
	}
	switch(oprate)
	{
		case view:
			{
				while(getchar()!='\n');//清除缓存
				view_mode();//进入查看函数
				goto start;//回到主页
				break;//防止进入下一个
			}
		case find:
			{
				while(getchar()!='\n');//清除缓存
				find_mode();//进看个人函数
				goto start;//回到主页
				break;//防止进入下一个
			}	
		case add:
			{
				while(getchar()!='\n');//清除缓存
				add_mode();//进入新增函数
				goto start;//回到主页
				break;//防止进入下一个
			}
		case delete:
			{
				while(getchar()!='\n');//清除缓存
				delete_mode;//进入删除函数
				goto start;//回到主页
				break;//防止进入下一个
			}
		case quit:
			{
				printf("欢迎下次使用\n");
				break;
			}
	}	
	return 0;
}
