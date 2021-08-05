#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "conio2.h"
#include "rlyres.h"
int enterchoice()
{
    textcolor(YELLOW);
    gotoxy(28,1);
    printf("RAILWAY RESERVATION SYSTEM\n");
    int i;
    for(i=0;i<80;i++)
    {
        printf("-");
    }
    printf("\n");
    int choice;
    textcolor(YELLOW);
    printf("Select an option:-\n1. View Trains\n2. Book Ticket\n3. View Ticket\n4. Search Ticket No\n5. View All Bookings\n6. View Train Bookings\n7. Cancel Ticket\n8. Cancel Train\n9. Quit\n\nEnter Choice:- ");
    scanf("%d",&choice);
    return choice;
    getch();
}
void add_trains()
{
    Train alltrains[4]={
              {"123","BPL","GWA",2100,1500},
              {"546","BPL","DEL",3500,2240},
              {"345","HBJ","AGR",1560,1135},
              {"896","HBJ","MUM",4500,3360},
              };
    FILE *fp=fopen("d:\\myproject\\alltrains.dat","rb");
    if(fp==NULL)
    {
        fp=fopen("d:\\myproject\\alltrains.dat","wb");
        fwrite(alltrains,4*sizeof(Train),1,fp);
        printf("File created and saved!\n");
    }
    else
        printf("File already present\n");
    fclose(fp);
}
void view_trains()
{
    int i;
    printf("TRAIN NO\tFROM\tTO\tFIRST AC FARE\tSECOND AC FARE\n");
     for(i=1;i<=80;i++)
        printf("-");
    FILE *fp=fopen("d:\\myproject\\alltrains.dat","rb");
    Train tr;
    while(fread(&tr,sizeof(tr),1,fp)==1)
    {
        printf("\n%s\t\t%s\t%s\t%d\t\t%d",tr.train_no,tr.from,tr.to,tr.fac_fare,tr.sac_fare);
    }
    printf("\n\n\n\n");
    fclose(fp);
}
int check_train_no(char *trainno)
{
    FILE *fp=fopen("d:\\myproject\\alltrains.dat","rb");
    Train tr;
    while(fread(&tr,sizeof(tr),1,fp)==1)
    {
          if(strcmp(tr.train_no,trainno)==0)
          {
                  fclose(fp);
                  return 1;
          }
    }
fclose(fp);
return 0;
}
int check_mob_no(char *mobno)  // diffrence
{
    if(strlen(mobno)!=10)
    {
        return 0;
    }
    while(*mobno!='\0')
    {
        if(isdigit(*mobno)==0)
            return 0;
        mobno++;
    }
    return 1;
}
Passenger * get_passenger_details()
{
    clrscr();
    textcolor(LIGHTGREEN);
    gotoxy(60,1);
    printf("Press 0 to exit");
    gotoxy(1,1);
    textcolor(YELLOW);
    printf("Enter passenger name:");
    static Passenger ps;
    fflush(stdin);
    fgets(ps.p_name,30,stdin);
    char *pos;
    pos=strchr(ps.p_name,'\n');
    *pos='\0';
    if(strcmp(ps.p_name,"0")==0)
    {
        textcolor(LIGHTRED);
        gotoxy(1,25);
        printf("Reservation Cancelled!");
        getch();
        textcolor(YELLOW);
        return NULL;
    }
    int valid;
    printf("Enter gender(M/F):");
    do
    {
        valid=1;
        fflush(stdin);
        scanf("%c",&ps.gender);
        if(ps.gender=='0')
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t\t");
            gotoxy(1,25);
            printf("Reservation Cancelled!");
            getch();
            textcolor(YELLOW);
            return NULL;
        }
        if(ps.gender!='M' && ps.gender!='F')
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("Error!Gender should be M or F(in uppercase)");
            valid=0;
            getch();
            gotoxy(19,2);
            printf(" \b");
            textcolor(YELLOW);
        }
    }while(valid==0);
    gotoxy(1,25);
    printf("\t\t\t\t\t\t\t\t");
    gotoxy(1,3);
        printf("Enter train number:");
        do
            {
                fflush(stdin);
                scanf("%s",ps.train_no);
                if(strcmp(ps.train_no,"0")==0)
                {
                    textcolor(LIGHTRED);
                    gotoxy(1,25);
                    printf("\t\t\t\t\t\t\t");
                    gotoxy(1,25);
                    printf("Reservation Cancelled!");
                    getch();
                    textcolor(YELLOW);
                    return NULL;
                }
                valid=check_train_no(ps.train_no);
                if(valid==0)
                {
                    textcolor(LIGHTRED);
                    gotoxy(1,25);
                    printf("Error! Invalid Train No");
                    getch();
                    gotoxy(20,3);
                    printf("\t\t\t\t\t\t");
                    gotoxy(20,3);
                    textcolor(YELLOW);
                }
            }while(valid==0);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t");

            gotoxy(1,4);
            printf("Enter travelling class(First AC-F,Second AC-S):");
            do
            {
            valid=1;
            fflush(stdin);
            scanf("%c",&ps.p_class);
            if(ps.p_class=='0')
            {
                textcolor(LIGHTRED);
                gotoxy(1,25);
                printf("\t\t\t\t\t\t\t");
                gotoxy(1,25);
                printf("Reservation Cancelled!");
                getch();
                textcolor(YELLOW);
                return NULL;
            }
            if(ps.p_class!='F' && ps.p_class!='S')
            {
                textcolor(LIGHTRED);
                gotoxy(1,25);
                printf("Error! Travelling class should be F or S (in uppercase)");
                valid=0;
                getch();
                gotoxy(48,4);
                printf(" \b");
                textcolor(YELLOW);
            }
            }while(valid==0);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t");

            gotoxy(1,5);
            printf("Enter address:");
            fflush(stdin);
            fgets(ps.address,30,stdin);
            pos=strchr(ps.address,'\n');
            *pos='\0';
            if(strcmp(ps.address,"0")==0)
            {
                textcolor(LIGHTRED);
                gotoxy(1,25);
                printf("\t\t\t\t\t\t\t");
                gotoxy(1,25);
                printf("Reservation Cancelled!");
                getch();
                textcolor(YELLOW);
                return NULL;
            }
            gotoxy(1,6);
            printf("Enter age:");
            do
            {
            valid=1;
            fflush(stdin);
            scanf("%d",&ps.age);
            if(ps.age==0)
            {
                textcolor(LIGHTRED);
                gotoxy(1,25);
                printf("\t\t\t\t\t\t\t");
                gotoxy(1,25);
                printf("Reservation Cancelled!");
                getch();
                textcolor(YELLOW);
                return NULL;
            }
            if(ps.age<0)
            {
                textcolor(LIGHTRED);
                gotoxy(1,25);
                printf("Error! Age should be positive");
                valid=0;
                getch();
                gotoxy(11,6);
                printf("\t\t\t\t\t\t\t");
                gotoxy(11,6);
                textcolor(YELLOW);
            }
            }while(valid==0);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t");
            gotoxy(1,7);
            printf("Enter mobile number:");
        do
            {
            fflush(stdin);
            fgets(ps.mob_no,12,stdin);
            pos=strchr(ps.mob_no,'\n');
            if(pos!=NULL)
            {
                *pos='\0';
            }
            if(strcmp(ps.mob_no,"0")==0)
            {
                textcolor(LIGHTRED);
                gotoxy(1,25);
                printf("\t\t\t\t\t\t\t");
                gotoxy(1,25);
                printf("Reservation Cancelled!");
                getch();
                textcolor(YELLOW);
                return NULL;
            }
            valid=check_mob_no(ps.mob_no);
            if(valid==0)
            {
                textcolor(LIGHTRED);
                gotoxy(1,25);
                printf("Error! Invalid mobile no.");
                getch();
                gotoxy(21,7);
                printf("\t\t\t\t\t\t\t\t\t");
                gotoxy(21,7);
                textcolor(YELLOW);
                }
            }while(valid==0);
            return &ps;
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t");
            gotoxy(1,1);
}
int last_ticket_no()
{
    FILE *fp=fopen("d:\\myproject\\allbookings.dat","rb");
    if(fp==NULL)
        return 0;
    Passenger pr;
    fseek(fp,-1L*sizeof(pr),SEEK_END);
    fread(&pr,sizeof(pr),1,fp);
    fclose(fp);
    return pr.ticketno;
}
int get_booked_ticket_count(char *train_no,char tc)
{
    FILE *fp=fopen("d:\\myproject\\allbookings.dat","rb");
    if(fp==NULL)
        return 0;
    Passenger pr;
    int count=0;
    while(fread(&pr,sizeof(pr),1,fp))
    {
        if(strcmp(pr.train_no,train_no)==0 && tc==pr.p_class)
            ++count;
    }
    fclose(fp);
    return count;
}
int book_ticket(Passenger p)
{
    int temp=get_booked_ticket_count(p.train_no,p.p_class);
    if(temp==30)
    {
        textcolor(LIGHTRED);
        printf("All Seats Full in train No %s in class %c",p.train_no,p.p_class);
        return -1;
    }
    int ticket_no=last_ticket_no()+1;
    p.ticketno=ticket_no;
    FILE *fp=fopen("d:\\myproject\\allbookings.dat","ab");
    if(fp==NULL)
    {
        textcolor(LIGHTRED);
        printf("Sorry! there's some issue, Please try again later");
        return -1;
    }
    fwrite(&p,sizeof(p),1,fp);
    fclose(fp);
    return ticket_no;
}
int accept_ticket_no()
{
    int valid;
    int ticket_no;
    clrscr();
    textcolor(LIGHTGREEN);
    gotoxy(60,1);
    printf("Press 0 to exit");
    gotoxy(1,1);
    textcolor(YELLOW);
    printf("Enter valid ticket number:");
            do
            {
            valid=1;
            fflush(stdin);
            scanf("%d",&ticket_no);
            if(ticket_no==0)
            {
                textcolor(LIGHTRED);
                gotoxy(1,25);
                printf("\t\t\t\t\t\t\t");
                gotoxy(1,25);
                printf("Cancelling Input...!");
                getch();
                textcolor(YELLOW);
                return 0;
            }
            if(ticket_no<0)
            {
                textcolor(LIGHTRED);
                gotoxy(1,25);
                printf("Error! Ticket number should be positive");
                valid=0;
                getch();
                gotoxy(21,1);
                printf("\t\t\t\t");
                gotoxy(21,1);
                textcolor(YELLOW);
            }
            }while(valid==0);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t");
            return ticket_no;
            clrscr();
}                                               // Comparison Completed
void view_ticket(int ticket_no)
{
    int i,found=0;
    FILE *fp=fopen("d:\\myproject\\allbookings.dat","rb");
    Passenger pr;
    if(fp==NULL)
    {
        gotoxy(1,25);
        textcolor(RED);
        printf("No bookings done yet");
        return;
    }
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
          if(pr.ticketno==ticket_no)
          {
                  gotoxy(28,3);
                textcolor(LIGHTBLUE);
                printf("Ticket Details With Ticket no. %d\n",ticket_no);
                textcolor(YELLOW);
                for(i=0;i<80;i++)
                {
                    printf("-");
                }
                printf("\n");
                printf("Name\tGender\t\tTrain No\tClass\tAddress Age\tMobile Number\n");
                for(i=1;i<=80;i++)
                    printf("-");
                textcolor(CYAN);
                printf("\n%s\t  %c\t\t %s\t\t%c\t%s\t%d\t%s",pr.p_name,pr.gender,pr.train_no,pr.p_class,pr.address,pr.age,pr.mob_no);
                found=1;
                break;
          }
    }
    if(!found)
    {
        printf("\nNo details of the ticket found ");
    }
    printf("\n");
    textcolor(YELLOW);
    for(i=1;i<=80;i++)
        printf("-");
