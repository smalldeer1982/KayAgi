# [ARC190E] Gaps of 1 or 2

## 题目描述

给定一个长度为 N 的非负整数序列 $A=(A_1,…,A_N)$，需要回答 $Q$ 个查询。

对于第 $i$ 个查询，给定满足 $1≤L_i≤R_i≤N$ 的整数 $L_i$和 $ R_i$，考虑长度为 $R_i−L_i+1$ 的子序列 $B=(A_{L_i},…,A_{R_i}$)。
对于子序列 $B$，考虑重复执行以下操作：
1. 选择满足 $1≤i,j≤∣B∣$ 且 $1≤B_i,B_j$且$1≤j−i≤2$的整数 $i$ 和 $j$。
2. 从 $B_i$ 和 $B_j$ 中各减去 $1$。

求出可以执行操作的最大次数。

## 说明/提示

$
1≤N≤200000\\
1≤Q≤200000\\
0≤A_i≤10^9\\
1≤L_i≤R_i≤N\\
$
所有输入值均为整数。

## 样例 #1

### 输入

```
6 1
1 1 4 0 3 2
1 6```

### 输出

```
5```

## 样例 #2

### 输入

```
6 6
49 83 10 77 21 62
1 1
1 2
1 3
3 5
1 6
5 6```

### 输出

```
0
49
59
31
151
21```

# 题解

## 作者：Hanghang (赞：11)

一个全新的领域！

众所周知，二分图最大匹配为：$|V_{L}|-\max_{S\in V_L}(|S|-|N(S)|)$，霍尔定理推论。

霍尔定理相关题目已经出了很多很多，诞生了许多好题。

聪明的出题人一定不会满足于此，走向全新的领域：一般图！

一般图最大匹配为：$\frac{1}{2} (|V|-\max_{S\in V}(O(V-S)-|S|))$，其中 $O(V-S)$ 表示把图扣去集合 $S$ 中的点之后大小为奇数的连通块个数，在学术上被称作：Tutte-Berge Formula。证明部分略去，有兴趣自行了解（我还不太会，待学习）

言归正传，那么本题先可以简单得建立出一般图最大匹配模型：两个距离小于等于 $2$ 的点之间连一条边，保留区间中的所有点，跑最大匹配。

那么我们现在只用考虑求 $\max_{S\in V}O(V-S)-|S|$。

注意到这里是带权的最大匹配（每个点包含了 $a_i$ 个点），可以发现一个点要么全部选入 $S$，要么全没有选入 $S$，具体而言，假设最终 $S$ 中选了 $0< x <a_i$ 个点，那么调整成选 $x-1$ 个点一定不劣。

不妨设 $d_i=1/0$ 表示下标 $i$ 的所有点选/没选入 $S$，考虑设计 $dp$ 转移。

不妨设区间长度为 $m$，以及 $d_0=d_{m+1}=1$，方便处理边界。

首先答案为奇 $0$ 连通块个数减去所有 $1$ 的带权和，当然会有细节需要你考虑。

当一个 $0$ 形成一个独立连通块时，贡献为 $a_i$ 并非 $1$（每个点都是孤立的）

$000100$ 出现时即中间只有一个 $1$ 间断两边的 $0$ 其实是一个连通块，这种情况是烦人的，但是你直接钦定全局不能出现这种情况即可（有支配性：不如把 $1$ 改为 $0$，可调整证明）

$a_i=0$ 的时候是不能选 $d_i=1$ 的，但是 $d_i=0$ 不劣于 $d_i=1$ 的，所以不需要特殊处理。

然后就可以 $dp$ 转移了，设 $f_{i,0/1/2/3/4}$ 表示当前考虑了 $1\sim i$，$i$ 号点当前状态为：单独的一个 $1$，在多个 $1$ 的连通块内，单独的一个 $0$，在多个 $0$ 的联通块内且当前连通块大小为偶数/奇数。

列出矩阵 （max+）做转移即可，细节看代码。

复杂度 $O((n+q\log)K^3)$，$K$ 为矩阵大小，本题还能支持单点修改。

