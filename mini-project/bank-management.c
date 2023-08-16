//DS MINI PROJECT
//BANK MANAGEMENT USING LINKED LIST
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
FILE *fp;
typedef struct accinfo{
    char name[20];
    char dob[20];
    char phone[20];
    char accno[20];
    int deposit;
    struct accinfo *lptr,*rptr;
}Account;//aka node
Account *start=NULL;
void fordelay(int j)
{   int i,k;
    for(i=0;i<j;i++)
        k=i;
}
Account* getaccount()//its like getnode()
{
    char name[20];
    Account *newaccount; //like new1
    newaccount=(Account*)malloc(sizeof(Account));
    printf("\nEnter the NAME:\n");
    fflush(stdin);//THIS IS GOD The fflush(stdin) statement is used to clear any remaining characters in the input buffer before calling gets
    gets(newaccount->name);
    printf("Enter the DATE OF BIRTH\n");
    scanf("%s",newaccount->dob);
    printf("Enter the PHONE NUMBER\n");
    scanf("%s",newaccount->phone);
    printf("Enter the ACCOUNT NUMBER\n");
    scanf("%s",newaccount->accno);
    printf("Enter the DEPOSIT AMOUNT \n");
    scanf("%d",&newaccount->deposit);
    newaccount->lptr=newaccount->rptr=NULL;
    return newaccount;
}

