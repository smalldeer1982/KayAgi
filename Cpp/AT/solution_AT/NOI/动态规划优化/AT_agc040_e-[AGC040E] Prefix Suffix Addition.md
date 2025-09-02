# [AGC040E] Prefix Suffix Addition

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc040/tasks/agc040_e

すぬけくんは，長さ $ N $ の整数列 $ x_1,x_2,\cdots,x_N $ を持っています． 最初，$ x $ の全ての要素は $ 0 $ です．

すぬけくんは，以下の $ 2 $ 種類の操作を好きな順序で好きな回数行うことができます．

- 操作 $ 1 $: 整数 $ k $ ($ 1\ \leq\ k\ \leq\ N $)，及び長さ $ k $ の非負整数列 $ c_1,c_2,\cdots,c_k $ を自由に選ぶ． ただし，$ c $ は**広義単調増加**でなくてはならない． そして，すべての $ i $ ($ 1\ \leq\ i\ \leq\ k $) について，$ x_i $ を $ x_i+c_i $ で置き換える．
- 操作 $ 2 $: 整数 $ k $ ($ 1\ \leq\ k\ \leq\ N $)，及び長さ $ k $ の非負整数列 $ c_1,c_2,\cdots,c_k $ を自由に選ぶ． ただし，$ c $ は**広義単調減少**な数列でなくてはならない． そして，すべての $ i $ ($ 1\ \leq\ i\ \leq\ k $) について，$ x_{N-k+i} $ を $ x_{N-k+i}+c_i $ で置き換える．

すぬけくんの目標は，全ての $ i $ について，$ x_i=A_i $ となるようにすることです． すぬけくんが目標を達成するために行う操作回数の最小値を求めてください．

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ A_i\ \leq\ 10^9 $
- 入力される値はすべて整数である．

### Sample Explanation 1

例えば，以下のように $ 3 $ 回の操作を行えば良いです． $ 3 $ 回未満の操作で目標は達成できません． - $ k=2,c=(1,2) $ として，操作 $ 1 $ を行う．操作後，$ x=(1,2,0,0,0) $ となる． - $ k=3,c=(0,0,1) $ として，操作 $ 1 $ を行う．操作後，$ x=(1,2,1,0,0) $ となる． - $ k=2,c=(2,1) $ として，操作 $ 2 $ を行う．操作後，$ x=(1,2,1,2,1) $ となる．

## 样例 #1

### 输入

```
5
1 2 1 2 1```

### 输出

```
3```

## 样例 #2

### 输入

```
5
2 1 2 1 2```

### 输出

```
2```

## 样例 #3

### 输入

```
15
541962451 761940280 182215520 378290929 211514670 802103642 28942109 641621418 380343684 526398645 81993818 14709769 139483158 444795625 40343083```

### 输出

```
7```

# 题解

## 作者：FjswYuzu (赞：45)

为什么标题是这串数字，懂的都懂啊！

很巧妙的题目。

首先这两个操作如果只有一个，怎么办？

假设我们有的是第一个操作。我们可以先选一堆前缀 $0$，然后再设置一个不下降序列。这样相当于区间减去一个不下降序列。

然后如果只有这样一个操作怎么办。容易发现我们可以把整个序列看成若干个极长不下降子段，并且最优情况下一次操作一定不能消去两个不同的不下降子段。因此只有一个操作的时候就等于整个序列的不下降子段个数。

显然对于另外一个操作也是成立的。这里出现了分开处理的动机。

自然我们想到对每一个 $i$ 分成两个序列 $a_i=p_i+q_i$，且令答案为 $p$ 的不下降极长子段个数和 $q$ 的不上升极长子段个数。这样就可以 DP 了。

记 $dp_{i,j}$ 表示我们在第 $i$ 个数令了 $q_i=j$。容易发现 DP 转移：

$$
dp_{i,j} = \min_{k=0}^{a_{i-1}} \{dp_{i-1,k}+[k<j]+[a_{i-1}-k>a_i-j]\}
$$

其实类似于两个条件 $p_{i-1}>p_i,q_{i-1}<q_i$ 每满足一个就会让值加一。注意到第一个非下降极长子段和最后一个非上升极长子段，我们还没有处理，所以答案应该取 $\min dp_{n+1}$。

分析条件的特殊性，发现在只考虑前 $i$ 个数的子问题，即 $dp_i$，在 $j<k$ 的情况下一定满足 $dp_{i,j} < dp_{i,k}$。因为 $q_i$ 越小 $p_i$ 越大，而两个条件为 $p_{i-1}>p_i,q_{i-1}<q_i$，所以 $q_i$ 越小一定最优。

同时我们可以发现 $dp_{i,0} + 2 \geq dp_{i,a_i}$。原因也很显然：因为最多只有两个条件同时满足，这样就算从同一个状态转移差值最多也只有 $2$。

那么有一个想法就是维护 $f_{0,i},f_{1,i}$ 表示 $dp_i$ 取值不同的三段（不维护 $f_{2,i}$ 的原因是它显然等于 $a_i$），同时维护取值最小的 $dp_i$。剩下的代码细节在代码里面。

