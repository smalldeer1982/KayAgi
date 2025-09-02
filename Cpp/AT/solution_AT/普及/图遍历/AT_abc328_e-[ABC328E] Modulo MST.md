# [ABC328E] Modulo MST

## 题目描述

给定一个有 $N$ 个顶点、$M$ 条边的带权无向连通简单图，顶点编号为 $1$ 到 $N$，边编号为 $1$ 到 $M$，以及一个正整数 $K$。  
第 $i$ 条边 $(1\leq i\leq M)$ 连接顶点 $u_i$ 和顶点 $v_i$，权值为 $w_i$。

对于该图的任意一棵生成树 $T$，定义 $T$ 的代价为 $T$ 所包含的所有边的权值之和对 $K$ 取模后的结果。  
请你求出所有生成树的代价的最小值。

## 说明/提示

## 限制条件

- $2\leq N\leq 8$
- $N-1\leq M\leq\dfrac{N(N-1)}{2}$
- $1\leq K\leq 10^{15}$
- $1\leq u_i < v_i \leq N\ (1\leq i\leq M)$
- $0\leq w_i < K\ (1\leq i\leq M)$
- 给定的图是简单且连通的
- 所有输入均为整数

## 样例解释 1

给定的图如下所示。  
![](https://img.atcoder.jp/abc328/67d2cc2b93ec47687a733cd379c3c07c.png)  
包含边 $1,3,5,6$ 的 $4$ 条边的生成树的代价为 $(99+86+81+95)\bmod{328}=361\bmod{328}=33$。  
该图所有生成树的代价都不小于 $33$，因此输出 $33$。

## 样例解释 2

该图只有一棵生成树，其代价为 $325437688$，请输出该值。

## 样例解释 3

请注意，输入和答案可能超出 $32$ 位整数的范围。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
5 6 328
1 2 99
1 3 102
2 3 86
2 4 94
2 5 95
3 4 81```

### 输出

```
33```

## 样例 #2

### 输入

```
6 5 998244353
1 2 337361568
1 6 450343304
2 3 61477244
2 5 745383438
4 5 727360840```

### 输出

```
325437688```

## 样例 #3

### 输入

```
8 28 936294041850197
1 2 473294720906780
1 3 743030800139244
1 4 709363019414774
1 5 383643612490312
1 6 557102781022861
1 7 623179288538138
1 8 739618599410809
2 3 857687812294404
2 4 893923168139714
2 5 581822471860662
2 6 740549363586558
2 7 307226438833222
2 8 447399029952998
3 4 636318083622768
3 5 44548707643622
3 6 307262781240755
3 7 12070267388230
3 8 700247263184082
4 5 560567890325333
4 6 704726113717147
4 7 588263818615687
4 8 549007536393172
5 6 779230871080408
5 7 825982583786498
5 8 713928998174272
6 7 751331074538826
6 8 449873635430228
7 8 11298381761479```

### 输出

```
11360716373```

# 题解

## 作者：Genius_Star (赞：5)

### 思路：

赛时想了个状压，交了四五发，结果做法假了，回来打暴力。

首先传统思路，直接爆搜每一条是否选择，时间复杂度为 $O(2^M)$。

因为是一颗树，不能有环，可以用并查集维护一下，即如果两个点本身都在一个联通块，还要进行连接，那么肯定会组成环。

爆搜的时候对于并查集因为需要回溯，需要可持久化并查集维护，正准备“贺”一个板子过来，突然发现因为是树，最多选 $n-1$ 条边，即每搜完 $n-1$ 条边就检查一下答案（暴力建图，深搜判环），检查答案的时间复杂度是 $O(N)$。

这样的话总复杂度为：$O(C_{m}^{n-1} \times n)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
const ll N=40,M=9;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
ll n,m,k,cnt=0,ans=1e18;
struct Node{
	ll u,v,w;
}a[N];
stack<ll> s,t;
ll p[N],f[N];
vector<ll> E[N];
void add(ll u,ll v){
	E[u].push_back(v);
	E[v].push_back(u);
}
void DFS(ll u,ll fa){
	f[u]++;
	if(f[u]>1)
	  return ;
	for(auto v:E[u]){
		if(v==fa)
		  continue;
		DFS(v,u);
	}
}
void check(){
	if(!cnt)
	  return ;
	ll sum=0,F=1;
	memset(f,0,sizeof(f));
	for(int i=1;i<=n;i++)
	  E[i].clear();
	for(int i=1;i<=cnt;i++){
		add(a[p[i]].u,a[p[i]].v);
		sum=(sum+a[p[i]].w)%k;
	}
	DFS(1,1);
	for(int i=1;i<=n;i++)
	  if(f[i]>1||!f[i])
	    F=0;
	if(F)
	  ans=min(ans,sum);
}
void dfs(ll x,ll sum){
	if(sum==(n-1)){
		cnt=0;
		t=s;
		while(!t.empty()){
			p[++cnt]=t.top();
			t.pop();
		}
		check();
		return ;
	}
	if(x==(m+1))
	  return ;
	s.push(x);
	dfs(x+1,sum+1);
	s.pop();
	dfs(x+1,sum);
}
int main(){
	n=read(),m=read(),k=read();
	for(int i=1;i<=m;i++){
		a[i].u=read();
		a[i].v=read();
		a[i].w=read();
	}
	dfs(1,0);
	write(ans);
	return 0;
}
```


---

## 作者：robertuu (赞：5)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc328_e)

比较简单的一道暴力题。

一定要注意题目的数据范围：$1 \le N \le 8$。发现这道题和最小生成树算法没有任何关系。

显然，`prim` 和 `kruskal` 两种最小生成树算法在这道题中无法使用。因为这道题需要进行取模，而这两种算法只考虑这一步的最优（权值和最小），而会忽略后面的步可能会通过取模使得权值变小，导致出现错误（和 `Dijkstra` 不能处理有负权边的图差不多）。

由于 $N$ 实在太小，可以使用暴力，先确定 $1$ 号点为根节点，之后枚举每个点在生成树上的父亲（这时的父亲不能只枚举到当前点，需要枚举到 $N$，因为与这个点相连的点可能编号都比他大）。

在确定了所有点的父亲后，检验从每个点沿着父边能否走回 $1$ 号点（非法状态有两种：结尾不是 $1$ 号点、进入死循环）。如果验证满足条件，则用当前的权值和更新答案。

复杂度：搜索复杂度是 $O(N^{N-1})$，检验时由于需要对每个点进行操作，复杂度为 $O(N^2)$，总复杂度为 $O(N^{N+1})$。在 $N \le 8$ 的情况下可以轻松通过。

Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[9][9],k,ans = 1e18;
bool b[9][9];
int n,fa[9];
bool check() // 检验
{
	for(int i = 2;i <= n;i++)
	{
		int tmp = i;
		bool vis[9] = {};
		vis[tmp] = 1;
		while(1)
		{
			if(!fa[tmp])
			{
				if(tmp != 1) return 0; // 结尾不是 1 号点
				break;
			}
			tmp = fa[tmp];
			if(vis[tmp]) return 0; // 进入死循环
			vis[tmp] = 1;
		}
	}
	return 1;
}
void dfs(int x,long long now) // 搜索（同时存储当前权值和）
{
	if(x > n)
	{
		if(check()) ans = min(ans,now);
		return;
	}
	for(int i = 1;i <= n;i++)
		if(b[i][x])
		{
			fa[x] = i;
			dfs(x+1,(now+a[i][x])%k);
		}
}
int main()
{
	int m,x,y;
	long long z;
	cin >> n >> m >> k;
	for(int i = 1;i <= m;i++)
	{
		cin >> x >> y >> z;
		a[x][y] = a[y][x] = z;
		b[x][y] = b[y][x] = 1;
	}
	dfs(2,0);
	cout << ans;
	return 0;
}
```


---

## 作者：suyulong1212 (赞：3)

第一次写题解，希望能过。

这个题长得一脸最小生成树板子的样子，然而并不是，我们所要求的是模意义下的最小值。

但他毕竟是一颗生成树嘛，所以我们可以仿照生成树的思想，Kruskal 不太方便，我们可以试着采用 Prim 的思想（~~这样就不用写并查集了hh~~）。

类似 Prim 算法，我们进行 DFS，每次都找一条可以从生成树中的点扩展到不在生成树中的点的边，尝试加入生成树，这样我们当然是可以遍历所有生成树的，答案取最小值即可。

附上赛时代码如下：

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
bool vis[10];
int n, m, cnt;
int head[10];
ll mod;
struct edg
{
    int next, to;
    ll val;
} edge[100];
void add_edge(int u, int v, ll val)
{
    edge[++cnt].to = v;
    edge[cnt].next = head[u], edge[cnt].val = val;
    head[u] = cnt;
}
ll sum, ans = 0x3f3f3f3f3f3f3f3f;
void Prim(int x)
{
    if (x == n)
    {
        ans = min(ans, sum);
        return;
    }
    for (int u = 1; u <= n; u++)
    {
        if (!vis[u])
            continue;
        for (int i = head[u]; i; i = edge[i].next)
        {
            int v = edge[i].to;
            if (vis[v])
                continue;
            vis[v] = 1;
            sum = (sum + edge[i].val) % mod;
            Prim(x + 1);
            sum = (sum - edge[i].val + mod) % mod;
            vis[v] = 0;
        }
    }
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> n >> m >> mod;
    for (int i = 1; i <= m; i++)
    {
        int u, v;
        ll val;
        cin >> u >> v >> val;
        add_edge(u, v, val), add_edge(v, u, val);
    }
    q.push(1);
    vis[1] = 1;
    Prim(1);
    cout << ans;
    return 0;
}
```

---

## 作者：fantastic_dream (赞：3)

### 题目大意
求 $n$ 个点的无向图模 $k$ 意义下的最小生成树（$2 \leq n \leq 8$）。
### 解答
看到 $n$ 的范围，可以知道这题直接暴力就行了。

考虑从当前已经在生成树中的点出发，把与这些点相连且不在生成树内的点加入生成树中，若都在生成树中，就更新答案。这里用一个 dfs 实现，注意 $k$ 的范围，要开 long long。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m,k,tot,head[10],ans=1e16,vn;
struct ed{
	int v,ne,w;
}p[100];
bool vi[10];
void add(int u,int v,int w){
	p[++tot]={v,head[u],w};
	head[u]=tot;
}
void dfs(int u,int now){
	vi[u]=1;
	if(vn==n-1){
		ans=min(now,ans);
		return ;
	}
	for(int i=1;i<=n;i++){
		if(!vi[i])	continue;
		for(int j=head[i];j;j=p[j].ne){
			int v=p[j].v;
			if(vi[v])	continue;
			vi[v]=1,vn++,dfs(v,(now+p[j].w)%k),vn--,vi[v]=0;
		}
	}
}
main(){
	ios::sync_with_stdio(0);
	cin>>n>>m>>k;
	for(int i=1;i<=m;i++){
		int u,v,w;
		cin>>u>>v>>w;
		add(u,v,w),add(v,u,w);
	}
	dfs(1,0);
	cout<<ans;
	return 0;
}
```


---

## 作者：Tang_poetry_syndrome (赞：2)

## [ABC328E] Modulo MST
### 思路
最近状压 DP 写多了，看啥都像状压，来篇状压 + dfs。  
首先定义状态 $s$，其二进制下第 $i$ 为代表选取第 $i$ 条边 $(0\le i \le m)$。  
将所有边塞入一个 `vector` 所建的图中，dfs 跑图，将遍历到的点标记。如果每个点都被标记了，则该方案合法，将全部合法方案的代价取最小值即答案。  
最后，根据树的性质进行剪枝：一颗 $n$ 个节点的树有 $n-1$ 条边。那么当方案边数不为 $n-1$ 时，答案一定不合法。这里提供一个函数 `__builtin_popcount(x)`，作用是求一个十进制数 $x$ 在二进制下有多少位为 $1$。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define f(i,j,k) for(register ll i=j;i<=k;++i)
#define g(i,j,k) for(register ll i=j;i>=k;--i)
#define pb push_back
#define pii pair<int,int>
#define pll pair<ll,ll>
using namespace std;
ll n,m,k,u[35],v[35],fa[15];
ll ans=LONG_LONG_MAX,w[35];
vector<ll> g[15];
bool vis[15];
void dfs(ll x){
	if(vis[x])return;
	vis[x]=1;
	if(!g[x].empty())
	f(i,0,g[x].size()-1)dfs(g[x][i]);
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>m>>k;
	f(i,1,m)cin>>u[i]>>v[i]>>w[i];
	f(i,0,(1<<m)-1){
		if(__builtin_popcount(i)!=n-1)continue;
		f(j,1,n)g[j].clear(),vis[j]=false;
		ll sum=0;
		f(j,1,m)if(i&(1ll<<j-1))g[u[j]].pb(v[j]),g[v[j]].pb(u[j]),sum=(sum+w[j])%k;
		bool flag=true;
		dfs(1);
		f(j,1,n)flag&=vis[j];
		if(flag)ans=min(ans,sum);
	}
	cout<<ans;
	return 0;
} 
```

---

## 作者：cjh20090318 (赞：2)

不是很难的 ABC E，甚至相比于以前的简单。

## 题意

给你一个 $N$ 个点 $M$ 条边的图，求出这个图在模 $K$ 意义下的最小生成树。

## 分析

观察到数据范围其实很小，所以先从朴素算法开始分析，考虑直接枚举子集。

但是每个子集组成的边不一定是一棵树，一棵树显然要满足任意两个点之间有且只有一条边连接。

所以枚举边集有且仅能有 $N-1$ 个元素，且连接后仅有一个连通块，这个并查集处理即可。

所以时间复杂度是 $O(nC_m^{n-1})$，~~但是因为本人懒得写搜索直接用的枚举二进制位。~~

## 代码

```cpp
//the code is from chenjh
#include<cstdio>
#include<algorithm>
typedef long long LL;
int n,m;
LL k;
struct Edge{
	int u,v;
	LL w;
}e[30];
int f[10];
int fd(const int x){return x==f[x]?x:f[x]=fd(f[x]);}//并查集路径压缩找根。
int main(){
	scanf("%d%d%lld",&n,&m,&k);
	for(int i=0;i<m;i++) scanf("%d%d%lld",&e[i].u,&e[i].v,&e[i].w);
	LL s=k;
	for(unsigned int x=0,mx=1u<<m;x<mx;x++)if(__builtin_popcount(x)==n-1){//判断是否刚好选了 n-1 条边。
		f[1]=1,f[2]=2,f[3]=3,f[4]=4,f[5]=5,f[6]=6,f[7]=7,f[8]=8;//对并查集进行初始化，循环展开加快速度。
		bool sol=1;LL w=0;
		int g=n;//连通块数量。
		for(int i=0;i<m;i++)if((x>>i)&1){
			if(fd(e[i].u)==fd(e[i].v)){sol=0;break;}//每两点之间有且仅有一条路径，如果已经连接说明不合法。
			f[fd(e[i].u)]=fd(e[i].v),--g;//成功合并一次减少一个连通块。
			w=(w+e[i].w)%k;
		}
		if(sol && g==1) s=s<w?s:w;//合法就取最小值。
	}
	printf("%lld\n",s);
	return 0;
}

```

---

## 作者：Redshift_Shine (赞：1)

# [Modulo MST](https://www.luogu.com.cn/problem/AT_abc328_e)

有人曰过：

> 这道题的并查集一定不要使用路径压缩！！

还有人曰过：

> 这道题的时间复杂度是 $O(m2^m)$ 。

但是我想说：

> 这道题的并查集可以使用路径压缩。
>
> 这道题的最大时间复杂度是 $O(C_{28}^7)$ 。

这道题的核心思路并不在深搜。

实际上，因为一个生成树一定会使用 $(n-1)$ 条边，所以我们可以直接用 $(n-1)$ 层循环枚举所有的边选法，然后用并查集判断每个方案是否可行。

我们可以直接使用一个 `array` 容器，每层循环的时候 `copy` 一份，就可以使用路径压缩还不会影响之前的并查集。而且最好边判断边加入而不是每次枚举完再判断，这样可以让消耗时间少很多。

为了展示一下 `array` 怎么用，我把代码放在这里。

```c++
#include<iostream>
#include<array>
#include<tuple>
#include<vector>
using namespace std;
using ll=long long;
using tpf=array<int,9>;
tpf fa;
inline int find(tpf& fa,int x){
    return x==fa[x]?x:fa[x]=find(fa,fa[x]);
}
inline void merge(tpf& fa,int x,int y){
    fa[find(fa,x)]=find(fa,y);
}
int n,m,x,y;
ll k,z,res=0x3f3f3f3f3f3f3f3f;
vector<tuple<int,int,ll>> vec;
void dfs(tpf& fa,int x,int ref,ll val){
    if(!ref){
        res=min(res,val);
        return;
    }
    for(int i=x;i<=m-ref;i++){
        auto& [a,b,va]=vec[i];
        if(find(fa,a)==find(fa,b))continue;
        tpf tmp=fa;
        merge(tmp,a,b);
        dfs(tmp,i+1,ref-1,(val+va)%k);
    }
}
int main(){
    cin>>n>>m>>k;
    for(int i=1;i<=n;i++)fa[i]=i;
    for(int i=1;i<=m;i++){
        cin>>x>>y>>z;
        vec.push_back({x,y,z});
    }
    dfs(fa,0,n-1,0ll);
    cout<<res<<'\n';
}
```

时间复杂度不高，因为 $C_{28}^7=1184040$ 。用时最大的点只跑了 11ms 。

---

## 作者：_smart_stupid_ (赞：1)

# [题目](https://www.luogu.com.cn/problem/AT_abc328_e)

### 思路：

这个题看似很难，我赛时以为有很巧妙的做法，赛后看数据范围才知道是暴力。

$ 2\leq\ N\leq8 $

$ N-1\leq\ M\leq\dfrac{N(N-1)}2 $

数据范围不大，可以用 DFS 加剪枝通过。

### 剪枝方法：

题目求最小生成树，只需要 $n - 1$ 条边就可以构成最小生成树。在搜索时用一个变量记录选择了多少条边，看到一条边，当我们选择的边数加上这条边不超过 $n - 1$ 条时才选择这条边继续搜索下去。

### 判断合法：

在搜索结束时，也就是所有的边都搜完了，判断选择的变数是否等于 $n - 1$，如果少了立刻判断为不合法，然后用并查集判断是否出现环，出现了环也立刻判断为不合法，如果没有环就统计变权的和，注意要模上 $k$。

### 为什么不能用克鲁斯卡尔？

这道题要求模数最小生成树，有些生成树边权和可能不是最大，也可能不是最小，但是他的模数边权可能就是最大或最小的。

### 细节：

题目已经强调过了，开 int 可能会爆，而且，答案可能会大于 $2 \times 10 ^ 9$，所以答案初始值应设为 $9 \times 10 ^ {17} $。

### AC Code：

```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<vector>
#include<queue>
#include<stack>
#include<list>
#include<set>
#include<map>
using namespace std;
int n,m;
long long k;
struct edge{
	int u,v;
	long long w;
};
edge a[30];
long long ans=900000000000000000ll;
bool vis[30];
int f[30];
int get(int x){
	if(f[x]==x) return x;
	return get(f[x]);
}
void dfs(int dep,int choose){
	if(dep==m+1){
		if(choose==n-1){
			for(int i=1;i<=n;i++) f[i]=i;
			// 判环
			bool flag=0;
			for(int i=1;i<=m;i++){
				if(vis[i]){
					if(get(a[i].u)!=get(a[i].v)){
						f[get(a[i].u)]=get(a[i].v);
					}
					else{
						flag=1;
					}
				}
			}
			// 求值
			if(flag==0){
				long long cnt=0;
				for(int i=1;i<=m;i++){
					if(vis[i]){
						cnt+=a[i].w;
						cnt%=k;
					}
				}
				cnt%=k;
				ans=min(ans,cnt);
			}
		}
		return ;
	}
	if(choose<n-1){
		vis[dep]=1;
		dfs(dep+1,choose+1);
		vis[dep]=0;
	}
	dfs(dep+1,choose);
}
int main(){
	scanf("%d%d%lld",&n,&m,&k);
	for(int i=1;i<=m;i++){
		scanf("%d%d%lld",&a[i].u,&a[i].v,&a[i].w);
	}
	dfs(1,0);
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：fcy20180201 (赞：1)

## 题意
给定一个 $N$ 个点 $M$ 条边的简单无向连通图，求这张图生成树模 $K$ 的最小值。

## 解法
温馨提示：做题一定要看数据范围，这题居然 $N \le 8$ ！！！

首先直接二进制枚举每条边肯定不行，所以考虑剪枝。因为生成树只有 $N-1$ 条边，所以当已经取的边达到 $N-1$ 时别的边就不能取了，当已经取的边加还未决定的边小于 $N-1$ 时就可以直接返回。但由于并查集不可逆，所以连通性只能在最后检查。时间复杂度 $O(C^{N-1}_ M \times N)$ 可以过。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=long long;//不开 long long 见祖宗。
int n,m,f[10]; 
ll k,ans=1e16;
vector<int>con[10];
struct edge{
	int u,v;
	ll w;
}ed[35];
int ff(int g){return f[g]==g?g:f[g]=ff(f[g]);}//并查集
vector<edge>v;
void dfs(int t,int cnt){
	if(m-t+1+cnt<n-1)return ;//如果已经取的边加还未决定的边小于 N-1 时就直接返回。
	if(t>m){
		for(int i=1;i<=n;i++)f[i]=i;
		ll sum=0;
		for(edge x:v){
			if(ff(x.u)==ff(x.v))return ;//如果形成环，直接退出。
			f[ff(x.u)]=f[x.v],sum=(sum+x.w)%k;
		}
		ans=min(ans,sum);
		return ;
	}
	dfs(t+1,cnt);
	if(cnt<n-1){//如果还未取到 N-1 条边，可以取。
		v.push_back(ed[t]);
		dfs(t+1,cnt+1);
		v.pop_back();
	}
	return ;
}

int main(){
	scanf("%d%d%lld",&n,&m,&k);
	for(int i=1;i<=m;i++){
		int u,v;ll w;
		scanf("%d%d%lld",&u,&v,&w);
		ed[i]={u,v,w};
	}
	dfs(1,0);
	printf("%lld",ans);
	return 0;
}

```

---

## 作者：Mr_Biantainne (赞：1)

**Upd: 修复了一些小问题。**
## 题意简述
有一个 $N$ 个节点 $M$ 条边的带权无向图，你需要挑出一些边建造生成树。对于每一棵生成树，都有一个边权和 $T$。你需要求出所有 $T$ 对给定值 $K$ 求余的值中最小的是多少。
## 题意分析
先看数据范围：
- $2 \le N \le 8$
- $N-1 \le M \le \frac{N(N-1)}{2}$

即：$1 \le M \le 28$。

枚举每条边是否选择，再加上检查满足要求的时间，总复杂度为 $O(n \times 2^m)$，再剪一剪枝，不会超时。显然就是爆搜！
## 解法介绍
选边的操作不难，直接 DFS，难点主要在剪枝。

**剪枝策略：**
如果这条边上的两个点 $u_i$ 与 $v_i$ 已经通过边间接连接在一起了，那么这条边就无需添加上去了。

怎么知道两个点是否连接？那就可以使用**并查集**！

在搜索时，对于一条边，有加上和不加两种情况。加上的时候使用并查集，回溯时返回初始状态。**提醒一下大家：由于有回溯，所以并查集千万不要使用路径压缩！我调了半小时才调出来！**
## 代码
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll n, m, k, u[30], v[30], w[30], fa[10], ans = 1e18, recp;
ll find(ll now)
{
	if (fa[now] == now) return now;
	return find(fa[now]); //不要路径压缩！
}
void dfs(ll now)
{
	if (now == m + 1) //搜索完成
	{
		ll num = find(1);
		for (ll i = 2; i <= n; i++) if (find(i) != num) return; //如果还没有完全连通就不满足要求
		ans = min(ans, recp % k); //计算答案
		return;
	}
	ll a = u[now], b = v[now], lst;
	ll ka = find(a), kb = find(b);
	if (ka == kb) goto there; //a 和 b 已经连接，不要增加这条边
	lst = fa[ka];
	fa[ka] = kb; //连接 a 和 b
	recp += w[now]; //更新答案
	dfs(now + 1); //选择这条边
	fa[ka] = lst; //回溯
	recp -= w[now]; //回溯
	there:;
	dfs(now + 1); //不选这条边
}
int main()
{
	cin >> n >> m >> k;
	for (ll i = 1; i <= n; i++) fa[i] = i; //初始化并查集
	for (ll i = 1; i <= m; i++) cin >> u[i] >> v[i] >> w[i];
	dfs(1);
	cout << ans;
}
```
**Max Exec time = 23ms**，还可以。

---

## 作者：Mortidesperatslav (赞：0)

卡常题，害得我白吃一堆罚时。

这道题很显然暴力吧。

$n \leq 8$，那么往大了算，就算 $m \leq 64$（直接看做 $n^2$），最后选法数也只有 $6 \times 10^8$。况且 $m$ 还远远不到这么大，只有 $28$，方法数只有 $10^6$，那么完全是可以过的。写个搜索就行了。

关键在于判环。我们可以采用并查集 $O(\log n)$ 判是否合法，如果两个点祖先相同，那么就不取。

讲到这里，很显然要用 dfs 做。

但是注意到 $7!=5040$，排列数会超过 $10^9$，要 hash 一下判重。

问题就出在这里。

用了 `map`，开了 O3，还是超时两个点（样例一个，数据一个）。

所以这题还得用 pbds 卡过去。pbds 可以看洛谷日报第 39 期，这里不详细讲了。

然后我们惊奇地发现，用了 pbds 不开 O2 都能稳过。

```cpp
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include<ext/pb_ds/hash_policy.hpp>
#include<ext/pb_ds/trie_policy.hpp>
#include<ext/pb_ds/priority_queue.hpp>
using namespace __gnu_pbds;
using namespace std;
int n,m;
long long k,ans=LLONG_MAX;//LLONG_MAX = 2^{63}-1
struct node{
	int u,v;
	long long c;
}p[66];
int fa[10];
bool vis[66];
gp_hash_table<long long,bool>vvis;
int find(int x){//并查集
	if(fa[x]==x)return x;
	return find(fa[x]);
}
void dfs(int kth,long long val){
	if(kth==n-1){
		//cout<<val<<"\n";
		ans=min(ans,val%k);//肯定合法，直接求 min
		return;
	}
	for(int i=1;i<=m;i++){
		if(vis[i]==1)continue;
		int zu=find(p[i].u),zv=find(p[i].v);
		if(zu==zv)continue;
		if(vvis[val+kth])continue;		
		fa[zu]=zv;//并查集，注意到这些处理都在 continue 下面，因为如果不这样会导致更新了却没有更新回去
		vis[i]=1;//搜过的边不能搜了
		dfs(kth+1,(val+p[i].c)%k);//爆搜
		vis[i]=0;
		fa[zu]=zu;
	}
	vvis[val+kth]=1;//注意要记录一下当前状态，否则会重复搜大量相同状态
}
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n>>m>>k;
	for(int i=1;i<=m;i++)cin>>p[i].u>>p[i].v>>p[i].c;
	for(int i=1;i<=n;i++)fa[i]=i;
	dfs(0,0);//爆搜
	cout<<ans;
}
```

---

## 作者：allenchoi (赞：0)

## 科技：  
搜索，剪枝，并查集  
## 思路：  
直接 $O(2^m)$ 搜索，加入如下剪枝：  
如果将剩余的边全部加入仍不足以构成一棵树，那么不继续搜索；  
如果尝试加入一条边的时候发现两点已属于一个连通块（并查集判断），则不继续搜索。  
注意由于并查集要撤销，所以不能路径压缩，只能按秩合并。  
## 代码：  
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,m,f[10],siz[10];
ll k,minn;
struct Edge
{
	int a,b;
	ll c;
} e[30];
int find(int x)
{
	while(f[x] != x) x = f[x];
	return x;
}
void dfs(int x,int c,ll s)
{
	if(x > m)
	{
		if(c == n - 1) minn = min(minn,s);
		return ;
	}
	if(m - x >= n - 1 - c) dfs(x + 1,c,s);
	if(find(e[x].a) != find(e[x].b))
	{
		int fx = find(e[x].a),fy = find(e[x].b);
		if(siz[fx] > siz[fy]) swap(fx,fy);
		f[fx] = fy,siz[fy] += siz[fx];
		dfs(x + 1,c + 1,(s + e[x].c) % k);
		f[fx] = fx,siz[fy] -= siz[fx];
	}
}
int main()
{
	scanf("%d%d%lld",&n,&m,&k);
	for(int i = 1;i <= m;i++) scanf("%d%d%lld",&e[i].a,&e[i].b,&e[i].c);
	for(int i = 1;i <= n;i++) f[i] = i,siz[i] = 1;
	minn = 1e17;
	dfs(1,0,0);
	printf("%lld\n",minn);
	return 0;
}
```

