#define _CRT_SECURE_NO_WARNINGS
#include "vector_final.h"
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

void making_first_deck(
    FILE *inp, card x[25]) { // this fucntion scans the file and makes a deck
    int i = 0;

    inp = fopen("_OG_Deck.txt", "r");

    if (inp == NULL) {
      printf("No file data\n");
    }

    while (!feof(inp)) {

      fscanf(inp, "%s", x[i].color);

      fscanf(inp, "%d", &x[i].value);

      fscanf(inp, "%s", x[i].action);

      // incriments "i" so that the next scan will be in the next element position
      i++;
    }
    fclose(inp);
}

void shuffle_first_deck(card x[108]) { // shuffles the deck when called
  int random_k = 0, random_j = 0;
  card temp;

  srand(time(0));

  for (int i = 1000; i > 0; i--) {

    random_k =
        rand() % 108; // Generates two randum elements to swap in the array
    random_j = rand() % 108;

    temp = x[random_k];
    x[random_k] = x[random_j]; // Swaps to elements in array
    x[random_j] = temp;
  }
}

// void deal_card_to_player(
//     card deck[108], card **head, card **tail,
//     int *indexLastCard) { // deals a single card to a player when called

//   card *newCard;
//   newCard = (card *)malloc(sizeof(card));

//   if (deck[108].value == NULL) {
//     suffle_remaining_decks(deck);
//   }
//   strcpy(newCard->action, deck[*indexLastCard].action);
//   strcpy(newCard->color, deck[*indexLastCard].color);
//   newCard->value = deck[*indexLastCard].value;
//   newCard->pt = NULL;

//   if (*head == NULL) {
//     *head = newCard;
//     *tail = newCard;
//   }

//   else {
//     (*tail)->pt = newCard;
//   }

//   *tail = newCard;

//   deck[*indexLastCard].value = NULL;
//   deck[*indexLastCard].action[0] = '\0';
//   deck[*indexLastCard].color[0] = '\0';

//   (*indexLastCard)++; // keeps track of the spot where the last card was dealt
// }
// // this is our most complicated fucntion the main point of the function is to
// // remouve a card from a players hand this function also copies that remouved
// // card so we can keep the memory and assigns it to the discarded variable this
// // function also calls a check function which determines weather the players
// // selected card can be played or not
// bool play_a_card(card deck[25], card **head, card **tail, card **discarded,
//                  int pickedCard, int *currentTotalCards, int *turnCount,
//                  char *changedColor[7]) {
//   card *preTarget = *head;
//   card *temp =
//       *head; // these variebles create many copies of head which we will change
//              // later to the card the player wants to discard or play
//   card *temp1 = *head;
//   bool x = false;
//   bool thisFunction = false;
//   card cardPlayed;

//   if (pickedCard == 1) {
//     preTarget = *head;
//     cardPlayed.value =
//         (*head)->value; // if player chooses first card in hand this makes a
//                         // copy and assigns to cardPlayed
//     strcpy(cardPlayed.color, (*head)->color);
//     strcpy(cardPlayed.action, (*head)->action);

//   }

//   else {
//     for (int i = 1; i < pickedCard - 1; i++) {
//       preTarget = preTarget->pt; // finds location in the list where the players
//                                  // card wanted to be played is
//     }
//     cardPlayed.value = preTarget->pt->value;
//     strcpy(cardPlayed.color,
//            preTarget->pt->color); // makes cardPlayed a copy of that card
//     strcpy(cardPlayed.action, preTarget->pt->action);
//   }

//   if (strcmp(changedColor, cardPlayed.color) == 0) {
//     x = true; // if the color of the card is the same as the color of the
//               // previous played card
//   } // then x is alwasy true wich means the card is allowed to be played

//   else {
//     x = can_card_be_played(
//         deck, cardPlayed, turnCount,
//         &changedColor); // calls a fucntion to cheack weather the card is
//                         // allowed to be played based on uno rules
//   }

//   if (x == true) { // if the condition to play a card is true enter the
//                    // statement

//     // deck[*turnCount + 1].value = cardPlayed.value;
//     // strcpy(deck[*turnCount + 1].color, cardPlayed.color);
//     // strcpy(deck[*turnCount + 1].action, cardPlayed.action);

//     *turnCount++;

//     (*discarded)->value = cardPlayed.value;
//     strcpy((*discarded)->color,
//            cardPlayed.color); //   discarded is a copy of cardPlayed
//     strcpy((*discarded)->action, cardPlayed.action);

//     strcpy(
//         changedColor,
//         (*discarded)->color); //  the previous color is now the new played color

