# 「RdOI R2」路径权值(distance)

## 题目背景

此题读入量较大，请选择合适的读入方式。

## 题目描述

给你一棵 $n$ 个点的边带权有根树，根节点为编号为 $1$ 的节点。定义 $u$ 的 $k-son$ 为 $u$ 子树中深度（指经过边数）比 $u$ **恰好**大 $k$ 的所有点。  
$m$ 次询问求一个点 $u$ 的 $k-son$ 两两之间距离的和。你需要输出这个值 $\bmod\left(10^9+7\right)$ 的结果。

## 说明/提示

**样例 $1$ 解释**

以下是样例中的树。  
![](https://cdn.luogu.com.cn/upload/image_hosting/lz4oy8ao.png)

---

**样例 $2$ 解释**

以下是样例中的树。  
![](https://cdn.luogu.com.cn/upload/image_hosting/hb45pofr.png)

---

**数据范围**

对于 $20\%$ 的数据，$n,m,k\le100$。  
对于 $50\%$ 的数据，$n,m,k\le10^3$。  
对于 $80\%$ 的数据，$n,m,k\le10^5$。  
对于 $100\%$ 的数据，$1\le n,m,k\le10^6,1\le k\le n,1\le w\le10^5,1\le u,v\le n$，保证给出的是一棵树。  

## 样例 #1

### 输入

```
5 3 
1 2 2
1 3 1
2 4 1
2 5 2
1 1
1 2
2 1```

### 输出

```
3
3
3```

## 样例 #2

### 输入

```
10 5
1 2 1
1 3 3
2 4 2
2 5 2
3 6 3
3 7 1
5 8 2
6 9 1
6 10 3
1 2
3 2
6 1
1 3
2 2```

### 输出

```
40
4
4
30
0```

# 题解

## 作者：abruce (赞：7)

### 20pts  
直接用 vector 存 u 的 k-son，每次询问暴力即可。  
### 50pts
考虑 $O(n^2)$ 的动态规划：一个点的贡献等于以它为 LCA 的贡献加上它子树为 LCA 的贡献。  
我们想到设 $f[u][k]$ 为 $u$ 深度为 $k$ 的答案。首先 $f[u][k]=\sum\limits_{v\in u} f[v][k-1]$。这些就是子树为 LCA 的贡献，接下来考虑如何计算它为 LCA 的贡献。  
假设以 $u$ 为根，计算两个儿子 $v$ 与 $w$ 之间贡献，则产生贡献的边为红色。  
![](https://cdn.luogu.com.cn/upload/image_hosting/7wsg394a.png)  
我们需要两个辅助数组 $g,h$，其中 $g[u][k]$ 代表 $u$ 的 $k-son$ 到其距离和，$h[u][k]$ 代表 $u$ 有多少个 $k-son$。  
这两个的转移方程显而易见：$g[u][k]=\sum\limits_{v\in u}g[v][k-1]+w(u,v)\times h[v][k-1],h[u][k]=\sum\limits_{v\in u}h[v][k-1],h[u][0]=1$，其中 $w(u,v)$ 代表边权。  
转移完 $g,h$ 后，我们发现对于一个新的子树 $w$，前面的所有子树 $v$ 产生的贡献是 $g[u][k]\times h[w][k-1]$（假设 $g[u][k]$ 已被前面的所有 $v$ 更新），而 $v$ 对 $w$ 的贡献是 $h[u][k]\times (g[w][k-1]+h[w][k-1]\times w(u,w))$。  
整合一下，$f[u][k]=\sum\limits_{v\in u}f[v][k-1]+g[u][k]\times h[v][k-1]+h[u][k]\times (g[v][k-1]+h[v][k-1]\times w(u,v))$，注意三个必须一起转移。  
### 80pts  
似乎可以有 ODTREE王子 的线段树合并和 Time_Tears 的神奇 DSU+树状数组解法。第一种做法本来能过现在已经 MLE 了。
## 100pts
因为 dp 数组第二维是以深度为下标，似乎可以长链剖分。  
但 $g$ 数组的转移形式不利于长剖。  
考虑将 $g$ 数组用树上差分进行转移，设 $dis[u]$ 为 $u$ 到根距离。则 $g$ 转移改为 $g[u][k]=\sum\limits_{v\in u}g[v][k-1],g[u][0]=dis[u]$，所有值调用时需要减去 $dis[u]\times h[u][k]$。  
则 $f$ 数组转移改为 $f[u][k]=\sum\limits_{v\in u}f[v][k-1]+(g[u][k]-dis[u]\times h[u][k])\times h[v][k-1]+h[u][k]\times (g[v][k-1]-dis[u]\times h[v][k-1])$。  
时间复杂度 $O(n)$。  
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+5,mod=1e9+7;
typedef long long ll;
char __buf[1<<21],*__p1,*__p2;
#define getchar() (__p1==__p2?(__p2=__buf+fread(__p1=__buf,1,1<<21,stdin),__p1==__p2?EOF:*__p1++):*__p1++)
inline int read() {
	int __x=0,__f=1;
	char __c=getchar();
	while(__c<'0'||__c>'9') {
		if(__c=='-')__f=-1;
		__c=getchar();
	}
	while(__c>='0'&&__c<='9') {
		__x=__x*10+__c-'0';
		__c=getchar();
	}
	return __x*__f;
}
inline char pc(char ch,bool bj) {
	static char buf[1<<18],*p1=buf,*p2=buf+(1<<18);
	return ((bj)||(*p1++=ch)&&p1==p2)&&fwrite(p1=buf,1,p1-buf,stdout),0;
}
void print(ll x) {
	if(x>9)print(x/10);
	pc(x%10^48,false);
}
inline void printnum(ll x,int ch) {
	print(x),pc(ch,false);
}
struct edge {
	int next,to,v;
} e[maxn];
int n,m,son[maxn],len[maxn],maxd[maxn];
ll tmp[maxn*3],*f[maxn],*g[maxn],*h[maxn],*id=tmp,ans[maxn],dis[maxn],hd[maxn],cnt;//注意一些数组需要开 long long
vector<int> q[maxn],qi[maxn];
void addedge(int x,int y,int z) {
	e[++cnt].next=hd[x];
	e[cnt].to=y;
	e[cnt].v=z;
	hd[x]=cnt;
}
void dfs(int u,int fa) {
	for(register int i=hd[u]; i; i=e[i].next) {
		int j=e[i].to;
		dis[j]=dis[u]+e[i].v;
		dfs(j);
		if(maxd[j]>maxd[son[u]])son[u]=j;
	}
	maxd[u]=maxd[son[u]]+1;
}
void dp(int u) {
	if(son[u])f[son[u]]=f[u]+1,g[son[u]]=g[u]+1,h[son[u]]=h[u]+1,dp(son[u]);//先走长儿子
	g[u][0]=dis[u],h[u][0]=1;
	for(register int i=hd[u]; i ; i=e[i].next) {
		int j=e[i].to;
		if(j==son[u])continue;
		f[j]=id,id+=maxd[j],g[j]=id,id+=maxd[j],h[j]=id,id+=maxd[j];
		dp(j);
		for(register int k=1; k<=maxd[j]; k++) {
			f[u][k]=(f[u][k]+f[j][k-1]+(g[u][k]-dis[u]*h[u][k]%mod+mod)%mod*h[j][k-1]%mod+h[u][k]*(g[j][k-1]-dis[u]*h[j][k-1]%mod+mod)%mod)%mod;
			g[u][k]=(g[u][k]+g[j][k-1])%mod;
			h[u][k]=(h[u][k]+h[j][k-1])%mod;//将轻儿子的信息合并上去
		}
	}
	for(register int i=0; i<q[u].size(); i++)if(q[u][i]<maxd[u])ans[qi[u][i]]=f[u][q[u][i]];//长剖必须离线求答案
}
int main() {
	int x,y,z;
	n=read(),m=read();
	for(register int i=1; i<n; i++) {
		x=read(),y=read(),z=read();
		addedge(x,y,z);
	}
	dfs(1);
	for(register int i=1; i<=m; i++) {
		x=read(),y=read();
		q[x].push_back(y),qi[x].push_back(i);
	}
	f[1]=id,id+=maxd[1],g[1]=id,id+=maxd[1],h[1]=id,id+=maxd[1];
	dp(1);
	for(register int i=1; i<=m; i++)printnum(ans[i],'\n');
	pc(0,1);
	return 0;
}
```

---

## 作者：a___ (赞：6)

出题人想让我们写长链剖分，所以我们就不写长链剖分。我们写树上启发式合并。  

考虑每个点开一个类似数组的东西，记该点的子树对于每个 $dep$ 的 $(sum=\sum dis),tot,ans$。

那么合并两个子树时,对于任意两个点 $x,y$，$dis(x,y)=dis_x+dis_y-2dis_{lca}$。

设我们合并 $u$ 和其儿子 $v$ 所在子树，则对于每个 $dep$，
$$\begin{aligned}
ans_u&=ans_u+ans_v+\sum_{x\in u}\sum_{y\in v}dis(x,y)\\
&=ans_u+ans_v+\sum_{x\in u}\sum_{y\in v}dis_x+dis_y-2dis_u\\
&=ans_u+ans_v+\sum_{x\in u}dis_x\sum_{y\in v}1+\sum_{y\in v}dis_y\sum_{x\in u}1-2dis_u\sum_{x\in u}\sum_{y\in v}1\\
&=ans_u+ans_v+sum_utot_v+sum_vtot_u-2tot_utot_vdis_u
\end{aligned}$$

现在的问题是对于每一个 $dep$ 都进行一次合并。我们选择使用 `set`，然后启发式合并，时间复杂度 $\mathbf O(n\log n)$，空间复杂度 $\mathbf O(n)$。

至于为什么启发式合并 `set` 是 $\mathbf O(n\log n)$ 的，首先遍历 `set` 是 $\mathbf O(n)$ 的，然后按顺序插入也是 $\mathbf O(n)$ 的，所以摊下来复杂度就是对的。

而空间复杂度是 $\mathbf O(n)$ 的原因是我们可以每次合并后把那个没用的 `set` 清空，这样可以保证同一时刻所有 `set` 中仅有 $\mathbf O(n)$ 个节点。

对于每个询问，把它挂到对应节点上，查这个点 $dep+k$ 的答案就好。

代码

```cpp
#include<cstdio>
#include<set>
#include<vector>
#include<algorithm>
const int N=1e6+10,logN=30,p=1e9+7;
int n,m,rt[N],ans[N],dep[N],dis[N];
struct edge
{
	int v,w,la;
	inline void set(int _v,int _w,int _la){v=_v;w=_w;la=_la;}
}e[N<<1];
struct node
{
	int val,tot,sum,ans;
	bool operator< (const node &x) const {return val<x.val;}
};
int la[N],cnt;
inline void add(int u,int v,int w){e[++cnt].set(v,w,la[u]);la[u]=cnt;}
inline void add(){int a,b,c;scanf("%d%d%d",&a,&b,&c);add(a,b,c);add(b,a,c);}
std::vector<std::pair<int,int> >qu[N];
std::set<node>c[N];
int merge(int x,int y,int z)
{
	if(c[x].size()<c[y].size())x^=y^=x^=y;
	std::set<node>::iterator it,i;node tmp;
	for(i=c[y].begin();i!=c[y].end();++i)
	{
		it=c[x].find(*i);
		if(it==c[x].end()){c[x].insert(*i);continue;}
		tmp=*it;c[x].erase(it);
		tmp.ans=(tmp.ans+i->ans+1ll*tmp.sum*i->tot%p+1ll*tmp.tot*i->sum%p-2ll*tmp.tot*i->tot%p*z%p+p)%p;
		tmp.sum=(tmp.sum+i->sum)%p;
		tmp.tot=(tmp.tot+i->tot)%p;
		c[x].insert(tmp);
	}
	c[y].clear();return x;
}
void dfs(int u,int f)
{
	dep[u]=dep[f]+1;c[rt[u]=u].insert((node){dep[u],1,dis[u],0});
	for(int i=la[u];i;i=e[i].la)
	if(e[i].v!=f)dis[e[i].v]=(dis[u]+e[i].w)%p,
	dfs(e[i].v,u),rt[u]=merge(rt[u],rt[e[i].v],dis[u]);
	int i,n=qu[u].size();
	std::set<node>::iterator it;
	for(i=0;i<n;i++)
	{
		it=c[rt[u]].find((node){dep[u]+qu[u][i].first,0,0,0});
		if(it!=c[rt[u]].end())ans[qu[u][i].second]=it->ans;
	}
}
int main()
{
	int i,x,y;scanf("%d%d",&n,&m);
	for(i=1;i<n;i++)add();
	for(i=1;i<=m;i++)scanf("%d%d",&x,&y),qu[x].push_back(std::make_pair(y,i));
	dfs(1,0);
	for(i=1;i<=m;i++)printf("%d\n",ans[i]);
	return 0;
}
```

---

## 作者：RedreamMer (赞：3)

[$\huge\texttt{P7581}$](https://www.luogu.com.cn/problem/P7581)

[$\texttt{My cnblogs}$](https://www.cnblogs.com/RedreamMer/p/14732487.html)

## 前言

刚学了长剖，比赛快结束的时候进来看了一眼，口胡秒了，写的时候发现巨大多细节，~~口胡不行~~。

长剖永存，空间卡的好啊！

## 题意

不做赘述。

## 思路

首先看到这是一道和深度有极大的关系，自然联想到建几个以深度为下标的数组通过 DFS 遍历并动态修改解决问题，而且可以用启发式合并的类似思路合并子树信息，因此能联想到用长链剖分解决问题。

但是长链剖分对数组空间和对子树信息继承关系要求比较苛刻，比如一开始我是这么想的：

+ 记录 $val[u][i]$ 表示以 $u$ 为根的子树所有深度为 $i$ 的节点到 $u$ 的路径长度之和。
+ 记录 $dis[u][i]$ 表示以 $u$ 为根的子树所有深度为 $i$ 的节点之间的距离之和。
+ 记录 $siz[u][i]$ 表示以 $u$ 为根的子树所有深度为 $i$ 的节点的个数。

$dis[u]$ 和 $siz[u]$ 的转移都很好写：

$$
dis[u][i]=\sum_{v\in son(u)}dis[v][i-1]+(siz[u][i]-siz[v][i-1])*(val[v][i-1]+siz[v][i-1]*w(u,v))
$$

（上面的公式在代码中为了方便并不是如此一模一样实现）

$$
siz[u][i]=[i==0]+\sum_{v\in son(n)}siz[v][i-1]
$$

但是对于 $val[u]$ 的转移就出了问题，因为 $val[u]$ 的值和 $u$ 这个点有关，也就是说从重儿子转移过来的还要加上一个值（还和 $siz[maxson(u)][i]$ 有关），不能直接继承，而暴力再枚举一遍重儿子的深度再加显然复杂度错误。

以下与出题人思路不同。

但是还是可以优化的，我们可以再建一个 $tag[u]$ 数组，即懒标记优化，每次 $u$ 节点合并前，因为先继承了重儿子的 $val[u]$ 数组，我们需要在 $tag[u][1]$ 加上一个 $w(u,maxson(u))$，当要访问 $val[u][i]$ 的时候，我们要先访问懒标记，更新并下传，因为下穿懒标记在更新 $val[u][i]$ 和 $siz[u][i]$ 前，所以不会访问到 $dis[u][i]$，所以加值延迟不会影响最终大小。



## 代码

感觉这样口胡还是有点难懂QwQ。

目前除出题人外的最优解，（~~rk1是数据改之前交的~~）。

```cpp
int a, b, mx[N + 5],
    son[N + 5][2];
LL op[N * 8 + 5], *tag[N + 5], ans[N + 5], *dis[N + 5], *val[N + 5], *tmp = op, *siz[N + 5];
vector<pii> st[N + 5], ask[N + 5];

void ins(int n, int len) {
    val[n] = tmp;
    tmp += len + 1;
    dis[n] = tmp;
    tmp += len + 1;
    siz[n] = tmp;
    tmp += len + 1;
    tag[n] = tmp;
    tmp += len + 1;
}
void add(int n, int i) {
    (tag[n][i + 1] += tag[n][i]) %= mod;
    (val[n][i] += tag[n][i] * siz[n][i] % mod) %= mod;
    tag[n][i] = 0;
}
void dfs(int n, int fa) {
    mx[n] = 1;
    rep(i, 0, siz(st[n]) - 1) {
        int v = st[n][i].fi;
        if (v == fa) continue;
        dfs(v, n);
        if (mx[v] > mx[son[n][0]]) son[n][0] = v, son[n][1] = st[n][i].se;
    }
    mx[n] = mx[son[n][0]] + 1;
}
void Dfs(int n, int fa) {
    if (son[n][0]) {
        val[son[n][0]] = val[n] + 1;
        dis[son[n][0]] = dis[n] + 1;
        siz[son[n][0]] = siz[n] + 1;
        tag[son[n][0]] = tag[n] + 1;
        Dfs(son[n][0], n);
    }
    siz[n][0] = 1;
    tag[n][1] = son[n][1];
    rep(i, 0, siz(st[n]) - 1) {
        int v = st[n][i].fi, p = st[n][i].se;
        if (v == fa || v == son[n][0]) continue;
        ins(v, mx[v]);
        Dfs(v, n);
        rep(j, 1, mx[v]) {
            if (j != mx[v]) add(v, j);
            add(n, j);
            (dis[n][j] += val[n][j] * siz[v][j - 1] % mod +
                          (val[v][j - 1] + p * siz[v][j - 1] % mod) *
                          siz[n][j] % mod + dis[v][j - 1]) %= mod;
            (val[n][j] += val[v][j - 1] + p * siz[v][j - 1] % mod) %= mod;
            (siz[n][j] += siz[v][j - 1]) %= mod;
        }
    }
    rep(i, 0, siz(ask[n]) - 1) {
        int x = ask[n][i].fi;
        ans[ask[n][i].se] = dis[n][x];
    }
}

signed main() {
    // freopen("in1.in", "r", stdin);
    // freopen("out.out", "w", stdout);
    a = read();
    b = read();
    int x, y, z;
    rep(i, 1, a - 1) {
        x = read();
        y = read();
        z = read();
        st[x].PB(MP(y, z));
        st[y].PB(MP(x, z));
    }
    dfs(1, 0);
    rep(i, 1, b) {
        x = read();
        y = read();
        if (y <= mx[x] - 1)
            ask[x].PB(MP(y, i));
    }
    ins(1, mx[1]);
    Dfs(1, 0);
    rep(i, 1, b) printf("%lld\n", ans[i]);
    return 0;
}
```



---

## 作者：igAC (赞：2)

# $\text{Description}$

学到了 $O(n)$ 空间线段树合并，遂记之。

[link](https://www.luogu.com.cn/problem/P7581)

简要题意：

给定一棵以 $1$ 为根的带权树，记 $dep_u$ 表示 $u$ 节点的深度，有 $m$ 次询问，每次询问给定 $u,k$，问在 $u$ 的子树中深度为 $dep_u+k$ 的节点的两两距离和。

# $\text{Solution}$

一种奇怪的线段树合并做法。

我们给每个节点都开一棵线段树，设当前节点为 $u$，对于位置 $i$ 记录以下信息：

- $cnt_i$ 表示有多少深度为 $i$ 的节点。

- $sum_i$ 表示深度为 $i$ 的点的 $\sum_v dis(u,v)$。

- $ans_i$ 表示答案。

设 $u,v$ 为 $x$ 的两棵子树，对于每一种深度 $i$，$x$ 节点的 $cnt_i$ 和 $sum_i$ 合并后变化是显然的，而 $ans_i$ 的变化为：

$$
\begin{aligned}

ans_{x,i}&=ans_{u,i}+ans_{v,i}+\sum_{u'\in \text{subtree} _ u|dep_{u'}=i}\sum_{v'\in \text{subtree} _ v|dep_{v'}=i} dis(u',v')\\
&=ans_{u,i}+ans_{v,i}+\sum_{u'\in \text{subtree} _ u|dep_{u'}=i}\sum_{v'\in \text{subtree} _ v|dep_{v'}=i}(dis(u',x)+dis(v',x))\\
&=ans_{u,i}+ans_{v,i}+sum_{u,i} \times cnt_{v,i} + sum_{v,i} \times cnt_{u,i}

\end{aligned}
$$

合并的过程可以用线段树合并维护，$sum_i$ 需要动态维护，而我们知道 $u \to fa_u$ 这一步所有 $u$ 子树中的点的 $dis$ 都增加了 $dis_{u,fa_u}$ 区间加维护即可。

综上我们的做法已经明确了，但是空间复杂度似乎不允许我们这么做，这时候可以用到 [$O(n)$ 空间复杂度线段树合并 orz](https://www.luogu.com/article/cgu2m3b5)，这样这个做法就没有问题了。

时间复杂度 $O(n \log n)$，**空间复杂度 $O(n)$**。

# $\text{Code}$

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ls(p) node[p].ls
#define rs(p) node[p].rs
#define N 1000005
#define Mod 1000000007
using namespace std;
int read(){
	int x=0,f=1,ch=getchar();
	for(;!isdigit(ch);ch=getchar()) f=(ch=='-')?-1:1;
	for(;isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch^48);
	return x*f;
}
int add(int x,int y){return x+y>=Mod?x+y-Mod:x+y;}
void Add(int &x,int y){x=add(x,y);}
int n,m,head[N],tot,rt[N],idx,deep[N],ans[N],stk[N<<1],top;
int Size[N],son[N],pre[N];
struct Edge{int to,nxt,val;}e[N<<1];
struct Query{int k,id;};
vector<Query>vec[N];
void add_edge(int x,int y,int z){
	e[++tot].to=y;
	e[tot].val=z;
	e[tot].nxt=head[x];
	head[x]=tot;
}
struct Segment{
	int ls,rs;
	int sum,cnt,ans;
	int tag;
}node[N<<1];//实测开两倍够用，考试的时候怕 RE 可以多开一些
int New(){return top?stk[top--]:++idx;}
void spread(int p){
	if(node[p].tag){
		if(ls(p)){
			Add(node[ls(p)].sum,((ll)node[ls(p)].cnt*node[p].tag)%Mod);
			Add(node[ls(p)].tag,node[p].tag);
		}
		if(rs(p)){
			Add(node[rs(p)].sum,((ll)node[rs(p)].cnt*node[p].tag)%Mod);
			Add(node[rs(p)].tag,node[p].tag);
		}
		node[p].tag=0;
	}
}
void modily(int &p,int l,int r,int x,int d){
	if(!p) p=New();
	Add(node[p].sum,d),Add(node[p].cnt,1);
	if(l==r) return;
	spread(p);
	int mid=(l+r)>>1;
	if(x<=mid) modily(ls(p),l,mid,x,d);
	else modily(rs(p),mid+1,r,x,d);
}
void change(int p,int l,int r,int ql,int qr,int d){
	if(!p) return;
	if(ql<=l && r<=qr){
		Add(node[p].sum,((ll)node[p].cnt*d)%Mod);
		Add(node[p].tag,d);
		return;
	}
	spread(p);
	int mid=(l+r)>>1;
	if(ql<=mid) change(ls(p),l,mid,ql,qr,d);
	if(qr>mid) change(rs(p),mid+1,r,ql,qr,d);
}
int query(int p,int l,int r,int x){
	if(!p) return 0;
	if(l==r) return node[p].ans;
	spread(p);
	int mid=(l+r)>>1;
	if(x<=mid) return query(ls(p),l,mid,x);
	else return query(rs(p),mid+1,r,x);
}
int merge(int x,int y,int l,int r){
	if(!x || !y) return x+y;
	if(l==r){
		Add(node[x].ans,node[y].ans);
		Add(node[x].ans,((ll)node[x].sum*node[y].cnt)%Mod);
		Add(node[x].ans,((ll)node[y].sum*node[x].cnt)%Mod);
		Add(node[x].sum,node[y].sum);
		Add(node[x].cnt,node[y].cnt);
		node[y]=(Segment){0,0,0,0,0,0},stk[++top]=y;
		return x;
	}
	int mid=(l+r)>>1;
	spread(x),spread(y);
	ls(x)=merge(ls(x),ls(y),l,mid);
	rs(x)=merge(rs(x),rs(y),mid+1,r);
	node[y]=(Segment){0,0,0,0,0,0},stk[++top]=y;
	return x;
}
void dfs1(int x,int f){
	deep[x]=deep[f]+1,Size[x]=1;
	for(int i=head[x];i;i=e[i].nxt){
		int y=e[i].to;
		if(y==f) continue;
		dfs1(y,x),pre[y]=e[i].val;
		Size[x]+=Size[y];
		if(!son[x] || Size[y]>Size[son[x]]) son[x]=y;
	}
}
void dfs2(int x,int f){
	if(son[x]){
		dfs2(son[x],x);
		change(rt[son[x]],1,n,1,n,pre[son[x]]);
		rt[x]=merge(rt[x],rt[son[x]],1,n);
		for(int i=head[x];i;i=e[i].nxt){
			int y=e[i].to;
			if(y==f || y==son[x]) continue;
			dfs2(y,x);
			change(rt[y],1,n,1,n,pre[y]);
			rt[x]=merge(rt[x],rt[y],1,n);
		}
	}
	modily(rt[x],1,n,deep[x],0);
	for(auto [k,id]:vec[x]) if(deep[x]+k<=n) ans[id]=query(rt[x],1,n,deep[x]+k);
}
int main(){
	n=read(),m=read();
	for(int i=1;i<n;++i){
		int x=read(),y=read(),z=read();
		add_edge(x,y,z);
		add_edge(y,x,z);
	}
	for(int i=1;i<=m;++i){
		int x=read(),k=read();
		vec[x].push_back((Query){k,i});
	}
	dfs1(1,0),dfs2(1,0);
	for(int i=1;i<=m;++i) printf("%d\n",ans[i]);
	return 0;
}
```

---

## 作者：BigJoker (赞：1)

### 50 pts

考虑 $n\le 1000$ 的数据。

设 $f_{u,k}$ 表示子树 $u$ 中第 $k$ 层之间两两距离之和。

设 $g_{u,k}$ 表示子树 $u$ 中第 $k$ 层有多少个节点。

设 $h_{u,k}$ 表示子树 $u$ 中第 $k$ 层的所有点到 $u$ 的距离之和。

首先考虑转移 $g$，$g$ 比较好转移，直接从子树中将 $k-1$，求和即可：

$$g_{u,k}\gets \sum_{v\in son_u}g_{v,k-1}$$

初始 $g_{u,0}\gets 1$，转移即可，接下来考虑 $h$，$h$ 可以考虑枚举每一个子树，然后对 $(u,v)$ 这条边所对的权值乘上个数再加上本来到达儿子的贡献：

$$h_{u,k}\gets \sum_{v\in son_u} h_{v,k-1}
+w(u,v)\times g_{v,k-1}$$

最后考虑转移 $f$，实际上 $f$ 是两两子树之间互相到达，以及子树内部互相到达，所以转移为：

$$f_{u,k}\gets \sum_{v\in son_u}f_{v,k-1}+h_{v,k-1}\times (g_{u,k}-g_{v-1,k})+w(u,v)\times g_{v-1,k}\times (g_{u,k}-g_{v-1,k})$$

最后对于每组询问，直接输出 $f_{u,k}$ 即可。

```cpp
#include<bits/stdc++.h>
#define mem(a,x) memset(a,x,sizeof(a))
#define re register
#define il inline
using namespace std;
typedef pair<int,int>PII;
const int N=1e3+5;
const int mod=1e9+7;
int n,m,f[N][N],g[N][N],h[N][N];
vector<PII>G[N];
il void dp(int u,int fa){
	g[u][0]=1;
	for(auto v:G[u]) 
		if(v.first!=fa) dp(v.first,u);
	for(re int k=1;k<=1000;k++)
		for(auto v:G[u])
			if(v.first!=fa) g[u][k]+=g[v.first][k-1],h[u][k]=((h[u][k]+h[v.first][k-1])%mod+1ll*v.second*g[v.first][k-1]%mod)%mod;
	for(re int k=1;k<=1000;k++){
		int sg=g[u][k];
		for(auto v:G[u])
			if(v.first!=fa){
//				if(u==1 && k==2){
//					cout<<v.first<<'\n';
//				}
				f[u][k]=((((f[u][k]+1ll*h[v.first][k-1]*(sg-g[v.first][k-1])%mod)%mod)+1ll*v.second*g[v.first][k-1]%mod*(sg-g[v.first][k-1])%mod)+f[v.first][k-1])%mod;	
			}
	}
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(re int i=1,u,v,w;i<n;i++){
		cin>>u>>v>>w;
		G[u].push_back(PII(v,w)),G[v].push_back(PII(u,w));
	}
	dp(1,0);
//	cout<<h[3][1]*(g[1][2]-g[3][1])+3*g[3][1]*(g[1][2]-g[3][1])+f[3][1]<<'\n';
	while(m--){
		int u,k;
		cin>>u>>k;
		cout<<f[u][k]<<'\n';
	}
	return 0;
}
```

### 80 pts

考虑线段树合并，线段树维护的是当前子树内不同深度的点到根节点的距离和以及它们的个数。

考虑如何合并，假设当前正在合并 $x$ 的子树，假设当前已经合并完成的子树为 $u$，即将合并进去的子树为 $v$，考虑它的贡献是什么？实际上等同于从 $u$ 中选择一个点，$v$ 中选择一个点，然后统计它们的距离，可以表示为：

$$\sum_{i\in son_u}\sum_{j\in son_v}dis_i+dis_j-2\times dis_x$$

很显然可以优化，将后面定值求出来，然后求和乘上对方的个数即可。

```cpp
#include<bits/stdc++.h>
#define mem(a,x) memset(a,x,sizeof(a))
#define re register
#define il inline
using namespace std;
typedef pair<int,int>PII;
const int N=1e6+5;
const int mod=1e9+7;
int n,m;
int ans[N],dep[N],dis[N],limit,idx;
int rt[N],ls[N*20],rs[N*20],val[N*20],sum[N*20],sz[N*20];
vector<PII>G[N],que[N];
//il void pushup(int p){
//	sz[p]=sz[ls[p]]+sz[rs[p]];
//}
il void upd(int &p,int l,int r,int x,int v){
	if(!p) p=++idx;
	if(l==r){
		sum[p]=v,sz[p]++;
		return ;
	}
	int mid=l+r>>1;
	if(x<=mid) upd(ls[p],l,mid,x,v);
	else upd(rs[p],mid+1,r,x,v);
//	pushup(p);
}
il int merge(int u,int v,int l,int r,int x){
	if(!u || !v) return u+v;
	if(l==r){
		val[u]=((((((val[u]+val[v])%mod+1ll*sz[u]*sum[v]%mod)%mod+1ll*sz[v]*sum[u]%mod)%mod)-2ll*sz[u]*sz[v]%mod*dis[x]%mod)%mod+mod)%mod;
		sz[u]+=sz[v];
		sum[u]=(sum[u]+sum[v])%mod;
		return u;
	}
	int mid=l+r>>1;
	ls[u]=merge(ls[u],ls[v],l,mid,x),rs[u]=merge(rs[u],rs[v],mid+1,r,x);
	return u;
}
il int query(int p,int l,int r,int k){
	if(!p) return 0;
	if(l==r) return val[p];
	int mid=l+r>>1;
	if(k<=mid) return query(ls[p],l,mid,k);
	return query(rs[p],mid+1,r,k);
}
il int S(int p,int l,int r,int k){
	if(!p) return 0;
	if(l==r) return val[p];
	int mid=l+r>>1;
	if(k<=mid) return S(ls[p],l,mid,k);
	return S(rs[p],mid+1,r,k);
}
il void dfs(int u,int fa){
	dep[u]=dep[fa]+1,limit=max(limit,dep[u]);
	for(auto v:G[u])
		if(v.first!=fa) dis[v.first]=(dis[u]+v.second)%mod,dfs(v.first,u);
}
il void dp(int u,int fa){
	for(auto v:G[u])
		if(v.first!=fa) dp(v.first,u),rt[u]=merge(rt[u],rt[v.first],1,limit,u);
	for(auto x:que[u])
		if(dep[u]+x.second<=limit) ans[x.first]=query(rt[u],1,limit,dep[u]+x.second);
		else ans[x.first]=0;
//	cout<<'x'<<u<<' '<<S(rt[u],1,limit,3)<<'\n';
	upd(rt[u],1,limit,dep[u],dis[u]);
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(re int i=1,u,v,w;i<n;i++){
		cin>>u>>v>>w;
		G[u].push_back(PII(v,w)),G[v].push_back(PII(u,w));
	}
	for(re int i=1;i<=m;i++){
		int x,k;
		cin>>x>>k;
		que[x].push_back(PII(i,k));
	}
	dfs(1,0),dp(1,0);
//	cout<<limit<<'\n';
	for(re int i=1;i<=m;i++)
		cout<<ans[i]<<'\n';
	return 0;
}
/*
5 1
1 2 2
1 3 1
2 4 1
2 5 2
2 1

10 1
1 2 1
1 3 3
2 4 2
2 5 2
3 6 3
3 7 1
5 8 2
6 9 1
6 10 3
1 2
*/
```

### 100pts

发现会 MLE，因为我们在线段树合并的时候会开太多的点，删除的点没用后就造成了空间的浪费，考虑将被删除的点用栈存下来，然后新开线段树节点的时候如果能用被删除的点就用删除的点，否则就新开一个点，这样就可以大大节约空间，不过这个做法如果精心构造还是会被卡，但是本题没有被卡，线段树合并实现线性空间还需要其它做法。

```cpp
#include<bits/stdc++.h>
#define mem(a,x) memset(a,x,sizeof(a))
#define re register
#define il inline
using namespace std;
typedef pair<int,int>PII;
const int N=1e6+5;
const int mod=1e9+7;
int n,m;
int ans[N],dep[N],mdep[N],dis[N],limit,idx;
int rt[N],ls[N],rs[N],val[N],sum[N],sz[N],trash[N],top;
vector<PII>G[N],que[N];
il int add(){
	if(!top) return ++idx;
	return trash[top--];
}
il void del(int x){
	ls[x]=rs[x]=sum[x]=val[x]=sz[x]=0,trash[++top]=x;
}
il void upd(int &p,int l,int r,int x,int v){
	if(!p) p=add();
	sz[p]++;
	if(l==r){
		sum[p]=v;
		return ;
	}
	int mid=l+r>>1;
	if(x<=mid) upd(ls[p],l,mid,x,v);
	else upd(rs[p],mid+1,r,x,v);
}
il int merge(int u,int v,int l,int r,int x){
	if(!u || !v) return u+v;
	if(l==r){
		val[u]=((((((val[u]+val[v])%mod+1ll*sz[u]*sum[v]%mod)%mod+1ll*sz[v]*sum[u]%mod)%mod)-2ll*sz[u]*sz[v]%mod*dis[x]%mod)%mod+mod)%mod,sz[u]+=sz[v],sum[u]=(sum[u]+sum[v])%mod,del(v);
		return u;
	}
	int mid=l+r>>1;
	ls[u]=merge(ls[u],ls[v],l,mid,x),rs[u]=merge(rs[u],rs[v],mid+1,r,x),del(v);
	return u;
}
il int query(int p,int l,int r,int k){
	if(!p || !sz[p]) return 0;
	if(l==r) return val[p];
	int mid=l+r>>1;
	if(k<=mid) return query(ls[p],l,mid,k);
	return query(rs[p],mid+1,r,k);
}
il void dfs(int u,int fa){
	mdep[u]=dep[u]=dep[fa]+1,limit=max(limit,dep[u]);
	for(auto v:G[u])
		if(v.first!=fa) dis[v.first]=(dis[u]+v.second)%mod,dfs(v.first,u),mdep[u]=max(mdep[u],mdep[v.first]);
}
il void dp(int u,int fa){
	for(auto v:G[u])
		if(v.first!=fa) dp(v.first,u),rt[u]=merge(rt[u],rt[v.first],1,limit,u);
	for(auto x:que[u])
		if(dep[u]+x.second<=limit && mdep[u]>=x.second+dep[u]) ans[x.first]=query(rt[u],1,limit,dep[u]+x.second);
		else ans[x.first]=0;
	upd(rt[u],1,limit,dep[u],dis[u]);
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(re int i=1,u,v,w;i<n;i++){
		cin>>u>>v>>w;
		G[u].push_back(PII(v,w)),G[v].push_back(PII(u,w));
	}
	for(re int i=1;i<=m;i++){
		int x,k;
		cin>>x>>k;
		que[x].push_back(PII(i,k));
	}
	dfs(1,0),dp(1,0);
	for(re int i=1;i<=m;i++)
		cout<<ans[i]<<'\n';
	return 0;
}
```

---

## 作者：yizhiming (赞：1)

瞄了眼出题人的题解，线段树合并被卡成 MLE 了。

但是我又卡回去了。

## 题目链接

[$Link$](https://www.luogu.com.cn/problem/P7581)

## 题目大意

给定一棵树，多次查询一个节点 $u$ 的所有子节点中，所有距离 $u$ 的大小为 $k$ 的节点的两两距离和。

## 题目分析

像这种子树答案仅在自身有用，查询完便无用的题目，我们可以直接用线段树合并维护答案，并在遍历树的时候将子树的答案累计上去。

所以，我们直接用线段树合并，下标为对应节点的深度维护即可。

我们现在考虑如何将一棵子树的贡献合并到根节点上。感觉这个式子还是很好推的，先设当前节点为 $u$，当前要合并的子树为 $v$。

那么 $v$ 的子树内的距离和是不会有影响的，同理之前已经合并的也不会。这部分的贡献直接累加上即可，现在的问题在于如何统计跨子树的贡献。

我们设 $dis_i$ 表示 $i$ 到根节点的路径和，设当前已经被统计贡献的子树集合为 $S$，$v$ 子树集合为 $T$。

那么跨子树的贡献即为 $\sum\limits_{x\in S}\sum\limits_{y\in T} dis_x+dis_y-2\times dis_u$，注意到 $2\times dis_u$ 是个定值，所以把它取出来，减去的次数是这两个集合的大小之积。

而对于每一个 $dis_x$ 都被计算了 $T$ 集合大小次，$dis_y$ 计算了 $S$ 集合大小次，所以合并的贡献就被转换成了如下的式子。

$ans_u = ans_S+ans_T+(\sum\limits_{x\in S}dis_x)\times |T|+(\sum\limits_{y\in T}dis_y)\times |S|-2\times dis_u\times |S||T|$。

这个式子我们直接维护 $S$ 和 $T$ 的大小、距离和以及答案即可。

查询的话对于每个节点开一个 vector，直接扫一遍，然后在线段树上查询答案即可。

## 代码细节

其实这里才是这篇博客最特殊的地方，出题人把空间卡掉了，我们需要对线段树合并进行优化。

第一个优化，废点回收，将不用的点记录下来，循环使用，理论上空间已经被降到 $O(n)$ 了，但是可以被特殊构造卡掉。

第二个优化，先考虑我们平时的线段树合并怎么写的？

```cpp
build(rt[u],1,maxn,dep[u],dis[u]);
for(int i=head[u];i;i=edge[i].nxt){
	int now = edge[i].to;
	if(now==f){
		continue;
	}
	dis[now] = (dis[u]+edge[i].val)%Mod;
	dfs(now,u);
	rt[u] = merge(rt[u],rt[now],1,maxn,u);
}
```

这里有哪里可以优化呢？我们发现当前查询一定不与当前节点所在深度有关，但是我们新建版本的时候就顺手把其插入到了线段树上，虽然查询不会收到影响，但是线段树合并的过程中，就一定会多出一部分无意义的节点，你每次都要去递归，将其合并上去。

这样就导致递归次数多爆栈，而且由于是先建树再合并，在一条链上废点回收还没开始工作呢，我们就一直在新建节点了，所以会把废点回收的空间优化卡掉，事实上，经常有线段树合并的题放一条链子，专门卡这种写法。

怎么办呢？既然当前节点的贡献不影响查询，那我等一切都查完了，都合并完了，再将贡献累加进去不就好了吗，这样就保证了复杂度。

维护深度的线段树合并，我记得时间没办法卡到 $n^2$，所以时间复杂度为 $O(n\log n)$，空间如果我没想错的话，只要加上第二个优化，废点回收就是正常的空间复杂度为线性。

## Code

这回是真的代码力。

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <queue>
using namespace std;
int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int N = 1e6+10;
int Mod = 1e9+7;
struct aa{
	int nxt,to,val;
}edge[N*2];
int head[N],tote;
void add(int u,int v,int w){
	edge[++tote].nxt = head[u];edge[tote].to = v;head[u] = tote;edge[tote].val = w;
}
struct nod{
	int k,id;
}nod[N];
int ans[N],dis[N],dep[N],des[N],rt[N],n;
vector<int>vec[N];
struct bb{
	int lc,rc,siz,ans,sum;
	void clear(){
		lc=rc=siz=ans=sum=0;
	}
}node[N*4];
int st[N*30],top,tot;
int newnode(){
	if(top){
		node[st[top]].clear();
		return st[top--];
	}else{
		return ++tot;
	}
}
void pushup(int u){
	node[u].siz = node[node[u].lc].siz+node[node[u].rc].siz;
}
void build(int &u,int l,int r,int x,int y){
	if(!u){
		u = newnode();
	}
	node[u].siz++;
	if(l==r){
		node[u].siz = 1;node[u].sum = y%Mod;
		return;
	}
	int mid = (l+r)/2;
	if(x<=mid){
		build(node[u].lc,l,mid,x,y);
	}else{
		build(node[u].rc,mid+1,r,x,y);
	}
}
int merge(int u,int v,int l,int r,int x){
	if(!u||!v){
		return u+v;
	}
	if(l==r){
		long long res = ((1ll*node[u].ans+1ll*node[v].ans%Mod)%Mod+(1ll*node[v].siz%Mod*(1ll*node[u].sum%Mod))%Mod+(1ll*node[u].siz%Mod*(1ll*node[v].sum%Mod))%Mod-(1ll*node[u].siz*node[v].siz%Mod*(2ll*dis[x]%Mod))%Mod+Mod)%Mod;
		node[u].ans = int(res);
		node[u].sum = (node[u].sum+node[v].sum)%Mod;
		node[u].siz = (node[u].siz+node[v].siz)%Mod;
		st[++top] = v;
		return u;
	}
	int mid = (l+r)/2;
	node[u].lc = merge(node[u].lc,node[v].lc,l,mid,x);
	node[u].rc = merge(node[u].rc,node[v].rc,mid+1,r,x);
	st[++top] = v;
	pushup(u);
	return u;
}
int query(int u,int l,int r,int pla){
	if(!u||!node[u].siz){
		return 0;
	} 
	if(l==r){
		return node[u].ans;
	}
	int mid = (l+r)/2;
	if(pla<=mid){
		return query(node[u].lc,l,mid,pla);
	}else{
		return query(node[u].rc,mid+1,r,pla);
	}
}
int maxn = 0;
void dfs(int u,int f){
	for(int i=head[u];i;i=edge[i].nxt){
		int now = edge[i].to;
		if(now==f){
			continue;
		}
		dis[now] = (dis[u]+edge[i].val)%Mod;
		dfs(now,u);
		rt[u] = merge(rt[u],rt[now],1,maxn,u);
	}
	int siz = vec[u].size();
	for(int i=0;i<siz;i++){
		int k = nod[vec[u][i]].k;
		if(dep[u]+k>des[u]){
			ans[nod[vec[u][i]].id] = 0;
		}else{
			ans[nod[vec[u][i]].id] = query(rt[u],1,maxn,dep[u]+k);
		}
	}
	build(rt[u],1,maxn,dep[u],dis[u]);
} 
void fc(int u,int f){
	dep[u] = dep[f]+1;
	des[u] = dep[u];
	maxn = max(maxn,dep[u]);
	for(int i=head[u];i;i=edge[i].nxt){
		int now = edge[i].to;
		if(now==f){
			continue;
		}
		fc(now,u);
		des[u] = max(des[u],des[now]);
	}
}
int main(){
	int m,u,v,w;
	n = read();m = read();
	for(int i=1;i<n;i++){
		u = read();v = read();w = read();
		add(u,v,w);add(v,u,w);
	}
	for(int i=1;i<=m;i++){
		u = read();v = read();
		nod[i].id = i;nod[i].k = v;
		vec[u].push_back(i);
	}
	fc(1,0);
	dfs(1,0);
	for(int i=1;i<=m;i++){
		cout<<ans[i]<<"\n";
	}
	return 0;
}
```
## 更新

出题人跟我说这道题线段树合并我过了是因为没卡，然后告诉我怎么做到真正意义上的线性线段树合并。

简单来说就是先跑一遍重剖，我们每次合并的时候优先合并重儿子即可。

复杂度也不会变，只是优化到不被卡了。放一下这部分的[参考文章](https://www.luogu.com.cn/blog/DPair2005/post-on-kong-jian-xian-duan-shu-ge-bing-post)。

数学式子要是哪里写错了，那就请大家忽视吧，主要是想宣传一下线段树合并做法。

---

## 作者：Tomle (赞：0)

考虑到我们可以写出朴素的二维 dp，其中一维与深度有关，自然想到长剖优化 dp。

设 $f_{u,i},g_{u,i},h_{u,i}$ 分别表示 $u$ 子树内有多少个深度为 $i$ 的点，深度为 $i$ 的点到根的距离之和，以及 $u$ 子树内深度为 $i$ 的点两两距离之和。转移是容易的：

$$
h_{u,i}\gets h_{v,i}+f_{u,i}(g_{v,i}-dis_uf_{v,i})+f_{v,i}(g_{u,i}-dis_{u}f_{u,i})\\
g_{u,i}\gets g_{v,i}\\
f_{u,i}\gets f_{v,i}
$$

做完了。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1000005, mod = 1e9 + 7;
typedef pair <int, int> pii;

int n, m, k, u, v, w, d[N], md[N], ls[N], di[N], *f[N], *g[N], *h[N];
vector <pii> T[N], Q[N];
int ans[N];
#define eb emplace_back

namespace Pool {
    int O[N * 20], *cur = O;
    int* $(int n) { auto R = cur; cur += n; return R; }
    int* $(int l, int r) { return $(r - l + 1) - l; }
} using Pool::$;

inline void rd(int &a, int ch = 0) {
    while (!isdigit(ch = getchar()));
    for (a = 0; isdigit(ch); ch = getchar()) a = (a << 3) + (a << 1) + (ch ^ 48);
}
void wrt(int x) {
    if (x > 9) wrt(x / 10);
    putchar(x % 10 ^ 48);
}
void dfs1(int u, int fa) {
    md[u] = d[u] = d[fa] + 1;
    for (auto [v, w] : T[u]) {
        if (v == fa) continue;
        di[v] = (di[u] + w) % mod;
        dfs1(v, u);
        md[u] = max(md[u], md[v]);
        if (md[v] > md[ls[u]]) ls[u] = v;
    }
}
void dfs2(int u, int fa) {
    if (ls[u]) f[ls[u]] = f[u], g[ls[u]] = g[u], h[ls[u]] = h[u], dfs2(ls[u], u);
    f[u][d[u]] = 1, g[u][d[u]] = di[u];
    for (auto [v, w] : T[u]) {
        if (v == fa || v == ls[u]) continue;
        f[v] = $(d[v], md[v]);
        g[v] = $(d[v], md[v]);
        h[v] = $(d[v], md[v]);
        dfs2(v, u);
        for (int i = d[v]; i <= md[v]; i++) {
            h[u][i] = (h[u][i] + h[v][i]
                + 1ll * f[u][i] * (g[v][i] - 1ll * f[v][i] * di[u] % mod + mod)
                + 1ll * f[v][i] * (g[u][i] - 1ll * f[u][i] * di[u] % mod + mod)) % mod;
            g[u][i] = (g[u][i] + g[v][i]) % mod;
            f[u][i] += f[v][i];
        }
    }
    for (auto [dp, id] : Q[u]) {
        if (dp <= md[u]) ans[id] = h[u][dp];
    }
}
int main() {
    rd(n), rd(m);
    for (int i = 1; i < n; i++) {
        rd(u), rd(v), rd(w);
        T[u].eb(v, w), T[v].eb(u, w);
    }
    dfs1(1, 0);
    for (int i = 1; i <= m; i++) {
        rd(u), rd(k);
        Q[u].eb(d[u] + k, i);
    }
    f[1] = $(1, md[1]), g[1] = $(1, md[1]), h[1] = $(1, md[1]);
    dfs2(1, 0);
    for (int i = 1; i <= m; i++) wrt(ans[i]), putchar(10);
}
```

---

## 作者：lfxxx (赞：0)

令 $S_{u,i}$ 表示 $u$ 的 $i - son$ 集合，再令 $dp_{u,i},sum_{u,i},sz_{u,i}$ 分别表示 $\sum_{j,k \in S_{u,i}} dis(j,k),\sum_{j \in S_{u,i}} dis(u,i),|S_{u,i}|$。

然后因为 $i$ 小于等于 $u$ 子树内最长链长度，所以可以长链剖分优化，具体而言，每次把轻儿子 $dp_{v,i}$ 合并到 $dp_{u,i+1}$ 上时可以直接暴力，但是继承重儿子的 dp 数组时需要维护一个形如将每个 $sum_{u,i}$ 加上 $sz_{u,i} \times w$ 的操作，于是对于每个点维护一个懒标记 $tag_u$ 表示真实的 $sum_{u,i}$ 为 $sum_{u,i} + tag_u \times sz_{u,i}$ 即可，注意继承重儿子的 $tag$ 以及轻儿子的 $sz_{v,i}$ 对 $tag_u$ 的贡献要删掉。

在链顶分配空间可以做到小常数 $O(n)$ 空间。

转移式见代码，代码中数组下标是反着排的。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e6+114;
const int mod = 1e9+7;
vector< pair<int,int> > E[maxn];
int n,q,maxdep[maxn];
int son[maxn],cost[maxn];
int id[maxn];
int tot;
int dp[maxn],sum[maxn],sz[maxn];
void dfs(int u,int fa){
    for(pair<int,int> nxt:E[u]){
        int v=nxt.first,w=nxt.second;
        if(v!=fa){
            dfs(v,u);
            maxdep[u]=max(maxdep[u],maxdep[v]+1);
            if(maxdep[v]>=maxdep[son[u]]) son[u]=v,cost[u]=w;
        }
    }
}
int val(int u,int i){return (1ll*sum[i+id[u]]+1ll*cost[u]*sz[i+id[u]])%mod;}
int answer[maxn];
vector< pair<int,int> >ask[maxn];
void DP(int u,int fa){
    if(son[u]!=0){
        id[son[u]]=id[u];
        DP(son[u],u);
        id[u]=id[son[u]];
        cost[u]=(cost[son[u]]+cost[u])%mod;
    }
    dp[id[u]+maxdep[u]]=0;
    sum[id[u]+maxdep[u]]=(mod-cost[u])%mod;
    sz[id[u]+maxdep[u]]=1;
    for(pair<int,int> nxt:E[u]){
        int v=nxt.first,w=nxt.second;
        if(v!=fa&&v!=son[u]){
            id[v]=tot;
            tot+=(maxdep[v]+1);
            DP(v,u);
            int c=maxdep[u]-maxdep[v]-1;
            for(int i=0;i<=maxdep[v];i++){
                dp[id[u]+i+c]=(1ll*dp[id[u]+i+c]+dp[id[v]+i]+1ll*sz[id[u]+i+c]*((1ll*val(v,i)+1ll*sz[id[v]+i]*w%mod)%mod)%mod+1ll*sz[id[v]+i]*val(u,i+c)%mod)%mod;
                sz[id[u]+i+c]=sz[id[u]+i+c]+sz[id[v]+i];
                sum[id[u]+i+c]=(1ll*sum[id[u]+i+c]+mod-(1ll*cost[u]*sz[id[v]+i]%mod))%mod;
                sum[id[u]+i+c]=(1ll*sum[id[u]+i+c]+val(v,i)+1ll*sz[id[v]+i]*w%mod)%mod;
            }
        }
    }
    E[u].clear();
    for(pair<int,int> query:ask[u]){
        if(query.first<=maxdep[u]) answer[query.second]=dp[id[u]+maxdep[u]-query.first];
    }
    ask[u].clear();
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n>>q;
    for(int i=1;i<n;i++){
        int u,v,w;
        cin>>u>>v>>w;
        E[u].push_back(make_pair(v,w));
        E[v].push_back(make_pair(u,w));
    }
    for(int i=1;i<=q;i++){
        int u,k;
        cin>>u>>k;
        if(1<=u&&u<=n) ask[u].push_back(make_pair(k,i));
    }
    dfs(1,0);
    tot+=(maxdep[1]+1);
    DP(1,0);   
    for(int i=1;i<=q;i++) cout<<answer[i]<<'\n';
    return 0;
}
```

---

## 作者：daniEl_lElE (赞：0)

长链剖分板子之一。

首先考虑 $dp_{i,j,0/1/2}$ 表示 $i$ 节点的子树中，深度为 $j$ 的所有点的总数、到根边权总和、两两之间的距离。

假设 $i$ 要合并一个子树 $v$，其间边权为 $w$，则：

$$dp_{i,j,0}+dp_{v,j,0}\to dp'_{i,j,0}$$
$$dp_{i,j,1}+dp_{v,j,1}\to dp'_{i,j,1}$$
$$dp_{i,j,2}+dp_{v,j,2}+(dp_{i,j,1}-dp_{i,j,0}\times dep_i)\times dp_{v,j,0}+(dp_{v,j,1}-dp_{v,j,0}\times dep_i)\times dp_{i,j,0}\to dp'_{i,j,2}$$

这样做是 $O(n^2)$ 的。

考虑[长链剖分](https://oi-wiki.org/graph/hld/#%E9%95%BF%E9%93%BE%E5%89%96%E5%88%86)优化，每次直接继承长链过来的答案。则总复杂度变为 $O(n)$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define lowbit(i) (i&(-i))
#define mid ((l+r)>>1)
using namespace std;
const int mod=1e9+7;
struct linker{
	signed top[2000005],lk[2000005],cnt;
	pair<signed,signed> num[2000005];
	void push_back(int a,pair<int,int> b){
		cnt++;
		lk[cnt]=top[a];
		top[a]=cnt;
		num[cnt]=b;
	}
}vc,qry;
int bel[1000005],dep[1000005],vdep[1000005],ext[1000005],tot,ans[1000005];
int hson[1000005],top[1000005],tqr;
int mp1[1000005],mp2[1000005],mp3[1000005];
void dfs(int now,int fa){
	dep[now]=dep[fa]+1;
	for(int i=vc.top[now];i;i=vc.lk[i]){
		auto v=vc.num[i];
		if(v.first==fa) continue;
		vdep[v.first]=vdep[now]+v.second;
		dfs(v.first,now);
		if(ext[v.first]>ext[now]){
			ext[now]=ext[v.first];
			hson[now]=v.first;
		}
	}
	ext[now]++;
}
void dfs2(int now,int fa){
	if(!bel[now]){
		bel[now]=++tot;
		top[now]=dep[now]-tqr;
		tqr+=ext[now];
	}
	top[hson[now]]=top[now];
	bel[hson[now]]=bel[now];
	for(int i=vc.top[now];i;i=vc.lk[i]){
		auto v=vc.num[i];
		if(v.first==fa||v.first==hson[now]) continue;
		dfs2(v.first,now);
	}
	if(hson[now]) dfs2(hson[now],now);
	for(int i=vc.top[now];i;i=vc.lk[i]){
		auto v=vc.num[i];
		if(v.first==fa||v.first==hson[now]) continue;
		for(int j=dep[v.first];j<=dep[now]+ext[v.first];j++){
			(mp3[j-top[now]]+=mp3[j-top[v.first]]+(mp2[j-top[now]]+mod-mp1[j-top[now]]*vdep[now]%mod)*mp1[j-top[v.first]]+(mp2[j-top[v.first]]+mod-mp1[j-top[v.first]]*vdep[now]%mod)*mp1[j-top[now]])%=mod;
			(mp2[j-top[now]]+=mp2[j-top[v.first]])%=mod;
			(mp1[j-top[now]]+=mp1[j-top[v.first]])%=mod;
		}
	}
	mp1[dep[now]-top[now]]=1;
	mp2[dep[now]-top[now]]=vdep[now]%mod;
	for(int i=qry.top[now];i;i=qry.lk[i]){
		auto v=qry.num[i];
		if(v.first>=ext[now]) continue;
		ans[v.second]=mp3[dep[now]+v.first-top[now]];
	}
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int n,m; cin>>n>>m;
	for(int i=1;i<n;i++){
		int u,v,w; cin>>u>>v>>w;
		vc.push_back(u,make_pair(v,w));
		vc.push_back(v,make_pair(u,w));
	}
	for(int i=1;i<=m;i++){
		int u,k; cin>>u>>k;
		qry.push_back(u,make_pair(k,i));
	}
	dfs(1,0);
	dfs2(1,0);
	for(int i=1;i<=m;i++) cout<<ans[i]<<"\n";
	return 0;
}
```

---

## 作者：hegm (赞：0)

### [「RdOI R2」路径权值(distance)](https://www.luogu.com.cn/problem/P7581)

询问 $i$ 的 $k$ 级孩子的互相之间的距离和。

容易发现我们可以离线通过线段树合并求出某个点的 $k-th$ 孩子，也可以求出 $k-th$ 孩子到他的距离总和。

我们建立一棵线段树，按照**深度**作为下标。

里面有 $3$ 个变量。

$sum_{i,j}$ 存储的是 $i$ 的子树中，深度为 $j$ 的点互相到达的距离总和。

$dis_{i,j}$ 存储的是 $i$ 的子树中，深度为 $j$ 的点到 $i$ 的距离和。

$num_{i,j}$ 存储的是 $i$ 的子树中，深度为 $j$ 的点的数量。

以上只是方便表达，对于某一个值如 $num_{i,j}$，

我们是要通过线段树查询出来的。

假如我们要将 $i$ 的线段树算出来，我们就要将 ${j\in son_i}$ 全部合并上来。

假如我们现在合并到了 $j$，应该将深度为 $k$ 合并上来。

- $num$

	![](https://cdn.luogu.com.cn/upload/image_hosting/4dy601yj.png)

	假如 $i=1,j=3,k=3$ 我们合并完 $2$ 后， $num_{1,3}=2$，我们直接将 $num_{1,3}$ 加上 $num_{3,3}$ 即可。
	
- $dis$

	![](https://cdn.luogu.com.cn/upload/image_hosting/z3myugw9.png)

	我们已经合并完了 $2$ 此时 $dis_{1,3}=1+3+1+4=9$，现在我们要将 $dis_{3,3}$ 也合并上来，考虑所有在 $j$ 的子树中深度为 $k$ 的点到 $i$ 的距离和到 $j$ 的距离的差别，容易发现只是多了一条边 $w_{1,3}$，每一个这样的点都会多一次 $w_{1,3}$，而这样的点有 $num_{3,3}$ 个，所以我们的 $dis_{1,3}$ 加上 $dis_{3,3}+num_{3,3}\times w_{1,3}$.
    
- $sum$

	考虑匹配的实际意义，首先，$j$ 子树内的点的互相间的距离就是 $sum_{j,k}$，这个不用再算，需要额外计算的是不同子树之间的比如 $5\to 7$ 之间的距离。
    
    ![](https://cdn.luogu.com.cn/upload/image_hosting/az397iaq.png)
    
    而这条路径又被分为两部分，一部分是已经被合并的点到根节点的距离，一部分是未合并的点到根节点的距离。
    考虑每一个是 $j$ 的子树中且深度为 $k$ 的点 $p$。
    
    那么所有需要和 $p$ 匹配的点就是已经和 $i$ 合并的且深度为 $k$ 的点，我们可以很容易的算出绿色路径的权值，其实就是 $dis_{i,k}$ 因为每一个都要和 $p$ 匹配，而这样的 $p$ 又有 $num_{j,k}$ 个，所以 $sum_{i,k}$ 加上 $dis_{i,k}\times num_{j,k}$。
    
    现在我们考虑蓝线的贡献，这时候可以反过来思考，对于每一个已经被合并到 $i$ 且深度为 $k$ 的点 $p$，他会和 $num_{j,k}$ 个点匹配，而这些点的 $dis$ 和有恰好是 $dis_{j,k}$，这样的点 $p$ 有 $num_{i,k}$ 个，所以   $sum_{i,k}=sum_{i,k}+dis_{j,k}\times num_{i,k}$。（这里的 $dis_{j,k}$ 一定要是增加了 $w_{i,j}$ 的 $dis_{j,k}$）
    
这就是所有的合并了，但是需要注意顺序，我们要先修改 $dis$ 然后修改 $sum$，最后修改 $num$，因为 $sum$ 会用到没有合并 $j$ 的 $num_{i,k}$，和合并后的 $dis$。

处理询问对每一个点建立 `vector` 存储即可。

对于修改 $dis$，需要一个懒标记来记录。

看代码！

### $\text{CODE}$

```cpp
#include<bits/stdc++.h>
#define N 1000006
#define lc tr[now].ls
#define rc tr[now].rs
#define mod 1000000007
using namespace std;
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int n,m,ans[N],rt[N],dep[N],d;
struct fig
{
	int to,next,val;
}k[N*2];int head[N],tot;
void add(int from,int to,int val)
{
	k[++tot].to=to;
	k[tot].next=head[from];
	k[tot].val=val;
	head[from]=tot;
}
vector<pair<int,int> >v[N];
struct node
{
	int sum,num,dis;
}kl[N*4];int cwc;
struct tree
{
	int ls,rs,lz,id;
	void clear(){id=ls=rs=lz=0;}
}tr[N*8];int cnt;
queue<int> q;
int news(int l,int r)
{
	int now;
	if(q.size())now=q.front(),q.pop();
	else now=++cnt;
	tr[now].clear();
	if(l==r)tr[now].id=++cwc;
	return now;
}
void add(int &a,int b)
{
	a%=mod;b%=mod;
	a=(1ll*a+b)%mod;
}
void down(int now)
{
	if(tr[now].lz)
	{
		add(kl[tr[lc].id].dis,1ll*kl[tr[lc].id].num*tr[now].lz%mod);
		add(kl[tr[rc].id].dis,1ll*kl[tr[rc].id].num*tr[now].lz%mod);
		add(tr[rc].lz,tr[now].lz);
		add(tr[lc].lz,tr[now].lz);
		tr[now].lz=0;
	}
}
int merge(int x,int y,int l,int r,int val)
{
	if(!x)
	{
		tr[y].lz+=val;
		add(kl[tr[y].id].dis,1ll*kl[tr[y].id].num*val%mod);
		return y;
	}
	if(!y)return x;
	down(x);down(y);
	if(l==r)
	{
		add(kl[tr[y].id].dis,1ll*kl[tr[y].id].num*val%mod);
		add(kl[tr[x].id].sum,1ll*kl[tr[x].id].dis*kl[tr[y].id].num%mod);
		add(kl[tr[x].id].sum,1ll*kl[tr[x].id].num*kl[tr[y].id].dis%mod);
		add(kl[tr[x].id].sum,kl[tr[y].id].sum);
		add(kl[tr[x].id].dis,kl[tr[y].id].dis);
		add(kl[tr[x].id].num,kl[tr[y].id].num);
		q.push(y);
		return x;
	}
	int mid=(l+r)>>1;
	tr[x].ls=merge(tr[x].ls,tr[y].ls,l,mid,val);
	tr[x].rs=merge(tr[x].rs,tr[y].rs,mid+1,r,val);
	q.push(y);
	return x;
}
int que(int now,int l,int r,int x)
{
	if(!now)return 0;
	if(l==r)return kl[tr[now].id].sum;
	down(now);int mid=(l+r)>>1;
	if(mid>=x)return que(lc,l,mid,x);
	return que(rc,mid+1,r,x);
}
void add(int now,int l,int r,int x)
{
	if(l==r)
	{
		kl[tr[now].id].num++;
		return;
	}
	down(now);
	int mid=(l+r)>>1;
	if(mid>=x)
	{
		if(!lc)lc=news(l,mid);
		add(lc,l,mid,x);
	}
	else 
	{
		if(!rc)rc=news(mid+1,r);
		add(rc,mid+1,r,x);
	}
}
void pf(int now,int fa)
{
	dep[now]=dep[fa]+1;d=max(d,dep[now]);
	for(int i=head[now];i;i=k[i].next)
	{
		if(k[i].to==fa)continue;
		pf(k[i].to,now);
	}
}
void dfs(int now,int fa)
{
	rt[now]=++cnt;
	for(int i=head[now];i;i=k[i].next)
	{
		if(k[i].to==fa)continue;
		dfs(k[i].to,now);
		rt[now]=merge(rt[now],rt[k[i].to],1,d,k[i].val);
	}
	add(rt[now],1,d,dep[now]);
	for(int i=0;i<(int)v[now].size();i++)
	{
		if(v[now][i].first+dep[now]>d)continue;
		ans[v[now][i].second]=que(rt[now],1,d,v[now][i].first+dep[now]);
	}
}
int main()
{
	n=read();m=read();
	for(int i=1,u,v,w;i<n;i++)
	{
		u=read();v=read();w=read();
		add(u,v,w);add(v,u,w);
	}
	for(int i=1,u,k;i<=m;i++)
	{
		u=read();k=read();
		v[u].push_back(make_pair(k,i));
	}
	pf(1,0);
	dfs(1,0);
	for(int i=1;i<=m;i++)cout<<ans[i]<<"\n";
	return 0;
}
```

---

