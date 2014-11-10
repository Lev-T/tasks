/**
 * @file: task/graph_impl.h 
 * Solution implementation of the programming task 2
 * Lev Teplyakov for iLab Compiler Project, 2014
 */

namespace Task {

    // ---- Graph::Node class implementation ----
    
    //constructor
    template < class NodeT, class EdgeT> Graph < NodeT, EdgeT >::Node::Node(Graph& g):
        _graph(g),
        _uid(g.get_new_id())
    {}
    
    //destructor
    template < class NodeT, class EdgeT> Graph < NodeT, EdgeT >::Node::~Node()
    {
        for(auto it = succs_set.begin(); it != succs_set.end(); it++)
        {
            (*it).succ().preds_set.erase(*it); // remove connecting edge from successor
            delete &(*it); // delete edge
        }
        
        for(auto it = preds_set.begin(); it != preds_set.end(); it++)
        {
            (*it).pred().succs_set.erase(*it); // remove connecting edge from predecessor
            delete &(*it); // delete edge
        }
    }
    
    // preds_begin
    template < class NodeT, class EdgeT> typename Graph < NodeT, EdgeT >::Node::pred_iterator
    Graph < NodeT, EdgeT >::Node::preds_begin() const
    {
        return preds_set.begin();
    }
    
    // preds_end
    template < class NodeT, class EdgeT> typename Graph < NodeT, EdgeT >::Node::pred_iterator
    Graph < NodeT, EdgeT >::Node::preds_end() const
    {
        return preds_set.end();
    }
    
    // succs_begin
    template < class NodeT, class EdgeT> typename Graph < NodeT, EdgeT >::Node::succ_iterator
    Graph < NodeT, EdgeT >::Node::succs_begin() const
    {
        return succs_set.begin();
    }
    
    // succs_end
    template < class NodeT, class EdgeT> typename Graph < NodeT, EdgeT >::Node::succ_iterator
    Graph < NodeT, EdgeT >::Node::succs_end() const
    {
        return succs_set.end();
    }
    
    // graph
    template < class NodeT, class EdgeT> const Graph<NodeT, EdgeT>&
    Graph<NodeT, EdgeT>::Node::graph() const
    {
        return _graph;
    }
    
    // uid
    template < class NodeT, class EdgeT> typename Graph < NodeT, EdgeT >::UId
    Graph< NodeT,  EdgeT>::Node::uid() const
    {
        return _uid;
    }
    
    // first_pred
    template < class NodeT, class EdgeT> EdgeT&
    Graph< NodeT,  EdgeT>::Node::first_pred() const
    {
        switch (preds_set.size()) {
            case 0:
                throw Error("first_pred: size is NULL");
            case 1:
                return *preds_set.begin();
            default:
                throw Error("first_pred: size is > 1");
        }
    }
    
    // first_succ
    template < class NodeT, class EdgeT> EdgeT&
    Graph< NodeT,  EdgeT>::Node::first_succ() const
    {
        switch (succs_set.size()) {
            case 0:
                throw Error("first_pred: size is NULL");
            case 1:
                return *succs_set.begin();
            default:
                throw Error("first_pred: size is > 1");
        }
    }
    
    // ---- End of Graph::Node class implementation ----
    
    // ---- Graph::Edge class implementation ----
    
    //constructor
    template < class NodeT, class EdgeT>
    Graph< NodeT,  EdgeT>::Edge::Edge(NodeT& p, NodeT& s):
    _pred(p),
    _succ(s),
    _graph(p.graph()),
    _uid(const_cast<Graph&>(_graph).get_new_id())
    {
        if(&(p.graph()) != &(s.graph()))
            throw Error("Edge: nodes from different graphs");
    }
    
    //destructor
    template < class NodeT, class EdgeT>
    Graph< NodeT,  EdgeT>::Edge::~Edge()
    {
        _pred.succs_set.erase(dynamic_cast<EdgeT&>(this));
        _succ.preds_set.erase(dynamic_cast<EdgeT&>(this));
    }
    
    //pred
    template < class NodeT, class EdgeT>
    NodeT& Graph< NodeT,  EdgeT>::Edge::pred() const
    {
        return _pred;
    }
    
    //succ
    template < class NodeT, class EdgeT>
    NodeT& Graph< NodeT,  EdgeT>::Edge::succ() const
    {
        return _succ;
    }
    
    //graph
    template < class NodeT, class EdgeT> Graph< NodeT,  EdgeT>&
    Graph< NodeT,  EdgeT>::Edge::graph() const
    {
        return _graph;
    }
    
    //uid
    template < class NodeT, class EdgeT> typename Graph< NodeT,  EdgeT>::UId
    Graph< NodeT,  EdgeT>::Edge::uid() const
    {
        return _uid;
    }
    
    // ---- End of Graph::Edge class implementation ----
    
    // ---- Graph class implementation ----
    
    //constructor
    template < class NodeT, class EdgeT>
    Graph< NodeT, EdgeT>::Graph():
    current_id(0)
    {}
    
    //destructor
    template < class NodeT, class EdgeT>
    Graph<NodeT,  EdgeT>::~Graph()
    {
        //delete all the nodes, so adges are deleted too
        for(auto it = nodes.begin(); it != nodes.end(); ++it)
            delete &(*it);
    }
    
    //nodes_begin
    template < class NodeT, class EdgeT> typename Graph< NodeT,  EdgeT>::node_iterator
    Graph< NodeT,  EdgeT>::nodes_begin() const
    {
        return nodes.begin();
    }
    
    //nodes_end
    template < class NodeT, class EdgeT> typename Graph< NodeT,  EdgeT>::node_iterator
    Graph<NodeT,  EdgeT>::nodes_end() const
    {
        return nodes.end();
    }
    
    //edges_begin
    template < class NodeT, class EdgeT> typename Graph< NodeT,  EdgeT>::edge_iterator
    Graph<NodeT,  EdgeT>::edges_begin() const
    {
        return edges.begin();
    }
    
    //edges_end
    template < class NodeT, class EdgeT> typename Graph< NodeT,  EdgeT>::edge_iterator
     Graph<NodeT,  EdgeT>::edges_end() const
    {
        return edges.end();
    }
    
    //num_nodes
    template < class NodeT, class EdgeT>
    UInt32 Graph<NodeT,  EdgeT>::num_nodes() const
    {
        return nodes.size();
    }
    
    //num_edges
    template < class NodeT, class EdgeT>
    UInt32 Graph< NodeT,  EdgeT>::num_edges() const
    {
        return edges.size();
    }
    
    //create_node
    template < class NodeT, class EdgeT>
    NodeT& Graph<NodeT,  EdgeT>::create_node()
    {
        NodeT* new_node = static_cast<NodeT*>(new NodeT(*(this)));
        nodes.insert(*new_node);
        return *new_node;
    }
    
    //create_edge
    template < class NodeT, class EdgeT>
    EdgeT& Graph<NodeT,  EdgeT>::create_edge( NodeT& pred, NodeT& succ)
    {
        EdgeT* new_edge = static_cast<EdgeT*>(new EdgeT(pred,succ));
        edges.insert(*new_edge);
        return *new_edge;
    }
    
    //remove_node
    template < class NodeT, class EdgeT>
    void Graph<NodeT,  EdgeT>::remove(NodeT& node)
    {
        delete &node;
    }
    
    //remove_edge
    template < class NodeT, class EdgeT>
    void Graph<NodeT,  EdgeT>::remove(EdgeT& edge)
    {
        delete &edge;
    }

    // ---- End of Graph class implementation ----
}; // namespace Task