```cpp
int n,a[200005];
int main(){
	n=read();
	for(int i=1;i<=n;++i)	a[i]=read();
	int f0=0,f1=0,dp=0; // f2=a[i]。dp 表示 dp[i][0]，取值为 dp[i][0] 的区间为 [0, f0]，取值为 dp[i][1] 的区间为 [f0+1, f1]
	for(int i=1;i<=n;++i)
	{
		int v=a[i],lst=a[i-1];
		if(v>=lst)	f1=max(f1,f0+v-lst);
		/*
		在这里 f0 显然不能移动，因为向右移动了会导致 q[i]>q[i-1] 导致取值变化，并且不动显然不会变化。
		然后 f1 的取值由两个方向决定。一个是不动保证了 q 没有贡献，一个是平移保证 p 没有贡献。两者取最大值。
		*/
		else
		{
			f1=max(f0,f1-lst+v);
			f0-=lst-v;
			/*
			这里的原因是，f1 可能只能选择让 p 贡献然后继承 f0 的位置，或者是平移让 p 没有贡献。
			f0 只能平移选择让 p 没有贡献。
			*/
			if(f0<0)	++dp,f0=f1,f1=v;
			/*
			f0 的取值已经不合法了，这个时候更新取值范围就好了。
			*/
		}
		f0=min(f0,v),f1=min(f1,v);
	}
	write(dp+int(f0<a[n])); // 点值算到 n+1
	return 0;
}
```

非常精妙的题目。

---

## 作者：APJifengc (赞：31)

关于本题的几个性质，楼上已经讲的很清楚了，但是由于~~我太菜了~~，没有明白楼上如何转移的，所以这里主要讲一下如何分类讨论转移。

# 分析

首先，DP 式子可以写成这样的形式：

$$
f_{i,j}=\min_{k=0}^{a_{i-1}}\{f_{i-1,k}+[j<k]+[j<k+a_i-a_{i-1}]\}
$$

由于是取 $\min$，对于一个 $j$，只有当 $k$ 减小时答案才可能会减小，所以对于取值相同的一段 $f_{i-1,k}$ 来说，$k$ 越小，答案一定越优，所以我们只需要考虑每段区间的最左边的端点就行，于是只用考虑三个左端点即可。

设这三个区间为：

$$
\begin{aligned}
\forall j\in[0, p],f_{i,j}&=d + 2\\
\forall j\in[p + 1, q],f_{i,j}&=d + 1\\
\forall j\in[q + 1, a_i],f_{i,j}&=d
\end{aligned}
$$

那么式子其实就是：

$$
f_{i,j}=\min\begin{cases}
d + 2 + [j < 0]+[j < 0 + a_i - a_{i-1}]\\
d + 1 + [j < p + 1]+[j < p + 1 + a_i - a_{i-1}]\\
d     + [j < q + 1]+[j < q + 1 + a_i - a_{i-1}]
\end{cases}
$$

设 $\Delta=a_i - a_{i-1}$，那么就是：

$$
f_{i,j}=\min\begin{cases}
d + 2 + [j < \Delta]\\
d + 1 + [j < p + 1]+[j < p + 1 + \Delta]\\
d     + [j < q + 1]+[j < q + 1 + \Delta]
\end{cases}
$$

我们分两种情况来讨论：

1. 	$\Delta\ge0$
   	
   	可以画个图来看：
   	
   	$$
    \begin{aligned}
    &\mid\xleftarrow{0\kern{0px}} d+3 \xrightarrow{\kern{0px}\Delta-1}
    \mid\xleftarrow{\Delta\kern{85px}} d+2 \xrightarrow{\kern{90px}a_i}
    \mid\\
    &\mid\xleftarrow{0\kern{5px}} d+3 \xrightarrow{\kern{5px}p}
    \mid\xleftarrow{p+1\kern{10px}} d+2 \xrightarrow{\kern{10px}p+\Delta}
    \mid\xleftarrow{p+\Delta+1\kern{35px}} d+1 \xrightarrow{\kern{35px}a_i}
    \mid\\
    &\mid\xleftarrow{0\kern{15px}} d+2 \xrightarrow{\kern{15px}q}
    \mid\xleftarrow{q+1\kern{20px}} d+1 \xrightarrow{\kern{22px}q+\Delta}
    \mid\xleftarrow{q+\Delta+1\kern{20px}} d \xrightarrow{\kern{25px}a_i}
    \mid\\
    \end{aligned}
    $$
    
    设新的 $p,q$ 为 $p',q'$。
    
    发现，$d$ 的取值一定是 $[q+\Delta+1,a_i]$，即 $q'=q + \Delta$。
    
    $p \le q$，那么此时只需要在 $q$ 和 $p+\Delta$ 中取 $\min$ 即可，即 $p'=\min(q, p + \Delta)$。
    
    发现此时 $p',q'\le a_i$ 是一定成立的，因为 $p\le a_{i-1},\ p'\le p+\Delta,\ p+\Delta \le a_{i-1}+\Delta=a_i$，$q'$ 同理，所以不需要考虑超出边界的问题。
2.  $\Delta<0$
    
    同样的，画出图来：
    
    $$
    \begin{aligned}
    &\mid\xleftarrow{0\kern{124px}} d+2 \xrightarrow{\kern{120px}a_i}
    \mid\\
    &\mid\xleftarrow{0\kern{5px}} d+3 \xrightarrow{\kern{5px}p+\Delta}
    \mid\xleftarrow{p+\Delta+1\kern{10px}} d+2 \xrightarrow{\kern{10px}p}
    \mid\xleftarrow{p+1\kern{35px}} d+1 \xrightarrow{\kern{35px}a_i}
    \mid\\
    &\mid\xleftarrow{0\kern{15px}} d+2 \xrightarrow{\kern{15px}q+\Delta}
    \mid\xleftarrow{q+\Delta+1\kern{20px}} d+1 \xrightarrow{\kern{22px}q}
    \mid\xleftarrow{q+1\kern{24px}} d \xrightarrow{\kern{22px}a_i}
    \mid\\
    \end{aligned}
    $$
    
    和上面是一样的，$p'=\min(q+\Delta,p),q'=q$。
    
    但是这里需要注意，$q$ 可能大于等于 $a_i$，这时候答案为 $d$ 的区间就不存在了，此时的最小值变成了 $d+1$，所以需要更新一下 $d$ 的取值。
    
    还需要注意一下 $q+\Delta<0$ 的情况。
    
