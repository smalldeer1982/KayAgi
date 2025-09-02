# [USACO21OPEN] Portals G

## 题目描述

Bessie 位于一个由 $N$ 个编号为 $1\dots N$ 的结点以及 $2N$ 个编号为 $1\cdots 2N$ 的传送门所组成的网络中。每个传送门连接两个不同的结点 $u$ 和 $v$（$u≠v$）。可能有多个传送门连接同一对结点。

每个结点 $v$ 与四个不同的传送门相连。与 $v$ 相连的传送门列表由 $p_v=[p_{v,1},p_{v,2},p_{v,3},p_{v,4}]$ 给出。

你的当前位置可以用有序对（当前结点，当前传送门）表示；即一个有序对 $(v,p_{v,i})$
，其中 $1\le v\le N$ 以及 $1\le i\le 4$。你可以使用以下任一操作来改变你的当前位置：

- 1. 由穿过当前传送门来改变当前结点。
- 2. 改变当前传送门。在每一个结点上，列表的前两个传送门是配对的，后两个传送门也是配对的。也就是说，如果你的当前位置是 $(v,p_{v,2})$，你可以转而使用传送门 $(v,p_{v,1})$，反之亦然。类似地，如果你的当前位置是 $(v,p_{v,3})$，你可以转而使用传送门 $(v,p_{v,4})$，反之亦然。没有其他改变传送门的方式（例如，你**不能**从传送门 $p_{v,2}$ 转去传送门 $p_{v,4}$ ）。

总共有 $4N$ 个不同的位置。不幸的是，并不一定每一个位置都可以从另外的每一个位置经过一系列操作而到达。所以，以 $c_v$ 哞尼的代价，你可以以任意顺序重新排列与 $v$ 相邻的传送门列表。在此之后，列表中的前两个传送门互相配对，同时后两个传送门也互相配对。

例如，如果你将与 $v$ 相邻的传送门以 $[p_{v,3},p_{v,1},p_{v,2},p_{v,4}]$ 的顺序重新排列，这意味着如果你位于结点 $v$ ，
- 如果你当前位于传送门 $p_{v,1}$ ，你可以转而使用传送门 $p_{v,3}$，反之亦然。
- 如果你当前位于传送门 $p_{v,2}$ ，你可以转而使用传送门 $p_{v,4}$，反之亦然。
你不再能够从传送门 $p_{v,1}$
转至传送门 $p_{v,2}$，或从传送门 $p_{v,3}$ 转至 $p_{v,4}$ ，反之亦然。

计算修改这一网络使得每一个位置都可以从另外的每一个位置到达所需要花费的哞尼的最小数量。输入保证存在至少一种修改网络的合法方式。 

## 说明/提示

#### 样例解释

重新排列结点 $1$ 和 $4$ 的邻接表就已足够。这需要总计 $c_1+c_4=13$ 哞尼。我们可以使 $p_1=[1,9,4,8]$ 以及 $p_4=[7,4,6,3]$。 

#### 数据范围与约定

$2\le N\le 10^5$，$1\le c_v\le 10^3$。

## 样例 #1

### 输入

```
5
10 1 4 8 9
11 1 2 5 6
12 9 10 2 3
3 4 3 6 7
15 10 8 7 5```

### 输出

```
13```

# 题解

## 作者：lyfqwq (赞：18)

本蒟蒻看到各位大佬的代码都这么的高端大气，那么就由我来一发朴实无华的题解来弥补你谷的空缺吧。

------------
## 【朴实无华的分析】

~~十分显然的~~ 一道 Kruskal 最小生成树题。

题意还是比较容易读懂的，主要就是关于题意转换比较难想，让我们看一下具体操作，究竟发生了些什么。

如以下问题所述：存在两个节点 $pi$ ， 每个节点有 $v_1, v_2, v_3, v_4$  四个传送门， 两个节点的关系如下图。

