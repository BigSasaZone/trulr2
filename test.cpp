#include <cassert>
#include "dynamic_array.h"
#include "linked_list.h"
#include "array_sequence.h"
#include "link_sequence.h"

void testDynamicArrayDefaultConstructor() {
  DynamicArray<int> arr;
  assert(arr.GetLenght() == 0);
}

void testDynamicArrayConstructorWithSize() {
  DynamicArray<int> arr(5);
  assert(arr.GetLenght() == 5);
  for (int i = 0; i < 5; ++i) {
    assert(arr.Get(i) == int());
  }
}

void testDynamicArraySetAndGet() {
  DynamicArray<int> arr(3);
  arr.Set(0, 10);
  arr.Set(1, 20);
  arr.Set(2, 30);
  assert(arr.Get(0) == 10);
  assert(arr.Get(1) == 20);
  assert(arr.Get(2) == 30);
  bool get_exception = false;
  try {
    arr.Get(3);
  } catch (std::out_of_range) {
    get_exception = true;
  }
  assert(get_exception);
  get_exception = false;
  try {
    arr.Set(3, 40);
  } catch (std::out_of_range) {
    get_exception = true;
  }
  assert(get_exception);
}

void testDynamicArrayAppend() {
  DynamicArray<int> arr;
  arr.Append(10);
  arr.Append(20);
  assert(arr.GetLenght() == 2);
  assert(arr.Get(0) == 10);
  assert(arr.Get(1) == 20);
  arr.Append(30);
  assert(arr.GetLenght() == 3);
  assert(arr.Get(2) == 30);
}

void testDynamicArrayPrepend() {
  DynamicArray<int> arr;
  arr.Prepend(10);
  arr.Prepend(20);
  assert(arr.GetLenght() == 2);
  assert(arr.Get(0) == 20);
  assert(arr.Get(1) == 10);
  arr.Prepend(30);
  assert(arr.GetLenght() == 3);
  assert(arr.Get(0) == 30);
  assert(arr.Get(1) == 20);
  assert(arr.Get(2) == 10);
}

void testDynamicArrayReSize() {
  DynamicArray<int> arr(5);
  for (int i = 0; i < 5; ++i) {
    arr[i] = i + 1;
  }
  arr.ReSize(10);
  assert(arr.GetLenght() == 10);
  for (int i = 0; i < 5; ++i) {
    assert(arr[i] == i + 1);
  }
  arr.ReSize(3);
  assert(arr.GetLenght() == 3);
  for (int i = 0; i < 3; ++i) {
    assert(arr[i] == i + 1);
  }
  bool get_exception = false;
  try {
    arr.Get(3);
  } catch (std::out_of_range) {
    get_exception = true;
  }
  assert(get_exception);
}

void testDynamicArrayReserve() {
  DynamicArray<int> arr;
  arr.Reserve(10);
  assert(arr.GetLenght() == 0);
  assert(arr.GetCapacity() == 10);
  arr.Reserve(0);
  assert(arr.GetLenght() == 0);
  assert(arr.GetCapacity() == 10);
}

void testDynamicArrayWhere() {
  DynamicArray<int> arr;
  arr.Append(10);
  arr.Append(20);
  arr.Append(30);
  arr.Append(40);

  DynamicArray<int> select_arr = arr.Where([](int value) { return value > 25; });
  assert(select_arr.GetLenght() == 2);
  assert(select_arr.Get(0) == 30);
  assert(select_arr.Get(1) == 40);
}

void testDynamicArrayMap() {
  DynamicArray<int> arr;
  arr.Append(10);
  arr.Append(20);
  arr.Append(30);
  DynamicArray<int> mapped = static_cast<DynamicArray<int>>(arr.Map([](int& value) { value += 1; }));
  assert(mapped.GetLenght() == 3);
  assert(mapped.Get(0) == 11);
  assert(mapped.Get(1) == 21);
  assert(mapped.Get(2) == 31);
}

void testLinkedListDefaultConstructor() {
  LinkedList<int> list;
  assert(list.GetLenght() == 0);
}

