#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERS 100

struct login
{
    char fname[30];
    char lname[30];
    char username[30];
    char password[20];
};

void login(void);
void registration(void);

int main(void)
{
    int option;

    printf("Press '1' to Register\nPress '2' to Login\n\n");
    scanf("%d", &option);
    getchar(); // Catching newline.

    system("CLS");

    if (option == 1)
    {
        registration();
    }
    else if (option == 2)
    {
        login();
    }

    return 0;
}

void login(void)
{
    char username[30], password[20];
    FILE *log;

    log = fopen("login.txt", "r");
    if (log == NULL)
    {
        fputs("Error opening file!", stderr);
        exit(1);
    }

    struct login l;
    int found = 0;

    printf("\nPlease enter your login credentials below:\n\n");
    printf("Username: ");
    fgets(username, sizeof(username), stdin);
    printf("\nPassword: ");
    fgets(password, sizeof(password), stdin);

    while (fread(&l, sizeof(l), 1, log))
    {
        if (strcmp(username, l.username) == 0 && strcmp(password, l.password) == 0)
        {
            found = 1;
            break;
        }
    }

    if (found)
    {
        printf("\nSuccessful Login\n");
    }
    else
    {
        printf("\nIncorrect Login Details\nPlease enter the correct credentials\n");
    }

    fclose(log);
}

void registration(void)
{
    FILE *log = fopen("login.txt", "a");
    if (log == NULL)
    {
        fputs("Error opening file!", stderr);
        exit(1);
    }

    struct login l;

    printf("\nWelcome to your online course provider. We need to enter some details for registration.\n\n");
    printf("Enter First Name: ");
    fgets(l.fname, sizeof(l.fname), stdin);
    printf("Enter Surname: ");
    fgets(l.lname, sizeof(l.lname), stdin);

    printf("Thank you.\nNow please choose a username and password as credentials for system login.\n");
    printf("Ensure the username is no more than 30 characters long.\n");
    printf("Ensure your password is at least 8 characters long and contains lowercase, uppercase, numerical, and special character values.\n");

    printf("Enter Username: ");
    fgets(l.username, sizeof(l.username), stdin);
    printf("Enter Password: ");
    fgets(l.password, sizeof(l.password), stdin);

    fwrite(&l, sizeof(l), 1, log);
    fclose(log);

    printf("\nConfirming details...\n...\nWelcome, %s!\n\n", l.fname);
    printf("Registration Successful!\n");
    printf("Press any key to continue...");
    getchar();
    system("CLS");
    login();
}
