#ifndef INTEGER_H_INCLUDED
#define INTEGER_H_INCLUDED

#include <bitset>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <fstream>
#include <limits>

using namespace std;


template<size_t N>
class Integer
{
    private:
        bitset<N> value;


        bool fullAdder(bool b1, bool b2, bool & carry)const;
        bool fullSubtractor(bool b1, bool b2, bool & borrow)const;
        bool bitsetLtEq(const bitset<N> & x, const bitset<N> & y)const;
        bool bitsetLt(const bitset<N> & x, const bitset<N> & y)const;
        bool bitsetGtEq(const bitset<N> & x, const bitset<N> & y)const;
        void bitsetAdd(bitset<N> & x, const bitset<N> & y)const;
        void bitsetSubtract(bitset<N> & x, const bitset<N> & y)const;
        void bitsetMultiply(bitset<N> & x, const bitset<N> & y)const;
        void bitsetDivide(bitset<N> x, bitset<N> y, bitset<N> & q, bitset< N > & r)const;
        bool bitsetGt(const bitset<N> & x, const bitset<N> & y)const;

        string hexToBin(string const& hex) const;

    public:
        Integer(bitset<N> const& bits):value(bits){};
        Integer(string const& bits){
            auto str = bits;
            str.erase(std::remove_if(str.begin(), str.end(), ::isspace), str.end());
            if(bits.rfind("0x", 0) == 0)
            {

                str = str.substr(2);
                str.insert(0, N/4 - str.length(), str[0]);
                value = bitset<N>(hexToBin(str));
            }

            else
                value = bitset<N>(bits);
            };
        Integer(long const& bits):value(bits){};

        //Addition :
        Integer<N> & operator+=( Integer<N> const & rhs );
        Integer<N> & operator+=( long const & rhs );
        template<size_t M>
        friend Integer<M> operator+( Integer<M> const & lhs, Integer<M> const & rhs );
        template<size_t M>
        friend Integer<M> operator+( Integer<M> const & lhs, long const & rhs );

        //Unary negation:
        Integer<N> operator-( ) const;

        //Subtraction:
        Integer<N> & operator-=( Integer<N> const & rhs );
        Integer<N> & operator-=( long const & rhs );
        template<size_t M>
        friend Integer<M> operator-( Integer<M> const & lhs, Integer<M> const & rhs );
        template<size_t M>
        friend Integer<M> operator-( Integer<M> const & lhs, long const & rhs );

        //Multiplication;
        Integer<N> & operator*=( Integer<N> const & rhs );
        template<size_t M>
        friend Integer<M> operator*( Integer<M> const & lhs, Integer<M> const & rhs );

        //Division:
        Integer<N> & operator/=( Integer<N> const & rhs );
        template<size_t M>
        friend Integer<M> operator/( Integer<M> const & lhs, Integer<M> const & rhs );

        //Modulus:
        Integer<N> & operator%=( Integer<N> const & rhs );
        template<size_t M>
        friend Integer<M> operator%( Integer<M> const & lhs, Integer<M> const & rhs );

        //Modular Power:
        Integer<N> power(Integer<N> x, Integer<N> y, Integer<N> p)const;

        //Modular Inverse:
        Integer<N> inverseModP(Integer<N> const& p) const;

        //Reduce mod p
        Integer<N> & reduce(Integer<N> const& p);
        Integer<N> reduced(Integer<N> const& p)const;

        //Increment:
        Integer<N> operator++( int );
        //Decrement:
        Integer<N> operator--( int );

        //Left shift:
        Integer<N> & operator<<=( size_t pos );
        template<size_t M>
        friend Integer<M> operator<<( Integer<M> const & lhs, size_t pos );

        //Right shift:
        Integer<N> & operator>>=( size_t pos );
        template<size_t M>
        friend Integer<M> operator>>( Integer<M> const & lhs, size_t pos );

        //Bitwise OR
        Integer<N> & operator|=( Integer<N> const & rhs );
        template<size_t M>
        friend Integer<M> operator|( Integer<M> const & lhs, Integer<M> const & rhs );

        //Bitwise AND
        Integer<N> & operator&=( Integer<N> const & rhs );
        template<size_t M>
        friend Integer<M> operator&( Integer<M> const & lhs, Integer<M> const & rhs );

        //Bitwise XOR
        Integer<N> & operator^=( Integer<N> const & rhs );
        template<size_t M>
        friend Integer<M> operator^( Integer<M> const & lhs, Integer<M> const & rhs );

