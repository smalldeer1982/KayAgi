# BZOJ3569 DZY Loves Chinese II

## 题目描述

给定无向图 $G = (V, E)$，$q$ 次询问每次给定一个边集，求删除该边集后图是否连通。保证边集大小不超过 $15$。强制在线。

## 说明/提示

数据保证，$1\leq n\leq 10^5$，$1\leq m\leq 5\times 10^5$，$1\leq Q\leq 5\times 10^4$，$1\leq k\leq 15$。保证图中没有重边与自环。

## 样例 #1

### 输入

```
5 10
2 1
3 2
4 2
5 1
5 3
4 1
4 3
5 2
3 1
5 4
5
1 1
3 7 0 3
4 0 7 4 6
2 2 7
4 5 0 2 13```

### 输出

```
Connected
Connected
Connected
Connected
Disconnected```

# 题解

## 作者：CYZZ (赞：16)

## [DZY Loves Chinese II](https://www.luogu.com.cn/problem/P10778)

### Part 0

省流：从 chen_zhe 犇犇跑过来的。

声明：本题解是正向推导，所以相较于直接给构造方式来说会比较冗长，但是有助于理解。

### Part 1

首先，可以线段树分治，但是不但不能在线，而且复杂度太高。所以，我们需要找到一个非数据结构的快速处理询问的方法。

思考什么时候图会不连通，不妨设图被分为了两个连通块 $S,V-S$（其余情况一定能规约到这种），考虑如何快速判断 $S$ 与 $V-S$ 不连通。

寻找哪些边是**一定**要被割掉的，发现 $E'_S=\{(u,v)\in E\mid u\in S,v\in V-S\}$ 这个边集一定要被割掉（即切断 $S$ 与外界的联系）。

我们要想知道一个询问边集是否合法，就要知道是否存在一个 $E'$ **是询问边集的子集**。对于每个 $S$ 都记录一个 $E'$ 是不可能的，于是我们要方便地刻画这个 $E'$。

接下来有个很 wisdom 的想法，考虑**随机异或哈希**：假如我们给每条边赋一个权值 $w$，使得对于所有 $E'$ 都满足 $\bigoplus\limits_{e\in E'}w_e=0$。

如果已能解决构造边权的部分（Part 2），剩下的就是：判断是否存在一个询问边集的子集，满足这个子集的**边权异或和为 $0$**。这个问题可以轻易地用**线性基**解决。

### Part 2

问题变为：如何构造能够满足所有 $E'$ 条件的权值。

先考虑最简单的情况：$S$ 为一个点，此时 $E'$ 为这个点的所有出边。也就是说，**每个点的出边的权值异或和为 $0$**（条件 $1.$）。

然而，我们发现满足这个条件就足够了，为什么呢？

如果 $S$ 里只有两个点，设为 $x,y$，发现 $E'_S=(E'_{\{x\}} \cup E'_{\{y\}})-(E'_{\{x\}} \cap E'_{\{y\}})$。

换句话说，**把两端都在 $S$ 里的边去掉被抵消掉了**，而 xor 和刚好就能体现“抵消”的性质。（这里可能比较抽象，建议自己手玩理解）。

而推广到三个点，四个点，$n$ 个点都是一样的，同样可以由条件 $1.$ 推出。

问题变为：如何满足条件 $1.$。

这个就比较简单了：随便 dfs 跑生成树。

