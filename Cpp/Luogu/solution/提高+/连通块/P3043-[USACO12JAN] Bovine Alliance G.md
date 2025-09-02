# [USACO12JAN] Bovine Alliance G

## 题目描述

给出 $N$ 个点 $M$ 条边的（没有自环但可能有重边的）无向图，要求给每个点分配 $0$ 条或 $1$ 条与它相邻的边，使得每条边被分配恰好一次，求方案数。答案对 $10^9+7$ 取模。

## 说明/提示

样例 $1$ 的 $6$ 种方案如下。

$4$ 个数分别代表第 $1\sim 4$ 条边被分配给了哪个点：

```plain
{2, 3, 4, 5} 
{2, 3, 5, 4} 
{1, 3, 4, 5} 
{1, 3, 5, 4} 
{1, 2, 4, 5} 
{1, 2, 5, 4} 
```

## 样例 #1

### 输入

```
5 4 
1 2 
3 2 
4 5 
4 5 
```

### 输出

```
6 
```

## 样例 #2

### 输入

```
6 5
1 2
2 3
3 4
1 4
2 4```

### 输出

```
0```

# 题解

## 作者：zundamon (赞：12)

首先可以想到，先对于所有的连通块进行计算贡献

运用乘法原理，将每个连通块的贡献相乘

定义一个连通块的贡献为它的可行方案数，下面开始分类讨论

----

### 对于存在环的连通块