---

## 作者：_Chronostatis_ (赞：0)

# Modulo MST 题解
## Description
> 有一个 $N$ 个节点 $M$ 条边的无向带权图，你需要选出一些边建造生成树。对于每一棵生成树，都有一个边权和 $T$。你需要求出所有 $T$ 对给定值 $K$ 求余的值中最小的是多少。

## Solution
看到这么小的数据范围，你想到了什么？我想到了爆搜！

组合搜索加剪枝，搜出 $N - 1$ 条边，然后检查选出来的边是否可以构成一棵树，如果可以就更新答案。

## Accept Code
```cpp
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 9;

struct Edge {
  int u, v;
  long long w;
} s[(MAXN + 1) * MAXN / 2];

int n, m;
bool flag[MAXN][MAXN], v[MAXN];
vector<int> e[MAXN];
long long k, ans = LLONG_MAX;

void GraphS(int u) { // 遍历
  if (v[u]) {
    return;
  }
  v[u] = 1;
  for (int i : e[u]) {
    if (flag[u][i]) {
      GraphS(i);
    }
  }
}

bool CheckT() { // 检查是否是一棵树
  fill(v + 1, v + n + 1, 0);
  GraphS(1);
  for (int i = 1; i <= n; ++i) {
    if (!v[i]) {
      return 0;
    }
  }
  return 1;
}

void CombS(int last, int pos, long long cnt) { // 组合搜索
  if (pos == n - 1) {
    if (CheckT()) {
      ans = min(ans, cnt);
    }
    return;
  }
  for (int i = last + 1; i <= m; ++i) {
    flag[s[i].u][s[i].v] = flag[s[i].v][s[i].u] = 1;
    CombS(i, pos + 1, (cnt + s[i].w % k) % k);
    flag[s[i].u][s[i].v] = flag[s[i].v][s[i].u] = 0;
  }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> n >> m >> k;
  for (int i = 1; i <= m; ++i) {
    cin >> s[i].u >> s[i].v >> s[i].w;
    e[s[i].u].push_back(s[i].v);
    e[s[i].v].push_back(s[i].u);
  }
  CombS(0, 0, 0);
  cout << ans;
  return 0;
}
```

