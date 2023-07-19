#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

void login(void);
void registration(void);
void user_log_in(char* username, char* password);
void display_user_data(char* username, char* password);
FILE* open_user_data_file(const char* filename, const char* mode);
void initializeCarList();
void displayCarList();
void displayRentedCar(char* username, char* password);
void rentCar(char* username, char* password);
void displayCarRatings();

struct login {
    char fname[40];
    char lname[40];
    char username[40];
    char password[30];
    char IBAN[30];
    char passport_id_number[10];
    char email[40];
    char phone_number[20];
    char rented_car[40];
};


#define MAX_CARS 14
#define MAX_NAME_LENGTH 50

typedef struct {
    char name[MAX_NAME_LENGTH];
    int availability;
    float price;
    float rating;
} Car;

Car carList[MAX_CARS];
int numCars = 0;


int main() {
    int option;
    int choice;
    initializeCarList();

    printf("Press '1' to Register\nPress '2' to Login\n");
    scanf("%d", &option);
    if (option == 1) {
        registration();
    }
    else if (option == 2) {
        // system("clear");
        login();
    }
    return 0;

}

FILE* open_user_data_file(const char* filename, const char* mode) {
    FILE* user_data = fopen(filename, mode);
    if (user_data == NULL) {
        printf("Error opening file: %s\n", filename);
        return 0;
    }
    return user_data;
}

int find_user(char* username, char* password, FILE* user_data) {
    struct login l;
    rewind(user_data);
    while (fread(&l, sizeof(struct login), 1, user_data)) {
        if (strcmp(username, l.username) == 0 && strcmp(password, l.password) == 0) {
            return 1;
        }
    }
    return 0;
}


void registration(void) {
    FILE* user_data = open_user_data_file("user_data.txt", "a");

    struct login l;

    getchar();

    int x = 0;
    while (x != 9) {
        printf("Welcome to the car rental service. To beggin using this app, you need to give some details\n Please, enter your First Name: \n");
        fgets(l.fname, sizeof(l.fname), stdin);

        printf("And now, Please enter your Surname\n");
        fgets(l.lname, sizeof(l.lname), stdin);

        printf("Now we need your passport id number\n");
        fgets(l.passport_id_number, sizeof(l.passport_id_number), stdin);

        printf("Now enter your IBAN\n");
        fgets(l.IBAN, sizeof(l.IBAN), stdin);

        printf("Now enter your email\n");
        fgets(l.email, sizeof(l.email), stdin);

        printf("Now enter your phone number\n");
        fgets(l.phone_number, sizeof(l.phone_number), stdin);

        printf("Now enter username\n");
        fgets(l.username, sizeof(l.username), stdin);

        printf("Enter your password\n");
        fgets(l.password, sizeof(l.password), stdin);

        if (strcmp(l.fname, "\n") == 0 || strcmp(l.lname, "\n") == 0 || strcmp(l.passport_id_number, "\n") == 0 || strcmp(l.IBAN, "\n") == 0 || strcmp(l.username, "\n") == 0 || strcmp(l.password, "\n") == 0 || strcmp(l.username, "\n") == 0 || strcmp(l.phone_number, "\n") == 0)
        {
            printf("There is a mistake. Looks like you missed a line\nLet's try again\n\n");
        }
        else { break; }
    }
    strcpy(l.rented_car, "");


    fwrite(&l, sizeof(l), 1, user_data);
    fclose(user_data);

    printf("Registration completed successfully\nPress any key to continue");
    getchar();

    login();
    // system("clear");
}


void login(void) {
    char username[40], password[30];
    FILE* user_data = open_user_data_file("user_data.txt", "r");

    struct login l;

    getchar();

    int found = 0;
    printf("Please enter your username and password\nEnter username:\n");
    fgets(username, sizeof(username), stdin);
    printf("Enter password:\n");
    fgets(password, sizeof(password), stdin);

    found = find_user(username, password, user_data);

    if (found == 1) {
        printf("\nSuccessful login\n");
        user_log_in(username, password);
    }
    else {
        printf("Incorrect login details\n");
    }
    fclose(user_data);
}



void user_log_in(char* username, char* password) {
    int i = 1;
    while (i != 0) {
        int option = 0;
        printf("Please choose from one of the following options\n1. Look at the car catalogue / Rent a car.\n2. Display car ratings\n3. View current rented auto\n4. Display user data\n9. Log out\n");
        scanf("%d", &option);
        switch (option) {
        case 1:
            // system("clear");
            rentCar(username, password);
            break;
        case 2:
            // system("clear");
            displayCarRatings();
            break;
        case 3:
            // system("clear");
            displayRentedCar(username, password);
            break;
        case 4:
            // system("clear");
            display_user_data(username, password);
            break;
        case 9:
            i = 0;
            break;
        default:
            printf("Sorry, we cannot do that yet\n");
        }
    }


}


