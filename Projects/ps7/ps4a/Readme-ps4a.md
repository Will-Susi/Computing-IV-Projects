# PS4a: Checkers

## Contact
Name: Will Susi
Section: 202
Time to Complete: 240 Min

## Description
Explain what the project does.

This project is the UI setup for the widely known game of Checkers.
This project sets up the game board and the Checkers for a game of Checkers.
It also displays whose turn it is and allows that player to select any of their pieces by showing them their selection.

### Features
Describe what your major decisions were and why you did things that way.

The set up for this game was not that far from setting up Sokoban.
The two big functions were the game constructor and the 'onPiece' function which checked if a game piece was selected
I had a starting layer of brown which would represent the board border, then the tiles, then the Checker pieces.
When setting up the tiles I simply alternated red and black squares.
For every black square that was in the first three rows I made a black checker and for every black square that was in the final three rows I made a red Checker.

I first decided it pass in whose turn it was to make the function generalized to check which player's turn it was, so they could select only their pieces.
I compared the mouse click with any of the current player piece and if they matched the tile under that piece would be highlighted.
I also made a function called 'clearHighlights' which cleared any previously highlighted pieces so the player could change what piece they wanted to play.
I did this because in part b I will need it again if I plan on implementing 'move assist'.

### Memory
Describe how you stored the game board including if you used smart pointers.

I chose to make an additional class called 'Pawn'. 
This class contains the sprite for a game piece along if it is a king or not.
For my Checkers class I made a a vector of textures that loaded all the game textures.
I represented the game board as a a vector-vector of drawable rectangles as it seemed the simplest.
I then made two vectors of 'Pawns', one representing the red player and the other the black.
Finally I stored whose turn it currently was in a variable named '_blackTurn' where if true it was Black's turn and otherwise was Red's.

### Lambdas
Describe what <algorithm> functions you used and what lambda expressions you wrote.

I didn't need any algorithms or lambdas.

### Issues
What did you have trouble with? What did you learn? What doesn't work? Be honest. You might be penalized if you claim something works and it doesn't.

I really had no major issues with the setup of the first part of this project adn have not found any issues.

### Extra Credit
Anything special you did. This is required to earn bonus points.

I did two suggested pieces of extra credit. 
The first thing I did was add a game frame around the game. The size of this frame can actually be changed if the user wanted.
The second thing I added was a current player indicator at the top of the screen which indicates which players turn it is.

## Acknowledgements
List all sources of help including the instructor or TAs, classmates, and web pages.
If you used images or other resources than the ones provided, list them here.

SFML API, Dr. Daly's checker texturesit pull