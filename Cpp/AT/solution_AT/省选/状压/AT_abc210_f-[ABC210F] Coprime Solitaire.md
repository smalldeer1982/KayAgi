# [ABC210F] Coprime Solitaire

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc210/tasks/abc210_f

テーブルの上に $ N $ 枚のカードが並んでいます。 $ i\ =\ 1,\ 2,\ \ldots,\ N $ について、$ i $ 枚目のカードの表には整数 $ A_i $ が、裏には整数 $ B_i $ が書かれています。  
 はじめ、すべてのカードは表が見えるように置かれています。

高橋君は好きな枚数（ $ 0 $ 枚でも良い）のカードを選んで裏返します。 その結果、以下の条件が満たされれば高橋君はうれしい気持ちになります。

- $ 1\ \leq\ i\ \lt\ j\ \leq\ N $ を満たす任意の整数のペア $ (i,\ j) $ について、$ i $ 枚目のカードの見えている面に書かれた整数と、$ j $ 枚目のカードの見えている面に書かれた整数が、互いに素である。

高橋君がうれしい気持ちになれる可能性があるかどうかを判定してください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 3\ \times\ 10^4 $
- $ 1\ \leq\ A_i,\ B_i\ \leq\ 2\ \times\ 10^6 $
- 入力はすべて整数

### Sample Explanation 1

はじめ、見えている整数は $ 2,\ 10,\ 4 $ です。 $ 1 $ 枚目のカードと $ 2 $ 枚目のカードを裏返すと、見えている整数は $ 5,\ 9,\ 4 $ となり、高橋君はうれしい気持ちになります。よって `Yes` を出力します。

### Sample Explanation 2

どのようにカードを裏返しても、高橋君はうれしい気持ちになりません。よって `No` を出力します。

## 样例 #1

### 输入

```
3
2 5
10 9
4 8```

### 输出

```
Yes```

## 样例 #2

### 输入

```
2
10 100
1000 10000```

### 输出

```
No```

# 题解

## 作者：VainSylphid (赞：5)