---

## 作者：incra (赞：0)

### [题目链接](https://www.luogu.com.cn/problem/AT_abc328_e)
### 题解
考虑 $m=\frac{n(n-1)}{2}=28$ 很小，但是 $O(n2^m)$ 会超时，故考虑组合式爆搜，从 $m$ 条边里选出 $n-1$ 条边（最小生成树的性质），时间复杂度 $O(nC_m^{n-1})$。

注意判断是否连通时可以用**带有路径压缩的并查集**，但是要记得备份，，不用路径压缩的并查集即为可撤销并查集。~~显然我不会。~~

比赛时觉得过不了没写，估计全场就我一个做出了 ABCF 的人。。。
### 代码
```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <iomanip>
#include <algorithm>
#include <bitset>
#include <cmath>
#include <map>
#include <set>
#define x first
#define y second
#define pb push_back
#define desktop "C:\\Users\\incra\\Desktop\\"
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef pair <int,int> PII;
const int dx[] = {1,0,-1,0},dy[] = {0,-1,0,1};
bool LAST = false;
istream& operator >> (istream& in,char* s) {
    if (LAST) return in;
	char ch = cin.get ();
	while ((isspace (ch) || ch == '\n') && ch != EOF) ch = cin.get ();
	int n = 0;
	while (!(isspace (ch) || ch == '\n') && ch != EOF) s[n++] = ch,ch = cin.get ();
	s[n] = '\0';
	if (ch == EOF) LAST = true;
	return in;
}
template <typename T1,typename T2> bool tomax (T1 &x,T2 y) {
	if (y > x) return x = y,true;
	return false;
}
template <typename T1,typename T2> bool tomin (T1 &x,T2 y) {
	if (y < x) return x = y,true;
	return false;
}
LL power (LL a,LL b,LL p) {
	LL ans = 1;
	while (b) {
		if (b & 1) ans = ans * a % p;
		a = a * a % p;
		b >>= 1;
	}
	return ans;
}
const int N = 10;
int n,m;
LL k;
int p[N],bp[N][N];
struct edge {
	int a,b;
	LL w;
}e[N * N];
int find (int x) {
	if (p[x] != x) return find (p[x]);
	return x;
}
LL ans;
LL res;
void DFS (int u,int last) {
//	cout << u << ' ' << res << endl;
	if (u == n) {
		ans = min (ans,res);
		return ;
	}
	for (int i = last;i <= m;i++) {
		if (find (e[i].a) == find (e[i].b)) continue;
		memcpy (bp[u],p,sizeof (p));
		p[find (e[i].a)] = find (e[i].b);
		LL bres = res;
		res = (res + e[i].w) % k;
		DFS (u + 1,i + 1);
		memcpy (p,bp[u],sizeof (p));
		res = bres;
	}
}
int main () {
	cin >> n >> m >> k;
	for (int i = 1;i <= n;i++) p[i] = i;
	ans = k - 1;
	for (int i = 1;i <= m;i++) {
		int a,b;
		LL w;
		cin >> a >> b >> w;
		e[i] = {a,b,w % k};
	}
	DFS (1,1);
	cout << ans << endl;
	return 0;
}
```

