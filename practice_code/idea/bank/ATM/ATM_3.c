#include<stdio.h>
#include <stdlib.h>
#include <string.h>

//初始化 账号密码
char account_number[999];//账号
char account_number_test[999];//校验账号
char account_password[999]; //密码
char account_password_test[999]; //校验密码
char account_password_1[999]; //取款密码
char account_password_1_test[999]; //校验取款密码
int account_password_1_test_1; //校验取款密码输入了几位
char administrators_password[999] = "lsy22.com"; //管理员密码
char administrators_password_test[999]; //校验管理员密码

//初始化 金额
double balance = 0; //余额
double interest_rate = 0.0175; //利率
double interest_rate_test = 0.0175; // 利率校验
double year = 0;//年份
double interest = 0; //利息
double prediction = 0; //预测余额
double save = 0; //存钱
double withdraw = 0; //取钱
double running_bill[999];//金额流水
char running_bill_symbol[999];//金额流水符号
double running_bill_balance[999];//金额流水余额
int running_bill_tab = 0; //金额流水次数

//函数声明

//银行主页
void bank_home_program ();

//账户注册页面
void account_sigin_program ();

//账户登录页面
void account_login_program ();

//账户主页
void account_home_program ();

//模式一 个人信息
void account_mode1_program ();

//模式一 个人信息 查看流水金额
void account_mode1_part1_program ();

//模式一 个人信息 修改账号
void account_mode1_part2_program ();

//模式一 个人信息 修改密码
void account_mode1_part3_program ();

//模式一 个人信息 修改取款密码
void account_mode1_part4_program ();

//模式二 存款
void account_mode2_program ();

//模式三 取款
void account_mode3_program ();

//模式四 预测余额
void account_mode4_program ();

//管理员登录页面
void administrastion_login_program ();

//管理员主页面
void administrastion_home_program ();

//管理员 查看流水金额
void administrastion_mode1_program ();

//管理员 修改用户账号
void administrastion_mode2_program ();

//管理员 修改用户密码
void administrastion_mode3_program ();

//管理员 修改用户取款密码
void administrastion_mode4_program ();

// 管理员修改年利率
void administrastion_mode5_program ();

//银行主页
void bank_home_program ()
{
    int bank_pick;//银行主页选择
    printf ( "----银行主页1-----\n" );
    printf ( "0.退出程序 \n" );
    printf ( "1.登录账户 \n" );
    printf ( "请输入:" );
    scanf ( "%d" , & bank_pick );
    switch ( bank_pick )
    {
        case 0:
        {
            exit ( 0 );
        }
        case 1:
        {
            if ( account_number[ 0 ] == '\0' )  //第一次进入注册
            {
                int account_sigin_pick; //选择是否进行注册
                printf ( "---尚未注册账户---\n" );
                printf ( "1.注册账户\n" );
                printf ( "输入其他返回银行主页\n" );
                printf ( "请输入:" );
                scanf ( "%d" , & account_sigin_pick );
                if ( account_sigin_pick == 1 )
                {
                    account_sigin_program ( );
                } else
                {
                    bank_home_program ( );
                }
            } else  //往后进入登录
            {
                account_login_program ( );
            }
            break;
        }
        case 22:
        {
            administrastion_login_program ( );
            break;
        }
        default:
        {
            printf ( "没有找到对应的模式请重新输入:\n" );
            while ( getchar ( ) != '\n' ); //清楚缓存
            bank_home_program ( );
            break;
        }
    }
}

