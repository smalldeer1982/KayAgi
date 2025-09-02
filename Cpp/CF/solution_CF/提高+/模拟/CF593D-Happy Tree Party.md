# Happy Tree Party

## 题目描述

为了庆祝博格丹的生日，他的母亲送给他一棵有$n$个节点的树，树的第$i$条边上写了一个数字$x_i$。顺带提醒一下，一棵树指的是一个由无向边连接的无环连通图。在礼物被送出之后，有$m$位访客陆续来到博格丹家中参加派对。第$i$位访客会进行如下两种操作其中之一：

>1.选择一个数$y_i$和两个节点$a_i$、$b_i$。在这之后，他会沿着树的边走一遍从$a_i$到$b_i$的最短路（当然，在树上这样的路径只有一条）。每当他经过一条边$j$时，他选择的数$y_i$会立刻变成$\lfloor \frac{y_i}{x_j} \rfloor$，也就是$\frac{y_i}{x_i}$向下取整。
>
>2.选择第$j$条边$p_j$，把它的边权$x_{p_i}$改成一个正整数$c_i \in [1,x_{p_i}]$。

由于博格丹很替他的客人们着想，他决定简化这个过程。你需要写一个程序处理访客们的操作，并且对于每一个第一种操作$i$，输出$y_i$最后的值。

## 样例 #1

### 输入

```
6 6
1 2 1
1 3 7
1 4 4
2 5 5
2 6 2
1 4 6 17
2 3 2
1 4 6 17
1 5 5 20
2 4 1
1 5 1 3
```

### 输出

```
2
4
20
3
```

## 样例 #2

### 输入

```
5 4
1 2 7
1 3 3
3 4 2
3 5 5
1 4 2 100
1 5 4 1
2 2 2
1 1 3 4
```

### 输出

```
2
0
2
```

# 题解

## 作者：LordLeft (赞：9)

看到这个题目，由于不是很会树链剖分、LCT等高级算法，于是考虑用LCA做这个题目

思路很简单，对于每一次查询，直接找到两点的LCA，由于边权很大而且要动态改边，所以两个点要一步一步跳到LCA，在这个过程中将$V$除以经过的边权，改边的话直接对链式前向星进行修改

然后就妥妥的TLE了。。。

此时仔细观察题面，可以发现一些有趣的性质：

虽然边权范围给的很大，但是初始值也只有$10^{18}$这么大，也就是一次查询最多经过边权大于1的边$log_2 10^{18} \approx 60$ 次

这样的话，就可以想到用并查集优化这个做法：把边权为1的边的目标节点记入它父亲节点的并查集，然后查询时两个点往LCA跳的过程中稍作修改，并且当$V$变成0时直接跳出，那么每次至多跳60次，而且往往会比60小很多，这样就可以用LCA的做法AC本题

具体细节见代码
```cpp
#include<iostream>
#include<cstdio>
#include<cctype>
#define E puts("E?")
#define ll long long
using namespace std;
inline ll read(){
    ll w=0,s=1;
    char c=getchar();
    while(!isdigit(c)){
        s=(c=='-')?-1:1;
        c=getchar();
        }
    while(isdigit(c)){
        w=(w<<3)+(w<<1)+c-'0';
        c=getchar();
        }
    return w*s;	
    }
const int N=200005;
ll pre[N],cnt;
struct Edge{
    ll nxt,to,wei,from;//链式前向星多记录一个from方便改边权
    };
Edge edge[N<<1];
void add_for(ll u,ll v,ll w){
    edge[++cnt].nxt=pre[u];
    edge[cnt].to=v;
    edge[cnt].wei=w;
    edge[cnt].from=u;
    pre[u]=cnt;
    }
ll f[N][21],dep[N],fa[N],va[N];
ll find(ll x){
    return fa[x]==x?x:fa[x]=find(fa[x]);//并查集
    }
void search(ll u,ll grt){
    f[u][0]=grt;
    dep[u]=dep[grt]+1;
    for(ll i=1;i<=17;i++){
        f[u][i]=f[f[u][i-1]][i-1];
        }
    for(ll i=pre[u];i>0;i=edge[i].nxt){
        ll v=edge[i].to,w=edge[i].wei;
        if(v!=grt){
            if(w==1){
                fa[v]=find(u);//在做LCA初始化的时候，遇到边权为1的边就可以把目标节点合并到父亲节点了
                }
            va[v]=w;//并查集的权值	
            search(v,u);
            }
        }
    }
ll LCA(ll u,ll v){
    if(dep[u]<dep[v]){
        swap(u,v);
        }
    for(ll i=17;i>=0;i--){
        if(dep[f[u][i]]>=dep[v]){
            u=f[u][i];
            }
        if(u==v){
            return u;
            }	
        }
    for(ll i=17;i>=0;i--){
        if(f[u][i]!=f[v][i]){
            u=f[u][i];
            v=f[v][i];
            }
        }
    return f[u][0];	
    }	
ll n,q;	
int main(){
    n=read();
    q=read();
    ll u,v,w;
    for(ll i=1;i<n;i++){
        u=read();
        v=read();
        w=read();
        add_for(u,v,w);
        add_for(v,u,w);//无向图连两条边
        }
    for(ll i=1;i<=n;i++){
        fa[i]=i;//并查集初始化
        }	
    search(1,0);	
    ll opt,x,y,z;
    for(ll p=1;p<=q;p++){
        opt=read();
        if(opt==1){//查询操作
            x=read();
            y=read();
            z=read();
            ll anc=LCA(x,y),a=x,b=y;
            while(dep[a]>dep[anc]&&z){//"&&z"就是当v为0时可以不用再跳了
                if(va[a]){	
                    z/=va[a];
                    }
                a=find(f[a][0]);//借助并查集，每次上跳不是简单的跳到父亲，而是父亲所在并查集的祖先（？）	
                }
            while(dep[b]>dep[anc]&&z){
                if(va[b]){
                    z/=va[b];
                    }
                b=find(f[b][0]);	
                }	
            printf("%lld\n",z);		
            }
        else{//修改操作
            x=read();
            y=read();
            ll u=edge[x<<1].from,v=edge[x<<1].to;
            if(f[u][0]==v){
                z=u;//由于我们做并查集的时候是把儿子并入父亲，所以改边时要看from和to哪个在树上是父亲
                }
            else{
                z=v;
                }	
            va[z]=y;
            if(va[z]==1){
                fa[z]=find(f[z][0]);//边权为1就合并
                }
            }	
        }
    return 0;
    }
```
GL~

---

## 作者：zjh111111 (赞：8)

