# Privatization of Roads in Treeland

## 题目描述

Treeland consists of $ n $ cities and $ n-1 $ roads. Each road is bidirectional and connects two distinct cities. From any city you can get to any other city by roads. Yes, you are right — the country's topology is an undirected tree.

There are some private road companies in Treeland. The government decided to sell roads to the companies. Each road will belong to one company and a company can own multiple roads.

The government is afraid to look unfair. They think that people in a city can consider them unfair if there is one company which owns two or more roads entering the city. The government wants to make such privatization that the number of such cities doesn't exceed $ k $ and the number of companies taking part in the privatization is minimal.

Choose the number of companies $ r $ such that it is possible to assign each road to one company in such a way that the number of cities that have two or more roads of one company is at most $ k $ . In other words, if for a city all the roads belong to the different companies then the city is good. Your task is to find the minimal $ r $ that there is such assignment to companies from $ 1 $ to $ r $ that the number of cities which are not good doesn't exceed $ k $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1141G/7d36299fe9125bdd92ab603e16bc3fe180559f7f.png)The picture illustrates the first example ( $ n=6, k=2 $ ). The answer contains $ r=2 $ companies. Numbers on the edges denote edge indices. Edge colors mean companies: red corresponds to the first company, blue corresponds to the second company. The gray vertex (number $ 3 $ ) is not good. The number of such vertices (just one) doesn't exceed $ k=2 $ . It is impossible to have at most $ k=2 $ not good cities in case of one company.

## 样例 #1

### 输入

```
6 2
1 4
4 3
3 5
3 6
5 2
```

### 输出

```
2
1 2 1 1 2 ```

## 样例 #2

### 输入

```
4 2
3 1
1 4
1 2
```

### 输出

```
1
1 1 1 ```

## 样例 #3

### 输入

```
10 2
10 3
1 2
1 3
1 4
2 5
2 6
2 7
3 8
3 9
```

### 输出

```
3
1 1 2 3 2 3 1 3 1 ```

# 题解

## 作者：ustze (赞：2)

div3果然**题很多呢  
题意就是给定一棵树，你可以给每条边一个颜色，问在不超过k个点连出两条相同颜色的边的情况下，最少需要几种颜色  
随便考虑一下发现如果k=0，那么答案就是度数最大的那个点的度数，贪心的想法就是，让度数大的点不满足条件，那答案就是剩下的n-k个点中度数最大的，至于方案就随便做一下就行了  
code:
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200005;
int n,k;
vector<int> G[N],g[N];
int deg[N],num,ans[N];
void dfs(int u,int fa,int fc){
    int x=1;
    if(x==fc&&x<num) x++;
    for(int i=0;i<G[u].size();i++){
    	int v=G[u][i];
        if(v==fa) continue;
        ans[g[u][i]]=x;
        dfs(v,u,x);
        if(x<num) x++;
        if(x==fc&&x<num) x++;
    }
}
int main(){
    cin>>n>>k;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        G[u].push_back(v);
        g[u].push_back(i);
        G[v].push_back(u);
        g[v].push_back(i);
        deg[u]++,deg[v]++;
    }
    sort(deg+1,deg+n+1);
    num=deg[n-k]!=0?deg[n-k]:1;
    cout<<num<<endl;
    dfs(1,0,0);
    for(int i=1;i<n;i++) cout<<ans[i]<<' ';
    return 0;
}

