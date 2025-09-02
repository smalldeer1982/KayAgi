# [USACO11DEC] Grass Planting G

## 题目描述

给出一棵有 $n$ 个节点的树，有 $m$ 个如下所示的操作：

- 将两个节点之间的 **路径上的边** 的权值均加一。

- 查询两个节点之间的 **那一条边** 的权值，保证两个节点直接相连。

初始边权均为 0。

## 说明/提示

对于 $100\%$ 的数据，$2\le n\le 10^5$，$1\le m\le 10^5$。

## 样例 #1

### 输入

```
4 6 
1 4 
2 4 
3 4 
P 2 3 
P 1 3 
Q 3 4 
P 1 4 
Q 2 4 
Q 1 4 
```

### 输出

```
2 
1 
2 

```

# 题解

## 作者：LeavingZzz (赞：66)

Upd On 2020-03-18 既然题单都出了那么就把原来的剪贴板换成题单吧qwq  
此篇题解意在提供一套树链剖分边权转点权的板子。
# A Solution For P3038
需要的前置芝士(没吃过的请加餐):  
[线段树](https://www.luogu.com.cn/problem/P3373)  [轻重链剖分](https://www.luogu.com.cn/problem/P3384)  
前置芝士次掉以后,你应该知道了使用树链剖分和线段树结合来处理以下几种基本问题:  
- 维护树上任意两点间简单路径包含的点的点权 和/最大值
- 维护树上任意单点的点权信息
- 维护树上任意一棵子树内的点权 和/最大值  

核心思想是通过剖分将其划分成可用线段树操作的区间,再利用线段树进行维护  
但是对于这一道题目,是要维护树上边权的相关信息,怎么办呢？
我们可以将边权转化为点权。（这个人又在说废话了）  
但是怎么转化？？  
我们的转化肯定是要将边映射到点上,很明显我们不可以让一个点同时对应多条边,也不可以让一条边对应多个点,这两种情况都是无法使用线段树进行相应维护的  
所以只能一对一进行映射  
画一棵树,观察一下,很快就可以发现,对于每一条边的两端的节点,我们只能选一个映射,而我们会选择深度较深的点进行映射,否则如果这个深度较浅的节点有多个儿子,这些儿子都会映射到这个节点上,GG。  

**下面给出树链剖分边权转点权的模板,代码后会有核心代码总结。**  

包含操作  
- 路径 询问/更新(边权和)
- 子树 询问/更新(边权和)  

```cpp
#include<bits/stdc++.h>
using namespace std;
int N,Q; 
inline int max_(const int &x,const int &y)
{
	return x>y?x:y;
}
const int maxn=2007;//总结点数
int TREE[maxn<<2];//四倍空间线段树
int lazy[maxn<<2];//懒惰标记数组,大小要开成与线段树一一对应
struct E{
	int u,v,w;
}e[maxn<<1];//树不定形要存双向边 
int first[maxn],nt[maxn<<1],ES;//邻接表
inline void addE(int u,int v,int w)//加边函数 
{
	e[++ES]=(E){u,v,w};
	nt[ES]=first[u];
	first[u]=ES;
	return ;
}
int sz[maxn]/*树大小*/,fa[maxn]/*直属父亲*/,top[maxn]/*链头结点*/;
int son[maxn]/*重儿子*/,depth[maxn]/*深度*/;
int id[maxn]/*结点->线段树编号*/,anti[maxn]/*线段树编号->结点*/;
int ix,A[maxn]/*在做点权树剖时的点权数组*/;
inline void DFS(int u)
{
	int v;sz[u]=1;//大小初始化 
	for(int i=first[u];i;i=nt[i])
	{
		v=e[i].v;
		if(v!=fa[u])//不能死转圈
		{
			depth[v]=depth[u]+1;
			fa[v]=u;//v的父亲是u
			A[v]=e[i].w;//转化关键代码1,将连向子节点的边权直接赋给子节点
			DFS(v);
			sz[u]+=sz[v];//维护大小
			if(sz[son[u]]<sz[v]) son[u]=v;//重儿子 
		}
	}
	return ; 
}
inline void dfs(int u,int tp)
{
	id[u]=++ix;anti[ix]=u;//建立正反映射
	top[u]=tp;//链头
	if(son[u]) dfs(son[u],tp);//优先遍历重儿子
	int v;
	for(int i=first[u];i;i=nt[i])
	{
		v=e[i].v;
		if(v==son[u]||v==fa[u]) continue;
		dfs(v,v);
	}
	return ;
}
#define mid (L+R>>1)
#define L(i) (i<<1)
#define R(i) (i<<1|1)//涉及到优先级较低的位运算建议加括号 
inline void Build(int L,int R,int i)
{
	if(L==R)
	{
		TREE[i]=A[anti[L]];//之前已经进行了转化可以不改变这里
		return ; 
	}
	Build(L,mid,L(i));
	Build(mid+1,R,R(i));
	TREE[i]=TREE[L(i)]+TREE[R(i)];
	return ;
}
inline void LAZY(int L,int R,int i)
{
	if(!lazy[i]) return ;
	lazy[L(i)]+=lazy[i];
	lazy[R(i)]+=lazy[i];
	TREE[L(i)]+=(mid-L+1)*lazy[i];
	TREE[R(i)]+=(R-mid)*lazy[i];
	lazy[i]=0;//高频错点！！ 
	return ;
}
inline void Update(int L,int R,int l,int r,int i,int k)
{
	if(l<=L&&R<=r)
	{
		TREE[i]+=k*(R-L+1);
		lazy[i]+=k;
		return ;
	}
	LAZY(L,R,i);//任何时候访问子节点都需要下传标记 
	if(l<=mid) Update(L,mid,l,r,L(i),k);
	if(r>mid) Update(mid+1,R,l,r,R(i),k);
	TREE[i]=TREE[L(i)]+TREE[R(i)];
	return ;
}
inline int Query(int L,int R,int l,int r,int i)
{
	if(l<=L&&R<=r)
		return TREE[i];
	LAZY(L,R,i);
	int ans=0;
	if(l<=mid) ans+=Query(L,mid,l,r,L(i));
	if(r>mid) ans+=Query(mid+1,R,l,r,R(i));
	return ans; 
}
inline void Update_Path(int x,int y,int k)
{
	while(top[x]!=top[y])
	{
		if(depth[top[x]]<depth[top[y]]) swap(x,y);
		Update(1,N,id[top[x]],id[x],1,k);
		x=fa[top[x]];
	}
	if(depth[x]>depth[y]) swap(x,y);
	Update(1,N,id[x],id[y],1,k);
	Update(1,N,id[x],id[x],1,-k);//核心代码2 
	return ;
}
inline int Query_Path(int x,int y)
{
	int ans=0;
	while(top[x]!=top[y])
	{
		if(depth[top[x]]<depth[top[y]]) swap(x,y);
		ans+=Query(1,N,id[top[x]],id[x],1);
		x=fa[top[x]];
	}
	if(depth[x]>depth[y]) swap(x,y);
	ans+=Query(1,N,id[x],id[y],1); 
	ans-=Query(1,N,id[x],id[x],1);//核心代码3 
	return ans;
}
inline int Re()
{
	char c;
	int re;
	while((c=getchar())>'9'||c<'0');
	re=c-48;
	while((c=getchar())>='0'&&c<='9')
	re=re*10+c-48;
	return re;
}
int main()
{
	N=Re();Q=Re();
	int u,v,w;
	for(int i=1;i<N;i++)
	{
		u=Re();v=Re();w=Re();
		addE(u,v,w);addE(v,u,w);
	}
	DFS(1);dfs(1,1);
	Build(1,N,1);
	int op;
	for(int i=1;i<=Q;i++)
	{
		op=Re();
		if(op==1)//路径更新
		{
			u=Re();v=Re();w=Re();
			Update_Path(u,v,w);
		}
		else if(op==2)//子树更新
		{
			u=Re();w=Re();
			Update(1,N,id[u],id[u]+sz[u]-1,1,w);
		}
		else if(op==3)//路径询问
		{
			u=Re();v=Re();
			printf("%d\n",Query_Path(u,v));
		}
		else//子树询问
		{
			u=Re();
			printf("%d\n",Query(1,N,id[u],id[u]+sz[u]-1,1));
		}
	}
	return 0;
}
```
上面这份板子是我认为最简单的转化方式,与点权树链剖分相比仅仅多了 $3$ 句话  
- 在进行 $DFS$ 遍历时即将进入子节点时将边权赋给子节点  
$A[v]=e[i].w$   

- 在进行路径更新的时候最后一步在 $LCA$ 上减去 $k$,因为 $LCA$ 代表的边权并不在所更新路径中(自己画图可以感受一下,画那种同一个父亲从一个子树到另外一个子树的路径就会发现父节点代表的边不算),$Update(1,N,id[x],id[x],1,-k)$

- 在进行路径查询的时候最后也会把多查询的 $LCA$ 代表的边权减掉   
$ans-=Query(1,N,id[x],id[x],1)$    


这是利于理解的版本哦,实际上我们在用的时候第二条和第三条都没有,而是将原来的  
```cpp
Update(1,N,id[x],id[y],1,k)  Query(1,N,id[x],id[y],1)
```
直接修改为  
```
Update(1,N,id[x]+1,id[y],1,k)  Query(1,N,id[x]+1,id[y],1)
```
而为什么我在这里没有写呢？
因为有时候当 $x$ 和 $y$ 跳到同一条链上时二者刚好重合,这时候加一会让进入线段树时出现 $l>r$ 这是不符合定义的,不利于理解。  
只不过线段树的 $feature$ 刚好让这种 $l=r+1$ 的情况什么都查不到就退出了函数,所以修改后因为加过一次 $1$ 而此时 $x$ 和 $y$ 恰好在一条链上,可以刚好忽略点 $x$ 的权值达到我们的目的，修改一句话就达到了两句话的效果。  

那么这道题在泥掌握上面的模板之后就可以轻松切掉了。  

树链剖分是像我这样的蒟蒻经常窒息的一个东西,最怕的就是 $\text{Segment Fault}$ 但是总是有一个过程的啊,[如果泥多练](https://www.luogu.com.cn/training/1654#information),每次都直接重新打,~~在你吐之前~~一定能够**熟练**掌握这个算法！！  
那些十几分钟切树剖一次过的神仙并不是刚学就这样,也只有一个信条  
**无他,唯手熟尔**  
$\text{The End}$

---

## 作者：grass8cow (赞：21)

总体思路：树链剖分以及一个支持区间修改，单点查询的线段树。

前置知识：[P3384 【模板】轻重链剖分](https://www.luogu.com.cn/problem/P3384)

（这道模板题包含了今天要用的所有操作，如线段树，树链剖分）

知道了这个知识，我们解决这道题就很容易了。

注意1：

线段树可以修改、查询的是点权，而题中修改、查询的是边权。我们该怎么办呢？

可以把边权转换为点权。注意到每个点与它爸爸只有一条边相连，那么一个点的权值就等于这条边的权值。

当然，对于根节点来讲是根本不存在的，因为它没有爸爸。

注意2：

对于两点间的路径上所有边权加一的操作，值得注意的是，它俩的最近公共祖先，也就是 LCA 所对应的边是不做操作的。

两点跳到同一重链上时，深度小的那个点就是 LCA。那么，我们最后只需要修改 $[id[u]+1,id[v]]$ 这个区间（此处 $d[u]<d[v]$ ），就巧妙地避免了 LCA 被修改的惨状。因为 $id[u]$ 这个点在区间外。

想要更详细的内容，就来看我的代码吧！（个人喜欢用 vector 以及 ~~龟速~~ cin 与 cout ）

```
#include<bits/stdc++.h>
using namespace std;
int n,m;
int fa[100001];//每个点的爸爸 
int d[100001];//每个点的深度
int son[100001];//每个点的重儿子
int su[100001];//一个点为根节点时该子树内的点数 
int top[100001];//每个点在树剖后所在链的顶端 
int id[100001];//每个点在线段树里所在的位置 
vector<int>g[100001];//大爱vector存图 
void dfs1(int x,int f,int deep)
{
	fa[x]=f;d[x]=deep;su[x]=1;int maxs=0,i;
	for(i=0;i<g[x].size();i++)
	{
		int v=g[x][i];
		if(v!=f)
		{
			dfs1(v,x,deep+1);
			su[x]+=su[v];
			if(maxs<su[v])
			{
				son[x]=v;
				maxs=su[v];
			}
		}
	}
}
void dfs2(int x,int fafa)
{
	top[x]=fafa;id[x]=++id[0];
	if(!son[x])return;
	dfs2(son[x],fafa);
	for(int i=0;i<g[x].size();i++)
	{
		int v=g[x][i];
		if(fa[x]==v||son[x]==v)continue;
		dfs2(v,v);
	}
}//很经典的两个dfs完成树剖 
struct qq
{
	int l,r,sum,add;
}q[400001];
void build(int p,int l,int r)
{
	q[p].l=l;q[p].r=r;
	if(l==r)return;
	build(p*2,l,(l+r)/2);
	build(p*2+1,(l+r)/2+1,r);
}
void pd(int p)
{
	q[p*2].add+=q[p].add;q[p*2+1].add+=q[p].add;
	q[p*2].sum+=(q[p*2].r-q[p*2].l+1)*q[p].add;
	q[p*2+1].sum+=(q[p*2+1].r-q[p*2+1].l+1)*q[p].add;
	q[p].add=0;
}
void change(int p,int x,int y)
{
	if(q[p].r<x||q[p].l>y)return;
	if(q[p].l>=x&&q[p].r<=y)
	{
		q[p].sum+=q[p].r-q[p].l+1;
		q[p].add++;
		return;
	}
	pd(p);
	change(p*2,x,y);
	change(p*2+1,x,y);
	q[p].sum=q[p*2].sum+q[p*2+1].sum;
} 
int ask(int p,int x)
{
	if(q[p].r<x||q[p].l>x)return 0;
	if(q[p].l==q[p].r)return q[p].sum;
	pd(p);
	return ask(p*2,x)+ask(p*2+1,x);
}//线段树的操作
int main()
{
	int x,y,i;
	char c;
	cin>>n>>m;
	for(i=1;i<n;i++)
	{
		cin>>x>>y;
		g[x].push_back(y);
		g[y].push_back(x);//存无向边 
	}
	dfs1(1,0,1);
	dfs2(1,1);
	build(1,1,n);
	while(m--)
	{
		cin>>c>>x>>y;
		if(c=='P')
		{
			while(top[x]!=top[y])
			{
				if(d[top[x]]<d[top[y]])swap(x,y);
				change(1,id[top[x]],id[x]);
				x=fa[top[x]];
			}
			if(d[x]>d[y])swap(x,y);
			change(1,id[x]+1,id[y]);//用上述方法避开LCA 
		}
		else
		{
			if(fa[x]==y)cout<<ask(1,id[x])<<endl;
			else cout<<ask(1,id[y])<<endl;//判断该边的边权是哪个点的点权 
		}
	}
	return 0;
}//美滋滋AC
```


---

## 作者：微雨燕双飞 (赞：14)

题解这么少，超级蒟蒻补一发。大佬们用的不是线段树（我不会），就是树链剖分（我还是不会），于是用了最傻的vector存图+倍增求LCA+树状数组用差分思想维护前缀和（貌似还没超过提高组的考纲），应该是目前最朴素（sha）的做法了。

由于蒟蒻不会压行大法，因此程序十分冗长，共94行，跑得还贼慢，加了O2、快读和一堆inline、register得了488ms（巨佬：叫你不学好邻接表，要用vector偷懒，这么慢真是没谁了）

好了，废话不多说，开看代码：
```cpp
#include<cstdio>
#include<vector>
using namespace std;
const int N=1e5+10;
vector<int> g[N]; //vector代替邻接表存图（不要学我）
int n,m,time,fa[N][21],d[N],l[N],r[N],t[N]; 
inline int read() //满大街的快读
{
  char c; int sign=1;
  while((c=getchar())<'0'||c>'9')
    if(c=='-') sign=-1;
  int res=c-'0';
  while((c=getchar())>='0'&&c<='9')
    res=res*10+c-'0';
  return res*sign;
}
void dfs(int u,int p) //倍增预处理之dfs，作用有二：1.标记每个点在树中的深度 2.标记每个点的父亲（2的0次方代祖先）
{
  d[u]=d[p]+1;
  fa[u][0]=p;
  time++;
  l[u]=time;
  for(register int i=0; i<g[u].size(); i++)
  {
    int v=g[u][i];
    if(v!=p) dfs(v,u);
  }
  r[u]=time;
}
int lca(int u,int v) //倍增求LCA
{
  if(d[u]<d[v]) swap(u,v); //让深度大的向上跳，直到u、v深度相同
  for(register int k=20; k>=0; k--)
    if(d[u]-d[v]>=(1<<k)) u=fa[u][k]; 
  if(u==v) return u; //如果已经汇成一点，那么这点就是LCA
  for(register int k=20; k>=0; k--)
    if(fa[u][k]!=fa[v][k]) //否则u和v一起向上跳，直到拥有相同父亲
    {
      u=fa[u][k];
      v=fa[v][k];
    }
  return(fa[u][0]); //求得u和v的LCA
}
inline void add(int i,int d) //树状数组单点修改
{
  while(i<=n)
  {
    t[i]+=d;
    i+=i&-i; 
  }
}
inline int sum(int i) //树状数组前缀和维护
{
  int s=0;
  while(i>0)
  {
    s+=t[i];
    i-=i&-i;
  }
  return s;
}
int main()
{
  n=read(); m=read();
  for(register int i=1; i<=n-1; i++) 
  {
    int u,v; 
    u=read(); v=read();
    g[u].push_back(v); //建树，双向有向边
    g[v].push_back(u); 
  } 
  dfs(1,0);
  for(register int k=1; k<=20; k++) //倍增预处理之fa数组（其中k取logn左右的一个数即可，可以稍微取大一些）
    for(register int u=1; u<=n; u++)
      fa[u][k]=fa[fa[u][k-1]][k-1]; //u的2的k次方代祖先是u的2的k-1次方代祖先的2的k-1次方代祖先（好绕啊。。。）
  for(register int i=1; i<=m; i++) 
  {
    char cmd; int u,v;
    scanf("%s",&cmd); u=read(); v=read();
    if(cmd=='P')
    {
      int p=lca(u,v); //查询LCA
      add(l[u],1);
      add(l[v],1);
      add(l[p],-2); //树状数组差分思想，先加到两处，再在一处减回
    } 
    else
    {
      if(d[u]<d[v]) u=v; //保证深度大的为u，小的为v
      printf("%d\n",sum(r[u])-sum(l[u]-1)); 
    } //树状数组查询r[u]和l[u]之间的区间和（前缀和相减）
  }
  return 0; 
} //结束
```

---

## 作者：CodyTheWolf (赞：11)

## 既然各位dalao都用的线段树+树剖或者LCA+树状数组，那为什么不用一下树状数组+树剖呢~？（滑稽
## 目前开O2后是本题的RANK2
Accepted  100 
用时: 172ms / 内存: 19480KB


------------


### 前置知识：树链剖分[P3384](https://www.luogu.org/problemnew/show/P3384)树状数组2（区间添加单点查询，差分）[P3368](https://www.luogu.org/problemnew/show/P3368)



------------

### 大致思路：

1.读入，连边，树剖。

-

2.对于'P'操作，我们只需在这个路径上的除了公共祖先以外的所有点添加1即可。

可以在草稿纸上随便画上一颗树，每次**在边上添加**可以转化为**添加某条边的底端**（即深度大的那个点），显而易见，这样做，**一个点是必定对应一条边的。**

但LCA那个点不属于我们要查的路径，所以当两个点跳到一条链上时，设x的深度小于y的深度，id[x]为x在树状数组上的编号，那么id[x]（即LCA）不在这条路径上，添加时只添加(id[x]+1,id[y])即可~！

-

3.对于'Q'操作，因为题目说在查询的时候只需要查**“一条边”**，而不是**“一段路径”**。所以在树状数组上单点查寻两端点深的那个端点即可（深的那个代表了一条边，如思路2所述）。

## CODE（附有简单注释）：
```cpp
#pragma warning (disable:4996)
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define RG register
using namespace std;
const int maxn = 1e5 + 5, maxm = maxn << 1;
int head[maxm], nxt[maxm], v[maxm]/*前向星*/, dad[maxn]/*某点父亲*/, son[maxn]/*重儿子*/,
sz[maxn]/*子树大小*/, depth[maxn]/*深度*/, id[maxn]/*某点在树状数组上的对应编号*/, top[maxn]/*重链头*/;

int n, m, cnt/*前向星用*/, root/*树根*/, num/*树剖用dfs序*/;

struct Binary_Indexed_Tree//结构体封装树状数组！
{
	int c[maxn];
	inline int lowbit(int k) { return k & (-k); }
	inline void add(int x, int k) { for (int i = x; i <= n; i += lowbit(i)) c[i] += k; }
	inline int sum(int x) { int ans = 0; for (int i = x; i; i -= lowbit(i))	ans += c[i]; return ans; }
	inline void update(int l, int r, int k) { add(l, k), add(r + 1, -k); }//区间加法
}BIT;
//以下是前向星，快读写和树剖
inline void addline(int x, int y) { v[cnt] = y, nxt[cnt] = head[x], head[x] = cnt++; }

inline int read()
{
	RG char c = getchar(); RG int x = 0;
	while (c<'0' || c>'9')	c = getchar();
	while (c >= '0'&&c <= '9')	x = (x << 3) + (x << 1) + c - '0', c = getchar();
	return x;
}

inline void write(int x)
{
	if (x > 9)	write(x / 10);
	putchar(x % 10 + '0'); return;
}

inline void dfs1(int x, int f, int d)
{
	dad[x] = f, depth[x] = d, sz[x] = 1;
	for (RG int i = head[x]; i != -1; i = nxt[i])
	{
		if (v[i] == f)	continue;
		dfs1(v[i], x, d + 1);
		sz[x] += sz[v[i]];
		if (sz[v[i]] > sz[son[x]])	son[x] = v[i];
	}
	return;
}

inline void dfs2(int x, int t)
{
	id[x] = ++num, top[x] = t;
	if (!son[x])	return;
	dfs2(son[x], t);
	for (RG int i = head[x]; i != -1; i = nxt[i])
		if (v[i] != dad[x] && v[i] != son[x])	dfs2(v[i], v[i]);
	return;
}
//添加操作！
inline void add(int x, int y, int k)
{
	RG int tx = top[x], ty = top[y];
	while (tx != ty)
	{
		if (depth[tx] >= depth[ty])	BIT.update(id[tx], id[x], k), x = dad[tx], tx = top[x];
		else BIT.update(id[ty], id[y], k), y = dad[ty], ty = top[y];
	}
	if (x == y)	return;//如果x==y不退出，线段树里会出现查询区间[l,r]出现l>r的情况
	if (id[x] <= id[y]) BIT.update(id[x] + 1, id[y], k);//记得+1避免LCA那个点
	else BIT.update(id[y] + 1, id[x], k);
	return;
}

int main()
{
	memset(head, -1, sizeof(head));
	n = read(), m = read();
	for (RG int i = 1; i < n; i++) { int x = read(), y = read(); addline(x, y), addline(y, x); }
	srand(19260817), root = rand() % n + 1, dfs1(root, 0, 1), dfs2(root, root);//随机选根！（用了一个很暴力的树快了4ms ？？？
	while (m--)
	{
		RG char c = getchar(); RG int x, y;
		while (c != 'P' && c != 'Q')	c = getchar();	x = read(), y = read();
		if (c == 'P')	add(x, y, 1);//直接调用
		if (c == 'Q')	depth[x] > depth[y] ? write(BIT.sum(id[x])) : write(BIT.sum(id[y])), putchar('\n');
		//看不懂的也可以翻译成：
		//if(depth[x]>depth[y])	write(BIT.sum(id[x]));
		//else	write(BIT.sum(id[y]));
		//putchar('\n');
		//即选取深度大的那个点进行查询
	}
	return 0;
}
```




---

## 作者：傅思维666 (赞：8)

## 题目大意：

给定一个有N个节点的树及M个操作：P操作把一条路径上的边权加一，Q操作询问一条路径上的权值和。



## 题解：

一道树链剖分的题。（板子题都是紫题了为啥这题还是蓝？）

难点有二：

一：边权转点权。

二：路径和的查询。

对于对树链剖分不是和熟悉的小伙伴，推荐下面的这篇博客，里面有对树链剖分的详细讲解。

[浅谈树链剖分](https://www.cnblogs.com/fusiwei/p/11519470.html)

我们会发现，树链剖分是一个对点权进行操作的东西。

而题目要求是边权。

所以我们要把边权转点权~~（废话）~~。

怎么转呢？

我们会发现一条边连着两个点，因为题目保证给出的是一棵树。我们会发现：一个点可能会有很多个儿子（也就是说有很多连着儿子的边），但是每个儿子只有一个父亲。对应地一层一层类比，我们会发现到叶子节点的时候，它连儿子也没有。

那么我们就可以考虑把边权变成其儿子节点的点权，那么根节点的点权为0，而其他所有边的边权都被映射到了一个点上。

截至这里，我们解决了第一个问题。

如果我们到这里就完事的话，我们最终会全WA。

为什么呢？

还是因为题目中询问的是边权。如果是一个路径的话，比如题目中想求得两条边的权值，但是我们映射完了之后会求得3个点的点权，也就意味着，我们多搞了一个答案。这显然是不符合正确性的。

因为我们是向子节点映射，所以我们多加的其实是目标点的LCA那个点的点权。

所以我们考虑把LCA那个点的点权减掉。

那么我们回顾一下树链剖分求LCA的过程（如有不懂还是翻上面的那篇博客）

我们跳来跳去，最后跳的那一次就能求到LCA，也就是说，我们为了维护查询的正确性，需要把最后一次跳跃的更浅的那个节点变成它的子节点。这样就能保证，LCA不会被加进来。

这个操作的正确性是显然的。因为LCA跳到最后，两个节点必然在一条重链上。而根据树链剖分的预处理操作，一条重链上的节点编号是连续的，那么我们寻找LCA进行跳跃的时候，id[x]就是我们的LCA，那么我们把它+1，就会得到它的儿子节点，这样，LCA就不会被加进来。

代码加深理解：

```cpp
#include<cstdio>
#include<algorithm>
#include<iostream>
#pragma GCC optimize(1)
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#define lson pos<<1
#define rson pos<<1|1
using namespace std;
const int maxn=1e5+1;
int n,m,tot,cnt;
int a[maxn];
int head[maxn],nxt[maxn<<1],to[maxn<<1];
int deep[maxn],size[maxn],son[maxn],fa[maxn];
int top[maxn],id[maxn],w[maxn];
int tree[maxn<<2],lazy[maxn<<2];
void add(int x,int y)
{
    to[++tot]=y;
    nxt[tot]=head[x];
    head[x]=tot;
}
void dfs1(int x,int f)
{
    deep[x]=deep[f]+1;
    size[x]=1;
    fa[x]=f;
    for(int i=head[x];i;i=nxt[i])
    {
        int y=to[i];
        if(y==f)
            continue;
        dfs1(y,x);
        size[x]+=size[y];
        if(!son[x]||size[y]>size[son[x]])
            son[x]=y;
    }
}
void dfs2(int x,int t)
{
    id[x]=++cnt;
    w[cnt]=a[x];
    top[x]=t;
    if(!son[x])
        return;
    dfs2(son[x],t);
    for(int i=head[x];i;i=nxt[i])
    {
        int y=to[i];
        if(y==fa[x]||y==son[x])
            continue;
        dfs2(y,y);
    }
}
void build(int pos,int l,int r)
{
    int mid=(l+r)>>1;
    if(l==r)
    {
        tree[pos]=w[l];
        return;
    }
    build(lson,l,mid);
    build(rson,mid+1,r);
    tree[pos]=tree[lson]+tree[rson];
}
void mark(int pos,int l,int r,int k)
{
    tree[pos]+=(r-l+1)*k;
    lazy[pos]+=k;
}
void pushdown(int pos,int l,int r)
{
    int mid=(l+r)>>1;
    mark(lson,l,mid,lazy[pos]);
    mark(rson,mid+1,r,lazy[pos]);
    lazy[pos]=0;
}

void update(int pos,int l,int r,int x,int y,int k)
{
    int mid=(l+r)>>1;
    if(x<=l && r<=y)
    {
        mark(pos,l,r,k);
        return;
    }
    pushdown(pos,l,r);
    if(x<=mid)
        update(lson,l,mid,x,y,k);
    if(y>mid)
        update(rson,mid+1,r,x,y,k);
    tree[pos]=tree[lson]+tree[rson];
}

void upd_chain(int x,int y,int k)
{
    while(top[x]!=top[y])
    {
        if(deep[top[x]]<deep[top[y]])
            swap(x,y);
        update(1,1,n,id[top[x]],id[x],k);
        x=fa[top[x]];
    }
    if(deep[x]<deep[y])
        swap(x,y);
    update(1,1,n,id[y]+1,id[x],k);
}
int query(int pos,int l,int r,int x,int y)
{
    int ret=0;
    int mid=(l+r)>>1;
    if(x<=l && r<=y)
        return tree[pos];
    pushdown(pos,l,r);
    if(x<=mid)
        ret+=query(lson,l,mid,x,y);
    if(y>mid)
        ret+=query(rson,mid+1,r,x,y);
    return ret;
}
int q_chain(int x,int y)
{
    int ret=0;
    while(top[x]!=top[y])
    {
        if(deep[top[x]]<deep[top[y]])
            swap(x,y);
        ret+=query(1,1,n,id[top[x]],id[x]);
        x=fa[top[x]];
    }
    if(deep[x]<deep[y])
        swap(x,y);
    ret+=query(1,1,n,id[y]+1,id[x]);
    return ret;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<n;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        add(x,y);
        add(y,x);
    }
    dfs1(1,0);
    dfs2(1,1);
    build(1,1,n);
    while(m--)
    {
        char ch;
        cin>>ch;
        if(ch=='P')
        {
            int x,y;
            scanf("%d%d",&x,&y);
            upd_chain(x,y,1);
        }
        else
        {
            int x,y;
            scanf("%d%d",&x,&y);
            printf("%d\n",q_chain(x,y));
        }
    }
    return 0;
}
```



---

## 作者：Drifterming (赞：8)

```
//树剖是在点上操作的，这道题是边
//那么怎么把边权转成点权呢？
//根据树的性质可以知道，一个点可以有多个儿子，但是只会有一个爸爸，
//所以我们可以把这个点和它爸爸之间的那条边的边权转移到这个点上来
//用这个点的点权来表示这条边的权值
//因为根节点没有爸爸，所以它不表示任何边权，点权为0
//但是我们怎么样才能不把两个点的公共祖先的权值算进去啊？
//node[fx].s+1? 不行，这是它的重儿子的位置
// 考虑一下，我们在Query或者Modify的时候，都是当x和y同时处于一条链了之后就break
//然后再把这条链加上，最近公共祖先不就是这条链的top嘛！
//所以，我们在while循环外边写node[x].s+1就可以不算上公共祖先了。
//但是也要注意，如果最后是条轻边，我们就要if特判一下，不能让他进线段树查询了
//因为如果是轻边的话，最后的那条链退化成了最近公共祖先这一个点，不能要！ 

#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int N=1e5+5;

int n,m;
int w[N];
int head[N],num_edge;
struct Edge
{
	int v,nxt;
}edge[N<<1];
struct Node
{
	int fa,son;
	int dep,top;
	int size;
	int s,t;
}node[N];
struct TREE
{
	TREE *lson,*rson;
	int l,r,mid,len;
	int num,lazy;
}tree[N<<2];

typedef TREE* Tree;
Tree Root,now_node=tree;

inline int read()
{
	char c=getchar();int num=0;
	for(;!isdigit(c);c=getchar())
		if(c=='P') return 1;
		else if(c=='Q')	return 2;
	for(;isdigit(c);c=getchar())
		num=num*10+c-'0';
	return num;
}

inline void add_edge(int u,int v)
{
	edge[++num_edge].v=v;
	edge[num_edge].nxt=head[u];
	head[u]=num_edge;
}

void dfs1(int u)
{
	node[u].size=1;
	for(int i=head[u],v;i;i=edge[i].nxt)
	{
		v=edge[i].v;
		if(v==node[u].fa)
			continue;
		node[v].fa=u;
		node[v].dep=node[u].dep+1;
		dfs1(v);
		node[u].size+=node[v].size;
		if(node[v].size>node[node[u].son].size)
			node[u].son=v;
	}
}

int bound;
void dfs2(int u,int top)
{
	node[u].top=top;
	node[u].s=++bound;
	if(node[u].son)
	{
		dfs2(node[u].son,top);
		for(int i=head[u],v;i;i=edge[i].nxt)
		{
			v=edge[i].v;
			if(v==node[u].son||v==node[u].fa)
				continue;
			dfs2(v,v);
		}
	}
	node[u].t=bound;
}

void build(Tree &root,int l,int r)
{
	root=++now_node;
	root->l=l,root->r=r,root->mid=l+r>>1,root->len=r-l+1;
	if(l==r)
		return;
	build(root->lson,l,root->mid);
	build(root->rson,root->mid+1,r);
}

inline void pushdown(Tree root)
{
	if(root->lazy)
	{
		root->lson->lazy+=root->lazy;
		root->rson->lazy+=root->lazy;
		root->lson->num+=root->lson->len*root->lazy;
		root->rson->num+=root->rson->len*root->lazy;
		root->lazy=0;
	}
}

void update(Tree root,int l,int r)
{
	if(root->l==l&&r==root->r)
	{
		root->num+=root->len;
		root->lazy+=1;
		return;
	}
	pushdown(root);
	if(r<=root->mid)
		update(root->lson,l,r);
	else if(l>root->mid)
		update(root->rson,l,r);
	else
	{
		update(root->lson,l,root->mid);
		update(root->rson,root->mid+1,r);
	}
	root->num=root->lson->num+root->rson->num;
}

int query(Tree root,int l,int r)
{
	if(root->l==l&&root->r==r)
		return root->num;
	pushdown(root);
	if(r<=root->mid)
		return query(root->lson,l,r);
	else if(l>root->mid)
		return query(root->rson,l,r);
	else
		return query(root->lson,l,root->mid)+query(root->rson,root->mid+1,r);
}

inline void Modify(int x,int y)
{
	int fx=node[x].top,fy=node[y].top;
	while(fx!=fy)
	{
		if(node[fx].dep>node[fy].dep)
		{
			update(Root,node[fx].s,node[x].s);
			x=node[fx].fa;
			fx=node[x].top;
		}
		else
		{
			update(Root,node[fy].s,node[y].s);
			y=node[fy].fa;
			fy=node[y].top;
		}
	}
	if(x!=y)
	{
		if(node[x].dep>node[y].dep)
			update(Root,node[y].s+1,node[x].s);
		else
			update(Root,node[x].s+1,node[y].s);
	}
}

inline int Query(int x,int y)
{
	int fx=node[x].top,fy=node[y].top;
	int ans=0;
	while(fx!=fy)
	{
		if(node[fx].dep>node[fy].dep)
		{
			ans+=query(Root,node[fx].s,node[x].s);
			x=node[fx].fa;
			fx=node[x].top;
		}
		else
		{
			ans+=query(Root,node[fy].s,node[y].s);
			y=node[fy].fa;
			fy=node[y].top;
		}
	}
	if(x!=y)
	{
		if(node[x].dep>node[y].dep)
			return ans+query(Root,node[y].s+1,node[x].s);
		else
			return ans+query(Root,node[x].s+1,node[y].s);
	}
	return ans;
}

int opt,u,v;
int main()
{
	n=read(),m=read();
	for(int i=1;i<n;++i)
	{
		u=read(),v=read();
		add_edge(u,v);
		add_edge(v,u);
	}
	dfs1(1);
	dfs2(1,1);
	build(Root,1,n);
	for(int i=1;i<=m;++i)
	{
		opt=read(),u=read(),v=read();
		if(opt==1)
			Modify(u,v);
		else
			printf("%d\n",Query(u,v));
	}
	return 0;
}
```

---

## 作者：Log_x (赞：3)

明显的一道**树链剖分**

首先，题目强调的加权**是边而不是点**，所以我们必须将为边加权转化成为点加权。

对于每条边，我们将其深度更大的端点加权，则区间 [l, r] 的加权（或询问）即为去掉深度最小的点，给其余点加权（或询问）。

这么一听处理起来似乎很麻烦，但我们可以思考下树剖查询的过程：

1）最后一次树剖查询时，当前两点 x,y 必定在同一重链上（y 的深度小于 x）；

2）根据处理前的 dfs 序，我们是优先遍历重儿子，那么重儿子在线段树中的编号一定紧邻其父节点（即为其父节点编号 + 1），则我们要忽略深度最小的那个点 y ，即为处理区间 [ y 在线段树中的编号 + 1， x 在线段树中的编号]（另外还要注意的是，y = x 时在线段树内执行会出错，我们要特判这种情况） 。

代码楼下已经有了，这里献丑再发一波，也算是较为符合自己的分析：










 







```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#define sL (s << 1)
#define sR (s << 1 | 1) 
using namespace std;
const int Maxn = 0x3f3f3f3f;
const int N = 1e5 + 5;
int top[N], idx[N], pos[N], sze[N], son[N], fa[N], vis[N], dep[N], T;
int lst[N], to[N << 1], nxt[N << 1], sum[N << 2], val[N << 2], n, m, E;
template <class T> inline void Swap(T &a, T &b) {a ^= b; b ^= a; a ^= b;}
inline int get()
{
    char ch; bool f = false; int res = 0;
    while (((ch = getchar()) < '0' || ch > '9') && ch != '-');
    if (ch == '-') f = true;
     else res = ch - '0';
    while ((ch = getchar()) >='0' && ch <= '9')
        res = (res << 3) + (res << 1) + ch - '0';
    return f? ~res + 1 : res;
}
inline void put(int x)
{
    if (x < 0)
      x = ~x + 1, putchar('-');
    if (x > 9) put(x / 10);
    putchar(x % 10 + 48);
}
inline void add(const int x, const int y)
{
    nxt[++E] = lst[x]; lst[x] = E; to[E] = y;
    nxt[++E] = lst[y]; lst[y] = E; to[E] = x; 
}
inline void dfs1(const int x, const int ls)
{
    sze[x] = 1; int y;
    fa[x] = ls; dep[x] = dep[ls] + 1;
    for (int i = lst[x]; i, y = to[i]; i = nxt[i])
    {
        if (y == ls) continue;
        dfs1(y, x);
        sze[x] += sze[y];
        if (sze[y] > sze[son[x]]) son[x] = y;
    }
}
inline void dfs2(const int x)
{
    if (son[x])
    {
        pos[son[x]] = ++T;
        top[son[x]] = top[x];
        idx[T] = son[x];
        dfs2(son[x]);
    }
    int y;
    for (int i = lst[x]; i, y = to[i]; i = nxt[i])
    if (!top[y])
    {
        pos[y] = ++T;
        idx[T] = y;
        top[y] = y;
        dfs2(y);
    }
}
inline void Push(const int s)
{
    sum[s] = sum[sL] + sum[sR]; 
}
inline void Add(const int s, const int k, const int z)
{
    val[s] += z;
    sum[s] += (k * z);
}
inline void Down(const int s, const int l, const int r, const int mi)
{
    if (!val[s]) return;
    Add(sL, mi - l + 1, val[s]);
    Add(sR, r - mi, val[s]);
    val[s] = 0;
}
inline void Und(const int s, const int l, const int r, const int x, const int y)
{
    if (l == x && r == y) return Add(s, r - l + 1, 1);
    int mid = l + r >> 1;
    Down(s, l, r, mid);
    if (y <= mid) Und(sL, l, mid, x, y);
    else if (x > mid) Und(sR, mid + 1, r, x, y);
    else 
    {
        Und(sL, l, mid, x, mid);
        Und(sR, mid + 1, r, mid + 1, y);
    }
    Push(s);
}
inline void PaUnd(const int u, const int v)
{
    int x = u, y = v, res = 0;
    while (top[x] != top[y])
    {
        if (dep[top[x]] < dep[top[y]]) Swap(x, y);
        Und(1, 1, T, pos[top[x]], pos[x]);
        x = fa[top[x]];
    }
    if (y == x) return ;
    if (dep[x] < dep[y]) Swap(x, y);
    Und(1, 1, T, pos[y] + 1, pos[x]);
}
inline int Que(const int s, const int l, const int r, const int x, const int y)
{
    if (l == x && r == y) return sum[s];
    int mid = l + r >> 1;
    Down(s, l, r, mid);
    if (y <= mid) return Que(sL, l, mid, x, y);
    else if (x > mid) return Que(sR, mid + 1, r, x, y);
    else return Que(sL, l, mid, x, mid) +
                Que(sR, mid + 1, r, mid + 1, y);
}
inline int PaQue(const int u, const int v)
{
    int x = u, y = v, res = 0;
    while (top[x] != top[y])
    {
        if (dep[top[x]] < dep[top[y]]) Swap(x, y);
        res += Que(1, 1, T, pos[top[x]], pos[x]);
        x = fa[top[x]];
    }
    if (x == y) return res;
    if (dep[x] < dep[y]) Swap(x, y);
    return res + Que(1, 1, T, pos[y] + 1, pos[x]);
}
inline void Init()
{
    dfs1(1, 0);
    idx[1] = pos[1] = top[1] = T = 1;
    dfs2(1);
} 
int main()
{
    n = get(); m = get(); char tp; int x, y;
    while (--n) add(get(), get());
    Init(); 
    while (m--)
    {
        while ((tp = getchar()) != 'P' && tp != 'Q');
        x = get(); y = get();
        if (tp == 'P') PaUnd(x, y);
         else put(PaQue(x, y)), putchar('\n');
    } 
    return 0;
}

```

---

## 作者：Treaker (赞：2)

$$\color{cornflowerblue}{\mathcal{Treaker}}$$
# 树链剖分
这不就是个**题嘛。

直接树剖切了。

我们把边权转化为点权。

对于树剖我们维护一下区间和 和 标记即可。

指针树剖题解在此。。。

完整代码如下：
```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;
const int N = 1e5+5;
inline int read()
{
	int x = 0 , f = 1;	char ch = getchar();
	while(ch < '0' || ch > '9')	{if(ch == '-')	f = -1; ch = getchar();}
	while(ch >= '0' && ch <= '9') {x = (x << 3) + (x << 1) + (ch ^ 48); ch = getchar();}
	return x * f;
}
int n , m , cnt;
int size[N] , top[N] , dfn[N] , hs[N] , dep[N] , fa[N];
char s[5];
struct Tree_Div
{
	struct Edge
	{
		int to; Edge *nxt;
		Edge(int to,Edge *nxt) : to(to) , nxt(nxt) {}
	}*head[N];
	inline void add(int u,int v) {head[u] = new Edge(v,head[u]);}
	#define to (i -> to)
	void get_tree(int x)
	{
		size[x] = 1;
		for(Edge *i = head[x];i;i = i -> nxt)
		{
			if(dep[to]) continue;
			dep[to] = dep[x] + 1;
			fa[to] = x;
			get_tree(to);
			size[x] += size[to];
			if(size[to] > size[hs[x]]) hs[x] = to;
		}
	}
	void dfs(int x,int topfa)
	{
		top[x] = topfa;
		dfn[x] = ++cnt;
		if(hs[x]) dfs(hs[x],topfa);
		for(Edge *i = head[x];i;i = i -> nxt)
		{
			if(to == fa[x] || to == hs[x]) continue;
			dfs(to,to);
		}
	}
	struct node
	{
		node *ls, *rs;
		int l , r , tag , sum;
		node(int l,int r) : l(l) , r(r) {ls = rs = NULL; sum = tag = 0;}
		inline int len() {return r - l + 1;}
		#define mid ((p -> l + p -> r) >> 1)
		#define len len()
		inline void up() {sum = ls -> sum + rs -> sum;}
		inline void down()
		{
			if(!tag) return;
			ls -> tag += tag; rs -> tag += tag;
			ls -> sum += tag * ls -> len; rs -> sum += tag * rs -> len;
			tag = 0;
		}
	}*root;
	void build(node *&p,int l,int r)
	{
		p = new node(l,r);
		if(l == r) return;
		build(p -> ls,l,mid); build(p -> rs,mid+1,r);
	}
	void chenge(node *p,int x,int y)
	{
		if(x <= p -> l && p -> r <= y) return (void)(p -> tag ++ , p -> sum += p -> len); p -> down();
		if(x <= mid) chenge(p -> ls,x,y);
		if(y > mid) chenge(p -> rs,x,y);
		p -> up();
	}
	inline void chenge(int x,int y)
	{
		while(top[x] != top[y])
		{
			if(dep[top[x]] < dep[top[y]]) swap(x,y);
			chenge(root,dfn[top[x]],dfn[x]);
			x = fa[top[x]];
		}
		if(dep[x] < dep[y]) swap(x,y);
		if(dfn[y] < dfn[x]) chenge(root,dfn[y]+1,dfn[x]);
	}
	int query(node *p,int x,int y)
	{
		if(x <= p -> l && p -> r <= y) return p -> sum; p -> down();
		return (x <= mid ? query(p -> ls,x,y) : 0) + (y > mid ? query(p -> rs,x,y) : 0);
	}
	inline int query(int x,int y)
	{
		int res = 0;
		while(top[x] != top[y])
		{
			if(dep[top[x]] < dep[top[y]]) swap(x,y);
			res += query(root,dfn[top[x]],dfn[x]);
			x = fa[top[x]];
		}
		if(dep[x] < dep[y]) swap(x,y);
		if(dfn[y] < dfn[x]) res += query(root,dfn[y]+1,dfn[x]);
		return res;
	}
	inline void LOL()
	{
		n = read(); m = read();
		for(int i = 1 , u , v;i < n;i ++)
		{
			u = read(); v = read();
			add(u,v); add(v,u);
		} dep[1] = 1;
		get_tree(1); dfs(1,1);
		build(root,1,n);
		for(int i = 1 , u , v;i <= m;i ++)
		{
			scanf("%s",s); u = read(); v = read();
			if(s[0] == 'P') chenge(u,v);
			else printf("%d\n",query(u,v));
		}
	}
}DNF;
int main()
{
	DNF.LOL();
	return 0;
}
```

---

## 作者：Qglin_ (赞：1)

树上边有边权，考虑到一个节点可能有多个子节点，但一定只有一个父节点，所以可以把一条边上的边权转化成为这条边连接的深度更大的点的点权，这样对路径上边权的操作就可以转化成为对路径上点权的操作。然而路径$(u,v)$的顶端节点$LCA(u,v)$的权值是不用加的。联系树链剖分原理，修改路径上点权的时候，最后是在同一条重链上进行的，此时我们把深度较大的点编号+1，就能避开对$LCA(u,v)$进行的修改。



查询一条边的边权也很好做了。找到这条边连接的深度较大的点，这个点的点权就是这条边的边权。

终于转化成了树剖模板。

贴代码：

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
#define rint register int
const int N = 300005;

inline int fd() {
    int x = 0, f = 1; char ch = getchar();
    while(!isdigit(ch)) {if(ch == '-') f = -f; ch = getchar();}
    while(isdigit(ch)) {x = x*10+ch-'0'; ch = getchar();}
    return x*f;
}

int z[N << 2], col[N << 2];
int id[N], siz[N], son[N], fa[N], top[N], dep[N];
int n, m, cnt;

int head[N], edcnt;
struct edge {int to, nxt;} ed[N << 1];
inline void ADD(int x,int y) {
    ed[++edcnt].nxt = head[x];
    head[x] = edcnt;
    ed[edcnt].to = y;
}

#define lson l, mid, rt<<1
#define rson mid + 1, r, rt<<1|1
#define root 1, n, 1

inline int _max(int a,int b) {return a < b ? b : a;}

inline void pushup(int rt) {z[rt] = z[rt << 1] + z[rt << 1 | 1];}
inline void color(int l,int r,int rt,int v) {
    z[rt] += (r - l + 1) * v;
    col[rt] += v;
}
inline void pushdown(int l,int r,int rt) {
    if (col[rt]) {
        int mid = (l + r) >> 1;
        color(lson, col[rt]);
        color(rson, col[rt]);
        col[rt] = 0;
    }
}
void build(int l,int r,int rt) {
    if(l == r) {
        z[rt] = 0;
        return;
    }
    int mid = (l+r)>>1;
    build(lson);
    build(rson);
}
int query(int l,int r,int rt,int k){
    if(l == r) {
        return z[rt];
    }
    int mid = (l+r)>>1;
    pushdown(l, r, rt);
    if(k <= mid) return query(lson,k);
    else return query(rson,k);
}
void update(int l,int r,int rt,int L,int R,int v) {
    if(L<=l && r<=R) {
        color(l, r, rt, v);
        return;
    }
    int mid = (l+r)>>1;
    pushdown(l, r, rt);
    if(L <= mid) update(lson,L,R,v);
    if(R > mid) update(rson,L,R,v);
    pushup(rt);
}

void dfs1(int x,int f,int deep) {
    dep[x] = deep;
    fa[x] = f;
    siz[x] = 1;
    int maxson = -1;
    for (rint i = head[x]; i; i = ed[i].nxt) {
        int y = ed[i].to;
        if (y == f) continue;
        dfs1(y, x, deep+1);
        siz[x] += siz[y];
        if (siz[y] > maxson) {
            maxson = siz[y];
            son[x] = y;
        }
    }
}
void dfs2(int x,int topf) {
    top[x] = topf;
    id[x] = ++cnt;
    if (!son[x]) return;
    dfs2(son[x], topf);
    for (rint i = head[x]; i; i = ed[i].nxt) {
        int y = ed[i].to;
        if (y == fa[x] || y == son[x]) continue;
        dfs2(y, y);
    }
}
inline void updRange(int x,int y,int v) {
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) swap(x, y);
        update(root, id[top[x]], id[x], v);
        x = fa[top[x]];
    }
    if (dep[x] > dep[y]) swap(x, y);
    update(root, id[x]+1, id[y], v);
}

int a[N], b[N], c[N], o, p, q;
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i < n; ++i) {
        scanf("%d %d\r\n", &o, &p);
        ADD(o, p); ADD(p, o);
    }
    dfs1(1, 0, 1);
    dfs2(1, 1);
    build(root);
    char fk;
    for (int j = 1; j <= m; ++j) {
        cin >> fk;
        scanf("%d %d", &o, &p);
        switch (fk) {
        	case 'Q' : if (dep[o] < dep[p]) swap(o, p); printf("%d\n", query(root, id[o])); break;
        	case 'P' : updRange(o, p, 1); break;
		}
    }
    return 0;
}
```



---

## 作者：Vasily (赞：1)

树链剖分维护，套上线段树的区间操作。但是有一点，这里的create\_tree可以省略（因为初始为空）

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <map>
#include <stack>
#include <queue>
#include <set>
#include <cmath>
#include <algorithm>
#include <ctime>

using namespace std ;
const int maxn = 300000 ;
inline void Read ( int &x ) {
    char c = getchar() ; bool f = 0 ; x = 0 ;
    while ( !isdigit(c) ) {
        if ( c == '-' ) f = 1 ;
        c = getchar() ;
    }
    while ( isdigit(c) ) {
        x = 10 * x + c - '0' ;
        c = getchar() ;
    } if (f) x = -x ;
}

int n, m, size[maxn], dep[maxn], fa[maxn], top[maxn], w[maxn], son[maxn], cnt ;
int e, be[maxn], nxt[maxn<<1], to[maxn<<1], tree[maxn<<2], lzy[maxn<<2], a[maxn] ;

void init() {
    memset ( fa, -1, sizeof(fa) ) ;
    memset ( son, -1, sizeof(son) ) ;
}

void add ( int x, int y ) {
    to[++e] = y ;
    nxt[e] = be[x] ;
    be[x] = e ;
}

int dfs1 ( int x, int father, int deep ) {
    fa[x] = father ;
    dep[x] = deep ;
    size[x] = 1 ;
    int i, u ;
    for ( i = be[x] ; i ; i = nxt[i] ) {
        u = to[i] ;
        if ( u == father ) continue ;
        size[x] += dfs1 ( u, x, deep+1 ) ;
        if ( son[x] == -1 || size[u] > size[son[x]] ) son[x] = u ;
    }
    return size[x] ;
}

void dfs2 ( int x, int Top ) {
    top[x] = Top ;
    w[x] = ++cnt ;
    int i, u ;
    if ( son[x] ) {
        for ( i = be[x] ; i ; i = nxt[i] ) {
            u = to[i] ;
            if ( u == son[x] ) dfs2 ( u, Top ) ;
        }
    } else return ;
    for ( i = be[x] ; i ; i = nxt[i] ) {
        u = to[i] ;
        if ( u == fa[x] || u == son[x] ) continue ;
        dfs2 ( u, u ) ;
    }
}

void push_up ( int h ) { tree[h] = tree[h<<1]+tree[h<<1|1] ; }
void push_down ( int h, int len ) {
    if ( lzy[h] ) {
        lzy[h<<1] += lzy[h] ;
        lzy[h<<1|1] += lzy[h] ;
        tree[h<<1] += ( len-(len>>1) ) * lzy[h] ;
        tree[h<<1|1] += (len>>1) * lzy[h] ;
        lzy[h] = 0 ;
    }
}

void update ( int h, int l, int r, int x, int y ) {
    if ( x <= l && r <= y ) {
        tree[h] += r-l+1 ;
        lzy[h] ++ ;
        return ; 
    }
    push_down(h,r-l+1) ;
    int mid = l+r >> 1 ;
    if ( y <= mid ) update ( h<<1, l, mid, x, y ) ;
    else if ( x > mid ) update ( h<<1|1, mid+1, r, x, y ) ;
    else {
        update ( h<<1, l, mid, x, mid ) ;
        update ( h<<1|1, mid+1, r, mid+1, y ) ;
    } push_up (h) ;
}

int query ( int h, int l, int r, int x, int y ) {
    if ( x <= l && r <= y ) return tree[h] ;
    push_down (h,r-l+1) ;
    int mid = l+r >> 1 ;
    if ( y <= mid ) return query ( h<<1, l, mid, x, y ) ;
    else if ( x > mid ) return query ( h<<1|1, mid+1, r, x, y ) ;
    else return
        query ( h<<1, l, mid, x, mid ) +
        query ( h<<1|1, mid+1, r, mid+1, y ) ;
}

char cmd[5] ;

void Update ( int u, int v ) {
    while ( top[u] != top[v] ) {
        if ( dep[top[u]] > dep[top[v]] ) swap ( u, v ) ;
        update ( 1, 2, n, w[top[v]], w[v] ) ;
        v = fa[top[v]] ;
    }
    if ( u == v ) return ;
    if ( dep[u] > dep[v] ) swap ( u, v ) ;
    update ( 1, 2, n, w[u]+1, w[v] ) ;
}

int Query ( int u, int v ) {
    int rec = 0 ;
    while ( top[u] != top[v] ) {
        if ( dep[top[u]] > dep[top[v]] ) swap ( u, v ) ;
        rec += query ( 1, 2, n, w[top[v]], w[v] ) ;
        v = fa[top[v]] ;
    }
    if ( u == v ) return rec ;
    if ( dep[u] > dep[v] ) swap ( u, v ) ;
    rec += query ( 1, 2, n, w[u]+1, w[v] ) ;
    return rec ;
}

int main() {
    int i, j, k, u, v ;
    Read(n) ; Read(m) ;
    init() ;
    for ( i = 1 ; i < n ; i ++ ) {
        Read(u) ; Read(v) ;
        add ( u, v ) ;
        add ( v, u ) ;
    }
    dfs1 ( 1, 1, 1 ) ;
    dfs2 ( 1, 1 ) ;
    while (m--) {
        scanf ( "%s", cmd ) ;
        Read(u) ; Read(v) ;
        if ( cmd[0] == 'P' ) Update ( u, v ) ;
        else printf ( "%d\n", Query ( u, v ) ) ;
    }
    return 0 ;
}
```

