# Task 1

The runtime on stack vs heap allocation was significant. Running a for loop with 1 billion iterations and `size = 10000` on the following code:

```cpp
std::array<int, size> arr1;
```

Time taken on 1.000.000.000 iterations: 2.12179 seconds

```cpp
std::array<int, size>* arr2 = new std::array<int, size>;
delete arr2;
```

Time taken on 1.000.000.000 iterations: 20.2793 seconds


# Task 2

> a) Hva skjer når vektorens lengde overskrider kapasiteten til arrayet?

When the length of the vector surpasses the assigned array, it allocates more memory by doubeling the capacity. 

> b) Hva skjer nå med size() og capacity()?

After reserving the vector has a capacity of 20, we do not need to reallocate whenever the vector gets full. 

> c) Hva skjer hvis vi istedenfor benytter medlemsfunksjonen resize(20)? 

If we use the resize function, the vector will be resized to 20 elements. If the vector is smaller than 20, it will be filled with 0. If the vector is larger than 20, the elements will be truncated.


> d) Hvor lang tid tar det å pushe 1.000.000 elementer til en vector?

0.027541 seconds

> e) Hva om vi bruker resize(1.000.000) og reserve(1.000.000) før vi pusher elementene?

resize : 0.035726 seconds
reserve: 0.013925 seconds
