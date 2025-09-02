# Maximum Distance

## 题目描述

Chouti 厌倦了枯燥的作业，于是他打开了几年前自己出的一个老编程题。

给定一个包含 $n$ 个顶点和 $m$ 条带权边的连通无向图。有 $k$ 个特殊顶点：$x_1, x_2, \ldots, x_k$。

我们定义一条路径的代价为该路径上所有边权的最大值。两个顶点之间的距离为连接它们的所有路径中代价的最小值。

对于每一个特殊顶点，找出另一个距离它最远的特殊顶点（即上述定义下距离最大的那个），并输出它们之间的距离。

原本的限制很小，所以 Chouti 觉得这题很无聊。现在，他提高了限制，希望你能帮他解决这个问题。

## 说明/提示

在第一个样例中，顶点 $1$ 和 $2$ 之间的距离为 $2$，因为可以通过权值为 $2$ 的边直接相连。因此对于 $1$ 和 $2$，距离最远的特殊顶点的距离都是 $2$。

在第二个样例中，可以发现 $1$ 和 $2$ 之间的距离、$1$ 和 $3$ 之间的距离都是 $3$，$2$ 和 $3$ 之间的距离是 $2$。

图中可能存在重边和自环，如第一个样例所示。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2 3 2
2 1
1 2 3
1 2 2
2 2 1
```

### 输出

```
2 2 
```

## 样例 #2

### 输入

```
4 5 3
1 2 3
1 2 5
4 2 1
2 3 2
1 4 4
1 3 3
```

### 输出

```
3 3 3 
```

# 题解

## 作者：_Fontainebleau_ (赞：3)

是一道**最小生成树**的题目。

用的是 $kruskal$ 。

其他不多说，就讲一下为什么最后输出 $ans$ $k$ 次。

假设一个点到另一个点的最大值比现在小，那么其他的点也会走这条路。

所以上代码。

```cpp
#include<bits/stdc++.h>
#define FOR(i,j,k)  for(int i=(j);i<=(k);i++)
using namespace std;
int n,m,k,cnt;
int ans;
bool s[100001];
int f[100001];
struct point{
	int a,b,val;
}p[200001];
inline int read()
{
    int x=0,f=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
    return x*f;
}
inline bool cmp(point x,point y)
{
	return x.val<y.val;
}
int find(int x)
{
	if(f[x]==x)	return x;
	f[x]=find(f[x]);
	return f[x];
}
int main()
{
	n=read(),m=read(),k=read();
	int x;
	for(int i=1;i<=n;i++)	f[i]=i;
	for(int i=1;i<=k;i++)	x=read(),s[x]=true;
	for(int i=1;i<=m;i++)
	{
		int u=read(),v=read(),w=read();
		p[++cnt].a=u,p[cnt].b=v,p[cnt].val=w;
	}
	sort(p+1,p+1+cnt,cmp);
	for(int i=1;i<=cnt;i++)
	{
		int fa=find(p[i].a),fb=find(p[i].b);
		if(fa!=fb)
		{
			if(s[fa]&&s[fb])	ans=max(ans,p[i].val);
			if(s[fa]||s[fb])	s[fa]=s[fb]=1;
			f[fa]=fb;
		}
	}
	for(int i=1;i<=k;i++)	printf("%d ",ans);
	return 0;
}

