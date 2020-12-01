#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

char filename[100];

struct student
{
    int rollno;
    char name[10];
    float per;
};
void insert()
{
    struct student s;
    char ask = 'Y';
    int nor, i = 0;
    int fp = open(filename, O_CREAT, S_IRUSR | S_IWUSR);
    close(fp);
    fp = open(filename, O_WRONLY | O_APPEND, S_IRUSR | S_IWUSR);
    printf("\nEnter number of records to be inserted: ");
    scanf("%d", &nor);
    while (i < nor)
    {
        printf("\nEnter information for record %d:", nor);
        printf("\nEnter roll number: ");
        scanf("%d", &s.rollno);
        printf("\nEnter name: ");
        scanf("%s", s.name);
        printf("\nEnter percentage: ");
        scanf("%f", &s.per);
        write(fp, &s, sizeof(s));

        i++;
    }
    close(fp);
}
void display()
{
    int fp, rd;
    struct student s;
    fp = open(filename, O_RDONLY, S_IRUSR);
    read(fp, &s, sizeof(s));
    printf("\nRoll No.\tName\tPercentage");
    do
    {
        printf("\n%d \t\t %s \t\t %f", s.rollno, s.name, s.per); //rd = read(fp, &s, sizeof(s));
    } while (read(fp, &s, sizeof(s)) > 0);
}
void modify()
{
    int fp1, fp2, rd, wr, r, flag = 0;
    struct student s;
    fp1 = open(filename, O_EXCL | O_RDONLY);
    fp2 = open("temp.txt", O_CREAT | O_WRONLY);
    printf("\nEnter roll number to modify: ");
    scanf("%d", &r);
    read(fp1, &s, sizeof(s));
    do
    {
        if (s.rollno == r)
        {
            flag = 1;
            printf("\nEnter modified roll number: ");
            scanf("%d", &s.rollno);
            printf("\nEnter modified name: ");
            scanf("%s", s.name);
            printf("\nEnter modified percentage: ");
            scanf("%f", &s.per);
        }
        write(fp2, &s, sizeof(s));
    } while (read(fp1, &s, sizeof(s)) > 0);
    if (flag)
    {
        printf("\nModification was carried out successfully!");
    }
    else
    {
        printf("\nModification was unsuccessful!");
    }
    close(fp1);
    close(fp2);
    remove(filename);
    rename("temp.txt", filename);
}
void delete ()
{
    int fp1, fp2, rd, wr, r, flag = 0;
    struct student s;
    fp1 = open(filename, O_EXCL | O_RDONLY);
    fp2 = open("temp.txt", O_CREAT | O_WRONLY);
    printf("\nEnter roll number to delete: ");
    scanf("%d", &r);
    read(fp1, &s, sizeof(s));
    do
    {
        if (s.rollno == r)
        {
            flag = 1;
            continue;
        }
        write(fp2, &s, sizeof(s));
    } while (read(fp1, &s, sizeof(s)) > 0);
    if (flag)
    {
        printf("\nDeletion was carried out successfully!");
    }
    else
    {
        printf("\nDeletion was unsuccessful!");
    }
    close(fp1);
    close(fp2);
    remove(filename);
    rename("temp.txt", filename);
}
int main()
{
    int choice;
    printf("\nEnter filename: ");
    scanf("%s", filename);
    while (1)
    {
        printf("\nChoose from the following: ");
        printf("\n1. Insert");
        printf("\n2. Display");
        printf("\n3. Modify");
        printf("\n4. Delete");
        printf("\n5. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            insert();
            break;
        case 2:
            display();
            break;
        case 3:
            modify();
            break;
        case 4:
            delete ();
            break;
        case 5:
            return 0;
        default:
            printf("\nEnter valid choice!");
        }
    }
    return 0;
}