//congrats the node is created !! now the part is to insert it in so ill be using insertbegin
void InsertAccount(){ //Insert End cuz first come first served
    Account *newaccount,*temp=start;
    newaccount=getaccount();
    if(!start){
        start=newaccount;
        return;
    }
    while(temp->rptr){
        temp=temp->rptr;
    }
    temp->rptr=newaccount;
    newaccount->lptr=temp;
}
void StoreAccounts()
{
    FILE *fp=fopen("bank.txt","wb");
    if(!fp){
        printf("File could not be opened!");
        return;
    }
    Account *temp=start;
    while(temp){
        fprintf(fp, "NAME: %s\n",temp->name);
        fprintf(fp, "DATE OF BIRTH: %s\n", temp->dob);
        fprintf(fp,"PHONE NUMBER:%s\n",temp->phone);
        fprintf(fp, "ACCOUNT NUMBER: %s\n",temp->accno);
        fprintf(fp, "DEPOSIT AMOUNT: %d\n", temp->deposit);
        fprintf(fp,"*\n");
        temp=temp->rptr;
    }
    fclose(fp);
}
//congrats your info has been successfully inserted inside the node !!
void displayaccno(){
    Account *temp=start;
    while(temp){
        printf("%s\n",temp->accno);
        temp=temp->rptr;
    }
}
void display(){
    int i=0;
    Account *temp=start;
    if (start==NULL){
        printf("The linked List is empty\n");
        return;
    }
    printf("\nTHE BANK INFORMATION IS:\n");
    printf("**\n");
    while(temp){
        printf("BANK INFO %d.\n",i+1);
        printf("NAME:%s\n",temp->name);
        printf("DATE OF BIRTH:%s\n",temp->dob);
        printf("PHONE NUMBER:%s\n",temp->phone);
        printf("ACCOUNT NUMBER:%s\n",temp->accno);
        printf("DEPOSITED AMOUNT:%d\n",temp->deposit);
        printf("**\n");
        temp=temp->rptr;
        i++;
    }
    StoreAccounts();
}
void deposit() {
    int moneydeposit = 0, flag = 0;
    char depositacc[20];
    try:
    printf("Enter the ACCOUNT NUMBER you want to DEPOSIT\n");
    displayaccno();
    scanf("%s", depositacc);
    //string comparision using linked list
    Account* temp=start;
    while(temp){
        if(strcmp(temp->accno, depositacc) == 0){
            flag = 1;
            printf("YOUR ACCOUNT EXIST IN OUR DATABASE!!!!\n");
            printf("YOU ACCOUNT NUMBER :%s \t BALANCE :%d\n",temp->accno,temp->deposit);
            printf("Enter the amount you want to Enter to %s\n", temp->accno);
            scanf("%d", &moneydeposit);
            temp->deposit += moneydeposit;
            printf("AMOUNT ADDED SUCCESSFULLY!!!");
            return;
        }
        temp=temp->rptr;
    }
    if(flag==0) {
        printf("ACCOUNT %s DOESNT EXIST IN OUR DATABASE PLEASE TRY AGAIN \n", depositacc);
        goto try;
    }
}
void withdraw(){
    int withdraw,flag=0;
    char withdrawacc[20];
    Account* temp=start;
    try:
    printf("\nEnter the ACCOUNT NUMBER you want to WITHDRAW\n");
    displayaccno();
    scanf("%s",withdrawacc);
    while(temp){
        if(strcmp(temp->accno, withdrawacc) == 0){
            flag=1;
            printf("YOUR ACCOUNT EXIST IN OUR DATABASE!!!!\n");
            start:
            printf("YOU ACCOUNT NUMBER :%s \t BALANCE :%d\n",temp->accno,temp->deposit);
            printf("Enter the AMOUNT you want to WITHDRAW\n");
            scanf("%d",&withdraw);
            if(temp->deposit<withdraw) {
                printf("INSUFFICIENT FUNDS PLEASE TRY AGAIN!!!!!\n");
                goto start;
            }
            else {
                temp->deposit -= withdraw;
                printf("AMOUNT WITHDRAWN SUCCESSFULLY\n");
            }
            return;
        }
        temp=temp->rptr;
    }
    if(flag==0){
        printf("ACCOUNT %s DOESNT EXIST IN OUR DATABASE PLEASE TRY AGAIN \n",withdrawacc);
        temp=start;//super important to reinitalize dont forget
        goto try;
    }

}
int checkacc(char editacc[]){
    Account *temp=start;
    while(temp){
        if(strcmp(temp->accno, editacc) == 0){
            return 1;
        }
        temp=temp->rptr;
    }
    return 0;
}
void edit(){
    char editname[20], editdob[20], editphone[20], editaccno[20], editacc[20];
    int editch, ch;
    Account* temp = start;
    again:
    printf("\nEnter the ACCOUNT NUMBER you want to EDIT\n");
    displayaccno();
    scanf("%s", editacc);
    int key=checkacc(editacc);//just for edit cuz we are using do while loop
    if(key==0){
        printf("ACCOUNT NUMBER %s DOESNT MATCH WITH OURDATA BASE PLEASE TRY AGAIN \n",editacc);
        goto again;
    }
    else {
        do {
            while (temp) {
                if (strcmp(temp->accno, editacc) == 0) {
                    try:
                    printf("1.NAME=%s\n2.DATE OF BIRTH=%s\n3.PHONE NUMBER=%s\n4.ACCOUNT NUMBER=%s\n", temp->name,
                           temp->dob,
                           temp->phone, temp->accno);
                    printf("Enter the option (1-4) you want to EDIT\n");
                    scanf("%d", &editch);
                    if (editch == 1) {
                        printf("Enter the NAME:\n");
                        fflush(stdin);
                        gets(editname);
                        strcpy(temp->name, editname);
                    } else if (editch == 2) {
                        printf("Enter the DATE OF BIRTH:\n");
                        scanf("%s", editdob);
                        strcpy(temp->dob, editdob);
                    } else if (editch == 3) {
                        printf("Enter the PHONE NUMBER:\n");
                        scanf("%s", editphone);
                        strcpy(temp->phone, editphone);
                    } else if (editch == 4) {
                        printf("Enter the ACCOUNT NUMBER:\n");
                        scanf("%s", editaccno);
                        strcpy(temp->accno, editaccno);
                    } else {
                        printf("INVALID INPUT PLEASE TRY AGAIN \n");
                        goto try;
                    }
                    printf("do you want to CONTINUE EDITING ? If YES then press 1 or WANT TO RETURN TO MAIN MENU press 0\n");
                    scanf("%d", &ch);
                    if (ch == 1) {
                        goto try;
                    }
                }
                temp = temp->rptr;
            }
        } while (ch == 1);
    }
}
void delete() {
    Account *temp = start;
    int flag = 0, count = 0;
    char deleteacc[20];

    while (count < 3) { // limit the number of retries to 3
        displayaccno();
        printf("Enter the ACCOUNT NUMBER you want to DELETE from the DATABASE\n");
        scanf("%s", deleteacc);

        while (temp) {
            if (strcmp(temp->accno, deleteacc) == 0) {
                flag = 1;
                printf("DELETION SUCCESS !!!\n");
                printf("DELETED BANK DETAILS INFO\n");
                printf("NAME=%s\nDATE OF BIRTH=%s\nPHONE NUMBER:%s\nACCOUNT NUMBER:%s\nDEPOSITED AMOUNT:%d\n",temp->name,temp->dob,temp->phone,temp->accno,temp->deposit);

                if (temp == start) {
                    start = temp->rptr;
                    if (start != NULL) {
                        start->lptr = NULL;
                    }
                    free(temp);
                } else if ((temp->lptr != NULL) && (temp->rptr != NULL)) {
                    temp->lptr->rptr = temp->rptr;
                    temp->rptr->lptr = temp->lptr;
                    free(temp);
                } else if (temp->rptr == NULL) {
                    temp->lptr->rptr = NULL;
                    free(temp);
                }
                return;
            }
            temp = temp->rptr;
        }
        if (flag == 0) {
            printf("THE ACCOUNT NUMBER %s DOESNT EXIST IN OUR DATABASE PLEASE TRY AGAIN\n", deleteacc);
            temp = start; //reinitialize
            count++;
        }
    }
    printf("MAXIMUM NUMBER OF TRIES REACHED. PLEASE TRY AGAIN LATER\n");
}

