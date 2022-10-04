#include <iostream>
#include <cassert>
#include "test.h"
#include "../src/finger_tree.h"
#include <memory>

struct ArrayMeasurer : Measurer <long, int> {
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
		compute (long elem) override
		{
			return 1;
		};

		int
		base (void) override
		{
			return 0;
		};
};

void test_finger_tree_size (void) {
	Measurer <long, int> *arry = new ArrayMeasurer ();
	auto tree = std::make_shared<FingerTree<long, int>> (arry);
	int s = 0;

	for (long i=0; i < 90; i++) {
		tree = tree->pushLeft (i);
		assert (s + 1 == tree->s ());
		s++;
	}
	for (long i=0; i < 90; i++) {
		tree = tree->pushRight (i);
		assert (s + 1 == tree->s ());
		s = tree->s ();
	}
	for (long i=0; i < 90; i++) {
		tree = tree->popLeft ();
		assert (s - 1 == tree->s ());
		s = tree->s ();
	}
	for (long i=0; i < 90; i++) {
		tree = tree->popRight ();
		assert (s - 1 == tree->s ());
		s = tree->s ();
	}
}

void test_finger_tree (void) {
	test_finger_tree_s ();
}