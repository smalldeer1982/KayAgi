# Fading into Fog

## 题目描述

This is an interactive problem.

There are $ n $ distinct hidden points with real coordinates on a two-dimensional Euclidean plane. In one query, you can ask some line $ ax + by + c = 0 $ and get the projections of all $ n $ points to this line in some order. The given projections are not exact, please read the interaction section for more clarity.

Using the minimum number of queries, guess all $ n $ points and output them in some order. Here minimality means the minimum number of queries required to solve any possible test case with $ n $ points.

The hidden points are fixed in advance and do not change throughout the interaction. In other words, the interactor is not adaptive.

A projection of point $ A $ to line $ ax + by + c = 0 $ is the point on the line closest to $ A $ .

## 说明/提示

In the sample the hidden points are $ (1, 3) $ and $ (2.5, 0.5) $

A picture, which describes the first query:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1826F/4744008dabc55375d10584d55a7e6bc54d18767a.png)

A picture, which describes the second query:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1826F/3b1f3044b777eff15fd4aeeb3484196dbbaecf67.png)

## 样例 #1

### 输入

```
1
2

1 1 2.5 1

1.500000001 1.500000000 2 2```

### 输出

```
? 0 1 -1

? 0.2 -0.2 0

! 1 3 2.5 0.500000001```

# 题解

## 作者：syf2008 (赞：9)

题意：



有 $n$ 个隐藏点，每次你可以给出 $a$，$b$，$c$，询问一条形如 $ax+by+c=0$ 的直线，交互库会以**任意顺序**告诉你每个点在直线上的投影（保证每个返回的投影点与真实投影点的距离不超过 $10^{-4}$）。

请用最少的询问求出这些隐藏点的位置，精度相差 $10^{-3}$ 即可。

保证每个隐藏点的与其他隐藏点的 $x$ 坐标和 $y$ 坐标都至少相差 $1$，每次询问的 $|a|+|b| \ge 0.1$。

$n\le 25$


简单题？

首先，这个样例给的很阴间，场上以为是最多只能 $2$ 次，赛后看了眼别人的码才知道可以 $3$ 次。


询问一条与 $y$ 轴平行的直线，可以得到 $n$ 个点的 $x$ 轴坐标的准确值。（记作第一次询问）

同理询问一条与 $x$ 轴平行的直线，可以得到 $n$ 个点的 $y$ 轴坐标的准确值。（记作第二次询问）

但是这些点 $y$ 轴和 $x$ 轴坐标的匹配关系我们不知道，所以我们要再询问一次，询问一条接近与 $x$ 轴平行的的直线，比如 $y=0.001x$。（记作第三次询问）

得到上次三次询问的结果后，我们把第一次按照 $x$ 轴大小排序，第二次按照 $y$ 轴大小排序。第三次按照 $x$ 轴大小排序。

然后因为知道第三次询问的斜率，我们把第一次准确询问的 $x$ 轴坐标带入第三次询问的直线，然后求出一个 $y$，但这个求出的 $y$ 精度有问题。

然后因为题目有一个良好的性质：

保证对于每 $2$ 个隐藏点之间的 $x$ 和 $y$ 相差至少为 $1$。


所以我们要把这个 $y$ 在第二次询问的精确的 $y$ 中寻找最接近的替换。那么这样就没有精度误差了。

就做完了。

