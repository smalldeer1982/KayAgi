# Fence Obstacle Course

## 题目描述

农夫约翰为奶牛们建造了一条障碍赛道。赛道由一系列 $N$ 个长度不一的栅栏组成（$1 \le N \le 100000$），每个栅栏都与 x 轴平行。栅栏 $i$ 的 y 坐标为 $i$。

FJ 的谷仓门位于原点（如下图中的 '`*`' 处）。赛道的起点位于坐标 ($S$,$N$)。

```
   +--S--+-+-+
+--+--+--+
    ...
   +--+--+-+
      +--+-+-+
|==|==|==*=|=|=|
-3 -2 -1 0 1 2 3
```

FJ 原本的意图是让奶牛跳过栅栏，但奶牛更喜欢四蹄着地。因此，它们会沿着栅栏行走，当栅栏结束时，它们会转向 x 轴并继续直线行走，直到碰到另一个栅栏段或谷仓的侧面。然后它们决定向左或向右走，直到到达栅栏段的末端，依此类推，直到最终到达谷仓的侧面，然后可能经过短暂的步行，达到终点。

自然地，奶牛们希望尽可能少地行走。找出奶牛们从起点到谷仓门来回行走的最短距离。


## 说明/提示

（由 ChatGPT 4o 翻译）

## 样例 #1

### 输入

```
4 0
-2 1
-1 2
-3 0
-2 1```

### 输出

```
4```

# 题解

## 作者：wjyppm1403 (赞：2)

题目大意：

>给定 $n$ 个平台，第 $i$ 个平台的高度为 $i$ ，其左右端点为 $L_i,R_i$。现在你在第 $n$ 个平台上，横坐标为 $S$，可以选择在平台的左端点或右端点跳到下一个平台。你需要设计一个移动方案使得移动到 $(0,0)$ 点时水平移动距离最小。输出最小水平移动距离。

下面我们将栅栏用“平台”一词来代替。

根据题意，能够发现奶牛跑到第 $i$ 个平台时有 2 种决策，分别是向左走到左端点和向右走到右端点，设 $f[i][0/1]$ 表示当前到达第 $i$ 个平台，向左走到左端点（即 0）或向右走到右端点（即 1）的累计距离最小值。

如果枚举从哪块模板跳过来复杂度可能会退化，我们可以考虑递推的思想，枚举下面的跳板 $j$，分别从左右端点枚举，只要枚举到第一个能够跳到的就结束枚举（~~你又不能穿过去这个跳板~~）。

