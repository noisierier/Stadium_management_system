#include "info_management.h"
#include<stdio.h>
#include"Administrator.h"
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include"delay.h"
#include <math.h>
#include"menu.h"
#include"user.h"

char uesr_id_[30];
char ad_id_[30];	
extern const char* venue_names[] ;

																											
void user_login(void)//�û���¼
{
	Node* head = (Node*)malloc(sizeof(Node));//����ͷ���
	head->next = NULL;
	loadList(head, "Customer.txt");
	system("cls");
	char free_key;
	printf("\n���������ĵ��û��˺ţ�����С��6�ַ������ô���10�ַ���:");
	char search[30];
	scanf("%s", search);
	while (!determine_id_passward(search))
	{
		printf("\n��ʽ���ԣ������������û��˺ţ�");
		scanf("%s", search);
	}
	Node* move = head;
	while (move->next != NULL)
	{
		
		if (strcmp(move->next->cus.id, search) == 0)
		{
			printf("\n�ɹ�ƥ�䵽�����˺ţ�");
			printf("\n\n���������ĵ��û����루����С��6�ַ������ô���10�ַ���:");
			char search_p[30];
			scanf("%s", search_p);
			while (!determine_id_passward(search_p))
			{
				printf("\n��ʽ���ԣ����������������û����룺");
				scanf("%s", search_p);
			}
			if (strcmp(move->next->cus.cus_password, search_p) == 0)
			{
				printf("\n����������ȷ���ѳɹ�����ϵͳ�����Ժ󡤡���������");
				strcpy(uesr_id_, search);
				delay(500);
				user_menu();
			}
			else
			{
				printf("\n������������밴�����������һ�����棺");
				free_key = getch();
				printf("%c", free_key);
				printf("\n���ڷ��ء�����������");
				delay(500);
				menu();
			}
		}
		move = move->next;
	}
	printf("\nδ�ҵ��û���Ϣ,�밴�����������һ�����棺");
	free_key = getch();
	printf("%c", free_key);
	printf("\n���ڷ��ء�����������");
	delay(500);
	menu();
}

void user_register(void)//�û�ע�ắ��
{
	Node* head = (Node*)malloc(sizeof(Node));//����ͷ���
	head->next = NULL;
	loadList(head, "Customer.txt");
	Node* fresh = (Node*)malloc(sizeof(Node));
	fresh->next = NULL;
	system("cls");
	char free_key;
	printf("�������ʾ��������Ҫ¼����û���Ϣ��");

	printf("\n��������Ҫע����û��˺ţ�����С��6�ַ������ô���10�ַ���:");//fflush(stdin);
	gets_s(fresh->cus.id, 30);
	while (!determine_id_passward(fresh->cus.id))
	{
		printf("\n��ʽ���ԣ������������û��˺ţ�");
		gets_s(fresh->cus.id, 30);
	}

	Node* move = head;
	while (move->next != NULL)
	{
		if (strcmp(move->next->cus.id, fresh->cus.id) == 0)
		{
			printf("\n�����Ѿ��д��˺ţ������������û��˺ţ�");
			fflush(stdin);
			gets_s(fresh->cus.id, 30);
			while (!determine_id_passward(fresh->cus.id))
			{
				printf("\n��ʽ���ԣ������������û��˺ţ�");
				fflush(stdin);
				gets_s(fresh->cus.id, 30);
			}
			move = head;
		}
		else
		{
			move = move->next;
		}
	}

	fresh->cus.appointmentNum[0] = '0'; fresh->cus.appointmentNum[1] = '\0'; fresh->cus.appointmentNum[2] = '\0'; fresh->cus.appointmentNum[3] = '\0'; fresh->cus.appointmentNum[4] = '\0';
	fresh->cus.book_num[0] = 0;fresh->cus.book_num[1] = 0;fresh->cus.book_num[2] = 0;fresh->cus.book_num[3] = 0;fresh->cus.book_num[4] = 0;fresh->cus.book_num[5] = 0;


	printf("\n�������û����루����С��6�ַ������ô���10�ַ�����");
	gets_s(fresh->cus.cus_password, 30);
	while (!determine_id_passward(fresh->cus.cus_password))
	{
		printf("\n��ʽ���ԣ������������û����룺");
		gets_s(fresh->cus.cus_password, 30);
	}

	printf("\n�������û�����������С��2�ַ������ô���20�ַ���:");
	gets_s(fresh->cus.name, 20);
	while (!determine_name(fresh->cus.name))
	{
		printf("\n��ʽ���ԣ������������û�������");
		gets_s(fresh->cus.name, 20);
	}

	printf("\n�������û��Ա�'1'�����У�'0'����Ů)��");
	char gender;
	gender = getchar();
	clearInputBuffer();
	while (gender != '0' && gender != '1')
	{
		printf("\n������'0'��'1'��");
		gender = getchar();
		clearInputBuffer();
	}
	if (gender == '0')
	{
		fresh->cus.gender[0] = '0';
		for (int i = 1; i < 10; i++)
		{
			fresh->cus.gender[i] = '\0';
		}
	}
	else if (gender == '1')
	{
		fresh->cus.gender[0] = '1';
		for (int i = 1; i < 10; i++)
		{
			fresh->cus.gender[i] = '\0';
		}
	}


	printf("\n�������û��ֻ��ţ�11λ���֣���");
	gets_s(fresh->cus.phone, 30);
	while (!determine_phone(fresh->cus.phone))
	{
		printf("\n��ʽ���ԣ������������û��ֻ��ţ�");
		gets_s(fresh->cus.phone, 30);
	}
	

	printf("\n�������û�����:");
	gets_s(fresh->cus.age, 5);
	while (!determine_age(fresh->cus.age))
	{
		printf("\n��ʽ���ԣ������������û����䣺");
		gets_s(fresh->cus.age, 20);
	}

	for (int i = 0; i < 30; i++)
	{
		fresh->cus.cus_balance[i] = '\0';//���û�ע�ᣬ������0
	}
	fresh->cus.cus_balance[0] = '0';
	

	printf("\n�������û�סַ:");
	scanf("%s", &fresh->cus.address);

	printf("\n�������û�����:");
	clearInputBuffer();
	gets_s(fresh->cus.email, 30);
	while (!determine_email(fresh->cus.email))
	{
		printf("\n��ʽ���ԣ������������û����䣺");
		gets_s(fresh->cus.email, 30);
	}


	for (int i = 0; i < 5; i++)
	{
		fresh->cus.noShowCount[i] = '\0';//���û�ע�ᣬˬԼ��������0
	}
	fresh->cus.noShowCount[0] = '0';

	move = head;
	while (move->next != NULL)
	{
		move = move->next;
	}
	move->next = fresh;
	saveList(head,"Customer.txt");
	printf("\n�ɹ�ע���û���Ϣ���������������һ�����棺");
	free_key = getch();
	printf("%c", free_key);
	delay(500);
	menu();

}

