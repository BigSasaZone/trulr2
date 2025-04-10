#pragma once
#include "array_sequence.h"

template<typename T>
class ImmutableArraySequence : LinkSequence{
private:
    DynamicArray<T> imut_array_;
public:
    ImmutableArraySequence() = default;
    ImmutableArraySequence(size_t lenght);
    ImmutableArraySequence(const ArraySequence<T>& array) = default;
    ImmutableArraySequence(const Sequence<T>& sequence);
    ImmutableArraySequence<T>* Instance();
};

template <typename T>
ImmutableArraySequence<T>::ImmutableArraySequence(size_t lenght) : imut_array_(lenght){}

template <typename T>
ImmutableArraySequence<T>::ImmutableArraySequence(const Sequence<T>& sequence):imut_array_(sequence.GetLenght()) {
    for (size_t i = 0; i < sequence.GetLenght(); ++i) {
        imut_array_.Set(i, sequence.Get(i));
    }
}

template <typename T>
ImmutableArraySequence<T>* ImmutableArraySequence<T>::Instance(){
    return new ImmutableArraySequence();
}
