# 题目信息

# Lose it!

## 题目描述

You are given an array $ a $ consisting of $ n $ integers. Each $ a_i $ is one of the six following numbers: $ 4, 8, 15, 16, 23, 42 $ .

Your task is to remove the minimum number of elements to make this array good.

An array of length $ k $ is called good if $ k $ is divisible by $ 6 $ and it is possible to split it into $ \frac{k}{6} $ subsequences $ 4, 8, 15, 16, 23, 42 $ .

Examples of good arrays:

- $ [4, 8, 15, 16, 23, 42] $ (the whole array is a required sequence);
- $ [4, 8, 4, 15, 16, 8, 23, 15, 16, 42, 23, 42] $ (the first sequence is formed from first, second, fourth, fifth, seventh and tenth elements and the second one is formed from remaining elements);
- $ [] $ (the empty array is good).

Examples of bad arrays:

- $ [4, 8, 15, 16, 42, 23] $ (the order of elements should be exactly $ 4, 8, 15, 16, 23, 42 $ );
- $ [4, 8, 15, 16, 23, 42, 4] $ (the length of the array is not divisible by $ 6 $ );
- $ [4, 8, 15, 16, 23, 42, 4, 8, 15, 16, 23, 23] $ (the first sequence can be formed from first six elements but the remaining array cannot form the required sequence).

## 样例 #1

### 输入

```
5
4 8 15 16 23
```

### 输出

```
5
```

## 样例 #2

### 输入

```
12
4 8 4 15 16 8 23 15 16 42 23 42
```

### 输出

```
0
```

## 样例 #3

### 输入

```
15
4 8 4 8 15 16 8 16 23 15 16 4 42 23 42
```

### 输出

```
3
```

# AI分析结果

### 题目内容重写
给定一个由 $n$ 个整数组成的数组 $a$，每个 $a_i$ 是以下六个数字之一：$4, 8, 15, 16, 23, 42$。

你的任务是删除最少的元素，使得数组变得“好”。

一个长度为 $k$ 的数组被称为“好”的，如果 $k$ 能被 $6$ 整除，并且可以将它分成 $k/6$ 个子序列，每个子序列都是 $4, 8, 15, 16, 23, 42$。

### 算法分类
贪心、离散化

### 题解分析与结论
本题的核心是通过贪心策略和离散化技术，找到能够组成最多完整子序列的元素数量，从而计算出需要删除的最少元素数。大多数题解都采用了类似的方法，即通过记录每个数字的前一个数字的匹配情况，逐步构建完整的子序列。

### 精选题解
#### 题解1：Lily_White (5星)
**关键亮点**：
- 使用离散化技术将数字映射为1到6，简化了后续处理。
- 通过记录每个数字的前一个数字的匹配情况，逐步构建完整的子序列。
- 代码简洁，逻辑清晰，时间复杂度为 $O(n)$。

**核心代码**：
```cpp
for (int i = 1; i <= n; i++) {
    if (a[i] == 1)
        cnt[1]++;
    else {
        if (cnt[a[i] - 1]) {
            cnt[a[i]]++;
            cnt[a[i] - 1]--;
        }
    }
}
cout << n - 6 * cnt[6] << endl;
```

#### 题解2：JHR100330 (4星)
**关键亮点**：
- 详细解释了离散化和贪心策略的实现过程。
- 通过记录每个数字的前一个数字的匹配情况，逐步构建完整的子序列。
- 代码结构清晰，易于理解。

**核心代码**：
```cpp
for(int i = 1; i <= n; i ++){
    scanf("%d", &a);
    a = change[a];
    if(a == 1)
        cnt[a] ++;
    else if(cnt[a - 1] != 0){
        cnt[a - 1] --;
        cnt[a] ++;
    }
}
printf("%d\n", n - cnt[6] * 6);
```

#### 题解3：Strong_Jelly (4星)
**关键亮点**：
- 使用map和stack进行匹配，虽然复杂度较高，但思路新颖。
- 通过栈结构记录每个数字的匹配情况，逐步构建完整的子序列。
- 代码实现较为复杂，但思路清晰。

**核心代码**：
```cpp
for(register int i = 1; i <= n; ++i) {
    if(q[i] == 4) {
        pru[++z].push(q[i]);
        f = true;
    } else {
        for(register int j = o; j <= z; ++j) {
            if(mp[q[i]] == pru[j].top()) {
                pru[j].push(q[i]);
                f = true;
            }
        }
    }
    if(!f) ++ans;
}
```

### 最优关键思路
通过离散化将数字映射为1到6，然后使用贪心策略记录每个数字的前一个数字的匹配情况，逐步构建完整的子序列。最终通过计算完整子序列的数量，得出需要删除的最少元素数。

### 可拓展之处
类似的问题可以通过离散化和贪心策略来解决，尤其是在需要匹配特定序列或模式的场景中。例如，匹配其他固定模式的序列，或者在某些约束条件下寻找最优解。

### 推荐题目
1. [P1177 【模板】快速排序](https://www.luogu.com.cn/problem/P1177)
2. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)
3. [P1048 采药](https://www.luogu.com.cn/problem/P1048)

---
处理用时：26.64秒