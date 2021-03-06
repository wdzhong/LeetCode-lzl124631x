// OJ: https://leetcode.com/problems/range-sum-query-mutable/
// Author: github.com/lzl124631x
// Time: 
//      NumArray: O(N)
//      update: O(1)
//      sumRange: O(logN)
// Space: O(N
typedef int Merge(const int &a, const int& b);
class SegTree {
    vector<int> tree;
    int N;
    Merge *merge;
    void buildTree(vector<int> &nums) {
        for (int i = 0, j = N; i < N;) tree[j++] = nums[i++];
        for (int i = N - 1; i > 0; --i) tree[i] = merge(tree[2 * i], tree[2 * i + 1]);
    }
public:
    SegTree(vector<int> &nums, Merge merge) {
        N = nums.size();
        tree.resize(N * 2);
        this->merge = merge;
        buildTree(nums);
    }
    
    void update(int i, int val) {
        i += N;
        tree[i] = val;
        while (i > 0) {
            i /= 2;
            tree[i] = merge(tree[2 * i], tree[2 * i + 1]);
        }
    }
    
    int query(int from, int to, int def) {
        int i = from + N, j = to + N;
        int ans = def;
        while (i <= j) {
            if (i % 2) ans = merge(ans, tree[i++]);
            if (j % 2 == 0) ans = merge(ans, tree[j--]);
            i /= 2;
            j /= 2;
        }
        return ans;
    }
};
class NumArray {
    SegTree* tree;
public:
    NumArray(vector<int>& nums) {
        if (nums.empty()) return;
        tree = new SegTree(nums, [](const int &a, const int &b) { return a + b; });
    }
    void update(int i, int val) {
        tree->update(i, val);
    }
    int sumRange(int i, int j) {
        return tree->query(i, j, 0);
    }
};