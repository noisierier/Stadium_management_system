#include<stdio.h>
#include"rank.h"
#include"delay.h"
#include"Administrator.h"

const char* hallNames[] = { "���ೡ��","��Ӿ����","���ⳡ��" };// �ַ������������������


void administrator_menu_rank(void)//����Աͳ�����˵�����
{
    system("cls");
    readFromFile();  //��ȡ������Ϣ
    printf(" __________________________________________________\n");
    printf(" ________________������Ԥ��������ϵͳ______________\n");
    printf(" __________________________________________����Ա��\n");
    printf("\t\t ��ѡ����������\t\t\t\n");
    printf(" __________________________________________________\n");
    printf("|                                                  |\n");
    printf("|    1.��ѯȫ������                                |\n");
    printf("|                                                  |\n");
    printf("|    2.����Ԥ����ͳ��                              |\n");
    printf("|                                                  |\n");
    printf("|    3.����Ԥ����ͳ��                              |\n");
    printf("|                                                  |\n");
    printf("|    4.����Ӫҵ��ͳ��                              |\n");
    printf("|                                                  |\n");
    printf("|    5.�Ա�ͳ��                                    |\n");
    printf("|                                                  |\n");
    printf("|    6.����ͳ��                                    |\n");
    printf("|                                                  |\n");
    printf("|    7.�������ͳ��                                |\n");
    printf("|                                                  |\n");
    printf("|    8.����Ԥ��ʱ��ͳ��                            |\n");
    printf("|                                                  |\n");
    printf("|    9.����ʹ����ͳ��                              |\n");
    printf("|                                                  |\n");
    printf("|    x.������һ������                              |\n");
    printf("|                                                  |\n");
    printf("|__________________________________________________|\n");
    administrator_choose_rank();
}

void administrator_choose_rank(void)//����Աͳ��ѡ��ϵͳ
{
    char flag;
    printf("����������ѡ�");
    flag = getch();
    printf("%c", flag);
    delay(100);
    while (flag != '1' && flag != '2' && flag != '3' && flag != '4' && flag != '5' && flag != '6' && flag != '7' && flag != '8' && flag != '9' && flag != 'x' && flag != 'X')
    {
        printf("\n�������ʾ������'1'��'2'��'3'��'4'��'5'��'6'��'7'��'8'��'9'��'x'��");
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
        parseOrderFile("orderInformation.txt");//��ӡȫ������
        administrator_menu_rank_return();
        break;
    case '2':
        system("cls");
        countVenueBookings("orderInformation.txt");//���ݳ���Ԥ��������
        administrator_menu_rank_return();
        break;
    case '3':
        system("cls");
        countFieldBookings("orderInformation.txt");//���ݳ���Ԥ��������
        administrator_menu_rank_return();
        break;
    case '4':
        system("cls");
        countVenueBusinesVolume("orderInformation.txt");//���ݳ���Ӫҵ������
        administrator_menu_rank_return();
        break;
    case '5':
        system("cls");
        calculateGenderStatistics();//�Ա�ͳ�� 
        administrator_menu_rank_return();
    case '6':
        system("cls");
        calculateAgeDistribution();//����ͳ��
        administrator_menu_rank_return();
    case '7':
        system("cls");
        sortByRent();//���ݳ����������
        administrator_menu_rank_return();
    case '8':
        system("cls");
        calculateHotTime();//����Ԥ��ʱ��
        administrator_menu_rank_return();
    case '9':
        system("cls");
        calculatingUtilization();//���ݳ���ʱ��ε�ʹ����
        administrator_menu_rank_return();
    case 'x':system("cls");
        printf("���ڷ��ء�����������");
        delay(500);
        Scheduled_anagement();
        break;
    case 'X':system("cls");
        printf("���ڷ��ء�����������");
        delay(500);
        Scheduled_anagement();
        break;
    default:
        break;
    }
}

void administrator_menu_rank_return(void)//���ع���Աͳ�����˵�����
{
    printf("\n�������������һ�����棺");
    char a;
    a = getch();
    printf("%c", a);
    delay(100);
    if (a != NULL)
    {
        printf("\n���ڷ��ء�����������");
        delay(400);
        administrator_menu_rank();
    }
}

int parseOrderFile(const char* filename)// ��ȡ����ӡȫ��������Ϣ
{
    FILE* file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("�޷����ļ�");
        return 1;
    }
    char line[MAX_LINE_LENGTH];
    struct Order order;
    while (fgets(line, sizeof(line), file))
    {
        line[strcspn(line, "\n")] = '\0';// ȥ����ĩ�Ļ��з�
        if (strlen(line) == 0) // ����ǿ��У�������һ��
        {
            continue;
        }
        if (sscanf(line, "%[^,],%[^,],%d,%d,%[^,],%[^_]_%[^_]_%[^_]_%[^ ]", // ʹ��sscanf����������Ϣ������������Ա�
            order.username, order.fullName, &order.age, &order.gender, order.orderNumber, order.venue, order.venueNumber, order.date, order.time) == 9) // ��ӡ������Ϣ
        {
            printf("�û���: %s\n", order.username);
            printf("�û�����: %s\n", order.fullName);
            printf("����: %d\n", order.age);
            printf("�Ա�: %d\n", order.gender);
            printf("������: %s\n", order.orderNumber);
            printf("���ݺ�: %s\n", order.venue);
            printf("���غ�: %s\n", order.venueNumber);
            printf("Ԥ������: %s\n", order.date);
            printf("Ԥ��ʱ��: %s\n", order.time);
            printf("\n");

        }
        else
        {
            printf("�޷�����������Ϣ: %s\n", line);
        }
    }
    fclose(file);
    return 0;
}

