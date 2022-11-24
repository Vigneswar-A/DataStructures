#include <bits/stdc++.h>

using namespace std;

class Edge
{
public:
    int src;
    int dest;
    int weight;
    Edge(int src, int dest, int weight)
        : src(src), dest(dest), weight(weight) {}
};

bool operator<(const Edge &edge1, const Edge &edge2)
{
    return edge1.weight > edge2.weight;
}

class Graph
{
    int ***adjacency;
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

        while (!stack_.empty())
        {
            node = stack_.top();
            stack_.pop();
            cout << node << " ";

            for (int i = 0; i < n; i++)
                if (adjacency[node][i][0] && !visited[i])
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

        while (!queue_.empty())
        {
            node = queue_.front();
            queue_.pop();
            cout << node << " ";

            for (int i = 0; i < n; i++)
                if (adjacency[node][i][0] && !visited[i])
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
        adjacency = new int **[n];

        for (int i = 0; i < n; i++)
        {
            adjacency[i] = new int *[n];
            for (int j = 0; j < n; j++)
            {
                adjacency[i][j] = new int[2];
                adjacency[i][j][0] = 0;
                adjacency[i][j][1] = 0;
            }
        }

        visited = new int[n];
    }

    void display()
    {

        /*
            display the adjacency matrix.
        */

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
                cout << "[" << adjacency[i][j][0] << ", " << adjacency[i][j][1] << "] ";
            cout << endl;
        }
    }

    bool add_edge(int u, int v, int weight = 0, int dir = 0)
    {
        /*
            add edge between vertices u and v, dir = 1 implies directed edge.
        */

        if (u >= n || v >= n)
            return false;
        adjacency[u][v][0] = 1;
        adjacency[u][v][1] = weight;
        if (dir == 0)
        {
            adjacency[v][u][0] = 1;
            adjacency[v][u][1] = weight;
        }
        return true;
    }

    void dfs()
    {

        /*
            depth first search the entire graph.
        */

        for (int i = 0; i < n; i++)
            visited[i] = 0;

        for (int i = 0; i < n; i++)
            if (!visited[i])
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

        for (int i = 0; i < n; i++)
            visited[i] = 0;

        for (int i = 0; i < n; i++)
            if (!visited[i])
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
            adjacency[u][v][0] = 0;
    }

    void clear_graph()
    {
        /*
            removes all existing edges from the graph.
        */

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                adjacency[i][j][0] = 0;
    }

    Graph construct_mst()
    {
        for (int i = 0; i < n; i++)
            visited[i] = 0;

        priority_queue<Edge> pq;
        for (int i = 0; i < n; i++)
            if (adjacency[0][i][0])
                pq.push(Edge(0, i, adjacency[0][i][1]));

        Graph mst(n);
        int edges_remaining = n - 1;
        visited[0] = 1;

        while (edges_remaining)
        {
            Edge edge = pq.top();
            pq.pop();
            if (visited[edge.dest])
                continue;

            mst.add_edge(edge.src, edge.dest, edge.weight);
            edges_remaining--;

            for (int i = 0; i < n; i++)
                if (adjacency[edge.dest][i][0])
                {
                    pq.push(Edge(edge.dest, i, adjacency[edge.dest][i][1]));
                }

            visited[edge.dest] = 1;
        }

        return mst;
    }

    void destroy_graph()
    {
        /*
            destroys graph from memory, provoke only when graph is never to be used again or at program end.
        */

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
                delete[] adjacency[i][j];
            delete[] adjacency[i];
        }

        delete[] adjacency;
        delete[] visited;
    }
};

int main(void)
{
    Graph graph(5);

    graph.add_edge(0, 2, 5);
    graph.add_edge(0, 1, 10);
    graph.add_edge(0, 3, 20);
    graph.add_edge(3, 4, 15);
    graph.add_edge(2, 4, 5);
    graph.add_edge(1, 2, 10);

    cout << "adjacency matrix:" << endl;
    graph.display();

    /*           20
           1----------4
           | \         \
        10 |  \ 5       \ 15
           |   \         \
           2----3---------5
             10       5
    */

    cout << "dfs: ";
    graph.dfs();

    cout << "bfs: ";
    graph.bfs();

    Graph mst = graph.construct_mst();
    mst.display();

    mst.destroy_graph();
    graph.destroy_graph();
}