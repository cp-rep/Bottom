# Bottom

The Bottom program is an exploration in Linux and NCurses through recreating Top from the GNU Core Utilities using C++.  

Everything was written from scratch, done by eye, and from testing the Top program.

I may go back and continue this at some point for various reasons.  Firstly, it's unfinished.  There are a few small bugs where addressing them were overshadowed by my constant reframing of the code base for speed, easier use, and extensibility.  Secondly, I wrote all the search alrogithms from scratch and hadn't spent time unit testing them for edge cases.  Further, algorithm portability is questionable because retreiving process data is going to vary between Linux distributions and I wrote and tested this project only on Arch-Linux systems.  Lastly, there are quite a few ideas I have had that I think could bring added value to a light-weight process management program that would be fun to implement here.
