#include <stdio.h>
#include <limits.h>
#define MAX 16  // Maximum number of cities
#define INF INT_MAX  // Infinity (used for no direct connection)

int dp[1 << MAX][MAX];  // DP table to store the minimum cost
int parent[1 << MAX][MAX];  // Table to store the parent city for path reconstruction

// Function to calculate the minimum cost using Dynamic Programming and Bitmasking
int tsp(int graph[MAX][MAX], int mask, int pos, int V) 
   {
    // If all cities have been visited, return the cost to go back to the start (city 0)
    if (mask == (1 << V) - 1) {
        return (graph[pos][0] != INF) ? graph[pos][0] : INF;  // Return INF if no direct route
    }

    // If the cost has already been computed, return it
    if (dp[mask][pos] != -1) 
   {
        return dp[mask][pos];
    }

    int minCost = INF;  // Initialize the minimum cost to infinity

    // Try to go to all other cities
    for (int city = 0; city < V; city++) {
        // If the city has not been visited yet and there is a direct path
        if ((mask & (1 << city)) == 0 && graph[pos][city] != INF) {
            int newCost = tsp(graph, mask | (1 << city), city, V);

            // Ensure we only add valid costs
            if (newCost != INF && (graph[pos][city] != INF)) {
                newCost += graph[pos][city];
            }

            // If this path is better, update the minimum cost and the parent city
            if (newCost < minCost) {
                minCost = newCost;
                parent[mask][pos] = city;
            }
        }
    }

    // Store the computed minimum cost in the DP table
    return dp[mask][pos] = minCost;
}

// Function to reconstruct the path taken
void printPath(int V) {
    int mask = 1, pos = 0;
    printf("The path taken is: 1 ");  // Starting from city 1 (0-based index is city 0)

    // Reconstruct the path using the parent table
    while (mask != (1 << V) - 1) {
        pos = parent[mask][pos];
        printf("-> %d ", pos + 1);  // Convert 0-based index to 1-based
        mask |= (1 << pos);  // Mark the city as visited
    }
    printf("-> 1\n");  // Return to the starting city
}

int main() {
    int V;
    
    // Input the number of cities
    printf("Enter the number of cities: ");
    scanf("%d", &V);

    // Check if the number of cities exceeds the limit
    if (V > MAX) {
        printf("Number of cities exceeds the maximum limit of %d\n", MAX);
        return 1;
    }

    int graph[MAX][MAX];
    
    // Input the distances between cities
    printf("Enter the distances between the cities in matrix form (enter -1 for no direct route):\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            printf("Distance from city %d to city %d: ", i + 1, j + 1);
            int distance;
            scanf("%d", &distance);
            if (distance == -1) {
                graph[i][j] = INF;  // No direct connection
            } else {
                graph[i][j] = distance;
            }
        }
    }

    // Initialize the DP and parent tables with -1
    for (int i = 0; i < (1 << V); i++) {
        for (int j = 0; j < V; j++) {
            dp[i][j] = -1;
            parent[i][j] = -1;
        }
    }

    // Calculate the minimum cost of the TSP
    int minCost = tsp(graph, 1, 0, V);  // Start from city 0 with only city 0 visited

    // Check if there's a valid path that visits all cities
    if (minCost == INF) {
        printf("There is no possible path that visits all cities.\n");
    } else {
        // Print the minimum cost
        printf("The minimum cost of the TSP is: %d\n", minCost);

        // Print the path taken
        printPath(V);
    }

    return 0;
}
