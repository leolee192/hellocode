#include <bits/stdc++.h>

using namespace std;

#define MY_DEBUG true

#define $(x) {if (MY_DEBUG) {cout << __LINE__ << ": "; cout << #x << " = " << x << " " << endl;}}

#if __cplusplus <= 199711L

#define nullptr NULL

template<class T>
string to_string(T value) {
    ostringstream os;
    os << value;
    return os.str();
}

#endif

template<class T>
std::ostream& operator<< (std::ostream& out, const vector<T>& v) {
    out << '[';
    for (size_t i=0; i < v.size(); ++i) {
        if (i != 0) cout << ',';
        cout << v[i];
    }
    out << ']';
    return out;
}

// REMEMBER: modify MY_DEBUG to false
// main region begin (DO NOT DELETE ABOVE)



int main()
{

    return 0;
}
