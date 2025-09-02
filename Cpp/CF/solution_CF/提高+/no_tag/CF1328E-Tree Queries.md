# Tree Queries

## 题目描述

You are given a rooted tree consisting of $ n $ vertices numbered from $ 1 $ to $ n $ . The root of the tree is a vertex number $ 1 $ .

A tree is a connected undirected graph with $ n-1 $ edges.

You are given $ m $ queries. The $ i $ -th query consists of the set of $ k_i $ distinct vertices $ v_i[1], v_i[2], \dots, v_i[k_i] $ . Your task is to say if there is a path from the root to some vertex $ u $ such that each of the given $ k $ vertices is either belongs to this path or has the distance $ 1 $ to some vertex of this path.

## 说明/提示

The picture corresponding to the example:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1328E/c550ce8ec76e16e620040a46eef6ab14f38a250f.png)

Consider the queries.

The first query is $ [3, 8, 9, 10] $ . The answer is "YES" as you can choose the path from the root $ 1 $ to the vertex $ u=10 $ . Then vertices $ [3, 9, 10] $ belong to the path from $ 1 $ to $ 10 $ and the vertex $ 8 $ has distance $ 1 $ to the vertex $ 7 $ which also belongs to this path.

The second query is $ [2, 4, 6] $ . The answer is "YES" as you can choose the path to the vertex $ u=2 $ . Then the vertex $ 4 $ has distance $ 1 $ to the vertex $ 1 $ which belongs to this path and the vertex $ 6 $ has distance $ 1 $ to the vertex $ 2 $ which belongs to this path.

The third query is $ [2, 1, 5] $ . The answer is "YES" as you can choose the path to the vertex $ u=5 $ and all vertices of the query belong to this path.

The fourth query is $ [4, 8, 2] $ . The answer is "YES" as you can choose the path to the vertex $ u=9 $ so vertices $ 2 $ and $ 4 $ both have distance $ 1 $ to the vertex $ 1 $ which belongs to this path and the vertex $ 8 $ has distance $ 1 $ to the vertex $ 7 $ which belongs to this path.

The fifth and the sixth queries both have answer "NO" because you cannot choose suitable vertex $ u $ .

## 样例 #1

### 输入

```
10 6
1 2
1 3
1 4
2 5
2 6
3 7
7 8
7 9
9 10
4 3 8 9 10
3 2 4 6
3 2 1 5
3 4 8 2
2 6 10
3 5 4 7```

### 输出

```
YES
YES
YES
YES
NO
NO```

# 题解

## 作者：WYXkk (赞：18)

题面上说的是“给定的点在 $1$ 到 $u$ 的路径上或者与路径上的某个点相邻”，

那么很显然我们可以转化为“$1$ 到 $u$ 的路径经过给定点旁边的某个点”。

令这棵树以 $1$ 为根，那么，这条路径要么经过给定点，要么经过给定点的父亲，要么经过给定点的至少一个儿子。

这时我们发现，经过以上三种点都必须经过给定点的父亲，于是我们就把题面转化为了：

给定若干个点，求是否有一条从 $1$ 开始的路径经过这些点。

按照深度排序后依次判断后一个点是否在前一个点的子树内即可。

只需要 dfs 一遍，求出 子树大小 $siz_i$，父亲 $fa_i$，深度 $dep_i$，dfs 序 $dfn_i$ 即可。

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

