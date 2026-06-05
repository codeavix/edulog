#include"edulog.h"
void setColor(int color){
    switch(color){
        case 0:printf("\033[0m");break;
        case 1:printf("\033[34m");break;
        case 2:printf("\033[32m");break;
        case 3:printf("\033[36m");break;
        case 4:printf("\033[31m");break;
        case 5:printf("\033[35m");break;
        case 6:printf("\033[33m");break;
        case 7:printf("\033[37m");break;
        case 10:printf("\033[92m");break;
        case 11:printf("\033[96m");break;
        case 14:printf("\033[93m");break;
        default:printf("\033[0m");break;
    }
}
void showmainmenu(Studentpersonal s[],Marks m[],Grade g[],int*n,int*ma,int*ga){
    char input[10];
    int choice;
    while (1){
        printf("\n==============================\n");
        printf("      WELCOME TO EDULOG\n");
        printf("==============================\n");
        printf("1.Admin Login\n");
        printf("2.Student Login\n");
        printf("3.Exit\n");
        printf("==============================\n");
        printf("Enter your choice: ");
        scanf("%d",&choice);
        switch(choice){
            case 1:
                adminlogin(s,m,g,n,ma,ga);
                break;
            case 2:
                studentlogin(s,g,*n,*ga);
                break;
            case 3:
                printf("\nThank you for using EduLog!\n");
                return;
            default:
                printf("\nInvalid choice! Please enter 1, 2, or 3.\n");
                break;
            }
        
    }
}

int adminlogin(Studentpersonal s[],Marks m[],Grade g[],int*n,int*ma,int*ga){
    char username[20],password[20];
    int choice;
    printf("\n------ ADMIN LOGIN ------\n");
    printf("Enter username: ");
    scanf("%s",username);
    printf("Enter password: ");
    scanf("%s",password);
    if(strcmp(username,"admin")==0&&strcmp(password,"1234")==0){
        printf("\nLogin successful!\n");
        while(1){
            printf("\n---- ADMIN MENU ----\n");
            printf("1.Display all students\n");
            printf("2.Search student\n");
            printf("3.Add Student\n");
            printf("4.Delete Student\n");
            printf("5.Modify marks\n");
            printf("6.Get toppers list\n");
            printf("7.Get Pass list\n");
            printf("8.Get fail list\n");
            printf("9.Get Subject toppers list\n");
            printf("10.show class stats\n");
            printf("11.Exit\n");
            printf("Enter your choice:");
            scanf("%d",&choice);
            switch(choice)
            {
            case 1:
                displayAllStudents(s,*n);
                break;
            case 2:
                searchstudent(s,g,*n);
                break;
            case 3:
                addStudent(s,m,n,ma);
                break;
            case 4:
                deletestudent(s,m,n,ma);
                break;
            case 5:
                modifyMarks(s,m,*n,*ma);
                break;
            case 6:
                topperslist(s,g,*n,*ga);
                break;
            case 7:
                passlist(s,g,*n,*ga);
                break;
            case 8:
                faillist(s,g,*n,*ga);
                break;
            case 9:
                subjecttoppers(s,g,*n,*ga);
                break;
            case 10:
                classStats(s,g,*n,*ga);
                break;
            case 11:
                printf("\nThank you for using EduLog!\n");
                return 0;
            default:
                printf("\nInvalid choice!\n");
                break;
    
            }
        }     
    }else{
        printf("\nInvalid credentials!\n");
        return 0;
    }
}
 
