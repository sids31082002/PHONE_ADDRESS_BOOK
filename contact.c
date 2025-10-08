#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<ctype.h>
#include "contact.h"
#include "file.h"
#include<stdio_ext.h>

void listContacts(AddressBook *addressBook, int sortCriteria) 
{
/*
 * Function: listContacts
 * -----------------------
 * Displays the list of contacts from the address book.
 *
 * Parameters:
 *   addressBook   - pointer to the AddressBook structure
 *   sortCriteria  - determines the way of sorting:
 *                     0 → Insertion order (no sorting)
 *                     1 → Sorted by Name (A–Z)
 *                     2 → Sorted by Phone number
 *                     3 → Sorted by Email
 *   - If no contacts exist, a message is displayed instead.
 *   - A addressBook -> contacts[i]orary copy of the contacts is made so that the
 *     original insertion order remains unchanged.
 *   - If sortCriteria = 0, the contacts are displayed in the
 *     order they were added.
 *   - sortCriteria = 1 (sort by name) using bubble sort and strcase cmp
 *   - sortCriteria = 2 (sort by phone) using bubble sort and strcase cmp
 *   - sortCriteria = 3 (sort by email) using bubble sort and strcase cmp
 *   - Based on the criteria selected, Bubble Sort is applied to the copy of the contacts created
 *     to sort the contacts
 *   - The sorted (or unsorted) list is then printed to stdout.
 *   - The function only displays contacts.
 */
 
    // Contact addressBook -> contacts[i][addressBook -> contactCount];
    // for(int i = 0;i < addressBook -> contactCount;i++){
    //     addressBook -> contacts[i][i] = addressBook -> contacts[i];
    // }
    
    if(sortCriteria == 1){     //sort by name
        for(int i = 0; i < addressBook -> contactCount - 1;i++){
            for(int j = 0;j < addressBook -> contactCount - i - 1;j++)
            {
                if( strcasecmp(addressBook -> contacts[j].name,addressBook -> contacts[j+1].name) > 0 ){
                    Contact swap = addressBook -> contacts[j];
                    addressBook -> contacts[j] = addressBook -> contacts[j+1];
                    addressBook -> contacts[j+1] = swap;
                }
            }
        }
    }

    if(sortCriteria == 2){     //sort by phone
        for(int i = 0; i < addressBook -> contactCount - 1;i++){
            for(int j = 0;j < addressBook -> contactCount - i - 1;j++){
                if( strcasecmp(addressBook -> contacts[j].phone,addressBook -> contacts[j+1].phone) > 0){
                    Contact swap= addressBook -> contacts[j];
                    addressBook -> contacts[j] = addressBook -> contacts[j+1];
                    addressBook -> contacts[j+1] = swap;
                }
            }
        }
    }

    if(sortCriteria == 3){     //sort by mail
        for(int i = 0; i < addressBook -> contactCount - 1;i++){
            for(int j = 0;j < addressBook -> contactCount - i - 1;j++){
                if(strcasecmp(addressBook -> contacts[j].email,addressBook -> contacts[j+1].email) > 0){
                    Contact swap= addressBook -> contacts[j];
                    addressBook -> contacts[j] = addressBook -> contacts[j+1];
                    addressBook -> contacts[j+1] = swap;
                }
            }
        }
    } 
    //if sortCriteria = 0 , We can skip sorting !! 
    if(addressBook -> contactCount > 0){
        printf("\n");
         for(int i = 0;i < addressBook -> contactCount;i++){
            printf("contact of person %d\n",i + 1);
            printf("NAME  : %s\n",addressBook -> contacts[i].name);
            printf("PHONE : %s\n",addressBook -> contacts[i].phone);
            printf("Email : %s\n",addressBook -> contacts[i].email);
            printf("\n");
        }
    }
    // Sort contacts based on the chosen criteria
    
}

