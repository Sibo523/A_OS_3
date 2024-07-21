#include "kosaraju.hpp"
#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <algorithm>
#include <ostream>
#include "kosaraju.hpp"
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
std::mutex mtx;
using namespace std;
void input(vector<pair<int, int>> &edges, int clientsocket, int &i, int &j);
void Newedge_helper(vector<pair<int, int>> &edges, int i, int j);

void newGraph(vector<pair<int, int>> &edges, int clientSocket, char nums[256], int &n)
{
    std::lock_guard<std::mutex> lock(mtx);
    int m;
    const std::string message = "Enter the number of vertices and edges: \n";
    write(clientSocket, message.data(), message.size());
    recv(clientSocket, nums, sizeof(nums), 0);

    // parse nums to n and m
    n = atoi(strtok(nums, " "));
    m = atoi(strtok(NULL, " "));
    std::cout << "n: " << n << " m: " << m << std::endl;
    edges.clear();
    const std::string message2 = "Enter the edges: ";
    write(clientSocket, message2.data(), message2.size());

    for (int i = 0; i < m; ++i)
    {
        int j, k;
        const char *message4 = "Enter the edge v,u separated by space in the same line: ";
        write(clientSocket, message4, strlen(message4));
        recv(clientSocket, nums, sizeof(nums), 0);
        j = atoi(strtok(nums, " "));
        k = atoi(strtok(NULL, " "));
        std::cout << "j: " << j << " k: " << k << std::endl; // not really relevent
        Newedge_helper(edges, j, k);
    }
}

void removeEdge(vector<pair<int, int>> &edges, int clientsocket)
{
    std::lock_guard<std::mutex> lock(mtx);
    string msg = "Enter the edge to remove: ";
    int i, j;
    input(edges, clientsocket, i, j);
    for (size_t k = 0; k < edges.size(); k++)
    {
        if (edges[k].first == i && edges[k].second == j)
        {
            edges.erase(edges.begin() + k);
            return; // Assuming that the edge is unique
        }
    }
}

vector<vector<int>> kosaraju(int n, const vector<pair<int, int>> &edges)
{
    std::lock_guard<std::mutex> lock(mtx);
    return kosaraju_list(n, edges);
}
///////////////////////////////////////////////////////////////////////////////////////////
void input(vector<pair<int, int>> &edges, int clientsocket, int &i, int &j)
{
    char nums[256];
    string msg = "Enter the edge to add: ";
    send(clientsocket, msg.data(), msg.size(), 0);
    recv(clientsocket, nums, sizeof(nums), 0);
    i = atoi(strtok(nums, " "));
    j = atoi(strtok(NULL, " "));
}
void Newedge_helper(vector<pair<int, int>> &edges, int i, int j)
{
    edges.push_back({i, j}); // assuming it's valid
    std::cout << "Edge added: " << i << " " << j << std::endl;
}
void Newedge(vector<pair<int, int>> &edges, int clientsock)
{
    int i, j;
    input(edges, clientsock, i, j);
    edges.push_back({i, j}); // assuming it's valid
}

///////////////////////////////////////////////////////////////////////////////////
void dfs_list(int v, const vector<list<int>> &graph, vector<bool> &visited, stack<int> &finishStack)
{
    visited[v] = true;
    for (int neighbor : graph[v])
    {
        if (!visited[neighbor])
        {
            dfs_list(neighbor, graph, visited, finishStack);
        }
    }
    finishStack.push(v);
}

void reverseDfs_list(int v, const vector<list<int>> &reverseGraph, vector<bool> &visited, vector<int> &component)
{
    visited[v] = true;
    component.push_back(v);
    for (int neighbor : reverseGraph[v])
    {
        if (!visited[neighbor])
        {
            reverseDfs_list(neighbor, reverseGraph, visited, component);
        }
    }
}

vector<vector<int>> kosaraju_list(int n, const vector<pair<int, int>> &edges)
{
    vector<list<int>> graph(n + 1), reverseGraph(n + 1);
    for (const auto &edge : edges)
    {
        graph[edge.first].push_back(edge.second);
        reverseGraph[edge.second].push_back(edge.first);
    }

    vector<bool> visited(n + 1, false);
    stack<int> finishStack;

    for (int i = 1; i <= n; ++i)
    {
        if (!visited[i])
        {
            dfs_list(i, graph, visited, finishStack);
        }
    }

    fill(visited.begin(), visited.end(), false);
    vector<vector<int>> scc;

    while (!finishStack.empty())
    {
        int v = finishStack.top();
        finishStack.pop();
        if (!visited[v])
        {
            vector<int> component;
            reverseDfs_list(v, reverseGraph, visited, component);
            scc.push_back(component);
        }
    }

    return scc;
}

void dfs_deq(int v, const vector<deque<int>> &graph, vector<bool> &visited, stack<int> &finishStack)
{
    visited[v] = true;
    for (int neighbor : graph[v])
    {
        if (!visited[neighbor])
        {
            dfs_deq(neighbor, graph, visited, finishStack);
        }
    }
    finishStack.push(v);
}

void reverseDfs_deq(int v, const vector<deque<int>> &reverseGraph, vector<bool> &visited, vector<int> &component)
{
    visited[v] = true;
    component.push_back(v);
    for (int neighbor : reverseGraph[v])
    {
        if (!visited[neighbor])
        {
            reverseDfs_deq(neighbor, reverseGraph, visited, component);
        }
    }
}

vector<vector<int>> kosaraju_deque(int n, const vector<pair<int, int>> &edges)
{
    vector<deque<int>> graph(n + 1), reverseGraph(n + 1);
    for (const auto &edge : edges)
    {
        graph[edge.first].push_back(edge.second);
        reverseGraph[edge.second].push_back(edge.first);
    }

    vector<bool> visited(n + 1, false);
    stack<int> finishStack;

    for (int i = 1; i <= n; ++i)
    {
        if (!visited[i])
        {
            dfs_deq(i, graph, visited, finishStack);
        }
    }

    fill(visited.begin(), visited.end(), false);
    vector<vector<int>> scc;

    while (!finishStack.empty())
    {
        int v = finishStack.top();
        finishStack.pop();
        if (!visited[v])
        {
            vector<int> component;
            reverseDfs_deq(v, reverseGraph, visited, component);
            scc.push_back(component);
        }
    }

    return scc;
}
