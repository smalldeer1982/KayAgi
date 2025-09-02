# [USACO11MAR] Tree Decoration G

## 题目描述

给定一颗以 $1$ 为根的有根树，第 $i$ 个结点的父结点为 $P_i$（$P_1=-1$），在第 $i$ 个结点上挂一个装饰物的代价为 $T_i$，每个结点可以挂任意个。现在给定每棵树子树中至少挂的装饰物个数 $C_i$，求满足要求的最少花费。

$1 \leq n \leq 10^5$，$1 \leq T_i \leq 100$，$1 \leq C_i \leq 10^7$，请注意要开 long long。

## 样例 #1

### 输入

```
5 
-1 9 3 
1 2 2 
5 3 2 
5 1 4 
2 3 3 
```

### 输出

```
20 
```

# 题解

## 作者：Idvz (赞：4)

可以用dfs递归找一找

```cpp
#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long LL;

const int SN = 100000 + 10;

LL f[SN], t[SN], c[SN], now[SN], head[SN];
LL n, ans, que[SN], num, root;

bool vis[SN];

struct Edge {
    int from,to,next;
}E[SN<<1];

void dfs(int u) {
    vis[u] = 1;
    for(int i = head[u]; i ;i = E[i].next) {
        if(vis[E[i].to])    continue;
        dfs(E[i].to);
        c[u] = min(c[u] , c[E[i].to]); //小贪心，更新树中最小的花费
        now[u] += now[E[i].to]; //更新一下当前以i为节点的子树中购买的个数
    }
    if(now[u] < t[u]) {
        ans += (t[u]-now[u]) * c[u]; //如果不够，接着买
        now[u] = t[u];
    }
}

void Add(int u,int v) {
    E[++num].from = u;
    E[num].to = v;
    E[num].next = head[u];
    head[u] = num;
}


int main() {

    scanf("%lld",&n);
    
    for(int i = 1; i <= n; i++) {
        scanf("%lld%lld%lld",&f[i],&t[i],&c[i]);
        if(f[i] != -1)
        Add(i,f[i]),Add(f[i],i); //加无向边
        else root = i;
    }

    dfs(root);
    
    printf("%lld\n",ans);
    
    return 0;

}
```

---

## 作者：fmx0219 (赞：4)

## 题目分析

~~一开始我以为是树形dp~~ 后来想了想发现是道贪心的大水题。

