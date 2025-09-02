# Encryption (medium)

## 题目描述

Heidi has now broken the first level of encryption of the Death Star plans, and is staring at the screen presenting her with the description of the next code she has to enter. It looks surprisingly similar to the first one – seems like the Empire engineers were quite lazy...

Heidi is once again given a sequence $ A $ , but now she is also given two integers $ k $ and $ p $ . She needs to find out what the encryption key $ S $ is.

Let $ X $ be a sequence of integers, and $ p $ a positive integer. We define the score of $ X $ to be the sum of the elements of $ X $ modulo $ p $ .

Heidi is given a sequence $ A $ that consists of $ N $ integers, and also given integers $ k $ and $ p $ . Her goal is to split $ A $ into $ k $ part such that:

- Each part contains at least $ 1 $ element of $ A $ , and each part consists of contiguous elements of $ A $ .
- No two parts overlap.
- The total sum $ S $ of the scores of those parts is maximized.

Output the sum $ S $ – the encryption code.

## 说明/提示

In the first example, if the input sequence is split as $ (3,4) $ , $ (7) $ , $ (2) $ , the total score would be ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF958C2/d4a5357e9a4720ebdcbfc92aa797cf51b7b836c8.png). It is easy to see that this score is maximum.

In the second example, one possible way to obtain score $ 37 $ is to make the following split: $ (16,3,24) $ , $ (13,9) $ , $ (8) $ , $ (7) $ , $ (5,12,12) $ .

## 样例 #1

### 输入

```
4 3 10
3 4 7 2
```

### 输出

```
16
```

## 样例 #2

### 输入

```
10 5 12
16 3 24 13 9 8 7 5 12 12
```

### 输出

```
37
```

# 题解

## 作者：Acfboy (赞：6)

很容易想出一个 $O(n^2k)$ 的 dp。$f_{i, j}$ 表示 $i$ 个数分成 $j$ 组的最大价值。

$$
f_{i,j} = \max\{f_{k,j-1} + sum_i - sum_k\}
$$

观察一下数据范围可以发现 $p$ 很小，所以 $sum_k$ 的取值是很少的，那么换一种思路，别枚举 $k$ 以取 $f_{k, j-1}$ 了，毕竟 $sum_k$ 和 $f_{k, j-1}$ 是相对应的。只需枚举 $sum_k$ 的值，把 $sum_k$ 对应的最大的 $f_{k, j-1}$ 拿来转移就可以了。

时间复杂度 $O(nkp)$。

```cpp
#include <cstdio>
#include <algorithm>
const int N = 20005, M = 55, INF = 0x3f3f3f3f;
int n, K, p, sum[N], f[M][N], t[105];
int main() {
	scanf("%d%d%d", &n, &K, &p);
	for (int i = 1; i <= n; i++) 
		scanf("%d", &sum[i]), 
		sum[i] = (sum[i] + sum[i-1]) % p;
	for (int i = 1; i <= n; i++) f[0][i] = -INF;
	for (int i = 1; i <= K; i++) {
		for (int j = 0; j < p; j++) t[j] = -INF;
		if (i == 1) t[0] = 0; 
		for (int j = 1; j <= n; j++) {
			f[i][j] = -INF;
			for (int k = 0; k < p; k++)
				f[i][j] = std::max(f[i][j], t[k] + (sum[j] - k + p) % p);
			t[sum[j]] = std::max(t[sum[j]], f[i-1][j]);
		}
	}
	printf("%d", f[K][n]);
	return 0;
}
```

---

## 作者：Tx_Lcy (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/CF958C2)

$\verb!CF!$ 的机子好快，居然让我的暴力过掉了。
## 思路
显然我们有一个 $\verb!DP!$ 的思路，设 $f_{i,j}$ 表示前 $i$ 个数，分成 $j$ 段的最大价值，然后转移就是 $f_{i,j}=\max{f_{k,j-1}+\sum_{l=k+1}^n a_l}$，后面的 $\sum$ 可以前缀和优化掉，但是前面的需要枚举，时间复杂度 $O(n^2k)$。