看到这种两面性的问题显然想到 2-SAT，不会 2-SAT 的先去做[这题](https://www.luogu.com.cn/problem/P4782)。

具体地，我们给每个质数设置一个集合，先把每一个数字都质因数分解，如果某个数有质因数 $p_i$，就把这个数的位置、是正面还是反面，加入 $p_i$ 对应的集合中。显然，对于某个数 $x$ 至多有 $\log x$ 级别的不同质因数。

这样一来一个集合中的数都不能同时共存，两两连边（若$x$ 则 $\neg y$）。
但是这样一来就要连 $O(n^2)$ 条边，显然时空都爆炸，于是我们想到前后缀优化连边。

对于每个集合，我们令 $x_i$ 为第 $i$ 个元素，$P_i$ 为前缀的反面“$\neg$”连边和，$Q_i$ 为后缀的反面“$\neg$”连边和。将 $P_i$ 和 $P_{i-1}$、$P_i$ 和 $\neg x_i$、$Q_i$ 和 $Q_{i+1}$、$Q_i$ 和 $\neg x_i$ 连边。
则对于 $x_i$，向 $P_{i-1}$ 和 $Q_{i+1}$ 连边，这样每个集合只用连 $O(n)$ 条边了。

总时间复杂度 $O(n \log w)$，其中 $w = \max(a_i,b_i)$。注意点和边的数目比较大，数组尽量开大点。

2024.9.23 修改了代码中的错误。

## 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	int nxt,v,val;
}e[3000005];
int n,d[60005],idx;
int p[200005],cntp,minp[2000005],qp[2000005];
bool f[2000005];
vector<int> t[2000005];
int cntg,h[1000005];
int dfn[1000005],low[1000005],cnt,s[1000005],sf[1000005],tp,scc[1000005],sc;
int fd(int w){return w > n ? w - n : w + n;}
void euler(int s)
{
	for(int i = 2;i <= s;i++)
	{
	    if(!f[i])
	        p[++cntp] = i,qp[i] = cntp,minp[i] = i;
	    for(int j = 1;j <= cntp && i * p[j] <= s;j++)
	    {
	    	f[i * p[j]] = true,minp[i * p[j]] = p[j];
	    	if(i % p[j] == 0)
	    	    break;
		}
	}
}
void addedge(int u,int v)
{
	e[++cntg] = {h[u],v},h[u] = cntg;
}
void tarjan(int u)
{
    low[u] = dfn[u] = ++cnt,s[++tp] = u,sf[u] = 1;
    for(int i = h[u];i;i = e[i].nxt)
	{
        if(!dfn[e[i].v])
            tarjan(e[i].v),low[u] = min(low[u],low[e[i].v]);
		else if(sf[e[i].v])
            low[u] = min(low[u],dfn[e[i].v]);
    }
    if(dfn[u] == low[u])
	{
        sc++;
        while(s[tp] != u)
            scc[s[tp]] = sc,sf[s[tp--]] = 0;
        scc[s[tp]] = sc,sf[s[tp--]] = 0;
    }
}
int main()
{
	euler(2000000);
	scanf("%d",&n),idx = n * 2;
	for(int i = 1;i <= n;i++)
	    scanf("%d%d",&d[i],&d[i + n]);
	for(int i = 1;i <= n * 2;i++)
	{
		int tmp = d[i];
		while(tmp > 1)
		{
			while(tmp / minp[tmp] % minp[tmp] == 0)
			    tmp /= minp[tmp];
			t[qp[minp[tmp]]].push_back(i),tmp /= minp[tmp];
		}
	}
	for(int i = 1;i <= cntp;i++)
	{
	    if(t[i].empty())
	        continue;
	    addedge(++idx,fd(t[i][0]));
		for(int j = 1;j < t[i].size();j++)
			addedge(t[i][j],idx++),addedge(idx,idx - 1),addedge(idx,fd(t[i][j]));
	    addedge(++idx,fd(t[i][t[i].size() - 1]));
		for(int j = t[i].size() - 2;j >= 0;j--)
			addedge(t[i][j],idx++),addedge(idx,idx - 1),addedge(idx,fd(t[i][j]));
	}
	for(int i = 1;i <= idx;i++)
	    if(!dfn[i])
	        tarjan(i);
	for(int i = 1;i <= n;i++)
        if(scc[i] == scc[i + n])
            printf("No"),exit(0);
    printf("Yes");
	return 0;
}
```

---

## 作者：hegm (赞：5)

### [[ABC210F] Coprime Solitaire](https://www.luogu.com.cn/problem/AT_abc210_f)

考虑对于值域范围内的每一个质数 $p$。

将所有 $a_i/b_i$ 能被当前质数整除的都找出来：

- 如果 $a_i$ 能被 $p$ 整除，那么我们将 $i$ 放入。

- 如果 $b_i$ 能被 $p$ 整除，那么我们将 $i+n$ 放入。

那么我们对于当前的整个数组 $c$ ，如果 $c_i$ 选了，那么 $\forall_{1\le j\le n\land j\ne i}\ \ c_j$ 这些就必须不能选。

所以对于某一个点 $i$ 我们要向所有的 $\neg c_j$ 连边。

容易发现这样的复杂度是 $n^2$ 的，所以我们考虑换一种连边方式，我们多添加 $n$ 个点 $f_{1\sim n}$。

其中 $f_i$ 向 $f_{i-1}$ 和 $\neg c_i$ 连边，特殊的 $f_1$ 只向 $\neg c_1$ 连边。

然后对于 $c_i$ 我们连边向 $f_{i-1}$。

容易发现我们的 $c_i$ 就可以间接指向 $\forall_{1\le j< i}\ \neg c_j$。

这就是前缀优化建边，同理我们可以搞出后缀优化建边，所以我们就可以在 $O(n)$ 的复杂度里面连出效果相同的边。

容易发现，我们直接筛出所有质数是行不通的，所以我们要对于每一个数进行质因数分解，对于每一个质因数，我们需要将他放入对应质因数的 `vector` 里面。

细节极多，需要仔细检查。

谢谢 @Maverik 的提醒，代码中有一处错误。

```cpp
#include<bits/stdc++.h>
#define M 2000005
#define int long long
using namespace std;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int n,cnt,mx,qwq,r[M],f[M],t[M],l[M],a[M],p[M],b[M],cwc,awa,low[M],dep,dfn[M],id[M];
stack<int> s;
vector<int> v[M];
bool lt[M],vis[M],pos[M];
struct fig
{
	int to,next;
}k[M*10];int tot,head[M];
void add(int from,int to)
{
	k[++tot].to=to;
	k[tot].next=head[from];
	head[from]=tot;
}
int xp(int x)
{
	if(x<=n)return x+n;
	else return x-n;
}
void tarjan(int now)
{
	s.push(now);
	dfn[now]=++dep;
	low[now]=dep;
	vis[now]=1;
	for(int i=head[now],to;i;i=k[i].next)
	{
		to=k[i].to;
		if(!dfn[to])tarjan(to);
		if(vis[to])low[now]=min(low[now],low[to]);
	}
	if(dfn[now]==low[now])
	{
		id[now]=now;
		vis[now]=0;
		int to=s.top();
		s.pop();
		while(to!=now)
		{
			vis[to]=0;
			id[to]=now;
			to=s.top();
			s.pop();
		}
	}
}
signed main()
{
	n=read();qwq=n*2;
	for(int i=1;i<=n;i++)
	{
		a[i]=read();
		b[i]=read();
		mx=max({mx,a[i],b[i]});
	}
	memset(lt,1,sizeof(lt));
	lt[1]=0;
	for(int i=1;i<=mx;i++)
	{
		if(lt[i]==1)l[++cnt]=i;
		for(int j=1;j<=cnt&&i*l[j]<=mx;j++)
		{
			lt[i*l[j]]=0;
			if(i%l[j]==0)break;
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1,con=sqrt(a[i]);j<=con;j++)
		{
			if(a[i]%j==0)
			{
				if(lt[j])v[j].push_back(i);
				if(lt[a[i]/j]&&a[i]!=j*j)v[a[i]/j].push_back(i);
			}
		}
		for(int j=1,con=sqrt(b[i]);j<=con;j++)
		{
			if(b[i]%j==0)
			{
				if(lt[j]==1)v[j].push_back(i+n);
				if(lt[b[i]/j]&&b[i]!=j*j)v[b[i]/j].push_back(i+n);
			}
		}
	}
	for(int i=1;i<=mx;i++)if(pos[i])p[++cwc]=i;
	for(int i=1;i<=cnt;i++)
	{
		awa=v[l[i]].size();
		if(!awa)continue;
		f[1]=++qwq;add(f[1],xp(v[l[i]][0]));
		for(int j=2;j<=awa;j++)
		{
			f[j]=++qwq;
			add(f[j],f[j-1]);
			add(f[j],xp(v[l[i]][j-1]));
			add(v[l[i]][j-1],f[j-1]);
		}
		t[awa]=++qwq;add(t[awa],xp(v[l[i]][awa-1]));
		for(int j=awa-1;j>=1;j--)
		{
			t[j]=++qwq;
			add(t[j],t[j+1]);
			add(t[j],xp(v[l[i]][j-1]));
			add(v[l[i]][j-1],t[j+1]);
		}
	}
	for(int i=1;i<=qwq;i++)if(!dfn[i])tarjan(i);
	for(int i=1;i<=n;i++)
	{
		if(id[i]==id[i+n])
		{
			cout<<"No\n";
			return 0;
		}
	}
	cout<<"Yes\n";
	return 0;
}
```

---

## 作者：CQ_Bab (赞：1)

# 思路
首先发现可以 2-SAT，但是如果暴力的话是 $n^2$ 的考虑优化，发现对于一对值 $x,y$ 如果不能在一起出现当且仅当存在 $p\in prime$ 并且 $x\bmod p=0$ 且 $y\bmod p=0$ 那么我们考虑枚举质因数 $p$ 然后统计出他的倍数集合（并且在序列中出现过）$v$，然后我们发现对于 $v$ 中的一个点 $x$ 会联想 $v$ 中其他点的不选的状态，这是一个裸的前缀和后缀直接前缀优化建边即可。

而点大致就是选 $a_i$ 的编号为 $i$ 不选 $a_i$ 为 $i+n$ 而选 $b_i$ 为 $i+2\times n$  不选 $b_i$ 为 $i+3\times n$，而首先连上 $i+n\to i+2\times n$ 和 $i+3\times n\to i$ 即可。

前缀优化建图大致就是对于每一个前缀新建一个 $x_i$ 然后连向 $x_{i-1}$ 又连上 $id_{i}$ 即可，后缀优化建边也大致一样。
# 代码
细节见代码。
```cpp
int T=1;
const int M=2e6+10,N=1e6+10;
int vis[M];
vector<int>pr,v[N];
int n;
stack<int>s;
int dfn[N],low[N],is[N],val[N],cnt,tot;
void tarjan(int x) {
	dfn[x]=low[x]=++tot;
	is[x]=1;
	s.push(x);
	for(auto to:v[x]) {
		if(!dfn[to]) {
			tarjan(to);
			low[x]=min(low[x],low[to]);
		}else if(is[to]) low[x]=min(low[x],dfn[to]);
	}
	if(low[x]==dfn[x]) {
		int p;
		cnt++;
		do{
			p=s.top();
			s.pop();
			val[p]=cnt;
			is[p]=0;
		}while(p!=x);
	}
}
int idx,a[N],b[N];
void add(int x,int y) {
	v[x].pb(y);
}
void init() {
	rep(i,2,M-10) {
		if(!vis[i]) {
			pr.pb(i);
			rep(j,2,(M-10)/i) {
				vis[i*j]=1;
			}
		}
	}
}
vector<int>vv[M];
int zheng[N],fan[N];
int rev(int x) {
	return x+n;
}
void solve() {
	init();
	in(n);
	rep(i,1,n) in(a[i]),in(b[i]),vv[a[i]].pb(i),vv[b[i]].pb(i+n*2);
	idx=4*n;
	rep(i,1,n) {
		add(i+n,i+2*n);
		add(i+3*n,i);
	}
	for(auto to:pr) {
		vector<int>ve;
		rep(i,1,(M-10)/to) {
			for(auto to1:vv[i*to]) {
				ve.pb(to1);
			}
		}
		if(ve.size()<=1) continue;
		int lst=0,cc=0;
		for(auto to:ve) {
			idx++;
			zheng[cc++]=idx;
			add(idx,rev(to));
			if(lst) add(idx,lst);
			lst=idx;
		}
		reverse(ve.begin(),ve.end());
		lst=cc=0;
		for(auto to:ve) {
			idx++;
			fan[cc++]=idx;
			add(idx,rev(to));
			if(lst) add(idx,lst);
			lst=idx;
		}
		reverse(ve.begin(),ve.end());
		rep(i,0,ve.size()-1) {
			if(i!=0) add(ve[i],zheng[i-1]);
			if(i!=ve.size()-1) add(ve[i],fan[ve.size()-1-i-1]);
		}
	}
	rep(i,1,idx) if(!dfn[i]) tarjan(i);
	rep(i,1,n) {
		if(val[i]==val[i+n]||val[i+2*n]==val[i+3*n]) {
			cout<<"No\n";
			return;
		}
	}cout<<"Yes\n";
}
fire main() {
	while(T--) {
		solve();
	}
	return false;
}
```

---

## 作者：To_our_starry_sea (赞：1)

### solution

似乎其他题解只是讲述方法，对前缀优化建图的原理讲的有点含糊？

首先对于这样的两面状态的问题，我们很容易想到 2-SAT 模型（当然还有一部分题目是最小割）。

我们筛出所有 $a_i$ 与 $b_i$ 的质因子，注意由于值域的问题，我们不能枚举所有的因子，也不能根号枚举，否则时空复杂度都是爆炸的。考虑每个数至多有 $O(\log n)$ 个质因子，所以这是可以接受的。

接下来我们发现问题规约到对于每个在值域范围内的质数，所有能被其整除的 $a_i$ 和 $b_i$ 的下表位置的集合中***至多***只能有 $1$ 个为该面朝上。

更一般的，考虑这样一个问题：对于一个长度为 $n$ 的布尔数组 $x_i$，要求区间 $[1,n]$ 内至多只有 $1$ 个数状态为 $1$ 的合法性判定。

容易的，发现其本质为 $\forall i, j \in [1,n],x_i \bigwedge x_j = 0$，而直接建图的复杂度为 $O(n^2)$，显然无法接受。

考虑前缀优化，在既有状态节点 $x_i$ 的基础上建立 $y_i$ 作为辅助节点，表示 $[1,i]$ 的区间内是否有状态为 $1$ 的数。

考虑连边，发现将 $x_i$ 向 $y_i$ 连边，表示由 $x_i = 1$ 可以推导出已经存在状态为 $1$ 的数，同时由 2-SAT 问题的建图的对称性可知，应该由 $y_i'$ 向 $x_i'$ 连边。同时若区间 $[1,i]$ 内存在点状态为 $1$，则区间 $[1,i+1]$ 内同样存在点是的状态为 $1$，因此由 $y_i$ 向 $y_{i+1}$ 连边，$y_{i+1}'$ 向 $y_i'$ 连边。最后，如果区间 $[1,i]$ 内存在状态为 $1$ 的数，则第 $i + 1$ 个数的状态必然不为 $1$，否则不合法，因此由 $y_i$ 向 $x_{i + 1}'$ 连边。容易发现这样建边与上文方式等价，且边数为 $O(n)$ 的。

最后跑完 tarjan 之后只需要判定 $x_i$ 和 $x_i'$ 是否在一个 scc 之中即可。

因此回到本题，设 $a_i$ 朝上的状态为 $x_i$，$b_i$ 朝上的状态为 $x_i'$，问题便可以按如上方式解决。

注意代码实现的方式与上文所述略有不同。

### Code


```cpp
#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define F(x) (x > n ? x - n : x + n)
const int MAXN = 3000005;
int n, m, T = 0, maxn = 0, cnt = 0, tot = 0, num = 0, head[MAXN];
int a[MAXN], b[MAXN], pd[MAXN], dfn[MAXN], low[MAXN], ins[MAXN], col[MAXN];
struct edge{
    int next,to;
} e[MAXN << 1];
vector<int> p[MAXN], w[MAXN];
stack<int> s;
inline void tarjan(int u) {
    dfn[u] = low[u] = ++num, ins[u] = 1, s.push(u);
    for (int i = head[u]; i; i = e[i].next) {
    	int v = e[i].to;
    	if (!dfn[v]) tarjan(v), low[u] = min(low[u], low[v]);
    	else if(ins[v]) low[u] = min(low[u], dfn[v]);
    }
    if (dfn[u] == low[u]) {
        int v;
        num++;
		do{
		   v = s.top();
		   s.pop();
		   ins[v] = 0, col[v] = num;
	    } while(u != v);
    }
}
inline void add(int u,int v) {
    cnt++;
	e[cnt].to = v;
	e[cnt].next = head[u];
	head[u] = cnt;	
}
inline int read() {
	int x = 0, f = 1; char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-')
		   f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar();
	return x * f;
}
int main(){
    n = read();
    for (int i = 1; i <= n; i++) a[i] = read(), b[i] = read(), maxn = max(maxn, max(a[i], b[i]));
    for (int i = 2; i <= maxn; i++) {
    	if (pd[i]) continue;
    	for (int j = i; j <= maxn; j += i) pd[j] = 1, p[j].push_back(i);
	}
    for (int i = 1; i <= n; i++) {
    	for (auto v : p[a[i]]) w[v].push_back(i);
    	for (auto v : p[b[i]]) w[v].push_back(i + n);
	}
	T = 2 * n;
    for (int i = 1; i <= maxn; i++) {
    	if (!w[i].size()) continue;
    	add(++T, F(w[i][0]));
    	for (int j = 1; j < (int)w[i].size(); j++) {
    		add(w[i][j], T), T++;
    		add(T, T - 1);
    		add(T, F(w[i][j]));
		}
		add(++T, F(w[i][w[i].size() - 1]));
		for (int j = w[i].size() - 2; j >= 0; j--) {
			add(w[i][j], T), T++;
			add(T, T - 1);
			add(T, F(w[i][j]));
		}
    }
    for (int i = 1; i <= T; i++) {
    	if (!dfn[i]) tarjan(i);
	}
	for (int i = 1; i <= n; i++) {
		if (col[i] == col[i + n]) {
			puts("No");
			return 0;
		}
	}
	puts("Yes");
    return 0;
}
```

---

## 作者：Exp10re (赞：0)

2-SAT 建图好题。

## 解题思路

考虑到每一张卡片要么正面要么反面，故使用 2-SAT。

记第 $i$ 张卡片正面状态为 $x_i$，反面状态为 $x_{i+n}$。

首先每一张卡片正反互斥，因此连边 $\neg x_i\rightarrow x_{i+n},\neg x_{i+n}\rightarrow x_i$。

然后考虑在何种情况下所有朝上卡片两两互质：注意到满足两两互质的充分必要条件是对于每一个质数 $p$，至多只有一张朝上卡片拥有该质因子。

建立多个集合，集合 $S_p$ 内有所有含有质因子 $p$ 的卡片编号。问题转变为每一个集合中至多只有一张卡片朝上。

显然有 $O(n^2)$ 的连边方式，但是复杂度难以接受。

想使用二元约束条件来表示 $x_{1,\cdots,m}$ 中至多有一个 $1$，有一个很典的 Trick，即前缀优化建图。具体而言，建立虚点 $y_{1,\cdots,m}$，并按以下方式连边：

$$\begin{aligned}
x_i &\rightarrow y_i \\
y_{i-1} &\rightarrow y_i \\
y_{i-1} &\rightarrow \neg x_i \\
\end{aligned}$$

你可以等价理解为 $y_i=x_i$ 的前缀或，并且第一个 $x_i=1$ 之后所有 $x_j(j\gt i)$ 在以上限制条件规约下都为 $0$。

用以上方式规约每一个集合内的卡片编号，总共会连 $O(n\log V)$ 条边。

故 2-SAT 的时间复杂度为 $O(n\log V)$，可以通过。

建议先筛出每一个值域内的数的最小质因数。传统的根号筛法很容易导致超时。

---

## 作者：shinkuu (赞：0)

~~看到这题不知道为什么第一反应是 flow。~~

先把每个数质因数分解，然后问题就变成了让选出的集合无交。

如果此时像我一样，发现是分成两个集合，就往最小割的方向想，就到死路了。主要是最小割就要求每两个不互质的数间都要加一个限制，无法优化。

事实上，注意到每个位置只有两种选择，抽象成选 $0/1$，就应该马上联想到 2-sat。建图方式就是如果 $A_i,B_j$ 不互质，则连 $i\to j$，$A_i,A_j$ 不互质则连 $i\to j+n$，其他同理。

发现这样还是会有 $O(n^2)$ 条边，于是优化建图，对于每一个质数开若干个虚点优化。注意不能直接每个质数开一个虚点然后对应着连，因为这样会导致 $i$ 一定能走到自己。正确的优化方式应该是对前缀/后缀分别进行前缀/后缀优化建图。

然后就 2-sat 常规跑一遍 tarjan 就行了。

code：

```cpp
int n,m,cur,pm[N],f[N],id[N];
int idx,top,st[N],dfn[N],low[N];
int k,c[N],g[N];
vector<int> a[M],b[M];
bool vis[N];
int tot,head[N];
struct node{
	int to,nxt;
}e[N<<1];
il void add(int u,int v){
	e[++tot]={v,head[u]},head[u]=tot;
}
void tarjan(int u){
	dfn[u]=low[u]=++idx;
	st[++top]=u;
	vis[u]=1;
	go(i,u){
		int v=e[i].to;
		if(!dfn[v]){
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}else if(vis[v]){
			low[u]=min(low[u],dfn[v]);
		}
	}
	if(low[u]==dfn[u]){
		k++;
		do{
			int v=st[top];
			c[v]=k;
			vis[v]=0;
		}while(st[top--]!=u);
	}
}
void Yorushika(){
	scanf("%d",&n);
	rep(i,1,n){
		int x,y;scanf("%d%d",&x,&y);
		int lst=0;
		while(x>1){
			if(f[x]!=lst){
				a[i].eb(id[f[x]]);
			}
			lst=f[x],x/=f[x];
		}
		lst=0;
		while(y>1){
			if(f[y]!=lst){
				b[i].eb(id[f[y]]);
			}
			lst=f[y],y/=f[y];
		}
	}
	cur=n+n;
	rep(i,1,n){
		for(int j:a[i]){
			if(g[j]){
				add(i,g[j]);
			}
		}
		for(int j:b[i]){
			if(g[j]){
				add(i+n,g[j]);
			}
		}
		for(int j:a[i]){
			cur++;
			if(g[j]){
				add(cur,g[j]);
			}
			add(g[j]=cur,i+n);
		}
		for(int j:b[i]){
			cur++;
			if(g[j]){
				add(cur,g[j]);
			}
			add(g[j]=cur,i);
		}
	}
	mems(g,0);
	drep(i,n,1){
		for(int j:a[i]){
			if(g[j]){
				add(i,g[j]);
			}
		}
		for(int j:b[i]){
			if(g[j]){
				add(i+n,g[j]);
			}
		}
		for(int j:a[i]){
			cur++;
			if(g[j]){
				add(cur,g[j]);
			}
			add(g[j]=cur,i+n);
		}
		for(int j:b[i]){
			cur++;
			if(g[j]){
				add(cur,g[j]);
			}
			add(g[j]=cur,i);
		}
	}
	mems(vis,0);
	rep(i,1,cur){
		if(!dfn[i]){
			tarjan(i);
		}
	}
	rep(i,1,n){
		if(c[i]==c[i+n]){
			puts("No");
			return;
		}
	}
	puts("Yes");
}
signed main(){
	int mx=2e6;
	rep(i,2,mx){
		if(!vis[i]){
			pm[++m]=i,id[i]=m;
			f[i]=i;
		}
		rep(j,1,m){
			if(pm[j]>mx/i){
				break;
			}
			vis[i*pm[j]]=1;
			f[i*pm[j]]=pm[j];
			if(i%pm[j]==0){
				break;
			}
		}
	}
	int t=1;
	//	scanf("%d",&t);
	while(t--)
		Yorushika();
}
```

---

