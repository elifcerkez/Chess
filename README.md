This program records a snapshot of a chess board taken from the user. If the file with the name entered by the user cannot be found or cannot be executed, the program automatically takes the starting position of a chess board. The program keeps track of the number of chess pieces on the board separately for white and black colors. It individually checks the threatened status of each chess piece on the board. The checked conditions are being threatened by a pawn, being threatened by a knight, and being threatened by a queen. A chess piece can be threatened by multiple pieces of the same type (for example, a white piece can be threatened by two black pawns) or multiple types of pieces at the same time. In this case, the threat status is considered only once, and its scoring is calculated accordingly. A threatened piece loses half of its score. Test code to verify the accuracy of the program is provided at the bottom of the cpp file. Accordingly, a sample output will be as follows:


	Please enter the name of the text file that you want it to be read: board3

	White Score: 109
	Black Score: 108

	vb -- -- vs ss -- -- -- 
	-- -- -- -- -- ps -- ps 
	-- as ps -- pb -- ab -- 
	-- -- -- ab -- -- -- -- 
	-- -- -- -- -- -- -- -- 
	-- -- -- -- -- -- pb -- 
	-- -- -- -- -- -- -- -- 
	-- -- -- -- sb -- -- -- 


	White				Black
	2 Pawn on the board.		3 Pawn on the board.
	2 Knight on the board.		1 Knight on the board.
	0 Bishop on the board.		0 Bishop on the board.
	0 Rook on the board.		0 Rook on the board.
	1 Queen on the board.		1 Queen on the board.
	1 King on the board.		1 King on the board.


	White				Black
	1 Pawn is threatened.		2 Pawn is threatened.
	2 Knight is threatened.		1 Knight is threatened.
	0 Bishop is threatened.		0 Bishop is threatened.
	0 Rook is threatened.		0 Rook is threatened.
	1 Queen is threatened.		1 Queen is threatened.
	0 King is threatened.		0 King is threatened.

The points are distributed like this:
 
 Pawn = 1          // represented as: p + (b for white or s for black) such as pb and ps

 
 Knight = 3        // represented as: ab as

 
 Bishop = 3        // represented as: fb fs

 
 Rook = 5          // represented as: kb ks

 
 Queen = 9         // represented as: vb vs

 
 King = 100        // represented as: sb ss
