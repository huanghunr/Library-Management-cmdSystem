#include "home.h"

#include "useroperations.h"

int home(usr *user){
    printf(home_str);
    sayhello();
    //printf(",%s,",user->username);
    printf("��ӭ����ͼ��ݹ���ϵͳ\n");
    printf("1.����\n");
    printf("2.����\n");
    printf("3.��ѯͼ��\n");
    printf("4.��ѯ���ļ�¼\n");
    printf("5.�޸�����\n");
    printf("6.�˳�\n");
    printf("7.����\n");
    printf(line_str);
    printf("��ѡ�����>>");
    int choice;
    int flag = scanf("%d",&choice);
    if(flag == 0){
        printf(">�����������������\n");
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
            printf(">�����������������\n");
        
    }

    return 0;

}