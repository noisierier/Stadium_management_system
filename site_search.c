#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include"site_search.h"
#include"delay.h"
#include<stdbool.h>
#include"info_management.h"
#define _CRT_SECURE_NO_WARNINGS 1


const char* hall__names[] = { "球类场馆","游泳场馆","室外场馆" };


time_t now; // 当前时间

int hallsNum = sizeof(halls) / sizeof(halls[0]);  // 获取场馆数

int courtsNum = sizeof(halls[0].courts) / sizeof(halls[0].courts[0]);  // 获取场地数

void inquiry_menu(void)//管理员查看场地预定函数界面
{   
    system("cls");
    printf(" __________________________________________________\n");
    printf(" ________________体育馆预定及管理系统______________\n");
    printf(" __________________________________________管理员版\n");
    printf("\t\t 请选择您的需求\t\t\t\n");
    printf(" __________________________________________________\n");
    printf("|                                                  |\n");
    printf("|    1.按场地编号显示场地预定情况                  |\n");
    printf("|                                                  |\n");
    printf("|    2.按场馆编号显示场地预定情况                  |\n");
    printf("|                                                  |\n");
    printf("|    3.使用说明                                    |\n");
    printf("|                                                  |\n");
    printf("|    4.返回预定管理界面                            |\n");
    printf("|                                                  |\n");
    printf("|__________________________________________________|\n");
    inquiry_choose();
}

void inquiry_choose(void)//用户预定查询界面选择函数
{
    readFromFile();
    char flag;
    char courtNum;// 读取用户输入的场馆编号
    char hallNum; // 用于存储用户输入的场馆编号
    printf("请输入您的选项：");
    flag = getch();
    printf("%c", flag);
    delay(100);
    while (flag != '1' && flag != '2' && flag != '3'&&flag!='4')
    {
        printf("\n请根据提示，输入'1'或'2'或'3'或'4'：");
        flag = getch();
        printf("%c", flag);
        delay(100);
    }
    switch (flag)
    {
        case '1':
            system("cls");
            printf("\n请输入要寻找的场地号(请输入整数)：");
            courtNum = getch();
            printf("%c", courtNum);
            delay(100);
            while (!isdigit(courtNum))
            {
                printf("\n输入格式错误，请输入整数：");
                courtNum = getch();
                printf("%c", courtNum);
                delay(100);
            }
            system("CLS");
            int courtNum_ = courtNum - '0';
            printCourtStatusByCourt(courtNum_); //按场地编号显示场地预定情况
            inquiry_menu_return();
            break;
        case '2':
            system("cls");
            printf("\n请输入要寻找的场馆编号：");
            hallNum = getch();
            printf("%c", hallNum);
            delay(100);
            while (!isdigit(hallNum))
            {
                printf("\n输入格式错误，请输入整数：");
                hallNum = getch();
                printf("%c", hallNum);
                delay(100);
            }
            system("CLS");
            int hallNum_ = hallNum - '0';
            printCourtStatusByHall(hallNum_); // 按场馆编号显示场地预定情况
            inquiry_menu_return();
            break;
        case'3':
            system("cls");//使用说明
            printf("使用说明\n");
            inquiry_menu_return();
            break;
        case '4': printf("\n正在返回······");
            delay(500);
            Scheduled_anagement();
            break;
        default:
            break;
    }
}

void inquiry_menu_user(void)//用户查看场地预定函数界面
{
    system("cls");
    printf(" __________________________________________________\n");
    printf(" ____________体育馆场地预定情况查询系统____________\n");
    printf(" __________________________________________用户版本\n");
    printf("\t\t 请选择您的需求\t\t\t\n");
    printf(" __________________________________________________\n");
    printf("|                                                  |\n");
    printf("|    1.按场地编号显示场地预定情况                  |\n");
    printf("|                                                  |\n");
    printf("|    2.按场馆编号显示场地预定情况                  |\n");
    printf("|                                                  |\n");
    printf("|    3.使用说明                                    |\n");
    printf("|                                                  |\n");
    printf("|    4.返回预定管理界面                            |\n");
    printf("|                                                  |\n");
    printf("|__________________________________________________|\n");
    inquiry_choose_user();
}

