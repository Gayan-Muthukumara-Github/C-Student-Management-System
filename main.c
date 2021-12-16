#include <stdio.h>
#include <time.h>
#include <string.h>

#define FILE_NAME1  "password.bin"
#define FILE_NAME2  "student.bin"

#define MAX_USER_NAME 30
#define MAX_PASSWORD  20
#define MAX_STUDENT_NAME 30
#define MAX_PHONE_NUMBER 20
#define MAX_HOME_ADDRESS 50
#define MAX_EMAIL_ADDRESS 30
#define MAX_ACEDEMIC_MAJOR 30

#define FILE_HEADER_SIZE  sizeof(logindetails)
#define FILE_HEADER_SIZE2  sizeof(StudentInfo)

typedef struct
{
    char username[25];
    char password[25];
} logindetails;

typedef struct// to call in program
{
    char studentName[MAX_STUDENT_NAME];// declare the character data type
    char phoneNumber[MAX_PHONE_NUMBER];// declare the charecter data type
    char homeAddress[MAX_HOME_ADDRESS];// declare the character data type
    char emailAddress[MAX_EMAIL_ADDRESS];// declare the character data type
    char acedemicMajor[MAX_ACEDEMIC_MAJOR];// declare the character data type
} StudentInfo;

void printMessageCenter(const char* );
void headMessage(const char*);
int isNameValid(const char*);
void AddNewStudent();
void ListAllStudent();
void SearchStudent();
void EditStudent(void);
void DeleteStudent();
void initial_db();
int isFileExists(const char*);
void login_system();
void menu();
void Exit();

int main()
{
    initial_db();
    login_system();
    return 0;
}

void printMessageCenter(const char* message)
{
    int len =0;
    int pos = 0;
    //calculate how many space need to print
    len = (78 - strlen(message))/2;
    printf("\t\t\t");
    for(pos =0 ; pos < len ; pos++)
    {
        //print space
        printf(" ");
    }
    //print message
    printf("\n\t\t\t#################              %s                 ############",message);
}
void headMessage(const char *message)
{
    system("cls");
    printf("\t\t\t###############################################################################");
    printf("\n\t\t\t#################                   ENGR213                        ############");
    printf("\n\t\t\t############     Student Information Management System Project in C   #########");
    printf("\n\t\t\t#################                                                  ############");
    printf("\n\t\t\t###############################################################################");
    printMessageCenter(message);

}
int isNameValid(const char *name)
{
    int validName = 1;
    int len = 0;
    int index = 0;
    len = strlen(name);
    for(index =0; index <len ; ++index)
    {
        if(!(isalpha(name[index])) && (name[index] != '\n') && (name[index] != ' '))
        {
            validName = 0;
            break;
        }
    }
    return validName;
}

void EditStudent(void)
{
    StudentInfo AddStudentToDB = {0};
    FILE *fp = NULL;
    unsigned char studentName[MAX_STUDENT_NAME] = {0};
    unsigned char phoneNumber[MAX_PHONE_NUMBER] = {0};
    unsigned char homeAddress[MAX_HOME_ADDRESS] = {0};
    unsigned char emailAddress[MAX_EMAIL_ADDRESS] = {0};
    unsigned char acedemicMajor[MAX_ACEDEMIC_MAJOR] = {0};

    headMessage("Update Credential");
    fp = fopen(FILE_NAME2,"rb+");
    if(fp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }
    fread (&AddStudentToDB,FILE_HEADER_SIZE2, 1, fp);
    if (fseek(fp,0,SEEK_SET) != 0)
    {
        fclose(fp);
        printf("\n\t\t\tFacing issue while updating password\n");
        exit(1);
    }
    printf("\n\n\t\t\tStudent Name:");
    fflush(stdin);
    fgets(studentName,MAX_STUDENT_NAME,stdin);

    printf("\n\t\t\tPhone: ");
    fflush(stdin);
    fgets(phoneNumber,MAX_PHONE_NUMBER,stdin);

    printf("\n\t\t\tHome Address: ");
    fflush(stdin);
    fgets(homeAddress,MAX_HOME_ADDRESS,stdin);

    printf("\n\t\t\tEmail Address: ");
    fflush(stdin);
    fgets(emailAddress,MAX_EMAIL_ADDRESS,stdin);

    printf("\n\t\t\tAcademic Major: ");
    fflush(stdin);
    fgets(acedemicMajor,MAX_ACEDEMIC_MAJOR,stdin);

    strncpy(AddStudentToDB.studentName,studentName,sizeof(studentName));
    strncpy(AddStudentToDB.phoneNumber,phoneNumber,sizeof(phoneNumber));
    strncpy(AddStudentToDB.homeAddress,homeAddress,sizeof(homeAddress));
    strncpy(AddStudentToDB.emailAddress,emailAddress,sizeof(emailAddress));
    strncpy(AddStudentToDB.acedemicMajor,acedemicMajor,sizeof(acedemicMajor));

    fwrite(&AddStudentToDB,FILE_HEADER_SIZE2, 1, fp);
    fclose(fp);

    printf("\n\n\t\t\tPress any key to go to main menu.....");
    fflush(stdin);
    getchar();
}

