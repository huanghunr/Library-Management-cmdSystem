#include "Library.h"
#include "base64.h"
#include "RC4.h"

//登录页面实现

int login(usr *user);
int initlogin(usr *user);
int initlogin(usr *user);    //主界面
int login(usr *user);   //登录
int checkuser(char* username,char* password,usr *user); //检查用户名密码
int user_register();    //注册


int initlogin(usr *user){
    int stat =0;
    int choice;
    char* hello = (char*)malloc(10);
    if(hello == NULL){
        printf("内存分配失败\n");
        return 0;
    }

    sayhello();
    printf("欢迎使用图书管理系统。\n");
    while(1){
        printf(line_str); //分割线
        printf("1.登录\n");
        printf("2.注册\n");
        printf("3.退出\n");
        printf(line_str);
        printf("请选择：");
        int flag = scanf("%d",&choice);
        if(flag == 0){
            printf("输入错误，请重新输入\n");
            while(getchar()!='\n'); //清空缓冲区，防止输入错误
            continue;
        }
        switch(choice){
            case 1:
                printf("<----登录---->\n");
                while(1){
                    int flag = login(user); //登录
                    if(flag == 1) return 1;   //登录成功
                    else if (flag == 3) break;  //返回主界面
                    else printf("用户名或密码错误，请重新输入\n");
                }
                break;
            case 2:
                printf("<----注册---->\n");
                while (1)
                {
                    int flag = user_register(); //注册
                    if(flag == 1 || flag == 3) break;   //注册成功或返回主界面
                    else printf("注册失败，请重新输入\n"); //注册失败，重新输入

                }
                break;
            case 3:
                exit(0);    //退出
                break;
            default:
                printf("输入错误，请重新输入"); //输入错误，重新输入
                break;
        }
    
    }
}


int login(usr *user){
    printf("**输入last返回上一级**\n");
    printf("请输入用户名>>");
    scanf("%s",user->username);
    if(strcmp(user->username,"last") == 0) return 3; //判断是否返回上一级

    printf("请输入密码>>");
    char password[26];
    scanf("%s",password);
    if(strcmp(user->password,"last") == 0) return 3;

    if(checkuser(user->username,password,user)){    //判断用户名和密码是否正确
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
        printf("内存分配失败\n");
        return 0;
    }

    printf("**输入last返回上一级**\n");

    //输入用户名
    while(1){
        printf("请输入用户名(不多于16位)>>");
        scanf("%s",new_user->username);
        if(strcmp(new_user->username,"last") == 0) return 3;
        if(strlen(new_user->username) > 16 || strlen(new_user->username) < 1){
            printf("用户名不符，请重新输入\n");
            continue;

        }
        //判断用户名是否已存在
        FILE *file = fopen("userdata.txt", "r");
        if (file == NULL) {
            printf("无法打开文件！\n");
            return 0;
        }
        char line[0x100];
        while (fgets(line, sizeof(line), file)) {
            
            char *token = strtok(line, ",");
            if(strcmp(token,new_user->username)==0){
                printf("用户名已存在，请重新输入\n");
                fclose(file);
                return 0;
            }
    
        }
        fclose(file);
        break;
    }

    //输入密码
    while(1){
        printf("请输入密码(最少8位，且不多于16位,支持字母数字和符号)>>");
        scanf("%s",new_user->password);
        if(strcmp(new_user->password,"last") == 0) return 3;
        if(strlen(new_user->password) > 16 || strlen(new_user->password) < 8){
            printf("密码不符，请重新输入\n");
            continue;
        }

        printf("请再次输入密码>>");
        char password[26];
        scanf("%s",password);
        if(strlen(password) > 16 || strlen(password) < 8){
            printf("密码不符，请重新输入\n");
            continue;
        }
        if(strcmp(new_user->password,password) != 0){
            printf("两次密码不一致，请重新输入\n");
            continue;
        }
        break;
    }

    unsigned char key[] = "mylibrary";
    enc(key,(unsigned char*)new_user->password);    //rc4加密密码
    base64_encode(new_user->password, new_user->password,strlen(new_user->password));   //base64编码
    
    FILE *file = fopen("userdata.txt", "a");
    if (file == NULL) {
        printf("无法打开文件！\n");
        return 0;
    }

    // 写入新用户数据到文件
    fprintf(file, "%s,%s,%d,%d", new_user->username, new_user->password, 0, 0);
    fclose(file);
    printf("注册成功！\n");
    system("cls");
    return 1;
    
}

int checkuser(char* username,char* password,usr *user){

    char line[0x100];
    FILE *file = fopen("userdata.txt", "r"); 
    if (file == NULL) {
        printf("无法打开文件！\n");
        return -1;
    }

    int flag =0; // 标记是否找到用户名
    int i = 3;
    while (fgets(line, sizeof(line), file)) {
        
        line[strcspn(line, "\n")] = 0;  //去掉换行符

        char *token = strtok(line, ",");    //strtok用逗号分隔
        int field_index = 0;
        if(strcmp(token,username)==0){
            flag = 1;
            printf("找到用户名\n");
            while (i--) {
                if(token == NULL){
                    printf("用户数据错误!\n");
                    return 0;
                }
                if (field_index == 0) {
                    strcpy(user->username, token); //获取用户名
                } else if (field_index == 1) {
                    strcpy(user->password, token);  //获取密码
                } else if (field_index == 2) {
                    user->isadmin = atoi(token);    //获取管理员权限
                }
                token = strtok(NULL, ",");
                field_index++;
            }
            fclose(file);
        }

    }
    if(flag == 0) return 0;

    unsigned char key[] = "mylibrary";  //加密密码
    enc(key,(unsigned char*)password);
    base64_encode(password, password,strlen(password));
       
    for(int i=0;i<strlen(password);i++){
        printf("%02x,",password[i]);
    }
    printf("password:%s\n",password);
        
    if (strcmp(user->password, password) == 0) return 1; //判断密码是否正确
    else return 0;
}