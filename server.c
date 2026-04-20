#include "csapp.h"


//Declaration of the struct of Arguments
struct Arguments {             // Struct to hold the file descriptor, the client hostname, and the client port. 
    int connfd;                // Function to take in more than four arguments.
    char client_hostname[MAXLINE];       
    char client_port[MAXLINE];
};

//Declaration of a mutex and setting it equal to default values 
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// Declaration of the struct of Struct_Employee_Info
typedef struct {
    char firstName[MAX_LENGTH];
    char lastName[MAX_LENGTH];
    char zipCode[MAX_LENGTH];
    char department[MAX_LENGTH];
    int salary;

} Struct_Employee_Info;

// take in the connection file descriptor and the character arrays of the hostname and port
void serverFunction(int connfd){
    
    FILE *file_object;                        
    Struct_Employee_Info employees[MAX_SIZE]; 
    char line[MAXLINE];                       
    int count = 0;                           
    file_object = fopen("records.csv", "r");   //Opening the file for reading 
    if (file_object == NULL) {
        printf("Unable to open the file.\n");  //Print out an error message if it doesn't open
    }

    //Adding the record from records.csv to the employees structure
    while (fgets(line, sizeof(line), file_object)) {
        sscanf(line, "%[^,],%[^,],%[^,],%[^,],%d",
               employees[count].firstName, employees[count].lastName,
               employees[count].zipCode, employees[count].department,&employees[count].salary);
        count++;
    }

    fclose(file_object);//closing the file 
    char buffer[MAXLINE]; 
    char successMessage[MAXLINE] = "Record added Sucessfully!!\n"; //Messsage here to be sent back for option 1
    size_t n;
    if(n<0){
        perror("Error!!");
    }
    // While loop until reached option 5 which breaks out
    while(1){
         bzero(buffer,MAXLINE);                     // clean out the buffer and read 1st option
         n = read(connfd, buffer, MAXLINE);        // store character and use the atoi
        int action_option;                         
        char firstName[MAXLINE];
        char option[MAXLINE];
        sscanf(buffer, "%[^\n]", option);        
        action_option = atoi(option);
        bzero(buffer,MAXLINE);
    if(action_option == 1){
        char firstName[MAXLINE];       // store information in temporary character arrays
        char LASTName[MAXLINE];        // sscanf() that reads from the buffer until a new line character is reached.
        char zip_code[MAXLINE];       // assigne the file_object to fopen and fprintf to send the information to the records.csv file
        char Department[MAXLINE];     //  information added to the array
        char salary[MAXLINE];         
        n = read(connfd, buffer, MAXLINE);   
        sscanf(buffer, "%[^\n]", firstName);
        bzero(buffer,MAXLINE);
        n = read(connfd, buffer, MAXLINE);
        sscanf(buffer, "%[^\n]", LASTName);
        bzero(buffer,MAXLINE);
        n = read(connfd, buffer, MAXLINE);
        sscanf(buffer, "%[^\n]", zip_code);
        bzero(buffer,MAXLINE);                      
        n = read(connfd, buffer, MAXLINE);
        sscanf(buffer, "%[^\n]", Department);
        bzero(buffer,MAXLINE);
        n = read(connfd, buffer, MAXLINE);
        sscanf(buffer, "%[^\n]", salary);
        bzero(buffer,MAXLINE);
        pthread_mutex_lock(&mutex); 
        file_object = fopen("records.csv", "a+");
        fprintf(file_object,"%s,%s,%s,%s,%s\n",firstName,LASTName,zip_code,Department,salary);
        pthread_mutex_unlock(&mutex);  
        n = write(connfd,successMessage,strlen(successMessage));
        count = 0;  
        fclose(file_object);
        file_object = fopen("records.csv", "r");
         while (fgets(line, sizeof(line), file_object)) {
            sscanf(line, "%[^,],%[^,],%[^,],%[^,],%d",employees[count].firstName, employees[count].lastName,employees[count].zipCode, employees[count].department,&employees[count].salary);
            count++;
            }
        fclose(file_object); 
        bzero(buffer,MAXLINE);
    }
    else if(action_option == 2){ 
        int new_counter = 0;
        file_object = fopen("records.csv", "r");
        while(fgets(line, sizeof(line), file_object)){
            new_counter++;
        }
        fclose(file_object); 
        file_object = fopen("records.csv", "r");
        if(new_counter != count){
        count=0;
         while(fgets(line, sizeof(line), file_object)) {
            sscanf(line, "%[^,],%[^,],%[^,],%[^,],%d",employees[count].firstName, employees[count].lastName,employees[count].zipCode, employees[count].department,&employees[count].salary);
            count++;
            }
        }
       fclose(file_object); 
       char lastName[MAXLINE];
        n = read(connfd, buffer, MAXLINE);      
        sscanf(buffer, "%[^\n]", firstName);   
        bzero(buffer, MAXLINE);
        n = read(connfd, buffer, MAXLINE);    
        sscanf(buffer, "%[^\n]", lastName);
        bzero(buffer, MAXLINE);
        int index_holder = -1;
        //For loop to iterate through the array of employees 
    for(int index = 0; index < count; index++){
        // Comparing case-insensitive names
        if((strcasecmp(employees[index].firstName, firstName) == 0) && 
            (strcasecmp(employees[index].lastName, lastName) == 0)){
                index_holder = index;
    snprintf(line,MAXLINE,"%s,%s,%s,%s,%d\n",employees[index_holder].firstName,employees[index_holder].lastName,employees[index_holder].zipCode,employees[index_holder].department,employees[index_holder].salary);
        //Using the sprintf function to store the line of data all together in the character array of line
            n = write(connfd,line,strlen(line));  //Writing to the client 
             bzero(line, MAXLINE);          
             bzero(buffer,MAXLINE);    //Clearing out the character arrays 
            }
        }
        if(index_holder == -1){ //If index holder didn't change the send back No Record found
            char n_line[MAXLINE];
             bzero(n_line,MAXLINE);    
            strcpy(n_line,"No record found!!\n");
            n = write(connfd,n_line,strlen(n_line));
        }
    }
    else if(action_option == 3){  // iterate through the zip code structure array and if it is there, string cat the information together. 
        bzero(line, MAXLINE);    // if not, write "No record found"
        char zip_Code[MAXLINE];
        int new_counter = 0;
        file_object = fopen("records.csv", "r");
        while(fgets(line, sizeof(line), file_object)){
            new_counter++;
        }
        fclose(file_object); 
        file_object = fopen("records.csv", "r");
        if(new_counter != count){
        count=0;
         while(fgets(line, sizeof(line), file_object)) {
            sscanf(line, "%[^,],%[^,],%[^,],%[^,],%d",employees[count].firstName, employees[count].lastName,employees[count].zipCode, employees[count].department,&employees[count].salary);
            count++;
            }
        }
       fclose(file_object); 
        n = read(connfd, buffer, MAXLINE);
        sscanf(buffer, "%[^\n]",zip_Code);
        pthread_mutex_lock(&mutex);
        int index_holder = -1;
            for(int index = 0; index < count; index++){
                if((strcmp(employees[index].zipCode,zip_Code)==0)){
                    index_holder = index;
                     bzero(line, MAXLINE);
                    strcat(line,employees[index_holder].firstName);
                    strcat(line,",");
                    strcat(line,employees[index_holder].lastName);
                    strcat(line,",");
                    strcat(line,employees[index_holder].zipCode);
                    strcat(line,",");
                    strcat(line,employees[index_holder].department);
                    strcat(line,",");
                    char salary[MAX_LENGTH];
                    snprintf(salary, sizeof(salary), "%d", employees[index_holder].salary);
                    strcat(line, salary);
                    strcat(line, "\n");
                    n = write(connfd,line,strlen(line));
                }
                
            }
        pthread_mutex_unlock(&mutex);
        if(index_holder == -1){ 
            char n_line[MAXLINE];
            bzero(n_line,MAXLINE);
            strcpy(n_line,"No record found!!\n");
            n = write(connfd,n_line,strlen(n_line));
        }
        else{
            bzero(line, MAXLINE);
            bzero(buffer,MAXLINE);
        }
    }
    else if(action_option == 4){  // compare by doing a string comparison. for loop to run and check.
        char SAlary[MAXLINE];     
        int new_counter = 0;
        file_object = fopen("records.csv", "r");
        while(fgets(line, sizeof(line), file_object)){
            new_counter++;
        }
        fclose(file_object); 
        file_object = fopen("records.csv", "r");
        if(new_counter != count){
        count=0;
         while(fgets(line, sizeof(line), file_object)) {
            sscanf(line, "%[^,],%[^,],%[^,],%[^,],%d",employees[count].firstName, employees[count].lastName,employees[count].zipCode, employees[count].department,&employees[count].salary);
            count++;
            }
        }
       fclose(file_object); 
        n = read(connfd, buffer, MAXLINE);
        sscanf(buffer, "%[^\n]", SAlary);
        char comparison[MAXLINE];               
        bzero(buffer,MAXLINE);
        n = read(connfd, buffer, MAXLINE);
        sscanf(buffer, " %[^\n]", comparison);
        int salary = atoi(SAlary);
        int index_holder = -1;
        if((strcmp(comparison,">=")==0)){
        for(int index = 0; index < count; index++){
        if(employees[index].salary >= salary){
            index_holder = index;
             bzero(line, MAXLINE);
            strcat(line,employees[index_holder].firstName);
            strcat(line,",");
            strcat(line,employees[index_holder].lastName);
            strcat(line,",");
            strcat(line,employees[index_holder].zipCode);
            strcat(line,",");
            strcat(line,employees[index_holder].department);
            strcat(line,",");
            char salary[MAX_LENGTH];
            snprintf(salary, sizeof(salary), "%d", employees[index_holder].salary);
            strcat(line, salary);
            strcat(line, "\n");
             n = write(connfd,line,strlen(line));
        }
        }
    }
        else if((strcmp(comparison,"<=")==0)){
         for(int index = 0; index < count; index++){
        if(employees[index].salary <= salary){
            index_holder = index;
             bzero(line, MAXLINE);
            strcat(line,employees[index_holder].firstName);
            strcat(line,",");
            strcat(line,employees[index_holder].lastName);
            strcat(line,",");
            strcat(line,employees[index_holder].zipCode);
            strcat(line,",");
            strcat(line,employees[index_holder].department);
            strcat(line,",");
            char salary[MAX_LENGTH];
            snprintf(salary, sizeof(salary), "%d", employees[index_holder].salary);
            strcat(line, salary);
            strcat(line, "\n");
             n = write(connfd,line,strlen(line));
            }
         }
        }
        else if((strcmp(comparison,"<")==0)){
         for(int index = 0; index < count; index++){
       if(employees[index].salary < salary){
            index_holder = index;
            bzero(line, MAXLINE);
            strcat(line,employees[index_holder].firstName);
            strcat(line,",");
            strcat(line,employees[index_holder].lastName);
            strcat(line,",");
            strcat(line,employees[index_holder].zipCode);
            strcat(line,",");
            strcat(line,employees[index_holder].department);
            strcat(line,",");
            char salary[MAX_LENGTH];
            snprintf(salary, sizeof(salary), "%d", employees[index_holder].salary);
            strcat(line, salary);
            strcat(line, "\n");
            n = write(connfd,line,strlen(line));
        }
         }
        }
        else if((strcmp(comparison,">")==0)){
         for(int index = 0; index < count; index++){
       if(employees[index].salary > salary){
            index_holder = index;
            bzero(line, MAXLINE);
            strcat(line,employees[index_holder].firstName);
            strcat(line,",");
            strcat(line,employees[index_holder].lastName);
            strcat(line,",");
            strcat(line,employees[index_holder].zipCode);
            strcat(line,",");
            strcat(line,employees[index_holder].department);
            strcat(line,",");
            char salary[MAX_LENGTH];
            snprintf(salary, sizeof(salary), "%d", employees[index_holder].salary);
            strcat(line, salary);
            strcat(line, "\n");
             n = write(connfd,line,strlen(line));
        }
    }
    }
    else if((strcmp(comparison,"==")==0)){
         for(int index = 0; index < count; index++){
        if(employees[index].salary == salary){
           index_holder = index;
             bzero(line, MAXLINE);
            strcat(line,employees[index_holder].firstName);
            strcat(line,",");
            strcat(line,employees[index_holder].lastName);
            strcat(line,",");
            strcat(line,employees[index_holder].zipCode);
            strcat(line,",");
            strcat(line,employees[index_holder].department);
            strcat(line,",");
            char salary[MAX_LENGTH];
            snprintf(salary, sizeof(salary), "%d", employees[index_holder].salary);
            strcat(line, salary);
            strcat(line, "\n");
             n = write(connfd,line,strlen(line));
            
        }
    }
    }
    if(index_holder == -1){ // return back "no record found"  if index holder is -1. 
        char n_line[MAXLINE];
        bzero(n_line,MAXLINE);
        strcpy(n_line,"No record found!!\n");
        n = write(connfd,n_line,strlen(n_line));
    }
    else{
        bzero(line,MAXLINE);
        bzero(buffer,MAXLINE);
    }
    if(n<0){
        perror("Error!!");
    }
    }
     else if(action_option==5){ 
         break;
     }
    }
}
void *thread(void *vargp){
    struct Arguments *arguments = (struct Arguments *)vargp;
    int connfd = (*arguments).connfd;
    char *client_hostname = (*arguments).client_hostname;
    char *client_port = (*arguments).client_port;
    pthread_detach(pthread_self());
    free(vargp);
    serverFunction(connfd);
    Close(connfd);
    printf("(%s,%s)disconnected\n", client_hostname, client_port);
    return NULL;
}