//     // these next lines remouve a card no matter wher is is in the list
//     if (pickedCard < *currentTotalCards && pickedCard > 2) {
//       for (int i = 1; i < pickedCard + 1; i++) {
//         temp = temp->pt;
//       }
//       for (int i = 1; i < pickedCard - 2; ++i) { // remouves card 2-end of list
//         temp1 = temp1->pt;
//       }
//       temp1->pt->pt = temp;
//     }

//     else if (pickedCard == 1 && *currentTotalCards == 1) {
//       return true;
//     } else if (pickedCard == 1) {
//       (*head) = temp->pt;
//       (*head)->pt = temp->pt->pt; // removes fist card

//     } else if (pickedCard == 2) {
//       (*head)->pt = temp->pt->pt; // removes secon card

//     }

//     else if (pickedCard == *currentTotalCards) {
//       for (int i = 1; i < pickedCard - 2; i++) { // middle cards reconects cards
//         temp = temp->pt;
//       }
//       (*tail)->pt = temp;
//       temp->pt->pt = NULL;
//     }

//     thisFunction =
//         true; //  then true is returned becauyse the card can be played

//   } else { // if a card cant be played then false is returned and these if
//            // statments print the card that could not be plyed

//     if ((preTarget->pt->value <= 9) && (preTarget->pt->value >= 0)) {
//       printf("%s %d cannot be placed \n", preTarget->pt->color,
//              preTarget->pt->value);
//     } else if ((strcmp(preTarget->pt->color, "Black") == 0) &&
//                (preTarget->pt->value == -1)) {
//       printf("%s Cannot be placed\n", preTarget->pt->action);
//     } else if ((strcmp(preTarget->pt->color, "Black") != 0) &&
//                (preTarget->pt->value == -1)) {
//       printf("%s %s cannot be placed\n", preTarget->pt->color,
//              preTarget->pt->action);
//     }
//     thisFunction = false;
//   }

//   return thisFunction;
// }

// void IntNode_PrintNodeData(
//     card *head) { // this function prints the players hands

//   while (head != NULL) {

//     if ((head->value <= 9) && (head->value >= 0)) { // here is the problem
//       printf("%s %d, ", head->color, head->value);

//     } else if ((strcmp(head->color, "Black") == 0) && (head->value == -1)) {
//       printf("%s, ", head->action);

//     } else if ((strcmp(head->color, "Black") != 0) && (head->value == -1)) {
//       printf("%s %s, ", head->color, head->action);
//     }

//     head = head->pt;
//   }
// }

// bool can_card_be_played(
//     card deck[108], card cardPlayed, int *turnCount,
//     char *changedColor) { // this function checks if the selected card is
//                           // allowed to be played;
//   card cardTemp;

//   cardTemp.value = cardPlayed.value;
//   strcpy(cardTemp.color, cardPlayed.color);
//   strcpy(cardTemp.action, cardPlayed.action);

//   // if colors are the same a card can be played
//   if (strcmp(cardPlayed.color, deck[*turnCount].color) == 0 ||
//       strcmp(cardPlayed.color, changedColor) == 0) {
//     return true;
//   }
//   // if values are the same then card can be played
//   if (cardPlayed.value == deck[*turnCount].value) {

//     return true;
//   }
//   // if the action are the same then the card acn be played example a red skip
//   // played on top of a blue skip
//   if ((strcmp(cardPlayed.action, cardTemp.action) == 0) &&
//       cardPlayed.value == -1) {
//     return true;
//   }
//   // a wild can always be played no mattter what the car undernieth is
//   if (strcmp(cardPlayed.color, "Black") == 0) {

//     return true;
//   }
//   // if the color changed due to a wild then the next card must be checked to
//   // see if it matches the changed color
//   if (strcmp(changedColor, cardPlayed.color) == 0) {
//     return true;
//   }
//   // if nothing works based on these rules then the card cant be played and the
//   // funtion returns false
//   return false;
// }

// void suffle_remaining_decks(
//     card y[108]) { // if the deck runs out and nobody has won then the discard
//                    // deck is shuffled
//   int random_k = 0, random_j = 0;
//   card temp;

//   srand(time(0));

//   for (int i = 1000; i > 0; i--) {

//     random_k =
//         rand() % 108; // Generates two randum elements to swap in the array
//     random_j = rand() % 108;

//     temp = y[random_k];
//     y[random_k] = y[random_j]; // Swaps to elements in array
//     y[random_j] = temp;
//   }

//   for (int i = 0; i < 108;
//        i++) { // this loop finds the null elements in the array because the
//               // players still have cards in there hands and puts them at the
//               // front of the array
//     if (y[i].value == NULL) {
//       int j = 0;
//       temp = y[i];
//       y[i] = y[j]; // Swaps to elements in array
//       y[j] = temp;
//       j++;
//     }
//   }
// }
