 #include <iostream>
 #include <string>
 #include <time.h>
 using namespace std;
 
 enum Piece { CROSS, CIRCLE, BLANK , C_CROSS} ;
 
 //Global variables
 const int WIDTH = 3;
 int moves;
 int winner;
 //Functtion prototypes
 void printBoard( Piece board[WIDTH][WIDTH] );
 void PVP (Piece board[WIDTH][WIDTH]);
 void PVC (Piece board[WIDTH][WIDTH]);
 void player1Move(Piece board[WIDTH][WIDTH]);
 void player2Move(Piece board[WIDTH][WIDTH]);
 void computerMove(Piece board[WIDTH][WIDTH]);
 void cMakeNextMove (Piece board[WIDTH][WIDTH],int & row, int & colum );
 bool checkStep(Piece board[WIDTH][WIDTH], int row, int colum);
 bool checkWin(Piece board[WIDTH][WIDTH]);
 void userManual(Piece board[WIDTH][WIDTH]);
 
 /*
    Main
 */
 int main()
    {
        // Store user answer
        string ans;
        while( ans != "n" )
        {
            //Create board
            Piece board[WIDTH][WIDTH];
            //Initialize each gird as blank
            for( int i = 0 ;  i < WIDTH ; i ++)
                for ( int j = 0; j < WIDTH ; j++)
                    board[i][j] = BLANK;
            //Reset move counter    
            moves = 0;
            //Reset winner status
            winner = 0;
            
            cout<<"Welcome to play TIC TAC TOE!\n";
            userManual(board);
            cout<<"Hope you will enjoy it!\n";
            
            cout<<"Please select game mode : \n"
                <<"1.PVP\t2.PVC\t3.Quit"<<endl;
            //Gaming mode
            int mode;
            //User should determine which mode to play, input will be reaquired again when entered an invalid answer 
            for(;;)
            {
                cin>>mode;
                if ( mode == 1)
                {
                    //Player vs player game mode
                    PVP(board);
                    break;
                }
                else if( mode == 2)
                {
                    //Player vs computer game mode
                    PVC(board);
                    break;
                }                    
                else if ( mode == 3)
                {
                    //Directly exit
                    cout<<"Thanks for playing!"<<endl;
                    
                    system("PAUSE");
                    exit(0);
                }
                else
                    cout<<"Invalid mode, please choose again: ";
            }
            cout<<"Gamer over"<<endl;
            
            //Check who is the winner
            switch (winner)
            {
                case 0 : cout <<"Draw game!"<<endl;break;
                case 1 : cout << "The winner is Player1!"<<endl;break;
                case 2 : cout << "The winner is Player2!"<<endl;break;
                case 3 : cout << "The winner is Computer!"<<endl;break;
            }
            
            //Check if player want to play again.
            cout<<"Would you like to play again?(y/n)";
            cin>>ans;
        }
        
        cout<<"Thanks for playing!"<<endl;
        system("PAUSE");
        return 0;
    }
/**
        userManual A user manual for those who need it
        @param board a 2d board filled with pieces
*/
    void userManual(Piece board[WIDTH][WIDTH])
    {
        string a;
        cout<<"Would you like to read user manual? y/n"<<endl;
        cin>>a;
        for(;;)
            {
                if ( a == "y")
                {
                    cout<<"A TIC TAC TOE board will be like this: \n";
                    printBoard(board);
                    cout<<"Any player who get three same pieces in a row/colum/diagonal will become the winner!\n";
                    cout<<"You can choose to play with other player(like, your friend) or play against computer!\n";
                    cout<<"You might be asked to choose which row(0~2) or colum(0~2) to put your piece!\n";
                    break;
                }
                else if(a == "n")
                    break;
                else
                {
                    cout<<"Invalid input, manual skipped !"<<endl;
                    break;
                }
                
                    
                    
            }
        
        
    }
    
    
/**
        PVP A gaming mode of player vs player.
        @param board a 2d board filled with pieces
    */
    void PVP (Piece board[WIDTH][WIDTH])
    {
        for(;;)
        {
            //Player1 makes the first move
            player1Move(board);
            //Draw the board after  move
            printBoard(board);
            //If there is a winner, exit
            if(checkWin(board))
                break;
            
            player2Move(board); 
            printBoard(board);
            if(checkWin(board))
                break;
            //If total moves reach the limit, exit loop
            if(moves>=WIDTH*WIDTH)
               break;
        }
    }
    
