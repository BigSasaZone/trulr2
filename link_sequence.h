#pragma once
#include "sequence.h"
#include "linked_list.h"

template <typename T>
class LinkSequence : public Sequence<T> {
 private:
  LinkedList<T> list_;

 public:
    LinkSequence() = default;
    LinkSequence(size_t lenght);
    LinkSequence(const LinkSequence<T>& sequence) = default;
    LinkSequence(const Sequence<T>& sequence);
    ~LinkSequence();
    T& Get(size_t index) override;
    const T& Get(size_t index) const override;
    T& GetLast() override;
    const T& GetLast() const override;
    T& GetFirst() override;
    const T& GetFirst() const override;
    size_t GetLenght() const override;
    Sequence<T>* GetSubsequence(size_t start_index, size_t end_index) override;
    void Append(const T& item) override;
    void Prepend(const T& item) override;
    void InsertAt(const T& item, size_t index) override;
    Sequence<T>* Concat(const Sequence<T>& sequence1, const Sequence<T>& sequence2) override;
    virtual LinkSequence<T>* Instanse();
};

template <typename T>
LinkSequence<T>::LinkSequence(size_t lenght) : list_(lenght) {
}

template <typename T>
LinkSequence<T>::LinkSequence(const Sequence<T>& sequence) : list_(0) {
  for (size_t i = 0; i < sequence.GetLenght(); ++i) {
    list_.Append(sequence.Get(i));
  }
}

template <typename T>
LinkSequence<T>::~LinkSequence() {
}

template <typename T>
T& LinkSequence<T>::Get(size_t index) {
  return list_.Get(index);
}

template <typename T>
const T& LinkSequence<T>::Get(size_t index) const {
  return list_.Get(index);
}

template <typename T>
T& LinkSequence<T>::GetLast() {
  return list_.GetLast();
}

template <typename T>
const T& LinkSequence<T>::GetLast() const {
  return list_.GetLast();
}

template <typename T>
T& LinkSequence<T>::GetFirst() {
  return list_.GetFirst();
}

template <typename T>
const T& LinkSequence<T>::GetFirst() const {
  return list_.GetFirst();
}

template <typename T>
size_t LinkSequence<T>::GetLenght() const {
  return list_.GetLenght();
}

template <typename T>
Sequence<T>* LinkSequence<T>::GetSubsequence(size_t start_index, size_t end_index) {
  LinkSequence<T>* new_list = new LinkSequence<T>;
  for (size_t i = start_index; i < end_index; ++i) {
    new_list->list_.Append(list_.Get(i));
  }
  return new_list;
}

template <typename T>
void LinkSequence<T>::Append(const T& item) {
  list_.Append(item);
}

template <typename T>
void LinkSequence<T>::Prepend(const T& item) {
  list_.Prepend(item);
}

template <typename T>
void LinkSequence<T>::InsertAt(const T& item, size_t index) {
  list_.InsertAt(item, index);
}

template <typename T>
Sequence<T>* LinkSequence<T>::Concat(const Sequence<T>& sequence1, const Sequence<T>& sequence2) {
    LinkSequence* new_list = Instanse();
    for (size_t i = 0; i < sequence1.GetLenght(); ++i) {
        new_list->list_.Append(sequence1.Get(i));
    }
    for (size_t i = 0; i < sequence2.GetLenght(); ++i) {
    new_list->list_.Append(sequence2.Get(i));
    }
    return new_list;
}
