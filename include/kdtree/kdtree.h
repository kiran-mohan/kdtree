/*
 * k-d tree Header
 * Author: Kiran Mohan
 */

#ifndef KDTREE_KDTREE_H
#define KDTREE_KDTREE_H

// C++ Standard Library
#include <vector>
#include <algorithm>
#include <tuple>
#include <memory>


namespace kd_tree
{

typedef std::vector<std::vector<double>> KdPointList;
typedef std::vector<double> KdPoint;

/**
 * @brief Structure of one Node in the k-d tree
 */
struct Node
{
  typedef std::shared_ptr<Node> NodePtr;
  KdPoint kd_point;
  NodePtr left_child;
  NodePtr right_child;
  
  // Constructor
  Node(
    KdPoint kd_pt,
    NodePtr l_ch,
    NodePtr r_ch) :
      kd_point(kd_pt),
      left_child(l_ch),
      right_child(r_ch)
  {
  }
};

typedef std::shared_ptr<Node> NodePtr;

/**
 * @brief Structure that is used to determine which axis to use as the key for sorting
 */
struct CompareAxis
{
  CompareAxis(size_t ax)
  {
    this->axis = ax;
  }
  /**
   * @brief Overloaded operator () to compare the appropriate axis
   * @param point1 The first point for comparison
   * @param point2 The second point for comparison
   * @return Returns true if value of point1 at axis is lower than that of point2; returns false otherwise
   */
  bool operator()(KdPoint point1, KdPoint point2)
  {
    return point1.at(axis) < point2.at(axis);
  }
  size_t axis;
};

class KdTree
{
public:
  /**
   * @brief Parameterized Constructor - constructs k-d tree from point_list
   * @param point_list The list of k-d points from which to build the tree
   */
  KdTree(KdPointList point_list)
  {
    head_ptr = buildKdTree(point_list);
  }

  /**
   * @brief Preorder traversal and print out of the tree elements (root,left,right)
   */
  void traverseTree();
  
private:
  /**
   * @brief Function that constructs the k-d tree from a list of k-d points
   * @param point_list The list of k-d points from which to build the tree
   * @param depth The current depth of the tree
   * @return The pointer pointing to the head node of the tree
   */
  NodePtr buildKdTree(KdPointList point_list, size_t depth=0);

  /**
   * @brief Preorder traversal and print out of the tree elements (root,left,right)
   * @param node_ptr The node from which to begin traversing the tree. If not provided, traversing starts from the root/head of the tree.
   */
  void traverseTree(NodePtr node_ptr, size_t indent=0);

  /**
   * @brief Prints the kd_point associated with the node
   * @param node_ptr Pointer to the node whose kd_point is to be printed
   */
  void printNode(NodePtr node_ptr);

  // MEMBERS
  NodePtr head_ptr;
};
}
#endif  // KDTREE_KDTREE_H

