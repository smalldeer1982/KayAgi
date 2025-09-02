# Dominant Indices

## 题目描述

You are given a rooted undirected tree consisting of $ n $ vertices. Vertex $ 1 $ is the root.

Let's denote a depth array of vertex $ x $ as an infinite sequence $ [d_{x, 0}, d_{x, 1}, d_{x, 2}, \dots] $ , where $ d_{x, i} $ is the number of vertices $ y $ such that both conditions hold:

- $ x $ is an ancestor of $ y $ ;
- the simple path from $ x $ to $ y $ traverses exactly $ i $ edges.

The dominant index of a depth array of vertex $ x $ (or, shortly, the dominant index of vertex $ x $ ) is an index $ j $ such that:

- for every $ k < j $ , $ d_{x, k} < d_{x, j} $ ;
- for every $ k > j $ , $ d_{x, k} \le d_{x, j} $ .

For every vertex in the tree calculate its dominant index.

## 样例 #1

### 输入

```
4
1 2
2 3
3 4
```

### 输出

```
0
0
0
0
```

## 样例 #2

### 输入

```
4
1 2
1 3
1 4
```

### 输出

```
1
0
0
0
```

## 样例 #3

### 输入

```
4
1 2
2 3
2 4
```

### 输出

```
2
1
0
0
```

# 题解

## 作者：Thomasguo666 (赞：97)

更好的阅读体验：https://thomasguo666.github.io/post/solution-cf1009f/

---

首先这个题可以想到是一个DP。状态设计：$f_{u,dep}$ 表示 u 的子树中与 u 距离为 dep 的点的个数。
转移方程如下: 
 $$
f_{u,dep}=\sum_{v \in son_u} f_{v,dep-1}
$$

然而如果直接暴力转移的话显然会 T 飞或者 M 飞，，所以我们需要一点点的优化。

---

引入一个概念：**长链剖分**

我们可以找到一个结点 u 的子树中，到这个节点距离最大的叶子节点。将两点之间的距离计为 $dep_u$ 。那么对于一个节点 u，我们把他的所有孩子中 dep 值最大的称作这个节点的 **长儿子**。

从一个节点开始，每次走向他的长儿子，一直走到叶子节点为止，经过的路径就是一条**长链**。显然，一整棵树会被分成若干条长链，并且每个节点都在恰好一条长链上，每条边要么在长链上，要么把一条长链的顶端连向另一条长链。

代码如下：
```cpp

int dep[1000005],son[1000005];
void dfs1(int u,int fa)
{
    for (int e=head[u];e;e=nex[e]) // 链式前向星
    {
        int v=tail[e];
        if (v==fa) continue;
        dfs1(v,u);
        if (dep[v]>dep[son[u]]) son[u]=v; // 寻找长儿子
    }
    dep[u]=dep[son[u]]+1; // 统计 u 的 dep
}
```

---

那么这个东西和 DP 又有什么关系呢？

我们可以采用一个优化策略：对于一个节点 u，我们先对它的长儿子做DP，但这里可以使用一些技巧，让长儿子把 dp 出来的东西直接存到 $f_u$ 里面去（当然观察 dp 式可以发现这边需要错一位），然后再把其他儿子 dp 出来的东西与 $f_u$ 暴力合并。

这里详细地说一说到底怎么样实现这个优化（貌似其他题解写得都很简略啊……窝看了半天都看不懂，可能是我太菜了）

首先，我们抛弃传统 DP 的预先为每个节点都申请一片空间的写法（空间开销过大），而是在 DP 的过程中，动态的为节点申请（DP数组的）内存，所以这里我们要采用指针的写法。

然后，**我们只对每一个长链的顶端节点申请内存**，而对于一条长链上的所有节点，我们让他们可以公用一片空间。具体地说，假设对节点 u 申请了内存之后，设 v 是 u 的长儿子，我们就把 $f_u$ 数组的起点（的指针）加一当作 $f_v$ 数组的起点（的指针，下同），以此类推。这也就是上面说的“让长儿子把 dp 出来的东西直接存到 $f_u$ 里面去”。当然，申请的内存要能装下一条长链。

那么显而易见的，使用了这个优化之后可以把时间和空间都减到 $O(n)$ 级别的，因为每个节点都只会在它所在的长链顶端被统计（或者说是被暴力合并）一次。

这部分优化的代码长成这个样子：
```cpp
void dfs2(int u,int fa)
{
    f[u][0]=1; // 先算上自己
    if (son[u])
    {
        f[son[u]]=f[u]+1; // 共享内存，这样一步之后，f[son[u]][dep]会被自动保存到f[u][dep-1]
        dfs2(son[u],u);
    }
    for (int e=head[u];e;e=nex[e])
    {
        int v=tail[e];
        if (v==son[u] || v==fa) continue;
        f[v]=now;now+=dep[v]; // 为 v 节点申请内存，大小等于以 v 为顶端的长链的长度
        dfs2(v,u);
        for (int i=1;i<=dep[v];i++)
        {
            f[u][i]+=f[v][i-1]; //暴力合并
        }
    }
}
```

当然，在 dp 开始前要先为以树根为顶端的长链申请内存。

然而，光有 dp 数组还没用，我们还要统计答案。

我们可以先令 u 节点的答案为它的长儿子的答案加一。然后在暴力合并的过程当中每次检查当前的 dep 是否优于 $ans_u$ （$ans_u$ 就是题目要求的东西），如果是的话那就更新答案。

最后如果发现 $f_{u,ans_u}=1$，即 u 的子树为一条链，无论在哪个深度下都只有一个点的话，那么就把当前节点的答案 $ans_u$ 设为 0 ，这个应该很好理解。

最后放上完整的代码：
```cpp
#include <bits/stdc++.h>
#define debug printf("Running %s on line %d...\n",__FUNCTION__,__LINE__)
#define in inline
#define re register
using namespace std;
typedef long long ll;
typedef double db;
in int read()
{
    int ans=0,f=1;char c=getchar();
    for (;!isdigit(c);c=getchar()) if (c=='-') f=-1;
    for (;isdigit(c);c=getchar()) ans=(ans<<3)+(ans<<1)+(c^48);
    return ans*f;
}
in int cmin(int &a,int b) {return a=min(a,b);}
in int cmax(int &a,int b) {return a=max(a,b);}
int n;
int buf[1000005];
int *f[1000005],*g[1000005],*now=buf;
int nex[2000005],head[1000005],tail[2000005],tot;
int ans[1000005];
void addedge(int u,int v)
{
    nex[++tot]=head[u];
    head[u]=tot;
    tail[tot]=v;
}
int dep[1000005],son[1000005];
void dfs1(int u,int fa) // 长链剖分
{
    for (int e=head[u];e;e=nex[e])
    {
        int v=tail[e];
        if (v==fa) continue;
        dfs1(v,u);
        if (dep[v]>dep[son[u]]) son[u]=v;
    }
    dep[u]=dep[son[u]]+1;
}
void dfs2(int u,int fa) //做dp
{
    f[u][0]=1;
    if (son[u])
    {
        f[son[u]]=f[u]+1; // 共享内存
        dfs2(son[u],u);
        ans[u]=ans[son[u]]+1; //从长孩子节点继承答案
    }
    for (int e=head[u];e;e=nex[e])
    {
        int v=tail[e];
        if (v==son[u] || v==fa) continue;
        f[v]=now;now+=dep[v]; // 分配内存
        dfs2(v,u);
        for (int i=1;i<=dep[v];i++)
        {
            f[u][i]+=f[v][i-1]; //暴力合并
            if (f[u][i]>f[u][ans[u]] || (f[u][i]==f[u][ans[u]] && i<ans[u])) ans[u]=i; //更新答案
        }
    }
    if (f[u][ans[u]]==1) ans[u]=0;
}
int main()
{
    n=read();
    for (int i=1;i<n;i++)
    {
        int u=read(),v=read();
        addedge(u,v);
        addedge(v,u);
    }
    dfs1(1,0); // 长链剖分
    f[1]=now;now+=dep[1]; // 为根节点的答案分配内存
    dfs2(1,0);
    for (int i=1;i<=n;i++) cout<<ans[i]<<endl;
    return 0;
}

```