void user_information_management_system_menu(void)//����Ա�汾�û���Ϣ����ϵͳ�˵�����
{
	system("cls");
	printf(" __________________________________________________\n");
	printf(" ______________�������û���Ϣ����ϵͳ______________\n");
	printf(" __________________________________________����Ա��\n");
	printf("\t\t ��ѡ����������\t\t\t\n");
	printf(" __________________________________________________\n");
	printf("|                                                  |\n");
	printf("|    1.¼���û���Ϣ                                |\n");
	printf("|                                                  |\n");
	printf("|    2.��ӡ�û���Ϣ                                |\n");
	printf("|                                                  |\n");
	printf("|    3.ͳ���û�����                                |\n");
	printf("|                                                  |\n");
	printf("|    4.�����û���Ϣ                                |\n");
	printf("|                                                  |\n");
	printf("|    5.�޸��û���Ϣ                                |\n");
	printf("|                                                  |\n");
	printf("|    6.ɾ���û���Ϣ                                |\n");
	printf("|                                                  |\n");
	printf("|    7.������Ϣ�������                            |\n");
	printf("|                                                  |\n");
	printf("|__________________________________________________|\n");
	management_system_choose();
}

void management_system_choose(void) //����Ա�汾�û���Ϣ����ϵͳѡ����
{
	Node* head = (Node*)malloc(sizeof(Node));//����ͷ���
	head->next = NULL;
	loadList(head, "Customer.txt");
	char flag;
	printf("����������ѡ�");
	flag = getch();
	printf("%c", flag);
	delay(100);
	while (flag != '1' && flag != '2' && flag != '3' && flag != '4' && flag != '5' && flag != '6' && flag != '7')
	{
		printf("\n�������ʾ������'1'��'2'��'3'��'4'��'5'��'6'��'7'��");
		flag = getch();
		printf("%c", flag);
		delay(100);
	}
	switch (flag)
	{
	case '1': additem(head); //¼���û���Ϣ
		break;
	case '2': showallitem(head); //��ӡ�û���Ϣ
		break;
	case '3': count(head);//ͳ���û�����
		break;
	case '4': seatchitem(head);//�����û���Ϣ
		break;
	case '5':modify_menu_pre(head);//�޸��û���Ϣ		
		break;
	case '6': deletecustomer(head);//ɾ���û���Ϣ		
		break;
	case '7': system("cls"); //������Ϣ�������		
		printf("���ڷ��ء�����������");
		delay(500);
		administerator_personal_information();
		break;
	default:
		break;
	}
}

void additem(Node* head) //����Ա����û���Ϣ
{
	Node* fresh = (Node*)malloc(sizeof(Node));
	fresh->next = NULL;
	system("cls");
	char free_key;
	printf("�������ʾ��������Ҫ¼����û���Ϣ��");

	printf("\n�������û��˺ţ�����С��6�ַ������ô���10�ַ���:");											//
	clearInputBuffer();
	gets_s(fresh->cus.id, 30);
	while (!determine_id_passward(fresh->cus.id))
	{
		printf("\n��ʽ���ԣ������������û��˺ţ�");
		gets_s(fresh->cus.id, 30);
	}

	Node* move = head;
	while (move->next != NULL)
	{
		if (strcmp(move->next->cus.id, fresh->cus.id) == 0)
		{
			printf("\n�����Ѿ��д��˺ţ������������û��˺ţ�");
			fflush(stdin);
			gets_s(fresh->cus.id, 30);
			while (!determine_id_passward(fresh->cus.id))
			{
				printf("\n��ʽ���ԣ������������û��˺ţ�");
				fflush(stdin);
				gets_s(fresh->cus.id, 30);
			}
			move = head;
		}
		else
		{
			move = move->next;
		}
	}

	fresh->cus.appointmentNum[0] = '0'; fresh->cus.appointmentNum[1] = '\0'; fresh->cus.appointmentNum[2] = '\0'; fresh->cus.appointmentNum[3] = '\0'; fresh->cus.appointmentNum[4] = '\0';
	fresh->cus.book_num[0] = 0; fresh->cus.book_num[1] = 0; fresh->cus.book_num[2] = 0; fresh->cus.book_num[3] = 0; fresh->cus.book_num[4] = 0; fresh->cus.book_num[5] = 0;

	printf("\n�������û����루����С��6�ַ������ô���10�ַ�����");
	gets_s(fresh->cus.cus_password, 30);
	while (!determine_id_passward(fresh->cus.cus_password))
	{
		printf("\n��ʽ���ԣ������������û����룺");
		gets_s(fresh->cus.cus_password, 30);
	}

	printf("\n�������û�����������С��2�ַ������ô���20�ַ���:");
	gets_s(fresh->cus.name, 20);
	while (!determine_name(fresh->cus.name))
	{
		printf("\n��ʽ���ԣ������������û�������");
		gets_s(fresh->cus.name, 20);
	}

	printf("\n�������û��Ա�'1'�����У�'0'����Ů)��");
	char gender;
	gender = getchar();
	clearInputBuffer();
	while (gender != '0' && gender != '1')
	{
		printf("\n������'0'��'1'��");
		gender = getchar();
		clearInputBuffer();
	}
	if (gender == '0')
	{
		fresh->cus.gender[0] = '0';
		for (int i = 1; i < 10; i++)
		{
			fresh->cus.gender[i] = '\0';
		}
	}
	else if (gender == '1')
	{
		fresh->cus.gender[0] = '1';
		for (int i = 1; i < 10; i++)
		{
			fresh->cus.gender[i] = '\0';
		}
	}

	printf("\n�������û��ֻ��ţ�11λ���֣���");
	gets_s(fresh->cus.phone, 30);
	while (!determine_phone(fresh->cus.phone))
	{
		printf("\n��ʽ���ԣ������������û��ֻ��ţ�");
		gets_s(fresh->cus.phone, 30);
	}

	printf("\n�������û�����:");
	gets_s(fresh->cus.age, 5);
	while (!determine_age(fresh->cus.age))
	{
		printf("\n��ʽ���ԣ������������û����䣺");
		gets_s(fresh->cus.age, 20);
	}

	printf("\n�������û����(Сд���֣���λС��):");
	gets_s(fresh->cus.cus_balance, 30);
	while ((!is_valid_number(fresh->cus.cus_balance)) || (!(str_to_double(fresh->cus.cus_balance) >= 0)))
	{
		printf("\n��ʽ���ԣ������������û���");
		gets_s(fresh->cus.cus_balance, 30);
	}

	printf("\n�������û�סַ:");
	scanf("%s", &fresh->cus.address);

	printf("\n�������û�����:");
	clearInputBuffer();
	gets_s(fresh->cus.email, 30);
	while (!determine_email(fresh->cus.email))
	{
		printf("\n��ʽ���ԣ������������û����䣺");
		gets_s(fresh->cus.email, 30);
	}

	printf("\n�������û�ˬԼ������Сд���֣�:");
	gets_s(fresh->cus.noShowCount, 5);
	int noShowCount_key = atoi(fresh->cus.noShowCount);
	while (strlen(fresh->cus.noShowCount) == 0 || !all_digits(fresh->cus.noShowCount) || noShowCount_key < 0 || noShowCount_key > 7)
	{
		printf("\n��ʽ���Ի��߳���ˬԼ���ƣ������������û�ˬԼ������");
		gets_s(fresh->cus.noShowCount, 5);
		noShowCount_key = atoi(fresh->cus.noShowCount);
	}

	move = head;
	while (move->next != NULL)
	{
		move = move->next;
	}
	move->next = fresh;
	saveList(head, "Customer.txt");	
	printf("\n�ɹ�����û���Ϣ���������������һ�����棺");
	free_key = getch();
	printf("%c", free_key);
	delay(500);
	user_information_management_system_menu();
}

