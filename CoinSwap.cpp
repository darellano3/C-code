
#include <iostream>
using namespace std;

// Global constants
const int BoardSize=5;
// structure to be used for linked lists
struct Node {
    char theBoard[ BoardSize];        // copy of move number
    int moveNumber;                    // move number
    Node *pNext;                       // pointer to next node
};

//--------------------------------------------------------------------------------
// Display name and program information
void displayIdentifyingInformation(){
    printf("Daisy Arellano");
    printf("Program5\n");
    printf("TA Nilanjana Basuu. T 10-11 \n");
}//--------------------------------------------------------------------------------
// Display instructions
void displayInstructions()
{
    cout << "Welcome to the coin swap puzzle.                             \n"
    << "Make moves to solve the puzzle where the objective is to swap the \n"
    << "place of the pieces on either side of the board.  X can only move \n"
    << "to the right into an empty square, or can jump to the right over  \n"
    << "an O into an empty square. Conversely O can only move to the left \n"
    << "into an empty square, or can jump to the left over an X into an   \n"
    << "empty square.  \n"
    << " \n"
    << "For each move enter the source (1..5) and destination (1..5).     \n"
    << "Enter 0 to exit the program. \n";
}
//--------------------------------------------------------------------------------
// See if game is over by checking final condition
bool notDone( char board[])
{
    return board[0]!='O' || board[1]!='O' || board[3]!='X' || board[4]!='X';
}
void displayBoard( char board[])
{
    cout << endl;
    cout << "   1 2 3 4 5\n";
    cout << "   ";
    for( int i=0; i<BoardSize; i++) {
        cout << board[ i] << " ";
    }
    cout << endl;
}
//--------------------------------------------------------------------------------
void undoMove( Node * &pHead,        // head of list, gets changed and returned
              int &moveNumber,      // move number
              char board[]){  // the board
    // check to see if this is not the beginning of the game
    if( pHead->pNext != NULL) {
        // undo the move by getting rid of the front node to restore board
        Node *pOriginalHead = pHead;      // save the original head of the list so that we can use it later
        pHead = pHead->pNext;        // move the head of the list to the next value
        // find previous mood by going through the board
        for( int i=0; i < BoardSize; i++) {
            board[i] = pHead->theBoard[i];
        }
        // extract the move number from the one stored for this node
        moveNumber = pHead->moveNumber;
        delete( pOriginalHead);             // delete original head of list
        displayBoard(board);
    }
    else {
        cout << "*** You cannot undo past the beginning of the game.  Please retry." << endl << endl;
    }
}
//--------------------------------------------------------------------------------
void promptForAndGetMove( char board[], int &moveNumber, int &source, int &destination, Node * &pHead)
{
    char userInput;
    
    // infinite loop can handle multiple undos
    while( true) {
        cout << moveNumber << ". Enter source and destination: ";
        cin >> userInput;
        // See if user input of 0 was given to exit the program
        if( userInput == '0') {
            cout << "\n";
            cout << "Exiting program\n";
            exit( 0);
        }
        if( userInput == 'u') {
            // undo the move
            undoMove( pHead, moveNumber, board);
            // go back up to back a move again
            continue;
        }
              // Input is likely numeric and is not '0' or 'u'.  Convert to a number.
        source = userInput - '0';
        // Also get destination portion of user input
        cin >> destination;
        // make sure user entry translates to position correctly
        source = source - 1;
        destination = destination - 1;
        // break out of loop because there is no more undos so this loop is over
        if( (destination >= 0 && source >= 0) && ( destination < 6 && source < 6)){
        moveNumber++;
        }
        else{
            cout<< " *** You can't refer to a position off the board. Invalid move, please retry.\n";
            return;
        }
            break;
    }
}
//--------------------------------------------------------------------------------
//function both makes the move and checks it against an "ideal move" which verifies user input is correct
void makeValidMove(int source, char theBoard[], int destination)
{
    // local variable
    char idealDestination;  //this is the destination which the user should be entering
    char next;          // this holds the value for the next move over
    char cross;   // character stored in destination if we must cross another piece
    int direction = 0;     // direction in which we should be moving
    
    // Find the right input (right direction)
    if( theBoard[ source]=='X') {
        direction = 1;      // 'X' moves 1 right
    }
    else {
        direction = -1;     // 'O' moves 1 left
    }
    //find correct position if position is correct but in wrong direction tell user they are moving in the wrong direction
    idealDestination = source + direction;
    if( destination == source - direction && (destination >= 0 && source >= 0) && ( destination < 6 && source < 6)){
        cout << "*** You can't move that piece that direction. Invalid move, please retry.\n";
        return;
    }
    if( theBoard[destination] != ' ' && (destination >= 0 && source >= 0) && ( destination < 6 && source < 6)){
        cout << "*** Destination square is not empty. Invalid move, please retry. \n";
        return;
    }
    next = theBoard[ idealDestination];
    // but if this destination is not available the new destination will be 2 over not 1
    if ( next != ' ') {
        idealDestination = source + (direction*2);
        cross = theBoard[ source + direction];
        if( cross == theBoard[source]){
            cout << "*** A jumped square must have an opponent. Invalid move, please retry. ";
            return;
        }
    }
    // if ideal destination and the user entered destination do not match then we prompt user for a new move
    // since we checked for all other reasons the users destination must be too far away
    if(idealDestination != destination && (destination >= 0 && source >= 0) && ( destination < 6 && source < 6)){
            cout << "*** Destination is too far away. Invalid move, please retry.";
            return;
    }
    // Make move
    char pieceBeingMoved;
    // choose correct letter (heads or tails)
    
    pieceBeingMoved = theBoard[source];
    
    // now store into correct location
    theBoard[ idealDestination] = pieceBeingMoved;
    // replace old piece with a blank
    theBoard[ source] = ' ';
}
void updateNodes( Node * &pHead,        // this parameter changes every time function runs
                     int moveNumber,        // helps us keep track of move number
                     char board[])          //our initial board
{
    Node *pOriginalHead = pHead;   // keep track of our original head since we change it but will need a node to point to it
    
    pHead = new Node;         // this node is blank
    pHead->pNext = pOriginalHead;  // points to the previous node on list
    
    // create new board with applied changes
    for( int i=0; i< BoardSize; i++) {
        pHead->theBoard[ i] = board[ i];
    }
    // add the move number to the node
    pHead->moveNumber = moveNumber;
    
}//end storeMoveOnList

//--------------------------------------------------------------------------------
int main()
{
    char board[ BoardSize + 1] = "XX OO";  // extra character for the NULL
    int source, destination;
    int moveNumber = 1;
     Node *pHead = NULL;          // initialize head of list pointer.  Very important to initialize this!
    // Display identifying information, the instructions, and the initial board
    displayIdentifyingInformation();
    displayInstructions();
    displayBoard( board);
    // create the initial node on the list, containing the blank board
    updateNodes( pHead, moveNumber, board);
    // Game play loop
    while( notDone( board) ) {
        promptForAndGetMove( board, moveNumber, source, destination, pHead);
        if( (destination >= 0 && source >= 0) && ( destination < 6 && source < 6)){
        makeValidMove( source, board, destination);
        // Store new move on linked list
        updateNodes( pHead, moveNumber, board);
        displayBoard( board);
        }
        else continue;
    }
    
    cout << "Congratulations, you did it! \n"
    << "\n"
    << "Exiting program ...\n";
    return 0;         // return value to keep C++ happy
}