// delete function
void DeleteStudent()
{
    int found = 0;
    char studentDelete = 0;

    char studentName[MAX_STUDENT_NAME] = {0};
    StudentInfo AddStudentToDB = {0};
    FILE *fp = NULL;
    FILE *tmpFp = NULL;
    int status = 0;
    headMessage("Delete Books Details");
    fp = fopen(FILE_NAME2,"rb");
    if(fp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }
    tmpFp = fopen("tmp.bin","wb");
    if(tmpFp == NULL)
    {
        fclose(fp);
        printf("File is not opened\n");
        exit(1);
    }
    fread (&AddStudentToDB,FILE_HEADER_SIZE2, 1, fp);
    fwrite(&AddStudentToDB,FILE_HEADER_SIZE2, 1, tmpFp);
    printf("\n\t\t\tEnter the name of student to delete:");
    scanf("%s",&studentDelete);
    while (fread (&AddStudentToDB, sizeof(AddStudentToDB), 1, fp))
    {
        if(AddStudentToDB.studentName != studentDelete)
        {
            fwrite(&AddStudentToDB,sizeof(AddStudentToDB), 1, tmpFp);
        }
        else
        {
            found = 1;
        }
    }
    (found)? printf("\n\t\t\tRecord deleted successfully....."):printf("\n\t\t\tRecord not found");
    fclose(fp);
    fclose(tmpFp);
    remove(FILE_NAME2);
    rename("student.bin",FILE_NAME2);
     printf("\n\n\t\t\tPress any key to go to main menu.....");
    fflush(stdin);
    getchar();
}

// search student
void SearchStudent()
{
    int found = 0;
    char studentName[MAX_STUDENT_NAME] = {0};
    StudentInfo AddStudentToDB = {0};
    FILE *fp = NULL;
    int status = 0;
    fp = fopen(FILE_NAME2,"rb");
    if(fp == NULL)
    {
        printf("\n\t\t\tFile is not opened\n");
        exit(1);
    }
    headMessage("SEARCH BOOKS");
    //put the control on books detail
    if (fseek(fp,FILE_HEADER_SIZE2,SEEK_SET) != 0)
    {
        fclose(fp);
        printf("\n\t\t\tFacing issue while reading file\n");
        exit(1);
    }
    printf("\n\n\t\t\tName of the student to search:");
    fflush(stdin);
    fgets(studentName,MAX_STUDENT_NAME,stdin);
    while (fread (&AddStudentToDB, sizeof(AddStudentToDB), 1, fp))
    {
        if(!strcmp(AddStudentToDB.studentName, studentName))
        {
            found = 1;
            break;
        }
    }
    if(found)
    {
        printf("\n\t\t\tName = %s\n",AddStudentToDB.studentName);
        printf("\t\t\tPhone = %s",AddStudentToDB.phoneNumber);
        printf("\t\t\tAddress = %s",AddStudentToDB.homeAddress);
        printf("\t\t\tEmail =  %s",AddStudentToDB.emailAddress);
    }
    else
    {
        printf("\n\t\t\tNo Record");
    }
    fclose(fp);
    printf("\n\n\n\t\t\tPress any key to go to main menu.....");
    getchar();
}

// List All Student
void ListAllStudent()
{
    int found = 0;

    StudentInfo AddStudentToDB = {0};
    FILE *fp = NULL;
    int status = 0;
    unsigned int countBook = 1;
    headMessage("List of Students");
    fp = fopen(FILE_NAME2,"rb");
    if(fp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }
    if (fseek(fp,FILE_HEADER_SIZE2,SEEK_SET) != 0)
    {
        fclose(fp);
        printf("Facing issue while reading file\n");
        exit(1);
    }
    while (fread (&AddStudentToDB, sizeof(AddStudentToDB), 1, fp))
    {
        printf("\n\t\t\tStudent Count = %d\n\n",countBook);
        printf("\t\t\tName = %s",AddStudentToDB.studentName);
        printf("\n\t\t\tPhone = %s",AddStudentToDB.phoneNumber);
        printf("\t\t\tAddress = %s",AddStudentToDB.homeAddress);
        printf("\t\t\tEmail =  %s",AddStudentToDB.emailAddress);
        printf("\t\t\tMajor =  %s\n",AddStudentToDB.acedemicMajor);
        found = 1;
        ++countBook;
    }
    fclose(fp);
    if(!found)
    {
        printf("\n\t\t\tNo Record");
    }
    printf("\n\n\t\t\tPress any key to go to main menu.....");
    fflush(stdin);
    getchar();
}

