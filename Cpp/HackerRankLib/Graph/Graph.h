#pragma once

#include <deque>
#include <map>
#include <memory>
#include <set>

template<class NodeState, class GraphState>
struct Node;

template<class NodeState, class GraphState>
struct Edge;

template<class NodeState, class GraphState>
struct Graph;

template<class NodeState, class GraphState>
struct Node
{
public:
	std::weak_ptr<Graph<NodeState, GraphState>> Graph;
	std::deque<std::weak_ptr<Edge<NodeState, GraphState>>> Edges;
	NodeState State;
};

template<class NodeState, class GraphState>
struct Edge
{
	std::weak_ptr<Node<NodeState, GraphState>> Source;
	std::weak_ptr<Node<NodeState, GraphState>> Destination;
};

template<class NodeState, class GraphState>
struct Graph
{
	std::map<std::size_t, std::shared_ptr<Node<NodeState, GraphState>>> Nodes;
	std::set<std::shared_ptr<Edge<NodeState, GraphState>>> Edges;
	GraphState State;

	void Merge(const Graph& other, const std::shared_ptr<Edge<NodeState, GraphState>>& linkingEdge)
	{
		Nodes.insert(other.Nodes.begin(), other.Nodes.end());
		Edges.insert(other.Edges.begin(), other.Edges.end());
	}
};