void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */ 
    
    /*
 * createContact
 * ------------------------
 * Adds a new contact to the AddressBook.
 * - Prompts user for name, phone, and email and validates 3 of them using seperate validate functions.
 * - if the email and phone is valid ,we check for duplicates (phone/email) creation by using seperate duplicate functions for email and phone
 * - Saves contact and increments contactCount on successful creation of contact.
 */

    char name_str[20], phone[11], email[30];

    label: 
        printf("Enter the name :");
        scanf("%19[^\n]", name_str);
        __fpurge(stdin);

        int ret = valid_name(name_str);
        if(ret != 0) {
            goto label;   
        }

        strcpy(addressBook->contacts[addressBook->contactCount].name , name_str);
        //get name and validate

    labell:  
        printf("Enter the phone number :");
        scanf(" %[^\n]", phone);

        ret = valid_phone(phone);
        if(ret != 0){
            goto labell;
        }
        
        if(duplicate_phone(addressBook, phone)) {
                return;   
        }
        
    strcpy(addressBook->contacts[addressBook->contactCount].phone, phone);    
    
    //get phone num and validate

    
    labelll:
        printf("Enter the email :");
        scanf(" %29[^\n]",email);
        ret = valid_email(email);
        if(ret != 0){
            goto labelll;
        }

        if(duplicate_email(addressBook,email))
                return;
        
    //get the email and validate
    strcpy(addressBook->contacts[addressBook->contactCount].email , email);

    addressBook->contactCount++;
    printf("\n");
    printf("The new contact has been successfully created !!\n");
    printf("\n");
   
}


void searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */

    /*
 * searchContact
 * ------------------------
 * Provides a menu to search contacts in the AddressBook , if no contacts presents shows error message.
 * - Allows searching by name, phone, or email.
 * - Calls the respective search functions .
 * - if found = 0 , prints no contact found and returns to main menu.
 * - if found = 1 , contact is found . 
 * - Displays matching contacts if found.
 * - Shows an error message if no match exists.
 * - Returns to the main menu when chosen.
 */

    char name_str[20], phone[11], email[30];
    int match[100];
    int option;
    printf("\n");
    if(addressBook -> contactCount == 0){
        printf("Contact list is empty to search . Try adding some contacts !!\n");
        return ;
    }
    
    do{
        printf("\n");
        printf("--Search Menu---\n\n  1. Search by name\n  2. Search by phone\n  3. Search by email\n  4. Back to main menu\n\n");
        printf("Enter the option to search :");
        scanf("%d",&option);
        printf("\n");
        switch(option)
        {
            case 1:
            {
                int found = 0;
                printf("Enter the name to search : ");
                scanf(" %[^\n]",name_str);
                search_by_name(addressBook,name_str,&found,match);
                if(found > 0){
                    return;
                }
                if(found == 0){
                    printf("No contact found , please try again !!");
                }
                break;
            }
            case 2:
            {
                int found = 0;
                printf("Enter the phone number to search : ");
                scanf(" %[^\n]",phone);
                search_by_phone(addressBook,phone,&found,match);
                if(found > 0){
                    return;
                }
                if(found == 0){
                    printf("No contact found , please try again !!");
                }
                break;
            }
            case 3:
            {
                int found = 0;
                printf("Enter the email to search : ");
                scanf(" %[^\n]",email);
                search_by_email(addressBook,email,&found,match);
                if(found > 0){
                    return;
                }
                if(found == 0){
                    printf("No contact found , please try again !!");
                }
                break;
            }
            case 4:
                return;
            default : 
                printf("Invalid option selected , please try again !!");
        }

    }while(option < 4);
}

