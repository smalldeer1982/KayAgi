# Count The Rectangles

## 题目描述

在平面上画有 $n$ 条线段，第 $i$ 条线段连接两点 $(x_{i,1}, y_{i,1})$ 和 $(x_{i,2}, y_{i,2})$。每条线段都是非退化的，并且要么是水平的，要么是竖直的——形式化地说，对于每个 $i \in [1, n]$，要么 $x_{i,1} = x_{i,2}$，要么 $y_{i,1} = y_{i,2}$（但两者不会同时成立）。只有不同类型的线段才可能相交：任意两条水平线段不会有公共点，任意两条竖直线段也不会有公共点。

我们称编号为 $h_1$、$h_2$、$v_1$ 和 $v_2$ 的四条线段（满足 $h_1 < h_2$ 且 $v_1 < v_2$）能够组成一个矩形，当且仅当满足以下条件：

- 线段 $h_1$ 和 $h_2$ 是水平线段；
- 线段 $v_1$ 和 $v_2$ 是竖直线段；
- 线段 $h_1$ 与 $v_1$ 相交；
- 线段 $h_2$ 与 $v_1$ 相交；
- 线段 $h_1$ 与 $v_2$ 相交；
- 线段 $h_2$ 与 $v_2$ 相交。

请计算有多少种选择四条线段的方法，使它们能够组成一个矩形。注意，必须满足 $h_1 < h_2$ 且 $v_1 < v_2$。

## 说明/提示

下图展示了样例的情况：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1194E/0df80808060fcc7405e536f42c94972d38a7ef82.png) ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1194E/8812b754a729f01695d6f682c0c9ba14b0826bfc.png)

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
7
-1 4 -1 -2
6 -1 -2 -1
-2 3 6 3
2 -2 2 4
4 -1 4 3
5 3 5 1
5 2 1 2
```

### 输出

```
7
```

## 样例 #2

### 输入

```
5
1 5 1 0
0 1 5 1
5 4 0 4
4 2 4 0
4 3 4 5
```

### 输出

```
0
```

# 题解

## 作者：Heartlessly (赞：17)

## Description

二维坐标系上有 $n$ 条线段，每条线段连接 $(x_{i,1},y_{i,1}),(x_{i,2},y_{i,2})$ 两个整点，且所有线段平行于坐标轴，保证平行于同一条坐标轴的线段不相交。求这些线段能组成多少个矩形。

$(1 \leq n \leq 5 \times 10^3,x,y \in [-5 \times 10^3,5 \times 10^3])$

## Solution 1

暴力做法。先把横线和竖线分开存储，我们可以 $O(n^2)$ 预处理出与第 $i$ 条横线相交的竖线集合为 $f_i$ 。接下来枚举矩形的上下两条边为第 $i$ 条横线和第 $j$ 条横线，那么同时与这两条横线相交的竖线集合为 $f_i \cap f_j$，假设这个集合的大小为 $x$，则能形成 ${\rm C}_x^2$ 个矩形，累加就能得到答案。显然可以用 $\rm bitset$ 优化，时间复杂度为 $O(\frac{n^3}{w})$ 。但是这样写当横线数量大时会被卡掉，所以可以特判一下横线竖线哪个多，如果横线较多， 就反过来预处理横线集合，枚举竖线。

## Code 1

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

template <class T>
inline void read(T &x) {
    x = 0;
    char c = getchar();
    bool f = 0;
    for (; !isdigit(c); c = getchar()) f ^= c == '-';
    for (; isdigit(c); c = getchar()) x = x * 10 + (c ^ 48);
    x = f ? -x : x;
}

template <class T>
inline void write(T x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    T y = 1;
    int len = 1;
    for (; y <= x / 10; y *= 10) ++len;
    for (; len; --len, x %= y, y /= 10) putchar(x / y + 48);
}

const int MAXN = 5e3, MAXM = 2500;
int n, cnt1, cnt2;
LL ans;
struct Node {
    int x1, y1, x2, y2;
} row[MAXN + 5], col[MAXN + 5];
bitset<MAXN + 5> f[MAXM + 5];

int main() {
    read(n);
    for (int x1, y1, x2, y2, i = 1; i <= n; ++i) {
        read(x1), read(y1), read(x2), read(y2);
        if (x1 > x2) swap(x1, x2);
        if (y1 > y2) swap(y1, y2);
        if (y1 == y2) row[++cnt1] = (Node) { x1, y1, x2, y2 };
        else col[++cnt2] = (Node) { x1, y1, x2, y2 };//分开存储 
    }
    if (cnt1 < cnt2) {//竖线较多 
        for (int i = 1; i <= cnt1; ++i)
            for (int j = 1; j <= cnt2; ++j)
                if (row[i].x1 <= col[j].x1 && row[i].x2 >= col[j].x1 && 
                col[j].y1 <= row[i].y1 && col[j].y2 >= row[i].y2)
                    f[i][j] = 1;//第 i 条横线与第 j 条竖线相交
        for (int i = 1; i <= cnt1; ++i)
            for (int j = i + 1; j <= cnt1; ++j) {
                int t = (f[i] & f[j]).count();//同时与 i,j 相交的竖线数量 
                ans += 1ll * t * (t - 1) >> 1;
            }
    } else {//横线较多 
        for (int i = 1; i <= cnt1; ++i)
            for (int j = 1; j <= cnt2; ++j)
                if (row[i].x1 <= col[j].x1 && row[i].x2 >= col[j].x1 && 
                col[j].y1 <= row[i].y1 && col[j].y2 >= row[i].y2)
                    f[j][i] = 1;//第 j 条横线与第 i 条竖线相交
        for (int i = 1; i <= cnt2; ++i)
            for (int j = i + 1; j <= cnt2; ++j) {
                int t = (f[i] & f[j]).count();//同时与 i,j 相交的横线数量 
                ans += 1ll * t * (t - 1) >> 1;
            }
    }
    write(ans);
    putchar('\n'); 
    return 0;
}
```