首先显而易见的是放越少的装饰越好，那我们怎么找最小值呢？我们可以比较每一棵子树内的根的Di和这棵子树内其它节点的Di和。如果根的Di小于这棵子树内其它节点的Di和，我们就把根的Di赋成这棵子树内其它节点的Di和。如果大于，是不是还有装饰没放，那我们就把多余的装饰放到这棵子树内Ci最小的节点上。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,root;
long long c[100005],p[100005];
struct node
{
	int ver;
	int next;
}e[200005];
int h[200005],cnt=0;
void add(int u,int v)
{
	e[++cnt].ver=v;
	e[cnt].next=h[u];
	h[u]=cnt;
}
long long minn[100005];//存最小值; 
void dfs(int x,int fa)
{
	minn[x]=p[x];
	for(int i=h[x];i;i=e[i].next)
	{
		int y=e[i].ver;
		if(y==fa) continue;
		dfs(y,x);
		minn[x]=min(minn[x],minn[y]);	
	}
}
long long sum[100005];//sum表示这棵树内放多少装饰; 
long long ans=0;
void dfs1(int x,int fa)
{
	for(int i=h[x];i;i=e[i].next)
	{
		int y=e[i].ver;
		if(y==fa) continue;
		dfs1(y,x);
		sum[x]+=sum[y];
	}
	if(sum[x]<c[x])
	{
		ans+=(c[x]-sum[x])*minn[x];
		sum[x]=c[x];//
	}
}
int main()
{
//	freopen("tdec.in","r",stdin);
//	freopen("tdec.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		int x;
		scanf("%d%lld%lld",&x,&c[i],&p[i]);
		if(x==-1) root=x;
		else add(x,i),add(i,x);
	}
	dfs(1,-1);
	dfs1(1,-1);
	cout<<ans;
}
```


---

## 作者：hhhhyq (赞：4)

### 一道为数不多的 ~~自己想出来的~~ 好题

### 写篇文章纪念一下hhhhh

这道题，乍一看，哇，树形dp......

~~不会啊~~仔细观察数据范围，我们发现hhhh数组都开不下

这就是道dfs题

思路：
* 对于每棵子树，记录放一个物品的最小代价（用 _mintree_ 表示，初始值为 _c_ ,我懒，直接用这个存的 _c_ ）和以当前结点为根的子树中，已经装饰的物品数量（用 _now_ 表示）;
* 如果已经没有子节点可以更新这个点，我们就把它加入队列，用以更新其它点 
 * 这里类似拓扑排序，维护每个点入度 _ind_ ，入度为零则入队；
 * 当然叶子结点入度为零，直接加入队列；
* 然后就开开心心地更新就好啦

**还有大家记得开long long，不开会liangliang（ _now_ 数组和答案 _ans_ ）**


代码emmm：
 
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<queue>

using namespace std;

typedef long long ll;
const int maxn=100050;

int n;
ll f[maxn],d[maxn],ind[maxn],min_tree[maxn],now[maxn];
// f[i]父亲节点 d[i]要求物品数 c[i]花费 ind[i]入度 min_tree[i]子树中物品最小花费 now[i]当前物品数 
ll ans=0;

void read(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld%lld%lld",&f[i],&d[i],&min_tree[i]);
		if(f[i]!=-1)ind[f[i]]++;
	}
}

void work(){
	queue<int> q;
	for(int i=1;i<=n;i++)
		if(ind[i]==0)q.push(i);
	while(!q.empty()){
		int t=q.front();
		if(d[t]>now[t])ans+=1ll*min_tree[t]*(d[t]-now[t]);
		if(t!=1){
		min_tree[f[t]]=min(min_tree[f[t]],min_tree[t]);
		ind[f[t]]--;
		now[f[t]]+=max(d[t],now[t]);	
		if(ind[f[t]]==0)q.push(f[t]);
		}
		 
		q.pop();
	}
}

void print(){
	printf("%lld\n",ans);
}

int main(){
	read();
	work();
	print();
}
```



---

## 作者：popcoount (赞：1)

这道题就是一个暴搜题。

首先我们读入这棵树，将所有边连上。

然后我们从节点 $1$ 开始 DFS，我们要定义如下数组：

- $minx[u]$ 表示以 $u$ 为根的子树中的最小权值（初始值为 $c[u]$）
- $cnt[u]$ 表示以 $u$ 为根的子树中挂了多少礼物
- $ans[u]$ 表示以 $u$ 为根装饰的最小费用

先遍历一边树，将上面的信息全都求出来。

然后如果我们现在的 $cnt[u]$ 已经超过或等于 $d[u]$ 了，说明已经符合要求，直接返回即可；

否则就需要再补全剩余的部分，也就是权值 $\times$ 需要补全的礼物数。

最后别忘了把 $cnt[u]$ 的数量换掉。

注意 long long。

# Code:

```
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e5 + 10, M = N * 2;
int n;
int d[N], c[N];
int h[N], e[M], ne[M], idx;
int minx[N];
int cnt[N];
int ans[N];
void add(int a, int b) {
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
void dfs(int u, int fa) {
	minx[u] = c[u];
	for (int i = h[u]; ~i; i = ne[i]) {
		int j = e[i];
		if (j == fa) continue;
		dfs(j, u);
		cnt[u] += cnt[j];
		minx[u] = min(minx[u], minx[j]);
		ans[u] += ans[j];
	}
	if (cnt[u] >= d[u]) return;
	ans[u] += minx[u] * (d[u] - cnt[u]);
	cnt[u] = d[u];
}
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	memset(h, -1, sizeof h);
	memset(minx, 0x3f, sizeof minx);
	cin >> n;
	for (int i = 1; i <= n; i++) {
		int x;
		cin >> x >> d[i] >> c[i];
		if (x == -1) continue;
		else add(x, i), add(i, x);
	}
	dfs(1, -1);
	cout << ans[1] << '\n';
	return 0;
}
```