void editContact(AddressBook *addressBook){
	/* Define the logic for Editcontact */

    /*
 * editContact
 * ------------------------
 * Provides a menu to edit existing contacts in the AddressBook.
 * - If no contacts exist, shows an error message and exit.
 * - Allows editing by searching contact through name, phone, or email by using valid functions for name phone and email.
 * - User must select a contact if multiple contacts with eneterd name phone or email are found.
 * - An array named track_index is used to track the (serial no)serial number of the contacts displayed after searching.
 * - If the serial number selected is beyond what is displayed , displays an error message.
 * - Validates the new input (name, phone, or email) before updating.
 * - Prevents duplicates by checking existing contacts before updating using the helper function dupicate_phone and duplicate_email.
 * - Displays success message after successful edit.
 * - Returns to the main menu when chosen.
 */

    char name_str[20], phone[11], email[30];
    int track_index[100];
    int found = 0;

    if(addressBook -> contactCount == 0){
        printf("Contact list is empty , try adding some contacts to edit !!\n");
        return;
    }
    printf("\nwhich detail you would like to update?\n");
    int choice , serial_no; //serial_no - to select which contact to edit  //choice - to selct a choice from edit menu
    do{
        printf("\n");
        printf("---Edit menu---\n\n  1. Edit by name\n  2. Edit by phone\n  3. Edit by email\n  4. Back to main menu\n\n");
        printf("Select a choice :");
        scanf("%d",&choice);
        getchar();
        switch(choice){
            case 1:
            {
                printf("Enter the name of the contact you want to edit(or type exit to stop): ");
                scanf("%[^\n]",name_str);
                __fpurge(stdin);
                if(strcmp(name_str,"exit")==0){
                    return;
                }
                search_by_name(addressBook,name_str,&found,track_index);
                if(found == 0){
                    printf("No contact found to edit, please try again !!");
                    return;
                }
                do{
                    printf("Enter the serial no of the contact you want to edit or enter 0 to cancel : ");
                    scanf("%d",&serial_no);
                    if(serial_no == 0){
                        return ; 
                    }
                    if(serial_no > 0 && serial_no <= found){
                        do{
                            printf("\nEnter the new name to update in the contact : ");
                            scanf(" %[^\n]",name_str);
                            if(valid_name(name_str)){
                                printf("\nEnter a valid name to update the contact !!\n");
                                continue;
                            }
                            else
                                break;
                        }while(1);
                        strcpy(addressBook->contacts[track_index[serial_no - 1]].name , name_str);   
                        printf("Contact has been edited successfully !!");
                        return;
                    } 
                    printf("Invalid choice , please try again!!");
                }while(1);
                break;
            }
            case 2:            
                {
                printf("Enter the phone number of the contact you want to edit(or type exit to stop): ");
                scanf("%[^\n]",phone);

                if(strcmp(phone,"exit") == 0){
                    return ;
                }
                search_by_phone(addressBook,phone,&found,track_index);
                if(found == 0){
                    printf("No contact found to edit, please try again !!");
                    return;
                }
                do{
                    printf("Enter the serial no of the contact you want to edit or enter 0 to cancel : ");
                    scanf("%d",&serial_no);
                    if(serial_no == 0){
                        return ; 
                    }
                    if(serial_no > 0 && serial_no <= found){
                        do{
                            printf("\nEnter the new phone number to update in the contact : ");
                            scanf(" %[^\n]",phone);
                            if(valid_phone(phone)){
                                printf("\nEnter a valid phone number to update the contact !!\n");
                                continue;
                            }
                            else{
                                if(duplicate_phone(addressBook,phone)){
                                    return;
                                }
                                break;
                            }    
                        }while(1);
                        strcpy(addressBook->contacts[track_index[serial_no - 1]].phone , phone);   
                        printf("Contact has been edited successfully !!");
                        return;
                    } 
                    printf("Invalid choice , please try again!!");
                }while(1);
                break;
            }
            case 3:
            {
                printf("Enter the email of the contact you want to edit(or type exit to stop): ");
                scanf("%[^\n]",email);

                if(strcmp(email,"exit") == 0){
                    return ;
                }
                 
                search_by_email(addressBook,email, &found, track_index);
                if(found == 0){
                    printf("No contact found to edit, please try again !!");
                    return;
                }
                do{
                    printf("\nEnter the serial no of the contact you want to edit or enter 0 to cancel : ");
                    scanf("%d",&serial_no);
                    if(serial_no == 0){
                        return;
                    }
                    if(serial_no > 0 && serial_no <= found){  
                        do{
                            printf("\nEnter the new email to update in the contact : ");
                            scanf(" %[^\n]",email);
                            if(valid_email(email)){
                                printf("\nEnter a valid email to update the contact !!\n");
                                continue;
                            }
                            else{
                                if(duplicate_email(addressBook,email)){
                                    return;
                                }
                                break;
                            }    
                        }while(1);
                        strcpy(addressBook->contacts[track_index[serial_no - 1]].email , email);   
                        printf("\nContact has been edited successfully !!\n");
                        return;
                    }
                    printf("Invalid choice , please try again!!\n");
                }while(1);
                break;
            }

            case 4:
                return;
            default:
                printf("\nInvalid choice ,Try again!!");
                continue;
        } 
    }while(1);
}
   