时间复杂度 $O(n^2)$，实际可以用三分优化。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
int n;
long double a[35],c[35],x,k,b1,minn,minx,yy;
pair<long double,long double>b[35];
void solve()
{
	cin>>n;
	cout<<"? 0 1 0"<<endl;
	for(int i=1;i<=n;i++)cin>>a[i]>>x;
	sort(a+1,a+n+1);
	cout<<"? 1 0 0"<<endl;
	for(int i=1;i<=n;i++)cin>>x>>c[i];
	sort(c+1,c+n+1);
	cout<<"? -0.001 1.0000 0.0000"<<endl;
	for(int i=1;i<=n;i++)cin>>b[i].fi>>b[i].se;
	sort(b+1,b+n+1);
	cout<<fixed<<setprecision(7);
	cout<<"! ";
	for(int i=1;i<=n;i++)
	{
		k=-1000.0;
		b1=b[i].se-k*b[i].fi;
		yy=k*a[i]+b1;
		minn=2e9;
		for(int j=1;j<=n;j++)
		if(fabs(yy-c[j])<=minn)
		{minn=fabs(yy-c[j]);minx=c[j];}
		cout<<a[i]<<' '<<minx<<' ';
	}
	cout<<endl;
}
int t;
int main()
{
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>t;
	while(t--)solve();
	return 0;
}
```

---

## 作者：红黑树 (赞：7)

[可能更好的阅读体验](https://rbtr.ee/CF1826F)

## 闲聊
好久不见啊，终于放暑假了。这题好妙啊，写个题解吧。

## 题意
随机生成 $n$ 个点 $\left(x_i, y_i\right)$，你要用尽可能少的询问来找出这些点。坐标的绝对值不超过 $100$ 且任意两点之间的横纵坐标之差都大于等于 $1$。
每次询问给出 $a, b, c$，评测机按任意顺序返回这 $n$ 个点在直线 $ax + by + c = 0$ 上的投影（精度 $10^{-4}$）。你需要保证 $a, b, c$ 的绝对值均不超过 $100$。
$t$ 组数据。

$n \leq 25, \lvert a \rvert + \lvert b \rvert \geq 0.1, t \leq 50$

## 题解
一条直线显然不可能找出。考虑用两条直线找点。仔细思考就会发现，两条直线虽然可以找到所有 $x$ 坐标 和 $y$ 坐标，但无法确定如何匹配起来。所以加入第 $3$ 条直线。
我们可以通过询问一条与 $x$ 轴平行的直线来确定所有点的 $x$ 坐标。再通过询问一条与 $y$ 轴平行的直线来确定所有点的 $y$ 坐标。现在我们要用第 $3$ 条直线把这些点匹配。我们可以询问一条斜率极小的直线，比如 $y = 0.001x$，带入每个点的 $x$ 坐标，算出一个大致的 $y$ 坐标，然后去匹配准确的 $y$ 坐标。因为任意两点之间的横纵坐标之差都大于等于 $1$，所以不会找错。

## 代码
```cpp
// Please submit with C++17! It's best to use C++20 or higher version.
// By Koicy (https://koicy.ly)
// rbtree (i@koicy.ly)
// Drifting and struggling in the mist.

#include <algorithm>
#include <array>
#include <cmath>
#include <cstring>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <tuple>
#include <vector>
#define _CONSOLE 0
// #define EFILE ""

using namespace std;
using tp = long long;
constexpr tp ZERO = 0, ONE = 1, INF32 = -1u >> 2, INF = -1ull >> 2;

template <typename _Type, size_t _Size>
struct mray : array<_Type, _Size + 9> {
  _Type& operator[](size_t index) { return this->at(index); }
};

// Defines

// Constants

// Classes

// Typedeves

// Variables
tp n;

// Arrays
mray<double, 32> a, b;
mray<pair<double, double>, 32> c;

// Functions
void MIST() {
}

void STRUGGLING([[maybe_unused]] tp TEST_NUMBER) { // :/
  cin >> n;
  cout << "? 0 1 0" << endl;
  for (tp i = 1; i <= n; ++i) cin >> a[i] >> a[0];
  cout << "? 1 0 0" << endl;
  for (tp i = 1; i <= n; ++i) cin >> b[0] >> b[i];
  cout << "? -0.001 1 0" << endl;
  for (tp i = 1; i <= n; ++i) cin >> c[i].first >> c[i].second;
  stable_sort(a.begin() + 1, a.begin() + n + 1);
  stable_sort(c.begin() + 1, c.begin() + n + 1);
  cout << "! ";
  for (tp i = 1; i <= n; ++i) {
    double y = c[i].second + c[i].first * 1000 - a[i] * 1000, l = b[n];
    for (tp j = 1; j < n; ++j) {
      if (abs(y - b[j]) < abs(y - l)) l = b[j];
    }
    cout << a[i] << ' ' << l << ' ';
  }
  cout << endl;
}

#include <fstream>

signed main() {
  tp t = 0, _t = 1;
  ios::sync_with_stdio(0);
  cin.tie(0);
#if !_CONSOLE
#ifdef _LOCAL
  static ifstream _in("input.in");
  cin.rdbuf(_in.rdbuf());
#else
#ifdef EFILE
  static ifstream _in(EFILE ".in");
  static ofstream _out(EFILE ".out");
  cin.rdbuf(_in.rdbuf());
  cout.rdbuf(_out.rdbuf());
#endif
#endif
#endif
  cin >> _t;
  MIST();
  while (t < _t) STRUGGLING(++t);
  return 0;
}

