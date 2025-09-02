# [ABC236G] Good Vertices

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc236/tasks/abc236_g

$ N $ 頂点の有向グラフがあります。$ N $ 個の頂点はそれぞれ頂点 $ 1 $ 、頂点 $ 2 $ 、$ \ldots $、頂点 $ N $ と呼ばれます。 時刻 $ 0 $ には、このグラフには辺がありません。

$ t\ =\ 1,\ 2,\ \ldots,\ T $ について、時刻 $ t $ に頂点 $ u_t $ から頂点 $ v_t $ への有向辺が追加されます。 （追加される辺が自己ループである場合、すなわち $ u_t\ =\ v_t $ の場合もあります。）

頂点 $ 1 $ から始め「現在いる頂点からちょうど $ 1 $ 本の有向辺をたどって到達できる頂点を $ 1 $ つ選び、選んだ頂点に移動する」ことを**ちょうど** $ L $ 回繰り返して到達できる頂点を「良い頂点」と呼びます。

$ i\ =\ 1,\ 2,\ \ldots,\ N $ について、頂点 $ i $ が良い頂点となる最小の時刻を出力してください。ただし、頂点 $ i $ が良い頂点となる時刻が存在しない場合は、代わりに $ -1 $ を出力してください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 100 $
- $ 1\ \leq\ T\ \leq\ N^2 $
- $ 1\ \leq\ L\ \leq\ 10^9 $
- $ 1\ \leq\ u_t,\ v_t\ \leq\ N $
- $ i\ \neq\ j\ \Rightarrow\ (u_i,\ v_i)\ \neq\ (u_j,\ v_j) $
- 入力はすべて整数

### Sample Explanation 1

時刻 $ 0 $ ではグラフは辺を持ちません。その後、以下の通りに辺の追加が行われます。 - 時刻 $ 1 $ に、頂点 $ 2 $ から頂点 $ 3 $ への有向辺が追加されます。 - 時刻 $ 2 $ に、頂点 $ 3 $ から頂点 $ 4 $ への有向辺が追加されます。 - 時刻 $ 3 $ に、頂点 $ 1 $ から頂点 $ 2 $ への有向辺が追加されます。これによって、頂点 $ 1 $ から頂点 $ 4 $ に $ 1\ \rightarrow\ 2\ \rightarrow\ 3\ \rightarrow\ 4 $ とちょうど $ 3 $ 回の移動で到達できるようになり、頂点 $ 4 $ は良い頂点に変わります。 - 時刻 $ 4 $ に、頂点 $ 3 $ から頂点 $ 2 $ への有向辺が追加されます。これによって、頂点 $ 1 $ から頂点 $ 2 $ に $ 1\ \rightarrow\ 2\ \rightarrow\ 3\ \rightarrow\ 2 $ とちょうど $ 3 $ 回の移動で到達できるようになり、頂点 $ 2 $ は良い頂点に変わります。 - 時刻 $ 5 $ に、頂点 $ 2 $ から頂点 $ 2 $ への有向辺（自己ループ）が追加されます。これによって、頂点 $ 1 $ から頂点 $ 3 $ に $ 1\ \rightarrow\ 2\ \rightarrow\ 2\ \rightarrow\ 3 $ とちょうど $ 3 $ 回の移動で到達できるようになり、頂点 $ 3 $ は良い頂点に変わります。 頂点 $ 1 $ が良い頂点となることはありません。

## 样例 #1

### 输入

```
4 5 3
2 3
3 4
1 2
3 2
2 2```

### 输出

```
-1 4 5 3```

## 样例 #2

### 输入

```
2 1 1000000000
1 2```

### 输出

```
-1 -1```

# 题解

## 作者：_liuyi_ (赞：7)

# 思路
我们设 $f_{ijk}$，表示 $j$ 号点到 $k$ 号点走 $i$ 步所需的最少操作次数，那么转移所需的复杂度为 $O(n^3l)$，$l\le1 \times 10^9$,明显需要优化。

我们考虑用倍增来优化走 $i$ 步，倍增的思想就是不再一步一步的走，而是 $2^i$ 的走，那么状态变为 $f_{ijk}$ 表示 $j$ 号点到 $k$ 号点走 $2^i$ 步所需的最少操作次数，复杂度优化为 $O(n^3\log l)$。