void countVenueBookings(const char* filename) // ��������ͳ��ÿ�����ݵ�Ԥ������������
{
    FILE* file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("�޷����ļ�");
        return;
    }
    char line[MAX_LINE_LENGTH];
    int hall1Bookings = 0;
    int hall2Bookings = 0;
    int hall3Bookings = 0;


    while (fgets(line, sizeof(line), file))  // ������Ӹ��� hallXBookings ��������������ĳ�������
    {
        line[strcspn(line, "\n")] = '\0';
        if (strlen(line) == 0)
        {
            continue;
        }
        struct Order order;
        if (sscanf(line, "%[^,],%[^,],%d,%d,%[^,],%[^_]_%[^_]_%[^_]_%[^ ]",
            order.username, order.fullName, &order.age, &order.gender, order.orderNumber, order.venue, order.venueNumber, order.date, order.time) == 9) // ���ݶ����еĳ����������Ӷ�Ӧ���ݵ�Ԥ������
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
    printf("���ೡ�� Ԥ������: %d\n", hall1Bookings);// ��ӡÿ�����ݵ�Ԥ������
    printf("��Ӿ���� Ԥ������: %d\n", hall2Bookings);
    printf("���ⳡ�� Ԥ������: %d\n", hall3Bookings);
    char choice;
    printf("\n��ѡ������ʽ��\n");
    printf("1. �Ӹߵ�������\n");
    printf("2. �ӵ͵�������\n");
    printf("��ѡ��1��2���� ");
    choice = getch();
    printf("%c",choice);
    delay(100);
   while(choice != '1' && choice != '2')
    {
        printf("\n���������������������ѡ�");
        choice = getch();
        printf("%c",choice);
        delay(100);
    }
    if (choice == '1') // �Ӹߵ�������ð������
    {
        int sortedBookings[] = { hall1Bookings, hall2Bookings, hall3Bookings };
        int n = sizeof(sortedBookings) / sizeof(sortedBookings[0]);

        for (int i = 0; i < n - 1; i++)
        {
            for (int j = 0; j < n - i - 1; j++)
            {
                if (sortedBookings[j] < sortedBookings[j + 1])   // ����Ԥ������
                {
                    int temp = sortedBookings[j];
                    sortedBookings[j] = sortedBookings[j + 1];
                    sortedBookings[j + 1] = temp;
                }
            }
        }
        printf("\n\n�Ӹߵ��������ĳ���Ԥ��������\n"); // ��ӡ�����ĳ���Ԥ������
        for (int i = 0; i < n; i++)
        {
            if (i == 0)
            {
                printf("���ೡ�� Ԥ������: %d\n", sortedBookings[i]);
            }
            else if (i == 1)
            {
                printf("��Ӿ���� Ԥ������: %d\n", sortedBookings[i]);
            }
            else if (i == 2)
            {
                printf("���ⳡ�� Ԥ������: %d\n", sortedBookings[i]);
            }
        }
        int mostPopularIndex = 0;// �ҵ����ܻ�ӭ�ĳ���
        for (int i = 1; i < n; i++)
        {
            if (sortedBookings[i] > sortedBookings[mostPopularIndex])
            {
                mostPopularIndex = i;
            }
        }

        if (mostPopularIndex == 0)  // ��ʾ���ܻ�ӭ�ĳ���
        {
            printf("\n���ܻ�ӭ�ĳ����ǣ����ೡ��\n");
        }
        else if (mostPopularIndex == 1)
        {
            printf("\n���ܻ�ӭ�ĳ����ǣ���Ӿ����\n");
        }
        else if (mostPopularIndex == 2)
        {
            printf("\n���ܻ�ӭ�ĳ����ǣ����ⳡ��\n");
        }
    }
    else if (choice == '2')// �ӵ͵�������ð������ķ�������
    {
        int sortedBookings[] = { hall1Bookings, hall2Bookings, hall3Bookings };
        char* venueNames[] = { "���ೡ��", "��Ӿ����", "���ⳡ��" }; // ��Ӧ�ĳ�������
        int n = sizeof(sortedBookings) / sizeof(sortedBookings[0]);

        for (int i = 0; i < n - 1; i++)
        {
            for (int j = 0; j < n - i - 1; j++)
            {
                if (sortedBookings[j] > sortedBookings[j + 1])// ����Ԥ������
                {
                    int temp = sortedBookings[j];
                    sortedBookings[j] = sortedBookings[j + 1];
                    sortedBookings[j + 1] = temp;
                    char* tempName = venueNames[j];// ͬʱ������Ӧ�ĳ�������
                    venueNames[j] = venueNames[j + 1];
                    venueNames[j + 1] = tempName;
                }
            }
        }
        printf("\n\n�ӵ͵��������ĳ���Ԥ��������\n");
        for (int i = 0; i < n; i++) // ��ӡ�����ĳ���Ԥ������
        {
            printf("%s Ԥ������: %d\n", venueNames[i], sortedBookings[i]);
        }
        int mostPopularIndex = 0;// �ҵ����ܻ�ӭ�ĳ���
        for (int i = 1; i < n; i++)
        {
            if (sortedBookings[i] > sortedBookings[mostPopularIndex])
            {
                mostPopularIndex = i;
            }
        }

        // ��ʾ���ܻ�ӭ�ĳ���
        printf("\n���ܻ�ӭ�ĳ����ǣ�%s\n", venueNames[mostPopularIndex]);
    }
}

