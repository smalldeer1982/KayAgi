# 题目信息

# [ICPC 2017 WF] Posterize

## 题目描述



![](https://onlinejudgeimages.s3-ap-northeast-1.amazonaws.com/problem/14638/1.png)

Pixels in a digital picture can be represented with three integers in the range $0$ to $255$ that indicate the intensity of the red, green, and blue colors. To compress an image or to create an artistic effect, many photo-editing tools include a `posterize` operation which works as follows. Each color channel is examined separately; this problem focuses only on the red channel. Rather than allow all integers from $0$ to $255$ for the red channel, a posterized image allows at most $k$ integers from this range. Each pixel's original red intensity is replaced with the nearest of the allowed integers. The photo-editing tool selects a set of $k$ integers that minimizes the sum of the squared errors introduced across all pixels in the original image. If there are $n$ pixels that have original red values $r_{1},$ . . . , $r_{n},$ and $k$ allowed integers $v_{1},$ . . . , $v_{k},$ the sum of squared errors is defined as

$$\sum\limits_{i=1}^n \min\limits_{1 \le j \le k}(r_i-v_j)^2$$

Your task is to compute the minimum achievable sum of squared errors, given parameter $k$ and a description of the red intensities of an image's pixels.



## 说明/提示

Time limit: 2 s, Memory limit: 512 MB. 



## 样例 #1

### 输入

```
2 1
50 20000
150 10000
```

### 输出

```
66670000
```

## 样例 #2

### 输入

```
2 2
50 20000
150 10000
```

### 输出

```
0
```

## 样例 #3

### 输入

```
4 2
0 30000
25 30000
50 30000
255 30000
```

### 输出

```
37500000
```

# AI分析结果



**算法分类**: 动态规划

---

### 综合分析与结论
题目要求将颜色值划分为最多 $k$ 个区间，每个区间用一个代表值，最小化总平方误差。核心难点在于如何高效计算区间划分的代价，并通过动态规划找到最优划分方式。两篇题解均采用动态规划，但实现细节和优化程度有显著差异。

---

### 高星题解推荐

#### 题解作者：LJY_ljy（⭐️⭐️⭐️⭐️⭐️）
**关键亮点**:
1. **前缀和优化**：预处理前缀和数组 `sum`，将误差计算转化为 $O(1)$ 的数学表达式。
2. **离散化处理**：将输入颜色值合并统计，避免重复计算。
3. **状态转移优化**：通过枚举前驱分割点 $j$，利用预处理的前缀和快速计算转移代价。
**核心代码**:
```cpp
// 预处理前缀和
sum[0][0] = DD[0][0]; 
sum[0][1] = DD[0][1];
for (long long i = 1; i <= 255; i++) {
    for (long long j = 0; j < 2; j++)
        sum[i][j] = sum[i - 1][j] + DD[i][j];
}

// DP转移
for (long long cnt = 2; cnt <= k; cnt++) {
    for (long long i = 0; i <= 255; i++) {
        for (long long j = 0; j < i; j++) {
            long long A = (2 * j - 2 * i) * (sum[255][0] - sum[(i + j)/2][0]) 
                        + (i * i - j * j) * (sum[255][1] - sum[(i + j)/2][1]);
            dp[i][cnt] = min(dp[i][cnt], dp[j][cnt - 1] + A); 
        }
    }
}
```

---

### 最优思路总结
1. **离散化统计**：合并相同颜色值的像素，减少计算量。
2. **前缀和数组**：预处理每个颜色值之后的像素总和和数量，将误差计算转化为线性代数表达式。
3. **动态规划状态设计**：定义 $dp[i][cnt]$ 表示前 $i$ 个颜色值使用 $cnt$ 个代表值的最小误差，通过枚举前驱状态实现高效转移。

---

### 扩展与相似题目
1. **P1776 宝物筛选**（动态规划 + 单调队列优化）
2. **P1063 能量项链**（区间划分动态规划）
3. **P3146 [USACO16OPEN]248**（区间合并动态规划）

---
处理用时：53.74秒