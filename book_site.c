#include<stdio.h>
#include"info_management.h"
#include"delay.h"
#include"site_search.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>
#include <wchar.h>
#include"book_site.h"
#include"user.h"

extern char uesr_id_[30];
char dates[7][15];// �洢���ڵ��ַ�������
struct Order orders[100];
int orderNum = 0;																					//order
const char* venue_names[] = { "���ೡ��1�ų�","���ೡ��2�ų�","��Ӿ����1�ų�","��Ӿ����2�ų�","���ⳡ��1�ų�","���ⳡ��2�ų�" };
const char* hall_names[] = { "���ೡ��","��Ӿ����","���ⳡ��" };
int lineNumber = 1;//��¼�û���������

void calculateDates() //����ʱ��
{
	// ��ȡ��ǰ����
	time_t t = time(NULL);
	struct tm* tm_info = localtime(&t);

	// ���㲢�洢����
	for (int i = 0; i < 7; i++) {
		tm_info->tm_mday++; // ����һ��
		mktime(tm_info);
		strftime(dates[i], sizeof(dates[i]), "%m-%d", tm_info); // ��ʽ������Ϊ"MM-DD"
	}
}

int isInteger(const char* input) //��֤����
{
	for (int i = 0; input[i] != '\0'; i++) 
	{
		if (input[i] < '0' || input[i] > '9') 
		{
			return 0; // ��������
		}
	}
	return 1; // ������
}  // ����һ����������֤�����Ƿ�Ϊ����

void saveOrderToFile(const char* ID, const char* name, const char* age, const char* gender, const char* orderNumber, const char* location)  //���涩����Ϣ
{ 
	FILE* file = fopen("orderInformation.txt", "a"); // ��׷��ģʽ���ļ�
	if (file == NULL) 
	{
		printf("���ļ�ʱ��������\n");
		return;
	}
	fprintf(file, "\n");
	fprintf(file, "%s,%s,%s,%s,%s,%s\n", ID, name, age, gender, orderNumber, location);
	fclose(file);
}

void book_f()//Ԥ��������֤�ӽ��뺯��
{
	Customer customer;
	int authResult = authenticateUser(uesr_id_, &customer);
	int canContinueBooking = checkAppointmentLimit(&customer);//Ԥ������δ����3�����Խ���Ԥ��
	if (authResult == -1)//ˬԼ��������3
	{
		system("cls");
		printf("\n����ˬԼ�����Ѿ��������Σ���ʱ�޷�ԤԼ���أ����������ݹ���Ա����ˬԼ��������!");
		delay(500);
		printf("\n�밴������˳�Ԥ��ϵͳ��");
		char key;
		key = getch();
		printf("%c",key);
		printf("\n\n���ڰ�ȫ�˳�ϵͳ�����Ժ󡤡���������");
		delay(500);
		reserve_message();
	}
	else if(canContinueBooking == 0)
	{
		system("cls");
		printf("\n�����ݹ涨���ͬʱԤ���������ݣ����Ѿ�Ԥ�����������ݣ�");
		delay(500);
		printf("\n�밴������˳�Ԥ��ϵͳ��");
		char key;
		key = getch();
		printf("%c", key);
		printf("\n\n���ڰ�ȫ�˳�ϵͳ�����Ժ󡤡���������");
		delay(500);
		reserve_message();
	}
	bookCourt(&customer);
	printf("\n�����ָ������밴�����������һ�����棺");
	char key;
	key = getch();
	printf("%c", key);
	delay(200);
	system("cls");
	printf("���ڷ��أ����Ժ󡤡���������");
	delay(300);
	reserve_message();
}

