import random
import time
import pymysql
import re

host = '121.4.180.183'  # 连接名称，默认127.0.0.1
user = 'study'  # 用户名
passwd = 'Bu!&Cre6h@pR%S'  # 密码
port = 3306  # 端口，默认为3306
db = 'study'  # 数据库名称
charset = 'utf8mb4'  # 字符编码

quantity = 20


def test_link():
    try:
        # 连接数据库
        conn = pymysql.connect(host=host, user=user, passwd=passwd, port=port, db=db, charset=charset)

        # 连接成功
        print("Connected to MySQL database successfully!")

        # 可以在此处执行数据库操作

        # 关闭连接
        conn.close()

    except pymysql.Error as e:
        # 连接失败，打印异常信息
        print("Failed to connect to MySQL database:", e)
        time.sleep(3)
        exit(1)


def detection_work_day():
    conn = pymysql.connect(host=host, user=user, passwd=passwd, port=port, db=db, charset=charset)

    cursor = conn.cursor()

    cursor.execute('delete from Mistake WHERE Date != CURDATE();')
    cursor.execute('SELECT Date FROM Mistake WHERE Date = CURDATE();')

    rows = cursor.fetchall()
    if len(rows) < 20:
        cursor.execute('SELECT English,Chinese FROM Work')
        work = cursor.fetchall()
        for _ in range(20 - len(rows)):
            test = random.choice(work)
            English = test[0]
            Chinese = test[1]
            Data = time.strftime("%Y-%m-%d", time.localtime())
            cursor.execute('insert into Mistake(English, Chinese, Date)\n'
                           f"values ('{English}','{Chinese}','{Data}')")
            conn.commit()

    cursor.close()
    conn.close()


def add_error(english):
    conn = pymysql.connect(host=host, user=user, passwd=passwd, port=port, db=db, charset=charset)

    cursor = conn.cursor()

    cursor.execute(f"update Work set frequency = frequency+1 where English='{english}'")

    conn.commit()

    cursor.close()
    conn.close()


def read_work_day():
    conn = pymysql.connect(host=host, user=user, passwd=passwd, port=port, db=db, charset=charset)

    cursor = conn.cursor()

    cursor.execute('SELECT English, Chinese FROM Mistake WHERE Date = CURDATE();')

    rows = cursor.fetchall()

    cursor.close()
    conn.close()

    return rows


def study_day(work_day):
    i = 0
    while i < quantity:
        print("-" * 20)
        print(f"第{i + 1}个")
        print("English\t:\t" + work_day[i][0])
        print("Chinese\t:\t" + work_day[i][1])
        print("-" * 20)
        j = 0
        while j < 3:
            english = input("请输入单词:")
            chinese = input("请输入意思:")
            if english == work_day[i][0] and chinese == work_day[i][1]:
                print("输入正确")
                j += 1
            else:
                if english != work_day[i][0]:
                    print("单词输入错误")
                if chinese != work_day[i][1]:
                    print("意思输入错误")
                j = 0
            print(f"\n还需要输入{3 - j}次")
        i += 1


def detection_day(work_day):
    for i in range(quantity):
        pick = random.randint(1, 2)
        if pick == 1:
            print("-" * 20)
            print(f"第{i + 1}个")
            print("English\t:\t" + work_day[i][0])
            print("-" * 20)
            Chinese = input("请输入意思:")
            if Chinese == work_day[i][1]:
                print("恭喜你答对了")
            else:
                print(f"正确答案应该是\t{work_day[i][1]}")
                add_error(work_day[i][0])
        else:
            print("-" * 20)
            print(f"第{i + 1}个")
            print("Chinese\t:\t" + work_day[i][1])
            print("-" * 20)
            English = input("请输入单词:")
            if English == work_day[i][0]:
                print("恭喜你答对了")
            else:
                print(f"正确答案应该是\t{work_day[i][0]}")
                add_error(work_day[i][0])
        i += 1