## Solution 2

考虑将横线按 $y$ 坐标从小到大排序，竖线按上端点的 $y$ 坐标从小到大排序。然后枚举矩形下面的边为第 $i$ 条横线，把所有与该横线相交的竖线存到队列里，用树状数组维护区间竖线数量。接着枚举矩形上面的边为第 $j$ 条横线（在第 $i$ 条横线的上方），对于队列里上端点在第 $j$ 条横线下方的竖线，我们可以在树状数组中把它删掉，因为它不与第 $j$ 条横线相交。由于队列里竖线的上端点单调递增，这步操作可以线性解决。对于每对 $i,j$，用树状数组查询区间竖线数量，统计答案。注意树状数组的下标不能为非正数，所以给所有初始坐标加上一个较大的整数，时间复杂度 $O(n^2 \log n)$ 。

## Code 2

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

template <class T>
inline void read(T &x) {
    x = 0;
    char c = getchar();
    bool f = 0;
    for (; !isdigit(c); c = getchar()) f ^= c == '-';
    for (; isdigit(c); c = getchar()) x = x * 10 + (c ^ 48);
    x = f ? -x : x;
}

template <class T>
inline void write(T x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    T y = 1;
    int len = 1;
    for (; y <= x / 10; y *= 10) ++len;
    for (; len; --len, x %= y, y /= 10) putchar(x / y + 48);
}

const int MAXN = 5e3, MAXM = 1e4 + 1;
int n, cnt1, cnt2, q[MAXN + 5];
LL ans;
struct Node {
    int x1, y1, x2, y2;
    
    inline friend bool operator<(Node x, Node y) {
        return x.y2 < y.y2;
    }
} row[MAXN + 5], col[MAXN + 5];
struct BinaryIndexTree {//树状数组 
    int ind[MAXM + 5];
    
    inline void clear() {
        memset(ind, 0, sizeof (ind));
    }
    inline void add(int x, int p) {
        for (; x <= MAXM; x += x & -x) ind[x] += p;
    }
    inline int query(int x) {
        int res = 0;
        for (; x; x -= x & -x) res += ind[x];
        return res;
    }
    inline int query(int l, int r) {
        return query(r) - query(l - 1);
    }
} bit;