void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */

    /*
 * deleteContact
 * ------------------------
 * Provides a menu to delete contacts from the AddressBook.
 * - If no contacts exist, shows an error message and exits.
 * - Allows searching by name, phone, or email before deletion.
 * - Displays matching contacts and requires the user to pick one 
 *   using a serial number.
 * - An array named track_index is used to track the (serial no)serial number of the contacts displayed after searching.
 * - If the serial number selected is beyond what is displayed , displays an error message.
 * - Asks for confirmation (Y/N) before deleting the selected contact.
 * - If confirmed, shifts remaining contacts  one index backwards , to maintain array order.
 * - Prints success message after deletion, or error if deletion doesnt happen.
 * - Prints invalid inputs if wrong serial number is entered or wrong character is entered during confirmation.
 * - Returns to the main menu when chosen.
 */

    char name_str[20], phone[11], email[30];
    int track_index[100];
    int found = 0;

    if(addressBook -> contactCount == 0){
        printf("Contact list is empty , try adding some contacts to delete !!\n");
        return;
    }
    printf("\nSearch a contact to delete --\n");
    int choice , serial_no; //serial_no - to select which contact to delete  //choice - to selct a choice from edit menu
    do{
       printf("\n");
        printf("---Delete menu---\n\n  1. search by name to delete\n  2. Search by phone to delete\n  3. Search by email to delete\n  4. Back to main menu\n\n");
        printf("Select a choice :");
        scanf("%d",&choice);
        getchar();
        switch(choice){
            case 1:
            {
               printf("\nEnter the name of the contact you want to delete(or type exit to stop): ");
                scanf("%[^\n]",name_str);
                __fpurge(stdin);
                if(strcmp(name_str,"exit")==0){
                    return;
                }
                search_by_name(addressBook,name_str,&found,track_index);
                if(found == 0){
                    printf("\nNo contact found to delete, please try again !!\n");
                    return;
                }
                do{
                    printf("\nEnter the serial no of the contact you want to delete or enter 0 to cancel : ");
                    scanf("%d",&serial_no);
                    if(serial_no == 0){
                        return ; 
                    }
                    if(serial_no > 0 && serial_no <= found){
                        do{
                            printf("\nAre you sure you want to delete the selected contact (Y/N) : ");
                            char ch;
                            scanf(" %c",&ch);
                            __fpurge(stdin);
                            if(ch == 'y' || ch == 'y' - 32){
                                for(int i = track_index[serial_no - 1]; i < addressBook->contactCount-1; i++){
                                    addressBook->contacts[i] = addressBook->contacts[i+1];
                                }
                                addressBook->contactCount--;
                                printf("\n Contact deleted successfully !!\n");
                            return;
                            }
                            else if(ch == 'n' || ch == 'n' - 32){
                                printf("\nNo contact deleted\n");
                                return;
                            }
                            else{
                                printf("\nInvalid character entered , please try again !!\n");
                                continue;
                            }
                        }while(1);
                    }
                    else{
                        printf("Invalid serial number selected . Try again !!\n");
                        continue;
                    }
                }while(1);
                break; 
            }
            case 2:
            {
                printf("\nEnter the phone number of the contact you want to delete(or type exit to stop): ");
                scanf("%[^\n]",phone);
                __fpurge(stdin);
                if(strcmp(phone,"exit")==0){
                    return;
                }
                search_by_phone(addressBook,phone,&found,track_index);
                if(found == 0){
                    printf("\nNo contact found to delete, please try again !!\n");
                    return;
                }
                do{
                    printf("\nEnter the serial no of the contact you want to delete or enter 0 to cancel : ");
                    scanf("%d",&serial_no);
                    if(serial_no == 0){
                        return ; 
                    }
                    if(serial_no > 0 && serial_no <= found){
                        do{
                            printf("\nAre you sure you want to delete the selected contact (Y/N) : ");
                            char ch;
                            scanf(" %c",&ch);
                            __fpurge(stdin);
                            if(ch == 'y' || ch == 'y' - 32){
                                for(int i = track_index[serial_no - 1]; i < addressBook->contactCount-1; i++){
                                    addressBook->contacts[i] = addressBook->contacts[i+1];
                                }
                                addressBook->contactCount--;
                                printf("\n Contact deleted successfully !!\n");
                            return;
                            }
                            else if(ch == 'n' || ch == 'n' - 32){
                                printf("\nNo contact deleted\n");
                                return;
                            }
                            else{
                                printf("\nInvalid character entered , please try again !!\n");
                                continue;
                            }
                        }while(1);
                    }
                    else{
                        printf("Invalid serial number selected . Try again !!\n");
                        continue;
                    }
                }while(1);
                break; 
            }
            case 3:
            {
                printf("\nEnter the email of the contact you want to delete(or type exit to stop): ");
                scanf("%[^\n]",email);
                __fpurge(stdin);
                if(strcmp(email,"exit")==0){
                    return;
                }
                search_by_email(addressBook,email,&found,track_index);
                if(found == 0){
                    printf("\nNo contact found to delete, please try again !!\n");
                    return;
                }
                do{
                    printf("\nEnter the serial no of the contact you want to delete or enter 0 to cancel : ");
                    scanf("%d",&serial_no);
                    if(serial_no == 0){
                        return ; 
                    }
                    if(serial_no > 0 && serial_no <= found){
                        do{
                            printf("\nAre you sure you want to delete the selected contact (Y/N) : ");
                            char ch;
                            scanf(" %c",&ch);
                            __fpurge(stdin);
                            if(ch == 'y' || ch == 'y' - 32){
                                for(int i = track_index[serial_no - 1]; i < addressBook->contactCount-1; i++){
                                    addressBook->contacts[i] = addressBook->contacts[i+1];
                                }
                                addressBook->contactCount--;
                                printf("\n Contact deleted successfully !!\n");
                            return;
                            }
                            else if(ch == 'n' || ch == 'n' - 32){
                                printf("\nNo contact deleted\n");
                                return;
                            }
                            else{
                                printf("\nInvalid character entered , please try again !!\n");
                                continue;
                            }
                        }while(1);
                    }
                    else{
                        printf("Invalid serial number selected . Try again !!\n");
                        continue;
                    }
                }while(1);
                break;
            }
            case 4:
                return;
            default :
                printf("Invalid choice ,Try again!!\n");
                continue;  
        } 
    }while(1);
}