void inquiry_choose_user(void)//用户预定查询界面选择函数
{
    readFromFile();
    char flag;
    char courtNum;// 读取用户输入的场馆编号
    char hallNum; // 用于存储用户输入的场馆编号
    printf("请输入您的选项：");
    flag = getch();
    printf("%c", flag);
    delay(100);
    while (flag != '1' && flag != '2' && flag != '3' && flag != '4')
    {
        printf("\n请根据提示，输入'1'或'2'或'3'或'4'：");
        flag = getch();
        printf("%c", flag);
        delay(100);
    }
    switch (flag)
    {
    case '1':
        system("cls");
        printf("\n请输入要寻找的场地号(请输入整数)：");
        courtNum = getch();
        printf("%c", courtNum);
        delay(100);
        while (!isdigit(courtNum))
        {
            printf("\n输入格式错误，请输入整数：");
            courtNum = getch();
            printf("%c", courtNum);
            delay(100);
        }
        system("CLS");
        int courtNum_ = courtNum - '0';
        printCourtStatusByCourt(courtNum_); //按场地编号显示场地预定情况
        inquiry_menu_return_user();
        break;
    case '2':
        system("cls");
        printf("\n请输入要寻找的场馆编号：");
        hallNum = getch();
        printf("%c", hallNum);
        delay(100);
        while (!isdigit(hallNum))
        {
            printf("\n输入格式错误，请输入整数：");
            hallNum = getch();
            printf("%c", hallNum);
            delay(100);
        }
        system("CLS");
        int hallNum_ = hallNum - '0';
        printCourtStatusByHall(hallNum_); // 按场馆编号显示场地预定情况
        inquiry_menu_return_user();
        break;
    case'3':
        system("cls");//使用说明
        printf("使用说明\n");
        inquiry_menu_return_user();
        break;
    case '4': printf("\n正在返回······");
        delay(500);
        reserve_message();
        break;
    default:
        break;
    }
}

void inquiry_menu_return(void)//管理员返回预定查询界面
{
    printf("按任意键返回预定查询界面：");
    char key_board = getch();
    if (key_board != NULL)
    {
        printf("%c", key_board);
        delay(100);
        inquiry_menu();
    }   
}

void inquiry_menu_return_user(void)//用户返回预定查询界面
{
    printf("按任意键返回预定查询界面：");
    char key_board = getch();
    if (key_board != NULL)
    {
        printf("%c", key_board);
        delay(100);
        inquiry_menu_user();
    }
}

void redcol(const char* text) // 设置红色字体
{
    printf("\033[1;31m%s\033[0m", text);   
}

void greencol(const char* text) // 设置绿色字体
{
    printf("\033[1;32m%s\033[0m", text);   
}

void lightbluecol(const char* text)// 设置浅蓝色字体
{
    printf("\033[1;94m%s\033[0m", text);   
}

void printCourtStatusByCourt(int courtNum)//通过场地来打印预定情况
{
    int found = 0; // 标志是否找到匹配的场地
    struct DateTime currentDateTime = getCurrentDateTime();    // 调用函数获取当前日期和时间
    printf("当前日期：%d-%02d-%02d\n", currentDateTime.year, currentDateTime.month, currentDateTime.day);    // 打印当前日期
    printf("场地编号：%d\n\n", courtNum);

    for (int i = 0; i < hallsNum; i++) 
    {
        for (int j = 0; j < halls[i].NumOfCourt; j++)// 遍历每个场地
        {  
            if (halls[i].courts[j].courtNum == courtNum)// 检查场地编号是否匹配
            { 
                printf("场馆号：%d\n", halls[i].hallNum);  // 打印场馆号
                printf("场馆名称：%s\n", hall__names[i]);
                printf("场地预订信息：\n");
                for (int d = 0; d < 7; d++) 
                {
                    struct Date printDate;
                    printDate.year = currentDateTime.year;
                    printDate.month = currentDateTime.month;
                    printDate.day = currentDateTime.day;

                    // 计算并打印日期
                    printDate.day += d;
                    if (printDate.day > 30) 
                    {
                        printDate.day -= 30;
                        printDate.month++;
                    }
                    if (printDate.month > 12) 
                    {
                        printDate.month -= 12;
                        printDate.year++;
                    }

                    printf("%d-%02d-%02d:\n", printDate.year, printDate.month, printDate.day+1);

                    for (int k = 0; k < 16; k++)
                    {
                        printf("%d：00-%d：00 ", (k + 6), (k + 7));
                        int num = halls[i].courts[j].time[d][k];
                        if (num == halls[i].courts[j].maxPerson) 
                        {
                            printf("\033[1;31m(%d/%d)\033[0m ", num, halls[i].courts[j].maxPerson);
                        }
                        else if (num < halls[i].courts[j].maxPerson)
                        {
                            printf("\033[1;32m(%d/%d)\033[0m ", num, halls[i].courts[j].maxPerson);
                        }
                        else 
                        {
                            printf("\033[1;31m(%d/%d)\033[0m ", num, halls[i].courts[j].maxPerson);
                        }
                        printf(" ┃  ");
                    }
                    printf("\n");
                }
                printf("\n");
                found = 1; // 标志为已找到匹配的场地
            }
        }
    }
    // 如果未找到匹配的场地，输出提示
    if (!found) 
    {
        printf("未找到匹配的场地编号：%d\n", courtNum);
    }
}

