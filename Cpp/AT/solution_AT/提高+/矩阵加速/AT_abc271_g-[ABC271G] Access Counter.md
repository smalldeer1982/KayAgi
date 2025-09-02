# [ABC271G] Access Counter

## 题目描述

【题目翻译】

给定 $24$ 个时间点，每个时间点有可能有两种指令

如果指令是 `T`，则高桥有 $x\%$ 的概率登录洛谷。

如果指令是 `A`，则青木有 $y\%$ 的概率登录洛谷。

操作是依次进行的。求洛谷第 $n$ 次被登录是由青木操作的概率。

答案对 $998244353$ 取模。

## 样例 #1

### 输入

```
1 50 50
ATATATATATATATATATATATAT```

### 输出

```
665496236```

## 样例 #2

### 输入

```
271 95 1
TTTTTTTTTTTTTTTTTTTTTTTT```

### 输出

```
0```

## 样例 #3

### 输入

```
10000000000000000 62 20
ATAATTATATTTAAAATATTATAT```

### 输出

```
744124544```

# 题解

## 作者：Tsawke (赞：4)

#  [[ABC271G] Access Counter](https://www.luogu.com.cn/problem/AT_abc271_g) Solution

[TOC]

## [更好的阅读体验戳此进入](http://blog.tsawke.com?t=ABC271G)

## 题面

每天存在 $ 24 $ 个时间点，两人要访问一个网站，给定一个 `A` 和 `T` 组成的长度为 $ 24 $ 的字符串，若为 `T` 则 Taka 有 $ X\% $ 的概率成功访问，若为 `A` 则 Aoki 有 $ Y\% $ 的概率成功访问，求该网站第 $ n $ 次被访问时是被 Aoki 访问的概率，对 $ 998244353 $ 取模。

## Solution

首先看一眼这个题面与 $ n $ 的范围，就不难联想到矩阵快速幂，但是这题的难点我认为主要还是在状态的设计与转移上。

一个显而易见但较为重要的性质，即两次访问之间间隔的天数是易于统计的，重要的在于两次访问的时间点 $ i, j $ 之间的位置关系。

令对应时间点的访问成功概率为 $ p_i $，令一天中未发生任何访问的概率为 $ P = \prod_{i = 1}^{24}(1 - p_i) $，考虑预处理 $ dp(i, j) $ 表示上次在 $ i $ 访问本次在 $ j $ 访问的概率，如果两者之间的距离不超过一天，显然可以预处理，令 $ R $ 为从 $ i + 1 $ 到 $ j - 1 $ 的所有 $ 1 - p $ 之积，则转移显然，即：
$$
dp(i, j) = \sum_{k = 0}^{+\infty}P^k \times R \times p_j
$$
显然和式为等比数列求和，且由题意可知公比 $ P \lt 0 $，则继续推式子可以得到：
$$
\lim\limits_{n \to +\infty}\dfrac{1 - P^n}{1 - P} \times R \times p_j
$$
显然 $ n \to +\infty $ 时 $ P^n \to 0 $，则转化为：
$$
\dfrac{R \times p_j}{1 - P}
$$
于是我们完成了 $ dp(i, j) $ 的预处理。

---

令 $ f(i, j) $ 表示第 $ i $ 次访问发生在 $ j $ 时刻的概率，有：
$$
f(i, j) = \sum_{k = 1}^{24} f(i - 1, k) \times dp(k, j)
$$
按照我们之前的想法挂到矩阵上：
$$
\begin{bmatrix}
f(i, 1) & f(i, 2) & \cdots & f(i, 24) \\
\end{bmatrix}
=
\begin{bmatrix}
f(i - 1, 1) & f(i - 1, 2) & \cdots & f(i - 1, 24) \\
\end{bmatrix}
\begin{bmatrix}
dp(1, 1) & dp(1, 2) & \cdots & dp(1, 24) \\
dp(2, 1) & dp(2, 2) & \cdots & dp(2, 24) \\
\vdots & \vdots & \ddots & \vdots \\
dp(24, 1) & dp(24, 2) & \cdots & dp(24, 24)
\end{bmatrix}
$$
显然 $ f(0, i) = [i = 24] $，初始时我们默认其最终选择的只能是 $ 24 $，等价于从 $ 0 $ 开始，这样不会对我们的结果造成影响，那么最终形式：
$$
\begin{bmatrix}
f(n, 1) & f(n, 2) & \cdots & f(n, 24) \\
\end{bmatrix}
=
\begin{bmatrix}
0 & 0 & \cdots & 1 \\
\end{bmatrix}
\begin{bmatrix}
dp(1, 1) & dp(1, 2) & \cdots & dp(1, 24) \\
dp(2, 1) & dp(2, 2) & \cdots & dp(2, 24) \\
\vdots & \vdots & \ddots & \vdots \\
dp(24, 1) & dp(24, 2) & \cdots & dp(24, 24)
\end{bmatrix}^n
$$
答案统计一下所有 $ i $ 处是 Aoki 的 $ f(n, i) $ 之和即可，可以矩阵快速幂优化，令 $ d = 24 $，则复杂度 $ O(d^3 \log n) $，可以通过。

