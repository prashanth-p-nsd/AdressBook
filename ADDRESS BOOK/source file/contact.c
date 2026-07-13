#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
//#include "populate.h"

//To list the contacts that are saved.
void listContacts(AddressBook *addressBook)
{
      // Display all saved contacts in a table format (sorted by name)
     printf("\n==============================list contact===================================\n");
     printf("| %-4s | %-20s | %-15s | %-25s |\n","S.No","Name","Phone Numbers","Emails");
     printf("-----------------------------------------------------------------------------\n");
    if(addressBook->contactCount == 0)
         {
            printf(" No Contacts Available\n ");//if no contacts found
         }

     Contact temp;

      // To print saved contacts in sorted order based on names
      
     for(int i = 0;i < addressBook->contactCount -1;i++)
     {
        for(int j = 0; j < addressBook->contactCount - i - 1; j++)
        {
            if(strcasecmp(addressBook->contacts[j].name,addressBook->contacts[j+1].name)>0)
            {
                temp = addressBook->contacts[j];
                addressBook->contacts[j] = addressBook->contacts[j+1];
                addressBook->contacts[j+1] = temp;
            }
        }
     }
       
    for(int i = 0 ; i < addressBook -> contactCount ; i++) // To print saved contacts
    {
        printf("| %-4d | %-20s | %-15s | %-25s |\n",i+1,addressBook -> contacts[i].name,addressBook -> contacts[i].phone,addressBook -> contacts[i].email);
    }
    printf("-----------------------------------------------------------------------------\n");
}
 
// Initialize the address book and load existing contacts from file
void initialize(AddressBook *addressBook)
{
    addressBook->contactCount = 0;

    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);// Load saved contacts
}

void saveAndExit(AddressBook *addressBook)
{
    saveContactsToFile(addressBook); // Save contacts to file
    printf("contacts saved.existing.\n");
    exit(EXIT_SUCCESS);              // Exit the program
}

// Create a new contact (name, phone, email with validation)
void createContact(AddressBook *addressBook)
{
    
    char Name[50];
    char Phone[20];
    char Email[50];

     int a, b, c;
    do{

        printf("Enter your name :");
        scanf(" %[^\n]",Name);

        a = createname(Name);// validate name

        if(a == 0)
        {
            printf("Error : Invalid name\n");
        }
    }while(a == 0);

    strcpy(addressBook -> contacts[addressBook -> contactCount].name,Name);

    do{
        printf("Enter Phone number :");
        scanf(" %[^\n]",Phone);

        b = createphone(Phone);// validate phone

        int i =0 , f = 0;
        // check duplicate phone numbers
        while(i < addressBook -> contactCount)
        {
         f = strcmp(addressBook -> contacts[i].phone,Phone);

         if(f == 0)
         {
            printf("Error : Already exist\n");
           b = 0;
          }  
        i++;
        }

    }while(b == 0);

    strcpy(addressBook -> contacts[addressBook ->contactCount].phone,Phone);

    do{
        printf("Enter E-mail address :");
        scanf(" %[^\n]",Email);

        c = createemail(Email); // validate email
        if(c == 0)
        {
        printf("Invalid Email Id\n");
        }
        int i = 0, f = 0;
        // check duplicate email
        while(i < addressBook -> contactCount)
        {
           if(strstr(Email,addressBook -> contacts[i].email))
           {
             f = 1;
           }
           i++;
        }
        if(f == 1)
        {
            printf("Error : Already exist\n");
            c = 0;
        }

    }while(c == 0);

    strcpy(addressBook -> contacts[addressBook ->contactCount].email,Email);

     // Increment contact count
    addressBook ->contactCount++;
    printf("Contacts Created\n");

}