        //Bitwise NOT
        Integer<N> operator~( ) const;

        //Equality
        template<size_t M>
        friend bool operator==( Integer<M> const & lhs, Integer<M> const & rhs );
        template<size_t M>
        friend bool operator==( Integer<M> const & lhs, long const & rhs );

        //Inequality
        template<size_t M>
        friend bool operator!=( Integer<M> const & lhs, Integer<M> const & rhs );
        template<size_t M>
        friend bool operator!=( Integer<M> const & lhs, long const & rhs );

        //Less than
        template<size_t M>
        friend bool operator<( Integer<M> const & lhs, Integer<M> const & rhs );
        template<size_t M>
        friend bool operator<( Integer<M> const & lhs, long const & rhs );

        //Less than or equal
        template<size_t M>
        friend bool operator<=( Integer<M> const & lhs, Integer<M> const & rhs );
        template<size_t M>
        friend bool operator<=( Integer<M> const & lhs, long const & rhs );

        //Greater than
        template<size_t M>
        friend bool operator>( Integer<M> const & lhs, Integer<M> const & rhs );
        template<size_t M>
        friend bool operator>( Integer<M> const & lhs, long const & rhs );

        //Greater than or equal
        template<size_t M>
        friend bool operator>=( Integer<M> const & lhs, Integer<M> const & rhs );
        template<size_t M>
        friend bool operator>=( Integer<M> const & lhs, long const & rhs );

        string to_string() const;
        void save(char path[255] , unordered_map<bitset<N>, bitset<N>>  &umap);
        void load(char path[255] , unordered_map<bitset<N>, bitset<N>>  &umap);
        void generateAddMap(char* path, Integer<N> maximum);
        void generateMultiMap(char* path, Integer<N> maximum);


};


//Left shift:
template<size_t N>
Integer<N> & Integer<N>::operator<<=( size_t pos )
{
    value <<= pos;
    return *this;
}
template<size_t N>
Integer<N> operator<<( Integer<N> const & lhs, size_t pos )
{
    auto tmp(lhs);
    tmp <<= pos;
    return tmp;
}

//Right shift:
template<size_t N>
Integer<N> & Integer<N>::operator>>=( size_t pos )
{
    value >>= pos;
    return *this;
}
template<size_t N>
Integer<N> operator>>( Integer<N> const & lhs, size_t pos )
{
    auto tmp(lhs);
    tmp >>= pos;
    return tmp;
}

//Bitwise OR
template<size_t N>
Integer<N> & Integer<N>::operator|=( Integer<N> const & rhs )
{
    value |= rhs.value;
    return *this;
}
template<size_t N>
Integer<N> operator|( Integer<N> const & lhs, Integer<N> const & rhs )
{
    auto tmp(lhs);
    tmp |= rhs;
    return tmp;
}

//Bitwise AND
template<size_t N>
Integer<N> & Integer<N>::operator&=( Integer<N> const & rhs )
{
    value &= rhs.value;
    return *this;
}
template<size_t N>
Integer<N> operator&( Integer<N> const & lhs, Integer<N> const & rhs )
{
    auto tmp(lhs);
    tmp &= rhs;
    return tmp;
}

//Bitwise XOR
template<size_t N>
Integer<N> & Integer<N>::operator^=( Integer<N> const & rhs )
{
    value ^= rhs.value;
    return *this;
}
template<size_t N>
Integer<N> operator^( Integer<N> const & lhs, Integer<N> const & rhs )
{
    auto tmp(lhs);
    tmp ^= rhs;
    return tmp;
}

//Bitwise NOT
template<size_t N>
Integer<N> Integer<N>::operator~( ) const
{
    auto tmp(*this);
    tmp.value = ~tmp.value;
    return tmp;
}

//Equality
template<size_t N>
bool operator==( Integer<N> const & lhs, Integer<N> const & rhs )
{
    return lhs.value == rhs.value;
}
template<size_t N>
bool operator==( Integer<N> const & lhs, long const & rhs )
{
    Integer<N> tmp(rhs);
    return lhs.value == tmp;
}

//Inequality
template<size_t N>
bool operator!=( Integer<N> const & lhs, Integer<N> const & rhs )
{
    return !(lhs == rhs);
}
template<size_t N>
bool operator!=( Integer<N> const & lhs, long const & rhs )
{
    return !(lhs == rhs);
}