```


---

## 作者：da32s1da (赞：3)

显然答案是**最小生成树**中的**最长边**，而且该最长边要满足**断开它**后的两部分中**都有特殊点**。

这个很容易在做最小生成树时顺便维护一下。
```
#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1e5+50;
int n,m,k,x,y;
struct node{
	int x,y,z;
	bool operator <(const node &o)const{return z<o.z;}
}b[N];
int fa[N],a[N],ans;
int gf(int u){return fa[u]==u?u:fa[u]=gf(fa[u]);}
int main(){
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=k;i++){
		scanf("%d",&x);
		a[x]=1;
	}
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<=m;i++)
	scanf("%d%d%d",&b[i].x,&b[i].y,&b[i].z);
	sort(b+1,b+m+1);
	for(int i=1;i<=m;i++){
		x=gf(b[i].x);
		y=gf(b[i].y);
		if(x==y)continue;
		fa[x]=y;
		if(a[x]&&a[y])ans=b[i].z;//两端都有特殊点
		if(a[x])a[y]|=1;//更新节点信息
	}
	for(int i=1;i<=k;i++)printf("%d ",ans);
}
```

---

## 作者：hongshixiaobai (赞：1)

# CF1081D Maximum Distance 题解
[传送门](https://www.luogu.com.cn/problem/CF1081D)
## 思路
首先显而易见，距离每个特殊点最远的特殊点距离都一样，所以将一个数（答案）输出 $k$ 次即可，可以在最小生成树合并过程中，记录每个连通分量中是否有特殊点，然后不断更新连接特殊点所在连通分量的边的长度，最后求得的最大值即为所有特殊点两两之间的最远距离。

## AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
struct _ {long long u,v,w;}tmp;
bool operator <(_ tmp1,_ tmp2){return tmp1.w>tmp2.w;}
priority_queue<_>q;long long n,m,i,j,k,u,v,fa[100005],ans,lst,cnt,flag[100005];
long long find(long long x){flag[fa[x]]|=flag[x];if(fa[x]==x)return x;return fa[x] = find(fa[x]);}
void merge(long long x,long long y){fa[find(x)] = fa[find(y)];flag[fa[find(y)]]|=flag[fa[find(x)]];}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n>>m>>k;
	for(i = 1;i<=k;i++)
	{
		cin>>lst;
		flag[lst] = 1;
	}
	for(i = 1;i<=m;i++)
	{
		cin>>tmp.u>>tmp.v>>tmp.w;
		q.push(tmp);
	}
	for(i = 1;i<=n;i++)fa[i] = i;
	while(q.size())
	{
		tmp = q.top();
		q.pop();
		if(find(tmp.u)!=find(tmp.v))
		{
			if(flag[find(tmp.u)]&&flag[find(tmp.v)])
			{
				ans = tmp.w;
			}
			merge(tmp.u,tmp.v);
			cnt++;
			if(cnt == n-1)break;
		}
	}
	for(i = 1;i<=k;i++)cout<<ans<<' ';
}
```

---

## 作者：BYR_KKK (赞：1)

duel 到的，没有蓝题难度。10分钟过掉之后发现登错号，令人忍俊不禁。

首先，根据题目中的定义，两点之间的距离就是其在 MST 上路径的最大值。这被称作最小瓶颈树。当我们贪心地往里面加边的时候，两个点第一次联通的时候加的那条边就是两点之间的距离，因此不难发现关于最小瓶颈树的结论是正确的。

考虑对于所有关键点而言，与其在树上距离最大的点的距离就是最后一次加边使其联通的边长。显然一定有且只有一次加边使得加边后的连通块包含全部的 $k$ 个关键点，加边前两个连通块分别包含非零个关键点。找出这一次加边即可，所加的长度就是答案。带权并查集可以维护。

---

## 作者：fush (赞：1)

很明显是一道**最小生成树**的题目。  
我用的是 kruskal。

只要在 kruskal 的时候判断一下哪些连结了特殊点，去选择其中的最大值即可。

由于是一棵树，那么肯定会经过我们选择中的那条最长的边，所以只需要输出 $k$ 次 $ans$ 即可。
```cpp
//#define LOCAL
#include<bits/stdc++.h>
#define endl '\n'
#define ll long long
using namespace std;
const int N = 1e5 + 10;
struct A{
	int u, v, w;
}e[N];
int a[N], fa[N], n, m, k;
int find(int x){
	return (fa[x] == x? x : fa[x] = find(fa[x]));
}
int main() {
	cin >> n >> m >> k;
    for(int i = 1; i <= n; i++)
        fa[i] = i;
    for(int i = 1; i <= k; i++){
        int x;
        cin >> x;
        a[x] = 1;
    }
	for(int i = 1; i <= m; i++)
		cin >> e[i].u >> e[i].v >> e[i].w;
	sort(e + 1, e + 1 + m, [&](A& i, A& j){return i.w < j.w;});
	int ans = 0;
	for(int i = 1;i <= m; i++){
		int x = find(e[i].u), y = find(e[i].v);
		if(x != y){
			if(a[x] && a[y])ans = Max(ans, e[i].w);
			if(a[x] || a[y])a[x] = a[y] = 1;
			fa[x] = y;
		}
	}
	for(int i = 1; i <= k; i++)
		cout << ans << " ";
	return 0;
}
```

---

## 作者：Infinite_Loop (赞：1)

