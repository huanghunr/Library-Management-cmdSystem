#include "Library.h"
#include "base64.h"
#include "RC4.h"

//��¼ҳ��ʵ��

int login(usr *user);
int initlogin(usr *user);
int initlogin(usr *user);    //������
int login(usr *user);   //��¼
int checkuser(char* username,char* password,usr *user); //����û�������
int user_register();    //ע��


int initlogin(usr *user){
    int stat =0;
    int choice;
    char* hello = (char*)malloc(10);
    if(hello == NULL){
        printf("�ڴ����ʧ��\n");
        return 0;
    }

    sayhello();
    printf("��ӭʹ��ͼ�����ϵͳ��\n");
    while(1){
        printf(line_str); //�ָ���
        printf("1.��¼\n");
        printf("2.ע��\n");
        printf("3.�˳�\n");
        printf(line_str);
        printf("��ѡ��");
        int flag = scanf("%d",&choice);
        if(flag == 0){
            printf("�����������������\n");
            while(getchar()!='\n'); //��ջ���������ֹ�������
            continue;
        }
        switch(choice){
            case 1:
                printf("<----��¼---->\n");
                while(1){
                    int flag = login(user); //��¼
                    if(flag == 1) return 1;   //��¼�ɹ�
                    else if (flag == 3) break;  //����������
                    else printf("�û����������������������\n");
                }
                break;
            case 2:
                printf("<----ע��---->\n");
                while (1)
                {
                    int flag = user_register(); //ע��
                    if(flag == 1 || flag == 3) break;   //ע��ɹ��򷵻�������
                    else printf("ע��ʧ�ܣ�����������\n"); //ע��ʧ�ܣ���������

                }
                break;
            case 3:
                exit(0);    //�˳�
                break;
            default:
                printf("�����������������"); //���������������
                break;
        }
    
    }
}


int login(usr *user){
    printf("**����last������һ��**\n");
    printf("�������û���>>");
    scanf("%s",user->username);
    if(strcmp(user->username,"last") == 0) return 3; //�ж��Ƿ񷵻���һ��

    printf("����������>>");
    char password[26];
    scanf("%s",password);
    if(strcmp(user->password,"last") == 0) return 3;

    if(checkuser(user->username,password,user)){    //�ж��û����������Ƿ���ȷ
        system("cls");
        sayhello();
        printf("%s!\n",user->username);
        return 1;
    }
    return 0;
}

int user_register(){
    usr *new_user = (usr*)malloc(sizeof(usr));
    if(new_user == NULL){
        printf("�ڴ����ʧ��\n");
        return 0;
    }

    printf("**����last������һ��**\n");

    //�����û���
    while(1){
        printf("�������û���(������16λ)>>");
        scanf("%s",new_user->username);
        if(strcmp(new_user->username,"last") == 0) return 3;
        if(strlen(new_user->username) > 16 || strlen(new_user->username) < 1){
            printf("�û�������������������\n");
            continue;

        }
        //�ж��û����Ƿ��Ѵ���
        FILE *file = fopen("userdata.txt", "r");
        if (file == NULL) {
            printf("�޷����ļ���\n");
            return 0;
        }
        char line[0x100];
        while (fgets(line, sizeof(line), file)) {
            
            char *token = strtok(line, ",");
            if(strcmp(token,new_user->username)==0){
                printf("�û����Ѵ��ڣ�����������\n");
                fclose(file);
                return 0;
            }
    
        }
        fclose(file);
        break;
    }

    //��������
    while(1){
        printf("����������(����8λ���Ҳ�����16λ,֧����ĸ���ֺͷ���)>>");
        scanf("%s",new_user->password);
        if(strcmp(new_user->password,"last") == 0) return 3;
        if(strlen(new_user->password) > 16 || strlen(new_user->password) < 8){
            printf("���벻��������������\n");
            continue;
        }

        printf("���ٴ���������>>");
        char password[26];
        scanf("%s",password);
        if(strlen(password) > 16 || strlen(password) < 8){
            printf("���벻��������������\n");
            continue;
        }
        if(strcmp(new_user->password,password) != 0){
            printf("�������벻һ�£�����������\n");
            continue;
        }
        break;
    }

    unsigned char key[] = "mylibrary";
    enc(key,(unsigned char*)new_user->password);    //rc4��������
    base64_encode(new_user->password, new_user->password,strlen(new_user->password));   //base64����
    
    FILE *file = fopen("userdata.txt", "a");
    if (file == NULL) {
        printf("�޷����ļ���\n");
        return 0;
    }

    // д�����û����ݵ��ļ�
    fprintf(file, "%s,%s,%d,%d", new_user->username, new_user->password, 0, 0);
    fclose(file);
    printf("ע��ɹ���\n");
    system("cls");
    return 1;
    
}

int checkuser(char* username,char* password,usr *user){

    char line[0x100];
    FILE *file = fopen("userdata.txt", "r"); 
    if (file == NULL) {
        printf("�޷����ļ���\n");
        return -1;
    }

    int flag =0; // ����Ƿ��ҵ��û���
    int i = 3;
    while (fgets(line, sizeof(line), file)) {
        
        line[strcspn(line, "\n")] = 0;  //ȥ�����з�

        char *token = strtok(line, ",");    //strtok�ö��ŷָ�
        int field_index = 0;
        if(strcmp(token,username)==0){
            flag = 1;
            printf("�ҵ��û���\n");
            while (i--) {
                if(token == NULL){
                    printf("�û����ݴ���!\n");
                    return 0;
                }
                if (field_index == 0) {
                    strcpy(user->username, token); //��ȡ�û���
                } else if (field_index == 1) {
                    strcpy(user->password, token);  //��ȡ����
                } else if (field_index == 2) {
                    user->isadmin = atoi(token);    //��ȡ����ԱȨ��
                }
                token = strtok(NULL, ",");
                field_index++;
            }
            fclose(file);
        }

    }
    if(flag == 0) return 0;

    unsigned char key[] = "mylibrary";  //��������
    enc(key,(unsigned char*)password);
    base64_encode(password, password,strlen(password));
       
    for(int i=0;i<strlen(password);i++){
        printf("%02x,",password[i]);
    }
    printf("password:%s\n",password);
        
    if (strcmp(user->password, password) == 0) return 1; //�ж������Ƿ���ȷ
    else return 0;
}