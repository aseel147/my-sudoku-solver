
#define SIZE 8


void Encryption();
void ROL_RIGHT(char word[20]);
void  Plus3(char word[20]);
void display(char board[][SIZE]);
int valid_moves(char board[][SIZE], int moves[][SIZE], char player);
void make_move(char board[][SIZE], int row, int col, char player);
void computer_move(char board[][SIZE], int moves[][SIZE], char player);
int best_move(char board[][SIZE], int moves[][SIZE], char player);
int get_score(char board[][SIZE], char player);
void Reversi();
void RunProgram();
int check_pass(char pass[20]);
void PrintMenu();
void playerVsplayer(char board[][SIZE], int moves[][SIZE]);
void Swap(char word[]);
void Reverse(char word[20]);
void Encryptiontable(char word[20]);
