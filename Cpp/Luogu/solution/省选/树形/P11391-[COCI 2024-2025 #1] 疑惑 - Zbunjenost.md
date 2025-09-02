# [COCI 2024/2025 #1] 疑惑 / Zbunjenost

## 题目背景

译自 [COCI 2024/2025 #1](https://hsin.hr/coci/) T5。$\texttt{5s,0.5G}$。满分为 $120$。

## 题目描述

给定一个 $n$ 个顶点的凸包和它的三角剖分。

可以认为点按照顺时针顺序标号 $1\sim n$，也就是说，$\forall 1\le i\le n$，点 $i$ 和点 $(i\bmod n+1)$ 间有边相连。

定义一条长度为 $m$（$m\ge 3$）的**简单回路** $a_0,a_1,\cdots,a_{m-1}$ 为满足以下条件的序列：

- $\forall i\in [0,m)$，$1\le a_i\le n$；
- $\forall 0\le i\lt j\lt m$，$a_i\neq a_j$；
- $\forall i\in [0,m)$，顶点 $a_i,a_{(i+1)\bmod m}$ 间有边相连。


定义两条回路**本质相同**，当且仅当一条回路可以通过翻转（reverse）或者循环移位或者翻转+循环移位得到另一条回路。

求出凸包内本质不同的回路条数，对 $(10^9+7)$ 取模。

## 说明/提示


#### 样例解释

- 样例 $1$ 解释：$[1,2,3]$，$[1,4,3]$，$[1,2,3,4]$ 是合法的回路。
- 样例 $2$ 解释：$[1, 2, 3]$，$[1, 3, 5]$，$[3, 4, 5]$，$[1, 2, 3, 5]$，$[1, 3, 4, 5]$，$[1, 2, 3, 4, 5]$ 是合法的回路。
- 样例 $3$ 解释：$[1, 2, 6]$，$[2, 3, 4]$，$[4, 5, 6]$，$[2, 4, 6]$，$[1, 2, 4, 6]$，$[2, 3, 4, 6]$，$[2, 4, 5, 6]$，$[1, 2, 3, 4, 6]$，$[2, 3, 4, 5, 6]$，$[1, 2, 4, 5, 6]$，$[1, 2, 3, 4, 5, 6]$ 是合法的回路。

#### 子任务

对于 $100\%$ 的数据，保证：

- $1\le n\le 2\times 10^5$；  
- 给定的是合法三角剖分。


| 子任务编号 | $n\le$ |  特殊性质 | 得分 |  
| :--: | :--: | :--: |:--: | 
| $ 1 $    | $15$ |  |   $ 13 $   |  
| $ 2 $    | $300$ |   |  $ 18 $   |  
| $ 3 $    | $2\times 10^3$ |   |  $ 34 $   |  
| $ 4 $    | $2\times 10^5$ | A  |  $ 15 $   |  
| $ 5 $    | $2\times 10^5$ |  |  $ 40 $   |  

- 特殊性质 A：$\forall 3\le i\le n-1$，点 $1$ 与点 $i$ 间有边相连。




## 样例 #1

### 输入

```
4 
1 3```

### 输出

```
3```

## 样例 #2

### 输入

```
5
1 3
3 5```

### 输出

```
6```

## 样例 #3

### 输入

```
6
2 4
4 6
6 2```

### 输出

```
11```

# 题解

## 作者：Purslane (赞：4)

# Solution

显然，每一个合法的简单回路**必定对应三角剖分中的一个子多边形**，如图所示。

![](https://s21.ax1x.com/2024/12/12/pAb1jGn.png)

观察发现，他是若干个联通的三角形的并。

考虑把相邻的三角形当做点，在相邻三角形之间连边，本质上就是求联通块的个数。

注意到三角剖分一定对应了一棵树（归纳易证），因此就是无聊的树形 DP。

如何求三角剖分？直接枚举所有相邻边即可！

复杂度 $O(n \log n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=2e5+10,MOD=1e9+7;
int n,tot,bl[MAXN],ans,dp[MAXN];
vector<int> G[MAXN],T[MAXN];
int dis(int i,int j) {
	if(j>=i) return j-i;
	return j+n-i;	
}
void dfs(int u,int f) {
	dp[u]=1;
	for(auto v:T[u]) {
		if(v==f) continue ;
		dfs(v,u),dp[u]=(dp[u]*(dp[v]+1))%MOD;
	}
	ans=(ans+dp[u])%MOD;
	return ;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n;
	map<pair<int,int>,int> mp;
	ffor(i,1,n) G[i].push_back(i%n+1),G[i%n+1].push_back(i);
	ffor(i,1,n-3) {
		int x,y;
		cin>>x>>y;
		G[x].push_back(y),G[y].push_back(x);
		mp[{x,y}]=mp[{y,x}]=i;
	}
	ffor(i,1,n) {
		sort(G[i].begin(),G[i].end(),[&](int A,int B) {return dis(A,i)<dis(B,i);});
		ffor(j,0,G[i].size()-2) {
			int u=i,v=G[i][j],w=G[i][j+1];
			if(u<=v&&u<=w) {
				++tot;
				int id1=mp[{u,v}],id2=mp[{u,w}],id3=mp[{v,w}];
				if(id1) {
					if(bl[id1]) T[tot].push_back(bl[id1]),T[bl[id1]].push_back(tot);
					else bl[id1]=tot;	
				}
				if(id2) {
					if(bl[id2]) T[tot].push_back(bl[id2]),T[bl[id2]].push_back(tot);
					else bl[id2]=tot;
				}
				if(id3) {
					if(bl[id3]) T[tot].push_back(bl[id3]),T[bl[id3]].push_back(tot);
					else bl[id3]=tot;
				}
			}
		}
	}
	dfs(1,0);
	cout<<ans;
	return 0;
}
```

---

## 作者：VainSylphid (赞：2)

显然任何一条回路也能用给定的边三角剖分，否则的话就不是一个合法的三角剖分。

如果我们把三角形看成点，把有公共边的三角形对应点连边，得到的会是一棵树，连通和无环都是显然的。

那么任何一条回路对应的若干个三角形应该在这棵树上连通，我们只要做一次树形 dp 统计这棵树上的连通块个数即可。

建树的实现有一些小技巧。考虑破环成链，把 $(1,n)$ 这条边和三角剖分的边放在一起处理，共有 $n-2$ 条边，恰好每个三角形可以对应一条边。

我们将这些边按照 $\lvert u-v\rvert$ 排序，维护每个点的前驱边和后继边。

遍历到 $(u,v)$ 时，如果 $u$ 的后继边 $(u,w)$ 不是多边形的某条边，将 $(u,v)$ 和对应的点连边，同理处理 $v$ 的前驱边 $(w,v)$。

然后将 $u$ 的后继边和 $v$ 的前驱边都设成 $(u,v)$。

代码简单而且常数小，结合计数排序复杂度线性，目前是最优解。


```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int mod = 1000000007;
struct edge{
	int u,v;
}t[200005],g[200005];
vector<int> e[200005];
int bc[200005];
int n,pre[200005],nxt[200005];
int ans,dp[200005];
void dfs(int u)
{
	dp[u] = 1;
	for(auto v : e[u])
		dfs(v),dp[u] = (ll)dp[u] * (dp[v] + 1) % mod;
	ans = (ans + dp[u]) % mod;
}
int main()
{
	scanf("%d",&n);
	for(int i = 1;i <= n - 3;i++)
	{
		scanf("%d%d",&t[i].u,&t[i].v);
		if(t[i].u > t[i].v)
			swap(t[i].u,t[i].v);
	}
	t[n - 2] = {1,n};
	for(int i = 1;i <= n - 2;i++)
		bc[t[i].v - t[i].u]++;
	for(int i = 1;i < n;i++)
		bc[i] += bc[i - 1];
	for(int i = n - 2;i;i--)
		g[bc[t[i].v - t[i].u]--] = t[i];
	for(int i = 1;i <= n - 2;i++)
	{
		if(nxt[g[i].u])
			e[i].push_back(nxt[g[i].u]);
		if(pre[g[i].v])
			e[i].push_back(pre[g[i].v]);
		pre[g[i].v] = nxt[g[i].u] = i;
	}
	dfs(n - 2);
	printf("%d\n",ans);
    return 0;
}
```

---

## 作者：dAniel_lele (赞：2)

首先很显然三角剖分是一种广义串并联图。所以三角剖分完全是在逗你玩。

考虑删一缩二叠重边。

设计 $dp_{(u,v),0/1}$ 表示目前 $(u,v)$ 边，有多少种从 $u$ 走到 $v$ 的方式，对应的原图的部分有多少环。

显然删一度点不用管他。

对于缩二度点，考察 $(u,w)$ 与 $(w,v)$。容易得到转移：

* $f_0=dp_{(u,w),0}\times dp_{(w,v),0}$；
* $f_1=dp_{(u,w),1}+dp_{(w,v),1}$。

对于叠合重边，考虑叠合 $dp_{(u,v),0/1}$ 与 $dp'_{(u,v),0/1}$，考虑拼在一起的环即可，有转移：

* $f_0=dp_{(u,v),0}+dp'_{(u,v),0}$；
* $f_1=dp_{(u,v),1}+dp'_{(u,v),1}+dp_{(u,v),0}\times dp'_{(u,v),0}$。

最后缩成一条边 $(u,v)$ 输出 $dp_{(u,v),1}$ 即可。

总复杂度 $O(n\log n)$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define double long double
#define mid ((l+r)>>1)
using namespace std;
const int mod=1e9+7;
map<pair<int,int>,int> f[2];
set<int> st[200005];
int ins[200005];
signed main(){
	int n; cin>>n;
	for(int i=1;i<=n;i++){
		int u=i,v=i%n+1; if(u>v) swap(u,v);
		st[u].insert(v);
		st[v].insert(u);
		f[0][make_pair(u,v)]=1;
	}
	for(int i=1;i<=n-3;i++){
		int u,v; cin>>u>>v; if(u>v) swap(u,v);
		st[u].insert(v);
		st[v].insert(u);
		f[0][make_pair(u,v)]=1;
	}
	queue<int> q;
	for(int i=1;i<=n;i++) if(st[i].size()==2) q.push(i),ins[i]=1;
	for(int j=1;j<=n-2;j++){
		int now=q.front(); q.pop();
		int x=*st[now].begin(),y=*next(st[now].begin());
		st[now].erase(x),st[now].erase(y);
		pair<int,int> p1=make_pair(now,x),p2=make_pair(now,y),p3=make_pair(x,y);
		if(p1.first>p1.second) swap(p1.first,p1.second);
		if(p2.first>p2.second) swap(p2.first,p2.second);
		if(p3.first>p3.second) swap(p3.first,p3.second);
		int tmp[2];
		tmp[0]=f[0][p1]*f[0][p2]%mod;
		tmp[1]=f[1][p1]+f[1][p2]%mod;
		(f[1][p3]+=tmp[0]*f[0][p3]+tmp[1])%=mod;
		(f[0][p3]+=tmp[0])%=mod;
		st[x].erase(now),st[y].erase(now);
		st[x].insert(y),st[y].insert(x);
		if(st[x].size()==2&&!ins[x]) q.push(x),ins[x]=1;
		if(st[y].size()==2&&!ins[y]) q.push(y),ins[y]=1;
	}
	int now=q.front();
	pair<int,int> p=make_pair(now,*st[now].begin());
	if(p.first>p.second) swap(p.first,p.second);
	cout<<f[1][p];
	return 0;
}
```

---

## 作者：Kingna (赞：1)

我们发现一条回路是多个三角形拼接形成的环状结构。

我们将有公共边的三角形连边，形成一颗树，求出树中的连通块数量。

如何将有公共边的三角形连边？考虑顶点 $u$ 的所有出边 $(u,v_i)$，将每个 $(u,v_i)$ 两侧的三角形连边。

如何求出连通块的数量？考虑树形 dp，$f_u=∏(f_v+1)$ 即可。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define PII pair<int, int>
#define _for(i, a, b) for (int i = (a); i <= (b); i++)
#define _pfor(i, a, b) for (int i = (a); i >= (b); i--)
#define int long long
const int N = 3e5 + 5, mod = 1e9 + 7;

int n, idx, nidx, f[N], res;
vector<int> G[N], nG[N]; 
map<pair<int, int>, int> pos;
map<pair<int, pair<int, int> >, int> vis;

void dfs(int u, int fa) {
  f[u] = 1;
  for (auto v : nG[u]) {
    if (v == fa) continue;
    dfs(v, u);
//    cout << u << ' ' << v << endl;
    f[u] = f[u] * (f[v] + 1) % mod;
  }
}

void S(int &a, int &b, int &c) {
  if (a > b) swap(a, b);
  if (a > c) swap(a, c);
  if (b > c) swap(b, c);
//  cout << a << ' ' << b << ' ' << c << endl; 
}

int dis(int a, int b) {
  if (a <= b) return b - a;
  return b - a + n;
} 

signed main() {
  cin >> n;
  _for(i, 1, n - 1) G[i].push_back(i + 1), G[i + 1].push_back(i), pos[{i, i + 1}] = pos[{i + 1, i}] = ++idx;
  G[1].push_back(n); G[n].push_back(1); pos[{1, n}] = pos[{n, 1}] = ++idx;
  _for(i, 1, n - 3) {
    int u, v;
    cin >> u >> v;
    G[u].push_back(v);
    G[v].push_back(u);
    pos[{u, v}] = pos[{v, u}] = ++idx;
  }
  _for(i, 1, n) sort(G[i].begin(), G[i].end(), [&](int x, int y) {
    return dis(i, x) < dis(i, y);
  });
  _for(i, 1, n) {
    int sz = G[i].size();
    if (sz == 3) {
      int ta = pos[{i, G[i][0]}], tb = pos[{G[i][0], G[i][1]}], tc = pos[{G[i][1], i}]; S(ta, tb, tc);
      if (!vis[{ta, {tb, tc}}]) vis[{ta, {tb, tc}}] = ++nidx;
      int t1 = pos[{i, G[i][1]}], t2 = pos[{i, G[i][2]}], t3 = pos[{G[i][2], G[i][1]}]; S(t1, t2, t3);
      if (!vis[{t1, {t2, t3}}]) vis[{t1, {t2, t3}}] = ++nidx;
      int w1 = vis[{ta, {tb, tc}}];
      int w2 = vis[{t1, {t2, t3}}];
      nG[w1].push_back(w2);
      nG[w2].push_back(w1); 
//      cout << w1 << ' ' << w2 << endl; 
      continue; 
    } 
    _for(j, 1, sz - 2) {
      int u = G[i][j], v = G[i][j + 1];
      if (j == 1) {
        int tmp = min(u, i);
        int ta = pos[{i, G[i][0]}], tb = pos[{G[i][0], u}], tc = pos[{u, i}]; S(ta, tb, tc);
        if (!vis[{ta, {tb, tc}}]) vis[{ta, {tb, tc}}] = ++nidx;
        int t1 = pos[{i, u}], t2 = pos[{i, v}], t3 = pos[{u, v}]; S(t1, t2, t3);
        if (!vis[{t1, {t2, t3}}]) vis[{t1, {t2, t3}}] = ++nidx;
        int w1 = vis[{ta, {tb, tc}}];
        int w2 = vis[{t1, {t2, t3}}];
        nG[w1].push_back(w2);
        nG[w2].push_back(w1); 
//        cout << w1 << ' ' << w2 < < endl; 
      }
      else if (j == sz - 2) {
        int tmp = min(i, u);
        int ta = pos[{i, u}], tb = pos[{v, i}], tc = pos[{u, v}]; S(ta, tb, tc);  
        if (!vis[{ta, {tb, tc}}]) vis[{ta, {tb, tc}}] = ++nidx;
        int t1 = pos[{i, u}], t2 = pos[{i, G[i][sz - 3]}], t3 = pos[{G[i][sz - 3], u}]; S(t1, t2, t3);
        if (!vis[{t1, {t2, t3}}]) vis[{t1, {t2, t3}}] = ++nidx;
        int w1 = vis[{ta, {tb, tc}}];
        int w2 = vis[{t1, {t2, t3}}];
        nG[w1].push_back(w2);
        nG[w2].push_back(w1); 
//        cout << w1 << ' ' << w2 << endl; 
      } 
      else {
        int ta = pos[{i, G[i][j - 1]}], tb = pos[{i, u}], tc = pos[{u, G[i][j - 1]}]; S(ta, tb, tc);
        if (!vis[{ta, {tb, tc}}]) vis[{ta, {tb, tc}}] = ++nidx;
        int t1 = pos[{i, u}], t2 = pos[{i, v}], t3 = pos[{u, v}]; S(t1, t2, t3);
        if (!vis[{t1, {t2, t3}}]) vis[{t1, {t2, t3}}] = ++nidx;
        int w1 = vis[{ta, {tb, tc}}];
        int w2 = vis[{t1, {t2, t3}}];
        nG[w1].push_back(w2);
        nG[w2].push_back(w1); 
//        cout << w1 << ' ' << w2 << endl; 
      }
    } 
  }
  _for(i, 1, n) {
    sort(nG[i].begin(), nG[i].end());
    nG[i].erase(unique(nG[i].begin(), nG[i].end()), nG[i].end()); 
  } 
  dfs(1, 0);
  _for(i, 1, nidx) res = (res + f[i]) % mod;
  cout << max(1ll, res) << endl;
}
```

---

