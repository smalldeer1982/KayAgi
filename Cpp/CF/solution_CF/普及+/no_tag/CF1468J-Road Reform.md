# Road Reform

## 题目描述

There are $ n $ cities and $ m $ bidirectional roads in Berland. The $ i $ -th road connects the cities $ x_i $ and $ y_i $ , and has the speed limit $ s_i $ . The road network allows everyone to get from any city to any other city.

The Berland Transport Ministry is planning a road reform.

First of all, maintaining all $ m $ roads is too costly, so $ m - (n - 1) $ roads will be demolished in such a way that the remaining $ (n - 1) $ roads still allow to get to any city from any other city. Formally, the remaining roads should represent an undirected tree.

Secondly, the speed limits on the remaining roads might be changed. The changes will be done sequentially, each change is either increasing the speed limit on some road by $ 1 $ , or decreasing it by $ 1 $ . Since changing the speed limit requires a lot of work, the Ministry wants to minimize the number of changes.

The goal of the Ministry is to have a road network of $ (n - 1) $ roads with the maximum speed limit over all roads equal to exactly $ k $ . They assigned you the task of calculating the minimum number of speed limit changes they have to perform so the road network meets their requirements.

For example, suppose the initial map of Berland looks like that, and $ k = 7 $ :

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1468J/9e4deeb1d4ca30454fafffe4f5580702d72a87b0.png)Then one of the optimal courses of action is to demolish the roads $ 1 $ – $ 4 $ and $ 3 $ – $ 4 $ , and then decrease the speed limit on the road $ 2 $ – $ 3 $ by $ 1 $ , so the resulting road network looks like that:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1468J/3406c65bb53e89861f39906767c44d2e2eb9dc4d.png)

## 说明/提示

The explanation for the example test:

The first test case is described in the problem statement.

In the second test case, the road network initially looks like that:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1468J/43a8595a75dedb1e97ea060aa027d63f3c69ff5a.png)The Ministry can demolish the roads $ 1 $ – $ 2 $ , $ 3 $ – $ 2 $ and $ 3 $ – $ 4 $ , and then increase the speed limit on the road $ 1 $ – $ 4 $ three times.

In the third test case, the road network already meets all the requirements.

In the fourth test case, it is enough to demolish the road $ 1 $ – $ 2 $ so the resulting road network meets the requirements.

## 样例 #1

### 输入

```
4
4 5 7
4 1 3
1 2 5
2 3 8
2 4 1
3 4 4
4 6 5
1 2 1
1 3 1
1 4 2
2 4 1
4 3 1
3 2 1
3 2 10
1 2 8
1 3 10
5 5 15
1 2 17
3 1 15
2 3 10
1 4 14
2 5 8```

### 输出

```
1
3
0
0```

# 题解

## 作者：XXh0919 (赞：5)

太久没写题解，咕值都快掉没了……写篇题解涨涨咕。

### 解法

题目中说要使得这一棵树的边权总值正好等于 $k$，不难想到用最小生成树。我们先用 kruskal 进行最小生成树，接着判断若有边权值大于 $k$，就把此边变为 $k$，否则不变。

### AC Code

```cpp
#include<bits/stdc++.h>
#define int long long
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define per(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int N=3e5+15;

int n,m,k,ans,cnt;
int fa[N];
struct edge{
	int u,v,w;
}e[N];

bool cmp(edge a,edge b){
	return a.w<b.w;
}

int find(int x){
	return x==fa[x]?x:(fa[x]=find(fa[x]));
}

void join(int x,int y){
	int f1=find(x),f2=find(y);
	if(f1!=f2)fa[f1]=f2;
}

int kruskal(){
	rep(i,1,n)fa[i]=i;
	sort(e+1,e+m+1,cmp);
	rep(i,1,m){
		if(find(e[i].u)!=find(e[i].v)){
			join(e[i].u,e[i].v);
			cnt=max(cnt,e[i].w);
			if(cnt>k)ans+=cnt-k;
		}
	}
	if(cnt<k){
		ans=0x3f3f3f3f;
		rep(i,1,m){
			ans=min(ans,abs(k-e[i].w));
		}
	}
	return ans;
}

void solve(){
	ans=cnt=0;
	cin>>n>>m>>k;
	rep(i,1,m){
		int u,v,w;
		cin>>u>>v>>w;
		e[i]=(edge){u,v,w};
	}
	cout<<kruskal()<<endl;
	
}

signed main(){
	ios::sync_with_stdio(0);
	int T=1;
	cin>>T;
	while(T--)solve();
	return 0;
} 
```