void testLinkedListConstructorWithSize() {
  LinkedList<int> list(5);
  assert(list.GetLenght() == 5);
  for (int i = 0; i < 5; ++i) {
    assert(list.Get(i) == int());
  }
}

void testLinkedListAppend() {
  LinkedList<int> list;
  list.Append(10);
  list.Append(20);
  assert(list.GetLenght() == 2);
  assert(list.Get(0) == 10);
  assert(list.Get(1) == 20);
  list.Append(30);
  assert(list.GetLenght() == 3);
  assert(list.Get(2) == 30);
}

void testLinkedListPrepend() {
  LinkedList<int> list;
  list.Prepend(10);
  list.Prepend(20);
  assert(list.GetLenght() == 2);
  assert(list.Get(0) == 20);
  assert(list.Get(1) == 10);
  list.Prepend(30);
  assert(list.GetLenght() == 3);
  assert(list.Get(0) == 30);
  assert(list.Get(1) == 20);
  assert(list.Get(2) == 10);
}

void testLinkedListInsertAt() {
  LinkedList<int> list;
  list.Append(10);
  list.Append(30);
  list.InsertAt(20, 1);
  assert(list.GetLenght() == 3);
  assert(list.Get(0) == 10);
  assert(list.Get(1) == 20);
  assert(list.Get(2) == 30);
  list.InsertAt(5, 0);
  assert(list.GetLenght() == 4);
  assert(list.Get(0) == 5);
  assert(list.Get(1) == 10);
  list.InsertAt(40, 4);
  assert(list.GetLenght() == 5);
  assert(list.Get(4) == 40);
  bool get_exception = false;
  try {
    list.InsertAt(50, 6);
  } catch (std::out_of_range) {
    get_exception = true;
  }
  assert(get_exception);
}

void testLinkedListWhere() {
  LinkedList<int> list;
  list.Append(11);
  list.Append(20);
  list.Append(33);
  list.Append(40);
  LinkedList<int> select_list = list.Where([](int value) { return value % 2 == 0; });
  assert(select_list.GetLenght() == 2);
  assert(select_list.Get(0) == 20);
  assert(select_list.Get(1) == 40);
}

void testLinkedListMap() {
  LinkedList<int> list;
  list.Append(10);
  list.Append(20);
  list.Append(30);
  list.Append(40);
  LinkedList<int> mapped = static_cast<LinkedList<int>>(list.Map([](int& value) { value *= 2; }));
  assert(mapped.GetLenght() == 4);
  assert(mapped.Get(0) == 20);
  assert(mapped.Get(1) == 40);
  assert(mapped.Get(2) == 60);
  assert(mapped.Get(3) == 80);
}

void testArraySequenceDefaultConstructor() {
  ArraySequence<int> arr;
  assert(arr.GetLenght() == 0);
}

void testArraySequenceConstructorWithSize() {
  ArraySequence<int> arr(5);
  assert(arr.GetLenght() == 5);
  for (int i = 0; i < 5; ++i) {
    assert(arr.Get(i) == int());
  }
}

void testArraySequenceGet() {
  ArraySequence<int> arr;
  arr.Append(10);
  arr.Append(20);
  arr.Append(30);
  assert(arr.Get(0) == 10);
  assert(arr.Get(1) == 20);
  assert(arr.Get(2) == 30);
  assert(arr.GetFirst() == 10);
  assert(arr.GetLast() == 30);
}

void testArraySequenceAppend() {
  ArraySequence<int> arr;
  arr.Append(10);
  arr.Append(20);
  arr.Append(30);
  assert(arr.Get(0) == 10);
  assert(arr.Get(1) == 20);
  assert(arr.Get(2) == 30);
  assert(arr.GetFirst() == 10);
  assert(arr.GetLast() == 30);
}

void testArraySequencePrepend() {
  ArraySequence<int> arr;
  arr.Prepend(10);
  arr.Prepend(20);
  arr.Prepend(30);
  assert(arr.Get(0) == 30);
  assert(arr.Get(1) == 20);
  assert(arr.Get(2) == 10);
  assert(arr.GetFirst() == 30);
  assert(arr.GetLast() == 10);
}

