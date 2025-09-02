# Greedy Subsequences

## 题目描述

对于某个数组 $c$，我们定义“贪心子序列”为一组下标序列 $p_1, p_2, \dots, p_l$，满足 $1 \le p_1 < p_2 < \dots < p_l \le |c|$，并且对于每个 $i \in [1, l-1]$，$p_{i+1}$ 是满足 $p_{i+1} > p_i$ 且 $c[p_{i+1}] > c[p_i]$ 的最小下标。

给定一个数组 $a_1, a_2, \dots, a_n$。对于它的每一个长度为 $k$ 的子区间，求出该子区间的最长贪心子序列的长度。

## 说明/提示

在第一个样例中：

- $[1, 5, 2, 5]$ —— 最长的贪心子序列可以是 $1, 2$（$[c_1, c_2] = [1, 5]$）或 $3, 4$（$[c_3, c_4] = [2, 5]$）。
- $[5, 2, 5, 3]$ —— 贪心子序列为 $2, 3$（$[c_2, c_3] = [2, 5]$）。
- $[2, 5, 3, 6]$ —— 贪心子序列为 $1, 2, 4$（$[c_1, c_2, c_4] = [2, 5, 6]$）。

在第二个样例中：

- $[4, 5, 2, 5, 3, 6]$ —— 最长的贪心子序列可以是 $1, 2, 6$（$[c_1, c_2, c_6] = [4, 5, 6]$）或 $3, 4, 6$（$[c_3, c_4, c_6] = [2, 5, 6]$）。
- $[5, 2, 5, 3, 6, 6]$ —— 贪心子序列为 $2, 3, 5$（$[c_2, c_3, c_5] = [2, 5, 6]$）。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
6 4
1 5 2 5 3 6
```

### 输出

```
2 2 3 
```

## 样例 #2

### 输入

```
7 6
4 5 2 5 3 6 6
```

### 输出

```
3 3 
```

# 题解

## 作者：E1_de5truct0r (赞：7)

## 思路

首先模拟一下样例，找找规律。

给定这样一个序列，因为每个数必须取他后面第一个大于它的数，所以 **每个数的下一个节点是唯一的**。一定会存在这么一些数，他们是**没有下一个节点的**（即它是从当前位置 $x$ 到 $n$ 之间最大的数）。想象一下，把这些点一个个都拎起来，那么每一个节点下面都是一颗树，即是一个**森林**。为了方便操作，我们可以常规操作一下，建立一个**超根** $n+1$，把这些没有下一个节点的点与超根连一条边。然后整个序列就是一个树形结构，两点 $(u,v)$ 之间的连边表示第 $v$ 个点的下一个节点是第 $u$ 个点。

---

方便理解，来搞一下样例：

![](https://cdn.luogu.com.cn/upload/image_hosting/ic2y18nz.png)

先建成这么一个图。

然后，对于第一个数 $1$，把 $1$ 的子树全部加一。

![](https://cdn.luogu.com.cn/upload/image_hosting/ikulpcer.png)

$2$ 至 $k$ 同理（样例 $k=4$）。

![](https://cdn.luogu.com.cn/upload/image_hosting/0mjj35wl.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/98o46w4i.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/87ozd480.png)

然后，此时的 $p_{\max}=2$。

$k+1$ 至 $n$ 添加和之前同理，但是每次要删掉最左边的一个，因为他不在这个区间里。

![](https://cdn.luogu.com.cn/upload/image_hosting/v0ygohe1.png)

此时，$p_{\max}=2$。

最后一个：

![](https://cdn.luogu.com.cn/upload/image_hosting/q3il3gx7.png)

此时，$p_{\max}=3$。

所以，输出为 ```2 2 3```。

各位应该理解了吧？

---

那么每次怎么进行查询呢？可以发现，以每一个点开始的贪心最长上升子序列，**随着右端点的增长，长度是单调不减的**，所以只需要查询长度为 $k$ 中的最长贪心上升子序列即可。暴力的方法显然是每次如果加入了一个数，那么 **所有下一个节点是这个数的位置** 的数，以他们开头的最长贪心上升子序列长度都会加一。查询就是对于 $[l,l+k-1]$ 这个区间中每一个 $i$，以它为开头的最长贪心上升子序列长度（记为 $p_i$）的最大值。

那么暴力显然是 $O(n^2)$，又是一个显然的区间加 & 区间查询最大值 的~~傻星~~线段树板子，用线段树简单优化即可。时间复杂度 $O(n \log n)$，可以通过。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN=1000005;
const int INF=1000000000;

int tr[MAXN<<2],tag[MAXN<<2]; // 线段树 & 懒标
void push_down(int p,int l,int r,int k) // 下传
{
	int mid=(l+r)>>1; 
	tr[p<<1]+=k;
	tr[p<<1|1]+=k;
	tag[p<<1]+=k;
	tag[p<<1|1]+=k;
	tag[p]=0;
}
void add(int p,int l,int r,int st,int ed,int k)
{
	if(st<=l && r<=ed)
	{
		tr[p]+=k;
		tag[p]+=k;
		return;
	}
	if(r<st || l>ed) return;
	int mid=(l+r)>>1;
	push_down(p,l,r,tag[p]);
	add(p<<1,l,mid,st,ed,k);
	add(p<<1|1,mid+1,r,st,ed,k);
	tr[p]=max(tr[p<<1],tr[p<<1|1]);
}
int query(int p,int l,int r,int st,int ed)
{
	if(st<=l && r<=ed) return tr[p];
	if(r<st || l>ed) return 0;
	int mid=(l+r)>>1;
	push_down(p,l,r,tag[p]);
	return max(query(p<<1,l,mid,st,ed),query(p<<1|1,mid+1,r,st,ed));
}

int a[MAXN],nxt[MAXN],dfn[MAXN],s[MAXN],tot;
vector<int> E[MAXN];
void dfs(int u) // 记录每个点的 dfn 序和子树大小（这样每个点的子树中 dfn 序是连续的，线段树修改方便）
{
	dfn[u]=++tot; s[u]=1;
	for(int i=0;i<E[u].size();i++)
	{
		int v=E[u][i];
		dfs(v);
		s[u]+=s[v];
	}
}

int main()
{
	int n,k; scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	
	stack<int> st;
	for(int i=1;i<=n;i++)
	{
		while(st.size() && a[st.top()]<a[i])
			E[i].push_back(st.top()),st.pop();
		st.push(i);
	}
	while(st.size())
		E[n+1].push_back(st.top()),st.pop();
	// 单调栈模拟求前驱（这个和今年，即 2022 年 NOI Online T1 类似）
	
	dfs(n+1); // 求出每个点在树里的 dfn 序和子树大小
	
	for(int i=1;i<=k;i++) add(1,1,n+1,dfn[i],dfn[i]+s[i]-1,1);
	printf("%d",query(1,1,n+1,1,n+1));
	for(int i=k+1;i<=n;i++)
	{
		add(1,1,n+1,dfn[i],dfn[i]+s[i]-1,1); //每次对所有下一个节点是 i 的都 +1（即 i 的子树里。）
		add(1,1,n+1,dfn[i-k],dfn[i-k],-INF); // 删去区间最左边的点（赋极小值相当于是不可能取到）
		printf(" %d",query(1,1,n+1,1,n+1)); // dfn 要从 1 到 n+1，因为一共其实是 n+1 个点
	}
	return 0;
}
```

