# 题目信息

# Index and Maximum Value

## 题目描述

Index 在生日派对上收到了另一个整数数组 $a_1,a_2,\dots,a_n$。随后，她准备对这个数组进行一些操作。

形式化地，她决定对这个数组执行 $m$ 次操作。有两种操作类型：
- 第一种操作形如 $\texttt{+ l r}$。给定两个正整数 $l,r$，将所有满足 $1\le i\le n,l\le a_i\le r$ 的 $a_i$ 的值改为 $a_i+1$。
- 第二种操作形如 $\texttt{- l r}$。给定两个正整数 $l,r$，将所有满足 $1\le i\le n,l\le a_i\le r$ 的 $a_i$ 的值改为 $a_i-1$。

举个例子，如果给定的数组 $a$ 初始为 $[7,1,3,4,3]$，在执行操作 $\texttt{+ 2 4}$ 后，数组变为 $a=[7,1,4,5,4]$。然后，在执行操作 $\texttt{- 1 10}$ 后，数组变为 $a=[6,0,3,4,3]$。

Index 对 $a$ 数组的最大值很好奇。在每次操作之后，请告诉她 $a$ 数组中的最大值。

## 样例 #1

### 输入

```
5
5 5
1 2 3 2 1
+ 1 3
- 2 3
+ 1 2
+ 2 4
- 6 8
5 5
1 3 3 4 5
+ 1 4
+ 2 3
- 4 5
- 3 3
- 2 6
5 5
1 1 1 1 1
+ 2 3
- 4 5
+ 1 6
- 2 5
+ 1 8
1 1
1
- 1 1
1 1
1000000000
+ 1000000000 1000000000```

### 输出

```
4 4 4 5 5
5 5 4 4 3
1 1 2 1 2
0
1000000001```

# AI分析结果



# Index and Maximum Value

## 题目描述

Index 在生日派对上收到了一个整数数组 $a_1,a_2,\dots,a_n$。她需要对数组进行 $m$ 次操作：

1. **+ l r**：将所有满足 $1\le i\le n$ 且 $l\le a_i\le r$ 的 $a_i$ 的值加 1。
2. **- l r**：将所有满足 $1\le i\le n$ 且 $l\le a_i\le r$ 的 $a_i$ 的值减 1。

每次操作后，输出数组的最大值。

---

## 题解分析与结论

### 关键思路
只需维护当前数组的最大值即可，无需处理整个数组。核心观察点：
1. 非最大值的元素在操作后无法超过当前最大值。
2. 只有当操作区间包含当前最大值时，最大值才会变化（+1/-1）。

### 解决难点
通过分析得出，其他元素的变化不会影响最大值的最终结果。例如：
- 若最大值不在操作区间内，其他元素的增减不会产生更大的值。
- 若最大值在操作区间内，其变化直接决定新的最大值。

### 最优题解（评分≥4星）

#### 1. wangzhaohan2910（5星）
**亮点**：代码简洁高效，直接维护最大值，时间复杂度 $O(n + m)$。
```cpp
int main() {
    int t; cin >> t;
    while (t--) {
        int n, m, maxn = 0;
        cin >> n >> m;
        for (int i = 1; i <= n; i++) {
            int x; cin >> x;
            maxn = max(maxn, x);
        }
        while (m--) {
            char c; int l, r;
            cin >> c >> l >> r;
            if (l <= maxn && maxn <= r) {
                maxn += (c == '+' ? 1 : -1);
            }
            cout << maxn << ' ';
        }
        cout << endl;
    }
}
```

#### 2. 封禁用户（4星）
**亮点**：包含思路证明，增强理解。
```cpp
int main() {
    int T; cin >> T;
    while (T--) {
        int maxn = 0;
        cin >> n >> m;
        while (n--) { 
            int x; cin >> x;
            maxn = max(maxn, x);
        }
        while (m--) {
            char op; int l, r;
            cin >> op >> l >> r;
            if (maxn >= l && maxn <= r) {
                maxn += (op == '+' ? 1 : -1);
            }
            cout << maxn << ' ';
        }
        cout << endl;
    }
}
```

#### 3. masonxiong（4星）
**亮点**：详细分类讨论四种情况，逻辑严谨。
```cpp
int main() {
    ios::sync_with_stdio(false);
    int t; cin >> t;
    while (t--) {
        int n, m, maxv = 0;
        cin >> n >> m;
        for (int i = 0; i < n; i++) {
            int x; cin >> x;
            maxv = max(maxv, x);
        }
        while (m--) {
            char op; int l, r;
            cin >> op >> l >> r;
            if (l <= maxv && maxv <= r) {
                maxv += (op == '+' ? 1 : -1);
            }
            cout << maxv << ' ';
        }
        cout << '\n';
    }
}
```

---

## 拓展与总结

### 类似题目套路
- **维护极值属性**：当题目只需关注极值（最大/最小）时，可尝试直接维护该属性而非整个数据集。
- **区间操作简化**：若操作仅影响满足特定条件的元素，可通过分析条件范围优化计算。

### 推荐题目
1. [P1198 [JSOI2008] 最大数](https://www.luogu.com.cn/problem/P1198)  
   **标签**：动态维护最大值，线段树/单调栈。
2. [P1440 求m区间内的最小值](https://www.luogu.com.cn/problem/P1440)  
   **标签**：滑动窗口，单调队列。
3. [P3870 [TJOI2009] 开关](https://www.luogu.com.cn/problem/P3870)  
   **标签**：区间翻转，维护状态统计。

---
处理用时：60.35秒