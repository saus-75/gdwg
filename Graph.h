#ifndef GDWG_H
#define GDWG_H

namespace gdwg {
    class Graph{
    public:
        Graph();
        ~Graph();

        Graph(const Graph& b);
        Graph(Graph&& b);

        bool addNode(const N& val);
        bool addEdge(const N& src, const N& dst, const E& w);
        bool replace(const N& oldData, const N& newData);
        void mergeReplace(const N& oldData, const N& newData);
        void deleteNode(const N&) noexcept;
        void deleteEdge(const N& src, const N& dst, const E& w) noexcept;
        void clear() noexcept;
        bool isNode(const N& val) const;
        void printNodes() const;
        void printEdges(const N& val) const;

        void begin() const;
        bool end() const;
        void next() const;
        const N& value() const;

    private:

    };
}

#include "Graph.tem"

#endif