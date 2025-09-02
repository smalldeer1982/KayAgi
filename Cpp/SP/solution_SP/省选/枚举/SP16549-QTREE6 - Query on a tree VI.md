# QTREE6 - Query on a tree VI

## 题目描述

给你一棵 $n$ 个点的树，编号 $1\sim n$。每个点可以是黑色，可以是白色。初始时所有点都是黑色。下面有两种操作：

* `0 u`：询问有多少个节点 $v$ 满足路径 $u$ 到 $v$ 上所有节点（包括 $u$）都拥有相同的颜色。

* `1 u`：翻转 $u$ 的颜色。

## 样例 #1

### 输入

```
5
1 2
1 3
1 4
1 5
3
0 1
1 1
0 1```

### 输出

```
5
1```

# 题解

## 作者：disposrestfully (赞：24)

既然大家写的都是$LCT$那我就来放一篇树剖好了.

首先我们设$Black(x)$示如果当前点$x$是黑点,$x$的子树中黑色联通块的大小.$White(i)$同理.

那么查询的时候显然就是从当前点开始往上跳,直到跳到根或者当前点的父亲颜色与它不同,答案就是当前点的$Black$或$White$值.


考虑修改操作,由于点$x$从黑变白和从白变黑是对称的,这里我们只讨论$x$从黑变白的情况.

> 从$Fa(x)$开始向上找到第一个白色点$u$,如果找不到的话$u=root$,将路径$Fa(x) \rightarrow u$上所有点的$Black$值减去$Black(x)$.

> 从$Fa(x)$开始向上找到第一个黑色点$u$,如果找不到的话$u=root$,将路径$Fa(x) \rightarrow u$上所有点的$White$值加上$White(x)$.

现在唯一剩下的问题是怎么找到$x$到根路径上的第一个白色/黑色点.

我们可以使用一颗线段树解决这个问题,树上每个节点维护其对应区间从右到左遇到的第一个白色点和黑色点的位置,这恰好对应了一条重链从下往上遇到的第一个白色点和黑色点的$dfs$序.

代码难度似乎不是很大的样子.

``` cpp
#include<bits/stdc++.h>
#define read() Read<int>()
namespace pb_ds{   
    namespace io{
        const int MaxBuff=1<<15;
        const int Output=1<<23;
        char B[MaxBuff],*S=B,*T=B;
		#define getc() ((S==T)&&(T=(S=B)+fread(B,1,MaxBuff,stdin),S==T)?0:*S++)
        char Out[Output],*iter=Out;
        inline void flush(){
            fwrite(Out,1,iter-Out,stdout);
            iter=Out;
        }
    }
    template<class Type> inline Type Read(){
        using namespace io;
        register char ch;
        register Type ans=0; 
        register bool neg=0;
        while(ch=getc(),(ch<'0' || ch>'9') && ch!='-');
        ch=='-'?neg=1:ans=ch-'0';
        while(ch=getc(),'0'<= ch && ch<='9') ans=ans*10+ch-'0';
        return neg?-ans:ans;
    }
    template<class Type> inline void Print(register Type x,register char ch='\n'){
        using namespace io;
        if(!x) *iter++='0';
        else{
            if(x<0) *iter++='-',x=-x;
            static int s[100]; 
            register int t=0;
            while(x) s[++t]=x%10,x/=10;
            while(t) *iter++='0'+s[t--];
        }
        *iter++=ch;
    }
}
using namespace pb_ds;
using namespace std;
typedef long long ll;
const int N=1e5+5;
const int inf=1e9;
#define mid (l+r>>1)
#define ls (x<<1)
#define rs (ls|1)
namespace seg_tree{
	int fr[N<<2][2];
	inline void pushup(int x){
		fr[x][0]=max(fr[ls][0],fr[rs][0]);
		fr[x][1]=max(fr[ls][1],fr[rs][1]);
	}	
	void build(int x,int l,int r){
		fr[x][0]=-inf,fr[x][1]=r;
		if (l==r) return;
		build(ls,l,mid),build(rs,mid+1,r);
	}
	void update(int x,int l,int r,int pos){
		if (l==r){
			swap(fr[x][0],fr[x][1]);
			return;
		}	
		if (pos<=mid) update(ls,l,mid,pos);
		else update(rs,mid+1,r,pos);
		pushup(x);
	}
	int query(int x,int l,int r,int L,int R,int opt){
		if (L<=l && r<=R) return fr[x][opt];
		int res=-inf;
		if (R>mid) res=query(rs,mid+1,r,L,R,opt);
		if (res!=-inf) return res;
		if (L<=mid) res=query(ls,l,mid,L,R,opt);
		return res;
	}
}
using namespace seg_tree;
struct seg{
	int add[N<<2],val[N];
	inline void Add(int x,int l,int r,int k){
		if (l==r) val[l]+=k;
		else add[x]+=k;
	}
	inline void pushdown(int x,int l,int r){
		if (add[x]){
			Add(ls,l,mid,add[x]);
			Add(rs,mid+1,r,add[x]);
			add[x]=0;		
		}
	}
	void update(int x,int l,int r,int L,int R,int k){
		if (L<=l && r<=R){
			Add(x,l,r,k);
			return;
		}
		pushdown(x,l,r);
		if (L<=mid) update(ls,l,mid,L,R,k);
		if (R>mid) update(rs,mid+1,r,L,R,k);
	}
	int query(int x,int l,int r,int pos){
		if (l==r) return val[l];
		pushdown(x,l,r);
		if (pos<=mid) return query(ls,l,mid,pos);
		return query(rs,mid+1,r,pos);
	}
}s[2];
int n,m,tot;
int dfn[N],fa[N],sz[N];
int son[N],dep[N],top[N];
int tp[N],rk[N];
struct edge{
	int next,to;
}a[N<<1];
int head[N],cnt;
inline void add(int u,int v){
	a[++cnt].to=v;
	a[cnt].next=head[u];
	head[u]=cnt;
}
void dfs1(int x){
	dep[x]=dep[fa[x]]+1;
	sz[x]=tp[x]=1;
	for (int i=head[x];i;i=a[i].next){
		int y=a[i].to;
		if (y==fa[x]) continue;
		fa[y]=x,dfs1(y),sz[x]+=sz[y];
		if (sz[son[x]]<sz[y]) son[x]=y;
	}
}
void dfs2(int x){
	if (x^son[fa[x]]) top[x]=x;
	else top[x]=top[fa[x]];
	rk[dfn[x]=++tot]=x;
	if (son[x]) dfs2(son[x]);
	for (int i=head[x];i;i=a[i].next){
		int y=a[i].to;
		if (y==fa[x] || y==son[x]) continue;
		dfs2(y);
	}
}
inline int find(int x,int opt){
	while (top[x]^1){
		int now=query(1,1,n,dfn[top[x]],dfn[x],opt);
		if (now>0) return rk[now];
		x=fa[top[x]];
	}
	x=query(1,1,n,1,dfn[x],opt);
	if (x>0) return rk[x];
	return 1;
}
inline void work(int u,int v,int opt,int w){
	while (top[u]^top[v]){
		if (dep[top[u]]<dep[top[v]]) swap(u,v);
		s[opt].update(1,1,n,dfn[top[u]],dfn[u],w);
		u=fa[top[u]];
	}
	if (dep[u]>dep[v]) swap(u,v);
	s[opt].update(1,1,n,dfn[u],dfn[v],w);
}
inline int get_fa(int x,int u){
	while (dep[fa[top[x]]]>dep[u])
		x=fa[top[x]];
	if (dep[top[x]]>dep[u]) x=top[x];
	if (dep[x]==dep[u]+1) return dfn[x];
	return dfn[u]+1;
}
int main(){
	freopen("6.in","r",stdin);
	freopen("6.out","w",stdout);
	n=read();
	for (int i=1;i<n;++i){
		int u=read(),v=read();
		add(u,v),add(v,u);		
	}
	dfs1(1),dfs2(1);
	for (int i=1;i<=n;++i){
		s[1].val[dfn[i]]=sz[i];
		s[0].val[dfn[i]]=1;
	}
	build(1,1,n);
	m=read();
	while (m--){
		int opt=read(),x=read();
		if (!opt){
			int y=find(x,tp[x]^1);
			if (tp[y]==tp[x]) y=dfn[y];
			else y=get_fa(x,y);
			Print(s[tp[x]].query(1,1,n,y));
		}else{
			int now[2],f[2];
			for (int i=0;i<=1;++i){
				now[i]=s[i].query(1,1,n,dfn[x]);
				if (fa[x]) f[i]=find(fa[x],i);
			}
			if (fa[x]){
				work(fa[x],f[tp[x]^1],tp[x],-now[tp[x]]);
				work(fa[x],f[tp[x]],tp[x]^1,now[tp[x]^1]);
			}
			update(1,1,n,dfn[x]);
			tp[x]^=1;
		}
	}
	io::flush();
	return 0;
}
```

