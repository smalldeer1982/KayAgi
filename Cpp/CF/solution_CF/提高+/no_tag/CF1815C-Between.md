# Between

## 题目描述

给定整数 $n,m$ 和 $m$ 个整数数对 $(a_i,b_i)$，保证 $a_i\neq b_i;1\leq a_i,b_i\leq n$ 且数对之间两两不同。  
你需要构造一个满足下列所有要求的序列：

- 序列中的所有元素都应为 $1\sim n$ 的整数。
- 序列中恰好有一个元素为 $1$。
- 对于每个整数 $i(1\leq i\leq m)$，都满足序列中任意两个位置不同且值为 $a_i$ 的元素之间都存在至少一个值为 $b_i$ 的元素。
- 在满足上述三条要求的情况下序列长度尽可能长。

如果满足上述前三条要求的序列可以达到任意大的长度，输出 `INFINITE`；否则输出 `FINITE`，并求出满足所有要求的任意一个序列。  
每个测试点包含 $t$ 组数据。

## 样例 #1

### 输入

```
5
3 2
3 1
2 1
1 0
2 0
2 2
1 2
2 1
5 5
2 1
3 1
4 2
4 5
5 1```

### 输出

```
FINITE
5
2 3 1 2 3 
FINITE
1
1 
INFINITE
FINITE
3
2 1 2 
FINITE
10
4 2 3 5 4 1 3 2 5 4```

# 题解

## 作者：Hisaishi_Kanade (赞：4)

考虑二元组限制 $(x,y)$ 可以在 $x,y$ 之间建立怎样的关系？

由于任意两个 $x$ 之间都必须有至少一个 $y$，所以设 $p_i$ 表示 $i$ 出现的次数，则 $c_x\le c_y+1$。

这个是不是比较像差分约束那个不等式？则对于 $(u,v)$ 建立 $y\to x$，边权为 $1$，广搜一遍即可求出每个数出现次数的最大值。

然后考虑构造。 设 $t_i$ 表示出现次数可以为 $i+1$ 的数排成一列。显然不存在有 $t_i$ 没有 $t_{i-1}$ 这样的情况。

我们尝试找规律，下面是一些比较小的情况：

+ $1$；
+ $t_1, 1, t_1$；
+ $t_2,t_1,1,t_2,t_1,t_2$；
+ $t_3,t_2,t_1,1,t_3,t_2,t_1,t_3,t_2,t_3$；
+ $t_4,t_3,t_2,t_1,1,t_4,t_3,t_2,t_1,t_4,t_3,t_2,t_4,t_3,t_4$；
+ $\cdots$

找一下规律，可以发现：


+ $1$；
+ $(t_1), 1, (t_1)$；
+ $(t_2,t_1),1,(t_2,t_1),(t_2)$；
+ $(t_3,t_2,t_1),1,(t_3,t_2,t_1),(t_3,t_2),(t_3)$；
+ $(t_4,t_3,t_2,t_1),1,(t_4,t_3,t_2,t_1),(t_4,t_3,t_2),(t_4,t_3),(t_4)$；
+ $\cdots$

设 $T_i=t_iT_{i-1}$，其中 $T_1=t_1$，显然对于 $n$，其有构造 $T_11T_1T_2T_3\cdots T_n$。

```cpp
#include <bits/stdc++.h>
#define rep(i, l, r) for(i=l; i<=r; ++i)
using namespace std;
const int N=1505, inf=1e9;
vector<int> e[N], t[N];
int dis[N], q[N], c[N];
int qt, n, m, i, j, l, r, mid, u, v, tot;
inline void print(int x)
{
	for(auto pt : t[x]) printf("%d ", pt);
}
inline void prinT(int x)
{
	int i; for(i=n-1; i>=x; --i) print(i);
	return ;
}
inline void cprint(int x)
{
	tot+=t[x].size();
}
inline void cprinT(int x)
{
	int i; for(i=n-1; i>=x; --i) cprint(i);
	return ;
}
int main()
{
	scanf("%d", &qt); while(qt--)
	{
		scanf("%d %d", &n, &m); rep(i, 1, n) e[i].clear();
		rep(i, 1, m)
		{
			scanf("%d %d", &u, &v);
			e[v].emplace_back(u);
		} q[l=r=1]=1; rep(i, 1, n) c[i]=inf; c[1]=0;
		while(l<=r)
		{
			mid=q[l]; ++l;
			for(auto nxt : e[mid])
				if(c[nxt]>c[mid]+1)
				{
					c[nxt]=c[mid]+1;
					q[++r]=nxt;
				}
		}
		rep(i, 1, n) if(c[i]==inf) {puts("INFINITE"); break;} if(i<=n) continue;
		rep(i, 1, n) t[i].clear();
		rep(i, 1, n) t[c[i]].emplace_back(i);
		tot=0; cprinT(1); ++tot; rep(i, 1, n) cprinT(i);
		puts("FINITE"); printf("%d\n", tot);
		prinT(1); printf("%d ", 1);
		rep(i, 1, n) prinT(i); puts("");
	}
}
```

