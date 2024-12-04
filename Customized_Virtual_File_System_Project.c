#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//          Author        :     Nilesh Balu Vidhate
//
//          Application   :     Customized Virtual File System (CVFS) is a project that provides a file 
//                              management solution designed to copy the functionality of a real file system.
//                              It includes features such as file creation, deletion, reading, writing and 
//                              implemented with efficient data structures and algorithms.

//          Date          :     10 Sep 2024
//
//
/////////////////////////////////////////////////////////////////////

#define MAXINODE 50

#define READ 1
#define WRITE 2

#define MAXFILESIZE 1024

#define REGULAR 1
#define SPECIAL 2

#define START 0
#define CURRENT 1
#define END 2


typedef struct superblock
{
    int TotalInodes;
    int FreeInodes;
}SUPERBLOCK,*PSUPERBLOCK;

typedef struct inode
{
    char FileName[50];
    int InodeNumber;
    int FileSize;
    int FileActualSize;
    int FileType;
    char *Buffer;
    int LinkCount;
    int ReferanceCount;
    int permission; // 1  2  3
    struct inode *next;
}INODE,*PINODE,**PPINODE;

typedef struct filetable
{
    int readoffset;
    int writeoffset;
    int count;
    int mode; // 1 2 3 
    PINODE ptrinode;
}FILETABLE, *PFILETABLE;

typedef struct UFDTarr
{
    PFILETABLE ptrfiletable;
}UFDT;

UFDT UFDTArr[50];

SUPERBLOCK SUPERBLOCKobj;
PINODE head = NULL;

void InitisliseSuperblock()
{
    int i = 0;

    while(i < MAXINODE)
    {
        UFDTArr[i].ptrfiletable = NULL;
        i++;
    }

    SUPERBLOCKobj.TotalInodes = MAXINODE;
    SUPERBLOCKobj.FreeInodes = MAXINODE;
}

void CreateDILB()
{
    int i = 0;
    PINODE newn = NULL;
    PINODE temp = head;

    while(i <= MAXINODE)
    {
        newn = (PINODE)malloc(sizeof(INODE));

        newn->LinkCount = 0;
        newn->ReferanceCount = 0;
        newn->FileType = 0;
        newn->FileSize = 0;

        newn->Buffer = NULL;
        newn->next = NULL;

        newn->InodeNumber = i;

        if(temp == NULL)
        {
            head = newn;
            temp = head;
        }
        else
        {
            temp->next = newn;
            temp = temp->next;
        }
        i++;
    }
    printf("DILB created Successfully.\n");
}

void ls_file()
{
    int i = 0;
    PINODE temp = head;

    if(SUPERBLOCKobj.FreeInodes == MAXINODE)
    {
        printf("Error : There are no files \n");
        return;
    }

    printf("\nFileName\tInode Number\tFile Size\tLink Count\n");
    printf("-----------------------------------------\n");
    while(temp != NULL)
    {
        if(temp->FileType != 0)
        {
            printf("%s\t\t%d\t\t%d\t\t%d\n",temp->FileName,temp->InodeNumber,temp->FileActualSize,temp->LinkCount);
        }
        temp = temp->next;
    }
    printf("------------------------------------------\n");
}

void CloseAllFile()
{
    int i = 0;
    while(i < 50)
    {
        if(UFDTArr[i].ptrfiletable != NULL)
        {
            UFDTArr[i].ptrfiletable->readoffset = 0;
            UFDTArr[i].ptrfiletable->writeoffset = 0;
            (UFDTArr[i].ptrfiletable->ptrinode->ReferanceCount)--;
            break;
        }
        i++;
    }
}

void DisplayHelp()
{
    printf("ls  : To List out all files\n");
    printf("clear : To clear console\n");
    printf("create : To create the file\n");
    printf("open : To open the file\n");
    printf("close  : To close file\n");
    printf("closeall  : To close all opened files\n");
    printf("read : To read the contents from file\n");
    printf("write : To write content into file\n");
    printf("exit : To terminate the file system\n");
    printf("stat : To Display information of file using name\n");
    printf("fstat : To Display information of file using file discriptor\n");
    printf("truncate : To remove all data from file\n");
    printf("rm : To delete the File\n");
}

