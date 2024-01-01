//头文件
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

//自定义头文件
#include "founction_statement_page.h"//界面
#include "function_statement_effect.h"//功能

struct Personal_Information that_person={1,"梁师谊",true,2023150,1,2020,"18888888888",{1,2,3}};//当前的联系人

void print_view_mode1(void)//打印视图模式
{
    //将原来的清空
    for ( int i = 3 ; i < 28 ; ++ i )
    {
        for ( int j = 0 ; j < 100 ; ++ j )
        {
            CursorJump ( i , j );//位置跳转
            printf (" ");
        }
    }
    //打印
    CursorJump ( 3 , 0 );//位置跳转
    color(7);
    printf ("编号  ");
    printf ("姓名\t");
    printf ("性别  ");
    printf ("学号\t");
    printf ("班级\t");
    printf ("入学年份  ");
    printf ("手机号码\t");
    printf ("选课编号");
    for ( int i = 5 ; i < 27 ;  i+=2 )
    {
        //编号
        CursorJump ( i , 0 );//位置跳转
        color (10);
        printf ("%d  ",that_person.id);
        //姓名
        CursorJump ( i , 6 );//位置跳转
        color (13);
        printf ("%s",that_person.name);
        //性别
        CursorJump ( i , 16 );//位置跳转
        if(that_person.sex)
        {
            color (11);
            printf ("男");
        }
        else
        {
            color (12);
            printf ("女");
        }
        //学号
        CursorJump ( i , 22 );//位置跳转
        color (9);
        printf ("%d",that_person.student_id);
        //班级
        CursorJump ( i , 32 );//位置跳转
        color (14);
        printf ("%d班",that_person.class);
        //入学年份
        CursorJump ( i , 40 );//位置跳转
        color (9);
        printf ("%d年",that_person.year);
        //电话号码
        CursorJump ( i , 50 );//位置跳转
        color (15);
        printf ("%s",that_person.phone);
        CursorJump ( i , 64 );//位置跳转
        for ( int j = 0 ; that_person.course_number[j] != '\0'  ; ++ j )
        {
            if(j>0)
            {
                color (12);
                printf (",");
            }
            color (11);
            printf ("%d",that_person.course_number[j]);
        }
    }
}

void print_view_mode2(void)//打印列表模式
{
    //将原来的清空
    for ( int i = 3 ; i < 28 ; ++ i )
    {
        for ( int j = 0 ; j < 100 ; ++ j )
        {
            CursorJump ( i , j );//位置跳转
            printf (" ");
        }
    }
    for ( int i = 4 ; i < 28 ;  i+=2 )
    {
        for ( int j = 6 ; j < 92 ; j+=10 )
        {
            CursorJump ( i , j );//位置跳转
            color (11);
            printf ("%s",that_person.name);
        }
    }
}