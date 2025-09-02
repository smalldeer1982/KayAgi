# Lonely Numbers

## 题目描述

In number world, two different numbers are friends if they have a lot in common, but also each one has unique perks.

More precisely, two different numbers $ a $ and $ b $ are friends if $ gcd(a,b) $ , $ \frac{a}{gcd(a,b)} $ , $ \frac{b}{gcd(a,b)} $ can form sides of a triangle.

Three numbers $ a $ , $ b $ and $ c $ can form sides of a triangle if $ a + b > c $ , $ b + c > a $ and $ c + a > b $ .

In a group of numbers, a number is lonely if it doesn't have any friends in that group.

Given a group of numbers containing all numbers from $ 1, 2, 3, ..., n $ , how many numbers in that group are lonely?

## 说明/提示

For first test case, $ 1 $ is the only number and therefore lonely.

For second test case where $ n=5 $ , numbers $ 1 $ , $ 3 $ and $ 5 $ are lonely.

For third test case where $ n=10 $ , numbers $ 1 $ , $ 5 $ and $ 7 $ are lonely.

## 样例 #1

### 输入

```
3
1 5 10```

### 输出

```
1
3
3```

# 题解

## 作者：One_JuRuo (赞：4)

## 思路

因为对于 $\gcd(a,b)$，$\frac a{\gcd(a,b)}$，$\frac b{\gcd(a,b)}$ 中 $a$ 和 $b$ 是等价的，可以交换的。所以我们先令 $a>b$。

令 $\gcd(a,b)=d$，因为 $\frac a{\gcd(a,b)}$ 有除法，所以我们应该想办法去除除法，就同乘以一个 $d$，即 $d^2$，$a$，$b$ 三条边。

构成三角形的三条边需要满足两条较小边之和大于最大边。

讨论一下情况：

- $d^2$ 最大，则需要满足 $a+b>d^2$。

- $d^2$ 不是最大，则 $a$ 最大，需要满足 $d^2+b>a$。

如果 $a,b$ 互质，则 $d=1$，因为 $a>b$，所以一定不满足，这种情况一定不能构成三角形。

那么 $a,b$ 一定不能互质，若 $d<\sqrt a$，则需要满足 $d^2+b>a$，令 $a=d\times k$，只需要令 $b=d\times (k-1)$，那么就可以满足条件了，若 $d>\sqrt a$，则需要满足 $a+b>d^2$，同样是上面一种的构造方法，所以如果 $a$ 是合数，很容易就能构造满足条件的 $b$。所以合数一定不是孤独数字。

再考虑 $a$ 是质数的情况，这种情况下，$a$ 没法找到不互质的 $b$，那么是质数就一定是孤独数字吗？不见得，因为 $b$ 可以是质数，那么 $a$ 至少取多少呢？

取 $b$ 的 $k$ 倍吗？三条边就是 $b$，$k\times b$，$b^2$，若 $k<b$，则需要满足 $b+k\times b>b^2$ 显然不满足，$k$ 至少要选 $b$ 也就是 $a$ 至少为 $b^2$。

所以对于质数 $p$，如果 $p^2$ 在范围 $[1,n]$ 内，它就不是孤独数字。

所以固定了范围为 $n$ 后，孤独数字就只有 $\lfloor \sqrt n\rfloor \sim n$ 的质数了。

所以，可以先线性筛预处理，然后前缀和统计质数个数，最终答案是 $1\sim n$ 的质数个数减去 $1\sim \lfloor \sqrt n\rfloor$ 的质数个数，记得加上 $1$ 的情况，$1$ 与任意数互质，所以它一定是孤独数字。

## AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
int shu[1000005],pri[1000005],cnt;
int T,n;
inline void init()//线性筛预处理
{
	for(int i=2;i<=1000000;++i)
	{
		if(!shu[i]) pri[++cnt]=i;
		for(int j=1;j<=cnt&&pri[j]*i<=1000000;++j)
		{
			shu[pri[j]*i]=1;
			if(i%pri[j]==0) break;
		}
	}
	for(int i=2;i<=1000000;++i) shu[i]^=1,shu[i]+=shu[i-1];//前缀和统计1~i的质数个数
}
int main()
{
	init();
	scanf("%d",&T);
	while(T--) scanf("%d",&n),printf("%d\n",shu[n]-shu[(int)sqrt(n)]+1);//注意：无论如何1都会孤独数字，所以记得+1
}
```

---

## 作者：是个汉子 (赞：4)

### Solution

看题和 $\gcd$ 有关系，所以我们可以先考虑一下质数，然后发现对于质数 $x$ ，当他不 $lonely$ 即满足条件的时候，是 $x^2$ 出现的时候，因为 $x+1>x,x+x>1$ 。

现在考虑合数，分两种情况，一种是形似 $p^2$ 的( $p$ 是质数)，因为 $p^2$ 能使 $p$ 不孤独，所以 $p^2$ 自己也是不孤独的；另一种是剩下的，设 $a,c$ 为其中任意的两个数( $a>c$ )， $b$ 为 $gcd(a,c)$ 且 $1<b<\sqrt a$，那么我们构造出一个 $c$ 满足条件： $\frac ab+b>\frac cb,\frac ab+\frac cb>b,\frac cb+b>\frac ab$ 即可。

因为 $a>c$ 所以 $\dfrac ab+b>\dfrac cb$ 显然满足，因为 $b<\sqrt a$ ，所以 $\dfrac cb+\dfrac ab>b$ 也满足。对于剩下的条件我们只要能证明必有一个 $\dfrac cb$ 满足 $\dfrac cb>\dfrac ab-b,\dfrac cb<\dfrac ab$ 。因为 $b>1$ ，所以在 $(\dfrac ab-b)$ ~ $\dfrac ab$ 起码有一个数字满足 $\dfrac cb$ 的条件。

我们已经考虑完所有情况，发现只有一个质数的平方没有出现在前 $n$ 数中时，这个质数才会被统计进答案。

说的简单一点：设 $sum_i$ 为前 $i$ 数中的质数的数量，那么答案就是 $sum_n-sum_{\lfloor \sqrt n\rfloor}$

### 代码

```c++
# include <iostream>
# include <cstdio>
# include <cmath>
# define MAXN 1000010

using namespace std;

inline void read(int & x){
	x = 0; int ch = getchar();
	for(	;!isdigit(ch); ch = getchar());
	for(	; isdigit(ch); ch = getchar()){
		x = x * 10 + ch - '0';
	}
}

int cntP = 0, prime[MAXN], sum[MAXN];
bool notP[MAXN];

int main(){
	int t;
	read(t);

	notP[0] = notP[1] = 1;

	for(int i = 2; i <= 1000000; i++){
		if(!notP[i]){
			prime[++cntP] = i;
		}
		for(int j = 1; j <= cntP && i * prime[j] <= 1000000; j++){
			notP[i * prime[j]] = 1;
			if(!(i % prime[j])){
				break;
			}
		}
	}

	for(int i = 1; i <= 1000000; i++){
		sum[i] = sum[i-1] + (!notP[i]);
	}

	for(int n; t; t--){
		read(n);
		printf("%d\n", sum[n] - sum[(int)sqrt(n)] + 1);
	}

	return 0;
}