![](https://cdn.luogu.com.cn/upload/image_hosting/370jrsb2.png)

那么很显然， 你可以从 $p_1v_1$ 进入到达 $p_2v_1, p_2v_2$ 这两个位置, 但是你无法到达 $p_2$ 的另外两个位置。

那么怎么办呢？

没错，就是通过改变传送门的位置从而使所有的位置组成一个连通块。很显然图中存在两个环， 我们需要将它变成一个环，那么就可以达到目的了。

操作完之后大概是这个样子：

![](https://cdn.luogu.com.cn/upload/image_hosting/rw2dyh3l.png)

这样你就会发现，你可以从任意位置出发，到达给定的任意位置，那么我们就达到了目的。

具体实现请看代码 ------------------->

## 【朴实无华的Code】
```
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int N = 1e6 + 5;//数据范围1e6足矣 

int n;
int d, ans;
int f[N>>1];//我们把传送门抽象成点，所以f数组要开2*N 
int p[N][4];//用于存四个传送门的信息 

struct bal {
	int pos;
	int sum;
};
bal t[N];//结构体存点的信息 

int re() {//快读不赘述 
	int x = 0, f = 1;
	char ch = getchar();
	while (ch < '0'||ch > '9') {
		if(ch == '-') f = -1;
		ch = getchar();
	}
	while (ch <= '9'&&ch >= '0') {
		x = x*10+ch-'0';
		ch = getchar();
	}
	return x*f;
}

int find(int x) {//这里提一下，优化后的找父亲 
	while(x != f[x])
	x = f[x] = f[f[x]];//路径压缩与找父亲同步，比递归省时 
	return x;
}

void un(int a, int b) {//合并 
	a = find(a);
	b = find(b);
	f[a] = b;
}

int cmp(bal a, bal b) {//按牟尼数进行排序 
	return a.sum < b.sum;
}

signed main() {
	n = re();
	for(int i = 1; i <= n<<1; i++)//注意要n<<1 
		f[i] = i;
	for(int i = 1; i <= n; i++) {
		t[i].pos = i; t[i].sum = re();
		p[i][0] = re(); p[i][1] = re();
		p[i][2] = re(); p[i][3] = re();
		un(p[i][0], p[i][1]);
		un(p[i][2], p[i][3]);//将已经联通的合并，初始化为多个环
	}
	sort(t + 1, t + n + 1, cmp);//cmp
	for(int i = 1; i <= n; i++) {//经典Kruskal，使所有环联通
		d = t[i].pos;
		int x = find(p[d][0]);
		int y = find(p[d][2]);
		if(x != y) {
			f[y] = x;
			ans += t[i].sum;
		}//这里直接跑完n即可，因为我不会优化... 
	}
	printf("%d\n", ans); 
	return 0;//好习惯哦 
}
```
END
------------
其他一些无关紧要的东西
- 如果您感觉这道题解对您有帮助，请留下您的肯定
- 如果有什么错误的地方，请不要吝啬您的评论
- 还有，目前已知最优解就是本人撒

![](https://cdn.luogu.com.cn/upload/image_hosting/gff927fq.png)

# 欢迎大佬们光顾[我的博客](https://www.luogu.com.cn/blog/beacon/)

---

## 作者：Eibon (赞：4)

将传送门进行连边，最后会形成一些联通块。

目标是将这些联通块都连接在一起。

思考交换操作的意义，发现交换操作会将两个环连在一起，即将两个环所在的联通块连在一起。

那我们就像 kruskal 最小生成树算法一样，将联通块合并在一起即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=4e5+5;
int T=1,n,ans;
int fa[maxn],a[maxn][4];
int get_fa(int x)
{
	return fa[x]==x?x:fa[x]=get_fa(fa[x]);
}
void ins(int u,int v)
{
	int uu=get_fa(u),vv=get_fa(v);
	fa[uu]=vv;
}
struct node
{
	int id,w;
	bool operator < (const node &x) const
	{
		return w<x.w;
	}
};
node c[maxn];
void solve()
{
	scanf("%lld",&n);
	for(int i=1;i<=n*2;i++){
		fa[i]=i;
	}
	for(int i=1;i<=n;i++){
		scanf("%lld%lld%lld%lld%lld",&c[i].w,&a[i][0],&a[i][1],&a[i][2],&a[i][3]);
		ins(a[i][0],a[i][1]);ins(a[i][2],a[i][3]);
		c[i].id=i;
	}
	sort(c+1,c+n+1);
	for(int i=1;i<=n;i++){
		int id=c[i].id;
		int uu=get_fa(a[id][0]);
		int vv=get_fa(a[id][2]);
		if(uu!=vv){
			fa[uu]=vv;
			ans+=c[i].w;
		}
	}
	printf("%lld\n", ans);
}
signed main()
{
//	freopen("1.in","r",stdin);
//	freopen("1.out","w",stdout);
//	scanf("%lld",&T);
	while(T--){
		solve();
	}
	return 0;
}
//dyyyyds
```

---

## 作者：7KByte (赞：4)

题目大意：给个 $2n$ 个点，和 $n$ 个五元组 $(a,b,c,d,e)$，最开始 $a$ 和 $b$ 连边，$c$ 和 $d$ 连边。对于每个五元组，可以花费 $e_i$ 的代价将 $a,b,c,d$ 重新排列，问最小的代价使所有点联通。每个点恰好出现两次。$n\le 10^5$

每个点出现两次表示每个点的度数为 $2$，而联通的图如果每个点的度数为 $2$，则一定是一个环。

如果图不连通，则是若干个环。

现在我们要使得图联通，也就是合并这些环，我们发现花费 $e_i$ 的代价可以将 $a_i,c_i$ 所在环连起来。

所以我们先用并查集维护每个点所在的环，再将环缩成点，每个五元组缩成边，最后跑最小生成树。

时间复杂度$\rm O(N\log N)$

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 200005
using namespace std;
struct node{
	int x,y,val;
	bool operator<(const node o)const{return val<o.val;}
}a[N];
int n,fa[N],val[N],u[N],v[N],x[N],y[N];
int get(int x){return fa[x]==x?x:fa[x]=get(fa[x]);}
int main(){
	scanf("%d",&n);
	rep(i,1,n*2)fa[i]=i;
	rep(i,1,n){
		scanf("%d%d%d%d%d",&val[i],&u[i],&v[i],&x[i],&y[i]);
		fa[get(u[i])]=get(v[i]);
		fa[get(x[i])]=get(y[i]);
	}
	rep(i,1,n){
		a[i].val=val[i];
		a[i].x=get(u[i]);
		a[i].y=get(x[i]);
	}
	rep(i,1,n*2)fa[i]=i;
	sort(a+1,a+n+1);long long ans=0;
	rep(i,1,n){
		if(get(a[i].x)!=get(a[i].y))
			ans+=a[i].val,fa[get(a[i].x)]=get(a[i].y);
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：tiger2005 (赞：3)

请认真读清楚题面后继续往下看。这道题的题面比较难以进行抽象化，所以只能读题面了 qwq

我们考虑到一个状态就是位置加上传送门，但是考虑到对于连接 $u$ 和 $v$ 的传送门 $i$，状态 $(u,i)$ 和 $(v,i)$ 可以互相到达，所以只需要记录传送门作为状态就行，也就是把传送门当作点。

根据题目要求，我们把每一个点第一个传送门和第二个传送门连起来，第三个和第四个连起来。不难发现在 $2N$ 个传送门中连接了 $2N$ 条边，并且一个传送门在两个端点分别连接了一次，度数一定是 $2$。很显然，最后构成的图形就是一些环的集合。

我们考虑修改一个点的传送门顺序，实际上就是把这个图中两条边断开，然后交换起始点拼起来。在两个环上进行考虑，就是把两个环拆成两条线，然后接在一起成为新的环。这实际上将两个连通块连在了一起。

想到了什么？对，我们可以使用最小生成树解决这个问题。我们按照花费从小到大考虑每一个点，如果四个传送门全部连在了一起，那么跳过，否则将它们直接连结在一起。由于前两个和后两个一定在同一个连通块中，这么做就是把两个连通块合并，最后使用并查集维护一下就行了。

具体实现请参考 Kruskal 算法。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;
int N;
int C[100010],A[100010][4];
int fa[200010];
int getF(int x){
	return x==fa[x]?x:fa[x]=getF(fa[x]);
}
inline void merg(int x,int y){
	x=getF(x);y=getF(y);
	fa[x]=y;
}
vector<pair<int,int> > vec;
int main(){
	scanf("%d",&N);
	for(int i=1;i<=2*N;i++)
		fa[i]=i;
	for(int i=1;i<=N;i++){
		scanf("%d%d%d%d%d",&C[i],&A[i][0],&A[i][1],&A[i][2],&A[i][3]);
		merg(A[i][0],A[i][1]),merg(A[i][2],A[i][3]);
	}
	for(int i=1;i<=N;i++)
		vec.push_back(make_pair(C[i],i));
	sort(vec.begin(),vec.end());
	int ans=0;
	for(int i=0,p,x,y;i<N;i++){
		p=vec[i].second;
		x=getF(A[p][0]),y=getF(A[p][2]);
		if(x!=y)	fa[x]=y,ans+=vec[i].first;
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：djh0314 (赞：3)

## 传送门 [P7528 [USACO21OPEN] Portals G](https://www.luogu.com.cn/problem/P7528)
## 题意
有 $2n$ 个点可以通过对应的传送门到另一个点，   
并且可以将一组的传送门消 $c_{i}$，  
将一组的四个传送门以任意序交换。   
求将所有点连通的最小价值。


### 首先观察样例的形成图。
![](https://cdn.luogu.com.cn/upload/image_hosting/0xjim0ib.png)   
不同颜色代表不可互达。

整理一下  
将第 1 列名为 $1\sim n$，  
第 2 列为 $n+1 \sim 2n$，  
......

于是就有了这样的图。
![](https://cdn.luogu.com.cn/upload/image_hosting/vx80fttp.png)

题意还给了一种方式----交换传送门。  
即我们对于第 $i$ 个传送门， 
可以将 $i$ 到 $i+n$ 的边与 $i+2n$  到 $i+3n$ 的边切断，
连接 $i$ 与 $i+2n$ 和 $i+n$ 与 $i+3n$ 的边；  
或  
连接 $i$ 与 $i+3n$  和 $i+n$ 与 $i+3n$  的边。

### 假设对第一组进行交换。
![](https://cdn.luogu.com.cn/upload/image_hosting/6ykqe7in.png)

可以明显观察出有两组环进行了合并。

于是可以想到：
对于第 $i$ 组，如果两个点不在一组中，那么我们就可以用 $c_{i}$ 的代价讲第这两个点所属的环合并。

于是代码的总思路就形成了：
以 $c_{i}$ 与其对应 $id$ 从小到大排序，  
对于排序后的第 $i$ 位，判断其两端是否在一个并查集，否则消耗 $c_{i}$ 合并。


### AC 代码如下
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5+5;
int n, m;
int ans;
int fa[N*2];//并查集
int door[N*2];//门
struct node {
	int val;
	int id;
} d[N];
bool cmp(node a,node b){
	return a.val<b.val;
}
int root(int x) {//并查集find
	return fa[x]=fa[x]==x?x:root(fa[x]);
}
void hb(int a,int b) {//合并两个并查集
	fa[root(a)]=root(b);
}
bool checK(int a,int b) {//看是否在同一并查集
	return root(a)==root(b);
}
signed main() {
	cin>>n;
	for(int i=1; i<=2*n; ++i) {//初始化
		fa[i]=i;
	}
	for(int i=1; i<=n; ++i) {
		int a,b,c,e;
		cin>>d[i].val;d[i].id=i;
		scanf("%d%d%d%d",&a,&b,&c,&e);
		if(door[a]) hb(door[a],i);
		if(door[b]) hb(door[b],i);
		if(door[c]) hb(door[c],i+n);
		if(door[e]) hb(door[e],i+n);
      //合并对应的门
		door[a]=i;
		door[b]=i;
		door[c]=i+n;
		door[e]=i+n;
	}
	sort(d+1,d+n+1,cmp);
	for(int i=1;i<=n;++i){
		if(!checK(d[i].id,d[i].id+n)){
			ans+=d[i].val;
			hb(d[i].id,d[i].id+n);
		}
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：lyt_awa (赞：2)

## 简要题意
有 $4N$ 个点， 输入 $c_v,p_{v,1},p_{v,2},p_{v,3},p_{v,4}$ 表示用一条无向边连接节点 $p_{v,1},p_{v,2}$ 和 $p_{v,3},p_{v,4}$，可以花费 $c_v$ 的代价连接四个节点（说明在思路里面）。求使所有节点连通的最小代价。
## 思路
对于两个节点原先的状态是这样的：  
![](https://cdn.luogu.com.cn/upload/image_hosting/q1yc9yn0.png?x-oss-process=image/resize,m_lfit,h_170,w_225)  
可以交换 $p_{1,2}$ 和 $p_{1,3}$ 然后变成这样：  
![](https://cdn.luogu.com.cn/upload/image_hosting/p7mn6quj.png?x-oss-process=image/resize,m_lfit,h_170,w_225)  
于是点就都连起来了。

所以~~很明显~~是 **Kruskal**。

于是可以先将输入存到结构体里面，在对 $c$ 排序，最后跑一边 Kruskal 就好了（详细见代码）。

------------
代码奉上。
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;

inline int read() {
	int x=0,f=1;
	char ch=getchar();
	for(;!isdigit(ch);ch=getchar())if(ch=='-')f=-f;
	for(;isdigit(ch);ch=getchar())x=(x<<1)+(x<<3)+(ch^48);
	return x*f;
}

int n, ans;

struct node {
	int c, p[4];
	bool operator < (const node &a) {
		return c < a.c;
	}
} v[N];

struct uniset {
	int fa[4 * N];
	void init(int n) {
		for (int i = 1; i <= n; ++i)
			fa[i] = i;
	}
	int find(int x) {
		return fa[x] == x ? x : fa[x] = find(fa[x]);
	}
	void Union(int x, int y) {
		x = find(x); y = find(y);
		fa[x] = y;
	}
} us;

int main() {
	n = read();
	us.init(4 * n);
	for (int i = 1; i <= n; ++i) {
		v[i].c = read();
		v[i].p[0] = read();
		v[i].p[1] = read();
		v[i].p[2] = read();
		v[i].p[3] = read();
		us.Union(v[i].p[0], v[i].p[1]);
		us.Union(v[i].p[2], v[i].p[3]);
	}
	sort(v + 1, v + n + 1);
	for (int i = 1; i <= n; ++i) {
		int f0 = us.find(v[i].p[0]);
		int f2 = us.find(v[i].p[2]);
		if (f0 != f2) {
			ans += v[i].c;
			us.Union(f0, f2);
		}
	}
	printf("%d\n", ans);
	return 0;
}
```
时间复杂度 $\Theta (N\log N)$。

---

## 作者：ZaireEmery (赞：1)

先按题意将传送门之间连边。

显然，每个点度数都为 $2$，这些点构成了一堆环。

考虑对于每个节点 $p_v$，如果 $p(v,0),p(v,1),p(v,2),p(v,3)$ 属于一个环，则一定不需操作。否则，一定可以通过如图的方式将 $p(v,0),p(v,1)$ 和 $p(v,2),p(v,3)$ 所在的环合并为一个大环。

![](https://cdn.luogu.com.cn/upload/image_hosting/fiktu0gw.png)

于是，如果把每个环看成一个点，这题就是一个最小生成树的题目。


```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans;
int c[100010],p[100010][4],fa[400010];
int idx[100010];
vector<int> pos[200010];
int find(int x){
	if(fa[x]==x)
		return x;
	fa[x]=find(fa[x]);
	return fa[x];
}
void merge(int x,int y){
	fa[find(x)]=find(y);
}
bool cmp(int a,int b){
	return c[a]<c[b];
}
signed main(){
	cin>>n;
	for(int i=0;i<4*n;i++)
		fa[i]=i;
	//连边
	for(int i=0;i<n;i++){
		idx[i]=i;
		cin>>c[i];
		for(int j=0;j<4;j++){
			cin>>p[i][j];
			pos[p[i][j]].push_back(i*4+j);
		}
		merge(i*4,i*4+1);
		merge(i*4+2,i*4+3);
	}
	for(int i=1;i<=2*n;i++)
		merge(pos[i][0],pos[i][1]);
	//Kruskal
	sort(idx,idx+n,cmp);
	for(int j=0;j<n;j++){
		int i=idx[j];
		if(find(i*4)!=find(i*4+2)){
			ans+=c[i];
			merge(i*4,i*4+2);
		}
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：cmll02 (赞：1)

先分析一下每次操作实际干了些什么。

显然这些传送门构成了一堆环。

如果一组中的门都在一个环里一定不用操作。

如果不在一个环，操作之后

![](https://cdn.luogu.com.cn/upload/image_hosting/99pu3zla.png)

也就是说两个环合并成了一个环。

那么显然问题变成了求最小生成树。

然后就好了。

```cpp
#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#define int long long
/*char buf[1<<23],*p1=buf,*p2=buf,obuf[1<<23],*O=obuf;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)*/
inline int read()
{
	int num = 0,f=1; char c = getchar();
	while (c<48 || c>57)f=(c=='-'?-1:f),c = getchar();
	while (c >= 48 && c <= 57)num = (num << 3) + (num << 1) + (c ^ 48), c = getchar();
	return num*f;
};
struct Edge{
    int v,nxt;
}e[5000005];
int h[2000005],cnt=1;
inline void addedge(int u,int v)
{
    e[cnt]=(Edge){v,h[u]};
    h[u]=cnt++;
}
int f[2000005],sz[2000005];
inline int find(int x)
{
    return x==f[x]?x:f[x]=find(f[x]);
}
inline int un(int x,int y)
{
    int fx=find(x),fy=find(y);
    if(fx==fy)return 0;
    if(sz[fx]>sz[fy])fx^=fy^=fx^=fy;
    f[fx]=fy,sz[fy]+=sz[fx];
    return 1;
}
struct EDGE{
    int u,v,w;
    int operator<(const EDGE& b)
    {
        return w<b.w;
    }
}E[500005*2];
int w[2000005],a[2000005],b[2000005],c[2000005],d[2000005];
int blo[2000005],ccf;
void dfs(int u,int fa,int B)
{
    blo[u]=B;
    for(int i=h[u];i;i=e[i].nxt)if(blo[e[i].v]==0)dfs(e[i].v,u,B);
}
signed main()
{
	int n=read(),anss=0;
	for(int i=1;i<=n;i++)
    {
        w[i]=read(),a[i]=read(),b[i]=read(),c[i]=read(),d[i]=read();
        addedge(a[i],b[i]);
        addedge(b[i],a[i]);
        addedge(c[i],d[i]);
        addedge(d[i],c[i]);
        f[i]=i,f[i+n]=i+n,sz[i]=1,sz[i+n]=1;
    }
    int B=0,ans=0;
    //puts("/qq");
    for(int i=1;i<=n+n;i++)if(blo[i]==0)dfs(i,0,++B);
    int tot=1;
    for(int i=1;i<=n;i++)
    {
        if(blo[a[i]]!=blo[c[i]])E[cnt++]=(EDGE){blo[a[i]],blo[c[i]],w[i]};
    }
    std::sort(E,E+cnt);
    for(int i=0;i<cnt;i++)
    {
        if(un(E[i].u,E[i].v))ans+=E[i].w;
    }
    printf("%lld\n",ans);
//	for(int i=1;i<=m;i++)printf("%lld/%lld\n",c[i],d[i]);
}
/*
 1 4 
 8 9
 1 2 
 5 6
 9 10 
 2 3
 4 3
  6 7
 10 8
  7 5
*/
```

---

## 作者：tiko_tao (赞：0)

## 题解：P7528 Portals G
[题目链接](https://www.luogu.com.cn/problem/P7528)  
这题其实不难，主要在于思考，最后转化成一个最小生成树模版题。

题目看起来比较复杂，其实跟那个位置是第几个点并没有关系。题目只要求每个**传送门**之间可以互相到达，即**连通**。因此我们只考虑传送门之间的关系即可。

把每个传送门当做一个图上的点，每一行的四个传送门可以按题目说的前后两两连一条**无向边**。当我们把所有输入做完之后，可以发现整个图变成了几个不同的**联通块**。  
题目中的重新排序操作，无非就是把原来在同一个连通块的 $p1$ 和 $p2$ 之间的边拆开， $p3,p4$ 同理，然后把 **$p1$ 所在的联通块**和 **$p3$ 所在的联通块**之间连一条边，那么它们就联通了， $p2,p4$ 同理。

分析完操作，似乎还是很难下手，看看有没有什么性质？

题目中甚至用粗体贴心地标出来了：“且每个传送门出现在**恰好两个结点**的邻接表中”。  
有了这个限制，我们不难发现在我们第一遍做完之后，所有联通块必然是一个**环**。

环说明了什么？

作为一个**由无向边构成的**环，我们删去它**任意**一条边，它内部的结点**依然联通**！  
这个时候，我们会发现，我们任意用一次重排序的操作，两个环之间内部各删去了一条边，然后两个环互相又连上了一条边...

想象一下——  
环还是环，只是变大了。

于是，我们发现这个性质始终成立。一次题目中的重排列操作成为了我们一次合并两个联通块的代价。

欸，这跟最小生成树中两个点连一条边~~有什么区别吗~~不是很像吗？  
至此，本题转化成了最小生成树板子题。

然后你就会发现代码肥肠好写 qwq。

```cpp
#include <bits/stdc++.h>
#define rep(i,a,n) for(int (i)=(a);(i)<=(n);(i)++)
#define pre(i,a,n) for(int (i)=(a);(i)>=(n);(i)--)
#define ull unsigned long long
#define int long long
using namespace std;
const int N = 100000 + 10;
struct node
{
	int c, p1, p2, p3, p4;
}q[N];
int n, ans = 0, cnt = 0;
int fa[N << 1];
bool vis[N << 1];
int find(int x) {return fa[x] == x ? x : fa[x] = find(fa[x]); }
bool cmp(node x, node y) {return x.c < y.c; }
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n;
	rep(i, 1, n << 1) fa[i] = i;
	rep(i, 1, n)
	{
		cin >> q[i].c >> q[i].p1 >> q[i].p2 >> q[i].p3 >> q[i].p4;
		int x = find(q[i].p1), y = find(q[i].p2);
		if (x != y) fa[x] = y;
		x = find(q[i].p3), y = find(q[i].p4);
		if (x != y) fa[x] = y; 
	}
	sort (q + 1, q + 1 + n, cmp);
	rep(i, 1, n << 1)
		if (!vis[find(i)])
			vis[find(i)] = 1, cnt++; //记录联通块总数 
	rep(i, 1, n)
	{
		if (cnt == 1) break;
		int x = find(q[i].p1), y = find(q[i].p3);
		if (x != y) fa[x] = y, cnt--, ans += q[i].c;
	}
	cout << ans << "\n";
	return 0;
}

```

---

## 作者：Naro_Ahgnay (赞：0)

## 题目大意

给定 $n$ 排编号从 $1$ 到 $2n$ 的点，每个编号出现两次，每一排的前两个点和后两个点可以连接，编号相同的点可以连接。可以花费 $c_i$ 的代价重新排列第 $i$ 行点的顺序，求最少的花费使得所有点都连成一片。

## 思路

### step1

首先需要发现的是：最初的图是一堆环的形式。

由此可以推出：**任意两个连在一起的点，它们一定在同一个环中**。

### step2

考虑重新排列第 $i$ 行点的顺序会改变什么。

要想将两个环合并成一个环，肯定需要考虑的是前两个点和后两个点不在一个环的行。

先证明为什么调换前两个点之一和后两个点之一的位置后这一行的四个点会连在一起：

假设这一行的四个点为 $a,b,c,d$，用 $x'$ 表示和点 $x$ 编号相同的点。则 $a$ 和 $b$ 最初连在一起，用 $a-b$ 表示点 $a$ 和 $b$ 直接相连。又由于 $a-a'$,$b-b'$，则 $a'$ 和 $b'$ 在一个环中，用 $a'≡b'$ 表示点 $a'$ 和 $b'$ 间接相连。

将 $b$ 和 $c$ 调换位置，这一行的四个点为 $a,c,b,d$。此时 $a-c$，且仍然有 $a'≡b'$，则 $c-a-a'≡b'-b-d$。这四个点就连在了一起，前两个点和后两个点所处的环也合并了。

所以，**调换前两个点之一和后两个点之一的位置后这一行的四个点会连在一起**。

### step3

由此，我们就将一行的四个点转化成了两个点，代表着两个环。

### step4

此时，最小生成树的形式已经被我们转换出来。

将每一行按照费用 $c_i$ 从小到大排序，用并查集记录点和点是否在一个环中。如果这一行的两个环（看 step3）不是同一个，就将它们合并。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	int c,pa,pb,pc,pd;
}a[100001];
int n,ans,p,q,dn;
int fa[200001];
inline int read()
{
	int x(0);char ch=getchar();
	while(ch<48||ch>57) ch=getchar();
	while(ch>=48&&ch<=57) x=x*10+(ch^48),ch=getchar();
	return x;
}
int fd(int x)
{
	if(fa[x]==x) return x;
	return fa[x]=fd(fa[x]);
}
bool cmp(node x,node y)
{
	return x.c<y.c;
}
int main()
{
//	freopen("magic.in","r",stdin);
//	freopen("magic.out","w",stdout);
	n=read();dn=n<<1;
	for(int i=1;i<=dn;i++) fa[i]=i;
	for(int i=1;i<=n;i++)
	{
		a[i].c=read(),a[i].pa=read(),a[i].pb=read(),a[i].pc=read(),a[i].pd=read();
		fa[fd(fa[a[i].pa])]=fd(fa[a[i].pb]),fa[fd(fa[a[i].pc])]=fd(fa[a[i].pd]);
	}
	sort(a+1,a+1+n,cmp);
	for(int i=1;i<=n;i++)
	{
		p=fd(fa[a[i].pa]),q=fd(fa[a[i].pc]);
		if(p!=q) fa[p]=q,ans+=a[i].c;
	}
	printf("%d",ans);
	return 0;
}
```



---

## 作者：huayucaiji (赞：0)

## 解题思路

 这个题目不是很复杂。我们可以先以每个状态为一个点建图，若两个状态可以相互到达，就可以连一条边。我们的任务就是让这张图联通。

容易发现，每个点的度都为 $2$，结合题目，我们知道这张图一定是若干个不相交的环组成的。那么想要让这些换相交，我们就需要加一些边，也就是通过改变传送门顺序。

比如说现在有一个点 $i$，$(i,p_2)$ 和  $(i,p_3)$ 这两个点不连通，我们就需要改变一下顺序，将 $(i,p_2),(i,p_3)$ 连起来，$(i,p_1),(i,p_4)$，那么两个环就连起来了。这个操作的花费是 $c_i$ 块钱。

因此，我们很容易想到 ```Kruskal```，我们对所有 $c_i$ 排序，然后查是否需要连这条边即可。

时间复杂度 $O(n\log n)$​。

## 代码

```cpp
//Don't act like a loser.
//This code is written by huayucaiji
//You can only use the code for studying or finding mistakes
//Or,you'll be punished by Sakyamuni!!!
#include<bits/stdc++.h>
using namespace std;

int read() {
	char ch=getchar();
	int f=1,x=0;
	while(ch<'0'||ch>'9') {
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		x=x*10+ch-'0';
		ch=getchar();
	}
	return f*x;
}

const int MAXN=1e5+10; 

int n;
int father[MAXN<<2],a[MAXN<<1][3],cnt[MAXN<<1];

int node(int i,int j) {
	return (i-1)*4+j;
}
int find(int x) {
	if(father[x]!=x) {
		father[x]=find(father[x]);
	}
	return father[x];
}

struct coin {
	int val,id;
}c[MAXN];
bool cmp(coin a,coin b) {
	return a.val<b.val;
}

signed main() {
	cin>>n;
	
	for(int i=1;i<=n*4;i++) {
		father[i]=i;
	}
	
	for(int i=1;i<=n;i++) {
		c[i].val=read();c[i].id=i;
		for(int j=1;j<=4;j++) {
			int x=read();
			a[x][++cnt[x]]=node(i,j);
		}
		for(int j=1;j<=3;j+=2) {
			int u=node(i,j),v=node(i,j+1);
			u=find(u);v=find(v);
			father[u]=v;
		}
	}
	
	for(int i=1;i<=2*n;i++) {
		int u=a[i][2],v=a[i][1];
		u=find(u);v=find(v);
		father[u]=v;
	}
	
	sort(c+1,c+n+1,cmp);
	
	int	ans=0;
	for(int i=1;i<=n;i++) {
		int u=node(c[i].id,1),v=node(c[i].id,3);
		u=find(u);v=find(v);
		if(u!=v) {
			ans+=c[i].val;
			father[u]=v;
		}
	}
	
	cout<<ans<<endl;
	return 0;
}


```

---

## 作者：Thunder_S (赞：0)

[可能更好的阅读体验。](https://www.cnblogs.com/Livingston/p/15141201.html)

## Solution

首先由于初始状态下 1、2 号传送门和 3、4 号传送门是不通的，因此把一个点拆成两个点。

由于每个点的度都为 2，因此易证所有连通块都是环。

最终的情况就是所有点组成一个大环。

如何将两个环合并呢？

可以将原点和拆点连起来！这代表着更改此点的顺序。

同时将原点和拆点连起来是可以保证正确的，因为原点和拆点都可以各保留一个点，连上对方的剩余点，这样就成功的将两个环合并。

那么最小的代价，可以将每个 $c_v$ 从小到大排序，然后按顺序依次合并环，是否在一个环上可以用并查集。

本人有点傻，直接打了最小生成树，也是可以的。

## Code

```cpp
#include<cstdio>
#include<algorithm>
#define N 200005
using namespace std;
struct node
{
	int x,y,v;
}edge[N*10];
int n,m,ans,c[N],x1[N],x2[N],x3[N],x4[N],f[N<<1];
bool bj[N<<1];
bool cmp(node x,node y) {return x.v<y.v;}
int find(int x)
{
	if (f[x]!=x) f[x]=find(f[x]);
	return f[x];
}
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;++i)
	{
		scanf("%d%d%d%d%d",&c[i],&x1[i],&x2[i],&x3[i],&x4[i]);
		if (!bj[x1[i]]) edge[x1[i]].x=i,bj[x1[i]]=true;
		else edge[x1[i]].y=i;
		if (!bj[x2[i]]) edge[x2[i]].x=i,bj[x2[i]]=true;
		else edge[x2[i]].y=i;
		if (!bj[x3[i]]) edge[x3[i]].x=i+n,bj[x3[i]]=true;
		else edge[x3[i]].y=i+n;
		if (!bj[x4[i]]) edge[x4[i]].x=i+n,bj[x4[i]]=true;
		else edge[x4[i]].y=i+n;
	}
	m=2*n;
	for (int i=1;i<=n;++i)
		edge[++m].x=i,edge[m].y=i+n,edge[m].v=c[i];
	for (int i=1;i<=2*n;++i)
		f[i]=i;
	sort(edge+1,edge+1+m,cmp);
	for (int i=1;i<=m;++i)
	{
		int x=find(edge[i].x),y=find(edge[i].y);
		if (x!=y)
		{
			ans+=edge[i].v;
			f[x]=y;
		}
	}
	printf("%d\n",ans);
	return 0;
}
```



---

## 作者：White_gugu (赞：0)

题意
-

对于每一个点 $i$ ，都有与之相连的传送门 $v_{i,1},v_{i,2},v_{i,3},v_{i,4}$ ，两个点当传送门分别与这两个点连接时则可以互相到达，而只有位置 $1,2$ 的传送门可以互相使用，位置 $3,4$ 的传送门可以互相使用，每一个点 $i$ 都可以用 $c_{i}$ 的代价使四个传送门重新调整顺序，求用最小的代价使每一个点互相可达。

方法
-
因为只有传送门 $1,2$ 可以互相可达和 $3,4$可以互相可达，所以我们可以考虑将每一个点都拆为两个点(设为 $i$ 和 $i+n$ )，分别与传送门 $v_{i,1},v_{i,2}$ 连接和传送门 $v_{i,3},v_{i,4}$ 连接，经过手玩样例，可以发现经过拆点构成的图一定是由众多环构成的。

调整顺序意味着将 $i$ 和 $i+n$ 连通，组合成一个新的大环，但是会不会对原来的环的连通性产生影响呢？明显不会，因为构成的环是由两个传送门进行依次连接的，而每次调整顺序都只是将其中一个传送门断掉，连另外的点的环（另外的也如此），这样又能拼成一个首尾相接的大环了。

![](https://cdn.luogu.com.cn/upload/image_hosting/uvia6ma3.png)

如图，红色边为调整顺序后的边，依旧构成环。

所以把每一个环看作一个大点，将旧点和新点所在的环用代价为调整顺序的代价的边连接，做一遍最小生成树即可。

代码
-
```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
struct node{
	int s,t;
	long long val;
}p[200200];
int n;
long long c[200200];
int v[100100][5];
int last[200200];
int head[400400];
int to[400400];
int next[400400];
int fa[400400];
int cnt=0;
bool vis[400400];
int color[400400];
int tot=0,ans;
void xx(int u,int v)
{
	to[cnt]=v;
	next[cnt]=head[u];
	head[u]=cnt;
	cnt++;
}
void find(int x,int col)
{
	vis[x]=1;
	color[x]=col;
	for(int i=head[x];i!=-1;i=next[i])
	{
		int y=to[i];
		if(!vis[y])
		find(y,col);
	}
}
bool cmp(node x,node y)
{
	return x.val<y.val;
}
int getf(int x)
{
	if(fa[x]==x) return x;
	fa[x]=getf(fa[x]);
	return fa[x];
}
void hb(int x,int y)
{
	fa[getf(x)]=getf(y);
	fa[x]=getf(x);
}
int main()
{
	memset(head,-1,sizeof(head));
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&c[i]);
		int pop=i;
		for(int j=1;j<=4;j++)
		{
			if(j==3)
			pop+=n;
			scanf("%d",&v[i][j]);
			if(last[v[i][j]])
		    {
		    	xx(last[v[i][j]],pop);
		    	xx(pop,last[v[i][j]]);
//		    	printf("%d %d %d %d\n",i,j,last[v[i][j]],pop);
			}
			else
			last[v[i][j]]=pop;
		}
	}
	for(int i=1;i<=2*n;i++)
	{
		if(!vis[i])
		{
			tot++;
			find(i,tot);
		}
	}
//	for(int i=1;i<=2*n;i++)
//	printf("%d %d\n",i,color[i]);
	for(int i=1;i<=n;i++)
	p[i].s=color[i],p[i].t=color[i+n],p[i].val=c[i];
	sort(p+1,p+n+1,cmp);
	int now=0,kkk=1;
	for(int i=1;i<=tot;i++)
	fa[i]=i;
//	for(int i=1;i<=n;i++)
//	printf("%d %d %d\n",p[i].s,p[i].t,p[i].val);
	while(now!=tot-1)
	{
		int p1=p[kkk].s,p2=p[kkk].t;
		if(getf(p1)==getf(p2))
		{
			kkk++;
			continue;
		}
		else
		{
			ans+=p[kkk].val;
			kkk++;
			now++;
			hb(p1,p2);
		}
	}
	printf("%d",ans);
}
```




---

