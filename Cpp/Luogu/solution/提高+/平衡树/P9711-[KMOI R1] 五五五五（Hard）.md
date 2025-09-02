# [KMOI R1] 五五五五（Hard）

## 题目背景

“事类相推，各有攸归，故枝条虽分而同本干知，发其一端而已。又所析理以辞，解体用图，庶亦约而能周，通而不黩，览之者思过半矣。”——刘徽


## 题目描述

小宋有一个序列 $A=\{a_1,a_2\dots,a_n\}$，其中 $\forall i\in [1,n],a_i\in[0,9]$。

对于 $1\le l\le r\le n$，他记 $f(l,r)$ 等于 $\overline{a_la_{(l+1)}\dots a_r}$ 的末尾连续 $5$ 的个数。

例如：对于序列 $a=\{1,1,4,5,1,4\}$，$f(2,4)=1,f(1,3)=0$。

不过小宋会对这个序列不断地操作，具体地，他会做以下操作：

- $(1,x,y)$：将第 $x$ 个数改为 $y$（$x\in[1,n],y\in[0,9]$）。

- $2$: 将序列 $a$ 反转，例如 $\{1,1,4,5\}$ 反转之后就是 $\{5,4,1,1\}$。

- $3$：对序列进行询问。

- $(4,l,r)$：对序列进行询问。

对于每一种操作 $3$，请你输出:

$$\Big(\sum\limits_{l=1}^
{n}\sum\limits_{r=l}^{n} f(l,r)\Big) \bmod 10^9+7$$

对于每一个操作 $4$，请你输出：

$$\Big(\sum\limits_{i=l}^{r}a_i\Big) \bmod 10^9+7$$

## 说明/提示

## 样例 $1$ 解释：

| 操作 | 操作后的序列 | 答案 |
| :----------: | :----------: | :----------: |
| $(1,3,3)$ | $\{1,5,3\}$ | $/$ |
| $3$ | $/$ | $2$ |
| $(1,1,5)$ | $\{5,5,3\}$ | $/$ |
| $(4,1,3)$ | $/$ | $13$ |

## 样例 $2$ 解释：

| 操作 | 操作后的序列 | 答案 |
| :----------: | :----------: | :----------: |
| $3$ | $/$ | $4$ |
| $2$ | $\{4,1,5,4,1,1\}$ | $/$ |
| $3$ | $/$ | $3$ |
| $(1,1,5)$ | $\{5,1,5,4,1,1\}$ | $/$ |
|$(4,1,4)$|$/$|$15$|
## 数据范围
| 测试点编号 | $n\le$ |$q\le$| 特殊性质 |
| :----------: | :----------: | :----------: | :----------: |
|$1$|$100$|$100$|$/$|
|$2,3$|$10^3$|$10^3$|$\mathbf{A}$|
|$4$|$10^3$|$10^3$|$\mathbf{B}$|
|$5\sim10$|$2\times 10^5$|$2\times 10^5$|$/$|
|$11\sim13$|$2\times 10^5$|$2\times 10^5$|$\mathbf{A}$|
|$14,15$|$2\times 10^5$|$2\times 10^5$|$/$|
|$16\sim18$|$5\times 10^5$|$5\times 10^5$|$\mathbf{B}$|
|$19\sim25$|$5\times 10^5$|$5\times 10^5$|$/$|

特殊性质 $\mathbf{A}:$ 没有操作 $2$。

特殊性质 $\mathbf{B}:$ 没有操作 $3$。

对于 $100\%$ 的数据：$1\le n\le 5\times 10^5$，$1\le q\le 5\times 10^5$。

 $\forall i\in [1,n]$，满足 $a_i\in[0,9]$。

## 样例 #1

### 输入

```
3 4
1 5 5
1 3 3
3
1 1 5
4 1 3```

### 输出

```
2
13```

## 样例 #2

### 输入

```
6 5
1 1 4 5 1 4
3
2
3
1 1 5
4 1 4```

### 输出

```
4
3
15```

# 题解

## 作者：Fire_flame (赞：6)



