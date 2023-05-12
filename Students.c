    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>


    typedef struct req{
        char name[20];
        int ID;
        int room, building;
        struct req *next;
    }request;

    int requestInQueue=0;
    request *head = NULL;
    request *rear = NULL;

    //Function to create linked list
    void create_linked_list() {
    FILE *fp;
    fp = fopen("data.txt", "r");
    if (fp == NULL) {
        printf("\nFile opening has failed\n");
        return;
    }
    int num_requests;
    fscanf(fp, "%d", &num_requests);

    head = (request *)malloc(sizeof(request));
    fscanf(fp, "%s %s %d %d %d", head->name,  &head->ID, &head->room, &head->building);
    head->next = NULL;
    rear = head;

    for (int i = 1; i < num_requests; i++) {
        request *new_node = (request *)malloc(sizeof(request));
        if (new_node == NULL) {
        printf("Failed to allocate memory.\n");
        exit(1);
        }
        fscanf(fp, "%s %s %d %d %d", new_node->name , &new_node->ID, &new_node->room, &new_node->building);
        new_node->next = NULL;
        rear->next = new_node;
        rear = new_node;
    }

    fclose(fp);
    }

    // Function to add a new node at a specific position(request)
    void add_node(){
        int position, ID, room, building;
        char name[20];
        printf("Enter the position: ");
        scanf("%d", &position);
        printf("Enter the name: ");
        scanf("%s", name);
        printf("Enter the ID: ");
        scanf("%d", &ID);
        printf("Enter the room: ");
        scanf("%d", &room);
        printf("Enter the building: ");
        scanf("%d", &building);
        request *temp = head;
        request *newNode = malloc(sizeof(request));
        newNode->ID = ID;
        newNode->room = room;
        newNode->building = building;
        strcpy(newNode->name, name);
        newNode->next = NULL;
        if (position == 1) {
            newNode->next = head;
            head = newNode;
        } else {
            int i;
            for (i = 1; i < position - 1 && temp != NULL; i++) {
                temp = temp->next;
            }
            if (temp == NULL) {
                printf("Invalid position\n");
            } else {
                newNode->next = temp->next;
                temp->next = newNode;
            }
        }
    }

    // Function to search a node by student's ID 
    void searchByID(int ID){
        request *temp = head;
        while (temp != NULL) {
            if (temp->ID == ID) {
                printf("Name: %s\n", temp->name);
                printf("ID: %d\n", temp->ID);
                printf("Room: %d\n", temp->room);
                printf("Building: %d\n", temp->building);
                return;
            }
            temp = temp->next;
        }
        printf("Student not found\n");
    }

    // Function to search by building
    void search_building(int s){
    request *current = head;
    int flag = 0;

    while (current != NULL){
        if (current->building == s) {
        printf("%s %s ID: %d, Room %d, Building %d\n", current->name, current->ID, current->room, current->building);
        flag = 1;
        } else {
        printf("No one found!");
        }
        current = current->next;
    }
    if (flag == 0) {
        printf("building is empty\n");
        }
    }

    //Function to delete a request
    void delete_node(int ID) {
        request *temp = head, *prev;
        if (temp != NULL && temp->ID == ID) {
            head = temp->next;
            free(temp);
            return;
        }
        while (temp != NULL && temp->ID != ID) {
            prev = temp;
            temp = temp->next;
        }
        if (temp == NULL) {
            printf("Request not found\n");
            return;
        }
        prev->next = temp->next;
        free(temp);
        printf("Request deleted successfully\n");
    }


    //Function to serve requests in the list
    void serve_request() {
        if (head == NULL) {
            printf("No requests in the queue\n");
            return;
        }
        request *temp = head;
        head = head->next;
        printf("Request served: %s\n", temp->name);
        free(temp);
    }

    void display_requests() {
        if (head == NULL) {
            printf("No requests in the queue\n");
            return;
        }
        request *temp = head;
        int position = 1;
        while (temp != NULL) {
            printf("Position: %d\n", position);
            printf("Name: %s\n", temp->name);
            printf("ID: %d\n", temp->ID);
            printf("Room: %d\n", temp->room);
            printf("Building: %d\n\n", temp->building);
            temp = temp->next;
            position++;
        }
    }


    //function to save to file
    void save_to_file(){
        FILE *fp;
        fp = fopen("data.txt", "w");
        int counter = 0;
        if (fp == NULL) {
            printf("Error opening file for writing\n");
            return;
        }
        request *temp = head;
        while (temp != NULL)
        {
            counter++;
            temp = temp->next;
        }
        request *temp2 = head;
        fprintf(fp, "%d\n", counter);
        while (temp2 != NULL){
            fprintf(fp, "%s %d %d %d\n", temp2->name, temp2->ID, temp2->room, temp2->building);
            temp2 = temp2->next;
        }
        fclose(fp);
        printf("Data saved to file\n");
    }

    //Function to exit program
    void exit_program() {
        save_to_file();
        printf("Exiting program\n");
        exit(0);
    }


    int main(){
        int choice = 0;
        int id, s;
        int pick;
        do{
            printf("1. Create the linked list:\n2. Create a new request:\n3. Search\n4. Delete Request\n5. Serving a Request\n6. Display current requests\n7. Save \n8. Exit\n");
            printf("Please choose an option from the following: ");
            scanf("%d", &choice);
            switch (choice){
                case 1:
                    create_linked_list();
                    break;
                case 2:
                    add_node();
                    break;
                case 3:
                printf("1. Search by ID\n 2.Search by Building\n Choose an option: \n");
                scanf("%d", &pick);
                if (pick == 1)
                {
                    printf("Enter student ID: ");
                    scanf("%d", &id);
                    searchByID(id);
                } else if (pick == 2)
                {
                    printf("Enter the number of the building: ");
                    scanf("%d", &s);
                    search_building(s);
                }
                else printf("Invalid Choice");
                break;
                case 4:
                    printf("Enter student ID: ");
                    scanf("%d", &id);
                    delete_node(id);
                    break;
                case 5:
                    serve_request();
                    break;
                case 6:
                    display_requests();
                    break;
                case 7:
                    save_to_file();
                    break;
                case 8:
                    exit_program(0);
                    break;
                default:
                    printf("Invalid choice, please try again.\n");
                    break;
            }
        }while(choice != 8);
        return 0;
    }