int main() {
    int i, n, exitchoice;
    char password[20] = "RNSIT", pass[20];
    retrypass:
    printf("Enter the password for access: ");
    scanf("%s", pass);
    printf("\nPLEASE WAIT CHECKING DATABASE");
    for (i = 0; i <= 6; i++) {
        fordelay(100000000000000);
        printf(".");
    }
    if (strcmp(pass, password) == 0) {
        printf("\n\nPassword Match!\nLOADING MAIN MENU");
        for (i = 0; i <= 6; i++) {
            fordelay(100000000000000);
            printf(".");
        }
        while (1) {
            exitreturn:
            printf("\n\n\n\t\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2 WELCOME TO THE MAIN MENU \xB2\xB2\xB2\xB2\xB2\xB2\xB2");
            printf("\n\n\t\t1. Create new account\n\t\t2. Display details\n\t\t3. Deposit to existing account\n\t\t4. Withdraw from an existing account\n\t\t5. Edit info from an existing account\n\t\t6. Removing existing account\n\t\t7. Exit\n\n\n\n\n\t\t Enter your choice: ");
            int choice;
            scanf("%d", &choice);
            switch (choice) {
                case 1:
                    printf("Enter the number of ACCOUNTS you want to make\n");
                    scanf("%d", &n);
                    for (i = 0; i < n; i++) {
                        printf("\n*DETAILS OF PERSON %d*", i + 1);
                        InsertAccount();
                        printf("*");
                    }
                    StoreAccounts();
                    break;
                case 2:
                    display();
                    break;
                case 3:
                    deposit();
                    break;
                case 4:
                    withdraw();
                    break;
                case 5:
                    edit();
                    break;
                case 6:
                    delete();
                    break;
                case 7:
                tryit:
                    printf("DO YOU WANT TO EXIT ? If YES then press 1 else 0 to continue back to MAIN MENU\n");
                    scanf("%d", &exitchoice);
                    if (exitchoice == 1)
                        exit(0);
                    else if (exitchoice == 0) {
                        goto exitreturn;
                    }
                    else {
                        printf("Enter valid choice either 1 or 0 please try again\n");
                        goto tryit;
                    }
                default:printf("INVALID INPUT PLEASE TRY AGAIN");
                    goto exitreturn;
            }
        }
    }
    else {
        printf("\nPASSWORD DOESNT MATCH PLEASE TRY AGAIN\n");
        goto retrypass;
    }
    return 0;
}