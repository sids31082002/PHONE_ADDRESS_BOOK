#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100

typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact;

typedef struct {
    Contact contacts[MAX_CONTACTS];
    int contactCount;
} AddressBook;

void createContact(AddressBook *addressBook);
void searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook, int sortCriteria);
void saveContactsToFile(AddressBook *AddressBook);
void loadContactsFromFile(AddressBook *addressBook);
int valid_email(char *email);
int valid_phone(char *phone);
int valid_name(char *name_str);
void search_by_name(AddressBook *addressBook,char *,int *,int *);
void search_by_phone(AddressBook *addressBook,char *,int *,int *);
void search_by_email(AddressBook *addressBook,char *,int *,int *);
int duplicate_phone(AddressBook *addressBook,const char *);
int duplicate_email(AddressBook *addressBook,const char *);

#endif
