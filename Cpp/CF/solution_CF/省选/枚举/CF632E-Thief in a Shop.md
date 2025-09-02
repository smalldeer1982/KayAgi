# Thief in a Shop

## 题目描述

A thief made his way to a shop.

As usual he has his lucky knapsack with him. The knapsack can contain $ k $ objects. There are $ n $ kinds of products in the shop and an infinite number of products of each kind. The cost of one product of kind $ i $ is $ a_{i} $ .

The thief is greedy, so he will take exactly $ k $ products (it's possible for some kinds to take several products of that kind).

Find all the possible total costs of products the thief can nick into his knapsack.

## 样例 #1

### 输入

```
3 2
1 2 3
```

### 输出

```
2 3 4 5 6
```

## 样例 #2

### 输入

```
5 5
1 1 1 1 1
```

### 输出

```
5
```

## 样例 #3

### 输入

```
3 3
3 5 11
```

### 输出

```
9 11 13 15 17 19 21 25 27 33
```

# 题解

## 作者：QuZhan (赞：18)

## dp方程：dp[i]=min(dp[i],dp[i-a[j]]+1)
### 表示选价值为i的最小物品数为dp[i]
### 注意的是按样例一的话
#### 3 2
#### 1 2 3
### 则dp[3]=1 我们能发现价值为3的话可以选2个物品
### 特别骚的办法是将价值排序，然后给所有物品减一个最小价值，最后不够K的话直接加0价值的物品 


```
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;
const int N=1000+5;
const int inf=1e9+5;
int n,k;
int a[N],b[N];
int dp[N*N];
int main()
{
    cin>>n>>k;
    for (int i=1;i<=n;i++)
        cin>>a[i];
    sort(a+1,a+n+1);
    for (int i=1;i<=n;i++)
        b[i]=a[i]-a[1];
    for (int i=0;i<N*N;i++)
        dp[i]=inf;
    dp[0]=0;
    for (int i=1;i<=n;i++)
        for (int j=1;j<N*N;j++)
        {
            if (j-b[i]>=0)
                dp[j]=min(dp[j],dp[j-b[i]]+1);
        }
    for (int i=0;i<N*N;i++)
    {
        if (dp[i]<=k)
            cout<<k*a[1]+i<<' ';
    }
} 
```

---

## 作者：zhoufangyuanPT (赞：14)

## solution-1

题目中已经写明了这是一个背包，所以我们考虑DP

设$f[i]$表示凑够$i$价值需要的最小物品数

DP转移方程：$f[i]=min\{f[i-a[j]]+1|1\leq j\leq n,a[j]\leq i\}$

但是这一题要求是正好取$k$个物品，所以我们要处理一下物品的价值

设价值最小的物品的价值为$x$

我们可以把每一个物品的价值减去$x$

这时所有物品数小于$k$的方案，都可以通过加上若干个0来达到$k$个

因为这时价值最小的物品减去$x$后就价值为0，所以可以加无限多个

同时原方程的每一个可用方案都可以用这种方式表示出来

所以我们只要把每一个$f[i]\leq k$的$i$求出，并加上$x\cdot k$

假设$n$,$k$,$a_i$同级~~（反正都是1000）~~，时间复杂度$O(n^3)$，然而本题时限`5s`，所以还是可以勉强跑过的

`code`

```c++
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int f[1010000],a[1100];
int main()
{
	int n,k;scanf("%d%d",&n,&k);
	int minx=0x3f3f3f3f,v=0;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		minx=min(minx,a[i]);
		v=max(v,a[i]);
	}
	v=v-minx;
	for(int i=1;i<=n;i++)a[i]-=minx;
	memset(f,63,sizeof(f));f[0]=0;
	for(int i=1;i<=k*v;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(a[j]<=i)f[i]=min(f[i],f[i-a[j]]+1);
		}
	}
	for(int i=0;i<=k*v;i++)
	{
		if(f[i]<=k)printf("%d ",i+k*minx);
	}
	printf("\n");
	return 0;
}
```

## solution-2

~~如果你和我一样菜~~，你会想到另一个DP方程

设$f[i][j]$表示用$i$个物品凑够$j$价值的方案数

则有状态转移方程

$f[i][j]=\sum\limits_{k=1}^nf[i-1][j-a[k]]$

可以用滚动数组滚掉一维，时间复杂度$O(n^4)$，TLE

这时我们定义$g_i=[i\in a]$

（这里的 $[P]$ 是指，当 $P$ 为真时，式子的值是 $1$ ；当 $P$ 为假时，式子的值是 $0$ 。// 可以理解成， `P` 是一个 0/1 布尔值， $[P]$ 就是 `(int)P`。）

则原方程可以表示为

$f[i][j]=\sum\limits_{k=0}^{j}f[i-1][j-k]\cdot g_k$

接着你会惊讶的发现这竟然是一个卷积~~QAQ~~

然后 FFT+快速幂 一波走起，快得飞起

时间复杂度$O(n^2logn)$，然而精度爆炸~~（叫你不用NTT）~~

`code`

```c++
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
struct complex
{
	double real,imag;
	complex(double r=0,double i=0):real(r),imag(i){}
};
inline complex operator+(complex x,complex y){return complex(x.real+y.real,x.imag+y.imag);}
inline complex operator-(complex x,complex y){return complex(x.real-y.real,x.imag-y.imag);}
inline complex operator*(complex x,complex y){return complex(x.real*y.real-x.imag*y.imag,x.real*y.imag+x.imag*y.real);}
struct node
{
	complex a[1048576];
	void fft(int);
}f,g;int len;
int r[1048576];
#define M_PI 3.14159265358979323846
void node::fft(int type)
{
	for(int i=0;i<len;i++)if(i<r[i])swap(a[i],a[r[i]]);
	for(int i=2;i<=len;i<<=1)
	{
		complex wi(cos(2*M_PI/i),type*sin(2*M_PI/i));
		for(int j=0;j<len;j+=i)
		{
			complex wk(1);
			for(int k=j;k<j+(i>>1);k++,wk=wk*wi)
			{
				complex a1=a[k],a2=wk*a[k+(i>>1)];
				a[k]=a1+a2;a[k+(i>>1)]=a1-a2;
			}
		}
	}
}
inline node operator*=(node &x,node y)
{
	for(int i=0;i<len;i++)x.a[i]=x.a[i]*y.a[i];
	return x;
}
int main()
{
	int n,m;scanf("%d%d",&n,&m);
	len=1;int rp=-1;
	while(len<=m*1000)len<<=1,rp++;
	r[0]=0;int x;
	for(int i=1;i<len;i++)r[i]=r[i>>1]>>1|(i&1)<<rp;
	for(int i=0;i<len;i++)f.a[i].real=1;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&x);
		g.a[x].real=1;
	}
	g.fft(1);
	while(m)
	{
		if(m&1)f*=g;
		g*=g;
		m>>=1;
	}
	f.fft(-1);
	for(int i=0;i<len;i++)
	{
		if(f.a[i].real>0.5*len)printf("%d ",i);
	}
	putchar('\n');
	return 0;
}
```

# solution-3

考虑如何减少精度误差

首先一开始的几个卷积的长度都很小，所以可以让快速幂时长度在不断变化，来使得一开始的误差很小。

同时我们只要求有一个方案就算是可以取走的价值了

所以在每做一次卷积后，我们就可以把那些方案数大于1的方案数都变为1，其他不可以实现的则为0

这时精度问题就没有了，我们也就不用写NTT了，~~听说NTT还被卡模数了~~

但是这样做每乘一次都要跑一遍`fft`和一遍`ifft`，所以时间巨大

时间复杂度$O(n^2log^2n)$，然而因为我的常数太大了，跑得比solution-1的$O(n^3)$还慢

`code`

```c++
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
inline void read(int &x)
{
	x=0;
	char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
}
inline void write(int x)
{
	int y=10;
	while(y<=x)y=y*10;
	while(y!=1){y=y/10;putchar(x/y+'0');x=x%y;}
}
struct complex
{
	long double real,imag;
	complex(long double r=0,long double i=0):real(r),imag(i){}
};
inline complex operator+(complex x,complex y){return complex(x.real+y.real,x.imag+y.imag);}
inline complex operator-(complex x,complex y){return complex(x.real-y.real,x.imag-y.imag);}
inline complex operator*(complex x,complex y){return complex(x.real*y.real-x.imag*y.imag,x.real*y.imag+x.imag*y.real);}
struct node
{
	complex a[1048576];
	void fft(int);
}f,g;int len;
int r[1048576];
#define M_PI 3.14159265358979323846
void node::fft(int type)
{
	for(int i=0;i<len;i++)if(i<r[i])swap(a[i],a[r[i]]);
	for(int i=2;i<=len;i<<=1)
	{
		complex wi(cos(2*M_PI/i),type*sin(2*M_PI/i));
		for(int j=0;j<len;j+=i)
		{
			complex wk(1);
			for(int k=j;k<j+(i>>1);k++,wk=wk*wi)
			{
				complex a1=a[k],a2=wk*a[k+(i>>1)];
				a[k]=a1+a2;a[k+(i>>1)]=a1-a2;
			}
		}
	}
}
inline node operator*=(node &x,node y)
{
	x.fft(1);y.fft(1);
	for(int i=0;i<len;i++)x.a[i]=x.a[i]*y.a[i];
	x.fft(-1);
	for(int i=0;i<len;i++)x.a[i]=complex(x.a[i].real/len>0.5?1:0);
	return x;
}
int main()
{
	int n,m;read(n);read(m);
	f.a[0].real=1;
	int gg=0,x;
	for(int i=1;i<=n;i++)
	{
		read(x);
		g.a[x].real=1;
		if(x>gg)gg=x;
	}
	len=1;int rp=-1;
	while(len<=gg)len<<=1,rp++;
	while(m)
	{
		len<<=1;rp++;
		r[0]=0;
		for(int i=1;i<len;i++)r[i]=r[i>>1]>>1|(i&1)<<rp;
		if(m&1)f*=g;
		g*=g;
		m>>=1;
	}
	for(int i=0;i<len;i++)
	{
		if(f.a[i].real>0.5)write(i),putchar(' ');
	}
	putchar('\n');
	return 0;
}
```

---

## 作者：Weng_Weijie (赞：8)

题解：

对所有物品构造生成函数$F(x)=\displaystyle\sum_{i\in S}x^i$

取 $k$ 个物品相当于选取其中的 $k$ 项相乘

于是计算 $F^k(x)$ 输出其中不为零的项即可

需要注意的一点是：模数 $998244353$ 和 $1004535809$ 都被hack了

可以选择双模数防止被hack(至少CF没有卡双模的数据)

代码：

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#define N 1048576
using LL = long long;
const int G = 3;
int mod;
int n, k, rev[N], lim, ilim, s, wn[N + 1];
std::vector<int> v;
inline int pow(int x, int y) {
    int ans = 1;
    for (; y; y >>= 1, x = static_cast<LL> (x) * x % mod)
        if (y & 1) ans = static_cast<LL> (ans) * x % mod;
    return ans;
}
inline int& up(int& x, int y) { if ((x += y) >= mod) x -= mod; return x; }
inline void NTT(int* A, int typ) {
    for (int i = 0; i < lim; i++) if (i < rev[i]) std::iter_swap(A + i, A + rev[i]);
    for (int i = 1; i < lim; i += i) {
        const int t = lim / i / 2;
        for (int j = 0; j < lim; j += i + i) {
            for (int k = 0; k < i; k++) {
                int w = typ ? wn[t * k] : wn[lim - t * k];
                int x = A[k + j], y = static_cast<LL> (w) * A[k + j + i] % mod;
                up(A[k + j], y), up(A[k + j + i] = x, mod - y);
            }
        }
    }
    if (!typ) for (int i = 0; i < lim; i++) A[i] = static_cast<LL> (ilim) * A[i] % mod;
}
inline void init(int len, int mod) {
	::mod = mod;
    lim = 1, s = -1; while (lim < len) lim += lim, s++; ilim = pow(lim, mod - 2);
    for (int i = 0; i < lim; i++) rev[i] = rev[i >> 1] >> 1 | (i & 1) << s;
    int w = pow(G, (mod - 1) / len);
    wn[0] = 1;
    for (int i = 1; i <= lim; i++) wn[i] = static_cast<LL> (wn[i - 1]) * w % mod;
}
int A[N], B[N];
int main() {
	std::ios::sync_with_stdio(0);
	std::cin >> n >> k;
	for (int i = 1, x; i <= n; i++) std::cin >> x, A[x] = B[x] = 1;
	init(1048576, 998244353);
	NTT(A, 1);
	for (int i = 0; i < lim; i++) A[i] = pow(A[i], k);
	NTT(A, 0);
	for (int i = 1; i <= 1000000; i++) if (A[i]) v.push_back(i);
	init(1048576, 1004535809);
	NTT(B, 1);
	for (int i = 0; i < lim; i++) B[i] = pow(B[i], k);
	NTT(B, 0);
	for (int i = 1; i <= 1000000; i++) if (B[i]) v.push_back(i);
	std::sort(v.begin(), v.end()); int tot = std::unique(v.begin(), v.end()) - v.begin();
	v.resize(tot);
	for (int i : v) std::cout << i << " ";
	return 0;
}
```

---

## 作者：pldzy (赞：6)

## 思路

题目要问的，是 $k$ 个物品最多能组成多少种不同的权值之和（每个数量不限）。

正着求当然很麻烦，但是反着解相对来说就简单多了。

所以我们可以将题目转化为：

**求凑某个权值和最少要多少物品，如果最少个数比 $k$ 要大，则这个权值和就无法凑出。**

题目分析到这里，就不难看出是背包 dp 了。

## 代码实现

### 状态转移

我们用 $dp_i$ 表示凑出权值和为 i 最少需要多少件物品。

01 背包问题这里不多阐述了。

则可以得到状态转移方程为：$dp_i \gets \min dp_i,dp_{i-a_j}+1$。

（j 为从 1 到 $n$ 个物品中满足 $a_j \le i$ 的物品。）

------------

### 优化

这里做一个简单的优化：

我们让权值最小的物品的权值为 0，其余的物品权值都减去最小的权值。

这样，最后当 $dp_i < k$（即数量不足）时，

可以用权值最小（刚刚权值清 0）的那个物品补上。

同时，在 dp 的时候我们也不用顾忌到数量要求了。

------------

### 代码

（更多细节请见代码及注释。）

```cpp
#include<bits/stdc++.h>
using namespace std;

const int maxn = 1005;
int n, k;
int limi;
int a[maxn], dp[maxn * maxn];

int read ()
{
	int x = 1, s = 0;
	char ch = getchar ();
	while (ch < '0' or ch > '9') {if (ch == '-') x = -1; ch = getchar ();}
	while (ch >= '0' and ch <= '9') s = s * 10 + ch - '0', ch = getchar ();
	return x * s;
}

int main ()
{
	memset (dp, 1e4, sizeof dp);//记得初始化 
	n = read (), k = read ();
	for (register int i (1); i <= n; ++i) a[i] = read ();
	
	sort (a + 1, a + n + 1);
	int tmp = a[1];
	for (register int i (1); i <= n; ++i) a[i] -= tmp;//记得是减去 kmp 而不是 a[1] 
	limi = k * a[n];
	dp[0] = 0;
	for (register int i (1); i <= limi; ++i)
	for (register int j (1); j <= n; ++j) if (a[j] <= i) dp[i] = min (dp[i], dp[i - a[j]] + 1);
	
	for (register int i (0); i <= limi; ++i) if (dp[i] <= k) printf ("%d ", i + tmp * k);//都要加上 kmp 因为之前减去了 
	return 0;
}
```

感谢阅读~

---

## 作者：Gaode_Sean (赞：5)

这是一道巧妙的完全背包问题。

设 $dp_i$ 表示能凑出价值为 $i$ 的最少物品数量。

则转移方程为 $dp[i]=\min(dp[i],dp[i-a[j]]+1)$，初始化 $dp_0=0$，其余为正无穷。

这样做只能处理 $dp_i=k$ 的情况，并不能处理 $dp_i \leq k$ 的情况。

我们可以考虑用一个价值为 $0$ 的物品使得物品的总价值不变，物品数量增加，这样对于 $dp_i \leq k$ 的情况，一定可以用 $k$ 个物品凑出总价值 $i$。

由此我们可以将所有物品的价值减去所有物品价值中的最小值，这样做保证可以出现一个价值为 $0$ 的物品。

## AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e3+1,M=1e6+1;
int val=1e9,a[N],n,k,dp[M];
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++){scanf("%d",&a[i]);val=min(val,a[i]);}
	for(int i=1;i<=n;i++) a[i]-=val;
	for(int i=1;i<M;i++) dp[i]=1e9;
	for(int i=1;i<=n;i++)
	{
		for(int j=a[i];j<M;j++) dp[j]=min(dp[j],dp[j-a[i]]+1);
	}
	for(int i=0;i<M;i++) if(dp[i]<=k) printf("%d ",val*k+i);
	return 0;
}
```

---

## 作者：luckydrawbox (赞：3)

## 题意

一个背包，$n$ 种物品，第 $i$ 种物品价值为 $a_i$，每种物品无穷个，只能拿 $k$ 个物品，问有哪些可能的价值？

## 分析

乍一看是一个完全背包模板，于是我们设 $dp_j$ 为当价值为 $j$ 时最少需要的物品数，可以写出方程式 $dp_j=\min(dp_j,dp_{j-a_i}+1)$，仅当 $dp_j=k$ 时，输出 $i$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1010,M=1e6,inf=1010;
int n,k,a[N],dp[N*N];
int main()
{
    cin>>n>>k;
    for(int i=1;i<=n;i++)
    	cin>>a[i];
    for(int i=1;i<=M;i++)
    	dp[i]=inf;
    for(int i=1;i<=n;i++)
    	for(int j=a[i];j<=M;j++)
    		dp[j]=min(dp[j],dp[j-a[i]]+1);
    for(int i=0;i<=M;i++)
    	if(dp[i]==k)
    		cout<<i<<" ";
	return 0;
}
```

然而连样例都过不了。

我们参考一下样例来找找原因：

```
3 2
1 2 3
```

原来在我们的计算里 $dp_3=1$，但其实 $dp_3=2=k$ 也是可行的。

那么有没有什么办法可以把 $1$ 个物品凑成 $2$ 个物品呢？

我们假设有一个最好的情况，我们已选物品的价值加上其他物品的价值后总价值不变，但总数量却能涨到 $k$ 个，在此样例中，设另外那个物品价值为 $x$，那么就相当于 $3+x=3,1+1=2=k$，即 $x=0$。也就是说，我们只要有价值为 $0$ 的物品，就可以凑成，可题目中 $1≤a_i≤1000$ 呀！

我们考虑之前的那个状态转移方程的变形：

若保证任意 $a_i≥v$，则之前的转移方程为 $dp_j=\min(dp_j,dp_{j-(a_i-v)}+1)$，设此时的某个答案为 $ans$，则真正答案可以转化为 $ans+k\times v$，也就是把之前缺少的价值补回来。

了解了这个变形，我们只需取 $v=\min_{i=1}^na_i$，就可以得到上面价值为 $0$ 的物品。

于是我们就用新的状态转移方程求出 $dp$ 数组，只要 $dp_i≤k$，即需要的最少物品数不大于 $k$ 个（缺少的可以用 $0$ 补），就算作一个答案。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1010,M=1e6,inf=1010;
int n,k,a[N],dp[N*N],v=inf;
int main()
{
    cin>>n>>k;
    for(int i=1;i<=n;i++)
	{
    	cin>>a[i];
		v=min(v,a[i]);
	}
    for(int i=1;i<=M;i++)//预处理赋极大值
    	dp[i]=inf; 
    for(int i=1;i<=n;i++)//减去最小值 
    	a[i]-=v; 
    for(int i=1;i<=n;i++)//普通完全背包 
    	for(int j=a[i];j<=M;j++)
    		dp[j]=min(dp[j],dp[j-a[i]]+1);
    for(int i=0;i<=M;i++)
    	if(dp[i]<=k)
    		cout<<i+k*v<<" ";
	return 0;
}
```


---

## 作者：SSHhh (赞：3)

这道估计大多数人看到题后，第一思路都是直接01背包，dp[j]=max(dp[j],dp[j-a[i]]+1)，那么你会发现，dp[i]，只能存一个数，而答案有很多种可能，比如样例，dp[2]=2，但是你可以取走两个 1 或一个 2，有两种情况，所以这个方法就再见了。

然后又会有人想到第二种思路：dp[i][j]=max(dp[i-1][j],dp[i-1][j-a[l]]+1)，这个方法正确性固然不会错，但一看数据范围，n 是 1000，k 是 1000，还有枚举 l 的复杂度 1000，好吧，又再见了。。。

所以思路是什么呢(其实我刚开始也不知道)，后来我上百度查了一下，百度的方法(就是楼下说的思路)是这样的：把所有数字排序后，给所有数字减去 a[1] (当然 a[1] 不用减)，然后拿这些数字直接去做01背包就行了。dp[i] 表示当前总价值是 i 时最少需要拿几个物品。

不过这个算法的正确性如何证明呢？

对于每一种取法，每一项减去 a[1] 后会空出 k 个 a[1] 的位置，那么每一种合法的 dp[i] 一定相当于没有减去时的 dp[i+a[1]·k]，因为对于每一个 i ，i+a[1]·k 都不相同，所以对于每一种合法的 dp[i]，dp[i+a[1]·k] 一定只有一种情况————总代价为 i+a[1]·k。直接输出这个数就行了。。。

下来就是具体代码实现了：

```cpp
#include<iostream>
#include<algorithm>
#include<string.h>
using namespace std;
int n,k,a[1005],dp[1000005];
bool cmp(int i,int j) {return i<j;}	//从小到大排序
int main()
{
    memset(dp,12,sizeof(dp));	//乱搞的初始化最大值
    cin>>n>>k;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    sort(a+1,a+n+1,cmp);
    for(int i=2;i<=n;i++)	a[i]-=a[1];	//骚操作
    dp[0]=0;
    for(int i=2;i<=n;i++)	//一定别忘了i从2开始枚举
        for(int j=0;j<=a[n]*k;j++)
            if(j>=a[i])	dp[j]=min(dp[j],dp[j-a[i]]+1);	//转移
    for(int i=0;i<=a[n]*k;i++)
        if(dp[i]<=k)	//判断当前 dp[i] 是否可以满足要求
            cout<<a[1]*k+i<<" ";
    return 0;
}
```

---

## 作者：little_gift (赞：2)

观察到价值最多到1e6那么考虑多项式

构造一个价值的生成函数然后多项式快速幂就好了

当然快速幂的时候可以逐次调整长度不用像我一样每次都1e6在那卷最后慢得要死

但是听~~[Weng_Weijie](https://www.luogu.org/space/show?uid=26127)~~说模数998244353和1004535809都被干掉了?

发现题目问的只是存在性而不是方案数所以可以每次卷积之后把所有存在的数都换成1

然后直接单模数卷

……好像没什么问题

当然双模~~或者三模~~也是正确的而且顺便还可以求出方案数

复杂度如果每次都1048576卷的话是2e9对于5s题还是能过去的

```cpp
#include <cstdio>
#include <algorithm>
constexpr int Mod=998244353;
inline void up(int& x) { x+=x>>31&Mod; }
inline int qpow(int a,int p,int s=1) {
	for (;p;p>>=1,a=1ll*a*a%Mod) if (p&1) s=1ll*s*a%Mod;
	return s;
}
constexpr int mxlen=1<<20;
int r[mxlen],w[mxlen],d;
void fftinit(int len) {
	int _d=(d=__builtin_ctz(len))-1;
	for (int i=1;i<len;++i) r[i]=r[i>>1]>>1|(i&1)<<_d;
	int wn=qpow(3,(Mod-1)>>d); w[len>>1]=1;
	for (int i=(len>>1)+1;i<len;++i) w[i]=1ll*w[i-1]*wn%Mod;
	for (int i=len>>1;--i;) w[i]=w[i<<1];
}
void dft(int a[],int len) {
	int shift=d-__builtin_ctz(len);
	for (int i=0;i<len;++i) if (i<r[i]) std::swap(a[i],a[r[i]>>shift]);
	for (int l=1;l<len;l<<=1) for (int i=0;i<len;i+=l<<1) for (int j=0;j<l;++j) {
		int tmp=1ll*a[i+j+l]*w[j+l]%Mod; up(a[i+j+l]=a[i+j]-tmp); up(a[i+j]+=tmp-Mod);
	}
}
void idft(int a[],int len) {
	std::reverse(a+1,a+len); dft(a,len);
	for (int invn=qpow(len,Mod-2),i=0;i<len;++i) a[i]=1ll*a[i]*invn%Mod;
}
void psmul(int s[],int a[],int len) { //多项式乘法
	static int t[mxlen];
	__builtin_memcpy(t,a,sizeof(int)*len);
	dft(s,len); dft(t,len);
	for (int i=0;i<len;++i) s[i]=1ll*s[i]*t[i]%Mod;
	idft(s,len);
	for (int i=0;i<len;++i) s[i]=!!s[i]; //每次卷完之后把存在的项值都变为1
}
int n,k,a[mxlen],s[mxlen];
int main() {
	int len=mxlen; fftinit(len);
	scanf("%d%d",&n,&k);
	for (int i=0;i<n;++i) {
		int x; scanf("%d",&x); a[x]=1;
	}
	s[0]=1;
	for (;k;k>>=1,psmul(a,a,len)) if (k&1) psmul(s,a,len);
	for (int i=0;i<=1000000;++i) if (s[i]) {
		static bool first=1;
		if (first) first=0;
		else putchar(' ');
		printf("%d",i);
	}
	putchar('\n');
}
```

---

## 作者：sto_5k_orz (赞：1)

每种物品无限选，还有 $n \leq 1000$ 这种数据范围，那绝对是完全背包。

$dp_{i}$ 表示凑出第 $i$ 件物品需要多少个物品，于是， $dp_{i}=k$ 的数就是答案。转移方程是 $dp_ {j}={dp_{j-a{i}}}+1$

code:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1010;
int dp[N * N], n, k, a[N];
int main() {
	cin >> n >> k;
	for(int i = 1; i <= n; i++) cin >> a[i];
	int M = a[n] * k; // M是枚举的最大值
	memset(dp, 63, sizeof dp);
	dp[0] = 0;
	for(int i = 1; i <= n; i++) for(int j = a[i]; j <= M; j++) dp[j] = min(dp[j], dp[j - a[i]] + 1);
	for(int i = 0; i <= M; i++) if(dp[i] == k) cout << i << " ";
	return 0;
}
```

结果呢？样例没过。因为样例 $1$ 中， $dp_{3} = 1$ ，但 $3$  也可以用 $3$ 个 $1$ 凑成。要是有一个 $a _{i} = 0$ 就好了！怎么办呢？人工制造。将每个数都减去最小值，那么最小值就变成了 $0$， 到了要算的时候，在加回去就可以了。

code:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1010;
int dp[N * N], n, k, sum, mi, a[N];
int main() {
	cin >> n >> k;
	for(int i = 1; i <= n; i++) cin >> a[i];
	sort(a + 1, a + 1 + n);
	int M = a[n] * k; // M为最大值 
	mi = a[1];
	memset(dp, 63, sizeof dp); // 初始化 
	dp[0] = 0;
	for(int i = 1; i <= n; i++) a[i] -= mi;
	for(int i = 1; i <= n; i++) for(int j = a[i]; j <= M; j++) dp[j] = min(dp[j], dp[j - a[i]] + 1); // 精髓 
	for(int i = 0; i <= M; i++) if(dp[i] <= k) cout << i + k * mi << " "; // 加回去 
	return 0;
}
```

然后，我们就用一道做黄题的方法 AC 了紫题

---

## 作者：Argon_Cube (赞：0)

* **【题目链接】**

[Link:CF632E](http://codeforces.com/problemset/problem/632/E)

* **【解题思路】**

设 

$$F(x)=\sum\limits_{i=1}^nx^{a_i}$$

显然答案即为 $F^k(x)$ 中系数不为 $0$ 的项的次数。

注意，模数 $998244353$ 与 $1004535809$ 都被 Hack 了，原理大概是让方案数正好是模数的倍数。这里我的模数取了 $167772161$ 就过了。

然后，在 [【模板】多项式快速幂（加强版）](https://www.luogu.com.cn/problem/P5273) 中，我们之所以使用 $\ln$ 与 $\exp$ 而不是直接将点值取 $k$ 次幂的原因是因为次数有可能溢出。现在我们不用担心溢出问题自然就可以直接将点值取 $k$ 次幂了，常数小了很多，还不用担心常数项。

* **【代码实现】**

```cpp
//前面的多项式板子省去了。
int main(int argc,char* argv[],char* envp[])
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int tmp,cnt,exponent;
	cin>>cnt>>exponent;
	while(cnt--)
		cin>>tmp,poly[tmp]++;
	int ceil_cnt=ceil_binary(exponent*1000+1);
	init_binrev(ceil_cnt);
	NTT(ceil_cnt,poly,1);
	for(int i=0;i<ceil_cnt;i++)
		poly[i]=fast_pow(poly[i],exponent,prime);
	NTT(ceil_cnt,poly,-1);
	for(int i=0;i<ceil_cnt;i++)
		if(poly[i])
			cout<<i<<' ';
	return 0;
}
```

---

## 作者：AC自动机 (赞：0)

### 思路

首先只能想到这是一个完全背包，然后具体实现也不会，后来想了一会，发现可以用dp[i]来表示当总价值为i的时候，所用的物品的最小数目，由一个简单的贪心思想可以得到，显然相同的价值，用的物品越少，那么后面的发展机会就越大2333333

但是最后发现当下面这组数据时：

3 2

1 2 3

然后人就凉了，因为dp[3]跑出来是1，因为当时的dp的定义是选最小，这时就没有办法判断到底是否可以用2个物品达到价值为3。

然后就需要百度了qwq，先把价值由小到大进行排序，然后把所有的数都减去最小的那个数，这样当dp[i]的值比k小的时候，就可以加上任意多个第一个数，这样就可以处理这种情况了，要是不看题解我估计一辈子都想不到╮(╯▽╰)╭



#### 代码

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
inline int cmp(int a,int b){
	return a<b;
}
int dp[1000005];
int cos[1005];
int main(){
	int n,k;
	cin>>n>>k;
	for(register int i=0;i<=1000004;i++){
		dp[i]=99999999;
	}
	for(register int i=1;i<=n;i++){
		cin>>cos[i];
	}
	sort(cos+1,cos+n+1,cmp);
	dp[0]=0;
	for(register int i=1;i<=n;i++){
		for(register int j=cos[i]-cos[1];j<=1000004;j++){
			dp[j]=min(dp[j-(cos[i]-cos[1])]+1,dp[j]);
		}
	}
	//cout<<dp[6]<<endl;
	for(register int i=0;i<=1000004;i++){
		//cout<<dp[i]<<endl;
		if(dp[i]<=k){
			cout<<(k-dp[i])*cos[1]+dp[i]*cos[1]+i<<' ';
		}
	}
}
```

---

## 作者：gyyyyx (赞：0)

[题面](https://www.luogu.com.cn/problem/CF632E)

题目大意：给出 $n,k$ 和长度为 $n$ 的序列 $a$，要在其中选出**恰好** $k$ 个数，**可重复选**，求选出的数之和有多少种取值。

假设一开始已经选好了 $k$ 个数，都是 $x$，那如果要换其它选择方式，则数字和一定会先减去若干 $x$，然后加上另外若干个数。

设 $b_i=a_i-\min\{a_i\}$，那么题目就变成：从 $b$ 中选出**不超过** $k$ 个数，求数字和有多少种取值。

这就是普通的完全背包。

设 $f_j$ 为选出的数之和为 $j$ 时最少需要选出多少个数，有 $f_j=\min(f_j,f_{j-b_i}+1)$。

```cpp
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f
#define N 1001
using namespace std;
int n,k,a[N],mn(INF),b[N],f[N*N+5];
int main(){
	scanf("%d%d",&n,&k);
	for(int i(1);i<=n;++i){
		scanf("%d",&a[i]);
		mn=min(mn,a[i]);
	}
	for(int i(1);i<=n;++i) b[i]=a[i]-mn;
	for(int j(1);j<=N*N;++j) f[j]=INF;
	for(int i(1);i<=n;++i)
		for(int j(b[i]);j<=N*N;++j)
			f[j]=min(f[j],f[j-b[i]]+1);
	for(int j(0);j<=N*N;++j)
		if(f[j]<=k) printf("%d ",mn*k+j);
	return 0;
}
```

这应该是我做过最简单的一道紫题了。

---

## 作者：hxhhxh (赞：0)

## 大意

给定 $ n $ 种物品和一个正整数 $ k $ ，每一种物品有无限个并有一个固定的权值，求恰好 $ k $ 个物品的权值和的所有可能值。

## 思路

可以考虑进行背包`dp`，求出凑出权值 $ i $ 至少需要几次，但是这样就会出现一个问题，参见样例 $ 1 $ ，`dp[3]=1`，但凑出权值 $ 3 $ 也可以用两个物品。

这时候，如果有一个权值为 $ 0 $ 的物品，那就好办了。哪里有这样的物品呢？人工制造。

由于一定要恰好选 $ k $ 个物品，所以权值至少是最小权值的 $ k $ 倍，剩下的就相当于用大权值物品换掉小权值物品，多处来一些权值。

可以将所有物品的权值减掉最小权值物品的权值。

如果`dp`出来数量不足 $ k $ 可以用 $ 0 $ 补上，最后将总权值加回来 $ k $ 倍的最小权值就是真实是权值和了。

## 代码
```cpp
#include<bits/stdc++.h>
#define min(a,b) (a)<(b)?(a):(b) 
using namespace std;
int n,k,a[2005],mn=1000000000,f[1000006],s,mx;
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++) scanf("%d",&a[i]),mn=min(mn,a[i]),mx=max(mx,a[i]);
	for(int i=1;i<=n;i++) a[i]-=mn;
	s=(mx-s)*k;
	memset(f,0x3f,sizeof(f));
	f[0]=0;
	for(int i=1;i<=n;i++) for(int j=a[i];j<=s;j++) f[j]=min(f[j],f[j-a[i]]+1);
	for(int i=0;i<=s;i++) if(f[i]<=k) printf("%d ",i+k*mn);
	return 0;
}
```

---

