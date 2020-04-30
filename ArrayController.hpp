#ifndef ARRAY_CONTROLLER
#define ARRAY_CONTROLLER

#include <iostream>
#include <unistd.h>

#include "GraphicsFramework/Tools.h"

template<typename T>
class ArrayController;

typedef void (*Sorter)(ArrayController<int>&);

// to speed up everything lower this value
#define DSLEEP 10000

template<typename T>
class ArrayController
{
public:
	ArrayController(const unsigned l);
	~ArrayController();

	inline T& operator[](const int index) { return array[index]; }
	inline unsigned size() const { return length; }

	inline unsigned getComparisonsCounter() const { return comparisons_counter; }
	inline unsigned getAssignmentsCounter() const { return assignments_counter; }

	inline T* begin() const { return array; }
	inline T* end() const { return array + length; }

	void setSleep(const float s) { sleep = s * DSLEEP; }
	inline float getSleepTime() const { return sleepTime; }

	inline bool equalOp(const T& lhs, const T& rhs) { usleep(sleep); ++comparisons_counter; sleepTime += sleep; return lhs == rhs; }
	inline bool lessThanOp(const T& lhs, const T& rhs) { usleep(sleep); ++comparisons_counter; sleepTime += sleep; return lhs < rhs;}
	inline bool lessThanEqualOp(const T& lhs, const T& rhs) { return !greaterThanOp(lhs, rhs); }
	inline bool greaterThanOp(const T& lhs, const T& rhs) { return lessThanOp(rhs, lhs); }
	inline bool greaterThanEqualOp(const T& lhs, const T& rhs) { return !lessThanOp(lhs, rhs); }

	void randomize(int offset = 0, int step = 1);
	void sort(Sorter func);
	bool sorted() const;

	bool wasAssigned(const unsigned index) const;

	void swap(const int i, const int j);
	void swapVal(const int index, T& val);
	void setVal(const int index, T& val);

	void print();


private:
	unsigned length;

	unsigned comparisons_counter;
	unsigned assignments_counter;
	bool* assignments;
	
	int sleep;
	float sleepTime;

	T* array;
};

#include "ArrayController.impl.hpp"
#endif