//Name Validation returns 1 if valid, 0 if invalid
int createname(char *name)
{
    int i = 0;
     while(name[i])
     {
        // Name cannot start with space or dot
        if(name[0] == ' ' || name[0] == '.')
          return 0;

        // Allow only alphabets, space, and dot    
        if(!(name[i] >= 'A' && name[i] <= 'Z' || name[i] >= 'a' && name[i] <= 'z' || name[i] == ' ' || name[i] == '.'))
        {
            return 0;
        }
         // if multiple spaces or dots
        if((name[i] == ' ' && name[i+1] == ' ') || (name[i] == '.' && name[i+1] == '.'))
        {
            return 0;
        }
        i++;
     }

     return 1;
}

// Phone Number Validation returns 1 if valid (10 digit), else 0
int createphone(char *phone)
{
    int i = 0, len;
    
    len = strlen(phone);

    while(phone[i])
    {
        //Allow only 0-9;
        if(!(phone[i] >= '0' && phone[i] <= '9'))
        {
            printf("Error :All elements shuold be numbers\n");
            return 0;
        }
        i++;
    }
    
    if(!(len == 10))
     {
       printf("Phone number must be 10 digit\n");
       return 0;
     }
    return 1;
   
}

//Email Id Validation returns 1 if valid email, else 0
int createemail(char *email)
{
    int i = 0, len = strlen(email), count = 0;
    
    // cannot start or end with @ or .
    if(email[0] == '@' || email[0] == '.' || email[len -1] == '@' || email[len - 1] == '.')
    {
        return 0;
    }

    // must contain '@'
    char *p = strchr(email ,'@');
    if(p == NULL)
    {
        return 0;
    }
    // must contain domain (.com, .in, .edu ..)
    if(!(strstr(p,".com") || strstr(p,".in") || strstr(p,".edu")))
    {
        return 0;
    }
    while(email[i])
    {
        // check characters one by one
        if(!(email[i] >= 'a' && email[i] <= 'z' || email[i] == '@' || email[i]== '.' || email[i] >= '0' && email[i] <= '9'))
        {
            return 0;
        }
        if(email[i] == '@') // only one @ allowed
        {
            count++;
            if(count != 1)
            {
                return 0;
            }
        }
        if( email[i] == '@' && email[i+1] == '.' || (email[i] == '.' && email[i+1] == '.'))
        {
            return 0;
        }
       
        i++;
    }
    return 1;
}

