# Ehab's Last Corollary

## 题目描述

给出一张 $n$ 个点的无向连通图和一个常数 $k$。

你需要解决以下两个问题的任何一个：
1. 找出一个大小为 $\lceil\frac k2\rceil$ 的独立集。
2. 找出一个大小不超过 $k$ 的环。

独立集是一个点的集合，满足其中任意两点之间在原图上没有边直接相连。

可以证明这两个问题必然有一个可以被解决。

## 样例 #1

### 输入

```
4 4 3
1 2
2 3
3 4
4 1```

### 输出

```
1
1 3```

## 样例 #2

### 输入

```
4 5 3
1 2
2 3
3 4
4 1
2 4```

### 输出

```
2
3
2 3 4```

## 样例 #3

### 输入

```
4 6 3
1 2
2 3
3 4
4 1
1 3
2 4```

### 输出

```
2
3
1 2 3```

## 样例 #4

### 输入

```
5 4 5
1 2
1 3
2 4
2 5```

### 输出

```
1
1 4 5```

# 题解

## 作者：一扶苏一 (赞：14)

## 【CF1364D】 Ehab's Last Corollary

### Analysis

有点诡异的题，可能需要一点灵光乍现？（

出于一些灵光，我们首先考虑 $k = n$ 的情况。构造答案很简单：

- 如果图是一棵树，那么直接对图进行黑白染色，显然同色结点构成了一个独立集，因此输出那个 size 不小于 $\left \lceil \frac k 2 \right \rceil$ 的集合的前 $\left \lceil \frac k 2 \right \rceil$ 个元素即可。
- 否则因为是连通图，图上一定存在环，大小显然不大于 $k$，因此直接输出这个环即可。

现在考虑 $n > k$ 的情况。注意到题目描述中“I have a proof that for any input you can always solve at least one of these problems”，因此给定的图的任一大小为 $k$ 的子图一定能找到解。因此我们在原图上随便选一个节点数为 $k$ 的连通块，然后问题就转化为了 $k = n$ 的情况，按照上面叙述找答案即可。

找环的方法是，从某个节点开始 dfs，用栈维护 dfs 树上当前节点到根的所有节点。如果在 dfs 过程中找到了下一个结点 $v$ 在栈里，那么当前栈顶元素到 $v$ 之间的所有节点构成了一个环。

### Code

```cpp
namespace Fusu {

const int maxn = 200005;

int n, m, t, cnt = 1;
bool vis[maxn];
std::pair<int, int> edge[maxn];
std::vector<int> e[maxn], ans[2];
std::queue<int> Q;

void dfs(const int u, const int v);
void dfs(const int u, const int v, const int fa);

void Main() {
  qr(n); qr(m); qr(t);
  for (int i = 1; i <= m; ++i) {
    qr(edge[i].first); qr(edge[i].second);
    e[edge[i].first].push_back(edge[i].second);
    e[edge[i].second].push_back(edge[i].first);
  }
  Q.push(1);
  vis[1] = true;
  while (cnt != t) {
    int u = Q.front(); Q.pop();
    for (auto v : e[u]) if (vis[v] == false) {
      vis[v] = true;
      Q.push(v);
      if (++cnt == t) break;
    }
  }
  for (int i = 1; i <= n; ++i) {
    e[i].clear();
  }
  int ecnt = 0;
  for (int i = 1; i <= m; ++i) {
    int u = edge[i].first, v = edge[i].second;
    if (vis[u] && vis[v]) {
      ++ecnt;
      e[u].push_back(v);
      e[v].push_back(u);
    }
  }
  memset(vis, 0, sizeof vis);
  if (ecnt == (t - 1)) {
    puts("1");
    dfs(1, 0, 0);
    int v = 0;
    int tt = t >> 1;
    if (t & 1) ++tt;
    if (ans[v].size() < tt) v = 1;
    for (int i = 0; i < tt; ++i) qw(ans[v][i], ' ');
    putchar('\n');
  } else {
    puts("2");
    dfs(1, 0);
  }
}

void dfs(const int u, const int w, const int fa) {
  ans[w].push_back(u);
  for (auto v : e[u]) if (v != fa) {
    dfs(v, w ^ 1, u);
  }
}

int top;
int stk[maxn];
std::vector<int> a;
void dfs(const int u, const int fa) {
  stk[++top] = u;
  vis[u] = true;
  for (auto v : e[u]) if (v != fa) {
    if (vis[v]) {
      while (stk[top] != v) {
        a.push_back(stk[top--]);
      }
      a.push_back(v);
      qw(a.size(), '\n');
      for (auto u : a) qw(u, ' ');
      putchar('\n');
      exit(0);
    } else {
      dfs(v, u);
    }
  }
  --top;
}

} // namespace Fusu
```



---

## 作者：WardLee (赞：10)

假如图是一棵树

按深度进行黑白染色即可，细节是某个颜色的节点数可能小于 $(k + 1) / 2$，需要另加判断。

如果不是一棵树

找到图中的最小环，如果节点数不超过 $k$，直接输出环；如果节点数大于 $k$，则在环上每隔一个点取一个点，则一定可以构造出符合要求的独立集。

代码中遇到节点数不超过 $k$  的环就直接输出了。码风较丑。

