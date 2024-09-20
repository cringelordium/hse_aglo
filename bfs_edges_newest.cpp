#include <iostream>
#include <vector>
#include <cstdint>
#include <queue>
#include <algorithm>
#include <climits>
#include <queue>

// Function to form edge between
// two vertices src and dest
void EdgeAdder(std::vector<std::vector<size_t>>& graph, size_t& edges) {

    for (size_t i = 0; i < edges; ++i) {

        size_t vertex1, vertex2;
        graph[vertex1].push_back(vertex2);
        graph[vertex2].push_back(vertex1);
    }
}

// Function which finds all the paths
// and stores it in paths array
void FindPaths(std::vector<std::vector<size_t>>& paths, std::vector<size_t>& path, 
               std::vector<std::vector<size_t>> parent, size_t vertexes, size_t end) {

	// Loop for all the parents
	// of the given vertex
	for (size_t par : parent[end]) {

		// Insert the current
		// vertex in path
		path.push_back(end);

		// Recursive call for its parent
		FindPaths(paths, path, parent, vertexes, par);

		// Remove the current vertex
		path.pop_back();
	}
}

// Function which performs bfs
// from the given source vertex
void bfs(std::vector<std::vector<size_t>> graph, std::vector<std::vector<size_t>> parent, size_t vertexes, size_t start)
{
	// dist will contain shortest distance
	// from start to every other vertex
	std::vector<size_t> dist(vertexes + 1, SIZE_MAX);
	std::queue<size_t> queue_of_vertexes;

	// Insert source vertex in queue and make
	// its parent -1 and distance 0
	queue_of_vertexes.push(start);
	parent[start] = { 0 };
	dist[start] = 0;

	// Until Queue is empty
	while (!queue_of_vertexes.empty()) {
		size_t vertex = queue_of_vertexes.front();
		queue_of_vertexes.pop();
		for (size_t neig : graph[vertex]) {
			if (dist[neig] > dist[vertex] + 1) {

				// A shorter distance is found
				// So erase all the previous parents
				// and insert new parent u in parent[v]

				dist[neig] = dist[vertex] + 1;
				queue_of_vertexes.push(neig);
				parent[neig].clear();
				parent[neig].push_back(vertex);

			} else if (dist[neig] == dist[vertex] + 1) {

				// Another candidate parent for
				// shortes path found
				parent[neig].push_back(vertex);
			}
		}
	}
}

// Function which prints all the paths
// from start to end
void print_paths(std::vector<std::vector<size_t>> graph, size_t vertexes, size_t start, size_t end) {

	std::vector<std::vector<size_t>> paths;
	std::vector<size_t> path;
	std::vector<size_t> parent[vertexes];

	// Function call to bfs
	bfs(graph, parent, vertexes, start);

	// Function call to find_paths
	FindPaths(paths, path, parent, vertexes, end);

	for (auto bad_path : paths) {

		// Since paths contain each
		// path in reverse order,
		// so reverse it
		std::reverse(bad_path.begin(), bad_path.end());

		// Print node for the current path
		for (int path_vert : bad_path)
			std::cout << path_vert << " ";
		std::cout << std::endl;
	}
}

int main() {

	size_t vertexes, edges;
    std::cin >> vertexes >> edges;

	// array of vectors is used
	// to store the graph
	// in the form of an adjacency list
	std::vector<std::vector<size_t>> graph(vertexes + 1);

	// Given source and destination
	size_t start, end;
	std::cin >> start >> end;

	// Function Call
	print_paths(graph, vertexes, start, end);

	return 0;
}