const int N=200005;
int dfn[N],siz[N],fa[N],dep[N];
int head[N],to[N<<1],nxt[N<<1],tot=0;void add(int u,int v){to[++tot]=v;nxt[tot]=head[u];head[u]=tot;}
int tme=0;
void dfs(int u,int f)
{
	dep[u]=dep[f]+1;fa[u]=f;siz[u]=1;dfn[u]=++tme;
	for(ri i=head[u];i;i=nxt[i]) if(to[i]!=f) {dfs(to[i],u);siz[u]+=siz[to[i]];}
}
bool in(int x,int y)//is y in the subtree of x
{return dfn[x]<=dfn[y]&&dfn[y]<dfn[x]+siz[x];}
bool cmp(int x,int y){return dep[x]<dep[y];}
int tmp[N];
int main()
{
	int n=rd();int m=rd();
	F(i,1,n-1){int u=rd();int v=rd();add(u,v);add(v,u);}
	dfs(1,1);
	while(m--)
	{
		int k=rd();
		F(i,1,k) tmp[i]=fa[rd()];
		sort(tmp+1,tmp+k+1,cmp);
		bool flg=true;
		F(i,1,k-1) if(!in(tmp[i],tmp[i+1])) flg=false;
		puts(flg?"YES":"NO");
	}
	return 0;
}
```



---

## 作者：liangbowen (赞：10)

[problem](https://www.luogu.com.cn/problem/CF1328E) & [blog](https://www.cnblogs.com/liangbowen/p/17540450.html)。

提供一个代码上不一样（？）的做法。

---

找到询问集合中，深度最大的点 $mx$。如果都最后一个点了，还拐到别的分支，显然毫无意义，所以 $(1,mx)$ 的路径是最优的。

那就好做了。$\operatorname{lca}(mx,q_i)$ 显然在 $(1,mx)$ 里，所以只需检查 $\forall\operatorname{dist}(q_i, \operatorname(mx, q_i))\le 1$ 即可。

[代码](https://codeforces.com/contest/1328/submission/213046072)，时间复杂度 $O(k\log n)$。


---

## 作者：ZBHRuaRua (赞：10)

看题时一眼虚树，直接不想想了，干脆复制粘贴虚树板子，1min写个树形DP把它A了就完事。（虽然正常人也能一眼LCA，但是开局连题意都没看的我看到那个$\sum k<=2e5$就忍不住虚树了）

先直接建虚树，然后对于合法情况，虚树上的每个点的子树中最深的点与当前点深度差大于$1$的子树一定不超过一个。

然后直接按照这个DFS一遍即可，如果超过一个了直接flag设为0.

代码有些无关变量之类的，可能是复制粘贴的板子里用的，但是实际函数部分是没有多余内容的：

```cpp
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<iostream>
#include<iomanip>
#include<algorithm>
#include<vector>
#define ll long long
using namespace std;
const int maxn=250050;
inline int read()
{
	int res=0,f=1;char c=getchar();
	while(c<'0'||c>'9') 
	{
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		res=res*10+(c-'0');
		c=getchar();
	}
	return res*f;
}
int n,m;
int cnt;
int ver[maxn<<1];
int nxt[maxn<<1];
int val[maxn<<1];
int head[maxn];
int tot,tmp;
int dfn[maxn];
int F[maxn][21];
int deep[maxn];
int a[maxn];
int st[maxn];
bool flag;
vector<int> e[maxn];
bool bj[200050];
inline void add(int x,int y)
{
	cnt++;
	ver[cnt]=y;
	nxt[cnt]=head[x];
	head[x]=cnt;
}
inline void dfs(int x,int fa)
{	
	dfn[x]=++tot;
	F[x][0]=fa;
	deep[x]=deep[fa]+1;
	for(int i=head[x];i;i=nxt[i])
	{
		if(ver[i]==fa) continue;
		dfs(ver[i],x);
	}
}
inline int lca(int x,int y)
{
	if(deep[x]<deep[y]) swap(x,y);
	for(int i=20;i>=0;i--)
	{
		if(deep[F[x][i]]>=deep[y])
		{
			x=F[x][i];
		}
	}
	if(x==y) return x;
	for(int i=20;i>=0;i--)
	{
		if(F[x][i]!=F[y][i])
		{
			x=F[x][i];y=F[y][i];
		}
	}
	return F[x][0];
}
inline void insert(int x)
{
	if(!tmp)
	{
		st[++tmp]=x;
		return;
	}
	int f=lca(x,st[tmp]);
	if(f==st[tmp])
	{
		st[++tmp]=x;
		return;
	}
	while(tmp>1&&dfn[st[tmp-1]]>=dfn[f])
	{
		e[st[tmp-1]].push_back(st[tmp]);
		--tmp;
	}
	if(st[tmp]!=f)
	{
		e[f].push_back(st[tmp]);
		tmp--;
		st[++tmp]=f;
	}
	st[++tmp]=x;
}
inline long long dp(int x)
{
	int ss=0;int deps=deep[x];
	for(int i=0;i<e[x].size();i++)
	{
		if(bj[e[x][i]]==0) ss++;
		else
		{
			int r=dp(e[x][i]);
			if(r-deep[x]>1) ss++;
			deps=max(deps,r);
		}
	}
	if(ss>1) flag=0;
	for(int i=0;i<e[x].size();i++)
	{
		if(bj[e[x][i]]==0)
		{
			int r=dp(e[x][i]);
			deps=max(deps,r);
		}
	}
	e[x].clear();
	return deps;
}
inline bool cmp(int x,int y)
{
	return dfn[x]<dfn[y];
}
int main()
{
	n=read();m=read();
	for(int i=1;i<n;i++)
	{
		int x,y;
		x=read();y=read();
		add(x,y);add(y,x);
	}
	dfs(1,0);
	for(int i=1;i<=20;i++)
	{
		for(int j=1;j<=n;j++)
		{
			F[j][i]=F[F[j][i-1]][i-1];
		}
	}
	while(m--)
	{
		int k;k=read();
		for(int i=1;i<=k;i++) a[i]=read(),bj[a[i]]=1;
		sort(a+1,a+k+1,cmp);
		st[tmp=1]=1;
		for(int i=1;i<=k;i++) if(a[i]!=1) insert(a[i]);
		while(tmp)
		{
			e[st[tmp-1]].push_back(st[tmp]);
			tmp--;
		}
		flag=1;
		dp(1);
		if(!flag) cout<<"NO"<<endl; 
		else cout<<"YES"<<endl;
		for(int i=1;i<=k;i++) bj[a[i]]=0;
	}
	return 0;
}
```


---

## 作者：PanH (赞：7)

## 题解 CF1328E Tree Queries

可以把 “是否有一条以根节点为一端的链使得询问的每个节点到此链的距离均 $\leq 1 $” 中的每个节点换成它的父亲，那么题意就转化为 **“是否有一条以根节点为一端的链使得询问的每个节点在链上”** 。

对于一些在同一条一端为根的链上的点，显然**深度小的点是深度大的点的祖先**。

于是只要对每次询问的几个点取个父亲，在根据深度排个序，相邻的两个验证一下是否有祖先与子孙的关系就好了。

我用了倍增来做判断，时间复杂度 $O(n\log n+m k\log k)$。

code:

```cpp
#include<bits/stdc++.h>
using namespace std;
template<class T>inline void read(T &x)
{
	x=0;int f=0;char ch=getchar();
	while(!isdigit(ch))	f=ch=='-',ch=getchar();
	while(isdigit(ch))	x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	x=f?-x:x;
}
const int N=2e5+5;
struct edge{
	int next,to;
}e[N<<1];
int head[N],cnt,v[N],f[N][20],dep[N],n,m;
inline void add(int u,int v)
{
	e[++cnt]={head[u],v};
	head[u]=cnt;
}
void dfs(int x,int fa)
{
	f[x][0]=fa,dep[x]=dep[fa]+1;
	for(int i=1;i<=18;i++)	f[x][i]=f[f[x][i-1]][i-1];
	for(int i=head[x];i;i=e[i].next)
		if(!dep[e[i].to])	dfs(e[i].to,x);
}
bool check(int x,int y)
{
	if(x==y)	return 1;
	for(int i=18;i>=0;i--)
		if(dep[f[x][i]]>=dep[y])	x=f[x][i];
	return x==y;
}
bool cmp(int x,int y)	{return dep[x]>dep[y];}
int main()
{
	read(n),read(m);
	for(int i=1;i<n;i++)
	{
		int u,v;
		read(u),read(v);
		add(u,v),add(v,u);
	}
	dfs(1,0);
	while(m--)
	{
		int k;read(k);
		for(int i=1;i<=k;i++)	read(v[i]),v[i]=v[i]==1?1:f[v[i]][0];
		sort(v+1,v+k+1,cmp);
		bool ok=1;
		for(int i=1;i<k;i++)
			if(!check(v[i],v[i+1]))	{ok=0;break;}
		if(ok)	puts("YES");
		else	puts("NO");
	}
	return 0;
}
```


---

## 作者：orpg (赞：5)

## [Tree Queries](https://www.luogu.com.cn/problem/CF1328E)
### 题目梗概
给你一个以 $1$ 为根的有根树。每次询问 $k$ 个节点，$v_1,v_2,\cdots v_k$。求出是否有一条以根节点为一端的链使得每一个 $v$ 到这条链的距离都 $\le1$。
### 题目大意
设数组 $v$ 中深度最大的点为 $x$，所以 $x$ 一定满足条件。考虑这个点与其他点 $y$ 的关系，不难发现，$\operatorname{lca}(x,y)$ 肯定要在链上，则符合条件的点 $y$ 到 $\operatorname{lca}(x,y)$ 的距离必须 $\le1$。
### 时间复杂度
这里的 $\operatorname{lca}$ 是用倍增维护的，所以时间复杂度就是 $O(k\log n)$。
### 上代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+5;
int n,m;
int tot;
int fl;
int head[maxn<<1];
int dep[maxn];
int v[maxn];
int f[maxn][35];
struct node{
    int to,nxt;
}ed[maxn<<1];
void add(int u,int v){
    ed[++tot].to=v;
    ed[tot].nxt=head[u];
    head[u]=tot;
}
void dfs(int u,int fa){
	dep[u]=dep[fa]+1,f[u][0]=fa;
	for(int i=1;i<=29;i++)
        f[u][i]=f[f[u][i-1]][i-1];
	for(int i=head[u];i;i=ed[i].nxt){
        int to=ed[i].to;
        if(to!=fa) dfs(to,u);
    }
}
int lca(int x,int y){
	for(int i=29;i>=0;i--){
		if(dep[f[x][i]]>=dep[y]){
			x=f[x][i];
		}
	}
	return x==y;
}
bool cmp(int x,int y){return dep[x]>dep[y];}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>m;
    for(int u,v,i=1;i<n;i++){
        cin>>u>>v;
        add(u,v);add(v,u);
    }
    f[1][0]=0;dep[1]=0;
    dfs(1,0);
    for(int k,i=1;i<=m;i++){
        cin>>k;
        for(int i=1;i<=k;i++) cin>>v[i],v[i]=f[v[i]][0];
        sort(v+1,v+k+1,cmp);
        int res=1;
        for(register int i=1; res==1&&i<k; i++) res&=lca(v[i],v[i+1]);
        if(res) puts("YES");
        else puts("NO");
    }
    return 0;
}
```


---

## 作者：WOL_GO (赞：3)

