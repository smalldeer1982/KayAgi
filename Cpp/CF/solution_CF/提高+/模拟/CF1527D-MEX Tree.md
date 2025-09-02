# MEX Tree

## 题目描述

You are given a tree with $ n $ nodes, numerated from $ 0 $ to $ n-1 $ . For each $ k $ between $ 0 $ and $ n $ , inclusive, you have to count the number of unordered pairs $ (u,v) $ , $ u \neq v $ , such that the MEX of all the node labels in the shortest path from $ u $ to $ v $ (including end points) is $ k $ .

The MEX of a sequence of integers is the smallest non-negative integer that does not belong to the sequence.

## 说明/提示

1. In example case $ 1 $ , ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1527D/e5c8025fcfbd1c007ce3cb8c715c969bfaa44c0d.png)
  - For $ k = 0 $ , there is $ 1 $ path that is from $ 2 $ to $ 3 $ as $ MEX([2, 3]) = 0 $ .
  - For $ k = 1 $ , there are $ 2 $ paths that is from $ 0 $ to $ 2 $ as $ MEX([0, 2]) = 1 $ and $ 0 $ to $ 3 $ as $ MEX([0, 2, 3]) = 1 $ .
  - For $ k = 2 $ , there is $ 1 $ path that is from $ 0 $ to $ 1 $ as $ MEX([0, 1]) = 2 $ .
  - For $ k = 3 $ , there is $ 1 $ path that is from $ 1 $ to $ 2 $ as $ MEX([1, 0, 2]) = 3 $
  - For $ k = 4 $ , there is $ 1 $ path that is from $ 1 $ to $ 3 $ as $ MEX([1, 0, 2, 3]) = 4 $ .
2. In example case $ 2 $ , ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1527D/218a42ab66b42084b0180ef8d681f370aa875732.png)
  - For $ k = 0 $ , there are no such paths.
  - For $ k = 1 $ , there are no such paths.
  - For $ k = 2 $ , there is $ 1 $ path that is from $ 0 $ to $ 1 $ as $ MEX([0, 1]) = 2 $ .

## 样例 #1

### 输入

```
2
4
0 1
0 2
2 3
2
1 0```

### 输出

```
1 2 1 1 1 
0 0 1```

# 题解

## 作者：丛雨 (赞：10)

# CF1527D MEX Tree

> 题意:给定一棵n个点的编号为$0\sim n-1$的树，求出mex分别为$0\sim n$的路径数，路径至少包含2个点
>
> mex为一个集合内未出现的最小非负整数
>
> $n\leq 2\cdot 10^5$

可以知道，mex为x的充要条件为0~x-1的数均在路径上且x不在路径上

维护x不在路径上比较复杂，所以我们使用容斥，用包含$[0,x-1]$的路径数减去包含$[0,x]$的路径即可

此时的问题转换为求包含$[0,x]$的路径数

因为路径有且仅有2个端点，所以对于$x$只有当$|\{i\mid i\in[0,x],\exists j\in [0,x],i\in {\tt anc}(j)\}|\leq 2$时存在满足条件的路径.其中${\tt anc}(i)$表示$i$的祖先集合(不包括$i$)

所以我们可以维护$[0,x]$的两个"端点"(没编号在$[0,x]$中的后代的点)，每次加入点$x+1$时则判是否为两个端点中的一个的祖先或后代;如果都不是则当$[x+1,n-1]$时无解

直接用倍增或树剖$\tt lca$的话时间复杂度为$O(n\log n)$,可以过(当然你想用标准$\tt rmq$求$\tt  lca$也可以做到$O(n)$),但是我们其实可以不必求$\tt lca$,直接$O(n)$的求解

我们再$dfs$过程中维护一个单调栈，维护一个关于编号单调递增的序列.被弹掉了的点则说明**存在编号比他小的点为他的后代**，即它不会改变端点.同时我们还可以求出这个点离他最近的编号小于他的点(下文中称这个点为前驱).$x$的前驱在加入$x$时一定为一个端点，否则则构成了"人"字形

但其实这里求出的不一定为严格的前驱，因为可能会有"远房兄弟"弹掉了前驱.但其实没有问题，若真的弹掉了前驱，则说明此时就至少存在$3$个端点了:弹掉前驱的点(的后代),自己(的后代)，前驱上面的点.即构成了"人"字形

所以我们直接用判断要加入点的前驱的方法代替了求$lca$(还比倍增好打些)

时空复杂度$O(n)$,单点最慢46ms，总时间869ms,目前$rk1$

```cpp
#include<bits/stdc++.h>
using namespace std;
# define ll long long
# define read read1<ll>()
# define Type template<typename T>
Type T read1(){
	T t=0;
	char k;
	bool vis=0;
	do (k=getchar())=='-'&&(vis=1);while('0'>k||k>'9');
	while('0'<=k&&k<='9')t=(t<<3)+(t<<1)+(k^'0'),k=getchar();
	return vis?-t:t;
}
# define fre(k) freopen(k".in","r",stdin);freopen(k".out","w",stdout)
int fa[200005],s,sz[200005],sta[200005],to[200005];
ll ans[200005];
bool vis[200005];
vector<int>G[200005];
void dfs(int n,int f){
	fa[n]=f;sz[n]=1;
	while(*sta&&sta[*sta]>n)vis[sta[*sta]]=1,--*sta;
	to[n]=sta[*sta];sta[++*sta]=n;
	for(auto i:G[n])
		if(i!=f)dfs(i,n),sz[n]+=sz[i];
	if(sta[*sta]==n)--*sta;
}
void Put(ll x){
	static int st[20],p;
	if(x<0)putchar('-'),x=-x;
	do st[++p]=x-x/10*10,x/=10;while(x);
	while(p)putchar(st[p]^'0'),--p;
}
int main(){
	for(int T=read;T--;){
		s=read;*sta=0;memset(vis,0,s);
		for(int i=0;i<s;++i)G[i].clear();
		for(int i=1;i<s;++i){
			int u=read,v=read;
			G[u].push_back(v);
			G[v].push_back(u);
		}dfs(0,0);ans[0]=ans[s]=0;
		int u=0,v=0,lt=-1,t=1,p=0;
		for(auto i:G[0])ans[0]+=1ll*t*sz[i],t+=sz[i];
		for(int i=1;i<s;++i){
			if(vis[i]){ans[i]=ans[i-1];continue;}
			if(to[i]==v)swap(u,v);
			if(to[i]==u){
				if(!u&&v){
					int j=i;while(fa[j])j=fa[j];
					if(j==p){memset(ans+i,0,s-i+1<<3);break;}
				}
				u=i;
				if(!v)
					if(~lt)ans[i]=1ll*sz[u]*lt;
					else{
						int j=u;lt=1;while(fa[j])j=fa[j];
						for(auto x:G[0])if(x!=j)lt+=sz[x];
						ans[i]=1ll*sz[u]*lt;p=j;
					}
				else ans[i]=1ll*sz[u]*sz[v];
			}else{memset(ans+i,0,s-i+1<<3);break;}
		}Put(1ll*s*(s-1)/2-ans[0]);putchar(' ');
		for(int i=0;i<s;++i)Put(ans[i]-ans[i+1]),putchar(' ');;putchar('\n');
	}
	return 0;
}
```



---

## 作者：meyi (赞：8)

由 $\text{mex}$ 的定义易知，包含 $[0,i-1]$ 的路径数减去包含 $[0,i]$ 的路径数表示的是包含 $[0,i-1]$ 且不包含 $i$ 的路径数，即 $\text{mex}$ 为 $i$ 的路径数。

定义 $ans_i$ 为包含 $[0,i]$ 的路径数，则 $\forall i\ge 1$，有 $\text{mex}_i=ans_{i-1}-ans_{i}$，而 $\text{mex}_0=\frac{n(n-1)}{2}-ans_0$。故问题转化为求出 $ans_i$。

考虑以 $0$ 为根的最短的包含 $[0,i-1]$ 的路径，设其左、右端点分别为 $l,r$，则 $i$ 有三种不同的情况需要处理，我们分类讨论一下：

