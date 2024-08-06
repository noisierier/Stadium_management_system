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
char dates[7][15];// 存储日期的字符串数组
struct Order orders[100];
int orderNum = 0;																					//order
const char* venue_names[] = { "球类场馆1号场","球类场馆2号场","游泳场馆1号场","游泳场馆2号场","室外场馆1号场","室外场馆2号场" };
const char* hall_names[] = { "球类场馆","游泳场馆","室外场馆" };
int lineNumber = 1;//记录用户所在行数

void calculateDates() //关于时间
{
	// 获取当前日期
	time_t t = time(NULL);
	struct tm* tm_info = localtime(&t);

	// 计算并存储日期
	for (int i = 0; i < 7; i++) {
		tm_info->tm_mday++; // 增加一天
		mktime(tm_info);
		strftime(dates[i], sizeof(dates[i]), "%m-%d", tm_info); // 格式化日期为"MM-DD"
	}
}

int isInteger(const char* input) //验证整数
{
	for (int i = 0; input[i] != '\0'; i++) 
	{
		if (input[i] < '0' || input[i] > '9') 
		{
			return 0; // 不是整数
		}
	}
	return 1; // 是整数
}  // 声明一个函数来验证输入是否为整数

void saveOrderToFile(const char* ID, const char* name, const char* age, const char* gender, const char* orderNumber, const char* location)  //保存订单信息
{ 
	FILE* file = fopen("orderInformation.txt", "a"); // 以追加模式打开文件
	if (file == NULL) 
	{
		printf("打开文件时发生错误。\n");
		return;
	}
	fprintf(file, "\n");
	fprintf(file, "%s,%s,%s,%s,%s,%s\n", ID, name, age, gender, orderNumber, location);
	fclose(file);
}

void book_f()//预定场地验证加进入函数
{
	Customer customer;
	int authResult = authenticateUser(uesr_id_, &customer);
	int canContinueBooking = checkAppointmentLimit(&customer);//预定场数未超过3，可以进行预定
	if (authResult == -1)//爽约次数大于3
	{
		system("cls");
		printf("\n您的爽约次数已经超过三次，暂时无法预约场地，请找体育馆管理员进行爽约次数消除!");
		delay(500);
		printf("\n请按任意键退出预定系统！");
		char key;
		key = getch();
		printf("%c",key);
		printf("\n\n正在安全退出系统，请稍后······");
		delay(500);
		reserve_message();
	}
	else if(canContinueBooking == 0)
	{
		system("cls");
		printf("\n体育馆规定最多同时预定三个场馆，您已经预定了三个场馆！");
		delay(500);
		printf("\n请按任意键退出预定系统！");
		char key;
		key = getch();
		printf("%c", key);
		printf("\n\n正在安全退出系统，请稍后······");
		delay(500);
		reserve_message();
	}
	bookCourt(&customer);
	printf("\n已完成指定命令，请按任意键返回上一级界面：");
	char key;
	key = getch();
	printf("%c", key);
	delay(200);
	system("cls");
	printf("正在返回，请稍后······");
	delay(300);
	reserve_message();
}

