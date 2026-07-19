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

    FILE * file;
    file = fopen("logo.txt","r");

    time_t rawtime;
    struct tm * timeinfo;
    time( &rawtime );
    timeinfo = localtime( &rawtime );

    printf("+-------------------------------------------------------------+\n");
    printf("|                       %02d:%02d %02d/%02d/%d                      |\n", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_mday, timeinfo->tm_mon+1, timeinfo->tm_year+1900);

    char menu_line[255];

    while(1){

        if (feof(file)){
            break;
        }

        fgets(menu_line,255,file);

        printf("%s",menu_line);
    }
    fclose(file);
}

void display_creating_course(){
    clear_terminal();
    printf("--------------------\n");
    printf("Creating Course\n");
    printf("--------------------\n");
}

void display_course_status_all(){
    clear_terminal();
    printf("+------------------+\n");
    printf("Listing Course Status\n");
    printf("+------------------+\n");
}

void display_course_status(int id){
    clear_terminal();
    printf("------------------------------------\n");
    printf("Listing Course Status with ID : %d\n",id);
    printf("------------------------------------\n");
}

void display_listing_all_courses(){
    clear_terminal();
    printf("--------------------\n");
    printf("Listing Courses\n");
    printf("--------------------\n");
}

void display_course(int id){
    clear_terminal();
    printf("--------------------\n");
    printf("Printing course with ID : %d\n",id);
    printf("--------------------\n");
}

void display_options(int id){
    clear_terminal();
    printf("-----------------------------------\n");
    printf("Updating Course with ID : %d\n",id);
    printf("-----------------------------------\n");
    printf("+---------------------+\n");
    printf("Name of University\t- 0\n");
    printf("Year of Course\t\t- 1\n");
    printf("Name of Course\t\t- 2\n");
    printf("Name of Lecturer\t- 3\n");
    printf("Status of Course\t- 4\n");
    printf("+---------------------+\n");
}

void display_delete(int id){
    clear_terminal();
    printf("--------------------\n");
    printf("Deleting Course with ID : %d\n",id);
    printf("--------------------\n");
}