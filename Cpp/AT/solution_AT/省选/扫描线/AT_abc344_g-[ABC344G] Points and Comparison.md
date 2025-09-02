# [ABC344G] Points and Comparison

## 题目描述

**请注意特殊的输入格式。**

在 $xy$ 平面上有 $N$ 个点 $(X_i, Y_i)$。这些点的信息将通过输入给出。

另外，给定 $Q$ 组整数对 $(A_j, B_j)$。  
定义 $f(A_j, B_j)$ 为满足 $Y_i \ge A_j \times X_i + B_j$ 的 $i$ 的个数。

请计算 $\displaystyle\sum_{j=1}^Q f(A_j, B_j)$。

但是，由于本题中的 $Q$ 非常大，$(A_j, B_j)$ 不会直接给出。  
取而代之，给出 $G_0, R_a, R_b$，$(A_j, B_j)$ 按如下方式生成：

- 首先，对于 $n \ge 0$，定义 $G_{n+1} = (48271 \times G_n) \bmod (2^{31}-1)$。
- 对于 $j=1,2,\dots,Q$，$(A_j, B_j)$ 按如下方式生成：
  - $A_j = -R_a + (G_{3j-2} \bmod (2 \times R_a + 1))$
  - $B_j = -R_b + ((G_{3j-1} \times (2^{31}-1) + G_{3j}) \bmod (2 \times R_b + 1))$

由此生成方法可知，$A_j, B_j$ 满足如下约束：

- $-R_a \le A_j \le R_a$
- $-R_b \le B_j \le R_b$

## 说明/提示

### 数据范围

- 所有输入均为整数。
- $1 \le N \le 5000$
- $1 \le Q \le 10^7$
- $|X_i|, |Y_i| \le 10^8$
- $(X_i, Y_i)$ 互不相同。
- $0 \le G_0 < 2^{31}-1$
- $0 \le R_a \le 10^8$
- $0 \le R_b \le 10^{16}$

### 样例解释 1

