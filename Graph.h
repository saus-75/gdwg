#ifndef GDWG_H
#define GDWG_H

#include <iostream>
#include <memory>
#include <algorithm>
#include <vector>
#include <map>
#include <stdexcept>
#include <typeinfo>

namespace gdwg {
    template <typename N, typename E>
    class Graph {
    
    public:
        Graph(){
            std::cout << "[ Graph Created ]\n";
        }
 
        ~Graph(){
            std::cout << "[ Graph Destroyed ]\n"; 
        };

        //copy and move
        // Graph(const Graph& b);
        // Graph(Graph&& b);

        //copy and move assignment
        // Graph& operator= (const Graph& b);
        // Graph& operator= (Graph&& b);

        bool addNode(const N& val);
        bool addEdge(const N& src, const N& dst, const E& w);
        // bool replace(const N& oldData, const N& newData);
        // void mergeReplace(const N& oldData, const N& newData);
        // void deleteNode(const N&) noexcept;
        void deleteEdge(const N& src, const N& dst, const E& w) noexcept;
        void clear() noexcept;
        bool isNode(const N& val) const;
        bool isConnected(const N& src, const N& dst) const;

        //TODO sort by ascending out-degrees
        void printNodes() const;
        //TODO sort by ascending weights
        void printEdges(const N& val) const;

        // void begin() const {}
        // bool end() const {}
        // void next() const {nodes.next();}
        // const N& value() const {nodes.begin()->getNode();}
        //TODO remove debugging prints

    private:
        class Node;
        std::vector<Node> nodes;

    private:
        class Node {
        public:
            Node(const N& val) : 
                nodePtr{std::make_shared<N>(val)}, in_{0}, out_{0}{}

            ~Node(){}

            bool formEdge(Node& dst, const E& weight);
            bool removeEdge(const N& dst, const E& w) noexcept;
            bool isEdge(const Node& dst, const E& weight) const;
            bool isConnected(const Node& dst) const;
            void clearEdges(){edges.clear();}
            void printEdges() const;
            void incIn(){in_++;}
            void decIn(){in_--;}

            std::weak_ptr<N> getNodePtr() const {return nodePtr;}
            const N& getNode() const {return *nodePtr;}
            const unsigned int getIn() const {return in_;}
            const unsigned int getOut() const {return out_;}
        
        private:
            //Forward declaration of Edge class
            class Edge;
            //a shared ptr pointing to a val
            std::shared_ptr<N> nodePtr;
            //number of incoming edges
            unsigned int in_;
            //number of outgoing edges
            unsigned int out_;
            //comprises all nodes its connected to
            std::vector<Edge> edges;

        private:
            class Edge {
            public:
                Edge(const Node& dst, const E& w) : 
                    weight_{w}, dst_{dst.getNodePtr()}{}
                
                ~Edge(){}

                const N& getDst() const { auto dst = dst_.lock(); return *dst; }
                const E& getWeight() const { return weight_; }

            private:
                E weight_;
                std::weak_ptr<N> dst_;
            };
        };
    };

    #include "Graph.tem"

}
#endif