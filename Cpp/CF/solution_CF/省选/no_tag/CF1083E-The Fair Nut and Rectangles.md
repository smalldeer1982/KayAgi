# The Fair Nut and Rectangles

## 题目描述

Fair Nut 被困在了平面世界。他需要解决这个任务才能脱困。

给定 $n$ 个矩形，每个矩形的顶点分别为 $(0, 0)$、$(x_i, 0)$、$(x_i, y_i)$、$(0, y_i)$。对于每个矩形，还给定一个数 $a_i$。你可以选择其中一些矩形，使得所选矩形的并集面积减去这些矩形对应 $a_i$ 的和最大。

保证不存在嵌套的矩形。

Nut 不知道如何求解答案，所以他请求你的帮助。

## 说明/提示

在第一个样例中，选择第一个和第二个矩形可以得到最优答案。

在第二个样例中，选择第一个和第二个矩形也可以得到最优答案。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
4 4 8
1 5 0
5 2 10
```

### 输出

```
9```

## 样例 #2

### 输入

```
4
6 2 4
1 6 2
2 4 3
5 3 8
```

### 输出

```
10```

# 题解

## 作者：Sooke (赞：7)

### 解题思路

因为矩形互不包含，所有给矩形排个序，满足 $x_i$ 单调递增，$y_i$ 单调递减。

首先有个 $\mathrm{dp}$ 的苗头：设做到排序后的第 $i$ 个矩形了，选择这个矩形，面积并减去权值和的最大值为 $f_i$。

很明显从上一个选择的第 $j$ 的矩形转移过来，则：

$$f_i = \max_{j\in [0,\,i-1]}\{f_j + S_i-a_i-S_i \cap S_j\}$$

其实不过是直接加上该矩形的贡献，又因为面积有重合，减掉而已。由于 $x_i,\,y_i$ 的单调性，配合下图，一定有：

$$S_i = x_iy_i,\ S_i \cap S_j = x_jy_i$$

![](https://i.loli.net/2019/01/11/5c384953e1f20.png)

但暴力转移是一定不行的，我们思考转移式有什么优美的性质。

$$f_i = \max_{j\in [0,\,i-1]}\{f_j +x_iy_i-x_jy_i - a_i\}$$

设它的决策点就是 $j$：

$$f_i = f_j +x_iy_i-x_jy_i - a_i$$

移项可得：

$$\underline{f_j}_{\ y} = \underline{y_i}_{\ k}\underline{x_j}_{\ x} + \underline{f_i - x_iy_i + a_i}_{\ b}$$

注意到 $y_i$ 单调递减，可作为斜率，用**斜率优化**维护好上式即可。

---

### 代码实现

当时读优没开 $\mathrm{long\ long\ WA}$ 了一发。

```cpp
#include <cmath>
#include <cstdio>
#include <algorithm>

inline long long read() {
    char c = getchar(); long long x = 0;
    while (c < '0' || c > '9') { c = getchar(); }
    while (c >= '0' && c <= '9') { x = (x << 1) + (x << 3) + (c & 15); c = getchar(); }
    return x;
}

typedef long long lol;

const int maxN = 2000005;
const double eps = 1e-10;

int n, l, r, q[maxN];
long long ans, f[maxN];

struct Square { lol x, y, w; } s[maxN];

bool operator <(Square x, Square y) { return x.y > y.y; }

inline double getX(int u) { return s[u].x; }
inline double getY(int u) { return f[u]; }
inline double getSlope(int u, int v) { return std::abs(getX(v) - getX(u)) < eps ? 1e10 : (getY(v) - getY(u)) / (getX(v) - getX(u)); }

