#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 6
#define LOG_SIZE 6

// For Queue and Stack
char queue[SIZE][20];
char stack[SIZE][20];
int front = 0, rear = -1;
int top = -1;

// For Flight Log
char flightLog[LOG_SIZE][20];
int logCount = 0;
 
 
// Singly Linked List (For Overloaded Drones)
typedef struct SNode {
    char name[20];
    struct SNode* next;
} SNode;
SNode* overloadedHead = NULL;

// Doubly Linked List (For Serviced Drones)
typedef struct DNode {
    char name[20];
    struct DNode* prev;
    struct DNode* next;
} DNode;
DNode* servicedHead = NULL;

// Circular Linked List (For Emergency Drones)
typedef struct CNode {
    char name[20];
    struct CNode* next;
} CNode;
CNode* circularHead = NULL;



// Enqueue a delivery
void enqueue(char request[]) {
    if (rear < SIZE - 1) {
        rear++;
        strcpy(queue[rear], request);
    } else {
        printf("Queue is full.\n");
    }
}

// Dequeue from queue and then push into the stack
void dequeueAndPushToStack() {
    while (front <= rear) {
        strcpy(stack[++top], queue[front++]);
    }
}

// Dispatch urgent deliveries from stack in LIFO order
void dispatchUrgentDeliveries() {
    printf("\nDispatch Order (LIFO):\n");
    while (top >= 0) {
        printf("%s\n", stack[top--]);
    }
}

// Log a delivery with array size 
void logDelivery(char delivery[]) {
    if (logCount < LOG_SIZE) {
        strcpy(flightLog[logCount++], delivery);
    } else {
        printf("Archived: %s\n", flightLog[0]);
        for (int i = 1; i < LOG_SIZE; i++) {
            strcpy(flightLog[i - 1], flightLog[i]);
        }
        strcpy(flightLog[LOG_SIZE - 1], delivery);
    }
}

// Show the current flight log
void showFlightLog() {
    printf("\nCurrent Flight Log:\n");
    for (int i = 0; i < logCount; i++) {
        printf("%s\n", flightLog[i]);
    }
}

// Add to the  overloaded drone list
void addToOverloaded(char name[]) {
    SNode* newNode = (SNode*)malloc(sizeof(SNode));
    strcpy(newNode->name, name);
    newNode->next = overloadedHead;
    overloadedHead = newNode;
}

// Move drone from overloaded to serviced
void moveToServiced(char name[]) {
    SNode *prev = NULL, *temp = overloadedHead;
    while (temp != NULL && strcmp(temp->name, name) != 0) {
        prev = temp;
        temp = temp->next;
    }
    if (temp != NULL) {
        if (prev == NULL) overloadedHead = temp->next;
        else prev->next = temp->next;
        free(temp);
    }

    DNode* newDNode = (DNode*)malloc(sizeof(DNode));
    strcpy(newDNode->name, name);
    newDNode->prev = NULL;
    newDNode->next = servicedHead;
    if (servicedHead != NULL)
        servicedHead->prev = newDNode;
    servicedHead = newDNode;
}

// Traversing the  serviced drones forward
void traverseServicedForward() {
    DNode* temp = servicedHead;
    printf("\nForward Traversal (Serviced Drones):\n");
    while (temp != NULL) {
        printf("%s\n", temp->name);
        temp = temp->next;
    }
}

// Traversing serviced drones backward
void traverseServicedBackward() {
    DNode* temp = servicedHead;
    if (temp == NULL) return;
    while (temp->next != NULL)
        temp = temp->next;

    printf("\nBackward Traversal (Serviced Drones):\n");
    while (temp != NULL) {
        printf("%s\n", temp->name);
        temp = temp->prev;
    }
}

// Add emergency drone to circular list
void addEmergencyDrone(char name[]) {
    CNode* newNode = (CNode*)malloc(sizeof(CNode));
    strcpy(newNode->name, name);
    if (circularHead == NULL) {
        circularHead = newNode;
        newNode->next = newNode;
    } else {
        newNode->next = circularHead->next;
        circularHead->next = newNode;
    }
}

// Traversing emergency drones in loop
void traverseEmergencyLoop(int rounds) {
    if (circularHead == NULL) return;
    CNode* temp = circularHead->next;
    printf("\nEmergency Drone Rerouting Loop:\n");
    for (int i = 0; i < rounds * 2; i++) {
        printf("%s\n", temp->name);
        temp = temp->next;
    }
}

//main menu
int main() {
    int choice;
    char input[20];
    printf("Cargo Drone Traffic Controller\n");

    do {
        printf("\nMENU\n");
        printf("1. Add Delivery Requests (Queue)\n");
        printf("2. Dispatch Urgent Deliveries (Stack)\n");
        printf("3. Log a Delivery (Array)\n");
        printf("4. Show Flight Log\n");
        printf("5. Mark Drone as Overloaded\n");
        printf("6. Service Drone & Move to Serviced List\n");
        printf("7. Traverse Serviced Drones (Forward & Backward)\n");
        printf("8. Add Emergency Drone (Circular List)\n");
        printf("9. Traverse Emergency Reroute Loop\n");
        printf("0. Exit\n");
        
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();  
        
        //calling the functions using switch cases
        switch (choice) {
            case 1:
                printf("Enter delivery name: ");
                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = 0;
                enqueue(input);
                break;
            case 2:
                dequeueAndPushToStack();
                dispatchUrgentDeliveries();
                break;
            case 3:
                printf("Enter delivery to log: ");
                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = 0;
                logDelivery(input);
                break;
            case 4:
                showFlightLog();
                break;
            case 5:
                printf("Enter overloaded drone name: ");
                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = 0;
                addToOverloaded(input);
                break;
            case 6:
                printf("Enter drone name to mark as serviced: ");
                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = 0;
                moveToServiced(input);
                break;
            case 7:
                traverseServicedForward();
                traverseServicedBackward();
                break;
            case 8:
                printf("Enter emergency drone name: ");
                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = 0;
                addEmergencyDrone(input);
                break;
            case 9:
                traverseEmergencyLoop(2);  // looping twice through emergency list
                break;
            case 0:
                printf("Exiting system. Goodbye!\n");
                break;
            default:
                printf("Invalid option. Try again.\n");
        }

    } while (choice != 0);

    return 0;
}