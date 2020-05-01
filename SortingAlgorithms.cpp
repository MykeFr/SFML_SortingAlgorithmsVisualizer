// Algorithms provided by GeeksForGeeks.com
// https://www.geeksforgeeks.org/sorting-algorithms/

#include "ArrayController.hpp"

///////////////////////////////////////////SELECTIONSORT/////////////////////////////////////////////////////////////
void selectionSort(ArrayController<int>& arr)
{
    unsigned i, j, min_idx;
    arr.setSleep(0.005);

    // One by one move boundary of unsorted subarray
    for (i = 0; i < arr.size() - 1; i++) {
        // Find the minimum element in unsorted array
        min_idx = i;

        for (j = i + 1; j < arr.size(); j++)
            if (arr.lessThanOp(arr[j], arr[min_idx]))
                min_idx = j;

        // Swap the found minimum element with the first element
        arr.swap(min_idx, i);
    }
}
///////////////////////////////////////////SELECTIONSORT/////////////////////////////////////////////////////////////


///////////////////////////////////////////BUBBLESORT////////////////////////////////////////////////////////////////
void bubbleSort(ArrayController<int>& arr)
{
    unsigned i, j;
    arr.setSleep(0.009);
    unsigned m = arr.size() - 1;

    for (i = 0; i < m; i++) {
        unsigned n = m - i;

        for (j = 0; j < n; j++)
            if (arr.greaterThanOp(arr[j], arr[j + 1]))
                arr.swap(j, j + 1);
    }
}
///////////////////////////////////////////BUBBLESORT//////////////////////////////////////////////////////////////////////

///////////////////////////////////////////RECURSIVEBUBBLESORT/////////////////////////////////////////////////////////////
// A function to implement bubble sort
void bubbleSortRec(ArrayController<int>& arr, unsigned n)
{
    // Base case
    if (n == 1)
        return;

    // One pass of bubble sort. After
    // this pass, the largest element
    // is moved (or bubbled) to end.
    for (unsigned i = 0; i < n - 1; i++)
        if (arr.greaterThanOp(arr[i], arr[i + 1]))
            arr.swap(i, i + 1);

    // Largest element is fixed,
    // recur for remaining array
    bubbleSortRec(arr, n - 1);
}

void bubbleSortRec(ArrayController<int>& arr)
{
    arr.setSleep(0.009);
    bubbleSortRec(arr, arr.size());
}

///////////////////////////////////////////RECURSIVEBUBBLESORT/////////////////////////////////////////////////////////////

///////////////////////////////////////////MERGESORT&ITERATIVE//////////////////////////////////////////////////////////////////////
// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void merge(ArrayController<int>& arr, int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;

    /* create temp arrays */
    int L[n1], R[n2];

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];

    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray

    while (i < n1 && j < n2) {
        if (arr.lessThanEqualOp(L[i], R[j])) {
            arr.setVal(k, L[i]);
            i++;
        }
        else {
            arr.setVal(k, R[j]);
            j++;
        }

        k++;
    }

    /* Copy the remaining elements of L[], if there
       are any */
    while (i < n1) {
        arr.setVal(k, L[i]);
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2) {
        arr.setVal(k, R[j]);
        j++;
        k++;
    }
}

/* l is for left index and r is right index of the
   sub-array of arr to be sorted */
