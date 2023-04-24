#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

// Define 8x8 as below for readability and open less room for typos.
#define R 8
#define C 8

using namespace std;

class Chess
{
private:
	// Chess board
    string cboard[R][C];

public:
	
	// Constructor
	Chess()
	{
		initBoard();
	}

    void initBoard(); 

    string getPiece(int row, int col)
    {
        return cboard[row][col];
    }

    void setPiece(int row, int col, string piece)
    {
        cboard[row][col] = piece;
    }
};

void Chess :: initBoard()
{
    // Initialize the chess board with default piece positions.
    cboard[0][0] = "ks";
    cboard[0][1] = "as";
    cboard[0][2] = "fs";
    cboard[0][3] = "vs";
    cboard[0][4] = "ss";
    cboard[0][5] = "fs";
    cboard[0][6] = "as";
    cboard[0][7] = "ks";

    for (int i = 0; i < C; i++)
    {
        cboard[1][i] = "ps";
        cboard[6][i] = "pb";
    }

    for (int i = 2; i < R - 2; i++)
    {
        for (int j = 0; j < C; j++)
        {
        	// -- for empty squares
            cboard[i][j] = "--";
        }
    }

    cboard[7][0] = "kb";
    cboard[7][1] = "ab";
    cboard[7][2] = "fb";
    cboard[7][3] = "vb";
    cboard[7][4] = "sb";
    cboard[7][5] = "fb";
    cboard[7][6] = "ab";
    cboard[7][7] = "kb";
}

class ChessBoard : public Chess
{
private:
    // Define Scores of pieces in the following order:
    // piyon (p)=1, at (a)=3, fil (f)=3, kale (k)=5, vezir (v)=9, sah (s)=100
    float pieceScores[6] = {1,3,3,5,9,100};
    
    // New scoring for the pieces that are under attack
	float pieceUnderAttack[6] = {-0.5, -1.5, -1.5, -2.5, -4.5, -50};
    float whiteScore = 0;
    float blackScore = 0;
    
public:
    
    // Constructor
    // Read the file to set the view of chess board.
    ChessBoard(string fileName)
    {
        ifstream inputFile(fileName.c_str());
        string line;
        int i = 0;
    
        while (i < R)
        {
            int j = 0;
			// Read each line from the text file.
            getline(inputFile, line);
			
			// Break the line to read chess pieces.
            stringstream p(line);
			
			// Store them as pieceName.
            string pieceName;
    
			// Set the chess piece at the corresponding position on the chess board.
            while (p >> pieceName && j < C)
            {
                setPiece(i, j, pieceName);
                j++;
            }
            i++;
        }
        inputFile.close();
        
    }

    // The names and order that will be used throughout the program
    string pieceNames[6] = {"p", "a", "f", "k", "v", "s"};

	// Arrays that store the counts of the chess pieces, in the same order as above
    int whitePieces[6] = {0};
    int blackPieces[6] = {0};
    
    // Arrays that store the counts of the chess pieces under a threat, in the same order as above
    int whiteUnderAttack[6] = {0};
    int blackUnderAttack[6] = {0};

    // Each square is flagged as false at the beginning. Throughout the program, if the square (therefore the piece) is threatened, it is set to true.
    // This is done to avoid checking the same square twice or more.
    bool threatened[8][8] = {false};

    void printBoard();

