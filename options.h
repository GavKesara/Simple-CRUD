#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "db_functions.h"
#include "menu.h"

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

    int new_id=get_id();
    arch=load_db("steamDB.txt","a");

    setbuf(stdin,NULL);
    printf("Enter name of University: ");
    fgets(course.name_university,MAX_CHAR,stdin);

    setbuf(stdin,NULL);
    printf("Enter the year of the Course: ");
    scanf("%d",&course.year);

    setbuf(stdin,NULL);
    printf("Enter name of the Course: ");
    fgets(course.name_course,MAX_CHAR,stdin);

    setbuf(stdin,NULL);
    printf("Enter name of lecturer: ");
    fgets(course.name_lecturer,MAX_CHAR,stdin);

    if(new_id==0){
        fprintf(arch,"%d | %s | %d | %s | %s",new_id,course.name_university,course.year,course.name_course,course.name_lecturer);
    }else{
        fprintf(arch,"%d | %s | %d | %s | %s",new_id,course.name_university,course.year,course.name_course,course.name_lecturer);
    }

    fclose(arch);
    return 0;
}

int read(){
    clear_terminal();
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

    printf("Enter -1 to list all OR Enter a specific ID: ");
    scanf("%d",&option);

    rewind(arch);

    if(option == -1){
        display_listing_all_courses();

        while(fscanf(arch,"%d | %[^|] | %d | %[^|] | %[^\n] ",&id,course.name_university,&course.year,course.name_course,course.name_lecturer)==5){

            printf("ID : %d\nName of Universty : %sYear of Course : %d\nName of Course : %sName of Lecturer : %s\n\n",id,course.name_university,course.year,course.name_course,course.name_lecturer);
        }
    }else{
        while(fscanf(arch,"%d | %[^|] | %d | %[^|] | %[^\n] ",&id,course.name_university,&course.year,course.name_course,course.name_lecturer)==5){

            if(id==option){
                display_course(option);
                printf("ID : %d\nName of Universty : %s\nYear of Course : %d\nName of Course : %s\nName of Lecturer : %s\n",id,course.name_university,course.year,course.name_course,course.name_lecturer);
                break;
            }
        }
    }
    fclose(arch);
    return 0;
}

int update(){
    clear_terminal();
    courses course;
    FILE *arch;
    FILE *temp;

    int option,id,a,found_id=0;
    int Usr_option;

    arch=load_db("steamDB.txt","r");
    temp=load_db("temp_______steamDB.txt","w");

    if(arch==NULL){
        printf("The file \"steamDB.txt\" does not exit.");
        if(temp)fclose(temp);
        return 1;
    }

    if(fgetc(arch)==EOF){
        printf("The file is empty.");
        fclose(temp);
        fclose(arch);
        remove("temp_______steamDB.txt");
        return 1;
    }

    rewind(arch);

    printf("Enter the specific ID you want to modify : ");
    scanf("%d",&option);
    setbuf(stdin,NULL);
    fflush(stdin);

    display_update(option);

    while(fscanf(arch,"%d | %[^|] | %d | %[^|] | %[^\n] ",&id,course.name_university,&course.year,course.name_course,course.name_lecturer)==5){
        if(id==option)
            found_id=1;
            display_options();
            printf("\n\n\nEnter number to modify : ");
            scanf("%d",&Usr_option);
            switch(Usr_option){
                case 0: printf("Enter new name of course : ");
                        fgets(course.name_university,MAX_CHAR,stdin);
                        break;
                case 1: printf("Enter new Course year : ");
                        scanf("%d",&course.year);
                        break;
                case 2: printf("Enter new course name : ");
                        fgets(course.name_course,MAX_CHAR,stdin);
                        break;
                case 3: printf("Enter new lecturer name : ");
                        fgets(course.name_lecturer,MAX_CHAR,stdin);
                        break;
                default: printf("Enter a correct value.");break;
            }
            if(id == 0)
                fprintf(temp,"%d | %s | %d | %s | %s ",id,course.name_university,course.year,course.name_course,course.name_lecturer);
            else
                fprintf(temp,"\n%d | %s | %d | %s | %s ",id,course.name_university,course.year,course.name_course,course.name_lecturer);
        }
    fclose(arch);
    fclose(temp);

    arch = load_db("steamDB.txt","w");
    temp = load_db("temp_______steamDB.txt","r");

    while((a=fgetc(temp))!=EOF){
        fputc(a,arch);
    }
    
    fclose(arch);
    fclose(temp);

    if(found_id){
        printf("\nTask Concluded.");
    }else{
        printf("\nThe system couldn't find the id you provided.");
    }
    remove("temp_______steamDB.txt");
    return 0;

}

int del(){
    clear_terminal();
    courses course;
    FILE * arch;
    FILE * temp;
    
    int option, id, a;

    arch = load_db("steamDB.txt","r");
    temp = load_db("temp____steamDB.txt","w");

    if(arch == NULL){
        printf("The file \"steamDB.txt\" does not exist!");
        return 1;
    }

    if(fgetc(arch) == EOF){
        printf("The file is empty.");
        remove("temp____steamDB.txt");
        return 1;
    }

    rewind(arch);

    printf("Enter the item ID: ");
    scanf("%d", &option);
    setbuf(stdin, NULL);
    fflush(stdin);

    display_delete(option);

    int found_id = 0;

    while (fscanf(arch,"%d | %[^|] | %d | %[^|] | %[^\n] ",&id,course.name_university,&course.year,course.name_course,course.name_lecturer)==5){
        
        if(option == id){
            found_id = 1;
            continue;
        }
            
        if(id-found_id == 0)
            fprintf(temp,"%d | %s | %d | %s | %s ",id,course.name_university,course.year,course.name_course,course.name_lecturer);
        else
            fprintf(temp,"\n%d | %s | %d | %s | %s ",id,course.name_university,course.year,course.name_course,course.name_lecturer);
        
    }


    fclose(arch);
    fclose(temp);

    arch = load_db("steamDB.txt","w");
    temp = load_db("temp____steamDB.txt","r");

    while( (a = fgetc(temp)) != EOF )
        fputc(a, arch);
    
    fclose(arch);
    fclose(temp);

    if(found_id)
        printf("\nTask concluded.");
    
    else
        printf("\nThe system couldn't find the ID you provided.");
    
    remove("temp____steamDB.txt");
    
    return 0;
}