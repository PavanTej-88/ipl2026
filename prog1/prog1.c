/*The advantage of storing array of structures as binary files is that we can use fseek to go to specific record and get the record.
Write a program to store n records in binary file.
Write a function to get mth record and display.
Use fseek
Write a function to delete a record.
Deleting a record requires thinking.*/
#include<stdio.h>
typedef struct{
    char n[50];
    int id,m;
}Student;
void input(Student *,int);
void write_to_binary(Student *,int);
void get_record(Student *,int,int);
void delete(Student *,int,int);
int main(){
    int n,m,d;
    printf("Enter number of records: ");
    scanf("%d",&n);
    if(n<=0){
        printf("Invalid size\n");
        return 0;
    }
    Student s[n];
    input(s,n);
    write_to_binary(s,n);
    printf("Enter the number of record to print: ");
    scanf("%d",&m);
    get_record(s,n,m);
    printf("Enter the number of record to delete: ");
    scanf("%d",&d);
    delete(s,n,d);
    return 0;
}
void input(Student *s,int n){
    for(int i=0;i<n;i++){
        printf("Enter student %d name: ",i+1);
        scanf("%s",s[i].n);
        printf("Enter student %d id: ",i+1);
        scanf("%d",&s[i].id);
        printf("Enter student %d marks: ",i+1);
        scanf("%d",&s[i].m);
    }
}
void write_to_binary(Student *s,int n){
    FILE *ptr=fopen("students.bin","wb");
    fwrite(s,sizeof(Student),n,ptr);
    fclose(ptr);
}
void get_record(Student *s,int n,int m){
    Student temp;
    FILE *ptr=fopen("students.bin","rb");
    fseek(ptr,(sizeof(Student))*(m-1),SEEK_SET);
    fread(&temp,sizeof(Student),1,ptr);
    fclose(ptr);
    printf("mth record:\nName: %s\tId: %d\tMarks: %d\n",temp.n,temp.id,temp.m);
}
void delete(Student *s,int n,int d){
    Student s1[n];
    FILE *ptr=fopen("students.bin","wb");
    fwrite(s,sizeof(Student),d-1,ptr);
    fwrite(s+d,sizeof(Student),n-d,ptr);
    fclose(ptr);
    FILE *ptr2=fopen("students.bin","rb");
    fread(s1,sizeof(Student),n-1,ptr2);
    printf("Records after deleting:\n");
    for(int i=0;i<n-1;i++){
        printf("%d record:\nName: %s\tId: %d\tMarks: %d\n",i,s1[i].n,s1[i].id,s1[i].m);
    }
}






