// Search Contact
int searchContact(AddressBook *addressBook)
{   
   
    printf("\n========Search contact=========\n");

    int choice;
    do{
        printf("--------------------------------\n");
        printf("Search By :\n");
        printf("1) Name \n");
        printf("2) Phone number \n");
        printf("3) Email \n");
        printf("4) Back to menu \n");
        printf("--------------------------------\n");
        printf(" Enter your choice :");
        if (scanf("%d", &choice) != 1) {
        while (getchar() != '\n'); 
        printf("Invalid input! Please enter a number.\n");
        choice = 0;
        continue;
        }
         // validate number input
       if (choice < 1 || choice > 4) {
        printf("Invalid choice! Please select 1–4.\n");
        continue;
        }
        
        switch(choice)
        {
            // Search by Name
            case 1:
                {
                 char t1[50];
                 int x,count, a;
                 int arr[50]; // for store index
                   while(1){
                    printf("Enter your name:");
                    scanf(" %[^\n]",t1);
                       x = createname(t1);
                     if(x == 0)
                     {
                        printf("Invalid Name.Please try again. \n");
                       continue;
                     }
                          count = 0;
                         int i = 0;
                        while(i < addressBook -> contactCount) //check matches
                        {
                       if(strcmp(addressBook -> contacts[i].name,t1) == 0)
                         {
                            arr[count++] = i;
                         }
                         i++;
                        }
                        if(count == 0)
                        {
                            printf("Contact not found.Try again\n");
                            continue;
                        }
                        // print all matched contacts
                        printf("\n------------------------------Contacts found---------------------------------\n");
                         for(int j = 0; j < count ; j++)
                         {
                            a = arr[j];
                         printf("| %-4d | %-20s | %-15s | %-25s |\n",j+1,addressBook -> contacts[a].name,addressBook -> contacts[a].phone,addressBook -> contacts[a].email);
                         }
                         printf("-----------------------------------------------------------------------------\n");
                         if(count == 1)
                         {
                            // if only one match, return it
                            return arr[0];
                         }
                         
                         // allow user to select which contact
                         int select, t;
                         printf("Select contact by serial number :");
                         scanf("%d",&select);

                         if(select >= 1 && select <= count)
                         {
                            t = arr[select - 1];
                            printf("\n------------------------------Contact found----------------------------------\n");
                            printf("| %-4d | %-20s | %-15s | %-25s |\n",select,addressBook -> contacts[t].name,addressBook -> contacts[t].phone,addressBook -> contacts[t].email);
                            printf("-----------------------------------------------------------------------------\n");
                            return arr[select - 1];
                         }
                         else
                         {
                            printf("Invalid selection\n");
                            continue;
                         }
                    }
                }
            break;
            case 2:
               {
                //Search by Phone number
                 char t2[20]; // store temp phone number
                 int x ;
                 while(1)
                 {
                    printf("Enter Phone number:");
                    scanf(" %[^\n]",t2);
                       x = createphone(t2); // Phone number validation
                     if(x == 0)
                     {
                        printf("Invalid Phone number.Please try again. \n");
                        continue;
                     }
                    
                         int i = 0, found = 0;
                        while(i < addressBook -> contactCount)
                        {
                       if(strcmp(addressBook -> contacts[i].phone,t2) == 0)
                         {
                            //print if the contact matchs
                         printf("\n------------------------------Contact found-----------------------------------\n");
                         printf("| %-4d. | %-20s | %-15s | %-25s |\n ", i+1,addressBook -> contacts[i].name,addressBook -> contacts[i].phone,addressBook -> contacts[i].email);
                         printf("-----------------------------------------------------------------------------\n");
                          return i;
                         }
                          i++;
                        }
                        if(found == 0)
                        {
                         printf("contact not found\n"); // if contact not found
                        }
                    }                
        
                }
            break;
            case 3:
                {
                    // search By Email Id 
                  char t3[50];
                  int x; 
                 while(1)
                 {
                    printf("Enter Email Id:");
                    scanf(" %[^\n]",t3);
                       x = createemail(t3);// Email validation
                     if(x == 0)
                     {
                        printf("Invalid Email Id.Please try again. \n");
                        continue;
                     }
    
                         int i = 0,found = 0;
                        while(i < addressBook -> contactCount)
                        {
                         char* c = strstr(addressBook->contacts[i].email, t3);
                           if(!(c == NULL))
                         {
                             // if contact found print the contact
                            printf("\n------------------------------Contact found-----------------------------------\n");
                         printf("| %-4d. | %-20s | %-15s | %-25s |\n", i+1,addressBook -> contacts[i].name,addressBook -> contacts[i].phone,addressBook -> contacts[i].email);
                         printf("------------------------------------------------------------------------------\n");
                         found = 1;
                          return i;

                        }
                        i++;
                    }
                        if(found == 0)
                        {
                         printf("contact not found\n");// if contact not found 
                        }
                    }
                
                }
            break;
            case 4:
            //Back to the Menu
            break;
            default:
               printf("Invalid choice. Please try again.\n");
        }
    }while(choice != 4);
}

