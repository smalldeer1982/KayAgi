# [ABC330F] Minimize Bounding  Square

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc330/tasks/abc330_f

$ xy $ 平面上に $ N $ 個の点 $ 1,2,\dots,N $ があります。このうち点 $ i $ は座標 $ (X_i,Y_i) $ にあります。  
あなたは、以下の操作を $ 0 $ 回以上 $ K $ 回以下行うことができます。

- まず、 $ N $ 点の中からひとつを選択する。選ばれた点を $ k $ とし、この点が現在 $ (x,y) $ にあるものとする。
- 次に、以下の $ 4 $ つからひとつを選択し、実行する。
  - 点 $ k $ を $ x $ 軸沿いに $ +1 $ だけ移動させる。点 $ k $ の座標は $ (x+1,y) $ となる。
  - 点 $ k $ を $ x $ 軸沿いに $ -1 $ だけ移動させる。点 $ k $ の座標は $ (x-1,y) $ となる。
  - 点 $ k $ を $ y $ 軸沿いに $ +1 $ だけ移動させる。点 $ k $ の座標は $ (x,y+1) $ となる。
  - 点 $ k $ を $ y $ 軸沿いに $ -1 $ だけ移動させる。点 $ k $ の座標は $ (x,y-1) $ となる。
- 複数の点を同じ座標に存在させることも許されます。また、入力で複数の点が同じ座標に存在しうることに注意してください。

全ての操作が終わった後、 $ N $ 個全ての点を内部または周上に包含する、各辺が $ x $ 軸または $ y $ 軸に平行な正方形をひとつ書き込みます。  
このとき、書き込む正方形の一辺の長さとしてありうる最小の値を求めてください。全ての点が常に格子点にあることから、この値は整数であることが示せます。

**特に、全ての点を同じ座標に存在させられる時、答えは $ 0 $ であるものとします。**

## 说明/提示

### 制約

- 入力は全て整数
- $ 1\ \le\ N\ \le\ 2\ \times\ 10^5 $
- $ 0\ \le\ K\ \le\ 4\ \times\ 10^{14} $
- $ 0\ \le\ X_i,Y_i\ \le\ 10^9 $

### Sample Explanation 1

