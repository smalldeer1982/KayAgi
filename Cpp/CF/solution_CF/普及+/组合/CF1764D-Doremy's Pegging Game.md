# Doremy's Pegging Game

## 题目描述

Doremy has $ n+1 $ pegs. There are $ n $ red pegs arranged as vertices of a regular $ n $ -sided polygon, numbered from $ 1 $ to $ n $ in anti-clockwise order. There is also a blue peg of slightly smaller diameter in the middle of the polygon. A rubber band is stretched around the red pegs.

Doremy is very bored today and has decided to play a game. Initially, she has an empty array $ a $ . While the rubber band does not touch the blue peg, she will:

1. choose $ i $ ( $ 1 \leq i \leq n $ ) such that the red peg $ i $ has not been removed;
2. remove the red peg $ i $ ;
3. append $ i $ to the back of $ a $ .

Doremy wonders how many possible different arrays $ a $ can be produced by the following process. Since the answer can be big, you are only required to output it modulo $ p $ . $ p $ is guaranteed to be a prime number.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1764D/39b25225514736b577fbcbcd5d0b5bf29ecc4db4.png) game with $ n=9 $ and $ a=[7,5,2,8,3,9,4] $ and another game with $ n=8 $ and $ a=[3,4,7,1,8,5,2] $

## 说明/提示

In the first test case, $ n=4 $ , some possible arrays $ a $ that can be produced are $ [4,2,3] $ and $ [1,4] $ . However, it is not possible for $ a $ to be $ [1] $ or $ [1,4,3] $ .

## 样例 #1

### 输入

```
4 100000007```

### 输出

```
16```

## 样例 #2

### 输入

```
1145 141919831```

### 输出

```
105242108```

# 题解

## 作者：VinstaG173 (赞：12)

挺有意思的数学题。

首先转化题意，发现当且仅当有至少 $\left\lfloor\dfrac n2\right\rfloor$ 颗连续的钉子被松开时才会结束操作，因此最终操作序列 $a_1,a_2,\dots,a_k$ 满足 $a_1,a_2,\dots,a_{k-1}$ 中不存在在圆上连续的 $\left\lfloor\dfrac n2\right\rfloor$ 颗钉子，且 $a_1,a_2,\dots,a_k$ 中存在在圆上连续的 $\left\lfloor\dfrac n2\right\rfloor$ 颗钉子。

注意到每颗钉子位置对称，故 $a_k$ 为钉子 $1,2,\dots,n$ 的情况均对称。则只需求出 $a_k=n$ 的情况下可能的 $a$ 总数，最终答案即为此情况总数的 $n$ 倍。

考虑除去 $a_k$，则问题转化为 $a_1,a_2,\dots,a_{k-1}\in\{1,2,\dots,n-1\}$，其中不存在连续 $\left\lfloor\dfrac n2\right\rfloor$ 个整数，且从 $1$ 开始递增的连续整数数量 $s$ 和 从 $n-1$ 开始递减的连续整数数量 $t$ 之和 $s+t\ge\left\lfloor\dfrac n2\right\rfloor-1$。这是因为在 $1,2,\dots,n-1$ 中，圆上连续的钉子一定对应连续整数，且与 $a_k=n$ 相连的钉子为从 $1$ 开始递增的连续整数和从 $n-1$ 开始递减的连续整数。

考虑枚举 $s+t$。当 $s+t=m$ 时，有 $m\ge\left\lfloor\dfrac n2\right\rfloor-1$，故 $m-\left\lfloor\dfrac n2\right\rfloor+1\le s,t\le\left\lfloor\dfrac n2\right\rfloor-1$，故 $(s,t)$ 的不同取值共有 $\left\lfloor\dfrac n2\right\rfloor-1-\left(m-\left\lfloor\dfrac n2\right\rfloor+1\right)=2\left\lfloor\dfrac n2\right\rfloor-m-1$ 种。

此时有钉子 $s+1$ 和 $n-1-t$ 均不存在于 $a_1,a_2,\dots,a_{k-1}$ 中，故剩下的钉子在 $[s+2,n-2-t]$ 中，共有 $M=\max\{0,n-m-3\}$ 个。由于 $M\le\left\lfloor\dfrac n2\right\rfloor-1$，故在其中任意选择钉子均满足要求。

在 $[s+2,n-2-t]$ 中选 $i$ 颗钉子有 $\binom Mi$ 种可能，且限制条件中没有对 $a_1,a_2,\dots,a_{k-1}$ 顺序的要求，故对应的 $a$ 共有 $(k-1)!\binom Mi=(m+i)!\binom Mi$ 种。

