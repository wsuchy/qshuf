# Qshuf is a memory efficient replacement for GNU shuf

It might be used by data scientist when one has gigabytes of data in one file and need to have it randomised.

**Qshuf** will not read the source file into memory.
Instead it analyzes the file by looking for places where lines start.
Then it randomly reads one line from the input and outputs it to stdout.

The only supported newline format is linux (\n)