![image.png](https://s2.loli.net/2023/07/05/UsjxDabmLp31J5c.png)

这边发现，右边的环中，每个点都必须收入一条边，有两种可行方案

所以 $4$ 号点所连接的唯一一条边，必须与 $4$ 号点分为一组，有一种可行方案

易得：**对于一个连通块，若块中存在环，则贡献为 $2$**

------

### 对于不存在环的连通块

![image.png](https://s2.loli.net/2023/07/05/5VocPskvSj6rWxu.png)

可以发现，这类连通块有 $n$ 个点，$n-1$ 条边

一定存在一个点是没有被分到边的

在 $n$ 个点中选取 $1$ 个没有被分到边的点，贡献为 $C_n^1 = n$ 

----

### 对于边数大于点数的连通块

![image.png](https://s2.loli.net/2023/07/05/2v4P8OwKhxtuLnb.png)

一定存在一个边没有被分配到点，不符合要求，方案为 $0$。

所以遇到这种连通块时，直接全局判 $0$ 即可。


-----

现在问题转化为了：对于每个连通块，判断是否存在环，及点数与边数的关系

对于判环，也可以转化为点数与边数的关系：

随便作一个环，就可以发现，**环中的点数 = 边数**

而边数可通过 $\text{所有点的出度入度之和} / 2$ 得出

整理得到：

```
对于每一个连通块：
   点数 > 边数： 为无环，贡献为点数
   点数 = 边数： 为有环，贡献为 2
   点数 < 边数： 不可行，答案为 0
   
最后将每个连通块的贡献相乘即可
```


代码：

```cpp
#define loop(i,x,y) for(int i=x;i<=y;i++)
#define doop(i,x,y) for(int i=x;i>=y;i--)
using namespace std;
const int Mod=1000000007;
const long long N=1e6+5;
ll n,m,xx,yy;
ll to[N],hd[N],nxt[N],tot;
void add(ll u,ll v){
	nxt[++tot]=hd[u];
	to[tot]=v;
	hd[u]=tot;
}
ll edg,pts;
void dfs(ll p){
	vis[p]=1,pts++;
	for(int i=hd[p];~i;i=nxt[i],edg++){
		if(!vis[to[i]]) dfs(to[i]);
	}
}
signed main(){
	memset(hd,-1, sizeof hd);
	n=read(),m=read();
	loop(i,1,m){
		xx=read(),yy=read();
		add(xx,yy),add(yy,xx);
	}
	ll ans=1;
	loop(i,1,n){
		
		if(!vis[i]){
			pts=edg=0;
			dfs(i);
			if(pts>edg/2) ans=(ans*pts)%Mod;
			else if(pts==edg/2) ans=(ans*2)%Mod;
			else {ans=0;break;}
		} 
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：LZWei (赞：5)

首先跑个tarjan,  记录缩点个数

如果缩点中是1—2——3——4。。。。这种类型的话，

缩点中的可能方案数就是num；

如果是1——2——3——。。。——1的话，缩点中的

情况就只有两种，，，判断的话见代码

——————————————————————————

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define M 200010
#define mdo 1000000007
using namespace std;
int n,m,x[M],y[M];
long long ans=1;
struct edge
{
    int to;
    int next;
};
edge e[M];
int head[M],num;
void add(int from,int to)
{
    e[++num].to=to;
    e[num].next=head[from];
    head[from]=num;
}
int dfn[M],low[M],blo[M],sta[M],vis[M];
int depth,top,cnt;
long long sum[M],tot[M];
void tarjan(int x)
{
    dfn[x]=low[x]=++depth;
    sta[++top]=x;
    vis[x]=1;
    for(int i=head[x];i!=0;i=e[i].next)
    {
        int to=e[i].to;
        if(dfn[to]==0)
        {
            tarjan(to);
            low[x]=min(low[x],low[to]);
        }
        else
        {
            if(vis[to]==1)
                low[x]=min(low[x],dfn[to]);
        }
    }
    if(dfn[x]==low[x])
    {
        cnt++;
        int j;
        do
        {
            j=sta[top--];
            blo[j]=cnt;
            sum[cnt]++;
            vis[j]=0;
        }while(j!=x);
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d",&x[i],&y[i]);
        add(x[i],y[i]);add(y[i],x[i]);
    }
    for(int i=1;i<=n;i++)
        if(dfn[i]==0) tarjan(i);
    for(int i=1;i<=m;i++)
    {
        int r1=blo[x[i]];
        int r2=blo[y[i]];
        if(r1==r2) tot[r1]++;
    }
    for(int i=1;i<=cnt;i++)
    {
        if(sum[i]==tot[i]) sum[i]=2;//判断，，，，，
        sum[i]=sum[i]%mdo;
        ans=ans*sum[i];
        ans=ans%mdo;
    }
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：优秀的渣渣禹 (赞：4)

其实这道题十分简单。。看到大佬们在用tarjan缩点，并查集合并。。。。
##### 蒟蒻渣渣禹都不会。
渣渣禹发现，给出的图经过处理之后会出现：
### 环。
### 不是环。
	不是环的情况我们有n中匹配方式（n为其点的个数）

	是环的情况我们只有两种匹配方式，顺时针匹配和逆时针匹配。

	所以我们dfs处理出图中有多少个环，和不是环的个数。

	ans 初始为1.

	遇到环ans乘二，否则ans乘n（n为这个不是环的点的个数）。
    
   	结束咯w。

```cpp
#define B cout << "BreakPoint" << endl;
#define O(x) cout << #x << " " << x << endl;
#define O_(x) cout << #x << " " << x << " ";
#define Msz(x) cout << "Sizeof " << #x << " " << sizeof(x)/1024/1024 << " MB" << endl;
#include<cstdio>
#include<cmath>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<queue>
#include<stack>
#define LL long long
#define N 100005
#define p 1000000007
using namespace std;
inline int read() {
	int s = 0,w = 1;
	char ch = getchar();
	while(ch < '0' || ch > '9') {
		if(ch == '-')
			w = -1;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9') {
		s = s * 10 + ch - '0';
		ch = getchar();
	}
	return s * w;
}
int to[2 * N],nxt[2 * N],head[2 * N],vis[N],tot;
int tmp,res;
LL ans = 1;
void add(int u,int vis) {
	to[++tot] = vis;
	nxt[tot] = head[u];
	head[u] = tot;
	return ;
}
void dfs(int x) {
	vis[x] = 1;
	tmp++;
	for(int i = head[x]; i; i = nxt[i],res++)
		if(!vis[to[i]])
			dfs(to[i]);
}
int n,m;
void init() {
	n = read(),m = read();
	for(int i = 1; i <= m; i++) {
		int x = read(),y = read();
		add(x,y);
		add(y,x);
	}
}
void solve() {
	for(int i = 1; i <= n; i++) {
		if(!vis[i]) {
			tmp = res = 0;
			dfs(i);
			if(tmp > res / 2) 
				ans = ans * tmp % p;
			else 
				if(tmp == res / 2) 
					ans = ans * 2 % p;
			else ans = 0;
		}
	}
	printf("%lld",ans);
}
int main(){
	init();
	solve();
	return 0;
}
```


---

## 作者：米奇奇米 (赞：3)

## 题解-P3043 牛联盟

### 题目翻译
这道题目的题目意思坑啦我好久。对于这道题目的比较正确的翻译应该是：
* 给每条边找一个配对的点，要求边$(u,v)$配对的点是$u$或$v$，且每个点最多只能被一条边配对，求不同方案数，答案对$998244353$ 取模。

### **Solution**

* **$tarjan$缩点**

我们先用$tarjan$缩一遍点，求出每个强联通分量的$siz[]$

* **如何处理相同的边**

很简单，我们只要用$num[]$记录不同强连通分量出现的次数

* **如何统计答案**

这里值得注意的是，如果$siz[col]=num[col]$的时候，$siz[col]=2$。

**如何理解这样的处理？**

![](https://cdn.luogu.com.cn/upload/pic/66221.png)


于是答案就是：$ans=ans*∑ (i=1..sum)siz[i] $ $sum$为强连通分量的个数

### $Code$
```cpp
#include <bits/stdc++.h>

#define int long long 
#define gc getchar

using namespace std;

const int maxn=100005,mod=1000000007;

vector<int>ma[maxn];
int low[maxn],dfn[maxn],sta[maxn];
int col[maxn],siz[maxn],num[maxn];
int n,m,cnt,top,now,sum,ans=1ll;
int u[maxn],v[maxn];

inline void tarjan(int u) {
	low[u]=dfn[u]=++cnt;
	sta[++top]=u;
	for ( int i=0;i<ma[u].size();i++ ) {
		int v=ma[u][i];
		if(!dfn[v]) {
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}
		else 
			if(!col[v]) low[u]=min(low[u],dfn[v]);
	}
	if(low[u]==dfn[u]) {
		col[u]=++sum;
		siz[sum]++;
		while(u!=sta[top]) {
			col[sta[top]]=sum;
			siz[sum]++;
			top--;
		}
		top--;
	}
}

inline int read() {
	int s=0; char c=gc();
	while(!isdigit(c)) c=gc();
	while(isdigit(c)) 
		s=s*10+(c^48),c=gc();
	return s;
}

signed main() {
	n=read(),m=read();
	for ( int i=1;i<=m;i++ ) {
		u[i]=read(),v[i]=read();
		ma[u[i]].push_back(v[i]);
		ma[v[i]].push_back(u[i]);
	}
	for ( int i=1;i<=n;i++ ) 
		if(!dfn[i]) tarjan(i);
	for ( int i=1;i<=n;i++ ) {
		int r1=col[u[i]];
		int r2=col[v[i]];
		if(r1==r2) num[col[u[i]]]++;
	}
	for ( int i=1;i<=sum;i++ ) {
		if(siz[i]==num[i]) siz[i]=2;
		siz[i]%=mod;
		ans=(ans*siz[i])%mod;
	}
	printf("%lld\n",ans);
	return 0;
}
```



---

## 作者：Dtw_ (赞：2)

# 思路
首先考虑图可能不连通，所以可以对于每个连通块求方案数，最后乘起来。

对于一个连通块，设 $n$ 为其点数，$m$ 为其边数。

当 $m > n$ 时：

边数比点数多，所以一定有点被同时选择，此时方案数为 $0$。

当 $m = n$ 时：

考虑到此时一定是一颗基环树，先考虑环上的点，即为每条边选左边的点和每条边选右边的点，当环上的点选完时，其余树上的点的方案一定唯一，所以此时方案数为 $2$。

当 $m < n$ 时：

他是一颗树，或者不连通。此时一定有一个点是不属于任何一条边的，所以枚举此点，其余点的方案唯一，所以此时的方案数为 $n$。

最后 DFS 一遍求出每个连通块来即可。

# Code
```cpp
#include<bits/stdc++.h>

using namespace std;

#define endl '\n'

#define TRACE 1
#define tcout TRACE && cout

#define IN(o) insert(o)

#define fi first
#define se second

#define int long long

#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

const int INF = 0x3f3f3f3f3f3f3f3f;

const int P = 1e9 + 7;

const int N = 1e6 + 10;

int n, m;

vector<int> G[N];

bool vis[N];

int node, edge;

void dfs(int u)
{
	node++;
	vis[u] = 1;
	for(auto v : G[u])
	{
		edge++;
		if(vis[v]) continue;
		dfs(v); 
	}
}

signed main()
{
	cin >> n >> m;
	for(int i=1; i<=m; i++)
	{
		int u, v;
		cin >> u >> v;
		G[u].push_back(v), G[v].push_back(u);
	}
	int res = 1;
	for(int i=1; i<=n; i++)
	{
		edge = node = 0;
		if(vis[i] == 0) 
		{
			dfs(i);
//			cout << edge << " " << node << endl; 
			edge /= 2;
			if(edge > node) 
			{
				res = 0;
				break;
			}
			else if(edge == node)
			{
				res = res * 2 % P; 
			}
			else if(edge < node)
			{
				res = res * node % P;
			}
		}
	}
	cout << res;
	return 0;
}


```

---

## 作者：Vin_1999 (赞：2)

并查集一次ac。

对于每个联通子图，如果v==e那么就是环或者树加一条返祖或横叉边。方案两种。

if v==e-1 方案v种，每次选一个做为没边连的孤点。

if e>v 直接输出0，因为边匹配有剩。

当然存储方式可以不用前向星。直接存边更方便。














```cpp
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<string>
#include<cstdio>
#include<queue>
#include<stack>
#include<set>
#include<map>
#include<vector>
#include<climits>
#define rep(i,s,n) for(int (i)=(s);(i)<=(n);(i)++)
using namespace std;
const int maxn=1e5+7,mod=1e9+7;
vector<int> v[maxn];
static int n,m;
static int anc[maxn];
int find(int x)
{
    if(anc[x]==x)  return x;
    return anc[x]=find(anc[x]);
}
static int vsum[maxn],esum[maxn];
inline void init()
{
    scanf("%d%d",&n,&m);
    int x,y;
    rep(i,1,m)
    {
        scanf("%d%d",&x,&y);
        v[x].push_back(y);
    }
    rep(i,1,n)
    {
        anc[i]=i;
        vsum[i]=1;
    }
}
void work()
{
    int c,d,cnt=n;
    rep(i,1,n)
    {
        for(int j=0;j<v[i].size();++j)
        {
            c=find(i);d=find(v[i][j]);
            if(c!=d)
            {
              anc[d]=c,--cnt,vsum[c]+=vsum[d];
              vsum[d]=0;esum[c]+=esum[d];
            }
            ++esum[c];
        }
    }
    rep(i,1,n) c=find(i);
}
unsigned long long ans=1;
inline void print()
{
    rep(i,1,n) if(vsum[i])
    {
        if(vsum[i]<esum[i])
        {
            printf("0");
            exit(0);
        }
        else if(vsum[i]==esum[i]+1)
        {
            (ans*=vsum[i])%=mod;
        }
        else if(vsum[i]==esum[i])
          (ans*=2)%=mod;
    }
    printf("%llu",ans);
}
int main()
{
  freopen("e:/in.txt","r",stdin);
  init();
  work();
  print();
  return 0;
}//by fjlyyz-ljy
```

---

## 作者：wflhx2011 (赞：1)

### Solution

首先注意，点可以没有它对应的边，**但边一定要有与它对应的点**。

通过样例，发现给定的图并不一定联通，所以对每个连通块计算方案数，最后取乘积即可。

对于每个连通块，通过边数和点数的关系，可以分为三种可能的情况：

1. 边数多于点数，此时一定有一条边没有相对应的点，不符合题目要求，所以直接输出 $0$。

1. 边数等于点数，即构成一个环，此时有 $2$ 种方案，顺时针分配和逆时针分配各一种。

1. 边数小于点数，又因为联通，所以只能是一棵树，边数比点数少 $1$，此时一定有一个点不会有所对的边，那么在这 $n$ 个点中随便选一个，答案为 $n$。

然后取乘积输出即可。

#### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,cnt,cnt1,ans=1,mo=1e9+7;
long long head[1000005],tot,vis[1000005];
struct edge
{
	long long f,t; 
}k[1000005];
void add(long long u,long long v)
{
	k[++tot].t=v;
	k[tot].f=head[u];
	head[u]=tot;
}
void dfs(long long s)
{
	vis[s]=1;
	cnt1++;
	for(long long i=head[s];i;i=k[i].f)
	{	
		cnt++;
		if(!vis[k[i].t]) 
			dfs(k[i].t);
	}
}
int main()
{
	cin>>n>>m;
	for(long long i=1;i<=m;i++)
	{
		long long u,v;
		cin>>u>>v;
		add(u,v);
		add(v,u);
	}
	for(long long i=1;i<=n;i++)
	{
		if(!vis[i])
		{
			cnt=cnt1=0;
			dfs(i);
			if(cnt1>cnt/2) 
				ans=(ans*cnt1)%mo;
			else if(cnt1==cnt/2) 
				ans=(ans*2)%mo;
			else 
			{
				ans=0;
				break;
			}
		}
  
	}
	cout<<ans;
	return 0;
}

  
```

---

## 作者：AC？别闹！ (赞：1)

[更好的阅读体验](https://blog.imlzhyt.top/archives/p3043-sol.html)

[题目链接](https://www.luogu.com.cn/problem/P3043)

本题解使用的是并查集合并算法。

### 题意

给出 n 个点 m 条边的无向图，要将所有边定向，且要求每个点的入度不大于 1，求可行方案数，对 $10^9+7$ 取模。

### 思路

考虑这个图单纯是一个环的情况，能发现对这个环定向的话只有两种情况，顺时针定向或者逆时针定向，那我们再向这个环上添加一条边指向另一个点使它变成一颗基环树呢？那这条边只有一种定向的可能，就是向那个单独的点定向。那如果把那条边指向的点换成一个环呢？你会发现这就是无解的情况，因为定向两个环的时候占用了所有的点，中间那条连接的边就没法定向了。

而如果这个图里没有环呢？那么定向的方案数就等于点数，因为一定会有一个点没有入度，定向的方案数即为选取这个点的方案数也就是 n。

最后一个要注意的点就是这个图不保证连通，可以运用乘法定理去统计所有连通块的总方案数。

然后知道了怎么做之后就是选择做法了呗，看了一圈题解发现没有并查集合并的做法（之前那个并查集的好像被撤了），那就讲讲并查集合并喽。

其实并查集合并就是在合并时同时合并这个连通块的信息，这里要统计的就是这个连通块里的边数和点。合并时要注意边数要加 1，也就是要把现在的这条边加进去。

上代码！

### 代码

```cpp
#include<iostream>
#include<algorithm>
#define int long long
using namespace std;
const int N=100005,mod=1000000007;
int n,m;
int p[N],dian[N],bian[N];
int read(){
    int x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-') f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<3)+(x<<1)+(c^48);
        c=getchar();
    }
    return x*f;
}//快读
int find(int x){
    if(p[x]!=x) p[x]=find(p[x]);
    return p[x];
}//并查集找祖先
signed main()
{
    n=read(); m=read();
    //初始化并查集，记得初始化点数为1，也就是它自己
    for(int i=0;i<=n;++i) p[i]=i,dian[i]=1;
    for(int i=0;i<m;++i){
        int u=read(),v=read();
        u=find(u),v=find(v);
        //如果找到环的话就只增加边数
        if(u==v) ++bian[u];
        else{
            //否则合并，并合并边数和点数
            p[u]=v;
            dian[v]+=dian[u];
            dian[u]=0;
            //边数记得加1，也就是现在的这条边
            bian[v]+=bian[u]+1;
        }
    }
    int ans=1;
    for(int i=1;i<=n;++i){
        //找独立的连通块
        if(p[i]!=i) continue;
        //统计答案
        if(bian[i]<dian[i]) ans*=dian[i],ans%=mod;
        else if(bian[i]==dian[i]) ans<<=1,ans%=mod;
        else ans=0;
    }
    cout<<ans<<endl;
    return 0;
}
```



---

## 作者：qiliu (赞：0)

## 思路

不妨先从最简单的情况想起。我们假设这张图只有两个点并且是连通的，这两个点之间有 $n$ 条边，进行分类讨论。

首先很显然的，因为每个点只能匹配一条边，所以当 $n < 3$ 时没有合法解。当 $n = 2$ 时，其中一条边可以任选一条边连上，另一条边选另一个点，共有两种情况。当 $n=1$ 时，这条边可以连任意一个点，有两种情况。

那么下一步，我们把这个结论推广一下。在一个可能不连通的图里，我们对于每个连通块进行讨论。

- 当这张图存在环时，对于环上的点，我们发现他有两种连法。可以感性理解为顺时针连和逆时针连。而剩下的点只能往远离环的方向连边。于是此时只有两种方案。注意到此时边数等于点数，方便统计答案。
- 当这张图不存在环时，如果边大于点，显然是无解的。如果点大于边，因为这是一个连通块，所以只有点比边多一这一种可能。此时必然有一个点分不到边，所以方案有 $n\choose 1$ 种可能。

最后统计答案，根据乘法原理，我们把每个连通块的方案数乘起来就能得到答案。

## code

```cpp
#include<bits/stdc++.h>
#define int long long
#define DEBUG(x) cerr<<#x<<'='<<x<<endl
#define endl '\n'
using namespace std;
inline int rd()
{
    char t=getchar();
    int f=1,x=0;
    while(t<'0'||t>'9')
    {
        if(t=='-')f=-1;
            t=getchar();
    }
    while(t>='0'&&t<='9')
        x=x*10+t-'0',t=getchar();
    return x*f;
}
inline void wt(int t)
{
    if(t<0)
        putchar('-'),t=-t;
    if(t>9)
        wt(t/10);
    putchar(t%10+'0');
    return;
}
const int N=1e5+100;
const int MOD=1e9+7;
int n,m;
vector<int>a[N];
bool vis[N];
int ans=1;
int dot=0,edge=0;
void dfs(int x){
    vis[x]=1;dot++;
    for(int i=0;i<a[x].size();i++){
        int v=a[x][i];edge++;
        if(!vis[v])dfs(v);
    }
}
signed main()
{
    // ios::sync_with_stdio(false);
    // cin.tie(0);
    // cout.tie(0);
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    n=rd(),m=rd();
    for(int i=1;i<=m;i++){
        int u=rd(),v=rd();
        a[u].push_back(v);
        a[v].push_back(u);
    }
    // memset(vis,0,sizeof(vis));
    // cerr<<n<<endl;
    for(int i=1;i<=n;i++){
        // cerr<<i<<' '<<vis[i]<<endl;
        if(!vis[i]){
            dot=edge=0;
            // cerr<<dot<<' '<<edge<<endl;
            dfs(i);
            edge/=2;//我们建的是双向边，所以最后统计边数要除以二。
            if(dot==edge)ans*=2,ans%=MOD;
            if(dot>edge)ans*=dot,ans%=MOD;
            if(dot<edge){putchar('0');return 0;}
        }
    }
    wt(ans);
    //fclose(stdin);
    //fclose(stdout);
    return 0;
}
```
希望有帮到你。

---

## 作者：FRZ_29 (赞：0)

## P3043 [USACO12JAN] Bovine Alliance G
[题目传送门](https://www.luogu.com.cn/problem/P3043)  
[也许更好的阅读体验](https://www.cnblogs.com/FRZ29/p/18336480)
### 思路
首先分情况讨论每种联通块的可能，有三种不同的情况会对答案 $ans$ 产生不同的贡献。

#### 联通块有环
![1](https://s2.loli.net/2024/08/01/DYa7iBNUo3r8Cq4.png)
如图，因为每条边都有要有归属，所以环上的边只能全都顺时针或逆时针属于某个点，且不在环上的点仅有一种可能。

因此该情况对答案的贡献为 $ans \times 2$。

#### 联通块为链
![2](https://s2.loli.net/2024/08/01/etdOUDaG5Li7HK8.png)
对于一条链，边数比点数小 1 所以仅有一个点是没有边的，而若确认某个点没有边的话，边的所属仅有一种可能。因此答案的贡献为 $ans \times t$，$t$ 为该联通块点的个数。

#### 联通块内边数大于等于点数
![3](https://s2.loli.net/2024/08/01/4kjn6Frl32ZVe9I.png)
问题的答案为 $0$，直接结束了。

#### 转化
问题变为判断联通块内的情况，对此，利用联通块内度数除以 $2$ 等于边数，判断点数与边数的关系即可。

### 代码
```cpp
#include <iostream>
#include <cstdio>
typedef long long LL;

using namespace std;

const int mod = 1e9 + 7, N = 1e5 + 5;

#define MOD(x) ((x + mod) % mod)
#define LF(i, __l, __r) for (int i = __l; i <= __r; i++)
#define RF(i, __r, __l) for (int i = __r; i >= __l; i--)

int head[N], ver[N * 2], nxt[N * 2], edge[N * 2];
int n, m, tot = 1;
bool vis[N];
LL ans = 1, cnt, cnt1;

void add(int u, int v) {
    ver[++tot] = v;
    nxt[tot] = head[u], head[u] = tot;
}

void dfs(int u) {
    vis[u] = true, cnt++;
    for (int i = head[u]; i; i = nxt[i]) {
        cnt1++;
        if (!vis[ver[i]]) dfs(ver[i]);
    }
}

int main() {
    scanf("%d%d", &n, &m);
    
    LF(i, 1, m) {
        int x, y;
        scanf("%d%d", &x, &y);
        add(x, y), add(y, x);
    }

    LF(i, 1, n) {
        if (!vis[i]) {
            cnt = cnt1 = 0;
            dfs(i);
            if (cnt == cnt1 / 2) ans = MOD(ans * 2);
            else if (cnt > cnt1 / 2) ans = MOD(ans * cnt);
            else { ans = 0; break; } 
        }
    }

    printf("%lld", ans);
    return 0;
}
```

> 三军可夺帅也，匹夫不可夺志也。

---

## 作者：IGA_Indigo (赞：0)

## 题目大意
题目翻译上已经说的很清楚了，给出 $n$ 个点 $m$ 条边的无向图，让你给边和点分组，要求是“每条边只能和相邻两点之一分在一组，点也可以单独一组。每个点只能被选择一次”。问方案数，答案对 $10^9+7$ 取模。

避免对输入输出格式有疑问，我稍微翻译一下。
### 输入格式
第一行两个正整数 $n$ 和 $m$。

接下来 $m$ 行每行两个正整数 $u$ 和 $v$，代表 $u$ 和 $v$ 之间有一条无向边。
### 输出格式
一个正整数，代表方案数。
## 大体思路
根据题意给的分组方式，我们考虑一个个连通块的去考虑，一个连通块分为三种情况：
- 有点没有分到边的，可以发现这种都是点数等于边数加一的（否则就不是个图了），这样的话肯定是连不满的，总会有一个点剩下，所以我们的方案数就变成 $ans=ans\times d$（$d$ 代表这一个连通块里的点数），这样就是每一个点失配的情况。
- 出现了环，这种的话环的内部顺着连和逆着连各是一种方式，接下来再在环外面连任意的点边都只有一种连接方式，所以这时候我们 $ans=ans\times 2$。
- 有点被分了多次，可以发现这种情况点数比边数大，这种情况不符合题目所给的分组方式，那我们的方案数清零：$ans=0$ 并跳出。

我们看一下代码便于理解。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
vector<int> t[100005];
int mod=1000000007;
bool vis[100005];
int b,d;
void dfs(int x){
	vis[x]=1;//正常 dfs 整个连通块 
	d++;
	for(auto v:t[x]){
		b++;//查询点数和边数 
		if(!vis[v]){//没标记过 
			dfs(v);//继续搜 
		}
	}
}
int main(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		t[u].push_back(v);
		t[v].push_back(u);//普通邻接表建图 
	}
	long long ans=1;
	for(int i=1;i<=n;i++){
		if(!vis[i]){//如果这个点没被选过 
			b=0,d=0;//先清零边数和点数 
			dfs(i);//扫一遍这个连通块 
			if(d>b/2){//我们说的第一种情况 
				ans=(ans*d)%mod;//我们可以让方案数乘点数 
			}
			else if(d==b/2){//我们说的第二种情况 
				ans=(ans*2)%mod;//我们可以让方案数乘 2
			}
			else{//我们说的第三种情况 
				ans=0;//不满足，方案数直接清零 
				break ;//跳出，没必要继续了 
			}
		}
	}
	cout<<ans;//正常输出答案即可 
	return 0;
}
```

---

## 作者：laoliu12345 (赞：0)

## P3043
[题目传送门](https://www.luogu.com.cn/problem/P3043)
### 解法说明
首先对于每个连通块，都分三种情况进行讨论：

一、若连通块无环，即满足 $cnt_1>cnt_2$，其中 $cnt_2$ 为边数，而 $cnt_1$ 为点数。（实际上边数最少为点数 $cnt_1-1$，故 $cnt_2=cnt_1-1$）。对这种情况画图分析后会发现其对答案的贡献为 $C^{cnt_2}_{cnt_1}$，即点数 $cnt_1$。

二、若连通块有环，且边数正好为点数，那此时我们只能选择把所有点加上，但对于每条边可以选择左节点还是右节点，故对答案贡献恒为 $2$。

三、若连通块有环，但边数大于点数，那此时我们就无法实现题目所要求的，故遇到此种情况直接使答案变为 $0$
。

那就可以愉快的写代码了。
### 题目代码
```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
const int N=5e6+10,Mod=1e9+7;
int n,m;
int h[N],e[N],ne[N],idx;
bool st1[N],st2[N];
int cnt1[N],cnt2[N];
int cnt;
int res=1;
void add(int a,int b)
{
	e[idx]=b,ne[idx]=h[a],h[a]=idx++;
}
void dfs(int u,int pre)
{
	if(st1[u]) return ;
	cnt1[cnt]++;
	st1[u]=true;
	for(int i=h[u];~i;i=ne[i])
	{
		int j=e[i];
		if(j==pre) continue;
		if(!st2[i]&&!st2[i^1])
		    cnt2[cnt]++;
		st2[i]=st2[i^1]=true;
		dfs(j,u);
	}
}
signed main()
{
	cin>>n>>m;
	memset(h,-1,sizeof h);
	while(m--)
	{
		int a,b;
		cin>>a>>b;
		add(a,b),add(b,a);
	}
	for(int i=1;i<=n;i++)
		if(!st1[i])
		{
			++cnt;
			dfs(i,-1);
		}
	//for(int i=1;i<=cnt;i++)
	//    cout<<cnt1[i]<<" "<<cnt2[i]<<endl;
	for(int i=1;i<=cnt;i++)
	{
		if(cnt1[i]==cnt2[i]) res*=2,res%=Mod;
		else if(cnt1[i]>cnt2[i]) res*=cnt1[i],res%=Mod;
		else
		{
			res=0;
			break;
		}
	}
	cout<<res<<endl;
	return 0;
}
```

---

## 作者：ttq012 (赞：0)

考虑将图 $G$ 拆分成若干个连通块 $G_1,G_2,G_3,\ldots,G_k$ 进行考虑。对于每一个 $G$ 图的子图连通块 $G'$，设 $n$ 是 $G'$ 图的点数，$m$ 是 $G'$ 图的边数。考虑分类讨论：

+ $n<m$，显然该连通块不能满足条件（边无法恰好和点一一配对）。
+ $n=m$，则图形成了一个基环树，此时基环树内部的环可以顺时针或者逆时针两种情况，因此该连通块有 $2$ 种不同的选取方案。
+ $n-1=m$，则图形成了一个树，一定有一个点没有分到任何一条边。所以考虑枚举这个点，剩下的边恰好可以和剩下的点一一匹配，送一该连通块一共有 $n$ 种不同的选择方案。

使用乘法原理把答案乘起来即可。使用并查集维护，时间复杂度为 $O(\alpha n)$。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 500100, mod = 1e9 + 7;
int fa[N];
int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}
vector<int> sccve[N];
vector<int> scced[N];
struct { int x, y; } a[N];
signed main() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) fa[i] = i;
    for (int i = 0; i < m; i++) {
        cin >> a[i].x >> a[i].y;
        int ta = find(a[i].x), tb = find(a[i].y);
        if (ta != tb) fa[ta] = tb;
    }
    for (int i = 0; i < m; i++)
        scced[find(a[i].x)].push_back(i);
    for (int i = 1; i <= n; i++)
        sccve[find(i)].push_back(i);
    int s = 1;
    for (int i = 1; i <= n; i++)
        if (sccve[i].size()) {
            if (sccve[i].size() == scced[i].size())
                s = s * 2 % mod;
            else if (sccve[i].size() == scced[i].size() + 1)
                s = s * sccve[i].size() % mod;
            else
                s = 0;
        }
    cout << s << '\n';
    return 0;
}
```

---

## 作者：cosf (赞：0)

## [P3043](https://www.luogu.com.cn/problem/P3043)

只能说，这题和 [ABC226E](https://www.luogu.com.cn/problem/AT_abc226_e) 简直就是重题。

转化一下本题题意：给定一个无向图，让你给边定向，问有多少种方案使得每个点的出度都小于等于 $1$。

我们考虑对于一个连通块的情况。

如果图中边数大于点数，显然不可行，直接输出 $0$。

如果边数等于点数，那么它必定是一个树加上一条多余的边，即基环树。

对于基环树内的环，显然有两种方法（可以理解为“顺时针”和“逆时针”）。

由于环的点数等于边数，所以环上的每一个点的出度都是 $1$，那么其他的边必定是“向外”的，即从远离环的点指向靠近环的点。

那么一个基环树的答案就是 $2$。

如果边数小于点数，则边数一定是点数 $-1$，否则不连通。因为出度和是点数 $-1$，所以必定有一个点的出度为 $0$。每一个点都可以作为这个出度为 $0$ 的点。

因为这样的图是树，我们只要把一个点当作根建一棵树，每条边由儿子指向父亲即可。

那么一个树的答案就是树的大小。

综合以上讨论，将每个连通块的答案相乘即得答案。

## 代码

```cpp
#include <iostream>
using namespace std;

#define MAXN 200005
#define MOD 998244353

using pii = pair<int, int>;
using ll = long long;

int fa[MAXN];
int siz[MAXN];
int sd[MAXN];

int find(int x)
{
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

void merge(int u, int v)
{
    int fu = find(u), fv = find(v);
    if (fu == fv)
    {
        return;
    }
    if (siz[fu] < siz[fv])
    {
        swap(fu, fv);
    }
    fa[fv] = fu;
    siz[fu] += siz[fv];
    sd[fu] += sd[fv];
}

pii e[MAXN];

int n, m;

int main()
{
    cin >> n >> m;
    if (n != m)
    {
        cout << 0 << endl;
        return 0;
    }
    for (int i = 1; i <= n; i++)
    {
        fa[i] = i;
        siz[i] = 1;
    }
    for (int i = 1; i <= m; i++)
    {
        cin >> e[i].first >> e[i].second;
        sd[e[i].first]++;
        sd[e[i].second]++;
    }
    for (int i = 1; i <= m; i++)
    {
        merge(e[i].first, e[i].second);
    }
    ll res = 1;
    for (int i = 1; i <= n; i++)
    {
        if (i == fa[i])
        {
            if (siz[i] != (sd[i] >> 1))
            {
                cout << 0 << endl;
                return 0;
            }
            else
            {
                res = (res << 1) % MOD;
            }
        }
    }
    cout << res << endl;
    return 0;
}

```


---

## 作者：天空即为极限 (赞：0)

容易发现只有如果一个联通块中边大于点数答案为 $0$。所以我们只要考虑边小于点数（树）和边等于点数（基环树）的连通块的各自的方案数，最后再相乘即可。

---
### 联通块结构为一棵树

我们可以考虑如果哪个点没有分到边，发现若一个点没有分到边，那么分组就是唯一的，所以一棵树的方案数就是这棵树的 $size$。

---
### 联通块结构为一棵基环树

考虑把环分离出来，发现环上的方案等价于给你一个简单环，要你给上面的边定向，使得每个环上点的入度为 $1$，这个显然方案数为 $2$。

而分离出环之后，剩下的东西就是一些树，每颗树上多了一条边，且这条边只有一个端点，每颗这样的树的的方案显然为 $1$。

所以基环树的方案数就是 $2$。

---

并查集来维护即可。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 5e5 + 5;

int fa[N], siz[N], e[N];
int find (int x) { return fa[x] == x ? x : fa[x] = find (fa[x]); }
void Union (int x, int y) {
  x = find (x), y = find (y);
  if (x == y) return e[x] ++, void ();
  fa[x] = y; siz[y] += siz[x]; e[y] += e[x] + 1;
}

const int mod = 1e9 + 7;

int main () {
  int n, m; cin >> n >> m;
  for (int i = 1; i <= n; i ++) fa[i] = i, siz[i] = 1;
  for (int i = 1; i <= m; i ++) {
    int x, y; cin >> x >> y;
    Union (x, y);
  }
  long long ans = 1;
  for (int i = 1; i <= n; i ++) {
    if (fa[i] == i) {
      if (siz[i] == e[i]) ans = ans * 2 % mod;
      else if (siz[i] < e[i]) ans = 0;
      else ans = ans * siz[i] % mod;
    }
  }
  cout << ans << "\n";
}
```


---

## 作者：Narcissusany (赞：0)

> 给每条边找一个配对的点，要求边 $(u,v)$ 配对的点是 $u$ 或 $v$ ，且每个点最多只能被一条边配对，求不同方案数。
>
> $1\leq m\leq n\leq 10^5$ 。

考虑问题可以转化成给每条边定向，使得最后整张图每个点的度数都 $\leq 1$ 的方案数。然后…然后就是考察对于图论模型的洞见性有多强了：

1、不难发现一个简单环的定向方式总共是 $2$ 。

2、考虑去计算一棵树的定向方式。发现随便找一个根，显然哪个点当根对于整棵树的方案数没有影响。考虑如果将所有边都向儿子定向，那么这样一定合法，这是第一种方案。同时，单独把某一条边取反，假设这条边连接的儿子是 $x$ ，那么同时需要把 $x\to fa_x,fa_x\to fa_{fa_x}, fa_{fa_x}\to fa_{fa_{fa_x}}$ 全部取反，那么最终会取反到根，根的入度会变成 $1$ ，这也就说明不能有 $>1$ 条边同时取反。所以可以知道一棵树的定向方式为 $1+(n-1)=n$ 。

发现对于无向图，本质上就是树插环的形态，本质上只有环和树两种东西，同时环接树这种结构由于与环相邻的那个点。所以拿一个带权并查集维护即可。有一个坑点，就是如果两个点不在同一个即集合里，边数也要++。

对于部分特判原因可以左转讨论区。

```cpp
ll ans ;
int n, m ;
int ns[N] ; 
int es[N] ; 
int fa[N] ; 
vint eg[N] ; 

int find(int x){
	if (x ^ fa[x])
		return fa[x] = find(fa[x]) ; 
	return fa[x] ; 
}
int main(){
	cin >> n >> m ; ans = 1 ;
	for (int i = 1 ; i <= n ; ++ i) 
		fa[i] = i, ns[i] = 1 ; int x, y ; 
	for (int i = 1 ; i <= m ; ++ i){
		x = qr(), y = qr() ;
		int f1 = find(x), f2 = find(y) ; 
		if (f1 != f2){
			fa[f1] = f2 ; 
			ns[f2] += ns[f1] ; 
			es[f2] += es[f1] + 1 ; 
		}else es[f1] ++ ; 
	}
	for (int i = 1 ; i <= n ; ++ i){
		if (fa[i] != i) continue ; 
		if (ns[i] == es[i]) 
			(ans *= 2ll) %= P ;
		else if (ns[i] - 1 == es[i]) 
			(ans *= (ll)ns[i]) %= P ;
		else ans = 0 ;
	}
	cout << ans << '\n' ; return 0 ; 
}




```

---

## 作者：RikoHere (赞：0)

题意:现在有$n$个点，$m$条边的图,$1 \leq m \leq n$，让点和其所连边进行配对，一个点或边只能配对一次，所有边必须配对，而点可以无需配对

这题有思维无码量还是比较友好的

现在我们有一张连通图，设它边数为$m$，点数为$n$，显然$m \ge n-1$

根据题意，一个点只能和一条边配对，自然的若在当前图中$m > n$，则是无解的

接下来进行分类讨论

$m=n$的情况下，有点类似**基环树**的感觉...思考和环有关的性质，若现在有一条环，每个点要和一条边进行匹配，不难发现匹配方案只有**两种**，因为一个点只和两条边相连嘛...对于基环上任意一个点的子树，因为**根节点必须与一条环上边匹配，所以其子树上任意一个节点只有子节点匹配其连向父节点的边一个选择**

$m=n-1$的情况下，借用上面的结论，每个子节点首先应该与其连向父节点的边匹配，而当前情况下我们**允许且只允许一个点不进行匹配**，那么方案数显然就是$n$了，可以画图理解

至于统计边数，就有很多种写法了，可以按照自己的思路写

```
//2019/8/7->Riko->AtNCU->luoguP3043
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<vector>

namespace Rikopack {
    bool digit (int ch) { return (ch <= '9' and ch >= '0');}
    inline int in () {
    	int x = 0, ch = getchar(), base = 1;
    	while (!digit(ch)) {
    	    if (ch == '-') base = -1;
    	    ch = getchar();
    	}
    	while (digit(ch)) x = x*10+ch-'0', ch = getchar();
    	return x*base;
    }
    template <typename T> inline void smax (T& x, T y) { if (x < y) x = y;}
    template <typename T> inline void smin (T& x, T y) { if (x > y) x = y;}
    void print (int x) { printf("debug:%d\n", x);}
    const int MAXINT = 2123456789;
    #define LL long long
    //Believing heart is your power
}
using namespace Rikopack;
using namespace std;

const int N = 101000, mod = 1e9+7;
int n, m, tmp, ans, Size, Edges;
int vis[N];
int nxt[N<<1], to[N<<1], bol[N], head[N], edgeind;
inline void add (int u, int v) {
	int i = ++edgeind;
	nxt[i] = head[u]; to[i] = v; head[u] = i;
}

void Getcir (int x, int fa) {
	vis[x] = true; Size++;
	for (int i = head[x]; i; i = nxt[i]) {
		int e = to[i];
		if (!bol[(i+1)/2]) {
			bol[(i+1)/2] = true;
			++Edges;
		}
		if (e == fa or vis[e]) continue;
		Getcir(e, x);
	}
}
void work (int x) {
	Edges = Size = tmp = 0;
	Getcir(x, 0);
	if (Edges == Size) tmp = 2;
	if (Edges == Size-1) tmp = Size;
}
void prepare () {
	n = in(); m = in();
	for (int i = 1; i <= m; ++i) {
		int u = in(), v = in();
		add(u, v); add(v, u);
	}
	ans = 1;
	for (int i = 1; i <= n; ++i) {
		if (!vis[i]) work(i);
		else continue;
		ans = ((LL)ans*tmp)%mod; 
		if (!ans) {
			puts("0"); return;
		}
	}
	printf("%d", ans);
}
int main () { prepare();}
```


---

## 作者：S__Z (赞：0)

这道题可以直接建边并进行dfs，如同下面的题解说的

定义V为当前联通块的点数，E为当前联通块的边数

\_if(V==(E-1)) ans=ans\*V%mod\_

\_if(V==E) ans=ans\*2%mod(这个自己可以画一下，环上正反两种情况\_

\_if(V<E) 不成立，结束\_

所以我们只需要维护V和E即可；

但如何维护呢?这不是无向图吗?

我们从偶数开始建边，因为每条边只会用到一次，所以当这条边用过之后，这条边与这条边xor 1全都变成已用（1），这样既重复经过了。


```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#define man 100010
#define mod 1000000007
#define ll long long
using namespace std;
struct edge
{    int next,to;}e[man<<2];
int head[man<<2],num=1,findd[man<<2];
inline void add(int from,int to)
{    e[++num].next=head[from];
    e[num].to=to;
    head[from]=num;
    }
bool vis[man];
int V,E;
void dfs(int u)
{    vis[u]=1;
    V++;
    for(int i=head[u];i;i=e[i].next)
    {    if(!findd[i])
        {    findd[i]=findd[i^1]=1;E++;
            if(!vis[e[i].to]) dfs(e[i].to);
            }
        }
    }
int n,m;
int main()
{    cin>>n>>m;
    for(int i=1;i<=m;i++)
    {    register int x,y;
        cin>>x>>y;
        add(x,y);add(y,x);
        }
    int ans=1;
    for(int i=1;i<=n;i++)
    {    if(!vis[i])
        {    V=E=0;
            dfs(i);
            if(E>V)
            {    printf("0\n");return 0;}
            if(V==E) ans=ans*2%mod;
            else ans=1ll*ans*V%mod;
            }
        }
    cout<<ans<<endl;
    return 0;
}
```

---