void showallitem(Node* head)//��ӡ�����û�����Ϣ
{
	system("cls");
	char free_key;
	Node* move = head->next;
	while (move != NULL) 
	{
		printf("�˺ţ�%s \n���룺%s \n������%s \n�Ա�0����Ů��1�����У���%d  \n���䣺%s \n�ֻ��ţ�%s \n��%.2f \nסַ��%s \n���䣺%s \nˬԼ����:%d  \n��Ԥ��������%d", move->cus.id, move->cus.cus_password, move->cus.name, atoi(move->cus.gender), move->cus.age, move->cus.phone, str_to_double(move->cus.cus_balance), move->cus.address, move->cus.email, atoi(move->cus.noShowCount), atoi(move->cus.appointmentNum));
		for (int i = 0; i < 6; i++)
		{
			printf("\n%s ԤԼ����: %d", venue_names[i], move->cus.book_num[i]);
		}
		printf("\n\n\n");
		move = move->next;
	}

	printf("\n�û���Ϣ��ӡ��ϣ��������������һ�����棺");
	free_key = getch();
	printf("%c", free_key);
	delay(500);
	user_information_management_system_menu();
}

void count(Node* head) //ͳ�������û�������
{
	system("cls");
	char free_key;
	int count = 0;
	Node* move = head->next;
	while (move != NULL) 
	{
		count++;
		move = move->next;
	}
	printf("�û���������Ϊ:%d\n", count);
	printf("\n�û�����ͳ����ϣ��������������һ�����棺");
	free_key = getch();
	printf("%c", free_key);
	delay(500);
	user_information_management_system_menu();
}

void seatchitem(Node* head)//�����û���Ϣ
{
	system("cls");
	char free_key;
	printf("\n��������Ҫ��ѯ���û��˺ţ�����С��6�ַ������ô���10�ַ���:");
	char search[30];
	scanf("%s", search);
	while (!determine_id_passward(search))
	{
		printf("\n��ʽ���ԣ�������������Ҫ��ѯ���û��˺ţ�");
		scanf("%s", search);
	}
	Node* move = head;
	while (move->next != NULL) 
	{
		if (strcmp(move->next->cus.id, search) == 0) 
		{
			printf("�˺ţ�%s \n���룺%s \n������%s \n�Ա�0����Ů��1�����У���%d\n���䣺%s\n�ֻ��ţ�%s\n�˺���%.2f\nסַ��%s\n�������䣺%s\nˬԼ������%d \n", move->next->cus.id, move->next->cus.cus_password, move->next->cus.name, atoi(move->next->cus.gender), move->next->cus.age, move->next->cus.phone, str_to_double(move->next->cus.cus_balance), move->next->cus.address, move->next->cus.email, atoi(move->next->cus.noShowCount));
			printf("�Ѿ���ӡ��ϣ��밴�����������һ�����棺");
			free_key = getch();
			printf("%c",free_key);
			printf("\n���ڷ��ء�����������");
			delay(500);
			user_information_management_system_menu();
		}
		move = move->next;
	}
	printf("\nδ�ҵ��û���Ϣ,�밴�����������һ�����棺");
	free_key = getch();
	printf("%c", free_key);
	printf("\n���ڷ��ء�����������");
	delay(500);
	user_information_management_system_menu();
}

void modify_menu_pre(Node* head)//�޸��û���Ϣ����_�ж��û������˺�
{
	system("cls");
	printf(" __________________________________________________\n");
	printf(" ______________�������û���Ϣ����ϵͳ______________\n");
	printf(" __________________________________________����Ա��\n");
	printf("\t\t ��ѡ����������\t\t\t\n");
	printf(" __________________________________________________\n");
	printf("|                                                  |\n");
	printf("|    1.������Ҫ�޸ĵ��û��˺�                      |\n");
	printf("|                                                  |\n");
	printf("|    2.ʹ���ֲ�                                    |\n");
	printf("|                                                  |\n");
	printf("|    3.������һ������                              |\n");
	printf("|                                                  |\n");
	printf("|__________________________________________________|\n");
	modify_choose_pre(head);//pre�汾��Ϣ�޸�ѡ��
}