/**
        PVC A gaming mode of player vs computer.
        @param board a 2d board filled with pieces
*/
    void PVC (Piece board[WIDTH][WIDTH])
    {
        for(;;)
        {
            player1Move(board);
            printBoard(board);
            if(checkWin(board))
                break;
            
            //Computer goes the second move
            computerMove(board); 
            printBoard(board);
            if(checkWin(board))
                break;
            //If total moves reach the limit, exit loop
            if(moves>=WIDTH*WIDTH)
               break;
        }
    }
    
/**
        player1Move Player makes the move to the place that user determined
        @param board a 2d board filled with pieces
*/
    void player1Move(Piece board[WIDTH][WIDTH])
    {
        //Prompt user to make move
        int row , colum;
        cout<<"\nPlayer 1's turn!"<<endl;
        for(;moves<WIDTH*WIDTH;)
        {
            cout<<"Please enter your step to move!";
            cout<<"Which row? row =";
            cin>>row;
            //Invalid input check
            while(row > WIDTH || row < 0)
            {
                cout<<"Invalid row, enter again!\nrow =";
                cin>>row;
            }
                
            cout<<"Which colum? colum =";
            cin>>colum;
            //Invalid colum check
            while(colum > WIDTH || colum < 0)
            {
                cout<<"Invalid colum, enter again!\ncolum =";
                cin>>colum;
            }
            //Check if it is a valid move
            if(checkStep(board,row,colum))
            {
                board[row][colum] = CIRCLE;
                moves++;
                break;
            }
            else
                cout<<"Invalid move,move again!"<<endl;
        }
    
    }
/**
        player2Move Player makes the move to the place that user determined
        @param board a 2d board filled with pieces
*/
    void player2Move(Piece board[WIDTH][WIDTH])
    {
        int row , colum;
        cout<<"\nPlayer 2's turn!"<<endl;
        for(;moves<WIDTH*WIDTH;)
        {
            cout<<"Please enter your step to move!";
            cout<<"Which row? row =";
            cin>>row;
            //Invalid input check
            while(row > WIDTH || row < 0)
            {
                cout<<"Invalid row, enter again!\nrow =";
                cin>>row;
            }
                
            cout<<"Which colum? colum =";
            cin>>colum;
            //Invalid colum check
            while(colum > WIDTH || colum < 0)
            {
                cout<<"Invalid colum, enter again!\ncolum =";
                cin>>colum;
            }
            //Check if it is a valid move
            if(checkStep(board,row,colum))
            {
                board[row][colum] = CROSS;
                moves++;
                break;
            }
            else
                cout<<"Invalid move,move again!"<<endl;
        }
        
    }
    
    
/**
        computerMove computer's turn
        @param board a 2d board filled with pieces
*/
    void computerMove(Piece board[WIDTH][WIDTH])
    {
        /* initialize random seed: */
        srand ( time(NULL) );
        cout<<"\nComputers turn!"<<endl;
        for(;moves<WIDTH*WIDTH;)
        {
            int row  = rand()%3;
            int colum  = rand()%3;
            cMakeNextMove(board , row , colum );
            if(checkStep(board,row,colum))
            {
                board[row][colum] = C_CROSS;
                moves++;
                break;
            }
        }
    }
    
    
    
/**
        cMakeNextMove computer makes the move to a specefic place
        @param board a 2d board filled with pieces
        @param row determine which row should computer move
        @param colum determine which colum should computer move
*/
    void cMakeNextMove (Piece board[WIDTH][WIDTH],int & row, int & colum )
    {
        //Checke by row
        for (int i = 0 ; i < WIDTH ; i++)
        {
            if (board[0][i] == board [1][i] && board[2][i]==BLANK && board[0][i]!=BLANK)
            {
                row = 2;
                colum= i;
            }
            else if
                (board [1][i] == board[2][i] && board[0][i]==BLANK && board[1][i]!=BLANK)
            {
                row = 0;
                colum = i;
            }
            else if
                (board[0][i] == board[2][i] && board [1][i]==BLANK && board[0][i]!=BLANK)
            {
                row = 1;
                colum= i;
            }
        }
    
        //Checke by colum   
        for (int i = 0 ; i < WIDTH ; i++)
        {
                if ( board[i][0] == board [i][1] && board[i][2]==BLANK && board[i][0] != BLANK)
                {
                    row = i;
                    colum= 2;
                }
                else if 
                    (board [i][1] == board[i][2] && board[i][0]==BLANK && board[i][1] != BLANK)
                {
                    row = i;
                    colum  = 0;
                }
                else if
                    (board [i][0] == board[i][2]&& board [i][1]==BLANK && board[i][0] != BLANK)
                {
                    row = i;
                    colum = 1;
                }
                
        }
        
        //Check diagonal
        if (board[0][2] == board [1][1] && board[2][0]==BLANK && board[1][1] != BLANK)
            {
                row = 2;
                colum = 0;
            }
        else if ( board [1][1] == board[2][0] && board[0][2]==BLANK && board[1][1] != BLANK)
            {
                row = 0;
                colum = 2;
            }
        else if ( board [0][2] == board[2][0] && board [1][1]==BLANK && board[2][0] != BLANK)
            {
                row = 1;
                colum = 0;
            }
        
        //Check diagonal   
        if (board[0][0] == board [1][1] && board[2][2]==BLANK&& board[1][1] != BLANK)
            {
                row = 2;
                colum = 2;
            }
        else if ( board [1][1] == board[2][2] && board[0][0]==BLANK&& board[1][1] != BLANK)
            {
                row = 0;
                colum = 0;
            }
        else if ( board [0][0] == board[2][2] && board [1][1]==BLANK&& board[2][2] != BLANK)
            {
                row = 1;
                colum = 1;
            }
            
            
    }
    
