# Original Multigen Data

These are the original files that were input to and output from the `multigen`
binary and used in DOOM. `multigen.txt` describes (among other things) mob
behavior as state machines, and is run through the `multigen` binary to produce
`info.c` and `info.h`, which are then included by and compiled into the DOOM.

To try out the `multigen` binary, use `multigen.txt` and compare the output to `info.c` and `info.h`.
If the output has changed but the input has not, a regression has likely been introduced.
