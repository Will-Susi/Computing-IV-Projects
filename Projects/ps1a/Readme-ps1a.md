# PS1: LFSR

## Contact
Name: Will Susi
Section: 202
Time to Complete: 240 min

## Description
Explain what the project does.

The project creates a LFSR class that represents a linear feedback shift register. This class contains a single data field that represents a 16-bit register as a string.
The class includes two major functions:
- The "step()" function which simulates a single shift of the register and returns an int that represents the new rightmost bit (LSB).
- The "generate()" function which takes an int that represents the number of shifts to make and returns an integer that is made from the binary number of the appended bits during the shift.

### Features
Describe the representation you used and why you did things that way. 

For the LFSR class I chose to simply represent the register as a string. It made each element easy to access and operate on. Accessing/modifying the front and the back, while not hard, probably could have been easier with something like a vector, but I just wanted to stay simple with a string. 

For step(), since each XOR was systematic, I simply used math and the pushed the resulting bit character to the end of the string and then replaced the string with a substring that was the same bit string without the leading bit.

For generate(), I used the math given to us and other than that further implementation wasn't really needed; just looped through for the argument amount of times.

### Issues
What doesn't work. Be honest. You might be penalized if you claim something works and it doesn't.

Everything seems to be working properly.

### Tests
Describe what is being tested in your Boost unit tests.

- The first test was given, this tests "step()" multiple times to a known result.

- The second test was also given, this tests "generate()" against a known result.

- The third test does a more extensive test of "generate()". It tests it consecutively 7 times, making sure the returned bit matches and the resulting bit-string match. The known bit/bit-strings are taken from the ps1a.pdf.

- The fourth test tests simply "getRegister()" to make sure it returns the data member "_register" properly. 

- The fifth and final test makes sure '<<' overload works by inserting the register to an sstream and then comparing the contents to a known result.

## Acknowledgements
List all sources of help including the instructor or TAs, classmates, and web pages.

Had help with some Makefile problems from professor Daly.