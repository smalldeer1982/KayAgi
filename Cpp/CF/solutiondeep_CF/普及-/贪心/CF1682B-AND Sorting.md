# 题目信息

# AND Sorting

## 题目描述

You are given a permutation $ p $ of integers from $ 0 $ to $ n-1 $ (each of them occurs exactly once). Initially, the permutation is not sorted (that is, $ p_i>p_{i+1} $ for at least one $ 1 \le i \le n - 1 $ ).

The permutation is called $ X $ -sortable for some non-negative integer $ X $ if it is possible to sort the permutation by performing the operation below some finite number of times:

- Choose two indices $ i $ and $ j $ $ (1 \le i \lt j \le n) $ such that $ p_i \& p_j = X $ .
- Swap $ p_i $ and $ p_j $ .

Here $ \& $ denotes the [bitwise AND operation](https://en.wikipedia.org/wiki/Bitwise_operation#AND).

Find the maximum value of $ X $ such that $ p $ is $ X $ -sortable. It can be shown that there always exists some value of $ X $ such that $ p $ is $ X $ -sortable.

## 说明/提示

In the first test case, the only $ X $ for which the permutation is $ X $ -sortable are $ X = 0 $ and $ X = 2 $ , maximum of which is $ 2 $ .

Sorting using $ X = 0 $ :

- Swap $ p_1 $ and $ p_4 $ , $ p = [2, 1, 3, 0] $ .
- Swap $ p_3 $ and $ p_4 $ , $ p = [2, 1, 0, 3] $ .
- Swap $ p_1 $ and $ p_3 $ , $ p = [0, 1, 2, 3] $ .

Sorting using $ X = 2 $ :

- Swap $ p_3 $ and $ p_4 $ , $ p = [0, 1, 2, 3] $ .

In the second test case, we must swap $ p_1 $ and $ p_2 $ which is possible only with $ X = 0 $ .

## 样例 #1

### 输入

```
4
4
0 1 3 2
2
1 0
7
0 1 2 3 5 6 4
5
0 3 2 1 4```

### 输出

```
2
0
4
1```

# AI分析结果



## 题目重写

### AND Sorting

#### 题目描述

给定一个包含 $0$ 到 $n-1$ 的整数排列 $p$（每个数恰好出现一次）。初始时该排列未排序（即至少存在一个 $i$ 使得 $p_i > p_{i+1}$）。

若存在一个非负整数 $X$，使得通过有限次以下操作可以将排列排序，则称该排列是 $X$-可排序的：

- 选择两个下标 $i$ 和 $j$（$1 \le i < j \le n$），且 $p_i \& p_j = X$。
- 交换 $p_i$ 和 $p_j$。

其中 $\&$ 表示按位与操作。

求使得 $p$ 是 $X$-可排序的最大 $X$。可以证明总存在某个 $X$ 使得 $p$ 是 $X$-可排序的。

#### 样例 #1

输入：
```
4
4
0 1 3 2
2
1 0
7
0 1 2 3 5 6 4
5
0 3 2 1 4
```
输出：
```
2
0
4
1
```

---

## 题解分析与结论

### 关键思路
**所有不在正确位置上的元素的按位与即为最大X**  
通过观察发现，需要交换的元素必须满足它们的按位与结果至少为X。最大X的取值是所有需要交换元素的共有二进制位，即它们的按位与结果。这是因为：
1. 需要交换的元素必须能够通过交换路径到达正确位置。
2. 按位与的运算特性决定了所有元素的共有位才能构成最大X。

### 最优题解

#### 题解1：yitian_（4星）
**核心亮点**：简洁的线性扫描实现，直接在输入时处理数据，空间复杂度O(1)。
```cpp
int ans = -1;
for (int i = 0; i < n; i++) {
    cin >> p[i];
    if (p[i] != i) {
        ans = (ans == -1) ? p[i] : ans & p[i];
    }
}
cout << ans << endl;
```
**实现思想**：初始化`ans`为-1（二进制全1），遍历时遇到不在正确位置的元素，不断进行按位与操作。

#### 题解2：hdkghc（5星）
**核心亮点**：利用按位与的性质，直接动态维护结果，无需额外存储数组。
```cpp
int ans = -1; 
for (int i = 0; i < n; i++) {
    int x; cin >> x;
    if (x != i) {
        ans &= x; // -1的补码全1，首次&=等效赋值
    }
}
cout << ans << endl;
```
**代码技巧**：利用`-1`的二进制全1特性，使得首次按位与操作等效于赋值，后续操作自然累积按位与结果。

#### 题解3：EternalHeart1314（4星）
**核心亮点**：显式收集所有需要处理的元素，逻辑更直观。
```cpp
vector<int> wrong;
for (int i = 0; i < n; ++i) {
    if (p[i] != i) {
        wrong.push_back(p[i]);
    }
}
int ans = wrong[0];
for (int num : wrong) {
    ans &= num;
}
cout << ans << endl;
```
**适用场景**：适合需要明确分离处理逻辑的场景，便于调试和扩展。

---

## 扩展与总结

### 关键技巧总结
1. **按位与的累积性质**：多个数的按位与结果会保留所有数共有的二进制位。
2. **初始值设定**：利用-1（二进制全1）作为初始值，简化首次赋值逻辑。
3. **问题转化**：将交换条件转化为需要交换元素的共有位分析。

### 同类题目推荐
1. [CF1095C - Powers Of Two](https://www.luogu.com.cn/problem/CF1095C)（位运算分解）
2. [CF1368B - Codeforces Subsequences](https://www.luogu.com.cn/problem/CF1368B)（位模式构造）
3. [P2114 [NOI2014] 起床困难综合症](https://www.luogu.com.cn/problem/P2114)（位运算策略优化）

### 个人心得摘录
- **hdkghc**提到：“利用`-1`的补码特性，使得首次按位与等效赋值”——这是对二进制特性的巧妙应用。
- **听取MLE声一片**指出：“所有不在原位置的数都要进行交换”——这是问题转化的关键观察点。

---
处理用时：85.82秒