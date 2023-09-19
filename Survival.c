#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* Structures */

// Base struct for everything with a name/description
// Consider cutting down on the description size if able
struct baseStruct{
    char name[32];
    char description[256];
};

struct itemStruct{
    struct baseStruct info;

    /*
    Differentiates between consumables, key items, equippables.
    Realistically I will probably end up doing more inheritance
    for various item types but who really knows.
    */ 

    int type;
};

struct interactableStruct{
    struct baseStruct info;
    char useText[256];
};

struct locationStruct{
    struct baseStruct info;
    struct interactableStruct interactables[8];
};

struct playerStruct{
    struct baseStruct info;
    struct locationStruct location;
    // struct itemStruct inventory[8];
    int health;
    int hunger;
    int thirst;
};

/* Functions */

// Used to detect valid input from user
void ParseInput(char[]);

// Print an object's name and description
void Inspect(char[]);

/* Variables */

char userInput[32];
char verb[16];
char noun[16];

char *bankVerb[] = {"quit", "inspect"};


int main(){
    system("cls");

    // Initialize Locations
    // Probably find a more convenient way to store/access text data
    // As well as the actual instances of each locationStruct :)
    struct locationStruct forest = {"FOREST", "The trees here are dense and unforgiving."}; 
    struct locationStruct house = {"HOUSE", "A very dead and old place."};

    // Initialize Player
    struct playerStruct player = {"", "Maker of their own destiny.", forest, 100, 0, 0};
    printf("What is your name?: ");
    fgets(player.info.name, sizeof(player.info.name), stdin);
    player.info.name[strcspn(player.info.name, "\n")] = 0;

    // Loop: Display relevant info and prompt player
    do {
        // Prompt
        system("cls");
        printf("| HEALTH: %i | HUNGER: %i | THIRST: %i |\n", player.health, player.hunger, player.thirst);
        printf("\n%s\n", player.location.info.description);
        printf("What are you going to do?\n>");

        // Command parsing
        fgets(userInput, 32, stdin);
        userInput[strcspn(userInput, "\n")] = 0;
        ParseInput(userInput);

        // Command functionality
        for (int pos = 0; pos < sizeof(bankVerb) / sizeof(bankVerb[0]); pos++){
            if (strcmp(verb, *(bankVerb + pos)) != 0){
                continue;
            }

            // Match
            switch (pos){
                case 0: // "quit"
                    exit(0);
                case 1: // "inspect"
                    Inspect(noun);
                    break;
            }
        }

        // Survival factors
        // I basically just made this to make sure the loop works lol
        player.hunger += 25;
        if (player.hunger > 99){
            player.hunger = 100; // Clamping hunger at 100 here, probably a better way to do that
            player.health -= 25;
        }
    }while (player.health > 0);

    // If we've reached this point, the player has died
    printf("\nYour suffering is over, %s", player.info.name);
    fgets(userInput, 1, stdin); // I wanna use something else here to await a keypress

    return 0;
}

void ParseInput(char input[]){

    char *token = strtok(input, " ");
    if (token == NULL){
        strncpy(verb, "", 1);
        strncpy(noun, "", 1);
    }
    else{
        strncpy(verb, token, sizeof(token));
        for (int i = 0; verb[i]; i++){
            verb[i] = tolower(verb[i]);
        }
    
       token = strtok(NULL, " ");
       
       if (token == NULL){
        strncpy(noun, "", 1);
       }
       else{
        strncpy(noun, token, sizeof(token));
        for (int i = 0; noun[i]; i++){
            noun[i] = tolower(noun[i]);
        }
       }
    }
}

void Inspect(char inspected[]){
    // uhhh use a void pointer to access info and cast it as whatever data type we're accessing ?? ig?
    printf("You have inspected %s", inspected);
}