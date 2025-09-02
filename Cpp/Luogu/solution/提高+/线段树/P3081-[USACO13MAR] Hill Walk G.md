# [USACO13MAR] Hill Walk G

## 题目描述

There are N hills (1 <= N <= 100,000). Each hill takes the form of a line segment from (x1, y1) to (x2, y2) where x1 < x2 and y1 < y2. None of these segments intersect or touch, even at their endpoints, and furthermore, the first hill satisfies (x1, y1) = (0,0).

Bessie the cow starts at (0,0) on the first hill. Whenever Bessie is on a hill, she climbs up until she reaches the end. Then she jumps off the edge. If she lands on another hill, she continues walking on that hill; otherwise, she falls very far until she lands safely on a cushion of pillows at y = -infinity.  Each hill (x1, y1) -> (x2, y2) should be regarded as containing the point (x1, y1) but not containing the point (x2, y2), so that Bessie will land on the hill if she falls on it from above at a position with x = x1, but she will not land on the hill if she falls on it from above at x = x2.

Please count the total number of hills that Bessie touches at some point during her walk.

有 $N(1 \le N \le 10 ^ 5)$座小山，每座山所占的区域用直线 $(x1, y1)$ 到 $(x2, y2)$ 来表示（$x1 < x2$ 并且 $y1 < y2$）。也就是说这些山用笛卡尔坐标系里的线段来表示，这些用于表示小山的线段都没有任何交点，第一座山的一端位于 $(x1, y1) = (0,0)$。


贝西从 $(0,0)$ 开始在第一座山上漫步，一旦贝西到了一座山，她会一直走到该山的终点，这时，她会从边缘处起跳，如果她降落到另一座山上，她会继续在新的山上漫步。贝西起跳后沿 $y$ 轴方向下落，如果贝西不能降落到一座山上，她会一直下落，直到到达 $y$ 轴的负无穷大位置（$y = -\infin$）。


每座用线段表示的山 $(x1, y1) \to (x2, y2)$ 包含 $(x1, y1)$ 这个点，但不包含 $(x2, y2)$，请计算出贝西总共在多少座山上漫步了。


## 说明/提示

There are four hills.  The first hill runs from (0,0) to (5,6), and so on.


Bessie walks on hills #1, #4, and finally #3.


## 样例 #1

### 输入

```
4 
0 0 5 6 
1 0 2 1 
7 2 8 5 
3 0 7 7 
```

### 输出

```
3 
```

# 题解

## 作者：w36557658 (赞：5)

先推销一下自己的博客：http://www.cnblogs.com/luyouqi233/p/8405865.html

首先说一下解题思路：我们走一遍线段，并且在掉落的时候以O(logn)的速度查找到你应当掉落在那个线段上。那么复杂度就是O(nlogn)了。

一个显然的思路，我们记录当前走在了哪个线段，用set维护接下来**可能**走的线段，取出我们所要的线段即可。

（PS：“可能”指你所在的坐标的x在某个线段的x区间内）

走在哪个线段没有难度，开个变量记录一下即可。

找接下来可能走的线段（并且及时剔除掉走过/不能走到的线段），扫描线即可解决。

那么这题的难点就在于我们如何排序（也就是set的比较方法）来取出我们所要的线段。

先画个图感性理解一下，黑点是我们所在的位置，编号就是我们排好序之后的编号。