void modify_choose_pre(Node* head)//pre�汾��Ϣ�޸�ѡ�񡪡����������ж��û��˺ŵĴ�����
{
	Node* move = head;
	char key, free_key;
	printf("���������Ҫѡ�����Ϣ��ѡ����ص�ѡ�");
	char flag;
	flag = getch();
	printf("%c", flag);
	delay(100);
	while (flag != '1' && flag != '2' && flag != '3')
	{
		printf("\n�������ʾ������'1'��'2'��'3'��");
		flag = getch();
		printf("%c", flag);
		delay(100);
	}
	switch (flag)
	{
	case '1':
		system("cls");
		printf("���������û��˺ţ�Ȼ����������ѡ��\n");
		printf("\n��������Ҫ�޸ĵ��û��˺ţ�����С��6�ַ������ô���10�ַ���:");
		char search[30];
		scanf("%s", search);
		while (!determine_id_passward(search))
		{
			printf("\n��ʽ���ԣ��˳��޸�ϵͳ�����Ǽ��������û��˺ţ�");
			printf("\n�˳��޸�ϵͳ�밴'P',���������û��˺��밴'1'��");
			key = getch();
			printf("%c", key);
			while (key != '1' && key != 'p' && key != 'P')
			{
				printf("\n������'1'��'P': ");
				key = getch();
				printf("%c", key);
				delay(100);
			}
			switch (key)
			{
			case'p':printf("\n���ڷ��ء�����������");
				delay(500);
				modify_menu_pre(head);
				break;
			case'P':printf("\n���ڷ��ء�����������");
				delay(500);
				modify_menu_pre(head);
				break;
			case'1':
				break;
			default:
				break;
			}
			printf("\n��������Ҫ�޸���Ϣ���û��˺ţ�����С��6�ַ������ô���10�ַ�����");
			scanf("%s", search);
		}
		while (strcmp(move->next->cus.id, search) != 0)
		{
			if (move->next == NULL)
			{
				printf("\n����û�������˺�,�밴������˳��޸�ϵͳ��");
				free_key = getch();
				printf("%c", free_key);
				delay(500);
				modify_menu_pre(head);
			}
			move = move->next;
		}
		system("cls");
		printf("���ҵ��û��˺ţ�����Ϊ����ת���û���ϸ��Ϣ�޸Ľ��棬���Ժ󡤡���������");
		delay(500);
		modify_choose_real(head, search);
		break;
	case '2':system("cls");
		printf("��ӡ�޸��û���Ϣʹ���ֲ�");
		printf("\n������������޸�ϵͳ��");
		free_key = getch();
		printf("%c", free_key);
		delay(500);
		modify_menu_pre(head);
		break;
	case '3':system("cls");
		printf("���ڷ��أ����Ժ󡤡���������");
		delay(500);
		user_information_management_system_menu();
		break;
	default:
		break;
	}
}

void modify_menu_real(char* id)//�����û��˺�
{
	system("cls");
	printf(" __________________________________________________\n");
	printf(" ______________�������û���Ϣ����ϵͳ______________\n");
	printf(" __________________________________________����Ա��\n");
	printf(" ��ǰ�����޸ĵ��û��˺ţ�%s\n",id);
	printf(" __________________________________________________\n");
	printf("\t\t ��ѡ����������\t\t\t\n");
	printf(" __________________________________________________\n");
	printf("|                                                  |\n");
	printf("|    1.�޸��û�����                                |\n");
	printf("|                                                  |\n");
	printf("|    2.�޸��û�����                                |\n");
	printf("|                                                  |\n");
	printf("|    3.�޸��û�����                                |\n");
	printf("|                                                  |\n");
	printf("|    4.�޸��û����                                |\n");
	printf("|                                                  |\n");
	printf("|    5.�޸��û�סַ                                |\n");
	printf("|                                                  |\n");
	printf("|    6.�޸��û�����                                |\n");
	printf("|                                                  |\n");
	printf("|    7.�޸��û�ˬԼ����                            |\n");
	printf("|                                                  |\n");
	printf("|    8.�޸��û��Ա�                                |\n");
	printf("|                                                  |\n");
	printf("|    9.�޸��û��ֻ���                              |\n");
	printf("|                                                  |\n");
	printf("|    x.������Ϣ�޸Ľ���                            |\n");
	printf("|                                                  |\n");
	printf("|__________________________________________________|\n");
}

void modify_choose_real(Node* head, char* id)//�Ѿ��ж��û���Ϣ���ڣ������û���Ϣ��ϸ�޸Ľ���
{
	Node* move = head;
	while (strcmp(move->cus.id, id) != 0)
	{
		move = move->next;
	}
	while (1)
	{
		modify_menu_real(id);//��ʾѡ�����
		printf("���������Ҫѡ�����Ϣ��ѡ����ص�ѡ�");
		char flag;
		char age[30];
		flag = getch();
		printf("%c", flag);
		delay(100);
		while (flag != '1' && flag != '2' && flag != '3' && flag != '4' && flag != '5' && flag != '6' && flag != '7' && flag != '8' && flag != '9' && flag != 'x'&&flag!='X')
		{
			printf("\n�������ʾ������'1'��'2'��'3'��'4'��'5'��'6'��'7'��'8'��'9'��'x'��");
			flag = getch();
			printf("%c", flag);
			delay(100);
		}
		switch (flag)
		{
		case '1':
			system("cls");
			printf("\n�������û����루����С��6�ַ������ô���10�ַ�����");
			clearInputBuffer();
			gets_s(move->cus.cus_password, 30);
			while (!determine_id_passward(move->cus.cus_password))
			{
				printf("\n��ʽ���ԣ������������û����룺");
				gets_s(move->cus.cus_password, 30);
			}
			return_modify_choose_real(head,id);

			break;
		case '2':
			system("cls");
			printf("\n�������û�����������С��2�ַ������ô���20�ַ���:");
			gets_s(move->cus.name, 20);
			while (!determine_name(move->cus.name))
			{
				printf("\n��ʽ���ԣ������������û�������");
				gets_s(move->cus.name, 20);
			}
			return_modify_choose_real(head, id);

			break;
		case '3':
			system("cls");
			printf("\n�������û�����:");
			scanf("%s",age);
			while (!determine_age(age))
			{
				printf("\n��ʽ���ԣ������������û����䣺");
				scanf("%s", age);
			}
			strcpy(move->cus.age,age);
			return_modify_choose_real(head, id);

			break;
		case '4':
			system("cls");
			printf("\n�������û����(Сд���֣���λС��):"); 
			clearInputBuffer();
			gets_s(move->cus.cus_balance, 30);
			while ((!is_valid_number(move->cus.cus_balance))|| !(str_to_double(move->cus.cus_balance)>=0))
			{
				printf("\n��ʽ���ԣ������������û���");
				gets_s(move->cus.cus_balance, 30);
			}
			return_modify_choose_real(head, id);

			break;
		case '5':
			system("cls");
			printf("\n�������û�סַ:");
			scanf("%s", move->cus.address);
			return_modify_choose_real(head, id);

			break;
		case '6':
			system("cls");
			printf("\n�������û�����:");																				
			clearInputBuffer();
			gets_s(move->cus.email, 30);
			while (!determine_email(move->cus.email))
			{
				printf("\n��ʽ���ԣ������������û����䣺");
				gets_s(move->cus.email, 30);
			}
			return_modify_choose_real(head, id);

			break;
		case'7':

			system("cls");
			printf("\n�������û�ˬԼ������Сд���֣�:");																	
			gets_s(move->cus.noShowCount, 5);
			int noShowCount_key = atoi(move->cus.noShowCount);
			while (strlen(move->cus.noShowCount) == 0 || !all_digits(move->cus.noShowCount) || noShowCount_key < 0 || noShowCount_key > 7)
			{
				printf("\n��ʽ���Ի��߳���ˬԼ���ƣ������������û�ˬԼ������");
				gets_s(move->cus.noShowCount, 5);
				noShowCount_key = atoi(move->cus.noShowCount);
			}
			return_modify_choose_real(head, id);

			break;

		case'8:':
			system("cls");
			printf("\n�������û��Ա�'1'�����У�'0'����Ů)��");
			char gender;
			gender = getchar();
			clearInputBuffer();
			while (gender != '0' && gender != '1')
			{
				printf("\n������'0'��'1'��");
				gender = getchar();
				clearInputBuffer();
			}
			if (gender == '0')
			{
				move->cus.gender[0] = '0';
				for (int i = 1; i < 10; i++)
				{
					move->cus.gender[i] = '\0';
				}
			}
			else if (gender == '1')
			{
				move->cus.gender[0] = '1';
				for (int i = 1; i < 10; i++)
				{
					move->cus.gender[i] = '\0';
				}
			}
			break;
		
		case'9':
			system("cls");
			printf("\n�������û��ֻ��ţ�11λ���֣���");
			gets_s(move->cus.phone, 30);
			while (!determine_phone(move->cus.phone))
			{
				printf("\n��ʽ���ԣ������������û��ֻ��ţ�");
				gets_s(move->cus.phone, 30);
			}
			break;


		case 'x': system("cls"); //������Ϣ�������		
			printf("���ڷ��ء�����������");
			delay(500);
			modify_menu_pre(head);
			break;
	
		case 'X': system("cls"); //������Ϣ�������		
			printf("���ڷ��ء�����������");
			delay(500);
			modify_menu_pre(head);
			break;
		default:
			break;
		}
	}
}

