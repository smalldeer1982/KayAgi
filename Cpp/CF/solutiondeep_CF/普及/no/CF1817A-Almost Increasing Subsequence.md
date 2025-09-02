# 题目信息

# Almost Increasing Subsequence

## 题目描述

A sequence is almost-increasing if it does not contain three consecutive elements $ x, y, z $ such that $ x\ge y\ge z $ .

You are given an array $ a_1, a_2, \dots, a_n $ and $ q $ queries.

Each query consists of two integers $ 1\le l\le r\le n $ . For each query, find the length of the longest almost-increasing subsequence of the subarray $ a_l, a_{l+1}, \dots, a_r $ .

A subsequence is a sequence that can be derived from the given sequence by deleting zero or more elements without changing the order of the remaining elements.

## 说明/提示

In the first query, the subarray is $ a_1, a_2, a_3 = [1,2,4] $ . The whole subarray is almost-increasing, so the answer is $ 3 $ .

In the second query, the subarray is $ a_1, a_2, a_3,a_4 = [1,2,4,3] $ . The whole subarray is a almost-increasing, because there are no three consecutive elements such that $ x \geq y \geq z $ . So the answer is $ 4 $ .

In the third query, the subarray is $ a_2, a_3, a_4, a_5 = [2, 4, 3, 3] $ . The whole subarray is not almost-increasing, because the last three elements satisfy $ 4 \geq 3 \geq 3 $ . An almost-increasing subsequence of length $ 3 $ can be found (for example taking $ a_2,a_3,a_5 = [2,4,3] $ ). So the answer is $ 3 $ .

## 样例 #1

### 输入

```
9 8
1 2 4 3 3 5 6 2 1
1 3
1 4
2 5
6 6
3 7
7 8
1 8
8 8```

### 输出

```
3
4
3
1
4
2
7
1```

# AI分析结果

### 题目内容重写

**几乎递增子序列**

**题目描述**

一个序列是**几乎递增**的，如果它不包含三个连续的元素 $x, y, z$ 满足 $x \ge y \ge z$。

给定一个数组 $a_1, a_2, \dots, a_n$ 和 $q$ 个查询。

每个查询由两个整数 $1 \le l \le r \le n$ 组成。对于每个查询，找到子数组 $a_l, a_{l+1}, \dots, a_r$ 中最长的几乎递增子序列的长度。

子序列是指通过删除零个或多个元素而不改变剩余元素的顺序从给定序列中派生的序列。

**说明/提示**

在第一个查询中，子数组是 $a_1, a_2, a_3 = [1, 2, 4]$。整个子数组是几乎递增的，所以答案是 $3$。

在第二个查询中，子数组是 $a_1, a_2, a_3, a_4 = [1, 2, 4, 3]$。整个子数组是几乎递增的，因为没有三个连续的元素满足 $x \ge y \ge z$。所以答案是 $4$。

在第三个查询中，子数组是 $a_2, a_3, a_4, a_5 = [2, 4, 3, 3]$。整个子数组不是几乎递增的，因为最后三个元素满足 $4 \ge 3 \ge 3$。一个长度为 $3$ 的几乎递增子序列可以是 $a_2, a_3, a_5 = [2, 4, 3]$。所以答案是 $3$。

**样例 #1**

**输入**

```
9 8
1 2 4 3 3 5 6 2 1
1 3
1 4
2 5
6 6
3 7
7 8
1 8
8 8
```

**输出**

```
3
4
3
1
4
2
7
1
```

### 算法分类
前缀和

### 综合分析与结论

该题目要求我们找到给定区间内最长的几乎递增子序列的长度。几乎递增子序列的定义是序列中不存在三个连续的元素 $x, y, z$ 满足 $x \ge y \ge z$。多个题解都采用了前缀和的思想来解决这个问题，通过预处理序列中满足 $x \ge y \ge z$ 的三元组的位置，然后在查询时通过前缀和数组快速计算区间内需要删除的元素数量，从而得到最长几乎递增子序列的长度。

### 评分较高的题解

#### 1. 作者：2021sunzishan (赞：8)
**星级：4星**
**关键亮点：**
- 使用前缀和数组 $s[i]$ 记录以 $i$ 结尾的满足 $x \ge y \ge z$ 的三元组数量。
- 查询时通过 $s[r] - s[l+1]$ 快速计算区间内需要删除的元素数量。
- 代码简洁，思路清晰。

**核心代码：**
```cpp
for(int i=1; i<=n; i++) {
    a[i]=read();
    if(i<3)continue;
    if(a[i]<=a[i-1]&&a[i-1]<=a[i-2])
        s[i]=s[i-1]+1;
    else
        s[i]=s[i-1];
}
while(m--) {
    int l=read(),r=read();
    int ls=r-l+1;
    if(ls<=2)
        printf("%d\n",ls);
    else
        printf("%d\n",ls-(s[r]-s[l+1]));
}
```

#### 2. 作者：Withershine (赞：8)
**星级：4星**
**关键亮点：**
- 详细解释了前缀和数组的定义和使用方法。
- 提供了对区间内满足条件的三元组的数量计算方法的证明。
- 代码实现清晰，逻辑严谨。

**核心代码：**
```cpp
for(int i=1; i<=n; i++) {
    a[i]=read();
    if(i>=3) {
        now = 0;
        if(a[i-2]>=a[i-1]&&a[i-1]>=a[i])
            now = 1;
        f[i] = f[i-1] + now;
    }
}
while(q--) {
    l = read();
    r = read();
    printf("%lld\n", answer(l, r));
}
```

#### 3. 作者：Shunpower (赞：3)
**星级：4星**
**关键亮点：**
- 将序列分成若干不上升段，并计算每个段对答案的贡献。
- 通过前缀和快速计算区间内需要删除的元素数量。
- 代码实现简洁，思路新颖。

**核心代码：**
```cpp
for(int i=1; i<=n; i++) {
    a[i]=read();
    if(i>=3) {
        now = 0;
        if(a[i-2]>=a[i-1]&&a[i-1]>=a[i])
            now = 1;
        f[i] = f[i-1] + now;
    }
}
while(q--) {
    l = read();
    r = read();
    printf("%lld\n", answer(l, r));
}
```

### 最优关键思路或技巧
- **前缀和数组**：通过预处理序列中满足 $x \ge y \ge z$ 的三元组的位置，快速计算区间内需要删除的元素数量。
- **区间处理**：在查询时，通过前缀和数组 $s[r] - s[l+1]$ 快速得到区间内需要删除的元素数量，从而得到最长几乎递增子序列的长度。

### 可拓展之处
- 类似的问题可以通过前缀和或其他预处理方法来优化查询效率。
- 可以扩展到处理其他类型的子序列问题，如最长递增子序列、最长不下降子序列等。

### 推荐题目
1. [P3374 【模板】树状数组 1](https://www.luogu.com.cn/problem/P3374)
2. [P3368 【模板】树状数组 2](https://www.luogu.com.cn/problem/P3368)
3. [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)

---
处理用时：37.15秒