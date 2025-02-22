#include "Library.h"
#include "Login.h"
#include "useroperations.h"
#include "home.h"

int main(){
    atexit(closeusersdata); //退出程序时关闭用户信息库
    atexit(closebookdata); //退出程序时关闭图书信息库

    if(initbookdata() !=1)exit(0); //初始化图书信息库
    if(initusersdata() !=1)exit(0); //初始化用户信息库
    usr *user = (usr*)malloc(sizeof(usr));//记录用户信息

    initlogin(user);

    lodadbookdata();
    while(1){
        home(user);
    }

    return 0;
}


