# [ABC352E] Clique Connect

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc352/tasks/abc352_e

$ N $ 頂点からなる重み付き無向グラフ $ G $ があります。 $ G $ の各頂点には $ 1 $ から $ N $ までの番号が付けられています。 最初、$ G $ には辺が $ 1 $ 本も存在しません。

今から、$ M $ 回の操作を行うことによって $ G $ に辺を追加していきます。 $ i\ (1\leq\ i\leq\ M) $ 回目の操作は以下の通りです。

- $ K_i $ 頂点からなる頂点の部分集合 $ S_i=\lbrace\ A_{i,1},A_{i,2},\dots,A_{i,K_i}\rbrace $ が与えられる。 $ u,v\in\ S_i $ かつ $ u\ <\ v $ を満たす全ての $ u,v $ について、頂点 $ u $ と頂点 $ v $ の間に重み $ C_i $ の辺を追加する。

$ M $ 回の操作を全て行ったとき $ G $ が連結になるか判定し、連結になるならば $ G $ の最小全域木に含まれる辺の重みの総和を求めてください。

## 说明/提示

### 制約

- $ 2\leq\ N\ \leq\ 2\times\ 10^5 $
- $ 1\leq\ M\ \leq\ 2\times\ 10^5 $
- $ 2\leq\ K_i\ \leq\ N $
- $ \displaystyle\ \sum_{i=1}^{M}\ K_i\ \leq\ 4\times\ 10^5 $
- $ 1\leq\ A_{i,1}\ <\ A_{i,2}\ <\ \dots\ <\ A_{i,K_i}\leq\ N $
- $ 1\leq\ C_i\leq\ 10^9 $
- 入力は全て整数

### Sample Explanation 1

