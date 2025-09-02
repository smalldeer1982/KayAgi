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

本题的核心在于理解二分查找中随机选择 `mid` 的影响，并找到在最坏情况下最小化查找次数的策略。题解中普遍采用了暴力搜索（DFS）的方法，通过枚举每次 `w` 的取值（0 或 1），递归地计算最小查找次数。虽然暴力搜索的时间复杂度较高，但由于数据范围较小（`n ≤ 2^20`，`q ≤ 100`），这种方法在本题中是完全可行的。

### 所选高星题解

#### 1. 作者：bh1234666 (★★★★☆)
- **关键亮点**：该题解详细分析了贪心策略的缺陷，并通过具体例子说明了为什么贪心不能得到最优解。同时，题解中给出了递归实现的二分查找代码，清晰易懂。
- **核心代码**：
  ```cpp
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
  **实现思想**：通过递归枚举 `w` 的两种取值，分别计算查找次数，取最小值。

#### 2. 作者：见贤思齐_Seakies (★★★★☆)
- **关键亮点**：该题解通过爆搜的方式，直接枚举 `w` 的两种取值，并更新最小查找次数。代码简洁，思路清晰。
- **核心代码**：
  ```cpp
  inline void get(int *num, int x, int l, int r, int cnt) {
      int w, mid;
      if (l == r) {
          ans = min(cnt, ans);
          return;
      }
      w = 0, mid = (l + r + w) / 2;
      if (num[mid] - w < x) get(num, x, mid + !w, r, cnt + 1);
      else get(num, x, l, mid - w, cnt + 1);
      w = 1, mid = (l + r + w) / 2;
      if (num[mid] - w < x) get(num, x, mid + !w, r, cnt + 1);
      else get(num, x, l, mid - w, cnt + 1);
  }
  ```
  **实现思想**：通过递归枚举 `w` 的两种取值，分别计算查找次数，取最小值。

#### 3. 作者：Joker_1212 (★★★★☆)
- **关键亮点**：该题解详细解释了 `w` 的作用，并通过 DFS 实现了暴力搜索。代码结构清晰，易于理解。
- **核心代码**：
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
          dfs(a, mid + !w, r, x, cnt);
      else
          dfs(a, l, mid - w, x, cnt);
      if ((r - l + 1) & 1)
      {
          w = 1;
          mid = (l + r + w) >> 1;
          if (a[mid] - w < x)
              dfs(a, mid + !w, r, x, cnt);
          else
              dfs(a, l, mid - w, x, cnt);
      }
  }
  ```
  **实现思想**：通过递归枚举 `w` 的两种取值，分别计算查找次数，取最小值。

### 最优关键思路与技巧

1. **暴力搜索（DFS）**：通过递归枚举每次 `w` 的取值，计算最小查找次数。虽然时间复杂度较高，但在本题数据范围内完全可行。
2. **避免贪心策略**：贪心策略在本题中无法得到最优解，因为前面的决策会影响后面的决策，导致无法保证全局最优。

### 可拓展之处

- **类似算法套路**：在处理类似的二分查找问题时，如果存在随机化或不确定性因素，可以考虑通过暴力搜索或动态规划来找到最优解。
- **同类型题目**：可以参考以下洛谷题目：
  1. [P1182 数列分段 Section II](https://www.luogu.com.cn/problem/P1182)
  2. [P2249 【深基13.例1】查找](https://www.luogu.com.cn/problem/P2249)
  3. [P8444 无尽的矩阵](https://www.luogu.com.cn/problem/P8444)

### 个人心得总结

- **调试经历**：在实现递归时，注意边界条件的处理，避免无限递归。
- **踩坑教训**：贪心策略在本题中不适用，需要仔细分析问题，避免盲目使用贪心。
- **顿悟感想**：通过具体例子分析问题，能够更好地理解算法的适用性和局限性。

---
处理用时：39.42秒