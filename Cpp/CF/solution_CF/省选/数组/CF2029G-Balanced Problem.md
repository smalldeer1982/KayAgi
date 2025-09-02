# Balanced Problem

## 题目描述

有一个长度为 $n$ 的整数数组 $a$，初始时所有元素均为 $0$。

Kevin 可以对数组进行若干次操作。每次操作有以下两种类型之一：

- 前缀加法 —— Kevin 选择一个下标 $x$（$1\le x\le n$），然后对每个 $1\le j\le x$，将 $a_j$ 增加 $1$；
- 后缀加法 —— Kevin 选择一个下标 $x$（$1\le x\le n$），然后对每个 $x\le j\le n$，将 $a_j$ 增加 $1$。

在 KDOI 国，人们认为整数 $v$ 是“平衡”的。因此，Iris 给了 Kevin 一个长度为 $n$ 的数组 $c$，并定义数组 $a$ 的美丽值如下：

- 初始时，令 $b=0$；
- 对于每个 $1\le i\le n$，如果 $a_i=v$，则将 $c_i$ 加到 $b$ 上；
- $a$ 的美丽值即为最终的 $b$。

Kevin 想要在所有操作完成后，使 $a$ 的美丽值最大。然而，他在犯困时已经进行了 $m$ 次操作。现在，他可以再进行任意次数（可能为零）的新操作。

你需要帮助 Kevin，若他最优地进行新操作，求出最大可能的美丽值。

不过，为了防止你只是“碰运气”，Kevin 给了你一个整数 $V$，你需要对于每个 $1\le v\le V$ 都解决这个问题。

## 说明/提示

在第一个测试用例中，数组 $a$ 在初始操作后变化如下：$[0, 0, 0] \xrightarrow{\mathtt{L}\ 3} [1, 1, 1] \xrightarrow{\mathtt{R}\ 3} [1, 1, 2] \xrightarrow{\mathtt{L}\ 1} [2, 1, 2]$。

- 对于 $v=1$，最优策略是不进行任何新操作，美丽值为 $b=c_2=2$；
- 对于 $v=2$，最优策略是在下标 $2$ 进行一次前缀加法，之后 $a$ 变为 $[3,2,2]$，美丽值为 $b=c_2+c_3=6$。