一道树上 [lca](https://www.luogu.com.cn/problem/P4211) 的题目。

首先，对于每一次询问的其中一个节点 $x$（$x\ne1$），如果 $x$ 不需要修改也能与修改后的其它点成为一条链，那么可以证明，把 $x$ 变为 $x$ 的父节点，那么 $x$ 与其它点也能成为一条链。再考虑如果把 $x$ 变为它的子节点能使所有点成为一条链，那么把 $x$ 变为它的父节点也一定能成立。所以，只需要把每一次询问给的点变为它的父节点（$1$ 除外），然后再判断一下修改后的点是否是一条链方可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+5;
void read(int &xx){
    register char ch=getchar();
    register int ans=0;
    char t=0;
    while(!isdigit(ch))t|=ch=='-',ch=getchar/*_unlocked*/();
    while(isdigit(ch))ans=(ans<<3)+(ans<<1)+(ch^48),ch=getchar/*_unlocked*/();
    xx=t?-ans:ans;
    return ;
}
void write(int x){
    if(x<0){
        putchar('-');
        x*=-1;
    }
    char wr[18];
    int cnt=1;
    if(x==0){
        putchar('0');
        putchar('\n');
        return ;
    }
    while(x){
        wr[cnt++]=x%10+'0';
        x/=10;
    }
    for(cnt--;cnt;cnt--){
        putchar(wr[cnt]);
    }
    putchar('\n');
    return;
}
struct edge{
   int to,nxt;
}e[maxn*4];
int head[maxn],cnt;
void add(int u,int v){
    e[++cnt].to=v;
    e[cnt].nxt=head[u];
    head[u]=cnt;
}
int fa[maxn],n,m,deep[maxn],p[maxn][21],a[maxn];
void dfs(int x,int f){
    fa[x]=f;
    deep[x]=deep[f]+1;
    p[x][0]=f;
    for(int i=1;(1<<i)<=deep[x];i++)
        p[x][i]=p[p[x][i-1]][i-1];
    for(int i=head[x];i;i=e[i].nxt){
        if(e[i].to==f)continue;
        dfs(e[i].to,x);
    }
}
int lca(int x,int y){
    if(deep[x]>deep[y])swap(x,y);
    for(int i=20;i>=0;i--)
        if(deep[x]<=deep[y]-(1<<i))y=p[y][i];
    if(x==y)return x;
    for(int i=20;i>=0;i--){
        if(p[x][i]==p[y][i])
            continue;
        else
            x=p[x][i],y=p[y][i];           //A和B一起上移
    }
    return p[x][0];
}
int main(){
    read(n);
    read(m);
    for(int i=1;i<n;i++){
        int x,y;
        read(x);
        read(y);
        add(x,y);
        add(y,x);
    }
    dfs(1,0);
    while(m--){
        int k;
        read(k);
        for(int i=1;i<=k;i++)read(a[i]);
        int maxx=1;
        for(int i=1;i<=k;i++){
            if(deep[a[i]]>deep[a[maxx]])maxx=i;
            if(a[i]!=1){
                a[i]=fa[a[i]];
            }
        }
        bool flag=1;
        for(int i=1;i<=k;i++){
            //cout<<a[i]<<" "<<maxx<<"\n";
            if(lca(a[maxx],a[i])!=a[i]){
                flag=0;
                break;
            }
        }
        if(flag)puts("YES");
        else puts("NO");
    }
    return 0;
}
```


---

## 作者：奇米 (赞：3)

## 题解 - $\mathrm{CF1328E\ Tree \ Queries}$

[$$\huge\color{blue}\boxed{\color{Violet}\mathfrak{There\ is \ my \ blog}}$$](https://www.luogu.com.cn/blog/wyy2020/)

### 题目意思

* [CF1328E](https://www.luogu.com.cn/problem/CF1328E)

### $\mathrm{Sol}$

* 一开始我还以为是什么虚树加个树形$DP$，看来是真的傻。后来仔细想想发现是道傻逼题啊。
* 我们首先不用考虑深度$\leq 1$的点。那么最优的策略显然是从深度最深的点$now$往上覆盖。那么对于有些不是这个点到根节点路径上的点，通过样例$1$的第一问可知只要它与$now$的$lca$与它的距离为$1$，即父亲节点那么也可以满足条件。
* 这样就$O(k_i\ log \ n)$完成了

### $\mathrm{Code}$

```cpp
#include <bits/stdc++.h>
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

const int N=2e5+5;

int n,m,cnt,dep[N],siz[N],f[N][26],a[N],b[N];
vector<int> M[N];

inline void dfs(int u,int fa)
{
	dep[u]=dep[fa]+1;
	f[u][0]=fa;
	for ( int i=1;i<=22;i++ ) 
		f[u][i]=f[f[u][i-1]][i-1];
	for ( int i=0;i<M[u].size();i++ )
	{
		int v=M[u][i];
		if(v==fa) continue;
		dfs(v,u);
	}
}

inline int LCA(int x,int y)
{
	if(dep[x]>dep[y]) swap(x,y);
	for ( int i=21;i>=0;i-- ) if(dep[y]-(1<<i)>=dep[x]) y=f[y][i];
	if(x==y) return x;
	for ( int i=21;i>=0;i-- ) 
		if(f[x][i]!=f[y][i])
			x=f[x][i],y=f[y][i];
	return f[x][0];
}

int main()
{
	n=read();
	m=read();
	for ( int i=1;i<n;i++ )
	{
		int x,y;
		x=read(),y=read();
		M[x].pb(y);
		M[y].pb(x);
	}
	dfs(1,0);
	for (;m--;)
	{
		int s=read(); 
		int now=read();
		b[1]=now;
		for ( int i=2;i<=s;i++ ) 
		{
			int x=read();
			if(dep[now]<dep[x]) now=x;
			b[i]=x;
		}
		int alb=0;
		for ( int i=1;i<=s;i++ )
		{
			int bla=LCA(now,b[i]);
			if(bla!=b[i]&&bla!=f[b[i]][0]) alb=1;
		}
		(!alb)?printf("YES\n"):printf("NO\n");
	}
	return 0;
}
		
		
		
		
```


---

## 作者：Mine_King (赞：2)

对于题目要求的 $v_i$ 和我们找出来的链，有以下关系：

- $v_i$ 的父亲在链中
- $v_i$ 在链中，则 $v_i$ 的父亲一定也在链中，因为这是一条一端为根节点的链
- $v_i$ 的子节点在链中，则 $v_i$ 一定在链中，$v_i$ 的父亲也一定在链中（理由同上）

（这里我们不考虑 $v_i=1$ 的情况，因为这种情况下 $v_i$ 一定在链上）  
所以无论如何 $v_i$ 的父亲一定在这条链上。

我们再考虑这条链有什么性质，很显然的一点就是链上的每一个点都是后面的点的祖先。  
然后就是，链上的每个点深度都不一样。

所以，如果要满足要求，那么 $v_i$ 的父亲一定要在深度比 $v_i$ 小的 $v_j$ 的父亲的子树里。  
这又可以转化成，$v_i$ 一定要在深度比自己小 $v_j$ 的父亲的子树里，因为一个点的父亲如果在一个点的子树中，那这个点一定也在这个子树中。

于是我们就有了实现方法：

1. 对整棵树进行 dfs 遍历
2. 遍历过程中记录每个点的父亲，深度，以该点为根的子树大小及 dfs 序
3. 对于每组询问，先按深度从小到大给 $v_i$ 排序
4. 从前往后遍历，如果 $dfn_y \ge dfn_x \& dfn_y \le dfn_x+size_x-1$，则 $v_i$ 在 $v_{i-1}$ 的父亲的子树中。其中 $x$ 表示 $v_{i-1}$ 的父亲，$y$ 表示 $v_i$，$dfn_x$ 表示 $x$ 的 dfs 序，$size_x$ 表示以 $x$ 为根的子树大小
5. 如果出现至少一个不满足要求的情况，则输出 $NO$，否则输出 $YES$

对于第 $4$ 步的解释：  
因为 $x$ 的子树的 dfs 序一定在 $dfn_x$~$dfn_x+size_x-1$ 之内。  
如果 $dfn_y<dfn_x$ 则 $y$ 比 $x$ 先遍历到，那一定不会在 $x$ 的子树中。   
因为 $x$ 的子树有 $size_x$ 个点，dfs 序在一个子树内是连续的，所以 $x$ 的子树的点的 dfs 序一定不会超过 $dfn_x+size_x-1$。

代码实现：
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,m,index;
int depth[200005],fa[200005],size[200005],dfn[200005];
int k,v[200005];
struct graph
{
	int tot;
	int hd[200005];
	int nxt[400005],to[400005];
	void add(int u,int v)
	{
		tot++;
		nxt[tot]=hd[u];
		hd[u]=tot;
		to[tot]=v;
		return ;
	}
}g;
bool cmp(int x,int y){return depth[x]<depth[y];}
void dfs(int now,int f)
{
	fa[now]=f;
	depth[now]=depth[f]+1;
	dfn[now]=++index;
	size[now]=1;
	for(int i=g.hd[now];i;i=g.nxt[i])
		if(g.to[i]!=f)
		{
			dfs(g.to[i],now);
			size[now]+=size[g.to[i]];
		}
	return ;
}
bool in(int x,int y)
{return dfn[y]>=dfn[x]&&dfn[y]<=dfn[x]+size[x]-1;}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<n;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		g.add(u,v);
		g.add(v,u);
	}
	dfs(1,0);//预处理
	for(int i=1;i<=m;i++)
	{
		scanf("%d",&k);
		for(int j=1;j<=k;j++) scanf("%d",&v[j]);
		sort(v+1,v+k+1,cmp);//注意先排序
		bool flag=true;
		for(int j=1;j<k;j++)
			if(v[j]!=1&&!in(fa[v[j]],v[j+1]))//这里要特判下v[j]=1的情况哦
			{
				flag=false;
				break;
			}
		if(flag) puts("YES");
		else puts("NO");
	}
	return 0;
}
```

---

## 作者：zhlzt (赞：1)

### 题解

显然题目可以转化为经过给定点的父亲，因为给定点必与路径上的某个点有边直接相连，要么是他自己，要么是他父亲，要么是他儿子，但无论如何总是要经过他的父亲的，这里定义 $1$ 的父亲为 $1$。

问题转化为找出一条从 $1$ 出发经过所有给定点父亲的链，那么按照深度排序后的后一个点必定是前一个点的儿子，用 dfn 序判断即可。

时间复杂度 $O\left(n+\displaystyle\sum k_i\right)$。

### 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+10;
pair<int,int>p[maxn];
vector<int>edge[maxn];
int dfn[maxn],dp[maxn];
int dep[maxn],fath[maxn],cnt;
void dfs(int u,int dad){
	dep[u]=dep[dad]+1;
	fath[u]=dad;
	dfn[u]=++cnt; dp[u]=dfn[u];
	for(auto v:edge[u]){
		if(v==dad) continue;
		dfs(v,u); dp[u]=max(dp[u],dp[v]);
	}
	return void();
}
int main(){
	int n,m;scanf("%d%d",&n,&m);
	for(int i=1;i<n;i++){
		int u,v;scanf("%d%d",&u,&v);
		edge[u].push_back(v);
		edge[v].push_back(u);
	}
	cnt=0; dfs(1,1);
	for(int t=0;t<m;t++){
		int k;scanf("%d",&k);
		for(int i=1;i<=k;i++){
			scanf("%d",&p[i].second);
			p[i].second=fath[p[i].second];
			p[i].first=dep[p[i].second];
		}
		sort(p+1,p+1+k);
		int pl=1,pr=n,tag=1;
		for(int i=1;i<=k;i++){
			int u=p[i].second;
			if(pl<=dfn[u] and dfn[u]<=pr){
				pl=dfn[u]; pr=dp[u];
			} 
			else {tag=0; break;}
		}
		puts(tag?"YES":"NO");
	}
	return 0;
} 
```

---

## 作者：Claire0918 (赞：1)

下文中，用 $\operatorname{fa}(u)$ 表示 $u$ 的父亲，$\operatorname{LCA}(x, y)$ 表示 $x$ 和 $y$ 的最近公共祖先。

显而易见，若点 $u$ 离一条链的距离小于等于 $1$，则该链必然经过 $\operatorname{fa}(u)$。

所以，我们可以使 $v_i = \operatorname{fa}(v_i)$。问题便转化成了：是否存在一条以根节点为端点的链经过所有 $v_i$。

可以先将 $\{v_i\}$ 按深度排序。若排序后 $\{v_i\}$ 中任意两个相邻点有祖先关系，即对于任何 $i > 0$，满足 $v_i$ 是 $v_{i + 1}$ 的祖先，则该链存在；否则，该链不存在。

可以用 $\operatorname{LCA}(v_i, v_{i + 1})$ 是否等于 $v_i$ 来判断是否有祖先关系。

Code: 
```cpp
#include<bits/stdc++.h>
#define mem(a, v) memset(a, v, sizeof(a));

using namespace std;

const int maxn = 2e5 + 10, maxlog = 18;

struct{
	int v, nex;
} edge[maxn << 1];

int n, q;
int query[maxn], dep[maxn], father[maxn][maxlog + 10];
int head[maxn], top = 0;

inline void add(int u, int v){
	edge[++top].v = v;
	edge[top].nex = head[u];
	head[u] = top;
}

inline bool cmp(const int & a, const int & b){
	return dep[a] < dep[b];
}

inline void dfs(int u, int fa){
	dep[u] = dep[fa] + 1;
	father[u][0] = fa;
	for (int i = 1; i <= maxlog; i++){
		father[u][i] = father[father[u][i - 1]][i - 1];
	}
	for (int i = head[u]; i; i = edge[i].nex){
		const int v = edge[i].v;
		if (v != fa){
			dfs(v, u);
		}
	}
}

inline int lca(int x, int y){
	if (dep[x] < dep[y]){
		swap(x, y);
	}
	for (int i = maxlog; ~i; i--){
		if (dep[father[x][i]] >= dep[y]){
			x = father[x][i];
		}
	}
	if (x == y){
		return x;
	}
	for (int i = maxlog; ~i; i--){
		if (father[x][i] != father[y][i]){
			x = father[x][i], y = father[y][i];
		}
	}
	return father[x][0];
}

int main(){
	scanf("%d %d", &n, &q);
	for (int i = 1; i < n; i++){
		int u, v;
		scanf("%d %d", &u, &v);
		add(u, v);
		add(v, u);
	}
	dfs(1, 0);
	while (q--){
		int k;
		scanf("%d", &k);
		for (int i = 1; i <= k; i++){
			scanf("%d", &query[i]);
			query[i] = father[query[i]][0];
		}
		sort(query + 1, query + k + 1, cmp);
		bool res = true;
		for (int i = 1; i < k; i++){
			if (lca(query[i], query[i + 1]) != query[i]){
				res = false;
			}
		}
		if (res){
			printf("YES\n");
		}else{
			printf("NO\n");
		}
	}
}
```

---

## 作者：syf2008 (赞：1)

题目意思数给你一棵树，询问以根节点为一端的链，询问每个节点是否到此链的距离均 $\le1$。

我们先把这个条件转换一下，询问的每个节点到此链的距离均 $\le1$，就是它的父亲或它自身在这条链上。

那么显然，如果要经过它，必须得经过它的父亲，所以这题就变成了询问以根节点为一端的链，询问是否每个节点的父亲均在链上。

那这题就非常简单了，首先对这个树进行树剖，然后把 $1$ 号点到询问深度最深的点都标为 $1$，然后直接单点查询，询问完后清空。

证明为什么到询问深度最深的点：  
若不选择深度最深的点，深度最深的点一定遍历不到。  

### 复杂度 $O(\sum_{}k \times \log n)$

## code:
```
#include <bits/stdc++.h>
const int N=2e5+5;
using namespace std;
int n,m,x,y,k;
vector<int>ji;
basic_string<int>e[N];
int ans;
int len,son[N],fa[N],deep[N],siz[N],top[N],now[N],last[N];
void dfs1(int x)
{
	siz[x]=1;
	for(auto y:e[x])
	if(y!=fa[x])
	{
		deep[y]=deep[x]+1;fa[y]=x;
		dfs1(y);
		siz[x]+=siz[y];
		if(siz[son[x]]<siz[y])son[x]=y;
	}
}
void dfs2(int x,int topp)
{
	top[x]=topp;now[x]=++len;last[len]=x;
	if(son[x])dfs2(son[x],topp);
	for(auto y:e[x])
	if(y!=fa[x]&&y!=son[x])
	dfs2(y,y);
}//树剖
int sum[4*N],tag[4*N];
void pushup(int p){sum[p]=sum[p<<1]+sum[p<<1|1];}
void pushdown(int p,int l,int r)
{
	if(tag[p]==-1)return;
	int mid=(l+r)>>1;
	sum[p<<1]=(mid-l+1)*tag[p];
	sum[p<<1|1]=(r-mid)*tag[p];
	tag[p<<1]=tag[p];
	tag[p<<1|1]=tag[p];
	tag[p]=-1;
}
void update(int p,int ll,int rr,int l,int r,int k)
{
	if(l<=ll&&rr<=r){sum[p]=(rr-ll+1)*k;tag[p]=k;return;}
	pushdown(p,ll,rr);
	int mid=(ll+rr)>>1;	
	if(l<=mid)update(p<<1,ll,mid,l,r,k);
	if(r>mid)update(p<<1|1,mid+1,rr,l,r,k);
	pushup(p);
}
void date(int u,int v,int z)
{
	while(top[u]!=top[v])
	{
		if(deep[top[u]]<deep[top[v]])swap(u,v);
		update(1,1,n,now[top[u]],now[u],z);
		u=fa[top[u]];
	}
	if(deep[u]<deep[v])swap(u,v);
	update(1,1,n,now[v],now[u],z);
}
void query(int p,int ll,int rr,int k)
{
	if(ll==rr&&ll==k){ans=sum[p];return;}
	pushdown(p,ll,rr);
	int mid=(ll+rr)>>1;
	if(k<=mid)query(p<<1,ll,mid,k);
	if(k>mid)query(p<<1|1,mid+1,rr,k);
	pushup(p);
}//线段树维护
int maxn,maxi;
signed main()
{
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=4*n;i++)tag[i]=-1;
	for(int i=1;i<n;i++){cin>>x>>y;e[x]+=y;e[y]+=x;}
	deep[1]=1;fa[1]=1;dfs1(1);dfs2(1,1);
	for(int i=1;i<=m;i++)
	{
		ji.clear();maxn=0;maxi=0;//清空
		cin>>k;
		for(int j=1;j<=k;j++)
		{
			cin>>x;
			if(fa[x]!=1)
			{
				ji.emplace_back(fa[x]);
				if(deep[fa[x]]>maxn){maxn=deep[fa[x]];maxi=fa[x];}//寻找深度最深的点
			}
		}
		if(ji.size()<=1){cout<<"YES\n";continue;}
		date(1,maxi,1);//标记
		for(int j=0;j<ji.size();j++)
		{
			ans=0;
			query(1,1,n,now[ji[j]]);//查询点
			if(!ans){cout<<"NO\n";goto ff;}
		}
		cout<<"YES\n";
		ff:;
		date(1,maxi,0);//清空
	}
}
```

---

## 作者：FutureThx (赞：1)

比较有思维含量的题目，LCA练手题

### 题目大意

给出一个根为 $1$ 的树，$m$ 次询问。

每次询问给出 $k$ 个节点，问是否存在一条以根节点 $1$ 为其中一个端点的链使得这 $k$ 个节点距离链的距离 $\le 1$ 。

### 解题思路

首先可以很快发现一个非常显然的结论：如果存在答案，那么当这条链除根节点外另外一个端点为这 $k$ 个节点中深度最大的节点时，这条链必定满足题目要求。

考虑到多组询问，所以不能直接暴力判断，同时又发现：

设 $u$ 为 $k$ 个节点中深度最大的节点，那么对于任意深度小于 $u$ 深度的节点 $v$ ，必定有 $LCA(u,v)$ 在端点分别为 $1$ 与 $u$ 的链上，因为这条链上包含了节点 $u$ 的所有祖先。

则可以根据这个性质来解题：遍历所有 $k$ 个节点，若存在一个节点 $v$ ,使得 $dis[LCA(u,v),v] >1$ ,则输出 ```NO``` ，否则输出 ```YES``` （注意输出格式为大写）

### 代码

```cpp
// Code of Ymw123
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;
#define int long long
#define MAX_N 200010
int n,m,t;
struct Tree{
    int dep;
    vector<int> next;
}node[MAX_N];
int f[MAX_N][21];
void bfs(int root){
    t = (int)(log(n) / log(2)) + 1;
    queue<int> q;
    q.push(root);
    node[root].dep = 1;
    while(!q.empty()){
        int u = q.front();
        q.pop();
        for(int i = 0;i < node[u].next.size();i++){
            int v = node[u].next[i];
            if(node[v].dep != 0)continue;
            node[v].dep = node[u].dep + 1;
            f[v][0] = u;
            for(int j = 1;j <= t;j++)
                f[v][j] = f[f[v][j - 1]][j - 1];
            q.push(v);
        }
    }
}
int LCA(int x,int y){
    int t = (int)(log(n) / log(2)) + 1;
    if(node[x].dep > node[y].dep) 
       swap(x,y);
    for(int i = t;i >= 0;i--)
        if(node[f[y][i]].dep >= node[x].dep)
           y = f[y][i];
    if(x == y) return x;
    for(int i = t;i >= 0;i--)
        if(f[x][i] != f[y][i])
           x = f[x][i],y = f[y][i];
    return f[x][0];
}
int dis(int x,int y){
    return node[x].dep + node[y].dep -  2 * node[LCA(x,y)].dep;
}
signed main(){
    cin >> n >> m;
    for(int i = 1;i < n;i++){
        int u,v;
        cin >> u >> v;
        node[u].next.push_back(v);
        node[v].next.push_back(u);
    }
    bfs(1);
    int v[MAX_N];
    while(m--){
        int k,max_node = -1;
        cin >> k;
        for(int i = 1;i <= k;i++){
            cin >> v[i];
            if(i == 1)max_node = v[i];
            else max_node = node[v[i]].dep > node[max_node].dep ? v[i] : max_node;
        }
        bool ans = true;
        for(int i = 1;i <= k;i++){
            int lca = LCA(v[i],max_node);
            if(dis(v[i],lca) > 1)ans = false,i = k + 1;
        }
        if(ans)cout << "YES" << endl;
        else cout << "NO" << endl;
    }
    return 0;
}
```

### 后记

Updata 2021/5/29 : 完成并提交题解

---

## 作者：Islauso (赞：1)

[题目](https://www.luogu.com.cn/problem/CF1328E)

---

这道题看起来还是有点意思，但仔细思考后其实并不是很难。

首先明确一点，对于给定的一个询问中的任意一个点，这条链必走它的父亲一定比必走它自己更有可能找到可行解（~~语文可能不太好，感性理解一下~~），我们可以分情况讨论一下，如果以这个点为根的子树中除了它没有其他的点需要满足要求，那么肯定就没有必要让这条链经过这个点，只经过它的父亲就好了，如果以这个点为根的子树中有需要满足要求的点，那么肯定也必须先经过它的父亲节点再经过这个点，所以，我们可以直接看这些点的父亲节点是否在一条链上，如果某个点的父亲不在链上，那它自己也就不可能在链上。

至于如何判断这些父亲节点是否在链上，我们可以先根据深度对它们升序排序，如果它们都在一条链上，那么前一个点一定会是后一个点的祖先，我们直接求出它们的 LCA，判断是否等于前一个点即可。

参考代码如下。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int n,m,log2n,point[N],fa[N][20],dep[N];
vector<int> edge[N];
bool cmp(int a,int b)
{
	return dep[a]<dep[b];
}
void dfs(int u,int father)//倍增预处理
{
	fa[u][0]=father;
	dep[u]=dep[fa[u][0]]+1;
	for(int i=1;(1<<i)<=dep[u];i++)
		fa[u][i]=fa[fa[u][i-1]][i-1];
	for(int i=0;i<edge[u].size();i++)
	{
		int v=edge[u][i];
		if(v!=fa[u][0])
			dfs(v,u);
	}
}
int lca(int u,int v)//倍增求 LCA
{
	if(dep[u]<dep[v])
		swap(u,v);
	int depu=dep[u],depv=dep[v];
	for(int i=0;i<=log2n;i++)
		if((depu-depv)&(1<<i))
			u=fa[u][i];
	if(u==v)
		return u;
	for(int i=log2n;i>=0;i--)
		if(fa[u][i]!=fa[v][i])
		{
			u=fa[u][i];
			v=fa[v][i];
		}
	return fa[u][0];
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n-1;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		edge[u].push_back(v);
		edge[v].push_back(u);
	}
	dfs(1,0);
	fa[1][0]=1;
	log2n=log(n)/log(2)+0.5;
	for(int i=1;i<=m;i++)
	{
		int s,x,flag=1;
		scanf("%d",&s);
		for(int j=1;j<=s;j++)
		{
			scanf("%d",&x);
			point[j]=fa[x][0];//直接存它们的父亲节点就行了
		}
		sort(point+1,point+1+s,cmp);
		for(int j=1;j<=s-1;j++)
			if(lca(point[j],point[j+1])!=point[j])//判断如上
			{
				flag=0;
				break;
			}
		if(flag)
			printf("YES\n");
		else
			printf("NO\n");
	}
	return 0;
}
```



