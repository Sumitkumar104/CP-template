#include <vector>

class SegmentTree {
private:
    std::vector<int> tree;
    int n;

    void buildTree(const std::vector<int>& nums, int left, int right, int index) {
        if (left == right) {
            tree[index] = nums[left];
            return;
        }

        int mid = (left + right) / 2;
        buildTree(nums, left, mid, 2 * index + 1);
        buildTree(nums, mid + 1, right, 2 * index + 2);
        tree[index] = tree[2 * index + 1] + tree[2 * index + 2];
    }

    int sumRange(int left, int right, int index, int qleft, int qright) {
        if (qright < left || qleft > right) {
            return 0;
        }

        if (qleft <= left && right <= qright) {
            return tree[index];
        }

        int mid = (left + right) / 2;
        return sumRange(left, mid, 2 * index + 1, qleft, qright) + sumRange(mid + 1, right, 2 * index + 2, qleft, qright);
    }

    void update(int left, int right, int index, int pos, int val) {
        if (left == right) {
            tree[index] = val;
            return;
        }

        int mid = (left + right) / 2;
        if (pos <= mid) {
            update(left, mid, 2 * index + 1, pos, val);
        } else {
            update(mid + 1, right, 2 * index + 2, pos, val);
        }

        tree[index] = tree[2 * index + 1] + tree[2 * index + 2];
    }

public:
    SegmentTree(const std::vector<int>& nums) {
        n = nums.size();
        tree.resize(4 * n);
        buildTree(nums, 0, n - 1, 0);
    }

    int sumRange(int qleft, int qright) {
        return sumRange(0, n - 1, 0, qleft, qright);
    }

    void update(int pos, int val) {
        update(0, n - 1, 0, pos, val);
    }
};
