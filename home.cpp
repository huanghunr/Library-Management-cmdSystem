#include "home.h"

#include "useroperations.h"

int home(usr *user){
    printf(home_str);
    sayhello();
    //printf(",%s,",user->username);
    printf("欢迎来到图书馆管理系统\n");
    printf("1.借书\n");
    printf("2.还书\n");
    printf("3.查询图书\n");
    printf("4.查询借阅记录\n");
    printf("5.修改密码\n");
    printf("6.退出\n");
    printf("7.清屏\n");
    printf(line_str);
    printf("请选择操作>>");
    int choice;
    int flag = scanf("%d",&choice);
    if(flag == 0){
        printf(">输入错误，请重新输入\n");
        while(getchar()!='\n');
        return 1; 
    }
    switch(choice){
        // case 1:
        //     borrow_book(user);
        //     break;
        // case 2:
        //     return_book(user);
        //     break;
        case 3:
            searchbooks();
            break;
        // case 4:
        //     search_borrow(user);
        //     break;
        // case 5:
        //     change_password(user);
        //     break;
        case 6:
            exit(0);
            break;
        case 7:
            system("cls");
            return 1;
        default:
            printf(">输入错误，请重新输入\n");
        
    }

    return 0;

}