int stat_file(char *name)
{
    PINODE temp = head;
    int i = 0;

    if(name == NULL)
    {
        return -1;
    }

    while(temp != NULL)
    {
        if(strcmp(name,temp->FileName) == 0)
        {
            break;
            temp = temp->next;
        }
    }

    if(temp == NULL)
    {
        return -2;
    }

    printf("\n ----------Statical information about file------------\n");
    printf("File Name  : %s\n",temp->FileName);
    printf("Inode Number : %d \n",temp->InodeNumber);
    printf("File Size : %d\n",temp->FileSize);
    printf("Actual File Size : %d\n",temp->FileActualSize);
    printf("Link Count : %d\n",temp->LinkCount);
    printf("Reference Count : %d\n",temp->ReferanceCount);

    if(temp->permission == 1)
    {
        printf(" File Permission : read only\n");
    }
    else if(temp->permission == 2)
    {
        printf(" File Permission : write only\n");
    }
    else if(temp->permission == 3)
    {
        printf(" File Permission : read and write\n");
    }

    printf("-------------------------------------------\n");
    return 0;
}

int fstat_file(int fd)
{
    PINODE temp = head;
    int i = 0;

    if(fd < 0)
    {
        return -1;
    }

    if(UFDTArr[fd].ptrfiletable == NULL)
    {
        return -2;
    }
    temp = UFDTArr[fd].ptrfiletable->ptrinode;

    printf("\n ----------Statical information about file------------\n");
    printf("File Name  : %s\n",temp->FileName);
    printf("Inode Number : %d \n",temp->InodeNumber);
    printf("File Size : %d\n",temp->FileSize);
    printf("Actual File Size : %d\n",temp->FileActualSize);
    printf("Link Count : %d\n",temp->LinkCount);
    printf("Reference Count : %d\n",temp->ReferanceCount);

    if(temp->permission == 1)
    {
        printf(" File Permission : read only\n");
    }
    else if(temp->permission == 2)
    {
        printf(" File Permission : write only\n");
    }
    else if(temp->permission == 3)
    {
        printf(" File Permission : read and write\n");
    }

    printf("-------------------------------------------\n");
    return 0;
}

int GetFDFromName(char *name)
{
    int i = 0;
    while(i<50)
    {
        if(UFDTArr[i].ptrfiletable != NULL)
        {
            if(strcmp((UFDTArr[i].ptrfiletable->ptrinode->FileName),name) == 0)
            break;
        }
        i++;
    }
    if(i == 50)
    {
        return -1;
    }
    else
    {
        return i;
    }
}

int CloseByName(char *name)
{
    int i = 0;
    i = GetFDFromName(name);

    if(i == -1)
    {
        return -1;
    }

    UFDTArr[i].ptrfiletable->readoffset = 0;
    UFDTArr[i].ptrfiletable->writeoffset = 0;
    (UFDTArr[i].ptrfiletable->ptrinode->ReferanceCount)--;
    return 0;
}

//rm_file("Demo.txt")
int rm_file(char *name)
{
    int fd = 0;
    fd = GetFDFromName(name);

    if(fd == -1)
    {
        return -1;
    }

    (UFDTArr[fd].ptrfiletable->ptrinode->LinkCount)--;

    if(UFDTArr[fd].ptrfiletable->ptrinode->LinkCount == 0)
    {
        UFDTArr[fd].ptrfiletable->ptrinode->FileType = 0;
        //free(UFDTArr[fd].ptrfiletable->ptrinode->Buffer);
        free(UFDTArr[fd].ptrfiletable);

        UFDTArr[fd].ptrfiletable = NULL;

        (SUPERBLOCKobj.FreeInodes)++;

    }
}

