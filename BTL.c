#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
//change for new branch
#pragma warning(disable:4996)

#define MAX_SIZE 15

const char HORZ = 196;
const char VERT = 179;
const char TL = 218;
const char TM = 194;
const char TR = 191;
const char BL = 192;
const char BM = 193;
const char BR = 217;
const int numW = 3;             // Width for writing out an integer
const int charW = 1;             // Width for writing out a character
const int numPerLine = 15;
const char VERT_START = 195;
const char VERT_END = 180;
const char VERT_MID = 197;
const char* inputCommand = "Previous move/Next move/Stop [p/n/s]: ";
const char* endOfHistory = "This is the end of the match.\nPrevious move/Next move/Stop [p/n/s]: ";
const char* startOfGame = "This is the start of the match.\nPrevious move/Next move/Stop [p/n/s]: ";
const char* invalidInput = "Illegal input, please try again: ";

enum Stone { NA, X, O };

struct Move {
    int row;
    int col;
    enum Stone stone;
}move;


static char* lineString(char left, char mid, char right, char horz, int wcell, int ncell);
bool makeMove(enum Stone board[][15], int size, char* playerMove, bool isFirstPlayerTurn);
bool hasWon(enum Stone board[][15], int size, bool isFirstPlayerTurn);
void displayHistory(char* history, int numOfMoves);
void startGame();
void displayBoard(enum Stone arr[][15], int size);
void displayBoardSimple(enum Stone arr[][15], int size);
void XoaKhoangTrangThua(char *s);
void XoaKyTu(char *s, int vitrixoa);
int tinh_so_hang(char *s);
int tinh_kitu_cot(char *s);
int kiemtra_dinhdang_hang_cot(char *s);
int XuLiChuoi(char *s);
bool KiemTraThangHangNgang(enum Stone board[][15], int size, bool isFirstPlayerTurn);
bool KiemTraThangHangDoc(enum Stone board[][15], int size, bool isFirstPlayerTurn);
bool KiemTraThangCheoChinh(enum Stone board[][15], int size, bool isFirstPlayerTurn);
bool KiemTraThangCheoPhu(enum Stone board[][15], int size, bool isFirstPlayerTurn);
void XuLiChuoiHistory(char *s, int numOfMove, int row[225], int col[225]);
long long power(long long x, long long y);

int main()
{
    printf("Welcome to Gomoku!\n");
    printf("1. Play game\n");
    printf("2. History\n");
    printf("3. Exit\n");
    printf("Please select mode [1/2/3]: ");
    int mode;
    while (true) {
        scanf("%d", &mode);
        if (mode == 1) {
            startGame();
            return 0;
        }
        else if (mode == 2) {
            int numOfMoves;
            printf("Please enter number of moves: ");
            scanf("%d", &numOfMoves);
            char history[700];
            printf("Please enter history: ");
            scanf("%s", history);
            displayHistory(history, numOfMoves);
            return 0;
        }
        else if (mode == 3) {
            return 0;
        }
        else {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            printf("Invalid mode, please try again: ");
        }
    }
    return 0;
}
//hang_cot

bool makeMove(enum Stone board[][15], int size, char* playerMove, bool isFirstPlayerTurn) {
    //BEGIN TODO
    
    if(XuLiChuoi(playerMove)==1 && board[15-tinh_so_hang(playerMove)][tinh_kitu_cot(playerMove)-1]==NA){
        if(isFirstPlayerTurn){
            board[15-tinh_so_hang(playerMove)][tinh_kitu_cot(playerMove)-1]=X;
        }else{
            board[15-tinh_so_hang(playerMove)][tinh_kitu_cot(playerMove)-1]=O;
        }
        move.row = 15-tinh_so_hang(playerMove); //luu vi tri dong vua danh
        move.col = tinh_kitu_cot(playerMove)-1; //luu vi tri cot vua danh
        //printf("test"); 
        return true;
    }else{
        return false;
    }
    return 0;
    //END TODO
}

bool haasWon(enum Stone board[][15], int size, bool isFirstPlayerTurn) {
    //BEGIN TODO
    if(KiemTraThangHangDoc(board, size, isFirstPlayerTurn) || KiemTraThangHangNgang(board, size, isFirstPlayerTurn) || KiemTraThangCheoChinh(board, size, isFirstPlayerTurn) || KiemTraThangCheoPhu(board, size, isFirstPlayerTurn)){
        return true;
    }else{
        return false;
    }
    //END TODO
}

