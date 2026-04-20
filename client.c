#include "csapp.h"
#include <stdio.h>        

void print_menu();        

static void result(int result) {   // avoid the result warning message
    (void)result;                   
}
// function to Hold the result. 
int main(int argc, char *argv[])  
{
    int clientfd;  
    char *host, *port;
    size_t n; 
    char buffer [MAXLINE]; 
    bzero(buffer,MAXLINE); 
    if (argc != 3)
    {
        fprintf(stderr, "usage: %s <host> <port>\n", argv[0]);
	    exit(0);
    }
    host = argv[1];
    port = argv[2];

    //client file descriptor to hold the host and the port 
    clientfd = Open_clientfd(host, port);
    int user_choice;
    int w_result;    

    // display the options menu
    print_menu();    
    w_result = scanf("%d", &user_choice);  // take user input, show "Wrong Input" if input is wrong
    if(w_result != 1){
        printf("Wrong Input");
    }
    // while true loop
    while(1){
        //Option 1:Sending a new record to records.csv 
        if(user_choice == 1){ 
            printf("\n");               //New line character for printing purposes
            char first_name[MAXLINE];
            char last_name[MAXLINE];
            char Department[MAXLINE];   //Character arrays to temporarily hold data that will be sent to the server 
            char zip_code[MAXLINE];
            char salary[MAXLINE];
            char choice[] = "1";      
            n = write(clientfd,choice,strlen(choice));                // Writing to the server the client's choice, asking user for all the information, and writing to the server all the information
            printf("Enter First Name: ");  
            result(scanf("%s", first_name));                          // getting the user's input 
            getchar();                                                // getting the newline character 
            n = write(clientfd,first_name,strlen(first_name)); 
            printf("Enter Last Name: ");                              
            result(scanf("%s", last_name));                             
            getchar();                                                 
            n = write(clientfd,last_name,strlen(last_name));          
            printf("Enter Zip Code: ");                               
            result(scanf("%s", zip_code));                           
            getchar();                                                
            n = write(clientfd,zip_code,strlen(zip_code));            
            printf("Enter Department: ");
            if (fgets(Department, sizeof(Department), stdin) == NULL) {
                printf("Error reading input.\n");
                exit(1);
            }
            Department[strcspn(Department, "\n")] = '\0';
            n = write(clientfd, Department, strlen(Department));
            printf("Enter Salary: ");
            result(scanf("%s", salary));
            getchar();
            n = write(clientfd,salary,strlen(salary));            
            printf("Message from the server:\n");                // messaging the user "input recieved"  
            n = read(clientfd,buffer,MAXLINE);                   
            printf("%s\n",buffer);                               //Displaying the contents of the server 
            bzero(buffer,MAXLINE);                               // clear out the buffer
            if(n<0){ 
                perror("Error!!");
            }
        }
        else if(user_choice == 2){ 
            printf("\n");         
            char first_name [MAXLINE];
            char last_name [MAXLINE];      
            char choice[] = "2";           
            n = write(clientfd,choice,strlen(choice));    
            printf("Enter First Name: ");        
            result(scanf("%s",first_name));                        // Ask the user for information, take the user input, and send the information to the server
            getchar();                                              
            n = write(clientfd,first_name,strlen(first_name));      
            printf("Enter Last Name: ");
            result(scanf("%s",last_name));                         
            getchar();
            n = write(clientfd,last_name,strlen(last_name));
            if(n<0)
                perror("Error!!");
            printf("Message from the server: \n");                //Print out the information coming back from server
            n = read(clientfd,buffer,MAXLINE);                    //Print out the message from the buffer
            printf("%s\n",buffer);                       
            printf("\n");                                
            bzero(buffer,MAXLINE);                               //Clear out the buffer 
        }
        else if(user_choice == 3){       
            printf("\n");              
            char zip_code[MAXLINE];    
            char choice[] = "3";
            n = write(clientfd,choice,strlen(choice));
            printf("Enter Zip Code: ");                         // Ask the user for information, take the user input, and send the information to the server
            result(scanf("%s", zip_code));                     
            getchar();                                          
            n = write(clientfd,zip_code,strlen(zip_code));
            if(n<0)   
                perror("Error!!");                               //Print out the information coming back from server
            printf("Message from the server:\n");                //Print out the message from the buffer
            n = read(clientfd,buffer,MAXLINE);                   
            printf("%s\n",buffer);
            bzero(buffer,MAXLINE);                               //Clear out the buffer
        }
		
        else if(user_choice == 4){     
            printf("\n");              
            char comparison[MAXLINE];
            char salary[MAXLINE];      
            char choice[] = "4";
            n = write(clientfd,choice,strlen(choice));
            printf("Enter Salary: ");                           // Ask user for salary and comparison type 
            result(scanf("%s", salary));                        //Write the character arrays
            getchar();                                     
            n = write(clientfd,salary,strlen(salary));
            printf("Enter Comparison Type [’>’,’<’,’==’,’>=’,’<=’]: ");
            result(scanf("%s",comparison));
            getchar();
            n = write(clientfd,comparison,strlen(comparison));
            if(n<0)
                perror("Error!!");  
             printf("Message from the server:\n");               //Print out the information coming back from server
             n = read(clientfd,buffer,MAXLINE);                  //Print out the message from the buffer
             printf("%s\n",buffer);           
            bzero(buffer,MAXLINE);                               //Clear out the buffer
        }
        else if(user_choice == 5){   
            char choice[] = "5";                                 // if option 5, break out of the while loop 
            n = write(clientfd,choice,strlen(choice));          //Writing to the server just "5" since we want to close everything on server side
            break;
        }
        print_menu();                                           //while loop recurring condition
        user_choice = 0;                                        //setting the user's choice back to zero
        w_result = scanf("%d", &user_choice);  
        if(w_result != 1){
            printf("B");
        }
        }
    
        printf("Connection Closed!!\n"); 
        return 0;
}
// print_menu
void print_menu(){                  
    printf("(1) Add new record\n");
    printf("(2) Search by Name\n");
    printf("(3) Search by Zip Code\n");
    printf("(4) Search by Salary\n");
    printf("(5) Terminate\n");
    printf("Select an option [1,2,3,4 or 5]: ");
}