但是，这个枚举可以加一个小优化，因为 $f_{i,j}$ 的状态全都是从 $f_{k,j-1}$ 转移过来的，既然它们分的段数相同，所以 $f$ 数组必然是单调不降的，当我们枚举到一个 $k$，发现 $f_{k,j-1}+p-1 \le f_{i,j}$ 时，我们已经不需要往下枚举了。

加上这个优化后暴力跑的飞快，最慢的点只需要 $\verb!93ms!$。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int const N=2e4+10;
int const M=50+5;
int f[N][M],sum[N],a[N];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int n,k,p;cin>>n>>k>>p;
	for (int i=1;i<=n;++i) cin>>a[i],sum[i]=sum[i-1]+a[i];
	for (int i=1;i<=n;++i){
	    f[i][1]=sum[i]%p;
	    for (int j=2;j<=min(i,k);++j)
			for (int k=i-1;k>=1;--k){
			    if (f[k][j-1]+p-1<=f[i][j]) break;//剪枝
	            f[i][j]=max(f[i][j],f[k][j-1]+(sum[i]-sum[k])%p);
			}
	}
	cout<<f[n][k]<<'\n';
	return 0;
}
```


---

## 作者：Hoks (赞：2)

## 前言
比较有意思的 dp 题。

摘自 [杂题选做](https://www.luogu.com.cn/training/499842#information)。
## 思路分析
首先考虑下最朴素的思路，设计 $f_{i,j}$ 表示前 $i$ 个数分成 $j$ 段的最大值，并处理出前缀和 $s$。

那么转移直接考虑枚举断点 $k$，方程式即为 
$$f_{i,j}=\max(f_{k,j-1}+(s_i-s_k)\bmod p)$$
这样的复杂度是 $O(n^2k)$ 的，考虑优化。

发现 $p$ 不是很大，考虑把其中的一个 $n$ 降为 $p$ 得到 $O(nkp)$。

不难发现如果 $s_x\equiv s_k\pmod p$ 的话，$s_i-s_x\equiv s_i-s_k\pmod p$。

那么从 $x$ 还是 $k$ 转移就取决于 $f_{x,j-1}$ 和 $f_{k,j-1}$ 的大小了，显然是从更大的值转移过来更优。

考虑枚举 $s_k$，对于每一种值存储一个最大的 $f_{k,j-1}$ 转移即可。
## 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e4+10,M=110,mod=1e9+7,INF=0x3f3f3f3f3f3f3f3f,lim=20;
int n,k,p,s[N],f[N][M],g[M];
namespace Fast_IO
{
    static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
    #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
    inline int read()
    {
        int x(0),t(1);char fc(getchar());
        while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
        return x*t;
    }
    inline void flush(){fwrite(out,1,length,stdout);length=0;}
    inline void put(char c){if(length==9999999) flush();out[length++]=c;}
    inline void put(string s){for(char c:s) put(c);}
    inline void print(int x)
    {
        if(x<0) put('-'),x=-x;
        if(x>9) print(x/10);
        put(x%10+'0');
    }
    inline bool chk(char c) { return !(c>='0'&&c<='1'); }
    inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
    inline void rd(char s[],int&n)
    {
        s[++n]=getchar();
        while(chk(s[n])) s[n]=getchar();
        while(ck(s[n])) s[++n]=getchar();
        n--;
    }
}
using namespace Fast_IO;
signed main()
{
    n=read(),k=read(),p=read();memset(f,-0x3f,sizeof f);
    for(int i=1;i<=n;i++) s[i]=(s[i-1]+read())%p;
    for(int j=1;j<=k;j++)
    {
        memset(g,-0x3f,sizeof g);if(j==1) g[0]=0;
        for(int i=1;i<=n;i++)
        {
            for(int k=0;k<p;k++) f[i][j]=max(f[i][j],g[k]+(s[i]-k+p)%p);
            g[s[i]]=max(g[s[i]],f[i][j-1]);
        }
    }print(f[n][k]);
    genshin:;flush();return 0;
}
```

