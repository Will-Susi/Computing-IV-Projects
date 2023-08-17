# PS1A: PhotoMagic

## Contact
Name: Will Susi
Section: 202
Time to Complete: 240 min

## Description
Explain what the project does.

The project takes a given image and a given seed, and encrypts that image using that seed into another image of seemingly random pixels. For each pixel in the image, the RBG values are each set to random values (0-255) using the generate function of the FibLFSR class. This function, with a value of 8, generates an 8-bit integer string, corresponding to the 0-255 possibly rbg values. Once the image has been encrypted, using the same seed with the new transformed image, it can be decrypted (using the same method) that results in the original image.

### Features
Describe what your major decisions were and why you did things that way.

The PhotoMagic file was pretty straight forward, as it was simpler to the original given example for opening a window except two now needed to be implemented. 

For the 'transform()' function, I chose to loop through each pixel of the image. For each pixel I split it into its separate rgb values and for each value XORed the original value with the 'generate()' function. The number 8 was passed into 'generate()' as to generate a random 8-bit number for each rgb value, 8 chosen because each rgb value can range from 0-255 and an 8-bit integer can generate all those values.

I also made a 'generateBinarySeed()' function that was for the extra credit, but I will go into more detail below.

### Issues
What doesn't work. Be honest. You might be penalized if you claim something works and it doesn't.

The semi-issue that I have though of more than encountered is with one of my tests. In test for the 'transform()' function the way I chose to check if it worked properly was to check if the pixel values were different after the transform. While there is a '==' overload for the 'Color' class, it apparently also needs the << overload for the Boost tests to function properly. So instead I had to compare each rgb value of each pixel. So, I made it so each rgb value at each pixel had to be different for the test to fail. But here is the real problem; There is a small chance that one or more of the rgb values could be the same while the others are different so I made it so all three had to be different to fail. So the problem remains that technically an incredibly small chance a pixel could randomize to all the same rgb values and the test would fail (given the seed).

### Extra Credit
Anything special you did. This is required to earn bonus points.

I did the extra credit of converting from an alphanumeric password to the LFSR initial seed. I implemented another function named 'generateBinarySeed()' that would take in a alphanumeric password and return proper binary seed. What I did was for a given alphanumeric password was make any odd characters in the ASCII table a 1 and any even a 0. This seemed to be the best way to make it semi-random. Any password over 16-bits were ignored had those trailing bits ignored.
For anything that is shorter than the required 16-bit seed length, the remaining bits are generated altering between a '0' and '1's, this also keeps it semi-random. These together make it seem as random as possible while also making it so the same alphanumeric seed makes the same binary seed every time.

I also made extensive tests to test the coding of the alphanumeric password as well as testing the transform function. I ran edge case tests for the password encoding such as too short, too long, many extraneous characters, and passing that a normal 16-bit password would still encode as that password. For the transform function, like I said above, I checked that after transform was ran that each individual pixel was different. I go into more depth about the test above.

## Acknowledgements
List all sources of help including the instructor or TAs, classmates, and web pages.

SFML API, help from Dr.Daly's Discord