void studentlogin(Studentpersonal s[],Grade g[],int n,int ga){
    int roll;
    char dob[11];
    int found=0;
    int index=-1;
    printf("\n=========================\n");
    printf("       STUDENT LOGIN\n");
    printf("=========================\n");
    printf("Enter Enrollment Number: ");
    scanf("%d",&roll);
    printf("Enter DOB (dd-mm-yyyy): ");
    scanf("%s",dob);
    for(int i=0;i<n;i++){
        if (s[i].roll==roll&&strcmp(s[i].dob,dob)==0){
            found=1;
            index=i;
            break;
        }
    }
    if(!found){
        printf("\nInvalid roll number or password\n");
        studentlogin(s,g,n,ga);
    }
    printf("\nLogin Successful! Welcome,%s\n", s[index].name);
    studentmenu(roll,s,g,n,ga);
}
void studentmenu(int roll,Studentpersonal s[],Grade g[],int n,int ga)
{
    int choice;
    int index=-1;
    for(int i=0;i<n;i++){
        if(s[i].roll==roll){
            index=i;
            break;
        }
    }
    if(index==-1){
        printf("Student record not found.\n");
        return;
    }
    printf("===========================================================\n");
    printf("\t\t    STUDENT MENU\n");
    printf("===========================================================\n");
    printf("\n1.personal details");
    printf("\n2.Report card");
    printf("\n3.Topper's list");
    printf("\n4.Pass list");
    printf("\n5.Fail list");
    printf("\n6.EXIT\n");
    while(1){
        printf("Enter your choice : ");
        scanf("%d",&choice);
        switch(choice){
            case 1:
            s_personal(roll,index,s,n);
                break;
            case 2:
            s_report(roll,index,g,ga,s,n);
                break;
            case 3:
            topperslist(s,g,n,ga);
                break;
            case 4:
            passlist(s,g,n,ga);
                break;
            case 5:
            subjecttoppers(s,g,n,ga);
                break;
            case 6:
            printf("\nExiting...\n");
                return;
            default:
            printf("\nInvalid choice! Choose between 1–6.\n");
                break;
        }
    }
}