前置知识：[T4 五五五五 （Easy）](https://www.luogu.com.cn/problem/T336096) 正解（必须），线段树或者平衡树。

可以发现上一道题其实提示了这个题目的方法呢。

## $\mathbf{Method1}$

本方法考虑线段树维护，定义 $g_i$ 表示数组 $\overline{a_1a_2\dots a_i}$ 末尾连续 $5$ 的个数。

首先预处理 $g$ 数组和初始答案 $ans$。

不难发现，在进行操作 $1$ 的过程中，仅仅维护 $g$ 数组是不够的，我们需要预处理一个镜像数组 $g'$，一个镜像答案 $ans'$。

$g'_i$ 表示 $\overline{a_ia_{(i-1)}\dots a_1}$ 末尾连续 $5$ 的个数。接下来，我们用线段树维护 $g,g'$ 即可。

---

对于操作 $1$，我们得分类讨论：

- 如果是把一个 $5$ 改成其他的数，那么 $g_{g'_{x}} \sim g_{x-1}$ 全部减 $g_x$，$g_x$ 清零。

	并且 $g'_{g_{x}} \sim g'_{x-1}$ 全部减 $g'_x$，$g'_x$ 清零。
   

- 把其他的数改成 $5$ 也同理，这里不再赘述。

记得每一次操作完 $ans,ans'$ 都要相应的改变。

---

对于操作 $2$，我们使用一个变量 $now$ 表示经过翻转了奇数次还是偶数次，$now=1$ 表示翻转了奇数次，$now=0$ 表示翻转了偶数次。

操作 $2$ 时直接异或一下 $now$ 即可。

---

对于操作 $3$，如果 $now=0$ 输出 $ans$，否则输出 $ans'$。

---

对于操作 $4$，就是一个普通线段树的区间求和（~~看这出题人多良心~~）。

标程：
```cpp
#include <ctime>//By wzy2021   (Orz Orz)
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;

const int N = 1e6 + 10;
const int mod = 1e9 + 7;

struct node {
	int l, r, sz, sum;
	int l5, r5, s5; ll sf, sg; 
};
int n, m; ll f[N], g[N];

void init (int n) {
	for (int i = 1; i <= n; ++i) f[i] = (f[i - 1] + i) % mod, g[i] = (g[i - 1] + i * (i + 1) / 2) % mod;
}

int get (int x, int y) {
	return (1ll * f[x] * y % mod + g[x]) % mod;
}

struct Tree {
	node t[N << 2];
	void pushup (int x) {
		t[x].sum = t[x << 1].sum + t[x << 1 | 1].sum;
		t[x].l5 = t[x << 1].l5; if (t[x << 1].l5 == t[x << 1].sz) t[x].l5 += t[x << 1 | 1].l5;
		t[x].r5 = t[x << 1 | 1].r5; if (t[x << 1 | 1].r5 == t[x << 1 | 1].sz) t[x].r5 += t[x << 1].r5;
		t[x].s5 = ((t[x << 1].s5 + t[x << 1 | 1].s5 - f[t[x << 1].r5] - f[t[x << 1 | 1].l5] + f[t[x << 1].r5 + t[x << 1 | 1].l5]) % mod + mod) % mod;
		t[x].sf = (t[x << 1].sf + t[x << 1 | 1].sf + 1ll * t[x << 1].sz * t[x << 1 | 1].s5 % mod) % mod;
		t[x].sf -= get (t[x << 1].r5, t[x << 1].sz - t[x << 1].r5) + get (t[x << 1 | 1].l5, t[x << 1].sz);
		t[x].sf += get (t[x << 1].r5 + t[x << 1 | 1].l5, t[x << 1].sz - t[x << 1].r5);
		t[x].sf = (t[x].sf % mod + mod) % mod;
	}
	void build (int x, int l, int r) {
		t[x].l5 = t[x].r5 = t[x].s5 = t[x].sf = t[x].sg = 0;
		t[x].l = l; t[x].r = r; t[x].sz = r - l + 1; t[x].sum = 0;
		if (l == r) return ;
		int mid = (l + r) >> 1;
		build (x << 1, l, mid); build (x << 1 | 1, mid + 1, r);
	}
	void update (int x, int k, int v) {
		if (t[x].l == t[x].r) {
			t[x].sum = v; t[x].l5 = t[x].r5 = t[x].s5 = t[x].sf = t[x].sg = (v == 5);
			return ;
		}
		int mid = (t[x].l + t[x].r) >> 1;
		if (k <= mid) update (x << 1, k, v);
		else update (x << 1 | 1, k, v);
		pushup(x);
	}
	int query (int x, int l, int r) {
		if (l <= t[x].l && t[x].r <= r) return t[x].sum;
		int mid = (t[x].l + t[x].r) >> 1, ans = 0;
		if (l <= mid) ans = (ans + query (x << 1, l, r)) % mod;
		if (r > mid) ans = (ans + query (x << 1 | 1, l, r)) % mod;
		return ans;
	}
} T[2]; 

int main() {
	init(N - 5);
	int n, m; scanf ("%d%d", &n, &m);
	T[0].build (1, 1, n); T[1].build(1, 1, n);
	for (int i = 1; i <= n; ++i) {
		int x; scanf ("%d", &x); T[0].update (1, i, x); T[1].update (1, n - i + 1, x); 
	} int flag = 0;
	while (m--) {
		int opt; scanf ("%d", &opt);
		if (opt == 1) {
			int x, y; scanf ("%d%d", &x, &y);
			T[flag].update(1, x, y); T[flag ^ 1].update(1, n - x + 1, y);
		} else if (opt == 2) {
			flag ^= 1;
		} else if (opt == 3) {
			printf ("%lld\n", T[flag].t[1].sf % mod);
		} else {
			int l, r; scanf ("%d%d", &l, &r);
			printf ("%d\n", T[flag].query (1, l, r));
		}
	}
	return 0;
}
```


## $\mathbf{Method2}$

这个题目也可以用平衡树解决。

因为 FF 不想再写字了，那么就留给大家去思考。

---

## 作者：Ginger_he (赞：3)

同校大佬出的比赛，膜拜。

首先发现只有序列反转奇数次会产生影响，下标 $x$ 变为 $n-x+1$。

考虑操作 $3$，对于一个极长的 $5$ 的连续段，设左右端点分别为 $l,r$，那么它对答案的贡献为

$$\begin{aligned}
&\sum_{i=1}^{r-l+1}i(r+1-i)\\
=&(r+1)\sum_{i=1}^{r-l+1}i-\sum_{i=1}^{r-l+1}i^2\\
=&\dfrac{t(t+1)(r+1)}{2}-\dfrac{t(t+1)(2t+1)}{6}
\end{aligned}$$

其中 $t=r-l+1$。

那我们只需要用 set 维护极长连续段，修改的时候更新贡献即可，操作 $4$ 可以使用树状数组或线段树维护区间和，时间复杂度 $O(n\log n)$。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define N 500005
const int p=1e9+7;
const int q1=500000004;
const int q2=166666668;
inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
	{
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
	{
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x*f;
}
struct node
{
	int l,r,v;
	bool operator < (const node &x) const
	{
		return l<x.l;
	}
};
int n,q,op,t,x,y,l,r,a[N],c[N],ansl,ansr;
set<node> s;
inline void add(int x,int y)
{
	for(;x<=n;x+=x&-x)
		c[x]=(c[x]+y)%p;
}
inline int query(int x)
{
	int res=0;
	for(;x;x-=x&-x)
		res=(res+c[x])%p;
	return res;
}
inline int calc1(int x)
{
	return 1ll*x*(x+1)%p*q1%p; 
}
inline int calc2(int x)
{
	return 1ll*x*(x+1)%p*(2*x+1)%p*q2%p;
}
inline int calc3(int l,int r)
{
	return ((1ll*(r+1)*calc1(r-l+1)%p-calc2(r-l+1))%p+p)%p;
}
inline void modify(int x,int y)
{
	auto it=--s.upper_bound(node{x,0,0});
	int l=it->l,r=it->r,v=it->v;
	if(it->v==5)
	{
		ansr=((ansr-calc3(l,r))%p+p)%p;
		ansl=((ansl-calc3(n-r+1,n-l+1))%p+p)%p;
	}
	s.erase(it);
	if(l<x)
	{
		s.insert(node{l,x-1,v});
		if(v==5)
		{
			ansr=(ansr+calc3(l,x-1))%p;
			ansl=(ansl+calc3(n-x+2,n-l+1))%p;
		}
	}
	if(x<r)
	{
		s.insert(node{x+1,r,v});
		if(v==5)
		{
			ansr=(ansr+calc3(x+1,r))%p;
			ansl=(ansl+calc3(n-r+1,n-x))%p;
		}
	}
	s.insert(node{x,x,y});
	it=s.lower_bound(node{x,0,0});
	l=r=x;
	if(x>1)
	{
		auto itt=it;
		itt--;
		if(itt->v==y)
		{
			if(y==5)
			{
				ansr=((ansr-calc3(itt->l,itt->r))%p+p)%p;
				ansl=((ansl-calc3(n-itt->r+1,n-itt->l+1))%p+p)%p;
			}
			l=itt->l,s.erase(itt);
		}
	}
	if(x<n)
	{
		auto itt=it;
		itt++;
		if(itt->v==y)
		{
			if(y==5)
			{
				ansr=((ansr-calc3(itt->l,itt->r))%p+p)%p;
				ansl=((ansl-calc3(n-itt->r+1,n-itt->l+1))%p+p)%p;
			}
			r=itt->r,s.erase(itt);
		}
	}
	s.erase(it);
	s.insert(node{l,r,y});
	if(y==5)
	{
		ansr=(ansr+calc3(l,r))%p;
		ansl=(ansl+calc3(n-r+1,n-l+1))%p;
	}
}
int main()
{
	n=read(),q=read();
	for(int i=1;i<=n;i++)
	{
		a[i]=read();
		add(i,a[i]); 
	}
	for(int i=1;i<=n;)
	{
		int j=i;
		while(j<n&&a[j+1]==a[i]) j++;
		s.insert(node{i,j,a[i]});
		if(a[i]==5)
		{
			ansr=(ansr+calc3(i,j))%p;
			ansl=(ansl+calc3(n-j+1,n-i+1))%p;
		}
		i=j+1;
	}
	while(q--)
	{
		op=read();
		if(op==1)
		{
			x=read(),y=read();
			if(t&1) x=n-x+1;
			if(a[x]==y) continue;
			modify(x,y);
			add(x,-a[x]);
			add(x,a[x]=y);
		}
		else if(op==2)
			t^=1;
		else if(op==3)
			printf("%d\n",t&1?ansl:ansr);
		else
		{
			l=read(),r=read();
			if(t&1) l=n-l+1,r=n-r+1;
			if(l>r) swap(l,r);
			printf("%d\n",((query(r)-query(l-1))%p+p)%p);
		}
	}
	return 0;
}
```

---

## 作者：lovely_hyzhuo (赞：2)

非常好（~~ex~~）的一道题。

首先，[简单版请](https://www.luogu.com.cn/problem/P9710)。

好，接下来默认你简单版过了。

有序列翻转这种奇怪的玩意，考虑全局标记，同时维护镜像数组和原数组。

每次修改（操作一）的时候，在当前线段树上改，在另一颗线段树上改 $n-x+1$ 为 $y$。

操作二直接 $flag=flag \oplus 1$。

操作三输出当前这颗线段树的一号管理员的值就行了。

操作四没什么好说的。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
int tag;
struct node
{
	int l,r,l5,r5,s5,sf,sg,sz,sum;
};
int f[2000010];
int g[2000010];
void init(int n)
{
	for(int i=1;i<=n;i++)
		f[i]=f[i-1]+i,f[i]%=mod,g[i]=g[i-1]+(i+1)*i/2,g[i]%=mod;
}
int get(int x,int y)
{
	return (f[x]*y%mod+g[x])%mod;
}
struct node1
{
	node tree[8000010];
void pushup(int x)
{
	tree[x].sum=tree[x<<1].sum+tree[x<<1|1].sum;
	tree[x].l5=tree[x<<1].l5; 
	if(tree[x<<1].l5==tree[x<<1].sz) 
		tree[x].l5+=tree[x<<1|1].l5;
	tree[x].r5=tree[x<<1|1].r5;
	if(tree[x<<1|1].r5==tree[x<<1|1].sz)
		tree[x].r5+=tree[x<<1].r5;
	tree[x].s5=((tree[x<<1].s5+tree[x<<1|1].s5-f[tree[x<<1].r5]-f[tree[x<<1|1].l5]+f[tree[x<<1].r5+tree[x<<1|1].l5])%mod+mod)%mod;
	tree[x].sf=(tree[x<<1].sf+tree[x<<1|1].sf+tree[x<<1].sz*tree[x<<1|1].s5%mod)%mod;
	tree[x].sf-=get(tree[x<<1].r5,tree[x<<1].sz-tree[x<<1].r5)+get(tree[x<<1|1].l5,tree[x<<1].sz);
	tree[x].sf+=get(tree[x<<1].r5+tree[x<<1| 1].l5,tree[x<<1].sz-tree[x<<1].r5);
	tree[x].sf=(tree[x].sf%mod+mod)%mod;
}
	void build(int l,int r,int k)
{
	tree[k].l5=tree[k].r5=tree[k].s5=tree[k].sf=tree[k].sg=0;
	tree[k].sz=r-l+1;tree[k].sum=0;
	tree[k].l=l,tree[k].r=r;
	if(l==r)
	{
		return;
	}
	int mid=(l+r)>>1;
	build(mid+1,r,k*2+1);
	build(l,mid,k*2);
	//pushup(k);
}
	
void update(int l,int r,int k,int p)
{
	if(tree[k].l>=l&&tree[k].r<=r)
	{
		tree[k].sum=p;
		tree[k].l5=tree[k].r5=tree[k].s5=tree[k].sf=tree[k].sg=(p==5);
		return;
	}
	int mid=(tree[k].l+tree[k].r)>>1;
	if(mid>=l)
	{
		update(l,r,k*2,p);
	}
	if(mid<r)
	{
		update(l,r,k*2+1,p);
	}
	pushup(k);
}
int query(int k,int l,int r)
{
	if(l<=tree[k].l&&tree[k].r<=r)
		return tree[k].sum;
	int sum=0,mid=(tree[k].l+tree[k].r)>>1;
	if(mid>=l)
	{
		sum+=query(k*2,l,r);
		sum%=mod;
	}
	if(mid<r)
	{
		sum+=query(k*2+1,l,r);
		sum%=mod;
	}
	return sum;
}
}t[2];
signed main()
{
	int n,m;
	cin>>n>>m;
	init(200000);
	t[1].build(1,n,1),t[0].build(1,n,1);
	for(int i=1;i<=n;i++)
	{
		int x;
		cin>>x;
		t[0].update(i,i,1,x);
		t[1].update(n-i+1,n-i+1,1,x);
	}
	while(m--)
	{
		int op;
		cin>>op;
		if(op==1)
		{
			int x,y;
			cin>>x>>y;
			t[tag].update(x,x,1,y);
			t[tag^1].update(n-x+1,n-x+1,1,y);
		}
		else if(op==2)
			tag^=1;
		else if(op==3)
			cout<<t[tag].tree[1].sf%mod<<endl;
		else
		{
			int l,r;
			cin>>l>>r;
			cout<<t[tag].query(1,l,r)<<endl;
		}
	}
	return 0;
}
```


---

## 作者：Disjoint_cat (赞：2)

# [P9711 [KMOI R1] 五五五五（Hard）](https://www.luogu.com.cn/problem/P9711)

一个不需要复杂线段树的解法。

## 零、吐槽

怎么 easy 是大水题，hard 就变成大数据结构了？

这个 $\bmod\ 10^9+7$ 哪来的，全是 $5$ 也不爆 `long long` 啊！

这个 $4$ 操作是干甚么的，完全脱离主题。。。

## 一、题意

给出一个长为 $n$ 的数列 $a$。

定义 $f(l,r)$ 为 $a_l\sim a_r$ 中末尾连续的 $5$ 的数量。

例如 $a=[5,5,5,4,5]$，则 $f(2,5)=1$，$f(2,3)=2$。

定义 $f(a)$ 为

$$\sum_{i=1}^n\sum_{j=i}^nf(i,j)$$

你需要维护 $q$ 次操作：

- $\texttt{1}\ x\ y$：令 $a_x\gets y$。
- $\texttt{2}$：翻转 $a$。
- $\texttt{3}$：求 $f(a)$。
- $\texttt{4}\ l\ r$：求 $\sum\limits_{i=l}^ra_i$。

数据范围：$n,q\le5\times10^5$。

## 二、题解

首先 $4$ 操作只要支持单间改区间和（翻转可以询问时改 $l,r$）。所以直接树状数组板子拍上去即可。以下只讨论 $3$ 操作。

首先忽略 $2$ 操作，只考虑单点修改。

考虑一段极长连续 $5$ 段对答案的贡献 $W$。设左端点为 $le$，长度为 $sz$，则讨论 $f(l,r)$ 的值。

如果 $f(l,r)=i$，则分类讨论：

- $l\ge le$，则 $r=l+i-1\le le+sz-1$，共有 $sz-i+1$ 个；
- $l<le$，则 $r=le+i-1$，共有 $le-1$ 个。

所以一共会有 $le+sz-i$ 个这样的区间。列出柿子：

$$
\begin{aligned}W&=\sum_{i=1}^{sz}i(le+sz-i)\\&=(le+sz)\sum_{i=1}^{sz}i-\sum_{i=1}^{sz}i^2\\&=\frac{sz(sz+1)(le+sz)}2-\frac{sz(sz+1)(2sz+1)}6\end{aligned}$$

所以 $W$ 就能 $\Theta(1)$ 计算了。

**以下设 $W(l,r)$ 为 $a_l\sim a_r$ 的贡献（即 $sz=r-l+1$）。** 特别的，当 $r<l$ 时 $W(l,r)=0$。

预处理答案参考 easy 版，同时用一个 `set` $S$ 记下**所有的极长连续 $5$ 段**和答案 $ans$。

考虑单点修改 $a_x\gets y$。如果操作前 $a_x=5$，那么我们要把原来包含 $a_x$ 的段分裂。

把之前 $x$ 所在的段 $[l,r]$ 从 $S$ 里取出来，然后把 $[l,x-1]$ 和 $[x+1,r]$ 插进去（记得特判空段）。然后答案要减去 $W(l,r)-W(l,x-1)-W(x+1,r)$。

然后如果 $y=5$，则可能要合并它前面、后面的段，并更新答案。

所以本题就做完了……吗？

不，我们还要考虑翻转。

因为只会整个序列翻转，所以考虑同时维护正的、反的 $S$ 和 $ans$（记为 $Sr$、$ansr$），当翻转时，直接交换 $S,Sr$、$ans,ansr$ 即可。~~说着简单，码长直接翻倍。~~

（当然，不能直接交换 `set`，可以考虑用指针或者打标记。）

总时间复杂度 $\Theta(q\log n)$。

## 三、代码

本人代码写成依托答辩，不放出来了。

---

## 作者：hanjinghao (赞：2)

# 思路

首先，用一个变量表示当前序列是正的还是反的。反的序列上的第 $ x $ 个数，就是正的序列上的第 $ n - x + 1 $ 个数。因此，翻转整个序列这一操作，我们已经轻松实现了。

考虑单独计算每一个 $ 5 $ 的极长连续段的贡献。设连续段的左端点为 $ l $，右端点为 $ r $。它会对以下两类区间产生贡献：

一、左端点属于 $ [1,l] $，右端点属于 $ [l,r] $ 的区间。贡献为 $ l \times (r - l + 2) \times (r - l + 1) \div 2 $。

二、左右端点均属于 $ [l + 1,r] $ 的区间。贡献为 $ \sum\limits_{i = 1}^{r - l}i \times (r - l - i + 1) $。你可以把式子展开，用平方和通项公式化简；也可以直接递推，即 $ O(n) $ 预处理，$ O(1) $ 查询。笔者用的是后者。

**这是对正的序列的贡献，用同样的方法可以求出对反的序列的贡献。**

每当一个 $ 5 $ 变成非 $ 5 $，就把它所在的连续段拆成左右两边；每当一个非 $ 5 $ 变成 $ 5 $，就判断一下它左右两边的连续段能否跟它合并（能合并就合并）。

连续段用 set 维护即可。

至于单点修改区间求和，用树状数组即可。

代码常数极小，最慢的点只跑了几十毫秒。

# 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

char buf[10000005];
int ppos, llen;

inline char gch()
{
	if (ppos == llen)
	{
		ppos = 0;
		llen = fread(buf, 1, 10000000, stdin);
	}
	if (ppos == llen) return -1;
	return buf[ppos++];
}

char obuf[10000005];
int opos;

inline void pch(char c)
{
	if (opos == 10000000)
	{
		fwrite(obuf, 1, 10000000, stdout);
		opos = 0;
	}
	obuf[opos++] = c;
}

template < typename T >
inline void read(T &x)
{
	bool flg = x = 0;
	char c;
	while ((c = gch()) < 48 || c > 57)
		flg |= c == '-';
	do
		x = (x << 1) + (x << 3) + (c ^ 48);
	while ((c = gch()) > 47 && c < 58);
	if (flg) x = -x;
}

int OUTPUT[45];

template < typename T >
inline void writeln(T x)
{
	if (x < 0)
	{
		pch('-');
		x = -x;
	}
	int len = 0;
	do
	{
		OUTPUT[++len] = x % 10 | 48;
		x /= 10;
	}while (x);
	while (len)
		pch(OUTPUT[len--]);
	pch('\n');
}

const int N = 5e5 + 5, P = 1e9 + 7;
int n, q, a[N], t[N];
set < pair < int, int > > st;
ll f[N];

inline int lowbit(int x)
{
	return x & (-x);
}

inline void Upd(int x, int val)
{
	while (x <= n)
	{
		t[x] += val;
		x += lowbit(x);
	}
}

inline int Qry(int x)
{
	int ret = 0;
	while (x)
	{
		ret += t[x];
		x -= lowbit(x);
	}
	return ret;
}

inline ll calc(ll x)
{
	return ((1ll + x) * x) >> 1;
}

int main()
{
	read(n);
	read(q);
	for (int i = 1; i <= n; ++i)
	{
		read(a[i]);
		Upd(i, a[i]);
	}
	for (int i = 1; i <= n; ++i)
		f[i] = f[i - 1] + calc(i - 1ll) + i;
	ll sum1 = 0, sum2 = 0;
	for (int i = 1; i <= n; ++i)
		if (a[i] == 5)
		{
			int p = i;
			while (p < n && a[p + 1] == 5)
				++p;
			st.emplace(i, p);
			ll tmp = calc(p - i + 1ll);
			sum1 += tmp * i + f[p - i];
			sum2 += tmp * (n - p + 1ll) + f[p - i];
			i = p;
		}
	bool sig = 1;
	while (q--)
	{
		int opt;
		read(opt);
		if (opt == 1)
		{
			int x, y;
			read(x);
			read(y);
			if (!sig) x = n - x + 1;
			if (a[x] == y) continue;
			Upd(x, y - a[x]);
			if (a[x] == 5)
			{
				auto it = st.upper_bound(make_pair(x, 0x3f3f3f3f));
				--it;
				int l = (it -> first), r = (it -> second);
				st.erase(it);
				ll tmp = calc(r - l + 1ll);
				sum1 -= tmp * l + f[r - l];
				sum2 -= tmp * (n - r + 1ll) + f[r - l];
				if (x != l)
				{
					st.emplace(l, x - 1);
					ll tmp2 = calc(x - l);
					sum1 += tmp2 * l + f[x - l - 1];
					sum2 += tmp2 * (n - x + 2ll) + f[x - l - 1];
				}
				if (x != r)
				{
					st.emplace(x + 1, r);
					ll tmp3 = calc(r - x);
					sum1 += tmp3 * (x + 1ll) + f[r - x - 1];
					sum2 += tmp3 * (n - r + 1ll) + f[r - x - 1];
				}
			}
			else if (y == 5)
			{
				if (st.empty())
				{
					st.emplace(x, x);
					sum1 += x;
					sum2 += n - x + 1;
				}
				else
				{
					auto it = st.upper_bound(make_pair(x, 0x3f3f3f3f));
					if (it == st.end())
					{
						--it;
						if ((it -> second) == x - 1)
						{
							int l = (it -> first), r = (it -> second);
							st.erase(it);
							ll tmp = calc(r - l + 1ll);
							sum1 -= tmp * l + f[r - l];
							sum2 -= tmp * (n - r + 1ll) + f[r - l];
							st.emplace(l, x);
							tmp = calc(x - l + 1ll);
							sum1 += tmp * l + f[x - l];
							sum2 += tmp * (n - x + 1ll) + f[x - l];
						}
						else
						{
							st.emplace(x, x);
							sum1 += x;
							sum2 += n - x + 1;
						}
					}
					else
					{
						if (it == st.begin())
						{
							if ((it -> first) == x + 1)
							{
								int l = (it -> first), r = (it -> second);
								st.erase(it);
								ll tmp = calc(r - l + 1ll);
								sum1 -= tmp * l + f[r - l];
								sum2 -= tmp * (n - r + 1ll) + f[r - l];
								st.emplace(x, r);
								tmp = calc(r - x + 1ll);
								sum1 += tmp * x + f[r - x];
								sum2 += tmp * (n - r + 1ll) + f[r - x];
							}
							else
							{
								st.emplace(x, x);
								sum1 += x;
								sum2 += n - x + 1;
							}
						}
						else
						{
							auto pre = it;
							--pre;
							if ((pre -> second) == x - 1 && (it -> first) == x + 1)
							{
								int l1 = (pre -> first), r1 = (pre -> second), l2 = (it -> first), r2 = (it -> second);
								st.erase(pre);
								ll tmp = calc(r1 - l1 + 1ll);
								sum1 -= tmp * l1 + f[r1 - l1];
								sum2 -= tmp * (n - r1 + 1ll) + f[r1 - l1];
								st.erase(it);
								tmp = calc(r2 - l2 + 1ll);
								sum1 -= tmp * l2 + f[r2 - l2];
								sum2 -= tmp * (n - r2 + 1ll) + f[r2 - l2];
								st.emplace(l1, r2);
								tmp = calc(r2 - l1 + 1ll);
								sum1 += tmp * l1 + f[r2 - l1];
								sum2 += tmp * (n - r2 + 1ll) + f[r2 - l1];
							}
							else if ((pre -> second) == x - 1)
							{
								int l = (pre -> first), r = (pre -> second);
								st.erase(pre);
								ll tmp = calc(r - l + 1ll);
								sum1 -= tmp * l + f[r - l];
								sum2 -= tmp * (n - r + 1ll) + f[r - l];
								st.emplace(l, x);
								tmp = calc(x - l + 1ll);
								sum1 += tmp * l + f[x - l];
								sum2 += tmp * (n - x + 1ll) + f[x - l];
							}
							else if ((it -> first) == x + 1)
							{
								int l = (it -> first), r = (it -> second);
								st.erase(it);
								ll tmp = calc(r - l + 1ll);
								sum1 -= tmp * l + f[r - l];
								sum2 -= tmp * (n - r + 1ll) + f[r - l];
								st.emplace(x, r);
								tmp = calc(r - x + 1ll);
								sum1 += tmp * x + f[r - x];
								sum2 += tmp * (n - r + 1ll) + f[r - x];
							}
							else
							{
								st.emplace(x, x);
								sum1 += x;
								sum2 += n - x + 1;
							}
						}
					}
				}
			}
			a[x] = y;
		}
		else if (opt == 2)
		{
			sig = !sig;
		}
		else if (opt == 3)
		{
			if (sig) writeln(sum1 % P);
			else writeln(sum2 % P);
		}
		else
		{
			int l, r;
			read(l);
			read(r);
			if (sig) writeln(Qry(r) - Qry(l - 1));
			else writeln(Qry(n - l + 1) - Qry(n - r));
		}
	}
	if (opos) fwrite(obuf, 1, opos, stdout);
	return 0;
}
```

---

## 作者：哈哈人生 (赞：2)

## 题外话
这题就是代码复杂而已。

## 思路
首先想到线段树（其实是树状数组，线段树也可以），对于每种操作：
1. 操作 $1$，调用线段树单点修改函数。
2. 操作 $2$，用一个布尔类型变量，记录序列为正或反。
3. 操作 $3$，预处理正序列的答案 $ans1$ 和反序列的答案 $ans2$。
4. 操作 $4$，调用线段树区间查询函数。

比较难得就是单点修改时，维护 $ans1$ 和 $ans2$ 的值正确，具体可以看[五五五五（Hard）的我的题解](https://www.luogu.com.cn/blog/zhaoqianhao/solution-p9710)。

我们观察到，如果原先正序列查询的区间是 $l$ 到 $r$，反过来就是查询 $n-r+1$ 到 $n-l+1$，单点修改雷同。

## 注意
这里的取模不能在计算和更新 $ans1$ 和 $ans2$ 时取模，因为后面如果再更新有可能出现负数，所以我们要开长整型在输出时取模（数据范围可以保证 $ans1$ 和 $ans2$ 不爆长整型），本人就因为这个点在赛时只得了 $96$ 分。

## 代码
简洁的代码。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
int n,m,q,a[1000005],op,x,y;
struct ST {
	int l,r,sum;
} tr[5000005];
void Build(int p,int l,int r) {
	tr[p].l=l,tr[p].r=r;
	if(tr[p].l==tr[p].r) {
		tr[p].sum=a[l];
		return;
	}
	int mid=l+r>>1;
	Build(p<<1,l,mid);
	Build(p<<1|1,mid+1,r);
	tr[p].sum=tr[p<<1].sum+tr[p<<1|1].sum;
}
void add(int p,int d,int k) {
	if(tr[p].l==tr[p].r) {
		tr[p].sum=k;
		return;
	}
	if(d<=tr[p<<1].r)add(p<<1,d,k);
	else add(p<<1|1,d,k);
	tr[p].sum=tr[p<<1].sum+tr[p<<1|1].sum;
}
int search(int p,int l,int r) {
	if(tr[p].l>=l&&tr[p].r<=r)return tr[p].sum;
	if(tr[p].r<l||tr[p].l>r)return 0;
	int s=0;
	if(tr[p<<1].r>=l)s+=search(p<<1,l,r);
	if(tr[p<<1|1].l<=r)s+=search(p<<1|1,l,r);
	return s;
}
bool pd=1;
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1; i<=n; i++)cin>>a[i];
	Build(1,1,n);
	int ans1=0,ans2=0;
	int l=-1,r;
	for(int i=1; i<=n; i++) {
		if(a[i]==5) {
			if(l==-1)l=i,r=i;
			else r++;
		} else {
			if(l==-1)continue;
			int cd=(r-l+1);
			for(int j=1; j<=cd; j++) {
				ans1+=(cd-(j-1)-1)*j;
				ans1+=l*j;
			}
			l=-1;
		}
	}
	if(l!=-1) {
		int cd=(r-l+1);
		for(int i=1; i<=cd; i++) {
			ans1+=(cd-(i-1)-1)*i;
			ans1+=l*i;
		}
	}
	l=-1;
	for(int i=n; i>=1; i--) {
		if(a[i]==5) {
			if(l==-1)r=i,l=i;
			else l--;
		} else {
			if(l==-1)continue;
			int cd=(r-l+1);
			for(int j=1; j<=cd; j++) {
				ans2+=(cd-(j-1)-1)*j;
				ans2+=(n-r+1)*j;
			}
			l=-1;
		}
	}
	if(l!=-1) {
		int cd=(r-l+1);
		for(int i=1; i<=cd; i++) {
			ans2+=(cd-(i-1)-1)*i;
			ans2+=(n-r+1)*i;
		}
	}
	while(m--) {
		cin>>op;
		if(op==1) {
			cin>>x>>y;
			if(!pd)x=n-x+1;
			if(a[x]==y);
			else if(a[x]==5) {
				int l,r,cd;
				l=x-1,r=x+1;
				while(l>=1&&a[l]==5)l--;
				l++;
				while(r<=n&&a[r]==5)r++;
				r--;
				cd=(r-l+1);
				for(int j=1; j<=cd; j++) {
					ans1-=(cd-(j-1)-1)*j;
					ans1-=l*j;
				}
				for(int i=1; i<=cd; i++) {
					ans2-=(cd-(i-1)-1)*i;
					ans2-=(n-r+1)*i;
				}
				l=x-1,r=x-1;
				while(l>=1&&a[l]==5)l--;
				l++;
				cd=(r-l+1);
				for(int j=1; j<=cd; j++) {
					ans1+=(cd-(j-1)-1)*j;
					ans1+=l*j;
				}
				for(int i=1; i<=cd; i++) {
					ans2+=(cd-(i-1)-1)*i;
					ans2+=(n-r+1)*i;
				}
				l=x+1,r=x+1;
				while(r<=n&&a[r]==5)r++;
				r--;
				cd=(r-l+1);
				for(int j=1; j<=cd; j++) {
					ans1+=(cd-(j-1)-1)*j;
					ans1+=l*j;
				}
				for(int i=1; i<=cd; i++) {
					ans2+=(cd-(i-1)-1)*i;
					ans2+=(n-r+1)*i;
				}
			} else if(y==5) {
				int l,r,cd;
				l=x-1,r=x+1;
				while(l>=1&&a[l]==5)l--;
				l++;
				while(r<=n&&a[r]==5)r++;
				r--;
				cd=(r-l+1);
				for(int j=1; j<=cd; j++) {
					ans1+=(cd-(j-1)-1)*j;
					ans1+=l*j;
				}
				for(int i=1; i<=cd; i++) {
					ans2+=(cd-(i-1)-1)*i;
					ans2+=(n-r+1)*i;
				}
				l=x-1,r=x-1;
				while(l>=1&&a[l]==5)l--;
				l++;
				cd=(r-l+1);
				for(int j=1; j<=cd; j++) {
					ans1-=(cd-(j-1)-1)*j;
					ans1-=l*j;
				}
				for(int i=1; i<=cd; i++) {
					ans2-=(cd-(i-1)-1)*i;
					ans2-=(n-r+1)*i;
				}
				l=x+1,r=x+1;
				while(r<=n&&a[r]==5)r++;
				r--;
				cd=(r-l+1);
				for(int j=1; j<=cd; j++) {
					ans1-=(cd-(j-1)-1)*j;
					ans1-=l*j;
				}
				for(int i=1; i<=cd; i++) {
					ans2-=(cd-(i-1)-1)*i;
					ans2-=(n-r+1)*i;
				}
			}
			a[x]=y;
			add(1,x,y);
		} else if(op==2) {
			pd=!pd;
		} else if(op==3) {
			if(pd)cout<<ans1%mod<<endl;
			else cout<<ans2%mod<<endl;
		} else {
			cin>>x>>y;
			if(pd)cout<<search(1,x,y)<<endl;
			else cout<<search(1,n-y+1,n-x+1)<<endl;
		}
	}
	return 0;
}
```
点个赞呗。

---

## 作者：TernaryTree (赞：2)

前置知识：P9710 [KMOI R1] 五五五五（Easy）

看到全局翻转这种邪恶操作考虑直接打全局 tag。

然后单点修，区间查询和如果翻转了要把位置一起翻转过来。

动态维护一个正着的答案和倒着的答案。修改有几种：

- 把非 $5$ 改成非 $5$：

  对答案没有贡献，直接在线段树上改这个值
  
- 把 $5$ 改成 $5$

  没用
  
- 把 $5$ 改成非 $5$

  发现改动的值只与前面 $5$ 的个数 $pre$、后面 $5$ 的个数 $suf$ 以及当前位置有关。大力推式子计算变化量，计算前面后面个数可以线段树维护。
  
  具体的，此处仅考虑维护正着的答案，反着同理；显然对于每个在 $suf$ 中的数，记其原来前面的 $5$ 的个数为 $p$，记 $pre+1=z$，记其位置为 $x$，其作为右端点对答案的贡献的变化量为：
  
  $p(x-p)+\dfrac12 p(p+1)-(p-z)(x-p+z)-\dfrac12(p-z)(p+1-z)$
  
  把这东西拆开然后对于 $p\in [pre+1,suf+pre+1]$ 求和即为变化量。
  
- 把非 $5$ 改成 $5$

  与上一种同理
  
总复杂度 $\Theta(n+q\log n)$

```cpp
#include <bits/stdc++.h>
#define int long long
#define ls (u << 1)
#define rs (u << 1 | 1)
#define mid (l + r >> 1)
#define lc ls, l, mid
#define rc rs, mid + 1, r
#define rt 1, 1, n

using namespace std;

const int maxn = 5e5 + 10;
const int mod = 1e9 + 7;
const int inv2 = 5e8 + 4;

struct node {
    int pre, suf, len, sum;
    node() = default;
};

struct seg {
    node tr[maxn << 2];
    
    node pushup(node l, node r) {
        if (!l.len) return r;
        if (!r.len) return l;
        node u = node();
        if (l.pre == l.len) u.pre = l.len + r.pre;
        else u.pre = l.pre;
        if (r.suf == r.len) u.suf = r.len + l.suf;
        else u.suf = r.suf;
        u.len = l.len + r.len;
        u.sum = (l.sum + r.sum) % mod;
        return u;
    }
    
    void build(int * a, int u, int l, int r) {
        if (l == r) {
            tr[u].len = 1;
            tr[u].pre = tr[u].suf = (a[l] == 5);
            tr[u].sum = a[l];
            return;
        }
        build(a, lc), build(a, rc);
        tr[u] = pushup(tr[ls], tr[rs]);
    }
    
    void modify(int u, int l, int r, int p, int k) {
        if (l == r) {
            tr[u].pre = tr[u].suf = (k == 5);
            tr[u].sum = k;
            return;
        }
        if (p <= mid) modify(lc, p, k);
        else modify(rc, p, k);
        tr[u] = pushup(tr[ls], tr[rs]);
    } 
    
    node query(int u, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return tr[u];
        node res = node();
        if (ql <= mid) res = pushup(res, query(lc, ql, qr));
        if (qr > mid) res = pushup(res, query(rc, ql, qr));
        return res;
    }
};

int n, q, rev = 0;
int pre, suf, lans, rans;
int a[maxn];
seg tr;

int sum(int l, int r) {
	return (l + r) % mod * (r - l + 1) % mod * inv2 % mod;
}

signed main() {
	cin >> n >> q;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n; i++) {
		if (a[i] == 5) ++pre, (lans += (i - pre) * pre % mod + pre * (pre + 1) % mod * inv2 % mod) %= mod;
		else pre = 0;
	}
	for (int i = n; i >= 1; i--) {
		if (a[i] == 5) ++suf, (rans += (n - i + 1 - suf) * suf % mod + suf * (suf + 1) % mod * inv2 % mod) %= mod;
		else suf = 0;
	}
	tr.build(a, rt);
	while (q--) {
		int op, x, y;
		cin >> op;
		if (op == 1) {
			cin >> x >> y;
			if (rev) x = n - x + 1;
			if (a[x] == y) continue;
			if (a[x] == 5) {
				int pre = (x - 1 >= 1 ? tr.query(rt, 1, x - 1).suf : 0);
				int suf = (x + 1 <= n ? tr.query(rt, x + 1, n).pre : 0);
				(lans += mod - (suf + 1) * (pre + 2) % mod * (pre + 1) % mod * inv2 % mod + (pre + 1) * sum(pre + 1, pre + suf + 1) % mod) %= mod;
				(lans += mod - (pre + 1) * sum(x, x + suf) % mod) %= mod;
				(rans += mod - (pre + 1) * (suf + 2) % mod * (suf + 1) % mod * inv2 % mod + (suf + 1) * sum(suf + 1, pre + suf + 1) % mod) %= mod;
				(rans += mod - (suf + 1) * sum(n - x + 1, n - x + 1 + pre) % mod) %= mod;
			} else if (y == 5) {
				int pre = (x - 1 >= 1 ? tr.query(rt, 1, x - 1).suf : 0);
				int suf = (x + 1 <= n ? tr.query(rt, x + 1, n).pre : 0);
				(lans += (suf + 1) * (pre + 2) % mod * (pre + 1) % mod * inv2 % mod + mod - (pre + 1) * sum(pre + 1, pre + suf + 1) % mod) %= mod;
				(lans += (pre + 1) * sum(x, x + suf) % mod) %= mod;
				(rans += (pre + 1) * (suf + 2) % mod * (suf + 1) % mod * inv2 % mod + mod - (suf + 1) * sum(suf + 1, pre + suf + 1) % mod) %= mod;
				(rans += (suf + 1) * sum(n - x + 1, n - x + 1 + pre) % mod) %= mod;
			}
			tr.modify(rt, x, y);
			a[x] = y;
		} else if (op == 2) {
			rev ^= 1;
		} else if (op == 3) {
			if (!rev) {
				cout << lans << endl;
			} else {
				cout << rans << endl;
			}
		} else {
			cin >> x >> y;
			if (rev) {
				x = n - x + 1, y = n - y + 1;
				swap(x, y);
			}
			cout << tr.query(rt, x, y).sum << endl;
		}
	}
	return 0;
}
```

---

## 作者：zxh923 (赞：2)

# P9711 [KMOI R1] 五五五五（Hard） 题解

[题目传送门](https://www.luogu.com.cn/problem/P9711)。

[前置](https://www.luogu.com.cn/problem/P9710)。

### 思路

首先默认你已经通过了前置。

这道题我用了一个非常麻烦的方法：双线段树维护。


+ 对于操作 $1$，我们需要在两颗线段树上都进行修改。

+ 对于操作 $2$，只需要把标记异或 $1$。

+ 对于操作 $3$，输出我们维护的结果。

+ 对于操作 $4$，就是一个线段树区间求和的板子，套板子就行了。

用 $2$ 棵线段树分别维护反转和未反转的数列。

我们可以用一个结构体存储要维护的各项信息，例如区间和与末尾 $5$ 的数量。

对于把非 $5$ 改成非 $5$ 这种操作，对 $3$ 类查询无影响。

所以我们判断时，只用判断该点是当前是不是 $5$，如果是赋值成 $1$，否则赋值成 $0$。

并且还要预处理 $5$ 的答案数组，在这里不详细阐述，如果想看请跳转至[这里](https://www.luogu.com.cn/problem/P9710)。

### 代码

```cpp
#include<bits/stdc++.h> 
#define int long long
#define N 500005
#define mod 1000000007
using namespace std;
int n,q,op,a[N],f[N],g[N],flag,xx,yy,b[N];
void init(int x){//预处理 
	for(int i=1;i<=x;i++){
		f[i]=f[i-1]+i;
		f[i]%=mod;
		g[i]=g[i-1]+i*(i+1)/2;
		g[i]%=mod;
	}
	return;
}
int fi(int x,int y){
	return (f[x]*y+g[x])%mod;
}
struct node{
	int sum,l5,r5,s5,sf,siz;
}w[N*4],t[N*4];
void pushup(int u){
	w[u].sum=w[u*2].sum+w[u*2+1].sum;//区间和合并 
	w[u].l5=w[u*2].l5;
	if(w[u*2].l5==w[u*2].siz)w[u].l5+=w[u*2+1].l5;
	w[u].r5=w[u*2+1].r5;
	if(w[u*2+1].r5==w[u*2+1].siz)w[u].r5+=w[u*2].r5;
	w[u].s5=((w[u*2].s5+w[u*2+1].s5-f[w[u*2].r5]-f[w[u*2+1].l5]+f[w[u*2].r5+w[u*2+1].l5])%mod+mod)%mod;
	w[u].sf=(w[u*2].sf+w[u*2+1].sf+w[u*2].siz*w[u*2+1].s5%mod)%mod;
	w[u].sf-=fi(w[u*2].r5,w[u*2].siz-w[u*2].r5)+fi(w[u*2+1].l5,w[u*2].siz);
	w[u].sf+=fi(w[u*2].r5+w[u*2+1].l5,w[u*2].siz-w[u*2].r5);
	w[u].sf=(w[u].sf+mod)%mod;//末尾5 数量 
}
void build(int u,int l,int r){
	w[u].siz=r-l+1;
	if(l==r){//到达叶节点判断并赋值 
		w[u].sum=a[l];
		if(a[l]==5){
			w[u].l5=w[u].r5=w[u].s5=w[u].sf=1;
		}else{
			w[u].l5=w[u].r5=w[u].s5=w[u].sf=0;
		}
		return;
	}
	int mid=(l+r)/2;
	build(u*2,l,mid);
	build(u*2+1,mid+1,r);//双向递归 
	pushup(u);//上传 
}
void modify(int u,int l,int r,int p,int y){
	if(l==r){//到达该点修改并判断 
		w[u].sum=y;
		if(y==5){
			w[u].l5=w[u].r5=w[u].s5=w[u].sf=1;
		}else{
			w[u].l5=w[u].r5=w[u].s5=w[u].sf=0;
		}
		return;
	}
	int mid=(l+r)/2;
	if(mid>=p)modify(u*2,l,mid,p,y);//查询 
	else modify(u*2+1,mid+1,r,p,y);
	pushup(u);
}
int qry(int u,int l,int r,int L,int R){
	if(L<=l&&R>=r){//如果完全包含 
		return w[u].sum;
	}else if(!(l>R||r<L)){//如果不完全脱离 
		int mid=(l+r)/2;
		return qry(u*2,l,mid,L,R)+qry(u*2+1,mid+1,r,L,R);
	}else return 0;
}
//以下是镜面操作 
void pushup1(int u){
	t[u].sum=t[u*2].sum+t[u*2+1].sum;
	t[u].l5=t[u*2].l5;
	if(t[u*2].l5==t[u*2].siz)t[u].l5+=t[u*2+1].l5;
	t[u].r5=t[u*2+1].r5;
	if(t[u*2+1].r5==t[u*2+1].siz)t[u].r5+=t[u*2].r5;
	t[u].s5=((t[u*2].s5+t[u*2+1].s5-f[t[u*2].r5]-f[t[u*2+1].l5]+f[t[u*2].r5+t[u*2+1].l5])%mod+mod)%mod;
	t[u].sf=(t[u*2].sf+t[u*2+1].sf+t[u*2].siz*t[u*2+1].s5%mod)%mod;
	t[u].sf-=fi(t[u*2].r5,t[u*2].siz-t[u*2].r5)+fi(t[u*2+1].l5,t[u*2].siz);
	t[u].sf+=fi(t[u*2].r5+t[u*2+1].l5,t[u*2].siz-t[u*2].r5);
	t[u].sf=(t[u].sf+mod)%mod;
}
void build1(int u,int l,int r){
	t[u].siz=r-l+1;
	if(l==r){
		t[u].sum=a[l];
		if(a[l]==5){
			t[u].l5=t[u].r5=t[u].s5=t[u].sf=1;
		}else{
			t[u].l5=t[u].r5=t[u].s5=t[u].sf=0;
		}
		return;
	}
	int mid=(l+r)/2;
	build1(u*2,l,mid);
	build1(u*2+1,mid+1,r);
	pushup1(u);
}
void modify1(int u,int l,int r,int p,int y){
	if(l==r){
		t[u].sum=y;
		if(y==5){
			t[u].l5=t[u].r5=t[u].s5=t[u].sf=1;
		}else{
			t[u].l5=t[u].r5=t[u].s5=t[u].sf=0;
		}
		return;
	}
	int mid=(l+r)/2;
	if(mid>=p)modify1(u*2,l,mid,p,y);
	else modify1(u*2+1,mid+1,r,p,y);
	pushup1(u);
}
int qry1(int u,int l,int r,int L,int R){
	if(L<=l&&R>=r){
		return t[u].sum;
	}else if(!(l>R||r<L)){
		int mid=(l+r)/2;
		return qry1(u*2,l,mid,L,R)+qry1(u*2+1,mid+1,r,L,R);
	}else return 0;
}
signed main(){
	scanf("%lld%lld",&n,&q);
	init(n);
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		b[i]=a[i];
	}
	build(1,1,n);
	for(int i=1;i<=n;i++){
		a[i]=b[n-i+1];
	}
	build1(1,1,n);
	while(q--){
		scanf("%lld",&op);
		if(op==1||op==4){
			scanf("%lld%lld",&xx,&yy);
		}if(op==1){//两边都要修改 
			if(flag==0){
				modify(1,1,n,xx,yy);
				modify1(1,1,n,n-xx+1,yy);
			}else{
				modify(1,1,n,n-xx+1,yy);
				modify1(1,1,n,xx,yy);
			}
		}else if(op==2){//判断是否反转 
			if(flag==1)flag=0;
			else flag=1;
		}else if(op==3){
			if(flag==0)cout<<w[1].sf<<'\n'; 
			else cout<<t[1].sf<<'\n';
		}else{
			if(flag==0)cout<<qry(1,1,n,xx,yy)<<'\n';//区间求和 
			else cout<<qry1(1,1,n,xx,yy)<<'\n';
		}
	}
	return 0;
}

```

### 其他

若要学习线段树请跳转至[这里](https://www.luogu.com.cn/problem/P3372)。

---