```

---

## 作者：nullqtr_pwp (赞：1)

# CF1141G
$1900$ 也有紫啊。

先考虑最多的染色种类数能是多少，我最开始的思路是二分，check 一下能否染成 $x$ 种颜色。设 $u$ 点的度数为 $d_u$，显然，对于 $d_u>x$ 的点，因为抽屉原理，不可能互不相同，所以必然是不好的点。若不好的点数量 $>k$ 则必然无解。我们接下来思考，剩下的 $d_u\leq x$  的点是否可以都是好的。我们考虑从 $1$ 号节点往下染色，记录父亲节点传下来的边的颜色，因为对这个点造成影响的只有父亲节点，往下传的时候它的儿子们一定是互不干扰的。因此可以直接从根节点 dfs 染色。如果不懂可以看 dfs 部分的代码。

优化：显然二分是没必要的，让颜色种类数直接取到 $d_i$ 的第 $k+1$ 大即可。

```cpp
const int maxn=200005;
vector<int>g[maxn];
int n,m,col[maxn],d[maxn],deg[maxn],ans;
map<pii,int>mp;
void dfs(int u,int f,int lst){
	int now=lst-1;
	if(!now) now=ans;
	for(int v:g[u]) if(v^f){
		col[mp[{u,v}]]=now;
		now--;
		if(!now) now=ans;
		dfs(v,u,col[mp[{u,v}]]);
	}
}
signed main(){
	n=read(),m=read();
	F(i,1,n-1){
		int u=read(),v=read();
		g[u].pb(v);
		g[v].pb(u);
		mp[{u,v}]=mp[{v,u}]=i;
	}
	F(i,1,n) deg[i]=(int)g[i].size();
	vector<int>v(n+1);
	F(i,1,n) v[i]=deg[i];
	sort(v.begin(),v.end());
	ans=v[n-m];
	printf("%d\n",ans);
	dfs(1,0,ans);
	F(i,1,n-1) printf("%d ",col[i]);
}
```


---

## 作者：Phartial (赞：1)

不会贪心。没关系，我会二分！

发现一个点的邻边的颜色不会影响到其他点（非邻点的情况是显然的，对于邻点 $x,y$，我们考虑以 $x$ 为根，在 $y$ 的子树里把需要的颜色和任意一种其他的颜色交换即可），因此每个点的贡献是独立的。于是考虑二分答案，假设我们现在二分出颜色数 $r$，则对于每个点，当且仅当它的度数大于 $r$ 时，这个点才会造成贡献。遍历整棵树，统计答案是否超过 $k$ 即可得到答案。

对于方案，我们可以直接 dfs 遍历整棵树，对每个点，我们将颜色依次涂在它的相邻边上，特判一下能不能与父亲边重复即可（即这个点是否必须造成贡献）

```cpp
#include <iostream>
#include <vector>

using namespace std;
using Pii = pair<int, int>;

const int kN = 2e5 + 1;

int n, k, p[kN];
vector<Pii> e[kN];

int D(int x, int f, int c) {
  int s = (c < e[x].size());
  for (Pii i : e[x]) {
    if (i.first != f) {
      s += D(i.first, x, c);
    }
  }
  return s;
}
void P(int x, int f, int c, int v) {
  int _c = 1;
  for (Pii i : e[x]) {
    if (i.first != f) {
      for (_c = _c % c + 1; c >= e[x].size() && _c == v; _c = _c % c + 1) {
      }
      P(i.first, x, c, p[i.second] = _c);
    }
  }
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  cin >> n >> k;
  for (int i = 1, x, y; i < n; ++i) {
    cin >> x >> y;
    e[x].emplace_back(y, i);
    e[y].emplace_back(x, i);
  }
  int l = 1, r = n;
  while (l < r) {
    int m = l + r >> 1;
    if (D(1, 0, m) <= k) {
      r = m;
    } else {
      l = m + 1;
    }
  }
  cout << l << '\n';
  P(1, 0, l, 0);
  for (int i = 1; i < n; ++i) {
    cout << p[i] << ' ';
  }
  return 0;
}
```

---

## 作者：liruixiong0101 (赞：0)

## P0 前置知识：
贪心，dfs。

## P1 题意：
给你一个 $n$ 个点的树，将其 $n-1$ 条边染色。  
定义一个点，连接这个点的边若颜色有相同，这个点为一个“坏点”，否则为“好点”。  
让你求最多有 $k$ 个“坏点”的情况下，你最少可以用几个颜色来染色，接着输出用这几个颜色进行染色的方案。

## P2 思路：
我们不妨贪心的将连边最多的前 $k$ 个点全部设为“坏点”，那么第 $n-k$ 的连边数量就是第一问的答案。  
上述的“连边数量”其实就是图论中的“度”。
设 $deg_i$ 为第 $i$ 个节点的度，将 $deg$ 数组从小到大排序后第一问的答案就是 $\max\{1,deg_{n-k}\}$。  
与 $1$ 取最大值的原因是：如果 $deg_{n-k}=0$，答案为 $0$ 吗？很显然不是，因为这样就不需要染色了很显然这是错的。

---

求出第一问的答案后，染色就好进行了，直接跑一边 dfs 进行染色即可。  
需要注意一点的是，dfs 只可以对点进行遍历，若要对边进行染色的话，那么就需要在从 $u$ 转移到 $v$ 的时候记录一下他们连边的编号是多少即可。

## P3 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
using LL = long long;
using Pii = pair<LL, LL>;
const int kMaxN = 2e5 + 5;
int n, k, deg[kMaxN], ans[kMaxN];
vector<Pii> e[kMaxN];
void dfs(int u, int fa, int pc) {
  int c = 0;
  for (Pii p : e[u]) {  // 遍历
    int v = p.first, i = p.second;
    if (/*v == fa || */ans[i]) {
      // 这里是判断有没有走回头路，因为后面的判断包括了前者，可以省略
      continue;
    }  // 染过色了
    if (min(c + 1, ans[0]) == pc) {
      c = min(c + 1, ans[0]);
    }  // 不能与邻边同色
    c = min(c + 1, ans[0]);
    ans[i] = c;    // 染色
    dfs(v, u, c);  // 遍历下一个点
  }
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> n >> k;
  for (int i = 1, u, v; i < n; i++) {
    cin >> u >> v;
    e[u].push_back({v, i});
    e[v].push_back({u, i});  // 加上编号一起存
    deg[u]++, deg[v]++;      // 记录度数
  }
  sort(deg + 1, deg + 1 + n);   // 排序
  ans[0] = max(1, deg[n - k]);  // 第一问答案
  dfs(1, -1, -1);
  cout << ans[0] << "\n";
  for (int i = 1; i < n; i++) {
    cout << ans[i] << " ";
  }
  return 0;
}
```