因此 $a_k=n$ 时共有 $\displaystyle\sum_{m=\left\lfloor\frac n2\right\rfloor-1}^{n-2}\left(2\left\lfloor\dfrac n2\right\rfloor-m-1\right)\sum_{i=0}^{M}(m+i)!\binom Mi$ 种可能的 $a$。

预处理阶乘及阶乘逆元，直接计算即可，时间复杂度 $O(n^2)$。

Code:
```cpp
int n,ntf;ll res,tmp;
ll fac[5003];
ll fic[5003];
inline ll C(int m,int b){
	return fac[m]*fic[b]%ntf*fic[m-b]%ntf;
}void solve(){rd(n);rd(ntf);res=0;
	fac[0]=1;for(rg int i=1;i<=n;++i)fac[i]=fac[i-1]*i%ntf;
	fic[n]=qpw(fac[n]);for(rg int i=n;i;--i)fic[i-1]=fic[i]*i%ntf;
	for(rg int m=n/2-1;m<n-2;++m){
		tmp=0;for(rg int i=0;i<=n-m-3;++i){
			tmp=(tmp+fac[m+i]*C(n-m-3,i))%ntf;
		}res=(res+(n-(n&1)-1-m)*tmp)%ntf;
	}res=(res+(1-(n&1))*fac[n-2]%ntf)%ntf;
	printf("%lld\n",res*n%ntf);
}
```

---

## 作者：honglan0301 (赞：5)

## 题意简述
$n\ (3\leq n\leq 5000)$ 个点排成一个环，你可以按照任意顺序删点，直到有一段长度 $\geq {n\over2}$ 的点都被删去为止。求有多少种可能的操作序列，对 $p$ 取模。

## 题目分析
显然最多只有一段这样的点都被删去，所以随便考虑都不会算重，不妨先假设最终状态是 $1$ 与 $1+i$ 之间的数被删完的情况。令 $f(i,j)$ 表示共删去了 $j$ 个点, $1$ 到 $1+i$ 之间的数被删完的情况数。  
 
首先，最后一个被删去的点一定介于 $1+i-{n\over2}$ 与 $1+{n\over2}$ 之间（否则在之前就结束了），即有 ${n\over2}+{n\over2}-i+1$ 种选择。其次，在 $1$ 到 $1+i$ 之外的点可以任意选，即有 $C_{n-i-1}^{j-i+1}$ 种选点方式。最后，前 $j-1$ 个点可以以任意顺序删，所以再有 $(j-1)!$ 种顺序。

于是我们得到 $f(i,j)=({n\over2}+{n\over2}-i+1)\times {C_{n-i-1}^{j-i+1}}\times (j-1)!$, 计算求和再 $\times n$ 即可。  

不过当 $n$ 为偶数时有一种特殊情况，即最终状态可能只剩下了一个点，需要特判。

