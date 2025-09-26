#include <ctype.h>
#include <stdbool.h> //true or false expressions
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Universal Variables
// CountPlayer and countDealer count how many cards they have.
int numPlayer[10], numDealer[10], score, countPlayer = 0, countDealer = 0, playerTotal, dealerTotal;
char move;
bool playerFinished, dealerFinished, gameFinished;
int cards[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11};
// "FullDeck" are the first predetermined 10 cards, while "Deck" are the deck
// used throughout the game.
int playerFullDeck[10], dealerFullDeck[10], playerDeck[10], dealerDeck[10];

// random number
void randomNum() 
{
  srand(time(NULL));
  for (int i = 0; i < 10; i++) 
  {
    numPlayer[i] = rand() % 13;
    numDealer[i] = rand() % 13;
  }
}

// Predetermines first 10 cards for both the player and the dealer.
void fillDecks() 
{
  for (int i = 0; i < 10; i++) 
  {
    playerFullDeck[i] = cards[numPlayer[i]];
    dealerFullDeck[i] = cards[numDealer[i]];
  }
}

void printPlayerCards() 
{
  printf("Your hand: \n ");
  for (int i = 0; i < countPlayer; i++) 
  {
    printf("%d ", playerDeck[i]);
  }
  printf("\n");
}

void printDealerCards() 
{
  printf("Dealer's hand: \n ");
  for (int i = 0; i < countDealer; i++) 
  {
    if (countDealer == 1) 
    {
      printf("%d ?", dealerDeck[i]);
    } else 
    {
      printf("%d ", dealerDeck[i]);
    }
  }
  printf("\n");
}

void checkIfOver21Dealer() 
{
  dealerTotal = 0;
  // Gets dealer total.(used many times throught the program)
  for (int i = 0; i < countDealer; i++) 
  {
    dealerTotal += dealerDeck[i];
  }

  // If over 21, end dealer move and check who wins.
  if (dealerTotal > 21) 
  {
    printf("BUST!!! The dealer went Over 21. You win. \n");
    dealerFinished = true;
    gameFinished = true;
  }
}

// Check if the total of dealer is bigger than total of player.
// If it is, dealer doesnt hit.
// If it isn't, dealer hits.
bool DealerBiggerThanPlayer() 
{
  bool bigger;
  dealerTotal = 0;
  for (int i = 0; i < countDealer; i++) 
  {
    dealerTotal += dealerDeck[i];
  }

  if (dealerTotal > playerTotal) 
  {
    bigger = true;
  } else 
  {
    bigger = false;
  }
  return bigger;
}

void oneMoreCardDealer() 
{
  dealerDeck[countDealer] = dealerFullDeck[countDealer];
  countDealer++;
}

void getDealerHand() 
{
  if (!DealerBiggerThanPlayer()) 
  {
    oneMoreCardDealer();
    printDealerCards();
  } else 
  {
    dealerFinished = true;
  }
}

void oneMoreCardPlayer() 
{
  playerDeck[countPlayer] = playerFullDeck[countPlayer];
  countPlayer++;
}

void checkIfOver21Player() 
{
  // Gets player total.(used many times throught the program)
  playerTotal = 0;
  for (int i = 0; i < countPlayer; i++) 
  {
    playerTotal += playerDeck[i];
  }

  // If over 21, end player move and check who wins.
  if (playerTotal > 21) 
  {
    printf("BUST!!! You went over 21. You Lost. \n");
    playerFinished = true;
    gameFinished = true;
  }
}

void getPlayerHand() 
{
  printf("Do you want to HIT or STAND?(H/S):  ");
  move = getchar(); // Player input, hit(h) or stand(s).
  getchar();

  switch (toupper(move)) 
  {
  case 'H': // Hit
    oneMoreCardPlayer();
    printPlayerCards();
    break;

  case 'S': // Stand
    printPlayerCards();
    playerFinished = true;
    break;
  }
}

void compare() 
{
  gameFinished = true;
  // Recalling dealer's total score.
  dealerTotal = 0;
  for (int i = 0; i < countDealer; i++) 
  {
    dealerTotal += dealerDeck[i];
  }
  // Recalling player's total score.
  playerTotal = 0;
  for (int i = 0; i < countPlayer; i++) 
  {
    playerTotal += playerDeck[i];
  }

  if (dealerTotal <= 21) 
  {
    if (playerTotal > dealerTotal) 
    {
      printf("You won! :o\n");
    } else if (playerTotal < dealerTotal) 
    {
      printf("Dealer won! :c\n");
    }
  }
}

void printResultsTXT() 
{
  // Recalling dealer's total score.
  dealerTotal = 0;
  for (int i = 0; i < countDealer; i++) 
  {
    dealerTotal += dealerDeck[i];
  }
  // Recalling player's total score.
  playerTotal = 0;
  for (int i = 0; i < countPlayer; i++) 
  {
    playerTotal += playerDeck[i];
  }

  FILE *fpt;
  fpt = fopen("results.txt", "w");
  fprintf(fpt, "RESULTS:");

  // Prints the player's hand on the .txt file.
  fprintf(fpt, "Your hand: \n ");
  for (int i = 0; i < countPlayer; i++) 
  {
    fprintf(fpt, "%d ", playerDeck[i]);
  }
  fprintf(fpt, "\n");

  // Prints the dealer's hand on the .txt file.
  fprintf(fpt, "Dealer's hand: \n ");
  for (int i = 0; i < countDealer; i++) 
  {
    fprintf(fpt, "%d ", dealerDeck[i]);
  }
  fprintf(fpt, "\n");

  // Prints an outcome of the game.
  if (playerTotal > 21) 
  {
    fprintf(fpt, "BUST!!! You went over 21. You Lost. \n");
  }

  // Prints another outcome of the game.
  if (dealerTotal > 21) 
  {
    fprintf(fpt, "BUST!!! The dealer went Over 21. You win. \n");
  } else 
  {
    if (playerTotal < dealerTotal) 
    {
      fprintf(fpt, "Dealer won! :c\n");
    }
  }

  // Prints total score of both the player and the dealer.
  fprintf(fpt, "\nPlayers's score: %d\n", playerTotal);
  fprintf(fpt, "Dealer's score: %d\n", dealerTotal);
}

void playGame() 
{
  gameFinished = false, playerFinished = false, dealerFinished = false;

  randomNum();
  fillDecks();

  oneMoreCardPlayer(); // This is the player's first card.
  oneMoreCardPlayer(); // This is the player's second card.

  printPlayerCards();

  oneMoreCardDealer(); // This is the dealer's first card.
  printDealerCards();

  while (!gameFinished) 
  {
    while (!playerFinished) 
    {
      getPlayerHand();
      checkIfOver21Player();
    }

    if (gameFinished) 
    {
      printResultsTXT(); // Prints when player goes over 21 on .txt file.
      return;            // Calls back to main
    }

    while (!dealerFinished) 
    {
      getDealerHand();
      checkIfOver21Dealer();
    }
    compare();
    printResultsTXT();
  }
}

// main function
int main() 
{
  printf("Terminology:\n*HIT(H) means that the player will get one more card.\n*STAND(S) means that the player does not want to get more cards and the dealer will play.\n*BUST means that the player of the dealer has gone over 21.\n\n");
  printf("Games is starting! \n\n");
  playGame();
  printf("\nGame finished! \n");

  return 0;
}