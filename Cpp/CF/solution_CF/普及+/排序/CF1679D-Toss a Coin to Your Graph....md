# Toss a Coin to Your Graph...

## 题目描述

One day Masha was walking in the park and found a graph under a tree... Surprised? Did you think that this problem would have some logical and reasoned story? No way! So, the problem...

Masha has an oriented graph which $ i $ -th vertex contains some positive integer $ a_i $ . Initially Masha can put a coin at some vertex. In one operation she can move a coin placed in some vertex $ u $ to any other vertex $ v $ such that there is an oriented edge $ u \to v $ in the graph. Each time when the coin is placed in some vertex $ i $ , Masha write down an integer $ a_i $ in her notebook (in particular, when Masha initially puts a coin at some vertex, she writes an integer written at this vertex in her notebook). Masha wants to make exactly $ k - 1 $ operations in such way that the maximum number written in her notebook is as small as possible.

## 说明/提示

Graph described in the first and the second examples is illustrated below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1679D/f21a10b2a32ca5315b6d3233f4e3f1d967d3f865.png)In the first example Masha can initially put a coin at vertex $ 1 $ . After that she can perform three operations: $ 1 \to 3 $ , $ 3 \to 4 $ and $ 4 \to 5 $ . Integers $ 1, 2, 3 $ and $ 4 $ will be written in the notepad.

In the second example Masha can initially put a coin at vertex $ 2 $ . After that she can perform $ 99 $ operations: $ 2 \to 5 $ , $ 5 \to 6 $ , $ 6 \to 2 $ , $ 2 \to 5 $ , and so on. Integers $ 10, 4, 5, 10, 4, 5, \ldots, 10, 4, 5, 10 $ will be written in the notepad.

In the third example Masha won't be able to perform $ 4 $ operations.

## 样例 #1

### 输入

```
6 7 4
1 10 2 3 4 5
1 2
1 3
3 4
4 5
5 6
6 2
2 5```

### 输出

```
4```

## 样例 #2

### 输入

```
6 7 100
1 10 2 3 4 5
1 2
1 3
3 4
4 5
5 6
6 2
2 5```

### 输出

```
10```

## 样例 #3

### 输入

```
2 1 5
1 1
1 2```

### 输出

```
-1```

## 样例 #4

### 输入

```
1 0 1
1000000000```

### 输出

```
1000000000```

# 题解

## 作者：Hovery (赞：12)

# Problem

