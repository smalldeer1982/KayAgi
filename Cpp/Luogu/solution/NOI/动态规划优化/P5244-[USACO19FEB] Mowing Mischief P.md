# [USACO19FEB] Mowing Mischief P

## 题目描述

Bessie 的表妹 Ella 和 Bella 正在参观农场。不幸的是，自从他们到达以来，他们一直在恶作剧。

在他们的最新计划中，他们决定尽可能多地割草。农场的草地是 $ T \times T $ 的正方形。左下角是 $ (0,0) $ ，右上角是 $ (T,T) $ 。因此，正方形包含 $ (T+1)^2 $ 个格点（具有整数坐标的点）。

Ella 和 Bella 计划从 $ (0,0) $ 开始并以每秒一个单位长度的速度运行到 $ (T,T) $ ，同时每只奶牛都握住非常锋利且非常有弹性的线的一端。任何被这根电线扫过的区域的草都会被切断。Ella 和 Bella 可能采取不同的路径，但她们只会向上或者向右移动，从一个格点移动到另一个格点。

Bessie 非常担心会切割太多的草，所以她发明了一个聪明的计划来限制 Ella 和 Bella 的路径。在整个草原上散布着 $ N $ 种花（ $ 1 \leq N \leq 2 \times 10^5 $ ），每种花都在一个特定的格点上。 Bessie 将从这些花中挑选一个子集 $ S $ ， $ S $ 集合中的花 Ella 和 Bella 都需要经过（Ella 和 Bella 的路径都必须经过 $ S $ 中的所有花朵）。

Ella 和 Bella 将会切割面积尽可能大的草，请帮助Bessie确定集合 $ S $ 使得被切割的草的**面积**最小。

## 说明/提示

选择 $ (10,3) $ 和 $ (13,11) $ 这两个位置上的花，可以使得被切割的草的面积最小。

子任务：对于 $ 20\% $ 的数据， $ N \leq 3200 $ 。

## 样例 #1

### 输入

```
5 20
19 1
2 6
9 15
10 3
13 11```

### 输出

```
117```

# 题解

## 作者：Unordered_OIer (赞：51)

# P5244 题解
## [宣传博客](https://www.luogu.com.cn/blog/291706/)
## 题意
二维坐标系中，选择坐标严格递增的一些点，相邻点依次作为对角线组成的长方形面积和最小。
$$x_0<x_1<...<x_k$$
$$y_0<y_1<...<y_k$$
这个应该很容易理解  

## 解答
二维最长不下降序列？  
按$x$排序，一维$LIS$

$DP$!  
假设$p$的最长上升序列长度为$i$，枚举点$p$左下角的所有最长上升序列长度为$i-1$的点$q$

那么我们可以写出转移方程：
$$dp_p=\min_{q∈L_{i-1}\ |\ p>>q}\{dp_q+(x_p-x_q)(y_p-y_q)\}$$
其中$p>>q$表示$p$在$q$的左上方，$L_x$表示以$x$结尾的$LIS$长度。

那么我们按层$dp$  
一共有$S$层  
对于$L_i$里的所有点  
决策：要在$L_{i-1}$里选一个点，选哪个？  
约束：这个点要在左下方

简化问题：  
没有约束？  
对于点$p_1,p_2∈L_i$，$q_1,q_2∈L_{i-1}$，  
$X_{p_1}<X_{p_2} -> Y_{p_1}>Y_{p_2}$  
$X_{q_1}<X_{q_2} -> Y_{q_1}>Y_{q_2}$  

可以证明：
如果$p_1$选择了$q_1$，那么$p_2$一定选择$q_1$

但是这样肯定不能~~AKIOI~~，于是我们要优化。  
这里就会用到一个常见的手段：$\color{red}{决策单调性！}$  

有约束，怎么办？~~中国山东找蓝翔~~  
我们发现**约束也是连续的！**  
因此当我们求区间最优解的时候，可以用$Segment\ tree$来维护。  
线段树每个结点表示$L_{i-1}$的一段区间。

所以我们确定步骤：
1. 对于第$i$层的一个点，找到$L_{i-1}$线段树上所有包含的区间，这些结点上记录下能对该点进行转移。
2. 每个结点上记录了一些$L_i$的转移目标，这些转移目标符合单调性。
3. 遍历$L_{i-1}$这棵线段树的所有（可转移的）结点，更新$L_i$的$DP$值。  

