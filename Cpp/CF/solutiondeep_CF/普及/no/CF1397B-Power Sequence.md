# 题目信息

# Power Sequence

## 题目描述

Let's call a list of positive integers $ a_0, a_1, ...,       a_{n-1} $ a power sequence if there is a positive integer $ c $ , so that for every $ 0 \le       i \le n-1 $ then $ a_i = c^i $ .

Given a list of $ n $ positive integers $ a_0, a_1, ...,       a_{n-1} $ , you are allowed to:

- Reorder the list (i.e. pick a permutation $ p $ of $ \{0,1,...,n - 1\} $ and change $ a_i $ to $ a_{p_i} $ ), then
- Do the following operation any number of times: pick an index $ i $ and change $ a_i $ to $ a_i - 1 $ or $ a_i + 1 $ (i.e. increment or decrement $ a_i $ by $ 1 $ ) with a cost of $ 1 $ .

Find the minimum cost to transform $ a_0, a_1, ..., a_{n-1} $ into a power sequence.

## 说明/提示

In the first example, we first reorder $ \{1, 3, 2\} $ into $ \{1, 2, 3\} $ , then increment $ a_2 $ to $ 4 $ with cost $ 1 $ to get a power sequence $ \{1, 2, 4\} $ .

## 样例 #1

### 输入

```
3
1 3 2```

### 输出

```
1```

## 样例 #2

### 输入

```
3
1000000000 1000000000 1000000000```

### 输出

```
1999982505```

# AI分析结果

【题目内容】
# 幂序列

## 题目描述

我们称一个正整数序列 $a_0, a_1, ..., a_{n-1}$ 为幂序列，如果存在一个正整数 $c$，使得对于每个 $0 \le i \le n-1$，都有 $a_i = c^i$。

给定一个包含 $n$ 个正整数的序列 $a_0, a_1, ..., a_{n-1}$，你可以进行以下操作：

- 重新排列序列（即选择一个排列 $p$ 并将 $a_i$ 更改为 $a_{p_i}$），然后
- 进行任意次数的操作：选择一个下标 $i$ 并将 $a_i$ 更改为 $a_i - 1$ 或 $a_i + 1$（即递增或递减 $a_i$ 1），每次操作的成本为 $1$。

求将序列 $a_0, a_1, ..., a_{n-1}$ 转换为幂序列的最小成本。

## 说明/提示

在第一个样例中，我们首先将序列 $\{1, 3, 2\}$ 重新排列为 $\{1, 2, 3\}$，然后将 $a_2$ 递增到 $4$，成本为 $1$，得到幂序列 $\{1, 2, 4\}$。

## 样例 #1

### 输入

```
3
1 3 2```

### 输出

```
1```

## 样例 #2

### 输入

```
3
1000000000 1000000000 1000000000```

### 输出

```
1999982505```

【算法分类】数学

【题解分析与结论】
本题的核心是通过枚举 $c$ 并计算与序列 $a$ 的差值，找到最小成本。由于 $c$ 的取值范围有限，且幂序列的增长速度极快，因此可以通过暴力枚举 $c$ 来解决。所有题解都提到了先对序列进行排序，然后枚举 $c$ 并计算差值的最小值。

【评分较高的题解】
1. **作者：⚡小林子⚡ (5星)**
   - **关键亮点**：通过 `pow(LONG_LONG_MAX,1.0/n)` 确定 $c$ 的最大值，避免了 $c$ 的无限枚举。代码简洁且高效。
   - **代码核心**：
     ```cpp
     int t=pow(LONG_LONG_MAX,1.0/n);
     for(int i=1;i<=t;i++){
         int sum=0,tmp=1;
         for(int j=1;j<=n;j++)
             sum+=abs(tmp-a[j]),tmp*=i;
         ans=min(ans,sum);
     }
     ```

2. **作者：vectorwyx (4星)**
   - **关键亮点**：通过 `pow(INF,1.0/n)` 确定 $c$ 的最大值，并优化了枚举范围，避免了不必要的计算。
   - **代码核心**：
     ```cpp
     int R=floor(pow(INF,1.0/n));
     fo(i,1,R){ 
         sum=0;
         power[0]=1;
         fo(j,1,n) power[j]=power[j-1]*i,sum+=abs(a[j]-power[j-1]);
         ans=min(ans,sum);
     }
     ```

3. **作者：jun头吉吉 (4星)**
   - **关键亮点**：通过 `log10(i)*(n-1)>=15` 判断 $c$ 的枚举范围，并在差值大于当前答案时提前退出，进一步优化了枚举过程。
   - **代码核心**：
     ```cpp
     for(int i=1;;i++){
         if(log10(i)*(n-1)>=15)break;
         long long tmp=0,now=1;
         for(int j=1;j<=n;j++)
             tmp+=abs(a[j]-now),now*=i;
         ans=min(ans,tmp);
         if(tmp>ans)break;
     }
     ```

【最优关键思路】
1. **排序**：先对序列进行排序，确保差值的计算是最优的。
2. **枚举范围**：通过数学方法确定 $c$ 的最大枚举范围，避免无限枚举。
3. **提前退出**：在差值大于当前答案时提前退出，减少不必要的计算。

【可拓展之处】
类似的问题可以通过枚举和数学优化来解决，尤其是在涉及幂运算或指数增长的问题中，枚举范围的控制是关键。

【推荐题目】
1. [P1020 导弹拦截](https://www.luogu.com.cn/problem/P1020)
2. [P1045 麦森数](https://www.luogu.com.cn/problem/P1045)
3. [P1062 数列](https://www.luogu.com.cn/problem/P1062)

---
处理用时：29.31秒