- 对于非树边，边权**随机**
- 对于树边，边权为**儿子节点已确定的出边的边权异或和**（这样 xor 起来为零）。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 100005
#define M 500005
#define V 65
#define ll unsigned long long
int n,m,q;
namespace GRAPH
{
    int tot=1,head[N];ll w[M];
    struct Edge{int next,to;}e[M<<1];
    void add_edge(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
    int idx,dfn[N],bk[N];mt19937_64 seed(847532);
    void dfs(int u,int from)
    {
        dfn[u]=++idx;bk[u]=1;ll sum=0;
        for(int i=head[u];i;i=e[i].next)
        {
            int v=e[i].to;if((i>>1)==from) continue;
            if(bk[v])
            {
                if(dfn[v]<dfn[u])
                    w[i>>1]=seed();
            }
            else dfs(v,i>>1);
            sum^=w[i>>1];
        }
        w[from]=sum;
    }
}using namespace GRAPH;
namespace Linear_Basis
{
    ll p[V];
    inline void Clear(){memset(p,0,sizeof p);}
    inline bool Insert(ll x)
    {
        for(int i=63;~i;i--) if(x>>i&1)
        {
            if(p[i]) x^=p[i];
            else return p[i]=x,1;
        }
        return 0;
    }
}using namespace Linear_Basis;
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        int x,y;scanf("%d%d",&x,&y);
        add_edge(x,y);add_edge(y,x);
    }
    dfs(1,0);scanf("%d",&q);
    ll lst=0;
    while(q--)
    {
        int cnt,flag=1;scanf("%d",&cnt);
        for(int i=1;i<=cnt;i++)
        {
            int x;scanf("%d",&x);x^=lst;
            flag&=Insert(w[x]);
        }
        Clear();lst+=flag;
        printf("%s\n",flag?"Connected":"Disconnected");
    }
}
```
多倍经验：P5227，P10075，P10774，放最后是因为怕有人跑了。

---

## 作者：xiao7_Mr_10_ (赞：2)

好的如你所见，这道题让我们动态删边然后询问原图是否连通。

我一看这不是很简单吗？线段树分治一挂直接就过了好吧。

但是，**强制在线**。~~不做了直接逃逸~~。

回归问题本质，我们只需要知道整张图是不是连通的即可，判断连通很麻烦，就倒过来想什么情况会**不连通**。

原图 $S$ 若是可以断成两个连通块 $E$ 与 $S-E$ 那么显然就是不连通的，两个以上的连通块都可以归类于上面的情况。

如果我想让图不连通，那么对于一条边 $(u,v)$，显然当两个端点各属于两个连通块就得删掉它。

所以有一个直观的想法了，我们若是能够找到一组询问的边集包含了图中子集 $T$ 就可以说明不连通了。

神奇的地方来了，这个东西叫**随机异或哈希**。构造边权使得对于所有 $T$ 的边权异或和都为 $0$。

那么我们只需要查询边集的异或和是否可以为 $0$ 即可，可以用**线性基**维护。

那怎么构造呢？

先说方法，随便在图上找棵生成树。然后非树边的边权随机，树边的边权为经过它的非树边的权值的异或和。然后就解决了这个问题。

为什么是对的捏。你想啊，如果 $S$ 里只有两个点的话那么边权就直接抵消掉了，理由是异或的性质。推广到多个点也是一样的。

所以，我们就用了看上去和本题一个八竿子打不着的算法线性基解决了这道题。

code：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=5e5+5;
mt19937 rnd(27426169); 
uniform_int_distribution<int> sjs(1,2e9); 
struct Point{
	int v,val;
};
struct xxj{
	int c[32];
	void clear(){
		memset(c,0,sizeof(c));
	}
	bool insert(int x){
		for(int i = 31;i >= 0;i--){
			if(x&(1<<i)){
				if(!c[i]){
					c[i]=x;
					return 1;
				}
				x^=c[i];
			}
		}
		return 0;
	}
}t;
bool vis[N];
int tot,n,m,u,v,f[N],val[N],pos[N];
vector <Point> e[N];
void dfs(int u,int fa){
	int sum=0;
	pos[u]=++tot;
	for(int i = 0;i < e[u].size();i++){
		int v=e[u][i].v,id=e[u][i].val;
		if(id==fa)continue;
		if(pos[v]){
			if(pos[v]<pos[u])val[id]=sjs(rnd);
		}
		else dfs(v,id);
		sum^=val[id]; 
	}
	val[fa]=sum;
}
int x,q,k;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m;
	for(int i = 1;i <= m;i++){
		cin >> u >>v;
		e[u].push_back((Point){v,i});
		e[v].push_back((Point){u,i});
	}
	dfs(1,0);
	cin >> q;
	int cnt=0;
	for(int i = 1;i <= q;i++){
		cin >> k;
		int flag=1;
		t.clear();
		for(int j = 1;j <= k;j++){
			cin >> x;
			x^=cnt;
			flag&=t.insert(val[x]);
		}
		cnt+=flag;
		if(flag)cout << "Connected\n";
		else cout << "Disconnected\n";
	}	
	return 0;
}
```

---

## 作者：hzoi_Shadow (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P10778)

# 前置知识