## 代码军
此处借鉴了dalao[$\text{\color{red}LIdox1536513344}$](https://www.luogu.com.cn/user/36220)的代码  
线段树建树
```cpp
inline void buildSegTr(int &rt,int l,int r){
  rt=++size;
  a[rt].ls=a[rt].rs=0;
  a[rt].trans.clear();
  if(l==r)return;
  int mid=(l+r)>>1;
  buildSegTr(a[rt].ls,l,mid);
  buildSegTr(a[rt].rs,mid+1,r);
}
```
转移
```cpp
inline void Modify(int rt,int l,int r,int x){
	if(p[x].x>=p[point[r]].x&&p[x].y>=p[point[l]].y){
		a[rt].trans.push_back(x);
		return;
	}
	if(p[x].x<=p[point[l]].x||p[x].y<=p[point[r]].y) return;
	int mid=(l+r)>>1;
	Modify(a[rt].ls,l,mid,x);
	Modify(a[rt].rs,mid+1,r,x);
}
```
解决问题
```cpp
inline void Solve(int l,int r,int ql,int qr){
	ll ans=inf,from=0;
	int mid=(l+r)>>1,now=tmp[mid];
	for(int i=ql;i<=qr;++i){
		int pos=point[i];
		ll res=dp[pos]+1ll*(p[now].x-p[pos].x)*(p[now].y-p[pos].y);
		if(res<ans){
			ans=res;
			from=i;
		}
	}
	dp[now]=min(dp[now],ans);
	if(l<mid) Solve(l,mid-1,from,qr);
	if(mid<r) Solve(mid+1,r,ql,from);
}
inline void Work(int rt,int l,int r){
	if(a[rt].trans.size()){
		tmp=a[rt].trans;
		Solve(0,tmp.size()-1,l,r);
	}
	if(l==r) return;
	int mid=(l+r)>>1;
	Work(a[rt].ls,l,mid);
	Work(a[rt].rs,mid+1,r);
}
```
主函数怎么用
```cpp
sort(p+1,p+n+1,cmpx);
for(ll i=1;i<=n;++i){
	ly[i]=Query(p[i].y)+1;
	Modify(p[i].y,ly[i]);
	pos[ly[i]].push_back(i);
	m=max(m,ly[i]);
}
for(ll i=0,now;i<(ll)pos[1].size();++i)now=pos[1][i],f[now]=1ll*p[now].x*p[now].y;
for(ll i=2,now;i<=m;++i){
	ST.init(pos[i-1]);
	for(ll j=0;j<(ll)pos[i].size();++j){
		now=pos[i][j];
		f[now]=INF;
		ST.modify(now);
	}
	ST.work();
}
ll ans=INF;
for(ll i=0;i<(ll)pos[m].size();++i){
	ll now=pos[m][i];
	ans=min(ans,f[now]+1ll*(T-p[now].x)*(T-p[now].y));
}
```
最后放一次完整代码（有修改）
```cpp
#include<bits/stdc++.h>
#define SIZE_N 300005
#define SIZE_T 1000005
#define INF 2e18
using namespace std;
typedef long long ll;
namespace Mischief{
	struct Node{ll x,y;}p[SIZE_N];
	inline bool cmpx(Node a,Node b){return a.x==b.x?a.y<b.y:a.x<b.x;}
	ll T,n,m,s,ly[SIZE_N],f[SIZE_N],bit[SIZE_T];
	vector<ll> pos[SIZE_N];
	inline ll LSB(ll x){return x&(-x);}
	inline void Modify(ll x,ll v){for(ll i=x;i<=T;i+=LSB(i))bit[i]=max(bit[i],v);}
	inline ll Query(ll x){ll res=0;for(ll i=x;i;i-=LSB(i))res=max(res,bit[i]);return res;}
	struct Segment_Tree{
		struct Node{
			ll ls,rs;
			vector<ll> trans;
		}a[SIZE_N<<1];
		ll n,size,rt;
		vector<ll> poll,tmp;
		inline void buildSt(ll &rt,ll l,ll r){
			rt=++size;
			a[rt].ls=a[rt].rs=0;
			a[rt].trans.clear();
			if(l==r)return;
			ll mid=(l+r)>>1;
			buildSt(a[rt].ls,l,mid);
			buildSt(a[rt].rs,mid+1,r);
		}
		inline void init(vector<ll> tmp){
			poll=tmp;
			n=tmp.size();
			rt=size=0;
			buildSt(rt,0,n-1);
		}
		inline void Modify(ll rt,ll l,ll r,ll x){
			if(p[x].x>=p[poll[r]].x&&p[x].y>=p[poll[l]].y){
				a[rt].trans.push_back(x);
				return;
			}
			if(p[x].x<=p[poll[l]].x||p[x].y<=p[poll[r]].y)return;
			ll mid=(l+r)>>1;
			Modify(a[rt].ls,l,mid,x);
			Modify(a[rt].rs,mid+1,r,x);
		}
		inline void modify(ll x){Modify(rt,0,n-1,x);}
		inline void Solve(ll l,ll r,ll ql,ll qr){
			ll ans=INF,from=0;
			ll mid=(l+r)>>1,now=tmp[mid];
			for(ll i=ql;i<=qr;++i){
				ll pos=poll[i];
				ll res=f[pos]+1ll*(p[now].x-p[pos].x)*(p[now].y-p[pos].y);
				if(res<ans)ans=res,from=i;
			}
			f[now]=min(f[now],ans);
			if(l<mid)Solve(l,mid-1,from,qr);
			if(mid<r)Solve(mid+1,r,ql,from);
		}
		inline void Work(ll rt,ll l,ll r){
			if(a[rt].trans.size())tmp=a[rt].trans,Solve(0,tmp.size()-1,l,r);
			if(l==r)return;
			ll mid=(l+r)>>1;
			Work(a[rt].ls,l,mid);
			Work(a[rt].rs,mid+1,r);
		}
		inline void work(){Work(rt,0,n-1);}
	}ST;
	inline int _main(){
		scanf("%lld%lld",&n,&T);
		for(ll i=1;i<=n;++i)scanf("%lld%lld",&p[i].x,&p[i].y);
		sort(p+1,p+n+1,cmpx);
		for(ll i=1;i<=n;++i){
			ly[i]=Query(p[i].y)+1;
			Modify(p[i].y,ly[i]);
			pos[ly[i]].push_back(i);
			m=max(m,ly[i]);
		}
		for(ll i=0,now;i<(ll)pos[1].size();++i)now=pos[1][i],f[now]=1ll*p[now].x*p[now].y;
		for(ll i=2,now;i<=m;++i){
			ST.init(pos[i-1]);
			for(ll j=0;j<(ll)pos[i].size();++j){
				now=pos[i][j];
				f[now]=INF;
				ST.modify(now);
			}
			ST.work();
		}
		ll ans=INF;
		for(ll i=0;i<(ll)pos[m].size();++i){
			ll now=pos[m][i];
			ans=min(ans,f[now]+1ll*(T-p[now].x)*(T-p[now].y));
		}
	}
}using namespace Mischief;
int main(){
	_main();
	return 0;
}
```
什么你不想翻上去点赞？那就[点这里吧](https://www.luogu.com.cn/blog/291706/solution-p5244#)！

---

## 作者：i207M (赞：18)

好题！~~我把minmax看反推了半天~~ [Blog](https://blog.csdn.net/qq_39972971/article/details/87967914)

我们肯定要求出以每个点结尾的LIS长度，然后长度相差1的点之间转移。

**性质：LIS相同的点，横坐标增加，纵坐标减小**

我们列出转移方程：

$$dp_i=\min_{j\in\ L[l-1] ,\ x_j< x_i,y_j< y_i}\{dp_j+(x_i-x_j)(y_i-y_j)\}$$

看着比较像斜率优化，但是好像化简不到标准形式？这是就要用到优化DP的另一个利器了：决策单调性！

考虑 $j,k(k<j)$ 两处转移，令 j 优于 k，则


$$dp_j+x_jy_j-x_iy_j-x_jy_i\leq dp_k+x_ky_k-x_iy_k-x_ky_i$$
 
$$(y_k-y_j)x_i+(x_k-x_j)y_i\leq dp_k+x_ky_k-dp_j-x_jy_j$$
 
注意到 $y_k-y_j$和 $ x_k-x_j$必然一正一负，因此这个半平面是一个斜率为正的半平面，一定会将下一层的点分为前后两部分，因而若排除掉 $x_j\leq x_i,y_j\leq y_i$的限制，该 DP 的转移具有决策单调性。

这道题的决策单调性是反的：后边的点更可能成为前边的点的最优决策点。

然后考虑如何解决$x_j\leq x_i,y_j\leq y_i$的限制。

注意到，如果我们把点按照横坐标递增编号，那么同一层中，满足$x_j\leq x_i,y_j\leq y_i$的编号是连续的，这启发我们把询问放到线段树上，对于线段树的每个节点。把节点上的询问拿出来，跑一边决策单调性。

复杂度$O(n\log ^2n)$

```cpp
#define N 200005
int n;
struct Node
{
	int x,y;
	Node() {}
	Node(const int _x,const int _y) {x=_x,y=_y;}
	friend bool operator<(const Node &a,const Node &b) {return a.x<b.x;}
} pt[N];
il LL dis(const int a,const int b) {return abs((LL)(pt[a].x-pt[b].x)*(pt[a].y-pt[b].y));}
const LL inf=1ll<<60;
LL dp[N];
void solve(int l,int r,int al,int ar,const vector<int> &q,const vector<int> &g)
{
	int _mid=(l+r)>>1,mid=q[_mid],am=0; LL t=inf;
	for(ri i=al; i<=ar; ++i) if(ckmin(t,dp[g[i]]+dis(g[i],mid))) am=i;
	ckmin(dp[mid],t);
	if(l<_mid) solve(l,_mid-1,am,ar,q,g);
	if(_mid<r) solve(_mid+1,r,al,am,q,g);
}
#define M N*4
#define ls (x<<1)
#define rs (x<<1|1)
const int rt=1;
vector<int>qu[M];
void upd(int x,int l,int r,int p,const vector<int> &g)
{
	if(pt[g[l]].y<=pt[p].y&&g[r]<=p) return qu[x].pb(p);
	if(pt[g[r]].y>pt[p].y||g[l]>p) return;
	gm;
	upd(ls,l,mid,p,g),upd(rs,mid+1,r,p,g);
}
void work(int x,int l,int r,const vector<int> &g)
{
	if(Size(qu[x]))
	{
		solve(0,Size(qu[x])-1,l,r,qu[x],g);
		qu[x].clear();
	}
	if(l==r) return;
	gm;
	work(ls,l,mid,g),work(rs,mid+1,r,g);
}
vector<int>pos[N];
int T;
int tre[N];
void upd(int x,int k)
{
	for(; x<=n; x+=x&-x) ckmax(tre[x],k);
}
int ask(int x)
{
	int res=0;
	for(; x; x-=x&-x) ckmax(res,tre[x]);
	return res;
}
int lis[N];
int ui[N],cu;
signed main()
{
#ifdef M207
	freopen("in.in","r",stdin);
	// freopen("ot.out","w",stdout);
#endif
	in(n,T);
	for(ri i=1; i<=n; ++i) in(pt[i].x,pt[i].y),ui[i]=pt[i].y;
	sort(ui+1,ui+1+n);
	sort(pt+1,pt+1+n);
	int mx=0;
	for(ri i=1,L; i<=n; ++i)
	{
		L=lower_bound(ui+1,ui+1+n,pt[i].y)-ui;
		lis[i]=ask(L)+1,ckmax(mx,lis[i]);
		upd(L,lis[i]);
		pos[lis[i]].pb(i);
	}
	for(ri i=1; i<=n; ++i) dp[i]=inf;
	for(solid i:pos[1]) dp[i]=(LL)pt[i].x*pt[i].y;
	for(ri i=2; i<=mx; ++i)
	{
		for(solid j:pos[i]) upd(rt,0,Size(pos[i-1])-1,j,pos[i-1]);
		work(rt,0,Size(pos[i-1])-1,pos[i-1]);
	}
	LL ans=inf;
	for(solid i:pos[mx]) ckmin(ans,dp[i]+(LL)(T-pt[i].x)*(T-pt[i].y));
	out(ans);
	return 0;
}

```


---

## 作者：bigmurmur (赞：10)

# [Mowing](https://www.luogu.com.cn/problem/P5244)


首先我们发现，若要使每个点途径转移的点尽可能多，我们首先肯定要对每个点求出 $LIS$ ，然后在 $LIS$ 差 $1$ 的点之间转移。

至于二维的 $LIS$ 先对 $x$ 排序， $y$ 轴的限制跑一个树状数组就解决了。

那么这样暴力转移最惨还是 $O(n^2)$ 的复杂度，怎么办呢？我们先观察一下 $DP$ 转移过程：

设 $f_i$ 表示从 $(0,0)$ 到第 $i$ 个点的面积 $Min$ ， 不难得到：

$f_i=Max_{\ x_j<=x_i\ ,\ y_j<=y_i\ }{\ \ f_j+(x_i-x_j)\times (y_i-y_j)}$

$\ LIS_j+1=LIS_i$ 的限制已经可以通过转移顺序解决掉。


假如我们先不考虑 $\ x_j<=x_i\ ,\ y_j<=y_i\ $ 的偏序限制，


观察这个式子，

~~Qu:嗯对这是斜率优化~~,

ZXY:但这个并不是斜率优化。

为啥呢？因为你发现有两个不同的关于 $i$ 的变量 $x_i$ 和 $y_i$。

那么。。。考虑一下决策单调性？

我们先把每一层的点按照 $x$ 排序 ，不难发现对于两个点 $i,j\ (i<j)$ ，满足 $x_i<x_j\ ,\ y_i>y_j$ , （否则同层的点也能发生转移，这很矛盾）

那么看看他是否满足四边形不等式，即对于四个决策点 $i,j,k,p\ \ (i<j,k<p)$ ,$i,j$ 和 $j,k$ 分别位于相邻的两层。

假如对于 $k$ 的转移满足从 $i$ 转移过来比从 $j$ 转移过来更优秀，那么有：

$\begin{cases} x_i<x_j 
\\y_i>y_j
\\f_j+(x_k-x_j)\times (y_k-x_j)\ <\ f_i+(x_k-x_i)\times (y_k-y_i)
\end{cases}$

那么把第三个式子化一下：

$(y_i-y_j)x_k+(x_i-x_j)y_k<(f_i+x_iy_i)-(f_j+x_jy_j)$

此时 $(y_i-y_j)>0$ 且 $(x_i-x_j)<0$

那么对于与 $k$ 同一层的点 $p\ (k<p)$ ,满足：

$\begin{cases}x_k<x_p
\\y_k>y_p
\end{cases}$

那么假如把 $k$ 替换成 $p$ ，一定会使得 $(y_i-y_j)x_p$ 这个正系数的表达式的值更大，也一定会使得 $(x_i-x_j)y_p$ 这个负系数的表达式值更大，所以左式的值会更大，更容易突破 $<$ 的限制！！！

欧耶！！我们发现他的决策单调性是反着的，也就是说靠后的点更容易成为前面点的最优决策。

这是其中一个优化利器，但是我们如何满足 $\ x_j<=x_i\ ,\ y_j<=y_i\ $ 这一个诡异的限制呢？

让我们观察一下他们的相对位置：

![](https://cdn.luogu.com.cn/upload/image_hosting/19rfnxgi.png)


不难发现，每一层的点能从上一层转移来的点都是一段连续的区间，这。。。不妨把他们都压到线段树上面，以上一层的点的下标作为线段树的下标。

于是我们要查询一个点能从哪里转移来的时候，只需要把他们推到对应线段树上区间的节点上，可以用 $vector$ 把询问压进去。压一个点的复杂度是 $log$ 级别点数规模的。

对于线段树上一个节点，如果他代表的区间为 $[l,r]$ ，那么这意味着这个点上挂着的询问都能从上一层 [l,r] 的点转移过来。

区间询问区间选择答案？不妨考虑分治处理。

![](https://cdn.luogu.com.cn/upload/image_hosting/0k7q40bv.png)

假如我们 $O(len)$ 扫一遍发现 $Q_{mid}$ 的最优决策点在蓝点的位置，根据反着的决策单调性，那么 $Q_{mid}$ 右边的询问显然在上一层的左边更优，左边的询问在右侧更优。

因此算法总括：

$DP$ + $Segment\ Tree$ + 分治

复杂度是 $O(n\ log^2n)$ ，有兴趣的同志们可以尝试严格证明，跑的挺快的，最慢一个点 $500ms$ 不开 $O2$

上代码：

```cpp
#include<cstdio>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
typedef long long LL;
const int N=2e5+5;
inline int getint()
{
	char c;int f=0;
	while(c=getchar(),c>'9' || c<'0');
	while(f=(f<<1)+(f<<3)+c-'0',c=getchar(),c>='0' && c<='9');
	return f;
}
int n,T,m,tot_node;
struct Flower{
	int x,y;
}a[N];
struct Seg{
	int ls,rs;
	vector<int> q;
}t[N<<3];
struct BIT_LOCK{
	int c[1000010];
	inline void add(int p,int val)
	{
		if(!p) return ;
		while(p<=T){
			c[p]=max(c[p],val);
			p+=p&-p;
		}
		return ;
	}
	inline int ask(int p)
	{
		int ans=0;
		while(p){
			ans=max(ans,c[p]);
			p-=p&-p;
		}
		return ans;
	}
}BIT;
int LIS[N];
int X[N],Y[N],tot,ROOT;
LL dp[N];
vector<int> g[N],st;

inline int max(int a,int b) {return a>b?a:b;}
inline int min(int a,int b) {return a>b?b:a;}
inline LL min(LL a,LL b) {return a>b?b:a;}
inline bool cmp(Flower a,Flower b) {return a.x<b.x || a.x==b.x && a.y<b.y;}
inline bool cmp_x(int x,int y) {return a[x].x<a[y].x || a[x].x==a[y].x && a[x].y<a[y].y;}

inline void query(int &p,int left,int right,int L,int R,int u)
{
	if(!p) p=++tot_node;
	if(L>=left && R<=right){
		t[p].q.push_back(u);
		return ;
	}
	int mid=L+R>>1;
	if(left<=mid) query(t[p].ls,left,right,L,mid,u);
	if(right>mid) query(t[p].rs,left,right,mid+1,R,u);
}
inline void merge(int ql,int qr,int L,int R,int dep)
{
	if(ql>qr) return ;
	if(L==R){
		int u=g[dep-1][L];
		for(register int i=ql;i<=qr;++i){
			int v=st[i];
			dp[v]=min(dp[v],dp[u]+1ll*(a[v].x-a[u].x)*(a[v].y-a[u].y));
		}
		return ;
	}
	int mid=ql+qr>>1;
	int v=st[mid];
	int pos=-1;
	LL minn=0x3f3f3f3f3f3f3f3f;
	for(register int i=L;i<=R;++i){
		int u=g[dep-1][i];
		LL val=dp[u]+1ll*(a[v].x-a[u].x)*(a[v].y-a[u].y);
		if(minn>val) minn=val,pos=i;
	}
	dp[v]=min(dp[v],minn);
	merge(ql,mid-1,pos,R,dep);
	merge(mid+1,qr,L,pos,dep);
}
inline void dfs(int p,int L,int R,int dep)
{
	if(!p) return ;
	if(L==R){
		for(register int i=0;i<(int)t[p].q.size();++i){
			int v=t[p].q[i];
			int u=g[dep-1][L-1];
			dp[v]=min(dp[v],dp[u]+1ll*(a[v].x-a[u].x)*(a[v].y-a[u].y));
		}
		t[p].q.clear();
		return ;
	}
	if(t[p].q.size()){
		st=t[p].q;
		merge(0,t[p].q.size()-1,L-1,R-1,dep);
		t[p].q.clear();
	}
	int mid=L+R>>1;
	dfs(t[p].ls,L,mid,dep);
	dfs(t[p].rs,mid+1,R,dep);
}
int main()
{
	memset(dp,0x3f,sizeof dp);
	n=getint(),T=getint();
	for(register int i=1;i<=n;++i){
		a[i].x=getint(),a[i].y=getint();
		LIS[i]=1;
	}
	sort(a+1,a+1+n,cmp);
	for(register int i=1;i<=n;++i){
		LIS[i]=max(LIS[i],BIT.ask(a[i].y)+1);
		BIT.add(a[i].y,LIS[i]);
	}
	for(register int i=1;i<=n;++i){
		g[LIS[i]].push_back(i);
		m=max(m,LIS[i]);
	}
	for(register int i=0;i<(int)g[1].size();++i){
		dp[g[1][i]]=1ll*a[g[1][i]].x*a[g[1][i]].y;
	}
	for(register int i=1;i<=m;++i){
		sort(g[i].begin(),g[i].end(),cmp_x);
	}
	tot=0;
	for(register int i=0;i<(int)g[1].size();++i){
		++tot;
		X[tot]=a[g[1][i]].x;
		Y[tot]=a[g[1][i]].y;
	}
	reverse(Y+1,Y+1+tot);
	for(register int k=2;k<=m;++k){
		int sx=g[k].size();
		for(register int i=1;i<=tot_node;++i)
			t[i].ls=t[i].rs=0;
		tot_node=ROOT=0;
		for(vector<int>::iterator it=g[k].begin();it!=g[k].end();++it){
			int u=*it;
			int l=upper_bound(Y+1,Y+1+tot,a[u].y)-Y;
			if(Y[l]>a[u].y || l>tot) --l;
			l=tot-l+1;
			int r=upper_bound(X+1,X+1+tot,a[u].x)-X;
			if(X[r]>a[u].x || r>tot) --r;
			query(ROOT,l,r,1,g[k-1].size(),u);
		}
		dfs(ROOT,1,tot,k);
		tot=0;
		for(vector<int>::iterator it=g[k].begin();it!=g[k].end();++it){
			++tot;
			X[tot]=a[*it].x;
			Y[tot]=a[*it].y;
		}
		reverse(Y+1,Y+1+tot);
	}
	LL ans=0x3f3f3f3f3f3f3f3f;
	for(register int i=1;i<=n;++i){
		if(LIS[i]==m){
			ans=min(ans,dp[i]+1ll*(T-a[i].x)*(T-a[i].y));
		}
	}
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：AzusaCat (赞：6)

给你一个长、宽均为 $T$ 的网格图，左下角坐标为 $(0,0)$，右上角坐标为 $(T,T)$。现在图上面有 $n$ 个点（一定在格点上），你需要选择一些点，使得你选择的点按 $x$ 从小到大排序后 $y$ 也单调上升。最大化选的点的数量；在此基础上，让排序好的相邻的两点形成的矩形的面积之和最小。输出最小面积和。$T\leqslant 10^6,N\leqslant 2\times 10^5$。

首先，对于最大化选点的数量，这可以看作按 $x$ 排好序之后求一遍 LIS。为了方便，我们把按 $x$ 排完序的点重编号，以后认为 $i<j$ 等价于 $x_i<x_j$（题目保证了不存在两个点使得 $x$ 或 $y$ 相等）。我们设 $l_i$ 为以 $i$ 结尾的 LIS 的长度。

第二问比较明显还需要 dp 求解，为了保证选的点数最多，我们只能在 $l$ 值相差为 $1$ 的点之间进行转移。具体地，设 $f[i]$ 为选择了以 $i$ 为结尾的 $l_i$ 个点矩形面积和的最小值，那么转移显然：
$$
f[i]=\min_{l_i=l_j+1,j<i,y_j<y_i}f[j]+(x_i-x_j)(y_i-y_j)
$$
这样就有了一个 $O(n^2)$  的朴素算法。

这个东西可能看起来有一些像斜率优化，但是并不行，因为拆开括号以后既有 $x_iy_j$ 项又有 $x_jy_i$ 项，斜率优化做不了这个。

我们考虑另外一个优化办法——决策单调性。我们先把括号拆开：
$$
f[i]=\min_{l_i=l_j+1,j<i,y_j<y_i}f[j]+x_iy_i-x_iy_j-x_jy_i+x_jy_j
$$
假设现在有两个决策点 $j,k\ (j<k)$，正在进行决策的是 $i$，那么 $j$ 比 $k$ 优当且仅当
$$
f[j]+x_iy_i-x_iy_j-x_jy_i+x_jy_j\leq f[k]+x_iy_i-x_iy_k-x_ky_i+x_ky_k\\
f[j]-x_iy_j-x_jy_i+x_jy_j\leq f[k]-x_iy_k-x_ky_i+x_ky_k\\
(y_k-y_j)x_i+(x_k-x_j)y_i\leq f[k]-f[j]+x_ky_k-x_jy_j
$$
我们注意到，对于两个 $l$ 相同的点 $j,k$，若 $x_j<x_k$，那么一定有 $y_j>y_k$。因为如果依旧有 $y_j<y_k$ 那么 $l_k$ 就可以从 $l_j$ 转移过来，它们的 $l$ 就不相等了。反过来同理。

那么如果我们把 $x_i$，$y_i$ 看作变量，那么 $j$ 比 $k$ 优的情况对应了坐标系里的一个半平面（也就是不等式的解集），而且因为我们钦定 $j>k$，那么这个半平面一定长这个样子 

![](https://cdn.luogu.com.cn/upload/image_hosting/cbauz78j.png)

其中蓝色为解集部分，解集一定是一条斜率为正的直线的下方。那么要更新的点一定被这条直线分为了两部分。那么如果在 $i$ 时，$j$ 比 $k$ 优（即点 $i$ 在蓝色区域内），那么对于 $u>i$，$j$ 也一定比 $k$ 优。这样的话对于一组 $l$ 相同的询问，他们的最优决策位置一定是单调不增的。这就可以决策单调性了。

注意一下上面的分析都忽略了 $x$ 和 $y$ 的限制，那么如何满足呢？注意到对于任何一个点，可行的决策点都是一个区间，所以对每一排开一个线段树，线段树分治一下，把询问丢到所有符合要求的区间内，这样如果一个询问被挂在了某个区间内，区间内的点都可以转移到它，最后把答案取 $\max$ 就好了。如果以分治或者二分+单调队列计算决策单调性，总的复杂度为 $O\left(n(\log^2n+\log T)\right)$。

需要特殊注意的是每次计算一个区间时，不要直接和 $f[mid]$ 比较，需要再开一个变量记录只包含这段区间中的决策点时的最小值，要不然有时已经算过的 $f[mid]$ 比整个区间的决策都优，这样就会错误。



代码：

```cpp
#include<bits/stdc++.h>
#define pb push_back
using namespace std;
struct flower
{
    int x,y,ans;
}c[200015];
typedef long long ll;
ll const inf=1e12;
int tree[1000005],T;
ll f[200015];
void modify(int x,int y){x++;for(int i=x;i<=T+1;i+=(i&(-i)))tree[i]=max(tree[i],y);}
int ask(int x){x++;int res=0;for(int i=x;i;i-=(i&(-i)))res=max(res,tree[i]);return res;}
bool cmp(flower x,flower y){return x.x<y.x;}
vector<int>v[200015],buc[1000005];
void insert(int l,int r,int x,int id,int d)
{
    if(c[v[d-1][l]].x>c[id].x||c[v[d-1][r]].y>c[id].y)return;
    if(c[v[d-1][l]].x<c[id].x&&c[v[d-1][l]].y<c[id].y&&
       c[v[d-1][r]].x<c[id].x&&c[v[d-1][r]].y<c[id].y){buc[x].pb(id);return;}
    int mid=(l+r)>>1;
    insert(l,mid,x*2,id,d);insert(mid+1,r,x*2+1,id,d);
}
void solve(int ql,int qr,int l,int r,int x,int d)
{
    if(l>r)return;
    int mid=(l+r)>>1,id=0;
    ll val=inf;//注意这里
    for(int i=ql;i<=qr;i++)
        if(f[v[d-1][i]]+1ll*(c[buc[x][mid]].x-c[v[d-1][i]].x)*
        (c[buc[x][mid]].y-c[v[d-1][i]].y)<val)
            val=f[v[d-1][i]]+1ll*(c[buc[x][mid]].x-c[v[d-1][i]].x)*
        (c[buc[x][mid]].y-c[v[d-1][i]].y),id=i;
    f[buc[x][mid]]=min(f[buc[x][mid]],val);
    solve(id,qr,l,mid-1,x,d);solve(ql,id,mid+1,r,x,d);//注意x是不变的
}
void dfs(int l,int r,int x,int d)
{
    solve(l,r,0,buc[x].size()-1,x,d);
    buc[x].clear();
    if(l==r)return;
    int mid=(l+r)>>1;
    dfs(l,mid,x*2,d),dfs(mid+1,r,x*2+1,d);
}
inline int read()
{
    int x=0;
    char ch=getchar();
    while(!isdigit(ch))ch=getchar();
    while(isdigit(ch))x=x*10+ch-48,ch=getchar();
    return x;
}
int main()
{
    int n;
    n=read(),T=read();
    for(int i=1;i<=n;i++)c[i].x=read(),c[i].y=read();
    n+=2;
    c[n].x=c[n].y=T;
    sort(c+1,c+n+1,cmp);
    int t=0;
    for(int i=1;i<=n;i++)
        c[i].ans=ask(c[i].y)+1,modify(c[i].y,c[i].ans),v[c[i].ans].pb(i);
    for(int i=1;i<=n;i++)t=max(t,c[i].ans),f[i]=(c[i].ans==1?0:inf);
    for(int i=2;i<=t;i++)//处理第i层
    {
        for(auto j:v[i])insert(0,v[i-1].size()-1,1,j,i);//线段树分治
        dfs(0,v[i-1].size()-1,1,i);//计算答案
    }
    ll ans=inf;
    for(int i=1;i<=n;i++)if(c[i].ans==t)ans=min(ans,f[i]);
    printf("%lld",ans);
    return 0;
}
```



---

## 作者：Liuxizai (赞：4)

[My Blog](https://liuxizai.ac.cn/archives/solution-lg5244.html)

## Description

在 $T\times T$ 的正方形网格上（左下角格点坐标为 $(0,0)$，右上角为 $(T,T)$，共 $(T+1)^2$ 个格点），给定 $n$ 个关键点，保证横纵坐标都互不相同。要求选出尽可能多的关键点，使其按横坐标从小到大排序后，纵坐标也单调增。在此基础上，最小化以相邻两点为对角线的长方形面积总和。

$1\le n\le 2\times 10^5,1\le T\le 10^6$

## Solution

首先要做一个二维 LIS，按横坐标排序后用树状数组维护转移即可。这部分是平凡的。

按照以每个点结尾的最长 LIS 长度分层，第二问的转移都应当发生在相邻层之间，这样我们就有了一个 $O(n^2)$ 的做法。

接下来考虑优化。由于涉及到正方形面积，很容易让人想到决策单调性。

对于同层的点，如果我们将其按横坐标从小到大排序，纵坐标一定单调减。考虑第 $t-1$ 层的两点 $A(x_a,y_a),B(x_b,y_b),x_a<x_b,y_a>y_b$ 和第 $t$ 层的两点 $C(x_c,y_c),D(x_d,y_d),x_c<x_d,y_c>y_d$，这里假设 $A,B$ 均能转移到 $C,D$。则我们考虑
$$
f(A, C)+f(B, D)=(x_c-x_a)(y_c-y_a)+(x_d-x_b)(y_d-y_b)\\
f(A, D)+f(B, C)=(x_d-x_a)(y_d-y_a)+(x_c-x_b)(y_c-y_b)
$$
两式联立化简后，问题转化为判断 $(x_a-x_b)(y_c-y_d)+(x_c-x_d)(y_a-y_b)$ 的正负，于是我们得到
$$
f(A,C)+f(B,D)>f(A,D)+f(B,C)
$$
中间的计算过程不多赘述，也很推荐通过画图来理解这一不等式，更加直观，只不过用电脑画个好看的图放题解里太麻烦 。

这是反向的四边形不等式，故本题有递减的决策单调性（[link](https://liuxizai.ac.cn/archives/quadrangle-inequality-properties.html#二分栈)），常规的做法是用二分栈来维护决策点，或者由于分层转移的特性，我们也可以使用分治，但本题中由于每个决策点只能向一个区间进行转移，直接应用这两种方法都行不通。

对于二分栈来说，我们可能会想在到达某个决策点作用域左端点时将其插入单调栈，但问题在于，此时这个决策点可能是劣的，无法替代栈顶，但这并不意味着这个决策点就可以被舍弃，因为其可能拥有比栈顶更大的作用域，可以在离开栈顶作用域后入栈，如果对一个决策点多次尝试入栈，时间复杂度就难以保证了。

对于分治也存在类似的问题，我们无法直接将决策点一分为二，分配给左右两侧的 dp 数组。

于是，我们不得不付出一个 $\log$ 的代价来解决这一问题。考虑使用和线段树分治类似的方法，将每个决策点放到作用域内的 $\log$ 个线段树结点上，然后遍历线段树，对于每个结点，现在每个决策点的作用域都覆盖当前结点对应的整个区间，所以直接使用二分栈或分治进行转移即可。总复杂度 $O(n\log^2 n)$。

每个线段树结点都应视作一个子问题，所以应在 dp 值算出后再进行合并，否则可能会出现在另一个结点上做出的决策优于当前结点上的所有决策点，导致当前结点无法转移的问题。

值得一提的是，我们需要线段树分治的本质原因在于决策单调性和可转移区间的移动方向不一致，如果移动方向一致的话，例如本题如果改为最大化面积，决策单调性变为递增，则直接使用二分队列或分治都是没有问题的。

## Code

```cpp
namespace Main{
    const int N = 200005;
    const int V = 1000005;
    int n, t, f[N];
    pair<int, int> flower[N];
    vector<pair<int, int>> layer[N];
    vector<ll> dp[N];
    struct bit{
        int t[V];
        inline int lowbit(int x) { return x & -x; }
        void modify(int x, int k) { for(; x < V; x += lowbit(x)) t[x] = max(t[x], k); }
        int query(int x) { int res = 0; for(; x; x -= lowbit(x)) res = max(res, t[x]); return res; }
    }tree;
    struct segtree{
        struct segtree_node{
            int l, r;
            vector<int> trans;
        }t[N<<2];
        #define ls p<<1
        #define rs p<<1|1
        void build(int p, int l, int r){
            t[p].l = l, t[p].r = r, t[p].trans.clear();
            if(l == r) return;
            int mid = l + r >> 1;
            build(ls, l, mid), build(rs, mid + 1, r);
        }
        void add(int p, int l, int r, int k){
            if(t[p].l >= l && t[p].r <= r){
                t[p].trans.push_back(k);
                return;
            }
            int mid = t[p].l + t[p].r >> 1;
            if(mid >= l) add(ls, l, r, k);
            if(mid < r) add(rs, l, r, k);
        }
        void calc(int d, vector<int> &sp, int l, int r, int sl, int sr){
            if(l > r) return;
            int mid = l + r >> 1, s = -1;
            ll val = 1e18;
            for(int i = sl; i <= sr; i++){
                ll tmp = dp[d - 1][sp[i]] + 1ll * (layer[d][mid].first - layer[d - 1][sp[i]].first) * (layer[d][mid].second - layer[d - 1][sp[i]].second);
                if(tmp < val) { val = tmp; s = i; }
            }
            dp[d][mid] = min(dp[d][mid], val);
            calc(d, sp, l, mid - 1, s, sr), calc(d, sp, mid + 1, r, sl, s);
        }
        void solve(int p, int d){
            if(!t[p].trans.empty()) calc(d, t[p].trans, t[p].l, t[p].r, 0, t[p].trans.size() - 1);
            if(t[p].l == t[p].r) return;
            solve(ls, d), solve(rs, d);
        }
        #undef ls
        #undef rs
    }t2;
    void Main(){
        input(n, t);
        for(int i = 0; i < n; i++) input(flower[i].first, flower[i].second);
        sort(flower, flower + n);
        int mx = 0;
        for(int i = 0; i < n; i++){
            f[i] = tree.query(flower[i].second) + 1;
            tree.modify(flower[i].second, f[i]);
            layer[f[i]].push_back(flower[i]);
            mx = max(mx, f[i]);
        }
        layer[0].emplace_back(0, 0), layer[++mx].emplace_back(t, t);
        dp[0] = {0};
        for(int i = 1; i <= mx; i++){
            t2.build(1, 0, layer[i].size() - 1);
            dp[i].resize(layer[i].size(), 1e18);
            for(int j = 0; j < layer[i - 1].size(); j++){
                int l = lower_bound(layer[i].begin(), layer[i].end(), layer[i - 1][j]) - layer[i].begin();
                int r = lower_bound(layer[i].begin(), layer[i].end(), layer[i - 1][j], [](pair<int, int> a, pair<int, int> b){
                    return a.second > b.second;
                }) - layer[i].begin() - 1;
                if(l <= r) t2.add(1, l, r, j);
            }
            t2.solve(1, i);
        }
        write(dp[mx][0]);
        return;
    }
} // namespace Main
```



---

## 作者：541forever (赞：3)

题目看上去求的是一个二维的 LIS 问题。考虑先将所有花按 $x$ 排序，预处理出到每个花 $i$ 时最多经过了 $c_i$ 朵花。接着考虑设 $f_i$ 表示到 $i$ 时再经过 $c_i$ 多花的前提下最少割了多少草。暴力转移显然：

$$f_i=\min_{c_j=c_i-1,x_j < x_i,y_j < y_i} f_j+(x_i-x_j)(y_i-y_j)$$

想要优化这个 dp，我们显然需要寻找一些性质。我们可以发现，若将所有花按 $c_i$ 分层后，对于同一层花 $i,j$ 若 $x_i>x_j$，则 $y_j$ 必定大于 $y_i$。所以我们大致可以往决策单调性上去靠。可以发现对于 $i$ 而言，若决策点 $j$ 比 $k$ 优，即 
$$f_j+(x_j-x_i)(y_j-y_i) \le f_k+(x_k-x_i)(y_k-y_i)$$

将式子拆开得到

$$f_j+x_jy_j+x_iy_i-x_iy_j-y_ix_j\le f_k+x_ky_k+x_iy_i-x_iy_k-y_ix_k$$

$$f_j+x_jy_j-f_k-x_ky_k\le x_i(y_j-y_k)+y_i(x_j-x_k)$$

因此我们可以发现若对于 $i$ 而言 $j$ 比 $k$ 优，且 $x_k>x_j$，则对于任意 $x_u>x_i$ 的 $u$ 而言，$j$ 都比 $k$ 优，因为此时 $x_j-x_k$ 的系数一定为变得更小，$y_j-y_k$ 的系数一定会变得更大，因此值显然增大，反之也是如此。

同时又因为对于同一层花 $i,j$ 若 $x_i>x_j$，则 $y_j$ 必定大于 $y_i$，则将同一层花按 $x$ 排序后，能转移到下一层花 $i$ 的一定是一段区间，因此考虑在每层花转移时，再前一层花上建一棵线段树，对该层的每朵花，在前一层的对应区间打上 tag，最后再根据决策单调性在线段树上分治地处理即可。

具体实现可以参见[代码](https://www.luogu.com.cn/paste/d5xecffz)

Tips:

最后要走到 (T,T) 这个点才能结束。

---

## 作者：1saunoya (赞：2)

决策单调性+线段树分治。


我们考虑这个其实就是要搞一个 LIS。

每次对 LIS 更新。

然后直接对 LIS = i 更新 LIS = i+1。

$f_i = \max\{ f_j + (x_i - x_j) \times (y_i - y_j)\}$。

对于两个决策点 $j,k$。

$j' - k' = f_j + (x_i - x_j) \times (y_i - y_j) - (f_k + (x_i - x_k) \times (y_i - y_k))$

$= f_j - f_k + x_ jy_j - x_ky_k  - (x_iy_j+x_jy_i-x_iy_k-x_ky_i)$。

$= (f_j - f_k) + x_ jy_j - x_ky_k - x_i(y_j - y_k) - y_i(x_j-x_k)$。


如果 $x_j \leq x_k, y_j \leq y_k$，那么这两个点不可能同时作为两个决策点。

所以仅有情况: $[x_j \leq x_k]$, $[y_j > y_k]$ 可以作为两个决策点。

而这个显然具有决策单调性。


对于转移的话，直接分层搞搞就可以了。


```cpp
/*
 _      _  _ _ _ _ _   _      _
\_\   /_/ \_\_\_\_\_\ \_\   /_/
 \_\ /_/      \_\      \_\ /_/
  \_\_/       \_\       \_\_/
   \_\         \_\       \_\
   \_\     \_\ \_\       \_\
   \_\      \_\\_\       \_\
*/
#include <bits/stdc++.h>
#define rep(i,x,y) for(int i=x;i<=y;i++)
#define per(i,x,y) for(int i=x;i>=y;i--)
#define sz(v) (int)v.size()
#define int long long
using namespace std;
template<class T>
void read(T&x) {
	static int c,neg;
	x=neg=0;c=getchar();
	while(!isdigit(c)){if(c=='-')neg=1;c=getchar();}
	while(isdigit(c)){x=x*10+c-48;c=getchar();}if(neg)x=-x;
}
template<class T>
void print(T x,char c='\n'){
	static int st[233],top;
	if(x<0)putchar('-'),x=-x;
	do{st[++top]=x%10;x/=10;}while(x);
	while(top)putchar(st[top--]+48);putchar(c);
}
template<class T>
void cmax(T&x,const T&y){
	x=(x>y)?x:y;
}
template<class T>
void cmin(T&x,const T&y){
	x=(x<y)?x:y;
}
struct h{
	int x,y;
	h(){
		x=0;
		y=0;
	}
	h(int _,int __){
		x=_;
		y=__;
	}
	bool operator<(const h&rhs)const{
		if(x!=rhs.x)return x<rhs.x;
		return y<rhs.y;
	}
};
int n,T;
const int N=2e5+52;
h a[N];
int lis[N];
int yy[N];
vector<int>pp[N];
int c[N];
int lowbit(int x){
	return x&-x;
}
void upd(int x,int y){
	for(;x<N;x+=lowbit(x)){
		cmax(c[x],y);
	}
}
int query(int x){
	int ans=0;
	for(;x;x^=lowbit(x)){
		cmax(ans,c[x]);
	}
	return ans;
}
int f[N];
const int inf=1e12;
vector<int>buc[N<<2];
void rebuild(int l,int r,int p){
	buc[p].clear();
	if(l==r){
		return;
	}
	int mid=l+r>>1;
	rebuild(l,mid,p<<1);
	rebuild(mid+1,r,p<<1|1);
}
void ins(int l,int r,int p,int x,const std::vector<int>&qwq){
	if(a[qwq[l]].x>a[x].x||a[qwq[r]].y>a[x].y){
		return;
	}
	if(a[qwq[l]].x<a[x].x&&a[qwq[l]].y<a[x].y&&a[qwq[r]].x<a[x].x&&a[qwq[r]].y<a[x].y){
		buc[p].push_back(x);
		return;
	}
	int mid=l+r>>1;
	ins(l,mid,p<<1,x,qwq);
	ins(mid+1,r,p<<1|1,x,qwq);
}
int get(int x,int y,int xx,int yy){
	return (x-xx)*(y-yy);
}
int get(h x,h y){
	return get(x.x,x.y,y.x,y.y);
}
void solve(int ql,int qr,int l,int r,
const std::vector<int>&qwq,const std::vector<int>&qaq){
	if(l>r){
		return;
	}
	int mid=l+r>>1,val=inf,id=0;
	rep(i,ql,qr){
		if(f[qaq[i]]+get(a[qwq[mid]],a[qaq[i]])<val){
			val=f[qaq[i]]+get(a[qwq[mid]],a[qaq[i]]);
			id=i;
		}
	}
	cmin(f[qwq[mid]],val);
	solve(id,qr,l,mid-1,qwq,qaq);
	solve(ql,id,mid+1,r,qwq,qaq);
}
void solve(int l,int r,int p,int dep){
	solve(l,r,0,sz(buc[p])-1,buc[p],pp[dep]);
	if(l==r){
		return;
	}else{
		int mid=l+r>>1;
		solve(l,mid,p<<1,dep);
		solve(mid+1,r,p<<1|1,dep);
	}
}
signed main(){
	read(n);read(T);
	int t=0;
	rep(i,1,n){
		int x,y;
		read(x);read(y);
		a[i]=h(x,y);yy[++t]=y;
	}
	a[++n]=h(0,0);yy[++t]=0;
	a[++n]=h(T,T);yy[++t]=T;
	sort(a+1,a+n+1);sort(yy+1,yy+t+1);t=unique(yy+1,yy+t+1)-yy-1;
	int mx=0;
	rep(i,1,n){
		int f=lower_bound(yy+1,yy+t+1,a[i].y)-yy;
		lis[i]=query(f)+1;
		cmax(mx,lis[i]);
		upd(f,lis[i]);
		pp[lis[i]].push_back(i);
	}
	memset(f,0x3f,sizeof(f));
	for(auto x:pp[1]){f[x]=a[x].x*a[x].y;}
	rep(i,2,mx){
		int sz=sz(pp[i-1]);rebuild(0,sz-1,1);
		for(auto x:pp[i]){ins(0,sz-1,1,x,pp[i-1]);}
		solve(0,sz-1,1,i-1);
	}
	print(f[n]);
	return 0;
}
```

---

## 作者：LIdox1536513344 (赞：2)

（看了楼上大佬题解看不太懂，决定自己改进一下）
# 题目大意
Bessie的表妹Ella和Bella正在参观农场。不幸的是，自从他们到达以来，他们一直在恶作剧。

在他们的最新计划中，他们决定尽可能多地割草。农场的草地是 T×T 的正方形。左下角是 (0,0) ，右上角是 (T,T) 。因此，正方形包含 (T+1)2 个格点（具有整数坐标的点）。

Ella和Bella计划从 (0,0) 开始并以每秒一个单位长度的速度运行到 (T,T) ，同时每只奶牛都握住非常锋利且非常有弹性的线的一端。任何被这根电线扫过的区域的草都会被切断。Ella和Bella可能采取不同的路径，但她们只会向上或者向右移动，从一个格点移动到另一个格点。

Bessie非常担心会切割太多的草，所以她发明了一个聪明的计划来限制Ella和Bella的路径。在整个草原上散布着 N 种花（1≤N≤2e5），每种花都在一个特定的格点上。 Bessie将从这些花中挑选一个子集 S ， S 集合中的花Ella和Bella都需要经过（Ella和Bella的路径都必须经过 S 中的所有花朵）。

Ella和Bella将会切割面积尽可能大的草，请帮助Bessie确定集合 SS 使得在 SS集合尽可能大的情况下被切割的草的面积最小。

# 题目分析
经过思考，我们发现骑士拉着线扫对Ella和Bella来说最优的情况就是划出一个矩形。

所以，问题变成了在 N 个点中选择某些点，排序后一一构成矩形（相邻的点），求构成的这些矩形的最小面积和。

 

将所有点按照其横坐标为第一关键字，纵坐标为第二关键字排序，靠前的点无法转移到靠后的点。用树状数组进行动态规划，我们可以得到以每个点为结尾的选取序列的最优长度。（相当于求以每个点结尾的LIS）并根据LIS的大小对点进行分层。

可以得出属于同一层的点横坐标递增，纵坐标递减。

 

接下来，我们只需要考虑层与层之间的转移。（本层点的LIS一定是由上一层点的LIS转移过来的）

转移方程如下：

 

dpi​ =Minj （j为上一层点 且 xj​≤xi​, yj​≤yi）​ ​{dpj ​+ (xi​−xj​) ∗ (yi​−yj​) } 


把后一项拆开，得：

dpi​ =Minj （j为上一层点 且 xj​≤xi​, yj​≤yi）​ ​{dpj ​+ xj​yj​ − xi​yj ​− xj​yi​ } +xiyi

考虑 j,k 两处转移，令 j的转移 优于 k  ，则

dpj​ + xj​yj​ − xi​yj ​− xj​yi​  ≤ dpk​ + xk​yk​ − xi​yk​ − xk​yi​

(yk​−yj​) xi​+(xk​−xj​)yi​ ≤ dpk​ + xk​yk​−dpj​−xj​yj​


注意到 yk​−yj​和 xk​−xj​必然一正一负，因此这个半平面一定会将下一层的点分为前后两部分，因而若排除掉 xj​≤xi​,yj​≤yi​的限制，该 DP 的转移具有决策单调性。

那么，先用线段树分治处理转移，再用决策单调性优化转移即可。
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN=3e5+10;
const int MAXT=1e6+10;
const ll Inf=1e18+7;
struct Node{
	int x,y;
}p[MAXN];
inline bool cmpx(Node a,Node b){return a.x==b.x?a.y<b.y:a.x<b.x;}

int T,n,m,s;
int layer[MAXN];
ll dp[MAXN];
int BIT[MAXT];
vector<int> pos[MAXN];
inline int lowbit(int x){return x&(-x);}
inline void Modify(int x,int v){for(int i=x;i<=T;i+=lowbit(i)) BIT[i]=max(BIT[i],v);}
inline int Query(int x){int res=0;for(int i=x;i;i-=lowbit(i))res=max(res,BIT[i]);return res;}

struct Segment_Tree{
	struct Node{
		int ls,rs;
		vector<int> trans;
	}a[MAXN<<1];
	
	int n,size,rt;
	vector<int> point,tmp;
	
	inline void Build(int &rt,int l,int r){
		rt=++size;
		a[rt].ls=a[rt].rs=0;
		a[rt].trans.clear();
		if(l==r) return;
		int mid=(l+r)>>1;
		Build(a[rt].ls,l,mid);
		Build(a[rt].rs,mid+1,r);
	}
	inline void Init(vector<int> tmp){
		point=tmp;
		n=tmp.size();
		rt=size=0;
		Build(rt,0,n-1);
	}
	inline void Modify(int rt,int l,int r,int x){
		if(p[x].x>=p[point[r]].x&&p[x].y>=p[point[l]].y){
			a[rt].trans.push_back(x);
			return;
		}
		if(p[x].x<=p[point[l]].x||p[x].y<=p[point[r]].y) return;
		int mid=(l+r)>>1;
		Modify(a[rt].ls,l,mid,x);
		Modify(a[rt].rs,mid+1,r,x);
	}
	inline void modify(int x){
		Modify(rt,0,n-1,x);
	}
	
	inline void Solve(int l,int r,int ql,int qr){
		ll ans=Inf;int from=0;
		int mid=(l+r)>>1,now=tmp[mid];
		for(int i=ql;i<=qr;++i){
			int pos=point[i];
			ll res=dp[pos]+1ll*(p[now].x-p[pos].x)*(p[now].y-p[pos].y);
			if(res<ans){
				ans=res;
				from=i;
			}
		}
		dp[now]=min(dp[now],ans);
		if(l<mid) Solve(l,mid-1,from,qr);
		if(mid<r) Solve(mid+1,r,ql,from);
	}
	inline void Work(int rt,int l,int r){
		if(a[rt].trans.size()){
			tmp=a[rt].trans;
			Solve(0,tmp.size()-1,l,r);
		}
		if(l==r) return;
		int mid=(l+r)>>1;
		Work(a[rt].ls,l,mid);
		Work(a[rt].rs,mid+1,r);
	}
	inline void work(){
		Work(rt,0,n-1);
	}
}ST;
int main(){
	scanf("%d%d",&n,&T);
	for(int i=1;i<=n;++i)
		scanf("%d%d",&p[i].x,&p[i].y);
	sort(p+1,p+n+1,cmpx);
	
	for(int i=1;i<=n;++i){
		layer[i]=Query(p[i].y)+1;
		Modify(p[i].y,layer[i]);
		pos[layer[i]].push_back(i);
		m=max(m,layer[i]);
		//cout<<layer[i]<<' ';
	}
	//cout<<111<<endl;
	for(int i=0,now;i<(int)pos[1].size();++i){
		now=pos[1][i];
		dp[now]=1ll*p[now].x*p[now].y;
	}
	for(int i=2,now;i<=m;++i){
		ST.Init(pos[i-1]);
		for(int j=0;j<(int)pos[i].size();++j){
			now=pos[i][j];
			dp[now]=Inf;
			ST.modify(now);
		}
		ST.work();
	}
	ll ans=Inf;
	//cout<<111<<endl;
	for(int i=0;i<(int)pos[m].size();++i){
		int now=pos[m][i];
		ans=min(ans,dp[now]+1ll*(T-p[now].x)*(T-p[now].y));
	}
	printf("%lld\n",ans);
	return 0;
}
```


时间复杂度  O(N log2N)


 

  
 

---

## 作者：MurataHimeko (赞：1)

有点无聊。

首先按照 $x$ 坐标排序。

设 $dis_i$ 表示从 $(0,0)$ 到当前点最多经过几个点。然后按照 $dis_i$ 分层，只有相邻的两层之间才能转移。

令 $S(i,j)$ 表示点 $i$ 和点 $j$ 围成的矩形的面积。

那么转移形如 $f_k = \min(f_i + S(i,k))$，复杂度 $O(n^2)$。


设 $i,j$ 是 $dis_k - 1$ 层的两个决策点，且 $x_i<x_j$。如果对于 $k$ 来说，$i$ 比 $j$ 更优，那么当 $k$ 更大时，$i$ 会一直比 $j$ 更优。也就是说存在决策单调性。证明的话，画画图很清晰。具体来说就是，去掉公共部分后，随着 $k$ 的增加，$S(i,k)$ 剩下的面积单调不增，$S(j,k)$ 剩下的面积单调不降。

还有一个问题，就是不同点的转移区间是不同的。这个是好解决的，类似线段树分治那样把点挂到线段树上的区间即可。

总复杂度 $O(n \log^2 n)$。

```cpp
#include <bits/stdc++.h>
#define rep(i, f, t) for(int i(f); i <= t; ++i)
#define re(i, t) for(int i(1); i <= t; ++i)
#define per(i, t, f) for(int i(t); i >= f; --i)
#define pe(i, t) for(int i(t); i >= 1; --i) 
#define nx(i, u) for(int i(head[u]); i; i = e[i].nxt)
typedef long long ll; 
using namespace std;
typedef pair <int, int> pii;
#define pb push_back
#define fi first
#define se second
#define ix(l, r) ((l + r) | (l != r)) 
#define ls (ix(l, mid))
#define rs (ix(mid + 1, r))
#define mp(i, j) (make_pair(i, j))
#define inf (int)(1e9+7)
#define INF 0x3f3f3f3f3f3f3f3f

namespace IO {
char buf[1 << 21], *p1 = buf, *p2 = buf, buf1[1 << 21];
inline char gc() {return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++;}
template<class I>
inline void read(I &x) {x = 0;I f = 1;char c = gc();while (c < '0' || c > '9') {if (c == '-') {f = -1;} c = gc();}while (c >= '0' && c <= '9') {x = x * 10 + c - '0';c = gc();}x *= f;}
template<class I>
inline void write(I x) {if (x == 0) {putchar('0');return;}I tmp = x > 0 ? x : -x;if (x < 0) {putchar('-');}int cnt = 0;while (tmp > 0) {buf1[cnt++] = tmp % 10 + '0';tmp /= 10;}while (cnt > 0)putchar(buf1[--cnt]);}
#define outn(x) write(x), putchar('\n')
#define out(x) write(x), putchar(' ')
} using namespace IO;
#define look_memory cerr<<abs(&sT-&eD)/1024.0/1024<<'\n'
int st;

const int N = 2e5 +5;
int n, m; 
pii p[N];
int base[N], len;
int t[N*5];
int dis[N];

void upd (int p, int w) {
    for(int i(p); i <= m; i += (i & (-i))) {
        t[i] = max(t[i], w);
    }
}

int query (int p) {
    int res = 0;
    for(int i(p); i; i -= (i & (-i))) {
        res = max(res, t[i]);
    }
    return res;
}

vector<int>vec[N]; 
ll f[N];
int rt;
vector<int>tr[N<<1];

void build (int l, int r) {
    tr[ix(l, r)].clear();
    if(l == r) return ;
    int mid = (l + r) >> 1;
    build(l, mid), build(mid + 1, r);
}

void ins (int l, int r, int dl, int dr, int w) {
    if(dl <= l && r <= dr) {
        tr[ix(l, r)].pb(w);
        return ;
    }
    int mid = (l +r) >> 1;
    if(dl <= mid) ins(l, mid, dl, dr, w);
    if(dr > mid) ins(mid + 1, r, dl, dr, w);
}

void solve (int l, int r, int L, int R) {
    if(l > r || L > R) return ; 
    int mid = (l + r) >> 1;
    int u = vec[0][mid];
    ll mn = INF, id = L;
    rep(i, L, R) {
        int v = vec[rt-1][i]; 
        ll w = f[v] + 1ll * (p[u].fi - p[v].fi) * (p[u].se - p[v].se);
        if(w < mn) {
            mn = w;
            id = i;
        }
    }
    f[u] = min(f[u], mn);
    solve(mid + 1, r, L, id);
    solve(l, mid - 1, id, R);
}

void work (int l, int r) {
    if((int)tr[ix(l,r)].size()) {
        vec[0].clear();
        for(int i : tr[ix(l, r)]) {
            vec[0].pb(i);
        }
        solve(0, (int)vec[0].size() - 1, l, r);
    }
    if(l == r) return ;
    int mid = (l + r) >> 1;
    work(l, mid), work(mid+ 1, r);
}

int main () { 
    read(n),read(m);
    memset(f, 0x3f, sizeof(f));
    re(i, n) {
        read(p[i].fi), read(p[i].se);
    }
    sort(p + 1, p + n + 1);
    int mx = 0;
    re(i, n) {
        dis[i] = query(p[i].se) + 1;
        upd(p[i].se, dis[i]);
        vec[dis[i]].pb(i);
        mx = max(mx, dis[i]);
    }
    for(int i : vec[1]) {
        f[i] = 1ll * p[i].fi * p[i].se;
    }
    for(rt = 2; rt <= mx; ++rt) {
        int L = vec[rt-1].size() - 1;
        build(0, L);
        for(int i : vec[rt]) {
            int al = 0, ar = L;
            while(al <= ar) {
                int x = (al + ar) >> 1;
                if(p[vec[rt-1][x]].se < p[i].se) ar = x - 1;
                else al = x + 1;
            }
            int bl = al;
            al = 0, ar = L;
            while(al <= ar) {
                int x = (al + ar) >> 1;
                if(p[vec[rt-1][x]].fi < p[i].fi) al = x + 1;
                else ar = x - 1;
            }
            int br = ar;
            ins(0, L, bl, br, i);
        }
        work(0, L);
    }
    ll ans =INF;
    for(int i : vec[mx]) {
        ans = min(ans, f[i] + 1ll * (m - p[i].fi) * (m - p[i].se));
    } 
    outn(ans);
    return 0;
}   
```


---

## 作者：huhangqi (赞：0)

将每个点按照其为最后一个点的最长上升子序列长度分层，这个点则通过上一层转移。

那么很容易就能够得到暴力代码，时间复杂度是 $O(n^2)$ 的。

但是这样明显还是无法通过。

我们观察转移式为：

$$
dp_i=dp_j+(x_i-x_j)\times (y_i-y_j)
$$

无法使用斜率优化，考虑能否使用决策单调性来优化。

假设现在我们要给下标为 $a$ 的点找一个上一层的点进行转移，上一层存在 $i$ 和 $j$ 两个点，$i$ 优于 $j$，并且 $i<j$ 时（按照 $x$ 的大小排序），可以得到：

$$
dp_i+(x_a-x_i)\times (y_a-y_i)\le dp_j+(x_a-x_j)\times (y_a-y_j)\\
dp_i+x_iy_i-x_iy_a-x_ay_i\le dp_j+x_jy_j-x_jy_a-x_ay_i\\
x_a(y_j-y_i)+y_a(x_j-x_i)\le dp_j+x_jy_j-dp_i-x_iy_i
$$

其中 $y_j-y_i$ 小于 $0$ 而 $x_j-x_i$ 大于 $0$，所以 $a$ 所在的这一层中下标越大的左式的值越小（在同一层中下标按照 $x$ 排序，而在同一层中 $x$ 越大则 $y$ 越小，所以左式递减），可以得到在同一层中下标大于 $a$ 的点决策点一定小于 $i$，这是因为对于大于 $i$ 的点都可以代入上述的 $j$ 中，而 $i$ 一定具有更优，所以具有单调性，可以通过决策单调性来优化。

但是，我们的转移是有要求的，从 $a$ 转移到 $b$ 一定要满足 $x_a<x_b$ 且 $y_a<y_b$，所以存在一个范围，只有在这个范围内才能够转移，而每个点的转移范围是不一样的，而且这明显会影响我们的决策。

这时我们可以想到在某个范围内，需要进行一些操作处理来得到答案，可以使用类似线段树分治的写法，线段树内存储某一段上一层的点的范围内全部都可以转移到的点。

我们通过二分或者直接在线段树内部处理，得到一个范围，再把这个点加入到这个范围内，通过决策单调性在内部进行处理即可。

由于一个点在线段树内出现次数是 $\log n$ 级别的，通过决策单调性求答案是 $n\log n$ 级别，由于线段树内出现 $\log n$ 次，所以最终的时间复杂度是 $O(n\log^2n)$。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,T,d[200005],cnt,f[200005],dp[200005];
struct P{
	int x,y;
}a[200005];
bool cmp(P a,P b){
	return a.x<b.x;
}
vector<int> e[200005];
struct ST{
	vector<int> c[800005];
	int ls[800005],rs[800005],id;
	void init(){
		id=0;
	}
	int New(){
		id++;
		c[id].clear();
		ls[id]=rs[id]=0;
		return id;
	}
	void change(int &p,int l,int r,int L,int R,int x){
		if(!p)p=New();
		if(l>=L&&r<=R)return c[p].push_back(x);
		int mid=l+r>>1;
		if(mid>=L)change(ls[p],l,mid,L,R,x);
		if(mid<R)change(rs[p],mid+1,r,L,R,x);
	}
	void CDQ(int p,int w,int l,int r,int L,int R){
		if(l>r)return;
		int mid=l+r>>1;
		int k,mi=1e18;
		for(int i=L;i<=R;i++){
			int tmp=dp[e[w][i]]+(a[c[p][mid]].x-a[e[w][i]].x)*(a[c[p][mid]].y-a[e[w][i]].y);
			if(tmp<mi)mi=tmp,k=i;
		}
		dp[c[p][mid]]=min(mi,dp[c[p][mid]]);
		CDQ(p,w,l,mid-1,k,R);
		CDQ(p,w,mid+1,r,L,k);
	}
	void query(int p,int w,int l,int r){
		if(!p)return;
		CDQ(p,w,0,c[p].size()-1,l,r);
		int mid=l+r>>1;
		query(ls[p],w,l,mid),query(rs[p],w,mid+1,r);
	}
}seg;
int findl(int x,int id){
	int l=0,r=e[id].size()-1;
	while(l<=r){
		int mid=l+r>>1;
		if(a[e[id][mid]].y<a[x].y)r=mid-1;
		else l=mid+1;
	}
	return r+1;
}
int findr(int x,int id){
	int l=0,r=e[id].size()-1;
	while(l<=r){
		int mid=l+r>>1;
		if(a[e[id][mid]].x<a[x].x)l=mid+1;
		else r=mid-1;
	}
	return l-1;
}
signed main(){
	cin>>n>>T;
	for(int i=1;i<=n;i++)cin>>a[i].x>>a[i].y;
	sort(a+1,a+n+1,cmp);
	a[++n]={T,T},a[0]={0,0};
	for(int i=0,w;i<=n;i++){
		if(!cnt||a[i].y>d[cnt])w=++cnt;
		else w=lower_bound(d+1,d+cnt+1,a[i].y)-d;
		d[w]=a[i].y;
		e[w].push_back(i);
	}
	memset(dp,0x3f,sizeof(dp));
	dp[0]=0;
	for(int i=2;i<=cnt;i++){
		int rt=0;
		seg.init();
		for(int j:e[i])seg.change(rt,0,e[i-1].size()-1,findl(j,i-1),findr(j,i-1),j);
		seg.query(rt,i-1,0,e[i-1].size()-1);
	}
	cout<<dp[n];
	return 0;
}

``````

---

## 作者：qwer6 (赞：0)

## 1. Description

在一个 $m\times m$ 的正方形中，给定 $n$ 个横，纵坐标均不相等的关键点。

现在有两个人从左下角 $(0,0)$ 的位置出发，前往右上角 $(m,m)$ 的位置，他们只会向上或者向右走，并且会让两人连线扫过的面积尽可能大。

现在要求求出一个点集 $S$，在两人的路径都经过这个点集中的点且 $S$ 尽可能大的前提下，使得两人连线扫过的面积尽可能小。

## 2. Solution

由于两人只会向上或向右走，因此点集 $S$ 中的点必须 $x$ 坐标递增，$y$ 坐标递增，那么 $S$ 的最大大小就是以 $x$ 为下标，$y$ 为权值的 LIS 的长度，这可以使用一个 $O(n\log n)$ 的算法求出，同时也可以求出一个 $LIS_i$ 表示以 $i$ 结尾的 LIS 的长度，这比较简单，就不细说了。

同时由于两人会让连线扫过的面积尽可能大，而两人一定会同时经过点集中的点，所以扫过的面积一定是若干个矩形的面积之和，这也是显然的。

因此我们得到了一个 $O(n^2)$ 的 DP 做法，将所有关键点按照 $x$ 坐标从小到大排序之后，假定 $f_i$ 表示点集以第 $i$ 个点结尾的最小代价，那么 $f_{i}=\min_{j=1}^{i-1} f_j+(x_i-x_j)\times (y_i-y_j)$ 其中 $j$ 需要满足 $y_j<y_i$ 且 $LIS_j=LIS_i-1$。

这个时间复杂度显然还不够优秀，因此我们考虑优化。

首先，由于 $i$ 只能从 $LIS_j=LIS_i-1$ 的 $j$ 转移过来，所以我们将所有关键点按照 $LIS$ 分层，转移只在层与层之间进行，那么显然的，同一层的关键点 $x$ 递增而 $y$ 递减，这十分好理解，因为如果在同一层中存在 $i,j$ 使得 $x_i<x_j$ 且 $y_i<y_j$，那么 $LIS_j\ge LIS_i+1$， $j$ 显然不应该出现在这一层。

然后我们尝试证明，对于处于同一层的 $i,j$ 如果都可以从上一层 $[l,r]$ 转移过来，那么当 $i<j$ 的时候，决策点递减，换句话说，如果假设 $i$ 的最优决策点为 $p$，$j$ 的最优决策点为 $q$，证明 $p>q$。

由于 $p$ 是 $i$ 的最优决策点，$q$ 是 $j$ 的最优决策点，那么就有：
$$
f_{p}+(x_i-x_p)\times (y_i-y_p)<f_q+(x_i-x_q)\times (y_i-y_q)\\
f_{p}+(x_j-x_p)\times (y_j-y_p)>f_q+(x_j-x_q)\times (y_j-y_q)\\
$$
上下相加即有：
$$
f_{p}+(x_i-x_p)\times (y_i-y_p)+f_q+(x_j-x_q)\times (y_j-y_q)<f_q+(x_i-x_q)\times (y_i-y_q)+f_{p}+(x_j-x_p)\times (y_j-y_p)\\
$$
也就是：
$$
-x_iy_p-x_py_i-x_jy_q-x_qy_j<-x_iy_q-x_qy_i-x_jy_p-x_py_j
$$
整理两边则有：
$$
(x_i-x_j)(y_p-y_q)+(y_i-y_j)(x_p-x_q)>0
$$
由于 $i<j$，由同一层的关键点 $x$ 递增而 $y$ 递减可以得到 $x_i-x_j<0,y_i-y_j>0$，因为这个式子大于 $0$，而 $y_p-y_q$ 与 $x_p-x_q$ 的正负性不同，所以 $x_p-x_q>0,y_p-y_q<0$，由此得到 $p>q$。

但是现在有一个问题，就是从 $j$ 转移到 $i$ 还要满足 $x_j<x_i$ 且 $y_j<y_i$，这反映到上一层的点中相当于一个区间。

因为 $x_j$ 递增，所以满足 $x_j<x_i$ 的点一定是一个形如 $[1,r]$ 的区间，同理因为 $y_j$ 递减，所以满足 $y_j<y_j$ 的点一定是一个形如 $[l,tot]$ 的区间，那么可以转移到 $i$ 的 $j$ 的区间就是 $[l,r]$。

而当 $i$ 增大的时候，整个区间整体右移，这显然是没有办法直接利用决策单调性写的，因为我们上面的证明基于：

> 处于同一层的 $i,j$ 如果都可以从上一层 $[l,r]$ 转移过来

所以我们需要让所有 $[l,r]$ 相同的 $i$ 放在一起，才可以利用决策单调性来写。

但是如果不做任何处理的话，时间复杂度就退化为 $O(n^2)$ 的了，这显然是无法接受的，因此要对 $i$ 的转移区间进行分割，然后分别求解，由此，我们联想到了线段树分治，也就是将询问挂在线段树上，那么在同一个节点上的询问就可以利用决策单调性来写了，具体可以使用分治来解决。

时间复杂度为 $O(n\log^2n)$，显然是可以通过此题了。

## 3. Code

```c++
/*by qwer6*/
/*略去缺省源与快读快写*/
const int N=2e5+5,M=1e6+5;
int n,m,len,tot;
ll ans;
int f[N];
pii a[N];
ll g[N];
vector<int>level[N];
struct Node{
	int ls,rs;
	vector<int>q;
	void init(){
		ls=rs=0;
		q.clear();
	}
}tree[N<<1]; 
#define mid (l+r>>1)
int New(){
	tree[++tot].init();
	return tot;
}
void change(int &p,int l,int r,int L,int R,int v){
	if(!p)p=New();
	if(L<=l&&r<=R){
		tree[p].q.push_back(v);
		return ;
	}
	if(mid>=L)change(tree[p].ls,l,mid,L,R,v);
	if(mid<R)change(tree[p].rs,mid+1,r,L,R,v);
}
void CDQ(int idx,int p,int l,int r,int L,int R){
	if(l>r)return ;
	ll mi=8e18;
	int x=tree[p].q[mid],place;
	for(int i=L,y;i<=R;i++){
		if(mi>cal(x,level[idx][i])){
			mi=cal(x,level[idx][i]);
			place=i;
		}
	}
	tomin(g[x],mi);
	CDQ(idx,p,l,mid-1,place,R);
	CDQ(idx,p,mid+1,r,L,place);
}
void dfs(int idx,int p,int l,int r){
	if(!p)return ;
	CDQ(idx,p,0,tree[p].q.size()-1,l,r); 
	if(l==r)return ;
	dfs(idx,tree[p].ls,l,mid),dfs(idx,tree[p].rs,mid+1,r);
}
#undef mid
int findL(int idx,int x){
	int l=0,r=level[idx].size()-1,res=level[idx].size();
	while(l<=r){
		int mid=l+r>>1;
		if(a[level[idx][mid]].second<a[x].second){
			res=mid;
			r=mid-1;
		}else l=mid+1;
	}
	return res;
}
int findR(int idx,int x){
	int l=0,r=level[idx].size()-1,res=-1;
	while(l<=r){
		int mid=l+r>>1;
		if(a[level[idx][mid]].first<a[x].first){
			res=mid;
			l=mid+1;
		}else r=mid-1;
	} 
	return res;
}
signed main(){
	read(n),read(m);
	for(int i=1;i<=n;i++)
		read(a[i].first),read(a[i].second);
	sort(a+1,a+n+1);
	for(int i=1,p;i<=n;i++){
		if(len==0||f[len]<a[i].second){
			f[++len]=a[i].second;
			level[len].push_back(i);
			continue;
		}
		p=lower_bound(f+1,f+len+1,a[i].second)-f;
		f[p]=a[i].second,level[p].push_back(i);
	}
	memset(g,0x3f,sizeof(g));
	for(int x:level[1])g[x]=1ll*a[x].first*a[x].second;
	for(int idx=2,rt,l,r,R;idx<=len;idx++){
		rt=0,R=level[idx-1].size()-1,l=r=-1;
		for(int x:level[idx]){
			while(l<R&&a[level[idx-1][l+1]].second>a[x].second)l++;
			while(r<R&&a[level[idx-1][r+1]].first<a[x].first)r++;
			change(rt,0,R,l+1,r,x);
		}
		dfs(idx-1,rt,0,R);
	}
	ans=8e18;
	for(int x:level[len])
		tomin(ans,g[x]+1ll*(m-a[x].first)*(m-a[x].second));
	write(ans);	
}
```

---

## 作者：Hilaria (赞：0)

### [P5244 Mowing Mischief P](https://www.luogu.com.cn/problem/P5244)

- 题意：

  给定一个 $T\times T$ 的矩阵，左下角的格点为 $(0,0)$，右上角为 $(T,T)$，因此，正方形包含 $(T+1)^2$ 个格点（具有整数坐标的点）。

  现在 Ella 和 Bella 从左下角同时出发走到右上角（速度相同），同时每人都握住非常锋利且非常有弹性的线的一端。任何被这根电线扫过的区域的草都会被切断。

  Ella 和 Bella 可能采取不同的路径，但她们只会向上或者向右移动，从一个格点移动到另一个格点。

  现在给定 $N$ 个格点，你可以选择选择其中一个子集 $S$，$S$ 集合中的点 Ella 和 Bella 都需要经过。

  Ella 和 Bella 将会切割面积尽可能大的草，请帮助Bessie确定集合 $S$ 使得在 $S$ 集合**尽可能大**的情况下被切割的草的**面积**最小。

  $1\leq N \leq 2\times 10^5,1\leq T\leq 10^6$

- 思路：

  我们首先手玩一下这个扫过的区域到底是什么，然后就会发现，这个其实就是两条路径框起来的矩阵的面积和。

  然后我们随便钦定一个点集 $S$，观察在钦定下，怎么走框出的面积和最大，然后手玩一下就可以发现，最大的路径就是尽量往右走，到钦定的点是再往上是最优的，且此时的答案就是：以钦定的点为矩阵的左下和右上角的矩阵面积和（为了方便，建议把 $(T,T)$ 加入钦定点的点集）。

  给个丑图（黑点为钦定点集，红矩阵为最大答案）：

  ![](https://cdn.luogu.com.cn/upload/image_hosting/368rx6c4.png)

  然后注意到题目要求 $S$ 最大的情况下，所以我们首先需要做一个 $\operatorname{LIS}$，然后就可以按层 DP，假设第 $p$ 个点的最长上升子序列为 $g_p$，最小矩阵和的答案为 $f_p$，那么我们可以写出 DP 式子：

  $f_p = min_{g_v + 1 = g_p\  |\ x_v<x_p,y_v<y_p} f_v + (x_p-x_v)\times(y_p-y_v)$

  这样我们就得到了卑微的 $O(n^2)$ 暴力。

  然后我们考虑去优化这个东西，首先将式子拆掉，变成（为方便阐述，下文的 $v$ 都为符合 $p$ 转移条件的点，我们用 $v-p$ 表示）：

  $f_p = min_{v-p} f_v + x_py_p-x_py_v-x_vy_p+x_vy_v$

  然后我们第一眼考虑斜优嘛，然后就发现好像不太对劲啊，这个 $x_vy_p,x_py_v$ 搞在一起不能进行斜优。

  那么只好去看看有没有单调性什么的了。

  首先有一个比较好找的，就是对于每一层的点按 $x$ 排序，他的 $y$ 一定是单调递减的。

  然后我们考虑对于当前转移的点 $p$，在上一层有两个**合法**的决策点 $j,k\ |\ j<k$，我们假定 $j$ 是 $p$ 的最优决策点，那么有：

  $f_j + x_py_p-x_py_j-x_jy_p+x_jy_j<f_k + x_py_p-x_py_k-x_ky_p+x_ky_k$

  简化一下：

  $x_p(y_k - y_j) + (x_k - x_j)y_p<(f_k+x_ky_k)-(f_j+x_jy_j)$

  那么我们可以发现，当 $p$ 变大后，$x_p$ 变大，$y_p$ 变小，而又因为 $y_k-y_j<0,x_k-x_j>0$，所以左边那坨只会变得更小，右边不变，那么在 $p$ 变大后，$j$ 一定仍比 $k$ 优，所以这是具有决策单调性的。

  但是，注意到这个决策单调性是有一个条件的，就是需要在 $j,k$ 是 $p$ 的合法转移点的情况下，如果直接全局做决策单调性是可能转移到不合法区间的，所以是不能直接做的。

  但是由于每层的 $x,y$ 都是有单调性的，所以对于每个点，他在上一层的合法转移点一定是一个区间的，这个可以写个二分或者双指针解决。

  注意到我们的决策单调性是在转移点合法时生效的，所以我们换一下考虑，对于一段点，如果我们知道它们都可以转移到哪些点，那么这是可以进行决策单调性的。

  那么我们可以线段树分治，将每个点的合法转移区间弄到线段树上，在那些区间上打上 tag，表示这一段区间可以转移到 $tag$ 去，然后就在线段树上搞决策单调性即可。

  时间复杂度为 $O(n\log^2 n)$，可以这么理解：每个点最多被拆到 $\log n$ 个区间上（指线段树的段），然后对于每个区间，他最多被算到 $\log n$ 次（分治是 $\log n$ 层的，每层一次），然后一共 $n$ 个点，就是 $O(n\log^2 n)$。

---

## 作者：SalN (赞：0)

P5244

提前加入 $(0,0),(T,T)$，首先因为只能向右/上走且钦定了速度相同，设拿到的点序列是 $p_0,\dots,p_{len}$，割掉的草的面积一定是 $p_{i},p_{i+1}$ 组成的矩形面积和 $\sum_{i=0}^{len-1}(X[p_{i+1}]-X[p_i])\times (Y[p_{i+1}]-Y[p_i])$，显然这样子最大。首先要最大化 $|p|$，设这个类似 LIS 的东西的长度为 $g$，按照 $g$  的值分层，只有上一层能往下一层转移，可以保证满足这个约束，同时因为同层之间一定互不转移，按照 $x\uparrow$ 去看一定有 $y\downarrow$ 这个条件。

现在考虑相邻层的转移 $A\to B$，怎么从一层的 $A=\{(x,y,f)\}$ 更新 $B=\{(x,y,f)\}$ 中 $B$ 的 $f$，这里 $f$ 是到某个点的最小切割面积。转移方程是 $f_B=\min_{x_A\leq x_B,y_A\leq y_B}\{f_A+(x_B-x_A)\times(y_B-y_A)\}$，上文提到 按照 $x\uparrow$ 去看一定有 $y\downarrow$ 这个条件，这种感觉多半跟决策单调性挂钩，这个直接函数意义上不太好分析，我们回归最原始的定义，考虑什么时候对于转移到 $(X,Y)$ 来说 $(x_1,y_1)$ 比 $(x_2,y_2)$ 优秀，不难写出以下柿子 >w<

$$f_{x_1,y_1}+(X-x_1)\times(Y-y_1)<f_{x_2,y_2}+(X-x_2)\times (Y-y_2)$$

$$(f_{x_1,y_1}+x_1y_1)-(f_{x_2,y_2}+x_2y_2)<X(y_1-y_2)+Y(x_1-x_2)$$

注意到这个柿子左边是定值，$y_1-y_2/x_1-x_2$ 一正一负，$X/Y$ 变化是反的，确实有决策单调性，但是是反的？？？

我们 reverse 一下 $A$ 然后变成带着只能在某个区间里面转移的决策单调性，注意到我们要的是单点对单点的 $\min$，我们容易考虑分块，考虑一个 $B_i$ 可以从 $A[l,\dots,r]$ 转移过来，这个可以二分求出，那对 $(l,r)$ 做嘛，对于非整块暴力，对于整块按顺序打上标记，再在每一块上面做一次普通的决策单调性，然后把贡献放到点里面。分块还是太暴力了，注意到很容易类似的放到线段树上面，那么考虑类似的做法上线段树即可，复杂度 $O(n\log^2n)$，因为一个询问分成 $\log$ 段，每一段都做 $\log$ 次 。          

```cpp
#include<bits/stdc++.h>
#define int long long
#define up(i,l,r) for(int i=l; i<=r; ++i)
#define dn(i,r,l) for(int i=r; i>=l; --i)
#define ls(p) (p<<1)
#define rs(p) (p<<1|1)
#define pb push_back

using namespace std;

const int N=200005, M=1000005;

int n, T, bit[M], len, L, R;
struct node {
	int x, y, f=1e13;
	bool operator<(const node &rhs) const { return x<rhs.x; }
} arr[N], A[N], B[N];
vector<node> p[N];
vector<int> tr[N<<2], ran;

void add(int x,int v) {
	for( ; x<=T; x+=x&-x) bit[x]=max(bit[x],v);
}

int ask(int x) {
	int ret=0;
	for( ; x; x-=x&-x) ret=max(ret,bit[x]);
	return ret;
}

void build(int p=1,int s=1,int e=L) {
	tr[p].clear();
	if(s==e) return;
	int mid=(s+e)>>1;
	build(ls(p),s,mid), build(rs(p),mid+1,e); 
}

void modify(int l,int r,int v,int p=1,int s=1,int e=L) {
	if(l<=s&&e<=r) {
		tr[p].pb(v);
		return;
	}
	int mid=(s+e)>>1;
	if(l<=mid) modify(l,r,v,ls(p),s,mid);
	if(r>mid) modify(l,r,v,rs(p),mid+1,e);
}

void solve(int l,int r,int s,int e) {
	if(l>r||s>e) return;
	int Mid=(s+e)>>1, mid=ran[Mid], val=1e13, pos=0;
	up(i,l,r) {
		int ret=A[i].f+(B[mid].x-A[i].x)*(B[mid].y-A[i].y);
		if(ret<val) val=ret, pos=i;
	}
	B[mid].f=min(B[mid].f,val);
	solve(l,pos,s,Mid-1), solve(pos,r,Mid+1,e);
}

void dfs(int p=1,int s=1,int e=L) {
	ran=tr[p], solve(s,e,0,(int)ran.size()-1);
	if(s==e) return;
	int mid=(s+e)>>1;
	dfs(ls(p),s,mid), dfs(rs(p),mid+1,e);
}

void solve() {
	build();
	up(i,1,R) {
		int l=1, r=L, p=0, q=0;
		while(l<=r) {
			int mid=(l+r)>>1;
			if(A[mid].y<=B[i].y) p=mid, r=mid-1;
			else l=mid+1;
		}
		l=1, r=L;
		while(l<=r) {
			int mid=(l+r)>>1;
			if(A[mid].x<=B[i].x) q=mid, l=mid+1;
			else r=mid-1; 
		}
		if(p&&q&&p<=q) modify(L-q+1,L-p+1,i);
	}
	up(i,1,L/2) swap(A[i],A[L-i+1]);
	dfs();
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> T;
	up(i,1,n) cin >> arr[i].x >> arr[i].y;
	arr[++n]=(node){T,T};
	sort(arr+1,arr+n);
	up(i,1,n) {
		int f=ask(arr[i].y)+1;
		p[f].pb(arr[i]), add(arr[i].y,f);
	}
	len=ask(T);
	for(node &o:p[1]) o.f=o.x*o.y;
	up(i,2,len) {
		L=R=0;
		for(node o:p[i-1]) A[++L]=o;
		for(node o:p[i]) B[++R]=o;
		solve();
		p[i].clear();
		up(j,1,R) p[i].pb(B[j]);
	}
	cout << B[1].f << '\n';
	return 0;
}
```

---

## 作者：xzzduang (赞：0)

[传送门](https://loj.ac/p/3767)

### 题意

给定平面上的一些点，你需要选取一些点使得横坐标纵坐标都递增，且选取的点尽量多。在点数尽量多的前提下，使相邻点的 $\Delta x\cdot \Delta y$ 之和最小。

所有点的横纵坐标都不相同 。

### 题解

第一个问题就是 LIS，我们先求出 $f_i$ 表示做到前 $i$ 个点的且第 $i$ 个点必选的最多选取的点数。

然后处理第二问，先按照 $f$ 进行分层。对于一个点 $i$，能转移到它的点需要满足是上一层的，而且横纵坐标都比 $i$ 的小。

发现一个性质：在同一层中，按照横坐标从小到大排序，则纵坐标也会递减。这是因为层内的点都是不能出现 $x_1<x_2$ 且 $y_1<y_2$ 的情况的，所以显然能转移到 $i$ 的点在上一层中形成了一个区间，这个区间可以二分找到。

假设没有横纵坐标都比 $i$ 小的限制，如何快速地转移，考虑决策单调性。设上一层的两个决策点 $j<k$。如果 $k$ 比 $j$ 更优：
$$
\begin{aligned}
dp_k+(x_i-x_k)(y_i-y_k)&\le dp_j+(x_i-x_j)(y_i-y_j)\\
x_i(y_j-y_k)+y_i(x_j-x_k)&\le (dp_j+x_jy_j)-(dp_k+x_ky_k)
\end{aligned}
$$
所以 $i$ 越大，上面的不等式越不容易满足，所以决策点是随着 $i$ 的变大而变小的。

考虑区间的限制，可以使用线段树分治，把询问点按照可行的决策点区间放入 log 个线段树节点，然后再在每个线段树的节点内跑决策单调性。

时间 $\mathcal{O}(n\log^2 n)$。

```cpp
#include<iostream>
#include<stdio.h>
#include<ctype.h>
#include<algorithm>
#include<vector>
#include<string.h>
#define N 200005
#define ls k<<1
#define rs k<<1|1
#define int long long
using namespace std;
inline int read(){
	int x=0,f=0; char ch=getchar();
	while(!isdigit(ch)) f|=(ch==45),ch=getchar();
	while(isdigit(ch)) x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	return f?-x:x;
}
struct node{
	int x,y,f;
}a[N];
int n,t,st[N],top,rev[N],dp[N],cnt,q[N],fick[N];
inline bool cmp1(node x,node y){
	return x.x<y.x;
}
inline bool cmp2(node x,node y){
	if(x.f==y.f) return x.x<y.x;
	return x.f<y.f;
}
vector<int> mp[4*N];
void insert(int k,int l,int r,int x,int y,int i){
	if(x<=l && r<=y) return (void)(mp[k].push_back(i));
	int mid=l+r>>1;
	if(x<=mid) insert(ls,l,mid,x,y,i);
	if(mid+1<=y) insert(rs,mid+1,r,x,y,i);
}
void solve(int l,int r,int x,int y){
	int mid=x+y>>1,id=0;
	fick[q[mid]]=1e18;
	for(int i=l;i<=r;++i){
		int tmp=dp[rev[i]]+(a[q[mid]].x-a[rev[i]].x)*(a[q[mid]].y-a[rev[i]].y);
		if(tmp<fick[q[mid]]) fick[q[mid]]=tmp,id=i;
	}
	if(x<mid) solve(id,r,x,mid-1);
	if(mid<y) solve(l,id,mid+1,y);
}
void work(int k,int l,int r){
	if(!mp[k].empty()){
		for(int i=0;i<mp[k].size();++i) q[i+1]=mp[k][i];
		solve(l,r,1,mp[k].size());
		for(int i=1;i<=mp[k].size();++i) dp[q[i]]=min(dp[q[i]],fick[q[i]]);
		mp[k].clear();
	}
	if(l==r) return;
	int mid=l+r>>1;
	work(ls,l,mid),work(rs,mid+1,r);
}
signed main(){
	n=read(),t=read();
	for(int i=1;i<=n;++i){
		a[i].x=read(),a[i].y=read();
	}
	a[++n]={0,0,0},a[++n]={t,t,0};
	sort(a+1,a+n+1,cmp1);
	for(int i=1;i<=n;++i){
		int l=1,r=top;
		while(l<=r){
			int mid=l+r>>1;
			if(a[i].y>st[mid]) l=mid+1;
			else r=mid-1;
		}
		if(r==top) top++;
		st[r+1]=a[i].y;
		a[i].f=r+1;
	}
	sort(a+1,a+n+1,cmp2);
	memset(dp,0x3f,sizeof(dp));
	rev[1]=cnt=1,dp[1]=0;
	for(int l=2,r=2;l<=n;l=++r){
		while(r+1<=n && a[r+1].f==a[l].f) r++;
		for(int i=l;i<=r;++i){
			int L=1,R=cnt;
			while(L<=R){
				int mid=L+R>>1;
				if(a[rev[mid]].x<a[i].x) L=mid+1;
				else R=mid-1;
			}
			int y=R;
			L=1,R=y;
			while(L<=R){
				int mid=L+R>>1;
				if(a[rev[mid]].y<a[i].y) R=mid-1;
				else L=mid+1;
			}
			int x=L;
			insert(1,1,cnt,x,y,i);
		}
		work(1,1,cnt);
		cnt=r-l+1;
		for(int i=l;i<=r;++i) rev[i-l+1]=i;
	}
	cout<<dp[n];
	return 0;
}

```



---

