#include <stdio.h>
#include "card.h"
#include "player.h"
#include "deck.h"
#include "gofish.h"

void displayHand(struct player* user){
  printf("Player 1's Hand - ");
  struct hand* temp_hand = (struct hand*)malloc(sizeof(struct hand));
  temp_hand = user->card_list;
  for(int i = 0; i < user->hand_size; i++){
    printf("%s%c ", temp_hand->top.rank, temp_hand->top.suit);
    temp_hand = temp_hand->next;
  }
  printf("\n");
  free(temp_hand);
}

void displayBook(struct player* target, int playernum){
  printf("Player %d's Book - ", playernum);
  for(int i=0; i<strlen(target->book); i++){
    if(target->book[i] == '0'){
      printf("10 ");
    }else{
      printf("%c ", target->book[i]);
    }
  }
  printf("\n");
}

int main(int args, char* argv[])
{
  //fprintf(stdout, "----- Go Fish Begins -----\n");

  struct player* user = (struct player*)malloc(sizeof(struct player));
  struct player* computer = (struct player*)malloc(sizeof(struct player));

  char play = 'Y';
  while(play == 'Y'){
    printf("\n----- Go Fish Begins -----\n\n");
    shuffle();
    deal_player_cards(user);      // 1
    deal_player_cards(computer);  // 2
    int turn = 1;

    while(1){
      displayHand(user);
      displayBook(user, 1);
      displayBook(computer, 2);


      if(turn == 1){
        char rank = user_play(user);
        char newRank[3];
        if (rank == '0'){
          strcpy(newRank, "10");
        }else{
          newRank[0] = rank;
          newRank[1] = '\0';
          newRank[2] = '\0';
        }
        int result = search(computer, newRank);
        //printf("Result %d\n", result);
        if(result > 0){
          //displayHand(computer);
          printf("\t- Player 2 has ");
          struct hand* temp_hand = (struct hand*)malloc(sizeof(struct hand));
          temp_hand = computer->card_list;
          for(int i = 0; i < computer->hand_size; i++){
            //printf("in loop\n");
            if(strcmp(temp_hand->top.rank, newRank) == 0){
              printf("%s%c ", temp_hand->top.rank, temp_hand->top.suit);
            }
            temp_hand = temp_hand->next;
          }
          printf("\n");
        }
        int status = transfer_cards(computer, user, newRank);
        //printf("Status: %d\n",status);
        if(status == 0){
          printf("\t- Player 2 has no %s's\n", newRank);
          struct card* newCard = next_card();
          printf("\t- Go Fish, Player 1 draws %s%c\n", newCard->rank, newCard->suit);
          add_card(user, newCard);
        }
        char isNewBook = check_add_book(user);
        if(isNewBook == '0'){
          turn = 2;
        }else if(isNewBook == '1'){
          printf("\t- Player 1 books 10\n");
          printf("\t- Player 1 gets another turn\n");
        }else{
          printf("\t- Player 1 books %c\n", isNewBook);
          printf("\t- Player 1 gets another turn\n");
        }
        printf("\n");
        //break;
        if(game_over(user) == 1){
          printf("Player 1 Wins! 7-%d\n", strlen(computer->book));
          break;
        }
      }

  // ---------------------------------------------------------------- //

      if(turn == 2){
        char rank = computer_play(computer);
        char newRank[3];
        if (rank == '0'){
          strcpy(newRank, "10");
        }else{
          newRank[0] = rank;
          newRank[1] = '\0';
          newRank[2] = '\0';
        }
        printf("Player 2's turn, enter a Rank: %s\n", newRank);
        int result = search(user, newRank);
        //printf("Result %d\n", result);
        if(result > 0){
          //displayHand(computer);
          printf("\t- Player 1 has ");
          struct hand* temp_hand = (struct hand*)malloc(sizeof(struct hand));
          temp_hand = user->card_list;
          for(int i = 0; i < user->hand_size; i++){
            //printf("in loop\n");
            if(strcmp(temp_hand->top.rank, newRank) == 0){
              printf("%s%c ", temp_hand->top.rank, temp_hand->top.suit);
            }
            temp_hand = temp_hand->next;
          }
          printf("\n");
        }

        printf("\t- Player 2 has ");
        struct hand* temp_hand = (struct hand*)malloc(sizeof(struct hand));
        temp_hand = computer->card_list;
        for(int i = 0; i < computer->hand_size; i++){
          //printf("in loop\n");
          if(strcmp(temp_hand->top.rank, newRank) == 0){
            printf("%s%c ", temp_hand->top.rank, temp_hand->top.suit);
          }
          temp_hand = temp_hand->next;
        }
        printf("\n");

        int status = transfer_cards(user, computer, newRank);
        //printf("Status: %d\n",status);
        if(status == 0){
          printf("\t- Player 1 has no %s's\n", newRank);
          struct card* newCard = next_card();
          printf("\t- Go Fish, Player 2 draws %s%c\n", newCard->rank, newCard->suit);
          add_card(computer, newCard);
        }
        char isNewBook = check_add_book(computer);
        if(isNewBook == '0'){
          turn = 1;
        }else if(isNewBook == '1'){
          printf("\t- Player 2 books 10\n");
          printf("\t- Player 2 gets another turn\n");
        }else{
          printf("\t- Player 2 books %c\n", isNewBook);
          printf("\t- Player 2 gets another turn\n");
        }
        printf("\n");
        //break;
        if(game_over(computer) == 1){
          printf("Player 2 Wins! 7-%d\n", strlen(user->book));
          break;
        }
      }
    }
    printf("Do you want to play again [Y/N]:");
    scanf(" %c", &play);
    if(play == 'N'){
      printf("Exiting.\n");
    }
    else if(play == 'Y'){
      printf("Re-starting game.\n");
      reset_player(user);
      reset_player(computer);
    }
    else{
      printf("Invalid input. Exiting.\n");
    }
  }
  free(user);
  free(computer);
}
