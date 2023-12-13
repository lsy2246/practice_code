#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int contact_digit=0;//存入了多少位置

struct Contact
{
	char name[50];//名字
	char sex[20];//性别
	char email[20];//电子邮箱
	char number[11];//电话号码
	struct Contact *next;//下一个联系人	   	
};
struct Contact *con[99];//声明结构体

void view_contact(void)//查看联系人
{
	int contact_number;//第几个联系人
	struct Contact *tmp_con=con[1];//声明结构体
	for(contact_number=1;contact_number<contact_digit;contact_number++)//查找非空联系人
	{
		tmp_con=con[contact_number];//复制结构体指针
		if(tmp_con!=NULL)
		{
			break;
		}
	}
	if(contact_digit==0 ||(contact_digit==contact_number && tmp_con==NULL))
	{
		printf("通讯录没有联系人\n");
		while(getchar()!='\n');//删除缓存
		return;
	}
	while(1)
	{
		printf("\n姓名:%s  ",tmp_con->name);
		printf("性别:%s  ",tmp_con->sex);
		printf("电子号码:%s  ",tmp_con->number);
		printf("电子邮箱:%s",tmp_con->email);
		if(tmp_con->next==NULL)
		{
			break;
		}
		else
		{
			tmp_con=tmp_con->next;//指向下一个联系人
		}
	}
	printf("\n");
	while(getchar()!='\n');//清除缓存
}

int find_numbering(const char name[])//查找编号
{
	int contact_number=1;//第几个联系人
	struct Contact *tmp_con=con[1];//声明临时结构体
        if(contact_digit==0)//如果查找到最后一个都没有
        {
                while(getchar()!='\n');//删除缓存
                return 100;
        }
	while(1)
	{	
		if(strcmp(tmp_con->name,name)==0)
		{
			return contact_number;
		}
		if(tmp_con->next==NULL)//如果下一个为NULL就退出
                {
                        return 100;
                }
                else
                {
			contact_number++;//增加联系人名次
                        tmp_con=tmp_con->next;//指向下一个联系人
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
	struct Contact *temp=con[contact_number];//声明临时储储存需要删除联系人的物理地址
	for(int i=contact_number;i<contact_digit;i++)//将所有联系人向前移一位
	{
		con[i]=con[i+1];
		con[i-1]->next=con[i];
	}
	printf("删除的联系人姓名是：%s\n", temp->name);
	free(temp);//释放这个联系人内容
	contact_digit--;//总数减一
	if(contact_digit==contact_number)//如果是最后一位
	{
		con[contact_number]->next=NULL;
	}
	printf("删除成功\n");
}

void revise_contact(const int contact_number)//修改信息
{	
	if(contact_number==100)
        {
                printf("\n查无此人\n");
                return;
        }
	int pick=0;
	start:
	printf("\n1.修改名字\n");
	printf("2.修改性别\n");
	printf("3.修改电话号码\n");
	printf("4.修改电子邮箱\n");
	printf("5.返回主页\n");
	printf("请输入:");
	while((scanf("%d",&pick))!=1)
	{
		while(getchar()!='\n');//清除缓存
		printf("请输入合法的数字:");
		scanf("%d",&pick);
	}
	switch(pick)
	{
		case 1:
			{
				printf("请输入姓名:");
				scanf("%50s",con[contact_number]->name);
				printf("修改成功!\n当前姓名为:%s",con[contact_number]->name);
				while(getchar()!='\n');//清除缓存
				goto start;//回到主菜单
				break;
			}
		case 2:
			{
				printf("请输入性别:");
				scanf("%20s",con[contact_number]->sex);
				printf("修改成功!\n当前性别为:%s",con[contact_number]->sex);
				while(getchar()!='\n');//清除缓存
				goto start;//回到主菜单
				break;
			}
		case 3:
			{
				printf("请输入电话号码:");
				number_tab:
        			scanf("%11s",con[contact_number]->number);
				for(int i=0;i<11;i++)
				{
					if(strlen(con[contact_number]->number)!=11||con[contact_number]->number[i]<'0'||con[contact_number]->number[i]>'9')
					{
						printf("请输入11位数字:");
						while(getchar()!='\n');//清除缓存
						goto number_tab;
					}
				}
				printf("修改成功!\n当前电话号码为:%s",con[contact_number]->number);
				while(getchar()!='\n');//清除缓存
				goto start;//回到主菜单
				break;
			}
		case 4:
			{
				printf("请输入电子邮箱:");
				email_tab:
				scanf("%20s",con[contact_number]->email);
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
				printf("修改成功!\n当前电子邮箱为:%s",con[contact_number]->email);
				while(getchar()!='\n');//清除缓存
				goto start;//回到主菜单
				break;
			}
		case 5: 
			{
				while(getchar()!='\n');//清除缓存
				return;//结束程序
			}
		default :
			{
				while(getchar()!='\n');//清除缓存
				printf("请输入对应的模式\n");
				goto start;//回到主菜单
			}
	}
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
	contact_digit++;
	//分配内存
	con[contact_digit]=(struct Contact *)malloc(sizeof(struct Contact));//给新联系人分配内存
	//姓名
	printf("请输入姓名:");
	scanf("%50s",con[contact_digit]->name);
	//性别
	printf("请输入性别:");
	scanf("%20s",con[contact_digit]->sex);
	//电话号码
	printf("请输入电话号码:");
	number_tab:
        scanf("%11s",con[contact_digit]->number);
	for(int i=0;i<11;i++)
	{
		if(strlen(con[contact_digit]->number)!=11||con[contact_digit]->number[i]<'0'||con[contact_digit]->number[i]>'9')
		{
			printf("请输入11位数字:");
			while(getchar()!='\n');//清除缓存
			goto number_tab;
		}
	}
	//电子邮箱
	printf("请输入电子邮箱:");
	email_tab:	
	scanf("%20s",con[contact_digit]->email);
	for(int i=0;i<=strlen(con[contact_digit]->email);i++)
	{
		if(con[contact_digit]->email[i]=='@')
		{
			break;
		}
		else if(i==strlen(con[contact_digit]->email))
		{
			while(getchar()!='\n');
			printf("请输入正确格式的邮箱:");
			goto email_tab;
		}	
	}
	//下一个地址
	if(contact_digit>1)
	{
		con[contact_digit-1]->next=con[contact_digit];//与上一个连接
	}
	con[contact_digit]->next=NULL;//将下一个设置为空
	while(getchar()!='\n');//清除缓存
	printf("\n新建成功");
	see_contact(contact_digit);//输出单个信息
}

int homepage(void)//主页
{
	printf("————通讯录————\n");
	printf("1.查看联系人\n");
	printf("2.查找联系人\n");
	printf("3.修改联系人\n");
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
			case 3:
				{
					printf("\n请输入需要修改联系人的姓名:");
                                        scanf("%s",name);
                                        contact_number= find_numbering(name);//查找名字所在的结构体
                                        revise_contact(contact_number);//修改联系人
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
