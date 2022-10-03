#include <iostream>
#include <cassert>
#include "test.h"
#include "../src/finger_node.h"
#include <memory>

struct ArrayMeasurer : Measurer <int *, int> {
	public:
		int
		combine (int first, int second) override 
		{
			return first + second;
		};

		int
		compare (int first, int second) override
		{
			return second - first;
		};

		int
		compute (int *elem) override
		{
			return 1;
		};

		int
		base (void) override
		{
			return 0;
		};
};

void test_finger_node_constructor (void) {
	int one = 1;
	int two = 2;
	int three = 3;

	auto finger = new FingerLeafNode<int *, int> (&one, &two, &three);
	assert (finger);
	std::cout << "Test constructor: \n";
}

void test_finger_node_find (void) {
	Measurer <int *, int> *arry = new ArrayMeasurer ();
	int one = 1;
	int two = 2;
	int three = 3;
	// 3 elements
	auto measure = 3;

	auto finger = std::make_shared<FingerLeafNode<int *, int>> (&one, &two, &three);
	int *result = finger->find (1, arry);
	std::cout << "Test search: " << *result << "\n";
	auto deepfinger = new FingerInnerNode<int *, int> (finger, NULL, NULL, measure);
}

void test_finger_node (void) {
	test_finger_node_constructor ();
	test_finger_node_find ();
}
