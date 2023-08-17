# PS4b: Checkers

## Contact
Name: Will Susi
Section: 202
Time to Complete: 12 Hours

## Description
Explain what the project does.

This project finishes the game of Checkers.
This project sets up the game sets up most of the core game mechanics for Checkers.
This includes:
- Highlighting a players piece when clicked and showing the moves that piece can make.
- Allowing said player to make said moves and removes any pieces that were jumped. 
This includes moving a piece diagonally in two directions depending on the pawn color.
- Kinging pawn that arrived at the opposing players end and giving the ability to move in all four diagonal directions 

The only game mechanics the were not added were multi-jumping and forcing a player to make a jump if they can.

### Features
Describe what your major decisions were and why you did things that way.

For the mechanics of the game I added a bunch of larger functions and helper functions.
I did a series of reductions after the code functioned to clean everything up.
The helper functions were mostly made out of the necessity to reduce lines of codes or long lines.
Here are a list for the major functions and how I implemented them.
- 'checkKing': This function checked if a pawn need to be kinged by checking through the pieces and seeing if they had reached the opponents side. If it need to be kinged I then changed their model and their member variable to make it possible to act like a king
- 'onTile': This function checked if a piece could be found on a given tile by looping through a vector of pieces and compared their locations to the given tile
- 'clickPieces': This function highlights a tile if the current player click on their piece at that location.
It gets the current players pieces and loops through, checking to see if the click was on a tile with their piece.
If one is found any past highlighted pieces (if you switched what piece you wanted to play) are un-highlighted, the new tile is highlighted, and then the 'showMoves' function is called.
- 'showMoves': This function is called by the 'clickPieces' function and highlights the tiles where the current piece can possibly move.
It first checks what type of pieces it is and if it is a king to know what direction it can move in.
It then loops through those directions to highlight the tiles it can actually move to.
It checks the two moves of jumping into a adjacent open space and jumping an opposing piece where no other piece is on the next tile.
- 'makeMove': This function first checks the game board for a selected piece.
If a selected piece is found it knows to make a move, looks for highlighted moves spots, and compares them to the mouse location.
If they match the piece's position is updated to the clicked spot, the current turn is switched to the next player, any highlights are cleared, and the 'removePieceJumped' function is called.
- 'removePieceJumped': This function finds the displacement between the starting spot of a piece and the move it just made. Using this displacement, the lambda could find where a piece was jumped. Once found the 'erase' member function of vector took the new end iterator returned by remove_if and the original end to remove the associated piece from the game board.

### Lambdas
Describe what <algorithm> functions you used and what lambda expressions you wrote.

I used a 'remove_if' algorithm along with a lambda to remove a jumped piece.
This combination searched through a given piece vector looking for a piece that matches a location.

### Issues
What did you have trouble with? What did you learn? What doesn't work? Be honest. You might be penalized if you claim something works and it doesn't.

Not much major trouble just a longer project especially after I tried cleaning some of the functions up a bit.
I did have a problem where a piece will occasionally duplicate itself because I wasn't properly implementing the 'remove_if' algorithm, but I fixed it.

### Extra Credit
Anything special you did. This is required to earn bonus points.

For extra credit I added the ability of highlighting a pieces moves when it is selected.

## Acknowledgements
List all sources of help including the instructor or TAs, classmates, and web pages.
If you used images or other resources than the ones provided, list them here.

SFML API, Dr. Daly's custom made checker sprites