//Less than
template<size_t M>
bool operator<( Integer<M> const & lhs, Integer<M> const & rhs )
{
    return lhs.bitsetLt(lhs.value, rhs.value);
}
template<size_t M>
bool operator<( Integer<M> const & lhs, long const & rhs )
{
    bitset<M> tmp(rhs);
    return lhs.bitsetLt(lhs.value, tmp);
}

//Less than or equal
template<size_t M>
bool operator<=( Integer<M> const & lhs, Integer<M> const & rhs )
{
    return lhs.bitsetLtEq(lhs.value, rhs.value);
}
template<size_t M>
bool operator<=( Integer<M> const & lhs, long const & rhs )
{
    bitset<M> tmp(rhs);
    return lhs.bitsetLtEq(lhs.value, tmp.value);
}
//Greater than
template<size_t M>
bool operator>( Integer<M> const & lhs, Integer<M> const & rhs )
{
    return lhs.bitsetGt(lhs.value, rhs.value);
}
template<size_t M>
bool operator>( Integer<M> const & lhs, long const & rhs )
{
    bitset<M> tmp(rhs);
    return lhs.bitsetGt(lhs.value, tmp.value);
}

//Greater than or equal
template<size_t M>
bool operator>=( Integer<M> const & lhs, Integer<M> const & rhs )
{
    return lhs.bitsetGtEq(lhs.value, rhs.value);
}
template<size_t M>
bool operator>=( Integer<M> const & lhs, long const & rhs )
{
    bitset<M> tmp(rhs);
    return lhs.bitsetGtEq(lhs.value, tmp.value);
}

template<size_t N>
string Integer<N>::to_string() const
{
    return value.to_string();
}
template<size_t N>
std::ostream& operator<<(std::ostream& stream, const Integer<N>& n)
{
    return stream << n.to_string();
}
template<size_t N>
bool Integer<N>::fullAdder(bool b1, bool b2, bool & carry)const {
   bool sum = (b1 ^ b2) ^ carry;
   carry = (b1 && b2) || (b1 && carry) || (b2 && carry);
   return sum;
}
template<size_t N>
bool Integer<N>::fullSubtractor(bool b1, bool b2, bool & borrow)const {
   bool diff;
   if (borrow) {
      diff = !(b1 ^ b2);
      borrow = !b1 || (b1 && b2);
   } else {
      diff = b1 ^ b2;
      borrow = !b1 && b2;
   }
   return diff;
}
template < size_t N >
bool Integer<N>::bitsetLtEq(const bitset<N> & x, const bitset<N> & y)const
{
    if( x[N-1]== true && y[N-1] == false)
        return true;
    if( x[N-1]== false && y[N-1] == true)
        return false;

    for (int i = N - 1; i >= 0; i--) {
     if (x[i] && !y[i]) return false;
     if (!x[i] && y[i]) return true;
    }
    return true;
}

template < size_t N >
bool Integer<N>::bitsetLt(const bitset<N> & x, const bitset<N> & y)const {
  if( x[N-1]== true && y[N-1] == false)
    return true;
  if( x[N-1]== false && y[N-1] == true)
    return false;

  for (int i = N - 1; i >= 0; i--) {
     if (x[i] && !y[i]) return false;
     if (!x[i] && y[i]) return true;
  }
  return false;
}
template < size_t N >
bool Integer<N>::bitsetGtEq(const bitset<N> & x, const bitset<N> & y)const {
  if( x[N-1]== true && y[N-1] == false)
    return false;
  if( x[N-1]== false && y[N-1] == true)
    return true;

  for (int i = N - 1; i >= 0; i--) {
     if (x[i] && !y[i]) return true;
     if (!x[i] && y[i]) return false;
  }
  return true;
}
template < size_t N >
bool Integer<N>::bitsetGt(const bitset<N> & x, const bitset<N> & y)const {
  if( x[N-1]== true && y[N-1] == false)
    return false;
  if( x[N-1]== false && y[N-1] == true)
    return true;

  for (int i = N - 1; i >= 0; i--) {
     if (x[i] && !y[i]) return true;
     if (!x[i] && y[i]) return false;
  }
  return false;
}
template < size_t N >
void Integer<N>::bitsetAdd(bitset<N> & x, const bitset<N> & y)const {


    bool carry = false;
    for (size_t i = 0; i < N; i++) {
     x[i] = fullAdder(x[i], y[i], carry);
    }
}
template < size_t N >
void Integer<N>::bitsetSubtract(bitset<N> & x, const bitset<N> & y)const {
  bool borrow = false;
  for (size_t i = 0; i < N; i++) {
     if (borrow) {
        if (x[i]) {
           x[i] = y[i];
           borrow = y[i];
        } else {
           x[i] = !y[i];
           borrow = true;
        }

     } else {
        if (x[i]) {
           x[i] = !y[i];
           borrow = false;
        } else {
           x[i] = y[i];
           borrow = y[i];
        }
     }
  }
}
template < size_t N >
void Integer<N>::bitsetMultiply(bitset<N> & x, const bitset<N> & y)const {
    bitset<N> tmp = x;


    x.reset();
    // we want to minimize the number of times we shift and add
    if (tmp.count() < y.count()) {
     for (size_t i = 0; i < N; i++)
        if (tmp[i]) bitsetAdd(x, y << i);
    } else {
     for (size_t i = 0; i < N; i++)
        if (y[i]) bitsetAdd(x, tmp << i);
    }

}

