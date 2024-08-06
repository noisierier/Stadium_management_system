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


const char* hall__names[] = { "���ೡ��","��Ӿ����","���ⳡ��" };


time_t now; // ��ǰʱ��

int hallsNum = sizeof(halls) / sizeof(halls[0]);  // ��ȡ������

int courtsNum = sizeof(halls[0].courts) / sizeof(halls[0].courts[0]);  // ��ȡ������

void inquiry_menu(void)//����Ա�鿴����Ԥ����������
{   
    system("cls");
    printf(" __________________________________________________\n");
    printf(" ________________������Ԥ��������ϵͳ______________\n");
    printf(" __________________________________________����Ա��\n");
    printf("\t\t ��ѡ����������\t\t\t\n");
    printf(" __________________________________________________\n");
    printf("|                                                  |\n");
    printf("|    1.�����ر����ʾ����Ԥ�����                  |\n");
    printf("|                                                  |\n");
    printf("|    2.�����ݱ����ʾ����Ԥ�����                  |\n");
    printf("|                                                  |\n");
    printf("|    3.ʹ��˵��                                    |\n");
    printf("|                                                  |\n");
    printf("|    4.����Ԥ���������                            |\n");
    printf("|                                                  |\n");
    printf("|__________________________________________________|\n");
    inquiry_choose();
}

void inquiry_choose(void)//�û�Ԥ����ѯ����ѡ����
{
    readFromFile();
    char flag;
    char courtNum;// ��ȡ�û�����ĳ��ݱ��
    char hallNum; // ���ڴ洢�û�����ĳ��ݱ��
    printf("����������ѡ�");
    flag = getch();
    printf("%c", flag);
    delay(100);
    while (flag != '1' && flag != '2' && flag != '3'&&flag!='4')
    {
        printf("\n�������ʾ������'1'��'2'��'3'��'4'��");
        flag = getch();
        printf("%c", flag);
        delay(100);
    }
    switch (flag)
    {
        case '1':
            system("cls");
            printf("\n������ҪѰ�ҵĳ��غ�(����������)��");
            courtNum = getch();
            printf("%c", courtNum);
            delay(100);
            while (!isdigit(courtNum))
            {
                printf("\n�����ʽ����������������");
                courtNum = getch();
                printf("%c", courtNum);
                delay(100);
            }
            system("CLS");
            int courtNum_ = courtNum - '0';
            printCourtStatusByCourt(courtNum_); //�����ر����ʾ����Ԥ�����
            inquiry_menu_return();
            break;
        case '2':
            system("cls");
            printf("\n������ҪѰ�ҵĳ��ݱ�ţ�");
            hallNum = getch();
            printf("%c", hallNum);
            delay(100);
            while (!isdigit(hallNum))
            {
                printf("\n�����ʽ����������������");
                hallNum = getch();
                printf("%c", hallNum);
                delay(100);
            }
            system("CLS");
            int hallNum_ = hallNum - '0';
            printCourtStatusByHall(hallNum_); // �����ݱ����ʾ����Ԥ�����
            inquiry_menu_return();
            break;
        case'3':
            system("cls");//ʹ��˵��
            printf("ʹ��˵��\n");
            inquiry_menu_return();
            break;
        case '4': printf("\n���ڷ��ء�����������");
            delay(500);
            Scheduled_anagement();
            break;
        default:
            break;
    }
}

void inquiry_menu_user(void)//�û��鿴����Ԥ����������
{
    system("cls");
    printf(" __________________________________________________\n");
    printf(" ____________�����ݳ���Ԥ�������ѯϵͳ____________\n");
    printf(" __________________________________________�û��汾\n");
    printf("\t\t ��ѡ����������\t\t\t\n");
    printf(" __________________________________________________\n");
    printf("|                                                  |\n");
    printf("|    1.�����ر����ʾ����Ԥ�����                  |\n");
    printf("|                                                  |\n");
    printf("|    2.�����ݱ����ʾ����Ԥ�����                  |\n");
    printf("|                                                  |\n");
    printf("|    3.ʹ��˵��                                    |\n");
    printf("|                                                  |\n");
    printf("|    4.����Ԥ���������                            |\n");
    printf("|                                                  |\n");
    printf("|__________________________________________________|\n");
    inquiry_choose_user();
}