int valid_name(char *name_str){

    /*
 * valid_name
 * ------------------------
 * Validates a given name string based on these rules:
 * - Name must not be empty.
 * - First character must be an alphabet.
 * - Allows alphabets, single spaces, and single dots.
 * - Disallows consecutive spaces or dots.
 * - Disallows trailing spaces or dots.
 *
 * Returns:
 *   0 → if name is valid
 *   1 → if name is invalid (with error message printed)
 */
    int i = 0;

    if(name_str[0] == '\0'){
        printf("Name should not be empty!!...Please , enter a valid name !!\n");   // to check for empty string
        return 1;
    }
    if(!isalpha(name_str[0])){ 
        printf("First character of name should not be a digit!!...Please , enter a valid name !!\n");    //to check if first character is an alphabet or not
        return 1;
    }        
    while(name_str[i]){
        if(isalpha(name_str[i]) || (name_str[i] == ' ' && name_str[i + 1] != ' ') || (name_str[i] == '.' && name_str[i + 1] != '.') || (name_str[i] != '.' && name_str[i + 1] == '\0') ){
            i++;
        }
        else{
            printf("Name should not contain consecutive spaces( ) or dot(.) ...Please , enter a valid name !!\n");
            return 1;
        }
    }
    if(name_str[i - 1] == ' ' || name_str[i - 1] == '.'){
        printf("Name should not end with space or dot! Please enter a valid name.\n");
        return 1;
    }
    if(name_str[i] == '\0')
        return 0;
}

