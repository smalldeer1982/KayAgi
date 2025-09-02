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

• 综合分析与结论：这几道题解均指出本题贪心不可行，因为前面决策会影响后面决策。鉴于数据范围，都采用暴力搜索的方法。具体是基于题目给定的二分查找代码，通过递归对w取0和1两种情况分别搜索，记录找到目标值的最小递归层数。各题解思路相近，在代码实现细节和注释详细度上有差异。
• 所选的题解：
  - 作者：bh1234666 (4星)
    - 关键亮点：对贪心不可行原因阐述清晰，通过具体例子对比贪心与正确解法的差异。代码实现采用递归，逻辑简洁。
    - 核心代码实现思想：`find`函数递归实现二分，每次递归时对`mid`的两种计算方式分别递归并取最小值，直到找到目标位置返回最小查找次数。
```
int find(int k,int f,int l)
{
	if(f==l) return 0;
	int mid=(f+l)>>1,ret=32;
	if(mid<k) ret=find(k,mid+1,l);
	else ret=find(k,f,mid);
	mid=(f+l+1)>>1;
	if(mid<=k) ret=min(ret,find(k,mid,l));
	else ret=min(ret,find(k,f,mid-1));
	return ret+1;
}
```
  - 作者：见贤思齐_Seakies (4星)
    - 关键亮点：代码注释详细，从题意概述、题目分析到代码各部分功能都有说明，便于理解。以题目递归代码为基础进行爆搜，结构清晰。
    - 核心代码实现思想：`get`函数依据题目给定的递归二分查找代码框架，对`w`分别取0和1递归搜索，更新最小查找次数`ans`，`find`函数初始化并调用`get`函数。
```cpp
inline void get(int *num, int x, int l, int r, int cnt) {
	int w, mid;
	if (l == r) {
		ans = min(cnt, ans); 
		return;
	}
	w = 0, mid = (l + r + w) / 2; 
	if (num[mid] - w < x) get(num, x, mid +!w, r, cnt + 1);
	else get(num, x, l, mid - w, cnt + 1);
	w = 1, mid = (l + r + w) / 2; 
	if (num[mid] - w < x) get(num, x, mid +!w, r, cnt + 1);
	else get(num, x, l, mid - w, cnt + 1);
}
inline int find(int *num, int x, int len) {
	ans = 1e9;
	get(num, x, 1, len, 0);
	return ans;
}
```
  - 作者：Joker_1212 (4星)
    - 关键亮点：对题目中`w`的作用总结出有用结论，即区间长度为偶数时最终确定区间唯一，奇数时有两个。DFS实现时针对区间奇偶性分别处理，代码简洁高效。
    - 核心代码实现思想：`dfs`函数递归实现二分查找，区间长度为偶数时`w`取0，奇数时`w`分别取0和1递归，更新最小查找次数`ans`。
```cpp
inline void dfs(int *a, int l, int r, int x, int cnt)
{
    if (l == r)
    {
        ans = min(ans, cnt);
        return;
    }
    ++cnt;
    int w = 0;
    int mid = (l + r + w) >> 1;
    if (a[mid] - w < x)
        dfs(a, mid +!w, r, x, cnt);
    else
        dfs(a, l, mid - w, x, cnt);
    if ((r - l + 1) & 1)
    {
        w = 1;
        mid = (l + r + w) >> 1;
        if (a[mid] - w < x)
            dfs(a, mid +!w, r, x, cnt);
        else
            dfs(a, l, mid - w, x, cnt);
    }
}
```
• 最优关键思路或技巧：面对决策有后效性不能贪心的情况，利用数据范围允许的条件，通过暴力递归搜索，对二分查找中`w`的不同取值情况分别处理，记录最小查找次数。
• 可拓展之处：此类题目关键在于分析决策的后效性，若贪心不可行，在数据范围允许下暴力搜索是常用方法。类似题目通常是在二分查找基础上增加条件或改变规则，需要深入理解二分原理和题目规则来求解。
• 推荐题目：
  - [P1182 数列分段 Section II](https://www.luogu.com.cn/problem/P1182)
  - [P2249 查找 P2249](https://www.luogu.com.cn/problem/P2249)
  - [P8444 [HGOI-1] 区间](https://www.luogu.com.cn/problem/P8444)
• 个人心得：无。 

---
处理用时：24.78秒