```cpp
#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = (j); i <= (k); i ++)
#define frep(i, j, k) for(int i = (j); i >= (k); i --)
#define mrep(i, h, j) for(int i = (h[j]); ~i; i = ne[i])
#define mset(a, v) memset(a, v, sizeof(a))
#define mcpy(a, v) memcpy(a, v, sizeof(a))

using namespace std;
typedef long long LL;
typedef pair<int, int> PII;

const int N = 100010, M = N << 2;
int n, m, K, mx, S, T;
int h[N], e[M], ne[M], idx;
int dep[N], cnt[N];
bool st[N], col[N];
vector<int> v, res1, res2;

void add(int a, int b){
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

//找最小环
void dfs(int u){
    v.push_back(u);
    dep[u] = v.size();
    mrep(i, h, u){
        int j = e[i];
        if(!dep[j]) dfs(j);
        else if(dep[j] == dep[u] - 1) cnt[u] ++;
        if(dep[j] < dep[u] - 1 || cnt[u] == 2){
            int t = dep[u] - dep[j] + 1;
            if(t <= K){
                printf("2\n%d\n", t);
                rep(k, dep[j] - 1, dep[u] - 1) printf("%d ", v[k]);
                exit(0);
            }
            else if(t <= mx){
                mx = t;
                S = u, T = j;
            }
        }
    }
    v.pop_back();
}

//输出独立集
void dfs1(int u){
    v.push_back(u);
    dep[u] = v.size();
    if(u == T){
        puts("1");
        for(int k = 0; k < K; k += 2) printf("%d ", v[k]);
        exit(0);
    }
    mrep(i, h, u){
        int j = e[i];
        if(u == S && j == T) continue;
        if(!dep[j]) dfs1(j);
    }
    v.pop_back();
}

//树的情况
void dfs2(int u){
    st[u] = true;
    if(col[u]) res1.push_back(u);
    else res2.push_back(u);
    mrep(i, h, u){
        int j = e[i];
        if(!st[j]){
            col[j] = !col[u];
            dfs2(j);
        }
    }
}

int main(){
    scanf("%d%d%d", &n, &m, &K);
    mset(h, -1);
    while(m --){
        int a, b;
        scanf("%d%d", &a, &b);
        add(a, b), add(b, a);
    }
    mx = n;
    dfs(1);
    if(S){
        mset(dep, 0);
        dfs1(S);
    }
    puts("1");
    dfs2(1);
    int t = (K + 1) / 2;
    if(res1.size() >= t){
        rep(i, 0, t - 1) printf("%d ", res1[i]);
    }
    else{
        rep(i, 0, t - 1) printf("%d ", res2[i]);
    }
    return 0;
}
```

---

## 作者：WYXkk (赞：7)

题目中有这么一段话：

> I have a proof that for any input you can always solve at least one of these problems, **but it's left as an exercise for the reader.**

然而，你（几乎）不得不找出这个证明，才可能做出这题……

那么就试图证明一下：

首先可以发现，如果一个环的长度超过 $k$，那么似乎可以每隔一个点取一个点，然后就……

构造出了一个大小至少为 $\left\lfloor\dfrac {k+1}2\right\rfloor=\left\lceil\dfrac k2\right\rceil$ 的独立集？！

然而事实上并不是，因为环上的点之间还可能有除环外的连边。

那么，如果直接取最小环，显然点之间除了环边就没有连边了，否则会与最小性矛盾。

于是，这个环，要么满足条件 $2$，要么隔一个点取一个点能够满足条件 $1$。

啊不对，似乎还少了无环（即树）的情况。

众所周知树是二分图，因此其两边至少有一边有 $\left\lceil\dfrac n2\right\rceil$ 个点，取点更多的一边能够满足条件 $1$。

$\texttt{Q.E.D.}$

树的情况可以如上处理，至于有环的情况……

这个图这么多点，找个锤子的最小环……

可以发现，只要 **环上的点之间没有除环外的连边** 即可。

我们可以先用 dfs 随便找个环，然后依次考虑每条边，如果其两端点是环上两个不相邻点，那就砍断其中一边，换成新的边。

这里可以用链表（？）实现，详情可以参照代码。

最后得到的环显然点之间没有环以外的连边（否则会在上面的一步中优化掉），按照证明中的思路分类讨论即可。

$\texttt{code:}$

```cpp
#include<cstdio>
#include<iostream>
#include<fstream>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
#define Set(a) memset(a,0,sizeof(a))
#define F(i,a,b) for(register int i=a,i##end=b;i<=i##end;++i)
#define UF(i,a,b) for(register int i=a,i##end=b;i>=i##end;--i)
#define openf(a) freopen(#a".in","r",stdin);freopen(#a".out","w",stdout)
#define re register
#define ri re int
#define il inline
typedef long long ll;
typedef unsigned long long ull;
template<typename T> inline T rd(T& x)
{
	T f=1;x=0;char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
	for(; isdigit(c);c=getchar()) x=(x<<3)+(x<<1)+(T)(c-'0');
	x*=f;
	return x;
}
ll rd(){ll x;rd(x);return x;}
inline int max(int a,int b){return a>b?a:b;}
inline int min(int a,int b){return a<b?a:b;}
const int inf=1<<30;

const int N=100005;
const int M=200005;
int u[M],v[M];
int head[N],to[M*2],nxt[M*2],tot=0;
void add(int u,int v){to[++tot]=v;nxt[tot]=head[u];head[u]=tot;}
int stk[N],top=0;
bool in[N];
bool dfs(int u,int f)
{
	stk[++top]=u;
	if(in[u]) return 1;
	in[u]=1;
	for(ri i=head[u];i;i=nxt[i]) if(to[i]!=f)
	{
		bool x=dfs(to[i],u);
		if(x) return 1;
	}
	--top;in[u]=0;return 0;
}
bool col[N];
void dfs2(int u,int f,bool c)
{
	col[u]=c;
	for(ri i=head[u];i;i=nxt[i]) if(to[i]!=f) dfs2(to[i],u,c^1);
}
int nnxt[N];bool in2[N];
int main()
{
	int n=rd();int m=rd();int k=rd();
	F(i,1,m) {rd(u[i]);rd(v[i]);add(u[i],v[i]);add(v[i],u[i]);}
	bool x=dfs(1,0);
	if(!x)
	{
		dfs2(1,0,0);k=(k+1)/2;
		int c[2];c[0]=c[1]=0;
		F(i,1,n) ++c[col[i]];
		puts("1");
		if(c[0]>=k) F(i,1,n) {if(col[i]==0) printf("%d ",i),--k;if(!k) break;}
		else F(i,1,n) {if(col[i]==1) printf("%d ",i),--k;if(!k) break;}
		puts("");
	}
	else
	{
		int u0=stk[top];--top;int lst=u0;in2[u0]=1;
		while(stk[top]!=u0)
		{
			nnxt[stk[top]]=lst;
			in2[stk[top]]=1;
			lst=stk[top];
			--top;
		}
		nnxt[u0]=lst;
		F(i,1,m)
		{
			int a=u[i],b=v[i];
			if(in2[a]&&in2[b]) if(nnxt[a]!=b&&nnxt[b]!=a)
			{
				for(ri c=nnxt[a];c!=b;c=nnxt[c]) in2[c]=0;
				nnxt[a]=b;
			}
		}
		int cnt=0;
		F(i,1,n) if(in2[i]) u0=i,++cnt;
		if(cnt<=k)
		{
			puts("2");
			printf("%d\n",cnt);
			printf("%d ",u0);
			for(ri i=nnxt[u0];i!=u0;i=nnxt[i]) printf("%d ",i);
			puts("");
		}
		else
		{
			puts("1");k=(k+1)/2;
			for(ri i=u0;k;i=nnxt[nnxt[i]],--k) printf("%d ",i);
			puts("");
		}
	}
	return 0;
}
```