---

## 作者：scp020 (赞：1)

# P3018 [USACO11MAR] Tree Decoration G 题解

模拟赛考到的题，过来发个题解。顺便吐槽一下这题真水，应该放第二题。

## 解法

刚看到这题我以为是树形 dp，仔细看了看题，发现题中的要求很少，没有依赖关系，没有要求联通，没有后效性，所以考虑贪心。

因为每个节点放装饰的代价都为正数，所以装饰越少越好。我们先去满足一个节点子树的要求，再去看这个节点的要求。分两种情况处理。

1. 一个节点 $i$ 的子树的装饰总和不少于 $d_i$，则本着不浪费的原则，我们不管这个节点。

2. 一个节点 $i$ 的子树的装饰总和少于 $d_i$，设其节点中已经有了 $m$ 个装饰，则本着不浪费的原则，我们在节点 $i$ 的子树中找到 $c_i$ 最少的点放 $d_i - m$ 个装饰，这样可以最小化这个点极其祖先的花费。

根据以上两种情况，我们从根节点开始深度优先搜索，按顺序贪心就可以了。

## 代码

```cpp
#define int long long
int n,d[100010],c[100010],root,ans,yet[100010];
struct edge
{
	int to;
	edge *next;
};
edge *head[100010];
inline void add(const int &x,const int &y)
{
	edge *e=new edge;
	e->to=y,e->next=head[x],head[x]=e;
}
inline void dfs(int pos,int fa)
{
	for(edge *i=head[pos];i!=nullptr;i=i->next)
		if(i->to!=fa) dfs(i->to,pos),c[pos]=min(c[pos],c[i->to]),yet[pos]+=yet[i->to];
	if(yet[pos]<d[pos]) ans+=(d[pos]-yet[pos])*c[pos],yet[pos]=d[pos];
}
signed main()
{
	read(n);
	for(int i=1,fa;i<=n;i++)
	{
		read(fa),read(d[i]),read(c[i]);
		if(fa==-1) root=i;
		else add(fa,i),add(i,fa);
	}
	dfs(root,0),cout<<ans;
	return 0;
}
```


---

## 作者：Gaode_Sean (赞：1)

我这题的思路使用 DFS 计算答案。

不妨设 $sum_x$ 表示以 $x$ 为根的子树中装饰物数量之和，$min_x$ 表示以 $x$ 为根的子树中单个装饰物最小的代价。

显然，若 $x$ 没有儿子节点，则 $sum_x=d_x$ 。

对于计算玩每一个子树的 $x$，若 $sum_x<d_x$，我们需要再花 $min_x \times (d_x-sum_x)$ 的代价来达到需求。

Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,c[100001],t[100001],fa,sum[100001],mn[100001];
long long ans;
vector<long long> vec[100001];
void dfs(long long x)
{
	mn[x]=t[x];
	for(long long i=0;i<vec[x].size();i++){
		long long y=vec[x][i];
		dfs(y);
		mn[x]=min(mn[x],mn[y]);
		sum[x]+=sum[y];
	}
	if(sum[x]<c[x]){
		ans+=(long long)((c[x]-sum[x])*mn[x]);
		sum[x]=c[x];
	}
}
int main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld%lld%lld",&fa,&c[i],&t[i]);
		if(i!=1) vec[fa].push_back(i);
	}
	dfs(1);
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：moosssi (赞：1)

这道题虽然是道树形dp，但其实主要运用贪心思想。