void return_modify_choose_real(Node* head, char* id)//�޸���Ϣ��ϣ����ؽ���
{
	system("cls");
	printf("��Ϣ�޸���ϣ����ڷ����޸�ѡ����棬���Ժ󡤡���������");
	delay(500);
	saveList(head, "Customer.txt");
	modify_choose_real(head, id);
}

void deletecustomer(Node* head) //ɾ���û���Ϣ
{
	char key, free_key;
	Node* move = head;
	system("cls");
	printf("��������Ҫɾ���û���Ϣ���û��˺ţ�����С��6�ַ������ô���10�ַ�����");
	char search[30];
	scanf("%s", search);
	while (!determine_id_passward(search))
	{
		printf("\n��ʽ���ԣ��˳�ɾ��ϵͳ�����Ǽ��������û��˺ţ�");
		printf("�˳�ɾ��ϵͳ�밴'P',���������û��˺��밴'1'��\n");
		key = getch();
		printf("%c", key);
		while (key != '1' && key != 'p' && key != 'P')
		{
			printf("\n������'1'��'P': ");
			key = getch();
			printf("%c", key);
			delay(100);
		}
		switch (key)
		{
		case 'p':
			printf("\n���ڷ��ء�����������");
			delay(500);
			user_information_management_system_menu();
			break;
		case 'P':
			printf("\n���ڷ��ء�����������");
			delay(500);
			user_information_management_system_menu();
			break;
		case '1':
			break;
		default:
			break;
		}
		printf("\n��������Ҫɾ����Ϣ���û��˺ţ�����С��6�ַ������ô���10�ַ�����");
		scanf_s("%s", search);
	}
	
	while (move->next != NULL && strcmp(move->next->cus.id, search) != 0)
	{
		move = move->next;
	}
	if (move->next == NULL)
	{
		printf("\n����û�������˺�,�밴������˳�ɾ��ϵͳ��");
		free_key = getch();
		printf("%c", free_key);
		delay(500);
		user_information_management_system_menu();
	}
	else
	{
		printf("���ҵ��û��˺ţ�����Ϊ��ɾ���û���Ϣ�����Ժ󡤡���������");
		Node* tmp = move->next;
		move->next = tmp->next;
		free(tmp);
		saveList(head, "Customer.txt");
		delay(200);
		printf("\n�ɹ�ɾ���û���Ϣ�����ڷ�����һ�����桤����������");

		delay(300);
		user_information_management_system_menu();
	}
}

void saveList(Node* head, const char* filename)//�����������ļ���
{
	FILE* file = fopen(filename, "wb");
	if (file == NULL)
	{
		printf("�޷����ļ� %s\n", filename);
		return;
	}
	Node* p = head->next;
	while (p != NULL)
	{
		fwrite(&p->cus, sizeof(Customer), 1, file);
		p = p->next;
	}
	fclose(file);
	saveListToFile(head, "customerInfo.txt");
}

void saveList_ad(Node* head, const char* filename)//�����������ļ���
{
	FILE* file = fopen(filename, "wb");
	if (file == NULL)
	{
		printf("�޷����ļ� %s\n", filename);
		return;
	}
	Node* p = head->next;
	while (p != NULL)
	{
		fwrite(&p->cus, sizeof(Customer), 1, file);
		p = p->next;
	}
	fclose(file);
}

void loadList(Node* head, const char* filename)//���ļ��ж�ȡ����
{
	FILE* file = fopen(filename, "rb");
	if (file == NULL)
	{
		printf("�޷����ļ� %s\n", filename);
		return;
	}
	Node* p = head;
	Customer cus;
	while (fread(&cus, sizeof(Customer), 1, file) == 1)
	{
		Node* newNode = (Node*)malloc(sizeof(Node));
		newNode->cus = cus;
		newNode->next = NULL;
		p->next = newNode;
		p = newNode;
	}
	fclose(file);
}