void printCourtStatusByHall(int hallNum) //通过场馆来打印预定情况
{
    int found = 0; // 标志是否找到匹配的场馆
    struct DateTime currentDateTime = getCurrentDateTime();    // 调用函数获取当前日期和时间
    printf("当前日期：%d-%02d-%02d\n", currentDateTime.year, currentDateTime.month, currentDateTime.day);    // 打印当前日期

    for (int i = 0; i < hallsNum; i++)
    {
        if (halls[i].hallNum == hallNum)// 检查场馆编号是否匹配
        { 
            found = 1; // 设置标志为已找到
            printf("场馆号：%d\n", halls[i].hallNum);
            printf("场馆名称：%s\n\n", hall__names[i]);
            // 打印场地预订情况
            for (int j = 0; j < halls[i].NumOfCourt; j++) 
            {
                printf("场地编号：%s (%d/%d)\n", halls[i].courts[j].courtId, halls[i].courts[j].maxPerson, halls[i].courts[j].maxPerson);
                printf("场地预订信息：\n");
                for (int d = 0; d < 7; d++) 
                {
                    struct Date printDate;
                    printDate.year = currentDateTime.year;
                    printDate.month = currentDateTime.month;
                    printDate.day = currentDateTime.day;

                    // 计算并打印日期
                    printDate.day += d;
                    if (printDate.day > 30)
                    {
                        printDate.day -= 30;
                        printDate.month++;
                    }
                    if (printDate.month > 12) 
                    {
                        printDate.month -= 12;
                        printDate.year++;
                    }

                    printf("%d-%02d-%02d:\n", printDate.year, printDate.month, printDate.day+1);

                    for (int k = 0; k < 16; k++) 
                    {
                        printf("%d：00-%d：00 ", (k + 6), (k + 7));
                        int num = halls[i].courts[j].time[d][k];
                        if (num == halls[i].courts[j].maxPerson) 
                        {
                            printf("\033[1;31m(%d/%d)\033[0m ", num, halls[i].courts[j].maxPerson);
                        }
                        else if (num < halls[i].courts[j].maxPerson) 
                        {
                            printf("\033[1;32m(%d/%d)\033[0m ", num, halls[i].courts[j].maxPerson);
                        }
                        else 
                        {
                            printf("\033[1;31m(%d/%d)\033[0m ", num, halls[i].courts[j].maxPerson);
                        }
                        printf(" ┃  ");
                    }
                    printf("\n");
                }
                printf("\n");
            }
        }
    }
    // 如果没有找到匹配的场馆编号
    if (!found) {
        printf("未找到匹配的场馆编号：%d\n", hallNum);
    }
}

