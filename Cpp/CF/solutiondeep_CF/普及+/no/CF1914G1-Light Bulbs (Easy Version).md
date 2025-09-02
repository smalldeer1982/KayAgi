# 题目信息

# Light Bulbs (Easy Version)

## 题目描述

The easy and hard versions of this problem differ only in the constraints on $ n $ . In the easy version, the sum of values of $ n^2 $ over all test cases does not exceed $ 10^6 $ . Furthermore, $ n $ does not exceed $ 1000 $ in each test case.

There are $ 2n $ light bulbs arranged in a row. Each light bulb has a color from $ 1 $ to $ n $ (exactly two light bulbs for each color).

Initially, all light bulbs are turned off. You choose a set of light bulbs $ S $ that you initially turn on. After that, you can perform the following operations in any order any number of times:

- choose two light bulbs $ i $ and $ j $ of the same color, exactly one of which is on, and turn on the second one;
- choose three light bulbs $ i, j, k $ , such that both light bulbs $ i $ and $ k $ are on and have the same color, and the light bulb $ j $ is between them ( $ i < j < k $ ), and turn on the light bulb $ j $ .

You want to choose a set of light bulbs $ S $ that you initially turn on in such a way that by performing the described operations, you can ensure that all light bulbs are turned on.

Calculate two numbers:

- the minimum size of the set $ S $ that you initially turn on;
- the number of sets $ S $ of minimum size (taken modulo $ 998244353 $ ).

## 样例 #1

### 输入

```
4
2
2 2 1 1
2
1 2 2 1
2
1 2 1 2
5
3 4 4 5 3 1 1 5 2 2```

### 输出

```
2 4
1 2
1 4
2 8```

# AI分析结果

### 题目内容重写（中文）

#### 灯泡（简单版）

**题目描述**

本题的简单版和困难版仅在 $n$ 的约束条件上有所不同。在简单版中，所有测试用例的 $n^2$ 之和不超过 $10^6$，且每个测试用例中的 $n$ 不超过 $1000$。

有 $2n$ 个灯泡排成一行，每个灯泡的颜色为 $1$ 到 $n$ 之间的一个整数（每种颜色恰好有两个灯泡）。

最初，所有灯泡都关闭。你选择一个灯泡集合 $S$，并将它们初始打开。之后，你可以按任意顺序执行以下操作任意次数：

- 选择两个颜色相同且一个打开一个关闭的灯泡 $i$ 和 $j$，并将关闭的灯泡打开；
- 选择三个灯泡 $i, j, k$，其中 $i$ 和 $k$ 是打开的且颜色相同，$j$ 位于它们之间（$i < j < k$），并将灯泡 $j$ 打开。

你需要选择一个初始打开的灯泡集合 $S$，使得通过执行上述操作，可以确保所有灯泡都被打开。

计算两个数字：

- 初始打开的灯泡集合 $S$ 的最小大小；
- 最小大小的集合 $S$ 的数量（模 $998244353$）。

**样例 #1**

**输入**

```
4
2
2 2 1 1
2
1 2 2 1
2
1 2 1 2
5
3 4 4 5 3 1 1 5 2 2
```

**输出**

```
2 4
1 2
1 4
2 8
```

### 算法分类
**并查集**

### 题解分析与结论

#### 题解1：Eibon（4星）
**关键亮点**：
- 使用异或哈希来检测区间是否闭合，从而确定最小集合大小。
- 通过记录哈希值的最后出现位置，避免重复计算。
- 使用乘法原理统计最小集合的数量。

**核心代码**：
```cpp
for(int i=1;i<=2*n;i++){
    int x;
    scanf("%lld",&x);
    cur[i]=cur[i-1]^w[x];
    lst[cur[i]]=i;
    if(!cur[i]){
        ans1++;
    }
}
for(int i=0;i<2*n;i++){
    if(cur[i]){
        continue;
    }
    int j=i+1,res=1;
    while(cur[j]){
        j=lst[cur[j]]+1;
        res++;
    }
    ans2=Mul(ans2,res);
}
```

#### 题解2：Erica_N_Contina（3星）
**关键亮点**：
- 提出“最小偶数序列”概念，并分析其性质。
- 通过划分序列为最小偶数序列，确定最小集合大小。
- 使用桶记录哈希值，剔除子序列中的灯。

**核心代码**：
（未提供完整代码，但思路清晰）

#### 题解3：huangrenheluogu（3星）
**关键亮点**：
- 使用并查集维护等效关系。
- 通过贪心策略选择初始点，确保所有灯被点亮。
- 分析等效传递性，简化问题。

**核心代码**：
（未提供完整代码，但思路清晰）

### 最优关键思路
- **异或哈希**：通过异或哈希检测区间闭合，确定最小集合大小。
- **乘法原理**：使用乘法原理统计最小集合的数量。
- **并查集**：通过并查集维护等效关系，简化问题。

### 可拓展之处
- 类似问题可以通过异或哈希或并查集来解决，特别是涉及区间闭合或等效关系的问题。
- 可以扩展到更复杂的图论问题，如最小生成树或最短路径问题。

### 推荐题目
1. [P1972 [SDOI2009]HH的项链](https://www.luogu.com.cn/problem/P1972)
2. [P3367 【模板】并查集](https://www.luogu.com.cn/problem/P3367)
3. [P3811 【模板】乘法逆元](https://www.luogu.com.cn/problem/P3811)

### 个人心得
- **调试经历**：在使用异或哈希时，确保哈希值的唯一性，避免冲突。
- **踩坑教训**：在统计最小集合数量时，注意避免重复计算，使用乘法原理时需确保每个区间的贡献独立。
- **顿悟感想**：通过异或哈希和并查集的结合，可以高效解决复杂的区间闭合和等效关系问题。

---
处理用时：34.59秒