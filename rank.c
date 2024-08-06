#include<stdio.h>
#include"rank.h"
#include"delay.h"
#include"Administrator.h"

const char* hallNames[] = { "球类场馆","游泳场馆","室外场馆" };// 字符串数组包含场馆名称


void administrator_menu_rank(void)//管理员统计主菜单界面
{
    system("cls");
    readFromFile();  //读取场地信息
    printf(" __________________________________________________\n");
    printf(" ________________体育馆预定及管理系统______________\n");
    printf(" __________________________________________管理员版\n");
    printf("\t\t 请选择您的需求\t\t\t\n");
    printf(" __________________________________________________\n");
    printf("|                                                  |\n");
    printf("|    1.查询全部订单                                |\n");
    printf("|                                                  |\n");
    printf("|    2.场馆预定量统计                              |\n");
    printf("|                                                  |\n");
    printf("|    3.场地预定量统计                              |\n");
    printf("|                                                  |\n");
    printf("|    4.场地营业额统计                              |\n");
    printf("|                                                  |\n");
    printf("|    5.性别统计                                    |\n");
    printf("|                                                  |\n");
    printf("|    6.年龄统计                                    |\n");
    printf("|                                                  |\n");
    printf("|    7.场地租金统计                                |\n");
    printf("|                                                  |\n");
    printf("|    8.热门预定时间统计                            |\n");
    printf("|                                                  |\n");
    printf("|    9.场地使用率统计                              |\n");
    printf("|                                                  |\n");
    printf("|    x.返回上一级界面                              |\n");
    printf("|                                                  |\n");
    printf("|__________________________________________________|\n");
    administrator_choose_rank();
}

void administrator_choose_rank(void)//管理员统计选择系统
{
    char flag;
    printf("请输入您的选项：");
    flag = getch();
    printf("%c", flag);
    delay(100);
    while (flag != '1' && flag != '2' && flag != '3' && flag != '4' && flag != '5' && flag != '6' && flag != '7' && flag != '8' && flag != '9' && flag != 'x' && flag != 'X')
    {
        printf("\n请根据提示，输入'1'或'2'或'3'或'4'或'5'或'6'或'7'或'8'或'9'或'x'：");
        flag = getch();
        printf("%c", flag);
        delay(100);
    }
    printf("\n");
    printf("\n");
    switch (flag)
    {
    case '1':
        system("cls");
        parseOrderFile("orderInformation.txt");//打印全部订单
        administrator_menu_rank_return();
        break;
    case '2':
        system("cls");
        countVenueBookings("orderInformation.txt");//根据场地预定量排序
        administrator_menu_rank_return();
        break;
    case '3':
        system("cls");
        countFieldBookings("orderInformation.txt");//根据场地预定量排序
        administrator_menu_rank_return();
        break;
    case '4':
        system("cls");
        countVenueBusinesVolume("orderInformation.txt");//根据场地营业额排序
        administrator_menu_rank_return();
        break;
    case '5':
        system("cls");
        calculateGenderStatistics();//性别统计 
        administrator_menu_rank_return();
    case '6':
        system("cls");
        calculateAgeDistribution();//年龄统计
        administrator_menu_rank_return();
    case '7':
        system("cls");
        sortByRent();//根据场地租金排序
        administrator_menu_rank_return();
    case '8':
        system("cls");
        calculateHotTime();//热门预定时间
        administrator_menu_rank_return();
    case '9':
        system("cls");
        calculatingUtilization();//根据场地时间段的使用率
        administrator_menu_rank_return();
    case 'x':system("cls");
        printf("正在返回······");
        delay(500);
        Scheduled_anagement();
        break;
    case 'X':system("cls");
        printf("正在返回······");
        delay(500);
        Scheduled_anagement();
        break;
    default:
        break;
    }
}

void administrator_menu_rank_return(void)//返回管理员统计主菜单界面
{
    printf("\n按任意键返回上一级界面：");
    char a;
    a = getch();
    printf("%c", a);
    delay(100);
    if (a != NULL)
    {
        printf("\n正在返回······");
        delay(400);
        administrator_menu_rank();
    }
}

int parseOrderFile(const char* filename)// 读取并打印全部订单信息
{
    FILE* file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("无法打开文件");
        return 1;
    }
    char line[MAX_LINE_LENGTH];
    struct Order order;
    while (fgets(line, sizeof(line), file))
    {
        line[strcspn(line, "\n")] = '\0';// 去除行末的换行符
        if (strlen(line) == 0) // 如果是空行，继续下一行
        {
            continue;
        }
        if (sscanf(line, "%[^,],%[^,],%d,%d,%[^,],%[^_]_%[^_]_%[^_]_%[^ ]", // 使用sscanf解析订单信息，包括年龄和性别
            order.username, order.fullName, &order.age, &order.gender, order.orderNumber, order.venue, order.venueNumber, order.date, order.time) == 9) // 打印订单信息
        {
            printf("用户名: %s\n", order.username);
            printf("用户姓名: %s\n", order.fullName);
            printf("年龄: %d\n", order.age);
            printf("性别: %d\n", order.gender);
            printf("订单号: %s\n", order.orderNumber);
            printf("场馆号: %s\n", order.venue);
            printf("场地号: %s\n", order.venueNumber);
            printf("预定日期: %s\n", order.date);
            printf("预定时间: %s\n", order.time);
            printf("\n");

        }
        else
        {
            printf("无法解析订单信息: %s\n", line);
        }
    }
    fclose(file);
    return 0;
}

