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
    char status[MAX_CHAR];
};

typedef struct course courses;

int create(){
    display_creating_course(); //display create course template
    courses course;
    FILE * arch;
    int new_id=get_id(); //gets id.
     
    arch=load_db("steamDB.txt","a");//opens file stream

    printf("\nEnter name of University: ");
    fgets(course.name_university,MAX_CHAR,stdin);
    course.name_university[strcspn(course.name_university,"\n")]='\0';

    printf("Enter the year of the Course: ");
    scanf("%d",&course.year);
    clear_buffer();

    printf("Enter name of the Course: ");
    fgets(course.name_course,MAX_CHAR,stdin);
    course.name_course[strcspn(course.name_course,"\n")]='\0';

    printf("Enter name of lecturer: ");
    fgets(course.name_lecturer,MAX_CHAR,stdin);
    course.name_lecturer[strcspn(course.name_lecturer,"\n")]='\0';

    printf("Enter Status of Course: ");
    fgets(course.status,MAX_CHAR,stdin);
    course.status[strcspn(course.status,"\n")]='\0';

    if(new_id==0){
        fprintf(arch,"%d | %s | %d | %s | %s | %s",new_id,course.name_university,course.year,course.name_course,course.name_lecturer,course.status);
    }else{
        fprintf(arch,"\n%d | %s | %d | %s | %s | %s",new_id,course.name_university,course.year,course.name_course,course.name_lecturer,course.status);
    }

    fclose(arch); //closes file stream
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
        return -1;
    }
    rewind(arch); //takes file cursor back to beginning

    if(fgetc(arch)==EOF){
        printf("The file \"steamDB.txt\" is empty.");
        return -1;
    }

    printf("Enter -1 to list all OR Enter a specific ID: ");
    scanf("%d",&option);
    clear_buffer();

    rewind(arch);

    if(option == -1){
        display_listing_all_courses();

        while(fscanf(arch,"%d | %[^|] | %d | %[^|] | %[^|] | %[^\n]",&id,course.name_university,&course.year,course.name_course,course.name_lecturer,course.status)==6){

            printf("ID : %d\t|\tStatus : %s\n\nName of Universty : %s\nYear of Course : %d\nName of Course : %s\nName of Lecturer : %s\n",id,course.status,course.name_university,course.year,course.name_course,course.name_lecturer);
        }
    }else{
        while(fscanf(arch,"%d | %[^|] | %d | %[^|] | %[^|] | %[^\n]",&id,course.name_university,&course.year,course.name_course,course.name_lecturer,course.status)==6){

            if(id==option){
                display_course(option);
                printf("ID : %d\t|\tStatus : %s\nName of Universty : %s\nYear of Course : %d\nName of Course : %s\nName of Lecturer : %s\n\n",id,course.status,course.name_university,course.year,course.name_course,course.name_lecturer);
                break;
            }
        }
    }
    fclose(arch);
    return 0;
}