int valid_phone(char *phone){
 /*
 * valid_phone
 * ------------------------
 * Validates a phone number string.
 * - Must not start with 0.
 * - Must contain only digits.
 * - Must be exactly 10 digits long.
 *
 * Returns:
 *   0 → if phone number is valid
 *   1 → if invalid (prints an error message)
 */
    int i = 0,count = 0;
    if(phone[0] == '0'){
        printf("Error , Phone number should not start with 0 ...please try again!!\n");
        return 1;
    }    
    while(phone[i]){
        if( !(isdigit(phone[i])) ){
            printf("Phone number should contain digits only ...please try again!!\n");
            return 1;
        }
        count++;
        i++;    
    }
    if(count == 10)
        return 0;
    else{
        printf("Phone number should be exactly 10 digits ...please try again!!\n");
        return 1;
    }    
}

int valid_email(char *email){
 /*
 * valid_email
 * ------------------------
 * Validates an email string.
 * - Must start with a lowercase alphabet.
 * - Must contain exactly one '@' symbol.
 * - Must contain at least one '.' after '@'.
 * - Domain name must not be empty (characters required between '@' and '.').
 * - Must contain only lowercase alphabets.
 *
 * Returns:
 *   0 → if email is valid
 *   1 → if invalid (prints an error message)
 */

    int i = 0,at_count = 0,at_pos = 0;
    int j;
    if(!(isalpha(email[0])) || !(islower(email[0]))){
        printf("Error,email should start with a lower case alphabet only!!\n");
        return 1;
    }
    while(email[i]){
        if(email[i] == '@')
            at_count++;
        i++;    
    }
    i = 0;
    if(at_count > 1){
        printf("A valid email should not contain more than 1 '@' symbol!!\n");
        return 1;
    }
    else if(at_count == 1){
        while(email[i]){
            if( isalpha(email[i]) && !(islower(email[i]))){
                printf("Email should contain only lower case alphabets!!\n");
                return 1;
            }
            else if(email[i] == '@'){
                at_pos = i;
                j = i + 1;
                while( email[j] && email[j] != '.'){
                    j++;
                }
                if(email[j] == '\0'){
                   printf("Error , email should contain atleast one '.' symbol after '@' symbol\n");
                   return 1; 
                }

                if((j - i) == 1){
                    printf("Error, there should be some domain name for email !!\n");
                    return 1;
                }
            }
            i++;
        }
        if(email[i] == '\0')
            return 0;
    }
    printf("Error , email should contain atleast one '@' symbol\n");
    return 1;
}

void search_by_name(AddressBook *addressBook,char *name_str,int *found,int track_index[]){
 /*
 * search_by_name
 * ------------------------
 * Searches the AddressBook for contacts matching the given name (case-insensitive).
 * - Iterates through all contacts and checks for partial matches.
 * - Prints contact details for each match found.
 * - 'found' variable tracks the number of matches and the function returns void
 * - 'track_index' stores the indices of all matched contacts which is used during edit and delete functions.
 */
    for(int i = 0; i < addressBook -> contactCount ;i++ ){   
        if(strcasestr(addressBook -> contacts[i].name , name_str)){
            if( *found == 0 )
                printf("\n   ---Contact found---   \n");
            printf("%d]  NAME : %s\n",*found + 1,addressBook -> contacts[i].name);
            printf("    PHONE : %s\n",addressBook -> contacts[i].phone);
            printf("    EMAIL : %s\n",addressBook -> contacts[i].email);
            track_index[(*found)++] = i;
        }
    }
}

void search_by_phone(AddressBook *addressBook,char *phone,int *found,int *track_index){
 /*
 * search_by_phone
 * ------------------------
 * Searches the AddressBook for contacts matching the given phone number (substring match).
 * - Iterates through all contacts and compares phone numbers.
 * - Prints details of each matching contact.
 * - 'found' keeps count of matches and keeps a count of the matched contacts found.
 * - 'track_index' stores the indices of matched contacts for use in delete and edit function.
 */
    for(int i = 0; i < addressBook -> contactCount ;i++ ){ 
        if(strstr(addressBook -> contacts[i].phone , phone)){
            if( *found == 0 )
                printf("\n   ---Contact found---   \n");
            printf("%d]  NAME : %s\n",*found + 1,addressBook -> contacts[i].name);
            printf("    PHONE : %s\n",addressBook -> contacts[i].phone);
            printf("    EMAIL : %s\n",addressBook -> contacts[i].email);
            track_index[(*found)++] = i;
        }
    }
}