void countVenueBookings(const char* filename) // 函数用于统计每个场馆的预定总量和排序
{
    FILE* file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("无法打开文件");
        return;
    }
    char line[MAX_LINE_LENGTH];
    int hall1Bookings = 0;
    int hall2Bookings = 0;
    int hall3Bookings = 0;


    while (fgets(line, sizeof(line), file))  // 继续添加更多 hallXBookings 变量，以满足你的场馆数量
    {
        line[strcspn(line, "\n")] = '\0';
        if (strlen(line) == 0)
        {
            continue;
        }
        struct Order order;
        if (sscanf(line, "%[^,],%[^,],%d,%d,%[^,],%[^_]_%[^_]_%[^_]_%[^ ]",
            order.username, order.fullName, &order.age, &order.gender, order.orderNumber, order.venue, order.venueNumber, order.date, order.time) == 9) // 根据订单中的场馆名字增加对应场馆的预定总量
        {
            if (strcmp(order.venue, "Hall1") == 0)
            {
                hall1Bookings++;
            }
            else if (strcmp(order.venue, "Hall2") == 0)
            {
                hall2Bookings++;
            }
            else if (strcmp(order.venue, "Hall3") == 0)
            {
                hall3Bookings++;
            }
        }
    }
    fclose(file);
    printf("球类场馆 预定总量: %d\n", hall1Bookings);// 打印每个场馆的预定总量
    printf("游泳场馆 预定总量: %d\n", hall2Bookings);
    printf("室外场馆 预定总量: %d\n", hall3Bookings);
    char choice;
    printf("\n请选择排序方式：\n");
    printf("1. 从高到低排序\n");
    printf("2. 从低到高排序\n");
    printf("请选择（1或2）： ");
    choice = getch();
    printf("%c",choice);
    delay(100);
   while(choice != '1' && choice != '2')
    {
        printf("\n请根据需求，重新输入您的选项：");
        choice = getch();
        printf("%c",choice);
        delay(100);
    }
    if (choice == '1') // 从高到低排序（冒泡排序）
    {
        int sortedBookings[] = { hall1Bookings, hall2Bookings, hall3Bookings };
        int n = sizeof(sortedBookings) / sizeof(sortedBookings[0]);

        for (int i = 0; i < n - 1; i++)
        {
            for (int j = 0; j < n - i - 1; j++)
            {
                if (sortedBookings[j] < sortedBookings[j + 1])   // 交换预定总量
                {
                    int temp = sortedBookings[j];
                    sortedBookings[j] = sortedBookings[j + 1];
                    sortedBookings[j + 1] = temp;
                }
            }
        }
        printf("\n\n从高到低排序后的场馆预定总量：\n"); // 打印排序后的场馆预定总量
        for (int i = 0; i < n; i++)
        {
            if (i == 0)
            {
                printf("球类场馆 预定总量: %d\n", sortedBookings[i]);
            }
            else if (i == 1)
            {
                printf("游泳场馆 预定总量: %d\n", sortedBookings[i]);
            }
            else if (i == 2)
            {
                printf("室外场馆 预定总量: %d\n", sortedBookings[i]);
            }
        }
        int mostPopularIndex = 0;// 找到最受欢迎的场馆
        for (int i = 1; i < n; i++)
        {
            if (sortedBookings[i] > sortedBookings[mostPopularIndex])
            {
                mostPopularIndex = i;
            }
        }

        if (mostPopularIndex == 0)  // 显示最受欢迎的场馆
        {
            printf("\n最受欢迎的场馆是：球类场馆\n");
        }
        else if (mostPopularIndex == 1)
        {
            printf("\n最受欢迎的场馆是：游泳场馆\n");
        }
        else if (mostPopularIndex == 2)
        {
            printf("\n最受欢迎的场馆是：室外场馆\n");
        }
    }
    else if (choice == '2')// 从低到高排序（冒泡排序的反向排序）
    {
        int sortedBookings[] = { hall1Bookings, hall2Bookings, hall3Bookings };
        char* venueNames[] = { "球类场馆", "游泳场馆", "室外场馆" }; // 对应的场馆名称
        int n = sizeof(sortedBookings) / sizeof(sortedBookings[0]);

        for (int i = 0; i < n - 1; i++)
        {
            for (int j = 0; j < n - i - 1; j++)
            {
                if (sortedBookings[j] > sortedBookings[j + 1])// 交换预定总量
                {
                    int temp = sortedBookings[j];
                    sortedBookings[j] = sortedBookings[j + 1];
                    sortedBookings[j + 1] = temp;
                    char* tempName = venueNames[j];// 同时交换对应的场馆名称
                    venueNames[j] = venueNames[j + 1];
                    venueNames[j + 1] = tempName;
                }
            }
        }
        printf("\n\n从低到高排序后的场馆预定总量：\n");
        for (int i = 0; i < n; i++) // 打印排序后的场馆预定总量
        {
            printf("%s 预定总量: %d\n", venueNames[i], sortedBookings[i]);
        }
        int mostPopularIndex = 0;// 找到最受欢迎的场馆
        for (int i = 1; i < n; i++)
        {
            if (sortedBookings[i] > sortedBookings[mostPopularIndex])
            {
                mostPopularIndex = i;
            }
        }

        // 显示最受欢迎的场馆
        printf("\n最受欢迎的场馆是：%s\n", venueNames[mostPopularIndex]);
    }
}