---

## 作者：lingying (赞：4)

感觉有点乱搞。~~不过构造题不都是乱搞吗。~~

## 建图

发现这 $m$ 个整数对 $(a_i,b_i)$ 包含关系可以转化为一条有向边 $a_i \rightarrow b_i$，其中 $a_i\ne 1$。

## 无解情况

显然，无解情况当且仅当有 $x\ne 1$ 不与 $1$ 在同一个连通块内。

## 最大长度

先考虑这个图是一个 DAG。手玩一下发现 $x$ 能出现的最多次数为其反图中与 $1$ 的最短距离。

如果图中有环呢？手玩一下还是会发现 $x$ 能出现的最多次数与其反图中与 $1$ 的最短距离相同。

考虑证明。假设有原图有一条边 $u\rightarrow v$，$c_i$ 表示 $i$ 这个点能出现的最多次数。那么必然有 $c_u\le c_v+1$，如果 $c_u$ 大于了 $c_v+1$ 必然不合法。

## 输出方案

其实想到这里已经可以用个链表乱搞了。不过为了保险一点，我们可以想一个巧妙的构造方案。

我们定义一个集合 $s_i=\{x \mathrel{|}c_x=i\}$。

方案可以为 $s_m s_{m-1}s_m s_{m-2}s_{m-1}s_ms_{m-3}s_{m-2}s_{m-1}s_m...s_1s_2s_3...s_m$。

不难证明这种构造一定是对的。

## 代码

```
#include<bits/stdc++.h>
using namespace std;

const int N=10005;

int _,n,m,idx;
int head[N],dist[N];
bool vis[N];
vector<int> vt[N];
queue<int> q;
struct edge
{
	int fr,to,ne;
}e[2*N];

void add(int x,int y)
{
	e[++idx].fr=x;
	e[idx].to=y;
	e[idx].ne=head[x];
	head[x]=idx;
}

int main()
{
	scanf("%d",&_);
	while(_--)
	{
		idx=0;
		memset(head,0,sizeof head);
		memset(vis,0,sizeof vis);
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++)vt[i].clear();
		for(int i=1;i<=m;i++)
		{
			int a,b;
			scanf("%d%d",&a,&b);
			if(a!=1)add(b,a);
		}
		dist[1]=1,q.push(1);
		while(!q.empty())
		{
			int u=q.front();
			q.pop();
			for(int i=head[u];i;i=e[i].ne)
			{
				int v=e[i].to;
				if(!vis[v])
				{
					vis[v]=1,dist[v]=dist[u]+1;
					q.push(v);
				}
			}
		}
		bool fl=1;
		for(int i=2;i<=n;i++)
			if(!vis[i])
				fl=0;
		if(!fl)
		{
			puts("INFINITE");
			continue;
		}
		puts("FINITE");
		for(int i=1;i<=n;i++)
		{
			vt[dist[i]].push_back(i);
		}
		int maxn=0,cnt=0;
		for(int i=1;i<=n;i++)
		{
			maxn=max(maxn,dist[i]);
		}
		for(int i=maxn;i>=1;i--)
			for(int j=i;j<=maxn;j++)
				cnt+=vt[j].size();
		cout<<cnt;
		putchar('\n');
		for(int i=maxn;i>=1;i--)
			for(int j=i;j<=maxn;j++)
				for(auto k:vt[j])
					cout<<k<<' ';
		putchar('\n');
	}
	return 0;
}
```



---

## 作者：Polaris_Australis_ (赞：2)