![](https://cdn.luogu.com.cn/upload/pic/13839.png)

（我们所在的位置是3，显然只需要跳到3-1=2的编号的那条边，我们就实现了走的动作。）

 设比较的两条线段a,b，则分为两种情况：

1.ax2<bx2（eg：a=5,b=4或a=2,b=4）：

 我们把a的右端点和b的左端点连线，显然发现这条线段将这两条线划分开来，上面的线编号大，下面的线编号小。

 2.ax2>bx2（eg：a=1,b=3或a=4,b=3）：

 同1的思路，其实只是把a和b颠倒而已。

 我们可以通过斜率来比较两条线的位置。

（PPS：貌似可以两条线分别取一个不同方向的点连线貌似就可以，不必非得按照题解的连线方法）

（PPPS：可能有这种情况（举一个1的例子）：

![](https://cdn.luogu.com.cn/upload/pic/13842.png)

这时候我们只需要平移一下就好了。


![](https://cdn.luogu.com.cn/upload/pic/13840.png)

所以用斜率判断是最准确的。）

---

## 作者：灵乌路空 (赞：4)

原题面：[Luogu](https://www.luogu.com.cn/problem/P3081)

知识点：扫描线，李超树。

被离散化鲨了哈哈，一个人交了三页半，感谢大神的提交记录救我一命呜呜：[https://www.luogu.com.cn/record/123948215](https://www.luogu.com.cn/record/123948215)。

### 简述

>给定平面坐标系上的 $n$ 条线段，每条线段的两个端点为 $(x_1, y_1)$，$(x_2, y_2)$ 且满足 $x_1<x_2$，$y_1<y_2$，且有且仅有第一条线段满足 $(x_1, y_1) = (0,0)$。  
>每条线段都代表一座山。初始时一个人位于 $(0, 0)$ 并在第一座山开始向右攀登，最右端 $(x_2, y_2)$ 是山的边缘，他会在边缘进行一个信仰之跃向下跳到横坐标为 $x_2$ 位置并尝试降落到其他山上的非边缘位置，若降落到另一座山上则会继续在新的山上进行攀登，否则就摔似了（悲  
>求这个人似之前攀登过了多少座山。  
>$1\le n\le 10^5$，$0\le x_1<x_2\le 10^9$，$0\le y_1<y_2\le 10^9$。  
>1S，125MB。

### 分析

初始时位于第一条线段上，考虑模拟攀登的过程，在边缘向下跳到最高的山上等价于找与 $x = x_2$ 交点纵坐标最大的线段，考虑使用李超树加入寻找后继的过程。但是要保证要找的线段可以降落到达，而李超树不支持删除操作，不能在一开始就将所有线段插入并仅在要查询降落到的下一座山时将不能到达的删除，则考虑使用扫描线在查询时先仅将对此时有贡献的插入。

设当前位于的线段为 $(x_1, y_1)\rightarrow (x_2, y_2)$，则可能成为当前线段后继的线段 $(x_1', y_1')\rightarrow (x_2', y_2')$ 一定满足 $x_1'\le x_1$，$x_2'>x_2$ 且在 $x=x_2$ 处交点坐标不大于 $y_2$。如果先将所有线段按左端点 $x_1'$ 进行排序然后依次枚举，则这些线段一定是连续的一段区间，考虑按照上述限制枚举这段区间并将每条线段插入到李超树区间 $[x_1', x_2'-1]$ 中，查询 $x=x_2$ 处即可得到后继，经过的山数量加一，若不存在则停止。

横坐标范围比较大注意先离散化再插入到李超树中。但需要注意如果仅把所有线段的横坐标离散化并**直接替换**原线段，可能会导致新的线段间出现相交的情况，因为只离散化横坐标后计算线段的斜率，相当于直接把一段很长的区间缩没了，这么搞显然不行。我的解决方案是仅在将线段**插入**李超树使用**离散化后的横坐标**表示区间，在计算线段某点的值时仍使用**原始的横坐标**。

总时间复杂度 $O(n\log^2 n)$ 级别。

### 代码

```cpp
//
/*
By:Luckyblock
*/
#include <bits/stdc++.h>
#define LL long long
#define pr std::pair
#define mp std::make_pair
const int kN = 1e5 + 10;
const int kX = kN << 2;
const double eps = 1e-9;
const double kInf = 1e18 + 2077;
//=============================================================
struct Line {
  LL x1, y1, x2, y2;
  int l, r, p;
  double k, b;
} l[kN];
int n, linenum;
int datanum, data[kN << 2];
int now, nowp, nowh, ans;
//=============================================================
inline int read() {
  int f = 1, w = 0; char ch = getchar();
  for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -1;
  for (; isdigit(ch); ch = getchar()) w = (w << 3) + (w << 1) + (ch ^ '0'); 
  return f * w;
}
int cmp(double x_, double y_) {
  if (x_ - y_ > eps) return 1;
  if (y_ - x_ > eps) return -1;
  return 0;
}
double calc(int id_, int x_) {
  double ret = l[id_].b + l[id_].k * x_;
  return ret;
}
void Add(int x0_, int y0_, int x1_, int y1_) {
  ++ linenum;
  if (x0_ == x1_) {
    l[linenum].k = 0;
    l[linenum].b = 1.0 * std::min(y0_, y1_);
  } else{
    l[linenum].k = 1.0 * (y1_ - y0_) / (x1_ - x0_);
    l[linenum].b = y0_ - l[linenum].k * x0_;
  }
}
bool cmp1(Line fir_, Line sec_) {
  if (fir_.x1 != sec_.x1) return fir_.x1 < sec_.x1;
  return fir_.y2 > sec_.y2;
}
namespace LSeg {
  #define ls (now_<<1)
  #define rs (now_<<1|1)
  #define mid ((L_+R_)>>1)
  const int kNode = kX << 3;
  int t[kNode];
  void Update(int now_, int L_, int R_, int u_) {
    int& v_ = t[now_];
    int bmid = cmp(calc(u_, data[mid]), calc(v_, data[mid]));
    if (bmid == 1 || (!bmid && u_ < v_)) std::swap(u_, v_);
    int bl = cmp(calc(u_, data[L_]), calc(v_, data[L_]));
    int br = cmp(calc(u_, data[R_]), calc(v_, data[R_]));
    if (bl == 1 || (!bl && u_ < v_)) Update(ls, L_, mid, u_);
    if (br == 1 || (!br && u_ < v_)) Update(rs, mid + 1, R_, u_);
  }
  void Modify(int now_, int L_, int R_, int l_, int r_, int u_) {
    if (l_ <= L_ && R_ <= r_) {
      Update(now_, L_, R_, u_);
      return ;
    }
    if (l_ <= mid) Modify(ls, L_, mid, l_, r_, u_);
    if (r_ > mid) Modify(rs, mid + 1, R_, l_, r_, u_);
  }
  pr <double, int> pmax(pr <double, int> x_, pr <double, int> y_) {
    if (cmp(x_.first, y_.first) == -1) return y_;
    if (cmp(x_.first, y_.first) == 1) return x_; 
    return x_.second < y_.second ? x_ : y_;
  }
  pr <double, int> Query(int now_, int L_, int R_, int pos_) {
    if (R_ < pos_ || pos_ < L_) return {-kInf, 0};
    double val_ = calc(t[now_], data[pos_]);
    if (L_ == R_) return mp(val_, t[now_]);
    return pmax(mp(val_, t[now_]), pmax(Query(ls, L_, mid, pos_), 
                                        Query(rs, mid + 1, R_, pos_)));
  }
  #undef ls
  #undef rs
  #undef mid
}
void Init() {
  n = read();
  for (int i = 1; i <= n; ++ i) {
    l[i].x1 = read(), l[i].y1 = read();
    l[i].x2 = read(), l[i].y2 = read();
    l[i].l = l[i].x1, l[i].p = l[i].x2, l[i].r = l[i].x2 - 1;
    data[i] = l[i].x1, data[i + n] = l[i].x2;
    data[i + 2 * n] = l[i].r;
  }
  std::sort(data + 1, data + 3 * n + 1);
  datanum = std::unique(data + 1, data + 3 * n + 1) - data - 1;
  for (int i = 1; i <= n; ++ i) {
    l[i].l = std::lower_bound(data + 1, data + datanum + 1, l[i].l) - data;
    l[i].r = std::lower_bound(data + 1, data + datanum + 1, l[i].r) - data;
    l[i].p = std::lower_bound(data + 1, data + datanum + 1, l[i].p) - data;
  }
  std::sort(l + 2, l + n + 1, cmp1);
  for (int i = 1; i <= n; ++ i) {
    Add(l[i].x1, l[i].y1, l[i].x2, l[i].y2);
  }

  l[0].b = -kInf;
}
//=============================================================
int main() {
  // freopen("3.txt", "r", stdin);
  // freopen("2.txt", "r", stdin);
  Init();
  ans = 1;
  now = 1, nowp = l[1].x2, nowh = l[1].y2;
  
  for (int i = 2; ; ) {
    for (; i <= n; ++ i) {
      if (l[i].x1 > nowp) break;
      if (l[i].x2 <= nowp || calc(i, nowp) > nowh) continue;
      LSeg::Modify(1, 1, datanum, l[i].l, l[i].r, i);
    }
    int ret = LSeg::Query(1, 1, datanum, l[now].p).second;
    if (!ret) break;
    ++ ans;
    now = ret, nowp = l[now].x2, nowh = l[now].y2;
  }
  printf("%d\n", ans);
  return 0;
}
```


---

## 作者：Seauy (赞：3)

~~不知道大家接受不接受这个又差又难写但想起来简单的方法~~

发现问题难以转换，考虑直接模拟走的过程，发现如果暴力找那座山会接住我每次是 $ O(n) $ 的，走 $ O(n) $ 次就是 $ O(n^2) $ 的

我们只要考虑加快寻找下一座山的复杂度就行了

# 1. 思路

如果 Bessie 要走到下一座山，肯定是从山顶垂直向下寻找最高的山

从高处往下看，求最高的线段，令人想到了李超线段树

那不对啊，会有在头顶上的山挡住李超的视线啊，而那座山却不是 Bessie 能到达的啊

那就把看到的不符合的山（在 Bessie 头顶上的）从线段树里删掉呗。这样做不会错，因为在头顶上的山不管怎样都不可能到达，可以删掉不管它们

网上一查，李超树不支持删除，~~炸胡~~

稳住，其实是可以支持删除的蛤。原版李超树不能支持删除是因为会把完全没有优势的线段直接踢掉，就找不回来了，但是我们如果把打败它的线段又给删除了，它就又有可能复出了

那么要被踢掉的时候先把它留住，放在堆里，等某个线段头顶上所有比它牛逼的线段全没了，它就又成老大了

分析复杂度，插入操作原来两只 log，加个堆变成 $ O(\log^3 n) $ ~~继续炸胡~~

~~稳住乃成功之母~~，虽然在一般情况下这么改进确实会炸胡，但这道题的线段们都有个特性，**互相之间都没交点**

那么同一区间内的线段就不用继续下放了，变成了普通的线段树区间修改操作，加个堆 $ O(\log^2 n) $，总复杂度 $ O(n \log^2 n) $ ~~反正能过~~

算仔细点，如果设值域是 $ v $，复杂度当是 $ O(n\log n \log v) $，但 $ v  $ 与 $ n^2 $ 同阶，取个对数 $ O(\log v)=O(\log n) $ 只是常数大了点

删除操作做个懒删除标记就行了

# 2. 优化

动态开点李超线段树+堆，每个结点都放个优先队列有1e7 个， MLE 上天成了 67 分

~~稳住稳住~~区区 MLE 算啥，卡空间奇招上！

### (1) 手写堆

STL 又拖我后腿，换成手写的就行了~~远古科技~~

难写的地方在于开的若干堆要共用一个数组，那就先预算一下每个区间要开多大，存下来分配位置就行了

~~码量++~~，这样就能 75 了~~艹才多过一个点~~

### (2) 简化结构体

我是这么定义线段结构体的

```cpp
struct Line
{
	double k,b;//直线解析式
	int L,R,D,U;//两端点
	int ID;//线段编号
	double sTd;//存进堆里用来比较的参数
};
```

发现放进堆里两端点坐标是不用的

那就搞个新类型把它们删掉

```cpp
struct sim
{
	double k,b,sTd;
	int ID;
};
```

一下子 92 分

### (3) 离散化

动态开点搞的结点数太多了，离散化后直接降了十倍

然后就 A 了

反正吸氧总时限跑进 1s 了，空间比人家大两倍

# 3. 代码

原来动态开点的写法懒得改了，就当一个小剪枝吧……

```cpp
#include<bits/stdc++.h>
using namespace std;

const int MAXN=1e5;
const int Size=1e9;
const int Trsz=2e6;

struct sim
{
	double k,b,sTd;
	int ID;
	bool operator < (const sim &ob) const
	{return sTd<ob.sTd;}
	bool operator > (const sim &ob) const
	{return sTd>ob.sTd;}
}Heap[Trsz+5];

struct Line
{
	double k,b;
	int L,R,D,U;
	int ID;
	double sTd;
	void Scan()
	{
		scanf("%d %d %d %d",&L,&D,&R,&U);
		/*
			D=kL+b
			U=kR+b
		*/
		k=(double)(U-D)/(R-L);
		b=D-k*L;
	}
	void Print() {cout<<k<<' '<<b<<endl;}
	double y(int x) {return k*x+b;}
	bool operator < (const Line &ob) const
	{return sTd<ob.sTd;}
	bool operator > (const Line &ob) const
	{return sTd>ob.sTd;}
	sim Zip() {return sim{k,b,sTd,ID};}
}Hill[MAXN+5];

int n,ans;
bool Passed[MAXN+5];
int pre[Trsz+5],Hsize[Trsz+5];
int Son[Trsz+5][2],num=1;
int discre[2*MAXN+5],Tail;

int HeapNum(int x,int y)
{return pre[x-1]+y;}

void Up(int x,int y)
{
	while(y>1)
	{
		if(Heap[HeapNum(x,y)]>Heap[HeapNum(x,y>>1)])
		{
			swap(Heap[HeapNum(x,y)],Heap[HeapNum(x,y>>1)]);
			y>>=1;
		}
		else break;
	}
}

void Push(int x,Line v)
{
	++Hsize[x];
	Heap[HeapNum(x,Hsize[x])]=v.Zip();
	Up(x,Hsize[x]);
}

void Down(int x,int y)
{
	for(int s=y<<1;s<=Hsize[x];)
	{
		if(s<Hsize[x] && Heap[HeapNum(x,s)]<Heap[HeapNum(x,s+1)]) ++s;
		if(Heap[HeapNum(x,s)]>Heap[HeapNum(x,y)])
		{
			swap(Heap[HeapNum(x,s)],Heap[HeapNum(x,y)]);
			y=s;
			s=y<<1;
		}
		else break;
	}
}

bool Empty(int x) {return !Hsize[x];}
sim Top(int x) {return Heap[HeapNum(x,1)];}

int BEST(int x)
{
	if(Empty(x)) return 0;
	return Top(x).ID;
}

void Pop(int x)
{
	Heap[HeapNum(x,1)]=Heap[HeapNum(x,Hsize[x])];
	--Hsize[x];
	Down(x,1);
}

void POP(int x)
{
	while(!Empty(x))
		if(Passed[Top(x).ID]) Pop(x);
		else break;
}

void New(int now,bool t)
{
	if(Son[now][t]) return;
	Son[now][t]=++num;
}

void Plus(int now,int L,int R,int QL,int QR)
{
	if(QL<=L && R<=QR) {++Hsize[now];return;}
	int mid=(L+R)>>1;
	if(QR<=mid) New(now,0),Plus(Son[now][0],L,mid,QL,QR);
	else if(mid<QL) New(now,1),Plus(Son[now][1],mid+1,R,QL,QR);
	else
	{
		New(now,0),New(now,1);
		Plus(Son[now][0],L    ,mid,QL,QR);
		Plus(Son[now][1],mid+1,R  ,QL,QR);
	}
}

void Insert(int now,int L,int R,Line x,int dL,int dR)
{
	//printf("[%d,%d]\n",L,R);
	if(dL<=L && R<=dR)
	{
		POP(now);
		x.sTd=x.y(discre[L]);
		//printf("Push in Heap\n");
		Push(now,x);
		return;
	}
	int mid=(L+R)>>1;
	New(now,0),New(now,1);
	if(dR<=mid) Insert(Son[now][0],L,mid,x,dL,dR);
	else if(mid<dL) Insert(Son[now][1],mid+1,R,x,dL,dR);
	else
	{
		Insert(Son[now][0],L    ,mid,x,dL,dR);
		Insert(Son[now][1],mid+1,R  ,x,dL,dR);
	}
}

int Ask(int now,int L,int R,int x)
{
	if(!now) return 0;
	POP(now);
	if(L==R) return BEST(now);
	int mid=(L+R)>>1,cnt;
	if(x<=mid) cnt=Ask(Son[now][0],L,mid,x);
	else cnt=Ask(Son[now][1],mid+1,R,x);
	if(BEST(now)*cnt==0) return BEST(now)+cnt;
	if(Hill[BEST(now)].y(discre[x])>Hill[cnt].y(discre[x])) return BEST(now);
	return cnt;
}

int Search(int x)
{
	for(int L=1,R=Tail,mid;1;)
	{
		mid=(L+R)>>1;
		     if(discre[mid]==x) return mid;
		else if(discre[mid]<x) L=mid+1;
		else R=mid-1;
	}
	return 0;
}

int main()
{
	//freopen("P3081_3.in","r",stdin);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		Hill[i].Scan();
		Hill[i].ID=i;
		//Hill[i].Print();
		discre[++Tail]=Hill[i].L;
		discre[++Tail]=Hill[i].R;
	}
	sort(discre+1,discre+Tail+1);
	Tail=unique(discre+1,discre+Tail+1)-discre-1;
	for(int i=1;i<=n;i++) Plus(1,1,Tail,Search(Hill[i].L),Search(Hill[i].R));
	for(int i=1;i<=num;i++)
	{
		pre[i]=pre[i-1]+Hsize[i];
		Hsize[i]=0;
	}
	for(int i=1;i<=n;i++) Insert(1,1,Tail,Hill[i],Search(Hill[i].L),Search(Hill[i].R));
	for(int now=1,nxt;now;now=nxt)
	{
		++ans;
		//printf("now at: %d\n",now);
		while(1)
		{
			nxt=Ask(1,1,Tail,Search(Hill[now].R));
			//printf("try: %d\n",nxt);
			if(!nxt) break;
			if(Hill[nxt].y(Hill[now].R)<=Hill[now].U)
			{
				if(Hill[now].R==Hill[nxt].R) {Passed[nxt]=1;continue;}
				break;
			}
			Passed[nxt]=1;
		}
	}
	printf("%d\n",ans);
	//printf("%d %d\n",pre[n],num);
	return 0;
}
/*
2
0 0 1 1
1 1 2 2

4 
0 0 5 6 
1 0 2 1 
7 2 8 5 
3 0 7 7
*/
```


---

## 作者：Lyrella (赞：2)

# 题解

我们从 $(0,0)$ 开始走。如果直接建李超线段树那么当我们想要取下面部分的线段时就出问题了，所以我们就需要一个支持删除的东西维护它。于是考虑平衡树。

然后走的时候我们是横坐标排序，所以现在就只用考虑纵坐标。在每次走到一个线段的终点时我们需要看可行区间中比当前线段低一层的是谁。然后就想到把线段全部丢到平衡树里面，通过某种排序方使这些线段从高到低排好序。

那么如何判断两个线段的高低呢？我们通过下图来分析。

![](https://cdn.luogu.com.cn/upload/image_hosting/h5bfp7su.png)

如果我要比较上面两条线段，我首先会去看它们右端点的位置。显然后者更靠右，然后我们把它们的右端点连接起来（如图红线）。如果前者更高（如图），那么**红线的斜率就会小于后面那条线段的斜率**，否则就会是图片下半部分的情况。于是我们比较线段之间的优先级时就可以先比较右端点再比较斜率了。

```cpp
bool operator <(line x, line y){
	if(x.c < y.c)return 1ll * (y.c - x.c) * (y.d - y.b) < 1ll * (y.d - x.d) * (y.c - y.a);
	return 1ll * (x.c - y.c) * (x.d - x.b) > 1ll * (x.c - x.a) * (x.d - y.d);
}
```

注意如果直接用除法可能精度会炸。

然后就从左往右扫一遍，把线段该加入平衡树的就加进来，该删的就删掉。如果删掉的是当前所在的区间就在平衡树里查找一个比它低一层的线段然后更新答案。实际实现时可以用 ```set``` 代替平衡树。

# 代码

```cpp
int main(){
	rd(n);
	for(int i = 1; i <= n; ++i)rd(l[i].a, l[i].b, l[i].c, l[i].d), p[i - 1 << 1 | 1] = {l[i].a, l[i].b, i}, p[i << 1] = {l[i].c, l[i].d, i}, l[i].id = i;
	s.ins(l[1]); sort(p + 1, p + 1 + (n << 1));
	for(int i = 2; i <= (n << 1); ++i)
		if(p[i].x == l[p[i].id].a)s.ins(l[p[i].id]);
		else if(p[i].id == cur){
			set < line > :: iterator it = s.find(l[p[i].id]);
			if(it == s.begin())break;
			++ans; it--;
			cur = it -> id;
		}
		else s.del(l[p[i].id]);
	wt(ans);
	return 0;
}
```

---

## 作者：Prms_Prmt (赞：2)

## 题意

平面上，有 $ n $ 条互不相交的线段 $ ( a , b ) \rightarrow ( p , q ),a < p, b < q $，$ a , b , c , d $ 都是整数；指定起点 $ (0 , 0) $，每此跳到从当前线段的 $ ( p , q )$ ，从 $ ( p , q ) $ 向下引铅垂射线，当前线段变为第一条与射线相交的线段；若无线段与之相交，则结束；统计结束前经过了多少条线段。


## 题解

考虑直接模拟 $ \mathcal O ( n ^ 2 ) $，可以用以下方法优化：

平衡树维护纵坐标可行性，扫描线维护横坐标可行性，时间复杂度 $ \mathcal O ( n \log n ) $。

### 纵坐标


线段间都不相交，如何比较“谁高谁低”？

- 当 $ p_2 = p_1 $：

  这个好办，直接比较 $q_1,q_2$；

- 当 $ p_2 > p_1 $：

  交换两条线段，按下一类讨论；

- 当 $ p_2 < p_1 $：

  如图：


  ![请联系作者修图](https://cdn.luogu.com.cn/upload/image_hosting/9ia8sxfg.png)

将黄线斜率和黑线斜率比较，可以确定红线/绿线与黑线的“纵坐标”大小关系。

这实际上是平衡树的排序函数，我们需要查找当前线段的合法前驱。

下面讨论如何保证平衡树内的线段合法。

### 横坐标

令当前线段编号为 $ v $；

#### 排序

扫描线，线段拆点按 $ x $ 升序为第一关键字，$ y $ 升序为第二关键字排序。

按 $ x $ 排序，保证平衡树内没有 $ \exists i \in \text{set}, a_i > p_v $；【$ A $】

按 $ y $ 排序，保证平衡树不遗漏 $ \forall i \le n, a_i = p_v \land b_i \le q_v $。【$ B $】

#### 过程

- 当前点是某条线段的起始点：
  
  将该线段加入平衡树。
  
- 当前点是某条线段的终点：
  
  - 不是当前线段的终点：
  
    将该线段从平衡树中删除。（保证平衡树内没有 $ \exists i \in \text{set}, p_i < p_v $）【$ C $】
  
  - 是当前线段的终点：
  
  	 查找此时平衡树内的前驱：
     
     1. 存在，答案加一，把当前线段改为前驱，删除当前线段；
     
     2. 不存在，结束。

可以证明，【$ A, B, C $】是线段横坐标合法的充分条件。

## CODE

讲的很清楚了，就不放注释了。


```cpp
#include <bits/stdc++.h>
using namespace std;

const int N=3e5;
int n;

struct seg{
	int a,b,p,q,ind;
	void scan(int i){
		scanf("%d%d%d%d",&a,&b,&p,&q);
		ind=i;
	}
	bool operator<(const seg &s) const{
		if(p<s.p)
			return 1ll*(s.p-p)*(s.q-s.b)<1ll*(s.p-s.a)*(s.q-q);
		else
			return 1ll*(p-s.p)*(q-b)>1ll*(p-a)*(q-s.q);
	}
}s[N];

struct pnt{
	int a,b,sg;
	bool operator<(const pnt &s) const{
		if(a==s.a) return b<s.b;
		return a<s.a;
	}
}p[N];

int main() {
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		s[i].scan(i),p[i*2-1]={s[i].a,s[i].b,i},p[i*2]={s[i].p,s[i].q,i};
	set<seg> t;
	int cur=1,ans=1;
	t.insert(s[1]);
	sort(p+1,p+2*n+1);
	for(int i=2;i<=2*n;i++){
		pnt u=p[i];
		if(p[i].a==s[p[i].sg].a) //is start
			t.insert(s[p[i].sg]);
		else // is end
			if(u.sg==cur) //is current end
			{
				auto it=t.find(s[p[i].sg]);
				if(it==t.begin()) break;
				auto _it=it;
				--_it;
				t.erase(it);
				cur=_it->ind;
				ans++;
			}
			else
				t.erase(s[p[i].sg]);//delete
	}
	cout<<ans;
	return 0;
}
```

参考：[uscao.org](http://usaco.org/current/data/sol_hillwalk.html)

---

## 作者：hzoi_Shadow (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/P3081)

# 前置知识

[李超线段树](https://oi-wiki.org/ds/li-chao-tree/) | [扫描线](https://oi-wiki.org/geometry/scanning/)

# 解法

自边缘处起跳等价于找到与 $x=x_{2}$ 相交的直线中最大的 $y \le y_{2}$。普通的李超线段树不支持删除操作，直接套用貌似很难处理。

观察到若能从 $(x_{1},y_{1}) \to (x_{2},y_{2})$ 跳跃至 $(x_{1}',y_{1}') \to (x_{2}',y_{2}')$，则一定有 $x_{1}' \le x_{2}<x_{2}'$。以 $x_{1}$ 排序后顺次扫描线加入即可。

需要离散化和动态开点，注意计算函数值的时候要拿原值来算。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
#define ull unsigned long long
#define sort stable_sort 
#define endl '\n'
const double eps=1e-9,inf=1e18;
struct node
{
	int x1,y1,x2,y2,l,r,pos;
	bool operator < (const node &another) const
	{
		return x1<another.x1;
	}
}a[100010];
struct line
{	
	double k,b;
}li[100010];
int b[300010];
double f(int id,double x)
{
	return (id==0)?-inf:li[id].k*x+li[id].b;
}
bool cmp(int a,int b,int x)
{
	if(f(a,x)-f(b,x)>eps)  return true;
	if(f(b,x)-f(a,x)>eps)  return false;
	return a<b;
}
int sx_max(int a,int b,int x)
{
	return cmp(a,b,x)==true?a:b;
}
struct LiChao_Tree
{
	struct SegmentTree
	{
		int id;
	}tree[1200010];
	#define lson(rt) (rt<<1)
	#define rson(rt) (rt<<1|1)
	void add(int rt,int l,int r,int id)
	{
		int mid=(l+r)/2;
		if(cmp(tree[rt].id,id,b[mid])==false)
		{
			swap(tree[rt].id,id);
		}
		if(l==r)
		{
			return;
		}
		if(cmp(tree[rt].id,id,b[l])==false)
		{
			add(lson(rt),l,mid,id);
		}
		if(cmp(tree[rt].id,id,b[r])==false)
		{
			add(rson(rt),mid+1,r,id);
		}
	}
	void update(int rt,int l,int r,int x,int y,int id)
	{
		if(x<=l&&r<=y)
		{
			add(rt,l,r,id);
			return;
		}
		int mid=(l+r)/2;
		if(x<=mid)
		{
			update(lson(rt),l,mid,x,y,id);
		}
		if(y>mid)
		{
			update(rson(rt),mid+1,r,x,y,id);
		}
	}
	int query(int rt,int l,int r,int pos)
	{
		if(l==r)
		{
			return tree[rt].id;
		}
		int mid=(l+r)/2;
		if(pos<=mid)
		{
			return sx_max(tree[rt].id,query(lson(rt),l,mid,pos),b[pos]);
		}
		else
		{
			return sx_max(tree[rt].id,query(rson(rt),mid+1,r,pos),b[pos]);
		}
	}
}T;
int main()
{
// #define Isaac
#ifdef Isaac
	freopen("in.in","r",stdin);
	freopen("out.out","w",stdout);
#endif
	int n,ans=0,i,j;
	cin>>n;
	for(i=1;i<=n;i++)
	{
		cin>>a[i].x1>>a[i].y1>>a[i].x2>>a[i].y2;
		b[++b[0]]=a[i].l=a[i].x1;
		b[++b[0]]=a[i].r=a[i].x2-1;
		b[++b[0]]=a[i].pos=a[i].x2;
	}
	sort(b+1,b+1+b[0]);
	b[0]=unique(b+1,b+1+b[0])-(b+1);
	for(i=1;i<=n;i++)
	{
		a[i].l=lower_bound(b+1,b+1+b[0],a[i].l)-b;
		a[i].r=lower_bound(b+1,b+1+b[0],a[i].r)-b;
		a[i].pos=lower_bound(b+1,b+1+b[0],a[i].pos)-b;
	}
	sort(a+2,a+1+n);
	for(i=1;i<=n;i++)
	{
		li[i].k=1.0*(a[i].y2-a[i].y1)/(a[i].x2-a[i].x1);
		li[i].b=a[i].y1-li[i].k*a[i].x1;
	}	
	for(i=1,j=2;i!=0;i=T.query(1,1,b[0],a[i].pos))
	{
		ans++;
		for(;j<=n&&a[j].x1<=a[i].x2;j++)
		{
			if(a[j].x2>a[i].x2&&f(j,a[i].x2)<=a[i].y2)
			{
				T.update(1,1,b[0],a[j].l,a[j].r,j);
			}
		}
	}
	cout<<ans<<endl;
	return 0;
}
```

---