// Editing the contact 
void editContact(AddressBook *addressBook)
{
    /* Define the logic for Editcontact */
     char Name[50];
    char Phone[20];
    char Email[50];
    
    
    printf("\n=========Edit contact==========\n");

         if(addressBook->contactCount == 0)
         {
            printf(" No Contacts avaliable ");// if no contact is Exist
            return;
         }

    int index = searchContact(addressBook);// store the index value in variable 

     int choice;
    do{
        // Allows editing Name / Phone / Email after searching
        printf("----------Edit contact----------\n");
        printf("Edit By :\n");
        printf("1) Edit Name \n");
        printf("2) Edit Phone number \n");
        printf("3) Edit Email \n");
        printf("4) Back to menu \n");
        printf("--------------------------------\n");
        printf(" Enter your choice :");
        // validate choice input
         if (scanf("%d", &choice) != 1) {
        while (getchar() != '\n'); 
        printf("Invalid input! Please enter a number.\n");
        choice = 0;
        continue;
        }

       if (choice < 1 || choice > 4) {
        printf("Invalid choice! Please select 1–4.\n");
        continue;
        }
         
        switch(choice)
        {
              case 1:
                {
                  int P;
                  do{
                    //Edit name
                    printf("Enter Name to Edit:");
                    scanf(" %[^\n]",Name);
                     P = createname(Name);//name validation
                     if(P == 0)
                     {
                         printf("Invalid Name .Please try again.\n");
                     }
                     else
                     {
                       strcpy(addressBook -> contacts[index].name,Name);
                       printf("Name Edited succesfully\n");
                     }
                  }while(P == 0);
                }
              break;
              case 2:
                 {
                  int P;
                    do{
                        //Edit Phone number
                       printf("Enter Phone number to Edit:");
                       scanf(" %[^\n]",Phone);
                          P = createphone(Phone);
                          int flag = 0;
                          for(int i = 0; i < addressBook->contactCount; i++)
                          {
                          if(i != index && strcmp(addressBook->contacts[i].phone, Phone)== 0)// check if the contact exist
                          {
                          flag = 1;
                          break;
                           }
                           }
                        if(flag == 1)
                           {
                            printf("Error: Phone number already exists.\n");
                            continue;
                           }
                            else if(P == 0)
                            {
                             printf("Invalid Phone number. Please try again.\n");
                             continue;
                           }
                          else
                          {
                            // store the contact in the structure
                            strcpy(addressBook -> contacts[index].phone, Phone);
                            printf("Phone number Edited succesfully\n");
                          }
                   }while(P == 0);
                }
              break;
              case 3:
                  {
                   int P;
                   do{
                    //Edit the Email Id
                   printf("Enter Email ID to Edit:");
                   scanf(" %[^\n]",Email);
                    P = createemail(Email);//Email validation 
                    int flag = 0;
                          for(int i = 0; i < addressBook->contactCount; i++)
                          {
                          if( i != index && strcmp(addressBook->contacts[i].email, Email) == 0)// check if the contact is exist or not
                          {
                          flag = 1;
                          break;
                           }
                           }
                    if(flag == 1)
                    {
                     printf("Error: Email id already exists.\n");
                     continue;
                    }
                     else if(P == 0)
                     {
                     printf("Invalid Email id Please try again.\n");
                     continue;
                     } 
                    else
                    {
                        //store the contact email in the structure
                    strcpy(addressBook -> contacts[index].email,Email);
                    printf("Email ID Edited succesfully\n");
                    }
                    }while(P == 0);
                }
              break;
              case 4:
              //Back to Menu
              break;
              default:
                   printf("Invalid choice. Please try again.\n");
         }
    }while(choice != 4);

}

// Delete selected contact after confirmation

void deleteContact(AddressBook *addressBook)
{
      
    printf("\n========Delete contact=========\n");

         if(addressBook->contactCount == 0)
         {
            printf(" No Contacts avaliable ");
            return;
         }
     
          // search and select contact
    int index = searchContact(addressBook);

    printf("Selected contact \n");

    char s_no;
    
    printf("Delete this contact? (y/n) :");
    if(scanf(" %c",&s_no) != 1)
    {
        while(getchar() != '\n');
        printf("Invalid input.\n");
        return;
    }

    if(s_no == 'y' || s_no == 'Y')
    {
    for(int i = index ; i < addressBook->contactCount-1;i++)
    {
        // Shift contacts
        addressBook->contacts[i] = addressBook->contacts[i+1];
    }
    addressBook->contactCount--;

    printf("Successfully contact delete");
    }
    else if((s_no == 'n' || s_no == 'N'))
    {
        printf("Deletion cancelles.");
        return;
    }
    else{
        printf("Invalid input.");
        return;
    }

}
