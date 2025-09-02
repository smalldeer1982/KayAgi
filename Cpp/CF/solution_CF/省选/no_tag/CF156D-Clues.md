# Clues

## 题目描述

As Sherlock Holmes was investigating another crime, he found a certain number of clues. Also, he has already found direct links between some of those clues. The direct links between the clues are mutual. That is, the direct link between clues $ A $ and $ B $ and the direct link between clues $ B $ and $ A $ is the same thing. No more than one direct link can exist between two clues.

Of course Sherlock is able to find direct links between all clues. But it will take too much time and the criminals can use this extra time to hide. To solve the crime, Sherlock needs each clue to be linked to all other clues (maybe not directly, via some other clues). Clues $ A $ and $ B $ are considered linked either if there is a direct link between them or if there is a direct link between $ A $ and some other clue $ C $ which is linked to $ B $ .

Sherlock Holmes counted the minimum number of additional direct links that he needs to find to solve the crime. As it turns out, it equals $ T $ .

Please count the number of different ways to find exactly $ T $ direct links between the clues so that the crime is solved in the end. Two ways to find direct links are considered different if there exist two clues which have a direct link in one way and do not have a direct link in the other way.

As the number of different ways can turn out rather big, print it modulo $ k $ .

## 说明/提示

The first sample only has two clues and Sherlock hasn't found any direct link between them yet. The only way to solve the crime is to find the link.

The second sample has three clues and Sherlock hasn't found any direct links between them. He has to find two of three possible direct links between clues to solve the crime — there are $ 3 $ ways to do it.

The third sample has four clues and the detective has already found one direct link between the first and the fourth clue. There are $ 8 $ ways to find two remaining clues to solve the crime.

## 样例 #1

### 输入

```
2 0 1000000000
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3 0 100
```

### 输出

```
3
```

## 样例 #3

### 输入

```
4 1 1000000000
1 4
```

### 输出

```
8
```

# 题解

## 作者：xht (赞：43)

# 请在博客中查看

设 $s_i$ 为第 $i$ 个连通块的点数，$d_i$ 为第 $i$ 个连通块的度数。

对于给定的 $d$ 序列构造 Prufer 序列的方案数为：

$$
\binom{k-2}{d_1-1,d_2-1,\cdots,d_k-1}=\frac{(k-2)!}{(d_1-1)!(d_2-1)!\cdots(d_k-1)!}
$$

对于给定的 $d$ 序列使图连通的方案数为：

$$
\binom{k-2}{d_1-1,d_2-1,\cdots,d_k-1}\cdot\prod_{i=1}^k{s_i}^{d_i}
$$

枚举 $d$ 序列使图连通的方案数为：

$$
\sum_{d_i\ge 1,\sum_{i=1}^kd_i=2k-2}\binom{k-2}{d_1-1,d_2-1,\cdots,d_k-1}\cdot\prod_{i=1}^k{s_i}^{d_i}
$$

设 $e_i=d_i-1$：

$$
\sum_{e_i\ge 0,\sum_{i=1}^ke_i=k-2}\binom{k-2}{e_1,e_2,\cdots,e_k}\cdot\prod_{i=1}^k{s_i}^{e_i+1}
$$

考虑多元二项式定理：

$$
(x_1 + \dots + x_m)^p = \sum_{c_i \ge 0,\sum_{i=1}^m c_i = p}\binom{p}{c_1, c_2, \cdots ,c_m}\cdot \prod_{i=1}^m{x_i}^{c_i}
$$

原式变为：

$$
(s_1+s_2+\cdots+s_k)^{k-2}\cdot\prod_{i=1}^ks_i
$$

即：

$$
n^{k-2}\cdot\prod_{i=1}^ks_i
$$

```cpp
const int N = 1e5 + 7;
int n, m, k, f[N], s[N];
modint ans = 1;

int get(int x) {
	return x == f[x] ? x : (f[x] = get(f[x]));
}

int main() {
	rd(n), rd(m), rd(P);
	if (P == 1) return print(0), 0;
	for (int i = 1; i <= n; i++) f[i] = i;
	for (int i = 1, x, y; i <= m; i++) rd(x), rd(y), f[get(x)] = get(y);
	for (int i = 1; i <= n; i++) ++s[get(i)];
	for (int i = 1; i <= n; i++) if (i == get(i)) ++k, ans *= s[i];
	if (k == 1) return print(1), 0;
	print(ans *= (modint)n ^ (k - 2));
	return 0;
}
```

---

## 作者：福州周圣力 (赞：11)

## 写在前面

