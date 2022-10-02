#include "finger_node.h"

#include "finger_tree.h"

#ifndef __FINGER_TREES_HDR
#define __FINGER_TREES_HDR 1

#include "finger_node.h"
#include <vector>
#include <climits>

#define ONE_AFFIX 0x1
#define TWO_AFFIX 0x2
#define THREE_AFFIX 0x4

#define STATE_ONE (ONE_AFFIX)
#define STATE_TWO (ONE_AFFIX | TWO_AFFIX)
#define STATE_THREE (THREE_AFFIX)
#define STATE_FOUR (THREE_AFFIX | ONE_AFFIX)

#define BITMASK int32_t
#define BITMASK_LEVELS 10 // sizeof(BITMASK) * CHAR_BIT / 3 , floor
#define BITMASK_BITS 32 // sizeof(BITMASK) * CHAR_BIT / 3 , floor
#define BITMASK_NULL 0
#define BITMASK_OVERFLOW      0b00101101101101101101101101101101
#define BITMASK_POST_OVERFLOW 0b00011011011011011011011011011011
#define BITMASK_POST_UNDERFLOW 0b00100100100100100100100100100100

// 0-indexed into the mask bit array
const static inline int
bit_set (BITMASK mask, int index)
{
	return (1 & (mask >> index)) != 0;
}

const static inline int
popcount (BITMASK mask)
{
	return __builtin_popcount (mask);
}

const static inline int
get_row (BITMASK mask, int level)
{
	const BITMASK init = mask >> (level * 3);
	const BITMASK first = (init & 0x1);
	const BITMASK second = (init & 0x2) >> 1;
	const BITMASK third = ((init & 0x4) >> 2) * 3;
	return first + second + third;
}

const static inline BITMASK
set_row (BITMASK mask, int level, int state)
{
	// The way the state with (index) bits looks in our bitmask
	const int mappings [] = {0, STATE_ONE, STATE_TWO, STATE_THREE, STATE_FOUR};
	const int new_state = mappings [state];

	// Bits holds the bitmask for all rows below
	// the changed row, lower bits, masks
	// out all lower rows
	const int bits = (level + 1) * 3;
	const int lower_bits = level * 3;

	const BITMASK upper_ones = ~((1 << bits) - 1);
	const BITMASK lower_ones = (1 << lower_bits) - 1;

	const BITMASK without = mask & (upper_ones | lower_ones);
	return without | (new_state << lower_bits);
}

const static inline int
get_num_underflow (BITMASK mask)
{
	// FIXME: parallel underflow check
	int i;
	for (i=0; i < BITMASK_LEVELS; i++) {
		if (get_row (mask, i) != 1) {
			break;
		}
	}
	assert (i < BITMASK_LEVELS);
	return i;
}

const static inline int
get_num_overflow (BITMASK mask)
{
	//// XOR the candy stripe pattern we care about
	//// and find the first differing row from the first
	//// differing bit (ceiling of bit index / 3)
	//BITMASK candy = BITMASK_OVERFLOW >>
	//return __builtin_clz (mask & BITMASK_OVERFLOW);
	// FIXME: parallel overflow check
	int i;
	for (i=0; i < BITMASK_LEVELS; i++) {
		if (get_row (mask, i) != 4) {
			break;
		}
	}
	assert (i < BITMASK_LEVELS);
	return i;
}

const static inline BITMASK
mask_out_lower (BITMASK mask, int i)
{
	auto i_leading_zeros = (1 << i) - 1;
	auto i_trailing_zeros = ~i_leading_zeros;
	return mask & i_trailing_zeros;
}

const static inline BITMASK
mask_out_upper (BITMASK mask, int i)
{
	auto above = BITMASK_BITS - i;
	auto i_trailing_ones = (1 << above) - 1;
	return mask & i_trailing_ones;
}

template <class Value, class Measure>
class FingerTree {
	private:
		const BITMASK left_bitmask;
		const BITMASK right_bitmask;
		const std::shared_ptr<std::vector<Value>> left_side;
		const std::shared_ptr<std::vector<Value>> right_side;

		const Measurer<Value, Measure> *measurer;

