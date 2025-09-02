# 题目信息

# Random Events

## 题目描述

Ron is a happy owner of a permutation $ a $ of length $ n $ .

A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array) and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1461C/11faf1b639f9cfdf4aa7dcbd7d3e47925fd41e48.png)Ron's permutation is subjected to $ m $ experiments of the following type: ( $ r_i $ , $ p_i $ ). This means that elements in range $ [1, r_i] $ (in other words, the prefix of length $ r_i $ ) have to be sorted in ascending order with the probability of $ p_i $ . All experiments are performed in the same order in which they are specified in the input data.

As an example, let's take a look at a permutation $ [4, 2, 1, 5, 3] $ and an experiment ( $ 3, 0.6 $ ). After such an experiment with the probability of $ 60\% $ the permutation will assume the form $ [1, 2, 4, 5, 3] $ and with a $ 40\% $ probability it will remain unchanged.

You have to determine the probability of the permutation becoming completely sorted in ascending order after $ m $ experiments.

## 说明/提示

Explanation of the first test case: It can be demonstrated that whether the final permutation is sorted or not depends solely on sorting being performed in the $ (4, 0.6) $ experiment.

## 样例 #1

### 输入

```
4
4 3
4 3 2 1
1 0.3
3 1
4 0.6
5 3
4 2 1 3 5
3 0.8
4 0.6
5 0.3
6 5
1 3 2 4 5 6
4 0.9
5 0.3
2 0.4
6 0.7
3 0.5
4 2
1 2 3 4
2 0.5
4 0.1```

### 输出

```
0.600000
0.720000
0.989500
1.000000```

# AI分析结果

### 题目内容重写

**随机事件**

**题目描述**

Ron 是一个长度为 $n$ 的排列 $a$ 的快乐拥有者。

长度为 $n$ 的排列是一个由 $1$ 到 $n$ 的 $n$ 个不同整数组成的数组，顺序任意。例如，$[2,3,1,5,4]$ 是一个排列，但 $[1,2,2]$ 不是排列（$2$ 在数组中出现了两次），$[1,3,4]$ 也不是排列（$n=3$ 但数组中有 $4$）。

Ron 的排列将进行 $m$ 次如下类型的实验：$(r_i, p_i)$。这意味着以 $p_i$ 的概率对前 $r_i$ 个元素（即长度为 $r_i$ 的前缀）进行升序排序。所有实验按照输入数据中指定的顺序进行。

例如，考虑一个排列 $[4, 2, 1, 5, 3]$ 和一个实验 $(3, 0.6)$。在这样的实验后，有 $60\%$ 的概率排列会变成 $[1, 2, 4, 5, 3]$，有 $40\%$ 的概率排列保持不变。

你需要确定在 $m$ 次实验后，排列完全按升序排列的概率。

**说明/提示**

第一个测试用例的解释：可以证明，最终排列是否有序仅取决于 $(4, 0.6)$ 实验是否成功。

**样例 #1**

**输入**

```
4
4 3
4 3 2 1
1 0.3
3 1
4 0.6
5 3
4 2 1 3 5
3 0.8
4 0.6
5 0.3
6 5
1 3 2 4 5 6
4 0.9
5 0.3
2 0.4
6 0.7
3 0.5
4 2
1 2 3 4
2 0.5
4 0.1
```

**输出**

```
0.600000
0.720000
0.989500
1.000000
```

### 算法分类
概率论

### 题解分析与结论

题目要求计算在多次随机事件后，排列完全升序的概率。核心思路是找到哪些操作是“决定性”的，即这些操作能够直接使排列升序。其他操作可以忽略，因为它们的影响已经被包含在决定性操作中。

### 高星题解

#### 题解1：Blunt_Feeling (5星)
**关键亮点**：
- 从后往前找到第一个不匹配的位置，确定哪些操作是决定性的。
- 使用动态规划的思想逐步计算概率，公式为 $f_i = (1 - f_{i-1}) \times p_i$。
- 代码简洁，逻辑清晰。

**核心代码**：
```cpp
int mark = 0;
Rep(i, n, 1) {
    if (a[i] != b[i]) {
        mark = i;
        break;
    }
}
double ans = 0;
while (m--) {
    int r; double p;
    cin >> r >> p;
    if (r >= mark) {
        ans += (1 - ans) * p;
    }
}
if (mark == 0) {
    cout << 1 << endl;
    continue;
}
printf("%.8lf\n", ans);
```

#### 题解2：IIIIndex (4星)
**关键亮点**：
- 从后往前找到第一个不匹配的位置，确定哪些操作是决定性的。
- 使用累乘的方式计算不排序的概率，最终用1减去这个概率得到结果。
- 代码逻辑清晰，处理了特殊情况。

**核心代码**：
```cpp
int last = n + 1;
for (int i = n; i > 0; i--) {
    if (a[i] == i) {
        last = i;
    } else break;
}
double ans = 1;
for (int i = 0; i < m; i++) {
    int r; double p;
    cin >> r >> p;
    if (r >= last - 1) {
        ans *= (1 - p);
    }
}
if (last == 1) {
    printf("1.000000\n");
} else {
    printf("%.6lf\n", 1 - ans);
}
```

#### 题解3：RockyYue (4星)
**关键亮点**：
- 从后往前找到第一个不匹配的位置，确定哪些操作是决定性的。
- 使用累乘的方式计算不排序的概率，最终用1减去这个概率得到结果。
- 代码简洁，处理了特殊情况。

**核心代码**：
```cpp
int k = -1;
for (int i = n; i; --i) {
    if (a[i] != i) {
        k = i;
        break;
    }
}
if (k == -1) {
    cout << 1 << '\n';
    continue;
}
double res = 1;
for (int i = 1; i <= m; ++i) {
    if (r[i] < k) {
        continue;
    }
    res = res == 0 ? (1 - p[i]) : res * (1 - p[i]);
}
cout << fixed << setprecision(6) << 1 - res << '\n';
```

### 最优关键思路
1. **从后往前找到第一个不匹配的位置**：这是确定哪些操作是决定性的关键步骤。
2. **动态计算概率**：使用公式 $f_i = (1 - f_{i-1}) \times p_i$ 或累乘不排序的概率，最终用1减去这个概率得到结果。
3. **处理特殊情况**：如果排列已经有序，直接输出1。

### 拓展思路
类似的问题可以出现在其他概率相关的题目中，例如多次独立事件的累积概率计算。可以考虑使用类似的方法，找到决定性事件，然后计算其影响。

### 推荐题目
1. [P3802 小魔女帕琪](https://www.luogu.com.cn/problem/P3802)
2. [P4316 绿豆蛙的归宿](https://www.luogu.com.cn/problem/P4316)
3. [P1850 换教室](https://www.luogu.com.cn/problem/P1850)

---
处理用时：45.28秒