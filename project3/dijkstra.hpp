#ifndef __DIJKSTRA_H_
#define __DIJKSTRA_H_

#include <vector>
#include <unordered_map>
#include <list>
#include <tuple>
#include <queue>
#include <optional>
#include "fheap.hpp"

// A vertex is typed as `vertex_t`. An edge is typed as `edge_t`.
using vertex_t = std::size_t;
using edge_weight_t = float;
using edge_t = std::tuple<vertex_t, vertex_t, edge_weight_t>;
using edges_t = std::vector<edge_t>;

enum class GraphType {
UNDIRECTED,
DIRECTED
};


class Graph {
    public:
        Graph() = delete;
        Graph(const Graph&) = delete;
        Graph(Graph&&) = delete;

        // We assume that if num_vertices is V, a graph contains n vertices from 0 to V-1.
        Graph(size_t num_vertices, const edges_t& edges, GraphType type)
			: num_vertices(num_vertices), type(type) {
			this->num_vertices = num_vertices;
			graph.resize(num_vertices);

			if(type == GraphType::UNDIRECTED) {
				for(auto &edge : edges) {
					const auto& [ from, to, weight ] = edge;
					graph[from].emplace_back(from, to, weight);
					graph[to].emplace_back(to, from, weight);
				}
			} else {
				for(auto &edge : edges) {
					const auto& [ from, to, weight ] = edge;
					graph[from].emplace_back(from, to, weight);
				}
			}
        }

		size_t get_num_vertices() { return num_vertices; }
		std::vector<edge_t> adj_list(vertex_t v) { return graph[v]; }
		
    private:
		size_t num_vertices;
		std::vector<std::vector<edge_t>> graph;
		GraphType type;
};




std::unordered_map<vertex_t, std::optional<std::tuple<vertex_t, edge_weight_t>>>
dijkstra_shortest_path(Graph& g, vertex_t src) {
	
	std::unordered_map<vertex_t, std::optional<std::tuple<vertex_t, edge_weight_t>>> previous;
	FibonacciHeap<std::tuple<vertex_t, edge_weight_t>> Q = {};
    // std::nullopt if vertex v is not reacheble from the source.
	std::vector<edge_weight_t> dist(g.get_num_vertices(), 1e10);
	dist[src] = 0;

    for(vertex_t v = 0; v < g.get_num_vertices(); v++){
		if(v != src){
			previous[v] = std::nullopt;
		}
		Q.insert(std::make_tuple(v, dist[v]));
	}
	while(Q.is_empty() == false){
		auto u = Q.extract_min().value();
		auto adj_list = g.adj_list(std::get<0>(u));
		for(auto adj_edge : adj_list){
			if(dist[std::get<0>(u)] + std::get<2>(adj_edge) < dist[std::get<1>(adj_edge)]){
				dist[std::get<1>(adj_edge)] = dist[std::get<0>(u)] + std::get<2>(adj_edge);
				previous[std::get<1>(adj_edge)] = u;
				Q.decrease_key()
			}
		}
	}
    // TODO
	
    

	return previous;
}


#endif // __DIJKSTRA_H_
