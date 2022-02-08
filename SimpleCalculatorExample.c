#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NUM 3
typedef struct {

    int number;
    char name[20];
    char surname [20];
    int grade;
}student;
int main()
{
    FILE *fptr = NULL;
    student ogr[NUM], tmp[NUM];
    char name1[20], name2[20];
    int max = -1; int min = 101; int toplam = 0; float average;
    int i;
    for(i=0; i<NUM; i++)
    {
        printf("Please enter the Name of %d. student: ",i+1);
        scanf("%s",ogr[i].name);
        printf("Please enter the Surname of %d. student: ",i+1);
        scanf("%s",ogr[i].surname);
        printf("Please enter the student number of %d. student: ",i+1);
        scanf("%d",&ogr[i].number);
        printf("Please enter the grade of %d. student: ",i+1);
        scanf("%d",&ogr[i].grade);
    }

    if((fptr =fopen("student.bin","wb")) == NULL)
    {
        printf("Error while opening the file!");
        return 1;
    }
    else
    {
        fwrite(ogr,sizeof(student),NUM,fptr);
    }
    fclose(fptr);

    if((fptr =fopen("student.bin","rb")) == NULL)
    {
        printf("Error while opening the file!");
        return 1;
    }
    else
    {
        fread(tmp,sizeof(student),NUM,fptr);
    }

    fclose(fptr);

    for(i=0; i<NUM; i++)
    {
        if(tmp[i].grade > max)
        {
            max = tmp[i].grade;
            strcpy(name1,tmp[i].name);
        }
        if(tmp[i].grade < min)
        {
            min = tmp[i].grade;
            strcpy(name2,tmp[i].name);
        }

        toplam += tmp[i].grade;
    }

    average = (float) toplam / NUM;

    printf("En yuksek notu alan ogrenci:\n");
    printf("   Adi  : %s\n", name1);
    printf("   Notu : %3d\n", max);
    printf("En dusuk notu alan ogrenci:\n");
    printf("   Adi  : %s\n", name2);
    printf("   Notu : %3d\n", min);

    return 0;
}