[Toss a Coin to Your Graph...](https://www.luogu.com.cn/problem/CF1679D)

# Sol

题目说最大的值最小，考虑二分。

对于一个点，若它的权值大于二分值，那显然是不能走的，所以我们只能走权值小于等于二分值的那些节点。

我们先枚举每条边，若该边左右两个端点的权值都小于等于二分值，就把这条边连上。

那建完图之后，下一步就是判断合不合法。

如果这张图有环，那答案显然成立。

若没有环，那我们就要求出这张图的最长路判断它是不是大于等于 $k$。

找环，求有向无环图的最长路，这两个可以用拓扑排序同时做。

找最长路比较简单，至于找环，就判断那些入队过的点的个数是不是小于整张图的点的个数就行了。

# Code

```cpp
#include<bits/stdc++.h>
#define int long long
#define pb push_back
using namespace std;

int du[200010], dis[200010], vis[200010], a[200010], x[200010], y[200010];
int n, m, k;
vector<int> G[200010];

bool check(int need)
{
    for (int i = 1;i <= n;i++)
    {
        G[i].clear();
        du[i] = 0;
        dis[i] = 0;
        vis[i] = 0;
    }
    for (int i = 1;i <= n;i++)
    if (a[i] <= need)
    dis[i] = 1;
    for (int i = 1;i <= m;i++)
    {
        if (a[x[i]] <= need && a[y[i]] <= need)
        {
            du[y[i]]++;
            G[x[i]].pb(y[i]);
            vis[x[i]] = vis[y[i]] = 1;
        }
    }//把这张图建出来。
    int cnt = 0, sum = 0;
    queue<int> q;
    for (int i = 1;i <= n;i++)
    if (!du[i] && vis[i])
    {
        dis[i] = 1;
        q.push(i);
        sum++;
    }
    else sum += vis[i];
    while (!q.empty())
    {
        int x = q.front();
        q.pop();
        ++cnt;//求入队的个数。
        for (auto i : G[x])
        {
            du[i]--;
            dis[i] = max(dis[i], dis[x] + 1);//求最长路。
            if (!du[i])
            q.push(i);
        }
    }
    if (cnt != sum)
    {
        return 1;
    }
    sum = 0;
    for (int i = 1;i <= n;i++)
    {
        sum = max(sum, dis[i]);
    }
    return sum >= k;
}

signed main()
{
    cin >> n >> m >> k;
    for (int i = 1;i <= n;i++)
    cin >> a[i];
    for (int i = 1;i <= m;i++)
    {
        cin >> x[i] >> y[i];
    }
    int l = 1, r = (int)1e9 + 10;
    while (l <= r)
    {
        int mid = l + r >> 1;
        if (check(mid))
        {
            r = mid - 1;
        }
        else l = mid + 1;
    }
    if (r == 1e9 + 10)
    cout << -1;
    else
    cout << r + 1;
}
```

---

## 作者：Komorebi_03 (赞：6)

## 思路：

点的最大权值最小，很容易想到二分答案。

建图过程第一篇题解我觉得写的很清楚了，这里不再赘述。

若图中有环，那么答案显然成立，因为可以在环上绕圈，比如样例二。

若没有环，则需要判断图中的最长路是否大于等于 $k$。

注意开 long long。

```cpp
// Problem: CF1679D Toss a Coin to Your Graph...
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1679D
// Memory Limit: 250 MB
// Time Limit: 3000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//By:Komorebi_03
#include<bits/stdc++.h>
using namespace std;
// #define clear(a) memset(a,0,sizeof a)
#define int long long
const int N = 1e6+5;
int n,m,k,cnt,sum,Max,a[N],u[N],v[N],du[N],dis[N],vis[N];
vector<int> g[N];
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}

void init()
{
	cnt=0;
	sum=0;
	Max=-1;
	for (int i=1;i<=n;i++)
	{
		g[i].clear();
		du[i]=0;
		dis[i]=0;
		vis[i]=0;
	}
}

bool check(int x)
{
	init();
	for (int i=1;i<=n;i++)
		if(a[i]<=x)
			dis[i]=1;
	for (int i=1;i<=m;i++)
	{
		if(a[u[i]]<=x && a[v[i]]<=x)
		{
			du[v[i]]++;
			g[u[i]].push_back(v[i]);
			vis[u[i]]=vis[v[i]]=1;
		}
	}
	queue<int> q;
	for (int i=1;i<=n;i++)
	{
		if(!du[i] && vis[i])
		{
			dis[i]=1;
			q.push(i);
			sum++;
		}
		else
			sum+=vis[i];
	}
	while (!q.empty())
	{
		int u=q.front();
		q.pop();
		++cnt;
		for (int i=0;i<g[u].size();i++)
		{
			int v=g[u][i];
			du[v]--;
			dis[v]=max(dis[v],dis[u]+1);
			if(!du[v])
				q.push(v);
		}
	}
	if(cnt!=sum)
		return true;
	for (int i=1;i<=n;i++)
		Max=max(Max,dis[i]);
	return Max>=k;
}

signed main()
{
	n=read();
	m=read();
	k=read();
	for (int i=1;i<=n;i++)
		a[i]=read();
	for (int i=1;i<=m;i++)
	{
		u[i]=read();
		v[i]=read();
	}
	int l=1;
	int r=1e9;
	while (l<=r)
	{
		int mid=(l+r)>>1;
		if(check(mid))
			r=mid-1;
		else
			l=mid+1;
	}
	if(r==1e9)
		cout<<-1;
	else
		cout<<r+1;
	return 0;
	//Amireux_35
}
```


---

## 作者：bsTiat (赞：6)

## 题意简述

珂朵莉给了你一个有向图，边数最大 $ 2×10^5 $ ，每个点有一个点权，任选起点，走k步，问经过的点的最大权值最小能是多少？$ k \leq 10^{18} $，无解输出-1，没有重边和自环，但是会有环。

## 题目分析

看到要求最大值最小，考虑二分答案。

若一个数可以是答案，那么比其大的数必然也可以是答案。

发现判定复杂度可以做到 $ O(n+m) $ ，总复杂度 $ O((n+m)\log Max) $ ，珂以做。

## 算法

每次将点权小于等于 $ mid $ 的点建一个图出来，然后一遍dfs判环，有环直接有解，没环再做一遍拓扑排序求DAG的最长路，若最长路长度大于等于k，说明有解，否则无解。

## code

```cpp
#include<bits/stdc++.h>
# define int long long
using namespace std;
const int N = 1e6;
inline int rd(){
	char c=getchar();int sum=0,f=1;
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c<='9'&&c>='0'){sum=(sum<<3)+(sum<<1)+(c^48);c=getchar();}
	return sum*f;
}
int n,m,k,ans,a[N];
vector<int>v[N];
int head[N],to[N],nxt[N],tot,vis[N],in[N],f[N],b[N];
inline void add(int x,int y){
	to[++tot]=y;nxt[tot]=head[x];head[x]=tot;
}
bool dfs(int x){
	vis[x]=1;b[x]=1;
	for(int i=head[x];i;i=nxt[i]){
		if(vis[to[i]])return 1;
		else if(b[to[i]]==0&&dfs(to[i]))return 1;
	}
	vis[x]=0;
	return 0;
}
bool check(int t){
	tot=0;int sum=0;
	for(int i=1;i<=n;++i)
		head[i]=0,vis[i]=0,in[i]=0,f[i]=1,b[i]=0;
	for(int i=1;i<=n;++i){
		if(a[i]>t)continue;
		++sum;
		for(auto p:v[i])
			if(a[p]<=t)add(i,p);
	}
	for(int i=1;i<=n;++i)
		if(!b[i])if(dfs(i))return 1;
	if(k>sum)return 0;
	for(int i=1;i<=n;++i)
		for(int j=head[i];j;j=nxt[j])++in[to[j]];
	queue<int>q; 
	while(!q.empty())q.pop();
	for(int i=1;i<=n;++i)
		if(in[i]==0)q.push(i);
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=head[u];i;i=nxt[i]){
			f[to[i]]=max(f[to[i]],f[u]+1);
			if(f[to[i]]>=k)return 1;
			--in[to[i]];if(!in[to[i]])q.push(to[i]);
		}
	}
	return 0;
} 
signed main(){
	int x,y;
	int l=1,r=1e9;
	n=rd();m=rd();k=rd();
	for(int i=1;i<=n;++i)a[i]=rd();
	if(m==0){
		if(k>1){
			cout<<-1;
			return 0;
		}
		ans=1e9;
		for(int i=1;i<=n;++i)
			ans=min(ans,a[i]);
		cout<<ans;
		return 0;
	}
	for(int i=1;i<=m;++i){
		x=rd();y=rd();
		v[x].push_back(y); 
	}
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid))ans=mid,r=mid-1;
		else l=mid+1;
	}
	cout<<(ans==0?-1:ans);
	return 0;
}

```


---

## 作者：starrylasky (赞：5)

[博客食用更佳](https://www.cnblogs.com/hhhsky001/articles/16271194.html)

# solution：二分&记忆化搜索

容易想到随着答案的增大这张图能走的边就会更多，这是个单调增。

所以考虑二分。

对于 $check$ 函数，先将可以走的边建成图，在对于图上每个点跑记忆化搜索，这样可以保证 $check$ 时线性的，定义 $f_i$ 为走到 $i$ 时还能走多少个点。

显然他的儿子能到达的最远距离加上到他这的距离大于等于k时就成立。

当第一遍搜时，就已经达到k，显然也是可行的。

对于环，我们考虑将搜到的点打标记，回溯的时候撤回标记，在搜的过程中如果搜到打了标记的，那就形成环。

总复杂度： $O(n~log~n)$ 。

# code

```cpp
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("inline")
#include<bits/stdc++.h>
#define re register
#define int long long
#define fep(i,l,r) for(re int i=l;i<=r;++i)
#define For(i,u) for(re int i=head[u];i;i=e[i].nxt)
#define feb(i,r,l) for(re int i=r;i>=l;--i)
using namespace std;
 
const int N = 2e6+5;
int n,m,k,head[N],tot,b[N],a[N],ans=-1,u[N],v[N],f[N]; bool vis[N];
struct Edge
{
	int v,nxt;
}e[N];

inline int read() { int s=0,w=1; char ch=getchar(); while(!(ch<='9'&&ch>='0')) {if(ch=='-') w=-1; ch=getchar();} while(ch<='9'&&ch>='0') {s=(s<<1)+(s<<3)+ch-'0'; ch=getchar();} return s*w; }
inline void write(int x) { if(x>=10) write(x/10); putchar(x%10+'0'); }
inline void print(int x) { if(x<0) putchar('-'),x=~(x-1); write(x); }

inline bool cmp(int d1,int d2) 
{
	return d1<d2; 
} 

inline void add(int u,int v)
{
	e[++tot]=(Edge){v,head[u]}; head[u]=tot;
}

inline bool dfs(int u,int p)
{
	if(p==k) return true;
	vis[u]=true;
	For(i,u)
	{
		if(vis[e[i].v]) return true;//形成了环 
		if(f[e[i].v])//已经深搜过了 
		{
			if(p+f[e[i].v]+1>=k) return true;//如果他的儿子能到达的最远距离+到他这的距离 >= k
		}
		else
		{
			bool flag=dfs(e[i].v,p+1);
			if(flag) return true;//成功了就返回 
		}
		f[u]=max(f[u],f[e[i].v]+1);//更新他能到达的最远距离 
	}
	vis[u]=false; return false;
}

inline bool check(int res)
{
	fep(i,1,n) head[i]=0,vis[i]=false,f[i]=0;
	while(tot) e[tot--]={0,0};
	fep(i,1,m)
	{
		if(res>=a[u[i]]&&res>=a[v[i]]) add(u[i],v[i]);
	}
	fep(i,1,n) if(a[i]<=res) if(dfs(i,1)) return true;
	return false;
}

signed main()
{
	n=read(),m=read(),k=read();
	fep(i,1,n) b[i]=a[i]=read();
	fep(i,1,m) u[i]=read(),v[i]=read();
	sort(b+1,b+1+n,cmp);
	int l=1,r=n;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(check(b[mid])) ans=b[mid],r=mid-1;
		else l=mid+1;
	}
	print(ans);
	return 0;
}
```

---

## 作者：Anguei (赞：3)

## 题意

给定一个 $n$ 个点 $m$ 条边有向图，每个顶点具有点权 $a_i$。保证不含自环（loops）和重边（multi-edges）。

你需要在这张图上找到一个长度为 $k$ （输入指定）的路径，使得路径上所有点权的最大值尽可能小。试求出这个最小值。

若找不到长度为 $k$ 的路径，输出 -1。

$n \leq 2\times 10^5$，$k\leq 10^{18}$。

## 分析

$k$ 的范围这么大，一定不是简单的 `dfs and similar` 题目。

**最大值最小**，想到二分答案。于是需要思考：这道题哪里会有单调性？

不难发现：如果把所有点权超过某个阈值的点都从图上删除，那么图上剩余点的数量和阈值之间就构成了单调关系。阈值越小，被删除的点就会越多，剩余的点就会越少。同时，点的数量与图上最长链的长度也是正相关的——点的数量越多，最长链的长度可能就越长。因此：**二分点权阈值**是此题的关键。

在一定的阈值下，若可以找到长度 $\geq k$ 的一条链，那么阈值可以尝试减小。否则必须增大阈值，以尽量增加最长链长度。

需要注意：如果有环，那么相当于存在一条长度无穷的链……

判环可以使用 dfs 或拓扑排序。求最长链简单 dp 一下就好。

注：其实没有必要真的删除超过阈值的点，在判环、dp 的时候写点特判，跳过不符合要求的点就可以。每次 check 的时候重新建图也可以，常数略大，时限 3s，可以过。

## 代码

```cpp
void solution() {
  int n, m;
  ll k;
  std::cin >> n >> m >> k;
  std::vector<int> a(n + 1);
  for (int i = 1; i <= n; ++i) read(a[i]);
  std::vector<std::vector<int>> g(n + 1);
  for (int i = 1; i <= m; ++i) {
    int u, v;
    read(u, v);
    g[u].push_back(v);
  }

  auto hasCycle = [&](const std::vector<std::vector<int>>& g2) {
    std::vector<int> ind(n + 1, 0);
    for (int i = 1; i <= n; ++i)
      for (auto v : g2[i]) ++ind[v];
    std::queue<int> q;
    for (int i = 1; i <= n; ++i)
      if (!ind[i]) q.push(i);
    int cnt = 0;
    while (!q.empty()) {
      ++cnt;
      int u = q.front();
      q.pop();
      for (auto v : g2[u]) {
        --ind[v];
        if (!ind[v]) q.push(v);
      }
    }
    return cnt < n;
  };

  auto check = [&](int x) {
    decltype(g) g2(n + 1);
    for (int i = 1; i <= n; ++i) {
      if (a[i] > x) continue;
      for (auto j : g[i]) {
        if (a[j] > x) continue;
        g2[i].push_back(j);
      }
    }
    if (hasCycle(g2)) return true;

    std::vector<int> dp(n + 1, -1);
    auto dfs = [&](auto self, int u) {
      if (~dp[u]) return dp[u];
      dp[u] = 1;
      for (auto v : g2[u]) dp[u] = std::max(dp[u], self(self, v) + 1);
      return dp[u];
    };
    for (int i = 1; i <= n; ++i)
      if (dp[i] == -1) dfs(dfs, i);
    for (int i = 1; i <= n; ++i)
      if (dp[i] >= k) return true;
    return false;
  };


  int l = *std::min_element(a.begin() + 1, a.end());
  int r = *std::max_element(a.begin() + 1, a.end());
  int mid = (l + r) / 2;
  while (l < r) {
    if (check(mid))
      r = mid;
    else
      l = mid + 1;
    mid = (l + r) / 2;
  }
  return print(check(mid) ? mid : -1);
}
```



---

## 作者：sgl654321 (赞：2)

### 题目大意
给定一有向图，点有点权。从任意点出发，任意的走上 $k$ 步，定义一条路径的代价为其经过的最大点权。最小化这个 $k$ 步路径的代价。

### 解题思路
最大值最小类问题，考虑二分答案加验证。

通过二分答案，我们就知道哪些点是可以经过的，哪些点是不可以经过的。对那些可以经过的点进行连边，建出导出子图。

对于该导出子图，如果其中存在一个环，即不是一个 DAG 的情况，显然我们可以走上无限步，是合法的。

如果是一个 DAG，那就要判断该 DAG 上的最长路径是否长度大于等于 $k$。

如何求最长路径长度呢？考虑拓扑排序 dp。用 $f_i$ 表示到 $i$ 这个点结束，可能的最长路径长度。

设有一条 $u\rightarrow v$ 的边，那么显然有转移 $f_v = \max(f_v,f_u+1)$。边界情况：对于入度为 $0$ 的点 $u$，有 $f_u = 1$。

我们只需要判断导出子图中是否有一个点 $x$ 满足 $f_x \ge k$ 即可。

### 参考代码
注意每次验证时的清空。

```cpp
#include<bits/stdc++.h>
#define maxn 200010
#define maxm 200010
using namespace std;
typedef long long ll;
struct edge{
	ll x, y; 
} e[maxm];
ll n, m, k, a[maxn], x, l, r, mid, ans;
ll kk, poi[maxn], v[maxm], nex[maxm], in[maxn];
ll dis[maxn];
bool vis[maxn], can[maxn];

queue<ll> q;
void add_edge(ll x, ll y){
	kk++; v[kk] = y; nex[kk] = poi[x]; poi[x] = kk; in[y] ++;
}
bool check(ll tar){
//	cout << tar << endl;
	for(int i = 1; i <= n; i++) 
		poi[i] = dis[i] = in[i] = 0, vis[i] = can[i] = 0;	
	for(int i = 1; i <= n; i++)
		if(a[i] <= tar) can[i] = 1;
	for(int i = 1; i <= kk; i++) v[i] = nex[i] = 0;
	kk = 0;
	
	for(int i = 1; i <= m; i++)
		if(a[e[i].x] <= tar && a[e[i].y] <= tar)
			add_edge(e[i].x, e[i].y), can[e[i].x] = can[e[i].y] = 1;
	for(int i = 1; i <= n; i++)	
		if(!in[i] && can[i]) q.push(i), dis[i] = 1, vis[i] = 1;
	while(!q.empty()){
		x = q.front(); q.pop();  
		ll save = poi[x];
		while(save){
			in[v[save]]--;
			dis[v[save]] = max(dis[v[save]], dis[x] + 1);
			if(in[v[save]] == 0) vis[v[save]] = 1, q.push(v[save]);
			save = nex[save];
		}
	}
	for(int i = 1; i <= n; i++)
		if(can[i] && (vis[i] == 0 || dis[i] >= k)){
		//	cout << i << ' ' << vis[i] << endl;
			return 1;
		} 
	return 0;
}

int main(){
	cin >> n >> m >> k;
	for(int i = 1; i <= n; i++) cin >> a[i];
	for(int i = 1; i <= m; i++) cin >> e[i].x >> e[i].y;
	l = 1; r = 1e10; ans = -1;
	while(l <= r){
		mid = (l + r) >> 1;
		if(check(mid)) ans = mid, r = mid - 1;
		else l = mid + 1;
	}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：Foreverxxx (赞：2)

### 题意

一张有向图，每个点有点权，求图中的一条长度为 $k$ 的路径，求所有符合条件的路径中，每一条路径经过的点的最大值的最小值。

也就是说，假设有 $n$ 条符合条件的路径，每条路径经过的点的权值的最大值构成了集合 $\{x_1,x_2,\dots,x_n\}$，我们需要求的就是 $\min\{x_1,x_2,\dots,x_n\}$。

### 思路

那么我们看到了“最大权值最小”这一提示，那么脑子里就直接想到了二分。

那么我们直接进行二分点权的操作，对于点权 $a_i \le mid$ 点进行建图。

现在问题就变成了：在一个新图中，是否存在长度 $len \ge k$ 的路径（此处长度指经过点的数量）？

那么新图中有链和环两种情况，分别进行考虑，这里需要注意一个细节，如果有环，那么这张图一定有长度大于等于 $k$ 的路径存在的，大不了绕几圈环。

链的情况很好解决，直接一次拓扑排序求最长路就行了。

对于环的情况也好解决。

一种方法是对原图进行 ``dfs`` 找环，这里不再赘述。

第二种是拓扑排序。我们知道，在操作开始前，我们是将入度为 $0$ 的点压入队列进行操作，但很显然，如果有环的话，这个环不会进行任何操作。所以如果拓扑排序结束后仍然有点的入度不为 $0$，即这个点在图中但是没有被遍历，那么说明图中存在环。

Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int sss=0,www=1;
	char chh=getchar();
	while(chh<'0'||chh>'9'){
		if(chh=='-') www=-1;
		chh=getchar();
	}
	while(chh>='0'&&chh<='9'){
		sss=sss*10+chh-'0';
		chh=getchar();
	}
	return sss*www;
}
int n,m,k;
int a[200005];
int edge[200005][2];
int head[200005],to[200005],nxt[200005],tot=1;
int in[200005],dist[200005];
void add(int u,int v){
	to[++tot]=v;
	nxt[tot]=head[u];
	head[u]=tot;
}
void top_sort(int mid){
	queue<int> q;
	for(register int i=1;i<=n;i++){
		if(!in[i]&&a[i]<=mid){
			dist[i]=1;
			q.push(i);
		}
	}
	while(!q.empty()){
		int x=q.front(); q.pop();
		for(register int i=head[x];i;i=nxt[i]){
			int u=to[i]; in[u]--;
			if(dist[u]<dist[x]+1){
				dist[u]=dist[x]+1;
			}
			if(!in[u]) q.push(u);
		}
	}
}
bool check(int mid){
	memset(head,-1,sizeof head); tot=1;
	memset(in,0,sizeof in);
	memset(dist,0,sizeof dist);
	for(register int i=1;i<=m;i++){
		if(a[edge[i][0]]<=mid&&a[edge[i][1]]<=mid){
			add(edge[i][0],edge[i][1]);
			in[edge[i][1]]++;
		}
	}
	top_sort(mid);
	for(register int i=1;i<=n;i++){
		if(dist[i]>=k||in[i]) return true;
	}
	return false;
}
signed main(){
	n=read(),m=read(),k=read();
	for(register int i=1;i<=n;i++){
		a[i]=read();	
	}
	for(register int i=1;i<=m;i++){
		edge[i][0]=read();
		edge[i][1]=read();
	}
	int l=0,r=1e9,mid,ans=-1;
	while(l<=r){
		mid=(l+r)>>1;
		if(check(mid)){
			ans=mid;
			r=mid-1;
		}
		else l=mid+1;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：JS_TZ_ZHR (赞：2)

## 题意：

给定一个图，图上每个点都有点权。请你找到一个长为 $k-1$ 的路径，使得其中点权最大的点权值最小。点和边可以重复经过。

## 题解：

看到最大最小直接考虑二分答案。

在计算答案是否能小于等于 $x$ 时，保留所有权值小于等于 $x$ 的点做一次拓扑排序。如果有环的话那么显然存在长为 $k-1$ 的路径。否则做一次 dp 求最长路径即可。

```cpp
#include<bits/stdc++.h>
#define N 1000005
#define int long long
using namespace std;
int n,m,k,l,r,ans=-1,in[N],f[N],u[N],v[N],a[N];
vector<int>ve[N];
bool check(int x){
    for(int i=1;i<=m;i++){
        if(a[u[i]]<=x&&a[v[i]]<=x)ve[u[i]].push_back(v[i]),in[v[i]]++;
    }
    queue<int>q;
    for(int i=1;i<=n;i++){
        if(!in[i]&&a[i]<=x)q.push(i),f[i]=1;
    }
    while(!q.empty()){
        int now=q.front();
        q.pop();
        for(int i=0;i<ve[now].size();i++){
            int y=ve[now][i];
            in[y]--;
            f[y]=max(f[y],f[now]+1);
            if(!in[y])q.push(y);
        }
    }
    for(int i=1;i<=n;i++)if(in[i])return 1;
    for(int i=1;i<=n;i++)if(f[i]>=k)return 1;
    
    return 0;
}
signed main(){
    cin>>n>>m>>k;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=1;i<=m;i++){
        cin>>u[i]>>v[i];
    }
    l=1,r=1e9;
    while(r>=l){
        int mid=(l+r)>>1;
        if(check(mid))ans=mid,r=mid-1;
        else l=mid+1;
        for(int i=1;i<=n;i++)in[i]=f[i]=0,ve[i].clear();
    }
    cout<<ans<<endl;
    //system("pause");
}
```


---

## 作者：registerGen (赞：2)

## Solution

题目要求的是最大值的最小值，考虑二分答案。

二分答案 $x$，然后我们将问题转化为：仅保留满足 $a_i\le x$ 的点，能否走 $k$ 步。

那么如果图中有环，在这个环里打转转就行了。

如果图中没有环（即这个图是 DAG），那么只需最长路径 $\ge k$ 即可，显然可以 DAGdp。

## Code

```cpp
const int N=2e5;

struct Edge{int to,nxt;}e[N+10];int head[N+10],tote;
void addEdge(int u,int v){e[++tote]={v,head[u]};head[u]=tote;}

int n,m,a[N+10];
ll k;
std::pair<int,int> E[N+10];
int ind[N+10],f[N+10];

bool check(int x){
  memset(head,0,sizeof(head));tote=0;
  memset(ind,0,sizeof(ind));
  memset(f,0,sizeof(f));
  for(int i=1;i<=m;i++)
    if(a[E[i].first]<=x&&a[E[i].second]<=x)
      addEdge(E[i].first,E[i].second),ind[E[i].second]++;
  std::queue<int> q;
  for(int i=1;i<=n;i++)
    if(!ind[i]&&a[i]<=x)q.push(i),f[i]=1;
  while(!q.empty()){
    int u=q.front();q.pop();
    for(int i=head[u];i;i=e[i].nxt){
      int v=e[i].to;
      f[v]=std::max(f[v],f[u]+1);
      if(--ind[v]==0)q.push(v);
    }
  }
  for(int i=1;i<=n;i++)
    if(ind[i]||f[i]>=k)return 1;
  return 0;
}

void mian(){
  scanf("%d%d%lld",&n,&m,&k);
  for(int i=1;i<=n;i++)
    scanf("%d",a+i);
  for(int i=1;i<=m;i++)
    scanf("%d%d",&E[i].first,&E[i].second);
  int l=1,r=1000000001,mid,ans=-1;
  while(l<r){
    mid=(l+r)>>1;
    if(check(mid))ans=mid,r=mid;
    else l=mid+1;
  }
  printf("%d\n",ans);
}
```

---

## 作者：I_am_Accepted (赞：2)

### Analysis

最大值最小？二分答案。

设当前二分答案到 $A$。

我们只保留有向图中点权 $\le A$ 构成的诱导子图。

接下来就是求此图的最长路（或者有环的话报告无穷），若最长路点数 $\ge k$ 则可行，否则不行。

这里我们用线性复杂度的记忆化搜索解决。

设 $f_i$ 表示从 $i$ 出发最多能经过几个点，$g_i$ 表示当前是（$1$）否（$0$）在 DFS 的栈中。

当前遍历到 $x$ 节点，遍历到 $x\to y$ 这条边。

若 $g_y$，则 $f_x=\infty$。

否则 DFS $y$ 节点，然后 $f_x=1+\max\limits_{x\to y}f_y$。

总时间 $O((n+m)\log n)$

（不过我 code 写的复杂度 $\log$ 值域的，无伤大雅）

### Code

```cpp
//Said no more counting dollars. We'll be counting stars.
#pragma GCC optimize("Ofast")
//#pragma GCC optimize("unroll-loops")//DONT use rashly,I have suffered
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")//DONT use rashly,I have suffered
#include<bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define fir first
#define sec second
#define mkp make_pair
#define pb emplace_back
#define mem(x,y) memset(x,y,sizeof(x))
#define For(i,j,k) for(int i=j;i<=k;i++)
#define Rof(i,j,k) for(int i=j;i>=k;i--)
#define Fe(x,y) for(int x=head[y];x;x=e[x].nxt)
#define ckmx(a,b) a=max(a,b)
#define ckmn(a,b) a=min(a,b)
#define fin(s) freopen(s,"r",stdin)
#define fout(s) freopen(s,"w",stdout)
#define file(s) fin(s".in");fout(s".out")
#define cerr cerr<<'_'
#define debug cerr<<"Passed line #"<<__LINE__<<endl
template<typename T>T ov(T x){cerr<<"Value: "<<x<<endl;return x;}
#define ll long long
const ll mod=1000000007;
inline ll pw(ll x,ll y){ll r=1;while(y){if(y&1)r=r*x%mod;x=x*x%mod;y>>=1;}return r;}
inline void mad(ll &a,ll b){a=(a+b)%mod;while(a<0)a+=mod;}
inline void mmu(ll &a,ll b){a=a*b%mod;while(a<0)a+=mod;}
#define inv(a) pw(a,mod-2)
#define int long long
#define N 200010
const int inf=2e18;
int n,a[N],f[N],m,k,tar;
vector<int> e[N];
void dfs(int x){
	f[x]=-1;
	int res=0;
	for(int i:e[x]){
		if(a[i]>tar) continue;
		if(f[i]==-1){
			f[x]=inf;
			return ;
		}
		if(!f[i]) dfs(i);
		ckmx(res,f[i]);
	}	
	f[x]=res+1;
}
bool check(){
	For(i,1,n) f[i]=0;
	int res=0;
	For(i,1,n) if(a[i]<=tar && !f[i]) dfs(i);
	For(i,1,n) ckmx(res,f[i]);
	return res>=k;
}
signed main(){IOS;
	cin>>n>>m>>k;
	For(i,1,n) cin>>a[i];
	int x,y;
	For(i,1,m){
		cin>>x>>y;
		e[x].pb(y);
	}
	int l=1,r=1e9,res=-1;
	while(l<=r){
		tar=(l+r)>>1;
		if(check()){
			res=tar;
			r=tar-1;
		}else{
			l=tar+1;
		}
	}
	cout<<res<<endl;
return 0;}
```

---

## 作者：ZZZZZZZF (赞：2)

# 思路

题目要求最大值最小，考虑二分答案。

每次二分，我们可以通过预处理来降低验证的复杂度。我们二分路径上的最大权重，记为 $mw$。那么只需验证是否存在 $len\le k$ 的路径。这里的路径可以是简单路径，也可以是环。

```cpp
//二分答案
l = 1,r = 1000000000;
ans = -1;
while(l<=r){
    int mid = (l+r)/2;
    if(check(mid)){
        ans = mid;
        r = mid-1;
    }
    else
        l = mid+1;
}
```

### 构建新图
为了方便处理，我们根据 $mw$ 构建一个新图，这个图只包含点权小于等于 $mw$ 的顶点。这样我们就不用考虑权值问题了，只需判断新图上是否存在一条 $len \le mw$ 的路径即可。

```
  //入度数量，拓扑排序用
  ind[N] = {0};
  //邻接表存图
  vector<int> G[N];
  for(int u = 1;u<=n;u++){
      if(w[u]<=maxW){
          for(int i = head[u];i;i = e[i].next){
              int v=e[i].v;
              if(w[v]<=maxW){
                  G[u].emplace_back(v);
                  ind[v]++;
              }
          }
      }
  }
```


### 找环 and 最长路
在新图上，我们可以跑一遍拓扑排序找环，然后根据拓扑排序的结果能快速找出最长路。
```cpp
//dis储存最长路
int dis[N];
vector<int> tp;//tp储存拓扑序，之后用来找最长路
queue<int> q;
for(int i = 1;i<=n;i++){
    if(!ind[i])q.emplace(i);//将起点入队，可能有多个起点
    dis[i] = 0;
}

//拓扑排序
while(!q.empty()){
    int u = q.front();q.pop();
    tp.emplace_back(u);
    for(int v :G[u])
        if(!--ind[v])
            q.emplace(v);
}

//找环，如果删到最后还有入度就存在环
for(int i = 1;i<=n;i++) if(ind[i]!=0)return 1;

```
关于找最长路，只需从依赖关系靠前的点开始更新即可。因为拓扑序已经确定，一个循环就能搞定。

```cpp
for(int u:tp)
    for(int v:G[u])
        dis[v] = max(dis[u]+1,dis[v]);
```

# Code

```cpp
#include<bits/stdc++.h>
#define M 200005
#define N 200005
using namespace std;

int m,n,tt,ans;
long long k;
int head[N],w[N],ind[N];

//链式前向星存图
struct edge{
    int next,v;
}e[M];

void add(int u,int v){
    e[++tt].v = v;
    e[tt].next = head[u];
    head[u] = tt;
    return;
}

bool check(int maxW){
    //建新图
    int ind[N];
    memset(ind,0,sizeof(ind));
    vector<int> G[N];
    for(int u = 1;u<=n;u++){
        if(w[u]<=maxW){
            for(int i = head[u];i;i = e[i].next){
                int v=e[i].v;
                if(w[v]<=maxW){
                    G[u].emplace_back(v);
                    ind[v]++;
                }
            }
        }
    }
    
    //初始化距离和拓扑排序起点
    int dis[N];
    vector<int> tp;//拓扑序
    queue<int> q;
    for(int i = 1;i<=n;i++){
        if(!ind[i])q.emplace(i);
        dis[i] = 0;
    }
    
    //拓扑排序
    while(!q.empty()){
        int u = q.front();q.pop();
        tp.emplace_back(u);
        for(int v :G[u])
            if(!--ind[v])
                q.emplace(v);
    }

    //找环
    for(int i = 1;i<=n;i++) if(ind[i]!=0)return 1;

    //DAG上dp找最长路
    for(int u:tp)
        for(int v:G[u])
            dis[v] = max(dis[u]+1,dis[v]);

    for(int i = 1;i<=n;i++)
        if(dis[i]>=k&&w[i]<=maxW)return 1;
    return 0;
}

int main(){

    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>m>>k;

    //因为是移动k-1次，这里wa了一次
    k--;
    for(int i = 1;i<=n;i++)
        cin>>w[i];
    for(int i = 1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        add(u,v);
    }
    
    //二分答案
    int l = 1,r = 1000000000;
    ans = -1;
    while(l<=r){
        int mid = (l+r)/2;
        if(check(mid)){
            ans = mid;
            r = mid-1;
        }
        else
            l = mid+1;
    }

    cout<<ans<<endl;

    return 0;
}
```

---

## 作者：allqpsi (赞：2)

### 直接上思路：二分

这道题是最大值最小，显然我们可以用二分做。

直接二分最大权值最小能是多少，然后在此最大权值最小上建图，把那些可以跑的边给放进新图中。然后再在此图上做拓扑排序，把最大可以走多远动态规划出来。

注意！我们再跑拓扑排序的同时要判环，如果有环的话就可以走无限步了。

#### 代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,k,in[200005],di[200005],ai[200005],x[200005],y[200005],l=1,r=1e9,cnt,sum;
vector<int>vi[200005];
bool vis[200005];
queue<int>qi;
bool check(int xx){
	while(!qi.empty()){
		qi.pop();
	}
	for(int i=1;i<=n;i++){
		while(!vi[i].empty()){
			vi[i].pop_back();
		}
		in[i]=0;
		di[i]=0;
		vis[i]=false;
	}
	for(int i=1;i<=n;i++){
		if(ai[i]<=xx){
			di[i]=1;
		}
	}
	for(int i=1;i<=m;i++){
		if(ai[x[i]]<=xx&&ai[y[i]]<=xx){
			in[y[i]]++;
			vi[x[i]].push_back(y[i]);
			vis[x[i]]=vis[y[i]]=true;
		}
	}
	cnt=0;
	sum=0;
	for(int i=1;i<=n;i++){
		if(in[i]==0&&vis[i]){
			di[i]=1;
			qi.push(i);
			sum++;
		}
		else{
			sum+=vis[i];
		}
	}
	while(!qi.empty()){
		int x=qi.front();
		qi.pop();
		cnt++;
		for(int i=0;i<vi[x].size();i++){
			int v=vi[x][i];
			in[v]--;
			di[v]=max(di[v],di[x]+1);
			if(!in[v]){
				qi.push(v);
			}
		}
	}
	if(cnt!=sum){
		return true;
	}
	sum=0;
	for(int i=1;i<=n;i++){
		sum=max(sum,di[i]);
	}
	return sum>=k;
}
signed main(){
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++){
		cin>>ai[i];
	}
	for(int i=1;i<=m;i++){
		cin>>x[i]>>y[i];
	}
	while(l<=r){
		int mid=(l+r)/2;
		if(check(mid)){
			r=mid-1;
		}
		else{
			l=mid+1;
		}
	}
	if(r==1e9){
		cout<<-1;
	}
	else{
		cout<<r+1;
	}
}
```


---

## 作者：vectorxyz (赞：1)

## 题意
> 珂朵莉给了你一个有向图，边数最大 $2 \times 10^5$，每个点有一个点权，任选起点，走 $k$ 步，问经过的点的最大权值最小能是多少？，无解输出 $-1$，没有重边和自环，但是会有环。
## 题解
我们对照图分析他的性质。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1679D/f21a10b2a32ca5315b6d3233f4e3f1d967d3f865.png)