---

## 作者：1234567890sjx (赞：2)

设 $f_{i,j}$ 表示当前看了前 $i$ 个数，当前划分了 $j$ 段，最大的价值是多少。

令 $g_i$ 表示 $(\sum_{j=1}^i a_j)\bmod p$ 的值。显然可以 $O(n)$ 递推。

显然 $f_{i,j}$ 可以从 $f_{k,j-1}$ 转移过来。其中 $1\le k<i$。

即 $f_{i,j}=\max_{k=1}^{i-1}(f_{k,j-1}-g_k)+g_i$。

时间复杂度 $O(n^2\times k)$。

考虑对于每一个 $j$ 都建立一个线段树。然后发现这个东西由于在第 $j-1$ 个树状数组上是一段连续的区间，所以直接查询即可。

时间复杂度 $O(kn\log n)$。

---

## 作者：Xiphi (赞：2)

### CF958C2

本题解将介绍三种方法，以供选择（第二种能过 hard vesion）。

先介绍暴力 dp 的做法，大概值一道黄题吧（？。设 $dp_{i,j}$ 表示选到 $j$ 时分 $i$ 段的最大值可以是多少。那么 $dp_{i,j}=\max_{k=1}^{k=i} (dp_{j-1,k}+sum(a_{k+1},\dots,a_i) \mod p)$。可写暴力如下：

```cpp
    for(int i=1;i<=n;++i){
        for(int j=1;j<=min(i,k);++j){
            for(int k=i-1;k>=1;--k){
                if(f[j-1][k]+p-1<=f[j][i]) break;
                if(j==1) f[j][i]=sum[i]%p;
                f[j][i]=max(f[j-1][k]+sum[i]-sum[k-1],f[j][i]);
                ans=max(f[j][i],ans);
            }
        }
    }
    cout<<ans;
```

在代码中，请注意 $i,j$ 表示的数与前面的不同。

#### sol. 1

考虑加入优化，发现对于固定的 $i,j$，$dp_{k,j-1}$ 不然单调不降。所以可以加入优化：当 $dp_{k,j-1}+p-1\le dp_{i,j}$ 时，break 掉。复杂度玄学。

```cpp
    cin>>n>>k>>p;
    for(int i=1;i<=n;++i) cin>>a[i],sum[i]=sum[i-1]+a[i];
    for(int i=1;i<=n;++i){
        f[1][i]=a[i]%p;
        for(int j=2;j<=min(i,k);++j){
            for(int k=i-1;k>=1;--k){
                if(f[j-1][k]+p-1<=f[j][i]) break;
                f[j][i]=max(f[j-1][k]+sum[i]-sum[k-1],f[j][i]);
                ans=max(f[j][i],ans);
            }
        }
    }
    cout<<ans;
```

#### sol.2

非常神的做法（针对 C3)。出题人 Orz。考虑继续优化 $O(n^2\times k)$ 的做法。首先观察 $dp$ 数组的性质，发现对于 $dp_{i,j}$，其一定是由 $dp_{1,l-1},dp_{2,l-1},\dots,dp_{i-1,l-1}$ 转移而来的，用 $f_{i,j}$ 记录选到 $i$ 且段数固定时，最小的 $dp_{k,j}$ 的 $k$ 的多少即可，每次从那里转移。复杂度 $O(nk)$。

#### sol.3

参考了官方题解。

设 $f_{i,j,k}$ 表示：

$f_{i,j,k} = \max_{sum(a_{j+1},\dots,a_i) \mod p=k} dp_{k - 1, j} + sum(a_{j+1},\dots,a_i)$。

