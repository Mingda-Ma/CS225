/**
 * @file graph_tools.cpp
 * This is where you will implement several functions that operate on graphs.
 * Be sure to thoroughly read the comments above each function, as they give
 *  hints and instructions on how to solve the problems.
 */

#include "graph_tools.h"

/**
 * Finds the minimum edge weight in the Graph graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @return the minimum weighted edge
 *
 * @todo Label the minimum edge as "MIN". It will appear blue when
 *  graph.savePNG() is called in minweight_test.
 *
 * @note You must do a traversal.
 * @note You may use the STL stack and queue.
 * @note You may assume the graph is connected.
 *
 * @hint Initially label vertices and edges as unvisited.
 */
int GraphTools::findMinWeight(Graph& graph)
{
    //TODO: YOUR CODE HERE
	// vector<Vertex> vertices = graph.getVertices();
	// vector<Edge> edges = graph.getEdges();

	// Edge minEdge;
	// int minWeight = -1;

	// //Initialize
	// for(auto edge : edges)
	// 	graph.setEdgeLabel(edge.source, edge.dest, "UNEXPLORED");
	// for(auto vertix : vertices)
	// 	graph.setVertexLabel(vertix, "UNEXPLORED");

	// queue<Vertex> Q;
	// Q.push(graph.getStartingVertex());
	// while(!Q.empty()){
	// 	Vertex cur = Q.front();
	// 	Q.pop();
	// 	vector<Vertex> neighbors = graph.getAdjacent(cur);
	// 	for(auto neighbor : neighbors){
	// 		if(graph.getVertexLabel(neighbor) == "UNEXPLORED"){
	// 			graph.setEdgeLabel(cur, neighbor, "DISCOVERY");
	// 			graph.setVertexLabel(neighbor, "VISITED");
	// 			Q.push(neighbor);

	// 			if(minWeight == -1){
	// 				minEdge = graph.getEdge(cur, neighbor);
	// 				minWeight = minEdge.getWeight();
	// 				graph.setEdgeLabel(cur, neighbor, "MIN");
	// 			}
	// 			else if(graph.getEdge(cur, neighbor).getWeight() < minWeight){
	// 				graph.setEdgeLabel(minEdge.dest, minEdge.source, "VISITED");
	// 				graph.setEdgeLabel(cur, neighbor, "MIN");
	// 				minEdge = graph.getEdge(cur, neighbor);
	// 				minWeight = minEdge.getWeight();
	// 			}
	// 		}
	// 		else if(graph.getEdgeLabel(cur, neighbor) == "UNEXPLORED"){
	// 			graph.setEdgeLabel(cur, neighbor, "CROSS");

	// 			if(minWeight == -1){
	// 				minEdge = graph.getEdge(cur, neighbor);
	// 				minWeight = minEdge.getWeight();
	// 				graph.setEdgeLabel(cur, neighbor, "MIN");
	// 			}
	// 			else if(graph.getEdge(cur, neighbor).getWeight() < minWeight){
	// 				graph.setEdgeLabel(minEdge.dest, minEdge.source, "VISITED");
	// 				graph.setEdgeLabel(cur, neighbor, "MIN");
	// 				minEdge = graph.getEdge(cur, neighbor);
	// 				minWeight = minEdge.getWeight();
	// 			}

	// 		}
	// 	}
	// }
 //    return minWeight;
	   vector <Vertex> vertices = graph.getVertices();
	for(unsigned i = 0; i < vertices.size(); i++)
		graph.setVertexLabel(vertices[i], "UNEXPLORED");
	vector <Edge> edges = graph.getEdges();
	for(unsigned i = 0; i < edges.size(); i++)
	{	Vertex u = edges[i].source;
		Vertex w = edges[i].dest;
		graph.setEdgeLabel(u, w, "UNEXPLORED");
	}
	queue <Vertex> q;
	q.push(vertices[0]);
	graph.setVertexLabel(vertices[0], "VISITED");
	Vertex startDest = (graph.getAdjacent(vertices[0]))[0];
	int minWeight = graph.getEdgeWeight(vertices[0], startDest);
	Vertex min1 = vertices[0];
	Vertex min2 = startDest;
	while(!q.empty())
	{
		Vertex w = q.front();
		q.pop();
		vector <Vertex> adjacent = graph.getAdjacent(w);
		for(size_t i = 0; i < adjacent.size(); i++)
		{
			if(graph.getVertexLabel(adjacent[i]) == "UNEXPLORED")
			{
				graph.setEdgeLabel(w, adjacent[i], "DISCOVERY");
				graph.setVertexLabel(adjacent[i], "VISITED");
				int currWeight = graph.getEdgeWeight(adjacent[i], w);
				if(currWeight < minWeight)
				{
					minWeight = currWeight;
					min1 = w;
					min2 = adjacent[i];
				}
				q.push(adjacent[i]);
			}
			else if(graph.getEdgeLabel(w, adjacent[i]) == "UNEXPLORED")
			{
				graph.setEdgeLabel(w, adjacent[i], "CORSS");
				int currWeight = graph.getEdgeWeight(adjacent[i], w);
				if(currWeight < minWeight)
				{
					minWeight = currWeight;
					min1 = w;
					min2 = adjacent[i];
				}
			}
		}
	}

	graph.setEdgeLabel(min1, min2, "MIN");
	return minWeight;
}
/**
 * Returns the shortest distance (in edges) between the Vertices
 *  start and end.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @param start - the vertex to start the search from
 * @param end - the vertex to find a path to
 * @return the minimum number of edges between start and end
 *
 * @todo Label each edge "MINPATH" if it is part of the minimum path
 *
 * @note Remember this is the shortest path in terms of edges,
 *  not edge weights.
 * @note Again, you may use the STL stack and queue.
 * @note You may also use the STL's unordered_map, but it is possible
 *  to solve this problem without it.
 *
 * @hint In order to draw (and correctly count) the edges between two
 *  vertices, you'll have to remember each vertex's parent somehow.
 */
