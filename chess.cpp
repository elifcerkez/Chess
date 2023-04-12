#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

// Define 8x8 as below for readability and open less room for typos
#define ROWS 8
#define COLS 8

using namespace std;

class Chess
{
private:
    // Chess board
    string cboard[ROWS][COLS];

public:
	
    // Constructor
    Chess()
    {
	initBoard();
    }

    void initBoard(); 

	// Getter function
    string getPiece(int row, int col)
    {
        return cboard[row][col];
    }

	// Setter function
    void setPiece(int row, int col, string piece)
    {
        cboard[row][col] = piece;
    }
};

void Chess :: initBoard()
{
    // Initialize the chess board with default piece positions
    cboard[0][0] = "ks";
    cboard[0][1] = "as";
    cboard[0][2] = "fs";
    cboard[0][3] = "vs";
    cboard[0][4] = "ss";
    cboard[0][5] = "fs";
    cboard[0][6] = "as";
    cboard[0][7] = "ks";

    for (int i = 0; i < COLS; i++)
    {
        cboard[1][i] = "ps";
        cboard[6][i] = "pb";
    }

    for (int i = 2; i < ROWS - 2; i++)
    {
        for (int j = 0; j < COLS; j++)
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
public:
	
    void readBoard(string fileName);		// Read the file to get the view of chess board
    
    void printBoard();  			// Print the current view of chess board
    
        
    // Define points of pieces in the following order:
    // piyon (p)=1, at (a)=3, fil (f)=3, kale (k)=5, vezir (v)=9, sah (s)=100
    string pieceNames[6] = {"p", "a", "f", "k", "v", "s"};
    
    float piecePoints[6] = {1,3,3,5,9,100};
    float pieceunderAttack[6] = {-0.5, -1.5, -1.5, -2.5, -4.5, -50};	// New scoring for the pieces that are under attack
	
    // Arrays that store the counts of the chess pieces, the order is already given
    int whitePieces[6] = {0};
    int blackPieces[6] = {0};
    
    int whiteunderAttack[6] = {0};
    int blackunderAttack[6] = {0};
    
    int whiteScore = 0;
    int blackScore = 0;
    
    void countPieces(string color, string pieceNames[]);				// Count chess pieces and store them in arrays
    void calculate();

    
};

void ChessBoard :: readBoard(string fileName)
{
    ifstream inputFile(fileName.c_str()); // Defined R and C constants caused a problem, so c_str() is used to avoid it
    string line;
    int i = 0;

    while (i < ROWS)
    {
        int j = 0;
        getline(inputFile, line); // Read each line from the text file
        stringstream p(line);    // Break the line to read chess pieces
        string pieceName;        // Store them as pieceName

        while (p >> pieceName && j < COLS)
        {
            setPiece(i, j, pieceName); // Set the chess piece at the corresponding position on the chess board
            j++;
        }
        i++;
    }
    inputFile.close();
}

void ChessBoard :: printBoard()
{
    for (int i = 0; i < ROWS; i++) 
    {
        for (int j = 0; j < COLS; j++) 
	{
            cout << getPiece(i, j) << " ";
        }
        cout << endl;
    }
}

void ChessBoard :: countPieces(string color, string pieceNames[])
{
	string newPieceNames[6];
	
	// pn stands for piece name. Each loop finds the count of the chess piece with different name/type
	for (int pn = 0; pn < 6; pn++)
	{
	    newPieceNames[pn] = pieceNames[pn] + color;
	    int count = 0;
	
	// Read the whole chess board and find how many pieces correspond to each type
	// For example, at the beginning, 8 pb, 2 ab, 2 fb, 2 kb, 1 vb, and 1 sb for whites
		for (int i = 0; i < ROWS; i++) 
		{
			for (int j = 0; j < COLS; j++) 
			{
		        if (getPiece(i,j) == newPieceNames[pn]) 
				{
		            count++;
		        }
		    }        
		}
		
		// Store the counts of each chess piece with a different name in the array while the color matches
		if (color == "b")
			whitePieces[pn] = count;
		else if (color == "s")
			blackPieces[pn] = count;
	}
}

void ChessBoard::calculate()
{
    // Calculate scores for white pieces
    for (int i = 0; i < 6; i++)
    {
        whiteScore += whitePieces[i] * piecePoints[i] + whiteunderAttack[i] * pieceunderAttack[i];
    }

    // Calculate scores for black pieces
    for (int i = 0; i < 6; i++)
    {
        blackScore += blackPieces[i] * piecePoints[i] + blackunderAttack[i] * pieceunderAttack[i];
    }

    // Print scores for both white and black pieces
    cout << "White Score: " << whiteScore << endl;
    cout << "Black Score: " << blackScore << endl << endl;
}

int main()
{
    string fileName;
    ChessBoard board;

    cout << "Please enter the name of the text file that you want it to be read: ";
    cin >> fileName;
    board.readBoard(fileName + ".txt");		// Read the txt file with the inputted name

    // Print the chess board
    board.printBoard();
    cout << endl << endl;
    
    board.countPieces("b", board.pieceNames);	// Count white pieces ( b defines beyaz)
    board.countPieces("s", board.pieceNames);   // Count black pieces ( s defines siyah)
	
    board.calculate();
	
/*	Control statements that checks the correctness of the number and type of pieces on the chessboard.
	for (int i = 0; i < 6; i++)
	{
	    cout << "There are " << board.whitePieces[i] << " " << board.pieceNames[i] + "b" << endl;
	}
    
        cout << endl << endl;

        for (int i = 0; i < 6; i++)
	{
	    cout << "There are " << board.blackPieces[i] << " " << board.pieceNames[i] + "s" << endl;
	}
	
*/	
    return 0;
}