## Code

```cpp
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

#define PI M_PI
#define E M_E
#define npt nullptr
#define SON i->to
#define OPNEW void* operator new(size_t)
#define ROPNEW void* Edge::operator new(size_t){static Edge* P = ed; return P++;}
#define ROPNEW_NODE void* Node::operator new(size_t){static Node* P = nd; return P++;}

using namespace std;

mt19937 rnd(random_device{}());
int rndd(int l, int r){return rnd() % (r - l + 1) + l;}
bool rnddd(int x){return rndd(1, 100) <= x;}

typedef unsigned int uint;
typedef unsigned long long unll;
typedef long long ll;
typedef long double ld;

#define MOD (998244353ll)

template < typename T = int >
inline T read(void);

ll N;
ll Taka, Aoki;
ll p[30];
ll P(1);
ll ansv(0);
ll inv100;
ll dp[30][30];
bitset < 30 > belong;

ll qpow(ll a, ll b){
    ll ret(1), mul(a);
    while(b){
        if(b & 1)ret = ret * mul % MOD;
        b >>= 1;
        mul = mul * mul % MOD;
    }return ret;
}

class Matrix{
private:
    int siz;
    ll v[30][30];
public:
    Matrix(int len = 24, int pat = 0){
        siz = len;
        for(int i = 0; i < siz; ++i)
            for(int j = 0; j < siz; ++j)
                v[i][j] = 0;
        switch(pat){
            case 1:{
                for(int i = 0; i < siz; ++i)v[i][i] = 1;
                break;
            }
            case 2:{
                v[0][siz - 1] = 1;
                break;
            }
            case 3:{
                for(int i = 1; i <= siz; ++i)
                    for(int j = 1; j <= siz; ++j)
                        v[i - 1][j - 1] = dp[i][j];
                break;
            }
            default: break;
        }
    }
    friend Matrix operator * (const Matrix &a, const Matrix &b){
        Matrix ret(24);
        for(int i = 0; i < 24; ++i)
            for(int j = 0; j < 24; ++j)
                for(int k = 0; k < 24; ++k)
                    (ret.v[i][j] += a.v[i][k] * b.v[k][j] % MOD) %= MOD;
        return ret;
    }
    void SetAns(void){
        for(int i = 0; i < 24; ++i)
            if(belong[i + 1])(ansv += v[0][i]) %= MOD;
    }
    void Print(void){
        printf("##########\n");
        for(int i = 0; i < siz; ++i)
            for(int j = 0; j < siz; ++j)
                printf("%lld%c", v[i][j], j == siz - 1 ? '\n' : ' ');
        printf("##########\n");
    }
}ans(24, 2);

Matrix qpow(Matrix a, ll b){
    Matrix ret(24, 1), mul(a);
    while(b){
        if(b & 1)ret = ret * mul;
        b >>= 1;
        mul = mul * mul;
    }return ret;
}

int main(){
    inv100 = qpow(100, MOD - 2);
    N = read < ll >(), Taka = read(), Aoki = read();
    for(int i = 1; i <= 24; ++i){
        char c = getchar(); while(!isalpha(c))c = getchar();
        p[i] = c == 'T' ? Taka : Aoki, belong[i] = c == 'T' ? false : true;
        (P *= (100 - p[i]) * inv100 % MOD) %= MOD;
    }
    for(int i = 1; i <= 24; ++i){
        for(int j = 1; j <= 24; ++j){
            ll R(1);
            if(i < j)for(int k = i + 1; k <= j - 1; ++k)(R *= (100 - p[k]) * inv100 % MOD) %= MOD;
            else{
                for(int k = i + 1; k <= 24; ++k)(R *= (100 - p[k]) * inv100 % MOD) %= MOD;
                for(int k = 1; k <= j - 1; ++k)(R *= (100 - p[k]) * inv100 % MOD) %= MOD;
            }
            dp[i][j] = R * (p[j] * inv100 % MOD) % MOD * qpow((1 - P + MOD) % MOD, MOD - 2) % MOD;
        }
    }
    Matrix base(24, 3);
    (ans * qpow(base, N)).SetAns();
    printf("%lld\n", ansv);
    fprintf(stderr, "Time: %.6lf\n", (double)clock() / CLOCKS_PER_SEC);
    return 0;
}

template < typename T >
inline T read(void){
    T ret(0);
    int flag(1);
    char c = getchar();
    while(c != '-' && !isdigit(c))c = getchar();
    if(c == '-')flag = -1, c = getchar();
    while(isdigit(c)){
        ret *= 10;
        ret += int(c - '0');
        c = getchar();
    }
    ret *= flag;
    return ret;
}
```

## UPD

update-2023_02_09 初稿

---

## 作者：翼德天尊 (赞：3)

一眼矩阵加速，但是补题的时候对于转移方程的构造想了好久。

