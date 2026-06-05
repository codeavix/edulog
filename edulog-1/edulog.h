#ifndef EDULOG_H
#define EDULOG_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#define  name_size 50
#define subject_count 4
typedef struct {
    int roll;
    char name[50];
    char dob[11];       
    char gender;       
    char batch[4];      
} Studentpersonal;
typedef struct {
    int roll;
    int bel[3];     
    int maths[3];
    int physics[3];
    int sdf[3];
} Marks;

typedef struct {
    int roll;
    float bel_total;
    float maths_total;
    float phy_total;
    float sdf_total;
    float bel_gpa;
    float maths_gpa;
    float phy_gpa;
    float sdf_gpa;
    char bel_grade[3];
    char maths_grade[3];
    char phy_grade[3];
    char sdf_grade[3];
    float percentage;
    float cgpa;
    int hasBack;
    char hasbackstr[5];
} Grade;

void showmainmenu(Studentpersonal s[],Marks m[],Grade g[],int*n,int*ma,int*ga);
int adminlogin(Studentpersonal s[], Marks m[], Grade g[], int *n, int *ma, int *ga);
void studentlogin(Studentpersonal s[],Grade g[],int n,int ga);
void studentmenu(int roll,Studentpersonal s[],Grade g[],int n,int ga);
void s_personal(int roll,int index, Studentpersonal s[], int n);
void loadStudents(Studentpersonal s[],int*n);
void loadMarks(Marks m[],int*ma);
void loadgrades(Grade g[],int*m);

void addStudent(Studentpersonal s[],Marks m[],int*n,int*ma);
void displayAllStudents(Studentpersonal s[],int n);
void searchstudent(Studentpersonal s[],Grade g[],int n);
void deletestudent(Studentpersonal s[],Marks m[],int*n,int*ma);
void modifyMarks(Studentpersonal s[],Marks m[],int n,int ma);
Marks inputMarks(int roll);
void calculateGrades(Studentpersonal students[],int n);
int assignGrade(float marks, float *allMarks, int n, char grade[3]);
void computeStats(float arr[], int n, float *mean, float *median, float *mode);
void classStats(Studentpersonal s[], Grade g[], int n, int ga);
void displayGrades(Studentpersonal students[],int n);
void s_report(int roll,int s_index, Grade g[], int ga, Studentpersonal s[], int n);
void topperslist(Studentpersonal s[], Grade g[], int n, int ga);
void passlist(Studentpersonal s[], Grade g[], int n, int ga);
void faillist(Studentpersonal s[], Grade g[], int n, int ga);
void subjecttoppers(Studentpersonal s[], Grade g[], int n, int ga);
void setColor(int color);

#endif