void countFieldBookings(const char* filename) // 函数用于统计每个场地的预定总量和排序
{
    FILE* file = fopen(filename, "r");
    if (file == NULL) 
    {
        perror("无法打开文件");
        return;
    }
    char line[MAX_LINE_LENGTH];
    int hall1Field1Bookings = 0;
    int hall1Field2Bookings = 0;
    int hall2Field1Bookings = 0;
    int hall2Field2Bookings = 0;
    int hall3Field1Bookings = 0;
    int hall3Field2Bookings = 0;

    while (fgets(line, sizeof(line), file)) 
    {
        line[strcspn(line, "\n")] = '\0';
        if (strlen(line) == 0)
        {
            continue;
        }
        struct Order order;
        if (sscanf(line, "%[^,],%[^,],%d,%d,%[^,],%[^_]_%[^_]_%[^_]_%[^ ]",// 根据订单中的场馆和场地名字增加对应的预定总量
            order.username, order.fullName, &order.age, &order.gender, order.orderNumber, order.venue, order.venueNumber, order.date, order.time) == 9)
        {
            if (strcmp(order.venue, "Hall1") == 0)
            {
                if (strcmp(order.venueNumber, "1") == 0) 
                {
                    hall1Field1Bookings++;
                }
                else if (strcmp(order.venueNumber, "2") == 0)
                {
                    hall1Field2Bookings++;
                }
            }
            else if (strcmp(order.venue, "Hall2") == 0) 
            {
                if (strcmp(order.venueNumber, "1") == 0)
                {
                    hall2Field1Bookings++;
                }
                else if (strcmp(order.venueNumber, "2") == 0)
                {
                    hall2Field2Bookings++;
                }
            }
            else if (strcmp(order.venue, "Hall3") == 0) 
            {
                if (strcmp(order.venueNumber, "1") == 0)
                {
                    hall3Field1Bookings++;
                }
                else if (strcmp(order.venueNumber, "2") == 0)
                {
                    hall3Field2Bookings++;
                }
            }
        }
    }
    fclose(file);
    // 打印每个场馆和场地的预定总量
    printf("球类场馆 场地1 预定总量: %d\n", hall1Field1Bookings);
    printf("球类场馆 场地2 预定总量: %d\n", hall1Field2Bookings);
    printf("游泳场馆 场地1 预定总量: %d\n", hall2Field1Bookings);
    printf("游泳场馆 场地2 预定总量: %d\n", hall2Field2Bookings);
    printf("室外场馆 场地1 预定总量: %d\n", hall3Field1Bookings);
    printf("室外场馆 场地2 预定总量: %d\n", hall3Field2Bookings);
    char choice;
    printf("\n请选择排序方式：\n");
    printf("1. 从高到低排序\n");
    printf("2. 从低到高排序\n");
    printf("请选择（1或2）： ");
    choice = getch();
    printf("%c", choice);
    delay(100);
    while (choice != '1' && choice != '2')
    {
        printf("\n请根据需求，重新输入您的选项：");
        choice = getch();
        printf("%c", choice);
        delay(100);
    }
    // 根据管理员的选择排序并打印
    if (choice == '1')// 冒泡排序，从高到低
    {
        int bookings[] =
        {
            hall1Field1Bookings, hall1Field2Bookings,
            hall2Field1Bookings, hall2Field2Bookings,
            hall3Field1Bookings, hall3Field2Bookings
        };
        int numBookings = sizeof(bookings) / sizeof(bookings[0]);

        for (int i = 0; i < numBookings - 1; i++) 
        {
            for (int j = 0; j < numBookings - i - 1; j++) 
            {
                if (bookings[j] < bookings[j + 1]) 
                {
                    int temp = bookings[j];// 交换两个元素
                    bookings[j] = bookings[j + 1];
                    bookings[j + 1] = temp;
                }
            }
        }

        // 打印排序后的结果
        printf("\n\n从高到低排序后的预定总量：\n");
        printf("球类场馆 场地1: %d\n", bookings[0]);
        printf("球类场馆 场地2: %d\n", bookings[1]);
        printf("游泳场馆 场地1: %d\n", bookings[2]);
        printf("游泳场馆 场地2: %d\n", bookings[3]);
        printf("室外场馆 场地1: %d\n", bookings[4]);
        printf("室外场馆 场地2: %d\n", bookings[5]);

        // 找到最受欢迎的场地
        int mostPopularBookings = bookings[0];
        printf("\n最受欢迎的场地：\n");
        if (hall1Field1Bookings == mostPopularBookings)
        {
            printf("球类场馆 场地1\n");
        }
        if (hall1Field2Bookings == mostPopularBookings) 
        {
            printf("球类场馆 场地2\n");
        }
        if (hall2Field1Bookings == mostPopularBookings) 
        {
            printf("游泳场馆 场地1\n");
        }
        if (hall2Field2Bookings == mostPopularBookings)
        {
            printf("游泳场馆 场地2\n");
        }
        if (hall3Field1Bookings == mostPopularBookings) 
        {
            printf("室外场馆 场地1\n");
        }
        if (hall3Field2Bookings == mostPopularBookings)
        {
            printf("室外场馆 场地2\n");
        }
    }
    else if (choice == '2') // 冒泡排序，从低到高
    {
        int bookings[] = 
        {
            hall1Field1Bookings, hall1Field2Bookings,
            hall2Field1Bookings, hall2Field2Bookings,
            hall3Field1Bookings, hall3Field2Bookings
        };
        int numBookings = sizeof(bookings) / sizeof(bookings[0]);
        char* hallNames[] = 
        {  
            "球类场馆 场地1", "球类场馆 场地2",
            "游泳场馆 场地1", "游泳场馆 场地2",
            "室外场馆 场地1", "室外场馆 场地2"
        };

        for (int i = 0; i < numBookings - 1; i++) 
        {
            for (int j = 0; j < numBookings - i - 1; j++) 
            {
                if (bookings[j] > bookings[j + 1]) 
                {
                    // 交换两个元素
                    int tempBooking = bookings[j];
                    bookings[j] = bookings[j + 1];
                    bookings[j + 1] = tempBooking;

                    // 交换对应的名称
                    char* tempName = hallNames[j];
                    hallNames[j] = hallNames[j + 1];
                    hallNames[j + 1] = tempName;
                }
            }
        }

        // 打印排序后的结果
        printf("\n\n从低到高排序后的预定总量：\n");
        for (int i = 0; i < numBookings; i++)
        {
            printf("%s: %d\n", hallNames[i], bookings[i]);
        }

        // 找到最受欢迎的场地
        int mostPopularBookings = bookings[numBookings - 1];
        printf("\n最受欢迎的场地：\n");
        if (hall1Field1Bookings == mostPopularBookings) 
        {
            printf("球类场馆 场地1\n");
        }
        if (hall1Field2Bookings == mostPopularBookings) 
        {
            printf("球类场馆 场地2\n");
        }
        if (hall2Field1Bookings == mostPopularBookings) 
        {
            printf("游泳场馆 场地1\n");
        }
        if (hall2Field2Bookings == mostPopularBookings)
        {
            printf("游泳场馆 场地2\n");
        }
        if (hall3Field1Bookings == mostPopularBookings) 
        {
            printf("室外场馆 场地1\n");
        }
        if (hall3Field2Bookings == mostPopularBookings) 
        {
            printf("室外场馆 场地2\n");
        }
    }
}