void search_by_email(AddressBook *addressBook,char *email,int *found,int *track_index){
 /*
 * search_by_email
 * ------------------------
 * Searches the AddressBook for contacts matching the given email (substring match).
 * - Iterates through all contacts and compares email addresses.
 * - Prints details of each matching contact.
 * - 'found' keeps count of matches and keeps a count of the matched contacts found.
 * - 'track_index' stores the indices of matched contacts for use in delete and edit function.
 */
    for(int i = 0; i < addressBook -> contactCount ;i++ ){
        if(strcasestr(addressBook -> contacts[i].email , email)){
            if( *found == 0 )
                printf("\n   ---Contact found---   \n");
            printf("%d]  NAME : %s\n",*found + 1,addressBook -> contacts[i].name);
            printf("    PHONE : %s\n",addressBook -> contacts[i].phone);
            printf("    EMAIL : %s\n",addressBook -> contacts[i].email);
            track_index[(*found)++] = i;
        }
    }
}

int duplicate_phone(AddressBook *addressBook,const char *phone){
 /*
 * duplicate_phone
 * ------------------------
 * Checks if the given phone number already exists in the AddressBook.
 * - Iterates through all existing contacts and compares phone numbers.
 * - If a duplicate is found:
 *      - Displays an error message.
 *      - Prompts the user whether they wish to view the existing contact (Y/N).
 *          - If 'Y', displays the contact details.
 *          - If 'N', skips showing but still flags it as duplicate.
 *      - Keeps asking until a valid response is entered.
 * - Returns 1 if a duplicate is found (regardless of user choice), else returns 0.
 */

    for(int i = 0; i < addressBook -> contactCount ; i++){
        if(strcmp(addressBook -> contacts[i].phone , phone) == 0){
            printf("Error: Phone number already exists for another contact!\n");
            do{
                printf("\nDo you wish to see this contact(Y/N) : ");
                char ch;
                scanf(" %c",&ch);
                __fpurge(stdin);
                if(ch == 'y' || ch == 'y' - 32){
                    printf("%d]  NAME : %s\n",i+1,addressBook -> contacts[i].name);
                    printf("    PHONE : %s\n",addressBook -> contacts[i].phone);
                    printf("    EMAIL : %s\n",addressBook -> contacts[i].email);
                    return 1;
                }
                else if(ch == 'n' || ch == 'N'){
                    return 1; 
                }
                else{
                    printf("\nInvalid character entered , please try again !!\n");
                    continue;
                }
            }while(1);
        }    
    }
    return 0;
}

int duplicate_email(AddressBook *addressBook,const char *email){
 /*
 * duplicate_email
 * ------------------------
 * Checks if the given email already exists in the AddressBook.
 * - Iterates through all existing contacts and compares emails.
 * - If a duplicate is found:
 *      - Displays an error message.
 *      - Prompts the user whether they wish to view the existing contact (Y/N).
 *          - If 'Y', displays the contact details.
 *          - If 'N', skips showing but still flags it as duplicate.
 *      - Keeps asking until a valid response is entered.
 * - Returns 1 if a duplicate is found (regardless of user choice), else returns 0.
 */

    for(int i = 0; i < addressBook -> contactCount ; i++){
        if(strcmp(addressBook -> contacts[i].email , email) == 0){
            printf("Error: Email already exists for another contact!\n");
            do{
                printf("\nDo you wish to see this contact(Y/N) : ");
                char ch;
                scanf(" %c",&ch);
                __fpurge(stdin);
                if(ch == 'y' || ch == 'y' - 32){
                    printf("%d]  NAME : %s\n",i+1,addressBook -> contacts[i].name);
                    printf("    PHONE : %s\n",addressBook -> contacts[i].phone);
                    printf("    EMAIL : %s\n",addressBook -> contacts[i].email);
                    return 1;
                }
                else if(ch == 'n' || ch == 'N'){
                    return 1; 
                }
                else{
                    printf("\nInvalid character entered , please try again !!\n");
                    continue;
                }
            }while(1);
        }    
    }
    return 0;
}