int update_status(){
    clear_terminal();
    courses course;
    FILE *arch;
    FILE *temp;

    int a,found_id=0;
    int option;

    arch=load_db("steamDB.txt","r");
    temp=load_db("temp_______steamDB.txt","w");

    if(temp==NULL){
        printf("The file \"temp_______steamDB.txt\" does not exist.");
        return -1;
    }
    if(arch==NULL){
        printf("The file \"steamDB.txt\" does not exist.");
        if(temp!=NULL){
            remove("temp_______steamDB.txt");
        }
        return -1;
    }

    if(fgetc(arch)==EOF){
        printf("The file is empty.");
        fclose(temp);
        fclose(arch);
        remove("temp_______steamDB.txt");
        return -1;
    }
    int id;
    printf("Enter id to modify Status : ");
    scanf("%d",&option);
    clear_buffer();

    rewind(arch);   
    while(fscanf(arch,"%d | %[^|] | %d | %[^|] | %[^|] | %[^\n] ",&id,course.name_university,&course.year,course.name_course,course.name_lecturer,course.status)==6){
        if(id==option){
            found_id=1;
            printf("Enter new Status of Course : ");
            fgets(course.status,MAX_CHAR,stdin);
        }
        if(id == 0 || (id==1 && found_id && option==0)){
            fprintf(temp,"%d | %s | %d | %s | %s | %s ",id,course.name_university,course.year,course.name_course,course.name_lecturer,course.status);
        }else{
            fprintf(temp,"\n%d | %s | %d | %s | %s | %s",id,course.name_university,course.year,course.name_course,course.name_lecturer,course.status);
        }
    }
    fclose(arch);
    fclose(temp);

    arch=load_db("steamDB.txt","w");
    temp=load_db("temp_______steamDB.txt","r");

    while((a=fgetc(temp))!=EOF){ //writes data from temp into steamDB
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

int update(){
    clear_terminal();
    courses course;
    FILE *arch;
    FILE *temp;

    int option,id,a,found_id=0;
    int Usr_option;

    arch=load_db("steamDB.txt","r"); //opens file stream 
    temp=load_db("temp_______steamDB.txt","w"); //create new temp file

    if(temp==NULL){
        printf("Error creating temp file.");
        return -1;
    }

    if(arch==NULL){
        printf("The file \"steamDB.txt\" does not exit.");
        if(temp!=NULL)fclose(temp);
        return -1; //exit with error(-1)
    }

    if(fgetc(arch)==EOF){
        printf("The file is empty.");
        fclose(temp);
        fclose(arch);
        remove("temp_______steamDB.txt");
        return -1; //exit with error(-1)
    }

    rewind(arch);

    printf("Enter the specific ID you want to modify : ");
    scanf("%d",&option);
    clear_buffer();

    while(fscanf(arch,"%d | %[^|] | %d | %[^|] | %[^|] | %[^\n] ",&id,course.name_university,&course.year,course.name_course,course.name_lecturer,course.status)==6){
        if(id==option){
            found_id=1;
            display_options(option);
            printf("\n\n\nEnter number to modify : ");
            scanf("%d",&Usr_option);
            clear_buffer(); //clears problem of /n being read into fgets
            switch(Usr_option){
                case 0: printf("Enter new name of course : ");
                        fgets(course.name_university,MAX_CHAR,stdin);
                        course.name_university[strcspn(course.name_university,"\n")]='\0';
                        break;
                case 1: printf("Enter new Course year : ");
                        scanf("%d",&course.year);
                        clear_buffer();
                        break;
                case 2: printf("Enter new course name : ");
                        fgets(course.name_course,MAX_CHAR,stdin);
                        course.name_course[strcspn(course.name_course,"\n")]='\0';
                        break;
                case 3: printf("Enter new lecturer name : ");
                        fgets(course.name_lecturer,MAX_CHAR,stdin);
                        course.name_lecturer[strcspn(course.name_lecturer,"\n")]='\0';
                        break;
                case 4: printf("Enter new Status : ");
                        fgets(course.status,MAX_CHAR,stdin);
                        course.status[strcspn(course.status,"\n")]='\0';
                        break;
                default: printf("Enter a correct value.");break;
            }
        }
        if(id == 0 || (id==1 && found_id && option==0)){
            fprintf(temp,"%d | %s | %d | %s | %s | %s ",id,course.name_university,course.year,course.name_course,course.name_lecturer,course.status);
        }else{
            fprintf(temp,"\n%d | %s | %d | %s | %s | %s",id,course.name_university,course.year,course.name_course,course.name_lecturer,course.status);            
        }
    }
    fclose(arch);
    fclose(temp);
    
    arch=load_db("steamDB.txt","w");
    temp=load_db("temp_______steamDB.txt","r");

    while((a=fgetc(temp))!=EOF){ //puts data in temp to arch
        fputc(a,arch);
    }

    fclose(temp);
    fclose(arch);

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
        return -1;
    }

    if(fgetc(arch) == EOF){
        printf("The file is empty.");
        remove("temp____steamDB.txt");
        return -1;
    }

    rewind(arch);

    printf("Enter the item ID: ");
    scanf("%d", &option);
    clear_buffer();

    display_delete(option);

    int found_id = 0;

    while (fscanf(arch,"%d | %[^|] | %d | %[^|] | %[^|] | %[^\n] ",&id,course.name_university,&course.year,course.name_course,course.name_lecturer,course.status)==6){
        
        if(option == id){
            found_id = 1;
            continue;
        }
            
        if(id-found_id == 0)
            fprintf(temp,"%d | %s | %d | %s | %s | %s",id,course.name_university,course.year,course.name_course,course.name_lecturer,course.status);
        else
            fprintf(temp,"\n%d | %s | %d | %s | %s | %s",id,course.name_university,course.year,course.name_course,course.name_lecturer,course.status);
        
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