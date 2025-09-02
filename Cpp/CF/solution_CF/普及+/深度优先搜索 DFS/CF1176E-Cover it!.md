# Cover it!

## 题目描述

You are given an undirected unweighted connected graph consisting of $ n $ vertices and $ m $ edges. It is guaranteed that there are no self-loops or multiple edges in the given graph.

Your task is to choose at most $ \lfloor\frac{n}{2}\rfloor $ vertices in this graph so each unchosen vertex is adjacent (in other words, connected by an edge) to at least one of chosen vertices.

It is guaranteed that the answer exists. If there are multiple answers, you can print any.

You will be given multiple independent queries to answer.

## 说明/提示

In the first query any vertex or any pair of vertices will suffice.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1176E/425f889a93c1cbf45927e909f714357cbb29729c.png)Note that you don't have to minimize the number of chosen vertices. In the second query two vertices can be enough (vertices $ 2 $ and $ 4 $ ) but three is also ok.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1176E/95acc958b4ac046071fd74b6c58c6e3e5d349deb.png)

## 样例 #1

### 输入

```
2
4 6
1 2
1 3
1 4
2 3
2 4
3 4
6 8
2 5
5 4
4 3
4 1
1 3
2 3
2 6
5 6
```

### 输出

```
2
1 3
3
4 3 6
```

# 题解

## 作者：hzjnsy (赞：3)

先 dfs 一遍找出一棵搜索树，显然搜索树上深度为奇数的点和深度为偶数的点相邻。

按照深度的奇偶性划分成两个点集，这两个点集**必有一个大小不超过 $\boldsymbol{\left\lfloor\dfrac{n}{2}\right\rfloor}$**（按 $n$ 的奇偶性讨论，反证得到点数超过 $n$ 矛盾）。

