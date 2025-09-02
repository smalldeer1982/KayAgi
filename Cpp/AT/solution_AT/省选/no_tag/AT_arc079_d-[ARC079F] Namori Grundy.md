# [ARC079F] Namori Grundy

## 题目描述

高桥君有一个$N$个点$N$条边的有向图，点的的编号从$1$到$N$

高桥君的图有$N$条边，形如：$(p_1,1),(p_2,2),...,(p_N,N)$，保证图是弱连通的。其中，$(u,v)$表示一条从点$u$到$v$的单向边。“弱连通”是指：假如所有的边都是双向边，则图是连通图

高桥君为每个点设置了一个权值，$a_i$表示点$i$的权值。他希望图满足如下性质：

所有$a_i$都是非负整数

对于每条边$(i,j)$，满足$a_i≠a_j$

对于所有$i,x(0\le x\lt a_i)$，存在一条边$(i,j)$满足$x=a_j$

请你帮高桥君判断一下，这样图是否存在呢？

## 说明/提示

$2 \leq N \leq 200000$

$1 \leq p_i \leq N$

$p_i \ne i$

保证给定的图是弱联通的

## 样例 #1

### 输入

```
4
2 3 4 1```

### 输出

```
POSSIBLE```

## 样例 #2

### 输入

```
3
2 3 1```

### 输出

```
IMPOSSIBLE```

## 样例 #3

### 输入

```
4
2 3 1 1```

### 输出

```
POSSIBLE```

## 样例 #4

### 输入

```
6
4 5 6 5 6 4```

### 输出

```
IMPOSSIBLE```

# 题解

## 作者：Ebola (赞：5)

### 题意

给定一个$N$个点的基环外向树，你需要给所有点设置权值，对于任意一个点$p$，需要满足：

1. $w_p$是一个非负整数

2. $[0,w_p)\cap \mathbb{Z}\subseteq\{w_{son_p}\}$

3. $w_p\notin \{w_{son_p}\}$

请你判断给定的图是否存在合法的权值分配方案

### 题解

首先考虑一棵树。

根据第二条限制条件，叶子节点权值必然是0，然后从叶子节点往上推，整棵树的权值分配有且只有一种方案。这个在代码上也很好实现，对于每个节点，将所有直接相连的子节点的权值对应的$vis$值设为$true$，然后从小到大找到第一个$vis$值为$false$的权值，这个权值就是当前节点的权值

接下来考虑一个环。不难想到，对于一个独立的环，它里面点的权值只能为$0$或$1$，并且两个值是交替分布的，假如这是一个奇环，那就不存在合法的权值分配方案了

那么将两个情况综合到一起来看。基环上的点，除了自己的子树以外，最多再指向环中的一个点，所以通过子树计算出它的权值后，最多还有$+1$的调整空间，并且当且仅当它所指向的环中另一个点权值恰好与它相同，他需要进行$+1$操作。假如它所指向的环中另一个点权值与它不相等，那么这个点的权值不需要也不能进行调整，因为假设它的权值是$x$，此时他的权值如果变小一些，会导致不满足条件三；如果大一些，会导致$x$不在子节点权值集合中。

以上分析非常明显地指向了一个结论：**当且仅当基环中所有点权值相同，并且这个基环是一个奇环，此时不存在权值分配方案，其它任何情况下都是存在的**

也许我的分析过程不是非常严谨，思维可能也有点跳，不过稍微YY一下，正确性还是非常显然的。代码实现也很简单。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int S=(1<<20)+5;
char buf[S],*H,*T;
inline char Get()
{
	if(H==T) T=(H=buf)+fread(buf,1,S,stdin);
	if(H==T) return -1;return *H++;
}
inline int read()
{
	int x=0;char c=Get();
	while(!isdigit(c)) c=Get();
	while(isdigit(c)) x=x*10+c-'0',c=Get();
	return x;
}

inline void upmax(int &x,const int &y){if(y>x) x=y;}
inline void upmin(int &x,const int &y){if(y<x) x=y;}

const int N=200010;
struct Edge{int to,next;} e[N];
int h[N],sum=0,n;
int fa[N],mex[N];
bool vis[N],loop[N];
bool have[N];

void add_edge(int u,int v)
{
	e[++sum].to=v;
	e[sum].next=h[u];
	h[u]=sum;
}

void dfs(int u)
{
	for(int t=h[u];t;t=e[t].next)
		if(!loop[e[t].to]) dfs(e[t].to);
	for(int t=h[u];t;t=e[t].next)
		if(!loop[e[t].to]) have[mex[e[t].to]]=1;
	while(have[mex[u]]) mex[u]++;
	for(int t=h[u];t;t=e[t].next)
		if(!loop[e[t].to]) have[mex[e[t].to]]=0;
}

