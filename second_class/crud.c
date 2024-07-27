#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct driver {
    unsigned int id;
    char name[50];
    char email[50];
    char phone[50];
    unsigned int experience;
    char workingDays[60];

};

//tracking of current id number
unsigned int id = 1;

void readInConsoleMessage(const char* console_text, char* result){
    printf(console_text);
    scanf("\n%[^\t\n]s", result);
}


// 
void fileCreation(){
    FILE* file = fopen("database.txt", "a");
    fclose(file);
}

struct driver* file_read(FILE* file)
{
    struct driver* actual = (struct driver*) malloc (sizeof(struct driver));
    fscan(file, "%u\t%[^\t]\t%s\t%s\t%u\t%[^\t\n]", &(actual->id), actual->name, actual->email, actual->phone, &(actual->experience), actual->workingDays );

    return actual;
    
}

void id_setup()
{
    FILE *infile;
    struct driver* actual;
    id = 0;

    infile = fopen("database.txt", "r");
    if (infile != NULL) 
    {
        actual = file_read(infile);
        while(!feof(infile))
        {
            id = actual -> id;
            free(actual);
            actual = file_read(infile);

        }
        free(actual);

    }
    fclose(infile);
    id++;
}

int main(int argc, char* argv)
{
    
    int command;
    unsigned int id;
    unsigned int exp;

    fileCreation();
    id_setup();

    do
    {
        
        printf("-----MENU-----\n");
        printf("Driver Add - 1\n");
        printf("Driver List - 2\n");
        printf("Driver Experience List - 3\n");
        printf("Driver Mod - 4\n");
        printf("Driver Delete - 5\n");
        printf("Exit - 6\n");
        
        switch (expression)
        {
        case '1':
            driver_creation();
            break;
        case '2':
            list();
            break;
        case '3':
            printf("Experience: ");
            scanf("%u", &exp);
            break;
        case '4':
            printf();
            break;
        case '5':
            driver_creation();
            break;
        case '6':
            driver_creation();
            break;
        
        default:
            break;
        }

    } while ((command == getchar()) != EOF);
    

    return 0;
}