---

## 作者：wrzSama (赞：5)

## 题意

给定一个长度为 $n$ 的序列 $a$ 和一个整数 $k$，对于该序列所有长度为 $k$ 的子区间求出其中最长的严格上升贪心子序列的长度。严格上升贪心子序列满足如果选择了一个元素，那么下一个要选的元素必须是其后面第一个比它大的元素。

## 思路

设 $dp_i$ 表示从第 $i$ 个元素开始选的严格贪心子序列的长度，先将它们所有的初值都赋成 $1$，从 $1$ 到 $n$ 依次加入所有元素。若加入了一个元素 $a_i$，我们可以二分找到最靠前的l使得区间 $[l,i-1]$ 中的所有元素都小于 $a_i$，二分时要查询的区间最大值可以用 $st$ 表来维护。那么元素 $a_i$ 就可以使区间 $[l,i-1]$ 的所有 $dp$ 值都加 $1$，因为它会接在且仅会接在所有以区间 $[l,i-1]$ 中的元素开头的严格上升贪心子序列的后面。最后，对于每次加入元素 $a_i$，若 $i>=k$，则输出区间 $[i-k+1,i]$ 中 $dp$ 的最大值作为子区间 $[i-k+1,i]$ 的答案。因为涉及区间加法和查询区间最大值的操作，所以可以用线段树来维护 $dp$ 的值。

## 代码

