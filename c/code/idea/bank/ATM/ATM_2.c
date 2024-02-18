#include<stdio.h>
#include<stdlib.h>

int main ()
{
    //初始化
    int account_1 , password_1 , password_2 = 0 , password_3 = 0 , account_2 = 0 , password_4 = 0; //账号;登录密码,取款密码,登录检查密码,检查登录账户,修改密码判断是不是6位
    char tab_1; //用户是否同意进入
    int tab_a = 0 , tab_b , tab_c , tab_d = 0 , tab_e , tab_f; //判断取款密码是否为6位数.判断取款密码是否为6位数,判断进入登录还是管理员,判断是否进入账户主页主页;账户主页选项;判断用户修改是否输入正确
    int administration_password , administration_a; //管理员密码,判断管理员选项
    double interest = 0 , capital = 10000 , money = 0 , interest_rate = 0.0175 , year = 0 , capital_1 = 0; //利息,本金,变动的钱,利率,年份,预测本金
    //注册账户
    printf ( "第一次使用需要注册账户 \n" );
    printf ( "不同意输入N,输入其他代表同意 \n:" );
    //获取用户是否同意进入
    tab_1 = getchar ( );

    if ( tab_1 == 'n' || tab_1 == 'N' )
    {
        return 1;
    }

    while ( getchar ( ) != '\n' );  //清楚缓存

    //注册登录账户
    printf ( "账户名(只支持数字):" );
    while ( scanf ( "%d" , & account_1 ) != 1 )
    {
        while ( getchar ( ) != '\n' );  //清楚缓存
        printf ( "请输入合法的数字:" );
        continue;
    }

    while ( getchar ( ) != '\n' );  //清楚缓存
    //注册登录密码
    printf ( "登录密码(只支持数字):" );
    while ( scanf ( "%d" , & password_1 ) != 1 )
    {
        while ( getchar ( ) != '\n' );  //清楚缓存
        printf ( "请输入合法的数字:" );
        continue;
    }
    while ( getchar ( ) != '\n' );  //清楚缓存
    //注册取款密码
    //注册取款密码
    printf ( "取款密码(只支持6位数字):" );
    while ( password_2 == 0 )
    {
        //判断是不是输入的数字
        while ( scanf ( "%d" , & password_2 ) != 1 )
        {
            while ( getchar ( ) != '\n' );  //清楚缓存
            printf ( "请输入合法的数字:" );
            continue;
        }
        tab_b = password_2;
        //判断是否为6位数

        while ( tab_b != 0 )
        {
            tab_b /= 10;
            tab_a ++;
        }

        if ( tab_a != 6 )
        {
            printf ( "当前输入%d位,密码是6位数 \n请重新输入:" , tab_a );
            password_2 = 0;
            tab_a = 0;
            continue;
        }
        if ( tab_a == 6 )
        {
            break;
        }
    }
    while ( getchar ( ) != '\n' );  //清楚缓存
    //提示用户输入成功
    printf ( "创建成功 \n" );
    printf ( "账户名:%d \n" , account_1 );
    printf ( "密码:%d \n" , password_1 );
    printf ( "密码:%d \n" , password_2 );
    printf ( "初始金额为%lf \n" , capital );

    //此层循环为主页面开始
    while ( 1 )
    {
        printf ( "----银行主页----\n" );
        printf ( "0.退出程序 \n" );
        printf ( "1.登录银行账户 \n" );
        printf ( "请输入数字:" );
        scanf ( "%d" , & tab_c );
        printf ( "----银行主页----\n" );

        while ( getchar ( ) != '\n' );  //清楚缓存
        //0退出
        if ( tab_c == 0 )
        {
            printf ( "欢迎下次使用" );
            return 1;
        }

        //获取是否输入正确
        if ( tab_c != 0 && tab_c != 1 && tab_c != 2 )
        {
            printf ( "输入错误请重新输入 \n" );
            continue;
        }

        //银行主页开始
        while ( tab_c == 1 )
        {
            printf ( "需要登陆账号 \n" );
            //获取用户账号
            printf ( "请输入账号:" );
            scanf ( "%d" , & account_2 );
            while ( account_1 != account_2 )  //判断账户是否正确
            {
                while ( getchar ( ) != '\n' );  //清楚缓存
                printf ( "请输入正确的账号:" );
                scanf ( "%d" , & account_2 );
            }
            //获取用密码
            printf ( "请输入密码:" );
            scanf ( "%d" , & password_3 );
            while ( password_1 != password_3 )  //判断密码是否正确
            {
                while ( getchar ( ) != '\n' );  //清楚缓存
                printf ( "请输入正确的密码:" );
                scanf ( "%d" , & password_3 );
            }
            // 正确的账号和密码
            printf ( "登录成功!\n" );
            tab_d = 1; //进入主页
            //此层输出账户主页
            while ( tab_d == 1 )
            {
                printf ( "----账户主页----\n" );
                printf ( "0.退出程序 \n" );
                printf ( "1.退出账户 \n" );
                printf ( "2.存钱 \n" );
                printf ( "3.取钱 \n" );
                printf ( "4.查看余额 \n" );
                printf ( "5.预测未来存款(当前利率为%.3lf) \n" , interest_rate );
                printf ( "6.修改账号 \n" );
                printf ( "7.修改密码 \n" );
                printf ( "8.修改取款密码 \n" );
                printf ( "请输入数字:" );
                scanf ( "%d" , & tab_e );
                printf ( "----账户主页----\n" );

                while ( getchar ( ) != '\n' );  //清楚缓存

                //重置判断
                tab_f = 0;
                tab_a = 0; //取款数字是否为6位
                //选择开始
                switch ( tab_e )
                {
                    case 0:
                    {
                        printf ( "欢迎下次使用" );
                        return 1;
                    }

                    case 1:
                    {
                        tab_d = 0; //使不进入其他循环
                        tab_c = 999; //使不进入其他循环
                        printf ( "退出成功\n" );
                        while ( getchar ( ) != '\n' );  //清楚缓存
                        break;
                    }

                    case 2:
                    {
                        printf ( "请输入需要存入多少钱:" );
                        while ( scanf ( "%lf" , & money ) != 1 )
                        {
                            while ( getchar ( ) != '\n' );  //清楚缓存
                            printf ( "请输入合法的数字:" );
                            continue;
                        }
                        capital += money;
                        break;
                    }

                    case 3:
                    {
                        printf ( "请输入当前密码或取款密码:" );
                        while ( scanf ( "%d" , & password_3 ) != 1 || password_3 != password_2 )
                        {
                            while ( getchar ( ) != '\n' );  //清楚缓存
                            printf ( "当密码错误,请重新输入:" );
                            continue;
                        }
                        printf ( "请输入需要取出多少钱:" );
                        while ( scanf ( "%lf" , & money ) != 1 || money > capital )
                        {
                            while ( getchar ( ) != '\n' );  //清楚缓存
                            printf ( "数字不合法或本金不足,请重新输入:" );
                            continue;
                        }
                        capital -= money;
                        break;
                    }

                    case 4:
                    {
                        printf ( "当前余额为%.3lf: \n" , capital );
                        break;
                    }

                    case 5:
                    {
                        printf ( "请输入预测多少年后:" );
                        while ( scanf ( "%lf" , & year ) != 1 || year < 0 )
                        {
                            while ( getchar ( ) != '\n' );  //清楚缓存
                            printf ( "请输入合法的数字:" );
                            continue;
                        }
                        double interest = capital * interest_rate * year; // 计算利息
                        double capital_1 = capital + interest; // 计算预测余额
                        printf ( "预测%.0lf年后获得\n" , year );
                        printf ( "利息%.3lf\n" , interest );
                        printf ( "余额%.3lf \n" , capital_1 );
                    }

                    case 6:
                    {
                        //验证用户开始
                        while ( tab_f == 0 )
                        {
                            printf ( "需要验证用户\n输入0退出\n" );
                            printf ( "请输入当前登录账户名或取款密码:" );
                            while ( scanf ( "%d" , & password_3 ) != 1 )
                            {
                                while ( getchar ( ) != '\n' );  //清楚缓存
                                printf ( "数字不合法或密码错误,请重新输入:" );
                                continue;
                            }

                            //检查是否退出
                            if ( password_3 == 0 )
                            {
                                printf ( "退出成功" );
                                tab_f = 1;
                                break;
                            }

                            //输入成功退出
                            if ( password_3 == password_2 || password_3 == account_1 )
                            {
                                printf ( "验证成功 \n" );
                                tab_f = 1;
                                break;
                            } else
                            {
                                printf ( "输入错误请重新输入 \n" );
                                continue;
                            }

                        }//验证用户结束


                        //修改新账户
                        while ( tab_a == 0 )
                        {
                            printf ( "请输入新账户名:" );
                            while ( scanf ( "%d" , & password_3 ) != 1 )
                            {
                                while ( getchar ( ) != '\n' );  //清楚缓存
                                printf ( "非法数字,请重新输入:" );
                                continue;
                            }

                            //二次确认账户
                            printf ( "请二次输入你的账户名:" );
                            while ( scanf ( "%d" , & password_4 ) != 1 || password_4 != password_3 )
                            {
                                while ( getchar ( ) != '\n' );  //清楚缓存
                                printf ( "账户名不一样,请重新输入:" );
                                continue;
                            }
                            //退出循环
                            break;
                        }//修改新的账户结束

                        account_1 = password_3;
                        printf ( "修改账号成功" );
                        printf ( "当前账户名是%d" , account_1 );
                        break;
                    }

                    case 7:
                    {
                        //验证用户开始
                        while ( tab_f == 0 )
                        {
                            printf ( "需要验证用户\n输入0退出\n" );
                            printf ( "请输入当前登录密码或取款密码:" );
                            while ( scanf ( "%d" , & password_3 ) != 1 )
                            {
                                while ( getchar ( ) != '\n' );  //清楚缓存
                                printf ( "数字不合法或密码错误,请重新输入:" );
                                continue;
                            }

                            //检查是否退出
                            if ( password_3 == 0 )
                            {
                                printf ( "退出成功" );
                                tab_f = 1;
                                break;
                            }

                            //输入成功退出
                            if ( password_3 == password_2 || password_3 == password_1 )
                            {
                                printf ( "验证成功 \n" );
                                tab_f = 1;
                                break;
                            } else
                            {
                                printf ( "输入错误请重新输入 \n" );
                                continue;
                            }

                        }//验证用户结束


                        //修改新密码
                        while ( tab_a == 0 )
                        {
                            printf ( "请输入新密码:" );
                            while ( scanf ( "%d" , & password_3 ) != 1 )
                            {
                                while ( getchar ( ) != '\n' );  //清楚缓存
                                printf ( "非法数字,请重新输入:" );
                                continue;
                            }

                            //二次确认密码
                            printf ( "请二次输入你的密码:" );
                            while ( scanf ( "%d" , & password_4 ) != 1 || password_4 != password_3 )
                            {
                                while ( getchar ( ) != '\n' );  //清楚缓存
                                printf ( "密码不一样,请重新输入:" );
                                continue;
                            }
                            //退出循环
                            break;
                        }//修改新的密码结束

                        password_1 = password_3;
                        printf ( "修改账户密码成功" );
                        printf ( "当前密码为:%d" , password_1 );
                        break;
                    }

                    case 8:
                    {
                        //验证用户开始
                        while ( tab_f == 0 )
                        {
                            printf ( "需要验证用户\n输入0退出\n" );
                            printf ( "请输入当前取款密码或账户登录密码:" );
                            while ( scanf ( "%d" , & password_3 ) != 1 )
                            {
                                while ( getchar ( ) != '\n' );  //清楚缓存
                                printf ( "数字不合法或密码错误,请重新输入:" );
                                continue;
                            }

                            //检查是否退出
                            if ( password_3 == 0 )
                            {
                                printf ( "退出成功" );
                                tab_f = 1;
                                break;
                            }

                            //输入成功退出
                            if ( password_3 == password_2 || password_3 == password_1 )
                            {
                                printf ( "验证成功 \n" );
                                tab_f = 1;
                                break;
                            } else
                            {
                                printf ( "输入错误请重新输入 \n" );
                                continue;
                            }

                        }//验证用户结束

                        //修改新密码
                        while ( tab_a != 6 )
                        {
                            printf ( "请输入新密码:" );
                            while ( scanf ( "%d" , & password_3 ) != 1 )
                            {
                                while ( getchar ( ) != '\n' );  //清楚缓存
                                printf ( "非法数字,请重新输入:" );
                                continue;
                            }

                            //判断是否为6位数
                            tab_a = 0;//初始化判断

                            //为了防止刚刚的密码没有了

                            password_4 = password_3;
                            while ( password_4 != 0 )
                            {
                                password_4 /= 10;
                                tab_a ++;
                            }

                            if ( tab_a != 6 )
                            {
                                printf ( "当前输入%d位,密码是6位数 \n请重新输入\n" , tab_a );
                                continue;
                            }

                            if ( tab_a == 6 )
                            {
                                printf ( "请二次输入你的密码:" );
                                while ( scanf ( "%d" , & password_4 ) != 1 || password_4 != password_3 )
                                {
                                    while ( getchar ( ) != '\n' );  //清楚缓存
                                    printf ( "密码不一样,请重新输入:" );
                                    continue;
                                }
                                if ( password_4 == password_3 )
                                {
                                    break;
                                }
                                break;
                            }//修改新的密码结束


                        }

                        password_2 = password_3;
                        printf ( "修改取款密码成功" );
                        printf ( "当前密码为:%d \n" , password_2 );
                        break;
                    }

                    default: //输入了其他
                    {
                        printf ( "输入错误,请重新输入 \n" );
                        while ( getchar ( ) != '\n' );  //清楚缓存
                        break;
                    }
                }//选择结束
            }


        }//银行主页结束


    }//此层循环为主页面结束
    return 0;
}