void displayHistory(char* history, int numOfMoves) {
    //BEGIN TODO
    int row[225]; //12a13c15c... row[12, 13 15...]
    int col[225]; // a c c 
    XuLiChuoiHistory(history, numOfMoves, row, col);
    enum Stone game[15][15];
    for (int i = 0; i < MAX_SIZE; i++) {
        for (int j = 0; j < MAX_SIZE; j++) {
            game[i][j] = NA;
        }
    }
    displayBoard(game, MAX_SIZE);
    char input[10];
    printf(inputCommand); 
    int count=0;
    while(1){
        scanf("%s", input); 
        if (strcmp(input, "n") == 0){ 
            count++;
            if(count>numOfMoves){
                printf(endOfHistory);
                count=numOfMoves;
            }else{
                //hien thi nuoc co tiep theo
                if(count%2!=0){
                    game[15-row[count-1]][col[count-1]]=X; //tuy vao count x
                }else{
                    game[15-row[count-1]][col[count-1]]=O; //tuy vao count
                }
                displayBoard(game, MAX_SIZE);
                printf(inputCommand); 
            }
        }else if (strcmp(input, "p") == 0) {
            count--;
            if(count<0){
                printf(startOfGame);
                count=0;
            }else{
                //hien thi nuoc co truoc do
                game[15-row[count]][col[count]]=NA;
                displayBoard(game, MAX_SIZE);
                printf(inputCommand); 
            }
            
        }else if(strcmp(input, "s") == 0){
            //stop
            return;
        }else{
            printf(invalidInput);
        }
    }

    //END TODO
}

void startGame() {
    enum Stone game[15][15];
    for (int i = 0; i < MAX_SIZE; i++) {
        for (int j = 0; j < MAX_SIZE; j++) {
            game[i][j] = NA;
        }
    }
    displayBoard(game, MAX_SIZE);
    char playerMove[50]; 
    bool player1Turn = true;
    printf("Player 1 turn: "); 
    while (true) {
        scanf("%s", playerMove);
        if (strcmp(playerMove, "ff") == 0) {
            printf("%s", ((player1Turn) ? "Player 2 won " : "Player 1 won "));
            break;
        }
        else if (makeMove(game, MAX_SIZE, playerMove, player1Turn)) {

            if (hasWon(game, MAX_SIZE, player1Turn)) {
                displayBoard(game, MAX_SIZE);
                printf("%s", ((player1Turn) ? "Player 1 won " : "Player 2 won "));
                return;
            }
            player1Turn = !player1Turn;
            displayBoard(game, MAX_SIZE);
            printf("%s", ((player1Turn) ? "Player 1 turn: " : "Player 2 turn: "));
        }
        else {
            printf("Illegal move, please try again: ");
        }
    }
}

static char* lineString(char left, char mid, char right, char horz, int wcell, int ncell) {
    static char result[100];
    strcpy(result, "");
    char cell[10];
    for (int i = 0; i < wcell; i++) {
        cell[i] = horz;
    }
    cell[wcell] = '\0';
    strncat(result, &left, 1);
    char cellMid[20];
    strcpy(cellMid, cell);
    strncat(cellMid, &mid, 1);
    for (int i = 0; i < ncell - 1; i++)
        strcat(result, cellMid);
    char cellRight[20];
    strcpy(cellRight, cell);
    strncat(cellRight, &right, 1);
    strcat(result, cellRight);
    return result;
}
void displayBoard(enum Stone arr[][15], int size) {
    //UPPERLINE
    printf("   ");
    for (int i = 0; i < size; i++) {
        printf("  %c ", (char)(i + 'a'));
    }
    printf("\n");
    printf("   %s\n", lineString(TL, TM, TR, HORZ, 3, numPerLine));

    //MIDDLE
    for (int i = 0; i < size; i++) {
        printf("%2d %c", size - i, VERT);
        for (int j = 0; j < size; j++) {
            if (arr[i][j] == NA) printf("   %c", VERT);
            if (arr[i][j] == X) printf(" X %c", VERT);
            if (arr[i][j] == O) printf(" O %c", VERT);
        }
        printf("\n");
        if (i != size - 1) printf("   %s\n", lineString(VERT_START, VERT_MID, VERT_END, HORZ, 3, numPerLine));
    }

    //UNDERLINE
    printf("   %s\n", lineString(BL, BM, BR, HORZ, 3, numPerLine));
}