那么，$dp_{i,j}$ 的计算公式如下 $dp(i, j) = \max_ m f (i,j,m)$。 

对于所有 $m ≠ 0$，$f (k, i, m + a_i \mod p) = f (k, i - 1, m) - m + (m + a_i \mod p)$。当 m 等于 $0$ 时，我们还必须考虑第 $k$ 组仅由 $a_i$ 构成的情况。因此 $f(k, i, a_i)=\min(f (k, i - 1, 0) + a_i, dp(k - 1, i - 1) + a_i)$. 这种方法的运行时间为 $O(nkp)$，在时间限制内通过。

---

## 作者：Charlie_ljk (赞：1)

先写出 $O(n^2k)$ 的转移方程：

$$f_{i,k}=\max\limits_{j=k-1}^{i-1}\{f_{j,k-1}+(sum_i-sum_j)\bmod p\}$$

发现对于每个 $f_{i,*}$ 其 $\bmod p$ 的值恒等于 $sum_i \bmod p$，那么对于两个转移点 $x,y$，有：

$$f_{x,k-1}+(sum_i-sum_x)\bmod p\equiv f_{y,k-1}+(sum_i-sum_y)\bmod p\pmod p$$

若 $f_{x,k-1}<f_{y,k-1}$，因为 $(sum_i-sum_j)\bmod p<p$，所以一定有 $f_{x,k-1}+(sum_i-sum_x)\bmod p\le f_{y,k-1}+(sum_i-sum_y)\bmod p$。

所以直接记录最优策略即可，复杂度 $O(nk)$。

代码如下：

```cpp
#include<bits/stdc++.h>
#define int long long 
#define endl '\n'
#define sort stable_sort
using namespace std;
const int N=5e5+10;
template<typename Tp> inline void read(Tp&x)
{
    x=0;register bool z=true;
    register char c=getchar();
    for(;c<'0'||c>'9';c=getchar()) if(c=='-') z=0;
    for(;'0'<=c&&c<='9';c=getchar()) x=(x<<1)+(x<<3)+(c^48);
    x=(z?x:~x+1);
}
void wt(int x){if(x>9)wt(x/10);putchar((x%10)+'0');}
void write(int x){if(x<0)putchar('-'),x=~x+1;wt(x);}
int n,m,p,f[N][2],sum[N],lastx[N],lasty[N];
signed main()
{
    read(n),read(m),read(p);
    for(int i=1,a;i<=n;i++)
        read(a),sum[i]=sum[i-1]+a;
    for(int j=1;j<=m;j++)
    {
        int maxx=f[j-1][(j-1)&1],ans=j-1;
        for(int i=j;i<=n;i++)
        {
            f[i][j&1]=maxx+(sum[i]-sum[ans])%p;
            if(f[i][(j-1)&1]>maxx) 
            {
                maxx=f[i][(j-1)&1];
                ans=i;
            }
        }
    }
    write(f[n][m&1]);
}
```

---

## 作者：Coros_Trusds (赞：0)

# 题目大意

有一个包含 $n$ 个正整数的数列，将这个数列分成 $m$ 个非空段，每段的价值为这段的所有数总和 $\bmod~p$，你需要使 $k$ 段价值总和最大，请求出这个最大值。

# 题目分析

先有 $\mathcal{O(n^2m)}$ 做法：

令 $dp[i][j]$ 表示前 $i$ 个数分 $j$ 组的最大值。

有 $dp[i][j]=\max\{dp[k][j-1]+(sum[i]-sum[k])\bmod p\}$。

-----

考虑怎么优化，注意到我们 $dp[i][j]$ 的最大值的求解是从 $\max\{dp[k][j-1]\}$ 里来的，但是单纯记录最大值还不行，我们还要记录位置（$sum[k]$），然后就做完了。

正确性证明：

