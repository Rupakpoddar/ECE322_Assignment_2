#include "card.h"
#include "player.h"

/*
 * Function: add_card
 * -------------------
 *  Add a new card to the player's hand.
 *
 *  target: the target player
 *  new_card: pointer to the new card to add
 *
 *  returns: return 0 if no error, non-zero otherwise
 */
int add_card(struct player* target, struct card* new_card){
  struct hand* hand_temp = (struct hand*)malloc(sizeof(struct hand));
  if (hand_temp == NULL) {
    return -1;
  }
  if (target->card_list == NULL)
    {
      hand_temp->top = *new_card;
      target->card_list = hand_temp;
      target->hand_size = 1;
    }
  else {
    hand_temp->top = *new_card;
    hand_temp->next = target->card_list;
    target->card_list = hand_temp;
    target->hand_size += 1;
  }
  return 0;
}

/*
 * Function: remove_card
 * ---------------------
 *  Remove a card from the player's hand.
 *
 *  target: the target player
 *  old_card: pointer to the old card to remove
 *
 *  returns: return 0 if no error, non-zero otherwise
 */
int remove_card(struct player* target, struct card* old_card){
  struct hand* temp_hand = target->card_list;
  if(target->hand_size == 0){
    return -1;
  }
  if(temp_hand->top.suit == old_card->suit && strcmp(old_card->rank, temp_hand->top.rank) == 0){
    if(temp_hand->next == NULL){
      target->card_list = NULL;
      target->hand_size = 0;
      return 0;
    }
    else{
      target->card_list = temp_hand->next;
      target->hand_size -= 1;
      return 0;
    }
  }

  while(temp_hand->next != NULL){
    if(temp_hand->next->top.suit == old_card->suit && strcmp(old_card->rank, temp_hand->next->top.rank) == 0){
      if(temp_hand->next->next == NULL){
        temp_hand->next = NULL;
        target->hand_size -= 1;
        return 0;
      }
      else{
        temp_hand->next = temp_hand->next->next;
        target->hand_size -= 1;
        return 0;
      }
    }
    temp_hand = temp_hand->next;
  }
  return -1;
}

/*
 * Function: check_add_book
 * ------------------------
 *  Check if a player has all 4 cards of the same rank.
 *  If so, remove those cards from the hand, and add the rank to the book.
 *  Returns after finding one matching set of 4, so should be called after adding each a new card.
 *
 *  target: pointer to the player to check
 *
 *  Return: a char that indicates the book that was added; return 0 if no book added.
 */
char check_add_book(struct player* target){
  struct hand* temp_hand = target->card_list;
  while(temp_hand != NULL){
    int i = 0;
    char rank[2];
    strcpy(rank, temp_hand->top.rank);
    struct hand* new_temp_hand = target->card_list;
    while(new_temp_hand != NULL){
      if(strcmp(new_temp_hand->top.rank, rank) == 0){
        i++;
      }
      if(i == 4){
        char suit[4] = {'C', 'D', 'H', 'S'};
        for(int j=0; j<4; j++){
          struct card* toRemove = (struct card*)malloc(sizeof(struct card));
          toRemove->suit = suit[j];
          strcpy(toRemove->rank, rank);
          remove_card(target, toRemove);
          free(toRemove);
        }
        strcat(target->book, rank);
        return '1';
      }
      new_temp_hand = new_temp_hand->next;
    }
    temp_hand = temp_hand->next;
  }
  return '0';
}

/*
 * Function: search
 * ----------------
 *  Search a player's hand for a requested rank.
 *
 *  rank: the rank to search for
 *  target: the player (and their hand) to search
 *
 *  Return: If the player has a card of that rank, return 1, else return 0
 */
int search(struct player* target, char* rank){
  struct hand* temp_hand = target->card_list;
  while(temp_hand != NULL){
    if(strcmp(temp_hand->top.rank, rank) == 0){
      return 1;
    }else{
      temp_hand = temp_hand->next;
    }
  }
  return 0;
}

