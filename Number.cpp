/** print with leading zeros */
cout << setw(2) << setfill('0') << (start / 60);

/** set precision **/
double f =3.14159;
  std::cout << std::setprecision(5) << f << '\n';
  std::cout << std::setprecision(9) << f << '\n';
  std::cout << std::fixed;
  std::cout << std::setprecision(5) << f << '\n';
  std::cout << std::setprecision(9) << f << '\n';
  /* output:
  3.1416
3.14159
3.14159
3.141590000

  */

/* floating-point comparison */
// refer to https://floating-point-gui.de/errors/comparison/
inline bool nearlyEqual(double a, double b) {
    double absA = abs(a);
    double absB = abs(b);
    double diff = abs(a - b);

    if (a == b) {
        return true;
    } else if (a == 0 || b == 0 || (absA + absB < DBL_EPSILON)) {
        return diff < DBL_EPSILON;
    } else {
        return diff / min(absA + absB, DBL_MAX) < DBL_EPSILON;
    }
}

/** BigInteger (10-based) */
struct BigInteger {
    vector<short> s;

    BigInteger(long long val = 0) {
        while (val > 0) {
            s.push_back(val % 10);
            val /= 10;
        }
    }

    BigInteger(string val) {
        for (int i=val.length() - 1; i >= 0; --i) {
            s.push_back(val[i] - '0');
        }
    }

    friend std::ostream& operator<< (std::ostream &out, const BigInteger &v);

    BigInteger operator+(const BigInteger &val) const {
        BigInteger y;
        int carry = 0;
        int i = 0;
        while (i < (long)s.size() ||
                i < (long)val.s.size() ||
                carry != 0) {
            int p = carry;
            if (i < (long)s.size()) {
                p += s[i];
            }
            if (i < (long)val.s.size()) {
                p += val.s[i];
            }

            y.s.push_back(p % 10);
            carry = p / 10;

            ++i;
        }
        return y;
    }

    BigInteger operator*(const BigInteger &val) const {
        BigInteger y;
        if (s.size() == 0 || val.s.size() == 0) {
            return y;
        }
        y.s.resize(s.size() + val.s.size());
        for (int i=0; i<(long)s.size(); ++i) {
            for (int j=0; j<(long)val.s.size(); ++j) {
                int sum = s[i] * val.s[j];
                y.s[i+j] += sum % 10;
                y.s[i+j+1] += sum / 10;
                int k = i+j;
                while (y.s[k] >= 10) {
                    y.s[k+1] += y.s[k] / 10;
                    y.s[k] = y.s[k] % 10;
                    ++k;
                }
            }
        }
        if (y.s[s.size() + val.s.size() - 1] == 0) {
            y.s.resize(s.size() + val.s.size());
        }

        return y;
    }
};

std::ostream& operator<< (std::ostream &out, const BigInteger &v) {
    bool zero = true;
    for (int i=v.s.size()-1; i>=0; --i) {
        if (!zero || v.s[i] != 0) {
            cout << v.s[i];
            zero = false;
        }
    }
    if (zero) {
        cout << '0';
    }
    return out;
}


/** END of BigInteger (10-based) */

// one operation O(sqrt(x))
bool isPrime(long long x) {
    if (x <= 1) return false;
    if (x == 2) return true;
    if (x % 2 == 0) return false;

    long i = 3, u = (long)(sqrt(x) + 1);
    while (i <= u) {
        if (x % i == 0) {
            return false;
        }
        i += 2;
    }
    return true;
}

// Euler's totient function
// https://www.geeksforgeeks.org/eulers-totient-function/
long long phi(long long n)
{
  long long result = n;

  for(long long p = 2; p * p <= n; ++p)
  {
    if (n % p == 0)
    {
      while (n % p == 0) {
        n /= p;
      }
      result -= result / p;
    }
  }

  if (n > 1) result -= result / n;

  return result;
}

// sieve of Eratosthenes O(nlog(log(n)))
vector<bool> eratosthenes(int upperbound) {
  std::vector<bool> flag(upperbound + 1, true);
  flag[0] = flag[1] = false; //exclude 0 and 1
  for (int i = 2; i * i <= upperbound; ++i) {
    if (flag[i]) {
      for (int j = i * i; j <= upperbound; j += i)
        flag[j] = false;
    }
  }
  return flag;
}

/* Find the gcd(p,q) and x,y such that p*x + q*y = gcd(p,q) */
long long gcd(long long p, long long q, long long *x, long long *y) {
    long long x1, y1; // previous coefficients
    long long g;

    if (q > p) return (gcd(q, p, y, x));

    if (q == 0) {
        *x = 1;
        *y = 0;
        return p;
    }

    g = gcd(q, p % q, &x1, &y1);

    *x = y1;
    *y = (x1 - p / q * y1);

    return g;
}

/* lcm(x, y) = x*y/gcd(x, y) */

