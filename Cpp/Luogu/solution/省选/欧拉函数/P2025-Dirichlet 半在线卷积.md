# Dirichlet 半在线卷积

## 题目描述

已知函数 $f$ 满足 $f(1)=1$，且

$$f(n)=\sum_{d|n,d<n}f(d)\varphi(n/d).$$

给定正整数 $n$，试求出 $f(1),f(2),\cdots,f(n)$ 的值。为控制输出量，你只需输出下式的值：

$$\bigoplus_{k=1}^n\left(f(k)\bmod 2^{32}\right). $$

其中 $\oplus$ 代表异或。

## 说明/提示

对于所有数据，$1\le n\le 5\times 10^7$。

对于样例一，$f$ 的前 $10$ 项依次为：$1,1,2,3,4,6,6,9,10,12$。

时限为 std 的 1.5 倍。

## 样例 #1

### 输入

```
10```

### 输出

```
10```

## 样例 #2

### 输入

```
1000000```

### 输出

```
3527171714```

## 样例 #3

### 输入

```
10000000```

### 输出

```
191685100```

# 题解

## 作者：DeepSkyCore (赞：9)

**此题解非正解，复杂度 $O(n\log n)$，但是进行了有效的常数优化。**

显然有一个非常简单的做法：先筛出来 $\varphi(x)$，然后从小到大枚举 $i$，枚举 $ij=x$，把 $f_i$ 和 $\varphi(j)$ 转移到 $f_x$ 即可。由于因数数量是 $O(n\log n)$，所以这个复杂度也是 $O(n\log n)$。

不过如果真的就这么写，自然是过不去的。这里提供一个常数非常小的写法，似乎在这题数据范围下比正解还快很多。

先想想这个东西为什么会慢。算一算实际的转移次数，甚至都不到 $10^9$，而时限 $4$ 秒，所以问题出在内存访问不够快。

首先考虑分块转移，也就是从小到大枚举 $x\in [kB, (k+1)B)$，然后对这个区间再枚举 $ij=x$ 转移。这样我们扫描一个 200MB 的数组的次数减小了，就会快很多，大概只需要跑 3s。下面是一个参考实现，其中，计算除法的部分还用了一次整除分块：

```cpp
constexpr int B = 2e6;
int n; cin>>n;
vector<u32> f(n+1), lst(n+1, 2);
f[1] = 1;
for(int l = 1, r = min(B, n); l <= n; l = r+1, r = min(l + B - 1, n)){
	for(u32 l0 = 1, r0, k; ; l0 = r0+1){
		k = r / l0, r0 = r / k;
		if(k == 1) break;
		rep(i,l0,r0){
			while(lst[i] <= k){
				f[i*lst[i]] += f[i] * phi[lst[i]];
				lst[i]++;
			}
		}
	}
}
u32 ans = 0;
rep(i,1,n){
	ans ^= f[i];
}
cout<< ans <<'\n';
```

不过就算这么搞，我们还是要多次扫描一遍 200MB 的数组，同时还需要在大概 8MB 的数组做随机访问，还能不能优化呢？

考虑一个非常简单的结论：设 $ij=x$，则 $\min(i,j)\le \sqrt x$。因此我们在分块后，区间转移的过程只需要枚举较小的那个因数就行了。

这么搞的话不需要多次扫 200MB 的数组，同时随机访问的内存也更密集。这样就跑得很快了，大概只需要 1.3s。同样给出参考实现：

```cpp
constexpr int B = 65536
int n; cin>>n;
vector<u32> f(n+1);
f[1] = 1;

int l = 1, r = min(n, B);
rep(i,1,r/2){
	for(int j=2; j <= r/i; j++){
		f[j*i] += f[i] * phi[j];
	}
}
l = r+1, r = min(l + B - 1, n);
for(; l <= n; l = r+1, r = min(l + B - 1, n)){
	rep(j,l,r){
		f[j] += phi[j];
	}
	rep(i,2,B){
		rep(j, max(i, (l-1)/i+1), r/i){
			f[i*j] += f[i]*phi[j];
			if(i != j) f[i*j] += phi[i]*f[j];
		}
	}
}

u32 ans = 0;
rep(i,1,n){
	ans ^= f[i];
}
cout<< ans <<'\n';
```

在这题中，由于函数固定，我们还可以结合分段打表。

同时，上述解法的常数非常小。可以看出即使上面的参考实现仍有优化空间，这段代码仍然能在 P5495 取得优于一般 $O(n\log\log n)$ 写法的前缀和的结果。

虽然复杂度更劣，但是由于好写好调常数小，暴力仍然是一个不错的选择。希望大家能够学会这种写法。

---

## 作者：飞雨烟雁 (赞：7)