int GraphTools::findShortestPath(Graph& graph, Vertex start, Vertex end)
{
    //TODO: YOUR CODE HERE
	// vector<Vertex> vertices = graph.getVertices();
	// vector<Edge> edges = graph.getEdges();
	// for(auto vertix : vertices)
	// 	graph.setVertexLabel(vertix, "UNEXPLORED");
	// for(auto edge : edges)
	// 	graph.setEdgeLabel(edge.source, edge.dest, "UNEXPLORED");

	// queue<Vertex> Q;
	// Q.push(start);
	// unordered_map<Vertex, Vertex> path;
	// while(!Q.empty()){
	// 	Vertex cur = Q.front();
	// 	Q.pop();
	// 	vector<Vertex> neighbors = graph.getAdjacent(cur);
	// 	for(auto neighbor : neighbors){
	// 		if(graph.getVertexLabel(neighbor) == "UNEXPLORED"){
	// 			graph.setVertexLabel(neighbor, "VISITED");
	// 			Q.push(neighbor);
	// 			path[neighbor] = cur;
	// 		}
	// 	}

	// }
	// int length = 0;
	// for(Vertex cur = end; cur != start; cur = path[cur], length++)
	// 	graph.setEdgeLabel(cur, path[cur], "MINPATH");

 //    return length;
	   vector <Vertex> vertices = graph.getVertices();
	for(size_t i = 0; i < vertices.size(); i++)
		graph.setVertexLabel(vertices[i], "UNEXPLORED");
	vector <Edge> edges = graph.getEdges();
	for(size_t i = 0; i < edges.size(); i++)
	{	Vertex u = edges[i].source;
		Vertex w = edges[i].dest;
		graph.setEdgeLabel(u, w, "UNEXPLORED");
	}
	queue <Vertex> q;
	unordered_map <Vertex, Vertex> parent;
	q.push(start);
	graph.setVertexLabel(start, "VISITED");
	while(!q.empty())
	{
		Vertex w = q.front();
		q.pop();
		vector <Vertex> adjacent = graph.getAdjacent(w);
		for(size_t i = 0; i < adjacent.size(); i++)
		{
			if(graph.getVertexLabel(adjacent[i]) == "UNEXPLORED")
			{
				graph.setEdgeLabel(w, adjacent[i], "DISCOVERY");
				graph.setVertexLabel(adjacent[i], "VISITED");
				pair <Vertex, Vertex> pairVertex (adjacent[i], w);
				parent.insert(pairVertex);
				q.push(adjacent[i]);
			}
			else if(graph.getEdgeLabel(w, adjacent[i]) == "UNEXPLORED")
			{
				graph.setEdgeLabel(w, adjacent[i], "CORSS");
			}
		}
	}
	int distance = 0;
	while(end != start)
	{
		graph.setEdgeLabel(end, parent[end], "MINPATH");
		end = parent[end];
		distance ++;
	}
	return distance;
}

/**
 * Finds a minimal spanning tree on a graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to find the MST of
 *
 * @todo Label the edges of a minimal spanning tree as "MST"
 *  in the graph. They will appear blue when graph.savePNG() is called.
 *
 * @note Use your disjoint sets class from MP 7.1 to help you with
 *  Kruskal's algorithm. Copy the files into the dsets.h and dsets.cpp .
 * @note You may call std::sort instead of creating a priority queue.
 */
void GraphTools::findMST(Graph& graph)
{
    //TODO: YOUR CODE HERE
	vector<Vertex> vertices = graph.getVertices();
	int n = vertices.size();

	unordered_map<Vertex, int> vertexMap;
	for(int i = 0; i < n; i++)
		vertexMap[vertices[i]] = i;

	DisjointSets vertexSet;
	vertexSet.addelements(n);

	vector<Edge> edges = graph.getEdges();
	std::sort(edges.begin(), edges.end());

	for(auto edge : edges){
		int source = vertexMap[edge.source];
		int dest = vertexMap[edge.dest];

		if(vertexSet.find(source) != vertexSet.find(dest)){
			vertexSet.setunion(source, dest);
			graph.setEdgeLabel(edge.source, edge.dest, "MST");
		}
	}
	    // int pu, pv;
     //    DisjointSets set;
     //    set.addelements(graph.getVertices().size());
     //    vector<Edge> edges = graph.getEdges();
     //    sort(edges.begin(), edges.end());
     //    for(unsigned i = 0; i < edges.size(); i++) {
     //            pu = set.find(edges[i].source);
     //            pv = set.find(edges[i].dest);
     //            if(pu != pv) {
     //                    graph.setEdgeLabel(edges[i].source, edges[i].dest, "MST");
     //                    set.setunion(pu, pv);
     //            }
     //    }

}

