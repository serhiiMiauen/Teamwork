#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

void login (void);
void registration(void);
void user_log_in(char *username, char *password);
void catalogue_of_cars(char *username);
void current_auto(char *username);
void display_user_data(char *username,char *password) ;
FILE *open_user_data_file(const char *filename, const char *mode);
int find_user(char *username, char *password, FILE *user_data);
void rent_car(int *option, char *username);

struct login{
    char fname[40];
    char lname[40];
    char username[40];
    char password[30];
    char IBAN[30];
    char passport_id_number[10];
    char rented_car[40];
};
struct car{
    char car_brend[40];
    char maker[20];
    int year;
    float price_per_day;
};

struct car car_catalogue[] = {
    {"Tesla Model S", "Tesla", 2012, 46.99},
    {"Chevrolet Volt", "Chevrolet", 2010, 38.99},
    {"Ford Focus", "Ford", 2010, 35.99},
    {"Toyota Prius (Third Generation)", "Toyota", 2009, 41.99},
    {"Honda CR-V (Fourth Generation)", "Honda", 2011, 34.99},
    {"BMW 5 Series (F10)", "BMW", 2010, 29.99},
    {"Audi A4 (B8)", "Audi", 2007, 39.99},
    {"Nissan Leaf", "Nissan", 2010, 32.99},
    {"Hyundai Sonata (Sixth Generation)", "Hyundai", 2009, 34.99},
    {"Jeep Wrangler (JK)", "Jeep", 2006, 36.99},
    {"Subaru Impreza (Fourth Generation)", "Subaru", 2007, 29.99},
    {"Kia Optima (Third Generation)", "Kia", 2010, 32.99},
    {"Mercedes-Benz C-Class (W204)", "Mercedes-Benz", 2007, },
    {"Porsche Panamera", "Porsche", 2009, 49.99},
    {"Lexus RX (Third Generation)", "Lexus", 2008, 37.99}
};

int main (){
    int option;
    printf("Press '1' to Register\nPress '2' to Login\n");
    scanf("%d", &option);
    if (option == 1){
        printf("\033[2J\033[1;1H");
        registration();
    }
    else if (option == 2){
        printf("\033[2J\033[1;1H");
        login ();
    }
    return 0;

} 

FILE *open_user_data_file(const char *filename, const char *mode) {
    FILE *user_data = fopen(filename, mode);
    if (user_data == NULL) {
        printf("Error opening file: %s\n", filename);
        exit(1);
    }
    return user_data;
}

int find_user(char *username, char *password, FILE *user_data){
    struct login l;

        while (fread (&l, sizeof(l), 1, user_data)){
            username[strcspn(username, "\n")] = '\0';
            password[strcspn(password, "\n")] = '\0';
            if (strcmp(username, l.username) == 0 && strcmp(password, l.password) == 0){
            return 1;
        }
    }
    return 0;
}

void registration (void){
    FILE *user_data = open_user_data_file("user_data.txt", "a");

    struct login l;

    getchar();

    int x = 0;
    while (x != 9){
    printf("Welcome to the car rental service. To beggin using this app, you need to give some details\n Please, enter your First Name: \n");
    fgets(l.fname, sizeof(l.fname), stdin);    
    printf("And now, Please enter your Surname\n");
    fgets(l.lname, sizeof(l.lname), stdin);

    printf("Now we need your passport id number\n");
    fgets(l.passport_id_number, sizeof(l.passport_id_number), stdin);

    printf("Now enter your IBAN\n");
    fgets(l.IBAN, sizeof(l.IBAN), stdin);    

    printf("Now enter username\n");
    fgets(l.username, sizeof(l.username), stdin);    

    printf("Enter your password\n");
    fgets(l.password, sizeof(l.password), stdin);    

    if (strcmp(l.fname, "\n") == 0 || strcmp(l.lname, "\n") == 0 || strcmp(l.passport_id_number, "\n") == 0 || strcmp(l.IBAN, "\n") == 0 || strcmp(l.username, "\n") == 0 || strcmp(l.password, "\n") == 0) 
    {
        printf("There is a mistake. Looks like you missed a line\nLet's try again\n\n");
    }
    else {break;}
    }
    strcpy(l.rented_car, "You don't have any rented car");

    fwrite(&l, sizeof(l), 1, user_data);
    fclose(user_data);

    printf("Registration completed successfully\nPress any key to continue");
    getchar();

    login();
    printf("\033[2J\033[1;1H");
}


