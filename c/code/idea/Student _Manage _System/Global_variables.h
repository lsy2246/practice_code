#ifndef GLOBAL_VARIABLES_H //检查函数有没有被声明
#define GLOBAL_VARIABLES_H //定义宏

struct Personal_Information//定义个人信息结构体变量
{
    unsigned int id;//编号
    char name[20];//姓名
    bool sex;//性别
    unsigned int student_id;//学号
    unsigned int class;//班级
    unsigned int year;//入学年份
    char phone[11];//手机号
    unsigned int course_number[20];//课程编号
};

struct Course//课程结构体
{
    unsigned int id;
    char name[20];
};


extern struct Course that_course;//当前课程
extern struct Personal_Information that_person;//当前的联系人
extern bool pick_revision;//判断文件有没有修改完成
extern bool pick_view_mode;//判断查看视图的模式
extern unsigned Total;//学生总数

#endif //GLOBAL_VARIABLES_H