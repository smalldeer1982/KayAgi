# Fewer Batteries

## 题目描述

在 2077 年机器人统治世界后，它们决定进行以下比赛。

有 $n$ 个检查点，第 $i$ 个检查点包含 $b_i$ 块电池。机器人最初从第 $1$ 个检查点出发，不带任何电池，必须到达第 $n$ 个检查点。

检查点之间共有 $m$ 条单向通道。第 $i$ 条通道允许从点 $s_i$ 移动到点 $t_i$（$s_i < t_i$），但不能反向移动。此外，只有当机器人拥有至少 $w_i$ 块充满电的电池时，才能使用第 $i$ 条通道；否则它会在途中耗尽电量。

当机器人到达点 $v$ 时，可以额外获取 $0$ 到 $b_v$（含）之间的任意数量电池。而且，它会携带之前收集的所有电池，并在每个检查点为所有已收集的电池充电。

求机器人旅程结束时能够拥有的最少电池数量，如果无法从第一个检查点到达最后一个检查点，则报告不可能。

## 说明/提示

在第一个测试用例中，需要在起点获取 $1$ 块电池，然后移动到点 $2$，再移动到点 $3$。

在第二个测试用例中，需要在起点获取 $2$ 块电池，移动到点 $2$ 再获取 $2$ 块电池，移动到点 $4$，最后移动到点 $5$。

在第三个测试用例中，没有从点 $1$ 到点 $n$ 的路径。