void login (void){
    char username[40], password[30]; 
    FILE *user_data = open_user_data_file("user_data.txt", "r");

    struct login l;

    getchar();

    int found = 0; 
    printf("Please enter your username and password\nEnter username:\n");
    fgets(username, sizeof(username), stdin);
    printf("Enter password:\n");
    fgets(password, sizeof(password), stdin);

    found = find_user(username, password, user_data);

    if (found == 1){
        printf("\nSuccessful login\n");
        user_log_in(username,password);
    } 
    else{
        printf("Incorrect login details\n");
    }
    fclose(user_data);
    printf("\033[2J\033[1;1H");
}



void user_log_in(char *username, char *password) {
    int i = 1;
    while (i != 0){
    int option = 0;
    printf("Please choose from one of the following options\n1. Rent auto\n2. View current rented auto\n3. Veiw account info\n9. Log out\n");
    scanf("%d",&option);
    switch(option){
        case 1:
            catalogue_of_cars(username);
            printf("\033[2J\033[1;1H");
            break;
        case 2: 
            current_auto(username);
            printf("\033[2J\033[1;1H");
            break;
        case 3: 
            display_user_data(username,password);
            printf("\033[2J\033[1;1H");
            break;
        case 9:
            exit(1);
        default:
            printf("Sorry, we cannot do that yet\n");
        }
    }
        

}
void catalogue_of_cars(char *username){ 
    printf("\033[2J\033[1;1H");
    for (int i = 0; i < sizeof(car_catalogue)/sizeof(car_catalogue[0]); i ++){
        printf("%d: Brend of car -- %s \t Maker of car -- %s\tReleased -- %d\t Price per day -- %0.2f€ (euro/day)\n", i, car_catalogue[i].car_brend, car_catalogue[i].maker, car_catalogue[i].year, car_catalogue[i].price_per_day);
    }
    int option = 0;
    printf("Please select one of the below options:\n1. Rent the car \n2. Exit\n");
    scanf("%d",&option);
        switch(option){
            case 1:
                option = 0;
                printf("Please select one of the cars above\n");
                scanf("%d",&option);
                if(option <0 || option>15){
                        printf("An error occurred, please try again later\n");
                        scanf("%d",&option);
                        return 0;}
                // rent_car(option, username);   in progress
                break;
            case 2:
                return 0;
                break;
            default:
                printf("Please select an available option\n");
                break;
    }
    printf("\033[2J\033[1;1H");

}
void current_auto(char *username){


}

void rent_car(int *option, char *username){
    printf("c2");
}

void display_user_data(char *username, char *password){
    FILE *user_data = open_user_data_file("user_data.txt", "r");

    struct login l;
    int found = 0; 

 found = find_user(username, password, user_data);

    if (found == 1){
        printf("First name: %s\n", l.fname);
        printf("Lase name: %s\n", l.lname);
        printf("Username: %s\n", l.username);
        printf("IBAN: %s\n", l.IBAN);
        printf("Password: %s\n", l.password);
        printf("Currect car: %s\n", l.rented_car);
        
    } 
    else{
        printf("Sorry, your details were not found. Please contact technical support\n");
    }
    fclose(user_data);
    printf("Press any key to continue\n");
    scanf("%d",&found);
    printf("\033[2J\033[1;1H");
}
