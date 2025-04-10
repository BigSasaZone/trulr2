#pragma once
#include <cstddef>
#include <stdexcept>

template <typename T>
class LinkedList {
 private:
  struct Node_ {
    T data;
    Node_* next;
    Node_* prev;
  };

 private:
  Node_* head_;
  Node_* tail_;
  size_t lenght_;

 public:
    LinkedList();
    LinkedList(size_t lenght);
    LinkedList(const LinkedList& other);
    LinkedList(const T* items, size_t count);
    T& Get(size_t index);
    const T& Get(size_t index) const;
    T& GetLast();
    const T& GetLast() const;
    T& GetFirst();
    const T& GetFirst() const;
    size_t GetLenght() const;
    bool IsEmpty() const;
    void Append(const T& item);
    void Prepend(const T& item);
    void InsertAt(const T& item, size_t index);
    template <class Predicate>
    LinkedList<T> Where(const Predicate& predicate) const;
    template <class Unary>
    LinkedList<T> Map(const Unary& unary) const;
};

template <typename T>
LinkedList<T>::LinkedList() : head_(nullptr), tail_(nullptr), lenght_(0) {
}

template <typename T>
LinkedList<T>::LinkedList(size_t lenght) : head_(nullptr), tail_(nullptr), lenght_(0) {
  for (size_t i = 0; i < lenght; ++i) {
    Append(T());
  }
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList& other) : head_(nullptr), tail_(nullptr), lenght_(other.lenght_) {
  if (lenght_ == 0) {
    return;
  }
  head_ = new Node_{other.head_->data, nullptr, nullptr};
  tail_ = head_;
  Node_* current_node = other.head_->next;
  while (current_node != nullptr) {
    tail_->next = new Node_{current_node->data, nullptr, tail_};
    tail_ = tail_->next;
    current_node = current_node->next;
  }
}

template <typename T>
LinkedList<T>::LinkedList(const T* items, size_t count) : head_(nullptr), tail_(nullptr), lenght_(count) {
  if (lenght_ == 0) {
    return;
  }
  head_ = new Node_{items[0], nullptr, nullptr};
  tail_ = head_;
  for (size_t i = 1; i < count; ++i) {
    tail_->next = new Node_{items[i], nullptr, tail_};
    tail_ = tail_->next;
  }
}

template <typename T>
bool LinkedList<T>::IsEmpty() const {
  return lenght_ == 0;
}

template <typename T>
void LinkedList<T>::Append(const T& item) {
  Node_* new_node = new Node_{item, nullptr, tail_};
  if (head_ == nullptr) {
    head_ = new_node;
  } else {
    tail_->next = new_node;
  }
  tail_ = new_node;
  ++lenght_;
}

template <typename T>
void LinkedList<T>::Prepend(const T& item) {
  Node_* new_node = new Node_{item, head_, nullptr};
  if (head_ != nullptr) {
    head_->prev = new_node;
  } else {
    tail_ = new_node;
  }
  head_ = new_node;
  ++lenght_;
}

template <typename T>
T& LinkedList<T>::Get(size_t index) {
  if (index >= lenght_) {
    throw std::out_of_range("Index out of range");
  }
  size_t count = 0;
  Node_* current_node = head_;
  while (true) {
    if (index == count) {
      return current_node->data;
    }
    current_node = current_node->next;
    ++count;
  }
}

template <typename T>
const T& LinkedList<T>::Get(size_t index) const {
  if (index >= lenght_) {
    throw std::out_of_range("Index out of range");
  }
  size_t count = 0;
  Node_* current_node = head_;
  while (true) {
    if (index == count) {
      return current_node->data;
    }
    current_node = current_node->next;
    ++count;
  }
}

template <typename T>
T& LinkedList<T>::GetLast() {
  if (lenght_ == 0) {
    throw std::out_of_range("List is empty");
  }
  return tail_->data;
}

template <typename T>
const T& LinkedList<T>::GetLast() const {
  if (lenght_ == 0) {
    throw std::out_of_range("List is empty");
  }
  return tail_->data;
}

template <typename T>
T& LinkedList<T>::GetFirst() {
  if (lenght_ == 0) {
    throw std::out_of_range("List is empty");
  }
  return head_->data;
}

template <typename T>
const T& LinkedList<T>::GetFirst() const {
  if (lenght_ == 0) {
    throw std::out_of_range("List is empty");
  }
  return head_->data;
}

template <typename T>
size_t LinkedList<T>::GetLenght() const {
  return lenght_;
}

template <typename T>
void LinkedList<T>::InsertAt(const T& item, size_t index) {
  if (index > lenght_) {
    throw std::out_of_range("Index Out Of Range");
  }
  if (index == 0) {
    Prepend(item);
    return;
  }
  if (index == lenght_) {
    Append(item);
    return;
  }
  Node_* current_node = head_;
  Node_* new_node = new Node_{item, nullptr, nullptr};
  for (size_t i = 0; i < index; ++i) {
    current_node = current_node->next;
  }
  new_node->next = current_node;
  new_node->prev = current_node->prev;
  new_node->prev->next = new_node;
  new_node->next->prev = new_node;
  ++lenght_;
}

template <typename T>
template <class Predicate>
LinkedList<T> LinkedList<T>::Where(const Predicate& predicate) const {
  LinkedList<T> copy_list;
  Node_* current_node = head_;
  while (current_node != nullptr) {
    if (predicate(current_node->data)) {
      copy_list.Append(current_node->data);
    }
    current_node = current_node->next;
  }
  return copy_list;
}

template <typename T>
template <class Unary>
LinkedList<T> LinkedList<T>::Map(const Unary& unary) const {
  LinkedList<T> copy_list;
  Node_* current_node = head_;
  while (current_node != nullptr) {
    copy_list.Append(current_node->data);
    unary(copy_list.GetLast());
    current_node = current_node->next;
  }
  return copy_list;
}