void inquiry_choose_user(void)//�û�Ԥ����ѯ����ѡ����
{
    readFromFile();
    char flag;
    char courtNum;// ��ȡ�û�����ĳ��ݱ��
    char hallNum; // ���ڴ洢�û�����ĳ��ݱ��
    printf("����������ѡ�");
    flag = getch();
    printf("%c", flag);
    delay(100);
    while (flag != '1' && flag != '2' && flag != '3' && flag != '4')
    {
        printf("\n�������ʾ������'1'��'2'��'3'��'4'��");
        flag = getch();
        printf("%c", flag);
        delay(100);
    }
    switch (flag)
    {
    case '1':
        system("cls");
        printf("\n������ҪѰ�ҵĳ��غ�(����������)��");
        courtNum = getch();
        printf("%c", courtNum);
        delay(100);
        while (!isdigit(courtNum))
        {
            printf("\n�����ʽ����������������");
            courtNum = getch();
            printf("%c", courtNum);
            delay(100);
        }
        system("CLS");
        int courtNum_ = courtNum - '0';
        printCourtStatusByCourt(courtNum_); //�����ر����ʾ����Ԥ�����
        inquiry_menu_return_user();
        break;
    case '2':
        system("cls");
        printf("\n������ҪѰ�ҵĳ��ݱ�ţ�");
        hallNum = getch();
        printf("%c", hallNum);
        delay(100);
        while (!isdigit(hallNum))
        {
            printf("\n�����ʽ����������������");
            hallNum = getch();
            printf("%c", hallNum);
            delay(100);
        }
        system("CLS");
        int hallNum_ = hallNum - '0';
        printCourtStatusByHall(hallNum_); // �����ݱ����ʾ����Ԥ�����
        inquiry_menu_return_user();
        break;
    case'3':
        system("cls");//ʹ��˵��
        printf("ʹ��˵��\n");
        inquiry_menu_return_user();
        break;
    case '4': printf("\n���ڷ��ء�����������");
        delay(500);
        reserve_message();
        break;
    default:
        break;
    }
}

void inquiry_menu_return(void)//����Ա����Ԥ����ѯ����
{
    printf("�����������Ԥ����ѯ���棺");
    char key_board = getch();
    if (key_board != NULL)
    {
        printf("%c", key_board);
        delay(100);
        inquiry_menu();
    }   
}

void inquiry_menu_return_user(void)//�û�����Ԥ����ѯ����
{
    printf("�����������Ԥ����ѯ���棺");
    char key_board = getch();
    if (key_board != NULL)
    {
        printf("%c", key_board);
        delay(100);
        inquiry_menu_user();
    }
}

void redcol(const char* text) // ���ú�ɫ����
{
    printf("\033[1;31m%s\033[0m", text);   
}

void greencol(const char* text) // ������ɫ����
{
    printf("\033[1;32m%s\033[0m", text);   
}

void lightbluecol(const char* text)// ����ǳ��ɫ����
{
    printf("\033[1;94m%s\033[0m", text);   
}