---

## 作者：EuphoricStar (赞：6)

简单题。

特判掉 $m = n - 1$ 的情况，此时一定能找到一个大小为 $\left\lceil\frac{k}{2}\right\rceil$ 的独立集，二分图染色即可。

否则，我们建出 dfs tree，找到一条连接的两个端点深度之差最小的返祖边，设它为 $(u, v)$，且 $dep_u > dep_v$。

若环长 $c = dep_u - dep_v + 1 \le k$ 就完成任务了，否则 $c > k$，我们在环上隔一个点取一个点即可，这样可构成独立集。因为这是长度最小的环，所以中间不会再出现返祖边。

[code](https://codeforces.com/problemset/submission/1364/213432125)

---

## 作者：45dino (赞：5)

注意到题目说了一句神秘的话：
>I have a proof that for any input you can always solve at least one of these problems, but it's left as an exercise for the reader.

既然题目这么说，就尝试着证明一下！

大概可以这样理解：如果某一个环的长度不超过 k ，即为所求；如果所有环的长度都大于 k ，或根本就没有环，那么肯定是可以有一个大小为 $\lceil \frac 2 k \rceil$ 的独立集的。

那么如何实现呢？注意到判环的要求更严格，所以先判断有没有环。

用一个栈存储当前 DFS 到的元素，同时记录下每一个元素入栈的时间截，如果 x 可以到 y 且 y 先入栈，那么这个环的大小就是 $dfn_x-dfn_y+1$ 。（感觉有点像 tarjan)

```cpp
void dfs(int x,int fa)
{
	st.push_back(x);
	dfn[x]=(int)st.size();
	for(int i=head[x];i;i=edge[i].next)
		if(edge[i].to!=fa)
		{
			if(!dfn[edge[i].to])
			{
				dfs(edge[i].to,x);
				continue;
			}
			if(dfn[x]-dfn[edge[i].to]+1<=k&&dfn[x]+1>=dfn[edge[i].to])
			{
				puts("2");
				cout<<dfn[x]-dfn[edge[i].to]+1<<endl;
				for(int j=dfn[edge[i].to]-1;j<dfn[x];j++)
					cout<<st[j]<<" ";
				exit(0);
			}
		}	
	st.pop_back();
}
```

如果判环失败，再找独立集。

注意到独立集的要求就是集内任意两个点都不相邻，所以用染色法即可（有点像二分图判定）

```cpp
void color(int x,int c)
{
	col_gro[c].push_back(x);
	col[x]=c;
	if(col_gro[c].size()==kk)
	{
		puts("1"); 
		for(int i=0;i<col_gro[c].size();i++)
			cout<<col_gro[c][i]<<" ";
//		for(int i:col_gro[c])
//			cout<<i<<" ";
		exit(0);
	}
	for(int i=head[x];i;i=edge[i].next)
		if(col[edge[i].to]==-1)
			color(edge[i].to,c^1);
}
```

所以这道题~~巧妙~~地将 tarjan 和二分图染色法判断结合到了一起（雾

总结：一个思维难度不算高，代码难度在蓝题里中等偏上的奇怪题

---

## 作者：Resurgammm (赞：5)

$update:$ 增加了 $\text{Reference}$

挺妙的构造题。

先建一棵 DFS 树，在无向连通图的 DFS 树中，所有的非树边都是后向边，所以可以应用这一性质。

在这个过程中对于一条非树边 $(u,v)$，已知其一定是后向边，那么若 $|dep_u-dep_v|\leq k$，那么就能找到一个大小不超过 $k$ 的简单环。

否则分两种情况讨论：

* $m=n-1$

	那么把节点按深度奇偶分一下，取大小较大的那一个集合，其子集一定能满足大小为 $\lceil\frac{k}{2}\rceil$。
 
* $\text{Otherwse}$

	一定存在一对 $(u,v)$ 满足 $|dep_u-dep_v|>k$，那么这棵 DFS 树一定深度大于 $k$，且不存在连接深度差为 $[2,k)$ 的非树边。
    
    那么就找到深度最大的点每次条两个父亲就能得到合法的独立集。
        
$\texttt{Code:}$