void countFieldBookings(const char* filename) // ��������ͳ��ÿ�����ص�Ԥ������������
{
    FILE* file = fopen(filename, "r");
    if (file == NULL) 
    {
        perror("�޷����ļ�");
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
        if (sscanf(line, "%[^,],%[^,],%d,%d,%[^,],%[^_]_%[^_]_%[^_]_%[^ ]",// ���ݶ����еĳ��ݺͳ����������Ӷ�Ӧ��Ԥ������
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
    // ��ӡÿ�����ݺͳ��ص�Ԥ������
    printf("���ೡ�� ����1 Ԥ������: %d\n", hall1Field1Bookings);
    printf("���ೡ�� ����2 Ԥ������: %d\n", hall1Field2Bookings);
    printf("��Ӿ���� ����1 Ԥ������: %d\n", hall2Field1Bookings);
    printf("��Ӿ���� ����2 Ԥ������: %d\n", hall2Field2Bookings);
    printf("���ⳡ�� ����1 Ԥ������: %d\n", hall3Field1Bookings);
    printf("���ⳡ�� ����2 Ԥ������: %d\n", hall3Field2Bookings);
    char choice;
    printf("\n��ѡ������ʽ��\n");
    printf("1. �Ӹߵ�������\n");
    printf("2. �ӵ͵�������\n");
    printf("��ѡ��1��2���� ");
    choice = getch();
    printf("%c", choice);
    delay(100);
    while (choice != '1' && choice != '2')
    {
        printf("\n���������������������ѡ�");
        choice = getch();
        printf("%c", choice);
        delay(100);
    }
    // ���ݹ���Ա��ѡ�����򲢴�ӡ
    if (choice == '1')// ð�����򣬴Ӹߵ���
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
                    int temp = bookings[j];// ��������Ԫ��
                    bookings[j] = bookings[j + 1];
                    bookings[j + 1] = temp;
                }
            }
        }

        // ��ӡ�����Ľ��
        printf("\n\n�Ӹߵ���������Ԥ��������\n");
        printf("���ೡ�� ����1: %d\n", bookings[0]);
        printf("���ೡ�� ����2: %d\n", bookings[1]);
        printf("��Ӿ���� ����1: %d\n", bookings[2]);
        printf("��Ӿ���� ����2: %d\n", bookings[3]);
        printf("���ⳡ�� ����1: %d\n", bookings[4]);
        printf("���ⳡ�� ����2: %d\n", bookings[5]);

        // �ҵ����ܻ�ӭ�ĳ���
        int mostPopularBookings = bookings[0];
        printf("\n���ܻ�ӭ�ĳ��أ�\n");
        if (hall1Field1Bookings == mostPopularBookings)
        {
            printf("���ೡ�� ����1\n");
        }
        if (hall1Field2Bookings == mostPopularBookings) 
        {
            printf("���ೡ�� ����2\n");
        }
        if (hall2Field1Bookings == mostPopularBookings) 
        {
            printf("��Ӿ���� ����1\n");
        }
        if (hall2Field2Bookings == mostPopularBookings)
        {
            printf("��Ӿ���� ����2\n");
        }
        if (hall3Field1Bookings == mostPopularBookings) 
        {
            printf("���ⳡ�� ����1\n");
        }
        if (hall3Field2Bookings == mostPopularBookings)
        {
            printf("���ⳡ�� ����2\n");
        }
    }
    else if (choice == '2') // ð�����򣬴ӵ͵���
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
            "���ೡ�� ����1", "���ೡ�� ����2",
            "��Ӿ���� ����1", "��Ӿ���� ����2",
            "���ⳡ�� ����1", "���ⳡ�� ����2"
        };

        for (int i = 0; i < numBookings - 1; i++) 
        {
            for (int j = 0; j < numBookings - i - 1; j++) 
            {
                if (bookings[j] > bookings[j + 1]) 
                {
                    // ��������Ԫ��
                    int tempBooking = bookings[j];
                    bookings[j] = bookings[j + 1];
                    bookings[j + 1] = tempBooking;

                    // ������Ӧ������
                    char* tempName = hallNames[j];
                    hallNames[j] = hallNames[j + 1];
                    hallNames[j + 1] = tempName;
                }
            }
        }

        // ��ӡ�����Ľ��
        printf("\n\n�ӵ͵���������Ԥ��������\n");
        for (int i = 0; i < numBookings; i++)
        {
            printf("%s: %d\n", hallNames[i], bookings[i]);
        }

        // �ҵ����ܻ�ӭ�ĳ���
        int mostPopularBookings = bookings[numBookings - 1];
        printf("\n���ܻ�ӭ�ĳ��أ�\n");
        if (hall1Field1Bookings == mostPopularBookings) 
        {
            printf("���ೡ�� ����1\n");
        }
        if (hall1Field2Bookings == mostPopularBookings) 
        {
            printf("���ೡ�� ����2\n");
        }
        if (hall2Field1Bookings == mostPopularBookings) 
        {
            printf("��Ӿ���� ����1\n");
        }
        if (hall2Field2Bookings == mostPopularBookings)
        {
            printf("��Ӿ���� ����2\n");
        }
        if (hall3Field1Bookings == mostPopularBookings) 
        {
            printf("���ⳡ�� ����1\n");
        }
        if (hall3Field2Bookings == mostPopularBookings) 
        {
            printf("���ⳡ�� ����2\n");
        }
    }
}

