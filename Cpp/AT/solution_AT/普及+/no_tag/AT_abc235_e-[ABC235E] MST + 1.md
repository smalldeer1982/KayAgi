# [ABC235E] MST + 1

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc235/tasks/abc235_e

$ N $ 頂点 $ M $ 辺の重み付き無向連結グラフ $ G $ が与えられます。$ G $ には自己ループや多重辺が含まれている可能性があります。  
 頂点には頂点 $ 1 $, 頂点 $ 2 $, $ \dots $, 頂点 $ N $ と番号がついています。  
 辺には辺 $ 1 $, 辺 $ 2 $, $ \dots $, 辺 $ M $ と番号がついています。辺 $ i $ は頂点 $ a_i $ と頂点 $ b_i $ を結ぶ重み $ c_i $ の辺です。ここで、$ 1\ \leq\ i\ \lt\ j\ \leq\ M $ を満たすすべての整数の組 $ (i,\ j) $ について $ c_i\ \neq\ c_j $ が成り立ちます。

以下で説明される $ Q $ 個のクエリに答えてください。  
 $ i $ 番目のクエリでは整数の組 $ (u_i,\ v_i,\ w_i) $ が与えられます。ここで、$ 1\ \leq\ j\ \leq\ M $ を満たすすべての整数 $ j $ について $ w_i\ \neq\ c_j $ が成り立ちます。   
 頂点 $ u_i $ と頂点 $ v_i $ を結ぶ重み $ w_i $ の無向辺を $ e_i $ として、$ G $ に $ e_i $ を追加してできるグラフ $ G_i $ を考えます。 このとき $ G_i $ の最小全域木 $ T_i $ は一意に定まることが証明できますが、$ T_i $ に $ e_i $ は含まれるでしょうか？答えを `Yes` あるいは `No` で出力してください。

ここで、クエリの前後で $ G $ は変化しないことに注意してください。言い換えると、クエリ $ i $ で $ G $ に $ e_i $ を追加したグラフを考えたとしても、他のクエリで出てくる $ G $ に $ e_i $ が追加されていることはありません。

 最小全域木とは？ $ G $ の **全域木** とは、$ G $ に含まれるすべての頂点と $ G $ に含まれる辺の一部からなる木のことを言います。  
 $ G $ の **最小全域木** とは、$ G $ の全域木の中で辺の重みの和が最小である木のことを言います。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ N\ -\ 1\ \leq\ M\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ a_i\ \leq\ N $ $ (1\ \leq\ i\ \leq\ M) $
- $ 1\ \leq\ b_i\ \leq\ N $ $ (1\ \leq\ i\ \leq\ M) $
- $ 1\ \leq\ c_i\ \leq\ 10^9 $ $ (1\ \leq\ i\ \leq\ M) $
- $ c_i\ \neq\ c_j $ $ (1\ \leq\ i\ \lt\ j\ \leq\ M) $
- グラフ $ G $ は連結である。
- $ 1\ \leq\ Q\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ u_i\ \leq\ N $ $ (1\ \leq\ i\ \leq\ Q) $
- $ 1\ \leq\ v_i\ \leq\ N $ $ (1\ \leq\ i\ \leq\ Q) $
- $ 1\ \leq\ w_i\ \leq\ 10^9 $ $ (1\ \leq\ i\ \leq\ Q) $
- $ w_i\ \neq\ c_j $ $ (1\ \leq\ i\ \leq\ Q,\ 1\ \leq\ j\ \leq\ M) $
- 入力はすべて整数である。

### Sample Explanation 1