```cpp
#include<bits/stdc++.h>
#pragma GCC O(2)
#pragma GCC O(3)
#pragma O(fast)
using namespace std;
inline int read()
{
	int read_result=0,is_below_0=0;
	char now_ch=0;
	while(!isdigit(now_ch))
	{
		is_below_0|=now_ch=='-';
		now_ch=getchar();
	}
	while(isdigit(now_ch))
	{
		read_result=(read_result<<3)+(read_result<<1)+(now_ch^48);
		now_ch=getchar();
	}
	return is_below_0?-read_result:read_result;
}
inline void write(int x)
{
	if(x<0)
	{
		putchar('-');
		x=-x;
	}
	if(x>9) write(x/10);
	putchar(x%10+'0');
}
int n,k,c[1000001],st[1000001][21],tr[4000001],lz[4000001];
inline void build(int o,int l,int r)
{
	if(l==r)
	{
		tr[o]=1;
		return;
	}
	int mid=(l+r)>>1;
	build(o<<1,l,mid);
	build(o<<1|1,mid+1,r);
	tr[o]=max(tr[o<<1],tr[o<<1|1]);
}
inline void update(int o,int l,int r,int x,int y)
{
	if(x<=l&&r<=y)
	{
		++tr[o];
		++lz[o];
		return;
	}
	int mid=(l+r)>>1;
	if(lz[o])
	{
		tr[o<<1]+=lz[o];
		lz[o<<1]+=lz[o];
		tr[o<<1|1]+=lz[o];
		lz[o<<1|1]+=lz[o];
		lz[o]=0;
	}
	if(x<=mid) update(o<<1,l,mid,x,y);
	if(y>mid) update(o<<1|1,mid+1,r,x,y);
	tr[o]=max(tr[o<<1],tr[o<<1|1]);
}
inline int query(int o,int l,int r,int x,int y)
{
	if(x<=l&&r<=y) return tr[o];
	int mid=(l+r)>>1,res=0;
	if(lz[o])
	{
		tr[o<<1]+=lz[o];
		lz[o<<1]+=lz[o];
		tr[o<<1|1]+=lz[o];
		lz[o<<1|1]+=lz[o];
		lz[o]=0;
	}
	if(x<=mid) res=query(o<<1,l,mid,x,y);
	if(y>mid) res=max(res,query(o<<1|1,mid+1,r,x,y));
	return res;
}
int main()
{
	n=read();
	k=read();
	for(int i=1;i<=n;++i)
	{
		st[i][0]=read();
		c[i]=c[i-1];
		if((1<<(c[i]+1))<=i) ++c[i];
	}
	for(int i=1;i<=20;++i)
	{
		for(int j=1;j<=n;++j)
		{
			if(j+(1<<(i-1))<=n) st[j][i]=max(st[j][i-1],st[j+(1<<(i-1))][i-1]);
			else st[j][i]=st[j][i-1];
		}
	}
	build(1,1,n);
	for(int i=1;i<=n;++i)
	{
		int l=1,r=i;
		while(l<r)
		{
			int mid=(l+r)>>1,maxa=max(st[mid][c[i-mid]],st[mid+i-mid-(1<<c[i-mid])][c[i-mid]]);
			if(maxa>=st[i][0]) l=mid+1;
			else r=mid;
		}
		if(l<i) update(1,1,n,l,i-1);
		if(i<k) continue;
		write(query(1,1,n,i-k+1,i));
		puts("");
	}
	return 0;
}
```


---

## 作者：p_b_p_b (赞：5)

