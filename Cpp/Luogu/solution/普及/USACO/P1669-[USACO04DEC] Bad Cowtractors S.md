# [USACO04DEC] Bad Cowtractors S

## 题目描述

奶牛贝茜被雇去建设 $N(2\le N\le 10^3)$ 个牛棚间的互联网。她已经勘探出 $M(1\le M\le 2\times 10^4)$ 条可建的线路，每条线路连接两个牛棚，而且会花费 $C(1\le C\le 10^5)$。农夫约翰吝啬得很，他希望建设费用最少甚至他都不想给贝茜工钱。贝茜得知工钱要告吹，决定报复。她打算选择建一些线路，把所有牛棚连接在一起，让约翰花费最大。但是她不能造出环来，这样约翰就会发现。

## 说明/提示

$2\le N\le 10^3$，$1\le M\le 2\times 10^4$，$1\le C\le 10^5$。

## 样例 #1

### 输入

```
5 8
1 2 3
1 3 7
2 3 10
2 4 4
2 5 8
3 4 6
3 5 2
4 5 17```

### 输出

```
42```

# 题解

## 作者：ForMyDream (赞：4)

## P1669 P1669 [USACO04DEC] Bad Cowtractors S

**[题目传送门](https://www.luogu.com.cn/problem/P1669)**

题意简化：在一个有 $N$ 个点 $M$ 条边的图中选出 $N-1$ 条边构成一棵树，使得树的总边权最大，求最大总边权。

上述问题即为最小/大生成树问题，本题为最大生成树，如有未详者可以移步 [P3366](https://www.luogu.com.cn/problem/P3366)。

该问题一般是 Kruskal 和 Prim 算法，下面提供代码。

- Kruskal 算法基于排序后的贪心，以并查集确保其正确性。复杂度 $O(m \log m)$ 该算法一般用得更多，性能更好。
- Prim 算法更像是 Dijkstra，通过一个类似于松弛的操作（但严格来说不是松弛）不断更新入树路径。复杂度 $O(n^2)$ 在稠密图中有应用。
- 注意这个图可能是不连通的，最后要判断是否选中了 $N-1$ 条边。
- 经试，这道题并没有必要开 long long，似乎有两篇题解写错了。
- **警钟：如果您使用的是邻接矩阵，加边时注意判定边的大小，因为有边权不同的重边，如果不考虑，就会出现[这样的结果](https://www.luogu.com.cn/record/111631408)，具体处理方式参见“Prim 版代码”。**

### Kruskal 版
```cpp
// 2023/5/30 Author:ForMyDream
#include<iostream>
#include<algorithm>
#define maxn 20001
//#define int long long
using namespace std;
int n,m,head[maxn],cnt,fa[maxn],ans,tot;
struct Edge{ int u,v,nxt,w; }edge[maxn];
bool cmp(Edge a,Edge b){ return a.w>b.w; }
void add(int u,int v,int w){ 
	edge[++cnt].v=v,edge[cnt].u=u,edge[cnt].w=w,
	edge[cnt].nxt=head[u],head[u]=cnt; 
}
int find(int x){ return x==fa[x] ? x : fa[x]=find(fa[x]); }
int merge(int x,int y){	
	int fx=find(x),fy=find(y);fa[fx]=fa[fy]; 
}
void Kruskal(){
	sort(edge+1,edge+m+1,cmp);
	for (int i=1;i<=m;i++){
		int fu=find(edge[i].u),fv=find(edge[i].v);
		if (fu==fv) continue;
		merge(fu,fv);
		ans+=edge[i].w,tot++;
//		printf("选中%d-%d\n",edge[i].u,edge[i].v);
	}
} 
signed main(){
	cin>>n>>m; int u,v,w;
	for (signed i=1;i<=m;i++){ cin>>u>>v>>w; add(u,v,w); }
	for (signed i=1;i<=n;i++) fa[i]=i;
	Kruskal();
	if (tot!=n-1) cout<<-1;
	else cout<<ans;
	return 0;
}


```

### Prim 版
```cpp
// 2023/5/30
#include<iostream>
#define maxn 2001
using namespace std;
int g[maxn][maxn],n,m,dis[maxn],ans,vis[maxn];
// 邻接矩阵   到最大生成树的距离(不是到根的距离)      是否在最大生成树中 
bool Prim(){
	for (int i=2;i<=n;i++) dis[i]=g[i][1]; // 因为以 1 为根 所以初始化为到 1 的距离
	for (int i=1;i<n;i++){ // (若联通)还需要找 N-1 个点 
		int id=-1,maxi=-114;
		for (int j=2;j<=n;j++){
			if (!vis[j]&&dis[j]>maxi){
				id=j,maxi=dis[j];
			}
		} 
//		cout<<id<<'\n';
		if (id==-1) return false; // 如果一个点都没选中->不连通 
		vis[id]=1; ans+=dis[id];
		for (int j=1;j<=n;j++){ // 类似于松弛操作：更新距离 
			dis[j]=max(g[id][j],dis[j]); 
		}
	} 
	return true;
}
int main(){
	cin>>n>>m; int u,v,w;
	for (int i=1;i<=n;i++){
		for (int j=1;j<=n;j++){
			g[i][j]=g[j][i]=-114;
		}
	}
	for (signed i=1;i<=m;i++){ cin>>u>>v>>w; g[u][v]=g[v][u]=max(w,g[u][v]); }
	if (!Prim()) cout<<-1;
	else cout<<ans;
	return 0;
}

```
### 记录：
[Kruskal 54ms](https://www.luogu.com.cn/record/111619164)   
[Prim 82ms](https://www.luogu.com.cn/record/111631443)   
本题为稀疏图，Kruskal 性能优于 Prim。

2023 年 5 月 30 日

---

## 作者：technopolis_2085 (赞：4)

分析：

1. 贝茜要选出一些铁路，把所有牛棚连在一起。
2. 选出的铁路不能有环。

所以选出的铁路构成一个生成树。

题目说了要求最大值，所以本题要求最大生成树。

然后做一遍 kruskal 就行了。

记得开 long long。

code：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=200010;
#define int long long
int fa[maxn];

struct node{
	int a,b,c;
};

node s[maxn];

int find(int x)
{
	if (fa[x]==x)
		return x;
	
	fa[x]=find(fa[x]);
	return fa[x];
}

bool cmp(node x,node y)
{
	return x.c>y.c;
}
signed main()
{
		
	int n,m;
	scanf("%lld%lld",&n,&m);
	
	for (int i=0;i<m;i++)
		scanf("%lld%lld%lld",&s[i].a,&s[i].b,&s[i].c);
		
	for (int i=1;i<=n;i++)
		fa[i]=i;
	 
	sort(s,s+m,cmp);
	int ret=0,cnt=0;
	
	for (int i=0;i<m;i++)
	{
		int ta=find(s[i].a);
		int tb=find(s[i].b);
		
		if (ta!=tb)
		{
			fa[ta]=tb;
			cnt++;
			ret+=s[i].c;
			
		}
	}
	
	if (cnt!=n-1)
		printf("-1");
	else
		printf("%lld",ret); 
	
	return 0;
}
```


---

## 作者：2021changqing52 (赞：2)

#### 分析 ：
1. 这些铁路要把所有的牛棚连在一起；

2. 铁路不能有环。

这就是一个生成树，题目里说要花费最大，也就是说求最大生成树的权值和，跑一遍 Kruskal 就行了，注意排序时要降序排。

#### Code ：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,fa[1005],ans,cnt;
struct edge{
	int u,v,w;
}e[20005];
bool cmp(edge a,edge b){
	return a.w>b.w;//降序排序
}
int find(int x){
	return x==fa[x]?x:fa[x]=find(fa[x]);
}
void merge(int x){
	int fax=find(e[x].u),fay=find(e[x].v);
	if(fax!=fay)fa[fax]=fay,ans+=e[x].w,cnt++;
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++)cin>>e[i].u>>e[i].v>>e[i].w;
	for(int i=1;i<=n;i++)fa[i]=i;
	sort(e+1,e+m+1,cmp);
	for(int i=1;i<=m&&cnt<n-1;i++)merge(i);
	if(cnt==n-1)cout<<ans;
	else cout<<-1;
	return 0;
} 
```

---

