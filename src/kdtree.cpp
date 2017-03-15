/*
 * k-d tree Implementation
 * Author: Kiran Mohan
 */

// C++ Standard Library
#include <iostream>
 #include <iomanip>
#include <vector>
#include <algorithm>
#include <tuple>
#include <memory>

// KdTree
#include <kdtree/kdtree.h>


namespace kd_tree
{

NodePtr KdTree::buildKdTree(KdPointList point_list, size_t depth)
{
  if (point_list.empty())
  {
  	return NULL;
  }
  size_t k = point_list[0].size();
  size_t axis = depth % k;
  std::sort(point_list.begin(), point_list.end(), CompareAxis(axis));
  size_t median_index = point_list.size() / 2;
  KdPointList left_point_list(point_list.begin(), point_list.begin() + median_index);
  KdPointList right_point_list(point_list.begin() + median_index + 1, point_list.end());
  NodePtr node_ptr = std::make_shared<Node>(point_list[median_index],
  	                                        buildKdTree(left_point_list, depth + 1),
  	                                        buildKdTree(right_point_list, depth + 1));
  return node_ptr;
}

void KdTree::traverseTree()
{
	traverseTree(head_ptr);
}

void KdTree::traverseTree(NodePtr node_ptr, size_t indent)
{
	if (node_ptr == NULL)
	{
		return;
	}
	if (indent)
	{
		std::cout << std::setw(indent) << ' ';
	}
	printNode(node_ptr);
	traverseTree(node_ptr->left_child, indent + 2);
	traverseTree(node_ptr->right_child, indent + 2);
}

void KdTree::printNode(NodePtr node_ptr)
{
	size_t counter = 1;
	size_t k = node_ptr->kd_point.size();
	for (double coordinate : node_ptr->kd_point)
	{
		if (counter == 1)
		{
			std::cout << "(";
		}
	  std::cout << coordinate;
	  if (counter != k)
	  {
	  	std::cout << ", ";
	  }
	  else
	  {
	  	std::cout << ")" << std::endl;
	  }
		counter++;
	}
}

}
