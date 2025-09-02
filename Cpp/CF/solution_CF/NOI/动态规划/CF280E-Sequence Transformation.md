# Sequence Transformation

## 题目描述

You've got a non-decreasing sequence $ x_{1},x_{2},...,x_{n} $ $ (1<=x_{1}<=x_{2}<=...<=x_{n}<=q) $ . You've also got two integers $ a $ and $ b $ $ (a<=b; a·(n-1)<q) $ .

Your task is to transform sequence $ x_{1},x_{2},...,x_{n} $ into some sequence $ y_{1},y_{2},...,y_{n} $ $ (1<=y_{i}<=q; a<=y_{i+1}-y_{i}<=b) $ . The transformation price is the following sum: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF280E/179b07629f5c2880a487dce85a0ebc41e16d4717.png). Your task is to choose such sequence $ y $ that minimizes the described transformation price.

## 样例 #1

### 输入

```
3 6 2 2
1 4 6
```

### 输出

```
1.666667 3.666667 5.666667 
0.666667
```

## 样例 #2

### 输入

```
10 100000 8714 9344
3378 14705 17588 22672 32405 34309 37446 51327 81228 94982
```

### 输出

```
1.000000 8715.000000 17429.000000 26143.000000 34857.000000 43571.000000 52285.000000 61629.000000 70973.000000 80317.000000 
797708674.000000
```

# 题解

## 作者：Reanap (赞：5)

模拟赛遇到了，写了 $O(n^2)$ 的做法。下来后发现原题可以过，所以写写题解。

考虑使用调整法。初始时，我们把相邻两个 $y$ 之间的差设为 $a$，然后进行调整达到最小化答案的目的。

考虑我们把相邻两个位置的差增大一个极小量 $\delta$ 会对答案带来怎样的影响。我们设每个位置 $i$ 的代价 $(x_i - y_i)^2$，则增加一个位置 $p$ 的与上一个位置的差分值 $\delta $ 对答案的影响为：$\Delta = \sum\limits_{i=p+1}^n (x_i-y_i-\delta)^2 - (x_i-y_i)^2 = \sum\limits_{i=p+1}^n 2(x_i-y_i)$。其实就是求导。

于是我们的策略就是每一步选择一个影响量为负且最小的可修改位置（如果有多个显然选择最右边的更优），将其增加一个 $\delta$。实际操作实际上就是将这个位置增加到不是最小值或者超过限制为止，加的数值显然可以 $O(n)$ 算。注意到，每个位置只会被进行这样的一次操作，所以总复杂度 $O(n^2)$。

不知道为什么，这个做法好像比较吃精度。 

我总感觉这个做法可以用数据结构维护，但实在没想出来，有会的同学可以留言教教我。

```cpp
#include <bits/stdc++.h>
#define pii pair <int , int>
#define pll pair <LL , LL>
#define mp make_pair
#define fs first
#define sc second
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;

// const int Mxdt=100000;
// static char buf[Mxdt],*p1=buf,*p2=buf;
// #define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,Mxdt,stdin),p1==p2)?EOF:*p1++;

template <typename T>
void read(T &x) {
	T f=1;x=0;char s=getchar();
	while(s<'0'||s>'9') {if(s=='-') f=-1;s=getchar();}
	while(s>='0'&&s<='9') {x=(x<<3)+(x<<1)+(s^'0');s=getchar();}
	x *= f;
}

template <typename T>
void write(T x , char s='\n') {
	if(!x) {putchar('0');putchar(s);return;}
	if(x<0) {putchar('-');x=-x;}
	T t = 0 , tmp[25] = {};
	while(x) tmp[t ++] = x % 10 , x /= 10;
	while(t -- > 0) putchar(tmp[t] + '0');
	putchar(s);
}

const int MAXN = 2e5 + 5;
const long double eps = 1e-5;

int n , m , a , b;
int x[MAXN];
long double d[MAXN] , y[MAXN] , s[MAXN];

int main() {
//    freopen("anxious.in" , "r" , stdin);
//    freopen("anxious.out" , "w" , stdout);
    read(n),read(m),read(a),read(b);
    for (int i = 1; i <= n; ++i) read(x[i]);

    d[1] = 1;
    for (int i = 2; i <= n; ++i) d[i] = a;
    
    long double res = m - (a * (n - 1) + 1);

    while(res) {
        y[1] = d[1];
        for (int i = 2; i <= n; ++i) y[i] = y[i - 1] + d[i];
        for (int i = n; i >= 1; --i) s[i] = s[i + 1] + y[i] - x[i];
        int p = 1;
        for (int i = 2; i <= n; ++i) if(s[i] <= s[p] + eps && d[i] + eps < b) p = i;
        if(s[p] >= 0) break;
        long double dl = 0;
        if(p == 1) dl = -s[p] / n;
        else dl = min(b - d[p] , -s[p] / (n - p + 1));
        dl = min(dl , res);
        for (int i = p + 1; i <= n; ++i) if(d[i] + eps < b) dl = min((s[i] - s[p]) / (i - p) , dl);
        d[p] += dl;res -= dl;
    }

    y[1] = d[1];
    for (int i = 2; i <= n; ++i) y[i] = y[i - 1] + d[i];
    long double ans = 0;
    for (int i = 1; i <= n; ++i) printf("%.6Lf " , y[i]) , ans += (y[i] - x[i]) * (y[i] - x[i]);
    puts("");

    printf("%.6Lf\n" , ans);

    return 0;
}
```

