#include<stdio.h>
#include<ctype.h>
#include<string.h>
#define max_size 100

typedef enum{firstname,lastname,mobno}search_t;

void addentry();
void display(int index);
void searchF(char *key,search_t);
void searchL(char *key,search_t);
void searchM(char *key,search_t);
void stringToLower(char *str);
void SaveToFile();
void ReadFromFile();
void removeEntryMob(char *mobno); //void clear();
void removeEntryName(char *mobno);
void CompAndSort();
void EditByFirstName(char *key,search_t type);
void EditByMob(char *key,search_t type);

typedef struct{
char firstname[20];
char lastname[20];
char mobno[20];
}contact;

contact phonebook [max_size];
int currentsize = 0; //int index;

void clear()
{
    system("PAUSE");
    system("CLS");
}

int main()
{
    int choice,i;
    char selection[30],clearBuffer[2];
    while(1)
    {
        puts("phonebook app main menu");
        puts("enter your choice");
        puts("    1.Insert a new entry:");
        puts("    2.Display All Entry:");
        puts("    3.search By FirstName:");
        puts("    4.search By LastName:");
        puts("    5.search By Mobile No:");
        puts("    6.Edit By FirstName: ");
        puts("    7.Edit By Mobile No.: ");
        puts("    8.Delete a contact (by Mobile No):");
        puts("    9.Delete a contact (by First Name):");
        puts("    10.save Database:");
        puts("    11.Exit");

        printf("\nEnter your choice\t");
        scanf("%d",&choice);
        gets(clearBuffer); //fflush(stdin); for windows not for Linux because in Linux stdin buffer can't be flushed or cleared

        switch(choice)
        {
            case 1:
                addentry();
                clear();
                break;
            case 2:
                CompAndSort();
                printf("\n-------------------------------------------------------------------------\n\n");
                for(i=0;i<currentsize;i++)
                {
                    display(i);
                    printf("\n-------------------------------------------------------------------------\n\n");
                }
                clear();
                break;
            case 3:
                printf("Enter First Name To Search: ");
                gets(selection);
                searchF(selection,firstname);
                clear();
                break;
            case 4:
                printf("Enter Last Name To Search: ");
                gets(selection);
                searchL(selection,lastname);
                clear();
                break;
            case 5:
                printf("Enter mobile Number To Search: ");
                gets(selection);
                searchM(selection,mobno);
                clear();
                break;
            case 6:
                printf("Enter First Name: ");
                gets(selection);
                EditByFirstName(selection,firstname);
                clear();
                break;
            case 7:
                printf("Enter Mobile No.: ");
                gets(selection);
                EditByMob(selection,mobno);
                clear();
                break;
            case 8:
                printf("Enter Mobile No To Delete: ");
                gets(selection);
                removeEntryMob(selection);
                clear();
                break;
            case 9:
                printf("Enter Enter First Name To Delete: ");
                gets(selection);
                removeEntryName(selection);
                clear();
                break;
            case 10:
               SaveToFile();
               clear();
                break;
            case 11:
                return 0;
                break;
            default :
                printf("\nInvalid Choice!\n\n");
                break;
        }
    }
    return 0;
}

void addentry()
{
    int i;
    contact c;
    printf("ENTER FNAME: ");
    gets(c.firstname);
    for(i=0;c.firstname[i]!='\0';i++)
    {
        if(c.firstname[i]==' ')
        {
            c.firstname[i]='\0';
            break;
        }
    }
    printf("ENTER LNAME: ");
    gets(c.lastname);
    for(i=0;c.lastname[i]!='\0';i++)
    {
        if(c.lastname[i]==' ')
        {
            c.lastname[i]='\0';
            break;
        }
    }
    printf("ENTER MOBNO: ");
    gets(c.mobno);
    for(i=0;c.mobno[i]!='\0';i++)
    {
        if(c.mobno[i]==' ')
        {
            c.mobno[i]='\0';
            break;
        }
    }
    phonebook[currentsize] = c;
    ++currentsize;
}

void display(int index)
{
    contact c1 = phonebook[index];
    printf("FNAME IS : %s\n",c1.firstname);
    printf("LNAME IS : %s\n",c1.lastname);
    printf("MOBNO IS : %s\n",c1.mobno);
}

void stringToLower(char *str){
    int i;
    int len = strlen(str);
    for(i =0;i<len; i++)
        str[i] = tolower (str[i]);
}

void searchF(char *key,search_t type)
{
    stringToLower(key);
    int found = 0;
    int i;
    char content[40];

    if(type==firstname)
    {
        for(i = 0; i<currentsize; i++)
        {
            strcpy(content,phonebook[i].firstname);
            stringToLower(content);
            if(strcmp(content,key) == 0)
            {
                display(i);
                found =1;
            }
        }
    }
}