void saveToFile() //保存场馆文件
{
    FILE* file = fopen("site.txt", "w");
    if (file == NULL)
    {
        printf("无法打开文件\n");
        return;
    }
    for (int i = 0; i < 3; i++) 
    {
        fprintf(file, "%d\n", halls[i].hallNum); // 保存场馆编号
        fprintf(file, "%d\n", halls[i].NumOfCourt);
        fprintf(file, "%s\n", halls[i].name);
        fprintf(file, "%s\n", halls[i].hallRegion);
        fprintf(file, "%s\n", halls[i].sportType);
        fprintf(file, "%d\n", halls[i].minAge);
        fprintf(file, "%d\n", halls[i].maxAge);
        for (int j = 0; j < halls[i].NumOfCourt; j++)
        {
            fprintf(file, "%d\n", halls[i].courts[j].courtNum);
            fprintf(file, "%d\n", halls[i].courts[j].rentRerHour);
            fprintf(file, "%s\n", halls[i].courts[j].courtId);
            for (int d = 0; d < 7; d++)
            {
                for (int k = 0; k < 16; k++)
                {
                    fprintf(file, "%d ", halls[i].courts[j].time[d][k]);
                }
                fprintf(file, "\n");
            }
            fprintf(file, "%d\n", halls[i].courts[j].maxPerson);
        }
        if (i < 2)
        {
            fprintf(file, "\n"); // 大厅之间添加一个空行，但不在最后一个大厅之后添加
        }
    }
    fclose(file);
}

void readFromFile()//打开文件
{
    FILE* file = fopen("site.txt", "r");
    if (file == NULL) 
    {
        printf("无法打开文件\n");
        return;
    }
    for (int i = 0; i < 3; i++) 
    {
        fscanf(file, "%d", &halls[i].hallNum); // 读取场馆编号
        fscanf(file, "%d", &halls[i].NumOfCourt);//场地个数
        fscanf(file, "%s", halls[i].name);//场馆名称
        fscanf(file, "%s", halls[i].hallRegion);//场馆区域
        fscanf(file, "%s", halls[i].sportType);//场馆运动类型
        fscanf(file, "%d", &halls[i].minAge);//场馆最小年龄限制
        fscanf(file, "%d", &halls[i].maxAge);//场馆最大年龄限制
        for (int j = 0; j < halls[i].NumOfCourt; j++)
        {
            fscanf(file, "%d", &halls[i].courts[j].courtNum); // 读取场地编号
            fscanf(file, "%d", &halls[i].courts[j].rentRerHour);
            fscanf(file, "%s", halls[i].courts[j].courtId); // 读取场地ID
            for (int d = 0; d < 7; d++)
            {
                for (int k = 0; k < 16; k++) 
                {
                    fscanf(file, "%d", &halls[i].courts[j].time[d][k]);
                }
            }
            fscanf(file, "%d", &halls[i].courts[j].maxPerson);
        }
    }
    fclose(file);
}

struct Date getCurrentDate()//获取现在的时间
{
    struct Date currentDate;

    time_t currentTime;
    struct tm* localTime;

    // 获取当前时间的秒数
    currentTime = time(NULL);

    // 转换为本地时间结构体
    localTime = localtime(&currentTime);

    // 提取日期信息
    currentDate.year = localTime->tm_year + 1900; // 年份需要加上1900
    currentDate.month = localTime->tm_mon + 1;    // 月份是从0开始的，所以需要加1
    currentDate.day = localTime->tm_mday;         // 当月的第几天

    return currentDate;
}

struct DateTime getCurrentDateTime()//获取时间（更加精细）
{
    struct DateTime currentDateTime;

    time_t currentTime;
    struct tm* localTime;

    // 获取当前时间的秒数
    currentTime = time(NULL);

    // 转换为本地时间结构体
    localTime = localtime(&currentTime);

    // 提取日期和小时信息
    currentDateTime.year = localTime->tm_year + 1900; // 年份需要加上1900
    currentDateTime.month = localTime->tm_mon + 1;    // 月份是从0开始的，所以需要加1
    currentDateTime.day = localTime->tm_mday;         // 当月的第几天
    currentDateTime.hour = localTime->tm_hour;        // 当前小时数

    return currentDateTime;
}