---

## 作者：Larunatrecy (赞：3)

一道较为复杂的 `slope trick`。

首先我们考虑一个最暴力的 `dp`，设 $dp_{i,j}$ 表示前 $i$ 个位置，$y_i=j$ 的最小代价，转移是显然的：

$$dp_{i,j}=\min_{j-k\in[a,b]}dp_{i-1,k}+(X_i-j)^2$$ 


我们把 $dp_{i,j}$ 看成关于 $j$ 的函数 $dp_i(j)$，不难用归纳证明 $dp_i(j)$ 在是一个凸函数，也就是说函数存在一个最小值点。

设 $dp_{i-1}(j)$ 的极值点为 $u$，把转移分成三种：

- $j-a< u$，$dp_i(j)=dp_{i-1}(j-a)+(X_i-j)^2$

- $u<j-b$，$dp_i(j)=dp_{i-1}(j-b)+(X_i-j)^2$

- $j-b\leq u\leq j-a$，$dp_i(j)=dp_{i-1}(u)+(X_i-j)^2$

我们还是不好做，考虑求个导，可以得到：

- $j-a< u$，$dp_i'(j)=dp_{i-1}'(j-a)+2j-2X_i$

- $u<j-b$，$dp_i'(j)=dp_{i-1}'(j-b)+2j-2X_i$

- $j-b\leq u\leq j-a$，$dp_i'(j)=2j-2X_i$

这等价于把 $u$ 左边的函数向右平移 $a$ 单位，$u$ 右边的函数向右平移 $b$ 单位，然后把中间部分变成 $0$，再整体加上 $2j-2X_i$ 的代价。

因为 $2j-2X_i$ 是单调的，而平移不会改变凸函数的性质，因此我们可以发现求完导之后的 $dp_i'(j)$ 也是一个凸函数。

同时，可以发现，我们最多只会新增两个段，因此可以做到 $O(n^2)$ 求出答案，如果我们同时记录下每一步转移的极值点，也可以倒着给出构造，可以通过此题。

但是能不能做的更好呢？

观察上述转移，和常规的 `slope trick` 不同的是，我们需要动态找到一个极值点，也就找到一个跨过 $0$ 点的段，而因为是凸函数，所以斜率单调，我们用平衡树维护所有斜率相同的段，每次找到跨过 $0$ 点的段，这是容易的。

然后，我们把左边的段打一个平移 $a$ 的标记，右边的段打一个 $b$ 标记，加入中间的 $0$ 段，最后整体加一个一次函数就好了。

也就是说，我们维护平移量，和一个一次函数的 $tag$ 即可。

