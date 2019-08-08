#ifndef CONFLICTGRAPH_HPP
#define CONFLICTGRAPH_HPP

#include <cstddef>
#include <vector>
#include <string>
#include <utility>

#ifdef DEBUG_CGRAPH
#include "cgraph.h"
#endif // DEBUG_CGRAPH


/**
 * Base class for Conflict Graph: a conflict graph
 * is a structure that stores conflicts between binary
 * variables. These conflicts can involve the original
 * problem variables or complementary variables.
 */
class CoinConflictGraph {
public:
  /**
   * Default constructor
   * @param _cols number of columns in the mixed integer linear program the number
   *        of elements in the conflict graph will be _cols*2
   *        (complementary variables)
   */
  CoinConflictGraph(size_t _size);

  /**
   * Default constructor
   * @param other conflict graph to be copied
   */
  CoinConflictGraph(const CoinConflictGraph *other);

  /**
   * Destructor
   */
  virtual ~CoinConflictGraph();

  /**
   * Checks if two conflict graphs are equal
   *
   * @param other conflict graph
   * @return if conflict graphs are equal
   */
  virtual bool operator==(const CoinConflictGraph &other) const;

  /**
   * Checks for conflicts between two nodes
   *
   * @param n1 node index
   * @param n2 node index
   * @return true if there is an edge between n1 and n2 in the conflict graph, 0 otherwise
   */
  virtual bool conflicting(size_t n1, size_t n2) const = 0;

  /**
   * Queries all nodes conflicting with a given node
   *
   * @param node node index
   * @param temp temporary storage area for storing conflicts, should have space for all elements in the graph (size())
   * @return pair containing (numberOfConflictingNodes, vectorOfConflictingNodes), the vector may be a pointer
   * to temp is the temporary storage area was used or a pointer to a vector in the conflict graph itself
   */
  virtual std::pair< size_t, const size_t *> conflictingNodes( size_t node, size_t *temp ) const = 0;

  double density() const;

  /**
   * number of nodes in the conflict graph
   */
  size_t size() const;

  /**
   * size of the conflict graph
   */
  size_t degree( const size_t node ) const;

  /**
   * minimum node degree 
   */
  size_t minDegree( ) const;

  /**
   * maximum node degree 
   */
  size_t maxDegree( ) const;

#ifdef DEBUG_CGRAPH
  std::vector< std::string > differences( const CGraph* cgraph ) const;
#endif

  // parameter: minimum size of a clique to be stored as a clique (not paiwise)
  static size_t minClqRow;
protected:
  // number of nodes
  size_t size_;

  // these numbers could be large, storing as double
  double nConflicts_;
  double maxConflicts_;
  double density_;

  std::vector< size_t > degree_;
  size_t minDegree_;
  size_t maxDegree_;

};

#endif // CONFLICTGRAPH_H

/* vi: softtabstop=2 shiftwidth=2 expandtab tabstop=2
*/
