# [POI 2016] Nim z utrudnieniem

## 题目描述

A 和 B 两个人玩游戏，一共有 $m$ 颗石子，A 把它们分成了 $n$ 堆，每堆石子数分别为 $a_1,a_2,...,a_n$，每轮可以选择一堆石子，取掉任意颗石子，但不能不取。谁先不能操作，谁就输了。在游戏开始前，B 可以扔掉若干堆石子，但是必须保证扔掉的堆数是 $d$ 的倍数，且不能扔掉所有石子。

A 先手，请问 B 有多少种扔的方式，使得 B 能够获胜。

## 说明/提示

对于 $100\%$ 的数据，$1\le n\le 5\times 10^5$，$1\le d\le 10$，$1\le a_i\le 10^6$，$m$ 不直接给出，但数据保证 $1\le m\le 10^7$。

## 样例 #1

### 输入

```
5 2
1 3 4 1 2```

### 输出

```
2```

# 题解

## 作者：chen_zhe (赞：13)

发现自己两年前做的题目洛谷上有了，开心。其实题解也是那个时候写的。

Nim游戏中，当$a_1\bigoplus a_2\bigoplus a_3 \bigoplus \cdots \bigoplus a_n=0$的时候，先手必输。

由此我们要在原来的局面中让后手取$k\times d$堆，让先手输，可以用到异或的一个性质：对于任何整数$A$，必然有$A \bigoplus A=0$，因此我们可以记录原来$n$堆石子的异或和$s$，也就是把题目的意思转换为了取$k\times d$堆石子，问有多少种方法让取到的石子堆中每堆石子的异或和为$s$

这样我们就可以转移一个$DP$方程。我们设$f_{i,j,k}$表示处理完$i$堆石子，取的堆数在$\mod j$意义下取了的石子的异或和为$k$的情况。

这个时候则有：$f_{i,j,k}=f_{i-1,j,k}+f_{i-1,j-1,k\bigoplus {a_i}}$

这样做的话，时间复杂度为$O(n \times d \times maxa)$，会TLE

有一个很巧妙的想法是：因为对于任意一个正整数$A$，它和比它自己小的数字异或起来的结果不会超过$A \times 2$，由此可以得出：$a_i$和比$a_i$小的数字的异或和不会超过$2\times a_i$，因此我们可以直接对石子排序，这样的时间复杂度就可以减少到$O(n \times d)$

最后有个小细节要注意一下：当$d|n$的时候，结果要减去$1$

然后后来就在bzoj上rank1了。（现在rank3）

