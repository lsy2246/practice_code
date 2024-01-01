#ifndef FUNCTION_STATEMENT_EFFECT_H //检查函数有没有被声明
#define FUNCTION_STATEMENT_EFFECT_H //定义宏

#include "effect_keystroke.h"//包含按键头文件
#include "Global_variables.h"//包含全局变量头文件

void HideCursor ();//隐藏光标

void CursorJump ( int y , int x );//光标跳转

void color ( int c );//颜色设置

#endif //FUNCTION_STATEMENT_EFFECT_H