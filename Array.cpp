
/** initialize vector in c++98 */
static const int arr[] = {16,2,77,29};
vector<int> vec (arr, arr + sizeof(arr) / sizeof(arr[0]) );

/** initialize vector inplace */
template <class T>
inline vector<T> list_of(T v1) {
    vector<T> vec;
    vec.push_back(v1);
    return vec;
}

template <class T>
inline vector<T> list_of(T v1, T v2) {
    vector<T> vec;
    vec.push_back(v1);
    vec.push_back(v2);
    return vec;
}

/** reverse iterate vector */
for (vector<my_class>::reverse_iterator it = my_vector.rbegin();
        it != my_vector.rend(); ++it ) {
}

/** sort with comparator */
struct myclass {
    vector<int> &solved, &penalty, &last;

    bool operator() (int i,int j) {
        if (solved[i] != solved[j]) return solved[i] > solved[j];
        if (penalty[i] != penalty[j]) return (penalty[i]) < (penalty[j]);
        return i < j;
    }
};

myclass myobj = {solved, penalty, last};
sort(board.begin(), board.end(), myobj);
// for array
sort(intervals, intervals+N, myobj);

/** binary search
 * find in [left, right) first i satisfying ge(i)
 * recheck equality if needed !!
 */
Index my_lower_bound(Index left, Index right) {
  while (left < right) {
    Index mid = left + (right - left) / 2;
    if (ge(mid)) right = mid;
    else left = mid + 1;
  }
  return left;
}

/** end of binary search */