```cpp
#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define rint register int
#define int long long
using namespace std;
namespace IO{
	#define File(x,y) freopen(#x,"r",stdin),freopen(#y,"w",stdout)
	inline int read(){
		int w=0,f=1; char ch=getchar();
		while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();}
		while(ch>='0'&&ch<='9'){w=(w<<3)+(w<<1)+(ch^48); ch=getchar();}
		return w*f;
	}
	inline void write(int x){
  		static int sta[35]; int top=0;
  		if(x<0) putchar('-'),x=-x;
  		do{sta[++top]=x%10,x/=10;}while(x);
  		while(top) putchar(sta[top--]+48); puts("");
	}
}
using namespace IO;
namespace CL{
	#define fill(x,y) memset(x,y,sizeof(x))
	#define copy(x,y) memcpy(x,y,sizeof(y))

	const int maxn=2e5+5;
	
	int n,m,k,top;
	int f[maxn],dep[maxn],stk[maxn];
	bool vis[maxn];
	queue<int> q1,q2;
	namespace Graph{
		int head[maxn],id;
		struct e{int v,next;}edge[maxn<<1];
		inline void add(int u,int v){
			edge[++id].v=v;
			edge[id].next=head[u];
			head[u]=id;
		}
	}using namespace Graph;
	inline int get(int x){return (x&1)?(x>>1)+1:(x>>1);}
	inline void solve1(){
		puts("1");
		if(m==n-1){
			for(int i=1;i<=n;i++){
				if(dep[i]&1) q1.push(i);
				else q2.push(i);
			}
			if(q1.size()>q2.size())
				for(int i=1;i<=get(k);i++) stk[++top]=q1.front(),q1.pop();
			else 
				for(int i=1;i<=get(k);i++) stk[++top]=q2.front(),q2.pop();
			for(int i=1;i<=top;i++) printf("%lld ",stk[i]); puts("");
		}else{
			int p=0;
			for(int i=1;i<=n;i++) if(dep[i]>dep[p]) p=i;
			while(p){
				stk[++top]=p;
				p=f[f[p]];
			}
			for(int i=1;i<=get(k);i++) printf("%lld ",stk[i]); puts("");
		}
	}
	inline void solve2(int u,int v){
		puts("2");
		printf("%lld\n",dep[u]-dep[v]+1);
		while(u!=v){
			stk[++top]=u;
			u=f[u];
		}
		stk[++top]=v;
		for(int i=1;i<=top;i++) printf("%lld ",stk[i]); puts("");
		exit(0);
	}
	void dfs(int u,int fa){
		f[u]=fa; dep[u]=dep[fa]+1;
		vis[u]=1;
		for(int i=head[u];i;i=edge[i].next){
			int v=edge[i].v;
			if(v==fa) continue;
			if(vis[v]){
				if(dep[u]<dep[v]) continue;
				if(dep[u]-dep[v]+1<=k) solve2(u,v);
				continue;
			}
			dfs(v,u);
		}
	}

	inline int main(){
		n=read(); m=read(); k=read();
		for(int i=1;i<=m;i++){
			int x=read(),y=read();
			add(x,y); add(y,x);
		}
		dfs(1,0); solve1();
		return 0;
	}
}
signed main(){return CL::main();}
```
 
 ## $\text{Reference}$
 
 $2021$ 国家集训队论文 《信息学竞赛中构造题的常用解题方法》—蒋凌宇

---

## 作者：奇米 (赞：4)

# 题解 - $\mathrm{CF1364D}$

## 题目意思

