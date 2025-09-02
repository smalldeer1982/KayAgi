# [USACO12MAR] Large Banner G

## 题目描述

Bessie is returning from a long trip abroad to the Isle of Guernsey, and Farmer John wants to mount a nice "Welcome Home" banner for her arrival. Farmer John's field has integer dimensions M x N (1 <= M, N <= 100,000), and he has installed a post at every possible point in the field with integer coordinates (if we assign a coordinate system to the field so that (0,0) is in the lower-left corner and (M,N) is in the upper-right corner). Of these (M+1) \* (N+1) points, Farmer John must pick two as the endpoints of the banner.

 
Farmer John, being the perfectionist that he is, insists that the banner must be completely straight.  This means that, for the two posts he chooses, there cannot be any other post on the line segment that the banner will form between them.  Additionally, Farmer John wants the banner to have length at least L and at most H (1 <= L <= H <= 150,000).  Farmer John needs your help to figure out how many possible ways he can hang the banner. The banner is reversible, so switching the two endpoints of the banner counts as the same way to hang the banner. As this number may be very large, Farmer John simply wants to know what it is modulo B (1 <= B <= 1,000,000,000).

Consider the example below, with M = 2 and N = 2: 

\* \* \*
\* \* \*
\* \* \*
Farmer John wants the length of the banner to be between 1 and 3 inclusive. Any choice of posts satisfies this length requirement, but note that eight pairs cannot be picked:

(0, 0) and (2, 0): (1, 0) is on the line segment between them

(0, 1) and (2, 1): (1, 1) is on the line segment between them

(0, 2) and (2, 2): (1, 2) is on the line segment between them

(0, 0) and (2, 2): (1, 1) is on the line segment between them

(0, 0) and (0, 2): (0, 1) is on the line segment between them

(1, 0) and (1, 2): (1, 1) is on the line segment between them

(2, 0) and (2, 2): (2, 1) is on the line segment between them

(0, 2) and (2, 0): (1, 1) is on the line segment between them

Therefore, there are a total of (9 choose 2) - 8 = 28 possible locations.

给出n,m,l,h，问有多少点A(ax,ay),B(bx,by)满足：ax,bx∈[0,n], ay,by∈[0,m]，l<=AB<=h，且线段AB上除A,B外无整点。


## 样例 #1

### 输入

```
2 2 1 3 100 
```

### 输出

```
28 
```

# 题解

## 作者：Isonan (赞：4)

