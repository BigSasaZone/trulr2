#pragma once
#include "link_sequence.h"

template<typename T>
class ImmutableLinkSequence : LinkSequence{
private:
    DynamicArray<T> imut_link_;
public:
    ImmutableLinkSequence() = default;
    ImmutableLinkSequence(size_t lenght);
    ImmutableLinkSequence(const LinkSequence<T>& array) = default;
    ImmutableLinkSequence(const Sequence<T>& sequence);
    ImmutableLinkSequence<T>* Instance();
};

template <typename T>
ImmutableLinkSequence<T>::ImmutableLinkSequence(size_t lenght) : imut_link_(lenght){}

template <typename T>
ImmutableLinkSequence<T>::ImmutableLinkSequence(const Sequence<T>& sequence):imut_link_(sequence.GetLenght()) {
    for (size_t i = 0; i < sequence.GetLenght(); ++i) {
        imut_link_.InsertAt(sequence.Get(i), i);
    }
}

template <typename T>
ImmutableLinkSequence<T>* ImmutableLinkSequence<T>::Instance(){
    return new ImmutableLinkSequence();
}