void searchL(char *key,search_t type)
{
    stringToLower(key);
    int found = 0;
    int i;
    char content[40];

    if(type==lastname)
    {
        for(i = 0;i<currentsize;i++)
        {
            strcpy(content,phonebook[i].lastname);
            stringToLower(content);
            if(strcmp(content,key) == 0)
            {
                display(i);
                found =1;
            }
        }
    }
}
void searchM(char *key,search_t type)
{
    stringToLower(key);
    int found = 0;
    int i;
    char content[40];
     if(type==mobno)
    {
        for(i = 0;i<currentsize;i++)
        {
            strcpy(content,phonebook[i].mobno);
            stringToLower(content);
            if(strcmp(content,key) == 0)
            {
                display(i);
                found =1;
            }

        }
    }
}
void SaveToFile()
{
    FILE *fp;
    fp = fopen("phonebook.db","wb");
    if(fp == NULL)
    {
        puts("Error:can't create Array_Database");
        return;
    }
    if(fwrite(&currentsize,sizeof(currentsize),1,fp) != 1)
    {
        puts("Error:can't save to file");
        return;
    }
    if(fwrite(phonebook,sizeof(phonebook),1,fp) != 1)
    {
        puts("Error:can't save to array_database");
        return;
    }
}

void ReadFromFile()
{
    FILE *fp;
    if((fp = fopen("phonebook.db","rb")) == NULL)
    {
        puts("Error:can't open Array_Database");
        return;
    }
    if(fread(&currentsize,sizeof(currentsize),1,fp) != 1)
    {
        puts("Error:can't read from file");
        return;
    }
    if(fread(phonebook,sizeof(phonebook),1,fp) != 1)
    {
        puts("Error:can't read from array_database");
        return;
    }

}

void removeEntryMob(char *mobno)
{
    int i,j;
    int count = 0;
    for(i=0;i<currentsize;i++)
    {

        if(strcmp(phonebook[i].mobno, mobno)==0)
        {
            for(j=i;j<currentsize-1;j++)
                phonebook[j]=phonebook[j+1];

            strcpy(phonebook[j].firstname,"");
            strcpy(phonebook[j].lastname,"");
            strcpy(phonebook[j].mobno,"");
            currentsize -=1;
            ++count;
        }
    }
    if(count == 0)
        puts("no entry deleted");
    else
        printf("%d entries deleted \n",count);
}

void removeEntryName(char *firstname)
{
    int i,j;
    int count = 0;
    for(i=0;i<currentsize;i++)
    {

        if(strcmp(phonebook[i].firstname, firstname)==0)
        {
            for(j=i;j<currentsize-1;j++)
                phonebook[j]=phonebook[j+1];

            strcpy(phonebook[j].firstname,"");
            strcpy(phonebook[j].lastname,"");
            strcpy(phonebook[j].mobno,"");
            currentsize -=1;
            ++count;
        }
    }
    if(count == 0)
        puts("no entry deleted");
    else
        printf("%d entries deleted \n",count);
}

void CompAndSort()
{
    int i,j,check;
    contact temp;
    for(i=0;i<=currentsize-2;i++)
    {
        for(j=0;j<=currentsize-2-i;j++)
        {
            check=strcmpi(phonebook[j].firstname,phonebook[j+1].firstname);
            if(check>0)
            {
                strcpy(temp.firstname,phonebook[j].firstname);
                strcpy(temp.lastname,phonebook[j].lastname);
                strcpy(temp.mobno,phonebook[j].mobno);

                strcpy(phonebook[j].firstname,phonebook[j+1].firstname);
                strcpy(phonebook[j].lastname,phonebook[j+1].lastname);
                strcpy(phonebook[j].mobno,phonebook[j+1].mobno);

                strcpy(phonebook[j+1].firstname,temp.firstname);
                strcpy(phonebook[j+1].lastname,temp.lastname);
                strcpy(phonebook[j+1].mobno,temp.mobno);
            }
        }
    }
}

void EditByFirstName(char *key,search_t type)
{
    stringToLower(key);
    int found = 0;
    int i;
    char content[40];

    if(type==firstname)
    {
        for(i = 0; i<currentsize; i++)
        {
            strcpy(content,phonebook[i].firstname);
            stringToLower(content);
            if(strcmp(content,key) == 0)
            {
                printf("Enter New Mobile No. ");
                gets(phonebook[i].mobno);
            }
        }
    }
}

void EditByMob(char *key,search_t type)
{
    stringToLower(key);
    int found = 0;
    int i;
    char content[40];

    if(type==mobno)
    {
        for(i = 0; i<currentsize; i++)
        {
            strcpy(content,phonebook[i].mobno);
            stringToLower(content);
            if(strcmp(content,key) == 0)
            {
                printf("Enter New FirstName: ");
                gets(phonebook[i].firstname);
            }
        }
    }
}
