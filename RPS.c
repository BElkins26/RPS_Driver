#include <stdio.h>
#include <stdlib.h>

int main()
{
FILE  *rpsfile = fopen("/dev/rps", "r");
char str[4];
char playchoice[9]; /* Here all the variables that I'll need for the program are created/declared */
int cmpchoice=0;
int playwins = 0;


int cmpwins = 0;
char *buffer=malloc(sizeof(char));
incaseofcaseerrors:
printf("\nWould you like to play rock paper scissors? yes/no\t");
scanf("%s", str);
if(strcmp(str, "yes") != 0 && strcmp(str, "Yes") != 0 && strcmp(str, "no") != 0 && strcmp(str, "No")) /*Program checks to make sure that user entered a valid form of yes or no, if they did not sends them back */
{
printf("\nYou did not indicate yes or no, please enter yes or no next time.");
goto incaseofcaseerrors;
}
while ((strcmp(str, "yes") == 0 || strcmp(str, "Yes") == 0) && (playwins < 3 && cmpwins < 3)) { /* Loops while the user had answered yes and neither the player nor computer has 3 wins*/
incaseofchoiceerrors:
printf("\nWhat is your choice? Please enter 'scissors', 'rock', or 'paper'.\t");
scanf("%s", playchoice);
printf("hereeeeee\n");
fread(buffer, 1, 1, rpsfile);
printf("char: %d\n", buffer[0]);
if(buffer[0]==1)
	cmpchoice=1;
else if(buffer[0]==2)
	cmpchoice=2;
else if(buffer[0]==3)
	cmpchoice=3;
else 
{
	printf("There was an error getting a thing from the device driver");
}
if(strcmp(playchoice, "rock") == 0 || strcmp(playchoice, "Rock") == 0) /*Program checks if the player entered rock, paper, or scissors.  If they didn't it sends them back */ 
{
    switch(cmpchoice) {
    case 1 :
        printf("\nThe computer chose rock so it's a tie! Nobody wins this time");
        printf("\nScore - Computer: %d Player: %d",cmpwins,playwins);
        break;
    case 2 :
        printf("\nThe computer chose paper! Paper covers rock, so you lose this time."); /*Program decides if player won or lost the round (or tied) based on the random value produced by the rand command*/
        cmpwins = cmpwins + 1;
        printf("\nScore - Computer: %d Player: %d",cmpwins,playwins);
        break;
    case 3 :
        printf("\nThe computer chose scissors! Rock beats scissors, so you win this round!");
        playwins = playwins + 1;
        printf("\nScore - Computer: %d Player: %d",cmpwins,playwins);
        break;
    }
}
else if(strcmp(playchoice, "scissors") == 0 || strcmp(playchoice, "Scissors") == 0)
{
    switch(cmpchoice) {
    case 3 :
        printf("\nThe computer chose scissors so it's a tie! Nobody wins this time");
        printf("\nScore - Computer: %d Player: %d",cmpwins,playwins);
        break;
    case 1 :
        printf("\nThe computer chose rock! Rock beats scissors, so you lose this time.");
        cmpwins = cmpwins + 1;
        printf("\nScore - Computer: %d Player: %d",cmpwins,playwins);
        break;
    case 2 :
        printf("\nThe computer chose paper! Scissors cut paper, so you win this round!");
        playwins = playwins + 1;
        printf("\nScore - Computer: %d Player: %d",cmpwins,playwins);
        break;
    }
}
else if(strcmp(playchoice, "paper") == 0 || strcmp(playchoice, "Paper") == 0)
{
    switch(cmpchoice) {
    case 2 :
        printf("\nThe computer chose paper so it's a tie! Nobody wins this time");
        printf("\nScore - Computer: %d Player: %d",cmpwins,playwins);
        break;
    case 3 :
        printf("\nThe computer chose scissors! Scissors cut paper, so you lose this time.");
        cmpwins = cmpwins + 1;
        printf("\nScore - Computer: %d Player: %d",cmpwins,playwins);
        break;
    case 1 :
        printf("\nThe computer chose rock! Paper covers rock, so you win this round!");
        playwins = playwins + 1;
        printf("\nScore - Computer: %d Player: %d",cmpwins,playwins);
        break;
    }
}
else
{
printf("\nIncorrect entry, please choose either rock, paper, or scissors");
goto incaseofchoiceerrors;
}
} 
if(strcmp(str, "no") != 0 && strcmp(str, "No") != 0) { /* If player has not answered no to the question asked at the beginning of the program, prints out final score and asks the user if they want to play again */
printf("\nFinal Score - Computer: %d Player: %d",cmpwins,playwins);
if(playwins > cmpwins)
{
printf("\nYou win!");
}
else if(cmpwins > playwins)
{
printf("\nYou lose!");
}
else if(cmpwins == playwins)
{
printf("\nIt's a tie!");
}
playwins=0;
cmpwins=0;
printf("\nDo you want to play again? yes/no\t");
scanf("%s",str);
if((strcmp(str, "yes") == 0 || strcmp(str, "Yes") == 0))
{
goto incaseofchoiceerrors;
}
else {
printf("\nThanks for playing! We hope you play again soon!\n");
}
}
else {
printf("Thanks, we hope you choose to play another time!\n");
}
close(rpsfile);
free(buffer);
return 0;
}
