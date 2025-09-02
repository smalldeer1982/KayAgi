# [RMI 2019] 还原 / Restore Arrays

## 题目描述

**本题中下标是 $\texttt{\textcolor{red}{0-indexed}}$ 的。**

构造一个长度为 $n$ 的 $\text{01}$ 串 $a_0\sim a_{n-1}$，满足以下条件：

- $\forall 0\le i\lt m$，都有 $k_i\mathrm{thmin}(a_{l_i},a_{{l_i}+1},\ldots,a_{r_i})=\mathrm{val}_i$。

这里，$k\mathrm{thmin}$ 表示一个数列内第 $k$ 小的元素。

## 说明/提示


对于 $100\%$ 的数据，保证：

- $1\le n\le 5\times 10^3$；
- $1\le m\le 10^4$；
- $0\le l_i\le r_i\lt n$；
- $1\le k_i\le r_i-l_i+1$；
- $\mathrm{val}_i\in \{0,1\}$。

### 子任务

| 编号 | $n\le$ | $m\le$ | 特殊性质 | 分值 |
| :-: | :-: | :-: | :-: | :-: |
| $1$ | $18$ | $200$ | / | $7$ |
| $2$ | $5\times 10^3$ | $10^4$ | $\text{A}$| $13$ |
| $3$ | $5\times 10^3$ | $10^4$ | $\text{B}$ | $25$ |
| $4$ | $5\times 10^3$ | $10^4$ | / | $55$ |

- 特殊性质 $\text{A}$：$\forall 0\le i\lt m$，$k_i=1$。
- 特殊性质 $\text{B}$：$\forall 0\le i\lt m$，要么 $k_i=1$，要么 $k_i=r_i-l_i+1$。


## 样例 #1

### 输入

```
4 5
0 1 2 1
0 2 2 0
2 2 1 0
0 1 1 0
1 2 1 0```

### 输出

```
0 1 0 0```

# 题解

## 作者：Bill_luogu (赞：4)

