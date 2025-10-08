# PHONE_ADDRESS_BOOK
This project aims in creating a metadata of the details of an individual like name phone number and email and storing this details using structure in C language . And it also provides the user using to edit delete and search any contact saved earlier. 

---

## Features

-  **Add Contact** – Create and store new contact details.
-  **Search Contact** – Search for a contact by **name**, **phone number**, or **email**.
-  **Edit Contact** – Modify existing contact information.
-  **Delete Contact** – Remove a saved contact.
-  **List Contacts** – Display all saved contacts (optionally sorted by name, phone, or email).
-  **Save Contacts** – Save all contact data for persistence between runs. *(optional if implemented)*

---

## Implementation Details

- Uses **structures** to store individual contact data.
- Contact list is managed using an **array of structures**.
- Follows a **menu-driven** interface for user-friendly interaction.
- Includes **input validation** for:
  - Proper email format.
  - 10-digit phone numbers.
  - Valid name input (alphabet-only).

## Example Menu
 1. Address Book Menu:
 2. Create contact
 3. Search contact
 4. Edit contact
 5. Delete contact
 6. List all contacts
 7. Save contacts
 8. Exit
    
  Enter your choice:

##Compile
``` sh
  gcc main.c contact.c -o addressbook
```
##Run
```sh
  ./addressbook
```
