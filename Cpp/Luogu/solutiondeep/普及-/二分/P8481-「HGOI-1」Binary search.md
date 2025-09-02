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
本题要求计算在最优随机选择下二分查找的最小次数。由于每次选择会影响后续路径，贪心策略不可行。各题解普遍采用DFS暴力枚举所有可能的分支，取最小值。关键是将问题转化为目标下标的查找，避免重复比较数组元素，从而优化时间复杂度。

### 高分题解推荐

#### 1. 作者：bh1234666（5星）
**关键亮点**：
- 将问题转化为目标下标的查找，预处理找到目标位置，避免比较数组元素。
- 递归时分别尝试两种mid计算方式，取最小次数。
- 时间复杂度O(nq)适用于题目数据范围，代码清晰高效。

**核心代码**：
```cpp
int find(int k, int f, int l) {
    if (f == l) return 0;
    int mid = (f + l) >> 1, ret = 32;
    if (mid < k) ret = find(k, mid + 1, l);
    else ret = find(k, f, mid);
    mid = (f + l + 1) >> 1;
    if (mid <= k) ret = min(ret, find(k, mid, l));
    else ret = min(ret, find(k, f, mid - 1));
    return ret + 1;
}
```
**实现思路**：递归处理两种mid情况（`mid=(l+r)/2`和`mid=(l+r+1)/2`），根据目标位置k选择分支，返回最小次数。

#### 2. 作者：JackMerryYoung（4星）
**关键亮点**：
- 直接模拟题目代码逻辑，枚举两种w值进行DFS。
- 思路直观，代码结构清晰，易于理解。

**核心代码（伪代码）**：
```python
def binary_search(num, x, l, r, step):
    if l == r:
        ans = min(ans, step)
        return
    mid = (l + r) // 2
    # 处理w=0的分支
    if条件判断并递归
    mid = (l + r + 1) // 2
    # 处理w=1的分支
    if条件判断并递归
```
**实现思路**：每次递归分两种情况处理mid，根据条件判断进入不同区间，统计最小步数。

### 最优思路总结
**关键技巧**：预处理目标下标，将问题转化为区间缩小问题。通过递归枚举所有可能的二分路径，避免重复计算数组元素，直接基于下标位置进行判断，显著提高效率。

### 相似题目推荐
1. **P2249 【深基13.例1】查找**  
   （考察二分查找基础，适合练习标准实现）
2. **P1182 数列分段 Section II**  
   （二分答案经典问题，锻炼逆向思维）
3. **P8444 环覆盖问题**  
   （结合贪心与二分，难度适中）

---
处理用时：96.72秒