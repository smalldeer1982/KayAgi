# ...好きです

## 题目描述

在いろは界，有个著名的故事：いろはちゃん在数直线上放置或移除大量硬币。

起初，数轴上没有任何硬币。いろはちゃん会进行 $Q$ 次操作。操作共有三种类型：

- **添加硬币**：在坐标 $x$ 处放置一个面值为 $v$ 的硬币。保证此时该位置没有其他硬币。
- **移除硬币**：将坐标 $x$ 处的硬币移除。保证此时该位置有硬币。
- **取硬币**：将ひらきち君放置在坐标 $x$，并让他取走一个硬币。ひらきち君会选择“效率”最高的硬币。“效率”定义为 $\frac{w}{|c-x|}$，其中 $w$ 是硬币的面值，$c$ 是硬币的坐标。

例如，若坐标 $2$ 有一个面值为 $3$ 的硬币，坐标 $5$ 有一个面值为 $8$ 的硬币，不同情况下“效率”最高值为：

- ひらきち君若在坐标 $0$，会取走坐标 $5$ 的硬币，“效率”是 $1.6$。
- 若在坐标 $1$，会取走坐标 $2$ 的硬币，“效率”是 $3.0$。
- 若在坐标 $7$，会取走坐标 $5$ 的硬币，“效率”是 $4.0$。

**注意，虽然ひらきち君取走硬币，但此硬币随后会被还原，故同一硬币可被多次取走。**

对于每次“取硬币”操作，请输出ひらきち君能获取的最高“效率”值。若此时数轴上没有硬币则输出 $0$。

## 说明/提示

- 所有输入均为整数
- $1 \leq Q \leq 3 \times 10^5$
- $0 \leq x \leq 10^9$
- $0 \leq v \leq 10^9$
- 每次“添加硬币”时，该位置无其他硬币
- 每次“移除硬币”时，该位置有硬币
- 每次“取硬币”时，该位置无硬币

### 部分得分

- 通过所有满足 $Q \leq 120000$ 的测试用例可得 $1100$ 分。
- 通过所有测试用例，还可额外得 $300$ 分。