このケースについて、横を $ x $ 軸、縦を $ y $ 軸として図示したものが以下です。 !\[\](https://img.atcoder.jp/abc330/932178d158b342b9bda6bdc72b439f0e.png) 例えば、図中の矢印に従って $ 4 $ 度の移動を行った後、図中に示した一辺が $ 3 $ の正方形で全ての点を内部または周上に含むことができ、これが最小値であることが示せます。

### Sample Explanation 2

最初から全ての点が同じ座標に存在します。 例えば操作を $ 0 $ 回行う (即ち、全く行わない) ことにより、全ての点を同じ座標に存在させられるので、この入力に対する答えは $ 0 $ です。

## 样例 #1

### 输入

```
6 5
2 0
5 2
0 3
3 2
3 4
1 5```

### 输出

```
3```

## 样例 #2

### 输入

```
4 400000000000000
1000000000 1000000000
1000000000 1000000000
1000000000 1000000000
1000000000 1000000000```

### 输出

```
0```

## 样例 #3

### 输入

```
10 998244353
489733278 189351894
861289363 30208889
450668761 133103889
306319121 739571083
409648209 922270934
930832199 304946211
358683490 923133355
369972904 539399938
915030547 735320146
386219602 277971612```

### 输出

```
484373824```

# 题解

## 作者：fcy20180201 (赞：20)

## 题意
给定 $XY$ 坐标上的 $N$ 个点，可以进行 $K$ 次操作，每次操作把一个点的 $X$ 或 $Y$ 坐标 $\pm 1$。最后用一个平行平行于坐标轴的正方形把 $N$ 个点包围，问正方形的最小边长。

## 思路
对这种不定量太多的求极值题，用二分确定一个不变量。这题就二分正方形的边长。接下来我们算 $N$ 个点 $X$ 坐标和 $Y$ 坐标分别到正方形的距离。

简化一下问题：在一条直线上有两个点 $a,b$，想要在这条线上再选一个点 $c$，使得 $a$ 到 $c$  的距离加 $b$ 到 $c$ 的距离最小，那么 $c$ 一定选在 $a,b$ 之间，所求值就是 $a$ 到 $b$ 的距离。

再扩展到这题来。在计算 $X$ 坐标所需操作数时，我们先考虑 $X$ 坐标上最外面的两个点，根据上面的简化情形，不难发现这两点到正方形的 $X$ 距离和正好是两点 $X$ 距离和减正方形边长（如果为负数就算成 0）。接下来考虑第二外的点对，以此类推，考虑完所有点对后就能算出所需操作数。$Y$ 坐标的方法同理。这样就能计算出假定的正方形边长是否可能实现。

## 代码
其实码量挺小的。

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
int n,x[200005],y[200005];
ll k;

bool check(int len){
	ll cnt=0;
	for(int i=1;i<=(n>>1);i++)cnt+=max(0,x[n-i+1]-x[i]-len)+max(0,y[n-i+1]-y[i]-len);
    //关键点，前面百字解析只为这一行。还有这里的 xi,yi 没有任何关系。
	return cnt<=k;
}

int main(){
	scanf("%d%lld",&n,&k);
	for(int i=1;i<=n;i++)scanf("%d%d",&x[i],&y[i]);
	sort(x+1,x+n+1);
	sort(y+1,y+n+1);
	int l=0,r=1e9+1;
	while(l<r){//二分边长
		int mid=(l+r)>>1;
		if(check(mid))r=mid;
		else l=mid+1;
	}
	printf("%d",l);
	return 0;
}
```

---

## 作者：Register_int (赞：9)

二维问题就很脑溢血。可是我们发现，操作次数的总和是曼哈顿距离，这说明横纵坐标实际上是独立的，可以单独处理，取最小值后合并。

考虑二分答案，问题变为所有点到长度为定值 $p$ 的区间距离之和的最小值。有一个简单的观察：这个区间的左右端点必然在一个给定点上。否则，我们选择点数较多的一侧，将区间向那个方向移动，就可以减小答案。如图，蓝线所示的区间显然比绿线优秀。

![](https://cdn.luogu.com.cn/upload/image_hosting/6axppqoi.png)

先做左边界在点上的情况，用双指针算出右边界在哪里。设取的区间为 $[l,r]=[x_i,x_i+p]$，第一个在区间右侧点的为 $j$，则答案为：

$$
\begin{aligned}
&\left(\sum^{i-1}_{k=1}x_k-l\right)+\left(\sum^n_{k=j}r-x_k\right)\\
=&\left(\sum^i_{k=1}x_k\right)-i\times l+(n-j+1)\times r-\left(\sum^n_{k=j}x_k\right)
\end{aligned}
$$

容易用前缀和优化做到 $O(1)$ 计算。右边界做相同处理，也可以选择将值域翻转过来做一遍。这样，单次检查的复杂度为 $O(n)$，总时间复杂度 $O(n\log n)$。

# AC 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 2e5 + 10;

int n, x[MAXN], y[MAXN]; ll k, sx[MAXN], sy[MAXN];

inline 
ll calc(int *a, ll *s, int p) {
	ll res = 1e18;
	for (int i = 1, j = 1; i <= n; i++) {
		for (; j <= n && a[j] - a[i] <= p; j++); ll l = a[i], r = a[i] + p;
		res = min(res, l * i - s[i] + s[n] - s[j - 1] - r * (n - j + 1));
	}
	for (int i = n, j = n; i; i--) {
		for (; j && a[i] - a[j] <= p; j--); ll l = a[i] - p, r = a[i];
		res = min(res, l * j - s[j] + s[n] - s[i] - r * (n - i));
	}
	return res;
}

inline 
bool check(int p) {
	return calc(x, sx, p) + calc(y, sy, p) > k;
}

ll l, r = 1e9, mid;

int main() {
	scanf("%d%lld", &n, &k);
	for (int i = 1; i <= n; i++) scanf("%d%d", &x[i], &y[i]);
	sort(x + 1, x + n + 1), sort(y + 1, y + n + 1);
	for (int i = 1; i <= n; i++) sx[i] = sx[i - 1] + x[i];
	for (int i = 1; i <= n; i++) sy[i] = sy[i - 1] + y[i];
	for (; l < r; check(mid = l + r >> 1) ? l = mid + 1 : r = mid);
	printf("%lld", l);
}
```

---

## 作者：xz001 (赞：6)

- 首先我们发现答案具有单调性，所以可以二分答案。
- 然后我们发现 $x$ 轴和 $y$ 轴之间没有什么关系，移动时要么移动 $x$，要么移动 $y$，不会一起移动。因此我们可以分别处理，由初一知识得知：
  - $n$ 个点中，若 $n$ 为奇数，那么最中间的那个点跟其他点的距离和最小，若 $n$ 为偶数，那么最中间两个点之间的位置距离其他点的总距离最小。
- 所以 ```check``` 函数可以这么写，对于 $x$ 轴和 $y$ 轴，我们分别不断枚举其最大的和最小的，若它们之间的距离大于二分的 ```mid```，则需要的最小移动次数加上**它们之间的距离减去 ```mid```**，去除最大的和最小的，否则 ```break```。
- 然后我们就以 $O(n\log_2 n)$ 的复杂度切了此题，代码如下：

```cpp

#include<bits/stdc++.h>
#define int long long
using namespace std;
int n, k, x[1000005], y[1000005];
int check (int mid) {
	int l = 1, r = n, sum = 0;
	while (l < r) {   //每次枚举最大的和最小的
		if (x[r] - x[l] <= mid) break;
		sum += (x[r] - x[l]) - mid;
		++ l, -- r;   //去除目前最大的和最小的
	}
	l = 1, r = n;
	while (l < r) {   //每次枚举最大的和最小的
		if (y[r] - y[l] <= mid) break;
		sum += (y[r] - y[l]) - mid;
		++ l, -- r;   //去除目前最大的和最小的
	}
	return sum;
}
signed main() {
	scanf("%lld%lld", &n, &k);
	for (int i = 1; i <= n; ++ i) scanf("%lld%lld", x + i, y + i);
	sort(x + 1, x + n + 1);
	sort(y + 1, y + n + 1);
    int l = 0, r = 2e9, ans;
    while (l <= r) {   //伟大的二分答案
    	int mid = (l + r) >> 1;
    	if (check(mid) <= k) {  //若需要的最小次数 <= k
    		ans = mid;
    		r = mid - 1;
		} else {
			l = mid + 1;
		}
	}
	printf("%lld", ans);
	return 0;
}
```

---

## 作者：FFTotoro (赞：3)

看到这种边长最小值，一眼二分。

二分一个边长考虑如何判定；显然 $x$ 和 $y$ 可以分开考虑。以 $x$ 为例，预处理将所有 $x$ 坐标排序，枚举那个正方形的左右边界，其中一种最优方案一定是把左或右边界放在其中一个点上。这样用前缀和与二分可以快速求出最小操作数。最后判断 $x$ 与 $y$ 的最小操作数之和即可。

放代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
typedef pair<int,int> pii;
main(){
  ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  int n,k; cin>>n>>k;
  vector<int> x(n),y(n),sx,sy;
  for(int i=0;i<n;i++)cin>>x[i]>>y[i];
  sort(x.begin(),x.end());
  sort(y.begin(),y.end());
  partial_sum(x.begin(),x.end(),back_inserter(sx)); // 前缀和
  partial_sum(y.begin(),y.end(),back_inserter(sy));
  auto sumx=[&](int l,int r)->int{
    if(r==-1)return 0;
    return sx[r]-(l?sx[l-1]:0);
  }; // 求和
  auto sumy=[&](int l,int r)->int{
    if(r==-1)return 0;
    return sy[r]-(l?sy[l-1]:0);
  };
  auto getx=[&](int l,int r){
    int ll=prev(upper_bound(x.begin(),x.end(),l))-x.begin(),
      rr=lower_bound(x.begin(),x.end(),r)-x.begin();
    return (ll+1)*l-sumx(0,ll)+sumx(rr,n-1)-(n-rr)*r;
  }; // 给定正方形的左右端点求操作数
  auto gety=[&](int l,int r){
    int ll=prev(upper_bound(y.begin(),y.end(),l))-y.begin(),
      rr=lower_bound(y.begin(),y.end(),r)-y.begin();
    return (ll+1)*l-sumy(0,ll)+sumy(rr,n-1)-(n-rr)*r;
  };
  int l=0,r=5e14;
  auto f=[&](int s){
    int cx=1e15,cy=1e15;
    for(int i=0;i<n;i++)
      cx=min({cx,getx(x[i],x[i]+s),getx(x[i]-s,x[i])}),
      cy=min({cy,gety(y[i],y[i]+s),gety(y[i]-s,y[i])});
    return cx+cy;
  }; // 求最小操作数
  while(l<r){
    int m=l+r>>1;
    if(f(m)<=k)r=m;
    else l=m+1;
  } // 二分边长
  cout<<r<<endl;
  return 0;
}
```

---

## 作者：yhx0322 (赞：3)

## Solution
容易发现，此题满足单调性：越大的正方形，越容易被满足。

二分正方形的边长 $mid$。现在变成了询问：能否经过不超过 $k$ 次操作，使得所有点的横坐标极差不超过 $mid$，并且纵坐标极差不超过 $mid$。注意到这里横坐标和纵坐标是独立的，所以可以分别求横坐标和纵坐标最少需要几次操作。

先考虑横坐标，纵坐标类似。把所有点按照横坐标排序以后，就是要把所有点都移动到一个长度为 $mid$ 的区间以内。可以枚举这个区间，然后用前缀和求移动的次数。

时间复杂度 $O(n \log n)$。

## Code
```cpp
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int N = 2e5 + 10;

ll n, m, a[N], b[N], f[N];

bool check(ll x) {
	ll mn1 = LONG_MAX, mn2 = LONG_MAX;
	for (int i = 1; i <= n; i++) {
		f[i] = f[i - 1] + a[i];
	}
	for (int i = 1, j = 1; i <= n; i++) {
		while (j < n && a[j + 1] <= a[i] + x) {
			j++;
		}
		mn1 = min(mn1, a[i] * (i - 1) - f[i - 1] + f[n] - f[j] - (a[i] + x) * (n - j));
	}
	for (int i = 1, j = 1; i <= n; i++) {
		while (a[j] < a[i] - x) {
			j++;
		}
		mn1 = min(mn1, (a[i] - x) * (j - 1) - f[j - 1] + f[n] - f[i] - a[i] * (n - i));
	}
	for (int i = 1; i <= n; i++) {
		f[i] = f[i - 1] + b[i];
	}
	for (int i = 1, j = 1; i <= n; i++) {
		while (j < n && b[j + 1] <= b[i] + x) {
			j++;
		}
		mn2 = min(mn2, b[i] * (i - 1) - f[i - 1] + f[n] - f[j] - (b[i] + x) * (n - j));
	}
	for (int i = 1, j = 1; i <= n; i++) {
		while (b[j] < b[i] - x) {
			j++;
		}
		mn2 = min(mn2, (b[i] - x) * (j - 1) - f[j - 1] + f[n] - f[i] - b[i] * (n - i));
	}
	return mn1 + mn2 <= m;
}
int main() {
	scanf("%lld%lld", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%lld%lld", &a[i], &b[i]);
	}
	sort(a + 1, a + n + 1);
	sort(b + 1, b + n + 1);
	ll l = 0, r = 1.1e9, ans = -1;
	while (l <= r) {
		ll mid = (l + r) >> 1;
		if (check(mid)) {
			ans = mid;
			r = mid - 1;
		} else {
			l = mid + 1;
		}
	}
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：qqqaaazzz_qwq (赞：2)

### [My Blog](https://www.luogu.com.cn/blog/Hello-2023/)

显然先套一个二分，二分正方形的边长，计算的时候我们可以把横轴和纵轴拆开计算。因此现在转化成了这个问题：

* 给你一些点，你可以选择一个长度为 $q$ 的区间，定义这个区间的价值为把所有点都移进区间的最小步数，求价值最小的区间。

这个问题我们发现，随着区间从左往右移动，区间的价值一定会慢慢变少，在某个地方达到谷值，然后价值又开始慢慢变多......咦？这不是一个 **单谷函数** 吗？我们可以直接三分去求它的谷值啊！至此，本题解决。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,k;
int x[200010],y[200010];

int cx(int st,int len)//给定区间的起点和长度，计算在x轴上的价值
{
	int cnt = 0;
	for (int i=1;i<=n;i++)
	{
		if(x[i]<=st)
		{
			cnt += (st-x[i]);
		}
		if(x[i]>=st+len)
		{
			cnt += (x[i]-(st+len));
		}
	}
	return cnt;
}

int cy(int st,int len)//给定区间的起点和长度，计算在y轴上的价值
{
	int cnt = 0;
	for (int i=1;i<=n;i++)
	{
		if(y[i]<=st)
		{
			cnt += (st-y[i]);
		}
		if(y[i]>=st+len)
		{
			cnt += (y[i]-(st+len));
		}
	}
	return cnt;
}

bool check(int len)
{
	int l = 0,r = 1e9;
	while(l<r)
	{
		//经典三分找谷值 
		int midl = (l+r)/2;
		int midr = midl+1;
		if(cx(midl,len)>cx(midr,len)) l = midl+1;
		else r = midr-1;
	}
	int minx = cx(l,len);//在 x 轴上价值最小区间的价值 
	l = 0,r = 1e9;
	while(l<r)
	{
		int midl = (l+r)/2;
		int midr = midl+1;
		if(cy(midl,len)>cy(midr,len)) l = midl+1;
		else r = midr-1;
	}
	int miny = cy(l,len);//在 y 轴上价值最小区间的价值 
	int sum = minx+miny;
	if(sum<=k) return true;
	else return false;
}

signed main()
{
	cin >> n >> k;
	for (int i=1;i<=n;i++) cin >> x[i] >> y[i];
	int l = 0,r = 1e9;
	int res = 1e9;
	while(l<=r)
	{
		int mid = (l+r)/2;
		if(check(mid))
		{
			res = mid;
			r = mid-1;
		}
		else l = mid+1;
	}
	cout << res << "\n";
	return 0;
} 
```

---

## 作者：hejianxing (赞：1)

[link](https://www.luogu.com.cn/problem/AT_abc330_f)

考场没 rush 出来。wtcl

[OptimisticForever](https://www.luogu.com.cn/user/214893) 帮调。

# 题解

考虑二分答案。

确定了边长之后，考虑如何算出最小的距离和。

每个点的移动相当于先横向移动若干格，再纵向移动若干格。假设这个矩形的横坐标 $[a,a+x]$ 已经确定，即矩形只能上下移动。首先将横坐标在 $[a,a+x]$ 外的点全部横向移动至这个范围内，这些移动步数是必要的。假设矩形的纵坐标为 $[b,b+x]$，那么纵坐标在这个范围外的点都需要纵向移动到这个范围。

于是发现横纵坐标是无关的。容易发现，矩形的左右两边上至少有一个点，上下同理。那么考虑计算所有点的横向移动的步数最小值，纵向移动的步数最小值，将其与 $k$ 比较即可。

具体地，按横坐标排序，考虑枚举矩形的左边贴着点 $l$，维护一个指针 $r$ 表示在 $r$ 到 $n$ 中的点是不被矩形的横坐标 $[l,l+x]$ 包含的，同时维护左右两边的点走到矩形的步数。再考虑矩形的右边贴着点 $r$，这两种情况的 $\min$ 值就是横向移动步数的最小值。

纵向移动同理。

时间复杂度 $O(n\log n)$。

# 实现

最开始没想到还要考虑右边贴点和上面贴点调了 1h。于是代码巨臭。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 200005;
int n;
LL K;
struct node {
    LL x, y;
} a[N], b[N];
bool cmp1(node t1, node t2) { return t1.x < t2.x; }
bool cmp2(node t1, node t2) { return t1.y < t2.y; }
bool check(int x) {
    int l = 1, r = n;
    LL sum1 = 1e16, sum2 = 1e16, suml = 0, sumr = 0;
    while (r >= 1 && a[r].x > a[l].x + x) sumr += a[r].x - (a[l].x + x), r--;//左边贴点
    while (l < n && a[l].x == a[l + 1].x) l++;
    sum1 = sumr;
    for (l++, r++; l <= n; l++) {
        suml += 1ll * (l - 1) * (a[l].x - a[l - 1].x), sumr -= 1ll * (n - r + 1) * (a[l].x - a[l - 1].x);
        while (r <= n && a[r].x <= a[l].x + x) sumr -= a[r].x - (a[l].x + x), r++;
        sum1 = min(sum1, suml + sumr);
        while (l < n && a[l].x == a[l + 1].x) l++;
    }
    suml = sumr = 0, l = 1, r = n;
    while (l <= n && a[l].x < a[r].x - x) suml += a[r].x - x - a[l].x, l++;//右边贴点
    while (r > 1 && a[r].x == a[r - 1].x) r--;
    sum1 = min(sum1, suml);
    for (l--, r--; r >= 1; r--) {
        sumr += 1ll * (n - r) * (a[r + 1].x - a[r].x), suml -= 1ll * l * (a[r + 1].x - a[r].x);
        while (l >= 1 && a[l].x >= a[r].x - x) suml -= a[r].x - x - a[l].x, l--;
        sum1 = min(sum1, suml + sumr);
        while (r > 1 && a[r].x == a[r - 1].x) r--;
    }
    suml = sumr = 0, l = 1, r = n;
    while (r >= 1 && b[r].y > b[l].y + x) sumr += b[r].y - (b[l].y + x), r--;//下面贴点
    while (l < n && b[l].y == b[l + 1].y) l++;
    sum2 = sumr;
    for (l++, r++; l <= n; l++) {
        suml += 1ll * (l - 1) * (b[l].y - b[l - 1].y), sumr -= 1ll * (n - r + 1) * (b[l].y - b[l - 1].y);
        while (r <= n && b[r].y <= b[l].y + x) sumr -= b[r].y - (b[l].y + x), r++;
        sum2 = min(sum2, suml + sumr);
        while (l < n && b[l].y == b[l + 1].y) l++;
    }
    suml = sumr = 0, l = 1, r = n;
    while (l <= n && b[l].y < b[r].y - x) suml += b[r].y - x - b[l].y, l++;//上面贴点
    while (r > 1 && b[r].y == b[r - 1].y) r--;
    sum2 = min(sum2, suml);
    for (l--, r--; r >= 1; r--) {
        sumr += 1ll * (n - r) * (b[r + 1].y - b[r].y), suml -= 1ll * l * (b[r + 1].y - b[r].y);
        while (l >= 1 && b[l].y >= b[r].y - x) suml -= b[r].y - x - b[l].y, l--;
        sum2 = min(sum2, suml + sumr);
        while (r > 1 && b[r].y == b[r - 1].y) r--;
    }
    return sum1 + sum2 <= K;
}
int main() {
    scanf("%d%lld", &n, &K);
    for (int i = 1; i <= n; i++) scanf("%lld%lld", &a[i].x, &a[i].y), b[i] = a[i];
    sort(a + 1, a + n + 1, cmp1), sort(b + 1, b + n + 1, cmp2), a[n + 1].x = b[n + 1].x = a[n + 1].y = b[n + 1].y = -1;
    int l = 0, r = 1e9, ans = 0;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (check(mid) == true) ans = mid, r = mid - 1;
        else l = mid + 1;
    }
    printf("%d", ans);
    return 0;
}
```

# 启示

别把问题想复杂了。

---

## 作者：FReQuenter (赞：0)

### 题意

给定平面内 $n$ 个点，你可以把这 $n$ 个点一共在坐标上移动 $k$ 次。移动可以是横着或者竖着走 $1$ 单位长度。移动结束后会有一个最小的正方形把所有点都框起来。最小化这个正方形的边长。

### 题解

一个套路，把 $x$ 轴和 $y$ 轴分开讨论。然后就可以转化了：

给定两个长度为 $n$ 的数组 $x,y$，可以对数组内任意一个数 $+1$ 或者 $-1$，一共执行 $k$ 次。求两个数列中 分别最大值减最小值 的最小值 的较大值。

我们二分最终的答案，正方形的边长。

那么就把“求两个数列中 分别最大值减最小值 的最小值 的较大值”变成了“一个数列中最大值减最小值等于 $mid$ 时操作步数是多少”，对两个数列都做一遍把答案加起来看是否小于等于 $k$。我们设正在操作的序列为 $a$。

先把数列排序。显然我们希望把大的数变小，小的数变大。且我们只关心一个数要变多少。

我们把这个数列中的数两两考虑。即 $\{a_{1},a_{n}\},\{a_2,a_{n-1}\}\cdots$ 这样子组合。如果一组数 $\{a_i,a_j\}$差大于 $mid$ 则花费 $a_j-a_i-mid$ 的代价把差变成 $mid$，否则不操作。

这个做法的正确性就来自排序。感性理解下，我们假设有一对合法的数 $\{x,y\},x\le y$ 且差值等于 $mid$，那么对于所有 $a_i\le x\le y \le a_j$，它们可以通过变成 $\{x,y\}$ 完成操作。对于 $x<a_i\le a_j<y$，则无需操作。**因为排序和上面的分组方式，不会出现其它情况。**

那么按照上面的思路实现就可以了。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,k,x[200005],y[200005];
int cal(int *x,int mid){
	int sum=0;
	for(int l=1,r=n;l<r;l++,r--){
		if(x[r]-x[l]<=mid) break;
		sum+=x[r]-x[l]-mid;
	}
	return sum;
}
bool check(int mid){
	return cal(x,mid)+cal(y,mid)<=k;
}
signed main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>x[i]>>y[i];
	sort(x+1,x+n+1),sort(y+1,y+n+1);
	int l=0,r=2000000000,ans=r;
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid)) r=mid-1,ans=mid;
		else l=mid+1;
	}
	cout<<ans;
}
```

---

## 作者：解方橙 (赞：0)

[Problem](https://atcoder.jp/contests/abc330/tasks/abc330_f)

二分是什么东西？不需要不需要。这里提供一个逆天的贪心做法。

首先是基本的贪心思想：争取把所有点都往“里”缩。

我们记 $S$ 为能包围初始点的最小矩形。

如果 $S$ 是长方形，那么我们一定要把它缩成正方形。具体来说，我们考虑一个贪心：将长方形上的两个短边（即我们要缩的边）中含点数较少的那个边往里缩，这样一定是不亏的。

因为 $x$ 和 $y$ 互不干扰，不会因为收缩了 $x$ 就影响 $y$ ，因此在都是让答案 $-1$ 的情况下，我们一定会选择代价较小的边进行收缩。

如果每次收缩距离为 $1$ ，那面对 $10^9$ 的值域就会无能为力。因此每次我们收缩到下一个有点的地方。可以用 $\operatorname{map}$ 维护横坐标和纵坐标。

好的，现在我们已经把 $S$ 缩成一个正方形了。接下来我们要把 $S$ 变成一个更小的正方形。采取和上面类似的策略，我们选取代价最小的两条邻边然后往里缩。还是缩到第一个有点的位置。

于是一通贪下去这道题就做完了，只是代码量和常数略大。注意到每一次往里缩**至少会使 $S$ 的边界上增加一个点**，因此这部分复杂度为 $\mathcal{O}(n)$ 。最后时间复杂度的瓶颈在 $\operatorname{map}$ 上。

[Submission](https://atcoder.jp/contests/abc330/submissions/47937322)

---

## 作者：OldDriverTree (赞：0)

这篇题解讲解二分套三分的做法。

考虑先二分正方形的边长 $l$。

可以发现 $x$ 和 $y$ 两维可以拆开。

这样就转化成移动数轴上的 $N$ 个点，使得 $N$ 个点在一个长度为 $l$ 的区间里，求最小移动步数。

可以发现区间的位置对应的最小移动步数是一个单峰函数，三分即可。

时间复杂度 $O(N\log^2 V)$，把数组排遍序后预处理前缀和，求最小移动步数时二分应该可以做到 $O(N\log N+\log^2V\log N)$。

这里就放赛时写的 $O(N\log^2 V)$ 代码。

但是直接这样写会 $\texttt{TLE}$，不理解为什么二分前把数组排遍序就过了，时间甚至是不排序的三分之一。

```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5;
int n,m,a[N],b[N];