考虑 $b_i$ 向 $a_i$ 连边建出的有向图，令 $cnt_i$ 表示 $i$ 在答案序列中的出现次数，则一条边 $(u,v)$ 代表限制 $cnt_v\le cnt_u-1$，这一限制是必要条件。对于单点的限制相当于将其所有入边的限制取 $\min$，转化到图上就是以 $1$ 号节点为起点跑最短路（这里定义最短路为路径点数最小值）。这里还要注意一些边界，比如有些点跑最短路跑不到则为 `INFINITE`。接下来考虑构造答案，设 $S_i$ 表示所有最短路长度为 $i$ 的节点所代表的数字的集合，则可以按照如下方式输出：

$$
str_n,str_{n-1},str_{n},str_{n-2},str_{n-1},str_{n}\cdots
$$

直接按照上述方法输出即可。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
namespace Wilson_Inversion {
void main();
}
int main() { return Wilson_Inversion::main(), 0; }
namespace Wilson_Inversion {
const int N = 1510, M = 5010;
int n, m, ans[N * N], len, dep[N];
vector<int> e[N], vec[N];
void solve() {
	len = 0;
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) e[i].clear(), vec[i].clear(), dep[i] = 0;
	for (int i = 1; i <= m; ++i) {
		int u, v;
		cin >> u >> v;
		if (u != 1) e[v].push_back(u);
	}
	queue<int> q;
	q.push(1);
	dep[1] = 1;
	vec[1].push_back(1);
	int tot = 0;
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		++tot;
		for (int i : e[u]) {
			if (!dep[i]) {
				dep[i] = dep[u] + 1;
				vec[dep[i]].push_back(i);
				q.push(i);
			}
		}
	}
	if (tot != n) {
		cout << "INFINITE\n";
		return;
	}
	for (int i = n; i; --i) {
		for (int j = i; j <= n; ++j) {
			for (int k : vec[j]) ans[++len] = k;
		}
	}
	cout << "FINITE\n";
	cout << len << "\n";
	for (int i = 1; i <= len; ++i) cout << ans[i] << " ";
	cout << "\n";
}
void main() {
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	int T;
	cin >> T;
	while (T--) solve();
}
}
```


---

## 作者：shipeiqian (赞：1)

# CF1815C 题解

## 题意

构造一个数组使其中满足以下条件：

+ 有且只有一个 $1$；

+ 给出的 $m$ 个条件 $a_i,b_i$ 表示任意两个 $a_i$ 之间至少有一个 $b_i$。

这样的数组如果无限长，则输出 `INFINITE`；否则输出 `FINITE` 以及数组长度和这个数组。

## 思路

对于每个 $a_i,b_i$，可以发现要让每个 $b_i$ 都被 $a_i$ 包围，$num_{a_i}=num_{b_i}+1$。

可以由此建出一棵树，bfs 求出每个数的数量。在 bfs 过程中如果有某个数没被访问到，就说明这个数不受限制，则为 `INFINITE`。

要求出这个数组，可以发现，只要把数量相同的所有数分成一组，按照同样的顺序构造，把数量多的放外面，少的层层递减即可。

## Code

```cpp
#include <bits/stdc++.h>
#define de "debug"
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
int n,m,dis[50005];
vector<int>g[50005];
bool vis[50005];
void solve(){
    cin >>n >>m;
    for(int i=1;i<=n;i++)g[i].clear(),vis[i]=dis[i]=0;
    for(int i=1;i<=m;i++){
        int u,v;
        cin >>u >>v;
        g[v].push_back(u);
    }
    queue<int>q;
    q.push(1);
    vis[1]=true;
    dis[1]=1;
    int deep=1;
    while(q.size()){
        int now=q.front();
        q.pop();
        for(int i=0;i<g[now].size();i++){
            int nxt=g[now][i];
            if(!vis[nxt]){
                q.push(nxt);
                vis[nxt]=true;
                dis[nxt]=dis[now]+1;
                deep=max(deep,dis[nxt]);
            }
        }
    }
    for(int i=1;i<=n;i++){
        if(!vis[i]){
            cout <<"INFINITE\n";//
            return ;
        }
    }
    vector<pii>cnt;
    vector<int>ans;
    for(int i=1;i<=n;i++){
        cnt.push_back({dis[i],i});//存下数量
    }
    sort(cnt.begin(),cnt.end(),[](pii x,pii y){return x.first>y.first;});//按数量排序
    for(int i=deep;i>=1;i--){
        for(int j=n-1;j>=0;j--){
            if(cnt[j].first==i){//所有数量相同的
                cnt[j].first--;
                ans.push_back(cnt[j].second);
            }
        }
    }
    cout <<"FINITE\n" <<ans.size() <<"\n";
    for(int i=0;i<ans.size();i++)cout <<ans[i] <<" ";
    cout <<"\n";
}
int main(){
    int T=1;
    cin >>T;
    while(T--)solve();
    return 0;
}
```



---

## 作者：王熙文 (赞：1)

## 思路

首先看到这种二元组的问题，可以先连边。在这个问题中是 $a_i$ 向 $b_i$ 连一条有向边。

可以思考什么时候数列无限长。猜测当有数在有向图上不能走到 $1$ 时数列无限长。可以把所有在有向图上不能走到 $1$ 的数拿出来，设其为 $b_1,b_2,\cdots,b_m$，那么 $b$ 里面每个数向外连的边也一定在 $b$ 里。构造 $1,b_1,b_2,\cdots,b_m,b_1,b_2,\cdots,b_m,\cdots$ 即可。

若不是这种情况，则每个数都直接或间接被 $1$ 限制。显然与 $1$ 最短距离为 $dis$ 的数最多可以放 $dis+1$ 个。考虑按照以下的方式构造：按照与 $1$ 的最短距离（设其为 $dis$）从小到大插入序列。最初有一个数 $1$。之后将 $dis=1$ 的数插入到 $1$ 的两边。接下来将 $dis=2$ 的数插入到每一个 $dis=1$ 的数前面和整个序列的最后。以此类推，$dis=x$ 的数插入到每一个 $dis=x-1$ 的数前面和整个序列的最后。这样构造对于 $dis=x$ 的数插入了 $x+1$ 遍，因此一定是最优的。

注意，对于 $dis=x$ 的数每次插入的顺序应当是一样的，否则会出问题，原因见下文。

为什么这样的构造满足要求呢？

* 对于 $dis$ 较大的数连向 $dis$ 较小的数，一定有前者的 $dis$ 为后者的 $dis+1$，那么在插入的过程中就能保证 $dis$ 较大的数相邻两个之间都有且仅有一个 $dis$ 较小的数。
* 对于 $dis$ 相同的数有连接，因为每次插入的顺序是一样的，所以也可以保证。
* 对于 $dis$ 较小的数连向 $dis$ 较大的数，可以发现每次插入 $dis$ 较大的数时一定有数在任意一对 $dis$ 较小的数中间，因此也能保证。可以手摸一下样例以保证完全理解。

不必用程序模拟这样的过程。手摸后可以发现，设 $c_x$ 为 $dis=x$ 的数组成的数列，$d_x$ 为 $c_n,c_{n-1},\cdots,c_x$，则最终的数列为：$d_1,1,d_1,d_2,\cdots,d_n$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
vector<int> e1[1510];
queue<int> q;
int dis[1510];
vector<int> e2[1510];
int tot,ans[2000010];
int main()
{
	int t; cin>>t; while(t--)
	{
		cin>>n>>m;
		for(int i=1; i<=n; ++i) e1[i].clear();
		for(int i=1; i<=m; ++i)
		{
			int u,v; cin>>u>>v;
			e1[v].push_back(u);
		}
		memset(dis,0x3f,sizeof(dis));
		dis[1]=0,q.push(1);
		while(!q.empty())
		{
			int frn=q.front(); q.pop();
			for(int v:e1[frn])
			{
				if(dis[v]>=1e9) dis[v]=dis[frn]+1,q.push(v);
			}
		}
		bool flag=0;
		for(int i=1; i<=n; ++i) flag|=(dis[i]>=1e9);
		if(flag) { cout<<"INFINITE\n"; continue; }
		cout<<"FINITE\n";
		for(int i=1; i<=n; ++i) e2[i].clear();
		for(int i=1; i<=n; ++i) e2[dis[i]].push_back(i);
		tot=0;
		for(int i=n; i>=1; --i) for(int j:e2[i]) ans[++tot]=j;
		ans[++tot]=1;
		for(int i=1; i<=n; ++i)
		{
			for(int j=n; j>=i; --j)
			{
				for(int k:e2[j]) ans[++tot]=k;
			}
		}
		cout<<tot<<'\n';
		for(int i=1; i<=tot; ++i) cout<<ans[i]<<' '; cout<<'\n';
	}
	return 0;
}
```

