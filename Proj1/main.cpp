// Compile using g++ main.cpp, run using ./a.out
#include"Board.cpp"
int main(int argc, char** argv){
    Board start("354210896");
    cout << start;
    int rq = 0;
    while(rq != 9){
        rq = 0;
        cout << "1-left, 2-up, 3-right, 4-down, 9-quit:";
        cin >> rq;
        switch(rq){
            case 1:
                start = Board(start.moveLeft());
                break;
            case 2:
                start = Board(start.moveUp());
                break;
            case 3:
                start = Board(start.moveRight());
                break;
            case 4:
                start = Board(start.moveDown());
                break;
            default:
                break;
        } 
        if(rq == 9) break;
        cout << start;
    }

    return 0;
}