转移方程则为 $f_{ijk}=\min(\max(f_{i-1jp,},f_{i-1pk}))$ $(1\le j,p,k\le n )$。

预处理完了 $f$ 数组后，我们对 $l$ 进行二进制拆分，二进制拆分后对于第 $m$ 位为 $1$，我们就开始走 $2^m$ 步，用 $g_{jp}$ 记录走 $2^m$ 步时， $j$ 到 $p$ 所需的最少操作次数，$v_{jp}$ 表示目前为止 $j$ 到 $p$ 所需的最少操作次数，转移其实差不多 $g_{jp}=\min(\max(v_{jk},f_{ikp}))$ $(1\le j,p,k\le n )$，最后把 $g$ 全部赋值给 $v$。

最后输出时判断一下 $v_{1i}$ 是否为无穷大，是就输出 $-1$ ,否则直接输出即可，具体见代码实现。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for(int i=a;i<=n;i++)
#define per(i,a,n) for(int i=n;i>=a;i--)
#define mem(a, x) memset(a, x, sizeof(a)) 
#define pb push_back
#define SZ(x) ((int)(x).size())
#define debug(x) cout<<#x<<":"<<x<<endl;
typedef long long ll;
typedef pair<int,int> PII;
typedef unsigned long long ull;
typedef double db;
const int N=105,MAXN=31,inf=1<<30;
const int mod=1e9+7;
int n,T,L,f[MAXN][N][N],g[N][N],v[N][N];
inline void init(){//初始化无穷大
	rep(i,0,30)
		rep(j,1,n)
			rep(k,1,n)
				f[i][j][k]=inf,
				v[j][k]=inf;
	rep(i,1,n) v[i][i]=0;//自己到自己距离为0
}
int main(){
	scanf("%d%d%d",&n,&T,&L);
	init();
	rep(i,1,T){
		int u,v;
		scanf("%d%d",&u,&v);
		if(f[0][u][v]==inf) f[0][u][v]=i;
	}
	rep(i,1,30)
		rep(j,1,n)
			rep(k,1,n)
				rep(l,1,n)
					if(f[i-1][j][k]!=inf&&f[i-1][k][l]!=inf)//要不为无穷大才能转移
						f[i][j][l]=min(f[i][j][l],max(f[i-1][j][k],f[i-1][k][l]));
	per(i,0,30){
		rep(j,1,n)
			rep(k,1,n)
				g[j][k]=inf;//g每次都要初始化无穷大
		if((1<<i)&L){
			rep(j,1,n)
				rep(k,1,n)
					rep(l,1,n)
						if(v[j][k]!=inf&&f[i][k][l]!=inf)
							g[j][l]=min(g[j][l],max(v[j][k],f[i][k][l]));
			memcpy(v,g,sizeof(v));//赋值
		}
	}
	rep(i,1,n) printf("%d ",v[1][i]==inf?-1:v[1][i]);
	return 0;
}
```


---

## 作者：Inui_Sana (赞：6)

来点另类思路！

首先考虑暴力地做：发现 $L$ 非常大，于是大概率是要矩阵快速幂，求出最后的邻接矩阵的。如果对暴力处理出所有 $T$ 次操作后的最终矩阵，复杂度为 $O(Tn^2\log L)=O(n^4\log L)$。（其实一开始想到了题解区中的 $O(\frac{n^4\log L}{\omega})$ 做法但是我不觉得能过）

但是你发现一个问题：每次只改变一条边，我们会做很多冗余计算。于是考虑把矩阵乘法计算过程列出来，一开始全是 $0$，后面在某一时刻，某些位置可能会变成 $1$，变成 $1$ 的位置后面也不会变成 $0$，于是可以不用管它了。

于是类似 bfs，我们每次拿出一个新变成 $1$ 的位置，看它会影响其他哪些位置也变成 $1$。类似矩阵乘法，在 $A\times B=C$ 中，如果 $A_{i,k}$ 变化，我们就枚举一个 $j$，看 $B_{k,j}$ 是否为 $1$，如果 $C_{i,j}$ 此时为 $0$ 就改为 $1$ 并 push 进 bfs 的队列中。对矩阵乘法过程中每次运算这么操作即可。

时间复杂度 $O(n^3\log L)$。但是你发现时间复杂度瓶颈在枚举上述 $j$，而矩阵中元素改变的次数只有 $O(n^2\log L)$ 次。而（如果我没想错的话）找能改变的位置显然是一个能用 bitset 维护的操作，使用一些 \_Find\_next 相关即可。再优化一下判断每个点此时是否可达，时间复杂度就降到了 $O(\frac{n^3\log L}{\omega})$。甚至可以直接把 bitset 换成一个 int128，将理论复杂度变为 $O(n^2\log L)$ 然后成功爆标！

但是由于作者比较懒所以还没有实现这个做法，如果你实现了/证伪了这个做法请敲打一下我（

code：

```cpp
int n,m,k,cur=-1,lim,ans[N],c[M];
int a[M][N][N],b[M][N][N];
vector<pii> g[M];
struct node{
	int p,x,y;
	node(int _p,int _x,int _y):p(_p),x(_x),y(_y){}
};
void upd(int u,int v){
	queue<node> q;
	rep(i,0,lim){
		g[i].clear();
	}
	a[0][u][v]=1;
	q.emplace(0,u,v);
	while(q.size()){
		auto [p,x,y]=q.front();
		q.pop();
		g[p].eb(x,y);
		if(p==lim){
			continue;
		}
		rep(i,1,n){
			if(a[p][y][i]&&!a[p+1][x][i]){
				a[p+1][x][i]=1;
				q.emplace(p+1,x,i);
			}
		}
		rep(i,1,n){
			if(a[p][i][x]&&!a[p+1][i][y]){
				a[p+1][i][y]=1;
				q.emplace(p+1,i,y);
			}
		}
	}
	for(auto [x,y]:g[lim]){
		b[0][x][y]=1;
		q.emplace(0,x,y);
	}
	rep(j,1,cur){
		while(q.size()&&q.front().p==j-1){
			auto [p,x,y]=q.front();
			q.pop();
			rep(i,1,n){
				if(a[c[j]][y][i]&&!b[j][x][i]){
					b[j][x][i]=1;
					q.emplace(j,x,i);
				}
			}
		}
		for(auto [x,y]:g[c[j]]){
			rep(i,1,n){
				if(b[j-1][i][x]&&!b[j][i][y]){
					b[j][i][y]=1;
					q.emplace(j,i,y);
				}
			}
		}
	}
}
void Yorushika(){
	read(n,m,k),lim=__lg(k);
	int tmp=k;
	drep(i,lim,0){
		if(tmp>=(1<<i)){
			c[++cur]=i;
			tmp-=1<<i;
		}
	}
	mems(ans,0x3f);
	rep(t,1,m){
		int u,v;read(u,v);
		upd(u,v);
		rep(i,1,n){
			if(b[cur][1][i]){
				ans[i]=min(ans[i],t);
			}
		}
	}
	rep(i,1,n){
		printf("%d ",ans[i]>1e9?-1:ans[i]);
	}
}
signed main(){
	int t=1;
	//read(t);
	while(t--){
		Yorushika();
	}
}
```

upd：喜报，鸽子写完了。现在在最优解上遥遥领先，耗时是第二的 $\frac{1}{3}$ 左右。

code：

```cpp
int n,m,k,cur=-1,lim,ans[N],c[M];
int a[M][N][N],b[M][N][N];
bitset<N> f[M][2][N],g[M][2][N];
vector<pii> vec[M];
struct node{
	int p,x,y;
	node(int _p,int _x,int _y):p(_p),x(_x),y(_y){}
};
void upd(int u,int v){
	queue<node> q;
	rep(i,0,lim){
		vec[i].clear();
	}
	bitset<N> tmp,all;
	all.set();
	a[0][u][v]=1;
	f[0][0][u][v]=f[0][1][v][u]=1;
	q.emplace(0,u,v);
	while(q.size()){
		auto [p,x,y]=q.front();
		q.pop();
		vec[p].eb(x,y);
		if(p==lim){
			continue;
		}
		tmp=f[p][0][y]&(f[p+1][0][x]^all);
		for(int i=tmp._Find_first();i<=n;i=tmp._Find_next(i)){
			a[p+1][x][i]=1;
			f[p+1][0][x][i]=f[p+1][1][i][x]=1;
			q.emplace(p+1,x,i);
		}
		tmp=f[p][1][x]&(f[p+1][1][y]^all);
		for(int i=tmp._Find_first();i<=n;i=tmp._Find_next(i)){
			a[p+1][i][y]=1;
			f[p+1][0][i][y]=f[p+1][1][y][i]=1;
			q.emplace(p+1,i,y);
		}
	}
	for(auto [x,y]:vec[lim]){
		b[0][x][y]=1;
		g[0][0][x][y]=g[0][1][y][x]=1;
		q.emplace(0,x,y);
	}
	rep(j,1,cur){
		while(q.size()&&q.front().p==j-1){
			auto [p,x,y]=q.front();
			q.pop();
			tmp=f[c[j]][0][y]&(g[j][0][x]^all);
			for(int i=tmp._Find_first();i<=n;i=tmp._Find_next(i)){
				b[j][x][i]=1;
				g[j][0][x][i]=g[j][1][i][x]=1;
				q.emplace(j,x,i);
			}
		}
		for(auto [x,y]:vec[c[j]]){
			tmp=g[j-1][1][x]&(g[j][1][y]^all);
			for(int i=tmp._Find_first();i<=n;i=tmp._Find_next(i)){
				b[j][i][y]=1;
				g[j][0][i][y]=g[j][1][y][i]=1;
				q.emplace(j,i,y);
			}
		}
	}
}
void Yorushika(){
	read(n,m,k),lim=__lg(k);
	int tmp=k;
	drep(i,lim,0){
		if(tmp>=(1<<i)){
			c[++cur]=i;
			tmp-=1<<i;
		}
	}
	mems(ans,0x3f);
	rep(t,1,m){
		int u,v;read(u,v);
		upd(u,v);
		rep(i,1,n){
			if(b[cur][1][i]){
				ans[i]=min(ans[i],t);
			}
		}
	}
	rep(i,1,n){
		printf("%d ",ans[i]>1e9?-1:ans[i]);
	}
}
signed main(){
	int t=1;
	//read(t);
	while(t--){
		Yorushika();
	}
}
```

upd2：刚刚发现上面的实际上是 $O(\frac{n^3\log L}{\omega}+n^3)$ 的。这里再来一份 $O(\frac{n^3\log L}{\omega})$ 的。又快了 2ms。

```cpp
int n,m,k,cur=-1,lim,ans[N],c[M];
int a[M][N][N],b[M][N][N];
bitset<N> f[M][2][N],g[M][2][N];
vector<pii> vec[M];
struct node{
	int p,x,y;
	node(int _p,int _x,int _y):p(_p),x(_x),y(_y){}
};
void upd(int u,int v,int t){
	queue<node> q;
	rep(i,0,lim){
		vec[i].clear();
	}
	bitset<N> tmp,all;
	all.set();
	f[0][0][u][v]=f[0][1][v][u]=1;
	q.emplace(0,u,v);
	while(q.size()){
		auto [p,x,y]=q.front();
		q.pop();
		vec[p].eb(x,y);
		if(p==lim){
			continue;
		}
		tmp=f[p][0][y]&(f[p+1][0][x]^all);
		for(int i=tmp._Find_first();i<=n;i=tmp._Find_next(i)){
			f[p+1][0][x][i]=f[p+1][1][i][x]=1;
			q.emplace(p+1,x,i);
		}
		tmp=f[p][1][x]&(f[p+1][1][y]^all);
		for(int i=tmp._Find_first();i<=n;i=tmp._Find_next(i)){
			f[p+1][0][i][y]=f[p+1][1][y][i]=1;
			q.emplace(p+1,i,y);
		}
	}
	for(auto [x,y]:vec[lim]){
		g[0][0][x][y]=g[0][1][y][x]=1;
		if(cur==0&&x==1){
			ans[y]=t;
		}
		q.emplace(0,x,y);
	}
	rep(j,1,cur){
		while(q.size()&&q.front().p==j-1){
			auto [p,x,y]=q.front();
			q.pop();
			tmp=f[c[j]][0][y]&(g[j][0][x]^all);
			for(int i=tmp._Find_first();i<=n;i=tmp._Find_next(i)){
				g[j][0][x][i]=g[j][1][i][x]=1;
				if(j==cur&&x==1){
					ans[i]=t;
				}
				q.emplace(j,x,i);
			}
		}
		for(auto [x,y]:vec[c[j]]){
			tmp=g[j-1][1][x]&(g[j][1][y]^all);
			for(int i=tmp._Find_first();i<=n;i=tmp._Find_next(i)){
				g[j][0][i][y]=g[j][1][y][i]=1;
				if(j==cur&&i==1){
					ans[y]=t;
				}
				q.emplace(j,i,y);
			}
		}
	}
}
void Yorushika(){
	read(n,m,k),lim=__lg(k);
	int tmp=k;
	drep(i,lim,0){
		if(tmp>=(1<<i)){
			c[++cur]=i;
			tmp-=1<<i;
		}
	}
	mems(ans,0x3f);
	rep(t,1,m){
		int u,v;read(u,v);
		upd(u,v,t);
	}
	rep(i,1,n){
		printf("%d ",ans[i]>1e9?-1:ans[i]);
	}
}
signed main(){
	int t=1;
	//read(t);
	while(t--){
		Yorushika();
	}
}
```

以及你也可以尝试严格 $O(n^2\log L)$ 但是并不会快。

```cpp
int n,m,k,cur=-1,lim,ans[N],c[M];
int a[M][N][N],b[M][N][N];
vector<pii> vec[M];
struct node{
	int p,x,y;
	node(int _p,int _x,int _y):p(_p),x(_x),y(_y){}
};
il int lg(__int128 x){
	return x>>60?__lg((ll)(x>>60))+60:__lg((ll)(x&((1ll<<60)-1)));
}
struct Bitset{
	__int128 x;
	Bitset(__int128 _x=0):x(_x){}
	il Bitset operator&(const Bitset &rhs)const{
		return Bitset(x&rhs.x);
	}
	il Bitset operator^(const Bitset &rhs)const{
		return Bitset(x^rhs.x);
	}
	il int get(int p){
		return x>>p&1;
	}
	il void set(int p){
		x|=(__int128)1<<p;
	}
	il int Find_first(){
		if(!x){
			return inf;
		}
		int ret=lg(x&(-x));
		x^=(__int128)1<<ret;
		return ret;
	}
}f[M][2][N],g[M][2][N];
void upd(int u,int v,int t){
	queue<node> q;
	rep(i,0,lim){
		vec[i].clear();
	}
	Bitset tmp,all;
	all.x=((__int128)1<<120)-1;
	f[0][0][u].set(v),f[0][1][v].set(u);
	q.emplace(0,u,v);
	while(q.size()){
		auto [p,x,y]=q.front();
		q.pop();
		vec[p].eb(x,y);
		if(p==lim){
			continue;
		}
		tmp=f[p][0][y]&(f[p+1][0][x]^all);
		for(int i=tmp.Find_first();i<=n;i=tmp.Find_first()){
			f[p+1][0][x].set(i),f[p+1][1][i].set(x);
			q.emplace(p+1,x,i);
		}
		tmp=f[p][1][x]&(f[p+1][1][y]^all);
		for(int i=tmp.Find_first();i<=n;i=tmp.Find_first()){
			f[p+1][0][i].set(y),f[p+1][1][y].set(i);
			q.emplace(p+1,i,y);
		}
	}
	for(auto [x,y]:vec[lim]){
		g[0][0][x].set(y),g[0][1][y].set(x);
		if(cur==0&&x==1){
			ans[y]=t;
		}
		q.emplace(0,x,y);
	}
	rep(j,1,cur){
		while(q.size()&&q.front().p==j-1){
			auto [p,x,y]=q.front();
			q.pop();
			tmp=f[c[j]][0][y]&(g[j][0][x]^all);
			for(int i=tmp.Find_first();i<=n;i=tmp.Find_first()){
				g[j][0][x].set(i),g[j][1][i].set(x);
				if(j==cur&&x==1){
					ans[i]=t;
				}
				q.emplace(j,x,i);
			}
		}
		for(auto [x,y]:vec[c[j]]){
			tmp=g[j-1][1][x]&(g[j][1][y]^all);
			for(int i=tmp.Find_first();i<=n;i=tmp.Find_first()){
				g[j][0][i].set(y),g[j][1][y].set(i);
				if(j==cur&&i==1){
					ans[y]=t;
				}
				q.emplace(j,i,y);
			}
		}
	}
}
void Yorushika(){
	read(n,m,k),lim=__lg(k);
	int tmp=k;
	drep(i,lim,0){
		if(tmp>=(1<<i)){
			c[++cur]=i;
			tmp-=1<<i;
		}
	}
	mems(ans,0x3f);
	rep(t,1,m){
		int u,v;read(u,v);
		upd(u,v,t);
	}
	rep(i,1,n){
		printf("%d ",ans[i]>1e9?-1:ans[i]);
	}
}
signed main(){
	int t=1;
	//read(t);
	while(t--){
		Yorushika();
	}
}
```

---

## 作者：Fan_sheng (赞：1)

来点劣质做法，模拟赛的时候卡常卡了两个小时差点吐血

（本篇复杂度较高，不是官方正解，注意避雷）

---

首先看到这个题面，你马上可以想到 [[TJOI2017]可乐](https://www.luogu.com.cn/problem/P3758) 的经典 trick。

> 设 $A$ 为图的邻接矩阵，$A^k_{i,j}$ 就表示从节点 $i$ 经过 $k$ 步到达节点 $j$ 的方案数。

显然答案具有可二分性，对每个点二分答案，使用矩阵快速幂 check 方案数是否大于 $0$，复杂度 $\mathbb O(n^4\log L\log T)$，非常的寄。

注意到多次询问，那我们直接改成**整体二分**，```solve(S,l,r)``` 表示 $S$ 集合内的点答案区间都在 $[l,r]$ 中。最后分治树上最多只有 $n$ 个叶子，check 一共会进行大约 $(1+2+4+8+\cdots+n)=\mathbb O(n)$ 次，复杂度 $\mathbb O(n^4\log L)$。实际运算次数还会高于这个值的。

回顾之前干的事，我们真的需要精确的方案数吗？需要的只是它是否 $>0$ 而已。假如 $A_{i,j}=\sum B_{i,k}C_{k,j}$，只要存在一个 $k$ 使得 $B_{i,k}>0\land C_{k,j}>0$，就有 $A_{i,j}>0$。

这样，我们把 $C$ 矩阵转置一下，用 $C^R$ 表示，可以直接使用 bitset 对 $B_i,C^R_j$ 求交，有交则 $A_{i,j}>0$。复杂度 $\mathbb O(\frac{n^4\log L}{\omega})$，可以通过本题。

Code

求交时请使用 ```any()``` 成员函数进行判断，```count()``` 之流会被卡爆。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,T,L,x[10003],y[10003],ans[10003];
struct star{
	bitset<101>a[101];
	star(){for(int i=1;i<=n;i++)a[i].reset();}
	friend star operator*(const star&x,const star&y){
		star res,Y;
		for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)if(y.a[i].test(j))Y.a[j].set(i);
		for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)if((x.a[i]&Y.a[j]).any())res.a[i].set(j);
		return res;
	}
};
inline star quickpow(star &a,int b){
	star ans;
	for(int i=1;i<=n;i++)ans.a[i].set(i);
	while(b){
		if(b&1)ans=ans*a;
		a=a*a,b>>=1;
	}return ans;
}
inline void solve(vector<int>&a,int l,int r){
	if(!a.size())return;
	int mid=(l+r)>>1;
	star G;
	for(int i=1;i<=mid;i++)G.a[x[i]].set(y[i]);
	G=quickpow(G,L);
	vector<int>A,B;
	for(int v:a){
		if(l==r)ans[v]=(G.a[1].test(v)?l:-1);
		else G.a[1].test(v)?A.emplace_back(v):B.emplace_back(v);
	}
	if(l==r)return;
	solve(A,l,mid),solve(B,mid+1,r);
}
int main(){
	scanf("%d%d%d",&n,&T,&L);
	for(int i=1;i<=T;i++)scanf("%d%d",&x[i],&y[i]);
	vector<int>tmp;
	for(int i=1;i<=n;i++)tmp.emplace_back(i);
	solve(tmp,1,T);
	for(int i=1;i<=n;i++)printf("%d ",ans[i]);return 0;
}
```


