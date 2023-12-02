/*
----------------------------------------------------------------------------------
	Program 2: Wumpus, version 2
  Course: CS 211, Fall 2022. Tues 8am Lab. Friday 1pm Lecture.
  System: Windows using Replit
  Submission: 10/08/2022
  Author: Bilguun Munkh-Erdene
  UIN: 652110707
  Late Submission Essay: I did not use any of the code from the posted Program 2 solution. 
  One of the differences i noticed was in the posted solution's resetPositions(...) function and my reset(...) function. In my program, the reset function has an extra line of code for the arrows, in case the player decides to put the location of the arrow to -1, then the player will automatically acquire the arrow. 
Another difference can be found in the function that moves players to a random place if the player location is the same as one of the bats' locations. In my solution, the function executes similarly to the functions that detect nearby hazards. I allocated space for three different locations and set them to random locations using the setUniqueValues(...) function from the first posted solution. The first location is for the player to move into after being teleported by the bats, the second location is for the bat to move into after teleporting the player, the third location is to store the bat's location that hasn't moved yet. I will comment that the posted solution's function is much more in-depth with how it uses variables to store the player's old and new location, and the comments help understand what exactly is going on. However, I think that albeit elaborate, the posted solution's function has a lot of information and may be confusing to people. So, I think my solution would generally be easier to understand and also much better for implementation, since most people didn't use the way shown in the posted solution.
The implementation of the shootArrow(...) function for both my and the posted solution's are very similar to each other, so I commend both solutions for implementation and ease of understanding. The function displayRoomInfo(...) detects nearbyHazards just like how my function nearbyDangers(...) and nearbyBats(...) do as well, though the main difference is in the posted solution, the professors resorted to creating separate variables for the rooms that are adjacent to the player. This declaration makes the code more easier to follow, but at the cost of efficiency. In my solution, I've used a for loop to quickly traverse through each adjacent room. I think in this case, using a for loop is a much better option to go through the adjacent rooms rather than declaring separate variables for them. It cuts down a lot of unnecessary work of having to manually check each adjacent room rather than having a single for loop to check it for you without difficulty. Another difference I noticed is in the main function, it is the implementation of how player "choice" input is taken. In the posted solution, professor Dale Reed and Ellen Kidane have opted to use if-else loops for which move the player decides to play when running the program. In my opinion, this is really more of what comes naturally to the person coding, so I cannot say which implementation IS better, but I can offer which implementation i favor more. I've used the switch code implementation, the reason I've used this is because from the perspective of someone else, it would be more understandable and easier to read through. Once again, this is really more of what comes naturally to the programmer, but I do like how the professors chose to implement the toupper() function to make the code more efficient. 
In conclusion, I really like the posted solution by the professors. I think there are some great lessons to take away from their code when closely inspected, and comparing it to my code has been a valuable learning experience.
  
----------------------------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>		// for srand
#include <stdbool.h>	// for the bool type in C
#include <time.h> // for time

//--------------------------------------------------------------------------------

// begin displayCave() - shows the outline of the in-game cave with a squashed dodecahedron

void displayCave()
{
    printf( "\n"
			"       ______18______             \n"
    		"      /      |       \\           \n"
    		"     /      _9__      \\          \n"
    		"    /      /    \\      \\        \n"
    		"   /      /      \\      \\       \n"
    		"  17     8        10     19       \n"
    		"  | \\   / \\      /  \\   / |    \n"
    		"  |  \\ /   \\    /    \\ /  |    \n"
    		"  |   7     1---2     11  |       \n"
    		"  |   |    /     \\    |   |      \n"
    		"  |   6----5     3---12   |       \n"
    		"  |   |     \\   /     |   |      \n"
    		"  |   \\       4      /    |      \n"
    		"  |    \\      |     /     |      \n"
    		"  \\     15---14---13     /       \n"
    		"   \\   /            \\   /       \n"
    		"    \\ /              \\ /        \n"
    		"    16---------------20           \n"
    		"\n");
}

// end displayCave()

//--------------------------------------------------------------------------------

//begin displayInstructions() - Shows instructions for players on how to play the game and also about how the game works

void displayInstructions()
{
    printf( "Hunt the Wumpus:                                             \n"
    		"The Wumpus lives in a completely dark cave of 20 rooms. Each \n"
    		"room has 3 tunnels leading to other rooms.                   \n"
    		"                                                             \n"
    		"Hazards:                                                     \n"
        	"1. Two rooms have bottomless pits in them.  If you go there you fall and die.   \n"
        	"2. Two other rooms have super-bats.  If you go there, the bats grab you and     \n"
        	"   fly you to some random room, which could be troublesome.  Then those bats go \n"
        	"   to a new room different from where they came from and from the other bats.   \n"
    		"3. The Wumpus is not bothered by the pits or bats, as he has sucker feet and    \n"
        	"   is too heavy for bats to lift.  Usually he is asleep.  Two things wake       \n"
        	"    him up: Anytime you shoot an arrow, or you entering his room.  The Wumpus   \n"
        	"    will move into the lowest-numbered adjacent room anytime you shoot an arrow.\n"
        	"    When you move into the Wumpus' room, then he wakes and moves if he is in an \n"
        	"    odd-numbered room, but stays still otherwise.  After that, if he is in your \n"
        	"    room, he snaps your neck and you die!                                       \n"
        	"                                                                                \n"
        	"Moves:                                                                          \n"
        	"On each move you can do the following, where input can be upper or lower-case:  \n"
        	"1. Move into an adjacent room.  To move enter 'M' followed by a space and       \n"
        	"   then a room number.                                                          \n"
        	"2. Shoot your guided arrow through a list of up to three adjacent rooms, which  \n"
        	"   you specify.  Your arrow ends up in the final room.                          \n"
        	"   To shoot enter 'S' followed by the number of rooms (1..3), and then the      \n"
        	"   list of the desired number (up to 3) of adjacent room numbers, separated     \n"
        	"   by spaces. If an arrow can't go a direction because there is no connecting   \n"
        	"   tunnel, it ricochets and moves to the lowest-numbered adjacent room and      \n"
        	"   continues doing this until it has traveled the designated number of rooms.   \n"
        	"   If the arrow hits the Wumpus, you win! If the arrow hits you, you lose. You  \n"
        	"   automatically pick up the arrow if you go through a room with the arrow in   \n"
        	"   it.                                                                          \n"
        	"3. Enter 'R' to reset the person and hazard locations, useful for testing.      \n"
        	"4. Enter 'C' to cheat and display current board positions.                      \n"
        	"5. Enter 'D' to display this set of instructions.                               \n"
        	"6. Enter 'P' to print the maze room layout.                                     \n"
        	"7. Enter 'X' to exit the game.                                                  \n"
        	"                                                                                \n"
        	"Good luck!                                                                      \n"
        	" \n\n");
}

//end displayInstructions()

//--------------------------------------------------------------------------------

// Return true if randomValue is already in array

int alreadyFound(int randomValue,      // New number we're checking
                 int randomNumbers[],  // Set of numbers previously found
                 int limit)            // How many numbers previously found
{
    int returnValue = false;
    
    // compare random value against all previously found values
    for( int i = 0; i<limit; i++) {
        if( randomValue == randomNumbers[i]) {
            returnValue = true;   // It is already there
            break;
        }
    }
    
    return returnValue;
} 

// end alreadyFound(...)

//--------------------------------------------------------------------------------

// Fill this array with unique random integers 1..20

void setUniqueValues(int randomNumbers[],   // Array of random numbers
                     int size)              // Size of random numbers array
{
    int randomValue = -1;
    
    for( int i = 0; i<size; i++) {
        do {
            randomValue = rand() % 20 + 1;   // random number 1..20
        } while (alreadyFound(randomValue, randomNumbers, i));
        randomNumbers[i] = randomValue;
    }
} 

// end setUniqueValues(...)

//--------------------------------------------------------------------------------

//begin movePlayer(...) - function moves player from their current room to adjacent room (Prompted with character "M")

void movePlayer(int *person, int **rooms[20][3], int *times, int *newPerson) 
{
      int inputLoc; // variable for new location for person
      scanf(" %d", &inputLoc); // space before %d is to ensure whitespace is skipped
      *newPerson = inputLoc; // new location input by the player for person

      if (*newPerson == (**rooms)[*person - 1][0] 
          || *newPerson == (**rooms)[*person - 1][1] 
          || *newPerson == (**rooms)[*person - 1][2]) {
        
              *person = *newPerson;
              *times += 1;
      }
      else {
        printf("Invalid move.  Please retry.\n"); // if user input room does not connect to an adjacent room the player is currently in then this will print
      }
  
      inputLoc = -1;
}

//end movePlayer(...)

//--------------------------------------------------------------------------------

//begin reset(...) - Resets player positions and changes them to the ones the player inputs (Prompted with character "R")

void reset(int *person, int *Wumpus, int *pit1, int *pit2, int *bat1, int *bat2, int *arrow, int *playerArrows)
{
      int newLocPerson, newLocWumpus, newPit1, newPit2, newBat1, newBat2, newArrow;
  
      printf("Enter the room locations (1..20) for player, wumpus, pit1, pit2, bats1, bats2, and arrow:\n\n");
      scanf(" %d %d %d %d %d %d %d", &newLocPerson, &newLocWumpus, &newPit1, &newPit2, &newBat1, &newBat2, &newArrow);
  
      *person = newLocPerson; // player set person location
      *Wumpus = newLocWumpus; // player set Wumpus location
      *pit1 = newPit1; // player set pit1 location
      *pit2 = newPit2; // player set pit2 location
      *bat1 = newBat1; // player set bat1 location
      *bat2 = newBat2; // player set bat2 location
      *arrow = newArrow; // player set arrow location
  
      if (*arrow == -1) { // if player sets arrow location to -1, player will automatically obtain 1 arrow
        *playerArrows = 1;
      }
  
}

//end reset(...)

//--------------------------------------------------------------------------------

//begin cheat(...) - Gives the position of person, wumpus, both pits when prompted with character "C"

void cheat(int *person, int *Wumpus, int *pit1, int *pit2, int *bat1, int *bat2, int *arrow) 
{
    printf( "Cheating! Game elements are in the following rooms: \n"
          "Player Wumpus Pit1 Pit2 Bats1 Bats2 Arrow  \n"
          "%4d %5d %6d %5d %5d %5d %5d \n\n", 
    			*person,
    			*Wumpus,
    			*pit1,
    			*pit2,
          *bat1,
          *bat2,
          *arrow
    		);
}

//end cheat(...)

//--------------------------------------------------------------------------------

// begin personWumpusDeath(...) - Function that decides if the Wumpus kills the player depending on whether or not the Wumpus is in an odd/even room

void personWumpusDeath(int *person, int **rooms[20][3], int *Wumpus, int *deathState) 
{
      if (*person == *Wumpus) {
        
          if (*Wumpus % 2 == 0) { // if Wumpus is in even room
                
                *deathState = 1;
                
                printf(	"You briefly feel a slimy tentacled arm as your neck is snapped. \n"
                        "It is over.\n");
                printf("\nExiting Program ...\n"); // end program since Wumpus killed player
                exit(0);
          }
          
          else {                 // if Wumpus is in odd room
                *Wumpus = (**rooms)[*Wumpus - 1][0];
              
                printf( "You hear a slithering sound, as the Wumpus slips away. \n"
      			          "Whew, that was close! \n");
          }
      }
}

// end personWumpusDeath(...)

//--------------------------------------------------------------------------------

// begin personPitfallDeath(...) - Function that plays if the player moves into a room where there is a pit, which kills the player and ends the program

void personPitfallDeath(int *person, int *pit1, int *pit2, int *deathState)
{
      if (*person == *pit1 || *person == *pit2) { // checking if person location is the same as pit1/pit2
          *deathState = 1;
        
          printf("Aaaaaaaaahhhhhh....   \n");
    	    printf("    You fall into a pit and die. \n");
          printf("\nExiting Program ...\n"); // end program since player died falling into pit
          exit(0);
      }
}

// end personPitfallDeath(...)

//--------------------------------------------------------------------------------

// begin nearbyDangers(...) - Function that detects if the Wumpus or a pit is in one of the adjacent rooms of the room the player is in

void nearbyDangers(int *person, int **rooms[20][3], int *Wumpus, int *pit1, int *pit2) 
{
        int i;
        
        for (i = 0; i < 3; i++) {  // checking if Wumpus is nearby
              int person1 = (**rooms)[*person - 1][i];
              
              if (person1 == *Wumpus) {  // If Wumpus is in an adjacent room, then warning will print
                printf("You smell a stench. ");
              } 
        }
  
        int k;
      
        for (k = 0; k < 3; k++) {  // checking if pits are nearby
              int person1 = (**rooms)[*person - 1][k];
          
              if (person1 == *pit1 || person1 == *pit2) {  // If pitfall is in an adjacent room, then warning will print
                printf("You feel a draft. ");
              }
        }
}

// end nearbyDangers(...)

//--------------------------------------------------------------------------------

// begin nearbyBats(...) - Function to detect bats nearby the player/person

void nearbyBats(int *person, int **rooms[20][3], int *bat1, int *bat2, int nearState[3]) 
{
        int i;
      
        for (i = 0; i < 3; i++) {
          
              if (*bat1 == (**rooms)[*person - 1][i] || *bat2 == (**rooms)[*person - 1][i]) {
                    nearState[2] = 2;
              }
        }
}
// end nearbyBats(...)

//--------------------------------------------------------------------------------

// begin batsRoomChange(...) - when the player moves into a room with a bat in it, they will be transported to a randomly chosen room

void batsRoomChange(int *person, int *bat1, int *bat2) 
{    
        if (*person == *bat1 || *person == *bat2) { // player has moved into a room with bat1/bat2
            printf("Woah... you're flying! \n");
    
            int *randLocation = (int *)malloc(sizeof(int) * 3); // allocating space for random location for bats to be transported to
            setUniqueValues(randLocation, 3);
        
            if (*person == *bat1) { // executes if person steps into a room with bat1 in it
                    *person = randLocation[0]; // sets person location to new random location that the bat took them to
                    *bat1 = randLocation[1]; // the bat flies away to a different room
                    randLocation[2] = *bat2;
            }

            else if (*person == *bat2) { // executes if person steps into a room with bat2 in it
                    *person = randLocation[0]; // sets person location to new random location that the bat took them to
                    *bat2 = randLocation[1]; // the bat flies away to a different room
                    randLocation[2] = *bat1;
            }
            printf("You've just been transported by bats to room %d.\n", *person);
            free(randLocation); // freeing up unneeded memory space
        }
}

// end batsRoomChange(...)

//--------------------------------------------------------------------------------

// begin acquiredArrow(...) - if player moves into a room with the arrow in it, they will immediately obtain it

void acquiredArrow(int *person, int *arrow, int *playerArrow) 
{
      if (*person == *arrow) { // executes if player is in the same room as arrow
        *playerArrow = 1; // The player has picked up the arrow
        *arrow = -1; // Arrow is found, therefore now not in any of the rooms
        printf("Congratulations, you found the arrow and can once again shoot.\n");
      }

}

// end acquiredArrow(...)

//--------------------------------------------------------------------------------

// begin shootPlayer(...) - player's ability to shoot an arrow to either kill the Wumpus, or themselves (accidentally)

void shootPlayer(int *person, int *Wumpus, int **rooms[20][3], int *arrow, int *playerArrow)
{
      int numOfRooms;  // number of rooms that player wants to shoot into
      int roomToShootPlayerInput;  // the exact rooms that player wants to shoot at
      int newArrowLoc;  // variable for storing arrow's new location after it is shot
      int adjacentRoomCheck = -1; // variable for checking if room is adjacent
  
      if (*playerArrow == 0) {  // executes if player doesn't have any arrows
            printf("Sorry, you can't shoot an arrow you don't have.  Go find it.\n");
            return;
      }

      int *shootArrowRooms = (int *)malloc(sizeof (int) * 3); // allocating space for rooms that player wants to shoot at
      *arrow = *person; // setting position of arrow at starting point / the room player is in

      // Taking in the input for the amount of rooms that player wants to shoot
      printf("Enter the number of rooms (1..3) into which you want to shoot, followed by the rooms themselves: ");
      scanf(" %d", &numOfRooms);
  
      if (numOfRooms > 4) {  // if player enters more than the allowed number of rooms, it will automatically set to the maximum - 3
            printf("Sorry, the max number of rooms is 3.  Setting that value to 3.");
            numOfRooms = 3;
      }

      int i;
      for (i = 0; i < numOfRooms; i++) {  // based on the player's input on the number of rooms they want to shoot, this loop will take in the inputs for the rooms they want to shoot AT.
            scanf(" %d", &roomToShootPlayerInput);
            shootArrowRooms[i] = roomToShootPlayerInput;
      }

      int j;
      for (i = 0; i < numOfRooms; i++) {  // for loop for each room that player wants to shoot
            for (j = 0; j < 3; j++) {  // for loop for adjacent rooms
                  if (shootArrowRooms[i] == (**rooms)[*arrow - 1][j]) {  // if the room that player wants to shoot at is one of the adjacent rooms, then the arrow will fly into that room
                        newArrowLoc = shootArrowRooms[i]; // arrow will now be located in the room that player shot at
                        *arrow = newArrowLoc; // setting arrow's location

                        adjacentRoomCheck = 1; 

                        if (*arrow == *Wumpus) { // executes when arrow is shot, and arrow's location is the same as the Wumpus, therefore killing it...
                              printf( "Wumpus has just been pierced by your deadly arrow! \n"
                                      "Congratulations on your victory, you awesome hunter you.\n");
                              printf("\nExiting Program ...\n");
                              free(shootArrowRooms);
                              exit(0);
                        }

                        if (*arrow == *person) { // executes when arrow is shot, and arrow's location is the same as the player's, therefore killing the player...
                              printf( "You just shot yourself.  \n"
                                      "Maybe Darwin was right.  You're dead.\n");
                              printf("\nExiting Program ...\n");
                              free(shootArrowRooms);
                              exit(0);
                        }

                        
                  }
            }
            if (adjacentRoomCheck == -1) { // if none of the rooms from player input are adjacent then this segment of code, called "Ricochet" will execute
                  *arrow = (**rooms)[*arrow - 1][0]; // the arrow ricoches into the lowest adjacent room
                  printf("Room %d is not adjacent.  Arrow ricochets...\n", shootArrowRooms[i]);

                  if (*arrow == *Wumpus) { // if the arrow ricoches into the Wumpus, then it will kill the Wumpus
                        printf( "Your arrow ricochet killed the Wumpus, you lucky dog!\n"
                                "Accidental victory, but still you win!\n");
                        printf("\nExiting Program ...\n");
                        free(shootArrowRooms); // freeing up unneeded memory after using it
                        exit(0);
                  }

                  if (*arrow == *person) { // if the arrow ricoches into the player, then it will kill the player
                        printf( "You just shot yourself, and are dying.\n"
                                "It didn't take long, you're dead.\n");
                        printf("\nExiting Program ...\n");
                        free(shootArrowRooms); // freeing up unneeded memory after using it
                        exit(0);
                  }
              
                  *Wumpus = (**rooms)[*Wumpus - 1][0]; // if the arrow ricoches and not hit anything, then the Wumpus will move into the lowest adjacent room
                  *playerArrow = 0; // since the arrow is shot, the player has no arrows left
                  return;
            }
            adjacentRoomCheck = -1;
            
      }
      *Wumpus = (**rooms)[*Wumpus - 1][0]; // if the arrow does not hit anything, then the Wumpus will move into the lowest adjacent room
      *playerArrow = 0;
      free(shootArrowRooms);
}

// end shootPlayer(...)

//--------------------------------------------------------------------------------

// begin main(void) - the meat of the program, combines all preceding functions and runs them all here

int main(void) 
{
    	// Seed the random number generator.  Change seed to time(0) to change output each time.
      srand(time(0));
      srand(1);
    
      int pit1, pit2, Wumpus, person, bat1, bat2, arrow; // Game variables
      char choice; // Variable to contain for the choice player chooses between M, R, C, D, G, P, X
    
      int newPerson; // Variable to store the location player inputs when choosing M
      int nearState[3]; // Variable to check if hazards (Wumpus, bats, and pits) are nearby
      int playerArrows = 0; // Variable to store the arrow found by the player
      int times = 1; // variable to update times "Enter your move" prints
    
      int deathState = -1; // Variable for checking if player is alive/dead 
  
      int i;
  
      int **rooms = (int **)malloc(sizeof(int *) * 20);
      for (i = 0; i < 20; i++) {
            rooms[i] = (int *)malloc(sizeof(int) * 3);
      }

      // All adjacent rooms in the cave, and the rooms they lead to
      rooms[0][0] = 2;  rooms[1][0] = 1;  rooms[2][0] = 2;  rooms[3][0] = 3;  
      rooms[0][1] = 5;  rooms[1][1] = 3;  rooms[2][1] = 4;  rooms[3][1] = 5;
      rooms[0][2] = 8;  rooms[1][2] = 10; rooms[2][2] = 12; rooms[3][2] = 14;

      rooms[4][0] = 1;  rooms[5][0] = 5;   rooms[6][0] = 6;   rooms[7][0] = 1;
      rooms[4][1] = 4;  rooms[5][1] = 7;   rooms[6][1] = 8;   rooms[7][1] = 7;
      rooms[4][2] = 6;  rooms[5][2] = 15;  rooms[6][2] = 12;  rooms[7][2] = 9;

      rooms[8][0] = 8;   rooms[9][0] = 2;   rooms[10][0] = 10;  rooms[11][0] = 3;
      rooms[8][1] = 10;  rooms[9][1] = 9;   rooms[10][1] = 12;  rooms[11][1] = 11;
      rooms[8][2] = 18;  rooms[9][2] = 12;  rooms[10][2] = 19;  rooms[11][2] = 13;

      rooms[12][0] = 12;  rooms[13][0] = 4;   rooms[14][0] = 6;   rooms[15][0] = 15;
      rooms[12][1] = 14;  rooms[13][1] = 13;  rooms[14][1] = 14;  rooms[15][1] = 17;
      rooms[12][2] = 20;  rooms[13][2] = 15;  rooms[14][2] = 16;  rooms[15][2] = 20;

      rooms[16][0] = 7;   rooms[17][0] = 9;   rooms[18][0] = 11;  rooms[19][0] = 13;
      rooms[16][1] = 16;  rooms[17][1] = 17;  rooms[18][1] = 18;  rooms[19][1] = 16;
      rooms[16][2] = 18;  rooms[17][2] = 19;  rooms[18][2] = 20;  rooms[19][2] = 19;
  
    
      // setting game variables to random locations
      int *randomNumbers = (int *)malloc(sizeof(int *) * 7);
      setUniqueValues(randomNumbers, 7);
  
      person = randomNumbers[0];
      Wumpus = randomNumbers[1];
      pit1 = randomNumbers[2];
      pit2 = randomNumbers[3];
      bat1 = randomNumbers[4];
      bat2 = randomNumbers[5];
      arrow = randomNumbers[6];
    
      while (deathState == -1) {
            // Always checks if player is dead at the beginning of loop to make sure program doesn't run after player dies
            personPitfallDeath(&person, &pit1, &pit2, &deathState);
            personWumpusDeath(&person, &rooms, &Wumpus, &deathState);
            nearbyBats(&person, &rooms, &bat1, &bat2, nearState);
        
            batsRoomChange(&person, &bat1, &bat2);
            acquiredArrow(&person, &arrow, &playerArrows);
        
        
            // Displays room and also checks for nearby dangers/bats each time the code loops
            printf("You are in room %d. ", person);
            nearbyDangers(&person, &rooms, &Wumpus, &pit1, &pit2);

            if (nearState[2] == 2) {
                  printf("You hear rustling of bat wings. ");
            }
  
            nearState[2] = -1;
              
            // if the deathState isn't -1, then that means the player is dead, so the program will end
            if (deathState != -1) {
                  printf("\nExiting Program ...\n");
                  exit(0);
                  break;
            }
        
            // Asking the player for input to choose from the Menu
            printf("\n\n%d. Enter your move (or 'D' for directions): ", times); 
            scanf(" %c", &choice);
    
            switch (choice) {
                  case 'm': // Runs when choice == "M"/"m", allows player to move to an adjacent room
                  case 'M':
                          movePlayer(&person, &rooms, &times, &newPerson);
                          break;
                  case 's': // Runs when choice == "S"/"s", allows player to shoot arrows
                  case 'S': 
                          shootPlayer(&person, &Wumpus, &rooms, &arrow, &playerArrows);
                          times++;
                          break;
                  case 'r': // Runs when choice == "R"/"r", resets player, wumpus, pitfall locations
                  case 'R':
                          reset(&person, &Wumpus, &pit1, &pit2, &bat1, &bat2, &arrow, &playerArrows);
                          break;
                  case 'c': // Runs when choice == "C"/"c", allows player to cheat and see where all hazards are located
                  case 'C':
                          cheat(&person, &Wumpus, &pit1, &pit2, &bat1, &bat2, &arrow);
                          
                          break;
                  case 'd': // Runs when choice == "D"/"d", displays cave layout and instructions on how to play the game
                  case 'D':
                          displayCave();
                          displayInstructions();
                          times++;
                          break;
                  case 'p': // Runs when choice == "P"/"p", displays cave layout
                  case 'P':
                          displayCave();
                          times++;
                          break;
                  case 'x': // Runs when choice == "X"/"x", which exits the game
                  case 'X':
                          printf("\nExiting Program ...\n"); // ends program prompted by player                                                              input
                          deathState = 1;
                          break;
                          
            }
              
    
      }
      free(rooms);
	    return 0;
}