int main() {
    n = read();
    for (int i = 1; i <= n; i++) { s[i].x = read(); s[i].y = read(); s[i].w = read() ;}
    std::sort(s + 1, s + n + 1);
    for (int i = 1; i <= n; i++) {
        while (l < r && getSlope(q[l], q[l + 1]) >= s[i].y) { l++; }
        f[i] = s[i].x * s[i].y - s[i].w;
        if (l <= r) { f[i] = std::max(f[i], f[q[l]] + (s[i].x - s[q[l]].x) * s[i].y - s[i].w); }
        ans = std::max(ans, f[i]);
        while (l < r && getSlope(q[r - 1], q[r]) <= getSlope(q[r], i)) { r--; } q[++r] = i;
    }
    printf("%I64d\n", ans);
    return 0;
}
```

---

## 作者：LCuter (赞：3)

## CF1083E 题解

##### $\text{Description}$

给定 $n$ 个左下角在 $(0,0)$，四边与 $x,y$ 轴平行的矩形（以右上角顶点的形式给出），保证两两不包含，每个矩形有一个权值 $a_i$，试选出若干个矩形，使得其面积并减去权值和最大。

$1\le n\le 10^6,1\le x_i,y_i\le 10^9,0\le a_i\le x_iy_i$

##### $\text{Solution}$

考虑两两不包含的含义，即我们将这些顶点按横坐标升序排列后，其纵坐标单调递减。

那么，我们按如上顺序将矩形加入决策集，可以发现其增加的面积只与上一个加入决策集的矩形相关，因此可以动态规划。

设 $f_i$ 表示最后一个选取了第 $i$ 个矩形的决策集中最大的答案，则有
$$
f_i =\max_{0\le j<i}\{f_j+y_i(x_i-x_j)-a_i\}=x_iy_i-a_i+\max_{0\le j<i}\{f_j-y_ix_j\}
$$
注意到后者是两变量的乘积项，所以考虑斜率优化，考虑用 $j$ 转移 $i$ 时，有：
$$
f_i-x_iy_i+a_i+x_jy_i=f_j
$$
将 $f_j$ 看作 $y$，将 $x_j$ 看作 $x$，则 $y_i$ 为斜率，我们要最大化截距。

因此，我们考虑维护一个上凸壳，也即相邻两点连线斜率单调递减，那么套路性地，我们需要找到与下一点连线的斜率最大但小于 $y_i$ 的点，该点即最优决策点。

回到问题本身，注意到 $y_i$ 单调递减，则可用单调队列维护上凸壳，每次转移时先从队首弹出与下一点连线的斜率比 $y_i$ 大的点，然后取队首作为决策点，最后在插入该点时删去不符合条件的决策点即可。

时间复杂度 $\mathcal O(n\log n)$，瓶颈在于排序。

##### $\text{Code}$

```cpp
#include<bits/stdc++.h>
#define REG register
using namespace std;
typedef long long ll;
typedef double D;
inline void read(int& x){
	static char c;
	while(!isdigit(c=getchar()));x=c^48;
	while(isdigit(c=getchar()))x=(x*10)+(c^48);
}
inline void read(ll& x){
	static char c;
	while(!isdigit(c=getchar()));x=c^48;
	while(isdigit(c=getchar()))x=(x*10)+(c^48);
}

const int N=1000005;

int n;

struct Rec{ll x,y,a;}rec[N];
inline bool cmp(Rec u,Rec v){return u.x<v.x;}

ll F[N];
inline ll Calc(int i,int j){return F[j]+rec[i].y*(rec[i].x-rec[j].x)-rec[i].a;}
inline D Slp(int i,int j){return 1.0*(F[i]-F[j])/(rec[i].x-rec[j].x);}

int Q[N],head=1,tail;

inline void Work(){
	read(n);
	for(REG int i=1;i<=n;++i)
    	read(rec[i].x),read(rec[i].y),read(rec[i].a);
	sort(rec+1,rec+n+1,cmp);
	F[1]=rec[1].x*rec[1].y-rec[1].a;
	Q[++tail]=0;
	for(REG int i=1;i<=n;++i){
    	while(head<tail&&Slp(Q[head],Q[head+1])>=rec[i].y) ++head;
    	F[i]=Calc(i,Q[head]);
    	while(head<tail&&Slp(Q[tail-1],Q[tail])<Slp(Q[tail],i)) --tail;
    	Q[++tail]=i;
    }
	ll Mx=0;
	for(REG int i=1;i<=n;++i) Mx=max(Mx,F[i]);
	printf("%lld\n",Mx);
}