```

（这个代码不是我的，是和我一个团队打比赛的同学的，~~本人代码锅了~~）

---

## 作者：npqenqpve (赞：2)

### 题意：
多组询问，每次询问给出 $n$，回答对于所以 $i\in [1,n]$，有多少个 $i$ 满足不存在 $j\in [1,n]$ 使得 $\gcd(i,j)$，$\frac{j}{\gcd(i,j)}$，$\frac{i}{\gcd(i,j)}$ 构成三角形 。
### 思路：
首先观察样例可以发现：
- 偶数一定不对答案有贡献，因为可以选择 $i$ 和 $i\pm2$ 使得他们的最大公约数为 $2$，另外两边之差一定是 $1$；

可以依照这种思路分类下去，由于奇数的情况有些复杂在最后讨论；

- 考虑某些质数 $p$，那么 $\gcd(p,j)$ 一定是 $1$ 或 $p$，$\frac{p}{\gcd(p,j)}$ 与对应上面是 $p$ 或 $1$，$\frac{j}{\gcd(p,j)}$ 与上面对应一定是 $j$ 或 $\frac{j}{p}$，发现不管怎么样都存在恰好 $1$ 个 $1$，所以两个不等于 $1$ 的值必须相等，那么 $j\gets p^2$ 即可，那么显然 $p\leq \sqrt n$ 的质数都存在 $j$ 满足条件；
- 现在考虑奇数的情况，质数已经证明可以，合数可以选择其最小的质因子 $p$，可以构造 $i-p$，$i$ 即可；

综上，所有合数满足条件，大于 $\sqrt n$ 的质数都不满足，$1$ 不满足，求前缀素数个数 $s_i$ 表示 $1-i$ 的素数个数，答案即为 $s_n-s_{\sqrt n}+1$  

---

## 作者：chaichunyang (赞：1)

题目翻译
 
**题目大意**

我们规定对于两个不同的数字 $a,b$ ,如果$\gcd(a,b)$,$\frac{a}{\gcd(a,b)}$,$\frac{b}{\gcd(a,b)}$可以构成一个三角形,那么 $a,b$ 便是一组好朋友.
我们进一步规定,如果在一个集合中中,有一数字$K$和这个集合中任意一个数字都不是朋友,那么数字 $K$ 就是一个孤独数字.
给定一个包含所有 $1$ 到 $n$ 整数的集合,求在该集合中有多少数字是孤独数字.

**输入输出格式**
第一行输入一个整数 $T$ 表示有 $T$ 组数据.
接下来一行 $T$ 个数字,其中第 $i$ 个数字为$n_{i}$,表示你应解决当$n=n_{i}$时的问题.
你应输出 $T$ 行,第 $i$ 行为当$n=n_{i}$时孤独数字的数量.

**样例解释**
当 $n=1$ 时, $1$ 是集合中唯一的数字,因此它是孤独数字.
当 $n=5$ 时, 孤独数字为$1,3,5$
当 $n=10$ 时, 孤独数字为$1,5,7$
# 解析
首先易得暴力是$O(\sum_{i=1}^{T}{n_{i}^{2}})$的时间来完成的（不计算gcd的时间）
5分钟就可以码出来：（这一份是输出有哪些的
```cpp
#include<bits/stdc++.h>
#define forr(x,y,z) for(int x=y;x<=z;x++)
using namespace std;
int N,T,g;
int gcd(int a,int b){return b==0?a:gcd(b,a%b);}//gcd
bool ch(int a,int b,int c){return (a>b&&a>c)?(b+c>a):((b>c)?(c+a>b):(a+b>c));}//判断△
bool ans[100039];//桶
int main(){
	scanf("%d",&T);
	while(T--){
		memset(ans,0,sizeof(ans));scanf("%d",&N);
		forr(i,1,N)forr(j,1,N){g=gcd(i,j);if(i!=j&&ch(i/g,j/g,g))ans[i]=ans[j]=1;}
		for(int i=1;i<=N;i++)if(!ans[i])printf("%d ",i);printf("\n");
	}
}
```
|输入|输出|
|--|--|
|1|1|
|2|1 2|
|3|1 2 3|
|4|1 3|
|5-6|1 3 5|
|7-8|1 3 5 7|
|9-10|1 5 7|
|11-12|1 5 7 11|
|13-16|1 5 7 11 13|
|17-18|1 5 7 11 13 17|
|19-22|1 5 7 11 13 17 19|
|23-24|1 5 7 11 13 17 19 23|
|25-28|1 7 11 13 17 19 23|
|$……$|$……$|
可以发现：
1. 除了$1$之外，其他数都是质数
2. 每到（或大于）一个质数的平方，这个质数就不在答案里（例如4,9,25）

 总结一下,答案是大于$\sqrt{n_i}$,小于$n_i$的质数的个数
复杂度:
$$O\left(\sum_{i=1}^{T}\left\{{\sum_{j=\sqrt{n_i}}^{n_i}{\sqrt{j}}}\right\}\right)$$

**优化**
给质数一个预处理：
得：
$$O\left(\sum_{i=1}^{T}\left\{n_i-\sqrt{n_i}\right\}+\sum_{i=1}^{1e6}{\sqrt{i}}\right)$$
**优化2**
再来一点前缀和
$$O\left(1e7+T\right)$$
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int N,M,ans,add[1000039];
bool z[1000039];
int main(){
	memset(z,1,sizeof(z));
	for(int i=2;i<=1e6;i++){
		if(z[i]){
			int k=2*i;
			while(k<=1e6){
				z[k]=0,k+=i;
			}
		}
		add[i]=add[i-1]+z[i];
	}
	scanf("%d",&N);
	while(N--){
		scanf("%d",&M);ans=0;
		printf("%d\n",add[M]-add[(int)sqrt(M)]+1);
	}
	return 0;
}
```

---

## 作者：under_the_time (赞：0)

## 题意

> 定义对于一对正整数 $(i,j)$ 是朋友，当且仅当长度分别为 $\gcd(i,j),\cfrac{i}{\gcd(i,j)},\cfrac{j}{\gcd(i,j)}$ 的三条边能够组成三角形。求 $1,2,\cdots,n$ 中有多少数，满足对于数 $x$ 在 $[1,n]$ 中找不到任何一个数使得它们是朋友。多组数据。$n\le 10^6$。

## 思路

首先我们考虑质数 $p$ 的情况。构造几组数据可以发现：$p$ 有朋友当且仅当 $n\ge p^2$。我们对另一个正整数 $x$ 进行讨论：

