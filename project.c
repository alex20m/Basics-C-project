#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "project.h"


int main(void) {

    char input[1000];
    char surname[100];
    char team[100];
    int hour;
    int minute;
    int second;
    char filename[50];
    int count = 0; //Number of drivers
    char n[2];
    int retval; //Integer for checking return value from save_to_file function.

    /* We start by making an array for where every element is a struct driver.
    We malloc for one element in the start and then we realloc for every new element that gets added.
    We also malloc every surname and team member in the function add_driver.*/
    Driver *driver = calloc(count + 1, sizeof(Driver));

    fgets(input, sizeof(input), stdin); // Get input

    while(input[0] != 'Q'){

        if(input[0] == 'A'){
            if(sscanf(input, "%c %s %s%1s", input, surname, team, n) == 3){
                driver = realloc(driver, (count + 1) * sizeof(Driver));
                if(add_driver(surname, team, count, driver) == 1){
                    printf("Driver \"%s\" is already in the database.\n", surname);
                }
                else{
                    printf("SUCCESS\n");
                    count++;
                }
            }
            else{
                printf("A should be followed by exactly 2 arguments.\n");
            }
        }

        else if(input[0] == 'L'){ 
            if(print_race(driver, count, stdout) == 0){
                printf("SUCCESS\n");
            }
        }

        else if(input[0] == 'W'){
            if(sscanf(input, "%c %s%1s", input, filename, n) == 2){
                FILE *ptr;
                ptr = fopen(filename, "w");
                if(ptr == NULL){
                    printf("Error writing to file %s.\n", filename);
                }
                else if(print_race(driver, count, ptr) == 0){
                    printf("SUCCESS\n");
                }
                fclose(ptr);
            }
            else{
                printf("W should be followed by exactly 1 argument.\n");
            }

        }

        else if(input[0] == 'O'){
            if(sscanf(input, "%c %s%1s", input, filename, n) == 2){
                retval = load_from_file(driver, filename, count);
                if(retval != -1){
                    count = retval;
                    printf("SUCCESS\n");
                }
            }
            else{
                printf("O should be followed by exactly 1 argument.\n");
            }
        }

        else if(input[0] == 'U'){
            if(sscanf(input, "%c %s %d %d %d%1s", input, surname, &hour, &minute, &second, n) == 5){
                if(update_total_time(surname, hour, minute, second, driver, count) == 0){
                    printf("SUCCESS\n");
                }
            }
            else{
                printf("U should be followed by exactly 4 arguments.\n");
            }
        }

        else{
            printf("Invalid command %c\n", input[0]);
        }

        fgets(input, sizeof(input), stdin); // Ask for new input
    }
    for(int i = 0; i < count; i++){
        free(driver[i].surname);
        free(driver[i].team);
    }
    free(driver);
    printf("SUCCESS\n");
}

//Adds a new driver to the struct array.
//Return 0 if successful, otherwise 1.
int add_driver(char *surname, char *team, int count, Driver *driver){

    int i = 0;

    while(i < count){
        if(strcmp(surname, driver[i].surname) == 0){
            return 1; // Driver is already in system
        }
        i++;
    }

    driver[count].surname = malloc(strlen(surname) + 1);
    driver[count].team = malloc(strlen(team) + 1);
    strcpy(driver[count].surname, surname);
    strcpy(driver[count].team, team);
    driver[count].hour = 0;
    driver[count].minute = 0;
    driver[count].second = 0;

    return 0;
}

//Return 0 if successful, otherwise 1.
int update_total_time(char *surname, int hour, int minute, int second, Driver *driver, int count){

    int i = 0;
    int check = 0;

    // Check if input is valid.
    if(hour < 0){
        printf("Hour cannot be negative.\n");
        return 1;
    }
    else if(minute < 0 || minute > 59){
        printf("Minute cannot be negative or greater than 59.\n");
        return 1;
    }
    else if(second < 0 || second > 59){
        printf("Second cannot be negative or greater than 59.\n");
        return 1;
    }

   // Checks if driver exists in database.
   while(i < count){
        if(strcmp(surname, driver[i].surname) == 0){
            check = 1; // Test to check if driver is in database.
            break;
        }
        else{
            i++;
        }
    }

    if(check == 0){ // Driver not in database.
        printf("Driver not found in databse\n");
        return 1;
    }

    // Adding the times to the driver.
    if(driver[i].second + second > 59){
        driver[i].minute += 1;
        driver[i].second = driver[i].second + second - 60;
    }
    else{
        driver[i].second += second;
    }

    if(driver[i].minute + minute > 59){
        driver[i].hour += 1;
        driver[i].minute = driver[i].minute + minute - 60;
    }
    else{
        driver[i].minute += minute;
    }

    driver[i].hour += hour;
    
    return 0;
}

// Calculates total time for a driver in seconds
int calculate_total_time(int hour, int minute, int second){
    int time;
    time = hour * 3600 + minute * 60 + second;
    return time;
}



/* Prints the stored drivers with their time, faster driver is printed higher up. Return 0 if successful, otherwise 1.
Prints the times either to stdout or to a file.*/
int print_race(Driver *driver, int count, FILE *filename){

    if(count == 0){
        printf("Database empty.\n");
        return 1;
    }
    Driver temp[1];
    // Compare driver times and check who are faster
    for(int i = 0; i < count; i++){
        for(int j = i + 1; j < count; j++){
            if(calculate_total_time(driver[i].hour, driver[i].minute, driver[i].second) > calculate_total_time(driver[j].hour, driver[j].minute, driver[j].second)){
                temp[0] = driver[i];
                driver[i] = driver[j];
                driver[j] = temp[0];
            }
        }
    }
    for(int i = 0; i < count; i++){
        fprintf(filename, "%s %s %d %d %d\n", driver[i].surname, driver[i].team, driver[i].hour, driver[i].minute, driver[i].second);
    }
    return 0;
}

// Loads drivers from a text file to database. Returns the new number of driver in databse if successful, otherwise -1.
int load_from_file(Driver *driver, const char *filename, int count){

    FILE *ptr;
	ptr = fopen(filename, "r");
    char input[1000];
    char surname[100];
    char team[100];

	if(ptr == NULL){
        printf("Cannot open file %s for reading.\n", filename);
		return -1;
	}
    /* Freeing the driver struct array to make room for the new struct array from file.*/
    for(int i = 0; i < count; i++){
        free(driver[i].surname);
        free(driver[i].team);
    }
    count = 0;
    while (fgets(input, sizeof(input), ptr) != NULL){ // Get one line of input from file.
        sscanf(input, "%s %s %d %d %d", surname, team, &driver[count].hour, &driver[count].minute, &driver[count].second);
        driver[count].surname = malloc(strlen(surname) + 1);
        driver[count].team = malloc(strlen(team) + 1);
        strcpy(driver[count].surname, surname);
        strcpy(driver[count].team, team);
        count++;
    }
    fclose(ptr);

    return count;
}