[线性基](https://oi-wiki.org/math/linear-algebra/basis/) | 异或哈希

# 解法

强制在线限制了 [luogu P5227 [AHOI2013] 连通图](https://www.luogu.com.cn/problem/P5227) 的线段树分治无法通过。

注意到对于原图的一张生成树中的树边，如果它与覆盖它的返祖边都断开了就会变得不连通。

不妨考虑异或哈希，对返祖边随机赋权，树边的权值为覆盖它的返祖边的权值的异或和。询问时通过线性基判断能否正确插入来得到是否同时出现。

值得一提的是异或哈希能通过的重要限制是 $k \le 15$，即每次删的边不会太多。但是随着 $k$ 的增长，错误性会逐渐扩大，且当 $k> O(\log V)$ 后一定存在不能插入的情况（已经插满了）使得判断错误。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
#define ull unsigned long long
#define sort stable_sort 
#define endl '\n'
mt19937_64 rng(random_device{}());
struct node
{
	int nxt,to,id;
}e[1000010];
int head[500010],u[500010],v[500010],vis[500010],ins[500010],cnt=0;
ull w[500010];
void add(int u,int v,int id)
{
	cnt++;  e[cnt]=(node){head[u],v,id};  head[u]=cnt;
}
void dfs(int x,int fa)
{
	vis[x]=ins[x]=1;
	for(int i=head[x];i!=0;i=e[i].nxt)
	{
		if(e[i].id!=fa)
		{
			if(vis[e[i].to]==0)  dfs(e[i].to,e[i].id);
			else  if(ins[e[i].to]==1)  w[e[i].id]=rng();
			w[fa]^=w[e[i].id];
		}
	}
	ins[x]=0;
}
struct Liner_Base
{
	ull d[70];
	void clear()
	{
		memset(d,0,sizeof(d));
	}
	int insert(ull x)
	{
		for(int i=63;i>=0;i--)
		{
			if((x>>i)&1)
			{
				if(d[i]==0)
				{
					d[i]=x;
					return 1;
				}
				x^=d[i];
			}
		}
		return 0;
	}
}L;
int main()
{
// #define Isaac
#ifdef Isaac
	freopen("in.in","r",stdin);
	freopen("out.out","w",stdout);
#endif
	int n,m,q,k,x,ans=0,flag,i,j;
	scanf("%d%d",&n,&m);
	for(i=1;i<=m;i++)
	{
		scanf("%d%d",&u[i],&v[i]);
		add(u[i],v[i],i);  add(v[i],u[i],i);
	}
	dfs(1,0);
	scanf("%d",&q);
	for(i=1;i<=q;i++)
	{
		scanf("%d",&k);  L.clear();
		flag=1;
		for(j=1;j<=k;j++)
		{
			scanf("%d",&x);  x^=ans;
			flag&=L.insert(w[x]);
		}
		ans+=flag;
		if(flag==0)  printf("Disconnected\n");
		else  printf("Connected\n");
	}
	return 0;
}
```

---

## 作者：chenhouyuan (赞：0)

题目要求我们能够快速的判断给定的边集能否将原图分割成不连通的。我们注意到 $k\le15$ 也就是说每次询问的边集很小，这为后面做法的正确性提供了保证。
# Solution
考虑**随机异或哈希**，我们希望给每条边赋权使得任意一个删除后**恰好**使图不连通的边集的异或和为 $0$，怎么办呢？试着构造，对图的 dfs 树上的非树边从 $0$ 开始标号并令其权值为 $2^x$，树边的权值则为穿过它的简单环上的非树边的异或和，此时当且仅当一条树边和它所在的简单环上的非树边被删去时图不连通且异或和为 $0$，符合我们的要求。

但是这样非树边的权值太大，不可接受。考虑随机化，对非树边随机赋权，修改后显然当一条树边和它所在的简单环上的非树边被删去时异或和仍为 $0$，但是可能存在非法情况，概率随 $k$ 增大而增大，因此当 $k$ 太大时这个做法就假了。

那如何快速判断询问呢？维护一个**线性基**即可。
# AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=1e5+5;
ll n,m,Q,a[N],cnt,k,c,fl,aa[70];
struct edge{
	ll u,v,w,id;
}e2[N*5];
vector<edge>e[N];
mt19937_64 rnd(time(0));
void dfs(ll x,ll f){
	a[x]=++a[0];
	for(edge i:e[x]){
		if(i.id==f)continue;
		if(a[i.v]){
			if(a[i.v]<a[x]){
				e2[i.id].w=rnd();
			}
		}
		else{
			dfs(i.v,i.id);
		}
		e2[f].w^=e2[i.id].w;
	}
}
ll put(ll x){
	x=e2[x].w;
	for(ll i=63;i>=0;i--){
		if(((x>>i)&1)==0)continue;
		if(!aa[i]){
			aa[i]=x;
			return 0;
		}
		x^=aa[i];
	}
	return 1;
}
int main(){
	scanf("%lld%lld",&n,&m);
	for(ll i=1;i<=m;i++){
		scanf("%lld%lld",&e2[i].u,&e2[i].v);
		e[e2[i].u].push_back({0,e2[i].v,0,i});
		e[e2[i].v].push_back({0,e2[i].u,0,i});
	}
	dfs(1,0);
	scanf("%lld",&Q);
	while(Q--){
		fl=0;
		memset(aa,0,sizeof(aa));
		scanf("%lld",&k);
		for(ll i=0;i<k;i++){
			scanf("%lld",&c);
			c^=cnt;
			if(put(c)){
				fl=1;
			}
		}
		if(fl){
			printf("Disconnected\n");
		}
		else{
			printf("Connected\n");
			cnt++;
		}
	}
	return 0;
}
```

---

