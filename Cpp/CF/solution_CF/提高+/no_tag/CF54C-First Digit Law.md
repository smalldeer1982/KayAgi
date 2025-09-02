# First Digit Law

## 题目描述

In the probability theory the following paradox called Benford's law is known: "In many lists of random numbers taken from real sources, numbers starting with digit 1 occur much more often than numbers starting with any other digit" (that's the simplest form of the law).

Having read about it on Codeforces, the Hedgehog got intrigued by the statement and wishes to thoroughly explore it. He finds the following similar problem interesting in particular: there are $ N $ random variables, the $ i $ -th of which can take any integer value from some segment $ [L_{i};R_{i}] $ (all numbers from this segment are equiprobable). It means that the value of the $ i $ -th quantity can be equal to any integer number from a given interval $ [L_{i};R_{i}] $ with probability $ 1/(R_{i}-L_{i}+1) $ .

The Hedgehog wants to know the probability of the event that the first digits of at least $ K% $ of those values will be equal to one. In other words, let us consider some set of fixed values of these random variables and leave only the first digit (the MSD — most significant digit) of each value. Then let's count how many times the digit 1 is encountered and if it is encountered in at least $ K $ per cent of those $ N $ values, than such set of values will be called a good one. You have to find the probability that a set of values of the given random variables will be a good one.

## 样例 #1

### 输入

```
1
1 2
50
```

### 输出

```
0.500000000000000```

## 样例 #2

### 输入

```
2
1 2
9 11
50
```

### 输出

```
0.833333333333333```

# 题解

## 作者：Mihari (赞：3)

# 题目