[$problem$ $link$](https://www.luogu.com.cn/problem/CF593D)

### 【题意】

给出**一棵树**，要求支持两个操作：

①从一个点出发，走到另一个点，给出一个初始值，依次除以路径上的边权结果下取整，输出最后的值。

②修改某一条边的边权，保证修改后的边权**比修改前的小**，且边权**永远不会出现零**。

### 【算法】

- 考虑除法，除以一个非一的数字，**变成零所需要的次数必定是log级别的**；所以，暴力整除，如果结果变为零直接跳出即可。

- 可是，可能有很多边的边权是一，这就对效率产生了影响。

- 考虑到一旦一条边边权变为了一，就不会再改变，可以用**并查集和倍增LCA**维护这些边权为一的边。

**参考@[LordLeft](https://www.luogu.com.cn/user/178864) 题解的思路。**


但是感觉他的代码因为一开始没有预处理并查集，只在修改时更新会被卡。

卡点：从节点1出发的两条链，都是查询，无修改。会被卡成$\mathcal{O(qn)}$

$\operatorname{CF}$ 数据不会那么水吧$...$

所以我来补一发预处理的代码。$($ 其余部分和 LordLeft 的大同小异。

```cpp
struct node {
	int dep, id;
	inline bool operator < (const mode & a) const {
		return dep < a.dep;
	}
} q[N];

inline void merge() {
	for (register int i=1; i<=n; ++i)
		if (va[i] == 1) { //va是边权，存在儿子那
			q[++ cnt].dep = dep[i]; q[cnt].id = i;
		}
   //这里不直接做的原因是
   边权为1的边可能不按深度由小到大给出，直接合并会出锅
	std :: sort(q + 1, q + cnt + 1); //按照深度排序
	for (register int k=1; k<=cnt; ++k) {
		int i = q[k].id;
		f[i] = find(fa[i][0]);
        //f[i]一开始=i，这个父亲相当于一个指针，不要和树上父亲混起来
        //fa[i][0]是i的树上父亲。
	}
}
```





---

## 作者：ACAね (赞：4)

### 方法一 

#### 使用Link-Cut_Tree,动态维护区间乘积 $O(nlogn)$

除板子之外，要注意一下，（你不管，直接用long double也可以）

要判断两个数如果一开始爆了1e18就不用记了，记个-1的标记

如何判断爆了呢qwq
```cpp
const long long MAX=1e18;
inline bool safe(long long a,long long b){return MAX/b>=a;}
```
就这样

这样还有个优势，就是如果两个数有一个是-1,一定会返回true

或者运用log,但是log比较慢，所以建议上面一种
```cpp
inline bool safe(long long a,long long b){return log(a)+log(b)<=log(MAX);}
```
我LCT写的比较丑，常数比较大qwq,

一个log被两个的树链剖分爆踩qwq
```cpp
/*
@Date    : 2019-07-09 13:18:57
@Author  : Adscn (adscn@qq.com)
@Link    : https://www.cnblogs.com/LLCSBlog
*/
#define FASTER
#ifdef FASTER
#pragma GCC diagnostic error "-std=c++11"
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#endif
#include<bits/stdc++.h>
using namespace std;
#define IL inline
#define RG register
#define gi getint()
#define gl getlong()
#define gc getchar()
#define File(a) 
freopen(a".in","r",stdin);freopen(a".out","w",stdout)
#define int long long
IL int getint()
{
	RG int xi=0;
	RG char ch=gc;
	bool f=0;
	while(ch<'0'|ch>'9')ch=='-'?f=1:f,ch=gc;
	while(ch>='0'&ch<='9')xi=(xi<<1)+(xi<<3)+ch-48,ch=gc;
	return f?-xi:xi;
}
IL long long getlong()
{
	RG long long xi=0;
	RG char ch=gc;
	bool f=0;
	while(ch<'0'|ch>'9')ch=='-'?f=1:f,ch=gc;
	while(ch>='0'&ch<='9')xi=(xi<<1)+(xi<<3)+ch-48,ch=gc;
	return f?-xi:xi;
}
template<typename T>
IL void pi(T k,char ch=0)
{
	if(k<0)k=-k,putchar('-');
	if(k>=10)pi(k/10,0);
	putchar(k%10+'0');
	if(ch)putchar(ch);
}
IL unsigned int LOG2(unsigned int x)
{
	unsigned int ret;
	__asm__ __volatile__ ("bsrl %1, %%eax":"=a"(ret):"m"(x));
	return ret;
}
const int N=1e5+7;
namespace LCT{
	int f[N<<1],c[N<<1][2],rev[N<<1];
	long long ret[N<<1],val[N<<1];
	const long long MAX=1e18;
	#define ls(x) (c[(x)][0])
	#define rs(x) (c[(x)][1])
	#define s(x,k) (c[(x)][(k)])
	inline bool ws(register int x,register int p){return ls(p)^x;}
	inline int nroot(register int x){return ls(f[x])==x||rs(f[x])==x;}
	inline bool safe(long long a,long long b){return MAX/a>=b;}
	inline void pushr(int x){if(x)swap(ls(x),rs(x)),rev[x]^=1;}
	inline void pushdown(int x)
	{
		if(!rev[x])return;
		pushr(ls(x)),pushr(rs(x));
		rev[x]=0;
	}
	inline void pushall(int x){if(nroot(x))pushall(f[x]);pushdown(x);}
	inline void pushup(int x){
		ret[x]=-1;
		if(safe(ret[ls(x)],ret[rs(x)])&&
			safe(ret[ls(x)]*ret[rs(x)],val[x]))ret[x]=ret[ls(x)]*ret[rs(x)]*val[x];
	}
	inline void rotate(int x)
	{
		register int p=f[x],g=f[p];
		register int t=ws(x,p),w=s(x,!t);
		if(nroot(p))s(g,ws(p,g))=x;s(x,!t)=p;s(p,t)=w;
		if(w)f[w]=p;f[p]=x;f[x]=g;
		pushup(p);
	}
	inline void Splay(int x)
	{
		pushall(x);
		while(nroot(x))
		{
			register int p=f[x],g=f[p];
			if(nroot(p))rotate(ws(x,p)^ws(p,g)?x:p);
			rotate(x);
		}
		pushup(x);
	}
	inline void access(register int x){for(register int y=0;x;x=f[y=x])Splay(x),rs(x)=y,pushup(x);}
	inline void makert(int x){access(x),Splay(x),pushr(x);}
	inline void Split(int x,int y){makert(x),access(y),Splay(y);}
	inline void link(int x,int y){makert(x);f[x]=y;}
	inline void modify(int x,int value)
	{
		makert(x);
		val[x]=value;
		pushup(x);
	}
	inline long long ask(int x,int y)
	{
		Split(x,y);
		return ret[y];
	}
	int main()
	{
		int n=gi,q=gi;
		fill(val,val+n+n+1,1);
		fill(ret,ret+n+n+1,1);
		for(int i=1;i<n;++i)
		{
			int u=gi,v=gi;
			val[i+N]=gl;
			link(u,i+N),link(i+N,v);
		}
		for(int i=1;i<=q;++i)
		{
			int type=gi;
			if(type==1)
			{
				int u=gi,v=gi;
				long long P=gl;
				long long V=ask(u,v);
				if(~V)pi(P/V,'\n');
				else pi(0,'\n');
			}
			else 
			{
				int u=gi;
				modify(u+N,gl);
			}
		}
		return 0;
	}
}
signed main()
{
	return LCT::main();
}
```

### 方法二

#### 暴力优化 $O(nlog(maxnum))$

注意到1e18大约等于$2^{60}$

所以最多经过60条边权大于1的边

所以对于每一个边权1的边用并查集连一下

不是1的就暴跳，爆了就退出就可以了qwq

然而还是吊打LCTqwq

代码仅供参考思路，不一定正确
```cpp
/*
@Date    : 2019-07-09 13:18:57
@Author  : Adscn (adscn@qq.com)
@Link    : https://www.cnblogs.com/LLCSBlog
*/
#ifdef FASTER
#pragma GCC diagnostic error "-std=c++11"
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#endif
#include<bits/stdc++.h>
using namespace std;
#define IL inline
#define RG register
#define gi getint()
#define gl getlong()
#define gc getchar()
#define File(a) freopen(a".in","r",stdin);freopen(a".out","w",stdout)
IL int getint()
{
	RG int xi=0;
	RG char ch=gc;
	bool f=0;
	while(ch<'0'|ch>'9')ch=='-'?f=1:f,ch=gc;
	while(ch>='0'&ch<='9')xi=(xi<<1)+(xi<<3)+ch-48,ch=gc;
	return f?-xi:xi;
}
IL long long getlong()
{
	RG long long xi=0;
	RG char ch=gc;
	bool f=0;
	while(ch<'0'|ch>'9')ch=='-'?f=1:f,ch=gc;
	while(ch>='0'&ch<='9')xi=(xi<<1)+(xi<<3)+ch-48,ch=gc;
	return f?-xi:xi;
}
template<typename T>
IL void pi(T k,char ch=0)
{
	if(k<0)k=-k,putchar('-');
	if(k>=10)pi(k/10,0);
	putchar(k%10+'0');
	if(ch)putchar(ch);
}
IL unsigned int LOG2(unsigned int x)
{
	unsigned int ret;
	__asm__ __volatile__ ("bsrl %1, %%eax":"=a"(ret):"m"(x));
	return ret;
}
const int N=2e5+7;
namespace BF{
	int fa[N],dep[N];
	typedef long long ll;
	inline int find(int x){return fa[x]==x?x:(fa[x]=find(fa[x]));}
	inline void link(int x,int y){fa[find(x)]=find(y);}	
	inline bool safe(ll a,ll b){if(a==0||b==0)return 1;return 1e18/b>=a;}
	struct edge{
		int v,nxt;long long w;
	}e[N<<1];
	int head[N],cnt;
	inline void add(int u,int v,long long w)
	{
		e[++cnt]=(edge){v,head[u],w};
		head[u]=cnt;
	}
	int f[N][17];
   long long val[N];
	void dfs(int x,int p)
	{
		f[x][0]=p,dep[x]=dep[p]+1;
		for(int i=1;i<=16;++i)f[x][i]=f[f[x][i-1]][i-1];
		for(int i=head[x];i;i=e[i].nxt)
		{
			int v=e[i].v;
			if(v==p)continue;
			if(e[i].w==1)link(v,x);
			dfs(v,x);
			val[v]=e[i].w;
		}
	}
	inline int LCA(int u,int v)
	{
		if(dep[u]<dep[v])swap(u,v);
		for(int i=16;i>=0;--i)if(dep[f[u][i]]>=dep[v])u=f[u][i];
		if(u==v)return u;
		for(int i=16;i>=0;--i)if(f[u][i]!=f[v][i])u=f[u][i],v=f[v][i];
		return f[u][0];
	}
	int U[N],V[N];
	int main(void)
	{
		int n=gi,q=gi;
		for(int i=1;i<=n;++i)fa[i]=i;
		for(int i=1;i<n;++i)
		{
			int u=gi,v=gi;long long c=gl;
			add(u,v,c);
			U[i]=u,V[i]=v;
		}
		dfs(1,0);
		for(int i=1;i<=q;++i)
		{
			int type=gi;
			if(type==1)
			{
				int u=gi,v=gi;long long P=gl;
				int lca=LCA(u,v);
				long long sum=1;
				while(dep[u]>dep[lca])
				{
					if(find(u)!=u)u=find(u);
					else sum=safe(sum,val[u])*sum*val[u],u=f[u][0];
				}
				if(sum==0){printf("0\n");continue;}
				while(dep[v]>dep[lca])
				{
					if(find(v)!=v)v=find(v);
					else sum=safe(sum,val[v])*sum*val[v],v=f[v][0];
				}
				if(sum)cout<<P/sum<<endl;
				else cout<<0<<endl;
			}
			else {
				int k=gi;long long w=gi;
				int u=U[k],v=V[k];
				if(dep[u]<dep[v])swap(u,v);
				val[u]=w;
				if(w==1)link(u,v);
			}
		}
		return 0;
	}
}
int main()
{
	return BF::main();
}
```
### 3.树链剖分 $O(nlog^2n)$
主要思路同LCT,

但是仍然吊打LCT了qwq

详见下面大佬题解

---

## 作者：qiyue7 (赞：3)

树链剖分+线段树   单点修改+区间连乘（连除等于连乘的倒数）

注意到乘积有可能爆long long 还有double可能会卡精度，所以选择long double

（常数大了一点但是还是过了）

AC代码：
```cpp
#include <iostream>
#include<vector>
#include<cstring>
#include<list>
#include<set>
#include<queue>
#include<map>
#include<stack>
#include<algorithm>
using namespace std;
#define int long long
const int N = 222000;
const double MAXN = 10e19;
#define double long double
struct node2
{
    node2 *L, *R;
    int l, r;
    double val;
};
void update(node2 *p)
{
    if (p->l == p->r)
        return;
    double k = p->L->val * p->R->val;
    if (k > MAXN)
        p->val = 0;
    else
        p->val = k;
}
void pl(node2 *a)
{
    if ((a->L != NULL) || (a->l == a->r))
        return;
    int mid = (a->l + a->r) / 2;
    a->L = new node2();
    a->L->l = a->l, a->L->r = mid, a->L->val = 0;
}
void pr(node2 *a)
{
    if ((a->R != NULL) || (a->l == a->r))
        return;
    int mid = (a->l + a->r) / 2;
    a->R = new node2();
    a->R->l = mid + 1, a->R->r = a->r, a->R->val = 0;
}
void build(int *p, node2 *x)
{
    pl(x), pr(x);
    if (x->l == x->r)
    {
        x->val = p[x->l];
        return;
    }
    else
        build(p, x->L), build(p, x->R);
    update(x);
}
void split(node2 *p, int l, int r,double w)
{
    if (p->l == l && p->r == r)
    {
        p->val = w;
        return;
    }
    int mid = (p->l + p->r) / 2;
    if (l <= mid && r > mid)
        split(p->L, l, mid,w), split(p->R, mid + 1, r,w);
    else if (r <= mid)
        split(p->L, l, r,w);
    else if (l >= mid + 1)
        split(p->R, l, r,w);
    update(p);
}
double query_sum(node2 *x, int L, int R) 
{
    double sum = 0;
    int mid = (x->l + x->r) / 2;
    if (x->l == L && x->r == R)
        return x->val;
    else
    {
        if (L <= mid && R > mid)
        {
            sum = query_sum(x->L, L, mid) * query_sum(x->R, mid + 1, R);
            if (sum < MAXN)
                return sum;
            else
                return 0;
        }
        else if (R <= mid)
            return query_sum(x->L, L, R);
        else if (L >= mid + 1)
            return query_sum(x->R, L, R);
    }
}
namespace tree_split1
{
    struct graph
    {
        long long Begin[N * 2], to[N * 2], Next[N * 2], e, weight[N * 2];
        void add(int u, int v)
        {
            to[++e] = v;
            Next[e] = Begin[u];
            Begin[u] = e;
        }
        void add(int u, int v, int w)
        {
            to[++e] = v;
            Next[e] = Begin[u];
            Begin[u] = e;
            weight[e] = w;
        }
        void init_graph()
        {
            e = 0;
            memset(Begin, -1, sizeof(Begin));
        }
    };
    int id[N];
    class tree_split
    {
    public:
        long long dep[N], fa[N], top[N], size1[N], son[N], weight[N], new_weight[N];
        int len;
        graph g;
        double query2(node2 *p, int x, int y)
        {
            double ans = 1;
            while (top[x] != top[y])
            {
                if (dep[top[x]] < dep[top[y]]) swap(x, y);
                ans *= query_sum(p,id[top[x]], id[x]);
                x = fa[top[x]];
            }
            if (dep[x] > dep[y]) swap(x, y);
            if(id[x]!=id[y])
            ans *= query_sum(p,id[x]+1, id[y]);
            return ans;
        }
        tree_split()
        {
            memset(fa, 0, sizeof(fa));
            memset(top, 0, sizeof(top));
            memset(size1, 0, sizeof(size1));
            memset(son, 0, sizeof(son));
            memset(g.Begin, -1, sizeof(g.Begin));
            memset(weight, 0, sizeof(weight));
            len = 0;
        }
        void init(int root)
        {
            dep[root] = 0;
            dfs1(root, root);
            dfs2(root, root);
        }
        void add_weight(int i, int w)
        {
            weight[i] = w;
        }
        void add_edge(int u, int v,double w)
        {
            g.add(u, v,w);
            g.add(v, u,w);
        }
        void dfs1(int u, int father)
        {
            dep[u] = dep[father] + 1;
            fa[u] = father;
            size1[u] = 1;
            for (int i = g.Begin[u]; i != -1; i = g.Next[i])
            {
                if (g.to[i] != father)
                {
                    weight[g.to[i]] = g.weight[i];
                    dfs1(g.to[i], u);
                    size1[u] += size1[g.to[i]];
                    if (size1[g.to[i]] > size1[son[u]])
                        son[u] = g.to[i];
                }
            }
        }
        void dfs2(int u, int topf)
        {
            id[u] = ++len;
            new_weight[len] = weight[u];
            top[u] = topf;
            if (son[u] == 0)return;
            dfs2(son[u], topf);
            for (int i = g.Begin[u]; i != -1; i = g.Next[i])
            {
                if (g.to[i] == fa[u] || g.to[i] == son[u]) continue;
                dfs2(g.to[i], g.to[i]);
            }
        }
        int find(int u)
        {
            return top[u] = top[u] == u ? u : find(top[u]);
        }
        int LCA(int u, int v) {
            if (find(u) != find(v))
                return dep[top[u]] > dep[top[v]] ? LCA(fa[top[u]], v) : LCA(u, fa[top[v]]);
            else return dep[u] > dep[v] ? v : u;
        }
    }tp;
}
using namespace tree_split1;
pair<int,int> cnt[210000];
int32_t main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);
    int n, m,op,a,b,p,c,w;
    double y;
    node2* tree = new node2();
    tree->l = 1;
    cin >> n >> m;
    tree->r = n;
    for (int i = 1; i <= n - 1; ++i)
    {
        cin >> a >> b >> w;
        cnt[i].first=a,cnt[i].second=b;
        tp.add_edge(a, b,w);
    }
    tp.init(1);
    build(tp.new_weight, tree);
    while (m--)
    {
        cin >> op;
        if (op == 1)
        {
            cin >> a >> b >> y;
            double L = tp.query2(tree, a, b);
            if (L == 0)
                cout << 0 << '\n';
            else
                cout << (int)(y / L) << '\n';
        }
        else
        {
            cin >> p >> c;
            int kk;
            if (tp.dep[cnt[p].first] > tp.dep[cnt[p].second])
                kk = cnt[p].first;
            else
                kk = cnt[p].second;
            split(tree, id[kk], id[kk], c);
        }
    }
    return 0;
}
```


---

## 作者：Warriors_Cat (赞：2)

算是树剖的板子题了，不过偶尔锻炼一下码力也好。

### $Solution:$

首先我们需要知道一个东西：

$$\forall a, b, c\in\mathbb{Z}, \left\lfloor{\dfrac{\left\lfloor\frac{a}{b}\right\rfloor}{c}}\right\rfloor=\left\lfloor\dfrac{a}{bc}\right\rfloor$$

证明可以直接看 [OI-Wiki](https://oi-wiki.org/math/mobius/) 上的，这里就不多说了。

知道这个后，我们就可以用树剖来维护路径乘积，最后直接一除就完事了。

可这里有个很恶心人的点：$x_i\in[1, 10^{18}]$，如果单纯的乘起来肯定会爆 `long long`。

但这里的 $y_i$ 也在 $[1, 10^{18}]$ 的范围中，所以如果这个路径积 $\ge 10^{18}$ 其实答案就为 $0$ 了，也就说明不需要统计了。于是我们可以在当乘积超过 $10^{18}$ 时直接令乘积为一个 $> 10^{18}$ 的数。最后直接一除就为 $0$ 了。

`long long` 乘 `long long` 会炸？用 `long double` 呗~

于是这题就做完了，时间复杂度为 $O(m\log^2 n)$。

如果不会树剖的话建议先去模板区学一下。

### $Code:$

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#include <vector>
#include <cmath>
#include <map>
using namespace std;
#define int long long
#define pd printf("ok\n")
#define x1 x_csyakioi_1
#define x2 x_csyakioi_2
#define y1 y_csyakioi_1
#define y2 y_csyakioi_2
#define y0 y_csyakioi_0
#define dingyi int mid = l + r >> 1, ls = p << 1, rs = p << 1 | 1
inline int read(){
	int x = 0, f = 1; char ch = getchar();
	while(ch < '0' || ch > '9'){ if(ch == '-') f = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9'){ x = x * 10 + (ch ^ 48); ch = getchar(); }
	return x * f;
}
const int N = 200010;
struct edge{
	int v, w, nxt;
}e[N << 1];
int head[N], cnt, n, m, opt, x, y, z, U[N], V[N], W[N], dep[N], siz[N], fa[N], top[N], son[N], seg[N], rev[N], a[N], d[N << 2];
inline void Add(int u, int v, int w){
	e[++cnt].v = v;
	e[cnt].w = w;
	e[cnt].nxt = head[u];
	head[u] = cnt;
}
inline void dfs1(int u, int f){
	dep[u] = dep[f] + 1;
	fa[u] = f;
	siz[u] = 1;
	for(int i = head[u]; i; i = e[i].nxt){
		int v = e[i].v;
		if(v == f) continue;
		a[v] = e[i].w;
		dfs1(v, u);
		siz[u] += siz[v];
		if(siz[v] > siz[son[u]]) son[u] = v;
	}
}
inline void dfs2(int u, int f){
	seg[u] = ++seg[0]; rev[seg[u]] = a[u];
	top[u] = f;
	if(!son[u]) return;
	dfs2(son[u], f);
	for(int i = head[u]; i; i = e[i].nxt){
		int v = e[i].v;
		if(v == fa[u] || v == son[u]) continue;
		dfs2(v, v);
	}
}//以上为预处理
inline int add(int x, int y){
	if((long double)x * (long double)y > 1e18) return 1e18 + 10000;
	return x * y;
}//这里需要注意
inline void pushup(int p){ d[p] = add(d[p << 1], d[p << 1 | 1]); }
inline void build(int p, int l, int r){
	if(l == r){ d[p] = rev[l]; return; }
	dingyi;
	build(ls, l, mid);
	build(rs, mid + 1, r);
	pushup(p);
}
inline void change(int p, int l, int r, int x, int y){
	if(l == r){ d[p] = y; return; } dingyi;
	if(x <= mid) change(ls, l, mid, x, y);
	else change(rs, mid + 1, r, x, y);
	pushup(p);
}
inline int query(int p, int l, int r, int x, int y){
	if(x <= l && r <= y) return d[p]; dingyi; int ans = 1;
	if(x <= mid) ans = add(ans, query(ls, l, mid, x, y));
	if(y > mid) ans = add(ans, query(rs, mid + 1, r, x, y));
	return ans;
}
inline int Query(int x, int y){
	int ans = 1, fx = top[x], fy = top[y];
	while(fx != fy){
		if(dep[fx] < dep[fy]) swap(x, y), swap(fx, fy);
		ans = add(ans, query(1, 1, n, seg[fx], seg[x]));
		x = fa[fx]; fx = top[x];
	}
	if(dep[x] > dep[y]) swap(x, y);
	if(x != y) ans = add(ans, query(1, 1, n, seg[x] + 1, seg[y]));//这里注意特判
	return ans;
}
signed main(){
	n = read(); m = read();
	for(int i = 1; i < n; ++i){
		U[i] = read(); V[i] = read(); W[i] = read();
		Add(U[i], V[i], W[i]); Add(V[i], U[i], W[i]);
	}
	dfs1(1, 0); dfs2(1, 1); build(1, 1, n);
	for(int i = 1; i <= m; ++i){
		opt = read(); x = read(); y = read();
		if(opt == 1){
			z = read();
			int ans = Query(x, y);
			printf("%lld\n", z / ans);
		}
		else{
			int u = U[x], v = V[x];
			if(fa[u] == v) swap(u, v);
			change(1, 1, n, seg[v], y);
		}
	}
	return 0;
}
```

---

## 作者：Naffygo (赞：2)

### 题目大意
有一棵 $n$ 个节点的树，树上的每一条边有一个权值 $x_i$ ，并且有 $m$ 个操作。

- $1$ 操作是给定 $c_i$ ，将 $a_i$ 到 $b_i$路径上的所有边走一遍，每经过一条边 $j$ ，$c_i$ 会变成 $\frac{c_i}{x_j}$向下取整
- $2$ 操作是将第 $j$ 条边的 $x_j$ 修改成 $c_i$

对于每一个操作 $1$ ,输出最后 $c_i$的值。

### 思路
看到题面很显然可以用树剖做，对于 $1$ 操作，一直除 $x_j$ 相当于将所有 $x_j$ 乘起来后再除。所以维护一个区间乘即可；对于 $2$ 操作，就是个单点修改。

但要注意的是可能乘积可能会超过 $10^{18}$ ，显然乘积超过 $10^{18}$ 会使得 $c_i$ 变成0，所以强行变成 $10^{18}$。为了防止精度误差还要开 $long $ $double$ ，线段树空间一定要开 $4$ 倍 ~~（我就是这里挂了然后疯狂 DEBUG ）~~。之后树剖就很容易解决了。


```cpp
#include<bits/stdc++.h>
#define fr(i,a,b) for(register int i = a;i <= b;++i)
#define int long long
#define double long double
#define ls k << 1
#define rs k << 1 | 1
#define N 200010
using namespace std;

const double MAX = 1e18;
struct tree{
	int l,r,f;
	double w;
}t[N << 2];
struct edge{
	int to,nxt,w;
}e[N << 2];
int h[N],fa[N],dep[N],top[N],size[N],son[N],id[N],w[N],w2[N];
int tot = 1,cnt;

inline int read(){
	int x = 0,f = 1;char c = getchar();
	while(!isdigit(c)){if(c == '-')f = -1;c = getchar();}
	while(isdigit(c)){x = x * 10 + c - '0';c = getchar();}
	return f * x;
}

inline void add(int x,int y,int z){
	e[++tot] = (edge){y,h[x],z};
	h[x] = tot;
}

inline void dfs1(int x,int f,int deep){
	fa[x] = f;dep[x] = deep + 1;size[x] = 1;
	for(register int i = h[x];i;i = e[i].nxt){
		int p = e[i].to;
		if(p != f){
			w[p] = e[i].w;
			dfs1(p,x,deep + 1);
			size[x] += size[p];
			if(size[p] > size[son[x]])son[x] = p;
		}
	}
}

inline void dfs2(int x,int t){
	top[x] = t;id[x] = ++cnt;w2[cnt] = w[x];
	if(!son[x])return;
	dfs2(son[x],t);
	for(register int i = h[x];i;i = e[i].nxt){
		int p = e[i].to;
		if(p != son[x] && p != fa[x])dfs2(p,p);
	}
}

inline double mul(double x,double y){if(!x && MAX / y >= x)return MAX;return x * y;}
inline void pushup(int k){t[k].w = mul(t[ls].w,t[rs].w);}

inline void build(int k,int l,int r){
	t[k].l = l;t[k].r = r;
	if(l == r){t[k].w = w2[l];return;}
	int mid = (l + r) >> 1;
	build(ls,l,mid);build(rs,mid + 1,r);
	pushup(k);
}

inline void update(int k,int x,int y){
	if(t[k].l == t[k].r){t[k].w = y;return;}
	int mid = (t[k].l + t[k].r) >> 1;
	if(x <= mid)update(ls,x,y);
	else update(rs,x,y);
	pushup(k);
}

inline double query(int k,int x,int y){
	if(t[k].l >= x && t[k].r <= y)return t[k].w;
	int mid = (t[k].l + t[k].r) >> 1;double tmp = 1;
	if(x <= mid)tmp = mul(tmp,query(ls,x,y));
	if(y > mid)tmp = mul(tmp,query(rs,x,y));
	return tmp;
}

inline double querych(int x,int y){
	double tmp = 1;
	while(top[x] != top[y]){
		if(dep[top[x]] < dep[top[y]])swap(x,y);
		tmp = mul(tmp,query(1,id[top[x]],id[x]));
		x = fa[top[x]];
	}
	if(dep[x] > dep[y])swap(x,y);
	tmp = mul(tmp,query(1,id[x] + 1,id[y]));
	return tmp;
}

signed main(){
	int n = read(),m = read();
	fr(i,1,n - 1){
		int x = read(),y = read(),z = read();
		add(x,y,z);add(y,x,z);
	}
	dfs1(1,0,1);dfs2(1,1);build(1,1,n);
	while(m--){
		int opt = read(),x = read(),y = read(),z;
		if(opt == 1){
			z = read();double s = querych(x,y);
			if(!s)printf("0\n");
			else cout<<(int)(z / s)<<endl;
		}
		else{
			int p = e[x << 1].to,q = e[x << 1 | 1].to;
			update(1,id[dep[p] > dep[q] ? p : q],y);
		}
	}
	return 0;
}
```


---

## 作者：2huk (赞：1)

首先 $\left\lfloor \dfrac {\lfloor \frac ab \rfloor}c \right\rfloor = \left\lfloor \dfrac a{bc} \right\rfloor$。所以我们只需要求解路径上所有边的边权乘积，以及支持单点（边）修改。树链剖分套线段树即可。

乘积会很大。而当它超过 `long long` 时除完下取整一定是 $0$。所以标记一下。

---

## 作者：WorldMachine (赞：1)

一眼题。

首先有一个结论：
$$
\left\lfloor\dfrac{\left\lfloor\frac{a}{b}\right\rfloor}{c}\right\rfloor=\left\lfloor\dfrac{a}{bc}\right\rfloor
$$
那么我们只需要用树链剖分维护链上的边权积即可。为了防止溢出，当两个数相乘超过 $10^{18}$ 时特判一下就行了。
```cpp
#include <bits/stdc++.h>
using namespace std;
#define eb emplace_back
typedef long long ll;
const int N = 200005;
int n, m, tot, dfn[N], siz[N], son[N], fa[N], dep[N], top[N], U[N], V[N];
ll val[N], a[N], c[N * 4];
vector<pair<int, ll> > G[N];
void dfs(int u) {
	siz[u] = 1, dep[u] = dep[fa[u]] + 1;
	int mx = 0;
	for (int i = 0, v; i < G[u].size(); i++) {
		v = G[u][i].first;
		if (v == fa[u]) continue;
		fa[v] = u, val[v] = G[u][i].second;
		dfs(v), siz[u] += siz[v];
		if (siz[v] > mx) mx = siz[v], son[u] = v;
	}
}
void dfs(int u, int f) {
	dfn[u] = ++tot, top[u] = f;
	if (son[u]) dfs(son[u], f);
	for (int i = 0, v; i < G[u].size(); i++) {
		v = G[u][i].first;
		if (v != fa[u] && v != son[u]) dfs(v, v);
	}
}
ll merge(ll x, ll y) {
	if (x == -1 || y == -1) return -1;
	if ((long double)x * y > 1e18) return -1;
	return x * y;
}
void build(int p, int l, int r) {
	if (l == r) return void(c[p] = a[l]);
	int mid = l + r >> 1;
	build(p * 2, l, mid), build(p * 2 + 1, mid + 1, r);
	c[p] = merge(c[p * 2], c[p * 2 + 1]);
}
void update(int p, int l, int r, int x, ll d) {
	if (l == r) return void(c[p] = d);
	int mid = l + r >> 1;
	if (x <= mid) update(p * 2, l, mid, x, d);
	else update(p * 2 + 1, mid + 1, r, x, d);
	c[p] = merge(c[p * 2], c[p * 2 + 1]);
}
ll query(int p, int l, int r, int s, int e) {
	if (s <= l && r <= e) return c[p];
	int mid = l + r >> 1;
	ll ans = 1;
	if (s <= mid) ans = merge(ans, query(p * 2, l, mid, s, e));
	if (e > mid) ans = merge(ans, query(p * 2 + 1, mid + 1, r, s, e));
	return ans;
}
ll getmul(int u, int v) {
	ll ans = 1;
	while (top[u] != top[v]) {
		if (dep[top[u]] > dep[top[v]]) {
			ans = merge(ans, query(1, 1, n, dfn[top[u]], dfn[u]));
			u = fa[top[u]];
		} else {
			ans = merge(ans, query(1, 1, n, dfn[top[v]], dfn[v]));
			v = fa[top[v]];
		}
	}
	if (u == v) return ans;
	if (dep[u] > dep[v]) swap(u, v);
	return merge(ans, query(1, 1, n, dfn[u] + 1, dfn[v]));
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> n >> m;
	ll w;
	for (int i = 1; i < n; i++) {
		cin >> U[i] >> V[i] >> w;
		G[U[i]].eb(V[i], w), G[V[i]].eb(U[i], w);
	}
	dfs(1), dfs(1, 1);
	for (int i = 1; i <= n; i++) a[dfn[i]] = val[i];
	a[1] = 1;
	build(1, 1, n);
	int op, x, y;
	ll z;
	while (m--) {
		cin >> op >> x;
		if (op == 1) {
			cin >> y >> z;
			ll k = getmul(x, y);
			cout << (k == -1 ? 0 : z / k) << '\n';
		} else {
			cin >> z;
			update(1, 1, n, dep[U[x]] < dep[V[x]] ? dfn[V[x]] : dfn[U[x]], z);
		}
	}
}
```

---

## 作者：jun头吉吉 (赞：1)

# CF593D 【Happy Tree Party】
[$\large{\color{pink}{My\ Blog}}$](https://chen-jia-liang.gitee.io/blog/2020/09/21/%E9%A2%98%E8%A7%A3-CF593D-%E3%80%90Happy-Tree-Party%E3%80%91/)
## 题意

给出一棵树，$\operatorname{zici}$一下两种操作：

1. 把第$p$条边改成$c$
2. 询问从$a\to b$的简单路径，每次经过一条边$(u_i,v_i,w_i)$，就把$c$变成$\lfloor\dfrac c {w_i} \rfloor$

## 题解
引理（逃

$$\lfloor \dfrac{\lfloor\frac{x}{a}\rfloor}{b}\rfloor=\lfloor\frac x{ab}\rfloor$$

推论：

$$\lfloor\dfrac{\lfloor\frac{\lfloor\frac{x}{a_1}\rfloor}{\dots}\rfloor}{a_n}\rfloor=\lfloor\frac{x}{\prod_{i=1}^na_i}\rfloor$$

于是这题就变成了了一个一眼题（

蒟蒻（没错就是我）：我会用树剖+线段树维护简单路径上的乘积！于是用`long long`存储一段的乘积，快快乐乐地抱灵了。

我们来考虑上述算法存在的问题：

> $2\le n\le200000,1\le m\le200000$

> $1\le u_i,v_i\le n,u_i\ne v_i,1\le x_i \le 10^{18}$

> $1\le p_i\le n-1,1\le y_i\le10^{18}$

$10^{18}$的$200000$次达到了$10^{3600000}$次，怎么可能存的下呀

但是，因为$x_i\le 10^{18}$，因此大于$10^{18}$的数字事实上都是没用的，因为若$\prod a_i>10^{18}$，答案必然是零

于是我们把代码中的`long long`改成`mylong`就可以$\color{green}{\operatorname{Accepted}}$本题了

下面给出`my_long`的具体实现：

```cpp
struct mylong{
	long long num;
	void operator=(long long b){
		num=b;
	}
	mylong operator+(mylong b){
		mylong c;
		if(log10(b.num)+log10(num)>18.1)
			c=2e18;
		else c=b.num*num;
		return c; 
	}
};
```
由于$10^{18}\times10^{18}$还是会爆`long long`这里用`log`来判断：

$$a\times b\le10^{18}$$

$$log_{10}a+log_{10}b\le18$$
## 代码

~~都说到这了代码应该很简单吧~~

```cpp
#include<bits/stdc++.h>
namespace in{
	char buf[1<<21],*p1=buf,*p2=buf;
	inline int getc(){
	    return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++;
	}
	template <typename T>inline void read(T& t){
	    t=0;int f=0;char ch=getc();
	    while (!isdigit(ch)){
	        if(ch=='-')f = 1;
	        ch=getc();
	    }
	    while(isdigit(ch)){
   	    	t=t*10+ch-48;
   	    	ch = getc();
   		}
		if(f)t=-t;
	}
	template <typename T,typename... Args> inline void read(T& t, Args&... args){
	    read(t);read(args...);
	}
}
namespace out{
	char buffer[1<<21];
	int p1=-1;
	const int p2 = (1<<21)-1;
	inline void flush() {
		fwrite(buffer,1,p1+1,stdout),
		p1=-1;
	}
	inline void putc(const char &x) {
		if(p1==p2)flush();
		buffer[++p1]=x;
	}
	template <typename T>void write(T x) {
		static char buf[35];
		static int len=-1;
		if(x>=0){
			do{
    			buf[++len]=x%10+48,x/=10;
    		}while (x);
		}else{
    		putc('-');
			do {
    			buf[++len]=-(x%10)+48,x/=10;
			}while(x);
		}
		while (len>=0)
			putc(buf[len]),--len;
	}
}
using namespace std;
int n,m;
struct mylong{
	long long num;
	void operator=(long long b){
		num=b;
	}
	mylong operator+(mylong b){
		mylong c;
		if(log10(b.num)+log10(num)>18.1)
			c=2e18;
		else c=b.num*num;
		return c; 
	}
};
const int N=200000+100;
template<class A,class B>
struct SGT{
	B a[N];//初始数组 
	struct node{
		int l,r;
		A val;
	}T[N*4];
	B* operator[](const int x){return a+x;}
	void build(int x,int l,int r){
		T[x].l=l,T[x].r=r;
		if(l==r){
			T[x].val=a[l];
			return;
		}
		int mid=l+r>>1;
		build(x<<1,l,mid);
		build(x<<1|1,mid+1,r);
		T[x].val=T[x<<1].val+T[x<<1|1].val;
	}
	void change(int x,int pos,B val){
		if(T[x].r==T[x].l){
			T[x].val=val;
			return;
		}
		int mid=T[x].l+T[x].r>>1;
		if(pos<=mid)change(x<<1,pos,val);
		else change(x<<1|1,pos,val);
		T[x].val=T[x<<1].val+T[x<<1|1].val;
	}
	A query(int x,int l,int r){
		if(l<=T[x].l&&T[x].r<=r)return T[x].val;
		int mid=T[x].l+T[x].r>>1;
		if(r<=mid)
			return query(x<<1,l,r);
		if(l>mid)
			return query(x<<1|1,l,r);
		return query(x<<1,l,r)+query(x<<1|1,l,r);
	}
};
SGT<mylong,long long>T;
vector<int>e[N];
int fath[N];
int deep[N];
int size[N];
int dfn[N];
int top[N];
int cnt;
void dfs1(int u){
	size[u]=1;
	for(auto v:e[u])
		if(v!=fath[u])
			fath[v]=u,
			deep[v]=deep[u]+1,
			dfs1(v),
			size[u]+=size[v];
}
void dfs2(int u){
	if(!fath[u])top[u]=u;
	dfn[u]=++cnt;
	int mx=-1,son;
	for(auto v:e[u])
		if(v!=fath[u])
			if(size[v]>mx)
				mx=size[v],
				son=v;
	if(mx==-1)return;
	top[son]=top[u];dfs2(son);
	for(auto v:e[u])
		if(v!=fath[u]&&v!=son)
			top[v]=v,
			dfs2(v);
}
struct node{int u,v,id;long long w;}E[N];
signed main(){
	in::read(n,m);
	for(int i=1;i<n;i++)
		in::read(E[i].u,E[i].v,E[i].w),
		e[E[i].u].push_back(E[i].v),
		e[E[i].v].push_back(E[i].u);
	dfs1(1);dfs2(1);
	for(int i=1;i<n;i++)
		if(fath[E[i].u]==E[i].v)E[i].id=dfn[E[i].u];
		else E[i].id=dfn[E[i].v];
	for(int i=1;i<n;i++)*T[E[i].id]=E[i].w;
	T.build(1,1,n);
	while(m--){
		int opt,x,y,p;
		long long c;
		in::read(opt);
		if(opt==1){
			in::read(x,y,c);
			mylong ans;ans=1;
            while(top[x] != top[y]){
                if(deep[top[x]]<deep[top[y]]) swap(x, y);
                ans=ans+T.query(1,dfn[top[x]],dfn[x]);
                x=fath[top[x]];
            }
            if(deep[x]>deep[y])swap(x,y);
            if(dfn[x]!=dfn[y])ans=ans+T.query(1,dfn[x]+1,dfn[y]);
            out::write(c/ans.num);
            out::putc('\n');
		}
		else if(opt==2){
			in::read(p,c);
			T.change(1,E[p].id,c);
		}
	}
	out::flush();
	return 0;
}
```

---

## 作者：shiruoyu114514 (赞：0)

有一个性质：$\lfloor \frac{\lfloor \frac{x}{y}\rfloor}{z} \rfloor=\lfloor \frac{x}{yz} \rfloor$。

这样若 $a_i$ 到 $b_i$ 的链积为 $p$，则答案为 $\lfloor \frac{y_i}{p} \rfloor$

看上去就是拿树链剖分就能轻易解决的事情。

但是 ``long long`` 最高只能表示 $10^{18}$，而 $p$ 的最大值有可能到 $10^{3600000}$，看上去不怎么能做。

注意到若 $p > 10^{18} $，则答案一定为 $0$。

那么我们树链剖分维护的时候，在乘积大于 $10^{18}$ 的时候手动将乘积处理为 $0$ 即可。在询问的时候若乘积为 $0$ 则输出 $0$。


```cpp
#include<bits/stdc++.h>

using namespace std;

#define int long long

const int maxn=2e5;

int father[maxn+5];
int sze[maxn+5];
int deep[maxn+5];
int heavyson[maxn+5];
int dfn[maxn+5];
int top[maxn+5];
vector<int> nxt[maxn+5];
int u[maxn+5],v[maxn+5],act[maxn+5];
long long w[maxn+5];
int rev[maxn+5];
long double a[maxn+5];
int n,q;
int dfncnt;

void dfs1(int now){
	sze[now]=1;
	for(auto i:nxt[now]){
		if(i!=father[now]){
			father[i]=now;
			deep[i]=deep[now]+1;
			dfs1(i);
			sze[now]+=sze[i];
			if(sze[i]>sze[heavyson[now]]){
				heavyson[now]=i;
			}
		}
	}
}

void dfs2(int now){
	dfn[now]=++dfncnt;
	rev[dfncnt]=now;
	if(now==heavyson[father[now]]){
		top[now]=top[father[now]];
	}
	else{
		top[now]=now;
	}
	if(heavyson[now]){
		dfs2(heavyson[now]);
	}
	for(auto i:nxt[now]){
		if(i!=heavyson[now]&&i!=father[now]){
			dfs2(i);
		}
	}
}

long long value[(maxn<<2)+5];

int merge(int x,int y){
	if(x==0||y==0){
		return 0;
	}
	if(x>1e18/y){
		return 0;
	}
	return x*y;
}

void pushup(int now){
	value[now]=merge(value[now<<1],value[now<<1|1]);
}

void build(int now,int from,int to){
	if(from==to){
		value[now]=a[rev[from]];
		return;
	}
	int mid=(from+to)>>1;
	build(now<<1,from,mid);
	build(now<<1|1,mid+1,to);
	pushup(now);
}

void update(int now,int from,int to,int pos,long double v){
	if(from==to){
		value[now]=v;
		return;
	}
	int mid=(from+to)>>1;
	if(pos<=mid){
		update(now<<1,from,mid,pos,v);
	}
	else{
		update(now<<1|1,mid+1,to,pos,v);
	}
	pushup(now);
}

long double ask(int now,int from,int to,int ql,int qr){
	if(from==ql&&to==qr){
		return value[now];
	}
	int mid=(from+to)>>1;
	int ans=1;
	if(ql<=mid){
		ans=merge(ans,ask(now<<1,from,mid,ql,min(qr,mid)));
	}
	if(mid<qr){
		ans=merge(ans,ask(now<<1|1,mid+1,to,max(mid+1,ql),qr));
	}
	return ans;
}

void update(int e,long long c){
	update(1,1,n,dfn[act[e]],c);
}

int lca(int u,int v){
	while(top[u]!=top[v]){
		if(deep[top[u]]<deep[top[v]]){
			swap(u,v);
		}
		u=father[top[u]];
	}
	if(deep[u]>deep[v]){
		swap(u,v);
	}
	return u;
}

int ask(int u,int fa){
	int ans=1;
	while(1){
		if(u==fa){
			return ans;
		}
		if(top[fa]==top[u]){
			ans=merge(ans,ask(1,1,n,dfn[fa]+1,dfn[u]));
			return ans;
		}
		ans=merge(ans,ask(1,1,n,dfn[top[u]],dfn[u]));
		u=father[top[u]];
	}
}

long long ask(int u,int v,long long k){
	int l=lca(u,v);
	int sum=merge(ask(u,l),ask(v,l));
	if(sum==0){
		return 0;
	}
	return k/sum;
}

signed main(){
	cin>>n>>q;
	for(int i=1;i<n;i++){
		cin>>u[i]>>v[i]>>w[i];
		nxt[u[i]].push_back(v[i]);
		nxt[v[i]].push_back(u[i]);
	}
	dfs1(1);
	dfs2(1);
	for(int i=1;i<n;i++){
		if(father[u[i]]==v[i]){
			a[u[i]]=w[i];
			act[i]=u[i];
		}
		else{
			a[v[i]]=w[i];
			act[i]=v[i];
		}
	}
	build(1,1,n);
	while(q--){
		int op;
		cin>>op;
		if(op==1){
			int u,v;
			long long k;
			cin>>u>>v>>k;
			cout<<ask(u,v,k)<<"\n";
		}
		else{
			int p;
			long long c;
			cin>>p>>c;
			update(p,c);
		}
	}
}
```

---

## 作者：船酱魔王 (赞：0)

# CF593D Happy Tree Party 题解

## 题意回顾

给定 $ n $ 点边带权的树，你需要支持两种操作：

* 沿着一条路径走，手中初始携带一个数字（$ 10^{18} $ 及以内），除以每条经过的边的权值再下取整，要求输出数字最后变成哪个数。

* 将一条边的边权改成**小于等于**原边权的一个数。

$ n \le 2 \times 10^5 $，操作数不超过 $ 2 \times 10^5 $。

## 分析

我们感性理解一下查询操作：当路径很长时，数值大概率很快变成 $ 0 $。

我们发现，这条路径上我们最多需要考虑 $ 64 $ 条左右的 $ \ge 2 $ 边权的边即可证明此路径值为 $ 0 $。

对于边权为 $ 1 $ 的边，显然再怎么改也没法对答案产生影响，因此我们可以直接跳过这些边。

在实现时，我们从 $ u,v $ 向他们的最近公共祖先跳，因为除以很多个数每次向下取整这个运算是可以交换顺序的，所以我们不用管顺序问题。

如果一个点上一条边边权为 $ 1 $，则我们跳过这条边，因为我们只需要向上跳，这里显然可以把所有边权为 $ 1 $ 的边构成的连通块都跳到一个点上，和并查集思想相似，通过路径压缩可将跳过边权 $ 1 $ 的边的均摊复杂度控制在合理范围内。

修改边权时，如果改成 $ 1 $ 的话在并查集上把这条边下面的点和上面的点合并即可。

注意 ```long long``` 的使用与向上跳及时判断是否跳过头。

## AC 代码

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#define int long long
using namespace std;
const int N = 2e5 + 5;
int n, m;
long long wi[N];
struct node {
	int to;
	int id;
};
node make(int v0, int i0) {
	node res;
	res.to = v0;
	res.id = i0;
	return res;
}
vector<node> g[N];
int st[N][21];
int dep[N];
int wid[N];
void pre_dfs(int u, int fath, int bid) {
	st[u][0] = fath;
	dep[u] = dep[fath] + 1;
	wid[u] = bid;
	for(int i = 0; i < g[u].size(); i++) {
		int v = g[u][i].to;
		if(v == fath) continue;
		pre_dfs(v, u, g[u][i].id);
	} 
}
int lca(int x, int y) {
	if(dep[x] < dep[y]) {
		swap(x, y);
	}
	for(int j = 20; j >= 0; j--) {
		if(dep[st[x][j]] >= dep[y]) {
			x = st[x][j];
		}
	}
	if(x == y) return x;
	for(int j = 20; j >= 0; j--) {
		if(st[x][j] != st[y][j]) {
			x = st[x][j];
			y = st[y][j];
		}
	}
	return st[x][0];
}
int up[N];
int findu(int u) {
	if(up[u] == u) {
		return u;
	} 
	return up[u] = findu(up[u]);
}
signed main() {
	scanf("%lld%lld", &n, &m);
	int u, v;
	long long w;
	for(int i = 1; i < n; i++) {
		scanf("%lld%lld%lld", &u, &v, &w);
		g[u].push_back(make(v, i));
		g[v].push_back(make(u, i));
		wi[i] = w;
	}
	int op;
	pre_dfs(1, 0, 0);
	for(int j = 1; j <= 20; j++) {
		for(int i = 1; i <= n; i++) st[i][j] = st[st[i][j - 1]][j - 1];
	}
	for(int i = 1; i <= n; i++) up[i] = i;
	for(int i = 2; i <= n; i++) {
		if(wi[wid[i]] == 1) {
			up[i] = st[i][0];
		}
	}
	for(int i = 1; i <= m; i++) {
		scanf("%lld", &op);
		if(op == 1) {
			scanf("%lld%lld%lld", &u, &v, &w);
			int l = lca(u, v);
			while(true) {
				if(dep[u] <= dep[l] || w == 0) {
					break;
				}
				u = findu(u);
				if(wi[wid[u]] == 1) {
					up[u] = st[u][0];
					continue;
				}
				if(dep[u] <= dep[l]) break;
				w /= wi[wid[u]];
				u = st[u][0];
			}
			while(true) {
				if(dep[v] <= dep[l] || w == 0) {
					break;
				}
				v = findu(v);
				if(wi[wid[v]] == 1) {
					up[v] = st[v][0];
					continue;
				}
				if(dep[v] <= dep[l]) break;
				w /= wi[wid[v]];
				v = st[v][0];
			}
			printf("%lld\n", w);
		} else if(op == 2) {
			scanf("%lld%lld", &u, &v);
			wi[u] = v;
		} else {
			printf("dthkxy AK IOI\n");
		}
	}
	return 0;
} 
```

## 总结与评价

本题考察了乘除运算增长速率较大这一性质，实现细节较多，可以辅助复习最近公共祖先、并查集的板子，是一道很巧妙的题目。

祝大家 NOIP2023 rp++。

---

## 作者：LXH5514 (赞：0)

## CF593D Happy Tree Party

[传送门](https://www.luogu.com.cn/problem/CF593D)

### 题目大意

给定一棵树，边带权。

操作1：给定一个数  $y_i$ ，然后从 $a_i$ 走到 $b_i$，每经过一条边都让 $y_i=\lfloor \frac{y_i}{x_i}  \rfloor$ 。输出最后的 $y_i$ 。

操作2：选择第 j 条边，将他的边权 $x_i$ 改为 $c_i \in [1,v_i]$ 。

### solution

1. 对于路径维护，就想到用树剖，由于没有给根，因此直接拿 1 当根就行~~也可能是我太菜了，其他的不会~~ 。

2. 一般的树剖都是点带权，而这里是边带权，那么就把父亲节点连到子节点的边权存在子节点就行了。

3. 考虑操作1，这个向下取整是不是很烦，如果我们每次操作 1 都需要遍历每个点是不是会炸掉，很自然的会想到如果能直接除以边权之积，这样就可以用线段树维护区间积了，对吧，因此我们这里来证明一下 $\lfloor \frac{y}{x_1*x_2} \rfloor=\lfloor \frac{\lfloor \frac{y}{x_1} \rfloor}{x_2} \rfloor$ 。

   设 $y=a*x1+b (a \in N,b \in [0,x_1) )$，

   因此$\lfloor \frac{\lfloor \frac{y}{x_1} \rfloor}{x_2} \rfloor = \lfloor \frac{a}{x2} \rfloor$

   再设 $a=c*x2+d(c \in N,d \in [0,x2))$

   因此$ \lfloor \frac{\lfloor \frac{y}{x_1} \rfloor}{x_2} \rfloor=c$ 。

   将 c 和 d 代入可得 $y=c*x_1*x_2+d*x1+b$。

   因为 $d<x2,b<x1$，所以 $\lfloor \frac{y}{x_1*x_2} \rfloor=c$。

   因此 $\lfloor \frac{y}{x_1*x_2} \rfloor=\lfloor \frac{\lfloor \frac{y}{x_1} \rfloor}{x_2} \rfloor$

   证明成功，nice。

4. 数据毒瘤，$x_i<=1e18$，因此乘起来会炸 long long，但是 $y<=1e18$，因此 如果乘起来大于 1e18，就打一个标记，而我打的标记是将这个数变成负数，然后还有一个神奇的方法判断这个数是否大于 1e18 ，就是用 long double。

   ```cpp
   long long a,b;
   long long inf=1e18;
   if((long double(a)*(long double)(b)>inf))return -1;
   ```

   AC 代码：

   ```cpp
   #include<iostream>
   #include<stdio.h>
   #define int long long
   using namespace std;
   int read()
   {
   	int x=0,f=1;
   	char c=getchar();
   	while(c<'0'||c>'9'){
   		if(c=='-')f=-1;
   		c=getchar();
   	}
   	while(c>='0'&&c<='9')x=(x<<3)+(x<<1)+f*(c-'0'),c=getchar();
   	return x;
   }
   const int MAXN=2*1e5+10,inf=1e18;
   int n,m,root;
   int u[MAXN*2],v[MAXN*2],first[MAXN],net[MAXN*2],val[MAXN*2];
   int uu[MAXN],vv[MAXN];
   int dep[MAXN],value[MAXN],son[MAXN],fa[MAXN],size[MAXN],top[MAXN];
   int dfn[MAXN],a[MAXN];
   int shu[MAXN*4];
   void ycl()
   {
   	for(int i=1;i<=n;i++)
   	first[i]=0; 
   }
   int cnt;
   void add(int x,int y,int z)
   {
   	cnt++;
   	u[cnt]=x;
   	v[cnt]=y;
   	val[cnt]=z;
   	net[cnt]=first[x];
   	first[x]=cnt;
   }
   void dfs1(int x)
   {
   	son[x]=-1;
   	size[x]=1;
   	for(int i=first[x];i;i=net[i])
   	{
   		if(dep[v[i]])continue;
   		fa[v[i]]=x;
   		value[v[i]]=val[i];
   		dep[v[i]]=dep[x]+1;
   		uu[(i-1)/2+1]=u[i];//由于一开始存的是双向边，但询问要查询，第j条边，由于我把边权存在了子节点，边的方向和题目所给的可能不一样，因此重新加边。
   		vv[(i-1)/2+1]=v[i];
   		dfs1(v[i]);
   		size[x]+=size[v[i]];
   		if(son[x]==-1||size[son[x]]<size[v[i]])son[x]=v[i];
   	}
   }
   int tot=0;
   void dfs2(int x,int y)
   {
   	top[x]=y;
   	tot++;
   	dfn[x]=tot;
   	a[tot]=x;
   	if(son[x]==-1)return ;
   	dfs2(son[x],y);
   	for(int i=first[x];i;i=net[i])
   	if(v[i]!=son[x]&&v[i]!=fa[x])dfs2(v[i],v[i]);
   }//树剖模板
   void update(int x)
   {
   	if(shu[x*2]<0||shu[x*2+1]<0||(long double)shu[x*2]*(long double)shu[x*2+1]>inf)
   	{
   		shu[x]=-1;
   		return ; //判断是否大于1e18
   	}
   	shu[x]=shu[x*2]*shu[x*2+1];
   }
   void build(int now,int l,int r)
   {
   	if(l==r)
   	{
   		shu[now]=value[a[l]];
   		return ;
   	}
   	int mid=(l+r)>>1;
   	build(now*2,l,mid);
   	build(now*2+1,mid+1,r);
   	update(now);
   }
   void change(int now,int l,int r,int x,int y)
   {
   	if(l==r)
   	{
   		shu[now]=y;
   		return ;
   	}
   	int mid=(l+r)>>1;
   	if(x<=mid)change(now*2,l,mid,x,y);
   	else change(now*2+1,mid+1,r,x,y);
   	update(now);
   }
   int query2(int now,int l,int r,int x,int y)
   {
   	if(l>=x&&r<=y)
   	{
   		return shu[now];
   	}
   	int mid=(l+r)>>1;
   	int ans1=1,ans2=1;
   	if(mid>=x)ans1*=query2(now*2,l,mid,x,y);
   	if(ans1<0)return -1;
   	if(mid+1<=y)ans2*=query2(now*2+1,mid+1,r,x,y);
   	if(ans2<0)return -1;
   	if((long double)ans1*(long double)ans2>inf)return -1;//大于1e18就返回负数
   	return ans1*ans2; 
   }
   int  query(int x,int y,int c)
   {
   	while(top[x]!=top[y])
   	{
   		if(dep[top[x]]<dep[top[y]])swap(x,y);
   		int z;
   		z=query2(1,1,n,dfn[top[x]],dfn[x]);
   		if(z<0||c==0){//如果除数的积已经大于1e18，那么答案一定为0.
   			return 0;
   		}
   		else c/=z;
   		x=fa[top[x]];
   	}
   	if(dfn[x]>dfn[y])swap(x,y);
   	int z=query2(1,1,n,dfn[x]+1,dfn[y]);
   	if(z<0)return 0;
   	else return c/z; 
   }
   signed main()
   {
   	n=read();
   	m=read();
   	ycl();
   	for(int i=1;i<=n-1;i++)
   	{
   		int x,y,z;
   		x=read();
   		y=read();
   		z=read();
   		add(x,y,z);
   		add(y,x,z);
   	}
   	root=1;
   	dep[root]=1;
   	dfs1(root);
   	dfs2(root,root);
   	build(1,1,n);
   	for(int i=1;i<=m;i++)
   	{
   		int opt;
   		opt=read();
   		if(opt==1)
   		{
   			int x,y,z;
   			x=read();
   			y=read();
   			z=read();
   			printf("%lld\n",query(x,y,z));
   		}
   		else {
   			int p,c;
   			p=read();
   			c=read();
   			change(1,1,n,dfn[vv[p]],c);
   		}
   	}
    	return 0;
   }
   ```

---

## 作者：_lxy_ (赞：0)

### 题意

给一棵 $n$ 个节点的树，有 $m$ 个操作，一共有两种操作：

- $1\ x\ y\ c$ 表示在 $x$ 到 $y$ 的路径上，每次让 $c \leftarrow \left\lfloor\dfrac{c}{w}\right\rfloor$ ，其中 $w$ 表示边权，询问最后 $c$ 的值。
  
- $2\ x\ c$ 表示把第 $x$ 条边的权值改为 $c$ 。
  

### 分析

显然能看出可以用树剖。容易想到，操作一可以用线段树维护，让 $c$ 除以区间里的每一个数即可。操作二就相当于一个单点修改。但是操作的都是边权，因此可以把边权都向下推到点权上，如图。

![](https://cdn.luogu.com.cn/upload/image_hosting/82pzroxb.png)

然后重链剖分一下，query 的时候每次把重链顶深度更大的向上跳到重链顶，让 $c$ 除以链上的每一个点。最后在处理一下剩余部分即可。同时还要注意一些细节，因为 long long 乘 long long 可能会炸，因此开 long double,另外除的时候判一下除数为0的情况，不然可能会 RE。

### 代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define mem(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long double ll;
typedef unsigned long long ull;
typedef pair<int,int> Pair;
const int inf=2139062143;
inline void qread(){}template<class T1,class ...T2>
inline void qread(T1 &a,T2&... b)
{
    register T1 x=0;register bool f=false;char ch=getchar();
    while(ch<'0') f|=(ch=='-'),ch=getchar();
    while(ch>='0') x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
    x=(f?-x:x);a=x;qread(b...);
}
template<class T> T qmax(T x,T y){return x>y?x:y;}
template<class T,class ...Arg> T qmax(T x,T y,Arg ...arg){return qmax(x>y?x:y,arg...);}
template<class T> T qmin(T x,T y){return x<y?x:y;}
template<class T,class ...Arg> T qmin(T x,T y,Arg ...arg){return qmin(x<y?x:y,arg...);}
const int MAXN=2e5+7;
int n,m,hson[MAXN],fa[MAXN],cnt[MAXN],dep[MAXN],top[MAXN],id[MAXN],tot,a[MAXN],val[MAXN];
vector<Pair>Tree[MAXN];int c;
namespace Seg_tree
{
    const int MX=8000007;
    ll tree[MX];
    inline int ls(int p){return p<<1;}
    inline int rs(int p){return p<<1|1;}
    inline void push_up(int p){tree[p]=tree[ls(p)]*tree[rs(p)];}
    void build(int a[],int p,int l,int r)
    {
        if(l==r) tree[p]=(long double)(a[l]);
        else
        {
            int mid=(l+r)>>1;
            build(a,ls(p),l,mid);
            build(a,rs(p),mid+1,r);
            push_up(p);
        }
    }
    void update(int p,int l,int r,int pos,ll k)
    {
        if(l==r) tree[p]=k;
        else
        {
            int mid=(l+r)>>1;
            if(mid>=pos) update(ls(p),l,mid,pos,k);
            else update(rs(p),mid+1,r,pos,k);
            push_up(p);
        }
    }
    void query(int p,int l,int r,int L,int R)
    {
        if(!c) return; // 如果c已经是0了，再怎么除还是0
        if(L<=l&&r<=R) 
        {
            if(!tree[p]) c=0; // 特判除数为0的情况
            else c/=tree[p];
        }
        else
        {
            int mid=(l+r)>>1;
            if(L<=mid) query(ls(p),l,mid,L,R);
            if(R>mid) query(rs(p),mid+1,r,L,R);
        }
    }
}
using namespace Seg_tree;
void dfs(int u,int f)
{
    cnt[u]=1;
    for(auto son:Tree[u])
    {
        if(son.first==f) continue;
        dep[son.first]=dep[u]+1;fa[son.first]=u;
        dfs(son.first,u);cnt[u]+=cnt[son.first];
        if(cnt[son.first]>cnt[hson[u]]) hson[u]=son.first;
    }
}
void dfs1(int u,int f,int t)
{
    id[u]=++tot;a[tot]=val[u];top[u]=t;
    if(hson[u]) dfs1(hson[u],u,t);
    for(auto son:Tree[u]) if(son.first!=hson[u]&&son.first!=f) dfs1(son.first,u,son.first);
}
void query_chain(int x,int y)
{
    int fx=top[x],fy=top[y];
    while(fx!=fy)
    {
        if(dep[fx]<dep[fy]) swap(fx,fy),swap(x,y); // 跳重链顶更深的
        if(!c) return;
        query(1,1,n,id[fx],id[x]);
        x=fa[fx],fx=top[x];
    }
    if(!c) return;
    if(id[x]>id[y]) swap(x,y);
    query(1,1,n,id[x]+1,id[y]);
}
map<int,Pair>mp;
signed main()
{
    qread(n,m);int i,j;
    for(i=0;i<n-1;i++)
    {
        int u,v,w;qread(u,v,w);
        Tree[u].push_back(Pair(v,w));
        Tree[v].push_back(Pair(u,w));
        mp[i]=Pair(u,v);
    }fa[1]=1;dep[1]=0;dfs(1,0);
    for(i=1;i<=n;i++)
    {
        for(auto j:Tree[i])
        {
            int u=i,v=j.first;
            if(dep[u]>dep[v]) swap(u,v); // 这条边推到了深度更深的点上
            val[v]=j.second;
        }
    }
    dfs1(1,0,1);build(a,1,1,n);int num=0;
    for(i=0;i<m;i++)
    {
        int op,x,y;qread(op);
        if(op==1)
        {
            qread(x,y,c);
            query_chain(x,y);
            printf("%lld\n",c);
        }
        if(op==2) 
        {
            qread(x,c);
            int u=mp[x-1].first,v=mp[x-1].second;
            if(id[u]>id[v]) swap(u,v);
            update(1,1,n,id[v],c); // 单点修改
        }
    }
    return 0;
}
```

---

## 作者：Mihari (赞：0)

# 题目

[传送门](https://www.luogu.com.cn/problem/CF593D)

# 题解

思维好题.

必须明白，一个数 $x(x\le 10^{18})$ 在反复执行除以某个数下取整，即反复 $x=\lfloor \frac{x}{t} \rfloor(t\ge 2)$ 超过 $60$ 次之后必定为 $0$，因为 $\log _210^{18}<60$，所以，如果去除那些边权为 $1$ 的边，我们最多使用暴力爬山法 $60$ 次，这个 $x$ 就会变成 $0$，而题目中又有一个边权值变化是具有特殊性的，即变化范围在 $[1,x_{p_i}]$，说明一条边只会往小变，并且在边权为 $1$ 之后不会再变回来，那么我们可以用类似并查集的数据结构，将那些边权为 $1$ 的边跳过不算，这样就可以保证我们暴力爬山只会执行最多 $60$ 次，那么时间复杂度为 $\mathcal O(60m+\alpha m)$，并查集的反阿克曼不能忘记。

# 代码

```cpp
https://www.cnblogs.com/Arextre/p/13553809.html
```



---