假定我们现在走过的路的点权一定是小于一个值的，我们叫他新图。那么如果我们走到了一个环里，那肯定是合法的。因为我们只需要不断的绕圈子走完这 $k$ 步即可。

那么没有环呢？我们跑一遍最长路，如果新图中最长的路径是小于 $k$ 的，说明我们如果要走完这 $k$ 步，肯定要走一部分老图，但老图点权都是不合法的，所以不可取。反之成立。

对于最长路和判环，我们可以拓扑加 $\tt{DAGDP}$ 解决。

然后回到我们最初的问题，如何确定那个最小的点权呢？注意到题目中是最大值最小，那么显然二分了。


## code
[submission](https://codeforces.com/contest/1679/submission/303331857)。

```cpp
#include <bits/stdc++.h>
#define int long long
namespace std
{
    template<typename T>
    T read(T x)
    {
        T opt = 1,sum = 0;
        char ch = getchar();
        while(!isdigit(ch)) opt = (ch == '-') ? -1 : 1, ch = getchar();
        while( isdigit(ch)) sum = (sum << 1) + (sum << 3) + (ch ^ 48), ch = getchar();
        return opt * sum;
    }
}
#define read std::read(0ll)
using namespace std;
const int N = 2e5 + 5;
int x[N], y[N];
int a[N];
vector<int> g[N];
int n, m, K, in[N];
int dis[N];
vector<int> topo;
bool vis[N];
int mp[N];
bool check(int k){
    for(int i = 1;i <= n;i ++ ) dis[i] = in[i] = mp[i] = 0, g[i].clear();
    for(int i =  1;i <= m;i ++ ){
        if(a[y[i]] <= k && a[x[i]] <= k){
            g[x[i]].push_back(y[i]);
            in[y[i]] ++ ;
            // cout << x[i] << ' ' << y[i] << endl;
            mp[x[i]] ++ , mp[y[i]]++;
        }
    }
    queue<int> q;
    for(int i = 1;i <= n;i ++ ) if(!in[i]) q.push(i);
    int _ = 0;
    for(int i = 1;i <= n;i ++ ) if(mp[i]) _ ++ ;
    if(!_) return 0;
    while(q.size()){
        int u = q.front(); q.pop();
        for(int i = 0;i < g[u].size();i ++ ) {
            int v = g[u][i];
            dis[v] = max(dis[v], dis[u] + 1);
            if(!--in[v]) q.push(v);
        }
    }
    int res = INT_MIN;
    for(int i = 1;i <= n;i ++ ){
        if(in[i]) return 1;
        else res = max(res, dis[i]);
    }
    return res >= K;
}
void work()
{
    n = read, m = read, K = read;
    K --;
    int minn = LONG_LONG_MAX, maxn = INT_MIN, l, r;
    for(int i = 1;i <= n;i ++ ) a[i] = read, minn = min(minn, a[i]), maxn = max(maxn, a[i]);
    for(int i = 1;i <= m;i ++ ){
        x[i] = read, y[i] = read;
    }
    int ans = -1;
    // cout << l << ' ' << r << endl;
    // cout << check(4) << endl;
    l = minn, r = maxn;
    while(l <= r){
        int mid = (l + r) / 2;
        if(check(mid)){
            ans = mid;
            r = mid - 1;
        }
        else l = mid + 1;
    }
    if(!K && !m) cout << minn << endl;
    else if(ans > maxn) cout << maxn << endl;
    else cout << ans << endl;
}

signed main(){int T = 1;while(T -- ) work();}
```

---

## 作者：intel_core (赞：1)

这个题边权的取值最多有 $m$ 个，$\text{DP}$ 和一众纯图论算法已经废了；又注意到答案满足显然的单调性，因此考虑二分答案。

现在考虑如何 $\text{check}$ 一个答案 $x$ ，取出权值 $\ge x$ 的点，现在考虑怎么在这些点的支撑子图上走 $k$ 步。

* 如果图上有环，随便你走多少步都可以。

* 如果图上没有环，可以在 $\text{DAG}$ 上 $\text{DP}$ 求最长链，如果最长链长度 $\ge k$ 就可以，否则就不行。

总复杂度 $O(m \log V)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int NR=2e5+10;
#define int long long
#define pb push_back
vector<int>g[NR];
int n,m,k,a[NR],cnt[NR],dis[NR];
#define pii pair<int,int>
#define fi first
#define se second
#define mkp make_pair
pii t[NR];

bool check(int x){
	memset(cnt,0,sizeof(cnt));
	memset(dis,0,sizeof(dis));
	bool flag=0;
	int lcy=0;
	for(int i=1;i<=n;i++)g[i].clear();
	for(int i=1;i<=m;i++)
		if(a[t[i].fi]<=x&&a[t[i].se]<=x)
			g[t[i].se].pb(t[i].fi),cnt[t[i].fi]++,flag=1;
	queue<int>q;
	for(int i=1;i<=n;i++)lcy+=a[i]<=x;
	for(int i=1;i<=n;i++)
		if(a[i]<=x&&!cnt[i])q.push(i),dis[i]=1,lcy--;
	if(flag&&q.empty())return 1;
	while(!q.empty()){
		int x=q.front();q.pop();
		for(int y:g[x]){
			cnt[y]--;dis[y]=max(dis[y],dis[x]+1);
			if(!cnt[y])q.push(y),lcy--;
		}
	}
	if(lcy)return 1;
	for(int i=1;i<=n;i++)
		if(dis[i]>=k)return 1;
	return 0;
}

signed main(){
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
	for(int i=1;i<=m;i++)scanf("%lld%lld",&t[i].fi,&t[i].se);
	int l=1,r=2e9,res=2e9;
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid))res=mid,r=mid-1;
		else l=mid+1;
	}
	if(res>1e9)puts("-1");
	else cout<<res<<endl;
	return 0;
} 
```

---

## 作者：_zuoqingyuan (赞：0)

很典的套路题。

# 思路分析

看到最大值最小，果断选择二分答案。

我们二分**路径上经过点的最大值**，也就是说，我们不能选择走到超过这个值的点，假设这个值为 $mid$，对于所有 $a_i>mid$ 的点，我们把这个点从原图中删去，我们就可以得到一张新图，只需要判断是否存在长度不小于 $k-1$ 的路径。

因为路径不要求是简单路径，综合 $k$ 的数据范围（$k\le 10^{18}$），我们可以知道，如果新图中存在一个环，我们从这个环上任意一个点出发，无限的绕着这个环走，也属于一种合法方案。所以当新图中存在一个环时，则必然有一条长度不小于 $k-1$ 的路径。

那图中没有环时，超过 $k-1$ 的路径就不存在吗？对于 $k$ 较小的情况下，如果新图（没有环）的最长路长度不小于 $k-1$，则合法路径也是存在的。因为新的有向图没有环，所以可以用拓扑排序在 DAG 上 DP，$O(m)$ 的时间复杂度内即可求解。

因为拓扑排序同时具有判定环的功能，我们顺便把第一种情况处理一下。总时间复杂度为 $O(m\log V)$，$V$ 为 $a_i$ 的取值上限。

# Code：


```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;
const int N=2e5+10,M=2e5+10;
int n,m,minv=1e9+10,maxv,a[N],ans,u[M],v[M],ind[N],dp[N],mk[N];
long long k;
queue<int>q;
vector<int>G[N];
bool check(int t){
	long long res=0,num=0;
	for(int i=1;i<=m;i++){
		if(a[u[i]]<=t&&a[v[i]]<=t){
			G[u[i]].push_back(v[i]);
			ind[v[i]]++;mk[u[i]]=1,mk[v[i]]=1;
		}
	}
	for(int i=1;i<=n;i++){
		if(!ind[i])q.push(i),dp[i]=0;
	}
	for(int i=1;i<=n;i++)if(mk[i])num++;//特判
	if(!num)return 0;
	while(q.size()){
		int x=q.front();q.pop();
		for(auto y:G[x]){
			dp[y]=max(dp[y],dp[x]+1);
			if((--ind[y])==0)q.push(y);
		}
	}
	for(int i=1;i<=n;i++){
		if(ind[i])return 1;
		else res=max(res,(long long)dp[i]);
	}
	if(res>=k-1)return 1;
	else return 0;
}
void clear(){
	for(int i=1;i<=n;i++)G[i].clear(),dp[i]=0,ind[i]=0,mk[i];
}
int main(){
	scanf("%d %d %lld",&n,&m,&k);
	for(int i=1;i<=n;i++){
		scanf("%d",a+i);
		minv=min(minv,a[i]);
		maxv=max(maxv,a[i]);
	}
	for(int i=1;i<=m;i++)scanf("%d %d",u+i,v+i);
	int l=1,r=1e9,mid;ans=r;
	while(l<r){
		
		mid=(l+r)>>1;
		if(check(mid))r=ans=mid;
		else l=mid+1;
		clear();
	}
	if(!m&&k==1)printf("%d\n",minv);//特判
	else if(l>maxv)printf("-1\n");
	else printf("%d",ans);
	return 0;
}
```
~~DAG 上 dp 10min 写完，二分答案调了 0.5h。越来越唐乐~~。

如有错误，请指出。

---

## 作者：JOKER_chu (赞：0)

肝疼.jpg

## 题意

就一句话，麻烦您读下题。

## 解法

观察到题目确定的最大权值越小越好，使用二分答案，在检查答案是否可行时将一条满足 $1 \leq i,j \leq n$ 的 $i \rightarrow j$ 的边，如果给出的 $a_i$ 与 $a_j$ 都 $\leq$ 二分出的答案，将其加入图中，随后在图中求最长路即可。

但是观察到题目给出的 $k \leq 10^{18}$，又会发现，只要我们建出的图中有环，那么就能无限走这个环，无论 $k$ 多大，都是可行的。

## 代码

```cpp
#include <iostream>

