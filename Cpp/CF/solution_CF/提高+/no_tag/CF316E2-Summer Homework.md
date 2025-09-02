# Summer Homework

## 题目描述

By the age of three Smart Beaver mastered all arithmetic operations and got this summer homework from the amazed teacher:

You are given a sequence of integers $ a_{1},a_{2},...,a_{n} $ . Your task is to perform on it $ m $ consecutive operations of the following type:

1. For given numbers $ x_{i} $ and $ v_{i} $ assign value $ v_{i} $ to element $ a_{xi} $ .
2. For given numbers $ l_{i} $ and $ r_{i} $ you've got to calculate sum ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF316E2/095e734be6677a366eba0d190d121c644f5bca60.png), where $ f_{0}=f_{1}=1 $ and at $ i>=2 $ : $ f_{i}=f_{i-1}+f_{i-2} $ .
3. For a group of three numbers $ l_{i} $ $ r_{i} $ $ d_{i} $ you should increase value $ a_{x} $ by $ d_{i} $ for all $ x $ $ (l_{i}<=x<=r_{i}) $ .

Smart Beaver planned a tour around great Canadian lakes, so he asked you to help him solve the given problem.

## 样例 #1

### 输入

```
5 5
1 3 1 2 4
2 1 4
2 1 5
2 2 4
1 3 10
2 1 5
```

### 输出

```
12
32
8
50
```

## 样例 #2

### 输入

```
5 4
1 3 1 2 4
3 1 4 1
2 2 4
1 2 10
2 1 5
```

### 输出

```
12
45
```

# 题解

## 作者：shinkuu (赞：1)

DS 好题。

涉及到斐波那契数列和一堆操作，很容易想到线段树+矩阵。而且我们的 @houzhe 学长曾经说过：

> 队友写半天线段树打各种 tag，还调不出来，我一脚把他踹下去写了个线段树维护矩阵就过了。

考虑对线段树上每一个点同时记录斐波那契数列情况和这个区间内和的转移。这样说有点抽象，把线段树上对应 $[i,i]$ 的区间的矩阵写出来就是：

$$\begin{bmatrix}0&1&0\\1&1&a_i\\0&0&1\end{bmatrix}$$

而计算答案初始状态的矩阵则是：

$$\begin{bmatrix}0&1&0\\0&0&0\\0&0&0\end{bmatrix}$$

其中，如果将矩阵用数组记录，那么位于 $(0,0)$ 到 $(1,1)$ 的是经典的斐波那契转移，初始装态的 $(0,2)$ 则是记录答案的和。

线段树其他节点直接 pushup 即可。

单点修改很简单，直接到叶子修改矩阵的 $(1,2)$ 位置即可。

查询时，用上述初始状态乘上对应区间的矩阵即可。