在第四个测试用例中，需要在起点获取 $1$ 块电池，移动到点 $2$ 再获取 $9$ 块电池，移动到点 $3$，最后移动到点 $4$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
4
3 3
2 0 0
1 2 1
2 3 1
1 3 2
5 6
2 2 5 0 1
1 2 2
1 3 1
1 4 3
3 5 5
2 4 4
4 5 3
2 0
1 1
4 4
3 10 0 0
1 2 1
1 3 3
2 3 10
3 4 5```

### 输出

```
1
4
-1
10```

# 题解

## 作者：tyr_04 (赞：9)

upd：2025-06-18 修改了一些不严谨的用语

[传送门](https://www.luogu.com.cn/problem/CF2110D)

赛时思路，提供一个和官解不一样的线性做法。

### 题意

给定一张有向图，每个点有点权 $p_i$，每个点只可能与编号更大的点有单向边（DAG），每条边有边权 $w_i$，一个机器人，初始时电量为 $0$，走到第 $i$ 个点时可以取 $0 \sim p_i$ 的任意整数作为增加的电量，通过第 $j$ 条边需满足当前电量大于等于 $w_j$，**通过后不消耗电量**，问机器走到第 $n$ 个点时的最小电量。

### 思路

首先考虑钦定一条从 $1$ 到 $n$ 的路线时，怎么判断能否到达 $n$？

不难想到如果每个点把电量都取满，能通过的边一定更多，因此分别计算从 $1$ 走到每个点时经过的点的 $p$ 的总和是否大于等于下一次走的边的边权，一旦出现小于的情况，说明该路线不可走。

如果当前路线可走，怎么求出到达 $n$ 的最小值？

试证明：如果当前路线可走，机器人走该路线到达 $n$ 的电量最小值等于当前路线经过边的边权最大值。

我们先找出了当前路线经过的边权最大且最靠前的边，考虑贪心，从第一个点开始尽量拿所有经过的点的电，如果当前电量大于等于该路线最大边权，返还多余的电量并停止拿电，由于我们判过当前路线可走，因此经过的点电量拿满那一部分边一定可走，剩下的边的边权小于等于最大边权，那么该路线所有边全部可走。

所以答案只与“该路线能否走到 $n$”和“该路线经过的边权最大值”有关。

考虑做两次 $dp$，建一张正向图和一张反向图，由于该图是 DAG 且正向图拓扑序为 $1,2 \ldots n$（反向图拓扑序为 $n,n - 1 \ldots 1$），做正向 $dp$ 时从 $1$ 到 $n$ 枚举（做反向 $dp$ 时从 $n$ 到 $1$ 枚举）即可。

先反向求出 $dp2_{i}$ 表示从 $n$ 点到 $i$ 点（反向图上）的所有路线中最大边权最小的值；再正向求出 $dp1_{i}$ 表示从 $1$ 开始可以走到 $i$ 的路线中，能拿到的电量最大值，在进行正向 $dp$ 求 $dp1_i$ 的过程中，如果第 $j$ 个位置满足 $dp1_{j} \ge dp2_{j}$，不再从 $j$ 向后转移且答案对 $dp2_{j}$ 取 $\min$（如果 $dp2_{j}$ 不是当前可行路线的边权最大值最小值，也就是说当前路线的边权最大值已经在之前经过，由于可以经过之前那条边，则一定有 $k < j$ 且 $dp1_{k} \ge dp2_{k}$，与我们一旦发现 $dp1_{j} \ge dp2_{j}$ 就不再从 $j$ 正向 $dp$ 向后转移矛盾，因此上述方法正确性有保证）。

总复杂度 $O(n + m)$。

### Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,m,dp1[200005],dp2[200005],b[200005],ans=-1;
vector<pair<int,int> > v1[200005],v2[200005];
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--)
	{
		cin>>n>>m;
		ans=1e18;
		for(int i=1;i<=n;i++)
		{
			v1[i].clear();
			v2[i].clear();
			dp1[i]=0;
			dp2[i]=1e18;
		}
		for(int i=1;i<=n;i++)
		{
			cin>>b[i];
		}
		for(int i=1;i<=m;i++)
		{
			int x,y,w;
			cin>>x>>y>>w;
			v1[x].push_back({y,w});
			v2[y].push_back({x,w});
		}
		dp1[1]=b[1];
		dp2[n]=0;
		for(int x=n;x>=1;x--)
		{
			for(int j=0;j<v2[x].size();j++)
			{
				int y=v2[x][j].first;
				dp2[y]=min(dp2[y],max(dp2[x],v2[x][j].second));
			}
		}
		for(int x=1;x<n;x++)
		{
			if(dp1[x]>=dp2[x])
			{
				ans=min(ans,dp2[x]);
				continue;
			}
			for(int j=0;j<v1[x].size();j++)
			{
				int y=v1[x][j].first;
				if(dp1[x]>=v1[x][j].second)
				{
					dp1[y]=max(dp1[y],dp1[x]+b[y]);
				}
			}
		}
		if(ans==1e18)
		{
			cout<<-1<<'\n';
			continue;
		}
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：lw393 (赞：2)

看见最小，那就是二分没跑了。

题目中有一个十分优良的性质：$s < t$。也就是说，顺序就是图的一个拓补序。

那就可以直接枚举了。

思路：在拥有电池数量上限为 $x$ 时，在电池没拿够 $x$ 的情况下，每个点的电池拿满（贪心的思想），拿满了以后就不拿了。

我们让 $f_u$ 为到达 $u$ 点所能拿到的最大电池数量上限为 $x$，初始状态下 $f_u = -\infty$（$u>1$），$f_1=0$。

若 $[u, v] \in V$，令 $w$ 为边 $[u, v]$ 的边权。若 $w \le f_u + b_u$，则更新 $f_v=\max(f_v,f_u + b_u, x)$。

最终只需判断 $f_n \ge 0$ 是否成立即可。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 2e5 + 5;
vector<pair<int, int> >G[N];
#define pb push_back

int b[N];

bool check(int x, int n){
  vector<int>minn(n + 1);
  for(int i = 1; i <= n; i++) minn[i] = -1e18;
  for(int i = 1; i <= n; i++){
    if(i == 1) minn[1] = 0;
    for(auto [v, w] : G[i]){
      if(min(minn[i] + b[i], x) >= w) minn[v] = max(minn[v], min(minn[i] + b[i], x));
    }
  }
  return minn[n] >= 0;
}

void solve(){
  int n, m;
  cin >> n >> m;
  for(int i = 1; i <= n; i++) cin >> b[i], G[i].clear();
  for(int i = 1; i <= m; i++) { int s, t, w; cin >> s >> t >> w; G[s].pb({t, w}); }
  int l = 0, r = 1e9 + 1;
  while(l < r) {
    int mid = (l + r) / 2;
    if(check(mid, n)) r = mid;
    else l = mid + 1;
  }
  cout << (l == 1e9 + 1 ? -1 : l) << '\n';
}

signed main(){
  int t = 1;
  cin >> t;
  while(t--){
    solve();
  }
  return 0;
}
```

