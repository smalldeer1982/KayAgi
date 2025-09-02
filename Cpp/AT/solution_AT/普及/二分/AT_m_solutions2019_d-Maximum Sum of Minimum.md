# Maximum Sum of Minimum

## 题目描述

[problemUrl]: https://atcoder.jp/contests/m-solutions2019/tasks/m_solutions2019_d

$ N $ 個の頂点 $ 1,2,\ldots,N $ からなる木 $ T $ と正の整数 $ c_1,c_2,\ldots,c_N $ が与えられます。 $ i(1\ \leq\ i\ \leq\ N-1) $ 番目の辺は頂点 $ a_i $ と頂点 $ b_i $ をつなぐ辺です。

$ T $ の各頂点に正の整数を書き込んだとき、以下のようにしてスコアを計算します。

- 各辺に、$ 2 $ つの端点に書き込まれた整数のうち小さい方を書き込む。
- 各辺に書き込まれた整数の総和をスコアとする。

$ T $ の各頂点に $ c_1,c_2,\ldots,c_N $ を $ 1 $ つずつ書き込んだときのスコアの最大値を求め、 それを達成する正の整数の書き込み方を $ 1 $ つ構成してください。

$ c_1,c_2,\ldots,c_N $ に複数回現れる整数があるときは、 その整数はその回数だけ使わなければならないことに注意してください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 10000 $
- $ 1\ \leq\ a_i,b_i\ \leq\ N $
- $ 1\ \leq\ c_i\ \leq\ 10^5 $
- 与えられるグラフは木である

### Sample Explanation 1

頂点 $ 1,2,3,4,5 $ にそれぞれ $ 1,2,3,4,5 $ を書き込むと、 $ 4 $ つの辺にはそれぞれ $ 1,2,3,4 $ が書き込まれるので、スコアは $ 10 $ になります。 これが最大のスコアです。

### Sample Explanation 2

$ c_1,c_2,\ldots,c_N $ は互いに異なるとは限りません。

## 样例 #1

### 输入

```
5
1 2
2 3
3 4
4 5
1 2 3 4 5```

### 输出

```
10
1 2 3 4 5```

## 样例 #2

### 输入

```
5
1 2
1 3
1 4
1 5
3141 59 26 53 59```

### 输出

```
197
59 26 3141 59 53```

# 题解

## 作者：Tsz1024_AK (赞：0)

### 题意解析
有一颗 $n$ 个顶点，$n-1$ 条边的树，树的分数为所有边的两个端点点权的较小值之和。

确定一个 $c_1,c_2,\cdots,c_n$ 的排列 $d_1,d_2,\cdots,d_n$，使得当点 $i$ 的点权为 $d_i$ 时，树的分数最大。要求输出最大的分数和排列 $d$。不保证 $c$ 中没有重复元素，如果有多种方案使分数最大，输出任意一种 $d$ 即可。

数据范围：$\begin{cases}1 \le a_i,b_i \le n \le 10^4\\1\le c_i \le 10^5\end{cases}$
### 题目思路
首先，给 $c$ 数组排序，然后找到这棵树的 dfs 序，接下来只需要根据 dfs 序给节点定点权即可，dfs 序越小的点点权越大，最后再根据 dfs 序**从大到小**填数，即可得出答案。
### 核心代码
```cpp
sort(c.rbegin(),c.rend());
dfs(tot,-1,0);
int bo=0;
for(int i=1;i<n;i++)
    bo+=min(sd[i],sd[px[i]]);
```
```cpp
px[t]=p,sd[t]=c[cnt];
cnt++;
for(int i=0;i<tot[t].size();i++){
		if(tot[t][i]==p) continue;
		dfs(tot,t,tot[t][i]);
}
```

---

## 作者：RioFutaba (赞：0)

# 解法

很显然，最大的 $c_i$ 对答案是没有贡献的。  
那么我们就要最大化剩下 $c_i$ 的贡献。

我们先将任意一个点定为根，在任意从根节点出发的路径上，除根节点外，每一个节点的点权都比其父节点小，那么除根节点外所有点都对答案有贡献。

只需要根据 dfs 序给节点定点权即可，dfs 序越小的点点权越大。

代码：


```cpp
#include <bits/stdc++.h>
using namespace std;

const int maxn=2e5+5;
int n;
int head[maxn],ne[maxn],to[maxn],tot;
int b[maxn],d[maxn],cnt,s;
void add(int u,int v){
	to[++tot]=v;
	ne[tot]=head[u];
	head[u]=tot;
}
void dfs(int u,int fa){
	d[u]=b[cnt--];//记录答案
	s+=d[u];
	for(int i=head[u];i;i=ne[i])
		if(to[i]!=fa) dfs(to[i],u);
}
int main(){
	cin >> n;
	for(int i=1,u,v;i<n;i++){
		cin >> u >> v;
		add(u,v);
		add(v,u);
	}
	for(int i=1;i<=n;i++) cin >> b[i];
	sort(b+1,b+n+1);
	cnt=n;
	dfs(1,0);//把1定为根
	cout << s-d[1] << endl;//根是没有记录进答案的
	for(int i=1;i<=n;i++) cout << d[i] << " ";
	cout << endl;
	return 0;
}
```

---

## 作者：wuzijinmlily (赞：0)

# 题意
给你一个有 $n$ 个点，$n-1$ 条边的无根树，确定一种排列 $d$，当点 $i$ 的值 $=$ $d_i$ 时，分数最大，求最大分数的方案，有多种方案输出任意一种即可。
# 思路
我们先给 $c$ 数组排序，找到这棵树的 dfs 序，再根据 dfs 序从大到小填数就没问题了，简直就是一道大水题，秒过。

# 代码

