# 题目信息

# 「HGOI-1」Binary search

## 题目背景

$\text{bh1234666}$ 正在学习[二分查找](https://baike.baidu.com/item/%E4%BA%8C%E5%88%86%E6%9F%A5%E6%89%BE/10628618?fr=aladdin)。

## 题目描述

众所周知二分查找的 $\text{mid}$ 在计算时可以取 $\lfloor\dfrac{l+r}{2}\rfloor$ 或者 $\lceil\dfrac{l+r}{2}\rceil$，于是有选择困难症的 $\text{bh1234666}$ 同学在自己的二分查找代码中加入了随机化，每次随机选取其中的一个作为 $\textit{mid}$。

注意，选取不同的 mid 其他参数也会受到影响，请以代码为准。

现在 $\text{bh1234666}$ 给你了二分查找使用的序列（保证为单调递增）以及他想要寻找的数（保证在序列内），他想知道在运气最好的情况下循环需要进行几次（即代码中 $\textit{cnt}$ 的可能的最终值的最小值）。

循环：
```cpp
int find(int *num,int x,int len)
{
	int l=0,r=len-1,mid,cnt=0,w;
	while(l<r)
	{
		cnt++;
		w=rand()%2;
		mid=(l+r+w)/2;
		if(num[mid]-w<x) l=mid+!w;
		else r=mid-w;
	}
	return mid;
}
```
递归：
```
int cnt;
int get(int *num,int x,int l,int r)
{
	if(l==r) return l;
	cnt++;
	int w=rand()%2;
	int mid=(l+r+w)/2;
	if(num[mid]-w<x) return get(num,x,mid+!w,r);
	else return get(num,x,l,mid-w);
}
int find(int *num,int x,int len)
{
	cnt=0;
	return get(num,x,0,len-1);
}
```
注：以上两代码完全等价。

在此对上述代码中的 $w$ 的作用做进一步阐释。

例如对于区间 $[0,7]$，有 $8$ 个成员。虽然 $mid$ 的取值会因为 $w$ 的取值改变而改变，但是最终确定的区间一定是 $[0,3]$ 或 $[4,7]$，选手可以就上述代码自行模拟。

对于区间 $[0,6]$，有 $7$ 个成员。$\textit{mid}$ 的取值与 $w$ 的取值无关，但是 $l$ 和 $r$ 的取值会受到 $w$ 的影响，最终确定的区间可能是 $[0,2]$，$[3,6]$（$w=1$）或 $[0,3]$，$[4,6]$（$w=0$）。

## 说明/提示

### 样例 1 解释

找 $4$：

取 $[1,5]$。

取 $[1,3]$。

取 $[3,3]$（退出循环）。

### 样例 2 解释

查询 $10$ 的位置。

$$
[1,13] \stackrel{w=0}{\longrightarrow} [1,7]\stackrel{w=0}{\longrightarrow}[5,7] \stackrel{w=1}{\longrightarrow} [5,5]
$$

### 数据范围及约定
本题采用**捆绑测试**，共有 $3$ 个 $\text{subtask}$，最终分数为所有 $\text{subtask}$ 分数之和。

$$
\def\arraystretch{1.5}
\begin{array}{|c|c|c|}\hline
\textbf{Task} & \textbf{Score} & \text{特殊限制} \cr\hline
1 & 25 & n \le 20 \cr\hline
2 & 35 & n=2^k(k \in \mathbf{N}) \cr\hline
3 & 40 &  \cr\hline
\end{array}
$$

对于 $100\%$ 的数据，保证 $1 \le n \le 2^{20}$，$1 \le q \le 100$，$1 \le num_i \le 10^9$。

本题有 [extra sub](https://www.luogu.com.cn/problem/P8487)。

## 样例 #1

### 输入

```
10
1 2 4 6 7 8 10 13 15 17
3
4
10
15```

### 输出

```
3
3
3```

## 样例 #2

### 输入

```
13
1 2 4 6 10 12 19 23 45 99 101 123 134
5
1
2
10
19
123
```

### 输出

```
3
4
3
3
4```

# AI分析结果



### 综合分析与结论
题目要求找到二分查找中运气最好的情况下的最小循环次数。各题解核心思路均为暴力递归，枚举每次两种可能的 mid 计算方式，取最小次数。由于数据范围允许（n ≤ 2²⁰，q ≤ 100），O(nq) 的递归解法可行。关键点在于完全模拟题中代码的区间划分逻辑，并通过分治策略遍历所有可能路径。

---

### 高星题解推荐

#### 1. 作者：bh1234666（★★★★★）
**关键亮点**  
- 直接采用递归分治，完美还原题中二分逻辑  
- 代码简洁清晰，参数传递与题设代码完全对应  
- 通过 `min(ret, ...)` 天然维护最小值，无冗余计算  

**核心代码实现**  
```cpp
int find(int k, int f, int l) {
    if (f == l) return 0;
    int mid = (f + l) >> 1, ret = 32;
    // 处理 w=0 的情况
    if (mid < k) ret = find(k, mid + 1, l);
    else ret = find(k, f, mid);
    // 处理 w=1 的情况
    mid = (f + l + 1) >> 1;
    if (mid <= k) ret = min(ret, find(k, mid, l));
    else ret = min(ret, find(k, f, mid - 1));
    return ret + 1;
}
```

#### 2. 作者：见贤思齐_Seakies（★★★★☆）
**关键亮点**  
- 全局变量 `ans` 维护最小值，逻辑直观易懂  
- 完全复现题中递归代码结构，便于对照验证  
- 添加详细注释说明 `w` 的两种选择逻辑  

**核心代码片段**  
```cpp
void get(int *num, int x, int l, int r, int cnt) {
    if (l == r) {
        ans = min(cnt, ans);
        return;
    }
    w = 0, mid = (l + r + w) / 2; // w=0 分支
    if (...) get(...);
    else get(...);
    w = 1, mid = (l + r + w) / 2; // w=1 分支
    if (...) get(...);
    else get(...);
}
```

#### 3. 作者：Joker_1212（★★★★☆）
**关键亮点**  
- 显式处理区间奇偶性，优化部分分支  
- 通过 `(r - l + 1) & 1` 减少无效递归  
- 代码结构清晰，变量命名规范  

**核心代码逻辑**  
```cpp
void dfs(int *a, int l, int r, int x, int cnt) {
    if (l == r) { ans = min(ans, cnt); return; }
    int w = 0, mid = (l + r + w) >> 1;
    // 处理 w=0 的情况
    if (...) dfs(...);
    else dfs(...);
    if ((r - l + 1) & 1) { // 仅奇数长度需要处理 w=1
        w = 1, mid = (l + r + w) >> 1;
        if (...) dfs(...);
        else dfs(...);
    }
}
```

---

### 最优思路总结
**关键技巧**  
1. **递归分治**：每次递归处理两种可能的 mid 选择（w=0 和 w=1），取较小值。  
2. **剪枝优化**：当区间长度为偶数时，部分解法避免重复计算（如 Joker_1212 的奇偶判断）。  
3. **参数传递**：严格模拟题中代码的 `mid` 计算和区间更新方式，确保逻辑一致。

**同类型拓展**  
- 类似分治策略可用于树形 DP、回溯问题等需要遍历多路径的场景。  
- 对二分变种问题（如非固定 mid 选择）可借鉴此递归枚举思想。

---

### 推荐练习题
1. **P2249 【深基13.例1】查找**  
   - 基础二分查找，练习标准实现。
2. **P1182 数列分段 Section II**  
   - 二分答案经典题，结合贪心验证。
3. **P8444 不等价交换法则**  
   - 二分与贪心结合，锻炼分治思维。

---
处理用时：68.39秒