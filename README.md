# Chess

This chess game reads a board from a txt file; if it is not given, it initializes a chess board as default. This program calculates the points of both chess players (white & black). When it is asked to enter a file name, it is expected that the user input the name only. The program itself is going to take it as a txt file.
The points are distrubited like this:

Pawn = 1          // represented as p + (b for white or s for black) such as pb and ps
Knight = 3        // represented as a + (b for white or s for black)
Bishop = 3        // represented as f + (b for white or s for black)
Rook = 5          // represented as k + (b for white or s for black)
Queen = 9         // represented as v + (b for white or s for black)
King = 100        // represented as s + (b for white or s for black)

Under the time limitations, the program is not calculating the points of pieces under attack yet. It accepts normal pointing. This will be updated later.
It is recommend to run the program with C++11 standard or higher since extended initializer lists are used.
