#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
int linesToInsert = 19;
int num = 3;


void insertCourtData(const char* filename) {



    int venueChoice; 
    char searchString[20] = ""; 
    char venueCodes[][10] = { "0xs0001", "0xs0003", "0xs0005" }; 
    printf("��ѡ�񳡹�:\n"); 
    printf("1. ����1\n");
    printf("2. ����2\n"); 
    printf("3. ����3\n"); 
    while (getchar() != '\n'); // ������뻺����
    scanf("%d", &venueChoice); 
    if (venueChoice < 1 || venueChoice > 3) { 
        printf("��Ч��ѡ��\n"); 
        return; 
    } 
    snprintf(searchString, sizeof(searchString), "%s", venueCodes[venueChoice - 1]); 
    char newText[1000] = ""; 
    FILE* file = fopen(filename, "r+");



    if (file == NULL) {
        printf("�޷����ļ�\n");
        return;
    }

    char line[1000];
    char inputLine[100];

    snprintf(newText, sizeof(newText), "%d", num);
    strcat(newText, "\n");


    while (1)
    {
        int isValidInput = 1;
        printf("�������³��ص����/h:\n");
        // �����û�������ı����Կ��н���
        while (getchar() != '\n'); // ������뻺����
        fgets(inputLine, sizeof(inputLine), stdin);

        // ��������Ƿ�����������ַ�

        for (size_t i = 0; i < strlen(inputLine); i++)
        {
            if (!isdigit(inputLine[i]) && inputLine[i] != '\n')
            {
                isValidInput = 0; // ��������������ַ�
                break;
            }
        }

        if (!isValidInput) 
        {
            printf("��Ч���룬���������֡�\n");
        }
        else {
            printf("���ɹ����롣\n\n");
            strcat(newText, inputLine);
            break;
        }
    }
    printf("�������³��ı��:\n");
    fgets(inputLine, sizeof(inputLine), stdin);

    size_t inputLineLength = strlen(inputLine);
    if (inputLineLength > 0 && inputLine[inputLineLength - 1] == '\n') {
        inputLine[inputLineLength - 1] = '\0';
    }

    strcat(newText, inputLine);
    printf("���ر�ųɹ����롣\n\n");

    strcat(newText, "\n0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n");


    while (1) {
        int isValidInput = 1; // ��ÿ��ѭ����ʼʱ����Ϊ1

        printf("�������³������������:\n");
        // �����û�������ı����Կ��н���
        fgets(inputLine, sizeof(inputLine), stdin);

        // ��������Ƿ�����������ַ�
        for (size_t i = 0; i < strlen(inputLine); i++)
        {
            if (!isdigit(inputLine[i]) && inputLine[i] != '\n') 
            {
                isValidInput = 0; // ��������������ַ�
                break;
            }
        }

        if (!isValidInput) 
        {
            printf("��Ч���룬���������֡�\n");
        }
        else {
            // ��������Ի��з���β�������滻Ϊ null ��ֹ��
            size_t inputLineLength = strlen(inputLine);
            if (inputLineLength > 0 && inputLine[inputLineLength - 1] == '\n')
            {
                inputLine[inputLineLength - 1] = '\0';
            }

            // ��������ַ���׷�ӵ� newText ��
            strcat(newText, inputLine);
            printf("������������ɹ����롣\n\n");
            break;
        }
    }

    FILE* tempFile = tmpfile();
    if (tempFile == NULL) 
    {
        printf("�޷�������ʱ�ļ�\n");
        fclose(file);
        return;
    }

    while (fgets(line, sizeof(line), file)) {
        fputs(line, tempFile);
        if (strstr(line, searchString)) {
            for (int i = 0; i < linesToInsert; i++) {
                if (fgets(line, sizeof(line), file)) {
                    fputs(line, tempFile);
                }
                else {
                    break;
                }
            }
            fputs(newText, tempFile);
            fputc('\n', tempFile);
        }
    }

    fclose(file);
    rewind(tempFile);
    file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("�޷����´��ļ�\n");
        fclose(tempFile);
        return;
    }

    while (fgets(line, sizeof(line), tempFile))
    {
        fputs(line, file);
    }

    fclose(tempFile);
    fclose(file);
    printf("�³�����Ϣ�ѱ��档\n");
    linesToInsert = linesToInsert + 11;
    num++;

}

void circulateInsertCourtData()
{
    
  


insertCourtData("site_ex.txt");

    
        
}


