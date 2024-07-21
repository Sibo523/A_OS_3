#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
// this is mad cause it doensn't have the globals and things but it's okay trust the process
void checkLargeComponent()
{
    while (true)
    {
        std::unique_lock<std::mutex> lock(mtxy);
        cv.wait(lock, []
                { return checkNeeded; });

        // Check if half or more nodes are in the same component
        for (const auto &component : sccGlobal)
        {
            if (component.size() >= nGlobal / 2)
            {
                std::cout << "Half or more of the nodes are in the same component." << std::endl;
                break;
            }
        }

        checkNeeded = false; // Reset the flag
    }
}