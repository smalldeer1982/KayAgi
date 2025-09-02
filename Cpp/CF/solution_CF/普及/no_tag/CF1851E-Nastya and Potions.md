# Nastya and Potions

## 题目描述

炼金术士 Nastya 很喜欢合成药水。现有 $ n $ 种药水，第 $ i $ 种药水可以用 $ c_i $ 个金币买入。

任何一种药水的合成方案都不超过 $ 1 $ 种。在合成某种药水的过程中，作为原料的药水将会被**完全消耗**。任何药水都不能直接或间接合成它本身。

作为一个经验老道的炼金术士，Nastya 已经可以**无限制地**获得 $ p_1, p_2, \dots, p_k $ 这 $ k $ 种药水，可是她却没法决定接下来要合成哪些药水。于是，她求助于你。对于 $ 1 \le i \le n $，她需要你求出获得第 $ i $ 种药水所需的最少的金币数。

## 说明/提示

对于样例一的第一组测试数据，最优方案如下：

- 用药水 $ 2, 4, 5 $ 合成药水 $ 1 $。
- 药水 $ 2 $ 只能买入。
- 药水 $ 3 $ 是无限制供应的。
- 相较于用药水 $ 3, 5 $ 合成药水 $ 4 $，直接买入更划算。
- 药水 $ 5 $ 只能买入。

## 样例 #1

### 输入

```
4
5 1
30 8 3 5 10
3
3 2 4 5
0 
0 
2 3 5
0 
3 2
5 143 3
1 3
1 2
0 
2 1 2
5 1
5 4 1 3 4
2
2 4 5
3 3 5 4
2 1 4
1 5
0 
4 2
1 1 5 4
2 4
3 2 4 3
0 
2 2 4
1 2```

### 输出

```
23 8 0 5 10 
0 143 0 
5 0 1 3 4 
0 0 0 0```

## 样例 #2

### 输入

```
3
6 3
5 5 4 5 2 2
3 4 5
2 2 5
1 5
3 4 1 6
4 2 6 1 5
0 
0 
6 2
1 4 4 1 5 2
3 6
4 6 3 4 5
4 6 5 3 4
0 
1 5
1 6
0 
2 1
4 3
1
0 
1 1```

### 输出

```
0 0 0 0 0 2 
0 0 0 0 0 0 
0 0```

# 题解

## 作者：_Only_this (赞：3)

### CF1851E Nastya and Potions 题解

------------

搞不懂为何把这题放在 E，或许是 cf 对数据结构情有独钟？？

这题就是个裸的拓扑排序板子啊。。

------------

题目保证无环，所以大胆跑拓扑。

将合成药水的步骤当做一条权值为 $0$ 的有向边，将购买药水的钱数当做制成此药水的初始最小价钱，当然还要注意无数瓶药水的情况，然后跑拓扑就行了啊。