void man(char *name)
{
    if(name == NULL)
    {
        return;
    }
    else if(strcmp(name,"create") == 0)
    {
        printf("Description : Used to create a new regular file\n");
        printf("Usage : create File_Name Permission\n");
    }
    else if(strcmp(name,"read") == 0)
    {
        printf("Description : Used to read data from regular file\n");
        printf("Usage : read File_Name No_of_Bytes_To_Read\n");
    }
    else if(strcmp(name,"write") == 0)
    {
        printf("Description : Used to write into regular file\n");
        printf("Usage : write File_Name \n After this enter the data that you want to write\n");
    }
    else if(strcmp(name,"ls") == 0)
    {
        printf("Description : Used to see the Files\n");
        printf("Usage : ls \n");   
    }
    else if(strcmp(name,"stat") == 0)
    {
        printf("Description : Used to display information of file\n");
        printf("Usage : stat File_Name\n");   
    }
    else if(strcmp(name,"fstat") == 0)
    {
        printf("Description : Used to display information of file\n");
        printf("Usage : stat File_descriptor\n");   
    }
    else if(strcmp(name,"truncate") == 0)
    {
        printf("Description : Used to remove data from file\n");
        printf("Usage : truncate File_Name\n");   
    }
    else if(strcmp(name,"open") == 0)
    {
        printf("Description : Used to open existing file\n");
        printf("Usage : open File_Name Mode\n");   
    }
    else if(strcmp(name,"close") == 0)
    {
        printf("Description : Used to close opend file\n");
        printf("Usage : close File_Name\n");   
    }
    else if(strcmp(name,"closeall") == 0)
    {
        printf("Description : Used to close all opend file file\n");
        printf("Usage : closeall\n");   
    }
    else if(strcmp(name,"lseek") == 0)
    {
        printf("Description : Used to change file offset\n");
        printf("Usage : lseek File_Name ChangeInOffset StartPoint\n");   
    }
    else if(strcmp(name,"rm") == 0)
    {
        printf("Description : Used to delete the file\n");
        printf("Usage : rm File_Name\n");   
    }
    else 
    {
        printf("Error : No manual entry available\n");      
    }
}

int WriteFile(int fd, char *arr,int isize)
{
    if(((UFDTArr[fd].ptrfiletable->mode) != WRITE) && ((UFDTArr[fd].ptrfiletable->mode) != READ+WRITE))
    {
        return -1;
    }

    if(((UFDTArr[fd].ptrfiletable->ptrinode->permission) != WRITE) && ((UFDTArr[fd].ptrfiletable->ptrinode->permission) != READ+WRITE))
    {
        return -1;
    }

    if(UFDTArr[fd].ptrfiletable->writeoffset == MAXFILESIZE)
    {
        return -2; 
    }

    if(UFDTArr[fd].ptrfiletable->ptrinode->FileType != REGULAR)
    {
        return -3; 
    }

    strncpy((UFDTArr[fd].ptrfiletable->ptrinode->Buffer) + (UFDTArr[fd].ptrfiletable->writeoffset),arr,isize);

    (UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize) = (UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize) + isize;

    return isize;

}

int truncate_file(char *name)
{
    int fd = GetFDFromName(name);

    if(fd == -1)
    {
        return -1;
    }

    memset(UFDTArr[fd].ptrfiletable->ptrinode->Buffer,0,1024);
    UFDTArr[fd].ptrfiletable->readoffset = 0;
    UFDTArr[fd].ptrfiletable->writeoffset = 0;
    UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize = 0;

}

PINODE Get_Inode(char *name)
{
    PINODE temp = head;

    int i = 0;

    if(name == NULL)
    {
        return NULL;
    }

    while(temp != NULL)
    {
        if(strcmp(name,temp->FileName) == 0)
        {
            break;
        }
        temp = temp->next;
    }

    return temp;

}

int CreateFile(char *name, int permission)
{
    int i = 3;

    PINODE temp = head;

    if((name == NULL) || (permission == 0) || (permission > 3))
    {
        return -1;
    }

    if(SUPERBLOCKobj.FreeInodes == 0)
    {
        return -2;
    }


    if(Get_Inode(name) != NULL)
    {
        return -3;
    }

    while(temp != NULL)
    {
        if((temp->FileType) == 0)
        {
            break;
        }
        temp = temp->next;
    }

    while(i<50)
    {
        if(UFDTArr[i].ptrfiletable == NULL)
        {
            break;
        }
        i++;
    }
    
    UFDTArr[i].ptrfiletable = (PFILETABLE)malloc(sizeof(FILETABLE));

    UFDTArr[i].ptrfiletable->count = 1;
    UFDTArr[i].ptrfiletable->mode = permission;
    UFDTArr[i].ptrfiletable->readoffset = 0;
    UFDTArr[i].ptrfiletable->writeoffset =0;

    UFDTArr[i].ptrfiletable->ptrinode = temp;

    strcpy(UFDTArr[i].ptrfiletable->ptrinode->FileName,name);
    UFDTArr[i].ptrfiletable->ptrinode->FileType = REGULAR;
    UFDTArr[i].ptrfiletable->ptrinode->ReferanceCount = 1;
    UFDTArr[i].ptrfiletable->ptrinode->LinkCount = 1;
    UFDTArr[i].ptrfiletable->ptrinode->FileSize = MAXFILESIZE;
    UFDTArr[i].ptrfiletable->ptrinode->FileActualSize = 0;
    UFDTArr[i].ptrfiletable->ptrinode->permission = permission;

    UFDTArr[i].ptrfiletable->ptrinode->Buffer = (char*)malloc(MAXFILESIZE);

    (SUPERBLOCKobj.FreeInodes)--;

    return i;
}