1. $i$ 在 $l$ 或 $r$ 的子树中，这时需要将对应端点移动到 $i$。
2. $i$ 在 $l$ 到 $r$的路径上，即 $l$ 或 $r$ 在 $i$ 的子树中，这时无需任何操作。
3. 其余情况，由于一条路径只能有两个端点，则此时没有任何一条路径能包含 $[0,i]$，下标 $\ge i$ 的 $ans$ 的值均为 $0$。

若为第 1、2 种情况，因为两个端点的子树内各取一点作为端点都能形成一条包含 $[0,i]$ 的路径，则 $ans_i$ 为两个端点子树大小相乘，需要注意的是若其中一个端点位于根，即 $1$ 处时，该端点的子树大小应减去**另一个端点所在儿子**的子树大小。

至于如何判断是哪种情况，只需要求 $\text{LCA}$ 即可。

代码如下，请注意实现与上述内容有些许差异：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ri register int
typedef long long ll;
const int maxn=2e5+10;
struct node{
	int to,nxt;
}e[maxn<<1];
int hd[maxn],len;
inline void addedge(int fr,int to){
	e[++len]={to,hd[fr]};
	hd[fr]=len;
}
int dep[maxn],fa[maxn],n,son[maxn],t,top[maxn];
ll siz[maxn];
void dfs1(int p,int f){
	dep[p]=dep[f]+1;
	fa[p]=f;
	siz[p]=1;
	for(ri i=hd[p];i;i=e[i].nxt)
		if(e[i].to!=f){
			dfs1(e[i].to,p);
			siz[p]+=siz[e[i].to];
			if(siz[e[i].to]>siz[son[p]])son[p]=e[i].to;
		}
}
void dfs2(int p,int k){
	top[p]=k;
	if(son[p]){
		dfs2(son[p],k);
		for(ri i=hd[p];i;i=e[i].nxt)
			if(!top[e[i].to])
				dfs2(e[i].to,e[i].to);
	}
}
inline int lca(int x,int y){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		x=fa[top[x]];
	}
	return dep[x]<dep[y]?x:y;
}
ll ans[maxn];
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		len=0;
		memset(hd,0,sizeof hd);
		memset(son,0,sizeof son);
		memset(top,0,sizeof top);
		for(ri i=1,x,y;i<n;++i){
			scanf("%d%d",&x,&y),++x,++y;
			addedge(x,y),addedge(y,x);
		}
		dfs1(1,0);
		dfs2(1,1);
		memset(ans,0,sizeof ans);
		ll sum=1;
		for(ri i=hd[1];i;i=e[i].nxt)ans[1]+=siz[e[i].to]*sum,sum+=siz[e[i].to];
		printf("%lld",1ll*n*(n-1)/2-ans[1]);
		ri l=1,r=1,sl,sr;
		for(ri i=2;i<=n;++i){
			ri a=lca(i,l),b=lca(i,r);
			if(a==l&&b==1){
				if(l==1){
					sl=siz[i];
					for(ri j=i;fa[j]>1;j=fa[j],sl=siz[j]);
				}
				l=i;
			}
			else if(b==r&&a==1){
				if(r==1){
					sr=siz[i];
					for(ri j=i;fa[j]>1;j=fa[j],sr=siz[j]);
				}
				r=i;
			}
			else if(a!=i&&b!=i)break;
			if(l==1)ans[i]=siz[r]*(n-sr);
			else if(r==1)ans[i]=siz[l]*(n-sl);
			else ans[i]=siz[l]*siz[r];
		}
		for(ri i=2;i<=n+1;++i)printf(" %lld",ans[i-1]-ans[i]);
		printf("\n");
	}
	return 0;
}
```

---

## 作者：cwfxlh (赞：6)

# [CF1527D](https://www.luogu.com.cn/problem/CF1527D)   

典题。   

考虑对于每一个点 $0,1,\dots,i-1$ 都选在路径中，这个时候的 $MEX\ge i$。于是我们可以对于每一个 $i$ 都求出 $MEX\ge i$ 的路径个数，输出差分序列就可以了。     

至于维护 $MEX\ge i$ 的路径个数，可以考虑先维护 $0,1,\dots,i-1$ 所构成的虚树（不过实现是完全不需要这么麻烦的，这里只是方便说明）。路径覆盖完这棵虚树是 $MEX\ge i$ 的充要条件。所以如果这个虚树不是一条链，后面的答案就全为零，否则计算一下子树大小乘一下，就算出覆盖这条链的路径个数了。

对于虚树（其实是一条链？）的维护，可以考虑新加入的点是否与之构成一条链，然后更新链端点。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,k1,k2,k3,k4,k5,k6,k7,k8,k9,l,r;
int F[500003][22],dep[500003],ans[500003],sz[500003];
vector<int>E[500003];
void dfs(int now){
	sz[now]=1;
	for(int i=1;;i++){
		if(F[F[now][i-1]][i-1])F[now][i]=F[F[now][i-1]][i-1];
		else break;
	}
	for(auto i:E[now]){
		if(i==F[now][0])continue;
		dep[i]=dep[now]+1;
		F[i][0]=now;
		dfs(i);
		sz[now]+=sz[i];
	}
	return;
}
int _lca(int X,int Y){
	if(dep[X]<dep[Y])swap(X,Y);
	int c=21;
	while(c--)if(dep[F[X][c]]>=dep[Y])X=F[X][c];
	c=21;
	while(c--)if(F[X][c]!=F[Y][c])X=F[X][c],Y=F[Y][c];
	while(X!=Y){
		X=F[X][0];
		Y=F[Y][0];
	}
	return X;
}
int dis(int X,int Y){return dep[X]+dep[Y]-2*dep[_lca(X,Y)];}
map<int,int>mp;
signed main(){
	scanf("%lld",&t);
	while(t--){
		scanf("%lld",&n);
		for(int i=1;i<=n;i++){
			E[i].clear();
			E[i].shrink_to_fit();
			for(int j=0;j<=21;j++)F[i][j]=0;
		}
		for(int i=1;i<n;i++){
			scanf("%lld%lld",&k1,&k2);
			k1++;
			k2++;
			E[k1].emplace_back(k2);
			E[k2].emplace_back(k1);
		}
		mp.clear();
		for(int i=0;i<=n+2;i++)ans[i]=0;
		dep[1]=1;
		dfs(1);
		for(int i=1;i<=n;i++){
			k1=n-1;
			for(auto j:E[i]){
				if(dep[j]>dep[i]){
					mp[i*(n+1)+j]=sz[j];
					k1-=sz[j];
				}
			}
			if(F[i][0])mp[i*(n+1)+F[i][0]]=k1;
		}
		ans[1]=(n*(n-1)/2);
		l=r=1;
		for(int i=2;i<=n+1;i++){
			k1=_lca(l,r);
			k2=1;
			if(k1!=l&&k1!=r)k2=sz[l]*sz[r];
			else{
				if(k1==r)swap(l,r);
				k2=sz[r];
				k3=r;
				k4=21;
				while(k4--)if(dep[F[k3][k4]]>dep[l])k3=F[k3][k4];
				k2*=mp[k3*(n+1)+l];
			}
			if(l==r){
				k2=n*(n-1)/2;
				for(auto j:E[l])k2-=sz[j]*(sz[j]-1)/2;
			}
			ans[i]=k2;
			if(i>n)break;
			if(dis(l,r)!=dis(i,l)+dis(i,r)){
				if(dis(l,i)==dis(l,r)+dis(r,i))r=i;
				else{
					if(dis(i,r)==dis(i,l)+dis(l,r))l=i;
					else break;
				}
			}
		}
		for(int i=1;i<=n+1;i++)printf("%lld ",ans[i]-ans[i+1]);
		printf("\n");
	}
	return 0;
}
```


---

## 作者：AsunderSquall (赞：6)

## 题意  

给一棵 $n$ 个节点的树，标号从 $0$ 到 $n-1$，对于任意 $k$，求点对 $u,v$ 的数量，使得 $\text{Mex}_{ w \in path(u,v)}=k$。

## 题解

whk 了两个月之后感觉自己已经没有脑子了（奇怪，说得好像我曾经有过一样）。