void user_modify_menu(void)//�û����˵�¼�����Ϣ�޸Ľ���
{
	system("cls");
	printf(" __________________________________________________\n");
	printf(" _______________�û�������Ϣ�޸�ϵͳ_______________\n");
	printf(" __________________________________________�û��汾\n");
	printf(" ��ǰ�����޸ĵ��û��˺ţ�%s\n", uesr_id_);		
	printf(" __________________________________________________\n");
	printf("\t\t ��ѡ����������\t\t\t\n");
	printf(" __________________________________________________\n");
	printf("|                                                  |\n");
	printf("|    1.�޸��û�����                                |\n");
	printf("|                                                  |\n");
	printf("|    2.�޸��û�����                                |\n");
	printf("|                                                  |\n");
	printf("|    3.�޸��û�����                                |\n");
	printf("|                                                  |\n");
	printf("|    4.�޸��û�סַ                                |\n");
	printf("|                                                  |\n");
	printf("|    5.�޸��û�����                                |\n");
	printf("|                                                  |\n");
	printf("|    6.�޸��û��Ա�                                |\n");
	printf("|                                                  |\n");
	printf("|    7.�޸��û��ֻ���                              |\n");
	printf("|                                                  |\n");
	printf("|    8.������һ������                              |\n");
	printf("|                                                  |\n");
	printf("|__________________________________________________|\n");
	user_modify_menu_choose();
}

void user_modify_menu_choose(void)//�û�������Ϣ�޸Ľ���ѡ����
{
		printf("���������Ҫѡ�����Ϣ��ѡ����ص�ѡ�");
		Node* head = (Node*)malloc(sizeof(Node));//����ͷ���
		head->next = NULL;
		loadList(head, "Customer.txt");
		Node* move = head;
		char flag;
		char age[30];
		while (strcmp(move->cus.id, uesr_id_) != 0)
		{
			move = move->next;
		}
		flag = getch();
		printf("%c", flag);
		delay(100);
		while (flag != '1' && flag != '2' && flag != '3' && flag != '4' && flag != '5' && flag != '6' && flag != '7' && flag != '8')
		{
			printf("\n�������ʾ������'1'��'2'��'3'��'4'��'5'��'6'��'7'��'8'��");
			flag = getch();
			printf("%c", flag);
			delay(100);
		}
		switch (flag)
		{
		case '1':
	
			system("cls");
			printf("\n�������޸ĺ���û����루����С��6�ַ������ô���10�ַ�����");
			clearInputBuffer();
			gets_s(move->cus.cus_password, 30);
			while (!determine_id_passward(move->cus.cus_password))
			{
				printf("\n��ʽ���ԣ������������û����룺");
				gets_s(move->cus.cus_password, 30);
			}
			printf("�޸���ɣ�����������һ�����档");
			saveList(head, "Customer.txt");
			delay(500);
			user_modify_menu();

	
			break;
		case '2':
	
			system("cls");
			printf("\n�������޸ĺ���û�����������С��2�ַ������ô���20�ַ���:");
			gets_s(move->cus.name, 20);
			while (!determine_name(move->cus.name))
			{
				printf("\n��ʽ���ԣ������������û�������");
				gets_s(move->cus.name, 20);
			}
			printf("�޸���ɣ�����������һ�����档");
			saveList(head, "Customer.txt");
			delay(500);
			user_modify_menu();
			
	
			break;
		case '3':
	
			system("cls");
			printf("\n�������޸ĺ���û�����:");
			scanf("%s", age);
			while (!determine_age(age))
			{
				printf("\n��ʽ���ԣ������������û����䣺");
				scanf("%s", age);
			}
			strcpy(move->cus.age, age);
			printf("�޸���ɣ�����������һ�����档");
			saveList(head, "Customer.txt");
			delay(500);
			user_modify_menu();
			
	
			break;
		
		case '4':
	
			system("cls");
			printf("\n�������޸ĺ���û�סַ:");
			scanf("%s", move->cus.address);
			printf("�޸���ɣ�����������һ�����档");
			saveList(head, "Customer.txt");
			delay(500);
			user_modify_menu();
			
	
			break;
		case '5':
	
			system("cls");
			printf("\n�������޸ĺ���û�����:");
			clearInputBuffer();
			gets_s(move->cus.email, 30);
			while (!determine_email(move->cus.email))
			{
				printf("\n��ʽ���ԣ������������û����䣺");
				
				gets_s(move->cus.email, 30);
			}
			printf("�޸���ɣ�����������һ�����档");
			saveList(head, "Customer.txt");
			delay(500);
			user_modify_menu();
			
	
			break;
		
		case'6':system("cls");
			printf("\n�������޸ĺ���û��Ա�'1'�����У�'0'����Ů)��");
			char gender;
			gender = getchar();
			clearInputBuffer();
			while (gender != '0' && gender != '1')
			{
				printf("\n������'0'��'1'��");
				gender = getchar();
				clearInputBuffer();
			}
			if (gender == '0')
			{
				move->cus.gender[0] = '0';
				for (int i = 1; i < 10; i++)
				{
					move->cus.gender[i] = '\0';
				}
			}
			else if (gender == '1')
			{
				move->cus.gender[0] = '1';
				for (int i = 1; i < 10; i++)
				{
					move->cus.gender[i] = '\0';
				}
			}
			printf("�޸���ɣ�����������һ�����档");
			saveList(head, "Customer.txt");
			delay(500);
			user_modify_menu();
			break;
		
		
		case '7':system("cls");
			printf("\n�������޸ĺ���û��ֻ��ţ�11λ���֣���");
			gets_s(move->cus.phone, 30);
			while (!determine_phone(move->cus.phone))
			{
				printf("\n��ʽ���ԣ������������û��ֻ��ţ�");
				gets_s(move->cus.phone, 30);
			}
			printf("�޸���ɣ�����������һ�����档");
			saveList(head, "Customer.txt");
			delay(500);
			user_modify_menu();
			break;



		case '8': system("cls"); //������Ϣ�޸�ǰ����		
			printf("���ڷ��ء�����������");
			delay(500);
			user_personal_information();
			
			break;
		default:
			break;
		}
}

