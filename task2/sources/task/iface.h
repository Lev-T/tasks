/**
 * @file: task/iface.h 
 * Interface of a programming task 2
 * Lev Teplyakov for iLab Compiler Project, 2014
 */

#include "../Utils/utils_iface.h" // utils
#include <unordered_set> // base container
#include <functional> // reference wrapper for unordered_set
#include <climits> // for UINT_MAX - max number of unique id
#include <string> // string for error throwing

/* namespaces import */
using namespace Utils;

//Debug assert with diagnostic info
#if !defined(GRAPH_ASSERTXD)
#    define GRAPH_ASSERTXD(cond, what) ASSERT_XD(cond, "Graph", what)
#endif

// Simple debug assert
#if !defined(GRAPH_ASSERTD)
#    define GRAPH_ASSERTD(cond) ASSERT_XD(cond, "Graph", "")
#endif

/**
 * Namespace for the programming task
 */
namespace Task
{
    //
    // Graph representation template
    // @param NodeT class representing nodes of graph, should be inherited from Graph::Node
    // @param EdgeT class representing edges of graph, should be inherited from Graph::Edge
    //
    template < class NodeT, class EdgeT> class Graph
    {
    public:
        
        typedef UInt32 UId; // Unique id type for node and edge
        static const UId INVALID_UID = (UId) (-1);
        
        // class for sets of elements, usage of unordered_set allows to search an element
        // with average O(1) time difficulty
        // also it inserts elements with "no copy or move operations are performed"
        typedef std::unordered_set<NodeT> node_set;
        typedef std::unordered_set<NodeT> edge_set;

        class Edge;
        class Node;
        // ---- Graph::Error class representation and implementation ----
        
        // class for errors to be thrown
        // implemented here, because it is small
        class Error: public std::exception
        {
        public:

            explicit Error(const char* message): // constructor
            msg(message)
            {}
            
            const char* what() const throw () // what() to get the error
            {
                return msg.c_str();
            }

        private:
        
            std::string msg; // string to keep error info
        };
        // ---- End of Graph::Error class representation and implementation ----

        // ---- Graph::Node representation ----
        
        class Node
        {
            
        public:
          
            //---- Iterator types ----
            
            typedef typename edge_set::iterator pred_iterator; // iterator for node's predecessor edges
            
            typedef typename edge_set::iterator succ_iterator; // iterator for node's successor edges

            pred_iterator preds_begin() const; // Get iterator to the first predecessor edge
            pred_iterator preds_end() const;   // Get end iterator for the predecessors

            succ_iterator succs_begin() const; // Get iterator to the first successor edge
            succ_iterator succs_end() const;   // Get end iterator for the successors

            const Graph& graph() const;  // Get the graph reference
            UId uid() const; // Get the node's unique id 

            EdgeT& first_pred() const; // Convinience routine returns first predecessor edge or throws an exception
            EdgeT& first_succ() const; // Convinience routine returns first successor edge or throws an exception
            
            UInt32 num_preds() const; // Get the number of predecessors
            UInt32 num_succs() const; // Get the number of successors

        protected:
       
            Node( Graph& g); // Constructor of the node
            virtual ~Node(); // Destructor

        private:
        
            // ---- Default  and copy constructors turned off ---
            
            Node();
            Node(const Node &n);
            
            // ---- The internal implementation routines ----
            
            // ---- The data involved in the implementation ----
            friend Edge;
            const UId _uid; // unique node id
            const Graph& _graph; // the graph reference
            edge_set succs_set; // set for successors
            edge_set preds_set; // set for predecessors
            
            
        };
        
        // ---- End of Graph::Node representation ----
        
        // ---- Graph::Edge representation ----

        class Edge
        {
        public:
            
            NodeT& pred() const; // Get edge predecessor
            NodeT& succ() const; // Get edge successor

            Graph& graph() const; // Get the graph
            UId uid() const; // Get the edge's unique id
            
        protected:
            
            Edge( NodeT& p, NodeT& s); // Construct an edge between given nodes or throw an exception if nodes are from different graphs
            virtual ~Edge();
            
        private:
            
        // ---- Default  and copy constructors turned off ---
            
            Edge();
            Edge( const Edge &e);

        // ---- The internal implementation routines ----


        // ---- The data involved in the implementation ----
            
            NodeT& _pred; // edge predecessor
            NodeT& _succ; // edge successor
            const Graph& _graph; // the graph reference
            const UId _uid; // unique edge id
        };
        
        // ---- End of Graph::Edge representation ----
        
    public:
        
    // ---- Graph interface, part of the task  ----

        typedef typename node_set::iterator node_iterator; // Iterator for the graph's nodes
        typedef typename edge_set::iterator edge_iterator; // Iterator for the graph's edges
               
        node_iterator nodes_begin() const; // Get the iterator to the first node
        node_iterator nodes_end() const;   // Get the end iterator for the nodes

        edge_iterator edges_begin() const; // Get the iterator to the first edge
        edge_iterator edges_end() const;   // Get the end iterator for the edges

        UInt32 num_nodes() const; // Get the number of nodes
        UInt32 num_edges() const; // Get the number of edges

        NodeT& create_node();                   // Create a new node and return reference to it
        EdgeT& create_edge( NodeT& pred, NodeT& succ); // Create a new edge between given nodes
    
        void remove( NodeT& node); // Remove and delete node
        void remove( EdgeT& edge); // Remove and delete edge

        virtual ~Graph(); // Destructor, deletes all nodes and edges
        Graph(); //constructor, initialise unique id generator
        
        UId get_new_id()
        {
            return current_id++;
        }
        
    private:

        // ---- The data involved in the implementation ----

        UId current_id; // variable for new id generating
        node_set nodes; // set of nodes
        edge_set edges; // set of adges
    };

    bool uTest( UnitTest *utest_p);
};

#include "graph_impl.h"