void countVenueBusinesVolume(const char* filename)//统计场馆的营业额+排序
{
    FILE* file = fopen(filename, "r");
    if (file == NULL) 
    {
        perror("无法打开文件");
        return;
    }
    char line[MAX_LINE_LENGTH];
    int hall1Field1Bookings = 0;
    int hall1Field2Bookings = 0;
    int hall2Field1Bookings = 0;
    int hall2Field2Bookings = 0;
    int hall3Field1Bookings = 0;
    int hall3Field2Bookings = 0;
    while (fgets(line, sizeof(line), file)) 
    {
        line[strcspn(line, "\n")] = '\0';
        if (strlen(line) == 0)
        {
            continue;
        }
        struct Order order;
        if (sscanf(line, "%[^,],%[^,],%d,%d,%[^,],%[^_]_%[^_]_%[^_]_%[^ ]",// 根据订单中的场馆和场地名字增加对应的预定总量
            order.username, order.fullName, &order.age, &order.gender, order.orderNumber, order.venue, order.venueNumber, order.date, order.time) == 9)
        {
            if (strcmp(order.venue, "Hall1") == 0) 
            {
                if (strcmp(order.venueNumber, "1") == 0)
                {
                    hall1Field1Bookings++;
                }
                else if (strcmp(order.venueNumber, "2") == 0) 
                {
                    hall1Field2Bookings++;
                }
            }
            else if (strcmp(order.venue, "Hall2") == 0) 
            {
                if (strcmp(order.venueNumber, "1") == 0) 
                {
                    hall2Field1Bookings++;
                }
                else if (strcmp(order.venueNumber, "2") == 0) 
                {
                    hall2Field2Bookings++;
                }
            }
            else if (strcmp(order.venue, "Hall3") == 0)
            {
                if (strcmp(order.venueNumber, "1") == 0) 
                {
                    hall3Field1Bookings++;
                }
                else if (strcmp(order.venueNumber, "2") == 0) 
                {
                    hall3Field2Bookings++;
                }
            }
        }
    }

    fclose(file);

    // 打印每个场馆和场地的预定总量
    float businessVolume1_1 = halls[0].courts[0].rentRerHour * hall1Field1Bookings;
    float businessVolume1_2 = halls[0].courts[1].rentRerHour * hall1Field2Bookings;
    float businessVolume2_1 = halls[1].courts[0].rentRerHour * hall2Field1Bookings;
    float businessVolume2_2 = halls[1].courts[1].rentRerHour * hall2Field2Bookings;
    float businessVolume3_1 = halls[2].courts[0].rentRerHour * hall3Field1Bookings;
    float businessVolume3_2 = halls[2].courts[1].rentRerHour * hall3Field2Bookings;
    printf("%s 场地1 营业额: %.2f\n", hallNames[0], businessVolume1_1);
    printf("%s 场地2 营业额: %.2f\n", hallNames[0], businessVolume1_2);
    printf("%s 场地1 营业额: %.2f\n", hallNames[1], businessVolume2_1);
    printf("%s 场地2 营业额: %.2f\n", hallNames[1], businessVolume2_2);
    printf("%s 场地1 营业额: %.2f\n", hallNames[2], businessVolume3_1);
    printf("%s 场地2 营业额: %.2f\n", hallNames[2], businessVolume3_2);

    // 根据管理员的选择排序并打印
    char choice;
    printf("\n请选择排序方式（1.从高到低，2.从低到高）：");
    choice = getch();
    printf("%c", choice);
    delay(100);
    while (choice != '1' && choice != '2')
    {
        printf("\n请根据需求，重新输入您的选项：");
        choice = getch();
        printf("%c", choice);
        delay(100);
    }
    if (choice == '1')
    {
        // 从高到低排序
        float businessVolumes[] = 
        {
            businessVolume1_1, businessVolume1_2,
            businessVolume2_1, businessVolume2_2,
            businessVolume3_1, businessVolume3_2
        };
        char* hallNames[] = 
        {
            "球类场馆 场地1", "球类场馆 场地2",
            "游泳场馆 场地1", "游泳场馆 场地2",
            "室外场馆 场地1", "室外场馆 场地2"
        };
        int numHalls = sizeof(hallNames) / sizeof(hallNames[0]);

        for (int i = 0; i < numHalls - 1; i++) 
        {
            for (int j = 0; j < numHalls - i - 1; j++)
            {
                if (businessVolumes[j] < businessVolumes[j + 1]) 
                {
                    // 交换两个元素
                    float tempVolume = businessVolumes[j];
                    businessVolumes[j] = businessVolumes[j + 1];
                    businessVolumes[j + 1] = tempVolume;
                    // 交换对应的名称
                    char* tempName = hallNames[j];
                    hallNames[j] = hallNames[j + 1];
                    hallNames[j + 1] = tempName;
                }
            }
        }

        // 打印排序后的结果
        printf("\n\n从高到低排序后的营业额：\n");
        for (int i = 0; i < numHalls; i++) {
            printf("%s 营业额: %.2f\n", hallNames[i], businessVolumes[i]);
        }

        // 找到营业额最高的场地
        float mostProfitableVolume = businessVolumes[0];
        printf("\n营业额最高的场地：\n");
        for (int i = 0; i < numHalls; i++) {
            if (businessVolumes[i] == mostProfitableVolume) {
                printf("%s\n", hallNames[i]);
            }
        }
    }
    else if (choice == '2') {
        // 从低到高排序
        float businessVolumes[] = {
            businessVolume1_1, businessVolume1_2,
            businessVolume2_1, businessVolume2_2,
            businessVolume3_1, businessVolume3_2
        };
        char* hallNames[] = {                                                                       //重定义
            "球类场馆 场地1", "球类场馆 场地2",
            "游泳场馆 场地1", "游泳场馆 场地2",
            "室外场馆 场地1", "室外场馆 场地2"
        };
        int numHalls = sizeof(hallNames) / sizeof(hallNames[0]);

        for (int i = 0; i < numHalls - 1; i++) {
            for (int j = 0; j < numHalls - i - 1; j++) {
                if (businessVolumes[j] > businessVolumes[j + 1]) {
                    // 交换两个元素
                    float tempVolume = businessVolumes[j];
                    businessVolumes[j] = businessVolumes[j + 1];
                    businessVolumes[j + 1] = tempVolume;

                    // 交换对应的名称
                    char* tempName = hallNames[j];
                    hallNames[j] = hallNames[j + 1];
                    hallNames[j + 1] = tempName;
                }
            }
        }

        // 打印排序后的结果
        printf("\n\n从低到高排序后的营业额：\n");
        for (int i = 0; i < numHalls; i++) {
            printf("%s 营业额: %.2f\n", hallNames[i], businessVolumes[i]);
        }

        // 找到营业额最高的场地
        float mostProfitableVolume = businessVolumes[numHalls - 1];
        printf("\n营业额最高的场地：\n");
        for (int i = 0; i < numHalls; i++) {
            if (businessVolumes[i] == mostProfitableVolume) {
                printf("%s\n", hallNames[i]);
            }
        }
    }
}