---

## 作者：PikachuQAQ (赞：0)

## Description

[Link](https://www.luogu.com.cn/problem/AT_abc328_e)

给定一张简单无向图，请你求出在模 $k$ 意义下的最小生成树。

## Solution

[**UPD: 跑的非常优秀，耗时 100ms。**](https://atcoder.jp/contests/abc328/submissions/47518821)

这个题目由于数据范围极小，各种乱搞也可以过，这也是我第一次赛时过 E。

首先知道我们只需要 $n-1$ 条边，那么我们可以考虑枚举边来暴力求。

怎么暴力求呢？

构造一个序列 $a$，使得其长度为 $m$，并且最后 $n-1$ 个数为 $1$，其他都为 $0$。

举个例子，当 $\begin{cases}n=3\\m=6\end{cases}$ 时：

$a=\{0,0,0,1,1\}$

这是什么意思？

这是一个模拟了选取边的数列，其中的 $0$ 表示没有选这条边，$1$ 就表示选了这条边，当前状态的答案加上这条边的边权然后模 $k$。

然后如果你会 `next_permutation`，你就可以枚举这个 $a$ 序列的所有情况，也就是选 $n-1$ 条边的所有情况。

选完边之后，我们还要判合法性。根据最小生成树的定义，我们要判掉两种情况：有环的和不连通的。这个可以用并查集解决。

如果这个状态合法，我们将答案和当前状态答案取最小值给答案即可。

这题要注意，该开 `long long` 的要开，不要被坑了。

## Code

```cpp
// 2023/11/11 PikachuQAQ

#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

const int kMaxN = 80;
const ll INF = 1e18;

int fa[kMaxN], siz[kMaxN];

int findfa(int x) {
    return (fa[x] == x) ? x : (fa[x] = findfa(fa[x]));
}

void uni(int x, int y) {
    int u = findfa(x), v = findfa(y);
    if (siz[u] > siz[v]) {
        swap(u, v);
    }
    fa[u] = v, siz[v] = siz[u];
}

ll k, ans = INF, w[kMaxN], res;
int n, m, vis[kMaxN], u[kMaxN], v[kMaxN], a[kMaxN], f;

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m >> k;
    for (int i = 1; i <= m; i++) {
        cin >> u[i] >> v[i] >> w[i];
        w[i] %= k;
    }
    for (int i = m; i > m - n + 1; i--) {
        a[i] = 1;
    }
    do {
        f = 1;
        for (int i = 1; i <= n; i++) {
            fa[i] = i, siz[i] = 1;
        }
        for (int j = 1; j <= m; j++) {
            if (a[j]) {
                if (findfa(u[j]) == findfa(v[j])) {
                    f = 0;
                    break;
                }
                uni(u[j], v[j]);
                res += w[j], res %= k;
            }
        }
        int rt = findfa(1);
        for (int j = 1; j <= n; j++) {
            if (findfa(j) ^ rt || f == 0) {
                f = 0;
                break;
            }
        }
        if (f) {
            ans = min(ans, res);
        }
        res = 0, fill(vis + 1, vis + n + 1, 0);
    } while (next_permutation(a + 1, a + m + 1));
    cout << ans << '\n';

    return 0;
}
```

---

## 作者：Natori (赞：0)

>[ABC328E Modulo MST](https://www.luogu.com.cn/problem/AT_abc328_e)

考场上以为这个题有什么很巧妙的做法，结果想半天没想出来。反正 $m \le 28$，果断爆搜，加点剪枝居然就过了。。。

------------
正如上面所提到的，考虑爆搜。

DFS 枚举每条边是否要选，枚举完之后先用并查集判断是不是树（就是有没有环），然后求当前方案的答案，与最终答案 $ans$ 取较小值。

这样做时间复杂度是 $\mathcal{O}(m2^m)$ 的，还要加上并查集，应该过不了吧？

现在来一个玄学优化的进行！

我是先把并查集加上了启发式合并，就是在维护代表元之外再维护每个集合的大小，每次都令小的集合合并到大的集合。~~赛后感觉并没有什么用，甚至增大常数~~

然后是一个比较关键的东西。在 DFS 的参数中加入 $num$ 表示当前选了多少边，如果 DFS 到底层节点发现 $num \not= n-1$，直接 ```return``` 即可。

还有就是在判断是否是树时，如果已经出现环，直接结束。

加上这三个优化就可以通过这道题，最大测试点 725 ms。

赛后一看，这个测试点居然是样例三。。。

于是我们使用广为人知的方法，可以做到最大测试点 221 ms（（（

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
bool Mbegin;
void File_Work(){
	freopen("test.in","r",stdin);
	freopen("test.out","w",stdout);
}
const int N=18,M=38;
int n,m,mod,from[M],to[M],cost[M];
struct Disjoint_Set_Union{
	int fa[N],siz[N];
	void init(){
		for(int i=1;i<=n;i++){
			fa[i]=i;
			siz[i]=1;
		}
	}
	int find(int x){
		return fa[x]==x?x:fa[x]=find(fa[x]);
	}
	void unite(int x,int y){
		x=find(x),y=find(y);
		if(x==y)
			return;
		if(siz[x]<siz[y])
			swap(x,y);
		fa[y]=x;
		siz[x]+=siz[y];
	}
}dsu;
int cnt;
int ans;
int eid[M];
bool vis[M];
void dfs(int dep,int num){
	if(dep>m){
		if(num!=n-1)
			return;
		int en=0;
		for(int i=1;i<=m;i++)
			if(vis[i]==1)
				eid[++en]=i;
		dsu.init();
		int res=0;
		for(int i=1;i<=n-1;i++){
			int u=from[eid[i]],v=to[eid[i]],w=cost[eid[i]];
			int uu=dsu.find(u),vv=dsu.find(v);
			if(uu==vv)
				return;
			dsu.unite(uu,vv);
			res=(res+w)%mod;
		}
//		for(int i=1;i<=n-1;i++)
//			cerr<<eid[i]<<' ';
//		cerr<<'\n';
//		cerr<<res<<"\n\n";
		ans=min(ans,res);
		return;
	}
	vis[dep]=1;
	dfs(dep+1,num+1);
	vis[dep]=0;
	dfs(dep+1,num);
}
bool Mend;
signed main(){
//	File_Work();
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cerr<<fixed<<setprecision(3)<<(&Mbegin-&Mend)/1048576.0<<" MB\n\n\n";
	cin>>n>>m>>mod;
	for(int i=1;i<=m;i++)
		cin>>from[i]>>to[i]>>cost[i];
	ans=mod;
	dfs(1,0);
	cout<<ans;
	cerr<<"\n\n\n"<<fixed<<setprecision(0)<<1e3*clock()/CLOCKS_PER_SEC<<" ms";
	return 0;
}
```

---

## 作者：qqqaaazzz_qwq (赞：0)

直接做肯定没法做，但观察到数据范围很小，所以我们考虑暴力枚举。

枚举从 $m$ 条边里选出 $n-1$ 条边的方案，再检查能否构成一棵生成树，若能，则更新答案。情况最多也就 $C(28,7)=1184040$ 种，足以通过此题。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,m,k;
int ans;
int u[40],v[40],w[40];
bool vis[40];
int p[40];

int find(int x)
{
	if(p[x]!=x) p[x] = find(p[x]);
	return p[x];
}

void check()
{
	for (int i=1;i<=n;i++) p[i] = i;
	int res = 0;
	for (int i=1;i<=m;i++)
	{
		if(vis[i]==true)
		{
			if(find(u[i])==find(v[i])) return;
			p[find(u[i])] = find(v[i]);
			res = (res+w[i])%k;
		}
	}
	ans = min(ans,res);
	return;
}

void dfs(int d,int c)
{
	if(c>(n-1)||c+(m-d+1)<(n-1)) return; 
	if(d==m+1)
	{
		check();
		return;
	}
	vis[d] = true;
	dfs(d+1,c+1);
	vis[d] = false;
	dfs(d+1,c);
	return;
}

signed main()
{
	cin >> n >> m >> k;
	ans = k;
	for (int i=1;i<=m;i++) cin >> u[i] >> v[i] >> w[i];
	dfs(1,0);
	cout << ans << "\n";
	return 0;
}
```

---

## 作者：HDS_Acenaphthylene (赞：0)

题目大意：求一个图的生成树的边权对 $K$ 取模的最小值。

$N\le 8$，暴搜枚举所有生成树即可。

注意，看上去这种算法是 $O(2^M)$ 的，但是其实不考虑两端点已经连通，时间复杂度也不超过 $ C_M^{N-1} = \frac{28!}{7!21!} = 1184040$。

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n, m, k;
pair<int, pair<int, int> > e[100];
int ans, cnt;
int f[10];
int find(int x){return (f[x] == x) ? x : find(f[x]);}
void dfs(int now, int x) {
	if(cnt == n - 1) ans = min(ans, x);
	if(now > m)return;
	dfs(now + 1, x);
	int u = e[now].second.first, v = e[now].second.second, w = e[now].first;
	if(find(u) != find(v)) {
		u = find(u), v= find(v);
		f[u] = v;
		cnt ++;
		dfs(now + 1, (x + w) % k);
		cnt --;
		f[u] = u;
	}
}
signed main() {
	cin >> n >> m >> k;
	ans = k;
	for(int i = 1;i <= n;i ++)f[i] = i;
	for(int i = 1;i <= m;i ++)cin >> e[i].second.first >> e[i].second.second >> e[i].first;
	dfs(1, 0);
	cout << ans;
	return 0;
}
```

---

## 作者：ilibilib (赞：0)

### 题目大意：

给出一个简单无向联通图，求**取模后**最小的生成树费用。

### 题目分析：

我们发现题目中给出 $N$ 和 $M$ 的取值范围很小。

所以直接**爆搜**。

```cpp
include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,k,ans=1e17;
struct node{int u,v,w;} tu[50];
bool bl[10];//标记这个点有没有被遍历
void dfs(int cnt,int sum)//cnt记录已经遍历几个点,sum是取模后生成树的费用
{
	if(cnt==n) {ans=sum<ans?sum:ans;return;}
	for(int i=1;i<=m;++i)//遍历每条边
		{
			if(bl[tu[i].u]&&!bl[tu[i].v])
			{
				bl[tu[i].v]=true;
				dfs(cnt+1,(sum+tu[i].w)%k);
				bl[tu[i].v]=false;
			}
			else if(!bl[tu[i].u]&&bl[tu[i].v])
			{
				bl[tu[i].u]=true;
				dfs(cnt+1,(sum+tu[i].w)%k);
				bl[tu[i].u]=false;
			}
		}
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>m>>k;
	int a,b,c;
	for(int i=1;i<=m;++i)
	{
		cin>>a>>b>>c;
		tu[i]={a,b,c};//记录边
	}
	for(int i=1;i<=n;++i)//以每个点为起点生成生成树
	{
		bl[i]=true;
		dfs(1,0);
		bl[i]=false;
	}
	cout<<ans;
	return 0;
}
```



---