// Add New Student
void AddNewStudent()
{
    int days;
    StudentInfo AddStudentToDB = {0};
    FILE *fp = NULL;
    int status = 0;
    fp = fopen(FILE_NAME2,"ab+");
    if(fp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }

    printf("\n\n\t\t\tTo exit enter Blank Space in the name input");

    do
    {
        printf("\n\t\t\tStudent Name(Use identical): ");
        fflush(stdin);
        fgets(AddStudentToDB.studentName,MAX_STUDENT_NAME,stdin);
        status = isNameValid(AddStudentToDB.studentName);
        if (!status)
        {
            printf("\n\t\t\tName contain invalid character. Please enter again.");
        }
    }
    while(!status);
    printf("\n\t\t\tPhone: ");
    fflush(stdin);
    fgets(AddStudentToDB.phoneNumber,MAX_PHONE_NUMBER,stdin);

    printf("\n\t\t\tHome Address: ");
    fflush(stdin);
    fgets(AddStudentToDB.homeAddress,MAX_HOME_ADDRESS,stdin);

    printf("\n\t\t\tEmail Address: ");
    fflush(stdin);
    fgets(AddStudentToDB.emailAddress,MAX_EMAIL_ADDRESS,stdin);

    printf("\n\t\t\tAcademic Major: ");
    fflush(stdin);
    fgets(AddStudentToDB.acedemicMajor,MAX_ACEDEMIC_MAJOR,stdin);

    fwrite(&AddStudentToDB,sizeof(AddStudentToDB), 1, fp);
    fclose(fp);
}
void Exit(){
    int choice = 0;
    printf("\n\n\n\t\t\tAre you sure you want to exit?");
    printf("\n\n\n\t\t\t[1]Main Menu\t\t[0]Exit\n");
    scanf("%d",&choice);
    if(choice == 1){
            menu();
          }

    else{
        exit(1);
    }


}
void menu()
{
    int choice = 0;
    do
    {
        printf("\n\n\n\t\t\t\t\t\t\tMAIN MENU");
        printf("\n\t\t\t\t\t\t=========================");
        printf("\n\n\n\t\t\t\t\t\t[1] Add a new Student");
        printf("\n\t\t\t\t\t\t[2] List all Student");
        printf("\n\t\t\t\t\t\t[3] Search for Student");
        printf("\n\t\t\t\t\t\t[4] Edit a Student");
        printf("\n\t\t\t\t\t\t[5] Delete a Student");
        printf("\n\t\t\t\t\t\t[0] Exit");
        printf("\n\t\t\t\t\t\t=========================");
        printf("\n\n\n\t\t\t\t\t\tEnter choice: ");
        scanf("%d",&choice);
        switch(choice)
        {
        case 1:
            AddNewStudent();
            break;
        case 2:
            ListAllStudent();
            break;
        case 3:
            SearchStudent();
            break;
        case 4:
            EditStudent();
            break;
        case 5:
            DeleteStudent();
            break;
        case 0:
            Exit();
            break;
        default:
            printf("\n\n\n\t\t\tINVALID INPUT!!! Try again...");
        }                                            //Switch Ended
    }
    while(choice!=0);                                        //Loop Ended
}

void login_system()
{
    unsigned char userName[MAX_USER_NAME] = {0};
    unsigned char password[MAX_PASSWORD] = {0};

    int L=0;

    logindetails fileHeaderInfo = {0};
    FILE *fp = NULL;

    headMessage("                  ");

    fp = fopen(FILE_NAME1,"rb");

    if(fp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }
    fread (&fileHeaderInfo,FILE_HEADER_SIZE, 1, fp);
    fclose(fp);
    do
    {
        printf("\n\n\n\t\t\t\t\t\t\tUsername:");
        fgets(userName,25,stdin);
        printf("\n\t\t\t\t\t\t\tPassword:");
        fgets(password,25,stdin);
        if((!strcmp(userName,fileHeaderInfo.username)) && (!strcmp(password,fileHeaderInfo.password)))
        {
            headMessage("LOGIN SUCCESSFULLY!");
            menu();
        }
        else
        {
            printf("\t\t\t\tLogin Failed Enter Again Username & Password\n\n");
            L++;
        }
    }
    while(L<=3);
    if(L>3)
    {
        headMessage("Login Failed");
        printf("\t\t\t\tSorry,Unknown User.");
        getch();
        system("cls");
    }
}
int isFileExists(const char *file)
{
    // Try to open file
    FILE *fp = fopen(file, "rb");
    int status = 0;
    // If file does not exists
    if (fp != NULL)
    {
        status = 1;
        // File exists hence close file
        fclose(fp);
    }
    return status;
}
void initial_db()
{
    FILE *fp = NULL;
    int status = 0;
    const char username[] ="user\n";
    const char password[] ="user\n";
    logindetails fileHeaderInfo = {0};
    status = isFileExists(FILE_NAME1);
    if(!status)
    {
        fp = fopen(FILE_NAME1,"wb");
        if(fp != NULL)
        {
            strncpy(fileHeaderInfo.password,password,sizeof(password));
            strncpy(fileHeaderInfo.username,username,sizeof(username));
            fwrite(&fileHeaderInfo,FILE_HEADER_SIZE, 1, fp);
            fclose(fp);
        }
    }
}

