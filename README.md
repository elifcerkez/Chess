# Chess

This chess game reads a board from a txt file; if it is not given, it initializes a chess board as default. This program calculates the points of both chess players (white & black). When it is asked to enter a file name, it is expected that the user input the name only. For example: "board1" and "board2". The program itself is going to take it as a txt file.
The points are distrubited like this:

Pawn = 1          // represented as p + (b for white or s for black) such as pb and ps
Knight = 3        // represented as ab as
Bishop = 3        // represented as fb fs
Rook = 5          // represented as kb ks
Queen = 9         // represented as vb vs
King = 100        // represented as sb ss

Under the time limitations, the program is not calculating the points of pieces under attack yet. It calculates according to normal scoring. This will be updated later.
It is recommend to run the program with C++11 standard or higher since extended initializer lists are used.
