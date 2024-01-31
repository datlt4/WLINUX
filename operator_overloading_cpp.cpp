#include <iostream>
#include <cmath>

class ComplexNumber
{
private:
    double real;
    double imaginary;

public:
    // Constructor - Destructor
    ComplexNumber(double r = 0.0, double i = 0.0) : real{r}, imaginary{i} {}
    ComplexNumber(const ComplexNumber &c) : real{c.real}, imaginary{c.imaginary} {}
    ComplexNumber(const ComplexNumber *c) : real{c->real}, imaginary{c->imaginary} {}
    ~ComplexNumber() {}

    // Unary Operators
    ComplexNumber operator+() const; // Unary Plus
    ComplexNumber operator-() const; // Unary Minus
    ComplexNumber &operator++();     // Increment (prefix)
    ComplexNumber operator++(int);   // Increment (postfix)
    ComplexNumber &operator--();     // Decrement (prefix)
    ComplexNumber operator--(int);   // Decrement (postfix)
    // double operator*() const;        // Dereference or Indirection
    ComplexNumber *operator&(); // Address-of

    // Binary Arithmetic Operators
    ComplexNumber operator+(const ComplexNumber &other) const;
    ComplexNumber operator-(const ComplexNumber &other) const;
    ComplexNumber operator*(const ComplexNumber &other) const;
    ComplexNumber operator/(const ComplexNumber &other) const;
    ComplexNumber operator%(const ComplexNumber &other) const;

    // Binary Comparison Operators
    bool operator==(const ComplexNumber &other) const;
    bool operator!=(const ComplexNumber &other) const;
    bool operator<(const ComplexNumber &other) const;
    bool operator>(const ComplexNumber &other) const;
    bool operator<=(const ComplexNumber &other) const;
    bool operator>=(const ComplexNumber &other) const;

    // Assignment Operators
    ComplexNumber &operator=(const ComplexNumber &other);
    ComplexNumber &operator+=(const ComplexNumber &other);
    ComplexNumber &operator-=(const ComplexNumber &other);
    ComplexNumber &operator*=(const ComplexNumber &other);
    ComplexNumber &operator/=(const ComplexNumber &other);
    ComplexNumber &operator%=(const ComplexNumber &other);

    // Bitwise Operators
    ComplexNumber operator<<(int shift) const;
    ComplexNumber operator>>(int shift) const;
    ComplexNumber operator&(const ComplexNumber &other) const;
    ComplexNumber operator|(const ComplexNumber &other) const;
    ComplexNumber operator^(const ComplexNumber &other) const;
    ComplexNumber &operator&=(const ComplexNumber &other);
    ComplexNumber &operator|=(const ComplexNumber &other);
    ComplexNumber &operator^=(const ComplexNumber &other);

    // Logical Operators
    bool operator!() const;
    bool operator&&(const ComplexNumber &other) const;
    bool operator||(const ComplexNumber &other) const;

    // Subscript Operator
    double &operator[](int index);
    const double &operator[](int index) const;

    // Function Call Operator
    ComplexNumber operator()();

    // Member Access Operators
    // const ComplexNumber* operator->() const;
    // const ComplexNumber* operator->*(int) const;

    // Other Operators
    ComplexNumber operator,(const ComplexNumber &other) const;
    static void *operator new(size_t size);
    static void operator delete(void *ptr);
    friend std::ostream &operator<<(std::ostream &os, const ComplexNumber &dt);
};

// Overloading Unary Plus operator
ComplexNumber ComplexNumber::operator+() const
{
    return *this; // Unary plus has no effect, return the same complex number
}

// Overloading Unary Minus operator
ComplexNumber ComplexNumber::operator-() const
{
    return ComplexNumber(-real, -imaginary);
}

// Overloading Increment operator (pre-increment)
ComplexNumber &ComplexNumber::operator++()
{
    ++real;
    ++imaginary;
    return *this;
}

// Overloading Increment operator (post-increment)
ComplexNumber ComplexNumber::operator++(int)
{
    ComplexNumber temp(*this);
    ++real;
    ++imaginary;
    return temp;
}

// Overloading Decrement operator (pre-decrement)
ComplexNumber &ComplexNumber::operator--()
{
    --real;
    --imaginary;
    return *this;
}

// Overloading Decrement operator (post-decrement)
ComplexNumber ComplexNumber::operator--(int)
{
    ComplexNumber temp(*this);
    --real;
    --imaginary;
    return temp;
}