其实这题一开始的想法是牛顿迭代来着，倍增算是意料之外的解法了。关于 DGF 牛顿迭代的正确性证明和实际操作，请见 [DGF 的计算理论：牛顿迭代与特殊求逆运算](https://www.luogu.com.cn/article/fvuj6pau)，你也可以在这篇文章中见到本文的解法，以下是简单的复述。

---

> 给定积性函数 $g(n)$，若 $f(n)$ 满足 $f(n)=\sum_{d|n,d<n}f(d)g(n/d),f(1)=1$，试求出 $f(1),\cdots,f(n)$ 的值。

设 $F(z)=\sum_{n\ge 1}f(n)n^{-z},G(z)=\sum_{n\ge 1}g(n)n^{-z}$，则我们就是要求 $F=1/(2-G)$，这相当于是做 DGF 求逆。回忆求逆的牛顿迭代式：

$$F\leftarrow 2F_0-(2-G)F_0^2$$

当 $F_0$ 的前 $\sqrt n$ 项都是正确的时，我们就能通过上面这条式子直接求出前 $n$ 项。在上面这条式子中，计算 $F_0^2$ 的时间复杂度是 $\Theta(n)$，乘上 $2-G$ 的时间复杂度是 $\Theta(n\log\log n)$。至于 $F_0$，我们可以直接做 DGF 求逆，以 $\Theta(\sqrt n\log n)$ 的时间花销将其求出。

综上，我们可以在 $\Theta(n\log \log n)$ 时间内求解 $1/(2-G)$。代码如下：


```cpp
#include <cmath>
#include <cstdio>
#include <iostream>
#define int unsigned int
using namespace std;

const int Mx = 5e7 + 5;

bool Vis[Mx];
int Prime[Mx / 10], tot;
int Phi[Mx]; 

void Sieve(int Nx){
	Phi[1] = 1;
	for(int i = 2; i < Nx; ++i){
		if(!Vis[i]) Prime[++tot] = i, Phi[i] = i - 1;
		for(int j = 1; j <= tot && Prime[j] * i < Nx; ++j){
			Vis[i * Prime[j]] = 1;
			if(i % Prime[j] == 0){
				Phi[i * Prime[j]] = Phi[i] * Prime[j];
				break;
			}
			Phi[i * Prime[j]] = Phi[i] * Phi[Prime[j]];
		}
	}
}

int Temp[Mx];
void Inv(const int *F, int *G, int n){
	Temp[1] = 1;
	for(int i = 2; i <= n; ++i) Temp[i] = -F[i];
	for(int i = 2; i <= n; ++i){
    	for(int j = (i << 1); j <= n; j += i) Temp[j] -= Temp[i] * F[j / i];
    }
	for(int i = 1; i <= n; ++i) G[i] = Temp[i];
}

int F[Mx], G[Mx], H[Mx], R[Mx];

signed main(){
	
	
	int n; scanf("%u", &n);
	
	Sieve(n + 1);
	int m = ceil(sqrt(n + 1)) - 1;
	for(int i = 2; i <= m; ++i) F[i] = -Phi[i]; F[1] = 1;
	Inv(F, G, m);
	
	for(int i = 1; i <= m; ++i) for(int j = 1; j <= m; ++j) R[i * j] += G[i] * G[j];
	for(int i = 1; i <= m * m; ++i) H[i] = R[i];
	for(int i = 1; i <= tot; ++i) for(int j = n / Prime[i]; j; --j){
		for(long long k = Prime[i]; j * k <= n; k *= Prime[i]) H[j * k] += H[j] * Phi[k];
	}
	for(int i = 1; i <= n; ++i) H[i] -= 2 * R[i];
	for(int i = 1; i <= m; ++i) H[i] = -H[i];
	
	int ans = 0;
	for(int i = 1; i <= n; ++i) ans ^= H[i];
	printf("%u", ans);
	
	return 0;
}
```

---

## 作者：RAYMOND_7 (赞：7)

半在线卷积，其实就是先分治，计算左区间答案，然后对右区间贡献，发现此时右区间内部没有贡献，不需要额外递归，从而降低时间复杂度。

本题中，如果我们得出了 $\large\lfloor\frac{n}{2}\rfloor$ 以内答案，那么后一半是可以直接计算的，暴力的复杂度为 $O(n\ln n)$ ，~~并不能通过任何测试点~~。

考虑优化，不难发现 $f\otimes\varphi=f\otimes Id \otimes \mu$，前面是个完全积性函数，可以在高维前缀和的过程中统计贡献，后面相当于高维差分。

具体的，当高位前缀和中乘上一个质数 $p_i$ 做贡献时，我们直接把原来的前缀和乘上一个 $p_i$ 就完成了和 $Id$ 函数做卷积的过程。

复杂度应该是 $O(n \ln \ln n)$ 的，不过常数有点大。

```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <cassert>
#include <ctime>

using namespace std;

#define ui unsigned
#define PII pair<int,int>
#define x first
#define y second
#define For(i, l, r) for(int i = l; i <= r; i ++)
#define Rep(i, l, r) for(int i = l; i >= r; i --)

bool START;

const int N=5e7+50;

int n,m,phi[N],cnt,p[N/10];
bool ok[N];
ui f[N],a[N],ans;

void solve(int n)
{
	if(n<=1)return ;
	solve(n/2);
	For(i,1,n)a[i]=0;
	For(i,1,n/2)a[i]=f[i];
	For(i,1,cnt)
	{
		if(p[i]>n)break;
		for(int j=1;j*p[i]<=n;j++)a[j*p[i]]+=a[j]*p[i];
	}
	For(i,1,cnt)
	{
		if(p[i]>n) break;
		for(int j=n/p[i];j;j--)a[j*p[i]]-=a[j];
	}
	For(i,n/2+1,n)f[i]=a[i];
}

bool ENDPOS = 0;
signed main()
{
	double chu = clock();
	cin>>n;
	f[1]=1;phi[1]=1;
	For(i,2,n)
	{
		if(!ok[i])p[++cnt]=i,phi[i]=i-1;
		For(j,1,cnt)
		{
			if(i*p[j]>n)break;
			ok[i*p[j]]=1;if(i%p[j]==0)break;
		}
	}
	solve(n);
	For(i,1,n)ans^=f[i];
	printf("%u\n", ans);
	cerr << "Time = " << (clock() - chu) / CLOCKS_PER_SEC << endl;
	cerr << (&ENDPOS - &START) * 1.0 / 1024 / 1024 << endl; return 0;
}

```

---

