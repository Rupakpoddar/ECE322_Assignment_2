#include "deck.h"

/*
 * Function: shuffle
 * --------------------
 *  Initializes deck_instance and shuffles it.
 *  Resets the deck if a prior game has been played.
 *
 *  returns: 0 if no error, and non-zero on error
 */
int shuffle(){
  srand(time(0));
  char Suits[4] = {'C', 'D', 'H', 'S'};
  char Ranks[13] = {'2', '3', '4', '5', '6', '7', '8', '9', '0', 'J'
        ,'Q', 'K', 'A'};
  int suit_rep[4] = {0, 0, 0, 0};
  int rank_rep[13] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

  for (int i = 0; i < 52; ++i) {

    int suit_index = rand() % 4;
    suit_rep[suit_index] += 1;
    while(suit_rep[suit_index] > 13){
      suit_index = rand() % 4;
      suit_rep[suit_index] += 1;
    }

    int rank_index = rand() % 13;
    rank_rep[rank_index] += 1;
    while(rank_rep[rank_index] > 4){
      rank_index = rand() % 13;
      rank_rep[rank_index] += 1;
    }

    deck_instance.list[i].suit = Suits[suit_index];
    if (rank_index == 8) {
      deck_instance.list[i].rank[0] = '1';
      deck_instance.list[i].rank[1] = '0';
      deck_instance.list[i].rank[2] = '\0';
    } else {
        deck_instance.list[i].rank[0] = Ranks[rank_index];
        deck_instance.list[i].rank[1] = '\0';
        deck_instance.list[i].rank[2] = '\0';
    }
  }
  /*
  for (int j = 0; j < 52; j++) {
    printf("%s%c\n", deck_instance.list[j].rank, deck_instance.list[j].suit);
  }
  */
  return 0;
}

/*
 * Function: deal_player_cards
 * ---------------------------
 *  Deal 7 random cards to the player specified in the function.
 *  Remove the dealt cards from the deck.
 *
 *  target: pointer to the player to be dealt cards
 *
 *  returns: 0 if no error, and non-zero on error
 */
int deal_player_cards(struct player* target){

}

/*
 * Function: next_card
 * -------------------
 *  Return a pointer to the top card on the deck.
 *  Removes that card from the deck.
 *
 *  returns: pointer to the top card on the deck.
 */
struct card* next_card( ){

}

/*
 * Function: size
 * --------------
 *  Return the number of cards left in the current deck.
 *
 *  returns: number of cards left in the deck.
 */
size_t deck_size( ){

}