---

## 作者：Nuisdete (赞：1)

对于二元组 $(a, b)$，我们称 $b$ 限制了 $a$，因为每两个 $a$ 之间都得有一个 $b$，可以用 $b \to a$ 来表示这个关系，最终就可以建成一张图（注意是否出现环是不影响的）。

考虑一下 `INFINITE` 的条件，显然是在有数字不受 $1$ 的限制的情况下可以无限制的放，也就是说，它在图上不被 $1$ 可达。

稍微玩玩样例就能发现，这个序列是有一个层级的，而这个层级就是 `bfs` 序（同一层级可以有多个数），相邻两个层级是穿插的关系，比如我们用编号 $1$ ~ $n$ 来表示每一层级，那么必有如下的关系：

```
1 2 1

3 2 3 2 3

4 3 4 3 4 3 4

5 4 5 4 5 4 5 4 5
```

然后我们就可以构造这个序列了，可以建出一个 `DAG` 用于表示各个层级（注意一个层级 $i$ 在序列上会出现 $i$ 次）在答案序列上的先后关系，然后拓扑排序输出答案。

注意一些数组的大小和清空等等。

Code：[https://codeforc.es/problemset/submission/1816/202026101](https://codeforc.es/problemset/submission/1816/202026101) .

---

## 作者：MarSer020 (赞：0)

你说的对但是一场 CF 两个 ad-hoc。

感觉这道题没有 CF1815B 难啊。

$\Large\text{Solution}$

考虑一条限制的影响。设 $c_i$ 表示序列中 $i$ 的出现次数。

观察样例发现如果两个 $x$ 之间至少有一个 $y$。则最优解形如 $x\cdots y\cdots x\cdots y\cdots x\cdots$，此时有 $c_x\le c_y+1$。

又 $c_1=1$，建边 dfs 可以 $O(nm)$ 跑出对于每个 $i$ 的最大 $c_i$。具体复杂度我也不会证，总之常数极小。

接下来考虑构造方案：考虑我们可以将出现次数一样的数放在一起构造，不妨设将出现次数为 $i$ 的数放在一起组成的字符串为 $s_i$，则有一组构造方案如下：

$$s_ns_{n-1}\cdots s_1s_{n}s_{n-1}\cdots s_2\cdots s_ns_{n-1}s_n$$

容易发现这组构造是满足条件的。

总时间复杂度 $O(\sum(nm+k))$，其中 $k$ 为答案长度。

$\Large\text{Code}$

代码没什么细节，这点也被 CF1815B 薄纱了。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int inf=0x3f3f3f3f;
int n,v[1505],m,T;
pair<int,int>b[1505];
bool f;
vector<int>e[1505],ans;
void dfs(int cur){
	for(int x:e[cur])
		if(!v[x]||v[x]>v[cur]+1)
			v[x]=v[cur]+1,dfs(x);
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0),cin>>T;
	while(T--){
		cin>>n>>m,ans.clear();
		for(int i=1;i<=n;i++)
			v[i]=0,e[i].clear();
		for(int i=1,x,y;i<=m;i++)
			cin>>x>>y,e[y].emplace_back(x);
		v[1]=f=1,dfs(1);
		for(int i=1;i<=n;i++)
			if(!v[i]){
				f=0;
				break;
			}
		if(!f){
			cout<<"INFINITE\n";
			continue;
		}
		cout<<"FINITE\n";
		for(int i=1;i<=n;i++)
			b[i]={v[i],i};
		sort(b+1,b+n+1,greater<>());
		for(int i=1,j=n;i<=n;i++){
			for(int k=1;k<=j;k++)
				ans.emplace_back(b[k].second);
			while(j&&b[j].first==i)
				j--;
			if(!j)
				break;
		}
		cout<<ans.size()<<'\n';
		for(int x:ans)
			cout<<x<<' ';
		cout<<'\n';
	}
	return 0;
}
```

---

