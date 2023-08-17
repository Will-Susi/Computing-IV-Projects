# PS2a: Sokoban

## Contact
Name: Will Susi
Section: 202
Time to Complete: 420 min 


## Description
Explain what the project does.

The project sets up the environment for running the famous game Sokoban. This includes displaying the player, any movable boxes, adn any environmental structures, and a game timer in the top left. The gameplay and mechanics will be implemented in the second part.

### Features
Describe what your major decisions were and why you did things that way.

- For the game textures I only load the textures once when the game is created. The textures are then shared between multiple sprites as to improve load speeds and reduce memory usage because they are lightweight objects. 

- For the the >> operator I assigned all of the member variables inside. I first read in the width and height of the level and set that as the size for the 2d vector of sprites as well as the 2d vector of characters. Then for each character read in from the level file I added it to the character vector. I also loaded in the associated texture to the the character, made a sprite from it, set its position for where it should be displayed, and added that sprite to the associated sprite container.

- For the the << operator I chose to simply loop through the 2d vector of the map characters.

- For the draw overload, I too simply looped through each sprite container and had them draw there positions to screen.

### Memory
Describe how you decided to store the level data including whether you used smart pointers.

I did not use any smart pointers. I first stored the level as a vector-vector of characters as to replicate a 2d array of the given characters. This made checking the map was properly read. I then created multiple containers holding an assortment of sprites; One vector-vector for the terrain sprites (anything that wont move) that was similar to the vector-vector of characters, a vector for any movable boxes, and then just a sprite member variable for the player. I also had a vector of textures that loaded all the game textures. Since I used STL containers, they automatically de-allocate any memory at the end of the program.

### Lambdas
Describe what <algorithm> functions you used and what lambda expressions you wrote.

I did not use/need any <algorithm> functions or lambda expressions. 

### Issues
What did you have trouble with?  What did you learn?  What doesn't work?  Be honest.  You might be penalized if you claim something works and it doesn't.

None that I noticed.

### Extra Credit
Anything special you did. This is required to earn bonus points.

I chose to add the timer like suggested. I used the clock class to start a clock adn get the elapsed time. I converted the elapsed time to seconds. To display it, I used the text class. I made the seconds into a string by splitting it into minutes and seconds adn appending them together with any filler '0's I then displayed the timer to screen in the top left where it was out of the way, but visible.

## Acknowledgements
List all sources of help including the instructor or TAs, classmates, and web pages.
If you used images or other resources than the ones provided, list them here.

SFML API, Tutor for overloading Draw class.