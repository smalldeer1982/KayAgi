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
本题核心在于处理二分查找中随机选择 mid 的特性，无法通过贪心获得最优解。各题解均采用递归或DFS暴力枚举所有可能的路径，取最小操作次数。由于数据规模中递归深度仅为 O(logn)，且 q 较小，该方案可行。

---

### 精选题解与评分

#### 1. 作者：bh1234666（⭐⭐⭐⭐⭐）
**关键亮点**  
- 精准指出贪心算法的错误本质（前序决策影响后序权值）  
- 递归实现简洁，利用分治思想处理两种 mid 情况  
- 代码中通过 min 函数直接取最优值，逻辑清晰  

**核心代码**  
```cpp
int find(int k, int f, int l) {
    if (f == l) return 0;
    int mid = (f + l) >> 1, ret = 32;
    if (mid < k) ret = find(k, mid + 1, l);
    else ret = find(k, f, mid);
    mid = (f + l + 1) >> 1; // 另一种mid计算方式
    if (mid <= k) ret = min(ret, find(k, mid, l));
    else ret = min(ret, find(k, f, mid - 1));
    return ret + 1;
}
```

#### 2. 作者：见贤思齐_Seakies（⭐⭐⭐⭐）
**关键亮点**  
- 详细注释说明递归终止条件和分支处理  
- 代码完全模拟题目给定逻辑，便于理解  
- 对随机选择 w 的两种情况进行显式处理  

**核心代码**  
```cpp
void get(int *num, int x, int l, int r, int cnt) {
    if (l == r) { ans = min(cnt, ans); return; }
    // 处理w=0和w=1两种情况
    w = 0, mid = (l + r + w) / 2;
    if (num[mid] - w < x) get(num, x, mid + !w, r, cnt + 1);
    else get(num, x, l, mid - w, cnt + 1);
    w = 1, mid = (l + r + w) / 2;
    if (num[mid] - w < x) get(num, x, mid + !w, r, cnt + 1);
    else get(num, x, l, mid - w, cnt + 1);
}
```

#### 3. 作者：Joker_1212（⭐⭐⭐⭐）
**关键亮点**  
- 显式处理区间奇偶性，减少不必要的递归  
- 代码结构简洁，包含详细边界条件判断  
- 对题目给出的代码逻辑进行精准转译  

**核心代码**  
```cpp
void dfs(int *a, int l, int r, int x, int cnt) {
    if (l == r) { ans = min(ans, cnt); return; }
    int w = 0, mid = (l + r + w) >> 1;
    if (a[mid] - w < x) dfs(a, mid + !w, r, x, cnt + 1);
    else dfs(a, l, mid - w, x, cnt + 1);
    if ((r - l + 1) & 1) { // 奇数长度时才处理第二种情况
        w = 1, mid = (l + r + w) >> 1;
        if (a[mid] - w < x) dfs(a, mid + !w, r, x, cnt + 1);
        else dfs(a, l, mid - w, x, cnt + 1);
    }
}
```

---

### 关键思路与技巧总结
1. **递归分治**：每次递归处理两种可能的 mid 分割方式，取最小值。时间复杂度 O(nq)，但实际运行效率高。
2. **区间奇偶优化**：当区间长度为奇数时必须处理两种 mid 情况，偶数时两种方式等价（部分题解优化）。
3. **代码转译**：将题目给定的二分逻辑直接转换为递归条件，确保模拟准确。

---

### 相似题目推荐
1. [P1182 数列分段 II](https://www.luogu.com.cn/problem/P1182)  
   **考查点**：二分答案与可行性验证的结合使用。
2. [P2249 查找](https://www.luogu.com.cn/problem/P2249)  
   **考查点**：标准二分查找实现与边界处理。
3. [P8444 弱化版](https://www.luogu.com.cn/problem/P8444)  
   **考查点**：二分答案的变式应用，需处理特殊条件。

---
处理用时：72.46秒