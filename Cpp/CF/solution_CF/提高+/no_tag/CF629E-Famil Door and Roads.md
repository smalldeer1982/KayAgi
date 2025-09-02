# Famil Door and Roads

## 题目描述

Famil Door’s City map looks like a tree (undirected connected acyclic graph) so other people call it Treeland. There are $ n $ intersections in the city connected by $ n-1 $ bidirectional roads.

There are $ m $ friends of Famil Door living in the city. The $ i $ -th friend lives at the intersection $ u_{i} $ and works at the intersection $ v_{i} $ . Everyone in the city is unhappy because there is exactly one simple path between their home and work.

Famil Door plans to construct exactly one new road and he will randomly choose one among $ n·(n-1)/2 $ possibilities. Note, that he may even build a new road between two cities that are already connected by one.

He knows, that each of his friends will become happy, if after Famil Door constructs a new road there is a path from this friend home to work and back that doesn't visit the same road twice. Formally, there is a simple cycle containing both $ u_{i} $ and $ v_{i} $ .

Moreover, if the friend becomes happy, his pleasure is equal to the length of such path (it's easy to see that it's unique). For each of his friends Famil Door wants to know his expected pleasure, that is the expected length of the cycle containing both $ u_{i} $ and $ v_{i} $ if we consider only cases when such a cycle exists.

## 说明/提示

Consider the second sample.

1. Both roads $ (1,2) $ and $ (2,3) $ work, so the expected length if ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF629E/2870a27a99e49b2e86fafede38ebc7cc8463668d.png)
2. Roads $ (1,3) $ and $ (2,3) $ make the second friend happy. Same as for friend $ 1 $ the answer is $ 2.5 $
3. The only way to make the third friend happy is to add road $ (2,3) $ , so the answer is $ 3 $

## 样例 #1

### 输入

```
4 3
2 4
4 1
3 2
3 1
2 3
4 1
```

### 输出

```
4.00000000
3.00000000
3.00000000
```

## 样例 #2

### 输入

```
3 3
1 2
1 3
1 2
1 3
2 3
```

### 输出

```
2.50000000
2.50000000
3.00000000
```

# 题解

## 作者：LlLlCc (赞：7)

求期望首先要知道，**期望长度$=$总长度/环数**

我们先来考虑如何找环

因为树上的简单路径只有一条，所以我们连边$(x\rightarrow y)$使得$a,b$在环上，就等于树上找两点$x\rightarrow y$的路径经过$a,b$两点

这时我们就要分类讨论了

- $a$不是$b$的祖先节点且$b$也不为$a$的祖先节点

