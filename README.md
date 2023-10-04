# Bottom

The Bottom program is an exploration in Linux and NCurses through recreating Top from the GNU Core Utilities using C++.  

Everything was written from scratch, done by eye, and from testing the Top program.

I may go back and continue this at some point for various reasons.  Firstly, it's unfinished.  Several bugs have been overshadowed while building/factoring the code base better for speed, usability, and extensibility.  Secondly, I wrote all the search alrogithms from scratch and hadn't spent time unit testing all of them for edge cases.  This is mainly due to having written some of them while still learning where and how to retrieve patricular process data.  Further, algorithm portability is questionable because retreiving process data is going to vary between Linux distributions and I wrote and tested this project only on my Arch Linux systems.  Lastly, there are quite a few ideas I have had that I think could bring added value to a light-weight process management program that would be fun to implement in Bottom.
