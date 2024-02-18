#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include<string.h>

struct Contact//每个联系人的结构体
{
	char name[20];//名字
	char sex[10];//性别
	char email[30];//email
};

enum Operate//选择的枚举函数
{
	view=1,find,add,delete,quit//查看,查看个人,新增,删除,退出
};

void view_mode(void)//查看所有联系人函数
{
	FILE *file=fopen("contact.txt","a+b");//打开文件
	struct Contact contact;//声明一块结构体临时储存读取到的通讯录
	while(fread (&contact , sizeof(struct Contact) , 1 , file) == 1)
	{
		printf("姓名:%s",contact.name);
		printf(" 性别:%s",contact.sex);
		printf(" 电子邮箱:%s\n",contact.email);
	}
	fclose(file);//关闭文件
}

void find_mode(void)//查找联系人函数
{
	FILE *file=fopen("contact.txt","a+b");//打开文件
	char tmp_name[20]="a";//申请接受用户的名字
	struct Contact contact;//临时接受的结构体
	printf("请输入需要查找的联系人:");
	scanf("%20s",tmp_name);//接受用户需要查找的姓名
	while(fread(&contact,sizeof(struct Contact),1,file) == 1)
	{
		if(strcmp(contact.name,tmp_name) == 0)
		{
			printf("姓名:%s",contact.name);
			printf(" 性别:%s",contact.sex);
			printf(" 电子邮箱:%s",contact.email);
			fclose(file);//关闭文件
			return;//结束函数
		}
	}

	printf("查无此人\n");
}

void add_mode(void)//新增联系人函数
{
	FILE *file=fopen("contact.txt","a+b");//以读的方式打开文件
	struct Contact contact;//声明一个临时结构体来接收用户
	struct Contact tmp_contact;//声明一个结构体来检查有无重复
	printf("请输入姓名:");
	scanf("%20s",contact.name);
	fseek(file, 0, SEEK_SET);//将文件指针移动到开头，并清除之前读取的内容
	//查找是否已经存入
	while(fread(&tmp_contact,sizeof(struct Contact),1,file) == 1)
	{
		if(strcmp(tmp_contact.name,contact.name) == 0)
		{
			printf("联系人已经存在\n");
			printf("姓名:%s",tmp_contact.name);
			printf(" 性别:%s",tmp_contact.sex);
			printf(" 电子邮箱:%s",tmp_contact.email);
			fclose(file);//关闭文件
			return;//结束函数
		}
	}
	printf("请输入性别:");
	scanf("%10s",contact.sex);
	printf("请输入电子邮箱:");
	scanf("%30s",contact.email);
	while (strcmp(contact.email,"@") != 0)
	{
		while(getchar()!='\n');//清除缓存
		printf("请输入正确格式的电子邮箱:");
		scanf("%30s",contact.email);//重新接收	
	}
	fwrite(&contact,sizeof(struct Contact),1,file);//写入文件
	fclose(file);//关闭文件
	printf("新建成功\n");
	printf("姓名:%s",contact.name);
	printf(" 性别:%s",contact.sex);
	printf(" 电子邮箱:%s",contact.email);
}

void delete_mode(void)//删除联系人函数
{
	FILE *file=fopen("contact.txt","rb");//通讯录文件
    FILE *tmp_file=fopen("tmp_contact.txt","wb");//零时通讯录文件
	char tmp_name[20]="a";//临时接收用户需要删除的姓名
	struct Contact contact;//声明结构体找到需要删除的位置
	printf("请输入需要删除的联系人的姓名:");
	scanf("%s",tmp_name);//接收需要删除的联系人的姓名
	while(fread( &contact , sizeof(struct Contact) , 1 ,file ) == 1)
	{
		if( strcmp(contact.name,tmp_name) != 0)
		{
            fwrite(&contact,sizeof(struct Contact) , 1 ,tmp_file);//如果不是需要删除的名字写入临时文件
		}
	}
	fclose(file);//关闭文件
    fclose(tmp_file);//关闭零时文件
    remove("contact.txt");//将原有通讯录删除
    rename("tmp_contact.txt", "contact.txt");//将临时通讯录更名
    printf("删除成功\n");
}


int main(void)
{
	int oprate=0;//创建选择
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
				delete_mode();//进入删除函数
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
