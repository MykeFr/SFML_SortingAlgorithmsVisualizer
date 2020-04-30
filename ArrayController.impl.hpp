#ifndef ARRAY_CONTROLLER
#error "Cannot include this file without ArrayController.hpp"
#endif
#ifndef ARRAY_CONTROLLER_IMPL
#define ARRAY_CONTROLLER_IMPL

template<typename T> ArrayController<T>::ArrayController(const unsigned l) : comparisons_counter(0),
	assignments_counter(0), sleepTime(0.)
{
	length = l;
	array = new T[length];
	assignments = new bool[length];

	for (unsigned i = 0; i < length; ++i)
		assignments[i] = false;
}

template<typename T>
void ArrayController<T>::randomize(int offset, int step)
{
	for (unsigned i = 0; i < length; ++i)
		array[i] = i * step + offset;

	std::random_shuffle(begin(), end(), [](int i) { return Rand.getI(0, i); });

	sleepTime = 0.;

	for (unsigned i = 0; i < length; ++i)
		assignments[i] = false;
}

template<typename T>
bool ArrayController<T>::wasAssigned(const unsigned index) const
{
	if (assignments[index]) {
		assignments[index] = false;
		return true;
	}

	return false;
}

template<typename T>
void ArrayController<T>::swap(const int i, const int j)
{
	T temp = array[i];
	array[i] = array[j];
	array[j] = temp;
	assignments[i] = true;
	assignments[j] = true;
	assignments_counter += 2;
}

template<typename T>
void ArrayController<T>::swapVal(const int i, T& val)
{
	T temp = array[i];
	array[i] = val;
	val = temp;
	assignments[i] = true;
	++assignments_counter;
}

template<typename T>
void ArrayController<T>::setVal(const int index, T& val)
{
	array[index] = val;
	assignments[index] = true;
	++assignments_counter;
}

template<typename T>
void ArrayController<T>::print()
{
	for (unsigned i = 0; i < length; ++i)
		std::cout << array[i] << std::endl;
}

template<typename T>
bool ArrayController<T>::sorted() const
{
	for (unsigned i = 0; i < length - 1; ++i)
		if (array[i] > array[i + 1]) return false;

	return true;
}

template<typename T>
void ArrayController<T>::sort(Sorter func)
{
	comparisons_counter = 0;
	assignments_counter = 0;
	func(*this);
}

template<typename T> ArrayController<T>::~ArrayController()
{
	if (array != nullptr)
		delete[] array;
}
#endif