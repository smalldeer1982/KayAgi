# PolandBall and Polygon

## 题目描述

PolandBall has such a convex polygon with $ n $ veritces that no three of its diagonals intersect at the same point. PolandBall decided to improve it and draw some red segments.

He chose a number $ k $ such that $ gcd(n,k)=1 $ . Vertices of the polygon are numbered from $ 1 $ to $ n $ in a clockwise way. PolandBall repeats the following process $ n $ times, starting from the vertex $ 1 $ :

Assume you've ended last operation in vertex $ x $ (consider $ x=1 $ if it is the first operation). Draw a new segment from vertex $ x $ to $ k $ -th next vertex in clockwise direction. This is a vertex $ x+k $ or $ x+k-n $ depending on which of these is a valid index of polygon's vertex.

Your task is to calculate number of polygon's sections after each drawing. A section is a clear area inside the polygon bounded with drawn diagonals or the polygon's sides.

## 说明/提示

The greatest common divisor (gcd) of two integers $ a $ and $ b $ is the largest positive integer that divides both $ a $ and $ b $ without a remainder.

For the first sample testcase, you should output "2 3 5 8 11". Pictures below correspond to situations after drawing lines.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF755D/4990bd3c0c7dd5836fdcc579f970dcdca8dbd872.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF755D/6451ef95db9646f275ba3ec79da2a8d5b0b028d0.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF755D/da900464c60a214ba6c5242ba8fc65122871a490.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF755D/a8b3c0780f20737fed12f744f83c0f1eab3d538f.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF755D/c214010a205eb51e891b2376aacedcb09475410e.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF755D/ac2e2680dc9611afb331663a01c918e0c001e832.png)

## 样例 #1

### 输入

```
5 2
```

### 输出

```
2 3 5 8 11 ```

## 样例 #2

### 输入

```
10 3
```

### 输出

```
2 3 4 6 9 12 16 21 26 31 ```

# 题解

## 作者：Brilliant11001 (赞：9)