void printCourtStatusByCourt(int courtNum)//ͨ����������ӡԤ�����
{
    int found = 0; // ��־�Ƿ��ҵ�ƥ��ĳ���
    struct DateTime currentDateTime = getCurrentDateTime();    // ���ú�����ȡ��ǰ���ں�ʱ��
    printf("��ǰ���ڣ�%d-%02d-%02d\n", currentDateTime.year, currentDateTime.month, currentDateTime.day);    // ��ӡ��ǰ����
    printf("���ر�ţ�%d\n\n", courtNum);

    for (int i = 0; i < hallsNum; i++) 
    {
        for (int j = 0; j < halls[i].NumOfCourt; j++)// ����ÿ������
        {  
            if (halls[i].courts[j].courtNum == courtNum)// ��鳡�ر���Ƿ�ƥ��
            { 
                printf("���ݺţ�%d\n", halls[i].hallNum);  // ��ӡ���ݺ�
                printf("�������ƣ�%s\n", hall__names[i]);
                printf("����Ԥ����Ϣ��\n");
                for (int d = 0; d < 7; d++) 
                {
                    struct Date printDate;
                    printDate.year = currentDateTime.year;
                    printDate.month = currentDateTime.month;
                    printDate.day = currentDateTime.day;

                    // ���㲢��ӡ����
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
                        printf("%d��00-%d��00 ", (k + 6), (k + 7));
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
                        printf(" ��  ");
                    }
                    printf("\n");
                }
                printf("\n");
                found = 1; // ��־Ϊ���ҵ�ƥ��ĳ���
            }
        }
    }
    // ���δ�ҵ�ƥ��ĳ��أ������ʾ
    if (!found) 
    {
        printf("δ�ҵ�ƥ��ĳ��ر�ţ�%d\n", courtNum);
    }
}

void printCourtStatusByHall(int hallNum) //ͨ����������ӡԤ�����
{
    int found = 0; // ��־�Ƿ��ҵ�ƥ��ĳ���
    struct DateTime currentDateTime = getCurrentDateTime();    // ���ú�����ȡ��ǰ���ں�ʱ��
    printf("��ǰ���ڣ�%d-%02d-%02d\n", currentDateTime.year, currentDateTime.month, currentDateTime.day);    // ��ӡ��ǰ����

    for (int i = 0; i < hallsNum; i++)
    {
        if (halls[i].hallNum == hallNum)// ��鳡�ݱ���Ƿ�ƥ��
        { 
            found = 1; // ���ñ�־Ϊ���ҵ�
            printf("���ݺţ�%d\n", halls[i].hallNum);
            printf("�������ƣ�%s\n\n", hall__names[i]);
            // ��ӡ����Ԥ�����
            for (int j = 0; j < halls[i].NumOfCourt; j++) 
            {
                printf("���ر�ţ�%s (%d/%d)\n", halls[i].courts[j].courtId, halls[i].courts[j].maxPerson, halls[i].courts[j].maxPerson);
                printf("����Ԥ����Ϣ��\n");
                for (int d = 0; d < 7; d++) 
                {
                    struct Date printDate;
                    printDate.year = currentDateTime.year;
                    printDate.month = currentDateTime.month;
                    printDate.day = currentDateTime.day;

                    // ���㲢��ӡ����
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
                        printf("%d��00-%d��00 ", (k + 6), (k + 7));
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
                        printf(" ��  ");
                    }
                    printf("\n");
                }
                printf("\n");
            }
        }
    }
    // ���û���ҵ�ƥ��ĳ��ݱ��
    if (!found) {
        printf("δ�ҵ�ƥ��ĳ��ݱ�ţ�%d\n", hallNum);
    }
}

void saveToFile() //���泡���ļ�
{
    FILE* file = fopen("site.txt", "w");
    if (file == NULL)
    {
        printf("�޷����ļ�\n");
        return;
    }
    for (int i = 0; i < 3; i++) 
    {
        fprintf(file, "%d\n", halls[i].hallNum); // ���泡�ݱ��
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
            fprintf(file, "\n"); // ����֮�����һ�����У����������һ������֮�����
        }
    }
    fclose(file);
}

