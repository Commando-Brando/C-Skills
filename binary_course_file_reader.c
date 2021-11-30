#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

/*
    Brandon Muller - hsi501
    assign5.c is a program c file that allows a user to write to a file called courses.dat which can be provided otherwise the program makes it
    courses.dat holds course data for a CS department. each course is located at an offset based on a unique course number 
    assign5 allows user to create, update, read, and delete courses. It also allows finding courses based on searching for specific strings.
*/

// course struct 
typedef struct{
    char name[80];
    char schedule[4];
    unsigned hours;
    unsigned size;
    unsigned padding;
} COURSE;


// prints course info based on a course struct c and the course number, n
void printCourse(COURSE c, int n){
    printf("Course number:       %d\n", n);
    printf("Course name:         %s\n", c.name);
    printf("Scheduled days:      %s\n", c.schedule);
    printf("Credit  hours        %u\n", c.hours);
    printf("Enrolled students:   %u\n", c.size);
}

// function prints the main menu
void printMenu(){
    printf("Enter one of the following actions or type CTRL-D to exit.\n");   
    printf("C - create a new course record\n");
    printf("R - read an existing course record\n");
    printf("U - update an existing course record\n");
    printf("D - delete an existing course record\n");
    printf("F - search for a course based on a keyword\n");
}

// create will create a new course entry in courses.dat
void create(){
    FILE *f;
    char buffer[80];
    COURSE c; 
    int crsNum;
    
    printf("Enter a course number:\n");
    fgets(buffer, 80, stdin);
    sscanf(buffer, "%d", &crsNum);
    f = fopen("courses.dat", "rb+");
    fseek(f, (long)crsNum * sizeof(COURSE), SEEK_SET);
    fread(&c, (long)sizeof(COURSE), 1L, f);
    // checks to see if hours are greater than 0 if 0 then there is no course at location
    if(c.hours > 0){
        printf("Error: location has data\n");
        return;
    }
    printf("Enter a course name:\n");
    fgets(buffer, 80, stdin);
    sscanf(buffer, "%[^\n]", c.name);
    printf("Enter a course schedule (MWF or TR):\n");
    fgets(buffer, 80, stdin);
    sscanf(buffer, "%s", c.schedule);
    printf("Enter course credit hours:\n");
    fgets(buffer, 80, stdin);
    sscanf(buffer, "%u", &c.hours);
    printf("Enter student enrollment:\n");
    fgets(buffer, 80, stdin);
    sscanf(buffer, "%u", &c.size);
    fseek(f, (long)crsNum * sizeof(COURSE), SEEK_SET);
    fwrite(&c, sizeof(COURSE), 1L, f);
    fclose(f);
}

// reads and prints course info based on user inputted course number
void read(){
    COURSE c;
    char buffer[80];
    FILE *f;
    int crsNum;

    printf("Enter a course number:\n");
    fgets(buffer, 80, stdin);
    sscanf(buffer, "%d", &crsNum);
    //printf("%d\n", crsNum);
    f = fopen("courses.dat", "rb+");
    fseek(f, (long)crsNum * sizeof(COURSE), SEEK_SET);
    fread(&c, (long)sizeof(COURSE), 1L, f);
    if(c.hours < 1){
        printf("Error: course not found\n");
        return;
    }
    printCourse(c, crsNum);
    fclose(f);
}

// updates an existing course based on user inputted course number. blank entries retain old data
void update(){
    FILE *f;
    char buffer[80];
    COURSE c; 
    int crsNum;
    
    printf("Enter a course number:\n");
    fgets(buffer, 80, stdin);
    sscanf(buffer, "%d", &crsNum);
    f = fopen("courses.dat", "rb+");
    fseek(f, (long)crsNum * sizeof(COURSE), SEEK_SET);
    fread(&c, (long)sizeof(COURSE), 1L, f);
    if(c.hours == 0){
        printf("Error: course not found\n");
        return;
    }
    printf("Enter a course name:\n");
    fgets(buffer, 80, stdin);
    if(strcmp(buffer, "\n") != 0)
        sscanf(buffer, "%[^\n]", c.name);
    printf("Enter a course schedule (MWF or TR):\n");
    fgets(buffer, 80, stdin);
    if(strcmp(buffer, "\n") != 0)
        sscanf(buffer, "%s", c.schedule);
    printf("Enter course credit hours:\n");
    fgets(buffer, 80, stdin);
    if(strcmp(buffer, "\n") != 0)
        sscanf(buffer, "%u", &c.hours);
    printf("Enter student enrollment:\n");
    fgets(buffer, 80, stdin);
    if(strcmp(buffer, "\n") != 0)
        sscanf(buffer, "%u", &c.size);
    fseek(f, (long)crsNum * sizeof(COURSE), SEEK_SET);
    fwrite(&c, (long)sizeof(COURSE), 1L, f);
    fclose(f);
}

