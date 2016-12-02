#include <iostream>   // For general IO
#include <fstream>    // For file input and output
#include <cassert>    // For the assert statement
#include <map>
#include <random>
#include <ctime>
#include <time.h>
using namespace std;
const int NumberOfWords = 500000;   // Number of dictionary words
const int MinWordLength = 3;      // Minimum dictionary word size to be stored
const int MaxWordLength = 16;     // Max word size.
const int NumberOfWordsInDictionary = 263533; //words in dictionary
void displayIdentifyingInformation(){
    printf("Daisy Arellano");
    printf("Program5\n");
    printf("TA Nilanjana Basuu. T 10-11 \n");
}
// code used from Dale Reed's Allocate file
int binarySearch( const char searchWord[],   // word to be looked up
                 char **dictionary,  // the dictionary of word
                 int numberOfDictionaryWords)      // number of words in the dictionary
{
    int low, mid, high;     // array indices for binary search
    int searchResult = -1;  // Stores index of word if search succeeded, else -1
    // Binary search for word
    low = 0;
    high = numberOfDictionaryWords - 1;
    while ( low <= high)  {
        mid = (low + high) / 2;
        // searchResult negative value means word is to the left, positive value means
        // word is to the right, value of 0 means word was found
        searchResult = strcmp( searchWord, dictionary[ mid]);
        if ( searchResult == 0)  {
            // Word IS in dictionary, so return the index where the word was found
            return mid;
        }
        else if (searchResult < 0)  {
            high = mid - 1; // word should be located prior to mid location
        }
        else  {
            low = mid + 1; // word should be located after mid location
        }
    }
    // Word was not found
    return -1;
}//end binarySearch()
void displayIntro()
{
    printf("Welcome to the game of Boggle, where you play against the clock\nto see how many words you can find using adjacent letters on the\nboard.  Each letter can be used only once for a given word.\nWhen prompted to provide input you may also:\nEnter 'r' to reset the board to user-defined values.\nEnter 's' to solve the board and display all possible words.\nEnter 't' to toggle the timer off/on.\nEnter 'x' to exit the program.\n\n"                       );
}



// Allocate memory for dictionary words array.
// Note that the '&' is needed so that the new array
// address is passed back as a reference parameter.
void allocateArray( char ** & matrix)
{
    // Allocate space for large array of C-style strings
    matrix = new char*[ NumberOfWords];
    // For each array entry, allocate space for the string to be stored there
    for (int i=0; i < NumberOfWords; i++) {
        matrix[i] = new char[ MaxWordLength];
            // just to be safe, initialize C-string to all null characters
        
        for (int j=0; j < MaxWordLength; j++) {
            matrix[i][j] = NULL;
        }//end for (int j=0...
    }//end for (int i...
}//end allocateArray()
// Deallocate memory for the dictionary words array. I suppos
// the '&' to make matrix a reference parameter is not strictly
// necessary, since the memory is freed up in either case.
void deallocateArray( char ** & matrix)
{
    // Deallocate dynamically allocated space for the array
    for (int i=0; i < NumberOfWords; i++) {
        delete [] matrix[ i];
    }
    delete [] matrix; // delete the array at the outermost level
}
//count letters in our word
int countLetters( char aWord[]){
    int i = strlen( aWord);
    return i;
}

// print approprate message and return appropriate points
int pointCounter( int letterNum){
    if( letterNum == 3){
        printf("Worth 1 point\n");
        return 1;
    }
    else if (letterNum == 4){
        printf("Worth 2 points\n");
        return 2;
    }
    else if( letterNum == 5){
        printf("Worth 4 points\n");
        return 4;
    }
    else{printf("Worth %d points\n", letterNum);
        return letterNum;}
}
void printBoard(char board[]){
    //print board using a one d array
    cout << board[0] << " " << board[1]<< " " << board[2] << " " << board[3] << " " << board[4] << " " << board[5] << "\n";
    cout <<  board[6] << " " << board[7] << " " << board[8] << " " << board[9] << " " << board[10] << " " << board[11] << "\n";
    cout << board[12] << " " << board[13] << " " << board[14] << " " << board[15] << " " << board[16] << " " << board[17] << "\n";
    cout <<  board[18] << " " << board[19] << " " << board[20] << " " << board[21] << " " << board[22] << " " << board[23] <<"\n";
    cout <<  board[24] << " " << board[25] << " " << board[26] << " " << board[27] << " " << board[28] << " " << board[29] <<"\n";
    cout <<  board[30] << " " << board[31] << " " << board[32] << " " << board[33] << " " << board[34] << " " << board[35] <<"\n";
}



