# PS5: DNA Alignment

## Contact
Name: Will Susi
Section: 202
Time to Complete: 7 Hours

### Results

- CPU: AMD Ryzen 7 3700X 8-Core Processor
- CPU Speed: 3.60 GHz
- Implementation method: Needleman-Wunsch
- Matrix method: Double vector
- Operating system: Windows 11 - WSL Ubuntu

- Test problems: Problem, estimated distance, time in seconds (w/o valgrind), memory in bytes(w/ valgrind)
1. ecoli2500.txt - ED: 118 Time: 0.39s, Memory Used: 82.4 MB
2. ecoli5000.txt - ED: 160 Time: 1.56s, Memory Used: 327.1 MB
3. ecoli7000.txt - ED: 194 Time: 3.10s, Memory Used: 639.5 MB
4. ecoli10000.txt - ED: 223 Time: 6.05s, Memory Used: 1,303.8 MB
5. ecoli20000.txt - ED: 3135 Time: 25.78s, Memory Used: 5,257.5 MB
6. ecoli28284.txt - ED: 8394 Time: 50.18s, Memory Used: "FATAL: VG_N_SEGMENTS is too low"

## Description
Explain what the project does.

This project computes the optimal sequence alignment for two DNA strings. 

### Features
Describe what your major decisions were and why you did things that way.

The project uses the Needleman-Wunsch of dynamic programming. 
It was implemented through the EDistance class, which takes two strings of length N and M, and creates an NxM matrix of integers.
To compute the value of each value in the matrix it was broken into sub-problems.
The final row and final column can be computed from the length of the string from doubling the size of the opposing string adn decreasing as the index decreases.
For filling everything else, we work backwards from the [N][M] by filling it with the minimum of three values. 
These three values are trying the cases of a letter of a string aligning with the same letter, a different letter, or a gap and finds the best comparison.
Once the matrix is filled, the penalty of alignment can be found at [0][0].
The actual alignment can be traced backwards using a similar way we populated the matrix.

### Issues
What did you have trouble with? What did you learn? What doesn't work? Be honest. You might be penalized if you claim something works and it doesn't.

There were no major problems as the ps5 pdf was a very good guide.

### Extra Credit
Anything special you did.  This is required to earn bonus points.

For extra credit I tried using both the C++ 'min' function and a user made 'min' function.
After trying the implementation of both, I found that the 'min' function I made was faster while using the same memory than when using the C++ defined 'min' function.

## Acknowledgements
List all sources of help including the instructor or TAs, classmates, and web pages.