完结撒花\*★,°\*:.☆(￣▽￣)/$:\*.°★\* 。！

---

## 作者：StudyingFather (赞：48)

一道非常不错的长链剖分练手题。

首先是常规的 DP：设 $f_{i,j}$ 表示点 $i$ 的 $j$ 级子节点的数量。

转移方程很显然（其中 $v$ 是 $i$ 的子节点）：

$$
f_{i,j}=\sum f_{v,j-1}
$$

边界是 $f_{i,0}=1$。

这样做的时间复杂度是 $O(n^2)$ 的，需要优化。

这时候长链剖分就登场了（实际上是树上启发式合并的思路）。

我们对于一个节点，先遍历它的重儿子，将重儿子的结果合并（说是合并，其实直接继承了重儿子的结果，并添加了当前点的信息）到当前点上。

接下来我们遍历这个点的其他轻儿子，将这些轻儿子的结果并到当前节点上。

每条重链都只合并了一次，故时间复杂度为 $O(n)$。

---

题解区似乎没有非指针版的实现？其实用 vector 也是可以搞的。

思路仍然是用 vector 存下每个点的信息。不过有几个特殊之处：

1. 按深度递增的顺序存储的话，因为合并重儿子信息时要在开头插入元素，效率低下。所以考虑按深度递减的顺序存储信息。
2. 合并重儿子信息的时候，直接用 swap 交换而不是复制，在时间和空间上都更优（swap 交换 vector 的时间复杂度是 $O(1)$ 的）。

```cpp
// Problem : F. Dominant Indices
// Contest : Educational Codeforces Round 47 (Rated for Div. 2)
// URL : https://codeforces.com/contest/1009/problem/F
// Author : StudyingFather
// Site : https://studyingfather.com
// Memory Limit : 512 MB
// Time Limit : 4500 ms
// Powered by CP Editor (https://github.com/cpeditor/cp-editor)

#include <cstdio>
#include <vector>
using namespace std;
vector<int> e[1000005],f[1000005];
int fa[1000005],len[1000005],son[1000005];
int ans[1000005];
void dfs1(int u,int f)
{
 fa[u]=f;
 for(auto v:e[u])
  if(v!=f)
  {
   dfs1(v,u);
   if(len[v]>=len[son[u]])
    son[u]=v,len[u]=len[v]+1;
  }
}
void dfs2(int u)
{
 if(son[u])
 {
  dfs2(son[u]);
  swap(f[u],f[son[u]]);//直接交换，降低时间空间开销
  f[u].push_back(1);//尾部插入深度为零的结果
  ans[u]=ans[son[u]];
  if(f[u][ans[u]]==1)ans[u]=len[u];
  for(auto v:e[u])
  {
   if(v==fa[u]||v==son[u])continue;
   dfs2(v);
   for(int i=len[v];i>=0;i--)
   {
    int tmp=i+len[u]-len[v]-1;
    f[u][tmp]+=f[v][i];
    if(f[u][tmp]>f[u][ans[u]]||(f[u][tmp]==f[u][ans[u]]&&tmp>ans[u]))
     ans[u]=tmp;//这里存储的是最优解在数组对应的位置，结果需要倒过来
   }
  }
 }
 else
 {
  f[u].push_back(1);
  ans[u]=0;
 }
}
int main()
{
 int n;
 scanf("%d",&n);
 for(int i=1;i<n;i++)
 {
  int u,v;
  scanf("%d%d",&u,&v);
  e[u].push_back(v);
  e[v].push_back(u);
 }
 dfs1(1,0);
 dfs2(1);
 for(int i=1;i<=n;i++)
  printf("%d\n",len[i]-ans[i]);
 return 0;
}
```

---

## 作者：Rachel_in (赞：15)

除了长链剖分，此题还可以线段树合并。


对于每个非叶节点，将它与子树合并。权值线段树中的下标为deep，这样就可以计算出每个节点里的数量最大值，优先靠在左边。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int res=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-f;ch=getchar();}	
	while(ch>='0'&&ch<='9'){res=(res<<3)+(res<<1)+ch-'0';ch=getchar();}
	return res*f;
}
void write(int x){
	if(x<0) putchar('-'),x=-x;
	if(x>9) write(x/10);
	putchar(x%10|'0');
}
const int N=2000005;
const int M=21000005;
int n,fir[N],nxt[N<<1],go[N<<1],dep[N],cnt,CNT;
int root[N],lc[M],rc[M],tr[M],id[M],ans[N];
inline void Add(int u,int v){
	nxt[++cnt]=fir[u];
	fir[u]=cnt;
	go[cnt]=v;
}
void init(int u,int fa){
	dep[u]=dep[fa]+1;
	for(int e=fir[u];e;e=nxt[e]){
		int v=go[e];
		if(v==fa) continue;	
		init(v,u);
	}
}
void insert(int &now,int l,int r,int x,int val){
	if(!now) now=++CNT;
	if(l==r){
		tr[now]+=val;
		id[now]=x;
		return ;
	}
	int mid=(l+r)>>1;
	if(x<=mid) insert(lc[now],l,mid,x,val);
	else insert(rc[now],mid+1,r,x,val);
	if(tr[lc[now]]>=tr[rc[now]]){
		tr[now]=tr[lc[now]];	
		id[now]=id[lc[now]];
	}else{
		tr[now]=tr[rc[now]];
		id[now]=id[rc[now]];
	}
}
int merge(int x,int y,int l,int r){
	if(!x) return y;
	if(!y) return x;
	if(l==r){
		tr[x]+=tr[y];
		id[x]=l;
		return x;
	}
	int mid=(l+r)>>1;
	lc[x]=merge(lc[x],lc[y],l,mid);
	rc[x]=merge(rc[x],rc[y],mid+1,r);
	if(tr[lc[x]]>=tr[rc[x]]){
		tr[x]=tr[lc[x]];
		id[x]=id[lc[x]];
	}else{
		tr[x]=tr[rc[x]];
		id[x]=id[rc[x]];	
	}	
	return x;
}
void dfs(int u,int fa){
	insert(root[u],1,n,dep[u],1);
	for(int e=fir[u];e;e=nxt[e]){
		int v=go[e];
		if(v==fa) continue;
		dfs(v,u);	
		root[u]=merge(root[u],root[v],1,n);
	}
	ans[u]=id[root[u]]-dep[u];
}
int main(){
	n=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		Add(u,v);Add(v,u);
	}
	init(1,0);
	dfs(1,0);
	for(int i=1;i<=n;i++){
		write(ans[i]);putchar('\n');
	}
	return 0;
}
```


---

## 作者：FutaRimeWoawaSete (赞：14)

以为十二篇题解里面怎么也得有启发式合并老哥，没想到真的没有。    

按理来说这道题不是归于启发式合并的经典例题里面吗？    

首先启发式合并有点小卡，如果您追求于更快的做法不妨使用树上倍增。    
其次就讲解一些此题如何树上启发式合并，很明显这道题符合我们树上启发式合并的一些基本特征，即：    

```
1.只具备查询操作；    
2.只和子树有关；
```   

所以考虑到了 $DSU$  ，我们直接先扫一遍把重儿子们都找出来，然后就是常规套路了，对于一棵子树递归过程中最后查询重儿子，此时我们获取了重儿子的情况并且要计算当前情况，然后我们就少查询了一次重儿子的情况。    

时间复杂度 $O(nlogn)$ 根据启发式合并而来这里不细讲。    

唯一注意的就是要考虑怎么初始化 $0$ 的情况，这里我直接没管直接在 $add$ 让它更新了一次，其他就没什么好说的了。     

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<map>
using namespace std;
const int Len = 1e6 + 5;
int Mx,Dis,n,m,Cnt[Len],head[Len],cnt,Print[Len],dep[Len],siz[Len],son[Len],Son;
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
void dfs1(int x,int f)
{
	dep[x] = dep[f] + 1;
	siz[x] = 1;
	int maxson = -1;
	for(int e = head[x] ; e ; e = edge[e].next)
	{
		int to = edge[e].to;
		if(to == f) continue;
		dfs1(to , x);
		siz[x] += siz[to];
		if(siz[to] > maxson) maxson = siz[to] , son[x] = to; 
	}
}
void add(int x,int f,int val,int now)
{
	Cnt[dep[x]] += val;
	if(Cnt[dep[x]] > Mx || (Cnt[dep[x]] == Mx && dep[x] -  dep[now] < Dis - dep[now])) Mx = Cnt[dep[x]] , Dis = dep[x];
	for(int e = head[x] ; e ; e = edge[e].next)
	{
		int to = edge[e].to;
		if(to == f || to == Son) continue;
		add(to , x , val , now);
	} 
}
void dfs2(int x,int f,int opt)
{
	for(int e = head[x] ; e ; e = edge[e].next)
	{
		int to = edge[e].to;
		if(to == f || to == son[x]) continue;
		dfs2(to , x , 0);
	}
	if(son[x]) dfs2(son[x] , x , 1) , Son = son[x];
	add(x , f , 1 , x) , Son = 0;
	Print[x] = Dis;
	if(!opt) add(x , f , -1 , x) , Mx = Dis = 0;
}
int main()
{
	scanf("%d",&n);
	for(int i = 1 ; i < n ; i ++)
	{
		int x,y;scanf("%d %d",&x,&y);
		add(x , y) , add(y , x);
	}
	dfs1(1 , 0);
	dfs2(1 , 0 , 1);
	for(int i = 1 ; i <= n ; i ++) printf("%d\n",Print[i] - dep[i]);
	return 0;
}
```