![](https://cdn.luogu.com.cn/upload/image_hosting/zis7zf5o.png)

显然，$x$只能取$a$的子树节点（包括$a$），$y$只能取$b$的子树结点（包括$b$）

**乘法原理：环数$\large=size_a\times  size_b$**

接下来就想怎么求这个环的长度了

首先不管$x,y$取在哪，$a\rightarrow b$和$x\rightarrow y$是必走的，即

$Dep_a-Dep_{LCA}+Dep_b-Dep_{LCA}+1$

其中$Dep$为在树中的深度

答案可以直接加上：$size_a\times  size_b\times  (Dep_a+Dep_b-2\times  Dep_{LCA}+1)$

然后就是求$x\rightarrow a$和$y\rightarrow b$的距离，即

$Dep_x-Dep_a+Dep_y-Dep_b$

然后发现这个其实是可以$Dfs$预处理对于每个节点其所有子树结点到该点的距离和

设：$\large s_x$为结点$x$的所有子树节点到$x$的距离和

$\large s_x=\sum\limits s_{son}+size_{son}$

- $a$为$b$的祖先节点或$b$为$a$的祖先节点

![](https://cdn.luogu.com.cn/upload/image_hosting/wzjm07mk.png)

这要比上一种要复杂一些

我们假设$a$为$b$的祖先

和之前有些不同，$y$依然是$b$的子树节点，但$x$则有些变化

因为要求$x \rightarrow y$要经过$a,b$两点，所以$x$不能取
$b$所在$a$子树的子树节点（即$c$的子树节点都不能取，其他节点都行）

所以：**环数$\large =size_b\times  (n-size_c)$**

同样的，$a \rightarrow b$和$x \rightarrow y$必走

答案可以直接加上：$size_b\times  (n-size_c)\times (Dep_b-Dep_a+1)$

因为$y \rightarrow b$和之前求法一样，就是$\large s_b$

所以我们只要考虑$x \rightarrow a$和$y \rightarrow b$就好了

和之前的想法类似，我们可以$Dfs$预处理一遍

不妨设$G_x$为所有节点到$x$点的距离和

根据定义：$\large G_{root}=\sum\limits_{i=1}^n Dep_i$

从根节点往下推，因为中心点往推到了子节点，所以对于子节点的所有子树节点距离$-1$，对于其他节点距离$+1$

$\large G_{son}=G_x-size_{son}+(n-size_{son})$

但我们发现，这样算还把节点$c$的子树节点的距离贡献算进去了，所以我们还要再减去$\large s_c$

详见代码：
```
#include<bits/stdc++.h>
#define maxn 1000005
#define ll long long
using namespace std;
int Q[1005],t,n,m,x,y,a,b,fa[maxn][20],Dep[maxn],lnk[maxn],nxt[maxn],son[maxn],tot;
ll Ans,s[maxn],si[maxn],S[maxn];
inline int read(){
	int ret=0;char ch=getchar();
	while (ch<'0'||ch>'9') ch=getchar();
	while (ch<='9'&&ch>='0') ret=ret*10+ch-'0',ch=getchar();
	return ret;
}
inline void add(int x,int y){nxt[++tot]=lnk[x];lnk[x]=tot;son[tot]=y;}
inline void Dfs1(int x){
	si[x]=1;
	for (int i=1;i<20;i++) fa[x][i]=fa[fa[x][i-1]][i-1];
	for (int i=lnk[x];i;i=nxt[i])
	  if (son[i]!=fa[x][0]) Dep[son[i]]=Dep[x]+1,fa[son[i]][0]=x,Dfs1(son[i]),si[x]+=si[son[i]],S[x]+=S[son[i]]+si[son[i]];
}
inline void Dfs2(int x){
	for (int i=lnk[x];i;i=nxt[i])
	  if (son[i]!=fa[x][0]) s[son[i]]=s[x]-2*si[son[i]]+n,Dfs2(son[i]);
}
inline int LCA(int x,int y){
	if (Dep[x]<Dep[y]) swap(x,y);
	int fx=x,fy=y;
	for (int i=19;i>=0;i--) if (Dep[fa[fx][i]]>=Dep[fy]) fx=fa[fx][i];
	if (fx==fy) return fx;
	for (int i=19;i>=0;i--) if (fa[fx][i]^fa[fy][i]) fx=fa[fx][i],fy=fa[fy][i];
	return fa[fx][0];
}
inline int Get(int x){
	for (int i=19;i>=0;i--) if (Dep[fa[x][i]]>Dep[y]) x=fa[x][i];
	return x;
}
int main(){
	n=read(),m=read();
	for (int i=1;i<n;i++) x=read(),y=read(),add(x,y),add(y,x);
	Dep[1]=1;Dfs1(1);for (int i=2;i<=n;i++) s[1]+=Dep[i]-1;Dfs2(1);
	for (int i=1;i<=m;i++){
		x=read(),y=read();
		if (x==y){printf("0.00000000\n");continue;}
		int top=LCA(x,y);Ans=0;
	    if (top^x&&top^y){
	    	ll len=1+Dep[x]+Dep[y]-2*Dep[top];
	    	Ans+=(ll)len*si[x]*si[y];
	    	Ans+=(ll)S[x]*si[y]+(ll)(S[y]*si[x]);
         	printf("%.8lf\n",(double)Ans/(si[x]*si[y]));
		}
		else{
			if (Dep[x]<Dep[y]) swap(x,y);
			top=Get(x);
			ll len=1+Dep[x]-Dep[y];
			Ans+=(ll)len*si[x]*(n-si[top]);
			Ans+=(ll)(s[y]-S[top]-si[top])*si[x]+(ll)S[x]*(n-si[top]);
         	printf("%.8lf\n",(double)Ans/(si[x]*(n-si[top])));
		}
	}
	return 0;
}
```


---

## 作者：Neutralized (赞：4)

这里提供一个智障且复杂度不优的写法，大家就当看个笑话吧。  
~~如果真的有人愿意写这个方法，那就祝您好运~~
***
显然这个 $a$，$b$ 都在环上是一个很好的约束，同时也说明此环一定包含 $a \to \operatorname{LCA}(a,b) \to b$ 这部分。也就是说，我们只需要考虑拼接的另一部分的期望长度。  

我们据此分情况讨论：  

当两个点不存在祖先关系时（$a \ne \operatorname{LCA}(a,b) \ne b$），$a$，$b$ 都在这个环里的条件是 $S \in subtree_a$，$T \in subtree_b$，其中 $subtree_x$ 表示 $x$ 的子树。  

不难得出此时的答案：  
$$\sum_{x \in subtree_a}\frac{dep_x}{siz_a}+\sum_{x \in subtree_b}\frac{dep_x}{siz_b}+1-2dep_{\operatorname{LCA}(a,b)}$$

因为要从 $a$ 子树中选择一点 $x$，那么期望长度是所有 $x$ 到 $a$ 的距离和除以个数。拆开括号后化简就是这样了。  
这个东西可以一遍 $\operatorname{dfs}$ 预处理，这里不多赘述，有需要可以看代码。  

考虑第二种情况，当 $a$，$b$ 存在祖先关系时，设 $a=\operatorname{LCA}(a,b)$，边的起点应该在 $subtree_b$ 中，而终点是 **除了 $a$ 向 $b$ 延伸的那棵子树之外** 的所有点中的一个。我们设这棵子树为 $T$。  
那么终点（算上连接的这条边）的贡献就是  

$$1+dep_a+\sum_{x \in tree-T}\frac{dep_x-2dep_{\operatorname{LCA}(x,a)}}{n-siz_{T}}$$    
你发现这个就是 [[LNOI2014]LCA](https://www.luogu.com.cn/problem/P4211) 的套路，所以这个 $\sum dep_{\operatorname{LCA}(x,a)}$ 其实就是，全树所有节点向根这条链 $+1$，然后对 $a \to root$ 求和。

但是现在我们有一个限制，就是这个 $x$ 要不在 $T$ 这个子树里，那么就是全树的答案减去 $T$ 子树的答案，显然我们可以转化为 $\operatorname{dfs}$ 序上连续区间解决。  

照搬上面那道题的方法，离线后使用树剖+线段树维护，而且可以顺便支持求 $\operatorname{LCA}$。当然也可以主席树。  

然后就做完了。  
时间复杂度 $O(n \log^2 n)$。  

~~注意上面标黑体的部分，这里没想清楚导致我调了一上午~~  
顺带一提，$\operatorname{dfs}$ 的作用是预处理一堆东西，同时因为要找到这个子树的根，我在树剖之外还写了一个倍增（。  

所以衷心劝告不要写这个写法，图个乐就好了。


```cpp
#include <bits/stdc++.h>
using namespace std;

#define ri register int
#define ll long long
#define Tp template<class T>
#define g() getchar()
#define pc(x) putchar(x)
#define isd(x) (x>=48&&x<=57)
namespace SlowIO{
	Tp inline void rd(T &x){ x=0; char i=g(); bool f=1; while(!isd(i)) f&=(i!='-'),i=g(); while(isd(i)) x=(x<<3)+(x<<1)+(i^48),i=g(); x*=((f<<1)-1); }
	const int OUT=1e6; static char outp[OUT]; int out;
	Tp inline void op(T x){ out=0; x<0&&(x=-x,pc('-')); if(!x){ pc(48); return; } while(x) outp[++out]=x%10+48,x/=10; while(out) pc(outp[out--]); }
	Tp inline void writeln(T x){ op(x);pc('\n'); }
	Tp inline void writesp(T x){ op(x); pc(' '); }
	Tp inline void write(T x,char c=0){ op(x); c&&pc(c); }
}; using namespace SlowIO;

#define N 100003
#define db double
int n,m,head[N],cntr,FA[N][17];
struct edge{ int to,nxt; }e[N<<1];
inline void add(int u,int v){ e[++cntr]={v,head[u]},head[u]=cntr; }
#define gfore(u) for(ri i=head[u],v;i;i=e[i].nxt)
int dfn[N],Dfn,rig[N],son[N],siz[N],fa[N],top[N],dep[N],id[N]; ll sum[N],Sdep[N];
inline void Dfs(int u,int father){
	dep[u]=dep[fa[u]=father]+1,siz[u]=1;
	gfore(u) if((v=e[i].to)!=father)
		Dfs(v,u),siz[u]+=siz[v],
		son[u]=siz[son[u]]<siz[v]?v:son[u];
}
inline void Df4(int u,int tp){
	dfn[u]=rig[u]=++Dfn,id[Dfn]=u,top[u]=tp; if(!son[u]) return; Df4(son[u],tp);
	gfore(u){ v=e[i].to; if(v!=fa[u]&&v!=son[u]) Df4(v,v); } rig[u]=Dfn;
}
inline void Df3(int u){
	FA[u][0]=fa[u]; for(ri i=1;i<=16;++i) FA[u][i]=FA[FA[u][i-1]][i-1];
	++sum[u]; gfore(u) if((v=e[i].to)!=fa[u])
		Df3(v),sum[u]+=sum[v];
}
inline void Df2(int u){
	sum[u]+=sum[fa[u]],Sdep[u]=dep[u];
	gfore(u) if((v=e[i].to)!=fa[u]) Df2(v),Sdep[u]+=Sdep[v];
}
ll val[N<<2]; int tag[N<<2];
#define lef(u) u<<1
#define rig(u) u<<1|1
inline void Get(int u,int l,int r,ll d){ val[u]+=d*(r-l+1),tag[u]+=d; }
inline void Down(int u,int l,int r){ if(!tag[u]) return; ri mid=l+r>>1; Get(lef(u),l,mid,tag[u]),Get(rig(u),mid+1,r,tag[u]),tag[u]=0; }
inline void push(int u){ val[u]=val[lef(u)]+val[rig(u)]; }
inline void Mdf(int u,int l,int r,int L,int R){
	if(L>R) return; if(l>=L&&r<=R) return Get(u,l,r,1); Down(u,l,r); ri mid=l+r>>1;
	if(L<=mid) Mdf(lef(u),l,mid,L,R); if(R>mid) Mdf(rig(u),mid+1,r,L,R); push(u);
}
inline ll Qry(int u,int l,int r,int L,int R){
	if(L>R) return 0; if(l>=L&&r<=R) return val[u]; Down(u,l,r);
	ri mid=l+r>>1; ll t=0; if(L<=mid) t=Qry(lef(u),l,mid,L,R);
	if(R>mid) t+=Qry(rig(u),mid+1,r,L,R); return t;
}
inline int LCA(int a,int b){
	while(top[a]^top[b]){
		if(dep[top[a]]<dep[top[b]]) swap(a,b);
		a=fa[top[a]];
	} return dep[a]<dep[b]?a:b;
}
inline void Root_Mdf(int a){
	while(a) Mdf(1,1,n,dfn[top[a]],dfn[a]),a=fa[top[a]];
}
inline ll Root_Qry(int a,ll t=0){
	while(a) t+=Qry(1,1,n,dfn[top[a]],dfn[a]),a=fa[top[a]]; return t;
}
inline int Skip(int a,int tar){
	for(ri i=16;i>=0;--i) if(dep[FA[a][i]]>dep[tar]) a=FA[a][i];
	return a;
}
#define pii pair<int,int>
#define fir(x) x.first
#define sec(x) x.second
#define rp register pii
vector<pii > lpos[N],rpos[N],qr;
ll ans[N]; db res[N];

int main()
{
	rd(n),rd(m);
	for(ri i=1,u,v;i<n;++i)
		rd(u),rd(v),add(u,v),add(v,u);
	Dfs(1,0),Df4(1,1),Df3(1),Df2(1);
	for(ri i=1;i<=m;++i){
		int a,b,lca; rd(a),rd(b),lca=LCA(a,b);
		if(dep[a]>dep[b]) swap(a,b);
		if(lca==a){
			int pos=Skip(b,a);
			lpos[dfn[pos]-1].push_back({i,a}),rpos[rig[pos]].push_back({i,a});
			ans[i]=Sdep[1]-Sdep[pos]-(sum[a]<<1);
			res[i]=1.0+(db)Sdep[b]/siz[b];
			qr.push_back({i,n-siz[pos]}); continue;
		} res[i]=(db)Sdep[a]/siz[a]+(db)Sdep[b]/siz[b]+1.0-2.0*dep[lca];
	} for(ri i=1;i<=n;++i){
		Root_Mdf(id[i]);
		for(rp t:lpos[i]) ans[fir(t)]-=Root_Qry(sec(t))<<1;
		for(rp t:rpos[i]) ans[fir(t)]+=Root_Qry(sec(t))<<1;
	} for(rp t:qr) res[fir(t)]+=(db)ans[fir(t)]/sec(t);
	for(ri i=1;i<=m;++i) printf("%.8lf\n",res[i]);
	return 0;
}
```

---

## 作者：Diaоsi (赞：3)

**二次扫描+换根 dp**

设加入某条边后 $\text{a,b}$ 处在同一个环内时与该边直接相连的两个点为一对**合法点对**。

由于每个合法点对被选取的概率是相等的，而合法点对数就是**可加边**的数量。

显然可加边的数量就是环的数量，所以期望就是**所有环的总长度/合法点对个数**。

为方便讨论，我们设：

+ $x$ 表示树上的一个节点。

+ $d(x)$ 表示节点 $x$ 到根节点的距离。

+ $size(x)$ 表示以 $x$ 为根节点的子树的大小。

+ $F(x)$ 表示以 $x$ 为**根节点的子树**中所有点到 $x$ 点的距离和。

+ $G(x)$ 表示以 $x$ 为**根**时所有点到 $x$ 点的距离和。

+ $\text{lca}(x,y)$ 表示 $x$ 和 $y$ 的最近公共祖先。

考虑环是由什么构成的：

+ 新加入的一条边

+ 路径 $\text{a} \rightarrow \text{b}$ 

因为在一棵树上路径 $\text{a} \rightarrow \text{b}$ 是唯一的，而加入一条边后路径 $\text{a} \rightarrow \text{b}$ 显然有两条，所以环一定包含路径 $\text{a} \rightarrow \text{b}$ 。

设当前选取的点为 $x$ 和 $y$ 。

接下来分类讨论两种情况，当 $\text{lca}(a,b)$ 不为 $a$ 或 $b$ 时：

此时 $x$ 和 $y$ 只能在 $a$ 和 $b$ 的子树中选取，根据**乘法原理**，选取的方案数为：

$$size(a) \ast size(b)$$

那怎么求环的总长度呢？根据上面讨论的结果，由于路径 $\text{a} \rightarrow \text{b}$ 和新加入的一条边在每个环中都会出现，而环的总数为 $size(a) \ast size(b)$ ，所以这部分对环总数的贡献为：

$$size(a) \ast size(b) \ast (|\text{a} \rightarrow \text{b}|+1)$$ 

至于 $|\text{a} \rightarrow \text{b}|$ ，简单地用 $\text{LCA}$ 求一下就行。

具体地说： $|\text{a} \rightarrow \text{b}|=d(a)+d(b)-2 \ast \text{lca}(a,b)$ 

假设 $x$ 在 $a$ 的子树中，$y$ 在 $b$ 的子树中。

现在只用考虑 $|\text{x} \rightarrow \text{a}|$ 和 $|\text{y} \rightarrow \text{b}|$ 对答案的贡献。

可以这样感性理解一下：

> 对于子树 $a$ 中的任意的一个节点，在所有方案中它必定会与子树 $b$ 中的所有节点连边形成一个环，子树 $b$ 同理。

>所以子树 $a$ 中的节点 $x$ 对答案的贡献为它到节点 $a$ 的距离乘上 $size(b)$ ,由此推广到所有点，得子树 $a$ 中所有的节点对答案的贡献的总和为 $F(a) \ast size(b)$ ，子树 $b$ 同理。

于是**环的总长度**为：

$$size(a) \ast size(b) \ast (d(a)+d(b)-2 \ast \text{lca}(a,b)+1) + F(a) \ast size(b) + F(b) \ast size(a) $$

答案为上面那堆东西除以 $size(a) \ast size(b)$ 。

讨论另一种情况，当 $\text{lca}(a,b)$ 为 $a$ 时 ($b$ 同理) ：

对于子树 $b$ ，仍然可以按照情况一来讨论，只是此时不能直接讨论 $a$ 的子树了，因为在 $a$ 上方的节点(可以理解为祖先节点及其子树中的节点)也能对答案产生贡献。

设 $Son_a$ 表示 $a$ 在路径 $\text{a} \rightarrow \text{b}$ 上的儿子节点，可以用类似倍增 $\text{LCA}$ 的办法求出。

把在 $a$ 上方的节点和 $a$ 的子树中的节点近似地看作 $a$ 的“子树”，参照情况一进行讨论。

此时在 $a$ 的“子树”和 $b$ 的子树中**选取 $x,y$ 的方案数**为：

$$(n-size(Son_a)) \ast size(b)$$

其中 $n$ 为整棵树的大小。

继续参考情况一，计算 $|\text{a} \rightarrow \text{b}|$ 和新加入的边对答案的贡献。

显然只用将原来环的总数变成 $(n-size(Son_a)) \ast size(b)$ 就行。

设 $y$ 在 $b$ 的子树中。

此时 $|\text{y} \rightarrow \text{b}|$ 对答案的贡献跟情况一类似，为：

$$F(b) \ast (n-size(Son_a))$$

讨论 $a$ 的“子树”，根据文章最开始的设定，可以知道 $G(a)$ 为所有点到 $a$ 点的距离之和，因为 $x$ 不会出现在 $Son_a$ 及其子树中，所以我们要减去 $F(Son_a)$ 对答案的影响，由于直接减去会导致 $|\text{a} \rightarrow Son_a |$ 的长度仍被计算，易得知在 $G(a)$ 中 $|\text{a} \rightarrow Son_a |$ 被计算了 $size(Son_a)$ 次，所以直接减去就行。

对答案的贡献跟情况一类似：

$$(G(a)-F(Son_a)-size(Son_a)) \ast size(b)$$

合并一下，得**环的总长度**为：

$$\begin{aligned}(n-size(Son_a)) \ast size(b) \ast (d(a)+d(b)-2 \ast \text{lca}(a,b)+1) + \\ F(b) \ast (n-size(Son_a)) + (G(a)-F(Son_a)-size(Son_a)) \ast size(b)\end{aligned}$$

答案就是**环的总长度/选取 $x,y$ 的方案数** 。

接下来考虑如何求出 $F(x)$ 和 $G(x)$ ，设树的一号节点为根。

 $F(x)$ 的求法比较显然，因为每条边的距离都是 $1$ ，所以在第一遍 dfs 回溯时直接统计即可，$size(x)$ 也可以一并求出：

$$size(x)=\sum_{y \in Son\{x\}}size(y)$$

$$F(x)=\sum_{y \in Son\{x\}} F(y) + size(y)$$

利用第一次 dfs 求出的信息求 $G(x)$ ，显然，当 $x=1$ 时有 $G(x)=F(x)$ 。

第二次 dfs 时，考虑将 $G(x)$ 直接转移到 $G(y),y \in Son\{x\}$ 。

由于 $G(x)$ 的特殊性，$G(x)$ 和 $G(y)$ 只会受到边 $x \rightarrow y$ 计算次数的影响，可以这么理解，在计算 $G(x)$ 时边 $x \rightarrow y$ 会被计算 $size(y)$ 次，而在计算 $G(y)$ 时边 $x \rightarrow y$ 会被计算 $n-size(y)$ 次，其他的边被计算的次数均不受影响，故：

$$G(y)=G(x)-size(y)+(n-size(y))$$

求出 $F(x)$ 和 $G(x)$ 后，就可以愉快地解决上面的问题了。

既然你能找到这题，我相信你能瞬间做出来的。

$Code:$
```cpp
#include<bits/stdc++.h>
using namespace std;
const long long N=100010,M=1000010,INF=0x3f3f3f3f;
inline long long Max(long long x,long long y){return x>y?x:y;}
inline long long Min(long long x,long long y){return x<y?x:y;}
inline void Swap(long long &x,long long &y){x^=y^=x^=y;}
long long head[N],ver[M],Next[M],tot;
long long n,m,t,d[N],F[N],G[N],dist[N],size[N],f[N][20];
queue<long long> q;
void add(long long x,long long y){
	ver[++tot]=y,Next[tot]=head[x],head[x]=tot;
}
void bfs(){
	d[1]=1;
	q.push(1);
	while(q.size()){
		long long x=q.front();q.pop();
		for(long long i=head[x];i;i=Next[i]){
			long long y=ver[i];
			if(d[y])continue;
			d[y]=d[x]+1;
			dist[y]=dist[x]+1;
			f[y][0]=x;
			for(long long j=1;j<=t;j++)
				f[y][j]=f[f[y][j-1]][j-1];
			q.push(y);
		}
	}
}
long long lca(long long x,long long y){
	if(d[x]>d[y])Swap(x,y);
	for(long long i=t;i>=0;i--)
		if(d[f[y][i]]>=d[x])y=f[y][i];
	if(x==y)return x;
	for(long long i=t;i>=0;i--)
		if(f[x][i]!=f[y][i])x=f[x][i],y=f[y][i];
	return f[x][0];
}
long long query(long long x,long long y){
	return dist[x]+dist[y]-2*dist[lca(x,y)];
}
void dfs1(long long x,long long fa){
	size[x]=1;
	for(long long i=head[x];i;i=Next[i]){
		long long y=ver[i];
		if(y==fa)continue;
		dfs1(y,x);
		size[x]+=size[y];
		F[x]+=F[y]+size[y];
	}
}
void dfs2(long long x,long long fa){
	if(x==1)G[x]=F[x];
	for(long long i=head[x];i;i=Next[i]){
		long long y=ver[i];
		if(y==fa)continue;
		G[y]=G[x]-size[y]+(n-size[y]);
		dfs2(y,x);
	}
}
long double GetE(long long x,long long y){
	long long Lca=lca(x,y);
	long double Size,Sum;
	if(d[x]>d[y])Swap(x,y);
	if(Lca!=x){
		Size=size[x]*size[y];
		Sum=Size*(dist[x]+dist[y]-2*dist[Lca]+1)+F[x]*size[y]+F[y]*size[x];
	}
	else{
		long long sonx=y;
		for(long long i=t;i>=0;i--)
			if(d[f[sonx][i]]>d[x])sonx=f[sonx][i];
		Size=(n-size[sonx])*size[y];
		Sum=Size*(dist[x]+dist[y]-2*dist[Lca]+1)+
		(G[x]-F[sonx]-size[sonx])*size[y]+F[y]*(n-size[sonx]);
	}
	return Sum/Size;
}
int main(){
	scanf("%lld%lld",&n,&m);
	t=(long long)(log(n)/log(2))+1;
	for(long long i=1;i<n;i++){
		long long x,y;
		scanf("%lld%lld",&x,&y);
		add(x,y),add(y,x);
	}
	bfs();
	dfs1(1,0);
	dfs2(1,0);
	while(m--){
		long long x,y;
		scanf("%lld%lld",&x,&y);
		printf("%.8lf\n",(double)GetE(x,y));
	}
	return 0;
}
```

---

## 作者：EityDawn (赞：2)

## 思路

先考虑一共有多少种在环上的情况。

1. 钦定 $x$ 的深度小于 $y$。询问的 $x,y$ 满足 $x$ 是 $y$ 的祖先，也就是 $y$ 在以 $x$ 为根的子树中。

   首先从 $x$ 到 $y$ 的路径上（除 $x,y$ 外）的点包括这些点的子树都不用考虑，这样必然成不了环 。

   ![](https://cdn.luogu.com.cn/upload/image_hosting/s23uicry.png)

   

   那么这棵树就被分成了两部分，设 $siz_i$ 为以 $i$ 为根的子树大小。我们需要找到 $x$ 的某一个儿子 $z$ 满足以 $z$ 为根的子树内包含 $y$。那么上图左部分就有 $n-siz_z$ 个点，右部分有 $siz_y$ 个点，那么就有 $(n-siz_z)\times siz_y$ 种情况成环。

2. 询问的 $x,y$ 没有上述的祖孙关系，形如这样

   ![](https://cdn.luogu.com.cn/upload/image_hosting/mmksip19.png)

   很显然，这种情况的成环的情况数为 $siz_x\times siz_y$。

那么好，现在情况数分析完了，我们再想怎么计算答案。

对于情况 $1$，设左半部分所有点到 $x$ 的距离和为 $sum_x$，每个点都会和右边的所有点连一次，对环长的总贡献为 $sum \times siz_y$，设右半部分所有点到 $y$ 的距离和为 $sum_y$，同理可得它对环长的贡献为 $(n-siz_z)\times sum_y$，而所有可能的环必然包含 $x,y$ 之间的路径，设路径长为 $dis$，那么贡献为 $(dis+1)\times (n-siz_z)\times siz_y$，累加起来除情况数即可。

而对于情况 $2$，与 $1$ 同理，环的总长为 $siz_x\times sum_y+siz_y\times sum_x+siz_x\times siz_y\times dis$。

上面两种情况，对于 $1$ 中的 $sum_y$ 和 $2$ 中的 $sum_x,sum_y$ 很好求，定义 $g_i$ 为以 $i$ 为根的子树到 $i$ 的距离和，则 $g_i=\sum_{j\in son_i}g_j+siz_j$，即求 $g_x$ 和 $g_y$。

但对于 $1$ 中的 $sum_x$ 却并不好求。观察 $1$ 图发现，$sum_x$ 实际上是将所有点到 $x$ 的距离和减掉了儿子 $z$ 这棵子树的贡献。那么定义 $f_i$ 为全局所有点到 $i$ 的距离和，这是很典的换根 *dp*。那么 $sum_x=f_x-g_z-siz_z$。还有一个问题，就是 $1$ 中 $z$ 的求法，这里很显然可以树上倍增。

那么综上来看，复杂度为 $O(n+m\log n)$。

### code

```cpp
#include<iostream>
#include<iomanip>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<climits>
#include<queue>
#include<vector>
#include<map>
#include<set>
#define int long long
using namespace std;
const int N=1e5+10;
typedef long long ll;
typedef unsigned long long ull;
template<class T>
inline void read(T &x)
{
   x=0;short w=1;
   char c=getchar();
   while(c<'0'||c>'9')
   {
       if(c=='-') w=-1;
       c=getchar();
   }
   while(c>='0'&&c<='9')
       x=(x<<3)+(x<<1)+c-'0',c=getchar();
   x=x*w;
}
inline void read(char &x){x=getchar();}
template<class T>
inline void write(T x)
{
   if(x<0) putchar('-'),x=-x;
   if(x>9) write(x/10);
   putchar(x%10^'0');
}
inline void write(char c){putchar(c);}
template<class type,class ...T>
inline void read(type &x,T&...y){read(x),read(y...);}
template<class type,class ...T>
inline void write(type x,T ...y){write(x),write(y...);}
int dep[N],fa[N][21],siz[N];
int f[N],g[N],n,m,rt=1;
vector<int>G[N];
void dfs(int now,int from)
{
    siz[now]=1;
    for(int i=1;(1<<i)<=dep[now];i++)
        fa[now][i]=fa[fa[now][i-1]][i-1];
    g[now]=0;
    for(int to:G[now])
    {
        if(to==from) continue;
        fa[to][0]=now;dep[to]=dep[now]+1;
        dfs(to,now);
        g[now]+=g[to]+siz[to],siz[now]+=siz[to];
    }
    return;
}
void redfs(int now,int from)
{
    for(int to:G[now])
    {
        if(to==from) continue;
        f[to]=f[now]+(n-2*siz[to]);
        redfs(to,now);
    }
    return;
}
int LCA(int x,int y)
{
    if(dep[x]<dep[y]) swap(x,y);
    for(int i=20;~i;i--)
        if((1<<i)<=dep[x]-dep[y]) x=fa[x][i];
    if(x==y) return x;
    for(int i=20;~i;i--)
        if((fa[x][i]^fa[y][i])) x=fa[x][i],y=fa[y][i];
    return fa[x][0];
}
signed main()
{
    read(n,m);
    for(int i=1,x,y;i<n;i++)
    {
        read(x,y);
        G[x].push_back(y);
        G[y].push_back(x);
    }
    dfs(rt,0);for(int i=1;i<=n;i++) f[rt]+=dep[i];redfs(rt,0);
    for(int i=1,x,y,z;i<=m;i++)
    {
        read(x,y);
        if(dep[x]>dep[y]) swap(x,y);
        z=LCA(x,y);
        if(z==x){//情况 1
            int dis=dep[x]+dep[y]-2*dep[z],son=y;
            for(int i=20;~i;i--)
                if(fa[son][i]&&dep[fa[son][i]]>dep[x]) son=fa[son][i];//倍增求 z
            double Ans=siz[y]*(f[x]-g[son]-siz[son])+(n-siz[son])*g[y]+(dis+1)*(n-siz[son])*siz[y];
            printf("%.6lf\n",Ans/((n-siz[son])*siz[y]));
        }
        else{//情况 2
            int dis=dep[x]+dep[y]-2*dep[z];
            double Ans=siz[x]*siz[y]*(dis+1)+siz[y]*g[x]+siz[x]*g[y];
            printf("%.6lf\n",Ans/(siz[x]*siz[y]));
        }
    }
    return 0;
}
```

****

---

## 作者：lyb666666 (赞：2)

### 题目描述

给出一棵n个节点的树。有m个询问，每一个询问包含两个数a、b，我们可以对任意两个不相连的点连一条无向边，并且使得加上这条边后a，b处在一个环内。对于每一个询问，求这样的环的期望长度。

$2<=n,m<=10^5$

### 输入

第一行包括两个整数n，m，分别表示节点数和询问数。
接下来n-1行，每行两个整数u、v表示有一条从u到v的边。
接下来m行，每行两个整数a、b（a≠b），表示一个询问。

### 输出

对于每一个询问，输出满足条件的环的期望长度。答案保留6位小数。


## 题解

题目求的是期望，其实就是求两个东西，$all=$能形成环的个数，$ans=$所有环的长度总和，两者相除得到答案。

转化为树上的计数问题。接下来分两种情况讨论。

先交代下面会用到的数组，及其意义。

> *$sz[x]$*：以x为根的子树所含节点的个数。
>
> *$dep[x]$*：节点深度。
>
> *$fa[x][i=0..17]$*：x向上第$2^i$个祖先（供后面倍增跳LCA用）。
>
> *$sum[x]$*：$= ∑_{son∈x}dep[son]$，也就是子树中所有点的深度之和。
>
> *$tot[x]$*：后面再说。



### 1.(u,v)不是祖先关系

![](https://images.cnblogs.com/cnblogs_com/Tieechal/1556277/o_CF%20tmps.png)

发现只能将u,v子树里的点连起来。

所以，能形成环的个数$all=sz[u]*sz[v]$，其中$sz$数组表示子树所含节点个数。

所有环的长度之和：

$ans+=sz[u]*(sum[v]-dep[v]*sz[v]);$
$ans+=sz[v]*(sum[u]-dep[u]*sz[u]);$
$ans+=all*(dep[u]+dep[v]-2*dep[lca]+1);$



------

### 2.(u,v)是祖先关系

特殊点说明：将深度小的点作为u。son是u的儿子中通向v的那一个。v是深度较大的那一个。

如何求son？倍增向上跳$dep[v]-dep[u]-1$步，可以在O(logN)时间内得到。

------

看下面这幅图，我们只能在**v的子树**中选一个点，在**蓝色部分(除子树son的点)** 选一个点，将两者相连，才能形成环。

所以，环的个数$all=sz[v]*(sz[1]-sz[son])$。

如何求环的长度总和？分成下面几部分分步求解。

这里换个元方便下面表示$sz1=sz[v]$，$sz2=(sz[1]-sz[son])$。$sz1$就是粉色部分的点数，$sz2$就是蓝色部分的点数。



![](https://images.cnblogs.com/cnblogs_com/Tieechal/1556277/o_CF%20tmp2.png)

**part1:**

$ans+=(sum[v]-dep[v]*sz1)*sz2+(dep[v]-dep[u])*all$

**part2:**

$ans+=1*all$

**part3：**

这个东西与前面几个相比不太好分析。

求树上两点(a,b)的距离就是$dep[a]+dep[b]-2*dep[LCA(a,b)]$。

全部加起来，那么现在我们求的就是下面这东西。
$$
dep[u]*sz2+∑_{x∈bluepart}(dep[x]-2*dep[LCA(u,x)])
$$
前面那个可以O(1)算出。就是后面那一坨如何在可行的时间内弄出？

考虑预处理一个数组$tot[son]$，表示，若它的父亲节点为u，则$tot[son]=∑_{x∈bluepart}(dep[x]-2*dep[LCA(u,x)])$也就是上面式子中后面的部分。

dfs一遍，完成$tot$数组的预处理，转移如下。画个图还是很好理解的，当弄到x时，f就是上式的lca。

```cpp
void dfs2(int x){
    int f=fa[x][0];
    if(f){
        tot[x]=tot[f]+sum[f]-sum[x];
        tot[x]-=2ll*(sz[f]-sz[x])*dep[f];
    }
    for(int i=head[x];i;i=e[i].nxt)if(e[i].to!=fa[x][0])dfs2(e[i].to);
}
```

综上分两种情况讨论，时间复杂度为$O(NlogN)$。

完整代码如下：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
typedef long long ll;
const int N=1e5+10;
inline int read(){
    int x=0;char c=getchar();
    while(c<'0'||c>'9')c=getchar();
    while(c>='0'&&c<='9')x=(x<<3)+(x<<1)+(c^48),c=getchar();
    return x;
}
struct edge{
    int to,nxt;
}e[N<<1];
int head[N],ecnt;
inline void link(int u,int v){
    e[++ecnt].to=v,e[ecnt].nxt=head[u];
    head[u]=ecnt;
}
int n,m;
ll sum[N],tot[N];
int sz[N],dep[N],fa[N][18];
ll gcd(ll a,ll b){return b==0?a:gcd(b,a%b);}
void dfs(int x,int f){
    fa[x][0]=f,dep[x]=dep[f]+1,sum[x]=dep[x];
    sz[x]=1;
    for(int i=head[x];i;i=e[i].nxt){
        int y=e[i].to;if(y==f)continue;
        dfs(y,x);
        sz[x]+=sz[y];
        sum[x]+=sum[y];
    }
}
void dfs2(int x){
    int f=fa[x][0];
    if(f){
        tot[x]=tot[f]+sum[f]-sum[x];
        tot[x]-=2ll*(sz[f]-sz[x])*dep[f];
    }
    for(int i=head[x];i;i=e[i].nxt)if(e[i].to!=fa[x][0])dfs2(e[i].to);
}
inline int jump(int x,int stp){
    for(int i=0;i<=17;i++)if(stp&(1<<i))x=fa[x][i];
    return x;
}
inline int LCA(int x,int y){
    if(dep[x]<dep[y])swap(x,y);
    int stp=dep[x]-dep[y];
    x=jump(x,stp);
    if(x==y)return x;
    for(int i=17;i>=0;i--)if(fa[x][i]!=fa[y][i])x=fa[x][i],y=fa[y][i];
    return fa[x][0];
}
signed main(){
    n=read(),m=read();
    for(int i=1;i<n;i++){
        int u=read(),v=read();
        link(u,v),link(v,u);
    }
    dfs(1,0),dfs2(1);
    for(int j=1;j<=17;j++)for(int i=1;i<=n;i++)fa[i][j]=fa[fa[i][j-1]][j-1];
    while(m--){
        int u=read(),v=read();
        if(dep[u]>dep[v])swap(u,v);
        int lca=LCA(u,v);
        ll all,ans;
        if(lca==u){
            int son=jump(v,dep[v]-dep[u]-1);
            int sz1=sz[v],sz2=sz[1]-sz[son]; 
            all=1ll*sz1*sz2,ans=0;
            ans+=1ll*(sum[v]-dep[v]*sz1)*sz2;
            ans+=1ll*(tot[son]+sz2*dep[u])*sz1;
            ans+=1ll*all*(dep[v]-dep[u]+1);
        }
        else{
            all=1ll*sz[u]*sz[v],ans=0;
            ans+=1ll*sz[u]*(sum[v]-dep[v]*sz[v]);
            ans+=1ll*sz[v]*(sum[u]-dep[u]*sz[u]);
            ans+=1ll*all*(dep[u]+dep[v]-2*dep[lca]+1);
        }
    	printf("%.7f\n",1.0*ans/all);
	}
}
```

[blog](https://www.cnblogs.com/Tieechal/p/11590224.html)



---

## 作者：forest114514 (赞：1)

### CF629E Famil Door and Roads

树形 DP+期望

我们首先考虑一下如何求环的大小的期望

我们可以独立考虑 $u$ 子树内的点和 $v$ 子树内的点的贡献期望值（记 $\overline L$ 为环的期望长度，$subtree_u$ 为 $u$ 的子树内的点的集合）。
$$
\overline L=dis(u,v)+\frac{\sum\limits_{p\in subtree_u}dis(u,p)}{siz_u}+\frac{\sum\limits_{p\in subtree_v}dis(v,p)}{siz_v}+1
$$
当然这是以当前树上 $u,v$ 没有祖先关系的时候，可以 $O(N)$ 预处理，$O(\log N)$ 询问出。

如果有祖先关系呢？

不妨设 $v$ 是 $u$ 的祖先，那么有：
$$
\overline L=dis(u,v)+\frac{\sum\limits_{ p\in subtree_u}dis(u,p)}{siz_u}+\frac{\sum\limits_{ p\notin subtree_v}dis(v,p)}{n-siz_x}+1 \quad (x\in son_v\land lca(x,u)=x) $$
对于 $\sum\limits_{p\notin subtree_v}dis(v,p)$ 也是 $O(N)$ 的预处理,$O(\log N)$ 的单次询问。

---

对于 $\sum\limits_{p\in subtree_u}dis(u,p)$  和 $\sum\limits_{p\notin subtree_v}dis(v,p)$ 的处理：

我们记 $f_u$ 为 $u$ 子树的所有结点到 $u$ 的距离和，$g_u$ 为以 $u$ 为根的节点深度和，$siz_u$ 为 $u$ 子树的大小，$dep_u$ 为 $u$ 节点的深度，那么有：
$$
\sum\limits_{p\in subtree_u}dis(u,p)=f_u 
$$
$$
\sum\limits_{p\notin subtree_v}dis(v,p)=g_u-\sum\limits_{p\in subtree_x}dis(x,p)=g_u-f_x-siz_x\quad (x\in son_v\land lca(x,u)=x)
$$
其中 $f_u=\sum\limits_{(u,v)\in G\&v\not=fa_u}{f_v+siz_v}$。

对于 $g_u$ 考虑换根 DP（~~板中板~~）：
$$
\begin{cases} g_u=g_{fa}-siz_u+(n-siz_u)& (u\not=rt)\\ g_{rt}=f_{rt} \end{cases}
$$
至于 $dis(u,v)$，~~这都不会还来做这个题~~？

---

为了方便求 $v$ 在 $u$ 到它路径上的儿子 $x$，我们用树上倍增求 LCA，总时间复杂度为 $O((N+M)\log N)$。

 **小细节**：为了不损失精度我们先统一加再除（~~反正我就吃了精度的亏……~~）。

CODE：

```cpp
#include<bits/stdc++.h>
#define re register
#define il inline
#define gc() getchar()
#define rep(i,a,b) for(re int i=a;i<=b;++i)
#define per(i,a,b) for(re int i=a;i>=b;--i)
#define tep(i,x) for(re int i=head[x];~i;i=ne[i])
#define ls(x) tr[x].son[0]
#define rs(x) tr[x].son[1]
#define eps (1e-9)
#define inf 0x3f3f3f3f
#define INF 1e18+100
#define pii pair<int,int>
#define mp(i,j) make_pair(i,j)
#define pb push_back
#define fi first
#define sc second
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef long double LD;
template<typename T> inline void read(T &x){
	bool f=1;x=0;char ch=gc();
	while(ch<'0'||ch>'9'){if(ch=='-')f=0;ch=gc();}
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch&15),ch=gc();
	x=f?x:-x;
}
template<typename T> inline void write(T x){
	if(x<0) putchar('-'),x=-x;
   	if(x>9) write(x/10);
   	putchar(('0'+x%10));
}
template <typename T,typename ...Args> inline
void read(T &x,Args &...args){read(x);read(args...);}
template<typename T> inline void write(T x,char c){write(x),putchar(c);}
const int N=2e5+100;
#define int LL
int n,m,Ti,dep[N],siz[N],fa[N][21];
LL f[N],g[N];
vector<int> E[N];
void dfs1(int x,int ff){
	siz[x]=1;
	fa[x][0]=ff;
	rep(i,1,19) fa[x][i]=fa[fa[x][i-1]][i-1];
	for(auto y:E[x]){
		if(y==ff) continue;
		dep[y]=dep[x]+1;
		dfs1(y,x);
		siz[x]+=siz[y];
		f[x]+=(f[y]+siz[y]);
	}
}
void dfs2(int x){
	if(x!=1)g[x]=g[fa[x][0]]+n-2*siz[x];
	else g[1]=f[1];
	for(auto y:E[x]){
		if(y==fa[x][0]) continue; 
		dfs2(y);
	}
}
int lca(int x,int y){
	if(dep[x]<dep[y]) swap(x,y);
	per(i,19,0) if(dep[fa[x][i]]>=dep[y]) x=fa[x][i];
	if(x==y) return x;
	per(i,19,0) if(fa[x][i]^fa[y][i]) x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}
int getson(int x,int y){
	per(i,19,0) if(dep[fa[x][i]]>dep[y]) x=fa[x][i];
	return x;
}
void solve(){
	int u,v;
	read(u,v);
	if(dep[u]<dep[v]) swap(u,v);
	int l=lca(u,v);
	double res=0;
	if(l==v){
		int son=getson(u,v);
		res=(double)(dep[u]-dep[v]+1)*siz[u]*(n-siz[son]);
		res+=1.0*f[u]*(n-siz[son])+1.0*(g[v]-f[son]-siz[son])*siz[u];
		res=res/(1.0*siz[u]*(n-siz[son]));
	}
	else{
		res=double(dep[u]+dep[v]-2*dep[l]+1)*siz[u]*siz[v]; 
		res+=1.0*f[u]*siz[v]+1.0*f[v]*siz[u];
		res=res/(1.0*siz[u]*siz[v]);
	}
	printf("%.10lf\n",res);
}
signed main(){
	//ios::sync_with_stdio(false);
	//cin.tie(0);cout.tie(0);
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	read(n,m);
	int u,v;
	rep(i,1,n-1){
		read(u,v);
		E[u].pb(v),E[v].pb(u);
	}
	dep[1]=1;
	dfs1(1,0);
	dfs2(1);
	while(m--) solve();
	return 0;
}
```



---

## 作者：Treaker (赞：1)

~~套路题，可海星~~

我们发现，答案就是 可以构成的所有环的总长度/可以构成的所有环的数量

那么，我们分情况讨论一下

对于询问的点对（x,y），我们默认$dep_x \ge dep_y$

1.y是x的祖先
	
我们定义w为，w是x的祖先且$fa_w=y$

此时，所有可以构成环的点对必定是，一个在x的子树内，另一个在w的子树外。

环的数量就是$size_x*(n-size_w)$

那么，环的总长度怎么求呢？

先考虑公共部分，也就是从x到w的长度（为啥不是从x到y的长度呢？因为为了方便求子树外的部分，选取y的话，可能会比较麻烦）和 新加的边的长度1，他会出现 $size_x*(n-size_w)$ 次。

其次就是，x子树内的部分，我们需要维护x子树内的所有点到x的距离和，他会出现 $n - size_w$ 次

最后就是，w子树外的部分，我们需要维护w子树外的所有点到w的距离和，他会出现$size_x$次

维护的这些东西，可以通过两遍dfs，换根DP来求出。这个是比较基础的了。

2.y不是x的祖先

这个更简单了

点对 是一个在x的子树内，另一个在y的子树内

公共部分是$dis_{x,y}$ + 1，会出现$size_x*size_y$次

两个子树内的部分就跟上面的差不多了。

然后就完美地解决了。

$O(n)$预处理，单次询问$O(logn)$

贴上代码

```cpp
const int N = 1e5 + 5;
int n , m;
int fa[N][20] , size[N] , dep[N];
ll sum[N] , s[N];
struct Edge
{
	int to; Edge *nxt;
	Edge(int to = 0,Edge *nxt = NULL) : to(to) , nxt(nxt) {}
} *head[N] , pool[N << 1] , *tail = pool;
inline void add(int u,int v) { head[u] = new (tail ++) Edge(v,head[u]);}
void get_tree(int x)
{
	dep[x] = dep[fa[x][0]] + 1; size[x] = 1;
	for(int i = 1;i <= 19;i ++) fa[x][i] = fa[fa[x][i - 1]][i - 1];
	for(Edge *i = head[x];i;i = i -> nxt)
	{
		int to = i -> to;
		if(to == fa[x][0]) continue;
		fa[to][0] = x;
		get_tree(to);
		size[x] += size[to];
		sum[x] += sum[to] + size[to];
	}
}
void dfs(int x)
{
	for(Edge *i = head[x];i;i = i -> nxt)
	{
		int to = i -> to;
		if(to == fa[x][0]) continue;
		s[to] = s[x] + sum[x] - sum[to] - size[to] + n - size[to];
		dfs(to);
	}
}
inline int LCA(int x,int y)
{
	if(dep[x] < dep[y]) swap(x,y);
	for(int i = 19;i >= 0;i --) if(dep[fa[x][i]] >= dep[y]) x = fa[x][i];
	if(x == y) return x;
	for(int i = 19;i >= 0;i --) if(fa[x][i] != fa[y][i]) x = fa[x][i] , y = fa[y][i];
	return fa[x][0];
}
inline int find(int x,int y)
{
	for(int i = 19;i >= 0;i --) if(dep[fa[fa[x][i]][0]] >= dep[y]) x = fa[x][i];
	return x;
}
inline int Dis(int x,int y) { return dep[x] + dep[y] - (dep[LCA(x,y)] << 1);}
int main()
{
	n = read(); m = read();
	for(int i = 1 , u , v;i < n;i ++) u = read() , v = read() , add(u,v) , add(v,u);
	get_tree(1); dfs(1);
	while(m --> 0)
	{
		int x = read() , y = read() , lca = LCA(x,y); double ans = 0;
		if(dep[x] < dep[y]) swap(x,y);
		if(lca == y) 
		{
			int w = find(x,y);
			ans = dep[x] - dep[w] + 1 + (double)sum[x] / (double)size[x] + (double)s[w] / (double)(n - size[w]);
		}
		else
		{
			ans = (double)sum[x] / (double)size[x] + (double)sum[y] / (double)size[y] + Dis(x,y) + 1;
		}
		printf("%.8f\n",ans);
	}
	return 0;
}
```


---

## 作者：_ZHONGZIJIE0608_ (赞：0)

给定一个 $n$ 个节点的树，$m$ 次询问，每次给两个点 $u,v$，在树上任意两点间连一条边使得 $u,v$ 在同一个环内，求这个环的期望长度。

首先考虑在哪两个点之间连边。注意到这两个点之间的路径一定经过点 $u,v$。所以环的期望长度等于经过点 $u,v$ 的路径长度之和与路径数量的商加上 $1$（就是加的那条边的长度）。

考虑维护过两点的路径长度之和与路径条数。

不难发现路径条数和子树大小有关。

由于根不同可能导致子树大小不同，需要分类讨论和换根。

设 $sz_{u}$ 表示以点 $1$ 为根时点 $u$ 的子树大小，$dep_{u}$ 表示点 $u$ 的深度。

如果两个点之间不存在一个点是另一个点的祖先的关系，方案数就是 $sz_{v} \times sz_{u}$。

如果两点间存在一个点是另一个点的祖先的关系，此时钦定 $u$ 是 $v$ 的祖先，则 $u$ 的子树大小会发生变化。

设点 $s$ 为从点 $v$ 到点 $u$ 的路径的倒数第二个节点，这里可以在求最近公共祖先时预处理。

此时，以 $v$ 为根时 $u$ 的子树大小，就是不在 $u$ 到 $v$ 路径（$u$ 不考虑在路径内）与 $v$ 的子树内的点的个数就是 $(n-sz_{s})$。

方案数处理完了，考虑路径长度之和。

显然，一条经过点 $u$ 和点 $v$ 的路径由以下三个部分组成：

- 从以 $u$ 为根时点 $v$ 子树内的一个点到 $v$ 的路径。
- 从 $v$ 到 $u$ 的路径。
- 从以 $v$ 为根时点 $u$ 子树内一个点到点 $u$ 的路径。

其中，第二个部分的路径长度是 $dep_{u}+dep_{v}-2 \times dep_{L}$，其中 $L$ 为点 $u,v$ 的最近公共祖先。

由于第二个部分对总长度的贡献就是点 $u$ 到点 $v$ 的距离乘路径条数，我们直接在最后计算答案时增加这个距离，并在求总长度时忽略这部分。

还是分类讨论。

设 $dp1_{u}$ 表示以 $1$ 为根时点 $u$ 子树内的一端为 $u$ 的路径长度之和。

设 $dp2_{u}$ 表示以 $u$ 为根时整棵树上一端为 $u$ 的路径长度之和，就是每个点到点 $u$ 的距离之和。

一个很经典的动态规划。下面给出 $dp1_{u}$ 的转移方程。

设 $son(u)$ 表示 $u$ 的子节点的集合，$fa$ 表示 $u$ 的父亲。

$$dp1_{u}=\sum_{v \in son(u)} dp1_{v}+sz_{v}$$

由于从儿子转移到父亲时路径长度全部加上 $1$，还是不难想到。

然后 $dp2_{1}=dp1_{1}$。

$dp2_u$ 的转移方程：

$$dp2_{u}=dp2_{fa}+(n-2 \times sz_{u})$$

$u=1$ 时并不用转移，而且这个转移方程十分经典。

接下来分类讨论。

如果 $u,v$ 不存在一个点是另一个点的祖先的关系，总长度（不算中间 $u,v$ 距离）就是 $dp1_{u} \times sz_{v}+dp1_{v} \times sz_{u}$。

如果 $u,v$ 存在一个点是另一个点的祖先的关系，就需要换根。计算总长度时参考没有这个关系的部分。

把 $dp2_{u}$ 减去 $u$ 为根时 $s$ 的子树的贡献得到 $u$ 的事实贡献 $(dp2_{u}-sz_{s}-dp1_{s})$，$v$ 的子树内的点的个数就是 $(n-sz_{s})$。

所以此时总长度为：

$$(dp2_{u}-sz_{s}-dp1_{s}) \times sz_{v} + dp1_{v} \times (n-sz_{s})$$

最后把“总长度”与方案数作商加上之前忽略掉的 $u,v$ 之间距离和新增的长度 $1$ 就是答案。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
int n,q,fa[N],sz[N],dep[N],son[N],top[N],dp1[N],dp2[N];
vector<int>e[N];
void dfs(int u,int ls){
	sz[u]=1;dep[u]=dep[ls]+1;fa[u]=ls;int mx=-1;
	for(auto v:e[u])if(v!=ls){
		dfs(v,u);sz[u]+=sz[v];if(sz[v]>mx)mx=sz[v],son[u]=v;dp1[u]+=dp1[v]+sz[v];
	}
}
void DFS(int u,int p){
	top[u]=p;if(!son[u])return;
	DFS(son[u],p);
	for(auto v:e[u])if(v!=son[u]&&v!=fa[u])DFS(v,v);
}
void ddfs(int u,int ls){
	for(auto v:e[u])if(v!=ls)dp2[v]=dp2[u]+(n-2*sz[v]),ddfs(v,u);
}
int LCA(int u,int v,int &s){
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]])swap(u,v);
		s=top[u];u=fa[top[u]];
	}
	if(u==v)return u;
	if(dep[u]>dep[v])swap(u,v);
	s=son[u];return u;
}
signed main(){
	ios::sync_with_stdio(false);cin.tie(0),cout.tie(0);
	cin>>n>>q;
	for(int i=1;i<n;++i){
		int u,v;cin>>u>>v;
		e[u].push_back(v);e[v].push_back(u);
	}dfs(1,0);DFS(1,1);dp2[1]=dp1[1];ddfs(1,0);
	while(q--){
		int u,v;cin>>u>>v;
		if(dep[u]>dep[v])swap(u,v);
		int s,l=LCA(u,v,s); int dis=(dep[u]+dep[v]-2*dep[l]);
		if(l!=u){
			double fas=sz[u]*sz[v];
			double tmp=dp1[u]*sz[v]+dp1[v]*sz[u];
			cout<<fixed<<setprecision(15)<<(tmp*1.0/fas)+1.0+dis<<'\n';
		}
		else{
			double fas=(n-sz[s])*sz[v];
			double tmp=(dp2[u]-dp1[s]-sz[s])*sz[v]+dp1[v]*(n-sz[s]);
			cout<<fixed<<setprecision(15)<<(tmp*1.0/fas)+1.0+dis<<'\n';
		}
	}
	return 0;
}
```

---

## 作者：_Wind_Leaves_ShaDow_ (赞：0)

对于一次询问，若连接 $x,y$ 两点可以使 $a,b$ 处于一个环中，令环的顺序为 $x\to a\to b\to y\to x$，那么此时环的长度为 $dis(a,b)+dis(a,x)+dis(y,b)+1$。

如果 $a,b$ 有祖先后代关系，$x$ 一定在 $a$ 的子树内（包括 $a$），令 $p$ 为 $b$ 往 $a$ 方向延伸的第一个子节点，那么 $y$ 可以位于任意一个不在 $p$ 的子树内的点。

期望 $E=\frac{\sum_{x\in son(a)}\sum_{y\not\in son(p)}dis(a,b)+dis(a,x)+dis(y,b)+1}{sz_a\times(n-sz_p)}$。

考虑拆式子。先把和 $x,y$ 无关的数提出来，然后和 $x$ 有关的项都与 $y$ 无关，提示我们分开维护。

$E=\frac{\sum_{x\in son(a)}dis(a,x)\times(n-sz_p)+\sum_{y\not\in son(p)}dis(b,y)\times sz_a}{sz_a\times(n-sz_p)}+dis(a,b)+1$。

于是我们只要维护一个点到子树内所有点的路径长度和和到子树外所有点的路径长度和。第一个可以一遍 dfs 求出来，第二个可以换根 dp 求出来。寻找 $p$ 是 $\log$ 的，可能有更简单的方法但是我降智。

如果 $a,b$ 没有祖先后代关系，那么更简单。

期望 $E=\frac{\sum_{x\in son(a)}\sum_{y\in son(b)}dis(a,b)+dis(a,x)+dis(y,b)+1}{sz_a\times sz_b}$。

同样得到 $E=\frac{\sum_{x\in son(a)}dis(a,x)\times sz_b+\sum_{y\in son(p)}dis(b,y)\times sz_a}{sz_a\times sz_b}+dis(a,b)+1$。

只需要维护到子树内的点的路径长度和。

所以我们能够 $O(\log n)$ 处理查询，做完了。复杂度 $O(q\log n)$。换根 dp 是线性的。

```cpp
#include <bits/stdc++.h>
#define int long long
#define Il inline
#define Rg register
#define Ri Rg int
#define pb push_back
#define vec vector
#define fi first
#define se second
#define IT ::iterator

using namespace std;
//typedef long long ll;
typedef double db;
typedef pair<int,int> pii;
const int N=1e5,Inf=1e9,mod=1e9+7;
const db eps=1e-9,pi=acos(-1.0);

int n,Q,de[N+5],sz[N+5],lg[N+5],fa[N+5][25],sd[N+5],su[N+5];
vec<int>v[N+5];

Il int lca(int x,int y){
	if(de[x]<de[y])swap(x,y);
	while(de[x]^de[y])x=fa[x][lg[de[x]-de[y]]];
	if(x==y)return x;
	for(Ri i=20;~i;i--)if(fa[x][i]^fa[y][i])x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}

Il db dis(int x,int y){return 1.0*(de[x]+de[y]-(de[lca(x,y)]<<1));}

Il void dfs(int p,int fr){
	de[p]=de[fr]+1;sz[p]=1;fa[p][0]=fr;
	for(Ri i=1;i<=20;i++)fa[p][i]=fa[fa[p][i-1]][i-1];
	for(Ri i:v[p])if(i^fr)dfs(i,p),sz[p]+=sz[i],sd[p]+=sd[i]+sz[i];
	return;
}

Il void dp(int p,int fr){
	su[p]=su[fr]+(n-sz[fr])+(sd[fr]-sd[p]-sz[p]+sz[fr]-sz[p]);
	for(Ri i:v[p])if(i^fr)dp(i,p);
	return;
}

Il int to(int p,int t){
	for(Ri i=20;~i;i--)if(de[fa[p][i]]>de[t])p=fa[p][i];
	return p;
}

signed main(){
	scanf("%lld%lld",&n,&Q);
	for(Ri i=2;i<=n;i++)lg[i]=lg[i>>1]+1;
	for(Ri i=1;i<n;i++){
		int x,y;scanf("%lld%lld",&x,&y);
		v[x].pb(y),v[y].pb(x);
	}
	dfs(1,0);
	for(Ri i:v[1])dp(i,1);
	while(Q--){
		int a,b,c;scanf("%lld%lld",&a,&b);c=lca(a,b);if(de[a]>de[b])swap(a,b);
		if(c^a)printf("%.6f\n",1.0*(sd[a]*sz[b]+sd[b]*sz[a])/(sz[a]*sz[b])+1.0+dis(a,b));
		else{
			int p=to(b,a);
			printf("%.6f\n",1.0*((su[p]-(n-sz[p]))*sz[b]+sd[b]*(n-sz[p]))/((n-sz[p])*sz[b])+1.0+dis(a,b));
		}
	}
	return 0;
}
```

---

## 作者：lfxxx (赞：0)

将 $u,v$ 之间路径上的点全部挖掉后，$u,v$ 所处的两个连通块之间连边才可能使得 $u,v$ 在环上，环长显然时这两个连通块到 $u,v$ 的距离平均值之和加上 $u,v$ 之间距离再加 $1$。

假若一个点被挖掉的是父亲，子树到其距离平均值可以简单树形 dp，若挖掉的是儿子，先从上到下 dp 求出全局所有点到其距离之和再减去挖掉的子树的贡献即可。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
//#define lowbit(x) (x&(-x))
//#define bp push_back
//#define sz size
//#define cl clear
const int maxn = 1e5+114;
vector<int> E[maxn];
int n,m;
int father[maxn];
int son[maxn],sz[maxn],dep[maxn],top[maxn];
int dp[maxn],g[maxn];//dp[u] u 子树内所有点到 u 距离之和，g[u] u 子树外所有点到 u 距离之和
void dfs1(int u,int fa){
	sz[u]=1;
	father[u]=fa;
	dep[u]=dep[fa]+1;
	for(int v:E[u]){
		if(v!=fa){
			dfs1(v,u);
			sz[u]+=sz[v];
			if(sz[v]>sz[son[u]]) son[u]=v;
			dp[u]+=dp[v]+sz[v];
		}
	}
} 
void dfs2(int u,int fa,int tp){
	top[u]=tp;
	if(son[u]!=0) dfs2(son[u],u,tp);
	for(int v:E[u]){
		if(v!=fa&&v!=son[u]) dfs2(v,u,v);
	}
}
void dfs3(int u,int fa){
	for(int v:E[u]){
		if(v!=fa){
			g[v]=(g[u]+dp[u]-dp[v]-sz[v])+(n-sz[v]);
			dfs3(v,u);
		}
	}
}
int LCA(int u,int v){
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]]) swap(u,v);
		u=father[top[u]];
	}
	if(dep[u]<dep[v]) swap(u,v);
	return v;
}
int dis(int u,int v){
	return dep[u]+dep[v]-2*dep[LCA(u,v)];
}
double ans[maxn];
vector< pair<int,int> > Query[maxn];//(a,id)
vector<int> vec;
void dfs4(int b,int fa){
	vec.push_back(b);
	for(pair<int,int> now:Query[b]){
		int a=now.first,id=now.second;
		if(a==b){
			int sum=dp[a]*(n-sz[a]+1)+g[a]*sz[a];
			int cnt=(n-sz[a]+1)*sz[a]-1;
			ans[id]=(double)sum/cnt+1;
		}else if(LCA(a,b)!=a){
			ans[id]=(double)dp[a]/sz[a]+(double)dp[b]/sz[b]+dis(a,b)+1;
		}else{
			int btp=vec[vec.size()-dis(a,b)];
			ans[id]=(double)(g[a]+dp[a]-dp[btp]-sz[btp])/(n-sz[btp])+(double)dp[b]/sz[b]+dis(a,b)+1;
		}
	}
	for(int v:E[b]){
		if(v!=fa) dfs4(v,b);
	}
	vec.pop_back();
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		E[u].push_back(v);
		E[v].push_back(u);
	}
	dfs1(1,0);
	dfs2(1,0,1);
	dfs3(1,0);
	for(int i=1;i<=m;i++){
		int a,b;
		cin>>a>>b;
		if(dep[a]>dep[b]) swap(a,b);
		//dep[a]<dep[b]
		Query[b].push_back(make_pair(a,i));
	}
	dfs4(1,0);
	for(int i=1;i<=m;i++) printf("%.8lf\n",ans[i]);
	return 0;
}

```

---

## 作者：Hoks (赞：0)

## 前言
水题，但我怎么看啥树的题都感觉像是做过。

摘自 [杂题选做](https://www.luogu.com.cn/training/518105)。
## 思路分析
套路题，考虑分讨。

显然的是，如果 $x,y$ 之间连了条边，能让 $u,v$ 在环上，那么 $x\rightarrow y$ 的路径必然是经过 $u,v$ 的。

分讨一下，考虑 $u,v$ 间有无拐点。

1. 有拐点的时候。

    此时比较简单，只要选出 $x,y$ 一个在 $u$ 子树里，一个在 $v$ 子树里就可以成环，方案数即为 $si_u\cdot si_v$。

   接着考虑算环长。

   定义 $f_i$ 表示 $i$ 子树里所有点（除 $i$ 外）到 $i$ 的距离和。

    $f_i$ 可以在 dfs 中处理出来，$f_u=\sum\limits_{v\in son_u} f_v+si_v$。

   那么 $si_u\cdot si_v$ 种方案的环长总长即为：
   $$f_u\cdot si_v+f_v\cdot si_u+si_u\cdot si_v\cdot(dis(u,v)+1)$$

   后面那个考虑直接剥出来，输出的时候再加上就行了。

   输出即为：
   $$\frac{f_u\cdot si_v+f_v\cdot si_u}{si_u\cdot si_v}+dis(u,v)+1$$
3. 没拐点的时候。

    此时令 $dep_u<dep_v$，即 $LCA(u,v)=u$。

   同时我们设 $z$ 为 $u\rightarrow v$ 路径上的**第一个**点。

   显然的是，我们要取出两个点 $x,y$ 满足一个点在 $v$ 子树内，另一个点**不在** $z$ 子树内。

   所以方案数为 $si_v\cdot(n-si_z)$。

   接着考虑计算环长。

   首先环长肯定至少为 $dis(u,v)+1$，这里不再赘述。

   接着考虑 $v$ 那一段的额外环长。

   类似于上面的，即为 $f_v\cdot(n-si_z)$。

   最后最难的部分，考虑 $u$ 那一段的额外环长。

   因为路径有拐点，所以很难处理。

   考虑容斥，用**所有点**到 $u$ 的距离减去 $z$ **子树内点**到 $u$ 的距离计算。

   定义 $g_i$ 表示所有点到点 $i$ 的距离，那么显然的 $g_1=f_1$。

   对于计算 $g_i$，我们考虑换根。

   还是在 dfs 中处理，设 $g_{fa_i}$ 已经算好了。

   那么当根节点从 $fa_i$ 移动到 $i$ 时，所有 $i$ 子树里的点距离都少了 $1$，所以 $-si_i$。

   而所有非 $i$ 子树里的点距离都多了 $1$，所以 $+n-si_i$。

   所以 $g_i=g_{fa_i}-si_i+n-si_i$。

   那么用这个去表示前面要算的东西就非常简单了，即为：
   $$si_v\cdot(g_u-f_z-si_z)$$

   最后输出答案就输出：
   $$\frac{f_v\cdot(n-si_z)+si_v\cdot(g_u-f_z-si_z)}{si_v\cdot(n-si_z)}+dis(u,v)+1$$
## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10,INF=0x3f3f3f3f3f3f3f3f,mod=1e9+7;
int n,q,cnt;vector<int>e[N];
namespace Fast_IO
{
    static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
    #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
    inline int read()
    {
        int x(0),t(1);char fc(getchar());
        while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
        return x*t;
    }
    inline void flush(){fwrite(out,1,length,stdout);length=0;}
    inline void put(char c){if(length==9999999) flush();out[length++]=c;}
    inline void put(string s){for(char c:s) put(c);}
    inline void print(int x)
    {
        if(x<0) put('-'),x=-x;
        if(x>9) print(x/10);
        put(x%10+'0');
    }
    inline bool chk(char c) { return !(c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'||c=='?'); }
    inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
    inline void rd(char s[],int&n)
    {
        s[++n]=getchar();
        while(chk(s[n])) s[n]=getchar();
        while(ck(s[n])) s[++n]=getchar();
        n--;
    }
}
using namespace Fast_IO;
namespace tree_decomposition
{
    int fa[N],son[N],si[N],dep[N];
    int top[N],id[N],dfn[N],f[N],g[N];
	inline void clear(int n)
	{
		memset(son,0,sizeof son);
		cnt=0;for(int i=1;i<=n;i++) e[i].clear();
	}
    inline void dfs1(int u,int ff)
    {
        fa[u]=ff,si[u]=1,dep[u]=dep[ff]+1;
        for(auto v:e[u])
        {
            if(v==ff) continue;
            dfs1(v,u);si[u]+=si[v];f[u]+=f[v]+si[v];
            if(si[son[u]]<si[v]) son[u]=v;
        }
    }
    inline void dfs2(int u,int topf)
    {
        top[u]=topf;if(u==1) g[u]=f[u];
	    else g[u]=g[fa[u]]+(n-si[u])-si[u];
        dfn[u]=++cnt,id[cnt]=u;
        if(son[u]) dfs2(son[u],topf);
        for(auto v:e[u])
        {
            if(v==fa[u]||v==son[u]) continue;
            dfs2(v,v);
        }
    }
    inline int LCA(int x,int y)
    {
        while(top[x]!=top[y])
        {
            if(dep[top[x]]<dep[top[y]]) swap(x,y);
            x=fa[top[x]];
        }
        return dep[x]<dep[y]?x:y;
    }
    inline int dis(int x,int y){return dep[x]+dep[y]-(dep[LCA(x,y)]<<1);}
}
using namespace tree_decomposition;
inline void solve()
{
    n=read(),q=read();for(int i=1,u,v;i<n;i++) u=read(),v=read(),e[u].emplace_back(v),e[v].emplace_back(u);
    dfs1(1,0),dfs2(1,1);
    for(int i=1,x,y,z,lca;i<=q;i++)
    {
        x=read(),y=read();lca=LCA(x,y);
        if(dep[x]>dep[y]) swap(x,y);
        if(x!=lca)
        {
            int cnt=si[x]*si[y],res=f[x]*si[y]+f[y]*si[x];
            printf("%.6lf\n",res*1.0/cnt+dis(x,y)+1);continue;
        }z=y;while(dep[fa[top[z]]]>=dep[x]+1) z=fa[top[z]];
        z=id[dfn[z]-(dep[z]-dep[x]-1)];
        int cnt=(n-si[z])*si[y],res=(n-si[z])*f[y]+si[y]*(g[x]-f[z]-si[z]);
        printf("%.6lf\n",res*1.0/cnt+dis(x,y)+1);
    }
}
signed main()
{
    int T=1;while(T--) solve();
    genshin:;flush();return 0;
}
```

---

## 作者：violin_wyl (赞：0)

## Famil Door and Roads

### 解析：


换根dp + 倍增 + 预处理

根据期望的定义不难发现，我们需要求的答案其实是 所有环的长度的和/这样的环的个数。

变量声明：

$siz_u,f_u,g_u$ 分别表示在根为 $1$ 的意义下子树 $u$ 的大小，在根为 $1$ 的意义下子树 $u$ 所有子树的大小的和，在根为 $u$ 的意义下所有子树的大小的和（这里不懂没关系，接着往下看）。

对于每次询问的点 $a,b$ ，我们分成两类进行讨论

- 如果  $a,b$ 互相无祖先关系，那么环的个数实际上就是 $siz_a \times siz_b$，而对于所有环的总长度，我们可以把边分为三类：

  - 新加入环的边，每次加一条边，一共加了**环的个数**次，这类边一共有 $siz_a \times siz_b$ 条。

  - 原先在树中的边且出现在了每一个环上，这样的边其实就是路径 $a \rightarrow b$ 上的所有边，同样出现了 $siz_a \times siz_b$  次。

  - 原先在树中的边但出现在了 $a$  ($b$) 的子树内，这样的边是最复杂的，我们考虑对于一个在 $a$ 子树内的节点 $u$ ,那么经过边 $father_u\rightarrow u$ 的次数为 $siz_u\times siz_b$，我们发现原式等价于 $siz_b\times \sum_{u\in \mathrm S}siz_u$，这时候我们可以通过 $f$ 数组快速计算出 $\sum_{u\in \mathrm S}siz_u$ ，其中 $\mathrm S$ 表示子树 $a$ 中所有点的集合（但不包括 $a$，因为连接 $father_a\rightarrow a$ 的边属于第二种情况）。则这种边的总个数为 $(f_a-siz_a)\times siz_b+(f_b-siz_b)\times siz_a$

    综上：这部分的答案为 : （其实还可以化简，但没有必要）
    $$
    \frac{siz_a \times siz_b+siz_a \times siz_b\times dis(a,b)+(f_a-siz_a)\times siz_b+(f_b-siz_b)\times siz_a}{siz_a\times siz_b}
    $$
    ![1](https://cdn.luogu.com.cn/upload/image_hosting/7pvn841u.png)

    其中，如果我要让 $2,4$ 两个点共环，那在两个子树中任意各选一个顶点相连就可以使他们共环，其中，蓝色边是每次都需要经过的，绿色边有几率通过 。

  - 如果  a,b 互相有祖先关系，我们钦定 $a$ 为 $b$ 的祖先，那么环的个数实际上是 $siz_b \times (n-siz_{son_a})$ 其中 $son_a$ 一定也是 $b$  的祖先，（这部分可以通过倍增求解）。而总环的大小，我们同样分为三类：

    - 新加入环的边，每次加一条边，一共加了**环的个数**次，这类边一共有 $siz_b \times (n-siz_{son_a})$ 条。

    - 原先在树中的边且出现在了每一个环上，同上一种情况，一共 $siz_b \times (n-siz_{son_a}) \times dis(a,b)$  次。

    - 原先在树中的边但出现在了 $a$  ($b$) 的子树内，这部分边在 $b$ 的子树内仍然可以快速求出，因为子树 $a$ 以外的大小是很好算出的，即 $f_b \times (n-siz_{son_a})$，但如果我们需要算 $a$ 子树外的所有子树的答案，这时候我们就需要钦定 $a$ 为根了，这部分很明显就是换根dp的板子，我们算出 $g_{father_u}$ 后，通过 $g$ 的定义可以发现 $g_u=\sum_{v\in \mathrm S} f_v+f_{father_u}-f_u-siz_u+n$。其中，$f_{father_u}-f_u-siz_u$  表示以 $fa_u$ 为子树的根的情况下的所有子树的大小的和。那这部分不难推出答案为 $(g_a - f_{son_a} - n)\times siz_b$ 。这部分的式子为：
      $$
      \frac{siz_a \times siz_b+siz_a \times siz_b\times dis(a,b)+f_b \times (n-siz_{son_a})+(g_a - f_{son_a} - n)\times siz_b}{siz_a\times siz_b}
      $$

    注意：所有的 $f$ 都可以通过 $g$  容斥算出，但实际上更麻烦了。

----------------------------------------------------

## code：

```c++
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e5 + 10;
inline int read ( )
{
    int x = 0, f = 1;
    char ch = getchar ( );
    while (ch < '0' || ch > '9') {if (ch == '-') f = - 1; ch = getchar ( );}
    while (ch >= '0' && ch <='9') {x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar ( );}
    return x * f;
}
int n, q;
struct edge {
    int ver, nxt;
}e[N << 1];
int head[N], tot;
void add_edge (int u, int v) { e[++tot] = (edge) {v, head[u]}; head[u] = tot; }
int fa[N][20], depth[N], siz[N], lg[N];
int sum1[N], sum2[N]; // 即 f, g 数组
void dfs1 (int u, int f) 
{
    fa[u][0] = f; depth[u] = depth[f] + 1;
    siz[u] = 1;
    for (int i = 1; i <= lg[depth[u]]; i++)
        fa[u][i] = fa[fa[u][i - 1]][i - 1];
    for (int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].ver;
        if (v == f) continue;
        dfs1 (v, u);
        siz[u] += siz[v];
    }
    sum1[u] = siz[u];
    for (int i = head[u]; i; i = e[i].nxt) if (e[i].ver != f) sum1[u] += sum1[e[i].ver];
}
void dfs2 (int u, int f) // 换根dp
{
    if (u != 1) {
        for (int i = head[u]; i; i = e[i].nxt)
            if (e[i].ver != f) sum2[u] += sum1[e[i].ver];
        sum2[u] += (sum2[f] - sum1[u] + n - siz[u]);
    }
    for (int i = head[u]; i; i = e[i].nxt)
        if (e[i].ver != f)
        		dfs2 (e[i].ver, u);
}
int getlca (int x, int y)
{
    if (depth[x] < depth[y]) swap (x, y);
    while (depth[x] > depth[y]) x = fa[x][lg[depth[x] - depth[y]] - 1];
    if (x == y) return x;
    for (int i = lg[depth[x]]; i >= 0; i--)
        if (fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i];
    return fa[x][0];
}
int dis (int a, int b) { return depth[a] + depth[b] - 2 * depth[getlca (a, b)]; }
int find (int a, int b)
{
    for (int i = lg[depth[b]]; i >= 0; i--)
      	if (fa[b][i] && depth[fa[b][i]] > depth[a]) b = fa[b][i];
    return b;
}
signed main()
{
    n = read (); q = read ( );
    for (int i = 1, u, v; i < n; i++) {
        u = read ( ), v = read ( );
        add_edge (u, v); add_edge (v, u);
    }
    for (int i = 1; i <= n; i++) lg[i] = lg[i - 1] + (1 << lg[i - 1] == i);
    dfs1 (1, 0); sum2[1] = sum1[1]; dfs2 (1, 0);
    double len, num;
    while (q--) {
        int a = read ( ), b = read ( ); if (depth[a] > depth[b]) swap (a, b);
        int lca = getlca (a, b);
        if (lca == a) {
            num = (n - siz[find(a, b)]) * siz[b];
            len = num + ((sum2[a] - sum1[find(a, b)] - n) * siz[b] + (sum1[b] - siz[b]) * (n - siz[find(a, b)])) + dis(a, b) * num;
        }
        else {
            num = siz[a] * siz[b];
            len = num + ((sum1[a] - siz[a]) * siz[b] + (sum1[b] - siz[b]) * siz[a]) + dis(a, b) * num;
        }
        printf ("%.6lf\n", (double)len / (double)num);
    }
    return 0;
}
```



---

## 作者：pzc2004 (赞：0)

# 题目分析
我们首先以1为根。  
对于给定的 $a,b$，若 $lca_{a,b}$ 不是 $a,b$，则只有在分别连接 $a,b$ 的子树内的点时（分别记为 $x,y$），$a,b$ 才可能在一个环内，此时环的长度就是 $1+dis_{a,b}+dis_{a,x}+dis_{b,y}$，所以我们只需求出$dis_{a,x},dis_{b,y}$ 的期望长度即可，这只需求出 $a$ 子树内所有点到 $a$ 的距离和，再除以 $size_a$ 即可，对 $b$ 同理，这个直接DP即可求出。  
若 $lca_{a,b}$ 是 $a,b$ 中的一个（这里假设等于 $a$），则我们需要求出 $a$ 的儿子中在 $(a,b)$ 这条链上的儿子，即 $b$ 的$dep_b-dep_a-1$ 级祖先(记为 $son$)。然后可以发现只有在连接 $b$ 的子树内的点（记为 $x$）和除去 $son$ 的子树外的所有点(记为 $y$)时，$a,b$ 才可能在一个环内，此时环的长度就是 $1+dis_{a,b}+dis_{a,x}+dis_{b,y}$，所以我们只需求出$dis_{a,x},dis_{b,y}$ 的期望长度即可，$dis_{b,y}$ 的期望的计算方法同上，$dis_{a,x}$ 的期望需要我们求出所有点到 $a$ 的长度和，再减去 $son$ 的贡献，再除以 $n-size_{son}$，这个需要换根DP。  
我使用了倍增来在线求LCA和K级祖先，复杂度 $O(NlogN)$，但其实可以用离线求LCA和K级祖先来做到 $O(N)$
``` cpp
#include <bits/stdc++.h>
using namespace std;
template <class T>
inline void read(T &x)
{
	x= 0;
	char c= getchar();
	while(!isdigit(c)) c= getchar();
	while(isdigit(c)) x= x * 10 + (c & 15), c= getchar();
}
#define N 100001
int n, m, head[N], cnt, dep[N], fa[N][17], sz[N];
long long a1[N], a2[N];//a1x表示x子树内节点到x的距离和,a2x表示x除去x子树外的所有点到x的距离和
struct Edge
{
	int a, b;
} e[N << 1];
inline void add(int a, int b)
{
	e[++cnt].a= head[a], e[cnt].b= b, head[a]= cnt;
}
inline void dfs1(int x, int y)//第一遍dfs求出a1数组
{
	fa[x][0]= y, sz[x]= 1;
	for(int i= 1; i < 17; i++) fa[x][i]= fa[fa[x][i - 1]][i - 1];
	for(int i= head[x]; i; i= e[i].a)
	{
		if(e[i].b == y) continue;
		dep[e[i].b]= dep[x] + 1, dfs1(e[i].b, x);
		sz[x]+= sz[e[i].b];
		a1[x]+= a1[e[i].b] + sz[e[i].b];//从儿子转移
	}
}
inline void dfs2(int x, int y)//第二遍dfs求出a2数组
{
	for(int i= head[x]; i; i= e[i].a)
	{
		if(e[i].b == y) continue;
		a2[e[i].b]= a2[x] + n - sz[x] + 1 + a1[x] - a1[e[i].b] - sz[e[i].b] + sz[x] - sz[e[i].b] - 1;//计算祖先的贡献和父亲的其他儿子的贡献
		dfs2(e[i].b, x);
	}
}
inline int lca(int x, int y)//倍增求LCA
{
	int k= dep[y] - dep[x];
	for(int i= 0, j= 1; i < 17; i++, j<<= 1)
		if(k & j) y= fa[y][i];
	if(x == y) return x;
	for(int i= 16; i >= 0; i--)
		if(fa[x][i] != fa[y][i]) x= fa[x][i], y= fa[y][i];
	return fa[x][0];
}
inline int ancestor(int x, int k)//倍增求K级祖先
{
	for(int i= 0, j= 1; i < 17; i++, j<<= 1)
		if(k & j) x= fa[x][i];
	return x;
}
signed main()
{
	read(n), read(m);
	for(int i= 1, x, y; i < n; i++) read(x), read(y), add(x, y), add(y, x);
	dfs1(1, 0), dfs2(1, 0);
	for(int i= 1, x, y; i <= m; i++)
	{
		read(x), read(y);
		if(dep[x] > dep[y]) swap(x, y);
		int l= lca(x, y);
		if(x == l)//x是两个点的LCA，即上文的第二种情况
		{
			int a= ancestor(y, dep[y] - dep[x] - 1);
			double ans= 1 + 1.0 * (a2[x] + a1[x] - a1[a] - sz[a]) / (n - sz[a]) + 1.0 * a1[y] / sz[y] + dep[y] - dep[x];
			printf("%0.10lf\n", ans);
		}
		else//上文的第一种情况
		{
			double ans= 1 + 1.0 * a1[x] / sz[x] + 1.0 * a1[y] / sz[y] + dep[x] + dep[y] - (dep[l] << 1);
			printf("%0.10lf\n", ans);
		}
	}
	return 0;
}
```

---