## P4 AC 链接：
<https://codeforces.com/problemset/submission/1141/209721453>

---

## 作者：cppcppcpp3 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1141G)。

## Solution

贪心，一个点是好的当且仅当从经过它的边颜色互不相同。那我们求出每个点的度数 $d_i$，排序后舍弃度数最大的 $k$ 的点，则 $ans=d_{k+1}$。

染色的过程通过一次 $\operatorname{dfs}$ 实现。设 $c$ 为最近使用过的颜色编号，则对点 $u$ 染色时，$c$ 加 $1$，如果 $c>ans$ 时将 $c$ 重置为 $1$ 即可。

```cpp
#include<bits/stdc++.h>
#define il inline
#define int long long
using namespace std;
const int N=2e5+5;
const int inf=1e9+7;

il int wrd(){
	int x=0,f=1; char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1; c=getchar();}
	while(isdigit(c)){x=x*10+c-48,c=getchar();}
	return x*f;
}

int n,k,d[N],cnt,head[N],ans,p[N];

struct edge{
	int to,nxt;
}e[N<<1];

il void add(int u,int v){
	e[++cnt]=edge{v,head[u]},head[u]=cnt;
}

void dfs(int u,int fa,int c){
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v==fa) continue;
		c=(c==ans ? 1 : c+1),p[(i+1)/2]=c; // (i+1)/2 是对应边的编号。
		dfs(v,u,c);
	}
}

bool cmp(int a,int b){
	return a>b;
}

main(){
	n=wrd(),k=wrd();
	for(int i=1;i<n;++i){
		int u=wrd(),v=wrd();
		add(u,v),add(v,u);
		++d[u],++d[v];
	}
	sort(d+1,d+n+1,cmp);
	ans=d[k+1];
	
	dfs(1,0,0);
	printf("%lld\n",ans);
	for(int i=1;i<n;++i) printf("%lld ",p[i]);
	return 0;
}
```

---

## 作者：傅思维666 (赞：0)

## 题解：

不知道为什么是紫题。

非常容易证明贪心。排个序就出来了。

然后染色的话是这道题重点，可以用DFS，在遍历的时候加个参数c保证颜色不重复。

之后把枚举到的原始边编号映射到答案边编号上即可。

