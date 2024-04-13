#ifndef SOLVER
#define SOLVER

#include "Board.cpp"
#include<functional>
#include<unordered_map>
#include<stack>
#include<unordered_set>

using namespace std;
class Solver{
public:
    unordered_map<string, string> cameFrom; //key is the node, value is the prior node in the solution path

    Solver(string alg = "uniform", string state = "354210896"){

        unordered_set<string> inFrontier; // stores all nodes that were either explored or are to be explored
        static auto priorityLow = [](pair<double, string> l, pair<double, string> r){
            return l.first > r.first;
        };
        priority_queue<pair<double, string>, vector<pair<double, string>>, decltype( priorityLow )>  frontier(priorityLow); // the top node is {priority, state}. Low priority first


        function<double(string, double)> heuristic =            // double heuristic (string state, prior sum);
            [](string state, double prior){return prior + 1;}; //uniform cost search, add the previous value + 1
        
        frontier.push({heuristic(state, 0.0), state});
        bool done = false;



        while(!done && frontier.size()){
            double dist = frontier.top().first;
            string state = frontier.top().second;
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
            }

            if(!inFrontier.count(r)){
                frontier.push({ heuristic(r, dist), r   });
                inFrontier.insert(r);
                cameFrom[r] = state;
            }
            if(!inFrontier.count(u)){
                frontier.push({ heuristic(u, dist), u  });
                inFrontier.insert(u);
                cameFrom[u] = state;
            }
            if(!inFrontier.count(d)){
                frontier.push({ heuristic(d, dist), d   });
                inFrontier.insert(d);
                cameFrom[d] = state;
            }

        }


        if(done) cout << "solved" << endl ;
        else cout << "unsolved" << endl;
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