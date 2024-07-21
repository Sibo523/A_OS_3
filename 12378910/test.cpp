#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>
#include "kosaraju.hpp"
#include <chrono>

TEST_CASE("kosarajaru_list")
{
    vector<pair<int, int>> edges = {{1, 2}, {2, 3}, {3, 1}, {3, 4}, {4, 5}, {5, 6}, {6, 4}, {7, 6}, {7, 8}, {8, 9}, {9, 7}};

    vector<vector<int>> scc = kosaraju_list(9, edges);

    CHECK(scc.size() == 3);
    CHECK(scc[0][0] == 7);
    CHECK(scc[0][1] == 9);
    CHECK(scc[0][2] == 8);
    CHECK(scc[1][0] == 1);
    CHECK(scc[1][1] == 3);
    CHECK(scc[1][2] == 2);
    CHECK(scc[2][0] == 4);
    CHECK(scc[2][1] == 6);
    CHECK(scc[2][2] == 5);
}
TEST_CASE("kusaraju's_deque")
{
    vector<pair<int, int>> edges = {{1, 2}, {2, 3}, {3, 1}, {3, 4}, {4, 5}, {5, 6}, {6, 4}, {7, 6}, {7, 8}, {8, 9}, {9, 7}};
    vector<vector<int>> scc = kosaraju_deque(9, edges);

    CHECK(scc.size() == 3);
    CHECK(scc[0][0] == 7);
    CHECK(scc[0][1] == 9);
    CHECK(scc[0][2] == 8);
    CHECK(scc[1][0] == 1);
    CHECK(scc[1][1] == 3);
    CHECK(scc[1][2] == 2);
    CHECK(scc[2][0] == 4);
    CHECK(scc[2][1] == 6);
    CHECK(scc[2][2] == 5);
}
TEST_CASE("kosaraju-list")
{
    vector<pair<int, int>> edges = {{1, 2}, {2, 3}, {3, 1}, {3, 4}, {4, 5}};
    vector<vector<int>> scc = kosaraju_list(5, edges);
    for (const auto &component : scc)
    {
        std::cout << "Component: ";
        for (int v : component)
        {
            std::cout << v << " ";
        }
        std::cout << std::endl;
    }
    CHECK(scc[0][0] == 1);
    CHECK(scc[0][1] == 3);
    CHECK(scc[0][2] == 2);
    CHECK(scc[1][0] == 4);
    CHECK(scc[2][0] == 5);
}