# Paths on the Tree

## 题目描述

You are given a rooted tree consisting of $ n $ vertices. The vertices are numbered from $ 1 $ to $ n $ , and the root is the vertex $ 1 $ . You are also given a score array $ s_1, s_2, \ldots, s_n $ .

A multiset of $ k $ simple paths is called valid if the following two conditions are both true.

- Each path starts from $ 1 $ .
- Let $ c_i $ be the number of paths covering vertex $ i $ . For each pair of vertices $ (u,v) $ ( $ 2\le u,v\le n $ ) that have the same parent, $ |c_u-c_v|\le 1 $ holds.

 The value of the path multiset is defined as $ \sum\limits_{i=1}^n c_i s_i $ .It can be shown that it is always possible to find at least one valid multiset. Find the maximum value among all valid multisets.

## 说明/提示

In the first test case, one of optimal solutions is four paths $ 1 \to 2 \to 3 \to 5 $ , $ 1 \to 2 \to 3 \to 5 $ , $ 1 \to 4 $ , $ 1 \to 4 $ , here $ c=[4,2,2,2,2] $ . The value equals to $ 4\cdot 6+ 2\cdot 2+2\cdot 1+2\cdot 5+2\cdot 7=54 $ .

In the second test case, one of optimal solution is three paths $ 1 \to 2 \to 3 \to 5 $ , $ 1 \to 2 \to 3 \to 5 $ , $ 1 \to 4 $ , here $ c=[3,2,2,1,2] $ . The value equals to $ 3\cdot 6+ 2\cdot 6+2\cdot 1+1\cdot 4+2\cdot 10=56 $ .

## 样例 #1

### 输入

```
2
5 4
1 2 1 3
6 2 1 5 7
5 3
1 2 1 3
6 6 1 4 10```

### 输出

```
54
56```

# 题解

## 作者：GalwayGirl (赞：17)

一道不错的树上贪心。

## 题意简述
给出一棵以 1 为根 $n$ 个节点的树，第 $i$ 个节点有一个 $s_i$ 的权值，用 $k$ 条从根节点出发的路径去覆盖它，记 $c_i$ 为 $i$ 节点被覆盖的次数，要求每一对有相同父亲的节点 $u$ 和 $v$，$|c_u-c_v|\leq1$，问最大的 $ \sum\limits_{i=1}^n c_i s_i $ 为多少。

## Solution
初看题目脑子里只剩下了暴搜的算法，沉下心反复读题，一层一层揭开这道题的面纱。

因为要最大化贡献，所以这 $k$ 条路径是一定要走到叶子节点的。把重点放在 $|c_u-c_v|\leq1$ 这一要求上，运用画图的方法或者运用鸽巢原理的思想，可以发现如果要满足要求，根节点给儿子们分配的路径必须要平均分配，剩下的再依次分配。记 $son_i$ 为儿子数，那么就要给每个儿子分配 $k/son_i$ 条，剩下 $rest=k \mod son_i$ 条路径，给儿子分配的 $k/son_i$ 条要变成了一个相同的子问题，所以每个子树都可以按照类似的方法处理。现在的问题就是如何处理剩下的 $rest$ 条路径。

既然要最大化贡献且剩下的路径要不重复的分配，那就选取前 $rest$ 条从该节点到叶子节点权值和最大的链，这个可以递归求取。主体思路到此结束。

## Detail

让我们来看看这张图。

