# 题目信息

# Maximum Subsequence

## 题目描述

You are given an array $ a $ consisting of $ n $ integers, and additionally an integer $ m $ . You have to choose some sequence of indices $ b_{1},b_{2},...,b_{k} $ ( $ 1<=b_{1}&lt;b_{2}&lt;...&lt;b_{k}<=n $ ) in such a way that the value of ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF888E/3a3d2e76b5bca3303d7d35912be232a5cadb1203.png) is maximized. Chosen sequence can be empty.

Print the maximum possible value of ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF888E/3a3d2e76b5bca3303d7d35912be232a5cadb1203.png).

## 说明/提示

In the first example you can choose a sequence $ b={1,2} $ , so the sum ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF888E/08d6750b1b23699a8b513ddd01c316f10e6a789c.png) is equal to $ 7 $ (and that's $ 3 $ after taking it modulo $ 4 $ ).

In the second example you can choose a sequence $ b={3} $ .

## 样例 #1

### 输入

```
4 4
5 2 4 1
```

### 输出

```
3
```

## 样例 #2

### 输入

```
3 20
199 41 299
```

### 输出

```
19
```

# AI分析结果



### 中文题目重写
给定一个包含 $n$ 个整数的数组 $a$ 和一个整数 $m$，要求选择一个下标序列 $b_1 < b_2 < ... < b_k$（可以是空序列），使得 $\left( \sum_{i=1}^k a_{b_i} \right) \mod m$ 的值最大。输出这个最大值。

### 综合分析与结论
本题核心解法为**折半搜索+双指针合并**。由于 $n \leq 35$，将数组均分后分别进行暴力搜索，再通过排序和双指针策略合并结果。关键点在于处理模运算时对两部分和的分情况讨论，以及利用单调性优化合并过程。

---

### 精选题解分析

#### 1. 作者：newbiechd（★★★★☆）
**关键亮点**：
- 清晰的折半搜索框架，处理边界条件（n=1特判）
- 双指针合并策略，时间复杂度严格线性
- 代码中显式维护两部分结果的排序和贪心匹配

**核心代码**：
```cpp
void dfs1(int i,int sum){
    if(i==b){ p[++k]=sum,p[++k]=(sum+a[b])%m; return ;}
    dfs1(i+1,sum), dfs1(i+1,(sum+a[i])%m);
}
// 合并部分
sort(p+1,p+k+1), sort(q+1,q+t+1);
int i=0,j=t,ans=0;
while(i<=k){
    while(p[i]+q[j]>=m) --j;
    ans=max(ans,p[i]+q[j]), ++i;
}
ans=max(ans,p[k]+q[t]-m); // 处理余数溢出情况
```

#### 2. 作者：Youngore（★★★★☆）
**关键亮点**：
- 对合并策略的数学证明，解释双指针的正确性
- 将结果分为 $p+q<m$ 和 $p+q≥m$ 两种情况讨论
- 指针初始化技巧（左数组尾指针与右数组头指针）

**核心思路**：
```cpp
sort(sum1, sum2);
int l = cnt1, r = 1;
for(r从1到cnt2){
    while(sum1[l] + sum2[r] >= mod) l--;
    res = max(res, sum1[l] + sum2[r]);
}
```

#### 3. 作者：jins3599（★★★★☆）
**关键亮点**：
- 代码简洁，直接体现折半搜索与双指针的核心逻辑
- 显式处理模运算后的最大值组合
- 变量命名清晰，逻辑模块化

**核心代码**：
```cpp
sort(sum1, sum2);
int l = cnt1, r = cnt2, ans = 0;
while(i <= cnt1){
    while(sum1[i] + sum2[r] >= mod) r--;
    ans = max(ans, sum1[i] + sum2[r]);
    i++;
}
ans = max(ans, (sum1[cnt1] + sum2[cnt2]) % mod);
```

---

### 最优思路总结
1. **折半分治**：将 $O(2^n)$ 优化为 $O(2^{n/2})$ 量级
2. **双指针合并**：利用排序后的单调性，线性时间找到最优组合
3. **模运算分治**：分情况讨论和值是否超过模数，取两部分最大值组合
4. **边界处理**：特判 n=1 和空序列情况

---

### 相似题目推荐
1. [P4799 [CEOI2015 Day2] 世界冰球锦标赛](https://www.luogu.com.cn/problem/P4799) - 折半搜索模板题
2. [P3067 [USACO12OPEN]Balanced Cow Subsets G](https://www.luogu.com.cn/problem/P3067) - 折半搜索+状态合并
3. [P7535 [COCI2016-2017#4] Kas](https://www.luogu.com.cn/problem/P7535) - 值域分治优化

---
处理用时：48.05秒