# PS7: Kronos Log Parsing

## Contact
Name: Will Susi
Section: 202
Time to Complete: 4 Hours

## Description
Explain what the project does.

This project parses a log file using regular expressions and outputs a report file.

### Features
Describe what your major decisions were and why you did things that way.

There wasn't a need for a class or an outside file so everything was done in main.
First two regex expressions were made to properly detect start and complete boots.
Each line from the log file was checked against tahese expressions.
When a boot started it was written to the report file with a date and time.
If a boot had already started and another boot was encountered before a complete boot an incomplete boot was written to the report file following the previous boot. 
The new boot was then written to the file with a date and time.
If a completion was encountered following a boot it was written to the file with a date and time.
The boot time between the start and completion was computed via the 'convertTime' function and was also added to the report.
This function took two date/time strings, made them ptime objects, subtracted them, and converted the computed time to milliseconds.
Once the whole log file was parsed, a summary was added to the beginning of the report indicating the total lines read, the total of boots started, and the total of completed boots.

### Approach
Describe your overall approach to solving this problem.

I first started by commenting out the general steps needed to complete the project.
I then made the regex expressions to capture the start and completed boot lines.
After that everything went very linearly; I opened the files, compared each read line to the regex expressions, and wrote to the report file if the matched the regular expressions.

### Regex
What regular expressions did you use?  Explain what each one does.

I used the two following regular expressions:
- "(\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2}): \(log\.c\.\d+\) server started"
- (\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2})+\.\d{3}:INFO:oejs.AbstractConnector:Started SelectChannelConnector@0.0.0.0:\d{4}

The first regular expression captures a boot start and the second expression captures a boot completion.
The start of both regular expressions is a group that captures the date and time of the log line.
After that they essentially both look for their respective text that indicates their respective intent.

### Issues
What did you have trouble with?  What did you learn?  What doesn't work?  Be honest.  You might be penalized if you claim something works and it doesn't.

I had a little trouble at the start of where to start because it felt a bit daunting, but once I started it was pretty simple.
I also had some general trouble with the regex and time/date libraries because the API is really bad and hard to follow, so some functions used from them took a second to get right.

### Extra Credit
Anything special you did. This is required to earn bonus points.

I started the report file with a summary of the file.

## Acknowledgements
List all sources of help including the instructor or TAs, classmates, and web pages.

Tutor, Boost API