//*/
```

---

## 作者：gghack_Nythix (赞：2)

## 前言：

vp 时遇到了这个题，但是我因为不会 E 题的优化做法导致没看这个题，没想到 F 题这么水。

## 分析：

首先，你询问 $y=0$ 可以得到所有点的 $x$ 坐标，询问 $x=0$ 可以得到所有点的 $y$ 坐标，这是显然的。

然后由于他会打乱顺序给你，所以考虑再询问一条直线。但是我们没有什么思路，所以去看看样例解释：

![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1826F/3b1f3044b777eff15fd4aeeb3484196dbbaecf67.png)

可以看到，他询问了一条 $0.2x=0.2y$ 的直线。这启发我们也构造一条这样的直线。

假设我们知道了某个点的 $x$ 坐标（上文已经询问过了），然后将他带入样例这组线，我们发现，在 $0.2x=0.2y$ 这条线上，它位于图中的 $(1,1)$ 处，再做一条经过 $(1,1)$ 点并和 $0.2x=0.2y$ 垂直的线，随后带入我们所询问的 $x$，就得到了一个近似的 $y$ 坐标。

但是使用样例的直线，真实的 $y$ 与求出来的 $y$ 相差过大，考虑询问一条 $y=\Delta x$ 的直线，其中 $\Delta$ 是一个极小值，那么我们的差距就会变得很小。

到这里，你可能会去开心的写代码，但是还有一个问题。题目中出题人返回的点精度不够。这导致我们的误差会很大。所以考虑在求出粗略的 $y$ 坐标后，在我们开始询问的较为精确 $y$ 坐标集合中取一个最接近的值就可以了。

```cpp
# include <bits/stdc++.h>
using namespace std;
struct node {
	double x , y;
} a[50][50] ;
void solve () {
	int cnt = 0 , n;
	cin >> n;
	cout << "? 0 1 0\n";
	++cnt ; for (int i = 1;i <= n;++i) cin >> a[cnt][i].x >> a[cnt][i].y;
	sort (a[cnt] + 1 , a[cnt] + n + 1 , [&] (node a , node b) { return a.x < b.x ; } );
	cout << "? 1 0 0\n";
	++cnt ; for (int i = 1;i <= n;++i) cin >> a[cnt][i].x >> a[cnt][i].y;
	sort (a[cnt] + 1 , a[cnt] + n + 1 , [&] (node a , node b) { return a.y < b.y ; } );
	cout << "? 0.001 1 0\n";
	++cnt ; for (int i = 1;i <= n;++i) cin >> a[cnt][i].x >> a[cnt][i].y;
	sort (a[cnt] + 1 , a[cnt] + n + 1 , [&] (node a , node b) { return a.x < b.x ; } );
	cout << "! \n";
	for (int i = 1;i <= n;++i) {
		double chuizhiK = 1000.00;
		double _0bx = a[1][i].x;
		double chuzhiB = a[3][i].y - chuizhiK * a[3][i].x;
		double real_y_for_comp = chuizhiK * _0bx + chuzhiB;
		double closet = 1000000000.00000;	
		for (int j = 1;j <= n;++j) {
			if (fabs(closet - real_y_for_comp) > fabs(a[2][j].y - real_y_for_comp) ) closet = a[2][j].y;
		}
		cout << fixed << setprecision(6) << _0bx << " " << closet << "\n";
	}	
}
signed main () {
	int T;
	cin >> T;
	while (T--) solve();
}
/*
	
*/
```

---

## 作者：Rei_Sen (赞：2)

やあやあ，这里是狂气之兔铃仙のだ $\sim$，由于题解区里其他人写得太简略了，于是铃仙在这里给大家放送详细版。

我们来一起审一下题目，题目要求我们用最少的询问次数来问出 $n$ 个点的具体坐标，每次询问的回答会给出点在直线上的投影的坐标，回答会打乱点的顺序，回答误差 $\varepsilon \in [-10^{-4},10^{-4}]$，你提供的答案误差应该在 $10^{-3}$ 以内，多测。

首先，我们得先弄明白我们最少需要多少次询问。这一点是容易的，考虑不打乱的情况，根据初中知识易得我们最多询问两次就能确定每个点，原因两直线确定一交点，每一次询问都相当于过该点做了一条垂直于询问直线的直线；如果打乱的话，我们就再来一次询问使得来确定一下每个 $x$ 所对应的 $y$ 就好了。综上，我们最少需要 $3$ 次才能问出 $n$ 个点的具体坐标。

前两次询问是简单地，我们可以问两条直线 $y = 0$ 和 $x = 0$ 来得出所有点的横纵坐标。

这个时候如果我们第三次询问能够在某个角度上满足一个单调性就能够对应出所有点的横纵坐标了。假设我们现在问一条直线 $y = kx$，现在我们希望每个点在这个直线上的投影的横坐标都是依据 $x$ 单调递增的，根据题目条件 $|x|,|y| \le 100$，$|x_a - x_b|,\,|y_a-y_b| \ge 1$，我们希望**与询问直线垂直的直线** $y = k_px+b_p$ 在 $\Delta x = 1$ 的情况下有 $\Delta y \gt 200$，所以不难得出此时 $k_p$ 应当满足 $k_p = \dfrac{\Delta y}{\Delta x} \gt 200$，故我们不难得出第三次询问 $k$ 的下界为 $k = \dfrac{-1}{k_p} = -\dfrac{1}{200}$。此时我们保证了 $x$ 和第三次询问所给定的点 $q$ 的横坐标 $q_x$ 能够满足单调性，即 $x_a \le x_b$，有 $q_{xa} \le q_{xb}$。

好，上面我们就解决了询问答案不带误差的情况，现在我们需要考虑如果询问带误差该怎么办。

我们首先设我们所能求到的纵坐标的误差为 $E_y$，带误差的纵坐标为 $y_e$，带误差的横坐标为 $x_e$，带误差的回答纵坐标为 $q_{ye}$，带误差的回答横坐标为 $q_{xe}$。

对于如何求出 $y_e$，我们首先不难通过询问直线的参数求出 $k_p = \dfrac{-1}{k}$，然后根据 $b_p = q_{ye} - k_pq_{xe}$ 得到 $b_p$，进而得到了与询问直线垂直的直线的方程 $y = k_px + b_p$，然后带入 $x_e$ 到 $y = k_px + b_p$ 中就不难求得 $y_e$ 了。现在我们希望我们有 $\max\,E_y \lt \min \,\{\dfrac{1}{2} + \varepsilon\}$，因为只有这样，我们找到的与计算结果相差最小的 $y$ 才是题目要求的 $y$。我们将回答所带的 $\varepsilon$ 带入全过程中，看看能得到什么：
$$
\begin{aligned}
y_e &= k_px_e+b_p\\
&= k_p(x + \varepsilon_{x_e}) + [(q_y + \varepsilon_{q_y}) - k_p(q_x+\varepsilon_{q_x})]\\
&= k_px + k_p \varepsilon_{x_e} + q_y + \varepsilon_{q_y} - k_pq_x - k_p\varepsilon_{q_x}\\
&= k_px + q_y - k_pq_x + k_p\varepsilon_{x_e} + \varepsilon_{q_e} - k_p\varepsilon_{q_x}
\end{aligned}
$$
由上式不难看出，我们的 $E_y = k_p\varepsilon_{x_e} + \varepsilon_{q_e} - k_p\varepsilon_{q_x}$，则我们不难得到：
$$
\begin{aligned}
\max \{k_p\varepsilon_{x_e} + \varepsilon_{q_e} - k_p\varepsilon_{q_x}\} &\lt \min \,\{\dfrac{1}{2} + \varepsilon\}\\
10^{-4}k_p + 10^{-4}k_p - (-10^{-4}k_p) &\lt \dfrac{1}{2} - 10^{-4}\\
3\times10^{-4} k_p &\lt 5\times 10^{-1} - 10^{-4}\\
k_p &\lt \dfrac{5\times 10^{-1} - 10^{-4}}{3\times10^{-4}}\\
k &\lt - \dfrac{3\times10^{-4}}{5\times 10^{-1} - 10^{-4}}
\end{aligned}
$$
故此时我们得到了我们询问的上界 $k \lt -\dfrac{3}{4999} \approx -6\times 10^{-4}$，综上，只要我们第三次询问的 $k \in (-5\times 10^{-3},\, -6 \times 10^{-4})$，就能通过该题。

PS：注意，询问的时候注意一下移项的变号。

时间复杂度 $O(n^2)$，但是用三分法可以做到更好的 $O(n \log n)$，这里懒得写了，因为 $O(n^2)$ 足以通过该题。

```cpp
// Powered by NEET. awa
#include <bits/stdc++.h>
using namespace std;
const int MAX_SIZE = 31;
typedef pair<double, double> pdd;
int n;
double x[MAX_SIZE];
double y[MAX_SIZE];
pdd p[MAX_SIZE];

