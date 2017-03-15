/*
 * k-d tree Node
 * Author: Kiran Mohan
 */

// C++ Standard Library
#include <iostream>

// KdTree
#include <kdtree/kdtree.h>


int main(int argc, char** argv)
{
	kd_tree::KdPointList point_list = {{2,3},{5,4},{9,6},{4,7},{8,1},{7,2}};
  kd_tree::KdTree tree(point_list);
  tree.traverseTree();
  return 0;
}