---

## 作者：yanbinmu (赞：1)

首先，看到这种和最小值有关的题，可以先想一下二分。

然后问题就转化为了有一个最大可行的携带数，看看能不能通过这个图，到达第 $n$ 个点。

然后我们就不会了。这个携带电池不是一成不变的，所以我们生跑 bfs 是不对的。

我们考虑要达到一个什么状态，那显然是某个点到达最大的可能达到的携带电池数后再去更新其他的点。那就是拓扑排序了。

我们注意到，所有的边都是从小向大连边的，那我们直接从小向大跑就是一个拓扑序了，因为连向这个点的点都一定跑完了。

代码奉上。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

const int N = 2e5 + 5;

int n, m;
int b[N];
struct node {
    int v, w;
};
vector<node> edge[N];

int now[N], t[N];

queue<int> q;
bool check(int mid) {
    for(int i = 1;i <= n;i ++ ) now[i] = -1;
    now[1] = min(mid, b[1]);
    for(int u = 1;u <= n;u ++ ) {
        for(auto i : edge[u]) {
            int v = i.v;
            int w = i.w;
            if(now[u] >= w) {
                now[v] = max(now[v], min(mid, now[u] + b[v]));
            }
        }
    }
    return now[n] != -1;
}

void solve() {
    cin >> n >> m;
    int sum = 0;
    for(int i = 1;i <= n;i ++ ) {
        cin >> b[i];
        sum += b[i];
    }
    for(int i = 1;i <= m;i ++ ) {
        int u, v, w;
        cin >> u >> v >> w;
        edge[u].push_back({v, w});
    }

    int l = 0, r = sum;
    int ans = -1;
    while(l <= r) {
        int mid = l + r >> 1;
        if(check(mid)) {
            r = mid - 1;
            ans = mid;
        }
        else l = mid + 1;
    }
    cout << ans << "\n";

    for(int i = 1;i <= n;i ++ ) {
        edge[i].clear();
    }
}

signed main() {
    int T;
    cin >> T;
    while(T -- ) {
        solve();
    }
    return 0;
}
```

---

## 作者：YuYuanPQ (赞：1)

显然，若答案为 $ans$，则携带 $\geq ans$ 个电池一定也是可以到达终点的。\
故有单调性，可以二分。

对于 $\text{check}$，我们可以用类似 DP 的方法来做。（因为 $s_i<t_i$）\
设 $dp_i$ 表示到 $i$ 这个点能携带的最大电池数量。\
枚举 $x$（$1\leq x\leq n$），对于每条 $(x,y)$，若可以通过（即 $\min(dp_x+b_x,mxbtr)\geq limt$），则更新：$dp_y=\max(dp_y,\min(dp_x+b_x,mxbtr))$。

初始时：对于所有 $i>1$，$dp_i$ 应设为极小值（表示到不了这个点）；而 $dp_1=0$。

注意：
- 二分的 $l=0$，因为 $0\leq m$。

后话：\
赛时为啥要把 DP 想成 BFS 呢？觉得没有正确性的时候就应该停下想别的了呀。\
所以 BFS 到底行不行，求私信解答。

## Code
```cpp
#include<bits/stdc++.h>

typedef int IT;
typedef long long LL;
typedef __int128 int128;
typedef double DB;
typedef long double LDB;

#define pb push_back
#define fst first
#define sec second
#define psh push
#define mkp make_pair
#define PII pair<IT,IT>
#define PLI pair<LL,IT>
#define lowbit(x) ((x)&(-x))
using namespace std;

const int N=2e5+10,M=3e5+10,ES=M;// <<1;
const int INF=1e9;

int n,m;
int b[N];

