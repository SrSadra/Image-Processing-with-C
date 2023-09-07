#include <stdio.h>


#define strSize 1000

int input;

char* strInput(){
    fflush(stdin);
    char* inp = (char*) malloc(10000);
    scanf("%[^\n]%*c", inp);
    return inp;
}

void welcomeMenu(){
    system("clear");
    printf("Welcome to c photoshop\n Press any number to continue");
    scanf("%d", &input);
    system("clear");
}


int endMenu(){
    printf("Do you want to Edit another image?\n1-Yes\n2-No");
    scanf("%d", &input);
    if (input == 1){
        return 1;
    }
    printf("Bye!");
    return 0;
}

