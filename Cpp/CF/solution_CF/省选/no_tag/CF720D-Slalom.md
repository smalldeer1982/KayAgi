# Slalom

## 题目描述

Little girl Masha likes winter sports, today she's planning to take part in slalom skiing.

The track is represented as a grid composed of $ n×m $ squares. There are rectangular obstacles at the track, composed of grid squares. Masha must get from the square $ (1,1) $ to the square $ (n,m) $ . She can move from a square to adjacent square: either to the right, or upwards. If the square is occupied by an obstacle, it is not allowed to move to that square.

One can see that each obstacle can actually be passed in two ways: either it is to the right of Masha's path, or to the left. Masha likes to try all ways to do things, so she would like to know how many ways are there to pass the track. Two ways are considered different if there is an obstacle such that it is to the right of the path in one way, and to the left of the path in the other way.

Help Masha to find the number of ways to pass the track. The number of ways can be quite big, so Masha would like to know it modulo $ 10^{9}+7 $ .

The pictures below show different ways to pass the track in sample tests. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF720D/2ddedad82f8f5e28a322fd1fe426b1600d8a03dd.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF720D/c0dbe07c720846d8b66f7c06424a8cfd200c6af3.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF720D/f511984d971426f2757dbb61173a665800b3ee08.png)

## 样例 #1

### 输入

```
3 3 0
```

### 输出

```
1
```

## 样例 #2

### 输入

```
4 5 1
2 2 3 4
```

### 输出

```
2
```

## 样例 #3

### 输入

```
5 5 3
2 2 2 3
4 2 5 2
4 4 4 4
```

### 输出

```
3
```

# 题解

## 作者：jun头吉吉 (赞：14)

# CF720D 【Slalom】
## 题意
一个 $n \times m$的网格，其中有$k$个矩形障碍，保证这些障碍不重叠。问你从$(1,1)$走到$(n,m)$，每步只能往右或往上走，不经过任何障碍的不同方案数。

**两种方案被视为不同，当且仅当存在一个障碍，它在第一种方案里被从右侧绕过，而在第二种方案里被从左侧绕过**。

方案数对$10^9+7$取模
## 题解
这是一个灰常厉害的题目，~~厉害到看了题解还是云里雾里，对着代码懵逼了半天才看懂~~

首先，这个**不同**的定义与我们平常接触到的**略有**不同。我们平常用$f_{i,j}$来dp的思路似乎不太可行。于是下面有本题第一个非常重要的转化：只记录**最低的路径**上的方案数。那么样例就是长这样的：

