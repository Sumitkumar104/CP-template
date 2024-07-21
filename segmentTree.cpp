/*

How we proceed with segment tree?
first build the segment tree and update the segment tree data Structure(array of size 4*n)
then query the segment tree

Always take the size of segment tree as 4 times the size of the array for worst case  scenario.

for query => We have three cases:
paritial overlap - call on both sides
complete overlap - return the segment tree value
no overlap - return the INT_MAX, INT_MIN, 0, 1, etc. depending on the query

*/

#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 2, MOD = 1e9 + 7;

class SegmentTree   {
public:
    vector<int> tree;
    SegmentTree(int n)
    {
        tree.resize(4 * n + 1);
    }

    void build(int index, int l, int r, vector<int> &a)
    {
        if (l == r)
        {
            tree[index] = a[l];
            return;
        }
        int mid = (l + r) / 2;
        build(2 * index + 1, l, mid, a);
        build(2 * index + 2, mid + 1, r, a);
        tree[index] = min(tree[2 * index + 1], tree[2 * index + 2]);
    }

    int query(int index, int l, int r, int ql, int qr)
    {
        // ql qr l r  or  l r ql qr
        if (qr < l || r < ql) // no overlap
            return INT_MAX;

        //  ql l r qr
        if (l >= ql && r <= qr) // complete overlap
            return tree[index];

        // partial overlap
        int mid = (l + r) / 2;
        int left = query(2 * index + 1, l, mid, ql, qr);
        int right = query(2 * index + 2, mid + 1, r, ql, qr);
        return min(left, right);
    }

    void update(int index, int l, int r, int i, int val)
    {
        if (l == r)
        {
            tree[index] = val;
            return;
        }
        int mid = (l + r) / 2;
        if (i <= mid)
            update(2 * index + 1, l, mid, i, val); // go in left part fo tree
        else
            update(2 * index + 2, mid + 1, r, i, val); // go in right part of tree
        tree[index] = min(tree[2 * index + 1], tree[2 * index + 2]);
    }
};

int minSegmentTree()
{
    vector<int> arr = {1, 3, 5, 2, 8, 5, 9, 0, 6, 4};
    int n = arr.size();

    SegmentTree segtree(n);
    segtree.build(0, 0, n - 1, arr);

    cout << "ans is this " << segtree.query(0, 0, n - 1, 1, 6) << endl;
    return 0;
}