void s_personal(int roll,int index,Studentpersonal s[],int n)
{
    printf("\n===========================================================\n");
    printf("\t\t  PERSONAL DETAILS\n");
    printf("===========================================================\n");
    printf("Roll Number: %d\n",s[index].roll);
    printf("Name: %s\n",s[index].name);
    printf("DOB: %s\n",s[index].dob);
    printf("Gender: %c\n",s[index].gender);
    printf("Batch: %s\n",s[index].batch);
    printf("===========================================================\n");
}
void loadStudents(Studentpersonal s[],int*n){
    FILE*fp=fopen("studentpersonal.txt","r");
    if(!fp){
        printf("Could not open file.\n");
        return;
    }
    *n=0;
    while(fscanf(fp,"%d\t%[^\t]\t%10s\t%c\t%3s",&s[*n].roll,s[*n].name,s[*n].dob,&s[*n].gender,s[*n].batch)==5){
        (*n)++;
    }
    fclose(fp);
}
void loadMarks(Marks m[],int *ma){

    FILE*fm=fopen("studentmarks.txt","r");
    if(!fm){
        printf("Could not open studentmarks.txt\n");
        return;
    }

    *ma=0;

    while(fscanf(fm,"%d %d %d %d\t%d %d %d\t%d %d %d\t%d %d %d\n",&m[*ma].roll,&m[*ma].bel[0], &m[*ma].bel[1], &m[*ma].bel[2],
                     &m[*ma].maths[0], &m[*ma].maths[1], &m[*ma].maths[2],&m[*ma].physics[0], &m[*ma].physics[1], &m[*ma].physics[2],
                     &m[*ma].sdf[0], &m[*ma].sdf[1], &m[*ma].sdf[2]) == 13)
    {
        (*ma)++;
    }

    fclose(fm);
}
void loadgrades(Grade g[],int*ga){
    FILE*fp=fopen("studentgrades.txt","r");
    if(!fp){
        printf("Could not open studentgrades.txt\n");
        *ga=0;
        return;
    }
    char grade1[5],grade2[5],grade3[5],grade4[5],status[10];
    *ga=0;
    while(fscanf(fp,"%d %f %s %f %s %f %s %f %s %f %s",
                    &g[*ga].roll,&g[*ga].bel_total,grade1,&g[*ga].maths_total,grade2,&g[*ga].phy_total,grade3,&g[*ga].sdf_total,grade4,&g[*ga].cgpa,status)==11)
    {
        strcpy(g[*ga].bel_grade,grade1);
        strcpy(g[*ga].maths_grade,grade2);
        strcpy(g[*ga].phy_grade,grade3);
        strcpy(g[*ga].sdf_grade,grade4);
        g[*ga].hasBack=(strcmp(status,"BACK")==0);
        (*ga)++;
    }
    fclose(fp);
}
void addStudent(Studentpersonal s[],Marks m[],int*n,int*ma){
    FILE *fp=fopen("studentpersonal.txt", "a"); 
    if (fp==NULL) {
        printf("Error opening file!\n");
        return;
    }
    
    printf("\nRoll no.   : ");
        scanf("%d",&s[*n].roll);
        printf("Name       : ");
        scanf(" %[^\n]s",s[*n].name);
        printf("DOB        : ");
        scanf("%s",s[*n].dob);
        printf("Gender     : ");
        scanf(" %c",&s[*n].gender);
        printf("Batch      : ");
        scanf("%s",s[*n].batch);
        fprintf(fp,"%d\t %s\t %s\t %c\t %s\n",s[*n].roll,s[*n].name,s[*n].dob,s[*n].gender,s[*n].batch);
    fclose(fp);
    int roll=s[*n].roll;
    (*n)++;
    m[*ma]=inputMarks(roll);
    (*ma)++;
    calculateGrades(s,*n);
    printf("Student added successfully\n");
    
}
void displayAllStudents(Studentpersonal s[],int n){
    printf("\nCurrent Students:\n");
    printf("Roll No.\t|Name\t\t|Date of birth\t|Gender\t|Batch\t|\n");
    for (int i=0;i<n;i++) {
        printf("%d\t\t|%s\t|%s\t|%c\t|%s\t|\n",s[i].roll,s[i].name,s[i].dob,s[i].gender,s[i].batch);
    }

}
void searchstudent(Studentpersonal s[],Grade g[],int n) {
    int roll;
    printf("Enter roll no. to search:");
    scanf("%d",&roll);
    int si=-1,gi=-1;
    for (int i=0;i<n;i++){
        if(s[i].roll==roll){
            si=i;
            break;
        }
    }
    for(int i=0;i<n;i++){
        if(g[i].roll==roll){
            gi=i;
            break;
        }
    }
    if(si==-1||gi==-1){
        printf("No record found for Roll No %d\n",roll);
        return;
    }
    printf("\nRecord Found:\n");
    printf("%d\t%s\t%s\t%c\t%s\n",s[si].roll, s[si].name, s[si].dob, s[si].gender, s[si].batch);
    printf("BEL marks:- %f\n",g[gi].bel_total);
    printf("Maths marks:- %f\n",g[gi].maths_total);
    printf("Physics marks:- %f\n",g[gi].phy_total);
    printf("SDF marks:- %f\n",g[gi].sdf_total);
    printf("CGPA:-%.2f\n",g[gi].cgpa);
    printf("Status:-%s\n",g[gi].hasBack?"BACK":"PASS");
}
void deletestudent(Studentpersonal s[],Marks m[],int*n,int*ma){
    int roll;
    printf("Enter roll no. to delete:-");
    scanf("%d",&roll);
    int found=0;
    int found1=0;
    for (int i=0;i<*n;i++) {
        if (s[i].roll==roll) {
            for (int j=i;j<*n-1;j++) {
                s[j] = s[j + 1];
            }
            (*n)--;
            found=1;
            break;
        }
    }
    for (int i=0;i<*ma;i++) {
        if (m[i].roll==roll) {
            for (int j=i;j<*ma-1;j++) {
                m[j] = m[j + 1];
            }
            (*ma)--;
            found1=1;
            break;
        }
    }
    if(found){
        FILE *fp=fopen("studentpersonal.txt","w");
        for (int i=0;i<*n;i++) {
            fprintf(fp,"%d\t%s\t%s\t%c\t%s\n",s[i].roll,s[i].name,s[i].dob,s[i].gender,s[i].batch);
        }
        fclose(fp);
        printf("Record deleted successfully.\n");
    } else {
        printf("Record not found!\n");
    }
    if(found1){
        FILE *fm=fopen("studentmarks.txt","w");
        for (int i=0;i<*ma;i++) {
            fprintf(fm,"%d\t%d %d %d\t%d %d %d\t%d %d %d\t%d %d %d\n",m[i].roll,m[i].bel[0],m[i].bel[1],m[i].bel[2],
                        m[i].maths[0],m[i].maths[1],m[i].maths[2],m[i].physics[0],m[i].physics[1],m[i].physics[2],
                        m[i].sdf[0],m[i].sdf[1],m[i].sdf[2]);
        }
        fclose(fm);
        printf("marks deleted successfully.\n");
    } else {
        printf("marks not found!\n");
    }
    calculateGrades(s,*n);
}
void modifyMarks(Studentpersonal s[],Marks m[],int n,int ma){
    int roll;
    printf("Enter roll number: ");
    scanf("%d",&roll);
    int index=-1;
    for(int i=0;i<ma;i++){
        if(m[i].roll==roll){
            index=i;
            break;
        }
    }
    if(index==-1){
        printf("No marks record found for this roll.\n");
        return;
    }
    printf("Modifying marks for roll no. %d\n",roll);
    printf("Enter BEL marks(Internal Midsem Endsem): ");
    scanf("%d %d %d",&m[index].bel[0],&m[index].bel[1],&m[index].bel[2]);
    printf("Enter Maths marks(Internal Midsem Endsem): ");
    scanf("%d %d %d",&m[index].maths[0],&m[index].maths[1],&m[index].maths[2]);

    printf("Enter Physics marks(Internal Midsem Endsem): ");
    scanf("%d %d %d",&m[index].physics[0],&m[index].physics[1],&m[index].physics[2]);

    printf("Enter SDF marks(Internal Midsem Endsem): ");
    scanf("%d %d %d",&m[index].sdf[0],&m[index].sdf[1],&m[index].sdf[2]);
    FILE *fm=fopen("studentmarks.txt","w");
    if(!fm){
        printf("Error opening studentmarks.txt for writing!\n");
        return;
    }
    for(int i=0;i<ma;i++){
        fprintf(fm,"%d\t%d %d %d\t%d %d %d\t%d %d %d\t%d %d %d\n",m[i].roll,
                m[i].bel[0],m[i].bel[1],m[i].bel[2],
                m[i].maths[0],m[i].maths[1],m[i].maths[2],
                m[i].physics[0],m[i].physics[1],m[i].physics[2],
                m[i].sdf[0],m[i].sdf[1],m[i].sdf[2]);
    }
    fclose(fm);
    calculateGrades(s,n);
    printf("Marks updated successfully.\n");
}