在第二个测试用例中，对于 $v=1$ 和 $v=2$，最优策略都是不进行任何新操作。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
5
3 3 2
1 2 4
L 3
R 3
L 1
3 3 2
5 1 4
L 3
R 3
L 1
5 4 5
1 1 1 1 1
L 3
R 2
L 5
L 4
10 12 9
10 9 8 7 6 5 4 3 2 1
L 2
L 4
R 4
R 4
L 6
R 8
L 3
L 2
R 1
R 10
L 8
L 1
1 1 4
1000000000
L 1```

### 输出

```
2 6
1 9
0 1 3 5 5
0 0 0 6 25 32 35 44 51
1000000000 1000000000 1000000000 1000000000```

# 题解

## 作者：Fesdrer (赞：5)

首先，我们思考，对于一个数组 $a$ 是否能从一个全为 $0$ 的序列通过若干次操作得出。注意到，对于 $i$，如果 $a_i<a_{i+1}$，那么操作中一定有对 $i+1$ 进行后缀加 $a_{i+1}-a_i$ 次，$a_i>a_{i+1}$ 同理，而前缀后缀加的次数需要分别小于等于 $a_1,a_n$，即：

$$
\sum_{i=1}^{n-1}\max(a_{i+1}-a_i,0)\le a_n\\
\sum_{i=1}^{n-1}\max(a_i-a_{i+1},0)\le a_1
$$

观察到，如果第一个式子成立，则我们考虑每一个 $a_i<a_{i+1}$，对 $i+1$ 进行后缀减 $a_{i+1}-a_i$ 次，这样以后，数组将递减，且 $a_n$ 非负，此时二式也会成立。反过来同理。因此上面两个限制条件可以变成：

$$
\sum_{i=1}^{n-1}|a_{i+1}-a_i|\le a_1+a_n
$$

注意到，题目先给出了一些固定的操作，因此这样操作以后的初始数组 $a$ 满足上式。容易发现，原序列中大于 $V$ 的元素可以丢弃，而相邻相等的元素就可以贪心地合并，此时整个序列的元素小于等于 $V$ 且互不相等，因此 $|a_{i+1}-a_i|>0$，因此序列长度定然小于等于 $a_1+a_n\le 2V$，即序列长度和值域都会变成 $\mathcal O(V^2)$。

此时我们考虑选择若干个元素并将其通过前缀加和后缀加提升到相同高度，设选择的元素下标从小到大排序后为数组 $p$，接下来思考提升到的高度的最小值。容易发现，如果 $a_{p_i}<a_{p_{i+1}}$ 那么就要对 $p_i$ 前缀加 $a_{p_{i+1}}-a_{p_i}$ 次。为了方便，我们让在数组 $p$ 的开头加入 $0$ 并让 $a_0=0$，这样以后，我们发现我们前缀加的次数就是提升到的最小高度，这是因为前缀加后序列递减，此时即使后缀加也不会使高度继续提升。令最小高度为 $H$，这种选择方式的美观度为 $C$，加入 $0$ 以后的 $p$ 的长度为 $l$，写成式子就是：

$$
H=\sum_{i=1}^l\max(a_{p_i}-a_{p_{i-1}},0)\\
C=\sum_{i=1}^lc_{p_i}
$$

这意味着 $C$ 可以贡献给大于等于 $H$ 的所有 $v$。

接下来，我们考虑 dp，设 $f(i,j)$ 表示选择到 $i$，当前提升高度的最小值为 $j$，美观度的最大值，则：

$$
f(i,j)=\max_{k=0}^{i-1}f(k,j-\max(a_i-a_k,0))+c_i
$$

分别考虑 $a_i$ 和 $a_k$ 的关系：

$$
f(i,j)=c_i+\max\begin{cases}\max\limits_{k\in[0,i-1]\bigcap a_k>a_i}f(k,j)\\\max\limits_{k\in[0,i-1]\bigcap a_k\le a_i}f(k,j-a_i+a_k)\end{cases}
$$

因此我们从小到大枚举 $i$，开 $2V$ 个树状数组，对于其中 $V$ 个树状数组，第 $j$ 个树状数组存当前的所有 $f(i,j)$，对另外 $V$ 个树状数组，第 $j$ 个存当前的所有 $f(i,j+a_i)$，这样就可以 $\mathcal O(v^2\log v)$ 转移了，答案就是：

$$
Ans(v)=\max_{i\le n,j\le v}f(i,j)
$$

```c++
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5,V=2005;
const long long INF=0x3f3f3f3f3f3f3f3f;
int T,n,m,v,a[N];
long long f[V<<1][V],c[2][V][V],val[N];
void add(int k,int p,int x,long long y){
	if(!x)	c[k][p][x]=max(c[k][p][x],y);
	else	for(;x<=v;x+=x&-x)	c[k][p][x]=max(c[k][p][x],y);
}
long long ask(int k,int p,int x){
	long long ret=c[k][p][0];
	for(;x;x-=x&-x)	ret=max(ret,c[k][p][x]);
	return ret;
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n>>m>>v;
		for(int i=1;i<=n;i++)	cin>>val[i];
		for(int i=0;i<=n+1;i++)	a[i]=0;
		while(m--){
			char op;
			int x;
			cin>>op>>x;
			if(op=='L')	{a[1]++;if(x<n)a[x+1]--;}
			else	a[x]++;
		}
		for(int i=2;i<=n;i++)	a[i]+=a[i-1];
		int newn=0;
		for(int i=1;i<=n;i++) if(a[i]<=v){
			if(newn&&a[newn]==a[i])	val[newn]+=val[i];
			else	a[++newn]=a[i],val[newn]=val[i];
		}
		n=newn;
		if(!n){
			while(v--)	cout<<0<<" ";
			cout<<endl;
			continue;
		}
		for(int i=0;i<=n;i++)	for(int j=0;j<=v;j++)	f[i][j]=-INF;
		for(int i=0;i<=v;i++)	for(int j=0;j<=v;j++)	c[0][i][j]=c[1][i][j]=-INF;
		auto insert=[&](int x,int y){add(0,y,v-a[x],f[x][y]),add(1,y-a[x],a[x],f[x][y]);};
		auto get=[&](int x,int y){f[x][y]=val[x]+max(ask(0,y,v-a[x]),ask(1,y-a[x],a[x]));};
		f[0][0]=0,insert(0,0);
		for(int i=1;i<=n;i++){
			for(int j=a[i];j<=v;j++)	get(i,j);
			for(int j=a[i];j<=v;j++)	insert(i,j);
		}
		for(int i=1;i<=n;i++)	for(int j=1;j<=v;j++)
			f[i][j]=max(max(f[i][j],f[i-1][j]),max(f[i][j-1],f[i-1][j-1]));
		for(int i=1;i<=v;i++)	cout<<f[n][i]<<" ";
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：_lmh_ (赞：3)

显然，一开始就大于 $V$ 的 $a_i$ 是没有意义的，我们可以直接把它删掉。

如果两个连续的 $a_i$ 相同，那么存在一组最优解，使得每次操作要么同时包含它们两个，要么两个都不包含（考虑调整法，将包含恰好一个这样的 $a_i$ 的操作的端点移动一位，必有一种方案不劣于原来的）。

这样我们可以把它们合并成一个数（$a_i$ 不变，$c_i$ 相加）

由于初始的 $a_i$ 是通过操作生成的，所以现在数列的长度是 $O(V)$ 的。（读者自证不难）

现在我们令 $f_{i,j,k}$ 为：考虑的前 $i$ 个 $(a_i,c_i)$，目标数为 $k$，目前我们可以把 $j$ 变成 $k$。（也就是说，$i$ 这个位置上叠了 $k-j$ 层操作）

现在想想 $f_i$ 到 $f_{i+1}$ 的转移。对于 $R$ 操作，我们可以把 $f_{i,j,k}$ 转移到 $f_{i+1,j-x,k}$ 上。

（相当于在 $i+1$ 进行 $x$ 次 $R$ 操作。）

对于 $L$ 操作，将 $f_{i,j,k}$ 转移到 $f_{i+1,j+x,k+x}$ 上。

（相当于在 $i+1$ 进行 $-x$ 次 $R$ 操作再全局 $+x$，也就是在 $i$ 进行 $x$ 次 $L$ 操作。）

在一个位置同时进行 $L$ 和 $R$ 的转移相当于全局加一个数，这个东西我们可以预处理 $f_0$ 的时候考虑到，就不用这么转移了。

预处理的时候令 $j\ge k$ 的 $f_{0,j,k}=0$，其余的 $f_{0,j,k}$ 为 $-\infin$。

滚动一下数组，发现每次只有 $f_{a[i],k}$（少了 $i$ 一维）的转移是有意义的（转移到其他位置没有贡献，等到有贡献了再转移也不迟）。

也就是说，**每次我们对 $f_{a_i,k}$ 进行转移，将其修改为$\max\{\max\{f_{a_i+x,k}\}(0\le x \le V-a_i),\max\{f_{a_i-x,k-x}\}(0\le x \le min\{k,a_i\})\}+c_i$**，这样我们用树状数组 $g,h$ 记录竖线和斜线上的后缀（前缀）最大值，就可以在 $O(V^2\log V)$ 复杂度内解决问题。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N=200007,B=50,M=2007;
ll T,n,m,V,a[N],c[N],A[N],C[N],g[M][M],h[M][M];
char op;
void modify(ll* c,ll x,ll v){
	while(x<=V){
		c[x]=max(c[x],v);x+=x&-x;
	}
}
ll query(ll* c,ll x){
	ll mx=0;
	while(x){
		mx=max(mx,c[x]);x&=x-1;
	}
	return mx;
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n>>m>>V;++V;
		for (int i=1;i<=n;++i){a[i]=0;cin>>c[i];}
		a[1]=1;
		for (int i=1,x;i<=m;++i){
			cin>>op>>x;
			if (op=='L'){++a[1];--a[x+1];}
			else ++a[x];
		}
		for (int i=2;i<=n;++i) a[i]+=a[i-1];m=A[0]=0;
		for (int i=1;i<=n;++i) if (a[i]<=V){
			if (a[i]==A[m]) C[m]+=c[i];
			else{
				A[++m]=a[i];C[m]=c[i];
			}
		}
		for (int i=0;i<=V;++i) for (int j=1;j<=V;++j){h[i][j]=0;g[i][V-j+1]=(i>=j?0:-1e18);}
		for (int i=1;i<=m;++i){
			ll a=A[i],c=C[i];
			for (int j=a;j<=V;++j){
				ll tmp=max(query(g[j],V-a+1),query(h[j-a],a))+c;
				modify(g[j],V-a+1,tmp);modify(h[j-a],a,tmp);
			}
		}
		ll ans=0;
		for (int i=2;i<=V;++i){
			ans=max(ans,query(g[i],V));
			cout<<ans<<' ';
		}
		cout<<'\n';
	}
	return 0;
}
```

---

## 作者：Petit_Souris (赞：2)

### G Balanced Problem


全锣鼓素质最低的用户出的题，还是很有水平的！

首先发现值域连续段肯定会一起操作，所以可以缩成一个长度 $\mathcal O(V)$ 的序列。记 $a_i$ 为这段区间被覆盖的次数，$c_i$ 为原 $c$ 序列对应区间的和。

考虑一些比较大力出奇迹的做法，比如来个 $\mathcal O(V^4)$ 的 dp。

枚举 $v$ 并计算答案。设 $dp_{i,j,k}$ 表示前 $i$ 个位置，目前有 $j$ 次前缀操作，$k$ 次后缀操作经过下标 $i$。转移的时候，前缀操作可以选择继承一部分到下一个位置，剩下一部分在这里结尾；后缀操作已经加入的必须继承到下一位，也可以在这个位置再开始一些新的操作。并且我们发现，当 $j+k+a_i\neq v$ 时，最优策略一定是不改变 $j,k$，因为这样留给后面更多操作空间。因此转移为：

$$dp_{i,j,k}=\max\limits_{u\ge j,v\le k}dp_{i-1,u,v}+c_i \ (j+k+a_i=v)$$

显然可以用二维树状数组优化到 $\mathcal O(V^3\log^2 V)$。

如何优化？发现每次都把所有的 $v$ 重新算一遍实在太浪费了。接下来是一步特别精妙的技巧：考虑改变一下 $k$ 这维的意义，表示只考虑后缀操作，还差 $k$ 就能满足 $v$ 的限制了（也就是有 $v-k$ 个后缀操作）。转移的时候，需要变化的 $(j,k)$ 满足 $j+a_i=k$。所以每次找出这 $\mathcal O(V)$ 个位置，依旧用二维树状数组优化即可。最终 $v$ 的答案为 $(0,0)$ 和 $(v,v)$ 为顶点的矩形内的最大值。时间复杂度 $\mathcal O(V^2\log^2 V)$。[submission](https://codeforces.com/contest/2029/submission/291024885)

事实上观察一下转移的形状，重构的点在一条斜线上，每次查询一个左上角的最大值，那么 $(j,j+a_i)$ 和 $(j+1,j+1+a_i)$ 的区别就只有第 $j+1$ 行一个前缀和第 $j+1+a_i$ 列一个前缀，所以行列可以拆成独立的两维，分别用一维树状数组维护就行了。时间复杂度 $\mathcal O(V^2\log V)$。[submission](https://codeforces.com/contest/2029/submission/291026193)

（1log 只比 2log 快了 80ms，极其幽默。）

Bonus 是啥？不带 log 做法我不会。

---

## 作者：raincity (赞：2)

## 分析

考虑 $m = 0$ 时，我们能造出怎样的数列 $a$。

前缀加操作相当于 $a_1 \gets a_1 + 1$，$d_{x + 1} \gets d_{x + 1} - 1$。后缀加操作相当于 $d_x \gets d_x + 1$。

$\forall i$，若 $d_i \ge 0$ 则显然可以独立构造出，否则构造的过程会使 $a_1$ 增大 $-d_i$。

因此，$a$ 可以构造当且仅当 $a_1 \ge \sum_{i = 2}^n \max(-d_i, 0) = \sum_{i = 2}^n \max(a_{i - 1} - a_i, 0)$。

观察到右式很像积木大赛的操作次数，只是少了 $a_n$ 这一项，因此 $a$ 可以构造当且仅当至多 $a_1 + a_n$ 次区间 $+ 1$ 操作可以构造出 $a$。

现在考虑原问题。假如我们钦定最终 $a_{p_1} = a_{p_2} = \dots = a_{p_k} = v$，设 $b_i$ 表示 $a_i$ 的增量，则 $b_{p_i} = v - a_{p_i}$，且 $b$ 必须可以用 $b_1 + b_n$ 次区间 $+ 1$ 次操作构造出。

对于 $b$ 两个固定的位置之间的位置，全取其中一个固定的位置的值显然最优，此时中间的这些位置相当于不存在。所以我们只需要固定 $b_1$ 和 $b_n$。

容易发现 $b_1$ 从 $0$ 开始增大的过程中，当 $b_1$ 不超过 $b_{p_1}$ 时，它增大 $1$ 会使得允许的操作次数增大 $1$，而需要的操作次数增大不超过 $1$。而当 $b_1$ 超过 $b_{p_1}$ 时，它增大 $1$ 一定会使得需要的操作次数增大 $1$。因此 $b_1 = b_{p_1}$ 最优。

综上，$b$ 合法当且仅当 $b_{p_1}, \dots, b_{p_k}$ 合法，即 $v \ge \sum_{i = 1}^k  \max(a_{p_i} - a_{p_{i - 1}}, 0)$，其中令 $a_0 = p_0 = 0$。

考虑直接对着判定 DP，设 $f(i, j)$ 表示选了 $a_i$，$\sum \max(a_{p_i} - a_{p_{i - 1}}, 0) = j$，最大的收益。

暴力转移是 $O(n^2 V)$，分类讨论把 $\max$ 拆掉，增加的一维偏序用树状数组维护可以优化到 $O(n V \log V)$。

考虑进一步优化。观察到 $a$ 是用操作生成的而不是任意给定的，一定有性质。显然只需要保留不超过 $V$ 的 $a_i$，并且相邻的相等的 $a_i$ 可以缩到一起，权值为 $c$ 之和。可以发现此时 $a_1 \le V$，$a_n \le V$，因此 $a$ 可以用 $2V$ 次区间 $+1$ 操作生成，所以 $a$ 的长度不超过 $4V$。这样复杂度优化到 $O(V^2 \log V)$，和题目保证的数据范围契合了，可以通过。

## 实现

```c++
#include <bits/stdc++.h>