### 参考
[题目解析](https://img.atcoder.jp/iroha2019-day4/editorial-L.pdf)

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
11
1 2 3
3 10
1 5 8
3 0
3 1
3 7
2 2
1 7 9
3 3
3 6
3 10```

### 输出

```
0.375000000000
1.600000000000
3.000000000000
4.000000000000
4.000000000000
9.000000000000
3.000000000000```

## 样例 #2

### 输入

```
10
1 0 10
3 1
3 2
3 3
3 4
3 5
3 6
3 7
3 8
3 9```

### 输出

```
10.000000000000
5.000000000000
3.333333333333
2.500000000000
2.000000000000
1.666666666667
1.428571428571
1.250000000000
1.111111111111```

# 题解

## 作者：_•́へ•́╬_ (赞：5)

## 思路

离线下来，按 $x$ 排序所有物品和查询，然后从左往右扫一遍，再从右往左扫一遍，进行贡献。这样我们处理的东西在下标上就有了单调性。

在时间轴上开线段树，每个节点上维护凸包。

插入物品时，在其存在时间区间对应的 $\log$ 个线段树节点上插入它。因为下标是单调的，所以凸包维护只需要在末尾弹一弹即可。

查询的话，在查询时间对应的 $\log$ 个线段树节点上查询。因为下标是单调的，所以单指针一下即可。

复杂度 $\mathcal O(n\log n)$。

## code

```cpp
#include<stdio.h>
#include<algorithm>
#include<vector>
#include<math.h>
#include<map>
#define N 524288
#define lc ((i)<<1|1)
#define rc ((i)+1<<1)
#define pr pair<int,int> 
using namespace std;
inline char nc()
{
	static char buf[99999],*l,*r;
	return l==r&&(r=(l=buf)+fread(buf,1,99999,stdin),l==r)?EOF:*l++;
}
inline void read(int&x)
{
	bool t=0;char c=nc();for(;c<'0'||'9'<c;t|=c=='-',c=nc());
	for(x=0;'0'<=c&&c<='9';x=(x<<3)+(x<<1)+(c^48),c=nc());if(t)x=-x;
}
int n,o[N],x[N],y[N],rgt[N],m,q,pos[N<<1];double ans[N];map<int,int>id;
struct qwq
{
	int l,r,x,y;
	inline bool operator<(const qwq&kkk)const{return x<kkk.x;}
}a[N];
vector<pr>mmp[N<<1];
inline double qry(vector<pr>&a,int&i,int x)
{
	if(a.empty())return 0;
	if(i>=a.size())i=a.size()-1;
	for(;i<a.size()-1&&a[i].second/(double)(x-a[i].first)
		<a[i+1].second/(double)(x-a[i+1].first);++i);
	for(;i&&a[i].second/(double)(x-a[i].first)
		<a[i-1].second/(double)(x-a[i-1].first);--i);
	return a[i].second/(double)(x-a[i].first);
}
inline double qry(int i,int l,int r,int p,int x)
{
	if(l==r)return qry(mmp[i],pos[i],x);
	int mid=l+r>>1;
	if(p<=mid)return max(qry(mmp[i],pos[i],x),qry(lc,l,mid,p,x));
	else return max(qry(mmp[i],pos[i],x),qry(rc,mid+1,r,p,x));
}
inline void add(vector<pr>&a,int x,int w)
{
	for(;a.size()&&a.back().second<=w;a.pop_back());
	if(a.size()&&a.back().first==x)return;
	for(;a.size()>1;a.pop_back())
	{
		int sz=a.size();
		if(atan2(a[sz-2].second-a[sz-1].second,a[sz-2].first-a[sz-1].first)
			>atan2(a[sz-1].second-w,a[sz-1].first-x))break;
	}
	a.emplace_back(x,w);
}
inline void add(int i,int l,int r,int ql,int qr,int x,int w)
{
	if(qr<l||r<ql)return;
	if(ql<=l&&r<=qr){add(mmp[i],x,w);return;}
	int mid=l+r>>1;
	add(lc,l,mid,ql,qr,x,w);add(rc,mid+1,r,ql,qr,x,w);
}
main()
{
	read(n);
	for(int i=0;i<n;++i)
	{
		read(o[i]);
		if(o[i]==1)read(x[i]),read(y[i]),id[x[i]]=i;
		else if(o[i]==2)read(x[i]),rgt[id[x[i]]]=i;
		else read(x[i]);
	}
	for(int i=0;i<n;++i)
		if(o[i]==1)a[q++]=(qwq){i,rgt[i]?rgt[i]:n-1,x[i],y[i]};
		else if(o[i]==3)a[q++]=(qwq){i,i,x[i],~i};
	sort(a,a+q);
	for(int i=0;i<q;++i)if(a[i].y>>31)
		ans[~a[i].y]=max(ans[~a[i].y],qry(0,0,n-1,a[i].l,a[i].x));
	else add(0,0,n-1,a[i].l,a[i].r,a[i].x,a[i].y);
	for(int i=0;i<N<<1;mmp[i++].clear());
	for(int i=q-1;i>=0;--i)if(a[i].y>>31)
		ans[~a[i].y]=max(ans[~a[i].y],qry(0,0,n-1,a[i].l,-a[i].x));
	else add(0,0,n-1,a[i].l,a[i].r,-a[i].x,a[i].y);
	for(int i=0;i<n;++i)if(o[i]==3)printf("%.10lf\n",ans[i]);
}
```

---

## 作者：hgckythgcfhk (赞：1)

### 简化题意：

> 维护一个数轴，单点插入删除，带权，记一个点的坐标为 $a$，权为 $b$，每次询问给定一个 $c$ 求 $\dfrac{b}{|a-c|}$ 的最大值。

考虑只有一次询问且修改都在询问前怎么做，由于询问的坐标两边是本质相同的，所以先只看右边，考虑哪些点可能成为答案，为了方便直接把 $a$ 看成原点，这相当于是求一个平面直角坐标系上的若干个点到原点的连线的斜率的最大值，考虑到斜率优化等凸优化问题经常和斜率有关，所以这个东西看起来像是凸的，不妨往这个方向证明一下。

现在造横坐标递增的 $3$ 个点 $A(x_a,y_a),B(x_b,y_b),C(x_c,y_c)$，连接 $AC$，显然 $AC$ 的斜率为 $\dfrac{y_c-y_a}{x_c-x_a}$，把 $A$ 代入 $AC$ 的点斜式方程得 $y-y_a=\dfrac{y_c-y_a}{x_c-x_a}(x-x_a)$，整理一下 $\dfrac{y-y_a}{x-x_a}=\dfrac{y_c-y_a}{x_c-x_a}$ 这个式子的意义是在直线 $AC$ 上的直线的点在以 $A$ 为原点的坐标系上的斜率等于 $AC$ 的斜率，根据式子显然 $AC$ 下方的点在以 $A$ 为原点的坐标系上斜率小于 $AC$ 的斜率，上方的点反之，我们现在找到横坐标为 $x_b$ 的 $3$ 个点 $B_1,B_2,B_3$ 使得这 $3$ 个点分别在 $AC$ 下方，$AC$ 上，$AC$ 上方，连接 $A$ 和这 $3$ 个点，事实上斜率大小关系可以直接连这 $3$ 个点看出来，上面是形式化的证明，现在连接 $B_1,B_2,B_3$ 造出来一个三角形，然后把这个三角形的顶点平移到原点，显然，不管我怎么动这个顶点，在一个三角形内顶点到底边上任意两点的连线谁在上谁在下的相对关系是不变的，所以只有 $AC$ 上方的点 $B$ 是有用的，根据定义，这是一个上凸的凸包。

现在考虑先只修改，再做多次询问的情况，还是只看右边，把所有点无论是修改还是询问降序排序，这相当于前缀插入，由于是凸的，所以具有决策单调性，也就是说在查询点不断左移的过程中一个决策点一旦没用就永远没用了。

于是问题可以转化成每个点有一段存在的时间区间，然后我们要做一个会做先修改再查询的问题，由于是求 $\max$，可以拆贡献，可以线段树分治。

如果先把所有点排好序这样我们处理一个线段树节点的时候可以直接跳指针且不用重新排序，所以时间复杂度 $O(n\log n)$。

注：程序中部分参考了题解。

为防止火车头导致无法过审，删除了缺省源，只放核心程序，不影响阅读。
```cpp
#define ls o<<1
#define rs ls|1
struct A{unsigned l,r;signed x,y;il bool operator<(const A a)const{return x<a.x;}}a[N];
struct B{signed x,y;il db val(const rg signed pos){return (1.0*y)/(pos-x);}};
unsigned q,n,st[N],ed[N];vector<B>b[N<<2];ump<unsigned,unsigned>id;
unsigned op[N],x[N],y[N],pos[N<<2];db ans[N];A I;B Q;
il db qry(vector<B>&a,int&i,const rg signed x){if(!a.SZ)return 0;if(i>a.SZ)i=a.SZ-1;
	for(;i<a.SZ-1&&a[i].val(x)<a[i+1].val(x);++i);
	for(;i       &&a[i].val(x)<a[i-1].val(x);--i);
	return a[i].val(x);}
il db qry(cit o,cit l,cit r){const rg db t=qry(b[o],pos[o],Q.y);if(l==r)return t;
	cit m=l+r>>1;return Q.x<=m?max(qry(ls,l,m),t):max(qry(rs,m+1,r),t);}
void ins(vector<B>&a,B b){while(a.SZ&&a.BK.y<=b.y)a.PP;
	if(a.SZ&&a.BK.x==b.x)return;for(;a.SZ>1;a.PP){B x=a.BK,y=a[a.SZ-2];
		if(atan2(y.y-x.y,y.x-x.x)>atan2(x.y-b.y,x.x-b.x))break;}a+=b;}
void ins(cit o,cit l,cit r){if(I.r<l||I.l>r)return;
	if(I.l<=l&&I.r>=r)return ins(b[o],B{I.x,I.y});
	cit m=l+r>>1;ins(ls,l,m),ins(rs,m+1,r);}
void init(){cin>>q;
	for(int i=1;i<=q;++i){cin>>op[i];
		if(op[i]==1)cin>>x[i]>>y[i],id[x[i]]=i,ed[i]=q,st[i]=i;
		if(op[i]==2)cin>>x[i],ed[id[x[i]]]=i;
		if(op[i]==3)cin>>x[i];}for(int i=1;i<=q;++i)
		if(op[i]==1)a[++n]=A{st[i],ed[i],x[i],y[i]};
else	if(op[i]==3)a[++n]=A{	i ,   i ,x[i],~ i };
	sort(a+1,a+n+1);
}void solve(){init();
	for(int i=1;i<=n;++i)if(a[i].y>>31)Q={a[i].l,a[i].x},
		ans[~a[i].y]=max(ans[~a[i].y],qry(1,1,q));
	else I=a[i],ins(1,1,q);
	for(int i=1;i<(N<<2);++i)b[i].resize(0);
	for(int i=1;i<=n;++i)a[i].x=-a[i].x;
	for(int i=n;  i;--i)if(a[i].y>>31)Q={a[i].l,a[i].x},
		ans[~a[i].y]=max(ans[~a[i].y],qry(1,1,q));
	else I=a[i],ins(1,1,q);
	for(int i=1;i<=q;++i)if(op[i]==3)cout<<fixed<<setprecision(6)<<ans[i]<<'\n';
}signed main(){open;int t=1;//cin>>t;
	while(t--)solve();
}

```
这种线段树分治的题，一定要注意线段树维护的序列的大小是 $q$ 而不一定是 $n$，因为是在时间轴上建线段树。

---

## 作者：DengStar (赞：0)

[在我的博客中查看](https://www.cnblogs.com/dengstar/p/18868959)

先考虑静态问题。先把绝对值拆开，只考虑询问左边的点，反过来的情况类似。容易想到在平面直角坐标系上考虑。考虑每个点对答案的贡献。对于点 $(x, y)$ 和询问 $x_{0} > x$，这个点对答案的贡献相当于使答案对 $\dfrac{y}{x_{0} - x}$ 取 $\max$。把一个点的贡献看作关于 $x_{0}$ 的函数，则相当于平面有若干个函数图象，每个点 $(x_{0}, 0)$ 的答案就是它正上方的点中纵坐标最大的。$x_{0}$ 在分母不好做，所以取个倒数变成 $\dfrac{x_{0} - x}{y}$，这是关于 $x_{0}$ 的一次函数 
$$
\dfrac{1}{y} x_{0} - \dfrac{x}{y}
$$
于是问题就变成了：

> 平面上有若干条直线，多次给定 $x_{0}$，求出直线上的点中，横坐标为 $x_{0}$ 的点中纵坐标为正数且最小的。

把操作和询问的 $x$ 坐标一起从小到大排序（操作的 $x$ 相当于对应直线的零点），逐个处理。维护加入直线的最小值构成的函数。这么做保证了考虑到的直线在 $x = x_0$ 处一定为正。由于一次函数是上凸的，根据经典结论，一堆一次函数的 $\min$ 仍然上凸，所以直线的最小值构成一个上凸包：

![](https://cdn.luogu.com.cn/upload/image_hosting/97xfjhsx.png)

注意到上凸包有以下性质：

- 随着 $x$ 坐标的增大，使得 $y$ 最小的直线**斜率单调递减**。

所以我们考虑维护一个**单调栈**，从栈底到栈顶从小到大存放直线的斜率，并且保证栈中每一条直线都存在某个位置，使得这堆直线中的最小值在此直线取到（也就是说保证每条直线都是凸包的一部分）。

加入一条新直线 $l$ 时，讨论它与栈顶直线的关系。有两种情况：

1. $l$ 的斜率小于等于栈顶直线的斜率。由于已经把直线的零点和询问的 $x$ 坐标从小到大排序，所以对于 $x$ 坐标更大的询问，$l$ 的纵坐标都一定小于斜率更大直线的纵坐标。此时连续弹栈，直到栈顶直线斜率小于 $l$ 的斜率。

  ![](https://cdn.luogu.com.cn/upload/image_hosting/uqv3ylbs.png)

   如图，$l$ 是新加入的直线。由于 $l$ 的斜率小于 $l'$ 的斜率，所以对于 $P$ 点右侧的询问，$l$ 的纵坐标一定小于 $l'$ 的纵坐标，因此 $l'$ 被弹出。但直线 $m$ 被保留了。

2. $l$ 的斜率大于栈顶直线的斜率，但是 **$l$ 与栈顶的交点在栈顶与次栈顶的交点右侧**。

   ![](https://cdn.luogu.com.cn/upload/image_hosting/hri1zeqg.png)

   如图，虽然 $l$ 的斜率大于栈顶 $l'$ 的斜率，但是由于 $l$ 和 $l'$ 的交点 $Q$ 在 $l'$ 与 $m$ 的交点 $S$ 左侧，所以对于 $P$ 右侧的询问，纵坐标最小值不可能在 $l'$ 取到，这种情况我们也需要弹栈。

以上就讨论完了加入直线的情况。下面考虑如何处理询问。根据凸包的性质，随着 $x$ 坐标的增大，使得 $y$ 最小的直线斜率单调递减。而栈中的直线斜率已经有序，且询问的 $x_0$ 也有序，所以只要比较栈顶和次栈顶在 $x_0$ 处的纵坐标哪个小，如果次栈顶更小，就弹栈。重复这个过程知道栈顶在 $x_0$ 处纵坐标最小，此时栈顶的纵坐标就是答案。

现在静态问题就解决了，时间复杂度为 $O(n \log n)$，瓶颈在排序，计算答案的过程是线性的。下面考虑动态问题。

**对时间轴建立线段树**。还是把操作和询问按 $x$ 坐标排序，然后预处理出每条直线出现的时间区间 $[l, r]$，对于 $[l, r]$ 在线段树上拆分出的 $O(\log n)$ 个区间，把直线加入到这个区间内，按静态问题的方法维护每个区间的凸包。查询 $x_{0}$ 时，对于线段树上包含 $x_{0}$ 的 $O(\log n)$ 个区间，分别计算答案然后取 $\min$。由于 $x$ 坐标有序，所以正确性可以保证。至于时间复杂度，每条直线在 $O(\log n)$ 个线段树上的区间出现，所以所有区间直线的总数为 $O(\log n)$。用单调栈计算答案的过程是线性的，所以总时间复杂度还是 $O(n \log n)$。

代码实现非常清晰：[Code](https://atcoder.jp/contests/iroha2019-day4/submissions/65557541)

下面附上我写的 generator 供大家调试，可以自行修改数据范围。为了方便，使用了 `vector.erase()` 用来完成从 `set` 中随机选取元素的过程，时间复杂度比较劣，但实测生成大数据也很快。（实际上更好的做法是把删除的元素和 `vector.back()` 交换，然后 `pop_back()`。）

（在文首链接查看）

---

## 作者：Linge_Zzzz (赞：0)

# Sol

考虑一下所有查询在所有修改后面咋做。先把所有点 $(x,w_x)$ 拍到平面直角坐标系上。查询 $x$ 时，分讨把绝对值去掉，只看右边，发现这个式子的含义是最大化一个点连到 $(x,0)$ 的斜率，不难发现答案一定在上凸壳上。所以我们把所有点和所有询问按 $x$ 排序，单调栈维护凸壳即可 $O(q)$ 做掉。注意因为凸壳的决策单调性，查询的时候可以直接弹而不用二分。

现在考虑查询和修改混在一块。我们发现有两个处理问题的维度，一个是按时间顺序每个询问直接做，但是很容易发现其不可做，所以我们按 $x$ 的顺序，在时间轴上开线段树，每个节点维护一个凸壳。遇到一个插入就在线段树上的对应区间分别插入这个点，遇到一个查询就在经过的路径上全查一遍顺便把不是最优的弹了。

复杂度分析，一个点最多被插入 $O(\log n)$ 次，弹出的点不会被再次插入，所以是 $O(n\log n)$ 的。

# Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
typedef pair<int,int> pii;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
const int N=3e5+10,INF=0x3f3f3f3f3f3f3f3f,mod=1e9+7;
int q,type;
bool isq[N];
double ans[N];
struct Q{
	int op,x,y,l,r;
}qr[N];
map<int,int> lst,lstv;
int tot;
struct Vec{
	int x,y;
	Vec(int x=0,int y=0):x(x),y(y){}
};
vector<Vec> t[N*4];
void build(int p,int l,int r){
	t[p].clear();
	if(l==r)return;
	int m=(l+r)>>1;
	build(p*2,l,m);
	build(p*2+1,m+1,r);
}
double k(Vec p,Vec q){
	return 1.0*(p.y-q.y)/(p.x-q.x);
}
void ins(vector<Vec> &v,Vec p){
	if(type==0)while(v.size()>1&&k(p,v[v.size()-1])<=k(v[v.size()-1],v[v.size()-2]))v.pop_back();
	else while(v.size()>1&&k(p,v[v.size()-1])>=k(v[v.size()-1],v[v.size()-2]))v.pop_back();
	v.push_back(p);
}
void update(int p,int l,int r,int L,int R,Vec v){
	if(L<=l&&r<=R){
		ins(t[p],v);
		return;
	}
	int m=(l+r)>>1;
	if(L<=m)update(p*2,l,m,L,R,v);
	if(R>m)update(p*2+1,m+1,r,L,R,v);
}
double ask(vector<Vec> &v,Vec p){
	if(v.size()==0)return 0;
	if(type==0)while(v.size()>1&&k(p,v[v.size()-1])<=k(v[v.size()-1],v[v.size()-2]))v.pop_back();
	else while(v.size()>1&&k(p,v[v.size()-1])>=k(v[v.size()-1],v[v.size()-2]))v.pop_back();
	return abs(k(p,v[v.size()-1]));
}
double query(int p,int l,int r,int pos,Vec v){
	double ans=ask(t[p],v);
	if(l==r)return ans;
	int m=(l+r)>>1;
	if(pos<=m)return max(ans,query(p*2,l,m,pos,v));
	else return max(ans,query(p*2+1,m+1,r,pos,v));
}
void work(){
	build(1,1,q);
	for(int i=1;i<=tot;i++){
		if(qr[i].op)update(1,1,q,qr[i].l,qr[i].r,Vec(qr[i].x,qr[i].y));
		else ans[qr[i].l]=max(ans[qr[i].l],query(1,1,q,qr[i].l,Vec(qr[i].x,0)));
	}
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>q;
	for(int i=1;i<=q;i++){
		int op;cin>>op;
		if(op==1){
			int x,v;cin>>x>>v;
			lst[x]=i,lstv[x]=v;
		}
		if(op==2){
			int x;cin>>x;
			qr[++tot]={1,x,lstv[x],lst[x],i};
			lst[x]=0;
		}
		if(op==3){
			int x;cin>>x;
			qr[++tot]={0,x,0,i,0};
			isq[i]=1;
		}
	}
	for(pii p:lst){
		if(p.se){
			int x=p.fi;
			qr[++tot]={1,x,lstv[x],lst[x],q};
		}
	}
	sort(qr+1,qr+1+tot,[](Q x,Q y){return x.x>y.x;});
	type=0;
	work();
	sort(qr+1,qr+1+tot,[](Q x,Q y){return x.x<y.x;});
	type=1;
	work();
	for(int i=1;i<=q;i++)
		if(isq[i])
			cout<<fixed<<setprecision(10)<<ans[i]<<'\n';
	return 0;
}
```

---