一道很牛牛的题，感觉这个结论扩展性极强，期待下一次遇见。

```cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll N=2e5+3,K=5,INF=1e18;
ll n,m,a[N],sa[N];
void Max(ll &x,ll y){if(x<y)x=y;}
struct Mat
{
	array<ll,K>f[K];
	auto& operator[](int x){return f[x];}
	void Clear(){memset(f,0xcf,sizeof(f));}
	friend Mat operator *(Mat A,Mat B)
	{
		Mat C;C.Clear();
		for(int i=0;i<K;i++)for(int k=0;k<K;k++)for(int j=0;j<K;j++)
			Max(C[i][j],A[i][k]+B[k][j]);
		return C;
	}
}I;
void Init(){for(int i=0;i<K;i++)for(int j=0;j<K;j++)I[i][j]=i==j?0:-INF;}
Mat Get(ll v)
{
	Mat A;
	if(v%2==0)
	{
		A[0]={-INF,-v,-INF,-INF,-INF};
		A[1]={-INF,-v,v,0,-INF};
		A[2]={-v,-INF,-INF,-INF,-INF};
		A[3]={-v,-INF,-INF,0,-INF};
		A[4]={-v,-INF,-INF,-INF,0};
	}
	else
	{
		A[0]={-INF,-v,-INF,-INF,-INF};
		A[1]={-INF,-v,v,-INF,1};
		A[2]={-v,-INF,-INF,-INF,-INF};
		A[3]={-v,-INF,-INF,-INF,1};
		A[4]={-v,-INF,-INF,-1,-INF};
	}
	return A;
}
struct SGT
{
	int DT;Mat tr[1<<19|3];
	void Up(int p){tr[p]=tr[p<<1]*tr[p<<1|1];}
	void Build()
	{
		DT=1<<(__lg(n)+1);
		for(int i=1;i<=n;i++)tr[i+DT]=Get(a[i]);
		for(int i=DT-1;i;i--)Up(i);
	}
	Mat Ask(int l,int r)
	{
		Mat sl=I,sr=I;
		for(l+=DT-1,r+=DT+1;l+1!=r;l>>=1,r>>=1)
		{
			if(~l&1)sl=sl*tr[l+1];
			if(r&1)sr=tr[r-1]*sr;
		}
		return sl*sr;
	}
}T;
int main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m;Init(); 
	for(int i=1;i<=n;i++)cin>>a[i],sa[i]=sa[i-1]+a[i];
	T.Build();
	for(int i=1,l,r;i<=m;i++)
	{
		cin>>l>>r;Mat t=T.Ask(l,r);
		ll ans=*max_element(t[1].begin(),t[1].end());
		cout<<(sa[r]-sa[l-1]-ans)/2<<"\n";
	}
}
```

---

## 作者：xxxxxzy (赞：3)

相当精巧的题目，反正我肯定做不起，写篇学习笔记。

首先我们考虑把 $|i-j| \le 2$ 的点可以消除一对这个过程视作 $i,j$ 进行匹配。

记 $o(V)$ 表示 $V$ 的奇连通块个数。

由 Tutte-Berge Formula 公式得到：一般图 $G=(V,E)$ 的最大匹配数为 $\dfrac{1}{2}\min\limits_{S \subseteq  V} {(|V| + |S| -o(V \setminus  S))} = \dfrac{1}{2}(|V|-\max\limits_{S \subseteq  V} { (-|S| +o(V \setminus  S))})$。

接下来只需要考虑计算 $\max\limits_{S \subseteq  V} { (o(V \setminus  S)-|S|)}$。

这张图是带权的，每个点都由 $a_i$ 个点组成，可以发现结论：对于任意的 $i$，最优方案只存在于将 $a_i$ 个点全部加入 $S$ 集合，或者全部不加入。

证明：假设第 $i$ 个点里面有 $x(1\le x<a_i)$ 个小点加入，那么我们可以将 $x$ 变为 $x-1$，因为并未改变 $i$ 与其他点的连通性，所以 $o(V \setminus  S)$ 最多变化 $\pm 1$，而 $-|S|$ 会增加一，所以 $\max\limits_{S \subseteq  V} { (o(V \setminus  S)-|S|)}$ 是单掉不降的。

