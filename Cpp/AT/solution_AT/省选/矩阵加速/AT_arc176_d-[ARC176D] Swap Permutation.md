# [ARC176D] Swap Permutation

## 题目描述

给定一个 $ (1,2,\dots,N) $ 的排列 $ P=(P_1,P_2,\dots,P_N) $。接下来要进行 $ M $ 次如下操作：

- 选择满足 $ 1\le i<j\le N $ 的整数对 $ (i,j) $，交换 $ P_i $ 和 $ P_j $。

操作序列共有 $ \left(\frac{N(N-1)}{2}\right)^M $ 种。请你求出所有操作序列结束后 $ \sum_{i=1}^{N-1} |P_i - P_{i+1}| $ 的总和对 $ 998244353 $ 取模的结果。

## 说明/提示

## 限制条件

- $ 2\le N\le 2\times 10^5 $
- $ 1\le M\le 2\times 10^5 $
- $ (P_1,P_2,\dots,P_N) $ 是 $ (1,2,\dots,N) $ 的一个排列

## 样例解释 1

所有可能的操作序列如下共 $ 3 $ 种：

- 选择 $ (i,j) = (1,2) $，$ P=(3,1,2) $。
- 选择 $ (i,j) = (1,3) $，$ P=(2,3,1) $。
- 选择 $ (i,j) = (2,3) $，$ P=(1,2,3) $。