void displayBoardSimple(enum Stone arr[][15], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%d", arr[i][j]);
        }
    }
    printf("\n");
}

void XoaKhoangTrangThua(char *s){
    int length=strlen(s);
    for(int i=0;i<length;i++){
        if((s[i]==' '&&s[i+1]==' ')||(s[i]==' '&&s[i+1]!=' ')){
            XoaKyTu(s, i);
            i--;
            length--; 
        }
    }
    if(s[0]==' '){
        XoaKyTu(s, 0);
        length--;
    }
    if(s[length-1]==' '){
        XoaKyTu(s, length-1);
        length--;
    }
}

void XoaKyTu(char *s, int vitrixoa){
    for(int i=vitrixoa+1;i<strlen(s);i++){
        s[i-1]=s[i];
    }
    s[strlen(s)-1]='\0';
}
/*
Tính số đầu của chuỗi. Ví dụ
s="456ty" => tinh_so_hang(s)=456
s="7h" => tinh_so_hang(s)=7
s="fx98" => tinh_so_hang(s)=-1 (không hợp lệ)
*/

//56a
int tinh_so_hang(char *s){
    int length = strlen(s); //12c
    int so=0;
    for(int i=0;i<length;i++){
        if((s[i]>='0' && s[i]<='9') && (s[i+1]>='a' && s[i+1]<='z')){
            for(int j=0;j<=i;j++){
                so += (s[j]-48)*power(10, i-j);
            }
            return so;
        }
    }
    return -1;
}
/*
Tính số kí tự của chuỗi rồi chuyển về dạng số
a=1, b=2, c=3, ... ,o=15
Ví dụ
s="798a" => tinh_kitu_cot(s)=0 (do a xem là 1)
s="7h" => tinh_kitu_cot(s)= 7 (do h xem là 8)
s="78aa" => tinh_kitu_cot(s)=-1 (không hợp lệ)
*/
//6c
int tinh_kitu_cot(char *s){
    int length = strlen(s);
    int kitu=0; //10c
    for(int i=0;i<length;i++){
        if((s[i]>='0' && s[i]<='9') && (s[i+1]>='a' && s[i+1]<='z')){
            if(s[i+2]=='\0'){ 
                kitu = s[i+1]-96;
            }else{
                return -1;
            }
            return kitu;
        }
    }
    return -1;
}

/*
hàm này kiểm tra xem có đúng định dạng chưa
tức là dạng (hàng_cột) hay (số_kí tự)
ví dụ: nếu có dạng "1121dudhudfh" thì hàm trả về 1 (đúng dạng [số trước, kí tự sau])
nếu có dạng "hdf94390" thì hàm trả về 0 (không đúng dạng [số trước, kí tự sau])
*/
int kiemtra_dinhdang_hang_cot(char *s){ 
    int length = strlen(s);
    if(s[0]>='1' && s[0]<='9'){
        return 1;
    }else{ 
        return 0;
    }
}
//5h
int XuLiChuoi(char *s){
    int length = strlen(s);
    if(kiemtra_dinhdang_hang_cot(s) && (tinh_so_hang(s) != -1) && (tinh_kitu_cot(s) != -1) && (tinh_so_hang(s)>=1 && tinh_so_hang(s)<=15) && (tinh_kitu_cot(s)>=1 && tinh_kitu_cot(s)<=15)){
        return 1;
    }else{
        return 0;
    }
}

