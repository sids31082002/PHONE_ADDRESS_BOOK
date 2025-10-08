#include <stdio.h>
#include "contact.h"


int main() 
{
    int choice;
    AddressBook addressBook;
    addressBook.contactCount = 0;
    loadContactsFromFile(&addressBook);  //to load the contacts at the start of the program always

    do {
        printf("\n\n\n----------Address Book Menu-----------\n\n");
        printf("  1. Create contact\n");
        printf("  2. Search contact\n");
        printf("  3. Edit contact\n");
        printf("  4. Delete contact\n");
        printf("  5. List all contacts\n");
    	printf("  6. Save contacts and exit\n\n");		
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();
        
        switch (choice) {
            case 1:
                createContact(&addressBook);
                break;
            case 2:
                searchContact(&addressBook);
                break;
            case 3:
                editContact(&addressBook);
                break;
            case 4:
                deleteContact(&addressBook);
                break;
            case 5:
                {
                    int sortChoice;  
                    if(addressBook . contactCount == 0){
                        printf("\n");
                        printf("Address book is empty to list any contacts. Try adding some contacts !!\n");
                        break;
                    }
                    do{
                        printf("\n---Select any option from below menu---\n\n  0. List by insertion order\n  1. List by name\n  2. List by phone number\n  3. List by email\n  4. Back to main menu\n\n");
                        printf("Enter the choice to list : ");
                        scanf("%d",&sortChoice);
                        if(sortChoice >= 0 && sortChoice < 4)
                            listContacts(&addressBook, sortChoice);
                        else if(sortChoice == 4) 
                            break;
                        else if(sortChoice > 4)
                        printf("Invalid choice , please try again");
                        
                    }while(sortChoice != 4);
                }    
                break;
            case 6:
                printf("Saving and Exiting...\n\n");
                saveContactsToFile(&addressBook);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);
    
       return 0;
}
