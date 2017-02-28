#include <iostream>
#include <string>
#include <sstream>
#include <limits>

class Complex {
    friend std::ostream& operator<<(std::ostream& os, const Complex& rhs);
    friend std::istream& operator>>(std::istream& os, const Complex& rhs);
public:
    Complex() : 
        m_real(0.0),
        m_imaginary(0.0)
    {}
    Complex(double real, double imaginary) :
        m_real(real),
        m_imaginary(imaginary)
    {}
    ~Complex() {}

    Complex operator+(const Complex& rhs) const {
        return Complex(m_real + rhs.m_real, m_imaginary + rhs.m_imaginary);
    }
    Complex operator-(const Complex& rhs) const {
        return Complex(m_real - rhs.m_real, m_imaginary - rhs.m_imaginary);
    }

    Complex operator*(const Complex& rhs) const {
        return Complex(m_real * rhs.m_real - m_imaginary * rhs.m_imaginary, m_real * rhs.m_imaginary + m_imaginary * rhs.m_real);
    }
    Complex operator/(const Complex& rhs) const {
        double denom = rhs.m_real * rhs.m_real + rhs.m_imaginary * rhs.m_imaginary;
        return Complex((m_real * rhs.m_real + m_imaginary * rhs.m_imaginary) / denom, (m_imaginary * rhs.m_real - m_real * rhs.m_imaginary) / denom);
    }

    double real() const {
        return m_real;
    }
    double imaginary() const {
        return m_imaginary;
    }
    double modulus() const {
        return std::sqrt(m_real * m_real + m_imaginary * m_imaginary);
    }
    double arg() const {
        return std::atan2(m_imaginary, m_real);
    }
    
    Complex conjugate() const {
        return Complex(m_real, -1.0 * m_imaginary);
    }
private:
    double m_real;
    double m_imaginary;
};

std::ostream& operator<<(std::ostream& os, const Complex& rhs) {
    if (rhs.m_imaginary >= 0.0) {
        os << rhs.m_real << " + " << rhs.m_imaginary << "i";
    } else {
        os << rhs.m_real << " - " << -1.0 * rhs.m_imaginary << "i";
    }
    return os;
}

std::istream& operator>>(std::istream& is, Complex& rhs) {
    std::string temp;
    std::stringstream sstream;
    double real, imaginary;
    bool negative = false;

    // Attempt to acquire valid real.
    is >> temp;
    sstream = std::stringstream(temp);
    sstream >> real;
    if (sstream.fail()) return is;

    temp = "";

    // Attempt to acquire valid operator.
    is >> temp;
    if (temp == "-") {
        negative = true;
    } else if (temp != "+") {
        return is;
    }
    
    temp = "";

    // Attempt to acquire valid imaginary.
    is >> temp;
    sstream = std::stringstream(temp);
    sstream >> imaginary;
    if (sstream.fail()) return is;

    rhs = { real, negative ? -1.0 * imaginary : imaginary };
    return is;
}

void print(Complex c) {
    std::cout << c << ": " << std::endl;
    std::cout << "    Real Part:      " << c.real() << std::endl;
    std::cout << "    Imaginary Part: " << c.imaginary() << std::endl;
    std::cout << "    Conjugate:      " << c.conjugate() << std::endl;
    std::cout << "    Modulus:        " << c.modulus() << std::endl;
    std::cout << "    Argument:       " << c.arg() << std::endl;
}

int main() {
    Complex complex = { 3.0, 4.0 };
    Complex complex2 = { 1.0, -2.0 };

    print(complex);
    std::cout << std::endl;
    print(complex2);
    std::cout << std::endl;
    std::cout << complex + complex2 << std::endl;
    std::cout << std::endl;
    std::cout << complex - complex2 << std::endl;
    std::cout << std::endl;
    std::cout << complex * complex2 << std::endl;
    std::cout << std::endl;
    std::cout << complex / complex2 << std::endl;
    std::cout << std::endl;

    std::stringstream sstream("1 + 10i");
    Complex complex3;
    sstream >> complex3;
    print(complex3);

    std::cout << std::endl << "Press any key to exit..." << std::endl;
    getchar();
    return 0;
}