int main(int argc, char *argv[])
{
   int listenfd;
   int *connfd;                         // File descriptor to communicate with the client
   socklen_t clientlen;
   struct sockaddr_storage clientaddr;  //Enough space for address 
   char client_hostname[MAXLINE], client_port[MAXLINE];
   pthread_t tid;
    
    if (argc != 2) {
	fprintf(stderr, "usage: %s <port>\n", argv[0]);
	exit(0);
    }

    listenfd = Open_listenfd(argv[1]);
    
    // infinite loop is being run until pressing ctrl+c.
    while (1) {               
    	clientlen = sizeof(struct sockaddr_storage);
        // wait for the connection from the client.
        connfd = malloc(sizeof(int));
    	*connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
        Getnameinfo((SA *) &clientaddr, clientlen, client_hostname, 
                                   MAXLINE,client_port, MAXLINE, 0);

        printf("Connected to (%s, %s)\n", client_hostname, client_port);
        struct Arguments *arguments = malloc(sizeof(struct Arguments));
        (*arguments).connfd = *connfd;
        strcpy(arguments->client_hostname, client_hostname);
        strcpy(arguments->client_port, client_port);
        pthread_create(&tid, NULL, thread, arguments);
        // interact with the client's information and do operations.
    }
        
    exit(0);
}
