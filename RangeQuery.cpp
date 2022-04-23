/** segment tree */
template<class T>
struct SegmentTree {
  T (*Op)(T, T);
  T Identity;

  int n;
  T *data;

  // index [0, n_)
  SegmentTree(int n_, T (*op_)(T, T), T identity_) {
    Op = op_;
    Identity = identity_;

    // enlarge to power of 2 for simplicity
    n = 1;
    while (n < n_) n *= 2;

    data = new T[2*n - 1];
    for (int i=0; i< 2*n - 1; ++i) {
      data[i] = Identity;
    }
  }

  void update(int k, T a) {
    k += n - 1; // leaf node
    data[k] = a;
    while (k > 0) {
      k = (k - 1) / 2; // upwards
      data[k] = Op(data[2*k + 1], data[2*k + 2]);
    }
  }

  // RMQ from [a, b)
  T query(int a, int b) {
    return _query(a, b, 0, 0, n);
  }

  // sub-query in interval [l, r)
  T _query(int a, int b, int k, int l, int r) {
    if (r <= a || b <= l) { // [a,b) not interleave with [l,r)
      return Identity;
    }
    if (a <= l && r <= b) { // [a, b) cover [l, r)
      return data[k];
    } else {
      T vl = _query(a, b, 2*k + 1, l, (l+r) / 2);
      T vr = _query(a, b, 2*k + 2, (l+r) / 2, r);
      return Op(vl, vr);
    }
  }
};
/** END of segment tree */