int main(){Work();}
```



---

## 作者：1saunoya (赞：3)

因为任意两个矩形不包含，所以不存在 $x_i \leq x_j \& y_i \leq y_j$。

按 $x_i$ 排序。

令 $f_j$ 为 $j$ 是最右边的那个矩形最多的贡献。
容易得到。

$f_i = \max\{f_j + (x_i - x_j) \times y_i\} - a_i$

设两个决策点 $x, y$

使得 $j$ 优于 $k$。

$f_j + (x_i - x_j) \times y_i \geq f_k + (x_i - x_k) \times y_i$

即 $f_j + x_iy_i - x_jy_i \geq f_k + x_iy_i - x_ky_i$

$f_j - f_k \geq (x_j - x_k)y_i$ $\to$ $\frac{f_j-f_k}{x_j-x_k} \geq y_i$

```cpp
#include <bits/stdc++.h>
const int B = 2 << 20;
struct streambufcin {
	std::streambuf *in;
	streambufcin() {
		std::ios::sync_with_stdio(false);
		std::cin.tie(NULL);
		in = std::cin.rdbuf();
		bg = ed = NULL;
//		freopen("testdata.txt", "r", stdin);
	}
	char buf[B], *bg, *ed, ch;
	char gc() { return bg == ed ? ed = buf + in -> sgetn(bg = buf, B), (bg == ed ? -1 : *bg++) : *bg++; }
	template<class T>
	streambufcin &operator >> (T &x) {
		bool neg = false;
		for (ch = gc(); !isdigit(ch); ch = gc());
		if (ch == '-')
			neg = true;
		for (x = 0; isdigit(ch); ch = gc())
			x = x * 10 + ch - 48;
		if (neg)
			x = -x;
		return *this;
	}
	streambufcin &operator >> (char c) {
		while (isspace(ch))
			ch = gc();
		c = ch;
		return *this;
	}
} cin;

struct streambufcout {
	std::streambuf *out = std::cout.rdbuf();
	char buf[B], *optr = buf;
	streambufcout() { out = std::cout.rdbuf(); }
	~streambufcout() { flush(); }
	void flush() { out -> sputn(buf, optr - buf); optr = buf; }
	void pc(char c) {
		if (optr == buf + B)
			flush();
		*optr++ = c;
	}
	template<class T>
	streambufcout &operator << (T x) {
		static int st[233], top;
		do {
			st[++top] = x % 10;
			x /= 10;
		} while (x);
		while (top)
			pc(st[top--] ^ 48);
		return *this;
	}
	streambufcout &operator << (char c) { pc(c); return *this; }
} cout;