void countVenueBusinesVolume(const char* filename)//ͳ�Ƴ��ݵ�Ӫҵ��+����
{
    FILE* file = fopen(filename, "r");
    if (file == NULL) 
    {
        perror("�޷����ļ�");
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
        if (sscanf(line, "%[^,],%[^,],%d,%d,%[^,],%[^_]_%[^_]_%[^_]_%[^ ]",// ���ݶ����еĳ��ݺͳ����������Ӷ�Ӧ��Ԥ������
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

    // ��ӡÿ�����ݺͳ��ص�Ԥ������
    float businessVolume1_1 = halls[0].courts[0].rentRerHour * hall1Field1Bookings;
    float businessVolume1_2 = halls[0].courts[1].rentRerHour * hall1Field2Bookings;
    float businessVolume2_1 = halls[1].courts[0].rentRerHour * hall2Field1Bookings;
    float businessVolume2_2 = halls[1].courts[1].rentRerHour * hall2Field2Bookings;
    float businessVolume3_1 = halls[2].courts[0].rentRerHour * hall3Field1Bookings;
    float businessVolume3_2 = halls[2].courts[1].rentRerHour * hall3Field2Bookings;
    printf("%s ����1 Ӫҵ��: %.2f\n", hallNames[0], businessVolume1_1);
    printf("%s ����2 Ӫҵ��: %.2f\n", hallNames[0], businessVolume1_2);
    printf("%s ����1 Ӫҵ��: %.2f\n", hallNames[1], businessVolume2_1);
    printf("%s ����2 Ӫҵ��: %.2f\n", hallNames[1], businessVolume2_2);
    printf("%s ����1 Ӫҵ��: %.2f\n", hallNames[2], businessVolume3_1);
    printf("%s ����2 Ӫҵ��: %.2f\n", hallNames[2], businessVolume3_2);

    // ���ݹ���Ա��ѡ�����򲢴�ӡ
    char choice;
    printf("\n��ѡ������ʽ��1.�Ӹߵ��ͣ�2.�ӵ͵��ߣ���");
    choice = getch();
    printf("%c", choice);
    delay(100);
    while (choice != '1' && choice != '2')
    {
        printf("\n���������������������ѡ�");
        choice = getch();
        printf("%c", choice);
        delay(100);
    }
    if (choice == '1')
    {
        // �Ӹߵ�������
        float businessVolumes[] = 
        {
            businessVolume1_1, businessVolume1_2,
            businessVolume2_1, businessVolume2_2,
            businessVolume3_1, businessVolume3_2
        };
        char* hallNames[] = 
        {
            "���ೡ�� ����1", "���ೡ�� ����2",
            "��Ӿ���� ����1", "��Ӿ���� ����2",
            "���ⳡ�� ����1", "���ⳡ�� ����2"
        };
        int numHalls = sizeof(hallNames) / sizeof(hallNames[0]);

        for (int i = 0; i < numHalls - 1; i++) 
        {
            for (int j = 0; j < numHalls - i - 1; j++)
            {
                if (businessVolumes[j] < businessVolumes[j + 1]) 
                {
                    // ��������Ԫ��
                    float tempVolume = businessVolumes[j];
                    businessVolumes[j] = businessVolumes[j + 1];
                    businessVolumes[j + 1] = tempVolume;
                    // ������Ӧ������
                    char* tempName = hallNames[j];
                    hallNames[j] = hallNames[j + 1];
                    hallNames[j + 1] = tempName;
                }
            }
        }

        // ��ӡ�����Ľ��
        printf("\n\n�Ӹߵ���������Ӫҵ�\n");
        for (int i = 0; i < numHalls; i++) {
            printf("%s Ӫҵ��: %.2f\n", hallNames[i], businessVolumes[i]);
        }

        // �ҵ�Ӫҵ����ߵĳ���
        float mostProfitableVolume = businessVolumes[0];
        printf("\nӪҵ����ߵĳ��أ�\n");
        for (int i = 0; i < numHalls; i++) {
            if (businessVolumes[i] == mostProfitableVolume) {
                printf("%s\n", hallNames[i]);
            }
        }
    }
    else if (choice == '2') {
        // �ӵ͵�������
        float businessVolumes[] = {
            businessVolume1_1, businessVolume1_2,
            businessVolume2_1, businessVolume2_2,
            businessVolume3_1, businessVolume3_2
        };
        char* hallNames[] = {                                                                       //�ض���
            "���ೡ�� ����1", "���ೡ�� ����2",
            "��Ӿ���� ����1", "��Ӿ���� ����2",
            "���ⳡ�� ����1", "���ⳡ�� ����2"
        };
        int numHalls = sizeof(hallNames) / sizeof(hallNames[0]);

        for (int i = 0; i < numHalls - 1; i++) {
            for (int j = 0; j < numHalls - i - 1; j++) {
                if (businessVolumes[j] > businessVolumes[j + 1]) {
                    // ��������Ԫ��
                    float tempVolume = businessVolumes[j];
                    businessVolumes[j] = businessVolumes[j + 1];
                    businessVolumes[j + 1] = tempVolume;

                    // ������Ӧ������
                    char* tempName = hallNames[j];
                    hallNames[j] = hallNames[j + 1];
                    hallNames[j + 1] = tempName;
                }
            }
        }

        // ��ӡ�����Ľ��
        printf("\n\n�ӵ͵���������Ӫҵ�\n");
        for (int i = 0; i < numHalls; i++) {
            printf("%s Ӫҵ��: %.2f\n", hallNames[i], businessVolumes[i]);
        }

        // �ҵ�Ӫҵ����ߵĳ���
        float mostProfitableVolume = businessVolumes[numHalls - 1];
        printf("\nӪҵ����ߵĳ��أ�\n");
        for (int i = 0; i < numHalls; i++) {
            if (businessVolumes[i] == mostProfitableVolume) {
                printf("%s\n", hallNames[i]);
            }
        }
    }
}

void calculateGenderStatistics() // ͳ��ÿ�����ص���Ů�����Լ�ÿ�����ݵ���Ů��������ͳ����ϲ���ĳ���
{
    typedef struct 
    {
        int maleCount;   // ��������
        int femaleCount; // Ů������
    } VenueGenderStats;
    FILE* file = fopen("orderInformation.txt", "r");
    if (file == NULL) 
    {
        perror("�޷����ļ�");
        return;
    }

    char line[MAX_LINE_LENGTH];
    struct Order order;

    // ����һ���������洢ÿ�����ص��Ա�ͳ����Ϣ
    GenderStats venueGenderStatistics[MAX_VENUES][MAX_FIELDS] = { 0 };

    // ����һ���������洢ÿ�����ݵ��Ա�ͳ����Ϣ
    VenueGenderStats venueStats[MAX_VENUES] = { 0 };

    // ��������������������Ů����ϲ���ĳ���
    int favoriteMaleVenue = -1;
    int favoriteFemaleVenue = -1;
    int maxMaleCount = -1;
    int maxFemaleCount = -1;

    while (fgets(line, sizeof(line), file)) 
    {
        // ȥ����ĩ�Ļ��з�
        line[strcspn(line, "\n")] = '\0';

        // ����ǿ��л�ﵽ�ļ�ĩβ��������һ��
        if (strlen(line) == 0) 
        {
            continue;
        }

        // ʹ��sscanf����������Ϣ������������Ա�
        if (sscanf(line, "%[^,],%[^,],%d,%d,%[^,],%[^_]_%[^_]_%[^_]_%[^ ]",
            order.username, order.fullName, &order.age, &order.gender, order.orderNumber, order.venue, order.venueNumber, order.date, order.time) == 9) {
            // ͳ���Ա�
            int hallNum = order.venue[4] - '0' - 1; // ���ݺ��ڶ�����Ϣ�ĵ�5���ַ�
            int courtNum = order.venueNumber[0] - '0' - 1; // ���غ��ڶ�����Ϣ�ĵ�1���ַ�

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

    // ��ӡÿ�����ص���Ů����
    printf("������Ůͳ��:\n");
    for (int i = 0; i < MAX_VENUES; i++)
    {
        for (int j = 0; j < MAX_FIELDS; j++)
        {
            printf("%s ����%d: ����%d��, Ů��%d��\n", hallNames[i], j + 1, venueGenderStatistics[i][j].maleCount, venueGenderStatistics[i][j].femaleCount);
        }
    }

    // ��ӡÿ�����ݵ���Ů����
    printf("\nÿ�����ݵ���Ů����:\n");
    for (int i = 0; i < MAX_VENUES; i++) 
    {
        printf("%s: ����%d��, Ů��%d��\n", hallNames[i], venueStats[i].maleCount, venueStats[i].femaleCount);

        // ������ϲ���ĳ���
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

    // ��ӡ��ϲ���ĳ���
    if (favoriteMaleVenue != -1) {
        printf("\n������ϲ���ĳ���: %s (����%d��)\n", hallNames[favoriteMaleVenue], maxMaleCount);
    }
    if (favoriteFemaleVenue != -1) {
        printf("Ů����ϲ���ĳ���: %s (Ů��%d��)\n", hallNames[favoriteMaleVenue], maxFemaleCount);
    }
}

void calculateAgeDistribution() // ͳ��ÿ�����ص�����ֲ�
{
    // ����һ���µĽṹ�����洢��ͬ���ص�����ֲ�
    typedef struct 
    {
        int age0to15Count;   // ����0-15������
        int age16to40Count;  // ����16-40������
        int age41to150Count; // ����41-150������
    } AgeDistribution;

    FILE* file = fopen("orderInformation.txt", "r");
    if (file == NULL) 
    {
        perror("�޷����ļ�");
        return;
    }

    char line[MAX_LINE_LENGTH];
    struct Order order;

    // ����һ���������洢ÿ�����ص�����ֲ�ͳ����Ϣ
    AgeDistribution venueAgeDistribution[MAX_VENUES][MAX_FIELDS] = { 0 };

    while (fgets(line, sizeof(line), file)) 
    {
        // ȥ����ĩ�Ļ��з�
        line[strcspn(line, "\n")] = '\0';

        // ����ǿ��л�ﵽ�ļ�ĩβ��������һ��
        if (strlen(line) == 0) 
        {
            continue;
        }

        // ʹ��sscanf����������Ϣ������������Ա�
        if (sscanf(line, "%[^,],%[^,],%d,%d,%[^,],%[^_]_%[^_]_%[^_]_%[^ ]",
            order.username, order.fullName, &order.age, &order.gender, order.orderNumber, order.venue, order.venueNumber, order.date, order.time) == 9) {
            // ͳ������ֲ�
            int hallNum = order.venue[4] - '0' - 1; // ���ݺ��ڶ�����Ϣ�ĵ�5���ַ�
            int courtNum = order.venueNumber[0] - '0' - 1; // ���غ��ڶ�����Ϣ�ĵ�1���ַ�

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

    // ��ӡÿ�����ص�����ֲ�
    printf("��������ֲ�ͳ��:\n");
    for (int i = 0; i < MAX_VENUES; i++) {
        for (int j = 0; j < MAX_FIELDS; j++) {
            printf("%s ����%d: ����0-15:%d��, ����16-40:%d��, ����41����:%d��\n",
                hallNames[i],
                j + 1,
                venueAgeDistribution[i][j].age0to15Count,
                venueAgeDistribution[i][j].age16to40Count,
                venueAgeDistribution[i][j].age41to150Count);
        }
    }
}

void sortByRent() // ��ȡ����������г��أ�ͬʱ��ӡ�����ĳ�����Ϣ
{
    int descending; // ��־�Ƿ������У�1��ʾ����0��ʾ����
    char choice;
    printf("��ѡ������ʽ��1��ʾ����0��ʾ����: ");
    choice = getch();
    printf("%c", choice);
    delay(100);
    while (choice != '1' && choice != '0')
    {
        printf("\n���������������������ѡ�");
        choice = getch();
        printf("%c", choice);
        delay(100);
    }
    descending = choice - '0';
    FILE* file = fopen("site.txt", "r");
    if (file == NULL) 
    {
        printf("�޷����ļ�\n");
        return;
    }
    Court allCourts[MAX_VENUES * MAX_FIELDS];
    int allCourtsCount = 0;
    int hallNums[MAX_VENUES * MAX_FIELDS]; // ���ڴ洢���ض�Ӧ�ĳ��ݱ��

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

            // ��������ӵ��ϲ���������У�����¼��Ӧ�ĳ��ݱ��
            allCourts[allCourtsCount] = halls[i].courts[j];
            hallNums[allCourtsCount] = halls[i].hallNum;
            allCourtsCount++;
        }
    }

    // ʹ��ð����������������г���
    for (int i = 0; i < allCourtsCount - 1; i++) 
    {
        for (int j = 0; j < allCourtsCount - i - 1; j++) 
        {
            int compareValue = (descending ? allCourts[j].rentRerHour > allCourts[j + 1].rentRerHour : allCourts[j].rentRerHour < allCourts[j + 1].rentRerHour);
            if (compareValue) 
            {
                // ��������
                Court tempCourt = allCourts[j];
                allCourts[j] = allCourts[j + 1];
                allCourts[j + 1] = tempCourt;
                // �������ݱ��
                int tempHallNum = hallNums[j];
                hallNums[j] = hallNums[j + 1];
                hallNums[j + 1] = tempHallNum;
            }
        }
    }

    fclose(file);


    // ��ӡ�����ĳ�����Ϣ�������������ƺͳ��ر��
    printf("\n\n�����%s���������г�����Ϣ:\n", (descending ? "����" : "����"));
    for (int i = 0; i < allCourtsCount; i++)
    {
        int hallIndex = hallNums[i] - 1;
        printf("%s ����%d ���ÿСʱ: %d\n", hallNames[hallIndex], allCourts[i].courtNum, allCourts[i].rentRerHour);
    }
}

int compareUsage(const void* a, const void* b)//�Ƚ��û�����
{
    return (*(int*)b - *(int*)a);
}

void calculateHotTime() // ͳ�Ʋ���ӡÿ��������ÿ��ʱ��ε�ԤԼ���
{
    FILE* file = fopen("site.txt", "r");
    if (file == NULL)
    {
        printf("�޷����ļ�\n");
        return;
    }

    // ��ʼ������������ͳ������
    int courtUsage[3][2][16] = { 0 }; // [����][����][ʱ���]
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
                int totalUsage = 0; // ��ǰʱ��ε���������
                for (int d = 0; d < 7; d++) 
                {
                    totalUsage += halls[i].courts[j].time[d][k];
                }
                // �ۼ�������
                courtUsage[hallNum][courtNum][k] += totalUsage;
            }
        }
    }
    fclose(file);
    printf("1.���ೡ�� 2.��Ӿ���� 3.���ⳡ��");
    printf("\n��ѡ��Ҫ�鿴�ĳ��ݱ��:");

    int selectedHall;
    char choice,key;
    choice = getch();
    printf("%c", choice);
    delay(100);
    while (choice != '1' && choice != '2' && choice != '3')
    {
        printf("\n���������������������ѡ�");
        choice = getch();
        printf("%c", choice);
        delay(100);
    }
    selectedHall = choice - '0';
    printf("\n\n1.1���� 2.2����");
    printf("\n��ѡ��Ҫ�鿴�ĳ��ر��:");
    int selectedCourt;
    key = getch();
    printf("%c", key);
    delay(100);
    while (key != '1' && key != '2')
    {
        printf("\n���������������������ѡ�");
        key = getch();
        printf("%c", key);
        delay(100);
    }
    selectedCourt = key - '0';
    selectedHall--; // ���û�ѡ��ת��Ϊ��������
    selectedCourt--;
    printf("\n\n%s ����%d �ĳ���������ͳ��:\n", hallNames[selectedHall], selectedCourt + 1);
    // ����һ������������������ͬʱά��ʱ������Ƶĸ�������
    int sortedUsage[16];
    const char* sortedTimePeriods[16];
    for (int k = 0; k < 16; k++) 
    {
        sortedUsage[k] = courtUsage[selectedHall][selectedCourt][k];
        sortedTimePeriods[k] = timePeriods[k];
    }
    // ʹ��ð������Ը��������������ͬʱ����ʱ������Ƶ�ͬ��
    for (int i = 0; i < 16 - 1; i++) 
    {
        for (int j = 0; j < 16 - i - 1; j++) 
        {
            if (sortedUsage[j] < sortedUsage[j + 1]) 
            {
                // ����������
                int tempUsage = sortedUsage[j];
                sortedUsage[j] = sortedUsage[j + 1];
                sortedUsage[j + 1] = tempUsage;
                // ����ʱ�������
                const char* tempTimePeriod = sortedTimePeriods[j];
                sortedTimePeriods[j] = sortedTimePeriods[j + 1];
                sortedTimePeriods[j + 1] = tempTimePeriod;
            }
        }
    }

    // ��ӡ������ʱ��������������ܻ�ӭʱ�������
    for (int k = 0; k < 16; k++) 
    {
        printf("%s: %d��\n", sortedTimePeriods[k], sortedUsage[k]);
    }

    // �ҵ����ܻ�ӭ��ʱ���
    int mostPopularTimeIndex = 0;
    printf("\n����������ܻ�ӭ��ʱ����ǣ�%s\n", sortedTimePeriods[mostPopularTimeIndex]);
}

void calculatingUtilization() //ͳ�Ʋ���ӡÿ��������ÿ��ʱ��εĳ���������

{
    FILE* file = fopen("site.txt", "r");
    if (file == NULL) {
        printf("�޷����ļ�\n");
        return;
    }

    // ��ʼ������������ͳ������
    int courtUsage[3][2][16] = { 0 }; // [����][����][ʱ���]
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
                int totalUsage = 0; // ��ǰʱ��ε���������
                for (int d = 0; d < 7; d++) 
                {
                    totalUsage += halls[i].courts[j].time[d][k];
                }
                // �ۼ�������
                courtUsage[hallNum][courtNum][k] += totalUsage;
            }
        }
    }

    fclose(file);

    printf("1.���ೡ�� 2.��Ӿ���� 3.���ⳡ��");
    printf("\n��ѡ��Ҫ�鿴�ĳ��ݱ��:");

    char choice,key;
    int selectedHall; 
    choice = getch();
    printf("%c", choice);
    delay(100);
    while (choice != '1' && choice != '2' && choice != '3')
    {
        printf("\n���������������������ѡ�");
        choice = getch();
        printf("%c", choice);
        delay(100);
    }
    selectedHall = choice - '0';
   
    printf("\n\n1.1���� 2.2����");
    printf("\n��ѡ��Ҫ�鿴�ĳ��ر��:");
    int selectedCourt;
  
    key = getch();
    printf("%c", key);
    delay(100);
    while (key != '1' && key != '2')
    {
        printf("\n���������������������ѡ�");
        key = getch();
        printf("%c", key);
        delay(100);
    }

    selectedCourt = key - '0';
    selectedHall--; // ���û�ѡ��ת��Ϊ��������
    selectedCourt--;
    printf("\n\n%s ����%d �ĳ���������ͳ��:\n", hallNames[selectedHall], selectedCourt + 1);
    // ����һ������������������ͬʱά��ʱ������Ƶĸ�������
    double courtUtilization[16];
    const char* sortedTimePeriods[16];
    for (int k = 0; k < 16; k++)
    {
        int totalUsage = courtUsage[selectedHall][selectedCourt][k];
        int maxPerson = halls[selectedHall].courts[selectedCourt].maxPerson;
        courtUtilization[k] = (double)totalUsage / (maxPerson * 7) * 100.0;
        sortedTimePeriods[k] = timePeriods[k];
    }
    // ʹ��ð������Ը��������������ͬʱ����ʱ������Ƶ�ͬ��
    for (int i = 0; i < 16 - 1; i++) 
    {
        for (int j = 0; j < 16 - i - 1; j++)
        {
            if (courtUtilization[j] < courtUtilization[j + 1])
            {
                // ����������
                double tempUtilization = courtUtilization[j];
                courtUtilization[j] = courtUtilization[j + 1];
                courtUtilization[j + 1] = tempUtilization;
                // ����ʱ�������
                const char* tempTimePeriod = sortedTimePeriods[j];
                sortedTimePeriods[j] = sortedTimePeriods[j + 1];
                sortedTimePeriods[j + 1] = tempTimePeriod;
            }
        }
    }
    // ��ӡ�����ĳ��������ʼ����������ʱ���
    for (int k = 0; k < 16; k++)
    {
        printf("%s: %.2lf%%\n", sortedTimePeriods[k], courtUtilization[k]);
    }
    // �ҵ����������ʱ���
    int mostUtilizedTimeIndex = 0;
    printf("\n���������������ʵ�ʱ����ǣ�%s\n", sortedTimePeriods[mostUtilizedTimeIndex]);
}