bool KiemTraThangHangNgang(enum Stone board[][15], int size, bool isFirstPlayerTurn){
    int dem_trai=0, dem_phai=0;
    int chan_trai=-1, chan_phai=-1;

    if(isFirstPlayerTurn){ //luot choi cua X
        if(move.col==0){
            //xet qua phai
            for(int j=move.col+1;j<size;j++){
                if(board[move.row][j]==X){
                    dem_phai++;
                }else{
                    chan_phai=j;
                    break;
                }
            }
        }else if(move.col==size-1){
            //xet qua trai
            for(int j=move.col-1;j>=0;j--){
                if(board[move.row][j]==X){
                    dem_trai++;
                }else{
                    chan_trai=j;
                    break;
                }
            }
        }else{
            //xet qua trai
            for(int j=move.col-1;j>=0;j--){
                if(board[move.row][j]==X){
                    dem_trai++;
                }else{
                    chan_trai=j;
                    break;
                }
            }
            //xet qua phai
            for(int j=move.col+1;j<size;j++){
                if(board[move.row][j]==X){
                    dem_phai++;
                }else{
                    chan_phai=j;
                    break;
                }
            }
        }
        int dem=dem_trai+dem_phai+1; 
        if(dem!=5){
            return false;
        }else{ //dem=5
            if(chan_trai==-1){ //khong bi chan trai (khong can xet them chan phai)
                return true;
            }else{ 
                if(board[move.row][chan_trai]==NA){ //bi chan trai nhung la NA
                    return true;
                }else{ // bi chan trai khong phai NA (chac chan la O)
                    //xet chan phai
                    if(chan_phai==-1){ //khong bi chan phai
                        return true;
                    }else{ 
                        if(board[move.row][chan_phai]==NA){ //bi chan phai nhung la NA
                            return true;
                        }else{
                            return false;
                        }
                    }
                }
            }
        }

    }else{ //luot choi cua O
        if(move.col==0){
            //xet qua phai
            for(int j=move.col+1;j<size;j++){
                if(board[move.row][j]==O){
                    dem_phai++;
                }else{
                    chan_phai=j;
                    break;
                }
            }
        }else if(move.col==size-1){
            //xet qua trai
            for(int j=move.col-1;j>=0;j--){
                if(board[move.row][j]==O){
                    dem_trai++;
                }else{
                    chan_trai=j;
                    break;
                }
            }
        }else{
            //xet qua trai
            for(int j=move.col-1;j>=0;j--){
                if(board[move.row][j]==O){
                    dem_trai++;
                }else{
                    chan_trai=j;
                    break;
                }
            }
            //xet qua phai
            for(int j=move.col+1;j<size;j++){
                if(board[move.row][j]==O){
                    dem_phai++;
                }else{
                    chan_phai=j;
                    break;
                }
            }
        }
        int dem=dem_trai+dem_phai+1; 
        if(dem!=5){
            return false;
        }else{ //dem=5
            if(chan_trai==-1){ //khong bi chan trai (khong can xet them chan phai)
                return true;
            }else{
                if(board[move.row][chan_trai]==NA){ //bi chan trai nhung la NA
                    return true;
                }else{ // bi chan trai khong phai NA (chac chan la X)
                    //xet chan phai
                    if(chan_phai==-1){ //khong bi chan phai
                        return true;
                    }else{ 
                        if(board[move.row][chan_phai]==NA){ //bi chan phai nhung la NA
                            return true;
                        }else{
                            return false;
                        }
                    }
                }
            }
        }
    }
}