int ecnt,head[N],nxt[ES],to[ES],lim[ES];
void add(int x,int y,int limt){
    nxt[++ecnt]=head[x];
    head[x]=ecnt;
    to[ecnt]=y;
    lim[ecnt]=limt;
    return;
}

int dp[N];
void DP_reset(){
    for(int i=1;i<=n;i++) dp[i]=-INF;
    return;
}
bool DP(int mxbtr){
    DP_reset();
    dp[1]=0;

    for(int x=1;x<=n;x++){
        for(int i=head[x];i;i=nxt[i]){
            int y=to[i],limt=lim[i];
            if(min(dp[x]+b[x],mxbtr)<limt) continue;
            dp[y]=max(dp[y],min(dp[x]+b[x],mxbtr));
        }
    }

    return dp[n]>=0;
}

int ans;

void sl_reset();
void solve(){
    sl_reset();
    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",&b[i]);

    for(int i=1;i<=m;i++){
        int s,t,w;
        scanf("%d %d %d",&s,&t,&w);
        add(s,t,w);
    }

    int l=0,r=1e9;
    while(l<=r){
        int mid=(l+r)>>1;
        if(DP(mid)) r=mid-1,ans=mid;
        else l=mid+1;
    }

    printf("%d\n",ans);
    return;
}
void sl_reset(){
    ecnt=0;
    for(int i=1;i<=n;i++) head[i]=0;

    ans=-1;
    return;
}