那么选择那个不超过 $\left\lfloor\dfrac{n}{2}\right\rfloor$ 的点集即可。
单组数据时间、空间复杂度均为 $\mathcal{O}(n + m )$。[代码](https://codeforces.com/contest/1176/submission/226942644)。


---

## 作者：registerGen (赞：2)

（如果有 hack，敬请指出）

这个题可以不用生成树，直接贪心：枚举每一个结点 $u$。

- 如果 $u$ 之前没被访问过，那把 $u$ 加入集合 $S$，然后把和 $u$ 有边相连的之前没被访问过的点 $v$ 加入集合 $T$（因为 $u,v$ 有边连接，所以这样一定不会比把 $v$ 也加入 $S$ 中更劣）。
- 否则 $u$ 之前一定被处理过，可以直接跳过。

最后输出 $S$ 或者 $T$ 即可。

代码：

```cpp
#include <algorithm>
#include <cstdio>

const int N = 2e5;

struct Edge {
  int to, nxt;
} e[N * 2 + 10];
int head[N + 10], tote;
void addEdge(int u, int v) {
  e[++tote] = {v, head[u]};
  head[u] = tote;
}

int n, m, col[N + 10];
bool vis[N + 10];

void mian() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= m; i++) {
    int u, v; scanf("%d%d", &u, &v);
    addEdge(u, v), addEdge(v, u);
  }
  for (int u = 1; u <= n; u++)
    if (!vis[u]) {
      vis[u] = 1;
      col[u] = 1; // 加入集合 S
      for (int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].to;
        if (!vis[v]) {
          vis[v] = 1;
          col[v] = 2; // 加入集合 T
        }
      }
    }
  int cnt = 0;
  for (int i = 1; i <= n; i++)
    if (col[i] == 1) cnt++;
  if (cnt <= n / 2) {
    printf("%d\n", cnt);
    for (int i = 1; i <= n; i++)
      if (col[i] == 1) printf("%d ", i);
  } else {
    printf("%d\n", n - cnt);
    for (int i = 1; i <= n; i++)
      if (col[i] == 2) printf("%d ", i);
  }
  puts("");
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    for (int i = 1; i <= n; i++)
      head[i] = vis[i] = col[i] = 0;
    tote = 0;
    mian();
  }
  return 0;
}
```

---

## 作者：Ryo_Yamada (赞：2)

不知道为什么 div3E，CF *1700 的题评了个紫。

考虑对于每个连通块，在它的生成树上跑 dfs，将深度 $\bmod 2 = 0/1$ 的点分成两个集合，哪个大小小就将其中所有点加入答案集合。题目保证有解所以不用考虑无解。

生成树也不用单求，直接在原图中跑就是一个合法的生成树。

$\text{Code}$：

```cpp
def(N, int, 2e5 + 5)

int n, m;
int c[2];
vector<int> e[N];
bool vis[N];
int dep[N];
vector<int> ans, d[2];

void dfs(int u, int Fa) {
	vis[u] = 1;
	dep[u] = dep[Fa] + 1;
	++c[dep[u] & 1];
	d[dep[u] & 1].pb(u);
	for(int v : e[u]) if(!vis[v]) dfs(v, u);
}

int main() {
	int t; qread(t);
	W(t) {
		ans.clear();
		qread(n, m);
		rep(i, 1, n) vis[i] = 0, e[i].clear();
		rep(i, 1, m) {
			int u, v;
			qread(u, v);
			e[u].pb(v), e[v].pb(u);
		}
		rep(i, 1, n) if(!vis[i]) {
			d[0].clear(), d[1].clear();
			c[0] = c[1] = 0;
			dfs(i, 0);
			if(c[0] > c[1]) for(int v : d[1]) ans.pb(v);
			else for(int v : d[0]) ans.pb(v);
		}
		cout << ans.size() << endl;
		for(int u : ans) printf("%d ", u);
		puts("");
	}
	return 0;
}
```


---

## 作者：__Deng_Rui_Song__ (赞：1)

# presafe
~~本人还是觉得这题很水的~~
# problem
[题目传送门](https://www.luogu.com.cn/problem/CF1176E)
# solution
这题总共分为两种情况：
1. 点 $1$ 选。
2. 点 $1$ 不选。

跑两边 dfs，隔一个选一个，但是有可能多于了 $\lfloor \frac{n}{2}\rfloor$ 个点，怎么办？

别急，肯定不会！因为这两种方案总共选择了 $n$ 个点，那么总会有一个不超过 $\lfloor \frac{n}{2}\rfloor$ 个点！
# code
```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n, m;
vector<int> g[200005], ans;
bool vis[200005];
void dfs(int x, bool flag) {
  if (vis[x]) return;
  vis[x] = 1;
  if (flag) ans.push_back(x);
  for (int i = 0; i < g[x].size(); i++) dfs(g[x][i], !flag);
}// 带分数
void solve() {
  cin >> n >> m;
  for (int i = 1, x, y; i <= m; i++) {
    cin >> x >> y;
    g[x].push_back(y);
    g[y].push_back(x);
  }// 建图
  dfs(1, 1);
  if (ans.size() <= n / 2) {// 如果合法
    cout << ans.size() << '\n';
    for (int i = 0; i < ans.size(); i++) cout << ans[i] << " \n"[i + 1 == ans.size()];
    ans.clear();
    fill(vis + 1, vis + n + 1, 0);
    for (int i = 1; i <= n; i++) g[i].clear();// 多测不清空，爆0两行泪
    return;
  }
  ans.clear();
  fill(vis + 1, vis + n + 1, 0);// 多测不清空，爆0两行泪
  dfs(1, 0);
  cout << ans.size() << '\n';
  for (int i = 0; i < ans.size(); i++) cout << ans[i] << " \n"[i + 1 == ans.size()];
  ans.clear();
  fill(vis + 1, vis + n + 1, 0);
  for (int i = 1; i <= n; i++) g[i].clear();// 多测不清空，爆0两行泪
}
int main() {
  for (cin >> t; t--; solve())
    ;
  return 0;
}
```

---

## 作者：xukuan (赞：1)

这题评分有点恶意了，最多就是蓝的（我可能评绿）

## 算法：二分图染色

对于每一张图，给每个点一个颜色（黑或白）。

输出的时候选颜色少的一种输出

证明其实就是$max_{x=-tan90}^{tan90} min(x,n-x) \leq [\frac{n}{2}]$

其中$tan90$表示正无穷

代码：
```cpp
#include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
#define ll long long
using namespace std;

ll n,m,odd,even,ans,v[200010],d[200010];
//odd,even分别代表不同颜色的点的个数
//v代表这个点有没有被访问
//d代表深度
ll ver[400010],Next[400010],head[200010],tot;
//链式前向星存图
queue<ll> q;

inline ll read(){//输入优化
	ll x=0,tmp=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-') tmp=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<3)+(x<<1)+(ch^48);
		ch=getchar();
	}
	return tmp*x;
}

inline void write(ll x){//输出优化
	if(x<0){
		putchar('-');
		x=-x;
	}
	ll y=10,len=1;
	while(y<=x){
		y=(y<<3)+(y<<1);
		len++;
	}
	while(len--){
		y/=10;
		putchar(x/y+48);
		x%=y;
	}
}

inline void addEdge(ll x,ll y){//链式前向星加边
	ver[++tot]=y;
	Next[tot]=head[x];
	head[x]=tot;
}

inline void bfs(){//bfs
	v[1]=1; d[1]=0;
	even++; q.push(1);
   //第一个点标记访问过，深度为0，进入队列
	while(!q.empty()){
		ll x=q.front(); q.pop();
		for(ll i=head[x]; i; i=Next[i]){
			ll y=ver[i];
			if(v[y]) continue;
			v[y]=1; d[y]=d[x]+1;
			if(d[y]&1) odd++;
			else even++;
			q.push(y);
		}
	}
}

inline void clean(){//清零，注意不要滥用memset
	for(ll i=1; i<=tot; i++) ver[i]=Next[i]=0;
	for(ll i=1; i<=n; i++) head[i]=d[i]=v[i]=0;
	tot=odd=even=ans=0;
}

int main(){
	for(ll T=read(); T; T--){
		n=read(); m=read();
		while(m--){
			ll x=read(),y=read();
			addEdge(x,y);
			addEdge(y,x);
		}
		bfs();
		for(ll i=1; i<=n; i++){
			if((d[i]&1)==(odd<=even)) ans++;//答案总数+1
		}
		write(ans); putchar('\n');
		for(ll i=1; i<=n; i++){
			if((d[i]&1)==(odd<=even)){
				write(i); putchar(' ');
			}
		}
		putchar('\n');
		clean();
	}
	return 0;
}
```

---

## 作者：sieve (赞：0)

## 题解：[CF1176E Cover it!](https://www.luogu.com.cn/problem/CF1176E)

这题挺水的，黄比较合适。

### 思路

既然题目保证了图全连通且无环。那么，我们直接跑 DFS 就行了，每次跑到一个点，如果没有被标记，就把这个点的状态设为上一个点的相反状态，即 $1$ 变 $2$，$2$ 变 $1$，不设 $0$ 是因为初始值是 $0$。

如果按照上述方法跑完后，每个节点的标记与其连接的所有点的标记都是相反的，那么，统计正标记的数量 $ca$ 和反标记的数量 $cb$，如果 $ca < cb$，就输出所有标记为正标记的点，否则输出所有标记为反标记的点。因为要保证节点数 $\le \lfloor \frac{n}{2} \rfloor$，所以越少越好。

至于为什么这样可以，因为所有的标记都是相反的，如果取了某一种标记的点，那么一定有另一种标记的点和它相邻。

### Code:

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
int n,m;
vector<int> g[N];
int vis[N];
void dfs(int u,int f)
{
	for(auto v:g[u])
	{
		if(vis[v]==0)
		{
			vis[v]=f;
			int ne=0;
			if(f==1) ne=2;
			else ne=1;
			dfs(v,ne);
		}
	}
	return;
}
void solve()
{
	cin>>n>>m;
	for(int i=1;i<=n;++i)
	{
		g[i].clear();
		vis[i]=0;
	}
	for(int i=1;i<=m;++i)
	{
		int x,y;
		cin>>x>>y;
		g[x].push_back(y);
		g[y].push_back(x);
	}
	dfs(1,1);
	int c1=0,c2=0;
	int cnt=0,ans=0;
	for(int i=1;i<=n;++i)
	{
		c1+=(vis[i]==1);
		c2+=(vis[i]==2);
	}
	if(c1<c2) ans=1;
	else ans=2;
	for(int i=1;i<=n;++i)
	{
		if(vis[i]==ans) cnt++;
	}
	cout<<cnt<<'\n';
	for(int i=1;i<=n;++i)
	{
		if(vis[i]==ans) cout<<i<<' ';
	}
	cout<<'\n';
	return;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int T;
	cin>>T;
	while(T--) solve();
	return 0;
}
```

---

## 作者：jr_zch (赞：0)

# [Cover it!](https://www.luogu.com.cn/problem/CF1176E)
## Part 1：题目大意
给你一张 $n$ 个点 $m$ 条边的无向连通简单图，要选择至多 $\lfloor \frac {n} {2} \rfloor$ 个点使得对于任意一个没有选择的点都和至少一个选中的点通过一条边连接。

保证答案存在，如果有多个答案，输出任意一个。

## Part 2：解题思路

观察到题目没有要求选的点最少，而且输出任何一个方案都是可以的，这题就简单了许多。

其实如果要求输出最少的点数，也可以通过先在树上跑一遍 dfs 序，然后用大根堆维护每个点的有效度，再用线段树加以优化解决。

先把这个图变成一棵**树**（听机房大佬说不变成树也可以），然后对于每一个节点，要么它自己被选中（那么它的儿子和爸爸绝对不能被选中），要么他的爸爸和儿子被选中（那么它自己绝对不能被选中）。

于是这个树的形态一定是一层被选中，下一层不被选中……

在奇数层和偶数层的总点数当中一定会有一方小于 $\lfloor \frac {n} {2} \rfloor$，最后比较两者点的个数并输出即可。

总时间复杂度为 $O(n \log_2 n)$。

## Part 3：Code
```cpp
#include <bits/stdc++.h>
using namespace std;

const int maxn=2e5+7;
int t,n,m,cnt,fp,sp;
int f[maxn],dep[maxn],fans[maxn],sans[maxn];
struct node{
	int u,v;
}e[maxn];
vector<int> tr[maxn];

int find(int x){
	if(f[x]==x) return x;
	f[x]=find(f[x]);
	return f[x];
}

void init(){
	cnt=fp=sp=0,dep[1]=1;
	for(int i=1;i<=n;i++){
		f[i]=i;
		tr[i].clear();
	}
	return ;
}

void dfs(int u,int fa){
	dep[u]=dep[fa]+1;
	for(int i=0;i<tr[u].size();i++){
		int v=tr[u][i];
		if(v!=fa) dfs(v,u);
	}
	return ;
}

void print(int len,int a[]){
	for(int i=1;i<=len;i++) printf("%d ",a[i]);
	printf("\n");
	return ;
}

int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&n,&m),init();
		for(int i=1;i<=m;i++) scanf("%d%d",&e[i].u,&e[i].v);
		for(int i=1;i<=m&&cnt<n;i++){
			int fx=find(e[i].u),fy=find(e[i].v);
			if(fx!=fy){
				f[fx]=fy,cnt++;
				tr[e[i].u].push_back(e[i].v);
				tr[e[i].v].push_back(e[i].u);
			}
		}
		dfs(1,-1);
		for(int i=1;i<=n;i++){
			if(dep[i]&1) fans[++fp]=i;
			else sans[++sp]=i;
		}
		printf("%d\n",min(fp,sp));
		print(min(fp,sp),fp<sp?fans:sans);
	}	
	return 0;
}
```
$$\text{Thanks for your reading.}$$

---

## 作者：wz20201136 (赞：0)

### 题意
给你一个无向连通图，选中至多 $\lfloor n/2 \rfloor$ 个点，使得没被选中的点至少和一个被选中的点相邻。
### 题解
在原图中找到一棵生成树，于是问题就转化为了在树上选中至多 $\lfloor n/2 \rfloor$ 个点，使得每对父节点和子节点至少有一个被选中。

这个问题是很好解决的：

求出每个点的深度，如果深度为奇数的点的数量少就选中所有深度为奇数的点，否则选中所有深度为偶数的点
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node
{
	int x,y;
}E[200005];
int t,n,m,fa[200005],dep[200005],cnt1,cnt2;
int find(int x)
{
	if(fa[x]==x) return x;
	return fa[x]=find(fa[x]);
}
vector<int> son[200005];
void dfs(int u,int fa)
{
	if(dep[u]%2==0) cnt2++;
	else cnt1++;
	for(int i=0;i<son[u].size();i++)
	{
		int v=son[u][i];
		if(v==fa) continue;
		dep[v]=dep[u]+1;
		dfs(v,u);
	}
}
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>n>>m;
		for(int i=1;i<=n;i++) fa[i]=i,son[i].clear();
		for(int i=1;i<=m;i++) scanf("%d%d",&E[i].x,&E[i].y);
		int cnt=0;
		for(int i=1;cnt<n-1;i++)//生成树
		{
			int u=E[i].x,v=E[i].y;
			int fu=find(u),fv=find(v);
			if(fu==fv) continue;
			fa[fu]=fv;
			cnt++;
			son[u].push_back(v);//建树
			son[v].push_back(u);
		}
		cnt1=cnt2=0;
		dep[1]=1;
		dfs(1,0);//求深度
		if(cnt1>cnt2)
		{
			cout<<cnt2<<endl;
			for(int i=1;i<=n;i++)
			{
				if(dep[i]%2==1) continue;
				printf("%d ",i);
			}
		}
		else
		{
			cout<<cnt1<<endl;
			for(int i=1;i<=n;i++)
			{
				if(dep[i]%2==0) continue;
				printf("%d ",i);
			}
		}
		puts("");
	}
	return 0;
}
```

