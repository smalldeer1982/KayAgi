# Counting Arrays

## 题目描述

You are given two positive integer numbers $ x $ and $ y $ . An array $ F $ is called an  $ y $ -factorization of $ x $ iff the following conditions are met:

- There are $ y $ elements in $ F $ , and all of them are integer numbers;
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF893E/d8d5a9dcea7fa6a7abfa89d7da34d6fb180c0f69.png).

You have to count the number of pairwise distinct arrays that are $ y $ -factorizations of $ x $ . Two arrays $ A $ and $ B $ are considered different iff there exists at least one index $ i $ ( $ 1<=i<=y $ ) such that $ A_{i}≠B_{i} $ . Since the answer can be very large, print it modulo $ 10^{9}+7 $ .

## 说明/提示

In the second testcase of the example there are six $ y $ -factorizations:

- $ {-4,-1} $ ;
- $ {-2,-2} $ ;
- $ {-1,-4} $ ;
- $ {1,4} $ ;
- $ {2,2} $ ;
- $ {4,1} $ .

## 样例 #1

### 输入

```
2
6 3
4 2
```

### 输出

```
36
6
```

# 题解

## 作者：hyman00 (赞：16)

首先正负数不用管，最后乘 $2^{y-1}$ 即可。

即确定了所以 $|a_i|$ 后，前 $n-1$ 个正负随便填，最后一个可以根据前面的唯一算出来。

接着，我们将 $x$ 分解，设 $x=p_1^{e_1}p_2^{e_2}\dots p_k^{e_k}$。

我们对每个质因子 $p_i$ 分开考虑：

也就转化为将 $e_i$ 个随便分给 $y$ 个数字，形式化的说，就是求有多少序列 $b_1,\dots,b_y\ge0$，使得 $\sum_j b_j=e_i$。

这个问题就是《小学奥数》里的《插板法》，具体自行百度，答案是 $C_{e_i+y-1}^{y-1}$。

这样，对每个质因子求出答案乘起来再乘 $2^{y-1}$ 即可，注意到 2 的次幂和组合数可以预处理，$O(1)$ 查询。

具体实现看代码（头文件省略）。

```c++
const int MOD=1000000007;
int qpow(int a,int b){		//快速幂
	int s=1;
	while(b){
		if(b&1)(s*=a)%=MOD;
		b>>=1;
		(a*=a)%=MOD;
	}
	return s;
}
int inv(int x){				//求逆元（费马小定理）
	return qpow(x,MOD-2);
}
int fac[1000106],fnv[1000106];
int pw[1000106];
int C(int a,int b){			//计算组合数
	re fac[a]*fnv[b]%MOD*fnv[a-b]%MOD;
}
int x,y;
int chk(int k){				//计算k次幂的贡献
//	cout<<"C("<<k+y-1<<","<<k<<")="<<C(k+y-1,k)<<";\n";
	re C(k+y-1,k);
}
void run(){
	cin>>x>>y;
	int ans=pw[y-1];
	for(int i=2;i*i<=x;i++){
		if(x%i==0){
			int r=0;
			while(x%i==0)x/=i,r++;
			(ans*=chk(r))%=MOD;
		}
	}
	if(x>1)(ans*=chk(1))%=MOD;
	cout<<ans<<"\n";
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	fac[0]=fnv[0]=pw[0]=1;	//预处理
	rept(i,1,1000105){
		fac[i]=fac[i-1]*i%MOD;
		fnv[i]=inv(fac[i]);
		pw[i]=pw[i-1]*2%MOD;
	}
	int tc=1;
	cin>>tc;
	while(tc--)
		run();
	re 0;
}

```

---

## 作者：mydiplomacy (赞：13)

这里我提供一个数学做法。

我们用$C(i,j)$代表从$j$个元素中选择$i$个元素组成无序元素对的方案数。