可以使用 `fhq-treap` 实现。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 6060;
int n,X[N],V,a,b;
typedef double db;
const db eps = 1e-8;
db dp[N],Y[N];
inline bool cmp(db x,db y){return x-y<eps;}
struct node 
{
	db K,B,l,r,addK,addB;
	int ls,rs,mov;
	int key;
	#define key(x) tr[x].key
	#define K(x) tr[x].K
	#define B(x) tr[x].B
	#define l(x) tr[x].l
	#define r(x) tr[x].r
	#define addK(x) tr[x].addK
	#define addB(x) tr[x].addB
	#define ls(x) tr[x].ls
	#define rs(x) tr[x].rs
	#define mov(x) tr[x].mov 
}tr[100200];
void pushtag(int x,db K,db B,db mov)
{
	if(!x)return;
	addB(x)+=-mov*addK(x)+B;
	B(x)+=-mov*K(x)+B;
	addK(x)+=K;K(x)+=K;
	mov(x)+=mov;l(x)+=mov;r(x)+=mov;
}
void pushdown(int x)
{
	if(!x)return;
	pushtag(ls(x),addK(x),addB(x),mov(x));
	pushtag(rs(x),addK(x),addB(x),mov(x));
	addK(x)=0;addB(x)=0;mov(x)=0;
}
void splitl(int k,int &x,int &y)
{
	if(!k)
	{
		x=y=0;
		return;
	}
	pushdown(k);
	db v=K(k)*l(k)+B(k);
	if(cmp(0,v))
	{
		y=k;
		splitl(ls(k),x,ls(k));
	}
	else 
	{
		x=k;
		splitl(rs(k),rs(k),y);
	}
}
void splitr(int k,int &x,int &y)
{
	if(!k)
	{
		x=y=0;
		return;
	}
	pushdown(k);
	db v=K(k)*r(k)+B(k);
	if(cmp(0,v))
	{
		y=k;
		splitr(ls(k),x,ls(k));
	}
	else 
	{
		x=k;
		splitr(rs(k),rs(k),y);
	}
}
int merge(int x,int y)
{
	if(!x||!y)return x+y;
	pushdown(x);pushdown(y);
	if(key(x)<key(y))
	{
		rs(x)=merge(rs(x),y);
		return x; 
	}
	ls(y)=merge(x,ls(y));
	return y;
}
int find(int x)
{
	while(ls(x))x=ls(x);
	return x;
}
int tot=0,root=0;
int main()
{
	cin>>n>>V>>a>>b;
	for(int i=1;i<=n;i++)scanf("%d",&X[i]);
	root=++tot;key(tot)=rand();
	l(0)=V;
	l(1)=1;r(1)=V;
	K(1)=2;B(1)=-2*X[1];
	for(int i=2;i<=n;i++)
	{
		int L,x,R;
		splitr(root,L,R);
		splitl(R,x,R);
		if(!x)
		{
			db u=l(find(R));
			dp[i-1]=u;
			x=++tot;key(tot)=rand();
			K(x)=B(x)=0;
			l(x)=u+a;r(x)=u+b;
			pushtag(L,0,0,a);
			pushtag(R,0,0,b);
			root=merge(merge(L,x),R);
		}
		else 
		{
			db u=-B(x)/K(x);
			dp[i-1]=u;
			if(cmp(l(x),u))
			{
				int p=++tot;key(tot)=rand();
				K(p)=K(x);
				B(p)=B(x)-a*K(x);
				l(p)=l(x)+a;
				r(p)=u+a;
				ls(x)=p;
			}
			if(cmp(u,r(x)))
			{
				int p=++tot;key(tot)=rand();
				K(p)=K(x);
				B(p)=B(x)-b*K(x);
				l(p)=u+b;
				r(p)=r(x)+b;
				rs(x)=p;
			}
			K(x)=B(x)=0;
			l(x)=u+a;
			r(x)=u+b;
			pushtag(L,0,0,a);
			pushtag(R,0,0,b);
			root=merge(merge(L,x),R);
		}
		pushtag(root,2,-2*X[i],0);
	}
	int L,R,x;
	splitr(root,L,R);
	splitl(R,x,R);
	db u;
	if(!x)u=l(find(R));
	else u=-B(x)/K(x);
	if(cmp(V,u)) u=V;
	db ans=0;
	for(int i=n;i>=1;i--)
	{
		Y[i]=u;
		ans+=(Y[i]-X[i])*(Y[i]-X[i]);
		if(cmp(u,dp[i-1]+a))u=u-a;
		else if(cmp(dp[i-1]+b,u))u=u-b;
		else u=dp[i-1];
	}
	for(int i=1;i<=n;i++)printf("%.8lf ",Y[i]);
	printf("\n%.8lf\n",ans);
	return 0;
}
```

---

## 作者：rizynvu (赞：1)

[cnblogs](https://www.cnblogs.com/fiosiate/p/18982803)。

只会复读[其他题解](https://codeforces.com/blog/entry/6952)了/ll。

首先有一个 dp 是记 $f_{i, j}$ 表示 $y_i = j$ 时的最小代价，转移形如 $f_{i, j} = \min\limits_{j - b\le k\le j - a} \{f_{i - 1, k}\} + (j - x_i)^2$。

不过此时遇到的问题是 $j$ 的上界不仅很大而且可能为小数，是十分不好维护的。

此时一个很妙的想法是考虑把 $f_i$ 当作是一个关于 $j$ 的函数，即看作 $f_i(j)$。  
这个函数可能会有一些分段的情况，但是首先对这个取 $\min$ 的操作感受一下，段数其实并不多。

于是考虑分段维护 $f_i'(j)$，这样的好处将会在后文体现。

首先来考虑初值：$f_1(j) = (j - x_1)^2$，那么有 $f_1'(j) = 2(j - x_1)$。

然后来考虑第一次转移：$f_{2, j} = \min\limits_{j - b\le k\le j - a} \{f_{1, k}\} + (j - x_2)^2$。  

先来考虑简化这个 $\min\limits_{j - b\le k\le j - a} \{f_{1, k}\}$， $f_1(j)$ 是具有性质的，这是单调递增的，所以考虑找到使 $f_1(j)$ 取到最小值的 $k = x_1$，那么 $\min\limits_{j - b\le k\le j - a} \{f_{1, k}\} = \begin{cases}f_1(k) &k + a\le j\le k + b\\ f_1(j - a) & j < k + a\\ f_1(j - b) & j > k + b\end{cases}$。  
令 $g(j) = \min\limits_{j - b\le k\le j - a}$ ，那么会发现 $g'(j) = \begin{cases} 0 & k + a < j < k + b\\ f_1'(j - a) & j < k + a\\ f_1'(j - b) & j > k + b\end{cases}$，即 $g'(j)$ 也是单调不降的。

那么 $f_2(j) = g(j) + (j- x_2)^2$，所以 $f_2'(j) = g'(j) + 2(j - x_2)$，会发现这依然是不降的。

于是可以发现，这之后的每一步转移也是类似的，都可以说明 $f_i'(j)$ 其实是单调不降的。  

那么每次转移都可以考虑求出使得取到 $f_i(j)$ 的最小值的值 $k$，这是容易通过 $f'_i(j)$ 来发现的。  
于是只需要把 $f_i'(j)$ 从 $k$ 处劈开，左边平移 $a$ 位，右边平移 $b$ 位，并把 $(k + a, k + b)$ 都填充上 $0$，最后再加上 $2(j - x_{i + 1})$ 这个函数，就实现了 $f_i'(j)\to f_{i + 1}'(j)$ 的转移。

需要注意的是 $f_i'(j)$ 并不一定是连续的，通常 $k$ 会满足 $f_i'(k) = 0$，但是在定义域限制下可能并不能找到合适的 $k$，但此时 $k$ 一定会在端点 / 分界点处（满足左侧 $f_i'(k) < 0$，右侧 $f'_i(k) > 0$，不过端点处可能还需要一些特判）。

于是每一步转移都可以 $\mathcal{O}(n)$ 完成，总的复杂度就为 $\mathcal{O}(n^2)$。

对于实现，可以考虑维护分界点的点值 $(p_{i, j}, f_{i, j})$，这样更容易处理平移的问题，因为 $f'_{i}(j)$ 是一次函数，所以分界点之间的 $f_i'(j)$ 是容易表示出来的。

由于这种做法的空间并不是十分友好，点值需要滚掉，可以考虑记下每一个点值是 $3$ 种情况的哪一种得到的，在构造时倒推，具体可以见实现。

还有就是，建议用 `long double`。

```c++
#include <bits/stdc++.h>