首先 $sum$ 数组一定严格单调递增，因为 $\forall i\in [1,n],a[i]\in[1,10^6]$。其次我们可以发现 $dp[i][j]\equiv sum[i](\bmod p)$，因为 $(a+b)\bmod p=a\bmod p+b\bmod p$。

所以找到两个 $x,y$，我们要做的其实就是求出 $dp[x][j-1],dp[y][j-1]$ 的最大值，设 $w[x]=(sum[i]-sum[x])\bmod p,w[y]=(sum[i]-sum[y])\bmod p$。

又因为 $dp[i][j]\equiv dp[i][j](\bmod p)$，

故 $dp[x][j-1]+w[x]\equiv dp[y][j-1]+w[y](\bmod p)$。

不妨设 $dp[x][j-1]\lt dp[y][j-1]$，因为 $w[x],w[y]\lt p$，所以 $dp[x][j-1]+w[x]\lt dp[y][j-1]+w[y]$。

所以我们有了思路：对于每个 $j$，记录最大的 $dp[k][j]$ 的位置 $k$，转移时就能 $\mathcal{O(1)}$ 转移了。

总时间复杂度 $\mathcal{O(nm)}$。

# 代码

```cpp
// Problem: CF958C2 Encryption (medium)
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF958C2
// Memory Limit: 500 MB
// Time Limit: 3000 ms
// Date:2022-05-21 15:33
// 
// Powered by CP Editor (https://cpeditor.org)

#include <iostream>
#include <cstdio>
#include <climits>//need "INT_MAX","INT_MIN"
#include <cstring>//need "memset"
#include <numeric>
#include <algorithm>
#define enter putchar(10)
#define debug(c,que) std::cerr << #c << " = " << c << que
#define cek(c) puts(c)
#define blow(arr,st,ed,w) for(register int i = (st);i <= (ed); ++ i) std::cout << arr[i] << w;
#define speed_up() std::ios::sync_with_stdio(false),std::cin.tie(0),std::cout.tie(0)
#define mst(a,k) memset(a,k,sizeof(a))
#define stop return(0)
const int mod = 1e9 + 7;
inline int MOD(int x) {
	if(x < 0) x += mod;
	return x % mod;
}
namespace Newstd {
	inline int read() {
		int ret = 0,f = 0;char ch = getchar();
		while (!isdigit(ch)) {
			if(ch == '-') f = 1;
			ch = getchar();
		}
		while (isdigit(ch)) {
			ret = (ret << 3) + (ret << 1) + ch - 48;
			ch = getchar();
		}
		return f ? -ret : ret;
	}
	inline void write(int x) {
		if(x < 0) {
			putchar('-');
			x = -x;
		}
		if(x > 9) write(x / 10);
		putchar(x % 10 + '0');
	}
}
using namespace Newstd;

const int N = 2e4 + 5,M = 55;
struct Rem {
	int Max,pos;
} ;
int a[N],sum[N],dp[N][M],g[2][M];
//dp[i][j]:前 i 个数分成 j 组的最大和
int n,m,p;
int main(void) {
	n = read(),m = read(),p = read();
	for (register int i = 1;i <= n; ++ i) {
		a[i] = read();
		sum[i] = (sum[i - 1] + a[i]) % p;
	}
	for (register int i = 1;i <= n; ++ i) dp[i][1] = sum[i];
	for (register int i = 1;i <= n; ++ i) {
		for (register int j = 2;j <= m; ++ j) {
			dp[i][j] = std::max(dp[i][j],dp[g[i & 1 ^ 1][j - 1]][j - 1] + ((sum[i] - sum[g[i & 1 ^ 1][j - 1]]) % p + p) % p);
		}
		for (register int j = 0;j <= m; ++ j) {
			g[i & 1][j] = g[i & 1 ^ 1][j];
			if (dp[i][j] > dp[g[i & 1][j]][j]) {
				g[i & 1][j] = i;
			}
		}
	}
	printf("%d\n",dp[n][m]);
	
	return 0;
}
```

---

