# [ABC354G] Select Strings

## 题目描述

有 $N$ 个仅由小写英文字母组成的字符串 $S_1,S_2,\ldots,S_N$，以及 $N$ 个正整数 $A_1,A_2,\ldots,A_N$。

对于集合 $\lbrace 1,2,\ldots,N \rbrace$ 的某个子集 $T$，如果对于任意 $i,j \in T$ 且 $i \neq j$，都不存在 $S_i$ 是 $S_j$ 的子串的情况，则称 $T$ 为**好集合**。

请你选择一个好集合 $T$，使得 $\displaystyle\sum_{i\in T}A_i$ 的值最大，并输出这个最大值。

子串的定义：字符串 $S$ 的**子串**是指通过从 $S$ 的开头删除 $0$ 个或多个字符、从结尾删除 $0$ 个或多个字符后得到的字符串。例如，`ab` 是 `abc` 的子串，但 `ac` 不是 `abc` 的子串。

## 说明/提示

## 限制条件

- $1 \leq N \leq 100$
- $S_i$ 由小写英文字母组成
- $1 \leq |S_i|$
- $|S_1|+|S_2|+\ldots+|S_N| \leq 5000$
- $1 \leq A_i \leq 10^9$

## 样例解释 1

作为好集合的 $T$ 及其对应的 $\displaystyle\sum_{i\in T}A_i$ 如下：

- 当 $T = \lbrace 1 \rbrace$ 时，$\displaystyle\sum_{i\in T}A_i = 5$
- 当 $T = \lbrace 2 \rbrace$ 时，$\displaystyle\sum_{i\in T}A_i = 2$
- 当 $T = \lbrace 3 \rbrace$ 时，$\displaystyle\sum_{i\in T}A_i = 3$
- 当 $T = \lbrace 4 \rbrace$ 时，$\displaystyle\sum_{i\in T}A_i = 4$
- 当 $T = \lbrace 2,3 \rbrace$ 时，$\displaystyle\sum_{i\in T}A_i = 5$
- 当 $T = \lbrace 2,4 \rbrace$ 时，$\displaystyle\sum_{i\in T}A_i = 6$

