#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void clear_terminal(){
    #ifdef _WIN32
        system("cls");
    #elif __linux__
        system("clear");
    #endif
}

void display_menu(){
    clear_terminal();

    FILE * arch;
    arch = fopen("logo.txt","r");

    time_t rawtime;
    struct tm * timeinfo;
    time( &rawtime );
    timeinfo = localtime( &rawtime );

    printf("+-------------------------------------------------------------+\n");
    printf("|                       %02d:%02d %02d/%02d/%d                      |\n", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_mday, timeinfo->tm_mon+1, timeinfo->tm_year+1900);

    char menu_line[255];

    while(1){

        if (feof(arch)){
            break;
        }

        fgets(menu_line,255,arch);

        printf("%s",menu_line);
    }
    fclose(arch);
}

void display_creating_course(){
    clear_terminal;
    printf("--------------------\n");
    printf('Creating Course\n');
    printf("--------------------\n");
}

void display_listiing_all_courses(){
    clear_terminal;
    printf("--------------------\n");
    printf("Listing Courses\n");
    printf("--------------------\n");
}

void display_course(int id){
    clear_terminal;
    printf("--------------------\n");
    printf("Printing course with ID : %d\n",id);
    printf("--------------------\n");
}

void display_update(int id){
    clear_terminal;
    printf("-------------------\n");
    printf("Updating Course with ID : %d\n",id);
    printf("-------------------\n");
}