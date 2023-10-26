#ifndef _PROJECT__H_
#define _PROJECT__H_

// A driver
typedef struct{
    char *surname; // Surname of the driver
    char *team; // Teamname of the driver
    int hour; // Total number of hours the driver has completed the race stages up to this point, which is a non-negative integer.
    int minute; //The driver’s stage completion minutes, which is an integer between 0 and 59 (inclusive).
    int second; // The driver’s stage completion seconds, which is an integer between 0 and 59 (inclusive).
} Driver;

int add_driver(char *surname, char *team, int count, Driver *driver);
int update_total_time(char *surname, int hour, int minute, int second, Driver *driver, int count);
int calculate_total_time(int hour, int minute, int second);
int print_race(Driver *driver, int count, FILE *filename);
int load_from_file(Driver *driver, const char *filename, int count);



#endif //! _PROJECT__H_