# 题目信息

# Tourist Problem

## 题目描述

Iahub is a big fan of tourists. He wants to become a tourist himself, so he planned a trip. There are $ n $ destinations on a straight road that Iahub wants to visit. Iahub starts the excursion from kilometer 0. The $ n $ destinations are described by a non-negative integers sequence $ a_{1} $ , $ a_{2} $ , ..., $ a_{n} $ . The number $ a_{k} $ represents that the $ k $ th destination is at distance $ a_{k} $ kilometers from the starting point. No two destinations are located in the same place.

Iahub wants to visit each destination only once. Note that, crossing through a destination is not considered visiting, unless Iahub explicitly wants to visit it at that point. Also, after Iahub visits his last destination, he doesn't come back to kilometer 0, as he stops his trip at the last destination.

The distance between destination located at kilometer $ x $ and next destination, located at kilometer $ y $ , is $ |x-y| $ kilometers. We call a "route" an order of visiting the destinations. Iahub can visit destinations in any order he wants, as long as he visits all $ n $ destinations and he doesn't visit a destination more than once.

Iahub starts writing out on a paper all possible routes and for each of them, he notes the total distance he would walk. He's interested in the average number of kilometers he would walk by choosing a route. As he got bored of writing out all the routes, he asks you to help him.

## 说明/提示

Consider 6 possible routes:

- \[2, 3, 5\]: total distance traveled: |2 – 0| + |3 – 2| + |5 – 3| = 5;
- \[2, 5, 3\]: |2 – 0| + |5 – 2| + |3 – 5| = 7;
- \[3, 2, 5\]: |3 – 0| + |2 – 3| + |5 – 2| = 7;
- \[3, 5, 2\]: |3 – 0| + |5 – 3| + |2 – 5| = 8;
- \[5, 2, 3\]: |5 – 0| + |2 – 5| + |3 – 2| = 9;
- \[5, 3, 2\]: |5 – 0| + |3 – 5| + |2 – 3| = 8.

The average travel distance is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF340C/46abd0367bb1ab89fd9e16a66d93ae130f1cb4b6.png) = ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF340C/3ee5b4e2d0bb159e64987b0886cc8a870c2084a7.png) = ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF340C/1d6a962c150afd1c2b26fd73c34a41806e6a93af.png).

## 样例 #1

### 输入

```
3
2 3 5
```

### 输出

```
22 3```

# AI分析结果



### 中文重写题目
#### 题目描述
Iahub 是游客的超级粉丝，他计划进行一次旅行。在一条直线上有 $n$ 个目的地，起点位于 0 公里处。第 $k$ 个目的地的位置用非负整数 $a_k$ 表示，所有目的地位置互不相同。Iahub 需要以某种顺序访问所有目的地各一次，访问结束后停留在最后一个目的地。

定义路线的总距离为：从起点到第一个目的地的距离，加上所有相邻目的地间的距离绝对值之和。求所有可能路线的平均距离。

#### 输入格式
第一行输入整数 $n$，第二行输入 $n$ 个整数 $a_1,a_2,...,a_n$。

#### 输出格式
输出平均距离的分数最简形式，用两个整数表示分子和分母。

#### 样例输入
3  
2 3 5  

#### 样例输出  
22 3  

---

### 分类
数学、排序、前缀和

---

### 题解分析与结论
**核心思路**：将总距离拆分为起始点贡献和相邻点对贡献，利用排序消除绝对值计算，通过前缀和优化求和过程。

**关键推导**：
1. **起始点贡献**：每个点作为第一个点出现的次数为 $(n-1)!$，总贡献为 $\sum a_i \times (n-1)!$
2. **相邻点对贡献**：每个点对 $(i,j)$ 在排列中相邻次数为 $2 \times (n-2)!$，总贡献为 $2 \times \sum_{i<j}(a_j - a_i) \times (n-1)!$
3. **数学化简**：最终平均值为 $\frac{\sum a_i + 2\sum_{i<j}(a_j - a_i)}{n}$

**优化技巧**：排序后使用前缀和快速计算 $\sum_{i<j}(a_j - a_i)$，复杂度从 $O(n^2)$ 降为 $O(n\log n)$

---

### 优质题解推荐

#### 题解1：DPair（5星）
**亮点**：  
- 清晰拆分起始点与中间段贡献  
- 数学推导完整，代码简洁高效  
- 前缀和优化实现优雅  

**核心代码**：
```cpp
sort(a + 1, a + n + 1);
LL pre = 0;
for (int i = 1; i <= n; i++) {
    ans1 += ((i-1)*a[i] - pre)*2; // 点对贡献
    pre += a[i];
}
ans1 += pre; // 起始点总和
LL g = gcd(ans1, n);
printf("%lld %lld", ans1/g, n/g);
```

#### 题解2：QianianXY（4星）
**亮点**：  
- 形象化解释为边贡献  
- 公式推导直观易懂  
- 代码结构清晰  

**代码思想**：  
```cpp
sort后维护前缀和：
sum += 2*(a[i]*(i-1) - 前缀和)
```

#### 题解3：MuYC（4星）
**亮点**：  
- 通过暴力找规律验证贡献次数  
- 详细推导排序后的绝对值处理  
- 代码包含完整输入输出处理  

---

### 关键技巧总结
1. **贡献拆分**：将总距离分解为独立元素的贡献，避免直接枚举排列
2. **排序优化**：利用有序性消除绝对值，将求和转化为线性计算
3. **前缀和**：快速计算 $\sum_{j<i}(a_i - a_j)$，避免双重循环
4. **分数化简**：使用最大公约数简化最终结果

---

### 同类题目推荐
1. [P2512 [HAOI2008] 糖果传递](https://www.luogu.com.cn/problem/P2512)  
   **相似点**：环形排列问题，中位数与绝对值求和优化

2. [P2709 小B的询问](https://www.luogu.com.cn/problem/P2709)  
   **相似点**：区间统计问题，平方差公式展开优化

3. [CF1008C Reorder the Array](https://codeforces.com/problemset/problem/1008/C)  
   **相似点**：排列重组优化，排序后贪心匹配

---
处理用时：62.05秒