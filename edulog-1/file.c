#include<stdio.h>
int main(){
    FILE*fp,*fm;
    fp=fopen("studentpersonal.txt","w");
    if(!fp){
        printf("Error creating studentpersonal.txt\n");
        return 1;
    }
    fm=fopen("studentmarks.txt","w");
    if(!fm){
        printf("Error creating studentmarks.txt\n");
        fclose(fp);
        return 1;
    }
    int n;
    printf("How many student records do you want to enter? ");
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        int roll;
        char name[50];
        char dob[15];
        char gender;
        char batch[10];
        int bel1,bel2,bel3;
        int maths1,maths2,maths3;
        int phy1,phy2,phy3;
        int sdf1,sdf2,sdf3;
        printf("\nEnter details for student %d\n",i+1);
        printf("Roll number: ");
        scanf("%d",&roll);
        printf("Name: ");
        scanf(" %[^\n]",name);
        printf("Date of Birth(dd-mm-yyyy): ");
        scanf("%s",dob);
        printf("Gender(M/F): ");
        scanf(" %c",&gender);
        printf("Batch: ");
        scanf("%s",batch);
        fprintf(fp, "%d\t%s\t%s\t%c\t%s\n",roll,name,dob,gender,batch);
        printf("Enter BEL marks (Internal Midsem Endsem): ");
        scanf("%d %d %d",&bel1,&bel2,&bel3);
        printf("Enter Maths marks (Internal Midsem Endsem): ");
        scanf("%d %d %d",&maths1,&maths2,&maths3);
        printf("Enter Physics marks (Internal Midsem Endsem): ");
        scanf("%d %d %d",&phy1,&phy2,&phy3);
        printf("Enter SDF marks (Internal Midsem Endsem): ");
        scanf("%d %d %d",&sdf1,&sdf2,&sdf3);
        fprintf(fm,"%d\t%d %d %d\t%d %d %d\t%d %d %d\t%d %d %d\n",roll,bel1, bel2, bel3,
                    maths1, maths2, maths3,phy1, phy2, phy3,sdf1, sdf2, sdf3
        );
    }
    fclose(fp);
    fclose(fm);
    printf("\nAll records saved successfully.\n");
    return 0;
}
