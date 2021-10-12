#include <stdio.h>
#include "card.h"
#include "player.h"
#include "deck.h"

int main(int args, char* argv[])
{
  fprintf(stdout, "Put your code here.\n");

  struct player* user = (struct player*)malloc(sizeof(struct player));
  struct player* computer = (struct player*)malloc(sizeof(struct player));

  struct card* temp1 = (struct card*)malloc(sizeof(struct card));
  struct card* temp2 = (struct card*)malloc(sizeof(struct card));
  struct card* temp3 = (struct card*)malloc(sizeof(struct card));
  struct card* temp4 = (struct card*)malloc(sizeof(struct card));
  struct card* temp5 = (struct card*)malloc(sizeof(struct card));

  temp1->suit = 'H';
  temp1->rank[0] = '1';
  temp1->rank[1] = '0';

  temp2->suit = 'S';
  temp2->rank[0] = '5';

  temp3->suit = 'D';
  temp3->rank[0] = '5';

  temp4->suit = 'H';
  temp4->rank[0] = '5';

  temp5->suit = 'C';
  temp5->rank[0] = '5';

  int val = add_card(user, temp1);
  val = add_card(user, temp2);
  val = add_card(user, temp3);
  val = add_card(user, temp4);
  val = add_card(user, temp5);

  /*
  struct hand* temp_hand = (struct hand*)malloc(sizeof(struct hand));
  temp_hand = user->card_list;
  printf("\n");
  for(int i = 0; i < user->hand_size; i++){
    printf("%s%c\n", temp_hand->top.rank, temp_hand->top.suit);
    temp_hand = temp_hand->next;
  }

  val = remove_card(user, temp3);

  temp_hand = user->card_list;
  printf("\n");
  for(int i = 0; i < user->hand_size; i++){
    printf("%s%c\n", temp_hand->top.rank, temp_hand->top.suit);
    temp_hand = temp_hand->next;
  }

  val = search(user, "J");
  printf("%d\n", val);

  //printf("%d\n", strlen(user->book));
  //char isBook = check_add_book(user);
  //printf("%d\n", strlen(user->book));
  //printf("val = %c\n", isBook);
  transfer_cards(user, computer, "10");

  temp_hand = (struct hand*)malloc(sizeof(struct hand));
  temp_hand = user->card_list;
  printf("\n");
  for(int i = 0; i < user->hand_size; i++){
    printf("User: %s%c\n", temp_hand->top.rank, temp_hand->top.suit);
    temp_hand = temp_hand->next;
  }

  temp_hand = computer->card_list;
  printf("\n");
  for(int i = 0; i < computer->hand_size; i++){
    printf("Computer: %s%c\n", temp_hand->top.rank, temp_hand->top.suit);
    temp_hand = temp_hand->next;
  }

  int isOver = game_over(user);
  printf("Is Over: %d\n", isOver);

  shuffle();
  */

  free(user);
  free(computer);
  free(temp1);
  free(temp2);
  free(temp3);
  free(temp4);
  free(temp5);
}