其中最大值为 $6$，因此输出 $6$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4
atcoder
at
coder
code
5 2 3 4```

### 输出

```
6```

## 样例 #2

### 输入

```
10
abcd
abc
ab
a
b
c
d
ab
bc
cd
100 10 50 30 60 90 80 70 40 20```

### 输出

```
260```

# 题解

## 作者：王华 (赞：6)

首先注意到 $n$ 和 $\sum|s_i|$ 都是非常小的，我们可以直接暴力确认字符串之间的关系，这里完全可以加强。

这种关系连成一张 DAG，并且是一个传递闭包，首先考虑   dp，但转移顺序如果按照传统的拓扑序转移，很难设计出合适的状态，如果从状态设计出发，简单的状态一般会有后效性，因此难以用 dp 解决。

 dp 失败的思路启发我们用一种能够最优地进行全局抉择的算法，结合小数据范围，这启示可以用网络流解决该问题。

本题实质上是在求一个传递闭包的最大权反链，有一个严格弱化版的题目是《祭祀》，可以先去了解一下这道题。

根据 Dilworth 定理，偏序集的最长反链等于最小链覆盖，但因为这里是一个完全偏序集(即传递闭包)，所以这里的最大权反链等于最大权点独立集，接下来的问题是如何求这个最大权点独立集。


带权的点我们难以处理，不妨将初始的点编号为 $1$ 至 $n$，称为有权点，点 $i$ 的点权为 $a_i$ ，将第 $i$ 个点拆成 $a_i$ 个无权点，构成集合 $S_i$。若有权点 $i$  指向有权点 $j$ 时，则对于任意 $x\in S_i \  y\in S_j$，均有 $x$ 指向 $y$。

在新图中，我们可以证明，新图的最长反链=原图的最大权反链。

#### 引理:对于新图中的每个 $S$，要么全选，要么全不选。
反证，如果只选一部分，由于每个集合里的点是等价的，显然能把剩下的都选上。

#### 定理:新图的最长反链=原图的最大权反链。
证明:

首先新图的最长反链一定是不小于原图的最大权反链的，因为对于原图的每一种选法，新图都可以构造一种方法与之相对应。

然后，鉴于引理，可以在原图中构造一种等价方案，将原图的有权点 $i$ 和集合 $S_i$ 相对应，如果 $S_i$ 被全选择，则点 $i$ 也选择，反之同理。


由于新图也满足偏序集的关系，可以用最小链覆盖来求，但点数太多，对于同一侧集合 $S_i$ 的点可以合并，与源汇点的边权也要合并，对这个二分图跑最大流即可。

---

## 作者：Expert_Dream (赞：6)

是一道网络流的题，可以用网络最大流来解决。

我们可以转换一下题面，把字符串看作图上的点，把他们互为子串的条件看作图上的边，边有边权，即为这他们连起来所产生的贡献，即为 $a$ 数组。这样就转换成了网络流中典型的最小路径覆盖问题。有一个定理，那就是最小路径问题等于权值之和减去最大流。

因此我们暴力判断 $i$ 是否是 $j$ 的子串并且按照最小路径覆盖问题的模型去连边，最后跑最大流即可。

代码：[link](https://atcoder.jp/contests/abc354/submissions/53649982)。

---

## 作者：FFTotoro (赞：5)

赛时这个一遍过，[全场 rk 28](https://atcoder.jp/contests/abc354/standings?watching=zyc212303)。写题解以纪念。

首先考虑用 KMP 暴力处理出每一对字符串可不可以同时选，如果能选就连边，转换为一般图带权最大独立集问题。

最大独立集可以用求最大团的方法求出（直接随机排列），但是带权的不太好做。于是考虑爬山，先将初始排列按照权值排序，如果这样直接贪心选肯定是错的；但是我们每次循环随机交换其中的 $3$ 对元素，然后判断解是不是比当前解更优，如果是那么更新答案。卡时后可以通过。

放代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
inline bool find(string text,string pattern){
  /* 字符串匹配 KMP 模板，请自行补全 */
}
int st; inline long long wmis(vector<vector<int> > b,vector<int> a){
  int n=a.size();
  for(auto &i:b)for(auto &j:i)j=!j;
  vector<int> p(n),r;
  iota(p.begin(),p.end(),0);
  sort(p.begin(),p.end(),[&](int x,int y){
    return a[x]>a[y];
  }); // 初始排列
  long long w=a[p[0]]; mt19937 g;
  uniform_int_distribution<> u(0,n-1);
  while(r.size()<n&&1.0*(clock()-st)/CLOCKS_PER_SEC<1.98){
    auto q=p;
    for(int i=0;i<3;i++)
      swap(q[u(g)],q[u(g)]);
    vector<int> v; long long c=0;
    for(int i:q){
      bool f=true;
      for(int j:v)f&=b[i][j];
      if(f)v.emplace_back(i),c+=a[i];
    } // 找最大团
    if(c>w)p=q,w=c; // 更新答案
  } // 卡时
  return w;
} // 找最大权独立集
int main(){
  ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  st=clock(); int n; cin>>n;
  vector<string> s(n);
  for(auto &i:s)cin>>i;
  vector b(n,vector<int>(n));
  for(int i=0;i<n;i++)
    for(int j=i+1;j<n;j++)
      if(find(s[i],s[j]))b[i][j]=b[j][i]=true; // 建图
  vector<int> a(n);
  for(auto &i:a)cin>>i;
  cout<<wmis(b,a)<<endl;
  return 0;
}
```

---

## 作者：ケロシ (赞：4)

另一种理解方式。

考虑答案即为 $\sum a_i$ 减去使得符合题目条件的代价，而符合条件就是选出的元素不能有偏序关系。

考虑有偏序关系的对不能共存，考虑**最小割**。对于每个 $i$ 拆成 $st(i)$ 和 $ed(i)$，然后连边 $S \to st(i)$ 和 $ed(i) \to T$，流量均为 $a_i$。然后考虑限制，若 $s_j$ 是 $s_i$ 的字串，则连一条无穷大的边 $st(i) \to ed(j)$，若要求最小割，则必须需要割掉 $S \to st(i)$ 或者 $ed(j) \to T$，这样就能计算代价。 


