#pragma once
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <deque>
#include <algorithm>
#include <list>
using std::vector, std::stack, std::pair, std::cin, std::cout, std::endl, std::fill, std::deque, std::list;

vector<vector<int>> kosaraju_list(int n, const vector<pair<int, int>> &edges);
vector<vector<int>> kosaraju_deque(int n, const vector<pair<int, int>> &edges);

//
vector<vector<int>> kosaraju(int n, const vector<pair<int, int>> &edges);               // adapter
void newGraph(vector<pair<int, int>> &edges, int clientSocket, char nums[256], int &n); // new graph
void Newedge(vector<pair<int, int>> &edges, int clientsocket);                          // add edge
void removeEdge(vector<pair<int, int>> &edges, int clientsocket);                       // remove edge