void solve(){
	cin>>n;
	
	cout<<"? 0.00 100.00 0.00"<<endl;
	long double garb = 0;
	for(int i = 1; i <= n; i++) {
		cin>>x[i]>>garb;
	}
	sort(x + 1, x + 1 + n);
	
	cout<<"? 100.00 0.00 0.00"<<endl;
	for(int i = 1; i <= n; i++) {
		cin>>garb>>y[i];
	}
	
	cout<<"? 0.02 10.00 0.00"<<endl;
	for(int i = 1; i <= n; i++) {
		cin>>p[i].first>>p[i].second;
	}
	sort(p + 1, p + 1 + n);
	
	cout << "! ";
	for(int i = 1; i <= n; i++) {
		double k = 500;
		double b = p[i].second - k * p[i].first;
		double yy = k * x[i] + b;
		double mi = 2e8;
		for(int j = 1; j <= n; j++){
			if(fabs(yy - y[j]) <= fabs(yy - mi)){
				mi = y[j];
			}
		}
		cout << fixed << setprecision(7) << x[i] << ' ' << mi << ' ';
	}
	cout<<endl;
}

int main(){
	int T;
	cin>>T;
	while(T--){
		solve();
	}
	return 0;
}
```





---

## 作者：cwfxlh (赞：1)

# [CF1826F](https://www.luogu.com.cn/problem/CF1826F)      

首先注意几个特殊的性质，任意两点的横纵坐标之差均不小于 $1$，同时坐标绝对值不超过 $100$。       

考虑最少要询问多少次才能询问出来。一次显然是不行的，但询问两条直线其实是可以给出答案的，具体方式就是询问一条 $y=0$，再询问一条 $y=0.001x$，因为横纵坐标差距是很大的，所以投影的相对顺序在倾斜一点点的情况下不会变（其实这个斜率可以再大一点，大概可以达到 $0.01$ 左右），在第二根线上按投影做垂线，取第一根线的横坐标来算，即可得到点的坐标。    
    
    
然而因为出题人刻意限制返回投影坐标的精度，上述做法的精度是不足的，误差最大会达到 $10^{-1}$，无论如何都无法规避这个问题。于是我们只能采用三条直线。询问一个 $x=0$ 和 $y=0$，得到精确的横纵坐标值，再询问一条 $y=0.001x$，按上面的方法求出纵坐标误差稍大的点坐标，将求出来的纵坐标与 $x=0$ 的投影的纵坐标匹配，即可得出精确的纵坐标（因为求出来的纵坐标误差不超过 $10^{-1}$，所以可以匹配上）。      

代码：     

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,flg;
double x[503],y[503],k1,k2,k3,k4,k5,k6,k7,k8,k9,vx[503],vy[503];
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		cout<<"? 0 1 0"<<endl;
		fflush(stdout);
		for(int i=1;i<=n;i++)cin>>x[i]>>k1;
		cout<<"? 1 0 0"<<endl;
		fflush(stdout);
		for(int i=1;i<=n;i++)cin>>k1>>y[i];
		cout<<"? 0.1 -100 0"<<endl;
		fflush(stdout);
		for(int i=1;i<=n;i++)cin>>vx[i]>>vy[i];
		cout<<"! ";
		for(int i=1;i<=n;i++){
			k3=x[1];
			for(int j=1;j<=n;j++)if(fabs(k3-vx[i])>fabs(x[j]-vx[i]))k3=x[j];
			k1=-1000.0*k3+(vx[i]*1000.0+vy[i]);
			k2=y[1];
			for(int j=1;j<=n;j++)if(fabs(k2-k1)>fabs(y[j]-k1))k2=y[j];
			cout<<fixed<<setprecision(9)<<k3<<" "<<k2<<" ";
		}
		cout<<endl;
		fflush(stdout);
	}
	return 0;
}
```


---