贴个代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 2e5+5;
const ll inf = 7e18;
struct qwe{
	int ne,to,val;
}e[maxn<<1];
int T,n,k,idx;
int a[maxn],head[maxn],in[maxn];
ll ans[maxn],sum[maxn];
bitset<maxn>vis;
inline void Init(){
	idx=0;
	for(int i=0;i<=n;i++){
		head[i]=-1,ans[i]=inf,sum[i]=0;
	}
	vis.reset();
	return ;
}
inline void Add(int u,int v,int val){
	e[++idx].ne=head[u];
	head[u]=idx;
	e[idx].to=v;
	e[idx].val=val;
	return ;
}
inline void Topsort(){
	queue<int>q;
	for(int i=1;i<=n;i++){
		if(!in[i]){
			q.push(i);
		}
	}
	for(int i=1;i<=n;i++){
		if(vis[i]){
			ans[i]=0;
		}
		else{
			ans[i]=a[i];
		}
	}
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=head[u];i!=-1;i=e[i].ne){
			int v=e[i].to;
			sum[v]+=ans[u]+e[i].val;
			if(!--in[v]){
				q.push(v);
				ans[v]=min(ans[v],sum[v]);
			}
		}
	}
	return ;
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&k);
		Init();
		for(int i=1;i<=n;i++)
			scanf("%d",&a[i]);
		for(int x,i=1;i<=k;i++){
			scanf("%d",&x);
			vis[x]=1;
		}
		for(int i=1;i<=n;i++){
			int num;
			scanf("%d",&num);
			while(num--){
				int x;
				scanf("%d",&x);
				Add(x,i,0),in[i]++;
			}
		}
		Topsort();
		for(int i=1;i<=n;i++)
			printf("%lld ",ans[i]);
		printf("\n");
	}
	return 0;
}
```


---

## 作者：Dream__Sky (赞：3)

题意简述：

炼金术士娜斯佳喜欢调配药水。药水一共有 $n$ 种，其中 $i$ 种药水可以用 $c_i$ 个金币购买。

任何一种药水都只能通过一种方法获得，即从其他几种药水中混合。在混合过程中使用的药水将被消耗。此外，任何药剂都不能通过一种或多种混合过程从自身获得。

作为一名经验丰富的炼金术士，娜斯佳拥有 $k$ 种药剂 $p_1, p_2, \dots, p_k$ 的无限供应，但她不知道下一步要获得哪一种。为了做出决定，她要求你找出每种 $1 \le i \le n$，她要获得下一种 $i$ 类型的药水至少需要花费多少硬币。

分析：

首先我们可以想到，每次枚举一种药水，查询它的最小值，当它可以被混合，就往下递归，去查询被混合的那一种药水的最小值。题目里说了，任何药剂都不能通过一种或多种混合过程从自身获得。所以不会陷入死循环。但是，这样搜索显然会超时，每一种药水被查询了好多次。我们尝试记忆化搜索。

设 $f_i$ 为第 $i$ 种药水的最小值。

如果在搜索过程中，第 $i$ 种药水在之前已经被查询过最小值，那么直接就返回 $f_i$。这样保证每种药水只会被查询一次，大大缩短了时间。

代码：

```cpp
#include <bits/stdc++.h>
#define int long long//十年OI一场空，不开longlong见祖宗
using namespace std;
int T,n,m,a[200111],f[200111];
vector<int> v[200111];
inline int dfs(int dep)
{
	if(f[dep]<2e10) return f[dep];//如果被查询过，就直接返回
	f[dep]=a[dep];//购买的价格
	int sum=0;
	for(int i=0;i<v[dep].size();i++) sum+=dfs(v[dep][i]);//混合的价格
	if(!v[dep].size()) sum=2e10;//对于不能混合的药水的特判
	f[dep]=min(f[dep],sum);//求最小值
	return f[dep];
}
inline void init()
{
	for(int i=1;i<=n+100;i++) f[i]=2e10,v[i].clear(); //fi初始为极大值
}
signed main()
{
	ios::sync_with_stdio(0);
	cin>>T;
	while(T--)
	{
		cin>>n>>m;
		init();
		
		for(int i=1;i<=n;i++) cin>>a[i];
		for(int i=1,x;i<=m;i++) cin>>x,f[x]=0;//如果这种药水可以被无限供应，那么就不需要任何价值
		
		for(int i=1,x;i<=n;i++)
		{
			cin>>x;
			for(int j=1,y;j<=x;j++) cin>>y,v[i].push_back(y);//记录药水混合情况
		}
		for(int i=1;i<=n;i++) cout<<dfs(i)<<" ";//搜索
		cout<<"\n";
	 } 
	return 0;
}
 
