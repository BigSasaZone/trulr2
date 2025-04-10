#pragma once
#include <cstddef>
#include <stdexcept>

template <typename T>
class Sequence {
public:
  virtual ~Sequence() = default;
  virtual T& Get(size_t index) = 0;
  virtual T& GetLast() = 0;
  virtual T& GetFirst() = 0;
  virtual const T& Get(size_t index) const = 0;
  virtual const T& GetLast() const = 0;
  virtual const T& GetFirst() const = 0;
  virtual size_t GetLenght() const = 0;
  virtual Sequence<T>* GetSubsequence(size_t start_index, size_t end_index) = 0;
  virtual void Append(const T& item) = 0;
  virtual void Prepend(const T& item) = 0;
  virtual void InsertAt(const T& item, size_t index) = 0;
  virtual Sequence<T>* Concat(const Sequence<T>& list1, const Sequence<T>& list2) = 0;
};
