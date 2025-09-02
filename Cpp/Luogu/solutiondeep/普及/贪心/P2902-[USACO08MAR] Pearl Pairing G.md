# 题目信息

# [USACO08MAR] Pearl Pairing G

## 题目描述

At Bessie's recent birthday party, she received $N(2 \le N \le 10^5,N\equiv0\pmod{2})$ pearls, each painted one of C different colors ($1\le C \le N$).

Upon observing that the number of pearls $N$ is always even, her creative juices flowed and she decided to pair the pearls so that each pair of pearls has two different colors.

Knowing that such a set of pairings is always possible for the supplied testcases, help Bessie perform such a pairing. If there are multiple ways of creating a pairing, any solution suffices.

在 Bessie 最近的生日聚会上，她收到 $N(2\le N \le 10^5,N\equiv0\pmod{2})$ 颗珍珠。一共有 $C$ 种颜色的珍珠（$1\le C \le N$），第 $i$ 种颜色的珍珠有 $C_i$ 颗。


观察到珍珠的数量 $N$ 总是偶数，她的创意来了，决定配对珍珠，使每对珍珠有两种不同的颜色。数据保证存在答案。请帮助 Bessie 执行这样的配对，如果有多种配对的方法，输出任意一种即可。

## 说明/提示

There are $8$ pearls and $3$ different colors. Two pearls have color $\mathrm{I}$; two have color $\mathrm{II}$; four have color $\mathrm{III}$.


Bessie pairs each pearl of color $\mathrm{III}$ with one of color $\mathrm{I}$ and $\mathrm{Ii}$.

说明：有 $8$ 颗珍珠和 $3$ 种不同的颜色。两颗珍珠颜色为 $1$，两颗珍珠颜色为 $2$，四颗珍珠颜色为 $3$。

Bessie 将每颗颜色为 $3$ 的珍珠与颜色为 $1$ 和 $2$ 的珍珠配对。

感谢@[线段木](https://www.luogu.com.cn/user/33930) 提供翻译，@[PineappleSummer](https://www.luogu.com.cn/user/880187) 修正翻译以及提供 $\LaTeX$。

## 样例 #1

### 输入

```
8 3 
2 
2 
4 
```

### 输出

```
1 3 
1 3 
2 3 
3 2 
```

# AI分析结果

### 综合分析与结论

该题的核心要求是将珍珠两两配对，且每对珍珠的颜色不同。题解中主要采用了以下几种思路：

1. **直接配对法**：将珍珠按颜色展开后，前一半与后一半直接配对。这种方法简单直接，时间复杂度为O(N)，适用于大多数情况。
2. **贪心策略**：每次选择数量最多的两种颜色进行配对，确保不会出现同色配对的情况。这种方法需要排序，时间复杂度为O(N log C)。
3. **优先队列**：使用优先队列动态维护颜色数量，每次取出最多的两种颜色进行配对。时间复杂度为O(N log C)。

最优的思路是**直接配对法**，因为它简单高效，且无需复杂的排序或数据结构。贪心策略和优先队列虽然也能解决问题，但复杂度较高，且代码实现相对复杂。

### 所选高分题解

#### 1. 作者：Waddles (5星)
**关键亮点**：思路清晰，代码简洁，直接展开珍珠并按顺序配对，时间复杂度O(N)。
**代码核心**：
```cpp
for(int i=1;i<=n/2;i++)printf("%d %d\n",a[i],a[i+n/2]);
```
**实现思想**：将珍珠按颜色展开后，前一半与后一半直接配对，确保每对颜色不同。

#### 2. 作者：Exber (4星)
**关键亮点**：代码简洁，直接展开珍珠并按顺序配对，时间复杂度O(N)。
**代码核心**：
```cpp
for(int i=1;i<=n/2;i++)printf("%d %d\n",num[i],num[i+n/2]);
```
**实现思想**：与Waddles的思路一致，代码实现简洁明了。

#### 3. 作者：Jason12 (4星)
**关键亮点**：代码简洁，直接展开珍珠并按顺序配对，时间复杂度O(N)。
**代码核心**：
```cpp
for(int i=1;i<=n/2;i++)printf("%d %d\n",s[i],s[i+n/2]);
```
**实现思想**：与上述两位作者思路一致，代码实现简洁。

### 最优关键思路

**直接配对法**：将珍珠按颜色展开后，前一半与后一半直接配对。这种方法简单高效，时间复杂度为O(N)，且无需复杂的排序或数据结构。

### 可拓展之处

1. **类似问题**：可以拓展到其他需要两两配对且满足某种条件的问题，如任务分配、资源调度等。
2. **优化思路**：如果数据量更大，可以考虑使用更高效的数据结构或并行计算来进一步优化。

### 推荐题目

1. **P1908 逆序对**：考察排序和配对思想。
2. **P1090 合并果子**：考察贪心策略和优先队列的使用。
3. **P1168 中位数**：考察排序和配对思想。

### 个人心得摘录

- **Waddles**：题解区居然没有这种解法，直接配对法简单高效。
- **Exber**：这道题十分的简单，建议评红，直接配对法即可。
- **Jason12**：贪心题，将颜色最多的牛先配对，直接配对法简单高效。

这些心得都强调了直接配对法的简单高效，适合大多数情况。

---
处理用时：28.80秒