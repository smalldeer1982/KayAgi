# 树林里的树 Trees in a Wood.

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=14&page=show_problem&problem=1155

[PDF](https://uva.onlinejudge.org/external/102/p10214.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10214/50c1f69fedc915b5433ce438aa7604af34fd8f42.png)

## 样例 #1

### 输入

```
3 2
0 0```

### 输出

```
0.7058824```

# 题解

## 作者：fa_555 (赞：4)

under 题解 [UVA10214](https://www.luogu.org/problem/UVA10214)

---

真心推荐刚学莫反的同学来做一下这道题目，这才是真正的 Mobius 反演入门题啊！

[P2158 仪仗队](https://www.luogu.org/problem/P2158)是这题的特殊情况，前者可以用欧拉 $\varphi$ 函数解决，而这题用 Mobius 反演简单得多。

没学过莫反的可以来我的[这篇题解](https://www.luogu.org/blog/fa555/solution-p4450)的 前置知识 部分学习一下。

我们回到这题。

---

分析题意，我们只需将四个象限之一的答案求出，就可推广到整个坐标系。

简化版题意：给定一个 N * M 的矩阵，求

$$ \sum \limits_{i = 1}^N \sum \limits_{j = 1}^M [\gcd(i, j) = 1] $$

尝试对这个式子进行套路性的莫反变形，得到

$$ \sum \limits_{i = 1}^N \sum \limits_{j = 1}^M \sum \limits_{d | \gcd(i, j)} \mu(d) $$

可以将 $d | \gcd(i, j)$ 拆开

$$ \sum \limits_{i = 1}^N \sum \limits_{j = 1}^M \sum \limits_{d | i, d | j} \mu(d) $$

改变枚举顺序，得到

$$ \sum \limits_{d = 1}^{\min(N, M)} \mu(d) \lfloor \tfrac{N}{d} \rfloor \lfloor \tfrac{M}{d} \rfloor $$

就可以单次 $O(n)$ 枚举答案了！

但是我们并不知道数据组数 ~~垃圾UVA~~，所以优化是必要的。和式含有两个形如 $\lfloor \tfrac{N}{d} \rfloor$ 的因子，意味着可以通过数论分块优化到单次 $O( \sqrt{N})$ 的复杂度，可以通过本题。

TIPS:

1. 求出的 `ans` 是单个象限中的答案，加上坐标轴四个方向的贡献均为 `1`，因此答案的分子是 `ans * 4 + 4`。

2. 原点是没有树的，因此分母是 `(N * 2 + 1) * (M * 2 + 1) - 1`。

3. 极端数据的分母会爆 `int`，不要忘记 `long long` 和强制类型转换。

code(c++):

*请手动优化常数*

```
#include<algorithm>
#include<bitset>
#include<iomanip>
#include<iostream>

using namespace std;
typedef long long ll;

bitset<2003> v; // 此处作用等价于 bool v[2003];
int N, M, p[305], mu[2003];
ll ans, tot;

inline void sieve(int N) {
	int m = 0;
	mu[1] = 1;
	for(int i = 2; i <= N; ++i) {
		if(!v[i]) p[++m] = i, mu[i] = -1;
		for(int j = 1, x; j <= m && i * p[j] <= N; ++j) {
			x = i * p[j];
			v.set(x); // v[x] = 1;
			if(i % p[j] == 0) break; // 此时 mu[x] = 0;
			mu[x] = -mu[i];
		}
		mu[i] += mu[i - 1]; // 顺便求出前缀和
	}
}

int main() {
	cout << fixed << setprecision(7);
		// 规定输出小数位数
	sieve(2000); // min(maxa, maxb) = 2000
	while(cin >> N >> M) {
		if(!N) return 0;
		ans = 0; // 多测不清空，爆零两行泪
		if(N > M) swap(N, M);
		for(int i = 1, j, n, m; i <= N; i = j + 1) {
			n = N / i, m = M / i; // 可有可无的小常数优化
			j = min(N / n, M / m);
			ans += (ll)(mu[j] - mu[i - 1]) * n * m;
		}
		ans = ans * 4 + 4;
		tot = (ll)(N * 2 + 1) * (M * 2 + 1) - 1;
		cout << (double)ans / tot << '\n';
	}
}


```
如果有错误或不懂的地方，请在私信或评论中告知我。**谢谢大家！**


---

## 作者：Arghariza (赞：2)

- 一句话题意：

$$ans=\frac{(\sum\limits_{i=1}^{n}\sum\limits_{j=1}^{m}[\gcd(i,j)=1])\times 4+4}{(2n+1)(2m+1)-1}$$

考虑计算 $t=\sum\limits_{i=1}^{n}\sum\limits_{j=1}^{m}[\gcd(i,j)=1]$，然后我们发现可以**莫比乌斯反演**。

根据莫比乌斯反演的式子 $[n=1]=\sum\limits_{d\mid n}\mu(d)$ ，套进去。

$$\begin{aligned}t&=\sum\limits_{i=1}^{n}\sum\limits_{j=1}^{m}[\gcd(i,j)=1]\\&=\sum\limits_{i=1}^{n}\sum\limits_{j=1}^{m}\sum\limits_{d\mid \gcd(i,j)}\mu(d)\\&=\sum\limits_{i=1}^{n}\sum\limits_{j=1}^{m}\sum\limits_{d\mid i,d\mid j}\mu(d)\\&=\sum\limits_{d=1}^{n}\mu(d)\sum\limits_{d\mid i}^{n}\sum\limits_{d\mid j}^{m}1\\&=\sum\limits_{d=1}^{n}\mu(d)(\sum\limits_{d\mid i}^{n}1)(\sum\limits_{d\mid j}^{m}1)\\&=\sum\limits_{d=1}^{n}(n/d)(m/d)\mu(d)\end{aligned}$$

于是就可以快乐地 $O(\sqrt{n})$ 整除分块了，最后套进最上面那个式子即可。

```cpp
#include <bits/stdc++.h>
#define int long long
namespace mystd {
    inline int read() {
        int w = 1, q = 0;
        char ch = ' ';
        while (ch != '-' && (ch < '0' || ch > '9')) ch = getchar();
        if (ch == '-') w = -1, ch = getchar();
        while (ch >= '0' && ch <= '9') q = q * 10 + ch - '0', ch = getchar();
        return w * q;
    }
    inline void write(int x) {
        if (x < 0) {
            x = ~(x - 1);
            putchar('-');
        }
        if (x > 9) write(x / 10);
        putchar(x % 10 + '0');
    }
}
using namespace std;
using namespace mystd;

const int maxn = 2020;
int n, m, ans, tot;
int p[maxn], mu[maxn], vis[maxn];

void init() {
	mu[1] = 1;
	for (int i = 2; i <= maxn - 1; i++) {
		if (!vis[i]) mu[i] = -1, p[++tot] = i;
		for (int j = 1; j <= tot && i <= (maxn - 1) / p[j]; j++) {
			vis[i * p[j]] = 1;
			if (i % p[j] == 0) {
				mu[i * p[j]] = 0;
				break;
			}
			mu[i * p[j]] = -mu[i];
		}
	}
	for (int i = 2; i <= maxn; i++) mu[i] += mu[i - 1];
}

int calc(int n, int m) {
	int l = 1, r, res = 0;
	while (l <= min(n, m)) {
		r = min(n / (n / l), m / (m / l));
		res += 1ll * (mu[r] - mu[l - 1]) * (n / l) * (m / l);
		l = r + 1;
	}
	return res;
}

signed main() {
	init();
    while (~scanf("%lld%lld", &n, &m) && !(!n && !m)) {
        printf("%.7lf\n", 1.0 * (calc(n, m) * 4.0 + 4.0) / (1.0 * (n * 2 + 1) * (m * 2 + 1) - 1.0));
    }
	return 0;
}
```

---

## 作者：wmy_goes_to_thu (赞：2)

咦？没有用欧拉函数做的吗？那么我就发表一篇吧。

还记得[这道题](https://www.luogu.com.cn/problem/P2158)吗？是一个欧拉函数的裸题，那么我们可以按着那道题的思路来做吧！但是有一个问题，那道题是正方形，这道题是矩形！

我最开始有一个思路，就是把一个 $n \times m,n \leq m$ 的矩形拆成 $\lfloor \frac{m}{n} \rfloor $ 个边长为 $n$ 的正方形和另外一个矩形，继续递归处理。但是这样会有反例，比如 $n=7,m=9$ 的时候，自己可以动手试一试。

其实，小矩形的面积没有多大，暴力即可，不用递归处理。然后就可以 AC 了。

代码：
```cpp
#include<iostream>
#include<algorithm>
#include<cstdlib>
#include<cstdio>
#include<cstring>
using namespace std;
int gcd(int a,int b){return b==0?a:gcd(b,a%b);}
int tp[2][2]={{8,12},{12,16}};
int s[2005],d[2005],tot=0,oul[2005];
void print()
{
	s[1]=1;
	for(int i=2;i<=2000;i++)
	{
		if(!s[i])d[++tot]=i;
		for(int j=1;j<=tot&&i*d[j]<=2000;j++)
		{
			s[i*d[j]]=1;
			if(i%d[j]==0)break;
		}
	}
}
void print2()
{
	oul[1]=1;
	for(int i=2;i<=2000;i++)
	{
		int pp=i;
		for(int j=1;j<=tot;j++)if(i%d[j]==0)pp=pp/d[j]*(d[j]-1);
		oul[i]=pp;
	}
}
long long solve(int n,int m)
{
	long long ans=0;
	for(int i=1;i<=n;i++)
	{
		int qq=m/i;
		ans+=qq*oul[i];
		for(int j=qq*i+1;j<=m;j++)if(gcd(i,j)==1)ans++;
	}
	return ans;
}
int main()
{
	print();
	print2();
	int n,m;
	while(cin>>n>>m&&(n||m))
	{
		double ans;
		if(n<=2&&m<=2)ans=1.0*tp[n-1][m-1]/((n*2+1)*(m*2+1)-1);
		else ans=1.0*(solve(n,m)*4+4)/(1ll*(n*2+1)*(m*2+1)-1);
		printf("%.7f\n",ans);
	}
	return 0;
}
```


---

## 作者：封禁用户 (赞：2)

```cpp
这题有两种方法：
第一种：来自刘汝佳的算法竞赛入门经典第二版的339页，介绍了用欧拉函数的解法，然而我并不会qwq，所以只有第二种方法。

第二种：
莫比乌斯反演：

其实这题很像[https://www.luogu.org/problemnew/show/P2158](P2158 仪仗队)，只是四个象限而已，不过有很多坑点。

这题数据灰常大（这里不是指会超时（如果不是的暴力的呼话）），2000 * 2000000 会爆int，所以得开long long。然后记得转换成浮点数相除。

其实题意很简单，就是求：
 n   m
 ∑   ∑ [gcd(i,j)=k]的个数
i=1 j=1

其中n = a,m = b,k = 1,然后把答案乘上4再加4；

而求上式便是莫比乌斯反演（~~懵逼钨丝反演~~）的一大应用

设f(k)为gcd(i,j) = k的个数，g(k)为满足k | gcd(i,j)的对数，
         floor(n/k)
则g(k) =     ∑     f(kx)
           x = 1
       = floor(n/k)floor(m/k)
由反演有：
	   floor(n/k)
f(k) =    ∑ mu(x)g(kx)
		x = 1
        
        floor(n/k)
     =    ∑ mu(x)floor(n/k)floor(m/k)
     	x = 1
其中mu(x)为莫比乌斯函数，可用线性筛求出

代码如下：（注意：下面的代码中使用了分块的思想（公共乘积优化），预处理了前缀和（我不打算在题解里讲了，有兴趣的去看我的LuoGu博客））

#include<cstdio>
#include<algorithm>

const int L = 40000 + 6;

typedef long long Long;//简化代码

int primes[L],mu[L],num,sum[L];
bool isPrime[L];

//线性筛莫比乌斯函数，就是线筛加了点东西
void sieve(int len){
	std::fill(isPrime,isPrime + len + 1,true);
	
	mu[1] = 1;//由定义mu(1)=1
	num = 0;
	
	for(int i = 2;i < len;++i){
		if(isPrime[i]){
			primes[num++] = i;
			mu[i] = -1;
		}
		static int d;
		for(int j = 0;j < num && (d = i * primes[j]) < len;++j){
			isPrime[d] = false;
			if(i % primes[j] == 0){
				mu[d] = 0;
				break;
			}else{
				mu[d] = -mu[i];
			}
		}
	}
	
    //处理前缀和，用于分块
	sum[0] = 0;
    for(int i = 1;i <= L;i++){
        sum[i] = sum[i - 1] + mu[i];
    }
}

//求解f(x),n,m是上界，d = k
Long f(int n, int m, int d) {
    if(n > m){
    	std::swap(n, m);
	}
    Long ans = 0;
    n /= d, m /= d;
    for(int i = 1, last = 1; i <= n; i = last + 1){
        last = std::min(n / (n / i), m / (m / i));
        ans += (Long)(sum[last] - sum[i - 1]) * (n / i) * (m / i);
    }
	 
    return ans * 4 + 4;//上述代码求出的是一个象限，总数需要*4 + 4个坐标轴上的4个点
}

int main(){
	sieve(L);//记得调用，我每次都忘qwq
	
	int a,b;
	while(scanf("%d %d",&a,&b) == 2 && a){
		Long K = f(a,b,1);
		Long N = (Long)(a * 2 + 1) * (b * 2 + 1) - 1;//这里一定记得赋值号右边也要强制类型转换
		
		printf("%.7lf\n",(double)K / (double)N);
	}
	
	return 0;
}
```

---

## 作者：TernaryTree (赞：1)

## 题目大意

求

$$\dfrac{4+4\sum_{i=1}^{n}\sum_{j=1}^{m}[\gcd(i,j)=1]}{(2n+1)(2m+1)-1}$$

## 思路分析

莫比乌斯反演 $+$ 整除分块板子题。

我们先看 $\sum_{i=1}^{n}\sum_{j=1}^{m}[\gcd(i,j)=1]$ 部分。

$$
\begin{aligned}
&\quad\  \sum_{i=1}^{n}\sum_{j=1}^{m}[\gcd(i,j)=1] \\ 
&= \sum_{i=1}^{n}\sum_{j=1}^{m}\sum_{d|\gcd(i,j)}\mu(d)\\
&= \sum_{i=1}^{n}\sum_{j=1}^{m}\sum_{d|i,d|j}\mu(d) \\
&= \sum_{d=1}^{\min(n,m)}\mu(d)\lfloor\frac nd\rfloor\lfloor\frac md\rfloor\\
\end{aligned}
$$

发现有形如 $\lfloor\dfrac xd\rfloor$ 的式子。可以整除分块。

简单介绍一下整除分块：

例如对于 $x=10$ 时，有表格如下：

| $d=$ | $1$ | $2$ | $3$ | $4$ | $5$ | $6$ | $7$ | $8$ | $9$ | $10$ |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| $\lfloor\dfrac xd\rfloor=$ | $10$ | $5$ | $3$ | $2$ | $2$ | $1$ | $1$ | $1$ | $1$ | $1$ |


发现 $1\sim 1,\ 2\sim 2, \ 3\sim 3, \ 4\sim 5,\ 6\sim 10$ 都是相同的数值。

并且注意到每一块的最右一块必然是 $\lfloor\dfrac{x}{\lfloor \dfrac {x}{d}\rfloor}\rfloor$。

所以这样就可以在小于 $O(n)$ 的时间复杂度里完成求和了。

## 主要坑点

多组数据，还有要开 `long long`。

注意多组数据的时候开始 `ans` 要清零。

然后就没了。

## 完整代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define double long double

using namespace std;

const int maxn = 1e5;
const double epslon = 1e-6;

bool vis[maxn + 1];
int mb[maxn + 1], prime[maxn + 1], cnt = 0;
int presum[maxn + 1];

int n, m;
double ans;

void generate_mb() {
	mb[1] = 1;
	for (int i = 2; i <= maxn; i++) {
		if (!vis[i]) {
			prime[++cnt] = i;
			mb[i] = -1;
		}
		for (int j = 1; j <= cnt && i * prime[j] <= maxn; j++) {
			vis[i * prime[j]] = 1;
			if (i % prime[j]) {
				mb[i * prime[j]] = -mb[i];
				continue;
			}
			break;
		}
	}
}

void generate_presum() {
	for (int i = 1; i <= maxn; i++) {
		presum[i] = presum[i - 1] + mb[i];
	}
}

void generate_ans() {
	ans = 0;
	int l = 1, r = 0;
	while (l <= n) {
		r = min(n / (n / l), m / (m / l));
		ans += (presum[r] - presum[l - 1]) * (n / l) * (m / l);
		l = r + 1;
	}
	ans = (ans * 4 + 4) / ((n * 2 + 1) * (m * 2 + 1) - 1);
}

signed main() {
	// freopen("r.out", "w", stdout);
	generate_mb();
	generate_presum();
	while (cin >> n >> m && (n || m)) {
		if (n > m) swap(n, m);
		generate_ans();
		cout << fixed << setprecision(7) << ans << endl;
	}
}


```

---

## 作者：Chouquet (赞：1)

感觉题解讲得太简略了（其实是我太弱了），而且用不到莫比乌斯反演的，讲一下我的思路吧。

本题输入只有 $a,b$ 两个数，还有多组数据。要想能过显然时间复杂度与 $b$ 无关，不然一定 $TLE$ 。根据题意，如果几棵树在一条直线上时，只能看到离原点最近的，而此时横坐标和纵坐标一定互质。如果只考虑第一象限且 **不算坐标轴** 的情况，这就是欧拉函数模板题。

但这题跟[P2158](https://www.luogu.com.cn/problem/P2158)的区别就在于，这道题 $a$ 与 $b$ 是不相等的。又因为 $a$ 的范围较小，所以只能枚举 $x$ 坐标，根据每一个 $x$ 计算这一竖线上能看到的树的个数。根据 $x$ 枚举 $y$ 是不可能的，只能~~分块~~分段计算了。假设 $y>x:$

$1 \sim x:$ 显然为 $\phi(x)$ 。

$x+1 \sim 2x:$ 因为 $gcd(kx+y,x)=gcd(y,x)$ （$k$ 为整数），所以仍然是 $\phi(x)$ 。

$2x+1 \sim 3x:$ 同上，仍为 $\phi(x)$ 。

$...$

$kx+1 \sim b:$ 该区间长度小于 $a$ 且没有固定的公式，只要暴力判断就行了。

用 $ans$ 累加，因为有四个象限而且还要算坐标轴（坐标轴向四个方向只能看到四棵），所以能看到 $4*ans+4$ 棵树，最后除以树的总数就行了(**注意不能算上原点**)。

时间复杂度：最差 $O(n^2logn)$ ，但做不到这么多。

代码：

```cpp
#include <cstdio>
long long a, b, phi[2003] = {0, 1}, ans;
void init() {//预处理phi的值
    for (int i = 2; i <= 2000; i++)
        if (!phi[i])
            for (int j = i; j <= 2000; j += i) {
                if (!phi[j])
                    phi[j] = j;
                phi[j] = phi[j] / i * (i - 1);
            }
}
long long gcd(long long x, long long y) {
    return !y ? x : gcd(y, x % y);
}
int main() {
    init();
    while (scanf("%lld%lld", &a, &b) != EOF) {
        if (!a && !b)
            break;
        ans = 0;
        for (long long x = 1; x <= a; x++) {
            ans += b / x * phi[x];//计算1~kx的phi个数
            for (long long i = b / x * x + 1; i <= b; i++)//暴力判断
                if (gcd(x, i) == 1)
                    ++ans;
        }
        printf("%.7lf\n", 1.0 * ((ans << 2ll) + 4) / (((a << 1ll) + 1) * ((b << 1ll) + 1) - 1));
        //树总共有(2a+1)*(2b+1)-1棵，写成位运算会快一丢丢
    }
    return 0;
}
```

注：结果可能会爆int，所以最好全开long long

---

## 作者：封禁用户 (赞：0)

### 思路
很明显，树林里的树能被分成答案完全相等的四块，只需计算一块即可。

显然，每块树林对答案的贡献为：
$$
\sum_{i=1}^{a}\sum_{j=1}^{b}[\gcd(i,j)=1]
$$

### 推导
$$
\begin{aligned}
&\sum_{i=1}^{a}\sum_{j=1}^{b}[\gcd(i,j)=1]&\\
=&\sum_{i=1}^{a}\sum_{j=1}^{b}\sum_{d\mid i,d \mid j}\mu(d)&\\
=&\sum_{d=1}^{\min(a,b)}\mu(d)\lfloor \frac{a}{d} \rfloor \lfloor \frac{b}{d} \rfloor 

\end{aligned}
$$

线性筛莫比乌斯函数，并求前缀和。\
再套上数论分块即可。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e6+7;
int mu[N],prime[N],top;
bitset<N> vis;

void init(){
	mu[1]=1;
	for(int i=2;i<N;++i){
		if(!vis[i]){
			prime[++top]=i;
			mu[i]=-1;
		}
		for(int j=1;j<=top&&i*prime[j]<N;++j){
			vis[i*prime[j]]=true;
			if(!(i%prime[j])){
				mu[i*prime[j]]=0;
				break;
			}
			mu[i*prime[j]]=-mu[i];
		}
	}
	for(int i=2;i<N;++i)
		mu[i]+=mu[i-1];
}

long long compute(int a,int b){
	long long res=0;
	for(int l=1,r;l<=a;l=r+1){
		r=min(a/(a/l),b/(b/l));
		res+=(mu[r]-mu[l-1])*1ll*(a/l)*1ll*(b/l);
	}
	return res;
}

int main(){
	int a,b;
	init();
	while(cin>>a>>b){
		if(!a)
			return 0;
		if(a>b)
			swap(a,b);
		printf("%.7lf\n",(double(1ll*compute(a,b)*4+4))/double(1ll*4*1ll*a*1ll*b+2*1ll*a+2*1ll*b));
	}
}
```

---

## 作者：luuia (赞：0)

### 题目大意

给定一个坐标系，满足 $x \in [-n,n]$，$y \in [-m,m]$，求从原点能直接看到的点（不被其它点遮挡）的数量。

### Solution

我们考虑一个点 $(x,y)$ 能被直接看到的条件。

如果 $\gcd(x,y) \neq 1$，那么设 $\gcd(x,y) = d$，那么 $(\frac{x}{d},\frac{y}{d})$ 与 $(x,y)$ 显然应该是共线的。因此，我们得到一个点能被直接看到的条件是 $\gcd(x,y) = 1$。

根据对称性，我们只需要统计一个象限内的点的数量，再乘以 $4$ 就得到了四个象限的情况。在坐标轴上的点显然有且只有 $4$ 个点能被看到，最后答案加 $4$ 即可。

因此，我们得到这个式子：

$$\operatorname{ans} = 4 \times \sum_{i = 1}^n\sum_{j = 1}^m[\gcd(i,j) = 1] + 4$$

这个式子直接算是 $O(nm\log n)$ 的，所以我们需要优化。莫比乌斯反演能够很好的解决这种问题。

不知道莫比乌斯反演的可以看 [我的专栏](https://www.luogu.com.cn/article/lycvbvlm) 。

这道题里莫比乌斯反演的核心式子是 $\mu * 1 = \varepsilon$，即：

$$\sum_{d \mid n}\mu(d) = [n = 1]$$

于是我们开始推式子。

$$
\begin{aligned}

\operatorname{ans'}

&= \sum_{i = 1}^n\sum_{j = 1}^m \,\,[\gcd(i,j) = 1] \\

&= \sum_{i = 1}^n\sum_{j = 1}^m\sum_{d \mid \gcd(i,j)}\mu(d) \\ 

&= \sum_{i = 1}^n\sum_{j = 1}^m\sum_{d=1}^{\min(n,m)}\mu(d)[d \mid i][d \mid j] \\ 

&= \sum_{d=1}^{\min(n,m)}\mu(d)\sum_{i = 1}^n\sum_{j = 1}^m[d \mid i][d \mid j] \\

&= \sum_{d=1}^{\min(n,m)}\mu(d)\lfloor\frac{n}{d}\rfloor\lfloor\frac{m}{d}\rfloor \\

\end{aligned}
$$

现在这个式子的计算是 $O(n)$ 的，只需要线性筛出 $\mu$ 然后直接计算即可。

复杂度更优的解法是对 $\lfloor\frac{n}{d}\rfloor\lfloor\frac{m}{d}\rfloor$ 进行整除分块，然后对 $\mu$ 杜教筛即可做到 $O(n^{\frac{2}{3}})$。

最后还需要除以所有点的数量即 $(2n + 1)(2m + 1)$。

### Code

[AC 记录](https://www.luogu.com.cn/record/152010670)

```cpp
#include<bits/stdc++.h>
using namespace std;

int read()
{
    int s = 0,w = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9')
    {
        if(ch == '-') w = -1;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9')
    {
        s = (s << 1) + (s << 3) + (ch ^ 48);
        ch = getchar();
    }
    return s * w;
}

const int N = 1e4 + 10;
long long T,n,m,tot,ans,mu[N],p[N];
bool flg[N];

void euler() 
{
	mu[1] = 1;
	for(int i = 2;i <= N;i++) 
	{
		if(!flg[i]) p[++tot] = i, mu[i] = -1;
		for(int j = 1;j <= tot && i * p[j] <= N;j++) 
		{
			flg[i * p[j]] = 1;
			if(i % p[j] == 0) 
			{
				mu[i * p[j]] = 0;
				break;
			}
			mu[i * p[j]] = -mu[i];
		}
	}
}

int main()
{
    //freopen("input.in","r",stdin);
    euler();
    while(1)
    {
        n = read(),m = read(),ans = 0;
        if(n == 0 && m == 0) break;
        if(n > m) swap(n,m);
        for(int i = 1;i <= n;i++) ans += mu[i] * (n / i) * (m / i);
        ans = ans * 4 + 4;
        cout << fixed << setprecision(7) << ans * 1.0 / ((2 * n + 1) * (2 * m + 1) - 1) << endl;
    }
    return 0;
}
```

---