首先考虑在链上怎么做。我们从 $0$ 开始往上推，比如我们现在枚举到了 $x$。  
那么我们发现 $0$ 到 $x$ 的数一定在一个区间 $[l,r]$ 内，于是我们知道 $\text{Mex}> x$ 的路径数有 $l\times(n-r+1)$ 条。然后以此类推，最后输出的时候减一下即可。

然后我们考虑怎么上树。首先，如果 $0$ 到 $x$ 的数不在同一条链上，那么能够同时经过这些数的路径一定不存在。否则显然 $0$ 到 $x-1$ 也一定是一条链，那么我们维护这条链和链两端的节点数即可。

我维护链的方法是，如果当前点不在链上，就不停地跳父亲直到找到已经在链上的点。如果是端点，那么就产生了新的端点，否则一定不是一条链。链两端的节点数可以直接用子树大小。

## 代码：
实现非常丑陋（最开始的时候甚至把一个 bool 数组能干的事用 set 来做，我果然没脑子）  

```cpp

int n,ans,m,l,r,L,R;
int a[N],b[N],sz1[N],sz2[N],FA[N],S[N];
vector<int> T[N];
void dfs(int u,int fa,int sz[])
{
    FA[u]=fa;
    sz[u]=1;for (int v:T[u]) if (v!=fa) dfs(v,u,sz),sz[u]+=sz[v];
}
signed main()
{
    int qwq;rd(qwq);while (qwq--)
    {
        rd(n);
        for (int i=0;i<=n;i++) T[i].clear();
        for (int i=1,x,y;i<n;i++) rd(x),rd(y),T[x].push_back(y),T[y].push_back(x);
        for (int i=0;i<=n+1;i++) a[i]=0,sz1[i]=sz2[i]=0,S[i]=0;
        l=r=0;dfs(0,-1,sz1);a[0]=n*(n-1)/2;
        a[1]=2*n-2;for (int v:T[0]) a[1]+=(n-1-sz1[v])*sz1[v];a[1]/=2;
        dfs(1,-1,sz2);l=1;r=0;L=sz1[l];R=sz2[r];a[2]=L*R;
        int x=0;while (x!=1) S[x]=1,x=FA[x];S[1]=1;
        for (int k=2;k<n;k++)
        {
            if (S[k]) {a[k+1]=L*R;continue;}
            int x=k;
            while (!S[x]) x=FA[x];
            if (x==l) 
            {
                int x=k;while (x!=l) S[x]=1,x=FA[x];
                l=k,L=sz1[l],a[k+1]=L*R;
            } else if (x==r) 
            {
                int x=k;while (x!=r) S[x]=1,x=FA[x];
                r=k;R=sz2[r],a[k+1]=L*R;
            } else break;
        }
        for (int i=0;i<=n;i++) a[i]-=a[i+1],cout<<a[i]<<" ";
        puts("");
    }
}
```

---

## 作者：do_while_true (赞：4)

求出 $mex\geq i$ 的路径数，然后再差分一下可以得到答案。

计算 $mex\geq i$ 的路径数，考虑 $0\sim i-1$ 在树上必须形成的一条链，路径数就是两个端点子树大小的乘积。

如果其中一个端点是另一个端点的祖先，那么就是底部的端点子树大小 $\times $ 顶部从上到下第二个节点的子树补大小。

找到顶部从上到下第二个节点，可以使用倍增。

看一个点是否在一条链上，就算一下这个点到这条链的距离即可。

考虑维护这条链的两个端点，每次新加进来一个点的时候分类讨论一下看看这个点会破坏掉链，还是在链中，还是作为新的端点。

码力归零选手表示好难写。

```cpp
#include<cstdio>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<ctime>
#include<random>
#include<assert.h>
#define pb emplace_back
#define mp make_pair
#define fi first
#define se second
#define dbg(x) cerr<<"In Line "<< __LINE__<<" the "<<#x<<" = "<<x<<'\n';
#define dpi(x,y) cerr<<"In Line "<<__LINE__<<" the "<<#x<<" = "<<x<<" ; "<<"the "<<#y<<" = "<<y<<'\n';
#define int long long
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int>pii;
typedef pair<ll,int>pli;
typedef pair<ll,ll>pll;
typedef vector<int>vi;
typedef vector<ll>vll;
typedef vector<pii>vpii;
template<typename T>T cmax(T &x, T y){return x=x>y?x:y;}
template<typename T>T cmin(T &x, T y){return x=x<y?x:y;}
template<typename T>
T &read(T &r){
	r=0;bool w=0;char ch=getchar();
	while(ch<'0'||ch>'9')w=ch=='-'?1:0,ch=getchar();
	while(ch>='0'&&ch<='9')r=r*10+(ch^48),ch=getchar();
	return r=w?-r:r;
}
template<typename T1,typename... T2>
void read(T1 &x, T2& ...y){ read(x); read(y...); }
const int N=200010;
int n;
int f[N],siz[N],dfn[N],dft,in[N],out[N],eft;
int L,R;
int pa[N][20];
int dep[N];
int trs[N];
int getfa(int x){
	return f[x]==x?x:f[x]=getfa(f[x]);
}
ll ans[N];
vi eg[N];
void dfs1(int x,int fa){
	trs[x]=1;
	if(x!=0){
		for(auto v:eg[x])if(v!=fa)dfs1(v,x),trs[x]+=trs[v];
	}
	else
		for(auto v:eg[x])if(v!=fa)dfs1(v,x),ans[1]+=1ll*trs[x]*trs[v],trs[x]+=trs[v];
}
void dfs2(int x,int fa){
	dep[x]=dep[fa]+1;trs[x]=1;dfn[x]=++dft;
	pa[x][0]=fa;
	for(int i=1;i<=19;i++)pa[x][i]=pa[pa[x][i-1]][i-1];
	in[x]=++eft;
	for(auto v:eg[x])if(v!=fa){
		dfs2(v,x);
		trs[x]+=trs[v];
	}
	out[x]=++eft;
}
int findsub(int x,int y){
	for(int i=19;~i;--i)
		if(dep[pa[y][i]]>dep[x])
			y=pa[y][i];
	return y;
}
int chkfa(int x,int y){//y is x's fafafa
	return in[y]<=in[x]&&out[x]<=out[y];
}
int LCA(int x,int y){
	if(dep[y]>dep[x])swap(x,y);
	for(int i=19;~i;--i)
		if(dep[pa[x][i]]>=dep[y])
			x=pa[x][i];
	if(x==y)return x;
	for(int i=19;~i;--i)
		if(pa[x][i]!=pa[y][i])
			x=pa[x][i],y=pa[y][i];
	return pa[x][0];
}
int dis(int x,int y){
	int lca=LCA(x,y);
	return dep[x]+dep[y]-2*dep[lca];
}
ll calc(){
	if(dep[L]<dep[R])swap(L,R);
	int lca=LCA(L,R);
	if(lca==R){
		return 1ll*trs[L]*(n-trs[findsub(R,L)]);
	}
	else{
		return 1ll*trs[L]*trs[R];
	}
}
void solve(){
	read(n);dft=eft=0;
	for(int i=0;i<=n;i++){
		ans[i]=0;
		vi().swap(eg[i]);
	}
	L=0;R=1;
	for(int i=1;i<n;i++){
		int u,v;read(u,v);
		eg[u].pb(v);eg[v].pb(u);
	}
	dfs1(0,N-1);
	dfs2(0,N-1);
	for(int x=1;x<n;x++){
		if(dep[L]<dep[R])swap(L,R);
//		dpi(L,R);
		if(dis(x,L)+dis(x,R)-dis(L,R)==0){
			ans[x+1]=calc();
		}
		else{
			int lca=LCA(L,R);
			if(lca==R){
				if(chkfa(R,x))
					R=x;
				else{
					if(chkfa(x,L))L=x;
					else{
						int tl=findsub(R,L);
//						dbg(tl);
						if(chkfa(x,tl))break;
						R=x;
					}
				}
			}
			else{
				if(chkfa(x,L))L=x;
				else if(chkfa(x,R))R=x;
				else break;
			}
			ans[x+1]=calc();
		}
	}
	ans[0]=1ll*n*(n-1)/2;
//	for(int i=0;i<=n;i++)cout << ans[i] << ' ';
//	puts("");
	ans[n+1]=0;
	for(int i=0;i<=n;i++)cout << ans[i]-ans[i+1] << ' ';
	puts("");
	
}
signed main(){
	int T;read(T);
	while(T--)solve();
	return 0;
}
```

