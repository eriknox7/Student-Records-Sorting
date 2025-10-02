#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<windows.h>
#define Newline "\n"
#define escape '\e'
typedef struct Node {
    char name[35];
    unsigned long int enroll_no;
    int DD, MM, YYYY;
    struct Node *next;
} Node;
Node *Head = NULL;
Node* Tail = NULL;
Node* GetNewNode(char name[], unsigned long int enroll_no, int DD, int MM, int YYYY);
void InsertNode(char name[], unsigned long int enroll_no, int DD, int MM, int YYYY);
int InvokeSort(int count);
void SortByName(int count);
void SortByEnrollment(int count);
void SortByDOB(int count);
void Swap(Node *Node1, Node *Node2);
void UserInstructions();
int TakeInput();
void ShowChoices();
void SortedHeader(int choice);
void PrintResult();
void EndingGreet();
void SaveFile(int choice);
int IsFileNameEmpty(char filename[]);
int DoesFileExist(char finename[]);
void ToLower(char name[]);
int CountDigit(unsigned long int n);
void ReleaseMemory();
void PrintWithDelay(char str[]);
void PrintWithDelay1(int count);
void PrintLine();
void PrintLine1();
void PrintLine2(FILE *fptr);
void PrintSpaces(int spaces);
void PrintSpaces1(int spaces, FILE *fptr);
void Red();
void Green();
void Yellow();
void Blue();
void purple();
void Cyan();
void ResetColor();
int main () {
    int choice, count;
    UserInstructions();
    count  = TakeInput();
    system("cls");
    PrintWithDelay1(count);
    ShowChoices();
    choice = InvokeSort(count);
    system("cls");
    SortedHeader(choice);
    PrintResult();
    SaveFile(choice);
    EndingGreet();
    ReleaseMemory();
    return 0;
}
Node* GetNewNode(char name[], unsigned long int enroll_no, int DD, int MM, int YYYY) {
    Node *NewNode = (Node*)malloc(sizeof(Node));
    strcpy(NewNode->name, name);
    NewNode->enroll_no = enroll_no;
    NewNode->DD = DD;
    NewNode->MM = MM;
    NewNode->YYYY = YYYY;
    NewNode->next = NULL;
    return NewNode;
}
void InsertNode(char name[], unsigned long int enroll_no, int DD, int MM, int YYYY) {
    if(Head == NULL) {
        Head = GetNewNode(name, enroll_no, DD, MM, YYYY);
        Tail = Head;
        return;
    }
    Tail->next = GetNewNode(name, enroll_no, DD, MM, YYYY);
    Tail = Tail->next;
}
int InvokeSort(int count) {
    int choice;
    choice_entry:
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
    fflush(stdin);
    scanf("%d", &choice);
    if(choice == 1) {
        SortByName(count);
    } else if(choice == 2) {
        SortByEnrollment(count);
    } else if(choice == 3) {
        SortByDOB(count);
    } else {
        PrintWithDelay(Newline "INVALID CHOICE. ENTER YOUR CHOICE AGAIN: ");
        goto choice_entry;
    }
    return choice;
}
void SortByName(int count) {
    int i, j, result, swapped = 0;
    Node *current, *next;
    char name1[35], name2[35];
    for(i=1; i<count; i++) {
        current = Head;
        next = current->next;
        for(j=1; j<=count-i; j++) {
            strcpy(name1, current->name);
            strcpy(name2, next->name);
            ToLower(name1);
            ToLower(name2);
            result = strcmp(name1, name2);
            if(result > 0) {
                Swap(current, next);
                swapped++;
            }
            current = next;
            next = current->next;
        }
        if(swapped==0) {
            break;
        }
    }
}
void SortByEnrollment(int count) {
    int i, j, swapped = 0;
    Node *current, *next;
    for(i=1; i<count; i++) {
        current = Head;
        next = current->next;
        for(j=1; j<=count-i; j++) {
            if(current->enroll_no > next->enroll_no) {
                Swap(current, next);
                swapped++;
            }
            current = next;
            next = current->next;
        }
        if(swapped == 0) {
            break;
        }
    }
}
void SortByDOB(int count) {
    int i, j, swapped = 0;
    Node *current, *next;
    for(i=1; i<count; i++) {
        current = Head;
        next = current->next;
        for(j=1; j<=count-i; j++) {
            if(current->YYYY < next->YYYY) {
                Swap(current, next);
                swapped++;
                goto update_link;
            } else if(current->YYYY == next->YYYY && current->MM < next->MM) {
                Swap(current, next);
                swapped++;
                goto update_link;
            } else if(current->YYYY == next->YYYY && current->MM == next->MM && current->DD < next->DD) {
                Swap(current, next);
                swapped++;
            }
            update_link:
            current = next;
            next = current->next;
        }
        if(swapped == 0) {
            break;
        }
    }
}
void Swap(Node *Node1, Node *Node2) {
    Node *tempNode = (Node*)malloc(sizeof(Node));
    Node *temp;
    *tempNode = *Node1;
    *Node1 = *Node2;
    *Node2 = *tempNode;
    temp = Node1->next;
    Node1->next = Node2->next;
    Node2->next = temp;
    free(tempNode);
}
void UserInstructions() {
    Green();
    PrintWithDelay("WELCOME TO EASY SORTING SOFTWARE!" Newline);
    printf(Newline);
    PrintWithDelay("ROLL NUMBERS WILL AUTOMATICALLY BE ALLOTED TO THE STUDENTS AFTER SORTING." Newline);
    printf(Newline);
    PrintWithDelay("THIS SOFTWARE IS CAPABLE OF SORTING THE DATA OF STUDENTS ON THE BASIS OF:" Newline);
    PrintWithDelay("1. NAME" Newline);
    PrintWithDelay("2. ENROLLMENT NUMBER" Newline);
    PrintWithDelay("3. DATE OF BIRTH" Newline);
    printf(Newline);
    purple();
    PrintWithDelay("PRESS ESC. KEY TO STOP ENTERING DATA." Newline);
    PrintWithDelay("PRESS ANY OTHER KEY TO CONTINUE ENTERING DATA." Newline Newline);
    PrintWithDelay("PRESS A KEY TO START ENTERING THE DATA: ");
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
    getch();
    printf(Newline Newline);
    ResetColor();
}
int TakeInput() {
    int count = 0, DD, MM, YYYY;
    unsigned long int enroll_no;
    char name[35];
    do{
        if(count != 0) {
            Blue();
            PrintLine();
        }
        Green();
        fflush(stdin);
        printf("ENTER THE NAME: ");
        Yellow();
        gets(name);
        Green();
        printf("ENTER THE ENROLLMENT NUMBER: ");
        Yellow();
        scanf("%lu", &enroll_no);
        Green();
        printf("ENTER DOB IN FORMAT 'DD MM YYYY': ");
        Yellow();
        scanf("%d%d%d", &DD, &MM, &YYYY);
        InsertNode(name, enroll_no, DD, MM, YYYY);
        count++;
        Beep(1500, 250);
    } while(getch() != escape);
    return count;
}
void ShowChoices() {
    printf(Newline Newline);
    Cyan();
    PrintWithDelay("1. SORT BY NAME" Newline);
    PrintWithDelay("2. SORT BY ENROLLMENT NUMBER" Newline);
    PrintWithDelay("3. SORT BY DATE OF BIRTH" Newline);
    PrintWithDelay("ENTER YOUR CHOICE: ");
}
void SortedHeader(int choice) {
    Yellow();
    if(choice == 1) {
        PrintWithDelay("DISPLAYING THE RESULTS AFTER SORTING BY NAME:" Newline Newline);
    } else if(choice == 2) {
        PrintWithDelay("DISPLAYING THE RESULTS AFTER SORTING BY ENROLLMENT NUMBER:" Newline Newline);
    } else {
        PrintWithDelay("DISPLAYING THE RESULTS AFTER SORTING BY DATE OF BIRTH:" Newline Newline);
    }
}
void PrintResult() {
    int roll_no = 1, digits;
    Node *temp = Head;
    Yellow();
    printf("ROLL NO        ENROLL NO        DOB          NAME" Newline);
    printf(Newline);
    while(temp != NULL) {
        digits = CountDigit(temp->enroll_no);
        Green();
        printf("%d", roll_no);
        if(roll_no > 999) {
            PrintSpaces(11);
            printf("%lu", temp->enroll_no);
            PrintSpaces(17-digits);
            if(temp->DD < 10 && temp->MM < 10) {
                printf("0%d-0%d-%d", temp->DD, temp->MM, temp->YYYY);
            } else if(temp->DD < 10) {
                printf("0%d-%d-%d", temp->DD, temp->MM, temp->YYYY);
            } else if(temp->MM < 10) {
                printf("%d-0%d-%d", temp->DD, temp->MM, temp->YYYY);
            } else {
                printf("%d-%d-%d", temp->DD, temp->MM, temp->YYYY);
            }
            PrintSpaces(3);
        } else if(roll_no > 99) {
            PrintSpaces(12);
            printf("%lu", temp->enroll_no);
            PrintSpaces(17-digits);
            if(temp->DD < 10 && temp->MM < 10) {
                printf("0%d-0%d-%d", temp->DD, temp->MM, temp->YYYY);
            } else if(temp->DD < 10) {
                printf("0%d-%d-%d", temp->DD, temp->MM, temp->YYYY);
            } else if(temp->MM < 10) {
                printf("%d-0%d-%d", temp->DD, temp->MM, temp->YYYY);
            } else {
                printf("%d-%d-%d", temp->DD, temp->MM, temp->YYYY);
            }
            PrintSpaces(3);
        } else if(roll_no > 9) {
            PrintSpaces(13);
            printf("%lu", temp->enroll_no);
            PrintSpaces(17-digits);
            if(temp->DD < 10 && temp->MM < 10) {
                printf("0%d-0%d-%d", temp->DD, temp->MM, temp->YYYY);
            } else if(temp->DD < 10) {
                printf("0%d-%d-%d", temp->DD, temp->MM, temp->YYYY);
            } else if(temp->MM < 10) {
                printf("%d-0%d-%d", temp->DD, temp->MM, temp->YYYY);
            } else {
                printf("%d-%d-%d", temp->DD, temp->MM, temp->YYYY);
            }
            PrintSpaces(3);
        } else {
            PrintSpaces(14);
            printf("%lu", temp->enroll_no);
            PrintSpaces(17-digits);
            if(temp->DD < 10 && temp->MM < 10) {
                printf("0%d-0%d-%d", temp->DD, temp->MM, temp->YYYY);
            } else if(temp->DD < 10) {
                printf("0%d-%d-%d", temp->DD, temp->MM, temp->YYYY);
            } else if(temp->MM < 10) {
                printf("%d-0%d-%d", temp->DD, temp->MM, temp->YYYY);
            } else {
                printf("%d-%d-%d", temp->DD, temp->MM, temp->YYYY);
            }
            PrintSpaces(3);
        }
        puts(temp->name);
        roll_no++;
        Red();
        PrintLine1();
        temp = temp->next;
    }
}
void EndingGreet() {
    Yellow();
    PrintWithDelay("THANKS FOR USING. ");
    getch();
    ResetColor();
}
void SaveFile(int sortchoice) {
    int choice;
    char filename[30];
    FILE *fptr;
    Blue();
    PrintWithDelay(Newline Newline "DO YOU WANT TO SAVE THE SORTED LIST IN A TEXT FILE?" Newline);
    PrintWithDelay("1. YES I WANT." Newline "2. NO, I DON'T." Newline);
    PrintWithDelay(Newline "ENTER YOUR CHOICE: ");
    choice_entry:
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
    fflush(stdin);
    scanf("%d", &choice);
    if(choice == 1) {
        Yellow();
        PrintWithDelay(Newline "ENTER THE NAME OF THE FILE IN XYZ.txt FORMAT: ");
        file_name_entry:
        fflush(stdin);
        gets(filename);
        if(IsFileNameEmpty(filename)) {
            Red();
            PrintWithDelay(Newline "FILE NAME CANNOT BE EMPTY. ENTER AGAIN: ");
            Yellow();
            goto file_name_entry;
        }
        if(DoesFileExist(filename)) {
            Red();
            PrintWithDelay(Newline "THE FILE ");
            PrintWithDelay(filename);
            PrintWithDelay(" ALREADY EXISTS." Newline);
            Blue();
            PrintWithDelay(Newline "DO YOU WANT TO REPLACE IT?" Newline "1. YES, REPLACE." Newline "2. NO, DO NOT REPLACE." Newline);
            PrintWithDelay(Newline "ENTER YOUR CHOICE: ");
            choice_entry1:
            FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
            fflush(stdin);
            while(1) {
                FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
                fflush(stdin);
                if(scanf("%d", &choice) == 1) {
                    break;
                } else {
                    while(getchar() != '\n');
                    PrintWithDelay(Newline "INVALID CHOICE. ENTER AGAIN: ");
                }
            }
            if(choice == 1) {
                fptr = fopen(filename, "w");
            } else if(choice == 2) {
                Yellow();
                PrintWithDelay(Newline "ENTER THE NEW NAME OF THE FILE: ");
                goto file_name_entry;
            } else {
                PrintWithDelay(Newline "INVALID CHOICE. ENTER AGAIN: ");
                goto choice_entry1;
            }
        } else {
            fptr = fopen(filename, "w");
        }
        int roll_no = 1, digits;
        Node *temp = Head;
        if(sortchoice == 1) {
            fprintf(fptr, "RESULTS AFTER SORTING BY NAME:" Newline Newline);
        } else if(sortchoice == 2) {
            fprintf(fptr, "RESULTS AFTER SORTING BY ENROLLMENT NUMBER:" Newline Newline);
        } else {
            fprintf(fptr, "RESULTS AFTER SORTING BY DATE OF BIRTH:" Newline Newline);
        }
        fprintf(fptr, "ROLL NO        ENROLL NO        DOB          NAME" Newline);
        fprintf(fptr, Newline);
        while(temp != NULL) {
            digits = CountDigit(temp->enroll_no);
            fprintf(fptr, "%d", roll_no);
            if(roll_no > 999) {
                PrintSpaces1(11, fptr);
                fprintf(fptr, "%lu", temp->enroll_no);
                PrintSpaces1(17-digits, fptr);
                if(temp->DD < 10 && temp->MM < 10) {
                    fprintf(fptr, "0%d-0%d-%d", temp->DD, temp->MM, temp->YYYY);
                } else if(temp->DD < 10) {
                    fprintf(fptr, "0%d-%d-%d", temp->DD, temp->MM, temp->YYYY);
                } else if(temp->MM < 10) {
                    fprintf(fptr, "%d-0%d-%d", temp->DD, temp->MM, temp->YYYY);
                } else {
                    fprintf(fptr, "%d-%d-%d", temp->DD, temp->MM, temp->YYYY);
                }
                PrintSpaces1(3, fptr);
            } else if(roll_no > 99) {
                PrintSpaces1(12, fptr);
                fprintf(fptr, "%lu", temp->enroll_no);
                PrintSpaces1(17-digits, fptr);
                if(temp->DD < 10 && temp->MM < 10) {
                    fprintf(fptr, "0%d-0%d-%d", temp->DD, temp->MM, temp->YYYY);
                } else if(temp->DD < 10) {
                    fprintf(fptr, "0%d-%d-%d", temp->DD, temp->MM, temp->YYYY);
                } else if(temp->MM < 10) {
                    fprintf(fptr, "%d-0%d-%d", temp->DD, temp->MM, temp->YYYY);
                } else {
                    fprintf(fptr, "%d-%d-%d", temp->DD, temp->MM, temp->YYYY);
                }
                PrintSpaces1(3, fptr);
            } else if(roll_no > 9) {
                PrintSpaces1(13, fptr);
                fprintf(fptr, "%lu", temp->enroll_no);
                PrintSpaces1(17-digits, fptr);
                if(temp->DD < 10 && temp->MM < 10) {
                    fprintf(fptr, "0%d-0%d-%d", temp->DD, temp->MM, temp->YYYY);
                } else if(temp->DD < 10) {
                    fprintf(fptr, "0%d-%d-%d", temp->DD, temp->MM, temp->YYYY);
                } else if(temp->MM < 10) {
                    fprintf(fptr, "%d-0%d-%d", temp->DD, temp->MM, temp->YYYY);
                } else {
                    fprintf(fptr, "%d-%d-%d", temp->DD, temp->MM, temp->YYYY);
                }
                PrintSpaces1(3, fptr);
            } else {
                PrintSpaces1(14, fptr);
                fprintf(fptr, "%lu", temp->enroll_no);
                PrintSpaces1(17-digits, fptr);
                if(temp->DD < 10 && temp->MM < 10) {
                    fprintf(fptr, "0%d-0%d-%d", temp->DD, temp->MM, temp->YYYY);
                } else if(temp->DD < 10) {
                    fprintf(fptr, "0%d-%d-%d", temp->DD, temp->MM, temp->YYYY);
                } else if(temp->MM < 10) {
                    fprintf(fptr, "%d-0%d-%d", temp->DD, temp->MM, temp->YYYY);
                } else {
                    fprintf(fptr, "%d-%d-%d", temp->DD, temp->MM, temp->YYYY);
                }
                PrintSpaces1(3, fptr);
            }
            fputs(temp->name, fptr);
            fprintf(fptr, Newline);
            roll_no++;
            PrintLine2(fptr);
            temp = temp->next;
        }
        fclose(fptr);
        Green();
        PrintWithDelay(Newline "FILE SAVED SUCCESSFULLY." Newline);
    } else {
        if(choice != 2) {
            PrintWithDelay(Newline "INVALID CHOICE. ENTER AGAIN: ");
            goto choice_entry;
        }
    }
    printf(Newline);
}
int IsFileNameEmpty(char filename[]) {
    if(filename[0] == '\0') {
        return 1;
    }
    return 0;
}
int DoesFileExist(char finename[]) {
    FILE *fptr;
    fptr = fopen(finename, "r");
    if(fptr == NULL) {
        return 0;
    }
    fclose(fptr);
    return 1;
}
void ToLower(char name[]) {
    int i = 0;
    while(name[i] != '\0') {
        if(name[i] >= 'A' && name[i] <= 'Z') {
            name[i] += 32;
        }
        i++;
    }
}
int CountDigit(unsigned long int n) {
    int count = 0;
    while(n > 0) {
        n/=10;
        count++;
    }
    return count;
}
void ReleaseMemory() {
    Node *temp = Head, *temp1;
    while(temp!=NULL) {
        temp1 = temp->next;
        free(temp);
        temp = temp1;
    }
    Head = NULL;
}
void PrintWithDelay(char str[]) {
    int i = 0;
    while(str[i] != '\0') {
        printf("%c", str[i]);
        Sleep(50);
        i++;
    }
}
void PrintWithDelay1(int count) {
    Yellow();
    PrintWithDelay("THE DATA OF ");
    Sleep(50);
    printf("%d ", count);
    PrintWithDelay("STUDENT(S) HAVE BEEN SUCCESSFULLY ENTERED." Newline Newline);
    PrintWithDelay("PRESS ENTER TO CONTINUE: ");
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
    getch();
}
void PrintLine() {
    printf(Newline "===============================================" Newline Newline);
}
void PrintLine1() {
    printf("----------------------------------------------------------------" Newline);
}
void PrintLine2(FILE *fptr) {
    fprintf(fptr, "----------------------------------------------------------------" Newline);
}
void PrintSpaces(int spaces) {
    for(int i=1; i<=spaces; i++) {
        printf(" ");
    }
}
void PrintSpaces1(int spaces, FILE *fptr) {
    for(int i=1; i<=spaces; i++) {
        fprintf(fptr, " ");
    }
}
void Red() {
    printf("\033[1;31m");
}
void Green() {
    printf("\033[0;32m");
}
void Yellow() {
    printf("\033[0;33m");
}
void Blue() {
    printf("\033[0;34m");
}
void purple() {
    printf("\033[0;35m");
}
void Cyan() {
    printf("\033[0;36m");
}
void ResetColor() {
    printf("\033[0m");
}