bool KiemTraThangHangDoc(enum Stone board[][15], int size, bool isFirstPlayerTurn){
    int dem_tren=0, dem_duoi=0;
    int chan_tren=-1, chan_duoi=-1;

    if(isFirstPlayerTurn){ //luot choi cua X
        if(move.row==0){
            //xet xuong duoi
            for(int i=move.row+1;i<size;i++){
                if(board[i][move.col]==X){
                    dem_duoi++;
                }else{
                    chan_duoi=i;
                    break;
                }
            }
        }else if(move.row==size-1){
            //xet len tren
            for(int i=move.row-1;i>=0;i--){
                if(board[i][move.col]==X){
                    dem_tren++;
                }else{
                    chan_tren=i;
                    break;
                }
            }
        }else{
            //xet len tren
            for(int i=move.row-1;i>=0;i--){
                if(board[i][move.col]==X){
                    dem_tren++;
                }else{
                    chan_tren=i;
                    break;
                }
            }
            //xet xuong duoi
            for(int i=move.row+1;i<size;i++){
                if(board[i][move.col]==X){
                    dem_duoi++;
                }else{
                    chan_duoi=i;
                    break;
                }
            }
        }
        int dem=dem_tren+dem_duoi+1; 
        if(dem!=5){
            return false;
        }else{ //dem=5
            if(chan_tren==-1){ //khong bi chan tren (khong can xet them chan duoi)
                return true;
            }else{
                if(board[chan_tren][move.col]==NA){ //bi chan tren nhung la NA
                    return true;
                }else{ // bi chan tren khong phai NA (chac chan la O)
                    //xet chan duoi
                    if(chan_duoi==-1){ //khong bi chan duoi
                        return true;
                    }else{ 
                        if(board[chan_duoi][move.col]==NA){ //bi chan duoi nhung la NA
                            return true;
                        }else{
                            return false;
                        }
                    }
                }
            }
        }

    }else{ //luot choi cua O
        if(move.row==0){
            //xet xuong duoi
            for(int i=move.row+1;i<size;i++){
                if(board[i][move.col]==O){
                    dem_duoi++;
                }else{
                    chan_duoi=i;
                    break;
                }
            }
        }else if(move.row==size-1){
            //xet len tren
            for(int i=move.row-1;i>=0;i--){
                if(board[i][move.col]==O){
                    dem_tren++;
                }else{
                    chan_tren=i;
                    break;
                }
            }
        }else{
            //xet len tren
            for(int i=move.row-1;i>=0;i--){
                if(board[i][move.col]==O){
                    dem_tren++;
                }else{
                    chan_tren=i;
                    break;
                }
            }
            //xet xuong duoi
            for(int i=move.row+1;i<size;i++){
                if(board[i][move.col]==O){
                    dem_duoi++;
                }else{
                    chan_duoi=i;
                    break;
                }
            }
        }
        int dem=dem_tren+dem_duoi+1; 
        if(dem!=5){
            return false;
        }else{ //dem=5
            if(chan_tren==-1){ //khong bi chan tren (khong can xet them chan duoi)
                return true;
            }else{
                if(board[chan_tren][move.col]==NA){ //bi chan tren nhung la NA
                    return true;
                }else{ // bi chan tren khong phai NA (chac chan la O)
                    //xet chan duoi
                    if(chan_duoi==-1){ //khong bi chan duoi
                        return true;
                    }else{ 
                        if(board[chan_duoi][move.col]==NA){ //bi chan duoi nhung la NA
                            return true;
                        }else{
                            return false;
                        }
                    }
                }
            }
        }
    }
}