// // Overloading Dereference operator
// double ComplexNumber::operator*() const
// {
//     // Returning the magnitude of the complex number for simplicity
//     return std::sqrt(real * real + imaginary * imaginary);
// }

// Overloading Address-of operator
ComplexNumber *ComplexNumber::operator&()
{
    return this; // Return the address of the current complex number
}

// Overloading Addition operator
ComplexNumber ComplexNumber::operator+(const ComplexNumber &other) const
{
    return ComplexNumber(real + other.real, imaginary + other.imaginary);
}

// Overloading Subtraction operator
ComplexNumber ComplexNumber::operator-(const ComplexNumber &other) const
{
    return ComplexNumber(real - other.real, imaginary - other.imaginary);
}

// Overloading Multiplication operator
ComplexNumber ComplexNumber::operator*(const ComplexNumber &other) const
{
    return ComplexNumber(
        real * other.real - imaginary * other.imaginary,
        real * other.imaginary + imaginary * other.real);
}

// Overloading Division operator
ComplexNumber ComplexNumber::operator/(const ComplexNumber &other) const
{
    double denominator = other.real * other.real + other.imaginary * other.imaginary;
    return ComplexNumber(
        (real * other.real + imaginary * other.imaginary) / denominator,
        (imaginary * other.real - real * other.imaginary) / denominator);
}

// Overloading Modulus operator
ComplexNumber ComplexNumber::operator%(const ComplexNumber &other) const
{
    return ComplexNumber(std::sqrt(real * real + imaginary * imaginary), 0);
}

// Overloading Equality operator
bool ComplexNumber::operator==(const ComplexNumber &other) const
{
    return (real == other.real) && (imaginary == other.imaginary);
}

// Overloading Inequality operator
bool ComplexNumber::operator!=(const ComplexNumber &other) const
{
    return !(*this == other);
}

// Overloading Less than operator
bool ComplexNumber::operator<(const ComplexNumber &other) const
{
    // Compare based on magnitude for simplicity
    return ((*this % *this).real < (other % other).real);
}

// Overloading Greater than operator
bool ComplexNumber::operator>(const ComplexNumber &other) const
{
    return !(*this <= other);
}

// Overloading Less than or equal to operator
bool ComplexNumber::operator<=(const ComplexNumber &other) const
{
    return (*this < other) || (*this == other);
}

// Overloading Greater than or equal to operator
bool ComplexNumber::operator>=(const ComplexNumber &other) const
{
    return !(*this < other);
}

// Overloading Assignment operator
ComplexNumber &ComplexNumber::operator=(const ComplexNumber &other)
{
    if (this != &other)
    { // Avoid self-assignment
        real = other.real;
        imaginary = other.imaginary;
    }
    return *this;
}

// Overloading Add and Assign operator
ComplexNumber &ComplexNumber::operator+=(const ComplexNumber &other)
{
    real += other.real;
    imaginary += other.imaginary;
    return *this;
}

// Overloading Subtract and Assign operator
ComplexNumber &ComplexNumber::operator-=(const ComplexNumber &other)
{
    real -= other.real;
    imaginary -= other.imaginary;
    return *this;
}

// Overloading Multiply and Assign operator
ComplexNumber &ComplexNumber::operator*=(const ComplexNumber &other)
{
    double resultReal = (real * other.real) - (imaginary * other.imaginary);
    double resultImaginary = (real * other.imaginary) + (imaginary * other.real);
    real = resultReal;
    imaginary = resultImaginary;
    return *this;
}

// Overloading Divide and Assign operator
ComplexNumber &ComplexNumber::operator/=(const ComplexNumber &other)
{
    double denominator = (other.real * other.real) + (other.imaginary * other.imaginary);
    double resultReal = ((real * other.real) + (imaginary * other.imaginary)) / denominator;
    double resultImaginary = ((imaginary * other.real) - (real * other.imaginary)) / denominator;
    real = resultReal;
    imaginary = resultImaginary;
    return *this;
}

// Overloading Modulus and Assign operator
ComplexNumber &ComplexNumber::operator%=(const ComplexNumber &other)
{
    // Modify based on your requirement for modulus assignment
    double modulus = std::sqrt(real * real + imaginary * imaginary);
    real = modulus;
    imaginary = 0.0;
    return *this;
}

// Overloading Left shift operator
ComplexNumber ComplexNumber::operator<<(int shift) const
{
    return ComplexNumber((long long)real << shift, (long long)imaginary << shift);
}