对应的 $ \sum_{i=1}^{N-1} |P_i - P_{i+1}| $ 分别为 $ 3,3,2 $。因此答案为 $ 3+3+2=8 $。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3 1
1 3 2```

### 输出

```
8```

## 样例 #2

### 输入

```
2 5
2 1```

### 输出

```
1```

## 样例 #3

### 输入

```
5 2
3 5 1 4 2```

### 输出

```
833```

## 样例 #4

### 输入

```
20 24
14 1 20 6 11 3 19 2 7 10 9 18 13 12 17 8 15 5 4 16```

### 输出

```
203984325```

# 题解

## 作者：Hanghang (赞：17)

## [[ARC176D] Swap Permutation](https://www.luogu.com.cn/problem/AT_arc176_d)

介绍一种这类题目通用的解法。

对于任意两个位置 $A,B$，其他的值最终到达这里的概率都是相等的，不妨设它为 $C$，那么最终对应位置的情况只有 $7$ 种：$(A,B),(B,A),(C,B),(B,C),(A,C),(C,A),(C,C)$。

考虑对换两个数之后变化的方案数，构造矩阵：
$$
M=\begin{bmatrix}
\binom{n-2}{2} & 1 & n-2 & 0 & n-2 & 0 & 0\\
1 & \binom{n-2}{2} & 0 & n-2 & 0 & n-2 & 0\\
1 & 0 & \binom{n-2}{2}+n-3 & 1 & 0 & 1 & n-3 \\
0 & 1 &  1 & \binom{n-2}{2}+n-3 & 1 & 0 & n-3\\
1 & 0 & 0 & 1 &\binom{n-2}{2}+n-3 & 1 & n-3\\
0 & 1 & 1 & 0 & 1 &\binom{n-2}{2}+n-3 & n-3\\
0 & 0 & 1 & 1 & 1 & 1 &\binom{n-2}{2}+2(n-4)+1
\end{bmatrix}
$$
其中矩阵第 $i$ 行第 $j$ 列恰好对应着从第 $i$ 种情况通过一次对换走到第 $j$ 种情况的方案数。

那么：
$$
e\times M^k=f
$$
$f,e$ 分别代表是一个长度为 $7$ 的行向量，$e$ 中只有第 $1$ 个位置为 $1$，其余都是 $0$（初始排列中恰好为第 $1$ 种情况），$f$ 中的第 $i$ 个位置表示经过 $k$ 次对换后的变成第 $i$ 种情况的方案数。

可以使用矩阵快速幂在 $O(T^3\log m)$ 的时间求得 $f$，$T$ 为矩阵大小 $7$，由于 $k$ 一般情况下不可能开得非常大（超过 $10^{18}$ 级别），所以这部分的计算时间往往可以忽略不记。

现在考虑每种情况对应的贡献。

在此题中，我们只需要考虑相邻点对的贡献，一共只有 $n$ 对，直接一个个处理即可（其他的一些题目不一定只有 $n$ 对，方法往往是枚举右边的值然后处理所有的贡献）。

设当前在处理 $(i,i+1)$ 这一点对，值分别为 $a_i,a_{i+1}$。

$(A,B),(B,A)$ 的贡献分别为：
$$
f_1\times |a_i-a_{i+1}|\\f_2\times |a_i-a_{i+1}|
$$
设 $sum_x=\displaystyle\sum_{i=1}^{n}|i-x|$。

$(C,B),(B,C)$ 的贡献分别为：
$$
\dfrac{f_3\times (sum_{a_{i+1}}-|a_i-a_{i+1}|)}{n-2}\\\dfrac{f_4\times (sum_{a_{i+1}}-|a_i-a_{i+1}|)}{n-2}
$$
即点对中的一个值是固定的，另一个值可以是除了 $A$ 中的所有数，每个数都是等概率的，所有直接求和再除以 $n-2$ 即可。

$(A,C),(C,A)$ 的贡献同理，分别为：
$$
\dfrac{f_5\times (sum_{a_{i}}-|a_i-a_{i+1}|)}{n-2}\\\dfrac{f_6\times (sum_{a_{i}}-|a_i-a_{i+1}|)}{n-2}
$$
最后考虑 $(C,C)$ 的贡献，还是因为等概率，贡献应是两个数不为 $A,B$ 的所有可能求和除以 $(n-2)(n-3)$。

设 $sx=\displaystyle\sum_{i=1}^{n}sum_i$，那么贡献为：
$$
\dfrac{f_7\times (sx-2(sum_{a_i}-sum_{a_{i+1}}-|a_i-a_{i+1}|)}{(n-2)(n-3)}
$$
把所有贡献加起来即为答案。

复杂度 $O(n+T^3\log m)$。

类似题目：[P4223 期望逆序对](https://www.luogu.com.cn/problem/P4223)（本题思路借鉴了 $\text{Yukikaze\_}$ 的题解）。

代码（$f$ 数组的下标有一些小小的改变）：

```cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll N=2e5+3,H=998244353;
ll Ksm(ll x,ll y)
{
	ll s=1;
	for(ll i=1;i<=y;i<<=1,x=x*x%H)if(i&y)s=s*x%H;
	return s;
}
struct Mat
{
	ll mat[7][7];
	void Clear(){memset(mat,0,sizeof(mat));}
	friend Mat operator *(Mat A,Mat B)
	{
		Mat C;C.Clear();
		for(int i=0;i<=6;i++)for(int j=0;j<=6;j++)for(int k=0;k<=6;k++)
		    C.mat[i][j]=(C.mat[i][j]+A.mat[i][k]*B.mat[k][j])%H;
		return C;
	}
}bas,res;
ll n,m,a[N],sum[N];
ll C2(ll x){return x*(x-1)/2%H;}
ll S(ll l,ll r){return l>r?0:(l+r)*(r-l+1)/2;}
void Init()
{
	res.mat[0][0]=1;
	bas=(Mat){{
    {C2(n-2),1,n-2,0,n-2,0,0},
	{1,C2(n-2),0,n-2,0,n-2,0},
	{1,0,(C2(n-2)+(n-3))%H,1,0,1,n-3},
	{0,1,1,(C2(n-2)+(n-3))%H,1,0,n-3},
	{1,0,0,1,(C2(n-2)+(n-3))%H,1,n-3},
	{0,1,1,0,1,(C2(n-2)+(n-3))%H,n-3},
	{0,0,1,1,1,1,(C2(n-2)+2*(n-4)+1)%H}
    }};
}
int main()
{
	cin>>n>>m;Init();ll sx=0;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(ll i=1;i<=n;i++)sum[i]=((i-1)*i-S(1,i-1)+S(i+1,n)-(n-i)*i)%H,sx=(sx+sum[i])%H;
	for(ll i=1;i<=m;i<<=1,bas=bas*bas)if(i&m)res=res*bas;
	ll *f=res.mat[0],ans=0,ivn2=Ksm(n-2,H-2),ivn3=Ksm((n-2)*(n-3)%H,H-2);
	for(int i=1;i<n;i++)
	{
		ll dt=abs(a[i+1]-a[i]),ka=sum[a[i]],kb=sum[a[i+1]];
		ans=(ans+(f[0]+f[1])*dt)%H;
		ans=(ans+(f[2]+f[3])*(kb-dt+H)%H*ivn2)%H;
		ans=(ans+(f[4]+f[5])*(ka-dt+H)%H*ivn2)%H;
		ans=(ans+f[6]*(sx+(-ka-kb+dt+2*H)*2)%H*ivn3)%H;
	}
	cout<<ans;
}
```

---

## 作者：Eraine (赞：7)

编号：AT_arc176_d

tag：计数（切糕模型），矩阵加速

难度：*2572

感谢 @Cbrx 保送爷的指导，让蒟蒻认识到自己的愚蠢。做了那么多切糕问题还是不会，唐 =(

把 $\mid P_i-P_{i+1}\mid$ 看做若干个 $1$ 相加，即在 $(\min(P_i,P_{i+1}),\max(P_i,P_{i+1})]$ 区间上的数对答案全部贡献 $1$，那么可以枚举阈值 $\text{limit}$，判断一个数是否大于 $\text{limit}$ 而构成 $01$ 序列。在 $[1,n-1]$ 上的 $n-1$ 个阈值构成 $n-1$ 个长度为 $n$ 的 $01$ 序列。

考虑一个 $01$ 串如何对答案产生贡献。很容易想到当且仅当出现连续的 $01$ 或 $10$ 时对答案贡献 $1$。

计算对于每个 $\text{limit}$，每个位置上对答案的贡献，发现到现在我们只关心原先的序列位置上 $0$ 和 $1$ 的情况和整个序列 $0$ 的个数和 $1$ 的个数，而后两个信息在枚举阈值时即可获得，前两个信息发现本质不同的情况只有三种（即 $00,01,11$），很容易在从小到大遍历阈值的情况均摊 $\Theta(1)$ 处理三个情况数之和。至于要交换 $m$ 轮，把 DP 式子推出来后发现对于 $m$ 轮的方程都是一样的，所以矩阵加速即可。

$\Theta(n\log m)$。

[submission](https://atcoder.jp/contests/arc176/submissions/52774194)

若有误请指出。虚心接受您的意见。

---

## 作者：DaiRuiChen007 (赞：6)

[Problem Link](https://www.luogu.com.cn/problem/AT_arc176_d)

**题目大意**

> 给定 $n$ 阶排列 $p_1\sim p_n$，$m$ 次操作选择 $1\le i<j\le n$ 并交换 $p_i,p_j$。
>
> 求最终每个排列的 $\sum_{i=1}^{n-1}|p_i-p_{i+1}|$ 之和。
>
> 数据范围：$n,m\le 2\times 10^5$。

**思路分析**

考虑如何刻画最终一个排列的权值，考虑 01 序列，设 $q_{x,i}=[p_i>x]$，那么最终一个排列的权值就是 $\sum_{x,i}[q_{x,i}\ne q_{x,i+1}]$，这是显然的因为这样的 $x$ 恰有 $|p_i-p_{i+1}|$ 个。

那么我们对于每个 01 序列，选定 $q_{i},q_{i+1}$ 观察 $m$ 次交换后有多少种方案使得其变成 $(0,1)$。

考虑 dp，那么状态为 $f_{i,s}$，其中 $i$ 是操作次数，$s$ 是当前状态，只有 $(0,0),(1,1)$ 和 $(0,1)/(1,0)$ 三种，转移也是简单的。

那么我们可以用 $3\times 3$ 矩阵加速转移，快速算出每种 $(q_i,q_{i+1})$ 对答案的贡献，至于每种 $q_i$ 有多少对可以简单统计。

时间复杂度 $\mathcal O(n\log m)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=2e5+5,MOD=998244353;
typedef array<array<ll,3>,3> mat;
mat operator *(mat u,mat v) {
	mat w={{{0,0,0},{0,0,0},{0,0,0}}};
	for(int k:{0,1,2}) for(int i:{0,1,2}) for(int j:{0,1,2}) {
		w[i][j]+=u[i][k]*v[k][j];
	}
	for(int i:{0,1,2}) for(int j:{0,1,2}) w[i][j]%=MOD;
	return w;
}
mat ksm(mat a,int b) {
	mat ret={{{1,0,0},{0,1,0},{0,0,1}}};
	for(;b;a=a*a,b>>=1) if(b&1) ret=ret*a;
	return ret;
}
int n,m,a[MAXN],p[MAXN];
signed main() {
	scanf("%d%d",&n,&m);
	ll k=1ll*n*(n-1)/2,ans=0;
	for(int i=1;i<=n;++i) scanf("%d",&a[i]),p[a[i]]=i;
	mat S{{{0,0,n-1},{0,0,0},{0,0,0}}};
	for(int i=1;i<n;++i) { //i*0,n-i*1
		if(p[i]>1) ++S[0][a[p[i]-1]>i],--S[0][1+(a[p[i]-1]>i)];
		if(p[i]<n) ++S[0][a[p[i]+1]>i],--S[0][1+(a[p[i]+1]>i)];
		mat I{{{k-2*(n-i),2*(n-i),0},{i-1,k-n+2,n-i-1},{0,2*i,k-2*i}}};
		for(int x:{0,1,2}) for(int y:{0,1,2}) I[x][y]%=MOD;
		mat T=S*ksm(I,m);
		ans=(ans+T[0][1])%MOD;
	}
	printf("%lld\n",ans);
	return 0;
	
}
```