		const inline std::shared_ptr<FingerTree <Value, Measure>>
		handle_underflow (bool left_near, BITMASK near_bitmask, BITMASK far_bitmask,
		          std::shared_ptr<std::vector<Value>> near_side, std::shared_ptr<std::vector<Value>> far_side) const
		{
			auto new_near_side = near_side;
			auto new_far_side = far_side;
			//auto new_near_bitmask = near_bitmask;
			auto new_far_bitmask = far_bitmask;
			const int num_underflow = get_num_underflow (near_bitmask);

			int num_above = BITMASK_BITS - num_underflow * 3;
			int current_pivot = get_row (near_bitmask, num_underflow);
			BITMASK masked = mask_out_upper (BITMASK_POST_UNDERFLOW, num_above);

			// Num-overflow is the index of the first non-overflow row in 0 indexing
			BITMASK changed;
			if (current_pivot > 0)
				changed = set_row (masked, num_underflow, current_pivot - 1);
			else
				changed = set_row (masked, num_underflow - 1, 0x0);

			BITMASK new_near_bitmask = changed | mask_out_lower (near_bitmask, (num_underflow + 1) * 3);

			assert (measure_bitmask (new_near_bitmask) == measure_bitmask(near_bitmask) - 1);

			return create (left_near, new_near_bitmask, new_far_bitmask, new_near_side, new_far_side);
		}

		const inline std::shared_ptr<FingerTree <Value, Measure>>
		handle_overflow (bool left_near, BITMASK near_bitmask, BITMASK far_bitmask,
		          std::shared_ptr<std::vector<Value>> near_side, std::shared_ptr<std::vector<Value>> far_side,
		          Value added) const
		{
			auto new_near_side = near_side;
			auto new_far_side = far_side;
			//auto new_near_bitmask = near_bitmask;
			auto new_far_bitmask = far_bitmask;

			const int num_overflow = get_num_overflow (near_bitmask);

			int num_above = BITMASK_BITS - num_overflow * 3;
			int current_pivot = get_row (near_bitmask, num_overflow);
			BITMASK masked = mask_out_upper (BITMASK_POST_OVERFLOW, num_above);

			// Num-overflow is the index of the first non-overflow row in 0 indexing
			BITMASK changed = set_row (masked, num_overflow, current_pivot + 1);
			BITMASK new_near_bitmask = changed | mask_out_lower (near_bitmask, (num_overflow + 1) * 3);

			return create (left_near, new_near_bitmask, new_far_bitmask, new_near_side, new_far_side);
		};

		const inline std::shared_ptr<FingerTree <Value, Measure>>
		push (bool left_near, BITMASK near_bitmask, BITMASK far_bitmask,
		          std::shared_ptr<std::vector<Value>> near_side, std::shared_ptr<std::vector<Value>> far_side,
		          Value added) const
		{
			auto new_near_side = near_side;
			auto new_far_side = far_side;
			auto new_near_bitmask = near_bitmask;
			auto new_far_bitmask = far_bitmask;

			auto new_first_row = 0;
			auto far_mask_without = far_bitmask & ~(ONE_AFFIX | TWO_AFFIX | THREE_AFFIX);
			auto near_mask_without = near_bitmask & ~(ONE_AFFIX | TWO_AFFIX | THREE_AFFIX);

			switch (get_row (near_bitmask, 0)) {
			case 0: {
				switch (get_row (far_bitmask, 0)) {
				case 0:
					// New element is in 1-affix
					new_far_bitmask = STATE_ONE | far_mask_without;
					break;
				case 1:
					// New element is in 2-affix
					new_far_bitmask = STATE_TWO | far_mask_without;
					break;
				case 2:
					// New element is in previous 3-affix position for 3-tuple
					new_far_bitmask = STATE_THREE | far_mask_without;
					break;
				case 3: {
					assert (popcount (near_bitmask) == 0);
					new_near_bitmask = STATE_ONE | far_mask_without;
					// Push to near, start near side's first slot
					//new_near_side = std::make_shared <std::vector<Value> >(near_side);
					//new_near_side->push_back (added);
					break;
				}
				default:
					assert (0 && "Should not be reached");
				}
				break;
			}
			case 1:
				new_near_bitmask = STATE_TWO | near_mask_without;
				break;
			case 2:
				new_near_bitmask = STATE_THREE | near_mask_without;
				break;
			case 3:
				new_near_bitmask = STATE_FOUR | near_mask_without;
				break;
			case 4:
				return handle_overflow (left_near, near_bitmask, far_bitmask, near_side, far_side, added);
			}

			return create (left_near, new_near_bitmask, new_far_bitmask, new_near_side, new_far_side);
		};