# CF1081D
## 思路
使得 $k$ 个点连通，使得最长边的权值最小，是一道最小生成树的题目。考虑使用 kruskal。只要在做 kruskal 时维护一下哪些边要选即可。至于为什么最后输出 $k$ 次 $ans$，因为是求到最远的点的路径的最大边权，肯定会经过选择的边中的最长边，所以输出 $k$ 次 $ans$ 即可。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int n,m,k,a[N],cnt,fa[N],ans;
bool f[N];
struct node{
	int u,v,d;
}e[N<<1];
bool cmp(node a,node b){
	return a.d<b.d;
}
int find(int x){
	return x==fa[x]?x:fa[x]=find(fa[x]);
}
int main(){
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=k;i++)scanf("%d",&a[i]),f[a[i]]=true;
	for(int i=1;i<=m;i++){
		int u,v,d;
		scanf("%d%d%d",&u,&v,&d);
		e[++cnt].u=u;
		e[cnt].v=v;
		e[cnt].d=d;
	}
	sort(e+1,e+1+cnt,cmp);
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<=cnt;i++){
		int u=e[i].u,v=e[i].v,d=e[i].d;
		int fu=find(u),fv=find(v);
		if(fu!=fv){
			if(f[fu]==true&&f[fv]==true){
				ans=max(ans,d);
			}else if(f[fu]==true||f[fv]==true){
				f[fu]=f[fv]=true;
			}
			fa[fu]=fv;
		}
	}
	for(int i=1;i<=k;i++)printf("%d ",ans);
	return 0;
}
```


---

## 作者：yhylivedream (赞：0)

套路先跑最小生成树，发现至少有一条边满足删除此边后，分裂的两个联通块中各有特殊点。

则两个联通块的特殊点互相到达都要经过这条边，找到最大的满足条件的边，输出 $k$ 次即为答案。

## Code

```cpp
#include <bits/stdc++.h>

using namespace std;
using LL = long long;
using Pii = pair<int, int>;

const int kMaxN = 1e5 + 5;

int n, m, k, mx, a[kMaxN], fa[kMaxN], f[kMaxN];

int GetRoot(int x) {
  return fa[x] == x ? x : fa[x] = GetRoot(fa[x]);
}
struct Node {
  int x, y, w;
  bool operator < (Node _) { return w < _.w; }
} e[kMaxN];

int main() {
  cin.tie(0)->ios::sync_with_stdio(0);
  cin >> n >> m >> k, iota(fa + 1, fa + n + 1, 1);
  for (int i = 1; i <= k; i++) {
    cin >> a[i], f[a[i]] = 1;
  }
  for (int i = 1, x, y, w; i <= m; i++) {
    cin >> x >> y >> w, e[i] = {x, y, w};
  }
  sort(e + 1, e + m + 1);
  for (int i = 1; i <= m; i++) {
    int fx = GetRoot(e[i].x), fy = GetRoot(e[i].y);
    if (fx != fy) {
      (f[fx] && f[fy]) && (mx = e[i].w);
      fa[fx] = fy, f[fy] |= f[fx];
    }
  }
  for (int i = 1; i <= k; i++) {
    cout << mx << ' ';
  }
}
```

---

## 作者：Bulyly (赞：0)

### 题目大意
给出 $n$ 个顶点 $m$ 条加权边和 $k$ 个特殊带点的无向图。路径的成本定义为其中边的最大权重，两个顶点之间的距离作为连接它们的路径的最小成本。对于每个特殊顶点,找到另一个离它最远的特殊顶点并输出它们之间的距离。
### 解析
显然就是把 $k$ 个特殊点连接在一起的最小边的最大值。为什么？首先答案一定是在 $k$ 个特殊点相连所构成图中。其次因为是最小边，所以是含 $k$ 个点的最小生成树所以明显的 MST。关于任何特殊点的答案一定是最小生成树中的最大值。因为任何特殊点都能经过该路径到达另外特殊点。所以输出是 $k$ 次最大值。关于求 MST,对于线段的取用，一定是去掉该线段后，两边集合都含有特殊点，否则将没必要加入。

Update on 12.11：添加了对于重要结论的证明。 

```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;
const int N=101105;
int n,m,k,ans,a,b,c;
bool sg[N];
int p[N];
struct Node
{
	int x,y,w;
}e[N];
inline int find(int x){return p[x]==x?p[x]:p[x]=find(p[x]);}
inline bool cmp(Node A,Node B){return A.w<B.w;}
int main()
{
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n;i++)  p[i]=i;
	for(int i=1;i<=k;i++)  scanf("%d",&a),sg[a]=1;
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&a,&b,&c);
		e[i]={a,b,c};
	}
	sort(e+1,e+m+1,cmp);
	for(int i=1;i<=m;i++)
	{
		int u=e[i].x,v=e[i].y,val=e[i].w;
		int pa=find(u),pb=find(v);
		if(pa!=pb)
		{
			if(sg[pa]&&sg[pb])  ans=val;
			if(sg[pa]||sg[pb])  sg[pa]=sg[pb]=1;
			p[pa]=pb;
		}
	}
	for(int i=1;i<=k;i++)  printf("%d ",ans);
	return 0;
}
```
完结撒花~

---

