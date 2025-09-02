# 切り取り線  (Cutting)

## 题目描述

[problemUrl]: https://atcoder.jp/contests/joi2014ho/tasks/joi2014ho5

JOI 君はペーパークラフトが趣味である．今日も JOI 君はペーパークラフトの作品を作ろうとしている．

まず，JOI 君は設計図にしたがって $ 1 $ 枚の長方形の紙に $ N $ 本の切り取り線を印刷した．各切り取り線は，紙の縦または横の辺に平行な線分である．紙を切り出してできるすべての部分は作品の中で何らかの部品として用いられる．当然のことながら，部品数の多い作品は製作が大変である．JOI 君は，すべての切り取り線にしたがって紙を切り出したとき，紙がいくつの部分に分かれるかを知りたい．

## 说明/提示

### 課題

紙の大きさと，$ N $ 本の切り取り線の情報が与えられる．これらの切り取り線にしたがって紙を切り分けたとき，紙がいくつの部分に分かれるかを求めるプログラムを作成せよ．

- - - - - -

### 制限

すべての入力データは以下の条件を満たす．

- $ 1\ \leqq\ W\ \leqq\ 1\,000\,000\,000 $．
- $ 1\ \leqq\ H\ \leqq\ 1\,000\,000\,000 $．
- $ 1\ \leqq\ N\ \leqq\ 100\,000 $．

### 小課題

#### 小課題 1 \[5 点\]

以下の条件を満たす．

- $ W\ \leqq\ 1\,000 $．
- $ H\ \leqq\ 1\,000 $．
- $ N\ \leqq\ 1\,000 $．

#### 小課題 2 \[5 点\]

以下の条件を満たす．

- $ N\ \leqq\ 1\,000 $．

#### 小課題 3 \[20 点\]

共有点を持つような異なる $ 2 $ つの切り取り線の組の個数は，$ 100\,000 $ 以下である．

#### 小課題 4 \[20 点\]

切り取り線上の任意の点から紙のある辺上の点まで，いくつかの切り取り線をたどって行くことができる．

#### 小課題 5 \[50 点\]

追加の制限はない．

- - - - - -

### Sample Explanation 1

