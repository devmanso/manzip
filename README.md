# manzip

* manzip is a file comrpession program that I've been working on to learn about file compression algorithms.

* This program only works with text files written in english and is ASCII text. Something like "صباح الخير" will most likely not get encoded, or something wierd will happen.

* This is liscensed under MIT Liscense, I am not responsible for any damages to your data or system.

* The program can be downloaded as Windows executable (.exe) on the releases tab of this github page. If you want a binary for a different OS like Linux or MacOS you will need to compile this on your own machine.

## Under-The-Hood

The way this program encodes/decodes files is through run-length-encoding. This means that sometimes file sizes might actually increase when encoded ("abcd" turns into "a1b1c1d1" when encoded).
RLE works best when there is a lot of repetition (i.e: "aaabbbcccddd" turns into "a3b3c3d3" when encoded)

### The code

[main.c](main.c): This is the entry point of the program and is the CLI, it takes 3 arguments representing the input/output file and encoding/decoding. It handles misinputs and errors. It requires manzip.h to work
[manzip.h](headers/manzip.h): This is where the RLE algorithm is implemented, it has encoding/decoding functions for both files and strings. You can inlude this header file into your own projects too, it only depends on the standard library

### How to compile (C99)

```
 gcc -o manzip -I./headers main.c
```

## How to use

Usage is also very simple, the program just needs 3 parameters

* input file ("myFile.ext")

* output file ("myEncodedFile.ext")

* mode ("E" or "D")

* Example usage (Encoding)

```
./manzip input.txt output.txt E
```

* Example usage (Decoding)

```
./manzip encoded.txt decoded.txt D
```