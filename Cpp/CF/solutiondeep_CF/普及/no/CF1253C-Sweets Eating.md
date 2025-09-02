# 题目信息

# Sweets Eating

## 题目描述

Tsumugi brought $ n $ delicious sweets to the Light Music Club. They are numbered from $ 1 $ to $ n $ , where the $ i $ -th sweet has a sugar concentration described by an integer $ a_i $ .

Yui loves sweets, but she can eat at most $ m $ sweets each day for health reasons.

Days are $ 1 $ -indexed (numbered $ 1, 2, 3, \ldots $ ). Eating the sweet $ i $ at the $ d $ -th day will cause a sugar penalty of $ (d \cdot a_i) $ , as sweets become more sugary with time. A sweet can be eaten at most once.

The total sugar penalty will be the sum of the individual penalties of each sweet eaten.

Suppose that Yui chooses exactly $ k $ sweets, and eats them in any order she wants. What is the minimum total sugar penalty she can get?

Since Yui is an undecided girl, she wants you to answer this question for every value of $ k $ between $ 1 $ and $ n $ .

## 说明/提示

Let's analyze the answer for $ k = 5 $ in the first example. Here is one of the possible ways to eat $ 5 $ sweets that minimize total sugar penalty:

- Day $ 1 $ : sweets $ 1 $ and $ 4 $
- Day $ 2 $ : sweets $ 5 $ and $ 3 $
- Day $ 3 $ : sweet $ 6 $

Total penalty is $ 1 \cdot a_1 + 1 \cdot a_4 + 2 \cdot a_5 + 2 \cdot a_3 + 3 \cdot a_6 = 6 + 4 + 8 + 6 + 6 = 30 $ . We can prove that it's the minimum total sugar penalty Yui can achieve if she eats $ 5 $ sweets, hence $ x_5 = 30 $ .

## 样例 #1

### 输入

```
9 2
6 19 3 4 4 2 6 7 8
```

### 输出

```
2 5 11 18 30 43 62 83 121
```

## 样例 #2

### 输入

```
1 1
7
```

### 输出

```
7
```

# AI分析结果

### 题目内容（中文重写）

Tsumugi 带了 $n$ 个美味的糖果到轻音乐部。这些糖果编号从 $1$ 到 $n$，其中第 $i$ 个糖果的糖分浓度用一个整数 $a_i$ 描述。

Yui 非常喜欢糖果，但出于健康考虑，她每天最多只能吃 $m$ 个糖果。

天数从 $1$ 开始编号（即第 $1$ 天、第 $2$ 天、第 $3$ 天，……）。在第 $d$ 天吃第 $i$ 个糖果会产生 $(d \cdot a_i)$ 的糖分惩罚，因为糖果会随着时间的推移变得更甜。每个糖果最多只能吃一次。

总糖分惩罚是所有被吃糖果的糖分惩罚之和。

假设 Yui 选择了恰好 $k$ 个糖果，并且可以按任意顺序吃它们。她能得到的最小总糖分惩罚是多少？

由于 Yui 是个犹豫不决的女孩，她希望你能回答从 $1$ 到 $n$ 的每一个 $k$ 值对应的这个问题。

### 算法分类
贪心、前缀和

### 题解分析与结论

1. **TheOnlyMan 的题解（5星）**
   - **关键亮点**：通过排序和前缀和优化，利用递推公式 $f[i] = f[i-m] + sum[i]$ 来高效计算每个 $k$ 的最小糖分惩罚。思路清晰，代码简洁。
   - **代码核心**：
     ```cpp
     for(int i=1;i<=n;i++){
         if(i-m>=0)ans[i]=ans[i-m]+sum[i];
         else ans[i]=sum[i];
     }
     ```
   - **个人心得**：强调了贪心策略的重要性，即尽早吃糖分高的糖果，以减少总糖分惩罚。

2. **许多的题解（4星）**
   - **关键亮点**：同样使用排序和前缀和，但通过维护一个特别的前缀和 $sum[i]=sum[i-m]+a[i]$ 来计算答案。思路与 TheOnlyMan 类似，但代码稍显冗长。
   - **代码核心**：
     ```cpp
     for(LL i=m;i<=n;i++)sum[i]=a[i]+sum[i-m];
     ```
   - **个人心得**：强调了贪心策略的正确性，并提醒了不开 `long long` 可能导致的问题。

3. **Register_int 的题解（4星）**
   - **关键亮点**：通过分组统计前缀和，利用余数分组计算每个 $k$ 的糖分惩罚。思路新颖，但实现稍复杂。
   - **代码核心**：
     ```cpp
     for (int i = 0; i < m; i++) {
         sum[i].push_back(0);
         for (int j = i ? i : m; j <= n; j += m) sum[i].push_back(sum[i].back() + a[j]);
     }
     ```
   - **个人心得**：强调了分组统计的优化方法，并提供了详细的实现思路。

### 最优关键思路或技巧
- **排序**：将糖果按糖分从小到大排序，确保每次选择糖分最小的糖果。
- **前缀和**：利用前缀和快速计算部分和，减少重复计算。
- **递推公式**：通过递推公式 $f[i] = f[i-m] + sum[i]$ 高效计算每个 $k$ 的最小糖分惩罚。

### 可拓展之处
- 类似的问题可以扩展到其他需要分组计算或递推优化的场景，如任务调度、资源分配等。

### 推荐题目
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
2. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)
3. [P1048 采药](https://www.luogu.com.cn/problem/P1048)

### 个人心得总结
- **调试经历**：在实现过程中，需要注意边界条件的处理，如 $i < m$ 时的特殊情况。
- **踩坑教训**：不开 `long long` 可能导致溢出问题，需特别注意。
- **顿悟感想**：贪心策略的正确性往往需要通过严格的数学证明来验证，不能仅凭直觉。

---
处理用时：33.32秒