fclose(fp);
textcolor(WHITE);
printf("\n\nPress enter to go into the main menu......");
return ;
}

char* accept_mob_no()
{
     static char mob_no[13];
     char *pos;
     int valid;
    textcolor(LIGHTGREEN);
    gotoxy(60,1);
    printf("Press 0 to exit");
    gotoxy(1,1);
    textcolor(YELLOW);
     printf("Enter valid mobile number:");
     do
     {
         fflush(stdin);
         fgets(mob_no,12,stdin);
         pos=strchr(mob_no,'\n');
         if(pos!=NULL)
         {
                *pos='\0';
         }
         if(strcmp(mob_no,"0")==0)
         {
                textcolor(LIGHTRED);
                gotoxy(1,25);
                printf("\t\t\t\t\t\t\t");
                gotoxy(1,25);
                printf("Cancelling Input!...");
                getch();
                textcolor(YELLOW);
                return NULL;
         }
         valid=check_mob_no(mob_no);
            if(valid==0)
            {
                textcolor(LIGHTRED);
                gotoxy(1,25);
                printf("Error! Invalid mobile no.");
                getch();
                gotoxy(27,1);
                printf("\t\t\t\t\t\t\t\t\t");
                gotoxy(27,1);
                textcolor(YELLOW);
                }
            }while(valid==0);
            clrscr();
            return mob_no;
}
int * get_ticket_no(char* p_mob_no)
{
    int count=0;
     FILE *fp=fopen("d:\\myproject\\allbookings.dat","rb");
     if(fp==NULL)
    {
        gotoxy(1,25);
        textcolor(RED);
        printf("No bookings done yet");
        return NULL;
    }
    Passenger pr;
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
        if(strcmp(pr.mob_no,p_mob_no)==0)
        {
            count++;
        }
    }
    if(!count)
    {
        fclose(fp);
        return NULL;
    }
    int *p=(int*)malloc((count+1)*sizeof(int));
    rewind(fp);
    int i=0;
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
        if(strcmp(pr.mob_no,p_mob_no)==0)
        {
            *(p+i)=pr.ticketno;
            i++;
        }
    }
    *(p+i)=-1;
    fclose(fp);
    return p;
}
void view_all_tickets(char* pmob_no,int* pticket_no )
{
    if(pticket_no==NULL)
    {
        textcolor(LIGHTRED);
        printf("Sorry! No ticket booked against mobile no %s",pmob_no);
        textcolor(WHITE);
        printf("\nPress any key to go back to main screen");
        textcolor(YELLOW);
        getch();
        return ;
    }
    printf("Following are tickets booked for the mobile number %s",pmob_no);
    int i;
    printf("\n\n Ticket Numbers\n");
    printf("--------------------------------");
    for(i=0;*(pticket_no+i)!=-1;i++)
    {
        printf("\n%d",*(pticket_no+i));
    }
    textcolor(WHITE);
    printf("\nPress any key to go back to main screen");
    textcolor(YELLOW);
    getch();
}
char* accept_train_no()
{
    int valid;
    static char train_no[20];
    gotoxy(60,1);
    textcolor(LIGHTGREEN);
    printf("Press 0 to Exit");
    gotoxy(1,1);
    textcolor(YELLOW);
    printf("Enter train number:");
        do
            {
            fflush(stdin);
            scanf("%s",train_no);
            if(strcmp(train_no,"0")==0)
            {
                textcolor(LIGHTRED);
                gotoxy(1,25);
                printf("\t\t\t\t\t\t\t");
                gotoxy(1,25);
                printf("Cancelling Input...!");
                getch();
                textcolor(YELLOW);
                return NULL;
            }
            valid=check_train_no(train_no);
            if(valid==0)
            {
                textcolor(LIGHTRED);
                gotoxy(1,25);
                printf("Error! Invalid Train No");
                getch();
                gotoxy(20,1);
                printf("\t\t\t\t\t\t");
                gotoxy(20,1);
                textcolor(YELLOW);
                }
            }while(valid==0);
            clrscr();
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t");
            return train_no;
}
void view_booking(char* train_no)
{
    FILE *fp=fopen("d:\\myproject\\allbookings.dat","rb");
     if(fp==NULL)
    {
        gotoxy(1,25);
        textcolor(RED);
        printf("No bookings done yet");
        return ;
    }
    Passenger pr;
    int i;
    int found=0;
    clrscr();
    gotoxy(28,1);
    textcolor(GREEN);
    printf("List of Passengers in train number %s\n",train_no);
    textcolor(RED);
    printf("Ticket NO\tCLASS\tName\t\tGENDER\tAGE\tMOBILE NO\n");
    textcolor(YELLOW);
    for(i=1;i<=80;i++)
    printf("-");
    int row=4;
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
          if(strcmp(pr.train_no,train_no)==0)
          {

                textcolor(CYAN);
                printf("\n%d\t\t%c\t%s\t\t%c\t%d\t%s\n",pr.ticketno,pr.p_class,pr.p_name,pr.gender,pr.age,pr.mob_no);
               // gotoxy(50,row);
               // printf("%c\t%d\t%s\n",pr.gender,pr.age,pr.mob_no);
                found=1;
                textcolor(YELLOW);
                for(i=1;i<=80;i++)
                printf("-");
                row=row+2;
          }
    }
    if(!found)
    {
        textcolor(RED);
        printf("\nNo details of the train %s found",train_no);
    }
    printf("\n");
