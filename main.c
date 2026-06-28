#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "options.h"

int main(){
    char user_input;
    do{
        display_menu();
    }while(user_input!='l');
    return 0;
}