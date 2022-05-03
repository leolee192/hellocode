/* ----- Segment Tree ----- */

inline int ceilPower2(int x) {
  int y = 1;
  while (y < x) y *= 2;
  return y;
}

/** segment tree inner storage */
int n = ceilPower2(max_i + 1);
T data[4 * MAX_N]; // normally long long
T delta[4 * MAX_N];

#define leaf(i) ((i) + n - 1)
#define parent(k) (((k) - 1) / 2)
#define leftChild(k) (2*(k) + 1)
#define rightChild(k) (2*(k) + 2)

/** init segment tree
 * data[k] corresponds to [l, r)
 * when call externally, use init(0, 0, n) */
void init(int k, int l, int r) {
  if (r - l == 1) { // leaf node
    data[k] = (l < n_) ? nums[l] : AggIdentity;
  } else {
    int lch = leftChild(k), rch = rightChild(k), mid = (l + r) / 2;
    init(lch, l, mid);
    init(rch, mid, r);
    data[k] = AggOp(data[lch], data[rch]);
  }
  delta[k] = UpdateIdentity;
}

/** find the aggregated value of [a, b)
 * data[k] corresponds to [l, r)
 * when call externally, use query(a, b, 0, 0, n)  */
T query(int a, int b, int k, int l, int r) {
  if (r <= a || b <= l) { // [a,b) and [l,r) do not intersect
    return AggIdentity;
  } else if (a <= l && r <= b) { // [l, r] subset of [a, b)
    return data[k];
  } else {
    int mid = (l + r) / 2;
    _pushDown(k, mid-l, r-mid);
    T vl = query(a, b, leftChild(k), l, mid);
    T vr = query(a, b, rightChild(k), mid, r);
    return AggOp(vl, vr);
  }
}

/* ----- end of Segment Tree ----- */

/* ----- point update ----- */

/**
 * update i-th (0-indexed) as a
 */
void update(int i, T a) {
  int k = leaf(i); // leaf node
  data[k] = a;
  while (k > 0) { // update upwards
    k = parent(k);
    data[k] = AggOp(data[leftChild(k)], data[rightChild(k)]);
  }
}

/* ----- end of point update ----- */

/* ----- interval update ----- */

void _pushDown(int k, int nl, int nr) {
  if (delta[k] != UpdateIdentity) {
    delta[2*k + 1] = UpdateOp(delta[2*k + 1], delta[k]);
    delta[2*k + 2] = UpdateOp(delta[2*k + 2], delta[k]);

    data[2*k + 1] = MultiUpdateOp(data[2*k + 1], delta[k], nl);
    data[2*k + 2] = MultiUpdateOp(data[2*k + 2], delta[k], nr);

    delta[k] = UpdateIdentity;
  }
};

/** update elements in [a,b) by delta
 * data[k] corresponds to [l, r)
  when call externally, use _update(a, b, delta, 0, 0, n)
 * */
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

/* ----- end of interval update ----- */

/* ----- merge tree ----- */

/** init segment tree
 * data[k] corresponds to [l, r)
 * when call externally, use init(0, 0, n) */
void init(int k, int l, int r) {
  if (r - l == 1) { // leaf node
    data[k].push_back(nums[l]);
  } else {
    int lch = leftChild(k), rch = rightChild(k), mid = (l + r) / 2;
    init(lch, l, mid);
    init(rch, mid, r);

    data[k].resize(r - l);
    merge(data[lch].begin(), data[lch].end(),
          data[rch].begin(), data[rch].end(),
          data[k].begin());
  }
}

/** number of numbers <= x in [a, b)
  data[k] corresponds to [l, r)
  when call externally, use query(a, b, x, 0, 0, n)
 */
int query(int a, int b, int x, int k, int l, int r) {
  if (r <= a || b <= l) { // [a,b) and [l,r) do not intersect
    return 0;
  } else if (a <= l && r <= b) { // [l, r] subset of [a, b)
    return upper_bound(data[k].begin(), data[k].end(), x) - data[k].begin();
  } else {
    int mid = (l + r) / 2;
    int vl = query(a, b, x, leftChild(k), l, mid);
    int vr = query(a, b, x, rightChild(k), mid, r);
    return vl + vr;
  }
}

/* ----- end of merge tree ----- */

/* ----- weighted segment tree ----- */

/**
 * find the index of i_th (1-based) least number
 * data[k] corresponds to [l, r)
 * when call externally, use i_th(i, 0, 0, n)
 */
int i_th(int i, int k, int l, int r) {
  if (r - l == 1) {
    return l;
  }
  int lch = leftChild(k), rch = rightChild(k), mid = (l + r) / 2;
  int res;
  if (i <= data[lch]) {
    res = i_th(i, lch, l, mid);
  } else {
    res = i_th(i-data[lch], rch, mid, r);
  }
  return res;
}

/* ----- end of weighted segment tree ----- */