---

## 作者：shuangmu (赞：5)

首先我们看到这个题要求让最长的边权恰为 $k$，不难想到最小生成树。我们只需要把最小生成树中边权比 $k$ 大的边调为 $k$ 就行了。当最小生成树中有边权大于等于 $k$ 的边时，该结论正确，因为按照 kruskal 的过程，如果我们构造的不是最小生成树（即选择其他边权较大的边），那调整的代价一定大于最小生成树。  
如果最小生成树中所有边都比 $k$ 小呢？我们只需要找到边权最接近 $k$，即 $ \vert w-k \rvert $ 最小的边来替换即可，因为最小生成树保证图中各点联通，用其他非最小生成树中的边来替换，一定不会增加其他非最小生成树的边。
代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 2e5+100;

inline int read(){
	int x = 0; char ch = getchar();
	while(ch<'0' || ch>'9'){ch = getchar();}
	while(ch>='0'&&ch<='9'){x = x*10+ch-48, ch = getchar();}
	return x;
}

struct node{
	int u, v, w;
	bool operator < (const node &b) const{
		return w<b.w;
	}
}edge[N<<1];

int T;
int n, m, K;

int fa[N], siz[N];
inline int find(int x){
	if(x != fa[x]) fa[x] = find(fa[x]);
	return fa[x];
}
bool merge(int x, int y){
	x = find(x), y = find(y);
	if(x == y) return 0;
	fa[x] = y;
	return 1;
}