void display_user_data(char* username, char* password) {
    FILE* user_data = open_user_data_file("user_data.txt", "r");
    struct login l;
    int found = find_user(username, password, user_data);

    if (found == 1) {
        fseek(user_data, -sizeof(struct login), SEEK_CUR);
        fread(&l, sizeof(struct login), 1, user_data);

        printf("First name: %s\n", l.fname);
        printf("Last name: %s\n", l.lname);
        printf("Username: %s\n", l.username);
        printf("IBAN: %s\n", l.IBAN);
        printf("Password: %s\n", l.password);
        printf("Email: %s\n", l.email);
        printf("Phone number: %s\n", l.phone_number);
        printf("Current car: %s\n", l.rented_car);
    }
    else {
        printf("Sorry, your details were not found. Please contact technical support.\n");
    }

    fclose(user_data);

    printf("Press any key to continue\n");
    getchar();
    getchar();
    // system("clear");
}

void initializeCarList() {
    Car car1;
    strcpy(car1.name, "Audi A4");
    car1.availability = 1;
    car1.price = 50.0;
    car1.rating = 4.5;
    carList[numCars] = car1;
    numCars++;

    Car car2;
    strcpy(car2.name, "BMW X5");
    car2.availability = 1;
    car2.price = 70.0;
    car2.rating = 4.2;
    carList[numCars] = car2;
    numCars++;

    Car car3;
    strcpy(car3.name, "Mercedes C-Class");
    car3.availability = 1;
    car3.price = 60.0;
    car3.rating = 4.7;
    carList[numCars] = car3;
    numCars++;

    Car car4;
    strcpy(car4.name, "Ford Mustang");
    car4.availability = 1;
    car4.price = 80.0;
    car4.rating = 4.4;
    carList[numCars] = car4;
    numCars++;

    Car car5;
    strcpy(car5.name, "Chevrolet Camaro");
    car5.availability = 1;
    car5.price = 75.0;
    car5.rating = 4.3;
    carList[numCars] = car5;
    numCars++;

    Car car6;
    strcpy(car6.name, "Toyota Camry");
    car6.availability = 1;
    car6.price = 55.0;
    car6.rating = 4.1;
    carList[numCars] = car6;
    numCars++;

    Car car7;
    strcpy(car7.name, "Honda Civic");
    car7.availability = 1;
    car7.price = 45.0;
    car7.rating = 4.0;
    carList[numCars] = car7;
    numCars++;

    Car car8;
    strcpy(car8.name, "Nissan Altima");
    car8.availability = 1;
    car8.price = 50.0;
    car8.rating = 3.9;
    carList[numCars] = car8;
    numCars++;
}

void displayCarList() {
    if (numCars == 0) {
        printf("No cars available.\n");
        return;
    }

    printf("Available cars:\n");
    for (int i = 0; i < numCars; i++) {
        if (carList[i].availability) {
            printf("%d. Name: %s, Price: %.2f, Rating: %.1f\n", i + 1, carList[i].name, carList[i].price, carList[i].rating);
        }
    }
}

void rentCar(char* username, char* password) {
    int choice;
    displayCarList();
    printf("Choose a car to rent (enter the number): ");
    scanf("%d", &choice);

    if (choice >= 1 && choice <= numCars && carList[choice - 1].availability) {
        printf("You have rented the car '%s'.\n", carList[choice - 1].name);
        carList[choice - 1].availability = 0;

        struct login l;
        FILE* user_data = open_user_data_file("user_data.txt", "r+"); // Open with "r+" mode

        int found = find_user(username, password, user_data);

        if (found == 1) {
            fseek(user_data, -sizeof(struct login), SEEK_CUR);
            fread(&l, sizeof(struct login), 1, user_data);

            strcpy(l.rented_car, carList[choice - 1].name);

            fseek(user_data, -sizeof(struct login), SEEK_CUR);
            fwrite(&l, sizeof(struct login), 1, user_data);

            fclose(user_data);
        }
        else {
            printf("Sorry, your details were not found. Please contact technical support.\n");
        }
    }
    else {
        printf("Invalid car choice or the car is not available.\n");
    }

    printf("Press Enter to continue...");
    getchar();
    getchar();
    // system("clear");
}

void displayRentedCar(char* username, char* password) {
    FILE* user_data = open_user_data_file("user_data.txt", "r");
    struct login l;
    int found = find_user(username, password, user_data);

    if (found == 1) {
        fseek(user_data, -sizeof(struct login), SEEK_CUR);
        fread(&l, sizeof(struct login), 1, user_data);

        printf("You have rented the car: %s\n", l.rented_car);
    }
    else {
        printf("Looks like you don't have any rented car.\n");
    }

    fclose(user_data);

    printf("Press Enter to continue...");
    getchar();
    getchar();
    // system("clear");
}

void displayCarRatings() {
    if (numCars == 0) {
        printf("No cars available.\n");
        return;
    }

    printf("Car Ratings:\n");
    for (int i = 0; i < numCars; i++) {
        printf("Name: %s, Rating: %.1f\n", carList[i].name, carList[i].rating);
    }
}