该输入包含 $10$ 个询问。生成的 $(A_j, B_j)$ 分别为 $(-2,4), (0,2), (-4,-2), (4,-5), (3,1), (-1,3), (2,-5), (3,-1), (3,5), (3,-2)$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
7
2 -2
-1 -2
0 1
2 1
-2 2
1 2
0 -1
10
1 5 5```

### 输出

```
36```

# 题解

## 作者：CuteMurasame (赞：14)

### 思路

观察题目，发现如果直接按照题意模拟就是 $\mathcal O(NQ)$ 的，其中通过计算可得 $(NQ)_{\max}=5\times 10^{10}$，本题看似可通过。（注：AtCoder 评测机一秒大概可以跑 $5\times 10^9$，此题时限 10s）

于是我们可以写出最朴素的[暴力程序](https://atcoder.jp/contests/abc344/submissions/51118843)。T 得很彻底。

#### 优化 0

使用火车头。

#### 优化 1

众所周知，大数相乘，`long long` 取精确值，而 `double` 取比较近似值。于是我们考虑使用 `double`。（$x_i,y_i$ 也可以用 `double` 存储，可以避免过多的类型转换）

此处，虽然直接将 `long long` 改为 `double` 会变慢，还会丢失较高的精度，但是有一个 `std::fma` 函数，`fma(x,y,z)` 表示计算 $x\times y+z$ 的近似值，并且不会丢失太高的精度（虽然误差还是比较大）。

在 [cppreference](https://zh.cppreference.com/w/cpp/numeric/math/fma) 中，提到了：

> 此运算经常在硬件中实现为融合乘加 CPU 指令。如果硬件支持，那么期待定义相应的 `FP_FAST_FMA?` 宏，但多数实现即使在不定义这些宏时也利用该 CPU 指令。

经测试，在 AtCoder 上使用 `std::fma` 函数比直接用 `double` 更快。

[优化结果](https://atcoder.jp/contests/abc344/submissions/51119819)。

#### 使优化 1 中 `double` 运算更精确

观察到通过优化 1 后，在前两个测试点得到了 Wrong Answer。这是因为就算使用了 `std::fma`，但是 `double` 的精度还是不足。

此处我们不使用精度更高的 `long double`，否则会 TLE，而且很难卡进时限。

实际上，`double` 减 `double` 是比 `std::fma` 中的加法精度更准确的，所以我们可以把题目中式子 $Y_i\geq A_j\times X_i+B_j$ 化为 $Y_i-C_j\geq A_j\times X_i+(B_j-C_j)$，其中 $C_j$ 取 $B_j\bmod10^8$ 不仅可以避免一些精度丢失，跑得还不是很慢。

[优化结果](https://atcoder.jp/contests/abc344/submissions/51121044)。

#### 优化 2

经过改正后的优化 1，我们还是超时了几十毫秒。

这里有另一个优化：把能用 `const` 的变量全部使用 `const`，这样编译器会知道你的变量不会被改变，所以会跑得更快。

我们可以把每次循环计算的 $A_j,B_j,C_j,G_{3j-2},G_{3j-1},G_{3j}$ 分别在循环内开几个 `const` 变量，以达到加速效果。

到这里，我们就可以 AC 此题了。

[AC 记录（9950ms，3824 KB）](https://atcoder.jp/contests/abc344/submissions/51122985)。

---

## 作者：FFTotoro (赞：8)

其实这题暴力可以过的。参考 [MMNMM 的解法](https://atcoder.jp/contests/abc344/submissions/51099529)。

发现数据范围很大，容易被卡时或者卡精度。于是考虑用浮点数处理，具体地，对于一个询问 $(A,B)$，令 $B_1=\mathrm{lsh}(\mathrm{rsh}(B,31),31),B_2=B-\mathrm{lsh}(\mathrm{rsh}(B,31),31)$，其中 $\mathrm{lsh}(x,y)$ 表示 $x$ 左移 $y$ 位，$\mathrm{rsh}$ 同理。结合 `cmath` 中的一个函数叫做 `fma(x,y,z)`（返回值是 $xy+z$，可以满足精度需求），则 $f(A,B)=\sum\limits_{i=1}^N[Y_i-B_2\ge\mathrm{fma}(A,X_i,B_1)]$。

但是上面的做法太慢了。于是我们考虑指令集优化；指令集中有个很开挂的东西叫做 `avx512f`。[AVX-512 指令集相关内容可以参考这里。](https://zhuanlan.zhihu.com/p/136099964)

再加上一些常规卡常技巧（例如使用 `const`），时间复杂度为 $O(NQ)$ 的暴力可以直接通过。

放代码：

```cpp
#pragma GCC optimize("Ofast,unroll-loop")
#pragma GCC target("avx512f")
#include<bits/stdc++.h>
using namespace std;
const long P=(1ll<<31)-1;
double x[5000],y[5000];
int main(){
  ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  int n; cin>>n;
  for(int i=0;i<n;i++)cin>>x[i]>>y[i];
  int q; long g0,ra,rb,c=0; cin>>q>>g0>>ra>>rb;
  auto G=[&](){return (g0*=48271)%=P;};
  while(q--){
    const long g1=G(),g2=G(),g3=G(),b=-rb+(g2*P+g3)%(rb<<1|1);
    const double a=-ra+g1%(ra<<1|1),b1=(b>>31)<<31,b2=b-((b>>31)<<31);
    for(int i=0;i<n;i++)c+=y[i]-b2>=fma(a,x[i],b1);
  }
  cout<<c<<endl;
  return 0;
}
```

---

## 作者：ReTF (赞：7)

[题目](https://atcoder.jp/contests/abc344/tasks/abc344_g)

有意思的题。

题目要求的 $Y_i\ge A_j\times X_i+B_j$ 可以整理成 $-X_i\times A_j+Y_i\ge B_j$，即把 $(X_i,Y_i)$ 视作一条斜率为 $-X_i$，截距为 $Y_i$ 的直线，要求有多少直线在 $x=A_j$ 时纵坐标大于 $B_j$。

按照横坐标递增顺序扫描线，动态维护所有直线的排名。对于询问，二分查找即可。

时间复杂度 $O(T\log T)$，其中 $T=n^2+q$。

因为本题实现复杂且卡空间，提供几点实现上的技巧，希望能对您有所帮助：

- 不需要开 long long 的变量尽量强转，$A,B$ 数组可以不开，$G$ 数组可以滚动；
- 交点坐标可以换成分数形式来避免损失精度；
- 可以先把所有的交点预处理出来再和询问一起排序；
- 对于多于两个直线有同一个交点的情况，可以把同一横坐标的交点打成一个包，包里的交点按照两直线的排名较小值排序，按此顺序不断交换直线排名直到实现完全逆序。

[代码](https://atcoder.jp/contests/abc344/submissions/51122963)

---

## 作者：Hooch (赞：4)

### 题意

给定 $N$ 个二维平面上的点 $(X_i, Y_i)$ 与 $Q$ 组询问，第 $j$ 组询问给出 $(A_j, B_j)$，询问有多少个 $(X_i, Y_i)$ 满足 $Y_i \ge A_j \times X_i + B_j$。

### 题解

首先这个式子是 $A \times X + B \le Y$，移项得 $-A \times X + Y \ge B$。假设每组询问的 $A$ 相等，那么把 $(X, Y)$ 按 $-A \times X + Y$ 排序，然后二分答案即可。而对于 $A$ 不同的情况，沿用刚才的方法，考虑维护这个排序后的序列（记为 $B$）。

这个序列显然不能在线维护，考虑离线。离线后对 $Q$ 个询问按 $A$ 从大到小排序，思考 $A$ 变小后，序列会发生什么变化。也就是对于两个点对 $(X_i, Y_i), (X_j, Y_j)$ 且在序列 $B$ 中有 $i < j$，原本存在关系 $-A_1X_i + Y_i \le -A_1X_j + Y_j$，移项得 $-A_1(X_i - X_j) + (Y_i - Y_j) \le 0$。在 $A_1$ 变成 $A_2$ ( $A_2 \le A_1$ ) 后，如果 $i$ 被放到 $j$ 的后面，就存在 $-A_2(X_i - X_j) + (Y_i - Y_j) \ge 0$，孤立 $A_2$ 之后得到 $A_2 \le \frac{Y_i - Y_j}{X_i - X_j}$，而 $\frac{Y_i - Y_j}{X_i - X_j}$ 其实就是 $(X_i, Y_i)$ 与 $(X_j, Y_j)$ 两点所连直线的斜率。

然后这道题就可以做了。首先将询问按 $A = +\infty$ 时的 $-AX_i + Y_i$ 排序，其实就是将 $X_i$ 按从大到小排序，$X_i$ 相等时将 $Y$ 从小到大。接着开一个小根堆存序列 $B$ 中相邻两点的斜率。一个一个询问往后扫，每次扫到一个新询问，看一下小根堆存的斜率里面有没有可以被更新顺序的。然后对 $B_i$ 二分就行了。复杂度 $O(Q \log N + N^2 \log N)$，这题时限 10s 可以过。

code:

```cpp
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
using i64 = long long;
using ld = double;
const int N = 5E3 + 5, Q = 1E7 + 5, MOD = INT_MAX;
const ld eps = 1E-6;
int n, q, posi[N], pposi[N];
i64 g[Q << 2], ra, rb;
struct pos {
  i64 x, y;
  bool operator < (const pos &w) const {
    return x == w.x ? y < w.y : x < w.x;
  }
} a[N];
struct que {
  i64 a; i64 b;
  bool operator < (const que &w) const {
    return a < w.a;
  }
} b[Q];
struct node {
  i64 X, Y; 
  int x;
  bool operator < (const node &w) const {
    i64 l = X * w.Y;
    i64 r = Y * w.X;
    if (l < r) return false;
    if (l > r) return true;
    return x > w.x;
  }
  node (i64 a, i64 b, int c) {X = a, Y = b, x = c;}
} ;
priority_queue <node> pq;
void push(int x) {
  if (x <= 1 || x >= n + 1) return ;
  if (a[x - 1] < a[x]) pq.emplace(node(a[x].y - a[x - 1].y, a[x].x - a[x - 1].x, x));
}
signed main(void) {
  ios :: sync_with_stdio(false);
  cin.tie(nullptr); cout.tie(nullptr);
  cin >> n;
  for (int i = 1; i <= n; ++i) cin >> a[i].x >> a[i].y;
  cin >> q >> g[0] >> ra >> rb;
  for (int i = 1; i <= 3 * q; ++i)
    g[i] = g[i - 1] * 48271 % MOD;
  for (int i = 1; i <= q; ++i) {
    b[i].a = -ra + g[3 * i - 2] % (2 * ra + 1);
    b[i].b = -rb + (g[3 * i - 1] * MOD % (2 * rb + 1) + g[3 * i]) % (2 * rb + 1);
  }
  sort(b + 1, b + 1 + q); sort(a + 1, a + 1 + n);
  for (int i = 2; i <= n; ++i) push(i);
  i64 sum = 0;
  for (int i = 1; i <= q; ++i) {
    int A = b[i].a;
    while (!pq.empty()) {
      i64 X = pq.top().X, Y = pq.top().Y; int x = pq.top().x;
      if (X != a[x].y - a[x - 1].y || Y != a[x].x - a[x - 1].x) {pq.pop(); continue;}
      i64 l = X, r = 1LL * Y * A;
      if (l >= r) break;
      pq.pop(); swap(a[x - 1], a[x]); 
      push(x - 1); push(x + 1); 
    }
    int l = 1, r = n + 1;
    while (l < r) {
      int mid = (l + r) >> 1;
      auto check = [&](int k) {
        return a[k].y >= 1LL * a[k].x * A + b[i].b;
      } ;
      if (check(mid)) r = mid;
      else l = mid + 1;
    }
    sum += n - l + 1;
  }
  cout << sum << '\n';
}
```

---

## 作者：pan_g (赞：3)

[传送门1](https://www.luogu.com.cn/problem/AT_abc344_g)
[传送门2](https://atcoder.jp/contests/abc344/tasks/abc344_g)

这道题，可以先把原来的的式子直接转化成 $-X_i\times A_j + Y_i \geq B_j$ 。这个式子可以看成一条一次函数当 $x = A_j$ 时 $y\geq B_j$ 。

那么维护就十分简单了，先求出各式在 $-\infin$ 处的排名，再挨个找交点，可以动态维护每个点的排名，然后就可以二分求贡献，最后累加即可。

时间复杂度 $O(n^2+q\log n)$ 。

但是对于这道题来讲，可以采取一些小寄巧：
1. G 数组可以滚动，不需要全求出来。
2. 交点的 $x$ 值尽量用分数表示，少用实数型。

## AC CODE
其余具体可以看代码注释。
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef __int128_t bll;
typedef unsigned long long ull;
typedef long long ll;
typedef double lb;
const ll GenShin = 114514191981054188;
const int homo = 1145141919;
const int INF = 0x3f3f3f3f;
const int N = 5e3+10;
const int M = 1e7+10;
const int mod = 2147483647;
const int Kk = 48271;
inline ll read(){
    ll res = 0, f = 1;
    char c = getchar();
    for(;!isdigit(c); c = getchar()) if(c == '-') f *= -1;
    for(;isdigit(c); c = getchar()) res = (res << 3) + (res << 1) + c - '0';
    return res * f;
}
inline void write(ll x){
    if(x < 0) putchar('-'), x *= -1;
    if(x > 9) write(x/10);
    putchar(x%10+48); return ;
}
pair<ll, ll> Q[M]; // 提问的数组
int tot, rk[N], ord[N]; // 总交点数  两个排名数组（互为反函数）
int n, q;
pair<int, int> L[N]; // 每条直线
struct CrossPoint{
	ll p, q; // 表示为 p/q
	int l, r; // 两条直线的编号
}P[N*N]; // 交点
bool cmp(CrossPoint a, CrossPoint b){
	return a.p * b.q == b.p * a.q ? a.l == b.l ? a.r < b.r : a.l < b.l : a.p * b.q < b.p * a.q;
}
bool Rank(int a, int b){
	return 1ll * L[a].first * mod + L[a].second < 1ll * L[b].first * mod + L[b].second;
}
int main(){
	n = read();
	for(int i = 1;i <= n;i++) L[i].first = read(), L[i].second = read();
	sort(L + 1, L + 1 + n); // 按斜率大小进行排序（升序降序皆可）
	q = read(); ll G[3], Ra, Rb;
	G[0] = read(), Ra = read(), Rb = read();
	for(int i = 1;i <= q;i++){
		G[1] = 1ll * G[0] * Kk % mod;
		G[2] = 1ll * G[1] * Kk % mod;
		G[0] = 1ll * G[2] * Kk % mod;
		Q[i] = make_pair(- Ra + (G[1] % (2 * Ra + 1)), - Rb + ((1ll * G[2] * mod + G[0]) % (2 * Rb + 1)));
	} // 滚动数组求询问
	sort(Q + 1, Q + 1 + q); // 将询问排序，保证排名交换后不再换回去
	for(int i = 1;i <= n;i++) for(int j = i + 1;j <= n;j++){
		if(L[i].first == L[j].first) continue; // 对于斜率相同的直线必然无交点，且会影响结果
		++ tot; P[tot].l = i, P[tot].r = j;
		ll p = L[i].second - L[j].second, q = L[i].first - L[j].first;
		if(q < 0) p *= -1, q *= -1; // 如果分母为负数，那么就需要变号，所以变为正数，然后可以比较
		P[tot].p = p, P[tot].q = q;
	}
	sort(P + 1, P + 1 + tot, cmp);
	// 此处如此排序，着重讲一下。
	// 首先，已经按斜率排了序
	// 如此排序就保证了如果在同一交点时一定将斜率大的排名调到斜率小的排名（至少我写的是这样的）
	// 排名的交换顺序是有讲究的（想了好久 awa ）
	for(int i = 1;i <= n;i++) rk[i] = i;
	sort(rk + 1, rk + 1 + n, Rank);
	// 在负无穷处排序
	for(int i = 1;i <= n;i++) ord[rk[i]] = i;
	int id = 1; ll ans = 0;
	for(int i = 1;i <= q;i++){
		for(;id <= tot;id++){
			if(P[id].p > P[id].q * Q[i].first) break ;
			// 如果交点的 x 大于当前查询的 x ，那么无需继续交换了
			swap(rk[ord[P[id].l]], rk[ord[P[id].r]]);
			swap(ord[P[id].l], ord[P[id].r]);
		}
		int l = 1, r = n, res = -1, mid;
		while(l <= r){
			mid = l+r >> 1;
			if(-L[rk[mid]].first * Q[i].first + L[rk[mid]].second < Q[i].second) l = mid + 1;
			else r = mid - 1, res = mid;
		} // 二分找大于等于 B 的第一个值
		if(res != -1) ans += 1ll * (n - res + 1);
		// 找到就可以总结贡献了
	}
	write(ans);
    return 0;
}
```

---