Marks inputMarks(int roll) {
    FILE *fm=fopen("studentmarks.txt", "a");
    Marks m;
    if (fm==NULL) {
        printf("Error opening file!\n");
        return m;
    }
    m.roll=roll;

    printf("\nEnter marks for BEL (Internal, Midsem, Endsem): ");
    scanf("%d %d %d",&m.bel[0],&m.bel[1],&m.bel[2]);

    printf("Enter marks for Maths (Internal, Midsem, Endsem): ");
    scanf("%d %d %d",&m.maths[0],&m.maths[1],&m.maths[2]);

    printf("Enter marks for Physics (Internal, Midsem, Endsem): ");
    scanf("%d %d %d",&m.physics[0],&m.physics[1],&m.physics[2]);

    printf("Enter marks for SDF (Internal, Midsem, Endsem): ");
    scanf("%d %d %d",&m.sdf[0],&m.sdf[1],&m.sdf[2]);

    fprintf(fm, "\n%d\t%d %d %d\t%d %d %d\t%d %d %d\t%d %d %d\n",
            m.roll,
            m.bel[0],m.bel[1],m.bel[2],
            m.maths[0],m.maths[1],m.maths[2],
            m.physics[0],m.physics[1],m.physics[2],
            m.sdf[0],m.sdf[1],m.sdf[2]);

    fclose(fm);
    printf("Marks added\n");
    return m;
}