[传送门](https://www.luogu.com.cn/problem/CF54C)

人话表述：

给你一个 $n$ 表示数列 $a$ 有多少个数；

对于每个数，给出 $l_i,r_i$ 表示数 $a_i\in [l_i,r_i]$；

给出 $k$，让你求数列 $a$ 中有至少 $\frac{n\times k}{100}$ 个数最高位为 $1$ 的概率并输出；

# 题解

巧妙的数位 $DP$ + 概率 $DP$ + 背包（虽然说题目表述不清就是了

可以利用 $l_i,r_i$ 求出 $a_i$ 最高位为 $1$ 的概率 $p_i$.

现在我们已经有了每一位出现合法数字的概率，考虑怎么拼凑出答案

关注题目，“求在 $n$ 个数中，至少有 $k$ 个数最高位为 $1$ 的概率”，发现有点像背包

考虑定义状态 $f[i][j]$ 表示前 $i$ 个数中，有 $j$ 个数的最高位为 $1$ 的概率，那么我们可以写出转移：

对于 $j=0$，实际上只可能由 $f[i-1][0]$ 一种情况转移过来，而这一位也只能选择 $0$，那么就有状转
$$
f[i][0]=f[i-1][0]\times (1-p[i])
$$
对于 $j>0$，有两种情况：

- 这一位选非 $1$ 开头的数字，由 $f[i-1][j]$ 转移；
- 这一位选择 $1$ 开头的数字，由 $f[i-1][j-1]$ 转移；

这两种情况相互独立，用加法连接，那么有转移
$$
f[i][j]=f[i-1][j]\times (1-p[i])+f[i-1][j-1]\times p[i]
$$
最后统计答案，由于都是独立，也直接相加即可

```cpp
https://www.cnblogs.com/Arextre/p/13473866.html
```


---

## 作者：_masppy_ (赞：2)

###  题目链接：[Link](https://www.luogu.com.cn/problem/CF54C)

&nbsp;

### 题目大意：
有一个长度为 $n$ 的序列 $a$，已知 $a_i \in [l_i,r_i]$，求序列 $a$ 中 有至少 $x\%$ 的数最高位为 $1$ 的概率。

&nbsp;

### 解题思路：
个人感觉算是一道没那么绕的题。$dp$ 状态比较好想，可以定义 $dp[i][j]$ 为序列前 $i$ 个数中至少有 $j$ 个数最高位为 $1$ 的概率。转移方程如下：
$$dp[i][j]=\begin{cases}1&j=0\\dp[i-1][j]+dp[i-1][j-1] \times\dfrac{\text{区间内1的个数}}{r_i-l_i+1}&j>0\end{cases}$$

区间内 $1$ 的个数也不是很难统计，枚举 $10^k$，判断 $[10^k,2\times 10^k-1]$ 之间有多少属于 $[l_i,r_i]$ 即可。

核心代码如下：
```cpp
	dp[0][0]=1.0;
	for(int i=1;i<=n;i++){
		ll num=0;
		ll l,r;
		scanf("%lld%lld",&l,&r);
		
		ll x=1ll;
		while(x*2ll<=l) x*=10ll;
		while(x<=min(999999999999999999,r)){
			num+=min(r-max(l,x)+1ll,min(x,x+x-l));
			x*=10ll;//枚举10^k
		}
		if(r==1000000000000000000) num++;//特殊判断1e18
		dp[i][0]=1.0;
		for(int j=1;j<=i;j++){//转移
			dp[i][j]=dp[i-1][j]+(dp[i-1][j-1]-dp[i-1][j])*num/(r-l+1.0);
		}
	}
```

不过这种方法的内存占用...

![](https://cdn.luogu.com.cn/upload/image_hosting/1a79ekki.png)

和各路大神们的 `0B` 似乎还是差了些，于是考虑对于 $dp$ 数组优化。

发现转移似乎只和 $i$ 与 $i-1$ 有关，显然可以滚动数组，于是将 $j$ 改为从大往小枚举，把 $dp$ 数组转成 $1$ 维。

代码如下：
```cpp
int main(){
	scanf("%d",&n);
	
	dp[0]=1.0;
	for(int i=1;i<=n;i++){
		ll num=0,l,r;
		scanf("%lld%lld",&l,&r);
		
		ll x=1ll;
		while(x*2ll<=l) x*=10ll;
		while(x<=min(inf-1,r)){
			num+=min(r-max(l,x)+1ll,min(x,x+x-l));
			x*=10ll;
		}
		if(r==inf) num++;
		for(int j=i;j>=1;j--) dp[j]+=(dp[j-1]-dp[j])*num/(r-l+1.0);
	}
	scanf("%lf",&m);
	
	y=m/100.0;
	x=n*y;
	if(n*y>(double)(x)) x++;
	
	printf("%.10f",dp[x]);
	return 0;
}

```

![](https://cdn.luogu.com.cn/upload/image_hosting/gmrrfau1.png)

嘻

---

## 作者：vvauted (赞：2)

- [CF54C First Digit Law](https://www.luogu.com.cn/problem/CF54C)

概率 $dp$ 入门题。

设 $f(x)$ 是 $[1,x]$ 中 $1$ 开头数字的个数，显然需要求的 $[l_i,r_i]$ 中 $1$ 开头数字的个数 $g(l_i,r_i)$ 就可以通过差分得到，而 $f(x)$ 可以通过简单数位 dp 得到。

显然对于第 $i$ 个数字来说，它为 $1$ 开头的数字的概率 

$$p_i =\frac {g(l_i,r_i)}{r-l+1}$$

可以 $O(n\lg V)$ 得到，那么剩下的部分即为我们使用这个概率做背包。

> $f_{i,j}$ 为考虑了前 $i$ 个数，其中有 $j$ 个 $1$ 开头的数字的概率，那么第 $i$ 位只有两种可能：是或者不是。易推得转移方程：

> $$f_{i,j}=p_if_{i-1,j-1}+(1-p_i)f_{i-1,j}$$

> 是 $1$ 开头数字的概率是 $p_i$，不是的概率是 $1-p_i$，与前面的概率用乘法法则乘得，而两个事件相互独立，用加法法则加起。

**Code**

```cpp
#include <bits/stdc++.h>
#define Maxn 1005
#define Nep(i, l, r) for(int i = l; i != r; ++ i)
#define Rep(i, l, r) for(int i = l; i <= r; ++ i)
#define rep(i, l, r) for(int i = l; i < r; ++ i)
#define Lep(i, l, r) for(int i = l; i >= r; -- i)
#define lep(i, l, r) for(int i = l; i > r; -- i)
#define Max(a, b) a = std :: max(a, b)
#define ll long long
#define ull unsigned long long
#define int long long

int read() {
	int x = 1, res = 0, ch = getchar();
	while(ch < '0' || ch > '9') { if(ch == '-') x = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9') res = (res << 3) + (res << 1) + (ch ^ 48), ch = getchar();
	return x * res;
}

double a[Maxn], f[Maxn];
int p[Maxn];

int calc(int x) {
    if(x == 0) return 0;
    p[0] = 1; Rep(i, 1, 18) p[i] = p[i - 1] * 10; int xx = x; 
    std :: vector <int> g; while(x) g.push_back(x % 10), x /= 10;
    int l = g.size() - 1; int ans = 0;
    rep(i, 0, l) ans += p[i]; if(g[l] == 1) ans += xx - p[l] + 1; 
    else ans += p[l]; return ans;
}

double solve(int x, int y) {
    return (calc(x) - calc(y - 1)) * 1.0 / (x - y + 1);
}

signed main() {
    int n = read(), m, l, r; 
    Rep(i, 1, n) l = read(), r = read(), a[i] = solve(r, l);
    m = ceil(read() * n * 1.0 / 100); f[0] = 1;
    Rep(i, 1, n) Lep(j, n, 0) f[j] = f[j] * (1 - a[i]) + (j > 0) * f[j - 1] * a[i];
    double ans = 0; Rep(i, m, n) ans += f[i]; printf("%.9g", ans);
}
```

---

## 作者：C6H14 (赞：2)

## 一点废话

[题目传送门](https://www.luogu.com.cn/problem/CF54C)

[My blog](https://www.luogu.com.cn/blog/128433/#)

## 思路

假设第 $i$ 位是以 $1$ 开头的数字概率为 $p_i$，且前 $i$ 位共有 $j$ 个数开头为 $1$ 的概率为 $f_{i,j}$，显然可以转移：

$$
f_{i,j}=\begin{cases}(1-p_i) \cdot f_{i-1,0}&x=0\\(1-p_i) \cdot f_{i-1,j-1} + p_i \cdot f_{i-1,j}&x>3\end{cases}
$$

怎么求 $p_i$ 呢？

考虑 $1$ 到 $a_i$ 中有多少个开头为 $1$ 的数，假设 $a_i$ 的位数为 $x+1$。

那么在 $1$ 到 $10^x-1$ 中一共有 $\begin{matrix}\underbrace{11\dots1}\\x-1\text{个}\end{matrix}$ 个开头为 $1$ 的数；若 $a_i$开头为 $1$，则在 $10^x-1$ 到 $a_i$ 中一共有 $a_i \% 10^x$ 个开头为 $1$ 的数；若 $a_i$ 开头不为 $1$，则在 $10^x$ 到 $a_i$ 中一共有 $10^x$ 个开头为 $1$ 的数。

注意一下可能爆 long long 即可。

时间复杂度 $O(n^2)$，妥妥能过。

## 代码

```cpp
__int128 f[105][105][105];
ll n,k;
int main()
{
	f[0][0][0]=1;
	for (int i=0;i<100;++i)
		for (int j=0;j<=i;++j)
			for (int k=0;k<=i;++k)
				f[i+1][j+1][max(k,j+1)]+=f[i][j][k],f[i+1][0][k]+=f[i][j][k];
	while (~scanf("%lld%lld",&n,&k))
	{
		__int128 ans=0;
		for (int i=0;i<=n;++i)
			for (int j=k;j<=n;++j)
				ans+=f[n][i][j];
		write(ans,'\n');
	}
	return 0;
}

```


---

## 作者：smoothset (赞：2)

#### 思路

首先对于这个区间 $[l, r]$ 之间的数我们可以用差分的方式将它们开头是$1$的概率求出来

令 $dp[i]$ 表示有 $i$ 个数的第$1$位是$1$的概率

然后呢再用一个概率 $dp$ ，考虑每个区间的贡献，将其概率求出来

最后再暴力枚举 $[1, n]$ 累加满足条件的概率即可
#### 代码
具体实现见代码
~~~cpp
typedef long long ll;
ll count(ll n)
{
    ll ans = 0, x = 1, cnt = 0, high = 0, num = n;
    while (num)
    {
        high = num % 10;
        num /= 10;
        cnt++;
    }
    cnt--;
    for (int i = 1; i <= cnt; i++, x *= 10)
        ans += x;
    if (high > 1)
        ans += x;
    else if (high == 1)
        ans += n - x + 1;
    return ans;
}
const int N = 1005;
double p[N], dp[N], ans;
int n, k;
ll l, r;
int main()
{
    ios :: sync_with_stdio(0);
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> l >> r;
        ll tmp = count(r) - count(l - 1);
        p[i] = 1.0 * tmp / (r - l + 1);
    }
    cin >> k;
    dp[0] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = n; j >= 0; j--)
        {
            dp[j] = dp[j] * (1 - p[i]);//当它不贡献时
            if (j > 0)
                dp[j] += dp[j - 1] * p[i];
        }
    for (int i = 0; i <= n; i++)
        if (i * 100 >= n * k)
            ans += dp[i];
    printf ("%.15f", ans);
    return 0;
}
~~~
[最后安利一下我的博客](https://blog.csdn.net/qq_43537070/article/details/107928701)

---

## 作者：wind_whisper (赞：1)

## $\text{Description}$
给出 $n$ 个数，然后给出 $n$ 行，每行 $l_i,r_i$，代表第 $i$ 个数在区间 $[l_i,r_i]$ 中，求一个概率使得这 $n$ 个数中有 $k\%$ 的数是 $1$ 开头的.  
$n\le1000,1\le l_i\le r_i\le10^{18}$.
## $\text{Solution}$
设 $f_x$ 为 $[1,x]$ 符合条件的数的个数，$sum_x=\sum_{x=0}^x 10^i$，$w_x$ 为满足 $10^i\le x$ 的最大的 $i$.  
就有：
$$f_x=\min(2\times10^{w_x}-1,x)-10^{w_x}+1+sum_{w_x-1}$$

那么第 $i$  个数符合条件的概率就是 $\dfrac{f_{r_i}-f_{l_i-1}}{r_i-l_i+1}$.  
求出每个变量的概率之后，简单 $n^2$ dp即可.  
细节上，注意 $10^{18}$ 乘 $10$ 会爆 longlong，所以求 $w_x$ 判断时要乘转除.  
## $\text{Code}$
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
//#define double long double
#define debug(...) fprintf(stderr,__VA_ARGS__)
const int N=1050;
const int mod=1e9+7;
inline ll read(){
  ll x(0),f(1);char c=getchar();
  while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
  while(isdigit(c)){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
  return x*f;
}

int n,m,k;
ll sum[20],mi[20];
double dp[N][N],p[N];
ll calc(ll x){
  if(x==0) return 0;
  int o=0;
  while(x/mi[o]>=10) ++o;
  return (o?sum[o-1]:0)+min(x,2*mi[o]-1)-mi[o]+1;
}
signed main(){
  #ifndef ONLINE_JUDGE
  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);
  #endif
  mi[0]=sum[0]=1;
  for(int i=1;i<=18;i++){
    mi[i]=mi[i-1]*10;sum[i]=sum[i-1]+mi[i];
  }
  n=read();
  for(int i=1;i<=n;i++){
    ll l=read(),r=read();
    p[i]=1.0*(calc(r)-calc(l-1))/(r-l+1);
    //printf("i=%d p=%lf\n",i,p[i]);
  }
  dp[0][0]=1;
  for(int i=0;i<n;i++){
    for(int j=0;j<=i;j++){
      dp[i+1][j+1]+=dp[i][j]*p[i+1];
      dp[i+1][j]+=dp[i][j]*(1-p[i+1]);
    }
  }
  int k=read();
  double res=0.0;
  for(int i=(n*k+99)/100;i<=n;i++) res+=dp[n][i];
  printf("%.10lf",res);
  return 0;
}
/*

*/

```


---

## 作者：baka24 (赞：0)

### 第一步，算出 $l_i-r_i$ 的区间内有 $w_i$ 个数是 $1$ 开头的

方法很多，推荐一种先分别算出 $1-l$ 之间和 $1-r$ 之间 $1$ 开头的数的数量再相减。

当我们求取 $1-x$ 之间开头为 $1$ 的数时，先算出位数 $t$，当 $x$ 首位不为 $1$ 时，答案为 $\sum\limits_{i=0}^{t-1}10^i $,否则答案为 $x-10^{t-1}+\sum\limits_{i=0}^{t-2}10^i$.

### 第二步，算出至少需要几个数是 $1$ 开头。
根据题意可得：
$$\text{需求数量=}\lceil \frac{k\times n}{100} \rceil$$

### 第三步，计算具体概率

设 $f_{i,j}$ 表示只看前 $i$ 段区间，符合条件的数的数量。$p_i$ 为第 $i$ 段区间选中 $1$ 开头的数的概率：$p_i=\frac{w_i}{r_i-l_i+1}$.

**转移**：

我们发现截至 $i$ 选中了 $j$ 个数的概率有两种情况

1. 本来就选中了 $j$ 个，第 $i$ 次没选中
2. 本来选中了 $j-1$ 个，第 $i$ 次选中了

所以可得：
$f_{i,j}=f_{i-1,j}\times(1-p_i)+f_{i-1,j-1}\times p_i$

边界：$f_{i,0}=1$

选 $0$ 个怎么选都是肯定成功。


```
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN=1010;
int n,k,l[MAXN],r[MAXN],cnt;
double w[MAXN],s[MAXN];
double f[MAXN],ans;
int Pow(int x,int y){
    int rt=1;
    while(y){
        if(y%2)rt*=x;
        x=x*x;
        y/=2;
    }
    return rt;
}
int num_1(int x){
    if(x==0)return 0;
    int rt=0,cnt=0,tmp=x;
    while(tmp){
        cnt++;
        tmp/=10;
    }
    for(int i=1;i<cnt;i++){
        rt+=Pow(10,i-1);
    }
    if(x/Pow(10,cnt-1)>1)rt+=Pow(10,cnt-1);
    else{
        rt+=x-(Pow(10,cnt-1)-1);
    }
    return rt;
}
signed main(){
    scanf("%lld",&n);
    for(int i=1;i<=n;i++){
        scanf("%lld%lld",&l[i],&r[i]);
    }
    scanf("%lld",&k);
    int num=(k*n-1)/100+1;
    if(k==0)num=0;
    for(int i=1;i<=n;i++){
        int tmp=num_1(r[i])-num_1(l[i]-1);
        if(tmp>0&&tmp<r[i]-l[i]+1){
            w[++cnt]=tmp;s[cnt]=r[i]-l[i]+1;
        }
        if(tmp==r[i]-l[i]+1&&num)num--;
    }
    f[0]=1;
    for(int i=1;i<=cnt;i++){
        for(int j=i;j>=1;j--){
            f[j]=f[j]*(s[i]-w[i])/s[i]+f[j-1]*w[i]/s[i];
        }
    }
    printf("%.10f",f[num]);
    return 0;
}
···

---

## 作者：Svemit (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF54C)

# Solution：

一个比较简单的数位 dp处理技巧加上一个暴力的 dp。

设 $p_i$ 为区间 $[l_i, r_i]$ 中出现 $1$ 开头的数的概率。

考虑 $solve(x)$ 函数为求出 $[1, x]$ 中开头为 $1$ 的个数。

显然低于 $x$ 的位数的数是全部能取到的，这时候开头为 $1$ 的个数有 $\sum_{i=1}^{len - 1} 10^{i-1}$ 个，再考虑位数等于 $x$ 的位数的数。

如果 $x$ 的开头大于 $2$ 的话，显然这一位的是可以全部取到的，小于 $2$ 的话就加上 $x - 10^{len - 1} + 1$ 即可。

算出概率后就可以直接 dp 了。

设 $f[i][j]$ 为前 $i$ 个区间有 $j$ 个 $1$ 开头的数的概率。

显然有方程：

$$f[i][j] = f[i-1][j] \times (1-p[i]) + f[i-1][j-1] \times p[i]$$

[代码](https://codeforces.com/contest/54/submission/220094551)

---

