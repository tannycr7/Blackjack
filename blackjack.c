#include <stdio.h>
#include <stdlib.h>
#include<time.h>
 //GLOBAL VARIABLES
int card[52];
int rounds = 0;
int win = 0;
int turns = 4;
 //PLAYER STATISTICS
void stats() {
  float percent = rounds != 0 ? (float) win / (float) rounds * 100.0 : 0;
  printf("\n PLAYER STATS \n");
  printf("\n Total rounds played : %d", rounds);
  printf("\n Total Wins : %d", win);
  printf("\n Win percentage for player is %.2f%% \n", percent);
}
 //SHUFFLE THE CARDS
void shuffle(int card[]) {
  int i, j;
  int tcard[52];
  for (i = 0; i < 52; i++) {
    tcard[i] = (i / 13 + 3) * 100 + i % 13 + 1;
  }

  srand(time(NULL));

  for (i = 0; i < 52; i++) {
    do {
      j = rand() % 52;
    } while (tcard[j] == 0);

    card[i] = tcard[j];
    tcard[j] = 0;
  }

  printf("\n The deck is shuffled \n");
}
 //DISTRIBUTE CARDS FOR NEXT ROUND
void distribute() {
  int i, j, temp;
  for (j = 0; j < turns; j++) {
    temp = card[0];
    for (i = 0; i < 51; i++) {
      card[i] = card[i + 1];
    }
    card[51] = temp;
  }

}
 //CALCULATE SUIT OF CARD
void facevalue() {
  int j;
  j = (rand() % 4) + 1;
  switch (j) {
  case 1:
    printf(" of Hearts\n");
    break;

  case 2:
    printf(" of Diamonds\n");
    break;

  case 3:
    printf(" of Spades\n");
    break;

  case 4:
    printf(" of Clubs\n");
    break;
  }

}
 //CALCULATE VALUE OF CARDS
void vcard(int a) {
  int value = a % 100;
  if (value == 11) {
    printf(" Jack");
    value = 10;
  } else if (value == 12) {
    printf(" Queen");
    value = 10;
  } else if (value == 13) {
    printf(" King");
    value = 10;
  } else if (value == 1) {
    printf(" Ace");
  } else
    printf(" %d", value);

}
 //GAMEPLAY