---

## 作者：TheLostWeak (赞：9)

[在博客查看](https://www.cnblogs.com/chenxiaoran666/p/CF1009F.html)

**大致题意：** 设$d(x,y)$表示$x$子树内到$x$距离为$y$的点的个数，对于每个$x$，求满足$d(x,y)$最大的最小的$y$。

### 暴力$DP$

首先让我们来思考如何暴力$DP$。

这应该还是比较简单的吧。

直接设$f_{x,i}$表示**在$x$的子树内，到$x$的距离为$i$的点的个数**。

则不难推出转移方程：

$$f_{x,0}=1,f_{x,i}=\sum f_{son_x,i-1}$$

但这样显然跑不过，要优化。

### 长链剖分

这是一道[**长链剖分**](https://www.cnblogs.com/chenxiaoran666/p/LongChainDissection.html)优化$DP$的典型例题。

设$len_x$为$x$到叶节点的最长距离，则不难发现转移方程第二维$i$显然不可能超过$len_x$。

考虑使用**指针**（虽然我很不喜欢指针，但貌似这里必须用$2333$），对于每条长链顶点给它开一个长度为$len_x$的内存供它存储。

然后，对于每条长链的第$i$个元素$t_i$，我们就用第$i$个位置作为$f_{t_i,0}$。

这样的好处就在于，对于一条长链，我们是可以直接让父节点从子节点那里继承答案的！

是不是非常神奇？

而对于非长儿子，我们暴力合并两条链。

由于每条链只会被合并一次，因此复杂度就达到了无比优秀的$O(n)$！

是不是很神奇？

### 代码

```cpp
#include<bits/stdc++.h>
#define Tp template<typename Ty>
#define Ts template<typename Ty,typename... Ar>
#define Reg register
#define RI Reg int
#define Con const
#define CI Con int&
#define I inline
#define W while
#define N 1000000
#define add(x,y) (e[++ee].nxt=lnk[x],e[lnk[x]=ee].to=y)
using namespace std;
int n,ee,lnk[N+5];struct edge {int to,nxt;}e[N<<1];
class FastIO
{
	private:
		#define FS 100000
		#define tc() (A==B&&(B=(A=FI)+fread(FI,1,FS,stdin),A==B)?EOF:*A++)
		#define pc(c) (C^FS?FO[C++]=c:(fwrite(FO,1,C,stdout),FO[(C=0)++]=c))
		#define tn (x<<3)+(x<<1)
		#define D isdigit(c=tc())
		int T,C;char c,*A,*B,FI[FS],FO[FS],S[FS];
	public:
		I FastIO() {A=B=FI;}
		Tp I void read(Ty& x) {x=0;W(!D);W(x=tn+(c&15),D);}
		Ts I void read(Ty& x,Ar&... y) {read(x),read(y...);}
		Tp I void write(Ty x) {W(S[++T]=x%10+48,x/=10);W(T) pc(S[T--]);}
		Tp I void writeln(Con Ty& x) {write(x),pc('\n');}
		I void clear() {fwrite(FO,1,C,stdout),C=0;}
		#undef D
}F;
class LongChainDissection//长链剖分优化DP
{
	private:
		#define Assign(x) (f[x]=p,p+=len[x])//分配内存
		#define F5(x,v) ((f[x][ans[x]]<f[x][v]||(f[x][ans[x]]==f[x][v]&&ans[x]>v))&&(ans[x]=v))//更新答案
		int son[N+5],len[N+5],ans[N+5],*p,*f[N+5],_f[N+5];
		I void dfs(CI x,CI lst)//DFS预处理长儿子与len数组
		{
			for(RI i=lnk[x];i;i=e[i].nxt) e[i].to^lst&&
				(dfs(e[i].to,x),len[e[i].to]>len[son[x]]&&(son[x]=e[i].to));
			len[x]=len[son[x]]+1;
		}
		I void DP(CI x,CI lst)//DP
		{
			RI i,j;son[x]&&(f[son[x]]=f[x]+1,DP(son[x],x),ans[x]=ans[son[x]]+1);//优先处理长儿子，并继承答案
			for(i=lnk[x];i;i=e[i].nxt) if(e[i].to^lst&&e[i].to^son[x])//枚举非长儿子
				for(Assign(e[i].to),DP(e[i].to,x),j=1;j<=len[e[i].to];++j)//暴力合并
					f[x][j]+=f[e[i].to][j-1],F5(x,j);f[x][0]=1,F5(x,0);
		}
	public:
		I LongChainDissection() {p=_f;}I void Init() {dfs(1,0);}//初始化
		I void Solve() {Assign(1),DP(1,0);for(RI i=1;i<=n;++i) F.writeln(ans[i]);}//DP并输出答案
}D; 
int main()
{
	RI i,x,y;for(F.read(n),i=1;i^n;++i) F.read(x,y),add(x,y),add(y,x);//读入+建边
	return D.Init(),D.Solve(),F.clear(),0;//求解
}
```

---

## 作者：Farkas_W (赞：7)

$$\text{CF1009F Dominant Indices}$$

$\quad$题目链接：[CF1009F Dominant Indices](https://www.luogu.com.cn/problem/CF1009F)(洛谷的链接)

$\quad$没有修改操作，询问子树，这就是一道 Dsu 板子题，这个算法又叫树上启发式合并(下面会细讲)。

$\quad$关于此题，用 $cnt_i$ 数组来表示深度为 $i$ 的结点数量，另外要注意要在修改的时候顺便记录 $cnt$ 最大的深度，不然会T飞(~~亲身经历~~)。

$\quad$下面就简单讲讲树上启发式合并 (Dsu on Tree)算法，如果有不懂的可以提出来。

$$\text{关于树上启发式合并(Dsu)前置知识}$$

$\quad$学这个之前需要对树上操作、 $dfs$ 序和轻重链剖分等知识有一定了解，最好已经掌握了树链剖分。

$$\text{算法思想}$$

$\quad$树上启发式合并 (Dsu on Tree)，是一个在 $O(n\log n)$ 时间内解决许多树上问题的有力算法，对于某些树上离线问题可以速度大于等于大部分算法且更易于理解和实现。

$\quad$先想一下暴力算法，对于每一次询问都遍历整棵子树，然后统计答案，最后再清空 $cnt$ 数组，最坏情况是时间复杂度为 $O(n^2)$ ，对于 $10^5$ 的数据肯定是过不去的。

$\quad$现在考虑优化算法，暴力算法跑得慢的原因就是多次遍历，多次清空数组，一个显然的优化就是将询问同一个子树的询问放在一起处理，但这样还是没有处理到关键，最坏情况时间复杂度还是 $O(n^2)$ ，考虑到询问 $x$ 节点时， $x$ 的子树对答案有贡献，所以可以不用清空数组，先统计 $x$ 的子树中的答案，再统计 $x$ 的答案，这样就需要提前处理好 $dfs$ 序。

$\quad$然后我们可以考虑一个优化，遍历到最后一个子树时是不用清空的，因为它不会产生对其他节点影响了，根据贪心的思想我们当然要把节点数最多的子树（即重儿子形成的子树）放在最后，之后我们就有了一个看似比较快的算法，先遍历所有的轻儿子节点形成的子树，统计答案但是不保留数据，然后遍历重儿子，统计答案并且保留数据，最后再遍历轻儿子以及父节点，合并重儿子统计过的答案。

$\quad$其实树上启发式合并的基本思路就是这样，可以看一下代码理解。

```cpp
il int check(int x)//统计答案
{
  int num=0,ret=0;
  for(re i=1;i<=n;i++)
    {
      if(cnt[i]==num){ret+=i;}
      else if(cnt[i]>num){num=cnt[i],ret=i;}
    }
  return ret;
}
il void add(int x){cnt[col[x]]++;}//单点增加
il void del(int x){cnt[col[x]]--;}//单点减少
il void raise(int x){for(re i=seg[x];i<=seg[x]+size[x]-1;i++)add(rev[i]);}//增加x子树的贡献
il void clear(int x){for(re i=seg[x];i<=seg[x]+size[x]-1;i++)del(rev[i]);}//清空x子树的贡献
il void dfs1(int x,int fa)
{
  dep[x]=dep[fa]+1;father[x]=fa;//处理深度，父亲
  seg[x]=++seg[0];rev[seg[x]]=x;size[x]=1;//子树大小，dfs序
  for(re i=head[x],y;i,y=go[i];i=next[i])
    {
      if(y==fa)continue;dfs1(y,x);
      size[x]+=size[y];
      if(size[y]>size[son[x]])son[x]=y;//重儿子
    }
}
il void dfs2(int x,int flag)//flag表示是否为重儿子，1表示重儿子，0表示轻儿子
{
  for(re i=head[x],y;i,y=go[i];i=next[i])
    {
      if(y==son[x]||y==father[x])continue;
      dfs2(y,0);//先遍历轻儿子
    }
  if(son[x])dfs2(son[x],1);//再遍历重儿子
  for(re i=head[x],y;i,y=go[i];i=next[i])
    {
      if(y==son[x]||y==father[x])continue;
      raise(y);//更新轻儿子的贡献
    }add(x);//加上x结点本身的贡献
  ans[x]=check(x);//更新答案
  if(!flag)clear(x);//如果是轻儿子，就清空
}
```
$\quad$上面的只是模板的代码，此题的完整代码在下面，建议自己写出来，那样会更有效果。

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<map>
#include<vector>
using namespace std;
#define re register int
#define int long long
#define LL long long
#define il inline
#define next nee
#define inf 1e18
il int read()
{
  int x=0,f=1;char ch=getchar();
  while(!isdigit(ch)&&ch!='-')ch=getchar();
  if(ch=='-')f=-1,ch=getchar();
  while(isdigit(ch))x=(x<<1)+(x<<3)+ch-'0',ch=getchar();
  return x*f;
}
il void print(int x)
{
  if(x<0)putchar('-'),x=-x;
  if(x/10)print(x/10);
  putchar(x%10+'0');
}
const int N=1e6+5;
int n,ans[N],next[N<<1],go[N<<1],head[N],tot,seg[N],son[N],father[N],size[N];
int cnt[N],dep[N],rev[N],Maxdep,Max,num;
il void Add(int x,int y)
{
  next[++tot]=head[x];
  head[x]=tot;go[tot]=y;
}
il void check(int x)//更新Max和num的值
{
  if(cnt[x]>Max)Max=cnt[x],num=x;
  else if(cnt[x]==Max&&x<num)num=x;//如果有相等的情况，取深度小的
}
il void dfs1(int x,int fa)//预处理
{
  father[x]=fa;size[x]=1;seg[x]=++seg[0];dep[x]=dep[fa]+1;rev[seg[x]]=x;//处理子树大小，父亲，深度，dfs序
  if(dep[x]>Maxdep)Maxdep=dep[x];
  for(re i=head[x],y;i,y=go[i];i=next[i])
    {
      if(y==fa)continue;dfs1(y,x);
      size[x]+=size[y];
      if(size[y]>size[son[x]])son[x]=y;//记录重儿子
    }
}
il void dfs2(int x,int flag)
{
  for(re i=head[x],y;i,y=go[i];i=next[i])
    {
      if(y==father[x]||y==son[x])continue;
      dfs2(y,0);Max=num=0;//先遍历轻儿子
      for(re j=seg[y];j<=seg[y]+size[y]-1;j++)
	{int z=rev[j];cnt[dep[z]]=0;}//顺便清空cnt数组，Max和num清零
    }if(son[x])dfs2(son[x],1);//再遍历重儿子
  for(re i=head[x],y;i,y=go[i];i=next[i])
    {
      if(y==father[x]||y==son[x])continue;
      for(re j=seg[y];j<=seg[y]+size[y]-1;j++)
	{
	  int z=rev[j];cnt[dep[z]]++;//更新轻儿子的贡献
	  check(dep[z]);
	}
    }cnt[dep[x]]++;check(dep[x]);//加上x结点本身的贡献
  ans[x]=num-dep[x];//更新答案
}
signed main()
{
  n=read();
  for(re i=1,x,y;i<n;i++)x=read(),y=read(),Add(x,y),Add(y,x);
  dfs1(1,0);dfs2(1,1);
  for(re i=1;i<=n;i++)print(ans[i]),putchar('\n');
  return 0;
}
```

---

## 作者：feecle6418 (赞：6)

线段树合并。

普通的线段树合并空间是 $O(n\log n)$，容易被卡空间、其实利用垃圾回收可以做到线性。

由于在任意时刻，有用的只有深度为 $i$ 的和深度为 $i+1$ 的点的线段树，我们可以在合并完成后将不用的点重复利用，开一个栈来记录废弃的点即可。

代码如下：

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
int n,cnt,cntt,h[1000005],root[1000005],ans[1000005];
int st[4000005],top;
struct TreeNode{
	int ls,rs,maxx,maxp;
	void Clear(){
		ls=rs=maxx=maxp=0;
	}
}t[4000005];
struct Edge{
	int to,next;
}e[2000005];
struct Que{
	int k,id;
};
int NewNode(){
	if(top)return st[top--];
	return ++cntt;
}
void Add_Edge(int x,int y){
	e[++cnt].to=y;
	e[cnt].next=h[x];
	h[x]=cnt;
}
void Pushup(int p){
	int l=t[p].ls,r=t[p].rs;
	if(t[l].maxx==t[r].maxx){
		t[p].maxx=t[l].maxx,t[p].maxp=t[l].maxp;
		return ;
	}
	if(t[l].maxx>t[r].maxx){
		t[p].maxx=t[l].maxx,t[p].maxp=t[l].maxp;
	}
	else {
		t[p].maxx=t[r].maxx,t[p].maxp=t[r].maxp;
	}
}
void Update(int &p,int l,int r,int x){
	if(!p)p=NewNode();
	if(l==r){
		t[p].maxx++,t[p].maxp=l;
		return ;
	}
	int mid=(l+r)/2;
	if(x<=mid)Update(t[p].ls,l,mid,x);
	else Update(t[p].rs,mid+1,r,x);
	Pushup(p);
}
void Merge(int &p,int q,int l,int r){
	if(!p||!q){
		p=p+q;
		return ;
	}
	if(l==r){
		t[p].maxx+=t[q].maxx;
		t[q].Clear(),st[++top]=q;
		return ;
	}
	int mid=(l+r)/2;
	Merge(t[p].ls,t[q].ls,l,mid);
	Merge(t[p].rs,t[q].rs,mid+1,r);
	Pushup(p);
	t[q].Clear(),st[++top]=q;
}
void Solve(int now,int fa,int dep){
    root[now]=++cntt;
	for(int i=h[now];i;i=e[i].next){
		int y=e[i].to;
		if(y==fa)continue;
		Solve(y,now,dep+1);
		Merge(root[now],root[y],1,n);
	}
	Update(root[now],1,n,dep);
	ans[now]=t[root[now]].maxp-dep;
}
int main(){
	scanf("%d",&n);
	for(int i=2,x,y;i<=n;i++){
		scanf("%d%d",&x,&y);
		Add_Edge(x,y);
		Add_Edge(y,x);
	}
	Solve(1,0,1);
	for(int i=1;i<=n;i++)printf("%d\n",ans[i]);
	return 0;
}
```

---

## 作者：eee_hoho (赞：6)

非常板子的dsu on tree的题，维护最大的$d(u,x)$下最小的深度，然后用这个值减去当前深度就是答案。

**Code**
``` cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
const int N = 1e6;
using namespace std;
int n,edge_cnt,edge[N * 2 + 5],nxt[N * 2 + 5],head[N + 5],dep[N + 5],son[N + 5],size[N + 5],L[N + 5],R[N + 5],dfn_cnt,ID[N + 5],ans[N + 5],sm,mx,mi,cnt[N + 5];
void add_edge(int u,int v)
{
    edge[++edge_cnt] = v;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}
void dfs1(int u,int fa)
{
    size[u] = 1;
    dep[u] = dep[fa] + 1;
    L[u] = ++dfn_cnt;
    ID[dfn_cnt] = u;
    for (int i = head[u];i;i = nxt[i])
    {
        int v = edge[i];
        if (v == fa)
            continue;
        dfs1(v,u);
        size[u] += size[v];
        if (size[v] > size[son[u]])
            son[u] = v;
    }
    R[u] = dfn_cnt;
}
void add(int u,int val)
{
    cnt[dep[u]] += val;
    if (cnt[dep[u]] > mx)
        mx = cnt[dep[u]],mi = dep[u];
    else
        if (cnt[dep[u]] == mx)
            mi = min(mi,dep[u]);
}
void modify(int u,int val)
{
    for (int i = L[u];i <= R[u];i++)
        add(ID[i],val);
}
void dfs2(int u,int fa)
{
    for (int i = head[u];i;i = nxt[i])
    {
        int v = edge[i];
        if (v == son[u] || v == fa)
            continue;
        dfs2(v,u);
        modify(v,-1);
        mx = mi = 0;
    }
    if (son[u])
        dfs2(son[u],u);
    for (int i = head[u];i;i = nxt[i])
    {
        int v = edge[i];
        if (v == son[u] || v == fa)
            continue;
        modify(v,1);
    }
    add(u,1);
    ans[u] = mi - dep[u];
}
int main()
{
    scanf("%d",&n);
    int u,v;
    for (int i = 1;i < n;i++)
    {
        scanf("%d%d",&u,&v);
        add_edge(u,v);
        add_edge(v,u);
    }
    dfs1(1,0);
    dfs2(1,0);
    for (int i = 1;i <= n;i++)
        printf("%d\n",ans[i]);
    return 0;
}
```

---

## 作者：Skyjoy (赞：5)

**本题前置芝士：基础 dp 的思想、树链剖分（或线段树）**

首先，康康题目，我们一眼就能看出这一题暴力 dp 的思路，能很快推出状态转移方程。我们以 $dp_{i,d}$ 表示 i 节点的子树中与 i 距离为 d 的节点的个数，转移方程如下：

$$dp_{i,d}=\sum f_{dp,d-1}$$

其中 j 为 i 的儿子，显然这种做法的复杂度是 $O(n^2)$ ，成功升天。所以此时我们用长链剖分就可以把复杂度降低为 $O(n)$ 了！

啥是长链剖分呢？，这其实就是树剖的一种，详情看

# [这里](https://www.baidu.com/s?tn=50000021_hao_pg&ie=utf-8&sc=UWd1pgw-pA7EnHc1FMfqnHR4nHDsP163P1D4nauW5y99U1Dznzu9m1Y1PHbLPjf3rj0z&ssl_sample=normal&srcqid=4253924105139110542&H123Tmp=nunew7&word=%E9%95%BF%E9%93%BE%E5%89%96%E5%88%86)

~~看上去有点恶心啊~~

这里解释一下吧：

首先，给定一个点 u ，令其到其子树距离最远的叶子结点的距离为 $dep_u$ ，则 u 节点 dep 值最大的儿子就是 u 节点的**长儿子**，这是一个递归就能搞定的。

之后，我们再从一个节点开始，每一次都走向它的长儿子，直到走到叶子，这样的一条路径就是一条**长链**，我们可以把一棵树恰好剖成若干个长链。这和过去我们做过重链剖分的思路是一样一样的！

看代码：

```cpp
void dfs1(int u,int f){//长链剖分 
	size[u]=1,fa[u]=f;//写着无聊，这题没用 
	for(int i=head[u];i;i=e[i].next){
		int v=e[i].to;
		if(v==f){
			continue;
		}
		dfs1(v,u);
		size[u]+=size[v];
		if(dep[v]>dep[son[u]]){
			son[u]=v;
		}
	}
	dep[u]=dep[son[u]]+1;//继承深度
}
```

接下来怎么做 dp 呢？

我们可以对于一个节点 u ，对 $son_u$ 做 dp ，然后把结果直接放入 $dp_u$ ，然后在将其他儿子的结果与 $dp_u$ 合并即可。

而这个过程我们用指针实现。

看代码：

```cpp
void dfs2(int u,int f){//dp过程 
	id[u]=++tot,pos[id[u]]=u;//写着无聊，这题没用 
	dp[u][0]=1;
	if(son[u]){
		dp[son[u]]=dp[u]+1;//共享内存 
		dfs2(son[u],u);
		k[u]=k[son[u]]+1;//继承答案 
	}
	for(int i=head[u];i;i=e[i].next){
		int v=e[i].to;
		if(v==son[u]||v==f){
			continue;
		}
		dp[v]=cur,cur+=dep[v];//分配内存 
		dfs2(v,u);
		for(int i=1;i<=dep[v];i++){
			dp[u][i]+=dp[v][i-1];
			if(dp[u][i]>dp[u][k[u]]||(dp[u][i]==dp[u][k[u]]&&i<k[u])){
				k[u]=i;//更新 
			}
		}
	}
	if(dp[u][k[u]]==1){
		k[u]=0;
	} 
}
```

# 最后完整代码：

```cpp
#include<bits/stdc++.h>
#define N 1000010
using namespace std;
int read(){
	int x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=(x<<3)+(x<<1)+ch-'0';
		ch=getchar();
	}
	return x;
}
int qwq[N];
int n,*dp[N],*cur=qwq,head[N],fa[N],son[N],size[N],dep[N],id[N],pos[N],cnt,tot,k[N],x,y;
struct edge{
	int to,next;
}e[N<<1];
void add(int u,int v){//链式前向星存图 
	e[++cnt].to=v;
	e[cnt].next=head[u];
	head[u]=cnt;
}
void dfs1(int u,int f){//长链剖分 
	size[u]=1,fa[u]=f;//写着无聊，这题没用 
	for(int i=head[u];i;i=e[i].next){
		int v=e[i].to;
		if(v==f){
			continue;
		}
		dfs1(v,u);
		size[u]+=size[v];
		if(dep[v]>dep[son[u]]){
			son[u]=v;
		}
	}
	dep[u]=dep[son[u]]+1;//继承深度 
}
void dfs2(int u,int f){//dp过程 
	id[u]=++tot,pos[id[u]]=u;//写着无聊，这题没用 
	dp[u][0]=1;
	if(son[u]){
		dp[son[u]]=dp[u]+1;//共享内存 
		dfs2(son[u],u);
		k[u]=k[son[u]]+1;//继承答案 
	}
	for(int i=head[u];i;i=e[i].next){
		int v=e[i].to;
		if(v==son[u]||v==f){
			continue;
		}
		dp[v]=cur,cur+=dep[v];//分配内存 
		dfs2(v,u);
		for(int i=1;i<=dep[v];i++){
			dp[u][i]+=dp[v][i-1];
			if(dp[u][i]>dp[u][k[u]]||(dp[u][i]==dp[u][k[u]]&&i<k[u])){
				k[u]=i;//更新 
			}
		}
	}
	if(dp[u][k[u]]==1){
		k[u]=0;
	} 
}
int main(){
	n=read();
	for(int i=1;i<n;i++){
		x=read(),y=read();
		add(x,y),add(y,x);
	}
	dfs1(1,0);
	dp[1]=cur,cur+=dep[1];//分配内存 
	dfs2(1,0);
	for(int i=1;i<=n;i++){
		printf("%d\n",k[i]);
	}
	return 0;
}
```

# 僵卧孤村不自哀，[创宇](https://www.luogu.com.cn/user/147999) AK IOI

---

## 作者：foreverlasting (赞：2)

[题面](https://www.luogu.org/problemnew/show/CF1009F)

长链剖分。

首先要发现$O(n^2)$的DP，这应该是好写的。$dp[i][j]$表示以$i$为根的子树内离$i$距离为$j$的节点个数。转移方程也就很好写了：$dp[i][j]+=dp[tox][j-1]$。然后为了好看一点，方程改成$dp[i][j+1]+=dp[tox][j]$。发现这个方程极其眼熟，这不就是简单版的[HOT](https://www.lydsy.com/JudgeOnline/problem.php?id=4543)吗？于是直接长链剖分就好了。

code:
```
//2018.9.12 by ljz
#include<bits/stdc++.h>
using namespace std;
#define res register int
#define LL long long
#define inf 0x3f3f3f3f
#define eps 1e-15
inline int read(){
    res s=0;
    bool w=0;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')w=1;ch=getchar();}
    while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=getchar();
    return w?-s:s;
}
inline void _swap(res &x,res &y){
    x^=y^=x^=y;
}
inline int _abs(const res &x){
    return x>0?x:-x;
}
inline int _max(const res &x,const res &y){
    return x>y?x:y;
}
inline int _min(const res &x,const res &y){
    return x<y?x:y;
}
const int N=1e6+10;
namespace MAIN{
    int n;
    struct E{
        int next,to;
        E() {}
        E(res next,res to):next(next),to(to) {}
    }edge[N<<1];
    int head[N],cnt;
    inline void addedge(res u,res v){
        edge[++cnt]=E(head[u],v),head[u]=cnt;
        edge[++cnt]=E(head[v],u),head[v]=cnt;
    }
    int fa[N],maxdep[N],dep[N],son[N];
    void dfs(res x,res fax,res depx){
        fa[x]=fax,maxdep[x]=dep[x]=depx;
        for(res i=head[x];~i;i=edge[i].next){
            res tox=edge[i].to;
            if(tox==fax)continue;
            dfs(tox,x,depx+1);
            maxdep[x]=_max(maxdep[x],maxdep[tox]);
            if(maxdep[tox]>maxdep[son[x]])son[x]=tox;
        }
    }
    int ans[N];
    int *dp[N],tmp[N<<5],*now=tmp+1;
    inline void Dp(res x){
        dp[x]=now,now+=maxdep[x]-dep[x]+1;
    }
    void DP(res x){
        if(son[x])dp[son[x]]=dp[x]+1,DP(son[x]),ans[x]=ans[son[x]]+1;
        dp[x][0]=1;
        for(res i=head[x];~i;i=edge[i].next){
            res tox=edge[i].to;
            if(tox==fa[x]||tox==son[x])continue;
            Dp(tox);
            DP(tox);
            for(res j=0;j<=maxdep[tox]-dep[tox];j++){
                dp[x][j+1]+=dp[tox][j];
                if(dp[x][j+1]>dp[x][ans[x]]||(dp[x][j+1]==dp[x][ans[x]]&&ans[x]>j+1))ans[x]=j+1;
            }
        }
        if(dp[x][ans[x]]==1)ans[x]=0;
    }
    inline void MAIN(){
        memset(head,-1,sizeof(head));
        n=read();
        for(res i=1;i<n;i++){
            res u=read(),v=read();
            addedge(u,v);
        }
        dfs(1,0,1);
        Dp(1);
        DP(1);
        for(res i=1;i<=n;i++)printf("%d\n",ans[i]);
    }
}
int main(){
    MAIN::MAIN();
    return 0;
}
```

---

## 作者：Great_Influence (赞：2)

长链剖分练手题。

先把树长链剖分，然后对于每个点，直接继承它偏爱儿子的$dp$数组，然后其他儿子暴力合并。可以证明，每个点所对应的$dp$位置只会被暴力合并1次。因此，时间复杂度就是$O(n)$的。

代码:

```cpp
#include<bits/stdc++.h>
#define Rep(i,a,b) for(register int i=(a);i<=(b);++i)
#define Repe(i,a,b) for(register int i=(a);i>=(b);--i)
#define pb push_back
#define Chkmax(a,b) a=a>b?a:b
#define Chkmin(a,b) a=a<b?a:b
typedef unsigned long long uint64;
typedef unsigned int uint32;
typedef long long ll;

using namespace std;

namespace IO
{
    const uint32 Buffsize=1<<15,Output=1<<23;
    static char Ch[Buffsize],*S=Ch,*T=Ch;
    inline char getc()
	{
		return((S==T)&&(T=(S=Ch)+fread(Ch,1,Buffsize,stdin),S==T)?0:*S++);
	}
    static char Out[Output],*nowps=Out;
    
    inline void flush(){fwrite(Out,1,nowps-Out,stdout);nowps=Out;}

    template<typename T>inline void read(T&x)
	{
		x=0;static char ch;T f=1;
		for(ch=getc();!isdigit(ch);ch=getc())if(ch=='-')f=-1;
		for(;isdigit(ch);ch=getc())x=x*10+(ch^48);
		x*=f;
	}

	template<typename T>inline void write(T x,char ch='\n')
	{
		if(!x)*nowps++='0';
		if(x<0)*nowps++='-',x=-x;
		static uint32 sta[111],tp;
		for(tp=0;x;x/=10)sta[++tp]=x%10;
		for(;tp;*nowps++=sta[tp--]^48);
		*nowps++=ch;
	}
}
using namespace IO;

inline void file()
{
#ifndef ONLINE_JUDGE
	freopen("water.in","r",stdin);
	freopen("water.out","w",stdout);
#endif
}

const int MAXN=1e6+7;

static int n,m,a[MAXN];

vector<int>ed[MAXN];

inline void init()
{
    read(n);
    static int u,v;
    Rep(i,1,n-1)read(u),read(v),ed[u].pb(v),ed[v].pb(u);
}

static int dps[MAXN],fa[MAXN],son[MAXN];

void dfs(int u)
{
    dps[u]=1;
	for(int v:ed[u])if(v^fa[u])
	{
	    fa[v]=u;dfs(v);
	    Chkmax(dps[u],dps[v]+1);
	    if(dps[v]>dps[son[u]])son[u]=v;
	}
}

static int ans[MAXN],cnt[MAXN],e,st[MAXN];

void getans(int u)
{
    int *f=&cnt[st[u]=++e],*g;
    f[ans[u]=0]=1;
    if(son[u])getans(son[u]),ans[u]=ans[son[u]]+1;
	else return;
	if(ans[u]==1)ans[u]=0;
    for(int v:ed[u])if(v^fa[u]&&v^son[u])
	{
		getans(v);
		g=&cnt[st[v]];
		Rep(i,0,dps[v]-1)
		    if((f[i+1]+=g[i])>=f[ans[u]]&&i+1<ans[u]
		    	||f[i+1]>f[ans[u]])
				    ans[u]=i+1;
    }
}

inline void solve()
{
    dfs(1);
    getans(1);
    Rep(i,1,n)write(ans[i]);
    flush();
}

int main()
{
    file();
    init();
    solve();
    return 0;
}

```

---

## 作者：watermonster (赞：1)

很明显的$dp$方程：

$dp_{u,i}=\sum dp_{v,i-1}$

然而空间和时间上都过不去，于是我们需要考虑优化。

我们可以用动态开点线段树来维护这个$dp$数组：

对于每个节点都开一棵以深度为下标的线段树，叶节点维护的是当前子树中**深度**（注意这里不是距离了）为$i$的节点数，而非叶节点维护区间中叶节点信息的最大值。（线段树以深度为下标是因为合并是节点维护的区间应该对应）

这时我们就可以进行深度优先遍历，先处理儿子，再将儿子上的线段树合并到当前节点。处理完所有儿子之后就可以到当前节点的线段树上查	询答案。

查询答案时就可以采用一个很简单的贪心策略：左儿子的值**大于等于**右儿子则向左儿子查询，否则向右儿子查询，到叶节点则直接返回。不过	此时查询到的答案是深度而题目要求的是距离，因此我们需要将答案减去当前节点的深度。



代码：

```cpp
#include <cstdio>

using namespace std;

#define re register
#define il inline
#define isdigit(ch) (ch>=48&&ch<=57)

const int N=1000010;

il void read(int &x)
{
	x=0;char ch=getchar();
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
}
il void write(int x){if(x/10)write(x/10);putchar(x%10+48);}
//IO优化

#define max(a,b) (a>b?a:b)

int cnt,h[N];
struct edge{int v,nxt;}e[N<<1];
il void add(int u,int v){e[++cnt]=(edge){v,h[u]};h[u]=cnt;}
//链式前向星

int n;

int rt[N],pool;
int ls[N<<5],rs[N<<5],val[N<<5];
//val表示当前节点维护的深度区间中最大的节点数量
#define update(p) (val[p]=max(val[ls[p]],val[rs[p]]))
//更新节点信息
il int merge(int p,int q,int l,int r)
{
	if(!p||!q) return q|p;
	if(l==r){val[p]+=val[q];return p;}
	re int mid=(l+r)>>1;
	ls[p]=merge(ls[p],ls[q],l,mid);
	rs[p]=merge(rs[p],rs[q],mid+1,r);
	update(p);return p;
}
//合并线段树
il void insert(int &p,int l,int r,int x)
{
	if(!p) p=++pool;
	if(l==r){++val[p];return;}
	re int mid=(l+r)>>1;
	if(x>mid) insert(rs[p],mid+1,r,x);
	else insert(ls[p],l,mid,x);
	update(p);
}
il int query(int p,int l,int r)
{
	if(l==r) return l;
	re int mid=(l+r)>>1;
	if(val[ls[p]]<val[rs[p]]) return query(rs[p],mid+1,r);
	else return query(ls[p],l,mid);
}
//查询答案
int ans[N],dep[N];
il void dfs(int x,int fa)
{
	dep[x]=dep[fa]+1;
	insert(rt[x],1,n,dep[x]);
	for(re int i=h[x];i;i=e[i].nxt)
		if(e[i].v^fa)//if(e[i].v!=fa)
		{
			dfs(e[i].v,x);
			rt[x]=merge(rt[x],rt[e[i].v],1,n);
		}
	ans[x]=query(rt[x],1,n)-dep[x];
    //由于答案是要当前节点往下的距离，而query返回的是深度，因此要减去dep[x]
}

int main()
{
	read(n);
	for(re int i=1,u,v;i<n;++i)
	{
		read(u),read(v);
		add(u,v);add(v,u);
	}
	dfs(1,0);
	for(re int i=1;i<=n;++i)
		write(ans[i]),puts("");
	return 0;
}
```


---

## 作者：ccviolett (赞：1)

又是一道线段树合并的题目可以直接用 dsu on tree 过掉，写起来非常简单，直接统计每棵子树中每个深度的数量，选其中最大且深度最小的减去当前深度即可。

```cpp
/* Header {{{ */
#include <bits/stdc++.h>
using namespace std;

typedef long long readtype;
typedef long long var;
typedef long double let;

readtype read() {
  readtype a = 0, c = getchar(), s = 0;
  while (!isdigit(c)) s |= c == '-', c = getchar();
  while (isdigit(c)) a = a * 10 + c - 48, c = getchar();
  return s ? -a : a;
}
/* }}} */

const int N = 1e6 + 1;

int n;
int top, fi[N], ne[N << 1], to[N << 1];
int fa[N], size[N], deep[N], maxson[N];
int maxid, have[N];
int res[N];

void Add(int u, int v);
void GetInfo(int t);
void GetRes(int t);
void GetDeep(int rt, int t, int v);

int main() {
#ifndef ONLINE_JUDGE
  freopen("1009F.in", "r", stdin);
  freopen("1009F.out", "w", stdout);
#endif
  n = read();
  for (int i = 1; i < n; ++i) {
    int u = read(), v = read();
    Add(u, v), Add(v, u);
  }
  GetInfo(1);
  GetRes(1);
  for (int i = 1; i <= n; ++i) printf("%d\n", res[i]);
  return 0;
}

void Add(int u, int v) {
  ne[++top] = fi[u], fi[u] = top, to[top] = v;
}

void GetInfo(int t) {
  size[t] = 1, deep[t] = deep[fa[t]] + 1;
  for (int i = fi[t]; i; i = ne[i]) {
    if (to[i] == fa[t]) continue;
    fa[to[i]] = t;
    GetInfo(to[i]);
    size[t] += size[to[i]];
    if (size[to[i]] > size[maxson[t]])
      maxson[t] = to[i];
  }
}

void GetRes(int t) {
  for (int i = fi[t]; i; i = ne[i]) {
    if (to[i] == fa[t] || to[i] == maxson[t]) continue;
    GetRes(to[i]);
    GetDeep(t, to[i], -1);
    maxid = 0;
  }
  
  if (maxson[t]) GetRes(maxson[t]);

  GetDeep(t, t, 1);

  res[t] = maxid - deep[t];
}

void GetDeep(int rt, int t, int v) {
  have[deep[t]] += v;
  if (have[deep[t]] > have[maxid]
      || (have[deep[t]] == have[maxid] && deep[t] < maxid)) maxid = deep[t];
  for (int i = fi[t]; i; i = ne[i]) {
    if (to[i] == fa[t] || to[i] == maxson[rt]) continue;
    GetDeep(rt, to[i], v);
  }
}
```

---

## 作者：qiyue7 (赞：1)

dsu on tree经典  不算难的STL练习题（~~简单的dsu on tree为啥要手写数据结构呢~~）  写的应该算是比较简洁明了的了

具体细节思路可以参考一下下面这题

[另一道dsu_on_tree经典题](https://www.luogu.org/blog/qiyue7ACM/solution-cf375d)

1A代码：

```cpp

using namespace std;
vector<int> edge[1100000];
bool vis[1100000];
queue<int> que;
stack<int> st;
int deep[1100000],ans[1100000],fa[1100000];
set<pair<int, int> > *se[1100000];
unordered_map<int, int> *trans[1100000];
int32_t main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int n, u, v,kk;
	cin >> n;
	memset(vis, 0, sizeof(vis));
	for (int i = 1; i <= n - 1; ++i)
	{
		cin >> u >> v;
		edge[u].push_back(v);
		edge[v].push_back(u);
	}
	que.push(1);
	deep[1] = 0;
	while (!que.empty())
	{
		kk = que.front();
		vis[kk] = 1;
		st.push(kk);
		que.pop();
		for (auto &s : edge[kk])
			if (!vis[s])
				que.push(s),deep[s]=deep[kk]+1,fa[s]=kk;
	}
	for (int i = 1; i <= n; ++i)
	{
		se[i] = new set<pair<int, int> >();
		trans[i] = new unordered_map<int,int>();
		se[i]->insert({ -1, deep[i] });
		(*trans[i])[deep[i]] = 1;
	}
	while (!st.empty())
	{
		kk=st.top();
		st.pop();
		ans[kk] = (se[kk]->begin())->second-deep[kk];
		if (fa[kk])
		{
			if (trans[kk]->size() > trans[fa[kk]]->size())
				swap(trans[kk], trans[fa[kk]]), swap(se[kk], se[fa[kk]]);
			for (auto &s : (*trans[kk]))
			{
				if (trans[fa[kk]]->find(s.first) == trans[fa[kk]]->end())
				{
					(*trans[fa[kk]])[s.first] = s.second;
					se[fa[kk]]->insert({ -s.second,s.first });
				}
				else
				{
					se[fa[kk]]->erase({-(*trans[fa[kk]])[s.first],s.first});
					(*trans[fa[kk]])[s.first] += s.second;
					se[fa[kk]]->insert({ -(*trans[fa[kk]])[s.first],s.first });
				}
			}
		}
		trans[kk]->clear();
	}
	for (int i = 1; i <= n; ++i)
		cout << ans[i] << '\n';
	return 0;
}
```


---

## 作者：OrinLoong (赞：0)

## CFP1009F Dominant Indices 学习笔记
[Luogu Link](https://www.luogu.com.cn/problem/CF1009F)

### 前言
此处讲长剖优化 DP 做法。因为据说树上启发式合并在这题跑得太慢。

实际上启发式合并那个常数还是很有点肉眼可见的，这题 $n$ 开到 $10^6$ 会更明显一些吧……大概。

### 题意简述
给定一棵 $n$ 个结点，以 $1$ 为根的树。定义 $d(u,x)$ 为 $u$ 子树中深度为 $\text{dep}(u)+x$ 的结点数。

对于每个点 $u$，在保证 $d(u,k)$ 最大的前提下求最小化 $k$。

$n\le 10^6$。

### 做法解析
我们先考虑一个朴素 DP。设 $f_{u,j}$ 表示 $u$ 的子树中与 $u$ 距离为 $j$ 的点的个数。则有转移方程：$f_{u,j}=\sum_{v\in \text{son}(u)} f_{v,j-1}$，$u$ 的答案即为 $\max f_{u,i}$。$ans_u$ 即为满足 $f_{u,k}=\max f_{u,i}$ 的所有 $k$ 中的最小值。

但是这坨玩意时空都是 $O(n^2)$ 的，所以我们需要优化。观察到这玩意在树形态均匀的时候差不多是 $O(n\log n)$ 的，这启示我们用树剖干掉它，又因为柿子和深度相关，考虑长剖。

长剖优化 DP 究竟是个什么东西？搞懂这题就明白了。

你先考虑一个情景：假如在一条内存空间里我存下了长成这样子的 $f_v$ 数组：

![pE7rh3d.md.png](https://s21.ax1x.com/2025/04/29/pE7rh3d.md.png)

那么我们会发现，我们往前面再加一格空间，啪的一下，$f_v$ 数组就以 $O(1)$ 的代价转移成了 $f_u$ 数组！

也就是说，我们可以通过合理地分配空间，让 $f_u$ 的一个儿子 $O(1)$ 地转移到 $f_u$，同时其它儿子则不得不暴力合并，感性理解我们应该选择 $f_u$ 的长儿子这么做。

![pE7r4gA.md.png](https://s21.ax1x.com/2025/04/29/pE7r4gA.md.png)

理性理解，一方面我们发现我们必须选择长儿子这么做，否则 $f_v$ 的数组装不下长儿子的数组；另一方面这样时空复杂度也有保证：因为每个长链的状态都有且仅有一次被暴力合并（就是在链顶），而长链总长就是 $O(n)$ 的，所以时间复杂度 $O(n)$，空间上每个结点只用占一格，所以空间复杂度 $O(n)$。

至于这个空间具体怎么分配？遍历出长儿子优先的 dfs 序后，$u$ 的数组空间始于自己的 $\text{dfn}$，长度为从自己开始往下的结点数量。

### 代码实现
说话便宜，展示代码。

```cpp
#include <bits/stdc++.h>
using namespace std;
using namespace obasic;
const int MaxN=1e6+5;
int N,X,Y;
vector<int> Tr[MaxN];
void addudge(int u,int v){
    Tr[u].push_back(v);
    Tr[v].push_back(u);
}
int dep[MaxN],epd[MaxN],dson[MaxN];
void dfs1(int u,int f){
    epd[u]=dep[u]=dep[f]+1;
    for(int v : Tr[u]){
        if(v==f)continue;
        dfs1(v,u);if(epd[v]>epd[dson[u]])epd[u]=epd[v],dson[u]=v;
    }
}
int pool[MaxN],dfn[MaxN],dcnt,ans[MaxN];
void updans(int u,int x){
    int &a=pool[dfn[u]+ans[u]],&b=pool[dfn[u]+x];
    if(b>a||(b==a&&x<ans[u]))ans[u]=x;
}
void dfs2(int u,int f){
    int &du=dfn[u];
    du=++dcnt,pool[du]=1;if(!dson[u])return;
    dfs2(dson[u],u),updans(u,ans[dson[u]]+1);
    for(int v : Tr[u]){
        if(v==f||v==dson[u])continue;
        dfs2(v,u);int &dv=dfn[v];
        for(int i=0;i<=epd[v]-dep[v];i++){
            pool[du+i+1]+=pool[dv+i];
            updans(u,i+1);
        }
    }
}
int main(){
    readi(N);
    for(int i=1;i<N;i++)readis(X,Y),addudge(X,Y);
    dfs1(1,0);dfs2(1,0);
    for(int i=1;i<=N;i++)writil(ans[i]);
    return 0;
}
```

---