![](https://cdn.luogu.com.cn/upload/pic/28665.png)

```cpp
/**************************************************************
    Problem: 4347
    User: rourou
    Language: C++
    Result: Accepted
    Time:9516 ms
    Memory:52464 kb
****************************************************************/
 
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <cctype>
 
using namespace std;
 
int read()
{
    int x=0,f=1;char ch=getchar();
    while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
    while (isdigit(ch)){x=x*10+ch-48;ch=getchar();}
    return x*f;
}
 
const int MOD=1e9+7;
 
int n,d,a[500050],f[11][1050000],g[1050000];
 
int main()
{
    n=read(),d=read();
    int s=0;
    for (int i=1;i<=n;i++)
        s^=(a[i]=read());
    sort(a+1,a+n+1);
    f[0][0]=1;
    int u=1;
    for (int i=1;i<=n;i++)
    {
        while (u<=a[i])
            u<<=1;
        for (int j=0;j<u;j++)
            g[j]=(f[d-1][j^a[i]]+f[0][j])%MOD;
        for (int j=d-1;j>0;j--)
            for (int k=0;k<u;k++)
                f[j][k]=(f[j][k]+f[j-1][k^a[i]])%MOD;
        for (int j=0;j<u;j++)
            f[0][j]=g[j];
    }
    if (n%d==0)
        f[0][s]--;
    if (f[0][s]<0)
        f[0][s]+=MOD;
    cout << f[0][s] << endl;
    return 0;
}
```


---

## 作者：VinstaG173 (赞：7)

首先我们要熟知一个结论：B 必胜当且仅当最初的所有石子数异或和 $=0$。这是 Nim 游戏的结论。

于是我们可以开始用 dp 解决这个问题。令 `dp[i][j][k]` 表示在前 $i$ 堆中丢弃了模 $d$ 余 $j$ 数量堆的石子，剩余石子的异或和为 $k$。

但是这样的时间复杂度是 $O(nmk)$，显然无法承受。

考虑到将石子从少到多排列后，扫到第 $i$ 堆时候的 $k$ 的二进制位数和 $a_i$ 的二进制位数相等。所以我们可以不用每次枚举到 $m$，只要枚举到可能的最大的 $k$ 就行了，这个数是不超过 $2a_i$ 的。时间复杂度变成了 $O(mk)$。

接着用滚动数组优化空间就行了。

Code:
```cpp
#include<cstdio>
const int p=1e9+7;
int n,d,x,m;
int nm[1050007];
int tmp[1050007];
int dp[13][1050007];//第一维表示 j，第二维表示 k
int main()
{
	scanf(" %d %d",&n,&d);
	for(int i=0;i<n;++i)scanf(" %d",&x),++nm[x],(x>m)&&(m=x);
	dp[0][0]=1;
	for(int i=1,h=1;i<=m;++i)
	{
		while(h<=i)h<<=1;
		while(nm[i]--)
		{
			for(int k=0;k<h;++k)
			{
				tmp[k]=dp[d-1][k]+dp[0][k^i];
				(tmp[k]>=p)&&(tmp[k]-=p);
			}
			for(int r=d-1;r;--r)
			{
				for(int k=0;k<h;++k)
				{
					if(k>(k^i))continue;
					x=dp[r][k];
					dp[r][k]=dp[r-1][k]+dp[r][k^i];
					(dp[r][k]>=p)&&(dp[r][k]-=p);
					dp[r][k^i]=dp[r-1][k^i]+x;
					(dp[r][k^i]>=p)&&(dp[r][k^i]-=p);
				}
			}
			for(int k=0;k<h;++k)
			{
				dp[0][k]=tmp[k];
			}
		}
	}
	if(n%d||dp[0][0])printf("%d\n",dp[0][0]-(n%d==0));
	else printf("%d\n",p-1);
	return 0;
}
```

---

## 作者：Alex_Wei (赞：2)

> *[P5970 [POI2016]Nim z utrudnieniem](https://www.luogu.com.cn/problem/P5970)
>
> [POI 合集](https://www.cnblogs.com/alex-wei/p/POI.html)。

根据取石子游戏的经典理论，我们需要选出 $k$ 堆石子，使得 $k \neq 0$，$d\mid k$ 且这 $k$ 堆石子的异或和等于 $\bigoplus a_i$。

考虑设计 $f_{i, j, k}$ 表示前 $i$ 堆石子中选出 $\bmod d = k$ 堆，异或和为 $j$ 的方案数，直接做的复杂度是 $\mathcal{O}(2 ^ {20}dn)$，因为不大于 $10 ^ 6$ 的数最大可能异或出 $2 ^{20} - 1$，无法接受。但注意到 $\sum a_i$ 有限制，说明有很多堆石子，石子数都很少。因为石子顺序不影响答案，如果我们按从小到大的顺序排列石子，那么前 $i$ 堆石子能够异或得到的所有数均不超过不小于 $a_i$ 的最小的 $2$ 的幂 $2 ^ r < 2a_i$，这样一来我们只需枚举到 $2 ^ r$ 而非 $2 ^ {20}$。总复杂度均摊下来就是 $\sum a_i$ 而非 $a_i \times n$。故可以通过，时间复杂度 $\mathcal{O}(md)$，空间复杂度使用滚动数组优化后为 $\mathcal{O}(2 ^ {20} d)$。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1 << 24;
const int mod = 1e9 + 7;
void add(int &x, int y) {x += y, x >= mod && (x -= mod);}
int n, d, tot, a[N], f[10][N];
int main() {
	cin >> n >> d;
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]), tot ^= a[i];
	sort(a + 1, a + n + 1), f[0][0] = 1;
	for(int i = 1; i <= n; i++) {
		static int g[N], lg;
		lg = 1 << 32 - __builtin_clz(a[i]);
		for(int j = 0; j < lg; j++)
			g[j] = (f[d - 1][j ^ a[i]] + f[0][j]) % mod;
		for(int j = d - 1; j; j--)
			for(int k = 0; k < lg; k++)
				f[j][k] = (f[j][k] + f[j - 1][k ^ a[i]]) % mod;
		for(int j = 0; j < lg; j++) f[0][j] = g[j];
	} cout << (f[0][tot] + mod - (n % d == 0)) % mod;
	return 0;
}
```

---

## 作者：Leasier (赞：1)

前置芝士：[Nim 游戏](https://oi-wiki.org/math/game-theory/impartial-game/)

首先由 Nim 游戏的经典结论可知石子数量异或和为 $0$ 时后手必胜。

考虑一个暴力 dp：设 $dp_{i, j, k}$ 表示前 $i$ 堆石子中删去石子堆数模 $d$ 为 $j$ 且删去的异或和为 $k$ 的方案数。

初值：$dp_{0, 0, 0} = 1$。

转移：$dp_{i, j, k} = dp_{i - 1, j, k} + dp_{i - 1, (j + d - 1) \bmod d, k \operatorname{xor} a_i}$。

答案：$dp_{n, 0, \operatorname{xor}_{i = 1}^n a_i} - [n \bmod d = 0]$。

直接做是 $O(nd \max a_i)$ 的，显然不能通过。

现在考虑优化。注意到 $m \leq 10^7$，又注意到异或的性质：一堆 $\leq x$ 的数异或起来不会超过 $2x$。

于是考虑对 $a$ 排序，从小到大处理，处理到 $a_i$ 时有效值域不会超过 $2a_i$。加上这个优化后时间复杂度变为 $O(md)$，可以通过。

代码：
```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>

using namespace std;

const int mod = 1e9 + 7;
int b[500007], dp[17][1048577], temp[1048577];

int main(){
	int n, s, full = 0, x = 1, ans;
	scanf("%d %d", &n, &s);
	for (int i = 1; i <= n; i++){
		scanf("%d", &b[i]);
		full ^= b[i];
	}
	sort(b + 1, b + n + 1);
	dp[0][0] = 1;
	for (int i = 1; i <= n; i++){
		while (x <= b[i]) x <<= 1;
		for (int j = 0; j < x; j++){
			temp[j] = (dp[0][j] + dp[s - 1][j ^ b[i]]) % mod;
		}
		for (int j = s - 1; j >= 1; j--){
			for (int k = 0; k < x; k++){
				dp[j][k] = (dp[j][k] + dp[j - 1][k ^ b[i]]) % mod;
			}
		}
		for (int j = 0; j < x; j++){
			dp[0][j] = temp[j];
		}
	}
	ans = dp[0][full];
	if (n % s == 0) ans = ((ans - 1) % mod + mod) % mod;
	cout << ans;
	return 0;
}
```

---

## 作者：木xx木大 (赞：0)

[P5970 [POI2016]Nim z utrudnieniem](https://www.luogu.com.cn/problem/P5970)

根据 Nim 博弈的结论，只要 B 扔完后剩下的各堆石子个数异或和为0，B就能获胜。那么设 $dp_{i,j,k}$ 表示当前考虑到第 $i$ 堆石子，已经取了 $j$ 堆，取走部分的异或和为 $k$ 的方案数。一个显然的 dp 方程：

 $dp_{i,j,k}=dp_{i-1,j-1,k \ xor \ a_i}+dp_{i-1,j,k}$

发现空间会炸，于是考虑像背包一样倒序转移，滚掉第一维。

发现这样 dp 的时间复杂度为 $O(nd\times max(a_i))$，也会炸。考虑如何优化。

（**本题核心**）一个性质：**一个数 $x$ 异或上一些比它小的数后，二进制下的位数不变。设 $u$ 表示二进制下与 $x$ 位数相同的最大的数，则 $u\le 2x$**。那么我们把 $a_i$ 从小到大排序，每次只枚举到的 $a_i$ 对应的 $u$ ，复杂度就降为了 $O(md)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace FGF
{
	int n,m;
	const int N=1e7+5;
	const int mo=1e9+7;
	int f[11][N],g[N];
	int a[N]; 
	void work()
	{
		scanf("%d%d",&n,&m);
		int sum=0;
		for(int i=1;i<=n;i++)
			scanf("%d",&a[i]),sum^=a[i];
		sort(a+1,a+n+1);
		int u=1;f[0][0]=1;
		for(int i=1;i<=n;i++)
		{
			while(u<=a[i])u<<=1;
			for(int k=0;k<u;k++)
				g[k]=(f[m-1][k^a[i]]+f[0][k])%mo;
			for(int j=m-1;j;j--)
				for(int k=0;k<u;k++)
					f[j][k]=(f[j-1][k^a[i]]+f[j][k])%mo;
			for(int k=0;k<u;k++)
				f[0][k]=g[k];
		}
		if(n%m==0)f[0][sum]--;	
		printf("%d",(f[0][sum]+mo)%mo);
	}
}
int main()
{
	FGF::work();
	return 0;
}
```

---

## 作者：pyyyyyy (赞：0)


[博客阅读效果更佳](https://www.cnblogs.com/pyyyyyy/p/13258015.html)

[Nim z utrudnieniem](https://www.luogu.com.cn/problem/P5970)

> $A$和$B$在进行$Nim$博弈，$A$是先手，但是$B$在开始之前可以扔掉$d$的倍数堆的石子（**不能扔掉全部的**），问$B$有多少种扔的办法使$B$必胜。

显然$B$必胜的条件为$a_1 \oplus a_2 \oplus \cdots a_n = 0$($NIM$博弈的结论)

显然可以这么来定义状态$f[i][j][k]$表示前$i$堆石子，扔掉了$j$堆(在$mod\ d$下),异或和是$k$的方案数

$f[i][j][k]=f[i-1][j][k]+f[i-1][j-1][k\oplus a_i]$

复杂度为$O(n\cdot d\cdot maxa_i)$

现在的问题在于怎么把$maxa_i$这一项变小？

有一个神奇的结论

> 因为对于任意一个正整数$N$，它和比它自己小的数字异或起来的结果不会超过$N \times 2$

所以只需要把$a_i$从小到大排序，这样复杂度就变成$O(n\cdot d)$

现在问题在于空间开销太大了。

显然可以用滚动数组，但是仍然太大，因为我们必须要把$i$这一维给省掉。

只需要在每一层$i$时，按照$k$从大到小的顺序进行转移即可。

还要注意$n$是$d$的倍数时，会算上全选的情况，答案需要减去$1$

```cpp
/*
@ author:pyyyyyy/guhl37
-----思路------

-----debug-------

*/
#include <bits/stdc++.h>
#define int long long 
using namespace std;
const int N = 500000 + 5;
const int mod = 1e9 + 7;
int sum, n, d, a[N], f[11][1 << 20], g[1 << 20];
signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	scanf("%d %d",&n, &d);
	for(int i = 1; i <= n; ++i)	scanf("%d",&a[i]),sum ^= a[i];
	sort(a + 1, a + 1 + n);
	f[0][0] = 1;
	for(int i = 1; i <= n; ++i)
	{
		int max = 1;
		while(max <= a[i]) max <<= 1;
		for(int j = 0; j < max; ++j) g[j] = f[d - 1][j];
		for(int k = d - 1; k ; --k)
			for(int j = 0; j < max; ++j)
				f[k][j] = (f[k][j] + f[k - 1][j ^ a[i]]) % mod;
		for(int j = 0; j < max; ++j) f[0][j] = (f[0][j] + g[j ^ a[i]]) % mod;
	}
	if(n % d == 0) f[0][sum] -= 1;
	cout << (f[0][sum] + mod)%mod;
	return 0;
}

```



---