int main(){ 
	T = read();
	while(T--){
		n = read(), m = read(), K = read();
		for(int i = 1; i<=m; ++i){
			edge[i].u = read(), edge[i].v = read(), edge[i].w = read();
		}
		for(int i = 1; i<=n; ++i) fa[i] = i; 
		sort(edge+1, edge+m+1);
		ll ans = 0, mx = 0;
		for(int i = 1; i<=m; ++i){
			if(merge(edge[i].u, edge[i].v)){
				mx = max(mx, 1ll*edge[i].w);
				ans+=(edge[i].w>K?edge[i].w-K:0);
			}
		}
		if(mx<K){
			ans = 0x3f3f3f3f3f3f3f3f;
			for(int i = 1; i<=m; ++i){
				ans = min(ans, 1ll*abs(edge[i].w-K));
			}
		}
		printf("%lld\n", ans);
	}
	return 0;
}
```

---

## 作者：jianhe (赞：4)

[link](https://www.luogu.com.cn/problem/CF1468J)


## 前言：
1. 多测不清空，爆零两行泪~
2. 注意自己的变量名！

我因此调了好久。

## 算法：最小生成树

首先看题。

题目中说：要在图中保留 $n-1$ 条边，使它变成一棵树。

因此想到 **最小生成树**。

我这里用的是 `Kruskal`，需要用到并查集。

因此要注意并查集要初始化！

大家应该都知道 `Kruskal` 算法的流程是：先对边权从小到大排序，再枚举每一个 $i$，看一下所对应的 $u$ 和 $v$ 是否在同一个集合内。如果不是，就可以选择这一条边。

做完最小生成树以后，我们要进行分类讨论：

计最小生成树中最大的边权为 $t$。

当 $t < k$ 时，遍历所有边，取与 $k$ 差值最小的即可。

当 $t > k$ 时，将所有边权与 $k$ 的差值相加即可。

注意多测要清空即可。

## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N=4e5+10,inf=2e9;
ll T,n,m,k,t,ans,ct,fa[N];
struct E{
	ll u,v,w;
}a[N];
bool cmp(E l,E r){
	return l.w<r.w;
}
void jian(){
	for(int i=1;i<=n;i++) fa[i]=i;
}
ll getfa(ll x){
	return fa[x]==x?x:fa[x]=getfa(fa[x]);
}
void kruskal(){
	jian();ct=t=ans=0;//多测不清空，爆零两行泪！
	sort(a+1,a+m+1,cmp);
	for(int i=1;i<=m;i++){
		ll x=getfa(a[i].u),y=getfa(a[i].v);
		if(x==y) continue;
		t=a[i].w,ans+=max(t-k,0ll),fa[x]=y;
		//因为边权是从小到大枚举的，所以当前值一定是最大的
	}
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n>>m>>k;
		for(int i=1;i<=m;i++)
			cin>>a[i].u>>a[i].v>>a[i].w;
	    kruskal();
	    if(t<k){
	    	ans=inf;//不要忘记
	    	for(int i=1;i<=m;i++)
				ans=min(ans,abs(a[i].w-k));
		}//t>k的情况在做最小生成树的时候顺便求出来了
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：_ZML_ (赞：2)

# 思路
先进行最小生成树。

把树上的边分成大于 $k$ 和小于 $k$ 进行讨论。

1. 有边大于 $k$ 时把它变成 $k$。
2. 否则不变。

记得多测清空。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pb push_back
#define rep(i,x,y) for(int i=x;i<=y;i++)
#define down(i,x,y) for(int i=x;i>=y;i--)
#define pii pair<int,int>
#define fi first
#define sc second
#define open_O2 ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define mem(x,y) memset(x,y,sizeof(x))
#define vec vector
struct node{
	int x,y,z;
}edge[300010];
bool cmp(node x,node y){
	return x.z<y.z;
} 
int fa[200010];
int get(int x){
	if(fa[x]==x) return x;
	return fa[x]=get(fa[x]);
}
signed main() {
// 	freopen("road.in","r",stdin);
// 	freopen("road.out","w",stdout);
	int T;
	cin>>T;
	while(T--){
		int n,m,k;
		cin>>n>>m>>k;
		for(int i=1;i<=n;i++) fa[i]=i;
		for(int i=1;i<=m;i++){
			int u,v,w;
			cin>>u>>v>>w;
			edge[i]={u,v,w};
		}
		sort(edge+1,edge+m+1,cmp);
		int cnt=0,ans=0;
		for(int i=1;i<=m;i++){
			int x=get(edge[i].x), 
				y=get(edge[i].y);
			if(x==y) continue;
			fa[x]=y;
			cnt=max(cnt,edge[i].z);
			if(cnt>k) ans+=cnt-k;
		}
		if(cnt<k){
			ans=0x3fffffff;
			for(int i=1;i<=m;i++){
				ans=min(ans,abs(k-edge[i].z));
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}

```

---

## 作者：zhuweiqi (赞：2)

本题是一道不错的图论题，思路非常巧妙。