# 代码

```cpp
int n, a[MAXN];
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    int p = -1, q = -1, d = 0;
    for (int i = 1; i <= n + 1; i++) {
        int delta = a[i] - a[i - 1];
        if (delta >= 0) {
            p = min(q, p + delta);
            q += delta;
        } else {
            p = max(min(q + delta, p), -1);
            if (q >= a[i]) {
                d++;
                q = p, p = -1;
            }
        }
    }
    printf("%d\n", d);
    return 0;
}
```

---

## 作者：约瑟夫用脑玩 (赞：12)

上一篇题解思路很清晰，但是很多地方并未解释原因，故在此补充我自己对结论的一些证明。

结论1：操作可以看做是任选一个区间加上单调不下降序列或单调不上升序列。

证明：在操作所加的序列前后添加上若干个 $0$ 即可表示，即对操作一的序列前面加上 $l-1$ 个 $0$ 或是在操作二的序列后面加上 $n-r$ 个 $0$ 表示操作区间 $[l,r]$。

结论2：只考虑加上单调不下降序列的操作，一定有一种安排方案使得区间两两不交，单调不上升序列同理。

证明：以下叙述默认不考虑出现两个操作可以合并成一个操作的情况。

考虑两个区间有交的操作形如 $[a,b],[c,d]$，满足 $a\le c,b\le d$，由于有交还满足 $c\le b$。

那么我们取出操作 $[c,d]$ 里面 $[c,b]$ 的那段区间，直接加到序列 $[a,b]$ 上。

有 $[a,b]$ 仍然单调不下降，且操作区间 $[c,d]$ 变为了操作区间 $(b,d]$。

再考虑两个区间有包含的操作形如 $[a,b],[c,d]$，满足 $a\le c,d\le b$，显然有交。

那么我们取出操作 $[a,b]$ 里面 $(d,b]$ 的那段区间，将 $[c,d]$ 加到剩下的 $[a,d]$ 那段序列上。

有 $[a,d]$ 仍然单调，多出来了一个操作 $(d,b]$ 可以看作是操作 $[c,d]$ 变成了操作 $(d,b]$。

------------

叙述：

我们将一个位置 $a_i$ 的贡献分为两部分，分别是操作一和操作二的贡献 $b_i,c_i$，那么有 $a_i=b_i+c_i$。

