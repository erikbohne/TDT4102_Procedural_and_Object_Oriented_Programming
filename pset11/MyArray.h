#pragma once

template <typename Type, int Size>
class MyArray {

private:
    Type elements[Size];

public:

    int getSize() const {
        return Size;
    }

    Type& at(int index) const {
        if (index < 0 || index >= Size) {
            throw std::out_of_range("Index out of bounds");
        }
        return const_cast<Type&>(elements[index]);
    }

    void fill(Type value) {
        for (int i = 0; i < Size; ++i) {
            elements[i] = value;
        }
    }
};