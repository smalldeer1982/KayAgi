# [ABC397E] Path Decomposition of a Tree

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc397/tasks/abc397_e

给定一棵包含 $NK$ 个顶点的树。顶点编号为 $1,2,\dots,NK$，其中第 $i$ 条边（$i=1,2,\dots,NK-1$）双向连接顶点 $u_i$ 和 $v_i$。

请判断是否可以将这棵树分解为 $N$ 条长度为 $K$ 的路径。更具体地说，判断是否存在满足以下条件的 $N \times K$ 矩阵 $P$：

- $P_{1,1}, \dots, P_{1,K}, P_{2,1}, \dots, P_{N,K}$ 是 $1,2,\dots,NK$ 的一个排列。
- 对于每个 $i=1,2,\dots,N$ 和 $j=1,2,\dots,K-1$，顶点 $P_{i,j}$ 和顶点 $P_{i,j+1}$ 之间存在一条边。


## 说明/提示

### 约束条件

- $1 \leq N$
- $1 \leq K$
- $NK \leq 2 \times 10^5$
- $1 \leq u_i < v_i \leq NK$
- 输入的图是一棵树
- 输入均为整数

### 样例解释 1

可以将树分解为由顶点 1,2 组成的路径、由顶点 3,4 组成的路径和由顶点 5,6 组成的路径。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
3 2
1 2
2 3
3 4
2 5
5 6```

### 输出

```
Yes```

## 样例 #2

### 输入

```
3 2
1 2
2 3
3 4
2 5
3 6```

### 输出

```
No```

# 题解

## 作者：sto__Liyhzh__orz (赞：4)

[洛谷传送门](https://www.luogu.com.cn/problem/AT_abc397_e) | [AT 传送门](https://atcoder.jp/contests/abc397/tasks/abc397_e)

感觉 D 比 E 难。。。

简单树上 DP。

非常显然，答案矩阵每一行是一条链。

那么我们可以记录每一个节点以他为根的子树的点数，为 ${siz_i}$。

1. 如果 ${siz_i}=k$

   以他为根的子树必须满足以下特征才可以成为阵矩的一行：

   这个节点 $i$ 的**有贡献**的儿子（即 ${siz_x}>0$）个数必须小于等于 $2$。

   否则输出 `No`。

   简单证明：非常显然，如果他有三个儿子有贡献，则一条链最多只能到达两个儿子，而上面的又过不来了，所以输出 `No`。


   然后，因为这个点已经跟他的儿子组成一行了，将 ${siz_i}\gets0$。

2. 如果 ${siz_i }\ne k$

   现在想要满足条件就必须让他父亲带着他了。

   且还要保持为一条链，则这个点的**有贡献**儿子个数必须小于等于 $1$。

   否则输出 `No`。

   证明同理。

代码：

```cpp
#include<bits/stdc++.h>
#define endl '\n'
#define lowbit(x) (x)&(-x)
#define small priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>
using namespace std;

typedef double db;
typedef long long ll;
//typedef __int128 III;
const db eqs=1e-6;
const int inf=1e9;
void ll_cmax(ll &a,ll b){a=a>b?a:b;}
void ll_cmin(ll &a,ll b){a=a<b?a:b;}
void int_cmax(int &a,int b){a=a>b?a:b;}
void int_cmin(int &a,int b){a=a<b?a:b;}
bool db_eq(db a,db b){return fabs(a-b)<eqs;}
bool number(char ch){return ch>='0' && ch<='9';}
bool lowerchar(char ch){return ch>='a' && ch<='z';}
int sqlong(int n){int sq=sqrt(n)+1;return min(sq,n);}

const int MAXN=200000+5;
vector<int>a[MAXN];
int son[MAXN],n,k;
vector<int>b[MAXN];

void dfs(int x,int fa)
{
	son[x]=1;
	for(int i=0;i<a[x].size();i++)
	{
		if(a[x][i]==fa) continue;
		dfs(a[x][i],x);
		son[x]+=son[a[x][i]];
		b[x].push_back(son[a[x][i]]);
	}
	int flag=0;
	for(int i=0;i<b[x].size();i++)
	{
    // 计算有贡献的儿子的个数
		if(b[x][i]>0)
		{
			flag++;
		}
	}
	if(son[x]==k) 
	{
		if(flag>2) 
		{
			cout<<"No\n";
			exit(0);
		}
		son[x]=0;
		return ;
	}
	if(flag<=1) return ;
	cout<<"No\n";
	exit(0);
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>k;
	int x,y;
	for(int i=1;i<n*k;i++)
	{
		cin>>x>>y;
		a[x].push_back(y);
		a[y].push_back(x);	
	}
	dfs(1,-1);
	if(son[1]!=0) cout<<"No\n";
	else cout<<"Yes\n";
	return 0;
}
//by Matrix_Power