bool KiemTraThangCheoChinh(enum Stone board[][15], int size, bool isFirstPlayerTurn){
    int dem_trai=0, dem_phai=0;
    int chan_trai1=-1, chan_trai2=-1, chan_phai1=-1, chan_phai2=-1;//1: row ; 2: col
    int i, j;
    if(isFirstPlayerTurn){ //luot cua X
        if(move.col==0 || move.row==0){
            //xet qua phai , xuong duoi (i tang, j tang )   
            i=move.row+1;
            j=move.col+1;
            while(1){
                if(board[i][j]==X){
                    dem_phai++;
                }else{
                    chan_phai1=i;
                    chan_phai2=j;
                    break;
                }
                i++;
                j++;
                if(i>size-1 || j>size-1){
                    break;
                }
            }
        }else if(move.col==size-1 || move.row==size-1){
            //xet qua trai, len tren (i giam, j giam )   
            i=move.row-1;
            j=move.col-1;
            while(1){
                if(board[i][j]==X){
                    dem_trai++;
                }else{
                    chan_trai1=i;
                    chan_trai2=j;
                    break;
                }
                i--;
                j--;
                if(i<0 | j<0){
                    break;
                }
            }
        }else{
            //xet qua trai, len tren (i giam, j giam )   
            i=move.row-1;
            j=move.col-1;
            while(1){
                if(board[i][j]==X){
                    dem_trai++;
                }else{
                    chan_trai1=i;
                    chan_trai2=j;
                    break;
                }
                i--;
                j--;
                if(i<0 | j<0){
                    break;
                }
            }

            //xet qua phai , xuong duoi (i tang, j tang )   
            i=move.row+1;
            j=move.col+1;
            while(1){
                if(board[i][j]==X){
                    dem_phai++;
                }else{
                    chan_phai1=i;
                    chan_phai2=j;
                    break;
                }
                i++;
                j++;
                if(i>size-1 || j>size-1){
                    break;
                }
            }
        }
        int dem=dem_trai+dem_phai+1;
        if(dem!=5){
            return false;
        }else{ //dem=5
            if(chan_trai1==-1 || chan_trai2==-1){ //khong bi chan trai (khong can xet them chan phai)
                return true;
            }else{
                if(board[chan_trai1][chan_trai2]==NA){ //bi chan trai nhung la NA
                    return true;
                }else{ // bi chan trai khong phai NA (chac chan la O)
                    //xet chan phai
                    if(chan_phai1==-1||chan_phai2==-1){ //khong bi chan phai
                        return true;
                    }else{ 
                        if(board[chan_phai1][chan_phai2]==NA){ //bi chan phai nhung la NA
                            return true;
                        }else{
                            return false;
                        }
                    }
                }
            }
        }

    }else{ //luot cua O
        if(move.col==0 || move.row==0){
            //xet qua phai , xuong duoi (i tang, j tang )   
            i=move.row+1;
            j=move.col+1;
            while(1){
                if(board[i][j]==O){
                    dem_phai++;
                }else{
                    chan_phai1=i;
                    chan_phai2=j;
                    break;
                }
                i++;
                j++;
                if(i>size-1 || j>size-1){
                    break;
                }
            }
        }else if(move.col==size-1 || move.row==size-1){
            //xet qua trai, len tren (i giam, j giam )   
            i=move.row-1;
            j=move.col-1;
            while(1){
                if(board[i][j]==O){
                    dem_trai++;
                }else{
                    chan_trai1=i;
                    chan_trai2=j;
                    break;
                }
                i--;
                j--;
                if(i<0 | j<0){
                    break;
                }
            }
        }else{
            //xet qua trai, len tren (i giam, j giam )   
            i=move.row-1;
            j=move.col-1;
            while(1){
                if(board[i][j]==O){
                    dem_trai++;
                }else{
                    chan_trai1=i;
                    chan_trai2=j;
                    break;
                }
                i--;
                j--;
                if(i<0 | j<0){
                    break;
                }
            }

            //xet qua phai , xuong duoi (i tang, j tang )   
            i=move.row+1;
            j=move.col+1;
            while(1){
                if(board[i][j]==O){
                    dem_phai++;
                }else{
                    chan_phai1=i;
                    chan_phai2=j;
                    break;
                }
                i++;
                j++;
                if(i>size-1 || j>size-1){
                    break;
                }
            }
        }
        int dem=dem_trai+dem_phai+1;
        if(dem!=5){
            return false;
        }else{ //dem=5
            if(chan_trai1==-1 || chan_trai2==-1){ //khong bi chan trai (khong can xet them chan phai)
                return true;
            }else{
                if(board[chan_trai1][chan_trai2]==NA){ //bi chan trai nhung la NA
                    return true;
                }else{ // bi chan trai khong phai NA (chac chan la X)
                    //xet chan phai
                    if(chan_phai1==-1||chan_phai2==-1){ //khong bi chan phai
                        return true;
                    }else{ 
                        if(board[chan_phai1][chan_phai2]==NA){ //bi chan phai nhung la NA
                            return true;
                        }else{
                            return false;
                        }
                    }
                }
            }
        }
    }
}