//账户注册页面
void account_sigin_program ()
{
    int account_sigin_pick; //没有注册账号是否需要注册
    account_sigin_number_tab:  //注册账号标签
    {
        printf ( "-----注册账号----\n" );
        printf ( "请输入账号:" );
        scanf ( "%s" , account_number );
        printf ( "请确认账号:" );
        scanf ( "%s" , account_number_test );
        if ( strcmp ( account_number , account_number_test ) != 0 )
        {
            while ( getchar ( ) != '\n' );//清除缓存
            printf ( "两次输入不相同,请重新输入 \n" );
            goto account_sigin_number_tab;
        }
    }

    account_sigin_password_tab:  //注册密码标签
    {
        printf ( "-----注册密码----\n" );
        printf ( "请输入密码:" );
        scanf ( "%s" , account_password );
        printf ( "请确认密码:" );
        scanf ( "%s" , account_password_test );
        if ( strcmp ( account_password , account_password_test ) != 0 )
        {
            while ( getchar ( ) != '\n' );//清除缓存
            printf ( "两次输入不相同,请重新输入 \n" );
            goto account_sigin_password_tab;
        }
    }

    account_sigin_password_1_tab:  //注册取款密码标签
    {
        printf ( "-----注册取款密码(只能输入6位)----\n" );
        printf ( "请输入取款密码:" );
        scanf ( "%s" , account_password_1 );
        //校验是不是6位
        account_password_1_test_1 = strlen ( account_password_1 );
        if ( account_password_1_test_1 != 6 )
        {
            while ( getchar ( ) != '\n' );//清除缓存
            printf ( "当前输入了%d位,请重新输入 \n" , account_password_1_test_1 );
            goto account_sigin_password_1_tab;
        }

        printf ( "请确认取款密码:" );
        scanf ( "%s" , account_password_1_test );
        if ( strcmp ( account_password_1 , account_password_1_test ) != 0 )
        {
            while ( getchar ( ) != '\n' );//清除缓存
            printf ( "两次输入不相同,请重新输入 \n" );
            goto account_sigin_password_1_tab;
        }
    }

    printf ( "注册成功\n" );
    printf ( "账号:%s\n" , account_number );
    printf ( "密码:%s\n" , account_password );
    printf ( "取款密码:%s\n" , account_password_1 );
    printf ( "请妥善保存好密码\n" );

    account_sigin_exit_tab: //选择退出标签
    {
        printf ( "1.返回银行主页\n" );
        printf ( "2.进行登录账户\n" );
        printf ( "请输入:" );
        scanf ( "%d" , & account_sigin_pick );
        switch ( account_sigin_pick )
        {
            case 1:
            {
                while ( getchar ( ) != '\n' ); //清除缓存
                bank_home_program ( );
            }
            case 2:
            {
                while ( getchar ( ) != '\n' ); //清除缓存
                account_login_program ( );
            }
            default:
            {
                while ( getchar ( ) != '\n' );  //清除缓存
                printf ( "输入错误,请重新输入 \n" );
                goto account_sigin_exit_tab;

            }
        }
    }
}

//账户登录页面
void account_login_program ()
{
    account_login_tab: //登录账号标签
    {
        printf ( "请输入账号:" );
        scanf ( "%s" ,account_number_test );
        if ( strcmp ( account_number_test , account_number ) != 0 )
        {
            printf ( "账号不正确请重新输入 \n" );
            while ( getchar ( ) != '\n' ); //清除缓存
            goto account_login_tab;
        }
    }

    password_login_tab: //登录密码标签
    {
        printf ( "请输入密码:" );
        scanf ( "%s" , account_password_test );
        if ( strcmp ( account_password_test , account_password ) != 0 )
        {
            printf ( "密码不正确请重新输入 \n" );
            while ( getchar ( ) != '\n' ); //清除缓存
            goto password_login_tab;
        }
    }

    printf ( "登录成功\n" );
    while ( getchar ( ) != '\n' );  //清除缓存
    account_home_program ( );
}

//账户主页
void account_home_program ()
{
    int account_home_pick;
    printf ( "----账户主页---- \n" );
    printf ( "0.退出程序 \n" );
    printf ( "1.个人信息 \n" );
    printf ( "2.存款 \n" );
    printf ( "3.取钱 \n" );
    printf ( "4.预测余额(当前利率为%.3lf%%) \n" , interest_rate * 100 );
    printf ( "5.退出账号 \n" );
    printf ( "请输入需要进入的模式:" );
    scanf ( "%d" , & account_home_pick );
    switch ( account_home_pick )
    {
        case 0:
        {
            exit ( 0 );
        }
        case 1:
        {
            while ( getchar ( ) != '\n' );  //清除缓存
            account_mode1_program ( );
            break;
        }
        case 2:
        {
            while ( getchar ( ) != '\n' );  //清除缓存
            account_mode2_program ( );
            break;
        }
        case 3:
        {
            while ( getchar ( ) != '\n' );  //清除缓存
            account_mode3_program ( );
            break;
        }
        case 4:
        {
            while ( getchar ( ) != '\n' );  //清除缓存
            account_mode4_program ( );
            break;
        }
        case 22:
        {
            while ( getchar ( ) != '\n' );  //清除缓存
            administrastion_login_program ( );
            break;
        }
        case 5:
        {
            while ( getchar ( ) != '\n' );  //清除缓存
            printf ( "退出成功 \n" );
            bank_home_program ( );
            break;
        }
        default:
        {
            while ( getchar ( ) != '\n' );  //清除缓存
            printf ( "没有找到对应的模式请重新输入 \n" );
            account_home_program ( );
        }
    }
}

