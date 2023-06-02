// x^ p mod m with crt
#include<iostream>
#include <vector>
using namespace std;

typedef unsigned long long ull;

vector<int> primeFactors(ull n)
{
    vector<int> v;
    int base_num_2 = 1;
    while (n % 2 == 0)
    {
        base_num_2 *= 2;
        n = n / 2;
        if (n % 2) {
            v.push_back(base_num_2);
        }

    }

    for (int i = 3; i <= sqrt(n); i = i + 2)
    {
        int base_num = 1;
        while (n % i == 0)
        {
            base_num *= i;
            n = n / i;
            if (n % i) {
                v.push_back(base_num);
            }
        }
    }

    if (n > 2)
        v.push_back(n);
    return v;
}

ull gcdExtended(ull a, ull b, ull* x, ull* y);

ull modInverse(ull A, ull M)
{
    ull x, y;
    ull g = gcdExtended(A, M, &x, &y);
    if (g != 1)
        cout << "Inverse doesn't exist";
    else {

        // m is added to handle negative x
        ull res = (x % M + M) % M;
        return res;
    }
    
}

ull gcdExtended(ull a, ull b, ull* x, ull* y)
{

    // Base Case
    if (a == 0) {
        *x = 0, * y = 1;
        return b;
    }

    // To store results of recursive call
    ull x1, y1;
    ull gcd = gcdExtended(b % a, a, &x1, &y1);

    // Update x and y using results of recursive
    // call
    *x = y1 - (b / a) * x1;
    *y = x1;

    return gcd;
}

ull crt(ull x, ull p, ull mod) {
    vector<int> m_i = primeFactors(mod); //factorization ::: getting m_i
    //vector<int> b_i; // b_i
    //vector<int> b_i_inverse; // b_i_inverse
    //vector<int> a_i; // a_i
    ull res = 0ull;
    ull b_i, b_i_inverse, a_i=0ull;
    ull xx = 1ull;
    for (auto it = m_i.begin(); it != m_i.end(); ++it) {
        //cout << ' ' << *it;
        //b_i.push_back(mod / (*it)); // ::: getting b_i
        //b_i_inverse.push_back(modInverse((mod / (*it)), (*it))); // ::: getting b_i_inverse

        b_i = mod / (*it);
        b_i_inverse = modInverse((mod / (*it)), (*it));
        for (ull i = 0ull; i < p; i++) {
            xx = (xx * x) % (*it);
        }
        a_i = xx;

        res = (res + ((a_i * b_i * b_i_inverse) % mod)) % mod;
    }

    /*for (auto it = m_i.begin(); it != m_i.end(); ++it) {
        cout << ' ' << *it;
    }*/
    /*
    for (auto it = b_i.begin(); it != b_i.end(); ++it) {
        cout << ' ' << *it;
    }
    for (auto it = b_i_inverse.begin(); it != b_i_inverse.end(); ++it) {
        cout << ' ' << *it;
    }
    for (auto it = a_i.begin(); it != a_i.end(); ++it) {
        cout << ' ' << *it;
    }*/

    return res;
}





int main() {

    ull res = crt(12345ull, 456789ull, 10000000000ull);
    cout << "answer is " << res << endl;

    return 0;
}