为什么上述建图不会同时割掉 $S \to st(i)$ 和 $ed(i) \to T$，因为限制是一个偏序集。这里简单证明一下，若 $S \to st(i)$ 和 $ed(i) \to T$ 均被割，则一定存在 $s_i$ 是 $s_k$ 的字串和 $s_j$ 是 $s_i$ 的字串，但是此时 $s_j$ 也是 $s_k$ 的字串，也需要割，上述的割法一定就不优了，所以不回出现 $i$ 对应的两条边都被割。


上述证明是基于满足严格偏序的，需要对字符串去重，然后跑 Dinic 即可。

```cpp
const int N = 1e2 + 5;
const int INF = 1e9 + 7;
const ll LNF = 1e15 + 7;
int n, a[N];
string s[N];
void solve() {
	cin >> n;
	map<string, int> mp;
	FOR(i, 1, n) cin >> s[i];
	FOR(i, 1, n) cin >> a[i];
	FOR(i, 1, n) {
		if(!mp.count(s[i])) mp[s[i]] = a[i];
		else chmax(mp[s[i]], a[i]);
	}
	n = SZ(mp);
	int cnt = 0;
	for(auto h : mp) {
		cnt++;
		s[cnt] = FI(h);
		a[cnt] = SE(h);
	}
	Dinic :: init();
	int S = 0, T = n * 2 + 1;
	ll sum = 0;
	FOR(i, 1, n) {
		sum += a[i];
		Dinic :: add(S, i, a[i]);
		Dinic :: add(i + n, T, a[i]);
	}
	FOR(i, 1, n) FOR(j, 1, n) if(i != j) {
		if(s[i].find(s[j]) != s[i].npos) {
			Dinic :: add(i, j + n, LNF);
		}
	}
	cout << sum - Dinic :: dinic(S, T) << endl;
}

```

---

## 作者：Linge_Zzzz (赞：4)

~~怎么 abc 还出网络流。~~

# 题意简述

给你 $n$ 个字符串 $s_i$，每个字符串有权值 $a_i$，你需要从中选出一些字符串，选出字符串的下标组成一个集合 $S$。

你需要满足对于任意的 $i\in S$，不存在 $j\in S(i\neq j)$ 使得 $s_i$ 是 $s_j$ 的子串。

任务是最大化 $\sum_{i\in S}a_i$。

数据范围：$n\leq 100,\sum |s_i|\leq 5000$。

# 解法

看到奇怪的数据范围没有什么头猪，不妨往一些玄学复杂度的东西上想，如网络流。

建立一个图。对于每个 $s_i,s_j(i<j)$，若 $s_i$ 是 $s_j$ 的子串，则在图上从 $i$ 到 $j$ 连一条有向边，容易知道这是一个 DAG。

现在我们把这个问题转化成了形式化问题：

> 给定一个 DAG，每个点有点权，你需要在 DAG 中选定一些点，使得没有任意两个点在一条链上，最大化权值和。

这个问题可以直接使用网络流解决。

具体地，把每个点 $i$ 拆成左部点 $L(i)$ 和右部点 $R(u)$，然后从 $S$ 向 $L(i)$ 连容量为 $a_i$ 的边，从 $R(i)$ 到 $T$ 连容量为 $a_i$ 的边。

对于原图中每条边 $(u,v)$，从 $L(u)$ 到 $R(v)$ 连容量为 $\inf$ 的边。

