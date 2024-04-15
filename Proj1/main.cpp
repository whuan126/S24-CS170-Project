// Compile using g++ main.cpp, run using ./a.out
#include"Board.cpp"
#include"solver.cpp"
int main(int argc, char** argv){
    Board start("102463758");
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

    cout << "Welcome to 8 puzzle solver.\n";
    cout << "Enter your puzzle, use a zero to represent the blank. Enter as one string:\n";
    string initial_state;
    cin >> initial_state;

    Board start(initial_state);

    cout << "Choose the algorithm:\n";
    cout << "1 - Uniform Cost Search\n";
    cout << "2 - A* with Misplaced Tile heuristic\n";
    cout << "3 - A* with Euclidean distance heuristic\n";
    int choice;
    cin >> choice;

    string algorithm = "uniform"; // default
    if (choice == 2) {
        algorithm = "misplaced";
    } else if (choice == 3) {
        algorithm = "euclidean";
    }

    Solver question(algorithm, start.getString());
    
    question.printStack();

    return 0;
}