void computeStats(float arr[],int n,float *mean,float *median,float *mode)
{
    float sum=0;
    for(int i=0;i<n;i++)
        sum+=arr[i];
    *mean=sum/n;
    float temp[200];
    for(int i=0;i<n;i++)
        temp[i]=arr[i];
    //sorting-mode/median
    for(int i=0;i<n-1;i++)
        for(int j=i+1;j<n;j++)
            if(temp[i]>temp[j]){
                float t=temp[i];
                temp[i]=temp[j];
                temp[j]=t;
            }
    if (n%2==1)
        *median=temp[n/2];
    else
        *median=(temp[n/2-1]+temp[n/2])/2.0;
    int maxCount=0;
    *mode=-1;

    for (int i=0;i<n;i++) {
        int count=1;
        for (int j=i+1;j<n;j++)
            if (temp[j]==temp[i])
                count++;

        if (count>maxCount&&count>1) {
            maxCount=count;
            *mode=temp[i];
        }
    }
}
void classStats(Studentpersonal s[],Grade g[],int n,int ga){
    float bel[100],maths[100],phy[100],sdf[100];
    for (int i=0;i<ga;i++) {
        bel[i]=g[i].bel_total;
        maths[i]=g[i].maths_total;
        phy[i]=g[i].phy_total;
        sdf[i]=g[i].sdf_total;
    }
    float mean,median,mode;
    printf("\nCLASS STATISTICS\n");
    computeStats(bel,ga,&mean,&median,&mode);
    printf("\nBEL:\n");
    printf("Mean: %.2f\n",mean);
    printf("Median: %.2f\n",median);
    printf("Mode: %.2f\n",mode);
    computeStats(maths,ga,&mean,&median,&mode);
    printf("\nMaths:\n");
    printf("Mean: %.2f\n",mean);
    printf("Median: %.2f\n",median);
    printf("Mode: %.2f\n", mode);
    computeStats(phy,ga,&mean,&median,&mode);
    printf("\nPhysics:\n");
    printf("Mean: %.2f\n",mean);
    printf("Median: %.2f\n",median);
    printf("Mode: %.2f\n", mode);
    computeStats(sdf,ga,&mean,&median,&mode);
    printf("\nSDF:\n");
    printf("Mean: %.2f\n",mean);
    printf("Median: %.2f\n",median);
    printf("Mode: %.2f\n",mode);
    printf("\n--------------------\n");
}



