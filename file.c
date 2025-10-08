#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) {
  FILE *fp = fopen("contact.csv","w");
  if(fp == NULL){
    printf("File not found!");
    return;
  }
  fprintf(fp,"Total no of contacts = %d\n",addressBook -> contactCount);
  for(int i = 0;i < addressBook -> contactCount;i++){
    fprintf(fp,"%s,%s,%s\n",addressBook -> contacts[i].name ,addressBook -> contacts[i].phone,addressBook -> contacts[i].email);
  }
  fclose(fp);
}

void loadContactsFromFile(AddressBook *addressBook) {
  FILE *fp = fopen("contact.csv","r");
  if(fp == NULL){
    printf("File not found!");
    return;
  }  
  fscanf(fp, "%*[^\n]\n");  // Discards everything until newline
  int i = 0;  
  while(fscanf(fp,"%[^,],%[^,],%[^\n]\n",addressBook -> contacts[i].name ,addressBook -> contacts[i].phone,addressBook -> contacts[i].email) == 3){
    i++;
    addressBook -> contactCount++;
  }
  fclose(fp);
}