int main()
{
	int n,x=1;
	n=read();
	for(int i=1;i<=n;i++)
	{
		fa[i]=read();
		add_edge(fa[i],i);
	}
	while(!vis[x]) vis[x]=1,x=fa[x];
	while(!loop[x]) loop[x]=1,x=fa[x];
	int mx=-1,mn=n+1,cnt=0;
	for(int i=1;i<=n;i++)
	{
		if(!loop[i]) continue;
		dfs(i);cnt++;
		upmax(mx,mex[i]);
		upmin(mn,mex[i]);
	}
	puts(mx==mn&&(cnt&1)?"IMPOSSIBLE":"POSSIBLE");
	return 0;
}
```



---

## 作者：Krimson (赞：4)

[点击](https://www.cnblogs.com/Guts/p/14721700.html)获得更好的阅读体验。

---------------------


首先根据题目可以得到两个信息：

- 给定的图是一颗基环外向树。

- 每个点的权值是其所有出边指向的点 $v$ 的权值 $a_{v}$ 的 $mex$ 。

其中第二点可以通过简单的反证法得到。  



1. 非环部分

   可以直接`dfs`，从叶子结点开始往上确定整棵树。

   这样，就已经可以处理非环部分的每一颗子树了，问题就只剩下了环上的点。  

2. 环上部分

   看到大部分人对于环这里都是采用了一些比较高妙的做法。

   但是我比较菜，想不到，于是直接敲了个“暴力“。  

   可以发现只要确定了环上的任意一个点，整个环也就被确定了。

   那么不妨随便选一个点 $u$，枚举$a_u$，填完整个环之后反过来check一下 $a_u$ 是不是 $mex_u$。

   由于 $a_{u}\leq n$ ，所以这里已经有一个 $O(n^2)$ 的做法了。

   

   但是前面所得的这个 $a_{u}$的上界显然比较粗略，尝试做一点优化。  

   对于选定的 $u$，把它除去环上的点的儿子的点权去重之后的个数 $siz$ 求出来，显然有 $a_{u}\leq siz+1$

   ~~然后一交上去发现跑得飞快~~  

   实际上，这种做法的复杂度是正确的。  

   考虑到一个非环点 $v$ 的点权是 $a_v$ ，这意味着它的儿子的权值至少满足分别为 $1$~$a_{v}-1$。  

   设 $f(x)$ 表示一个权值为 $x$ 的点为根的子树里最少点的数量，那么可以得到:
   $$
   \begin{aligned}
   f(x)&=1+\sum^{x-1}_{i=0}f(i)\\
   f(0)&=1
   \end{aligned}
   $$
   所以有 $f(x)=2^x$ 。

   所以枚举的次数是 $O(\log n)$，总时间复杂度为 $O(n\log n)$。


_Code_
------------------------------


 ```cpp
 #include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
