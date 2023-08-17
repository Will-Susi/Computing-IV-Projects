# PS2a: Sokoban

## Contact
Name: Will Susi
Section: 202
Time to Complete: 450 min

## Description
Explain what the project does.

This part of the project sets up the gameplay and mechanics so the full game can be played. This includes being able to move around using WASD and reset the level using 'R'. The boxes can now be pushed around into open spaces. Any wall block player or box movement. When all the boxes are pushed into the storage areas the game announces that they win.

### Features
Describe what your major decisions were and why you did things that way.

In main I added the functionality of key presses. I chose to use SFML's 'KeyPressed' vs their 'isKeyPressed' to more easily replicate the proper movement of the player. 

In the 'movePlayer' function I made a vector of pairs that represented the displacement after a key press. This made it so I could generalize the movement by just passing in the displacement of both the x and y each time. For each movement I checked that it wouldn't cause the player go out of the play area or through a wall, and it would act appropriate with the box physics. This included making sure a box couldn't push another box or too wouldn't go through a wall or out the play area. If any sort of movement wasn't allowed no movement was made, and if a movement was made the assorted sprites were updated,

In the isWon function there was a few sceneries were the player would win. To crack down on all of them, I found the lower between the number of boxes and the number of storage spaces. I then looped through the assortment of both, comparing their values. If the number of matching values met that lower number that meant the player won. I used the 'find_if' algorithm along with a lambda function her as it seemed the most appropriate place to do so.

### Lambdas
Describe what <algorithm> functions you used and what lambda expressions you wrote.

I used the 'find_if' algorithm along with a lambda function to check if the game had been won. The lambda served as a comparison checker to compare the locations of the 'boxSprites' and the 'storageLocations' to see if any matched up. If any matched up the 'find_if' algorithm returned an iterator indicating the there is a box in a storage location. If the number of boxes in storage containers was correct the function 'isWon' returned true, otherwise it returned false.

### Issues
What did you have trouble with?  What did you learn?  What doesn't work?  Be honest.  You might be penalized if you claim something works and it doesn't.

Everything seems to work as intended but I did have some trouble/learned some stuff. I had a little trouble getting the victory text to center but figured it out in the end. I also had little trouble implementing the algorithm and lambda because I originally made the program without them. I hadn't really used lambdas before this either so it took a second to figure out, but seems to be working well now. In general I had some trouble ith player/box moving restrictions like out of bounds and what not but they have been resolved.

### Extra Credit
Anything special you did. This is required to earn bonus points.

I added the ability for the player model to change depending on the direction they last moved. This was simply added by updating the sprite texture every time the player sprite moved. I also added a victory sound when the player won. This too was simply added by calling the sound library with a preloaded victory noise that played when 'isWon' returned true.

I additionally added a new feature. This feature was the addition of going to the previous level by pushing 'P' or the next level by pushing 'N', after winning. It works for any number of added levels (including multi-digit levels). It only requires that to go to a previous level that the name of the level be one previous number; the same idea goes for the next level feature. If the level does not exist you simply wont be able to move to that non-existent level.


## Acknowledgements
List all sources of help including the instructor or TAs, classmates, and web pages.
If you used images or other resources than the ones provided, list them here.

SFML API.
Used the 'Course Clear' sound bit from Nintendo's Super Mario Bros game: https://www.youtube.com/watch?v=kfcV9TXFFes
Help with lambdas from a classmate.