int n;
const int N = 1e6 + 1;
int l, r, q[N];
const double eps = 1e-10;
struct Square { long long x, y, w; bool operator <(const Square &rhs) const { return y > rhs.y; } } s[N];
long long f[N];
double getX(int u) { return s[u].x; } 
double getY(int u) { return f[u]; }
double getslope(int u, int v) { return std::abs(getX(v) - getX(u)) < eps ? 1e10 : (getY(v) - getY(u)) / (getX(v) - getX(u)); }

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) { cin >> s[i].x >> s[i].y >> s[i].w; }
	std::sort(s + 1, s + n + 1); q[l = r = 0] = 0;
	long long answer = 0;
	for (int i = 1; i <= n; i++) {
		while (l < r && getslope(q[l], q[l + 1]) >= s[i].y) { ++l; } 
		f[i] = 1ll * s[i].x * s[i].y - s[i].w;
		if (l <= r) { int j = q[l]; f[i] = std::max(f[i], f[j] + 1ll * (s[i].x - s[j].x) * s[i].y - s[i].w); }
		answer = std::max(answer, f[i]);
		while (l < r && getslope(q[r - 1], q[r]) <= getslope(q[r], i)) { --r; } q[++r] = i;
	}
	cout << answer << '\n';
	return 0;
}
```

---

## 作者：Walrus (赞：2)

斜率优化好题。当笔记了。

注意到这里的矩阵是**互不包含**，且具有固定端点 $(0,0)$ 并在同一象限，可以考虑按横坐标先排序。

对于这种选点问题，就考虑上一个从哪个矩形转移过来更优。

**Tips：横坐标在数组存储里是行，也就是数组里的纵坐标。注意不要混淆。**

故令 $dp_i$ 表示选到第 $i$ 个矩形的最大价值，然后转移的话枚举 $1\sim i-1$，找到最优的一个转移。怎么算价值呢？首先要明确价值（新加入的） $W=x_i\times y_i-w_i-X$。$X$ 是和上一个矩阵的交。怎么算 $X$ 呢？发现对于按横坐标排序的矩阵两两交可以快速得到，假设上一个从 $j$ 转移，那么有 $X=x_j\times y_i$。这里读者自行画图理解，不放图了。

故朴素转移有：
$$dp_i=\max \limits_{1\leq j < i} \{dp_j+x_i\times y_i-w_i-x_j\times y_i\}$$

整理一下：
$$dp_i=\max \limits_{1\leq j < i} \{dp_j+y_i\times(x_i-x_j)-w_i\}$$

这显然是 $O(N^2)$ 的，不可取，考虑优化。注意到 $y_i\times(x_i-x_j)$ 这一项，典型的斜率优化形式。

这里假设 $j$ 比 $k$ 更优。那么有：
$$dp_j+y_i\times (x_i-x_j)-w_i>dp_k+y_i\times (x_i-x_k)-w_i$$

整理并移项：
$$\dfrac{dp_j-dp_k}{x_j-x_k}>y_i$$

然后就可以用单调队列维护这个凸包，属于类板板题，时间复杂度 $O(N)$。

```cpp
#include <bits/stdc++.h>
#define FASTIO ios::sync_with_stdio(0), cin.tie(nullptr), cout.tie(nullptr);
#define rep(i, j, k) for(int i = j; i <= k; ++i)
#define pre(i, j, k) for(int i = j; i >= k; --i)
#define pb push_back
#define int long long
#define inf 0x3fffffff
#define PII pair<int, int>
#define fi first
#define se second

using namespace std;

const int N = 2e6 + 5;

int n, C, L, l, r, res, h[N];
int dp[N], f[N], q[N << 1]; 

struct Martix {
	int w, x, y;
	bool operator < (const Martix &a) const {return x == a.x ? y < a.y : x < a.x;}
} a[N];

int X(int i) {//这里没有判，严谨点可以加上除数为 0 的情况
	return a[i].x;
}

int Y(int i) {
	return dp[i];
}

double slope(int i, int j) {
	return 1.0 * (Y(j) - Y(i)) / (X(j) - X(i));
} 

void insert(int i) {
	while(l < r && slope(q[r - 1], q[r]) <= slope(q[r - 1], i)) --r;
	q[++r] = i;
}