int main(){
    int T=1;
    scanf("%d",&T);
    while(T--){
        solve();
    }
    return 0;
}
```

[Link](https://codeforces.com/contest/2110/submission/321658473)

---

## 作者：Hhy140516 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF2110D)
# 分析
发现求最小值，所以二分。

二分时，进行 DP。

$dp_i$ 表示在点 $i$，在不超过限制的情况下，最多带的个数。

当这条路能走，若 $dp_i+b_i>w$，则 $dp_i$ 是自己和 $w$ 取最大值；否则 $dp_i$ 是自己和 $dp_i+b_i$ 取最大值。
# 代码
```cpp
//Code by hhy
#include<bits/stdc++.h>
#define F(i , a , b , c) for( int i = (a) ; ((c > 0) ? i <= (b) : i >= (b)) ; i += c )
#define T(i , root , b , c) for( int i = root ; b ; c )
#define int long long
#define W(f) while(f)
#define ull unsigned long long
#define pb push_back
#define fi first
#define se second
#define ll long long
#define debug(...){\
	cout<<"debug in function "<<__FUNCTION__<<",line "<<__LINE__<<"\n";\
	string s=#__VA_ARGS__,s2="";\
	vector<string>v;\
	for(auto i:s){\
		if(i==','){\
			v.push_back(s2);\
			s2="";\
		}else{\
			s2+=i;\
		}\
	}\
	v.push_back(s2);\
	vector<int>v2={__VA_ARGS__};\
	for(int i=0;i<v.size()-1;i++){\
		cout<<v[i]<<"="<<v2[i]<<"\n";\
	}\
	cout<<v[v.size()-1]<<"="<<v2[v2.size()-1]<<"\n\n";\
}
using namespace std ;
const int kMaxN = 2e5 + 5 , MOD = 998244353 , INF = 1e18 ;
struct Edgepr
{
	int u , w ;
};
struct Edgeve
{
	int v , w ;
};
struct node
{
  int x , y , id ;
}Node[kMaxN] ;
int n , m ;
int b[200005] ;
int dp[200005] ;
vector<Edgeve> G[200005] ;
inline ll ksm(ll a , ll b)
{
	ll mul = 1 ;
	while(b)
	{
		if(b & 1) mul *= a , mul %= MOD ;
		a *= a ;
		a %= MOD ;
		b >>= 1 ;
	}
	return mul ;
}
inline int read()
{
    int x = 0 , f = 1 ;
    char ch = getchar() ;
    while(ch < '0' || ch > '9')
    {
        if(ch == '-') f = -1 ;
        ch = getchar() ;
    }
    while(ch >= '0' && ch <= '9') x = x * 10 + ch - '0' , ch = getchar() ;
    return x * f ;
}
void write(int x)
{
    if(x < 0) putchar('-') , x = -x ;
    if(x > 9) write(x / 10) ;
    putchar(x % 10 + '0') ;
}
bool check(int mid)
{
    //初始化
    memset(dp , -0x3f , sizeof dp) ;
    dp[1] = 0 ;
    F(i , 1 , n , 1)
    {
        for( int j = 0 ; j < G[i].size() ; j++ )
        {
            int v = G[i][j].v , w = G[i][j].w ;
            if(min(dp[i] + b[i] , mid) >= w) dp[v] = max(dp[v] , min(dp[i] + b[i] , mid)) ; // 可行，转移
        }
    }
    return dp[n] >= 0 ;
}
void Read()
{
    cin >> n >> m ;
	F(i , 1 , n , 1) cin >> b[i] ;
}
void work()
{
    Read() ;
    F(i , 1 , n , 1) G[i].clear() ;
    int maxn = 0 ;
    F(i , 1 , m , 1)
    {
        int u , v , w ;
        cin >> u >> v >> w ;
        maxn = max(maxn , w) ;
        G[u].push_back({v , w}) ;
    }
    int l = 0 , r = maxn + 1 ; // 二分
    W(l < r)
    {
        int mid = l + r >> 1 ;
        if(check(mid)) r = mid ;
        else l = mid + 1 ;
    }
    cout << (l == maxn + 1 ? -1 : l) << "\n" ;
}
signed main()
{
//	freopen(".in" , "r" , stdin) ;
//	freopen(".out" , "w" , stdout) ;
	ios::sync_with_stdio(0) , cin.tie(0) , cout.tie(0) ;
    int t = 1 ;
    cin >> t ;
    while(t--) work() ;
    return 0 ;
}
```

---

## 作者：Shadow_T (赞：0)

比较好做的 $2000$ 题。当时看题目死活想不出来，突然 codeforces 跳出来：

> `Note that s_i < t_i`

然后这题就人机了。

首先考虑二分答案。对于 $\operatorname{check}$ 函数，我们可以考虑实现一个类似 $\text d \text p$ 的做法。令 $dp_i$ 为第 $i$ 个点可以拥有的最大的电池数量，然后顺序从第一个点向最后一个点递推。

假设当前可以拥有的最大的电池数量为 $x$，先将 $dp$ 数组全部设为 $-1$，$dp_1$ 为 $\min(b_1,x)$，$-1$ 就到表暂时还无法到达这个点。

每次枚举当前点 $v$ 可以通向的点 $u$，如果这条边的要求小于 $dp_v$，即第 $v$ 个点可以拥有的最大电池数，就可以更新 $dp_u$ 的最大值。但是因为我们一开始有一个最大的电池数量限制 $x$，所以每次运算后还得和 $x$ 取小值，保证不超过 $x$。

最后如果 $dp_n \neq -1$ ，就在这个 $x$ 的限制下可以成功走到 $n$ 点，否则就是不行。

```
#include <bits/stdc++.h>
using namespace std;
void Ios()
{
	ios::sync_with_stdio (0);
	cin.tie(0);
	cout.tie(0);
}
const int maxn=3e5+10;
int b[maxn],s[maxn],t[maxn],w[maxn];
#define pii pair<int,int>
#define fir first
#define sec second
vector<pii> g[maxn];
int dp[maxn],n,m;
bool check(int x)
{
//	cout<<x<<"\n";
	for(int i=1;i<=n;i++)
	dp[i]=-1;
	dp[1]=min(b[1],x);
	for(int i=1;i<=n;i++)
	for(int j=0;j<g[i].size();j++)
	{
	//	cout<<g[i][j].sec<<","<<i<<","<<g[i][j].fir<<"\n";
		if(g[i][j].sec<=dp[i])
		dp[g[i][j].fir]=max(dp[g[i][j].fir],dp[i]+b[g[i][j].fir]),
		dp[g[i][j].fir]=min(dp[g[i][j].fir],x);
	}
//	for(int i=1;i<=n;i++) cout<<dp[i]<<" ";cout<<"\n";
	return dp[n]!=-1;
}
void solve()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>b[i],g[i].clear();
	for(int i=1;i<=m;i++)
	{
		cin>>s[i]>>t[i]>>w[i];
		g[s[i]].push_back({t[i],w[i]});
	}
	int l=0,r=1e9;
	while(l<r)
	{
		int mid=(l+r)/2;
		if(check(mid)) r=mid;
		else l=mid+1;
	}
	if(!check(l)) cout<<"-1\n";
	else cout<<l<<"\n";
}
int main()
{
	Ios();
	int t;
	cin>>t;
	while(t--) solve();
 }
