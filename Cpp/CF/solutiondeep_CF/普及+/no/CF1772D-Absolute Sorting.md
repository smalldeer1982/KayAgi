# 题目信息

# Absolute Sorting

## 题目描述

You are given an array $ a $ consisting of $ n $ integers. The array is sorted if $ a_1 \le a_2 \le \dots \le a_n $ .

You want to make the array $ a $ sorted by applying the following operation exactly once:

- choose an integer $ x $ , then for every $ i \in [1, n] $ , replace $ a_i $ by $ |a_i - x| $ .

Find any value of $ x $ that will make the array sorted, or report that there is no such value.

## 说明/提示

In the first test case, after using $ x = 4 $ , the array becomes $ [1, 1, 1, 1, 1] $ .

In the third test case, after using $ x = 0 $ , the array becomes $ [1, 2, 3, 4, 5, 6, 7, 8] $ .

In the fourth test case, after using $ x = 42 $ , the array becomes $ [32, 37, 38, 39, 40, 41] $ .

## 样例 #1

### 输入

```
8
5
5 3 3 3 5
4
5 3 4 5
8
1 2 3 4 5 6 7 8
6
10 5 4 3 2 1
3
3 3 1
3
42 43 42
2
100000000 99999999
6
29613295 52036613 75100585 78027446 81409090 73215```

### 输出

```
4
-1
0
42
2
-1
100000000
40741153```

# AI分析结果

### 题目内容重写

**绝对排序**

#### 题目描述

给定一个由 $n$ 个整数组成的数组 $a$。如果 $a_1 \le a_2 \le \dots \le a_n$，则称数组 $a$ 是排序的。

你希望通过以下操作恰好一次来使数组 $a$ 排序：

- 选择一个整数 $x$，然后对于每个 $i \in [1, n]$，将 $a_i$ 替换为 $|a_i - x|$。

找到任何一个能使数组排序的 $x$ 值，或者报告不存在这样的值。

#### 说明/提示

在第一个测试用例中，使用 $x = 4$ 后，数组变为 $[1, 1, 1, 1, 1]$。

在第三个测试用例中，使用 $x = 0$ 后，数组变为 $[1, 2, 3, 4, 5, 6, 7, 8]$。

在第四个测试用例中，使用 $x = 42$ 后，数组变为 $[32, 37, 38, 39, 40, 41]$。

#### 样例 #1

##### 输入

```
8
5
5 3 3 3 5
4
5 3 4 5
8
1 2 3 4 5 6 7 8
6
10 5 4 3 2 1
3
3 3 1
3
42 43 42
2
100000000 99999999
6
29613295 52036613 75100585 78027446 81409090 73215
```

##### 输出

```
4
-1
0
42
2
-1
100000000
40741153
```

### 算法分类

**数学**

### 题解分析与结论

本题的核心在于通过数学推导确定 $x$ 的取值范围，使得对数组中的每个元素 $a_i$ 进行 $|a_i - x|$ 操作后，数组变为非递减序列。各题解均通过分析相邻元素的关系，推导出 $x$ 的取值范围，并通过维护区间交集来找到合适的 $x$。

### 精选题解

#### 题解1：Composite_Function (赞：13)  
**星级：5**  
**关键亮点：**  
- 通过数学推导，清晰地分析了 $x$ 的取值范围，并给出了简洁的代码实现。
- 代码逻辑清晰，时间复杂度为 $O(n)$，效率高。

**核心代码：**
```cpp
l = 0, r = 4e18;
for (int i = 1; i < n; ++i) {
    if (a[i] < a[i + 1]) r = min(r, (a[i] + a[i + 1]) / 2);
    if (a[i] > a[i + 1]) l = max(l, (a[i] + a[i + 1] + 1) / 2);
}
if (l <= r) cout << l << endl;
else cout << -1 << endl;
```

#### 题解2：loser_seele (赞：6)  
**星级：4**  
**关键亮点：**  
- 通过维护 $l$ 和 $r$ 来逐步缩小 $x$ 的取值范围，思路清晰。
- 代码实现简洁，时间复杂度为 $O(n)$。

**核心代码：**
```cpp
int l = 0, r = 2e9;
for (int i = 1; i < n; i++) {
    if (a[i] > a[i + 1]) l = max(l, (a[i] + a[i + 1] + 1) / 2);
    if (a[i] < a[i + 1]) r = min(r, (a[i] + a[i + 1]) / 2);
}
if (l > r) puts("-1");
else cout << l << endl;
```

#### 题解3：FQR_ (赞：4)  
**星级：4**  
**关键亮点：**  
- 通过分类讨论，详细推导了 $x$ 的取值范围，并给出了合理的代码实现。
- 代码结构清晰，易于理解。

**核心代码：**
```cpp
int l = 0, r = 1e9;
for (int i = 1; i < n; i++) {
    if (a[i] < a[i + 1]) r = min(r, (a[i] + a[i + 1]) / 2);
    else if (a[i] > a[i + 1]) l = max(l, (a[i] + a[i + 1] + 1) / 2);
}
if (l <= r) cout << l << endl;
else cout << -1 << endl;
```

### 最优关键思路与技巧

1. **数学推导**：通过分析相邻元素的关系，推导出 $x$ 的取值范围。
2. **区间交集**：通过维护 $l$ 和 $r$ 来逐步缩小 $x$ 的取值范围，最终判断是否存在解。
3. **时间复杂度优化**：所有题解的时间复杂度均为 $O(n)$，效率较高。

### 可拓展之处

类似的问题可以通过数学推导和区间交集的方法来解决，例如在给定条件下寻找满足某种性质的参数值。

### 推荐题目

1. [P1020 导弹拦截](https://www.luogu.com.cn/problem/P1020)
2. [P1091 合唱队形](https://www.luogu.com.cn/problem/P1091)
3. [P1048 采药](https://www.luogu.com.cn/problem/P1048)

---
处理用时：43.68秒