对于每个节点，我们就选择子树内花费最小的节点，在上面放就行了。

统计答案时，如果子树内已放置的个数大于当前节点的所需数，不用管了，如果小于，缺多少补上去就行了，最后记得开long long 。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
typedef long long ll;
int head[N],ver[N],net[N],tot;
int n,c[N],minc[N],d[N];
ll ans,siz[N];
void add(int a,int b){
	net[++tot]=head[a];
	head[a]=tot;
	ver[tot]=b;
}
void dfs(int x,int fa){
	minc[x]=c[x];
	siz[x]=d[x]; 
	ll sum=0;
	for(int i=head[x];i;i=net[i]){
		int v=ver[i];
		if(v==fa)continue;
		dfs(v,x);
		minc[x]=min(minc[x],minc[v]);//寻找子树内花费最少的节点 
		sum+=siz[v];//记录当前子树内已放了多少个 
	}
	if(sum<siz[x]){//不够就补上 
		ans+=(siz[x]-sum)*(ll)minc[x]; 
	}
	else siz[x]=sum;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		int j;
		scanf("%d%d%d",&j,&d[i],&c[i]);
		if(i==1)continue;
		add(i,j);
		add(j,i);
	}
	dfs(1,0);
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：pocafup (赞：1)

~~简单题~~

好像题解基本上都是代码加注释，没多少解释，这里给个亲民的解释。

首先不难想到一个沙雕 dp，$dp[u][i] = min(dp[u][i],dp[v][j] + (i-j)*val(u))$，其中 $u,v$ 为当前节点和要去的节点，$i,j$ 表示当前节点上装饰的数量。

然后我们发现 $n,d\le 10^6$，这么开二维显然会炸。

观察一下规律：如果某个节点的子树已经全部被满足，那么在包含这个节点的子树上任意一点放装饰都只会影响这一个点是否满足，不会对已经满足的子树产生影响。

因此考虑贪心。

我们考虑记录某一个节点的子树中价值最小的节点的价值，在满足父节点之前保证其子树已经被全部满足。

具体一点，$val[u] = min(val[v]),v \in {subtree(u)}$

再观察一下，在一个节点的子树上放装饰会对其产生影响。因此，我们考虑记录子树上放的装饰数量和。

具体一点，$sz[u] = \sum sz[v], v\in {subtree(u)}$

然后会出现两种情况：

- 子树上的装饰数量大于等于父节点需要的装饰数量
- 子树上的装饰数量严格小于父节点需要的装饰数量

对于第一种情况，~~显然~~我们啥都不用做。

对于第二种情况，由于节点的子树已经全部被满足，而更新其他任何点都不会再对此节点子树的装饰数量产生贡献，因此，我们需要对这个节点累计贡献。

具体一点：$ans = \sum\limits_{u=1}^n min(req[u]-\sum sz[v],0)\times val[u]$

可以使用 dfs 进行实现，复杂度 $O(n)$

```cpp
const int MAXN = 1e5+5;
const int MAXM = 1e5+5;
int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1};
int n,m,t,pos[MAXN],k,a,b,c,val[MAXN],req[MAXN],sz[MAXN],ans;
namespace AdjEdge{
  //var
  int head[MAXN],tot;
  struct Edge{
    int u,v,d,nxt;
  }edge[MAXM<<1];
  inline void add(int u, int v, int d=0){
    edge[++tot].u = u;
    edge[tot].v = v;
    edge[tot].d = d;
    edge[tot].nxt = head[u];
    head[u] = tot;
  }
}
using namespace AdjEdge;
inline int dfs(int u=1){
  trav(i,u){
    int v = edge[i].v;
    sz[u]+=dfs(v);//求子树大小
    val[u] = chkmin(val[u],val[v]);//求最小价值
  }
  if (sz[u]<req[u]) ans+=(req[u]-sz[u])*val[u],sz[u] = req[u];//更答案
  return sz[u];
}
signed main(){
  n = read();
  For(i,1,n) {a = read(), req[i] = read(), val[i] = read();if (a!=-1) add(a,i);}
  dfs();
  writeln(ans);
}
```