- 若 $p|x$，那么一定有 $pk=x$，其中 $k$ 为正整数；那么三边长度分别为 $p,1,k$，取 $k=p$ 即 $x=p^2$ 即为最小的合法解。
- 否则，三边长度分别为 $1,p,x$ 且 $x\ne p$，故无解。

于是 $p$ 存在朋友的充要条件为：$n\ge p^2$。接下来讨论合数 $a$ 的情况。我们考虑将它质因数分解：$a=\prod_{i=1}^kp_i^{c_i}$，取出最小的质因子 $p_{\min}$ 后构造 $b=\cfrac{a(p_{\min}-1)}{p_{\min}}$，此时 $(a,b)$ 即为朋友。由于这么构造出的 $b$ 总是 $<a$，所以合数一定有朋友。于是最终答案变为了求 $[\lfloor\sqrt n\rfloor+1,n]$ 中的质数个数。线性筛一下求个前缀和作差就做完了。注意 $1$ 也是没有朋友的。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 5;
int ans[maxn];
int p[maxn], pcnt; bool vis[maxn];
void init() {
    for (int i = 2; i <= maxn - 5; i ++) {
        if (!vis[i])
            p[++ pcnt] = i;
        for (int j = 1; 1ll * i * p[j] <= maxn - 5 && j <= pcnt; j ++) {
            vis[i * p[j]] = 1;
            if (i % p[j] == 0) break;
        }
    }
    for (int i = 2; i <= maxn - 5; i ++)
        ans[i] += ans[i - 1] + (vis[i] ^ 1);
}
int main() {
    init(); int T; scanf("%d", &T);
    while (T --) {
        int n;
        scanf("%d", &n);
        int m = sqrt(n);
        printf("%d\n", ans[n] - ans[m] + 1);
    }
    return 0;
}
```

---

## 作者：Erica_N_Contina (赞：0)




## 思路

 数学结论题。

我们设 $a>b,d=\gcd(a,b)$，并且把三边都乘上一个 $d$ 得 $d^2,a,b$。分情况讨论。

- $a,b$ 互质

我们要优先考虑这种情况，因为这种情况很显然无法构造可行解。虽然这个条件对求解答案没有帮助，但是这样后面我们就不需要讨论这种情况了。

- $d^2>a$

此时我们要满足 $a+b>d^2$，很显然按照约束，$a,b$ 只可以是合数。我们设 $a=k\times d$，很显然可以让 $b=(k-1)\times d$。 

- $d^2\le a$

此时我们要满足 $a<b+d^2$。那么假设 $a=k\times d$，显然如果 $a$ 是合数，我们就可以使得 $b=(k-1)\times d$ 而构造出可行解。证明：$kd<(k-1)d+d^2=(k-1+d)d$。

根据以上的整理，可以得知当 $k$ 是合数时，一定有解。但是若 $k$ 为质数，也不一定无解。

考虑到 $a$ 为质数，$d=1$，这种情况显然找不到解。

考虑 $b$ 为质数，$d$ 可能不为 $1$，这种情况需要考虑。

设 $a=b\times k$，若 $k$ 为整数，那么 $d=b^2$。那么可以得出只有 $a>b(b-1)$ 才行。结合前面的设定，$a\ge b^2$。即若在给定范围内，没有 $k^2$，对于质数 $k$ 才一定无解。

那么统计出值在 $\sqrt n\sim n$ 范围内的质数的个数输出即可。

---

我惊讶于 cf 解除同步流比 `printf` 慢。

```C++
#include<bits/stdc++.h>
#define rep(l,r,i) for(int i=l,END##i=r;i<=END##i;++i)
#define per(r,l,i) for(int i=r,END##i=l;i>=END##i;--i)
using namespace std;
//#define int long long
#define pii pair<int,int>

#define lc(x) (x<<1)
#define rc(x) (x<<1|1)

#define rd read()
inline int read()
{
	int xx=0,ff=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') ff=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') xx=xx*10+(ch-'0'),ch=getchar();
	return xx*ff;
}
inline void write(int out)
{
	if(out<0) putchar('-'),out=-out;
	if(out>9) write(out/10);
	putchar(out%10+'0');
}

const int N=1e6+15;
//const int INF=1e18+5;
const int MOD=998244353;
int ans,m;
int f;
int a,b,qzh[N],len,T,n;
int prime[N],notprime[N];
int tot;

void init(){
	notprime[1]=1;
	for(int i=2;i<N;i++){
		if(notprime[i])continue;
		prime[++tot]=i;
		for(int j=2;j*i<N;j++)notprime[i*j]=1;
	}
	
	for(int i=1;i<N;i++)qzh[i]=qzh[i-1]+(notprime[i]==0);
}