//模式一 个人信息
void account_mode1_program ()
{
    int account_mode1_pick;
    printf ( "---个人信息--- \n" );
    printf ( "1.查看余额 \n" );
    printf ( "2.查看金额流水 \n" );
    printf ( "3.修改账号 \n" );
    printf ( "4.修改密码 \n" );
    printf ( "5.修改取款密码 \n" );
    printf ( "6.返回到账户主页 \n" );
    printf ( "请输入需要进入的模式:" );
    scanf ( "%d" , & account_mode1_pick );
    switch ( account_mode1_pick )
    {
        case 1:
        {
            while ( getchar ( ) != '\n' );  //清除缓存
            printf ( "当前余额为%.3lf\n" , balance );
            account_mode1_program ( );
            break;
        }
        case 2:
        {
            while ( getchar ( ) != '\n' );  //清除缓存
            account_mode1_part1_program ( );
            break;
        }
        case 3:
        {
            while ( getchar ( ) != '\n' );  //清除缓存
            account_mode1_part2_program ( );
            break;
        }
        case 4:
        {
            while ( getchar ( ) != '\n' );  //清除缓存
            account_mode1_part3_program ( );
            break;
        }
        case 5:
        {
            while ( getchar ( ) != '\n' );  //清除缓存
            account_mode1_part4_program ( );
            break;
        }
        case 6:
        {
            while ( getchar ( ) != '\n' );  //清除缓存
            account_home_program ( );
            break;
        }
        case 22:
        {
            while ( getchar ( ) != '\n' );  //清除缓存
            administrastion_login_program ( );
            break;
        }
        default :
        {
            printf ( "输入错误请重新输入\n" );
            while ( getchar ( ) != '\n' );  //清除缓存
            account_mode1_program ( );
            break;
        }

    }

}

//模式一 个人信息 查看流水金额
void account_mode1_part1_program ()
{
    printf ( "---金额流水开始--- \n" );
    for ( int running_bill_tab_test = 0 ; running_bill_tab_test < running_bill_tab ; running_bill_tab_test ++ )
    {
        if ( running_bill_symbol[ running_bill_tab_test ] == '+' )
        {
            printf ( "第%d次 \n" , running_bill_tab_test + 1 );
            printf ( "存入%.3lf元 " , running_bill[ running_bill_tab_test ] );
            printf ( "余额%.3lf元 \n" , running_bill_balance[ running_bill_tab_test ] );
        }
        if ( running_bill_symbol[ running_bill_tab_test ] == '-' )
        {
            printf ( "第%d次 \n" , running_bill_tab_test + 1 );
            printf ( "取出%.3lf元 " , running_bill[ running_bill_tab_test ] );
            printf ( "余额%.3lf元 \n" , running_bill_balance[ running_bill_tab_test ] );
        }
    }
    if ( running_bill_tab == 0 ) // 如果用户没有取款记录
    {
        printf ( "暂无存取款记录 \n" );
    }
    printf ( "---金额流水结束--- \n" );
    printf ( "按回车结束" );
    while ( getchar ( ) != '\n' );//清除缓存
    account_mode1_program ( );
}

//模式一 个人信息 修改账号
void account_mode1_part2_program ()
{
    account_modify_number_tab:  //修改账号标签
    {
        printf ( "-----修改账号----\n" );
        printf ( "请输入原账号:" );
        scanf ( "%s" , account_number_test );
        if ( strcmp ( account_number , account_number_test ) != 0 )
        {
            printf ( "与原账号不相同,请重新输入 \n" );
            goto account_modify_number_tab;
        }
        printf ( "请输入新账号:" );
        scanf ( "%s" , account_number );
    }
    printf ( "修改账户成功!\n" );
    printf ( "新账号名:%s \n" , account_number );
    while ( getchar ( ) != '\n' );//清除缓存
    account_mode1_program ( );
}

