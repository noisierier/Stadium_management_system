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
    printf("请选择场馆:\n"); 
    printf("1. 场馆1\n");
    printf("2. 场馆2\n"); 
    printf("3. 场馆3\n"); 
    while (getchar() != '\n'); // 清空输入缓冲区
    scanf("%d", &venueChoice); 
    if (venueChoice < 1 || venueChoice > 3) { 
        printf("无效的选择\n"); 
        return; 
    } 
    snprintf(searchString, sizeof(searchString), "%s", venueCodes[venueChoice - 1]); 
    char newText[1000] = ""; 
    FILE* file = fopen(filename, "r+");



    if (file == NULL) {
        printf("无法打开文件\n");
        return;
    }

    char line[1000];
    char inputLine[100];

    snprintf(newText, sizeof(newText), "%d", num);
    strcat(newText, "\n");


    while (1)
    {
        int isValidInput = 1;
        printf("请输入新场地的租金/h:\n");
        // 接收用户输入的文本，以空行结束
        while (getchar() != '\n'); // 清空输入缓冲区
        fgets(inputLine, sizeof(inputLine), stdin);

        // 检查输入是否包含非数字字符

        for (size_t i = 0; i < strlen(inputLine); i++)
        {
            if (!isdigit(inputLine[i]) && inputLine[i] != '\n')
            {
                isValidInput = 0; // 输入包含非数字字符
                break;
            }
        }

        if (!isValidInput) 
        {
            printf("无效输入，请输入数字。\n");
        }
        else {
            printf("租金成功输入。\n\n");
            strcat(newText, inputLine);
            break;
        }
    }
    printf("请输入新场的编号:\n");
    fgets(inputLine, sizeof(inputLine), stdin);

    size_t inputLineLength = strlen(inputLine);
    if (inputLineLength > 0 && inputLine[inputLineLength - 1] == '\n') {
        inputLine[inputLineLength - 1] = '\0';
    }

    strcat(newText, inputLine);
    printf("场地编号成功输入。\n\n");

    strcat(newText, "\n0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n");


    while (1) {
        int isValidInput = 1; // 在每次循环开始时重置为1

        printf("请输入新场最大容纳人数:\n");
        // 接收用户输入的文本，以空行结束
        fgets(inputLine, sizeof(inputLine), stdin);

        // 检查输入是否包含非数字字符
        for (size_t i = 0; i < strlen(inputLine); i++)
        {
            if (!isdigit(inputLine[i]) && inputLine[i] != '\n') 
            {
                isValidInput = 0; // 输入包含非数字字符
                break;
            }
        }

        if (!isValidInput) 
        {
            printf("无效输入，请输入数字。\n");
        }
        else {
            // 如果输入以换行符结尾，将其替换为 null 终止符
            size_t inputLineLength = strlen(inputLine);
            if (inputLineLength > 0 && inputLine[inputLineLength - 1] == '\n')
            {
                inputLine[inputLineLength - 1] = '\0';
            }

            // 将输入的字符串追加到 newText 中
            strcat(newText, inputLine);
            printf("场地最大人数成功输入。\n\n");
            break;
        }
    }

    FILE* tempFile = tmpfile();
    if (tempFile == NULL) 
    {
        printf("无法创建临时文件\n");
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
        printf("无法重新打开文件\n");
        fclose(tempFile);
        return;
    }

    while (fgets(line, sizeof(line), tempFile))
    {
        fputs(line, file);
    }

    fclose(tempFile);
    fclose(file);
    printf("新场馆信息已保存。\n");
    linesToInsert = linesToInsert + 11;
    num++;

}

void circulateInsertCourtData()
{
    
  


insertCourtData("site_ex.txt");

    
        
}