---

## 作者：nynkqh_yzp (赞：0)

要求所有未选择的点都至少和一个选择了的点直接相连，我们可以跑 `dfs` 将图转换成一棵树，树上的答案显然一定可以作为图的一个答案。

我们求出树上每个节点的深度，如果我们把一层全部选上，那么与它相邻的两层中的每一个点都是可以不选的，所有我们把节点按深度的奇偶性分成两个集合，任选一个集合都可以满足条件，但我们需要 $k\leq\lfloor \frac{n}{2}\rfloor$ 所以我们需要节点数量较少的一个集合。
```cpp
#include<bits/stdc++.h> 
using namespace std;
int t;
int n,m,an[2],h[200001];
vector<int>a[200001];
bool v[200001],am;
void dfs(int x,int y){
	v[x]=1;
	h[x]=y;
	for(int i=0;i<a[x].size();i++)
		if(v[a[x][i]]==0)
			dfs(a[x][i],y+1);
}
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&n,&m);
		an[0]=an[1]=0;
		am=0;
		for(int i=1;i<=n;i++){
			a[i].clear();
			v[i]=0;
			h[i]=0;
		}
		for(int i=1;i<=m;i++){
			int x,y;
			scanf("%d%d",&x,&y);
			a[x].push_back(y);
			a[y].push_back(x);
		}
		dfs(1,1);
		for(int i=1;i<=n;i++)
			h[i]%=2;
		for(int i=1;i<=n;i++)
			an[h[i]]++;
		if(an[0]<=an[1])
			am=0;
		else
			am=1;
		printf("%d\n",an[am]);
		for(int i=1;i<=n;i++)
			if(h[i]==am)
				printf("%d ",i);
		printf("\n");
	}
	return 0;
}
```


---