以下では頂点 $ u $ と頂点 $ v $ を結ぶ重み $ w $ の無向辺を $ (u,v,w) $ と表します。 $ G $ を図に表したものを以下に挙げます。 !\[image\](https://img.atcoder.jp/ghi/15ac15edee5a8b055f65192d7323d43b.png) たとえばクエリ $ 1 $ では $ G $ に $ e_1\ =\ (1,3,1) $ を追加したグラフ $ G_1 $ を考えます。$ G_1 $ の最小全域木 $ T_1 $ の辺集合は $ \lbrace\ (1,2,2),(1,3,1),(2,4,5),(3,5,8)\ \rbrace $ であり $ e_1 $ を含みます。よって `Yes` を出力します。

## 样例 #1

### 输入

```
5 6 3
1 2 2
2 3 3
1 3 6
2 4 5
4 5 9
3 5 8
1 3 1
3 4 7
3 5 7```

### 输出

```
Yes
No
Yes```

## 样例 #2

### 输入

```
2 3 2
1 2 100
1 2 1000000000
1 1 1
1 2 2
1 1 5```

### 输出

```
Yes
No```

# 题解

## 作者：MinimumSpanningTree (赞：13)

这题可以使用 $\text{Kruskal}$ 来求解。

如果每次询问都重新求一次最小生成树的话，数据范围太大很明显会超时。所以我们可以考虑离线操作。

首先我们先把 $m+q$ 条边按权值小到大排序。记得把询问的那 $q$ 条标记一下，方便后面判断。

接下来遍历每条边：

* 并查集判断如果这条边的两个结点已经连通，直接跳过。

* 否则进行以下操作：

	* 如果是原来的 $m$ 条边，直接并查集合并两条边。
    
	* 如果是询问的 $q$ 条边，不进行合并操作，遍历到了当前边说明当前边将会是新最小生成树的边，记录下来。
    
最后把询问记录下来结果的输出即可。

```
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
const int N=2e5+100;
int n,m,u,v,d,q,fa[N],cnt;
struct node
{
	int x,y,val,id;
}a[N*2];
bool r[N];
bool cmp(node a1,node a2)
{
	return a1.val<a2.val;
}
int find1(int dx)//并查集查询祖先
{
	return dx==fa[dx]?dx:fa[dx]=find1(fa[dx]);
}
void merge1(int dx,int dy)//并查集合并
{
	int gx=find1(dx),gy=find1(dy);
	if(gx!=gy) fa[gx]=gy;
}
int main()
{
	scanf("%d%d%d",&n,&m,&q);
	for(int i=1;i<=n;i++) fa[i]=i;
	for(int i=1;i<=m;i++) scanf("%d%d%d",&a[i].x,&a[i].y,&a[i].val);
	for(int i=1;i<=q;i++)
	{
		scanf("%d%d%d",&a[m+i].x,&a[m+i].y,&a[m+i].val);
		a[m+i].id=i;//记录当前边的查询编号
	}
	m+=q;
	sort(a+1,a+m+1,cmp);//按边权值从小到大排序
	for(int i=1;i<=m;i++)//Kruskal
	{
		if(find1(a[i].x)!=find1(a[i].y))//两个结点不连通
		{
			//printf("%d %d %d %d\n",a[i].x,a[i].y,a[i].val,a[i].id); 
			if(a[i].id) r[a[i].id]=true;//有查询编号标记，是查询边，有贡献，标记
			else merge1(a[i].x,a[i].y),cnt++;//否则是原来的边，合并
		}
		if(cnt==n-1) break;//最小生成树生成完成
	}
	for(int i=1;i<=q;i++) r[i]?printf("Yes\n"):printf("No\n");//输出查询的记录
	return 0;
}
```

---

## 作者：Enoch006 (赞：6)

### 题目思路：
原图中因为各边权值不同，所以其最小生成树是唯一的。

题目给出另一些边，求加入这些边后最小生成树会不会变化。也就是求如果加入这些边，我们对图做最小生成树时会不会将此边加入最小生成树。

考虑用 Kruskal 求解。

如果遍历到此边，则将他标记但不把它加入最小生成树中（此边是给出的询问边不是原图里的边，我们还需对其他询问边操作）。反之不动即可。

### 题目代码
```cpp
#include<bits/stdc++.h>
#define maxm 1000005
using namespace std;
int n,m,q,sum,vis[maxm],fa[maxm],d[maxm],ans[maxm];
struct node{
	int x,y,z,k;
}a[maxm];
bool cmp(const node &a,const node &b){
	return a.z<b.z;
}
int getfa(int x){
	if(fa[x]==x)return x;
	return fa[x]=getfa(fa[x]);
}
void init(){
	for(int i=1;i<=n;i++){
		fa[i]=i;
	}
}
void mst(){//Kruskal 求解。
	int f1,f2,k=0;
	for(int i=1;i<=m+q;i++){
		f1=getfa(a[i].x);
		f2=getfa(a[i].y);
		if(f1!=f2){
			if(a[i].k>m){//如果是询问边，则对他进行标记。
				ans[a[i].k-m]=1;
			}
			else{//正常原图边。
				fa[f1]=f2;
				k++;
			}
		}
		if(k==n-1){
			break;
		}
	}
	return ;
}
signed main(){
	cin>>n>>m>>q;
	for(int i=1;i<=m+q;i++){
		cin>>a[i].x>>a[i].y>>a[i].z;
		a[i].k=i;//标记每条边是原图边或者是询问边。
	}
	sort(a+1,a+m+q+1,cmp);
	init(); 
	mst();
	for(int i=1;i<=q;i++){
		if(ans[i]==0)cout<<"No\n";
		else cout<<"Yes\n";
	}
    return 0;
} 
```


---

## 作者：XTianShuo (赞：5)

## 思路概述
考虑最小生成树。

显然，若新加的边一定在新图的最小生成树中，那把这条边一定替换掉了原图最小生成树中的一条边。

所以，我们判断新加的边是否一定会在新图的最小生成树中，只需要判断，原图最小生成树中，新加的边的两个端点之间路径的边权最大值是否大于这条新加的边的边权，若大于则一定可以加进去，否则不一定。

## 解法实现
1. 对原图求最小生成树，并建新图。

2. 对于新加的边，在刚刚建立的新图上求两端点之前路径边权最大值（考虑 最近公共祖先或树剖），按照上面的想法判断即可。

## code
代码较丑不喜勿喷。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long
const int N=2e5+10,M=N*2;

int n,m,q;
struct edge{
	int u,v,w;
	bool operator<(const edge &x)	const
	{
		return w<x.w;
	}
}ed[N];
int fa[N];
int h[N],e[M],ne[M],w[M],tot;
int f[N][22],g[N][22],dep[N];

int find(int x)
{
	if(fa[x]==x)	return x;
	return fa[x]=find(fa[x]);
}
void add(int a,int b,int c)
{
	e[++tot]=b;w[tot]=c;ne[tot]=h[a];h[a]=tot;
}
void dfs(int x,int FA)
{
	dep[x]=dep[FA]+1;
	f[x][0]=FA;
	for(int i=1;i<=20;i++)
	{
		f[x][i]=f[f[x][i-1]][i-1];
		g[x][i]=max(g[x][i-1],g[f[x][i-1]][i-1]);
	}
	for(int i=h[x];i;i=ne[i])
	{
		int j=e[i];
		if(j==FA)	continue;
		g[j][0]=w[i];
		dfs(j,x);
	}
}
int get_lca(int a,int b)
{
	if(dep[a]<dep[b])	swap(a,b);
	int ans=0;
	for(int i=20;i>=0;i--)
		if(dep[f[a][i]]>=dep[b])
		{
			ans=max(ans,g[a][i]);
			a=f[a][i];
		}
	if(a==b)	return ans;
	for(int i=20;i>=0;i--)
		if(f[a][i]!=f[b][i])
		{
			ans=max(ans,max(g[a][i],g[b][i]));
			a=f[a][i];b=f[b][i];
		}
	return max(ans,max(g[a][0],g[b][0]));
}

signed main()
{
	scanf("%lld%lld%lld",&n,&m,&q);
	for(int i=1;i<=m;i++)
		scanf("%lld%lld%lld",&ed[i].u,&ed[i].v,&ed[i].w);
	sort(ed+1,ed+1+m);
	for(int i=1;i<=n;i++)	fa[i]=i;
	for(int i=1;i<=m;i++)
	{
		int a=find(ed[i].u),b=find(ed[i].v);
		if(a==b)	continue;
		fa[a]=b;
		add(ed[i].u,ed[i].v,ed[i].w);
		add(ed[i].v,ed[i].u,ed[i].w);
	}
	
	dfs(1,0);
	
	for(int i=1;i<=q;i++)
	{
		int a,b,c;
		scanf("%lld%lld%lld",&a,&b,&c);
		int lca=get_lca(a,b);
		if(lca>c)	printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}

---

## 作者：PineappleSummer (赞：2)

[[ABC235E] MST + 1](https://www.luogu.com.cn/problem/AT_abc235_e)

简单题，套路做多了很快就能想到。

首先将询问离线。把所有边分为原图边和询问边，以 Kruskal 求解最小生成树的方式，按边权从小到大排序。

对于一条边 $(u,v)$，如果 $u$ 和 $v$ 不在一个集合，则可能成为最小生成树上的边。如果该边是原图边，则一定是最小生成上的边，将 $u$ 所在集合与 $v$ 所在集合合并。如果该边是询问边，则说明该边比原图最小生成树上某条边更优，将那条原图边替换掉，可以成为最小生成树上的边，将该边打上 `Yes` 标记。

如果 $(u,v)$ 在同一个集合，则不可能成为最小生成树上的边。若该边是询问边，打上 `No` 标记。

[代码](https://atcoder.jp/contests/abc235/submissions/55715916)，时间复杂度 $O(m\log m)$。

---

## 作者：mzw2006 (赞：2)

### 题目链接
[MST + 1](https://www.luogu.com.cn/problem/AT_abc235_e)

### 思路
这里介绍两种思路:  

基本思路  

首先先求出原图的 MST (Minimum Spanning Tree);  
再考虑 $q$ 次询问，一条边能不能成为最小生成树上的新边。  
**要考虑到**：  
当增加询问的边时，它会与原树边形成一个环，此时就要考虑删去一条边，因为要求 MST ,所以要删去环上最大的一条边，就要判断询问的边是否是最大的，是则不能成为树边，否则可以, 询问之间是独立的,所以不用修改直接累加答案。询问路径上的最大边可以用 LCA + 倍增 ；  
这里就不细讲这一部分，可以对着代码理解。

很巧的方法  

可不可以在建树的的过程中就判断边可不可以成为新树边？  
答案肯定是可以。  
把 $M+Q$ 条边全部存下来，应为既有原图边又有询问的边，所以要存下序号以便判断。  
算法的重点就在 Kruskal 中 ，对 $M+Q$ 条边进行正常的 MST ，当在过程中有条询问的边时-----**编号大于 $M$**, 它在询问时可以成为树边，因为询问间独立，所以也是累加答案但不加入树中。  
两种方法的代码都粘一下。

### 代码

[方法一](https://www.luogu.com.cn/paste/2l6kbabh)

[方法二](https://www.luogu.com.cn/paste/62iqp0za)

---

## 作者：dlzlj_2010 (赞：1)

发现有多组询问，每次询问都跑一遍最小生成树不现实，考虑**离线**。  
先读入所有询问，然后再跑最小生成树，对在最小生成树上的询问边进行**标记**，最后输出即可。

注意事项：  
- 询问边不是持久的，所以不能进行合并。（我就因为这个调了半天）
 
 ## code：
 ```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
const int N=2e5+5,M=4e5+5;//要加上询问边
struct node{
	int u,v,w;
	int id;
}e[M];
bool cmp(node a,node b){
	return a.w<b.w;
}
int n,m,q;
bool ans[N];//最终结果
int fa[N];//并查集
void init(){
	for(int i=1;i<=n;i++){
		fa[i]=i;
	}
}
int find(int x){
	if(fa[x]==x)return x;
	return fa[x]=find(fa[x]);
}
void unionn(int x,int y){
	x=find(x),y=find(y);
	if(x!=y)fa[x]=y;
}
void Kruskal(){
	init();
	sort(e+1,e+1+m+q,cmp);
	for(int i=1;i<=m+q;i++){
		int u=e[i].u,v=e[i].v;
		u=find(u),v=find(v);
		if(u==v)continue;
		if(e[i].id>m)//是询问边
			ans[e[i].id-m]=1;
		else unionn(u,v);
	}
}
int main(){
	cin>>n>>m>>q;
	for(int i=1;i<=m+q;i++){
		int u,v,w;
		cin>>u>>v>>w;
		e[i]={u,v,w,i};
	}
	Kruskal();
	for(int i=1;i<=q;i++){
		cout<<(ans[i]?"Yes":"No")<<'\n';
	}
	return 0;
}

```

---

## 作者：Tang_poetry_syndrome (赞：1)

## [ABC235E] MST + 1
[洛谷题面](https://www.luogu.com.cn/problem/AT_abc235_e) [Atcoder 题面](https://atcoder.jp/contests/abc235/tasks/abc235_e)
### 题目大意
给定一个 $n$ 个点，$m$ 条边的无向连通图，每条边有权值 $c_i$，各不相同。所以，其最小生成树是唯一的。  
有 $q$ 次询问，每次给出一条边：$x_i,y_i,w_i$，表示两端点为 $x_i$ 和 $y_i$，权值为 $w_i$。  
问加入的这条边是否会让改图的最小生成树发生变化。
### 思路
最小生成树板子题。  
这里我们称前 $m$ 条边所构成的最小生成树为原最小生成树，所有边（即 $m+q$ 条边）构成的最小生成树成为全最小生成树。  
利用克鲁斯卡尔算法求全最小生成树。如果在原最小生成树的边未在全最小生成树中遍历完时，在全最小生成树中遍历到了后 $q$ 条边，那么该边即对最小生成树造成影响。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define f(i,j,k) for(register int i=j;i<=k;++i)
using namespace std;
const int N=4e5+10;
int n,m,q,f[N];
bool ans[2*N];
string check(bool x){return (x==true)?"Yes":"No";}
struct node{
	int u,v,w,k;
}a[N];
int finds(int x){return x==f[x]?x:f[x]=finds(f[x]);}
bool cmp(node a,node b){return a.w<b.w;}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>m>>q; 
	for(int i=1;i<=m+q;i++){
		cin>>a[i].v>>a[i].u>>a[i].w;
		a[i].k=i;
		f[i]=i;
	}
	sort(a+1,a+m+q+1,cmp);
	for(int i=1;i<=m+q;i++){
		int u=a[i].u,v=a[i].v,k=0;
		int fu=finds(u),fv=finds(v);
		if(fu!=fv)
			if(a[i].k>m) ans[a[i].k]=1;
			else{f[fu]=fv;k++;}
		if(k==n-1) break;
	}
	for(int i=m+1;i<=q+m;i++)
		cout<<check(ans[i])<<'\n';
	return 0;
}
```
[提交记录](https://atcoder.jp/contests/abc235/submissions/45979912)

---

## 作者：wnsyou (赞：1)

[传送门](https://www.luogu.com.cn/problem/AT_abc235_e)

## 题意

给定一个 $n$ 个点 $m$ 条边的无向连通图，第 $i$ 条边连接 $x_i$ 和 $y_i$，边权为 $c_i$。

有 $Q$ 组询问，每组询问给定三个数 $u_i$、$v_i$ 和 $w_i$，令 $e_i$ 为一条连接 $u_i$ 和 $v_i$ 的无向边，边权为 $w_i$。

对于每组询问，请你判断：对于加入这条边后的图，问其最小生成树中是否包含了这条边，如果是，输出`Yes`，否则输出`No`。

保证题目给定的原图边权两两不同，保证加入的边的边权与原图中的任意一条边都不相同。

**每组询问是独立的，互相不产生影响。**

## 思路

使用**克鲁斯卡尔算法。**

首先这题数据范围不小，直接模拟是肯定不行的。

我们知道，克鲁斯卡尔算法是按边权从小到大排序，然后用并查集判断这条边是否有必要加入最小生成树，而每条边能否加入最小生成树中，取决于**那些边权比这条边小的边**。

同理，每组询问中给出的边，只取决于那些原图中的边权比其小的边。

那么就可以推出一种做法：

- 首先将每个询问给出的边和原图中的边共同记录下来。
- 给所有边按边权从小到大排序。
- 就像普通的最小生成树一样处理，只是那些询问中的边只需要判断、**不需要加入图中**。

最后输出即可。

[我的做法是离线做法，在线做法已经有人讲过了，详见这篇。](https://www.luogu.com.cn/blog/XTianShuo/solution-at-abc235-e)

## Code

```cpp
#include <iostream>
#include <algorithm>

using namespace std;

const int M = 4e5 + 10; // 记得开两倍空间

struct Node {
  int x, y, z, f; // 记录每条边的边权等，f 用来记录是第几次询问的边
  bool operator < (const Node &i) const {
    return z < i.z;
  }
} a[M];

int n, m, q, ans[M], f[M];

int Find (int x) {
  return (f[x] ? f[x] = Find(f[x]) : x);
}

int main(){
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n >> m >> q;
  for (int i = 1; i <= m; i++) {
    cin >> a[i].x >> a[i].y >> a[i].z;
  }
  for (int i = 1; i <= q; i++) {
    cin >> a[i + m].x >> a[i + m].y >> a[i + m].z; // 将所有边记录在一起
    a[i + m].f = i; // 记录是第几次询问
  }
  sort(a + 1, a + m + q + 1);
  for (int i = 1; i <= m + q; i++) {
    if (a[i].f) { // 如果不是原图中的边
      int l = Find(a[i].x), r = Find(a[i].y);
      ans[a[i].f] = (l != r); // 只需判断，不需加入
    } else { // 是原图中的边
      // 克鲁斯卡尔算法
      int l = Find(a[i].x), r = Find(a[i].y);
      if (l != r) {
        f[l] = r;
      }
    }
  }
  for (int i = 1; i <= q; i++) { // 输出
    cout << (ans[i] ? "Yes" : "No") << '\n';
  }
  return 0;
}
```



---

## 作者：FreedomKing (赞：0)

比较板的 Kruskal 做法就能通过。

### 思路

考虑一个很妙的性质，我们可以将所有边混在一起，包括询问的边但要标记一下，然后在跑 Kruskal 时，若某个边是优的，即目前权值最小且加入后不存在环的边，讨论一下它是不是询问的边，若是询问的边即这条边会对最小生成树产生贡献，记录但是**不加入**到树中；若不是询问的边，直接加入就行。

关于做法的正确性问题，因为对于每个询问如果你在选边的过程中选到了，那么就代表它绝对是会被加入到最小生成树中的，这时我们知道答案了直接结束此次询问让下次询问继承现在的状态即可，也就是不加入到最小生成树中，这样的操作是无后效性的。

### AC Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5,mN=1e4+5,mod=1e9+7;
namespace FreedomKing_qwq{};
using namespace FreedomKing_qwq;
namespace FreedomKing_qwq{
	inline int qread(){
#define qr qread()
		int x=0,c=getchar(),t=1;
		while(c<'0'||c>'9'){
			t^=(c=='-');
			c=getchar();
		}
		while(c>='0'&&c<='9'){
			x=(x<<3)+(x<<1)+c-'0';
			c=getchar();
		}
		return (t?x:-x);
	}
	inline void qwrite(int x){
#define qw(_) qwrite(_)
#define qws(_) qw(_),putchar(' ')
#define qwe(_) qw(_),putchar('\n')
		if(x<0) putchar('-'),x=-x;
		if(x>9) qw(x/10);
		putchar(x%10+'0');
		return;
	}
	inline int qpow(int x,int p,int mod){
		x=(p!=0?x:1);
		mod=(mod?mod:LONG_LONG_MAX);
		if(p<0) return qpow(qpow(x,-p,mod),mod-2,mod);
		int t=1;
		while(p>1){
			if(p&1) t=(t*x)%mod;
			x=(x*x)%mod;
			p>>=1;
		}
		return (x*t)%mod;
	}
	//	inline int max(int x,int y){return (x>y?x:y);}
	inline int min(int x,int y){return (x<y?x:y);}
	inline int gcd(int x,int y){return (x%y==0?y:gcd(y,x%y));}
	inline int lcm(int x,int y){return (x/gcd(x,y)*y);}
}
int f[N];
bool ans[N];
inline void init(int x){for(int i=1;i<=x;i++) f[i]=i;return;}
inline int find(int x){return (f[x]==x?x:f[x]=find(f[x]));}
inline void update(int x,int y){x=find(x);y=find(y);f[x]=y;return;}
struct node{
	int u,v,w,q;
}a[N];
bool cmp(node x,node y){return x.w<y.w;}
signed main(){
	int n=qr,m=qr,T=qr;
	init(n);
	for(int i=1;i<=m+T;i++){
		a[i].u=qr;
		a[i].v=qr;
		a[i].w=qr;
		(i>m?a[i].q=i-m:0);
	}
	sort(a+1,a+m+T+1,cmp);
	for(int i=1;i<=m+T;i++){
		if(find(a[i].u)!=find(a[i].v)){
			if(a[i].q) ans[a[i].q]=true;
			else update(a[i].u,a[i].v);
		}
	}
	for(int i=1;i<=T;i++) puts(ans[i]?"Yes":"No");
	return 0;
}
```

---

## 作者：XYQ_102 (赞：0)

## 题目大意
给你一个图 $G$ 含有 $n$ 个顶点和 $m$ 条边，给出 $Q$ 次询问，询问所多输入的边加上原图 $G$ 的最小生成树是否是存在 $e_i$，存在输出 `Yes` 不存在输出 `No`。
## 思路
首先我们可以想到用最简单的方法，在每次询问时都做一次 Kruskal 算法，如果这个边被取到了，那么输出 `Yes`，反之亦然。

但时间复杂度为 $\Theta(Q\times n\times \log n)$，太慢。

因为每个询问是相互独立的，而且询问的边 $e_i$ 对于并查集不会产生影响，所以可以想到只用一次 Kruskal 算法，把所有的边都涵盖上。

在遍历时每条边的处理方法：
- 如果是询问的 $e_i$ 的边
	- 如果 $e_i$ 的所连的两个顶点 $u,v$ 没有连通，则标记为 `Yes`。
    - 如果连通，则标记为 `No`。
- 如果是 $G$ 的边
	- 将两个顶点在并查集内合并。

时间复杂度 $\Theta((n+Q)\times\log(n+Q))$。
## 代码
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>

using namespace std;

const int maxn = 200005;

struct Edge{int u,v,w,Is,num;};
int fa[maxn];
Edge e[maxn*2];
bool ans[maxn];
int n,m,q;
vector<Edge> qe;

bool operator ==(const Edge &a,const Edge &b){return (a.u == b.u && a.v == b.v && a.w == b.w);}

int found(int x){
    return fa[x] == x ? x : fa[x] = found(fa[x]);
}


bool cmp(Edge x,Edge y){
    return x.w < y.w;
}

inline void Init_Onion(){
    for(int x=1;x<=n;x++)    fa[x] = x;
    memset(ans,0,sizeof(ans));
}


int main()
{
    scanf("%d %d %d",&n,&m,&q);
    for(int i=1;i<=m;i++){
        scanf("%d %d %d",&e[i].u,&e[i].v,&e[i].w);
        e[i].Is = 0;
    }

    for(int i=1;i<=q;i++){
        scanf("%d %d %d",&e[m+i].u,&e[m+i].v,&e[m+i].w);
        e[m+i].Is = 1;e[m+i].num = i;
    }

    sort(e+1,e+m+q+1,cmp);
    Init_Onion();

    int k = 0;
    for(int i=1;i<=m+q;i++){
        if(e[i].Is == 1){
            if(found(e[i].v) != found(e[i].u))
                ans[e[i].num] = 1;
            continue;
        }

        int u = e[i].u,v = e[i].v;
        int f = found(u),t = found(v);
        fa[t] = f;
    }

    for(int i=1;i<=q;i++){
        if(ans[i] == 1)
            printf("Yes\n");
        else
            printf("No\n");
    }    
    return 0;
}
```

---

## 作者：linbaicheng2022 (赞：0)

# [ABC235E] MST + 1 题解

[题目传送门](https://www.luogu.com.cn/problem/AT_abc235_e)

## 思路

不难发现，如果新加入的边在最小生成树上，那么原来 $A$ 到 $B$ 的距离一定会因为这条边的加入而更新。

于是我们可以对原图先进行最小生成树，再对于每条新加边的边权与新图中两点的距离比较，如果发现距离发生了变化，就输出 Yes，否则输出 No。

对于求距离，因为数据范围比较大，可以采用倍增 lca 算法求距离。

## 代码

```cpp
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 500010;
int n, m, q, fa[N];
int h[N], e[N], ne[N], w[N];
int dis[N], st[N];
int f[N][22], g[N][22];
int idx = 0;
struct no {
	int x, y, w;
} ed[N];

bool cmp (no a, no b) {
	return a.w < b.w;
}

void add (int a, int b, int c) {
	e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++;
}

int find (int x) {
	if (fa[x] == x) return x;
	return fa[x] = find (fa[x]);
}

void dfs (int x, int FA, int dep) {
	dis[x] = dep;
	f[x][0] = FA;
	
	for (int i = 1; i <= 20; i ++) {
		f[x][i] = f[f[x][i - 1]][i - 1];
		g[x][i] = max (g[x][i - 1], g[f[x][i - 1]][i - 1]);
	}
	
	for (int i = h[x]; i != -1; i = ne[i]) {
		int j = e[i];
		if (j == FA) continue;
		g[j][0] = w[i];
		dfs (j, x, dep + 1);
	}
}

int get_lca (int a, int b) {
	if (dis[a] < dis[b]) swap (a, b);
	
	int res = 0;
	for (int i = 20; i >= 0; i --) {
		if (dis[f[a][i]] >= dis[b]) {
			res = max (res, g[a][i]);
			a = f[a][i];
		}
	}
	
	if (a == b) return res;
	
	for (int i = 20; i >= 0; i --) {
		if (f[a][i] != f[b][i]) {
			res = max ({res, g[a][i], g[b][i]});
			a = f[a][i];
			b = f[b][i];
		}
	}
	
	return max ({res, g[a][0], g[b][0]});
}

void init () {
	for (int i = 1; i <= n; i ++)
		fa[i] = i;
}

int main () {
	memset (h, -1, sizeof h);
	scanf ("%d%d%d", &n, &m, &q);
	
	for (int i = 1; i <= m; i ++) {
		int a, b, c;
		scanf ("%d%d%d", &a, &b, &c);
		ed[i] = {a, b, c};
	}
	
	sort (ed + 1, ed + 1 + m, cmp);
	init ();
	
	for (int i = 1; i <= m; i ++) {
		int a = ed[i].x, b = ed[i].y, w = ed[i].w;
		a = find (a), b = find (b);
		
		if (a != b) {
			fa[a] = b;
			add (ed[i].x, ed[i].y, w);
			add (ed[i].y, ed[i].x, w);
		}
	}
	
	dfs (1, 0, 1);
	
	while (q --) {
		int a, b, c;
		scanf ("%d%d%d", &a, &b, &c);
		int lca = get_lca (a, b);
		
		if (lca > c) printf ("Yes\n");
		else printf ("No\n");
	}
	
	return 0;
}
```

---

## 作者：mz2022 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc235_e)
	
背景：
--------
由于这题是教练 @cicidog 出的，给我们讲的时候也是照着 @XTianShuo 的代讲的，所以代码会有点像。
	
思路：
--------
考虑 kruscal 求最小生成树，显然，判断是否在新的最小生成树中，对于每次询问，就是求他的边权是否大于两端点之间的最大边权，如果大于就会改变最小生成树，反之不会。
	
Code：
--------
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
	const int N = 5e5;
	int n, m, Q, x, y, w, cnt = 0, fa[N], head[N], f[N][55], g[N][55], dep[N];
	struct node {
		int a, b, w;
	} ed[N];
	bool cmp(node p, node q) {
		return p.w < q.w;
	}
	struct no {
		int to, nxt, w;
	} e[N];
	void add(int u, int v, int w) {
		cnt++;
		e[cnt].to = v;
		e[cnt].w = w;
		e[cnt].nxt = head[u];
		head[u] = cnt;
	}
	void init() {
		for (int i = 1; i <= n; i++)fa[i] = i;
	}
	int find(int x) {
		if (x != fa[x])fa[x] = find(fa[x]);
		return fa[x];
	}
	void dfs(int now, int fa, int Dep) {
		dep[now] = Dep;
		f[now][0] = fa;
		for (int i = 1; i <= 20; i++) {
			f[now][i] = f[f[now][i - 1]][i - 1];
			g[now][i] = max(g[now][i - 1], g[f[now][i - 1]][i - 1]);
		}
		for (int i = head[now]; i; i = e[i].nxt) {
			if (e[i].to == fa)continue;
			g[e[i].to][0] = e[i].w;
			dfs(e[i].to, now, Dep + 1);
		}
	}
	int LCA(int a, int b) {
		if (dep[a] < dep[b])swap(a, b);
		int ans = 0;
		for (int i = 20; i >= 0; i--) {
			if (dep[f[a][i]] >= dep[b]) {
				ans = max(ans, g[a][i]);
				a = f[a][i];
			}
		}
		if (a == b)return ans;
		for (int i = 20; i >= 0; i--) {
			if (f[a][i] != f[b][i]) {
				ans = max({ans, g[a][i], g[b][i]});
				a = f[a][i];
				b = f[b][i];
			}
		}
		return max({ans, g[a][0], g[b][0]});
	}
	signed main() {
		//	freopen("d.in", "r", stdin);
		//	freopen("d.out", "w", stdout);
		ios::sync_with_stdio(false);
		cin.tie();
		cout.tie();
		cin >> n >> m >> Q;
		for (int i = 1; i <= m; i++) {
			cin >> ed[i].a >> ed[i].b >> ed[i].w;
		}
		init();
		sort(ed + 1, ed + m + 1, cmp);
		for (int i = 1; i <= m; i++) {
			int a = find(ed[i].a), b = find(ed[i].b);
			if (a == b)continue;
			fa[a] = b;
			add(ed[i].a, ed[i].b, ed[i].w);
			add(ed[i].b, ed[i].a, ed[i].w);
		}
		dfs(1, 0, 1);
		while (Q--) {
			cin >> x >> y >> w;
			int l = LCA(x, y);
			if (l > w)cout << "Yes" << endl;
			else cout << "No" << endl;
		}
		return 0;
	}
```

---

## 作者：CarroT1212 (赞：0)

### 题目大意

给定一个 $N$ 个点 $M$ 条边的简单无向连通图，有边权，且每条边的边权互不相同。现给定 $Q$ 次互相独立的询问，每次询问会给定一条新边（可能与原图中的边重合，但是保证边权不与原图中的任何一条边相同），问加入这条边后的新图的最小生成树是否与原图的最小生成树相同。（$1 \le N,M,Q \le 2\times 10^5$）

------------

### 解法分析

在线做法。

首先考虑什么情况下新图的最小生成树会和原图的不同。

可以发现，加入一条边后，最小生成树如果变化，那只可能是有一条边变为新加的边。因为原图的最小生成树已经是最优情况，由于生成树的种种性质，加一条边不可能使生成树发生较大的变化，题目又保证了边权互不相同，所以尽量保持原生成树的状态肯定是比其它情况都要优的。而且，这条变掉的边只可能在原图最小生成树中新边连接的两个点之间的路径上。因为只有这条路径上的边被删掉，加上新边后生成树才能是连通的。

所以问题就转化为了每次询问给定两个点和一个数 $w_i$，问原图的最小生成树中这两个点之间的路径上是否存在一条边的权值大于 $w_i$。如果有，则把这条边换成新边就是新图的最小生成树了。

我一开始想边权赋给儿子作点权后用树剖杀，但是想到 ABC 的 E 题放树剖是不是有点过于凶残（主要是太长了懒得打），随后在同学的引导下想到了倍增。记录每个点的第 $2^i$ 级祖先和这个点（包括）与第 $2^i$ 级祖先（不包括）之间的路径上的边权的最大值，按照求 LCA 的方法一步步往上跳取个最大值就可以了。其实这么看来很多树剖的题如果没有子树的整体操作的话都能用倍增薄纱。

------------

### 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
#define ld long double
#define pb push_back
#define pii pair<int,int>
#define pll pair<ll,ll>
#define vo void()
using namespace std;
const int N=2e5+7;
struct edge { int x,y,z; } a[N];
int n,m,q,ff[N],b[N],mx[N][21],fa[N][21],dep[N];
vector<int> v[N];
vector<pii> v1[N];
int fnd(int x) { return ff[x]==x?x:ff[x]=fnd(ff[x]); }
void dfs1(int p,int f) {
	dep[p]=dep[f]+1;
	for (pii i:v1[p]) if (i.first!=f)
		v[p].pb(i.first),v[i.first].pb(p),b[i.first]=i.second,dfs1(i.first,p);
}
void dfs2(int p,int f) {
	fa[p][0]=f,mx[p][0]=b[p];
	for (int i=1;i<21;i++)
		fa[p][i]=fa[fa[p][i-1]][i-1],mx[p][i]=max(mx[p][i-1],mx[fa[p][i-1]][i-1]);
	for (int i:v[p]) if (i!=f) dfs2(i,p);
}
int que(int x,int y) {
	int ret=0;
	if (dep[x]<dep[y]) swap(x,y);
	for (int i=20;i>=0;i--) if (dep[x]-dep[y]>=1<<i)
		ret=max(ret,mx[x][i]),x=fa[x][i];
	if (x==y) return ret;
	for (int i=20;i>=0;i--) if (fa[x][i]!=fa[y][i])
		ret=max({ret,mx[x][i],mx[y][i]}),x=fa[x][i],y=fa[y][i];
	ret=max({ret,mx[x][0],mx[y][0]});
	return ret;
}
int main() {
	scanf("%d%d%d",&n,&m,&q);
	for (int i=1;i<=n;i++) ff[i]=i;
	for (int i=1;i<=m;i++) scanf("%d%d%d",&a[i].x,&a[i].y,&a[i].z);
	sort(a+1,a+m+1,[](edge x,edge y){return x.z<y.z;});
	for (int i=1;i<=m;i++) {
		int fx=fnd(a[i].x),fy=fnd(a[i].y);
		if (fx!=fy)
			ff[fx]=fy,v1[a[i].x].pb({a[i].y,a[i].z}),v1[a[i].y].pb({a[i].x,a[i].z});
	}
	dfs1(1,0),dfs2(1,0);
	for (int x,y,z;q--;)
		scanf("%d%d%d",&x,&y,&z),printf(que(x,y)>z?"Yes\n":"No\n");
	return 0;
}
```

---

## 作者：chengning0909 (赞：0)

# abc 235 e

## 题意

给定一个 $n$ 个点，$m$ 条边的无向连通图，每条边有权值 $c_i$，各不相同。

有 $q$ 次询问，每次给出一条边：$x_i, y_i, w_i$

表示两端点为 $x_i$ 和 $y_i$ ，权值为 $w_i$ 

问：加入这条边之后，这条边是否会在新的最小生成树中？

## 思路

### 离线

因为你需要查询这条边是否在新的最小生成树中，所以有这么一种做法：

1. 将原本的 $m$ 条边和查询的 $q$ 条边一起按照权值从小到大排序。

2. 用并查集维护最小生成树，如果当前边是查询边，就查询两个点现在是否连通，如果是原来的边，就直接按照最小生成树的做法写。

### 在线

其实，你要查询一条边是否在最小生成树上，就是看这条边是不是在这两个点联通之前就被枚举到了。

也就是比较这两个点之间的简单路径上的边权的最大值和这条边的权值的大小就可以了。

---

## 作者：ttq012 (赞：0)

首先跑一遍原图的最小生成树，并记录下最小生成树的每一条边。

然后用记录下来的边建图。

由于每一个询问独立，所以对于每一条给出的询问的边，如果他能够成为最小生成树的树边，当且仅当他的权值小于原来这两个点的权值。否则就不能成为。

时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;
map<int,vector<int> >mp;
struct node{
  int a,b,c;
}edge[N];
vector<pair<int,int> >z[N];
int fa[N],dep[N],f[N][20],w[N][20];
void dfs(int u,int fa,int s=0){
  dep[u]=dep[fa]+1;
  f[u][0]=fa;
  for(auto &[j,k]:z[u])
    if(j!=fa){
      w[j][0]=k;
      dfs(j,u,k);
    }
}
int lca(int a,int b){
  if(dep[a]<dep[b])swap(a,b);
  int delta=dep[a]-dep[b],res=0;
  for(int i=0;i<20;i++)
    if(delta&(1<<i))
      res=max(res,w[a][i]),a=f[a][i];
  if(a==b)return res;
  for(int i=19;~i;i--) 
    if(f[a][i]!=f[b][i])
      res=max({res,w[a][i],w[b][i]}),a=f[a][i],b=f[b][i];
  return max({res,w[a][0],w[b][0]});
}
int find(int x){
  return x==fa[x]?x:fa[x]=find(fa[x]);
}
signed main(){
  int n,m,q;
  cin>>n>>m>>q;
  for(int i=1;i<=m;i++)
    cin>>edge[i].a>>edge[i].b>>edge[i].c;
  for(int i=1;i<=n;i++)fa[i]=i;
  sort(edge+1,edge+m+1,[&](const node&lhs,const node&rhs){
    return lhs.c<rhs.c;
  });
  // cout<<"----------------\n";
  for(int i=1;i<=m;i++){
    int a=edge[i].a,b=edge[i].b,c=edge[i].c;
    int ta=find(a),tb=find(b);
    if(ta!=tb){
      // cout<<a<<' '<<b<<' '<<c<<'\n';
      fa[ta]=tb;
      z[a].push_back({b,c});
      z[b].push_back({a,c});
    }
  }
  // cout<<"----------------\n";
  dfs(1,0);
  for(int i=1;i<20;i++)
  for(int j=1;j<=n;j++)
  f[j][i]=f[f[j][i-1]][i-1],w[j][i]=max(w[j][i-1],w[f[j][i-1]][i-1]);
  while(q--){
    int x,y,w;
    cin>>x>>y>>w;
    int calc=lca(x,y);
    // cout<<"calc="<<calc<<'\n';
    if(calc>w)cout<<"Yes\n";
    else cout<<"No\n";
  }
  return 0;
}
```

---