```

[赛时记录](https://codeforces.com/contest/2110/submission/321115967)

---

## 作者：dbywsc (赞：0)

蒟蒻第一次在场上做出 D 题！！！

所以比赛还没结束就开始写题解了 qwq

## 思路

其实看到这道题的第一眼就想到了[大陆争霸](https://www.luogu.com.cn/problem/P2446)这道题，但是后面发现两道题的做法并不相同。

我们需要在身上的电池数大于当前边权的情况下才能走这条路，并且每个节点能拿到 $b_i$ 块电池，注意我们走路是**不消耗电池**的，所以答案就应该等价于我们从 $1$ 号节点出发， 到 $n$ 号节点的路径中，**最大边权的最小值**。显然它具备很明显的二段性，所以我们可以使用二分答案来做。

由于题目保证所有的边都是从编号小的端点指向编号大的端点，所以直接遍历每一个点相当于自动做了一次拓扑排序，因此我们可以使用图上 dp 。

我们可以将所有的边权存下来（并且要排序和去重），此时答案一定在这个边权数组中，每次判断时做一次图上 dp ，设 $f_v$ 是到达节点 $v$ 时最多的电池数，那么初始状态和边界设置为：$f_1 = b_1$，其他为 $-1$。

状态转移方程为：

$f_v = \underset {u \rightarrow v, w \leq x, f_u \geq w}{\max}(f_u + b_v)$

如果 $f_n \geq 0$，说明存在一条路径上的所有边权均不超过 $x$，移动右端点，否则移动左端点。

下面提供赛时代码（写的非常的乱）：

## 代码

```cpp
#include <bits/stdc++.h>
#define x first
#define y second
#define endl '\n'
using i64 = long long;
typedef std::pair<int, int> PII;
const int N = 3e5 + 10;
std::vector<PII> G[N];
int n, m;
int w[N];
bool judge(i64 x) {
    std::vector<i64> f(n+1, -1);
    f[1] = w[1];
    for(int i = 1; i <= n; i++) {
        if(f[i] < 0) continue;
        for(auto ed : G[i]) {
            int v = ed.x;
            i64 W = ed.y;
            if(W <= x && f[i] >= W) {
                i64 t = f[i] + w[v];
                if(t > f[v]) f[v] = t;
            }
        }
    }
    return f[n] >= 0;
}
void solve(void) {
    std::cin >> n >> m;
    std::vector<i64> all;
    all.reserve(m);
    for(int i = 1; i <= n; i++) G[i].clear();
    for(int i = 1; i <= n; i++) std::cin >> w[i];
    for(int i = 1; i <= m; i++) {
        int u, v; i64 W;
        std::cin >> u >> v >> W;
        G[u].emplace_back(v, W);
        all.push_back(W);
    }
    if(m == 0) {
        std::cout << -1 << endl;
        return;
    }
    sort(all.begin(), all.end());
    all.erase(unique(all.begin(), all.end()), all.end());
    int l = 0, r = all.size() - 1, ans = -1;
    while(l <= r) {
        int mid = (l + r) / 2;
        if(judge(all[mid])) {
            ans = mid;
            r = mid - 1;
        } else l = mid + 1;
    }
    if(ans == -1) std::cout << -1 << endl;
    else          std::cout << all[ans] << endl;
}
int main(void) {
    //freopen("test.in", "r", stdin);
    int t = 1;
    std::cin >> t;
    while(t--) solve();
    return 0;
}
```

---