```


---

## 作者：_sunkuangzheng_ (赞：2)

**【题目大意】**

$n$ 个物品，第 $i$ 个物品的价格为 $a_i$，其中有 $k$ 个物品是无限量且免费的。每个物品 $i$ 都可以由 $m_i$ 个物品 $a_{i1},a_{i2},\ldots,a_{im}$ 制成，且保证没有物品可以直接或间接地由他自己制成，问得到每个物品地最小花费。$1 \le k \le n \le 2 \times 10^5,1 \le a_i \le 10^9,0 \le m_i < n$。

**【题目分析】**

很容易想到图论建模，我们根据物品的制成关系建一张有向图。因为没有物品可以直接或间接制成他自己，所以相当于题目保证图无环，即图是一张有向无环图。

我们从不能由其他物品制成的物品（即 $m_i = 0$ ）开始向其他物品遍历，在统计每个物品的花费时需要计算所有能够制成它的物品的费用和，想到**拓扑排序**。我们一边拓扑一边在图上 dp，设 $f_u$ 表示制成物品 $u$ 的最小花费，则易得 $f_u = \min(a_u,\sum\limits_{v \to u}f_v)$，其中 $v \to u$ 表示点 $v$ 向点 $u$ 有边。时间复杂度 $\Theta(n+m)$。

**【代码】**

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
struct edge{int to,nxt;}e[500005];int cnt,t,x,m,u,head[500005],n,k,a[500005],g[500005],d[500005],b[500005],f[500005];
void add(int u,int v){e[++cnt].to = v,e[cnt].nxt = head[u],head[u] = cnt;}
void work(){
    cin >> n >> k;
    cnt = 0;
    queue<int> q;
    for(int i = 1;i <= n;i ++) cin >> a[i],d[i] = b[i] = g[i] = 0,f[i] = a[i],head[i] = 0;
    for(int i = 1;i <= k;i ++) cin >> x,f[x] = 0,a[x] = 0;
    for(int i = 1;i <= n;i ++){
        cin >> m,d[i] = m;if(!d[i]) q.push(i),g[i] = a[i];
        for(int j = 1;j <= m;j ++) cin >> u,add(u,i);
    }
    while(!q.empty()){
        int u = q.front();q.pop();
        f[u] = min(f[u],g[u]);
        for(int i = head[u];i;i = e[i].nxt){
            int v = e[i].to;g[v] += f[u];
            if(!(--d[v])) q.push(v);
        }
    }
    for(int i = 1;i <= n;i ++) cout << f[i] << " ";
    cout << "\n";
}
signed main(){
    cin >> t;
    while(t --) work();
    return 0;
}
```

---

## 作者：NBest (赞：1)

第一眼以为是连边跑个最短路，没想到比跑最短路还简单。

由于一种魔药可以由其他的药合成，而且没有自己到的自己的方法，显然是个 DAG，可以用拓扑序一个个搞，但是我懒得打，直接跑个记搜即可。

关注到有无限的魔药，赋值为 $0$ 即可，不能被合成的直接赋值成原价格，对于可以被合成的，我们向下搜索找价值，然后把总价格与自己的价格比较即可。
## $Code$
```cpp
int T,n,k,a[200005];
ll f[200005];
vector<int>F[200005];
ll dfs(int x){
    if(f[x]!=-1)return f[x];
    ll ans=0;
    for(int y:F[x]){
        ans+=dfs(y);
    }
    return f[x]=min(ans,1ll*a[x]);
}
int main(){
    T=read();
    while(T--){
        n=read(),k=read();
        for(int i=1;i<=n;i++){
            a[i]=read();
            f[i]=-1;
            F[i].clear();
        }
        for(int i=1;i<=k;i++){
            int p=read();
            a[p]=0;
            f[p]=0;
        }
        for(int i=1;i<=n;i++){
            int m=read();
            for(int j=1;j<=m;j++){
                int u=read();
                if(!a[i])continue;
                F[i].push_back(u);
            }
            if(!m)f[i]=a[i];
        }
        for(int i=1;i<=n;i++){
            printf("%lld ",dfs(i));
        }
        puts("");
    }
}
```

---

## 作者：CQ_Bob (赞：1)

## 分析

算法：爆搜。

对于一种药水，我们有以下情况获得：

1. 本来就有
2. 直接购买
3. 合成

对于情况 $1$，很显然这已经是最优的了，我们不需要看情况 $2,3$ 所需的价值（此时代价为 $0$）。而对于情况 $2,3$，我们可以 DFS 爆搜。对于药水 $x$，如果 $x$ 没有被搜索过，说明其最小代价是不定的，我们可以对其合成所需的药水进行搜索，得到代价 $a_1$，而该药水又能自行购买，代价为 $a_2$。所以确定代价即为 $\min(a_1,a_2)$。
## 代码

