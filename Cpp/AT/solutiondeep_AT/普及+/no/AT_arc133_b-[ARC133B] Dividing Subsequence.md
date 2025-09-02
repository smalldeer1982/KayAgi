# 题目信息

# [ARC133B] Dividing Subsequence

## 题目描述

**【题目大意】**

给定两个长度为 $n(n\le 2\times 10^5)$ 的 $1\sim n$ 的排列 $\text{P}$ 和 $\text{Q}$。

现在需要在 $\text{P}$ 和 $\text{Q}$ 中分别取出长度为 $k$ 两个子序列 $\text{A}$ 和 $\text{B}$，满足 $\forall i\in [1,k],a_i\mid b_i$。

最大化 $k$，求 $k$。

## 样例 #1

### 输入

```
4

3 1 4 2

4 2 1 3```

### 输出

```
2```

## 样例 #2

### 输入

```
5

1 2 3 4 5

5 4 3 2 1```

### 输出

```
3```

## 样例 #3

### 输入

```
10

4 3 1 10 9 2 8 6 5 7

9 6 5 4 2 3 8 10 1 7```

### 输出

```
6```

# AI分析结果

### 题目内容重写

**【题目大意】**

给定两个长度为 $n(n\le 2\times 10^5)$ 的 $1\sim n$ 的排列 $\text{P}$ 和 $\text{Q}$。

现在需要在 $\text{P}$ 和 $\text{Q}$ 中分别取出长度为 $k$ 的两个子序列 $\text{A}$ 和 $\text{B}$，满足 $\forall i\in [1,k],a_i\mid b_i$。

最大化 $k$，求 $k$。

### 算法分类
动态规划、树状数组

### 题解分析与结论

#### 题解1：yukimianyan
**星级：5星**
**关键亮点：**
- 通过枚举所有满足 $a_i \mid b_j$ 的 $(i,j)$ 对，利用调和级数性质，复杂度为 $O(n\log n)$。
- 使用排序和最长上升子序列（LIS）来避免重复选择相同的 $j$。
- 代码简洁，逻辑清晰，优化得当。

**核心代码：**
```cpp
sort(b+1,b+cnt+1,[](pair<int,int> a,pair<int,int> b){
    return a.second!=b.second?a.second<b.second:a.first>b.first;
});
int top=0;
for(int i=1;i<=cnt;i++){
    if(!top||c[top]<b[i].first) c[++top]=b[i].first;
    else *lower_bound(c+1,c+top+1,b[i].first)=b[i].first;
}
```
**核心思想：**
- 对 $(i,j)$ 按 $j$ 升序、$i$ 降序排序，然后对 $i$ 做 LIS，确保 $j$ 严格递增且不重复。

#### 题解2：mountain_climber
**星级：4星**
**关键亮点：**
- 预处理所有可能的 $(i,j)$ 对，复杂度为 $O(n\log n)$。
- 使用树状数组优化 LIS 的求解，确保复杂度为 $O(n\log^2 n)$。
- 代码结构清晰，逻辑严谨。

**核心代码：**
```cpp
sort(vec.begin(), vec.end(), cmp);
int len = vec.size();
for (int i = 0; i < len; i ++ ) {
    dp[i] = query(vec[i].second - 1) + 1;
    add(vec[i].second, dp[i]);
}
```
**核心思想：**
- 对 $(i,j)$ 按 $i$ 升序、$j$ 降序排序，然后对 $j$ 做 LIS，确保 $i$ 严格递增且不重复。

#### 题解3：toolong114514
**星级：4星**
**关键亮点：**
- 通过枚举 $a_i$ 的倍数，预处理所有可能的 $(i,j)$ 对，复杂度为 $O(n\log n)$。
- 使用树状数组优化 LIS 的求解，确保复杂度为 $O(n\log^2 n)$。
- 代码简洁，逻辑清晰。

**核心代码：**
```cpp
sort(arr+1,arr+cnt+1,cmp);
for(int i=1;i<=cnt;i++){
    f[i]=ask(arr[i].val2-1)+1;
    upd(arr[i].val2,f[i]);
    ans=max(ans,f[i]);
}
```
**核心思想：**
- 对 $(i,j)$ 按 $i$ 升序、$j$ 降序排序，然后对 $j$ 做 LIS，确保 $i$ 严格递增且不重复。

### 最优关键思路与技巧
1. **调和级数枚举**：利用 $a_i \mid b_j$ 的性质，通过调和级数枚举所有可能的 $(i,j)$ 对，复杂度为 $O(n\log n)$。
2. **排序与 LIS**：对 $(i,j)$ 按 $j$ 升序、$i$ 降序排序，然后对 $i$ 做 LIS，确保 $j$ 严格递增且不重复。
3. **树状数组优化**：使用树状数组优化 LIS 的求解，确保复杂度为 $O(n\log^2 n)$。

### 可拓展之处
- 类似的问题可以扩展到其他二元关系，如 $a_i \leq b_j$ 或 $a_i \equiv b_j \pmod{m}$ 等。
- 可以结合其他数据结构如线段树、平衡树等进一步优化。

### 推荐题目
1. [P1439 最长公共子序列](https://www.luogu.com.cn/problem/P1439)
2. [P3374 树状数组 1](https://www.luogu.com.cn/problem/P3374)
3. [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)

---
处理用时：33.26秒