void ad_login(void)//����Ա��¼
{
	Node* head = (Node*)malloc(sizeof(Node));//����ͷ���
	head->next = NULL;
	loadList(head, "administrator.txt");
	system("cls");
	char free_key;
	printf("\n���������ĵĹ���Ա�˺ţ�����С��6�ַ������ô���10�ַ���:");
	char search[30];
	scanf("%s", search);
	while (!determine_id_passward(search))
	{
		printf("\n��ʽ���ԣ��������������Ա�˺ţ�");
		scanf("%s", search);
	}
	Node* move = head;
	while (move->next != NULL)
	{

		if (strcmp(move->next->cus.id, search) == 0)
		{
			printf("\n�ɹ�ƥ�䵽�����˺ţ�");
			printf("\n\n���������ĵĹ���Ա���루����С��6�ַ������ô���10�ַ���:");
			char search_p[30];
			scanf("%s", search_p);
			while (!determine_id_passward(search_p))
			{
				printf("\n��ʽ���ԣ��������������Ĺ���Ա���룺");
				scanf("%s", search_p);
			}
			if (strcmp(move->next->cus.cus_password, search_p) == 0)
			{
				printf("\n����������ȷ���ѳɹ�����ϵͳ�����Ժ󡤡���������");
				strcpy(ad_id_, search);
				delay(500);
				administrator_menu();
			}
			else
			{
				printf("\n������������밴�����������һ�����棺");
				free_key = getch();
				printf("%c", free_key);
				printf("\n���ڷ��ء�����������");
				delay(500);
				menu();
			}
		}
		move = move->next;
	}
	printf("\nδ�ҵ�����Ա��Ϣ,�밴�����������һ�����棺");
	free_key = getch();
	printf("%c", free_key);
	printf("\n���ڷ��ء�����������");
	delay(500);
	menu();
}

void ad_modify_menu(void)//����Ա���˵�¼�����Ϣ�޸Ľ���
{
	system("cls");
	printf(" __________________________________________________\n");
	printf(" ______________�����ݸ�����Ϣ����ϵͳ______________\n");
	printf(" __________________________________________����Ա��\n");
	printf(" ��ǰ�����޸ĵĹ���Ա�˺ţ�%s\n", ad_id_);
	printf(" __________________________________________________\n");
	printf("\t\t ��ѡ����������\t\t\t\n");
	printf(" __________________________________________________\n");
	printf("|                                                  |\n");
	printf("|    1.�޸Ĺ���Ա����                              |\n");
	printf("|                                                  |\n");
	printf("|    2.�޸Ĺ���Ա����                              |\n");
	printf("|                                                  |\n");
	printf("|    3.�޸Ĺ���Ա����                              |\n");
	printf("|                                                  |\n");
	printf("|    4.�޸Ĺ���Աסַ                              |\n");
	printf("|                                                  |\n");
	printf("|    5.�޸Ĺ���Ա����                              |\n");
	printf("|                                                  |\n");
	printf("|    6.�޸Ĺ���Ա�ֻ���                            |\n");
	printf("|                                                  |\n");
	printf("|    7.������һ������                              |\n");
	printf("|                                                  |\n");
	printf("|__________________________________________________|\n");
	ad_modify_menu_choose();
}

void ad_modify_menu_choose(void)//����Ա������Ϣ�޸Ľ���ѡ����
{
	printf("���������Ҫѡ�����Ϣ��ѡ����ص�ѡ�");
	Node* head = (Node*)malloc(sizeof(Node));//����ͷ���
	head->next = NULL;
	loadList(head, "administrator.txt");
	Node* move = head;
	char flag;
	char age[30];
	while (strcmp(move->cus.id, ad_id_) != 0)
	{
		move = move->next;
	}
	flag = getch();
	printf("%c", flag);
	delay(100);
	while (flag != '1' && flag != '2' && flag != '3' && flag != '4' && flag != '5' && flag != '6' && flag != '7' )
	{
		printf("\n�������ʾ������'1'��'2'��'3'��'4'��'5'��'6'��'7'��");
		flag = getch();
		printf("%c", flag);
		delay(100);
	}
	switch (flag)
	{
	case '1':

		system("cls");
		printf("\n�������޸ĺ�Ĺ���Ա���루����С��6�ַ������ô���10�ַ�����");
		clearInputBuffer();
		gets_s(move->cus.cus_password, 30);
		while (!determine_id_passward(move->cus.cus_password))
		{
			printf("\n��ʽ���ԣ��������������Ա���룺");
			gets_s(move->cus.cus_password, 30);
		}
		printf("�޸���ɣ�����������һ�����档");
		saveList_ad(head, "administrator.txt");
		delay(500);
		ad_modify_menu();


		break;
	case '2':

		system("cls");
		printf("\n�������޸ĺ�Ĺ���Ա����������С��2�ַ������ô���20�ַ���:");
		gets_s(move->cus.name, 20);
		while (!determine_name(move->cus.name))
		{
			printf("\n��ʽ���ԣ��������������Ա������");
			gets_s(move->cus.name, 20);
		}
		printf("�޸���ɣ�����������һ�����档");
		saveList_ad(head, "administrator.txt");
		delay(500);
		ad_modify_menu();


		break;
	case '3':

		system("cls");
		printf("\n�������޸ĺ�Ĺ���Ա����:");
		scanf("%s", age);
		while (!determine_age(age))
		{
			printf("\n��ʽ���ԣ��������������Ա���䣺");
			scanf("%s", age);
		}
		strcpy(move->cus.age, age);
		printf("�޸���ɣ�����������һ�����档");
		saveList_ad(head, "administrator.txt");
		delay(500);
		ad_modify_menu();


		break;

	case '4':

		system("cls");
		printf("\n�������޸ĺ�Ĺ���Աסַ:");
		scanf("%s", move->cus.address);
		printf("�޸���ɣ�����������һ�����档");
		saveList_ad(head, "administrator.txt");
		delay(500);
		ad_modify_menu();


		break;
	case '5':

		system("cls");
		printf("\n�������޸ĺ�Ĺ���Ա����:");
		clearInputBuffer();
		gets_s(move->cus.email, 30);
		while (!determine_email(move->cus.email))
		{
			printf("\n��ʽ��������������������Ա���䣺");
			gets_s(move->cus.email, 30);
		}
		printf("�޸���ɣ�����������һ�����档");
		saveList_ad(head, "administrator.txt");
		delay(500);
		ad_modify_menu();


		break;
	case'6':system("cls");
		printf("\n�������޸ĺ�Ĺ���Ա�ֻ��ţ�11λ���֣���");
		gets_s(move->cus.phone, 30);
		while (!determine_phone(move->cus.phone))
		{
			printf("\n��ʽ���ԣ��������������Ա�ֻ��ţ�");
			gets_s(move->cus.phone, 30);
		}
		printf("�޸���ɣ�����������һ�����档");
		saveList_ad(head, "administrator.txt");
		delay(500);
		ad_modify_menu();
		break;


	case '7': system("cls"); //������Ϣ�޸�ǰ����		
		printf("���ڷ��ء�����������");
		delay(500);
		administerator_personal_information();

		break;
	default:
		break;
	}
}

