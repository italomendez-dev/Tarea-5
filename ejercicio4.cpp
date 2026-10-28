#include <stdexcept>
#include <iostream>
#include <memory>
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

struct Node {
    int id;
    explicit Node(int value) : id(value) {}
};
class Graph {
    std::unordered_map<int, Node> nodes_;
    std::unordered_map<int, std::vector<int>> adjacency_;
public:
    void addEdge(int from, int to) {
        nodes_.try_emplace(from, from);
        nodes_.try_emplace(to, to);
        adjacency_[from].push_back(to);
    }
    const std::vector<int>& neighbors(int id) const {
        static const std::vector<int> empty;
        auto it = adjacency_.find(id);
        return it == adjacency_.end() ? empty : it->second;
    }
    bool hasNode(int id) const {
        return nodes_.find(id) != nodes_.end();
    }
};
class GraphIterator {
public:
    virtual ~GraphIterator() = default;
    virtual bool hasNext() const = 0;
    virtual int next() = 0;
};
class BFSIterator : public GraphIterator {
    const Graph& graph_;
    std::queue<int> pending_;
    std::unordered_set<int> visited_;
public:
    BFSIterator(const Graph& graph, int start) : graph_(graph) {
        if (graph_.hasNode(start)) {
            pending_.push(start); visited_.insert(start);
        }
    }
    bool hasNext() const override {
        return !pending_.empty();
    }
    int next() override {
        if (!hasNext())
            throw std::out_of_range("BFSIterator sin elementos");
        int current = pending_.front();
        pending_.pop();
        for (int neighbor : graph_.neighbors(current))
            if (visited_.insert(neighbor).second)
                pending_.push(neighbor);
        return current;
    }
};
class DFSIterator : public GraphIterator {
    const Graph& graph_;
    std::stack<int> pending_;
    std::unordered_set<int> visited_;
public:
    DFSIterator(const Graph& graph, int start) : graph_(graph) {
        if (graph_.hasNode(start)) pending_.push(start);
    }
    bool hasNext() const override {
        return !pending_.empty();
    }
    int next() override {
        if (!hasNext())
            throw std::out_of_range("DFSIterator sin elementos");
        int current = pending_.top(); pending_.pop();
        while (!visited_.insert(current).second) {
            if (pending_.empty())
                throw std::out_of_range("DFSIterator sin elementos");
            current = pending_.top();
            pending_.pop();
        }
        const auto& adjacent = graph_.neighbors(current);
        for (auto it = adjacent.rbegin(); it != adjacent.rend(); ++it)
            if (!visited_.count(*it)) pending_.push(*it);
        return current;
    }
};

int main() {
    Graph g;
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 4);

    std::unique_ptr<GraphIterator> it =
            std::make_unique<BFSIterator>(g, 1);

    std::cout << "BFS: ";

    while (it->hasNext())
        std::cout << it->next() << ' ';

    std::cout << '\n';
    it = std::make_unique<DFSIterator>(g, 1);

    std::cout << "DFS: ";

    while (it->hasNext()) std::cout << it->next() << ' ';
    std::cout << '\n';
}
