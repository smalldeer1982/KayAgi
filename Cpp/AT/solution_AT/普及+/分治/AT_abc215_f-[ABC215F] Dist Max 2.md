# [ABC215F] Dist Max 2

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc215/tasks/abc215_f

$ 2 $ 次元平面上の $ N $ 個の相異なる点が与えられます。点 $ i\,\ (1\ \leq\ i\ \leq\ N) $ の座標は $ (x_i,y_i) $ です。

$ 2 $ つの点 $ i,j\,\ (1\ \leq\ i,j\ \leq\ N) $ の距離を $ \mathrm{min}\ (|x_i-x_j|,|y_i-y_j|) $ 、すなわち $ x $ 座標の差と $ y $ 座標の差の小さい方と定義します。

異なる $ 2 $ つの点の距離の最大値を求めてください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 200000 $
- $ 0\ \leq\ x_i,y_i\ \leq\ 10^9 $
- $ (x_i,y_i) $ $ \neq $ $ (x_j,y_j) $ $ (i\ \neq\ j) $
- 入力は全て整数である。

### Sample Explanation 1

点 $ 1 $ と点 $ 2 $ の距離は $ 2 $ 、点 $ 1 $ と点 $ 3 $ の距離は $ 4 $ 、点 $ 2 $ と点 $ 3 $ の距離は $ 1 $ です。よって $ 4 $ を出力してください。

## 样例 #1

### 输入

```
3
0 3
3 1
4 10```

### 输出

```
4```

## 样例 #2

### 输入

```
4
0 1
0 4
0 10
0 6```

### 输出

```
0```

## 样例 #3

### 输入

```
8
897 729
802 969
765 184
992 887
1 104
521 641
220 909
380 378```

### 输出

```
801```

# 题解

## 作者：白简 (赞：13)

二分答案。

一般来说找最大值的最小，最小值的最大一般都是二分答案。

我们二分的是 $\mathrm{min}\ (\left| x_i-x_j \right|,\left| y_i-y_j \right|)$，假设现在枚举到 $mid$，那么合法的条件是 $\mathrm{min}\ (\left| x_i-x_j \right|,\left| y_i-y_j \right|) \geq mid$，即 $\left| x_i - x_j \right| \geq mid$ 且 $\left| y_i - y_j \right| \geq mid$。

我们可以把所有点按照 $x$ 从小到大排序，然后我们可以用双指针维护。

先定位右指针位置，使得 $x_r - x_l \geq mid$，然后开始移动左指针，并时刻根据 $x_r - x_l$ 的值移动右指针，这一步就保证了 $\left| x_i - x_j \right| \geq mid$。

两个指针位置确定时，找到左指针左侧和右指针右侧区间的的 $y$ 的最大值、最小值，判断二者相减值是否合法。

---

## 作者：zhujiangyuan (赞：2)

补一下去年集训的题目。

