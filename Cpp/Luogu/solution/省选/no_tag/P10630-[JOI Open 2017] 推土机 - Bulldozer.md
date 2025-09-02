# [JOI Open 2017] 推土机 / Bulldozer

## 题目描述

**译自 [JOI Open 2017](https://contests.ioi-jp.org/open-2017/index.html) T2 「ブルドーザー / Bulldozer」**

平面上有 $N$ 个点，点 $i\:(1≤i≤N)$ 位于 $(X_i, Y_i)$，点 $i\:(1≤i≤N)$ 的权值为非零整数 $W_i$（可能为负数）。  
在平面上画两条平行线，所得的总价值为平行线之间（压线也算）所有点的权值之和。求总价值至多不超过多少。

## 说明/提示

**样例解释 1**

![](https://cdn.luogu.com.cn/upload/image_hosting/rk2miemg.png)

选择点 $2, 3, 4, 5$。

**样例解释 2**

注意，点 $1,2,3$ 共线。点 $4,5,6$ 共线。

**样例解释 3**

这组样例中没有三点共线。选择的平行线一条过点 $1,2$，另一条过点 $3,4$。

#### 数据范围

所有输入数据都满足以下条件。

 $1≤N≤2000, |X_i|,|Y_i|≤10^9,1 ≤|W_i|≤10^9(1≤i≤N)$ 。$(X_i,Y_i)≠(X_j,Y_j)\:(1≤i<j≤N)$ 。

|子任务|分值|$N≤100$|无三点共线|设 $L$ 是在平面上通过两个不同点的一条线，$L'$ 是在平面上另一条通过两个不同点的线，那么 $L$ 和 $L'$ **不**相互平行|其他条件|
|:---------:|:------------:|:-------------:|:---------------:|:-:|:------------:|
|$1$     |$5$    |√            |×                 |×|所有点都在 $x$ 轴上|
|$2$     |$20$  |√          |√               |√|无|
|$3$     |$35$  |×          |√                |√|无|
|$4$     |$20$  |×          |√                |×|无|
|$5$     |$20$  |×          |×                |×|无|

## 样例 #1

### 输入

```
5
-5 5 -2
2 5 10
1 4 -2
4 -5 4
-2 2 7```

### 输出

```
19```

## 样例 #2

### 输入

```
6
0 0 6
1 0 -2
2 0 8
0 1 -2
1 1 5
2 1 -2```

### 输出

```
15```

## 样例 #3

### 输入

```
5
0 0 2
4 0 2
3 2 -1
1 2 2
1 1 -1```

### 输出

```
5```

## 样例 #4

### 输入

```
2
0 0 -1
1 0 -1```

### 输出

```
0```

# 题解

## 作者：Autumn_Rain (赞：1)

前置知识：[小白逛公园](https://www.luogu.com.cn/problem/P4513)。

样例解释：[样例说明]( https://www.luogu.com.cn/paste/f5ftyv0q)。



---



### 思路：

- 假设平行线的斜率已确定。从上往下扫，把每个点按扫到的时间顺序存入线段树，答案等价于求最大子段和。

- 先把两平行线重合穿过一个给定点，两平行线重合但什么也不穿过的情况算上。

- 有这样一个集合 $S$，包含了以下两种直线。

  1. 一条直线穿过两个给定点。

  2. 只穿过一个给定点。


- 根据样例解释，可以发现除去特判的情况外，答案一定可以由集合 $S$ 中的两条平行线围成。因此枚举两两点预处理直线斜率。


- 当平行线斜率改变时，两点在线段树上的顺序（即被平行线扫到的先后顺序）才会变。两点间的顺序只变一次，故总变化次数是 $\mathcal {O(n^2)}$ 的。

- 因此我们将平行线进行极角排序 $^{\clubsuit} $。然后计算过程中不停交换两两点的位置，这样的排序方式可以保证不重不漏，两点间的顺序刚好变一次（你可以将字母 $A,B,C,\cdots$ 围成一圈，两两交换，看看是不是不重不漏）。

极角排序 $^{\clubsuit} $：把平面上的一些点按照一选定的中心点（不一定是给定点）排成顺（逆）时针。[这篇(详细)](https://lnrbhaw.github.io/2018/12/15/%E6%B5%85%E8%B0%88%E6%9E%81%E8%A7%92%E6%8E%92%E5%BA%8F/) 和 [这篇(简洁)](https://blog.csdn.net/weixin_30650039/article/details/98717187) 都值得一看。

时间复杂度：$\mathcal{O(n^{2}\log n)}$。

---



### 代码中变量及函数意义的解释：

代码：[CODE](https://www.luogu.com.cn/paste/2fecyclb)。

- 结构体 ```point```：保存一个点的横纵坐标。

- 数组 ```p```：当前点在原序列（输入序列）中是第几个。

- 结构体 ```a```：输入的点集，$p,w$ 分别维护坐标、权值。

- 结构体 ```b```：$p$ 维护两点坐标的差，$x,y$ 代表 $p$ 中的坐标是序列 $a$ 中哪两点做差得来的（注意这里的 $x,y$ 是 $a$ **排序后**的下标）。

线段树维护最大子段和部分不加赘述，但是要注意更新时与 $0$ 取最大值，如果贡献为负数的话，我们当然可以不选这样的点。



---

以下是实现极角排序的函数，学习向量后会更加便于理解。

- 函数 ```cmp```：把 $a$ 中的横坐标小的点排到前面，横坐标一样大就把纵坐标小的排到前面。

- 函数 ```k```：用于对极角排序而进行的计算。你可以理解为斜率比较函数。$k$ 值为负数时，前一条线斜率更大。$k$ 值为 $0$ 时，斜率一样大。$k$ 值为正数时，后一条线斜率更大。

- 函数 ```cmp2```：把所有两两点组成的直线按照斜率从小到大排序。一样大就把横坐标小的放前面，横坐标也一样就把纵坐标小的放前面。

如果你不明白为什么这样可以让直线按照斜率从小到大排序，请看[这里的一些补充说明](https://www.luogu.com.cn/paste/i9gac4tf)。

（这里很多排序是个性化的，你也可以按照其它顺序排）


---


常见错误：[调试请查看](https://www.luogu.com.cn/paste/fipdkllm)。


[本题解的 LaTex 可自取](https://www.luogu.com.cn/paste/3a0hlahb)。

---

## 作者：D2T1 (赞：1)

## JOI Open 2017 - 推土机

考虑答案斜率只有可能为给定点中两点连线斜率，以及这个斜率稍微偏一点点（如样例 3），所以预处理所有斜率并排序，维护一个数组表示以这个斜率从下往上扫到每一个点的顺序。那么答案就为这个数组每个时刻的最大子段和。

对于斜率需稍微偏一点点的情况，可以发现仍然对应的是数组中的某个子段；每个子段也都能找到一个给定斜率，所以做法是正确的。

对于每个点对，它们之间在数组中的先后关系一定至多两种且一定只会变化至多一次，故可以预处理出这一次变化时间，使用单点修改、查询最大子段和的线段树维护数组即可。

但是会有一个问题：若存在多点共线，不妨为 $A,B,C$ 共线，斜率扫过这一条线时数组中三点顺序会由 $A,B,C$ 变为 $C,B,A$。预处理的结果是在这一刻有三个先后关系变化：$AB,AC,BC$。问题就是这三个变化需要一定的顺序。

若以 $AB,AC,BC$ 的顺序变化，数组 $ABC$ 会变为 $CBA$；但若以 $AC,AB,BC$ 的顺序变化，数组 $ABC$ 会变为 $BAC$。

经过打表得知可以使得排列 rev 的变化顺序数量为 [A092238](https://oeis.org/A092238)，但不是本题重点。

可以证明若原排列为 $ABCD\cdots$，以 $AB,AC,AD,\cdots,BC,BD,\cdots,CD,\cdots$ 的顺序变化一定是正确的。所以只需在算法开始之前对点进行排序即可。

时间复杂度 $O(n^2\log n)$。

```cpp
//P10630
#include <bits/stdc++.h>
using namespace std;

const int N = 2010;
int n, x[N], y[N], w[N];
int cnt, pos[N];
map<int, int> mp;
vector<pair<int, int> > cg[N*N];
int tmp[N], tmpp[N];

typedef long long ll;
double p[N*N];
struct tree{
    ll am, lm, rm, sum;
} t[N*4];
void psu(tree &p, tree ls, tree rs){
    p.sum = ls.sum + rs.sum;
    p.lm = max(ls.lm, ls.sum + rs.lm);
    p.rm = max(rs.rm, rs.sum + ls.rm);
    p.am = max(ls.am, rs.am);
    p.am = max(p.am, ls.rm + rs.lm);
}
void add(int p, int l, int r, int x, int v){
    if(l == r){
        tmp[x] = p;
        t[p].sum = v;
        t[p].am = t[p].lm = t[p].rm = max(0, v);
    } else {
        int mid = l + r >> 1;
        if(x <= mid){
            add(p<<1, l, mid, x, v);
        } else {
            add(p<<1|1, mid+1, r, x, v);
        }
        psu(t[p], t[p<<1], t[p<<1|1]);
    }
}

ll ans = 0;

struct node{
    int x, y, w, id;
} a[N];

int st = 0;
bool cmp(node c, node d){
    double cc = c.y - c.x * p[st];
    double dd = d.y - d.x * p[st];
    return fabs(cc-dd) <= 1e-8 ? c.x < d.x : cc<dd;
}
bool cmq(node c, node d, int op){
    double cc = c.y - c.x * p[op];
    double dd = d.y - d.x * p[op];
    return fabs(cc-dd) <= 1e-8 ? c.x < d.x : cc<dd;
}

int main(){
    scanf("%d", &n);
    for(int i = 1; i <= n; ++ i){
        scanf("%d%d%d", &x[i], &y[i], &w[i]);
        a[i] = { x[i], y[i], w[i], i };
    }
    for(int i = 1; i <= n; ++ i){
        for(int j = i + 1; j <= n; ++ j){
            if(x[i] != x[j]){
                double sl = (y[j] - y[i]) * 1.0 / (x[j] - x[i]);
                p[++cnt] = sl;
            }
        }
    }
    sort(p + 1, p + cnt + 1);
    p[0] = p[1] - 1;
    int m = unique(p, p + cnt + 1) - p;
    sort(a + 1, a + n + 1, cmp);
    for(int i = 1; i <= n; ++ i){
        pos[a[i].id] = i;
    }
    for(int i = 1; i <= n; ++ i){
        for(int j = i + 1; j <= n; ++ j){
            if(a[i].x != a[j].x){
                double sl = (a[j].y - a[i].y) * 1.0 / (a[j].x - a[i].x);
                int ps = lower_bound(p, p + m + 1, sl) - p;
                cg[ps].push_back(make_pair(a[i].id, a[j].id));
            }   
        }
    }
    for(int i = 1; i <= n; ++ i){
        add(1, 1, n, pos[i], w[i]);
    }
    for(int i = 0; i <= m; ++ i){
        ans = max(ans, t[1].am);
        for(auto j : cg[i]){
            int x = j.first, y = j.second;
            add(1, 1, n, pos[x], w[y]);
            add(1, 1, n, pos[y], w[x]);
            swap(pos[x], pos[y]);
        }
    }
    ans = max(ans, t[1].am);
    printf("%lld\n", ans);
}
```

---

## 作者：masterhuang (赞：0)

> 平面上有 $N$ 个点，点 $i$ 位于 $(X_i, Y_i)$，权值为非零整数 $W_i$（可能为负数）。 
>
> 在平面上画**两条平行线**，所得的总价值为平行线之间（压线也算）所有点的权值之和。求总价值的最大值。
>
> $N\le 2000, |X_i|,|Y_i|,|W_i|\le 10^9,(X_i,Y_i)≠(X_j,Y_j)\:(i\neq j)$ 。

先考虑平行线的斜率，初步猜测为是两点间的斜率。

但是稍加观察我们发现应该是两点间斜率 $\pm\,\varepsilon$​​​ 比较准确，因为可能有若干点共线的情况。

$\pm\,\varepsilon$ 这个形式太丑了，我们尝试优美点描述：

设两点间斜率从小到大依次为：$k_1,k_2,\cdots,k_m$。我们依次考虑斜率在 $(-\infty,k_1),[k_1,k_2),\cdots,[k_{m-1},k_m),[k_m,\infty)$ 的时候的答案。

显然在题目条件下，这整个区间都是等价的。

---

然后我们尝试描述被两条平行线夹在中间的点。

考虑和平行线垂直的任意一条直线，然后考虑所有点在这条线上的投影（垂直和**投影的垂直**，应该懂为啥了吧），如下图：

![](https://dl3.img.timecdn.cn/2025/06/19/image.png)

于是我们发现相当于投影上的一个区间，并且显然是双射的。

或者说，把这条直线顺次做扫描，扫描到的点依次加入一个序列，这东西对应序列的区间。

然后维护出区间，就转换为最大子段和问题。

---

然后我们考虑斜率改变的时候，序列会怎么改变。

初始由于斜率 $-\infty$，序列就是按照 $(x,y)$ 坐标这个二元组排序的结果。

一样的，只有在两个点连线的斜率**被扫描后**，这两点在序列中的位置才会交换。

直接扫描，线段树维护最大子段和，复杂度 $O(N^2\log N)$​。

注意按斜率排序的时候，如果斜率相等，`pair` $(i,j)$ 小的要在前面，其中 $(i,j)$ 是形成此斜率的两点。

---



---

我把这归类为**平几维护相对顺序**的问题。类似题目 [P4864](https://www.luogu.com.cn/problem/P4864)，还有 **nfls《直线交点》**。

上面两题说的事情是：按 $x$ 坐标做扫描线，维护直线在 $x=X$ 时的相对顺序（例如求 $\texttt{kth}$​）。

可以把直线看成序列中的元素，初始按照斜率排序（$x=-\infty$ 的值）。

然后每扫到一个交点，交换对应两条线在序列中的位置，就维护了相对顺序。

交换次数为 $O(n^2)$​。

- 这题其实不太一样，是把点投影到直线上，要维护点的相对顺序。

```cpp
//洛谷 P10630
//https://www.luogu.com.cn/problem/P10630
#include<bits/stdc++.h>
#define LL long long
#define P pair<LL,LL>
#define x first
#define y second
#define ls w<<1
#define rs w<<1|1
#define lw l,m,ls
#define rw m+1,r,rs
#define fr(x) freopen(#x".in","r",stdin);freopen(#x".out","w",stdout);
using namespace std;
const int N=2005;
int n,m,p[N];LL ans;
struct E{P t;LL w;}A[N];
struct F{P t,id;}B[N*N/2];
inline LL operator*(P A,P B){return A.x*B.y-A.y*B.x;}
struct T{LL sl,sr,s,mx;}a[N<<2];
inline void ins(T &A,int t){A={t,t,t,t};}
inline void pu(int w)
{
	a[w].sl=max(a[ls].s+a[rs].sl,a[ls].sl);
	a[w].sr=max(a[rs].s+a[ls].sr,a[rs].sr);
	a[w].s=a[ls].s+a[rs].s;
	a[w].mx=max({a[ls].mx,a[rs].mx,a[ls].sr+a[rs].sl});
}
void bd(int l=1,int r=n,int w=1)
{
	if(l==r) return ins(a[w],A[l].w);
	int m=(l+r)>>1;bd(lw),bd(rw),pu(w);
}
void upd(int p,LL t,int l=1,int r=n,int w=1)
{
	if(l==r) return ins(a[w],t);int m=(l+r)>>1;
	p<=m?upd(p,t,lw):upd(p,t,rw);pu(w);
}
int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);cin>>n;
	for(int i=1;i<=n;i++) cin>>A[i].t.x>>A[i].t.y>>A[i].w,p[i]=i;
	sort(A+1,A+1+n,[](E A,E B){return A.t<B.t;});bd();
	for(int i=1;i<=n;i++) for(int j=1;j<i;j++)
		B[++m]={{A[i].t.x-A[j].t.x,A[i].t.y-A[j].t.y},{i,j}};
	sort(B+1,B+1+m,[](F A,F B){
		LL t=A.t*B.t;return !t?A.id<B.id:t<0;
	});
	ans=max(0ll,a[1].mx);
	for(int i=1,j;i<=m;i=j)
	{
		for(j=i+1;j<=m&&!(B[i].t*B[j].t);j++);
		for(int k=i;k<j;k++)
		{
			auto [u,v]=B[k].id;
			upd(p[u],A[v].w),upd(p[v],A[u].w),swap(p[u],p[v]);
		}ans=max(ans,a[1].mx);
	}
	return cout<<ans,0;
}
```

---