让 $\sum_{i=1}^n a_i$ 减去最大流就是答案。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF=0x3f3f3f3f;
const ll INFL=0x3f3f3f3f3f3f3f3f;
namespace mf{
	const int N=1e5+10,M=1e5+10;
	int s,t;
	struct edge{
		int v,nxt;
		ll w;
	}e[M*2];
	int head[N],cnt=2;
	void add(int u,int v,ll w){
		e[cnt].v=v;
		e[cnt].w=w;
		e[cnt].nxt=head[u];
		head[u]=cnt++;
	}
	void addflow(int u,int v,ll w){
		add(u,v,w);
		add(v,u,0);
	}
	int d[N],cur[N];
	bool bfs(){
		memset(d,0,sizeof(d));
		queue<int> q;
		q.push(s);
		d[s]=1,cur[s]=head[s];
		while(q.size()){
			int u=q.front();q.pop();
			for(int i=head[u];i;i=e[i].nxt){
				if(!d[e[i].v]&&e[i].w){
					d[e[i].v]=d[u]+1;
					cur[e[i].v]=head[e[i].v];
					if(e[i].v==t)return 1;
					q.push(e[i].v);
				}
			}
		}
		return 0;
	}
	ll dinic(int u,ll flow){
		if(u==t)return flow;
		ll rm=flow;
		for(int i=cur[u];i&&rm;i=e[i].nxt){
			cur[u]=i;
			if(e[i].w&&d[e[i].v]==d[u]+1){
				ll k=dinic(e[i].v,min(e[i].w,rm));
				if(!k)d[e[i].v]=0;
				rm-=k;
				e[i].w-=k;
				e[i^1].w+=k;
			}
		}
		return flow-rm;
	}
	ll Maxflow(){
		ll ans=0;
		while(bfs())ans+=dinic(s,INFL);
		return ans;
	}
}
const int N=110;
ll n,a[N],sum;
string s[N];
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n;
	mf::s=0,mf::t=n*2+1;
	for(int i=1;i<=n;i++)cin>>s[i];
	for(int i=1;i<=n;i++)cin>>a[i],sum+=a[i];
	for(int i=1;i<=n;i++){
		mf::addflow(mf::s,i,a[i]);
		mf::addflow(i+n,mf::t,a[i]);
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(i==j)continue;
			if(s[i]==s[j]&&i<j)continue;
			if(s[i].find(s[j])!=string::npos){
				mf::addflow(i,j+n,INFL);
			}
		}
	}
	cout<<sum-mf::Maxflow()<<endl;
	return 0;
}
```

---

## 作者：CQ_Bob (赞：4)

## 分析

考虑网络流。

对于 $S$，很容易想到将它们分成两组：被选择的与不被选择的。

对于 $S_i$，如果我们把它选了，那所有除 $i$ 外 $S_j$ 是 $S_i$ 子串的 $j$ 我们都不能选。将 $i$ 与这样的 $j$ 之间建有向边，边权为极大值。

然后就很简单。把 $S$ 与一个源点连边，边权为 $a_i$，再把它们与一个汇点连边，边权为 $a_i$。前者表示如果分到汇点，则需要 $a_i$ 的代价从源点那里不选它；后者表示如果分到汇点，则需要 $a_i$ 的代价从汇点那里不选它。这里的源点**不一定**表示选择的点的集合。

然后我们就需要求出来一种方法，使得断掉一些边之后没有一个与源点联通的点会与一个与汇点联通的点联通。这样就能表示选择的点之间都不存在 $S_i$ 是 $S_j$ 的子串了。

然后这个就是一个最小割，答案为 $\sum a_i - MinCut$。

注：当 $S_i=S_j,i\ne j$ 时，只需要在它们之间建一条边。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define re register
#define il inline
#define pii pair<int,int>
#define x first
#define y second
#define gc getchar()
#define rd read()
#define debug() puts("------------")

namespace yzqwq{
	il int read(){
		int x=0,f=1;char ch=gc;
		while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=gc;}
		while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=gc;
		return x*f;
	}
	il int qmi(int a,int b,int p){
		int ans=1;
		while(b){
			if(b&1) ans=ans*a%p;
			a=a*a%p,b>>=1;
		}
		return ans;
	}
	il auto max(auto a,auto b){return (a>b?a:b);}
	il auto min(auto a,auto b){return (a<b?a:b);}
	il int gcd(int a,int b){
		if(!b) return a;
		return gcd(b,a%b);
	}
	il int lcm(int a,int b){
		return a/gcd(a,b)*b;
	}
	il void exgcd(int a,int b,int &x,int &y){
		if(!b) return x=1,y=0,void(0);
		exgcd(b,a%b,x,y);
		int t=x;
		x=y,y=t-a/b*x;
		return ;
	}
	mt19937 rnd(time(0));
}
using namespace yzqwq;

const int N=8e6+10;
int a[N],n,s,t; 
string str[N];
int ne[N<<1],e[N<<1],w[N<<1],h[N],h2[N],idx=1;
int dep[N],vis[N];
int sum,ans,Max;

il void add(int a,int b,int c){
	ne[++idx]=h[a],e[idx]=b,w[idx]=c,h[a]=idx;
	ne[++idx]=h[b],e[idx]=a,w[idx]=0,h[b]=idx;
}
il bool bfs(){
	for(re int i=s;i<=t;++i)
		h2[i]=h[i],
		dep[i]=1e18,vis[i]=0;
	queue<int> qu;
	qu.push(s),dep[s]=0,vis[s]=1;
	while(!qu.empty()){
		int now=qu.front();qu.pop();
		for(re int i=h[now];i;i=ne[i]){
			int j=e[i];
			if(dep[j]>dep[now]+1&&w[i]){
				dep[j]=dep[now]+1;
				if(!vis[j]) vis[j]=1,qu.push(j);
			}
		}
	}
	if(dep[t]<1e18) return 1;
	return 0;
}
il int dfs(int now,int Min){
	if(now==t) return ans+=Min,Min;
	int use=0;
	for(re int i=h2[now];i;i=ne[i]){
		int j=e[i];h2[now]=i;
		if(dep[j]==dep[now]+1&&w[i]){
			int use_=dfs(j,min(Min-use,w[i]));
			if(use_<=0) continue;
			use+=use_;
			w[i]-=use_,w[i^1]+=use_;
			if(use==Min) return use;
		}
	}
	return use;
}
il void dinic(){
	while(bfs()) dfs(s,1e18);
	return ;
}

il void solve(){
	n=rd,s=0,t=1e6+1;
	for(re int i=1;i<=n;++i) cin>>str[i];
	for(re int i=1;i<=n;++i) a[i]=rd,sum+=a[i],Max=max(Max,a[i]);
	for(re int i=1;i<=n;++i)
	for(re int j=1;j<=n;++j){
		if(i==j) continue;
		if(str[i]==str[j]&&i>j) continue;
		int idx=str[j].find(str[i]);
		if(idx!=string::npos) add(i,n+j,1e18);
	}
	for(re int i=1;i<=n;++i)
		add(s,i,a[i]),add(i+n,t,a[i]);
	dinic();
	printf("%lld\n",sum-ans);
	return ;
}

signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	int t=1;while(t--)
	solve();
	return 0;
}

```

