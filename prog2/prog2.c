/*Write a program that stores array of structures in ascii format in a file.
Write a function to create an array of seek positions of the beginning of the each record(structure) in the file
Write a function to display the record given the position.*/
#include <stdio.h>
#include <string.h>
#define MAX_RECORDS 100
struct Student {
    int id;
    char name[50];
    int age;
    float marks;
};
void writeRecords(struct Student arr[], int n) {
    FILE *fp = fopen("students.txt", "w");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }
    int i;
    for (i = 0; i < n; i++) {
        fprintf(fp, "%d %s %d %.2f\n", arr[i].id, arr[i].name, arr[i].age, arr[i].marks);
    }
    fclose(fp);
    printf("Records written to file.\n");
}
void buildSeekPositions(long positions[], int *count) {
    FILE *fp = fopen("students.txt", "r");
    if (fp == NULL) {
        printf("Error opening file!\n");    
        return;
    }
    char line[200];
    *count = 0;
    while (1) {
        long pos = ftell(fp);
        if (fgets(line, sizeof(line), fp) == NULL)
            break;
        positions[*count] = pos;
        (*count)++;
    }
    fclose(fp);
    printf("Found %d records, seek positions built.\n", *count);
}
void displayRecord(long position) {
    FILE *fp = fopen("students.txt", "r");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }
    fseek(fp, position, SEEK_SET);
    struct Student s;
    fscanf(fp, "%d %s %d %f", &s.id, s.name, &s.age, &s.marks);
    printf("ID    : %d\n", s.id);
    printf("Name  : %s\n", s.name);
    printf("Age   : %d\n", s.age);
    printf("Marks : %.2f\n", s.marks);
    fclose(fp);
}
int main() {
    struct Student arr[] = {
        {1, "name1",  20, 88.5},
        {2, "name2",    22, 76.0},
        {3, "name3",21, 91.3},
        {4, "name4",  19, 83.7}
    };
    int n = 4;
    writeRecords(arr, n);
    long positions[MAX_RECORDS];
    int count = 0;
    buildSeekPositions(positions, &count);
    int i;
    printf("\nSeek positions:\n");
    for (i = 0; i < count; i++) {
        printf("  Record %d -> byte %ld\n", i + 1, positions[i]);
    }
    printf("\nDisplaying record 3 using seek position:\n");
    displayRecord(positions[2]);
    printf("\nDisplaying record 1 using seek position:\n");
    displayRecord(positions[0]);
    return 0;
}