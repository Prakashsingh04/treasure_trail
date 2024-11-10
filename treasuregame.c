#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Node 
{
    char locationName[30];
    int treasures;   
    int traps;       
    char clue[100]; 
    struct Node* next;
    struct Node* prev;
} Node;

Node* createLocation(char* name, int treasures, int traps, char* clue)
 {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->locationName, name);
    newNode->treasures = treasures;
    newNode->traps = traps;
    strcpy(newNode->clue, clue);
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

//link 2 location
void linkLocations(Node* loc1, Node* loc2) {
    loc1->next = loc2;
    loc2->prev = loc1;
}


//traverse
void playGame(Node* start) {
    Node* current = start;
    int totalTreasures = 0;

    while (current != NULL) {
        printf("\nYou have arrived at: %s\n", current->locationName);
        printf("Treasures here: %d | Traps here: %d\n", current->treasures, current->traps);
        printf("Clue: %s\n", current->clue);

        // Encounter treasures and traps
        totalTreasures += current->treasures;
        printf("Current treasure count: %d\n", totalTreasures);

        if (current->traps > 0) {
            printf("You encountered %d traps!\n", current->traps);
            totalTreasures -= current->traps; // Deduct treasures based on traps
        }

        if (totalTreasures <= 0) {
            printf("You lost all your treasures and the game!\n");
            return;
        }

        // Move to the next location or exit
        char choice;
        printf("Move to the next location? (y/n): ");
        scanf(" %c", &choice);
        if (choice == 'y') {
            current = current->next;
        } else {
            printf("Game Over. Final treasure count: %d\n", totalTreasures);
            return;
        }
    }

    printf("Congratulations! You completed the Treasure Trail with %d treasures!\n", totalTreasures);
}

int main() {
    
    Node* start = createLocation("Forest", 5, 1, "Beware of traps in the next location.");
    Node* cave = createLocation("Cave", 8, 3, "Rich treasures ahead but be cautious.");
	Node* underground = createLocation("underground", 5, 3, "you are underground may find gold but be carefull!!!!");    
    Node* beach = createLocation("Beach", 3, 0, "The final location is within reach!");

    
    linkLocations(start, cave);
    linkLocations(cave,underground);
    linkLocations(cave, beach);

    printf("@@@@-Welcome to the Treasure Trail-@@@@\n");
    playGame(start);

    return 0;
}
