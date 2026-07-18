#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "options.h"

int main(){
    char user_input;

    do{
        display_menu(); //returns a menu to the user

        user_input=getchar(); //takes in a single char input from user
        clear_buffer();

        user_input = tolower(user_input); //lowers str to avoid case(upper/lower) errors

        switch (user_input) //switch-case to assign functions to each case
        {
        case 'c':
            create();
            break;        
            
        case 'r':
            read();
            break;
        
        case 'u':
            update();
            break;
        
        case 'd':
            del();
            break;
            
        case 'l':
            return 0;
            break;
        
        default:
            break;
        }

        printf("\n\n\t\tPress Enter to Continue\n");
        setbuf(stdin,NULL);
        while( getchar() != '\n' );

    } while (user_input != 'l');//program exit condition
    
    return 0;
}