首先，考虑安排正负号。由于$x$是正数，所以最终方案中的$y$项必然有偶数个负号。

那么，正负号的安排方案共有

$C(0,y)+C(2,y)+C(4,y)+C(6,y)+...+C(y,y)$ （$y$是偶数时）

$C(0,y)+C(2,y)+C(4,y)+C(6,y)+...+C(y-1,y)$ （$y$是奇数时）

种安排方案。

考虑化简上面的式子。

当$y$是奇数时，有$C(0,y)=C(y,y), C(1,y)=C(y-1,y), ..., C((y-1)/2,y)=C((y+1)/2,y)$。所以我们有$C(0,y)+C(2,y)+C(4,y)+C(6,y)+...+C(y-1,y)=C(1,y)+C(3,y)+...+C(y,y)$。然而注意到$C(0,y)+C(1,y)+C(2,y)+C(3,y)...+C(y,y)=2^y$（组合数基本性质），所以我们有$C(0,y)+C(2,y)+C(4,y)+C(6,y)+...+C(y-1,y)=2^{y-1}$。

当$y$是偶数时，由于$C(i,j)=C(i,j-1)+C(i-1,j-1)$（组合数基本性质），且$C(y,y)=1=C(y-1,y-1)$。所以我们有$C(0,y)+C(2,y)+C(4,y)+C(6,y)+...+C(y,y)=C(0,y-1)+(C(1,y-1)+C(2,y-1))+(C(3,y-1)+C(4,y-1))+...+(C(y-3,y-1)+C(y-2,y-1)+C(y-1,y-1)=2^{y-1}$。

注意上两式结果是一样的，所以我们可以得到正负号的安排方案共有$2^{y-1}$种。

我们将$x$分解质因数，显然我们可以独立考虑每个质因数。设$x=p^dk$，其中$k$不是$p$的倍数。则我们需要将$d$个$p$分给$y$个数。

我们将问题转换为，“将$d$个相同的球放到$y$个不同的盒子里，每个盒子可以为空，问有几种放法。”。这个问题等价于“将$d+y$个球放到$y$个盒子里，每个盒子里有至少一个”。后者又等价于“在$d+y-1$个位置离选$y-1$个位置”。关于这两个问题为什么等价这里不再证明（经典的球与盒子问题）。所以方案数就是$C(y,d)$。

另外最后一个点就是如何$O(1)$计算$C(i,j)$%$mod$的值。由排列组合公式可知$C(i,j)=j!/(i!(j-i)!)$。所以我们可以预处理出$fac[i]$与$inv[i]$，分别代表$(i!)%mod$的值以及$(i!)$的逆元。则$C(i,j)=fac[j]*inv[i]*inv[j-i]$。

注意到预处理inv数组时可以倒着递推，有公式$inv[i]=inv[i+1]*(i+1)$。

这是因为，$fac[i+1]*inv[i+1]=1  =>  fac[i]*(i+1)*inv[i+1]=1 => fac[i]*((i+1)*inv[i+1])=1$。

于是此题得解，代码很好写，就不放了。

---

## 作者：Arghariza (赞：5)

根据小学套路，前 $y-1$ 个符号可以先忽略，留在第 $y$ 个调整，所以符号共有 $2^{y-1}$ 种。

所以以下只需要考虑正整数的情况，发现由于乘积 $\le 10^6$，最多只能填 $19$ 个非 $1$ 的正整数，于是考虑 $dp$。

令 $dp_{i,j}(i\le19,j\le10^6)$ 表示长度为 $i$ 的不含 $1$ 的正整数列，乘积为 $j$ 的方案数。

显然有：

$$dp_{i,j}=\sum_{k\mid j,k<j}dp_{i-1,k}$$

注意到不好枚举每个数的因数，我们考虑枚举每个因数的倍数，那复杂度就变成了一个调和级数。

考虑把 $1$ 加进去，枚举非 $1$ 项个数 $i$，将 $y-i$ 个 $1$ 插进 $i+1$ 个空里面，和分组同理，方案数为 $\dbinom{y-i+i+1-1}{i+1-1}=\dbinom{y}{i}$。

于是答案就是：

$$2^{y-1}\sum_{i=1}^{\min(y,19)}\dbinom{y}{i}dp_{i,x}$$

复杂度 $O(n\log^2{n}+q\log{n})$。

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

const int maxn = 1e6 + 100;//
const int mod = 1e9 + 7;
int t, x, y, fac[maxn], inv[maxn], ifac[maxn], dp[21][maxn];

int C(int n, int m) { return n < m ? 0 : fac[n] * ifac[m] % mod * ifac[n - m] % mod; }
int ksm(int p, int q) {
	int res = 1;
	while (q) {
		if (q & 1) res = res * p % mod;
		p = p * p % mod;
		q >>= 1;
	}
	return res;
}

signed main() {
	dp[0][1] = fac[0] = ifac[0] = inv[1] = 1;
	for (int i = 0; i <= 19; i++) {
		for (int j = 1; j <= 1e6; j++) {
			if (!dp[i][j]) continue;
			for (int k = j * 2; k <= 1e6; k += j) {
				dp[i + 1][k] = (dp[i + 1][k] + dp[i][j]) % mod;
			}
		}
	}
	for (int i = 1; i <= 1e6; i++) {
		if (i > 1) inv[i] = inv[mod % i] * (mod - mod / i) % mod;
		fac[i] = fac[i - 1] * i % mod, ifac[i] = ifac[i - 1] * inv[i] % mod;
	}
	t = read();
	while (t--) {
		x = read(), y = read();
		int res = 0;
		for (int i = 0; i <= min(y, 19ll); i++) {
			res = (res + dp[i][x] * C(y, i) % mod) % mod;
		}
		write(res * ksm(2, y - 1) % mod);
		puts("");
	}
	return 0;
}
```

---

## 作者：eee_hoho (赞：3)

首先不考虑正负号，那么我们可以把原题看作把$x$的质因子分配到序列的若干个位置中，那么设$x=\prod_ip_i^{k_i}$，则对于每个$p_i$，都有把$k_i$个小球放到$y$个有标号盒子中，并且盒子可以为空，相当于有$k_i+y$个小球放到$y$个有标号盒子中，每个盒子不能为空，于是用插板法解决，方案数为$\begin{pmatrix}k_i+y-1\\y-1\end{pmatrix}$。

然后考虑正负号的问题，我们肯定是每次选择序列中偶数个位置，把他们变为负数，所以有如下式子：

$$\sum_{i=0}^{\lfloor\frac{y}{2}\rfloor}\begin{pmatrix}y\\2i\end{pmatrix}$$

考虑化简这个式子，那么先考虑$y$是奇数，那么有：

$$\begin{aligned}\sum_{i=0}^{\frac{y-1}{2}}\begin{pmatrix}y\\2i\end{pmatrix}\\
=\sum_{i=0}^\frac{y-1}{2}\begin{pmatrix}y\\i\end{pmatrix}\end{aligned}$$

而我们发现$2^y=\sum_{i=0}^y\begin{pmatrix}y\\i\end{pmatrix},\begin{pmatrix}y\\i\end{pmatrix}=\begin{pmatrix}y\\y-i\end{pmatrix}$，那么原式就$=2^{y-1}$。

然后考虑$y$是偶数，那么有：

$$\sum_{i=0}^{\frac{y}{2}}\begin{pmatrix}y\\2i\end{pmatrix}$$

然后如果$\frac{y}{2}$是奇数，那么有：

$$\begin{aligned}2\sum_{i=0}^{\frac{\frac{y}{2}-1}{2}}\begin{pmatrix}y\\2i\end{pmatrix}\\=2\sum_{i=0}^{\frac{y}{2}-1}\begin{pmatrix}y-1\\i\end{pmatrix}\end{aligned}\\=2(2^{y-2})=2^{y-2}$$

而如果$\frac{y}{2}$是偶数，那么有：

$$\begin{aligned}2\sum_{i=0}^{\frac{\frac{y}{2}-2}{2}}\begin{pmatrix}y\\2i\end{pmatrix}\end{aligned}+\begin{pmatrix}y\\\frac{y}{2}\end{pmatrix}\\=2\sum_{i=0}^{\frac{y}{2}-2}\begin{pmatrix}y-1\\i\end{pmatrix}+\begin{pmatrix}y\\\frac{y}{2}\end{pmatrix}\\=2(2^{y-2}-\begin{pmatrix}y-1\\\frac{y}{2}-1\end{pmatrix})+\begin{pmatrix}y-1\\\frac{y}{2}\end{pmatrix}+\begin{pmatrix}y-1\\\frac{y}{2}-1\end{pmatrix}\\=2^{y-1}+\begin{pmatrix}y-1\\\frac{y}{2}\end{pmatrix}-\begin{pmatrix}y-1\\\frac{y}{2}-1\end{pmatrix}\\=2^{y-1}$$

综上所述可以得到$\sum_{i=0}^{\lfloor\frac{y}{2}\rfloor}\begin{pmatrix}y\\2i\end{pmatrix}=2^{y-1}$。

**Code**
``` cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
const int N = 2e6;
const int p = 1e9 + 7;
using namespace std;
int T,x,y,fac[N + 5],inv[N + 5],ans;
int mypow(int a,int x){int s = 1;for (;x;x & 1 ? s = 1ll * s * a % p : 0,a = 1ll * a * a % p,x >>= 1);return s;}
int C(int n,int m)
{
    return 1ll * fac[n] * inv[n - m] % p * inv[m] % p;
}
int main()
{
    scanf("%d",&T);
    fac[0] = 1;
    for (int i = 1;i <= N;i++)
        fac[i] = 1ll * fac[i - 1] * i % p;
    inv[1] = 1;
    for (int i = 2;i <= N;i++)
        inv[i] = 1ll * (p - p / i) * inv[p % i] % p;
    inv[0] = 1;
    for (int i = 1;i <= N;i++)
        inv[i] = 1ll * inv[i - 1] * inv[i] % p;
    while (T--)
    {
        scanf("%d%d",&x,&y);
        ans = mypow(2,y - 1);
        int xx = x;
        for (int i = 2;i * i <= xx;i++)
            if (xx % i == 0)
            {
                int cnt = 0;
                while (xx % i == 0)
                {
                    xx /= i;
                    cnt++;
                }
                ans = 1ll * ans * C(cnt + y - 1,y - 1) % p;
            }
        if (xx != 1)
            ans = 1ll * ans * y % p;
        printf("%d\n",ans);
    }
    return 0;
}
```

---

## 作者：太阳起晚了呢 (赞：2)

## 解

考虑单次询问

首先我们可以简单地去掉允许有负数这个条件

考虑在最后的答案序列中，前 $y-1$ 个元素的乘积为正还是为负，通过最后一项，我们都能将其转化为一个正数，所以前 $y-1$ 个元素的可以任意选择正负，于是我们直接给答案加上一个 $2^{y-1}$ 的系数

对于乘积这样的形式，我们自然可以想到对 $x$ 进行质因数分解，这样可以得到很多个数，那么是不是把这些数随意组合成 $y$ 个元素就可以了呢？显然当这些数有重复的时候，这样组合是会算多了的。 ~~好那么我们考虑一个容斥~~  

根据乘法原理，我们对于每个质因子进行单独考虑，最后把它们的贡献都乘起来就可以了。

对于一个质因子 $a_i^{p_i}$ 我们实际上就是考虑把 $p_i$ 个相同的元素放进 $y$ 个不同的容器当中，容器可以为空。

根据高中数学 ~~（小学奥数）~~ 其组合意义相当于把 $p_i+y$ 个元素分割成 $y$ 个部分，根据隔板法，我们可以得出对于单个质因子其贡献为 $\large \binom{p_i+y-1}{y-1}$ 

所以对于 $\large x=\prod_{i} a_i^{p_i}$ 在不考虑正负性的情况下，成为一个长度为 $y$ 的序列的元素乘积的情况数有

$\large \prod_i \large \binom{p_i+y-1}{y-1}$

那么答案为 $\large ans=\large \prod_i \large \binom{p_i+y-1}{y-1} \times 2^{y-1}$ 

至此本题结束

代码里我放了分解质因数在这个题里的 $3$ 种本质一样常数不同的写法，第二个是不能通过此题的，可以参考。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
const int maxn=2e6+10;
inline int MOD(int a) {return (a<mod)?a:a-a/mod*mod;}
inline int inc(int a,int b) {return (a+=b)>=mod?a-mod:a;}
inline int dec(int a,int b) {return (a-=b)<0?a+mod:a;}
int read()
{
	int x=0,k=1;
	char ch=getchar();
	while(ch<'0' || ch>'9')
	{
		if(ch=='-') k=-1;
		ch=getchar();
	}
	while(ch>='0' && ch<='9')
	{
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x*k;
}
void write(int x)
{
	if(x>9) write(x/10);
	putchar(x%10+'0');
}
int ksm(int x,int y)
{
    int res=1;
    while(y)
    {
        if(y&1) res=MOD(res*x);
        x=MOD(x*x);
        y>>=1;
    }
    return res;
}
int jc[maxn],jcv[maxn];
int p[maxn],tot;
bool vis[maxn];
void getprim()
{
    tot=1;p[1]=2;
    for(int i=3;i<maxn;i++)
    {
        if(!vis[i]) p[++tot]=i;
        for(int j=1;j<=tot && p[j]*i<maxn;j++)
        {
            vis[p[j]*i]=1;
            if(i%p[j]==0) break;
        }
    }
}
int e2[maxn];
void prework()
{
    getprim();
    jc[0]=1;e2[0]=1;
    for(int i=1;i<maxn;i++) jc[i]=MOD(jc[i-1]*i),e2[i]=MOD(e2[i-1]*2);
    jcv[maxn-1]=ksm(jc[maxn-1],mod-2);
    for(int i=maxn-2;i>=1;i--) jcv[i]=MOD(jcv[i+1]*(i+1));
    //for(int i=1;i<=5;i++) cout<<jc[i]*jcv[i]%mod<<' ';
    jcv[0]=1;
}
inline int C(int n,int m)
{
	if(n<=m) return 1;
    return MOD(MOD(jc[n]*jcv[n-m])*jcv[m]);
}
inline void solve()
{
    int x,y;
    x=read();y=read();
    int ans=1;
	int top=1;
	
	for(int i=1;p[i]*p[i]<=x;i++)
	{
		if(x%p[i]) continue;
		int res=0;
        while(x%p[i]==0) res++,x/=p[i];
        //cout<<res<<endl;
        ans=MOD(ans*C(res+y-1,y-1)); 
	}
	
	/*
    while(x!=1 && p[top]*p[top]<=x)
    {
        while(x%p[top]!=0) top++;
        //cout<<top<<endl;
        int res=0;
        while(x%p[top]==0) res++,x/=p[top];
        //cout<<res<<endl;
        ans=MOD(ans*C(res+y-1,y-1)); 
        //cout<<x<<endl;
    }
    */
    /*
    for(int i=2;i*i<=x;i++)
    {
    	if(x%i) continue;
    	int cnt=0;
    	while(x%i==0) x/=i,cnt++;//cout<<cnt<<endl;
    	ans=MOD(ans*C(cnt+y-1,y-1));
	}
	*/
	//cout<<x<<' '<<ans<<endl;
    if(x>1) ans=MOD(ans*y);
    //cout<<ans<<endl;
    ans=MOD(ans*e2[y-1]);
    write(ans);putchar('\n');
}
signed main()
{
	//freopen("1.out","r",stdin);
	//freopen("1.ans","w",stdout);
    prework();
    //cout<<C(5,3)<<endl;
    int Q;Q=read();
    while(Q--) solve();
    return 0;
}
```


---

## 作者：_lxy_ (赞：0)

[博客食用效果更佳](https://www.cnblogs.com/lxy-2022/p/CF893E-Solution.html)
### 题意

略。

### 分析

先考虑不为负数的情况，最后乘上 $2^{y-1}$ 即可。

首先想到 dp，状态很好想，$dp_{i,j}$ 表示长度为 $i$ 的序列乘积为 $j$ 的方案数，转移方程也就呼之欲出了：
$$
dp_{i,j}=\sum\limits_{k|j} dp_{i-1,k}
$$
但是很显然这样时间空间双爆，因此考虑优化：

由于 $y \leq 10^6$，且 $2^{19}<10^6<2^{20}$ 所以这个序列中不为 $1$ 的项最多有 $19$ 项，因此可以先算出来不带 $1$ 的，最后再用排列组合算一下。现在的 $dp_{i,j}$ 表示有 $i$ 项不为 $1$ 的序列乘积为 $j$ 的方案数，这样预处理部分的时空问题就都解决了。

然后处理查询，枚举不含 $1$ 的项数，对于不含 $1$ 的项数 $i$，需要将 $y-i$ 个 $1$ 安排到 $i+1$ 个空里（包括最前和最后），发现用小学奥数的插板法很容易做，设有 $t$ 种安排方法，则有
$$
t={i+1-1 \choose y-i+i+1-1}={i \choose y}
$$
那么最后的答案就是
$$
2^{y-1}\sum\limits_{i=0}^{\min(m,19)} t \cdot dp_{i,x}
$$

### 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
typedef long long ll;
static char buf[1000000],*p1=buf,*p2=buf,obuf[1000000],*p3=obuf;
#define gc() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
#define getchar gc
inline void qread(){}template<class T1,class ...T2>
inline void qread(T1 &a,T2&... b)
{
    register T1 x=0;register bool f=false;char ch=getchar();
    while(ch<'0') f|=(ch=='-'),ch=getchar();
    while(ch>='0') x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
    x=(f?-x:x);a=x;qread(b...);
}
template<class T> T qmax(T x,T y){return x>y?x:y;}
template<class T,class ...Arg> T qmax(T x,T y,Arg ...arg){return qmax(x>y?x:y,arg...);}
template<class T> T qmin(T x,T y){return x<y?x:y;}
template<class T,class ...Arg> T qmin(T x,T y,Arg ...arg){return qmin(x<y?x:y,arg...);}
const int MAXN=1e6+7;
const int mod=1e9+7;
const int _=1e6;
int T,n,m,dp[21][MAXN],cnt,inv[_+7],fac[_+7],ifac[_+7],ans;
int fastpow(int base,int power,int modx)
{
    int res=1;
    while(power)
    {
        if(power&1) res=(res*base)%modx;
        power>>=1;base=(base*base)%modx;
    }return res%modx;
}
inline int C(int x,int y){return fac[x]*ifac[y]%mod*ifac[x-y]%mod;}
signed main()
{
    qread(T);
    int i,j,k;
    inv[0]=inv[1]=fac[0]=ifac[0]=1;
    for(i=1;i<=_;i++) fac[i]=fac[i-1]*i%mod;
    for(i=2;i<=_;i++) inv[i]=inv[mod%i]*(mod-mod/i)%mod;
    for(i=1;i<=_;i++) ifac[i]=ifac[i-1]*inv[i]%mod;dp[0][1]=1;
    for(i=0;i<=19;i++)
        for(j=1;j<=1e6;j++)
        {
            if(!dp[i][j]) continue;
            for(k=j+j;k<=1e6;k+=j) 
                dp[i+1][k]=((long long)dp[i+1][k]+(long long)dp[i][j])%(long long)mod;
        }
    while(T--)
    {
        qread(n,m);ans=0;
        for(i=0;i<=qmin(m,19ll);i++)
            if(dp[i][n]>0) ans=(ans+dp[i][n]*C(m,i))%mod;
        printf("%lld\n",(ans*fastpow(2,m-1,mod))%mod);
    }
    return 0;
}
```

---

## 作者：lgswdn_SA (赞：0)

组合计数板题。

（题解中将 x 和 y 全部写反了，包括代码中的，所以就将就 swap 一下吧）

题目中有两个东西分开计算。第一个是所有数的乘积为 $y$，第二个是正负号。

首先对于所有数的乘积为 $y$，我们考虑对每个数进行素因数分解。设质因数分解 $a_i=\prod_j p_{i,j}^{q_{i,j}}$，$y=\prod_j py_j^{qy_j}$，则题目条件等价于

$$
\sum_{i=1}^{x} q_{i,j}=qy_j
$$

考虑到每个素因数之间是独立的，我们分开算然后再乘起来。上面一个式子是一个很典型的整数拆分的组合计数模型，方案数为 

$$
\prod_{j} \binom{qy_j+x-1}{x-1}
$$

其次考虑正负号。我们也就是要在 $x$ 个位置中选择偶数个位置让其变成负数，方案数为

$$
\sum_{k=0}^{[\frac{x}{2}]} \binom{x}{2k}
$$
这是一个很经典的变换。我们将其复制一份后，然后我们对复制的一份运用对称恒等式，发现这两个的和即 $\sum_{0\le i\le x} \binom{x}{i}=2^x$，所以原式的答案即这个式子的答案的一半

$$
2^{x-1}
$$

所以答案为

$$
ans=2^{x-1}\prod_{j} \binom{qy_j+x-1}{x-1}
$$

```cpp
#define int long long
#define rep(i,a,b) for(register int i=(a);i<=(b);i++)
#define per(i,a,b) for(register int i=(a);i>=(b);i--)
using namespace std;
const int N=2e6+9,mod=1e9+7;

inline int read() {
    register int x=0, f=1; register char c=getchar();
    while(c<'0'||c>'9') {if(c=='-') f=-1; c=getchar();}
    while(c>='0'&&c<='9') {x=(x<<3)+(x<<1)+c-48,c=getchar();}
    return x*f;
}

int T,x,y,fac[N],inv[N],ifac[N];
void pre(int n=2000000) {
    inv[0]=inv[1]=fac[0]=ifac[0]=1;
    rep(i,1,n) fac[i]=fac[i-1]*i%mod;
    rep(i,2,n) inv[i]=inv[mod%i]*(mod-mod/i)%mod;
    rep(i,1,n) ifac[i]=ifac[i-1]*inv[i]%mod;
}
int C(int x,int y) {
    if(x<0||y<0||x<y) return 0;
    else return fac[x]*ifac[y]%mod*ifac[x-y]%mod;
}
int ksm(int x,int y) {
	if(y==0) return 1;
	else return ksm(x*x%mod,y/2)*(y%2?x:1)%mod;
}

signed main() {
	pre();
	int T=read();
	while(T--) {
		int y=read(), x=read(), ans=ksm(2,x-1);
		for(int i=2;i*i<=y;i++) {
			if(y%i) continue;
			int cnt=0;
			while(y%i==0) y/=i, cnt++;
			ans=ans*C(cnt+x-1,x-1)%mod;
		}
		if(y!=1) ans=ans*x%mod;
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

