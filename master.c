#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

float walletBalance = 500.0;

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

void rentCar() {
    int choice;
    displayCarList();
    printf("Choose a car to rent (enter the number): ");
    scanf("%d", &choice);

    if (choice >= 1 && choice <= numCars && carList[choice - 1].availability) {
        if (walletBalance >= carList[choice - 1].price) {
            printf("You have rented the car '%s'.\n", carList[choice - 1].name);
            carList[choice - 1].availability = 0;
            walletBalance -= carList[choice - 1].price;
            printf("Remaining balance in your wallet: %.2f\n", walletBalance);
        }
        else {
            printf("Insufficient funds in your wallet to rent the car '%s'.\n", carList[choice - 1].name);
        }
    }
    else {
        printf("Invalid car choice or the car is not available.\n");
    }

    printf("Press Enter to continue...");
    getchar();
    getchar();
    system("clear");
}

void displayRentedCar() {
    printf("Currently rented car:\n");
    for (int i = 0; i < numCars; i++) {
        if (!carList[i].availability) {
            printf("Name: %s\n", carList[i].name);
            break;
        }
    }

    printf("Press Enter to continue...");
    getchar();
    getchar();
    system("clear");
}

void displayWalletBalance() {
    printf("Wallet balance: %.2f\n", walletBalance);

    printf("Press Enter to continue...");
    getchar();
    getchar();
    system("clear");
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

int main() {
    initializeCarList();

    int choice;

    while (1) {
        printf("\nMenu:\n");
        printf("1. List available cars\n");
        printf("2. Rent a car\n");
        printf("3. View currently rented car\n");
        printf("4. View wallet balance\n");
        printf("5. View car ratings\n");
        printf("6. Exit\n");
        printf("Choose an option: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n') {
                continue;
            }
            continue;
        }

        switch (choice) {
        case 1:
            displayCarList();
            break;
        case 2:
            rentCar();
            break;
        case 3:
            displayRentedCar();
            break;
        case 4:
            displayWalletBalance();
            break;
        case 5:
            displayCarRatings();
            break;
        case 6:
            exit(0);
        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
    }

    return 0;
}
