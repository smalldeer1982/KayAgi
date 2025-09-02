# 题目信息

# Pictures with Kittens (easy version)

## 题目描述

The only difference between easy and hard versions is the constraints.

Vova likes pictures with kittens. The news feed in the social network he uses can be represented as an array of $ n $ consecutive pictures (with kittens, of course). Vova likes all these pictures, but some are more beautiful than the others: the $ i $ -th picture has beauty $ a_i $ .

Vova wants to repost exactly $ x $ pictures in such a way that:

- each segment of the news feed of at least $ k $ consecutive pictures has at least one picture reposted by Vova;
- the sum of beauty values of reposted pictures is maximum possible.

For example, if $ k=1 $ then Vova has to repost all the pictures in the news feed. If $ k=2 $ then Vova can skip some pictures, but between every pair of consecutive pictures Vova has to repost at least one of them.

Your task is to calculate the maximum possible sum of values of reposted pictures if Vova follows conditions described above, or say that there is no way to satisfy all conditions.

## 样例 #1

### 输入

```
5 2 3
5 1 3 10 1
```

### 输出

```
18
```

## 样例 #2

### 输入

```
6 1 5
10 30 30 70 10 10
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
4 3 1
1 100 1 1
```

### 输出

```
100
```

# AI分析结果

### 题目内容
# 小猫图片（简单版本）

## 题目描述
简单版本和困难版本的唯一区别在于数据范围限制。

Vova 喜欢小猫图片。他使用的社交网络中的动态消息流可以表示为一个包含 $n$ 张连续图片的数组（当然都是小猫图片）。Vova 喜欢所有这些图片，但有些图片比其他图片更漂亮：第 $i$ 张图片的美观度为 $a_i$ 。

Vova 想转发恰好 $x$ 张图片，并且要满足以下条件：
- 动态消息流中每至少 $k$ 张连续图片的片段中，至少有一张是 Vova 转发的图片；
- 转发图片的美观度值之和尽可能大。

例如，如果 $k = 1$，那么 Vova 必须转发动态消息流中的所有图片。如果 $k = 2$，那么 Vova 可以跳过一些图片，但在每两张连续图片中，Vova 必须至少转发其中一张。

你的任务是计算如果 Vova 遵循上述条件，转发图片的美观度值之和的最大可能值，或者说明不存在满足所有条件的方法。

## 样例 #1
### 输入
```
5 2 3
5 1 3 10 1
```
### 输出
```
18
```

## 样例 #2
### 输入
```
6 1 5
10 30 30 70 10 10
```
### 输出
```
-1
```

## 样例 #3
### 输入
```
4 3 1
1 100 1 1
```
### 输出
```
100
```

### 算法分类
动态规划

### 题解综合分析与结论
所有题解均采用动态规划算法，状态定义基本一致，都用 $dp_{i,j}$ 表示前 $i$ 个数中选 $j$ 个数且第 $i$ 个数必选时的最大和。状态转移方程为 $dp_{i,j}=\max\limits_{l=\max(0, i - k)}^{i - 1} dp_{l,j - 1} + a_i$ ，即从前面满足条件的状态转移而来。主要难点在于如何优化转移过程以及处理非法情况。部分题解提到可直接暴力 $O(n^3)$ 转移，由于本题数据范围小可以通过，但对于加强版则需优化。优化思路是利用单调队列维护区间最大值，将时间复杂度降为 $O(n^2)$ 。同时，所有题解都强调要将 $dp$ 数组初始化为负无穷，以避免非法情况转移导致答案错误。

### 通用建议与扩展思路
对于此类动态规划问题，关键在于准确理解题意确定状态和转移方程。在数据范围允许时，暴力转移是一种可行方法，但要时刻思考优化方向。单调队列优化适用于求固定区间最值的动态规划转移。同类型题通常围绕在一定限制条件下求最值，类似算法套路是先确定状态，根据限制条件推导转移方程，再考虑优化。

### 推荐题目
1. [P1880 [NOI1995] 石子合并](https://www.luogu.com.cn/problem/P1880)
2. [P1063 能量项链](https://www.luogu.com.cn/problem/P1063)
3. [P1220 关路灯](https://www.luogu.com.cn/problem/P1220) 

---
处理用时：35.47秒