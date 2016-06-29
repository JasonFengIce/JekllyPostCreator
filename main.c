#include <zconf.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <memory.h>


int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("please enter file name!\n");
        return 0;
    }

    char *file_name = argv[1];

    char buffer[1024];
    getcwd(buffer, 1024);


    time_t rawtime;
    struct tm *timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);

    int year = 1900 + timeinfo->tm_year;
    int month = timeinfo->tm_mon + 1;
    int day = timeinfo->tm_mday;


    char year_s[5];
    char month_s[3];
    char day_s[3];

    sprintf(year_s, "%d", year);
    sprintf(month_s, "%d", month);
    sprintf(day_s, "%d", day);

    char *date = malloc(strlen(year_s) + strlen(month_s) + strlen(year_s) + 2 + 1);

    strcpy(date, year_s);
    strcat(date, "-");
    strcat(date, month_s);
    strcat(date, "-");
    strcat(date, day_s);


    char *title = malloc(strlen(date) + strlen(file_name) + strlen("-") + strlen(".markdown") + 1);
    strcpy(title, date);
    strcat(title, "-");
    strcat(title, file_name);
    strcat(title, ".markdown");


    printf("title %s\n", title);

//    FILE *fopen(char *filename,char *type) 打开一个文件filename,打开方式为type，
//    并返回这个文件指针，type可为以下字符串加上后缀
//    ┌──┬────┬───────┬────────┐
//    │type│读写性  │文本/2进制文件│建新/打开旧文件 │
//    ├──┼────┼───────┼────────┤
//    │r   │读      │文本          │打开旧的文件    │
//    │w   │写      │文本          │建新文件        │
//    │a   │添加    │文本          │有就打开无则建新│
//    │r+  │读/写   │不限制        │打开            │
//    │w+  │读/写   │不限制        │建新文件        │
//    │a+  │读/添加 │不限制        │有就打开无则建新│
//    └──┴────┴───────┴────────┘


    FILE *file_p = fopen(title, "w");
    if (file_p != NULL) {
        fprintf(file_p, "---\n");
        fprintf(file_p, "layout: post\n");
        fprintf(file_p, "title:  %s\n", file_name);
        fprintf(file_p, "date:   %s\n", date);
        fprintf(file_p, "categories: jekyll update\n");
        fprintf(file_p, "---\n");
        fclose(file_p);
    }

    free(date);
    free(title);

    return 0;
}