void read_site_menu_user(void)//场地查询界面——用户
{
    readFromFile();//从文件中读取场馆场地信息并将其存储到结构体中
    /*直接用strcpy语句给三个场馆的hallRegion[10]（所属区域）
   sportType[12](运动类型)赋值中文字符串 因为文件读取不了中文字符串*/
    strcpy(halls[0].sportType, "室内球类运动");
    strcpy(halls[1].sportType, "游泳相关运动");
    strcpy(halls[2].sportType, "足球及田径项目");
    strcpy(halls[0].name, "球类场馆");
    strcpy(halls[1].name, "游泳场馆");
    strcpy(halls[2].name, "室外场馆");
    delay(100);
    system("cls");
    printf(" __________________________________________________\n");
    printf(" ________________体育馆场地查询系统________________\n");
    printf(" __________________________________________用户版本\n");
    printf("\t\t 请选择您的需求\t\t\t\n");
    printf(" __________________________________________________\n");
    printf("|                                                  |\n");
    printf("|    1.通过场馆名称查询                            |\n");
    printf("|                                                  |\n");
    printf("|    2.通过场馆所属区域查询                        |\n");
    printf("|                                                  |\n");
    printf("|    3.通过场地运动类型查询                        |\n");
    printf("|                                                  |\n");
    printf("|    4.通过过滤预约人数已满场地查询                |\n");
    printf("|                                                  |\n");
    printf("|    5.返回上一级界面                              |\n");
    printf("|                                                  |\n");
    printf("|__________________________________________________|\n");
    read_site_choose_user();
}

void read_site_choose_user(void)//查询场地信息选择——用户
{
    char flag;
    printf("请输入您的选项：");
    flag = getch();
    printf("%c", flag);
    delay(100);
    while (flag != '1' && flag != '2' && flag != '3' && flag != '4' && flag != '5')
    {
        printf("\n请根据提示，输入'1'或'2'或'3'或'4'或'5'：");
        flag = getch();
        printf("%c", flag);
        delay(100);
    }
    switch (flag)
    {
    case '1': findHallbyName();//通过场馆名称查询
        read_site_menu_return_user();
        break;
    case '2': findHallbyRegion();//通过场馆所属区域查询
        read_site_menu_return_user();
        break;
    case '3':findHallbyType();//通过场地运动类型查询
        read_site_menu_return_user();
        break;
    case '4':findAvailableCourts();//通过过滤预约人数已满场地查询
        read_site_menu_return_user();
        break;
    case '5':printf("\n正在返回······");
        delay(500);
        user_menu();
    default:
        break;
    }
}

void read_site_menu_ad(void) //场地查询界面——管理员
{
    readFromFile();//从文件中读取场馆场地信息并将其存储到结构体中
    /*直接用strcpy语句给三个场馆的hallRegion[10]（所属区域）
  sportType[12](运动类型)赋值中文字符串 因为文件读取不了中文字符串*/
    strcpy(halls[0].sportType, "室内球类运动");
    strcpy(halls[1].sportType, "游泳相关运动");
    strcpy(halls[2].sportType, "足球及田径项目");
    strcpy(halls[0].name, "球类场馆");
    strcpy(halls[1].name, "游泳场馆");
    strcpy(halls[2].name, "室外场馆");
    delay(100);
    system("cls");
    printf(" __________________________________________________\n");
    printf(" ________________体育馆场地及管理系统______________\n");
    printf(" __________________________________________管理员版\n");
    printf("\t\t 请选择您的需求\t\t\t\n");
    printf(" __________________________________________________\n");
    printf("|                                                  |\n");
    printf("|    1.通过场馆名称查询                            |\n");
    printf("|                                                  |\n");
    printf("|    2.通过场馆所属区域查询                        |\n");
    printf("|                                                  |\n");
    printf("|    3.通过场地运动类型查询                        |\n");
    printf("|                                                  |\n");
    printf("|    4.通过过滤预约人数已满场地查询                |\n");
    printf("|                                                  |\n");
    printf("|    5.返回上一级界面                              |\n");
    printf("|                                                  |\n");
    printf("|__________________________________________________|\n");
    read_site_choose_ad();
}

