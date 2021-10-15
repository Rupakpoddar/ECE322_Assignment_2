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
  //printf("Hello\n");
  srand(time(0));
  char suits[4] = {'C', 'D', 'H', 'S'};
  char ranks[13] = {'2', '3', '4', '5', '6', '7', '8', '9', '0', 'J'
        ,'Q', 'K', 'A'};

  int randomList[52];
  for(int i = 0; i < 52; i++){
    randomList[i] = i;
  }

  for(int i = 0; i < 52; i++){
    int random = rand()%52;
    int temp = randomList[i];
    randomList[i] = randomList[random];
    randomList[random] = temp;
  }

  int count = 0;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 13; j++){
      deck_instance.list[randomList[count]].suit = suits[i];
      if (j == 8) {
        deck_instance.list[randomList[count]].rank[0] = '1';
        deck_instance.list[randomList[count]].rank[1] = '0';
        deck_instance.list[randomList[count]].rank[2] = '\0';
      } else {
          deck_instance.list[randomList[count]].rank[0] = ranks[j];
          deck_instance.list[randomList[count]].rank[1] = '\0';
          deck_instance.list[randomList[count]].rank[2] = '\0';
      }
      count++;
    }
    deck_instance.top_card = 51;
  }

  /*
  for (int j = 0; j < 52; j++) {
    printf("%s%c\n", deck_instance.list[j].rank, deck_instance.list[j].suit);
  }

  return 0;
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
  for(int i=0; i<7; i++){
    add_card(target, &(deck_instance.list[deck_instance.top_card]));
    deck_instance.top_card--;
  }
  return 0;
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
  deck_instance.top_card--;
  if(deck_instance.top_card < -1){
    printf("The deck ran out of cards, press ctrl+c to exit.\n");
    while(1){}
  }
  return &deck_instance.list[deck_instance.top_card+1];
}

/*
 * Function: size
 * --------------
 *  Return the number of cards left in the current deck.
 *
 *  returns: number of cards left in the deck.
 */
size_t deck_size( ){
  return (size_t)deck_instance.top_card;
}
