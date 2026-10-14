// Name: Abrham Dawit
// CruzID: asdawit
// Winter 25 - 101
// Assignment: pa6
// BigInteger.cpp
// Implementation file for the BigInteger ADT

#include "BigInteger.h"
#include <stdexcept>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

// Constants for base conversion: BASE = 10^POWER
const long BASE = 1000000000; // 1,000,000,000
const int POWER = 9;

// Constructors
BigInteger::BigInteger() : signum(0) {
    // digits list remains empty
}
BigInteger::BigInteger(long x) {
    if (x == 0) {
        signum = 0;
    } else {
        signum = (x < 0) ? -1 : 1;
        long absx = (x < 0) ? -x : x;
        digits.clear();
        while (absx > 0) {
            long digit = absx % BASE;
            digits.moveBack();
            digits.insertAfter(digit);
            absx /= BASE;
        }
    }
}

// Constructor from string
BigInteger::BigInteger(string s) {
    if (s.size() == 0)
        throw invalid_argument("BigInteger: empty string");
    size_t start = 0;
    if (s[0] == '-') { 
        signum = -1; 
        start++; 
    } else if (s[0] == '+') { 
        signum = 1; 
        start++; 
    } else { 
        signum = 1; 
    }

    while (start < s.size() && s[start] == '0')
        start++;
    if (start == s.size()) {
        signum = 0;
        return;
    }
    digits.clear();

    size_t end = s.size();
    for (size_t i = end; i > start; ) {
        size_t j = (i >= POWER && i - POWER > start) ? i - POWER : start;
        string group = s.substr(j, i - j);
        long value = stol(group);
        digits.moveBack();
        digits.insertAfter(value);
        if (i >= POWER)
            i -= POWER;
        else
            break;
    }
}

// Copy constructor
BigInteger::BigInteger(const BigInteger& N) {
    signum = N.signum;
    digits = N.digits;
}

// Access Functions
int BigInteger::sign() const {
    return signum;
}

int BigInteger::compare(const BigInteger& N) const {
    if (signum != N.signum)
        return (signum > N.signum) ? 1 : -1;
    if (signum == 0)
        return 0;
    
    int len1 = digits.length();
    int len2 = N.digits.length();
    if (len1 != len2) {
        if (signum > 0)
            return (len1 > len2) ? 1 : -1;
        else
            return (len1 > len2) ? -1 : 1;
    }

    List copy1 = digits;
    List copy2 = N.digits;
    copy1.moveBack();
    copy2.moveBack();
    for (int i = 0; i < len1; i++) {
        long d1 = copy1.movePrev();
        long d2 = copy2.movePrev();
        if (d1 != d2)
            return (signum > 0) ? (d1 > d2 ? 1 : -1) : (d1 > d2 ? -1 : 1);
    }
    return 0;
}

// Manipulation Procedures
void BigInteger::makeZero() {
    signum = 0;
    digits.clear();
}

void BigInteger::negate() {
    if (signum != 0)
        signum = -signum;
}

// Helper Functions for Magnitude Arithmetic
List addLists(const List& A, const List& B) {
    List result;
    int lenA = A.length(), lenB = B.length();
    long carry = 0;
    List copyA = A, copyB = B;
    copyA.moveFront();
    copyB.moveFront();
    int i = 0;
    while (i < lenA || i < lenB || carry != 0) {
        long a = (i < lenA) ? copyA.moveNext() : 0;
        long b = (i < lenB) ? copyB.moveNext() : 0;
        long sum = a + b + carry;
        carry = sum / BASE;
        long digit = sum % BASE;
        result.moveBack();
        result.insertAfter(digit);
        i++;
    }
    return result;
}

List subtractLists(const List& A, const List& B) {
    List result;
    int lenA = A.length(), lenB = B.length();
    long borrow = 0;
    List copyA = A, copyB = B;
    copyA.moveFront();
    copyB.moveFront();
    int i = 0;
    while (i < lenA) {
        long a = copyA.moveNext();
        long b = (i < lenB) ? copyB.moveNext() : 0;
        long diff = a - b - borrow;
        if (diff < 0) { 
            diff += BASE; 
            borrow = 1; 
        } else { 
            borrow = 0; 
        }
        result.moveBack();
        result.insertAfter(diff);
        i++;
    }

    while (result.length() > 1) {
        result.moveBack();
        if (result.peekPrev() == 0)
            result.eraseBefore();
        else break;
    }
    return result;
}

