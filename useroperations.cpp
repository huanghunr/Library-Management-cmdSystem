#include "Library.h"
#include "RC4.h"
int initbookdata();
int initusersdata();
void closeusersdata();
void closebookdata();
int lodadbookdata();
int listbooks();
int listbooks_byauther();
int listbooks_bytype();
int listbooks_byname();
int searchbooks();
int arrangement();
int sort_byauthor();
int sort_bytitle();
int listavaliable(book *data);
int defualtlistbook(book *data);
int reverse();

book books[100];
book temp[100]; //��ʱ����
int bookcount = 0;

int initbookdata(){
    FILE* fp = fopen("bookdataa.txt", "rb");
    FILE* fp1 = fopen("bookdata.txt", "wb");
    if (fp == NULL) {
        perror("�� bookdataa.txt ʧ��");
        return 0;
    }
    if (fp1 == NULL) {
        perror("�� bookdata.txt ʧ��");
        return 0;
    }
    fseek(fp, 0, SEEK_END);
    long file_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    unsigned char *file_content = (unsigned char *)malloc(file_size);
    if (file_content == NULL) {
        perror("�ļ��򿪴���");
        fclose(fp);
        return 0;
    }
    fread(file_content, 1, file_size, fp); 

    fclose(fp);
    unsigned char key[] ="mybookdata";
    enc(key, file_content);
    printf("success\n");
    printf("file_size: %zu\n", file_size);
    printf("file_content: %p\n", file_content);

    size_t bytes_written = fwrite(file_content, 1, file_size, fp1);
    if (bytes_written != file_size) {
    perror("�ļ�д��ʧ��");
    fclose(fp1);
    return 0;
}
    fclose(fp1);
    return 1;
} 


int initusersdata(){
    FILE* fp = fopen("userdataa.txt", "rb");
    FILE* fp1 = fopen("userdata.txt", "wb");
    if (fp == NULL) {
        perror("�� bookdataa.txt ʧ��");
        return 0;
    }
    if (fp1 == NULL) {
        perror("�� bookdata.txt ʧ��");
        return 0;
    }

    fseek(fp, 0, SEEK_END);
    long file_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    unsigned char *file_content = (unsigned char *)malloc(file_size);
    if (file_content == NULL) {
        perror("�ļ��򿪴���");
        fclose(fp);
        return 0;
    }
    fread(file_content, 1, file_size, fp);

    fclose(fp);
    unsigned char key[] ="mybookdata";
    enc(key, file_content);
    size_t bytes_written = fwrite(file_content, 1, file_size, fp1);
    if (bytes_written != file_size) {
    perror("�ļ�д��ʧ��");
    fclose(fp1);
    return 0;
}
    fclose(fp1);
    return 1;
} 

void closeusersdata(){
    FILE* fp = fopen("userdata.txt", "w");
    if (fp == NULL) {
        perror("�� userdataa.txt ʧ��");

    }
    fclose(fp);

}

void closebookdata(){
    FILE* fp = fopen("bookdata.txt", "w");
    if (fp == NULL) {
        perror("�� bookdataa.txt ʧ��");

    }
    fclose(fp);

}

int searchbooks(){
    while(1){
    printf("\n<------------------------<---����ͼ��--->------------------------------->\n");
    printf("1.����������\n");
    printf("2.�����߲���\n");
    printf("3.���������\n");
    printf("4.ȫ���г�\n");
    printf("5.����\n");
    printf(line_str);
    printf("��������ҷ�ʽ>>");
    int choice;
    int flag = scanf("%d",&choice);
    if(flag == 0){
        printf(">�����������������\n");
        while(getchar()!='\n'); 
        continue;
    }
    switch (choice) {
        case 1:
            while(1){
                if(listbooks_byname() == 3) return 3;
            }
            break;
        case 2:
        while(1){
            if(listbooks_byauther() == 3) return 3;
        }
            break;
        case 3:
            while(1){
                if(listbooks_bytype() == 3) return 3;
            }
            break;
        case 4:
            if(listbooks() == 3) return 3;
            break;
        case 5:
            return 3;
        default:
            printf(">�����������������\n");
            break;

    }
    }
    return 0;
}