#define double long double

constexpr double eps = 1e-9;

constexpr int maxn = 6000 + 10;

int n, m, x[maxn], a, b;

double p[maxn * 2], f[maxn * 2];

double pu[maxn];
char lst[maxn][maxn * 2];

double y[maxn];

int main() {
    scanf("%d%d%d%d", &n, &m, &a, &b);
    for (int i = 1; i <= n; i++) scanf("%d", &x[i]);

    p[1] = 1.0, f[1] = 2.0 * (p[1] - x[1]);
    p[2] = m, f[2] = 2.0 * (p[2] - x[1]);

    for (int i = 2; i <= n; i++) {
        for (int j = 0; j <= (i - 1) * 2; j++) {
            if ((j == 0 || f[j] < eps) && (j == (i - 1) * 2 || -eps < f[j + 1])) {
                if (p[j + 1] - p[j] > eps && 1 <= j && j < (i - 1) * 2) {
                    pu[i - 1] = p[j] + (-f[j]) * (p[j + 1] - p[j]) / (f[j + 1] - f[j]);
                } else if (j >= 1) {
                    pu[i - 1] = p[j];
                } else {
                    pu[i - 1] = p[1];
                }
                for (int k = (i - 1) * 2; k >= j + 1; k--) {
                    p[k + 2] = p[k] + b, f[k + 2] = f[k], lst[i][k + 2] = 2;
                }
                p[j + 1] = pu[i - 1] + a, f[j + 1] = 0, lst[i][j + 1] = 1;
                p[j + 2] = pu[i - 1] + b, f[j + 2] = 0, lst[i][j + 2] = 1;
                for (int k = 1; k <= j; k++) {
                    p[k] += a, lst[i][k] = 0;
                }
                break;
            }
        }

        for (int j = 1; j <= i * 2; j++) {
            f[j] += 2.0 * (p[j] - x[i]);
        }
    }

    const int low = 1 + a * (n - 1), upp = m;
    double val = -1;
    for (int i = 0; i <= n * 2; i++) {
        if ((i == 0 || f[i] < eps) && (i == n * 2 || -eps < f[i + 1])) {
            double u;
            if (p[i + 1] - p[i] > eps && 1 <= i && i < 2 * n) {
                u = p[i] + (-f[i]) * (p[i + 1] - p[i]) / (f[i + 1] - f[i]);
            } else if (i >= 1) {
                u = p[i];
            } else {
                u = p[1];
            }
            if (low - eps < u && u < upp + eps) {
                val = u;
            } else if (u < low + eps) {
                val = low;
            } else {
                val = upp;
            }
        }
    }

    y[n] = val;
    for (int i = n; i > 1; ) {
        for (int j = 1; j < i * 2; j++) {
            if (p[j] - eps < val && val < p[j + 1] + eps) {
                if (lst[i][j] == 1 && lst[i][j + 1] == 1) {
                    val = pu[i - 1];
                } else if (lst[i][j] == 0) {
                    val -= a;
                } else {
                    val -= b;
                }
            }
        }
        for (int j = 1; j <= i * 2; j++) {
            if (lst[i][j] == 0) {
                p[j] -= a;
            }
            if (lst[i][j] == 2) {
                p[j - 2] = p[j] - b;
            }
        }
        y[--i] = val;
    }

    double ans = 0;
    for (int i = 1; i <= n; i++) {
        printf("%.10Lf ", y[i]);
        ans += (y[i] - x[i]) * (y[i] - x[i]);
    }
    printf("\n%.10Lf\n", ans);
    return 0;
}
```

---

## 作者：Felix72 (赞：0)

受到 slope trick 的启发，这题一看就要分段维护函数。但是这题不是一次函数，怎么办呢？

经过分析后发现，函数的下凸性在本题中仍成立，那么我们可以分段记录二次函数的几个参数，并暴力平移。

对于每一步，我们找到最小值对应的位置（函数下凸，这个值只有一个）。算出 $y_n$ 后再到着往回推，取与这个位置最近的可行位置即可。

```cpp
#include <bits/stdc++.h>
#include <ext/pb_ds/priority_queue.hpp>
using namespace std;