//模式一 个人信息 修改密码
void account_mode1_part3_program ()
{
    account_modify_password_tab:  //修改密码标签
    {
        printf ( "-----修改密码----\n" );
        printf ( "请输入原密码:" );
        scanf ( "%s" , account_password_test );
        if ( strcmp ( account_password , account_password_test ) != 0 )
        {
            printf ( "与原密码不相同,请重新输入 \n" );
            goto account_modify_password_tab;
        }
        printf ( "请输入新密码:" );
        scanf ( "%s" , account_password );
    }
    printf ( "修改密码成功!\n" );
    printf ( "新密码:%s \n" , account_password );
    while ( getchar ( ) != '\n' );//清除缓存
    account_mode1_program ( );
}

//模式一 个人信息 修改取款密码
void account_mode1_part4_program ()
{
    account_modify_password_1_tab:  //注册取款密码标签
    {
        printf ( "-----修改取款密码(只能输入6位)----\n" );
        printf ( "请输入原取款密码:" );
        scanf ( "%s" , account_password_1_test );
        if ( strcmp ( account_password_1 , account_password_1_test ) != 0 )
        {
            while ( getchar ( ) != '\n' );//清除缓存
            printf ( "两次输入不相同,请重新输入 \n" );
            goto account_modify_password_1_tab;
        }
    }

    account_modify_password_2_tab:
    {
        printf ( "请输入新取款密码:" );
        scanf ( "%s" , account_password_1 );
        //校验是不是6位
        account_password_1_test_1 = strlen ( account_password_1 );
        if ( account_password_1_test_1 != 6 )
        {
            while ( getchar ( ) != '\n' );//清除缓存
            printf ( "当前输入了%d位,请重新输入 \n" , account_password_1_test_1 );
            goto account_modify_password_2_tab;
        }

    }

    printf ( "修改取款密码成功! \n" );
    printf ( "新取款密码:%s \n" , account_password_1 );
    while ( getchar ( ) != '\n' );//清除缓存
    account_mode1_program ( );
}

//模式二 存款
void account_mode2_program ()
{
    account_mode2_pick_1:
    printf ( "请输入需要存入多少钱:" );
    while ( ( scanf ( "%lf" , & save ) != 1 )&& save < 0)
    {
        printf ( "请重新输入合法的金额:" );
        while ( getchar ( ) != '\n' );//清除缓存
        continue;
    }
    if ( save < 0 )
    {
        printf ( "不能输入负值\n" );
        while ( getchar ( ) != '\n' );//清除缓存
        goto account_mode2_pick_1;
    }
    balance += save; //存款
    running_bill[ running_bill_tab ] = save;//保存流水
    running_bill_balance[ running_bill_tab ] = balance; //保存历史记录
    running_bill_symbol[ running_bill_tab ] = '+'; //保存取款还是存款
    ++ running_bill_tab;
    printf ( "存款成功 \n" );
    printf ( "当前余额:%.3lf \n" , balance );
    while ( getchar ( ) != '\n' );//清除缓存
    account_home_program ( );
}

//模式三 取款
void account_mode3_program ()
{
    account_mode3_pick_1:  //校验取款密码标签
    {
        printf ( "-----取款密码(只能输入6位)----\n" );
        printf ( "请输入取款密码:" );
        scanf ( "%s" , account_password_1_test );
        if ( strcmp ( account_password_1 , account_password_1_test ) != 0 )
        {
            while ( getchar ( ) != '\n' );//清除缓存
            printf ( "输入密码错误,请重新输入 \n" );
            goto account_mode3_pick_1;
        }
    }


    account_mode3_pick_2: //取款标签
    {
        printf ( "请输入需要取出多少钱:" );
        while ( scanf ( "%lf" , & withdraw ) != 1  )
        {
            printf ( "请重新输入合法的金额:" );
            while ( getchar ( ) != '\n' );//清除缓存
            continue;
        }
        if ( withdraw < 0 )
        {
            printf ( "不能输入负值\n" );
            while ( getchar ( ) != '\n' );//清除缓存
            goto account_mode3_pick_2;
        }
        if ( withdraw > balance )
        {
            printf ( "余额不足\n" );
            while ( getchar ( ) != '\n' );//清除缓存
            goto account_mode3_pick_2;
        }
    }
    balance -= withdraw; //取款
    running_bill[ running_bill_tab ] = withdraw; //保存流水
    running_bill_balance[ running_bill_tab ] = balance; //保存历史记录
    running_bill_symbol[ running_bill_tab ] = '-'; //保存取款还是存款
    ++ running_bill_tab;
    printf ( "存款成功\n" );
    printf ( "当前余额:%.3lf\n" , balance );
    while ( getchar ( ) != '\n' );//清除缓存
    account_home_program ( );
}