signed main(){
	init();
	
    int T=rd;
    while(T--){
    	n=rd;
    	printf("%d\n",qzh[n]-qzh[(int)sqrt(n)]+1);
	}
    return 0;
}

```





---

## 作者：fanfansann (赞：0)

CF1423K Lonely Numbers（思维，分类讨论）（1600）

**Problem**

我们规定对于两个不同的数字 $a,b$ ，如果 $\gcd(a,b),\dfrac{a}{\gcd(a,b)},\dfrac{b}{\gcd(a,b)}$  可以构成一个三角形,那么 $a,b$ 便是一组好朋友。

我们进一步规定，如果在一个集合中，有一数字 $k$ 和这个集合中任意一个数字都不是朋友，那么数字 $k$ 就是一个孤独数字。

给定一个 **包含所有 $1$ 到 $n$ 整数的集合** ，求在该集合中有多少数字是孤独数字。

**Solution**

能组成三角形，显然有任意两边之和大于第三边，即：

$$\begin{aligned}a + \gcd(a, b)^2 > b\\
a + b > \gcd(a, b)^2\\
b + \gcd(a, b)^2>a\end{aligned}$$

 得：
 $$
 a - b < \gcd(a, b)^2 < a + b
 $$
$\gcd$ 相关的问题显然考虑按照 ： **偶合数，偶质数(2)，奇质数，奇合数，1**   进行分类讨论。

- **偶合数**
若 $a$ 是偶数，显然任意两个相邻的偶数的 $\gcd$ 都是 $2$，所以我们可以找到与 $a$ 相邻的偶数，即 $a+2$ 或 $a-2$，（若$a=a+2$则 $b=a$） $a - b < \gcd(a, b)^2 < a + b\Rightarrow2<4<(2a±2\ge6)$，即所有的偶数一定能找到另一个数与之形成三角形。 

- **偶质数（$2$）**
显然这里 $2$ 也一定成立 。 

- **奇质数**
$a$ 为质数，与除自己倍数以外的所有的数的 $\gcd$ 均为 $1$ ，显然不能构成三角形，除此之外，自己的倍数，需要满足的条件为 $\gcd(x,a)^2=a^2<(x+1)a$，显然 $x>a-1$，即 $x$ 最小取 $a$，所以为了满足条件：$a^2 - a < a^2 < a^2 + a$，$\{a,a^2\}$ 是一组能组成三角形的解，除此之外的奇质数一定是孤独数。  
- **奇合数**
若 $a$ 为合数，显然 $a=p_1^{\alpha_1}p_2^{\alpha_2}\cdots$，我们只需要选择唯一分解式中的最小的 $p$，令 $a=p\times x$，显然 $\{a±p,a\}$ 能组成三角形，即：$a + p - a < (\gcd(a+p,a)=p)^2=p^2 < 2a+p$，故奇合数一定不是孤独数。 
- **1**
显然 $1$ 与任意数的 $\gcd$ 均为 $1$，所以一定是孤独数。


综上所诉：我们只需要计算 $1\sim n$ 中有多少个质数，以及满足在 $1\sim n$ 中有 $p^2$ 的质数的个数，即 $1\sim \sqrt n$ 中有多少个质数，我们显然可以直接预处理出所有的质数个数数组 $num$，最终的答案为：$ans=num[n] - num[\sqrt n)]+1$。（加 $1$ 是因为 $1$ 也是答案）

**Code**

```cpp
// Problem: K. Lonely Numbers
// Contest: Codeforces - Bubble Cup 13 - Finals [Online Mirror, unrated, Div. 1]
// URL: https://codeforces.com/problemset/problem/1423/K
// Memory Limit: 256 MB
// Time Limit: 1500 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e6 + 7;

int n, m, t;
int primes[maxn], cnt, num[maxn];
bool vis[maxn];

void init(int n)
{
	vis[1] = 1;
	for(int i = 2; i <= n; ++ i) {
		if(vis[i] == 0) {
			primes[ ++ cnt] = i;
			num[i] = 1;
		}
		for(int j = 1; j <= cnt && i * primes[j] <= n; ++ j) {
			vis[i * primes[j]] = 1;
			if(i % primes[j] == 0) break;
		}
	}
	for(int i = 1; i <= n; ++ i) {
		num[i] += num[i - 1];
	}
}

int main()
{
	init(maxn - 7);
	scanf("%d", &t);
	while(t -- ) {
		scanf("%d", &n);
		int down = floor(sqrt(n)); 
		printf("%d\n", num[n] - num[down] + 1);
	}
	return 0;
}
```


---

