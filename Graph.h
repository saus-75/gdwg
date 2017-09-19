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
            std::cout << "[ Graph Created ]\n";
        }
        
        ~Graph(){
            std::cout << "[ Graph Destroyed ]\n"; 
        };

        //copy and move
        // Graph(const Graph& b);
        // Graph(Graph&& b);

        // bool addNode(const N& val);
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
        class Node {
            public:
                Node(const N& val) : nodePtr{std::make_shared<N>(val)}, degree{0} {
                    std::cout << " [ Node Created ]\n";
                };

                ~Node(){ 
                    std:: cout << " [ Node Deleted ]\n"; 
                }

                const N& getNode() const {return *nodePtr;}
                const unsigned int getDegree() const {return degree;}
                //for when edge class need access?
                // std::weak_ptr<N> getNodePtr() const {return nodePtr;}
                
            private:
                //a shared ptr pointing to a val
                std::shared_ptr<N> nodePtr;
                //node's number of neighbours
                unsigned int degree;
                //vector of Edges which comprises of two weak_ptr pointing to two nodes
                // std::vector<Edge> edges;
        };

        //vector of Nodes which comprises of shared_ptr pointing to a val
        //a vector of shared ptr of Nodes
        std::vector<shared_ptr<Node>> nodes;
    };

    //add Node into graph
    template <typename N, typename E>
    bool Graph<N,E>::addNode(const N& val){
    }

    //print the nodes in the graph
    template <typename N, typename E>
    void Graph<N,E>::printNodes() const{
    }

    //More to add
    template <typename N, typename E>
    void Graph<N,E>::clear() noexcept{
    }

// #include "Graph.tem"

}


#endif