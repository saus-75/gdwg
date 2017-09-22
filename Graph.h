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
    
    private:
        class Node;
        using Node_ = std::shared_ptr<Node>;
    public:
        Graph(){
            std::cout << "[ Graph Created ]\n";
        }
 
        ~Graph(){
            std::cout << "[ Graph Destroyed ]\n"; 
        };

        Graph(const Graph& b){
            for (auto i : b.getNodes()){
                nodes.push_back(std::make_shared<Node>(Node(*i)));
            }
        }

        Graph(Graph&& b){
            nodes = std::move(b.nodes);
        }

        Graph& operator= (const Graph& b){
            clear();
            for (auto i : b.getNodes()){
                nodes.push_back(std::make_shared<Node>(Node(*i)));
            }
            return this;
        }
        Graph& operator= (Graph&& b){
            clear();
            nodes = std::move(b.nodes);
            return this;
        }

        bool addNode(const N& val);
        bool addEdge(const N& src, const N& dst, const E& w);
        bool replace(const N& oldData, const N& newData);
        void mergeReplace(const N& oldData, const N& newData);
        void deleteNode(const N& val) noexcept;
        void deleteEdge(const N& src, const N& dst, const E& w) noexcept;
        void clear() noexcept;
        bool isNode(const N& val) const;
        bool isConnected(const N& src, const N& dst) const;
        const std::vector<Node_> getNodes() const {return nodes;}


        void printNodes() const;
        void printEdges(const N& val) const;
        //REMOVE AT THE END!!
        void printInEdges(const N& val) const;
        
        void begin() const {itr = 0;}
        bool end() const {if (itr == nodes.size()) return true; return false;}
        void next() const {itr++;}
        const N& value() const {return (*nodes[itr]).getNode();}
        //TODO remove debugging prints

    private:

        std::vector<Node_> nodes;
        mutable unsigned int itr = 0;

    private:
        class Node {
        private:
            //Forward declaration of Edge class
            class Edge;
            using Edge_ = std::shared_ptr<Edge>;

        public:
            Node(const N& val) : 
                nodePtr{std::make_shared<N>(val)}, in_{0}, out_{0}{}

            ~Node(){}

            Node(const Node& b): 
                in_{b.getIn()}, out_{b.getOut()}, nodePtr{std::make_shared<N>(b.getNode())} 
            {
                for (auto i : b.getOutEdge()){
                    edges.push_back(std::make_shared<Edge>(Edge(*i)));
                }
                for (auto i : b.getInEdge()){
                    edges.push_back(std::make_shared<Edge>(Edge(*i)));
                }
            }

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
            const int getIn() const {return in_;}
            const int getOut() const {return out_;}
            const std::vector<Edge_> getOutEdge() const {return edges;}
            const std::vector<Edge_> getInEdge() const {return inEdges;}
        
        private:
            std::shared_ptr<N> nodePtr;
            int in_;
            int out_;
            std::vector<Edge_> edges;
            std::vector<Edge_> inEdges;

        private:
            class Edge {
            public:
                Edge(const Node_& dst, const E& w) : 
                    weight_{std::make_shared<E>(w)}, dst_{dst}{}
                
                ~Edge(){}
                
                Edge(const Edge& b): weight_{std::make_shared<E>(b.getWeight())}, dst_{b.getDstPtr()}{}

                const bool canUnlock() const { if(auto dst = dst_.lock()){ return true; } return false; } 
                const Node& getDst() const { auto dst = dst_.lock(); return *dst; }
                const std::weak_ptr<Node> getDstPtr() const { auto dst = dst_.lock(); return dst; }
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