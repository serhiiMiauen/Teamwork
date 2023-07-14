#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

void login (void);
void registration(void);
void user_log_in(char username[40]);
void to_rent_car(void);
void current_auto(void);
void display_user_data(char username[40]);


struct login
{
    char fname[40];
    char lname[40];
    char username[40];
    char password[30];
    char IBAN[30];
    char passport_id_number[10];
};

int main (){
    int option;
    printf("Press '1' to Register\nPress '2' to Login\n");
    scanf("%d", &option);
    if (option == 1){
        registration();
    }
    else if (option == 2){
        login ();
    }
    
} 

void registration (void){
    FILE *user_data = fopen("user_data.txt", "a");
    if (user_data == NULL){
        printf("Error opening file\n");
        exit(1);
        }

    struct login j;
    fgets(j.fname, sizeof(j.fname), stdin);    

    int x = 0;
    while (x != 9){
    printf("Welcome to the car rental service. To beggin using this app, you need to give some details\n Please, enter your First Name: \n");
    fgets(j.fname, sizeof(j.fname), stdin);    
    printf("And now, Please enter your Surname\n");
    fgets(j.lname, sizeof(j.lname), stdin);

    printf("Now we need your passport id number\n");
    fgets(j.passport_id_number, sizeof(j.passport_id_number), stdin);

    printf("Now enter your IBAN\n");
    fgets(j.IBAN, sizeof(j.IBAN), stdin);    

    printf("Now enter username\n");
    fgets(j.username, sizeof(j.username), stdin);    

    printf("Enter your password\n");
    fgets(j.password, sizeof(j.password), stdin);    

    if (strcmp(j.fname, "\n") == 0 || strcmp(j.lname, "\n") == 0 || strcmp(j.passport_id_number, "\n") == 0 || strcmp(j.IBAN, "\n") == 0 || strcmp(j.username, "\n") == 0 || strcmp(j.password, "\n") == 0) 
    {
        printf("There is a mistake. Looks like you missed a line\nLet's try again\n\n");
    }
    else {break;}
    }
    fwrite(&j, sizeof(j), 1, user_data);
    fclose(user_data);

    printf("Registration completed successfully\nPress any key to continue");
    getchar();

    login();
}

void login (void){
    char username[40], password[30]; 
    FILE *user_data;
    user_data = fopen("user_data.txt", "r");    
    if (user_data == NULL){
        printf("Error opening file\n");
        exit(1);
    }

    struct login l;

    fgets(username, sizeof(username), stdin);

    int found = 0; 
    printf("Please enter your username and password\n Enter username: \n");
    fgets(username, sizeof(username), stdin);
    printf("Enter password:\n");
    fgets(password, sizeof(password), stdin);

    while (fread (&l, sizeof(l), 1, user_data)){
        if (strcmp(username, l.username) == 0 && strcmp(password, l.password) == 0){
            found = 1;
            break;
        }
    }

    if (found == 1){
        printf("\nSuccessful login\n");
        user_log_in(username);
    } 
    else{
        printf("Incorrect login details\n");
    }
    fclose(user_data);
}


void user_log_in(char username[40]){
    int i = 1;
    while (i != 0){
    int option = 0;
    printf("Please choose from one of the following options\n 1. Rent auto\n 2. View current rented auto\n3. Veiw account info\n9. Log out\n");
    scanf("%d",&option);
    switch(option){
        case 1:
            to_rent_car();
            break;
        case 2: 
            current_auto();
            break;
        case 3: 
            display_user_data(username);
            break;
        case 9:
            exit(1);
        default:
            printf("Sorry, we can do that yet\n");


    }
    }
        

}
void to_rent_car(void){printf("a");}
void current_auto(void){printf("b");}


void display_user_data(char username[40]){

    FILE *user_data;
    user_data = fopen("user_data.txt", "r");    
    if (user_data == NULL){
        printf("Error opening file\n");
        exit(1);
    }

    struct login l;
    int found = 0; 

    while (fread (&l, sizeof(l), 1, user_data)){
        if (strcmp(username, l.username) == 0){
            found = 1;
            break;
        }
    }

    if (found == 1){
        printf("First name: %s", l.fname);
        printf("Lase name: %s", l.lname);
        printf("Username: %s", l.username);
        printf("IBAN: %s", l.IBAN);
        printf("Password: %s\n", l.password);
        
    } 
    else{
        printf("Sorry, your details were not found. Please contact technical support");
    }
    fclose(user_data);
    printf("Press any key to continue\n");
    getchar();
}


