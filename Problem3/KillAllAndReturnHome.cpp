#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Function to find paths recursively
void findPathsRecursive(const vector<pair<int, int>> &soldiers, int x, int y, vector<pair<int, int>> &currentPath, vector<vector<pair<int, int>>> &paths)
{
    if (soldiers.empty())
    {
        paths.push_back(currentPath);
        return;
    }

    for (size_t i = 0; i < soldiers.size(); ++i)
    {
        pair<int, int> soldier = soldiers[i];
        vector<pair<int, int>> remainingSoldiers(soldiers.begin(), soldiers.end());
        remainingSoldiers.erase(remainingSoldiers.begin() + i);

        currentPath.push_back(soldier);
        findPathsRecursive(remainingSoldiers, soldier.first, soldier.second, currentPath, paths);
        currentPath.pop_back();
    }
}

// Function to find and print all paths
void findPaths(vector<pair<int, int>> &soldiers, int castleX, int castleY)
{
    // Sort soldiers based on their positions for simplicity
    sort(soldiers.begin(), soldiers.end(), [](const pair<int, int> &a, const pair<int, int> &b)
         { return a.first * 10 + a.second < b.first * 10 + b.second; });

    vector<vector<pair<int, int>>> paths;
    vector<pair<int, int>> currentPath;
    findPathsRecursive(soldiers, castleX, castleY, currentPath, paths);

    cout << "Thanks. There are " << paths.size() << " unique paths for your 'special_castle'" << endl;
    for (size_t i = 0; i < paths.size(); ++i)
    {
        cout << "Path " << (i + 1) << ":" << endl;
        for (const auto &step : paths[i])
        {
            cout << "Kill at (" << step.first << "," << step.second << "). Turn Left" << endl;
        }
        cout << "Arrive (" << castleX << "," << castleY << ")" << endl;
    }
}

int main()
{
    int numSoldiers;
    cout << "Enter number of soldiers: ";
    cin >> numSoldiers;

    vector<pair<int, int>> soldiers(numSoldiers);
    for (int i = 0; i < numSoldiers; ++i)
    {
        cout << "Enter coordinates for soldier " << (i + 1) << ": ";
        cin >> soldiers[i].first >> soldiers[i].second;
    }

    int castleX, castleY;
    cout << "Enter the coordinates for your special castle: ";
    cin >> castleX >> castleY;

    findPaths(soldiers, castleX, castleY);

    return 0;
}
