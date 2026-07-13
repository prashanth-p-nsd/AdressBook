#include <stdio.h>
#include "file.h"
#include "contact.h"

void saveContactsToFile(AddressBook *addressBook)
{
    FILE *fptr;

    fptr = fopen("contacts.csv","w");

    if (fptr == NULL) 
    {
    printf("Error opening file!\n");
    return;
    }

    fprintf(fptr,"%d\n",addressBook->contactCount);
    int i ;
    for(i = 0; i < addressBook->contactCount; i++)
    {
    fprintf(fptr,"%s,%s,%s \n",addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
      
    }

    fclose(fptr);
}

void loadContactsFromFile(AddressBook *addressBook)
{
  
      FILE *fptr;

    fptr = fopen("contacts.csv","r");

    if (fptr == NULL) 
    {
    printf("Error opening file!\n");
    return;
    }

    fscanf(fptr,"%d\n",&addressBook->contactCount);
    int i;
    for(i = 0; i < addressBook->contactCount; i++)
    {
    fscanf(fptr,"%[^,],%[^,],%[^\n]\n",addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
      
    }

    fclose(fptr);



}