int play() {
  int pcard[5] = {0}; //ARRAY OF PLAYER CARDS
  int dcard[5] = {0}; //ARRAY OF DEALER CARDS
  int i;
  int psum = 0;
  int dsum = 0;
  char check;

  if (rounds % 6 == 0) { //SHUFFLE AT THE START AND EVERY 6 ROUNDS
    shuffle(card);
  }

  pcard[0] = card[0];
  pcard[1] = card[1];
  dcard[0] = card[2];
  dcard[1] = card[3];

  printf("\n Dealer's first Card is :");
  vcard(dcard[0]);
  facevalue();
  printf("\n Player's first card is:");
  vcard(pcard[0]);
  facevalue();
  printf("\n Player's second Card is :");
  vcard(pcard[1]);
  facevalue();

  //PLAYERS PLAY
  for (i = 0; i < 2; i++) {
    if (pcard[i] % 100 == 1) {
      printf("\n Chose a value for your Ace Card. Enter (h) for 11 and (l) for 1 : ");
      do {
        scanf(" %c", & check);
      } while (check != 'h' && check != 'l');

      if (check == 'h') {
        psum += 11;
      } else if (check == 'l') {
        psum += 1;
      }

    } else if ((pcard[i] % 100 == 11) || (pcard[i] % 100 == 12) || (pcard[i] % 100 == 13)) {
      psum += 10;
    } else {
      psum += (pcard[i] % 100);
    }
    if (psum > 21) {
      printf("\n The sum of Players card is %d\n", psum);
      printf("DEALER WINS");
      rounds++;
      return 0;

    } else if (psum == 21) {
      printf("\n Sum of Players card is %d. It's a Blackjack. \n", psum);
      printf("PLAYER WINS");
      rounds++;
      win++;
      return 0;
    }
  }

  printf("\n The sum of players card is %d \n", psum);

  //IF PLAYER WANTS TO HIT
  for (i = 0; i < 3; i++) {
    printf("\n Enter (h) for hit and (s) for stand : ");
    do {
      scanf(" %c", & check);
    } while (check != 'h' && check != 's');
    if (check == 'h') {
      pcard[i + 2] = card[i + 4];
      printf("\n Your new card is ");
      turns++;
      vcard(pcard[i + 2]);
      facevalue();

      if (pcard[i + 2] % 100 == 1) {
        printf("\n Chose a value for your Ace Card. Enter (h) for 11 and (l) for 1 : ");
        do {
          scanf(" %c", & check);
        } while (check != 'h' && check != 'l');

        if (check == 'h') {
          psum += 11;
        } else if (check == 'l') {
          psum += 1;
        }
      } else if ((pcard[i + 2] % 100 == 11) || (pcard[i + 2] % 100 == 12) || (pcard[i + 2] % 100 == 13)) {
        psum += 10;
      } else {
        psum += (pcard[i + 2] % 100);
      }
      if (psum > 21) {
        printf("\n Sum of Players card is %d\n", psum);
        printf("\n DEALER WINS");
        rounds++;
        return 0;
      } else if (psum == 21) {
        printf("\n The sum of Player's card is %d. It's a BLACKJACK. \n", psum);
        printf("\n PLAYER WINS");
        rounds++;
        win++;
        return 0;
      } else {
        printf("\n The sum of players card is %d\n", psum);
      }
    } else {
      printf("\n The sum of players card is %d\n", psum);
      break;
    }
  }

  if (i == 3) { //PLAYER WINS BY DEFAULT IF MAX CARDS DRAWN AND POINTS LESS THAN 21
    printf("\n The sum of maximum cards drawn is less than 21\n");
    printf("\n PLAYER WINS");
    rounds++;
    return 0;
  }

  // DEALERS PLAY
  printf("\n Dealer's Second Card is :");
  turns++;
  vcard(dcard[1]);
  facevalue();

  if ((dcard[0] % 100 == 1) && (dcard[1] % 100) == 1) //Check IF BOTH ACE
  {

    dsum = 12;
    printf("\n The sum of Dealer's card is %d\n", dsum);
  } else if ((dcard[0] % 100 == 1 && dcard[1] % 100 == 10) || (dcard[0] % 100 == 10 && dcard[1] % 100 == 1)) // Check IF ACE AND 10 FORM A BLACKJACK
  {
    dsum = 21;
    printf("\n The sum of Dealer's card is %d, It's a BLACKJACK\n", dsum);
    printf("\n DEALER WINS");
    rounds++;
    return 0;
  } else if ((dcard[0] % 100 == 1 && dcard[1] % 100 < 10) || (dcard[1] % 100 == 1 && dcard[0] % 100 < 10)) //CHECK IF ACE AND NUMBER CARD
  {
    dsum = (dcard[0] % 100 + dcard[1] % 100) + 10;
    printf("\n The sum of Dealer's card is %d\n", dsum);
  } else if ((dcard[0] % 100) > 10 && (dcard[1] % 100 > 10)) //CHECK IF BOTH FACE CARD
  {
    dsum = 20;
    printf("\n The sum of Dealer's card is %d\n", dsum);
  } else if ((dcard[0] % 100 == 1 && dcard[1] % 100 > 10) || (dcard[0] % 100 > 10 && dcard[1] % 100 == 1)) //CHECK IF ACE AND FACE CARD
  {
    dsum = 21;
    printf("\n The sum of Dealer's card is %d. It's a BLACKJACK\n", dsum);
    printf("\n DEALER WINS");
    rounds++;
    return 0;

  } else if (((dcard[0] % 100) > 10 && (dcard[1] % 100 < 11)) || ((dcard[0] % 100 < 11) && (dcard[1] % 100) > 10)) // CHECK IF FACE AND NUMBER VARD
  {
    if (dcard[0] % 100 > 10) {
      dsum = dcard[1] % 100 + 10;
      printf("\n The sum of Dealer's card is %d\n", dsum);
    } else {
      dsum = dcard[0] % 100 + 10;
      printf("\n The sum of Dealer's card is %d\n", dsum);
    }
  } else {
    dsum = (dcard[0] % 100 + dcard[1] % 100); // IF BOTH ARE NUMBER CARDS
    printf("\n The sum of Dealer's card is %d\n", dsum);
  }
 //DEALER HITS THE DECK
  for (i = 0; i < 3 && dsum < 17; i++) {     //SOFT 17
    dcard[i + 2] = card[i + 7];
    printf("\n Dealer's new card is");
    turns++;
    vcard(dcard[i + 2]);
    facevalue();

    if (dcard[i + 2] % 100 == 1) {
      if (dsum + 11 <= 21) {
        printf("\n Dealer has chosen Ace value as 11\n");
        dsum = dsum + 11;
        printf("\n The sum of Dealer's cards is now: %d\n", dsum);
      } else {
        printf("\n Dealer has chosen Ace value as 1\n");
        dsum = dsum + 1;
        printf("\n The sum of Dealer's cards is now: %d\n", dsum);
      }
    } else if (dcard[i + 2] % 100 > 10) {
      dsum += 10;
      if (dsum > 21) {
        printf("\n The sum of Dealer's cards is now: %d\n", dsum);
        printf("\n PLAYER WINS");
        rounds++;
        win++;
        return 0;
      } else {
        printf("\n The sum of Dealer's cards is now: %d\n", dsum);
      }
    } else {
      dsum += dcard[i + 2] % 100;
      printf("\n The sum of Dealer's cards is now: %d\n", dsum);
    }

  }
  //COMPARISON
  if (i == 3 && dsum > 22) {
    printf("\n PLAYER WINS");
    rounds++;
    win++;
    return 0;
  } else if (i == 3 && dsum > psum) {
    printf("\n DEALER WINS");
    rounds++;
    win++;
    return 0;
  }
  if (dsum > 21 || psum > dsum) {
    printf("\n PLAYER WINS ");
    rounds++;
    win++;
    return 0;
  } else if (psum == dsum) {
    printf("\n It's a PUSH ");
    rounds++;
    return 0;
  } else if (psum < dsum) {
    printf("\n DEALER WINS ");
    rounds++;
    return 0;
  }
  return 0;
}
 //WELCOME SCREEN