[code 及 E3 sol](https://www.luogu.com.cn/blog/Kato-Megumi/solution-cf316e3)

---

## 作者：liujiaxi123456 (赞：0)

#### 思路：
区修区查，考虑线段树，先不考虑修改，考虑查询。

发现 pushup 时左儿子的答案可以直接继承。

但右儿子的系数不对，考虑推式子：
- 应该的答案：$\sum_{i=mid+1}^{r} = f_{i-l}\cdot a_i$

有边界不好推式子，考虑先退去掉边界的情况：
- 设 $g_i = \sum_{j=0}^{n-1}f_{i+j}\cdot a_{j+1}$
- 则有 $g_{i-1}+g_{i-2}=\sum_{j=0}^{n-1}(f_{i+j-1}+f_{i+j-2})\cdot a_{j+1} = \sum_{j=0}^{n-1}f_{i+j}\cdot a_{j+1} = g_i$
- $g_i = g_{i-1}+g_{i-2}=2g_{i-2}+g_{i-3}=3g_{i-3}+2g_{i-4}=\cdots=f_{i-j}\cdot g_{j}+f_{i-j-1}\cdot g_{j-1}=f_{i-1}\cdot g_1+f_{i-2}\cdot g_0$

考虑把式子带入线段树中维护：
- 相当于对线段树上的每个节点维护它的 $g_0,g_1$。
- pushup 时：
  + $g_{0, t} = g_{0, ls} + g_{mid-l+1, rs}$
  + $g_{1, t} = g_{1, ls} + g_{mid-l+2, res}$

现在考虑区间加：
- 写式子，设区间加 $d$：
  + $ \Delta_{g_0} = f_0\cdot d + f_1\cdot d + \cdots + f_{r-l}\cdot d = sumf_{r-l}\cdot d $
  + $\Delta_{g_1} = f_1\cdot d + f_2\cdot d + \cdots + f_{r-l+1}\cdot d = (sumf_{r-l+1}-f_0)\cdot d$
- 预处理 $f$ 的前缀和即可。
#### Code：
~~这是一个比次优解快了近两倍的代码。~~
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int Maxn = 2e5+5, MOD = 1e9;
int N;

class SegmentTree {
private:
	ll f[Maxn], sumf[Maxn];
	struct Segment { int tag; ll g0, g1; } seg[Maxn*4];
	inline int calc(int t, int k) {
		return (!k ?seg[t].g0 :(k==1 ?seg[t].g1 :(f[k-1]*seg[t].g1 + f[k-2]*seg[t].g0)%MOD));
	}
	inline void pushup(int t, int llen) {
		seg[t].g0 = (seg[t<<1].g0 + calc(t<<1|1, llen)) %MOD;
		seg[t].g1 = (seg[t<<1].g1 + calc(t<<1|1, llen+1)) %MOD;
	}
	inline void Add(int t, int len, int d) {
		seg[t].tag = (seg[t].tag + d) %MOD;
		seg[t].g0 = (seg[t].g0 + sumf[len-1]*d) %MOD;
		seg[t].g1 = (seg[t].g1 + sumf[len]*d-d) %MOD; // 差分掉 f[0]
	}
	inline void pushdown(int t, int l, int r) {
		if(seg[t].tag) {
			int mid = (l+r)>>1;
			Add(t<<1, mid-l+1, seg[t].tag);
			Add(t<<1|1, r-mid, seg[t].tag);
			seg[t].tag = 0;
		}
	}
	inline void Change(int t, int l, int r, int pos, int k) {
		if(l == r)	return seg[t].g0 = seg[t].g1 = k, void();
		int mid = (l+r)>>1; pushdown(t, l, r);
		if(pos <= mid)	Change(t<<1, l, mid, pos, k);
		else	Change(t<<1|1, mid+1, r, pos, k);
		pushup(t, mid-l+1);
	}
	inline ll Query(int t, int l, int r, int L, int R) {
		if(r<L || R<l)	return 0;
		if(L<=l && r<=R)	return calc(t, l-L);
		int mid = (l+r)>>1; pushdown(t, l, r);
		return Query(t<<1, l, mid, L, R) + Query(t<<1|1, mid+1, r, L, R);
	} 
	inline void Modify(int t, int l, int r, int L, int R, int d) {
		if(r<L || R<l)	return ;
		if(L<=l && r<=R)	return Add(t, r-l+1, d);
		int mid = (l+r)>>1; pushdown(t, l, r);
		Modify(t<<1, l, mid, L, R, d), Modify(t<<1|1, mid+1, r, L, R, d);
		pushup(t, mid-l+1);
	}
	inline void Build(int t, int l, int r, int *a) {
		if(l == r)	return seg[t].g0 = seg[t].g1 = a[l], void();
		int mid = (l+r)>>1; 
		Build(t<<1, l, mid, a), Build(t<<1|1, mid+1, r, a);
		pushup(t, mid-l+1);
	}
public:
	inline void init(int *a, int N) {
		f[0] = f[1] = 1, sumf[0] = 1, sumf[1] = 2;
		for(int i=2; i<=N; i++) {
			f[i] = (f[i-1] + f[i-2]) %MOD;
			sumf[i] = (sumf[i-1] + f[i]) %MOD;
		}
		Build(1, 1, N, a);
	}
	inline void Change(int pos, int y) { Change(1, 1, N, pos, y); }
	inline int Query(int l, int r) { return Query(1, 1, N, l, r) %MOD; }
	inline void Modify(int l, int r, int d) { Modify(1, 1, N, l, r, d); }
} seg;

namespace Josh_zmf {
	
	int Q, a[Maxn];

	inline int main() {
		cin>> N>> Q;
		for(int i=1; i<=N; i++)	cin>> a[i];
		seg.init(a, N);
		for(int opt, l, r, x, y; Q--; ) {
			cin>> opt;
			if(opt == 1) {
				cin>> x>> y;
				seg.Change(x, y);
			} else if(opt == 2) {
				cin>> l>> r;
				cout<< seg.Query(l, r)<< '\n';
			} else {
				cin>> l>> r>> x;
				seg.Modify(l, r, x);
			}
		}
		return 0;
	}

}

int main() {
	Josh_zmf::main();
	return 0;
}
```

---