---

## 作者：suxxsfe (赞：1)

[CF1328E Tree Queries](https://codeforces.com/contest/1328/problem/E)  
## 题意  
给你一个树，然后多次询问  
每次询问给出一堆节点，问你是否能找到一个**从根出发的**链，是的对于给出的每个节点，都能找出链上的点，是的他们的距离小于等于$1$  
$n\leq 2\cdot 10^5,m\leq 2\cdot 10^5,\sum k\leq 2\cdot 10^5$  
其中$m$是询问次数，$k$是每次给出的点数  

-----------  

首先，一个点要想符合题目的条件，无非有两种情况  
一种是就在链上，这个好说  
另一种是距离链上的点距离为$1$，那么，肯定是他的父亲在链上  

所以，我们可以把每个给出的点转换成他的父亲，问题就变成看：能否找到一个链，是的这些点都在链上  
这样的转换对第一种肯定是没有影响的，一个点在链上，他的父亲肯定也在链上  

所以考虑转换后的问题  
我首先想到的是，找出深度最大的节点，对于其它每个点和它求 LCA ，如果这个 LCA 不是那个深度较小的点，说明肯定连不成一个链  
这一点判断基于那个链必须从根出发  
然后写完代码交上去：  

![](https://pic.downk.cc/item/5e7e1c3d504f4bcb049945d6.png)  
\#100 WA!  
emmm，估计是写炸了，~~第一个MLE是邻接表忘开2倍了~~  

然而并没看出错，所以考虑一种实现更简单的方法  
上面求 LCA 其实可以理解为从下向上考虑，那么还有一种从上往下考虑的方法：  
先把每个点按深度从小到大排序，然后如果`p[i+1]`不在`p[i]`的子树里，那么肯定连不成一个链  
至于怎么判断也很简单，记录一个dfs序和每个节点子树大小就行，具体见代码的`check`函数  

$\texttt{code.}$  
```cpp  
#include<cstdio>
#include<algorithm>
#include<iostream>
#include<cmath>
#include<iomanip>
#include<cstring>
#define reg register
#define EN std::puts("")
#define LL long long
inline int read(){
	int x=0,y=1;
	char c=std::getchar();
	while(c<'0'||c>'9'){if(c=='-') y=0;c=std::getchar();}
	while(c>='0'&&c<='9'){x=x*10+(c^48);c=std::getchar();}
	return y?x:-x;
}
int n,m;
int fir[200006],nex[400006],to[400006],tot;
int p[200006],fa[200006],size[200006];
int dfn[200006],deep[200006],dfscnt;
inline void add(int a,int b){
	to[++tot]=b;
	nex[tot]=fir[a];fir[a]=tot;
}
void dfs(int u,int fat){
	fa[u]=fat;deep[u]=deep[fat]+1;dfn[u]=++dfscnt;size[u]=1;
	for(reg int i=fir[u];i;i=nex[i])if(to[i]!=fat) dfs(to[i],u),size[u]+=size[to[i]];
}
inline int check(int a,int b){//看b是不是在a的子树 
	if(dfn[b]<dfn[a]) return 0;
	if(dfn[b]>=dfn[a]+size[a]) return 0;
	//这里一定是>=，如果dfn[b]=dfn[a]+size[a]，也说明b并不在a的子树里，因为统计size[a]的时候a这个点也被算进去了 
	return 1;
}
inline int cmp(int x,int y){return deep[x]<deep[y];}
int main(){
	n=read();m=read();
	for(reg int a,b,i=1;i<n;i++){
		a=read();b=read();
		add(a,b);add(b,a);
	}
	reg int k;
	dfs(1,1);
	while(m--){
		k=read();
		for(reg int i=1;i<=k;i++) p[i]=fa[read()];
		std::sort(p+1,p+1+k,cmp);
		for(reg int i=2;i<=k;i++)
			if(!check(p[i-1],p[i])) goto NO;
		std::puts("YES");continue;
		NO:;std::puts("NO");
	}
	return 0;
}
```  

那个没A的LCA做法也放在这，也许哪天很闲的时候会再调调  
[记录](https://www.luogu.com.cn/record/32199021)  
```cpp  
#include<cstdio>
#include<algorithm>
#include<iostream>
#include<cmath>
#include<iomanip>
#include<cstring>
#define reg register
#define EN std::puts("")
#define LL long long
inline int read(){
	int x=0,y=1;
	char c=std::getchar();
	while(c<'0'||c>'9'){if(c=='-') y=0;c=std::getchar();}
	while(c>='0'&&c<='9'){x=x*10+(c^48);c=std::getchar();}
	return y?x:-x;
}
int n,m;
int fir[200006],nex[400006],to[400006],tot;
int p[200006];
int fa[23][200006],deep[200006];
inline void add(int a,int b){
	to[++tot]=b;
	nex[tot]=fir[a];fir[a]=tot;
}
void dfs(int u,int fat){
	fa[0][u]=fat;deep[u]=deep[fat]+1;
	for(reg int i=fir[u];i;i=nex[i])if(to[i]!=fat) dfs(to[i],u);
}
inline int check(int a,int b){
	for(reg int i=20;~i;i--)
		if(deep[fa[i][b]]>=deep[a]) b=fa[i][b];
	return a==b;
}
int main(){
	n=read();m=read();
	for(reg int a,b,i=1;i<n;i++){
		a=read();b=read();
		add(a,b);add(b,a);
	}
	reg int k,maxdeep,maxdeepid;
	dfs(1,1);
	for(reg int i=1;i<=n;i++)
		for(reg int j=1;j<=20;j++) fa[j][i]=fa[j-1][fa[j-1][i]];
	while(m--){
		k=read();maxdeep=0;
		for(reg int i=1;i<=k;i++){
			p[i]=fa[0][read()];
			if(deep[p[i]]>maxdeep) maxdeep=deep[p[i]],maxdeepid=p[i];
		}
		for(reg int i=1;i<=k;i++)if(p[i]!=maxdeepid){
			if(!check(p[i],maxdeepid)) goto NO;
		}
		std::puts("YES");continue;
		NO:;std::puts("NO");
	}
	return 0;
}
```

---

## 作者：Fairicle (赞：1)

因为这是一个毒瘤的多组询问，所以肯定不能每次询问都 dfs 一遍，又看到了 $\sum\limits\ k$ $\le$ $2e5$ ，所以复杂度应该是要带 $k$ 的。

这题有一个很显然的做法就是选择从根到深度最深的点的路径，然后对于每一个点去看它或者它的父亲是否在这个路径上。大概朴素做法是平方的。

我们发现，如果我们沿着这条路径搜，如果这条路径很长，例如这颗树是条链，就 GG 了，所以我们考虑每一个点。

我们记深度最深的点为 $u$，对于每一个点 $v$ ，它和 $u$ 的 LCA 必定是在选定的路径上的，那么我们只需要判断这个 LCA 和 $v$ 是否距离 $\le1$ 即可。

时间复杂度 $O(logn\sum\limits k$)

code：
```
#include"bits/stdc++.h"
using namespace std;
#define ll long long
#define ri register int
inline int rd(){
	int x=0,flag=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') flag=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+(ch^48);ch=getchar();}
	return x*flag;
}
int n,m,k,a[200010],x,y;
int wl,head[200010],dep[200010],f[200010][20];
struct node{
	int nxt,to;
}star[400010];
inline void add(int from,int to){
	wl++;
	star[wl].to=to;
	star[wl].nxt=head[from];
	head[from]=wl;
}
inline int lowbit(int x){return x & ( - x ) ;}
void dfs(int now,int fa){
	dep[now]=dep[fa]+1;
	f[now][0]=fa;
	for(ri i=head[now];i;i=star[i].nxt)
	{
		int u=star[i].to;
		if(u==fa) continue;
		dfs(u,now);
	}
}
inline int get_lca(int x,int y){
	if(dep[x]<dep[y]) swap(x,y);
	int t=dep[x]-dep[y];
	for(ri i=0;i<=19;++i)
	if(t&(1<<i)) x=f[x][i];
	for(ri i=19;i>=0;--i)
	if(f[x][i]!=f[y][i]) x=f[x][i],y=f[y][i];
	if(x==y) return x;
	return f[x][0];
}
inline void calc(){
	for(ri j=1;j<=19;++j)
	for(ri i=1;i<=n;++i)
	f[i][j]=f[f[i][j-1]][j-1];
}
int main()
{
	n=rd(),m=rd();
	for(ri i=1;i<n;++i)
	{
		x=rd(),y=rd();
		add(x,y),add(y,x);
	}
	dfs(1,0);
	calc();
	while(m--)
	{
		k=rd();
		int maxn=1,flg=1;
		for(ri i=1;i<=k;++i) {a[i]=rd();if(dep[a[i]]>dep[maxn]) maxn=a[i];}
		for(ri i=1;i<=k;++i)
		{
			int lca=get_lca(a[i],maxn);
			if(lca!=a[i]&&f[a[i]][0]!=lca) flg=0;
		}
		if(flg) puts("YES");
		else puts("NO");
	}
    return 0;
}
```


---

## 作者：Polaris_Dane (赞：1)

看到$\sum k_i$以为是个虚树，后来发现这道题目比较憨

首先最优策略肯定选从深度最深的点到根的一条链

那么选出来后，只要每个点的父亲，都在这条链上就可以了(特判一下根)

实现方法树剖和$\text{LCA}$都可以

$\text{LCA}$复杂度$O(\log n\sum k_i)$

树剖复杂度$O(\log^2n\sum k_i)$

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<cctype>
#include<set>
#include<queue>
#define M 2010000
#define inf 0x3f3f3f3f
#define LL long long
#define int long long
const int mod=998244353;
using namespace std;
inline int read(){
	int f=1,x=0;char s=getchar();
	while (!isdigit(s)){if(s=='-')f=-1;s=getchar();}
	while (isdigit(s)){x=(x<<1)+(x<<3)+(s^48),s=getchar();}
	return x*f;
}
int n,m,head[M],cnt,a[M];
struct edge{int to,nxt;}e[M];
inline void add_edge(int u,int v){e[++cnt].nxt=head[u],head[u]=cnt,e[cnt].to=v;}
int dep[M],fa[M],top[M],son[M],siz[M],id[M],ref[M],tot;
inline void dfs1(int rt,int f){
	fa[rt]=f,dep[rt]=dep[f]+1,siz[rt]=1;
	for (int i=head[rt];i;i=e[i].nxt){
		if (e[i].to==f) continue;
		dfs1(e[i].to,rt),siz[rt]+=siz[e[i].to];
		if (siz[e[i].to]>siz[son[rt]]) son[rt]=e[i].to;
	}
}
inline void dfs2(int rt,int topf){
	top[rt]=topf,id[rt]=++tot,ref[tot]=rt;
	if (!son[rt]) return;
	dfs2(son[rt],topf);
	for (int i=head[rt];i;i=e[i].nxt){
		if (e[i].to==fa[rt]||e[i].to==son[rt]) continue;
		dfs2(e[i].to,e[i].to);	
	}
}
inline int get_lca(int x,int y){
	while (top[x]!=top[y]){
		if (dep[top[x]]<dep[top[y]]) swap(x,y);
		x=fa[top[x]];
	}
	if (dep[x]<dep[y]) swap(x,y);
	return y;
}
signed main(void){
	n=read(),m=read();
	for (int i=1;i<=n-1;i++){
		int u=read(),v=read();
		add_edge(u,v),add_edge(v,u);
	}
	dfs1(1,0),dfs2(1,1);
	for (int i=1;i<=m;i++){
		int k=read(),now=0,flag=1;
		for (int j=1;j<=k;j++) a[j]=read(),now=dep[a[j]]>dep[now]?a[j]:now;
		for (int j=1;j<=k;j++){
			int lca=get_lca(now,a[j]);
			if (lca!=a[j]&&lca!=fa[a[j]]&&a[j]!=1) flag=0;
		}
		if (flag) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}

```


---

## 作者：andyli (赞：1)

题意：  

每次询问给一些点，判断能否找到一条从根出发的路径使得每一个点都在这条链上或与这条链的距离为 $1$ 。  
询问的点数和不超过 $2\times 10^5$。  

说句闲话：  

比赛结束前1min想到正解，比赛结束后30秒测对样例，wzbl。  

分析：  

要想使每一个点都在这条链上或与这条链的距离为 $1$ ，则这些点的父亲（不妨设 $1$ 的父亲为 $1$）必须在一条以根出发的链上，只需判断所有点的父亲是否在以根出发的链上即可。把这些点按深度排序，排完序后若相邻两点的 LCA 均为深度较小的那一个点，则说明在一条以根出发的链上。  

时间复杂度 $\mathcal O(\sum k\log \sum k)$。  

代码如下（[快读模板](https://www.luogu.com.cn/blog/andyli/read-template)）：  
```cpp
#include <algorithm>
#include <cstring>
const int maxn = 200005;

int A[maxn];
// 树剖LCA
template <int maxn>
struct Tree_Chain_Split {
    struct Edge {
        int next, to;
        Edge(int next = 0, int to = 0) : next(next), to(to) {}
    } edges[maxn << 1];
    struct Node {
        int dfc, top, dep, son, sz, fa;
    } tree[maxn];

    int id[maxn], head[maxn], cnt, dfc;
    void AddEdge(int u, int v)
    {
        edges[++cnt] = Edge(head[u], v);
        head[u] = cnt;
    }
    void dfs1(int u)
    {
        tree[u].sz = 1;
        for (int i = head[u]; i; i = edges[i].next)
            if (int v = edges[i].to; v != tree[u].fa) {
                tree[v].fa = u;
                tree[v].dep = tree[u].dep + 1;
                dfs1(v);
                tree[u].sz += tree[v].sz;
                if (tree[v].sz > tree[tree[u].son].sz)
                    tree[u].son = v;
            }
    }
    void dfs2(int u, int t)
    {
        tree[u].top = t;
        tree[u].dfc = ++dfc;
        id[dfc] = u;
        if (tree[u].son)
            dfs2(tree[u].son, t);
        for (int i = head[u]; i; i = edges[i].next)
            if (int v = edges[i].to; v != tree[u].fa && v != tree[u].son)
                dfs2(v, v);
    }
    int LCA(int x, int y)
    {
        while (tree[x].top != tree[y].top) {
            if (tree[tree[x].top].dep < tree[tree[y].top].dep)
                swap(x, y);
            x = tree[tree[x].top].fa;
        }
        return tree[x].dep < tree[y].dep ? x : y;
    }
};

Tree_Chain_Split<maxn> t;
int main()
{
    int n, m;
    io.read(n, m);
    for (int i = 1; i < n; i++) {
        int u, v;
        io.read(u, v);
        t.AddEdge(u, v), t.AddEdge(v, u);
    }
    t.tree[1].fa = 1;
    t.dfs1(1), t.dfs2(1, 1);
    while (m--) {
        int k;
        io.read(k);
        for (int i = 1; i <= k; i++) {
            io.read(A[i]);
            A[i] = t.tree[A[i]].fa;
        }
        std::sort(A + 1, A + 1 + k, [](const int& x, const int& y) { return t.tree[x].dep < t.tree[y].dep; });
        bool flag = true;
        for (int i = 1; i < k; i++)
            flag &= t.LCA(A[i], A[i + 1]) == A[i];
        writeln(flag ? "YES" : "NO");
    }
    return 0;
}
```

---

## 作者：Aegleseeker_ (赞：0)

感觉非常一眼。

我们先考虑只有一个点的情况，即：找到一条起点是 $1$ 的链，使得 $u$ 到链的距离 $\le1$。我们找到链上的距那个点最近的点 $v$ ，也就是满足 $\operatorname{dis}(u,v)\le 1$ 的 $v$，容易发现 $v$ 要不就是 $u$ 本身，要不就是 $u$ 的父亲，要不就是 $u$ 的儿子。这三种情况都限制了链的一个条件：

**满足要求的链，必须经过 $u$ 的父亲。**

接下来我们再考虑有 $k$ 个点的情况。根据刚刚的结论，满足要求的链必须经过 $v_1,v_2,\dots, v_k$ 的父亲，且要形成从 $1$ 出发的一条链。

我们先求出每个点的父亲。要满足链都经过这些父亲，说明这些父亲必须形成祖先关系。

我们把这些父亲按深度排序，同时检查是否满足 $\operatorname{lca}(fa_{v_{i-1}},fa_{v_i})=fa_{v_{i-1}}$，不满足说明无法构造出满足要求的链，否则可以构造。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int n,m;
struct edge{
	int to,nxt;
}e[N*2];
int head[N],cnt;
void addedge(int u,int v){
	e[++cnt].to=v;
	e[cnt].nxt=head[u];
	head[u]=cnt;
}
int f[N][20],deep[N];
void dfs(int u,int fa){
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v==fa){
			continue;
		}
		f[v][0]=u;
		deep[v]=deep[u]+1;
		dfs(v,u);
	}
}
void init(){
	for(int j=1;j<=19;j++){
		for(int i=1;i<=n;i++){
			f[i][j]=f[f[i][j-1]][j-1];
		}
	}
}
int lca(int u,int v){
	if(deep[u]<deep[v]){
		swap(u,v);
	}
	for(int i=19;i>=0;i--){
		if(deep[f[u][i]]>=deep[v]){
			u=f[u][i];
		}
	}
	if(u==v){
		return u;
	}
	for(int i=19;i>=0;i--){
		if(f[u][i]!=f[v][i]){
			u=f[u][i];
			v=f[v][i];
		}
	}
	return f[u][0];
}
int q[N];
bool cmp(int x,int y){
	return deep[x]<deep[y];
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>n>>m;
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		addedge(u,v);
		addedge(v,u);
	}
	deep[1]=1;
	f[1][0]=1;
	dfs(1,0);
	init();
	for(int i=1;i<=m;i++){
		int k;
		cin>>k;
		for(int j=1;j<=k;j++){
			cin>>q[j];
			q[j]=f[q[j]][0];
		}
		bool flag=1;
		sort(q+1,q+k+1,cmp);
		for(int j=2;j<=k;j++){
			if(lca(q[j-1],q[j])!=q[j-1]){
				flag=0;
				break;
			}
		}
		if(flag){
			cout<<"YES\n";
		}else{
			cout<<"NO\n";
		}
	}
	return 0;
}
```

---

## 作者：mahaihang1 (赞：0)

## 分析
对于任意一个节点 $i$，如果有一条链到 $i$ 的距离 $\le$ $1$, 则这条链上一定至少有 $i$，$i$ 的父节点，$i$ 的子节点这些节点的其中之一。

同时，我们发现，一条链上如果有 $i$,则也一定有 $i$ 的父节点，因为到达 $i$ 的必须经过 $i$ 的父节点。同理，一条链上如果有 $i$ 的子节点,则也一定有 $i$，也一定有 $i$ 的父亲节点。

所以对于一条链到 $i$ 的距离 $\le$ $1$,则有 $i$ 的父节点在这条链上。

因此，对于每次询问，每个点跳到它的父节点，在判断这些点是否在一条以 $1$ 节点为端点的链上即可。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=200010;
int n,m,ver[2*N],nxt[2*N],hd[N],f[N],x,idx,u,v,k;
queue <int> q;
struct node{
	int fa,deep,size,son,top,dfn;
}a[N];
void add(int x,int y){
	ver[++idx]=y;
	nxt[idx]=hd[x];
	hd[x]=idx;
}
void dfs1(int p,int f){
	a[p].son=0;
	a[p].size=1;
	a[p].fa=f;
	a[p].deep=a[f].deep+1;
	for(int i=hd[p];i;i=nxt[i]){
		if(ver[i]!=f){
			dfs1(ver[i],p);
			a[p].size+=a[ver[i]].size;
			if(a[a[p].son].size<a[ver[i]].size) a[p].son=ver[i];
		}
	}
}
void dfs2(int p,int f,int t){
	a[p].dfn=++idx;
	a[p].top=t;
	if(a[p].son) dfs2(a[p].son,p,t);
	for(int i=hd[p];i;i=nxt[i]){
		if(ver[i]!=f&&ver[i]!=a[p].son) dfs2(ver[i],p,ver[i]);
	}
}//树剖 
int lca(int x,int y){
	while(a[x].top!=a[y].top){
		if(a[a[x].top].deep>a[a[y].top].deep) x=a[a[x].top].fa;
		else y=a[a[y].top].fa;
	}
	return a[x].deep<a[y].deep?x:y;
}//树剖求LCA 
bool cmp(int _x,int _y){
	return a[_x].deep<a[_y].deep;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<n;i++){
		cin>>u>>v;
		add(u,v),add(v,u);
	}
	dfs1(1,0);
	idx=0;
	dfs2(1,0,1);
	for(int i=1;i<=m;i++){
		cin>>k;
		idx=0;
		int x;
		while(k--){
			cin>>x;
			f[++idx]=x;
			if(x!=1) f[idx]=a[f[idx]].fa;//每个点跳它的父节点 
		}
		bool ff=0;
		sort(f+1,f+1+idx,cmp);
		for(int j=1;j<idx;j++){
			if(lca(f[j+1],f[j])!=f[j]){//判断是否在一条链上 
				ff=1;
				break;
			}
		}
		if(ff) cout<<"NO\n";
		else cout<<"YES\n";
	} 
	return 0;
}
```

---

## 作者：Discorder_ (赞：0)

[题目地址](https://www.luogu.com.cn/problem/CF1328E)

**题目概括**：
   
   给你一个以 $1$ 为根的有根树。
   
   每次给出 $k$ 个节点。
   
   求一条链，以 $1$ 和树上其他任意一个点为两端，且这条链经过给出节点或者给出节点的邻接节点。
   
  **解题思路**：
  
  如果要经过一个节点，会有三种情况：
  
  1：经过它的父亲。
  
  2：经过它本身。
  
  3：经过它的两个及以上的儿子（这样才能覆盖节点）。
  
  但是题目给的是一个有根树，所以要想经过一个节点或者它的儿子就必须经过它的父亲，所以题目就变成了让我们满足链经过给出节点的父亲节点。
   
   我们可以按照深度从小到大排序后，依次判断相邻两个点中深度大的是否在深度小的子树内即可。
  
  为什么可以这么做？
  
  以样例的最后一个询问为例：
  
 ![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1328E/c550ce8ec76e16e620040a46eef6ab14f38a250f.png)
 
 
  $5$ 和 $7$ 在排序后相邻，父亲节点分别为 $2$ 和 $3$ ，因为 $3$ 不在 $2$ 的子树内，所以这两个点如果要相连的话，相连的这条路线不能与前面构成的路径连成一条链，所以不符合题意。
  
  **代码（附注释）**：
  
  ```cpp
  #include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
struct node{
	int next,to;
}edge[2*N];
int tot=0,idx=0,head[2*N],n,m,u,v;
int siz[N],dfn[N],fat[N],dep[N];
int k,x,nodes[N];
//siz:点的子树上的点总数, fat:点的父亲, dep:点的深度
//dfn:点的dfs序 
inline void add(int from, int to){
	edge[++tot]={head[from],to};
	head[from]=tot;
} 
inline void dfs(int now, int fa){
    dfn[now]=++idx, fat[now]=fa, siz[now]=1, dep[now]=dep[fa]+1;
    for(int i=head[now]; i!=-1; i=edge[i].next){
    	int to=edge[i].to;
    	if(to==fa) continue;
    	dfs(to,now);
    	siz[now]+=siz[to];
    }
}
inline bool cmp(int a, int b){
	return dep[a]<dep[b];
}//按照深度排序(从小到大) 
inline bool str(int x, int y){
	//cout<<x<<' '<<y<<' '<<dfn[x]<<' '<<dfn[y]<<endl;
	if(dfn[x]+siz[x]>dfn[y]&&dfn[x]<=dfn[y]) return true;
	return false;
}//y是否在x的子树内 

int main(){
    memset(head,-1,sizeof(head));
	scanf("%d%d", &n,&m);
	for(int i=1; i<n; i++){
		scanf("%d%d", &u,&v);
		add(u,v), add(v,u);
	}
	dfs(1,1);
	//求出siz,dfn,dep
	while(m--){
		scanf("%d", &k);
		for(int i=1; i<=k; i++){
			scanf("%d", &x), nodes[i]=fat[x];
		}
		sort(nodes+1,nodes+k+1,cmp);
		bool flag=false;
		for(int i=1; i<k; i++){
			if(!str(nodes[i],nodes[i+1])){
				printf("NO\n");
				flag=true;
				break;
			}
		}
		if(!flag) printf("YES\n");
	}
	return 0;
}
```

**感谢收看！**
  

---

## 作者：lmb990607 (赞：0)

看了一下别的题解好像都带了个log，其实好像不用，因为是从根到某个点的路径那么你如果要经过其中一个询问点的儿子那么一定会经过这个询问点，所以可以转换为对于每个询问点你要么经过它，要么经过它的父亲，显然可以看出会选择的点一定是询问点中深度最深的其中一个

那么其实对于每个询问可以对应到书上的一些点上面，只需要在遍历树的时候记录一下根到当前点的路径有哪些点走过了，并在每个点判断一下对应的询问就行了

复杂度应该是O（n+k）？（不大会算...）

代码常数巨大，可自行优化emmm
```
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#include <ext/pb_ds/priority_queue.hpp>
using namespace __gnu_pbds;
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const ll inff = 0x3f3f3f3f3f3f3f3f;
#define FOR(i,a,b) for(int i(a);i<=(b);++i)
#define FOL(i,a,b) for(int i(a);i>=(b);--i)
#define REW(a,b) memset(a,b,sizeof(a))
#define inf int(0x3f3f3f3f)
#define si(a) scanf("%d",&a)
#define sl(a) scanf("%I64d",&a)
#define sd(a) scanf("%lf",&a)
#define ss(a) scanf("%s",a)
#define mod ll(998244353)
#define pb push_back
#define eps 1e-6
#define lc d<<1
#define rc d<<1|1
#define Pll pair<ll,ll>
#define P pair<int,int>
#define pi acos(-1)
#define VI vector<vector<int>>
using namespace std;
const int N=2e5+8;
int n,m,fa[N],k[N],x,y,deep[N],vis[N],mp[N];
vector<int>g[N],ds[N];
vector<P> q[N];
void dfs(int u,int f)
{
    deep[u]=deep[f]+1;fa[u]=f;
    for(int i=0;i<g[u].size();i++)
    {
        int v=g[u][i];
        if(v==f) continue;
        dfs(v,u);
    }
}

void gao(int u)
{
    mp[u]=1;
    for(int i=0;i<ds[u].size();i++)
    {
        int v=ds[u][i],flag=1;
        FOR(j,0,k[v]-1)
        {
            P qw=q[v][j];
            if(mp[qw.first]||mp[qw.second]) continue;
            flag=0;break;
        }
        vis[v]=flag;
    }
    for(int i=0;i<g[u].size();i++)
    {
        int v=g[u][i];
        if(v==fa[u]) continue;
        gao(v);
    }
    mp[u]=0;
}
int main()
{
    cin.tie(0);
    cout.tie(0);
    cin>>n>>m;
    FOR(i,1,n-1)
    {
        si(x),si(y);
        g[x].pb(y);
        g[y].pb(x);
    }
    dfs(1,0);
    FOR(i,1,m)
    {
        si(k[i]);
        int qw=0,zz;
        FOR(j,1,k[i])
        {
            si(x),q[i].pb(P(fa[x],x));
            if(deep[x]>qw) qw=deep[x],zz=x;
        }
        ds[zz].pb(i);
    }
    gao(1);
    FOR(i,1,m)
    {
        if(vis[i]) puts("YES");
        else puts("NO");
    }
    return 0;
}
```


---