#define il inline
#define ri register int
#define ll long long
#define ui unsigned int
il ll read(){
    bool f=true;ll x=0;
    register char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-') f=false;ch=getchar();}
    while(ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
    if(f) return x;
    return ~(--x);
}
il void write(const ll &x){if(x>9) write(x/10);putchar(x%10+'0');}
il void print(const ll &x) {x<0?putchar('-'),write(~(x-1)):write(x);putchar('\n');}
il ll max(const ll &a,const ll &b){return a>b?a:b;}
il ll min(const ll &a,const ll &b){return a<b?a:b;}
const int MAXN=2e5+7;
int mark[MAXN],col[MAXN],n;
int vec[MAXN],top;
int a[MAXN];
vector<int> g[MAXN];
int mex(int u){
    top=0;
    for(ri i=0;i<g[u].size();++i){
        int v=g[u][i];
        vec[++top]=a[v];
    }
    sort(vec+1,vec+top+1);
    int ans=0;
    for(ri i=1;i<=top;++i){
        if(vec[i]==ans) ++ans;
        else if(vec[i]>ans) break;
    }
    return ans;
}
void get_circle(int u){    
    for(ri i=0;i<g[u].size();++i){
        int v=g[u][i];
        if(!col[v]){
            col[v]=col[u];
            get_circle(v);
            if(mark[v]) mark[u]=1;
        }
        else if(col[u]==col[v]){
            mark[u]=1;
            return;
        }
    }
}
void dfs(int u){
    int now=0;
    for(ri i=0;i<g[u].size();++i){
        int v=g[u][i];
        dfs(v);
    }
    a[u]=mex(u);
}
int root,tot=1e9;
int vis[MAXN],fa[MAXN];
int main(){
    n=read();
    for(ri i=1;i<=n;++i){
        int u=read();
        g[u].push_back(i);
    }
    for(ri i=1;i<=n;++i){
        if(!col[i]) col[i]=i,get_circle(i);
        if(mark[i]) break;
    }
    for(ri i=1;i<=n;++i){
        if(mark[i]){
            vector<int> revec;
            int cnt=0;
            for(ri j=0;j<g[i].size();++j){
                int u=g[i][j];
                if(mark[u]){
                    fa[u]=i;
                    continue;
                }
                dfs(u);
                revec.push_back(a[u]);
            }
            sort(revec.begin(),revec.end());
            revec.erase(unique(revec.begin(),revec.end()),revec.end());
            cnt=revec.size()+1;
            if(cnt<tot) root=i,tot=cnt;
        }
    }
    vector<int> vec;
    for(ri i=0;i<=tot+1;++i){
        a[root]=i;
        for(ri u=fa[root];u!=root;u=fa[u])
            a[u]=mex(u);
        if(mex(root)==i) return !puts("POSSIBLE");
    }
    puts("IMPOSSIBLE");
    return 0;
}
 ```





---

## 作者：封禁用户 (赞：3)

[更好的阅读体验哦](https://www.cnblogs.com/wo-shi-zhen-de-cai/p/11598083.html)

> 题意：有一个弱联通的有向图，含有$n$个结点和$n$条边。试问是否存在方案，赋给每个结点一个自然数权值$val_i$，满足对于所有结点$u$,$val_u=mex\{val_v|(u,v)\in E\}$。一个集合的$mex$是没有在这个集合中出现的最小自然数。

显然是个基环树，先考虑在树上的情况。

对于一棵树，完全可以将其叶子的值赋为$0$，然后再顺次向上做即可，一定存在这样的方案。

在基环树上，最后会化为一个环，每个点有权值，所以我们只要考虑环上的不满足情况即可。

考虑两个在环上相邻的节点$u\rightarrow v$，设它们的$val_u$和$val_v$

- $val_u>val_u$，那么不需要修改权值。

- $val_u=val_v$，那么把$val_u$变成$val_u+1$
- $val_u<val_v$，那么不需要修改权值。

综上，当且仅当环上点权相同且点数为奇数时不存在方案（因为$+1$时会死循环）

值得注意的是，对于一个点要先跑完所有子树再将子节点权值加入桶中，计算$mex$。不然会在某个子树中出现其他子树的答案。。。

```c++
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int read()
{
    int f=1,w=0;char x=0;
    while(x<'0'||x>'9') {if(x=='-') f=-1; x=getchar();}
    while(x!=EOF&&x>='0'&&x<='9') {w=(w<<3)+(w<<1)+(x^48);x=getchar();}
    return w*f;
}
const int N=200010;
const int INF=1e18;
int num_edge,n,Cnt;
int Cir[N],Vis[N],Val[N];
int head[N<<1],fa[N],Jud[N];
struct Edge{int next,to;} edge[N<<1];
inline void Add(int from,int to)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	head[from]=num_edge;
}
inline void Dfs(int pos)
{
	for(int i=head[pos];i;i=edge[i].next)
		if(!Cir[edge[i].to]) Dfs(edge[i].to);
	for(int i=head[pos];i;i=edge[i].next)
		if(!Cir[edge[i].to]) Jud[Val[edge[i].to]]=1;
	for(;Jud[Val[pos]];Val[pos]++);
	for(int i=head[pos];i;i=edge[i].next)
		if(!Cir[edge[i].to]) Jud[Val[edge[i].to]]=0;
}
main(){
	int pos=1;n=read();
	for(int i=1;i<=n;i++) fa[i]=read(),Add(fa[i],i);
	for(;!Vis[pos];pos=fa[pos]) Vis[pos]=1;
	for(;!Cir[pos];pos=fa[pos]) Cir[pos]=1;
	int Max=-1,Min=INF;
	for(int i=1;i<=n;i++)
		if(Cir[i]) Cnt++,Dfs(i),Max=max(Max,Val[i]),Min=min(Min,Val[i]);
	if(Max==Min&&Cnt&1) puts("IMPOSSIBLE");
	else puts("POSSIBLE");
}
```



---

## 作者：迟暮天复明 (赞：1)

不一样的做法。

显然这个图是一个环连着很多点，那么不在环上的点的点权是唯一确定的。对于环上的任意一个点来说，因为它连出去的点只有一个点的权值还没有确定，所以这个点的权值只有两种可能：$\operatorname{mex}\{v\}$ 和 $\operatorname{mex}\{v,\operatorname{mex}\{v\}\}$。同时，对于环上的任意一个点来说，只要它的权值确定了，整张图也就确定了。于是随便选一个点把这两个取值分别带进去看看有没有成立的就可以了。时间复杂度 $O(N)$。

---

## 作者：fade_away (赞：0)

# ARC079F - Namori Grundy
[安利博客](https://blog.csdn.net/xmr_pursue_dreams/article/details/111868414)
## Solution

首先这是一个$N$个点$N$条边的有向图，所以它的基图是一棵基环树，其次这个图的所有点入度为$1$，因此这是一棵基环外向树。

然后对于$a_i$，假设我们求出$S=\{a_j|(i,j)\in E\}$，即$i$的所有出边的$a$的集合，那么显然$a_i=mex\;S$，$a_i$的值是可以通过其出边唯一确定的。

我们先考虑一棵树的情况，我们发现叶子结点必然为$0$，因此每一个结点$i$的$a_i$都可以从下到上通过其儿子结点递推得到。

现在考虑基环树，对于环上一点，我们可以通过它的子树唯一确定去掉环时它的$a$，然后可以发现**当且仅当环长为奇数且环上结点的$a$都相等时无解**。

然后直接找到环，递推求出每一个$a$，判一判就行了。

时间复杂度$O(n)$。
### Proof 
现在我们可以把子树点都扔掉，只考虑一个$k$元环。
我们设环上点依次为$0,1,2...k-1$，$(i+1,i)\in E$，（之后的下标都在模$k$意义下）。
1. 若$a_{i+1}$要加$1$，当且仅当$a_{i+1}=a_i$。
2. 因为环上点出度为$1$，一个点最多加$1$。

首先我们不会让所有点都加$1$，因为这和所有点不变一样，所以若**存在方案，一定有一种有至少一个点$p$不动的方案**。

如果我们知道$p$，那么我们可以从$p$开始判断$a_p$是否等于$a_{p+1}$，若相等则$a_{p+1}+1$。

我们令一段连续的$+1$的下标区间为$[l+1,r]$，显然有$a_{l}=a_{l+1},a_{l+1}+1=a_{l+2},a_{l+2}+1=a_{l+3}...$，因此这段$a$一定是$a_l,a_l,a_l+1,a_l+2...a_l+(r-l-1)$，点$l$不动且为其中的最小值。

所以我们有结论：**若能找到一个$i$，使得$a_i\not = a_{i-1}$且$\forall_j a_i\leq a_j$，$i$可以作为$p$，方案存在。**

那么最后还剩下找不到$i$的环，其上的点必然是所有$a$相等的，这个就很容易考虑了，因为所有点都等价，所以可以任取一个作为$p$，最后的序列一定长成$a_p,a_p+1,a_p,a_p+1,a_p,a_{p}+1...$的形式。

**这就相当于一个二分图染色，只有当$k$为奇数时，存在相邻两个$a$相等，不合法；当$a$为偶数时存在合法方案。**

综上，当且当且仅当环长为奇数且环上结点的$a$都相等时无解。
## Code

```cpp
vector<int> e[MAXN];
int fa[MAXN],vis[MAXN],instk[MAXN],flag[MAXN],tag[MAXN],f[MAXN],n;
void dfs(int x)
{
	vis[x]=1,instk[x]=1;
	for (auto v:e[x])
	{
		if (instk[v]) 
		{
			for (int p=x;p!=v;p=fa[p]) flag[p]=1;
			flag[v]=1;
		}
		else fa[v]=x,dfs(v);
	}
	instk[x]=0;
}

void tree_dp(int x,int father)
{
	for (auto v:e[x]) if (v!=father&&!flag[v]) tree_dp(v,x);
	for (auto v:e[x]) if (v!=father&&!flag[v]) tag[f[v]]=x;
	for (int i=0;i<n;i++) 
		if (tag[i]!=x) { f[x]=i; return; }
}

signed main()
{
	n=read();
	for (int i=1,x;i<=n;i++) x=read(),e[x].PB(i);
	for (int i=1;i<=n;i++) if (!vis[i]) dfs(i);
	int p=0,num=0;
	for (int i=1;i<=n;i++) 
		if (flag[i]) tree_dp(i,0),p=f[i],num++;
	if (!(num&1)) { puts("POSSIBLE"); return 0; } 
	for (int i=1;i<=n;i++)
		if (flag[i]&&p!=f[i]) { puts("POSSIBLE"); return 0; }
	puts("IMPOSSIBLE");
	return 0;
}


```


---