![](https://cdn.luogu.com.cn/upload/image_hosting/3z0dllsq.png)

- 一条**最低的路径**指的是在所有相同的路径中所有点都最低的。如绿色就是一条最低的路径，而紫色就不是。可以证明，**最低的路径**的条数就等于方案数

~~至于为什么竖的没有更新本人才疏学浅解释不清楚还是留给大家自己思考吧~~

最后的答案即为$2+1=3$。

先来讲一讲这个东西是如何得到的：
1. 如果当前列没有新矩形，那么$f_{i,j}=f_{i-1,j}$
2. 如果加入了新矩形，那么新矩形的上方一列会产生新的**最低的路径**，那第$4$列第$5$行举例。
![](https://cdn.luogu.com.cn/upload/image_hosting/6i8da0vf.png)
$2$实际上就是两个一之和。那我们举一个更大的例子

![](https://cdn.luogu.com.cn/upload/image_hosting/imqg6w8t.png)

那么$b$就是从$x,y,z$转移过来，与$a$半毛钱关系都没有。于是我们设矩形从$y1$到$y2$，那么就有：
$$f_{i,x}=0,x\in[y1,y2]$$
$$f_{i,y2+1}=\sum_{x=low}^{y2+1}f_{i-1,x}\ (low\text{为从从y2下去能到的最远距离})$$

那么现在我们的时间复杂度为$O(nm^2)$，空间复杂度为$O(n)$，考虑优化。

首先，考虑此算法的瓶颈在哪里。主要还是两个地方：
1. 求出 $low$
2. 求 $\sum_{x=low}^{y2+1}f_{i-1,x}$

第二个东西求和用线段树维护十分简单。第一个东西就有点神奇了。

我们用一个`set`来存储当前所有覆盖的线段。那么我们就可以找到最大（指按`pair`的排序方法）的一条第一条线段。那么$low$就可以取他的 $y2+1$ 。可能 $y2+1$ 并不是最远距离。看下面一张图片来理解一下：

![](https://cdn.luogu.com.cn/upload/image_hosting/7le9p8a8.png)

两个之间的 $f$ 值必定是 $0$ ，因此不会影响 $dp$。

于是我们高高兴兴的打了一棵线段树，把一个矩形 $(x1,y1)\to (x2,y2)$ 看作是在 $x1$ 加入 $[y1,y2]$ ，在 $x2+1$减去$[y1,y2]$ ，用`set`维护最低线段。然后你会开开心心地 $\color{red}\text{WA}$ 光。接下来是本题的一些细节：

1. 加线的时候要从高往低加，因为低的会影响高的。
2. 一开始`set`里要插入`{0,0}`不然会出现奇奇怪怪的错误
3. 要先删线再加线~~如果你用`multiset`当我没说~~

本题的大致思路就是这样了。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
template<typename T>
inline void read(T &x){
	x=0;char c=getchar();bool f=false;
	for(;!isdigit(c);c=getchar())f!=c=='-';
	for(;isdigit(c);c=getchar())x=x*10+c-'0';
	if(f)x=-x;
}
template<typename T ,typename ...Arg>
inline void read(T &x,Arg &...args){
	read(x);read(args...);
}
template<typename T>
inline void write(T x){
	if(x<0)putchar('-'),x=-x;
	if(x>=10)write(x/10);
	putchar(x%10+'0');
}
const int mod=1e9+7;
const int N=1e6+10;
struct Seg_Tree{
	struct node{
		int l,r;
		int tag;//全零
		int sum; 
	}T[N*4];
	#define lson x<<1
	#define rson x<<1|1
	void build(int x,int l,int r){
		T[x].l=l,T[x].r=r;
		if(l==r)return;
		int mid=l+r>>1;
		build(lson,l,mid);
		build(rson,mid+1,r);
	}
	void pushup(int x){
		T[x].sum=(T[lson].sum+T[rson].sum)%mod;
	}
	void pushdown(int x){
		if(T[x].tag){
			T[lson].tag=T[rson].tag=1;
			T[lson].sum=T[rson].sum=0;
			T[x].tag=0;
		}
	}
	void upd(int x,int pos,int val){
		if(T[x].l==T[x].r){
			T[x].sum=val;
			return;
		}
		pushdown(x);
		int mid=T[x].l+T[x].r>>1;
		if(pos<=mid)upd(lson,pos,val);
		if( mid<pos)upd(rson,pos,val);
		pushup(x); 
	}
	void zero(int x,int l,int r){
		if(l<=T[x].l&&T[x].r<=r){
			T[x].tag=1;T[x].sum=0;
			return;
		}
		pushdown(x);
		int mid=T[x].l+T[x].r>>1;
		if(l<=mid)zero(lson,l,r);
		if(mid<r)zero(rson,l,r);
		pushup(x);
	}
	int qry(int x,int l,int r){
		if(l<=T[x].l&&T[x].r<=r)return T[x].sum;
		pushdown(x);
		int tmp=0,mid=T[x].l+T[x].r>>1;
		if(l<=mid)(tmp+=qry(lson,l,r))%=mod;
		if(mid<r)(tmp+=qry(rson,l,r))%=mod;
		return tmp;
	}
}seg;
int n,m,T;
vector<pair<int,int>>add[1000010],del[1000010];
set<pair<int,int>>s;
signed main(){
	read(n,m,T);
	while(T--){
		int X1,Y1,X2,Y2;
		read(X1,Y1,X2,Y2);
		add[X1].push_back(make_pair(Y1,Y2));
		del[X2+1].push_back(make_pair(Y1,Y2));
	}
	s.insert({0,0});
	for(auto Seg:add[1])
		s.insert(Seg);
	seg.build(1,1,m);
	seg.upd(1,1,1);
	for(int i=2;i<=n;i++){
		sort(add[i].begin(),add[i].end());
		reverse(add[i].begin(),add[i].end());
		for(auto Seg:add[i]){
			int x=Seg.first,y=Seg.second;
			if (y==m) continue;
			auto it=s.lower_bound(make_pair(y+2,0));it--;
			int ans=0;
			auto pr=*it;
			if(pr.second<=y)ans=seg.qry(1,pr.second+1,y+1);
			seg.upd(1,y+1,ans);
		}
		for(auto Seg:del[i])
			s.erase(Seg);
		for(auto Seg:add[i])
			s.insert(Seg),
			seg.zero(1,Seg.first,Seg.second);
	}
	auto it=s.end();it--;
	printf("%d",seg.qry(1,(*it).second+1,m));
}
```

---

## 作者：Lgx_Q (赞：3)

题意：一个 $n\times m$ 的网格，有 $k$ 个矩形障碍，保证这些障碍不重叠，但可能接壤。

从 $(1,1)$ 走一条路径，每次只能向右或向上，把 $k$ 个矩形划分成两个集合，求有多少种可能的划分方法，模 $10^9+7$。

$3\le n,m\le 10^6,\space 1\le k\le 10^5$

---

一个直观的不一样的方法。

注：下文认为横坐标为**行的编号**，纵坐标为**列的编号**。

考虑类似于 [这题](https://www.luogu.com.cn/problem/AT_arc101_d) 的思想，我们计算 跨越在下面的矩形的集合上方的轮廓线个数，这样可以做到每个集合算一次。

例如

![](https://cdn.luogu.com.cn/upload/image_hosting/xv9fc9ih.png?x-oss-process=image/resize,m_lfit,h_300,w_1000)

其特点是：每次从上到右的拐弯都会在与这条轮廓线接壤的矩形的左上角处。

因此，我们可以在每个矩形的左上角处做 dp，设 $f_i$ 表示从 $(1,1)$ 到矩形 $i$ 的左上角处的轮廓线个数。

转移枚举上一个矩形 $j$ 的左上角：

$$f_i=\sum_{j,\text{一定条件}} f_j$$

现在我们分析“一定条件”是什么，不难发现，从矩形 $j$ 的左上角拐弯后，轮廓线会在矩形 $j$ 的上面一行向左走，然后在矩形 $i$ 的左边一列向上走，条件就是走到的格子没有障碍。

考虑算出从矩形 $i$ 的左上角处开始，向下/向右一直走空格子，最远能走到的格子 $(a_i,b_i),(c_i,d_i)$，如下图

![](https://cdn.luogu.com.cn/upload/image_hosting/v0xajghz.png?x-oss-process=image/resize,m_lfit,h_450,w_1000)

那么矩形 $j$ 上面的 $(c_j,b_j)\sim (c_j,d_j)$ 都是空格子，矩形 $i$ 左边的 $(a_i,b_i)\sim (c_i, b_i)$ 都是空格子。

我们可以理解为每个矩形都对应一个这样的“L 型”图形，因此 $j$ 能转移到 $i$ 的条件是这两个“L 型”图形有交，并且两个矩形的左上角格子不在同一行也不在同一列。

用式子表示，就是

$$a_i\le c_j<c_i \space \text{且}\space b_j<b_i\le d_j$$

这是二维偏序的形式。按 $b_i$ 排序，由于有 $d_j$ 的限制，每个决策 $j$ 贡献到后面的 $i$ 是从 $j+1$ 开始的一段，这个可以二分/优先队列处理。然后 $a_i\le c_j<c_i$ 可以直接用树状数组/线段树查询 $[a_i,c_i-1]$ 的和。

边界情况可以在网格下面增添一个矩形表示起点，在网格右边增添一个矩形表示终点。

最后一个问题：如何求 $a_i,b_i,c_i,d_i$？

首先 $b_i,c_i$ 是已知的，就是矩形左边一列和上面一行的编号。以 $a_i$ 为例，$d_i$ 类似。

我们要求的就是“从 $(c_i,b_i)$ 向下走，走到的第一个有障碍的格子的坐标”。考虑从前往后扫描线，并用 multiset 储存每个扫到的矩形对应的线段的上端点。每次先查询 $(c_i,b_i)$ 是否为空，若为空，查询 set 中 $c_i$ 的前驱即为所求。

时间复杂度 $O(k\log (n+m+k))$。

```cpp
#include<bits/stdc++.h>
#define ls(p) a[p].lc
#define rs(p) a[p].rc
#define fi first
#define se second
#define mkp make_pair
#define ll long long
#define pir pair<ll,ll>
#define pb push_back
using namespace std;
const ll maxn=1e6+10, inf=1e17, mod=1e9+7;
ll n,m,k,l1,l2,tree[maxn],f[maxn];
multiset<ll>st;
struct node{
	ll x,l,r,v;
}p1[maxn],p2[maxn];
struct ptw{
	ll x1,y1,x2,y2,id; //此处 a[i]为x1，b[i]为y1，c[i]为x2，d[i]为y2 
}a[maxn];
vector<pir>v1[maxn],v2[maxn];
bool cmp(node a,node b){
	return a.x<b.x;
}
void add(ll x,ll n,ll v){
	while(x<=n){
		tree[x]=(tree[x]+v+mod)%mod; x+=x&-x;
	}
}
ll ask(ll x,ll n){
	ll v=0;
	while(x){
		v=(v+tree[x])%mod; x-=x&-x;
	} return v;
}
bool cmp2(ptw a,ptw b){
	return a.y1!=b.y1? a.y1<b.y1:a.x2>b.x2;
}
priority_queue<pir>q;
int main(){ 
	scanf("%lld%lld%lld",&n,&m,&k);
	for(ll i=1;i<=k;i++){
		ll xa,ya,xb,yb;
		scanf("%lld%lld%lld%lld",&xa,&ya,&xb,&yb);
		v1[xb+1].pb(mkp(ya-1,i)), v2[ya-1].pb(mkp(xb+1,i));
		p1[++l1]=(node){xa,ya,yb,1};
		p1[++l1]=(node){xb+1,ya,yb,-1};
		p2[++l2]=(node){ya,xa,xb,1};
		p2[++l2]=(node){yb+1,xa,xb,-1};
		a[i].y1=ya-1, a[i].x2=xb+1;
		a[i].x1=xb+1, a[i].y2=ya-1;
		a[i].id=i;
	}
	sort(p1+1,p1+1+l1,cmp);
	sort(p2+1,p2+1+l2,cmp);
	++k, a[k]=(ptw){1,0,1,m,k}; f[k]=1;
	v1[1].pb(mkp(0,k));
	++k, a[k]=(ptw){1,m,n+1,m,k};
	v2[m].pb(mkp(n+1,k));
	st.insert(m+1);
	for(ll i=1,j=0;i<=n;i++){
		while(j<l1&&p1[j+1].x==i){
			++j;
			add(p1[j].l,m,p1[j].v), add(p1[j].r+1,m,-p1[j].v);
			if(p1[j].v==1) st.insert(p1[j].l);
			else st.erase(st.find(p1[j].l));
		}
		for(pir t:v1[i]){
			ll tmp=ask(t.fi,m);
			if(!tmp){
				a[t.se].y2=*(st.lower_bound(t.fi))-1;
			}
		}
	} memset(tree,0,sizeof tree);
	st.clear(), st.insert(0);
	for(ll i=1,j=0;i<=m;i++){
		while(j<l2&&p2[j+1].x==i){
			++j; add(p2[j].l,n,p2[j].v), add(p2[j].r+1,n,-p2[j].v);
			if(p2[j].v==1) st.insert(p2[j].r);
			else st.erase(st.find(p2[j].r));
		}
		for(pir t:v2[i]){
			ll tmp=ask(t.fi,m);
			if(!tmp){
				a[t.se].x1=*(--st.lower_bound(t.fi))+1;
			}
		}
	}
	sort(a+1,a+1+k,cmp2);
	memset(tree,0,sizeof tree);
	for(ll i=1;i<=k;i++){
		ll id=a[i].id;
		while(!q.empty()&&-q.top().fi<a[i].y1){
			ll j=q.top().se; q.pop();
			add(a[j].x2,n,-f[a[j].id]);
		}
		if(id!=k-1) f[id]=(ask(a[i].x2-1,n)-ask(a[i].x1-1,n)+mod)%mod;
		add(a[i].x2,n,f[id]); 
		q.push(mkp(-a[i].y2,i));
	}
	printf("%lld",f[k]);
	return 0;
}
```

---

## 作者：lupengheyyds (赞：1)

# 代表元计数——CF720D Slalom 题解

首先这题路径数的定义与平时不太一样：如果其没有以不同的方式跨过障碍，即使路径所走的是不同的，也要算作一条。

对于算作一条的许多路径，如果可以使仅其中一条产生贡献，便可以解决问题。为了方便，这里取最低的一条，称作代表路径

设 $f_{i,j}$ 表示走到 $i,j$ 的代表路径数是多少。

如果没有矩形，直接 $f_{i,j}=f_{i-1,j}$。

如果有矩形，形如下图：引用了[前人](https://www.luogu.com.cn/user/174304)的[题解](https://www.luogu.com.cn/article/53a8gaos)图片，在此鸣谢。

![](https://cdn.luogu.com.cn/upload/image_hosting/imqg6w8t.png)

设向下第一个碰到的第一个矩形上界为 $u$ 那么 $f_{i,j}=\sum_{k=u+1}^jf_{i-1,k}$

从左到右扫描线，求和用线段树，找 $u$ 用 `set` 维护一下当前被覆盖的线段。复杂度 $T:\mathcal O((m+k)\log n) M:\mathcal O(k)$。 

## 代码：
```cpp
#include<bits/stdc++.h>
#define io ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
#define file(s) freopen(s".in","r",stdin),freopen(s".out","w",stdout)
#define int long long
#define double long double
#define loop(i,a,b) for(int i=a;i<=b;i++)
#define pool(i,a,b) for(int i=a;i>=b;i--)
#define mset(a,v) memset(a,v,sizeof a)
#define mcpy(a,b) memcpy(a,b,sizeof b)
#define myas(x) if(!(x))exit(1);
#define umap unordered_map
#define pb push_back
#define pc(x) __builtin_popcountll(x)
#define fi first
#define se second
using namespace std;
typedef unsigned long long ull;
typedef pair<int,int> pa;
typedef vector<int> vi;
#define DEBUG 
#ifndef DEBUG
#define cerr none
ofstream none("nul");
#endif
const int NN=1e6+5,MOD=1e9+7;
int n,m,k;
int l[NN],r[NN];
vector<int> ed[NN];
vector<int> add[NN],del[NN];
struct SegTr{
	int sum,tag;
	#define ls(x) (x<<1)
	#define rs(x) (x<<1|1)
	#define sum(x) sgt[x].sum
	#define tag(x) sgt[x].tag
}sgt[NN<<2];
void Up(int p){
	sum(p)=(sum(ls(p))+sum(rs(p)))%MOD;
	return;
}
void Alter(int p){
	tag(p)=1;
	sum(p)=0;
	return;
}
void Down(int p){
	if(!tag(p))return;
	Alter(ls(p)),Alter(rs(p));
	tag(p)=0;
	return;
}
int Sum(int l,int r,int p=1,int L=1,int R=m){
	if(l>R||L>r)return 0;
	if(l<=L&&R<=r)return sum(p);
	int mid=L+R>>1;
	Down(p);
	return (Sum(l,r,ls(p),L,mid)+Sum(l,r,rs(p),mid+1,R))%MOD;
}
void Add(int pos,int v,int p=1,int L=1,int R=m){
	if(L==R){
		(sum(p)+=v)%=MOD;
		return;
	}
	Down(p);
	int mid=L+R>>1;
	if(pos<=mid)Add(pos,v,ls(p),L,mid);
	else		Add(pos,v,rs(p),mid+1,R);
	return Up(p);
}
void Prune(int l,int r,int p=1,int L=1,int R=m){
	if(l>R||L>r)return;
	if(l<=L&&R<=r)return Alter(p);
	int mid=L+R>>1;
	Down(p);
	Prune(l,r,ls(p),L,mid);
	Prune(l,r,rs(p),mid+1,R);
	return Up(p);
}
set<int> se;
signed main(){
	cin>>n>>m>>k;
	loop(i,1,k){
		int x,y;cin>>x>>l[i]>>y>>r[i];
		add[x].pb(i);
		del[y+1].pb(i);
	}
	se.insert(0);
	loop(i,1,n){
		sort(add[i].begin(),add[i].end(),[&](int x,int y){return l[x]>l[y];});
		sort(del[i].begin(),del[i].end(),[&](int x,int y){return l[x]>l[y];});
		for(int o:add[i]){
			int pos=1+*--se.upper_bound(r[o]+1);
			if(r[o]<m)Add(r[o]+1,Sum(pos,r[o]));
		}
		if(i==1)Add(1,1);
		for(auto o:del[i])se.erase(l[o]);
		for(auto o:add[i]){
			se.insert(l[o]);
			Prune(l[o],r[o]);
		}
	}
	int pos=*--se.upper_bound(m);
	cout<<Sum(pos,m);
	return 0;
}
```

---

## 作者：Petit_Souris (赞：1)

先考虑怎么不重不漏地数到所有路径。很直接的思路是对于每种本质相同的路径选出一个代表元，因此我们不妨计数在决定了每个障碍从上走还是从下走的情况下，$y$ 坐标最小的路径。称这样的路径为最优路径。

这样就可以开始 dp 了：设 $f_{x,y}$ 表示从 $(1,1)$ 走到 $(x,y)$ 的最优路径数量。我们按照横坐标从小到大扫描进行转移。

转移的时候，看看这张图就会清晰很多了：

![](https://cdn.luogu.com.cn/upload/image_hosting/kx1nhia6.png)

红点表示要转移到的 $(x,y)$（$(x,y)$ 一定是作为一个障碍物的左上角的上方的点出现的，否则不符合最优的条件），绿点表示 $y'<y$ 且有最优路径的 $(x-1,y')$，从 $f_{x-1,y'}$ 转移到 $f_{x,y}$（蓝色的箭头）。那么这样一次转移合法的条件即 $(x-1,y')$ 到 $(x-1,y)$ 中间没有障碍（深蓝色的箭头表示不合法的转移，因为中间被障碍物挡住了）。绿色的箭头代表的转移是从 $f_{x-1,y}$ 到 $f_{x,y}$ 的，只要中间没有障碍就可以一路转移。

那么我们获得了一个 $\mathcal O(n(n+m))$ 的做法。

考虑用数据结构优化这件事情，我们要干的事情是：

- 对于每个需要转移的 $(x,y)$，找到 $(x-1,y)$ 向下不经过障碍能走到的最远的点 $(x-1,z)$。
- 求 $\sum\limits_{i=z}^{y-1}f_{x-1,i}$。（这里求和上界不是 $y$ 是因为 $(x-1,y)\to (x,y)$ 的转移是分开做的，避免重复）
- 对于所有不是障碍的 $(x,y)$，$f_{x-1,y}\to f_{x,y}$。

我们可以维护两棵线段树，第一棵线段树用来记录 dp 数组，第二棵线段树用来维护扫描线矩形覆盖。

对于找转移点 $z$，可以在第二棵线段树上从 $y$ 开始向前二分出第一个被覆盖了的位置；对于求和部分，可以在第一棵线段树上区间求和；对于横向移动的转移，我们发现实际上就是把上一层的 dp 保留了过来，再把障碍的位置清零，就是区间清零操作。所以第一棵线段树需要支持单点修改，区间清零，区间和，第二棵线段树需要支持区间加，区间最大值。时间复杂度 $\mathcal O((n+m)\log n)$。

模拟赛考的版本是有矩形相交的，顺便也讲一下怎么做吧。

对于矩形可能相交的情况和上面的部分分其实是类似的，只不过我们需要考虑这样的情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/yz6n1f02.png)

这时候红点的 $f$ 值应当为 $0$，但是不会被这一层的障碍清空。这时候应该手动判断一下这个位置是否在障碍里，可以在上面的第二棵线段树里判断。于是就做完了。

注意一些实现细节：

- 对于 $x$ 相同的，同时加入的矩形，应当按照上边界的 $y$ 从大到小计算，不然会重复转移。
- 最后计算答案的时候只有在最上的障碍物以上的 $f_{n,y}$ 才会被统计进答案。
- 判断一个点在不在障碍里应该看 $x$ 时刻的状态而不是 $x-1$ 时刻的，所以要注意一下增减和 dp 转移的顺序。
- 矩阵相交的时候可能有多个上边界重叠的情况，这时候某些写法可能会重复计算，需要避免。

```cpp
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
#define pii pair<ll,ll>
#define rep(i,a,b) for(ll i=(a);i<=(b);++i)
#define per(i,a,b) for(ll i=(a);i>=(b);--i)
using namespace std;
bool Mbe;
ll read(){
    ll x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
void write(ll x){
    if(x<0)putchar('-'),x=-x;
    if(x>9)write(x/10);
    putchar(x%10+'0');
}
const ll N=1e6+9,Mod=1e9+7;
ll n,k,m,qd[N],ok[N];
struct Node{
    ll x,y,u,v;
}a[N];
vector<ll>id[N],del[N];
struct SegT1{
    ll tr[N<<2];
    bool tag[N<<2];
    void Pushup(ll x){
        tr[x]=(tr[x<<1]+tr[x<<1|1])%Mod;
    }
    void Pushtag(ll x){
        tr[x]=0,tag[x]=1;
    }
    void Pushdown(ll x){
        if(!tag[x])return ;
        Pushtag(x<<1),Pushtag(x<<1|1);
        tag[x]=0;
    }
    void Upd(ll x,ll l,ll r,ll u,ll v){
        if(l>u||r<u)return ;
        if(l==r){
            tr[x]=v;
            return ;
        }
        ll mid=(l+r)>>1;
        Pushdown(x);
        Upd(x<<1,l,mid,u,v);
        Upd(x<<1|1,mid+1,r,u,v);
        Pushup(x);
    }
    void Cov(ll x,ll l,ll r,ll ql,ll qr){
        if(l>qr||r<ql)return ;
        if(ql<=l&&r<=qr){
            Pushtag(x);
            return ;
        }
        ll mid=(l+r)>>1;
        Pushdown(x);
        Cov(x<<1,l,mid,ql,qr);
        Cov(x<<1|1,mid+1,r,ql,qr);
        Pushup(x);
    }
    ll Query(ll x,ll l,ll r,ll ql,ll qr){
        if(l>qr||r<ql)return 0;
        if(ql<=l&&r<=qr)return tr[x];
        ll mid=(l+r)>>1;
        Pushdown(x);
        return (Query(x<<1,l,mid,ql,qr)+Query(x<<1|1,mid+1,r,ql,qr))%Mod;
    }
}T1;
struct SegT2{
    ll mx[N<<2],tag[N<<2];
    void Pushup(ll x){
        mx[x]=max(mx[x<<1],mx[x<<1|1]);
    }
    void Pushtag(ll x,ll k){
        mx[x]+=k,tag[x]+=k;
    }
    void Pushdown(ll x){
        if(!tag[x])return ;
        Pushtag(x<<1,tag[x]);
        Pushtag(x<<1|1,tag[x]);
        tag[x]=0;
    }
    void Upd(ll x,ll l,ll r,ll ql,ll qr,ll k){
        if(l>qr||r<ql)return ;
        if(ql<=l&&r<=qr){
            Pushtag(x,k);
            return ;
        }
        ll mid=(l+r)>>1;
        Pushdown(x);
        Upd(x<<1,l,mid,ql,qr,k);
        Upd(x<<1|1,mid+1,r,ql,qr,k);
        Pushup(x);
    }
    ll Query(ll x,ll l,ll r,ll ql,ll qr){
        if(l>qr||r<ql||ql>qr)return 0;
        if(ql<=l&&r<=qr)return mx[x];
        ll mid=(l+r)>>1;
        Pushdown(x);
        return max(Query(x<<1,l,mid,ql,qr),Query(x<<1|1,mid+1,r,ql,qr));
    }
    ll Find(ll x,ll l,ll r,ll p){
        if(mx[x]==0)return 0;
        if(l==r)return l;
        ll mid=(l+r)>>1;
        Pushdown(x);
        if(p<=mid)return Find(x<<1,l,mid,p);
        ll rg=Find(x<<1|1,mid+1,r,p);
        if(rg)return rg;
        return Find(x<<1,l,mid,p);
    }
}T2;
bool Med;
int main(){
    cerr<<fabs(&Med-&Mbe)/1048576.0<<"MB\n";
    n=read(),k=read(),m=read();
    rep(i,1,m)a[i].x=read(),a[i].y=read(),a[i].u=read(),a[i].v=read();
    rep(i,1,m){
        id[a[i].x].push_back(i);
        del[a[i].u+1].push_back(i);
    }
    T1.Upd(1,1,k,1,1);
    for(ll j:id[1])T2.Upd(1,1,k,a[j].y,a[j].v,1);
    rep(i,2,n){
        sort(id[i].begin(),id[i].end(),[&](ll x,ll y){
            return a[x].v>a[y].v;
        });
        for(ll j:del[i])T2.Upd(1,1,k,a[j].y,a[j].v,-1);
        for(ll j:id[i]){
            if(a[j].v<k)ok[j]=!T2.Query(1,1,k,a[j].v+1,a[j].v+1);
        }
        for(ll j:del[i])T2.Upd(1,1,k,a[j].y,a[j].v,1);
        for(ll j:id[i]){
            ll p=a[j].v+1;
            if(p>k||qd[p]==i||!ok[j])continue;
            ll q=T2.Find(1,1,k,p)+1;
            ll s=T1.Query(1,1,k,q,p);
            T1.Upd(1,1,k,a[j].v+1,s),qd[a[j].v+1]=i;
        }
        for(ll j:id[i]){
            T2.Upd(1,1,k,a[j].y,a[j].v,1);
            T1.Cov(1,1,k,a[j].y,a[j].v);
        }
        for(ll j:del[i])T2.Upd(1,1,k,a[j].y,a[j].v,-1);
    }
    ll p=T2.Find(1,1,k,k)+1;
    ll ans=T1.Query(1,1,k,p,k);
    write(ans);
    cerr<<"\n"<<clock()*1.0/CLOCKS_PER_SEC*1000<<"ms\n";
    return 0;
}
```

---