void read_site_choose_ad(void)//查询场地信息选择
{
    char flag;
    printf("请输入您的选项：");
    flag = getch();
    printf("%c", flag);
    delay(100);
    while (flag != '1' && flag != '2' && flag != '3' && flag != '4' && flag != '5')
    {
        printf("\n请根据提示，输入'1'或'2'或'3'或'4'或'5'：");
        flag = getch();
        printf("%c", flag);
        delay(100);
    }
    switch (flag)
    {
    case '1': findHallbyName();//通过场馆名称查询
        read_site_menu_return_ad();
        break;
    case '2': findHallbyRegion();//通过场馆所属区域查询
        read_site_menu_return_ad();
        break;
    case '3':findHallbyType();//通过场地运动类型查询
        read_site_menu_return_ad();
        break;
    case '4':findAvailableCourts();//通过过滤预约人数已满场地查询
        read_site_menu_return_ad();
        break;
    case '5':printf("\n正在返回······");
        delay(500);
        site_management();
    default:
        break;
    }
}

void findHallbyName()//通过场馆名称查询
{
    char indexChar;
    system("cls");
    printf("请输入要查询的场馆索引 (1/2/3):\n");
    printf("1.球类场馆\n");
    printf("2.游泳场馆\n");
    printf("3.室外场馆\n");
    indexChar = _getch(); // 获取输入的字符
    int index = indexChar - '1';  // 将字符转换为整数索引
    delay(100);
    printHallInfoByIndex(index);
}

void findHallbyRegion() //通过场馆所属区域查询
{
    system("cls");
    char indexChar;
    printf("请输入要查询的场馆索引 (1/2/3):\n");
    printf("1.Region1\n");
    printf("2.Region2\n");
    printf("3.Region3\n");
    indexChar = _getch(); // 获取输入的字符
    int index = indexChar - '1'; // 将字符转换为整数索引
    delay(100);
    printHallInfoByIndex(index);
}

void findHallbyType()//通过场地运动类型查询
{
    char indexChar;
    system("cls");
    printf("请输入要查询的场馆索引 (1/2/3):\n");
    printf("1.室内球类运动\n");
    printf("2.游泳相关运动\n");
    printf("3.足球及田径项目\n");
    indexChar = _getch(); // 获取输入的字符
    int index = indexChar - '1'; // 将字符转换为整数索引
    delay(100);
    printHallInfoByIndex(index);
}

void printHallInfoByIndex(int index) // 通过场馆名称查询并显示信息
{
    if (index >= 0 && index < 3)
    {
        printf("\n场地数量：%d\n", halls[index].NumOfCourt);
        printf("场馆名称: %s\n", halls[index].name);
        printf("所属区域: %s\n", halls[index].hallRegion);
        printf("场馆运动类型: %s\n", halls[index].sportType);
        printf("限制最小年龄: %d\n", halls[index].minAge);
        printf("限制最大年龄: %d\n", halls[index].maxAge);
        int NumOfCourts = sizeof(halls[index].courts) / sizeof(halls[index].courts[0]);
        for (int i = 0; i < NumOfCourts; i++)
        {
            printf("\n");
            printf("场地 %d 的相关信息：\n", i + 1);
            printf("场地ID：%s\n", halls[index].courts[i].courtId);
            printf("每小时的租金：%d\n", halls[index].courts[i].rentRerHour);
        }
    }
    else 
    {
        printf("无效的场馆索引: %d\n", index);
    }
}

void read_site_menu_return_ad(void)//管理员返回场馆查询界面
{
    char free_key;
    printf("\n命令已执行完毕，按任意键返回上一级界面：");
    free_key = getch();
    printf("%c",free_key);
    printf("\n正在返回······");
    delay(500);
    read_site_menu_ad();
}

void read_site_menu_return_user(void)//用户返回场馆查询界面
{
    char free_key;
    printf("\n命令已执行完毕，按任意键返回上一级界面：");
    free_key = getch();
    printf("%c", free_key);
    printf("\n正在返回······");
    delay(500);
    read_site_menu_user();
}