---

## 作者：ctzm (赞：0)

**只会板子也能场切紫！**

前置知识：矩阵乘法、二分、bitset的使用。

---

### 问题陈述

有一个有 $N$ 个节点的有向图，最开始没有边，接下来有 $T$ 次操作，第 $t$ 次加入一条 $u_t$ 到 $v_t$ 的有向边(可能存在自环)。

定义一个节点是好节点当且仅当能从 $1$ 号节点出发经过恰好 $L$ 条边到达该节点。

输出每个节点成为好节点的最少操作次数，如果不能，输出 `?1`。

$1 \le N \le 100$，$1 \le T \le N^2$，$1 \le L \le 10^9$。

---

考虑矩阵乘法的经典 trick：有向图上走恰好/至多 $k$ 条边的最短路/方案数/是否可达……，$k$ 很大的情况下都可以用矩阵乘法来高效解决。[例题：P3758 [TJOI2017] 可乐
](https://www.luogu.com.cn/problem/P3758)。

题目要求我们求解每个节点成为好节点的最少操作次数，可以考虑为每个节点单独求解：枚举次数，然后运行矩阵乘法。节点个数为 $O(N)$，枚举次数需要 $O(N^2)$ 时间，而矩阵乘法需要 $O(N^3 \log L)$ 时间，合计 $O(N^6 \log L)$，难以通过。

由于是不断加边，且要求解最少操作次数，可以考虑二分次数。单调性显然：如果某次操作后可行，那么后面都可行，可以直接使用这次操作的方案（因为后面只加边，不会破坏这种方案）。于是二分次数的时间复杂度变为 $O(\log N^2) = O(\log N)$（注意二者复杂度本质相同，$\log$ 下仅仅是常数区别），合计 $O(N^4 \log L \log N)$，在题目给出的限制条件下依然难以通过。

注意到我们只需要知道走恰好 $k$ 条边后**是否可达**，这意味着我们可以使用 bitset 来加速矩阵乘法。具体来讲是这样的：

- 通常的矩阵乘法是 `c[i][j] = for k sum (a[i][k]*b[k][j])`。
- 这里我们只需要知道走恰好 $k$ 条边后**是否可达**，所以矩阵乘法被简化为 `c[i][j] = for k OR (a[i][k] AND b[k][j])`。也就是所有的 `a[i][k] AND b[k][j]` 或起来。
- 我们先对矩阵 b 进行转置，也就是所有的 `a[i][k] AND b[j][k]` 或起来。
- bitset 支持两个 bitset 进行位运算（等效于给每一位位运算作为结果，但是 bitset 会快上很多），我们只需要知道 `a[i]&b[j]` 是否存在某一位为 1 就好了。这样，这一步的复杂度就从 $O(N)$ 变为 $O(\frac{N}{w})$。我们要计算 $O(N^2)$ 次（最终矩阵有 $O(N^2)$ 的元素），整体复杂度就从 $O(N^3)$ 变为 $O(\frac{N^3}{w})$。

所以合计时间复杂度为 $O(\frac{N^4 \log L \log N}{w})$，其中 $w$ 为计算机位数，可看作 $32$ 或 $64$。这样 $w$ 就和 $\log L$ 抵消了，~~然后 $\log N$ 可以和 AtCoder 的高速评测机抵消，~~[于是就过了](https://atcoder.jp/contests/abc236/submissions/64978882)。

笑点解析：笔者做题时想错复杂度以为是 $O(\frac{N^3 \log L \log N}{w})$ 所以放心写了。但是反正能过警示我们有的时候要~~算错复杂度~~敢于实现代码，你不写永远不知道能不能过。

---

## 作者：zhanghao233 (赞：0)

# 思路
显然的，我们可以用 dp 解决问题，我们很容易地设计出：

$f_{i,j,l}$ 表示 $i$ 到 $j$ 用 $l$ 步的最少操作次数。很明显，时间和空间都不允许我们这么做。

## 优化1
我们考虑题目只用节点 1，所以我们可以优化掉一维。然后转移方程为：

$f_{j,l}=\min(\max(f_{k,l-1},v_{j,k}))$

矩阵加速经常用于优化部分递推式简单且固定的 dp 式子，而且用了矩阵可以进一步优化空间。

$$
\begin{bmatrix} 
f_{1,l-1} \\ f_{2,l-1} \\ ... \\f_{n,l-1}
\end{bmatrix}
\times
\begin{bmatrix} 
t_{1,1} & t_{1,2} & ... & t_{1,n-1} & t_{1,n}\\
t_{2,1} & t_{2,2} & ... & t_{2,n-1} & t_{2,n}\\
\vdots & \vdots & \ddots & \vdots & \vdots \\
t_{n,1} & t_{n,2} & ... & t_{n,n-1} & t_{n,n}
\end{bmatrix}
=
\begin{bmatrix} 
f_{1,l} \\ f_{2,l} \\ ... \\f_{n,l}
\end{bmatrix}
$$

当然我们的**矩阵乘法**得换成 $c_{i,j}=\min(\max (a_{i,k},b_{k,j})),(1\le k \le n)$。

最终算法时间复杂度为 $O(n^3\log L)$。

## 优化2
我们考虑优化数量较大的维数，也就是 $L$。

我们可以使用倍增，也就是：

$f_{i,j,l}$ 表示 $i$ 到 $j$ 用 $2^l$ 步的最少操作次数。

转移方程为：

$f_{i,j,l}=\min(\max(f_{i,k,l-1},f_{k,j,l-1}))$

然后我们为了满足题意要走 $L$ 步，我们就把 $L$ 进行二进制拆分，走有贡献的每一步，显然的我们需要另两个数组，存答案和进行更新，即：

$g_{i,j}=\min(\max(t_{i,k},f_{k,j,l}))$，这里的方程代表我在走，意思就是 $t_{i,k}$ 代表我前面走过的，$f_{k,j,l}$ 代表我现在要走的。最后把 $g$ 复制给 $v$ 即可。

时间复杂度为 $O(n^3\log L)$。

# 后记
其实这就是最短路。

---

## 作者：EastPorridge (赞：0)

$l \le 10^9$ 告诉我们往矩阵快速幂上面靠，我们不妨把时间当作权值。

考虑状态 $f_{v,i}$ 表示从点 $1$ 出发到点 $v$ 拥有长度为 $i$ 的路径需要的最小时间，则有转移

$$f_{v,i} = \min \{\max(f_{u,i-1},w_{u \rightarrow v}) \}$$

$w_{u \rightarrow v}$ 表示 $u$ 到 $v$ 这条边出现的时间，为了满足所有边均出现，所以里面取 $\max$；最小时间，所以外面取 $\min$。

根据伟大之神 Larunatrecy 所述，感觉可以外面二分时间，里面做一个 $\max$ 矩乘，但我们也可以直接做矩乘，

根据 [这个](https://www.cnblogs.com/juruo-zzt/p/16813076.html) 东西，$(Z \cup \infty, \min , \max )$ 构成半环，同时 $(Z \cup \infty, \min)$ 是交换幺半群，$(Z, \max)$ 是半群，所以 $\min ,\max$ 的矩阵乘法之间有结合律，直接上就可以了。

### Code.

```cpp
#include<bits/stdc++.h>
int read()
{
	int x=0; bool f=0; char ch=getchar();
	while(ch < '0' || ch > '9') f|=(ch == '-'),ch=getchar();
	while(ch >= '0' && ch <= '9') x=x*10+(ch^48),ch=getchar();
	return f ? -x : x;
}
using namespace std;
const int imax=0x3f3f3f3f;
int n,m,l;
struct mat
{
	int a[101][101];
	mat() { memset(a,0x3f,sizeof a);}
	mat operator * (const mat &o) const {
		mat res;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				for(int k=1;k<=n;k++)
					res.a[i][j]=min(res.a[i][j],max(a[i][k],o.a[k][j]));
		return res;
	}
} ma;
mat ksm(mat a,int b)
{
	mat s; for(int i=1;i<=n;i++) s.a[i][i]=0;
	while(b) {if(b&1) s=(s*a); a=a*a; b>>=1;}
	return s;
}
int main()
{
	n=read(); m=read(); l=read();
	for(int i=1;i<=m;i++) {int u=read(),v=read(); ma.a[u][v]=min(ma.a[u][v],i);}
	ma=ksm(ma,l);
	for(int i=1;i<=n;i++) printf("%d ",ma.a[1][i] == imax ? -1 : ma.a[1][i]); 
	return 0;
}
```

---