void randBoard( char board[]){
    double r;
    srand(time(NULL));
    for( int j = 0; j <37; j++)
    {
        r = (double)(rand()%10000)/10000;
        float frequency[] = {0.07680,  //  a
            0.09485,  //  b
            0.13527,  //  c
            0.16824,  //  d
            0.28129,  //  e
            0.29299,  //  f
            0.32033,  //  g
            0.34499,  //  h
            0.43625,  //  i
            0.43783,  //  j
            0.44627,  //  k
            0.49865,  //  l
            0.52743,  //  m
            0.59567,  //  n
            0.66222,  //  o
            0.69246,  //  p
            0.69246,  //  q
            0.76380,  //  r
            0.86042,  //  s
            0.92666,  //  t
            0.95963,  //  u
            0.96892,  //  v
            0.97616,  //  w
            0.97892,  //  x
            0.99510,  //  y
            1.00000}; //  z
        int i;
        //get right letter for value
        for ( i = 0; i <27; i++){
            if( r < frequency[i]){
                break;
            }
        }
        char letter = (char) 'a' + i;
        //enter our new letter into appropriate spaces of array
        if(6 < j && j < 11){
            board[j] = letter;
        }
        if( j > 12 && j < 17){
            board[j] = letter;
        }
        if(j > 18 && j < 23){
            board[j] = letter;
        }
        if( j > 24 && j <29){
            board[j] = letter;
        }
    }
}
//recursive function to find if all characters are around eachother and on board
bool findNextCharacter( char board[], char userInput[], int indexOfCharacter, int wordLetter)
{
    bool wordWasFound = false;//return false if no loops are entered
    char tempBoard[37];//temp board note: this was created just in case things changed and I wanted original board
    for( int z = 0; z < 37; z++){
        tempBoard[z] = board[z];// copy all original values into our board
    }//to start off if our letter count matches the amount of times this function has run then this
    //word and every letter in it is in our board
    if( wordLetter == strlen(userInput)){
        return true;
    }
    //array of all possible directions
    int moveArray[] = {6, 1, -1, -6, 7, -7, 5, -5};
    // Go through all 8 possible moves and see if 2nd character is found
    for( int i = 0; i < 8; i++){
        //mark next index as our current index plus current move
        int next = indexOfCharacter + moveArray[i];
        //if our letter matches our current move then move into next loop
        if(userInput[ wordLetter] == tempBoard[next]){
            //mark our temporary board with an asterik so we dont backtrack
            char temp = tempBoard[next];
            tempBoard[next] = '*';
            indexOfCharacter = next;
            //call function again but with next letter
            wordWasFound = findNextCharacter( tempBoard, userInput, indexOfCharacter, wordLetter + 1);
            //if our word was found then return back to original board otherwise we can check other first values
            if(wordWasFound){
                tempBoard[i] = temp;
                break;
            }
        }
    }
    return wordWasFound;
}
//find our first letter
bool firstLetter( char board[], char word[]){
    char tempBoard[37];
    for( int z = 0; z < 37; z++){
        tempBoard[z] = board[z];
    }
    //send false if letter is never found
    bool wordWasFound = false;
    int c = 0;   // get the first character
    for( int i = 0; i <37; i++){
        // if it is found enter next loop
        if( word[c] == tempBoard[i]){
            char temp = tempBoard[i];
            //replace with astericks as to not backtrack
            tempBoard[i] = '*';
            //move on to the next char
            wordWasFound = findNextCharacter(tempBoard, word, i, c + 1);
            //once function is done return to normal board
            tempBoard[i] = temp;
            break;
        }
    }
    return wordWasFound;
}
void resetBoard(char board[], char word[], char tempBoard[]){
    char userArray[37];
    //only enter this loop if the user put in an r alone
    if( word[0] == 'r' && (strlen(word) < 2)){
        cout << "enter letters to be used\n";
        //take in users desired board letters
        cin >> userArray;
        for(int i = 0; i < 37; i++){
            //this for loop enters desired characters into appropriate spaces
            if(6 < i && i < 11){
                board[i] = userArray[i -7];
            }
            if( i > 12 && i < 17){
                board[i] = userArray[i- 9];
            }
            if(i > 18 && i < 23){
                board[i] = userArray[i - 11];
            }
            if( i > 24 && i <29){
                board[i] = userArray[i - 13];
            }
        }
        for( int z = 0; z < 37; z++){
            tempBoard[z] = board[z];
        }
        printBoard( board);
    }
    //if the user didnt press r then proceed onto printing a regular board
    else{
        cout << "\n";
        printBoard( board);}
}
void sortAnswers( char **dictionary, int *index, char *userInput,int wordRows){
    //for every row in dictionary compare to our user input
    for( int i = 0; i < wordRows; i++){
        if(strcmp( dictionary[i], userInput) == 0){
            // if they are the same then create memory for our index of the length of word
            index[i] = strlen(userInput);
        }
    }
    //this loop searches the appropriate lengths in order
    //so 3 first then 4 etc.
    // if the word and the length match print the dictionary entry which is
    //already in abc order
    for(int j = 3; j < 17; j++){
        for(int i = 0; i < wordRows; i++){
            if(index[i] == j){
                cout << dictionary[i] << " ";
            }
        }
    }
}
void checkallAnswers(char **dictionary, int min, int max, char board[]){
    char theWord[ 81];
    ifstream inStream;       // declare an input stream for my use
    int wordRow = 0;
    int originalWordRow = 0;// Row for the current word
    inStream.open( "dictionary.txt");
    assert( ! inStream.fail() );
    while ( inStream >> theWord) {
        int wordLength = (int)strlen( theWord);
        //allocate memory only of max and min lengths
        if( (min <= wordLength) && wordLength <= max) {
            strcpy( dictionary[ wordRow], theWord);
            // increment number of words
            wordRow++;
            //search for the words we brough in from dictionary in our board
            if(firstLetter(board, theWord)){
                //if found print the words
                cout << theWord << " ";
            }
            
        }
        originalWordRow++;
    }
    
}




