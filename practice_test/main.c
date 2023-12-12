#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int contact_digit=0;//存入了多少位置

struct Contact
{
	char name[20];//名字
	char sex[20];//性别
	char email[20];//电子邮箱
	char number[11];//电话号码
	struct Contact *next;//下一个联系人	   	
};
struct Contact *con[99];//声明结构体

void view_contact(void)//查看联系人
{
	int contact_number;//第几个联系人
	for(contact_number=1;contact_number<contact_digit;contact_number++)//查找非空联系人
	{
		if(con[contact_number]!=NULL)
		{
			break;
		}
	}
	if(contact_digit==0 ||(contact_digit==contact_number && con[contact_number]==NULL))
	{
		printf("通讯录没有联系人\n");
		while(getchar()!='\n');//删除缓存
		return;
	}
	while(1)
	{
		printf("\n姓名:%s  ",con[contact_number]->name);
		printf("性别:%s  ",con[contact_number]->sex);
		printf("电子号码:%s  ",con[contact_number]->number);
		printf("电子邮箱:%s\n",con[contact_number]->email);
		if(con[contact_number]->next==NULL)
		{
			break;
		}
		else
		{
			con[contact_number]=con[contact_number]->next;//指向下一个联系人
		}
	}
	while(getchar()!='\n');//清除缓存
}

int find_numbering(const char name[])//查找编号
{
	int i=0;//查看的次数
	int contact_number;//第几个联系人
	const int length=strlen(name);//需要查找的名字长度
        for(contact_number=1;contact_number<contact_digit;contact_number++)//查找非空联系人
        {
                if(con[contact_number]!=NULL)
                {
                        break;
                }
        }
        if(contact_digit==0 ||(contact_digit==contact_number && con[contact_number]==NULL))
        {
                while(getchar()!='\n');//删除缓存
                return 100;
        }
	while(1)
	{	
		for(i=0;i<length;i++)
		{
			if(name[i]!=con[contact_number]->name[i])
			{
				break;
			}		
		}
		if(length==i)
		{
			return contact_number;	
		}
		else if(con[contact_number]->next==NULL)
                {
                        return 100;
                }
                else
                {
                        con[contact_number]=con[contact_number]->next;//指向下一个联系人
                }
	}	
}

void remove_contact(int contact_number)//删除联系人
{
	if(contact_number==100)
	{
		printf("\n查无此人\n");
		return;
	}
	free(con[contact_number]);//释放这个联系人内容
	con[contact_number]=NULL;//将它指向空
	for(contact_number--;contact_number>0;contact_number--)//查找前一个有效地址
	{
		if(con[contact_number]!=NULL)
		{	
			int i=0;//后面一位的有效值
			if(i==contact_digit&&con[i]==NULL)//如果没有找到后一个就标记空
			{	
				con[contact_number]->next=NULL;
				break;
			}
			for(i=contact_number+1;i<=contact_digit;i++)//查找后一位有效值
			{
				if(con[i]!=NULL)//如果查找到后一位就将前一位链接到最后一位
				{
					con[contact_number]->next=con[i];
					break;
				}
			}
			break;
                }
	}
	printf("删除成功\n");
}

void see_contact(const int contact_number)//查看单个联系人
{
	if(contact_number==100)
	{
		printf("\n查无此人\n");
		return;
	}
	printf("\n姓名:%s  ",con[contact_number]->name);
	printf("性别:%s  ",con[contact_number]->sex);
	printf("电子号码:%s  ",con[contact_number]->number);
	printf("电子邮箱:%s\n",con[contact_number]->email);
}

void add_contact(void)//新增联系人
{	
	int contact_number=0;//增加位置变量
	//判断增加的位置
	for(contact_number=0;contact_number<=contact_digit;contact_number++)
	{
		if(con[contact_number]==NULL)//查找有无空位
		{
			break;
		}
		else if(contact_number==contact_digit)//需要新增的话
		{
			contact_number++;//设置本次的位置
			contact_digit++;//增加总数量
			break;
		}

	}
	//分配内存
	con[contact_number]=(struct Contact *)malloc(sizeof(struct Contact));//给新联系人分配内存
	//姓名
	printf("请输入姓名:");
	scanf("%s",con[contact_number]->name);
	//性别
	printf("请输入性别:");
	scanf("%s",con[contact_number]->sex);
	//电话号码
	printf("请输入电话号码:");
	number_tab:
        scanf("%s",con[contact_number]->number);
	for(int i=0;i<11;i++)
	{
		if(strlen(con[contact_number]->number)!=11||con[contact_number]->number[i]<'0'||con[contact_number]->number[i]>'9')
		{
			printf("请输入11位数字:");
			while(getchar()!='\n');//清除缓存
			goto number_tab;
		}
	}
	//电子邮箱
	printf("请输入电子邮箱:");
	email_tab:	
	scanf("%s",con[contact_number]->email);
	for(int i=0;i<=strlen(con[contact_number]->email);i++)
	{
		if(con[contact_number]->email[i]=='@')
		{
			break;
		}
		else if(i==strlen(con[contact_number]->email))
		{
			while(getchar()!='\n');
			printf("请输入正确格式的邮箱:");
			goto email_tab;
		}	
	}
	//下一个地址
	if(contact_number==contact_digit)//最后一个
	{
		for(int i=contact_number-1;i>0;i--)//查找前一个有效地址
                {
                        if(con[i]!=NULL)
                        {

                                con[i]->next=con[contact_number];
                                break;
                        }
                }
		con[contact_number]->next=NULL;
	}
	else//从中间新增
	{
		for(int i=contact_number-1;i>0;i--)//查找前一个有效地址
		{
			if(con[i]!=NULL)
			{

				con[i]->next=con[contact_number];
				break;
			}
		}
		for(int i=contact_number+1;i<=contact_digit;i++)//查找后一位有效值
		{
			if(con[i]!=NULL)
                        {
                                con[contact_number]->next=con[i];
                                break;
                        }
		}
	}
	printf("\n新建成功");
	see_contact(contact_number);//输出单个信息
}

int homepage(void)//主页
{
	printf("————通讯录————\n");
	printf("1.查看联系人\n");
	printf("2.查找联系人\n");
	printf("4.删除联系人\n");
	printf("5.新建联系人\n");
	printf("6.退出通讯录\n");
	int accept = 0;//接受用户输入的模式
	printf("请输入:");
	accept_tab://接受输入标签
	while(  (  scanf("%d",&accept) ) != 1)
	{
		while(getchar() != '\n');//清楚缓存
		printf("请输入合法数字:");
		scanf("%d",&accept);
	}
	if(accept>0&&accept<6)
	{
		return accept;
	}
	else if(accept==6)
	{
		printf("欢迎下次使用\n");
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
	char name[10];//要接受用户输入的名字
	int contact_number;//查找名字所在的结构体返回值
	int homepage_pick=0;//主页选择变量
	while(1)
	{
		homepage_pick=homepage();//接收主页选择
		switch(homepage_pick)
		{
			case 1:
				{
					view_contact();//输出所有联系人
					break;
				}
			case 2:
				{	
					printf("\n请输入需要查找联系人的姓名:");
					scanf("%s",name);
					contact_number= find_numbering(name);//查找名字所在的结构体
					see_contact(contact_number);//输出单个信息
					break;
				}
			case 4:
				{
					printf("\n请输入需要删除联系人的姓名:");
                                        scanf("%s",name);
                                        contact_number= find_numbering(name);//查找名字所在的结构体
					remove_contact(contact_number);//删除联系人
					break;
				}
			case 5:
				{
					add_contact();//进行增加
					break;
				}
		}
	}
	return 0;
}