---

## 作者：Dfkuaid (赞：4)

> [题目链接](https://www.luogu.com.cn/problem/CF1527D)

## #1.0 基本思路

首先需要理解这个 "mex" 的含义，我们需要找出所有的路径使得 $i$ 是编号最小的未出现的点，那么也就意味着 $[0,i-1]$ 应当全部包含在我们要找的路径中。那么我们便可以尝试维护这样的路径：路径两端 $x, y\in[0,i-1]$，$[0，i-1]$ 包含在路径经过的点集中，然后计算有多少条路经可以不经过 $i$（询问）。最后再尝试将 $i$​ 加入当前维护的路径（修改）。

不妨先将整棵树的根节点设为 $0$。

## #2.0 分类讨论

>  下文中会反复运用 LCA 来进行判断，这里采用 st 表 $O(n\log n)$ 预处理，$O(1)$​ 询问的方法。​

- `siz[i]` 表示以 $i$​ 为根的子树大小。
- `sp` 为非零端点所在 $0$ 的对应儿子的子树大小

本题涉及到的情况比较多，这里会一一讨论。

### #2.1 询问

先来看询问的部分，整体分为 $3$​ 种情况：

- **$i$ 在当前路径中**；
- **$i$ 是当前路径端点的子孙**；
- **$i$ 不属于上面的任意一种情况**；

这里再拎出来两种比较特殊的情况：$mex=0$ 和 $mex=1.$

当 $mex=0$​ 时，每次选择的路径应当是都在同一 $0$​ 的子树内的两个点为端点；当 $mex=1$​​ 时，可行的路径数为在去掉 $1$​ 的子树后的点集中任意选取两个点产生的路径条数，减去不经过 $0$ 的路径数量（即在仅在 $0$​ 的子节点的子树内的路径），需要特判是 $1$ 的祖先的子树的情况，采用 LCA 判断。计算代码如下：

``` cpp
inline void pre_ans() {
    ans[1] = (siz[0] - siz[1]) * (siz[0] - siz[1] - 1) / 2;
    for (int i = head[0]; i; i = e[i].nxt) {
        ans[0] += (1ll * siz[e[i].v] * (siz[e[i].v] - 1)) / 2;
        int lca = LCA(1, e[i].v);
        if (lca == e[i].v) ans[1] -= ((siz[e[i].v] - siz[1])
                                    * (siz[e[i].v] - siz[1] - 1) / 2);
        else ans[1] -= siz[e[i].v] * (siz[e[i].v] - 1) / 2;
    }
}
```

解决上面的两种特殊情况后，我们再来看将所有情况分为两种情况：

- **路径一端是零**；
- **路径两端都不是零**；

先来看路径一端是零（两端分别为 $x,0$）的情况：

- **$i$​ 在当前路径中**；

  $LCA(x,i)=i$，这种情况答案一定为 $0$；

- **$i$ 是当前路径端点的子孙**；
  1. $i$​ 是不为零的一端的端点的子孙。那么答案应当是 `(siz[x] - siz[i]) * (siz[0] - sp)`。这种情况的判断条件 $LCA(x,i)=x$；
  2. $i$​ 是不与非零端点所在 $0$​ 的对应儿子的子树中。那么答案是 `(siz[0] - sp - siz[i]) * siz[x]`。这种情况的判断条件 $LCA(x, i)=0$​；

- **$i$ 不属于上面的任意一种情况**；

  那么也就意味着 $i$ 是当前路径上的一个分叉，答案即为 `(siz[0] - sp) * siz[x]`。

再来看路径两端 $x,y$ 都不是零的情况：

- **$i$ 在当前路径中**；

  $LCA(x,i)=i$ 或 $LCA(y,i)=i$​，那么答案为零；

- **$i$ 是当前路径端点的子孙**；

  答案为对应端点子树大小减去 `siz[i]` 再乘上另一端点子树大小；

- **$i$​ 不属于上面的任意一种情况**；

  答案为 `siz[x] * siz[y]`；

以上，便是查询操作的所有内容。以下是代码:

``` cpp
inline ll GetAns(int k){
    int lca1 = LCA(k, lp), lca2 = LCA(k, rp);
    ll res1, res2;
    if (rp) { //这里在插入时会保证为 0 的一端一定是 rp
        res1 = siz[lp]; res2 = siz[rp];
        if (lca1 == k || lca2 == k) return 0;
        /*i 在当前路径上*/
        else if (lca1 == lp) res1 -= siz[k];
        else if (lca2 == rp) res2 -= siz[k];
        /*两种不同的情况*/
    } else {
        res1 = siz[lp]; res2 = siz[rp] - sp;
        if (lca1 == k || lca2 == k) return 0;
        else if (lca1 == lp) res1 -= siz[k];
        else if (lca1 == 0) res2 -= siz[k];
    }
    return res1 * res2;
}
```

### #2.2 修改

现在来尝试将 $i$ 加入当前所维护的路径。

仍旧分为两种大情况：

- 至少一端为 $0$；
- 两端都不为 $0$；

若两端都不为 $0$，那么有以下三种情况：

- **在路径上**。即 $LCA(x, i)=i$ 或 $LCA(y,i)=i$，那么说明 $i$ 已经在路径上。
- **是其中一端的儿子**，即 $LCA(x,i)=x$ 或 $LCA(y,i)=y$，将对应的端点设置为 $i$ 即可；
- **不属于上面的两种情况**，即是当前路径的分叉，那么显然不可能将 $[1,i]$ 通过一条路径相连，那么后面的所有答案数都应当是 $0$​。

若存在至少一端 $y=0$，有以下几种情况：

- 另一端也是 $0$，那么令其中一端变为 $i$；
- $LCA(x,i)=i$，已经在路径上；
- $LCA(x,i)=i$，更新 $x=i$​；
- 不属于上面的情况但 $LCA(x,i)\ne0$，那么意味着分叉了，插入失败；
- $x\ne0$ 且 $LCA(x,i)=0$，那么更新 $y=0$；

``` cpp
inline bool add(int x) {
    int lf = LCA(lp, x), rf = LCA(rp, x);
    if (rp) {
        if (lf == lp) {lp = x; return true;}
        else if (lf == x) return true;
        if (rf == rp) {rp = x; return true;}
        else if (rf == x) return true;
    } else {
        if (lf && (lf != lp && lf != x)) return false;
        else if (lf == lp) {lp = x; return true;}
        else if (lf == x) return true;
        else if (lf) return false;
        else {rp = x; return true;}
    }
    return false;
}
```

## #3.0 完整代码

> 有许多数组可以不 `memset()` 就不 `memset()`；比如本题中的 `dep[]` 和 `siz[]`；

``` cpp
const int N = 600010;
const int INF = 0x3fffffff;

struct Edge {
    int u, v;
    int nxt;
};
Edge e[N << 1];

int n, head[N], cnt = 1, st[N << 1], scnt, lp, rp;
int mn[N << 1][30], dep[N], w[N], rt, t, lg2[N], f1, f2;
ll ans[N], sp, siz[N];

inline void clear() { //清空
    cnt = 1, scnt = lp = rp = 0;
    mset(head, 0); dep[0] = 0;
}

inline void add(const int &u, const int &v) {
    e[cnt].u = u, e[cnt].v = v;
    e[cnt].nxt = head[u], head[u] = cnt ++;
}

inline int LCA(int a, int b) { //O(1) 获得 LCA
    int l = w[a], r = w[b];
    if (r < l) swap(l, r);
    int k = lg2[r - l + 1];
    if (dep[mn[l][k]] < dep[mn[r - (1 << k) + 1][k]])
        return mn[l][k];
    else return mn[r - (1 << k) + 1][k];
}

void dfs(int x, int fa) { //计算 siz[],dep[] 等数组
    st[++ scnt] = x, w[x] = scnt;
    siz[x] = 1, dep[x] = dep[fa] + 1;
    for (int i = head[x]; i; i = e[i].nxt) {
        if (e[i].v == fa) continue;
        dfs(e[i].v, x); st[++ scnt] = x;
        siz[x] += siz[e[i].v];
    }
}

inline void get_st() { //计算 st 表，用于 O(1) LCA
    lg2[1] = 0;
    for (int i = 2; i <= scnt; ++ i) lg2[i] = lg2[i >> 1] + 1;
    for (int i = 1; i <= scnt; ++ i) mn[i][0] = st[i];
    for (int j = 1; j <= lg2[scnt]; ++ j)
      for (int i = 1; i + (1 << j) - 1 <= scnt; ++ i)
        if (dep[mn[i][j - 1]] < dep[mn[i + (1 << (j - 1))][j - 1]])
          mn[i][j] = mn[i][j - 1];
        else mn[i][j] = mn[i + (1 << (j - 1))][j - 1];
}

inline void pre_ans() { //预处理 0 和 1 的答案
    ans[1] = (siz[0] - siz[1]) * (siz[0] - siz[1] - 1) / 2;
    for (int i = head[0]; i; i = e[i].nxt) {
        ans[0] += (1ll * siz[e[i].v] * (siz[e[i].v] - 1)) / 2;
        int lca = LCA(1, e[i].v);
        if (lca == e[i].v) ans[1] -= ((siz[e[i].v] - siz[1])
                                    * (siz[e[i].v] - siz[1] - 1) / 2);
        else ans[1] -= siz[e[i].v] * (siz[e[i].v] - 1) / 2;
    }
}

inline bool add(int x) { //尝试将点加入路径
    int lf = LCA(lp, x), rf = LCA(rp, x);
    if (rp) {
        if (lf == lp) {lp = x; return true;}
        else if (lf == x) return true;
        if (rf == rp) {rp = x; return true;}
        else if (rf == x) return true;
    } else {
        if (lf && (lf != lp && lf != x)) return false;
        else if (lf == lp) {lp = x; return true;}
        else if (lf == x) return true;
        else if (lf) return false;
        else {rp = x; return true;}
    }
    return false;
}

inline ll GetAns(int k){ //计算每个点的答案
    int lca1 = LCA(k, lp), lca2 = LCA(k, rp);
    ll res1, res2;
    if (rp) {
        res1 = siz[lp]; res2 = siz[rp];
        if (lca1 == k || lca2 == k) return 0;
        else if (lca1 == lp) res1 -= siz[k];
        else if (lca2 == rp) res2 -= siz[k];
    } else {
        res1 = siz[lp]; res2 = siz[rp] - sp;
        if (lca1 == k || lca2 == k) return 0;
        else if (lca1 == lp) res1 -= siz[k];
        else if (lca1 == 0) res2 -= siz[k];
    }
    return res1 * res2;
}

int main(){
    scanf("%d", &t);
    while (t --) {
        scanf("%d", &n); clear();
        for (int i = 1; i < n; ++ i) {
            int u, v; scanf("%d%d", &u, &v);
            add(u, v); add(v, u);
        }
        dfs(rt = 0, 0); get_st(); pre_ans();
        /*进行所需要的预处理*/
        for (int i = head[0]; i; i = e[i].nxt)
          if (LCA(e[i].v, 1) == e[i].v) {
              sp = siz[e[i].v]; break;
          } //计算 sp
        for (int i = 2; i <= n; ++ i) {
            if (!add(i - 1)) break; 
            //尝试加入 i-1，不行就退出
            if (i == n) {ans[i] = 1; break;}
            /*如果 i == n，那么显然只存在一条路径
            贯穿整个树（其实是一条链）*/
            ans[i] = GetAns(i);
        }
        for (int i = 0; i <= n; ++ i) {
            printf("%lld ", ans[i]);
            ans[i] = 0;
        }
        printf("\n");
    }
    return 0;
}
```



---

## 作者：chenzhaoxu2027 (赞：3)

致敬传奇分类讨论。

# 题意

给你一棵 $n$ 个点的树，顶点编号 $0,1,\dots,n-1$。定义一条路径的权值是这个路径上的点的编号构成集合的 $\operatorname{mex}$。对于每一个 $0 \le i \le n$ 求出权值恰好是 $i$ 的路径数量。

# 分析

求出恰好为 $i$ 时的答案不好做。考虑求出权值大于等于 $i$ 时的答案再差分回去。

如果某一个路径权值大于等于 $i$ 就说明这个路径经过了 $0,1,\dots,i-1$。如果为 $i$ 的答案不是 $0$ 就说明至少有一个路径能经过这 $i$ 个点。

因此我们从小到大枚举 $i$，同时维护 $l,r$ 表示树链的左右端点。如果 $i,l,r$ 不能被任一树链覆盖那么 $i$ 及以后的答案就全是 $0$ 了。否则我们更新树链的左右端点。答案利用乘法原理，相当于分别在“$r$ 的除了 $l$ 方向以外的其他连通分量”和“$l$ 的除了 $r$ 方向以外的其他连通分量”各选一个点。

考虑如何维护 $l,r$。对于已有的 $l,r$。有两种情况：祖孙关系或不是祖孙关系。如果 $l,r$ 不是祖孙关系，考虑 $i$ 在哪里合法。只有三个地方：$l$ 子树、$r$ 子树、$l,r$ 路径上。前两种情况简单，但是什么时候 $i$ 位于 $l,r$ 路径上呢？

这里给出引理：

- 如果树上某三个节点 $a,b,c$，$a,b$ 不是祖孙关系，$a,b,c$ 两两不等且满足 $\{\operatorname{LCA}(a,b),c\}=\{\operatorname{LCA}(a,c),\operatorname{LCA}(b,c)\}$（这两个都是可重集）那么 $c$ 就在 $a,b$ 路径上。反之亦然。

证明：

记 $\operatorname{LCA}(a,b)=T$，故左侧集合等于 $\{c,T\}$。

讨论 $c$ 的位置：

如果 $c$ 在 $a$ 子树里面，则右侧集合等于 $\{T,a\}$。此时等式不成立。$c$ 在 $b$ 子树里面时同理。

如果 $c$ 不在 $T$ 子树里面，则右侧集合等于 $\{\operatorname{LCA}(T,c) \cdot 2\}$。等式不成立。

如果 $c=T$ 则等式显然成立。

如果 $c$ 在 $a,b$ 路径上，不妨假设 $\operatorname{LCA}(a,c)=T$，那么右侧集合等于 $\{T,c\}$。等式成立。

其他情况下假设 $\operatorname{LCA}(a,c)=T$，那么右侧集合等于 $\{T,\operatorname{LCA}(b,c)\}$。由于 $c$ 不在 $a,b$ 路径上，因此等式不成立。

综上所述，等式成立的充要条件就是 $c$ 在 $a,b$ 路径上。证毕。

这样一来我们就能够解决 $l,r$ 不是祖孙关系的情形了。

然后讨论 $l,r$ 呈祖孙关系的情况。这里设 $r$ 是 $l$ 的祖先。这里 $i$ 的合法位置就剩下了：$l$ 子树、$l,r$ 路径上以及 $r$ 的除 $l$ 方向的子树和 $r$ 子树外这四种情况。这时前两种和第四种是简单的，主要来看第三种。

这里比较巧妙。如果 $i$ 是第三种情况，那么 $i$ 在 $r$ 子树中，因此 $\operatorname{LCA}(r,i)=r$。同时 $i$ 不在“$r$ 的 $l$ 方向子树”里面。换句话说就是 $l$ 不在 $i$ 子树里面呗。于是 $\operatorname{LCA}(l,i)=r$。这两个条件就完美约束了 $i$ 的所有范围。

维护好了 $l,r$ 该计算答案了。依然分讨两种情况：祖孙关系或不是祖孙关系。后者依旧简单，$ans=sz_l \times sz_r$。

对于 $l,r$ 呈祖孙关系的情形，设 $r$ 是 $l$ 的祖先。但是我没有想到巧妙办法，只能够把“$r$ 的 $l$ 方向子树”到底是谁求出来。可以写 dfn 序二分，而使用重剖的人就可以依靠“重链 dfn 序连续”的性质直接爬链即可。

假设“$r$ 的 $l$ 方向子树”是 $u$，那么就有 $ans=sz_l \times (n-sz_u)$。

最终复杂度：$O(n+q\log n)$。瓶颈在于求 LCA 和求定向子树。注意特判掉 $\operatorname{mex}=0,1$ 的情况。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n;
int dfstime;
struct tree_heavy{
	int hson,fa,sz,d;
	int dfn,top;
}t[500005];
int num[500005];
vector<int> g[500005];
int ans[500005];
void dfs1(int x,int fa){
	t[x].fa=fa;
	t[x].sz=1;
	t[x].d=t[t[x].fa].d+1;
	t[x].hson=-1;
	for(int i=0;i<g[x].size();i++){
		int v=g[x][i];
		if(v==fa){
			continue;
		}
		dfs1(v,x);
		t[x].sz+=t[v].sz;
		if(t[x].hson==-1||t[t[x].hson].sz<t[v].sz){
			t[x].hson=v;
		}
	}
}
void dfs2(int x,int tp){
	t[x].top=tp;
	dfstime++;
	t[x].dfn=dfstime;
	num[dfstime]=x;
	if(t[x].hson!=-1){
		dfs2(t[x].hson,tp);
	}
	for(int i=0;i<g[x].size();i++){
		int v=g[x][i];
		if(v==t[x].fa||v==t[x].hson){
			continue;
		}
		dfs2(v,v);
	}
}
int LCA(int x,int y){
	while(t[x].top!=t[y].top){
		if(t[t[x].top].d<t[t[y].top].d){
			swap(x,y);
		}
		x=t[t[x].top].fa;
	}
	if(t[x].d<t[y].d){
		swap(x,y);
	}
	return y;
}
int LZH(int x,int y){
	while(t[x].top!=t[y].top){
		if(t[t[x].top].d<t[t[y].top].d){
			swap(x,y);
		}
		if(t[t[x].top].fa==y){
			return t[x].top;
		}
		x=t[t[x].top].fa;
	}
	if(t[x].d<t[y].d){
		swap(x,y);
	}
	return num[t[y].dfn+1];
}
int l,r;
int calc(){
	int C=LCA(l,r);
	if(C!=l&&C!=r){
		return t[l].sz*t[r].sz;
	}
	if(C==l){
		swap(l,r);
	}
	return t[l].sz*(n-t[LZH(l,r)].sz);
} 
bool check(int x){
	int C=LCA(l,r);
	if(C!=l&&C!=r){
		int cl=LCA(x,l);
		int cr=LCA(x,r);
		if(cl==x&&cr==C||cr==x&&cl==C){
			return 1;
		} 
		if(cl==l&&cr==C){
			l=x;
			return 1;
		}
		if(cr==r&&cl==C){
			r=x;
			return 1;
		}
		return 0;
	}
	if(C==l){
		swap(l,r);
	}
	int cl=LCA(x,l);
	int cr=LCA(x,r);
	if(cl==l){
		l=x;
		return 1;
	}
	if(cl==x&&cr==r){
		return 1;
	}
	if(cr==cl){
		r=x;
		return 1;
	}
	return 0;
}
void slv(){
	dfstime=0;
	for(int i=1;i<=n;i++){
		g[i].clear();
		t[i]={0,0,0,0,0,0};
	}
	cin>>n;
	for(int i=1;i<n;i++){
		int x,y;
		cin>>x>>y;
		x++;
		y++;
		g[x].push_back(y);
		g[y].push_back(x);
	}
	dfs1(1,0);
	dfs2(1,1);
	l=1,r=2;
	ans[0]=ans[1]=n*(n-1)/2;
	for(int v:g[1]){
		ans[1]-=t[v].sz*(t[v].sz-1)/2;
	}
	ans[2]=calc();
	ans[n+1]=0;
	int fl=0;
	for(int i=3;i<=n;i++){
		if(fl||!check(i)){
			fl=1;
			ans[i]=0;
		}
		else{
			ans[i]=calc();
		}
	}
	for(int i=0;i<n;i++){
		ans[i]-=ans[i+1];
	}
	for(int i=0;i<=n;i++){
		cout<<ans[i]<<" ";
	}
	cout<<"\n";
}
signed main(){
	int t;
	cin>>t;
	while(t--){
		slv();
	}
	return 0;
}
```

附图：

![](https://cdn.luogu.com.cn/upload/image_hosting/qecff23d.png)

---

## 作者：yyrwlj (赞：2)

不用差分的一个做法。

考虑 MEX 为 $i$ 当且仅当包含了 $0$ 到 $i - 1$ 且不包含 $i$。

那么 $0$ 到 $i-1$ 必须在一条路径上，不然往后肯定都无解。

接下来我们考虑路径的两头，如果 $i$ 不在这两头的子树里面就直接算乘积即可，否则在哪边就把哪边的子树大小减去子树 $i$ 的大小即可。

判在哪边子树只需要看与那个头的 lca 是不是那个头就行。

两个头中有一个是 $0$ 就需要特殊处理，我们可以把这个头的信息去掉另一个头方向子树 $x$ 的信息，看在不在这个头的子树内只需要看与 $x$ 的 lca 是不是不等于它即可。

```cpp
#include <bits/stdc++.h>
#define lowbit(o) o & -o
#define pb push_back
#define x first
#define y second
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef pair<int, int> PII;
typedef pair<LL, LL> PLL;
const int N = 200005, K = 19;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
LL siz[N], n;
vector<int> g[N];
int dep[N], f[N][K], x, y;
bool st[N];
void dfs(int u,int fa)
{
	siz[u] = 1;
	dep[u] = dep[fa] + 1;
	for (int i : g[u])
		if (i != fa)
		{
			f[i][0] = u;
			for (int j=1;j<K;j++)
				f[i][j] = f[f[i][j - 1]][j - 1];
			dfs(i, u);
			siz[u] += siz[i];
		}
}
int lca(int x,int y)
{
	if (dep[x] < dep[y])
		swap(x, y);
	for (int i=K-1;i>=0;i--)
		if (dep[f[x][i]] >= dep[y])
			x = f[x][i];
	if (x == y)
		return x;
	for (int i=K-1;i>=0;i--)
		if (f[x][i] != f[y][i])
			x = f[x][i], y = f[y][i];
	return f[x][0];
}
int get(int x)
{
	for (int i=K-1;i>=0;i--)
		if (f[x][i])
			x = f[x][i];
	return x;
}
void work()
{
	cin >> n;
	for (int i=0;i<n;i++)
		g[i].clear(), st[i] = false;
	for (int i=1;i<n;i++)
	{
		int a, b;
		cin >> a >> b;
		g[a].pb(b);
		g[b].pb(a);
	}
	if (n == 2)
	{
		cout << "0 0 1\n";
		return;
	}
	dep[0] = 0;
	dfs(0, 0);
	LL ans0 = 0;
	for (int i : g[0])
		ans0 += siz[i] * (siz[i] - 1) / 2;
	cout << ans0 << ' ';
	int f1 = get(1);
	LL sum = 1, ans1 = 0;
	for (int i : g[0])
		if (i == f1)
			ans1 += sum * (siz[i] - siz[1]), sum += siz[i] - siz[1];
		else
			ans1 += sum * siz[i], sum += siz[i];
	cout << ans1 << ' ';
	x = y = 0;
	st[0] = true;
	for (int i=2;i<=n;i++)
	{
		int v = i - 1;
		if (!st[v])
		{
			while (!st[v])
				st[v] = true, v = f[v][0];
			if (v != x && v != y)
			{
				if (v == i - 1)
					continue;
				for (;i<=n;i++)
					cout << "0 ";
				break;
			}
			if (v == x)
				x = i - 1;
			else
				y = i - 1;
		}
		if (st[i])
		{
			cout << "0 ";
			continue;
		}
		LL sx = siz[x], sy = siz[y];
		if (!x)
			sx -= siz[get(y)];
		if (!y)
			sy -= siz[get(x)];
		if (lca(x, i) == x && (x || lca(get(y), i) != get(y)))
			cout << sy * (sx - siz[i]) << ' ';
		else if (lca(y, i) == y && (y || lca(get(x), i) != get(x)))
			cout << sx * (sy - siz[i]) << ' ';
		else
			cout << sx * sy << ' ';
	}
	cout << '\n';
}
signed main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int _T = 1;
    cin >> _T;
    while (_T--)
        work();
    return 0;
}
```

---

## 作者：DengDuck (赞：2)

好题，学到了一个关于 $\text{mex}$ 的有用性质。

一个集合 $S$ 满足 $\text{mex}$ 为 $x$ 当且仅当满足 $[0,x-1]\subseteq S,x\not\in S$，那么显然我们可以转换为包含 $[0,x-1]$ 的数量减去包含 $[0,x]$ 的数量。

所以对于这道题，我们只需要求 $ans_x$ 表示满足  $[0,x]\subseteq S$
的路径数量即可。

发现包含 $[0,x]$ 的前提是包含 $[0,x-1]$，如果有解的话显然可以找到两个点 $l,r\in[0,x]$ 使得 $[0,x]\subseteq (l\to r)$，这里的 $l\to r$ 表示一条路径。

那么方案数显然是 $sz_l\times sz_r$，但是如果 $l=1$ 或者 $r=1$ 的时候需要特殊处理防止 $l,r$ 在根节点的同一个儿子内。

拜谢 meyi，太神了。

```cpp
#include<bits/stdc++.h>
#define LL long long
#define LF long double
#define pLL pair<LL,LL>
#define pb push_back
//#define fir first
//#define sec second
using namespace std;
//const LL inf;
const LL N=2e5+5;
const LL M=18;
//const LL mod;
//const LF eps;
//const LL P;
vector<LL>v[N];
LL T,n,dep[N],sz[N],ans[N],F[N][M+5];
void dfs(LL x,LL fa)
{
	dep[x]=dep[fa]+1;
	sz[x]=1;
	F[x][0]=fa;
	for(int i=1;i<=M;i++)F[x][i]=F[F[x][i-1]][i-1];
	for(LL i:v[x])
	{
		if(i==fa)continue;
		dfs(i,x);
		sz[x]+=sz[i];
	}
}
LL lca(LL x,LL y)
{
	if(dep[y]>dep[x])swap(x,y);
	for(int i=M;i>=0;i--)if(dep[x]-(1<<i)>=dep[y])x=F[x][i];
	if(x==y)return x;
	for(int i=M;i>=0;i--)if(F[x][i]!=F[y][i])x=F[x][i],y=F[y][i];
	return F[x][0];
}
int main()
{
	scanf("%lld",&T);
	while(T--)
	{
		scanf("%lld",&n);
		for(int i=1;i<=n+5;i++)
		{
			v[i].clear();
			ans[i]=0;
			for(int j=0;j<=M;j++)F[i][j]=0;
		}
		for(int i=1;i<=n-1;i++)
		{
			LL x,y;
			scanf("%lld%lld",&x,&y);
			x++,y++;
			v[x].pb(y),v[y].pb(x);
		}
		dfs(1,0);
		ans[0]=n*(n-1)/2;
		LL sum=1;
		for(LL i:v[1])ans[1]+=sz[i]*sum,sum+=sz[i];
		LL l=1,r=1;
		for(int i=2;i<=n;i++)
		{
			LL a=lca(i,l),b=lca(i,r),sl,sr;
			if(a==l&&b==1)
			{
				if(l==1)
				{
					sl=sz[i];
					for(LL j=i;F[j][0]!=1;j=F[j][0],sl=sz[j]);//找 l 是根节点的哪个儿子，这个子树 r 不能选
				}
				l=i;
			}
			else if(b==r&&a==1)r=i;
			else if(a!=i&&b!=i)break;
			if(l==1)ans[i]=sz[r]*(n-sr);
			else if(r==1)ans[i]=sz[l]*(n-sl);
			else ans[i]=sz[l]*sz[r];
		}
		for(int i=1;i<=n+1;i++)printf("%lld ",ans[i-1]-ans[i]);
		printf("\n");
	}
	return 0;
}
//RP++
```

## 一个小提醒

可以不写 LCA 吗？其实是可以的，而且更加优美，考虑以下实现：

```cpp
bool In(int x,int y)
{
	return Dfn[x]<=Dfn[y]&&Dfn[y]<=Dfn[x]+Sz[x]-1;
}
void Work()
{
	int L=0,R=0,RF=0;Hav[0]=1;
	for(int i=1;i<=n;i++)
	{
		if(L==R)
		{
			LL Sum=1;
			for(int j:G[0])
			{
				S[i]+=1ll*Sum*Sz[j];
				Sum+=Sz[j];
			}
		}
		else if(L==0)S[i]+=1ll*Sz[R]*(Sz[0]-Sz[RF]);
		else S[i]+=1ll*Sz[L]*Sz[R];
		if(Hav[i])continue;
		if(!In(L,i)&&!In(R,i))return;
		if(In(R,i))
		{
			while(R!=i)
			{
				for(int j:G[R])
				{
					if(Dfn[j]>Dfn[R]&&In(j,i))
					{
						if(R==0)RF=j;
						R=j,Hav[j]=1;
						break;
					}
				}
			}
			continue;
		}
		if(In(L,i))
		{
			while(L!=i)
			{
				for(int j:G[L])
				{
					if(Dfn[j]>Dfn[L]&&In(j,i))
					{
						if(L==0&&j==RF)return;
						L=j,Hav[j]=1;
						break;
					}
				}
			}
		}
	}
}
```

---

## 作者：SunsetLake (赞：2)

## 思路

如果一条路径的 $\text {mex} = k$，那么 $0 \sim k-1$ 这些点一定在路径中出现过，并且一定在一条链上。如果不在一条链上，那么就不满足简单路径这一条件了。因此我们在从小到大加点的过程中如果发现一个点不在已求出的链上，那么比这个点编号大的 $k$ 答案一定都是 $0$ 了，因为不能同时把 $0 \sim k-1$ 都一起走一遍，$\text {mex}$ 也就一定 $< k$ 了。

知道这个以后我们就得到了一个大致思路：从小到大枚举 $\text {mex}$ 值 $k$，同时维护一条链的左、右端点，$k$ 的答案就是包含已求出的链并且不包含 $k$ 的所有路径数量。求完答案再判断当前点 $k$ 是否能与 $0 \sim k-1$ 继续构成一条链。如果能，那就更新链的左右端点，否则直接退出，其余输出 $0$ 即可。

那么，如何判断 $k$ 这个点在不在已求出的链上呢？我们可以暴力跳父亲，跳的时候同时打标记，这样就保证了每个点只会经过一次，时间为 $\mathcal {O(n)}$。如果 $k$ 向上跳到的第一个被打了标记的点是 $l$ 或者 $r$，那么从这两个端点延伸一定能到 $k$，$k$ 也就一定能在链上。此时就可以继续更新了。

做完这步，还有一个问题就是：如何求满足条件的路径数量？可以先从 $0$ 开始，$\text {mex}=0$ 的路径数量就是不经过 $0$ 的所有路径条数。可以树形 dp 解决，设 $f_u$ 表示以 $u$ 为根的子树中所有路径的数量，$g_u$ 表示以 $u$ 为根的子树中**不经过** $u$ 的所有路径条数。那么 $g_u=\displaystyle\sum_{v \in son_u}f_v$，$f_u=g_u+size_u-1+\dfrac{\displaystyle\sum_{v \in son_u}size_v \displaystyle\sum_{p\in son_u,p \ne v}size_p}{2} $。$f_u$ 的转移可以看成三部分：

1. 所有的 $f_v$。
1. 以 $u$ 的子树中的任意一点为起点，$u$ 为终点的路径。即 $size_u-1$。
1. $u$ 的两两儿子之间跨过 $u$ 点相连的所有路径。那就是所有的 $size_v \times size_p$，除以 $2$ 是因为会算重。

这样我们就求出了 $\text {mex}=0$ 的答案，为 $g_0$。因为链有两个端点，所以还要把 $1$ 的答案求出来。对于 $1$，与一开始说的做法一样，跳父亲跳到 $0$，这时就已经有了链的雏形。那么，答案就是经过 $0$ 且不经过 $1$ 的路径条数，于是容斥一下，用所有经过 $0$ 的路径减去既经过 $1$ 又经过 $0$ 的路径:$f_0-g_0-size_1*(n-size_{now})$。其中 $now$ 是 $1$ 在向上跳父亲时跳到的 $0$ 的直连儿子。画下图就能理解了。

于是初始化左端点为 $1$，右端点为 $0$。每次枚举点 $k$，跳到链上后更新答案。怎么算答案？其实跟 $1$ 的计算方式很像，包含以求出的链的路径且不包含 $k$ 的路径条数。假如 $k$ 跳到了 $l$，那么就是 $(size_l-size_k) \times size_r$（可能需要画图理解，有点抽象）。注意有 $l,r$ 可能为 $0$，此时 $size_r,size_l$ 就要减去多的一坨，此题就结束了。

其余细节见注释，赛时写的代码，可能有点丑，见谅。

## code

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int t,n,pp; 
int head[200005],cnt,k,vis[200005];
int ft[200005];
ll sz[200005];
ll f[200005],g[200005];
struct edge{
	int v,nxt;
}e[400005];
void add(int u,int v){
	e[++k].v=v;
	e[k].nxt=head[u];
	head[u]=k;
}
void dfs(int u,int fa){
	ll res=0,sum=0;
	sz[u]=1;
	ft[u]=fa;
	for(int i=head[u];~i;i=e[i].nxt){
		int v=e[i].v;
		if(v==fa)continue;
		dfs(v,u);
		g[u]+=f[v];
		sz[u]+=sz[v];
		res+=sz[v];
		sum+=sz[v]*sz[v];
	}
	res*=res;
	f[u]+=g[u]+sz[u]-1+(res-sum)/2;//计算f[u]
}
void solve(){
	cin>>n;
	k=0;
	for(int i=0;i<=n;++i){
		sz[i]=0;
		head[i]=-1;
		f[i]=g[i]=vis[i]=0;
	}
	for(int i=1;i<n;++i){
		int a,b;
		cin>>a>>b;
		add(a,b);add(b,a);
	}
	dfs(0,-1);
	cout<<g[0]<<" ";
	int now=1;
	vis[0]=1;
	while(ft[now]!=0){//跳1的父亲
		vis[now]=1;
		now=ft[now];
	}
	vis[now]=1;
	pp=now;
	cout<<f[0]-g[0]-sz[1]*(n-sz[now])<<" ";
	int l=1,r=0;//维护链的端点
	bool flag=0;
	int epos=0;
	for(int i=2;i<=n;++i){
		now=i;
		int po=0;
		while((!vis[ft[now]])){//向上跳
			po++;
			vis[now]=1;
			now=ft[now];
		}
		int ffa=ft[now]; 
		if((ffa!=l)&&(ffa!=r)&&(po||(po==0&&(!vis[i])))){//不在链上
			flag=1;
			if(r!=0)cout<<sz[l]*sz[r]<<' ';
			else cout<<sz[l]*(sz[r]-sz[pp])<<" ";
			epos=i+1;
			break;
		}
		if(now==i&&po==0&&vis[i]){//已经在链上了，那就不可能把0~k-1走完，答案为0
			cout<<0<<" ";
			continue;
		}
		vis[now]=1;
		if(ffa==l){//更新左右端点
			if(r!=0)cout<<(sz[l]-sz[i])*sz[r]<<" ";
			else cout<<(sz[l]-sz[i])*(sz[r]-sz[pp])<<' ';
			l=i;
		}
		else{
			if(r!=0)cout<<(sz[r]-sz[i])*sz[l]<<' ';
			else cout<<(sz[r]-sz[pp]-sz[i])*sz[l]<<" ";
			r=i;
		}
		
	}
	if(flag){//不在链上全部输出0
		for(int i=epos;i<=n;++i)cout<<"0 ";
		cout<<endl;
		return;
	}
	cout<<endl;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>t;
	while(t--)solve();
	return 0;
} 
```


