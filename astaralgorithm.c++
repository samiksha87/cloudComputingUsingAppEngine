#include <iostream>  
#include <vector>  
#include <queue>  
  
using namespace std;  
  
struct Node {  
    int x, y; // Coordinates of the node  
    int g; // Cost from the start node to this node  
    int h; // Heuristic value (estimated cost from this node to the goal node)  
    Node* parent; // Parent node in the path  
  
    Node (int x, int y): x(x), y(y), g(0), h(0), parent(nullptr) {}  
  
    // Calculate the total cost (f = g + h)  
    int f () const {  
        return g + h;  
    }  
};  
  
// Heuristic function (Euclidean distance)  
int calculateHeuristic (int x, int y, int goals, int goal) {  
    return static cast<int> (sqrt (pow (goals - x, 2) + pow (goal - y, 2)));  
}  
  
// A* search algorithm  
vector<pair<int, int>> AStarSearch (int startX, int startY, int goals, int goal, vector<vector<int>>& grid) {  
    vector<pair<int, int>> path;  
    int rows = grid. size ();  
    int cols = grid [0].size ();  
  
    // Create the open and closed lists  
    Priority queue <Node*, vector<Node*>, function<bool (Node*, Node*)>> open List([](Node* lhs, Node* rhs) {  
        return lhs->f() > rhs->f();  
    });  
    vector<vector<bool>> closed List (rows, vector<bool> (cols, false));  
  
  
    // Push the start node to the open list  
    openList.push(start Node);  
  
    // Main A* search loop  
    while (! Open-list. Empty ()) {  
        // Get the node with the lowest f value from the open list  
        Node* current = open-list. Top ();  
        openest. pop ();  
  
        // Check if the current node is the goal node  
        if (current->x == goals && current->y == goal) {  
            // Reconstruct the path  
            while (current! = nullptr) {  
                path. push_back(make_pair(current->x, current->y));  
                current = current->parent;  
            }  
            Reverse (path. Begin(), path.end ());  
            break;  
        }  
  
        // Mark the current node as visited (in the closed list)  
        Closed-list [current->x] [current->y] = true;  
  
        // Generate successors (adjacent nodes)  
        int dx [] = {1, 0, -1, 0};  
        int dy [] = {0, 1, 0, -1};  
  
        for (int i = 0; i < 4; i++) {  
            int new X = current->x + dx [i];  
            int new Y = current->y + dy [i];  
  
  
                        }  
                        break;  
                    }  
                  
  
                    successor->parent = current;  
                    open List.push(successor);  
                }  
    // Cleanup memory  
    for (Node* node: open List) {  
        delete node;  
    }  
  
    return path;  
}  
  
int main () {  
    int rows, cols;  
    cout << "Enter the number of rows: ";  
    cin >> rows;  
    cout << "Enter the number of columns: ";  
    cin >> cols;  
  
    vector<vector<int>> grid (rows, vector<int>(cols));  
  
    cout << "Enter the grid (0 for empty, 1 for obstacle):" << endl;  
    for (int i = 0; i < rows; i++) {  
        for (int j = 0; j < cols; j++) {  
            cin >> grid[i][j];  
        }  
    }  
  
    int startX, startY, goalX, goalY;  
    cout << "Enter the start coordinates (x y): ";  
    cin >> startX >> start;  
    cout << "Enter the goal coordinates (x y): ";  
    cin >> goals >> goals;  
  
    vector<pair<int, int>> path = AStarSearch (startX, startY, goal, goal, grid);  
  
    if (! path. Empty ()) {  
        cout << "Shortest path from (" << startX << "," << start << ") to (" << goal << "," << goal << "):" << endl;  
        for (const auto& point: path) {  
            cout << "(" << point. first << "," << point. second << ") ";  
        }  
        cout << endl;  
    } else {  
        cout << "No path found!" << endl;  
    }  
  
    return 0;  
}  