signed main() {
	FASTIO
	
	cin >> n;
	rep(i, 1, n) cin >> a[i].x >> a[i].y >> a[i].w;
	sort(a + 1, a + 1 + n);
	 
	l = 0, r = 1, q[++l] = 0;
	rep(i, 1, n) {
		while(l < r && slope(q[l], q[l + 1]) >= a[i].y) ++l;
		dp[i] = max(dp[i], dp[q[l]] + (a[i].x - a[q[l]].x) * a[i].y - a[i].w);
		res = max(res, dp[i]);
//		cout << i << ' ' << q[l] << '\n';
		insert(i);
	}
	cout << res;
	return 0;
}
```

---

## 作者：Iniaugoty (赞：2)

> 给定 $n$ 个两两不包含的矩形，左下角 $(0, 0)$，右上角 $(x _ i, y _ i)$，权值 $a _ i$。请你选出若干个矩形，最大化面积并减去权值和。求这个最大值。

~~根据题单名称可以知道~~很难不想到 DP。

设 $dp _ i$ 表示在前 $i$ 个矩形中，选出一些，其中强制选了 $i$，的最大值。则答案为 $\max _ {i = 1} ^ {n} dp _ i$。

但直接这样做的话很凌乱，不知道哪里被覆盖过，哪里没有，不便于转移。

状态不变。不妨按 $x$ 上升排序，由于题目要求矩形两两不包含，显然 $y$ 是下降的。

考虑枚举上一个选的矩形 $j(0 \le j < i)$ 进行转移（钦定第 $0$ 个矩形 $(0, 0)$，权值 $0$）。

由于 $x$ 上升，可知 $[x _ j, x _ i]$ 这一段区间还没有被覆盖过，同时 $i$ 在这里的高度为 $y _ i$；由于 $y$ 下降，可知 $[0, x _ j]$ 这一段区间内已覆盖的高度全部高于 $y _ i$，$i$ 无法做出任何贡献。

于是

$$dp _ i = \max _ {j = 0} ^ {i - 1} dp _ j + (x _ i - x _ j) y _ i - a _ i$$

很难不发现这是斜率优化的形式。稍作变形。

$$dp _ j = y _ i x _ j + dp _ i - a _ i + x _ i y _ i$$

其中 $dp _ j$ 是 $y$，$y _ i$ 是斜率 $k$，$x _ j$ 是 $x$，$dp _ i - a _ i + x _ i y _ i$ 是截距 $b$。

由排序可知 $x$ 上升，$k$ 下降。同时要求的是最大值，最大化截距。单调队列维护上凸壳即可。DP 部分时间复杂度 $O(n)$。

实现上，如果维护斜率转除为乘的话，会爆 `long long`，请使用 `__int128` 强转。并且 CF 32 位机上 `__int128` 会 CE，请交到 64 位语言上。

总时间复杂度是 $O(n \log n)$，瓶颈在排序。

[code。](https://codeforces.com/contest/1083/submission/270634264)

---

## 作者：VenusM1nT (赞：1)

因为矩形互不包含，所以可以排个序，使 $x$ 单增，$y$ 单减。  
于是不妨设 $f_i$ 为已经考虑完前 $i-1$ 个矩形并选择 $i$ 的权值，很容易就可以得到一个转移方程：
$$f_i=\max_{j=1}^{i-1}\{f_j+S_i-a_i-S_i\cap S_j\}$$

又根据容斥易得

$$S_i\cap S_j=x_j\times y_i$$

于是可以写出最终的转移方程：

$$f_i=\max_{j=1}^{i-1}\{f_j+x_i\times y_i-x_j\times y_i-a_i\}$$

此时开始斜率优化标准流程，考虑 $j$ 比 $k$ 更优，有

$$f_j+x_i\times y_i-x_j\times y_i-a_i\ge f_k+x_i\times y_i-x_k\times y_i-a_i$$

移项，把含有 $i$ 的移到一边

$$f_j-f_k\ge(x_j-x_k)\times y_i$$

除过去，得到

$$y_i\leq\frac{f_j-f_k}{x_j-x_k}=k$$

为了得到计算式再移一次项

$$f_j=x_j\times y_i-x_i\times y_i+a_i+f_i$$

稍加思索得

$$y=f_j,k=y_i,x=x_j,b=f_i+a_i-x_i\times y_i$$

又 $k=y_i$ 单减，因此是个上凸壳。

然后就可以快乐维护了

```cpp
#include<bits/stdc++.h>
#define N 1000000
#define reg register
#define inl inline
#define int long long
#define inf 1e18
using namespace std;
struct Node
{
	int x,y,val;
	friend bool operator < (const Node &x,const Node &y)
	{
		return x.y>y.y;
	}
}a[N+5];
int n,f[N+5];
int q[N*2+5],head,tail;
inl double Calc(reg int x,reg int y)
{
	return a[x].x==a[y].x?inf:((double)(f[y]-f[x])/(double)(a[y].x-a[x].x));
}
signed main()
{
	scanf("%lld",&n);
	for(reg int i=1;i<=n;i++) scanf("%lld %lld %lld",&a[i].x,&a[i].y,&a[i].val);
	sort(a+1,a+n+1);
	head=1;
	reg int ans=0;
	for(reg int i=1;i<=n;i++)
	{
		while(head<tail && Calc(q[head],q[head+1])>=a[i].y) head++;
		f[i]=a[i].x*a[i].y-a[i].val;
		if(head<=tail) f[i]=max(f[i],f[q[head]]+(a[i].x-a[q[head]].x)*a[i].y-a[i].val);
		ans=max(ans,f[i]);
		while(head<tail && Calc(q[tail-1],q[tail])<=Calc(q[tail],i)) tail--;
		q[++tail]=i;
	}
	printf("%lld\n",ans);
	return 0;
}
```	

---

## 作者：Cl41Mi5deeD (赞：0)

给定了 $n$ 个原点为左下端点，$(x_i,y_i)$ 为右上端点的矩形与其权值，求数个矩形面积减去其权值和的最大值。

**给出的矩形保证任意两个矩形的面积不会出现包含关系**。而所有矩形的左下端点是重合的。

即 $\forall(x_i,y_i),(x_j,x_j),x_i>x_j,y_i<y_j$ 否则一定会出现面积的重叠。进而，$x_i$ 递增时，$y_i$ 递减。考虑对 $x_i$ 排序使得数据有单调性。

写出 $O(n^2)$ 的 dp 方程：
$$
dp[i]=max_{j=0}^{i-1}\{dp[j]+y_i*(x_i-x_j)-a_i\}
$$

$dp[i]$ 表示取第 $i$ 个矩形的最优解，上一次取了第 $j$ 个矩形。

![](https://cdn.luogu.com.cn/upload/image_hosting/cnulmo7a.png)

考虑斜率优化，将方程转化为 $Y=K*X+B$ 的形式。

$$
dp[j]=w[i].y*w[j].x+dp[i]+w[i].a-w[i].y*w[i].x
$$

$$
Y=dp[j]
$$
$$
K=w[i].y
$$
$$
X=w[j].x
$$
$$
B=dp[i]+w[i].a-w[i].y*w[i].x
$$
保证 $X$ 递增时 $K$ 递减。维护上凸壳即可。

```cpp
#include<bits/stdc++.h>
#define int long long
#define MAXN 1000005
using namespace std;
int n,ans;
inline void read(int& x){
	static char c;
	while(!isdigit(c=getchar()));x=c^48;
	while(isdigit(c=getchar()))x=(x*10)+(c^48);
}
struct square{
	int x,y,a;
}w[MAXN];
bool cmp(square a,square b){
	return a.x<b.x;
}
int dp[MAXN],q[MAXN],h,t;
inline int Y(int x){
	return dp[x];
}
inline int X(int x){
	return w[x].x;
}
inline int K(int x){
	return w[x].y;
}
inline double slope(int x_1,int x_2){
	if(X(x_1)==X(x_2))return 1e18;
	return 1.0*(Y(x_1)-Y(x_2))/(X(x_1)-X(x_2));
}
signed main(){
	read(n);
	for(register int i=1;i<=n;i++)read(w[i].x),read(w[i].y),read(w[i].a);
	sort(w+1,w+1+n,cmp);
	for(register int i=1;i<=n;i++){
		//dp[i]=max(dp[i],dp[j]+(w[i].x-w[j].x)*(w[i].y)-w[i].a);
		//dp[i]=dp[j]+w[i].y*w[i].x-w[i].y*w[j].x-w[i].a
		// Y   = K      X    +             B
		//dp[j]=w[i].y*w[j].x+dp[i]+w[i].a-w[i].y*w[i].x
		while(t>h&&K(i)<=slope(q[h+1],q[h]))++h;
		dp[i]=dp[q[h]]+(w[i].x-w[q[h]].x)*w[i].y-w[i].a;
		ans=max(ans,dp[i]);
		while(t>h&&slope(i,q[t-1])>=slope(q[t],q[t-1]))--t;
		q[++t]=i;
	}
	printf("%lld",ans);
	return 0;
}
```
这个题时间卡的比较狠，优化全带上。

---

## 作者：songhongyi (赞：0)

这题确实简单啊。

两个矩形包含的充要条件是 $x_i>x_j$ 且 $y_i>y_j$。因此所有给出的点一定构成一个一象限的右上凸壳。

也就是说，我们按照 $x$ 升序排序，$y$ 一定是降序。

考虑 DP 答案。设 $f_i$ 表示考虑到第 $i$ 个的答案。枚举上一个矩形，则：

$$
f_i = \min _{j<i}\left(f_j + y_i \times \left(x_j-x_i\right)\right)
$$

不难发现这是一个很典型的斜率优化转移形式。正好 $y$ 递减，也就是决策点单调，可以用单调队列维护。因为要排序，复杂度 $O(n \log n)$。

核心代码：

```cpp
i64 dp[ 1000010 ];
struct Node
{
    i64 x, y;
    i64 a;
} a[ 1000010 ];
i64 X( int j )
{
    return a[ j ].x;
}
i64 Y( int j )
{
    return dp[ j ];
}
long double slope( int i, int j )
{
    return ( long double )( Y( j ) - Y( i ) ) / ( X( j ) - X( i ) );
}
deque< int > q;
int main()
{
    cin.tie( 0 );
    int n;
    read( n );
    for ( int i = 1; i <= n; i++ )
    {
        read( a[ i ].x ), read( a[ i ].y ), read( a[ i ].a );
    }
    sort( a + 1, a + n + 1, []( Node a, Node b ) { return a.x < b.x; } );
    q.push_back( 0 );
    dp[ 1 ] = a[ 1 ].x * a[ 1 ].y - a[ 1 ].a;
    for ( int i = 1; i <= n; i++ )
    {
        while ( q.size() > 1
                and slope( *( q.begin() ), *( q.begin() + 1 ) ) >= a[ i ].y )
        {
            q.pop_front();
        }
        int j = q.front();
        dp[ i ] = dp[ j ] + a[ i ].y * ( a[ i ].x - a[ j ].x ) - a[ i ].a;
        while ( q.size() > 1
                and slope( *( q.end() - 1 ), *( q.end() - 2 ) )
                        <= slope( *( q.end() - 2 ), i ) )
        {
            q.pop_back();
        }
        q.push_back( i );
    }
    i64 ans = 0;
    for ( int i = 1; i <= n; i++ )
    {
        ans = max( ans, dp[ i ] );
    }
    cout << ans << endl;
}
```



---

## 作者：Umbrella_Leaf (赞：0)

### 题意

> 平面上有 $n$ 个以 $(0,0)$ 为左下角的矩形，每个矩形拥有权值 $a_i$，保证矩形之间互不包含。现在要求选择若干个矩形，使得矩形的面积并减去矩形权值和尽可能大。$1\le n\le 10^6$。

### 题解

先将矩形按 $x$ 坐标排序。那么由于矩形互不包含，所以 $y$ 坐标递减。

容易设计 $dp_i$ 表示考虑了第 $1$ 到 $i$ 个矩形，且必须选择第 $i$ 个时最大的答案。有转移：

$$dp_i=\max_{1\le j<i}dp_j+(x_i-x_j)y_i-a_i$$

这个式子可以斜率优化。具体来说，我们把式子转化成：

$$dp_j=x_jy_i+(dp_i-x_iy_i+a_i)$$

我们把 $(x_j,dp_j)$ 看成一个点，那么转移到 $i$ 时相当于询问一条斜率为 $y_i$ 的直线经过哪个点时截距最大。

由于 $y_i$ 递减，我们只需要用单调队列维护上凸壳即可。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
int n;
struct node{
    ll x,y,val;
    bool operator <(const node &b)const{return x<b.x;}
}a[1000005];
int que[1000005],head,tail;
ll dp[1000005];
ll read(){
    ll x=0;char c=getchar();
    while(c<'0'||c>'9')c=getchar();
    while(c>='0'&&c<='9')x=x*10+(c^'0'),c=getchar();
    return x;
}
int main(){
    n=read();
    for(int i=1;i<=n;i++)a[i].x=read(),a[i].y=read(),a[i].val=read();
    sort(a+1,a+n+1);
    head=1,tail=0;
    ll ans=0;
    for(int i=1;i<=n;i++){
        while(head<tail&&1.0*(dp[que[head+1]]-dp[que[head]])/(a[que[head+1]].x-a[que[head]].x)>=a[i].y)head++;
        dp[i]=a[i].x*a[i].y-a[i].val;
        if(head<=tail)dp[i]=max(dp[i],dp[que[head]]-a[i].y*a[que[head]].x+a[i].y*a[i].x-a[i].val);
        ans=max(ans,dp[i]);
        while(head<tail&&1.0*(dp[que[tail]]-dp[que[tail-1]])/(a[que[tail]].x-a[que[tail-1]].x)<=1.0*(dp[i]-dp[que[tail]])/(a[i].x-a[que[tail]].x))tail--;
        que[++tail]=i;
    }
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：_lxy_ (赞：0)

[博客食用效果更佳](https://www.cnblogs.com/lxy-2022/p/CF1083E-Solution.html)
#### 题意

一个坐标系中 $n$ 个矩形，每个矩形左下角在 $(0,0)$，右上角在 $(x_i,y_i)$，有权值 $a_i$，保证任意两个矩形不出现包含关系，让选出若干个矩形，求矩形面积并减权值和的最大值。

#### 分析

由于保证不出现包含关系，因此将矩形按左右距从小到大排，发现如果一个矩形的上下距不比前面的所有矩形上下距长，而它左右距也一定比前面的所有左右距短，那么前面一定存在一个矩形完全包含它，与题意矛盾。因此矩形的上下距一定单调递增。

设 $dp_i$ 表示以 $i$ 为结尾的矩形序列面积并减权值和的最大值。从 $dp_j$ 转移多出来的面积并是 $(y_i-y_j)x_i$，因此转移方程为：
$$
dp_i=dp_j+(y_i-y_j)x_i-w_i
$$
斜率优化即可。

#### 核心代码

```cpp
struct node{
    int x,y,w;
    bool operator < (const node &o)const{return y<o.y;}
}a[MAXN];
double gety(int i){return dp[i];}double getx(int i){return a[i].y;}
double slope(int i,int j){return (gety(j)-gety(i))/(getx(j)-getx(i));}
signed main(){
    qread(n);int i,j;for(i=1;i<=n;i++) qread(a[i].x,a[i].y,a[i].w);sort(a+1,a+1+n);h=t=1;
    for(i=1;i<=n;i++){
        while(h<t&&slope(q[h],q[h+1])>=a[i].x) h++;
        int j=q[h];dp[i]=dp[j]+(a[i].y-a[j].y)*a[i].x-a[i].w;
        while(h<t&&slope(q[t-1],q[t])<=slope(q[t],i)) t--;q[++t]=i;
        ans=qmax(ans,dp[i]);    
    }printf("%lld\n",ans);
    return 0;
}
```

[record](https://codeforc.es/problemset/submission/1083/172005955)



---