// Arithmetic Operations
BigInteger BigInteger::add(const BigInteger& N) const {
    if (signum == 0) return N;
    if (N.signum == 0) return *this;
    BigInteger result;
    if (signum == N.signum) {
        result.digits = addLists(digits, N.digits);
        result.signum = signum;
    } else {
        BigInteger A = *this, B = N;
        A.signum = B.signum = 1;
        int cmp = A.compare(B);
        if (cmp == 0)
            result.makeZero();
        else if (cmp > 0) {
            result.digits = subtractLists(digits, N.digits);
            result.signum = signum;
        } else {
            result.digits = subtractLists(N.digits, digits);
            result.signum = N.signum;
        }
    }

    if (result.digits.length() == 0 ||
       (result.digits.length() == 1 && result.digits.front() == 0))
        result.signum = 0;
    return result;
}

BigInteger BigInteger::sub(const BigInteger& N) const {
    BigInteger negN = N;
    negN.negate();
    return add(negN);
}

BigInteger BigInteger::mult(const BigInteger& N) const {
    BigInteger result;
    if (signum == 0 || N.signum == 0) {
        result.makeZero();
        return result;
    }
    int lenA = digits.length(), lenB = N.digits.length();
    vector<long> prod(lenA + lenB, 0);
    List A = digits, B = N.digits;
    A.moveFront();
    for (int i = 0; i < lenA; i++) {
        long a = A.moveNext();
        List Bcopy = B;
        Bcopy.moveFront();
        long carry = 0;
        for (int j = 0; j < lenB; j++) {
            long b = Bcopy.moveNext();
            long temp = prod[i + j] + a * b + carry;
            prod[i + j] = temp % BASE;
            carry = temp / BASE;
        }
        prod[i + lenB] += carry;
    }

    while (prod.size() > 1 && prod.back() == 0)
        prod.pop_back();
    result.digits.clear();
    for (long d : prod) {
        result.digits.moveBack();
        result.digits.insertAfter(d);
    }
    result.signum = signum * N.signum;
    if (result.digits.length() == 1 && result.digits.front() == 0)
        result.signum = 0;
    return result;
}

// to_string: Converts the BigInteger to a base-10 string representation
std::string BigInteger::to_string() {
    if (signum == 0) return "0";
    int len = digits.length();
    vector<long> d;
    List temp = digits;
    temp.moveFront();
    for (int i = 0; i < len; i++) {
        d.push_back(temp.moveNext());
    }
    ostringstream oss;
    if (signum < 0)
        oss << "-";
    oss << d.back();
    for (int i = len - 2; i >= 0; i--) {
        oss.width(POWER);
        oss.fill('0');
        oss << d[i];
    }
    return oss.str();
}

// Overloaded Operators
std::ostream& operator<<(std::ostream& stream, BigInteger N) {
    stream << N.to_string();
    return stream;
}

bool operator==(const BigInteger& A, const BigInteger& B) {
    return A.compare(B) == 0;
}
bool operator<(const BigInteger& A, const BigInteger& B) {
    return A.compare(B) < 0;
}
bool operator<=(const BigInteger& A, const BigInteger& B) {
    return A.compare(B) <= 0;
}
bool operator>(const BigInteger& A, const BigInteger& B) {
    return A.compare(B) > 0;
}
bool operator>=(const BigInteger& A, const BigInteger& B) {
    return A.compare(B) >= 0;
}

BigInteger operator+(const BigInteger& A, const BigInteger& B) {
    return A.add(B);
}
BigInteger operator-(const BigInteger& A, const BigInteger& B) {
    return A.sub(B);
}
BigInteger operator*(const BigInteger& A, const BigInteger& B) {
    return A.mult(B);
}
BigInteger operator+=(BigInteger& A, const BigInteger& B) {
    A = A.add(B);
    return A;
}
BigInteger operator-=(BigInteger& A, const BigInteger& B) {
    A = A.sub(B);
    return A;
}
BigInteger operator*=(BigInteger& A, const BigInteger& B) {
    A = A.mult(B);
    return A;
}