int OpenFile(char *name, int mode)
{
    int i = 0;

    PINODE temp = NULL;

    if(name == NULL || mode <= 0)
    {
        return -1;
    }

    temp = Get_Inode(name);

    if(temp == NULL)
    {
        return -2;
    }

    if(temp->permission < mode)
    {
        return -3;
    }
    
    while(i<50)
    {
        if(UFDTArr[i].ptrfiletable == NULL)
        {
            break;
        }
        i++;
    }

    UFDTArr[i].ptrfiletable = (PFILETABLE)malloc(sizeof(FILETABLE));
    
    if(UFDTArr[i].ptrfiletable == NULL)
    {
        return -1;
    }

    UFDTArr[i].ptrfiletable->count = 1;
    UFDTArr[i].ptrfiletable->mode = mode;

    if(mode == READ + WRITE)
    {
        UFDTArr[i].ptrfiletable->readoffset = 0;
        UFDTArr[i].ptrfiletable->writeoffset = 0;
    }
    else if(mode == READ)
    {
        UFDTArr[i].ptrfiletable->readoffset = 0;
    }
    else if(mode == WRITE)
    {
        UFDTArr[i].ptrfiletable->writeoffset = 0;
    }
    UFDTArr[i].ptrfiletable->ptrinode = temp;
    (UFDTArr[i].ptrfiletable->ptrinode->ReferanceCount)++;

    return i;
}

int ReadFile(int fd, char *arr, int isize)
{
    int read_size = 0;

    if(UFDTArr[fd].ptrfiletable == NULL)
    {
        return -1;
    }

    if(UFDTArr[fd].ptrfiletable->mode != READ && UFDTArr[fd].ptrfiletable->mode != READ + WRITE)
    {
        return -2;
    }

    if(UFDTArr[fd].ptrfiletable->ptrinode->permission != READ && UFDTArr[fd].ptrfiletable->ptrinode->permission != READ + WRITE)
    {
        return -2;
    }

    if(UFDTArr[fd].ptrfiletable->readoffset == UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize)
    {
        return -3;
    }

    if(UFDTArr[fd].ptrfiletable->ptrinode->FileType != REGULAR)
    {
        return -4;
    }

    read_size = (UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize)-(UFDTArr[fd].ptrfiletable->readoffset);

    if(read_size < isize)
    {
        strncpy(arr,(UFDTArr[fd].ptrfiletable->ptrinode->Buffer) + (UFDTArr[fd].ptrfiletable->readoffset), read_size);
        (UFDTArr[fd].ptrfiletable->readoffset) = (UFDTArr[fd].ptrfiletable->readoffset) + read_size;
    }
    else
    {
        strncpy(arr,(UFDTArr[fd].ptrfiletable->ptrinode->Buffer) + (UFDTArr[fd].ptrfiletable->readoffset), isize);
        (UFDTArr[fd].ptrfiletable->readoffset) = (UFDTArr[fd].ptrfiletable->readoffset) + isize;
    }

    return isize;
}

