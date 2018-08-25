#ifndef BIGINT_H
#define BIGINT_H

#include <iostream>
#include <vector>
#include <string>

typedef std::vector<int> DigitContainer;


class BigInt
{
public:
    BigInt();
    BigInt(std::string int_string);

    std::vector<int>    get_large_int() const;
    std::string         get_large_string() const;
    void                add_to_int(int add_this);

private:
    void    set_length(std::vector<int> &x, std::vector<int> &y);

    std::string     m_lhs, m_rhs;
    DigitContainer  m_digits;
};
BigInt operator+(const BigInt& lhs, const BigInt& rhs);
BigInt operator-(const BigInt& lhs, const BigInt& rhs);
BigInt operator*(const BigInt& lhs, const BigInt& rhs);

//create these for the program
BigInt operator<(const BigInt& lhs, const BigInt& rhs);
BigInt operator>(const BigInt& lhs, const BigInt& rhs);
BigInt operator==(const BigInt& lhs, const BigInt& rhs);

std::ostream& operator<<(std::ostream& out, const BigInt& value);

#endif // BIGINT_H
