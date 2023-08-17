# PS6: RandWriter

## Contact
Name: Will Susi
Section: 202
Time to Complete: 5 hours

## Description
Explain what the project does.

This project uses a given text and generates new random text based off of it.
It takes the text, a kgram length, and a new text length.
A kgram is a substring of the text of the given length.
Using these many many kgrams, and their occurrences, new text of any length can be generating using the past kgrams probabilities.

### Features
Describe what your major decisions were and why you did things that way.

This project created a RandWriter class which was used to hold the kgrams and k+1grams generated from a text. 
I chose to store the kgrams and k+1grams separately as unordered maps, where the key was a string representing the kgram and the value was a int representing the number of times the kgram occurred.
The constructor parsed through the text and filled the two maps while also generating a seed that would be used later for RNG.
As for the new text it goes as follows:
- 'generate()' - This function returns a string of new text given a starting kgram and length of generation.
It loops for the desired length of generation, calls 'kRand' to get a pseudo-random character, and returns a string once all those characters have been generated.
- 'kRand()' - This function returns a character based of a given kgram.
The kgram is first checked to actually exist in the kgram map using the 'freq' function, and if it is, it finds and stores all its associated k+1grams.
It then counts the number of total occurrences of all k+1grams with kgram in them os that a k+1gram with more occurrences has a higher probability of being picked.
A number is then randomly generated based off the RandWrite seed, and a distribution is applied to it so the random number is between 1 and the total occurrences. 
That random number is then used to pick one of the k+1grams and returns the last character of the k+1gram.
- 'freq()' - Determines if a given kgram or a k+1gram can be found in their respective maps.
The overload for a k+1gram wasn't implemented because of how the internal structure of my RandWriter was made (two separate maps).

### Testing
What tests did you write?  What exceptions did you use?  Does your code pass the tests?

My code pasts all the tests I made.
I created three types of tests for each function of the RandWriter class.
These tests made sure the function threw the right error with bad input, didn't throw an error with good input, and produced a reasonable output when called.

### Lambda
What does your lambda expression do?  What function did you pass it to?

The lambda expression I used was to count the total number of kgrams in a map.
I used this, along with 'for_each' algorithm.
Together they access the second element, or the occurrences, of each kgram in the map and sum them up to be used to generate their probabilities.

### Issues
What did you have trouble with?  What did you learn?  What doesn't work?  Be honest.  You might be penalized if you claim something works and it doesn't.

There were small challenges along the way but nothing that became a major issue.

### Extra Credit
Anything special you did. This is required to earn bonus points.
Did you make a new instrument?  What is the instrument and how did you make it?  How does the user choose between the guitar or the new instrument?

None.

## Acknowledgements
List all sources of help including the instructor or TAs, classmates, and web pages.

Tutor