## 代码
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define int long long
using namespace std;
int n,mod,dp[5005][5005],jc[5005],c[5005][5005],ans;
inline int read()
{
	int now=0,nev=1; char c=getchar();
	while(c<'0' || c>'9') { if(c=='-') nev=-1; c=getchar();}
	while(c>='0' && c<='9') { now=(now<<1)+(now<<3)+(c&15); c=getchar(); }
	return now*nev;
}
void init()
{
	c[0][0]=1;
	jc[0]=1;
	for(int i=1;i<=5000;i++)
	{
		jc[i]=i*jc[i-1];
		jc[i]%=mod;
		c[i][0]=1;
		for(int j=1;j<=i;j++)
		{
			c[i][j]=c[i-1][j]+c[i-1][j-1];
			c[i][j]%=mod;
		}
	}
}
signed main()
{
	n=read();
	mod=read();
	init();
	for(int i=n/2+1;i<=n-1;i++)
	{
		for(int j=i-1;j<=n-2;j++)
		{
			dp[i][j]=n/2+n/2-i+1;
			dp[i][j]*=c[n-i-1][j-i+1];
			dp[i][j]%=mod;
			dp[i][j]*=jc[j-1];
			ans+=dp[i][j];
			ans%=mod;
		}
	}
	if(n%2==0)
	{
		dp[n][n-1]=1;
		dp[n][n-1]*=jc[n-2];
		ans+=dp[n][n-1];
		ans%=mod;
	}
	ans*=n;
	ans%=mod;
	cout<<ans<<endl;
}
```

---

## 作者：Alex_Wei (赞：4)

枚举最终绑在两侧的点的距离 $i$。设 $a$ 的最后一个元素有 $r$ 种可能，则对于 $n$ 为偶数，$r = i$，对于 $n$ 为奇数，$r = i - 1$。

枚举绑在两侧的点之间保留的数的个数 $j$，则答案为 $n \sum_i r \times \sum_{j = 0} ^ {i - 2} \binom {i - 2} {j} (n - 3 - j)!$。$\binom {i - 2} j$ 表示从两侧点之间选 $j$ 个保留，$(n - 3 - j)!$ 表示任意安排不保留且不是最后一个点的所有点的顺序，$r$ 表示最后一个元素有 $r$ 种可能，$n$ 表示任意安排绑在两侧的点。

注意特判 $i = 1$ 的情况。对于 $n$ 为偶数，$i$ 的枚举范围为 $[1, \frac n 2]$，对于 $n$ 为奇数，$i$ 的枚举范围为 $[2, \frac {n + 1} 2]$。时间复杂度 $\mathcal{O}(n ^ 2)$。[代码](https://codeforces.com/contest/1764/submission/183008710)。

---

## 作者：MortisM (赞：2)

[CF1764D Doremy's Pegging Game](https://codeforces.com/contest/1764/problem/D)

**Hint：数学。**

简单题，赛时智障没调出来。

发现只要有超过 $\lfloor\frac{n}{2}\rfloor$ 个连续的被删掉了就会碰到中间的钉子，而且不可能有超过一段。

这启发我们枚举这个连续的一段的长度，剩下用数学算算就行了。

设长度为 $l$，则需要考虑最后一个放的位置（因为有可能没放最后一个之前已经有连续的了，这样不应该被算入答案）。最后一个放的可能的位置有 $2\lfloor\frac{n}{2}\rfloor-l$ 个位置，这个比较好推，大概就是两边都不能达到 $\lfloor\frac{n}{2}\rfloor$ 个，补详细介绍了。

剩下还要枚举一下其他位置选了多少个，设为 $x$ 个。答案计算：确定连续段的位置 $\times n$，确定最后一个放的位置 $\times(2\lfloor\frac{n}{2}\rfloor-l)$，确定其他的选哪些 $\times\binom{\max(0,n-l-2)}{x}$，随便排列选取顺序 $\times (l+x-1)!$。所以答案为：
$$
\sum_{l=1}^n\sum_{x=0}^{\max(0,n-l-2)}n\cdot(2\lfloor\frac{n}{2}\rfloor-l)\cdot\binom{\max(0,n-l-2)}{x}\cdot (l+x-1)!
$$

时间复杂度 $\mathcal{O}(n^2)$。[代码](https://codeforces.com/contest/1764/submission/182753202)。

---

## 作者：james1BadCreeper (赞：1)

首先，我们发现这个停止操作序列的条件不太优美。因此，考虑寻找其充要条件。在纸上画一画，不难发现当有至少**连续** $c=\left\lfloor\dfrac n 2\right\rfloor$ 个数删除后，操作便会停止。

其次，我们注意到这个结构本身是一个环，也就是说，我们只需要求出最后一个取的钉子是 $n$ 的方案数，然后乘上 $n$ 便可以得到最终答案。

于是，我们可以考虑枚举实际被删掉的 $l$，可能成为中间的位置的那个有 $2c-l$ 个。

枚举除了这一段中，其它位置选择的个数 $x$。需要确定选择那些选给 $x$，方案数为 $\dbinom{n-l-2}{x}$，最后乘上全排列 $(l+x-1)!$。

```cpp
#include <bits/stdc++.h>
using namespace std; 
const int N = 5000; 

int n, P; 
int fac[5005], C[5005][5005]; 

int main(void) {
    cin >> n >> P; const int P = ::P; 
    for (int i = fac[0] = 1; i <= N; ++i) fac[i] = 1ll * fac[i - 1] * i % P; 
    for (int i = 0; i <= N; ++i) for (int j = C[i][0] = 1; j <= i; ++j)
        C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % P; 
    int ans = 0, c = n / 2; 
    for (int l = c; l <= n; ++l) for (int x = 0; x <= max(0, n - l - 2); ++x) if (c * 2 > l)
        ans = (ans + 1ll * (c * 2 - l) * C[max(0, n - l - 2)][x] % P * fac[l + x - 1]) % P; 
    ans = 1ll * ans * n % P; 
    cout << ans << endl; 
    return 0; 
}
```

---