void calculateGenderStatistics() // 统计每个场地的男女数量以及每个场馆的男女数量，并统计最喜欢的场馆
{
    typedef struct 
    {
        int maleCount;   // 男性数量
        int femaleCount; // 女性数量
    } VenueGenderStats;
    FILE* file = fopen("orderInformation.txt", "r");
    if (file == NULL) 
    {
        perror("无法打开文件");
        return;
    }

    char line[MAX_LINE_LENGTH];
    struct Order order;

    // 声明一个数组来存储每个场地的性别统计信息
    GenderStats venueGenderStatistics[MAX_VENUES][MAX_FIELDS] = { 0 };

    // 声明一个数组来存储每个场馆的性别统计信息
    VenueGenderStats venueStats[MAX_VENUES] = { 0 };

    // 声明变量来跟踪男生和女生最喜欢的场馆
    int favoriteMaleVenue = -1;
    int favoriteFemaleVenue = -1;
    int maxMaleCount = -1;
    int maxFemaleCount = -1;

    while (fgets(line, sizeof(line), file)) 
    {
        // 去除行末的换行符
        line[strcspn(line, "\n")] = '\0';

        // 如果是空行或达到文件末尾，继续下一行
        if (strlen(line) == 0) 
        {
            continue;
        }

        // 使用sscanf解析订单信息，包括年龄和性别
        if (sscanf(line, "%[^,],%[^,],%d,%d,%[^,],%[^_]_%[^_]_%[^_]_%[^ ]",
            order.username, order.fullName, &order.age, &order.gender, order.orderNumber, order.venue, order.venueNumber, order.date, order.time) == 9) {
            // 统计性别
            int hallNum = order.venue[4] - '0' - 1; // 场馆号在订单信息的第5个字符
            int courtNum = order.venueNumber[0] - '0' - 1; // 场地号在订单信息的第1个字符

            if (hallNum >= 0 && hallNum < MAX_VENUES && courtNum >= 0 && courtNum < MAX_FIELDS) {
                if (order.gender == 0) 
                {
                    venueGenderStatistics[hallNum][courtNum].femaleCount++;
                }
                else if (order.gender == 1)
                {
                    venueGenderStatistics[hallNum][courtNum].maleCount++;
                }
                venueStats[hallNum].femaleCount += (order.gender == 0 ? 1 : 0);
                venueStats[hallNum].maleCount += (order.gender == 1 ? 1 : 0);
            }
        }
    }

    fclose(file);

    // 打印每个场地的男女数量
    printf("场地男女统计:\n");
    for (int i = 0; i < MAX_VENUES; i++)
    {
        for (int j = 0; j < MAX_FIELDS; j++)
        {
            printf("%s 场地%d: 男性%d人, 女性%d人\n", hallNames[i], j + 1, venueGenderStatistics[i][j].maleCount, venueGenderStatistics[i][j].femaleCount);
        }
    }

    // 打印每个场馆的男女人数
    printf("\n每个场馆的男女人数:\n");
    for (int i = 0; i < MAX_VENUES; i++) 
    {
        printf("%s: 男性%d人, 女性%d人\n", hallNames[i], venueStats[i].maleCount, venueStats[i].femaleCount);

        // 更新最喜欢的场馆
        if (venueStats[i].maleCount > maxMaleCount) 
        {
            maxMaleCount = venueStats[i].maleCount;
            favoriteMaleVenue = i;
        }
        if (venueStats[i].femaleCount > maxFemaleCount)
        {
            maxFemaleCount = venueStats[i].femaleCount;
            favoriteFemaleVenue = i;
        }
    }

    // 打印最喜欢的场馆
    if (favoriteMaleVenue != -1) {
        printf("\n男生最喜欢的场馆: %s (男性%d人)\n", hallNames[favoriteMaleVenue], maxMaleCount);
    }
    if (favoriteFemaleVenue != -1) {
        printf("女生最喜欢的场馆: %s (女性%d人)\n", hallNames[favoriteMaleVenue], maxFemaleCount);
    }
}