int main() {
    read(n);
    for (int x1, y1, x2, y2, i = 1; i <= n; ++i) {
        read(x1), read(y1), read(x2), read(y2);
        x1 += MAXN + 1, y1 += MAXN + 1, x2 += MAXN + 1, y2 += MAXN + 1;//防止出现负数 
        if (x1 > x2) swap(x1, x2);
        if (y1 > y2) swap(y1, y2);
        if (y1 == y2) row[++cnt1] = (Node) { x1, y1, x2, y2 };
        else col[++cnt2] = (Node) { x1, y1, x2, y2 };
    }
    sort(row + 1, row + cnt1 + 1), sort(col + 1, col + cnt2 + 1);
    for (int i = 1; i <= cnt1; ++i) {//枚举矩形下面的边 
        bit.clear();//清空树状数组 
        int tail = 0, k = 1;
        for (int j = 1; j <= cnt2; ++j)
            if (row[i].x1 <= col[j].x1 && row[i].x2 >= col[j].x1 && 
            col[j].y1 <= row[i].y1 && col[j].y2 >= row[i].y2) {
                //与第 i 条横线相交 
                bit.add(col[j].x1, 1);//树状数组单点修改 
                q[++tail] = j;//存入队列 
            }
        for (int j = i + 1; j <= cnt1; ++j) {//枚举矩形上面的边 
            for (; col[q[k]].y2 < row[j].y1 && k <= tail; ++k)// k 单调递增 
                bit.add(col[q[k]].x1, -1);//删去队列中不与 j 相交的竖线
            int l = max(row[i].x1, row[j].x1), r = min(row[i].x2, row[j].x2);
            if (l < r) {//两条线段有交 
                int res = bit.query(l, r);//[l, r] 区间内的竖线能与 i,j 组成矩形 
                ans += 1ll * res * (res - 1) / 2;//统计答案 
            }
        }
    }
    write(ans);
    putchar('\n');
    return 0;
}
```



---

## 作者：xfrvq (赞：1)

考虑固定两条横向直线，设与它们相交的纵向直线数量为 $x$，那么答案就是 $\displaystyle\sum\frac{x(x-1)}2$，（当然反过来用纵向直线也可以啊）。

枚举直线复杂度已经是 $n^2$，我们考虑数的那步怎么做。可以转数点模型（吗），但是没必要。

考虑建立 `bitset` 存一条直线与其他直线的相交情况 $0/1$。然后与两条直线都相交就是 `bitset` 的 `and`，然后数 $1$ 的个数就是 `count()`。

总复杂度 $O\left(\dfrac{n^3}w\right)$，发现限制很紧。于是我们考虑在横向直线多的时候，枚举纵向直线，否则枚举横向直线。

于是 $n$ 的大小相当于被优化掉了一半，效果显著啊（喜。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 5e3 + 5;

int n; long long res = 0;
int l1,x[N],xi[N],yl[N],yr[N];
int l2,y[N],yi[N],xl[N],xr[N];
bitset<N> t[N];

int main(){
	scanf("%d",&n);
	for(int x1,x2,y1,y2,i = 1;i <= n;++i){
		scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
		if(x1 > x2) swap(x1,x2); if(y1 > y2) swap(y1,y2);
		if(x1 == x2) x[++l1] = x1,xi[l1] = i,yl[l1] = y1,yr[l1] = y2;
		if(y1 == y2) y[++l2] = y1,yi[l2] = i,xl[l2] = x1,xr[l2] = x2;
	}
	if(l1 < l2){
		for(int i = 1;i <= l1;++i)
			for(int j = 1;j <= l2;++j)
				if(xl[j] <= x[i] && x[i] <= xr[j])
					if(yl[i] <= y[j] && y[j] <= yr[i]) t[i][yi[j]] = 1;
		for(int i = 1;i <= l1;++i)
			for(int j = i + 1;j <= l1;++j){
				int x = (t[i] & t[j]).count();
				res += x * (x - 1) / 2;
			}
	} else {
		for(int i = 1;i <= l1;++i)
			for(int j = 1;j <= l2;++j)
				if(xl[j] <= x[i] && x[i] <= xr[j])
					if(yl[i] <= y[j] && y[j] <= yr[i]) t[j][xi[i]] = 1;
		for(int i = 1;i <= l2;++i)
			for(int j = i + 1;j <= l2;++j){
				int x = (t[i] & t[j]).count();
				res += x * (x - 1) / 2;
			}
	}
	printf("%lld\n",res);
	return 0;
}
```

---

## 作者：_edge_ (赞：1)

首先可以发现先枚举两条横线，他们是不相交的，因此我们所需要计算的即为和他们有交的竖线。

~~这个问题是典型的偏序问题，可以用树状数组之类的搞，但是我比较傻不太会做。~~

