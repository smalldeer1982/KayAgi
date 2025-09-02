# 题目信息

# Merge it!

## 题目描述

You are given an array $ a $ consisting of $ n $ integers $ a_1, a_2, \dots , a_n $ .

In one operation you can choose two elements of the array and replace them with the element equal to their sum (it does not matter where you insert the new element). For example, from the array $ [2, 1, 4] $ you can obtain the following arrays: $ [3, 4] $ , $ [1, 6] $ and $ [2, 5] $ .

Your task is to find the maximum possible number of elements divisible by $ 3 $ that are in the array after performing this operation an arbitrary (possibly, zero) number of times.

You have to answer $ t $ independent queries.

## 说明/提示

In the first query of the example you can apply the following sequence of operations to obtain $ 3 $ elements divisible by $ 3 $ : $ [3, 1, 2, 3, 1] \rightarrow [3, 3, 3, 1] $ .

In the second query you can obtain $ 3 $ elements divisible by $ 3 $ with the following sequence of operations: $ [1, 1, 1, 1, 1, 2, 2] \rightarrow [1, 1, 1, 1, 2, 3] \rightarrow [1, 1, 1, 3, 3] \rightarrow [2, 1, 3, 3] \rightarrow [3, 3, 3] $ .

## 样例 #1

### 输入

```
2
5
3 1 2 3 1
7
1 1 1 1 1 2 2
```

### 输出

```
3
3
```

# AI分析结果

### 题目翻译

# 合并它！

## 题目描述

给定一个由 $n$ 个整数 $a_1, a_2, \dots , a_n$ 组成的数组 $a$。

在一次操作中，你可以选择数组中的两个元素，并将它们替换为它们的和（新元素可以插入到数组中的任意位置）。例如，从数组 $[2, 1, 4]$ 中，你可以得到以下数组：$[3, 4]$、$[1, 6]$ 和 $[2, 5]$。

你的任务是找到在执行任意次（可能为零次）操作后，数组中能被 $3$ 整除的元素的最大可能数量。

你需要回答 $t$ 个独立的查询。

## 说明/提示

在第一个示例查询中，你可以通过以下操作序列得到 $3$ 个能被 $3$ 整除的元素：$[3, 1, 2, 3, 1] \rightarrow [3, 3, 3, 1]$。

在第二个查询中，你可以通过以下操作序列得到 $3$ 个能被 $3$ 整除的元素：$[1, 1, 1, 1, 1, 2, 2] \rightarrow [1, 1, 1, 1, 2, 3] \rightarrow [1, 1, 1, 3, 3] \rightarrow [2, 1, 3, 3] \rightarrow [3, 3, 3]$。

## 样例 #1

### 输入

```
2
5
3 1 2 3 1
7
1 1 1 1 1 2 2
```

### 输出

```
3
3
```

### 算法分类
贪心

### 题解分析与结论

这道题的核心思路是通过贪心策略，尽可能多地合并元素，使得最终数组中能被3整除的元素数量最大化。题解的关键在于对数组中元素按模3的余数进行分类，然后根据余数的不同进行合并操作。

### 所选高星题解

#### 题解1：Raych123 (4星)
**关键亮点**：
- 通过模3的余数分类，简化问题。
- 详细解释了合并策略，优先合并余1和余2的元素，再将剩余的余1或余2元素三个一组合并。
- 代码简洁，逻辑清晰。

**核心代码**：
```cpp
int cnt[3] = {};
for (int i = 1; i <= n; i++) {
    int a;
    scanf("%d", &a);
    cnt[a % 3]++;
}
if (cnt[1] > cnt[2]) {
    cnt[1] -= cnt[2];
    printf("%d\n", cnt[0] + cnt[2] + cnt[1] / 3);
} else if (cnt[1] == cnt[2]) {
    printf("%d\n", cnt[0] + cnt[1]);
} else {
    cnt[2] -= cnt[1];
    printf("%d\n", cnt[0] + cnt[1] + cnt[2] / 3);
}
```

#### 题解2：fjy666 (4星)
**关键亮点**：
- 同样通过模3的余数分类，简化问题。
- 使用`min`和`max`函数简化了合并逻辑，代码更加简洁。
- 时间复杂度为$\Theta(n)$，空间复杂度为$\Theta(1)$。

**核心代码**：
```cpp
int x = min(cnt[1], cnt[2]);
int y = max(cnt[1], cnt[2]) - x;
printf("%d\n", cnt[0] + x + (y / 3));
```

#### 题解3：sinsop90 (4星)
**关键亮点**：
- 使用贪心策略，优先合并余1和余2的元素，再将剩余的余1或余2元素三个一组合并。
- 代码简洁，逻辑清晰，易于理解。

**核心代码**：
```cpp
int ans = 0;
memset(t, 0, sizeof(t));
for(int i = 1; i <= n; i++) {
    cin >> mps[i];
    if(mps[i] % 3 == 0) {
        ans++;
    } else if(mps[i] % 3 == 1) {
        t[1]++;
    } else {
        t[2]++;
    }
}
cout << ans + min(t[1], t[2]) + (max(t[1], t[2]) - min(t[1], t[2])) / 3 << endl;
```

### 最优关键思路或技巧
- **模3分类**：通过将数组中的元素按模3的余数分类，简化问题。
- **贪心策略**：优先合并余1和余2的元素，再将剩余的余1或余2元素三个一组合并，以最大化能被3整除的元素数量。

### 可拓展之处
- 类似的问题可以通过模数分类和贪心策略来解决，例如求数组中能被其他数整除的元素的最大数量。

### 推荐题目
1. [P3740 - 线段树+离散化](https://www.luogu.com.cn/problem/P3740)
2. [P1004 - 方格取数](https://www.luogu.com.cn/problem/P1004)
3. [P1048 - 采药](https://www.luogu.com.cn/problem/P1048)

---
处理用时：32.70秒