void user_menu_rank(void)//�û�ͳ�����˵�����
{
    system("cls");
    readFromFile();  //��ȡ������Ϣ
    printf(" __________________________________________________\n");
    printf(" _________________������Ԥ��ϵͳ___________________\n");
    printf(" __________________________________________�û��汾\n");
    printf("\t\t ��ѡ����������\t\t\t\n");
    printf(" __________________________________________________\n");
    printf("|                                                  |\n");
    printf("|    1.����Ԥ����ͳ��                              |\n");
    printf("|                                                  |\n");
    printf("|    2.����Ԥ����ͳ��                              |\n");
    printf("|                                                  |\n");
    printf("|    3.�Ա�ͳ��                                    |\n");
    printf("|                                                  |\n");
    printf("|    4.����ͳ��                                    |\n");
    printf("|                                                  |\n");
    printf("|    5.�������ͳ��                                |\n");
    printf("|                                                  |\n");
    printf("|    6.����Ԥ��ʱ��ͳ��                            |\n");
    printf("|                                                  |\n");
    printf("|    7.����ʹ����ͳ��                              |\n");
    printf("|                                                  |\n");
    printf("|    8.������һ������                              |\n");
    printf("|                                                  |\n");
    printf("|__________________________________________________|\n");
    user_choose_rank();
}