def detection_random():
    conn = pymysql.connect(host=host, user=user, passwd=passwd, port=port, db=db, charset=charset)

    cursor = conn.cursor()

    cursor.execute('select English,Chinese from Work')

    rows = cursor.fetchall()

    works = []
    for _ in range(quantity):
        works.append(random.choice(rows))

    cursor.close()
    conn.close()
    detection_day(works)


def revise_work():
    conn = pymysql.connect(host=host, user=user, passwd=passwd, port=port, db=db, charset=charset)
    chines_pick = re.compile(r'^[\u4e00-\u9fa5]+$')
    english_pick = re.compile(r'^[a-zA-Z]+$')
    number_pick = re.compile(r'^[0-9]+$')
    cursor = conn.cursor()

    cursor.execute('select * from Class;')

    Classs = cursor.fetchall()

    print("\n1.增加单词")
    print('2.删除单词')
    print('3.查询类')
    print('4.查询单词')
    pick = input("请输入:")
    match pick:
        case '1':
            English = input("请输入单词:")
            while not bool(english_pick.fullmatch(English)):
                English = input("请输入单词:")

            Chinese = input("请输入意思:")
            while not bool(chines_pick.fullmatch(Chinese)):
                Chinese = input("请输入意思:")

            Class = input("请输入类")
            while not bool(number_pick.fullmatch(Class)) and not "0" < Class < f"{len(Classs)}" and not Class == "":
                if not bool(number_pick.fullmatch(Class)):
                    print("不是数字")
                if not "0" < Class < f"{len(Classs)}":
                    print("没有此类")
            try:
                if Class == '':
                    cursor.execute('insert into Work(english, chinese)\n'
                                   f"values('{English}','{Chinese}')")
                else:
                    cursor.execute('insert into Work(english, chinese,ClassID)\n'
                                   f"values('{English}','{Chinese}',{Class})")
            except:
                cursor.execute(f"select English ,chinese,ClassID from Work where English='{English}';")
                data = cursor.fetchall()
                if len(data) == 0:
                    print("\n未知错误\n")
                else:
                    print("\n数据已经存在")
                    data = data[0]
                    print(f"English:{data[0]}")
                    print(f"Chinese:{data[1]}")
                    print(f"Chinese:{data[2]}\n")
            else:
                conn.commit()
                print(f"\n添加成功 values('{English}','{Chinese}',{Class})\n")
        case '2':
            English = input("请输入单词:")
            while not bool(english_pick.fullmatch(English)):
                English = input("请输入单词:")
            cursor.execute(f"select English from Work where English='{English}';")
            data = cursor.fetchall()
            if len(data) == 0:
                print("\n没有查到此单词\n")
            else:
                cursor.execute(f"delete from Work where English='{English}';")
                conn.commit()
                print(f"\n{English}删除成功\n")
        case '3':
            print("\n")
            for Class in Classs:
                print(f"id:{Class[0]}\tclass:{Class[1]}")
            print("\n")
        case '4':
            English = input("请输入单词:")
            while not bool(english_pick.fullmatch(English)):
                English = input("请输入单词:")
            cursor.execute(f"select English ,chinese,ClassID from Work where English='{English}';")
            data = cursor.fetchall()
            if len(data) == 0:
                print("\n没有查到此单词\n")
            else:
                for work in data:
                    print(f"\nEnglish:{work[0]}")
                    print(f"Chinese:{work[1]}")
                    print(f"ClassID:{work[2]}\n")


    cursor.close()
    conn.close()


test_link()
detection_work_day()
work_day = read_work_day()
pick = 0

while pick != 'exit':
    print("1.每日学习")
    print("2.每日检测")
    print("3.随机检测")
    print("4.修改单词")
    print('exit 退出')
    pick = input("请输入需要进入的模式:")
    match pick:
        case '1':
            study_day(work_day)
        case '2':
            detection_day(work_day)
        case '3':
            detection_random()
        case '4':
            revise_work()