![](https://cdn.luogu.com.cn/upload/image_hosting/hk8xo5g1.png)

假设 $1$ 节点和 $2$ 节点的 $rest$ 皆为 $1$ ，设此时 $2$ 节点到叶子节点的最大链为（$2$，$4$），1节点到叶子节点的最大链为（$1$，$2$，$4$），此时 $4$ 节点会被覆盖两次，而 $5$ 节点一次都没有覆盖，打破了平衡。由于最大链可以递归求取，每个节点可以维护一个堆，存储从儿子节点传上来的最大链值，其中用完的最大值求可以弹掉，防止父亲重复使用。

见此处代码。
```cpp
long long dfs2(int now,long long k,int fa){
    ans+=k*w[now];  
    if(!son[now])return w[now];
    long long fen=k/son[now],rest=k%son[now];
    priority_queue<long long>q;
    for(int i=head[now];i;i=edge[i].next){
        int v=edge[i].to;      
        if(v==fa)continue;
        q.push(dfs2(v,fen,now));
    }
    if(rest){
        while(rest--){
            ans+=q.top();
            q.pop();
        }
    }
    return q.top()+w[now];
}
```
最后贴上完整代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+100;
int t,n,head[N],p,c,son[N];
long long w[N],ans;
struct xzh{
    int next,to;
}edge[2*N];
void add(int u,int v){
    c++;
    edge[c].next=head[u];
    edge[c].to=v;
    head[u]=c;
}
long long k;
void dfs1(int now,int fa){
    for(int i=head[now];i;i=edge[i].next){
        int v=edge[i].to;
        if(v==fa)continue;
        son[now]++;
        dfs1(v,now);   
    }
}
long long dfs2(int now,long long k,int fa){
    ans+=k*w[now];  
    if(!son[now])return w[now];
    long long fen=k/son[now],rest=k%son[now];
    priority_queue<long long>q;
    for(int i=head[now];i;i=edge[i].next){
        int v=edge[i].to;      
        if(v==fa)continue;
        q.push(dfs2(v,fen,now));
    }
    if(rest){
        while(rest--){
            ans+=q.top();
            q.pop();
        }
    }
    return q.top()+w[now];
}
int main(){
    scanf("%d",&t);
    while(t--){
        ans=0;c=0;
        for(int i=1;i<=n;i++){
            son[i]=0;
            head[i]=0;
        }
        scanf("%d%lld",&n,&k);
        for(int i=2;i<=n;i++){
            scanf("%d",&p);
            add(p,i);
            add(i,p);
        }
        for(int i=1;i<=n;i++){
            scanf("%lld",&w[i]);
        }
        dfs1(1,0);
        dfs2(1,k,0);
        printf("%lld\n",ans);
    }
    return 0;
}
```
祝大家CSP/NOIP RP++。

---

## 作者：As_Snow (赞：4)

[可能更好的食用效果](https://www.cnblogs.com/As-Snow/articles/16968736.html)
### 思路
我们从 $|c_u-c_v|\le 1$ 切入。设节点 $u$ 有 $k$ 个儿子。则根据小学就学过的鸽巢原理可以得到 $u$ 的每个儿子至少会分到 $\left\lfloor \dfrac{c_u}{k}\right\rfloor$ 条路径，最多分到 $\left\lceil\dfrac{c_u}{k}\right\rceil$。而且分到 $\left\lceil\dfrac{c_u}{k}\right\rceil$ 条路径的儿子个数 $rest=c_u\bmod k$。由于 $u$ 的父亲也可能给 $u$ 多分配一条路径，所以 $u$ 的儿子分配到的路径条数有 4 种情况：$ \left\lfloor\dfrac{c_u}{k}\right\rfloor,\left\lceil\dfrac{c_u}{k}\right\rceil,\left\lfloor\dfrac{c_u+1}{k}\right\rfloor,\left\lceil\dfrac{c_u+1}{k}\right\rceil$。其中，最小的 $\left\lfloor\dfrac{c_u}{k}\right\rfloor$ 和最大的 $\left\lceil\dfrac{c_u+1}{k}\right\rceil$ 相差不会超过 1，所以一个节点分配到的节点数只有两种情况。

然后我们来决定这 $rest$ 个多分配一条路径的机会分给那些儿子。显然哪些儿子多分配后增加的收益最大就分配给谁，用递归去求解。	

### Code

```
#include<bits/stdc++.h>
#define int long long
#define push_back emplace_back
using namespace std;
const int N = 2e5+25;
const int INF = 1e9+7;
int T;
int n,k,s[N];
vector<int>g[N];//存边
map<int,int>f[N];//记录每个节点带来的收益
int dfs(int u,int m){
	if(m==0)return 0;
	if(f[u].count(m))return f[u][m];
	if(g[u].size()==0)return f[u][m]=m*s[u];
	int t=m/g[u].size(),rest=m%g[u].size();
	int res=0;
	for(auto v:g[u])res+=dfs(v,t);
	if(rest){
		priority_queue<int>q;//将增加的收益用优先队列来维护
		for(auto v:g[u])q.emplace(dfs(v,t+1)-dfs(v,t));
		for(int i=0;i<rest;i++)res+=q.top(),q.pop();
	}
	res+=m*s[u];
	return f[u][m]=res;
}
void solve(){
	cin>>n>>k;
	for(int i=1;i<=n;i++)
		g[i].clear(),f[i].clear();
	for(int i=2,u;i<=n;i++)
		cin>>u,g[u].push_back(i);
	for(int i=1;i<=n;i++)cin>>s[i];
	cout<<dfs(1,k)<<'\n';
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--)solve();
	return 0;
}
```

---

## 作者：LYY_yyyy (赞：1)

首先每条路径肯定一路走到叶子，不走到显然不优。

对于树上问题，我们考虑怎么递归成子问题。我们发现关键点就在于父亲与儿子之间 $k$ 的继承。注意到 $c_i=\sum_{u\in son(i)}c_u$，于是 $c_u$ 一定是 $\lfloor \frac{c_i}{\sum [u\in son(i)]}\rfloor$ 然后再考虑一个加不加 1。我们可以先继承 $k=\lfloor \frac{c_i}{\sum [u\in son(i)]}\rfloor$ 给 $u$，然后我们发现给 $c_u$ 加 1 的贡献是确定的：如果 $u$ 是叶子，那就是 $s_u$；否则就是在 $u$ 决策时最大的没加 1 的路径，这个可以不断递归上传得到。于是做完了，每次决策的时候将上传的值从大到小排序取前 $p=k-\lfloor \frac{c_i}{\sum [u\in son(i)]}\rfloor \times \sum [u\in son(i)]$ 个计入答案，再将第 $p+1$ 个上传即可。

代码：
```cpp
#include<bits/stdc++.h>
#define lowbit(x) (x&(-x))
#define pb emplace_back
using namespace std;
int T;
int n,k,s[200010];
vector<int> g[200010];
long long ans=0;
int dfs(int now,int k)
{
	vector<int> d;ans+=k*1ll*s[now];
	if(!g[now].size()) return s[now];
	int sz=g[now].size();
	int op=k/sz,add=k-op*sz;
	for(auto to:g[now]) d.pb(dfs(to,op));
	sort(d.begin(),d.end());reverse(d.begin(),d.end());
	for(int i=0;i<add;i++) ans+=d[i];
	return d[add]+s[now];
}
int main()
{
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--)
	{
		int p;ans=0;
		cin>>n>>k;for(int i=1;i<=n;i++) g[i].clear();
		for(int i=2;i<=n;i++) cin>>p,g[p].pb(i);
		for(int i=1;i<=n;i++) cin>>s[i];
		dfs(1,k);cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：xianggl (赞：1)

题意：

给定一棵 $n$ 个点的树，根为 1，每个点有点权 $s_i$。

你需要找出一个路径可重集，有 $k$ 条路径，第 $i$ 条为从 $1$ 到 $u_i$ 的路径。

令 $c_i$ 为 $i$ 被这些路径覆盖的总次数。

你需要满足：对于任意 $(u, v)$，若 $(u, v)$ 是兄弟，则 $\mid c_u - c_v \mid \leq 1$。

对于一种方案，价值为 $\sum c_i \times s_i$。

求出最大价值。

题解：

切入点显然是 $\mid c_u - c_v \mid \leq 1$。

也就是说，若 $u$ 被覆盖了 $k$ 次，那么一部分儿子被覆盖了 $\lfloor k / deg_u \rfloor$ 次，另一部分有$\lceil k / deg_u \rceil$ 次。

那么我们 $dp$ 出哪些选择下取整，哪些上取整即可，这非常容易。

具体来讲，令 $dp_{u, k}$ 表示 $u$ 有 $k$ 条路径覆盖的最大权值。

先算出 $u$ 的儿子 $v$ 下取整/上取整的答案，再用 $k \bmod deg_u$ 个增益最大的上取整替代即可。

时间复杂度感性理解一下，$k$ 和 $k + 1$ 产生的状态不会太多。

代码：

```
#include <bits/stdc++.h>
#define ri register int
#define ll long long
using namespace std;
const int Maxn=2e5;
map<int,ll>dp[Maxn+5];
vector<int>adj[Maxn+5];
int s[Maxn+5];
ll dfs(int u,int k) {
	if(dp[u].find(k)!=dp[u].end())return dp[u][k];
	ll res=1ll*s[u]*k;
	if(adj[u].empty())return dp[u][k]=res;
	int son=(int)adj[u].size(),p=k/son,rem=k%son;
	vector<ll>more;
	for(ri v:adj[u]) {
		res+=dfs(v,p);
		if(rem)more.push_back(dfs(v,p+1)-dfs(v,p)); 
	}
	sort(more.begin(),more.end(),greater<ll>());
	for(ri i=0;i<rem;i++)res+=more[i];
	return dp[u][k]=res;
}
void solve() {
	int n,k;
	scanf("%d%d",&n,&k);
	for(ri i=2;i<=n;i++) {
		int x;
		scanf("%d",&x);
		adj[x].push_back(i);
	}
	for(ri i=1;i<=n;i++)scanf("%d",&s[i]);
	printf("%lld\n",dfs(1,k));
	for(ri i=1;i<=n;i++)adj[i].clear(),dp[i].clear();
}
int main() {
	int T;
	scanf("%d",&T);
	while(T--)solve();
	return 0;
}

```


---

## 作者：wmrqwq (赞：0)

这是一篇视频题解。

![](bilibili:BV1E9XWYzEUV?t=453)

[参考代码](https://codeforces.com/contest/1746/submission/311755399)

---

## 作者：1234567890sjx (赞：0)

考虑贪心。显然一个点 $u$ 所有儿子结点被访问次数的差不会超过 $1$。设 $u$ 有 $k$ 个儿子，当前有 $m$ 的访问次数可用，则每一个儿子都先给 $\lfloor\frac{m}{k}\rfloor$ 的访问次数。剩下的 $m\bmod k$ 次访问次数贪心的给增加一次可以让答案变化最大的 $m\bmod k$ 个儿子结点。使用 `unordered_map` 对答案做记忆化即可通过。

```cpp
int a[N], n, k;
map<signed, int> f[N];
vector<signed> z[N], down[N];
int dfs(int u, int m) {
    if (!m) return 0;
    if (down[u].size() == 0) return m * a[u];
    if (f[u].count(m)) return f[u][m];
    int now = 0, rm = m % down[u].size();
    for (auto &v : down[u]) now += dfs(v, m / down[u].size());
    if (!rm) return f[u][m] = now + a[u] * m;
    priority_queue<signed> q; 
    for (auto &v : down[u]) q.push(dfs(v, m / down[u].size() + 1) - dfs(v, m / down[u].size()));
    while (rm--) now += q.top(), q.pop();
    return f[u][m] = now + a[u] * m;
}
void getdown(int u, int fa) {
    for (auto &v : z[u])
        if (v != fa) getdown(v, u), down[u].eb(v);
}
void run() {
    int T = read();
    while (T--) {
        n = read(), k = read();
        for (int i = 1; i <= n; ++i) z[i].clear(), down[i].clear(), f[i].clear();
        for (int i = 2; i <= n; ++i) {
            int x = read();
            z[i].eb(x);
            z[x].eb(i);
        }
        for (int i = 1; i <= n; ++i) a[i] = read();
        getdown(1, 0);
        cout << dfs(1, k) << '\n';
    }
}
```

---

