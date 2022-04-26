/** segment tree */
template<class T>
struct SegmentTree {
  T (*AggOp)(T, T);
  T AggIdentity;

  int n;
  T *data;
  T (*UpdateOp)(T, T); // result = UpdateOp(origin, delta)
  T UpdateIdentity;
  T (*MultiUpdateOp)(T, T, int);
  T *delta;

  // index [0, n_)
  SegmentTree(int n_,
              T (*aggOp_)(T, T), T aggIdentity_,
              T (*updateOp_)(T, T), T updateIdentity_, T (*multiUpdateOp_)(T, T, int)) {
    AggOp = aggOp_;
    AggIdentity = aggIdentity_;
    UpdateOp = updateOp_;
    UpdateIdentity = updateIdentity_;
    MultiUpdateOp = multiUpdateOp_;

    // enlarge to power of 2 for simplicity
    n = 1;
    while (n < n_) n *= 2;

    data = new T[2*n - 1];
    for (int i=0; i< 2*n - 1; ++i) {
      data[i] = AggIdentity;
    }

    delta = new T[2*n - 1];
    for (int i=0; i< 2*n - 1; ++i) {
      delta[i] = UpdateIdentity;
    }
  }

  void _pushDown(int k, int nl, int nr) {
    if (delta[k] != UpdateIdentity) {
      delta[2*k + 1] = UpdateOp(delta[2*k + 1], delta[k]);
      delta[2*k + 2] = UpdateOp(delta[2*k + 2], delta[k]);

      data[2*k + 1] = MultiUpdateOp(data[2*k + 1], delta[k], nl);
      data[2*k + 2] = MultiUpdateOp(data[2*k + 2], delta[k], nr);

      delta[k] = UpdateIdentity;
    }
  };

  void update(int k, T delta_) {
    update(k, k+1, delta_);
  }

  // update [a,b) by delta_
  void update(int a, int b, T delta_) {
    _update(a, b, delta_, 0, 0, n);
  }

  // sub-update in interval [l, r)
  void _update(int a, int b, T delta_, int k, int l, int r) {
    if (r <= a || b <= l) { // [a,b) not interleave with [l,r)
      return;
    }
    if (a <= l && r <= b) {
      data[k] = MultiUpdateOp(data[k], delta_, r-l);
      delta[k] = UpdateOp(delta[k], delta_);
      return;
    } else {
      int m = (l+r) / 2;
      _pushDown(k, m-l, r-m);
      if (l < m) _update(a, b, delta_, 2*k + 1, l, m);
      if (m < r) _update(a, b, delta_, 2*k + 2, m, r);
      data[k] = AggOp(data[2*k + 1], data[2*k + 2]);
    }
  }

  // RMQ from [a, b)
  T query(int a, int b) {
    return _query(a, b, 0, 0, n);
  }

  // sub-query in interval [l, r)
  T _query(int a, int b, int k, int l, int r) {
    if (r <= a || b <= l) { // [a,b) not interleave with [l,r)
      return AggIdentity;
    }
    if (a <= l && r <= b) { // [a, b) cover [l, r)
      return data[k];
    } else {
      int m = (l+r) / 2;
      _pushDown(k, m-l, r-m);
      T vl = _query(a, b, 2*k + 1, l, m);
      T vr = _query(a, b, 2*k + 2, m, r);
      return AggOp(vl, vr);
    }
  }
};
/** END of segment tree */