```

[AC 记录。](https://atcoder.jp/contests/abc397/submissions/63840170)

---

## 作者：littlebug (赞：3)

E<D。

## Solution

树形 dp，不过好像也不怎么像 dp。

考虑自底向上贪心（或者叫 dp？），记录每个点在她的子树内连起来的链（如果该子树存在合法构造使得只有最多一条链连到这个点上）$c_u$，遇到长度 $=k$ 的链就砍掉。然后对于每一个 $u$ 判一下她每个叶子结点的 $c_v$，如果存在 $c_{v_1} + c_{v_2} = k - 1$，就可以把这两条链通过 $u$ 连起来，且只能这么做，当然在这之后就必须满足子树内没有其它的 $c_v \ne 0$ 了，毕竟 $u$ 只能用一次嘛。

如果不满足上述情况就无解，另外，还要在最后判一下 $c_1$ 是不是 $=k$。

具体还是看代码吧，注意一些细节。

## Code

```cpp
int n,k,c[MAXN];
vector <int> p[MAXN];

il void dfs(int u,int ufa)
{
	unordered_map <int,int> d; int now; d[0]=inf; bool op=0;
	for(auto v:p[u]) if(v!=ufa)
	{
		dfs(v,u);
		now=c[v];
		if(now==k || now==0) continue;
		
		if(d.count(k-now-1) && d[k-now-1]>0) 
		{
			if(op) cout<<"No",exit(0);
			--d[k-now-1],op=1;
		}
		else ++d[now];
	}
	
	int res=0;
	for(auto [i,j]:d) if(i>0 && j>0)
	{
		if(res) cout<<"No",exit(0);
		if(op) cout<<"No",exit(0);
		
		res=i;
	}
	
	c[u]=res+(!op);
}

signed main()
{
	read(n,k),_::r(p,n*k,false);
	
	if(k==1) return cout<<"Yes",0;
	
	dfs(1,0);
	cout<<((c[1]==k || c[1]==0) ? "Yes" : "No");
	
	return 0;
}
```

---

华风夏韵，洛水天依！

---

## 作者：wuzebang2009 (赞：3)

题目想让我们找出一颗树里是否可以分成 $n$ 条链使这 $n$ 条链有 $k$ 个节点，我们可以从下往上计算一个节点每棵子树的大小，如果树中有超过 $2$ 个子树的节点树不能被 $k$ 整除，那么就无解了，因为这其中肯定有两个子树要互相调用对方的节点，其他的多余节点就没法形成合法形状了。如果正好有 $2$ 个不能被整除，那么他们相互借用后能否合成合法形状，也就是看子树包含父节点的大小是否能被 $k$ 整除了。

```cpp
#include<bits/stdc++.h>
#define N 300010
using namespace std;
typedef long long ll;
vector<int> e[N];
int n,k,f=1;
int siz[N];

void dfs(int x,int fa){
    siz[x]=1;
    int rr=0;
    for(auto v:e[x]){
        if(v==fa) continue;
        dfs(v,x);
        siz[x]+=siz[v];
        if(siz[v]%k) rr++;
    }
    if(rr>2 || (rr==2 && siz[x]%k)) f=0;
}

int main(){
    cin>>n>>k;
    for(int i=1;i<n*k;i++){
        int a,b;
        cin>>a>>b;
        e[a].push_back(b),e[b].push_back(a);
    }
    dfs(1,0);
    if(f) cout<<"Yes";
    else cout<<"No";
}
```

---

## 作者：Awsdkl (赞：2)

考虑对于每一个结点，有三种可能：  
1. 和自己的**其中一个**子节点连为一条链。
2. 和自己的两个子节点连为一条链，自己为链中间的一个结点。
3. 自己所有子节点都可以独自构成一条长为 $K$ 的链，自己和父节点连为一条链。

不难发现，所有子节点构成的链的长度中最多只有两条不为 $K$。当有一条时，可以将当前结点接到这个链上；当有两条时，可以将这两条一左一右和当前结点拼接，即当前结点为这条链中间的一个点，然后计算这个长度，若不为 $K$ 则输出 ```No```。  
我们设计一个 ```dfs``` 函数，它的返回值为以这个点为**端点**的链的长度。及只有在第 $1$ 和第 $3$ 种情况时才会返回这个长度，当为第 $2$ 种情况时，返回 $0$。当不满足情况，即要输出 ```No``` 时，返回 $-1$。  
那么我们只需要在 ```dfs``` 过程中开一个数组记录一下每个 ```dfs``` 的返回值，然后再数一下数组中有多少个值不为 $K$，再跟上一个判断就行了。
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const int MAXN = 2e5+5;

int n, k;
vector<int> e[MAXN];

int dfs(int u, int fa)
{
	vector<int> siz;
	for(int i = e[u].size()-1;i >= 0;i--)
	{
		int v = e[u][i];
		if(v == fa) continue;
		int sz = dfs(v, u);
		if(sz) siz.push_back(sz);
		if(sz == -1) return -1;
	}
	int cnt = 0;
	int re = 0;
	vector<int> sta;//存的是长度不为 K 的链的长度
	for(int i = siz.size()-1;i >= 0;i--)
	{
		int sz = siz[i];
		if(sz != k)
		{
			sta.push_back(sz);
		}
	}
	if(sta.size() > 2)
	{
		return -1;
	}
	if(sta.size() == 1)
	{
		return sta[0]+1;
	}
	if(sta.size() == 2)
	{
		if(sta[0] + sta[1] + 1 != k) return -1;
		else return 0;
	}
	return 1;
  //最后记得要return 1（我就是这个 1 打成 0 了赛后4min才调出来）
}

int main()
{
	scanf("%d%d", &n, &k);
	for(int i = 1;i < n * k;i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	int re = dfs(1, 0);
	printf(re == k || re == 0 ? "Yes" : "No");
	return 0;
}
```

