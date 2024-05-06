#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <stack>
#include <algorithm>

using namespace std;

// Structure to represent a landmark node
struct Landmark {
    string name;
    vector<string> adjacent; // Names of adjacent landmarks
};

// Function to perform Depth-First Search (DFS)
void DFS(const unordered_map<string, Landmark>& graph, const string& start) {
    unordered_map<string, bool> visited;
    stack<string> stk;

    cout << "DFS Traversal: ";
    stk.push(start);
    visited[start] = true;

    while (!stk.empty()) {
        string current = stk.top();
        stk.pop();
        cout << current << " ";

        for (const auto& adjacent : graph.at(current).adjacent) {
            if (!visited[adjacent]) {
                stk.push(adjacent);
                visited[adjacent] = true;
            }
        }
    }
    cout << endl;
}

// Function to perform Breadth-First Search (BFS)
void BFS(const unordered_map<string, Landmark>& graph, const string& start) {
    unordered_map<string, bool> visited;
    queue<string> q;

    cout << "BFS Traversal: ";
    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        string current = q.front();
        q.pop();
        cout << current << " ";

        for (const auto& adjacent : graph.at(current).adjacent) {
            if (!visited[adjacent]) {
                q.push(adjacent);
                visited[adjacent] = true;
            }
        }
    }
    cout << endl;
}

int main() {
    unordered_map<string, Landmark> graph;

    while (true) {
        int choice;
        cout << "\n1. Add Landmark\n";
        cout << "2. Add Connection between Landmarks\n";
        cout << "3. Perform DFS\n";
        cout << "4. Perform BFS\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string name;
                cout << "Enter landmark name: ";
                cin >> name;
                graph[name] = {name, {}};
                break;
            }
            case 2: {
                string source, destination;
                cout << "Enter source landmark: ";
                cin >> source;
                cout << "Enter destination landmark: ";
                cin >> destination;
                graph[source].adjacent.push_back(destination);
                graph[destination].adjacent.push_back(source);
                break;
            }
            case 3: {
                string start;
                cout << "Enter starting landmark for DFS: ";
                cin >> start;
                DFS(graph, start);
                break;
            }
            case 4: {
                string start;
                cout << "Enter starting landmark for BFS: ";
                cin >> start;
                BFS(graph, start);
                break;
            }
            case 5: {
                cout << "Exiting...";
                return 0;
            }
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