const int N = 6010;
typedef pair < double, double > PII;
int n; long long q, a, b, x[N];
double ans[N], ps[N];

inline double inrange(double x, double l, double r)
{return ((x < l) ? l : ((x > r) ? r : x));}
struct func
{
	double a, b, c, l, r;
	func operator + (const func &w) const {return {a + w.a, b + w.b, c + w.c, l, r};}
	inline PII getmx()
	{
		double x = inrange(-b / (2 * a), l, r);
		return {x, a * x * x + b * x + c};
	}
	inline void add(double d)
	{
		double na, nb, nc;
		na = a; nb = b - 2 * a * d;
		nc = a * d * d - b * d + c;
		a = na, b = nb, c = nc;
	}
}; func f[N * 2]; int cnt;

int main()
{
//	freopen("text.in", "r", stdin);
//	freopen("prog.out", "w", stdout);
//	ios::sync_with_stdio(false);
//	cin.tie(0), cout.tie(0);
	cin >> n >> q >> a >> b;
	q -= a * (n - 1);
	for(int i = 1; i <= n; ++i) cin >> x[i], x[i] -= a * (i - 1);
	for(int i = 1; i <= n; ++i)
	{
//		cerr << "-----------------------------------------\n";
		long long na = 1, nb = -2 * x[i], nc = x[i] * x[i];
		if(i == 1)
		{
			++cnt; f[cnt].l = 1, f[cnt].r = q;
			f[cnt].a = na; f[cnt].b = nb, f[cnt].c = nc;
			ps[i] = f[cnt].getmx().first;
		}
		else
		{
			int id = 1;
			for(int j = 1; j <= cnt; ++j)
				if(f[j].getmx().second < f[id].getmx().second)
					id = j;
			PII cur = f[id].getmx();
			for(int j = cnt + 2; j >= id + 3; --j)
			{
				f[j] = f[j - 2];
				f[j].l += b - a;
				f[j].r += b - a;
				f[j].r = min(f[j].r, (double)q);
			}
			cnt += 2;
			f[id + 1].a = f[id + 1].b = 0; f[id + 1].c = cur.second;
			f[id + 1].l = cur.first, f[id + 1].r = cur.first + b - a;
			f[id + 1].r = min(f[id + 1].r, (double)q);
			
			f[id + 2].a = f[id].a, f[id + 2].b = f[id].b;
			f[id + 2].c = f[id].c; f[id + 2].l = cur.first + b - a;
			f[id + 2].r = f[id].r + b - a; f[id + 2].r = min(f[id + 2].r, (double)q);
			
			f[id].r = cur.first;
			
			while(cnt && f[cnt].l > q) --cnt;
			
			for(int j = id + 2; j <= cnt; ++j)
				f[j].add(b - a);
			
			for(int j = 1; j <= cnt; ++j)
				f[j] = f[j] + (func){na, nb, nc, 0, 0};
			
			id = 1;
			for(int j = 1; j <= cnt; ++j)
				if(f[j].getmx().second < f[id].getmx().second)
					id = j;
			ps[i] = f[id].getmx().first;
		}
//		cerr << ps[i] << '\n';
//		for(int j = 1; j <= cnt; ++j)
//			cerr << f[j].a << " " << f[j].b << " " << f[j].c << " " << f[j].l << " " << f[j].r << '\n';
	}
	int id = 1;
	for(int i = 1; i <= cnt; ++i)
		if(f[i].getmx().second < f[id].getmx().second)
			id = i;
	PII cur = f[id].getmx();
	ans[n] = cur.first;
	for(int i = n - 1; i >= 1; --i)
		ans[i] = inrange(ps[i], ans[i + 1] - (b - a), ans[i + 1]);
	double sig = 0;
	for(int i = 1; i <= n; ++i)
	{
		sig += (ans[i] - x[i]) * (ans[i] - x[i]);
		ans[i] += (i - 1) * a;
	}
	for(int i = 1; i <= n; ++i) printf("%.6lf ", ans[i]);
	printf("\n"); printf("%.6lf\n", sig);
	return 0;
}
/*
2 5 1 2
1 4
*/
```

---