void menu() {
  char input;

  printf("---------------------------------------------------BLACKJACK---------------------------------------------------\n\n Enter : (p) to start Playing, (r) for reading Rules, (q) to Quit the game : ");
  scanf(" %c", & input);

  while (input != 'p' && input != 'r' && input != 'q') {
    printf(" \n Enter a valid input : ");
    scanf(" %c", & input);
  }
  switch (input) {
  case 'p':
    play();
    break;
  case 'r':
    printf(" \n\n---------------------------------------The RULES for BlackJack Simulator---------------------------------------\n\n Player attempts to beat the Dealer by getting a count as close to 21 as possible, without going over 21.\n Face cards are worth 10 , Aces are worth 1 or 11 depending on which makes a better hand.\n Number cards are worth their equivalet value.\n The player starts with two cards, One of the dealer's cards is hidden until the end.\n You need to (Hit) to get a new card or (Stand) to hold your card total.\n If you go over 21 you automatically loose.\n If you get a Blacjack (Ace & 10)  or (Ace & (King ,Queen ,Jack)) at the start you win by default.\n If for 5 turns you don't go over 21, you win by default.\n The players are not allowed to split the cards.\n The game is free of Betting money.\n\n\n ");
    menu();
    break;
  case 'q':
    printf("\n -----------------------------------------");
    printf(" \n Thanks for playing, do come again\n");
    stats();
    exit(0);
    break;
  }
}
int main() {
  char input;
  menu();
  do {
    printf(" \n\n Do you wish to continue further. Enter (y) for yes or any other key to quit the game : ");//ASK USER IF WISH TO CONTINUE THE GAME
    scanf(" %c", & input);
    if (input != 'y') {
      printf("\n -----------------------------------------");
      printf(" \n Thanks for playing! Do come again \n");
      stats();
      return 0;
    } else {
      distribute();
      play();
    }
  }
  while (input == 'y');

  return 0;
}
