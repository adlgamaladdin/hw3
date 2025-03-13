#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>

template <typename T, typename PComparator = std::less<T> >
class Heap
{
public:
  /**
   * @brief Construct a new Heap object
   * 
   * @param m ary-ness of heap tree (default to 2)
   * @param c binary predicate function/functor that takes two items
   *          as an argument and returns a bool if the first argument has
   *          priority over the second.
   */
  Heap(int m=2, PComparator c = PComparator());

  /**
  * @brief Destroy the Heap object
  * 
  */
  ~Heap();

  /**
   * @brief Push an item to the heap
   * 
   * @param item item to heap
   */
  void push(const T& item);

  /**
   * @brief Returns the top (priority) item
   * 
   * @return T const& top priority item
   * @throw std::underflow_error if the heap is empty
   */
  T const & top() const;

  /**
   * @brief Remove the top priority item
   * 
   * @throw std::underflow_error if the heap is empty
   */
  void pop();

  /// returns true if the heap is empty

  /**
   * @brief Returns true if the heap is empty
   * 
   */
  bool empty() const;

    /**
   * @brief Returns size of the heap
   * 
   */
  size_t size() const;

private:
  /// Add whatever helper functions and data members you need below
  std::vector<T> heap;
  int m; // number of children
  PComparator c;
  void heapifyUp(int index);
  void heapifyDown(int index);
  int getParentIndex(int index) const;
  int getChildIndex(int parentIndex, int childNumber) const;
  int getMinChildIndex(int parentIndex) const;

};

// Add implementation of member functions here

template <typename T, typename PComparator>
Heap<T,PComparator>::Heap(int m, PComparator c) : m(m), c(c) {
  if(m < 2){
    throw std::invalid_argument("m can't be less than 2.");
  }

}

template <typename T, typename PComparator>
Heap<T,PComparator>::~Heap(){
}

template <typename T, typename PComparator>
void Heap<T,PComparator>::push(const T& item){
  heap.push_back(item);
  heapifyUp(heap.size() - 1);
}

template <typename T, typename PComparator>
bool Heap<T,PComparator>::empty() const{
  return heap.empty();
}

template <typename T, typename PComparator>
size_t Heap<T,PComparator>::size() const{
  return heap.size();
}

template <typename T, typename PComparator>
void Heap<T,PComparator>::heapifyUp(int index){
  while (index > 0) {
    int parentIndex = getParentIndex(index); 
    if (c(heap[index], heap[parentIndex])) { //compares priority of parent and child; if tied does not swap them and keeps it based on order added
        std::swap(heap[index], heap[parentIndex]); 
        index = parentIndex;
    } else {
        break;
    }
}

}

template <typename T, typename PComparator>
void Heap<T,PComparator>::heapifyDown(int index){
  while (true) {
    int minChildIndex = getMinChildIndex(index);
    if (minChildIndex == -1 || c(heap[index], heap[minChildIndex])) {
        break;
    }
    std::swap(heap[index], heap[minChildIndex]);
    index = minChildIndex;
}

}

template <typename T, typename PComparator>
int Heap<T,PComparator>::getParentIndex(int index) const{
  return (index - 1) / m;
}

template <typename T, typename PComparator>
int Heap<T,PComparator>::getChildIndex(int parentIndex, int childNumber) const{
  return m * parentIndex + childNumber + 1;
}

template <typename T, typename PComparator>
int Heap<T, PComparator>::getMinChildIndex(int parentIndex) const { //finds smallest child out of all children of a parent
    int firstChildIndex = getChildIndex(parentIndex, 0);
    if (firstChildIndex >= static_cast<int>(heap.size())) { // checks if childindex is valid
        return -1;
    }

    int minChildIndex = firstChildIndex; 
    for (int i = 1; i < m; ++i) { // runs from first child index to last and if it finds one smaller replaces the minchildindex value
        int currChildIndex = getChildIndex(parentIndex, i);
        if (currChildIndex < static_cast<int>(heap.size()) && c(heap[currChildIndex], heap[minChildIndex])) {
            minChildIndex = currChildIndex;
        }
    }
    return minChildIndex;
}


// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("The heap is empty."); 
  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
  return heap[0];

}


// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(heap.empty()){
    throw std::underflow_error("The heap is empty.");
  }
  heap[0] = heap.back();
  heap.pop_back();
  if(!heap.empty()) heapifyDown(0);
}





#endif

