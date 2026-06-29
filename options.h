#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"db_functions.h"
#include"menu.h"

#define MAX_CHAR 50

struct course{
    char name_university[MAX_CHAR];
    int year;
    char name_course[MAX_CHAR];
    char name_lecturer[MAX_CHAR];

};

typedef struct course courses;

int create(){
    display_creating_course();
    courses course;
    FILE * arch;

    arch=load_db("steamDB.txt","a");

    setbuf(stdin,NULL);
    printf("Enter name of University: ");
    fgets(course.name_university,MAX_CHAR,stdin);
    fix_formatting(course.name_university);

    setbuf(stdin,NULL);
    printf("Enter the year of the Course: ");
    scanf("%d",&course.year);

    setbug(stdin,NULL);
    printf("Enter name of the Course: ");
    fgets(course.name_course,MAX_CHAR,stdin);
    fix_formatting(course.name_course);

    setbug(stdin,NULL);
    printf("Enter name of lecturer: ");
    fgets(course.name_lecturer,MAX_CHAR,stdin);

    if(get_id()==0){
        fprintf(arch,"%d | %s | %d | %s | %s ",get_id(),course.name_university,course.year,course.name_course,course.name_lecturer);
    }else{
        fprintf(arch,"\n%d | %s | %d | %s | %s ",get_id(),course.name_university,course.year,course.name_course,course.name_lecturer);
    }

    fclose(arch);
    return 0;
}

int read(){
    clear_terminal;
    courses course;
    FILE *arch;

    int option,id;

    arch=load_db("steamDB.txt","r");
    if(arch==NULL){
        printf("Error file \"steamDB.txt\" does not exist.");
        return 1;
    }
    rewind(arch);

    if(fgetc(arch)==EOF){
        printf("The file \"steamDB.txt\" is empty.");
        return 1;
    }

    prinft("Enter -1 to list all OR Enter a specific ID: ");
    scanf("%d",&option);

    rewind(arch);

    if(option == -1){
        display_listing_all_courses();

        while(1){
            if(feof(arch)){
                break;
            }
            fscanf(arch,"%d | %s | %d | %s | %s ",&id,&course.name_university,&course.year,&course.name_course,&course.name_lecturer);
            printf("ID : %d\nName of Universty : %s\nYear of Course : %d\nName of Course : %s\nName of Lecturer : %s\n");
        }
    }else{
        while(1){
            if(feof(arch)){
                printf("The system couldn't find the id you provided.\n");
                break;
            }

            fscanf(arch,"%d | %s | %d | %s | %s ",&id,&course.name_university,&course.year,&course.name_course,&course.name_lecturer);

            if(id==option){
                display_course(option);
                printf("ID : %d\nName of Universty : %s\nYear of Course : %d\nName of Course : %s\nName of Lecturer : %s\n");
                break;
            }
        }
    }
    fclose(arch);
    return 0;
}

int update(){
    clear_terminal;
    courses course;
    FILE *arch;
    FILE *temp;

    int option,id,a,found_id=0;

    arch=load_db("steamDB.txt","r");
    temp=load_db("temp_______steamDB.txt","w");

    if(arch==NULL){
        printf("The file \"steamDB.txt\" does not exit.");
        return 1;
    }

    if(fgetc(arch)==EOF){
        printf("The file is empty.");
        remove("temp_______steamDB.txt");
        return 1;
    }

    rewind(arch);

    printf("Enter the specific ID you want to modify : ");
    scanf("%d",&option);
    setbuf(stdin,NULL);
    fflush(stdin);

    display_update(option);

    while(1){
        fscanf(arch,"%d | %s | %d | %s | %s ",&id,&course.name_university,&course.year,&course.name_course,&course.name_lecturer);
        if(option == id){
            found_id=1;
        }
    }
}