using namespace std;

#define L(i, l, r) for (int i = (l); i <= (r); ++i)
#define R(i, l, r) for (int i = (r); i >= (l); --i)
#define all(x) begin(x), end(x)
#define len(x) int((x).size())

using ll = long long;
using db = long double;

template <typename T>
inline bool ckmin(T &x, const T &y) {
  if (y < x) {
    x = y;
    return true;
  } else {
    return false;
  }
}

template <typename T>
inline bool ckmax(T &x, const T &y) {
  if (x < y) {
    x = y;
    return true;
  } else {
    return false;
  }
}

constexpr int N = 2e5 + 5, V = 2005;
constexpr ll inf = 4e18;

int n, m, v, a[N], d1[N], d2[N];
ll c[N], ans[V];

void minify() {
  int tot = 0;
  L(i, 1, n) {
    if (a[i] <= v) {
      a[++tot] = a[i], c[tot] = c[i];
    }
  }
  n = tot, tot = 0;
  L(i, 1, n) {
    if (i == 1 or a[i] != a[i - 1]) {
      a[++tot] = a[i], c[tot] = c[i];
    } else {
      c[tot] += c[i];
    }
  }
  n = tot;
}

namespace bit1 {
ll t[V][V];

void init(int n) {
  L(i, 1, v + 1) {
    memset(t[i], 0xc0, (n + 1) * sizeof t[0][0]);
  }
}

void upd(int id, int x, ll val) {
  for (++x; x > 0; x &= x - 1) {
    ckmax(t[x][id], val);
  }
}

ll qry(int id, int x) {
  ll ans = -inf;
  for (++x; x <= v + 1; x += x & -x) {
    ckmax(ans, t[x][id]);
  }
  return ans;
}
}