		const inline std::shared_ptr<FingerTree <Value, Measure>>
		pop (bool left_near, BITMASK near_bitmask, BITMASK far_bitmask,
		          std::shared_ptr<std::vector<Value>> near_side, std::shared_ptr<std::vector<Value>> far_side) const
		{
			auto new_near_side = near_side;
			auto new_far_side = far_side;
			auto new_near_bitmask = near_bitmask;
			auto new_far_bitmask = far_bitmask;

			auto new_first_row = 0;
			auto far_mask_without = far_bitmask & ~(ONE_AFFIX | TWO_AFFIX | THREE_AFFIX);
			auto near_mask_without = near_bitmask & ~(ONE_AFFIX | TWO_AFFIX | THREE_AFFIX);

			const int near_row = get_row (near_bitmask, 0);
			const int far_row = get_row (far_bitmask, 0);

			switch (near_row) {
			case 0: {
				assert (near_bitmask == 0);
				switch (far_row) {
				case 3:
					// Break up 3-node
					new_far_bitmask = STATE_TWO | far_mask_without;
					break;
				case 2:
					// Pop two affix 
					new_far_bitmask = STATE_ONE | far_mask_without;
					break;
				case 1:
					// Pop one affix 
					//new_far_bitmask = 0x0 | far_mask_without;
					return handle_underflow (!left_near, far_bitmask, near_bitmask, far_side, near_side);
					break;
				case 0:
					assert (far_bitmask == 0);
					assert (0 && "Don't pop an empty tree");
					break;
				default:
					assert (0 && "Should not be reached");
				}
				break;
			}
			case 4:
				new_near_bitmask = STATE_THREE | near_mask_without;
				break;
			case 3:
				new_near_bitmask = STATE_TWO | near_mask_without;
				break;
			case 2:
				new_near_bitmask = STATE_ONE | near_mask_without;
				break;
			case 1:
				return handle_underflow (left_near, near_bitmask, far_bitmask, near_side, far_side);
			}

			if (get_row (near_bitmask, 0) == 0)
				assert (measure_bitmask (new_far_bitmask) == measure_bitmask(far_bitmask) - 1);
			else
				assert (measure_bitmask (new_near_bitmask) == measure_bitmask(near_bitmask) - 1);

			return create (left_near, new_near_bitmask, new_far_bitmask, new_near_side, new_far_side);
		};

		const inline std::shared_ptr<FingerTree <Value, Measure>>
		create (bool left_near, BITMASK near_bitmask, BITMASK far_bitmask,
		          std::shared_ptr<std::vector<Value>> near_side, std::shared_ptr<std::vector<Value>> far_side) const
		{
			if (left_near)
				return std::make_shared <FingerTree<Value, Measure> > (measurer, near_bitmask, far_bitmask, near_side, far_side);
			else
				return std::make_shared <FingerTree<Value, Measure> > (measurer, far_bitmask, near_bitmask, far_side, near_side);
		};

		const inline size_t
		measure_bitmask (BITMASK mask) const
		{
			// The 0th index holds 3 items, the Nth holds 3 ** (N - 1) items
			int size = 1;
			int accum = 0;

			int num_rows = sizeof (mask) * CHAR_BIT / 3;

			for (int i=0; i < num_rows; i += 1) {
				if (bit_set (mask, i * 3))
					accum += size;
				if (bit_set (mask, (i * 3) + 1))
					accum += size;
				if (bit_set (mask, (i * 3) + 2))
					accum += size * 3;
				size = size * 3;
			}
			return accum;
		};

	public:
		FingerTree (const Measurer<Value, Measure> *measurer, const BITMASK left_bitmask, const BITMASK right_bitmask,
		    const std::shared_ptr<std::vector<Value>> left_side, const std::shared_ptr<std::vector<Value>> right_side) :
		    left_bitmask (left_bitmask), right_bitmask (right_bitmask), left_side (left_side), right_side (right_side)
		{
			if ((left_bitmask & 0xf) == 0x0)
				assert (left_bitmask == 0);

			if ((right_bitmask & 0xf) == 0x0)
				assert (right_bitmask == 0);
		};