// Overloading Right shift operator
ComplexNumber ComplexNumber::operator>>(int shift) const
{
    return ComplexNumber((long long)real >> shift, (long long)imaginary >> shift);
}

// Overloading Bitwise AND operator
ComplexNumber ComplexNumber::operator&(const ComplexNumber &other) const
{
    return ComplexNumber((long long)real & (long long)other.real, (long long)imaginary & (long long)other.imaginary);
}

// Overloading Bitwise OR operator
ComplexNumber ComplexNumber::operator|(const ComplexNumber &other) const
{
    return ComplexNumber((long long)real | (long long)other.real, (long long)imaginary | (long long)other.imaginary);
}

// Overloading Bitwise XOR operator
ComplexNumber ComplexNumber::operator^(const ComplexNumber &other) const
{
    return ComplexNumber((long long)real ^ (long long)other.real, (long long)imaginary ^ (long long)other.imaginary);
}

// Overloading Bitwise AND and Assign operator
ComplexNumber &ComplexNumber::operator&=(const ComplexNumber &other)
{
    real = (long long)real & (long long)other.real;                // real &= other.real;
    imaginary = (long long)imaginary & (long long)other.imaginary; // imaginary &= other.imaginary;
    return *this;
}

// Overloading Bitwise OR and Assign operator
ComplexNumber &ComplexNumber::operator|=(const ComplexNumber &other)
{
    real = (long long)real | (long long)other.real;                // real |= (long long)other.real;
    imaginary = (long long)imaginary | (long long)other.imaginary; // imaginary |= (long long)other.imaginary;
    return *this;
}

// Overloading Bitwise XOR and Assign operator
ComplexNumber &ComplexNumber::operator^=(const ComplexNumber &other)
{
    real = (long long)real ^ (long long)other.real;                // real ^= (long long)other.real;
    imaginary = (long long)imaginary ^ (long long)other.imaginary; // imaginary ^= (long long)other.imaginary;
    return *this;
}

// Overloading Logical NOT operator
bool ComplexNumber::operator!() const
{
    // Considering the modulus as a condition
    return std::abs(real) < 1e-6 && std::abs(imaginary) < 1e-6;
}

// Overloading Logical AND operator
bool ComplexNumber::operator&&(const ComplexNumber &other) const
{
    // Considering the modulus as a condition
    return !(*this) && !(other);
}

// Overloading Logical OR operator
bool ComplexNumber::operator||(const ComplexNumber &other) const
{
    // Considering the modulus as a condition
    return !(*this) || !(other);
}

// Overloading Subscript operator
double &ComplexNumber::operator[](int index)
{
    if (index == 0)
    {
        return real;
    }
    else if (index == 1)
    {
        return imaginary;
    }
    else
    {
        // Handle out-of-range condition or throw an exception
        throw std::out_of_range("Invalid index for ComplexNumber");
    }
}

// Overloading Subscript operator for const objects
const double &ComplexNumber::operator[](int index) const
{
    if (index == 0)
    {
        return real;
    }
    else if (index == 1)
    {
        return imaginary;
    }
    else
    {
        // Handle out-of-range condition or throw an exception
        throw std::out_of_range("Invalid index for ComplexNumber");
    }
}

// Overloading Function Call Operator
ComplexNumber ComplexNumber::operator()()
{
    // Example of a function call operation (returning a copy of the complex number)
    return *this;
}

// Overloading Comma Operator
ComplexNumber ComplexNumber::operator,(const ComplexNumber &other) const
{
    // Example of comma operator (returning the second complex number)
    return other;
}

// Overloading Dynamic Memory Allocation (new)
void *ComplexNumber::operator new(size_t size)
{
    // Example of dynamic memory allocation
    return ::operator new(size);
}

// Overloading Dynamic Memory Deallocation (delete)
void ComplexNumber::operator delete(void *ptr)
{
    // Example of dynamic memory deallocation
    ::operator delete(ptr);
}

// Overload the insertion                                                  operator to recognize an ostream object on the left
std::ostream &operator<<(std::ostream &os, const ComplexNumber &C)
{
    os << C.real << "+";
    if (C.imaginary < 0)
        os << "(" << C.imaginary << ")i";
    else
        os << C.imaginary << "i";
    return os;
}