int lodadbookdata(){

    FILE *fp = fopen("bookdata.txt", "r");
    if (fp == NULL) {
        printf(">���ļ�ʧ��\n");
        return -1;
    }

    int i = 0;
    char line[0x100];
    while (fgets(line, sizeof(line), fp)) {
        
        line[strcspn(line, "\n")] = 0;
        char *token = strtok(line, ",");
        int j =0;
        int index=0;
        while( index < 10 && token != NULL) {
        if (index == 0) books[i].bookid = atoi(token);
        else if (index == 1) strcpy(books[i].title, token);
        else if (index == 2) strcpy(books[i].author, token);
        else if (index == 3) books[i].bookstatus=atoi(token);
        else if (index == 4) strcpy(books[i].borrower, token);
        else if (index == 5) books[i].borrowtime=atoi(token);
        else if (index == 6) strcpy(books[i].last_borrower, token);
        else if (index == 7) books[i].last_borrowtime = atoi(token);
        else if (index == 8) books[i].last_returntime = atoi(token);
        else if (index == 9) strcpy(books[i].type, token);
        token = strtok(NULL, ",");
        index++;
        }
        i++;
    
    }
    bookcount = i;
    fclose(fp);

    return 0;
}


int listbooks(){
    for(int i = 0; i < bookcount; i++){
        temp[i] = books[i];
    }
    defualtlistbook(books);
    while(1){

    int flag = arrangement();
    if( flag== 9) listavaliable(temp);
    else if (flag == 0) {
        printf("�������");
        return 0;
    }
    else if(flag == 10) return 0;
    
    else defualtlistbook(temp);
    }
    return 0;
}

int listbooks_byname(){

    int flag = 0;
    char name[20];
    printf("����������(����last����)>>");
    scanf("%s", &name);
    if(strcmp(name,"last")==0) return 3;  //������һ��

    for (int i = 0; i < bookcount; i++){
        if (strcmp(books[i].title, name) == 0){
            flag++;
            if(flag ==1) printf(outline);
            printf("��ţ�%d   ������%s   ���ߣ�%s   ����:%s\n", books[i].bookid, books[i].title, books[i].author,books[i].type);
        }
    }
    if (flag == 0) {
        printf(">û���ҵ����鼮\n");}
    printf(outline);
    return 0;

}

int listbooks_byauther(){

    int flag = 0;
    char name[20];
    printf("������������(����last����)>>");
    scanf("%s", &name);
    if(strcmp(name,"last")==0) return 3;
    for (int i = 0; i < bookcount; i++){
        if (strcmp(books[i].author, name) == 0){
            flag++;
            if(flag ==1) printf(outline);
            printf("��ţ�%d   ������%s   ���ߣ�%s   ����:%s   ", books[i].bookid, books[i].title, books[i].author,books[i].type);
            if(books[i].bookstatus==0) printf("״̬�����ɽ�\n");
            else printf("״̬���ɽ�\n");
        }
    }
    if (flag == 0) {
        printf(">û���ҵ����鼮\n");
        printf(outline);
        return 0;
    }
    else{
        printf(outline);
        while(1){
            int flag = arrangement();
            if(flag == 9) {
                for (int i = 0; i < bookcount; i++){
                    if (strcmp(temp[i].author, name) == 0 && temp[i].bookstatus == 1){
                        flag++;
                        if(flag ==1) printf(outline);
                        printf("��ţ�%d   ������%s   ���ߣ�%s   ����:%s   ", temp[i].bookid, temp[i].title, temp[i].author,temp[i].type);
                        if(books[i].bookstatus==0) printf("״̬�����ɽ�\n");
                        else printf("״̬���ɽ�\n");
                }   }
            }
            else if(flag == 0) {
                printf("�������");
                return 0;
            }
            else if(flag == 10) return 3;
            else {
                for (int i = 0; i < bookcount; i++){
                    if (strcmp(temp[i].author, name) == 0){
                        flag++;
                        if(flag ==1) printf(outline);
                        printf("��ţ�%d   ������%s   ���ߣ�%s   ����:%s   ", temp[i].bookid, temp[i].title, temp[i].author,temp[i].type);
                        if(books[i].bookstatus==0) printf("״̬�����ɽ�\n");
                        else printf("״̬���ɽ�\n");
                }   }
            }
        }
    }
}