注意到我们转移的时候其实只关注两点：当前所在的小时，以及当前 access 了几次。

所以我们不妨设 $dp_{i,j}$ 表示当前 access 了 $i$ 次，且最后一次 access 是在第 $j$ 个小时进行的。而 $i$ 这一维我们是要矩阵加速转移的，所以我们只需要考虑 $j$ 这一维怎么转移。也就是，如果从第 $i$ 个小时 access 之后，一直不 access，直到不知道多少天之后又在第 $j$ 个小时 access 了的概率是多少。

我们不妨设 $p_i$ 为第 $i$ 个小时 access 的概率，$s_{i,j}$ 为从第 $i$ 个小时转移到第 $j$ 个小时的概率，$n$ 为过去的整数天数，$sum_{i,j}$ 为从第 $i$ 个小时到第 $j$ 个小时都不 access 的概率。则有方程：
$$
s_{i,j}=\sum_{n=0}^{+\infty}sum_{i+1,j-1}p_i\times sum_{1,24}^n
$$
于是就是一个等比数列求和的形式，转化一下就是：
$$
s_{i,j}=\dfrac{sum_{i+1,j-1}p_i}{1-sum_{1,n}}
$$
于是把它扔进矩阵，套路矩阵加速即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int long long
const int N=24;
const int mod=998244353;
const int hun=828542813;
int n,q,p,s=1;
char in[N+1];
struct node{
	int a[N][N];
	node(){
		memset(a,0,sizeof(a));
	}
	void init(){
		for (int i=0;i<N;i++)
			a[i][i]=1;
	}
}S,Z;
node operator *(const node&x,const node&y){
	node z;
	for (int k=0;k<N;k++)
		for (int i=0;i<N;i++)
			for (int j=0;j<N;j++)
				z.a[i][j]=(z.a[i][j]+x.a[i][k]*y.a[k][j]%mod)%mod;
	return z;
}
ll read(){
	ll w=0,f=1;
	char c=getchar();
	while (c>'9'||c<'0'){
		if (c=='-') f=-1;
		c=getchar();
	}
	while (c>='0'&&c<='9'){
		w=(w<<3)+(w<<1)+(c^48);
		c=getchar();
	}
	return w*f;
}
ll ksm(ll x,ll y){
	ll ans=1;
	while (y){
		if (y&1) ans=ans*x%mod;
		x=x*x%mod;
		y>>=1;
	}
	return ans;
}
ll inv(ll x){
	x=(x%mod+mod)%mod;
	return ksm(x,mod-2);
}
ll chan(int pos,bool flag){
	if (!flag){
		if (in[pos]=='T') return q*hun%mod;
		return p*hun%mod;		
	}else{
		if (in[pos]=='T') return (100-q)*hun%mod;
		return (100-p)*hun%mod;
	}
}
node ksm_(node x,int y){
	node ans;
	ans.init();
	while (y){
		if (y&1) ans=ans*x;
		x=x*x;
		y>>=1;
	}
	return ans;
}
signed main(){
	n=read(),q=read(),p=read();
	scanf("%s",in);
	for (int i=0;i<N;i++){
		s=s*chan(i,1)%mod;
	}
	for (int i=0;i<N;i++){
		for (int j=0;j<N;j++){
			if (i<j){
				int now=1;
				for (int k=i+1;k<j;k++) now=now*chan(k,1)%mod;
				now=now*chan(j,0)%mod;
				Z.a[i][j]=now*inv(1-s)%mod;
			}else{
				int now=1;
				for (int k=i+1;k<N;k++) now=now*chan(k,1)%mod;
				for (int k=0;k<j;k++) now=now*chan(k,1)%mod;
				now=now*chan(j,0)%mod;
				Z.a[i][j]=now*inv(1-s)%mod;
			}
		}
	}
	for (int i=0;i<N;i++)
		S.a[0][i]=Z.a[N-1][i];
	Z=ksm_(Z,n-1);
	S=S*Z;
	int ans=0;
	for (int i=0;i<N;i++){
		if (in[i]=='A') ans=(ans+S.a[0][i])%mod;
	}
	cout<<ans<<'\n';
	return 0;
}
```

---

## 作者：中缀自动机 (赞：0)

[题面](https://www.luogu.com.cn/problem/AT_abc271_g)

考虑记 $f_{i,j}$ 表示当前已经有 $i$ 次访问，且第 $i$ 次访问存在于第 $j$ 个小时。

那么下一次访问在第 $k$ 个小时的概率是什么呢？

枚举中间隔的天数，假设从第 $j$ 个小时第一次到第 $k$ 个小时中间经过的小时都没有访问网站的概率为 $P_{j,k}$，一天没有发生访问的概率为 $P$，那么我们的转移系数为：

$$s_{j,k}=\sum_{i=0}^{\infty }P^kP_{j,k}=\frac{P_{j,k}}{1-P} $$

接下来把转移写成矩阵，做矩阵快速幂即可。

令 $m=24$，则时间复杂度为 $O({m}^3\log{n})$。

---

