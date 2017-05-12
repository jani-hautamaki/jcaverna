# jcaverna
C implementation of Caverna: The Cave Farmers

## What is this?

This is a *almost complete* digitalization of the game mechanics 
of Caverna: The Cave Farmers, a boardgame by Uwe Rosenberg.

Regarding the completeness: the solo game is complete, 
but multiplayer game is not (has some action spaces that
have not been implemented, eg. Imitation).

## Single C source file with 10k lines??

The source code is crappy as the whole game engine was
written into a single source code file. This was meant
to be just a proof-of-concept, and the actual release
was meant to be a properly written C library.

However, almost one year has passed since I wrote
the original, monolithic game engine, and I have just
not found the time to rewrite the engine properly.
It looks like the well-written library code is not
going to appear any time soon, and therefore I am
releasing this monolithic crap instead. Just to
record it into history, and for anyone interested.

Obviously, creating a game engine like this would have
been somewhat easier with a language that has classes,
inheritance, and dynamic binding. However, I took it
as a challenge and as a research to create something
with C that is more suited to an object-oriented language.

## Why is this?

The motivation for this work came from the solo game,
which is completely deterministic. There is no randomness
in the solo game of Caverna. Therefore, the solo game scores
are comparable with each other. There exists a fantastic
solo game sequence for Caverna, by Alex Rockwell, which
results in the magnificent score of 200. 

Theoreticaly, one should be able to compute the highest 
solo game score with an exhaustive search (i.e. using 
brute force). The exhaustive search would require 
a computer, obviously. The game engine sprung to life 
due to the ambitious goal of computing the optimal 
solo game (actually, there might be multiple play 
sequences with the same score). 

However, it became apparent that the exhaustive search
(brute force) would require an astronomical amount of 
time to complete. Even though there are only 11 rounds
in the solo game, the number of play sequences explode
in just few rounds. So, without fancy heuristics,
there is no hope for finding the optimal solo play
sequence with brute force.

## Build (on Linux)

To build, execute the following spell
```bash
gcc -Wall -std=c99 caverna.c cli.c
```
This creates a binary `a.out` which is the CLI for the game.

## Play 200pts solo game

After compiling the game, you can run the CLI command transcript
for the Alex Rockwell's 200pts solo game by executing
```bash
./a.out < SOLO_200
```
The program should end with a breakdown how the 200pts are achieved.

## CLI guide?

There is no guide at this point, as the CLI is just some 
crappy ad-hoc code. The options are that you inspect
the source code to learn how to use the crappy CLI, or
you inspect and try out parts of the transcript `SOLO_200`.

## License

The source code is released under GPLv3.