void calculateAgeDistribution() // 统计每个场地的年龄分布
{
    // 声明一个新的结构体来存储不同场地的年龄分布
    typedef struct 
    {
        int age0to15Count;   // 年龄0-15的人数
        int age16to40Count;  // 年龄16-40的人数
        int age41to150Count; // 年龄41-150的人数
    } AgeDistribution;

    FILE* file = fopen("orderInformation.txt", "r");
    if (file == NULL) 
    {
        perror("无法打开文件");
        return;
    }

    char line[MAX_LINE_LENGTH];
    struct Order order;

    // 声明一个数组来存储每个场地的年龄分布统计信息
    AgeDistribution venueAgeDistribution[MAX_VENUES][MAX_FIELDS] = { 0 };

    while (fgets(line, sizeof(line), file)) 
    {
        // 去除行末的换行符
        line[strcspn(line, "\n")] = '\0';

        // 如果是空行或达到文件末尾，继续下一行
        if (strlen(line) == 0) 
        {
            continue;
        }

        // 使用sscanf解析订单信息，包括年龄和性别
        if (sscanf(line, "%[^,],%[^,],%d,%d,%[^,],%[^_]_%[^_]_%[^_]_%[^ ]",
            order.username, order.fullName, &order.age, &order.gender, order.orderNumber, order.venue, order.venueNumber, order.date, order.time) == 9) {
            // 统计年龄分布
            int hallNum = order.venue[4] - '0' - 1; // 场馆号在订单信息的第5个字符
            int courtNum = order.venueNumber[0] - '0' - 1; // 场地号在订单信息的第1个字符

            if (hallNum >= 0 && hallNum < MAX_VENUES && courtNum >= 0 && courtNum < MAX_FIELDS) {
                if (order.age >= 0 && order.age <= 15) 
                {
                    venueAgeDistribution[hallNum][courtNum].age0to15Count++;
                }
                else if (order.age >= 16 && order.age <= 40)
                {
                    venueAgeDistribution[hallNum][courtNum].age16to40Count++;
                }
                else if (order.age >= 41 && order.age <= 150)
                {
                    venueAgeDistribution[hallNum][courtNum].age41to150Count++;
                }
            }
        }
    }

    fclose(file);

    // 打印每个场地的年龄分布
    printf("场地年龄分布统计:\n");
    for (int i = 0; i < MAX_VENUES; i++) {
        for (int j = 0; j < MAX_FIELDS; j++) {
            printf("%s 场地%d: 年龄0-15:%d人, 年龄16-40:%d人, 年龄41以上:%d人\n",
                hallNames[i],
                j + 1,
                venueAgeDistribution[i][j].age0to15Count,
                venueAgeDistribution[i][j].age16to40Count,
                venueAgeDistribution[i][j].age41to150Count);
        }
    }
}

void sortByRent() // 读取租金并排序所有场地，同时打印排序后的场地信息
{
    int descending; // 标志是否降序排列，1表示降序，0表示升序
    char choice;
    printf("请选择排序方式（1表示升序，0表示降序）: ");
    choice = getch();
    printf("%c", choice);
    delay(100);
    while (choice != '1' && choice != '0')
    {
        printf("\n请根据需求，重新输入您的选项：");
        choice = getch();
        printf("%c", choice);
        delay(100);
    }
    descending = choice - '0';
    FILE* file = fopen("site.txt", "r");
    if (file == NULL) 
    {
        printf("无法打开文件\n");
        return;
    }
    Court allCourts[MAX_VENUES * MAX_FIELDS];
    int allCourtsCount = 0;
    int hallNums[MAX_VENUES * MAX_FIELDS]; // 用于存储场地对应的场馆编号

    for (int i = 0; i < 3; i++) 
    {
        fscanf(file, "%d", &halls[i].hallNum);
        fscanf(file, "%d", &halls[i].NumOfCourt);
        fscanf(file, "%s", halls[i].name);
        fscanf(file, "%s", halls[i].hallRegion);
        fscanf(file, "%s", halls[i].sportType);
        fscanf(file, "%d", &halls[i].minAge);
        fscanf(file, "%d", &halls[i].maxAge);
        for (int j = 0; j < halls[i].NumOfCourt; j++) 
        {
            fscanf(file, "%d", &halls[i].courts[j].courtNum);
            fscanf(file, "%d", &halls[i].courts[j].rentRerHour);
            fscanf(file, "%s", halls[i].courts[j].courtId);
            for (int d = 0; d < 7; d++) 
            {
                for (int k = 0; k < 16; k++) 
                {
                    fscanf(file, "%d", &halls[i].courts[j].time[d][k]);
                }
            }
            fscanf(file, "%d", &halls[i].courts[j].maxPerson);

            // 将场地添加到合并后的数组中，并记录对应的场馆编号
            allCourts[allCourtsCount] = halls[i].courts[j];
            hallNums[allCourtsCount] = halls[i].hallNum;
            allCourtsCount++;
        }
    }

    // 使用冒泡排序按租金排序所有场地
    for (int i = 0; i < allCourtsCount - 1; i++) 
    {
        for (int j = 0; j < allCourtsCount - i - 1; j++) 
        {
            int compareValue = (descending ? allCourts[j].rentRerHour > allCourts[j + 1].rentRerHour : allCourts[j].rentRerHour < allCourts[j + 1].rentRerHour);
            if (compareValue) 
            {
                // 交换场地
                Court tempCourt = allCourts[j];
                allCourts[j] = allCourts[j + 1];
                allCourts[j + 1] = tempCourt;
                // 交换场馆编号
                int tempHallNum = hallNums[j];
                hallNums[j] = hallNums[j + 1];
                hallNums[j + 1] = tempHallNum;
            }
        }
    }

    fclose(file);


    // 打印排序后的场地信息，包括场馆名称和场地编号
    printf("\n\n按租金%s排序后的所有场地信息:\n", (descending ? "升序" : "降序"));
    for (int i = 0; i < allCourtsCount; i++)
    {
        int hallIndex = hallNums[i] - 1;
        printf("%s 场地%d 租金每小时: %d\n", hallNames[hallIndex], allCourts[i].courtNum, allCourts[i].rentRerHour);
    }
}