// deletes a course entry in the courses.dat file
void delete(){
    FILE *f;
    char buffer[80];
    COURSE c; 
    int crsNum;
    
    printf("Enter a course number:\n");
    fgets(buffer, 80, stdin);
    sscanf(buffer, "%d", &crsNum);
    f = fopen("courses.dat", "rb+");
    fseek(f, (long)crsNum * sizeof(COURSE), SEEK_SET);
    fread(&c, (long)sizeof(COURSE), 1L, f);
    if(c.hours == 0){
        printf("Error: course not found\n");
        return;
    }
    c.hours = 0;
    fseek(f, (long)crsNum * sizeof(COURSE), SEEK_SET);
    fwrite(&c, (long)sizeof(COURSE), 1L, f);
    fclose(f);
    printf("%d was successfully deleted\n", crsNum);
}

// takes in a string a returns an all uppercase version
char *upperCase(char *s){
    int i;

    for(i = 0; s[i] != '\0'; i++){
        if(s[i] >= 'a' && s[i] <= 'z'){
            s[i] = s[i] - 32;
        }
    }
    return s;
}

// searches all the records for a user inputted keyword and prints out any courses that match
void search(){
    char buffer[80];
    char keyword[80];
    COURSE c;
    FILE *f;
    int i = 0;
    char t[80];
    char t2[80];

    printf("Enter a phrase to search:\n");
    fgets(buffer, 80, stdin);
    sscanf(buffer, "%[^\n]", keyword);
    f = fopen("courses.dat", "rb+");

    while(fread(&c, sizeof(COURSE), 1L, f) == 1){
        if(c.hours > 0){
            strcpy(t, c.name);
            strcpy(t2, c.schedule);
            if(strstr(upperCase(t), upperCase(keyword)) != NULL){
                printf("%d   \"%s\"\n", i, c.name);
            }
            else if(strstr(upperCase(t2), upperCase(keyword)) != NULL){
                printf("%d   \"%s\"\n", i, c.schedule);
            }
            else if(c.hours == atoi(keyword)){
                printf("%d   \"%d\"\n", i, c.hours);
            }
            else if(c.size == atoi(keyword)){
                printf("%d   \"%d\"\n", i, c.size);
            }
        }
        i++;
    }
    fclose(f);
}


// main loops through an infinite while loop until user enter ctrl-d. it also checks to see if courses.dat exists and creates it otherwise
int main(){
    FILE *f;
    char buffer[50];
    char choice[50];
    printf("Assignment 5 created by Brandon Muller (hsi501)\n");
    
    // check to see if courses.dat exists otherwise create it
    f = fopen("courses.dat", "rb+");
    if(f == NULL){
        f = fopen("courses.dat", "wb+");
        fclose(f);
    }


    // infinite while loop that prints menu and calls functions to perform course actions
    while(1){
        printMenu();
        
        if(fgets(buffer, 50, stdin) == NULL)
            return 0;

        sscanf(buffer, "%s", choice);

        if(strcmp(choice, "c") == 0 || strcmp(choice, "C") == 0){
            create();
        }
        else if(strcmp(choice, "r") == 0 || strcmp(choice, "R") == 0){
            read();
        }
        else if(strcmp(choice, "u") == 0 || strcmp(choice, "U") == 0){
            update();
        }
        else if(strcmp(choice, "d") == 0 || strcmp(choice, "D") == 0){
            delete();
        }
        else if(strcmp(choice, "f") == 0 || strcmp(choice, "F") == 0){
            search();
        }
        else
            printf("ERROR: invalid option\n");
    }
}
