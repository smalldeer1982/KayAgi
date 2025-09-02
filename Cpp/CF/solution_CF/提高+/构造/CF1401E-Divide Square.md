# Divide Square

## 题目描述

There is a square of size $ 10^6 \times 10^6 $ on the coordinate plane with four points $ (0, 0) $ , $ (0, 10^6) $ , $ (10^6, 0) $ , and $ (10^6, 10^6) $ as its vertices.

You are going to draw segments on the plane. All segments are either horizontal or vertical and intersect with at least one side of the square.

Now you are wondering how many pieces this square divides into after drawing all segments. Write a program calculating the number of pieces of the square.

## 说明/提示

The sample is like this:

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1401E/17be53a5afe098ed0413461c4a2e30e4f2b8aabc.png)

## 样例 #1

### 输入

```
3 3
2 3 1000000
4 0 4
3 0 1000000
4 0 1
2 0 5
3 1 1000000```

### 输出

```
7```

# 题解

## 作者：syksykCCC (赞：18)

只有两种情况，会产生一个新的块：

1. square 的**对边**被一条 segment 连接，如图：
  
   ![image.png](https://i.loli.net/2020/08/23/9hoOlIuLHM2Bqzg.png)

2. 两条 segment **相交**，如图：

   ![image.png](https://i.loli.net/2020/08/23/mqGVZQ3cO1up7Kn.png)
   
   注意，因为每条 segment 必然有一段与 square 的一边相连，则两条相交必会产生一个新的块。

所以，我们可以分这两种情况来计算所有的块。

首先，$ans \gets 1$（没有 segment 也有初始的一个块）。

第一种情况是很好处理的，对于读入的某条横边或者竖边，如果它的两个端点分别为 $0$ 和 $10^6$，则 $ans \gets ans + 1$。

对于第二种情况，我们可以抽象为一个**单点修改，区间查询**的问题。

比如，我们把**横边**看作「修改」，**竖边**看作「查询」。

下面，我们依次处理横坐标位于 $1, 2, \cdots 10^6-1$ 的交点（也就是从左往右扫描），可以抽象为 $1-$时刻，$2-$时刻……，在每一个时刻，**先处理查询操作，再处理修改操作**。

尝试动态维护一个数组 $\text{cover}$，$\text{cover}_i = 0/1$ 表示在当前时刻下，纵坐标 $i$ 上面是否被线段覆盖。

* 定义操作 $\operatorname{\large{M}\small{ODIFY}}\normalsize{(t, p, v)}$ 表示在 $t$ 时刻，将 $\text{cover}_p$ 增加 $v$；
* 定义操作 $\operatorname{\large{Q}\small{UERY}}\normalsize{(t, l, r)}$ 表示询问在 $t$ 时刻，查询 $\sum\limits_{i=l}^{r}\text{cover}_i$。

描述一下一条横边 $(y, lx, rx)$，它表示，在时刻 $[lx, rx]$ 中，把 $\text{cover}_y$ 赋值为 $1$。那么，通过差分的方法，我们可以把每一条横边抽象为两个修改操作：$\operatorname{\large{M}\small{ODIFY}}\normalsize{(lx-1, y, 1)}$ 和 $\operatorname{\large{M}\small{ODIFY}}\normalsize{(rx, y, -1)}$。因为是先查询后修改，所以，$lx$ 时刻就应该被计入的贡献应该在 $lx-1$ 时刻修改，同理，$rx$ 时刻以后就要被撤销的影响应该在 $rx$ 时刻修改。

描述一下一条竖边 $(x, ly, ry)$，它会与**在 $x$ 时刻，$\text{cover}_i = 1(ly \le i \le ry)$** 的那些纵坐标上的线段相交。那么，总量就是一个查询操作，即 $\operatorname{\large{Q}\small{UERY}}\normalsize{(x, ly, ry)}$，将其累加到 $ans$ 中。

那么，将所有操作按照 **「时间不同时，按照时间升序；时间相同时，先修改后查询」** 的方式排序，这就成为了一个标准的单点修改，区间查询的问题，可以用树状数组/线段树解决。

时间复杂度 $\mathcal O(n \log n)$，代码中用的是树状数组，将坐标范围平移到了 $[1, 10^6 + 1]$ 防止越界，并且将修改和查询分开了，当然也可以存在一起排序。

```cpp
#include <bits/stdc++.h>
#define int long long
#define AddModification(t, p, v) mdfy[++m0] = (modification){t, p, v};
#define AddQuery(t, l, r) qry[++q0] = (query){t, l, r};
using namespace std;
const int N = 1e5 + 5, S = 1e6 + 5;
int y[N], lx[N], rx[N], x[N], ly[N], ry[N];
int ans = 1, n, m, o[S], m0, q0;
struct modification
{
	int t, p, v;
	bool operator < (const modification &oth) const { return t < oth.t; }
} mdfy[N << 1];
struct query
{
	int t, l, r;
	bool operator < (const query &oth) const { return t < oth.t; }
} qry[N << 1];
void Modify(modification &opt)
{
	for(int p = opt.p; p < S; p += p & -p)
		o[p] += opt.v;
}
int Query(query &opt)
{
	int res = 0;
	for(int p = opt.r; p; p -= p & -p)
		res += o[p];
	for(int p = opt.l - 1; p; p -= p & -p)
		res -= o[p];
	return res;
}
signed main()
{
	scanf("%lld %lld", &n, &m);
	for(int i = 1; i <= n; i++)
	{
		scanf("%lld %lld %lld", &y[i], &lx[i], &rx[i]);
		if(lx[i] == 0 && rx[i] == 1000000) ans++;
		y[i]++; lx[i]++; rx[i]++;
		AddModification(lx[i] - 1, y[i], 1);
		AddModification(rx[i], y[i], -1);
	}
	for(int i = 1; i <= m; i++)
	{
		scanf("%lld %lld %lld", &x[i], &ly[i], &ry[i]);
		if(ly[i] == 0 && ry[i] == 1000000) ans++;
		x[i]++; ly[i]++; ry[i]++;
		AddQuery(x[i], ly[i], ry[i]);
	}
	sort(mdfy + 1, mdfy + m0 + 1);
	sort(qry + 1, qry + q0 + 1);
	int nowm = 1, nowq = 1;
	for(; nowm <= m0 && mdfy[nowm].t == 0; nowm++) Modify(mdfy[nowm]);
	for(int t = 1; t < S; t++)
	{
		for(; nowq <= q0 && qry[nowq].t == t; nowq++) ans += Query(qry[nowq]);
		for(; nowm <= m0 && mdfy[nowm].t == t; nowm++) Modify(mdfy[nowm]);
	}
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：George1123 (赞：7)


来蒟蒻逊逊的博客园看看$\to$

[$\Huge\it\color{#aa4514}{George1123}$](https://www.cnblogs.com/George1123/p/13550010.html)

---

## 题面

> [CF1401E Divide Square](https://www.luogu.com.cn/problem/CF1401E) 

> 给一个正方形平面边长为 $10^6$，给 $n$ 条横线段和 $m$ 条竖线段，**每条线段都与正方形边缘相交**且**一条直线上不会有两条线段**，求被线段划分后有几个块。

> 数据范围：$0\le n,m\le 10^5$，$0<x,y<10^6$，$0\le (lx<rx),(ly<ry)\le 10^6$。

---

## 蒟蒻语

前天打小号 $30$ 分钟切了 $\tt ABCD$ 以为能 $\tt AK$，结果 $\tt E$ 少看了条件开始硬钢幸得爆零。

---

## 蒟蒻解

**结论：**$ans=($内部交点数 $p)+(10^6$ 长度线段数 $s)+1$。

这个结论应该比较好找，可以多画几个图找规律。

蒟蒻本来想了一个很炫酷的证明，但被证伪了，看个逊一点的吧……

**证明：**

对于 $s=0$ 的情况，所有线段都贴且仅贴一边又互相不重合，所以每多一个交点多一个块易证。

对于 $s>0$ 的情况，如果一条长度为 $10^6$ 的线段不穿过线段，那么固然把正方形分成两块多一块。否则从一条被穿过的线段把它拆成两条线段考虑，答案也会 $+1$。

综上，$ans=p+s+1$。

---
至于实现，可以用树状数组扫描线，代码中给出一种新奇的树状数组写法。

---
## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

//Start
typedef long long ll;
typedef double db;
#define mp(a,b) make_pair((a),(b))
#define x first
#define y second
#define be(a) (a).begin()
#define en(a) (a).end()
#define sz(a) int((a).size())
#define pb(a) push_back(a)
#define R(i,a,b) for(int i=(a),I=(b);i<I;i++)
#define L(i,a,b) for(int i=(a),I=(b);i>I;i--)
const int iinf=0x3f3f3f3f;
const ll linf=0x3f3f3f3f3f3f3f3f;

//Data
const int N=1e5,M=1e6;
int n,m; ll ans=1;
vector<int> d;
struct segment{
	int op,y,l,r;
	segment(){}
	segment(int _op,int _y,int _l,int _r){
		op=_op,y=_y,l=_l,r=_r;
	}
};
vector<segment> a;

//FenwickTree
vector<int> c;
void add(int i,int v){for(;i<sz(c);i|=i+1) c[i]+=v;}
int sum(int i){int v=0;for(;~i;(i&=i+1)--) v+=c[i];return v;}

//Main
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>m;
	R(i,0,n){
		int y,l,r; cin>>y>>l>>r;
		if(r-l==M) ++ans;
		d.pb(l),d.pb(r),a.pb(segment(0,y,l,r));
	}
	R(i,0,m){
		int x,l,r; cin>>x>>l>>r;
		if(r-l==M) ++ans;
		d.pb(x),a.pb(segment(1,l,x,1)),a.pb(segment(1,r,x,-1));
	}
	sort(be(a),en(a),[&](segment p,segment q){
		if(p.y!=q.y) return p.y<q.y;
		return p.op*p.r>q.op*q.r;
	});
	sort(be(d),en(d)),d.erase(unique(be(d),en(d)),en(d));
	c.assign(sz(d),0);
	// c.assign(M+1,0);
	for(auto u:a){
		if(u.op){
			int i=lower_bound(be(d),en(d),u.l)-be(d);
			add(i,u.r);
		} else {
			int l=lower_bound(be(d),en(d),u.l)-be(d);
			int r=lower_bound(be(d),en(d),u.r)-be(d);
			ans+=sum(r)-sum(l-1);
		}
	}
	cout<<ans<<'\n';
	return 0;
}
```
---
**祝大家学习愉快！**

---

## 作者：LTb_ (赞：5)

我们定义特殊线段为一个端点为  $0$，另一个端点为 $10^6$ 的线段。

然后瞎猜一个看上去十分不靠谱的结论：
$$
\text{ans}=\text{线段交点个数}+\text{特殊线段个数}+1
$$
然后你发现它过了（亲身经历

考虑两根线段，如果它们相交则必然产生**恰好** $1$ 个块。这很好理解，因为每根线段都有至少一个端点在边界上。

普通线段不会产生在此之外的贡献，而特殊线段们自己就可以产生 $1$ 的贡献。

交点个数则是一个经典树状数组问题：用值域为 $1\sim 10^6$ 的树状数组维护水平的线段。将垂直线段按横坐标从小到大排序，枚举竖直线段的同时维护水平线段。

```c++
// 2020.08.21
// by LTb
// #pragma GCC optimize(2)
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define debug cout<<"QwQ"<<endl;
inline int read(){
    int x=0,f=1;
    char ch;
    while(ch<'0'||ch>'9')  {if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return f*x;
}

const int MAXN=100005;
const int MAX=1e6;
int n,m;
int a[MAXN];
struct BIT{
	int tree[MAX+10];
	int Max_Value=n;

	inline int lowbit(int x){
	    return x&(-x);
	}

	inline void add(int x,int c){
		while (x<=Max_Value+1){
			tree[x]+=c;
			x+=lowbit(x);
		}
	}

	inline int query(int x){
		int ans=0;
		while (x>0){
			ans+=tree[x];
			x-=lowbit(x);
		}
		return ans;
	}

	inline int query2(int l,int r){
		return query(r)-query(l-1);
	}

	inline void add2(int l,int r,int c){
		add(l,c);
		add(r+1,-c);
	}
}t;

vector<pair<int,int> > v[MAX+10];
struct node{
	int x,l,r;
	bool operator<(node b){
		return x<b.x;
	}
}q[MAXN];

signed main()

{
	n=read();m=read();
	t.Max_Value=MAX+2;
	int ans=1;
	for (int i=1;i<=n;i++){
		int x=read(),l=read(),r=read();
		if (l==0 && r==MAX) ans++;
		v[l].push_back(make_pair(x,1));
		v[r+1].push_back(make_pair(x,-1));
	}

	for (int i=1;i<=m;i++){
		q[i].x=read();q[i].l=read();q[i].r=read();
		if (q[i].l==0 && q[i].r==MAX) ans++;
	}

	sort(q+1,q+1+m);

	int cur=0;
	for (int i=1;i<=m;i++){
		while (cur<=q[i].x){
			for (auto j:v[cur])
				t.add(j.first,j.second);
			cur++;
		}
		int tmp=t.query2(q[i].l,q[i].r);
		ans+=tmp;
	}

	cout<<ans<<endl;
	return 0;
}
```



---

## 作者：max67 (赞：4)

## 前言

~~一鱼两吃？~~

[JOI2014 裁剪线](https://www.luogu.com.cn/problem/AT_joi2014ho5) 是 [CF1401E](https://www.luogu.com.cn/problem/CF1401E) 的加强版。对于前一题，你可以在 [loj2760](https://loj.ac/p/2760) 查看更详细的题面。

你也可以通过 [这个](https://www.luogu.com.cn/blog/max67/solution-at-joi2014ho5) 和 [这个](https://www.luogu.com.cn/blog/max67/solution-cf1401e) 跳到两条几乎一模一样的题解。
## 题解

$w,h$ 为原题中的矩形长宽。

首先将线段的横纵坐标离散化，下文假定 $w,h \le 10^5$。下文假设 $k$ 是原题中的 $n+m$。

本题解讲的是去除横边和竖边必须与矩形边直接相连的条件后的做法。
### 做法 1

或者你可以康康这篇[题解](https://blog.csdn.net/qq_42101694/article/details/104775768)。


显然被答案可以看做这张图形成的极大连通块数量（我们把 $(i,j)$ 看做一个点，两个点之间联通当且仅当两个点可以四联通并且不经过裁剪线）

看着样例的图像，你想起了曾经做过的模板题[扫描线](https://www.luogu.com.cn/problem/P5490)。那么我们模仿对应的套路，从上到下扫描每一行的贡献。

一个睿智的想法是动态维护当前行的每个点属于哪个联通块。答案即为连通块的数量。

* 加入一条竖直线段：假设存在一条起点为 $(i+1,x)$ 的竖直线段，直观上来看他把第 $i+1$ 行分割成了依然相连的两个部分，但这两个部分仅通过第 $i+1$ 行的点无法互相联通。

[![ppAk6Jg.png](https://s1.ax1x.com/2023/03/03/ppAk6Jg.png)](https://imgse.com/i/ppAk6Jg)

* 删除一条竖直线段：假设存在一条终点为 $(i+1,x)$ 的竖直线段，从直观上来看他把我们原本认为可能不相联通的两个连通块并在一起。

[![ppAkgzj.png](https://s1.ax1x.com/2023/03/03/ppAkgzj.png)](https://imgse.com/i/ppAkgzj)

* 加入一条水平线段：假设存在一条 $(i,x) \rightarrow (i,y)$ 的水平线段，假设他与水平线段交的点为：$(i,a_1),(i,a_2)\dots(i,a_n)$，那么对于 $j \in [a_1,a_n]$ 内的点，$(i,j)$ 与 $(i+1,j)$ 在前 $i+1$ 行中不连通。我们可以直观的看做新建了 $n-1$ 个连通块，但这些连通块可能在之后的行中与其他连通块合并。

[![ppAm8ot.png](https://s1.ax1x.com/2023/03/03/ppAm8ot.png)](https://imgse.com/i/ppAm8ot)

因为答案是 $O(n^2)$ 级别的，所以我们不能鱼唇的直接维护每个点所属的连通块编号。但是我们发现当在删除一条竖直线段时才会有两个连通块进行合并，或者加入一条竖直线段时有两个部分相连通——这是 $O(k)$ 级别的。我们可以给这些可能特殊的连通块一个标号，最后再用并查集计算连通块的数量。

这启发我们分开维护可能相同的联通块和其他连通块。大概需要这些操作：

* 我们把一个区间看成一个（当前行的）连通块。保证同一个区间内的点在同一行内互相联通。不同的区间可能互相联通。默认每个区间的贡献为 $1$，看成一个互不相同的连通块。初始默认每个区间没有标号。

* 加入一个线段：把一个区间分裂成两个区间，删去这两个区间的贡献，（如果没有编号的话）给他们一个新的标号。

* 把两个区间合并，并删去这两个区间的贡献，（如果没有标号的话新设标号）把他们两个的标号合并。

* 统计包含在询问区间内的所有区间的贡献，并重新把他之内的所有区间内的贡献设为 $1$，标号清空。

* 最后用并查集统计连通块个数。

容易发现平衡树（或者线段树？）能胜任此次工作，复杂度为 $O(k\log k  +k\alpha(k))$。

另外，可以把原图矩形的四条边也看成加入进来的边。

代码的话可以看开头给的题解。（需要略微改动）


### 做法 2

你睿智的发现这是一张放在平面上的图（~~但是并不是叫做平面图~~），你回想起了伟大的[欧拉公式](https://oi-wiki.org/graph/planar/)：

$$
n-m+r=p+1
$$

（$n$ 是点数，$m$ 是边数，$r$ 是面数，$p$ 是联通分支数）

如果能把题目的图变成一张平面图，说不定就能轻松的算出答案。成为平面图的其中一个方法是有一张方法使得这张图放在平面上使得边互不相交。

那么一个简单的构造方法是把题目所给图的所有交点建做新图的顶点，新图两个顶点之间有连边当且仅当他们在原图中相邻（存在一条路径使得不经过其他新图的顶点）。那么问题就转化成了对新图的点数，边数，联通分支数进行计数。


[![ppAEXa6.png](https://s1.ax1x.com/2023/03/03/ppAEXa6.png)](https://imgse.com/i/ppAEXa6)

如果你直接暴力维护的话也不是不行，但是我们可以挖掘新图中的一些性质对原图进行简化。

先考虑对点数以及边数的计数，一个朴素的想法是考虑原图中每条线段对答案的贡献：

* 若第 $x$ 条线段被 $a_x$ 条线段穿过，那么他对新图贡献了 $a_x-1$ 条边。由于每个新图中的点会被原图中的两条线段穿过。设 $n$ 是新点数，$m,r$ 同理，因此可以得到等式：

$$
\sum_{x\in[1,k]} a_x= 2\times n
$$

那么边数即：

$$
m=\sum_{x\in[1,k]} (a_x-1) = 2\times n-  k 
$$

那么求 $r$ 的式子可以简化为：

$$
n-m+r = p+1 \rightarrow r=p+1-n+(2\times n-k)\rightarrow r=p+1 + n-k
$$

由于这个公式计算了这个矩形外面的面积为无限大的面，因此答案可以写作：

$$
r=p+n-k
$$

接下来讲解实现细节：

对于点数的统计，我们可以采用类似扫描线的形式，用树状数组记录当前行的竖直线段个数，遇到水平线段时统计覆盖的个数即可。

对于联通分支的统计，因为在原图中的线段上的点互相联通，我们可以转为维护原图线段的联通分支个数。

还是套用类似扫描线的方式，那么当我们遇到一条水平线段时，我们需要与与他相交的所有竖直边用并查集合并。如何操作？若一个区间被水平线段合并，那么在当前时刻内部的所有竖直边都被合并，以后再被水平线段合并时（不考虑这之间加入的其他竖直边）只需合并其中的一条竖直边即可。显然操作之后我们只需要选出一个消失最晚的竖直线段作为当前线段的代表元素即可。

按照上面的想法，我们考虑把询问区间拆成 $\log$ 段维护，因此我们用线段树维护区间。加入竖直线段时往线段树上所有包含他的区间加入。对于询问区间，我们在线段树上找到 $\log$ 个被他包含的区间，每个区间内的所有点与水平线段暴力连边，并保留消失最晚的一条竖直边。对于删除操作，我们模仿延迟标记，对这个竖直线段打个 tag，扫到时直接跳过即可。用 vector 维护即可。

那么总的复杂度是 $O(k \log k+k\alpha (k))$，时间复杂度也是 $O(k\log k+k)$。注意不是 $O(k\log k\times \alpha(k))$，因为虽然加入了 $O(k\log k )$ 个点，但只有 $O(k)$ 个标号不同的线段。

~~代码实现的时候记得临时变量不能开得太大，也就是说用 vector 离散化的时候如果它是临时变量，lower_bound 会变得很慢。。。~~


```cpp
#include<bits/stdc++.h>
#define pii pair<int,int>
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define ll long long
#define eb emplace_back 
using namespace std;
const int N=2e6+10;
struct Seg{int x,l,r,id;}p[N];
int n,m,k,R;
int tag[N];
vector<int>qry[N],add[N];
namespace F
{
	int fa[N];
	void clear(int n){for(int i=0;i<=n;i++)fa[i]=i;}
	int get(int x){return x==fa[x]?x:fa[x]=get(fa[x]);}
	void merge(int x,int y){x=get(x);y=get(y);if(x!=y)fa[x]=y;}
}
namespace bit
{
	#define lb(x) (x&(-x))
	int c[N];
	void add(int x,int y){for(;x<=R;x+=lb(x))c[x]+=y;}
	int ask(int x){int t=0;for(;x;x-=lb(x))t+=c[x];return t;}
	int ask(int l,int r){return ask(r)-ask(l-1);}
}
namespace T
{
	#define ls (x<<1)
	#define rs (x<<1|1)
	#define midd (L+R>>1)
	vector<int>vt[N];
	void insert(int x,int p,int L,int R,int v)
	{
		vt[x].pb(v);
		if(L==R)return;
		int mid=midd;
		if(p<=mid)insert(ls,p,L,mid,v);
		else insert(rs,p,mid+1,R,v);
	}
	void merge(vector<int>&vt,int v)
	{
		int id=0;
		for(auto y:vt)if(y&&!tag[y])
			F::merge(v,y),(p[y].r>p[id].r?id=y:0);
		vt.clear();vt.pb(id);
	}
	void query(int x,int l,int r,int L,int R,int v)
	{
		if(l<=L&&R<=r)return merge(vt[x],v);
		int mid=midd;
		if(l<=mid)query(ls,l,r,L,mid,v);
		if(r>mid)query(rs,l,r,mid+1,R,v);
	}
}
ll solve()
{
	ll res=0;
	for(int i=1;i<=R;i++)
	{
		for(auto y:add[i])
			if(y>0)bit::add(p[y].x,1),T::insert(1,p[y].x,1,R,y);
			else bit::add(p[-y].x,-1),tag[-y]=1;
		for(auto y:qry[i])
			T::query(1,p[y].l,p[y].r,1,R,y),res+=bit::ask(p[y].l,p[y].r);
	}
	for(int i=1;i<=k;i++)res+=F::fa[i]==i;
	return res;
}
vector<int>vt;
signed main()
{
	n=1e6;m=1e6;int k1=0,k2=0;
	scanf("%d%d",&k1,&k2);k=k1+k2;
	p[0]={-1,-1,-1,-1};
	for(int i=1,a,b,c,d;i<=k;i++)
	{
		if(i<=k1)scanf("%d%d%d",&a,&b,&d),c=a;
		else scanf("%d%d%d",&b,&a,&c),d=b;
		p[i]={a,b,c,d};
		vt.pb(a);vt.pb(b);vt.pb(c);vt.pb(d);
	}
	vt.pb(0);vt.pb(n);vt.pb(m);
	p[++k]={0,0,n,0};p[++k]={0,0,0,m};p[++k]={n,0,n,m};p[++k]={0,m,n,m};
	sort(vt.begin(),vt.end());vt.erase(unique(vt.begin(),vt.end()),vt.end()); 
	R=vt.size();F::clear(k);
	for(int i=1;i<=k;i++)
	{
		int a=p[i].x,b=p[i].l,c=p[i].r,d=p[i].id;
		auto get=[=](int x){return lower_bound(vt.begin(),vt.end(),x)-vt.begin()+1;};
		a=get(a);b=get(b);c=get(c);d=get(d);
		if(a==c)p[i]={a,b,d,i},qry[a].pb(i);
		else p[i]={b,a,c,i},add[a].pb(i),add[c+1].pb(-i);
	}
	printf("%lld\n",solve()-k);
	return 0;
}
```


---

## 作者：xuyunao (赞：3)

# CF1401E 严谨证明

本题结论是：分出区域的数量 = 交点数量 $+$ 贯穿边的数量 $+1$，想要感性理解请参考其他题解，这里给出严谨的证明。严谨证明来自 [lzx](https://www.luogu.com.cn/user/561613)（太强了）。

首先需要知道前置知识：  
[oi-wiki 平面图上的欧拉公式](https://oi-wiki.org/graph/planar/#%E6%AC%A7%E6%8B%89%E5%85%AC%E5%BC%8F)。  
[平面图上的欧拉公式](https://zhuanlan.zhihu.com/p/497187113)。

## 前置定理部分

在本文中平面图的定义为：可以在一个平面上绘制的无向图，且任何两条边仅在顶点处相交。对于本题也就是说，两条边的交点也被计算为顶点。

下图使用黑色点表示平面图的顶点，左侧不是平面图，右侧是平面图。

![如图](https://cdn.luogu.com.cn/upload/image_hosting/5yid0oc1.png)

在平面图中，我们设点的数量为 $N$，边的数量为 $M$，所划分成区域的数量为 $K$，要注意这里的 $K$ 不仅包含了图形内部，也包含了外部的区域，例如在下面图中 $K = 2$。

![](https://cdn.luogu.com.cn/upload/image_hosting/vrvdwy8s.png)

定理内容为：$N - M + K = 2$。

由于 $K$ 还包含了外部区域，这部分不是我们想要统计的，因此在这个题里面，实际上是 $N - M + K = 1$，进行移项，易得 $K = M - N + 1$。

这样我们就把问题转化为，对于给出的这张图，将其转化为一张平面图之后，要求出它的点的数量 $N$ 和边的数量 $M$。

下文中，我们把长度为 $10^6$ 的边称为贯穿边，其余称为普通边，假设贯穿边总共有 $l$ 条，并把交点的个数设为 $x$。

## 计算部分

我们分别来计算，先来考虑点的数量，分为矩形上的点和矩形内部的点两部分计算。

### 计算点的数量
对于矩形上的点，有以下几种：

- 矩形最初有 $4$ 个点。
- 加入一条普通边，会与矩形产生 $1$ 个交点。
- 加入一条贯穿边，会与矩形产生 $2$ 个交点。

将其相加，位于矩形上的点总共有 $4 + m + l$ 个。

矩形内部的点，也就是交点的个数 $x$。

将上述两部分相加，得到 $N = 4 + m + l + x$。

### 计算边的数量

我们依旧分开考虑，首先来看矩形上的。

最初的矩形有 $4$ 条边，随后往里加入边，发现每加入一条普通边，会与矩形产生一个交点，这个交点把一条边分成了两段，也就相当于每条普通边会额外产生 $1$ 条边。

再来看贯穿边，贯穿边会与矩形产生 $2$ 个交点，也就是将两条线段分别分成 $2$ 段，因此每条贯穿边会产生 $2$ 条边。

矩形上共有 $4 + m + l$ 条边。

接下来看矩形内部，每个交点会产生 $2$ 条边，如下图所示。

![](https://cdn.luogu.com.cn/upload/image_hosting/1eyi65fz.png)

如图，两条普通边产生了 $1$ 个交点，这个交点对应着 $1,2$ 两条边。这里要注意，普通边在末端并没有与矩形另一边相交，因此伸出部分不被算作边，相当于实际上这幅图是这样的。

![](https://cdn.luogu.com.cn/upload/image_hosting/p4u1h5mi.png)

再来看贯穿边，贯穿边的每个交点会产生 $3$ 条边，因此两种边一共会产生 $2 \times x + l$ 的贡献，贯穿边具体如图。

![](https://cdn.luogu.com.cn/upload/image_hosting/o50hedck.png)

那么边的数量 $M = 4 + m + 2 \times l + 2 \times x$。

我们把 $N,M$ 代回到本题的公式中，$K = M - N + 1 = l + x + 1$，也就是结论，分出的区域数量 $=$ 交点数量 $+$ 贯穿边的数量 $+1$。

---

## 作者：UncleSam_Died (赞：2)

### 解题思路
其实多看几组也能发现块数等于交点的数量加上两个端点都在边上的线段数量再加一。

证明如下（图见样例）：
- 对于两条只有一个端点位于边上的线段，因为保证有一个端点位于边上，那么这两条线段的交点一定会和已存在的点、边构成一个新的矩形；
- 对于其中有一条为两个端点均位于边上的两条线段，两个端点均位于边上的线段会与已存在的两边构成两个矩形；
- 剩下的不规则部分产生 $1$ 的贡献。

此时问题转化为如何计算出交点数量。

考虑枚举横坐标，然后统计出此时这个坐标上有多少条横向线段，然后判断是否有一条竖线的横坐标为当前横坐标，如果有，则分以下两种情况计算：
1. 存在一个端点位于 x 轴上，那么直接将答案加上纵坐标小于等于 $r_i$ 的横线数量即可；
2. 其他情况，不妨设当前横坐标上有 $sum$ 条横向线段，那么答案应加上 $sum$ 减去纵坐标小于 $l_i$ 的横线数量。

那么，我们需要做到快速维护横向线段。考虑使用树状数组。设当前横坐标为 $x$，设横线段左端点横坐标为 $la_i$，右端点横坐标为 $ra_i$，纵坐标为 $y_i$。那么我们分别对于横线按照 $la_i$ 从小到大和 $ra_i$ 从大到小排序，然后判断若 $la_i=x$，那么在 $y_i$ 位置加上 $1$；若 $ra_1=x$，那么在 $y_i$ 位置减去 $1$。然后判断若 $x$ 处有纵线段，那么直接查找即可。

本题步骤如下：
- 分别存储横、纵线段，横线段存两份；
- 将纵线段按 $x$ 排序，两份横线段分别按 $la_i$ 从小到大和 $ra_i$ 从大到小排序；
- 枚举 $x$，更新当前位置上的横线段数量；
- 判断是否存在一条竖线段，若有则按上文所讲方法更新 $ans$ 即可；
- 枚举每条线段，若该线段两个端点都在正方形边上，那么 $ans\gets ans+1$；
- 输出 $ans+1$；

### 注意事项
- 不开 long long 见祖宗；
- 不需要考虑树状数组越界问题；
- 先添加线段，然后计算，最后再删；
- 在计算 $r$ 位于边上的线段时，一定要查询小于等于 $l-1$ 的横线数量，而不是 $l$。

### AC 代码
```cpp
#include<set>
#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
#define int long long
#define N 100005
#define mint 0
#define maxt 1000000
int n,m;
struct Line{
    int y,l,r;
}a[N],d[N];
struct lIne{
    int x,l,r;
}b[N];
inline bool cmp(Line A,Line B){
    return A.l<B.l;
}
inline bool Cmp(lIne A,lIne B){
    return A.x<B.x;
}
inline bool CMP(Line A,Line B){
    return A.r<B.r;
}
struct BitTree{
    int val[(maxt<<2)+5];
    #define lowbit(x) (x&(-x))
    inline void Add(int x,int v){
        while(x<=maxt){
            val[x]+=v;
            x+=lowbit(x);
        }
    }
    inline int Query(int x){
        int res=0;
        while(x){
            res+=val[x];
            x-=lowbit(x);
        }return res;
    }
}tree;
signed main(){
    scanf("%lld%lld",&n,&m);
    for(register int i=1;i<=n;++i){
        scanf("%lld",&a[i].y);
        scanf("%lld",&a[i].l);
        scanf("%lld",&a[i].r);
    }
    for(register int i=1;i<=m;++i){
        scanf("%lld",&b[i].x);
        scanf("%lld",&b[i].l);
        scanf("%lld",&b[i].r);
    }
    for(register int i=1;i<=n;++i)
        d[i]=a[i];
    std::sort(a+1,a+n+1,cmp);
    std::sort(d+1,d+n+1,CMP);
    std::sort(b+1,b+m+1,Cmp);
    int la=1,ra=1,lb=1,ans=0,cnt=0;
    for(register int x=mint;x<=maxt;++x){
        while(a[la].l==x&&la<=n){
            tree.Add(a[la].y,1);
            ++la;++cnt;
        }
        if(x==b[lb].x){
            if(b[lb].l==mint&&b[lb].r==maxt)
                ++ans;
            if(b[lb].l==mint)
                ans+=tree.Query(b[lb].r);
            else
                ans+=cnt-tree.Query(b[lb].l-1);
            ++lb;
        }while(d[ra].r==x&&ra<=n){
            tree.Add(d[ra].y,-1);
            ++ra;--cnt;
        }
    }for(register int i=1;i<=n;++i)
        if(a[i].l==mint&&a[i].r==maxt)
            ++ans;
    printf("%lld",ans+1ll);
}
```

---

## 作者：Fairicle (赞：2)

这题很容易看出大致的思路

首先通过观察发现，答案就是（长度为 $1e6$ 的线段条数） $+$ （线段之间的交点个数） $+ \ 1$

那么问题转化为如何统计这些线段之间的交点个数。

容易想到一种做法，在 $x$ 轴上从左向右扫，碰到一条水平线段的左端点就在树状数组中加 $1$，碰到右端点加 $1$ 的位置就减 $1$，同时统计每条竖直线段对答案的贡献。

具体见代码：
```cpp
#include"bits/stdc++.h"
using namespace std;
#define ll long long
#define ul unsigned long long
#define ui unsigned int
#define ri register int
#define pb push_back
#define mp make_pair
char p[30]={'0','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
inline ll rd(){
	ll x=0,flag=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') flag=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+(ch^48);ch=getchar();}
	return x*flag;
}
#define N 1000010
int n,m,y[N],lx[N],rx[N],x[N],ly[N],ry[N],co[N];
ll ans;
inline int lowbit(int x){return x & ( - x ) ;}
inline void add(int x,int v){
	for(ri i=x;i<=1e6;i+=lowbit(i)) co[i]+=v;
}
inline int sum(int x){
	int ans=0;
	for(ri i=x;i>0;i-=lowbit(i)) ans+=co[i];return ans;
}
vector<int>a[N];
vector<int>b[N];
vector<int>c[N];
int main()
{
	std::ios::sync_with_stdio(false);
	n=rd(),m=rd();
	for(ri i=1;i<=n;++i){
		y[i]=rd(),lx[i]=rd(),rx[i]=rd();
		if(rx[i]-lx[i]==1000000) ans++;
		a[lx[i]].push_back(i);
		b[rx[i]+1].push_back(i);
	}
	for(ri i=1;i<=m;++i){
		x[i]=rd(),ly[i]=rd(),ry[i]=rd();
		if(ry[i]-ly[i]==1000000) ans++;
		c[x[i]].push_back(i);
	}
	for(ri i=0;i<=1000000;++i){
		int siz=a[i].size();
		for(ri j=0;j<siz;++j) add(y[a[i][j]],1);siz=b[i].size();
		for(ri j=0;j<siz;++j) add(y[b[i][j]],-1);siz=c[i].size();
		for(ri j=0;j<siz;++j){
			if(ly[c[i][j]]==0) ans+=sum(ry[c[i][j]]);
			else ans+=sum(1000000)-sum(ly[c[i][j]]-1);
			//cout<<i<<" "<<ans<<endl;
		}
	}
	cout<<ans+1;
    return 0;
}
```


---

## 作者：SJZ2010 (赞：1)

没对与正方形相交细想，结果写了线段树……

不过我这个做法可以改几下通过[加强版](https://www.luogu.com.cn/problem/AT_joi2014ho5)。（应该吧）

---

我们注意到，新增一个连通块的充要条件是四面都有线把它围住。（废话）

这就启示我们按照扫描线的方式加入与删除线段。

但还要考虑如果在这根横线前面没有竖线作为“底线”时怎么办？如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/o3avetjo.png)

解决方法也不难，我们在加入线段时，暴力把还没有“底线”的横线“激活”即可，被激活的横线可以做贡献。在横线线末端我们再把它删掉。而竖线算答案时，就会提供与它相交的激活的竖线的贡献。（不过你得先把顶上、底下的正方形的边加进去，但这样会多算一次要减掉）

[AC.](https://codeforces.com/contest/1401/submission/277846902)

---

## 作者：baoziwu2 (赞：1)

~~这道题可以作为扫描线的前置题练手~~

~~真的~~

先说结论：我们定义贯穿线为满足题目要求且长度为 $10^6$ 的线段，设 $num_1$ 为贯穿线的数量，$num_2$ 为交点的数量
答案即为 $ans = num_{1}+num_{2}+1$

浅浅说一下理解：因为题目要求的线段是平行坐标轴，所以产生的交点必然是横纵线相交，又因为是在封闭的正方形内，所以所以出现一个交点必然会产生一个额外的正方形，不过当贯穿线的存在本来就可以把正方形分开，所以要考虑上贯穿线的贡献

所以我们将本题转换为了统计横纵线交点数量，考虑使用扫描线解决

这里我们把横线抽象成时刻，纵轴想象成一个数组 `line`，$line_i = 0/1$ 表示当前 $i$ 纵坐标有无被线段覆盖。

一条横边 $(y,l,r)$ 即为在时刻 $l$ 到时刻 $r$ 在 $y$ 纵坐标做出贡献，具体表现为在时刻 $l$ 对 $line_y$ 加上 $1$，时刻 $r+1$ 对 $line_y$ 减去 $1$

一条纵边 $(x,l,r)$ 即为在 $line_l$ 到 $line_r$ 都加上 $1$

所以我们需要维护区间查询，单点修改，可以考虑用树状数组解决

看到其他题解里将修改和查询分开，其实没有必要，只要保证时间按顺序即可，同时保证在相同时间内先修改，后查询即可

~~可能常数较大，但是真的好写~~

```C++
#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
using ll = long long;

int n, m;

inline int read() {
  int res = 0, f = 1; char c = getchar();
  while(!isdigit(c)) {
    if(c == '-') f = -1;
    c = getchar();
  }
  while(isdigit(c)) {
    res = res * 10 + c - '0';
    c = getchar();
  }
  return res * f;
}

class fenwickTree {
  int static const N = 1e6 + 5;
  int c[N];
#define lowbit(x) x & -x
public:
  inline void insert(int x, int d) {
    for(int i = x; i < N; i += lowbit(i)) 
      c[i] += d;
  }
  
  inline int query(int x) {
    ll res = 0;
    for(int i = x; i; i -= lowbit(i))
      res += c[i];
    return res;
  }
}t;

struct node {
  int id; // mod = 1, query = 2;
  int tim, l, r;
  
  bool operator < (const node& ano) const {
    if(tim == ano.tim) return id < ano.id;
    return tim < ano.tim;
  }
};

vector<node> line;

signed main() {
  n = read(), m = read();
  line.reserve(2e5);
  
  ll ans = 0;
  while(n --) { 
    int y = read() + 1, l = read() + 1, r = read() + 1;
    ans += (r - l == 1e6);
    line.push_back({1, l, y, 1});
    line.push_back({1, r + 1, y, -1});
  }
  
  while(m --) {
    int x = read() + 1, l = read() + 1, r = read() + 1;
    ans += (r - l == 1e6);
    line.push_back({2, x, l, r});
  }
  
  sort(line.begin(), line.end());
  
  for(node x : line) {
    if(x.id == 1) t.insert(x.l, x.r);
    else ans += t.query(x.r) - t.query(x.l - 1);
  }
  
  printf("%lld\n", ans + 1);
  return 0;
}
```

---

## 作者：Plozia (赞：1)

宣传博客 $\to$ [link](https://blog.csdn.net/BWzhuzehao/article/details/119642949)

一道套路题。

考虑将所有的横线分个类，左端点在边界上的为 1 类（L 类），右端点在边界上的为 1 类（R 类），左右都在边界上的随意分，然后将所有的竖线按照其 $x$ 升序排序。

开两个值域线段树（能支持单点修改区间查询即可），一棵维护 L 类，一棵维护 R 类。

- 理论上一棵也可行，但是两棵理解方便。

将所有竖线从左到右依次统计竖线分割横线所创造的贡献，对于一条横线而言，首先将 R 类里面所有左端点小于等于当前竖线 $x$ 的线丢到线段树里，将 L 类里面所有右端点大于当前竖线 $x$ 的删掉，这样线段树维护的横线就是可能会做出贡献的线。

然后直接统计一下两类中 $y$ 被竖线覆盖的线段个数即可。

这两个操作都能用线段树完成。

需要注意的是可能有的线左右端点/上下端点都在边界上，此时答案需要额外加 1。

Code：[GitHub CodeBase-of-Plozia CF1401E Divide Square.cpp](https://github.com/Plozia/CodeBase-of-Plozia/blob/main/Codeforces%20%E5%88%B7%E9%A2%98%E5%90%88%E9%9B%86/CF1401E%20Divide%20Square.cpp)

```cpp
/*
========= Plozia =========
    Author:Plozia
    Problem:CF1401E Divide Square
    Date:2021/8/12
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 1e5 + 5, MAXA = 1e6 + 5;
int n, m, cntl, cntr, cl, cr;
LL ans = 1;
struct node1 { int l, r, sum; } LTree[MAXA << 2], RTree[MAXA << 2];
struct node2 { int y, r; } Linel[MAXN];
struct node3 { int y, l; } Liner[MAXN];
struct node4 { int x, l, r; } a[MAXN];

int Read()
{
    int sum = 0, fh = 1; char ch = getchar();
    for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
    for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = sum * 10 + (ch ^ 48);
    return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }
bool cmp2(const node2 &fir, const node2 &sec) { return fir.r < sec.r; }
bool cmp3(const node3 &fir, const node3 &sec) { return fir.l < sec.l; }
bool cmp4(const node4 &fir, const node4 &sec) { return fir.x < sec.x; }

void LBuild(int p, int l, int r)
{
    LTree[p].l = l, LTree[p].r = r;
    if (l == r) return ;
    int mid = (l + r) >> 1;
    LBuild(p << 1, l, mid); LBuild(p << 1 | 1, mid + 1, r);
}

void RBuild(int p, int l, int r)
{
    RTree[p].l = l, RTree[p].r = r;
    if (l == r) return ;
    int mid = (l + r) >> 1;
    RBuild(p << 1, l, mid); RBuild(p << 1 | 1, mid + 1, r);
}

void LChange(int p, int x, int d)
{
    if (LTree[p].l == LTree[p].r) { LTree[p].sum += d; return ; }
    int mid = (LTree[p].l + LTree[p].r) >> 1;
    if (x <= mid) LChange(p << 1, x, d);
    else LChange(p << 1 | 1, x, d);
    LTree[p].sum = LTree[p << 1].sum + LTree[p << 1 | 1].sum;
}

void RChange(int p, int x, int d)
{
    if (RTree[p].l == RTree[p].r) { RTree[p].sum += d; return ; }
    int mid = (RTree[p].l + RTree[p].r) >> 1;
    if (x <= mid) RChange(p << 1, x, d);
    else RChange(p << 1 | 1, x, d);
    RTree[p].sum = RTree[p << 1].sum + RTree[p << 1 | 1].sum;
}

int LAsk(int p, int l, int r)
{
    if (LTree[p].l >= l && LTree[p].r <= r) return LTree[p].sum;
    int mid = (LTree[p].l + LTree[p].r) >> 1, val = 0;
    if (l <= mid) val += LAsk(p << 1, l, r);
    if (r > mid) val += LAsk(p << 1 | 1, l, r);
    return val;
}

int RAsk(int p, int l, int r)
{
    if (RTree[p].l >= l && RTree[p].r <= r) return RTree[p].sum;
    int mid = (RTree[p].l + RTree[p].r) >> 1, val = 0;
    if (l <= mid) val += RAsk(p << 1, l, r);
    if (r > mid) val += RAsk(p << 1 | 1, l, r);
    return val;
}

int main()
{
    n = Read(), m = Read();
    for (int i = 1; i <= n; ++i)
    {
        int y = Read(), l = Read(), r = Read();
        if (l == 0) Linel[++cntl] = (node2){y, r};
        else Liner[++cntr] = (node3){y, l};
        if (l == 0 && r == 1000000) ++ans;
    }
    for (int i = 1; i <= m; ++i) a[i].x = Read(), a[i].l = Read(), a[i].r = Read();
    std::sort(Linel + 1, Linel + cntl + 1, cmp2);
    std::sort(Liner + 1, Liner + cntr + 1, cmp3);
    std::sort(a + 1, a + m + 1, cmp4);
    LBuild(1, 0, 1000000); RBuild(1, 0, 1000000);
    for (int i = 1; i <= cntl; ++i) LChange(1, Linel[i].y, 1);
    for (int i = 1; i <= m; ++i)
    {
        if (a[i].l == 0 && a[i].r == 1000000) ++ans;
        for (; cl <= cntl && Linel[cl].r < a[i].x; ++cl) LChange(1, Linel[cl].y, -1);
        for (; cr <= cntr && Liner[cr].l <= a[i].x; ++cr) RChange(1, Liner[cr].y, 1);
        ans += (LL)RAsk(1, a[i].l, a[i].r) + (LL)LAsk(1, a[i].l, a[i].r);
    }
    printf("%lld\n", ans); return 0;
}
```

---

## 作者：RockyYue (赞：0)

### 1401E

有正方形，其中点横纵坐标范围均为 $[0,10^6]$，$n$ 条横线和 $m$ 条竖线穿过，每条线必有一端点在正方形边上，求这些线把正方形分成了多少部分，要求 $O(n\log n+m\log m+V\log V)$，其中 $V=10^6$。

### Sol

- 思考产生一个新块的条件，当且仅当，一条线段贯穿整个正方形，或横竖两条线段有交点（在所有相同类型线段没有重复部分的条件下）。
- 第一部分好求，想如何处理交点个数，记录下横线段（修改），竖线段处计算贡献（查询）。
  - 想如何对于竖线段快速求出与其交横线段个数，按照输入中对线段的描述，竖线段 $(x,yl,yr)$ 表示其中点横坐标均为 $x$，纵构成 $[yl,yr]$，横线段 $(y,xl,xr)$ 与其交充要条件为 $x\in [xl,xr]$ 且 $y\in [yl,yr]$。
  - 利用时间-值域思想，将其中一个限制转化为时间上限制（不妨 $x$）则每个时刻下只需要考虑一维线段上限制。
  - 记 $cov_i$ 为当前时刻下，线段上点 $i$ 是否被覆盖（即是否有横经过，只考虑整点），有则一次修改可以表示为，时刻 $[xl,xr]$ 中将 $cov_y$ 设为 $1$，查询则时刻 $x$ 下，求 $\sum_{i=yl}^{yr}{cov_i}$。
- 实现中，规定同一个时刻下先查询后修改（调换顺序亦可），一次修改只在两端操作，中间保留 $cov$ 即可，即在 $xl-1$ 时刻设其为 $1$，$xr$ 时刻设为 $0$，可以树状数组。
- 注意特殊处理时刻 $-1$ 要设为 $1$ 的部分，同时操作前线段去重。

---

## 作者：ifffer_2137 (赞：0)

### 题意
给定一个 $10^6\times 10^6$ 的正方形，$n$ 条横线和 $m$ 条竖线穿过了它，**其中每条线的两个端点之一一定在正方形的边上，任意两条线段不共线**，求这些线把正方形分成了多少个部分。
### 分析
用手画一下找一下规律，最开始一个块，先画上所有横线，块数增加了两端顶满的横线数量，考虑一条竖线，发现它每穿过一条横线就会多一个块，如果它两端都顶满，就又会多一个块，所以我们只需要求出每条竖线与几条横线相交，再加上顶满线段数量加一就行了。

然后扫描线，从 x 轴扫一遍，动态维护当前的 y 轴，树状数组区间求和即可，时间复杂度 $\mathcal O(n\log_2n)$。

代码可能写得有点丑，将就看一下。
### 代码
```cpp
//From: ifffer_2137
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define inf 0x7fffffff
inline int read(){
    char ch=getchar();int x=0,w=1;
    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+ch-48,ch=getchar();return w==1?x:-x;
}
const int maxn=1e5+5;
const int maxm=1e6+5;
int n,m;
int ans=1;
struct node{
	int d,k;
};
vector<node> x[maxm],q[maxm];
struct Fenwick_Tree{
	int c[maxm];
	int lowbit(int x){
		return x&(-x);
	}
	void update(int x,int k){
		while(x<=1000000){
			c[x]+=k;
			x+=lowbit(x);
		}
	}
	int query(int x){
		int res=0;
		while(x){
			res+=c[x];
			x-=lowbit(x);
		}
		return res;
	}
}tr;
signed main(){
	cin.tie(0),cout.tie(0);
	n=read(),m=read();
	for(int i=1;i<=n;i++){
		int y=read(),l=read(),r=read();
		if(l==0&&r==1000000) ans++;
		x[l].push_back((node){y,1});
		x[r+1].push_back((node){y,-1});
	}
	for(int i=1;i<=m;i++){
		int x=read(),l=read(),r=read();
		if(l==0&&r==1000000) ans++;
		if(l==0) q[x].push_back((node){r,0});
		else q[x].push_back((node){l,1});
	}
	for(int i=0;i<=1000000;i++){
		for(node v:x[i]) tr.update(v.d,v.k);
		for(node v:q[i]){
			if(v.k) ans+=tr.query(1000000)-tr.query(v.d-1);
			else ans+=tr.query(v.d);
		}
	}
	cout<<ans<<endl;
	return 0;
}
```

---

