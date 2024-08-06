#ifndef BOOK_SITE_H
#define BOOK_SITE_H
#include"info_management.h"


struct Order
{
	char ID[20];
	char name[20];
	int age;     // ʹ���������洢����
	int gender;  // ʹ���������洢�Ա�
	char orderNumber[30];     //�������
	char location[50];   //����ĳ��ݡ����ء����ڡ�ʱ���
};

struct order_info {
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

void book_f();//Ԥ��������֤�ӽ��뺯��

void bookCourt(Customer* customer);//Ԥ������

void saveOrderToFile(const char* ID, const char* name, const char* age, const char* gender, const char* orderNumber, const char* location);  //���涩����Ϣ

void calculateDates(); //����ʱ��

int isInteger(const char* input);//��֤����

int authenticateUser(const char* username, Customer* customer);//ƥ���û��˺ţ��洢������Ϣ����֤ˬԼ����С����

int checkAppointmentLimit(const Customer* customer);//��֤��ԤԼ����С������������������ԤԼ

int authenticateUser_history(const char* username, Customer* customer);//ƥ���û��˺ţ��洢������Ϣ������֤ˬԼ����,��ӡ�û�����ʹ��

void showOrders(char username[], Customer* customer);//��ӡ��ʷԤԼ������ȡ��Ԥ��

void showOrders_menu();//��ӡ��ʷ����������ȡ��Ԥ��Ԥ����

void saveOrder();//��order���ݴ���ļ�

int readOrder();//�Ķ������ĵ��������ܶ�������

int filter_digits(const char* input); //���ַ����й��˳����ֲ���������

void signIn_pre(void);//ǩ��Ԥ����

void signIn(char username[], Customer* customer);//�û�ǩ��

int calculateDateDifferenceFromToday(const char* cancellationTimeRange);//��ȡ������Ϣ������ȡ��Ԥ���ı���Ϣ�����ļ�


#endif