---

## 作者：Filberte (赞：0)

若 $S_j$ 是 $S_i$ 的子串，则从 $i$ 向 $j$ 连一条边，那么最终会构成一个偏序集，要求偏序集上带权最大反链。

这类“每个点都贡献，某些点之间相互矛盾”的问题，考虑最小割建图。每个点拆成 $x_i$ 和 $y_i$ ，$\forall i\in[1,n]$，连 $s \rightarrow x_i$ 和 $y_i \rightarrow t$，边权均为 $a_i$。对于偏序集中一条边 $u \rightarrow v$，连 $x_u\rightarrow y_v$，边权为 $+\infin$，来构造矛盾关系，使得$s \rightarrow x_u$ 和 $y_v \rightarrow t$ 这两条边至少被割掉一条，最终用总权值和减掉最小割就是答案。

补充一个证明：不存在 $s \rightarrow x_u$ 与 $y_v \rightarrow t$ 同时被割的情况。若 $s \rightarrow x_u$ 被割说明某一个 $S_i$ 是 $S_u$ 的子串且没割 $y_i \rightarrow t$，而 $y_u \rightarrow t$ 说明 $s_u$ 是某一个 $S_j$ 的子串且没割 $s \rightarrow x_j$，但 $S_i$ 是 $S_j$ 的子串，所以这两条保留的边至少割掉一条，此时割去与之对应 $u$ 有关的边是多余的，只会让最小割更大，因此不存在前文所述情况。

