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

# Task 3

> a) Ta tiden på hele programmet før optimalisering.

Time taken: 8.13712 seconds

> b) Ta tiden etter optimalisering. Noter endringer.

First change was removing the for loop that set the column values to 0.0 to this

```cpp
column.resize(matrixSize, 0.0);
```

New time taken: 5.23663 seconds

Next change is going from this:

```cpp
double sumMatrix(std::vector<std::vector<double>> matrix){
    double sum;
    for (int col = 0; col < matrix.size(); col++){
        for (int row = 0; row < matrix.size(); row++){
            double value = matrix.at(row).at(col);
            sum += value;            
        }
    }
    return sum;
}
```

to this:

```cpp
double sumMatrix(const std::vector<std::vector<double>>& matrix) {
    double sum = 0.0;
    for (const auto& row : matrix) {
        for (double value : row) {
            sum += value;
        }
    }
    return sum;
}
```

Changing the for loop to use a range-based for loop and using a reference to the matrix instead of copying it.

New time taken: 2.66229 seconds


Last change will be from this:

```cpp
void setDiagonalValue(std::vector<std::vector<double>>& matrix, double newValue){
    for (int row = 0; row < matrix.size(); row++){
        for (int col = 0; col < matrix.size(); col++){
            bool isDiagonal = (row == col);
            if (isDiagonal){
                matrix.at(row).at(col) = newValue;
            }
        }
    }
}
```

to this:

```cpp
void setDiagonalValue(std::vector<std::vector<double>>& matrix, double newValue) {
    for (int i = 0; i < minDimension; ++i) {
        matrix[i][i] = newValue;
    }
}
```

This will only iterate over the diagonal elements of the matrix. We also use direct access instead of .at().

New time taken: 2.48834 seconds



> c) Skru på kompilatoroptimalisering. Hva skjer med tiden?

SUPER SPEEEEEEEEEEED SUPER FAAAAAAST

Time taken: 0.250721 seconds