考虑 $b_i$ 的贡献，应该是划分成上升子序列的个数，转化一下对答案贡献即为：$\sum_{i<n}[b_i>b_{i+1}]$。（可以参考[CF578E](https://www.luogu.com.cn/problem/CF578E)）

$c_i$ 同理，由于 $c_i=a_i-b_i$，那么我们设 $f_{i,j}$ 表示DP到第 $i$ 个位置，$b_i=j$ 时的最小值。

------------

结论3：$i$ 不变时，$j$ 越大，$f_{i,j}$ 减少或不变。

证明：考虑转移，$f_{i,j}=\min_k{f_{i-1,k}+[k>j]+[a_{i-1}-k<a_i-j]}$。

有 $f_{i,j}=\min_k{f_{i-1,k}+[j<k]+[j<k-a_{i-1}+a_i]}$，显然 $j$ 越大时贡献越小。

结论4：$f_{i,0}\le f_{i,a_i}+2$

证明：考虑满足 $b_i=a_i$ 的一种最优方案，考虑包含 $i$ 操作1，一定形如：

![](https://cdn.luogu.com.cn/upload/image_hosting/fqjvi14x.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

将 $b_i$ 改为 $0$，考虑变化：

![](https://cdn.luogu.com.cn/upload/image_hosting/hgzqxqrt.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

显然至多增加 $1$ 的贡献，$c_i$ 同理，故至多 $+2$。

------------

叙述：那么我们只存储满足 $f_{i,x}=k$ 的 $x$ 的范围，由于 $k$ 至多只有三种，直接转移有值的对应的范围即可。

时间复杂度 $O(n)$。

---

## 作者：EuphoricStar (赞：10)

比较神奇的题。

考虑如果只有第 $1$ 种操作，答案显然就是 $\sum\limits_{i = 0}^n [a_i > a_{i + 1}]$。因为两个极长不降子段显然不可能通过一次操作消除，并且可以逐个消除极长不降子段达到这个下界。

现在有 $2$ 种操作，不妨设第 $1$ 种操作对 $a_i$ 的贡献为 $b_i$，第 $2$ 种操作对 $a_i$ 的贡献为 $c_i$（显然 $a_i = b_i + c_i$）。那么答案就是 $\sum\limits_{i = 0}^n [b_i > b_{i + 1}] + [c_i < c_{i + 1}]$。

$b_i, c_i$ 不确定，自然地想到一个初步的 dp，设 $f_{i, j}$ 为考虑到第 $i$ 位，$b_i = j, c_i = a_i - j$ 的最小操作次数。有转移：

$$f_{i, j} = \min\limits_{k = 0}^{a_{i - 1}} f_{i - 1, k} + [k > j] + [a_{i - 1} - k < a_i - j]$$

整理得：

$$f_{i, j} = \min\limits_{k = 0}^{a_{i - 1}} f_{i - 1, k} + [j < k] + [j < k + a_i - a_{i - 1}]$$

初值 $f_{0, 0} = 0$，答案为 $f_{n + 1, 0}$。

没办法直接数据结构优化，不妨观察这个转移形式的性质。

发现 $f_{i, j}$ 单调不增，因为更大的 $j$ 显然要加的更少。

又发现如果我们强制钦定 $f_{i, 0}$ 从 $f_{i, a_i}$ 的最优转移点转移过来，会得到 $f_{i, 0} \le f_{i, a_i} + 2$。

于是我们可以知道 $f_i$ 被分成值相等的至多 $3$ 段。然后我们维护这 $O(1)$ 段即可。

注意到 $f_{i, j}$ 一定是从 $f_{i - 1}$ 的每一段的左端点转移过来（因为 $k$ 增大，$f_{i - 1, k}$ 不变，后面加的不会变少），所以如果我们知道 $j$，我们可以 $O(1)$ 计算出后面那坨最小值。

于是我们对于 $f_i$ 的 $O(1)$ 段，每一段知道左端点，二分找到其右端点即可。这样转移是 $O(\log V)$ 的（其实可以分类讨论做到 $O(1)$ 转移，但是我太懒了）。

[code](https://atcoder.jp/contests/agc040/submissions/43926597)

---

## 作者：Log_x (赞：10)

## Solution

- 在操作所加的序列前添加上若干个 $0$ 就可以看做是任选一个区间加上单调不下降序列或单调不上升序列。

- 由调整法可知，就其中一种操作而言，方案中区间覆盖的范围一定可以做到不相交。

- 设 $b_i, c_i$ 分别表示操作 1 和操作 2 在第 $i$ 个位置加上的权值，满足 $\forall 1 \le i \le n, b_i + c_i = a_i$。

- 于是在确定 $b,c$ 的情况下，最优的方案就是在将 $b,c$ 中为 $0$ 的元素删去后，将 $b$ 划分为尽量少的单调不下降序列，将 $c$ 划分为尽量少的单调不上升序列。

- 令 $a_0 = a_{n + 1} = 0$，则最优的答案就为 $\sum \limits_{i = 0}^{n}([b_i > b_{i + 1}] + [c_i < c_{i + 1}])$。

- 因此朴素的 DP 就是设 $f_{i,j}$ 表示已经处理了前 $i$ 个位置、$b_i = j$ 的最少操作数。

- 由调整法可知， $f_{i,j}$ 在固定 $i$ 时随着 $j$ 的增大单调不上升，并且 $f_{i,0} \le f_{i,a_i} + 2$， 可以将 $f_{i,j}$ 中权值相同的并成一块进行转移，显然块数只有常数级别。

- 时间复杂度 $\mathcal O(n)$。
 
## Code
 
```cpp
#include <bits/stdc++.h>

template <class T>
inline void read(T &res)
{
	char ch;
	while (ch = getchar(), !isdigit(ch));
	res = ch ^ 48;
	while (ch = getchar(), isdigit(ch))
		res = res * 10 + ch - 48;
}

template <class T>
inline T Max(T x, T y) {return x > y ? x : y;}
template <class T>
inline T Min(T x, T y) {return x < y ? x : y;}

using std::vector;
const int N = 2e5 + 5;
int a[N], n;

struct seg
{
	int l, r;

	seg() {}
	seg(int L, int R):
		l(L), r(R) {}

	inline bool Empty()
	{
		return l > r;
	}

	inline seg operator & (const seg &a) 
	{
		return seg(Max(l, a.l), Min(r, a.r)); 
	}

	inline seg operator ^ (const seg &a)
	{
		return a.l == l ? seg(a.r + 1, r) : seg(l, a.l - 1);
	}
};

struct node
{
	seg a;
	int v;

	node() {}
	node(seg A, int V):
		a(A), v(V) {}

	inline bool operator < (const node &a) const
	{
		return v < a.v;
	}
};

vector<node> now, nxt, cur;

int main()
{
	freopen("operate.in", "r", stdin);
	freopen("operate.out", "w", stdout);

	read(n);
	for (int i = 1; i <= n; ++i)
		read(a[i]);
	now.push_back(node(seg(0, 0), 0));
	for (int i = 1; i <= n + 1; ++i)
	{
		int det = a[i] - a[i - 1];
		seg lim = seg(0, a[i]), tmp;

		cur.clear();
		for (node x : now)
		{
			tmp = seg(0, Min(det + x.a.r - 1, x.a.r - 1)) & lim;
			if (!tmp.Empty())
				cur.push_back(node(tmp, x.v + 2));
			tmp = seg(det + x.a.l, x.a.r - 1) & lim;
			if (!tmp.Empty())
				cur.push_back(node(tmp, x.v + 1));
			tmp = seg(x.a.l, det + x.a.r - 1) & lim;
			if (!tmp.Empty())
				cur.push_back(node(tmp, x.v + 1));
			tmp = seg(Max(x.a.l, det + x.a.l), a[i]) & lim; 
			if (!tmp.Empty())
				cur.push_back(node(tmp, x.v));
		}
		std::sort(cur.begin(), cur.end());
		now.clear();
		for (node x : cur)
		{
			seg res = x.a;
			for (node y : now)
			{
				tmp = res & y.a;
				if (!tmp.Empty())
					res = res ^ tmp;
				if (res.Empty())
					break ;
			}
			if (!res.Empty())
				now.push_back(node(res, x.v));
		}
	}
	printf("%d\n", now[0].v);

	fclose(stdin); fclose(stdout);
	return 0;
}
```

---

## 作者：CUIXIAO (赞：2)

由于可以加上的是非负数，所以操作等价于给一个区间加上一段不下降或者不上升的值。

把所有不下降的操作拉出来单独看，总有一种方法可以使得所有操作的区间无交，证明可以考虑两个区间$[a,b]$和$[c,d]$，满足$a<c<b<d$，那么把$[c,d]$上$[c,b]$的操作加到$[a,b]$上，也是合法的，于是同一类的操作区间无交。

假设$a_i=b_i+c_i$，$b_i$为不下降操作对$i$的增量，$c_i$为不上升的，不难发现答案就是$\sum[b_i<b_{i-1}]+[c_i>c_{i-1}]$。

我们设$f[i][j]$表示已经确定了前$i$个的$b_i$分别为多少，并且$b_i=j$时的最小代价和，然后我们就得到了一个复杂度超级大的dp做法。

仔细观察这个dp，其中藏着性质。

对于同一个$i$，随着$j$的增大$f[i][j]$是不增的，因为$b_i$在增大且$c_i$在减小，所以$f[i][j]$不会变大。

其次就是$f[i][0]\le f[i][a_i]+2$，因为在同一种转移下，$b_i$由$a_i$变成$0$，只可能在$i$处增加$[b_i<b_{i-1}]$的操作，对于$c_i$同理，所以最多增加$2$次操作。

综合这两个性质，对于同一个$i$，$f[i][j]$的取值最多只有三种，记录这三个区间的端点然后转移即可，复杂度$O(n)$。

转移的分讨主要关注于这一组不等式

设$f[i][j]=f[i-1][k]+[j<k]+[a_i-j>a_{i-1}-k]$

$$
\begin{cases}
l\le k\le r\\j\ge k\\j\ge k+a_i-a_{i-1}
\end{cases}
$$
再根据$a_i$与$a_{i-1}$的大小关系转移。

---

## 作者：zifanwang (赞：1)

比较巧的题。

先考虑只有 $1$ 操作时怎么做，显然答案为满足 $1\le i<n\land A_i>A_{i+1}$ 的 $i$ 的个数，即每次选一段尽量长的不降段进行操作。

接下来加上 $2$ 操作，考虑对每个 $i$ 将 $A_i$ 分为 $x_i$ 和 $A_i-x_i$，$x_i$ 用 $1$ 操作，$A_i-x_i$ 用 $2$ 操作，答案即为 $\sum_{i=2}^n [x_i<x_{i-1}]+[A_i-x_i>A_{i-1}-x_{i-1}]$，即 $\sum_{i=2}^n [x_i<x_{i-1}]+[x_i<x_{i-1}+A_i-A_{i-1}]$。容易得到一个比较暴力的 dp：记 $f_{i,j}$ 表示确定 $x_1,x_2,\dots,x_i$，$x_i$ 为 $j$ 的最少代价，有：

$$f_{i,j}=\min_{k=0}^{A_{i-1}}\{f_{i-1,k}+[j<k]+[j<k+A_i-A_{i-1}]\}$$

发现 $[j<k]+[j<k+A_i-A_{i-1}]$ 总共有三种值，对每个 $i$ 把 $f_{i,j}$ 分成了三段，记录前两段的右端点直接转移即可，时间复杂度 $\mathcal O(n)$。

参考代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define mxn 200003
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define rept(i,a,b) for(int i=(a);i<(b);++i)
#define drep(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
int n,ans,a[mxn],f[mxn][2];
signed main(){
	scanf("%d",&n);
	rep(i,1,n)scanf("%d",&a[i]);
	rep(i,1,n){
		if(a[i]>=a[i-1]){
			f[i][0]=f[i-1][0];
			f[i][1]=max(f[i-1][1],f[i-1][0]+a[i]-a[i-1]);
		}else{
			f[i][0]=f[i-1][0]+a[i]-a[i-1];
			f[i][1]=max(f[i-1][0],f[i-1][1]+a[i]-a[i-1]);
			if(f[i][0]<0){
				ans++;
				f[i][0]=f[i][1],f[i][1]=a[i];
			}
		}
		f[i][0]=min(f[i][0],a[i]);
		f[i][1]=min(f[i][1],a[i]);
	}
	cout<<ans+(f[n][0]<a[n]);
	return 0;
}
```

---

## 作者：OldDriverTree (赞：0)

好题。

# Solution

首先如果只有第一种操作 / 第二种操作，那么答案就为 $\sum\limits_{i=1}^{n+1} [a_i<a_{i-1}]$ / $\sum\limits_{i=1}^{n+1} [a_i>a_{i-1}]$。

然后可以发现本题就相当于将 $a_i$ 拆分为 $p_i+q_i$，最小化 $\sum\limits_{i=1}^{n+1} [p_i<p_{i-1}]+\sum\limits_{i=1}^{n+1} [q_i>q_{i-1}]$。然后考虑这样一个暴力 DP，设 $f_{x,y}$ 表示考虑前 $x$ 个数，$p_x=y$ 的答案最小是多少，状态转移方程就为 $f_{x,y}=\min\limits_{i=0}^{a_{x-1}}\{f_{x-1,i}+[y<i]+[a_x-y>a_{x-1}-i]\}$。

但是这样复杂度直接升天，继续挖掘性质。

为了方便观察，我们先移项得到 $f_{x,y}=\min\limits_{i=0}^{a_{x-1}}\{f_{x-1,i}+[y<i]+[y<a_x-a_{x-1}+i]\}$。然后不难发现对于同一个决策 $i$，$y$ 越大答案越小，且极差不超过 $2$，将所有决策的答案取 min 后 $f_{x,y}$ 显然仍然满足这两个性质，且对于 $f_{x,y}$ 相同的一段，最优一定是取 $y$ 最小的那个。

所以我们只需要记录一个 $ans,p,q$ 分别表示 $f_{x,y}$ 的最小值，以及 $ans+1$ 和 $ans$ 最小的位置，形式化来说就是：
$$
f_{x,y}=
\begin{cases}
ans-2&y\in [0,p-1]\\
ans-1&y\in [p,q-1]\\
ans&y\in [q,a_x]\\
\end{cases}
$$
现在的转移方程就为（为了方便，这里令 $\Delta=a_x-a_{x-1}$）：
$$
f_{x,y}=\min
\begin{cases}
ans+2+[y<\Delta]\\
ans+1+[y<p]+[y<\Delta+p]\\
ans+[y<q]+[y<\Delta+q]
\end{cases}
$$

然后考虑如何动态维护 $ans,p,q$，分类讨论：
+ $a_x<q$，$ans$ 显然会加一，此时取不到 $ans+2$，因此 $p=0$。再考虑 $q$，对于第二种转移，$y$ 要满足 $p\le y$，对于第三种转移，因为 $\Delta<0$，所以 $y$ 要满足 $\Delta+q\le y$，因此新的 $q$ 就为 $\min(p,\Delta+q)$，注意这里 $\Delta+q$ 有可能小于 $0$，因此 $q$ 还要和 $0$ 取 max。
+ $q\le a_x<a_{x-1}$，此时 $ans$ 不变，因为 $\Delta<0$，所以和上面同理，$p$ 就为 $\max(\min(p,\Delta+q),0)$。对于 $q$，在第三种转移中需要满足 $y\ge q$，所以 $q$ 不变。
+ $a_{x-1}\le a_x$，此时 $ans$ 不变，$\Delta\ge 0$。然后考虑 $p$，对于第二种转移，要满足 $\Delta+p\le y$，对于第三种转移，要满足 $q\le y$，因此 $p=\min(\Delta+p,q)$。对于 $q$，在第三种转移中需要满足 $y\ge \Delta+q$，因此直接把 $q$ 加上 $\Delta$ 即可。

时间复杂度 $O(n)$。

# Code
```
//when you use vector or deque,pay attention to the size of it.
//by OldDirverTree
#include<bits/stdc++.h>
//#include<atcoder/all>
#define P pair<int,int>
#define int long long
#define mid (l+r>>1)
using namespace std;
//using namespace atcoder;
//using mint=modint998244353;
int n,ans,p,q;

struct custom_hash
{
    static uint64_t splitmix64(uint64_t x) {
        x+=0x9e3779b97f4a7c15;
        x=(x^(x>>30) )*0xbf58476d1ce4e5b9;
        x=(x^(x>>27) )*0x94d049bb133111eb;
        return x^(x>>31);
    }
    size_t operator() (uint64_t x) const {
        static const uint64_t FIXED_RANDOM=chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x+FIXED_RANDOM);
    }
};
int read() {
    int x=0; bool _=true; char c=0;
    while (!isdigit(c) ) _&=(c!='-'),c=getchar();
    while (isdigit(c) ) x=x*10+(c&15),c=getchar();
    return _?x:-x;
}
main()
{
    n=read();
    for (int i=1,lst=0;i<=n+1;i++) {
        int val=i<=n?read():0;
        if (val<q) ans++,q=max(min(p,val-lst+q),0ll),p=0;
        else if (val<lst) p=max(min(p,val-lst+q),0ll);
        else p=min(p+val-lst,q),q+=val-lst; lst=val;
    }
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：Purslane (赞：0)

# Solution

经典的定义域值域交换的套路。

先考虑计算，如果知道每个点**通过操作 $1$ 得到的总权值 $c_i$**，所需要的代价。

可以证明，答案为 $\sum_{i=0}^{n-1} [c_i > c_{i+1}]$，其中 $c_0=0$。

所以我们要拟定 $0 \le c_i \le a_i$ 使得 $\sum_{i=0}^{n} [c_i > c_{i+1}] + [a_i - c_i < a_{i+1} - c_{i+1}]$ 最小（其中 $a_0=a_{n+1}=0$）。

设 $dp_{i,j}$ 表示，钦定 $c_i = j$，前 $i$ 个数的最小代价。

-----

后面的步骤就需要一些小小的观察了。

如果是考场上碰到这个题，大家大概都会暴力 DP 然后打表。很容易观察到两个结论：

1. $dp$ 数组关于第二维不增。原因是，$j$ 越大，第一个艾弗森括号和第二个艾弗森括号都会更小（即，$dp_{i,j}$ 的任何一组方案，都可以构造出 $(i,j+1)$ 的一组解使得其代价 $\le dp_{i,j}$）。
2. $dp$ 数组极差 $\le 2$。原因是，$dp_{i,a_i}$ 的基础上最多修改两个艾弗森括号，就可以得到 $(i,0)$ 的一组解，所以 $dp_{i,0} \ge dp_{i,a_i}$。

> PS：对于最优化问题中的不等式问题的证明（比如，序列的凸性和单调性），可以考虑**构造性证明**。即，如果证明问题 $A$ 的最优解 $f(A)$ 要大于等于问题 $B$ 的最优解 $g(B)$，则只需证明 $A$ 的任何一组方案 $S$ 都可以对应到 $B$ 的一组方案 $T$，使得 $f(S) \ge g(T)$。

这样就可以值域定义域转化。只需要记录 $dp_{i,a_i}$ 的值和两个分界点。

这个东西看起来会有一大堆的分类讨论，不牛。

考虑转移形如

$$
dp_{i,j} = \min_{0 \le k \le a_{i-1}} \{dp_{i-1,k} + [k>j] + [a_{i-1} - k < a_i-j]\}
$$

当后面的艾弗森括号一定时，肯定希望 $k$ 尽量大。所以 $k$ 的取值为 $j$、$a_{i-1} - a_i + j$、$a_{i-1}$。$k$ 是分界点，$j$ 才能是分界点，所以 $j$ 的可能分界点也只有 $O(1)$ 个，把他们拉出来暴力检验即可。

复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=2e5+10;
int n,a[MAXN],dp[MAXN],i1[MAXN],i2[MAXN];
int f(int u,int v) {
	int ans=dp[u];
	if(v>=i1[u]) ans--;
	if(v>=i2[u]) ans--;	
	return ans;
}
int calc(int u,int v) {
	int ans=INT_MAX;
	if(v<=a[u-1]) ans=min(ans,f(u-1,v)+(a[u-1]-v<a[u]-v));
	if(a[u-1]-a[u]+v>=0) ans=min(ans,f(u-1,a[u-1]-a[u]+v)+(a[u-1]>a[u]));
	ans=min(ans,f(u-1,a[u-1])+(a[u-1]>v)+(0<a[u]-v));
	return ans;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n;
	int ans1=0,ans2=0;
	ffor(i,1,n) cin>>a[i];
	ffor(i,1,n-1) ans1+=(a[i]>a[i+1]),ans2+=(a[i]<a[i+1]);
	n++;
	dp[0]=0,i1[0]=i2[0]=2000000000;
	ffor(i,1,n) {
		set<int> pos;
		if(a[i-1]<=a[i]) pos.insert(a[i-1]);
		pos.insert(a[i]),pos.insert(a[i]-1);
		if(i1[i-1]!=2000000000) {
			if(i1[i-1]<=a[i]) pos.insert(i1[i-1]);
			if(-a[i-1]+a[i]+i1[i-1]>=0) pos.insert(-a[i-1]+a[i]+i1[i-1]);
		}
		if(i2[i-1]!=2000000000) {
			if(i2[i-1]<=a[i]) pos.insert(i2[i-1]);
			if(-a[i-1]+a[i]+i2[i-1]>=0) pos.insert(-a[i-1]+a[i]+i2[i-1]);
		}
		if(a[i]>=a[i-1]) pos.insert(a[i]-a[i-1]);
		pos.insert(0);
		dp[i]=calc(i,0);
		i1[i]=i2[i]=2000000000;
		pos.erase(0);
		int lstval=dp[i];
		for(auto v:pos) {
			int nval=calc(i,v);
			if(nval<lstval) {
				if(nval==lstval-2) i1[i]=i2[i]=v;
				else if(i1[i]==2000000000) i1[i]=v;
				else i2[i]=v;
			}
			lstval=nval;
		}
	}
	cout<<min({ans1+1,ans2+1,f(n,a[n])});
	return 0;
}
```

---

## 作者：Mortidesperatslav (赞：0)

很抽象的题目。

可以发现单独一个操作非常好做，如果只有第一个操作，答案为序列的极长上升字段个数，如果只有第二个操作同理。

于是考虑对于每个 $a_i$，把贡献拆成两部分 $a_i=pre_i+suf_i$，分别为操作 $1$ 和操作 $2$ 的贡献。

考虑用 $f_{i,j}$ 表示处理到第 $i$ 个元素，且 $suf_i=j$。

如何转移呢？肯定是从 $f_{i-1,k}$（$0 \leq k \leq a_{i-1}$）转移过来。

可以发现 $f_{i,j}$ 为 $f_{i-1,k}+[j>k]+[a_{i-1}-k>a_i-j]$ 的最小值。

为什么呢？因为一操作不降，二操作不增，推一下就出来了。

现在问题在于，这个 dp 方程是 $O(nV)$ 的，过不了一点。

优化是比较抽象的。考虑以下几个性质。

### 性质 1

$f_{i,j+x}\ge f_{i,j}$（$0 \leq j \leq j+x \leq a_i$）。

证明：要使得 $j \leq k$，一定要 $j$ 更小；要使得 $a_{i}-j \geq a_{i-1}-k$，还是要 $j$ 更小。所以 $j$ 小答案肯定会小。

### 性质 2

$f_{i,a_i} - f_{i,0} \leq 2$。

最多只有两个状态可以满足。所以差值最多为 $2$。

既然这样，我们自然而然就可以想到用 $f_{i,0}$ 和 $f_{i,1}$ 来表示从前一个状态推过来 $+0$ 和 $+1$ 的 $j$ 最大值（$f_{i,2}$ 不用维护，因为一定是 $a_i$）。

这样 dp 就可以了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, a[1000005], ans, f[1000005][2];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	for (int i = 1; i <= n; i++){
		f[i][0] = f[i - 1][0];
		f[i][1] = f[i - 1][1];
		if (a[i] >= a[i - 1])
			f[i][1] = max(f[i][1], f[i][0] + a[i] - a[i - 1]);
		else{
			f[i][1] = max(f[i][0], f[i][1] + a[i] - a[i - 1]);
			f[i][0] = f[i][0] + a[i] - a[i - 1];
			if (f[i][0] < 0){
				ans++;
				f[i][0] = f[i][1];
				f[i][1] = a[i];
			}
		}
		if (f[i][0] > a[i])
			f[i][0] = a[i];
		if (f[i][1] > a[i])
			f[i][1] = a[i];
	}
	if (f[n][0] < a[n])
		cout << ans + 1;
	else
		cout << ans;
	return 0;
}
```

---

## 作者：Wu_Qi_Tengteng (赞：0)

由于序列中的数可以取 $0$，那么其实就相当于把序列上的一段加上一个正整数不下降序列或者不上升序列。

我们发现一个很巧妙的东西，如果只有一个操作，那么答案显然就是这个序列的极长不下降子段或者极长不下降子段的数量。

证明：我们发现，最优的操形式一定可以转化为加上若干个不相交且互相之间不能连成一段的操作的形式且并不会使操作数变多。那么这个显然就是将原序列用极长不下降子段拼起来了。

现在考虑两种操作，由于加法运算律，我们可以将一个 $a_i$ 拆成两个部分，一部分拿去第一个操作，一部分拿去第二个操作。这样就可以分开算贡献。

可以考虑 $dp $。设 $f_{i,j}$ 表示考虑了 $[1,i]$,第 $i$ 个分出了 $j$ 给不下降序列，剩下 $a_i-j$ 给不上升序列。

$$
f_{i,j}=\min_{k=0}^{a_{i-1}} f_{i-1,k}+[j<k]+[j<a_i-a_{i-1}+k]
$$

我们发现在确定了 $k$ 的情况下，$j$ 越大显然越优。那么对于所有的 $k$ 来说都是这样的，所以 $i$不变， $j$ 越大 $f_{i,j}$ 越小。

并且我们发现 $f_{i,0}\le f_{i,a_i}+2$。如果他大于 $f_{i,a_i}+2$,那么我们显然可以取转移到 $f_{i,a_i}$ 的 $k$ 作为上一个位置的值，并且使答案最多为 $f_{i,a_i}+2$。

那么我们就可以将这个序列直接划分为三个部分。分别是为 $f_{i,a_i}-2$，$f_{i,a_i}-1$，$f_{i,a_i}$ 的部分。

设三个区间分别为 $[0,p]$，$[p+1,q]$，$[q+1,a_{i-1}]$，最小值为 $d$ （$-1\le p\le q<a_{i-1}$）。我们发现，转移的时候只会从区间的最左端点转移。因为点越靠右。满足小于他的 $j$ 的数量就会越多。

所以可以得到转移式子。
$$
f_{i,j}=\min\begin{cases}
  & \text d+2+[j<0]+[j<a_i-a_{i-1}]\\
  & \text d+1+[j<p+1]+[j<a_i-a_{i-1}+p+1]\\
  & \text d+[j<q+1]+[j<a_i-a_{i-1}+q+1]\\
\end{cases}
$$
我们设 $\Delta=a_i-a_{i-1}$，我们可以来分类讨论一下。这里设 $p',q'$ 表示转移之后新的两个分界点。

当 $\Delta \ge 0$ 的时候:
$[0,\Delta -1]$ 可以取到 $d+3$，$[\Delta,a_i]$ 可以取到 $d+2$。

$[0,p]$ 可以取到 $d+3$，$[p+1,p+\Delta]$ 可以取到 $d+2$， $[p+\Delta+1,a_i]$ 可以取到 $d+1$。

$[0,q]$ 可以取到 $d+2$，$[q+1,q+\Delta]$ 可以取到 $d+1$， $[q+\Delta+1,a_i]$ 可以取到 $d$。

我们知道 $q+\Delta +1 \le a_i$，所以有 $p’=\min(p+\Delta,q),q'=q+\Delta$, $d$ 不变。

当 $\Delta < 0$ 的时候：
$[0,a_i]$ 可以取到 $d+2$。

$[0, p+\Delta]$ 可以取到 $d+3$，$[p+\Delta+1,p]$ 可以取到 $d+2$， $[p+1,a_i]$ 可以取到 $d+1$。

$[0,q+\Delta]$ 可以取到 $d+2$，$[q+\Delta+1,q]$ 可以取到 $d+1$，$[q+1,a_i]$ 可以取到 $d$。

如果 $q\ge a_i$ ,那么 $d'=d+1,p'=-1,q=\max(\min(p,q+\Delta),-1)$。

否则 $d'=d,p'=\max(\min(p,q+\Delta),-1),q=q$。

时间复杂度 $\mathcal{O}(n)$ 。

```c++
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();} 
	return x*f;
}
const int N=2e5+10;
int n,a[N],p=-1,q=-1,d; 
signed main(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n+1;i++){
		int Delta=a[i]-a[i-1];
		if(Delta>=0){
			p=min(p+Delta,q);
			q=q+Delta;
		}else{
			if(q<a[i]){
				p=max(min(p,q+Delta),-1ll);
			}else{
				q=max(min(p,q+Delta),-1ll);
				p=-1;
				d++;
			}
		}
	}
	printf("%lld\n",d);
	return 0;
} 
```

---