    // Count chess pieces and store them in arrays.
    void countPieces(string color, string pieceNames[]);				
    void calculate();


void attackedbyPawn()
{
    for (int i = 0; i < R; i++)
    {   
        for (int j = 0; j < C; j++)
        {   
            // Define pawn moves.
            int whitePawnMoves[2][2] = {{-1,-1}, {-1,1}};
            int blackPawnMoves[2][2] = {{1,-1}, {1,1}};

            string whitePiece = getPiece(i,j);
            if (whitePiece.find('b') != string::npos && threatened[i][j] == false) 
            {
                // Flag to keep track of whether this piece is under attack.
                bool isUnderAttack = false;

                // Check all 2 possibilities of pawn moves.
                for (int k = 0; k < 2; k++)
                {
                    int x = i + whitePawnMoves[k][0];
                    int y = j + whitePawnMoves[k][1];
                    
                    // Check if the (x,y) pair is on the board.
                    if (x >= 0 && x < R && y >= 0 && y < C) 
                    {
                        // Check if there is any rival (black) pawn that can be a threat.
                        if (getPiece(x, y) == "ps")
                        {   
                            for (int k = 0; k < 6; k++)
                            {
                                if (whitePiece.find(pieceNames[k]) != string::npos)
                                {  
                                    isUnderAttack = true;
                                    break;
                                }
                            }
                        }
                    }
                }
                
                // If the piece is under attack, increase the count of the corresponding piece type in the array.
                if (isUnderAttack)
                {
                    for (int k = 0; k < 6; k++)
                    {
                        if (whitePiece.find(pieceNames[k]) != string::npos)
                        {  
                            threatened[i][j] = true;
                            whiteUnderAttack[k]++;
                            break;
                        }
                    }
                }
            }
            
            string blackPiece = getPiece(i,j);
			// Note that "sb" refers to white king, and 's' in "sb" will confuse the program since 's' refers to color black.
            if (blackPiece.find('s') != string::npos && blackPiece != "sb" && threatened[i][j] == false) 
            {
                // Flag to keep track of whether this piece is under attack
                bool isUnderAttack = false;

                // Check all 2 possibilities of pawn moves.
                for (int k = 0; k < 2; k++)
                {
                    int x = i + blackPawnMoves[k][0];
                    int y = j + blackPawnMoves[k][1];
                    
                    // Check if the (x,y) pair is on the board.
                    if (x >= 0 && x < R && y >= 0 && y < C) 
                    {
                        // Check if there is any rival (white) pawn that can be a threat.
                        if (getPiece(x, y) == "pb")
                        {   
                            for (int k = 0; k < 6; k++)
                            {
                                if (blackPiece.find(pieceNames[k]) != string::npos)
                                {  
                                    isUnderAttack = true;
                                    break;
                                }
                            }
                        }
                    }
                }
                
                // If the piece is under attack, increase the count of the corresponding piece type in the array.
                if (isUnderAttack)
                {
                    for (int k = 0; k < 6; k++)
                    {
                        if (blackPiece.find(pieceNames[k]) != string::npos)
                        {  
                            threatened[i][j] = true;
                            blackUnderAttack[k]++;
                            break;
                        }
                    }
                }
            }
            
        }
    }
}

void attackedbyKnight()
{
    for (int i = 0; i < R; i++)
    {   for (int j = 0; j < C; j++)
        {   
            // If there is a knight in the position of the piece that can move to that position, the piece is under threat.
            // Define knight moves.
            int knightMoves[8][2] = {{-2,1}, {-1,2}, {1,2}, {2,1}, {2,-1}, {1,-2}, {-1,-2}, {-2,-1}};

            string whitePiece = getPiece(i,j);
            if (whitePiece.find('b') != string::npos && threatened[i][j] == false) 
            {
                bool isUnderAttack = false;
                
                // Check all 8 possibilities of knight moves.
                for (int k = 0; k < 8; k++)
                {
                    int x = i + knightMoves[k][0];
                    int y = j + knightMoves[k][1];
                    
                    // Check if the (x,y) pair is on the board.
                    if (x >= 0 && x < 8 && y >= 0 && y < 8) 
                    {
                        // Check if there is any rival (black) knight that can be a threat.
                        if (getPiece(x, y) == "as") 
                        {   
                            for (int k = 0; k < 6; k++)
                            {
                                if (whitePiece.find(pieceNames[k]) != string::npos)
                                {   
                                    isUnderAttack = true;
                                    break;
                                }
                            }
                        }
                    }
                }
                
                if (isUnderAttack)
                {
                    for (int k = 0; k < 6; k++)
                    {
                        if (whitePiece.find(pieceNames[k]) != string::npos)
                        {  
                            threatened[i][j] = true;
                            whiteUnderAttack[k]++;
                            break;
                        }
                    }
                }                
            }

            string blackPiece = getPiece(i,j);
            if (blackPiece.find('s') != string::npos && blackPiece != "sb" && threatened[i][j] == false) 
            {
                bool isUnderAttack = false;
                
                for (int k = 0; k < 8; k++) 
                {
                    int x = i + knightMoves[k][0];
                    int y = j + knightMoves[k][1];
                    
                    if (x >= 0 && x < 8 && y >= 0 && y < 8) 
                    {
                        // Check if there is any rival (white) knight that can be a threat.
                        if (getPiece(x, y) == "ab") 
                        {   
                            for (int k = 0; k < 6; k++)
                            {
                                if (blackPiece.find(pieceNames[k]) != string::npos)
                                {   
                                    isUnderAttack = true;
                                    break;
                                }
                            }                            
                        }
                    }
                }
                
                if (isUnderAttack)
                {
                    for (int k = 0; k < 6; k++)
                    {
                        if (blackPiece.find(pieceNames[k]) != string::npos)
                        {  
                            threatened[i][j] = true;
                            blackUnderAttack[k]++;
                            break;
                        }
                    }
                }
            }
        }
    }
}

void attackedbyQueen()
{
    // Define a temporary board.
    string copyboard[8][8];

    // Copy the board to a temporary board.
    for  (int i = 0; i < R; i++)
    {
        for (int j = 0; j < C; j++)
        {
            copyboard[i][j] = getPiece(i,j); 
        }
    }

    for (int i = 0; i < R; i++) 
    {
        for (int j = 0; j < C; j++) 
        {
            string whitePiece = copyboard[i][j];
            if ( whitePiece.find('b') != string::npos && threatened[i][j] == false )
            {
                // Check column-wise, lower side.
                for (int x = i+1; x < R; x++)
                {   
                    // Find the first occurence of non-empty square.
                    if (copyboard[x][j] != "--")
                    {   
                        // Check if the piece is a black queen, if so, the piece is under threat.
                        if (copyboard[x][j] == "vs")
                        {
                            for (int k = 0; k < 6; k++)
                            {
                                if (whitePiece.find(pieceNames[k]) != string::npos)
                                {   
                                    threatened[i][j] = true;
                                    whiteUnderAttack[k]++;
                                    break;
                                }
                            }
                        }
                    
                    break;
                    }
                }

                // Check column-wise, upper side.
                for (int x = i-1; x >= 0; x--)
                {
                    if (copyboard[x][j] != "--")
                    {
                        if (copyboard[x][j] == "vs")
                        {
                            for (int k = 0; k < 6; k++)
                            {
                                if (whitePiece.find(pieceNames[k]) != string::npos)
                                {   
                                    threatened[i][j] = true;
                                    whiteUnderAttack[k]++;
                                    break;
                                }
                            }
                        }
                        
                    break;
                    }
                }

                // Check row-wise, right side.
                for (int y = j+1; y < C; y++)
                {   
                    if (copyboard[i][y] != "--")
                    {   
                        if (copyboard[i][y] == "vs")
                        {
                            for (int k = 0; k < 6; k++)
                            {
                                if (whitePiece.find(pieceNames[k]) != string::npos)
                                {   
                                    threatened[i][j] = true;
                                    whiteUnderAttack[k]++;
                                    break;
                                }
                            }
                        }
                    
                    break;
                    }
                }

                // Check row-wise, left side.
                for (int y = j-1; y >= 0; y--)
                {   
                    if (copyboard[i][y] != "--")
                    {   
                        if (copyboard[i][y] == "vs")
                        {
                            for (int k = 0; k < 6; k++)
                            {
                                if (whitePiece.find(pieceNames[k]) != string::npos)
                                {   
                                    threatened[i][j] = true;
                                    whiteUnderAttack[k]++;
                                    break;
                                }
                            }
                        }
                    
                    break;
                    }
                }

                // Check left upper diagonal.
                for (int x = i-1, y = j-1; x >= 0 && y >= 0; x--, y--) 
                {
                    if (copyboard[x][y] != "--")
                    {   
                        if (copyboard[x][y] == "vs")
                        {
                            for (int k = 0; k < 6; k++)
                            {
                                if (whitePiece.find(pieceNames[k]) != string::npos)
                                {   
                                    threatened[i][j] = true;
                                    whiteUnderAttack[k]++;
                                    break;
                                }
                            }
                        }
                    
                    break;
                    }
                }

                // Check right lower diagonal.
                for (int x = i+1, y = j+1; x < R && y < C; x++, y++)
                {
                    if (copyboard[x][y] != "--")
                    {   
                        if (copyboard[x][y] == "vs")
                        {
                            for (int k = 0; k < 6; k++)
                            {
                                if (whitePiece.find(pieceNames[k]) != string::npos)
                                {   
                                    threatened[i][j] = true;
                                    whiteUnderAttack[k]++;
                                    break;
                                }
                            }
                        }
                    
                    break;
                    }
                }

                // Check right upper diagonal.
                for (int x = i-1, y = j+1; x >= 0 && y < C; x--, y++)
                {
                    if (copyboard[x][y] != "--")
                    {   
                        if (copyboard[x][y] == "vs")
                        {
                            for (int k = 0; k < 6; k++)
                            {
                                if (whitePiece.find(pieceNames[k]) != string::npos)
                                {   
                                    threatened[i][j] = true;
                                    whiteUnderAttack[k]++;
                                    break;
                                }
                            }
                        }
                    
                    break;
                    }
                }

                // Check left lower diagonal.
                for (int x = i+1, y = j-1; x < R && y >= 0; x++, y--)
                {
                    if (copyboard[x][y] != "--")
                    {   
                        if (copyboard[x][y] == "vs")
                        {
                            for (int k = 0; k < 6; k++)
                            {
                                if (whitePiece.find(pieceNames[k]) != string::npos)
                                {   
                                    threatened[i][j] = true;
                                    whiteUnderAttack[k]++;
                                    break;
                                }
                            }
                        }
                    
                    break;
                    }
                }   
            }

            string blackPiece = copyboard[i][j];
            if ( blackPiece.find('s') != string::npos && blackPiece != "sb" && threatened[i][j] == false )
            {
                // Check column-wise, lower side.
                for (int x = i+1; x < R; x++)
                {   
                    // Find the first occurence of non-empty square.
                    if (copyboard[x][j] != "--")
                    {   
                        // Check if the piece is a white queen, if so, the piece is under threat.
                        if (copyboard[x][j] == "vb")
                        {
                            for (int k = 0; k < 6; k++)
                            {
                                if (blackPiece.find(pieceNames[k]) != string::npos)
                                {   
                                    threatened[i][j] = true;
                                    blackUnderAttack[k]++;
                                    break;
                                }
                            }
                        }
                    
                    break;
                    }
                }

                // Check column-wise, upper side.
                for (int x = i-1; x >= 0; x--)
                {
                    if (copyboard[x][j] != "--")
                    {
                        if (copyboard[x][j] == "vb")
                        {
                            for (int k = 0; k < 6; k++)
                            {
                                if (blackPiece.find(pieceNames[k]) != string::npos)
                                {   
                                    threatened[i][j] = true;
                                    blackUnderAttack[k]++;
                                    break;
                                }
                            }
                        }
                        
                    break;
                    }
                }

                // Check row-wise, right side.
                for (int y = j+1; y < C; y++)
                {   
                    if (copyboard[i][y] != "--")
                    {   
                        if (copyboard[i][y] == "vb")
                        {
                            for (int k = 0; k < 6; k++)
                            {
                                if (blackPiece.find(pieceNames[k]) != string::npos)
                                {   
                                    threatened[i][j] = true;
                                    blackUnderAttack[k]++;
                                    break;
                                }
                            }
                        }
                    
                    break;
                    }
                }

                // Check row-wise, left side.
                for (int y = j-1; y >= 0 ; y--)
                {   
                    if (copyboard[i][y] != "--")
                    {   
                        if (copyboard[i][y] == "vb")
                        {
                            for (int k = 0; k < 6; k++)
                            {
                                if (blackPiece.find(pieceNames[k]) != string::npos)
                                {   
                                    threatened[i][j] = true;
                                    blackUnderAttack[k]++;
                                    break;
                                }
                            }
                        }
                    
                    break;
                    }
                }

                // Check left upper diagonal.
                for (int x = i-1, y = j-1; x >= 0 && y >= 0; x--, y--) 
                {
                    if (copyboard[x][y] != "--")
                    {   
                        if (copyboard[x][y] == "vb")
                        {
                            for (int k = 0; k < 6; k++)
                            {
                                if (blackPiece.find(pieceNames[k]) != string::npos)
                                {   
                                    threatened[i][j] = true;
                                    blackUnderAttack[k]++;
                                    break;
                                }
                            }
                        }
                    
                    break;
                    }
                }

                // Check right lower diagonal.
                for (int x = i+1, y = j+1; x < R && y < C; x++, y++)
                {
                    if (copyboard[x][y] != "--")
                    {   
                        if (copyboard[x][y] == "vb")
                        {
                            for (int k = 0; k < 6; k++)
                            {
                                if (blackPiece.find(pieceNames[k]) != string::npos)
                                {   
                                    threatened[i][j] = true;
                                    blackUnderAttack[k]++;
                                    break;
                                }
                            }
                        }
                    
                    break;
                    }
                }

                // Check right upper diagonal.
                for (int x = i-1, y = j+1; x >= 0 && y < C; x--, y++)
                {
                    if (copyboard[x][y] != "--")
                    {   
                        if (copyboard[x][y] == "vb")
                        {
                            for (int k = 0; k < 6; k++)
                            {
                                if (blackPiece.find(pieceNames[k]) != string::npos)
                                {   
                                    threatened[i][j] = true;
                                    blackUnderAttack[k]++;
                                    break;
                                }
                            }
                        }
                    
                    break;
                    }
                }

                // Check left lower diagonal.
                for (int x = i+1, y = j-1; x < R && y >= 0; x++, y--)
                {
                    if (copyboard[x][y] != "--")
                    {   
                        if (copyboard[x][y] == "vb")
                        {
                            for (int k = 0; k < 6; k++)
                            {
                                if (blackPiece.find(pieceNames[k]) != string::npos)
                                {   
                                    threatened[i][j] = true;
                                    blackUnderAttack[k]++;
                                    break;
                                }
                            }
                        }
                    
                    break;
                    }
                }

            }
        }
    }
}
};