int listbooks_bytype(){
    int flag = 0;
    char name[20];
    printf("�����������(����last����)>>");
    scanf("%s", &name);
    if(strcmp(name,"last")==0) return 3;

    for (int i = 0; i < bookcount; i++){
        if (strcmp(books[i].type, name) == 0){
            flag++;
            if(flag==1) printf(outline);
            printf("��ţ�%d   ������%s   ���ߣ�%s   ����:%s   ", books[i].bookid, books[i].title, books[i].author,books[i].type);
            if(books[i].bookstatus==0) printf("״̬�����ɽ�\n");
        }
    }

    if (flag == 0) {
        printf(">û���ҵ������鼮\n");
        printf(outline);
        return 0;
    }
    else{
        printf(outline);
        while(1){
            int flag = arrangement();
            if(flag == 9) {
                for (int i = 0; i < bookcount; i++){
                    if (strcmp(temp[i].type, name) == 0 && temp[i].bookstatus == 1){
                        flag++;
                        if(flag ==1) printf(outline);
                        printf("��ţ�%d   ������%s   ���ߣ�%s   ����:%s   ", temp[i].bookid, temp[i].title, temp[i].author,temp[i].type);
                        if(books[i].bookstatus==0) printf("״̬�����ɽ�\n");
                        else printf("״̬���ɽ�\n");
                }   }
            }
            else if(flag == 0) {
                printf("�������");
                return 0;
            }
            else if(flag == 10) return 3;
            else {
                for (int i = 0; i < bookcount; i++){
                    if (strcmp(temp[i].type, name) == 0){
                        flag++;
                        if(flag ==1) printf(outline);
                        printf("��ţ�%d   ������%s   ���ߣ�%s   ����:%s   ", temp[i].bookid, temp[i].title, temp[i].author,temp[i].type);
                        if(books[i].bookstatus==0) printf("״̬�����ɽ�\n");
                        else printf("״̬���ɽ�\n");
                }   }
            }
        }}
    return 0;
}

int sort_byauthor(){
    book tempvalue;

    for (int i = 0; i < bookcount; i++){
        for (int j = i + 1; j < bookcount; j++){
            if (strcmp(temp[i].author, temp[j].author) > 0){
                //��С�����ţ�ֱ�ӱ��浽��ʱ�����У�����ԭ�������
                tempvalue = temp[i];
                temp[i] = temp[j];
                temp[j] = tempvalue;
            }
        }
    }
    return 0;
}
int sort_bytitle(){
    book tempvalue;
    for(int i = 0; i < bookcount; i++){
        temp[i] = books[i];
    }
    for (int i = 0; i < bookcount; i++){
        for (int j = i + 1; j < bookcount; j++){
            if (strcmp(temp[i].title, temp[j].title) > 0){
                //��С�����ţ�ֱ�ӱ��浽��ʱ�����У�����ԭ�������
                tempvalue = temp[i];
                temp[i] = temp[j];
                temp[j] = tempvalue;
            }
        }
    }
    return 0;
}

int sort_byborrowtime(){
    book tempvalue;
    for(int i = 0; i < bookcount; i++){
        temp[i] = books[i];
    }
    for (int i = 0; i < bookcount; i++){
        for (int j = i + 1; j < bookcount; j++){
            if (temp[i].borrowtime > temp[j].borrowtime){
                //��С�����ţ�ֱ�ӱ��浽��ʱ�����У�����ԭ�������
                tempvalue = temp[i];
                temp[i] = temp[j];
                temp[j] = tempvalue;
            }
        }
    }
    return 0;
}

int arrangement(){

    printf("--------------------------\n");
    printf("����ʽ(Ĭ�ϰ��������):\n");
    printf("1.����������\n2.����������\n3.���������\n8.����\n9.���β��ɽ����\n10.����\n");
    printf("--------------------------\n");
    printf("��ѡ������ʽ>>");
    int choice;
    scanf("%d", &choice);
    switch (choice){
        case 1:
            if(!sort_byauthor()) return 1;
            return 0;
        case 2:
            if(!sort_bytitle()) return 2;
            return 0;
        case 8:
            if(!reverse()) return 8;
            return 0;
        case 9:
            return 9;
        case 10:
            return 10;
        default:
        printf("�����������������\n");
        return 0;
        }
}

int reverse(){
    book temp2[100];
    for(int i = 0; i < bookcount; i++){
        temp2[i] = temp[bookcount-i-1];
    }
    for (int i = 0; i < bookcount; i++)
    {
        temp[i] = temp2[i];
    }
    return 0;
}

int defualtlistbook(book *data){
    printf(outline);
    for(int i = 0; i < bookcount; i++){
        printf("��ţ�%d   ������%s   ���ߣ�%s   ����:%s   ", data[i].bookid, data[i].title, data[i].author,data[i].type);
        if(data[i].bookstatus==0) printf("״̬�����ɽ�\n");
        else printf("״̬���ɽ�\n");
    }
    printf(outline);
    return 0;
}

int listavaliable(book *data){
    printf(outline);
    for(int i = 0; i < bookcount; i++){
        if(data[i].bookstatus==1){
            printf("��ţ�%d   ������%s   ���ߣ�%s   ����:%s   ", data[i].bookid, data[i].title, data[i].author,data[i].type);
            printf("״̬���ɽ�\n");

        }
    }
    return 0;
}