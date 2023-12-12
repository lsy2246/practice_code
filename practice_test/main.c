#include <stdio.h>
#include <stdlib.h>

int contact_digit=0;//存入了多少号码

struct Contact
{
	int sex;//性别
	char name[10];//名字
	char email[20];//电子邮箱
	char number[11];//电话号码
	struct Contact *next;//下一个联系人	   	
};
struct Contact *con[99];//声明结构体

void add_contact(int contact_number)//新增联系人
{	
	//初始化
	con[contact_number]=(struct Contact *)malloc(sizeof(struct Contact));//给新联系人分配内存
	//姓名
	printf("请输入姓名:");
	scanf("%s",con[contact_number]->name);
	//性别
	printf("请选择性别\n");
	printf("1.男性\n");
	printf("2.女性\n");
	printf("3.未知\n");
	printf("请输入:");
sex_tab:
	while ( scanf("%d",&con[contact_number]->sex )!=1 )
			{
				while(getchar()!='\n');//清楚缓存
				printf("请输入合法的数字:");
				scanf("%d",&con[contact_number]->sex );
			}
	if(con[contact_number]->sex<1||con[contact_number]->sex>3)
	{
		while(getchar()!='\n');//清楚缓存
		printf("请输入正确的模式");
		goto  sex_tab;
	}

	//电子邮箱
	printf("请输入电子邮箱:");                         
	scanf("%s",con[contact_number]->email);
	//下一个地址
	if(contact_number==contact_digit)
	{
		con[contact_number]->next=NULL;
	}
	else
	{
		con[contact_number-1]->next=con[contact_number];
		con[contact_number]->next=con[contact_number+1];
	}
}
int homepage(void)//主页
{
	printf("————通讯录————\n");
	printf("1.查看联系人\n");
	printf("2.查找联系人\n");
	printf("3.删除联系人\n");
	printf("4.新建联系人\n");
	printf("5.退出通讯录\n");
	int accept = 0;//接受用户输入的模式
	printf("请输入:");
accept_tab://接受输入标签
	while(  (  scanf("%d",&accept) ) != 1)
	{
		while(getchar() != '\n');//清楚缓存
		printf("请输入合法数字:");
		scanf("%d",&accept);
	}
	if(accept>0&&accept<5)
	{
		return accept;
	}
	else if(accept==5)
	{
		printf("欢迎下次使用");
		exit(0);
	}
	else
	{
		while(getchar() != '\n');//清楚缓存
		printf("请输入正确的模式:");
		goto accept_tab;
	}
}
int main(void)
{
	homepage();
	return 0;
}
