#pragma once
#include "sequence.h"
#include "dynamic_array.h"
template <typename T>
class ArraySequence : public Sequence<T> {
private:
    DynamicArray<T> array_;
    
public:
    ArraySequence() = default;
    ArraySequence(size_t lenght);
    ArraySequence(const ArraySequence<T>& array) = default;
    ArraySequence(const Sequence<T>& sequence);
    T& Get(size_t index) override;
    T& GetLast() override;
    T& GetFirst() override;
    const T& Get(size_t index) const override;
    const T& GetLast() const override;
    const T& GetFirst() const override;
    size_t GetLenght() const override;
    Sequence<T>* GetSubsequence(size_t start_index, size_t end_index) override;
    void Append(const T& item) override;
    void Prepend(const T& item) override;
    void InsertAt(const T& item, size_t index) override;
    Sequence<T>* Concat(const Sequence<T>& sequence1, const Sequence<T>& sequence2) override;
    virtual ArraySequence<T>* Instanse();
};
template <typename T>
ArraySequence<T>::ArraySequence(size_t lenght) : array_(lenght) {
}

template <typename T>
ArraySequence<T>::ArraySequence(const Sequence<T>& sequence) : array_(sequence.GetLenght()) {
  for (size_t i = 0; i < sequence.GetLenght(); ++i) {
    array_.Set(i, sequence.Get(i));
  }
}

template <typename T>
T& ArraySequence<T>::Get(size_t index) {
  return array_.Get(index);
}

template <typename T>
const T& ArraySequence<T>::Get(size_t index) const {
  return array_.Get(index);
}

template <typename T>
T& ArraySequence<T>::GetLast() {
  return array_.GetLast();
}

template <typename T>
const T& ArraySequence<T>::GetLast() const {
  return array_.GetLast();
}

template <typename T>
T& ArraySequence<T>::GetFirst() {
  return array_.GetFirst();
}

template <typename T>
const T& ArraySequence<T>::GetFirst() const {
  return array_.GetFirst();
}

template <typename T>
size_t ArraySequence<T>::GetLenght() const {
  return array_.GetLenght();
}

template <typename T>
Sequence<T>* ArraySequence<T>::GetSubsequence(size_t start_index, size_t end_index) {
  ArraySequence<T>* new_array = new ArraySequence<T>(end_index - start_index);
  for (size_t i = start_index; i < end_index; ++i) {
    new_array->array_.Set(i - start_index, array_.Get(i));
  }
  return new_array;
}

template <typename T>
void ArraySequence<T>::Append(const T& item) {
    array_.Append(item);
}

template <typename T>
void ArraySequence<T>::Prepend(const T& item) {
    array_.Prepend(item);
}

template <typename T>
void ArraySequence<T>::InsertAt(const T& item, size_t index) {
    array_.InsertAt(item, index);
}

template <typename T>
Sequence<T>* ArraySequence<T>::Concat(const Sequence<T>& sequence1, const Sequence<T>& sequence2) {
    ArraySequence* new_array = Instanse();
    for (size_t i = 0; i < sequence1.GetLenght(); ++i) {
        new_array->array_.Set(i, sequence1.Get(i));
    }
    for (size_t i = 0; i < sequence2.GetLenght(); ++i) {
        new_array->array_.Set(sequence1.GetLenght() + i, sequence2.Get(i));
    }
    return new_array;
}
