# 题目信息

# The Third Problem

## 题目描述

You are given a permutation $ a_1,a_2,\ldots,a_n $ of integers from $ 0 $ to $ n - 1 $ . Your task is to find how many permutations $ b_1,b_2,\ldots,b_n $ are similar to permutation $ a $ .

Two permutations $ a $ and $ b $ of size $ n $ are considered similar if for all intervals $ [l,r] $ ( $ 1 \le l \le r \le n $ ), the following condition is satisfied: $ $$$\operatorname{MEX}([a_l,a_{l+1},\ldots,a_r])=\operatorname{MEX}([b_l,b_{l+1},\ldots,b_r]), $ $  where the  $ \\operatorname{MEX} $  of a collection of integers  $ c\_1,c\_2,\\ldots,c\_k $  is defined as the smallest non-negative integer  $ x $  which does not occur in collection  $ c $ . For example,  $ \\operatorname{MEX}(\[1,2,3,4,5\])=0 $ , and  $ \\operatorname{MEX}(\[0,1,2,4,5\])=3 $ .</p><p>Since the total number of such permutations can be very large, you will have to print its remainder modulo  $ 10^9+7 $ .</p><p>In this problem, a permutation of size  $ n $  is an array consisting of  $ n $  distinct integers from  $ 0 $  to  $ n-1 $  in arbitrary order. For example,  $ \[1,0,2,4,3\] $  is a permutation, while  $ \[0,1,1\] $  is not, since  $ 1 $  appears twice in the array.  $ \[0,1,3\] $  is also not a permutation, since  $ n=3 $  and there is a  $ 3$$$ in the array.

## 说明/提示

For the first test case, the only permutations similar to $ a=[4,0,3,2,1] $ are $ [4,0,3,2,1] $ and $ [4,0,2,3,1] $ .

For the second and third test cases, the given permutations are only similar to themselves.

For the fourth test case, there are $ 4 $ permutations similar to $ a=[1,2,4,0,5,3] $ :

- $ [1,2,4,0,5,3] $ ;
- $ [1,2,5,0,4,3] $ ;
- $ [1,4,2,0,5,3] $ ;
- $ [1,5,2,0,4,3] $ .

## 样例 #1

### 输入

```
5
5
4 0 3 2 1
1
0
4
0 1 2 3
6
1 2 4 0 5 3
8
1 3 7 2 5 0 6 4```

### 输出

```
2
1
1
4
72```

# AI分析结果



### 题目重述
#### 题目描述
给定一个由 $0$ 到 $n-1$ 组成的排列 $a_1,a_2,\ldots,a_n$，求有多少个排列 $b_1,b_2,\ldots,b_n$ 与 $a$ 相似。两个排列相似的条件是：对于所有区间 $[l,r]$，其 $\operatorname{MEX}$ 值相等。$\operatorname{MEX}$ 定义为区间中未出现的最小非负整数。答案需对 $10^9+7$ 取模。

#### 输入输出样例
见原题。

---

### 题解分析与结论
#### 核心思路
所有题解均围绕以下关键点展开：
1. **固定位置观察**：0 和 1 的位置必须与原排列一致，否则单元素区间或特定区间的 MEX 会改变。
2. **动态维护区间**：从 0 开始，逐步处理每个数 $k$，维护当前包含 $0$ 到 $k-1$ 的最左（$l$）和最右（$r$）位置。若 $k$ 在原排列中的位置 $\text{pos}_k$ 落在 $[l, r]$ 内，则其可放置在区间内的剩余空位中，方案数为 $(r-l+1 - k)$；否则必须固定位置，并扩展 $l$ 或 $r$。
3. **乘法原理累乘**：每一步的可用位置数相乘即为最终答案。

#### 最优解代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9 + 7;

int main() {
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        vector<int> pos(n);
        for (int i = 0; i < n; i++) {
            int x; cin >> x;
            pos[x] = i; // 记录每个数的位置
        }
        long long ans = 1;
        int l = pos[0], r = pos[0];
        for (int k = 1; k < n; k++) {
            if (pos[k] > l && pos[k] < r) 
                ans = ans * (r - l + 1 - k) % MOD;
            else {
                l = min(l, pos[k]);
                r = max(r, pos[k]);
            }
        }
        cout << ans << '\n';
    }
}
```

#### 关键技巧
1. **区间维护**：用 $l$ 和 $r$ 动态记录已处理数的最小和最大位置，判断当前数的位置是否可调整。
2. **贡献计算**：若可调整，剩余空位数为区间长度减去已处理的数个数（$k$），直接累乘。
3. **线性复杂度**：仅需遍历一次排列，时间复杂度 $O(n)$，空间复杂度 $O(n)$。

---

### 推荐相似题目
1. [CF1295F Good Contest](https://codeforces.com/problemset/problem/1295/F) - 区间划分与计数。
2. [洛谷 P1971 最大 MEX 问题](https://www.luogu.com.cn/problem/P1971) - MEX 性质应用。
3. [CF1690G Unusual MEX](https://codeforces.com/problemset/problem/1690/G) - 动态维护区间与 MEX 结合。

---
处理用时：74.40秒