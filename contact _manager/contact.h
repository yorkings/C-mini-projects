#ifndef CONTACT_H
#define CONTACT_H

struct  Contact{
     char name[50];
    char phone[20];
    int age;
};

// function prototypes
void  add_contact(struct Contact **contacts,int *count);
void view_contacts(struct Contact *contacts,int *count);
void delete_contact(struct Contact **contacts,int *count);
void update_contact(struct Contact *contacts,int *count);

void save_contacts(struct Contact *contacts,int *count);
void load_contacts(struct Contact **contacts,int *count);

#endif
