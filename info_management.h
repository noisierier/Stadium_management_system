#ifndef INFO_MANAGEMENT_H
#define INFO_MANAGEMENT_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Customer 
{
    char age[5];           // ����
    char id[30];            // �˺�
    char cus_password[30];  // ����
    char name[20];     // ����
    char gender[10];           //�Ա�
    char phone[30];         //�绰
    char email[30];    // ����
    char cus_balance[30] ; // ���
    char address[30];  // סַ
    char noShowCount[5];   // ˬԼ����
    char appointmentNum[5]; //��ԤԼ����
    int book_num[6];//�������ݵ�ԤԼ����
} Customer;//�û���Ϣ


typedef struct _Node
{
	Customer cus;
	struct _Node* next;
}Node;//�����Ϣ

bool is_valid_number(char* str); //�ж��ַ������������ֵΪ��������С��

bool all_digits(char* str); //�ж������ڴ洢���ַ�ȫ��������

int count_strings(char* strings); //��������Ԫ�ظ���

int determine_id_passward(char* strings);//�ж��û����������ʽ����

int determine_name(char* strings);//�ж��û����ָ�ʽ����

int  determine_age(char* strings);//�ж��û������ʽ����

bool determine_email(char* email);//�ж������ʽ����

void management_system_choose(void); //����Ա�汾�û���Ϣ����ϵͳѡ����

void additem(Node* head); //����û���Ϣ

void showallitem(Node* head);//��ӡ�����û�����Ϣ

void count(Node* head); //ͳ�������û�������

void seatchitem(Node* head);//�����û���Ϣ

void modify_menu_pre(Node* head);//�޸��û���Ϣ����_�ж��û������˺�

void modify_choose_pre(Node* head);//pre�汾��Ϣ�޸�ѡ�񡪡����������ж��û��˺ŵĴ�����

void modify_menu_real(char* id);//�����û��˺�

void modify_choose_real(Node* head, char* id);//�Ѿ��ж��û���Ϣ���ڣ������û���Ϣ��ϸ�޸Ľ���

void return_modify_choose_real(Node* head, char* id);//�޸���Ϣ��ϣ����ؽ���

void deletecustomer(Node* head); //ɾ���û���Ϣ

void saveList(Node* head, const char* filename);//�����������ļ���

void saveList_ad(Node* head, const char* filename);//��������������Ա�ļ���

void loadList(Node* head, const char* filename);//���ļ��ж�ȡ����

void clearInputBuffer(); //����gets_s()���µĻ��з�

double str_to_double(char* str);//�����ת����˫����С��

void user_login(void);//�û���¼

void user_register(void);//�û�ע�ắ��

void user_modify_menu(void);//�û����˵�¼�����Ϣ�޸Ľ���

void user_modify_menu_choose(void);//�û�������Ϣ�޸Ľ���ѡ����

void ad_modify_menu_choose(void);//����Ա������Ϣ�޸Ľ���ѡ����

void ad_modify_menu(void);//�û����˵�¼�����Ϣ�޸Ľ���

void user_read_info(void);//�û��鿴������Ϣ

void ad_read_info(void);//����Ա�鿴������Ϣ

bool determine_phone(char* str);//�ж��ֻ��Ÿ�ʽ

void saveListToFile(Node* head, const char* filename);//���������ݴ洢�����������ļ���

#endif