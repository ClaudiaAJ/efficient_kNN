#ifndef FDE20_BONUSPROJECT_3_KNN_HPP
#define FDE20_BONUSPROJECT_3_KNN_HPP

#include "Matrix.hpp"

#include <queue>
#include <vector>
#include <unordered_map>
#include <unordered_set>

//---------------------------------------------------------------------------
/// Find the top k neighbors for the node start. The directed graph is stored in
/// matrix m and you can use getNeighbors(node) to get all neighbors of a node.
/// A more detailed description is provided in Matrix.hpp.
/// The function should return the k nearest neighbors in sorted order as vector
/// of Matrix::Entry, where Entry->column is the neighbor node and Entry->weight
/// is the cost to reach the node from the start node.
std::vector<Matrix::Entry> getKNN(const Matrix &m, unsigned start, unsigned k) {

    using Entry = Matrix::Entry;
    std::vector<Entry> result;
    result.reserve(k);

    // store current minimum distance from start node to each node
    std::unordered_map<unsigned, double> costs;
    //std::priority_queue<Entry, std::vector<Entry>, std::greater<Entry>> pq; //error when using with pq.push, why?

    // compare function to sort the entries based on their weight (ascending):
    auto comp = [](const Matrix::Entry &w1, const Matrix::Entry &w2) {
        return w1.weight > w2.weight;
    };
    std::priority_queue<Matrix::Entry, std::vector<Matrix::Entry>, decltype(comp)> pq(comp);

    // insert start node into pq with distance of 0 and store distance of 0 in costs
    pq.push(Entry(start, 0));
    costs[start] = 0;

    while (!pq.empty() && result.size() < k) {
        Entry next_node = pq.top();
        pq.pop();

        // store popped node in result if it is one of the kNN

        if (next_node.weight > 0) {
            result.push_back(next_node);
        }

        for (auto &new_node: m.getNeighbors(next_node.column)) {
            unsigned node = new_node.column;
            double weight = new_node.weight;
            if (costs.find(node) == costs.end() || costs[node] > next_node.weight + weight) {
                costs[node] = next_node.weight + weight;
                pq.push(Entry(node, costs[node]));
            }
        }
    }

    return result;
}

//---------------------------------------------------------------------------

#endif // FDE20_BONUSPROJECT_3_KNN_HPP