この入力の場合，切り取り線は下図のようになる． !\[2014-ho-t5-fig01.png\](https://img.atcoder.jp/joi2014ho/2014-ho-t5-fig01.png) よって，切り取り線によって紙は $ 4 $ つの部分に分かれる．なお，この入力は小課題 $ 4 $ の条件を満たしている． - - - - - -

### Sample Explanation 2

この入力の場合，切り取り線は下図のようになる． !\[2014-ho-t5-fig02.png\](https://img.atcoder.jp/joi2014ho/2014-ho-t5-fig02.png) よって，切り取り線によって紙は $ 5 $ つの部分に分かれる．なお，この入力は小課題 $ 4 $ の条件を満たしていない．

## 样例 #1

### 输入

```
10 10 5
6 0 6 7
0 6 7 6
2 3 9 3
2 3 2 10
1 9 8 9```

### 输出

```
4```

## 样例 #2

### 输入

```
13 7 28
1 1 4 1
1 1 1 3
2 2 3 2
2 2 2 3
1 3 2 3
3 2 3 6
4 1 4 6
3 6 4 6
5 1 8 1
5 1 5 6
6 2 7 2
6 2 6 5
7 2 7 5
6 5 7 5
8 1 8 6
5 6 8 6
9 1 12 1
9 1 9 2
9 2 10 2
12 1 12 2
11 2 12 2
10 2 10 5
9 5 10 5
9 5 9 6
11 2 11 5
11 5 12 5
12 5 12 6
9 6 12 6```

### 输出

```
5```

# 题解

## 作者：Linge_Zzzz (赞：6)

# 简要题意

给你一个 $w\times h$ 的矩形，内部给你 $n$ 条横平或竖直的线段，问这些线段分割矩形形成了多少联通块？

$n\leq 10^5,w,h\leq 10^9$。

# 解法

我们试图水平地从下往上扫描这些线段来求得答案。

进一步，我们能想到在每一个扫描时刻使用并查集维护这一行上每个点所属的连通块。

考虑加入直线后对连通块的变化——本质上是并查集的操作。

我们只需要考虑横着的和竖着的两种情况。

## 一条竖直的线段加入

（偷个官方图）

![](https://cdn.luogu.com.cn/upload/image_hosting/zt1nvhrh.png)

从视觉上来看，虽然这条线段加入了，但是它并没有真正地把原来的连通块分割开来。

## 一条竖直的线段离开

![](https://cdn.luogu.com.cn/upload/image_hosting/0kdi3jmu.png)

不管这条线段左右两边原来是不是在一个连通块里，它们最后都合为一体了，对应并查集的合并操作。

## 一条水平的线段加入

![](https://cdn.luogu.com.cn/upload/image_hosting/wilohl78.png)

我们可以看到，原来被竖着的线段分割形成的连通块，如果其完整地被这条横线覆盖，那么就相当于是对这些连通块在并查集里新开点。

## 一种朴素的解法

我们在并查集里维护上述东西，最后统计并查集里有多少个连通块，减去一即为答案。

但这样远远不够。仔细一想，瓶颈在于横线所造成的并查集新开点。如果我们每个都真的去开，岂不是太浪费时间了？考虑优化这一过程。

## 懒标记优化

我们不妨使用懒标记（先不去想懒标记如何实现）。对于一条水平线段的加入，我们对需要新开点的连通块打上懒标记，当下一次水平线段加入的时候，统计一下这个水平线段里包含了多少被标记过的连通块，则这些连通块必定对答案有贡献。

没有被标记的有没有贡献呢？加入完所有的线段后我们再看看并查集里有多少个连通块。因为已经被统计过的连通块都没有在并查集里新开点，所以不会造成重复统计。

## 实现

有插入、删除、标记，我们考虑 FHQ-Treap。

首先我们把线段分成三种：水平线段、竖直线段加入、竖直线段删除。对于这三种线段，我们按照他们操作的纵坐标升序排序。纵坐标相同的，竖直线段加入在前面，中间是水平线段，最后是竖直线段删除。

为什么要这么做呢？你可以把水平线段加入的操作看成统计之前的懒标记再打上新的懒标记。水平线段统计答案要用到之前的线段，所以不能先删，水平线段打懒标记要给后面的线段打，所以要先加入后面的线段。有人可能会问了，万一给之前的线段打上了怎么办？不要忘了我们马上就要把它删了，所以对答案没影响。

明确了操作顺序，考虑具体如何用平衡树实现。

我们对于每个连通块，记录它的左侧横坐标（你想用右侧也可以）。

分裂是按值分裂，方便我们快速通过值找到连通块。

```cpp
void split(int p,int v,int &x,int &y){
  if(!p){x=y=0;return;}
  pushdown(p);
  if(t[p].v<=v)split(t[p].rs,v,t[x=p].rs,y);
  else split(t[p].ls,v,x,t[y=p].ls);
  pushup(p);
}
int merge(int x,int y){
  if(!x||!y)return x+y;
  pushdown(x),pushdown(y);
  if(t[x].rd>t[y].rd){
    t[x].rs=merge(t[x].rs,y);
    pushup(x);
    return x;
  }else{
    t[y].ls=merge(x,t[y].ls);
    pushup(y);
    return y;
  }
}
```

对于平衡树上每个节点，我们还要记录这个点有没有懒标记 `lz`、这个点的子树里有多少个懒标记 `cv` 以及这个点在并查集中的编号 `id`。

`pushup` 和 `pushdown` 是显然的。

```cpp
void pushup(int p){
  if(!p)return;
  t[p].sz=t[t[p].ls].sz+t[t[p].rs].sz+1;
  t[p].cv=t[t[p].ls].cv+t[t[p].rs].cv;
}
void update_cv(int p){
  if(!p)return;
  t[p].cv=t[p].sz;
  t[p].lz=1;
}
void pushdown(int p){
  if(!p)return;
  if(t[p].lz){
    update_cv(t[p].ls);
    update_cv(t[p].rs);
    t[p].cv--;
    t[p].id=DSU::newnode();
    t[p].lz=0;
  }
}
```

考虑如何让竖直线段加入。

首先我们要先找到这个线段分割了哪个连通块，然后把这个连通块分割开。

```cpp
int mx(int p){ //最大值所在节点
  while(t[p].rs){
    pushdown(p);
    p=t[p].rs;
  }
  return p;
} 
void ins(int v){
  int x,y;
  split(rt,v,x,y);
  int p=newnode(v);
  t[p].id=t[mx(x)].id;// x 的最大值，即为被分割的连通块
  rt=merge(merge(x,p),y);
}
```

删除操作自然也不难想。

```cpp
void del(int v){
  int x,y,z;
  split(rt,v-1,x,y);
  split(y,v,y,z);
  DSU::merge(t[mx(x)].id,t[y].id);
  rt=merge(x,z);//因为保证线段不重合，所以可以认为 y 只有一个结点
}
```

打标记这个可能有点抽象。

```cpp
void update(int l,int r){
  int n,m,p,q;
  split(rt,l-1,n,m);
  split(m,r,m,q);
  split(m,t[mx(m)].v-1,m,p);
  ans+=t[m].cv;
  update_cv(m);
  rt=merge(merge(n,m),merge(p,q));
}
```

为什么分出来 `m` 之后还要去掉最右侧的一个呢？因为我们记录的是左侧坐标，最右侧的那个实际上是没有完全被这个区间包含的。

初始化直接插入一个负无穷的点表示整个区间。

最后注意数组别开小了，还有把原来矩形上下左右 $4$ 条边加进去。

# Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e5+10,INF=0x3f3f3f3f3f3f3f3f,mod=1e9+7;
int w,h,n;
struct op{
	int y,l,r,t;
	op(){}
	op(int _y,int _l,int _r,int _t):y(_y),l(_l),r(_r),t(_t){}
	bool operator<(op rhs){
		if(y==rhs.y)return t<rhs.t;
		else return y<rhs.y;
	}
}o[N*3];
int tot;
int ans;
namespace DSU{
	int fa[N*100],tot;
	int newnode(){tot++;return fa[tot]=tot;}
	int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}
	void merge(int x,int y){x=find(x),y=find(y),fa[x]=y;}
	int calc(){
		int res=0;
		for(int i=1;i<=tot;i++)
			if(fa[i]==i)res++;
		return res;
	}
}
namespace FHQ{
	struct node{
		int ls,rs;
		int sz,rd;
		int v,id;
		int lz,cv;
	}t[N*3];
	int tot,rt;
	stack<int> st;
	int newnode(int v){
		int p=0;
		if(!st.size())p=++tot;
		else p=st.top(),st.pop();
		t[p].sz=1,t[p].rd=rand();
		t[p].v=v;
		return p;
	}
	void delnode(int p){
		st.push(p);
		memset(&t[p],0,sizeof(node));
	}
	void pushup(int p){
		if(!p)return;
		t[p].sz=t[t[p].ls].sz+t[t[p].rs].sz+1;
		t[p].cv=t[t[p].ls].cv+t[t[p].rs].cv;
	}
	void update_cv(int p){
		if(!p)return;
		t[p].cv=t[p].sz;
		t[p].lz=1;
	}
	void pushdown(int p){
		if(!p)return;
		if(t[p].lz){
			update_cv(t[p].ls);
			update_cv(t[p].rs);
			t[p].cv--;
			t[p].id=DSU::newnode();
			t[p].lz=0;
		}
	}
	void split(int p,int v,int &x,int &y){
		if(!p){x=y=0;return;}
		pushdown(p);
		if(t[p].v<=v)split(t[p].rs,v,t[x=p].rs,y);
		else split(t[p].ls,v,x,t[y=p].ls);
		pushup(p);
	}
	int merge(int x,int y){
		if(!x||!y)return x+y;
		pushdown(x),pushdown(y);
		if(t[x].rd>t[y].rd){
			t[x].rs=merge(t[x].rs,y);
			pushup(x);
			return x;
		}else{
			t[y].ls=merge(x,t[y].ls);
			pushup(y);
			return y;
		}
	}
	int mx(int p){
		while(t[p].rs){
			pushdown(p);
			p=t[p].rs;
		}
		return p;
	}
	void ins(int v){
		int x,y;
		split(rt,v,x,y);
		int p=newnode(v);
		t[p].id=t[mx(x)].id;
		rt=merge(merge(x,p),y);
	}
	void del(int v){
		int x,y,z;
		split(rt,v-1,x,y);
		split(y,v,y,z);
		DSU::merge(t[mx(x)].id,t[y].id);
		rt=merge(x,z);
	}
	void update(int l,int r){
		int n,m,p,q;
		split(rt,l-1,n,m);
		split(m,r,m,q);
		split(m,t[mx(m)].v-1,m,p);
		ans+=t[m].cv;
		update_cv(m);
		rt=merge(merge(n,m),merge(p,q));
	}
	void init(){
		ins(-INF);
		t[rt].id=DSU::newnode();
	}
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>w>>h>>n;
	for(int i=1;i<=n;i++){
		int a,b,c,d;
		cin>>a>>b>>c>>d;
		if(b==d)o[++tot]=op(b,a,c,2);
		else o[++tot]=op(b,a,0,1),o[++tot]=op(d,c,0,3);
	}
	o[++tot]=op(0,0,w,2);
	o[++tot]=op(h,0,w,2);
	o[++tot]=op(0,0,0,1);
	o[++tot]=op(h,0,0,3);
	o[++tot]=op(0,w,0,1);
	o[++tot]=op(h,w,0,3);
	sort(o+1,o+1+tot);
	FHQ::init();
	for(int i=1;i<=tot;i++){
		if(o[i].t==1)FHQ::ins(o[i].l);
		if(o[i].t==2)FHQ::update(o[i].l,o[i].r);
		if(o[i].t==3)FHQ::del(o[i].l);
	}
	ans+=DSU::calc();
	cout<<ans-1<<'\n';
	return 0;
}

---

## 作者：max67 (赞：3)

## 前言

~~一鱼两吃？~~

[JOI2014 裁剪线](https://www.luogu.com.cn/problem/AT_joi2014ho5) 是 [CF1401E](https://www.luogu.com.cn/problem/CF1401E) 的加强版。对于前一题，你可以在 [loj2760](https://loj.ac/p/2760) 查看更详细的题面。

你也可以通过 [这个](https://www.luogu.com.cn/blog/max67/solution-at-joi2014ho5) 和 [这个](https://www.luogu.com.cn/blog/max67/solution-cf1401e) 跳到两条几乎一模一样的题解。
## 题解

首先将线段的横纵坐标离散化，下文假定 $w,h \le 10^5$。下文假设 $k$ 是原题中的 $n$。


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

代码的话可以看开头给的题解。


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

(~~可能是~~全网最短代码)

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
	scanf("%d%d%d",&n,&m,&k);
	p[0]={-1,-1,-1,-1};
	for(int i=1,a,b,c,d;i<=k;i++)
	{
		scanf("%d%d%d%d",&a,&b,&c,&d);
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

## 作者：Suiseiseki (赞：1)

题解：先丢一道[弱化版](http://codeforces.com/problemset/problem/1401/E)，然而这一道题的解题方法和刚才那道题没有太大关系。

这边先丢[官方题解](https://www.ioi-jp.org/joi/2013/2014-ho/2014-ho-t5-review.pdf)，如果您有疑问的话可以在官方题解中寻找解答。

首先肯定要离散化，这没有问题。

我们可以先考虑一个十分暴力的做法，我们将矩形化成 $1\times 1$ 的小方格，然后再找联通块。紧接着我们可以发现这之中的不少格子都是可以合并的，最后合并后剩下的个数就是联通块数。

如果暴力全部拆开来的话我们会得到一个非常暴力的 $O(n^2)$ 的做法，你可以取得 ~~日本选拔赛最高分~~ $10$ 分的好成绩。

发现边界非常麻烦，我们把边界拆成四条线段来做。

如果一些线段并没有相交，我们可以将它们分开来计算，这样对于答案是没有影响的。

至于这个东西怎么处理我们可以用并查集，但是并查集比较难求线段交，所以我们可以用线段树来实现。

然后画图找规律可以发现，整张图的联通块个数就可以表示成交点个数加上联通块个数减去线段个数。

接下来唯一麻烦的就是如何求交点，这个可以直接扫描线轻松地解决。

时间复杂度 $O(n\log n)$。

代码可以去我的博客查看：[第13回日本情報オリンピック　本選 E - 切り取り線 （Cutting） 题解
](https://www.cnblogs.com/withhope/p/13854824.html)

---

## 作者：Ebola (赞：0)

一种基于**平面图欧拉定理**的不同做法。

假设你做过 **[CF1401E](https://codeforces.com/problemset/problem/1401/E)**，本题与它不同的地方是：本题不要求线段的一端贴着边。CF1401E 的做法是这样的：

- 内部交点数 $+$ 贯穿线段数 $+1$。

实际上也可以这样解释：

- 把边界交点也视为交点，求：交点总数 $-$ 线段总数 $+1$。

如果推广到本题，那就是：

- 交点总数 $-$ 线段总数 $+$ 线段连通块个数

  注意，如果两条线段都连着边界，也算它们连通！

![](https://cdn.luogu.com.cn/upload/image_hosting/miwu59b8.png)

> 注：上述结论可以使用平面图欧拉公式 $V-E+F=\omega+1$ 来证明。其中 $V$ 是点数、$E$ 是边数、$F$ 是面数（即平面被割成了几个区域）、$\omega$ 是图的连通块数。

交点我们已经会求了，考虑求线段连通块个数。

扫描线。从左往右扫，以纵坐标维护一棵线段树：

- 碰到水平线左端点，就把它加入线段树里的 $O(\log)$ 个区间。
- 碰到水平线右端点，就相应地删除。
- 碰到竖直线就在线段树里找到 $O(\log)$ 个区间，把它和之前加入了这些区间的水平线连起来。

这样看来，线段树的每个节点要有一个 `vector`，那碰到竖直线使枚举 `vector` 里的所有水平边，岂不是 T 飞？

事实上，在发生一次连边之后，你只需要保存 `vector` 里右端点最大的那个边即可。

> 解释：首先，`vector` 里这些水平边已经通过竖直边连起来了。其次，如果接下来再碰到竖直边，要和这个区间连边，那 `vector` 里的所有水平边都在他的纵坐标范围内，所以把它和随便的一条水平边连起来就 ok 了。保留最后被删除的水平边即可。

---