拿掉了头文件，放上去会ce，但是并没有防抄袭。

---

## 作者：tumu1t (赞：1)

这道题考察图的运用

可以从树的叶节点向上推，推出每个节点的价值

再运用模拟。

注意有long long

算深度和推价值注意下。

下面上代码（代码丑，轻喷）

注释自认为很详细了，不懂可以私信我。

```cpp
#include<bits/stdc++.h>
using namespace std;
struct u{
    int fa,d,c,m,deep,id;//fa是父亲，d是需求，c是该点花费，k该点子树拥有的装饰物数 
	long long int k;    //m是该点子树的最小花费，deep是深度，id是该点编号 
    vector<int> son;     //son是儿子表 
};
u A[200000];//100000个点 开两倍 
int n;//n是点个数 
int ftcur[200000];//是排序后原编号向新编号的转变 具体看A处 
inline int read() {//快读 
    char ch = getchar(); int x = 0, f = 1;
    while(ch < '0' || ch > '9') {
        if(ch == '-') f = -1;
        ch = getchar();
    } while('0' <= ch && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    } return x * f;
}
bool cmp(u a,u b)//按深度倒序排序 
{
    return a.deep>b.deep;
}
void dfs(int step,int cur)//确定深度 step是当前深度，cur是当前点 
{
    A[cur].deep=step;//填上深度 
    for(int i=0;i<A[cur].son.size();i++)//遍历儿子 
    {
        dfs(step+1,A[cur].son[i]);
    }
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++)
    {
        A[i].fa=read();
		A[i].d=read();
		A[i].c=read();
        A[i].id=i;//记录编号 
        if(i!=1)//不标注会越界 
        A[A[i].fa].son.push_back(i);//记为父亲的儿子 
    }

    dfs(1,1);//记录深度 
    sort(A+1,A+n+1,cmp);//按深度倒序 
    for(int i=1;i<=n;i++)//A
	{
		ftcur[A[i].id]=i;//此处因为排序后父亲会出问题，需要确定原点在排序过后的位置
		 				 //此处对新编号和原编号进行对应 
	} 
    for(int i=1;i<=n;i++)//记录更改过的父亲编号 
    {
        A[i].son.clear();//清空儿子 等下修改 
        if(i!=n)//不标注会越界 
        A[i].fa=ftcur[A[i].fa];//更新原父亲在排序后的位置 
    }
    for(int i=1;i<=n;i++)
    {
    	if(i!=n)//不标注会越界 
        A[A[i].fa].son.push_back(i);//更新儿子们，刚刚清空过了 
    }
    long long int ans=0;//注意long long 
    for(int i=1;i<=n;i++)
    {
        A[i].m=A[i].c;//计算子树上的最小价格 
        for(int j=0;j<A[i].son.size();j++)//遍历儿子 
        { 
            A[i].m=min(A[A[i].son[j]].m,A[i].m);//更新价格 
        }
    }
    long long int q;//不加longlong会有精度问题 
    for(int i=1;i<=n;i++)
    {
        if(A[i].k<=A[i].d)
        {
        	q=(A[i].d-A[i].k)*A[i].m;//算出需要添加的装饰物的价格 
            ans+=q;//给ans加上 
            A[i].k=A[i].d;//更新该点的装饰物数
        }
        A[A[i].fa].k+=A[i].k;//父亲更新 
    }
    cout<<ans;//输出 
    return 0;

}
```

---

## 作者：Yang818 (赞：0)

