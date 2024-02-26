#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct card_s {
  char color[7];
  int value;
  char action[15];
  struct card_s *pt;
} card;

void making_first_deck(FILE *inp, card x[108]); // scan the file into a deck

void shuffle_first_deck(card x[108]); // if player chooses to shuffle this
                                      // function is called an deck is shufled

void deal_card_to_player(
    card deck[108], card **head, card **tail,
    int *indexLastCard); // deals a card from the deck array into a players hand

bool can_card_be_played(card deck[108], card cardPlayed, int *turnCount,
                        char *changedColor); // checks if a card can be played

bool play_a_card(
    card deck[108], card **head, card **tail, card **discarded, int pickedCard,
    int *currentTotalCards, int *turnCount,
    char *changedColor[7]); // deletes a card from the players hand as they play
                            // it keeps track of number of cards in players hand
                            // keeps track of the discarded card

void IntNode_PrintNodeData(
    card *list); // prints the current cards in a players hand

void suffle_remaining_decks(
    card y[108]); // shuffle the deck if the game is not over by the time the
                  // players go through the deck