int main()

{
    //toggle counter to see when the timer is on or off
    int toggle = 0;
    time_t start = time(NULL);  //time_t is a type just like int
    displayIdentifyingInformation();
    displayIntro();
    // initialize our dictionary
    char ** dictionary;
    // malloc and set our index so we know its a dynamic array
    int *index = new int[ NumberOfWordsInDictionary];
    for(int i = 0; i < NumberOfWordsInDictionary; i++){
        index[i] = 0;
    }
    allocateArray( dictionary);
    char theWord[ 81];
    ifstream inStream;      // declare an input stream for my use
    int wordRow = 0;
    int originalWordRow = 0;// Row for the current word
    inStream.open( "dictionary.txt");
    assert( ! inStream.fail() );
    while ( inStream >> theWord) {
        //read in only dictionary words of appropriate length
        int wordLength = (int)strlen( theWord);
        if( wordLength >= MinWordLength && wordLength <= MaxWordLength) {
            // copy word into alocated memory
            strcpy( dictionary[ wordRow], theWord);
            // increment number of words
            wordRow++;
        }
        originalWordRow++;
    }
    cout << "The dictionary total number of words is: " << originalWordRow <<  endl;
    cout << "Number of words of the right length is: " <<wordRow << "\n";
    //stary with an array that is all astericks these values will go into our board
    char board[37] = "************************************";
    //set random values to our board
    randBoard(board);
    //print this initial board
    printBoard(board);
    //set counter which will count the moves of our player
    int k = 1;
    //temporary board holds our values
    char tempBoard[37];
    //holds users input
    char userWord[17];
    //while we are under a minute ( or alternatively if timer is toggled off while player does not press x
    while( (time(NULL) - start) < 60 ){
        char userWord[MaxWordLength];
        cout << k << ". Please enter word: ";
        //take in user input
        cin >> userWord;
        //if x then exit
        if(userWord[0] == 'x' && strlen( userWord) < 2)
        {
            return 0;
            
        }
        //if the string length is more than 2 and less than 16 OR if it is r then run next loop
        if( (strlen( userWord) > 2 || userWord[0] == 'r')){
            //points index to the result of our binary search
            *index = binarySearch(userWord, dictionary, NumberOfWordsInDictionary);
            //number of poiints for this round
            int letterCount = countLetters( userWord);
            //puts values of board into our temporary board
            for( int z = 0; z < 37; z++){
                tempBoard[z] = board[z];
            }
            //if our letters are all found and our length is either greater than two or r
            if( ((firstLetter(tempBoard, userWord) == true)) && (strlen( userWord) > 2 || userWord[0] == 'r') && *index != -1){
                cout << "words so far are: ";
                //lead us to the function that puts all word in a list
                sortAnswers( dictionary, index, userWord, NumberOfWordsInDictionary);
                cout << "\n";
            }
            //if the recursive function returned false then the word wasnt found on our board
            else if( firstLetter(tempBoard, userWord) == false ){
                cout << "Word not found on board\n";
            }
            //if the word is not r and the binary results were -1 then word was not found in dictionary
            else if( strlen(userWord) != 1 && *index == -1){
                cout << "was not found in the dictionary.\n";
            }
            //either print original board or print new board if user entered r
            resetBoard( board, userWord, board);
        }
        //if worrd is less than 3 and is not r then it must not be appropriate length
        if(  (strlen( userWord) < 3) && (userWord[0] != 't' && userWord[0] != 'r'))
        {
            cout << " Sorry word is not appropriate length. Please enter a word that is atleast 3 characters and less than 16 characters.\n";
        }
        //if toggle has been pressed once then it is off
        if(toggle%2 != 0){
            start = time(NULL);
        }
        //if togge has been pressed twice or 0 times then it is on
        if(toggle%2 == 0){
            cout << 60 - (time(NULL) - start)
            << " seconds remaining"//total time elapsed
            << endl;
        }
        //if the user entered t then toggles counter goes up but if they enter s then
        //function to show all answers is called (only after taking in the min and max ofcourse
        if( strlen(userWord) < 2){
            if(userWord[0] == 't'){
                toggle++;
            }
            if( userWord[0] == 's'){
                cout << " enter min\n";
                int userInputmin;
                cin >> userInputmin;
                cout << "enter max\n";
                int userInputmax;
                cin >> userInputmax;
                checkallAnswers(dictionary, userInputmin, userInputmax, board);
                break;
                }
        }
        //increase our counter so we know what move we are on
           k++;
    }
    return 0;
}