//模式四 预测余额
void account_mode4_program ()
{
    account_mode4_program_pick: //输入年份标签
    {
        printf ( "请输入要预测多少年后:" );
        while ( scanf ( "%lf" , & year ) != 1 )
        {
            printf ( "请重新输入合法的年份:" );
            while ( getchar ( ) != '\n' );//清除缓存
            continue;
        }
        if ( year <= 0 )
        {
            printf ( "输入错误年份\n" );
            while ( getchar ( ) != '\n' );//清除缓存
            goto account_mode4_program_pick;
        }
    }
    interest = balance * interest_rate * year; //利息
    prediction = balance + interest; //余额

    printf ( "%.0lf年后 \n" , year );
    printf ( "获得利息:%.3lf\n" , interest );
    printf ( "余额为:%0.3lf\n" , prediction );
    while ( getchar ( ) != '\n' );//清除缓存
    account_home_program ( );
}

//管理员登录页面
void administrastion_login_program ()
{
    printf ( "-----管理员登录页面----\n" );
    printf ( "请输入管理员密码:" );
    scanf ( "%s" , administrators_password_test );
    if ( strcmp ( administrators_password , administrators_password_test ) != 0 )
    {
        while ( getchar ( ) != '\n' );//清除缓存
        printf ( "密码输入错误 \n" );
        bank_home_program ( );
    }
    while ( getchar ( ) != '\n' );//清除缓存
    administrastion_home_program ( );
}

//管理员主页面
void administrastion_home_program ()
{
    int administrastion_home_program_pick;
    printf ( "---管理员界面--- \n" );
    printf ( "1.查看用户个人信息 \n" );
    printf ( "2.查看金额流水\n" );
    printf ( "3.修改用户账号 \n" );
    printf ( "4.修改用户密码 \n" );
    printf ( "5.修改取款密码 \n" );
    printf ( "6.修改银行利率 \n" );
    printf ( "7.返回到账户主页 \n" );
    printf ( "请输入需要进入的模式:" );
    scanf ( "%d" , & administrastion_home_program_pick );
    switch ( administrastion_home_program_pick )
    {
        case 1:
        {
            printf ( "----用户个人信息----\n" );
            printf ( "当前账号:%s \n" , account_number );
            printf ( "当前密码:%s \n" , account_password );
            printf ( "当前取款密码:%s \n" , account_password_1 );
            printf ( "当前余额为:%lf \n" , balance );
            while ( getchar ( ) != '\n' );//清除缓存
            administrastion_home_program ( );
            break;
        }
        case 2:
        {
            while ( getchar ( ) != '\n' );  //清除缓存
            administrastion_mode1_program ( );
            break;
        }
        case 3:
        {
            while ( getchar ( ) != '\n' );  //清除缓存
            administrastion_mode2_program ( );
            break;
        }
        case 4:
        {
            while ( getchar ( ) != '\n' );  //清除缓存
            administrastion_mode3_program ( );
            break;
        }
        case 5:
        {
            while ( getchar ( ) != '\n' );  //清除缓存
            administrastion_mode4_program ( );
            break;
        }
        case 6:
        {
            while ( getchar ( ) != '\n' );  //清除缓存
            administrastion_mode5_program ( );
            break;
        }
        case 7:
        {
            printf ( "返回成功 \n" );
            while ( getchar ( ) != '\n' );//清除缓存
            bank_home_program ( );
            break;
        }
        default:
        {
            printf ( "输入错误,请重新输入 \n" );
            while ( getchar ( ) != '\n' );//清除缓存
            administrastion_home_program ( );
            break;
        }
    }

}

//管理员 查看流水金额
void administrastion_mode1_program ()
{
    printf ( "---金额流水开始--- \n" );
    for ( int running_bill_tab_test = 0 ; running_bill_tab_test < running_bill_tab ; running_bill_tab_test ++ )
    {
        if ( running_bill_symbol[ running_bill_tab_test ] == '+' )
        {
            printf ( "第%d次 \n" , running_bill_tab_test + 1 );
            printf ( "存入%.3lf元 \n" , running_bill[ running_bill_tab_test ] );
            printf ( "余额%.3lf元 \n" , running_bill_balance[ running_bill_tab_test ] );
        }
        if ( running_bill_symbol[ running_bill_tab_test ] == '-' )
        {
            printf ( "第%d次 \n" , running_bill_tab_test + 1 );
            printf ( "取出%.3lf元 \n" , running_bill[ running_bill_tab_test ] );
            printf ( "余额%.3lf元 \n" , running_bill_balance[ running_bill_tab_test ] );
        }
    }
    if ( running_bill_tab == 0 ) // 如果用户没有取款记录
    {
        printf ( "暂无存取款记录 \n" );
    }
    printf ( "---金额流水结束--- \n" );
    printf ( "按回车结束" );
    while ( getchar ( ) != '\n' );//清除缓存
    administrastion_home_program ( );
}

