#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"

int main(){
    struct  Contact *contacts=NULL;
    int count=0;
    load_contacts(&contacts,&count);
    int choice;
    do{
        printf("\n--- Contact Manager ---\n");
        printf("1. Add Contact\n");
        printf("2. View Contacts\n");
        printf("3. Update Contact\n");
        printf("4. Delete Contact\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d",&choice);
        while(getchar()!='\n'); // clear buffer
        switch(choice){
            case 1:
                add_contact(&contacts,&count);
                break;
            case 2:
                view_contacts(contacts,&count);
                break;
            case 3:
                update_contact(contacts,&count);
                break;
            case 4:
                delete_contact(&contacts,&count);
                break; 
            case 5:
                save_contacts(contacts,&count);
                printf("Contacts saved.Have a nice day!\n");
                free(contacts);
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Try again.\n"); 
        }

    }while (choice!=5);
        
}