---

## 作者：Francais_Drake (赞：1)

对于不经过 $0$ 点的路径，显然其 $\operatorname{mex}$ 值为 $0$ 。

所以我们可以以 $0$ 号点为根结点，则所有 $\operatorname{mex}$ 值大于 $0$ 的路径必须经过根结点，方便将来的计算。

满足 $\operatorname{mex} \geq k$ 的一条最短路径可能由一个或两个非 $0$ 的端点。我们在运算时维护这两个端点，同时维护每个节点的最远非 $0$ 祖先，这样可以方便地由它们推出满足 $\operatorname{mex}\geq k$ 的路径条数（即完全包含这条最短路径的路径条数）：

$$
cnt_k=\begin{cases}
siz_{st}*(n-siz_{bel_1}),& ed=0 \\
siz_{st}*siz_{ed},& \text{otherwise.}
\end{cases}
$$

其中 $siz_k$ 为 $k$ 结点子树大小，$bel_k$ 为 $k$ 结点的深度最小的非 $0$ 祖先，$cnt_k$ 为满足 $\operatorname{mex} \geq k$ 的路径数， $st,ed$ 为此最短路径的非 $0$ 端点。特别地，当此最短路径只有一个非 $0$ 端点时，令 $ed$ 为 $0$ 。

因此，在对一条路径进行拓展（指由 $\operatorname{mex} \geq k$ 的路径条数及其满足的性质推出 $\operatorname{mex} \geq k+1$ 的路径条数的操作）时，可能遇到以下几种情况：

