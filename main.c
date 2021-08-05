#include <stdio.h>
#include <stdlib.h>
#include "conio2.h"
#include "rlyres.h"
int main()
{
    int choice;
    int ticket_no;
    Passenger *ptr;
    char* pmob_no;
    char* ptrain_no;
    int *pticket_no;
    int result;
    add_trains();
    do
    {
        choice=enterchoice();
        switch(choice)
            {
            case 1:
                view_trains();
                getch();
                clrscr();
                break;
            case 2:
                ptr=get_passenger_details();
                clrscr();
                if(ptr!=NULL)
                {
                    ticket_no=book_ticket(*ptr);
                    if(ticket_no==-1)
                    {
                        textcolor(LIGHTRED);
                        printf("Booking failed!");
                    }
                    else
                    {
                        textcolor(LIGHTGREEN);
                        printf("Ticket successfully booked\nYou have been alloted with ticket no of %d",ticket_no);
                    }
                    textcolor(WHITE);
                    printf("\nPress any key to go back to main screen");
                    getch();
                    clrscr();
                }
                break;
            case 3:
                clrscr();
                ticket_no=accept_ticket_no();
                if(ticket_no!=0)
                    view_ticket(ticket_no);
                getch();
                clrscr();
                break;
            case 4:
                clrscr();
                pmob_no=accept_mob_no();
                if(pmob_no!=NULL)
                {
                    pticket_no=get_ticket_no(pmob_no);
                    view_all_tickets(pmob_no,pticket_no);
                }
                clrscr();
                break;
            case 5:
                view_all_bookings();
                clrscr();
                break;
            case 6:
                clrscr();
                ptrain_no=accept_train_no();
                if(ptrain_no!=NULL)
                {
                    view_booking(ptrain_no);
                }
                clrscr();
                break;
            case 7:
                clrscr();
                ticket_no=accept_ticket_no();
                if(ticket_no!=0)
                {
                    result=cancel_ticket(ticket_no);
                    if(result==0)
                    {
                        textcolor(RED);
                        gotoxy(1,25);
                        printf("Sorry! No tickets booked against ticket no %d",ticket_no);
                    }
                    else if(result==1)
                    {
                        textcolor(GREEN);
                        gotoxy(1,3);
                        printf("Ticket no %d succesfully cancelled\n",ticket_no);
                    }
                    else if(result==2)
                    {
                        textcolor(RED);
                        gotoxy(1,25);
                        printf("Sorry! Error in cancellation. Try Again!");
                    }
                }
                textcolor(WHITE);
                printf("\nPress any key to go back to main screen");
                getch();
                clrscr();
                break;
            case 8:
                clrscr();
                ptrain_no=accept_train_no();
                if(ptrain_no!=NULL)
                {
                    result=cancel_train(ptrain_no);
                    if(result==0)
                    {
                        textcolor(RED);
                        gotoxy(1,25);
                        printf("Sorry! No train booked against ticket no %s",ptrain_no);
                    }
                    else if(result==1)
                    {
                        textcolor(GREEN);
                        gotoxy(1,3);
                        printf("Train no %s succesfully cancelled\n",ptrain_no);
                    }
                    else if(result==2)
                    {
                        textcolor(RED);
                        gotoxy(1,25);
                        printf("Sorry! Error in cancellation. Try Again!");
                    }
                }
                textcolor(WHITE);
                printf("\nPress any key to go back to main screen");
                getch();
                clrscr();
                break;
            case 9:
                choice=0;
                break;
            default:
                textcolor(RED);
                printf("Wrong choice! Try Again\n");
                getch();
                clrscr();
                break;
            }
    }
            while(choice!=0);
    return 0;
}