void ChessBoard :: printBoard()
{
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) 
		{
            cout << getPiece(i, j) << " ";
        }
        cout << endl;
    }
}

void ChessBoard :: countPieces(string color, string pieceNames[])
{
	string newPieceNames[6];
	
	// pn stands for piece name. Each loop finds the count of the chess piece with different name/type.
	for (int pn = 0; pn < 6; pn++)
	{
		newPieceNames[pn] = pieceNames[pn] + color;
	    int count = 0;
	
	// Read the whole chess board and find how many pieces correspond to each type.
	// For example, at the beginning, 8 pb, 2 ab, 2 fk, 2 kb, 1 vb, and 1 sb for whites.
		for (int i = 0; i < R; i++) 
		{
			for (int j = 0; j < C; j++) 
			{
		        if (getPiece(i,j) == newPieceNames[pn]) 
				{
		            count++;
		        }
		    }        
		}
		
		// Store the counts of each chess piece with a different name in the array while the color matches.
		// For example, whitePieces[0] = 8, whitePieces[1] = 2, whitePieces[2] = 2, whitePieces[3] = 1, whitePieces[4] = 1, whitePieces[5] = 1.
		if (color == "b")
			whitePieces[pn] = count;
		else if (color == "s")
			blackPieces[pn] = count;
	}
}