1.  $k$ 结点为 $st$ 结点的祖先或后代。此时若 $k$ 结点的深度大于 $st$ 结点的深度，则将 $st$ 赋为 $k$ 。

2.  $k$ 结点与 $st$ 结点的最近公共祖先非 $0$ 且不满足情况 $1$ ，即 $bel_k = bel_{st} $ 。此时不存在 $\operatorname{mex} \geq k+1$ 的简单路径。

3.  $k$ 结点为 $ed$ 结点的祖先或后代且不满足情况 $1,2$ （包括 $ed=0$ 的情况）。处理方式与情况 $1$ 方式类似。

4.  不满足情况 $1,2,3$ 。此时同样不存在 $\operatorname{mex} \geq k+1$ 的简单路径。

对于某结点是否为另一结点的祖先或后代，我们有 $O(n)$ 预处理， $O(1)$ 查询的在线做法。

考虑利用一棵树的 dfn 序。对于一个结点 $i$ ，它的子树的 dfn 序一定是以此结点 dfn 序为首的一段长为 $siz_i-1$ 连续序列。故而判断某结点是否为另一结点的后代，只需看它的 dfn 序是否在另一结点的子树 dfn 序列中即可，是否为另一结点的祖先则反之。故而只需在 dfs 求深度和子树大小时，顺便求其 dfn 序即可。