![](https://cdn.luogu.com.cn/upload/image_hosting/ul6ojtiv.png)

转移方程如下，其中 $j$ 表示左端点往下走走到的第一个平台，$k$ 表示右端点往下走走到的第一个平台：

$$f[j][0]=\min\limits_{L_j\le L_i \le R_j}f[i][0]+|L_i-L_j| \\ f[j][1]=\min\limits_{L_j\le L_i \le R_j}f[i][0]+|L_i-R_j|$$

$$f[k][0]=\min\limits_{L_k\le R_i \le R_k}f[i][1]+|R_i-L_k| \\ f[k][1]=\min\limits_{L_k\le R_i \le R_k}f[i][1]+|R_i-R_k|$$

初始化 $f[n][0]=|s-L_n|, f[n][1]=|R_n-s|$，其余全部为正无穷。

这样的时间复杂度是 $O(n^2)$，不能通过本题。

观察转移方程，我们发现瓶颈就在于枚举一个在区间范围的合法值 $j,k$。要查询的是第一个，又是区间查询。我们可以使用线段树来优化。

我们可以从小到大枚举，每一次我们查询左端点被下方的哪一个点覆盖，右端点同理，记录下来，查询完后我们对 $[L_i,R_i]$ 进行区间赋值，赋值为 $i$。这样我们查询的值刚好就是上面要求的往下走第一个值，转移方程同上，做法是等价的只不过用线段树加快了查询。

时间复杂度为 $O(n \log n)$，瓶颈在插入与查询。

本题的坐标有负值，可以考虑离散化或都加上一个偏移量，这里采用后者方法。注意区间覆盖用懒标记优化复杂度，线段树不应当有 pushup，因为这里维护的是单独区间颜色信息（当然也可以用珂朵莉树，但是复杂度不一定了）。

代码如下：

```cpp
#include <bits/stdc++.h>
#define ls p << 1
#define rs p << 1 | 1
#define getn(x) (x + 100001) // 坐标偏移，将负坐标转换为正数方便处理
using namespace std;
constexpr int MN = 2e6 + 15;
int f[MN][2], lc[MN], rc[MN], n, s;
// lc，rc为记录的编号
struct zhalan {
    int l, r;
} zl[MN];

struct segtree {
    int l, r, val, cov;
} t[MN << 2];


void pushdown(int p) {
    if (t[p].cov) {
        t[ls].val = t[rs].val = t[ls].cov = t[rs].cov = t[p].cov;
        t[p].cov = 0;
    }
}

void build(int p, int l, int r) {
    t[p].l = l;
    t[p].r = r;
    if (l == r) return;
    int mid = l + r >> 1;
    build(ls, l, mid);
    build(rs, mid + 1, r);
}

void cover(int p, int fl, int fr, int k) {
    if (t[p].l >= fl && t[p].r <= fr) {
        t[p].cov = t[p].val = k;
        return;
    }
    pushdown(p);
    int mid = (t[p].l + t[p].r) >> 1;
    if (mid >= fl) cover(ls, fl, fr, k);
    if (mid < fr) cover(rs, fl, fr, k);
}


int query(int p, int pos) {
    if (t[p].l == t[p].r) return t[p].val;
    pushdown(p);
    int mid = (t[p].l + t[p].r) >> 1;
    return pos <= mid ? query(ls, pos) : query(rs, pos);
}

int main() {
    memset(f, 0x3f, sizeof(f)); // 初始化为极大值
    build(1, 1, 2e6);
    zl[0].l = zl[0].r = getn(0); //注意这里是getn(0)! 原点也要偏移！
    cin >> n >> s;
    for (int i = 1; i <= n; i++) {
        int a, b;
        cin >> a >> b;
        zl[i].l = getn(a);//偏移l，r
        zl[i].r = getn(b);
        lc[i] = query(1, zl[i].l); // 查询当前平台i的左端点下方第一个平台编号
        rc[i] = query(1, zl[i].r); // 查询当前平台i的右端点下方第一个平台编号
        cover(1, zl[i].l, zl[i].r, i); // 将区间[zl[i].l, zl[i].r]标记为平台i
    }

    f[n][0] = abs(getn(s) - zl[n].l);
    f[n][1] = abs(zl[n].r - getn(s));

    for (int i = n; i >= 1; i--) {// 递推，启动！
        // 从当前平台i的左端点跳到下方平台lc[i]的左右端点
        f[lc[i]][0] = min(f[lc[i]][0], f[i][0] + abs(zl[i].l - zl[lc[i]].l));
        f[lc[i]][1] = min(f[lc[i]][1], f[i][0] + abs(zl[i].l - zl[lc[i]].r));
        // 从当前平台i的右端点跳到下方平台rc[i]的左右端点
        f[rc[i]][0] = min(f[rc[i]][0], f[i][1] + abs(zl[i].r - zl[rc[i]].l));
        f[rc[i]][1] = min(f[rc[i]][1], f[i][1] + abs(zl[i].r - zl[rc[i]].r));
    }
    cout << f[0][0]; // 这里也可以是f[0][1]
    return 0;
}

```

---

## 作者：xyvsvg (赞：1)

提供一种目前实现最简单的做法。

设 $f_{i,j}$ 表示考虑到第 $i$ 个栅栏，且位置是 $j$ 的最小步数。显然 $\forall\ l_i<j<r_i$，$f_{i,j}$ 都不合法，这时候奶牛只能向左或者向右走到边缘。

第一维可以直接滚动数组压掉。

考虑使用珂朵莉树维护这个过程。由于每次加入的点只有 $O(1)$ 个，且每个点被访问后就马上被删除，所以复杂度是 $O(n\log n)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> P;
signed main()
{
    int n,s;
    cin>>n>>s;
    vector<P>a(n);
    map<int,int>odt;
    odt[-1e9]=odt[1e9]=-1;
    odt[s]=0;
    for(auto&[x,y]:a)
        cin>>x>>y;
    reverse(a.begin(),a.end());
    const int inf=0x3f3f3f3f;
    for(auto[l,r]:a)
    {
        if(!odt.count(l))
            odt[l]=inf;
        if(!odt.count(r))
            odt[r]=inf;
        for(auto it=odt.upper_bound(l);it->first<r;it=odt.erase(it))
            odt[l]=min(odt[l],it->first-l+it->second),
            odt[r]=min(odt[r],r-it->first+it->second);
    }
    int ans=inf;
    for(auto[x,y]:odt)
        ans=min(ans,abs(x)+y);
    cout<<ans<<endl;
    return 0;
}

```

---

## 作者：GY程袁浩 (赞：1)

> **$\textbf{Motivation 1}$：我发现对于奶牛到了一个栅栏上，只有两种决策，我是不是可以把往左走或者往右走之后当成一个子结构？**

没错，我们可以这么做！走到栅栏左边或者右边两种决策可以引出我们的子结构。

设 $f_{i,0/1}$ 表示在一个栅栏的最左边和最右边时题目要求的答案。转移是显然的，我们只需要考虑由左边和右边往下走到的栅栏的 DP 状态转移即可。代价就是我们走到新栅栏的左边右边的路程。

好了，现在我们只有一个问题了，就是我们该如何知道从一个栅栏的左边和右边走下去的栅栏是什么。考虑这实际上相当于一些操作。操作一是查询位置 $pl$ 上的值，操作二是让一个区间值都与 $k$ 取最大值。那么这个东西明显是线段树能做的，上懒标记即可。

那么这个数据结构优化 DP 的题目我们就做好了。因为坐标有可能是负数，所以我们加上偏移量即可。

```cpp
// Problem: P10964 Fence Obstacle Course
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P10964
// Memory Limit: 512 MB
// Time Limit: 1000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
#define int long long
#define upp(a, x, y) for (int a = x; a <= y; a++)
#define dww(a, x, y) for (int a = x; a >= y; a--)
#define pb(x) push_back(x)
#define endl '\n'
#define x first
#define y second
#define PII pair<int, int>
using namespace std;
const int N = 3e5 + 10, INF = 0x3f3f3f3f3f3f3f3f;
struct node {
    int l, r, maxn, lz;
#define l(x) tr[x].l
#define r(x) tr[x].r
#define maxn(x) tr[x].maxn
#define lz(x) tr[x].lz
};
struct segmentree {
    node tr[N * 4];
    void pu(int x) { maxn(x) = max(maxn(x * 2), maxn(x * 2 + 1)); }
    void pd(int x) {
        if (lz(x)) {
            maxn(x * 2) = max(maxn(x * 2), lz(x));
            maxn(x * 2 + 1) = max(maxn(x * 2 + 1), lz(x));
            lz(x * 2) = max(lz(x * 2), lz(x));
            lz(x * 2 + 1) = max(lz(x * 2 + 1), lz(x));
            lz(x) = 0;
        }
    }
    void build(int x, int l, int r) {
        l(x) = l, r(x) = r;
        if (l == r) {
            maxn(x) = 0;
            return;
        }
        int mid = l + r >> 1;
        build(x * 2, l, mid);
        build(x * 2 + 1, mid + 1, r);
        pu(x);
    }
    void change(int x, int ll, int rr, int k) {
        int l = l(x), r = r(x);
        if (l >= ll && r <= rr) {
            maxn(x) = max(maxn(x), k);
            lz(x) = max(lz(x), k);
            return;
        }
        pd(x);
        int mid = l + r >> 1;
        if (ll <= mid) change(x * 2, ll, rr, k);
        if (mid < rr) change(x * 2 + 1, ll, rr, k);
        pu(x);
    }
    int qry(int x, int p) {
        int l = l(x), r = r(x);
        if (l == r && l == p) return maxn(x);
        int mid = l + r >> 1;
        pd(x);
        int ans;
        if (p <= mid)
            ans = qry(x * 2, p);
        else
            ans = qry(x * 2 + 1, p);
        pu(x);
        return ans;
    }
} t1;
int dist(int x, int y) { return abs(x - y); }
int f[N][2];
int l[N], r[N];
int n, s;
PII a[N];
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    memset(f, 0x3f, sizeof f);
    cin >> n >> s;
    s += 1e5 + 2;
    t1.build(1, 1, 2e5 + 2);
    upp(i, 1, n) {
        cin >> a[i].x >> a[i].y;
        a[i].x += 1e5 + 2;
        a[i].y += 1e5 + 2;
    }
    // reverse(a + 1, a + 1 + n);
    upp(i, 1, n) {
        l[i] = t1.qry(1, a[i].x);
        r[i] = t1.qry(1, a[i].y);
        t1.change(1, a[i].x, a[i].y, i);
    }
    a[0].x = a[0].y = 1e5 + 2;
    f[0][0] = f[0][1] = 0;
    upp(i, 1, n) {
        f[i][0] = min(f[i][0], min(f[l[i]][0] + dist(a[i].x, a[l[i]].x),
                                   f[l[i]][1] + dist(a[i].x, a[l[i]].y)));
        f[i][1] = min(f[i][1], min(f[r[i]][0] + dist(a[i].y, a[r[i]].x),
                                   f[r[i]][1] + dist(a[i].y, a[r[i]].y)));
    }
    int kk = 0;
    dww(i, n, 1) if (a[i].x < s && a[i].y > s) {
        kk = i;
        break;
    }
    cout << min(f[kk][0] + dist(s, a[kk].x), f[kk][1] + dist(s, a[kk].y))
         << endl;
    return 0;
}
```

---

## 作者：AndrewBer (赞：0)

# Fence Obstacle Course题解

[P10964 Fence Obstacle Course - 洛谷](https://www.luogu.com.cn/problem/P10964)

## 题意

> 在一个平面直角坐标系中，给出起点和若干条线段的坐标。求从起点出发向下走，遇到线段可以走的线段的两个端点，然后继续向下走，最后走到横轴再走到原点的过程中，水平移动的最小距离。

## 思路

我们可以发现，当走到某一条线段后，可以花费一段水平位移移动到某一个端点，然后以这个端点作为起点再出发。很明显，这个过程满足最优子结构，所以考虑 dp。

设 $dp_{i,0/1}$ 表示从第 $i$ 个围栏的左/右端点出发，走到原点所需的最小位移。

转移方程非常简单：
$$
dp_{i,0} = \min(dp_{j,0} + |fence_{i,0} - fence_{j,0}|,dp_{j,1} + |fence_{i,0} - fence_{j,1}|)
$$

$$
dp_{i,1} = \min(dp_{j,0} + |fence_{i,1} - fence_{j,0}|,dp_{j,1} + |fence_{i,1} - fence_{j,1}|)
$$

其中 $fence_{i,0/1}$ 表示第 $i$ 个围栏的左/右端点的横坐标，$j$ 则是当前从所在端点向下走遇到的第一个围栏的标号。

根据题意，我们可以从将第 $0$ 号围栏左右端点设置成原点，然后从 $1$ 到 $n$ 跑一遍 dp 即可。而对于 $j$ 的查找，如果枚举时间按复杂度将会是 $O(n^2)$ 的，显然无法承受，考虑优化。

很显然纵坐标更大的围栏会覆盖纵坐标小的围栏，这就转化成线段区间覆盖问题，用线段树和懒标记就可以轻松解决,时间复杂度优化到了 $O(\log n)$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 100010;
int n,s,v[N*2];
long long f[N*2][2],ans = 1e14;

struct node
{
	int a,b;
}fence[N];

struct SegmenTree
{
	int l,r,id;
	#define l(p) t[p].l
	#define r(p) t[p].r
	#define k(p) t[p].id 
}t[N*8];

void Biuld(int p,int l,int r)
{
	l(p) = l;r(p) = r;
	if(l == r)return;
	int mid = (l+r)>>1;
	Biuld(p*2,l,mid);
	Biuld(p*2+1,mid+1,r);
}

void spread(int p)
{
	if(k(p) != -1)
	{
		k(p*2) = k(p);
		k(p*2+1) = k(p);
		k(p) = -1;
	}
}

void change(int p,int l,int r,int v)
{
	if(l <= l(p) && r(p) <= r)
	{
		k(p) = v;
		return;
	}
	spread(p);
	int mid = (l(p) + r(p))>>1;
	if(l <= mid) change(p*2,l,r,v);
	if(r > mid) change(p*2+1,l,r,v);
}

int ask(int p,int x)
{
	if(l(p) == r(p)) return k(p);
	spread(p);
	int mid = (l(p) + r(p))>>1;
	if(x <= mid) return ask(p*2,x);
	else return ask(p*2+1,x);
}

int main()
{
	int x;
	scanf("%d %d",&n,&s);
	s += 100000;
	Biuld(1,0,200000);
	memset(f,0x3f,sizeof(f));
	f[0][0] = f[0][1] = 0;
	fence[0].a = fence[0].b = 100000;
	for(int i = 1;i<=n;i++) scanf("%d %d",&fence[i].a,&fence[i].b);
	for(int i = 1;i<=n;i++)
	{
		fence[i].a += 100000;
		fence[i].b += 100000;
		x = ask(1,fence[i].a);
//		printf("<%d,",x);
		f[i][0] =  min(f[x][0] + abs(fence[i].a-fence[x].a),f[x][1] + abs(fence[i].a - fence[x].b));
		x = ask(1,fence[i].b);
//		printf("%d>\n",x);
		f[i][1] =  min(f[x][0] + abs(fence[i].b-fence[x].a),f[x][1] + abs(fence[i].b - fence[x].b));
//		printf("left:%d right:%d\n",f[i][0],f[i][1]);
		change(1,fence[i].a,fence[i].b,i);
	}
	ans = min(f[n][0] + abs(s-fence[n].a),f[n][1] + abs(s-fence[n].b));
	printf("%lld",ans);
	return 0;
}
```

---

