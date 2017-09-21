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
        bool replace(const N& oldData, const N& newData);
        // void mergeReplace(const N& oldData, const N& newData);
        void deleteNode(const N& val) noexcept;
        void deleteEdge(const N& src, const N& dst, const E& w) noexcept;
        void clear() noexcept;
        bool isNode(const N& val) const;
        bool isConnected(const N& src, const N& dst) const;

        void printNodes() const;
        void printEdges(const N& val) const;
        //REMOVE AT THE END!!
        void printInEdges(const N& val) const;

        // void begin() const {}
        // bool end() const {}
        // void next() const {nodes.next();}
        // const N& value() const {nodes.begin()->getNode();}
        //TODO remove debugging prints

    private:
        class Node;
        using Node_ = std::shared_ptr<Node>;

        std::vector<Node_> nodes;

    private:
        class Node {
        public:
            Node(const N& val) : 
                nodePtr{std::make_shared<N>(val)}, in_{0}, out_{0}{}

            ~Node(){}

            void replace(const N& newData){nodePtr = std::make_shared<N>(newData);}
            bool formEdge(Node_& dst, const E& weight);
            void formInEdge(Node_& src, const E& weight);
            bool removeEdge(const N& dst, const E& w) noexcept;
            void removeInEdge(const N& src, const E& w) noexcept;
            bool isEdge(const Node_& dst, const E& weight) const;
            bool isConnected(const Node& dst) const;
            void cleanEdges();
            void clearEdges(){inEdges.clear(); edges.clear();}
            void printEdges();
            void printInEdges();

            void upIn(){in_ = inEdges.size();}
            void upOut(){out_ = edges.size();}
            void upAll(){in_ = inEdges.size(); out_ = edges.size();}

            std::weak_ptr<N> getNodePtr() const {return nodePtr;}
            const N& getNode() const {return *nodePtr;}
            const unsigned int getIn() const {return in_;}
            const unsigned int getOut() const {return out_;}
        
        private:
            //Forward declaration of Edge class
            class Edge;
            using Edge_ = std::shared_ptr<Edge>;

            //a shared ptr pointing to a val
            std::shared_ptr<N> nodePtr;
            //number of incoming edges
            int in_;
            //number of outgoing edges
            int out_;
            //comprises all outgoing nodes
            std::vector<Edge_> edges;
            //comprises all incoming nodes
            std::vector<Edge_> inEdges;

        private:
            class Edge {
            public:
                Edge(const Node_& dst, const E& w) : 
                    weight_{std::make_shared<E>(w)}, dst_{dst}{}
                
                ~Edge(){}
                
                const bool canUnlock() const { if(auto dst = dst_.lock()){ return true; } return false; } 
                const Node& getDst() const { auto dst = dst_.lock(); return *dst; }
                const E& getWeight() const { return *weight_; }

            private:
                std::shared_ptr<E> weight_;
                std::weak_ptr<Node> dst_;
            };
        };
    };

    #include "Graph.tem"

}
#endif