		// FIXME: get measurer from subclass, no indirection
		FingerTree (Measurer<Value, Measure> *measurer) : left_bitmask (BITMASK_NULL), right_bitmask (BITMASK_NULL), left_side (nullptr), right_side (nullptr)
		{};

		//const std::shared_ptr<FingerTree <Value, Measure>>
		//add (Value v)
		//{
		
		//}

		//const Value
		//find (Measure threshold)
		//{
		
		//}

		//const std::shared_ptr<FingerTree <Value, Measure>>
		//concat (FingerTree *ftree) 
		//{
			//return nullptr;
		//}

		const size_t 
		size (void) const
		{
			return measure_bitmask (this->left_bitmask) + measure_bitmask (this->right_bitmask);
		};

		const std::shared_ptr<FingerTree <Value, Measure>>
		pushLeft (Value v) const
		{
			return push (true, left_bitmask, right_bitmask, left_side, right_side, v);
		};

		const std::shared_ptr<FingerTree <Value, Measure>>
		pushRight (Value v) const
		{
			return push (false, right_bitmask, left_bitmask, right_side, left_side, v);
		};

		const std::shared_ptr<FingerTree <Value, Measure>>
		popLeft (void) const
		{
			return pop (true, left_bitmask, right_bitmask, left_side, right_side);
		};

		const std::shared_ptr<FingerTree <Value, Measure>>
		popRight (void) const
		{
			return pop (false, right_bitmask, left_bitmask, right_side, left_side);
		};

		//const Value
		//peekRight (Value v) const
		//{
			//return; 
		//};
};


#endif





#ifndef __FINGER_NODE_HDR
#define __FINGER_NODE_HDR 1

#include <memory>

#include <cassert>

template <class Value, class Measure>
struct Measurer
{
	public:
		virtual Measure
		combine (Measure first, Measure second) = 0;

		virtual int
		compare (Measure first, Measure second) = 0;

		virtual Measure
		compute (Value val) = 0;

		virtual Measure
		base (void) = 0;
};

template <class Value, class MeasureClass>
struct FingerNode
{
	public:
		const int depth;
		// implement filter and map with
		//std::shared_ptr<FingerNode>
		//foldr ((Value)(*)(Value));

		Value
		find (MeasureClass threshold, Measurer<Value, MeasureClass> *executor);

		FingerNode (int depth) : depth(depth) {};
};

template <class Value, class MeasureClass>
struct FingerInnerNode : FingerNode<Value, MeasureClass> {
	using ref = std::shared_ptr<FingerNode<Value, MeasureClass> >;

	public:
		const MeasureClass measure;
		const ref left;
		const ref middle;
		const ref right;
		FingerInnerNode (ref left, ref middle, ref right, MeasureClass m): 
			FingerNode<Value, MeasureClass>(0), left(left), middle(middle), right(right), measure(m) {};
};

template <class Value, class Measure>
struct FingerLeafNode : FingerNode<Value, Measure> {
	public:
		const Value left;
		const Value middle;
		const Value right;
		FingerLeafNode (Value left, Value middle, Value right): 
			FingerNode<Value, Measure>(0), left(left), middle(middle), right(right) {};
};

template <class Value, class Measure>
Value
FingerNode<Value, Measure>::find (Measure threshold, Measurer<Value, Measure> *executor)
{
	Measure accum = executor->base ();

	if (this->depth == 0) {
		auto handle = (FingerLeafNode<Value, Measure> *) this;
		accum = executor->combine (accum, executor->compute(handle->left));
		if (executor->compare(threshold, accum) > 0)
			return handle->left;

		accum = executor->combine (accum, executor->compute(handle->middle));
		if (executor->compare(threshold, accum) > 0)
			return handle->middle;

		accum = executor->combine (accum, executor->compute(handle->right));
		if (executor->compare(threshold, accum) > 0)
			return handle->right;
	} else {
		assert(0);
		return NULL;
	}

	return NULL;
}

#endif