---

## 作者：P2441M (赞：3)

## 题意
[原题链接](https://atcoder.jp/contests/arc176/tasks/arc176_d)

给定一个长度为 $n$ 的排列 $p$，并执行以下操作 $m$ 次：选择 $1\leq i<j\leq n$，交换 $p_i$ 和 $p_j$。

定义一个序列 $p$ 的权值为 $\sum_{i=1}^{n-1}|p_i-p_{i-1}|$。求在 $\binom{n}{2}^m$ 种可能的操作后，$p$ 的价值之和。答案对 $998244353$ 取模。

对于所有数据，$2\leq n\leq 2\times 10^5$，$1\leq m\leq 2\times 10^5$。

## 题解
一顿乱想后发现序列的权值很难进行统计，所以考虑重新刻画权值。显然
$$
|p_i-p_{i+1}|=\sum_{j=1}^n[\min(p_i,p_{i+1})<j\leq \max(p_i,p_{i+1})]
$$

据此，考虑枚举 $k\in[1,n)$，建立 $0/1$ 序列 $v_i=[p_i>k]$。注意到若 $v$ 中存在相邻的 $(0,1)/(1,0)$，则说明对应位置上 $\min(p_i,p_{i+1})<j\leq \max(p_i,p_{i+1})$，与权值的形式恰好一致！因此，问题转化为对于每个 $0/1$ 序列，计算所有可能的交换操作后相邻的 $(0,1)/(1,0)$ 的数量总和。

我们选定两个相邻的位置 $j$ 和 $j+1$ 进行观察，则本质不同的 $0/1$ 对只有 $3$ 种：$(0,0),(1,1),(0,1)/(1,0)$，依次标号为 $[1,3]$。考虑 DP。令 $f_{i,1/2/3}$ 表示 $i$ 次操作后这两个位置最终形成某种 $0/1$ 对的方案数。转移很简单，并且显然可以矩阵快速幂优化，这里直接给出转移矩阵：
$$
T=
\begin{bmatrix}
\binom{n-2}{2}+2(c_0-2)+1 & 0 & 2c_1\\
0 & \binom{n-2}{2}+2(c_1-2)+1 & 2c_0\\
c_0-1 & c_1-1 & \binom{n-2}{2}+(n-2)+1
\end{bmatrix}
$$

其中 $c_0=k,c_1=n-k$ 分别表示 $v$ 中 $0,1$ 的个数。依据选定的 $j$ 和 $j+1$ 的初始情况，列出初始的 $1\times 3$ 答案矩阵，再右乘 $T^m$ 即可得到这两个位置的答案。于是我们得到了 $O(n^2\log{m})$ 的算法。但既然本质不同的 $0/1$ 对只有 $3$ 种，那么直接维护它们的数量即可，无需枚举每对相邻的位置。时间复杂度 $O(n\log{m})$。

具体实现时，可以将 $3$ 个 $1\times 3$ 的初始矩阵合并为一个 $3\times 3$ 矩阵整体转移。

## 代码
```cpp
#include <iostream>

using namespace std;

#define lowbit(x) ((x) & -(x))
#define chk_min(x, v) (x) = min((x), (v))
#define chk_max(x, v) (x) = max((x), (v))
typedef long long ll;
typedef pair<int, int> pii;
const int N = 2e5 + 5, M = 2e5 + 5, MOD = 998244353;

int n, m, ans, p[N], pos[N];
int c0, c1, t1, t2, t3;
bool vis[N];

struct Matrix {
	int r, c;
	ll a[5][5];
	
	void clear(ll v = 0) {
		for (int i = 1; i <= r; ++i)
			for (int j = 1; j <= c; ++j) a[i][j] = v;
	}
	
	Matrix operator*(const Matrix &x) const {
		Matrix res = { r, x.c }; res.clear();
		for (int i = 1; i <= r; ++i)
			for (int j = 1; j <= x.c; ++j)
				for (int k = 1; k <= c; ++k)
					res.a[i][j] = (res.a[i][j] + a[i][k] * x.a[k][j] % MOD) % MOD;
		return res;
	}
} f, g, t;

Matrix qpowm(Matrix a, ll b) {
	--b;
	Matrix res = a;
	for (; b; b >>= 1) {
		if (b & 1) res = res * a;
		a = a * a;
	}
	return res;
}

void change(int x, int d) {
	if (!vis[x] && !vis[x + 1]) f.a[1][1] += d;
	else if (vis[x] && vis[x + 1]) f.a[2][2] += d;
	else f.a[3][3] += d;
} 

int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) cin >> p[i], pos[p[i]] = i;
	f = t = { 3, 3 };
	f.clear(); f.a[2][2] = n - 1;
	for (int i = 1; i <= n; ++i) vis[i] = true;
	for (int i = 1; i < n; ++i) {
		if (pos[i] > 1) change(pos[i] - 1, -1);
		if (pos[i] < n) change(pos[i], -1);
		vis[pos[i]] = 0;
		if (pos[i] > 1) change(pos[i] - 1, 1);
		if (pos[i] < n) change(pos[i], 1);
		c0 = i; c1 = n - i;
		ll v = 1ll * (n - 2) * (n - 3) / 2;
		t.a[1][1] = v + ((c0 - 2) << 1) + 1; t.a[1][2] = 0; t.a[1][3] = c1 << 1;
		t.a[2][1] = 0; t.a[2][2] = v + ((c1 - 2) << 1) + 1; t.a[2][3] = c0 << 1;
		t.a[3][1] = c0 - 1; t.a[3][2] = c1 - 1; t.a[3][3] = v + c0 - 1 + c1 - 1 + 1;
		for (int i = 1; i <= 3; ++i)
			for (int j = 1; j <= 3; ++j) t.a[i][j] %= MOD;
		g = f * qpowm(t, m);
		ans = (ans + (g.a[1][3] + g.a[2][3] + g.a[3][3]) % MOD) % MOD;
	}
	cout << ans;
	return 0;
}
```

---

## 作者：WangBng (赞：1)

$*\color{orange}{2572}$，简单题。

考虑对于 `01` 序列怎么做，假设有 $x$ 个 $0$，$n-x$ 个 $1$，那么对于一个任意的相邻项组合 `00,01,10,11`，可以列出一次交换操作后变为 `00,01,10,11` 的方案数，最终是所有 `01,10` 能产生 $1$ 的贡献。

可以列出矩阵：（顺序为 `00,01,10,11`）

$$\begin{bmatrix} C_{n-2}^2+1+2(x-2) & n-x & n-x & 0 \\ x-1 & C_{n-2}^2+n-2 & 1 & n-x-1 \\ x-1 & 1 & C_{n-2}^2+n-2 & n-x-1\\ 0 & x & x & C_{n-2}^2+2n-2x-3 \end{bmatrix}$$

设该矩阵经过矩阵乘法后得到的值为 $w_{00/01/10/11,00/01/10/11}$。

那么接下来要考虑非 $01$ 序列的情况了，考虑到如果令 $\ge x$ 的是 $1$，$<x$ 的是 $0$，那么把相邻项为 $01$ 或 $10$ 的方案加起来即可。

这是一个套路，具体可见 HNOI 切糕。

先计算出 $x=1$ 时的答案，再考虑从 $x$ 变到 $x+1$ 对应的变化。

令 $v_{ij}$ 表示相邻项为 $\overline{ij}$ 的方案数，可以在每次变化中动态维护，那么答案即为：

$$\text{ans}=\sum\limits_{x}\sum\limits_{(ij,kl)}w_{ij,kl}v_{ij}[kl=01 \ \text{or} \ kl=10]$$。

后面的可以矩阵乘法计算，总复杂度 $O(n\log m)$，带一个 $64$ 倍的常数。

---

## 作者：StarPatrick (赞：1)

不知道为什么题解都是清一色的矩阵乘法，$m$ 不是才 2e5 吗？

设初始序列为 $a$。

考虑拆贡献，我们先计算 $P_i=a_x,P_{i+1}=a_y$ 对答案贡献了多少次，分三种情况：

1. $x\in \{i,i+1\},y\in \{i,i+1\}$
2. $x\notin \{i,i+1\},y\in \{i,i+1\}$ 或 $x\in \{i,i+1\},y\notin \{i,i+1\}$ 两种情况差不多
3. $x\notin \{i,i+1\},y\notin \{i,i+1\}$

可以发现，把 $x,y$ 看成 1，其他看成 0，可以发现，对于同一种情况的 $x,y$ 对答案的贡献次数都是一样的。定义 $dp_{a,b}$ 表示经过 $a$ 次操作后 $\{i, i+1\}$ 中有 $b$ 个 1 的操作方案数。可以发现，这个 dp 是与 $i$ 无关的，预处理即可，转移显然。（其他题解难道是对这个 dp 矩阵乘法？）

计算了每种情况对答案的贡献次数后，根据乘法分配律，接下来需要再算上 $\sum |a_x-a_y|$ 即可。

对于情况一，只有一对 $x,y$，直接计算即可。

对于情况二和情况三，这里我直接不想动脑子了，对 $x\notin \{i,i+1\}$ 的 $a_x$ 建立了一颗权值线段树，暴力计算贡献即可，不知道还有没有更简单的方法。

然后不断从 $i, i+1$ 推到 $i+1, i+2$ 就做完了。

复杂度 $O(n\log n+m)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int MAXN = 2e5, mod = 998244353, inv2 = (mod+1)/2;
int n, m, a[MAXN+5];
ll dp[MAXN+5][3], all;
ll dfs(int i, int u) {
	if (i==m+1) return (u==2);
	if (!u&&n<=3) return 0;
	if (u==1&&n<=2) return 0;
	if (dp[i][u]!=-1) return dp[i][u];
	if (!u) return dp[i][u]=(dfs(i+1, 1)*4+dfs(i+1, 0)*((all-4)%mod))%mod;
	else if (u==1) return dp[i][u]=(dfs(i+1, 2)+dfs(i+1, 0)*(n-3)+dfs(i+1, 1)*((all-(n-2))%mod))%mod;
	else return dp[i][u]=(dfs(i+1, 1)*2*(n-2)+dfs(i+1, 2)*((all-2*(n-2))%mod))%mod;
}
ll sum[4*MAXN+5];
int num[4*MAXN+5];
void insert(int i, int l, int r, int q, int x) {
	if (l==r) {
		num[i]+=x;
		sum[i]+=x*l;
		return ;
	}
	int mid = l+r>>1;
	if (q<=mid) insert(i*2, l, mid, q, x);
	else insert(i*2+1, mid+1, r, q, x);
	sum[i] = sum[i*2]+sum[i*2+1];
	num[i] = num[i*2]+num[i*2+1];
	return ;
}
ll found1(int i, int l, int r, int q, int w) {
	if (q>w) return 0;
	if (l>=q&&r<=w) return sum[i];
	int mid = l+r>>1;
	ll ans = 0;
	if (q<=mid) ans+=found1(i*2, l, mid, q, w);
	if (w>mid) ans+=found1(i*2+1, mid+1, r, q, w);
	return ans;
}
int found2(int i, int l, int r, int q, int w) {
	if (q>w) return 0;
	if (l>=q&&r<=w) return num[i];
	int mid = l+r>>1, ans = 0;
	if (q<=mid) ans+=found2(i*2, l, mid, q, w);
	if (w>mid) ans+=found2(i*2+1, mid+1, r, q, w);
	return ans;
}
ll getans(int x) {
	return ((1ll*x*(2*found2(1, 1, n, 1, x)-(n-2))+found1(1, 1, n, x+1, n)-found1(1, 1, n, 1, x))%mod+mod)%mod;
}
int main() {
	memset(dp, -1, sizeof(dp));
	scanf("%d %d", &n, &m);
	all = 1ll*n*(n-1)/2;
	for (int p=1;p<=n;p++) {
		scanf("%d", &a[p]);
	}
	ll u = 0;
	for (int p=3;p<=n;p++) {
		insert(1, 1, n, a[p], 1);
	}
	for (int p=3;p<=n;p++) {
		u = (u+getans(a[p]))%mod;
	}
	u = u*inv2%mod;
	ll ans = 0;
	for (int p=2;p<=n;p++) {
		ans = (ans+dfs(1, 1)*(getans(a[p])+getans(a[p-1]))+dfs(1, 0)*u+dfs(1, 2)*abs(a[p]-a[p-1]))%mod;
		if (p!=n) {
			u = (u-getans(a[p+1])+mod)%mod;
			insert(1, 1, n, a[p+1], -1);
			insert(1, 1, n, a[p-1], 1);
			u = (u+getans(a[p-1]))%mod;
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：WrongAnswer_90 (赞：1)

# [My Blogs](https://www.cnblogs.com/WrongAnswer90/p/18377491)

### [[ARC176D] Swap Permutation](https://www.luogu.com.cn/problem/AT_arc176_d)

对每个位置分别算贡献。一个很重要的观察是其他所有数都是等价的（非常神奇）。设 $A$ 表示原来 $i$ 位置上的数，$B$ 表示原来 $i+1$ 位置上的数，$C$ 表示其他的数，设 $f_{0\sim 7}$ 表示经过 $m$ 次操作之后 $AB,BA,AC,CA,BC,CB,CC$ 的概率。每个位置 $i$ 的 $f$ 都是相同的。转移系数应该比较容易手搓出来，预处理 $f$ 可以暴力 DP，也可以矩阵快速幂（所以其实可以做 $m=10^{18}$ 的）。

设 $sum_i$ 表示 $\sum_j\text{abs}(i-j)$，$all$ 表示 $\sum_i\sum_j\text{abs}(i-j)$。对于第 $i$ 个位置，其贡献为：

$$
\begin{aligned}
&(f_0+f_1)\text{abs}(a_i-a_{i+1})\\
+&(f_2+f_3)\frac{(sum_{a_i}-\text{abs}(a_i-a_{i+1}))}{n-2}\\
+&(f_4+f_5)\frac{(sum_{a_{i+1}}-\text{abs}(a_i-a_{i+1}))}{n-2}\\
+&f_6\frac{all-sum_{a_{i+1}}-sum_{a_i}+\text{abs}(a_i-a_{i+1}))}{\binom{n-2}2}\\
\end{aligned}
$$

总复杂度 $\mathcal O(n+T^3\log m)$，其中 $T=7$。

```cpp
int n,m,a[200010];
struct Matrix{int f[7][7];Matrix(){memset(f,0,sizeof(f));}}A;
struct Vector{int f[7];Vector(){memset(f,0,sizeof(f));}}B;
inline Matrix operator *(const Matrix x,const Matrix y)
{
	Matrix z;
	for(int i=0;i<7;++i)for(int j=0;j<7;++j)for(int k=0;k<7;++k)
	Madd(z.f[i][j],Cmul(x.f[i][k],y.f[k][j]));
	return z;
}
inline Vector operator *(const Vector x,const Matrix y)
{
	Vector z;
	for(int j=0;j<7;++j)for(int k=0;k<7;++k)
	Madd(z.f[j],Cmul(x.f[k],y.f[k][j]));
	return z;
}
inline int calc(int x){return Cadd(Cmul(x-1,x,inv2),Cmul(n-x+1,n-x,inv2));}
//0:AB 1:BA 2:AC 3:CA 4:BC 5:CB 6:CC
inline void mian()
{
	read(n,m);int ans=0,all=0;
	for(int i=1;i<=n;++i)read(a[i]),Madd(all,calc(i));
	Mmul(all,inv2);
	if(n==2)return write(1);
	A.f[0][0]=Cmul(n-2,n-3,inv2),A.f[0][1]=1,A.f[0][2]=n-2,A.f[0][5]=n-2;
	A.f[1][0]=1,A.f[1][1]=Cmul(n-2,n-3,inv2),A.f[1][3]=n-2,A.f[1][4]=n-2;
	A.f[2][0]=1,A.f[2][2]=Cadd(Cmul(n-2,n-3,inv2),n-3),A.f[2][3]=1,A.f[2][4]=1,A.f[2][6]=n-3;
	A.f[3][1]=1,A.f[3][2]=1,A.f[3][3]=Cadd(Cmul(n-2,n-3,inv2),n-3),A.f[3][5]=1,A.f[3][6]=n-3;
	A.f[4][1]=1,A.f[4][2]=1,A.f[4][4]=Cadd(Cmul(n-2,n-3,inv2),n-3),A.f[4][5]=1,A.f[4][6]=n-3;
	A.f[5][0]=1,A.f[5][3]=1,A.f[5][4]=1,A.f[5][5]=Cadd(Cmul(n-2,n-3,inv2),n-3),A.f[5][6]=n-3;
	A.f[6][2]=1,A.f[6][3]=1,A.f[6][4]=1,A.f[6][5]=1,A.f[6][6]=Cdel(Cmul(n,n-1,inv2),4);
	B.f[0]=1;
	for(;m;m>>=1,A=A*A)if(m&1)B=B*A;
	int iv1=power(n-2,MOD-2),iv2=power(Cmul(n-2,n-3,inv2),MOD-2);
	for(int i=1;i<n;++i)
	{
		Madd(ans,Cmul(Cadd(B.f[0],B.f[1]),abs(a[i]-a[i+1])));
		Madd(ans,Cmul(iv1,Cadd(B.f[2],B.f[3]),Cdel(calc(a[i]),abs(a[i]-a[i+1]))));
		Madd(ans,Cmul(iv1,Cadd(B.f[4],B.f[5]),Cdel(calc(a[i+1]),abs(a[i]-a[i+1]))));
		Madd(ans,Cmul(iv2,B.f[6],Cadd(Cdel(all,calc(a[i]),calc(a[i+1])),abs(a[i]-a[i+1]))));
	}
	write(ans);
}
```

---

## 作者：鲤鱼江 (赞：0)

感觉很棒的 trick 啊！给出了这一类问题的通解。

单纯对于这个题有更简洁的做法。

对于任意一个位置 $x$ 来讲，其他值都是等价的。也就是说除了 $P_x$ 之外的值最后留在 $x$ 的概率是相等的。

注意到这一点之后，因为答案牵扯到两个位置，所以我们枚举两个位置 $x,y$ 讨论它们的权值关系，不妨假设 $x<y$，不难发现对于任意 $x<y$ 来讲，求出来的东西亦等价。

需要注意的是，我们并没有强调 $x,y$ 一定相邻，不过不难发现 $x,y$ 是否相邻最后结果都是一样的。

记 $a=P_x,b=P_y$，$c$ 表示不为 $a,b$ 的值，那么最后位置 $x,y$ 上的值有 $7$ 种情况：$(a,b),(b,a),(c,b),(b,c),(a,c),(c,a),(c,c)$。

考虑构造矩阵 $M$，其中 $M_{i,j}$ 表示原本是情况 $i$ 通过一次交换变成情况 $j$ 的方案数，构造如下：
$$
\begin{bmatrix}
{n-2\choose 2}&1&n-2&0&n-2&0&0\\
1&{n-2\choose 2}&0&n-2&0&n-2&0\\
1&0&{n-2\choose 2}+n-3&1&0&1&n-3\\
0&1&1&{n-2\choose 2}+n-3&1&0&n-3\\
1&0&0&1&{n-2\choose 2}+n-3&1&n-3\\
0&1&1&0&1&{n-2\choose 2}+n-3&n-3\\
0&0&1&1&1&1&{n-2\choose 2}+2(n-4)+1\\
\end{bmatrix}
$$
定义 $1\times 7$ 的行向量 $e$：$\begin{bmatrix} 1&0&0&0&0&0&0\end{bmatrix}$，也就是只有开头为一。

再定义行向量 $f=e\times M^{k}$，那么 $f_{1,i}$ 就是经过 $k$ 次操作后，$x,y$ 上值是 $i$ 种情况得方案数了，当然为了方便起见，在没有歧义的情况下我们用 $f_i$ 表示 $f_{1,i}$。

回归到本问题。

假设现在正在处理位置 $i,i=1$，考虑 $7$ 种情况分别对答案的贡献。

$(a,b),(b,a)$ 的贡献为：$(f_1+f_2)\times|P_i-P_{i+1}|$。

设 $s_x=\sum\limits_{i=1}^n |i-x|=\frac{x(x-1)}{2}+\frac{(n-x+1)(n-x)}{2}$，继续考虑接下来的贡献。

$(c,b),(b,c)$ 的贡献：$\frac{(f_3+f_4)\times(s_{P_{i+1}}-|P_{i}-P_{i+1}|)}{n-2}$。

除以 $n-2$ 是因为选出 $c$ 的方案已经在 $M$ 中算过了，但是在 $s$ 中又算了一遍所以要去重。

同理 $(a,c),(c,a)$ 的贡献：$\frac{(f_5+f_6)\times(s_{P_i}-|P_{i}-P_{i+1}|)}{n-2}$。

记 $sum=\sum\limits_{i=1}^n s_i$，继续计算 $(c,c)$ 的贡献为：
$$
\frac{f_7\times(sum-2(s_{P_i}+s_{P_{i+1}}-|P_i-P_{i+1}|))}{(n-2)(n-3)}
$$
把所有贡献加起来即可。

```cpp
#include<bits/stdc++.h>

using namespace std;

const int N=2e5+10;
const int mod=998244353;
struct modint {
    int val;
    static int norm(const int& x) { return x < 0 ? x + mod : x; }
    modint inv() const {
        int a = val, b = mod, u = 1, v = 0, t;
        while (b > 0) t = a / b, swap(a -= t * b, b), swap(u -= t * v, v);
        return modint(u);
    }
    modint() : val(0) {}
    modint(const int& m) : val(norm(m)) {}
    modint(const long long& m) : val(norm(m % mod)) {}
    modint operator-() const { return modint(norm(-val)); }
    modint& operator+=(const modint& o) { return val = (1ll * val + o.val) % mod, *this; }
    modint& operator-=(const modint& o) { return val = norm(1ll * val - o.val), *this; }
    modint& operator*=(const modint& o) { return val = static_cast<int>(1ll * val * o.val % mod), *this; }
    modint operator-(const modint& o) const { return modint(*this) -= o; }
    modint operator+(const modint& o) const { return modint(*this) += o; }
    modint operator*(const modint& o) const { return modint(*this) *= o; }
	friend std::ostream& operator<<(std::ostream& os, const modint a) { return os << a.val; }
}s[N],ans,sum,f[N];

int n,m,a[N];

const int Max=7;
struct Matrix{
	modint a[Max+1][Max+1];
	modint* operator [](const int x){return a[x];}
	inline void clear(){memset(a,0,sizeof(a));}
	inline void Init(){for(int i=1;i<=Max;++i) for(int j=1;j<=Max;++j) a[i][j]=(i==j);}
	Matrix operator *(const Matrix &t){
		Matrix z;z.clear();
		for(int i=1;i<=Max;++i) for(int k=1;k<=Max;++k) for(int j=1;j<=Max;++j) z[i][j]+=a[i][k]*t.a[k][j];
		return z;
	}
}bas,res;

inline void init(){
	modint tmp=1ll*(n-2)*(n-3)/2;res[1][1]=1;
	bas=(Matrix){{
		{0,0,0,0,0,0,0,0},
		{0,tmp,1,n-2,0,n-2,0,0},
		{0,1,tmp,0,n-2,0,n-2,0},
		{0,1,0,tmp+n-3,1,0,1,n-3},
		{0,0,1,1,tmp+n-3,1,0,n-3},
		{0,1,0,0,1,tmp+n-3,1,n-3},
		{0,0,1,1,0,1,tmp+n-3,n-3},
		{0,0,0,1,1,1,1,tmp+2*(n-4)+1}
	}};
}


int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>m;init();for(int i=1;i<=n;++i) cin>>a[i];
	for(int i=1;i<=n;++i){
		s[i]=1ll*i*(i-1)/2+1ll*(n-i+1)*(n-i)/2;
		sum+=s[i];
	}
	for(int i=m;i;i>>=1,bas=bas*bas) if(i&1) res=res*bas;
	for(int i=1;i<=7;++i) f[i]=res[1][i];
	modint d=modint(n-2).inv(),div=modint(1ll*(n-2)*(n-3)).inv();
	for(int i=1;i<n;++i){
		modint v=abs(a[i]-a[i+1]),x=s[a[i]],y=s[a[i+1]];
		ans+=(f[1]+f[2])*v;
		ans+=(f[3]+f[4])*(y-v)*d;
		ans+=(f[5]+f[6])*(x-v)*d;
		ans+=f[7]*(sum-(x+y-v)*2)*div;
	}
	cout<<ans<<endl;
	return 0;
}
```

## 更简洁的做法

直接转差分，枚举阈值 $c$，将小于 $c$ 的当作 $0$，大于等于 $c$ 的当作 $1$。

那么一个 $01$ 串对答案产生的贡献就是 $01$ 交界处的个数。

然后发现情况数被压到了三种，直接沿用上面的做法即可！

---