template < size_t N >
void Integer<N>::bitsetDivide(bitset<N> x, bitset<N> y, bitset< N > & q, bitset< N > & r)const
{
      if (y.none()) {
         throw domain_error("division by zero undefined");
      }
      q.reset();
      r.reset();
      if (x.none()) {
         return;
      }
      if (x == y) {
         q[0] = 1;
         return;
      }
      r = x;
      if (bitsetLt(x, y)) {
         return;
      }

      // count significant digits in divisor and dividend
      size_t sig_x;
      for (int i = N - 1; i >= 0; i--) {
         sig_x = i;
         if (x[i]) break;
      }
      size_t sig_y;
      for (int i = N - 1; i >= 0; i--) {
         sig_y = i;
         if (y[i]) break;
      }
      // align the divisor with the dividend
      size_t n = (sig_x - sig_y);
      y <<= n;
      // make sure the loop executes the right number of times
      n += 1;
      // long division algorithm, shift, and subtract
      while (n--) {
         // shift the quotient to the left
         if (bitsetLtEq(y, r)) {
            // add a new digit to quotient
            q[n] = true;
            bitsetSubtract(r, y);
         }
         // shift the divisor to the right
         y >>= 1;
      }
}

//Addition :
template<size_t N>
Integer<N> & Integer<N>::operator+=( Integer<N> const & rhs )
{
    bitsetAdd(value, rhs.value);
    return *this;
}
template<size_t N>
Integer<N> & Integer<N>::operator+=( long const & rhs )
{
    Integer<N> tmp(rhs);
    *this += tmp;
    return *this;
}
template<size_t M>
Integer<M> operator+( Integer<M> const & lhs, Integer<M> const & rhs )
{
    auto tmp(lhs);
    tmp += rhs;
    return tmp;
}
template<size_t M>
Integer<M> operator+( Integer<M> const & lhs, long const & rhs )
{
    Integer<M> tmp(rhs);
    return lhs + tmp;
}

//Unary negation:
template<size_t N>
Integer<N> Integer<N>::operator-( ) const
{
    //TODO Complément à deux...
    return Integer<N>(0) - *this;
}

//Subtraction:
template<size_t N>
Integer<N> & Integer<N>::operator-=( Integer<N> const & rhs )
{
    bitsetSubtract(value, rhs.value);
    return *this;
}
template<size_t N>
Integer<N> & Integer<N>::operator-=( long const & rhs )
{
    Integer<N> tmp(rhs);
    *this -= tmp;
    return *this;
}
template<size_t M>
Integer<M> operator-( Integer<M> const & lhs, Integer<M> const & rhs )
{
    auto tmp(lhs);
    tmp -= rhs;
    return tmp;
}
template<size_t M>
Integer<M> operator-( Integer<M> const & lhs, long const & rhs )
{
    Integer<M> tmp(rhs);
    return lhs - tmp;
}

//Multiplication;
template<size_t N>
Integer<N> & Integer<N>::operator*=( Integer<N> const & rhs )
{
    bitsetMultiply(value, rhs.value);
    //Integer<N> tmp(multiply(value, rhs.value, N));
    //value = tmp.value;
    return *this;
}

template<size_t M>
Integer<M> operator*( Integer<M> const & lhs, Integer<M> const & rhs )
{
    auto tmp(lhs);
    tmp *= rhs;
    return tmp;
}