void ChessBoard::calculate()
{
    // Calculate the score for white pieces.
    for (int i = 0; i < 6; i++)
    {
        whiteScore += whitePieces[i] * pieceScores[i] + whiteUnderAttack[i] * pieceUnderAttack[i];
    }

    // Calculate the score for black pieces.
    for (int i = 0; i < 6; i++)
    {
        blackScore += blackPieces[i] * pieceScores[i] + blackUnderAttack[i] * pieceUnderAttack[i];
    }

    cout << "\tWhite Score: " << whiteScore << endl;
    cout << "\tBlack Score: " << blackScore << endl << endl;
}

int main()
{
	string fileName;

    cout << "Please enter the name of the text file that you want it to be read: ";
    cin >> fileName;
    
    ChessBoard board(fileName + ".txt");
    
    board.attackedbyPawn();
    board.attackedbyKnight();
    board.attackedbyQueen();

	board.countPieces("b", board.pieceNames);
	board.countPieces("s", board.pieceNames);
	
	// Print both players' scores.
	board.calculate();
	

//	TEST STATEMENTS FOR THE PROGRAM
/*
    string fullPieceNames[6] = {"Pawn", "Knight", "Bishop", "Rook", "Queen", "King"};

    board.printBoard();
    	cout << endl << endl;

	// Shows how many chess pieces are currently on the board for white and black, separately.
    cout << "\tWhite" << "\t\t\t\tBlack" << endl;
	for (int i = 0; i < 6; i++)
	{
	    cout << "\t" << board.whitePieces[i] << " " << fullPieceNames[i] + " on the board.";
        cout << "\t\t" << board.blackPieces[i] << " " << fullPieceNames[i] + " on the board." << endl;
	}
    cout << endl << endl;

	// Shows how many chess pieces are currently under threat for white and black, separately.
    cout << "\tWhite" << "\t\t\t\tBlack" << endl;
    for (int i = 0; i < 6; i++) 
    {
        cout << "\t" << board.whiteUnderAttack[i] << " " << fullPieceNames[i] << " is threatened." ;
        cout << "\t\t" << board.blackUnderAttack[i] << " " << fullPieceNames[i] << " is threatened." << endl;
    }
    
    cout << endl;
*/
    return 0;
}