!\[\](https://img.atcoder.jp/abc352/b54e4b0cfe2f7e5974a2b95be370953a.png) 左の図は $ M $ 回の操作を全て行ったあとの $ G $ を、右の図はその最小全域木の $ 1 $ つを表しています（辺の横に書かれた数はその辺の重みを示します）。 最小全域木に含まれる辺の重みの総和は $ 3+2+4=9 $ です。

### Sample Explanation 2

$ M $ 回の操作を全て行っても $ G $ は連結になりません。

## 样例 #1

### 输入

```
4 3
3 3
1 2 3
2 2
1 2
3 4
1 3 4```

### 输出

```
9```

## 样例 #2

### 输入

```
3 2
2 1
1 2
2 1
1 2```

### 输出

```
-1```

## 样例 #3

### 输入

```
10 5
6 158260522
1 3 6 8 9 10
10 877914575
1 2 3 4 5 6 7 8 9 10
4 602436426
2 6 7 9
6 24979445
2 3 4 5 8 10
4 861648772
2 4 8 9```

### 输出

```
1202115217```

# 题解

## 作者：kkxacj (赞：4)

#### 思路

显然，我们不能暴力加边，容易发现，题目求得是求最小生成树中各条边的总重，可以考虑把所有加边操作按 $c_i$ 从小到大排序，按建最小生成树的方法，可以用并查集看这 $k_i$ 个数有几个连通块，然后贡献就为连通块个数减一乘上 $c_i$，之后再将几个连通块都连成一个连通块。

最后看一下是否有多个连通块，有多个就无解，否则输出答案。

**code**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
namespace IO
{
	template<typename T>
	void Read(T &_x){_x=0;int _f=1;char ch=getchar();while(!isdigit(ch)) _f=(ch=='-'?-1:_f),ch=getchar();while(isdigit(ch)) _x=_x*10+(ch^48),ch=getchar();_x*=_f;}
	template<typename T,typename... Args>
	void Read(T &_x,Args&...others){Read(_x);Read(others...);}
	const int BUF=20000000;char buf[BUF],top,stk[32];int plen;
	#define pc(x) buf[plen++]=x
	#define flush(); fwrite(buf,1,plen,stdout),plen=0;
	template<typename T>inline void print(T x){if(!x){pc(48);return;}if(x<0) x=-x,pc('-');for(;x;x/=10) stk[++top]=48+x%10;while(top) pc(stk[top--]);}
}
using namespace IO;
int n,m,x,f[200010],v[400010],bj[400010],za[400010],ans,sum,ans1;
struct w
{
	int k,c;
	vector<int>a;
}q[200010];
int find(int x)
{
	if(f[x] == x) return x;
	return f[x] = find(f[x]);
}
inline bool cmp(w x,w y)
{
	return x.c < y.c;
}
signed main()
{
	Read(n),Read(m);
	for(int i = 1;i <= n;i++) f[i] = i;
	for(int i = 1;i <= m;i++)
	{
		Read(q[i].k),Read(q[i].c); sum = 1;
		for(int j = 1;j <= q[i].k;j++) 
		{
			Read(x);
			q[i].a.push_back(x);
		}
	}
	sort(q + 1,q + 1 + m,cmp);
	for(int i = 1;i <= m;i++)
	{
		sum = 0;
		for(int j = 1;j <= q[i].k;j++)
		{
			if(!v[f[find(q[i].a[j-1])]]) sum++;
			v[f[find(q[i].a[j-1])]]++;
		}
		ans += (sum - 1) * q[i].c;
		for(int j = 1;j <= q[i].k;j++) v[f[find(q[i].a[j-1])]] = 0;
		for(int j = 2;j <= q[i].k;j++) f[find(q[i].a[j-1])] = find(q[i].a[0]);
	}
	for(int i = 1;i <= n;i++) if(f[find(i)] == i) ans1++;
	if(ans1 > 1) ans = -1;
	print(ans);
	flush();
	return 0;
}

```

---

## 作者：CQBZ_ZJYjoe (赞：3)

[原题链接](https://atcoder.jp/contests/abc352/tasks/abc352_e)

## 思路解析
本题通过题意可得，要我们加一些边后做最小生成树，但可以发现，如果照题意中对每个操作里的点集暴力连边的话，时间与空间双双爆炸。

但由于 kruskal 的操作方法可得，将输入点集中相邻两个连边，不影响正确性，于是，本题结束。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using ll=long long;
using namespace std;

ll n,m,dist[1505],ans,cnt,tot;
struct Node
{
	int u,v,t;
}a[800005];
namespace DSU
{
	vector<int> fa;
	//	vector<int> siz;
	//	vector<int> sd;
	//	vector<vector<int>> son;
	
	inline void init(int x)
	{
		fa.resize(x+1);
		iota(fa.begin(),fa.end(),0);
		//		fill(siz.begin(),siz.end(),1);
		//		fill(sd.begin(),sd.end(),0);
		//		son.resize(x+1);
		//		for (int i=1;i<=n;i++)
		//			son[i]={i};
	}
	
	inline int find(int x)
	{
		if (x==fa[x])
			return x;
		fa[x]=find(fa[x]);
		return fa[x];
		//		return find(fa[x]);
	}
	
	inline void merge(int x,int y)
	{
		auto fx=find(x),fy=find(y);
		if (fx==fy)
			return ;
		fa[fx]=fy;
		cnt--;
		//		if (siz[fx]>siz[fy])
		//			swap(fx,fy);
		//		fa[fx]=fy,siz[fy]+=siz[fx],son[fy].insert(son[fy].end(),son[fx].begin(),son[fy].end());
		//		if (sd[fx]==sd[fy])
		//			fa[fx]=fy,sd[fy]++;
		//		else if (sx[fx]<sd[fy])
		//			fa[fx]=fy;
		//		else 
		//			fa[fy]=fx;
	}
}

inline bool cmp(const Node &x,const Node &y)
{
	return x.t<y.t;
}

inline void kruskal()
{
	int cnt=1;
	sort(a+1,a+tot+1,cmp);//按边权从小到大排序
	for (int i=1;i<=tot;i++)
	{
		int fx=DSU::find(a[i].u),fy=DSU::find(a[i].v);
		if (fx==fy)
			continue;
		ans+=a[i].t;
		DSU::merge(fx,fy);
		cnt++;
		if (cnt==n)
			break;
	}
} 

signed main()
{
	ios::sync_with_stdio(0);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	cnt=n;
	DSU::init(n);
	for (int i=1;i<=m;i++)
	{
		int xt,tx,x,y;
		cin>>xt>>tx>>x;
		for (int j=2;j<=xt;j++)
			cin>>y,DSU::merge(x,y),a[++tot].u=x,a[tot].v=y,a[tot].t=tx,x=y;//加边
	}
	if (cnt!=1)//判断图是否连通
	{
		cout<<-1;
		return 0;
	}
	DSU::init(n);//初始化并查集
	kruskal();
	cout<<ans;
	return 0;
}
```

---

## 作者：what_can_I_do (赞：2)

[传送门](https://www.luogu.com.cn/problem/AT_abc352_e)

做这道题需要先掌握 kruskal。

首先直接按照常规做法暴力存边是肯定不行的，所以得另寻思路。

kruskal 的做法其实就是贪心，从小到大按边权排序，然后按排好序的顺序取边，不过这条边要满足两个端点不在同一个联通块内。

现在再来看这一道题，会发现对于每组 $A$，如果一个点与其它所有点都连边，那么所有点就都在同一连通块了，所以实际可连边数最多仅 $K-1$ 条。

又因为同一组 $A$ 内每条边边权相同，所以可以不在乎顺序。

那么现在就取出第一个点，让它和同组的其它 $K-1$ 个点进行配对，如果不在同一个连通块内就连边，如果边数达到 $n-1$ 条就退出。

判断不成功的方式只需要看最终边数是否达到 $n-1$ 条即可。

# CODE:
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n,m;
int fa[200010];
int tot=0;
ll ans=0;
struct aaa
{
	int k;
	ll c;
	vector<int> s;
}a[200010];
inline bool cmp(aaa x,aaa y)
{
	return x.c<y.c;
}
inline int find(int k)
{
	if(fa[k]==k) return k;
	return fa[k]=find(fa[k]);
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		cin>>a[i].k>>a[i].c;
		for(int j=1;j<=a[i].k;j++)
		{
			int x;
			cin>>x;
			a[i].s.push_back(x);
		}
	}
	sort(a+1,a+m+1,cmp);
	for(int i=1;i<=n;i++) fa[i]=i;
	for(int i=1;i<=m;i++)
	{
		int fx=find(a[i].s[0]);
		for(int j=1;j<=a[i].k-1;j++)
		{
			int fy=find(a[i].s[j]);
			if(fx!=fy)
				fa[fy]=fx,ans+=a[i].c,tot++;
			if(tot==n-1) break;
		}
		if(tot==n-1) break;
	}
	if(tot!=n-1) printf("-1");
	else printf("%lld",ans);
	return 0;
}
```

---

## 作者：SkyLines (赞：2)

## Solution

一看题面：``minimum spanning tree``。

所以要用到最小生成树。

考虑第 $i$ 次操作，对于每个 $u,v$ 都要将 $u,v$ 连边，直接模拟肯定会超时，$S_i$ 是一个连通块，所以可以将 $i,i+1$ 连边即可。

至少要开路径压缩。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int max_(int aa, int bb){
	return aa > bb ? aa : bb;
}
int min_(int aa, int bb){
	return aa < bb ? aa : bb;
}
int abs_(int aa){
	return aa > 0 ? aa : -aa;
}
int pow_(int aa, int bb, int cc){
	int ans = 1;
	while(bb){
		if(bb & 1) ans = ans * aa % cc;
		aa = aa * aa % cc;
		bb >>= 1;
	}
	return ans;
}
const int K = 2e5 + 5;
int n, m, aaa, fa[K], w, u, v, fu, fv, cnt, szz[K];
size_t sz, ii, jj;
using ll = long long;
ll ans;
struct node{
	int k, c;
	vector<int> a;
} edge[K];
bool cmp(node xx, node yy){
	return xx.c < yy.c;
}
int find(int aa){
	if(fa[aa] == aa) return aa;
	else return fa[aa] = find(fa[aa]);
}
int main(){
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= n; i++) fa[i] = i;
	for(int kk = 1; kk <= m; kk++){
		scanf("%d %d", &edge[kk].k, &edge[kk].c);
		for(int i = 1; i <= edge[kk].k; i++){
			scanf("%d", &aaa);
			edge[kk].a.push_back(aaa);
		}
	}
	sort(edge + 1, edge + m + 1, cmp);
	for(int i = 1; i <= m; i++){
		w = edge[i].c;
		sz = edge[i].a.size();
		for(ii = 0; ii + 1 < sz; ii++){
			jj = ii + 1;
			u = edge[i].a[ii];
			v = edge[i].a[jj];
			fu = find(u);
			fv = find(v);
			if(fu == fv) continue;
			if(szz[fu] < szz[fv]) swap(fu, fv);
			fa[fv] = fu;
			szz[fu] += szz[fv];
			ans += w;
			cnt++;
			if(cnt == n - 1){
				printf("%lld", ans);
				return 0;
			}
		}
	}
	printf("-1");
	return 0;
}
```

---

## 作者：zzhbpyy (赞：1)

### [题目传送门](https://www.luogu.com.cn/problem/AT_abc352_e)

## 思路

虽然可连的边数惊人，但还是可以按照 Kruskal 算法的思想求解，从权值最小的边开始尽可能多的连接不连通的点，并对权值求和。

## 完整代码

```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct Edge{
	int k,c;
	vector<int>a;
}a[200005];
int n,m,fa[200005];
int find(int x){
	if(x==fa[x])return x;
	return fa[x]=find(fa[x]);
}
inline void merge(int a,int b){
	fa[find(a)]=find(b);
}
int ans,res;
signed main(){
	ios::sync_with_stdio(0),cin.tie(nullptr),cout.tie(nullptr);
	cin>>n>>m;
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<=m;i++){
		cin>>a[i].k>>a[i].c;
		a[i].a.resize(a[i].k+1);
		for(int j=1;j<=a[i].k;j++)cin>>a[i].a[j];
	}
	sort(a+1,a+m+1,[](Edge a,Edge b){
		return a.c<b.c;
	});
	for(int i=1;i<=m;i++){
		for(int j=2;j<=a[i].k;j++){
			if(find(a[i].a[j])!=find(a[i].a[j-1]))ans++,res+=a[i].c,merge(a[i].a[j],a[i].a[j-1]);
		}
	}
	if(ans!=n-1)cout<<-1;
	else cout<<res;
}
```

---

## 作者：Luke_li (赞：1)

# 题面
有 $n$ 个点，没有边，做 $m$ 次操作。

每次操作给你 $k_i$ 个点，把这些点两两连一条长度为 $c_i$ 的边。

求最后图中最小生成树的边权和。

# 分析

首先发现 $\sum k$ 最大有 $4\times10^5$ ，两个点之间连一条边，最多有 $1.6\times10^{11}$ 条边，显然不能直接加边。

分析一下发现最后的图中有很多边权一样的边，而用 kruscal 求最小生成树的过程中，对于边权一样的边，选哪个都行。（也就是说只要维持整个图联通，这些边就可以互相替换）所以同一操作中只要把相邻的每两个点之间连一条边就能代表所有其他的边。

这时只要把 $m$ 次操作按照 $c_i$ 排序，然后对于每次操作，把形如 $(A_i,A_i+1)$ 的 $k_i-1$ 条边连起来，用这些边做最小生成树，就能求出整张图的最小生成树。

# 代码

内含注释

```cpp
#include <iostream>
#include <vector>
#include <map>
#include <cstring>
#include <set>
#include <queue>
#include <cmath>
#include <stdio.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const ll N=2e5+10;
const ll inf=0x3f3f3f3f3f3f3f3f;
const ll MOD=998244353;
ll n,m,cnt,ans;
struct node
{
    ll c,k;
    vector<ll> a;
}a[N];
bool cmp(const node &x,const node &y)
{
    return x.c<y.c;
}
ll fa[N];
ll get(ll x)
{
    if(fa[x]==x)
        return x;
    return fa[x]=get(fa[x]);
}
void merge(ll x,ll y,ll z)
{
    if(get(x)!=get(y))//注意这里要判断是不是已经在同一个集合里面了
    {
        cnt++;
        ans+=z;
        fa[get(x)]=get(y);
    }
}
int main()
{
    ios::sync_with_stdio(0);
    cin>>n>>m;
    for(ll i=1;i<=m;i++)//结构体node用来存储每次操作
    {
        cin>>a[i].k>>a[i].c;
        for(ll j=1;j<=a[i].k;j++)
        {
            ll x;
            cin>>x;
            a[i].a.push_back(x);
        }           
    }
    sort(a+1,a+m+1,cmp);//对m次操作排序
    for(ll i=1;i<=n;i++)
        fa[i]=i;
    for(ll i=1;i<=m;i++)
    {
        for(ll j=0;j<ll(a[i].a.size())-1;j++)
        {
            ll t1=a[i].a[j],t2=a[i].a[j+1];
            merge(t1,t2,a[i].c);//常规的kruscal求最小生成树
        }
    }
    if(cnt==n-1)//如果加的边足够构成最小生成树
        cout<<ans<<endl;
    else
        cout<<-1<<endl;
    return 0;
}

```

---

## 作者：_Weslie_ (赞：1)

## 思路

考虑第一问（连通性），显然要使用并查集（下文的代码中使用了 bfs）。

但是我们显然不能将所有边都建出来。

因为只考虑连通性，所以只需保证一个集合内所选的边能保证所有点之间互相连通即可。

再考虑第二问（最小生成树）。

**注意：下文中的 $n$ 与原题中的 $N$ 不是同一个意义，集合即顶点子集。**

肯定不能建完图，但是我们知道，连接 $n$ 个点并使其互相连通至少需要 $n-1$ 条边。因为一个集合内的边都是等价的，所以只需任意选择 $n-1$ 条即可。

正确性证明：

在我们进行 kruskal 时，我们是先对边长进行排序，然后判断两个端点是否连通。

现在在一个集合中，每一条边边长都一样，那么它们一定会排在一起。

现在我们选择了 $n-1$ 条边，那么这个集合内的点已经保证连通了，就没有必要再选了，剩下的边都是浪费。

为了不浪费我们的时间资源和空间资源，我们只需任意选择 $n-1$ 条边即可。

## 代码实现

- 因为如果第一问使用并查集维护本题要写 $2$ 个并查集，所以我第一问使用了 bfs 的方法判断连通。
- 因为要判断图的连通，所以只应进行 $1$ 次 bfs。
- ```union``` 在 C++ 中为关键字，所以并查集的合并操作我使用了 ```vnion```。
- 本题数据范围可能爆 ```int```。

## Code

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,k[400005],c[400005],a[400005],vis[400005],fa[400005];
queue<int>q;
struct node{
	int u,v,w,nxt;
}e[800005];
int head[400005],cnt;
void bfs(int now){
	q.push(now);
	while(!q.empty()){
		int v=q.front();q.pop();
		if(vis[v])continue; 
		vis[v]=1;
		for(int i=head[v];i;i=e[i].nxt){
			q.push(e[i].v);
		}
	}
}
bool cmp(node _,node __){
	if(_.w<__.w)return 1;
	return 0;
}
int findd(int now){
	if(fa[now]==now)return now;
	return fa[now]=findd(fa[now]);
}
void vnion(int _,int __){
	fa[findd(__)]=findd(_);
}
void add(int u,int v,int w){
	e[++cnt].u=u;
	e[cnt].v=v;
	e[cnt].w=w;
	e[cnt].nxt=head[u];
	head[u]=cnt;
}
int tot=0;
signed main(){
	cin>>n>>m;
	for(int i=1;i<=400004;i++)fa[i]=i;
	for(int i=1;i<=m;i++){
		cin>>k[i]>>c[i];
		for(int j=1;j<=k[i];j++){
			cin>>a[j];
		} 
		for(int j=2;j<=k[i];j++){
			add(a[1],a[j],c[i]);
			add(a[j],a[1],c[i]);
		}
	}
	bfs(1);
	for(int i=1;i<=n;i++){
		if(vis[i]==0){
			cout<<-1;
			return 0;
		}
	}
	sort(e+1,e+cnt+1,cmp);
	long long ans=0;
	for(int i=1;i<=cnt;i++){
		if(findd(e[i].u)!=findd(e[i].v)){
			vnion(e[i].u,e[i].v);
			ans+=e[i].w;
			tot++;
		}
		if(tot==n-1)break;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：HasNoName (赞：1)

### 思路

由于题目要求求最小生成树，所以显然可以对边权从小到大排序。

对于每个顶点子集，由于边权从小到大排序，所以按顺序遍历每个集合，在保证是树的情况下能连的边尽量连一定最优。

判断是否已经连过可以使用并查集。

因为 $n$ 个点可以连 $n-1$ 条边，在把不重复的边乘上边权即可。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200005;
typedef long long ll;
unordered_map<int,int>c;
struct T
{
    int m;
    ll k;
    vector<int>c;
}a[N];
int fa[N];
bool cmp(T a,T b)
{
    return a.k<b.k;
}
int find(int x)//并查集
{
    if(x==fa[x])return x;
    return fa[x]=find(fa[x]);
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n,m,x;
    cin>>n>>m;
    for(int i=1;i<=m;i++)
    {
        cin>>a[i].m>>a[i].k;
        for(int j=0;j<a[i].m;j++)
        {
            cin>>x;
            a[i].c.push_back(x);
        }
    }
    sort(a+1,a+m+1,cmp);//排序
    ll ans=0;
    for(int i=1;i<=n;i++)
        fa[i]=i;
    for(int i=1;i<=m;i++)
    {
        ll u=0;
        for(int j=0;j<a[i].m;j++)
        {
            if(c[find(a[i].c[j])])continue;//判重
            c[find(a[i].c[j])]=1;
            fa[find(a[i].c[j])]=find(a[i].c[0]);//并查集中祖先是谁没有关系
            u++;//边数
        }
        u--;//因为a[i].c[0]和自己连了一条边，所以减去1
        ans+=a[i].k*u;
        c.clear();
    }
    int t=find(1);//判断图是否连通
    for(int i=1;i<=n;i++)
    {
        if(find(i)!=t)
        {
            cout<<"-1\n";
            return 0;
        }
    }
    cout<<ans<<'\n';
    return 0;
}

```

---

## 作者：FreedomKing (赞：1)

转化一下就可以变成 Kruskal 板子。

### 思路

首先要理解一下每次操作所谓的两两加边，其实就是让整个点集形成一个边权都为 $c_i$ 的完全图，有了这个结论我们就可以考虑不按照操作建边了。

但问题还不是很好做，点集与点集之间的合并还是不好搞。如果考虑把图中的每条边都更新为最小值然后再跑 Kruskal，这显然就没有用的上文得到的结论。

可以考虑离线一下按 $c$ 排个序，从权值小的连通块往权值较大的连通块依次使用 Kruskal 合并，由于只要能合并到同一并查集即可，所以一个点集只需要建 $k_i-1$ 条边，这样就保证了边数的问题。

### AC Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
namespace FreedomKing_qwq{};
using namespace FreedomKing_qwq;
const int xN=1e7+5,N=2e5+5,mN=1e3+5,mod=1e9+7;
namespace FreedomKing_qwq{
	//#define lc (p<<1)
	//#define rc (p<<1|1)
	inline int qread(){
#define qr qread()
		int x=0,c=getchar(),t=1;
		while(c<'0'||c>'9'){
			t^=(c=='-');
			c=getchar();
		}
		while(c>='0'&&c<='9'){
			x=(x<<3)+(x<<1)+c-'0';
			c=getchar();
		}
		return (t?x:-x);
	}
	inline void qwrite(int x){
#define qw(_) qwrite(_)
#define qws(_) qw(_),putchar(' ')
#define qwe(_) qw(_),putchar('\n')
		if(x<0) x=-x,putchar('-');
		if(x>9) qwrite(x/10);
		putchar(x%10+'0');
		return;
	}
	inline int qpow(int x,int p,int mod){
		x=(p?x:1);
		mod=(mod?mod:LONG_LONG_MAX);
		int t=1;
		while(p>1){
			if(p&1) t=(t*x)%mod;
			x=(x*x)%mod;
			p>>=1;
		}
		return (x*t)%mod;
	}
	inline int gcd(int x,int y){return (x%y==0?y:gcd(y,x%y));}
	inline int lcm(int x,int y){return (x/gcd(x,y)*y);}
	inline int max(int x,int y){return (x>y?x:y);}
	inline int min(int x,int y){return (x<y?x:y);}
	inline int abss(int x){return (x>=0?x:-x);}
	inline int lowbit(int x){return (x&-x);}
}
struct node{
	int k,c;
	vector<int>f;
}a[N];
bool cmp(node x,node y){return x.c<y.c;}
int fa[N];
inline void init(int x){
	for(int i=1;i<=x;i++) fa[i]=i;
	return;
}
inline int find(int x){
	return (fa[x]==x?x:fa[x]=find(fa[x]));
}
inline void update(int x,int y){
	x=find(x);y=find(y);
	fa[y]=x;
	return;
}
signed main(){
	int n=qr,m=qr;
	init(n);
	for(int i=1;i<=m;i++){
		a[i].k=qr,a[i].c=qr;
		for(int j=1;j<=a[i].k;j++) a[i].f.push_back(qr);
//		sort(a[i].f.begin(),a[i].f.end());
	}
	sort(a+1,a+m+1,cmp);
	int ans=0,cnt=0;
	for(int i=1;i<=m;i++){
		for(int j=1;j<a[i].k;j++){
			if(find(a[i].f[j])!=find(a[i].f[j-1])){
				update(a[i].f[j],a[i].f[j-1]);
				cnt++;
				ans+=a[i].c;
			}
		}
	}
	if(cnt==n-1) qw(ans);
	else puts("-1");
	return 0;
}
```

---

## 作者：_ZML_ (赞：1)

# 思路
这里提供一种暴力做法。方法就是当边数到达一个值过后就不加边了。我取的值是 $500000$，实际上可以开大一些，只要 $x \log x$ 不超时就行了。

# 代码
[赛时提交记录](https://atcoder.jp/contests/abc352/submissions/53139257)
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int a[200020];
int cnt;
struct rec
{
    int x, y, z;
} edge[5000010];
int fa[500010];
bool operator<(rec a, rec b)
{
    return a.z < b.z;
}
int get(int x) { return fa[x] == x ? x : fa[x] = get(fa[x]); }
signed main()
{
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
    {
        int k, c;
        cin >> k >> c;
        for (int i = 1; i <= k; i++)
        {
            cin >> a[i];
        }
        if(cnt>5000000) continue;
        for (int i = 1; i < k; i++)
        {
            for (int j = i + 1; j <= k; j++)
            {
                int u = a[i], v = a[j];
                if(cnt>5000000) break;
                edge[++cnt] = {u, v, c};
                
            }
            if(cnt>5000000) break;
        }
    }
    sort(edge + 1, edge + cnt + 1);
    for(int i=1;i<=n;i++) fa[i]=i;
    int ans = 0;
    for (int i = 1; i <= cnt; i++)
    {
        int x = get(edge[i].x),
            y = get(edge[i].y);
        if (x == y)
            continue;
        fa[x] = y;
        ans += edge[i].z;
    }
    int flag = 0;
    for (int i = 1; i <= n; i++)
        if (fa[i] == i)
            flag++;
    if (flag > 1)
        cout << "-1";
    else
        cout << ans;
    return 0;
}
```

---

## 作者：lfxxx_ (赞：0)

## 思路
- 我们可以把一个加边操作看成将 $A_{i,1},A_{i,2},\cdots,A_{i,k_i}$ 合并到一个集合里面，考虑使用并查集维护这一个集合。

- 先对边按权值排序，便于以后的合并操作。

- 如果加的边数已经达到 $N-1$，则已经是一颗树，不必要加边了。

- 实际上是一个 kruskal 算法的变形。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
struct node{
	int k,w;
	vector<int>e;
	bool operator<(const node&b)const{return w<b.w;}//121124
}p[N];
int fa[N];
int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}
bool merge(int x,int y)
{
	x=find(x),y=find(y);
	if(x!=y)
		fa[x]=y;
	return x!=y;
}
signed main()
{
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;++i)
		fa[i]=i;
	for(int i=1;i<=m;++i)
	{
		cin>>p[i].k>>p[i].w;
		for(int j=0;j<p[i].k;++j)
		{
			int tmp;
			cin>>tmp;
			p[i].e.emplace_back(tmp);
		}
	}
	sort(p+1,p+m+1);
	int cnt=0;
	int ans=0;
	for(int i=1;i<=m;++i)
	{
		for(int j=1;j<p[i].k;++j)
		{
			if(merge(p[i].e[j],p[i].e[j-1]))
				++cnt,ans+=p[i].w;
			if(cnt==n-1)
			{
				cout<<ans;
				exit(0);
			}
		}
	}
	cout<<-1;
}
```

---

## 作者：卡卡卡卡卡卡 (赞：0)

## 题解
给出 $N$ 个点，$M$ 组边集。

题目要求最小生成树，根据定义，将边从小到大排序。

因为最后都是一个块，所以只要能增加块的大小就是有贡献的，用贡献的边就加进去，这可以用并查集处理，记得特判无解的情况。

时间复杂度：$O(M+\sum K)$。
## code：
```cpp
// LUOGU_RID: 158078828
#include<bits/stdc++.h>
using namespace std;
long long now,maxn,sum=0,ans,fa[500005];
struct node{
	long long c,k,id;
	vector<long long> e;
}p[500005];
bool cmp(node x,node y)
{
	return x.c<y.c;
}
long long find(long long x)
{
	if(fa[x]!=x)return fa[x]=find(fa[x]);
	else return x;
} 
void unionn(long long x,long long y)
{
	long long fx=find(x),fy=find(y);
	fa[fx]=fy;
}
int main()
{
    long long n,m;
    cin>>n>>m;
    for(long long i=1;i<=m;i++)
    {
    	cin>>p[i].k>>p[i].c;p[i].id=i;
    	for(long long j=1;j<=p[i].k;j++)
    	{
    		long long t;
    		cin>>t;
    		p[i].e.push_back(t);
		}
	}
	sort(p+1,p+1+m,cmp);//排序
	for(long long i=1;i<=n;i++)fa[i]=i;
	for(long long i=1;i<=m;i++)
	{
		long long sz=p[i].e.size(),t;
		for(long long j=0;j<sz;j++)
		{
			if(j==0)t=p[i].e[j];
			else 
			{
		        long long o=p[i].e[j];
		        if(o<=0)continue;
				if(find(o)!=find(t))ans+=p[i].c,unionn(p[i].e[j],t);//加边
			}
		}
	}
	for(int i=1;i<=n;i++)//特判
	{
		if(find(1)!=find(i))
		{
			cout<<-1;
			return 0;
		}
	}
	cout<<ans;
}
```

---

## 作者：T_TLucas_Yin (赞：0)

按照如题所示的方式建图，在极限情况下肯定每两个点之间都有很多重边。如果我们暴力地建图、去重边，显然时空都是不够用的。

注意题目只要求我们求这个图的最小生成树。用 Kruskal 求最小生成树时，用到的核心思想是并查集判断联通。我们考虑借助这个思想，跳过建图的过程，直接求最小生成树。

由于每次给定了我们很多点，并要求其中**每个点之间**都建一条给定权值的边。所以建一个集合的边，就相当于把该集合全都并到一个并查集里。

我们按照边权从小到大给输入的集合排个序，这样每个集合中的点第一次联通建的就一定是权值最小的边。我们每在连通块中加入一个新节点，就在一个累加器中加入该边的权值。当图第一次联通时，输出该累加器即可。这一部分除了存边的形式，其他都和 Kruskal 算法一样。

代码很好写吧（应该）。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,top,x;
struct node{
	int x,k;
}a[200005];
bool cmp(node a,node b){
	return a.x<b.x;
}
vector<int> v[200005];
int f[200005];
int Find(int k){
	if(f[k]==k) return k;
	else return f[k]=Find(f[k]);
}
int main(){
	scanf("%d %d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d %d",&top,&a[i].x);
		a[i].k=i;
		for(int j=1;j<=top;j++){
			scanf("%d",&x);
			v[i].push_back(x);
		}
	}
	sort(a+1,a+1+m,cmp);
	for(int i=1;i<=n;i++) f[i]=i;
	long long sum=0,cnt=0;
	for(int i=1;i<=m;i++){
		int k=a[i].k;
		for(int j=1;j<v[k].size();j++){
			int x=Find(v[k][j-1]),y=Find(v[k][j]);
			if(x!=y) f[x]=y,sum+=a[i].x,cnt++;
		}
		if(cnt==n-1){
			printf("%lld",sum);
			return 0;
		}
	}
	printf("-1");
	return 0;
}
```

---

## 作者：Heldivis (赞：0)

# ABC352E

前置芝士：[并查集](https://www.luogu.com.cn/problem/P3367)、[最小生成树](https://www.luogu.com.cn/problem/P3366)。

## 题意

一个有 $N$ 个点的加权无向图，进行 $M$ 次操作，每次操作给出 $K,C,A_i$，表示在点 $A_1,A_2,\dots,A_K$ 之间加一条权值为 $C$ 的边。若操作后，图不连通，输出 $-1$，否则求出该图的最小生成树的边权和。

## 分析 & 解题

连通性很好判断。

先进行一次并查集，每次使 $A_1$ 和 $A_2,A_3\dots,A_K$ 连边，最后判断每个点的祖先是否相同，若相同，则为连通；否则不连通。

如何求最小生成树的边权和？

类似 Kruskal 算法，将每次操作按边权从小到大排序，查询点集，如果存在两点不在一个连通块，将这两点连边，并加上边权。

但是如果双重循环会超时，可以每次令 $A_1$ 和 $A_i$ 连边，则每次操作后，该点集一定连通，效果和双重循环相同。

这样操作，最后一定是最小生成树，证明同 Kruskal 算法。

时间复杂度 $O(M\log M+\sum K)$。

*[Code](https://www.luogu.com.cn/paste/r64vw6cb)*

---

## 作者：封禁用户 (赞：0)

感觉比 D 好想。

# 题意：

$m$ 个操作，每次操作给 $k_i$ 个点 $a_1,a_2,\cdots,a_{k_i}$，将它们两两连边，边权为 $c_i$，求最后最小生成树边权和。

# 思路

暴力建边+ kruskal 求最小生成树复杂度为 $O(\sum k_i^2+\sum k_i^2\log \sum k_i^2)$，不可行。

发现给的 $k_i$ 个点并不用全部都连上边，因为我们只需要两点间边权最小的边，剩下的边都多余。

再考虑 kruskal 的实现过程，发现可以选择将边权 $c_i$ 排序，然后从大到小依次将第 $i$ 个命令的 $k_i$ 个点连边。

剩下的判联通这些其实就是求最小生成树的过程，套板子就好了。

显然当边数为 $n-1$ 时目前连的边组成的连通图即为最小生成树。

复杂度 $O(\sum k_i)$。

```cpp
#include<bits/stdc++.h>
#define sd std::
#define int long long
#define inf 0x3f3f3f3f
#define linf 1e18
#define il inline
#define db double
#define ldb long double
#define F(i,a,b) for(int i=(a);i<=(b);i++)
#define f(i,a,b) for(int i=(a);i>=(b);i--)
#define MIN(x,y) (x<y?x:y)
#define MAX(x,y) (x>y?x:y)
#define me(x,y) memset(x,y,sizeof x)
#define pii sd pair<int,int>
#define umap(x,y) sd unordered_map<x,y>
#define pque(x) sd priority_queue<x>
#define X first
#define Y second
#define kg putchar(' ')
#define Fr(a) for(auto it:a)
#define dbg(x) sd cout<<#x<<": "<<x<<sd endl
il int read(){int w=1,c=0;char ch=getchar();for(;ch>'9'||ch<'0';ch=getchar()) if(ch=='-') w=-1;for(;ch>='0'&&ch<='9';ch=getchar()) c=(c<<3)+(c<<1)+ch-48;return w*c;}
void printt(int x){if(x>9) printt(x/10);putchar(x%10+48);}
il void print(int x){if(x<0) putchar('-'),printt(-x);else printt(x);}
il void put(int x){print(x);putchar('\n');}
il void printk(int x){print(x);kg;}
const int N=4e5+10;
int n,m,x;
int fa[N];
int find(int x)
{
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
sd vector<int> p[N];
struct query
{
	int k,c,id;
}q[N];
int cmp(query a,query b)
{
	return a.c<b.c;
}
int ans,cnt;
void kruskal()
{
	for(int i=1;i<=m;i++)
	{
		for(int j=0,len=p[q[i].id].size();j<len-1;j++)
		{
			int u=find(p[q[i].id][j]);
			int v=find(p[q[i].id][j+1]);//连边
			if(u==v) continue;
			ans+=q[i].c;
			cnt++;
			fa[u]=v;
			if(cnt==n-1) return print(ans),void();
		}
	}
	puts("-1");
}
il void solve()
{
	n=read(),m=read();
	F(i,1,n) fa[i]=i;
	F(i,1,m)
	{
		q[i].k=read(),q[i].c=read(),q[i].id=i;
		F(j,1,q[i].k) x=read(),p[i].emplace_back(x);
	}
	sd sort(q+1,q+1+m,cmp);//按ci排序
	kruskal();//求最小生成树
}
signed main()
{
    int T=1;
//    T=read();
    while(T--) solve();
    return 0;
}
```

---

## 作者：六楼溜刘 (赞：0)

### 题意

- 给你一张有 $N$ 个点的边带权无向图，给出的方法是告诉你这张图中的 $M$ 个完全连通子图（即团）的点集，其中第 $i$ 个团内所有边的边权均为 $C_i$。整个图中可能有重边，问最小生成树，需要特判不连通的情况。
- $1 \le N\le 2\times 10^5$，读入点集总大小不超过 $4\times 10^5$。

### 题解

简单题，考验对 Kruskal 的理解（看到最小生成树就应该想 Kruskal 吧）。

首先离开这道题考虑 Kruskal 的过程，容易发现是从小到大枚举边，然后每次将这样的边缩成一个点。那么不妨认为每次是把边权相同的边全部拿出来，这样就能得到若干个连通块。显然此时无论缩哪些边，最终都能将每个连通块缩成恰好一个点，并且缩的边数也是相同的（每个连通块缩 $|S|-1$ 条），那么对最小生成树的贡献也是相同的。

回到这道题，容易发现给出的每个团相当于都是把点集缩成一个点，那么就将点集按 $C_i$ 升序排列，然后每次将涉及的连通块全部用并查集并起来即可。具体缩哪些边不重要，怎么好写怎么来（反正它是个团对吧）。复杂度 $O(\sum K+n\log n)$。

### code

[提交记录](https://atcoder.jp/contests/abc352/submissions/53131730)

```cpp
#include<bits/stdc++.h>
#define mem(a,b) memset(a,b,sizeof(a))
#define forup(i,s,e) for(i64 i=(s);i<=(e);i++)
#define fordown(i,s,e) for(i64 i=(s);i>=(e);i--)
#ifdef DEBUG
#define msg(args...) fprintf(stderr,args)
#else
#define msg(...) void()
#endif
using namespace std;
using i64=long long;
#define gc getchar()
inline i64 read(){
    i64 x=0,f=1;char c;
    while(!isdigit(c=gc)) if(c=='-') f=-1;
    while(isdigit(c)){x=(x<<3)+(x<<1)+(c^48);c=gc;}
    return x*f;
}
#undef gc
const i64 N=2e5+5,inf=0x3f3f3f3f;
i64 n,m,ans;
struct Node{
	i64 c;
	vector<i64> vec;
}op[N];
i64 fa[N];
i64 getfa(i64 x){return x==fa[x]?x:fa[x]=getfa(fa[x]);}
bool cmp(Node &a,Node &b){
	return a.c<b.c;
}
void merge(int u,int v,int c){
	u=getfa(u);v=getfa(v);
	if(u==v) return;
	ans+=c;
	fa[u]=v;
}
signed main(){
	n=read();m=read();
	forup(i,1,n) fa[i]=i;
	forup(i,1,m){
		i64 k=read();op[i].c=read();
		forup(j,1,k){
			i64 a=read();
			op[i].vec.push_back(a);
		}
	}
	sort(op+1,op+m+1,cmp);
	forup(i,1,m){
		i64 sz=op[i].vec.size();
		forup(j,0,sz-2){
			merge(op[i].vec[j],op[i].vec[j+1],op[i].c);
		}
	}
	int cnt=0;
	forup(i,1,n){
		if(fa[i]==i) ++cnt;
	}
	if(cnt>1){
		puts("-1");
	}else{
		printf("%lld\n",ans);
	}
}
```

---

## 作者：incra (赞：0)

### Solution
水题。

首先显然不可能把所有边都建出来然后求最小生成树。

考虑 kruskal 求 MST 的过程。

我们把边权从小到大排序，然后顺序遍历，把能合并的点集合并。

那么做法就很明显了，把每一类边按边权排序，然后把这些点所在的点集合并即可，注意原本就在同一集合的一对点不需要合并。
### Code
[Link](https://atcoder.jp/contests/abc352/submissions/53113990)。

---

## 作者：2023lpx (赞：0)

# AT_abc352_e [ABC352E] Clique Connect 题解

## 题目大意

给你一副加权无向图，其边的给出方式为给你 $S_i=\lbrace A_{i,1},A_{i,2},\dots,A_{i,K_i}\rbrace$，其中 $u, v \in S_i$，且 $u < v$，连接所有可行的 $u,v$ 建长度为 $c$ 的边，让你求这幅图的最小生成树的边权总和。

## 思路

kruskal 板子题。

对于 kruskal 来说，在每条边的边权都一样时：

$$1\leftrightarrow2,1\leftrightarrow3,2\leftrightarrow3$$

和

$$1\leftrightarrow2,1\leftrightarrow3$$

对答案的贡献是一样的（都是连通的）。


所以题目就变得非常简单了。

每次输入只用将每个点与第一个点建边即可。

然后跑 kruskal。

## code

```cpp
#include<cstdio>
#include<map>
using namespace std;
#define int long long
int n,m;
int k,c;
int const maxn=200000;
struct To{
	int to;
	int lst;
	int len;
	int from;
}to[maxn*2*2+1];
int head[maxn+1];
int cnt;
void qsort(int l,int r){
	int i=l,j=r,mid=to[(l+r)>>1].len;
	while(i<j){
		while(to[i].len<mid){
			i++;
		}
		while(to[j].len>mid){
			j--;
		}
		if(i<=j){
			swap(to[i],to[j]);
			i++;
			j--;
		}
	}
	if(i<r){
		qsort(i,r);
	}
	if(l<j){
		qsort(l,j);
	}
}
int ans;
int fa[maxn+1];
int find(int a){
	if(fa[a]==a){
		return a;
	}
	return fa[a]=find(fa[a]);
}
signed main(){
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%lld%lld",&k,&c);
		int in;
		int r;
		scanf("%lld",&r);
		for(int j=2;j<=k;j++){
			scanf("%lld",&in);
			cnt++;
			to[cnt].to=r;
			to[cnt].lst=head[in];
			to[cnt].len=c;
			to[cnt].from=in;
			head[in]=cnt;
			cnt++;
			to[cnt].to=in;
			to[cnt].lst=head[r];
			to[cnt].len=c;
			to[cnt].from=r;
			head[r]=cnt;
		}
	}
	qsort(1,cnt);
	for(int i=1;i<=n;i++){
		fa[i]=i;
	}
	for(int i=1;i<=cnt;i++){
		int u=find(to[i].to);
		int v=find(to[i].from);
		if(u==v){
			continue;
		}
		ans+=to[i].len;
		fa[v]=u;
	}
	for(int i=1;i<=n;i++){
		fa[i]=find(fa[i]);
	}
	int f=fa[1];
	for(int i=1;i<=n;i++){
		if(fa[i]!=f){
			printf("-1");
			return 0;
		}
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：lilong (赞：0)

### 题意

给定一个有 $n$ 个点的图，初始没有任何边。接下来有 $m$ 次操作，每次操作给定一个大小为 $k$ 的集合 $S$ 和一个权值 $c$，并对所有 $u,v \in S$ 并且 $u < v$ 的点 $u,v$ 连上一条边权为 $c$ 的边。$m$ 次操作后，判断图的连通性，若图联通则需求出其最小生成树的边权总和。

### 思路

如果直接暴力建边，时间复杂度 $O(n^2)$，不可接受。

仔细思考一下，其实发现并不需要这么多的边。具体地，对于一个大小为 $k$ 的集合 $S$，只需要连 $k-1$ 条边。为什么呢？假设只有这 $k$ 个点要求最小生成树，那么最后一定只选择 $k-1$ 条边。换句话说，在求最小生成树的过程中，只要保证对于同一个 $S$ 中的点有足够的边能够选择即可。

有了上面的结论后，这道题就不难了。先使用并查集判断连通性，再使用 Kruskal 或 Prim 算法求最小生成树即可。时间复杂度 $O(n \log n)$。

代码如下：

```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#define int long long
using namespace std;
int n,m,cnt,c,a,b,fa[1000001];
int tot,ans;
struct E
{
	int u,v,w;
}e[1000001];
int cx( int x )
{
	if( x == fa[x] ) return x;
	return fa[x] = cx( fa[x] );
}
bool ck( void )
{
	int f = cx( 1 );
	for( int i = 2 ; i <= n ; i ++ )
		if( cx( i ) != f )
			return false;
	return true;
}
bool cmp( E x , E y )
{
	return x.w < y.w;
}
signed main()
{
	cin >> n >> m;
	for( int i = 1 ; i <= n ; i ++ )
		fa[i] = i;
	while( m -- )
	{
		cin >> cnt >> c;
		cin >> a;
		for( int i = 2 ; i <= cnt ; i ++ )
		{
			cin >> b;
			fa[cx( b )] = cx( a );
			tot ++;
			e[tot].u = a,e[tot].v = b,e[tot].w = c;
        }
	}
	if( !ck() )
	{
		cout << -1 << endl;
		return 0;
	}
	sort( e + 1 , e + tot + 1 , cmp );
	cnt = 0;
	for( int i = 1 ; i <= n ; i ++ )
		fa[i] = i;
	for( int i = 1 ; i <= tot ; i ++ )
	{
		int x = cx( e[i].u ),y = cx( e[i].v );
		if( x == y ) continue;
		fa[x] = y;
		ans += e[i].w;
		cnt ++;
		if( cnt == n - 1 ) break;
	}
	cout << ans;
	return 0;
}
```

---

## 作者：2c_s (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc352_e)

## 思路

前置知识：[kruskal 最小生成树](https://www.luogu.com.cn/problem/solution/P3366)。不会的同学可以来这个题的题解区学习。

最小生成树裸题，但需要一点变式。

这道题没有直接给边，而是给了互相连通的一些点集。但我们不需要连这些边，只需要保证点集内部的点互相连通即可。所以我们**只让第一个点去连其他的点**，保证连通性。

建图完成，之后就是跑最小生成树了。我们选择用 kruskal 算法计算。跑完最小生成树后输出。时间复杂度 $\mathcal{O}(N\log N)$。

- 图不一定连通，如果不连通（能加的边数**小于 $N-1$**），输出 ``-1``。

- 边权和会超 int，记得开 long long。

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll read(){//快读。
	ll k=0,flag=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')flag=-1;c=getchar();}
	while(c>='0'&&c<='9'){k=(k<<1)+(k<<3)+(c^48);c=getchar();}
	return k*flag;
}
const int N=4e5+10;
int n,m,cnt,fa[N],num;
struct node{
	int x,y;
	ll w;
}a[N];
bool cmp(node a,node b){return a.w<b.w;}//边权从小到大排序。
int find(int x){//并查集查找这个点是否连通。
	if(x==fa[x])return x;
	return fa[x]=find(fa[x]);
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=m;++i){
		int k=read();
		ll c=read();
		int u=read();
		for(int i=1;i<k;++i){
			int v=read();
			a[++cnt]={u,v,c};//用 1 号点连其他的。
		}
	}
	sort(a+1,a+1+cnt,cmp);
	for(int i=1;i<=n;++i)fa[i]=i;//记录一开始每个点的父亲是自己。
	ll ans=0;
	for(int i=1;i<=cnt;++i){
		int fx=find(a[i].x);
		int fy=find(a[i].y);
		if(fx!=fy){//没连过就连。
			ans+=a[i].w;
			fa[fx]=fy;
			if(++num==n-1)break;//如果连图完成就退出。
		}
	}
	if(num<n-1)ans=-1;//不连通输出 -1。
	cout<<ans;
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/158053395)

---

## 作者：Dtw_ (赞：0)

[at](https://atcoder.jp/contests/abc352/tasks/abc352_e)
# 题目大意
~~给你一堆边，求他的最小生成树的权值。~~

给你一个加权无向图 $G$ ，其中有 $N$ 个顶点，编号为 $1$ 至 $N$ 。最初， $G$ 没有边。

您将执行 $M$ 次操作来为 $G$ 添加边。 $i$ -th 运算 $(1 \leq i \leq M)$ 的操作如下：

- 给你一个由 $K_i$ 个顶点组成的顶点子集 $S_i={ A_{i,1},A_{i,2},\dots,A_{i,K_i}}$ 。对于每一对 $u, v$ ，即 $u, v \in S_i$ 和 $u < v$ ，在顶点 $u$ 和 $v$ 之间添加一条边，权重为 $C_i$ 。

数据范围

-   $2 \leq N \leq 2 \times 10^5$
-   $1 \leq M \leq 2 \times 10^5$
-   $2 \leq K_i \leq N$
-   $\sum_{i=1}^{M} K_i \leq 4 \times 10^5$

完成所有 $M$ 操作后，确定 $G$ 是否相连。如果是，求 $G$ 最小生成树中各条边的总权重。
# 思路
你看着我的题目描述很简单对吧，但是实际上他所有的边总共大约有 $1.6 \times 10^{11}$。

但这样我们就不可求了吗？

当然不是。我们考虑我们一次所连的点一定在同一个联通块内，且边权相同，那么我们只要保证他联通就行，因为多余的边是没必要的。所以我们就可以前一个点向后一个点连边，然后再跑 Kruskal。

时间复杂度的话 $O(M +\sum K \log (M +\sum K))$

# Code
```cpp
#include<bits/stdc++.h>

using namespace std;

#define endl '\n'

#define TRACE 1
#define tcout TRACE && cout

#define int long long

#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

const int N = 2e5 + 10, M = 2e5 + 10, L = 1e9;

int a[M];

int n, m;
int p[N];
int res, cnt, idx;

struct Edge
{
	int u, v, w;
}edge[4 * M];

inline int fifa(int u)
{
	if(u == p[u])
	{
		return u;
	}
	return p[u] = fifa(p[u]);
}

inline void join(int a, int b)
{
	a = fifa(a);
	b = fifa(b);
	if(a != b)
	{
		p[a] = b;
	}
}

inline bool query(int x, int y)
{
	return fifa(x) == fifa(y);
}

bool cmp(Edge x, Edge y)
{
	return x.w < y.w;
}

inline int kruskal()
{
	for(int i=1; i<=n; i++)
	{
		p[i] = i;
	}
	sort(edge+1, edge+idx+1, cmp);
	for(int i=1; i<=idx; i++)
	{
		int u = edge[i].u;
		int v = edge[i].v;
		int w = edge[i].w;
		if(!query(u, v))
		{
			join(u, v);
			res += w;
			cnt++;
			if(cnt == n-1)
			{
				return res;
			}
		}
	}
	return -1;
}

signed main()
{
	fst;
	cin >> n >> m;
	for(int i=1; i<=m; i++)
	{
		int k, c;
		cin >> k >> c;
		for(int j=1; j<=k; j++)
		{
			cin >> a[j];
			if(j >= 2)
			{
				edge[++idx] = {a[j-1], a[j], c};
			}
		}
	}
	int res = kruskal();
	cout << res;
	return 0;
}


```

---

## 作者：无名之雾 (赞：0)

~~讲个笑话，因为不会 kruskal 所以写了并查集。~~

## 思路

我们对于加边的操作，直接当做将 $A_{i,1}，A_{i,2}…，A_{i,k}$ 合并至一个集合即可。

## 实现

简单并查集维护集合。然后对边按权值从低到高排序。最后判断是否构成树即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
const int N=2e5+5;
int c[N],k[N],f[N];
vector<int>a[N];
vector<pair<int,int> >v;
int find(int x){
	if(x==f[x])return x;
    return f[x]=find(f[x]);
}
void fun(int a,int b){
    if(find(a)!=find(b))f[find(a)] = find(b);
}
signed main(){
   	int n=read(),m=read();
    for(int i=1;i<=n;i++)f[i]=i;
    for(int i=1;i<=m;i++){
        k[i]=read(),c[i]=read();
        for(int j=1;j<=k[i];j++){
            int u=read();
            a[i].emplace_back(u);
        }
        v.emplace_back(make_pair(c[i],i));
    }
    sort(v.begin(),v.end());
	int ans=0;
    for(auto e : v){
		int w=e.first,s=e.second;
        map<int,bool>b;
        int cnt=0;
        for(int &u : a[s]){
            if(b[find(u)]==0){
                b[find(u)]=1;
                cnt++;
            }
        }
        ans+=(c[s])*(cnt-1);
        for(int i=0;i+1<a[s].size();i++)fun(a[s][i],a[s][i+1]);
    }
    for(int i=2;i<=n;i++){
        if(find(1)!=find(i)){
        	puts("-1");
            return 0;
        }
    }
    cout<<ans;
	return 0;
}
```

[赛时AC记录](https://atcoder.jp/contests/abc352/submissions/53127664)

---

## 作者：封禁用户 (赞：0)

因为本题的数据范围为 $M\le 2\times 10^{5}$，所以不能暴力建边跑生成树。

考虑一个优化。我们按边权将每次操作排序，然后按普通的 kruskal 的操作依次连边就行。

[code](https://atcoder.jp/contests/abc352/submissions/53135027)。

---

## 作者：P_VICVIC_R (赞：0)

其实挺简单的

---

### 思路

先[读题](https://www.luogu.com.cn/problem/AT_abc352_e)，这道题是求**最小生成树**，并且建图方式十分奇葩：

简单说就是给你一个点集，然后把点集里的每一个点都连起来构成一个子图，最后将这个子图搞成一个完全图。

然后因为数据中每一个点集都可以是全集，又有  $N,M$ 上限相等，所以算上重边最多有 $n\times \sum^{n-1}_{i=1}i$ 条边，与 $n^3$ 差不多了，建边都超时了，所以这道题注定不会建图。

我们发现 每个子集所构成的子图边权都相等，不妨将每个子图单独存储，按照边权排序（这一步是为了方便求最小生成树）。

因为同一个子图内部的点是一定能互相到达的，当求最小生成树时，每个子图都只需要形成一棵或多棵树，（因为子集之间有交集，所以在一个子集中有可能有的多个点会先被其他子集选走）再由树上的一点连到其他树上就行，其他的边就一定不会被选上。

剩下的并查集判环之类的就不赘述了。

### [code](https://www.luogu.com.cn/paste/35apcwj2)

---

## 作者：zengziqvan (赞：0)

本题是一道考察 kruskal 性质的好题。

考虑离线下来操作，将所有加边操作按照 $c_i$ 从小到大排序。

这样只会从权值小的开始加边。

扫描每个加边操作，对于每个加边操作：

从第一个点向后面每个点尝试连边，若已经联通则不连。

正确性简证：

首先若联通则不连显然成立，因为如果联通则前面一定出现了一次权值小于等于当前加边操作的加边。

每次操作加的边单独提出来一定能够凑成一个节点数为 $k$ 的单位完全图。

其最小生成树一定是随便取 $k-1$ 条边构成一棵树。

既然这样，我们不妨~~偷懒~~直接从第一个点向后面每个点连边。

证毕。

判断是否联通可以并查集。

但是求最小生成树权值怎么求？kruskal 吗？

不需要！

我们每次加边都是从小到大加，并且每次加都保证不与之前的边冲突。

这不就是 kruskal 模板吗！

在加边时统计答案即可。

时间复杂度 $\operatorname{O}(N\log N)$。

采用路径压缩 $+$ 按秩合并优化的并查集可以做到 

$\operatorname{O}(N\times\alpha(N))$。

```c++
#include <bits/stdc++.h>
#define LL long long
#define ULL unsigned long long
#define FOR(i,l,r) for(int i=l;i<=r;++i)
#define ROF(i,r,l) for(int i=r;i>=l;--i)
#define mkp make_pair
#define fr first
#define se second
#define pb push_back
using namespace std;
const int N=2e5+10;
int n,m,id[N],fa[N];
LL ans;
struct Node {
	int k,c;
	vector<int>a;
}ak[N];//离线
int cmp(int x,int y) {
	return ak[x].c<ak[y].c;
}
int Get(int x) {
	return x==fa[x]?x:fa[x]=Get(fa[x]);
}
void Merge(int x,int y) {//仅路径压缩
	x=Get(x),y=Get(y);
	fa[Get(y)]=Get(x); 
}
main() {
	cin>>n>>m;
	FOR(i,1,n) fa[i]=i;
	FOR(i,1,m) {
		scanf("%d%d",&ak[i].k,&ak[i].c);
		FOR(j,1,ak[i].k) {
			int x;
			scanf("%d",&x);
			ak[i].a.push_back(x);
		}
		id[i]=i;
	}
	sort(id+1,id+m+1,cmp);//直接对编号排序，可以避免vector搬运的巨大常数
	FOR(o,1,m) {
		int i=id[o];
		int x=ak[i].a[0];
		for(int j=1;j<ak[i].a.size();++j) {
			int y=ak[i].a[j];
			if(Get(x)!=Get(y)) {//尝试加边
				Merge(x,y);
				ans+=ak[i].c;//累计答案
			}
		}
	}
	int num=0;
	FOR(i,1,n) if(fa[i]==i) num++;
	if(num>=2) {//判断是否联通
		puts("-1");
		return 0;
	}
	cout<<ans<<"\n";
	return 0;
}
```

---

## 作者：Liuliuliuliuliu (赞：0)

[题目](https://www.luogu.com.cn/problem/AT_abc352_e)

# 题目大意
给你一个有 $N$ 个点的无向图 $G$，这些点标号为 $1 - N$。在最开始的时候，$G$ 没有边。

给你 $M$ 个操作加边。第 $i$ 个操作遵循以下原则。

- 给你一个子集 $S_i = \{A_{i,1},A_{i,2},A_{i,3},...,A_{i,k_i}\}$。对于任意一组 $u,v \in S_i$ 并且 $u < v$ 加一条权值为 $C_i$ 的边。

经过 $M$ 个操作之后，判断 $G$ 是否是联通的。如果是，输出其最小生成树的权值和。否则输出 `-1` 。

$2 \le N \le 200000$

$1 \le M \le 200000$

$2 \le K_i \le N$

$\sum_{i = 1}^{M} K_i \le 400000$

# 分析
按照题目描述中的输入建边显然是超时的。那么就来想。既然是要求最小生成树，那么只需要相邻两个点建一条边就可以了。这是因为它们的权值均为 $C_i$。或者让他们每个点都与 $1$ 号点建边。只需要保证图的连通性即可。

分析完以上这些，剩下的就是最小生成树的板子了。这里我用的是 `kruskal` 算法。

最后的最后，请不要忘记，~~不~~ **开 long long** ~~见祖宗~~！！！

# kruskal
本质实现为贪心和并查集。一开始每个点是一个单独的集合。先贪心的从小到大的排序每条边的权值。然后判断这条边的两个端点是否在同一个集合里。如果在，说明这两个点已经联通，所以就不用再连这条边了；否则，令 `ans+=e[i].w` 并将两个端点合并。具体实现看代码。

# 完整代码
```
#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<set>
#include<vector>
#include<algorithm>
#include<cstdlib>
using namespace std;
#define int long long
#define _INF 100000000
#define INF 0x3f3f3f3f 
inline int Read(){
    int x=0,f=1;
    char c=getchar();
    while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
    while(isdigit(c)){x=x*10+c-48;c=getchar();}
    return x*f;
}
inline void Write(int x){
	if(x<0) {putchar('-');x=-x;}
	if(x>9) Write(x/10);
	putchar(x%10+'0');
}

const int N=2e5+10,E=4e5+10;
int n,m,ans=0;
struct edge{
	int from,to,w;
}e[E<<1]; 
int num_Edge=0;
int fa[N];

bool cmp(edge A,edge B){
	return A.w<B.w;
}

int findf(int x){
	if(fa[x]==x) return x;
	return fa[x]=findf(fa[x]);
}

bool check(int x,int y){
	if(findf(x)!=findf(y)) return 1;
	return 0;
}

void merge(int x,int y){
	int fx=findf(x),fy=findf(y);
	fa[fx]=fy;
	return ;
}

signed main(){
	n=Read();m=Read();
	for(int i=1;i<=m;i++){
		int k=Read(),c=Read();
		int cina,cink;
		for(int j=1;j<=k;j++){
			cink=Read();
			if(j!=1){
				e[++num_Edge].from=cina;
				e[num_Edge].to=cink;
				e[num_Edge].w=c;				
			}
			cina=cink;
		}
	}
	sort(e+1,e+num_Edge+1,cmp);
	for(int i=1;i<=n;i++) fa[i]=i;
	for(int i=1;i<=num_Edge;i++){
		if(check(e[i].from,e[i].to)){
			ans+=e[i].w;
			merge(e[i].from,e[i].to);
		}
	}
	int cnt=0;
	for(int i=1;i<=n;i++){
		if(fa[i]==i) cnt++;
	}
	if(cnt>1) puts("-1");
	else printf("%lld",ans);
	return 0;
}
```

---

## 作者：Elysian_Realme (赞：0)

# AT_abc352_e

## 解题思路

**可以每一组 $a$ 中组成可以同时选择多条边，别读错题了（悲）。**

显然是一个 MST，kruscal 板子就可以了。不过需要注意一点，枚举每一条边显然是炸掉了。考虑到同一组 $a$ 里的所有点都一定处于同一个连通块，所以只连相邻的两个点即可。

[code](https://atcoder.jp/contests/abc352/submissions/53198838)

```cpp
// Problem: E - Clique Connect
// Contest: AtCoder - AtCoder Beginner Contest 352
// URL: https://atcoder.jp/contests/abc352/tasks/abc352_e
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// 
// By：lmq
// AC Time：2024-05-06 20:08:06

#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
struct edge{
	int u,v,w;
	bool operator<(edge b)const{
		return w<b.w;
	}
};
vector<edge> g;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int n,m,sum,cnt;
int p[N];
int root(int x){
	if(p[x]==x)return x;
	return p[x]=root(p[x]);
}
int kruskal(){
	for(int i=1;i<=n;i++)
		p[i]=i;
	int cnt=0,sum=0;
	sort(g.begin(),g.end());
	for(edge i:g){
		int u=root(i.u),v=root(i.v),w=i.w;
		if(u==v)continue;
		p[u]=v,cnt++,sum+=w;
		if(cnt==n-1)return sum;
	}
	return -1;
}
signed main(){
	cin>>n>>m;
	while(m--){
		int k,c,u,v;cin>>k>>c>>u;
		for(int i=2;i<=k;i++){
			cin>>v;
			g.push_back((edge){u,v,c});
			u=v;
		}
	}
	cout<<kruskal()<<endl;
	return 0;
}

```

---

## 作者：Vitamin_B (赞：0)

# 思路
首先显然不能 $O(\sum m^2)$ 暴力建边求最小生成树，要考虑更快的方法。让我们来回顾一下 kruskal 的实现过程：
1. 先把所有边排序；
1. 再按边权从小到大进行并查集，逐渐合并每个连通块，直到合并成一个块。

这个思路在这题中仍然可行。因为每个子集的所有边权是相同的，所以我们把所有子集按边权 $c_i$ 排序，然后把子集中的每个点与 $a_{i,1}$ 合并一下就行了。最后不连通就无解。
# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair <int, int> pii;
typedef pair <ll, ll> pll;
int n, m, k[200005], c[200005], id[200005], f[200005], x, y, tot = 1;
vector <int> v[200005];
ll sum;
int find (int x) {
	return x == f[x] ? x : f[x] = find (f[x]);
}
bool cmp (const int& x, const int& y) {
	return c[x] < c[y];
}
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> n >> m;
	for (int i = 1; i <= n; ++ i)
		f[i] = i;
	for (int i = 0; i < m; ++ i) {
		id[i] = i;
		cin >> k[i] >> c[i];
		for (int j = 0; j < k[i]; ++ j)
			cin >> x, v[i].emplace_back (x);
	}
	sort (id, id + m, cmp);
	for (int i = 0; i < m; ++ i) {
		x = v[id[i]][0];
		for (int j = 1; j < k[id[i]]; ++ j) {
			y = v[id[i]][j];
			if (find (x) != find (y)) {
				f[find (x)] = find (y);
				++ tot;
				sum += c[id[i]];
			}
		}
	}
	cout << (tot < n ? -1 : sum);
	return 0;
}
```

---

## 作者：zhangjiting (赞：0)

## 思路

如果对于每一组，我们都认为每两个点之间都有边，根本做不了。

但最小生成树要求的是总权值最小，所以只要认为 $A_{i,j}$ 和 $A_{i,j+1}$ 存在一条权值为 $C_i$ 的边就可以。

对于所有操作，离线下来按 $C_i$ 从小到大排序，直接跑 Kruskal 就好了。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
#define debug(x) cout<<#x<<':'<<x<<endl
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
using namespace std;
const int N=2e5+5;
int n,m,f[N],ans,tot;
struct node{
	int k,c;
	vector<int> a;
}e[N];
bool cmp(node x,node y){
	return x.c<y.c;
}
int find(int x){
	if(x==f[x]) return x;
	else return f[x]=find(f[x]);
}
signed main(){
	IOS;
	cin>>n>>m;
	for(int i=1;i<=n;i++) f[i]=i;
	for(int i=1;i<=m;i++){
		cin>>e[i].k>>e[i].c;
		e[i].a.push_back(0);
		for(int j=1,x;j<=e[i].k;j++){
			cin>>x;
			e[i].a.push_back(x);
		}
	}
	sort(e+1,e+m+1,cmp);
	for(int i=1;i<=m;i++){
		for(int j=1;j<e[i].k;j++){
			int u=e[i].a[j],v=e[i].a[j+1];
			u=find(u),v=find(v);
			if(u==v) continue;
			ans+=e[i].c;
			tot++;
			f[u]=v;
			if(tot==n-1) return cout<<ans,0;
		}
	}
	cout<<-1;
    return 0;
}
```

---