```c++
#include <bits/stdc++.h>
using namespace std;
namespace MF{
    #define int_64 long long
    static const int maxn = 2e5;
    static const int maxm = 1e5;
    const int_64 Mxf = 1e18;
    struct E{int to, nxt;int_64 f;}e[maxm];
    int hd[maxn], cur[maxn], _te = 1;
    void add_edge(int u, int v, int_64 w){
        e[++_te] = {v, hd[u], w};hd[u] = _te;  
        e[++_te] = {u, hd[v], 0};hd[v] = _te;
    }
    int nods, s, t;
    int_64 maxf = 0;
    int d[maxn];
    bool bfs(){
        for(int i = 0;i <= nods;i++) d[i] = 0, cur[i] = hd[i];
        queue<int> q;q.push(s);d[s] = 1;
        while(!q.empty()){
            int u = q.front();q.pop();
            for(int i = hd[u];i;i = e[i].nxt){
                int v = e[i].to;
                if(e[i].f && !d[v]){
                    d[v] = d[u] + 1;
                    q.push(v);
                    if(v == t) return 1;
                }
            }
        }
        return 0;
    }
    int_64 dfs(int u, int_64 flow){
        if(u == t) return flow;
        int_64 sum = 0;
        for(int &i = cur[u];i;i = e[i].nxt){
            int v = e[i].to;
            if(e[i].f && d[v] == d[u] + 1){
                int_64 gt = dfs(v, min(e[i].f, flow));
                e[i].f -= gt, e[i ^ 1].f += gt;
                sum += gt, flow -= gt;
            }
        }
        if(!sum) d[u] = 0;
        return sum;
    }
    void dinic(){
        while(bfs()) maxf += dfs(s, Mxf);
    }
}
using namespace MF;
const int N = 1e5;
int n;
map<string, int> vis;
string ts[N], str[N];int tv[N], val[N], cnt;
int main(){
    cin >> n;
    for(int i = 1;i <= n;i++)
        cin >> ts[i];
    for(int i = 1;i <= n;i++)
        cin >> tv[i];
    for(int i = 1;i <= n;i++){
        cin >> ts[i] >> tv[i];
        if(!vis.count(ts[i])) vis[ts[i]] = tv[i];
        else if(tv[i] > vis[ts[i]]) vis[ts[i]] = tv[i];
    }
    n = 0;
    for(auto [ns, nv] : vis) str[++n] = ns, val[n] = nv;
    s = 0, t = 2 * n + 1, nods = 2 * n + 1;
    int_64 Sum = 0;
    for(int i = 1;i <= n;i++){
        add_edge(s, i, val[i]);
        add_edge(i + n, t, val[i]);
        Sum += val[i];
        for(int j = 1;j <= n;j++) if(i != j){
            if(str[i].find(str[j]) != string::npos)
                add_edge(i, j + n, Mxf);
        }
    }
    dinic();
    cout << Sum - maxf << endl;
    return 0;
}
```

---

## 作者：CCPSDCGK (赞：0)

首先由于 $\sum s_i$ 非常小，可以直接用 string 的 `find` 函数解决判断子串关系问题。

假如所有子串都不相同（如果有，特殊处理一下即可），且 $i$ 向 $j$ 连边当且仅当 $i$ 是 $j$ 的子串，这样该图构成一张 DAG。

那就变成了求 DAG 上的最大权反链，把每个点拆成左右两部分，如果 DAG 上两点 $i,j$，有连边那么在新图上 左部点 $i$ 就向右部点 $j$ 连边。

然后超级源点向左部点 $i$ 连流量为 $a_i$ 的边，右部点 $i$ 连流量为 $a_i$ 的边到超级汇点就行。

答案是所有点权和减去最大流。

时间复杂度：$O(n^4+(\sum s_i)^2)$
```cpp
string s[105];
struct line{
	int to,nxt,flow;
}edge[10305];
int head[205],tot=-1,n,zz[205];
inline void add(int u,int v,int w){
	edge[++tot]={v,head[u],w},head[u]=tot;
	edge[++tot]={u,head[v],0},head[v]=tot;
}
int level[202];
bool bfs(){
	me(level,0);
	queue<int> q;q.emplace(0),level[0]=1;
	while(!q.empty()){
		int f=q.front();q.pop();
		for(int i=head[f];~i;i=edge[i].nxt) if(!level[edge[i].to]&&edge[i].flow){
			level[edge[i].to]=level[f]+1,q.emplace(edge[i].to);
		}
	}
	return level[n+n+1];
}
ll dfs(int s,ll flow){
	if(s==n+n+1) return flow;
	ll tmp=flow;
	for(int &i=zz[s];~i;i=edge[i].nxt) if(level[edge[i].to]==level[s]+1&&edge[i].flow){
		ll ret=dfs(edge[i].to,min(flow,(ll)edge[i].flow));
		if(!ret){
			level[edge[i].to]=0;continue;
		}
		flow-=ret,edge[i].flow-=ret,edge[i^1].flow+=ret;
		if(!flow) return tmp;
	}
	return tmp-flow;
}
int main(){
	me(head,-1);cin>>n;
	for(int i=1;i<=n;i++) cin>>s[i];
	for(int i=1;i<n;i++) for(int j=i+1;j<=n;j++){
		if(s[i]==s[j]){
			add(i,j+n,inf);continue;
		}
		if(~s[i].find(s[j])) add(i,j+n,inf);
		if(~s[j].find(s[i])) add(j,i+n,inf);
	}
	ll ans=0;
	for(int i=1;i<=n;i++){
		int x;cin>>x,ans+=x;
		add(0,i,x),add(i+n,n+n+1,x);
	}
	while(bfs()) memmove(zz,head,n+n+2<<2),ans-=dfs(0,1e18);cout<<ans;
	return 0;
}
```