因此如果我们可以用一个类似于桶一样的记录这个横线与竖线哪个相交了，再取他们的交集即可。

这个桶用 bitset 来实现即可。

需要注意的一些细节就是判断是否有交的时候，竖线的 $x$ 要在横线之间，横线 $y$ 要在竖线之间。

同时，这样写可能会被卡常，所以要手动开一下 O2，或者横竖线转换。

我的代码里没写 O2，要用这种方法过题的同学请自行开。

时间复杂度 $O(\frac{n^3}{w})$ 。

```cpp
#include <iostream>
#include <cstdio>
#include <bitset>
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21],*p1=buf,*p2=buf;
inline int read()
{
    char c=getchar();int x=0;bool f=0;
    for(;!isdigit(c);c=getchar())f^=!(c^45);
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    if(f)x=-x;return x;
}
using namespace std;
const int INF=5e3+5;
struct _node_data{
	int x,y,xx,yy;
}aa[INF],bb[INF];
int n,tot1,tot2;
bitset<INF> f[INF];
signed main()
{
	n=read();
	for (int i=1;i<=n;i++) {
		int x=0,y=0,xx=0,yy=0;
		x=read();y=read();xx=read();yy=read();
		if (y>yy) swap(y,yy);
		if (x>xx) swap(x,xx);
		if (y==yy) aa[++tot1]=(_node_data){x,y,xx,yy};
		else bb[++tot2]=(_node_data){x,y,xx,yy};
	}
	for (int i=1;i<=tot1;i++) {
		for (int j=1;j<=tot2;j++) {
			if (aa[i].x<=bb[j].x && bb[j].x<=aa[i].xx) 
				if (bb[j].y<=aa[i].y && aa[i].y<=bb[j].yy) {
					f[i][j]=1;
				} 
		}
	}
	long long ans=0;
	for (int i=1;i<=tot1;i++)
		for (int j=i+1;j<=tot1;j++) {
			long long xx=(f[i]&f[j]).count();
			ans+=xx*(xx-1)/2;
		}
	cout<<ans<<"\n";
	return 0;
}
```


---

## 作者：Juanzhang (赞：1)

这是一篇 **非正解** ，建议看完标算再食用（雾

令 $n1=$ 平行于 $y$ 轴的线段数， $n2=$ 平行于 $x$ 轴的线段数

考虑任意两条平行于 $y$ 轴的线段对答案的贡献，令 $s=$ 同时与两条线段相交的平行于 $x$ 轴的线段数，贡献即为 $\frac{s(s-1)}{2}$

可以考虑枚举每两条平行于 $y$ 轴的线段，统计答案可以考虑对于每条平行于 $y$ 轴的线段，预处理与之相交的平行于 $x$ 轴的线段并用 bitset 存储，之后暴力 bitset 操作

时间复杂度 $O(\frac{n^3}{w})$ ，仍然跑不过

可以发现这个做法的时间复杂度瓶颈在于每次 bitset 操作的时间复杂度都是 $\frac{5000}{w}$ 的，而我们只需要统计 bitset 前 $n2$ 位，可以考虑 **手写** bitset

考虑这样做的最坏时间复杂度，把 $n1$ 取到 $3333$ ，大概会跑 $3333^2\times(5000-3333)/64/2\approx1.4\times10^8$ 次~~，cf机子两秒完全不虚~~

时间复杂度 $O(\frac{n^3}{w})$

代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int maxn = 5010;
int n, n1, n2, tot;

struct node1 {
  int x, y1, y2;
} a[maxn];

struct node2 {
  int x1, x2, y;
} b[maxn];

typedef unsigned long long u64;

struct Bitset {
  u64 s[maxn >> 6];

  inline void set(int x) {
    s[x >> 6] |= 1llu << (x & 63);
  }
} tmp, f[maxn];