void testArraySequenceInsertAt() {
  ArraySequence<int> arr;
  arr.Append(10);
  arr.Append(20);
  arr.InsertAt(30, 1);
  assert(arr.Get(0) == 10);
  assert(arr.Get(1) == 30);
  assert(arr.Get(2) == 20);
  assert(arr.GetFirst() == 10);
  assert(arr.GetLast() == 20);
}

void testArraySequenceConcat() {
  ArraySequence<int> arr1;
  arr1.Append(10);
  arr1.Append(20);
  ArraySequence<int> arr2;
  arr2.Append(30);
  arr2.Append(40);
  ArraySequence<int>* concat_arr = dynamic_cast<ArraySequence<int>*>(arr1.Concat(arr1, arr2));
  assert(concat_arr != nullptr);
  assert(concat_arr->GetLenght() == 4);
  assert(concat_arr->Get(0) == 10);
  assert(concat_arr->Get(1) == 20);
  assert(concat_arr->Get(2) == 30);
  assert(concat_arr->Get(3) == 40);
  delete concat_arr;
}

void testArraySequenceGetSubsequence() {
  ArraySequence<int> arr;
  arr.Append(10);
  arr.Append(20);
  arr.Append(30);
  arr.Append(40);
  ArraySequence<int>* subsequence = dynamic_cast<ArraySequence<int>*>(arr.GetSubsequence(1, 3));
  assert(subsequence != nullptr);
  assert(subsequence->GetLenght() == 2);
  assert(subsequence->Get(0) == 20);
  assert(subsequence->Get(1) == 30);
  delete subsequence;
}

void testLinkSequenceDefaultConstructor() {
  LinkSequence<int> list;
  assert(list.GetLenght() == 0);
}

void testLinkSequenceConstructorWithSize() {
  LinkSequence<int> list(5);
  assert(list.GetLenght() == 5);
  for (int i = 0; i < 5; ++i) {
    assert(list.Get(i) == int());
  }
}

void testLinkSequenceGet() {
  LinkSequence<int> list;
  list.Append(10);
  list.Append(20);
  list.Append(30);
  assert(list.Get(0) == 10);
  assert(list.Get(1) == 20);
  assert(list.Get(2) == 30);
}

void testLinkSequenceAppend() {
  LinkSequence<int> list;
  list.Append(10);
  list.Append(20);
  list.Append(30);
  assert(list.Get(0) == 10);
  assert(list.Get(1) == 20);
}
void testLinkSequencePrepend() {
  LinkSequence<int> list;
  list.Prepend(10);
  list.Prepend(20);
  list.Prepend(30);
  assert(list.Get(0) == 30);
  assert(list.Get(1) == 20);
  assert(list.Get(2) == 10);
}

void testLinkSequenceInsertAt() {
  LinkSequence<int> list;
  list.Append(10);
  list.Append(30);
  list.InsertAt(20, 1);
  assert(list.Get(0) == 10);
  assert(list.Get(1) == 20);
  assert(list.Get(2) == 30);
}

void testLinkSequenceConcat() {
  LinkSequence<int> list1;
  list1.Append(10);
  list1.Append(20);
  LinkSequence<int> list2;
  list2.Append(30);
  list2.Append(40);
  LinkSequence<int>* concat_list = dynamic_cast<LinkSequence<int>*>(list1.Concat(list1, list2));
  assert(concat_list != nullptr);
  assert(concat_list->GetLenght() == 4);
  assert(concat_list->Get(0) == 10);
  assert(concat_list->Get(1) == 20);
  assert(concat_list->Get(2) == 30);
  assert(concat_list->Get(3) == 40);
  delete concat_list;
}

void testLinkSequenceGetSubsequence() {
  LinkSequence<int> list;
  list.Append(10);
  list.Append(20);
  list.Append(30);
  list.Append(40);
  LinkSequence<int>* subsequence = dynamic_cast<LinkSequence<int>*>(list.GetSubsequence(1, 3));
  assert(subsequence != nullptr);
  assert(subsequence->GetLenght() == 2);
  assert(subsequence->Get(0) == 20);
  assert(subsequence->Get(1) == 30);
  delete subsequence;
}