```
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define PII pair<int,int>
#define x first
#define y second
const int N=4e5+10;
int val[N];
int ne[N],e[N],h[N],idx;
void add(int a,int b){
	ne[++idx]=h[a],e[idx]=b,h[a]=idx++;
}
bool vis[N];
int dfs(int now){
	int ans=0;
	vis[now]=1;
	bool bo=0;
	for(int i=h[now];~i;i=ne[i]){
		bo=1;
		int j=e[i];
		if(vis[j]){
			ans+=val[j];
		}
		else{
			dfs(j);
			ans+=val[j];
		}
	}
	if(bo){
		return val[now]=min(val[now],ans);
	}
	else{
		return val[now];
	}
}
void solve(){
	int n,k;
	cin>>n>>k;
	idx=0;
	for(int i=1;i<=n;i++){
		cin>>val[i];
		vis[i]=0,h[i]=-1;
	}
	for(int i=1;i<=k;i++){
		int x;cin>>x;
		val[x]=0;
	}
	for(int i=1;i<=n;i++){
		int x;cin>>x;
		for(int j=1;j<=x;j++){
			int y;cin>>y;
			add(i,y);
		}
	}
	for(int i=1;i<=n;i++){
		if(!vis[i]){
			dfs(i);
		}
	}
	for(int i=1;i<=n;i++){
		cout<<val[i]<<" ";
	}
	cout<<"\n";
}
int t;
signed main(){
	cin>>t;
	while(t--){
		solve();
	}
	return 0;
}

```


---

## 作者：c1ampy (赞：1)

## 从 P1875 看本题