而 $x=a_i$ 的时候连通性会改变，所以是另一种选择方案。

我们设 $s_i=0/1$ 代表第 $i$ 个点全部不选入/选入 $S$，要求的信息就为奇连通 $0$ 块的数量减去 $1$ 所有位置的权值和。

我们注意到，两个 $0$ 夹一个 $1$ 的情况是非常不方便处理的，我们考虑避免这种情况。可以发现，把 $1$ 改成 $0$ 是一定不会变劣的：

证明：跟上面相似，我们考虑把 $1$ 替换成 $0$，表示奇数连通块为 $O$，偶数为 $E$，合并了左右两个连通块，讨论 $O|O,O|E,E|O,E|E$ 四种情况后发现，$o(V \setminus  S)$ 最多变化 $\pm 1$，而 $-|S|$ 的增幅必定 $\ge 1$，所以替换一定更优。

还有一个细节，就是关于 $a_i=0$ 的处理。可以发现，把 $a_i=0$ 的地方，选 $s_i=0$ 不劣于 $s_i=1$。

证明：$s_i=0/1$ 对答案造成的影响产生于 $i$ 左右两边 $0$ 连通块的合并，换句话说 $s_i=0/1$ 会产生贡献当且仅当 $i-1$ 与 $i+1$ 都是 $0$，在这个条件下，$i-1$ 与 $i+1$ 是一个连通块，所以说 $i$ 的合并是无效的。

接着就可以直接动态 dp 了：