void mergeSort(ArrayController<int>& arr, int l, int r)
{
    if (l < r) {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l + (r - l) / 2;

        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

/* Iterative mergesort function to sort arr[0...n-1] */
void mergeSortIt(ArrayController<int>& arr)
{
    arr.setSleep(0.4);
    unsigned n = arr.size();
    unsigned curr_size;  // For current size of subarrays to be merged
    // curr_size varies from 1 to n/2
    unsigned left_start; // For picking starting index of left subarray
    // to be merged

    // Merge subarrays in bottom up manner.  First merge subarrays of
    // size 1 to create sorted subarrays of size 2, then merge subarrays
    // of size 2 to create sorted subarrays of size 4, and so on.
    for (curr_size = 1; curr_size <= n - 1; curr_size = 2 * curr_size) {
        // Pick starting point of different subarrays of current size
        for (left_start = 0; left_start < n - 1; left_start += 2 * curr_size) {
            // Find ending point of left subarray. mid+1 is starting
            // point of right
            int mid = std::min(left_start + curr_size - 1, n - 1);

            int right_end = std::min(left_start + 2 * curr_size - 1, n - 1);

            // Merge Subarrays arr[left_start...mid] & arr[mid+1...right_end]
            merge(arr, left_start, mid, right_end);
        }
    }
}

void mergeSort(ArrayController<int>& arr)
{
    arr.setSleep(0.4);
    mergeSort(arr, 0, arr.size() - 1);
}
///////////////////////////////////////////MERGESORT&ITERATIVE/////////////////////////////////////////////////////////////

///////////////////////////////////////////QUICKSORT&ITERATIVE/////////////////////////////////////////////////////////////
/* This function takes last element as pivot, places
the pivot element at its correct position in sorted
array, and places all smaller (smaller than pivot)
to left of pivot and all greater elements to right
of pivot */
int partition(ArrayController<int>& arr, int low, int high)
{
    int pivot = arr[high]; // pivot
    int i = (low - 1); // Index of smaller element

    for (int j = low; j <= high - 1; j++) {
        // If current element is smaller than the pivot
        if (arr.lessThanOp(arr[j], pivot)) {
            i++; // increment index of smaller element
            arr.swap(i, j);
        }
    }

    arr.swap(i + 1, high);
    return (i + 1);
}

/* The main function that implements QuickSort
arr[] --> Array to be sorted,
low --> Starting index,
high --> Ending index */
void quickSort(ArrayController<int>& arr, int low, int high)
{
    if (low < high) {
        /* pi is partitioning index, arr[p] is now
        at right place */
        int pi = partition(arr, low, high);

        // Separately sort elements before
        // partition and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

/* A[] --> Array to be sorted,
l --> Starting index,
h --> Ending index */
void quickSortIt(ArrayController<int>& arr, int l, int h)
{
    // Create an auxiliary stack
    int stack[h - l + 1];

    // initialize top of stack
    int top = -1;

    // push initial values of l and h to stack
    stack[++top] = l;
    stack[++top] = h;

    // Keep popping from stack while is not empty
    while (top >= 0) {
        // Pop h and l
        h = stack[top--];
        l = stack[top--];

        // Set pivot element at its correct position
        // in sorted array
        int p = partition(arr, l, h);

        // If there are elements on left side of pivot,
        // then push left side to stack
        if (p - 1 > l) {
            stack[++top] = l;
            stack[++top] = p - 1;
        }

        // If there are elements on right side of pivot,
        // then push right side to stack
        if (p + 1 < h) {
            stack[++top] = p + 1;
            stack[++top] = h;
        }
    }
}

void quickSort(ArrayController<int>& arr)
{
    arr.setSleep(0.1);
    quickSort(arr, 0, arr.size() - 1);
}

void quickSortIt(ArrayController<int>& arr)
{
    arr.setSleep(0.2);
    quickSortIt(arr, 0, arr.size() - 1);
}
///////////////////////////////////////////QUICKSORT&ITERATIVE/////////////////////////////////////////////////////////////

///////////////////////////////////////////HEAPSORT/////////////////////////////////////////////////////////////
// To heapify a subtree rooted with node i which is
// an index in arr[]. n is size of heap
void heapify(ArrayController<int>& arr, int n, int i)
{
    int largest = i; // Initialize largest as root
    int l = 2 * i + 1; // left = 2*i + 1
    int r = 2 * i + 2; // right = 2*i + 2

    // If left child is larger than root
    if (l < n && arr.greaterThanOp(arr[l], arr[largest]))
        largest = l;

    // If right child is larger than largest so far
    if (r < n && arr.greaterThanOp(arr[r], arr[largest]))
        largest = r;

    // If largest is not root
    if (largest != i) {
        arr.swap(i, largest);

        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}

// main function to do heap sort
void heapSort(ArrayController<int>& arr, int n)
{
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // One by one extract an element from heap
    for (int i = n - 1; i > 0; i--) {
        // Move current root to end
        arr.swap(0, i);

        // call max heapify on the reduced heap
        heapify(arr, i, 0);
    }
}

void heapSort(ArrayController<int>& arr)
{
    arr.setSleep(0.1);
    heapSort(arr, arr.size());
}
///////////////////////////////////////////HEAPSORT/////////////////////////////////////////////////////////////

///////////////////////////////////////////SHELLSORT/////////////////////////////////////////////////////////////
/* function to sort arr using shellSort */
void shellSort(ArrayController<int>& arr)
{
    arr.setSleep(0.1);

    // Start with a big gap, then reduce the gap
    for (unsigned gap = arr.size() / 2; gap > 0; gap /= 2) {
        // Do a gapped insertion sort for this gap size.
        // The first gap elements arr[0..gap-1] are already in gapped order
        // keep adding one more element until the entire array is
        // gap sorted
        for (unsigned i = gap; i < arr.size(); i += 1) {
            // add arr[i] to the elements that have been gap sorted
            // save arr[i] in temp and make a hole at position i
            int temp = arr[i];

            // shift earlier gap-sorted elements up until the correct
            // location for arr[i] is found
            unsigned j;

            for (j = i; j >= gap && arr.greaterThanOp(arr[j - gap], temp); j -= gap)
                arr.setVal(j, arr[j - gap]);

            //  put temp (the original arr[i]) in its correct location
            arr.setVal(j, temp);
        }
    }
}
///////////////////////////////////////////SHELLSORT////////////////////////////////////////////////////////////

///////////////////////////////////////////COMBSORT////////////////////////////////////////////////////////////
// To find gap between elements
int getNextGap(int gap)
{
    // Shrink gap by Shrink factor
    gap = (gap * 10) / 13;

    if (gap < 1)
        return 1;

    return gap;
}

// Function to sort arr[0..n-1] using Comb Sort
void combSort(ArrayController<int>& arr)
{
    arr.setSleep(0.1);
    // Initialize gap
    int gap = arr.size();

    // Initialize swapped as true to make sure that
    // loop runs
    bool swapped = true;

    // Keep running while gap is more than 1 and last
    // iteration caused a swap
    while (gap != 1 || swapped == true) {
        // Find next gap
        gap = getNextGap(gap);

        // Initialize swapped as false so that we can
        // check if swap happened or not
        swapped = false;

        // Compare all elements with current gap
        for (unsigned i = 0; i < arr.size() - gap; i++) {
            if (arr.greaterThanOp(arr[i], arr[i + gap])) {
                arr.swap(i, i + gap);
                swapped = true;
            }
        }
    }
}

///////////////////////////////////////////COMBSORT/////////////////////////////////////////////////////////////

///////////////////////////////////////////CYCLESORT////////////////////////////////////////////////////////////
// Function sort the array using Cycle sort
void cycleSort(ArrayController<int>& arr)
{
    arr.setSleep(0.);

    // count number of memory writes
    unsigned writes = 0;

    // traverse array elements and put it to on
    // the right place
    for (unsigned cycle_start = 0; cycle_start <= arr.size() - 2; cycle_start++) {
        // initialize item as starting point
        int item = arr[cycle_start];

        // Find position where we put the item. We basically
        // count all smaller elements on right side of item.
        unsigned pos = cycle_start;

        for (unsigned i = cycle_start + 1; i < arr.size(); i++)
            if (arr.lessThanOp(arr[i], item))
                pos++;

        // If item is already in correct position
        if (pos == cycle_start)
            continue;

        // ignore all duplicate  elements
        while (item == arr[pos])
            pos += 1;

        // put the item to it's right position
        if (pos != cycle_start) {
            arr.swapVal(pos, item);
            writes++;
        }

        // Rotate rest of the cycle
        while (pos != cycle_start) {
            pos = cycle_start;

            // Find position where we put the element
            for (unsigned i = cycle_start + 1; i < arr.size(); i++)
                if (arr.lessThanOp(arr[i], item))
                    pos += 1;

            // ignore all duplicate  elements
            while (item == arr[pos])
                pos += 1;

            // put the item to it's right position
            if (item != arr[pos]) {
                arr.swapVal(pos, item);
                writes++;
            }
        }
    }

    // Number of memory writes or swaps
    // cout << writes << endl ;
}
///////////////////////////////////////////CYCLESORT///////////////////////////////////////////////////////////////

///////////////////////////////////////////COCKTAILSORT////////////////////////////////////////////////////////////
// Sorts arrar arr[0..n-1] using Cocktail sort
void cocktailSort(ArrayController<int>& arr)
{
    arr.setSleep(0.01);
    unsigned n = arr.size();
    bool swapped = true;
    int start = 0;
    int end = n - 1;

    while (swapped) {
        // reset the swapped flag on entering
        // the loop, because it might be true from
        // a previous iteration.
        swapped = false;

        // loop from left to right same as
        // the bubble sort
        for (int i = start; i < end; ++i) {
            if (arr.greaterThanOp(arr[i], arr[i + 1])) {
                arr.swap(i, i + 1);
                swapped = true;
            }
        }

        // if nothing moved, then array is sorted.
        if (!swapped)
            break;

        // otherwise, reset the swapped flag so that it
        // can be used in the next stage
        swapped = false;

        // move the end point back by one, because
        // item at the end is in its rightful spot
        --end;

        // from right to left, doing the
        // same comparison as in the previous stage
        for (int i = end - 1; i >= start; --i) {
            if (arr.greaterThanOp(arr[i], arr[i + 1])) {
                arr.swap(i, i + 1);
                swapped = true;
            }
        }

        // increase the starting point, because
        // the last stage would have moved the next
        // smallest number to its rightful spot.
        ++start;
    }
}
///////////////////////////////////////////COCKTAILSORT////////////////////////////////////////////////////////////

///////////////////////////////////////////INSERTIONSORT////////////////////////////////////////////////////////////
/* Function to sort an array using insertion sort*/
void insertionSort(ArrayController<int>& arr)
{
    arr.setSleep(0.01);
    unsigned n = arr.size();
    unsigned i;
    int key, j;

    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;

        /* Move elements of arr[0..i-1], that are
        greater than key, to one position ahead
        of their current position */
        while (j >= 0 && arr.greaterThanOp(arr[j], key)) {
            arr.setVal(j + 1, arr[j]);
            j = j - 1;
        }

        arr.setVal(j + 1, key);
    }
}
///////////////////////////////////////////INSERTIONSORT////////////////////////////////////////////////////////////////////

///////////////////////////////////////////RECURSIVEINSERTIONSORT////////////////////////////////////////////////////////////
// Recursive function to sort an array using
// insertion sort
void insertionSortRec(ArrayController<int>& arr, unsigned n)
{
    // Base case
    if (n <= 1)
        return;

    // Sort first n-1 elements
    insertionSortRec(arr, n - 1);

    // Insert last element at its correct position
    // in sorted array.
    int last = arr[n - 1];
    int j = n - 2;

    /* Move elements of arr[0..i-1], that are
      greater than key, to one position ahead
      of their current position */
    while (j >= 0 && arr.greaterThanOp(arr[j], last)) {
        arr.setVal(j + 1, arr[j]);
        j--;
    }

    arr.setVal(j + 1, last);
}

void insertionSortRec(ArrayController<int>& arr)
{
    arr.setSleep(0.01);
    insertionSortRec(arr, arr.size());
}
///////////////////////////////////////////RECURSIVEINSERTIONSORT////////////////////////////////////////////////////////////

///////////////////////////////////////////BINARYINSERTIONSORT////////////////////////////////////////////////////////////
// A binary search based function to find the position
// where item should be inserted in arr[low..high]
int binarySearch(ArrayController<int>& arr, int item, int low, int high)
{
    if (high <= low)
        return (arr.greaterThanOp(item, arr[low])) ? (low + 1) : low;

    int mid = (low + high) / 2;

    if (arr.equalOp(item, arr[mid]))
        return mid + 1;

    if (arr.greaterThanOp(item, arr[mid]))
        return binarySearch(arr, item, mid + 1, high);

    return binarySearch(arr, item, low, mid - 1);
}

// Function to sort an array arr[] of size 'n'
void insertionSortBin(ArrayController<int>& arr)
{
    arr.setSleep(0.1);
    unsigned n =arr.size();
    unsigned i;
    int loc, j, selected;

    for (i = 1; i < n; ++i) {
        j = i - 1;
        selected = arr[i];

        // find location where selected sould be inseretd
        loc = binarySearch(arr, selected, 0, j);

        // Move all elements after location to create space
        while (j >= loc) {
            arr.setVal(j + 1, arr[j]);
            j--;
        }

        arr.setVal(j + 1, selected);
    }
}
///////////////////////////////////////////BINARYINSERTIONSORT////////////////////////////////////////////////////////////

///////////////////////////////////////////BITONICSORT//////////////////////////////////////////////////////////////////////
/*The parameter dir indicates the sorting direction, ASCENDING
   or DESCENDING; if (arr[i] > arr[j]) agrees with the direction,
   then arr[i] and arr[j] are interchanged.*/
void compAndSwap(ArrayController<int>& arr, int i, int j, int dir)
{
    if (dir == arr.greaterThanOp(arr[i], arr[j]))
        arr.swap(i, j);
}

/*It recursively sorts a bitonic sequence in ascending order,
  if dir = 1, and in descending order otherwise (means dir=0).
  The sequence to be sorted starts at index position low,
  the parameter cnt is the number of elements to be sorted.*/
void bitonicMerge(ArrayController<int>& arr, int low, int cnt, int dir)
{
    if (cnt > 1) {
        int k = cnt / 2;

        for (int i = low; i < low + k; i++)
            compAndSwap(arr, i, i + k, dir);

        bitonicMerge(arr, low, k, dir);
        bitonicMerge(arr, low + k, k, dir);
    }
}

/* This function first produces a bitonic sequence by recursively
    sorting its two halves in opposite sorting orders, and then
    calls bitonicMerge to make them in the same order */
void bitonicSort(ArrayController<int>& arr, int low, int cnt, int dir)
{
    if (cnt > 1) {
        int k = cnt / 2;

        // sort in ascending order since dir here is 1
        bitonicSort(arr, low, k, 1);

        // sort in descending order since dir here is 0
        bitonicSort(arr, low + k, k, 0);

        // Will merge wole sequence in ascending order
        // since dir=1.
        bitonicMerge(arr, low, cnt, dir);
    }
}

void bitonicSort(ArrayController<int>& arr)
{
    arr.setSleep(0.2);
    bitonicSort(arr, 0, arr.size(), 1);
}
///////////////////////////////////////////BITONICSORT////////////////////////////////////////////////////////////

///////////////////////////////////////////PANCAKESORT////////////////////////////////////////////////////////////
/* Reverses arr[0..i] */
void flip(ArrayController<int>& arr, unsigned i)
{
    unsigned start = 0;

    while (start < i) {
        arr.swap(start, i);
        start++;
        i--;
    }
}

// Returns index of the
// maximum element in
// arr[0..n-1]
int findMax(ArrayController<int>& arr, unsigned n)
{
    unsigned mi, i;

    for (mi = 0, i = 0; i < n; ++i)
        if (arr.greaterThanOp(arr[i], arr[mi]))
            mi = i;

    return mi;
}

// The main function that
// sorts given array using
// flip operations
void pancakeSort(ArrayController<int>& arr)
{
    arr.setSleep(0.01);
    unsigned n = arr.size();

    // Start from the complete
    // array and one by one
    // reduce current size
    // by one
    for (int curr_size = n; curr_size > 1; --curr_size) {
        // Find index of the
        // maximum element in
        // arr[0..curr_size-1]
        int mi = findMax(arr, curr_size);

        // Move the maximum
        // element to end of
        // current array if
        // it's not already
        // at the end
        if (mi != curr_size - 1) {
            // To move at the end,
            // first move maximum
            // number to beginning
            flip(arr, mi);

            // Now move the maximum
            // number to end by
            // reversing current array
            flip(arr, curr_size - 1);
        }
    }
}
///////////////////////////////////////////PANCAKESORT////////////////////////////////////////////////////////////
