#include "bigint.h"
#include <algorithm>

BigInt::BigInt()
{

}

BigInt::BigInt(std::string int_string1)
{
    //-----The magic for loops that set the chars to ints-----
    for (int i = int_string1.size() - 1; i >= 0; i--)
        if (int_string1[i] > 57 || int_string1[i] < 48)
            std::cout << "ERROR: Invalid Digit was inputted, it will be ignored." << std::endl;
        else
            m_digits.push_back(static_cast<int>(int_string1[i]) - 48);
    //--------------------end of magic----------------------
}

std::vector<int> BigInt::get_large_int() const
{
    return m_digits;
}

std::string BigInt::get_large_string() const
{
    std::string return_string;
    int tmp_size = m_digits.size()-1;

    if(m_digits.at(m_digits.size()-1)<0)
    {
        return_string+=45;
        return_string+=(m_digits.at(m_digits.size()-1))*-1+48;
        tmp_size-=1;
    }

    for(int i = tmp_size;i>=0;i--)
    {
        if((i+1)%3==0 && i!=m_digits.size()-1)
            return_string += ',';
        return_string += char(m_digits.at(i)+48);
    }
    return return_string;
}

void BigInt::add_to_int(int add_this)
{
    m_digits.push_back(add_this);
}

void set_length(std::vector<int> &x, std::vector<int> &y)
{
    int choice;

    if (x.size() > y.size())
        choice = 1;
    else
        choice = 2;

    switch (choice)
    {
    case 1:
        for (int i = (x.size() - 1) - (y.size() - 1); i > 0; i--)
            y.push_back(0);
        break;
    case 2:
        for (int i = (y.size() - 1) - (x.size() - 1); i > 0; i--)
            x.push_back(0);
        break;
    }
}

BigInt operator+(const BigInt &lhs, const BigInt &rhs)
{
    BigInt result;
    std::vector<int> x_tmp = lhs.get_large_int();
    std::vector<int> y_tmp = rhs.get_large_int();

    set_length(x_tmp, y_tmp);

    for (int i = 0; i < x_tmp.size(); i++)
    {
        int tmp = 0;
        tmp = x_tmp.at(i) + y_tmp.at(i);
        if (i < x_tmp.size() - 1)
        {
            if (tmp >= 10)
            {
                result.add_to_int(tmp % 10);
                x_tmp.at(i + 1) += (tmp / 10);
            }else{
                result.add_to_int(tmp);
            }
        }else{
            if (tmp >= 10)
            {
                result.add_to_int(tmp % 10);
                result.add_to_int(tmp / 10);
            }else{
                result.add_to_int(tmp);
            }
        }
    }
    return result;
}

BigInt operator-(const BigInt &lhs, const BigInt &rhs)
{
    BigInt result, cleanup, reverse_this;
    std::vector<int> x_tmp = lhs.get_large_int();
    std::vector<int> y_tmp = rhs.get_large_int();
    std::vector<int> clean_vec;

    bool start_num  = false;
    bool flip       = false;

    set_length(x_tmp, y_tmp);
    for(int i=x_tmp.size()-1;i>=0;i--)
    {
        if(x_tmp.at(i) > y_tmp.at(i) && x_tmp.at(i) != y_tmp.at(i))
        {
            break;
        }else if(x_tmp.at(i) < y_tmp.at(i) && x_tmp.at(i) != y_tmp.at(i)){
            flip = true;
            break;
        }
    }

    if(flip == true)
    {
        std::vector<int> flip_this;
        flip_this = x_tmp;
        x_tmp = y_tmp;
        y_tmp = flip_this;
    }

    for (int i=0; i<x_tmp.size(); i++)
    {
        int tmp = 0;
        tmp = x_tmp.at(i) - y_tmp.at(i);
        if (tmp < 0)
        {
            x_tmp.at(i+1) -= 1;
            x_tmp.at(i)+=10;
            result.add_to_int(x_tmp.at(i) - y_tmp.at(i));
        }else{
            result.add_to_int(tmp);
        }
    }

    for(int i=result.get_large_int().size()-1;i>=0;i--)
    {
        if(result.get_large_int().at(i) != 0)
            start_num = true;

        if(start_num == true && cleanup.get_large_int().size()!=0)
            cleanup.add_to_int(result.get_large_int().at(i));

        if(start_num == true && flip == true && cleanup.get_large_int().size() == 0)
            cleanup.add_to_int(result.get_large_int().at(i)*-1);
        else if(start_num == true && flip == false && cleanup.get_large_int().size() == 0)
            cleanup.add_to_int(result.get_large_int().at(i));
        else if(start_num == false && flip == false && i == 0 && cleanup.get_large_int().size()==0)
            cleanup.add_to_int(0);
    }
    result = cleanup;
    for(int i=result.get_large_int().size()-1;i>=0;i--)
        reverse_this.add_to_int(result.get_large_int().at(i));
    result = reverse_this;
    return result;
}

BigInt operator*(const BigInt &lhs, const BigInt &rhs)
{
    BigInt result, add_tmp_1, add_tmp_2, clear;
    std::vector<int> x_tmp = lhs.get_large_int();
    std::vector<int> y_tmp = rhs.get_large_int();

    int carry = 0;
    for (int i = 0; i < y_tmp.size(); i++)
    {
        for(int j = 0; j< x_tmp.size();j++)
        {
            int tmp = 0;
            tmp = x_tmp.at(j) * y_tmp.at(i);
            tmp += carry;
            carry = 0;

            if (j < x_tmp.size()-1)
            {
                if (tmp >= 10)
                {
                    add_tmp_1.add_to_int(tmp % 10);
                    carry = tmp/10;
                }else{
                    add_tmp_1.add_to_int(tmp);
                }
            }else{
                if (tmp >= 10)
                {
                    add_tmp_1.add_to_int(tmp % 10);
                    add_tmp_1.add_to_int(tmp / 10);
                }else{
                    add_tmp_1.add_to_int(tmp);
                }
            }
        }
        add_tmp_2 = add_tmp_2+add_tmp_1;
        add_tmp_1 = clear;
        for(int k = 0;k<=i;k++)
            add_tmp_1.add_to_int(0);
    }
    result = add_tmp_2;
    return result;
}

BigInt operator<(const BigInt& lhs, const BigInt& rhs)
{

}

BigInt operator>(const BigInt& lhs, const BigInt& rhs)
{

}

BigInt operator==(const BigInt& lhs, const BigInt& rhs)
{

}

std::ostream &operator<<(std::ostream &out,const BigInt& value)
{
    out << value.get_large_string();
    return out;
}