我们设 $f_{01/11/110/00/00'}$，五种状态（后简写为 0/1/2/3/4）分别表示结尾为 $01$，$11$，$110$，$00$ 且连通块大小为偶数，$00$ 且连通块大小为偶数。

列出矩阵，注意要 $a_i$ 奇数和偶数分类讨论，这里的矩阵乘法是 (max,+) 的广义矩阵乘法：

$
\begin{bmatrix}f_{0} & f_{1} & f_{2} & f_{3} & f_{4} \end{bmatrix}
\begin{bmatrix}-\infty & -a_i & -\infty & -\infty & -\infty \\ -\infty & -a_i & a_i & 0 & -\infty \\ -a_i & -\infty & -\infty & -\infty & -\infty \\ -a_i & -\infty & -\infty & 0 & -\infty \\ -a_i & -\infty & -\infty & -\infty & 0\end{bmatrix}
=\begin{bmatrix}f_{0}' & f_{1}' & f_{2}' & f_{3}' & f_{4}' \end{bmatrix}
(a_i \mod 2 \equiv  0)
$

$
\begin{bmatrix}f_{0} & f_{1} & f_{2} & f_{3} & f_{4} \end{bmatrix}
\begin{bmatrix}-\infty & -a_i & -\infty & -\infty & -\infty \\ -\infty & -a_i & a_i & -\infty & 1 \\ -a_i & -\infty & -\infty & -\infty & -\infty \\ -a_i & -\infty & -\infty & -\infty & 1 \\ -a_i & -\infty & -\infty & -1 & -\infty\end{bmatrix}
=\begin{bmatrix}f_{0}' & f_{1}' & f_{2}' & f_{3}' & f_{4}' \end{bmatrix}
(a_i \mod 2 \equiv  1)
$

总复杂度 $O(k^3 n \log n)$，这里默认 $n,q$ 同阶。

---

## 作者：masterhuang (赞：2)

目前两篇题解各有一些比较含糊的地方，我融合了一下。

---

一般图最大匹配有个类似 **Hall** 定理的结论。

定义 $o(V)$ 表示子图 $V$ 中连通块大小为 **奇数** 的连通块个数。

对于图 $G(V,E)$，最大匹配能如下表示：

$$
\dfrac{1}{2}\left(|V|-\max\limits_{S\sube V} (o(V\backslash S)-|S|)\right)
$$

被称作 [Tutte–Berge 公式
](https://www.cnblogs.com/ldxcaicai/p/12565005.html)。

发现形式和 **tuttle** 矩阵很像，于是证明大概是 **tuttle** 矩阵那套，但是我不太会，可以查看上述链接。

---

先做全局，建立图论模型：把一个点拆成 $a_i$ 个点，然后距离 $\le 2$ 的所有连边，答案是最大匹配。

套用结论，分析 $S$。

发现对于一个 $i$，看着 $a_i$ 要么全在 $S$，要么全不在。

> 证明是若选了 $1\le x<a_i$ 个在 $S$ 中，少掉一个能使 $-|S|$ 增加 $1$。
>
> 并且 $o(V\backslash S)$ 最多减少 $1$，于是选 $x-1$ 个一定不劣。
>
> 若 $x=a_i$ 则 $x-1$ 会影响连通性，对 $o(V\backslash S)$ 的影响就不一定了。

于是我们考虑 $01$ 序列 $s$，$s_i=0/1$ 表示位置 $i$ 全不选或全选。

则答案为奇 $0$ 连通块个数减所有 $1$ 位置的 $a$ 的和，要找这个的 $\max$。

---

发现可以设计 **dp**。请注意我下面当前和钦定的用词。

设第 $i$ 位的状态 $f_{i,0/1/2/3/4}$ 分别是：

- 当前单 $1$

- 当前多 $1$

- 钦定单 $0$

- 钦定多 $0$，$0$ 连通块的 $\sum a_i$ 为偶数

- 钦定多 $0$，$0$ 连通块的 $\sum a_i$ 为奇数


当前单 $1$ 能转移到当前多 $1$，但是钦定单 $0$ 无法转移到钦定多 $0$。

这是为了算贡献方便。

---

- 你发现此时把单 $1$ 转移到钦定 $0$ 的情况比较麻烦，你还要记 $1$ 前面那个 $0$ 的连通块的奇偶性。

  因为 $010$ 这样第二个 $0$ 能跨过去转移，还要多记信息。

你发现不如把它变成 $000$。

> 因为 $-|S|$ 增加 $a_i$，奇连通块个数最多减少 $1$ 个。
>
> 若 $a_i=0$，则奇无法拆成两个偶，于是恰好减少 $0$ 个。
>
> 否则 $a_i\ge 1$，一定不劣。


---

于是你就可以设计转移矩阵了，矩阵乘法是 $(\max,+)$，转移要分 $a_i$ 奇偶讨论。

若 $2\mid a_i$：

$[f_0 , f_1 , f_2 , f_3 , f_4]\begin{bmatrix} -\infty & -a_i & -\infty & -\infty & -\infty \\ -\infty & -a_i & a_i & 0 & -\infty \\ -a_i & -\infty & -\infty & -\infty & -\infty \\ -a_i & -\infty & -\infty & 0 & -\infty \\ -a_i & -\infty & -\infty & -\infty & 0 \end{bmatrix} = [f'_0 , f'_1 , f'_2 , f'_3 , f'_4]$

---

若 $2\nmid a_i$：

$[f_0 , f_1 , f_2 , f_3 , f_4] \begin{bmatrix} -\infty & -a_i & -\infty & -\infty & -\infty \\ -\infty & -a_i & a_i & -\infty & 1 \\ -a_i & -\infty & -\infty & -\infty & -\infty \\ -a_i & -\infty & -\infty & -\infty & 1 \\ -a_i & -\infty & -1 & -\infty & -\infty \end{bmatrix} = [f'_0 , f'_1 , f'_2 , f'_3 , f'_4]$

---

初始钦定 $l$ 左边有 $\infty$ 个 $1$，不影响答案。

于是初始 $f=[-\infty,0,-\infty,-\infty,-\infty]$。

线段树维护区间矩阵乘积，总复杂度 $\mathcal{O}(k^3 (n+q \log n))$。

但是发现查询的时候只需维护向量乘矩阵，于是复杂度变成 $\mathcal{O}(nk^3+qk^2 \log n)$。

代码跑挺快的。

[$\bf{record}$](https://atcoder.jp/contests/arc190/submissions/68450597)

---

