#ifndef BOARD 
#define BOARD

#include<iostream> // https://www.youtube.com/watch?v=kfVsfOSbJY0
#include<string>
#include<queue>
// Representation: Every board could become a string, and vice versa
// 012
// 345 <- these are the indices
// 678

// And the string would look like 354210896


using namespace std;

class Board{
public:
    // don't have to worry about rule of 3/5/7 as size is const and internal
    int spots[3][3] = {{3,5,4}, {2,1,0}, {8,9,6}};
    Board(string start = "123456780"){
        for(int i = 0; i < 9; i++){
            int r = i / 3;
            int c = i % 3;
            spots[r][c] = start[i] - '0';
        }
    }

    string getString(){
        string ans;
        for(int i = 0; i < 9; i++){
            ans += (char)('0' + spots[i/3][i%3]);
        }
        return ans;
    }

    string moveLeft(){ // return the state of the board after moving the blank (0) left. Do nothing if impossible
        int r0 = -1;
        int c0 = -1;
        // find row, col of the free
        for(int r = 0; r < 3; r++){
            for(int c = 0; c < 3; c++){
                if(spots[r][c] == 0){
                    r0 = r;
                    c0 = c;
                    break;
                }
            }
        }

        if(c0 == 0) return getString(); // moveLeft is impossible

        int tmp = spots[r0][c0-1];
        spots[r0][c0-1] = 0;
        spots[r0][c0] = tmp;
        string ans = getString();
        spots[r0][c0] = 0;
        spots[r0][c0-1] = tmp;
        return ans;
    }

    string moveRight(){ // return the state of the board after moving the blank (0) right. Do nothing if impossible
        int r0 = -1;
        int c0 = -1;
        // find row, col of the free
        for(int r = 0; r < 3; r++){
            for(int c = 0; c < 3; c++){
                if(spots[r][c] == 0){
                    r0 = r;
                    c0 = c;
                    break;
                }
            }
        }

        if(c0 == 2) return getString(); // moveRight is impossible

        int tmp = spots[r0][c0+1];
        spots[r0][c0+1] = 0;
        spots[r0][c0] = tmp;
        string ans = getString();
        spots[r0][c0] = 0;
        spots[r0][c0+1] = tmp;
        return ans;
    }
    string moveUp(){ // return the state of the board after moving the blank (0) up. Do nothing if impossible
        int r0 = -1;
        int c0 = -1;
        // find row, col of the free
        for(int r = 0; r < 3; r++){
            for(int c = 0; c < 3; c++){
                if(spots[r][c] == 0){
                    r0 = r;
                    c0 = c;
                    break;
                }
            }
        }

        if(r0 == 0) return getString(); // moveLeft is impossible

        int tmp = spots[r0-1][c0];
        spots[r0-1][c0] = 0;
        spots[r0][c0] = tmp;
        string ans = getString();
        spots[r0][c0] = 0;
        spots[r0-1][c0] = tmp;
        return ans;
    }
    string moveDown(){ // return the state of the board after moving the blank (0) down. Do nothing if impossible
        int r0 = -1;
        int c0 = -1;
        // find row, col of the free
        for(int r = 0; r < 3; r++){
            for(int c = 0; c < 3; c++){
                if(spots[r][c] == 0){
                    r0 = r;
                    c0 = c;
                    break;
                }
            }
        }

        if(r0 == 2) return getString(); // moveDown is impossible

        int tmp = spots[r0+1][c0];
        spots[r0+1][c0] = 0;
        spots[r0][c0] = tmp;
        string ans = getString();
        spots[r0][c0] = 0;
        spots[r0+1][c0] = tmp;
        return ans;
    }

};

ostream& operator<<(ostream& l, Board& b){
    l << endl;
    for(int r = 0; r < 3; r++){
        for(int c = 0; c < 3; c++) l << b.spots[r][c] << ' ';
        l << endl;
    }
    l << endl;
    return l;
}

#endif