* [题目传送门](https://www.luogu.com.cn/problem/CF1364D)

## $\mathrm{Sol}$

* 我们首先先考虑第一问，我们可以通过黑白染色来完成判断，复杂度$O(n)$

* 对于第二问判环，我们记录每个点进入环的时间戳$id_i$，如果对于两个点$(u,v):k\leq id_u-id_v$，那么直接输出就可以了。对于$id_i$这个我们只要用$vector$维护一下即可。复杂度$O(n)$

## $\mathrm{Code}$

```cpp
#include <bits/stdc++.h>
#define For(i,a,b) for ( int i=(a);i<=(b);i++ )
#define Dow(i,b,a) for ( int i=(b);i>=(a);i-- )
#define GO(i,x) for ( int i=head[x];i;i=e[i].nex )
#define mem(x,s) memset(x,s,sizeof(x))
#define cpy(x,s) memcpy(x,s,sizeof(x))
#define YES return puts("YES"),0
#define NO return puts("NO"),0
#define GG return puts("-1"),0
#define pb push_back
using namespace std;

inline int read()
{
	int sum=0,ff=1; char ch=getchar();
	while(!isdigit(ch))
	{
		if(ch=='-') ff=-1;
		ch=getchar();
	}
	while(isdigit(ch))
		sum=sum*10+(ch^48),ch=getchar();
	return sum*ff;
}

const int mod=1e9+7;
const int mo=998244353;
const int N=1e6+5;

int n,m,vis[N],id[N],ans,s,S,C[N];
vector<int> G[N],zh,yzc[3];

inline void dfs(int u,int fa)
{
	zh.pb(u);
	id[u]=(int)zh.size();
	For(i,0,(int)G[u].size()-1)
	{
		int v=G[u][i];
		if(v==fa) continue;
		if(!id[v]) dfs(v,u);
		else 
			if(id[u]-id[v]+1<=s&&id[u]-id[v]+1>=0) 
			{
				puts("2");
				printf("%d\n",id[u]-id[v]+1);
				For(j,id[v]-1,id[u]-1) printf("%d ",zh[j]);
				exit(0);
			}
	}
   zh.pop_back();
}

inline void col(int u,int c)
{
	yzc[c].pb(u);
	C[u]=c;
	if(yzc[c].size()==S) 
	{
		puts("1");
		For(i,0,(int)yzc[c].size()-1) printf("%d ",yzc[c][i]);
		exit(0);
	}
	For(i,0,(int)G[u].size()-1)
	{
		int v=G[u][i];
		if(~C[v]) continue;
		col(v,c^1);
	}
}

int main()
{
	n=read();
	m=read();
	s=read();
	For(i,1,m) 
	{
		int x,y;
		x=read(),y=read();
		G[x].pb(y);
		G[y].pb(x);
	}
	S=(s+1)/2;
	memset(C,-1,sizeof(C));
	dfs(1,0);
	col(1,1);
	return 0;
}
	
```


---

## 作者：迟暮天复明 (赞：2)

只把前 $k$ 个点拿出来，如果是一个森林，那么就把每棵树的最大独立集求出来合一块输出前 $k/2$ 个点，否则一定存在环，于是 DFS 判环即可。

---

## 作者：huayucaiji (赞：1)

这个题是一道很好的“图论+树”的题。

**推荐一道同一个人出的类似的题：[Ehab's Last Theorem](https://codeforces.com/contest/1325/problem/F)**

题目有云：

>**I have a proof that for any input you can always solve at least one of these problems, but it's left as an exercise for the reader.**

我们就来先证明一下。

我们要思考一个问题，什么时候我们能找到一个大小为 $\lceil \frac{k}{2}\rceil$ 的独立集？只有当我们能在图中找到一个大小为 $k$ 的树或一个大小为 $k$ 的简单环时才可以，然而此时我们可以回答第一个问题，我们也就证明了一定有解。

简单环就是任意环上不相邻的点没有连线，即 $(v_i,v_{i+1})\notin E$。

我们提供两种解法：

### 法一

首先我们来解决 $n=k$ 的情况。这个时候如果图是一棵树，那么我们一定能找到独立集这个问题的解，否则就可回答第一个问题。

如果 $n\neq k$，我们就找到一个大小为 $k$ 的联通子图，用 $n=k$ 的方法去做，问题就迎刃而解了。

那么我们来讲一下如何找到一个环（不限大小）。

我们先来看一个图：

![F](http://image.qingtengbc.com/2020/03/18/4d02aaca97fdd.png)

首先，我们随便以一个点作为起点进行 DFS。我们以1位起点。那么，我把DFS中经过过的边（也就是DFS树），边权为 $1$，其他为 $0$。那么原图就变成了这个样子：

![F2](http://image.qingtengbc.com/2020/03/19/56979c11e7fc4.png)

我们发现，由 $1$ 边构成的图是一棵树，虽然这个性质对我们的解题毫无用处，但这个DFS树真的是没什么用，了解就好，他对我们的思路启发是有一点作用的。我们继续讲题，现在，如果在DFS时，我们从 $u$ 出发，找到了一个点 $v$，如果之前 $v$ 已经被搜到过了，那么我们就找到了一个环。这个环的大小就至少为 $dfn_u-dfn_v+1$。（$dfn$ 表第 $i$ 个点被遍历到的时间戳）。

```cpp
#include<bits/stdc++.h>
using namespace std;

int read() {
    char ch=getchar();
    int f=1,x=0;
    while(ch<'0'||ch>'9') {
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9') {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return f*x;
}

const int maxn=1e5+10;

struct edge {
	int v,next;
}e[maxn<<2];

int n,h[maxn],h2[maxn],cnt,m,k,cnt2;
bool ex[maxn],flag,is[maxn];
stack<int> s;
vector<int> ans[2];

void addedge(int u,int v) {
	e[++cnt].v=v;
	e[cnt].next=h[u];
	h[u]=cnt;
}
void insert(int u,int v) {
	addedge(u,v);
	addedge(v,u);
}

void dfs(int u,int fa) {//找环
	s.push(u);
	ex[u]=1;
	for(int i=h[u];i;i=e[i].next) {
		int v=e[i].v;
		
		if(fa!=v&&is[v]) {//is[v]判断答我们遍历的点是否在我们建的新图里
			if(ex[v]) {//找到就输出
				int sz=s.size();
				
				for(int j=0;j<sz;j++) {
					ans[0].push_back(s.top());
					if(s.top()==v) {
						break;
					}
					s.pop();
				}
				
				sz=ans[0].size();
				printf("2\n%d\n",sz);
				for(int j=0;j<sz;j++) {
					printf("%d ",ans[0][j]);
				}
				exit(0);
			}
			
			dfs(v,u);
		}
	}
	s.pop();
	ex[u]=0;
}

void color(int u,int fa,int type) {//找独立集
	ans[type].push_back(u);
	for(int i=h[u];i;i=e[i].next) {
		int v=e[i].v;
		
		if(fa!=v&&is[v]) {
			color(v,u,1-type);
		}
	}
}

void create(int u,int fa,int num) {//建新图
	is[u]=1;
	for(int i=h[u];i;i=e[i].next) {
		int v=e[i].v;
		
		if(!is[v]) {
			if(flag) {
				return ;
			}
			if(num==1) {
				flag=1; 
			}
			create(v,u,num-1);
		}
	}
}

int main() {
	n=read();m=read();k=read();
	
	for(int i=1;i<=m;i++) {
		int a=read(),b=read();
		insert(a,b);
	}
	
	m=0;
	create(1,0,k-1);
	
	dfs(1,0);
	
	printf("1\n");
	color(1,0,0);
	
	if(ans[0].size()<ans[1].size()) {
		swap(ans[0],ans[1]);
	}
	int sz=ans[0].size();
	sz=min(sz,(k+1)/2);//判断一下我们找到的最大独立集的大小是否一定小于 ceil(k/2)
	for(int i=0;i<sz;i++) {
		printf("%d ",ans[0][i]);
	}
	
	return 0;
}
```

### 法二

我们先来找一个简单环，如果这个环的大小大于 $k$，染色法找独立集，否则直接输出。

---

## 作者：Flandre_495 (赞：1)

题面是 $Rainy\_chen$ 大神翻译的，很详细对吧。

____

比赛完发现自己做法和官方题解不太一样，就写下来了。

由于图保证连通，先随便生成一棵树出来，直接DFS就好了，记录下每个点的父亲。

剩下的边是**非树边**，你发现非树边可以与树边连成环。

其实非树边组成的环很复杂，但这里我们只需要考虑**只经过一条非树边**的环。

我们计算每个非树边，它与树边构成的那条**环的长度**，把信息记在那条非树边上。

然后找出最小的环（注意这个环是只经过一条非树边的环，不一定是全局最小环）。

三种情况：

**1.**压根没环，就是棵树，奇数和偶数层肯定有一层满足的，输出这个独立集就好了。

**2.**最小环长度小于等于 $k$，那太好了，直接按 $2$ 的方案把环输出出来。

**3.**最小环长度大于 $k$，那咋办嘛？你会发现如果你在这条环上每隔两个点选一个点，一定是个独立集，而且正好能选出 $\left\lceil\dfrac k2\right\rceil$ 个点。

但你有个疑问：选出的这些点会不会有连边呢？

回答：如果有连边，那么你**选出的这个环**一定不是最小环，只要它有弦，就一定存在更小的环，放一张图会更好理解：

![](https://files-cdn.cnblogs.com/files/clever-sheep/T1.bmp)

全局最小环显然是6-10-8-9，但是我们只考虑一条非树边的环，发现这并不会影响1 6 8成为独立集。

如果6 8有连边，那么最小环肯定会缩小，那也就不需要考虑这条更大的环了。

____

代码不算短，但是感觉不需要任何科技，比官方题解其实好理解些？大概。

我的代码太丑了，就不放了。。。

---

## 作者：syksykCCC (赞：1)

想一想，「简单环」和「独立集」有什么关系？

**如果一个大小为 $s$ 的环是不可分割的，那么，把环上的元素隔一位取一个，就可以分为两个大小为 $\lfloor\frac{s}{2}\rfloor$ 的独立集。**


下图展示的是 $s = 5$ 的一种分法，分割出了 $\{1, 3\}$ 和 $\{ 2, 4\}$ 两个独立集：

![image.png](https://i.loli.net/2020/06/15/3QiXPzAgljcpuF7.png)

关键在于找出一个「不可分割的环」，比方说它的大小为 $a$，要是 $a \le k$，那么我们就完成任务 2 了，直接输出它就好，否则（$a > k$），必然有 $\lfloor\frac{a}{2}\rfloor \ge \lceil\frac{k}{2}\rceil$，这意味着，在这个分割出来的独立集中**再分割一个大小为 $\lceil\frac{k}{2}\rceil$ 的独立集**就可以完成任务 1 了。

所以，如果求出一个不可分割的环呢？

我们可以先在这个图中随便找出一个环，把点集按照顺序存在一个 `deque`（双端队列）里面。

然后，遍历每一条边 $\left<u, v\right>$，如果 $\left<u, v\right>$ **切割**了现有的环，那么，就再割出来的两个小环中任选一个保留，$m$ 条边都割完为止。

具体的实现方法是，如果 $u, v$ 都在当前环中，且 $\left<u, v\right>$ 不是一条环上的边（可以比较 $u$ 和 $v$ 在环中的位置差是不是 $1$ 来确定），则 $\left<u, v\right>$ 必然切割当前环，如图：

![image.png](https://i.loli.net/2020/06/15/zCLamQtUVfoDiIY.png)

原来 `deque` 当中的元素依次是 $\{1, 2, 3, 4, 5\}$，现在来了条边 $\left<2, 4 \right>$ 切割，那么，必然有一个新的小环端点为 $u = 2$ 和 $v = 4$，那么把两端其余的元素弹出，就可以得到新的小环 $\{ 2, 3, 4 \}$。

当然，如果这张图一个环都没有，则这张图是树，树必然是二分图，直接二分图染色后在较大的颜色集中提取 $\lceil\frac{k}{2}\rceil$ 个来完成任务 1 就好了。

初始 DFS 找环是 $\mathcal O(n)$ 的，遍历边集是 $\mathcal O(n)$ 的，环中最多有 $n$ 个元素，所以弹出次数的总和也是 $\mathcal O(n)$ 的，所以总时间复杂度 $\mathcal O(n)$（这里不区分 $n$ 和 $m$）。

代码仅供参考：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
vector<int> G[N];
deque<int> circ;
vector<int> s, col[2];
int n, m, k, pos[N], u[N], v[N];
bool in_circ[N];
void DFS(int u)
{
	pos[u] = s.size();
	s.push_back(u);
	col[pos[u] & 1].push_back(u);
	for(int v : G[u])
	{
		if(pos[v] == -1) DFS(v);
		else if(circ.empty() && pos[u] > pos[v] + 1)
		{
			for(int i = pos[v]; i <= pos[u]; i++)
			{
				circ.push_back(s[i]);
				in_circ[s[i]] = true;
			}
		}
	}
	s.pop_back();
}
int main()
{
	memset(pos, -1, sizeof pos);
	cin >> n >> m >> k;
	for(int i = 1; i <= m; i++)
	{
		cin >> u[i] >> v[i];
		G[u[i]].push_back(v[i]);
		G[v[i]].push_back(u[i]);
	}
	DFS(1);
	if(circ.empty())
	{
		cout << 1 << endl; 
		if(col[0].size() < col[1].size()) swap(col[0], col[1]);
		for(int i = 0; i < (k + 1) / 2; i++) cout << col[0][i] << ' ';
		return 0;
	}
	for(int i = 1; i <= m; i++)
	{
		if(in_circ[u[i]] && in_circ[v[i]] && abs(pos[u[i]] - pos[v[i]]) != 1)
		{
			while(circ.front() != u[i] && circ.front() != v[i]) 
				in_circ[circ.front()] = false, circ.pop_front();
			while(circ.back() != u[i] && circ.back() != v[i]) 
				in_circ[circ.back()] = false, circ.pop_back();
		}
	}
	if(circ.size() <= k)
	{
		cout << 2 << endl;
		cout << circ.size() << endl;
		for(int i = 0; i < circ.size(); i++) cout << circ[i] << ' ';
	}
	else
	{
		cout << 1 << endl;
		for(int i = 0; i < (k + 1) / 2; i++) cout << circ[i * 2] << ' ';
	}
	return 0;
}
```

---

## 作者：Karry5307 (赞：1)

### 题意

给定一个 $n$ 个点 $m$ 条边的无向连通图和一个正整数 $k$，求出一个大小不超过 $k$ 的环或者是恰好为 $\left\lceil\frac{k}{2}\right\rceil$ 的独立集。

$\texttt{Data Range:}3\leq k\leq n\leq 10^5,n-1\leq m\leq 2\times 10^5$

### 题解

考虑一个环，环上面没有其他连接不相邻两个点的边，如果这个环的大小不超过 $k$ 直接回答这个环即可。

否则，我们可以以隔一个点选一个点的方式找到一个至少为 $\left\lceil\frac{k}{2}\right\rceil$ 的独立集，回答它的一个子集即可。

于是就想到要去求这么一个环，赛场上因为求环求错了导致 $\texttt{FST}$，身败名裂。

如果没有环直接二分图染色回答独立集即可。

否则，首先按照 $\texttt{Kruskal}$ 的过程找到一个环，然后逐一检查所有的边。

如果这条边是原图上钦定的生成基环树上的边，不管。

否则，如果这条边连接了环上两个不相邻的点，那么这个环被这条边分成了两个子环，随机取一个即可。

先对环上的点按顺序重新标号，这样子我们就可以用一个区间来表示一段环了，更新的话可以直接维护这个区间来更新。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
typedef long long int li;
const ll MAXN=2e5+51;
struct Edge{
	ll to,prev;
};
Edge ed[MAXN<<1];
ll n,m,kk,tot,cur,nxt,fx,fy,totx,l,r,pu,pv,pp;
ll u[MAXN],v[MAXN],ffa[MAXN],fa[MAXN],indSet[MAXN],rp[MAXN];
ll tag[MAXN],last[MAXN],depth[MAXN],cx[2];
vector<ll>res;
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
inline ll find(ll x)
{
	return x==ffa[x]?x:ffa[x]=find(ffa[x]);
}
inline void addEdge(ll from,ll to)
{
	ed[++tot].prev=last[from];
	ed[tot].to=to;
	last[from]=tot;
}
inline void dfs(ll node,ll f)
{
	fa[node]=f,cx[depth[node]=depth[f]^1]++;
	for(register int i=last[node];i;i=ed[i].prev)
	{
		ed[i].to!=f?dfs(ed[i].to,node):(void)(1);
	}
}
int main()
{
	n=read(),m=read(),kk=read();
	for(register int i=1;i<=n;i++)
	{
		ffa[i]=i;
	}
	for(register int i=1;i<=m;i++)
	{
		u[i]=read(),v[i]=read();
		if((fx=find(u[i]))!=(fy=find(v[i])))
		{
			addEdge(u[i],v[i]),addEdge(v[i],u[i]),ffa[fy]=fx,tag[i]=1;
		}
		else
		{
			if(totx)
			{
				continue;
			}
			tag[i]=1;
			dfs(u[i],0),indSet[++totx]=cur=v[i];
			for(;cur!=u[i];indSet[++totx]=cur=fa[cur]);
		}
	}
	if(!totx)
	{
		dfs(1,0),pp=cx[0]>cx[1]?0:1;
		for(register int i=1;i<=n;i++)
		{
			depth[i]==pp?res.push_back(i):(void)(1);
		}
		puts("1");
		for(register int i=0;i<(kk+1)>>1;i++)
		{
			printf("%d ",res[i]);
		}
		return 0;
	}
	for(register int i=1;i<=totx;i++)
	{
		rp[indSet[i]]=i;
	}
	l=1,r=totx;
	for(register int i=1;i<=m;i++)
	{
		if(!tag[i])
		{
			pu=rp[u[i]],pv=rp[v[i]],pu>pv?swap(pu,pv):(void)(1);
			if(l<=pu&&pu<=r&&l<=pv&&pv<=r)
			{
				l=pu,r=pv;
			}
		}
	}
	for(register int i=l;i<=r;i++)
	{
		res.push_back(indSet[i]);
	}
	if(r-l+1<=kk)
	{
		printf("2\n%d\n",r-l+1);
		for(register int i=0;i<r-l+1;i++)
		{
			printf("%d ",res[i]);
		}
	}
	else
	{
		puts("1");
		for(register int i=0,j=0;j<(kk+1)>>1;i+=2,j++)
		{
			printf("%d ",res[i]);
		}
	}
}

```

---

## 作者：FutaRimeWoawaSete (赞：0)

考虑建立无向图的 dfs 树并按照第一次走过的顺序为树边定向，显然这么做得到的非树边都是返祖边。

考虑枚举所有返祖边，如果对应的路径长度不超过 $k$ 就可以直接输出。

否则我们分两类讨论：

- $m = n - 1$ 即原图是棵树，那么我们直接按照深度的奇偶性分组，显然这样较大的一组至少有 $\lceil \frac{n}{2} \rceil$ 个点，且 $\lceil \frac{k}{2} \rceil \leq \lceil \frac{n}{2} \rceil$，随便从集合里面选几个点就行了；

- $m < n - 1$，那么根据最开始枚举返祖边得到的性质，我们知道 dfs 树的最大深度至少为 $k$，并且任意具有祖先-子孙关系且深度差在 $k$ 以内的点对没有返祖边相连，利用以上性质我们将深度最大的节点 $x$ 每次向上爬两层得到的所有节点输出前 $\lceil \frac{k}{2} \rceil$ 个即可。

```cpp
/*
貌似根据之前 PMOI 的那道题的套路
先建 dfs 树，如果叶子节点 >= lceil k/2 rceil 个叶子就直接输出
感觉不是很对，树的话就叶子节点如果不超过 k/2 咋办呢…… 
After reading the solution
果然还是应该先找简单环吗…… 
*/
#include "bits/stdc++.h"
using namespace std;
const int Len = 2e5 + 5;
int n,m,k,l,head[Len],cnt,vis[Len],dep[Len],fa[Len],mx;
vector<int> v[2];
struct node
{
	int next,to;
}edge[Len << 1];
void add(int from,int to)
{
	edge[++ cnt].to = to;
	edge[cnt].next = head[from];
	head[from] = cnt;
}
void dfs(int x,int f)
{
	vis[x] = 1;
	dep[x] = dep[f] + 1;
	v[dep[x] % 2].push_back(x);
	if(dep[x] > dep[mx]) mx = x;
	fa[x] = f;
	for(int e = head[x] ; e ; e = edge[e].next)
	{
		int to = edge[e].to;
		if(to == f) continue;
		if(vis[to]) 
		{
			if(dep[x] > dep[to] && dep[x] - dep[to] < k) 
			{
				puts("2");
				printf("%d\n",dep[x] - dep[to] + 1);
				int now = x;
				while(now != to){printf("%d ",now);now = fa[now];}
				printf("%d ",now);
				exit(0);
			}
			continue;
		}
		dfs(to , x);
	}
}
int main()
{
	scanf("%d %d %d",&n,&m,&k);
	if(k % 2 == 0) l = k / 2;
	else l = k / 2 + 1;
	for(int i = 1 ; i <= m ; i ++)
	{
		int x,y;scanf("%d %d",&x,&y);
		add(x , y);
		add(y , x);
	}
	dfs(1 , 0);
	if(m == n - 1)
	{
		if(v[0].size() < v[1].size()) swap(v[0] , v[1]);
		puts("1");
		for(int i = 0 ; i < l ; i ++) printf("%d ",v[0][i]);
		return 0;
	}
	puts("1");
	while(l --)
	{
		printf("%d ",mx);
		mx = fa[mx];
		mx = fa[mx];
	}
	return 0;
}
```

---

## 作者：caidzh (赞：0)

~~为什么我的代码这么长啊/kk~~

这题思维难度并不大

首先考虑为什么题中给出的两个问题其中一个必定有解

从原图中抽出一棵树，此时如果我们随便加进去一条非树边，图上会出现一个环

考虑加入每一条非树边得到的环

显然这些环中肯定存在至少一个环是**极小**的

考虑一个极小环的大小如果大于$k$，从这个环中依次取出不相邻的点就是问题 $1$ 的解（因为是极小的，所以诱导子图中不可能存在不在环上的边），否则这个环就是问题 $2$ 的解

需要判断树的情况，这个直接把所有深度为奇数的或者偶数的点取出来就可以了

感觉非常丢人的代码
```cpp
const int maxn=100010,mod=998244353;
int n,m,k,u[maxn],v[maxn],vis[maxn],fa[maxn],flg;
vector<int>g[maxn],G[maxn];int ansu,ansv;
int Find(int x){
	return fa[x]==x?x:fa[x]=Find(fa[x]);
}
int res[maxn][20],dis[maxn];
void dfs(int x,int fa){
	dis[x]=dis[fa]+1;
	for(int i=1;i<=19;i++)res[x][i]=res[res[x][i-1]][i-1];
	for(int i=0;i<g[x].size();i++){
		int v=g[x][i];if(v==fa)continue;
		res[v][0]=x;dfs(v,x);
	}
}
int LCA(int x,int y){
	if(dis[x]<dis[y])swap(x,y);
	for(int i=19;i>=0;i--)if(dis[res[x][i]]>=dis[y])x=res[x][i];if(x==y)return x;
	for(int i=19;i>=0;i--)if(res[x][i]!=res[y][i])x=res[x][i],y=res[y][i];return res[x][0];
}
int dist(int x,int y){
	return dis[x]+dis[y]-2*dis[LCA(x,y)];
}
int sta[maxn],tp,f;
void solve(int x,int fa){
	if(f)return;sta[++tp]=x;
	if(x==ansv){
		int tot=1;f=1;cout<<1+flg<<endl;
		if(flg){
			cout<<tp<<endl;for(int i=1;i<=tp;i++)cout<<sta[i]<<" ";
		}
		else{
			for(int i=1;i<=tp&&tot<=(k+1)/2;i+=2)cout<<sta[i]<<" ",tot++;
		}return;
	}
	for(int i=0;i<g[x].size();i++){
		int v=g[x][i];if(v==fa)continue;solve(v,x);
	}tp--;
}
int main(){
	n=read();m=read();k=read();
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<=m;i++){
		int x=read(),y=read(),u=Find(x),v=Find(y);
		if(u!=v)g[x].pb(y),g[y].pb(x);
		else G[x].pb(y),G[y].pb(x);fa[u]=v;
	}
	if(m==n-1){
		dfs(1,0);int tot1=0,tot2=0,tot=1;
		for(int i=1;i<=n;i++)if(dis[i]&1)tot1++;else tot2++;cout<<1<<endl;
		if(tot1>=k/2){
			for(int i=1;i<=n&&tot<=(1+k)/2;i++)
				if(dis[i]&1)cout<<i<<" ",tot++;
		}
		else{
			for(int i=1;i<=n&&tot<=(1+k)/2;i++)
				if(dis[i]%2==0)cout<<i<<" ",tot++;
		}
	}else{
		dfs(1,0);
		for(int i=1;i<=n;i++)
			for(int j=0;j<G[i].size();j++){
				int u=i,v=G[i][j];if(dist(u,v)+1<=k)flg=1;
			}
		if(flg){
			for(int i=1;i<=n;i++)
				for(int j=0;j<G[i].size();j++){
					int u=i,v=G[i][j];if(dist(u,v)+1<=k)ansu=u,ansv=v;
			}
		}
		else{
			for(int i=1;i<=n;i++)
				for(int j=0;j<G[i].size();j++){
					int u=i,v=G[i][j];if(dist(u,v)+1>k)ansu=u,ansv=v;
			}
		}solve(ansu,0);
	}return 0;
}
```


---