对于树形态的计数问题，一种常用的解题思路是借助 [Prufer 序列](https://oi-wiki.org/graph/prufer/)将树和组合数联系在一起。

## 算法一

如果原图是一棵树，那么根据 Cayley 公式：答案为 $n^{n-2}$。

## 算法二

如果把每一个连通块看成一个点，那么总的连边方案为 $n^{k-2}$（由于要连 $k-1$ 条边，所以 Prufer 序列的长度为 $k-2$，又因为在每一位上填一个 $1\sim n$ 的数所形成的 Prufer 序列都有意义，所以根据乘法原理得出答案为 $n^{k-2}$）。

但是仅仅构造出 Prufer 序列是不够的，要用 Prufer 序列对树的形态数量进行计算还需要证明 Prufer 序列的数量与树的形态的数量之间的关系（例如对于一般的树，两者之间的关系是一一对应）。

考虑[用 Prufer 序列重建树](https://oi-wiki.org/graph/prufer/#prufer_3)的过程，每次我们都会将 Prufer 序列的最前面的一个点  $u$ 拿出来进行连边，但是我们并不知道与 $u$ 连边的会是连通块内的哪一个点，所以选定一个连通块内与 $u$ 连边的点会使答案乘上 $s_i$（即连通块的大小）。

综上所述，最终的答案为 $n^{k-2}\times \prod\limits_{i=1}^k s_k$。

## [参考代码](https://codeforces.com/contest/156/submission/86086658)

```cpp
#include<cstdio>
using namespace std;int p,f[100005],sz[100005];
int ff(int x) {return x==f[x]?x:f[x]=ff(f[x]);}
inline int qpow(int a,int b) {int rtv=1;
	for (;b;b>>=1,a=1LL*a*a%p) if (b&1) rtv=1LL*rtv*a%p;
	return rtv;
}int main() {int n,m,u,v,ans=1,cnt=0;scanf("%d%d%d",&n,&m,&p);
	for (register int i=1;i<=n;++i) f[i]=i,sz[i]=1;
	for (register int i=1;i<=m;++i) {scanf("%d%d",&u,&v);
		int fu=ff(u),fv=ff(v);if (fu^fv) f[fu]=fv,sz[fv]+=sz[fu];
	}for (register int i=1;i<=n;++i) if (f[i]==i) ++cnt,ans=1LL*ans*sz[i]%p;
	printf("%I64d",cnt<2?1%p:1LL*ans*qpow(n,cnt-2)%p);return 0;
}
```

---

## 作者：shao0320 (赞：5)

考虑共有$k$个连通块，第$i$个联通块的大小为 $s_i$ ，在最终生成的树的度数为 $d_i$ 的方案数。

对应到prufer序列上就是
$$
{k-2\choose d_1-1,d_2-1\cdots d_k-1}\prod {{s_i}^{d_i}}=\frac{(k-2)!}{\prod (d_i-1)!}\prod {{s_i}^{d_i}}
$$
看到这个$d_i-1$的形式似乎不是很优美，设$f_i=d_i-1$，即
$$
{k-2\choose e_1,e_2,\cdots ,e_k}\prod{s_i^{e_i+1}}
$$
这是个多项式定理的形式，多项式定理即为项数多于 $1$ 的情况下
$$
(x_1+x_2+\cdots+x_t)^m=\sum_{\sum n_i=t}{{t\choose n_1,n_2,\cdots,n_t}}\prod x_i^{n_i}
$$
$n_i$ 为 $x_i$ 这项的系数，一个比较简单的证明：从 $m$ 项中选择 $n$ 个数，那么组合为 $(n_1,n_2,\cdots,n_t)$的方案就有 
$$
t\choose n_1,n_2,\cdots,n_t
$$
种，每种权值为 $\prod x_i^{n_i}$。

由于$\sum s_i=n$于是原式即可化为 
$$
n^{k-2}\prod s_i
$$


---

## 作者：Inui_Sana (赞：4)

~~whk 考试前写题解攒 rp 有用吗~~

仍然是讲讲想出来的过程。

首先，我们只需要关心一个联通块中有哪些点，而不用关心图的具体形态。

然后，将每个连通块看作一个点，就变成了一个无根树计数问题，但是带权值。首先想到 prufer 序列。

>prufer 序列的定义：一棵无根树中，每次将编号最小的叶子取出来，将和它相连的点编号加入序列，然后删掉这个叶子。重复操作知道剩下的点只有两个，其中有一个一定是 $n$。形成的序列就是 prufer 序列。

然后发现我们可以参考无根树计数的方法来尝试计数。

>无根树计数方法：发现 prufer 序列中每个位置都可以取到 $[1,n]$ 内的所有数，所以方案数即为 $n^{n-2}$。

发现带权之后，设第 $i$ 个联通块大小为 $c_i$，则确定一个 prufer 序列 $P$ 后，连边方案数分成两部分。下文 $k$ 定义按照翻译。

- 第一部分，对于每个连通块，选择它记录 prufer 序列时，被删去时，和它相连的连通块中的一个点。这部分的方案数为 $\prod_{i\le k-2}c_{P_i}\times c_k$。后面要乘上 $c_k$ 的原因是最后剩的两个点还要计算一次。

- 第二部分，对于每个连通块，选择它记录 prufer 序列时，被删去时，它连向相连连通块的那条边，所连的这个连通块的一个点。这部分的方案数是 $\prod_{i\le k-1}c_i$，原因显然。

所以乘起来即为 $\prod_{i\le k-2}c_{P_i}\times \prod_{i\le k}c_i$。

但是我们还不知道 prufer 序列长什么样，但是发现这是经典的问题：在若干个集合中各选一个元素相乘，所有乘积之和。这个和就是所有集合内元素之和之积。

回到原题中，每个集合的和都是 $n$，所以最后答案即为 $n^{k-2}\times\prod_{i\le k}c_i$。

别忘了 $k=1$。

同时别忘了 $mod=1$。

code：

```cpp
int n,m,mod,c[N];
struct DSU{
	int fa[N];
	void init(){rep(i,1,n)fa[i]=i;}
	il void merge(int x,int y){fa[find(x)]=find(y);}
	int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
}T;
il int qpow(int x,int y){
	int ret=1;
	while(y){
		if(y&1)ret=1ll*ret*x%mod;
		x=1ll*x*x%mod,y>>=1;
	}
	return ret;
}
void Yorushika(){
	scanf("%d%d%d",&n,&m,&mod);
	T.init();
	rep(i,1,m){
		int u,v;scanf("%d%d",&u,&v);
		T.merge(u,v);
	}
	rep(i,1,n)c[T.find(i)]++;
	int ans=1,cnt=0;
	rep(i,1,n)if(c[i])ans=1ll*ans*c[i]%mod,cnt++;
	if(cnt==1)puts(mod==1?"0":"1");
	else printf("%lld\n",1ll*ans*qpow(n,cnt-2)%mod);
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)
		Yorushika();
}
```

---

## 作者：BBD186587 (赞：4)

记原图的连通块数为 $k$，各个连通块的大小为 $c_i$。

把两个连通块连起来的方案数显然为 $c_ic_j$，确定树的形态后，连出来的方案数就是把每条边的方案数乘起来。

把连通块看作点。把边权摊到点上。记最终的树上第 $i$ 个连通块的度数为 $d_i$，那么它对答案的贡献就是 $c_i^{d_i}$。

考虑 prufer 序列以保证可以连成一棵树。一个点每在 prufer 序列上出现一次，对答案的贡献就是 $c_i$。因为一个度数为 $x$ 的点只会在 prufer 序列上出现 $x-1$ 次，所以还需要额外算一次贡献。

最终的答案就是 $\prod c_i \times (\sum c_i)^{k-2}=\prod c_i \times n^{k-2}$。

---

## 作者：Karry5307 (赞：4)

### 题意

给定一张 $n$ 个点 $m$ 条边的无向图，设最少加 $k$ 条边能使图联通，求加 $k$ 条边使图联通的方案数，对 $p$ 取模。

$\texttt{Data Range:}1\leq n\leq 10^5$，$0\leq m\leq 10^5$。

### 题解

简单题。

一个很明显的想法是将每一个连通块内的点缩成一个，权值为这个连通块的点数，于是只需要求这个新图中连 $k$ 条边连成树的权值和。

设每个点权值为 $w_i$，考虑如何计算树的权值。对于每一条树边 $(u,v)$，对答案的贡献为 $w_uw_v$，所以如果设每个点的度数为 $d_i$，一棵树的权值为 $\prod w_i^{d_i}$。

对于度数的问题自然考虑 Prufer 序列，设新的 $d_i$ 为原来的 $d_i-1$，则答案为

$$\sum_{d_1+\cdots+d_n=n-2}\binom{n-2}{d_1,\cdots,d_n}w_i^{d_i+1}$$

显然是卷积的形式，将一个 $w_i$ 提出来之后即

$$(n-2)!\prod w_i\sum_{d_1+\cdots+d_n=n-2}\frac{w_i^{d_i}}{d_i!}$$

右边很明显可以用 GF 表示，即

$$(n-2)!\prod w_i[x^{n-2}]e^{\sum w_ix}$$

即

$$\prod w_i\left(\sum w_i\right)^{n-2}$$

直接做即可。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
typedef long long int li;
const ll MAXN=2e5+51;
ll n,m,MOD,u,v,totd,prod;
ll ffa[MAXN],bel[MAXN],sz[MAXN];
inline ll read()
{
    register ll num=0,neg=1;
    register char ch=getchar();
    while(!isdigit(ch)&&ch!='-')
    {
        ch=getchar();
    }
    if(ch=='-')
    {
        neg=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        num=(num<<3)+(num<<1)+(ch-'0');
        ch=getchar();
    }
    return num*neg;
}
inline ll qpow(ll base,ll exponent)
{
    ll res=1;
    while(exponent)
    {
        if(exponent&1)
        {
            res=(li)res*base%MOD;
        }
        base=(li)base*base%MOD,exponent>>=1;
    }
    return res;
}
inline ll find(ll x)
{
	return x==ffa[x]?x:ffa[x]=find(ffa[x]);
}
int main()
{
	n=read(),m=read(),MOD=read(),prod=1;
	for(register int i=1;i<=n;i++)
	{
		ffa[i]=i;
	}
	for(register int i=1;i<=m;i++)
	{
		u=find(read()),v=find(read()),u!=v?ffa[v]=u:1;
	}
	for(register int i=1;i<=n;i++)
	{
		find(i)==i?bel[i]=++totd:1;
	}
	if(totd==1)
	{
		return puts(MOD==1?"0":"1"),0;
	}
	for(register int i=1;i<=n;i++)
	{
		sz[bel[find(i)]]++;
	}
	for(register int i=1;i<=totd;i++)
	{
		prod=(li)prod*sz[i]%MOD;
	}
	printf("%d\n",(li)prod*qpow(n,totd-2)%MOD);
}
```

---

## 作者：Purslane (赞：3)

# Solution

提供一种非常简介的推导方式。

考虑给每个连通块赋一个优先级，用来生成 Prufer 序列。

缩点之后，我们学习 Prufer 序列的构建方式，每次删掉**优先级最小**的叶子节点，并且把**这个叶子节点和它父节点连边在原树上对应的另一个端点**加入新的序列之中。

容易发现这样 Prufer 序列长度应该为 $n-1$，因为第 $n-1$ 个数只知道在哪个连通块里面，但是并不知道具体是哪个节点。

这样 Prufer 序列的个数为 $n^{k-2} \times sze_{rt}$，$rt$ 是优先级最大的连通块。

注意到除了 $rt$ 以外的每一个连通块和它父亲的连边的、属于自己的端点有 $s_u$ 种可能，他们都要乘到答案之中去。

所以答案是：

$$
n^{k-2} \times \prod sze_u
$$

$k$ 为连通块个数。$sze$ 为每个连通块的大小。

特判 $k=1$ 的情况。

---

## 作者：Str_ywr (赞：2)

思路和其他题解不完全一样，没有那么多推式子的东西。

首先，可以把每个连通块缩成一个点，并记录 $sz_i$ 表示第 $i$ 个连通块的大小。假设现在有 $k$ 个连通块。

那么连接剩下的就相当于一个连接一个有标号无根树，根据 $prufer$ 序列，所有长度为 $k-2$ 的序列和这个对应。

那么考虑一种固定的树在原图中有多少种连边方式。我们考虑树上的一条边 $(u,v)$，它的贡献是 $sz_i \times sz_v$，这个树的总贡献，就是所有边的贡献乘积。这个就相当于是每个块的 $sz_i$ 的度数次方的乘积。

度数等于在序列出现次数 $+1$，我们可以把 $+1$ 提取出来。

那么就转化成了在序列中出现的次数。

考虑 $dp_i$, 表示长为 $i$ 的序列的所有可能情况的答案总和，发现每一次转移只需要枚举一下这个位置是几，$dp_j = \sum_{i=1}^{i\le n} dp_{j-1} \times sz_i$，这个其实就相当于是上一次的 $\times n$。

所以答案就是 $n^{k-2} \times sum$, 其中 $sum$ 就是把 $+1$ 提取出来的答案，也就是 $\prod sz_i$。

最后还要记得特判整个图连通的情况。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
ll n, m, mod; int fa[N], sz[N];
int getfa(int x) {
	return x == fa[x] ? x : fa[x] = getfa(fa[x]);
}
ll sum = 1, cnt;
ll qpow(ll x, ll y) {
	ll ans = 1;
	while (y) {
		if (y & 1) ans = (ans * x) % mod;
		y >>= 1; x = (x * x) % mod;
	}
	return ans;
}
int main() {
	cin >> n >> m >> mod;
	for (int i = 1; i <= n; i++) fa[i] = i, sz[i] = 1;
	for (int i = 1; i <= m; i++) {
		int u, v; scanf("%d%d", &u, &v);
		int xx = getfa(u), yy = getfa(v);
		if (xx != yy) {
			fa[xx] = yy; sz[yy] += sz[xx];
		}
	}
	for (int i = 1; i <= n; i++) {
		if (getfa(i) == i) {
			sum = (sum * sz[i]) % mod; cnt++;
		}
	}
	if (cnt == 1) {
		cout << 1 % mod; return 0; //!!!!!mod可能是1 
	}
	sum = (sum * qpow(n, cnt - 2)) % mod;
	cout << sum;
}
```


---

## 作者：Richard_Whr (赞：1)

为啥没人用生成函数解释。

总共有 $m$ 个联通块，显然 $m=1$ 的时候答案为 $1$，需要特判。

对第 $k$ 个联通块，设他的大小为 $s_k$，写出他的生成函数（EGF）：

$$F_k(x)=\sum\limits_{i}\frac{s_k^{i+1}}{i!}\times x^i$$

提出一个 $s_k$，得到更优美的形式：

$$\frac{F_k(x)}{s_k}=\sum\limits_{i}\frac{s_k^{i}}{i!}\times x^i$$

根据 EGF 的一些基本内容，右边的东西的封闭形式就是 $e^{s_kx}$。

完后我们要求的东西是：

$$
\begin{align*}

  [x^{m-2}]\prod\limits_{k}F_k(x)&=\prod s_i \times [x^{m-2}]e^{\sum\limits_{k}s_k\times x}\\

  &=\prod s_i \times [x^{m-2}]e^{n\times x} \\

  &=\prod s_i \times n^{m-2} \\

\end{align*}
$$

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
int p[N],sz[N];
int n,m,mod;

int find(int x)
{
	if(p[x]!=x) return p[x]=find(p[x]);
	return p[x];
}

void merge(int x,int y)
{
	x=find(x),y=find(y);
	if(x==y) return;
	p[x]=y,sz[y]+=sz[x];
}

signed main()
{
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	
	cin>>n>>m>>mod;
	for(int i=1;i<=n;i++) p[i]=i,sz[i]=1;
	
	for(int i=1,x,y;i<=m;i++)
	{
		cin>>x>>y;
		merge(x,y);
	}
	
	int mul=1,cnt=0;
	for(int i=1;i<=n;i++)
	{
		if(find(i)!=i) continue;
		mul=mul*sz[i]%mod;
		cnt++;
	}
	
	if(cnt==1) cout<<1%mod<<"\n",exit(0);
	
	for(int i=1;i<=cnt-2;i++) mul=mul*n%mod;
	
	cout<<mul<<"\n";
	
	return 0;
}

```

---

## 作者：_Kenma_ (赞：1)

# CF156D 解题报告

## 前言

凯莱定理的推广。

感觉用 prufer 序列证明的题解说的都比较含糊。

## 思路分析

结论：

$$ans=n^{k-2}\prod_{i}^{k} s_i$$

其中 $s_i$ 为第 $i$ 个连通块的大小。

考虑用 prufer 序列的性质证明。

首先有一个 naive 的想法：钦定连通块之间的偏序关系，将每一个连通块当作一个点构建 prufer 序列。

但是其实这并不好做。

发现如果直接在 prufer 序列中记录连通块的编号的话，对于一条 $i \to j$ 的边，它可能的情况为 $s_i \cdot s_j$ 种。所以，连边方式直接决定了这个 prufer 序列对答案的贡献。

也就是说，每一个 prufer 序列对答案的贡献不是相同的，这使得统计答案很困难。

考虑在 prufer 序列中多刻画一些事情。

我们还是把每一个连通块看作一个点，但是，和上面 prufer 序列不同的是，我们在 prufer 序列中不记录相邻联通块的编号，而是记录实际相邻的点的编号。

举个例子：

![](https://cdn.luogu.com.cn/upload/image_hosting/zeevo5l5.png)

按照之前的构建方法，prufer 序列为：$6,6$。

按照新的构建方法，prufer 序列为：$1,2$。

这样相当于我们确定了每条边的一端的连边情况。

所以，对于一条 $i \to j$ 的路径，它对答案的贡献为 $s_i$。

因此，根据乘法原理，对于每一个 prufer 序列，它对答案的贡献都为 $\prod_{i}^{k} s_i$。

而这样的 prufer 序列有 $n^{k-2}$ 个。

所以答案为：$ans=n^{k-2}\prod_{i}^{k} s_i$。

## 代码实现

可以用并查集维护连通块大小。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,x,y,k,mod,ans;
int fa[200005],size[200005];
void init(){
	k=n;
	ans=1;
	for(int i=1;i<=n;i++){
		size[i]=1;
		fa[i]=i;
	}
}
int find(int x){
	if(fa[x]==x) return x;
	else return fa[x]=find(fa[x]);
}
void merge(int x,int y){
	x=find(x);
	y=find(y);
	if(x==y) return;
	k--;
	fa[x]=y;
	size[y]+=size[x];
}
int binpow(int a,int b){
	if(b==0) return 1;
	int res=binpow(a,b/2);
	if(b&1) return res*res%mod*a%mod;
	else return res*res%mod; 
}
int main(){
	cin>>n>>m>>mod;
	init();
	for(int i=1;i<=m;i++){
		cin>>x>>y;
		merge(x,y);
	}
	for(int i=1;i<=n;i++){
		if(fa[i]==i) ans=ans*size[i]%mod;
	}
	if(k==1){
		cout<<1%mod;
		return 0;
	}
	ans=ans*binpow(n,k-2)%mod;
	cout<<ans;
	return 0;
}
```

---

## 作者：_ZHONGZIJIE0608_ (赞：1)

给定一个 $n$ 个点 $m$ 条边的带标号无向图，它有 $k$ 个连通块，求添加 $k-1$ 条边使得整个图连通的方案数，答案对 $p$ 取模。

$k$ 个连通块，添加 $k-1$ 条边使得整张图连通……有点眼熟。

将每个连通块抽象成一个点，则该题转化为求 $k$ 个连通块的生成树个数。

由于每个值域为 $[1,n]$，长度为 $k-2$ 的 Prufer 序列均可生成一棵树，生成树个数为 $n^{k-2}$。

根据乘法原理，每个连通块内选择一个点出来连边，方案数为 $\prod_{i-1}^k {s_i}$，其中 $s_i$ 表示连通块中点的个数。

所以答案为 $n^{k-2}\prod_{i=1}^k {s_i}$。

用并查集找连通块统计即可。

注意：

- $p=1$ 时答案为 $0$。
- $k=1$ 时答案为 $1$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=4e5+10;
int n,m,p,k=0;
int fa[N],s[N];
inline int find(int x){return fa[x]==x?fa[x]:fa[x]=find(fa[x]);}
inline void Union(int x,int y){int fax=find(x),fay=find(y);if(fax!=fay)fa[fax]=fay;}
inline int qpow(int a,int b){
	int s=1;a%=p;
	while(b){
		if(b&1ll)s=s*a%p;
		a=a*a%p;b>>=1ll;
	}
	return s%p;
}
signed main(){
	ios::sync_with_stdio(false);cin.tie(0),cout.tie(0);
	cin>>n>>m>>p;
	if(p==1){
		cout<<(0);return 0; 
	}
	for(int i=1;i<=n;++i)fa[i]=i;
	for(int i=1;i<=m;++i){
		int u,v;cin>>u>>v;Union(u,v);
	}
	for(int i=1;i<=n;++i)++s[find(i)];sort(s+1,s+1+n,greater<int>());
	for(int i=1;i<=n+1;++i)if(!s[i]){k=i-1;break;}
	if(k==1){
		cout<<(1%p);return 0;
	}
	int ans=qpow(n,k-2);
	for(int i=1;i<=k;++i)ans=ans*s[i]%p;
	cout<<ans%p;
	return 0;
}
```

---

## 作者：_Fontainebleau_ (赞：1)

### 题意
 
- 一个 $n$ 个点 $m$ 条边的带标号无向图有 $k$ 个连通块，求添加 $k-1$ 条边使得整个图联通的方案。

- $1\le n\le 10^5,0\le m\le 10^5$。

### 做法

~~icpc 考了原题，在不知道 Prufer 序列的情况下找出了规律然后 A 了。~~

前置芝士：

- Prufer 序列
- 多元二项式定理

尽可能讲得很详细了。


设 $s_i$ 为第 $i$ 个连通块的大小，$d_i$ 为第 $i$ 个连通块的度数。我们先把每个连通块都看作一个点，则易知共 $\displaystyle \frac{(k-2)!}{\prod\limits_{i=1}^k(d_i-1)!}$ 种方案。

> why?首先 $k$ 个点的话 Prufer 序列应该长 $k-2$。假设序列中每个数都不相同，则有 $(k-2)!$ 种方法。因为点 $i$ 在序列中出现了 $d_i-1$ 次，所以每一种方案重复算了 $(d_i-1)!$ 次。

对于第 $i$ 个连通块而言，其连接方式应该有 $s_i^{d_i}$ 种。

> why?向外共 $d_i$ 条边，每条边各可以选择 $s_i$ 中的一个点，所以 $s_i^{d_i}$ 种。

然后就到了快乐的推式子时间。

$$ \binom{k-2}{d_1-1,d_2-1,\cdots,d_k-1}\cdot \prod_{i=1}^k s_i^{d_i}=\frac{(k-2)!}{\prod\limits_{i=1}^k(d_i-1)!}\cdot \prod_{i=1}^k s_i^{d_i}$$

现在要枚举 $d$ 序列：

$$\sum_{d_i\ge1,\sum_{i=1}^k{d_i}=2k-2}\binom{k-2}{d_1-1,d_2-1,\cdots,d_k-1}\cdot \prod_{i=1}^k s_i^{d_i}$$

很令人难受，好在我们有多元二项式定理：

$$(x_1+\cdots+x_m)^p=\sum_{c_i\ge0,\sum_{i=1}^m{c_i}=p}\binom{p}{c_1,c_2,\cdots,c_m}\cdot \prod_{i=1}^m x_i^{c_i}$$

对原式稍加改动，令 $e_i=d_i-1$，则有：

$$\sum_{e_i\ge0,\sum_{i=1}^{k}e_i=k-2}\binom{k-2}{e_1,e_2\cdots,e_k}\cdot\prod_{i=1}^k s_i^{e_i+1}=(s_1+s_2+\cdots+s_k)^{k-2}\cdot\prod_{i=1}^k s_i=n^{k-2}\prod_{i=1}^k s_i$$

所以最后答案就是 $\displaystyle n^{k-2}\cdot\prod_{i=1}^k s_i$。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,mod,ans=1,k;
int f[100005];
int siz[100005];
int find(int x)
{
	return f[x]==x?x:f[x]=find(f[x]);
}
inline int qpow(int a,int b)
{
	int res=1,p=a;
	while(b)
	{
		if(b&1)	res=1ll*res*p%mod;
		p=1ll*p*p%mod;b>>=1; 
	}
	return res;
}
inline int read()
{
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-f;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	return x*f;
}
int main()
{
	n=read(),m=read(),mod=read();
	if(mod==1)	return puts("0"),0;
	for(int i=1;i<=n;i++)	f[i]=i;
	for(int i=1;i<=m;i++)
	{
		int u=read(),v=read();
		int p=find(u),q=find(v);
		f[q]=p;
	}
	for(int i=1;i<=n;i++)	siz[find(i)]++;
	for(int i=1;i<=n;i++)
		if(siz[i])	k++,ans=1ll*ans*siz[i]%mod;
	if(k<2)	ans=1;
	else ans=1ll*ans*qpow(n,k-2)%mod;
	printf("%d\n",ans);
	return 0;
}

```



---

## 作者：wangyibo201026 (赞：0)

## 思路

考虑到把 $k$ 个连通块看作点，那么总方案数根据 Prufer 序列来说是 $n^{k - 2}$（合法 Prufer 序列长度为 $k - 2$）。

考虑到每一个点有不同的连接方式，这样连接会给答案带来 $\prod_{i = 1}^k siz_i$ 种不同的方案，即连通块大小相乘。

所以最终答案就是：

$$n^{k - 2} \cdot \prod_{i = 1}^k siz_i$$

## 代码

代码：

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int N = 2e5 + 5;

int n, m, k, mod, ans = 1;
int fa[N], p[N], d[N], siz[N];
bool vis[N];

int head[N], tot;

struct Graph {
	int to, next;
} edges[N << 1];

void add ( int u, int v ) {
	tot ++;
	edges[tot].to = v;
	edges[tot].next = head[u];
	head[u] = tot;
}

int fast_pow ( int a, int b ) {
	int res = 1ll;
	while ( b ) {
		if ( b & 1 ) {
			res = res * a;
			res %= mod;
		}
		b /= 2ll;
		a = a * a;
		a %= mod;
	}
	return res;
}

void Prufer () {
	int pos;
	for ( int i = 1; i <= n; i ++ ) {
		if ( d[i] == 1 ) {
			pos = i;
			break;
		}
	}
	int leaf = pos;
	for ( int i = 1; i <= n - 2; i ++ ) {
		p[i] = fa[leaf];
		d[fa[leaf]] --;
		if ( d[fa[leaf]] == 1 && fa[leaf] < pos ) {
			leaf = fa[leaf];
			continue;
		}
		pos ++;
		while ( d[pos] != 1 ) {
			pos ++;
		}
		leaf = pos;
	}
}

void unPrufer () {
	int pos;
	for ( int i = 1; i <= n - 2; i ++ ) {
		d[p[i]] ++;
	}
	for ( int i = 1; i <= n; i ++ ) {
		d[i] ++;
	}
	for ( int i = 1; i <= n; i ++ ) {
		if ( d[i] == 1 ) {
			pos = i;
			break;
		}
	}
	int leaf = pos;
	for ( int i = 1; i <= n - 2; i ++ ) {
		fa[leaf] = p[i];
		d[fa[leaf]] --;
		if ( d[fa[leaf]] == 1 && fa[leaf] < pos ) {
			leaf = fa[leaf];
			continue;
		}
		pos ++;
		while ( d[pos] != 1 ) {
			pos ++;
		}
		leaf = pos;
	}
	for ( int i = 1; i < n; i ++ ) {
		if ( !fa[i] ) {
			fa[i] = n;
		}
	}
}

void dfs ( int x ) {
	vis[x] = true;
	siz[k] ++;
	for ( int i = head[x]; i; i = edges[i].next ) {
		if ( !vis[edges[i].to] ) {
			dfs ( edges[i].to );
		}
	}
}

signed main () {
	ios :: sync_with_stdio ( false );
	cin.tie ( 0 ), cout.tie ( 0 );
	cin >> n >> m >> mod;
	for ( int i = 1; i <= m; i ++ ) {
		int u, v;
		cin >> u >> v;
		add ( u, v ), add ( v, u );
	}
	for ( int i = 1; i <= n; i ++ ) {
		if ( !vis[i] ) {
			k ++;
			dfs ( i );
			ans *= siz[k];
			ans %= mod;
		}
	}
	if ( k == 1 ) {
		cout << 1 % mod;
		return 0;
	}
	cout << ans * fast_pow ( n, k - 2 ) % mod;
	return 0;
}


// 2n - 2
```

---

## 作者：lfxxx (赞：0)

考虑把连通块缩成一个点，那么就是 $k$ 个点的无根树数量，等价于长度为 $k-2$ 的 Prüfer 序列数量也就是 $n^{k-2}$，你还需要在每个连通块内选出一个点代表这个连通块作为缩点后的树上的点连边，因此还需要乘上连通块大小之积。

注意连通块数量为 $1$ 时答案为 $1$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,p;
const int maxn = 1e5+114;
vector<int> edge[maxn];
int col[maxn],sz[maxn];
int qpow(int a,int b){
	if(b==0) return 1;
	if(b==1) return a%p;
	int res=qpow(a,b/2);
	res=res*res%p;
	if(b%2==1) res=res*(a%p)%p;
	return res;
}
int cl;
void dfs(int u){
	col[u]=cl;
	for(int v:edge[u]){
		if(col[v]==0) dfs(v);
	}
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m>>p;
	for(int i=1;i<=m;i++){
		int x,y;
		cin>>x>>y;
		edge[x].push_back(y);
		edge[y].push_back(x);
	}
	for(int i=1;i<=n;i++) 
		if(col[i]==0) cl++,dfs(i);
	for(int i=1;i<=n;i++) sz[col[i]]++;
	int res=1;
	for(int i=1;i<=cl;i++) res=res*sz[i]%p;
	if(cl==1){
		cout<<1%p<<'\n';
		return 0;
	}else{
		cout<<qpow(n,cl-2)*res%p<<'\n';
	}
	return 0;
}
```


---

## 作者：_fairytale_ (赞：0)

考虑 $k$ 个连通块构成的生成树都可以被一个值域 $[1,n]$，长度为 $k-2$ 的 Prüfer 序列唯一表示出来，这部分答案是 $n^{k-2}$。

然后每个连通块内部都可以选任何一个点与外界连边，所以答案再乘上 $\prod_{i=1}^{k}size_i$ 即可。

```cpp
#include<bits/stdc++.h>
#define re register
#define maxn 200100
#define ll long long
using namespace std;
int n,m,p;
int fa[maxn],siz[maxn];
int find(int x){
	return x==fa[x]?x:fa[x]=find(fa[x]);
}
inline int qp(int x,int y) {
	int res=1;
	while(y) {
		if(y&1)res=1ll*res*x%p;
		x=1ll*x*x%p;
		y>>=1;
	}
	return res;
}
ll ans=1,k;
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
    cin>>n>>m>>p;
    for(re int i=1;i<=n;++i)fa[i]=i,siz[i]=1;
    for(re int i=1;i<=m;++i){
    	re int u,v;
		cin>>u>>v;
		int fu=find(u),fv=find(v);
		if(fu==fv)continue;
		fa[fv]=fu;
		siz[fu]+=siz[fv];
	}
	for(re int i=1;i<=n;++i){
		if(fa[i]==i)ans=ans*siz[i]%p,++k;
	}
	if(k==1)return cout<<1%p,0;
	ans=ans*qp(n,k-2)%p;
	cout<<ans;
	return 0;
}

```

---

## 作者：Union_of_Britain (赞：0)

当然可以使用矩阵树定理导出结论。

设 $n$ 为连通块个数，大小分别为 $a_{1:n}$，和为 $S$，即原图大小。

根据矩阵树定理，就是需要计算

$$\det  
\begin{pmatrix}  
  a_1(S-a_1)& -a_1a_2& \cdots  & -a_{1}a_{n} \\  
  -a_2a_1& a_2(S-a_2)& \cdots  & -a_2a_n \\  
  \vdots & \vdots & \ddots & \vdots \\  
  -a_na_1& -a_na_2& \cdots  & a_n(S-a_n) 
\end{pmatrix}_{[n-1]}  $$

对其做初等行变换，第 $i$ 行除以 $a_i$，答案即（注意只取了前 $n-1$ 行列）

$$\prod_{i<n}a_i\cdot\det  
\begin{pmatrix}  
  (S-a_1)& -a_2& \cdots  & -a_{n} \\  
  -a_1& (S-a_2)& \cdots  & -a_n \\  
  \vdots & \vdots & \ddots & \vdots \\  
  -a_1& -a_2& \cdots  & (S-a_n)  
\end{pmatrix}_{[n-1]}    $$

转置一下。

$$D=\begin{pmatrix}  
  (S-a_1)& -a_1& \cdots  & -a_{1} \\  
  -a_2& (S-a_2)& \cdots  & -a_2 \\  
  \vdots & \vdots & \ddots & \vdots \\  
  -a_{n-1}& -a_{n-1}& \cdots  & (S-a_{n-1})  
\end{pmatrix}$$

一个便捷的方法是考虑特征值。如果 $D$ 的 $n-1$ 个非零特征值是 $\lambda_1,\lambda_2,\dots ,\lambda _{n-1}$，那么结果是

$$|D|=\prod \lambda_i$$

考虑 $D{\bf v}$，设 $S_2=\sum {\bf v_i}$。则有：

$$(D{\bf v})_i={\bf v_i}S-a_iS_2$$

而 $S_2=0$ 的线性无关向量 ${\bf v}$ 恰有 $n-2$ 个。这意思是说 $\lambda_1=\lambda_2=\dots=\lambda_{n-2}=S$。还需要找一个向量。

假设 $\lambda_{n-1}=A$。应该有

$$(D{\bf v})_i={\bf v_i}S-a_iS_2=A{\bf v_i}$$

对 $i$ 求和：

$$
\sum_i {\bf v_i}S-a_iS_2=\sum_i A{\bf v_i}\\
SS_2-(S-a_n)S_2=AS_2
$$

当 $S_2\neq 0$ 时 $A=a_n$。一个 $S_2\neq 0$ 的 $\bf v$ 显然和前面 $S_2=0$ 的 $\bf v$ 线性无关。

那么 

$$\det D=a_nS^{n-2}$$

所以答案即

$$\prod_{i<n}a_i\cdot a_nS^{n-2}=S^{n-2}\prod a_i$$

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=1e5+5;
int ans=1,n,m,mod,vis[maxn],cnt=0,tot=0;
vector<int> e[maxn];
void dfs(int u){
	if(vis[u])return ;
	cnt+=vis[u]=1;
	for(auto v:e[u])dfs(v);
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n>>m>>mod;
	for(int i=1,u,v;i<=m;i++)cin>>u>>v,e[u].push_back(v),e[v].push_back(u);
	for(int i=1;i<=n;i++)if(!vis[i])dfs(i),ans=(ans*cnt)%mod,cnt=0,++tot;
	for(int i=1;i<=tot-2;i++)(ans*=n)%=mod;
	ans%=mod;
	cout<<(tot==1?1%mod:ans)<<endl;
	return 0;
}

```

---

## 作者：MspAInt (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF156D)

一眼秒了！

把每个联通块看作一个节点，$k$ 个点 $k-1$ 条边，要求使图联通。好吧就是一棵树。

$k$ 个点，不同形态树的个数，明显就是 [prufer 序列](https://oi-wiki.org/graph/prufer/)。

又，每个节点（即联通块）里的任意点均可连边，因此答案为：

$$n^{k-2}\times\prod_{i=1}^{k}c_i$$

注意要特判和取模。

[record](https://vjudge.net/solution/45199748/QP0gAviimq4gu4nDLD60)

---

