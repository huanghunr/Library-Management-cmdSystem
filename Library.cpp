#include "Library.h"

void sayhello(){
    time_t now_time = time(NULL);
    struct tm *local_time = localtime(&now_time);

    int hour = local_time->tm_hour;

    if (hour >= 5 && hour < 12) {
        printf("�����,");
    } else if (hour >= 12 && hour < 18) {
        printf("�����,");
    } else {
        printf("���Ϻ�,");
    }
}

int last(char* input){
    if (strcmp(input, "_last") == 0) {
        printf("������һ��\n");
        return 3;
    }
    return 0;
}