void readFromFile()//���ļ�
{
    FILE* file = fopen("site.txt", "r");
    if (file == NULL) 
    {
        printf("�޷����ļ�\n");
        return;
    }
    for (int i = 0; i < 3; i++) 
    {
        fscanf(file, "%d", &halls[i].hallNum); // ��ȡ���ݱ��
        fscanf(file, "%d", &halls[i].NumOfCourt);//���ظ���
        fscanf(file, "%s", halls[i].name);//��������
        fscanf(file, "%s", halls[i].hallRegion);//��������
        fscanf(file, "%s", halls[i].sportType);//�����˶�����
        fscanf(file, "%d", &halls[i].minAge);//������С��������
        fscanf(file, "%d", &halls[i].maxAge);//���������������
        for (int j = 0; j < halls[i].NumOfCourt; j++)
        {
            fscanf(file, "%d", &halls[i].courts[j].courtNum); // ��ȡ���ر��
            fscanf(file, "%d", &halls[i].courts[j].rentRerHour);
            fscanf(file, "%s", halls[i].courts[j].courtId); // ��ȡ����ID
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

struct Date getCurrentDate()//��ȡ���ڵ�ʱ��
{
    struct Date currentDate;

    time_t currentTime;
    struct tm* localTime;

    // ��ȡ��ǰʱ�������
    currentTime = time(NULL);

    // ת��Ϊ����ʱ��ṹ��
    localTime = localtime(&currentTime);

    // ��ȡ������Ϣ
    currentDate.year = localTime->tm_year + 1900; // �����Ҫ����1900
    currentDate.month = localTime->tm_mon + 1;    // �·��Ǵ�0��ʼ�ģ�������Ҫ��1
    currentDate.day = localTime->tm_mday;         // ���µĵڼ���

    return currentDate;
}

struct DateTime getCurrentDateTime()//��ȡʱ�䣨���Ӿ�ϸ��
{
    struct DateTime currentDateTime;

    time_t currentTime;
    struct tm* localTime;

    // ��ȡ��ǰʱ�������
    currentTime = time(NULL);

    // ת��Ϊ����ʱ��ṹ��
    localTime = localtime(&currentTime);

    // ��ȡ���ں�Сʱ��Ϣ
    currentDateTime.year = localTime->tm_year + 1900; // �����Ҫ����1900
    currentDateTime.month = localTime->tm_mon + 1;    // �·��Ǵ�0��ʼ�ģ�������Ҫ��1
    currentDateTime.day = localTime->tm_mday;         // ���µĵڼ���
    currentDateTime.hour = localTime->tm_hour;        // ��ǰСʱ��

    return currentDateTime;
}

void read_site_menu_user(void)//���ز�ѯ���桪���û�
{
    readFromFile();//���ļ��ж�ȡ���ݳ�����Ϣ������洢���ṹ����
    /*ֱ����strcpy�����������ݵ�hallRegion[10]����������
   sportType[12](�˶�����)��ֵ�����ַ��� ��Ϊ�ļ���ȡ���������ַ���*/
    strcpy(halls[0].sportType, "���������˶�");
    strcpy(halls[1].sportType, "��Ӿ����˶�");
    strcpy(halls[2].sportType, "�����ﾶ��Ŀ");
    strcpy(halls[0].name, "���ೡ��");
    strcpy(halls[1].name, "��Ӿ����");
    strcpy(halls[2].name, "���ⳡ��");
    delay(100);
    system("cls");
    printf(" __________________________________________________\n");
    printf(" ________________�����ݳ��ز�ѯϵͳ________________\n");
    printf(" __________________________________________�û��汾\n");
    printf("\t\t ��ѡ����������\t\t\t\n");
    printf(" __________________________________________________\n");
    printf("|                                                  |\n");
    printf("|    1.ͨ���������Ʋ�ѯ                            |\n");
    printf("|                                                  |\n");
    printf("|    2.ͨ���������������ѯ                        |\n");
    printf("|                                                  |\n");
    printf("|    3.ͨ�������˶����Ͳ�ѯ                        |\n");
    printf("|                                                  |\n");
    printf("|    4.ͨ������ԤԼ�����������ز�ѯ                |\n");
    printf("|                                                  |\n");
    printf("|    5.������һ������                              |\n");
    printf("|                                                  |\n");
    printf("|__________________________________________________|\n");
    read_site_choose_user();
}

void read_site_choose_user(void)//��ѯ������Ϣѡ�񡪡��û�
{
    char flag;
    printf("����������ѡ�");
    flag = getch();
    printf("%c", flag);
    delay(100);
    while (flag != '1' && flag != '2' && flag != '3' && flag != '4' && flag != '5')
    {
        printf("\n�������ʾ������'1'��'2'��'3'��'4'��'5'��");
        flag = getch();
        printf("%c", flag);
        delay(100);
    }
    switch (flag)
    {
    case '1': findHallbyName();//ͨ���������Ʋ�ѯ
        read_site_menu_return_user();
        break;
    case '2': findHallbyRegion();//ͨ���������������ѯ
        read_site_menu_return_user();
        break;
    case '3':findHallbyType();//ͨ�������˶����Ͳ�ѯ
        read_site_menu_return_user();
        break;
    case '4':findAvailableCourts();//ͨ������ԤԼ�����������ز�ѯ
        read_site_menu_return_user();
        break;
    case '5':printf("\n���ڷ��ء�����������");
        delay(500);
        user_menu();
    default:
        break;
    }
}

void read_site_menu_ad(void) //���ز�ѯ���桪������Ա
{
    readFromFile();//���ļ��ж�ȡ���ݳ�����Ϣ������洢���ṹ����
    /*ֱ����strcpy�����������ݵ�hallRegion[10]����������
  sportType[12](�˶�����)��ֵ�����ַ��� ��Ϊ�ļ���ȡ���������ַ���*/
    strcpy(halls[0].sportType, "���������˶�");
    strcpy(halls[1].sportType, "��Ӿ����˶�");
    strcpy(halls[2].sportType, "�����ﾶ��Ŀ");
    strcpy(halls[0].name, "���ೡ��");
    strcpy(halls[1].name, "��Ӿ����");
    strcpy(halls[2].name, "���ⳡ��");
    delay(100);
    system("cls");
    printf(" __________________________________________________\n");
    printf(" ________________�����ݳ��ؼ�����ϵͳ______________\n");
    printf(" __________________________________________����Ա��\n");
    printf("\t\t ��ѡ����������\t\t\t\n");
    printf(" __________________________________________________\n");
    printf("|                                                  |\n");
    printf("|    1.ͨ���������Ʋ�ѯ                            |\n");
    printf("|                                                  |\n");
    printf("|    2.ͨ���������������ѯ                        |\n");
    printf("|                                                  |\n");
    printf("|    3.ͨ�������˶����Ͳ�ѯ                        |\n");
    printf("|                                                  |\n");
    printf("|    4.ͨ������ԤԼ�����������ز�ѯ                |\n");
    printf("|                                                  |\n");
    printf("|    5.������һ������                              |\n");
    printf("|                                                  |\n");
    printf("|__________________________________________________|\n");
    read_site_choose_ad();
}

void read_site_choose_ad(void)//��ѯ������Ϣѡ��
{
    char flag;
    printf("����������ѡ�");
    flag = getch();
    printf("%c", flag);
    delay(100);
    while (flag != '1' && flag != '2' && flag != '3' && flag != '4' && flag != '5')
    {
        printf("\n�������ʾ������'1'��'2'��'3'��'4'��'5'��");
        flag = getch();
        printf("%c", flag);
        delay(100);
    }
    switch (flag)
    {
    case '1': findHallbyName();//ͨ���������Ʋ�ѯ
        read_site_menu_return_ad();
        break;
    case '2': findHallbyRegion();//ͨ���������������ѯ
        read_site_menu_return_ad();
        break;
    case '3':findHallbyType();//ͨ�������˶����Ͳ�ѯ
        read_site_menu_return_ad();
        break;
    case '4':findAvailableCourts();//ͨ������ԤԼ�����������ز�ѯ
        read_site_menu_return_ad();
        break;
    case '5':printf("\n���ڷ��ء�����������");
        delay(500);
        site_management();
    default:
        break;
    }
}

void findHallbyName()//ͨ���������Ʋ�ѯ
{
    char indexChar;
    system("cls");
    printf("������Ҫ��ѯ�ĳ������� (1/2/3):\n");
    printf("1.���ೡ��\n");
    printf("2.��Ӿ����\n");
    printf("3.���ⳡ��\n");
    indexChar = _getch(); // ��ȡ������ַ�
    int index = indexChar - '1';  // ���ַ�ת��Ϊ��������
    delay(100);
    printHallInfoByIndex(index);
}

void findHallbyRegion() //ͨ���������������ѯ
{
    system("cls");
    char indexChar;
    printf("������Ҫ��ѯ�ĳ������� (1/2/3):\n");
    printf("1.Region1\n");
    printf("2.Region2\n");
    printf("3.Region3\n");
    indexChar = _getch(); // ��ȡ������ַ�
    int index = indexChar - '1'; // ���ַ�ת��Ϊ��������
    delay(100);
    printHallInfoByIndex(index);
}

void findHallbyType()//ͨ�������˶����Ͳ�ѯ
{
    char indexChar;
    system("cls");
    printf("������Ҫ��ѯ�ĳ������� (1/2/3):\n");
    printf("1.���������˶�\n");
    printf("2.��Ӿ����˶�\n");
    printf("3.�����ﾶ��Ŀ\n");
    indexChar = _getch(); // ��ȡ������ַ�
    int index = indexChar - '1'; // ���ַ�ת��Ϊ��������
    delay(100);
    printHallInfoByIndex(index);
}

void printHallInfoByIndex(int index) // ͨ���������Ʋ�ѯ����ʾ��Ϣ
{
    if (index >= 0 && index < 3)
    {
        printf("\n����������%d\n", halls[index].NumOfCourt);
        printf("��������: %s\n", halls[index].name);
        printf("��������: %s\n", halls[index].hallRegion);
        printf("�����˶�����: %s\n", halls[index].sportType);
        printf("������С����: %d\n", halls[index].minAge);
        printf("�����������: %d\n", halls[index].maxAge);
        int NumOfCourts = sizeof(halls[index].courts) / sizeof(halls[index].courts[0]);
        for (int i = 0; i < NumOfCourts; i++)
        {
            printf("\n");
            printf("���� %d �������Ϣ��\n", i + 1);
            printf("����ID��%s\n", halls[index].courts[i].courtId);
            printf("ÿСʱ�����%d\n", halls[index].courts[i].rentRerHour);
        }
    }
    else 
    {
        printf("��Ч�ĳ�������: %d\n", index);
    }
}

void read_site_menu_return_ad(void)//����Ա���س��ݲ�ѯ����
{
    char free_key;
    printf("\n������ִ����ϣ��������������һ�����棺");
    free_key = getch();
    printf("%c",free_key);
    printf("\n���ڷ��ء�����������");
    delay(500);
    read_site_menu_ad();
}

void read_site_menu_return_user(void)//�û����س��ݲ�ѯ����
{
    char free_key;
    printf("\n������ִ����ϣ��������������һ�����棺");
    free_key = getch();
    printf("%c", free_key);
    printf("\n���ڷ��ء�����������");
    delay(500);
    read_site_menu_user();
}

void findAvailableCourts()// �������ں�ʱ��β�ѯ���أ�ʵ�ֹ��˲�ѯ
{
    system("cls");
    int selectedDay;
    int selectedTimeSlot;
    char key;
    bool availableCourtsFound = false; // ����һ����־���������ڼ���Ƿ��з��������ĳ���
    char selectedDayChar;// ��ȡ�û�������ַ���ѡ��Ҫ��ѯ������
   
    // ��ȡ��ǰ���ں�ʱ��
    time_t current_time;
    struct tm* time_info;
    time(&current_time);
    time_info = localtime(&current_time);

    // ��ӡ���������
 /*   printf("\n1.%04d-%02d-%02d\t",
        time_info->tm_year + 1900, time_info->tm_mon + 1, time_info->tm_mday);*/

    // ��ӡδ�����������
    for (int i = 1; i < 8; i++) {
        // ����һ���ʱ��
        current_time += 24 * 60 * 60; // 60�� * 60���� * 24Сʱ
        time_info = localtime(&current_time);

        // ��ӡδ������
        printf("%d.%04d-%02d-%02d\n", i,
            time_info->tm_year + 1900, time_info->tm_mon + 1, time_info->tm_mday);
    }





    printf("��ѡ��Ҫ��ѯ������ (1-7): ");
    selectedDayChar = _getch();  // ʹ�� _getch ��ȡ�û�������ַ�
    printf("%c", selectedDayChar);
    delay(100);
    while (selectedDayChar != '1' && selectedDayChar != '2' && selectedDayChar != '3' && selectedDayChar != '4' && selectedDayChar != '5' && selectedDayChar != '6' && selectedDayChar != '7' )
    {
        printf("\n�������ʾ������'1'��'2'��'3'��'4'��'5'��'6'��'7'��");
        selectedDayChar = getch();
        printf("%c", selectedDayChar);
        delay(100);
    }
    selectedDay = (selectedDayChar - '0' - 1);  // ���ַ�ת��Ϊ����
    printf("\n\n��ѡ��Ҫ��ѯ��ʱ���:\n"); // ��ȡ�û�������ַ���ѡ��Ҫ��ѯ��ʱ���
    printf("a. 6:00-7:00       b. 7:00-8:00       c. 8:00-9:00          d. 9:00-10:00\n");
    printf("e. 10:00-11:00     f. 11:00-12:00     g. 12:00-13:00        h. 13:00-14:00\n");
    printf("i. 14:00-15:00     j. 15:00-16:00     k. 16:00-17:00        l. 17:00-18:00\n");
    printf("m. 18:00-19:00     n. 19:00-20:00     o. 20��00-21��00      p. 21��00-22��00\n");
    printf("\n����������ѡ�����������������ͼ���Ϸ�ͼ���е�'a'-'p',ע���������Сд��ĸ):");
    key = getch();
    printf("%c",key);
    delay(100);
    while ( key != 'a' && key != 'b' && key != 'c' && key != 'd' && key != 'e' && key != 'f' && key != 'g' && key != 'h' && key != 'i'&& key != 'j' && key != 'k' && key != 'l' && key != 'm' && key != 'n' && key != 'o' && key != 'p' )
    {
        printf("\n�������ʾ������ͼ���Ϸ�ͼ���е�'a'-'p',ע���������Сд��ĸ��");
        key = getch();
        printf("%c", key);
        delay(300);
    }
    selectedTimeSlot = key - 'a';
    system("cls");
    printf("\n�ڸ�ʱ��ο�ԤԼ�ĳ����У�\n");
    for (int i = 0; i < 3; i++) // ѭ���������г��ݺͳ���
    {
        for (int j = 0; j < halls[i].NumOfCourt; j++)
        {
            Court court = halls[i].courts[j];
            if (court.time[selectedDay][selectedTimeSlot] == 0 && court.maxPerson > 0) // �����ѡ���ں�ʱ��ε�ԤԼ���
            {
                availableCourtsFound = true; // ����ҵ����������ĳ��أ�����־��������Ϊtrue
                printf("����ID: %s\n", court.courtId); // ������������ĳ�����Ϣ
                printf("������������: %s\n", halls[i].name);
                printf("������������: %s\n", halls[i].hallRegion);
                printf("�����˶�����: %s\n", halls[i].sportType);
                printf("׼����С��������: %d\n", halls[i].minAge);
                printf("׼�������������: %d\n", halls[i].maxAge);
                printf("ÿСʱ���: %d\n", court.rentRerHour);
                printf("\n");
            }
        }
    }
    if (!availableCourtsFound)  // ����־���������û�з��������ĳ��أ��������Ӧ��Ϣ
    {
        printf("�޷��������ĳ���\n");
    }
}


