#include <windows.h>

void HideCursor ( void )//隐藏光标
{
    CONSOLE_CURSOR_INFO curInfo; //定义光标信息的结构体变量
    curInfo . dwSize = 1; //如果没赋值的话，光标隐藏无效
    curInfo . bVisible = FALSE; //将光标设置为不可见
    HANDLE handle = GetStdHandle ( STD_OUTPUT_HANDLE ); //获取控制台句柄
    SetConsoleCursorInfo ( handle , & curInfo ); //设置光标信息
}

void CursorJump ( int y , int x )//光标跳转
{
    COORD pos; //定义光标位置的结构体变量
    pos . X = x; //横坐标
    pos . Y = y; //纵坐标
    HANDLE handle = GetStdHandle ( STD_OUTPUT_HANDLE ); //获取控制台句柄
    SetConsoleCursorPosition ( handle , pos ); //设置光标位置
}

void color ( int c )//颜色设置
{
    SetConsoleTextAttribute ( GetStdHandle ( STD_OUTPUT_HANDLE ) , c ); //颜色设置
    //注：SetConsoleTextAttribute是一个API（应用程序编程接口）
}
