# Notes from lecture on 9 January 2024
> TDT4102 - Prosedyre- og objektorientert programmering (C++)

### Data types
> Data types are used to define variables

#### Primitive data types
> Primitive data types are the most basic data types available

| Data type | Description |
| --------- | ----------- |
| int | Stores integers (whole numbers) |
| float | Stores floating point numbers (decimals) |
| double | Stores floating point numbers (decimals) with higher precision |
| bool | Stores boolean values (true or false) |
| char | Stores single characters |

#### Non-primitive data types
> Non-primitive data types are more complex data types

| Data type | Description |
| --------- | ----------- |
| string | Stores text |
| array | Stores multiple values in one variable |
| vector | Stores multiple values in one variable (more flexible than arrays) |
| object | Stores multiple values in one variable (more flexible than arrays) |

### Type casting
> Conversion of data types

Can be done using ecplicit casting or implicit casting.
```c++
int a = 5;
float b = 10.5;
int c = (int) b; // c = 10
float d = a; // d = 5.0
```

### Operators
> Operators are symbols that perform operations on operands

Arithmetic operators: +, -, *, /, %, ++, --
Logical operators: &&, ||, !, <, >, <=, >=, ==, !=

Examples:
```c++
int a = 5;
int b = 10;
int c = a + b; // c = 15
int e = a * b; // e = 50
int f = a / b; // f = 0
int g = a % b; // g = 5
a++; // a = 6
a--; // a = 5
bool l = a < b; // l = true
```

C++ does not have the // operator like in Python.

Good practice:
Do not use == and =! with floating point numbers, as they are not precise.

### Text output
> Output text to the console

```c++
cout << "What is your favorite food? " << endl;
string food;
cin >> food;
cout << "Your favorite food is " << food << endl;
```

`cin` is used to get input from the user. Can only be used for one word at a time. This means that if the user inputs "I like pizza", the variable `food` will only contain "I".

`getline(cin, food)` can be used to get the entire line of input.

### If statements
> Execute code if a condition is true

```c++
bool condition = true;

if (condition) {
    cout << "Condition is true" << endl;
} else {
    cout << "Condition is false" << endl;
}
```

of course it is possible to have multiple conditions:
```c++
bool condition1 = true;
bool condition2 = false;

if (condition1 && condition2) {
    cout << "Both conditions are true" << endl;
} else if (condition1 || condition2) {
    cout << "One of the conditions are true" << endl;
} else {
    cout << "Both conditions are false" << endl;
}
```

### Loops
> Execute code multiple times

#### While loop
```c++
int i = 0;
while (i < 10) {
    cout << i << endl;
    i++;
}
```
Should be used when the number of iterations is unknown.

#### Do-while loop
```c++
int i = 0;
do {
    cout << i << endl;
    i++;
} while (i < 10);
```
Should be used when the code should be executed at least once.

#### For loop
```c++
for (int i = 0; i < 10; i++) {
    cout << i << endl;
}
```
Should be used when the number of iterations is known.

### Functions
> A function is a block of code that performs a specific task

```c++
void someFunction(int parameter, bool another) {
    // do something
}
```

Example 1 (adding):
```c++
int add(int a, int b) {
    return a + b;
}
```

Example 2 (printing the addition):
```c++
void printAddition(int a, int b) {
    cout << add(a, b) << endl;
}
```

#### Declartion vs Definition
> A function declaration tells the compiler about a function's name, return type, and parameters. A function definition provides the actual body of the function.

```c++
// Declaration
void functionA();

// Definition
int functionA() {
}
```

#### Order matters
> The compiler reads the code from top to bottom. This means that if a function is called before it is defined, the compiler will not know what to do.


