#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

FILE* load_db(char *file_name, char *option){
    FILE * file;
    
    file = fopen(file_name,option);

    return file;
}

void fix_formatting(char *string){
    string[strcspn(string, "\n")] = 0;

    for(int i = 0; i < strlen(string); i++){
        string[i] = tolower(string[i]);
        string[i] = (string[i] == ' ') ? '_' : string[i];
    }
}

int get_id (){
    FILE * file;

    file = load_db("steamDB.txt","r");
    
    if (file == NULL){
        printf("Error loading file steamDB.txt");
        return -1; //program exit(-1)
    }

    int c = fgetc(file);
    
    if (c == EOF) {
        return 0; // If the file is empty, it means that there are no games registered. 
    } else {
        ungetc(c, file);
    }

    char line[255];
    int last_id;
    
    while(fgets(line,sizeof(line),file)!=NULL){
        last_id = atoi(&line[0]);
    }
    fclose(file);
    return last_id + 1;
}

void clear_buffer(){
    int c;
    while((c=getchar())!='\n' && c!=EOF);
}