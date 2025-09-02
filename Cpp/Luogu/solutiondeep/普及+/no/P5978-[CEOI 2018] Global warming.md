# 题目信息

# [CEOI 2018] Global warming

## 题目描述

给定 $n$，你可以将任意 $a_l$ 至 $a_r$($1\le l\le r\le n$)每一个元素加上一个 $d$($-x\le d\le x$), 求 $a$ 数组的最大严格上升子序列长度。

## 说明/提示

对于 $100\%$ 的数据，$1\le n\le 2\times 10^5$。

## 样例 #1

### 输入

```
8 10
7 3 5 12 2 7 3 4```

### 输出

```
5```

# AI分析结果



### 算法分类
动态规划

### 综合分析与结论
题目要求通过一次区间加减操作最大化最长严格上升子序列（LIS）。各题解核心思路为：**贪心选择前缀减或后缀加，预处理前后缀 LIS 后合并求最大值**。关键点包括：
1. **贪心性质**：操作整个前缀/后缀最优，只需枚举分界点。
2. **预处理技巧**：正序求前缀 LIS，倒序求修改后的后缀 LIS。
3. **二分优化**：利用 `lower_bound` 维护单调性，复杂度 O(n log n)。

### 精选题解

#### 1. lnwhl（⭐⭐⭐⭐⭐）
- **核心亮点**：代码简洁高效，两次二分处理前后缀 LIS，通过 `-a[i]+x` 巧妙处理修改后的条件。
- **代码核心**：
  ```cpp
  memset(lis,0x7f,sizeof(lis));
  for(int i=n;i>=1;--i) {
    int j=lower_bound(lis,lis+n,-a[i]+x)-lis;
    int jj=lower_bound(lis,lis+n,-a[i])-lis;
    lis[jj]=-a[i]; ans=max(ans,L[i]+j);
  }
  ```

#### 2. DengDuck（⭐⭐⭐⭐）
- **核心亮点**：树状数组维护动态规划状态，离散化处理数值，支持两种状态（是否修改）。
- **代码核心**：
  ```cpp
  struct BIT { /* 维护最大值 */ };
  BIT T0,T1; // T0:未修改，T1:已修改
  for(int i=1;i<=n;i++) {
    LL K0=T0.Qry(t0-1)+1, K1=max(T0.Qry(t1-1),T1.Qry(t0-1))+1;
    T0.Upd(t0,K0); T1.Upd(t0,K1);
  }
  ```

#### 3. ETHANK（⭐⭐⭐⭐）
- **核心亮点**：逆向思维处理后缀 LIS，通过离散化统一数值范围。
- **代码核心**：
  ```cpp
  per(i,n,1) {
    tomax(ans,f[i]+(lower_bound(...,-a[i]+X)-h-1));
    h[lower_bound(...,-a[i])-h] = -a[i];
  }
  ```

### 最优关键思路
**分治合并法**：将问题拆分为前后缀处理，利用二分维护单调序列。预处理前缀 LIS 数组 `L[i]`，倒序维护修改后的后缀序列，合并时用 `L[i] + R[i] -1` 避免重复计算当前元素。

### 扩展与类似题目
- **LIS 变形**：可尝试 [P1439 最长公共子序列](https://www.luogu.com.cn/problem/P1439)、[P4303 基因匹配](https://www.luogu.com.cn/problem/P4303)。
- **贪心+DP优化**：[P4597 序列sequence](https://www.luogu.com.cn/problem/P4597)。

### 个人心得摘录
- **Hoks**：观察到修改区间应尽量覆盖更大范围，避免中间断裂。
- **DengDuck**：通过树状数组维护动态状态，离散化是关键步骤。
- **reductt**：强调预处理的重要性，避免重复计算。

### 推荐题目
1. [P1439 最长公共子序列](https://www.luogu.com.cn/problem/P1439)
2. [P4303 基因匹配](https://www.luogu.com.cn/problem/P4303)
3. [P4597 序列sequence](https://www.luogu.com.cn/problem/P4597)

---
处理用时：87.79秒