void user_choose_rank(void)//�û�ͳ��ѡ��ϵͳ
{
    char flag;
    printf("����������ѡ�");
    flag = getch();
    printf("%c", flag);
    delay(100);
    while (flag != '1' && flag != '2' && flag != '3' && flag != '4' && flag != '5' && flag != '6' && flag != '7' && flag != '8' )
    {
        printf("\n�������ʾ������'1'��'2'��'3'��'4'��'5'��'6'��'7'��'8'��");
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
        countVenueBookings("orderInformation.txt");//���ݳ���Ԥ��������
        user_menu_rank_return();
        break;
    case '2':
        system("cls");
        countFieldBookings("orderInformation.txt");//���ݳ���Ԥ��������
        user_menu_rank_return();
        break;
    case '3':
        system("cls");
        calculateGenderStatistics();//�Ա�ͳ�� 
        user_menu_rank_return();
    case '4':
        system("cls");
        calculateAgeDistribution();//����ͳ��
        user_menu_rank_return();
    case '5':
        system("cls");
        sortByRent();//���ݳ����������
        user_menu_rank_return();
    case '6':
        system("cls");
        calculateHotTime();//����Ԥ��ʱ��
        user_menu_rank_return();
    case '7':
        system("cls");
        calculatingUtilization();//���ݳ���ʱ��ε�ʹ����
        user_menu_rank_return();
    case '8':system("cls");
        printf("���ڷ��ء�����������");
        delay(500);
        reserve_message(); 
        break;
    default:
        break;
    }
}

void user_menu_rank_return(void)//�����û�ͳ�����˵�����
{
    printf("\n�������������һ�����棺");
    char a;
    a = getch();
    printf("%c", a);
    delay(100);
    if (a != NULL)
    {
        printf("\n���ڷ��ء�����������");
        delay(400);
        user_menu_rank();
    }
}