int assignGrade(float marks,float *Marks,int n,char grade[3])
{
    float sorted[200];
    for(int i=0;i<n;i++)
        sorted[i]=Marks[i];

    for(int i=0;i<n-1;i++)
        for(int j=i+1;j<n;j++)
            if(sorted[i]>sorted[j]) {
                float t=sorted[i];
                sorted[i]=sorted[j];
                sorted[j]=t;
            }
    int below=0;
    for(int i=0;i<n;i++)
        if(sorted[i]<=marks)
            below++;
    float percentile=(float)below/n*100.0;
    if(marks<40){
        strcpy(grade,"F");
        return 0;
    }
    if(percentile>=90){
        strcpy(grade,"A+");
        return 10; 
    }
    else if(percentile>=75){
        strcpy(grade,"A");
        return 9;
    }
    else if(percentile>=55){
        strcpy(grade,"B+");
        return 8;
    }
    else if(percentile>=35){
        strcpy(grade,"B");
        return 7; 
    }
    else if(percentile>=20){
        strcpy(grade,"C+");
        return 6;
    }
    else if(percentile>=10){
        strcpy(grade,"C");
        return 5;
    }
    else if(percentile>=5){
        strcpy(grade,"D");
        return 4; 
    }
    else{strcpy(grade,"E");
        return 3;
    }
}
void calculateGrades(Studentpersonal students[],int n){
    FILE*fm=fopen("studentmarks.txt","r");
    FILE*fg=fopen("studentgrades.txt","w");
    if(!fm||!fg){
        printf("Error opening marks/grades file.\n");
        return;
    }
    int count=0;
    Marks m[100];
    Grade g[100];

    while(fscanf(fm,"%d %d %d %d\t%d %d %d\t%d %d %d\t%d %d %d\n",&m[count].roll,
                  &m[count].bel[0],&m[count].bel[1],&m[count].bel[2],
                  &m[count].maths[0],&m[count].maths[1],&m[count].maths[2],
                  &m[count].physics[0],&m[count].physics[1],&m[count].physics[2],
                  &m[count].sdf[0],&m[count].sdf[1],&m[count].sdf[2])==13)
    {
        g[count].roll=m[count].roll;
        g[count].bel_total=m[count].bel[0]+m[count].bel[1]+m[count].bel[2];
        g[count].maths_total=m[count].maths[0]+m[count].maths[1]+m[count].maths[2];
        g[count].phy_total=m[count].physics[0]+m[count].physics[1]+m[count].physics[2];
        g[count].sdf_total=m[count].sdf[0]+m[count].sdf[1]+m[count].sdf[2];
        count++;
    }
    fclose(fm);
    if(count==0){
        printf("No records found.\n");
        fclose(fg);
        return;
    }
    float bel_scores[100],maths_scores[100],phy_scores[100],sdf_scores[100];

    for(int i=0;i<count;i++){
        bel_scores[i]=g[i].bel_total;
        maths_scores[i]=g[i].maths_total;
        phy_scores[i]=g[i].phy_total;
        sdf_scores[i]=g[i].sdf_total;
    }
    for(int i=0;i<count;i++){
        g[i].bel_gpa=assignGrade(g[i].bel_total,bel_scores,n, g[i].bel_grade);
        g[i].maths_gpa=assignGrade(g[i].maths_total,maths_scores,n, g[i].maths_grade);
        g[i].phy_gpa=assignGrade(g[i].phy_total,phy_scores,n,g[i].phy_grade);
        g[i].sdf_gpa=assignGrade(g[i].sdf_total,sdf_scores,n,g[i].sdf_grade);

        g[i].cgpa=(g[i].bel_gpa+g[i].maths_gpa+g[i].phy_gpa+g[i].sdf_gpa)/4.0;

        g[i].hasBack=(strcmp(g[i].bel_grade,"F")==0||strcmp(g[i].maths_grade,"F")==0||strcmp(g[i].phy_grade,"F")==0||strcmp(g[i].sdf_grade,"F")==0)?1:0;
        fprintf(fg,"%d\t%.1f\t%s\t%.1f\t%s\t%.1f\t%s\t%.1f\t%s\t%.2f\t%s\n",g[i].roll,g[i].bel_total,g[i].bel_grade,g[i].maths_total,g[i].maths_grade,
                    g[i].phy_total,g[i].phy_grade,g[i].sdf_total,g[i].sdf_grade,g[i].cgpa,g[i].hasBack ?"BACK" :"PASS");
    }
    fclose(fg);

}
void s_report(int roll,int s_index,Grade g[],int ga,Studentpersonal s[],int n)
{
    int g_index=-1;
    for (int i=0;i<ga;i++) {
        if (g[i].roll==roll) {
            g_index=i;
            break;
        }
    }
    if (g_index==-1) {
        setColor(4);
        printf("\nError: No grade record found for this student.\n");
        setColor(7);
        return;
    }
    setColor(11);
    printf("\n===========================================================\n");
    printf("                      REPORT CARD\n");
    printf("===========================================================\n");
    setColor(6);
    printf("ENROLLMENT NUMBER  : ");
    setColor(10);
    printf("%d\n", s[s_index].roll);

    setColor(6);
    printf("NAME               : ");
    setColor(10);
    printf("%s\n", s[s_index].name);

    setColor(6);
    printf("DATE OF BIRTH      : ");
    setColor(10);
    printf("%s\n", s[s_index].dob);

    setColor(6);
    printf("GENDER             : ");
    setColor(10);
    printf("%c\n", s[s_index].gender);

    setColor(6);
    printf("BATCH              : ");
    setColor(10);
    printf("%s\n", s[s_index].batch);
    setColor(7);
    printf("-----------------------------------------------------------\n");
    setColor(11);
    printf("%-15s %-10s %-10s\n","Subject","Marks","Grade");
    setColor(7);
    printf("-----------------------------------------------------------\n");

    setColor(6);
    printf("%-15s ","BEL");
    setColor(10);
    printf("%-10.1f ",g[g_index].bel_total);
    setColor(3);
    printf("%-10s\n",g[g_index].bel_grade);

    setColor(6);
    printf("%-15s ","Maths");
    setColor(10);
    printf("%-10.1f ",g[g_index].maths_total);
    setColor(3);
    printf("%-10s\n",g[g_index].maths_grade);

    setColor(6);
    printf("%-15s ","Physics");
    setColor(10);
    printf("%-10.1f ",g[g_index].phy_total);
    setColor(3);
    printf("%-10s\n",g[g_index].phy_grade);

    setColor(6);
    printf("%-15s ","SDF");
    setColor(10);
    printf("%-10.1f ",g[g_index].sdf_total);
    setColor(3);
    printf("%-10s\n",g[g_index].sdf_grade);
    setColor(7);
    printf("-----------------------------------------------------------\n");
    setColor(11);
    printf("CGPA : ");
    setColor(10);
    printf("%.2f\t",g[g_index].cgpa);
    setColor(11);
    printf("STATUS : ");
    if (g[g_index].hasBack)
        setColor(4),printf("BACK\n");
    else
        setColor(10),printf("PASS\n");
    setColor(7);
    printf("-----------------------------------------------------------\n");
}
void topperslist(Studentpersonal s[],Grade g[],int n,int ga){
    Grade temp[100];
    for (int i=0;i<ga;i++) {
        temp[i]=g[i];
    }
    for (int i=0;i<ga-1;i++) {
        for (int j=i+1;j<ga;j++) {
            if (temp[i].cgpa<temp[j].cgpa) {
                Grade t=temp[i];
                temp[i]=temp[j];
                temp[j]=t;
            }
        }
    }
    setColor(11);
    printf("\n===================== TOPPERS LIST =====================\n");
    setColor(7);
    printf("%-8s %-20s %-12s %-8s %-5s\n","Roll","Name","DOB","Batch","CGPA");
    printf("---------------------------------------------------------\n");
    int any=0;
    for(int i=0;i<ga;i++){
        if(temp[i].cgpa>8.5){
            int in=-1;
            for(int j=0;j<n;j++){
                if(s[j].roll==temp[i].roll){
                    in=j;
                    break;
                }
            }
            setColor(10);
            printf("%-8d %-20s %-12s %-8s %-5.2f\n",temp[i].roll,s[in].name,s[in].dob,s[in].batch,temp[i].cgpa);
            any=1;
        }
    }
    if(!any){
        setColor(4);
        printf("\nNo toppers with CGPA > 8.5 found.\n");
    }

    setColor(7);
    printf("---------------------------------------------------------\n");
}
void passlist(Studentpersonal s[],Grade g[],int n,int ga){
    setColor(11);
    printf("\n====================== PASS LIST ======================\n");
    setColor(7);
    printf("%-8s %-20s %-12s %-8s %-5s\n",
           "Roll", "Name", "DOB", "Batch", "CGPA");
    printf("--------------------------------------------------------\n");

    int any=0;

    for(int i=0;i<ga;i++){
        if(!g[i].hasBack){
            int in=-1;
            for(int j=0;j<n;j++){
                if(s[j].roll==g[i].roll){
                    in=j;
                    break;
                }
            }
            setColor(10);
            printf("%-8d %-20s %-12s %-8s %-5.2f\n",g[i].roll,s[in].name,s[in].dob,s[in].batch,g[i].cgpa);
            any=1;
        }
    }
    if(!any){
        setColor(4);
        printf("\nNo students PASSed.\n");
    }

    setColor(7);
    printf("--------------------------------------------------------\n");
}