inline int add(int x, int y) {
  int ans = 0;
  for (register int i = 0; i <= tot; ++i) {
    ans += __builtin_popcountll(f[x].s[i] & f[y].s[i]);
  }
  return ans;
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    int x1, x2, y1, y2;
    scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
    if (x1 == x2) {
      if (y1 > y2) swap(y1, y2);
      a[++n1] = node1{x1, y1, y2};
    } else {
      if (x1 > x2) swap(x1, x2);
      b[++n2] = node2{x1, x2, y1};
    }
  }
  tot = n2 >> 6;
  for (int i = 1; i <= n1; ++i) {
    for (int j = 1; j <= n2; ++j) {
      if (b[j].x1 <= a[i].x && a[i].x <= b[j].x2 && a[i].y1 <= b[j].y && b[j].y <= a[i].y2) {
        f[i].set(j);
      }
    }
  }
  long long ans = 0;
  for (int i = 1; i < n1; ++i) {
    for (int j = i + 1; j <= n1; ++j) {
      int s = add(i, j);
      ans += s * (s - 1);
    }
  }
  printf("%I64d", ans >> 1);
  return 0;
}
```

---

## 作者：zhangxiao666 (赞：0)

## 题意：
给定 $n$ 条平行于坐标轴的线段，问能组成多少个矩形。

## 思路：
先预处理与每条横线相交纵线的集合，那与两条横线相交的纵线数量显然就是他们交集的大小 $siz$，然后他们贡献就是 $C^2_x$ 了。

求交集可以用 $\rm bitset$ 优化到 $\frac{n}{w}$，防止横线特别多可以先比较横线竖线大小，按少的做，这样 $n$ 就小了只少一半，总体上就是 $\frac{n^3}{w}$（实际还有个 $\frac{1}{8}$）。

然后一个紫就做完了。

## 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 5e3 + 5;
int n, cntx, cnty;
long long ans;
struct node {int xx1, yy1, xx2, yy2;};
array<node, N> x, y;
array<bitset<N>, 2505> f;

template<class T>
inline void read(T &x) 
{ 
	x = 0;
	short flag = 1;
	char c = getchar();
    while(c < '0' || c > '9'){
        if(c == '-')flag = -1;
        c = getchar();
    }
	while(c >= '0' && c <= '9') {
		x = (x << 3) + (x >> 1) + (c ^ 48);  
		c = getchar();
	}
	x *= flag;
}

bool Check(node a, node b)
{
    return (a.xx1 <= b.xx1 && a.xx2 <= b.xx2 && b.yy1 <= a.yy1 && b.yy2 <= a.yy1);
}

long long C2(int x)
{
    return (x * 1ll * (x - 1)) >> 1;
}

void work()
{
    read(n);
    for (int i = 1; i <= n; ++i) 
    {
        short xx1, yy1, xx2, yy2;
        read(xx1), read(yy1), read(xx2), read(yy2);
        if (xx1 > xx2) swap(xx1, xx2);
        if (yy1 > yy2) swap(yy1, yy2);
        if (xx1 == xx2) x[++cntx] = {xx1, yy1, xx2, yy2};
        else y[++cnty] = {xx1, yy1, xx2, yy2};
    }
    if (cnty > cntx)
    {
        for (int i = 1; i <= cntx; ++i)
        {
            for (int j = 1; j <= cnty; ++j)
            {
                if (Check(y[j], x[i])) f[i][j] = 1;
            }
        }
        for (int i = 1; i <= cntx; i++)
        {
            for (int j = i + 1; j <= cntx; j++)
            {
                ans += C((f[i] & f[j]).count());
            }
        }
    }
    else
    {
        for (int i = 1; i <= cnty; ++i)
        {
            for (int j = 1; j <= cntx; ++j)
            {
                if (Check(y[i], x[j])) f[i][j] = 1;
            }
        }
        for (int i = 1; i <= cntx; ++i)
        {
            for (int j = i + 1; j <= cntx; ++j)
            {
                ans += C((f[i] & f[j]).count());
            }
        }
    }
    cout << ans << "\n";
}

int mian()
{
    work();
    return 3;
}
```

---

## 作者：1saunoya (赞：0)

题意:给若干**平行于坐标轴的**线段，数矩形个数

看到题，然后就能得到一个优秀的做法。

我们首先枚举两条横线。

然后数一下同时穿过这两条横线的有多少个竖线，显然可以用 $\binom{2}{cnt}$ 来计算个数。

这个过程可以用 bitset 优化。

有点卡常。

可以考虑手写 bitset 或者每次都变换横线竖线（

这样就可以过了。

