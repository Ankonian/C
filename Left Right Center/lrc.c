#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

const char *names[] = {"Whoopi",
			"Dale",
			"Rosie",
			"Jimmie",
			"Barbara",
			"Kyle",
			"Raven",
			"Tony",
			"Jenny",
			"Clint"};
int pot=0;
    typedef enum faciem {LEFT , RIGHT , CENTER , PASS } faces ;
    faces die [] = {LEFT , RIGHT , CENTER , PASS , PASS , PASS };
bool doesPlayerHasMoney(int bank[], int currenPos);
void toss(int bank[], int numPlayers, int currentPlayer, int randomNumber);
bool checkWinStatus(int bank[], int numPlayers);
int whoWon(int bank[], int numPlayer);
int main(void)
{
    int numPlayers;
    unsigned int seed;
    int randomNumber;
    int currentPlayer = 0;   
 /*
     *Create seed for the random number generator and generate a sequence of random numbers  
 *   */
    printf("Enter Seed: "); 
    scanf("%u", &seed); 
    srand(seed); 
   
     /*
     *Ask for how many players 
     */
    printf("How many players? ");
    scanf("%d", &numPlayers);
    /*
    * Create a bank for each player to keep track of where the money goes 
 *  */
    int bank[10];
    for(int i = 0; i < 10; i++)
    {
	bank[i] = 3;
    }
    //the flow of the money after the die is rolled
   int roll = 0;
   int winner;
    while(checkWinStatus(bank, numPlayers))
    {
	if(currentPlayer == numPlayers)
	{
	    currentPlayer = 0;
	}
	if(doesPlayerHasMoney(bank, currentPlayer))
	{
	    printf("%s rolls... ", names[currentPlayer]);
	    roll = bank[currentPlayer];
	    if(roll > 3)
	    {
		roll = 3;
	    }
        }
	for(int i = 0; i < roll; i++)
	{
	    randomNumber = rand() % 6;
	    toss(bank, numPlayers, currentPlayer, randomNumber);
	}
	currentPlayer++;    
	
	printf("\n");
    }
    winner = whoWon(bank, numPlayers);
    printf("%s wins the $%d pot with $%d in the bank\n", names[winner],pot,bank[winner]);
    return 0;

}
void toss(int bank[], int numPlayers, int currentPlayer, int randomNumber)
{
switch(randomNumber)
          {
              case(0):
                  bank[currentPlayer]--;
                   if(currentPlayer == 0)
                   {
                      bank[numPlayers]++;
                      printf(" gives %s $1 ", names[numPlayers]);
                   }
                   else
                   {
                      bank[currentPlayer+1]++;
                      printf(" %s gives %s $1 ",names[currentPlayer], names[currentPlayer-1]);
                   }
                  break;
              case(1):
                  bank[currentPlayer]--;
                  if(currentPlayer == numPlayers)
                  {
                      bank[0]++;
                      printf("  %s gives %s $1",names[currentPlayer], names[0]);
                  }
                  else
                  {
                      bank[currentPlayer+1]++;
                      printf(" %s gives %s $1",names[currentPlayer], names[currentPlayer+1]);
                  }
                  break;
              case(2):
                  bank[currentPlayer]--;
                  pot++;
                  break;
              default:
                  printf(" gets a pass ");
                  break;
          }

}
bool doesPlayerHasMoney(int bank[], int currentPos)
{
    bool hasMoney;
    if(bank[currentPos] > 0)
    {
	hasMoney = true;
    }
    else
    {
	hasMoney = false;
    }
    return hasMoney;
}
bool checkWinStatus(int bank[], int numPlayers)
{
   int numPlayersHaveMoney = 0;
   bool moreThanOnePlayerHasMoney; 
    for(int i = 0; i < numPlayers-1; i++)
    {
	if(bank[i] != 0)
	{
	    numPlayersHaveMoney++;
	}
    }
    if(numPlayersHaveMoney > 1)
    {
	moreThanOnePlayerHasMoney = true;
    }
    else
    {
 	moreThanOnePlayerHasMoney = false;
    }
    return moreThanOnePlayerHasMoney;
}
int whoWon(int bank[], int numPlayer)
{
    int winner = 0;
    for(int i = 0; i <numPlayer; i++)
    {
	if(bank[i] == 0)
	{
	    winner++;
	}
    }
	return winner;
} 