int compareUsage(const void* a, const void* b)//比较用户年龄
{
    return (*(int*)b - *(int*)a);
}

void calculateHotTime() // 统计并打印每个场地中每个时间段的预约情况
{
    FILE* file = fopen("site.txt", "r");
    if (file == NULL)
    {
        printf("无法打开文件\n");
        return;
    }

    // 初始化场地租用量统计数组
    int courtUsage[3][2][16] = { 0 }; // [场馆][场地][时间段]
    const char* timePeriods[] = 
    {
        "6:00-6:59", "7:00-7:59", "8:00-8:59", "9:00-9:59",
        "10:00-10:59", "11:00-11:59", "12:00-12:59", "13:00-13:59",
        "14:00-14:59", "15:00-15:59", "16:00-16:59", "17:00-17:59",
        "18:00-18:59", "19:00-19:59", "20:00-20:59", "21:00-21:59"
    };

    for (int i = 0; i < 3; i++)
    {
        int hallNum = halls[i].hallNum - 1;
        for (int j = 0; j < halls[i].NumOfCourt; j++)
        {
            int courtNum = halls[i].courts[j].courtNum - 1;
            for (int k = 0; k < 16; k++) 
            {
                int totalUsage = 0; // 当前时间段的总租用量
                for (int d = 0; d < 7; d++) 
                {
                    totalUsage += halls[i].courts[j].time[d][k];
                }
                // 累加租用量
                courtUsage[hallNum][courtNum][k] += totalUsage;
            }
        }
    }
    fclose(file);
    printf("1.球类场馆 2.游泳场馆 3.室外场馆");
    printf("\n请选择要查看的场馆编号:");

    int selectedHall;
    char choice,key;
    choice = getch();
    printf("%c", choice);
    delay(100);
    while (choice != '1' && choice != '2' && choice != '3')
    {
        printf("\n请根据需求，重新输入您的选项：");
        choice = getch();
        printf("%c", choice);
        delay(100);
    }
    selectedHall = choice - '0';
    printf("\n\n1.1场地 2.2场地");
    printf("\n请选择要查看的场地编号:");
    int selectedCourt;
    key = getch();
    printf("%c", key);
    delay(100);
    while (key != '1' && key != '2')
    {
        printf("\n请根据需求，重新输入您的选项：");
        key = getch();
        printf("%c", key);
        delay(100);
    }
    selectedCourt = key - '0';
    selectedHall--; // 将用户选择转换为数组索引
    selectedCourt--;
    printf("\n\n%s 场地%d 的场地利用率统计:\n", hallNames[selectedHall], selectedCourt + 1);
    // 创建一个副本数组用于排序，同时维护时间段名称的副本数组
    int sortedUsage[16];
    const char* sortedTimePeriods[16];
    for (int k = 0; k < 16; k++) 
    {
        sortedUsage[k] = courtUsage[selectedHall][selectedCourt][k];
        sortedTimePeriods[k] = timePeriods[k];
    }
    // 使用冒泡排序对副本数组进行排序，同时保持时间段名称的同步
    for (int i = 0; i < 16 - 1; i++) 
    {
        for (int j = 0; j < 16 - i - 1; j++) 
        {
            if (sortedUsage[j] < sortedUsage[j + 1]) 
            {
                // 交换租用量
                int tempUsage = sortedUsage[j];
                sortedUsage[j] = sortedUsage[j + 1];
                sortedUsage[j + 1] = tempUsage;
                // 交换时间段名称
                const char* tempTimePeriod = sortedTimePeriods[j];
                sortedTimePeriods[j] = sortedTimePeriods[j + 1];
                sortedTimePeriods[j + 1] = tempTimePeriod;
            }
        }
    }

    // 打印排序后的时间段租用量及最受欢迎时间段名称
    for (int k = 0; k < 16; k++) 
    {
        printf("%s: %d人\n", sortedTimePeriods[k], sortedUsage[k]);
    }

    // 找到最受欢迎的时间段
    int mostPopularTimeIndex = 0;
    printf("\n这个场地最受欢迎的时间段是：%s\n", sortedTimePeriods[mostPopularTimeIndex]);
}

void calculatingUtilization() //统计并打印每个场地中每个时间段的场地利用率