//管理员 修改用户账号
void administrastion_mode2_program ()
{
    administrastion_modify_number_tab:  //修改账号标签
    {
        printf ( "-----修改账号----\n" );
        printf ( "请输入新账号:" );
        scanf ( "%s" , account_number );
        printf ( "请确认新账号:" );
        scanf ( "%s" , account_number_test );
        if ( strcmp ( account_number , account_number_test ) != 0 )
        {
            while ( getchar ( ) != '\n' );//清除缓存
            printf ( "两次输入不相同,请重新输入 \n" );
            goto administrastion_modify_number_tab;
        }
        printf ( "修改账户成功!\n" );
        printf ( "当前用户名为%s\n" , account_number );
        while ( getchar ( ) != '\n' );//清除缓存
        administrastion_home_program ( );
    }
}

//管理员 修改用户密码
void administrastion_mode3_program ()
{
    account_modify_password_tab:  //修改密码标签
    {
        printf ( "-----修改密码----\n" );
        printf ( "请输入密码:" );
        scanf ( "%s" , account_password );
        printf ( "请确认密码:" );
        scanf ( "%s" , account_password_test );
        if ( strcmp ( account_password , account_password_test ) != 0 )
        {
            while ( getchar ( ) != '\n' );//清除缓存
            printf ( "两次输入不相同,请重新输入 \n" );
            goto account_modify_password_tab;
        }
        printf ( "修改密码成功!\n" );
        printf ( "当前密码为%s\n" , account_password );
        while ( getchar ( ) != '\n' );//清除缓存
        administrastion_home_program ( );
    }
}

//管理员 修改用户取款密码
void administrastion_mode4_program ()
{
    account_modify_password_1_tab:  //修改密码标签
    {
        printf ( "-----修改取款密码(只能输入6位)----\n" );
        printf ( "请输入新的取款密码:" );
        scanf ( "%s" , account_password_1 );
        //校验是不是6位
        account_password_1_test_1 = strlen ( account_password_1 );
        if ( account_password_1_test_1 != 6 )
        {
            while ( getchar ( ) != '\n' );//清除缓存
            printf ( "当前输入了%d位,请重新输入 \n" , account_password_1_test_1 );
            goto account_modify_password_1_tab;
        }

        printf ( "请确认取款密码:" );
        scanf ( "%s" , account_password_1_test );
        if ( strcmp ( account_password_1 , account_password_1_test ) != 0 )
        {
            while ( getchar ( ) != '\n' );//清除缓存
            printf ( "两次输入不相同,请重新输入 \n" );
            goto account_modify_password_1_tab;
        }
    }
    printf ( "修改取款密码成功!\n" );
    printf ( "当前密码为%s\n" , account_password_1 );
    while ( getchar ( ) != '\n' );//清除缓存
    administrastion_home_program ( );
}

// 管理员修改年利率
void administrastion_mode5_program ()
{
    account_modify_interest_rate_tab: // 修改年利率标签
    {
        printf ( "-----修改年利率----\n" );
        printf ( "请输入调整后的利率不用加%%:" );
        scanf ( "%lf" , & interest_rate_test );
        printf ( "请确认年利率:" );
        scanf ( "%lf" , & interest_rate );
        if ( interest_rate != interest_rate_test )
        {
            while ( getchar ( ) != '\n' ); // 清除缓存
            printf ( "两次输入不相同,请重新输入 \n" );
            goto account_modify_interest_rate_tab;
        }
        interest_rate = interest_rate / 100;
        printf ( "修改年利率成功!\n" );
        printf ( "当前年利率:%.3lf%%\n" , interest_rate * 100 );
        while ( getchar ( ) != '\n' ); // 清除缓存
        administrastion_home_program ( );
    }
}

//主函数
int main ()
{
    //银行
    bank_home_program ( );
    return 0;
}
