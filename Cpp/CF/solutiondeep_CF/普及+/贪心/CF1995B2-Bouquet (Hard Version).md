# 题目信息

# Bouquet (Hard Version)

## 题目描述

This is the hard version of the problem. The only difference is that in this version, instead of listing the number of petals for each flower, the number of petals and the quantity of flowers in the store is set for all types of flowers.

A girl is preparing for her birthday and wants to buy the most beautiful bouquet. There are a total of $ n $ different types of flowers in the store, each of which is characterized by the number of petals and the quantity of this type of flower. A flower with $ k $ petals costs $ k $ coins. The girl has decided that the difference in the number of petals between any two flowers she will use to decorate her cake should not exceed one. At the same time, the girl wants to assemble a bouquet with the maximum possible number of petals. Unfortunately, she only has $ m $ coins, and she cannot spend more. What is the maximum total number of petals she can assemble in the bouquet?

## 说明/提示

In the first test case, some valid bouquets are $ (1, 1, 2, 2), (2, 2, 3), (1, 1), (2, 2) $ . The maximum over all valid bouquets not greater than $ 10 $ is $ 7 $ for $ (2, 2, 3) $ . In the second test case, you can assemble a valid bouquet with $ (206, 206, 207, 207, 207) $ with a sum of $ 1033 $ , which is the maximum number of petals the girl can buy. In the third test case, you can assemble a valid bouquet with $ (5, 5, 5, 4) $ with a sum of $ 19 $ . It can be seen that no valid bouquet can have $ 20 $ petals.

## 样例 #1

### 输入

```
7
3 10
1 2 3
2 2 1
3 1033
206 207 1000
3 4 1
6 20
4 2 7 5 6 1
1 2 1 3 1 7
8 100000
239 30 610 122 24 40 8 2
12 13123 112 1456 124 100 123 10982
6 13
2 4 11 1 3 5
2 2 1 2 2 1
8 10330
206 210 200 201 198 199 222 1000
9 10 11 12 13 14 15 16
2 10000000000
11 12
87312315 753297050```

### 输出

```
7
1033
19
99990
13
10000
9999999999```

# AI分析结果



### 题目中文翻译
#### Bouquet (困难版本)

##### 题目描述
这是该问题的困难版本。唯一区别在于，此版本中所有类型的花的花瓣数和数量都是预先设定好的，而非逐个列举。

一个女孩准备生日，想买最美丽的花束。花店有 $n$ 种不同的花，每种花有两个属性：花瓣数和该类型花的数量。一朵有 $k$ 个花瓣的花价值 $k$ 枚硬币。女孩要求花束中任意两朵花的花瓣数相差不超过 1。同时，她希望花束的总花瓣数尽可能多。但她只有 $m$ 枚硬币，不能超支。她能组装出的最大总花瓣数是多少？

##### 输入输出样例
（具体样例见原题）

---

### 题解综合分析

#### 最优思路总结
1. **排序预处理**：对所有花按花瓣数排序，便于处理相邻差值不超过1的情况。
2. **双值贪心策略**：对于相邻花瓣数差为1的两种花（设值为 $x$ 和 $x+1$），优先全买 $x$，剩余预算买 $x+1$，最后尝试将部分 $x$ 替换为 $x+1$ 以最大化总价值。
3. **替换优化**：在预算未耗尽时，计算可替换次数 $\min(\text{已选x数量}, \text{剩余预算}, \text{剩余x+1可用量})$，通过替换实现价值+1的提升。

#### 关键技巧
- **相邻对处理**：排序后只需考虑相邻两种花的组合情况，将二维问题降为一维。
- **替换策略数学建模**：将替换操作转化为线性计算，避免暴力枚举。

---

### 高星题解推荐

#### 1. Eraine 的题解（★★★★☆）
**核心思路**：
1. 对花瓣数排序后，转化为相邻 $x$ 和 $x+1$ 的组合问题。
2. 先尽可能买满 $x$，再买 $x+1$。
3. 计算剩余空间可进行的替换次数，通过 $\min(sum0, sum_{x+1}-sum1, m - cost)$ 确定最大提升。

**代码亮点**：
```cpp
// 计算初始可买量
int sum0 = min(c_i, m / x); 
int sum1 = min(c_j, (m - sum0*x) / (x+1));
// 计算剩余空间可替换次数
int extra = min({sum0, c_j - sum1, m - sum0*x - sum1*(x+1)});
total = sum0*x + sum1*(x+1) + extra;
```

#### 2. Leeb 的题解（★★★★☆）
**核心思路**：
1. 对每个花单独计算最大购买量。
2. 对相邻差值1的花对，先全买组合，若超预算则逐步调整。

**代码亮点**：
```cpp
// 处理相邻差1的花对
if (a[i+1].x == a[i].x + 1) {
    // 尝试全买
    if (total_cost <= m) update_max();
    else {
        // 调整策略：先买满低价花，再逐步替换
        int k1 = m / a[i].x;
        int used = k1 * a[i].x;
        int k2 = (m - used) / a[i+1].x;
        // 计算可替换次数
        int replace = min(k1, a[i+1].c - k2);
        replace = min(replace, m - used - k2*a[i+1].x);
        total = used + k2*a[i+1].x + replace;
    }
}
```

---

### 相似题目推荐
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090) - 贪心+优先队列
2. [P1803 线段覆盖](https://www.luogu.com.cn/problem/P1803) - 活动选择贪心
3. [P4995 跳跳！](https://www.luogu.com.cn/problem/P4995) - 双指针+贪心

---

### 题解心得分野
**Eraine 的调试经验**：
> "在背包问题中，$x+1$ 的约束更紧，优先填满 $x$ 再调整。这种调整策略是解决二元约束问题的通用思路。"

**总结**：当遇到类似两变量优化问题时，先固定一个变量最大化，再通过剩余空间调整另一个变量，往往能得到最优解。

---
处理用时：69.65秒