fclose(fp);
textcolor(WHITE);
printf("\n\nPress any key to go into the main menu......");
getch();
return;
}
void view_all_bookings()
{
    FILE *fp=fopen("d:\\myproject\\allbookings.dat","rb");
     if(fp==NULL)
    {
        gotoxy(1,25);
        textcolor(RED);
        printf("No bookings done yet");
        return ;
    }
    Passenger pr;
    int i;
    clrscr();
    gotoxy(28,1);
    textcolor(GREEN);
    printf("List of all the Passengers\n\n");
    textcolor(RED);
    printf("Ticket NO\tCLASS\tName\t\t\GENDER\tAGE\tMOBILE NO\n");
    textcolor(YELLOW);
    for(i=1;i<=80;i++)
    printf("-");
    int row=4;
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
                textcolor(CYAN);
                printf("\n%d\t\t%c\t%s\t\t%c\t%d\t%s\n",pr.ticketno,pr.p_class,pr.p_name,pr.gender,pr.age,pr.mob_no);
                //gotoxy(50,row);
               // printf("%c\t%d\t%s\n",pr.gender,pr.age,pr.mob_no);
                textcolor(YELLOW);
                for(i=1;i<=80;i++)
                printf("- ");
                row=row+2;
    }
printf("\n");
fclose(fp);
textcolor(WHITE);
printf("\n\nPress enter to go into the main menu......");
getch();
return;
}
int cancel_ticket(int ticket_no)
{
    int result;
    Passenger pr;
    int found=0;
    FILE *fp=fopen("d:\\myproject\\allbookings.dat","rb");
     if(fp==NULL)
    {
        gotoxy(1,25);
        textcolor(RED);
        printf("No bookings done yet");
        fclose(fp);
        return -1;
    }
    FILE *ft=fopen("d:\\myproject\\temp.dat","wb");
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
        if(pr.ticketno==ticket_no)
        {
            found=1;
        }
        else
        {
            fwrite(&pr,sizeof(pr),1,ft);
        }
    }
    fclose(fp);
    fclose(ft);
    if(found==0)
    {
        remove("d:\\myproject\\temp.dat");
    }
    else
    {
        result=remove("d:\\myproject\\allbookings.dat");
        if(result!=0)
            return 2;
        result=rename("d:\\myproject\\temp.dat","d:\\myproject\\allbookings.dat");
        if(result!=0)
            return 2;
    }
    return found;
}
int cancel_train(char* train_no)
{
    int result;
    Passenger pr;
    int found=0;
    FILE *fp=fopen("d:\\myproject\\allbookings.dat","rb");
     if(fp==NULL)
    {
        gotoxy(1,25);
        textcolor(RED);
        printf("No bookings done yet");
        fclose(fp);
        return -1;
    }
    FILE *ft=fopen("d:\\myproject\\temp.dat","wb");
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
        if(strcmp(pr.train_no,train_no)==0)
        {
            found=1;
        }
        else
        {
            fwrite(&pr,sizeof(pr),1,ft);
        }
    }
    fclose(fp);
    fclose(ft);
    if(found==0)
    {
        remove("d:\\myproject\\temp.dat");
    }
    else
    {
        result=remove("d:\\myproject\\allbookings.dat");
        if(result!=0)
            return 2;
        result=rename("d:\\myproject\\temp.dat","d:\\myproject\\allbookings.dat");
        if(result!=0)
            return 2;
    }
    return found;
}