本蒟蒻刚从[P2996](https://www.luogu.com.cn/problem/P2996)来的。要是没有想出来的朋友也可以先去看看那道题
## 题意
就是有一棵树，这个数的每个节点都有一个属于自己的数字，这个数字要比以这个节点为根的子树上所有节点挂的东西的总数还大或相等。有点抽象，我们看张图。

![题意](https://cdn.luogu.com.cn/upload/image_hosting/wrd8ynwb.png)

（如图） i 这个节点的数字就是 $d_i$，$d_i$ 要比整棵以 i 为根节点的树上所有东西的总和还大或相等。每个节点挂东西的费用不一样。求最小费用。
## 分析

很明显，这是一道树形 dp 题。树形 dp 的模板题可以参看这[一道题](https://www.luogu.com.cn/problem/P1352)

树形 dp 的普通 dfs 相信大家都会写，这边讲一讲这道题中独特的，怎么挂东西。先看一张图。
![分析](https://cdn.luogu.com.cn/upload/image_hosting/u8latm6h.png)

在这一张图中我们假设 $d_u=10$，$d_v=15$ 且 $u$ 和 $v$ 都分别正好挂满10个和15个,但是如果 $d_i=30$ ，那么剩下的5个该挂到哪里呢？肯定是选最便宜点来挂的啦。所以我们不光要建立一个数组来存储现在挂的数量，也要建立一个数组保存一棵树上价格最小的点。
本蒟蒻用刚刚学会的 $\LaTeX$ 来打一遍数组推导式：

$size_i$ 表示以 i 为根节点的子树现在挂的东西的数量。

$size_i=\sum_{v \in son_i}size_v$

$c_u$ 表示以 u 为根的一棵树上价格最小的点。

$c_u=\min(c_v,c_u)$

再加一个 dfs 就好了。

### 代码

为了让大家自己思考，这边就只给出 dfs 的代码了。
```cpp
dfs(u){
	for(i=head[u];i;i=e[i].nxt){//这边示范用链式前向星来储存树 
		int v=e[i];
		dfs(v);
		size[u]+=size[v];
		c[u]=min(c[u],c[v]); 
	}
	if(size[u]<d[u]){//size数组见上文 
		ans+=(d[u]-size[u])*c[u];//c数组见上文
		size[u]=d[u]; //其实是size[u]=size[u]+d[u]-size[u];被简化成了size[u]=d[u];
	}
}
```
望通过

---

## 作者：zhimao (赞：0)

这题还没Pascal题解？那我来发一波。
#### 题意
对于一棵树，初始每个结点的权值为0，要求以结点i为根的子树的权值和大于等于Di，同时给结点i权值加1花费Ci，求最小花费。
#### 分析
显然，当以结点i为根的子树的权值和小于Di时，我们应把权值加在Ci最小的地方。因此，我们可以通过一遍DFS求每个结点最小的Ci，记为min数组。
然后是第二遍DFS，对于每个结点，先求自己每个儿子的最小花费和权值和（为叶节点直接算：Di\*Ci），接着算当前自己的权值和，小于Di加差乘min，大于等于直接过。
### 注意
费用和权值可能超longint，要开int64。
#### 代码
```pascal
var d,c,head,next,went,min:array[0..100005] of longint;
  f,num:array[0..100005] of int64;
  n,i,k,x,root:longint;
procedure dfs1(y:longint);
var j:longint;
begin
  j:=head[y];min[y]:=c[y];
  while j<>0 do
    begin
      dfs1(went[j]);
      if min[went[j]]<min[y] then min[y]:=min[went[j]];
      j:=next[j];
    end;
end;
procedure dfs2(y:longint);
var j:longint;
begin
  j:=head[y];
  while j<>0 do
    begin
      dfs2(went[j]);
      num[y]:=num[y]+num[went[j]];
      f[y]:=f[y]+f[went[j]];
      j:=next[j];
    end;
  if num[y]<d[y] then
    begin
      f[y]:=f[y]+(d[y]-num[y])*min[y];
      num[y]:=d[y];
    end;
end;
begin
  readln(n);
  for i:= 1 to n do
    begin
      read(x,d[i],c[i]);
      if x=-1 then
        begin
          root:=i;
          k:=x;
        end
      else
        begin
          next[i+k]:=head[x];
          went[i+k]:=i;
          head[x]:=i+k;
        end;
    end;
  dfs1(root);
  dfs2(root);
  writeln(f[root]);
end.

```


---

## 作者：Celebrate (赞：0)

这一道题需要开long long（卡了我好久）

注释在代码里面

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
typedef long long LL;
const int N=1e5+10;
struct edge{//编目录 
	int v,nxt;
}e[N];int cnt,last[N];
inline void add(int u,int v){//建边 
	e[++cnt]=(edge){v,last[u]};
	last[u]=cnt;
}
struct trnode{//树形结构 
	LL cost,minn,s;//cost表示满足当前节点的要求所需的最小花费，minn表示i的子树中单价最小的节点，s为以i为根的所以节点的装饰总数， 
}tr[N];
LL d[N],c[N];
int n;
void dfs(int u){
	tr[u].minn=c[u];tr[u].s=0; 
	for(int i=last[u],v=e[i].v;i;i=e[i].nxt,v=e[i].v){//搜索所有的儿子节点，求出cost,minn和s 
		dfs(v);
		tr[u].minn=min(tr[u].minn,tr[v].minn);
		tr[u].s+=tr[v].s;
		tr[u].cost+=tr[v].cost;
	}
	LL tt=d[u]-tr[u].s;//表示还差的装饰数 
	if(tt<0)tt=0;//tt>=0 
	else tr[u].s=d[u];//不要忘记改变tr[u].s 
	tr[u].cost+=LL(tt*tr[u].minn);//增加当前节点的花费 
}
int main(){
	scanf("%lld",&n);int tt;
	for(int i=1;i<=n;i++){
		scanf("%d%lld%lld",&tt,&d[i],&c[i]);
		if(tt==-1)continue;
		add(tt,i);//建边 
	}
	dfs(1);//搜索根节点 
	printf("%lld\n",tr[1].cost);//输出 
	return 0;
}

```


我的博客：

https://blog.csdn.net/zsyzClb/article/details/83657108

---

## 作者：luaddict (赞：0)

其实不难呵，以叶子节点为起点，不断向上更新，遇到儿子数为0的根节点就入队（每有一个儿子入队，根节点儿子数减一），ans累加，具体看程序。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
struct ss
{
    long long fa,money,cnt,need,ru;
} s[100005];//fa表示父节点，money表示当前在这棵子树上安装一个装饰最少花费的钱，s[i].money=min(s[i].money,s[k].money)，k为子节点，cnt为当前安了多少，need表示需要多少，ru就是儿子数。
int n,t[100005];//t为队列。
long long ans;
void bfs()
{
    int head=0,tail=0;
    for(int i=1; i<=n; i++)
        if(!s[i].ru)//先把叶子节点入队。
            t[tail++]=i;
    while(head!=tail)
    {
        int a=t[head];
        if(s[a].need>s[a].cnt)//如果需求大于已安装的，就累加。
        {
            ans+=(s[a].need-s[a].cnt)*s[a].money;//累加ans。
            s[a].cnt=s[a].need;//更新装饰数。
        }
        int b=s[a].fa;
        if(b!=-1)
        {
            s[b].cnt+=s[a].cnt;//更新装饰数。
            s[b].money=min(s[b].money,s[a].money);//更新最小花费。
            s[b].ru--;//儿子数减1。
            if(!s[b].ru)//如果儿子数为0，则入队。
                t[tail++]=b;
        }
        head++;
    }
    return;
}
int main()
{
    int i,j;
    scanf("%d",&n);
    for(i=1; i<=n; i++)
    {
        scanf("%lld%lld%lld",&s[i].fa,&s[i].need,&s[i].money);
        if(s[i].fa!=-1)
            s[s[i].fa].ru++;
    }
    bfs();
    cout<<ans<<endl;
    return 0;
}
```

---