int authenticateUser(const char* username, Customer* customer)//ƥ���û��˺ţ��洢������Ϣ����֤ˬԼ����С����
{
	FILE* file = fopen("customerInfo.txt", "r");
	if (file == NULL)
	{
		printf("�޷����û���Ϣ�ļ�\n");
		return 0; // �ļ���ʧ�ܣ���֤ʧ��
	}
	char line[256]; // ����ÿ�в�����256���ַ�
	while (fgets(line, sizeof(line), file) != NULL)
	{
		char* token = strtok(line, ",");
		if (token != NULL)
		{
			strcpy(customer->age, token);
			token = strtok(NULL, ",");
			if (token != NULL)
			{
				strcpy(customer->id, token);
				if (strcmp(username, customer->id) == 0)//������Ӧ���û���
				{
					token = strtok(NULL, ",");
					if (token != NULL)
					{
						strcpy(customer->cus_password, token);
						token = strtok(NULL, ",");
						if (token != NULL)
						{
							strcpy(customer->name, token);
							token = strtok(NULL, ",");
							if (token != NULL)
							{
								strcpy(customer->gender, token); // ��ȡ�Ա��ֶ�
								token = strtok(NULL, ",");
								if (token != NULL)
								{
									strcpy(customer->phone, token);
									token = strtok(NULL, ",");
									if (token != NULL)
									{
										strcpy(customer->email, token);
										token = strtok(NULL, ",");
										if (token != NULL)
										{
											strcpy(customer->cus_balance, token);
											token = strtok(NULL, ",");
											if (token != NULL)
											{
												strcpy(customer->address, token);
												token = strtok(NULL, ",");
												if (token != NULL)
												{
													strcpy(customer->noShowCount, token);
													// ���ˬԼ�����Ƿ����3
													if (atoi(customer->noShowCount) > 3)
													{
														fclose(file);
														return -1; // ˬԼ�������࣬�û���֤ʧ�ܣ�����-1
													}
													token = strtok(NULL, ",");
													if (token != NULL)
													{
														strcpy(customer->appointmentNum, token);
														// ����������ݵ�ԤԼ����
														for (int i = 0; i < 6; i++)
														{
															token = strtok(NULL, ",");
															if (token != NULL)
															{
																customer->book_num[i] = atoi(token);
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
						fclose(file);
						return 1; // �û���֤�ɹ�
					}
				}
				else
				{
					lineNumber++;
				}
			}
		}
	}
	fclose(file);
	return 0; // �û���֤ʧ��
}

int checkAppointmentLimit(const Customer* customer)//��֤��ԤԼ����С������������������ԤԼ
{
	int numAppointments = atoi(customer->appointmentNum);
	return (numAppointments >= 3) ? 0 : 1;
}

void showOrders_menu()//��ӡ��ʷ����������ȡ��Ԥ��Ԥ����
{
	delay(100);
	system("cls");
	Customer customer;
	orderNum = readOrder();
	authenticateUser_history(uesr_id_, &customer);//���ļ��л�ȡ���û���ȫ����Ϣ
	showOrders(uesr_id_, &customer);//�����ӡ��ʷ������ȡ��Ԥ��ѡ��
	delay(500);
	printf("������ִ����ϣ��밴�����������һ������:");
	char free_key;
	free_key = getch();
	printf("%c",free_key);
	printf("\n���ڰ�ȫ���أ����Ժ󡤡���������");
	delay(500);
	reserve_message();
}

void showOrders(char username[], Customer* customer)//��ӡ��ʷԤԼ������ȡ��Ԥ��
{
	readFromFile();
	int userOrderNum = 0;
	struct Order userOrder[100];
	if (orderNum > 0)
	{
		for (int i = 0; i < orderNum; i++)														//ordernum
		{
			if (strcmp(username, orders[i].ID) == 0)
			{
				userOrder[userOrderNum] = orders[i];
				userOrderNum++;
			}
		}
	}
	if (userOrderNum == 0)
	{
		printf("�û���ԤԼ��¼\n");
		return;
	}
	// �����������洢��ѡ������ԤԼ�������ں�ʱ��
	char selectedDateTime[100][1024];
	int selectedDateTimeCount = 0;
	for (int i = 0; i < userOrderNum; i++)
	{
		printf("\n");
		printf("���:%d\n", (i + 1));
		printf("ID��%s\n", userOrder[i].ID);
		printf("������%s\n", userOrder[i].name);
		printf("������ţ�%s\n", userOrder[i].orderNumber);
		char locationInfo[1024];
		strcpy(locationInfo, userOrder[i].location);
		char* str1 = strtok(locationInfo, "_");
		if (str1 != NULL)
		{
			// ���ݡ����ء����ڡ�ʱ���
			printf("���ݣ�%s\n", str1);
			str1 = strtok(NULL, "_");
			if (NULL != str1)
			{
				printf("����:%s\n", str1);
				str1 = strtok(NULL, "_");

				if (NULL != str1)
				{
					char date[1024]; // ���һ���������洢����
					strcpy(date, str1); // �������ڵ� 'date' ����
					printf("����:%s\n", date); // ��ӡ����
					// ��ʽ�����ڣ�ȷ���·ݺ�����Ϊ��λ��
					char formattedDate[1024];
					if (strlen(date) == 1)
					{
						snprintf(formattedDate, sizeof(formattedDate), "0%s", date);
					}
					else
					{
						snprintf(formattedDate, sizeof(formattedDate), "%s", date);
					}

					str1 = strtok(NULL, "_");
					if (NULL != str1)
					{
						printf("ʱ���:%s\n", str1);
						// ��ʽ��ʱ��ε�������Ϣ
						// �洢���ں�ʱ�䵽������
						snprintf(selectedDateTime[selectedDateTimeCount], sizeof(selectedDateTime[selectedDateTimeCount]), "%s %s", formattedDate, str1);
						selectedDateTimeCount++;
					}
				}
			}
		}
	}
	int num = 0;
	int j;
	int k;
	while (1)
	{
		printf("������Ҫȡ���Ķ�����ţ���0���أ�");														//�˴�������
		if (scanf("%d", &num) != 1)
		{
			printf("��Ч�����룬���������롣\n");
			while (getchar() != '\n');  // ������뻺����
			continue;
		}
		if (num == 0) // �û�ѡ��0����
		{
			system("CLS");
			printf("���ڷ�����һ�����棬���Ժ󡤡���������");												//Ԥ����ʷΨһһ�����Է�����һ������ĵط�
			delay(500);
			reserve_message();
		}

		if (num > 0 && num <= userOrderNum)
		{
			// �û���������Ч�Ķ�����ţ�����ȡ������
			// ��ȡ��ǰʱ��
			time_t now;
			struct tm* current_time;
			time(&now);
			current_time = localtime(&now);
			// ������֪ʱ���ַ���
			int month, day, startHour, startMinute, endHour, endMinute;
			sscanf(selectedDateTime[num - 1], "%d-%d %d:%d - %d:%d", &month, &day, &startHour, &startMinute, &endHour, &endMinute);
			// ��ȡ��ǰ���
			int currentYear = current_time->tm_year + 1900;
			// ������������֪���ں�ʱ���tm�ṹ��
			struct tm known_time =
			{
				.tm_year = currentYear - 1900, // ʹ�õ�ǰ���
				.tm_mon = month - 1,           // �·ݴ�0��ʼ
				.tm_mday = day,
				.tm_hour = startHour,
				.tm_min = startMinute,
				.tm_sec = 0 // ������Ϊ0����Ϊ������û������
			};
			// ת��Ϊtime_t����
			time_t known_time_t = mktime(&known_time);
			// ����ʱ���
			double time_difference = difftime(known_time_t, now);
			if (time_difference < 0)
			{
				printf("�Ѿ�����Ԥ��ʱ�䣬����ȡ��������\n");
			}
			// ���ʱ���С��1Сʱ��3600�룩����ֹ��������
			else if (time_difference < 3600)
			{
				printf("ȡ��ʧ�ܣ���Ϊ����Ԥ��ʱ�䲻��1Сʱ��\n");
			}
			else
			{
				// �û���������Ч�Ķ�����ţ���������ȡ���������߼�
				printf("��ѡ��ȡ���Ķ�����ԤԼ�������ں�ʱ�䣺%s\n", selectedDateTime[num - 1]);
				// ��ȡ��ǰʱ��
				time_t now;
				struct tm* current_time;
				time(&now);
				current_time = localtime(&now);
				// ������֪ʱ���ַ���
				int month, day, startHour, startMinute, endHour, endMinute;
				sscanf(selectedDateTime[num - 1], "%d-%d %d:%d - %d:%d", &month, &day, &startHour, &startMinute, &endHour, &endMinute);
				// ��ȡ��ǰ���
				int currentYear = current_time->tm_year + 1900;
				// ������������֪���ں�ʱ���tm�ṹ��
				struct tm known_time =
				{
					.tm_year = currentYear - 1900, // ʹ�õ�ǰ���
					.tm_mon = month - 1,           // �·ݴ�0��ʼ
					.tm_mday = day,
					.tm_hour = startHour,
					.tm_min = startMinute,
					.tm_sec = 0 // ������Ϊ0����Ϊ������û������
				};
				// ת��Ϊtime_t����
				time_t known_time_t = mktime(&known_time);
				// ����ʱ���
				double time_difference = difftime(known_time_t, now);
				// ���ʱ���
				/*printf("ʱ���Ϊ%.0lf��\n", time_difference);*/
				if ((time_difference) < 0)
				{
					printf("����ȡ������Ϊ�����Ѿ���ʼʹ�á�\n");
					printf("������ִ����ϣ��밴�����������һ������:");
					char free_key;
					free_key = getch();
					printf("%c", free_key);
					printf("\n���ڰ�ȫ���أ����Ժ󡤡���������");
					delay(500);
					reserve_message();
				}
				// ���ʱ���С��1Сʱ��3600�룩����ֹ��������
				if ((time_difference) < 3600)
				{
					printf("ȡ��ʧ�ܣ���Ϊ����Ԥ��ʱ�䲻��1Сʱ��\n");
					printf("������ִ����ϣ��밴�����������һ������:");
					char free_key;
					free_key = getch();
					printf("%c", free_key);
					printf("\n���ڰ�ȫ���أ����Ժ󡤡���������");
					delay(500);
					reserve_message();


				}
				// ���ʱ�����ڵ���24Сʱ�����Լ�������
				printf("���Լ������г�����Ϊ����Ԥ��ʱ�䳬��1Сʱ��\n");
				char cancelLation[100];
				for (j = 0; j < orderNum; j++)															//ordernum
				{
					if (strcmp(orders[j].ID, userOrder[num - 1].ID) == 0 && strcmp(orders[j].name, userOrder[num - 1].name) == 0
						&& strcmp(orders[j].orderNumber, userOrder[num - 1].orderNumber) == 0 && strcmp(orders[j].location, userOrder[num - 1].location) == 0)
					{
						strcpy(cancelLation, orders[j].location);
						for (k = j; k < orderNum - 1; k++)												//ordernum
						{
							orders[k] = orders[k + 1];
						}
						orderNum--;
						break;
					}
				}
				saveOrder();
				int hallIndex;
				int courtIndex;
				sscanf(userOrder[num - 1].location, "Hall%d_%d", &hallIndex, &courtIndex);
				hallIndex -= 1;
				courtIndex -= 1;
				int rentPerHour = halls[hallIndex].courts[courtIndex].rentRerHour;
				
				Node* head = (Node*)malloc(sizeof(Node));//����ͷ���
				head->next = NULL;
				loadList(head, "Customer.txt");
				Node* move = head;
				char age[30];
				while (strcmp(move->cus.id, uesr_id_) != 0)
				{
					move = move->next;
				}
				move->cus.cus_balance;					//�޸����
				double balance = str_to_double(move->cus.cus_balance);
				balance = balance + rentPerHour;
				sprintf(move->cus.cus_balance, "%.2lf", balance);
				move->cus.appointmentNum;//�޸���Ԥ������
				int appointmentNum_ = atoi(move->cus.appointmentNum);
				appointmentNum_ = appointmentNum_ - 1;
				sprintf(move->cus.appointmentNum, "%.d", appointmentNum_);
				move->cus.book_num[courtIndex]--;//�޸ĸ������ص�Ԥ������
				saveList(head, "Customer.txt");//���������ļ�˫����
				system("cls");
				printf("����ִ��ȡ��������Ժ󡤡���������");

				
				int cancellationHallNumber;
				int cancellationVenueNumber;
				char cancellationTimeRange[10];
				int cancellationHour;
				sscanf(cancelLation, "Hall%d_%d_%9[^_]_%d", &cancellationHallNumber, &cancellationVenueNumber, cancellationTimeRange, &cancellationHour);
				int difference = calculateDateDifferenceFromToday(cancellationTimeRange);
				halls[cancellationHallNumber - 1].courts[cancellationVenueNumber - 1].time[difference - 1][cancellationHour - 6]--;
				saveToFile();

				delay(500);
				printf("\nȡ���ɹ�!\n");
				printf("������ִ����ϣ��밴�����������һ������:");
				char free_key;
				free_key = getch();
				printf("%c", free_key);
				printf("\n���ڰ�ȫ���أ����Ժ󡤡���������");
				delay(500);
				reserve_message();
			}
		}
		else
		{
			printf("��Ч�Ķ�����ţ����������롣\n");
		}
	}
}

int authenticateUser_history(const char* username, Customer* customer)//ƥ���û��˺ţ��洢������Ϣ������֤ˬԼ����
{
	FILE* file = fopen("customerInfo.txt", "r");
	if (file == NULL)
	{
		printf("�޷����û���Ϣ�ļ�\n");
		return 0; // �ļ���ʧ�ܣ���֤ʧ��
	}
	char line[256]; // ����ÿ�в�����256���ַ�
	while (fgets(line, sizeof(line), file) != NULL)
	{
		char* token = strtok(line, ",");
		if (token != NULL)
		{
			strcpy(customer->age, token);
			token = strtok(NULL, ",");
			if (token != NULL)
			{
				strcpy(customer->id, token);
				if (strcmp(username, customer->id) == 0)//������Ӧ���û���
				{
					token = strtok(NULL, ",");
					if (token != NULL)
					{
						strcpy(customer->cus_password, token);
						token = strtok(NULL, ",");
						if (token != NULL)
						{
							strcpy(customer->name, token);
							token = strtok(NULL, ",");
							if (token != NULL)
							{
								strcpy(customer->gender, token); // ��ȡ�Ա��ֶ�
								token = strtok(NULL, ",");
								if (token != NULL)
								{
									strcpy(customer->phone, token);
									token = strtok(NULL, ",");
									if (token != NULL)
									{
										strcpy(customer->email, token);
										token = strtok(NULL, ",");
										if (token != NULL)
										{
											strcpy(customer->cus_balance, token);
											token = strtok(NULL, ",");
											if (token != NULL)
											{
												strcpy(customer->address, token);
												token = strtok(NULL, ",");
												if (token != NULL)
												{
													strcpy(customer->noShowCount, token);
													token = strtok(NULL, ",");
													if (token != NULL)
													{
														strcpy(customer->appointmentNum, token);
														// ����������ݵ�ԤԼ����
														for (int i = 0; i < 6; i++)
														{
															token = strtok(NULL, ",");
															if (token != NULL)
															{
																customer->book_num[i] = atoi(token);
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
						fclose(file);
						return 1; // �û���֤�ɹ�
					}
				}
				else
				{
					lineNumber++;
				}
			}
		}
	}
	fclose(file);
	return 0; // �û���֤ʧ��
}

void saveOrder()//��order���ݴ���ļ�

{
	FILE* file = fopen("orderInformation.txt", "w");
	if (file == NULL)
	{
		printf("�޷����ļ� orderInformation.txt\n");
		return;
	}
	for (int i = 0; i < orderNum; i++)//��orders����д���ļ�													//ordernum
	{
		fprintf(file, "%s,%s,%d,%d,%s,%s\n", orders[i].ID, orders[i].name, orders[i].age, orders[i].gender, orders[i].orderNumber, orders[i].location);
	}
	fclose(file);//�ر��ļ�
}

int readOrder()//�Ķ�order�ļ�����������Ϣ�ļ�
{
	int orderNum_ = 0;
	FILE* file = fopen("orderInformation.txt", "r");
	if (file == NULL)
	{
		printf("�޷����ļ� orderInformation.txt\n");
		return;
	}
	char str[1000];
	while (fgets(str, sizeof(str), file))
	{
		if (str[0] == '\n')
		{
			continue;
		}
		// �����ŷָ��ַ���
		char* token = strtok(str, ",");
		if (token != NULL)
		{
			strcpy(orders[orderNum_].ID, token);
			token = strtok(NULL, ",");
			if (token != NULL)
			{
				strcpy(orders[orderNum_].name, token);
				token = strtok(NULL, ",");
				if (token != NULL)
				{
					// ��ȡ����
					orders[orderNum_].age = atoi(token); // ʹ��atoi���ַ���ת��Ϊ����
					token = strtok(NULL, ",");
					if (token != NULL)
					{
						// ��ȡ�Ա�
						orders[orderNum_].gender = atoi(token); // ʹ��atoi���ַ���ת��Ϊ����
						token = strtok(NULL, ",");
						if (token != NULL)
						{
							strcpy(orders[orderNum_].orderNumber, token);
							token = strtok(NULL, ",");
							if (token != NULL)
							{
								strcpy(orders[orderNum_].location, token);
								orderNum_++;
							}
						}
					}
				}
			}
		}
	}
	// �ر��ļ�
	fclose(file);
	return orderNum_;
}

void bookCourt(Customer* customer)//Ԥ������
{
	struct Order order;
	calculateDates(); // ��������
	readFromFile();
	int hallIndex;  // ҪԤ���Ĵ�������
	int courtIndex;   // ҪԤ���ĳ�������
	int dayIndex;   // ҪԤ������������
	int timeSlot;   // ҪԤ����ʱ�������
	int booked = 0;  // ���ڱ���Ƿ�ɹ�Ԥ��
	do {
		// ��ʾ������Ϣ��ѡ��
		system("cls");
		printf("��ѡ�����б�\n");
		printf("1.���ೡ��\n");
		printf("2.��Ӿ����\n");
		printf("3.���ⳡ��\n");
		printf("4.�˳�Ԥ��ϵͳ\n");
		char flag;
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
		if (flag == '4')
		{
			system("cls");
			printf("���ڷ�����һ�����棬���Ժ󡤡���������");
			delay(500);
			reserve_message();
		}
		hallIndex = flag - '0';
		hallIndex--;  // ����Ϊ��������
		// ��ʾ������Ϣ��ѡ��
		printf("\n\n��ѡ�����б�\n");
		for (int i = 0; i < halls[hallIndex].NumOfCourt; i++)
		{
			printf("%d. ����%d\n", i + 1, i + 1);
		}
		char input[30];
		// ѭ���ȴ���Ч�ĳ�������
		while (1)
		{
			printf("��ѡ��ҪԤ���ĳ��ر�� (����0����ѡ��)��");
			if (scanf("%s", input) != 1 || !isInteger(input))
			{
				printf("��Ч�����룬������ѡ�񳡵ء�\n");
				while (getchar() != '\n');  // ������뻺����
				continue;
			}
			courtIndex = atoi(input);
			if (courtIndex == 0 || (courtIndex >= 1 && courtIndex <= halls[hallIndex].NumOfCourt))
			{
				break;  // ������Ч���˳�ѭ��
			}
			else
			{
				printf("��Ч�����룬������ѡ�񳡵ء�\n");
			}
		}
		if (courtIndex == 0)
		{
			system("cls");  // ����
			continue;  // ����ѡ��
		}
		courtIndex--;  // ����Ϊ��������
		int userAge = atoi(customer->age);
		// ��ȡ��ѡ�񳡹ݵ���С�������������
		int minAge = halls[hallIndex].minAge;
		int maxAge = halls[hallIndex].maxAge;
		if (userAge < minAge || userAge > maxAge)// ���������ж�
		{
			printf("\n��Ǹ����������Ϊ%d�������ϳ��ݵ��������ơ����ݵĿ�������Ϊ%d-%d��\n\n", userAge, minAge, maxAge);
			char key;
			printf("����ѡ�񳡹��밴'1'���˳�Ԥ��ϵͳ�밴'P:'");
			printf("����������ѡ�");
			key = getch();
			printf("%c", key);
			delay(100);
			while (key != '1' && key != 'p' && key != 'P')
			{
				printf("\n�������ʾ������'1'��'P'��");
				key = getch();
				printf("%c", key);
				delay(100);
			}
			if (key == '1')
			{
				system("cls");  // ����
				continue;  // ����ѡ�񳡹�
			}
			if (key == 'p' || key == 'P')
			{
				break;  // �˳�bookCourt����
			}
		}
		int rentPerHour = halls[hallIndex].courts[courtIndex].rentRerHour;
		int userBalance = atoi(customer->cus_balance);// ��������ж�
		if (userBalance < rentPerHour)
		{
			printf("\n��Ǹ���������Ϊ%d��������֧���������%d/h��\n", userBalance, rentPerHour);
			printf("1.����ѡ�񳡹��밴'1'���˳�Ԥ��ϵͳ�밴'P:");
			printf("����������ѡ�");
			char key;
			key = getch();
			printf("%c", key);
			delay(100);
			while (key != '1' && key != 'p' && key != 'P')
			{
				printf("\n�������ʾ������'1'��'P'��");
				key = getch();
				printf("%c", key);
				delay(100);
			}
			if (key == '1')
			{
				system("cls");  // ����
				continue;  // ����ѡ�񳡹�
			}
			if (key == 'p' || key == 'P')
			{
				break;  // �˳�bookCourt����
			}
		}
		printf("\n��ѡ�����б�\n");// ��ʾ������Ϣ��ѡ��
		for (int i = 0; i < 7; i++)
		{
			printf("%d. %s\n", i + 1, dates[i]);
		}
		printf("����������ѡ��(���ڱ��Ϊ1��7����������쿪ʼ�ĵ�һ�쵽������)��");
		char key;
		key = getch();
		printf("%c", key);
		delay(100);
		while (key != '1' && key != '2' && key != '3' && key != '4' && key != '5' && key != '6' && key != '7')
		{
			printf("\n�������ʾ������'1'��'2'��'3'��'4'��'5'��'6'��'7'��");
			key = getch();
			printf("%c", key);
			delay(100);
		}
		dayIndex = key - '0';
		dayIndex--;  // ����Ϊ��������
		printf("\n\n��ѡʱ����б�\n");// ��ʾʱ�����Ϣ��ѡ��
		for (int i = 0; i < 16; i++)
		{
			printf("%d. %02d:00 - %02d:59\n", i + 1, 6 + i, 6 + i);
		}
		// ѭ���ȴ���Ч��ʱ�������
		while (1)
		{
			printf("��ѡ��ҪԤ����ʱ��α�� (����0����ѡ��)��");
			if (scanf("%s", input) != 1 || !isInteger(input))
			{
				printf("��Ч�����룬������ѡ��ʱ��Ρ�\n");
				while (getchar() != '\n');  // ������뻺����
				continue;
			}
			timeSlot = atoi(input);
			if (timeSlot == 0 || (timeSlot >= 1 && timeSlot <= 16))
			{
				break;  // ������Ч���˳�ѭ��
			}
			else
			{
				printf("��Ч�����룬������ѡ��ʱ��Ρ�\n");
			}
		}
		if (timeSlot == 0)
		{
			system("cls");  // ����
			continue;  // ����ѡ��
		}
		timeSlot--;  // ����Ϊ��������
		if (halls[hallIndex].courts[courtIndex].time[dayIndex][timeSlot] >= halls[hallIndex].courts[courtIndex].maxPerson)// ����ʱ����Ƿ��Ѿ�Ԥ����
		{
			printf("\n�ó��ظ�ʱ���Ԥ�������Ѵﳡ���������������ԤԼ�������ػ�����ʱ���\n");
			printf("�밴�����������һ�����棺");
			char key;
			key = getch();
			printf("%c",key);
			delay(200);
			system("cls");
			printf("���ڰ�ȫ�˳�ϵͳ�����Ժ󡤡���������");
			delay(500);
			reserve_message();
		}
		else
		{
			time_t currentTime;// ��ȡ��ǰϵͳ���ں�ʱ��
			struct tm* localTime;
			time(&currentTime);  // ��ȡ��ǰʱ��
			localTime = localtime(&currentTime);  // ת��Ϊ����ʱ��
			int year = localTime->tm_year + 1900;  // �����Ҫ���� 1900
			int month = localTime->tm_mon + 1;      // �·ݴ� 0 ��ʼ����Ҫ���� 1
			int day = localTime->tm_mday;           // ���е���
			int hour = localTime->tm_hour;          // Сʱ
			int minute = localTime->tm_min;         // ����
			// ���ɶ�����ţ���ʽΪ���˿�ID+Ԥ�����ڣ�yyyy:mm:dd:hh:mm��
			char orderNumber[50];
			sprintf(orderNumber, "%s-%04d:%02d:%02d:%02d:%02d", customer->id, year, month, day, hour, minute);
			// ���������Ϣ
			struct order_info order;
			char locationInfo[50];
			// ����������Ϣ�ַ�������ʽΪ��Hall1_1_09-05_07:00 - 07:59
			sprintf(locationInfo, "Hall%d_%d_%s_%02d:%02d - %02d:%02d", hallIndex + 1, courtIndex + 1, dates[dayIndex], 6 + timeSlot, 0, 6 + timeSlot, 59);
			char formattedInfo[1024];
			snprintf(formattedInfo, sizeof(formattedInfo), "%s,%s,%s,%s,%s,%s\n", customer->id, customer->name, customer->age, customer->gender, orderNumber, locationInfo);
			char combinedDateTime[1024];
			//��������Ԥ��������ʱ�䣬����combinedDateTime��
			if (sscanf(formattedInfo, "%[^,],%[^,],%d,%d,%[^,],%[^_]_%[^_]_%[^_]_%[^ ]",
				order.username, order.fullName, &order.age, &order.gender, order.orderNumber, order.venue, order.venueNumber, order.date, order.time) == 9)
			{
				sprintf(combinedDateTime, "%s%s", order.date, order.time);
				printf("\n");
			}
			//��ȡ��Ԥ���ĳ���ʱ�䣬����selectedDateTime[selectedDateTimeCount]�У���0��ʼ����
			readFromFile();
			int userOrderNum = 0;
			orderNum = readOrder();
			struct Order userOrder[100];
			if (orderNum > 0)
			{
				for (int i = 0; i < orderNum; i++)
				{
					if (strcmp(uesr_id_, orders[i].ID) == 0)
					{
						userOrder[userOrderNum] = orders[i];
						userOrderNum++;
					}
				}
			}
			char selectedDateTime[100][1024];// �����������洢��ѡ������ԤԼ�������ں�ʱ��
			int selectedDateTimeCount = 0;
			for (int i = 0; i < userOrderNum; i++)
			{
				char locationInfo[1024];
				strcpy(locationInfo, userOrder[i].location);
				char* str1 = strtok(locationInfo, "_");
				if (str1 != NULL)
				{
					// ���ݡ����ء����ڡ�ʱ���
					str1 = strtok(NULL, "_");
					if (NULL != str1)
					{
						str1 = strtok(NULL, "_");
						if (NULL != str1)
						{
							char date[1024]; // ���һ���������洢����
							strcpy(date, str1); // �������ڵ� 'date' ����
							// ��ʽ�����ڣ�ȷ���·ݺ�����Ϊ��λ��
							char formattedDate[1024];
							if (strlen(date) == 1)
							{
								snprintf(formattedDate, sizeof(formattedDate), "0%s", date);
							}
							else
							{
								snprintf(formattedDate, sizeof(formattedDate), "%s", date);
							}
							str1 = strtok(NULL, "_");
							if (NULL != str1)
							{
								// ��ʽ��ʱ��ε�������Ϣ
								char* hyphenPos = strrchr(str1, '-');
								if (hyphenPos != NULL)
								{
									*hyphenPos = '\0';
								}
								// �洢���ں�ʱ�䵽������
								snprintf(selectedDateTime[selectedDateTimeCount], sizeof(selectedDateTime[selectedDateTimeCount]), "%s%s", formattedDate, str1);
								selectedDateTimeCount++;
							}
						}
					}
				}
			}
			int found = 0; // ���ڱ���Ƿ��ҵ�ƥ�� 
			for (int i = 0; i < selectedDateTimeCount; i++)
			{ 
					if (filter_digits(combinedDateTime) == filter_digits(selectedDateTime[i]))
					{ 
					
						printf("����������Ԥ����������������ͬһʱ��Ԥ���������أ�");
						printf("\n�밴�������ȫ�˳�ϵͳ��");
						char key;
						key = getch();
						printf("%c",key);
						delay(200);
						system("cls");
						printf("\n���ڰ�ȫ�˳�ϵͳ�����Ժ󡤡���������");
						delay(500);
						reserve_message();
					} 
			} 
			printf("Ԥ���ɹ������Ķ�������ǣ�%s\n", orderNumber);//û������ͬʱ��ԤԼ�������أ����гɹ�Ԥ���ж�
			halls[hallIndex].courts[courtIndex].time[dayIndex][timeSlot]++;// ����Ԥ��������Ԥ������
			printf("��Ԥ���ĳ����ǣ�%s�����غţ�%d�����ڣ�%s��ʱ��Σ�%02d:00 - %02d:59\n", hall_names[hallIndex], courtIndex + 1, dates[dayIndex], 6 + timeSlot, 6 + timeSlot);
			booked = 1;  // ���Ϊ�ɹ�Ԥ��
			if (booked)
			{
				char locationInfo[50];
				// ����������Ϣ�ַ�������ʽΪ��Hall1_1_09-05_07:00 - 07:59
				sprintf(locationInfo, "Hall%d_%d_%s_%02d:%02d - %02d:%02d", hallIndex + 1, courtIndex + 1, dates[dayIndex], 6 + timeSlot, 0, 6 + timeSlot, 59);
				saveOrderToFile(customer->id, customer->name, customer->age, customer->gender, orderNumber, locationInfo);
			}
			saveToFile();
			// �ڳɹ�Ԥ�����غ󣬸����û���Ϣ�����浽�ļ�
			Node* head = (Node*)malloc(sizeof(Node));//����ͷ���
			head->next = NULL;
			loadList(head, "Customer.txt");
			Node* move = head;
			char age[30];
			while (strcmp(move->cus.id, uesr_id_) != 0)
			{
				move = move->next;
			}
			move->cus.cus_balance;//�޸����
			double balance = str_to_double(move->cus.cus_balance);
			balance = balance - rentPerHour;
			sprintf(move->cus.cus_balance, "%.2lf", balance);
			move->cus.appointmentNum;//�޸���Ԥ������
			int appointmentNum_ = atoi(move->cus.appointmentNum);
			appointmentNum_ = appointmentNum_ + 1;
			sprintf(move->cus.appointmentNum, "%.d", appointmentNum_);
			move->cus.book_num[courtIndex]++;//�޸ĸ������ص�Ԥ������
			saveList(head, "Customer.txt");//���������ļ�˫����
		}
	} while (!booked);  // ѭ��ֱ���ɹ�Ԥ��Ϊֹ
}

int filter_digits(const char* input) //���ַ����й��˳����ֲ���������
{
	char output[20];
	int j = 0;
	for (int i = 0; i < strlen(input); i++)
	{
		if (isdigit(input[i]))
		{
			output[j++] = input[i];
		}
	}
	output[j] = '\0';
	return atoi(output);
}

void signIn_pre(void)//ǩ��Ԥ����
{

	delay(100);
	system("cls");
	Customer customer;
	orderNum = readOrder();
	authenticateUser_history(uesr_id_, &customer);//���ļ��л�ȡ���û���ȫ����Ϣ
	signIn(uesr_id_, &customer);
	delay(500);
	printf("������ִ����ϣ��밴�����������һ������:");
	char free_key;
	free_key = getch();
	printf("%c", free_key);
	printf("\n���ڰ�ȫ���أ����Ժ󡤡���������");
	delay(500);
	reserve_message();
}

void signIn(char username[], Customer* customer)//ǩ��
{
	readFromFile();
	int userOrderNum = 0;
	struct Order userOrder[100];
	orderNum = readOrder();
	if (orderNum > 0)
	{
		for (int i = 0; i < orderNum; i++)
		{
			if (strcmp(username, orders[i].ID) == 0)
			{
				userOrder[userOrderNum] = orders[i];
				userOrderNum++;
			}
		}
	}
	if (userOrderNum == 0)
	{
		printf("�û���ԤԼ��¼\n");
		printf("������ִ����ϣ��밴�����������һ������:");
		char free_key;
		free_key = getch();
		printf("%c", free_key);
		printf("\n���ڰ�ȫ���أ����Ժ󡤡���������");
		delay(500);
		reserve_message();
	}
	// �����������洢��ѡ������ԤԼ�������ں�ʱ��
	char selectedDateTime[100][1024];
	int selectedDateTimeCount = 0;
	for (int i = 0; i < userOrderNum; i++)
	{
		printf("\n");
		printf("���:%d\n", (i + 1));
		printf("ID��%s\n", userOrder[i].ID);
		printf("������%s\n", userOrder[i].name);
		printf("������ţ�%s\n", userOrder[i].orderNumber);
		char locationInfo[1024];
		strcpy(locationInfo, userOrder[i].location);
		char* str1 = strtok(locationInfo, "_");
		if (str1 != NULL)
		{
			// ���ݡ����ء����ڡ�ʱ���
			printf("���ݣ�%s\n", str1);
			str1 = strtok(NULL, "_");
			if (NULL != str1)
			{
				printf("����:%s\n", str1);
				str1 = strtok(NULL, "_");

				if (NULL != str1)
				{
					char date[1024]; // ���һ���������洢����
					strcpy(date, str1); // �������ڵ� 'date' ����
					printf("����:%s\n", date); // ��ӡ����
					// ��ʽ�����ڣ�ȷ���·ݺ�����Ϊ��λ��
					char formattedDate[1024];
					if (strlen(date) == 1)
					{
						snprintf(formattedDate, sizeof(formattedDate), "0%s", date);
					}
					else
					{
						snprintf(formattedDate, sizeof(formattedDate), "%s", date);
					}

					str1 = strtok(NULL, "_");
					if (NULL != str1)
					{
						printf("ʱ���:%s\n", str1);
						// ��ʽ��ʱ��ε�������Ϣ
						// �洢���ں�ʱ�䵽������
						snprintf(selectedDateTime[selectedDateTimeCount], sizeof(selectedDateTime[selectedDateTimeCount]), "%s %s", formattedDate, str1);
						selectedDateTimeCount++;
					}
				}
			}
		}
	}
	int num = 0;
	int j;
	int k;
	while (1)
	{
		printf("������Ҫǩ���Ķ�����ţ���0���أ�");
		if (scanf("%d", &num) != 1)
		{
			printf("��Ч�����룬���������롣\n");
			while (getchar() != '\n');  // ������뻺����
			continue;
		}
		if (num == 0)
		{
			// �û�ѡ��0����
			system("CLS");
			break;
		}
		if (num > 0 && num <= userOrderNum)
		{
			// �û���������Ч�Ķ�����ţ�����ȡ������
			break;
		}
		else
		{
			printf("��Ч�Ķ�����ţ����������롣\n");
		}
	}
	if (num == 0)
	{
		printf("\n���ڰ�ȫ���أ����Ժ󡤡���������");
		delay(500);
		reserve_message();
	}
	else
	{
		// �û���������Ч�Ķ�����ţ���������ȡ���������߼�
		printf("��ѡ��ǩ���Ķ��������ں�ʱ�䣺%s\n", selectedDateTime[num - 1]);
		// ��ȡ��ǰʱ��
		time_t now;
		struct tm* current_time;
		time(&now);
		current_time = localtime(&now);
		// ������֪ʱ���ַ���
		int month, day, startHour, startMinute, endHour, endMinute;
		sscanf(selectedDateTime[num - 1], "%d-%d %d:%d - %d:%d", &month, &day, &startHour, &startMinute, &endHour, &endMinute);
		// ��ȡ��ǰ���
		int currentYear = current_time->tm_year + 1900;
		// ������������֪���ں�ʱ���tm�ṹ��
		struct tm known_time =
		{
			.tm_year = currentYear - 1900, // ʹ�õ�ǰ���
			.tm_mon = month - 1,           // �·ݴ�0��ʼ
			.tm_mday = day,
			.tm_hour = startHour,
			.tm_min = startMinute,
			.tm_sec = 0 // ������Ϊ0����Ϊ������û������
		};
		// ת��Ϊtime_t����
		time_t known_time_t = mktime(&known_time);
		// ����ʱ���
		double time_difference = difftime(known_time_t, now);
		// ���ʱ���
		/*printf("ʱ���Ϊ%.0lf��\n", time_difference);*/
		if ((time_difference) < -3600)
		{
			printf("ǩ��ʧ�ܣ���Ϊ�Ѿ�����Ԥ��ʱ�䡣\n");
			Node* head = (Node*)malloc(sizeof(Node));//����ͷ���
			head->next = NULL;
			loadList(head, "Customer.txt");
			Node* move = head;
			char age[30];
			while (strcmp(move->cus.id, uesr_id_) != 0)
			{
				move = move->next;
			}
			int noShowCount = atoi(move->cus.noShowCount);
			noShowCount++;
			sprintf(move->cus.noShowCount, "%.d", noShowCount);
			saveList(head, "Customer.txt");//���������ļ�˫����											
			printf("����ˬԼ���������ӣ������������ݹ涨���������ŵĺù���");
			printf("\n�밴�����������һ�����棺");
			char key;
			key = getch();
			printf("%c",key);
			delay(200);
			system("cls");
			printf("���ڰ�ȫ�˳�ǩ��ϵͳ�����Ժ󡤡���������");
			delay(500);
			reserve_message();												//����
		}
		if ((time_difference) > 600)
		{
			printf("ǩ��ʧ�ܣ���Ϊֻ����ǰʮ����ǩ����\n");
			printf("�밴�����������һ������:");
			char free_key;
			free_key = getch();
			printf("%c", free_key);
			printf("\n���ڰ�ȫ���أ����Ժ󡤡���������");
			delay(500);
			reserve_message();														//����
		}
		else
		{
			printf("ǩ���ɹ���\n");
			printf("������ִ����ϣ��밴�����������һ������:");
			char free_key;
			free_key = getch();
			printf("%c", free_key);
			printf("\n���ڰ�ȫ���أ����Ժ󡤡���������");
			delay(500);
			reserve_message();													//����
		}
	}
}

int calculateDateDifferenceFromToday(const char* cancellationTimeRange) //��ȡ������Ϣ������ȡ��Ԥ���ı���Ϣ�����ļ�
{
	char currentDate[6]; // �洢��ǰ���ڵ��ַ���
	// ��ȡ��ǰ���ڲ���ʽ��
	time_t now;
	struct tm* current_time;
	time(&now);
	current_time = localtime(&now);
	strftime(currentDate, 6, "%m-%d", current_time);
	struct tm cancelDate = { 0 }; // ��ʼ��Ϊ0���Ա���������·ݺ�����
	struct tm today = { 0 };
	// ����ȡ�����ںͽ������ڵ��ַ���
	if (sscanf(cancellationTimeRange, "%d-%d", &cancelDate.tm_mon, &cancelDate.tm_mday) != 2 ||
		sscanf(currentDate, "%d-%d", &today.tm_mon, &today.tm_mday) != 2)
	{
		printf("���ڽ���ʧ��\n");
		return -1; // ���ش���ֵ
	}
	// �����·�Ϊ0��11�ķ�Χ
	cancelDate.tm_mon -= 1;
	today.tm_mon -= 1;
	// �������Ϊ��ǰ��ݣ����Ը�����Ҫ�޸�
	int currentYear = 2023; // ���赱ǰ�����2023
	cancelDate.tm_year = currentYear - 1900;
	today.tm_year = currentYear - 1900;
	// ������ת��Ϊʱ���
	time_t cancelTime = mktime(&cancelDate);
	time_t currentTime = mktime(&today);
	// �������ڲ�ֵ������ȡ��
	int daysDifference = (int)difftime(cancelTime, currentTime) / (60 * 60 * 24);
	return daysDifference;
}