---

## 作者：Liyunze123 (赞：0)

如果 $s_i$ 是 $s_j$ 的子串，或者 $s_j$ 是 $s_i$ 的子串，就要在 $(i,j)$ 之间连一条无向边。求最大权独立集。

~~可蒟蒻不会做，所以用了暴力~~

我们定义 $p$ 数组，一开始 $p_i=i$。

解题流程：

1. 每次操作，随机交换三组 $(p_i,p_j)$。

2. 我们从一开始，遍历 $p$ 数组。如果 $p_i$ 还没被遍历到，$tmp$ 就加上 $a_{p_i}$（一开始 $tmp$ 为 $0$），接着遍历所有跟 $p_i$ 有连边的 $j$。

3. 如果 $tmp>ans$，更新 $ans$。否则将 $p$ 复原。

4. 重复执行 $1$ 到 $3$。

~~讲个笑话，卡不到1.99秒不算对~~

代码如下：
```
#include<cstdio>
#include<bits/stdc++.h>
#include<string.h>
using namespace std;
int n,e[10010],ne[10010],idx,h[110],a[110],p[110],st,mod=1e9+7;
long long ans;
string s[110];
void add(int a,int b){e[idx]=b,ne[idx]=h[a],h[a]=idx++;}
void solve(){
	st=clock();
	while(1.0*(clock()-st)/CLOCKS_PER_SEC<1.99){
		int b[110]={0},i[4],j[4];
		for(int w=0;w<3;w++)i[w]=rand()%n+1,j[w]=rand()%n+1,swap(p[i[w]],p[j[w]]);
		long long s=0;
		for(int w=1;w<=n;w++)
			if(!b[p[w]]){
				s+=a[p[w]];
				for(int x=h[p[w]];x!=-1;x=ne[x])b[e[x]]=1;
			}
		if(s>ans)ans=s;
		else for(int w=2;w>=0;w--)swap(p[i[w]],p[j[w]]);
	}
}
int main(){
	srand(time(0)),scanf("%d",&n);
	string::size_type idx;
	for(int w=1;w<=n;w++)cin>>s[w],p[w]=w,h[w]=-1;
	for(int w=1;w<=n;w++)scanf("%d",&a[w]);
	for(int w=1;w<=n;w++)for(int x=w+1;x<=n;x++)if(!(s[w].find(s[x])==string::npos&&s[x].find(s[w])==string::npos))add(w,x),add(x,w);
	solve(),printf("%lld",ans);
	return 0;
}
```

---

## 作者：JimmyLee (赞：0)

# 题目分析

## 题意

给定 $n$ 个字符串，要求从中选出若干个组成一个集合，且集合中每个字符串都互不包含。

求集合中字符串的权值的和的最大值。

## 分析

首先很容易想到用 KMP 判两个串是否存在包含关系。

考虑建图，将不能同时存在于一个集合中的串的节点相连。

然后发现只需求出这个图的**最大权独立集**就行了。

~~但是我不会。~~

---

因为字符串间的包含关系是一种非严格偏序关系。

所以说如果保证给定字符串 $S_i$ 互不相同，那么建出来的图就是 DAG。

在这个图上跑最大权反链即可。