首先，我们考虑用 Kruskal 求出这张图的[最小生成树](https://www.luogu.com.cn/problem/P3366)（由于题目保证初始时给定的图满足任意两个点互相可达，所以不用考虑无解的情况），根据求最小生成树的原理，我们必定优先选择边权较小的边，因此如果最小生成树中边权最大的边的权值 $\geq k$，我们的操作次数肯定是最小的（这种情况下的操作次数即为把最小生成树中所有边权 $>k$ 的边的权值减到 $k$ 为止）；否则，我们考虑最小生成树中边权最大的边的权值（设为 $maxs$）$<k$ 的情况，相信这种策略对于了解过基环树或严格次小生成树的读者们并不陌生，由于 $maxs<k$，所以我们可以贪心地选择一条**尚未在最小生成树上**且边权 $\geq maxs$ 的边，使其最后的权值通过最少次数的操作变为 $k$，从而使得最小生成树中所有边权的最大值正好等于 $k$，由于题目保证了没有重边或自环，所以加入此边后原来的最小生成树就成为了基环树，我们只需要断一条在环上的其它边，就可以使其再次成为生成树啦。参考代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+2,M=2e5+2;
struct edge{
	int x,y,z;
}e[M];
bool cmp(edge x,edge y){return x.z<y.z;}
int f[N];
inline int find(int x){
	if(x==f[x]) return x;
	return f[x]=find(f[x]);
}
int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		int n,m,k;
		scanf("%d%d%d",&n,&m,&k);
		for(int j=1;j<=m;j++) scanf("%d%d%d",&e[j].x,&e[j].y,&e[j].z);
		sort(e+1,e+1+m,cmp);
		int cnt=n;
		for(int i=1;i<=n;i++) f[i]=i;
		long long ans=0;
		for(int j=1;j<=m;j++){
			if(find(e[j].x)!=find(e[j].y)){
				f[f[e[j].x]]=f[e[j].y];
				if(e[j].z>k) ans+=e[j].z-k;
				if(--cnt==1){
					if(e[j].z<k){
						ans=1e18;
						for(;j<=m;j++) ans=min(ans,(long long)abs(e[j].z-k));
					}
					break;
				}
			}
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：Light_Pursuer (赞：1)

# [Road Reform - 洛谷](https://www.luogu.com.cn/problem/CF1468J) 1800

## Soluition

由于题目中只说了要求所有边权中的最大值。因此不难想到，我们需要求一个最小生成树。

求完最小生成树之后，我们只需要考虑最小生成树的最大边即可。

先预处理出和 $k$ 最接近的边，假设为 $P$。

如果最小生成树的最大边已经大于 $k$ 了，那么只能运用当前的最小生成树作为结果。如果最小生成树的最大边小于 $k$ 的话，那么只能加入 $P$ 这条边，再删去原最小生成树一条边即可。

code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=200005;
int read()
{
	int ret=0,f=1;char c=getchar();
	while(c<'0'||c>'9') 
	{
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		ret=ret*10+c-'0';
		c=getchar();
	}
	return ret*f;
}
int n,m,k,fa[N],minn,maxx,ans;
struct node
{
	int u,v,w;
}edge[N];
bool cmp(node x,node y)
{
	return x.w<y.w;
}
int find(int u)
{
	if(fa[u]==u)
	{
		return u;
	} 
	return fa[u]=find(fa[u]);
}
void kruskal()
{
	sort(edge+1,edge+1+m,cmp);
	for(int i=1;i<=m;i++)
	{
		if(fa[find(edge[i].u)]!=fa[find(edge[i].v)])
		{
			maxx=max(maxx,edge[i].w);
			fa[find(edge[i].u)]=fa[find(edge[i].v)];
			if(edge[i].w>k)
			{
				ans+=edge[i].w-k;
			}
		}
	}
}
signed main()
{
	int t;t=read();
	while(t--)
	{
		n=read(),m=read(),k=read();
		for(int i=1;i<=n;i++)
		{
			fa[i]=i;
		}
		minn=1e12,ans=0,maxx=0;
		for(int i=1;i<=m;i++)
		{
			edge[i].u=read(),edge[i].v=read(),edge[i].w=read();
			minn=min(minn,abs(k-edge[i].w));
		}
		kruskal();
		if(maxx<k)
		{
			cout<<minn<<endl;
		}
		else
		{
			cout<<ans<<endl;
		}
	}
	return 0;
}
```

---

## 作者：zhujiangyuan (赞：0)

最小生成树、分类讨论。

首先 Kruskal 跑一个最小生成树，如果 MST 上的边大于 $k$，需要减到 $k$，换其他边不会更优。

如果最小生成树上边权的最大值小于 $k$，答案为 $\min\limits_{i=1}^m|w_i-k|$。因为将最小生成树外的任意一条边加到最小生成树上，都可以去掉原 MST 上的一条边使得其仍为一颗生成树。

提交记录：<https://codeforces.com/contest/1468/submission/269890774>。

---

## 作者：Merge_all (赞：0)

## 思路：
- 第一眼得到的思路：最小生成树。可以用吗？最小生成树得到的值是**用贪心得到的最优解**，而这道题正好可以使用。

- 怎么做？首先将边权**从小到大排一遍序**，求出最小生成树中所有的边权。这个时候分两种情况：

    1. **最小生成树中有边权大于** $k$，这时用一个变量存所有边权大于 $k$ 的 $z_{i}$ 的权值 和 $k$ 的差相加的和，就是答案。
    
    2. 如果所有**最小生成树中所有的边权小于** $k$，就求出 $\lvert k - z_{i} \rvert$ 中最小的值，那就是答案。

#### 代码：
```
#include <bits/stdc++.h>
#define int long long

namespace My_std {
	inline int read() {
		int x = 0, f = 1;
		char ch = getchar();
		while (ch < '0' || ch > '9') {
			if (ch == '-')
				f = -1;
			ch = getchar();
		}
		while (ch >= '0' && ch <= '9') {
			x = (x << 3) + (x << 1) + (ch ^ 48);
			ch = getchar();
		}
		return x * f;
	}
}
using namespace My_std;
using namespace std;
#define endl "\n"
const int N = 200100;
int T, n, m, k;
int u, v, w;
int Max_num, Max, cnt;
int f[N];

struct edge {
	int x, y, z;
} a[N << 1];

bool cmp(edge x, edge y) {
	return x.z < y.z;
}

int find(int x) {//并查集维护
	return x == f[x] ? x : f[x] = find(f[x]);
}

void init() {
	Max = 0;
	Max_num = 0;
	cnt = 0;//多测不清空，亲人两行泪
	for (int i = 1; i <= n; i++)
		f[i] = i;
	for (int i = 1; i <= m; i++) {
		cin >> u >> v >> w;
		a[i] = {u, v, w};
	}
}

void solve() {
	sort(a + 1, a + m + 1, cmp);
	for (int i = 1; i <= m; i++) {
		if (cnt == n - 1)
			break;
		int fx = find(a[i].x), fy = find(a[i].y);
		if (fx != fy) {
			cnt++;
			Max_num = max(Max_num, a[i].z);
			f[fx] = fy;
			if (Max_num > k)
				Max += (Max_num - k);
		}
	}
	if (Max_num < k) {
		Max = INT_MAX;
		for (int i = 1; i <= m; i++)
			Max = min(Max, abs(k - a[i].z));
	}
}

void print() {
	cout << Max << endl;
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);//用cin更方便，这题不用卡常
	cin >> T;
	while (T--) {
		cin >> n >> m >> k;
		init();
		solve();
		print();
	}
	return 0;
}
```

---

## 作者：Zhuluoan (赞：0)

## 题目简述
给定一个有 $n$ 个节点，$m$ 条无向带权边的图，和一个参数 $k$，第 $i$ 条边权值为 $s_i$。

现在你要保留这个图中的 $n-1$ 条边使得这个图变成一棵树，然后你可以对这棵树上的任意边进行修改，每次修改可以使这个边的权值加上一或减去一。

现在你需要使所有边权的最大值**正好等于** $k$，求所有保留方案的最小操作数。

## 题目分析
首先，发现此题要求的是最大值等于 $k$，易想到先做出最小的情况，再调整最大值逼近 $k$，并且本题还要将一张图变成一棵树，综上所述，可以想到先求出图的最小生成树。

接下来，我们可知最小生成树的最大值，令它为 $\max$，我们可分以下三种情况尽行讨论：

- 如果 $\max\lt k$，我们可以遍历所有的边，找一条最接近 $k$ 的边，他们之间的差的绝对值便是答案。由生成树的性质可知，使这条边替换生成树的一条边后生成树仍然可以是一棵树，符合题意。
- 如果 $\max=k$，不需要调整，答案为 $0$。
- 如果 $\max\gt k$，我们应遍历所有树边，将凡是大于 $k$ 的树边都减小使它等于 $k$，并累加他们的差，这样才能符合要求。由于是最小生成树，易证此为最优解。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int n,m,t,k,fu[N],Max,a[N],b[N],cnt1;
unsigned long long ans;
struct edge
{
	int u,v,w;
	friend bool operator < (edge x,edge y)
	{
		return x.w<y.w;
	}
}e[N];
int find(int x)
{
	return fu[x]==x?x:fu[x]=find(fu[x]);
}
void solve()
{
	cin>>n>>m>>k;
	cnt1=0;
	ans=-1;
	memset(e,0,sizeof e);
	memset(fu,0,sizeof fu);
	for(int i=1;i<=n;i++)
	{
		fu[i]=i;
	}
	for(int i=1;i<=m;i++)
	{
		cin>>e[i].u>>e[i].v>>e[i].w;
	}
	sort(e+1,e+1+m);
	for(int i=1;i<=m;i++)
	{
		int x=e[i].u,y=e[i].v;
		if(find(x)!=find(y))
		{
			fu[find(x)]=find(y);
			Max=e[i].w;
			b[++cnt1]=e[i].w;
		}
		a[i]=e[i].w;
	}
	if(Max<k)
	{
	    for(int i=1;i<=m;i++)
	    {
	    	ans=min(ans,1ull*abs(k-a[i]));
		}
	}
	else
	{
		ans=0;
		for(int i=1;i<=cnt1;i++)
		{
			if(b[i]>=k) ans+=b[i]-k;
		}
	}
    cout<<ans<<"\n";
}
int main()
{
	cin>>t;
	while(t--)
	{
		solve();
	}
	return 0;
}
```

---

## 作者：WA_sir (赞：0)

## [题目](https://codeforces.com/problemset/problem/1468/J)|[链接](https://www.luogu.com.cn/problem/CF1468J)

### 题目大意

对于一个 $n$ 点 $m$ 边的无向图，保留 $n-1$ 条边使其变成树。每次操作可以对一条边权修改 $1$，使得边权中最大值为 $k$，求操作次数。

### 题目分析

对于图转树的问题，很容易想到最小生成树。可以先求出图的最小生成树，然后进行分类讨论。分类讨论的标准应为得出的最小生成树所有边权的最大值。

1. 最大值 $\le k$，此时只需将最大边改为离 $k$ 最近的边，再计算这一条边的修改次数。

2. 最大值 $> k$，将所有 $> k$ 的边修改，将修改次数相加。

### 参考代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct node{
	int u,v,w;
}e[200005],ee[200005];
int t,n,m,k,ans,fa[200005],cnt,min_;
bool qu_mi;
bool cmp(node na,node nb)
{
	return na.w<nb.w;
}
int gf(int x)
{
	if(x-fa[x])return fa[x]=gf(fa[x]);
	return x;
}
signed main()
{
	scanf("%lld",&t);
	while(t--)
	{
		cnt=0;min_=1e18;
		scanf("%lld%lld%lld",&n,&m,&k);
		for(int i=1;i<=n;i++)fa[i]=i;
		for(int i=1,uu,vv,ww,j=1;i<=m;i++,j++)
		{
			scanf("%lld%lld%lld",&uu,&vv,&ww);
			e[j]=node{uu,vv,ww};
			min_=min(min_,abs(ww-k));
		}
		sort(e+1,e+m+1,cmp);
		for(int i=1;i<=m&&cnt<n-1;i++)
		{
			int u=gf(e[i].u),v=gf(e[i].v);
			if(u-v)
			{
				ee[++cnt]=e[i];
				fa[u]=v;
			}
		}
		ans=0;
		if(ee[cnt].w<=k)ans=min_;
		else
			for(int i=cnt;i;i--)
				if(ee[i].w>k)ans+=ee[i].w-k;
				else break;
		printf("%lld\n",ans);
	}
	return 0;
}
```

感谢阅读。

---

## 作者：lhc0707 (赞：0)

## 题意

给定一个无向带权图，保留其中的 $n-1$ 条边使这个图变成一棵树，然后每次操作让一条边的边权加一或减一，求使得最大边权恰好为 $k$ 的最小操作数。

## 题解

先跑一遍最小生成树。我们知道最小生成树有两层含义，一层是边权和最小，还有一层就是最大边权最小。在跑最小生成树的时候，记录下当前最大的边权。为什么我们要让最大边权最小呢？因为如果最大边权比 $k$ 大，那么最小代价也就是必然的代价就要加上当前最大边权的权值减 $k$ 的值，把这个值加入最终结果。

如果跑完最小生成树后，最大边权大于等于 $k$，那我们可以直接输出结果。如果最大边权小于 $k$，我们就应该考虑，可不可以用另外一条边 $(u,v)$ 代替当前的最大边权。显然，如果想让这条边权值 $w$ 与 $k$ 的绝对值更小，这条边边权一定大于最小生成树中找到的最大边权，这样就可以确保新边的边权一定是生成树的最大边权，接下来，枚举每条边即可。

注意：本题有多组数据，记得赋初值。还有，一定要开 `long long`。

## 代码
```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<cmath>
#define int long long
using namespace std;
const int N=250010;
int T,n,m,k,fa[N];
struct edge{int u,v,w;}e[N];
bool operator <(edge a,edge b){return a.w<b.w;}
inline int find(int x){
	if(fa[x]==x)return x;
	return fa[x]=find(fa[x]);
}
inline bool merge(int u,int v){
	u=find(u),v=find(v);
	if(u==v)return false;
	fa[u]=v;return true;
}
signed main(){
	scanf("%lld",&T);
	while(T--){
		int MaxNum=0,ans=0;
		scanf("%lld%lld%lld",&n,&m,&k);
		for(int i=1;i<=n;i++)fa[i]=i;
		for(int i=1;i<=m;i++)
			scanf("%lld%lld%lld",&e[i].u,&e[i].v,&e[i].w);
		sort(e+1,e+1+m);
		for(int i=1;i<=m;i++){
			if(merge(e[i].u,e[i].v)){
				MaxNum=max(MaxNum,e[i].w);
				if(MaxNum>k)ans+=MaxNum-k;
			}
		}
		if(MaxNum<k){
			ans=0x3f3f3f3f;
			for(int i=1;i<=m;i++)
				ans=min(ans,abs(e[i].w-k));
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

望过审QWQ。

---

## 作者：Night_fall (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1468J)

------------

把图变成树，易想到[最小生成树](https://www.luogu.com.cn/problem/P3366)。

重点在于树上**边权的最大值正好等于 $k$。**

那么分类讨论：

1. 当树上有边大于等于 $k$ 时，把所有边权大于等于 $k$ 的边变成 $k$，直接输出。

2. 否则（树上所有边权均小于 $k$）寻找最接近 $k$ 的边，易证：只需要把这个边的边权变为 $k$ 即为答案。

按照这个思路写就行啦~

------------

### Code

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
#define int long long

struct EDGE{
    int u,v,c;
    bool operator<(const EDGE&x){return c<x.c;}
} e[200010];
int f[200010];
int find(int x){return f[x]=(f[x]==x?x:find(f[x]));} //最小生成树

signed main(){
	int T;
	cin>>T;
	while(T--){
	    int n,m,k;
	    scanf("%lld%lld%lld",&n,&m,&k);
	    int mint=1e9;
	    for(int i=1;i<=n;i++) f[i]=i;
	    for(int i=1;i<=m;i++) scanf("%lld%lld%lld",&e[i].u,&e[i].v,&e[i].c),mint=min(mint,abs(k-e[i].c)); //mint预处理出最接近k的边权
	    sort(e+1,e+1+m);
	    int ans=0,cnt=1;
	    for(int i=1;i<=m;i++){
	        int u=e[i].u,v=e[i].v;
	        if(find(u)!=find(v)) f[find(u)]=find(v),ans+=max(0ll,e[i].c-k),cnt++;
	        if(cnt==n){
	            break;
	        }
           //ans算出大于k的边边权的答案
	    }
	    if(ans) printf("%lld\n",ans); //情况1
       else printf("%lld\n",mint); //情况2
	}
    return 0;
}
```

---

## 作者：Helloworldwuyuze (赞：0)

# CF1468J 题解

### 题意

#### [传送门](https://www.luogu.com.cn/problem/CF1468J)

给定 $n$ 个点和 $m$ 条带权无向边，以及一个常数 $k$，求在这个图中建一棵生成树并在这棵树上进行操作，每次操作可以让这棵生成树上的任意一条边增加或减小一点边权，问如何生成一棵树才能使操作次数最少。

## Solution

### 前置知识

最小生成树，不会的[去这里](https://www.luogu.com.cn/problem/P3366)。

### 正文

在一个图上生成一棵树，我们马上就会想到最小生成树，我们设 $maxx$ 表示最小生成树中的最大权值，那么不难想到：

- 1. 如果 $maxx>k$ 显然最小生成树中权值大于 $k$ 的边权与 $k$ 的差值和。

- 2. 如果 $maxx\le k$ 那么答案就是 $\min_{i=1}^m\{|s_i-k|\}$。

#### 证明

- 第一种情况，因为最小生成树已经是权值和最小的树了，那么超过 $k$ 的边权与 $k$ 的差值之和也一定最小，所以把所有大于 $k$ 的边权与 $k$ 的差值加起来就一定是最优答案。

- - 第二种情况，因为 $maxx<k$，我们可以把最小生成树中的一条边舍弃，再加入那一条边权离 $k$ 最近的边，那个值就是答案。但还有一个问题，如何证明能够找到一条边使得再最小生成树中删掉该边再连上那条权值离 $k$ 最近的边能够形成一棵树呢？

- - 其实，我们知道一个无向图拥有最小生成树的充要条件是图联通，如果我们能够找到一条 $maxx<k$ 的树，那么就说明所有权值小于 $k$ 的边能够让图联通，那么再加入一条离 $k$ 最近的边也一定联通，那么就一定可以在加入权值离 $k$ 最近的边的情况下生成最小生成树。

### ```AC CODE```

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<ctime>
#include<algorithm>
#include<cstring>
#include<string>
#include<vector>
#include<queue>
#define EN puts("")
#define endl '\n'
#define space putchar('')

using namespace std;
const int INF = 0x3f3f3f3f;
#define int long long

const int N = 2e5 + 10;
const int M = 2e5 + 10;
#define x first
#define y second

int T,n,m,k;
int fa[N];
pair<int,pair<int,int>> e[N];

int find(int x){return x==fa[x]?fa[x]:fa[x]=find(fa[x]); }

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n>>m>>k;
        int minn=INF,c=0,sum=0;
        for(int i=1;i<=n;++i)   fa[i]=i;
        for(int i=1;i<=m;++i){
            cin>>e[i].y.x>>e[i].y.y>>e[i].x;
            minn=min(minn,abs(e[i].x-k));
        }
        sort(e+1,e+1+m);
        for(int i=1;i<=m;++i){
            int a=find(e[i].y.x), b=find(e[i].y.y);
            if(a==b)    continue;
            fa[a]=b;
            if(e[i].x>k)    sum+=e[i].x-k;
            if(++c==n-1)    break;
        }
        if(sum) cout<<sum<<endl;
        else    cout<<minn<<endl;
    }
    return 0;
}
```

---

