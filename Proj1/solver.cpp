#ifndef SOLVER
#define SOLVER

#include "Board.cpp"
#include<functional>
#include<unordered_map>
#include<stack>
#include<unordered_set>
#include<cmath>
using namespace std;
class Solver{
public:
    unordered_map<string, string> cameFrom; //key is the node, value is the prior node in the solution path

    Solver(string alg = "uniform", string state = "354210896"){
        unordered_map<string, double> gScore; // stores the distance from the start to this node, EXCEPT 0 means infinity
        unordered_set<string> inFrontier; // stores all nodes that were either explored or are to be explored
        static auto priorityLow = [](pair<double, string> l, pair<double, string> r){
            return l.first > r.first;
        };
        priority_queue<pair<double, string>, vector<pair<double, string>>, decltype( priorityLow )>  frontier(priorityLow); // the top node is {priority, state}. Low priority first


        function<double(string, double)> heuristic = [&alg](string state, double prior) {
            if (alg == "euclidean") {
                return euclideanDistance(state) + prior; // A* with Euclidean distance heuristic
            } else if (alg == "misplaced") {
                return misplacedTile(state) + prior; // A* with misplaced tile heuristic
            } else {
                return prior + 1; // Uniform cost search as fallback
            }
        };

        frontier.push({heuristic(state, 0.0), state});
        bool done = false;
        gScore[state] = 1;


        while(!done && frontier.size()){
            string state = frontier.top().second;
            double dist = gScore[state];
            frontier.pop();
            //if(inFrontier.count(state)) continue; // we have opened this node already
            inFrontier.insert(state);
            if(state == "123456780"){
                done = true;
                break;
            }

            Board puzzle(state);

            string l = puzzle.moveLeft();
            string r = puzzle.moveRight();
            string u = puzzle.moveUp();
            string d = puzzle.moveDown();

            if(!inFrontier.count(l)){
                frontier.push({ heuristic(l, dist), l   });
                inFrontier.insert(l);
                cameFrom[l] = state;
                if(gScore[l])   gScore[l] = min(gScore[l], dist + 1);
                else            gScore[l] = dist+1;
            }

            if(!inFrontier.count(r)){
                frontier.push({ heuristic(r, dist), r   });
                inFrontier.insert(r);
                cameFrom[r] = state;
                if(gScore[r])   gScore[r] = min(gScore[r], dist + 1);
                else            gScore[r] = dist+1;
            }
            if(!inFrontier.count(u)){
                frontier.push({ heuristic(u, dist), u  });
                inFrontier.insert(u);
                cameFrom[u] = state;
                if(gScore[u])   gScore[u] = min(gScore[u], dist + 1);
                else            gScore[u] = dist+1;
            }
            if(!inFrontier.count(d)){
                frontier.push({ heuristic(d, dist), d   });
                inFrontier.insert(d);
                cameFrom[d] = state;
                if(gScore[d])   gScore[d] = min(gScore[d], dist + 1);
                else            gScore[d] = dist+1;
            }

        }


        if(done) cout << "solved" << endl ;
        else cout << "unsolved" << endl;
    }

    static double euclideanDistance(const string& state, const string& goal="123456780") {
        double sum = 0.0;
        int x1, y1, x2, y2;
        for(char tile = '1'; tile <= '8'; ++tile) {
            int index1 = state.find(tile);
            int index2 = goal.find(tile);
            
            // Convert index to x, y coordinates in a 3x3 grid
            x1 = index1 % 3; y1 = index1 / 3;
            x2 = index2 % 3; y2 = index2 / 3;

            // Calculate Euclidean distance for this tile
            sum += sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
        }
        return sum;
    }

    static double misplacedTile(const string& state, const string& goal = "123456780") {
        int misplaced = 0;
        for (int i = 0; i < state.length(); i++) {
            if (state[i] != '0' && state[i] != goal[i]) {
                misplaced++;
            }
        }
        return misplaced;
    }

    void printStack(){
        cout << "-------------SOLUTION----------" << endl;
        string pos = "123456780";
        stack<string> st;
        while(cameFrom[pos] != ""){
            st.push(pos);
            pos = cameFrom[pos];
        }
        while(st.size()){
            Board out(st.top());
            cout << out;
            st.pop();
        }
    }

};

#endif