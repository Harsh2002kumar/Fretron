#include <iostream>
#include <vector>
#include <utility>

using namespace std;

// Define a simple Line2D class to represent line segments
class Line2D
{
public:
    double x1, y1, x2, y2;

    Line2D(double x1, double y1, double x2, double y2)
        : x1(x1), y1(y1), x2(x2), y2(y2) {}

    bool intersectsLine(const Line2D &other) const
    {
        // Function to check if two line segments intersect
        // Using the cross product method for 2D line segments

        // Helper function to calculate the orientation
        auto orientation = [](double x1, double y1, double x2, double y2, double x3, double y3)
        {
            double val = (y2 - y1) * (x3 - x2) - (x2 - x1) * (y3 - y2);
            if (val == 0)
                return 0;             // Collinear
            return (val > 0) ? 1 : 2; // Clockwise or Counterclockwise
        };

        int o1 = orientation(x1, y1, x2, y2, other.x1, other.y1);
        int o2 = orientation(x1, y1, x2, y2, other.x2, other.y2);
        int o3 = orientation(other.x1, other.y1, other.x2, other.y2, x1, y1);
        int o4 = orientation(other.x1, other.y1, other.x2, other.y2, x2, y2);

        if (o1 != o2 && o3 != o4)
            return true;

        return false;
    }
};

void plotFlightPaths(const vector<vector<pair<int, int>>> &flights)
{
    vector<Line2D> lines;
    vector<pair<int, int>> flightIndices;

    // Convert each flight's coordinates into line segments
    for (int flightIndex = 0; flightIndex < flights.size(); flightIndex++)
    {
        const auto &flight = flights[flightIndex];
        for (int i = 0; i < flight.size() - 1; i++)
        {
            Line2D line(flight[i].first, flight[i].second, flight[i + 1].first, flight[i + 1].second);
            lines.push_back(line);
            flightIndices.emplace_back(flightIndex, i);
        }
    }

    // Check for intersections between any two flight paths
    vector<bool> intersectedFlights(flights.size(), false);
    for (int i = 0; i < lines.size(); i++)
    {
        for (int j = i + 1; j < lines.size(); j++)
        {
            if (lines[i].intersectsLine(lines[j]))
            {
                intersectedFlights[flightIndices[i].first] = true;
                intersectedFlights[flightIndices[j].first] = true;
            }
        }
    }

    // Print the non-intersecting flight paths
    cout << "Non-intersecting flight paths:\n";
    for (int i = 0; i < flights.size(); i++)
    {
        if (!intersectedFlights[i])
        {
            cout << "Flight " << (i + 1) << " path: ";
            for (int j = 0; j < flights[i].size(); j++)
            {
                cout << "(" << flights[i][j].first << ", " << flights[i][j].second << ")";
                if (j < flights[i].size() - 1)
                {
                    cout << " -> ";
                }
            }
            cout << endl;
        }
    }
}

int main()
{
    int numFlights;
    cout << "Enter the number of flights: ";
    cin >> numFlights;

    vector<vector<pair<int, int>>> flights;

    // Read coordinates for each flight
    for (int i = 0; i < numFlights; i++)
    {
        int numCoordinates;
        cout << "Enter the number of coordinates for flight " << (i + 1) << ": ";
        cin >> numCoordinates;

        vector<pair<int, int>> flight(numCoordinates);

        for (int j = 0; j < numCoordinates; j++)
        {
            cout << "Enter coordinate " << (j + 1) << " (format: x y): ";
            cin >> flight[j].first >> flight[j].second;
        }
        flights.push_back(flight);
    }

    // Plot the paths and check for intersections
    plotFlightPaths(flights);

    return 0;
}
