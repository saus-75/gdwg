#ifndef GDWG_H
#define GDWG_H

#include <iostream>
#include <memory>
#include <algorithm>
#include <vector>
#include <map>

namespace gdwg {
    template <typename N, typename E>
    class Graph {
    
    public:
        Graph(){
            std::cout << "Created\n";
        }
        
        ~Graph(){
            std::cout << "Destroyed\n"; 
        };

        //copy and move
        // Graph(const Graph& b);
        // Graph(Graph&& b);

        bool addNode(const N& val);
        // bool addEdge(const N& src, const N& dst, const E& w);
        // bool replace(const N& oldData, const N& newData);
        // void mergeReplace(const N& oldData, const N& newData);
        // void deleteNode(const N&) noexcept;
        // void deleteEdge(const N& src, const N& dst, const E& w) noexcept;
        // void clear() noexcept;
        // bool isNode(const N& val) const;
        // void printNodes() const;
        // void printEdges(const N& val) const;

        // void begin() const;
        // bool end() const;
        // void next() const;
        // const N& value() const;

    private:
        std::vector<N> nodes;
        std::vector<E> edges;
    };

#include "Graph.tem"

}


#endif