int authenticateUser(const char* username, Customer* customer)//匹配用户账号，存储数组信息，验证爽约次数小于三
{
	FILE* file = fopen("customerInfo.txt", "r");
	if (file == NULL)
	{
		printf("无法打开用户信息文件\n");
		return 0; // 文件打开失败，认证失败
	}
	char line[256]; // 假设每行不超过256个字符
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
				if (strcmp(username, customer->id) == 0)//锁定对应的用户名
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
								strcpy(customer->gender, token); // 读取性别字段
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
													// 检查爽约次数是否大于3
													if (atoi(customer->noShowCount) > 3)
													{
														fclose(file);
														return -1; // 爽约次数过多，用户验证失败，返回-1
													}
													token = strtok(NULL, ",");
													if (token != NULL)
													{
														strcpy(customer->appointmentNum, token);
														// 处理各个场馆的预约次数
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
						return 1; // 用户验证成功
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
	return 0; // 用户验证失败
}

int checkAppointmentLimit(const Customer* customer)//验证总预约次数小于三，可以正常进行预约
{
	int numAppointments = atoi(customer->appointmentNum);
	return (numAppointments >= 3) ? 0 : 1;
}

void showOrders_menu()//打印历史订单并进行取消预定预处理
{
	delay(100);
	system("cls");
	Customer customer;
	orderNum = readOrder();
	authenticateUser_history(uesr_id_, &customer);//从文件中获取该用户的全部信息
	showOrders(uesr_id_, &customer);//进入打印历史订单和取消预定选项
	delay(500);
	printf("命令已执行完毕，请按任意键返回上一级界面:");
	char free_key;
	free_key = getch();
	printf("%c",free_key);
	printf("\n正在安全返回，请稍后······");
	delay(500);
	reserve_message();
}

void showOrders(char username[], Customer* customer)//打印历史预约订单和取消预定
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
		printf("用户无预约记录\n");
		return;
	}
	// 定义数组来存储所选订单的预约场地日期和时间
	char selectedDateTime[100][1024];
	int selectedDateTimeCount = 0;
	for (int i = 0; i < userOrderNum; i++)
	{
		printf("\n");
		printf("序号:%d\n", (i + 1));
		printf("ID：%s\n", userOrder[i].ID);
		printf("姓名：%s\n", userOrder[i].name);
		printf("订单编号：%s\n", userOrder[i].orderNumber);
		char locationInfo[1024];
		strcpy(locationInfo, userOrder[i].location);
		char* str1 = strtok(locationInfo, "_");
		if (str1 != NULL)
		{
			// 场馆、场地、日期、时间段
			printf("场馆：%s\n", str1);
			str1 = strtok(NULL, "_");
			if (NULL != str1)
			{
				printf("场地:%s\n", str1);
				str1 = strtok(NULL, "_");

				if (NULL != str1)
				{
					char date[1024]; // 添加一个变量来存储日期
					strcpy(date, str1); // 复制日期到 'date' 变量
					printf("日期:%s\n", date); // 打印日期
					// 格式化日期，确保月份和日期为两位数
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
						printf("时间段:%s\n", str1);
						// 格式化时间段等其他信息
						// 存储日期和时间到数组中
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
		printf("请输入要取消的订单序号，按0返回：");														//此处有输入
		if (scanf("%d", &num) != 1)
		{
			printf("无效的输入，请重新输入。\n");
			while (getchar() != '\n');  // 清空输入缓冲区
			continue;
		}
		if (num == 0) // 用户选择按0返回
		{
			system("CLS");
			printf("正在返回上一级界面，请稍后······");												//预定历史唯一一处可以返回上一级界面的地方
			delay(500);
			reserve_message();
		}

		if (num > 0 && num <= userOrderNum)
		{
			// 用户输入了有效的订单序号，可以取消订单
			// 获取当前时间
			time_t now;
			struct tm* current_time;
			time(&now);
			current_time = localtime(&now);
			// 解析已知时间字符串
			int month, day, startHour, startMinute, endHour, endMinute;
			sscanf(selectedDateTime[num - 1], "%d-%d %d:%d - %d:%d", &month, &day, &startHour, &startMinute, &endHour, &endMinute);
			// 获取当前年份
			int currentYear = current_time->tm_year + 1900;
			// 创建并设置已知日期和时间的tm结构体
			struct tm known_time =
			{
				.tm_year = currentYear - 1900, // 使用当前年份
				.tm_mon = month - 1,           // 月份从0开始
				.tm_mday = day,
				.tm_hour = startHour,
				.tm_min = startMinute,
				.tm_sec = 0 // 秒数设为0，因为输入中没有秒数
			};
			// 转换为time_t类型
			time_t known_time_t = mktime(&known_time);
			// 计算时间差
			double time_difference = difftime(known_time_t, now);
			if (time_difference < 0)
			{
				printf("已经过了预定时间，不能取消订单。\n");
			}
			// 如果时间差小于1小时（3600秒），禁止继续运行
			else if (time_difference < 3600)
			{
				printf("取消失败，因为距离预定时间不到1小时。\n");
			}
			else
			{
				// 用户输入了有效的订单序号，继续处理取消订单的逻辑
				printf("您选择取消的订单的预约场地日期和时间：%s\n", selectedDateTime[num - 1]);
				// 获取当前时间
				time_t now;
				struct tm* current_time;
				time(&now);
				current_time = localtime(&now);
				// 解析已知时间字符串
				int month, day, startHour, startMinute, endHour, endMinute;
				sscanf(selectedDateTime[num - 1], "%d-%d %d:%d - %d:%d", &month, &day, &startHour, &startMinute, &endHour, &endMinute);
				// 获取当前年份
				int currentYear = current_time->tm_year + 1900;
				// 创建并设置已知日期和时间的tm结构体
				struct tm known_time =
				{
					.tm_year = currentYear - 1900, // 使用当前年份
					.tm_mon = month - 1,           // 月份从0开始
					.tm_mday = day,
					.tm_hour = startHour,
					.tm_min = startMinute,
					.tm_sec = 0 // 秒数设为0，因为输入中没有秒数
				};
				// 转换为time_t类型
				time_t known_time_t = mktime(&known_time);
				// 计算时间差
				double time_difference = difftime(known_time_t, now);
				// 输出时间差
				/*printf("时间差为%.0lf秒\n", time_difference);*/
				if ((time_difference) < 0)
				{
					printf("不能取消，因为场地已经开始使用。\n");
					printf("命令已执行完毕，请按任意键返回上一级界面:");
					char free_key;
					free_key = getch();
					printf("%c", free_key);
					printf("\n正在安全返回，请稍后······");
					delay(500);
					reserve_message();
				}
				// 如果时间差小于1小时（3600秒），禁止继续运行
				if ((time_difference) < 3600)
				{
					printf("取消失败，因为距离预定时间不到1小时。\n");
					printf("命令已执行完毕，请按任意键返回上一级界面:");
					char free_key;
					free_key = getch();
					printf("%c", free_key);
					printf("\n正在安全返回，请稍后······");
					delay(500);
					reserve_message();


				}
				// 如果时间差大于等于24小时，可以继续运行
				printf("可以继续运行程序，因为距离预定时间超过1小时。\n");
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
				
				Node* head = (Node*)malloc(sizeof(Node));//创建头结点
				head->next = NULL;
				loadList(head, "Customer.txt");
				Node* move = head;
				char age[30];
				while (strcmp(move->cus.id, uesr_id_) != 0)
				{
					move = move->next;
				}
				move->cus.cus_balance;					//修改余额
				double balance = str_to_double(move->cus.cus_balance);
				balance = balance + rentPerHour;
				sprintf(move->cus.cus_balance, "%.2lf", balance);
				move->cus.appointmentNum;//修改总预定次数
				int appointmentNum_ = atoi(move->cus.appointmentNum);
				appointmentNum_ = appointmentNum_ - 1;
				sprintf(move->cus.appointmentNum, "%.d", appointmentNum_);
				move->cus.book_num[courtIndex]--;//修改各个场地的预定次数
				saveList(head, "Customer.txt");//链表数组文件双保存
				system("cls");
				printf("正在执行取消命令，请稍后······");

				
				int cancellationHallNumber;
				int cancellationVenueNumber;
				char cancellationTimeRange[10];
				int cancellationHour;
				sscanf(cancelLation, "Hall%d_%d_%9[^_]_%d", &cancellationHallNumber, &cancellationVenueNumber, cancellationTimeRange, &cancellationHour);
				int difference = calculateDateDifferenceFromToday(cancellationTimeRange);
				halls[cancellationHallNumber - 1].courts[cancellationVenueNumber - 1].time[difference - 1][cancellationHour - 6]--;
				saveToFile();

				delay(500);
				printf("\n取消成功!\n");
				printf("命令已执行完毕，请按任意键返回上一级界面:");
				char free_key;
				free_key = getch();
				printf("%c", free_key);
				printf("\n正在安全返回，请稍后······");
				delay(500);
				reserve_message();
			}
		}
		else
		{
			printf("无效的订单序号，请重新输入。\n");
		}
	}
}

int authenticateUser_history(const char* username, Customer* customer)//匹配用户账号，存储数组信息，不验证爽约次数
{
	FILE* file = fopen("customerInfo.txt", "r");
	if (file == NULL)
	{
		printf("无法打开用户信息文件\n");
		return 0; // 文件打开失败，认证失败
	}
	char line[256]; // 假设每行不超过256个字符
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
				if (strcmp(username, customer->id) == 0)//锁定对应的用户名
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
								strcpy(customer->gender, token); // 读取性别字段
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
														// 处理各个场馆的预约次数
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
						return 1; // 用户验证成功
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
	return 0; // 用户验证失败
}

void saveOrder()//将order数据存进文件

{
	FILE* file = fopen("orderInformation.txt", "w");
	if (file == NULL)
	{
		printf("无法打开文件 orderInformation.txt\n");
		return;
	}
	for (int i = 0; i < orderNum; i++)//把orders数组写入文件													//ordernum
	{
		fprintf(file, "%s,%s,%d,%d,%s,%s\n", orders[i].ID, orders[i].name, orders[i].age, orders[i].gender, orders[i].orderNumber, orders[i].location);
	}
	fclose(file);//关闭文件
}

int readOrder()//阅读order文件，即订单信息文件
{
	int orderNum_ = 0;
	FILE* file = fopen("orderInformation.txt", "r");
	if (file == NULL)
	{
		printf("无法打开文件 orderInformation.txt\n");
		return;
	}
	char str[1000];
	while (fgets(str, sizeof(str), file))
	{
		if (str[0] == '\n')
		{
			continue;
		}
		// 按逗号分割字符串
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
					// 读取年龄
					orders[orderNum_].age = atoi(token); // 使用atoi将字符串转换为整数
					token = strtok(NULL, ",");
					if (token != NULL)
					{
						// 读取性别
						orders[orderNum_].gender = atoi(token); // 使用atoi将字符串转换为整数
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
	// 关闭文件
	fclose(file);
	return orderNum_;
}

void bookCourt(Customer* customer)//预定场地
{
	struct Order order;
	calculateDates(); // 计算日期
	readFromFile();
	int hallIndex;  // 要预定的大厅索引
	int courtIndex;   // 要预定的场地索引
	int dayIndex;   // 要预定的日期索引
	int timeSlot;   // 要预定的时间段索引
	int booked = 0;  // 用于标记是否成功预定
	do {
		// 显示场馆信息供选择
		system("cls");
		printf("可选场馆列表：\n");
		printf("1.球类场馆\n");
		printf("2.游泳场馆\n");
		printf("3.室外场馆\n");
		printf("4.退出预定系统\n");
		char flag;
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
		if (flag == '4')
		{
			system("cls");
			printf("正在返回上一级界面，请稍后······");
			delay(500);
			reserve_message();
		}
		hallIndex = flag - '0';
		hallIndex--;  // 调整为数组索引
		// 显示场地信息供选择
		printf("\n\n可选场地列表：\n");
		for (int i = 0; i < halls[hallIndex].NumOfCourt; i++)
		{
			printf("%d. 场地%d\n", i + 1, i + 1);
		}
		char input[30];
		// 循环等待有效的场地输入
		while (1)
		{
			printf("请选择要预定的场地编号 (输入0重新选择)：");
			if (scanf("%s", input) != 1 || !isInteger(input))
			{
				printf("无效的输入，请重新选择场地。\n");
				while (getchar() != '\n');  // 清空输入缓冲区
				continue;
			}
			courtIndex = atoi(input);
			if (courtIndex == 0 || (courtIndex >= 1 && courtIndex <= halls[hallIndex].NumOfCourt))
			{
				break;  // 输入有效，退出循环
			}
			else
			{
				printf("无效的输入，请重新选择场地。\n");
			}
		}
		if (courtIndex == 0)
		{
			system("cls");  // 清屏
			continue;  // 重新选择
		}
		courtIndex--;  // 调整为数组索引
		int userAge = atoi(customer->age);
		// 获取所选择场馆的最小和最大年龄限制
		int minAge = halls[hallIndex].minAge;
		int maxAge = halls[hallIndex].maxAge;
		if (userAge < minAge || userAge > maxAge)// 进行年龄判定
		{
			printf("\n抱歉，您的年龄为%d，不符合场馆的年龄限制。场馆的可入年龄为%d-%d。\n\n", userAge, minAge, maxAge);
			char key;
			printf("重新选择场馆请按'1'，退出预定系统请按'P:'");
			printf("请输入您的选项：");
			key = getch();
			printf("%c", key);
			delay(100);
			while (key != '1' && key != 'p' && key != 'P')
			{
				printf("\n请根据提示，输入'1'或'P'：");
				key = getch();
				printf("%c", key);
				delay(100);
			}
			if (key == '1')
			{
				system("cls");  // 清屏
				continue;  // 重新选择场馆
			}
			if (key == 'p' || key == 'P')
			{
				break;  // 退出bookCourt函数
			}
		}
		int rentPerHour = halls[hallIndex].courts[courtIndex].rentRerHour;
		int userBalance = atoi(customer->cus_balance);// 进行余额判定
		if (userBalance < rentPerHour)
		{
			printf("\n抱歉，您的余额为%d，不足以支付场地租金%d/h。\n", userBalance, rentPerHour);
			printf("1.重新选择场馆请按'1'，退出预定系统请按'P:");
			printf("请输入您的选项：");
			char key;
			key = getch();
			printf("%c", key);
			delay(100);
			while (key != '1' && key != 'p' && key != 'P')
			{
				printf("\n请根据提示，输入'1'或'P'：");
				key = getch();
				printf("%c", key);
				delay(100);
			}
			if (key == '1')
			{
				system("cls");  // 清屏
				continue;  // 重新选择场馆
			}
			if (key == 'p' || key == 'P')
			{
				break;  // 退出bookCourt函数
			}
		}
		printf("\n可选日期列表：\n");// 显示日期信息供选择
		for (int i = 0; i < 7; i++)
		{
			printf("%d. %s\n", i + 1, dates[i]);
		}
		printf("请输入您的选项(日期编号为1到7，代表从明天开始的第一天到第七天)：");
		char key;
		key = getch();
		printf("%c", key);
		delay(100);
		while (key != '1' && key != '2' && key != '3' && key != '4' && key != '5' && key != '6' && key != '7')
		{
			printf("\n请根据提示，输入'1'或'2'或'3'或'4'或'5'或'6'或'7'：");
			key = getch();
			printf("%c", key);
			delay(100);
		}
		dayIndex = key - '0';
		dayIndex--;  // 调整为数组索引
		printf("\n\n可选时间段列表：\n");// 显示时间段信息供选择
		for (int i = 0; i < 16; i++)
		{
			printf("%d. %02d:00 - %02d:59\n", i + 1, 6 + i, 6 + i);
		}
		// 循环等待有效的时间段输入
		while (1)
		{
			printf("请选择要预定的时间段编号 (输入0重新选择)：");
			if (scanf("%s", input) != 1 || !isInteger(input))
			{
				printf("无效的输入，请重新选择时间段。\n");
				while (getchar() != '\n');  // 清空输入缓冲区
				continue;
			}
			timeSlot = atoi(input);
			if (timeSlot == 0 || (timeSlot >= 1 && timeSlot <= 16))
			{
				break;  // 输入有效，退出循环
			}
			else
			{
				printf("无效的输入，请重新选择时间段。\n");
			}
		}
		if (timeSlot == 0)
		{
			system("cls");  // 清屏
			continue;  // 重新选择
		}
		timeSlot--;  // 调整为数组索引
		if (halls[hallIndex].courts[courtIndex].time[dayIndex][timeSlot] >= halls[hallIndex].courts[courtIndex].maxPerson)// 检查该时间段是否已经预定满
		{
			printf("\n该场地该时间段预定人数已达场地最大容纳量，请预约其他场地或其他时间段\n");
			printf("请按任意键返回上一级界面：");
			char key;
			key = getch();
			printf("%c",key);
			delay(200);
			system("cls");
			printf("正在安全退出系统，请稍后······");
			delay(500);
			reserve_message();
		}
		else
		{
			time_t currentTime;// 获取当前系统日期和时间
			struct tm* localTime;
			time(&currentTime);  // 获取当前时间
			localTime = localtime(&currentTime);  // 转换为本地时间
			int year = localTime->tm_year + 1900;  // 年份需要加上 1900
			int month = localTime->tm_mon + 1;      // 月份从 0 开始，需要加上 1
			int day = localTime->tm_mday;           // 月中的日
			int hour = localTime->tm_hour;          // 小时
			int minute = localTime->tm_min;         // 分钟
			// 生成订单编号，格式为：顾客ID+预定日期（yyyy:mm:dd:hh:mm）
			char orderNumber[50];
			sprintf(orderNumber, "%s-%04d:%02d:%02d:%02d:%02d", customer->id, year, month, day, hour, minute);
			// 输出订单信息
			struct order_info order;
			char locationInfo[50];
			// 构建场地信息字符串，格式为：Hall1_1_09-05_07:00 - 07:59
			sprintf(locationInfo, "Hall%d_%d_%s_%02d:%02d - %02d:%02d", hallIndex + 1, courtIndex + 1, dates[dayIndex], 6 + timeSlot, 0, 6 + timeSlot, 59);
			char formattedInfo[1024];
			snprintf(formattedInfo, sizeof(formattedInfo), "%s,%s,%s,%s,%s,%s\n", customer->id, customer->name, customer->age, customer->gender, orderNumber, locationInfo);
			char combinedDateTime[1024];
			//解析出新预订订单的时间，存在combinedDateTime中
			if (sscanf(formattedInfo, "%[^,],%[^,],%d,%d,%[^,],%[^_]_%[^_]_%[^_]_%[^ ]",
				order.username, order.fullName, &order.age, &order.gender, order.orderNumber, order.venue, order.venueNumber, order.date, order.time) == 9)
			{
				sprintf(combinedDateTime, "%s%s", order.date, order.time);
				printf("\n");
			}
			//获取已预订的场地时间，存在selectedDateTime[selectedDateTimeCount]中，从0开始检索
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
			char selectedDateTime[100][1024];// 定义数组来存储所选订单的预约场地日期和时间
			int selectedDateTimeCount = 0;
			for (int i = 0; i < userOrderNum; i++)
			{
				char locationInfo[1024];
				strcpy(locationInfo, userOrder[i].location);
				char* str1 = strtok(locationInfo, "_");
				if (str1 != NULL)
				{
					// 场馆、场地、日期、时间段
					str1 = strtok(NULL, "_");
					if (NULL != str1)
					{
						str1 = strtok(NULL, "_");
						if (NULL != str1)
						{
							char date[1024]; // 添加一个变量来存储日期
							strcpy(date, str1); // 复制日期到 'date' 变量
							// 格式化日期，确保月份和日期为两位数
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
								// 格式化时间段等其他信息
								char* hyphenPos = strrchr(str1, '-');
								if (hyphenPos != NULL)
								{
									*hyphenPos = '\0';
								}
								// 存储日期和时间到数组中
								snprintf(selectedDateTime[selectedDateTimeCount], sizeof(selectedDateTime[selectedDateTimeCount]), "%s%s", formattedDate, str1);
								selectedDateTimeCount++;
							}
						}
					}
				}
			}
			int found = 0; // 用于标记是否找到匹配 
			for (int i = 0; i < selectedDateTimeCount; i++)
			{ 
					if (filter_digits(combinedDateTime) == filter_digits(selectedDateTime[i]))
					{ 
					
						printf("按照体育馆预定条例，您不能在同一时间预定两个场地！");
						printf("\n请按任意键安全退出系统：");
						char key;
						key = getch();
						printf("%c",key);
						delay(200);
						system("cls");
						printf("\n正在安全退出系统，请稍后······");
						delay(500);
						reserve_message();
					} 
			} 
			printf("预定成功！您的订单编号是：%s\n", orderNumber);//没有在相同时间预约其他场地，进行成功预定判定
			halls[hallIndex].courts[courtIndex].time[dayIndex][timeSlot]++;// 进行预定，增加预定人数
			printf("您预定的场馆是：%s，场地号：%d，日期：%s，时间段：%02d:00 - %02d:59\n", hall_names[hallIndex], courtIndex + 1, dates[dayIndex], 6 + timeSlot, 6 + timeSlot);
			booked = 1;  // 标记为成功预定
			if (booked)
			{
				char locationInfo[50];
				// 构建场地信息字符串，格式为：Hall1_1_09-05_07:00 - 07:59
				sprintf(locationInfo, "Hall%d_%d_%s_%02d:%02d - %02d:%02d", hallIndex + 1, courtIndex + 1, dates[dayIndex], 6 + timeSlot, 0, 6 + timeSlot, 59);
				saveOrderToFile(customer->id, customer->name, customer->age, customer->gender, orderNumber, locationInfo);
			}
			saveToFile();
			// 在成功预定场地后，更新用户信息并保存到文件
			Node* head = (Node*)malloc(sizeof(Node));//创建头结点
			head->next = NULL;
			loadList(head, "Customer.txt");
			Node* move = head;
			char age[30];
			while (strcmp(move->cus.id, uesr_id_) != 0)
			{
				move = move->next;
			}
			move->cus.cus_balance;//修改余额
			double balance = str_to_double(move->cus.cus_balance);
			balance = balance - rentPerHour;
			sprintf(move->cus.cus_balance, "%.2lf", balance);
			move->cus.appointmentNum;//修改总预定次数
			int appointmentNum_ = atoi(move->cus.appointmentNum);
			appointmentNum_ = appointmentNum_ + 1;
			sprintf(move->cus.appointmentNum, "%.d", appointmentNum_);
			move->cus.book_num[courtIndex]++;//修改各个场地的预定次数
			saveList(head, "Customer.txt");//链表数组文件双保存
		}
	} while (!booked);  // 循环直到成功预定为止
}

int filter_digits(const char* input) //从字符串中过滤出数字并返回整数
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

void signIn_pre(void)//签到预处理
{

	delay(100);
	system("cls");
	Customer customer;
	orderNum = readOrder();
	authenticateUser_history(uesr_id_, &customer);//从文件中获取该用户的全部信息
	signIn(uesr_id_, &customer);
	delay(500);
	printf("命令已执行完毕，请按任意键返回上一级界面:");
	char free_key;
	free_key = getch();
	printf("%c", free_key);
	printf("\n正在安全返回，请稍后······");
	delay(500);
	reserve_message();
}

void signIn(char username[], Customer* customer)//签到
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
		printf("用户无预约记录\n");
		printf("命令已执行完毕，请按任意键返回上一级界面:");
		char free_key;
		free_key = getch();
		printf("%c", free_key);
		printf("\n正在安全返回，请稍后······");
		delay(500);
		reserve_message();
	}
	// 定义数组来存储所选订单的预约场地日期和时间
	char selectedDateTime[100][1024];
	int selectedDateTimeCount = 0;
	for (int i = 0; i < userOrderNum; i++)
	{
		printf("\n");
		printf("序号:%d\n", (i + 1));
		printf("ID：%s\n", userOrder[i].ID);
		printf("姓名：%s\n", userOrder[i].name);
		printf("订单编号：%s\n", userOrder[i].orderNumber);
		char locationInfo[1024];
		strcpy(locationInfo, userOrder[i].location);
		char* str1 = strtok(locationInfo, "_");
		if (str1 != NULL)
		{
			// 场馆、场地、日期、时间段
			printf("场馆：%s\n", str1);
			str1 = strtok(NULL, "_");
			if (NULL != str1)
			{
				printf("场地:%s\n", str1);
				str1 = strtok(NULL, "_");

				if (NULL != str1)
				{
					char date[1024]; // 添加一个变量来存储日期
					strcpy(date, str1); // 复制日期到 'date' 变量
					printf("日期:%s\n", date); // 打印日期
					// 格式化日期，确保月份和日期为两位数
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
						printf("时间段:%s\n", str1);
						// 格式化时间段等其他信息
						// 存储日期和时间到数组中
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
		printf("请输入要签到的订单序号，按0返回：");
		if (scanf("%d", &num) != 1)
		{
			printf("无效的输入，请重新输入。\n");
			while (getchar() != '\n');  // 清空输入缓冲区
			continue;
		}
		if (num == 0)
		{
			// 用户选择按0返回
			system("CLS");
			break;
		}
		if (num > 0 && num <= userOrderNum)
		{
			// 用户输入了有效的订单序号，可以取消订单
			break;
		}
		else
		{
			printf("无效的订单序号，请重新输入。\n");
		}
	}
	if (num == 0)
	{
		printf("\n正在安全返回，请稍后······");
		delay(500);
		reserve_message();
	}
	else
	{
		// 用户输入了有效的订单序号，继续处理取消订单的逻辑
		printf("您选择签到的订单的日期和时间：%s\n", selectedDateTime[num - 1]);
		// 获取当前时间
		time_t now;
		struct tm* current_time;
		time(&now);
		current_time = localtime(&now);
		// 解析已知时间字符串
		int month, day, startHour, startMinute, endHour, endMinute;
		sscanf(selectedDateTime[num - 1], "%d-%d %d:%d - %d:%d", &month, &day, &startHour, &startMinute, &endHour, &endMinute);
		// 获取当前年份
		int currentYear = current_time->tm_year + 1900;
		// 创建并设置已知日期和时间的tm结构体
		struct tm known_time =
		{
			.tm_year = currentYear - 1900, // 使用当前年份
			.tm_mon = month - 1,           // 月份从0开始
			.tm_mday = day,
			.tm_hour = startHour,
			.tm_min = startMinute,
			.tm_sec = 0 // 秒数设为0，因为输入中没有秒数
		};
		// 转换为time_t类型
		time_t known_time_t = mktime(&known_time);
		// 计算时间差
		double time_difference = difftime(known_time_t, now);
		// 输出时间差
		/*printf("时间差为%.0lf秒\n", time_difference);*/
		if ((time_difference) < -3600)
		{
			printf("签到失败，因为已经过了预定时间。\n");
			Node* head = (Node*)malloc(sizeof(Node));//创建头结点
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
			saveList(head, "Customer.txt");//链表数组文件双保存											
			printf("您的爽约次数已增加，请遵守体育馆规定，做个诚信的好公民！");
			printf("\n请按任意键返回上一级界面：");
			char key;
			key = getch();
			printf("%c",key);
			delay(200);
			system("cls");
			printf("正在安全退出签到系统，请稍后······");
			delay(500);
			reserve_message();												//返回
		}
		if ((time_difference) > 600)
		{
			printf("签到失败，因为只能提前十分钟签到。\n");
			printf("请按任意键返回上一级界面:");
			char free_key;
			free_key = getch();
			printf("%c", free_key);
			printf("\n正在安全返回，请稍后······");
			delay(500);
			reserve_message();														//返回
		}
		else
		{
			printf("签到成功！\n");
			printf("命令已执行完毕，请按任意键返回上一级界面:");
			char free_key;
			free_key = getch();
			printf("%c", free_key);
			printf("\n正在安全返回，请稍后······");
			delay(500);
			reserve_message();													//返回
		}
	}
}

int calculateDateDifferenceFromToday(const char* cancellationTimeRange) //获取场馆信息，用于取消预定改变信息存入文件
{
	char currentDate[6]; // 存储当前日期的字符串
	// 获取当前日期并格式化
	time_t now;
	struct tm* current_time;
	time(&now);
	current_time = localtime(&now);
	strftime(currentDate, 6, "%m-%d", current_time);
	struct tm cancelDate = { 0 }; // 初始化为0，以便后续设置月份和日期
	struct tm today = { 0 };
	// 解析取消日期和今天日期的字符串
	if (sscanf(cancellationTimeRange, "%d-%d", &cancelDate.tm_mon, &cancelDate.tm_mday) != 2 ||
		sscanf(currentDate, "%d-%d", &today.tm_mon, &today.tm_mday) != 2)
	{
		printf("日期解析失败\n");
		return -1; // 返回错误值
	}
	// 调整月份为0到11的范围
	cancelDate.tm_mon -= 1;
	today.tm_mon -= 1;
	// 设置年份为当前年份，可以根据需要修改
	int currentYear = 2023; // 假设当前年份是2023
	cancelDate.tm_year = currentYear - 1900;
	today.tm_year = currentYear - 1900;
	// 将日期转换为时间戳
	time_t cancelTime = mktime(&cancelDate);
	time_t currentTime = mktime(&today);
	// 计算日期差值并向下取整
	int daysDifference = (int)difftime(cancelTime, currentTime) / (60 * 60 * 24);
	return daysDifference;
}










