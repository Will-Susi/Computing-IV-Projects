# PS3: Pythagorean Tree

## Contact
Name: Will Susi
Section: 202
Time to Complete: 480 min

## Description
Explain what the project does.

This project creates a Pythagorean Tree from a given side length, size, and angle measure. The Pythagorean Tree starts as a square and generates two more squares of possible different sizes depending on the given angle measure where new square will go from. Each new square will generate two new squares as many times as the given recursion depth.

### Features
Describe what your major decisions were and why you did things that way.

I chose to make two classes, a Tree class and a Node class. A tree object has a root node or the starting square and has two children that are also nodes. Each node has a left and right node member and a rectangle object. The tree calls upon a recursive 'grow' function which creates two children from a given parent Node with the correct new position, angle, size, etc. This recursion loops for the given depth.

### Issues
What did you have trouble with?  What did you learn?  What doesn't work?  Be honest.  You might be penalized if you claim something works and it doesn't.

I came across a few different challenges. The first was setting the origin of every new object. SFML API is pretty bad at documenting this, along with it being confusing in general, so it took me a while to get each new rotation/position correct to make it look like the reference image.

I also had trouble with fitting the window to the tree. I can get the basic tree to fit fine, as it is a set width and height, but figuring out the equation for a changed angle/depth was too hard. I spent hours trying to figure it out with no avail, as it still won't work for anything outside of the set 45 degrees. So you can put in a different angle measure, and it will draw the tree correctly, but it will not fit on the screen.

### Extra Credit
Anything special you did.  This is required to earn bonus points.

I added color changing to the tree. The starting color is always brown (like a stump) adn then any following levels loop through the rainbow. I did this with a set 6 colors, but you can add/take away more.

I also added the ability to change the angle, but as mentioned above, it will not fit correctly in the window.

## Acknowledgements
List all sources of help including the instructor or TAs, classmates, and web pages.

SFML API, Tutor