#include <vector>

#define endl '\n'

#define int long long

using namespace std;

const int N = 2e5 + 5;

int n, m, k, l, r = 1e9 + 6, h, a[N], x[N], y[N], dp[N], v[N];

vector<int>cnt[N], topo;

void s(int x){
  if(v[x] != 0){
    if(v[x] == 1){
      h = 1;
    }
    return ;
  }
  v[x] = 1;
  for(int to : cnt[x]) s(to);
  v[x] = -1;
  topo.push_back(x);
}

bool function1(int xx){
  bool ret = 0;
  topo.clear();
  h = 0;
  for(int i = 1; i <= n; ++i) v[i] = dp[i] = 0, cnt[i].clear();
  for(int i = 1; i <= m; ++i){
    if(a[x[i]] <= xx && a[y[i]] <= xx){
      cnt[y[i]].push_back(x[i]);
    }
  }  
  for(int i = 1; i <= n; ++i){
    if(a[i] <= xx) s(i);
  }
  if(h == 1) return 1;
  if(topo.empty()) return 0;
  for(int i : topo){
    dp[i] = 1;
    for(int j : cnt[i]){
      dp[i] = max(dp[i], dp[j] + 1);
    }
  }
  for(int i = 1; i <= n; ++i){
    ret |= dp[i] >= k && a[i] <= xx;
  }
  return ret;
}

signed main(){
  cin >> n >> m >> k;
  for(int i = 1; i <= n; cin >> a[i], ++i);
  for(int i = 1; i <= m; cin >> x[i] >> y[i], ++i);
  while(l < r){
    int mid = (l + r) >> 1;
    if(function1(mid) == 1){
    	r = mid;
	  }else{
		 l = mid + 1;
	  }
  }
  cout << (l == 1e9 + 6 ? -1 : l);
  return 0;
}


```

---