```cpp
#include<algorithm>
#include<bitset>
#include<cassert>
#include<climits>
#include<cmath>
#include<complex>
#include<deque>
#include<iomanip>
#include<iostream>
#include<map>
#include<queue>
#include<set>
#include<string>
#include<tuple>
#include<vector>
using namespace std;
using ll=long long;
using pii=pair<int,int>;
using pll=pair<ll,ll>;
#define TEST cerr << "TEST" << endl
#define AMARI 998244353
#define TIME_LIMIT 1980000
#define el '\n'
#define El '\n'
vector<int> par;
vector<ll> ans;
vector<ll> c;
int cnt=0;
void dfs(vector<vector<int>> const& g,int p,int t){
	par[t]=p;
	ans[t]=c[cnt];
	cnt++;
	for(int i=0;i<g[t].size();i++)
	{
		if(g[t][i]==p)continue;
		dfs(g,t,g[t][i]);
	}
}
#define MULTI_TEST_CASE false
void solve()
{
	int n;
	cin>>n;
	par.resize(n);
	ans.resize(n);
	vector<vector<int>> g(n);
	for(int i=0;i<n-1;i++)
	{
		int u,v;
		cin>>u>>v;
		u--;
		v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	c.resize(n);
	for(int i=0;i<n;i++)cin>>c[i];
	sort(c.rbegin(),c.rend());
	dfs(g,-1,0);
	ll score=0;
	for(int i=1;i<n;i++)
	{
		score+=min(ans[i],ans[par[i]]);
	}
	cout<<score<<el;
	for(int i=0;i<n;i++)cout<<ans[i]<<' ';
	cout<<el;
	return;
}
void calc()
{
	return;
}
signed main()
{
	cin.tie(nullptr);
	ios::sync_with_stdio(false);
	calc();
	int t=1;
	if(MULTI_TEST_CASE) cin>>t;
	while(t--)
	{
		solve();
	}
	return 0;
}
```



---

## 作者：XYQ_102 (赞：0)

## 思路
其实就是除了最大值都加一遍，如果一个值加了两遍会占一个比它大的值得位置，不优，构造的话就是随便选一个根然后按 dfs 序从大到小填数。
## Code
```cpp
#include <bits/stdc++.h>
#define fi first
#define se second
#define pii pair<int,int>
#define mp make_pair
#define pb push_back
#define space putchar(' ')
#define enter putchar('\n')
#define eps 1e-10
#define MAXN 10005
#define ba 47
//#define ivorysi
using namespace std;
typedef long long int64;
typedef unsigned int u32;
typedef double db;
template<class T>
void read(T &res) {
    res = 0;T f = 1;char c = getchar();
    while(c < '0' || c > '9') {
    	if(c == '-') f = -1;
    	c = getchar();
    }
    while(c >= '0' && c <= '9') {
    	res = res * 10 +c - '0';
    	c = getchar();
    }
    res *= f;
}
template<class T>
void out(T x) {
    if(x < 0) {x = -x;putchar('-');}
    if(x >= 10) {
    	out(x / 10);
    }
    putchar('0' + x % 10);
}
struct node {
    int to,next;
}E[MAXN * 2];
int sumE,head[MAXN],N;
int c[MAXN],ans;
int p[MAXN],tot;
void add(int u,int v) {
    E[++sumE].to = v;
    E[sumE].next = head[u];
    head[u] = sumE;
}
void dfs(int u,int fa) {
    p[u] = c[tot--];
    for(int i = head[u] ; i ; i = E[i].next) {
        int v = E[i].to;
        if(v != fa) {
            dfs(v,u);
        }
    }
}
void Solve() {
    read(N);
    int a,b;
    for(int i = 1 ; i < N ; ++i) {
        read(a);read(b);add(a,b);add(b,a);
    }
    for(int i = 1 ; i <= N ; ++i) read(c[i]);
    sort(c + 1,c + N + 1);
    for(int i = 1 ; i < N ; ++i) ans += c[i];
    tot = N;
    dfs(1,0);
    out(ans);enter;
    for(int i = 1 ; i <= N ; ++i) {
        out(p[i]);space;
    }
    enter;
}
int main() {
#ifdef ivorysi
    freopen("f1.in","r",stdin);
#endif
    Solve();
    return 0;
}


```

---

## 作者：aeiouaoeiu (赞：0)

这题好像就是个贪心？？？

因为一条边取的是最小值，那么那个较大值就没用了，不如把最小值搞大点，所以我们给 $c$ 排个序，进行一次 bfs，给起始点放最大值，然后给后边遍历到的点放能放到的最大值，这样只有起始点的最大值没有贡献，其他都有贡献，为最优解。
```cpp
#include<bits/stdc++.h>
#define pb push_back
#define pob pop_back
#define mp make_pair
using namespace std;
typedef long long ll;
const int maxn=10005;
ll n,ans[maxn],num;
vector<ll> edge[maxn],c;
queue<ll> q;
int main(void){
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	ll T=1;
	//cin>>T;
	for(int tcs=1;tcs<=T;tcs++){
		cin>>n;
		ll u,v,w;
		for(int i=1;i<n;i++){
			cin>>u>>v;
			edge[u].pb(v),edge[v].pb(u);
		}
		for(int i=1;i<=n;i++){
			cin>>w;
			c.pb(w);
		}
		sort(c.begin(),c.end());
		ans[1]=c.back(),c.pob(),q.push(1);
		for(;!q.empty();){
			u=q.front(),q.pop();
			for(auto v:edge[u]){
				if(!ans[v]) ans[v]=c.back(),num+=c.back(),c.pob(),q.push(v);
			}
		}
		cout<<num<<"\n";
		for(int i=1;i<=n;i++) cout<<ans[i]<<" ";
	}
	return 0;
}
```

---

