#ifndef SITE_SEARCH_H
#define SITE_SEARCH_H

struct Date // �ṹ�����ڴ洢������Ϣ
{
    int year;
    int month;
    int day;
};

struct DateTime
{
    int year;
    int month;
    int day;
    int hour;
};

typedef struct //����Ԥ����Ϣ�ṹ��   
{ 
    int courtNum; //���ر��
    int rentRerHour;//����ÿСʱ�����
    char courtId[10];
    int time[7][16];   // ĳһ��ĳ��ʱ��ε�ԤԼ����
    int maxPerson; //�ó������ɵ��������
} Court;

typedef struct
{
    int hallNum;  //���ݱ��
    int NumOfCourt;  //������ݵĳ�������
    char name[10];//���ݱ��
    char hallRegion[15];//������������
    char sportType[15];//�����˶�����
    int minAge;//׼����С��������
    int maxAge;//׼�������������
    Court courts[2];
} Hall;

Hall halls[3];

void inquiry_menu(void);//����Ԥ����ѯ�˵�����

void inquiry_choose(void);//����Ԥ����ѯ�˵�ѡ����

void inquiry_menu_user(void);//�û��鿴����Ԥ����������

void inquiry_choose_user(void);//�û�Ԥ����ѯ����ѡ����

void inquiry_menu_return_user(void);//�û�����Ԥ����ѯ����

void inquiry_menu_return(void);//���س���Ԥ����ѯ�˵����溯��

void redcol(const char* text);//��ɫ�ַ�

void greencol(const char* text);//��ɫ�ַ�

void lightbluecol(const char* text);//��ɫ�ַ�

void printCourtStatusByCourt(int courtNum);//ͨ����������ӡԤ�����

void printCourtStatusByHall(int hallNum); //ͨ����������ӡԤ�����

void saveToFile(); //�����ļ�

void readFromFile();//���ļ�

struct Date getCurrentDate();//��ȡ���ڵ�ʱ��

struct DateTime getCurrentDateTime(); //��ȡʱ�䣨���Ӿ�ϸ��

void read_site_menu_user(void);

void read_site_choose_user(void);//��ѯ������Ϣѡ�񡪡��û�

void read_site_menu_ad(void);//���ز�ѯ���桪������Ա

void read_site_choose_ad(void);//��ѯ������Ϣѡ��

void findHallbyName();//ͨ���������Ʋ�ѯ

void findHallbyRegion(); //ͨ���������������ѯ

void findHallbyType();//ͨ�������˶����Ͳ�ѯ

void findAvailableCourts();// �������ں�ʱ��β�ѯ���أ�ʵ�ֹ��˲�ѯ

void printHallInfoByIndex(int index); // ͨ���������Ʋ�ѯ����ʾ��Ϣ

void read_site_menu_return_ad(void);//����Ա���س��ݲ�ѯ����

void read_site_menu_return_user(void);//�û����س��ݲ�ѯ����


#endif