代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn=2e5+5;
int n,k,r;
int tot,head[maxn],to[maxn<<1],nxt[maxn<<1];
int du[maxn],ans[maxn];
void add(int x,int y)
{
	to[++tot]=y;
	nxt[tot]=head[x];
	head[x]=tot;
}
void coloring(int x,int f,int c)
{
	for(int i=head[x];i;i=nxt[i])
	{
		int y=to[i];
		if(y==f)
			continue;
		c++;
		if(c>r)
			c=1;
		ans[(i+1)/2]=c;
		coloring(y,x,c);
	}
}
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<n;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);
		add(y,x);
		du[x]++,du[y]++;
	}
	sort(du+1,du+n+1);
	r=du[n-k];
	coloring(1,0,0);
	printf("%d\n",r);
	for(int i=1;i<n;i++)
		printf("%d ",ans[i]);
	return 0;
}
```



---

## 作者：zhy12138 (赞：0)

本文同步发表于[我的博客](https://zhy12138.github.io/2019/03/24/CF-1141-div3/)

根据题目定义，一个节点$i$若需要成为‘好’的点，则至少需要$degree_i$中颜色才能满足条件，题中允许存在k个'坏'节点，则最大所需颜色为将$degree$排序后的第k+1个。

方案的话随便染，只要在k个颜色的范围中并且尽量染不同颜色即可。

注：文中的degree指点的度数

```cpp
#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<iomanip>
#include<cstring>
#include<algorithm>
#include<ctime>
using namespace std;
inline int read()
{
	int kkk=0,x=1;
	char c=getchar();
	while((c<'0' || c>'9') && c!='-')
		c=getchar();
	if(c=='-')
		x=-1,c=getchar();
	while(c>='0' && c<='9')
		kkk=(kkk<<3)+(kkk<<1)+(c-'0'),c=getchar();
	return kkk*x;
}
int n,k,head[200001],tot,root,maxn,ans[200001],degree[200001];
struct sb
{
	int to,nextn;
}a[400001];
inline void ADD(int from,int to)
{
	a[++tot].to=to,a[tot].nextn=head[from];
	head[from]=tot;
}
inline void fun(int u,int fa,int col)
{
	for(register int i=head[u];i!=0;i=a[i].nextn)
	{
		int v=a[i].to;
		if(v==fa)
			continue;
		++col;
		if(col>maxn)
			col=1;
		ans[(i+1)/2]=col;
		fun(v,u,col);
	}
}
int main()
{
	n=read(),k=read();
	for(register int i=1;i<n;++i)
	{
		int u=read(),v=read();
		++degree[u];
		++degree[v];
		ADD(u,v);
		ADD(v,u);
	}
	sort(degree+1,degree+n+1);
	maxn=degree[n-k];
	printf("%d\n",maxn);
	fun(1,0,0);
	for(register int i=1;i<n;++i)
		printf("%d ",ans[i]);
	return 0;
}
```

---

## 作者：C_S_X_ (赞：0)

没人发题解？~~赶快趁机刷贡献~~

### 一道水题

定义一个“好城市”的所有边来自不同的公司。最多允许出现k个不好的城市，请问至少需要多少个公司，并输出每条道路属于哪个公司，special judge。

如果一开始的坏城市的数量大于k，我们就要将一些坏城市边为好城市，而答案r取决于我们选择处理的城市的最大度数。于是直接贪心先将城市按度数排序，放过前面k个度数较大的坏城市不处理,将剩下的超标的城市标记一下。一次搜索遍历一下贪心把这些城市的边处理一下就没了。。。

~~这题竟然被前几个人评成黑题，我点了黄。~~

```cpp
#include<bits/stdc++.h>
#define N 200005
using namespace std;
int n,k,in1[N],in2[N],tot=0,first[N],nxt[N<<1],cnt=0,r=1;
int d[N]={0},tag[N]={0},fa[N]={0};
map <pair<int,int>,int> col;
struct Edge
{
	int u,v;
}edge[N<<1];
struct Node
{
	int num,du;
}p[N];

int Read()
{
	int x=0,f=1;
	char c=getchar();
	while (c<'0'||c>'9') {if (c=='-') f=-1;c=getchar();}
	while (c>='0'&&c<='9') {x=(x<<1)+(x<<3)+c-'0';c=getchar();}
	return f*x;
}


bool cmp1(const Node a,const Node b)
{
	return a.du>b.du;
}
void Add(int u,int v)
{
	tot++;
	nxt[tot]=first[u];
	first[u]=tot;
	edge[tot]=(Edge){u,v};
	return;
}

void DFS(int u,int e)
{
	int cl=1;
	if (tag[u]) for (int j=first[u];j!=-1;j=nxt[j])
	{
		int v=edge[j].v;
		if (v==fa[u]) continue;
		if (e!=-1&&cl==col[make_pair(u,fa[u])]) cl++;
		fa[v]=u;
		col[make_pair(u,v)]=cl;
		col[make_pair(v,u)]=cl;
		cl++;
		DFS(v,j);
	}
	else
	{
		if (e!=-1) cl=col[make_pair(u,fa[u])];
		for (int j=first[u];j!=-1;j=nxt[j])
		{
			int v=edge[j].v;
			if (v==fa[u]) continue;
			fa[v]=u;
			col[make_pair(u,v)]=cl;
			col[make_pair(v,u)]=cl;
			DFS(v,j);
		}
	}
	return;
}

int main()
{
	memset(first,-1,sizeof(first));
	n=Read(),k=Read();
	for (int i=1;i<n;i++)
	{
		in1[i]=Read(),in2[i]=Read();
		Add(in1[i],in2[i]),Add(in2[i],in1[i]);
		d[in1[i]]++,d[in2[i]]++;
	}
	for (int i=1;i<=n;i++) p[i]=(Node){i,d[i]};
	sort(p+1,p+n+1,cmp1);
	for (int i=1;i<=n;i++) 
	{
		if (p[i].du>1) cnt++;
		if (cnt>k) r=max(r,p[i].du),tag[p[i].num]=1;
	}
	DFS(1,-1);
	printf("%d\n",r);
	for (int i=1;i<n;i++) printf("%d ",col[make_pair(in1[i],in2[i])]);
	return 0;
}
```


---

