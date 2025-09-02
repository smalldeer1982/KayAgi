# 题目信息

# [ICPC 2021 Nanjing R] Paimon Sorting

## 题目描述

Paimon just invents a new sorting algorithm which looks much like $\textit{bubble sort}$, with a few differences. It accepts a $1$-indexed sequence $A$ of length $n$ and sorts it. Its pseudo-code is shown below.

```cpp
// The Sorting Algorithm
SORT(A)
  for i from 1 to n // n is the number of elements if A
    for j from 1 to n
      if a[i] < a[j] // a[i] is the i-th element in A
        Swap a[i] and a[j]
```


If you don't believe this piece of algorithm can sort a sequence it will also be your task to prove it. Anyway here comes the question:

Given an integer sequence $A = a_1, a_2, \cdots, a_n$ of length $n$, for each of its prefix $A_k$ of length $k$ (that is, for each $1 \le k \le n$, consider the subsequence $A_k = a_1, a_2, \cdots, a_k$), count the number of swaps performed if we call $\text{SORT}(A_k)$.

## 样例 #1

### 输入

```
3
5
2 3 2 1 5
3
1 2 3
1
1
```

### 输出

```
0 2 3 5 7
0 2 4
0
```

# AI分析结果

### 算法分类
树状数组、排序

### 综合分析与结论
本题的核心在于理解并模拟给定的排序算法，计算每个前缀序列的交换次数。通过分析，可以发现该排序算法的交换次数与序列中元素的相对大小关系密切相关。树状数组被广泛用于高效计算前缀和，从而快速统计比当前元素大的元素个数，这是解决本题的关键。

### 所选题解

#### 1. 作者：spider_men (4星)
**关键亮点**：
- 使用树状数组维护比当前元素大的元素个数，思路清晰。
- 通过插入法逐步计算每个前缀的交换次数，代码简洁高效。

**核心代码**：
```cpp
void Add(int x) {
    while(x <= n) {
        c[x]++;
        x += lowbit(x);
    }
}
int Sum(int x) {
    int tot = 0;
    while(x) {
        tot += c[x];
        x -= lowbit(x);
    }
    return tot;
}
void solve() {
    cin >> n;
    memset(c, 0, sizeof(int) * (n + 9));
    memset(vis, 0, sizeof(int) * (n + 9));
    maxn = cnt = flag = 0; ans = 0;
    for(int i = 1; i <= n; i++) {
        cin >> a[i], maxn = max(maxn, a[i]);
    }
    cout << ans;
    vis[a[1]] = 1; Add(a[1]);
    for(int i = 2; i <= n; i++) {
        if(!vis[a[i]]) vis[a[i]] = 1, Add(a[i]);
        if(a[i] == a[1]) flag = 1; cnt += flag - (flag ? a[i] > a[1] : 0);
        if(a[i] > a[1]) ans += 1 + cnt, swap(a[1], a[i]), cnt = flag = 0;
        ans += Sum(a[1]) - Sum(a[i]);
        cout << " " << ans;
    }
    cout << "\n";
}
```

#### 2. 作者：CashCollectFactory (4星)
**关键亮点**：
- 详细分析了不同情况下的交换次数，特别是处理相同元素的情况。
- 使用树状数组进行高效统计，代码结构清晰。

**核心代码**：
```cpp
void Add(int x) {
    for(int i = x; i <= n; i += lowbit(i)) tree[i]++;
}
int Sum(int x) {
    int ans = 0;
    for(int i = x; i; i -= lowbit(i)) ans += tree[i];
    return ans;
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> T;
    while(T--) {
        cin >> n;
        int res = 0, cnt = 0;
        bool flag = 0;
        memset(tree, 0, sizeof(tree));
        memset(vis, 0, sizeof(vis));
        for(int i = 1; i <= n; i++) cin >> a[i];
        cout << 0;
        vis[a[1]] = 1;
        Add(a[1]);
        for(int i = 2; i <= n; i++) {
            if(!vis[a[i]]) vis[a[i]] = 1, Add(a[i]);
            if(a[i] == a[1]) flag = 1;
            cnt += flag - (flag ? a[i] > a[1] : 0);
            if(a[i] > a[1]) res += 1 + cnt, swap(a[1], a[i]), cnt = flag = 0;
            res += Sum(a[1]) - Sum(a[i]);
            cout << " " << res;
        }
        cout << endl;
    }
    return 0;
}
```

### 最优关键思路或技巧
- **树状数组的应用**：用于高效计算比当前元素大的元素个数，这是解决本题的核心。
- **逐步插入法**：通过逐步插入元素并维护当前最大元素，计算每个前缀的交换次数。

### 可拓展之处
- 类似的问题可以通过树状数组或线段树来高效处理前缀和或区间查询。
- 可以进一步优化处理相同元素的情况，减少不必要的计算。

### 推荐题目
1. [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)
2. [P3374 树状数组 1](https://www.luogu.com.cn/problem/P3374)
3. [P3368 树状数组 2](https://www.luogu.com.cn/problem/P3368)

### 个人心得
- **调试经历**：在处理相同元素时，容易忽略其对交换次数的影响，需要仔细分析每种情况。
- **顿悟感想**：树状数组在处理前缀和问题时非常高效，掌握其应用可以解决许多类似问题。

---
处理用时：26.60秒