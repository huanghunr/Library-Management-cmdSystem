#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <string.h>

#define _CRT_SECURE_NO_WARNINGS
#define is_admin 1
#define line_str "\n<-----------------------------*****----------------------------------->\n"
#define home_str "\n<------------------------<----Ö÷½çÃæ---->------------------------------>\n"
#define outline "\n+--------------------------------------------------------------------+\n"

typedef struct user_data{
    char username[26];
    char password[26];
    bool isadmin;
    int books;
    char borrowedbook[20][20];
    char bookbucket[20][20];

} usr;


typedef struct book_data{
    uint32_t bookid;
    char title[40];
    char author[40];
    int bookstatus;
    char borrower[20];
    int borrowtime;
    char last_borrower[20];
    int last_borrowtime;
    int last_returntime;
    char type[20];
    
}book;

void sayhello();
int last(char* input);