[更好的阅读体验](https://www.cnblogs.com/Brilliant11001/p/18573071)

NOIP 前写题解加 rp（

## [题目传送门](https://www.luogu.com.cn/problem/CF755D)

这道题怎么都是数据结构题解？那本蒟蒻就来一篇数学规律法题解（貌似是本题唯一的线性做法）。

### 思路：

模拟赛上有一道十分相似的题目，但是一开始想到的是用数据结构维护每次插入一条线段之前查询有多少根线段与其相交，但是太蒻了不会打，所以只好思考数学解法。

~~让我们充分发扬人类智慧~~

注意到本题有两句特别关键的话：

1. 任意三个对角线都不能在同一点相交；
2. $k$ 与 $n$ 互质。

第一句话保证了省去了许多需要讨论的情况，从而得出一个结论：

> 增加的截⾯数 $=$ 新边与之前连的边的交点数 $+1$。（这里只算图形内的交点）

而第二句话告诉我们：**每个点都会被连且仅会被连一次，这意味着不需要考虑重边的问题。**

观察了一会儿样例，发现新截面数的增长很有规律：每次加的数 $d$ 是单调递增并且逐步 $+1$ 的，所以不妨从此入手，猜测增长速率 $d$ 的增长规律。

画图举例，假设 $n = 7,k = 3$：

![](https://cdn.luogu.com.cn/upload/image_hosting/39p2iglc.png)

先画第一条线段：

![](https://cdn.luogu.com.cn/upload/image_hosting/z9rreoc7.png)

这时分割为了 $2$ 份。

再画一条：

![](https://cdn.luogu.com.cn/upload/image_hosting/gtnrdpu4.png)

这时变成了 $3$ 份，注意到这时只增加了 $1$，而第一次增长了 $2$，所以考虑将画第一条时单独提出来特殊考虑，作为起始状态。

再画一条呢？

![](https://cdn.luogu.com.cn/upload/image_hosting/gbt2yq7w.png)

会发现这时出现了一个交点，那么增长量将变为 $2$。

这时我猜测**每过一圈 $d$ 就增加 $1$。**

再画一条：

![](https://cdn.luogu.com.cn/upload/image_hosting/2jzq928f.png)

交点又增加了一个！那么我们上面的假设就被否决了！这时我们提出新的规律：**每经过一圈，$d$ 将在接下来的两次操作中逐渐增加 $1$。**

但是很快我发现这个结论也是错的，当 $n = 17,k = 3$ 时就可以推翻，因为将 $16$ 号点和 $2$ 号点时 $d$ 已经增加 $1$ 了，因为必定会和 $1$ 号点连出去的线段相交。

![](https://cdn.luogu.com.cn/upload/image_hosting/nmsbdhe4.png)

那么经过一堆完善后，设现在分割的份数为 $base$，结论如下：

1. 若当前连的边未跨过 $n$ 号点，$base\leftarrow base + d$；
2. 否则若当前连的边的较大的端点刚好为 $n$，$base\leftarrow base + d$ 并且 $d$ 将在**本次操作后的两次操作内**逐渐增大 $1$；
3. 否则就只剩下较大的端点超过 $n$ 的情况了，先 $d\leftarrow d + 1$，再 $base \leftarrow base + d$，并且 $d$ 将在**本次操作后的一次操作内**逐渐增大 $1$。

还没结束，万一 $k\ge \frac{n}{2}$ 呢？这会直接导致 $d$ 的增长过程还没结束就会再次接受增长的信号吗？

实际上，我们~~不难~~发现连边是具有对称性的，所以若 $k\ge \frac{n}{2}$ 直接令 $k\leftarrow n - k$ 就行了。

代码没什么好讲的，就是根据结论模拟，时间复杂度 $O(n)$。

代码是直接由考场代码改过来的。

$\texttt{Code:}$

```cpp
#include <set>
#include <cstring>
#include <iostream>

using namespace std;

const int N = 1000010;
typedef long long ll;
int T;
int n, k;

void solve() {
    scanf("%d%d", &n, &k);
    if(k > n / 2) k = n - k;
    int x = k % n + 1, lasx = 1;
    ll res = 0, base = 2;
    int d = 1;
    int flag = -1; // flag 表示还有几次操作后 d 会 +1，相当于一个延时标记
    for(int i = 1; i < n; i++) {
        printf("%lld " , base);
        if(~flag) flag--;
        if(!flag) d++, flag = -1;
        if(x + k > n && flag == -1) {
            if(i != n - 1) d++;
            base += d;
            flag = 1;
            lasx = x, x = (x + k - 1) % n + 1;
        }
        else if(x + k == n) {
            base += d;
            d++;
            flag = 2;
            lasx = x, x = (x + k - 1) % n + 1;
        }
        else {
            base += d;
            lasx = x, x = (x + k - 1) % n + 1;
        }
        res ^= (ll)i * base;
    }
    printf("%lld\n", base);
}

int main() {
    T = 1;
    while(T--) {
        solve();
    }
    return 0;
}
```

---

## 作者：Windy_Hill (赞：2)

## 题意
给你一个 $n$ 边形，每隔 $k - 1$ 个点连一条边，问每次连完边后，$n$ 边形内有多少个区域。

## 思路
首先模拟一下样例1。

![](https://cdn.luogu.com.cn/upload/image_hosting/k33k9u5j.png)

第一次做完后，蓝色的边是我们刚连的，没有红边与其相交。

![](https://cdn.luogu.com.cn/upload/image_hosting/b14t0z5y.png)

第二次做完后，蓝色的边是我们刚连的，没有红边与其相交。

![](https://cdn.luogu.com.cn/upload/image_hosting/5i6ldv10.png)

第三次做完后，蓝色的边是我们刚连的，有 ```1``` 条红边与其相交。

![](https://cdn.luogu.com.cn/upload/image_hosting/fw1ubjl1.png)

第四次做完后，蓝色的边是我们刚连的，有 ```2``` 条红边与其相交。

![](https://cdn.luogu.com.cn/upload/image_hosting/ta2935sd.png)

第五次做完后，蓝色的边是我们刚连的，有 ```2``` 条红边与其相交。

再分析一下样例。

``` 2 3 5 8 11 ```

相邻两个的差是

``` 1 1 2 3 3 ```

注：第一个是与没连时候的差。

那实际上每次所加的数是与连接过的边相交的数加一。

我们可以将这个图压平再来看一下。

没做：
``` 0 0 0 0 0 ```

做了一次之后：
``` 1 0 1 0 0 ```

做了两次之后：
``` 1 0 2 0 1 ```

做了三次之后：
``` 1 1 2 0 2 ```

做了四次之后：
``` 1 2 2 1 2 ```

做了五次之后：
``` 2 2 2 2 2  ```

每次如果跨回去了那就要再加上一个做过次数的总和。

否则就加上两点之差。

注意：如果 $k > \frac{n}{2}$ ，那么就要将 $k$ 变为 $n - k$。

## 代码
```cpp
#include <bits/stdc++.h>

#define int long long 

using namespace std;

int n, m;
int tr[1000010];

//树状数组
int lowbit(int x)
{
    return x & -x;
}

void update(int x, int c)  
{
    for (int i = x; i <= n; i += lowbit(i)) tr[i] += c;
}

int query(int x)  
{
    int res = 0;
    for (int i = x; i; i -= lowbit(i)) res += tr[i];
    return res;
}

signed main()
{
    cin >> n >> m;
    m = min(m, n - m);
    
    int res = 1;//一开始就有一个区域
    int x = 1;
    for (int i = 1; i <= n; i ++ )
    {
        int y = x + m;
        res ++ ;
        if (y > n) y -= n, res += query(n) + query(y - 1) - query(x);//如果跨了点1
        else res += query(y - 1) - query(x);//没跨点1
        update(x, 1), update(y, 1);
        x = y, cout << res << " ";
    }
    
    return 0;
}
```

---

## 作者：是个汉子 (赞：2)

[洛谷传送门](https://www.luogu.com.cn/problem/CF755D)	[CF传送门](http://codeforces.com/problemset/problem/755/D)

### Solution

有个很显然的规律是：每次 $ans$ 增加的是所连这条边和别的边的交点数量+1

为什么呢？

可以~~性感~~感性理解

先看刚开始连第一条边的时候， $ans+=1\rightarrow ans\times 2$ ，也就相当于将多边形分成了两半，图也是这么画的

后面连的直线每和另一条直线 $k$ 进行相交，就相当于将 $k$ 前的空间一分为二

而和最后一条直线相交完，还有一片空间，也被一分二为二

~~就是这样，这个题就完了~~

问题来了，怎么维护交点？

发现题目中给的条件是 $\gcd(k,n)=1$ ，也就是不会出现重边

所以可以用一些数据结构来维护从某个点出发的直线数

举个例子：当 $u,v$ 进行连边的时候，只需要 $sum_{u,v}$ ，其中 $sum$ 为直线数的和

我这里用的是线段树（因为怕有不喜欢树状数组的同学）

小细节：使 $k=\min(k,n-k)$ 。其实是因为这样可以统一情况，不然还要分 $k>\frac n2,k\leq \frac n2$ 

### Code

```c++
#include<bits/stdc++.h>
#define ls rt<<1
#define rs rt<<1|1
#define ll long long

using namespace std;
const int N=100010;
int n,k,T;
ll ans=1;
struct node{
    ll lz,sum;
    int l,r;
}tr[N<<6];

void build(int rt,int l,int r){
    tr[rt].l=l; tr[rt].r=r;
    if(l==r) return ;
    int mid=(l+r)>>1;
    build(ls,l,mid);
    build(rs,mid+1,r);
}

inline void pushup(int rt){
    tr[rt].sum=tr[ls].sum+tr[rs].sum;
}

inline void pushdown(int rt){
    if(!tr[rt].lz) return ;
    tr[ls].lz+=tr[rt].lz;
    tr[ls].sum+=tr[rt].l*(tr[ls].r-tr[ls].l+1);
    tr[rs].lz+=tr[rt].lz;
    tr[rs].sum+=tr[rt].l*(tr[rs].r-tr[rs].l+1);
    tr[rt].lz=0;
}

void update(int rt,int L,int R,ll val){
    int l=tr[rt].l,r=tr[rt].r;
    if(L<=l&&r<=R){
        tr[rt].lz+=val;
        tr[rt].sum+=(r-l+1)*val;
        return ;
    }
    if(tr[rt].lz) pushdown(rt);
    int mid=(l+r)>>1;
    if(L<=mid) update(ls,L,R,val);
    if(R>mid) update(rs,L,R,val);
    pushup(rt);
}

ll query(int rt,int L,int R){
    int l=tr[rt].l,r=tr[rt].r;
    if(L<=l&&r<=R) return tr[rt].sum;
    ll res=0;
    if(tr[rt].lz) pushdown(rt);
    int mid=(l+r)>>1;
    if(L<=mid) res+=query(ls,L,R);
    if(R>mid) res+=query(rs,L,R);
    return res;
}

int main(){
    int last=1,now;
    scanf("%d%d",&n,&k);
    T=n;
    if(k>n/2) k=n-k;
    build(1,1,n);
    while(T--){
        now=(last+k-1)%n+1;
        if(now>last) ans+=query(1,last+1,now-1)+1;
        else ans+=query(1,last+1,n)+query(1,1,now-1)+1;
        update(1,last,last,1);update(1,now,now,1);
        last=now;
        printf("%lld ",ans);
    }
    return 0;
}
```



---

## 作者：co7ahang (赞：1)

题目：CF755D 
[洛谷](https://www.luogu.com.cn/problem/CF755D)
[Codeforces](https://codeforces.com/problemset/problem/755/D)

这是一道数据结构大水题。

打模拟赛的时候把这道题放到了 T4，做完 T1 就看这道题有思路就写出来了。

首先考虑如何暴力模拟计算答案，当每链接一条边 $(x, x + k)$ 时，被分割的区域数 $s$ 会增加 $u + 1$，其中 $u$ 是与这条边在正多边形中有交叉的线段数量。而题目保证边数（即点数）$n$ 与 $k$ 互质，说明在每一个点都被连接后才会回到初始节点，共链接 $n$ 条边。我们把每一次的连边存下来，在新的一次连边时判断有多少条边与此时的连边相交。暴力复杂度 $O(n^2)$，期望得分 $0$ 分。

考虑优化。时间复杂度的瓶颈是计算重复的边。想出了一个很奇怪的判断方法，用两颗树状数组储存每条边的左节点和右节点，由于 $k$ 是确认的，所以只用一个节点的位置就可以求出另一个节点。对于左节点与当前边 $(l, r)$ 相交时，统计左节点在区间 $[r - k + 1, r - 1]$ 的线段数量，右节点则统计 $[l + 1, l + k - 1]$。如果节点越界的话特判一下 $\pm n$ 即可。使用树状数组的话复杂度 $O(n \log n)$。

最开始要注意把 $k$ 赋值为 $\min(k, n - k)$，这两种情况是等效的，但是可以缩小一点范围防止越界。卡这个卡了很久。

懒得修的赛事代码。凑合看看就行。
```cpp
#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
#define int long long
using namespace std;
inline int read() {
	int x = 0, f = 1; char ch = getchar();
	while(ch > '9' || ch < '0') {
		if(ch == '-') f = -1; ch = getchar();
	}
	while(ch >= '0' && ch <= '9') x = (x << 3) + (x << 1) + (ch - 48), ch = getchar();
	return x * f;
}
const int N = 2e6 + 10;

typedef pair<int, int> pii;
int n, k;
priority_queue <int> E[N];
vector <pii> V;
namespace Tree {
	int vall[N], valr[N];
	int lowbit(int x) {
		return x & -x;
	}
	int queryl(int x) {
		int ans = 0;
		while(x) {
			ans += vall[x];
			x -= lowbit(x);
		}
		return ans;
	}
	void modifyl(int x, int y) {
		while(x <= n) {
			vall[x] += y;
			x += lowbit(x);
		}
	}
	int queryr(int x) {
		int ans = 0;
		while(x) {
			ans += valr[x];
			x -= lowbit(x);
		}
		return ans;
	}
	void modifyr(int x, int y) {
		while(x <= n) {
			valr[x] += y;
			x += lowbit(x);
		}
	}
}
void solve();
signed main() {
	int T; T = 1;
	while(T--) solve();
	return 0;
}
using namespace Tree;
int calc1(int l, int r) {
	//[l, r] 闭区间
    //这里可能向左越界
	if(l >= 1 && r <= n) return queryl(r) - queryl(l - 1);
	else return queryl(n) - queryl(l - 1 + n) + queryl(r);
}
int calc2(int l, int r) {
    //这里可能向右越界
	if(l >= 1 && r <= n) return queryr(r) - queryr(l - 1);
	else return queryr(n) - queryr(l - 1) + queryr(r - n);
}
int SegmentJudge(int l, int r) {
	int ans = 0;
	if(l > r) swap(l, r);
	ans += calc1(r - k + 1, r - 1);
	ans += calc2(l + 1, l + k - 1);
	return ans;
}
void solve() {
	n = read(), k = read();
	k = min(k, n - k);
	int x = 1;
	int ans = 1;
	for(int i = 1; i <= n; i++) {
		int y = (x + k > n ? x + k - n: x + k);
		// x -> x + k
		ans += SegmentJudge(x, y) + 1;
		cout << ans << " ";
		Tree::modifyl(x, 1);
		Tree::modifyr(y, 1);
		x = y;
	}
	cout << endl;
	return;
}
```

---

## 作者：JustPureH2O (赞：1)

[更好的阅读体验](https://justpureh2o.cn/articles/755)

题目地址：[CF 755D](https://www.luogu.com.cn/problem/CF755D)

> 给出一个 $n$ 边形，和距离 $k$。 第一次连接 $1$ 和 $k+1$，第二次连接 $k+1$ 和 $(k+1+k)\bmod n$，依次进行 $n$ 次，每次结束后输出 $n$ 边形被分割成了几个区域。
>
> $n,k$ 互质，$5\leq n\leq10^6$。

今天模拟赛 T2，赛时多测卡线段树加上多测没清空喜爆零。同机房还有用 $\mathcal O(n)$ 惊天地泣鬼神纯数学做法 A 的，在此表示深深膜拜。

为了取模方便，本文是 `0-index` 的。

首先，根据互质关系可得，本题无需考虑重边的情况。因为题目可以看作是 $x$ 向 $(x+k)\bmod n$ 连边，因此只有满足 $x\equiv x+\lambda k\pmod n,\lambda\in\mathbb Z$ 时才可能出现重边，这要求 $n\mid\lambda k$，而 $n\perp k$，所以 $\lambda\geq n$，且是 $n$ 的倍数时才会出现重边，对应 $n+1$ 次操作之后。本题中只考虑前 $n$ 次，因而不存在重边问题。

手搓可以发现第一个规律：$k$ 具有对称性，即 $k$ 和 $n-k$ 作为步长时的答案是相同的，只是方向相反而已。

接着研究，发现第二个规律——连边带来的贡献是当前边与已有边的相交次数加一。我们的核心任务就是维护当前边会与多少已连接的边相交。

假设当前待连的边是 $(L,R)$。仔细观察样例可发现，其实相交线段个数就是 $L$ 到 $R$（注意顺序，不是 $R$ 到 $L$）间内每个点的度数之和（多边形本身的边不计入度数）。因此对于每次操作，我们获得区间 $[L+1,R-1]$ 内所有点已经连出边的总数即可，注意特判右端点是否越过节点 $0$。贡献的产生如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/cshpg1mw.png)

线段树的常数还是很大的，建议使用树状数组（或者上边大佬的数学做法）。

```cpp
#include <bits/stdc++.h>
#define N 1000010
using namespace std;

typedef long long ll;

struct SegmentTree {
#define le(x) (x << 1)
#define ri(x) (x << 1 | 1)
#define leftSubtree(x) (tree[le(x)])
#define rightSubtree(x) (tree[ri(x)])
    int l, r, size;
    ll sum;
} tree[N << 2];

void pushup(int idx) {
    tree[idx].sum = leftSubtree(idx).sum + rightSubtree(idx).sum;
}

void build(int idx, int l, int r) {
    tree[idx].l = l, tree[idx].r = r;
    tree[idx].size = r - l + 1;
    if (l == r) return;
    int mid = (l + r) >> 1;
    build(le(idx), l, mid);
    build(ri(idx), mid + 1, r);
    pushup(idx);
}

void modify(int idx, int uid) {
    if (tree[idx].size == 1 && tree[idx].l == uid) {
        tree[idx].sum++;
        return;
    }
    int mid = (tree[idx].l + tree[idx].r) >> 1;
    if (uid <= mid) modify(le(idx), uid);
    if (uid > mid) modify(ri(idx), uid);
    pushup(idx);
}

ll query(int idx, int l, int r) {
    if (l <= tree[idx].l && tree[idx].r <= r) return tree[idx].sum;
    int mid = (tree[idx].l + tree[idx].r) >> 1;
    ll ret = 0;
    if (l <= mid) ret += query(le(idx), l, r);
    if (r > mid) ret += query(ri(idx), l, r);
    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, k;
    cin >> n >> k;
    k = min(k, n - k);
    build(1, 0, n - 1);
    int pos = 0;
    ll section = 1;
    for (int i = 1; i <= n; i++) {
        int L = (pos + 1) % n, R = (pos + k - 1 + n) % n; // 左右端点
        ll sum = R < L ? query(1, 0, R) + query(1, L, n - 1) : query(1, L, R); // 获得区间内每个点连出去多少条边，注意判断是否跨过节点 0
        modify(1, pos); // 为当前的线段端点累加 1
        modify(1, (pos + k) % n);
        section += sum + 1; // 图形总数
        pos = (pos + k) % n; // 跳到下一个位置
        cout << section << ' ';
    }

    return 0;
}
```

[AC 记录](https://codeforces.com/contest/755/submission/293491375)

$\texttt{The End}$

---

## 作者：abensyl (赞：1)

原题：[CF755D PolandBall and Polygon](https://www.luogu.com.cn/problem/CF755D)。

好题，思维与数据结构的完美结合。

## 思路

注明：在以下的所有描述中，两根线段相较于端点处，我们不称它们相交，仅在线段中部产生交点我们才称它们相交。

首先，如果没有交线，那么每一次分割都是把原本的图形分成两半，也就是将块数加一。

那么，如果一条线和其他现有一个交点，就会再加一，类似的，如果和其他的 $n$ 根线产生了 $n$ 个交点，就会增加 $n+1$ 个块数（因为即便没有交点也会加一）。

那么，我们要解决的问题就是，画每根线的时候，能和其他的线产生多少交点。

可以自己构造一组样例，以 $n=7$ 和 $k=3$ 为例，手动模拟样例，发现前两次操作都只是在原先的基础上加一，没有产生任何交点，第二此操作后答案为 $3$，图形大致如下：

![](https://www.mfstem.org/file/241/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202023-12-03%20092641.png)

当连接下一条边，从 $7$ 连到 $3$ 的时候，就会和线段 $1\rightarrow 4$ 产生一个交点，所以块数增加 $2$，变为 $5$，大致如下图：

![](https://www.mfstem.org/file/241/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202023-12-03%20094429.png)

再连接一条边的时候，从 $3$ 到 $6$ 会和两条线段产生交点，很显然的可以发现，产生的交点个数就是 $3$ 顺时针转到 $6$ 所经过所有点的边的数量。

![](https://www.mfstem.org/file/241/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202023-12-03%20094609.png)

那么，我们就大致的得到了做法，只要知道本次连边的两点间的所有点的度数和即可，显然地，这个操作可以用树状数组维护。

**注意点：**

- 需要开 long long；  
- $k$ 要先对 $n$ 取模，因为转很多圈相当于一圈没转；
- 如果 $k>{n\over 2}$，那么 $k$ 应当赋值为 $n-k$，因为顺时针转 $k$ 和逆时针转 $n-k$ 是本质相同的，如果不进行这个操作会导致 WA。

## 代码
```cpp
#include <bits/stdc++.h>
#define int long long
#define lowbit(i) (i&-i)
using namespace std;
const int N = 1e6 + 5;
int tr[N];
void update(int u,int x) {
	for(int i=u;i<N;i+=lowbit(i)) tr[i]+=x;
}
int query(int u) {
	int res=0;
	for(int i=u;i;i-=lowbit(i)) res+=tr[i];
	return res;
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr),
	cout.tie(nullptr);
	int n,k;
	cin>>n>>k;
	k%=n;
	if(k>n/2) k=n-k;
//	cerr<<n<<' '<<k<<'\n';
	int id=1;
	long long res=1,lst=1;
	for(int i=1;i<=n;++i) {
		int nxt=lst+k;
		if(nxt>n) nxt=nxt-n;
//		cerr<<lst<<' '<<nxt<<' ';
		res++;
		if(nxt<lst) {
			res+=query(n)-query(lst);
			res+=query(nxt-1);
		} else {
			res+=query(nxt-1)-query(lst);
		}
		update(lst,1);
		update(nxt,1);
		cout<<res<<' ';
//		cerr<<'\n';
		lst=nxt;
	}
	return 0;
}
```

---

## 作者：__Hacheylight__ (赞：1)

Codeforces 755D PolandBall and Polygon 题解

题意：

给你一个n边行，每次让你将x与(x+k)%n的点连一条边，每次询问该多边形内面积被划分成了几块

分析：

我们发现这个输出很有规律，但是规律好像不是很好找。

于是我们考虑其他方法。

根据样例分析的图画，我们发现：

1.前两幅图只对答案做出了1的贡献

2.第3幅图对答案做出了2的贡献，且他连出的边与边（1，3）有交点；

3.图4,5都对答案做出了3的贡献，且有两个交点；

根据这个发现，我们大胆的推断出了结论：每条边对答案的贡献是与他的交点的个数+1

那么怎么算交点个数呢？

题目给了我们一个台阶，他告诉我们n与k互质且k不变，

于是不会出现重边或边包含边的问题，于是我们的问题就转化成了维护x到(x+k)%n中的点延伸出的边的数量（这些边必与本边相交），这个可以通过任何一种数据结构维护，like树状数组

注意两个细节：

1.k = min(k, n - k)

2.long long

分类讨论搞一下就AC了吧。

代码： //一大堆头文件不要管

```cpp
#include <map>
#include <set>
#include <cmath>
#include <ctime>
#include <queue>
#include <stack>
#include <vector>
#include <bitset>
#include <cstdio>
#include <cctype>
#include <string>
#include <cstring>
#include <cassert>
#include <climits>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <functional>
using namespace std ;

#define rep(i, a, b) for (int (i) = (a); (i) <= (b); (i)++)
#define Rep(i, a, b) for (int (i) = (a) - 1; (i) < (b); (i)++)
#define REP(i, a, b) for (int (i) = (a); (i) >= (b); (i)--)
#define clr(a) memset(a, 0, sizeof(a))
#define Sort(a, len, cmp) sort(a + 1, a + len + 1, cmp)
#define ass(a, sum) memset(a, sum, sizeof(a))

#define ls ((rt) << 1)
#define rs ((rt) << 1 | 1)
#define lowbit(x) (x & -x)
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define endl '\n'
#define ENDL cout << endl
#define SZ(x) ((int)x.size())

typedef long long ll ;
typedef unsigned long long ull ;
typedef vector <int> Vi ;
typedef pair <int, int> Pii ;
typedef pair <ll, ll> Pll ;
typedef map <int, int> mii ;
typedef map <string, int> msi ;
typedef map <ll, ll> mll ;

const int N = 1000100 ;
const double eps = 1e-8 ;
const int iinf = INT_MAX ;
const ll linf = 2e18 ;
const double dinf = 1e30 ;
const int MOD = 1000000007 ;

inline int read(){
    int X = 0, w = 0 ;
	char ch = 0 ;
    while (!isdigit(ch)) { w |= ch == '-' ; ch = getchar() ; }
    while (isdigit(ch)) X = (X << 3) + (X << 1) + (ch ^ 48), ch = getchar() ;
    return w ? - X : X ;
}

void write(int x){
     if (x < 0) putchar('-'), x = - x ;
     if (x > 9) write(x / 10) ;
     putchar(x % 10 + '0') ;
}

void print(int x) {
	cout << x << endl ;
	exit(0) ;
}

void PRINT(string x) {
	cout << x << endl ;
	exit(0) ;
}

void douout(double x){
	 printf("%lf\n", x + 0.0000000001) ;
}

int n, k, now, to ;
ll ans ;
int bit[N] ;

void add(int a, int x) {
	for (; a <= n; a += lowbit(a)) bit[a] += x ;
}

int sum(int a) {
	int res = 0 ;
	for (; a; a -= lowbit(a)) res += bit[a] ;
	return res ;
}

signed main(){
	scanf("%d%d", &n, &k) ;
	k = min(k, n - k) ;
	now = 1 ;
	ans = 1 ;
	for (int i = 1; i <= n; i++) {
		to = now + k ;
		ans++ ;
		if (to > n) {
			to -= n ;
			ans += sum(n) - sum(now) + sum(to - 1) ;
		}
		else {
			ans += sum(to - 1) - sum(now) ;
		}
		add(now, 1) ;
		add(to, 1) ;
		now = to ;
		printf("%lld ", ans) ;
	}
}

/*
写代码时请注意：
	1.是否要开Long Long？数组边界处理好了么？
	2.实数精度有没有处理？
	3.特殊情况处理好了么？
	4.做一些总比不做好。
思考提醒：
	1.最大值和最小值问题可不可以用二分答案？
	2.有没有贪心策略？否则能不能dp？
*/

```


---

## 作者：Suiseiseki (赞：1)

这道题，emmm~

其实探规可能更简单一些，只是我懒得想了。

那么就暴力地用树状数组做呗。

对于两个点，我们算出它们之间的连线与其他连线的交点个数为$x$

那么这一次的答案$ans=$上一次的答案$last\_ans+1+x$

那么怎么求呢？区间查询，单点更改，很明显的一个树状数组啊。
```cpp
#include <cstdio>
#include <iostream>
using namespace std;
#define ll long long
#define Maxn 1000000
ll f[Maxn+5];
int n,k;
void add(int x,int a){
	for(int i=x;i<=n;i+=(i&(-i))){
		f[i]+=a;
	}
}
ll query(int x){
	ll ans=0;
	for(int i=x;i>0;i-=(i&(-i))){
		ans+=f[i];
	}
	return ans;
}
ll sum(int left,int right){
	return query(right)-query(left-1);
}
int main(){
	scanf("%d%d",&n,&k);
	if(k>(n>>1)){
		k=n-k;
	}
	int start=1,end;
	ll ans=1;
	for(int i=1;i<=n;i++){
		end=(start+k-1)%n+1;
		if(start>end){
			ans+=1+sum(start+1,n)+sum(1,end-1);
		}
		else{
			ans+=1+sum(start+1,end-1);
		}
		add(start,1);
		add(end,1);
		start=end;
		cout<<ans<<" ";
	}
	puts("");
	return 0;
}
```


---

## 作者：shinzanmono (赞：0)

对于 $k\geq \frac{n}2$，令 $k\leftarrow n-k$，因为连边是具有对称性的。

考虑连边 $(l,r)$ 的贡献是什么，答案是中间有的空白段的个数。也就是中间的线段数 $+1$，由于二者有边当且仅当 $dis=k$，所以中间的任意两点一定没有边，即中间点的度数和几位所求。

问题转换为单点加区间求和，树状数组板子解决。

---

## 作者：xuan_gong_dong (赞：0)

## 题解
[PolandBall and Polygon](https://www.luogu.com.cn/problem/CF755D)
## 分析
有点离谱，两千分的氵题。

建议手玩一下两个样例，发现每次增加的值就是这条线的出边再 $+1$，换句话说，就是这个线段包含的所有点所连出去边 $+1$。容易证明不会有一个边一个边包含另一个边。

然后其实就出来了，本质就是单点修改区间查询 $sum$。直接用线段树就好了，复杂度是 $O(n \log n)$。

注意一个细节就是 $k$ 如果大于 $n$，取 $n-k$。
## Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct node
{
	int l,r;
	int sum;
	int lazy;
}tree[4000010];
int n,k;
int a[1000010];
void build(int id,int l,int r)
{
	tree[id].l=l;
	tree[id].r=r;
	if(l==r)
	{
		tree[id].sum=a[l];
		return;
	}
	int mid=(l+r)/2;
	build(id*2,l,mid);
	build(id*2+1,mid+1,r);
	tree[id].sum=tree[id*2].sum+tree[id*2+1].sum;
}
void updata(int id,int x)
{
	if(tree[id].l==x&&tree[id].r==x)
	{
		tree[id].sum++;
		return;
	}
	int mid=(tree[id].l+tree[id].r)/2;
	if(mid>=x)
		updata(id*2,x);
	else if(mid<x)
		updata(id*2+1,x);
	tree[id].sum=tree[id*2].sum+tree[id*2+1].sum;	
}
int query1(int id,int l,int r)
{
	if(tree[id].l==l&&tree[id].r==r) 
		return tree[id].sum ;
	int mid=(tree[id].l+tree[id].r)/2;
	if(mid>=r)
		return query1(id*2,l,r);
	else if(mid<l)
		return query1(id*2+1,l,r);
	else
		return query1(id*2,l,mid)+query1(id*2+1,mid+1,r);		
}
signed main()
{
	scanf("%lld%lld",&n,&k);
	k=min(k,n-k);
	build(1,1,n);
	int id=1;
	int sum=1;
	for(int i=1;i<=n;i++)
	{
		updata(1,id);
		int to=id+k;
		if(to>n)to-=n;
		updata(1,to);
		if(to>id)
			sum+=query1(1,id+1,to-1);
		else
		{
			if(id<n)
			sum+=query1(1,id+1,n);
			if(to>1)
			sum+=query1(1,1,to-1);
		}
		sum++;
		id=to;
		printf("%lld ",sum);
	}
	return 0;
}
```


---

## 作者：MILLOPE (赞：0)


## 题目描述

PolandBall has such a convex polygon with n*n* veritces that no three of its diagonals intersect at the same point. PolandBall decided to improve it and draw some red segments.

He chose a number k*k* such that $gcd(n,k)=1$ . Vertices of the polygon are numbered from $1$ to $n$ in a clockwise way. PolandBall repeats the following process $n$ times, starting from the vertex $1$ :

Assume you've ended last operation in vertex $x$ (consider $x=1$ if it is the first operation). Draw a new segment from vertex x$ to k$ -th next vertex in clockwise direction. This is a vertex $x+k$ or $x+k-n$ depending on which of these is a valid index of polygon's vertex.

Your task is to calculate number of polygon's sections after each drawing. A section is a clear area inside the polygon bounded with drawn diagonals or the polygon's sides.

## 输入格式

There are only two numbers in the input: $n,k$( $5<=n<=10^{6}$, $2<=k<=n-2$ , $gcd(n,k)=1$ ).

## 输出格式

You should print $n$ values separated by spaces. The $i -th$ value should represent number of polygon's sections after drawing first $i$ lines.

## 题意翻译

给出一个$n$边形，和距离$k$。 第一次连接$1$和 $k+1$，第二次连接$k+1$和$(k+1+k)%n$，依次进行$n$次，每次结束后输出$n$边形被分割成了几个区域。

## 输入输出样例

输入 #1

```
5 2
```

输出 #1

```
2 3 5 8 11 
```

输入 #2

```
10 3
```

输出 #2

```
2 3 4 6 9 12 16 21 26 31 
```

## 说明/提示

The greatest common divisor (gcd) of two integers a*a* and b*b* is the largest positive integer that divides both a*a* and b*b* without a remainder.

For the first sample testcase, you should output "$2 \  3 \ 5 \ 8 \ 11$". Pictures below correspond to situations after drawing lines.

![img](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9jZG4ubHVvZ3UuY29tLmNuL3VwbG9hZC92anVkZ2VfcGljL0NGNzU1RC80OTkwYmQzYzBjN2RkNTgzNmZkY2M1NzlmOTcwZGNkY2E4ZGJkODcyLnBuZw?x-oss-process=image/format,png)![img](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9jZG4ubHVvZ3UuY29tLmNuL3VwbG9hZC92anVkZ2VfcGljL0NGNzU1RC82NDUxZWY5NWRiOTY0NmYyNzViYTNlYzc5ZGEyYThkNWIwYjAyOGQwLnBuZw?x-oss-process=image/format,png)



![img](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9jZG4ubHVvZ3UuY29tLmNuL3VwbG9hZC92anVkZ2VfcGljL0NGNzU1RC9hOGIzYzA3ODBmMjA3MzdmZWQxMmY3NDRmODNjMGYxZWFiM2Q1MzhmLnBuZw?x-oss-process=image/format,png)![img](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9jZG4ubHVvZ3UuY29tLmNuL3VwbG9hZC92anVkZ2VfcGljL0NGNzU1RC9jMjE0MDEwYTIwNWViNTFlODkxYjIzNzZhYWNlZGNiMDk0NzU0MTBlLnBuZw?x-oss-process=image/format,png)

![img](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9jZG4ubHVvZ3UuY29tLmNuL3VwbG9hZC92anVkZ2VfcGljL0NGNzU1RC9hYzJlMjY4MGRjOTYxMWFmYjMzMTY2M2EwMWM5MThlMGMwMDFlODMyLnBuZw?x-oss-process=image/format,png)



## 题解

- 对于本题，我们可以发现每多一条线它对答案的贡献是它与其他的线的交点$+1$。
- 所以我们只需统计交点即可。 
  线段可以被看作有两个点的集合，当我们新加入一条线段时，我们只需将对应两个端点的权值++，即可代表我们加入了这条线段。 
- 所以统计交线的个数也就很$easy$了。假设我们要从$l$连向$r$，我们只需计算$sum(r-1)-sum(l)$，即我们只需计算$l,r$中间点的权值和即可。 但是如果$r$的编号超过了$n$，我们就需要对$r$进行取模，这时r有可能会小于$l$，那么我们只需计算$sum(n)+sum(r-1)-sum(l)$。（对照样例的图理解一下吧）
- 注意$k$应该取$min(k,n-k)$以及要开$long \ long$

## code

```cpp
#include <bits/stdc++.h> 
using namespace std; 
const int maxn = 1e6 + 1000; 
typedef long long LL; 

int n, k; 
LL c[maxn]; 

inline int lowbit(int x) { return x & (-x); }

inline void add(int x, int val ) {
	for (; x <= n; x += lowbit(x)) c[x] += val; 
}

inline LL query(int x) {
	LL ret = 0; 
	for (; x; x -= lowbit(x)) {
		ret += c[x]; 
	}
	return ret; 
}

int main() {
	scanf("%d%d", &n, &k); 
	k = min(k, n - k); 
	LL ans = 1; int now = 1, to; 
	for (int i = 1; i <= n; ++i) {
		to = now + k; ++ans; 
		if (to > n) {
			to -= n; 
			ans += query(n) + query(to - 1) - query(now); 
		}
		else {
			ans += query(to - 1) - query(now); 
		}
		add(now, 1); add(to, 1); 
		now = to; 
		printf("%lld ", ans); 
	}
	return 0; 
}
```

---

