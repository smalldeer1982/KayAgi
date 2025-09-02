# [NEERC 2014] Improvements

## 题目描述

Son Halo 拥有编号从 1 到 $n$ 的 $n$ 艘飞船和一个空间站。它们最初与空间站在一条直线上排列，因此飞船 $i$ 距离空间站 $x_i$ 米，并且所有飞船都在空间站的同一侧（$x_i > 0$）。所有 $x_i$ 都是不同的。空间站被认为是编号为 0，并且 $x_0$ 被认为等于 0。

每两艘连续编号的飞船之间用绳子连接，第一艘飞船与空间站连接。编号为 $i$ 的绳子（对于 $1 \le i \le n$）连接飞船 $i$ 和 $i-1$。注意，编号为 1 的绳子连接第一艘飞船与空间站。

Son Halo 认为绳子 $i$ 和绳子 $j$ 相交，当且仅当线段 $[x_{i}^{min}, x_{i}^{max}]$ 和 $[x_{j}^{min}, x_{j}^{max}]$ 有公共的内部点，但它们中的任何一个都不完全包含在另一个中，其中 $x_{k}^{min} = \min(x_{k-1}, x_k)$，$x_{k}^{max} = \max(x_{k-1}, x_k)$。即：

$$
\begin{cases} 
x_{i}^{min} < x_{j}^{min} \sim \& \sim x_{j}^{min} < x_{i}^{max} \sim \& \sim x_{i}^{max} < x_{j}^{max} \\
x_{j}^{min} < x_{i}^{min} \sim \& \sim x_{i}^{min} < x_{j}^{max} \sim \& \sim x_{j}^{max} < x_{i}^{max} \ 
\end{cases}
$$

Son Halo 想要重新排列飞船，使得没有绳子相交。因为他很懒，他希望以一种方式重新排列飞船，使得保持在原始位置 $x_i$ 的飞船总数最大化。所有飞船在重新排列后必须保持在空间站的同一侧，并且在不同的位置 $x_i$。然而，飞船在重新排列后可以占据任何实数位置 $x_i$。

你的任务是找出可以保持在其初始位置的飞船的最大数量。

## 说明/提示

时间限制：1 秒，内存限制：256 MB。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
4
1 3 2 4
```

### 输出

```
3
```

## 样例 #2

### 输入

```
4
1 4 2 3
```

### 输出

```
4
```

# 题解

## 作者：junee (赞：1)

# P6993 [NEERC2014] Improvements 题解

## 前置知识

树状数组。

## 题目分析

首先我们可以知道，对于移动一个点等价于删除一个点，这个是好理解的，那么原题面转化为删去最少的点使得剩下的点连线合法。

考虑最后剩下的合法点序列的形态长什么样。

![](https://cdn.luogu.com.cn/upload/image_hosting/nddb3vhh.png)

我们规定箭头指的方向表示后面节点的编号大于前面结点的编号。发现任意一个节点都保证一定是后缀点的最大或最小的 $x$，不然就不合法。

对于一个节点，他下一个节点可能往左跳或者往右跳，往右跳，使得这段序列的编号持续递增，往左跳使得在它左边的点的编号持续递减。

对于任意一个合法序列，按照 $x$ 重排后，发现它的编号是一段上升子序列和一段下降子序列，其实我们答案就是枚举每一个点的最长上升子序列和最长下降子序列，最后取出最大值即可。

最长上升子序列和最长下降子序列可以用树状数组预处理出来。

时间复杂度为 $O(n\log n)$。

```
#include<iostream>
#include<iomanip>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<random>
#include<chrono>
using namespace std;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
typedef long long LL;
const int N=2e5+10; 
int n,a[N],ans=0;
int f[N],g[N];
struct DS{
	int tr[N*2];
	void init(){
		for(int i=1;i<=N;i++)tr[i]=0;
	}
	void add(int x,int k){
		for(;x<=N;x+=x&-x)tr[x]=max(tr[x],k);
	}
	int ask(int x){
		int res=0;
		for(;x;x-=x&-x)res=max(res,tr[x]);
		return res;
	}
}bit;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++){
		f[i]=bit.ask(a[i])+1;
		bit.add(a[i],f[i]);
	}
	bit.init();
	for(int i=1;i<=n;i++)a[i]=n-a[i]+1;
	for(int i=1;i<=n;i++){
		g[i]=bit.ask(a[i])+1;
		bit.add(a[i],g[i]);
	}
	for(int i=1;i<=n;i++)ans=max(f[i]+g[i]-1,ans);
	cout<<ans;
	return 0;
}
```

---

## 作者：zhylj (赞：1)

不难发现我们每次可以将不选的点移动到上一个选的点向正确方向一个充分小的长度位置，于是问题可以转化为选取一个长度最大的合法序列。

考虑若不动的点的坐标集合为 $\{0,x_{i_1},x_{i_2},\cdots,x_{i_k}\}(i_1\lt i_2\lt \cdots\lt i_k)$，那么根据走到这个绳子的时候是向左走还是向右走，我们可以发现，该序列合法当且仅当：对于所有 $j\in[1,k]$，$x_{i_j}$ 要么比 $\max_{p\gt j} x_{i_p}$ 还要大，要么比 $\min_{p\gt j} x_{i_p}$ 还要小。

然后考虑枚举 $i_k$，注意到对于任何可能的序列从 $i_k$ 开始往前的后缀最大值的位置和后缀最小值的位置必然只会存在一个交，也就是 $i_k$。于是其实两部分的贡献是独立的，我们可以把以 $i_k$ 结尾的最长上升和下降子序列加起来再减一（多统计了 $i_k$）即可得到这个位置能贡献的最大答案。

然后就做到了 $\mathcal O(n\log n)$。

```cpp
const int N = 5e5 + 5;

int n, a[N], f[N], g[N];

struct Bit {
	int tr[N];
	void Modify(int o, int v) { for(; o <= n; o += o & -o) tr[o] = std::max(tr[o], v); }
	int Query(int o) { int ret = 0; for(; o; o -= o & -o) ret = std::max(ret, tr[o]); return ret; }
} A, B;

int main() {
	rd(n);
	for(int i = 1; i <= n; ++i) rd(a[i]);
	int ans = 0;
	for(int i = 1; i <= n; ++i) {
		f[i] = A.Query(a[i]) + 1;
		g[i] = B.Query(n - a[i] + 1) + 1;
		A.Modify(a[i], f[i]);
		B.Modify(n - a[i] + 1, g[i]);
		ans = std::max(ans, f[i] + g[i] - 1);
	}
	printf("%d\n", ans);
	return 0;
}
```

---