[[ABC215F] Dist Max 2](https://www.luogu.com.cn/problem/AT_abc215_f)

AtCoder Problems 评分：$\color{Blue}{1853}$。

看到最小值最大，考虑二分答案。

先按横坐标从小到大排序，横坐标相同按纵坐标从小到大排序。

二分一个答案 $mid$，考虑双指针进行 check。$l$ 为双指针维护的左端点，$r$ 为右端点，首先跳 $r$ 保证 $\left| x_r - x_l\right| \ge mid$ **始终成立**。再跳 $l$ 记录 $y_l$ 的最小值与最大值。对于每个 $r$，当 $l$ 不能再跳的时候比较一下 $y_l$ 的最小值和最大值与 $y_r$ 的差值是否大于等于 $mid$，如果是，返回 $1$。当 $r$ 跳到 $n$ 时还没有返回，返回 $0$。

check 代码：
```cpp
bool check (LL delta)
{
	LL minv = 1e14, maxv = 0;
	for (int l = 1, r = 1; r <= n; r++)
	{
		while (l < r && a[r].x - a[l].x >= delta)
		{
			minv = min (minv, a[l].y);
			maxv = max (maxv, a[l].y);
			l++;
		}
		if (maxv - a[r].y >= delta) return true;
		if (a[r].y - minv >= delta) return true;
	}
	return false;
}
```

二分代码：
```cpp
LL l = 0, r= 1e14;
while (l < r)
{
	LL mid = (l + r + 1) >> 1;
	if (check(mid)) l = mid;
	else r = mid - 1;
}
printf("%lld", l);
```

[完整代码](https://atcoder.jp/contests/abc215/submissions/51990102)，时间复杂度 $O(n\log V)$，$V$ 为 $x,y$ 的值域。

---

## 作者：Tx_Lcy (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc215_f)

## 思路

简单题，考虑二分答案。

我们只需要按左端点排序，然后维护一个大根堆，一个小根堆，然后暴力扫一遍，判断一下即可。

具体 $\verb!check!$ 的过程是先把所有 $|x_i-x_j| \le x$ 的 $j$ 都扫进去，然后维护一个最大的 $y_j$，最小的 $y_j$，然后判断一下是否有一个与 $y_i$ 的差值 $\ge x$ 即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int const N=1e6+10;
int n;
struct node{int x,y;}a[N];
inline bool cmp(node a,node b){return a.x<b.x;}
inline bool check(int x){
    int l=0,j=0;while (a[j].x-a[1].x<x && j<=n) ++j;
    if (j>n) return 0;
    priority_queue<int>q;
    priority_queue< int,deque<int>,greater<int> >qq;
    for (int i=j;i<=n;++i){
        while (abs(a[i].x-a[l+1].x)>=x && l+1<=i) ++l,q.push(a[l].y),qq.push(a[l].y);
        if (abs(q.top()-a[i].y)>=x || abs(qq.top()-a[i].y)>=x) return 1;
    }
    return 0;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin>>n;
    for (int i=1;i<=n;++i) cin>>a[i].x>>a[i].y;
    sort(a+1,a+n+1,cmp);
    int l=0,r=1e9;
    while (l<r){
        if (l+1==r){
            if (check(r)) l=r;
            break;
        }
        int mid=(l+r)>>1;
        if (check(mid)) l=mid;
        else r=mid-1;
    }
    cout<<l<<'\n';
    return 0;
}
```


---

## 作者：sad_lin (赞：0)

看到题目要求答案最大值最小，直接就是考虑二分答案。

然后最重要的是如何判断答案是否合法呢，我们先按 $x$ 坐标从小到大排序，然后我们双指针，我们的右指针 $r$ 不断向后扫，直到 $x_r-x_l\ge mid$ 说明存在不合法的可能，此时右移左指针，同时记录扫过的 $y$ 坐标的最大值与最小值.

因为只有我们 $x$ 坐标不合法时才开始判断 $y$ 坐标是否合法，已经没有试错的机会，所以如果 $y_l$ 的最大值与最小值与 $y_r$ 的差值超过了 $mid$ 就直接返回 $0$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+10;
const int mod=1e9+7;
#define ll long long
#define int ll

int n;

struct ss{
	int x,y;
}a[N];

bool cmp(ss g,ss h){
	if(g.x==h.x){
		return g.y<h.y;
	}
	return g.x<h.x;
}

int check(int mid){
	int mx=0,mi=1e14;
	for(int l=1,r=1;r<=n;r++){
		while(l<r&&a[r].x-a[l].x>=mid){
			mx=max(mx,a[l].y);
			mi=min(mi,a[l].y);
			l++;
		}
		if(mx-a[r].y>=mid||a[r].y-mi>=mid) return 0;
	}
	return 1;
}

signed main(){
	ios::sync_with_stdio(false);
//	cin.tie(nullptr);
	
	cin>>n;
	
	for(int i=1;i<=n;i++){
		cin>>a[i].x>>a[i].y; 
	}
	
	sort(a+1,a+n+1,cmp);
	
	int l=0,r=1e14,mid,ans=r;
	
	while(l<=r){
		mid=(l+r)>>1;
		if(check(mid)){
			r=mid-1;
		}
		else{
			l=mid+1;
			ans=mid;
		}
	}
	cout<<ans;	
    return 0;
}
```

---

## 作者：ttq012 (赞：0)

对于二维问题一般考虑把二维问题转换成一维问题。

那么首先把所有点按照 $x$ 坐标从小到大排序。

然后二分答案。设当前二分到了 $p$ 那么就是要求 $\min(|x_i-x_j|, |y_i-y_j|)\ge p$。

然后用双指针来维护。由于 $x$ 一定单调递增了，所以维护两个指针 $l$ 和 $r$ 满足 $x_r-x_l\ge p$。

对于每一个用双指针找到的最小区间 $[l,r]$，把 $l$ 往左移动，把 $r$ 往右移动，必然继续满足 $x$ 方向的条件。所以用一个线段树维护区间的最大值和最小值，找到 $[1,l]$ 和 $[r,n]$ 两端区间 $y$ 方向的最大值和最小值，判断一下答案是否合法即可。

时间复杂度是 $O(n\log^2n)$ 的，其中二分部分时间复杂度是 $O(\log n)$ 的，判断答案部分时间复杂度是 $O(n\log n)$ 的。

可能是一个比较新颖的做法？

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 10;
struct Node
{
    int x, y;
} z[N];
int n;
bool operator<(const Node &lhs, const Node &rhs)
{
    return lhs.x < rhs.x || lhs.x == rhs.x && lhs.y < rhs.y;
}
struct Sgtn
{
    int l, r;
    int mx, mi;
    Sgtn() { l = r = mx = 0; mi = 1e12; }
    void init(int p)
    {
        l = r = p;
        mx = mi = z[p].y;
    }
} zz[N << 2];
Sgtn operator+(const Sgtn &lhs, const Sgtn &rhs)
{
    Sgtn res;
    res.l = lhs.l, res.r = rhs.r;
    res.mx = max(lhs.mx, rhs.mx);
    res.mi = min(lhs.mi, rhs.mi);
    return res;
}
void build(int l, int r, int rt)
{
    if (l == r)
        zz[rt].init(l);
    else
    {
        int mid = l + r >> 1;
        build(l, mid, rt << 1);
        build(mid + 1, r, rt << 1 | 1);
        zz[rt] = zz[rt << 1] + zz[rt << 1 | 1];
    }
}
Sgtn query(int l, int r, int rt, int nowl, int nowr)
{
    if (nowl <= l && r <= nowr)
        return zz[rt];
    int mid = l + r >> 1;
    if (nowl > mid)
        return query(mid + 1, r, rt << 1 | 1, nowl, nowr);
    if (mid >= nowr)
        return query(l, mid, rt << 1, nowl, nowr);
    return query(l, mid, rt << 1, nowl, nowr) + query(mid + 1, r, rt << 1 | 1, nowl, nowr);
}
int querymax(int l, int r)
{
    return query(1, n, 1, l, r).mx;
}
int querymin(int l, int r)
{
    return query(1, n, 1, l, r).mi;
}
bool check(int p)
{
    int l = 1, r = 1;
    while (l <= n && r <= n)
    {
        while (r <= n && z[r].x - z[l].x < p)
            r++;
        if (r <= n)
        {
            int ql1x = querymax(1, l), ql1n = querymin(1, l);
            int ql2x = querymax(r, n), ql2n = querymin(r, n);
            if (abs(ql1x - ql2n) >= p || abs(ql2x - ql1n) >= p)
                return true;
        }
        l++;
    }
    return false;
}
signed main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> z[i].x >> z[i].y;
    sort(z + 1, z + n + 1);
    build(1, n, 1);
    int l = 0, r = 1e9, best = -1;
    while (l <= r)
    {
        int mid = l + r >> 1;
        if (check(mid))
            best = mid, l = mid + 1;
        else
            r = mid - 1;
    }
    cout << best << '\n';
    return 0;
}

```

---

## 作者：cqbzrjx (赞：0)

# 分析

看到最小最大值此类问题时。就可以想到用二分答案 $mid$，但是需要找到一对点 $i$ 和 $j$ 满足 $\min \left(\left|x_{i}-x_{j}\right|,\left|y_{i}-y_{j}\right|\right) \geq  mid$。

# 做法

于是可以先按照 $x$ 从小到大排序，然后从左到右遍历点 $j$，所以对于任意满足 $x_{j}-x_{i} \geq mid$ 的点 $i$ 都是备选点。

此时可知在点 $1$ 到点 $i$ 中，如果存在某个点 $k$ 满足 $|y_{j}-y_{k}| \geq mid$ 就有解。

然后发现只需要维护可选点中纵坐标 $y$ 的前缀最小值和前缀最大值即可。

```cpp
bool check (mid)//双指针
for j: 1 -> N	//保持 (x_j - x_i >= mid)
    i = max{k | x_j - x_k >= mid}
	miny = min{y_k | 1 <= k <= i}
	maxy = max{y_k | 1 <= k <= i}
    if (y_j - miny >= val || maxy - y_j >= val) return true;
return false;
```

复杂度分析是 $O(n \log V)$，其中 $V$ 为值域。


# AC code
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
struct Node{
    int x, y;
} a[N];
bool cmp(Node t1, Node t2){
    return t1.x < t2.x;
}
int n;
bool check(int x){
    int maxn = INT_MIN, minn = INT_MAX;
    for(int i = 1, j = 1; i <= n; i++){
        while(j < i && a[i].x - a[j].x >= x){
            maxn = max(maxn, a[j].y);
            minn = min(minn, a[j].y);
            j++;
        }
        if(maxn >= a[i].y + x)return true;
        if(minn <= a[i].y - x)return true;
    }
    return false;
}
int main()
{
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> a[i].x >> a[i].y;
    sort(a + 1, a + 1 + n, cmp);
    int L = 0, R = 1e9 + 10;
    while(L + 1 < R){
        int M = (L + R) >> 1;
        if(check(M)) L = M;
        else R = M;
    }
    cout << L << endl;
    return 0;
}
```

---

## 作者：封禁用户 (赞：0)

### 二分答案。

首先，我们可以假设任意两个点之间的距离最大值为 $d$。那么对于任意两个点 $i$ 和 $j$，如果它们之间的距离小于等于 $d$，那么它们一定满足以下条件之一：

- $\left | x_i-x_j \right |\leqslant d$ 且 $\left | y_i-y_j \right |\leqslant d$

- $\left | x_i-x_j \right |\leqslant d$ 且 $\left | y_i-y_j \right |> d$

- $\left | x_i-x_j \right |> d$ 且 $\left | y_i-y_j \right |\leqslant d$

因此，我们可以枚举每一对满足条件 $1$ 或 $2$ 的点，然后检查它们之间的距离是否小于等于 $d$。具体来说，我们可以先将所有点按照 $x$ 坐标排序，然后对于每个点 $i$，只需要在其右侧 $x$ 坐标小于等于 $x_i+d$ 的点中找到 $y$ 坐标与 $y_i$ 的差的绝对值小于等于 $d$ 的点即可。时间复杂度为 $O(N \log N)$。

按照 $y$ 坐标排序同理。对于每个点 $i$，在其上方 $y$ 坐标小于等于 $y_i+d$ 的点中找到 $x$ 坐标与 $x_i$ 的差的绝对值小于等于 $d$ 的点。时间复杂度也为 $O(N \log N)$。

综上，总的时间复杂度为 $O(N \log N\times \log W)$，其中 $W$ 是坐标范围。我们可以使用二分答案来确定最大距离 $d$ 的值，然后检查是否存在两个点之间的距离大于等于 $d$。二分的上界是坐标范围中的最大值，下界可以设为 $0$。

### AC code
```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
struct node{
	int x,y;
}Point[200005];
bool cmp(node a,node b){
	return a.x<b.x;
}
int y_min[200005],y_max[200005];
bool check(int mid){
	for(int i=0,j=1;j<=n;j++){
		while(Point[j].x-mid>=Point[i+1].x) i++;
		if(i==0) continue;
		if(abs(y_min[i]-Point[j].y)>=mid || abs(y_max[i]-Point[j].y)>=mid) return 1;
	}
	return 0;
}
int main(){
	cin >> n;
	for(int i=1;i<=n;i++){
		cin >> Point[i].x >> Point[i].y;
	}
	sort(Point+1,Point+n+1,cmp);
	y_min[0]=INT_MAX;
	for(int i=1;i<=n;i++){
		y_min[i]=min(y_min[i-1],Point[i].y);
		y_max[i]=max(y_max[i-1],Point[i].y);
	}
	int l=0,r=1e9;
	while(l<r){
		int mid=(l+r+1)/2;
		if(check(mid)) l=mid;
		else r=mid-1;
	}
	cout << l;
	return 0;
}
```


---

## 作者：_zzzzzzy_ (赞：0)

## 思路
首先我们要先确定这是一道二分答案题，我们就直接二分 $\min(|x_i-x_j|,|y_i-y_j|)$，也就是说 $|x_i-x_j|\le mid\;|y_i-y_j|\le mid$。

我们可以直接把横坐标排一遍序，就可以用一个双指针来维护 $|x_i-x_j|\le mid$ 然后我们对于每一个满足 $|x_i-x_j|\le mid$ 的区间求纵坐标的最大值和最小值，我们贪心的想，如果这个区间在满足横坐标的约束下越大显然是越好的，那么就只用判断纵坐标的最大最小值和 $mid$ 之差是否满足条件就行了。

```cpp
bool f(int x){
	int mx=LONG_LONG_MIN,mn=LONG_LONG_MAX;
	for(int i=1,j=1;i<=n;i++){
		while(j<i&&a[i].first-a[j].first>=x){
			mx=max(mx,a[j].second);
			mn=min(mn,a[j].second);
			j++;
		}
		if(mx-x>=a[i].second)return 1;
		if(mn+x<=a[i].second)return 1;
	}
	return 0;
}
```

这是我写的判断函数，通过分析可以知道时间复杂度是 $O(n\log 1e9)$，可以通过。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=1000000;
pair<int,int>a[maxn];
int n;
bool f(int x){
	int mx=LONG_LONG_MIN,mn=LONG_LONG_MAX;
	for(int i=1,j=1;i<=n;i++){
		while(j<i&&a[i].first-a[j].first>=x){
			mx=max(mx,a[j].second);
			mn=min(mn,a[j].second);
			j++;
		}
		if(mx>=a[i].second+x)return 1;
		if(mn<=a[i].second-x)return 1;
	}
	return 0;
}
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i].first>>a[i].second;
	}
	sort(a+1,a+1+n);
	int l=0,r=1e9,ans=0;
	while(l<=r){
		int mid=l+r>>1;
		if(f(mid))ans=mid,l=mid+1;
		else r=mid-1;
	}
	cout<<ans<<"\n";
	return 0;
}
```

---

## 作者：wangyibo201026 (赞：0)

## 前言

这道题是在一场训练中和学长一起做的，然后我们一起交流了一些奇妙的做法，感觉大有所获。

## 题目大意

给你 $n$ 个点，定义两点 $i, j$ 的距离为 $\min(|x_i - x_j|, |y_i - y_j|)$，请问，任意不相同两点的距离最大值时多少。

## 思路

为什么有那么多的 $O(n \log_2 n)$ 的解法？难道 $O(n \log_2^2 n)$ 不香吗？

我们看到最终的式子与 $x$ 和 $y$ 都有关，所以我们可以考虑一个典型的套路：先把一维给排序处理好，然后另一维再乱搞。

### 思路 $1$

我们先把 $x$ 从小到大排序好，然后我们发现此时的答案**显然**拥有单调性，如果目前答案 $ans$ 不行，那么比它小的 $ans$ 也不行。但是这个不是最主要的。

我们二分出一个 $mid$，然后我们我们发现此时的 $x$ 时拥有单调性的，这是我们人为造出来的，也就是说，对于任意的 $i > j$，都要满足 $x_i \ge x_j$。

然后我们发现，排完一维序之后再处理另一维，这明显是应该可以用权值线段树做的事情，事实也说明，可以这样。

我们考虑对于此时的每一个 $i$，如果只要有一个 $j > i, x_j - x_i \ge mid$，且 $y_j - y_i \ge mid$ 就行了，我们发现 $x_j - x_i$ 是可以用权值线段树的值域那一维解决的，而 $y_j - y_i$ 就可以直接使用查询线段树值域区间解决，查询哪一段值域呢？应该是所有 $x_j - x_i \ge mid$ 的一段值域，因为如果 $x_j - x_i < mid$，那么你 $y_j - y_i$ 就没有任何意义。

由于值域有 $10^9$ 的范围，所以要动态开点。

那么有人会问，虽然是 $O(n \log_2^2 n)$ 的，但是常数太大了！卡不过去怎么办？没关系，我们还有一种常数极小的做法。

### 思路 $2$

如果我们仔细观察上面的 $x_j - x_i$，那么我们会发现，这个东西是有单调性的！所以我们可以得到一个值 $pos$（也有可能 $pos$ 超出了 $n$，变成 $n + 1$），使得 $x_{pos} - x_i, x_{pos + 1} - x_i, ... , x_{n} - x_i$ 全部都要 $\ge mid$，这个东西肯定是连续的，所以是一段后缀，我们考虑此时我们再通过二分求出 $pos$，然后把 $pos$ 开头的一段后缀给处理一下就可以了。

所以我们现在需要求出是否有 $pos \le k \le n$，且 $y_{k} - y_i \ge mid$ 的值，我们发现，此时 $y_{k}$ 要么就是极小的，要么就是极大的，所以我们只需要满足最小的 $y_k$ 和最大的 $y_k$ 减去 $y_i$ 看是否有一个 $\ge mid$ 就可以了，这个明显就是后缀最值问题，预处理一下就完事了。

---

以上两种思路是作者认为比较好想且代码难度低的方法，虽然两种做法都可以通过优化优化到 $O(n \log n)$，但仍是两种不错且普遍适用的做法，再次讲解。如果您发现本文有什么问题，请私信作者。

---

## 作者：迟暮天复明 (赞：0)

[没说更好的阅读体验](https://www.cnblogs.com/1358id/p/15171179.html)

比赛结束后第一时间想到这个题的解法。

赛时已经想到了这是个二分，我们以此为突破口继续往下走。
考虑 $\operatorname{check}$ 函数怎么写。我们看这个 $n$ 是 $10^7$ 级别的，所以时间复杂度应该是 $O(n\log n)$，所以 $\operatorname{check}$ 函数里面可以遍历整个数组。

那我们先把原数组按照横坐标排个序扔进去做 $\operatorname{2-pointer}$ 不就可以了么。

我以 $i$ 为右端点，$j$ 为左端点，那么什么时候我们可以右移左端点？就是 $j+1$ 这个点，他的横坐标和 $i$ 的差值大于等于这个 $mid$。
那么显然如果我在 $i$ 处做到了 $j$，那么所有 $i$ 右边的点和 $j$ 的组合都是合法的，所以这个 $j$ 他就永远是合法的。

那么我们就可以记录一下已做到的 $j$ 他的纵坐标的最大值和最小值，和每一个进去的 $i$ 的纵坐标减一减，如果纵坐标之差要大于等于 $mid$，而横坐标我们已经证明了他的差值必定大于等于 $mid$，那么这个 $mid$ 就肯定是成立的。

但是这个题，如果只遍历一次那么答案可能会被漏掉，所以还得从右往左遍历一遍，此时 $j$ 是右端点，$i$ 是左端点。

---

## 作者：Trump_ (赞：0)

又是逆天二分，永远写不对边界条件 QAQ。

看见找最小值的最大值，直接鉴定为**二分答案**。

设我们现在已经枚举到 $mid$，所以我们这时必定会存在 $i, j$ 满足 $\left| x_i - x_j \right| \geq mid$ 并且满足 $\left| y_i - y_j \right| \geq mid$。

此时我们遇事不决先排序，将每个点以横坐标 $X$ 的值为关键字进行升序排序，然后维护双指针就行了。

我们的双指针 $l,r$ 表示左区间 $1 \sim l$ 以 $l$ 为结尾，右区间 $r \sim n$ 以 $r$ 为右端点。这时我们要保证区间 $1 \sim l$ 的每一个点的横坐标与区间 $r \sim n$ 的每一个点的横坐标的差大于我们二分到的 $mid$。将这两个符合差为 $mid$ 要求的区间内点的纵坐标 $Y$ 的最大值与最小值分别与另一区间内纵坐标 $Y$ 的最小值最大值作差，判断是否大于等于 $mid$。若大于，则符合题目要求，返回真。

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;

int n;

struct Picture {
	int x, y;
	bool operator < (const Picture & b) const {
		if (x != b.x) return x < b.x;
		return y < b.y;
	}//sort的时候用 
}a[1000100];

bool check(int differ) {
	int MaxY = -1e9, MinY = 1e9;
	//在l之前Y轴的最值 
	for (int r = 1, l = 0; r <= n; ++ r) { 
		//这里面的l表示左半部分的右端点，r表示右半部分的左端点
		//l就是左指针，r就是右指针 
		while (l < r && a[r].x - a[l + 1].x >= differ) {
			//若存在更小的X轴之差符合差最小值得differ的条件，就更新l的值 
			MaxY = max(MaxY, a[l + 1].y);
			MinY = min(MinY, a[l + 1].y);
			//将左指针新包含的范围内的MaxY和MinY更新 
			l ++;
		}
		if (MaxY - a[r].y >= differ) return true;
		if (a[r].y - MinY >= differ) return true;
		//判断左边的Y的最值与右侧的Y的最值的差是不是大于differ 
		//在循环里我们相当于将右指针后面的数全部枚举了一遍最大值，最小值 
		//左指针除了l=r=1的时候处理右指针，其他时候都是左指针跟着右指针移动
		//所以在右指针更新的时候，左指针左边的MaxY与MinY也都被更新了，正确性可以保证 
	}
	return false;
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++ i) {
		scanf("%d%d", &a[i].x, &a[i].y);
	}
	sort(a + 1, a + 1 + n);
	int l = 0, r = 1e9, ans = 0;
	while (l <= r) {
		//二分找最值 
		int mid = (l + r) >> 1;
		if (check(mid)) {
			l = mid + 1;
			ans = mid;
		}
		else r = mid - 1;
	}
	printf("%d\n", ans);
	return 0;
}
```

PS：顺带附上找最最大的最小值。

```cpp
while (l <= r) {
	int mid = (l + r) >> 1;
	if (check(mid)) {
		r = mid - 1;
		ans = mid;
	}
	else l = mid + 1;
}

---

## 作者：lfxxx (赞：0)

考虑二分答案。

假设当前二分的答案为 $k$，那么对于每个点，距离大于等于 $k$ 的点构成了平面上 $4$ 个子平面。

那么只需查询子平面中是否存在点即可，类似于窗口的星星，把问题转换成求矩形交集，用一个扫描线维护，复杂度 $O(n \log V)$，加上二分，总复杂度 $O(n \log^2 V)$，勉强可过。

---