此题使用差分约束，想要 $\color{#52C41A}{AC}$ 此题，必须经过以下步骤。
## STEP 1：什么是差分约束系统？
模板题：[P5960 【模板】差分约束](https://www.luogu.com.cn/problem/P5960)

差分约束系统就是由 $n$ 个变量， $m$ 条形式如 $a_{i}-a_{j}\le k$ 不等式组成，求他们的任意解。
## STEP 2：用什么算法求解？
观察 $a_{i}-a_{j}\le k$，与最短路最对比： $dis_{y}-dis_{x}\le w_{<x,y>}$，发现大致相同，于是用最短路算法求解，其中的 $dis_{i}$ 就是 $a_{i}$ 的其中一个解。
## STEP 3：如何建边？
设 $sum_{i}=sum_{i-1}+a_{i}$，则当 $val_{i}=1$ 时，证明前面最多有 $k-1$ 个 $0$，$sum_{r}-sum_{l-1}\ge r-l+1-(k-1)=sum_{l-1}-sum_{r}\le l+k-2-r$，当 $val_{i}=0$ 时，表示至少有 $k$ 个 $0$，$sum_{r}-sum_{l-1}\le r-l+1-k$。将 $l-1$ 和 $r$ 连边。
## STEP 4：从哪个点开始？
建一个超级源节点 $0$，和每个点都连一条权值为 $0$ 的边。  
怎么知道这是对的呢？  
很简单，设 $a_{0}$ 为 $\infty$，相当于 $n$ 条不等式 $a_{i}\le a_{0}+0$，不影响其他不等式。
## STEP 5：用哪个最短路算法？
很多人都会想到用 dijkstra ，当你提交后会发现花花绿绿的，这是因为 dijkstra 判不了无解（即有负环），所以使用 SPFA 或者 Bellman-Ford ，本蒟蒻使用的是 SPFA 。
## STEP 6：一些小问题
再次提交，发现又是花花绿绿。再次回到题目，由于是 $01$ 串，所以满足 $a_{i}\le a_{i+1}$ 和 $a_{i+1}\le a_{i}+1$ ，转换分别得到 $a_{i}-a_{i+1}\le 0$ 和 $a_{i+1}-a_{i}\le1$，于是我们又得到了许多差分约束。后来发现 TLE 了，考虑优化。
## AC Code：
```cpp
#include<iostream>
#include<queue>
#include<vector>
using namespace std;
queue<int> q;
vector<int> v[10010];
int dis[100010],cnt[10010];
bool vis[10010];
int n,m;
bool spfa()
{
	while(q.size())
	{
		int x=q.front();
		q.pop();
		vis[x]=0;
		for(int i=0;i<v[x].size();i+=2)
		{
			int y=v[x][i],w=v[x][i+1];
			if(dis[x]+w>=dis[y])continue;
			dis[y]=dis[x]+w;
			cnt[y]=cnt[x]+1;
			if(cnt[y]>=min(n,(int)3e3))//玄学优化
			{
				cout<<"-1";//无解
				return 0;
			}
			if(!vis[y])
			{
				q.push(y);
				vis[y]=1;
			}
		}
	}
	return 1;
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		int l,r,k,val;
		cin>>l>>r>>k>>val;
		l++,r++;//本蒟蒻习惯下标从 1 开始
		if(val==1)
		{
			v[r].push_back(l-1);
			v[r].push_back(l+k-2-r);
		}
		else
		{
			v[l-1].push_back(r);
			v[l-1].push_back(r-l+1-k);
		}
	}
	for(int i=1;i<=n;i++)dis[i]=2147483647;//初始化
	for(int i=0;i<n;i++)v[i].push_back(i+1),v[i].push_back(1),v[i+1].push_back(i),v[i+1].push_back(0);//加边
	vis[0]=1;
	q.push(0);
	if(spfa())
	{
		for(int i=1;i<=n;i++)
			cout<<(dis[i]>dis[i-1])<<' ';
	}
	return 0;
}
```

---

## 作者：Chengqijun2012 (赞：2)

# [P12088 [RMI 2019] 还原 / Restore Arrays](https://www.luogu.com.cn/problem/P12088)

## Updata 2025/5/16：改正了一处小错误。
首先通过题目很容易看出，这是一道差分约束的题目。~~标签不是有吗你 TM 扯这么多废话干什么~~

那么只要你做过[这题](https://www.luogu.com.cn/problem/P5960)就知道差分约束要用 SPFA ~~这个死了的算法~~来做，因为要判断负环，也就是无解的情况。

## 解题步骤：
### 第一步：
题目中规定 $val_{i} \in \{0,1\}$，那就非常好做了。我们设 $s$ 数组为 $a$ 数组的前缀和数组，也就是 $s_{i}=s_{i-1}+a_{i}$，则因为 $a$ 数组是 $\texttt 01$ 串，所以我们以此时的 $s_{i}$ 也代表数列前 $i$ 个数中 $1$ 的个数。然后分两种情况讨论：
1. 当 $val_{i}=0$ 时，数列内第 $k_{i}$ 小的元素是 $0$，则保证数列前 $k_{i}$ 小的数都是 $0$，容易得出 $s_{r_{i}}-s_{l_{i}-1}\le r_{i}-l_{i}+1-k_{i}$。
2. 当 $val_{i}=1$ 时，数列内第 $k_{i}$ 小的元素是 $1$，则保证数列前 $k_{i}$ 小的数最多有 $k_{i}-1$ 个 $0$，容易得出 $s_{r_{i}}-s_{l_{i}-1}\ge r_{i}-l_{i}+1-(k_{i}-1)$，可这是大于号啊，怎么建边？别着急，根据 $x-y\ge z=y-x\le (-z)$ 可以发现，上面的约束可以转化成 $s_{l_{i}-1}-s_{r_{i}}\le -(r_{i}-l_{i}+1-(k_{i}-1))$。如果你不喜欢负数，你还可以把它改成 $s_{l_{i}-1}-s_{r_{i}}\le k_{i}-1-(r_{i}-l_{i}+1)$。

### 第二步：
根据我们刚刚推理出来的约束，可以建两条边，分别是：
- 当 $val_{i}=0$ 时：一条 $l_{i} \to r_{i} +1$，权值为 $r_{i}-l_{i}+1-k_{i} $
- 一条 $r_{i}+1 \to l_{i}$，权值为 $-(r_{i}-l_{i}+1-(k_{i}-1))$ 或 $k_{i}-1-(r_{i}-l_{i}+1)$ 的边。（其实一条边的权值有很多，只要满足约束就行了）

连边的时候要注意：这题的下标是从 $0$ 开始的，所以我们要把 $r_{i}-(l_{i}-1)$ 转化成 $(r_{i}+1)-l_{i}$。不然数组会越界。

由于这题是 $\texttt 01$ 串，有可能会连很多重复的，无用的边，所以直接跑 SPFA 会 T 几个点，要加点优化。

AC Code：
```cpp
#include <iostream>
#include <cstring>
#include <queue>
#include <vector>
#include <climits>
#include <algorithm>
#include <cmath>
#define ll long long
#define P pair<int, int>
#define MP make_pair
#define PU push_back
#define li(x) x << 1
#define ri(x) (x << 1) | 1
#define INF LLONG_MAX >> 2
using namespace std;
const int N = 5e3 + 5;
int n, m, d[N], cnt[N];
vector<P> g[N];
bool inv[N];

inline int read(){   //快读
	int f = 1, x = 0;
	char c = getchar();
	while(c < '0' || c > '9'){if(c == '-') f = -1; c = getchar();}
	while('0' <= c && c <= '9') x = x * 10 + (int)(c - '0'), c = getchar();
	return x * f;
}

void SPFA(int s){
	memset(d, 0x3f, sizeof(d));
	queue<int> q;
	d[s] = 0;
	q.push(s);
	inv[s] = true;
	while(!q.empty()){
		int u = q.front();
		q.pop();
		inv[u] = false;
		for(auto [w, v] : g[u])
			if(d[v] > d[u] + w){
				d[v] = d[u] + w;
				if(!inv[v]){
					cnt[v] = cnt[u] + 1;
					if(cnt[v] > min(n, 3000)) puts("-1"), exit(0);      //玄学优化，不加min(n, 3000)会TLE掉4个点
					inv[v] = true, q.push(v);
				}
			}
	}
}

int main(){
//	freopen("water.in.txt", "r", stdin);
//	freopen("water.out.txt", "w", stdout);

//  ios::sync_with_stdio(false);
//  cin.tie(0), cout.tie(0);
	
	n = read(), m = read();
	for(int i = 1, l, r, k, val; i <= m; i++){
		l = read(), r = read(), k = read(), val = read();
		if(val) g[r + 1].push_back(MP(k - 1 - (r - l + 1), l));
		else g[l].push_back(MP(r + 1 - l - k, r + 1));
	}
	for(int i = 0; i < n; i++) g[i].PU(MP(1, i + 1)), g[i + 1].PU(MP(0, i));
	SPFA(0);
	for(int i = 1; i <= n; i++) cout << (d[i] > d[i - 1]) << ' ';
	cout << "\n";
	return 0;
}
```
完结撒花！！！

---

## 作者：fush (赞：2)

我们把答案数组设为 $a$，设 $s_0 = 0, s_i = s_{i - 1} + a_{i - 1}$。

考虑每个限制。  
如果 $val_i = 1$，我们要保证 $s_{r_i} - s_{l_i} \ge (r_i - l_i + 2 - k_i)$ 即 $s_{l_i} - s_{r_i} \le -(r_i - l_i + 2 - k_i)$。  
否则，需要使 $s_{r_i} - s_{l_i} \le (r_i - l_i + k_i - 1)$。

那么用差分约束即可。

```
#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define FL(a,b,c) for(int a=(b),a##end=(c);a<=a##end;++a)
#define FR(a,b,c) for(int a=(b),a##end=(c);a>=a##end;--a)
#define lowbit(x) ((x)&-(x))
#define eb emplace_back
#define ll long long
#define vt vector
#define ar(x) array<int,x>
#define PII pair<int, int>
#define max(a, b)({auto b5k5u7=(a);auto tmd67v8=(b);b5k5u7<tmd67v8?tmd67v8:b5k5u7;})
#define cmax(a, b)({auto tmd67v8=(b);(tmd67v8>a)&&(a=tmd67v8);})
#define min(a, b)({auto b5k5u7=(a);auto tmd67v8=(b);b5k5u7>tmd67v8?tmd67v8:b5k5u7;})
#define cmin(a, b)({auto tmd67v8=(b);(tmd67v8<a)&&(a=tmd67v8);})
constexpr int N = 5e3 + 10;
vt<PII>e[N];
int dis[N], f[N], vis[N], n, m;
#define addedge(u, v, w) e[u].eb(v,w)
queue<int>q;
void SPFA(int s){
	dis[s] = 0, q.push(s);
	int u, v, w;
	while (!q.empty()) {
		u = q.front(), q.pop(), vis[u] = 0;
		for(auto&z : e[u])
			if (dis[v = z.first] > (w = dis[u] + z.second))
				if(dis[v] = w, !vis[v])
					if (++f[v] > min(n, 3e3))cout << -1, exit(0);
					else q.push(v), vis[v] = 1;
	}
}
int32_t main(){
	cin.tie(0)->sync_with_stdio(0);
	cin >> n >> m;
	while(m--){
		int u, v, w, k;
		cin >> u >> v >> k >> w, v++;
		if(w)addedge(v, u, k - v + u - 1);
		else addedge(u, v, (v - u - k));
	}
	FL(i, 0, n - 1)addedge(i, i + 1, 1), addedge(i + 1, i, 0);
	memset(dis, 0x3f, sizeof dis), SPFA(0);
	FL(i, 1, n)cout << (dis[i] > dis[i - 1]) << " ";
	cout << endl;
	return 0;
}
```

---

## 作者：Tyih (赞：2)

# 前言

~~关于 SPFA，它死了。~~

如果你写的是正常的 SPFA，那么恭喜你，会喜提 $20$ 分的高分以及获得 TLE 三到四个点。

# Solution

前置知识：[差分约束](https://oi.wiki/graph/diff-constraints/)

首先本题限制了区间 $l$ 到 $r$ 的第 $k$ 小的元素为 $\mathrm{val}$（$\mathrm{val} \in \{0,1\}$）。
我们可以将其进行分类讨论：

1. 若 $\mathrm{val}=0$，则有区间 $l$ 到 $r$ 中 $0$ 的个数 $\ge k$，即 $1$ 的个数 $\le r-l+1-k$。（$r-l+1$ 为区间长度。）
2. 若 $\mathrm{val}=1$，则有区间 $l$ 到 $r$ 中 $0$ 的个数 $<k$，即 $1$ 的个数 $> r-l+1-k$，可以推出 $1$ 的个数 $\ge r-l+1-k+1$。

我们可以设一个 $Sum_i$ 表示前 $i$ 个数的前缀和。则 $Sum_r-Sum_{l-1}$ 可以表示为区间 $l$ 到 $r$ 中 $1$ 的个数。

我们就可以将上述的讨论进行转化：

$$
\begin{cases}
Sum_r-Sum_{l-1} \le r-l+1-k,\quad\quad\quad\quad \ \mathrm{val}=0 \\
Sum_r-Sum_{l-1} \le -(r-l+1-k+1),\quad\mathrm{val}=1
\end{cases}
$$

因为 $Sum_i$ 表示的是前缀和且数只有 $0$ 或 $1$，所以同时还要满足以下条件：

$$
\forall i \in [1,n],\text{都有}
\begin{cases}
Sum_i-Sum_{i-1} \le 1\\
Sum_{i-1}-Sum_{i} \le0
\end{cases}
$$

之后就可以愉快的使用差分约束 AC 本题了。

**注：这里的差分约束要用 Bellman-Ford，若使用 SPFA 你将会 TLE 的很惨**。

# Code

```cpp
#include <bits/stdc++.h>
#define IOS cin.tie(0),cout.tie(0),ios::sync_with_stdio(0)
#define ll long long
#define db double
#define pb push_back
using namespace std;
const int N=5e3+5;
ll n,m,s[N],cnt[N];
vector<array<int,3>> to;
int main(){
    IOS;cin>>n>>m;
    memset(s,0x7f,sizeof s);
  	for(int i=1;i<=n;i++){
		to.pb({i-1,i,1});
		to.pb({i,i-1,0});
	}  
    for(int i=1,l,r,k,v;i<=m;i++){
    	cin>>l>>r>>k>>v;
    	l++;r++;//在这里将其转化为下标从一开始 
    	if(v) to.pb({r,l-1,-(r-l+1-k+1)});
		else to.pb({l-1,r,r-l+1-k});
	}
	s[0]=0;
	bool flag=0;
	for(int i=1;i<=n;i++){//Bellman-Ford
		flag=0;
		for(auto e:to){
			int u=e[0],v=e[1],w=e[2];
			if(s[v]>s[u]+w){
				flag=1;
				s[v]=s[u]+w;
			}
		}
    	if(!flag) break;
	}
	if(flag){
		cout<<"-1\n";
		return 0;
	}
	for(int i=1;i<=n;i++){
		cout<<s[i]-s[i-1]<<" ";
	}
    return 0;
}
```

# 后记

关于 SPFA，它又活了。

你可以使用一些玄学优化来通过本题，就像这样：

```cpp
	memset(s,0x7f,sizeof s);
	queue<int> q;
	q.push(0);
	vis[0]=1;s[0]=0;
	int tt=0;
	while(!q.empty()){//SPFA
		int u=q.front();q.pop();
		vis[u]=0;
		for(PLL tp:to[u]){
			int v=tp.first,w=tp.second;
			tt++;
			if(tt>2e7){//玄学优化
				cout<<-1<<"\n";
				return 0;
			}
			if(s[u]+w<s[v]){
				s[v]=s[u]+w;
				cnt[v]=cnt[u]+1;
				if(cnt[v]>=n){
					cout<<"-1\n";
					return 0;
				}
				if(!vis[v]) q.push(v),vis[v]=1;
			}
		}
	}
  for(int i=1;i<=n;i++) cout<<s[i]-s[i-1]<<" ";
```

不过不建议在考试时使用。

---

## 作者：Loyal_Soldier (赞：1)

前置知识：差分约束系统。

模板：[P5960 【模板】差分约束](https://www.luogu.com.cn/problem/P5960)

### 思路

设 $sum_i$ 为 $a$ 数组前 $i$ 个数的和，即为 $a$ 数组前 $i$ 个数中 $1$ 的个数。

- $\text{val}_i = 0$，表示区间至少有 $k$ 个 $0$，$l - 1$ 向 $r$ 连一条边权为 $r - l + 1 - k$ 的边，因为 $sum_r - sum_{l - } \le r - l + 1 - k$。

- $\text{val}_i = 1$，表示区间至多有 $k - 1$ 个 $0$，即 $sum_r - sum_{l - 1} \ge r - l + 1 - (k - 1)$，转化一下即为 $sum_{l - 1} - sum_r\le - (r - l + 1 - (k - 1))$，$r$ 向 $l - 1$ 连一条边权为 $-(r - l + 1 - (k - 1))$ 的边。

由于 $sum$ 数组是前缀和，应当建出 $sum_i - sum_{i - 1}\le 1$ 和 $sum_{i - 1} - sum_i \le 0$ 的边。

然后跑一遍 Bellman-Ford 或 SPFA 即可，记得判断负环。

### 代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define double long double
using namespace std;
const int N = 5e3 + 10;
int n, m;
int dis[N], cnt[N];
vector <array<int, 3> > G;//array 是一种类似结构体的 STL
signed main()
{
	cin >> n >> m;
	for(int i = 1;i <= m;i ++)
	{
		int l, r, k, val;
		cin >> l >> r >> k >> val;
		l ++, r ++;//本人下标习惯从 1 开始
		if(val == 0) G.push_back({l - 1, r, r - l + 1 - k});
		else G.push_back({r, l - 1, -(r - l + 1 - k + 1)});//连边
	}
	for(int i = 1;i <= n;i ++)
	{
		G.push_back({i - 1, i, 1});
		G.push_back({i, i - 1, 0});//连边
	}
	memset(dis, 0x3f, sizeof(dis));//初始化成极大值
	dis[0] = 0;
	for(int i = 1;i <= n;i ++)
		for(auto j : G)
		{
			int u = j[0], v = j[1], w = j[2];
			dis[v] = min(dis[v], dis[u] + w);
		}//Bellman-Ford
	for(auto i : G)
	{
		int u = i[0], v = i[1], w = i[2];
		if(dis[v] > dis[u] + w)
		{
			cout << -1;
			return 0;
		}//判断是否有负环
	}
	for(int i = 1;i <= n;i ++) cout << dis[i] - dis[i - 1] << ' ';//输出
	return 0;
}
```

---

## 作者：Sunset_afterglow (赞：1)

这道题目也是我切过最水的蓝，秒出思路，然后就过了，简直不可思议。
前置知识：前缀和，差分约束。
# 思路
本体思路极为好想，我们钦定 $sum_i$ 为前 $i$ 个数中有多少个 $0$，然后约束条件，就可以转化为，当 $val = 0$ 时，$sum_r-sum_{l-1}\ge k$，当 $val=1$ 时，$sum_r-sum_{l-1}<k$,此时的差分约束已经初见端详，我们直接移项，得出两式分别可以化成 $e(r ,l-1 ,-k),e(l-1 ,r ,k-1)$。值得注意的时 $sum_i-sum_{i-1} \in {0 ,1}$，直接连边就行了。
##### *此处的 $e(x ,y ,z)$，表示 $x$，到 $y$，一条边权为 $z$，的边。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read() {
	int x = 0 ,f = 1;
	char ch = getchar();
	while('0' > ch || ch > '9') {
		if(ch == '-') f = -1;
		ch = getchar();
	}
	while('0' <= ch && ch <= '9') {
		x = (x << 3) + (x << 1) + (ch & 15);
		ch = getchar();
	}
	return x * f;
}
const int N = 5e3 + 5;
struct Point {
	int u ,v ,w;
}at[5 * N];
int n ,m ,mptt ,dist[N] ,cnt[N];
bool flag[N];
queue<int>que;
vector<pair<int ,int> >vt[N];
inline int Spfa() {
  memset(dist ,0x3f ,sizeof dist);
  dist[0] = 0;
  for(int i = 1;i <= n + 1;++ i) {
  	for(int j = 1;j <= mptt;++ j) {
  		if(dist[at[j].v] > dist[at[j].u] + at[j].w) {
				dist[at[j].v] = dist[at[j].u] + at[j].w;
				cnt[at[j].v] = cnt[at[j].u] + 1;
				if(cnt[at[j].v] > n + 1) {return -1;}
			}
		}
	}
	cout << !dist[1] << ' ';
	for(int i = 2;i < n;++ i)
		cout << !(dist[i] - dist[i - 1]) << ' ';
	return !(dist[n] - dist[n - 1]);
}
signed main() {
	n = read() ,m = read();
	for(int i = 1 ,l ,r ,k ,vl;i <= m;++ i) {
		l = read() + 1 ,r = read() + 1 ,k = read() ,vl = read();
		if(vl) {at[++ mptt] = Point{l - 1 ,r ,k - 1};}
		if(!vl) {at[++ mptt] = Point{r ,l - 1 ,-k};}
	}
	for(int i = 0;i < n;++ i) {
		vt[i + 1].push_back(make_pair(i ,0));
		vt[i].push_back(make_pair(i + 1 ,1));
		at[++ mptt] = Point{i + 1 ,i ,0};
		at[++ mptt] = Point{i ,i + 1 ,1};
	}
	cout << Spfa();
	return 0;
}
```

---

## 作者：Fyq_20 (赞：1)

## [题解：RMI2019 还原 / Restore Arrays](https://www.luogu.com.cn/problem/P12088) 

**题面题意很清楚，这里不作解释。**

## 主要思路：差分约束

注意到 $a_i$ 中只可能有 $0$ 或 $1$，所以可以断定题面中 $val_i$ 也只可能是 $0$ 或 $1$。  
此时发现如果 $val_i=1$，则在 $[l_i,r_i]$ 上最多有 $k_i-1$ 个 $0$，即最少 $(r_i-l_i+1-k_i+1)$ 个 $1$；  
反之，如果 $val_i=0$，则在 $[l_i,r_i]$ 上最少有 $k$ 个 $0$，即最多 $(r_i-l_i+1-k_i)$ 个 $1$。

容易想到，若组建前缀和数组 $s_i$，
则此时有许多二元不等式，形如：
$$s_{r_i} - s_{l_{i}-1}\ge r_i-l_i+1-k_i+1\ \ (val_i=1)$$  
或
$$s_{r_i} - s_{l_{i}-1}\le r_i-l_i+1-k_i\ \ (val_i=0)$$ 

此时这两种式子恰好可以化为差分约束标准式：
$$s_{l_{i}-1}-s_{r_i} \le -(r_i-l_i+1-k_i+1)\ \ (val_i=1)$$
$$s_{r_i} - s_{l_{i}-1}\le r_i-l_i+1-k_i\ \ (val_i=0)$$
所以只需要在 $val_i=1$ 时，  
从 $s_{r_i}$ 向 $s_{l_i-1}$ 连一条边权为 $-(r_i-l_i+1-k_i+1)$ 的边；  
在 $val_i=0$ 时，  
从 $s_{l_i-1}$ 向 $s_{r_i}$ 连一条边权为 $r_i-l_i+1-k_i$的边。

然后使用 $\text{SPFA}$ 或 $\text{Bellman-Ford}$ 计算最短路，如果有负环则说明没有方案，没有则还原出原数组正常输出。

**PS:需要注意在初始化的时候应当建出 $s_i-s_{i-1}\ge0$ 和 $s_i-s_{i-1}\le1$ 对应的边。**

建边部分 code：
```cpp
struct T
{
    int to,val;
};
vector<T> v[5005];
//上方为定义部分
cin>>l>>r>>k>>val;
if(val==1)
{
    //此题下标从0开始，所以所有的下标+1
    v[r+1].push_back((T){l,-r+l-1+k-1});
}
else
{
    //此题下标从0开始，所以所有的下标+1
    v[l].push_back((T){r+1,r-l+1-k});
}
```

最终计算部分 code：
```cpp
struct T
{
    int to,val;
};
vector<T> v[5005];
int dist[5005];
int cnt[5005];
int ans[5005];
queue<int> q;
//定义部分结束
q.push(0);
bool flag=0;//负环
while(!q.empty())
{
    int x=q.front();//当前位置
    q.pop();
    for(int i=0;i<v[x].size();i++)
    {
        int to=v[x][i].to;//松弛位置
        int val=v[x][i].val;
        if(dist[to]>dist[x]+val)
        {
            dist[to]=dist[x]+val;
            cnt[to]=cnt[x]+1;
            if(cnt[to]>n+1)flag=1;
            q.push(to);
        }
    }
    if(flag)break;//有负环则跳出
}
if(flag)//特判
{
    cout<<-1<<endl;
    exit(0);
}
else
{
    for(int i=1;i<=n;i++)
    {
        ans[i]=dist[i]-dist[i-1];
        //这里直接-=会有问题
        cout<<ans[i]<<" ";
    }
}

---

## 作者：LostKeyToReach (赞：1)

因为是 $0/1$ 串，所以非常好做。

我们不妨维护这个字符串的前缀和 $p$，考虑分类讨论，当 $\text{val} = 0$，此时 $p_{r} - p_{l - 1} \ge k \Rightarrow p_r - k \ge p_{l - 1}$，连边 $(l - 1, r, -k)$；当 $\text{val} = 1$，此时 $p_{r} - p_{l - 1} \le k - 1 \Rightarrow p_r \le p_{l - 1} + k - 1$，连边 $(r, l - 1, k - 1)$。

同时注意到我们有 $p_{i} \le p_{i + 1} \le p_{i} + 1$，故此时连边 $(i, i + 1, 1)$ 和 $(i + 1, i, 0)$。

再连个虚拟源点跑 SPFA 即可，最终答案为 $p_i - p_{i - 1}$。

我代码写的是暴力松弛，时间复杂度 $O(nm)$。

代码如下：

```cpp
#define MULTI_TEST 0
int32_t main() {
#if MULTI_TEST == 1
#else
    int n, m;
    std::cin >> n >> m;
    Vec<std::tuple<int, int, int>> edges;
    For(i, 0, n - 1) edges.eb(i, i + 1, 1), edges.eb(i + 1, i, 0);
    For(i, 0, m - 1) {
        int l, r, k, v;
        std::cin >> l >> r >> k >> v;
        if (!v) edges.eb(r + 1, l, -k);
        else edges.eb(l, r + 1, k - 1);
    }
    For(i, 0, n) edges.eb(n + 1, i, 0);
    VI dist(n + 2, 1e9); dist[n + 1] = 0;
    For(i, 0, n) {
        bool ok = 0;
        for (auto& [x, y, w] : edges) {
            if (dist[x] != 1e9 && dist[y] > dist[x] + w) {
                dist[y] = dist[x] + w;
                ok = 1;
            }
        }
        if (!ok) break;
    }
    for (auto& [x, y, w] : edges) if (dist[x] != 1e9 && dist[y] > dist[x] + w) {
        return std::cout << "-1\n", 0;
    }
    int v = dist[0];
    For(i, 0, n) dist[i] -= v;
    VI ans(n, -1);
    For(i, 0, n - 1) {
        if (dist[i + 1] == dist[i] + 1) {
            ans[i] = 0;
        }
        else if (dist[i + 1] == dist[i]) {
            ans[i] = 1;
        }
        else {
            return std::cout << "-1\n", 0;
        }
    }
    For(i, 0, n - 1) std::cout << ans[i] << " \n"[i == n - 1];
#endif
}
```

---

## 作者：WuMin4 (赞：1)

## [[RMI 2019] 还原 / Restore Arrays](https://www.luogu.com.cn/problem/P12088)

## 思路

观察到对于 $01$ 序列求区间第 $k$ 小可以转换为统计 $01$ 的个数。

具体来说，假设长度为 $n$ 的 $01$ 序列 $a$ 中的第 $k$ 大为 $0$，则需要保证至多有 $n-k$ 个 $1$。若第 $k$ 大为 $1$，则需要保证至少有 $n-k+1$ 个 $1$。

于是我们可以对 $01$ 序列 $a$ 求前缀和，设前缀和数组为 $b$。

$k_i\mathrm{th \min}(a_{l_i},a_{l_i+1},\ldots,a_{r_i})=0$ 便可以表示为 $b_{r_i}-b_{l_i-1}\le (r_i-l_i+1)-k_i$。

$k_i\mathrm{th \min}(a_{l_i},a_{l_i+1},\ldots,a_{r_i})=1$ 也可以表示为 $b_r-b_{l-1}\ge (r-l+1)-k+1$，两边同时取反得到 $b_{l-1}-b_r\le k-1-(r-l+1)$。

因为 $b$ 单调不减且相邻两数之差不超过 $1$，则 $0\le b_i-b_{i-1}\le 1$，也就是 $b_{i-1}-b_i\le 0$ 和 $b_i-b_{i-1}\le 1$。

以上条件可以写成一个不等式组，显然满足[差分约束](https://www.luogu.com.cn/problem/P5960)的格式，直接套模板即可。

时间复杂度 $O(nm)$，差分约束直接写 spfa 可能会被卡，SLF 优化后可以通过。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
namespace cf{
	struct node{int x,d;};
	int n,dis[5005],lkj[5005];
	bool vis[5005];
	vector<node> t[5005];
	void add(int x,int y,int d){//a_x-a_y<=a_d
		t[y].push_back({x,d});
	}
	bool skjb(){
		memset(dis,0x3f,sizeof(dis));
		deque<int> q;
		q.push_back(0);
		dis[0]=0;
		while(!q.empty()){
			int u=q.front();q.pop_front();
			vis[u]=false;
			if(q.size()&&dis[q.front()]>dis[q.back()])
				swap(q.front(),q.back());
			for(node v:t[u]){
				if(dis[v.x]>dis[u]+v.d){
					dis[v.x]=dis[u]+v.d;
					if(!vis[v.x]){
						vis[v.x]=true;
						lkj[v.x]++;
						q.push_back(v.x);
						if(lkj[v.x]>n+1)
							return false;
					}
				}
			}
		}
		return true;
	}
	bool sol(){
		for(int i=1;i<=n;i++)
			t[0].push_back({i,0});
		return skjb();
	}
}
int n,m;
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	clock();
	cin>>n>>m;
	cf::n=n+1;
	for(int i=1;i<n;i++)
		cf::add(i+1,i,1),cf::add(i,i+1,0);
	for(int l,r,x,y,i=1;i<=m;i++){
		cin>>l>>r>>x>>y,l+=2,r+=2;
		if(y==0) cf::add(r,l-1,r-l+1-x);
		else cf::add(l-1,r,-(r-l+1-x+1));
	}
	if(!cf::sol()) cout<<-1;
	else for(int i=2;i<=n+1;i++)
		cout<<cf::dis[i]-cf::dis[i-1]<<" ";
	return 0;
}
```

[记录](https://www.luogu.com.cn/record/212738452)

---