/*
 * Function: transfer_cards
 * ------------------------
 *   Transfer cards of a given rank from the source player's
 *   hand to the destination player's hand. Remove transferred
 *   cards from the source player's hand. Add transferred cards
 *   to the destination player's hand.
 *
 *   src: a pointer to the source player
 *   dest: a pointer to the destination player
 *   rank: the rank to transfer
 *
 *   Return: 0 if no cards found/transferred, <0 if error, otherwise
 *   return value indicates number of cards transferred
 */
int transfer_cards(struct player* src, struct player* dest, char* rank){
  struct hand* temp_hand = src->card_list;
  int i = 0;
  int check = 0;
  while(temp_hand != NULL){
    if(strcmp(temp_hand->top.rank, rank) == 0){
      struct card* toTransfer = &(temp_hand->top);
      check += add_card(dest, toTransfer);
      check += remove_card(src, toTransfer);
      i++;
    }
    temp_hand = temp_hand->next;
  }
  if(i > 0){
    if(check == 0){
      return i;
    }else{
      return -1;
    }
  }
  return 0;
}

/*
 * Function: game_over
 * -------------------
 *   Boolean function to check if a player has 7 books yet
 *   and the game is over
 *
 *   target: the player to check
 *
 *   Return: 1 if game is over, 0 if game is not over
 */
int game_over(struct player* target){
  if(strlen(target->book) == 7){
    return 1;
  }
  else{
    //printf("game over: %d\n", strlen(target->book));
    return 0;
  }
}

/*
 * Function: reset_player
 * ----------------------
 *
 *   Reset player by free'ing any memory of cards remaining in hand,
 *   and re-initializes the book.  Used when playing a new game.
 *
 *   target: player to reset
 *
 *   Return: 0 if no error, and non-zero on error.
 */
int reset_player(struct player* target){
  struct hand* temp_hand = target->card_list;
  while(temp_hand != NULL){
      //printf("Free\n");
      struct hand* copy_hand = temp_hand;
      free(copy_hand);
      temp_hand = temp_hand->next;
    }
    strcpy(target->book, "");
    target->hand_size = 0;
    return 0;
}

/*
 * Function: computer_play
 * -----------------------
 *
 *   Select a rank randomly to play this turn. The player must have at least
 *   one card of the selected rank in their hand.
 *
 *   target: the player's hand to select from
 *
 *   Rank: return a valid selected rank
 */
char computer_play(struct player* target){
  srand(time(0));
  char Ranks[13] = {'2', '3', '4', '5', '6', '7', '8', '9', '0', 'J'
        ,'Q', 'K', 'A'};
  while(1){
      int Random = rand() % 13;
      char RandomRank[3];
      if(Random == 8){
        strcpy(RandomRank, "10");
      }else{
        RandomRank[0] = Ranks[Random];
        RandomRank[1] = '\0';
        RandomRank[2] = '\0';
      }
      int i = search(target, RandomRank);
      //printf("%d\n", i);
      if(i == 1){
        //printf("Hello\n");
        //printf("%s\n", RandomRank);
        //return RandomRank;
        return Ranks[Random];
      }
  }
}

/*
 * Function: user_play
 * -------------------
 *
 *   Read standard input to get rank user wishes to play.  Must perform error
 *   checking to make sure at least one card in the player's hand is of the
 *   requested rank.  If not, print out "Error - must have at least one card from rank to play"
 *   and then re-prompt the user.
 *
 *   target: the player's hand to check
 *
 *   returns: return a valid selected rank
 */
char user_play(struct player* target){
  char input[3];
  printf("Enter a rank that you wish to play: ");
  scanf("%s", input);
  //printf("%s\n", input);
  int i = search(target, input);
  while(i == 0){
    printf("Error - must have at least one card from rank to play\n");
    printf("Enter a rank that you wish to play: ");
    scanf("%s", input);
    i = search(target, input);
  }
  char toReturn;
  if(strcmp(input, "10") == 0){
    toReturn = '0';
  }
  else{
    toReturn = input[0];
  }
  return toReturn;
}