---

## 作者：AstaVenti_ (赞：1)

# $\mathbf{0x00}$ 启

蒟蒻的第 $\color{red}\mathbf{52}$ 篇题解。

# $\mathbf{0x01}$ 承

给出一个有 $N\times K$ 个节点的树，问能否把它分成 $K$ 条链，每条有 $N$ 个节点。

# $\mathbf{0x02}$ 转

考虑一个以 $u$ 为根的子树，设 $sz_u=pk+q(p,q\in\mathbb N,q<k)$ 表示这个子树的大小。初始化每个叶子节点大小为 $1$。显然，如果 $q=0$，则在这个子树中是可以完成配对的。

$\mathbf{Q:}$ 如果 $q\neq0$ 呢？

$\mathbf{A:}$ 如果 $q\neq0$，那么说明在这个子树中会多出一些节点不能配对。这些节点应该尽可能地靠近子树的根节点（以便于和上面的节点重新配对），记以 $u$ 为根的子树中这些不能配对的点的数量为 $dp_u=q$。

$\mathbf{Q:}$ 什么情况下无解？

$\mathbf{A:}$ 考虑在某个根节点 $u$ 下有一些子树 $t_1,t_2\cdots t_n$，其中满足 $dp_i\neq0$ 的点有 $m$ 个。

- 如果 $m=0$，则代表这些子树全部匹配完成，此时 $dp_u=1$（之所以不是 $0$ 是因为还有这个点本身）；
- 如果 $m=1$，则代表有一个子树 $t_x$ 没有匹配完成，此时 $dp_u=dp_x+1$；
- 如果 $m=2$，则代表有两个子树 $t_x,t_y$ 没有匹配完成，此时如果想再凑出一条链，则必须是一条从 $t_x$ 出发，经过根节点到达 $t_y$ 的，长度为 $dp_x+dp_y+1$ 的链。如果发现 $dp_x+dp_y+1\neq k$，则无论如何也凑不出一条链，无解。
- 如果 $m\geq3$，永远无法找到一条链使其经过根节点和三个子树上面部分，无解。

# $\mathbf{0x03}$ 合


```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,k;
string ans[]={"Yes","No"};
vector<ll>e[200005],dp;
bool f=0;
void dfs(ll u,ll fa){
	ll mx=0,mn=LLONG_MAX,c=0;
	for(auto v:e[u]){
		if(v==fa)continue;
		dfs(v,u);
		if(dp[v]!=k)c++,mx=max(dp[v],mx),mn=min(dp[v],mn);
	}
	if(c==0)dp[u]=1;
	else if(c==1)dp[u]=mx+1;
	else if(c==2){
		if(mx+mn+1==k){
			dp[u]=k;
		}else{
			f=1;
			return;
		}
	}else{
		f=1;
		return;
	}
	
}
int main(){
	cin>>n>>k;
	for(ll i=1,u,v;i<=n*k-1;i++){
		cin>>u>>v;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	dp.resize(n*k+1);
	dfs(1,0);
	cout<<ans[f];
}

```

---

## 作者：q_hacker_p (赞：1)

## 分析题目
首先对于一个以 $x$ 为根的子树，因为 $x$ 只有一个，所以从任意一点向上走的路径只能有一条。那么我们对他的子树节点数量进行分类讨论。设 $r_u$ 为以 $1$ 为根的子树 $u$ 中，剩余未匹配的点的个数。
## 分类讨论
* $r_u > k$\
  此时说明下面的点不能进行匹配，而加上点 $u$，不会影响匹配的成功与否，所以此时肯定不能进行匹配。
* $r_u = k$\
  此时由于只能从下往上走并从上往下走，所以最多经过两个未全部匹配子节点。
* $r_u < k$\
  此时只能有一个未全部匹配子节点，因为他需要再继续往上找点，所以只能经过一个子节点。
## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
ll n, k;
vector <ll> adj[200002];
ll siz[200002];
void dfs(ll u, ll fa)
{
	ll cnt = 0;
	for(ll it:adj[u])
	{
		if(it == fa)
			continue;
		dfs(it, u);
		siz[u] += siz[it];
		cnt += siz[it] > 0;
	}
	if(siz[u] > k || (siz[u] == k && cnt >= 3) || (siz[u] < k && cnt >= 2))
	{
		cout << "No";
		exit(0);
	}
	if(siz[u] == k)
		siz[u] = 0;
	return ;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);     cout.tie(0);
	cin >> n >> k;
	for(int i = 1; i < n * k; i++)
	{
		siz[i + 1] = 1;
		ll u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	siz[1] = 1;
	dfs(1, 0);
	cout << "Yes";
	return 0;
}
```

---

## 作者：wmrqwq (赞：1)

这是一篇视频题解。

![](bilibili:BV12EQDYWEFU?t=640)

[参考代码](https://atcoder.jp/contests/abc397/submissions/63816450)

---

## 作者：_zhangcx (赞：1)

# 题解：[E - Path Decomposition of a Tree](https://atcoder.jp/contests/abc397/tasks/abc397_e)

注：赛时太紧张，把树边建成有向边后挂了，大家千万注意别犯唐氏错误。

题意就是能不能把给定的一棵树划分成 $N$ 条长度为 $K$ 的链。考虑树形 DP，在以 $u$ 为根节点的子树中，划分任意条长度为 $K$ 的链后剩余一条以 $u$ 开头的链，我们设这条链的长度为 $f_u$。

显然，若一个节点 $u$ 的 $f_u=0$，则这个子树可以被划分成恰好任意条长度为 $K$ 的链，简称**完全划分**，否则称剩余的以根节点为开头的链为**剩余链**。

首先是边界情况：叶子节点 $u$ 的 $f_u=1$。

对于一个非叶子节点 $u$，分类讨论：

* 如果 $u$ 的所有儿子 $v$ 的子树都是被完全划分的，则 $u$ 的子树划分后只会剩下 $u$ 这个点，所以 $f_u=1$；
* 如果 $u$ 的所有儿子 $v$ 的子树有且只有一个不能被完全划分的，设它为 $v_1$，则 $u$ 的子树划分后只会剩下 $u$ 这个点和 $v$ 的子树的剩余链，把这两部分并成一条链，所以 $f_u=f_{v_1}+1$；
* 如果 $u$ 的所有儿子 $v$ 的子树有且只有两个不能被完全划分的，分别设它为 $v_1$ 和 $v_2$，则 $u$ 的子树划分后只会剩下 $u$ 这个点和 $v_1$ 的子树、$v_2$ 的子树的两条剩余链，所以 $f_u=f_{v_1}+f_{v_2}+1$。如果转移后 $f_u>K$ 的话则说明没有合法的划分方案；
* 如果 $u$ 的所有儿子 $v$ 的子树有多于两个被完全划分的，则 $u$ 与这些剩余链构成一棵树，说明没有合法的划分方案。

转移后容易证明 $f_{root}=0$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
int n, k;
vector<int> G[N];
int f[N];
void dfs(int ufa, int u) {
    if (G[u].empty()) return void(f[u] = 1 % k);
    for (int v : G[u]) if (v != ufa) dfs(u, v);
    set<int> s; // s记录其子树不能被完全划分的儿子v
    for (int v : G[u]) if (v != ufa) if (f[v]) s.insert(v);
    if (s.empty()) f[u] = 1 % k;
    else if (s.size() == 1) f[u] = (f[*s.begin()] + 1) % k;
    else if (s.size() == 2) {
        if (f[*s.begin()] + f[*next(s.begin())] + 1 == k) f[u] = 0;
        else cout << "No", exit(0);
    } else cout << "No", exit(0);
}
int main() {
    ios::sync_with_stdio(false), cin.tie(0);
    cin >> n >> k;
    for (int i = 1; i < n * k; i++) {
        int u, v;
        cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    dfs(0, 1);
    cout << "Yes";
    return 0;
}
```