/**
        checkStep check if Player makes the move to the place that user determined
        @param board a 2d board filled with pieces
        @param row row determined by user
        @param colum colum determied by user
        @return result of checking valid move
*/   
    bool checkStep(Piece board[WIDTH][WIDTH], int row, int colum)
    {
        if( board[row][colum] == BLANK )
            return true;
        else
            return false;
    }
    
/**
        checkWin check if there is a winner and set up the winner
        @param board a 2d board filled with pieces
    */
    bool checkWin(Piece board[WIDTH][WIDTH])
    {
        for (int i = 0 ; i < WIDTH ; i++)
        {
            if ( board[0][i] == board [1][i] && board [1][i] == board[2][i]
                &&board[0][i]!=BLANK&&board [1][i]!=BLANK&&board[2][i]!=BLANK)
            {
                switch (board[1][i])
                    {
                        case CIRCLE : winner = 1;break;
                        case CROSS : winner = 2;break;
                        case C_CROSS : winner  =3 ;break;
                        default : return false;
                    }
                return true;
            }
            
        }
        
        for (int i = 0 ; i < WIDTH ; i++)
        {
            if ( board[i][0] == board [i][1] && board [i][1] == board[i][2]
                &&board[i][0]!=BLANK && board[i][1]!=BLANK && board[i][2]!=BLANK)
            {
                switch (board[i][1])
                    {
                        case CIRCLE : winner = 1;break;
                        case CROSS : winner = 2;break;
                        case C_CROSS : winner  =3 ;break;
                        default : return false;
                    }
                return true;
            }
        }
        
        if (board[0][2] == board [1][1] && board [1][1] == board[2][0]
             &&board[0][2]!=BLANK&&board[1][1]!=BLANK&&board[2][0]!=BLANK)
        {
            switch (board[1][1])
                    {
                        case CIRCLE : winner = 1;break;
                        case CROSS : winner = 2;break;
                        case C_CROSS : winner  =3 ;break;
                    }
            return true;
        }
        else if (board[0][0] == board [1][1] && board [1][1] == board[2][2]
            &&board[0][0]!=BLANK&&board[1][1]!=BLANK&&board[2][2]!=BLANK)
        {
            switch (board[1][1])
                    {
                        case CIRCLE : winner = 1;break;
                        case CROSS : winner = 2;break;
                        case C_CROSS : winner  =3 ;break;
                    }
            return true;    
        }
        
       
        return false;
    }
/**
        printBoard print the whole board
        @param board a 2d board filled with pieces
    */
    void printBoard( Piece board[WIDTH][WIDTH] )
    {
        cout<<"\t 0   1   2 "<<" <- Colum"<<endl;
        for( int i = 0 ;  i < WIDTH ; i ++)
        {
            cout<<"\t--- --- --- "<<endl;
            cout<<"Row-"<<i<<"  |";
            for ( int j = 0; j < WIDTH ; j++)
            {
                switch(board[i][j])
                {
                    case CROSS : cout<<" X |";break;
                    case CIRCLE : cout<<" O |";break;
                    case C_CROSS : cout<<" X |";break;
                    default : cout<<"   |";break;
                }
            }
            cout<<endl;

        }
        cout<<"\t--- --- ---  "<<endl;
    }