---

## 作者：VenusM1nT (赞：0)

树链剖分。和 `P4315 月下“毛景树”` 的做法类似，将边权转为点权，然后只要处理两种操作：区间加和区间和即可，“边权转点权”的做法可以参考我 `P4315` 的题解：[Here](https://www.luogu.org/blog/Venus/solution-p4315)，中间两段话就是了。

其他的只是树链剖分和线段树的基本操作，无脑套模板即可。

```cpp
#include<bits/stdc++.h>
#define MAXN 100005
using namespace std;
int cnt,fst[MAXN],nxt[MAXN<<1],to[MAXN<<1];
int n,Q,t[MAXN<<2],tag[MAXN<<2];
int siz[MAXN],son[MAXN],dfn[MAXN],Index,top[MAXN],dep[MAXN],faz[MAXN];
string s;
void AddEdge(int u,int v)
{
	to[++cnt]=v;
	nxt[cnt]=fst[u];
	fst[u]=cnt;
}
void Dfs1(int u)
{
	siz[u]=1;
	son[u]=0;
	for(int i=fst[u];i;i=nxt[i])
	{
		int v=to[i];
		if(v==faz[u]) continue;
		faz[v]=u;
		dep[v]=dep[u]+1;
		Dfs1(v);
		siz[u]+=siz[v];
		if(siz[son[u]]<siz[v]) son[u]=v;
	}
}
void Dfs2(int u,int rt)
{
	dfn[u]=++Index;
	top[u]=rt;
	if(son[u]) Dfs2(son[u],rt);
	for(int i=fst[u];i;i=nxt[i])
	{
		int v=to[i];
		if(v==faz[u] || v==son[u]) continue;
		Dfs2(v,v);
	}
}
void PushUp(int rt)
{
	t[rt]=t[rt<<1]+t[rt<<1|1];
}
void PushDown(int rt)
{
	tag[rt<<1]+=tag[rt];
	tag[rt<<1|1]+=tag[rt];
	t[rt<<1]+=tag[rt];
	t[rt<<1|1]+=tag[rt];
	tag[rt]=0;
}
void BuildSegmentTree(int rt,int l,int r)
{
	if(l==r)
	{
		t[rt]=0;
		return;
	}
	int mid=l+r>>1;
	BuildSegmentTree(rt<<1,l,mid);
	BuildSegmentTree(rt<<1|1,mid+1,r);
	PushUp(rt);
}
void Modify(int rt,int l,int r,int tl,int tr,int val)
{
	if(tl<=l && r<=tr)
	{
		t[rt]+=val;
		tag[rt]+=val;
		return;
	}
	PushDown(rt);
	int mid=l+r>>1;
	if(tl<=mid) Modify(rt<<1,l,mid,tl,tr,val);
	if(tr>mid) Modify(rt<<1|1,mid+1,r,tl,tr,val);
	PushUp(rt);
}
int Query(int rt,int l,int r,int tl,int tr)
{
	if(tl<=l && r<=tr) return t[rt];
	PushDown(rt);
	int mid=l+r>>1,res=0;
	if(tl<=mid) res+=Query(rt<<1,l,mid,tl,tr);
	if(tr>mid) res+=Query(rt<<1|1,mid+1,r,tl,tr);
	return res;
}
void ModifyOnTree(int u,int v,int val)
{
	while(top[u]!=top[v])
	{
		if(dep[top[u]]<dep[top[v]]) swap(u,v);
		Modify(1,1,n,dfn[top[u]],dfn[u],val);
		u=faz[top[u]];
	}
	if(dep[u]>dep[v]) swap(u,v);
	Modify(1,1,n,dfn[u]+1,dfn[v],val);
}
int QueryOnTree(int u,int v)
{
	int res=0;
	while(top[u]!=top[v])
	{
		if(dep[top[u]]<dep[top[v]]) swap(u,v);
		res=max(res,Query(1,1,n,dfn[top[u]],dfn[u]));
		u=faz[top[u]];
	}
	if(dep[u]>dep[v]) swap(u,v);
	res=max(res,Query(1,1,n,dfn[u]+1,dfn[v]));
	return res;
}
int main()
{
	scanf("%d %d",&n,&Q);
	for(int i=1;i<n;i++)
	{
		int x,y,z;
		scanf("%d %d",&x,&y);
		AddEdge(x,y);
		AddEdge(y,x);
	}
	Dfs1(1);
	Dfs2(1,1);
	BuildSegmentTree(1,1,n);
	while(Q--)
	{
		int x,y,z;
		cin>>s;
		scanf("%d %d",&x,&y);
		if(s=="P") ModifyOnTree(x,y,1);
		else if(s=="Q") printf("%d\n",QueryOnTree(x,y));
	}
	return 0;
}
```

---

## 作者：King丨帝御威 (赞：0)

首先，这道题的翻译是有问题的(起码现在是)，查询的时候应该是查询某一条路径的权值，而不是某条边(坑死我了)。

与平常树链剖分题目不同的是，这道题目维护的是边权，而不是点权，那怎么办呢？好像有点棘手诶，这是一种非常经典的题型，我们可以发现，一个点最多只有一个父亲！！！那，我们显然就可以用这个点的点权去代替它与它父亲之间的边权！！！然后这道题不就成了树链剖分水题了嘛？刚开始边权都是$0$，那我们就根据题目给的边建边权为$0$的边。

$nonono$，还有一个坑点就是在路径查询和修改的时候，两点的$LCA$的点权是不能算在其中的，因为它的点权是$LCA$与$LCA$父亲之间边的边权，注意这几个问题，那这题就真的是水题了！

具体实现看代码：

```cpp
#include<cstdio>
#include<algorithm>
#include<cctype>
#define maxn 100007
#define ls rt<<1
#define rs rt<<1|1
using namespace std;
int n,m,head[maxn],d[maxn],son[maxn],siz[maxn],id[maxn],w[maxn];
int num,cnt,sum[maxn<<2],lazy[maxn<<2],top[maxn],fa[maxn],a[maxn];
char s[3];
inline int qread() {
  char c=getchar();int num=0,f=1;
  for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
  for(;isdigit(c);c=getchar()) num=num*10+c-'0';
  return num*f;
}
struct node {
  int v,w,nxt;
}e[maxn<<1];
inline void ct(int u, int v, int w) {
  e[++num].v=v;
  e[num].w=w;
  e[num].nxt=head[u];
  head[u]=num;
}
inline void pushup(int rt) {
  sum[rt]=sum[ls]+sum[rs];
}
void build(int rt, int l, int r) {
  if(l==r) {
    sum[rt]=a[l];
    return;
  }
  int mid=(l+r)>>1;
  build(ls,l,mid);
  build(rs,mid+1,r);
  pushup(rt);
}
inline void pushdown(int rt, int len) {
  if(lazy[rt]) {
    sum[ls]+=(len-(len>>1))*lazy[rt];
    sum[rs]+=(len>>1)*lazy[rt];
    lazy[ls]+=lazy[rt],lazy[rs]+=lazy[rt];
    lazy[rt]=0;
  }
}
void modify(int rt, int l, int r, int L, int R, int val) {
  if(L>r||R<l) return;
  if(L<=l&&r<=R) {
    sum[rt]+=(r-l+1)*val;
    lazy[rt]+=val;
    return;
  }
  pushdown(rt,r-l+1);
  int mid=(l+r)>>1;
  modify(ls,l,mid,L,R,val),modify(rs,mid+1,r,L,R,val);
  pushup(rt);
}
int csum(int rt, int l, int r, int L, int R) {
  if(L>r||R<l) return 0;
  if(L<=l&&r<=R) return sum[rt];
  pushdown(rt,r-l+1);
  int mid=(l+r)>>1;
  return csum(ls,l,mid,L,R)+csum(rs,mid+1,r,L,R);
}
void dfs1(int u) {
  siz[u]=1;
  for(int i=head[u];i;i=e[i].nxt) {
    int v=e[i].v;
    if(v!=fa[u]) {
      d[v]=d[u]+1;
      fa[v]=u;
      w[u]=e[i].w;                 //化边权为点权。
      dfs1(v);
      siz[u]+=siz[v];
      if(siz[v]>siz[son[u]]) son[u]=v;
    }
  }
}
void dfs2(int u, int t) {
  id[u]=++cnt;
  top[u]=t;
  a[cnt]=w[u];
  if(son[u]) dfs2(son[u],t);
  for(int i=head[u];i;i=e[i].nxt) {
    int v=e[i].v;
    if(v!=fa[u]&&v!=son[u]) dfs2(v,v);
  }
}
void cal(int x, int y) {
  int fx=top[x],fy=top[y];
  while(fx!=fy) {
    if(d[fx]<d[fy]) swap(x,y),swap(fx,fy);
    modify(1,1,cnt,id[fx],id[x],1);
    x=fa[fx],fx=top[x];
  }
  if(id[x]>id[y]) swap(x,y);
  modify(1,1,cnt,id[x]+1,id[y],1);     //LCA的点权不能算在其中！！
}
int query(int x, int y) {
  int fx=top[x],fy=top[y],ans=0;
  while(fx!=fy) {
    if(d[fx]<d[fy]) swap(x,y),swap(fx,fy);
    ans+=csum(1,1,cnt,id[fx],id[x]);
    x=fa[fx],fx=top[x];
  }
  if(id[x]>id[y]) swap(x,y);
  ans+=csum(1,1,cnt,id[x]+1,id[y]);    //同上。
  return ans;
}
int main() {
  n=qread(),m=qread();
  for(int i=1,u,v;i<n;++i) {
    u=qread(),v=qread();
    ct(u,v,0);ct(v,u,0);
  }
  dfs1(1);dfs2(1,1);build(1,1,n);
  for(int i=1,u,v;i<=m;++i) {
    scanf("%s",s);
    u=qread(),v=qread();
    if(s[0]=='P') cal(u,v);
    else printf("%d\n",query(u,v));
  }
  return 0;
}
```

希望这篇题解能让大家对这种题型更加熟悉！

---