void faillist(Studentpersonal s[],Grade g[],int n,int ga)
{
    setColor(11);
    printf("\n===================== FAIL LIST (BACK) =====================\n");
    setColor(7);
    printf("%-8s %-20s %-12s %-8s %-5s\n", "Roll", "Name", "DOB", "Batch", "CGPA");
    printf("------------------------------------------------------------\n");
    int any=0;
    for(int i=0;i<ga;i++){

        if(g[i].hasBack){
            int in=-1;
            for (int j=0;j<n;j++){
                if (s[j].roll==g[i].roll){
                    in=j;
                    break;
                }
            }
            setColor(4);
            printf("%-8d %-20s %-12s %-8s %-5.2f\n",g[i].roll,s[in].name,s[in].dob,s[in].batch,g[i].cgpa);
            any=1;
        }
    }
    if(!any){
        setColor(10);
        printf("\nNo students with BACK.\n");
    }
    setColor(7);
    printf("------------------------------------------------------------\n");
}
void subjecttoppers(Studentpersonal s[],Grade g[],int n,int ga)
{
    if(ga==0){
        setColor(4);
        printf("\nNo grade data available.\n");
        setColor(7);
        return;
    }
    int beltop=0,mathtop=0,phytop=0,sdftop=0;

    for(int i=1;i<ga;i++){
        if(g[i].bel_total>g[beltop].bel_total)beltop=i;
        if(g[i].maths_total>g[mathtop].maths_total)mathtop=i;
        if(g[i].phy_total>g[phytop].phy_total)phytop=i;
        if(g[i].sdf_total>g[sdftop].sdf_total)sdftop=i;
    }
    setColor(11);
    printf("\n====================== SUBJECT TOPPERS ======================\n");
    setColor(7);
    printf("%-12s %-8s %-20s %-12s %-8s %-5s\n","Subject","Roll","Name","DOB","Batch","Marks");
    printf("---------------------------------------------------------------\n");
    for(int j=0;j<n;j++){
        if(s[j].roll==g[beltop].roll){
            setColor(10);
            printf("%-12s %-8d %-20s %-12s %-8s %-5.1f\n","BEL",
                    s[j].roll,s[j].name,s[j].dob,s[j].batch,g[beltop].bel_total);
            break;
        }
    }
    for(int j=0;j<n;j++){
        if(s[j].roll==g[mathtop].roll){
            setColor(10);
            printf("%-12s %-8d %-20s %-12s %-8s %-5.1f\n","Maths",
                    s[j].roll,s[j].name,s[j].dob,s[j].batch,g[mathtop].maths_total);
            break;
        }
    }

    for(int j=0;j<n;j++){
        if(s[j].roll==g[phytop].roll){
            setColor(10);
            printf("%-12s %-8d %-20s %-12s %-8s %-5.1f\n","Physics",
                    s[j].roll,s[j].name,s[j].dob,s[j].batch,g[phytop].phy_total);
            break;
        }
    }
    for(int j=0;j<n;j++){
        if(s[j].roll==g[sdftop].roll){
            setColor(10);
            printf("%-12s %-8d %-20s %-12s %-8s %-5.1f\n","SDF",
                    s[j].roll,s[j].name,s[j].dob,s[j].batch,g[sdftop].sdf_total);
            break;
        }
    }
    setColor(7);
    printf("---------------------------------------------------------------\n");
}
int main(){
    Studentpersonal s[100];
    Marks m[100];
    Grade g[100];
    int n,ga,ma;

    loadStudents(s,&n);
    loadMarks(m,&ma);
    calculateGrades(s,n);
    loadgrades(g,&ga);
    showmainmenu(s,m,g,&n,&ma,&ga);
    return 0;
}






    

    


    