[code](https://codeforces.ml/contest/1194/submission/98177803)

---

## 作者：DerrickLo (赞：0)

我们记 $a_{i,j}$ 表示第 $i$ 条线段与第 $j$ 条线段是否相交。

我们考虑枚举两条平行的线段 $i,j$，如果这两条直线之间有 $x$ 条与他们垂直且与他们相交的线段，那么这两条直线之间就有 $\frac{x\times(x-1)}{2}$ 个矩形。

那么我们枚举所有与它们垂直的线段 $k$，如果 $a_{i,k}=1$ 且 $a_{j,k}=1$，那么线段 $k$ 就满足条件。

我们要求有多少个 $k$，如果暴力枚举是 $O(n^3)$ 的，我们可以使用 `bitset` 优化，时间复杂度 $O(\frac{n^3}{w})$，可以通过。

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize("-Ofast,fast-math,-inline")
#pragma GCC target("avx,sse,sse2,sse3,sse4,popcnt") 
using namespace std;
int n;
long long ans;
bitset<5005>b[5005],c;
struct nd{
	int a,b,c,d;
}a[5005];
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i].a>>a[i].b>>a[i].c>>a[i].d;
		if(a[i].a>a[i].c)swap(a[i].a,a[i].c);
		if(a[i].b>a[i].d)swap(a[i].b,a[i].d);
	}
	for(int i=1;i<=n;i++)for(int j=i+1;j<=n;j++){
		int f1=(a[i].a==a[i].c)?1:2,f2=(a[j].a==a[j].c)?1:2;
		if(f1==f2){
			b[i][j]=b[j][i]=0;
			continue;
		}
		if(f1==1){
			if(a[j].a<=a[i].a&&a[j].c>=a[i].a&&a[i].b<=a[j].b&&a[i].d>=a[j].b){
				b[i][j]=b[j][i]=1;
			}
		}
		else{
			if(a[i].a<=a[j].a&&a[i].c>=a[j].a&&a[j].b<=a[i].b&&a[j].d>=a[i].b){
				b[i][j]=b[j][i]=1;
			}
		}
	}
	for(int i=1;i<=n;i++)for(int j=i+1;j<=n;j++){
		if(a[i].a==a[i].c&&a[j].a==a[j].c){
			int aa=(b[i]&b[j]).count();
			ans+=(long long)aa*(aa-1)/2;
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：happybob (赞：0)

考虑一个三次方做法：

枚举两条横线，求出有多少条竖线和两条横线都相交，假设为 $c$ 个，那么对答案有 $\dbinom{c}{2}$ 的贡献。复杂度 $O(n^3)$。

考虑求出每条横线与每条竖线是否相交，这部分可以 $O(n^2)$ 求出，那么就可以用 `bitset` 维护了，复杂度 $O(\dfrac{n^3}{\omega})$，适当卡常即可通过。

```cpp
#pragma GCC optimize("-Ofast,fast-math,-inline")
#pragma GCC target("avx,sse,sse2,sse3,sse4,popcnt") 
#include <bits/stdc++.h>
using namespace std;

const int N = 5e3 + 5;

#define x1 X1
#define y1 Y1
#define x2 X2
#define y2 Y2

int t, n, k;

int x1[N], y1[N], x2[N], y2[N];
long long ans=0ll;

bitset<N> bt[N];

int main()
{
	ios::sync_with_stdio(0), cin.tie(0);
	cin>>n;
	vector<int> v;
	for(int i=1;i<=n;i++)
	{
		cin>>x1[i]>>y1[i]>>x2[i]>>y2[i];
	}
	for(int i=1;i<=n;i++)
	{
		if(y1[i]!=y2[i]) continue;
		for(int j=1;j<=n;j++)
		{
			if(y1[j]==y2[j]) continue;
			int l=y1[j],r=y2[j];
			if(l>r) swap(l,r);
			if(y1[i]<l||y1[i]>r) continue;
			int nl=x1[i],nr=x2[i];
			if(nl>nr) swap(nl,nr);
			if(x1[j]<nl||x1[j]>nr) continue;
			bt[i][j]=1;
			//cout<<"!!!: "<<i<<" "<<j<<"\n";
		}
	}
	for(int i=1;i<=n;i++)
	{
		if(y1[i]!=y2[i]) continue;
		for(int j=1;j<=n;j++)
		{
			if(y1[j]!=y2[j]||y1[j]>=y1[i]) continue;
			int cnt=(bt[i]&bt[j]).count();
			ans=(ans+1ll*cnt*(cnt-1)/2);
			//cout<<"!!!: "<<i<<" "<< j <<" " << cnt<<"\n";
		}
	}
	cout<<ans<<"\n";
	return 0;
}

```

---

