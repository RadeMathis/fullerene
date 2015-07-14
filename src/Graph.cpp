/* * *
 * Createed by Rade Mathis for the LaBRI
 * All right reserved by the LaBRI
 * * *
 * v1.0.0 (14/07/2015)
 * * *
 * This is an interface
 * This class is 1:1 linked with class Graph, who've been to be consider as
 * its inner class.
 * Considering here that a Vertice only make sens in a graph, vertices won't be
 * encapsulated in graphs.
 * * *
 * Here is just some code for Graph::Iterator
 * * */

#include <Graph.hpp>

Graph::~Graph(){}

Iterator::Iterator(Graph* g, int indice) 
	: g_(g), indice_(indice)
{}

Iterator& Iterator::operator++(){
	indice_ = g_->next_(indice_);
	Iterator& out = *this;
	return out;
}

bool Iterator::operator!=(Iterator const& iter) const {
	return indice_ != iter.indice_;
}

Vertice* Iterator::operator*() const {
	return g_->element_(indice_);
}