namespace bit2 {
ll t[V][2 * V];

void init(int n) {
  L(i, 1, v + 1) {
    memset(t[i], 0xc0, (n + 1) * sizeof t[0][0]);
  }
}

void upd(int id, int x, ll val) {
  for (++x; x <= v + 1; x += x & -x) {
    ckmax(t[x][id], val);
  }
}

ll qry(int id, int x) {
  ll ans = -inf;
  for (++x; x > 0; x &= x - 1) {
    ckmax(ans, t[x][id]);
  }
  return ans;
}
}

void proc() {
  cin >> n >> m >> v;
  L(i, 1, n) {
    cin >> c[i];
  }
  memset(d1 + 1, 0, n * sizeof d1[0]);
  memset(d2 + 1, 0, n * sizeof d2[0]);
  L(i, 1, m) {
    char tp;
    int x;
    cin >> tp >> x;
    if (tp == 'L') {
      ++d1[x];
    } else {
      ++d2[x];
    }
  }
  R(i, 1, n - 1) {
    d1[i] += d1[i + 1];
  }
  L(i, 1, n) {
    d2[i] += d2[i - 1];
    a[i] = d1[i] + d2[i];
  }
  minify();
  // cerr << "n = " << n << "\n";
  // L(i, 1, n) {
  //   cerr << "a[" << i << "] = " << a[i] << ", c[" << i << "] = " << c[i] << "\n";
  // }
  memset(ans, 0, (v + 1) * sizeof ans[0]);
  bit1::init(v);
  bit2::init(2 * v), bit2::upd(v, 0, 0);
  L(i, 1, n) {
    L(j, 0, v) {
      ll f = max(bit1::qry(j, a[i]), bit2::qry(j - a[i] + v, a[i])) + c[i];
      ckmax(ans[j], f);
      bit1::upd(j, a[i], f);
      bit2::upd(j - a[i] + v, a[i], f);
      // cerr << "f[" << i << "][" << j << "] = " << f << "\n";
    }
  }
  L(i, 1, v) {
    ckmax(ans[i], ans[i - 1]);
    cout << ans[i] << " \n"[i == v];
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cin.exceptions(cin.failbit);

  int t;
  cin >> t;
  L(_, 1, t) {
    proc();
  }
}
```

---