int LseekFile(int fd,int size,int from)
{
    if((fd < 0) || (from > 2))
    {
        return -1;
    }

    if(UFDTArr[fd].ptrfiletable == NULL)
    {
        return -1;
    }

    if((UFDTArr[fd].ptrfiletable->mode == READ) || (UFDTArr[fd].ptrfiletable->mode == READ + WRITE))
    {
        if(from == CURRENT)
        {
            if(((UFDTArr[fd].ptrfiletable->readoffset) + size) > UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize)
            {
                return -1;
            }

            if(((UFDTArr[fd].ptrfiletable->readoffset) + size) < 0)
            {
                return -1;
            }

            (UFDTArr[fd].ptrfiletable->readoffset) = (UFDTArr[fd].ptrfiletable->readoffset)+size;
        }
        else if(from == START)
        {
            if(size > (UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize))
            {
                return -1;
            }

            if(size < 0)
            {
                return -1;
            }

            (UFDTArr[fd].ptrfiletable->readoffset) = size;
        }
        else if(from == END)
        {
            if((UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize) + size > MAXFILESIZE)
            {
                return -1;
            }

            if(((UFDTArr[fd].ptrfiletable->readoffset) + size) < 0)
            {
                return -1;
            }

            (UFDTArr[fd].ptrfiletable->readoffset) = (UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize) + size;
        }
    }
    else if((UFDTArr[fd].ptrfiletable->mode) == WRITE)
    {
        if(from == CURRENT)
        {
            if(((UFDTArr[fd].ptrfiletable->writeoffset) + size) > MAXFILESIZE)
            {
                return -1;
            }
            
            if(((UFDTArr[fd].ptrfiletable->writeoffset) + size) < 0)
            {
                return -1;
            }

            if(((UFDTArr[fd].ptrfiletable->writeoffset) + size) > (UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize))
            {
                return -1;
            }

            (UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize) = (UFDTArr[fd].ptrfiletable->writeoffset) + size;
            (UFDTArr[fd].ptrfiletable->writeoffset) = (UFDTArr[fd].ptrfiletable->writeoffset) + size;;
        }
        else if(from == START)
        {
            if(size > MAXFILESIZE)
            {
                return -1;
            }

            if(size < 0)
            {
                return -1;
            }

            if(size > (UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize))
            {
                return -1;
            }

            (UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize) = size;
            (UFDTArr[fd].ptrfiletable->writeoffset) = size;
        }
        else if(from == END)
        {
            if((UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize) + size > MAXFILESIZE)
            {
                return -1;
            }

            if(((UFDTArr[fd].ptrfiletable->writeoffset) + size) < 0)
            {
                return -1;
            }
            (UFDTArr[fd].ptrfiletable->writeoffset) = (UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize) + size;
        }
    }
    else
    {
        printf("Error : Command not found...\n");
    }
}