int read() {
	int x=0; char c=0; while (!isdigit(c) ) c=getchar();
	while (isdigit(c) ) x=(x<<3)+(x<<1)+(c&15),c=getchar();
	return x;
}
int f(int *a,int x,int k)
{
	int sum=0;
	for (int i=0;i<n;i++) {
		if (a[i]<x) sum+=x-a[i];
		if (a[i]>x+k) sum+=a[i]-x-k;
	}
	return sum;
}
int work(int *a,int x)
{
	int l=0,r=1e9;
	while (l+2<r) {
		int mid1=(l+l+r)/3,mid2=(l+r+r)/3;
		f(a,mid1,x)>f(a,mid2,x)?l=mid1:r=mid2;
	}
	int ans=1e17;
	while (l<=r)
	ans=min(ans,f(a,l++,x) );
	return ans;
}
bool check(int x) {
	return work(a,x)+work(b,x)<=m;
}
main()
{
	n=read(),m=read();
	for (int i=0;i<n;i++)
	a[i]=read(),b[i]=read();
	sort(a,a+n),sort(b,b+n);
	int l=0,r=1e9;
	while (l<=r) {
		int mid=(l+r)>>1;
		if (check(mid) ) r=mid-1;
		else l=mid+1;
	}
	printf("%lld",l);
	return 0;
}
```

---

## 作者：I_am_kunzi (赞：0)

# AT_abc330_f 题解

### 题目翻译

给定你 $ n $ 个点和 $ k $ 次移动次数，每次可以将任意一个点向上、下、左、右任意一个方向移动一格，并耗费一次移动次数。求一个最小的正方形边长使得移动后可以将所有点都包含在内。

### 题目思路

这道题要求最小的边长，那么一般可以用二分或者贪心等方法，在这里我会用比较好理解的贪心来讲解。

整体思路可以理解为：每次看当前能画出的最小长方形（如果是正方形则没有长宽对比，不知道该怎么移动）的长和宽，找到较大的一个，并通过移动两端点较少的一侧将答案缩小，直到无法移动为止。

下面我们来依次分析每一步的实现。对于坐标的存储，我们发现我们需要的只有每个横坐标位置、纵坐标位置上分别有多少个点，这一部分可以通过定义 ``` map < long long , long long > cntx , cnty; ``` 实现。

在此之后，我们需要模拟移动这个过程。这一部分可以将上面的两个 ``` map ``` 遍历并分别存入 ``` vector < pair < long long , long long > > x , y; ``` 中进行后续操作即可。

我们通过定义 ``` long long xl = 0 , xr = x.size() - 1 , yl = 0 , yr = y.size() - 1; ``` 和每次修改这些变量的值，来代替每次移动后同一位置上点的增多造成的删除操作，此时我们只需每次修改 ``` vector ``` 中变量的值即可。

总体来说，用贪心方法写本题，细节较多，详细内容请看代码及注释。

### 题目代码

```cpp
#include<iostream>
#include<vector>
#include<map>
using namespace std;
pair < long long , long long > a[200005]; 
map < long long , long long > cntx , cnty; 
vector < pair < long long , long long > > x , y; 
signed main()
{
	long long n , k;
	cin >> n >> k;
	for(int i = 1 ; i <= n ; i++)
	{
		cin >> a[i].first >> a[i].second;
		cntx[a[i].first]++; 
		cnty[a[i].second]++;
	}
	for(pair < long long , long long > i : cntx) // 遍历 cntx 中每个元素，i 的类型可以用 auto 代替
	{
		x.push_back(i); // map 和 vector 中元素类型相同，可以直接 push_back
	}
	for(pair < long long , long long > i : cnty) // 同上
	{
		y.push_back(i);
	}
	long long xl = 0 , xr = x.size() - 1;
	long long yl = 0 , yr = y.size() - 1;
	while(k > 0) // 只要还能进行操作就继续，体现贪心思想
	{
		long long lx = x[xr].first - x[xl].first; // 计算当前长方形长和宽
		long long ly = y[yr].first - y[yl].first;
		bool xwz , ywz; // 记录移动 xl yl 位置 (0) 还是移动 xr yr 位置 (1)
		long long disx , disy; // 记录分别需要移动的距离
		long long mvx , mvy; // 记录分别需要移动多少个点
		if(lx) // 如果所有点还不在一条直线上，就进行计算
		{
			if(x[xl].second < x[xr].second) // xl 位置需要移动的点少，则移动 xl 位置
			{
				disx = x[xl + 1].first - x[xl].first; // 需要移动的距离，就是下一个有点的位置 - 当前位置
				mvx = x[xl].second; // 需要移动的点数，就是当前位置的点数
				xwz = 0;
			}
			else
			{
				disx = x[xr].first - x[xr - 1].first; // 注意这里要不是减去 x[xr + 1].first
				mvx = x[xr].second;
				xwz = 1;
			}
		}
		if(ly) // 同上
		{
			if(y[yl].second < y[yr].second)
			{
				disy = y[yl + 1].first - y[yl].first;
				mvy = y[yl].second;
				ywz = 0;
			}
			else
			{
				disy = y[yr].first - y[yr - 1].first;
				mvy = y[yr].second;
				ywz = 1;
			}
		}
		if(lx == 0 && ly == 0) // 已经移动到同一个点上，答案已经为 0，中断循环
		{
			break;
		}
		else if(lx > ly) // 此时需要对 x 数组操作
		{
			long long diss = min(k / mvx , min(disx , lx - ly)); 
			// k / mvx：当前能移动的最大距离
			// disx：到下一个地方的距离
			// lx - ly：成为一个正方形还需移动的距离（成为正方形后再移动也无法减小答案）
			// 这三者取 min，也体现了贪心思想
			if(diss == 0) // 此时无法移动，中断循环
			{
				break;
			}
			k -= mvx * diss; // 减小剩余移动次数
			if(xwz == 0) // 分类讨论并更改 x[xl].first 或 x[xr].first
			{
				x[xl].first += diss;
			}
			else
			{
				x[xr].first -= diss; // 注意是减法，不是加法
			}
		}
		else if(lx < ly) // 同上
		{
			long long diss = min(k / mvy , min(disy , ly - lx));
			if(diss == 0)
			{
				break;
			}
			k -= mvy * diss;
			if(ywz == 0)
			{
				y[yl].first += diss;
			}
			else
			{
				y[yr].first -= diss;
			}
		}
		else // 此时只剩下 lx == ly，则可以共同移动
		{
			long long diss = min(min(k / (mvx + mvy) , disx) , disy);
			// k / (mvx + mvy)：共同移动时可以移动的距离
			// disx：移动到下一个 x 数组位置
			// disy：移动到下一个 y 数组位置
			if(diss == 0)
			{
				break;
			}
			k -= diss * (mvx + mvy);
			if(xwz == 0) // 注意这里 x 数组和 y 数组都要更改
			{
				x[xl].first += diss;
			}
			else
			{
				x[xr].first -= diss;
			}
			if(ywz == 0)
			{
				y[yl].first += diss;
			}
			else
			{
				y[yr].first -= diss;
			}
		}
		// 一轮的模拟操作结束，下面是维护数组部分
		if(xl != xr) // 如果 xl xr 还不在一起，说明此时可能对 x 数组进行了操作，需要修改
		{
			if(x[xl].first == x[xl + 1].first) // 如果 xl 位置已经移动到 xl + 1 位置，则合并这两个位置的点并修改 xl
			{
				x[xl + 1].second += x[xl].second;
				xl++;
			}
			if(x[xr].first == x[xr - 1].first) // 同上，但需注意 xr 是向前移动
			{
				x[xr - 1].second += x[xr].second;
				xr--;
			}
		}
		if(yl != yr) // 同上
		{
			if(y[yl].first == y[yl + 1].first)
			{
				y[yl + 1].second += y[yl].second;
				yl++;
			}
			if(y[yr].first == y[yr - 1].first)
			{
				y[yr - 1].second += y[yr].second;
				yr--;
			}
		}
	}
	long long lx = x[xr].first - x[xl].first; // 最后计算此时长方形的长和宽，正方形边长就相当于对这两者取 max
	long long ly = y[yr].first - y[yl].first;
	cout << max(lx , ly) << endl;
	return 0;
}
```

---

## 作者：1234567890sjx (赞：0)

由于答案具有单调性，所以考虑二分答案。

然后发现 $x$ 坐标和 $y$ 坐标是互不影响的，所以分开考虑。

对于每一个二分到的边长 $p$，为了框选到尽量多的点，不管是横坐标 $x$ 还是纵坐标 $y$，都可以钦定枚举到的原来的一个点的横坐标 / 纵坐标在正方形的边界上。这个点直接枚举即可。

设一个点是当前被钦定为横坐标的边界上的点，再枚举她是在上边界或者下边界上即可。

纵坐标的边界上的点枚举她是在左边界或者右边界上即可。

对所有情况分开取 $\min$，时间复杂度为 $O(n\log n)$。

---

