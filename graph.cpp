// FILE: graph.cpp (part of the namespace main_savitch_15)
// TEMPLATE CLASS IMPLEMENTED: graph<Item> (See graph.h for documentation.)
// This file is included in the header file and not compiled separately.
// INVARIANT for the graph class:
//   1. The number of vertices in the graph is stored in the member variable
//      many_vertices.
//   1. These vertices are numbered from 0 to many_vertices-1.
//   2. edges is the adjacency matrix for the graph (with true in edges[i][j]
//      to indicate an edge from vertex i to vertex j).
//   3. For each i < many_vertices, labels[i] is the label of vertex i.

#include <cassert>    // Provides assert
#include <cstdlib>    // Provides size_t
#include <set>        // Provides set
using std::size_t;

namespace main_savitch_15
{
    // CONSTRUCTORS
    template <class Item>
    graph<Item>::graph ( ) :  allocated(10), many_vertices(0) {
        edges = new bool*[allocated];
        
        for(int i = 0; i < allocated; i++){
            edges[i] = new bool[allocated];
        }
        
        labels = new Item[allocated];
    }
    
    template <class Item>
    graph<Item>::graph (size_t initial_allocation ) : allocated(initial_allocation), many_vertices(0) {
        edges = new bool*[allocated];
        
        for(int i = 0; i < allocated; i++){
            edges[i] = new bool[allocated];
        }
        
        labels = new Item[allocated];
    }
    
    template<class Item>
    graph<Item>::graph(const graph &source) : many_vertices(source.many_vertices) {
        allocated = source.allocated;
        edges = new bool*[allocated];
        labels = new Item[allocated];
        
        for(int i = 0; i < allocated; i++){
            edges[i] = new bool[allocated];
            labels[i] = source.labels[i];
            for(int j = 0; j < allocated; j++){
                edges[i][j] = source.edges[i][j];
            }
        }
    }
    
    // OPERATORS
    template <class Item>
    graph<Item>& graph<Item>::operator =(const graph &source) {
        if(this == &source)
            return *this;
        
        if(allocated != source.allocated){
            delete [] labels;
            for(int i = 0; i < allocated; i++){
                delete [] edges[i];
            }
            delete [] edges;
        }
        
        allocated = source.allocated;
        many_vertices = source.many_vertices;
        
        labels = new Item[allocated];
        edges = new bool*[allocated];
        for(int i = 0; i < allocated; i++){
            labels[i] = source.labels[i];
            edges[i] = new bool[allocated];
            for(int j = 0; j < allocated; j++){
                edges[i][j] = source.edges[i][j];
            }
        }
        
        return *this;
    }
    
    // MODIFICATION MEMBER FUNCTIONS
    template <class Item>
    void graph<Item>::add_edge(size_t source, size_t target)
    // Library facilities used: cassert, cstdlib
    {
        assert(source < size( ));
        assert(target < size( ));
        edges[source][target] = true;
    }
    
    template <class Item>
    void graph<Item>::add_vertex(const Item& label)
    // Library facilities used: cassert, cstdlib
    {
        size_t new_vertex_number;
        size_t other_number;
        
        if(size() >= allocated)
            resize(allocated*2);
        
        new_vertex_number = many_vertices;
        many_vertices++;
        for (other_number = 0; other_number < many_vertices; ++other_number)
        {
            edges[other_number][new_vertex_number] = false;
            edges[new_vertex_number][other_number] = false;
        }
        labels[new_vertex_number] = label;
    }
    
    template <class Item>
    bool graph<Item>::is_edge(size_t source, size_t target) const
    // Library facilities used: cassert, cstdlib
    {
        assert(source < size( ));
        assert(target < size( ));
        return edges[source][target];
    }
    
    template <class Item>
    Item& graph<Item>::operator[ ] (size_t vertex)
    // Library facilities used: cassert, cstdlib
    {
        assert(vertex < size( ));
        return labels[vertex];     // Returns a reference to the label
    }
    
    template <class Item>
    Item graph<Item>::operator[ ] (size_t vertex) const
    // Library facilities used: cassert, cstdlib
    {
        assert(vertex < size( ));
        return labels[vertex];     // Returns only a copy of the label
    }
    
    template <class Item>
    std::set<size_t> graph<Item>::neighbors(size_t vertex) const
    // Library facilities used: cassert, cstdlib, set
    {
        std::set<size_t> answer;
        size_t i;
        
        assert(vertex < size( ));
        
        for (i = 0; i < size( ); ++i)
        {
            if (edges[vertex][i])
                answer.insert(i);
        }
        return answer;
    }
    
    template <class Item>
    void graph<Item>::remove_edge(size_t source, size_t target)
    // Library facilities used: cassert, cstdlib
    {
        assert(source < size( ));
        assert(target < size( ));
        edges[source][target] = false;
    }
    
    template <class Item>
    void graph<Item>::resize(size_t new_allocation) {
        if(new_allocation < allocated)
            return;
        
        Item *tmp_labels = new Item[new_allocation];
        bool **tmp_edges = new bool*[new_allocation];
        
        for(int i = 0; i < new_allocation; i++){
            tmp_edges[i] = new bool[new_allocation];
        }
        
        for(int i = 0; i < allocated; i++){
            tmp_labels[i] = labels[i];
            for(int j = 0; j < allocated; j++){
                tmp_edges[i][j] = edges[i][j];
            }
            delete [] edges[i];
        }
        
        delete [] labels;
        delete [] edges;
        labels = tmp_labels;
        edges = tmp_edges;
        allocated = new_allocation;
    }
    
    // DESTRUCTOR
    template <class Item>
    graph<Item>::~graph() {
        delete [] labels;
        for(int i = 0; i < allocated; i++){
            delete [] edges[i];
        }
        delete [] edges;
    }
}