原题传送门[>Here<](https://www.luogu.org/problemnew/show/P3050)

考虑当线段的一个端点为(0,0),另一个端点为(i,j)时，则gcd(i,j)=1且$l^2\le i^2+j^2 \le h^2$(长度为1时特殊处理）

再考虑每条这样的线段可以平移到$(n-i+1)(m-j+1)$个位置，并且还可以反转成$(0,j),(i,0)$，同样可以平移到$(n-i+1)(m-j+1)$个位置

所以答案就是

$$2\sum_{i=1}^{n}\sum_{j=1}^{m}[gcd(i,j)=1][l^2\le i^2+j^2 \le h^2](n-i+1)(m-j+1)$$

j的范围可以改成$lim1\le j\le lim2$,其中$lim1=\sqrt{l^2-i^2},lim2=\sqrt{h^2-i^2}$

再次考虑发现式子里有$[gcd(i,j)=1]$,可以用莫比乌斯函数

所以式子就变成

$$2\sum_{i=1}^{n}\sum_{j=lim1}^{lim2}\sum_{d|n}\mu(d)(n-i+1)(m-j+1)$$

$$=2\sum_{d=1}^{n}\mu(d)\sum_{i=1}^{|\frac nd|}\sum_{j=|\frac {n}{lim1}|}^{|\frac {n}{lim2}|}(n-id+1)(m-jd+1)$$

$$=2\sum_{d=1}^{n}\mu(d)\sum_{i=1}^{|\frac nd|}(n-id+1)[(m+1)(lim2-lim1+1)-\frac {(lim1+lim2)(lim2-lim1+1)}{2}]$$

这个式子可以$O(n\sqrt{n})$算出来，然后就愉快的AC了

至于长度等于1时，很明显有$n(m+1)+m(n+1)$种可能，特判一下就好了。

代码：
```cpp
#include <cstdio>
#include <cmath>

long long max(long long a,long long b){return a>b?a:b;}
long long min(long long a,long long b){return a<b?a:b;}
long long prime[100001],mu[100001],top;
long long ans,n,m,l,h,B,lim1,lim2;
bool pri[100001];

int main(){
    scanf("%lld%lld%lld%lld%lld",&n,&m,&l,&h,&B);
    if(n>m)n^=m^=n^=m;
    mu[1]=1;
    for(int i=2;i<=n;i++){
        if(!pri[i]){
            prime[++top]=i;
            mu[i]=-1;
        }
        for(int j=1;j<=top&&i*prime[j]<=n;j++){
            pri[i*prime[j]]=1;
            if(i%prime[j]==0){
                mu[i*prime[j]]=0;
                break;
            }
            mu[i*prime[j]]=-mu[i];
        }
    }
    if(l<=1&&h>=1)ans=((n*(m+1))%B+(m*(n+1))%B)%B;
    for(long long i=1;i<=n;i++)
        for(long long j=1;j<=n/i;j++){
            if(l<=i*j)lim1=1;
            else lim1=ceil(sqrt(l*l-(j*i)*(j*i)));
            if(lim1>m)continue;
            if(i*j>=h)continue;
            lim2=min(m,floor(sqrt(h*h-(j*i)*(j*i))));
            lim1=((lim1-1)/i)+1;
            lim2/=i;
            ans+=(mu[i]*(n-j*i+1)*((m+1)*(lim2-lim1+1)-((lim1+lim2)*(lim2-lim1+1)*i)/2))*2;
            ans%=B;
        }
    while(ans<0)ans+=B;
    printf("%lld",ans);
}
```

---

## 作者：南阳刘子骥 (赞：2)


机房大佬 [$\text{Y}{\color{Red}\text{ouwike}}$](https://www.luogu.com.cn/user/261773) 有一个 $O(n \log n)$ 的解法，但是祂不屑于写题解，就让我来帮他写了。

----

首先我们考虑怎样才能让一个线段除了端点之外不经过整点。
这里我们不考虑位置，只考虑其形状。那就可以让线段的一个点在 $(0,0)$，另一个点在 $(i,j)$。
可以发现，当 $i$ 与 $j$ 互质，即 $\gcd(i,j) = 1$ 的时候，该线段才不会经过整点。
那么这样的线段的个数如下：

$$
\sum_{i=1}^n \sum_{j=1}^m [\gcd(i,j)=1]
$$

注意到我们线段的端点不一定需要在原点上，并且线段的方向也有两种，那么完整的式子如下：

$$
2 \sum_{i=1}^n \sum_{j=1}^m [\gcd(i,j)=1] (n-i+1)(m-j+1)
$$

考虑莫比乌斯反演：

$$
2 \sum_{i=1}^n \sum_{j=1}^m \sum_{p|i,p|j} \mu(p) (n-i+1)(m-j+1)
$$

现在我们可以开始考虑线段长度的限制了。
这个限制我们直接加在 $j$ 上，让式子变成这个样子：

$$
2 \sum_{i=1}^n \sum_{j=\lceil \sqrt{l^2-i^2} \rceil}^{\lfloor \sqrt{h^2-i^2} \rfloor} \sum_{p|i,p|j} \mu(p) (n-i+1)(m-j+1)
$$

将带有 $p$ 的求和号拿到带有 $j$ 的求和号的前面，并将枚举 $j$ 改为枚举 $\frac{j}{p}$：

$$
2 \sum_{i=1}^n \sum_{p|i} \mu(p) \sum_{j=\lceil \frac{\sqrt{l^2-i^2}}{p} \rceil}^{\lfloor \frac{\sqrt{h^2-i^2}}{p} \rfloor} (n-i+1)(m-jp+1)
$$

将最后的多项式拆开：

$$
2 \sum_{i=1}^n \sum_{p|i} \mu(p) \sum_{j=\lceil \frac{\sqrt{l^2-i^2}}{p} \rceil}^{\lfloor \frac{\sqrt{h^2-i^2}}{p} \rfloor} (n-i+1)(m+1)-(n-i+1)jp
$$

将其拆成两个式子。
第一个式子如下：

$$
2 \sum_{i=1}^n \sum_{p|i} \mu(p) \sum_{j=\lceil \frac{\sqrt{l^2-i^2}}{p} \rceil}^{\lfloor \frac{\sqrt{h^2-i^2}}{p} \rfloor} (n-i+1)(m+1)
$$

发现带有 $j$ 的求和号的后面那一部分与 $j$ 无关，将其提出来：

$$
\begin{aligned}
& 2 \sum_{i=1}^n \sum_{p|i} \mu(p) (n-i+1)(m+1) \sum_{j=\lceil \frac{\sqrt{l^2-i^2}}{p} \rceil}^{\lfloor \frac{\sqrt{h^2-i^2}}{p} \rfloor} 1  \\\\
=& 2 \sum_{i=1}^n \sum_{p|i} \mu(p) (n-i+1)(m+1)(\lfloor \frac{\sqrt{h^2-i^2}}{p} \rfloor - \lceil \frac{\sqrt{l^2-i^2}}{p} \rceil+1)
\end{aligned}
$$

第二个式子如下：

$$
\begin{aligned}
& 2 \sum_{i=1}^n \sum_{p|i} \mu(p) \sum_{j=\lceil \frac{\sqrt{l^2-i^2}}{p} \rceil}^{\lfloor \frac{\sqrt{h^2-i^2}}{p} \rfloor} (n-i+1)jp \\\\
=& 2 \sum_{i=1}^n \sum_{p|i} \mu(p) p (n-i+1) \sum_{j=\lceil \frac{\sqrt{l^2-i^2}}{p} \rceil}^{\lfloor \frac{\sqrt{h^2-i^2}}{p} \rfloor} j
\end{aligned}
$$

而最后一个求和号可以用等差数列求和公式来做。

同时注意一个边界条件：当线段长度为 $1$ 的时候，相邻两个点之间连的边也是可以的，需要特判来进行修正。

----

我们在预处理莫比乌斯函数的时候就是 $O(n \log n)$ 的时间复杂度，而枚举的时候只枚举了一个 $i$ 和 $i$ 的所有约数，枚举约数的时间复杂度是单个 $O(\log n)$ 的，总体来说也是 $O(n \log n)$。

代码如下：

``` cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1e6 + 10;
int mu[N], prime[N], vis[N];
vector<int> d[N];
int n, m, mod;
int l, h;
void moebius(int n)
{
	mu[1] = 1;
	for(int i = 2; i <= n; ++i)
	{
		if(!vis[i]) prime[++prime[0]] = i, mu[i] = mod - 1;
		for(int j = 1; j <= prime[0] && i * prime[j] <= n; ++j)
		{
			vis[i * prime[j]] = 1;
			if(i % prime[j] == 0)
			{
				mu[i * prime[j]] = 0;
				break;
			}
			mu[i * prime[j]] = mod - mu[i];
		}
	}
}
int sum(int n)
{
	return ((1ll * (1 + n) * n) >> 1) % mod;
}
int solve()
{
	int ans = 0;
	for(int i = 1; i <= n; ++i)
	{
		int lim = min(m, (int)sqrt(1ll * h * h - 1ll * i * i));
		int lim2 = max(1, (int)ceil(sqrt(1ll * l * l - 1ll * i * i)));
		for(auto p : d[i])
		{
			if(lim / p >= (lim2 - 1) / p + 1)
				ans = (ans + 1ll * (n - i + 1) * (m + 1) % mod * mu[p] % mod * ((lim / p) - ((lim2 - 1) / p + 1) + 1) % mod) % mod;
		}
	}
	for(int i = 1; i <= n; ++i)
	{
		int lim = min(m, (int)sqrt(1ll * h * h - 1ll * i * i));
		int lim2 = max(1, (int)ceil(sqrt(1ll * l * l - 1ll * i * i)));
		for(auto p : d[i])
		{
			if(lim / p >= (lim2 - 1) / p + 1)
				ans = (ans + mod - 1ll * (n - i + 1) * p % mod * mu[p] % mod * (sum(lim / p) + mod - sum(((lim2 - 1) / p + 1) - 1)) % mod) % mod;
		}
	}
	return (ans + ans) % mod;
}

int main()
{
	scanf("%d%d", &n, &m);
	scanf("%d%d", &l, &h);
	scanf("%d", &mod);
	moebius(n);
	for(int i = 1; i <= n; ++i)
		for(int j = i; j <= n; j += i)
			d[j].push_back(i);

	int ans = solve();
	if(l == 1)
		ans = (ans + (1ll * n * (m + 1) % mod + 1ll * (n + 1) * m % mod) % mod) % mod;

	printf("%d\n", ans);
	return 0;
}
```




---

## 作者：xixike (赞：1)

## Description

[Luogu传送门](https://www.luogu.com.cn/problem/P3050)

## Solution

容易发现一条线段是可以平移旋转的，所以只统计从 $(0, 0)$ 开始的线段就行了。

枚举从 $(0, 0)$ 开始的线段终点是 $(i, j)$。

众所周知，中间不经过其他整点的条件相当于是 $\gcd(i, j) = 1$。

再来看能平移到那些位置，不难发现有 $(n - i + 1) \times (m - j + 1)$ 个位置，平且可以旋转，所以再乘个 2。

对于横平竖直的边单独处理一下就行。

暴力的话 $O(nm\log n)$ 可以拿到 $\text{65pts}$。

下面来优化，目前答案是：

$$
\begin{aligned}
Ans =& \sum_{i = 1}^n\sum_{j = 1}^m2(n - i + 1)(m - j + 1)[\gcd(i, j) == 1] \\
=& \sum_{i = 1}^n\sum_{j = 1}^m\sum_{d | (i, j)}\mu(d)2(n - i + 1)(m - j + 1) \\
=& \sum_{d = 1}^n\mu(d)\sum_{i = 1}^{\lfloor\frac nd\rfloor}2(n - i + 1)\sum_{j = \lceil\frac{\sqrt{l^2 - (id)^2}}{k}\rceil}^{\lfloor\frac{\sqrt{h^2 - (id)^2}}{k}\rfloor}(m - j + 1) \\
\end{aligned}
$$

令 $L = \lceil\frac{\sqrt{l^2 - (id)^2}}{k}\rceil, R = \lfloor\frac{\sqrt{h^2 - (id)^2}}{k}\rfloor$，得：

$$
\begin{aligned}
Ans =& \sum_{d = 1}^n\mu(d)\sum_{i = 1}^{\lfloor\frac nd\rfloor}2(n - i + 1)\sum_{j = L}^{R}(m - j + 1) \\
=& \sum_{d = 1}^n\mu(d)\sum_{i = 1}^{\lfloor\frac nd\rfloor}2(n - i + 1)\frac{[(m - L + 1) + (m - R + 1)](R - L + 1)}{2} \\
=& \sum_{d = 1}^n\mu(d)\sum_{i = 1}^{\lfloor\frac nd\rfloor}(n - i + 1)[(m - L + 1) + (m - R + 1)](R - L + 1)
\end{aligned}
$$

复杂度 $O(n \ln n)$。

## Code

```cpp
#include <bits/stdc++.h>
#define pb push_back
#define int long long

using namespace std;

namespace IO{
    inline int read(){
        int x = 0, f = 1;
        char ch = getchar();
        while(!isdigit(ch)) {if(ch == '-') f = -1; ch = getchar();}
        while(isdigit(ch)) x = (x << 3) + (x << 1) + ch - '0', ch = getchar();
        return x * f;
    }

    template <typename T> inline void write(T x){
        if(x < 0) putchar('-'), x = -x;
        if(x > 9) write(x / 10);
        putchar(x % 10 + '0');
    }
}
using namespace IO;

const int N = 1e5 + 10;
int n, m, l, h, mod, ans;
int mu[N], p[N], vis[N], tot;

inline void euler(int n){
    mu[1] = 1;
    for(int i = 2; i <= n; ++i){
        if(!vis[i]) p[++tot] = i, mu[i] = -1;
        for(int j = 1; j <= tot && i * p[j] <= n; ++j){
            vis[i * p[j]] = 1;
            if(i % p[j]) mu[i * p[j]] = -mu[i];
            else break;
        }
    }
}

inline int add(int x) {return x >= mod ? x - mod : x;}
inline int sub(int x) {return x < 0 ? x + mod : x;}
inline int mul(int x, int y) {return 1ll * x * y % mod;}
inline int cal(int x) {return (x % mod + mod) % mod;}
inline int sqr(int x) {return x * x;}

signed main(){
#ifndef ONLINE_JUDGE
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
#endif 
    n = read(), m = read(), l = read(), h = read(), mod = read();
    if(n > m) swap(n, m);
    euler(n);
    if(l <= 1) ans = add(mul(n, m + 1) + mul(m, n + 1));
    for(int d = 1; d <= n; ++d){
        int res = 0;
        for(int i = 1; i <= n / d; ++i){
            if(sqr(h) <= sqr(i * d)) continue;
            int L = ceil(1.0 * sqrt(sqr(l) - sqr(i * d)) / d), R = min(m, (int)floor(sqrt(sqr(h) - sqr(i * d)))) / d;
            if(sqr(l) <= sqr(i * d)) L = 1;
            if(L > R || L > m) continue;
            res = add(res + mul(n - i * d + 1, mul(add(m - L * d + 1 + m - R * d + 1), R - L + 1)));
        }
        ans = add(ans + cal(mu[d] * res));
    }
    write(ans), puts("");
    return 0;
}
```

---

## 作者：Priestess_SLG (赞：0)

好久没写题解了（

很显然，一条连接 $(x_1,y_1)$ 和 $(x_2,y_2)$ 点的线段在平面直角坐标系上可以先把 $(x_1,y_1)$ 点平移到 $(0,0)$，那么就是考虑一条 $(0,0)$ 到 $(x,y)$ 的线段上是否没有其他的整点。

此时令 $d=\gcd(x,y)$，则：

+ 若 $d=1$ 则显然线段上没有其他整点。
+ 若 $d>1$，则把 $x,y$ 同时除以 $d$ 得到 $(x',y')$ 在线段上。

单独处理所有横向和竖向的路径后，要求的东西就是：

$$
\sum\limits_{i=1}^n\sum\limits_{j=1}^m2(n-i+1)(m-j+1)[\gcd(i,j)=1]
$$

看上去很炫酷，因此考虑喵一个反演。套路的，原式为：

$$
\begin{aligned}
&\sum\limits_{i=1}^n\sum\limits_{j=1}^m2(n-i+1)(m-j+1)[\gcd(i,j)=1][边长符合限制条件]\\
=&\sum\limits_{i=1}^n\sum\limits_{j=1}^m\sum\limits_{d=1}^{\min(n,m)}2(n-i+1)(m-j+1)\mu(d)[边长符合限制条件]\\
=&\sum\limits_{d=1}^{\min(n,m)}\mu(d)\sum\limits_{i=1}^{\lfloor\frac nd\rfloor}\sum\limits_{j=1}^{\lfloor \frac md\rfloor}2(n-id+1)(m-jd+1)[边长符合限制条件]\\
=&\sum\limits_{d=1}^{\min(n,m)}\mu(d)\sum\limits_{i=1}^{\lfloor\frac nd\rfloor}\sum\limits_{j=\lceil\frac{\sqrt{l^2-i^2d^2}}{d}\rceil}^{\lfloor\frac{\sqrt{h^2-i^2d^2}}{d}\rfloor}2(n-id+1)(m-jd+1)\\
=&2\sum\limits_{d=1}^{\min(n,m)}\mu(d)\sum\limits_{i=1}^{\lfloor\frac nd\rfloor}(n-id+1)\sum\limits_{j=\lceil\frac{\sqrt{l^2-i^2d^2}}{d}\rceil}^{\lfloor\frac{\sqrt{h^2-i^2d^2}}{d}\rfloor}(m-jd+1)\\
\end{aligned}
$$

式子枚举 $j$ 的后半部分可以直接等差数列求和，前半部分预处理筛出 $\mu$ 积性函数后是调和级数，因此总时间复杂度为 $O(n\log n)$ 可以通过。处理有细节。

```cpp
// #pragma GCC optimize(3,"Ofast","inline")
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1000010;
int pr[N],isp[N],idx,mu[N];
void sieve(){
    mu[1]=1,isp[1]=1;
    for(int i=2;i<N;++i){
        if(!isp[i])pr[++idx]=i,mu[i]=-1;
        for(int j=1;j<=idx&&i*pr[j]<N;++j){
            mu[i*pr[j]]=mu[i]*mu[pr[j]],isp[i*pr[j]]=1;
            if(i%pr[j]==0){mu[i*pr[j]]=0;break;}
        }
    }
}
int calc(int l,int r,int b){
    return (l+r)*(r-l+1)/2%b;
}
int m,n,l,h,b;
signed main(){
    cin.tie(0)->sync_with_stdio(false);
    cout<<fixed<<setprecision(15);
    sieve();
    cin>>m>>n>>l>>h>>b;
    int s=0;
    if(n>m)swap(n,m);
    for(int d=1;d<=min(n,m);++d){
        int now=0;
        for(int i=1;i<=n/d;++i){
            if(h*h<=i*i*d*d)continue;
            int ll=ceil(1.*sqrt(l*l-i*i*d*d)/d),rr=floor(1.*sqrt(h*h-i*i*d*d)/d);
            int L=ll,R=rr,tmp=(m-L*d+1+m-R*d+1)*(R-L+1)%b;
            if(L<1||l*l<=i*i*d*d)L=1;if(R>m/d)R=m/d;if(L>R)continue;
            tmp=(m-L*d+1+m-R*d+1)*(R-L+1)%b;
            now=(now+tmp*(n-i*d+1)%b)%b;
        }
        s=(s+now*mu[d]%b+b)%b;
    }
    if(l<=1)s=(s+n*(m+1)+m*(n+1))%b;
    cout<<s<<'\n';
}
```

---

## 作者：__ycx2010__ (赞：0)

[传送门](https://www.luogu.com.cn/problem/P3050)

假设 $n<m$。

设 $f(x)$ 表示有多少个整点 $A,B$ 满足 $|AB|^2 <= x$ 且线段 $AB$ 之间无整点。

则答案等于 $f(h^2) - f(l^2-1)$。

那么如何计算 $f(x)$ 呢？设一条线段水平距离为 $i$，竖直距离为 $j$，那么在矩形中形如这样的线段会出现 $(n-i+1)(m-j+1)$ 次。

当线段 $(i,j)$ 可以时，$(i,-j)$ 也可以，所以上述线段的贡献为 $2$。

当线段与 $x$ 轴或 $y$ 轴垂直时，对答案贡献为 $n(m+1)+m(n+1)$。

列出 $f(x)$ 的式子

$$f(x) =(n + 1)m + m(n+1) + 2\sum_{i=1}^n \sum_{j=1}^m (n-i+1)(m-j+1) [i^2+j^2 \leq x \wedge gcd(i,j) = 1]$$

莫比乌斯反演得到

$$f(x) =(n + 1)m + m(n+1) + 2\sum_{i=1}^n \sum_{j=1}^m (n-i+1)(m-j+1) [i^2+j^2 \leq x] \sum_{d|i,d|j} \mu(d)$$

$$f(x) =(n + 1)m + m(n+1) + 2\sum_{d=1}^n \mu(d)\sum_{i=1}^{\lfloor \frac{n}{d} \rfloor} \sum_{j=1}^{\lfloor\frac{\min\{m,\lfloor\sqrt{x-i^2d^2}\rfloor\}}{d}\rfloor} (n-id+1)(m-jd+1)$$

于是枚举 $d,i$，直接计算即可，时间复杂度 $O(n\ln n)$。

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 100010;
int n, m, l, h, b;
int mu[N], vis[N], prime[N], tot;

void init() {
	mu[1] = 1;
	for (int i = 2; i < N; i ++ ) {
		if (!vis[i]) {
			prime[++ tot] = i;
			mu[i] = -1;
		}
		for (int j = 1; prime[j] * i < N; j ++ ) {
			vis[i * prime[j]] = true;
			if (i % prime[j] == 0) break;
			mu[i * prime[j]] = -mu[i];
		}
	}
}

int solve(ll x) {
	if (x <= 0) return 0;
	int ans = 0;
	for (int d = 1; d <= n; d ++ ) {
		for (int i = 1; i * d <= n; i ++ ) {
			if (1ll * i * d * i * d >= x) break;
			int lim = min(m, (int)floor(sqrt(x - 1ll * i * i * d * d))) / d, res = 0;
			res = (res + 1ll * (n - i * d + 1) * (m + 1) % b * lim % b) % b;
			res = (res + b - 1ll * (n - i * d + 1) * d % b * ((1ll * (1 + lim) * lim / 2) % b) % b) % b;
			ans = ((ll)ans + b + mu[d] * res) % b;
		}
	}
	return (1ll * n * m * 2 % b + n + m + ans * 2 % b) % b;
}

int main() {
	init();
	scanf("%d%d%d%d%d", &n, &m, &l, &h, &b);	
	if (n > m) swap(n, m);
	printf("%d\n", (solve(1ll * h * h) + b - solve(1ll * l * l - 1)) % b);
    return 0;
}
```

---