void user_read_info(void)//�û��鿴������Ϣ
{
	Node* head = (Node*)malloc(sizeof(Node));//����ͷ���
	head->next = NULL;
	loadList(head, "Customer.txt");
	Node* move = head;
	char key;
	system("cls");
	while (strcmp(move->cus.id, uesr_id_) != 0)
	{
		move = move->next;
	}
	printf("�˺ţ�%s \n���룺%s \n������%s  \n�Ա�(0����Ů��1������)��%d \n�ֻ��ţ�%s \n���䣺%s\n�˺���%.2f\nסַ��%s\n�������䣺%s\nˬԼ������%d \n��ԤԼ������%d", move->cus.id, move->cus.cus_password, move->cus.name, atoi(move->cus.gender), move->cus.phone, move->cus.age, str_to_double(move->cus.cus_balance), move->cus.address, move->cus.email, atoi(move->cus.noShowCount), atoi(move->cus.appointmentNum));
	for (int i = 0; i < 6; i++)
	{
		printf("\n%s ԤԼ����: %d", venue_names[i], move->cus.book_num[i]);
	}
	printf("\n\n�Ѿ���ӡ��ϣ��밴�����������һ�����棺");
	key = getch();
	printf("%c",key);
	delay(500);
	user_personal_information();
}

void ad_read_info(void)//����Ա�鿴������Ϣ														
{
	Node* head = (Node*)malloc(sizeof(Node));//����ͷ���
	head->next = NULL;
	loadList(head, "administrator.txt");
	Node* move = head;
	char key;
	while (strcmp(move->cus.id, ad_id_) != 0)
	{
		move = move->next;
	}
	system("cls");
	printf("�˺ţ�%s \n���룺%s \n������%s \n�ֻ��ţ�%s \n���䣺%s\nסַ��%s\n�������䣺%s\n", move->cus.id, move->cus.cus_password, move->cus.name, move->cus.phone, move->cus.age, move->cus.address, move->cus.email);
	if (strcmp(move->cus.id, "11111111") == 0)
	{
		printf("�������ݣ����� 1");
	}
	if (strcmp(move->cus.id, "22222222") == 0)
	{
		printf("�������ݣ����� 2");
	}
	if (strcmp(move->cus.id, "33333333") == 0)
	{
		printf("�������ݣ����� 3");
	}
	printf("\n�Ѿ���ӡ��ϣ��밴�����������һ�����棺");
	key = getch();
	printf("%c", key);
	delay(500);
	administerator_personal_information();
}

bool is_valid_number(char* str) //�ж��ַ������������ֵΪ��������С��
{
	int dot_count = 0;
	for (int i = 0; str[i] != '\0'; i++)
	{
		if (str[i] == '.')
		{
			dot_count++;
			if (dot_count > 1)
			{
				return false;
			}
		}
		else if (!isdigit(str[i]))
		{
			return false;
		}
	}
	return true;
}

bool all_digits(char* str) //�ж������ڴ洢���ַ�ȫ��������
{
	for (int i = 0; str[i] != '\0'; i++)
	{
		if (!isdigit(str[i]))
		{
			return false;
		}
	}
	return true;
}

int count_strings(char* strings) //��������Ԫ�ظ���
{
	int count = 0;
	while (strings[count] != NULL)
	{
		count++;
	}
	return count;
}

int determine_id_passward(char* strings)//�ж��û����������ʽ����
{
		int length = strlen(strings);
		if (length < 6 || length > 10)
		{
			return 0;
		}
		for (int i = 0; i < length; i++)
		{
			if (!isalnum(strings[i]))
			{
				return 0;
			}
		}
		return 1;
}

int determine_name(char* strings)//�ж��û����ָ�ʽ����
{
	int key = count_strings(strings);
	if (key <= 20 && key >= 2)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int  determine_age(char* strings)//�ж��û������ʽ����
{
	int age = atoi(strings);
	if (!all_digits(strings))
	{
		return 0;
	}
	else if (age > 150 || age < 0)
	{
		return 0;
	}
	return 1;
}

bool determine_email(char* email) //�ж������ʽ����
{
	int at = -1;
	int dot = -1;
	int len = strlen(email);
	for (int i = 0; i < len; i++)
	{
		if (email[i] == '@')
		{
			at = i;
		}
		else if (email[i] == '.')
		{
			dot = i;
		}
	}
	if (at == -1 || dot == -1)
	{
		return false;
	}
	if (at > dot)
	{
		return false;
	}
	if (at != 3 || dot - at != 4 || len - dot != 4)
	{
		return false;
	}
	for (int i = 0; i < at; i++)
	{
		if (!isalnum(email[i]))
		{
			return false;
		}
	}
	for (int i = at + 1; i < dot; i++)
	{
		if (!isalnum(email[i]))
		{
			return false;
		}
	}
	for (int i = dot + 1; i < len; i++)
	{
		if (!isalnum(email[i]))
		{
			return false;
		}
	}
	return true;
}

bool determine_phone(char* str)
{
	int len = strlen(str);
	if (len != 11)
	{
		return false;
	}
	for (int i = 0; i < len; i++)
	{
		if (!isdigit(str[i]))
		{
			return false;
		}
	}
	return true;
}

void clearInputBuffer() //����gets_s()���µĻ��з�
{
	char c;
	while ((c = getchar()) != '\n' && c != EOF);
}

double str_to_double(char* str)//�����ת����˫����С��
{
	double num;
	sscanf(str, "%lf", &num);
	return (double)((int)(num * 100 + 0.5)) / 100;
}

void saveListToFile(Node* head, const char* filename) //���������ݴ洢�����������ļ���
{
	int numCustomers = 0;
	Node* move = head;
	FILE* file = fopen(filename, "w");
	if (file == NULL)
	{
		printf("\n�ļ���ʧ�ܣ�");
	}
	while (move->next != NULL)
	{
		move = move->next;
		fprintf(file, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%d,%d,%d,%d,%d,%d\n",
			move->cus.age, move->cus.id, move->cus.cus_password,
			move->cus.name, move->cus.gender,
			move->cus.phone, move->cus.email,
			move->cus.cus_balance, move->cus.address,
			move->cus.noShowCount, move->cus.appointmentNum,
			move->cus.book_num[0], move->cus.book_num[1],
			move->cus.book_num[2], move->cus.book_num[3],
			move->cus.book_num[4], move->cus.book_num[5]);
	}
	fclose(file);
}