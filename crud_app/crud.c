#include <stdio.h>
#include <strings.h>
#include <stdlib.h>

// func declarations
void process_command(int option);
void modify_driver(void);
void list_experience(void);
int list_drivers(void);
void add_driver(void);
void print_menu(void);


typedef struct{
    unsigned int id;
    char name[50];
    char email[50];
    unsigned int experience;
    char working_days[100];
} Driver;


int main(int argc, char** argv){
    int option;

    FILE* fp = fopen("database.txt", "w");

    

    print_menu();
    do {        
        printf("Type selected option: ");
        scanf("%i", &option);
        process_command(option);
    } while (option != 6);

    printf("Exiting...\n");
    return 0;
}

void process_command(int option){
    switch (option){
        case 0:
            print_menu();
            break;
        case 1:
            add_driver();
            break;
        case 2:
            list_drivers();
            break;
        case 3:
            list_drivers();
            break;
        case 4:
            list_experience();
            break;
        case 5:
            modify_driver();
            break;
        case 6:
            break;
        default:
            printf("%i is invalid, please enter a valid option.", option);
    }

}
void modify_driver(void){
    printf("Modifing driver...\n");
}

void list_experience(void){
    printf("Listing experience...\n");
}

int list_drivers(void){
    printf("Listing drivers...\n");
    printf("opening database...\n");
    
    FILE* fp = fopen("database.txt", "r");

    if (fp == NULL){
        printf("file cannot be opened.");
        return 1;
    } 

    char str[200];
    int i = 1;
    while (fgets(str, 200, fp) != NULL){
        printf("Line %i: ", i);
        printf("%s", str);
        i++;
    }

    fclose(fp);
    return 0;
}

void add_driver(void){
    printf("Adding driver...\n");
}

void print_menu(void){
    char options_menu[][50] = {
        "Print options\t\t - 0\n",
        "Driver Add\t\t - 1\n",
        "Driver List\t\t - 2\n",
        "Driver Experience List\t - 3\n",
        "Driver Mod\t\t - 4\n",
        "Driver Delete\t\t - 5\n",
        "Exit\t\t\t - 6\n"
    };
    printf("-----OPTIONS-----\n");

    int i;
    for(i = 0; i < (sizeof(options_menu)/sizeof(options_menu[0])); i++){
        printf("%s", options_menu[i]);
    }
}



