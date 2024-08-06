#ifndef RANK_H  
#define RANK_H  

#include <stdio.h>
#include <string.h>
#include"site_search.h"
#define MAX_LINE_LENGTH 100
#define MAX_VENUES 3
#define MAX_FIELDS 2



struct Order // 结构体用于存储订单信息
{
    char username[50];
    char fullName[50];
    int age;     // 使用整数来存储年龄
    int gender;  // 使用整数来存储性别
    char orderNumber[50];
    char venue[50];
    char venueNumber[50];
    char date[20];
    char time[20];
};

typedef struct 
{
    int maleCount;   // 男性数量
    int femaleCount; // 女性数量
} GenderStats;

GenderStats genderStatistics[MAX_VENUES][MAX_FIELDS]; // 存储性别统计信息的数组

void administrator_menu_rank(void);//管理员统计主菜单界面

void administrator_choose_rank(void);//管理员统计选择系统

void administrator_menu_rank_return(void);//返回管理员统计主菜单界面

int parseOrderFile(const char* filename);// 读取并打印全部订单信息

void countFieldBookings(const char* filename); // 函数用于统计每个场地的预定总量和排序

void countVenueBookings(const char* filename);// 函数用于统计每个场馆的预定总量和排序

void countVenueBusinesVolume(const char* filename);//统计场馆的营业额+排序

void calculateGenderStatistics(); // 统计每个场地的男女数量以及每个场馆的男女数量，并统计最喜欢的场馆

void calculateAgeDistribution(); // 统计每个场地的年龄分布

void sortByRent(); // 读取租金并排序所有场地，同时打印排序后的场地信息

int compareUsage(const void* a, const void* b);//比较用户年龄

void calculateHotTime(); // 统计并打印每个场地中每个时间段的预约情况

void calculatingUtilization(); //统计并打印每个场地中每个时间段的场地利用率

void user_menu_rank(void);//用户统计主菜单界面

void user_choose_rank(void);//用户统计选择系统

void user_menu_rank_return(void);//返回用户统计主菜单界面

#endif