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
#include <limits>

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

void KdTree::printKdPoint(KdPoint kd_point)
{
	std::cout << "(";
  for (size_t i = 0; i < k; i++)
  {
    if (i < k-1)
    {
      std::cout << kd_point.at(i) << ",";
    }
    else
    {
    	std::cout << kd_point.at(i) << ")" << std::endl;
    }
  }
}

KdPoint KdTree::minKdPoint(KdPoint a, KdPoint b, KdPoint c, size_t dim)
{
	if (a.at(dim) < b.at(dim))
	{
		if (a.at(dim) < c.at(dim))
		{
			return a;
		}
		else
		{
			return c;
		}
	}
	if (b.at(dim) < c.at(dim))
	{
		return b;
	}
	else
	{
		return c;
	}
}

KdPoint KdTree::findMin(size_t dim)
{
	return findMin(dim, head_ptr, 0);
}

KdPoint KdTree::findMin(size_t dim, NodePtr node_ptr, size_t current_dim)
{
  if (node_ptr == NULL)
  {
  	return kd_max_point;
  }
  if (current_dim == dim)
  {
  	if (node_ptr->left_child == NULL)
  	{
  		return node_ptr->kd_point;
  	}
  	else
  	{
  		return findMin(dim, node_ptr->left_child, (current_dim+1)%k);
  	}
  }
  else
  {
  	return minKdPoint(findMin(dim, node_ptr->left_child, (current_dim+1)%k),
  		                findMin(dim, node_ptr->right_child, (current_dim+1)%k),
  		                node_ptr->kd_point,
  		                dim);
  }
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

void KdTree::printMinInAllDims()
{
  for (size_t i = 0; i < k; i++)
  {
  	std::cout << "Minimum in dimension " << i << " : ";
  	printKdPoint(findMin(i));
  }
}

}