{
    FILE* file = fopen("site.txt", "r");
    if (file == NULL) {
        printf("无法打开文件\n");
        return;
    }

    // 初始化场地租用量统计数组
    int courtUsage[3][2][16] = { 0 }; // [场馆][场地][时间段]
    const char* timePeriods[] = 
    {
        "6:00-6:59", "7:00-7:59", "8:00-8:59", "9:00-9:59",
        "10:00-10:59", "11:00-11:59", "12:00-12:59", "13:00-13:59",
        "14:00-14:59", "15:00-15:59", "16:00-16:59", "17:00-17:59",
        "18:00-18:59", "19:00-19:59", "20:00-20:59", "21:00-21:59"
    };

    for (int i = 0; i < 3; i++)
    {
        int hallNum = halls[i].hallNum - 1;
        for (int j = 0; j < halls[i].NumOfCourt; j++) 
        {
            int courtNum = halls[i].courts[j].courtNum - 1;
            for (int k = 0; k < 16; k++) 
            {
                int totalUsage = 0; // 当前时间段的总租用量
                for (int d = 0; d < 7; d++) 
                {
                    totalUsage += halls[i].courts[j].time[d][k];
                }
                // 累加租用量
                courtUsage[hallNum][courtNum][k] += totalUsage;
            }
        }
    }

    fclose(file);

    printf("1.球类场馆 2.游泳场馆 3.室外场馆");
    printf("\n请选择要查看的场馆编号:");

    char choice,key;
    int selectedHall; 
    choice = getch();
    printf("%c", choice);
    delay(100);
    while (choice != '1' && choice != '2' && choice != '3')
    {
        printf("\n请根据需求，重新输入您的选项：");
        choice = getch();
        printf("%c", choice);
        delay(100);
    }
    selectedHall = choice - '0';
   
    printf("\n\n1.1场地 2.2场地");
    printf("\n请选择要查看的场地编号:");
    int selectedCourt;
  
    key = getch();
    printf("%c", key);
    delay(100);
    while (key != '1' && key != '2')
    {
        printf("\n请根据需求，重新输入您的选项：");
        key = getch();
        printf("%c", key);
        delay(100);
    }

    selectedCourt = key - '0';
    selectedHall--; // 将用户选择转换为数组索引
    selectedCourt--;
    printf("\n\n%s 场地%d 的场地利用率统计:\n", hallNames[selectedHall], selectedCourt + 1);
    // 创建一个副本数组用于排序，同时维护时间段名称的副本数组
    double courtUtilization[16];
    const char* sortedTimePeriods[16];
    for (int k = 0; k < 16; k++)
    {
        int totalUsage = courtUsage[selectedHall][selectedCourt][k];
        int maxPerson = halls[selectedHall].courts[selectedCourt].maxPerson;
        courtUtilization[k] = (double)totalUsage / (maxPerson * 7) * 100.0;
        sortedTimePeriods[k] = timePeriods[k];
    }
    // 使用冒泡排序对副本数组进行排序，同时保持时间段名称的同步
    for (int i = 0; i < 16 - 1; i++) 
    {
        for (int j = 0; j < 16 - i - 1; j++)
        {
            if (courtUtilization[j] < courtUtilization[j + 1])
            {
                // 交换利用率
                double tempUtilization = courtUtilization[j];
                courtUtilization[j] = courtUtilization[j + 1];
                courtUtilization[j + 1] = tempUtilization;
                // 交换时间段名称
                const char* tempTimePeriod = sortedTimePeriods[j];
                sortedTimePeriods[j] = sortedTimePeriods[j + 1];
                sortedTimePeriods[j + 1] = tempTimePeriod;
            }
        }
    }
    // 打印排序后的场地利用率及最高利用率时间段
    for (int k = 0; k < 16; k++)
    {
        printf("%s: %.2lf%%\n", sortedTimePeriods[k], courtUtilization[k]);
    }
    // 找到最高利用率时间段
    int mostUtilizedTimeIndex = 0;
    printf("\n这个场地最高利用率的时间段是：%s\n", sortedTimePeriods[mostUtilizedTimeIndex]);
}

void user_menu_rank(void)//用户统计主菜单界面
{
    system("cls");
    readFromFile();  //读取场地信息
    printf(" __________________________________________________\n");
    printf(" _________________体育馆预定系统___________________\n");
    printf(" __________________________________________用户版本\n");
    printf("\t\t 请选择您的需求\t\t\t\n");
    printf(" __________________________________________________\n");
    printf("|                                                  |\n");
    printf("|    1.场馆预定量统计                              |\n");
    printf("|                                                  |\n");
    printf("|    2.场地预定量统计                              |\n");
    printf("|                                                  |\n");
    printf("|    3.性别统计                                    |\n");
    printf("|                                                  |\n");
    printf("|    4.年龄统计                                    |\n");
    printf("|                                                  |\n");
    printf("|    5.场地租金统计                                |\n");
    printf("|                                                  |\n");
    printf("|    6.热门预定时间统计                            |\n");
    printf("|                                                  |\n");
    printf("|    7.场地使用率统计                              |\n");
    printf("|                                                  |\n");
    printf("|    8.返回上一级界面                              |\n");
    printf("|                                                  |\n");
    printf("|__________________________________________________|\n");
    user_choose_rank();
}

void user_choose_rank(void)//用户统计选择系统
{
    char flag;
    printf("请输入您的选项：");
    flag = getch();
    printf("%c", flag);
    delay(100);
    while (flag != '1' && flag != '2' && flag != '3' && flag != '4' && flag != '5' && flag != '6' && flag != '7' && flag != '8' )
    {
        printf("\n请根据提示，输入'1'或'2'或'3'或'4'或'5'或'6'或'7'或'8'：");
        flag = getch();
        printf("%c", flag);
        delay(100);
    }
    printf("\n");
    printf("\n");
    switch (flag)
    {
  
    case '1':
        system("cls");
        countVenueBookings("orderInformation.txt");//根据场地预定量排序
        user_menu_rank_return();
        break;
    case '2':
        system("cls");
        countFieldBookings("orderInformation.txt");//根据场地预定量排序
        user_menu_rank_return();
        break;
    case '3':
        system("cls");
        calculateGenderStatistics();//性别统计 
        user_menu_rank_return();
    case '4':
        system("cls");
        calculateAgeDistribution();//年龄统计
        user_menu_rank_return();
    case '5':
        system("cls");
        sortByRent();//根据场地租金排序
        user_menu_rank_return();
    case '6':
        system("cls");
        calculateHotTime();//热门预定时间
        user_menu_rank_return();
    case '7':
        system("cls");
        calculatingUtilization();//根据场地时间段的使用率
        user_menu_rank_return();
    case '8':system("cls");
        printf("正在返回······");
        delay(500);
        reserve_message(); 
        break;
    default:
        break;
    }
}

void user_menu_rank_return(void)//返回用户统计主菜单界面
{
    printf("\n按任意键返回上一级界面：");
    char a;
    a = getch();
    printf("%c", a);
    delay(100);
    if (a != NULL)
    {
        printf("\n正在返回······");
        delay(400);
        user_menu_rank();
    }
}