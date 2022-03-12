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