bool KiemTraThangCheoPhu(enum Stone board[][15], int size, bool isFirstPlayerTurn){
    int dem_trai=0, dem_phai=0;
    int chan_trai1=-1, chan_trai2=-1, chan_phai1=-1, chan_phai2=-1;//1: row ; 2: col
    int i, j;
    if(isFirstPlayerTurn){ //luot cua X
        if(move.col==0 || move.row==size-1){
            //xet qua phai , len tren (i giam, j tang )   
            i=move.row-1;
            j=move.col+1;
            while(1){
                if(board[i][j]==X){
                    dem_phai++;
                }else{
                    chan_phai1=i;
                    chan_phai2=j;
                    break;
                }
                i--;
                j++;
                if(i<0 || j>size-1){
                    break;
                }
            }
        }else if(move.col==size-1 || move.row==0){
            //xet qua trai, xuong duoi (i tang, j giam )   
            i=move.row+1;
            j=move.col-1;
            while(1){
                if(board[i][j]==X){
                    dem_trai++;
                }else{
                    chan_trai1=i;
                    chan_trai2=j;
                    break;
                }
                i++;
                j--;
                if(i>size-1| j<0){
                    break;
                }
            }
        }else{
            //xet qua trai, xuong duoi (i tang, j giam )   
            i=move.row+1;
            j=move.col-1;
            while(1){
                if(board[i][j]==X){
                    dem_trai++;
                }else{
                    chan_trai1=i;
                    chan_trai2=j;
                    break;
                }
                i++;
                j--;
                if(i>size-1| j<0){
                    break;
                }
            }

            //xet qua phai , len tren (i giam, j tang )   
            i=move.row-1;
            j=move.col+1;
            while(1){
                if(board[i][j]==X){
                    dem_phai++;
                }else{
                    chan_phai1=i;
                    chan_phai2=j;
                    break;
                }
                i--;
                j++;
                if(i<0 || j>size-1){
                    break;
                }
            }
        }
        int dem=dem_trai+dem_phai+1;
        if(dem!=5){
            return false;
        }else{ //dem=5
            if(chan_trai1==-1 || chan_trai2==-1){ //khong bi chan trai (khong can xet them chan phai)
                return true;
            }else{
                if(board[chan_trai1][chan_trai2]==NA){ //bi chan trai nhung la NA
                    return true;
                }else{ // bi chan trai khong phai NA (chac chan la O)
                    //xet chan phai
                    if(chan_phai1==-1||chan_phai2==-1){ //khong bi chan phai
                        return true;
                    }else{ 
                        if(board[chan_phai1][chan_phai2]==NA){ //bi chan phai nhung la NA
                            return true;
                        }else{
                            return false;
                        }
                    }
                }
            }
        }

    }else{ //luot cua O
        if(move.col==0 || move.row==size-1){
            //xet qua phai , len tren (i giam, j tang )   
            i=move.row-1;
            j=move.col+1;
            while(1){
                if(board[i][j]==O){
                    dem_phai++;
                }else{
                    chan_phai1=i;
                    chan_phai2=j;
                    break;
                }
                i--;
                j++;
                if(i<0 || j>size-1){
                    break;
                }
            }
        }else if(move.col==size-1 || move.row==0){
            //xet qua trai, xuong duoi (i tang, j giam )   
            i=move.row+1;
            j=move.col-1;
            while(1){
                if(board[i][j]==O){
                    dem_trai++;
                }else{
                    chan_trai1=i;
                    chan_trai2=j;
                    break;
                }
                i++;
                j--;
                if(i>size-1| j<0){
                    break;
                }
            }
        }else{
            //xet qua trai, xuong duoi (i tang, j giam )   
            i=move.row+1;
            j=move.col-1;
            while(1){
                if(board[i][j]==O){
                    dem_trai++;
                }else{
                    chan_trai1=i;
                    chan_trai2=j;
                    break;
                }
                i++;
                j--;
                if(i>size-1| j<0){
                    break;
                }
            }

            //xet qua phai , len tren (i giam, j tang )   
            i=move.row-1;
            j=move.col+1;
            while(1){
                if(board[i][j]==O){
                    dem_phai++;
                }else{
                    chan_phai1=i;
                    chan_phai2=j;
                    break;
                }
                i--;
                j++;
                if(i<0 || j>size-1){
                    break;
                }
            }
        }
        int dem=dem_trai+dem_phai+1;
        if(dem!=5){
            return false;
        }else{ //dem=5
            if(chan_trai1==-1 || chan_trai2==-1){ //khong bi chan trai (khong can xet them chan phai)
                return true;
            }else{
                if(board[chan_trai1][chan_trai2]==NA){ //bi chan trai nhung la NA
                    return true;
                }else{ // bi chan trai khong phai NA (chac chan la O)
                    //xet chan phai
                    if(chan_phai1==-1||chan_phai2==-1){ //khong bi chan phai
                        return true;
                    }else{ 
                        if(board[chan_phai1][chan_phai2]==NA){ //bi chan phai nhung la NA
                            return true;
                        }else{
                            return false;
                        }
                    }
                }
            }
        }
    }
}

void XuLiChuoiHistory(char *s, int numOfMove, int row[225], int col[225]){
    int length=strlen(s);
    int k=0, idx=0;
    for(int i=0;i<numOfMove;i++){
        row[i]=0;
        col[i]=0;
    }//10o
    for(int i=0;i<length;i++){
        if((s[i]>='0'&&s[i]<='9') &&(s[i+1]>='a'&&s[i+1]<='z')){
            for(int j=k;j<=i;j++){
                row[idx] += (s[j]-48)*power(10, i-j);
            }
            col[idx]=s[i+1]-97;
            idx++;
            k=i+2;
            i++;
        }
    }
}
long long power(long long x, long long y){
    long long result = 1;
    for(int i = 1; i <= y; i++) {
        result *= x;
    }
    return result;
}