int main()
{
    {
        ComplexNumber a(2.0, 3.0);
        std::cout << "a: " << a << std::endl;

        // Unary Plus
        ComplexNumber b = +a;
        std::cout << "Unary Plus: a: " << a << ", b: " << b << std::endl;

        // Unary Minus
        ComplexNumber c = -a;
        std::cout << "Unary Minus: a: " << a << ", c: " << c << std::endl;

        // Pre-increment
        ComplexNumber d = ++a;
        std::cout << "Pre-increment: a: " << a << ", d: " << d << std::endl;

        // Post-increment
        ComplexNumber e = a++;
        std::cout << "Post-increment: a: " << a << ", e: " << e << std::endl;

        // Pre-decrement
        ComplexNumber f = --a;
        std::cout << "Pre-decrement: a: " << a << ", f: " << f << std::endl;

        // Post-decrement
        ComplexNumber g = a--;
        std::cout << "Post-decrement: a: " << a << ", g: " << g << std::endl;

        // // Dereference
        // double magnitude = *a;
        // std::cout << "Dereference (Magnitude): " << magnitude << std::endl;

        // Address-of
        ComplexNumber *ptr = &a;
        std::cout << "Address-of: " << ptr << std::endl;
    }
    std::cout << "------------------------------\n";
    {
        ComplexNumber a(2.0, 3.0);
        ComplexNumber b(1.0, 2.0);

        // Addition
        ComplexNumber c = a + b;
        std::cout << "Addition: a: " << a << ", b: " << b << ", c: " << c << std::endl;

        // Subtraction
        ComplexNumber d = a - b;
        std::cout << "Subtraction: a: " << a << ", b: " << b << ", d: " << d << std::endl;

        // Multiplication
        ComplexNumber e = a * b;
        std::cout << "Multiplication: a: " << a << ", b: " << b << ", e: " << e << std::endl;

        // Division
        ComplexNumber f = a / b;
        std::cout << "Division: a: " << a << ", b: " << b << ", f: " << f << std::endl;

        // Modulus
        ComplexNumber modulus = a % b;
        std::cout << "Modulus: " << modulus << std::endl;
    }
    std::cout << "------------------------------\n";
    {
        ComplexNumber a(2.0, 3.0);
        ComplexNumber b(1.0, 2.0);
        ComplexNumber c(2, 3);

        // Equality
        bool isEqual = (a == b);
        std::cout << "a: " << a << ", b: " << b << " equality: " << (isEqual ? "true" : "false") << std::endl;
        std::cout << "a: " << a << ", c: " << c << " equality: " << ((a == c) ? "true" : "false") << std::endl;

        // Inequality
        bool isNotEqual = (a != b);
        std::cout << "a: " << a << ", b: " << b << " inequality: " << (isNotEqual ? "true" : "false") << std::endl;
        std::cout << "a: " << a << ", c: " << c << " inequality: " << ((a != c) ? "true" : "false") << std::endl;

        // Less than
        bool isLessThan = (a < b);
        std::cout << "a: " << a << ", b: " << b << " less than: " << (isLessThan ? "true" : "false") << std::endl;
        std::cout << "a: " << a << ", c: " << c << " less than: " << ((a < c) ? "true" : "false") << std::endl;

        // Greater than
        bool isGreaterThan = (a > b);
        std::cout << "a: " << a << ", b: " << b << " greater than: " << (isGreaterThan ? "true" : "false") << std::endl;
        std::cout << "a: " << a << ", c: " << c << " greater than: " << ((a > c) ? "true" : "false") << std::endl;

        // Less than or equal to
        bool isLessThanOrEqual = (a <= b);
        std::cout << "a: " << a << ", b: " << b << " less than or equal to: " << (isLessThanOrEqual ? "true" : "false") << std::endl;
        std::cout << "a: " << a << ", c: " << c << " less than or equal to: " << ((a <= c) ? "true" : "false") << std::endl;

        // Greater than or equal to
        bool isGreaterThanOrEqual = (a >= b);
        std::cout << "a: " << a << ", b: " << b << " greater than or equal to: " << (isGreaterThanOrEqual ? "true" : "false") << std::endl;
        std::cout << "a: " << a << ", c: " << c << " greater than or equal to: " << ((a >= c) ? "true" : "false") << std::endl;
    }
    std::cout << "------------------------------\n";
    {
        ComplexNumber a(2.0, 3.0);

        // Assignment
        ComplexNumber c;
        c = a;
        std::cout << "Assignment: a: " << a << ", c: " << c << std::endl;

        // Add and Assign
        ComplexNumber d(1.0, 1.0);
        d += a;
        std::cout << "Add and Assign: a: " << a << ", d: " << d << std::endl;

        // Subtract and Assign
        ComplexNumber e(1.0, 1.0);
        e -= a;
        std::cout << "Subtract and Assign: a: " << a << ", e: " << e << std::endl;

        // Multiply and Assign
        ComplexNumber f(2.0, 2.0);
        f *= a;
        std::cout << "Multiply and Assign: a: " << a << ", f: " << f << std::endl;

        // Divide and Assign
        ComplexNumber g(2.0, 2.0);
        g /= a;
        std::cout << "Divide and Assign: a: " << a << ", g: " << g << std::endl;

        // Modulus and Assign
        ComplexNumber h(3.0, 4.0);
        h %= a;
        std::cout << "Modulus and Assign: a: " << a << ", h: " << h << std::endl;
    }
    std::cout << "------------------------------\n";
    {
        ComplexNumber a(5, 3);
        ComplexNumber b(3, 2);

        // Left shift
        ComplexNumber c = a << 1;
        std::cout << "Left shift: a: " << a << ", b: " << b << ", c: " << c << std::endl;

        // Right shift
        ComplexNumber d = a >> 1;
        std::cout << "Right shift: a: " << a << ", b: " << b << ", d: " << d << std::endl;

        // Bitwise AND
        ComplexNumber e = a & b;
        std::cout << "Bitwise AND: a: " << a << ", b: " << b << ", e: " << e << std::endl;

        // Bitwise OR
        ComplexNumber f = a | b;
        std::cout << "Bitwise OR: a: " << a << ", b: " << b << ", f: " << f << std::endl;

        // Bitwise XOR
        ComplexNumber g = a ^ b;
        std::cout << "Bitwise XOR: a: " << a << ", b: " << b << ", g: " << g << std::endl;

        // Bitwise AND and Assign
        a &= b;
        std::cout << "Bitwise AND and Assign: a: " << a << ", b: " << b << std::endl;

        // Bitwise OR and Assign
        a |= b;
        std::cout << "Bitwise OR and Assign: a: " << a << ", b: " << b << std::endl;

        // Bitwise XOR and Assign
        a ^= b;
        std::cout << "Bitwise XOR and Assign: a: " << a << ", b: " << b << std::endl;
    }
    std::cout << "------------------------------\n";
    {
        ComplexNumber a(0.0, 0.0);
        ComplexNumber b(3.0, 4.0);

        // Logical NOT
        bool notA = !a;
        std::cout << "a: " << a << ", b: " << b << "  logical NOT for a: " << std::boolalpha << notA << std::endl;

        // Logical NOT
        bool notB = !b;
        std::cout << "a: " << a << ", b: " << b << "  logical NOT for b: " << std::boolalpha << notB << std::endl;

        // Logical AND
        bool andResult = a && b;
        std::cout << "a: " << a << ", b: " << b << "  logical AND: " << std::boolalpha << andResult << std::endl;

        // Logical OR
        bool orResult = a || b;
        std::cout << "a: " << a << ", b: " << b << "  logical OR: " << std::boolalpha << orResult << std::endl;
    }
    std::cout << "------------------------------\n";
    {
        ComplexNumber a(2.0, 3.0);

        // Access real and imaginary parts using subscript operator
        std::cout << "Real part: " << a[0] << "; Imaginary part: " << a[1] << std::endl;

        // Modify real and imaginary parts using subscript operator
        a[0] = 5.0;
        a[1] = -2.0;

        // Display the modified complex number
        std::cout << "Modified Complex Number: a: " << a << std::endl;
    }
    std::cout << "------------------------------\n";
    {
        ComplexNumber a(2.0, 3.0);

        // Function Call Operator
        ComplexNumber b = a();
        std::cout << "Function Call Operator Result: a: " << a << ", b: " << b << std::endl;
    }
    std::cout << "------------------------------\n";
    {
        ComplexNumber a(2.0, 3.0);
        ComplexNumber b(1.0, 2.0);

        // Comma Operator
        ComplexNumber c = (a, b);
        std::cout << "Comma Operator Result: a: " << a << ", b: " << b << ", c: " << c << std::endl;

        // Dynamic Memory Allocation (new)
        ComplexNumber *dynamicObject = new ComplexNumber(4.0, 5.0);
        std::cout << "Dynamic Memory Allocation Result: " << *dynamicObject << std::endl;
        delete dynamicObject; // Dynamic Memory Deallocation (delete)
    }
    std::cout << "------------------------------\n";
    return 0;
}
// clang++ ./operator_overloading.cpp -o app && ./app
// g++ ./operator_overloading.cpp -o app && ./app