不得不说本题与 [P1875 佳佳的魔法药水](https://www.luogu.com.cn/problem/P1875) 有很多相似之处。本篇题解便从 P1875 引入，讲解本题。

P1875 的解法如下：
- 建立图论模型，原料药水对应结点向目标药水对应结点连有向边。
- 不设边权，而设点权，点权为获得对应药水的最小花费。
- 当原料药水 $ 1 $ 已经确定无法再被更新最小花费，并尝试更新其目标药水的最小花费时，需要保证另一原料药水 $ 2 $ 同样确定无法再被更新最小花费。
- 在此图论模型和答案更新方法的基础上，使用 Dijkstra 算法解题。

一道题目的解法与其题目条件与限制有必然联系，我们先解释 P1875 为何使用如上方法解题，再分析本题与 P1875 的异同，进而得到本题的解法。

一般使用最短路算法的题目的图论模型都带有边权，而 P1875 不同，题目中合成药水的花费是两种原料药水的花费之和，而两种原料药水的花费是可以被更新的，就不便将其作为边权。因此我们将原料药水的花费作为可更新的点权，并在其已经被确定为最小值时，才用其去更新目标药水的最小花费。

这种「不设边权而设点权」「先确定原料药水再更新目标药水」的做法同样使用于本题。

但本题与 P1875 的些许区别使得不适合使用最短路算法解题，而更适合使用拓扑排序解题，原因如下：
- 本题保证「任何药水都不能直接或间接合成自身」，这使得建出的图是 DAG。而在 DAG 上递推答案，拓扑排序明显更合适。
- 在 P1875 中，一个合成配方只有两种原料药水；而本题中，一个合成配方的药水数量不定。如果使用最短路算法，在尝试更新答案时，需要检查配方中的其他药水是否全部已经确定最小花费。这样的检查在 P1875 中是 $ \mathcal{O}(1) $ 的，但在本题中时间复杂度难以评估。
- 在 DAG 使用拓扑排序递推答案时，一个结点入队，代表其已经确定答案，并可以去更新其它结点的答案，这天然保证了一个结点在入队时，其所有前驱节点都已经确定答案，其自身的答案才可以被更新，从而省去了上一点提到的「时间复杂度难以评估的检查」。

## 代码实现

本题代码实现有以下细节应该注意：
- 对于无限制供应的药水，其花费应设为 $ 0 $。
- 无限制供应药水的花费必定是最小的，我们应将其作为拓扑排序的起点，因此其不应存在入边，建图时应注意特判。
- 图论题使用数组多，多测清空应小心。

具体代码如下：

```cpp
#include <iostream>
#include <vector>
#include <queue>

const int inf = 1 << 30;
const int max_n = 2e5 + 10;
const int max_m = 2e5 + 10;

struct Edge {
	int next;
	int to;
};

int head[max_n];
Edge edge[max_m << 1];
int edge_idx = 0;
long long cost[max_n];
bool unlimited[max_n];
std::vector <int> from[max_n];
int in_degree[max_n];
std::queue <int> q;

template <typename T> void clear(T * arr, const int n);
void add_edge(const int from, const int to);
void topo(const int n);

int main() {

	int T;
	scanf("%d", &T);

	while (T--) {
		int n, k;
		scanf("%d %d", &n, &k);
		for (int i = 1; i <= n; ++i) {
			scanf("%lld", &cost[i]);
		}

		clear(unlimited, n);
		for (int i = 1; i <= k; ++i) {
			int p;
			scanf("%d", &p);
			cost[p] = 0;
			unlimited[p] = true;
		}

		clear(head, n);
		clear(in_degree, n);
		edge_idx = 0;
		for (int to = 1; to <= n; ++to) {
			int m;
			scanf("%d", &m);

			from[to] = {};
			for (int i = 1; i <= m; ++i) {
				int	from_;
				scanf("%d", &from_);
				if (unlimited[to]) {
					continue;
				}
                
				add_edge(from_, to);
				++in_degree[to];
				from[to].emplace_back(from_);
			}
		}

		topo(n);

		for (int i = 1; i <= n; ++i) {
			printf("%d ", cost[i]);
		}
		putchar('\n');
	}

	return 0;
}

void add_edge(const int from, const int to) {
	edge[++edge_idx].to = to;
	edge[edge_idx].next = head[from];
	head[from] = edge_idx;
}

void topo(const int n) {
	q = {};
	for (int i = 1; i <= n; ++i) {
		if (in_degree[i]) {
			continue;
		}
		q.emplace(i);
	}

	while (!q.empty()) {
		int cur = q.front();
		q.pop();

		for (int i = head[cur]; i; i = edge[i].next) {
			int to = edge[i].to;
			if (--in_degree[to]) {
				continue;
			}
			long long sum = 0;
			for (const int & i : from[to]) {
				sum += cost[i];
			}
			cost[to] = std::min(cost[to], sum);
			q.emplace(to);
		}
	}
}

template <typename T> void clear(T * arr, const int n) {
	for (int i = 0; i <= n; ++i) {
		arr[i] = 0;
	}
}
```

---

## 作者：Wf_yjqd (赞：0)

思路很简单，没啥好说的啊。

考虑用合成的方式转移最小价格，会出现一个问题就是无法直接确定转移的顺序。

由于题目保证无环，可以直接拓扑排序。

在过程中记录每种药通过合成获得的最小代价。

和原价取 $\min$ 输出即可。

复杂度 $\operatorname{O}(n)$。

------------

注意特殊处理有无限瓶药的情况。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll maxn=4e5+84;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
            f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=x*10+c-'0';
        c=getchar();
    }
    return x*f;
}
inline void write(register ll x){
    if(x<0){
        putchar('-');
        x=-x;
    }
    if(x>9)
        write(x/10);
    putchar(x%10+'0');
    return ;
}
ll T,n,m,k,x,ans[maxn],anss[maxn],spc,du[maxn],head[maxn],ecnt=1;
bitset<maxn> bespc;
struct Edge{
    ll to,ne;
}e[maxn];
inline void add(ll u,ll v){
    e[ecnt]={v,head[u]};
    head[u]=ecnt++;
    return ;
}
queue<ll> q;
inline void topsort(){
    while(!q.empty())
        q.pop();
    for(ll i=1;i<=n;i++)
        if(!du[i])
            q.push(i);
    while(!q.empty()){
        ll t=q.front();
        q.pop();
        for(ll i=head[t];i;i=e[i].ne){
            // printf("%lld %lld\n",t,e[i].to);
            du[e[i].to]--;
            anss[e[i].to]+=ans[t];
            if(!du[e[i].to]){
                ans[e[i].to]=min(ans[e[i].to],anss[e[i].to]);
                q.push(e[i].to);
            }
        }
    }
    return ;
}
int main(){
    T=read();
    while(T--){
        bespc.reset();
        n=read();
        k=read();
        head[0]=0;
        ecnt=1;
        for(ll i=1;i<=n;i++){
            ans[i]=read();
            du[i]=head[i]=anss[i]=0;
        }
        for(ll i=1;i<=k;i++){
            spc=read();
            ans[spc]=0;
            bespc[spc]=1;
        }
        for(ll i=1;i<=n;i++){
            m=read();
            for(ll j=1;j<=m;j++){
                x=read();
                if(!bespc[i]){
                    add(x,i);
                    du[i]++;
                }
            }
        }
        topsort();
        for(ll i=1;i<=n;i++){
            write(ans[i]);
            putchar('Sherry');
        }
        putchar('\n');
    }
    return 0;
}
```


---

## 作者：xzyg (赞：0)

题意：

```
炼金术士纳斯蒂亚喜欢混合药剂。
商店总共有 n 种药剂，第 i 型药剂 c_i 元。
所有药剂都只能通过混合其他几种药剂获得。
混合过程中使用的药水会被消耗掉。
此外，没有药剂可以通过一个或多个混合过程从自身获得（无法自己合成自己）。

