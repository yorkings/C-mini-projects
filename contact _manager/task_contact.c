#include<stdlib.h>
#include <string.h>
#include <stdio.h>
#include "contact.h"

void add_contact(struct Contact **contacts,int *count){
    struct Contact *temp=realloc(*contacts, (*count + 1) * sizeof(struct Contact));
    if (!temp) {
        printf( "Error: Failed to allocate memory for new contact.\n");
        return;
    }
    *contacts = temp;
    printf("Enter name: ");
    fgets((*contacts)[*count ].name, sizeof((*contacts)[*count ].name), stdin);
    (*contacts)[*count ].name[strcspn((*contacts)[*count ].name, "\n")] = 0;
    printf("Enter phone: ");
    fgets((*contacts)[*count ].phone, sizeof((*contacts)[*count ].phone), stdin);
    (*contacts)[*count ].phone[strcspn((*contacts)[*count ].phone, "\n")] = 0;
    printf("Enter age: ");
    scanf("%d", &(*contacts)[*count ].age);
    while (getchar() != '\n'); // clear buffer
    (*count)++;
    printf("Contact added!\n");
}

void view_contacts(struct Contact *contacts,int *count){
    if(*count==0){
        printf("No contacts to display.\n");
        return;
    }
    printf("\n--- Contacts ---\n");
    for(int i=0;i<*count;i++){
        printf("%d. %s | %s | %d\n",i+1,contacts[i].name,contacts[i].phone,contacts[i].age);
    }
}

void delete_contact(struct Contact **contacts,int *count){
    if(*count==0){
        printf("No contacts to delete.\n");
        return;
    }
    int del;
    printf("Enter contact number to delete: ");
    scanf("%d",&del);
    while (getchar() != '\n'); // clear buffer
    if(del<1 || del>*count){
        printf("Invalid contact number.\n");
        return;
    }
    for(int i=del-1;i<*count-1;i++){
        (*contacts)[i]=(*contacts)[i+1];
    }
    struct Contact *temp=realloc(*contacts, (*count - 1) * sizeof(struct Contact));
    if (!temp && *count > 1) {
        printf( "Error: Failed to reallocate memory after deleting contact.\n");
        exit(EXIT_FAILURE);
    }
    *contacts = temp;
    (*count)--;
    printf("Contact deleted.\n");
}   

void update_contact(struct Contact *contacts,int *count){
    if(*count==0){
        printf("No contacts to update.\n");
        return;
    }
    int upd;
    printf("Enter contact number to update: ");
    scanf("%d",&upd);
    while (getchar() != '\n'); // clear buffer
    if(upd<1 || upd>*count){
        printf("Invalid contact number.\n");
        return;
    }
    printf("Enter new name: ");
    fgets(contacts[upd-1].name, sizeof(contacts[upd-1].name), stdin);
    contacts[upd-1].name[strcspn(contacts[upd-1].name, "\n")] = 0;
    printf("Enter new phone: ");
    fgets(contacts[upd-1].phone, sizeof(contacts[upd-1].phone), stdin);
    contacts[upd-1].phone[strcspn(contacts[upd-1].phone, "\n")] = 0;
    printf("Enter new age: ");
    scanf("%d", &contacts[upd-1].age);
    while (getchar() != '\n'); // clear buffer
    printf("Contact updated.\n");
}   

void save_contacts(struct Contact *contacts,int *count){
    FILE *file=fopen("contacts.dat","wb");
    if(file==NULL){
        printf("Error: Could not open file for writing.\n");
        return;
    }
    fwrite(count,sizeof(int),1,file);
    fwrite(contacts,sizeof(struct Contact),*count,file);
    fclose(file);
}   
void load_contacts(struct Contact **contacts,int *count){
    FILE *file=fopen("contacts.dat","rb");
    if(file==NULL){
        printf("No saved contacts found.\n");
        return;
    }
    fread(count,sizeof(int),1,file);
    struct Contact *temp=realloc(*contacts, (*count) * sizeof(struct Contact));
    if (!temp && *count > 0) {
        printf( "Error: Failed to allocate memory for loading contacts.\n");
        exit(EXIT_FAILURE);
    }
    *contacts = temp;
    fread(*contacts,sizeof(struct Contact),*count,file);
    fclose(file);
}

void load_range(struct Contact **contacts, int *count, int start, int end) {

    FILE *file = fopen("contacts.dat", "rb");
    if (file == NULL) {
        printf("No file found.\n");
        return;
    }

    int total;
    fread(&total, sizeof(int), 1, file);

    if (start < 0 || end >= total || start > end) {
        printf("Invalid range.\n");
        fclose(file);
        return;
    }

    int n = end - start + 1;

    // Allocate only needed memory
    *contacts = malloc(n * sizeof(struct Contact));

    // THIS IS THE KEY PART
    fseek(file, sizeof(int) + start * sizeof(struct Contact), SEEK_SET);

    fread(*contacts, sizeof(struct Contact), n, file);

    *count = n;

    fclose(file);

    printf("Loaded contacts %d to %d\n", start + 1, end + 1);
}