//Division:
template<size_t N>
Integer<N> & Integer<N>::operator/=( Integer<N> const & rhs )
{
    bitset<N> q, r;
    bitsetDivide(value, rhs.value, q, r);
    value = q;
    return *this;
}
template<size_t M>
Integer<M> operator/( Integer<M> const & lhs, Integer<M> const & rhs )
{
    auto tmp(lhs);
    tmp /= rhs;
    return tmp;
}

//Modulus:
template<size_t N>
Integer<N> & Integer<N>::operator%=( Integer<N> const & rhs )
{
    bitset<N> q, r;
    bitsetDivide(value, rhs.value, q, r);
    value = r;
    return *this;
}
template<size_t M>
Integer<M> operator%( Integer<M> const & lhs, Integer<M> const & rhs )
{
    auto tmp(lhs);
    tmp %= rhs;
    return tmp;
}

//Increment:
template<size_t N>
Integer<N> Integer<N>::operator++( int )
{
    *this += 1;
    return *this;
}
//Decrement:
template<size_t N>
Integer<N> Integer<N>::operator--( int )
{
    *this -= 1;
    return *this;
}

template<size_t N>
Integer<N> Integer<N>::inverseModP(Integer<N> const& p) const
{
    Integer<N> temp(value);
    if( temp == Integer<N>(0))
        throw domain_error("Calculating modular inverse of 0.");
    //From Fermat's therorem supposing p is prime.
    return power(temp, p - Integer<N>(2), p);
}

template<size_t N>
Integer<N> Integer<N>::power(Integer<N> x, Integer<N> y, Integer<N> p)const
{
    Integer<N> res(1);     // Initialize result
    x.reduce(p); // Update x if it is more than or
    Integer<N> zero(0), one(1);
    if(x == zero) return zero; // In case x is divisible by p;

    while (y > zero)
    {
        // If y is odd, multiply x with result
        if ((y & one) != zero)
        {
            res = (res*x).reduced(p);
        }

        // y must be even now
        y.value = y.value >> 1; // y = y/2
        x = (x*x).reduced(p);
    }
    return res;
}

template<size_t N>
Integer<N> & Integer<N>::reduce(Integer<N> const& p)
{
    *this = reduced(p);
    return *this;
}

template<size_t N>
Integer<N> Integer<N>::reduced(Integer<N> const& p) const
{
    Integer<N> R(0);
    if(value[N-1])
    {
        Integer<N> tmp(-*this);
        bitset<N> q, r, numerator(tmp.value);
        bitsetDivide(numerator, p.value, q, r);
        R = -Integer<N>(r);
    }
    else
    {
        bitset<N> q, r, numerator(value);
        bitsetDivide(numerator, p.value, q, r);
        R = r;
    }
    if(R<Integer<N>(0))
        R = R + p;

    return R;
}

template<size_t N>
string Integer<N>::hexToBin(string const& hex) const
{
    string ret;
    for(auto const& c : hex)
    {
        if(c==' ')
            continue;
        string bin;
        switch (toupper(c))
        {
        case 'A':
            bin = "1010";
            break;

        case 'B':
            bin = "1011";
            break;

        case 'C':
            bin = "1100";
            break;

        case 'D':
            bin = "1101";
            break;

        case 'E':
            bin = "1110";
            break;

        case 'F':
            bin = "1111";
            break;

        default:
            bin = std::bitset< 4 >( c - '0' ).to_string();
            break;
        }
        ret.append(bin);
    }
    return ret;
}


void save(char path[255] , unordered_map<string, string>  &umap){
    ofstream myfile(path);
    if (myfile.is_open())
    {
        for (auto& it: umap) {
            myfile << it.first << '\n' << it.second << '\n';
        }
        myfile.close();
    }
}

template<size_t N>
void generateMaps(char* pathAdd, char* pathMulti, Integer<N> maximum , unordered_map<string, string> &addMap, unordered_map<string, string> &multiMap)
{
    for(Integer<N> i(0);i < maximum;i++)
        for(Integer<N> j(0);j < maximum;j++)
        {
            auto index = (i & j).to_string();
            multiMap[index] = (i*j).to_string();
            addMap[index] = (i+j).to_string();
        }

    save(pathAdd,addMap);
    save(pathMulti,multiMap);
}


#endif // INTEGER_H_INCLUDED
