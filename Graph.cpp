#include <iostream>
#include <stack>
#include <queue>

using namespace std;

class Graph
{
    int **adjacency;
    int n;
    int *visited;

    private:
        void dfs_helper(int src)
        {
            /* 
                depth first search starting from src.
            */

            stack<int> stack_;
            stack_.push(src);
            int node;

            while(!stack_.empty())
            {
                node = stack_.top();
                stack_.pop();
                cout << node << " ";

                for(int i = 0; i < n; i++)
                    if(adjacency[node][i] && !visited[i])
                    {
                        stack_.push(i);
                        visited[i] = 1;
                    }
            }
        }

        void bfs_helper(int src)
        {

            /* 
                breadth first search starting from src.
            */


            queue<int> queue_;
            queue_.push(src);
            int node;

            while(!queue_.empty())
            {
                node = queue_.front();
                queue_.pop();
                cout << node << " ";

                for(int i = 0; i < n; i++)
                    if(adjacency[node][i] && !visited[i])
                    {
                        queue_.push(i);
                        visited[i] = 1;
                    }
            }
        }

    public:
        Graph(int nodes)
        {

            /* 
                initialise graph with adjacency matrix
            */

            n = nodes;
            adjacency = new int*[n];
            
            for(int i = 0; i < n; i++)
            {
                adjacency[i] = new int[n];
                for(int j = 0; j < n; j++)
                    adjacency[i][j] = 0;
            }

            visited = new int[n];
        }

        void display()
        {

            /* 
                display the adjacency matrix.
            */

            for(int i = 0; i < n; i++)
            {
                for(int j = 0; j < n; j++)
                    cout << adjacency[i][j] << " ";
                cout << endl;
            }
        }

        bool add_edge(int u, int v, int dir = 0)
        {
            /* 
                add edge between vertices u and v, dir = 1 implies directed edge.
            */

            if (u >= n || v >= n)
                return false;
            adjacency[u][v] = 1;
            if (dir == 0)
                adjacency[v][u] = 1;
            return true;
        }

        void dfs()
        {

            /* 
                depth first search the entire graph.
            */

            for(int i = 0; i < n; i++)
                visited[i] = 0;

            for(int i = 0; i < n; i++)
                if(!visited[i])
                {
                    visited[i] = 1;
                    dfs_helper(i);
                }   

            cout << endl;
        }

        void bfs()
        {
            /* 
                breadth first search the entire graph.
            */

            for(int i = 0; i < n; i++)
                visited[i] = 0;

            for(int i = 0; i < n; i++)
                if(!visited[i])
                {
                    visited[i] = 1;
                    bfs_helper(i);
                }   
            
            cout << endl;
        }

        void remove_edge(int u, int v)
        {
            /*
                simply removes any edge between vertices u and v if exists.
            */
            if (u < n && v < n)
                adjacency[u][v] = 0;
        }

        void clear_graph()
        {
            /*
                removes all existing edges from the graph.
            */

            for(int i = 0; i < n; i++)
                for(int j = 0; j < n; j++)
                    adjacency[i][j] = 0;
        }

        void destroy_graph()
        {
            /*
                destroys graph from memory, provoke only when graph is never to be used again or at program end.
            */

            for(int i = 0; i < n; i++){
                delete[] adjacency[i];
            }

            delete[] adjacency;
            delete[] visited;
        }
};

int main(void)
{
    Graph graph(6);
    graph.add_edge(1, 3);
    graph.add_edge(1, 2);
    graph.add_edge(1, 4);
    graph.add_edge(4, 5);
    graph.add_edge(3, 5);
    graph.add_edge(2, 3);
    graph.display();
    graph.dfs();
    graph.bfs();
    graph.destroy_graph();

}