但是字符串可能相同，如果没有考虑这种情况会 WA 1 个点。

可以直接把两个相同的串之间的边断掉一条，成功 AC。

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;

template<typename Tp, size_t sizn, size_t sizm>
struct netflow
{
    int cnt=1, s=sizn-2, t=sizn-3;
    Tp val[sizm<<1], dis[sizn];

    void link(int u, int v, Tp w)
    {
        // println(cerr, "{} {} {}", u, v, w);
        to[++cnt]=v;       val[cnt]=w;
        nxt[cnt]=head[u]; head[u]=cnt;
        to[++cnt]=u;       val[cnt]=0;
        nxt[cnt]=head[v]; head[v]=cnt;
    }

    int head[sizn], to[sizm<<1], nxt[sizm<<1], now[sizm<<1];
    Tp inf=numeric_limits<Tp>::max()/2;
    int bfs()
    {
        for(int i=1;i<sizn;i++) dis[i]=inf;
        dis[t]=inf;
        queue<int> q;
        q.push(s);
        dis[s]=0;
        now[s]=head[s];
        while(!q.empty())
        {
            int idx=q.front(); q.pop();
            for(int i=head[idx];i;i=nxt[i])
            {
                int arr=to[i];
                if(val[i]>0&&dis[arr]==inf)
                {
                    q.push(arr);
                    now[arr]=head[arr];
                    dis[arr]=dis[idx]+1;
                    if(arr==t) return 1;
                }
            }
        }
        return 0;
    }

    Tp dfs(int idx, Tp sum)
    {
        if(idx==t) return sum;
        Tp k, res=0;
        for(int i=now[idx];i&&sum;i=nxt[i])
        {
            now[idx]=i;
            int arr=to[i];
            if(val[i]>0&&(dis[arr]==dis[idx]+1))
            {
                k=dfs(arr, min(sum, val[i]));
                if(k==0) dis[arr]=inf;
                val[i]-=k;      res+=k;
                val[i^1]+=k;    sum-=k;
            }
        }
        return res;
    }

    Tp maxflow()
    {
        Tp ans=0;
        while(bfs()) ans+=dfs(s, inf);
        return ans;
    }
};

netflow<int64_t, 10005, 100005> nf;
#define maxn 5003

#define l(x) ((x)<<1)
#define r(x) ((x)<<1|1)

namespace KMP
{
    int nxt[maxn];

    void build(const string &k)
    {
        memset(nxt, -1, sizeof nxt);
        for(int i=1,j=-1;i<k.size();i++)
        {
            while(~j&&k[j+1]!=k[i]) j=nxt[j];
            if(k[i]==k[j+1]) j++;
            nxt[i]=j;
        }
    }

    bool chk(const string &k, const string &t)
    {
        for(int i=0, j=-1;i<t.size();i++)
        {
            while(~j&&k[j+1]!=t[i]) j=nxt[j];
            if(k[j+1]==t[i]) j++;
            if(j==k.size()-1) return 1;
        }
        return 0;
    }
}

string ss[102];

bitset<102> bs[102];

int main()
{
    int n;
    cin>>n;
    for(int i=1;i<=n;i++) cin>>ss[i];
    for(int i=1;i<=n;i++)
    {
        KMP::build(ss[i]);
        for(int j=1;j<=n;j++)
        {
            if(i==j) continue;
            if(KMP::chk(ss[i], ss[j]))
                bs[i][j]=1;
        }
    }
    
    for(int j=1;j<=n;j++)
        for(int i=1;i<=n;i++)
            if(bs[i][j]&&bs[j][i])
                bs[i][j]=0;
    for(int j=1;j<=n;j++)
        for(int i=1;i<=n;i++)
            if(bs[i][j])
                bs[i]|=bs[j];
    for(int j=1;j<=n;j++)
        for(int i=1;i<=n;i++)
            if(bs[i][j]) nf.link(l(i), r(j), nf.inf);
    
    int64_t sum=0;
    for(int64_t i=1, w;i<=n;i++)
    {
        cin>>w;
        nf.link(nf.s, l(i), w);
        nf.link(r(i), nf.t, w);
        sum+=w;
    }
    int64_t ret=nf.maxflow();
    cout<<(sum-ret)<<'\n';
}
```

---

