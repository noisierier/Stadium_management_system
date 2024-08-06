#ifndef RANK_H  
#define RANK_H  

#include <stdio.h>
#include <string.h>
#include"site_search.h"
#define MAX_LINE_LENGTH 100
#define MAX_VENUES 3
#define MAX_FIELDS 2



struct Order // �ṹ�����ڴ洢������Ϣ
{
    char username[50];
    char fullName[50];
    int age;     // ʹ���������洢����
    int gender;  // ʹ���������洢�Ա�
    char orderNumber[50];
    char venue[50];
    char venueNumber[50];
    char date[20];
    char time[20];
};

typedef struct 
{
    int maleCount;   // ��������
    int femaleCount; // Ů������
} GenderStats;

GenderStats genderStatistics[MAX_VENUES][MAX_FIELDS]; // �洢�Ա�ͳ����Ϣ������

void administrator_menu_rank(void);//����Աͳ�����˵�����

void administrator_choose_rank(void);//����Աͳ��ѡ��ϵͳ

void administrator_menu_rank_return(void);//���ع���Աͳ�����˵�����

int parseOrderFile(const char* filename);// ��ȡ����ӡȫ��������Ϣ

void countFieldBookings(const char* filename); // ��������ͳ��ÿ�����ص�Ԥ������������

void countVenueBookings(const char* filename);// ��������ͳ��ÿ�����ݵ�Ԥ������������

void countVenueBusinesVolume(const char* filename);//ͳ�Ƴ��ݵ�Ӫҵ��+����

void calculateGenderStatistics(); // ͳ��ÿ�����ص���Ů�����Լ�ÿ�����ݵ���Ů��������ͳ����ϲ���ĳ���

void calculateAgeDistribution(); // ͳ��ÿ�����ص�����ֲ�

void sortByRent(); // ��ȡ����������г��أ�ͬʱ��ӡ�����ĳ�����Ϣ

int compareUsage(const void* a, const void* b);//�Ƚ��û�����

void calculateHotTime(); // ͳ�Ʋ���ӡÿ��������ÿ��ʱ��ε�ԤԼ���

void calculatingUtilization(); //ͳ�Ʋ���ӡÿ��������ÿ��ʱ��εĳ���������

void user_menu_rank(void);//�û�ͳ�����˵�����

void user_choose_rank(void);//�û�ͳ��ѡ��ϵͳ

void user_menu_rank_return(void);//�����û�ͳ�����˵�����

#endif