---

## 作者：FlashHu (赞：24)

[洛谷题目传送门](https://www.luogu.org/problemnew/show/SP16549)
## 思路分析
题意就是要维护同色连通块大小。要用LCT维护子树大小就不说了，可以看看[蒟蒻的LCT总结](http://www.cnblogs.com/flashhu/p/8324551.html)。

至于连通块如何维护，首先肯定可以想到一个很naive的做法：直接维护同色连通块，每次更改时暴力修改父边和子边。。。。。。

来个菊花图吧！（话说我真的好弱，前几天ZJOI的时候才知道对于某点度数很大的树/图有这样的称呼，真是很形象哈23333）

既然这条路行不通，那就换一种模型吧。

这是一种高级的维护染色连通块的较为通用的模型。

感觉蒟蒻对这种模型的理解与许多巨佬有不一样的地方，在这儿瞎扯扯吧

很多与树有关的题目，当边权不好处理时，有时候会转化为此边子节点的点权处理。

因为有根树中除了根，每个点都有唯一的父边。

在这一题里，道理是一样的，但转化方向却是反的，要把点化为边！

把每个点的父边赋予该点的颜色。我们需要两个LCT，每种对应一个颜色。一条边只有在对应颜色的LCT中才会被连上。

于是，原来同色点的连通块，就变成了剪开顶端节点后的边的连通块（解释一下，因为点的颜色给了父边，那么既然是顶端节点，那它的父边就不会在连通块中，也就是这个点与连通块不同色，于是该点的所有子树不能连起来，于是要剪掉）

然后就可以惊讶地发现，修改一个点的颜色之后，只要在原来颜色对应LCT中断掉父边，再在新颜色对应LCT中连接父边，就可以轻而易举地维护连通块啦。

再谈查询，上面提到了要剪开顶端节点（也就是连通块构成的树的树根），于是先findroot，再输出它的重子树的大小。

一个小细节，1节点是没有父亲的，不过为了模型的建立，要有父边，于是需要加一个虚点，让1的父亲指向它连边。

```cpp
#include<cstdio>
#include<cstdlib>
#define R register int
#define I inline void
const int N=1000009,M=N<<1;
#define lc c[x][0]
#define rc c[x][1]
#define C col[u]
int fa[N],he[N],ne[M],to[M];
bool col[N];
struct LCT{
	int f[N],c[N][2],si[N],s[N];
	bool r[N];
	LCT(){for(R i=1;i<N;++i)s[i]=1;}//注意初始化
	inline bool nroot(R x){return c[f[x]][0]==x||c[f[x]][1]==x;}
	I pushup(R x){
		s[x]=s[lc]+s[rc]+si[x]+1;
	}
	I rotate(R x){
		R y=f[x],z=f[y],k=c[y][1]==x,w=c[x][!k];
		if(nroot(y))c[z][c[z][1]==y]=x;c[x][!k]=y;c[y][k]=w;
		f[w]=y;f[y]=x;f[x]=z;
		pushup(y);
	}
	I splay(R x){
		R y;
		while(nroot(x)){
			if(nroot(y=f[x]))rotate((c[f[y]][0]==y)^(c[y][0]==x)?x:y);
			rotate(x);
		}
		pushup(x);
	}
	I access(R x){
		for(R y=0;x;x=f[y=x]){
			splay(x);
			si[x]+=s[rc];
			si[x]-=s[rc=y];
		}
	}
	inline int findroot(R x){
		access(x);splay(x);
		while(lc)x=lc;
		splay(x);
		return x;
	}
	I link(R x){//只传一个参数，因为只会连父边，cut同理
		splay(x);//不用access，因为这时x肯定是连通块的根
		R y=f[x]=fa[x];
		access(y);splay(y);//与常规LCT不同，别忘加
		si[y]+=s[x];s[y]+=s[x];
	}
	I cut(R x){
		access(x);splay(x);
		lc=f[lc]=0;
		pushup(x);
	}
}lct[2];
void dfs(R x){
	for(R y,i=he[x];i;i=ne[i])
		if((y=to[i])!=fa[x])
			fa[y]=x,dfs(y),lct[0].link(y);
}
#define G ch=getchar()
#define in(z) G;\
	while(ch<'-')G;\
	z=ch&15;G;\
	while(ch>'-')z*=10,z+=ch&15,G
int main(){
	register char ch;
	R p=1,n,m,i,u,v,op;
	in(n);
	for(i=1;i<n;++i){
		in(u);in(v);
		to[++p]=v;ne[p]=he[u];he[u]=p;
		to[++p]=u;ne[p]=he[v];he[v]=p;
	}
	dfs(1);
	fa[1]=n+1;lct[0].link(1);//虚点
	in(m);
	while(m--){
		in(op);in(u);
		if(op)lct[C].cut(u),lct[C^=1].link(u);
		else{
			v=lct[C].findroot(u);
			printf("%d\n",lct[C].s[lct[C].c[v][1]]);
		}
	}
    return 0;
}
```

---

## 作者：panyf (赞：8)

树剖 $O(m\log n)$ 做法。

记 $b_x$ 表示将 $x$ 变为黑点，其他点颜色不变，$x$ 子树内 $x$ 所在的同色连通块大小。

$w_x$ 表示 $x$ 为白点，同理。

考虑将某个点 $x$ 从黑变白的影响，从白变黑同理。

首先从 $fa_x$ 向上找到第一个白点 $u$，如果找不到则 $u=root$，将路径 $fa_x\rightarrow u$ 上的所有点（包含端点）的 $b$ 值减去 $b_x$。

然后从 $fa_x$ 向上找到第一个黑点 $u$，找不到则 $u=root$，将路径 $fa_x\rightarrow u$ 上的所有点的 $w$ 值加上 $w_x$。

考虑询问。不妨设 $x$ 为黑色，从 $x$ 向上找到第一个点 $u$ 满足其父亲为白色，找不到则 $u=root$，$b_u$ 即所求。

维护 $b$ 和 $w$ 需要支持链加，单点查询，可以用树上差分+树状数组做到一个 $\log$，具体做法是维护差分值 $t$，对 $u\rightarrow v$ 加 $w$（$v$ 是 $u$ 的祖先）转化为 $t_u$ 加 $w$、$t_{fa_v}$ 减 $w$，查询 $x$ 的值就是 $x$ 子树的 $t$ 求和。

现在只需要支持从 $fa_x$ 向上找到第一个黑/白点，显然可以用树剖+线段树上二分/set 做到两个 $\log$。

考虑优化，对每条重链维护两个值，分别表示重链上深度最浅的黑/白点。

修改 $x$ 的颜色时，除了在 set 上修改，额外更新一下所在重链的这两个值。

找点时，先判断深度最浅的黑/白点是否在询问区间内，若是，则进行一次 set 上查询，然后直接返回结果。这样每次只需要跳 $\log$ 次重链+一次 set 查询，复杂度 $O(\log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+3;
using ar=int[N];
ar ip,p,ed,fa,tp,sz,d,sn;
bool c[N];
basic_string<int>g[N];
int id,n,m[N][2];
struct F{
	int t[N];
	void add(int x,int y){if(x)for(x=p[x];x<=n;x+=x&-x)t[x]+=y;}
	int sum(int x){int r=0;for(;x;x-=x&-x)r+=t[x];return r;}
	int get(int x){return sum(ed[x])-sum(p[x]-1);}
}f[2];
set<int>s[N][2];
void dfs1(int x,int y){
	sz[x]=1,d[x]=d[y]+1,fa[x]=y;
	for(int i:g[x])if(i!=y)if(dfs1(i,x),sz[x]+=sz[i],sz[i]>sz[sn[x]])sn[x]=i;
}
void dfs2(int x,int y){
	if(tp[x]=y,ip[p[x]=++id]=x,sn[x])dfs2(sn[x],y);
	for(int i:g[x])if(!p[i])dfs2(i,i);
	if(ed[x]=id,f[0].add(x,1),f[1].add(x,1),f[1].add(fa[x],-1),s[tp[x]][0].insert(p[x]),x==y)m[x][0]=p[x];
}
int get(int x,bool c){//从x向上找到第一个点u满足其父亲颜色为c
	int y=x,z;
	for(x=fa[x];x;x=fa[y=tp[x]])if(m[tp[x]][c]&&m[tp[x]][c]<=p[x])return z=ip[*--s[tp[x]][c].upper_bound(p[x])],z==x?y:sn[z];
	return 1;
}
int main(){
	int i,j,k,q;
	for(scanf("%d",&n),i=1;i<n;++i)scanf("%d%d",&j,&k),g[j]+=k,g[k]+=j;
	for(dfs1(1,0),dfs2(1,1),scanf("%d",&q);q--;)if(scanf("%d%d",&i,&j),i){
		s[k=tp[j]][c[j]].erase(p[j]),s[k][!c[j]].insert(p[j]);
		m[k][0]=s[k][0].size()?*s[k][0].begin():0,m[k][1]=s[k][1].size()?*s[k][1].begin():0;
		k=get(j,!c[j]),i=f[c[j]].get(j),f[c[j]].add(fa[j],-i),f[c[j]].add(fa[fa[k]],i);
		c[j]^=1,k=get(j,!c[j]),i=f[c[j]].get(j),f[c[j]].add(fa[j],i),f[c[j]].add(fa[fa[k]],-i);
	}else printf("%d\n",f[c[j]].get(get(j,!c[j])));
	return 0;
}
```


---

## 作者：Soulist (赞：7)

~~这是一个萌新求助~~

显然暴力做因为度数的缘故所以非常的麻烦，于是我们考虑一个常见的 trick

对于每个点维护 $f_{u,0},f_{u,1}$ 表示子树内到他的白点/黑点的数量，那么查询只需要找到最顶部的一个父亲满足沿途其与其颜色相同，直接输出这个父亲的数组就是答案了。

于是只需要考虑维护，我们发现每次每次其实只会影响一段父亲的 $f$ 数组，那么只需要通过链修改计算答案即可，所以类似于查询处理即可。

通过树链剖分/LCT维护，复杂度为 $\mathcal O(n\log^2 n)$ 或 $\mathcal O(n\log n)$

LCT 的话前后者都通过 Splay 二分处理即可，然而我华丽丽的 TLE 了...

说好的 $1\log$ 呢... 不过感觉是写挂了，所以这里贴一份代码[求助](https://www.luogu.com.cn/paste/5twc5w4g)

---

## 作者：Reaepita (赞：5)

这里提供一种类似 QTree5 不用 link 和 cut 的做法。

维护 $lsum,rsum$ 表示每一条实链中深度最浅的点，能够到达多少同色点，深度最深的点，能够到达多少同色点。

在 pushup 的时候，我们对于 $lsum_{rt} $ 只需要考虑，
$lsum_{ls}$ ， $rt$ 连接的其他splay的同色连通点的数量，和跨过 $rt$ 到达这条实链中其它的同色连通点的数量。

具体来说就是

$lsum_{rt}=lsum_{ls}+$虚边贡献$+1+lsum_{rs}$

转移的时候要注意维护合法性。

维护 $Tcol_{rt}$ 表示以 $rt$ 为根的splay所代表的链上的节点颜色是否相同（不相同值为 $2$）

$Lcol$ 维护每一条实链上深度最浅的点的颜色

$Rcol$ 维护每一条实链上深度最深的点的颜色。

这样的话 pushup 的时候，需要保证实链上深度最浅的点能够走到
$rt$($Tcol_{ls}=col_{rt}$)，否则 $lsum_{rt}=lsum_{ls}$。

同时若 $Lcol_{rs}!=col_{rt}$ 说明 $rt$ 不能够向深度更大的点走了

即 $lsum_{rt}=lsum_{ls}+$虚边贡献$+1$

那么转移 $rsum $ 同理。

对于虚边的贡献，直接维护 $cnt_{rt,{0/1}}$ 表示白色和黑色对应的同色连通块大小。

在access的时候直接加减即可。



```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+10;
const int inf=1e8;
int n;
struct LCT
{
    int son[maxn][2],col[maxn];
    int fa[maxn],lmx[maxn],rmx[maxn];
    int Tcol[maxn],Lcol[maxn],Rcol[maxn];
    void init(){col[0]=-1;for(int i=1;i<=n;i++)lmx[i]=rmx[i]=Tcol[i]=Lcol[i]=Rcol[i]=col[i]=1;}
    int cnt[maxn][2];
    bool isroot(int u){return son[fa[u]][1]!=u&&son[fa[u]][0]!=u;}
    void pushup(int u)
    {
        if(!u)return;
        int ls=son[u][0],rs=son[u][1];
        lmx[u]=lmx[ls]+(((Tcol[ls]!=2&&col[u]==Tcol[ls])||!ls)?cnt[u][col[u]]+1+(Lcol[rs]==col[u]?lmx[rs]:0):0);
        rmx[u]=rmx[rs]+(((Tcol[rs]!=2&&col[u]==Tcol[rs])||!rs)?cnt[u][col[u]]+1+(Rcol[ls]==col[u]?rmx[ls]:0):0);
        if(!ls)Lcol[u]=col[u];
        else Lcol[u]=Lcol[ls];
        if(!rs)Rcol[u]=col[u];
        else Rcol[u]=Rcol[rs];
        if(Tcol[ls]==2||Tcol[rs]==2||(ls&&Tcol[ls]!=col[u])||(rs&&Tcol[rs]!=col[u]))Tcol[u]=2;
        else Tcol[u]=col[u];
    }
    void rotate(int u)
    {
        int f=fa[u],g=fa[f];
        int nf=son[f][1]==u,ng=son[g][1]==f;
        if(!isroot(f))son[g][ng]=u;fa[u]=g;
        son[f][nf]=son[u][nf^1];
        if(son[u][nf^1])fa[son[u][nf^1]]=f;
        son[u][nf^1]=f,fa[f]=u;
        pushup(f),pushup(u);
    }
    void splay(int u)
    {
        while(!isroot(u))
        {
            //cout<<u<<endl;
            //cout<<u<<' '<<fa[u]<<endl;
            int f=fa[u],g=fa[f];
            if(!isroot(f))(son[f][1]==u)^(son[g][1]==f)?rotate(u):rotate(f);
            rotate(u);
        }
        pushup(u);
    }
    void access(int u)
    {
        for(int y=0;u;u=fa[u])
        {
            splay(u);
            cnt[u][Lcol[son[u][1]]]+=lmx[son[u][1]];
            son[u][1]=y;
            cnt[u][Lcol[son[u][1]]]-=lmx[son[u][1]];
            pushup(y=u);
        }
    }  
    void link(int a,int b)
    {
        splay(a);
        //cout<<Lcol[a]<<endl;
        fa[a]=b;cnt[b][Lcol[a]]+=lmx[a],pushup(b);
    }
    int query(int u)
    {
        access(u),splay(u);
        return rmx[u];
    }
    void update(int u)
    {
        access(u),splay(u);
        col[u]^=1;pushup(u);
    }
}T;
struct edge{int v,nxt;}e[maxn<<1];
int head[maxn],ecnt=0;
void add(int u,int v){e[++ecnt]=(edge){v,head[u]},head[u]=ecnt;}
void dfs(int u,int pre)
{
    for(int i=head[u];~i;i=e[i].nxt)
    {
        int v=e[i].v;
        if(v==pre)continue;
        dfs(v,u);
        T.link(v,u);
    }
}
int main()
{
    memset(head,-1,sizeof(head));
    scanf("%d",&n);
    T.init();
    for(int i=1;i<n;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        add(u,v);
        add(v,u);
    }
    dfs(1,0);
   // for(int i=1;i<=n;i++)cout<<T.query(i)<<endl;
    int Q;
    scanf("%d",&Q);
    while(Q--)
    {
        int op,u;
        scanf("%d%d",&op,&u);
        if(op==0)printf("%d\n",T.query(u));
        else T.update(u);
    }
    system("pause");
}
```





---

## 作者：Cyhlnj (赞：5)

黑白开两个$LCT$

然后有一个很$Naive$的做法

就是每次改颜色时，暴力枚举连的点，$Link$或$Cut$

显然菊花树直接就卡掉了

###优化

把树定成一棵以$1$为根的有根树，然后把颜色放在它的父亲与它相连的边上

然后维护子树信息

$Link$或$Cut$就只涉及一条边

注意到每个子树的根不一定同色

询问时要特判根的颜色

就是$Access$一下，然后$Splay$，跳左儿子找到根，并把它$Splay$

如果同色，就输出它的子树信息，否则输出它的右儿子的子树信息

应为右儿子深度比它大，所以，右儿子的子树信息就是答案


由于我们定义它是有根树

那么我们不能$Makeroot$，这样的话才能保证能找到当前子树的根

那么$Link$时，为保证它父亲以上的点不受影响，

$Access$并$Splay$它父亲

又因为它就是当前的子树的根，把它$Splay$一下，之后再连虚边

$Cut$时，把它$Access$并$Splay$，那么它的父亲就在左子树，直接删掉它和它左儿子的实边是没有影响的

```cpp
# include <bits/stdc++.h>
# define RG register
# define IL inline
# define Fill(a, b) memset(a, b, sizeof(a))
using namespace std;
typedef long long ll;
const int _(1e5 + 5);

IL int Input(){
	RG int x = 0, z = 1; RG char c = getchar();
	for(; c < '0' || c > '9'; c = getchar()) z = c == '-' ? -1 : 1;
	for(; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + (c ^ 48);
	return x * z;
}

struct LCT{
	typedef int Arr[_];
	Arr fa, ch[2], sum, val;
	
	IL int Son(RG int x){
		return ch[1][fa[x]] == x;
	}

	IL int Isroot(RG int x){
		return ch[0][fa[x]] != x && ch[1][fa[x]] != x;
	}
	
	IL void Update(RG int x){
		sum[x] = sum[ch[0][x]] + sum[ch[1][x]] + val[x] + 1;
	}

	IL void Rotate(RG int x){
		RG int y = fa[x], z = fa[y], c = Son(x);
		if(!Isroot(y)) ch[Son(y)][z] = x; fa[x] = z;
		ch[c][y] = ch[!c][x], fa[ch[c][y]] = y;
		ch[!c][x] = y, fa[y] = x, Update(y);
	}

	IL void Splay(RG int x){
		for(RG int y = fa[x]; !Isroot(x); Rotate(x), y = fa[x])
			if(!Isroot(y)) Son(x) ^ Son(y) ? Rotate(x) : Rotate(y);
		Update(x);
	}

	IL void Access(RG int x){
		for(RG int y = 0; x; y = x, x = fa[x]){
			Splay(x), val[x] += sum[ch[1][x]] - sum[y];
			ch[1][x] = y, Update(x);
		}
	}

	IL int Findroot(RG int x){
		Access(x), Splay(x);
		while(ch[0][x]) x = ch[0][x];
		Splay(x);
		return x;
	}

	IL void Link(RG int x, RG int y){
		if(!y) return;
		Access(y), Splay(x), Splay(y);
		fa[x] = y, val[y] += sum[x], Update(y);
	}

	IL void Cut(RG int x, RG int y){
		if(!y) return;
		Access(x), Splay(x);
		ch[0][x] = fa[ch[0][x]] = 0, Update(x);
	}
} T[2];
int fa[_], n, m, col[_];
vector <int> G[_];

IL void Dfs(RG int u, RG int ff){
	for(RG int i = 0, l = G[u].size(); i < l; ++i){
		RG int v = G[u][i];
		if(v == ff) continue;
		T[1].Link(v, u), fa[v] = u;
		Dfs(v, u);
	}
}

int main(RG int argc, RG char *argv[]){
	n = Input();
	for(RG int i = 1; i <= n; ++i) col[i] = 1;
	for(RG int i = 1; i < n; ++i){
		RG int u = Input(), v = Input();
		G[u].push_back(v), G[v].push_back(u);
	}
	Dfs(1, 0), m = Input();
	for(RG int i = 1; i <= m; ++i){
		RG int op = Input(), x = Input(), ff, &c = col[x];
		if(op) T[c].Cut(x, fa[x]), c ^= 1, T[c].Link(x, fa[x]);
		else{
			T[c].Access(x), ff = T[c].Findroot(x);
			if(col[ff] == c) printf("%d\n", T[c].sum[ff]);
			else printf("%d\n", T[c].sum[T[c].ch[1][ff]]);
		}
	}
	return 0;
}

```

---

## 作者：Kelin (赞：4)

题意:询问与$u$相同颜色的联通块的大小,带修改

考虑建立黑白两颗$lct$,答案就是在相应$lct$中,$u$所属的那棵树的大小了 

至于修改的话一个非常暴力的想法就是直接$cut$然后$link$

这样的话碰到菊花图就$GG$了(下面我们讨论维护黑树的$lct$,白树同理)

考虑到原树的形态是不会变的,所以我们可以设在$lct$中如果有边$edge(u,v)$,那么$v$就是黑色($u$不一定是黑色) 

这样的话我们$cut$和$link$都只要管$edge(u$原树中的父亲,$u)$这条边了 

统计答案的话就把它$access$上去后然后判断这条链最上面的那个点是不是黑点,不是就要输出最上面那个点的儿子节点

要是不会$lct$维护子树信息可以先做做这个[题目](https://www.luogu.org/problemnew/show/P4219)

然后这题因为只要$link,cut$ $egde(fa[u],u)$这条边所以写法可以特殊一点

具体怎么特殊看代码

```
#include<bits/stdc++.h>
#define fp(i,a,b) for(int i=a,I=b;i<=I;++i)
#define go(i,u) for(int i=fi[u],v=e[i].to;i;v=e[i=e[i].nx].to)
#define file(s) freopen(s".in","r",stdin),freopen(s".out","w",stdout)
using namespace std;
char ss[1<<17],*A=ss,*B=ss;
inline char gc(){return A==B&&(B=(A=ss)+fread(ss,1,1<<17,stdin),A==B)?-1:*A++;}
template<class T>inline void sd(T&x){
    char c;T y=1;while(c=gc(),(c<48||57<c)&&c!=-1)if(c==45)y=-1;x=c^48;
    while(c=gc(),47<c&&c<58)x=(x<<1)+(x<<3)+(c^48);x*=y;
}
char sr[1<<21],z[20];int C=-1,Z;
inline void Ot(){fwrite(sr,1,C+1,stdout),C=-1;}
template<class T>inline void we(T x){
    if(C>1<<20)Ot();if(x<0)sr[++C]=45,x=-x;
    while(z[++Z]=x%10+48,x/=10);
    while(sr[++C]=z[Z],--Z);sr[++C]='\n';
}
const int N=1e5+5;
typedef int arr[N];
struct eg{int nx,to;}e[N<<1];
int n,m,ce;arr fi,fa,sz,col;
struct LCT{
	int Col,ch[N][2];arr fa,sz,tp;
	#define lc(u)(ch[u][0])
	#define rc(u)(ch[u][1])
	inline void op(int u,int w){sz[u]+=w,tp[u]+=w;}
	inline bool ir(int u){return lc(fa[u])^u&&rc(fa[u])^u;}
	inline bool gf(int u){return rc(fa[u])==u;}
	inline void up(int u){sz[u]=sz[lc(u)]+sz[rc(u)]+tp[u];}
	inline void rot(int u){
		int p=fa[u],k=gf(u);
		if(!ir(p))ch[fa[p]][gf(p)]=u;
		if(ch[u][!k])fa[ch[u][!k]]=p;
		ch[p][k]=ch[u][!k],ch[u][!k]=p;
		fa[u]=fa[p],fa[p]=u,up(p);
	}
	void splay(int u){
		for(int f=fa[u];!ir(u);rot(u),f=fa[u])
			if(!ir(f))rot(gf(u)==gf(f)?f:u);
		up(u);
	}
	inline void acc(int u){for(int v=0;u;u=fa[v=u])splay(u),tp[u]+=sz[ch[u][1]]-sz[v],ch[u][1]=v,up(u);}
	inline void brt(int u){acc(u),splay(u);}
	inline void link(int u,int v){
		if(!v)return;
		brt(v),splay(u),tp[fa[u]=v]+=sz[u];
	}
	inline void cut(int u,int v){
		if(!v)return;
		brt(u),fa[lc(u)]=0,lc(u)=0,up(u);
	}
	inline int Gf(int u){brt(u);while(lc(u))u=lc(u);return u;}
	inline int qry(int u){
		int p=Gf(u);splay(p);
		return col[p]==Col?sz[p]:sz[ch[p][1]];
	}
}T[2];
inline void add(int u,int v){e[++ce]=eg{fi[u],v},fi[u]=ce;}
void dfs(int u){sz[u]=1;go(i,u)if(v!=fa[u])T[0].fa[v]=fa[v]=u,dfs(v),sz[u]+=sz[v];}
int main(){
    #ifndef ONLINE_JUDGE
        file("s");
    #endif
	sd(n),T[1].Col=1;int u,v;
	fp(i,2,n)sd(u),sd(v),add(u,v),add(v,u);
	dfs(1);sd(m);fp(i,1,n)T[0].tp[i]=T[0].sz[i]=sz[i];
	while(m--){
		sd(v),sd(u);int&c=col[u];
		if(v)T[c].cut(u,fa[u]),T[c].op(u,-1),c^=1,T[c].op(u,1),T[c].link(u,fa[u]); 
		else we(T[c].qry(u));
	}
return Ot(),0;
}
```

---

## 作者：xukuan (赞：2)

操作有两种，一种是问相同颜色的点的大小，一种是改变点的颜色。

众所周知Qtree系列是LCT的题目，那么这题怎么用LCT去解决？

相对于传统的维护区间的LCT，我们还要再开一个sum来维护子树的大小。

开两颗lct，询问的时候直接输出根节点右儿子的sum，翻转就是先再一颗lct里把它删掉再再另一颗lct里加上去

代码：

```cpp
#include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
#define ll long long
using namespace std;

const ll N=100010;
ll n,m,fa[N],colour[N];
ll ver[N<<1],Next[N<<1],head[N],tot;

inline ll read(){
	ll x=0,tmp=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-') tmp=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<3)+(x<<1)+(ch^48);
		ch=getchar();
	}
	return tmp*x;
}

inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	ll y=10,len=1;
	while(y<=x){
		y=(y<<3)+(y<<1);
		len++;
	}
	while(len--){
		y/=10;
		putchar(x/y+48);
		x%=y;
	}
}

inline void addEdge(ll x,ll y){
	ver[++tot]=y;
	Next[tot]=head[x];
	head[x]=tot;
}

struct LCT{
	struct Link_Cut_tree{
		ll son[2],father,sum,size;
	}tree[N];
	LCT(){for(ll i=1; i<N; i++) tree[i].sum=1;}
	
	inline void pushup(ll p){
		tree[p].sum=tree[tree[p].son[0]].sum+tree[tree[p].son[1]].sum+tree[p].size+1;
	}
	
	inline bool isroot(ll p){
		return tree[tree[p].father].son[0]!=p&&tree[tree[p].father].son[1]!=p;
	}
	
	inline bool which(ll p){
		return tree[tree[p].father].son[1]==p;
	}
	
	inline void rotate(ll p){
		ll fa=tree[p].father,fafa=tree[fa].father;
		bool w=which(p);
		if(!isroot(fa)) tree[fafa].son[which(fa)]=p;
		tree[fa].son[w]=tree[p].son[w^1];
		tree[tree[p].son[w^1]].father=fa;
		tree[p].son[w^1]=fa;
		tree[fa].father=p;
		tree[p].father=fafa;
		pushup(fa); pushup(p);
	}
	
	inline void splay(ll p){
		for(ll i=tree[p].father; !isroot(p); rotate(p),i=tree[p].father){
			if(!isroot(i)){
				if(which(i)==which(p)) rotate(i);
				else rotate(p);
			}
		}
		pushup(p);		
	}
	
	inline void access(ll p){
		for(ll y=0; p; p=tree[y=p].father){
			splay(p);
			tree[p].size+=tree[tree[p].son[1]].sum;
			tree[p].size-=tree[tree[p].son[1]=y].sum;
			pushup(p);
		}
	}
	
	inline ll getroot(ll p){
		access(p);
		splay(p);
		while(tree[p].son[0]) p=tree[p].son[0];
		splay(p);
		return p;
	}
	
	inline void makeroot(ll p){
		access(p);
		splay(p);
	}
	
	inline void split(ll x,ll y){
		makeroot(x);
		access(y);
		splay(y);
	}
	
	inline void link(ll p){
		access(p);
		splay(p);
		ll y=tree[p].father=fa[p];
		access(y); splay(y);
		tree[y].size+=tree[p].sum;
		tree[y].sum+=tree[p].sum;
	}
	
	inline void cut(ll p){
		access(p); splay(p);
		tree[p].son[0]=tree[tree[p].son[0]].father=0;
		pushup(p);
	}
}lct[2];

void dfs(ll x){
	for(ll i=head[x]; i; i=Next[i]){
		ll y=ver[i];
		if(y==fa[x]) continue;
		fa[y]=x;
		dfs(y);
		lct[0].link(y);
	}
}

int main(){
	n=read();
	for(ll i=1; i<n; i++){
		ll x=read(),y=read();
		addEdge(x,y);
		addEdge(y,x);
	}
	dfs(1);
	fa[1]=n+1; lct[0].link(1);
	m=read();
	while(m--){
		ll op=read(),x=read();
		switch(op){
			case 0:{
				ll y=lct[colour[x]].getroot(x);
				write(lct[colour[x]].tree[lct[colour[x]].tree[y].son[1]].sum); putchar('\n');
				break;
			}
			case 1:{
				lct[colour[x]].cut(x);
				colour[x]^=1;
				lct[colour[x]].link(x);
				break;
			}
		}
	}
	return 0;
}
```

---

## 作者：liujiaxi123456 (赞：0)

## 关键词：
### 抽象题意：
树上待修单点所在连通块大小。
### 思路：
显然，一个连通块的答案可以记录在最上方的一个点上。

若我们把 $u$ 的子树内的连通块大小记录在 $u$ 上。

查询 $u$ 时的答案即为一条与 $u$ 同色的链最上方的点的答案。

由于颜色只有两种，可以建两棵树，每个点的答案记录**假设**当前点为白/黑的子树连通块大小。

而我们显然可以使用重链剖分。

所以我们现在需要维护一条链上的一个点，能连续达到最上方的同色点（同上），考虑如何在线段树上查询。

1. 若查询的 $u$ 在当前区间的左儿子，直接进去。
2. 若在右儿子，判断右儿子从左端开始一直同色的长度有没有超过 $u$，有则进左儿子，否则进右儿子。

再来考虑修改带来的影响。

显然为 $u$ 向上的链中与 $u$ 联通的所有点的 $ans' = ans+\Delta ans_u$，当然可以线段树整体操作。

交换两颗树上的 $ans_u$ 即可。

时间按复杂度：$O(N\log^2{N})$。
### 优化：
1. 对于 $ans$ 的查询，可以树上差分。
2. 在树剖向上爬时，记录链上最浅的白/黑点，在查询时，先判断在不在区间里，只会进行一次线段树查询。
3. 线段树查询可以用 set 实现。

时间复杂度：$O(N\log{N})$。

---

## 作者：cike_bilibili (赞：0)

#  QTREE6 题解
动态维护同色联通块大小，考虑每个颜色开一个 LCT。当反转一个节点颜色时，显然不可以依次断开周围的每条边。由于树上每个节点只有一个父亲，所以只需要断开与父亲的边，在另外一个颜色的 LCT 上重新连上，统计实儿子的答案，也就是子树大小就行了。

Tip：进行换根操作时只需要 Access 与 Splay 即可，因为树的形态是固定的，不能进行真正的换根。

# AC CODE
```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read(){
	int ans=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')w=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		ans=(ans<<1)+(ans<<3)+ch-'0';
		ch=getchar();
	}
	return w*ans;
} 
int col[100005];
int fa[100005];
struct edge{
	int to;
	int next;
}ed[200005];
int cnt;
int h[100005];
void add(int x,int y){
	ed[++cnt]={y,h[x]};
	h[x]=cnt;
}
void dfs(int x,int f){
	fa[x]=f;
	for(int i=h[x];i;i=ed[i].next){
		int v=ed[i].to;
		if(v==f)continue;
		dfs(v,x);
	}
}
int n,m;
struct link_cut_tree{
	struct tree{
		int ch[2];
		int fa;
		int sz;
		int si;
		bool lazy;
		int id;
	}tree[300005];
	inline bool isroot(int x){
		if(tree[tree[x].fa].ch[0]!=x&&tree[tree[x].fa].ch[1]!=x)return 1;
		return 0;
	}
	inline void pushup(int i){
		tree[i].sz=tree[i].si+tree[tree[i].ch[0]].sz+tree[tree[i].ch[1]].sz+1;
	}
	inline bool get(int x){
		return tree[tree[x].fa].ch[1]==x;
	}
	inline void pushdown(int x){
		if(tree[x].lazy){
			if(tree[x].ch[0]){
				tree[tree[x].ch[0]].lazy^=1;
				swap(tree[tree[x].ch[0]].ch[0],tree[tree[x].ch[0]].ch[1]);	
			}
			if(tree[x].ch[1]){
				tree[tree[x].ch[1]].lazy^=1;
				swap(tree[tree[x].ch[1]].ch[0],tree[tree[x].ch[1]].ch[1]);
			}
			tree[x].lazy=0;
		}
	}
	void update(int x){
		if(!isroot(x))update(tree[x].fa),tree[x].fa=tree[x].fa;
		pushdown(x);
	}
	inline void rotate(int x){
		int p=tree[x].fa,q=tree[p].fa,chk=get(x);
		if(!isroot(p))tree[q].ch[p==tree[q].ch[1]]=x;
		tree[p].ch[chk]=tree[x].ch[!chk];
		tree[tree[x].ch[!chk]].fa=p;
		tree[x].ch[!chk]=p;
		tree[p].fa=x;
		tree[x].fa=q;
		pushup(p),pushup(x);
	}
	inline void splay(int x){
		update(x);
		for(int f=tree[x].fa;!isroot(x);rotate(x),f=tree[x].fa){
			if(!isroot(tree[x].fa))rotate(get(f)==get(x)?f:x);
		}
	}
	inline void access(int x){
		int p;
		for(p=0;x;p=x,x=tree[x].fa){
			splay(x);
			if(p)tree[x].si-=tree[p].sz;
			if(tree[x].ch[1])tree[x].si+=tree[tree[x].ch[1]].sz;
			tree[x].ch[1]=p;
			pushup(x);
		}
	}
	inline void makeroot(int x){
		access(x);
		splay(x);
	}
	inline int find(int x){
		access(x);
		splay(x);
		pushdown(x);
		while(tree[x].ch[0])x=tree[x].ch[0],pushdown(x);
		splay(x);
		return x; 
	}
	void link(int x,int y){
		makeroot(x);
		access(y);
		splay(y);
		tree[x].fa=y;
		tree[y].si+=tree[x].sz;
	}
	inline void cut(int x,int y){
		makeroot(x);
		tree[tree[x].ch[0]].fa=0;
		tree[x].ch[0]=0;
		pushup(x);
	}
}t[2];
signed main(){
	n=read();
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		add(x,y);
		add(y,x);
	}
	dfs(1,0); 
	for(int i=2;i<=n;i++){
		t[0].link(i,fa[i]);
	}
	fa[1]=n+1;
	t[0].link(1,n+1);
	m=read();
	while(m--){
		int opt=read(),u=read();
		if(opt==1){
			t[col[u]].cut(u,fa[u]);
			col[u]=!col[u];
			t[col[u]].link(u,fa[u]);
		}
		else{
			int rt=t[col[u]].find(u);
			printf("%d\n",t[col[u]].tree[t[col[u]].tree[rt].ch[1]].sz);
		}
		
	}
	return 0;
}
```

---

## 作者：SrsgPrince_ (赞：0)

# QTREE6 - Query on a tree VI 题解

题面传送门：[QTREE6 - Query on a tree VI](https://www.luogu.com.cn/problem/SP16549)。

另：在 [博客](https://www.luogu.com.cn/blog/fy123333/SP16549Solution) 里查看观感最佳。

## 题目分析 Hint

QTree 系列的题目就是让你用 Link-Cut Tree 做的。那么我们来看具体怎么用 LCT 完成题目中的操作。

题目中有两个操作：

1.  `0 u`：询问有多少个节点 $v$ 满足路径 $u$ 到 $v$ 上所有节点（包括 $u$）都拥有相同的颜色。
2. `1 u`：翻转 $u$ 的颜色。

其中第一个操作就是维护颜色相同的连通块的大小。第二种就是改颜色。

## 思路 Solution

第一个操作可以拆分为维护大小和维护连通块，维护大小很简单，在下面 LCT 的介绍中会讲到，那么维护连通块怎么做呢？首先是暴力做法，每次更改时暴力修改父边和子边，即 $\operatorname{Cut()}$ 后再 $\operatorname{Link()}$。但是这种做法来一个菊花图直接暴毙。这时候我们换一种思路，把点权转化为边权，那么我们就可以开两颗 LCT，一棵是存白的，一棵存黑的，一条边只有在对应颜色的 LCT 中才会被连上。修改一个点的颜色之后，只要在原来颜色对应 LCT 中断掉父边，再在新颜色对应LCT中连接父边，询问的时候先 $\operatorname{findRoot()}$，然后再输出它重子树的大小就行了。复杂度为 $O(n \log n)$

思路有了之后来介绍一下 Link-Cut Tree。

Link-Cut Tree 是用来解决动态树的问题的，动态树问题通常有这几个操作：
    
1. 修改两点间路径权值。
2. 查询两点间路径权值和。
3. 修改某点子树权值。
4. 查询某点子树权值和。
5. 在线断开并连接一些边，保证仍是一棵树。

简单一点就是维护一个森林，支持删除某条边，加入某条边，并保证加边，删边之后仍是森林。我们要维护这个森林的一些信息。

LCT 中需要进行剖分，这里我们并不选择常见的重链，也不选择奇奇怪怪的 DAG 链，我们选择 **实链剖分**。

先说一下实链是什么：对于一个点连向它所有儿子的边，我们自己选择一条边进行剖分，我们称被选择的边为实边，其他边则为虚边。对于实边，我们称它所连接的儿子为实儿子。对于一条由实边组成的链，我们同样称之为实链。选择实链的原因是，我们可以自己指定需要的链，那么这样便于我们进行求解。

我们可以简单的把 LCT 理解成用一些 Splay 来维护动态的树链剖分，以期实现动态树上的区间操作。对于每条实链，我们建一个 Splay 来维护整个链区间的信息。

在 LCT 中，我们需要辅助树，每棵辅助树维护的是一棵树，一些辅助树构成了 LCT，其维护的是整个森林。

1. 辅助树由多棵 Splay 组成，每棵 Splay 维护原树中的一条路径，且中序遍历这棵 Splay 得到的点序列，从前到后对应原树「从上到下」的一条路径。
2. 原树每个节点与辅助树的 Splay 节点一一对应。
3. 辅助树的各棵 Splay 之间并不是独立的。每棵 Splay 的根节点的父亲节点本应是空，但在 LCT 中每棵 Splay 的根节点的父亲节点指向原树中 **这条链** 的父亲节点。这类父亲链接与通常 Splay 的父亲链接区别在于儿子认父亲，而父亲不认儿子，对应原树的一条虚边。因此，每个连通块恰好有一个点的父亲节点为空。
4. 由于辅助树的以上性质，我们维护任何操作都不需要维护原树，辅助树可以在任何情况下拿出一个唯一的原树，我们只需要维护辅助树即可。

接下来是具体的函数写法：

先给一些函数的具体写法

1. $\operatorname{pushUp()}$

```cpp
inline void pushUp(int p) {
    siz[p] = siz[lson] + siz[rson] + 1;
}
```

2. $\operatorname{pushDown()}$

```cpp
inline void pushDown(int p) {
    if(tag[p] != stdTag) {
        // 下放标签
        tag[p] = stdTag;
    }
}
```

这俩都很简单，正常的树里也有，接下来是 LCT 特有的。

3. $\operatorname{nRoot()}$ 或 $\operatorname{isRoot()}$

都是判断是否是它的根的，只不过是习惯的问题。

```cpp
inline bool nRoot(int x) {
    return chd[f[x]][0] == x || chd[f[x]][1] == x;
}
inline bool isRoot(int x) {
    return chd[f[x]][0] != x && chd[f[x]][1] != x;
}
```

4. $\operatorname{Splay()}$ && $\operatorname{Rotate()}$

这两个函数都是 Splay 里的，因为我们是用它来维护的，所以有 Splay 的函数，不过会有一些修改。

```cpp
inline void rotate(int x) {
    int y = f[x], z = f[y], k = chd[y][1] == x, w = chd[x][!k];
	if (nRoot(y)) // if (!isRoot(y))
        chd[z][chd[z][1] == y] = x;
    chd[x][!k] = y;
    chd[y][k] = w;
	f[w] = y; f[y] = x; f[x] = z;
	pushUp(y);
}
inline void splay(int x) {
    int y;
    while (nRoot(x)) /*while (!isRoot(x))*/ { 
        if (nRoot(y = f[x])) // if (!isRoot(y = f[x]))
            rotate((chd[f[y]][0] == y) ^ (chd[y][0] == x) ? x : y);
        rotate(x);
    }
    pushUp(x);
}
```

5. $\operatorname{Access()}$

```cpp
// Access 是 LCT 的核心操作，试想我们像求解一条路径，而这条路径恰好就是我们当前的一棵 Splay，直接调用其信息即可。先来看一下代码，再结合图来看看过程
inline void access(int x) {
    for (int y = 0; x; y = x, x = f[x]) {
        splay(x);
        rt[x] += s[chd[x][1]];
        rt[x] -= s[chd[x][1] = y];
    }
}
```

6. $\operatorname{findRoot()}$

```cpp
inline int findRoot(int x) {
    access(x), splay(x);
    while (chd[x][0]) x = chd[x][0];
    splay(x);
    return x;
}
```

7. $\operatorname{Link()}$

```cpp
inline void link(int x) { // 只用连接父边，所以只用传一个参数
    splay(x);
    int y = f[x] = fa[x];
    access(y), splay(y);
    rt[y] += s[x];
    s[y] += s[x];
}
```

8. $\operatorname{Cut()}$

```cpp
inline void cut(int x) {
    access(x), splay(x);
    chd[x][0] = f[chd[x][0]] = 0;
    pushUp(x);
}
```

除此之外，还有一些这题用不到的一些函数，不过它们确实是模板。

9. $\operatorname{makeRoot()}$

```cpp
inline void makeRoot(int x) {
    access(x);
    swap(chd[x][0], chd[x][1]);
    tag[x] ^= 1;
}
```

10. $\operatorname{update()}$

```cpp
inline void update(int x) {
    // 所有的函数内容写在这里
}
```

再根据上面我们的思路，可以写出下面的代码。

```cpp
struct LinkCutTree {
    int f[maxn], chd[maxn][2], rt[maxn], s[maxn];
    bool r[maxn];
    LinkCutTree() {
        for (int i = 1; i < maxn; ++i)
            s[i] = 1;
    }
    inline bool nRoot(int x) {
        return chd[f[x]][0] == x || chd[f[x]][1] == x;
    }
    inline void pushUp(int x) {
        s[x] = s[chd[x][0]] + s[chd[x][1]] + rt[x] + 1;
    }
    inline void rotate(int x) {
        int y = f[x], z = f[y], k = chd[y][1] == x, w = chd[x][!k];
		if (nRoot(y))
            chd[z][chd[z][1] == y] = x;
        chd[x][!k] = y;
        chd[y][k] = w;
		f[w] = y; f[y] = x; f[x] = z;
		pushUp(y);
    }
    inline void splay(int x) {
        int y;
        while (nRoot(x)) {
            if (nRoot(y = f[x]))
                rotate((chd[f[y]][0] == y) ^ (chd[y][0] == x) ? x : y);
            rotate(x);
        }
        pushUp(x);
    }
    inline void access(int x) {
        for (int y = 0; x; y = x, x = f[x]) {
            splay(x);
            rt[x] += s[chd[x][1]];
            rt[x] -= s[chd[x][1] = y];
        }
    }
    inline int findRoot(int x) {
        access(x), splay(x);
        while (chd[x][0]) x = chd[x][0];
        splay(x);
        return x;
    }
    inline void link(int x) {
        splay(x);
        int y = f[x] = fa[x];
        access(y), splay(y);
        rt[y] += s[x];
        s[y] += s[x];
    }
    inline void cut(int x) {
        access(x), splay(x);
        chd[x][0] = f[chd[x][0]] = 0;
        pushUp(x);
    }
}lct[2];
inline void dfs(int x) {
    for (int y, i = head[x]; i; i = nxt[i]) 
        if ((y = des[i]) != fa[x])
            fa[y] = x, dfs(y), lct[0].link(y);
}
int main() {
    char ch;
    int p = 1, n, m, u, v, opt;
    n = quickRead();
    for (int i = 1; i < n; ++i) {
        u = quickRead(), v = quickRead();
        des[++p] = v, nxt[p] = head[u], head[u] = p;
        des[++p] = u, nxt[p] = head[v], head[v] = p;
    }
    dfs(1);
    fa[1] = n + 1;
    lct[0].link(1);
    m = quickRead();
    while (m--) {
        opt = quickRead(), u = quickRead();
        if (opt) lct[col[u]].cut(u), lct[col[u] ^= 1].link(u);
        else {
            v = lct[col[u]].findRoot(u);
            quickWrite(lct[col[u]].s[lct[col[u]].chd[v][1]], '\n');
        }
    }
    return 0;
}
```

现在你学会这道题怎么用 LCT 做了，但是还有一种做法，几乎是 LCT 通用的，我们刚才在 LCT 的介绍部分说过了，我们需要实链剖分，那我们自然也可以用重链剖分做，只不过不太一样。

思路是 首先从 $fa_x$ 向上找到第一个白点 $u$，如果找不到则 $u=root$，将路径 $fa_x \rightarrow u$ 上的所有点（包含端点）的 $b$ 值减去 $bx$。然后从 $fa_x$ 向上找到第一个黑点 $u$，找不到则 $u=root$，将路径 $fa_x \rightarrow u$ 上的所有点的 $w$ 值加上 $wx$。复杂度为 $O(m \log {n})$。


---

## 作者：黑影洞人 (赞：0)

题面：

>给你一棵树，每个节点有黑白颜色，最开始默认黑色，每次查询求多少个节点到x的路径上所有节点的颜色都和x一样，支持颜色翻转操作。

首先如果没有操作1，我们可以直接树形 DP 统计然后询问。

颜色带修，说明支持动态修改，考虑 LCT。

使用 LCT 维护子树信息，要维护实链和虚子树。

对于每个节点 $x$ ，维护 $siz$ (以 $x$ 为根的子树大小)和 $zs$ (以 $x$ 为根的虚子树大小)

显然，$siz$ 的值可以用子节点向上维护。

$$siz_x=siz_{lc}+siz_{rc}+zs_x+1$$

剩下的就是细节了，因为每个节点都要有一个向上连接父节点的边，因此建立一个虚节点作为 $1$ 的父节点。

```cpp
#include<cstdio>
#include<algorithm>
#define N 214514
using namespace std;
int n,m;
int f[N],col[N]; 
int head[N],to[N],nxt[N],tot;
void add(int u,int v){
	to[++tot]=v;
	nxt[tot]=head[u];
	head[u]=tot;
}
struct link_cut_tree{
	int ch[N][2],f[N],siz[N],zs[N];
	#define lc ch[x][0]
	#define rc ch[x][1]
	int son(int x){return x==ch[f[x]][1];}
	int nroot(int x){return x==ch[f[x]][0]||x==ch[f[x]][1];}
	void pushup(int x){siz[x]=siz[lc]+siz[rc]+zs[x]+1;}
	void rotate(int x){
		int y=f[x],z=f[y],k=son(x),w=ch[x][!k];
		if(nroot(y))ch[z][son(y)]=x;
		ch[x][!k]=y,ch[y][k]=w;
		if(w)f[w]=y;
		f[x]=z,f[y]=x;
		pushup(y);pushup(x);
	}
	void splay(int x){
		while(nroot(x)){
			int y=f[x];
			if(nroot(y))rotate(son(x)!=son(y)?x:y);
			rotate(x);
		}
		pushup(x);
	}
	void access(int x){
		for(int y=0;x;x=f[y=x]){
			splay(x);
			zs[x]+=siz[rc];
			zs[x]-=siz[rc=y];
			pushup(x);
		}
	}
	void makeroot(int x){access(x),splay(x);}
	int findroot(int x){
		makeroot(x);
		while(lc)x=lc;
		splay(x);
		return x;
	}
	void link(int x,int y){
		makeroot(x);
		f[x]=y;
		makeroot(y);
		zs[y]+=siz[x];
		siz[y]+=siz[x];
	}
	void cut(int x,int y){makeroot(x);lc=f[lc]=0;pushup(x);}
}lct[2];
void dfs(int x,int fa){
	for(int i=head[x];i;i=nxt[i]){
		int y=to[i];
		if(y==fa)continue;
		f[y]=x;
		dfs(y,x);
		lct[col[y]].link(y,x);
	}
}
signed main(){
	scanf("%d",&n);
	for(int i=1;i<N;i++)lct[0].siz[i]=lct[1].siz[i]=1;
	for(int i=1;i<n;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		add(u,v);
		add(v,u);
	}
	scanf("%d",&m);
	for(int i=1;i<=n+1;i++)col[i]=1;
	dfs(1,0);
	f[1]=n+1;lct[1].link(1,n+1);
	while(m--){
		int op,x;
		scanf("%d%d",&op,&x);
		if(op==0){
			int rt=lct[col[x]].findroot(x);
			int ans=lct[col[x]].siz[lct[col[x]].ch[rt][1]];
			printf("%d\n",ans);
		}else{
			lct[col[x]].cut(x,f[x]);
			col[x]^=1;
			lct[col[x]].link(x,f[x]);
		}
	}
	return 0;
}



