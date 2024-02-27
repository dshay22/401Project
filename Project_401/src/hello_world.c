#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "other_file.h"

int main() {
    printf("Hello, World!\n");
    helloFromAnotherFile();

    char playAgain = 'y';
    while (playAgain == 'y') {
        FILE *inp = '\0';

        card *headCard1 = '\0';
        card *headCard2 ='\0'; // these two lines create a head for each player hand and are user to make a list of each player hand

        card *tailCard1 ='\0'; // these two lines create a tail for each player hand and are user to make a list of each player hand
        card *tailCard2 = '\0';

        card deck[108]; // Main Deck

        card discarded;

        //discarded = (card *)malloc(sizeof(card)); // The card Player Plays

        int totalCardsPlayerHand1 = 7;
        int totalCardsPlayerHand2 = 7;
        int index = 0;
        int userShuffle, users, targetCard;
        int turnCount = 0;

        char dealCards;

        char changedColor[7];

        bool x = false;
        bool canPlayer1Play = true;
        bool canPlayer2Play = true;

        printf("Let's Play a Game of UNO!!\n");

        printf("Press 1 to shuffle the UNO deck or 2 to load a deck from a file: \n");
        scanf(" %d", &userShuffle); // Checks what players want to do;

        if ((userShuffle != 1) && (userShuffle != 2)) {
            while ((userShuffle != 1) && (userShuffle != 2)) {
                printf("Press 1 to shuffle the UNO deck or 2 to load a deck from a file: \n"); // If wrong key is pressed this keep asking
                scanf(" %d", &userShuffle);
            }
        }
        if (userShuffle == 1) {
            making_first_deck(inp, deck);
            shuffle_first_deck(deck);
            printf("The deck is shuffled. Press any key to deal cards\n"); // call to suffle the deck for the first time
            scanf(" %c", &dealCards);
        } 
        else if (userShuffle == 2) {
            making_first_deck(inp, deck);
            printf("The deck is ready. Press any key to deal cards\n"); // Loads deck from File "OG_deck"
            scanf(" %c", &dealCards);
        }

        if (dealCards != '\0') {
            for (int i = 0; i < totalCardsPlayerHand1; i++) {
                deal_card_to_player(deck, &headCard1, &index);
            } // Deals cards to 2 players
            for (int i = 0; i < totalCardsPlayerHand2; i++) {
                deal_card_to_player(deck, &headCard2, &index);
            }
        }

        deck[0] = deck[index]; // assigns the crad after both hands dealt to zero.

        deck[index].value = '\0';
        deck[index].action[0] = '\0'; // After last card is dealt that card spot in the array becomes '\0'.
        deck[index].color[0] = '\0';

        index++;
        strcpy(changedColor, deck[0].color);
        if ((deck[0].value <= 9) && (deck[0].value >= 0)) {
            printf("Discard Pile: %s %d\n", deck[0].color, deck[0].value);
        } else if ((strcmp(deck[0].color, "Black") == 0) && (deck[0].value == -1)) { // Printing last played card
            printf("Discard Pile: %s\n", deck[0].action);
        } else if ((strcmp(deck[0].color, "Black") != 0) && (deck[0].value == -1)) {
            printf("Discard Pile: %s %s\n", deck[0].color, deck[0].action);
        }

        while (totalCardsPlayerHand1 != 0 || totalCardsPlayerHand2 != 0) { // condition to check the total cards in each player hand,
                        // if zero a player has won loop ends.

            if (canPlayer1Play == true) { // condition to check if player 1 can play because no skip or
                        // draw card was played then
                canPlayer2Play = true;
                printf("Player 1 hand: ");
                IntNode_PrintNodeData(headCard1); // prints the linked list for player 1 hand
                printf("\n");

                while (x != true) { // x is false to start and in line 119 x is set to true if a card can be played this condition checks if the card selected by a player is valid within the rules of Uno

                    printf("Select a card to play (1-%d) or press 0 to draw dards\n", totalCardsPlayerHand1);
                    scanf("%d", &targetCard); // asks and scans the card 1-7 of player hand

                    if (targetCard == 0) { // if player has no playable cards then pressing zero means they can draw a card
                        printf("Discard Pile: %s %d\n", discarded.color, discarded.value);
                        deal_card_to_player(deck, &headCard1, &index); // call function to draw a single card from the deck
                        printf("Player 1 hand: ");
                        IntNode_PrintNodeData(headCard1); // after card is drawn this reprints the hand for redability
                        printf("\n");
                        totalCardsPlayerHand1 += 1; // counter to ensure the hand total is correct in this case the total increases by one
                    } 
                    else {
                        x = play_a_card(deck, &headCard1, &discarded, targetCard, &turnCount, changedColor); // function to check is card can be played
                    }
                    //x = true; //DELET LINE
                }

                totalCardsPlayerHand1 -= 1;
                if (totalCardsPlayerHand1 == 1) {
                    printf("PLAYER 1 'UNO'\n");
                }
                if (totalCardsPlayerHand1 == 0) {
                    break;
                } // if a card can be played then total cards in players hand goes down.

                x = false; // x is reset to false to rpepare for the next players turn
                printf("DICARDED COLOR:: %d %s\n", discarded.value, discarded.color);
                if ((discarded.value <= 9) && (discarded.value >= 0)) {
                  printf("Discard Pile: %s %d\n", discarded.color, discarded.value); // discarded as mentioned abouve is the card a player played
                }
                else if ((strcmp(discarded.color, "Black") == 0) && (discarded.value == -1)) {
                    printf("Discard Pile: %s\n", discarded.action);
                } 
                else if ((strcmp(discarded.color, "Black") != 0) && (discarded.value == -1)) {
                    printf("Discard Pile: %s %s\n", discarded.color, discarded.action);
                }

                if (strcmp(discarded.action, "Wild") == 0) {
                  printf("Player one what color do you choose? (Blue, Red, Green, Yellow), first Letter should be Capatilized.\n"); // if discardedis a special card like a wild of drawt wo these stamentscheck
                  scanf("%s", changedColor); // if these statments detrmine a special card has been played then action happen
                  canPlayer2Play = true;
                  printf("Player chose the new color %s\n", changedColor); // if wild is played then the person can changeg the color
                } 
                else if (strcmp(discarded.action, "Wild-Draw-Four") == 0) {
                    printf("Player one what color do you choose? (Blue, Red, Green, ""Yellow), first Letter should be Capatilized.\n"); // if wild draw four they can change color
                    scanf("%s", changedColor);
                    printf("Player one chose a the new color %s\n", changedColor);

                    for (int i = 0; i < 4; i++) {
                        deal_card_to_player(deck, &headCard2, &index); // deals four cards to other player
                    }

                    canPlayer2Play = false; // skips otherplayers turn
                    totalCardsPlayerHand2 = totalCardsPlayerHand2 + 4; // increments the total by 4
                } 
                else if (strcmp(discarded.action, "Draw-Two") == 0) {
                    for (int i = 0; i < 2; i++) {

                        deal_card_to_player(deck, &headCard2, &index); // draw two card for the other player.
                    }
                    canPlayer2Play = false; // skips other player turn by setting there condition to false
                    totalCardsPlayerHand2 = totalCardsPlayerHand2 + 2;
                } 
                else if (strcmp(discarded.action, "Skip") == 0) {
                    canPlayer2Play = false; // skips other players turn by setting condition to false
                }
                else if (strcmp(discarded.action, "Reverse") == 0) {
                    canPlayer2Play = false;
                } 
                else if (strcmp(discarded.action, "Play") == 0) { // a regular card was played so the other player is allowed to play and the condition is true
                  canPlayer2Play = true;
                }

                ++turnCount; // turncount is incrimented
                deck[turnCount].value = discarded.value; // the deack is now reassigned where the emptyspace is to the discarded card
                strcpy(deck[turnCount].color, discarded.color);
                strcpy(deck[turnCount].action, discarded.action);

                // Much of the next lines are repeated for player two so comments wont
                // be as in depth
            }
        
            if (canPlayer2Play == true) { // checks conditions of the if statments above
                canPlayer1Play = true;
                printf("Player 2 hand: ");
                IntNode_PrintNodeData(headCard2); // print player two hand
                printf("\n");

                while (x != true) { //    x starts as false this condition checks
                                    //    weather a card is valid to play
                    printf("Select a card to Play (1-%d) or press 0 to draw cards\n", totalCardsPlayerHand2);
                    scanf("%d", &targetCard);

                    if (targetCard == 0) {
                    printf("Discard Pile: %s %d\n", discarded.color, discarded.value);
                    deal_card_to_player(deck, &headCard2, &index);
                    printf("Player 2 hand: ");
                    IntNode_PrintNodeData(headCard2);
                    printf("\n");
                    totalCardsPlayerHand2 += 1;
                    } else {
                    x = play_a_card(deck, &headCard2, &discarded, targetCard, &turnCount, changedColor); // x iss set to true if the card can be played
                    }
                }

                x = false;
                totalCardsPlayerHand2 -= 1; // total cards is decreimented if a card is played.
                if (totalCardsPlayerHand2 == 1) {
                    printf("PLAYER 2 'UNO'\n");
                }
                if (totalCardsPlayerHand2 == 0) {
                    break;
                }

                printf("DICARDED COLOR:: %d %s\n", discarded.value, discarded.color);
                if ((discarded.value <= 9) && (discarded.value >= 0)) {
                    printf("Discard Pile: %s %d\n", discarded.color, discarded.value);
                } else if ((strcmp(discarded.color, "Black") == 0) &&
                            (discarded.value == -1)) {
                    printf("Discard Pile: %s\n",
                            discarded.action); // prints the discarded card
                } else if ((strcmp(discarded.color, "Black") != 0) &&
                            (discarded.value == -1)) {
                    printf("Discard Pile: %s %s\n", discarded.color, discarded.action);
                }

                if (strcmp(discarded.action, "Wild") == 0) {
                    printf("Player two what color do you choose? (Blue, Red, Green, "
                            "Yellow), First Letter should be Capatilized.\n");
                    scanf("%s", changedColor);
                    printf("Player two played a Wild and chose a the new color %s\n",
                            changedColor);
                    canPlayer1Play = true;
                } else if (strcmp(discarded.action, "Wild-Draw-Four") == 0) {
                    printf("Player two what color do you choose? (Blue, Red, Green, "
                            "Yellow), First Letter should be Capatilized.\n");
                    scanf("%s", changedColor);
                    printf("Player two played a Wild and chose a the new color %s\n",
                            changedColor);
                    for (int i = 0; i < 4; i++) {

                    deal_card_to_player(deck, &headCard1, &index);
                    }
                    canPlayer1Play = false;
                    totalCardsPlayerHand1 = totalCardsPlayerHand1 + 4;
                } else if (strcmp(discarded.action, "Draw-Two") == 0) {
                    for (int i = 0; i < 2; i++) {
                    deal_card_to_player(deck, &headCard1, &index);
                    }
                    canPlayer1Play = false;
                    totalCardsPlayerHand1 = totalCardsPlayerHand1 + 2;
                } else if (strcmp(discarded.action, "Skip") == 0) {
                    canPlayer1Play = false;
                } else if (strcmp(discarded.action, "Reverse") == 0) {
                    canPlayer1Play = false;
                } else if (strcmp(discarded.action, "Play") == 0) {
                    canPlayer1Play = true;
                }
                ++turnCount;
                deck[turnCount].value = discarded.value;
                strcpy(deck[turnCount].color, discarded.color);
                strcpy(deck[turnCount].action, discarded.action);
            }
            //totalCardsPlayerHand1 = 0; //DELET LINE
            //totalCardsPlayerHand2 = 0; //DELET LINE
        }

        free(headCard1); //after a playerhas won everything is freed free(headCard2); free(tailCard1);
        free(tailCard2);
        //free(deck);

        if (totalCardsPlayerHand1 == 0) {
          printf("\n\n\nPLAYER 1 HAS WON\n\n\n");
          printf("Would you like to play again? y/n"); // prints what player has won
          scanf(" %c", &playAgain);
        }
        
        if (totalCardsPlayerHand2 == 0) {
            printf("\n\n\nPLAYER 2 HAS WON\n\n\n");
            printf("Would you like to play again? y/n");
            scanf(" %c", &playAgain);
        }
    }

    printf("Have Wonderful Time\n");
    return 0;
}