核心代码：

```cpp

void dfs(const int &p){
	siz[p]=1;
	dfn[p]=++tim;
	int lp,to;
	for(lp=h[p];lp;lp=E[lp].nxt){
		to=E[lp].to;if(siz[to]) continue;
		dep[to]=dep[p]+1;bel[to]=u;
		dfs(to);siz[p]+=siz[to];
	}
	End[p]=tim;//此处为了方便，可以直接记录此节点的子树对应的 dfn 序列的左右端点
}
#define in(x,y) ((dfn[x]<dfn[y])&&(End[x]>=dfn[y]))
#define rel(x,y) ((in(x,y))||(in(y,x)))

//main函数中：
dep[0]=1;siz[0]=End[0]=n;dfn[0]=tim=1;
for(i=h[0];i;i=E[i].nxt){
	u=E[i].to;bel[u]=u;
	dep[u]=2;dfs(u);
	all+=s*siz[u];
	s+=siz[u];
}
cnt[0]=((n-1ll)*n)>>1LL;
cnt[1]=all;cnt[2]=siz[1]*(n-siz[bel[1]]);
st=1;ed=0;
eds=n-siz[bel[1]];
for(i=2;i<n;++i){
	if(rel(i,st)){if(dep[st]<dep[i]) st=i;}
	else if(bel[i]==bel[1]) break;
	else if(rel(i,ed)){if(dep[ed]<dep[i]) ed=i;}
	else break;
	if(ed) cnt[i+1]=siz[st]*siz[ed];
	else cnt[i+1]=siz[st]*eds;
}
for(i=0;i<=n;++i) printf("%lld ",cnt[i]-cnt[i+1]);
```


---

