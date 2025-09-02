# PRIMES2 - Printing some primes (Hard)

## 题目描述

The problem statement is really simple (the constraints maybe not). You are to write all primes less than 10^9.

## 样例 #1

### 输入

```
```

### 输出

```
2
3581
7927
...
999978527
999988747
999999151```

# 题解

## 作者：Leasier (赞：5)

### 简介
Wheel Factorization 是埃氏筛的一种优化。
### 算法
前置芝士：[埃氏筛](https://oi-wiki.org/math/sieve/#_2)、[区间筛](https://oi-wiki.org/math/sieve/#_6)

在暴力埃氏筛时，我们会重复标记一些质数。

如何减少重复标记的数目呢？设 $p_n$ 表示第 $n$ 个质数，$M_n = \displaystyle\prod_{i = 1}^n p_i$，$\operatorname{LPF}(n)$ 表示 $n$ 的最小质因数，则可以先筛出前 $M_k$ 个数中 $\operatorname{LPF} > p_n$ 的数和 $1$，再以 $M_k$ 为块长，依次筛出每个块内的质数。

注意：

1. 筛的时候直接从第 $k + 1$ 个质数开始筛，且统计质数时只需要看可能为质数的数；

2. 第一个块需要特判。

时间复杂度为 $O(\frac{n}{\ln k})$。
### 代码
```cpp
inline int init(){
	int cnt = 0, block_cnt = 0, ans;
	p[0] = p[1] = true;
	for (register int i = 1; i < block; i++){
		pre_block[i] = 1;
	}
	for (register int i = 2; i <= block; i++){
		if (!p[i]){
			prime[++cnt] = i;
			if (cnt <= M){
				prime[cnt] = i;
				pre_block[i] = 0;
			}
		}
		for (register int j = 1; j <= cnt && i * prime[j] <= block; j++){
			register int t = i * prime[j];
			p[t] = true;
			if (j <= M) pre_block[t] = 0;
			if (i % prime[j] == 0) break;
		}
	}
	for (register int i = 1; i < block; i++){
		if (pre_block[i]) mark[++block_cnt] = i;
	}
	ans = cnt;
	for (register int i = 1; i < K; i++){
		register int end = (i + 1) * block - 1, start = i * block;
		memcpy(cur_block, pre_block, sizeof(bool) * block);
		for (register int j = M + 1; prime[j] * prime[j] <= end; j++){
			register int t1 = max((start - 1) / prime[j] + 1, prime[j]) * prime[j], t2 = prime[j] << 1;
			if (!(t1 & 1)) t1 += prime[j];
			for (register int k = t1 - start; k < block; k += t2){
				cur_block[k] = 0;
			}
		}
		for (register int j = 1; j <= block_cnt; j++){
			if (cur_block[mark[j]]) prime[++ans] = start + mark[j];
		}
	}
	return ans;
}
```
### 例题
1. [SP6488 PRIMES2 - Printing some primes (Hard)](https://www.luogu.com.cn/problem/SP6488)（模板题）

代码：
```cpp
#include <stdio.h>
#include <string.h>

const int N = 50851836 + 7, block = 2 * 3 * 5 * 7 * 11 * 13 * 17, M = 7, K = 1959, P = 1e9, Q = 500;
int prime[N], mark[block + 7];
bool p[block + 7], pre_block[block + 7], cur_block[block + 7];

inline int max(int a, int b){
	return a > b ? a : b;
}

inline int init(){
	int cnt = 0, block_cnt = 0, ans;
	p[0] = p[1] = true;
	for (register int i = 1; i < block; i++){
		pre_block[i] = 1;
	}
	for (register int i = 2; i <= block; i++){
		if (!p[i]){
			prime[++cnt] = i;
			if (cnt <= M){
				prime[cnt] = i;
				pre_block[i] = 0;
			}
		}
		for (register int j = 1; j <= cnt && i * prime[j] <= block; j++){
			register int t = i * prime[j];
			p[t] = true;
			if (j <= M) pre_block[t] = 0;
			if (i % prime[j] == 0) break;
		}
	}
	for (register int i = 1; i < block; i++){
		if (pre_block[i]) mark[++block_cnt] = i;
	}
	ans = cnt;
	for (register int i = 1; i < K; i++){
		register int end = (i + 1) * block - 1, start = i * block;
		memcpy(cur_block, pre_block, sizeof(bool) * block);
		for (register int j = M + 1; prime[j] * prime[j] <= end; j++){
			register int t1 = max((start - 1) / prime[j] + 1, prime[j]) * prime[j], t2 = prime[j] << 1;
			if (!(t1 & 1)) t1 += prime[j];
			for (register int k = t1 - start; k < block; k += t2){
				cur_block[k] = 0;
			}
		}
		for (register int j = 1; j <= block_cnt; j++){
			if (cur_block[mark[j]]) prime[++ans] = start + mark[j];
		}
	}
	return ans;
}

inline void write(int n){
	if (n >= 10) write(n / 10);
	putchar(n % 10 + '0');
}

int main(){
	int cnt = init();
	for (register int i = 1, j = 0; i <= cnt && prime[i] <= P; i++){
		if (++j % Q == 1){
			write(prime[i]);
			putchar('\n');
		}
	}
	return 0;
}
```
2. [SP6489 KPRIMES2 - Finding the Kth Prime (Hard)](https://www.luogu.com.cn/problem/SP6489)

详见[这篇题解](https://www.luogu.com.cn/blog/Leasier/solution-SP6489)。

---

## 作者：xxxxxzy (赞：2)

[题目](https://www.luogu.com.cn/problem/SP6488)

有个结论，先上：

如果一个正整数 $p$ 与 $k$ 互质，则 $p+k$ 与 $k$ 互质。

反之，如果一个正整数 $p$ 与 $k$ 不互质，则 $p+k$ 与 $k$ 不互质。

那么，我们可以先选定一个 $k$，筛出 $[1,k]$ 的所有与 $k$ 不互质的数，然后拿这些数去筛 $[k+1,2k],[2k+1,3k]...$

简单来说，就是每次处理一个块 $[qk+1,(q+1)k]$，用之前的质数去筛这个区间，然后最后只用看 $[1,k]$ 与 $k$ 互质的数的位置。

时间复杂度就是 $O(n \dfrac{\varphi (k)}{k} )$。

注意卡常，比如说直接忽略偶数。

(SPOJ远程提交好像炸了，不过我在SPOJ官网过了)

```cpp
#include<bits/stdc++.h>
#define int long long
const int K=510510,N=1e9;
using namespace std;
int pos[K+5],primes[60000005],m,p;
bool ph[K+5];
void prime(int n){
	for(int i=2;i<=n;i++){
		if(!ph[i]) primes[++m]=i;
		for(int j=1;j<=m&&i*primes[j]<=n;j++){
			ph[i*primes[j]]=1;
			if(i%primes[j]==0) break;
		}
	}
}
#define ctz __builtin_ctz
inline signed gcd(signed a,signed b) {
    signed az = ctz(a), bz = ctz(b), z = (az > bz) ? bz : az, t; b >>= bz;
    while(a) a >>= az, t = a - b, az = ctz(t), b = min(a, b), a = t < 0ll ? -t : t;
    return b << z;
}
signed main(){
    prime(K);
	for(int i=1;i<=K;i++){
		if(gcd(i,K)==1) pos[++p]=i;
	}
	for(int i=2;i<=1959;i++){
		int r=i*K,l=(i-1)*K+1;
		memset(ph,0,sizeof(ph));
		for(int j=8;j<=m&&primes[j]*primes[j]<=r;j++){
			int now=primes[j]*max(primes[j],(l-1)/primes[j]+1ll);
			if(!(now&1)) now+=primes[j];
			now-=l-1;
			while(now<=K) ph[now]=1,now+=primes[j]<<1;
		}
		for(int j=1;j<=p;j++){
			if(!ph[pos[j]]) primes[++m]=l+pos[j]-1;
		}
	}
    for(int i=1;i<=m;i+=500){
    	if(primes[i]>N) break;
    	printf("%lld\n",primes[i]);
	}
} 
```

---

## 作者：cdxxx04 (赞：1)

# 题解：SP6488 PRIMES2 - Printing some primes (Hard)

[题目传送门](https://www.luogu.com.cn/problem/SP6488)

[推荐题目](https://www.luogu.com.cn/problem/SP6489)

---

## 关于区间筛

[筛至平方根（OI Wiki）](https://oi-wiki.org/math/number-theory/sieve/#%E7%AD%9B%E8%87%B3%E5%B9%B3%E6%96%B9%E6%A0%B9)

[分块筛选（OI Wiki）](https://oi-wiki.org/math/number-theory/sieve/#%E5%88%86%E5%9D%97%E7%AD%9B%E9%80%89)

## 题目思路

这道题是一道很明显的区间筛。

区间筛的主要思想是把 $1\sim n$ 分成 $\sqrt{n}$ 块，先处理除第 $1$ 块的质数，接着不断用第 $i-1$ 块的质数去筛第 $i$ 块的质数，知道把这 $\sqrt{n}$ 块全部筛完。

## AC 代码

```cpp
#include <bits/stdc++.h>
#define IF_ON_LINEOJ true
#define IF_ON_LUOGU false
namespace fast {
#if IF_ON_LUOGU == false
#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector")
#endif
#define endl '\n'
#define il inline
#define re register
#define ri re int
#define ll long long
#if IF_ON_LINEOJ
static char buf[100000], *p1 = buf, *p2 = buf;
#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++)
#define int long long
#endif
il void takefastout()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0 /*nullptr*/);
}
il int read()
{
    ri x(0);
    re char c = getchar();
    while (c > '9' || c < '0')
        c = getchar();
    while (c <= '9' && c >= '0')
        x = (x << 1) + (x << 3) + (c ^ 48), c = getchar();
    return x;
}
#undef int
}
using namespace std;
using namespace fast;
#define set(x, y) x[y >> 5] |= 1 << (y & 31)
const int M = 8, K = 1959, N = 50851836 + 7, block = 2 * 3 * 5 * 7 * 11 * 13 * 17, block_size = (block >> 5);
int prime[N], pre_block[block_size + 1], cur_block[block_size + 1];
char p[block + 1];
void build_prime()
{
    int cnt = 0;
    p[0] = p[1] = true;
    set(pre_block, 0);
    set(pre_block, block);
    for (ri i = 2; i <= block; i++) {
        if (p[i] == 0) {
            prime[++cnt] = i;
            if (cnt < M)
                set(pre_block, i);
        }
        for (ri j = 1; j <= cnt && i * prime[j] <= block; j++) {
            int t = i * prime[j];
            p[t] = true;
            if (j < M)
                set(pre_block, t);
            if (i % prime[j] == 0)
                break;
        }
    }
    for (ri i = 1, j = cnt; i < K; i++) {
        int end = (i + 1) * block - 1, start = i * block;
        memcpy(cur_block, pre_block, sizeof(cur_block));
        for (ri k = M; prime[k] * prime[k] <= end; k++) {
            int t1 = max((start - 1) / prime[k] + 1, prime[k]) * prime[k], t2 = prime[k] << 1;
            for (ri l = (t1 & 1 ? t1 : t1 + prime[k]) - start; l < block; l += t2)
                set(cur_block, l);
        }
        for (ri k = 0; k <= block_size; k++) {
            int t1 = ~cur_block[k];
            while (t1) {
                int t2 = __builtin_ctz(t1);
                if ((k << 5) + t2 >= block)
                    break;
                prime[++j] = start + (k << 5) + t2;
                if (j >= N)
                    return;
                t1 -= t1 & -t1;
            }
        }
    }
}
int main()
{
    takefastout();
    build_prime();
    for (ri i = 1, j = 0; prime[i] < 1e9; i++)
        if (++j % 500 == 1)
            cout << prime[i] << '\n';
    return 0;
}
```

---