作为一名经验丰富的炼金术士，纳斯提亚 k 种无限药剂 p1，p2，…，pk，

但是她不知道她下一步应该得到哪一个。

为了决定，她要求你找出，对于每个 1≤i≤n，她需要获得 i 类药剂花费的最少硬币数。
```

对于第 $ i $ 类药剂，将它的原材料向它连一条边。

设 $ f_i $ 为第 $ i $ 类药剂所需最小价钱，容易得到：

$$ f_v = \min\{\sum_{if \ e(u,v) \ exsit} {f_u},c_i \} $$

无法自己合成自己的条件实际上保证了这个图无环。

然后拓扑排序就行了。

对于无限药剂的处理，将其商店价钱改为 $ 0 $ 即可。

丑陋的代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define MAXN 200010
#define MAXM 200010
using namespace std;
 
ll read(){
	char ch=getchar();
	ll s=0, w=1;
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){s=s*10+ch-'0';ch=getchar();}
	return s*w; 
}
 
ll n, k;
ll c[MAXN];
ll cnt[MAXN];
ll v[MAXN];
bool vis[MAXN];
 
queue <ll> q;
 
struct node{
	ll nxt, to;
}e[MAXM];
ll head[MAXN], tot = 0;
 
void add_edge(ll u, ll v){
	e[++tot].nxt = head[u];
	e[tot].to = v;
	head[u] = tot;
}
 
void init(){
	
	while(!q.empty()){
		q.pop();
	} 
	
	tot = 0;
	
	n = read(), k = read();
	
	for(ll i = 1; i <= 10000 * n; i++){
		if(i == MAXN){
			break;
		}
		e[i].nxt = 0;
		e[i].to = 0;
		head[i] = 0;
		v[i] = 0, c[i] = 0;
		vis[i] = false;
	} 
	
	for(ll i = 1; i <= n; i++){
		c[i] = read();
	}
	
	ll p;
	
	for(ll i = 1; i <= k; i++){
		p = read();
		c[p] = 0;
	}
	
	ll m, u;
	
	for(ll i = 1; i <= n; i++){
		m = read();
		if(m == 0){
			v[i] = c[i];
			vis[i] = true;
			q.push(i); 
		}else{
			for(ll j = 1; j <= m; j++){
				u = read();
				add_edge(u, i);
			}
			cnt[i] = m;
		}
	}
}
 
void work(){
	
	while(!q.empty()){
		ll u = q.front(), vv;
		q.pop();
		
		v[u] = min(v[u], c[u]);
		
		for(ll i = head[u]; i; i = e[i].nxt){
			vv = e[i].to;
			v[vv] += v[u];
			cnt[vv]--;
			if(!vis[vv] && cnt[vv] == 0){
				vis[vv] = true;
				q.push(vv); 
			}
		}
	}
}
 
int main(){
	ll T = read();
	
	while(T--){
		init();
		
		work();
		
		for(ll i = 1; i <= n; i++){
			cout << min(c[i], v[i]) << " ";
		}
		
		cout << endl;
	}
	return 0;
}
```


---

## 作者：Elairin176 (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF1851E)    
## 题意
有 $n$ 种药水，第 $i$ 种药水有一个起始价格 $a_i$。         
现在有 $k$ 种药水可以无限获得（即价格为 $0$），第 $i$ 种可以无限获得的药水为第 $p_i$ 瓶。     
还有 $n$ 种混合关系，第 $i$ 种混合关系为：第 $i$ 瓶药水可以通过混合所有 $e_{i,j}(j\in[1,m_i])$ 瓶药水获得。      
求出所有 $n$ 瓶药水最少需要花多少钱制作或买到。     
## 解法
我们把所有关系抽象成一个图，对于每次询问，我们跑一遍以它为起始结点的 dfs 即可。    
为了节省时间，我们引入记忆化搜索。    
每次 dfs 我们只需取这瓶药水的最小混合花费和原花费的最小值作为答案。    
时间复杂度为 $O(N+M),N=\sum\limits^t_{i=1}n_i,M=\sum\limits^t_{i=1}\sum\limits^{n_i}_{j=1}m_{i,j}$，可以通过。     
[CODE](https://www.luogu.com.cn/paste/uwr12nyy)

---