[AC记录。](https://atcoder.jp/contests/abc397/submissions/63884530)

---

## 作者：Dream_poetry (赞：1)

### 思路：

我们考虑感性 dfs。

首先跑第一次 dfs，求出每个点的子树大小，以及它子树中叶子节点个数。

第二次直接跑 dfs，往下处理完之后，考虑如下情况：

1. $siz_x=q,vis_x \le 2$，此时显然这一部分直接构成了一条符合条件的路径，我们把这一部分从原树中删去。

2. $siz_x=q,vis_x>2$，此时由于叶子结点数目大于 $2$，显然无法构成一条路径，输出 ```-1```。

3. $siz_x<q$，此时显然数目不够，跳过即可。

4. $siz_x>q$，此时显然这个节点以下部分也无法构成合法路径了，输出 ```-1```。

对于合法情况，我们要及时更新 $siz$ 和 $vis$ 的值。

### 代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,q;
struct node{
	int nex,to;
}e[5000005];
int tot;
int he[5000005];

inline void add(int x,int y){
	e[++tot].nex=he[x];
	e[tot].to=y;
	he[x]=tot;
}
int siz[1000005];

int vis[1000005];


inline void dfs(int x,int fa){
	siz[x]=1;
	for (int i=he[x];i;i=e[i].nex){
		int v=e[i].to;
		if (v==fa) continue;
		dfs(v,x);
		vis[x]+=vis[v]; 
		siz[x]+=siz[v];
	}
	if (siz[x]==1){
		vis[x]=1;
	}
}



inline void DFS(int x,int fa){
	for (int i=he[x];i;i=e[i].nex){
		int v=e[i].to;
		if (v==fa) continue;
		siz[x]-=siz[v];
		vis[x]-=vis[v];
		DFS(v,x);
		siz[x]+=siz[v];
		vis[x]+=vis[v];
	}
	if (siz[x]==q && vis[x]<=2){
		siz[x]=0;
		vis[x]=0;
	}
	else if (siz[x]==q && vis[x]>2 || siz[x]>q){
		cout<<"No";
		exit(0);
	}
	if (siz[x]==1){
		vis[x]=1;
	}
}

signed main(){
	cin>>n>>q;
	for (int i=1;i<n*q;i++){
		int x,y;
		cin>>x>>y;
		add(x,y);
		add(y,x);
	}	
	dfs(1,0);
	DFS(1,0);
	cout<<"Yes";
	return 0;
}


/*
2 4
1 2
2 3
3 4
2 5
3 6
3 7
1 8
*/
```

---

## 作者：HasNoName (赞：0)

### 思路
显然，一棵树如果合法的话，它的叶子节点一定是能在一条链上。

所以从下向上树形动态规划。

如果一个子树不能全部划分完，则记录为有用的子树。

如果一个节点有用的子树个数大于 $2$，则一定不合法，无解。

否则如果子树个数为 $0$，则返回多余一个节点。

如果子树个数为为 $1$，则返回个数加一对 $k$ 去模。

如果个数为 $2$，那么要么无解，要么返回 $0$。如果子树个数之和为 $k-1$，则有解，否则一定无解。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=300005;
typedef long long ll;
struct T
{
	int ne,to;
}e[2*N];
int he[N],idx,n,k;
void add(int x,int y)
{
	e[++idx].ne=he[x];
	e[idx].to=y;
	he[x]=idx;
}
int dfs(int x,int fa)
{
	vector<int>v;
	for(int i=he[x];i;i=e[i].ne)
	{
		int y=e[i].to;
		if(y==fa)continue;
		int t=dfs(y,x);
		if(t==0)continue;
		v.push_back(t);
	}
	if(v.size()==0)return 1%k;//一定要mod k!调了作者40分钟+8次罚时
	if(v.size()==1)return (v[0]+1)%k;
	if(v.size()>2)
	{
		cout<<"No\n";
		exit(0);
	}
	if((v[0]+v[1]+1)%k!=0)
	{
		cout<<"No\n";
		exit(0);
	}
	return 0;
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>k;
	for(int i=1;i<n*k;i++)
	{
		int x,y;
		cin>>x>>y;
		add(x,y);
		add(y,x);
	}
	dfs(1,0);
	cout<<"Yes\n";
	return 0;
}
```

---

## 作者：_ayaka_ (赞：0)

### 思路

首先明确我们的目标，在一个树上尝试找到 $n$ 个长度为 $k$ 的链。显然突破点在于确定链尾与链首，以及我们没有必要去统计目前有多少条找到的链，因为图上有 $nk$ 个点，意味着我们如果找到一种把所有点整成长度为 $k$ 的链的方案，那链必定有 $n$ 条。

一个显然的思路，叶节点一定是某一条链的开头，那么先考虑图是一条链的情况，新建一个变量 $p_i$ 表示 $i$ 这个点所在的链目前有多少个点。显然只要从叶节点往上搜，每往上搜一个就把 $p_i$ 设定为自己的儿子 $+1$，搜到了 $p_i=k$ 就清空，最后看在链首的 $p_1$ 是不是等于 $0$ 就行了。

那在树上呢？树上的区别仅是可能一个点有多个儿子。那其实也很好处理，如果自己的儿子的 $p$ 就是 $0$，那说明这个儿子本身就是一条链的顶点，不管它就行了。如果不等于 $k$，那说明这条链要连接当前这个点。可以记录这样的链的长度，第一个记录为 $l_1$，第二个为 $l_2$，然后分情况讨论：

- 如果 $l_1=0$ 并且 $l_2=0$，说明当前点是一个新的链尾。
- 如果 $l_1\neq 0$ 并且 $l_2=0$，说明当前点应该是 $l_1$ 这条链上的。
- 如果 $l_1\neq 0$ 并且 $l_2\neq 0$，说明当前点是连接 $l_1$ 与 $l_2$ 的中转点，判定 $l_1+l_2+1=k$，成立则合法，此点为中转点。否则此树不合法。
- 如果儿子中 $\neq 0$ 的链不止 $2$ 条，显然不合法，因为当前点至多只能连接两条链。

然后就讨论完了，具体看代码，时间复杂度 $O(n)$。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int unsigned long long
int n, k, x, y;
vector<int> e[1000005];
int dfs(int u, int fa) {
	int l1 = 0, l2 = 0;
	for (auto v : e[u]) {
		if (v == fa) continue;
		int p = dfs(v, u);
		if (p == -1) return -1;
		if (l1) {
			if (l2) return -1;
			l2 = p;
		} else l1 = p;
	}
	if (l1 && l2 && l1 + l2 + 1 != k) return -1;
	return (l1 + l2 + 1) % k;
}
signed main() {
	cin >> n >> k;
	for (int i = 1; i < n * k; i++) {
		cin >> x >> y;
		e[x].push_back(y);
		e[y].push_back(x);
	}
	int ans = dfs(1, 0);
	if (ans != 0) cout << "No";
	else cout << "Yes";
	return 0;
}
```

---

## 作者：Dtw_ (赞：0)

## 题意
给你一颗树，有 $n\times k$ 个点，问你能否拆成 $n$ 条长为 $k$ 的链。
## Solution
赛时被 D 卡到最后 10 分钟，猜了个以重心为根然后从子树往上合并，没写完。事实上哪个为根都无所谓。

考虑长为 $k$ 的路径，要么就是往上连，要么就是两条链合并起来。

那么记录一个 $d_u$ 表示 $u$ 点目前的路径长度，那么如果父亲的还没被合并过，或者当前这个点的链和父亲那个链合并起来正好是 $k$ 那就可以合并上去。否则就不行了。

## Code
```cpp
#include <bits/stdc++.h>

using namespace std;

#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

const int N = 2e5 + 10, inf = 0x3f3f3f3f;

int n, k, d[N];
vector<int> e[N];
bool f = 1;

void dfs(int u, int fa)
{
    for (auto v : e[u]) if (v != fa) dfs(v, u);
    if (d[u] == k) return;
    if (d[fa] == 1 || d[fa] + d[u] == k) d[fa] += d[u];
    else f = 0;
}

int main()
{
    fst
    cin >> n >> k;
    for (int i = 1; i <= n * k; i++) d[i] = 1;
    for (int i = 1; i < n * k; i++)
    {
        int u, v; cin >> u >> v;
        e[u].push_back(v), e[v].push_back(u);
    }
    if (k == 1) { cout << "Yes"; return 0; }
    dfs(1, 0);
    if (f) cout << "Yes";
    else cout << "No";
    return 0;
}
```

---

## 作者：2023lpx (赞：0)

# AT_abc397_e [ABC397E] Path Decomposition of a Tree 题解

## 题目大意

给出一棵树，问你是否存在一种方法将这棵树分割成 $n$ 条长为 $k$ 的链。

## 思路

既然给出的是一棵树，又要求能分割出 $n$ 条链，不难想到：

- 一个点只能和最多两个儿子组成一条链。
  
- 如果一个点和两个儿子组成一条链，则长度必须为 $k$，否则必定不合法。
  

自己画图理解一下。

直接跑一边树就好了。

## code

[link](https://atcoder.jp/contests/abc397/submissions/63813515)

---

## 作者：zhangbo1000 (赞：0)

大分类讨论题。

设 $need_i$ 表示若使 $i$ 号结点合法，还需要在上方链接多少个结点与 $i$ 同一条链，然后 dfs 判断，对于结点 $u$，合法的链有两种情况：

- 从 $u$ 的祖先结点（包括 $u$）伸展到 $u$（继续往下走）。
- 从 $u$ 的一颗子树途径 $u$ 走到另一颗子树。

由此产生几种决策方案：

- 若 $u$ 有且只有一个子结点 $v$ 满足 $need_v>0$，那么 $u$ 需要和它同一条链，故 $need_u=need_v-1$。
- 若 $u$ 有且只有两个子结点 $v_1,v_2$ 满足 $need_{v_1}>0,need_{v_2}$，那么：
  - 若 $k-need_{v_1}+k-need_{v_2}+1=k$，即 $need_{v_1}+need_{v_2}=k+1$，一条链贯穿 $u$，$v_1$ 的子树，$v_2$ 的子树符合条件，置 $need_u=0$。
  - 否则不存在划分方案，报告无解。
- 若 $u$ 的所有子结点 $v$ 满足 $need_v=0$，或者 $u$ 没有子节点，那么 $u$ 只能作为一条链的结尾，$need_u=k-1$。

dfs 结束后，如果所有节点都没有报告无解**且根节点 $m$ 满足 $need_m=0$**，那么有解，否则无解。

[代码和评测记录。](https://atcoder.jp/contests/abc397/submissions/63800855)

---

## 作者：Statax (赞：0)

## 前言

~~马币~~ E 题吃 10 发罚时最后发现题看错了…

## 思路

我们把每得到一个路径看成从树中删去，那么易得一定要从叶子节点开删，且能删则删。

无解的情况有两种：（记以 $x$ 为根的子树大小为 $sz[x]$。）

- $sz[x] > m$。
- 以 $x$ 为根的子树中，没有长度为 $sz[x]$ 的简单路径。

注意，此时此刻的子树是有可能被删了一些节点的。

还是比较好理解的，只是因为作者语文太差了，建议看代码理解。

## 代码

时间复杂度 $O(n)$。

```cpp
void dfs (int u, int fa) {
    sz[u] = 1;
    for (const auto & v : g[u]) {
        if (v == fa) 
            continue;
        dfs (v, u);
        if (sz[v]) 
            deg[u] += deg[v];
        sz[u] += sz[v];
    }
    if (!deg[u]) deg[u] = 1;
    if (sz[u] > m || deg[u] > 2)
        puts ("No"), exit (0);
    if (sz[u] == m) 
        sz[u] = 0;   
}
```

---

## 作者：FreedomKing (赞：0)

### 思路

题目给出的是树，考虑对树上的点分类：

- 叶子结点，一定是要作为某条链的某个端点的；

- 度为 2 的节点，即位于链上的点；

- 度为 3 的节点，**可能**链接两条合法的链的点；

- 度大于 3 的节点，如果存在，显然出现了两条链相交的情况，无法将这个节点分给两者中任何一条，直接输出无解，下文默认不存在这类节点，不再讨论。

然后 dfs 就行了，对每个节点开一个计数器 $cnt_i$ 表示它所处的链已有多少个节点，从叶子结点也就是可以确定的链的端点从下往上回溯，对于父节点 $u$ 和其具有先后顺序的子节点 $v_1,v_2$，有以下情况：

- 若 $v_1$ 存在

  - 若 $v_2$ 不存在，也就是 $u$ 只有一个子节点，那么它们要么处于同一条链上，要么 $u$ 就是新链的端点之一，可以更新 $cnt_u=(cnt_{v_1}+1)\bmod k$。

  - 若 $v_2$ 存在，则 $v_1,v_2,u$ 只能在同一链上，需验证 $cnt_{v_1}+cnt_{v_2}+1=k$ 是否成立，成立就更新 $cnt_u=0$，否则无解。
 
- 若 $v_1$ 不存在，那么 $u$ 就是叶子节点。

### AC Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5;
inline int qread(){
#define qr qread()
	int x=0,t=1,ch=getchar();
	while(ch<'0'||ch>'9'){
		t^=(ch=='-');
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=(x<<3)+(x<<1)+ch-'0';
		ch=getchar();
	}
	return (t?x:-x);
}
inline void qwrite(int x){
#define qw(_) qwrite(_)
#define qws(_) qw(_),putchar(' ')
#define qwe(_) qw(_),putchar('\n')
	if(x<0) x=-x,putchar('-');
	if(x>9) qw(x/10);
	putchar(x%10+'0');
	return;
}
inline int qpow(int x,int p,int mod){
	mod=(mod?mod:LONG_LONG_MAX);
	x=(p?x:1);
	int t=1;
	while(p>1){
		if(p&1) t=(t*x)%mod;
		x=(x*x)%mod;
		p>>=1;
	}
	return (x*t)%mod;
}
int cnt[N],k;
vector<int>e[N];
inline void dfs(int u,int fa){
	int tmp1=0,tmp2=0;
	for(int i=0;i<e[u].size();i++){
		int v=e[u][i];
		if(v==fa) continue;
		dfs(v,u);
		if(cnt[v]){
			if(tmp1==0) tmp1=cnt[v];
			else if(tmp2==0) tmp2=cnt[v];
			else{
				puts("No");
				exit(0);
			}
		}
	}
	cnt[u]=(1+tmp1)%k;
	if(tmp2!=0){
		cnt[u]=(cnt[u]+tmp2)%k;
		if(cnt[u]!=0){
			puts("No");
			exit(0);
		}
	}
	return;
}
signed main(){
	int n=qr;k=qr;
	for(int i=2;i<=n*k;i++){
		int u=qr,v=qr;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	dfs(1,0);
	puts("Yes");
	return 0;
}
```

---

## 作者：chenzhiyou2009 (赞：0)

题意就是给你一颗有 $n \times k$ 个结点的树，问你能不能把这棵树切成 $n$ 个长度为 $k$ 的路径。

我们先手玩一下样例，然后就差不多会了，观察到以下两件事：

- 将任意结点钦定为根不影响最终的答案。
- 按照这种策略删一定最优：如果有一个子树是一个长为 $k$ 的路径，那么删掉。

注意每次删除的是一颗子树，所以可以使用类似树形 DP 想法，分类讨论一下即可。

可以删掉的情况：这个子树的根是长为 $k$ 的路径上的一点。因为要是路径，所以必须保证这个子树的根的子树是链，且最多有两个子树。

无解的情况：不可以删，且上传给父亲的时候不是一条链。也就是说不能删，且这个子树的根有一个以上的子树。

否则我们可以不动这个子树，然后传递给它的父亲。

具体实现见代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

#define For(i, j, k) for (int i = j; i <= k; ++ i)
#define Rof(i, j, k) for (int i = j; i >= k; -- i)
#define ll long long
#define db double
#define vi vector<int>
#define pb push_back
#define pii pair<int, int>
#define mkp make_pair

const int N = 2e5 + 10;

int n, k, m;
vi g[N];
bool st[N] = {false};
int siz[N], deg[N];

void dfs(int now, int fa) {
    siz[now] = 1;
    for (auto v : g[now]) {
        if (v == fa) {
            continue;
        }
        dfs(v, now);
        if (!st[v]) {
            siz[now] += siz[v];
            deg[now] ++ ;
        }
    }
    if (siz[now] == k && deg[now] <= 2) {
        st[now] = true;
    }
    else if (deg[now] > 1) {
        cout << "No\n";
        exit(0);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    cin >> n >> k;
    For (i, 1, n * k - 1) {
        int u, v;
        cin >> u >> v;
        g[u].pb(v), g[v].pb(u);
    }

    dfs(1, 0);
    cout << "Yes\n";

    return 0;
}
```

评级建议下位绿。

---

## 作者：cyq32ent (赞：0)

题意：将树分为长度为 $K$ 的 $N$ 条链是否可行。

考虑自底至上延伸链。对于叶子节点，初始化一条长度为 $1$ 的链。对于非叶子节点：考虑这个节点的儿子。如果某个儿子所在的链的长度已经达到了 $K$，就无需再管它。只考虑其余的（链长度小于 $K$ 的）儿子节点。如果没有其余的儿子节点，这个节点就相当于一个叶子节点。如果只有一个儿子节点，那么这个节点就只能延续儿子节点的链。如果有两个儿子节点，那么这两个儿子所在的链的长度之和一定要等于 $K-1$，因为此时唯一一种延伸链的方法是把两条链同父节点合并，否则在这里无解。如果还剩下三个或更多儿子节点，那么一定无解，因为父节点不可能出现在多条链中。代码就很简单了：

```cpp
#include<bits/stdc++.h>
using namespace std;
int N,K;
vector<int>G[202503];
int dfs(int u,int p){
	if(G[u].size()==2&&u!=1){
		for(auto v:G[u])if(v!=p)return (dfs(v,u)+1)%K;
	}if(G[u].size()<=1&&u!=1)return 1;
	vector<int>cd;
	for(auto v:G[u]){
		if(v!=p){
			int d=dfs(v,u);
			if(d%K)cd.push_back(d);
		}
	}
	//cout<<u<<' '<<cd.size()<<endl;
	if(cd.size()==0)return 1;
	else if(cd.size()==1)return (cd[0]+1)%K;
	else if(cd.size()==2&&cd[0]+cd[1]==K-1)return 0;
	else cout<<"No",exit(0);
}
int main(){
	cin>>N>>K;
	for(int i=1,u,v;i<N*K;i++)cin>>u>>v,G[u].push_back(v),G[v].push_back(u);
	dfs(1,0);
	cout<<"Yes";
	return 0;
}
```

---

## 作者：SunsetVoice (赞：0)

比 D 简单。披着动归外壳的分讨贪心。

考虑一条路径和根的关系。设 $dp_i$ 表示到了当前点已经匹配了几个。

设 $sum$ 为 $dp_v$ 非零个数（$v$ 为 $u$ 子节点）

- $sum=0$ 此时子节点全部匹配完，相当于 $u$ 为叶子节点。$dp_u=1$。
- $sum=1$ 此时相当于 $u$ 为非零值向上的路径中的一个点，$dp_u=(v1+1)$，如果匹配完（$dp_u=k$）设置成 $0$。
- $sum=2$ 此时路径必须是从一个非零值向上到 $u$ 在向另一个节点拐，需保证这条路长度是 $k$（$v1+v2+1=k$）否则必然无解。$dp_u=0$。
- $sum>2$ 必然无解，路径上的点度小于 $3$。

就做完了，要特判 $k=1$。


```cpp
#include<bits/stdc++.h>
#define int long long
#define endl "\n"
using namespace std;
int n,k,dp[500001] = {0},fl = 0;
vector<int>e[500001]; 
void dfs(int x,int fa){
	int v1 = -1,v2 = -1,ma = 0;
	for(int v:e[x]){
		if(v==fa)continue;
		dfs(v,x);
		if(fl==1)return;
		if(dp[v]!=0){
			if(v1==-1)v1 = dp[v];
			else if(v2==-1)v2 = dp[v];
			else{
				cout<<"No"<<endl;
				fl = 1;
				return;
			}
			ma = max(ma,dp[v]);
		}
	}
//	cout<<x<<" "<<v1<<" "<<v2<<endl;
	if(v2==-1){
		if(v1==-1)dp[x] = 1;
		else dp[x] = (v1+1)%k;
	}else{
		if(v1+v2+1!=k){
			cout<<"No"<<endl;
			fl = 1;
			return;
		}
	}
	
	
	return;
}
signed main(){
	cin.tie();
	cout.tie();
	cin>>n>>k;
	n*=k;
	for(int i = 1;i<n;i++){
		int u,v;
		cin>>u>>v;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	if(k==1){
		cout<<"Yes"<<endl;
		return 0;
	}
	dfs(1,-1);
	if(fl==0){
		cout<<"Yes"<<endl;
	}
	return 0;
}/*
3 1
1 2
2 3
*/

```

---