```


---

## 作者：FutaRimeWoawaSete (赞：0)

LCT 基础套路之维护黑白染色块。               

默认大家都会 LCT 维护子树信息了。

我们考虑一个比较显然的想法：我两棵 LCT 一棵维护黑色一棵维护白色，然后每次就直接树上联通块查点数就好了。               

不过这样改点的话就会导致一次可能改很多条边，时间复杂度直接爆炸！      

考虑树剖里面的一个常见套路：点挂边。        

随便指定一个点为 $rt$，我们直接把点的颜色放到父亲与它的边上去每次就只有一条边被改动，对 $rt$ 开个虚根就可以保证所有连接都合法。         

不难通过观察发现，这样的话我们只需要把连通块内的根带来的影响（连接了其他子树）给清除就好了。               

这个不难，直接在连边和删边时不要改根，查询时直接找当前的根翻上去后再打通一下查询点 $x$ ，根的右儿子就是实际连通块的根。        

时间复杂度 $O(n \log n)$。

```cpp
#include "bits/stdc++.h"
using namespace std;
const int Len = 2e5 + 5;
int n,m,col[Len],head[Len],cnt,fa[Len],dep[Len];
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
struct SSplay
{
	int ch[2],f,rev,pre;
	int sz,szl,szc;
};
struct LLCT
{
	SSplay t[Len];
	void push_up(int x)
	{
		t[x].pre = t[x].ch[0] ? t[t[x].ch[0]].pre : x;
		t[x].sz = t[t[x].ch[0]].sz + t[t[x].ch[1]].sz + t[x].szl + 1;
		t[x].szc = t[t[x].ch[0]].szc + t[t[x].ch[1]].szc + 1;
	}
	void push_rev(int x)
	{
		if(!x) return;
		swap(t[x].ch[0] , t[x].ch[1]) , t[x].rev ^= 1;
	}
	void push_down(int x)
	{
		if(t[x].rev)
		{
			push_rev(t[x].ch[0]);
			push_rev(t[x].ch[1]);
			t[x].rev = 0;
		}
	}
	int idf(int x)
	{
		if(!t[x].f) return -1;
		if(t[t[x].f].ch[0] == x) return 0;
		if(t[t[x].f].ch[1] == x) return 1;
		return -1; 
	}
	void llcon(int son,int x,int op)
	{
		if(op == 0) t[x].ch[0] = son;
		if(op == 1) t[x].ch[1] = son;
		t[son].f = x;
	}
	void rotate(int x)
	{
		int y = t[x].f , z = t[y].f , opx = idf(x) , opy = idf(y) , u = t[x].ch[opx ^ 1];
		llcon(u , y , opx);
		llcon(y , x , opx ^ 1);
		llcon(x , z , opy);
		push_up(y) , push_up(x);
	}
	void push_all(int x)
	{
		if(idf(x) != -1) push_all(t[x].f);
		push_down(x);
	}
	void Splay(int x)
	{
		push_all(x);
		while(idf(x) != -1)
		{
			int y = t[x].f;
			if(idf(y) == -1) rotate(x);
			else
			{
				if(idf(x) == idf(y)) rotate(y) , rotate(x);
				else rotate(x) , rotate(x);
			}
		}
	}
	void access(int x)
	{
		int lst = 0 , z;
		while(x)
		{
			Splay(x) , z = t[x].ch[1];
			t[x].szl -= t[lst].sz;
			t[x].szl += t[z].sz;
			t[x].ch[1] = lst;
			push_up(x);
			lst = x;
			x = t[x].f;
		}
	}
	void makeroot(int x)
	{
		access(x);
		Splay(x);
		push_rev(x);
	}
	int findroot(int x)
	{
		access(x);
		Splay(x);
		int u = x;
		while(t[u].ch[0]) u = t[u].ch[0];
		return u;
	}
	void link(int x,int y)//保证当前节点一定得是树根 
	{
		Splay(y);
		access(x) , Splay(x);
		//printf("%d %d %d %d %d %d\n",x,y,t[x].sz,t[y].sz,t[x].szl,t[y].szl);
		t[x].ch[1] = y , t[y].f = x;
		push_up(x);
		//printf("%d %d %d %d %d %d\n",x,y,t[x].sz,t[y].sz,t[x].szl,t[y].szl);
		//printf("%d\n",findroot(x));
	}
	void cut(int x,int y)
	{
		access(y) , Splay(x);
		t[x].ch[1] = 0 , t[y].f = 0;
		push_up(x);
	}
	int ask(int x)
	{
		int rt = findroot(x);
		access(rt) , Splay(rt);
		access(x);
		return t[t[rt].ch[1]].sz;
	}
}LCT[2];
void dfs(int x,int f)
{
	fa[x] = f;
	dep[x] = dep[f] + 1;
	for(int e = head[x] ; e ; e = edge[e].next)
	{
		int to = edge[e].to;
		if(to == f) continue;
		dfs(to , x);
	}
}
int main()
{
	scanf("%d",&n);
	for(int i = 1 ; i < n ; i ++) 
	{
		int x,y;scanf("%d %d",&x,&y);
		add(x , y) , add(y , x);
	}
	add(n + 1 , 1);
	dfs(n + 1 , 0);
	for(int i = 1 ; i <= n + 1 ; i ++) LCT[0].push_up(i) , LCT[1].push_up(i);
	for(int i = 1 ; i <= n ; i ++) LCT[col[i]].link(fa[i] , i);
	scanf("%d",&m);
	int opt,x;
	for(int i = 1 ; i <= m ; i ++)
	{
		scanf("%d %d",&opt,&x);
		if(opt == 0) printf("%d\n",LCT[col[x]].ask(x));
		else 
		{
			LCT[col[x]].cut(fa[x] , x);
			col[x] ^= 1;
			LCT[col[x]].link(fa[x] , x);
		}
	} 
	return 0;
}
```

---