int main()
{
    char *ptr = NULL;

    int ret = 0;
    int fd = 0;
    int count = 0;

    char command[4][80];
    char str[80];
    char arr[1024];

    InitisliseSuperblock();
    CreateDILB();

    while(1)
    {
        fflush(stdin);
        strcpy(str,"");

        printf("Niles@CVFS>");

        fgets(str,80,stdin); // sccanf("%[^'\n']s,str");

        count = sscanf(str,"%s %s %s %s", command[0],command[1],command[2],command[3]);

        if(count == 1)
        {
            if(strcmp(command[0],"ls") == 0)
            {
                ls_file();
            }
            else if(strcmp(command[0],"closeall") == 0)
            {
                CloseAllFile();
                printf("All Files closed successfully\n");
                continue;
            }
            else if(strcmp(command[0],"clear") == 0)
            {
                //system("cls");// on Windows
                system("clear");
                continue;
            }
            else if(strcmp(command[0],"help") == 0)
            {
                DisplayHelp();
                continue;
            }
            else if(strcmp(command[0],"exit") == 0)
            {
                printf("Terminating the niles Virtual File System.\n");
                break;
            }
            else
            {
                printf("Error : Command not found...\n");
                continue;
            }
        }
        else if(count == 2)
        {
            if(strcmp(command[0],"stat") == 0)
            {
                ret = stat_file(command[1]);
                if(ret == -1)
                {
                    printf("Error : Incorrect Parameters\n");
                }
                if(ret == -2)
                {
                    printf("Error : There is no such file\n");
                }
                continue;
            }
            else if(strcmp(command[0],"fstat") == 0)
            {
                ret = fstat_file(atoi(command[1]));
                if(ret == -1)
                {
                    printf("Error : Incorrect Parameters\n");
                }
                if(ret == -2)
                {
                    printf("Error : There is no such file\n");
                }
                continue;
            }
            else if(strcmp(command[0],"close") == 0)
            {
                ret = CloseByName(command[1]);
                if(ret == -1)
                {
                    printf("Error : There is no such file\n");
                }
                continue;
            }
            else if(strcmp(command[0],"rm") == 0)
            {
                ret = rm_file(command[1]);
                if(ret == -1)
                {
                    printf("Error : There is no such file\n");
                }
                continue;
            }
            else if(strcmp(command[0],"man") == 0)
            {
                man(command[1]);
                continue;
            }
            else if(strcmp(command[0],"write") == 0)
            {
                fd = GetFDFromName(command[1]);
                if(fd == -1)
                {
                    printf("Error : Incorrect parameter\n");
                    continue;
                }
                printf("Enter the data :\n");
                scanf("%[^'\n']s,",arr);

                ret = strlen(arr);
                if(ret == 0)
                {
                    printf("Error : Incorrect parameter\n");
                    continue;
                }
                
                ret = WriteFile(fd,arr,ret);
                
                if(ret == -1)
                {
                    printf("Error : Permission denied\n");
                }
                if(ret == -2)
                {
                    printf("Error : There is no sufficient memory to write\n");
                }
                if(ret == -3)
                {
                    printf("Error : It is not regular file\n");
                }
            }
            else if(strcmp(command[0],"truncate") == 0)
            {
                ret = truncate_file(command[1]);
                if(ret == -1)
                {
                    printf("Error : Incorrect parameter\n");
                }
            }
            else
            {
                printf("Error : Command not found...\n");
                continue;
            }
            
        }
        else if(count == 3)
        {
            if(strcmp(command[0],"create") == 0)
            {
                ret = CreateFile(command[1],atoi(command[2]));

                if(ret >= 0)
                {
                    printf("File is Successfully created with file descriptor : %d\n",ret);
                }

                if(ret == -1)
                {
                    printf("Error : Incorrect parameter\n");
                }

                if(ret == -2)
                {
                    printf("Error : There is no free iNodes\n");
                }

                if(ret == -3)
                {
                    printf("Error : File already exists\n");
                }

                if(ret == -4)
                {
                    printf("Error : Memory allocation failure\n");
                }

                continue;
            }
            else if(strcmp(command[0],"open") == 0)
            {
                ret = OpenFile(command[1],atoi(command[2]));

                if(ret >= 0)
                {
                    printf("File is Successfully opend with file descriptor : %d\n",ret);
                }

                if(ret == -1)
                {
                    printf("Error : Incorrect parameter\n");
                }

                if(ret == -2)
                {
                    printf("Error : There is not present\n");
                }

                if(ret == -3)
                {
                    printf("Error : Permission denied\n");
                }

                continue;   
            }
            else if(strcmp(command[0],"read") == 0)
            {
                ret = GetFDFromName(command[1]);

                if(fd == -1)
                {
                    printf("Error : Incorrect parameter\n");
                    continue;
                }
                ptr = (char*)malloc(sizeof(atoi(command[2])) + 1);
                if(ptr == NULL)
                {
                    printf("Error : memory allocation failure\n");
                    continue;
                }

                ret = ReadFile(fd,ptr,atoi(command[2]));

                if(ret == -1)
                {
                    printf("Error : File not existing\n");
                }

                if(ret == -2)
                {
                    printf("Error : Permisssion denied\n");
                }

                if(ret == -3)
                {
                    printf("Error : Reached at end of file\n");
                }

                if(ret == -4)
                {
                    printf("Error : it is not regular file\n");
                }
                
                if(ret == 0)
                {
                    printf("Error : File is empty\n");
                }

                if(ret > 0)
                {
                    write(2,ptr,ret);
                }

                continue; 
            }
            else
            {
                printf("Error : Command not found...\n");
                continue;
            }
        }
        else if(count == 4)
        {
            if(strcmp(command[0],"lseek") == 0)
            {
                fd = GetFDFromName(command[1]);

                if(fd == -1)
                {
                    printf("Error : Incorrect parameter\n");
                    continue;
                }

                ret = LseekFile(fd,atoi(command[2]),atoi(command[3]));

                if(ret == -1)
                {
                    printf("Error : Unable to perform lseek\n");
                }
            }
            else
            {
                printf("Error : Command not found...\n");
                continue;
            }
        }
        else
        {
           printf("Error : Command not found...\n");
            continue; 
        }
    }

    return 0;
}