void findAvailableCourts()// 根据日期和时间段查询场地，实现过滤查询
{
    system("cls");
    int selectedDay;
    int selectedTimeSlot;
    char key;
    bool availableCourtsFound = false; // 创建一个标志变量，用于检查是否有符合条件的场地
    char selectedDayChar;// 获取用户输入的字符来选择要查询的日期
   
    // 获取当前日期和时间
    time_t current_time;
    struct tm* time_info;
    time(&current_time);
    time_info = localtime(&current_time);

    // 打印今天的日期
 /*   printf("\n1.%04d-%02d-%02d\t",
        time_info->tm_year + 1900, time_info->tm_mon + 1, time_info->tm_mday);*/

    // 打印未来七天的日期
    for (int i = 1; i < 8; i++) {
        // 增加一天的时间
        current_time += 24 * 60 * 60; // 60秒 * 60分钟 * 24小时
        time_info = localtime(&current_time);

        // 打印未来日期
        printf("%d.%04d-%02d-%02d\n", i,
            time_info->tm_year + 1900, time_info->tm_mon + 1, time_info->tm_mday);
    }





    printf("请选择要查询的日期 (1-7): ");
    selectedDayChar = _getch();  // 使用 _getch 获取用户输入的字符
    printf("%c", selectedDayChar);
    delay(100);
    while (selectedDayChar != '1' && selectedDayChar != '2' && selectedDayChar != '3' && selectedDayChar != '4' && selectedDayChar != '5' && selectedDayChar != '6' && selectedDayChar != '7' )
    {
        printf("\n请根据提示，输入'1'或'2'或'3'或'4'或'5'或'6'或'7'：");
        selectedDayChar = getch();
        printf("%c", selectedDayChar);
        delay(100);
    }
    selectedDay = (selectedDayChar - '0' - 1);  // 将字符转换为整数
    printf("\n\n请选择要查询的时间段:\n"); // 获取用户输入的字符来选择要查询的时间段
    printf("a. 6:00-7:00       b. 7:00-8:00       c. 8:00-9:00          d. 9:00-10:00\n");
    printf("e. 10:00-11:00     f. 11:00-12:00     g. 12:00-13:00        h. 13:00-14:00\n");
    printf("i. 14:00-15:00     j. 15:00-16:00     k. 16:00-17:00        l. 17:00-18:00\n");
    printf("m. 18:00-19:00     n. 19:00-20:00     o. 20；00-21：00      p. 21：00-22：00\n");
    printf("\n请输入您的选项（按照您的需求输入图表上方图表中的'a'-'p',注意必须输入小写字母):");
    key = getch();
    printf("%c",key);
    delay(100);
    while ( key != 'a' && key != 'b' && key != 'c' && key != 'd' && key != 'e' && key != 'f' && key != 'g' && key != 'h' && key != 'i'&& key != 'j' && key != 'k' && key != 'l' && key != 'm' && key != 'n' && key != 'o' && key != 'p' )
    {
        printf("\n请根据提示，输入图表上方图表中的'a'-'p',注意必须输入小写字母：");
        key = getch();
        printf("%c", key);
        delay(300);
    }
    selectedTimeSlot = key - 'a';
    system("cls");
    printf("\n在该时间段可预约的场地有：\n");
    for (int i = 0; i < 3; i++) // 循环遍历所有场馆和场地
    {
        for (int j = 0; j < halls[i].NumOfCourt; j++)
        {
            Court court = halls[i].courts[j];
            if (court.time[selectedDay][selectedTimeSlot] == 0 && court.maxPerson > 0) // 检查所选日期和时间段的预约情况
            {
                availableCourtsFound = true; // 如果找到符合条件的场地，将标志变量设置为true
                printf("场地ID: %s\n", court.courtId); // 输出符合条件的场地信息
                printf("所属场馆名称: %s\n", halls[i].name);
                printf("场馆所属区域: %s\n", halls[i].hallRegion);
                printf("场馆运动类型: %s\n", halls[i].sportType);
                printf("准入最小年龄限制: %d\n", halls[i].minAge);
                printf("准入最大年龄限制: %d\n", halls[i].maxAge);
                printf("每小时租金: %d\n", court.rentRerHour);
                printf("\n");
            }
        }
    }
    if (!availableCourtsFound)  // 检查标志变量，如果没有符合条件的场地，则输出相应信息
    {
        printf("无符合条件的场地\n");
    }
}