[$$\large \color{purple} My\; Blog$$](https://www.cnblogs.com/p-b-p-b/p/10502681.html)

---------------------

看到题解那么少就来发一篇吧……

---------------------

## 思路

看完题目一脸懵逼，感觉无从下手。

莫名其妙地想到笛卡尔树，但笛卡尔树好像并没有太大作用。

考虑把笛卡尔树改一下：每个点的父亲设为它的右边第一个大于它的位置。

这时突然发现一个很好的性质：搞答案时每次从右边加入一个点$x$时，以$x$的子树中的一个点为起点的长度全都加一。

那么按dfs序建线段树维护区间和、区间加、单点修改为-INF（从左边删点）即可。

--------------------------

## 代码

```cpp
#include<bits/stdc++.h>
clock_t t=clock();
namespace my_std{
    using namespace std;
    #define pii pair<int,int>
    #define fir first
    #define sec second
    #define MP make_pair
    #define rep(i,x,y) for (int i=(x);i<=(y);i++)
    #define drep(i,x,y) for (int i=(x);i>=(y);i--)
    #define go(x) for (int i=head[x];i;i=edge[i].nxt)
    #define templ template<typename T>
    #define sz 1001010
    typedef long long ll;
    typedef double db;
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    templ inline T rnd(T l,T r) {return uniform_int_distribution<T>(l,r)(rng);}
    templ inline bool chkmax(T &x,T y){return x<y?x=y,1:0;}
    templ inline bool chkmin(T &x,T y){return x>y?x=y,1:0;}
    templ inline void read(T& t)
    {
        t=0;char f=0,ch=getchar();double d=0.1;
        while(ch>'9'||ch<'0') f|=(ch=='-'),ch=getchar();
        while(ch<='9'&&ch>='0') t=t*10+ch-48,ch=getchar();
        if(ch=='.'){ch=getchar();while(ch<='9'&&ch>='0') t+=d*(ch^48),d*=0.1,ch=getchar();}
        t=(f?-t:t);
    }
    template<typename T,typename... Args>inline void read(T& t,Args&... args){read(t); read(args...);}
    char __sr[1<<21],__z[20];int __C=-1,__Z=0;
    inline void __Ot(){fwrite(__sr,1,__C+1,stdout),__C=-1;}
    inline void print(register int x)
    {
    	if (__C>1<<20) __Ot(); if (x<0) __sr[++__C]='-',x=-x;
    	while (__z[++__Z]=x%10+48,x/=10);
    	while (__sr[++__C]=__z[__Z],--__Z);__sr[++__C]='\n';
    }
    void file()
    {
        #ifndef ONLINE_JUDGE
        freopen("a.in","r",stdin);
        #endif
    }
    inline void chktime()
    {
        #ifndef ONLINE_JUDGE
        cout<<(clock()-t)/1000.0<<'\n';
        #endif
    }
    #ifdef mod
    ll ksm(ll x,int y){ll ret=1;for (;y;y>>=1,x=x*x%mod) if (y&1) ret=ret*x%mod;return ret;}
    ll inv(ll x){return ksm(x,mod-2);}
    #else
    ll ksm(ll x,int y){ll ret=1;for (;y;y>>=1,x=x*x) if (y&1) ret=ret*x;return ret;}
    #endif
//	inline ll mul(ll a,ll b){ll d=(ll)(a*(double)b/mod+0.5);ll ret=a*b-d*mod;if (ret<0) ret+=mod;return ret;}
}
using namespace my_std;

int n,m;
int a[sz];
struct hh{int t,nxt;}edge[sz<<1];
int head[sz],ecnt;
void make_edge(int f,int t)
{
	edge[++ecnt]=(hh){t,head[f]};
	head[f]=ecnt;
	edge[++ecnt]=(hh){f,head[t]};
	head[t]=ecnt;
}

int dfn[sz],low[sz],cnt;
void dfs(int x,int fa)
{
	dfn[x]=++cnt;
	go(x) if (edge[i].t!=fa) dfs(edge[i].t,x);
	low[x]=cnt;
}

void build()
{
	stack<int>s;
	rep(i,1,n)
	{
		while (!s.empty()&&a[s.top()]<a[i]) make_edge(s.top(),i),s.pop();
		s.push(i);
	}
	while (!s.empty()) make_edge(s.top(),n+1),s.pop();
}

int mx[sz<<2];
int tag[sz<<2];
#define ls k<<1
#define rs k<<1|1
#define lson ls,l,mid
#define rson rs,mid+1,r
void Add(int k,int w){mx[k]+=w;tag[k]+=w;}
void pushdown(int k){Add(ls,tag[k]);Add(rs,tag[k]);tag[k]=0;}
void pushup(int k){mx[k]=max(mx[ls],mx[rs]);}
void add(int k,int l,int r,int x,int y)
{
	if (x<=l&&r<=y) return Add(k,1);
	int mid=(l+r)>>1;
	pushdown(k);
	if (x<=mid) add(lson,x,y);
	if (y>mid) add(rson,x,y);
	pushup(k);
}
void modify(int k,int l,int r,int x)
{
	if (l==r) return void(mx[k]=-1e9);
	int mid=(l+r)>>1;
	pushdown(k);
	if (x<=mid) modify(lson,x);
	else modify(rson,x);
	pushup(k);
}

int main()
{
	file();
	read(n,m);
	rep(i,1,n) read(a[i]);
	build();
	dfs(n+1,0);
	rep(i,1,n) --dfn[i],--low[i];
	rep(i,1,n)
	{
		add(1,1,n,dfn[i],low[i]);
		if (i>m) modify(1,1,n,dfn[i-m]);
		if (i>=m) printf("%d ",mx[1]);
	}
	return 0;
}
```



---

## 作者：Arghariza (赞：3)

简单题。

$i$ 向 $i$ 后**第一个** $j$，$a_j$ 比 $a_i$ 大的点连边，不难发现最后形成了一棵森林，并且一个点的父亲 $\text{fa}_i>i$。

题目变成了取 $[l,r]$ 中的点为起点，向祖先方向走去并且终点编号 $\le r$ 的最长链长度。

考虑离线，维护从每个点开始的最长链长度 $f_i$，答案即全局查询最大值。

如果 $i<l$，相当于删去 $i$ 点，$f_i$ 可以直接赋为 `-inf`，由于询问左端点递增，暴力修改即可。

考虑加入一个右端点 $r$ 对答案的贡献，对于所有 $r$ 子树内并且未被删去的点 $i$，$f_i\gets f_i+1$。

维护子树加，单点修改，全局查询最大值即可，$O(n\log n)$。

[评测记录。](https://codeforces.com/contest/1132/submission/192228376)

---

## 作者：Polaris_Australis_ (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF1132G)

先考虑没有 $k$ 这个限制，直接求整个序列的最长贪心递增子序列，如果从右往左转移，容易发现，每个点只能从其右侧第一个比他大的点转移。所以维护一个单调队列即可，每一时刻的队列大小即为以当前点为开头的子序列长度（先设为 $f_x$，之后要用到）。

接下来考虑正解：关键在于删点操作。容易发现，删除一个点之后所影响到的区间是一段连续区间，这段区间内的 $f_x$ 都要 $-1$，所以现在需要找到这样的一段区间。考虑一个点左侧的 $k-1$ 个点，如果这些点中有的点点权比它大，记为 $end_x$，那么删除 $x$ 所影响的区间为 $[end_x+1,x]$，如果没有点权比它大的，则记 $end_x=x-k$，这样删除 $x$ 所影响的区间也是 $[end_x+1,x]$。而以上这两类分别是从队尾弹出和从队顶弹出，所以在弹出的时候记录即可，把 $f_x$ 统计在线段树中，每次删点的时候区间修改即可。

代码：

```cpp
// Problem: CF1132G Greedy Subsequences
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1132G
// Memory Limit: 250 MB
// Time Limit: 2000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
#define int long long
#define miny(x, y) x = min(x, y)
#define maxy(x, y) x = max(x, y)
#define lowbit(x) ((x) & (-(x)))
#define fu(i, l, r) for (int i = (l); i <= (r); ++i)
#define fd(i, r, l) for (int i = (r); i >= (l); --i)
#define mem(x, y) memset(x, y, sizeof(x))
#define file(x)                 \
  freopen(x ".in", "r", stdin); \
  freopen(x ".out", "w", stdout);
#define mod 998244353
#ifdef int
#define inf 0x3f3f3f3f3f3f3f3f
#else
#define inf 0x3f3f3f3f
#endif
#define inv(x) qp(x, mod - 2)
using namespace std;
namespace Std {
template <typename tp>
void read(tp &x) {
  x = 0;
  int y = 1;
  char c = getchar();
  while (c < '0' || c > '9') {
    if (c == '-') y = -1;
    c = getchar();
  }
  while (c >= '0' && c <= '9') {
    x = (x << 1) + (x << 3) + (c & 15);
    c = getchar();
  }
  x *= y;
}
template <typename tp>
void write(tp x) {
  if (x < 0) {
    putchar('-');
    write(-x);
    return;
  }
  if (x > 9) write(x / 10);
  putchar((x % 10) | 48);
}
int qp(int x, int y) {
  int cmp = 1;
  while (y) {
    if (y & 1) (cmp *= x) %= mod;
    (x *= x) %= mod;
    y >>= 1;
  }
  return cmp;
}
int n, k, ans[1000010], tot, a[1000010], id[1000010], q[1000010], tr[4000010],
    tag[4000010], end[4000010];
inline void pushdown(int x) {
  tr[x << 1] += tag[x];
  tr[x << 1 | 1] += tag[x];
  tag[x << 1] += tag[x];
  tag[x << 1 | 1] += tag[x];
  tag[x] = 0;
}
inline void pushup(int x) { tr[x] = max(tr[x << 1], tr[x << 1 | 1]); }
void change(int x, int l, int r, int L, int R, int num) {
  if (L <= l && r <= R) {
    tr[x] += num;
    tag[x] += num;
    return;
  }
  pushdown(x);
  int mid = (l + r) >> 1;
  if (L <= mid) change(x << 1, l, mid, L, R, num);
  if (R > mid) change(x << 1 | 1, mid + 1, r, L, R, num);
  pushup(x);
}
void modify(int x, int l, int r, int pos, int num) {
  if (l == r) {
    tr[x] = num;
    return;
  }
  pushdown(x);
  int mid = (l + r) >> 1;
  if (pos <= mid)
    modify(x << 1, l, mid, pos, num);
  else
    modify(x << 1 | 1, mid + 1, r, pos, num);
  pushup(x);
}
int query(int x, int l, int r, int L, int R) {
  if (L <= l && r <= R) return tr[x];
  if (L > r || l > R) return 0;
  pushdown(x);
  int mid = (l + r) >> 1;
  return max(query(x << 1, l, mid, L, R), query(x << 1 | 1, mid + 1, r, L, R));
}
bool cmp(int x, int y) { return a[x] < a[y]; }
void main() {
  read(n);
  read(k);
  fu(i, 1, n) read(a[i]), id[i] = i;
  int head = 1, tail = 0;
  fd(i, n, n - k + 2) {
    while (head <= tail && a[i] >= a[q[tail]]) end[q[tail--]] = i;
    q[++tail] = i;
    modify(1, 1, n, i, tail - head + 1);
  }
  fd(i, n - k + 1, 1) {
    while (head <= tail && a[i] >= a[q[tail]]) end[q[tail--]] = i;
    q[++tail] = i;
    modify(1, 1, n, i, tail - head + 1);
    if (i + k <= n && q[head] - i == k) end[q[head++]] = i - 1;
    if (i + k <= n) change(1, 1, n, end[i + k] + 1, i + k, -1);
    ans[i] = query(1, 1, n, i, i + k - 1);
  }
  fu(i, 1, n - k + 1) printf("%lld ", ans[i]);
  puts("");
}
}  // namespace Std
#undef int
int main() {
  Std::main();
  return 0;
}
```


---

## 作者：Parabola (赞：2)

### Part0.题外话

这篇题解我没有什么题外话欸...

那就“瑠衣赛高！”⑧

------------

### Part1.思路

所以说刚开始做着题的时候，我同学看了下p_b_p_b神佬的题解（Orz p_b_p_b)，说是笛卡尔树。

然后我就一直往笛卡尔树那个方向想...

搞了半天，老师都讲题了，我还没做出来。

后来我才知道为什么p_b_p_b把它叫“笛卡尔树”

只不过是建个树出来，用笛卡尔树的构造方法罢了...

可以一眼看见，对于每一个序列上的每一个点，它下一个满足“Greedy Subsequences”的点是固定的。

所以我们可以依靠这个东西建一棵树。

什么意思？

对于每一个$i$，我们找到最小的$j$满足$(i<j , A[i] > A[j])$，然后把$i$的爸爸设置成$j$

然后这会有个森林。

于是在序列最后面加上一个$\rm inf$ ，就会有棵树

到这里熟练的同学已经熟练地上了一个栈建出了这个树（和笛卡尔差不多）

然后我们看看，序列上一个Greedy Subsequences一定是上面的一段连续路径

记$Ans[i]$代表当$i$作为起点时，Greedy Subsequences的长度

发现每一个点被加入到询问区间的时候，它的子树所有的$Ans$都会+1

然后从询问区间删除的时候，它子树$Ans$都会-1

每一次询问就回答整棵树中$Ans$最大值就好了

换句话来说，你现在维护一棵树，支持两个操作

1. u k

以u的根节点的子树点权都加上k

2.u

询问以u为根的子树点权最大值是多少

然后这里十分熟练地上了一个dfs序+线段树

------------

### Part3.Code
```cpp
#include<bits/stdc++.h>
#define lc (o << 1)
#define rc (lc | 1)
#define mid ((l + r) >> 1)
#define mp(x , y) make_pair(x , y)
using namespace std;

typedef pair<int , int> pii;

const int MAXN = 1000000 + 5;
const int inf = 0x3f3f3f3f;

int n , k , dfs_clock , A[MAXN] , dfn[MAXN] , sz[MAXN];

vector <int> G[MAXN];
stack <pii> s;

inline void add(int u , int v) {G[u].push_back(v);}

void dfs(int u) {
	sz[u] = 1 , dfn[u] = ++dfs_clock;
	for(int i = 0 ; i < (int)G[u].size() ; ++i) dfs(G[u][i]) , sz[u] += sz[G[u][i]];
}

int maxv[MAXN << 2] , addv[MAXN << 2];
inline void up(int o) {maxv[o] = max(maxv[lc] , maxv[rc]);}
inline void Add(int o , int k) {maxv[o] += k , addv[o] += k;}
inline void down(int o) {
	if(addv[o]) {
		Add(lc , addv[o]); Add(rc , addv[o]);
		addv[o] = 0;
	}
}
inline void modify(int o , int l , int r , int ql , int qr , int k) {
	if(qr < l || ql > r) return ;
	if(ql <= l && r <= qr) return Add(o , k);
	down(o);
	modify(lc , l , mid , ql , qr , k); modify(rc , mid + 1 , r , ql , qr , k);
	up(o);
}

int main() {
	scanf("%d %d" , &n , &k);
	for(int i = 1 ; i <= n ; ++i) scanf("%d" , A + i);
	A[++n] = inf;
	for(int i = 1 ; i <= n ; ++i) {
		while(!s.empty() && s.top().first < A[i]) add(i , s.top().second) , s.pop();
		s.push(mp(A[i] , i));
	}
	dfs(n);
	for(int i = 1 ; i <= k ; ++i) modify(1 , 1 , n , dfn[i] , dfn[i] + sz[i] - 1 , 1);
	printf("%d " , maxv[1]);
	for(int i = k + 1 ; i < n ; ++i) {
		modify(1 , 1 , n , dfn[i] , dfn[i] + sz[i] - 1 , 1); 
		modify(1 , 1 , n , dfn[i - k] , dfn[i - k] + sz[i - k] - 1 , -1);
		printf("%d " , maxv[1]);
	}
	return 0;
} 
```


---

## 作者：elbissoPtImaerD (赞：1)

在模拟赛之后一周做到，不好评价。

对于每个 $i$ 考虑往 $\min\limits_{a_i<a_j,i<j}j$ 连有向边，最后会连成一颗根向树，以一个点作为开始就是一直跳父边，扫描 $r$，类似双指针移动 $l$，维护 $f_i$ 表示以 $i$ 开始不跳出 $r$ 的最长链长，那么 加入 $r$ 相当于做子树加，删除 $l$ 做的是单点修改，回答询问是全局最大值，使用线段树维护之，复杂度 $O(n\log n)$。

所以你为什么开 $10^6$。

[$\color{green}{\checkmark}$](https://www.luogu.com.cn/record/161480187)

---

## 作者：Luciylove (赞：1)

长度为 $k$ 相当于固定右端点扫描线。

尝试维护所有左端点的答案，并维护一个区间最大值。

那么新增 $a_i$ 相当于维护所有会导向到 $i$ 的左端点，这个可以建树解决。

然后那我们放弃了序列轴的区间查询，所以我们尝试全局最大值，然后就可以使用单点设 $-\inf$ 来维护。

然后你就做完了。

复杂度 $O(n \log n)$。

```cpp
#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = l; i <= r; i ++)
#define per(i, r, l) for (int i = r; i >= l; i --)
#define ckmin(x, v) x = x > v ? v : x 
#define int long long
#define lc x << 1
#define rc x << 1 | 1

using namespace std;
using ll = long long;
const int _ = 1e6 + 5;
const ll inf = 1e16;

int read() {
	int X = 0;
	char ch = 0, w = 0;
	while (ch < 48 || ch > 57)ch = getchar(), w |= (ch == '-');
	while (ch >= 48 && ch <= 57)X = X * 10 + (ch ^ 48), ch = getchar();
	return w ? -X : X;
}

int n, k;
int a[_], stk[_], top, ret;
int add[_ << 2], mx[_ << 2];
void apply (int x, int k) { add[x] += k, mx[x] += k; }
void pushdown (int x) { if (add[x]) apply(lc, add[x]), apply(rc, add[x]), add[x] = 0; }
void modify (int x, int l, int r, int ql, int qr, int k) {
	if (ql <= l && r <= qr) return apply(x, k);
	int mid = (l + r) >> 1; pushdown(x);
	if (ql <= mid) modify(lc, l, mid, ql, qr, k);
	if (qr > mid) modify(rc, mid + 1, r, ql, qr, k);
	return mx[x] = max(mx[lc], mx[rc]), void();
}

vector <int> e[_];
int dfc, dfn[_], sz[_], nxt[_];
void dfs (int x) {
	dfn[x] = ++ dfc, sz[x] = 1;
	for (int y : e[x]) dfs(y), sz[x] += sz[y];
}
signed main () {
	n = read(), k = read();
	rep(i, 1, n) {
		a[i] = read();
		while (top >= 1 && a[stk[top]] < a[i])
			nxt[stk[top]] = i, top --;
		stk[++ top] = i;
	}
	rep(i, 1, n) e[nxt[i]].push_back(i);
	rep(i, 1, n) if (!nxt[i]) dfs(i);
	rep(i, 1, n) {
		if (i > k)
			modify(1, 1, n, dfn[i - k], dfn[i - k], -inf);
		modify(1, 1, n, dfn[i], dfn[i] + sz[i] - 1, 1);
		if (i >= k)
			printf("%d ", mx[1]);
	}
	return 0;
}
```

---

## 作者：qwerty_pwp (赞：0)

# CF1132G Solution

## The Problem

有一个长度为 $n$ 的序列，你需要对于每个长度为 $k$ 的区间，找出最长的子序列满足：

在这个子序列中，每一项（除第一项外）都恰好是子序列中前一项在原序列中从它开始往后第一个严格大于它的元素。

$1 \leq k \leq n \leq 10^6$；给出的序列 $A$ 中，所有元素（正整数）$a_i$ 的大小不超过 $n$.

## Before The Solution

第一步想到的是建树，但是没有想到怎么处理答案。

先想到可以跑 dfs，一边跑一边使用双指针。但是问题在于，双指针只针对于链上的所有极大满足条件的段求解，但是答案不一定只出现在其中。如果统计所有区间的话，复杂度就会爆炸。

于是便想到可以用滑动窗口的方式，动态地由前一个区间转移到后一个区间。

然后问题就变成了如何动态更新每个节点的信息。想到可以用 $f_i$ 表示与 $i$ 有关的最大段的解，那么，应该将 $i$ 放在开头还是结尾呢？

考虑到放在开头，加值时就变成了根节点要从儿子更新，而删除时要从下往上一层一层更新，平方的复杂度不能满足要求。

于是用 $f_i$ 表示以 $i$ 为结尾的答案。加入一个点就代表了子树同时加。再加上线段树可以做到一个 $\log$。然后再处理一些细节。

## Solution

我们将原序列中每一项与从它开始往后第一个严格大于它的元素建立父子关系，其中 $a_i$ 较小的是儿子。

注意到每个节点最多只有一个父亲，于是所有的节点构成了森林。我们将所有树根连接到一个超级节点（编号为 $n+1$）上，于是变成了一颗有 $n+1$ 个结点的有根树。

我们令子树的节点 $i$ 代表序列中的第 $i$ 个元素，记节点 $i$ 的父亲为 $f_i$，我们有 $f_i>i$.

令 $d_i$ 为在限定范围内，最长的以 $a_i$ 为结尾的合法子序列的长度，那么有 $d_i=d_{f_i}+1$.

因为是每个长度固定为 $k$ 的区间，所以，我们考虑用从左往右滑动窗口的方式来求出所有区间的答案。具体有如下 $2$ 种操作：

1. 将序列最左侧的元素删除，这个节点在序列中的编号为 $i$。本操作在我们构建出的树上体现为：将节点 $i$ 设为一个极小的值,（至少小于等于 $-N$，保证动态转移时，它不能再变成正的）。这样做并不会影响到以 $i$ 为根的子树中的其它节点，因为，我们有 $f_i>i$，这样就保证了在节点 $i$ 删除前，以节点 $i$ 为根的子树中的其它节点都已经被删除。

2. 在序列右侧加入一个节点，这个节点在序列中的编号为 $i$。本操作在我们构建出的树上体现为：将以 $i$ 为根的子树中所有元素 $+1$。由于我们已经将被删除的节点设为了一个极小值，所以加它并不会使它影响答案。我们同样可以由 $f_i>i$ 保证，在加入节点 $i$ 时，以节点 $i$ 为根的子树中的其它节点都已经被加入过了。

在滑动窗口时，每次先将目标区间向右扩展一格，若区间长度大于 $k$ 则将左端点后移一格，并统计答案。

将子树全局加可以用 dfn 序转化为区间加，而求最大值实际上我们可以直接可以求整棵树上的最大值（根据上文证明这是可行的）。

于是就转化成了一个线段树区间加，区间求和的问题。

时间复杂度 $O(n\log n)$，空间复杂度 $O(n)$，可以通过本题。

## The Sample

在这里，我们用原题中的第一组样例来进行说明：

| 样例输入                 | 样例输出      |
| :----------------------- | :------------ |
| $6~4~1~5~2~5~3~6$ | $2~2~3$ |

首先，我们用单调栈求出所有的 $f_i$：

|  $i$  | $1$  | $2$  | $3$  | $4$  | $5$  |       $6$       |
| :---: | :--: | :--: | :--: | :--: | :--: | :-------------: |
| $f_i$ | $2$  | $6$  | $4$  | $6$  | $6$  | $7$（超级节点） |

然后建出这颗树：

![](https://cdn.luogu.com.cn/upload/image_hosting/959rxa3k.png)

然后，我们滑动窗口（按照加入和删除操作在树上的体现），每次找到全树上最大值，得到答案：

| 区间 | $[1,4]$ | $[2,5]$ | $[3,6]$ |
| :--: | :-----: | :-----: | :-----: |
| 答案 |   $2$   |   $2$   |   $3$   |

即为样例的答案。

## AC Code

```cpp
//CF Submission #304533022
//Time:1.75s Memory:184500Kb
//tag 2400
#include <bits/stdc++.h>
using namespace std;
const int N=1000005;
int n,k,cnt,a[N],fa[N],dfn[N],siz[N];
//fa:节点在有根树上的祖先
//dfn:节点在有根树上的dfn序
//siz:子树大小
vector <int> s[N];
//存储父子关系
stack <pair <int,int> > stk;
inline void run(int x) {//跑dfn序以及求子树大小
	dfn[x]=++cnt;
	siz[x]=1;
	for(int i=0;i<s[x].size();++i) {
		run(s[x][i]);
		siz[x]+=siz[s[x][i]];
	}
}
struct node {
	int sum;
	int tag;
}tr[N << 4];
inline void update(int x) {//这3个函数是线段树的
	tr[x].sum=max(tr[x << 1].sum,tr[x << 1 | 1].sum);
}
inline void pushdown(int x) {
	tr[x << 1].sum+=tr[x].tag;
	tr[x << 1 | 1].sum+=tr[x].tag;
	tr[x << 1].tag+=tr[x].tag;
	tr[x << 1 | 1].tag+=tr[x].tag;
	tr[x].tag=0;
}
inline void add(int x,int l,int r,int ll,int rr,int k) {
	if(l>=ll && r<=rr) {
		tr[x].sum+=k;
		tr[x].tag+=k;
		return ;
	}
	pushdown(x);
	int mid=(l+r) >> 1;
	if(mid>=ll) add(x << 1,l,mid,ll,rr,k);
	if(mid<rr) add(x << 1 | 1,mid+1,r,ll,rr,k);
	update(x);
}
signed main() {
	cin >> n >> k;
	for(int i=1;i<=n;++i) cin >> a[i];
	a[n+1]=INT_MAX;
	for(int i=1;i<=n+1;++i) {//找到序列中每个数，向右看第一个比它严格大的数（单调栈）
		while(!stk.empty() && stk.top().second<a[i]) {
			fa[stk.top().first]=i;
			s[i].push_back(stk.top().first);
			stk.pop();
		}
		stk.push(make_pair(i,a[i]));
	}
	run(n+1);
	for(int i=1;i<=n;++i) {//滑动窗口
		add(1,1,n+1,dfn[i],dfn[i]+siz[i]-1,1);
		if(i>k) add(1,1,n+1,dfn[i-k],dfn[i-k],-N);
		if(i>=k) cout << tr[1].sum << ' ';//因为是全局最大值，就不用写query函数了
	}
	return 0;
}
```

---

## 作者：wfc284 (赞：0)

显然每个数的后继是固定的。  
处理每个区间，应该是每次加一个点，删一个点。但是我们发现原来的模型对于加点和删点并不友好，每次要影响到的点是散的，并不是一个连续的区间。

我们考虑将后继关系建出树形结构。具体地，将一个点的父亲设为其后继。没有后继的，向 $0$ 号根结点连边。每个结点的深度就是其 Greedy Subsequence 的长度。  
然后我们对树做出 DFS 序。我们发现，加一个点影响到的恰好是其子树内的点，即将子树内的点深度加一。  
删一个点似乎不好直接在 DFS 序上维护。换个角度，我们将其深度修改为 $-\infty$，让答案不可能取到它就行。

于是，我们需要一个支持区间修改（加一，及单点修改）、查询全局最大的数据结构。可以采用线段树。  
时间复杂度 $O(n\log n)$。

[submission.](https://codeforces.com/contest/1132/submission/305429591)

---

