# Paper Cutting Again

## 题目描述

There is a rectangular sheet of paper with initial height $ n $ and width $ m $ . Let the current height and width be $ h $ and $ w $ respectively. We introduce a $ xy $ -coordinate system so that the four corners of the sheet are $ (0, 0), (w, 0), (0, h) $ , and $ (w, h) $ . The sheet can then be cut along the lines $ x = 1,2,\ldots,w-1 $ and the lines $ y = 1,2,\ldots,h-1 $ . In each step, the paper is cut randomly along any one of these $ h+w-2 $ lines. After each vertical and horizontal cut, the right and bottom piece of paper respectively are discarded.

Find the expected number of steps required to make the area of the sheet of paper strictly less than $ k $ . It can be shown that this answer can always be expressed as a fraction $ \dfrac{p}{q} $ where $ p $ and $ q $ are coprime integers. Calculate $ p\cdot q^{-1} \bmod (10^9+7) $ .

## 说明/提示

For the first test case, the area is already less than $ 10 $ so no cuts are required.

For the second test case, the area is exactly $ 8 $ so any one of the $ 4 $ possible cuts would make the area strictly less than $ 8 $ .

For the third test case, the final answer is $ \frac{17}{6} = 833\,333\,342\bmod (10^9+7) $ .

For the fourth test case, the final answer is $ \frac{5}{4} = 250\,000\,003\bmod (10^9+7) $ .

## 样例 #1

### 输入

```
4
2 4 10
2 4 8
2 4 2
2 4 6```

### 输出

```
0
1
833333342
250000003```

# 题解

## 作者：EuphoricStar (赞：20)

印度出题人玩[原](https://www.luogu.com.cn/problem/AT_arc114_e)神玩的吧？？？

考虑计算每条折线被选的概率。考虑相当于是有一个 $1 \sim n + m - 2$ 的排列 $p$，然后一条 $x = i$ 的直线被选且不是最后一个被选的，当且仅当它在 $p$ 中排在 $x = 1 \sim i - 1$ 和 $y = 1 \sim \left\lfloor\frac{k}{i}\right\rfloor$ 之前。$y = i$ 则类似。

一个 $1 \sim N$ 的排列中，$M$ 个数中一个数在其他 $M - 1$ 个数前面的概率是 $\frac{1}{M}$。于是我们能很轻松地枚举每条 $x = i$ 和 $y = i$ 的直线计算答案。总时间复杂度 $O(n + m)$。

[code](https://codeforces.com/contest/1924/submission/243756415)

---

## 作者：xuanxuan001 (赞：5)

虽然官方还没出题解，但扫了眼代码感觉我的做法貌似比官方题解简单，所以发篇题解。

又是阴间场，B 的线段树 pushdown 写错了一个变量然后 WA #10 硬瞪了二十分钟还无脑交了两发，但至少没 fst。感觉如果跳过 BD 写个 ACE 都能上大分，但在赛场上又怎么预料得到呢。

发现切割的过程可以转换为从位置 $(n,m)$ 一直走直到位置 $(x,y)$ 满足 $xy < k$ 为止需要移动的期望步数，移动方式是每次等概率走到它正下面（即只有 $x$ 变小）和正右边（即只有 $y$ 变小）的所有点中的一个。

可以将期望步数转换为对于所有 $(x,y)$ 满足 $x \le n,y \le m,xy \ge k$ 的位置，经过 $(x,y)$ 的概率求和。

先不考虑复杂度的问题，考虑对所有的 $1 \le X \le n$ 且 $1 \le Y \le m$ 求出经过 $(X,Y)$ 的概率 $P(X,Y)$。

需要分为下面几种情况讨论：

1. $X=n$ 且 $Y=m$，就是初始位置，概率为 $1$。
2. $X<n$ 且 $Y=m$，考虑点移动的过程，如果 $y$ 减小了那就寄了，所以只能是 $x$ 减小，那么继续分讨减小后的 $x$：
	1. $x>X$，那么继续减小。
	2. $x=X$，那么就经过了目标位置。
	3. $x<X$，寄了。

   所以综合以上的分讨，发现只需要考虑第一次 $x \le X$ 的时候或者 $y$ 减小时 $x$ 的取值即可，发现此时有 $X+m-1$ 种可能（需要将 $y$ 减小的情况也考虑在内），其中只有一种会经过，所以得到 $P(x,y) = \dfrac 1{X+m-1}$。当然对于数学直觉较好或见过类似问题的选手来说可以不需要很严谨的推导并得出结论。
3. $X=n$ 且 $Y<m$，与上面类似，$P(X,Y) = \dfrac 1{Y+n-1}$
4. $X<n$ 且 $Y<m$，发现这类情况比较复杂，并不是简单的 $\dfrac 1{X+Y-1}$（我按这个手模样例发现过不去），需要先考虑第一次走到 $x=X$ 或 $y=Y$ 时再转换成 2 或 3 的讨论。

	与 2 和 3 的讨论类似，发现如果一次移动后依然满足 $x>X$ 且 $y>Y$ 就可以不考虑，那么排除掉那些情况后就只有下面这些可能：
	1. 减少 $x$ 并且 $x=X$ ，进入下一步分讨。
	2. 减少 $x$ 并且 $x<X$ ，寄。
	3. 减少 $y$ 并且 $y=Y$ ，进入下一步分讨。
	4. 减少 $y$ 并且 $y<Y$ ，寄。

	那么上面总共的方案数有 $X+Y$ 种，其中能转换为 2 和 3 的情况的只有 $2$ 种，发现转换后的概率与前面独立，所以最终的概率就是两步的概率的乘积 $P(X,Y) = \dfrac 2{(X+Y)(X+Y-1)}$。

可以手模样例以辅助理解，样例（$n = 2,m = 4$）的 $P$ 如下：

$P(2,4) = 1,P(2,3) = \dfrac 14,P(2,2) = \dfrac 13,P(2,1) = \dfrac 12$

$P(1,4) = \dfrac 14,P(1,3) = \dfrac 16,P(1,2) = \dfrac 13,P(1,1) = 1$

然后考虑复杂度的问题，由于题目保证了 $\sum n,\sum m \le 10^6$，所以前面三类情况直接暴力计算都是可以接受的，但第四类有 $(n-1)(m-1)$ 个点，不能直接枚举。

但是发现第四类中 $P(X,Y)$ 只和 $X+Y$ 的值有关，并且这个值只有 $O(n+m)$ 种可能的取值，所以可以考虑枚举这个值并计算有多少个位置要被计入答案。

确定了 $N=X+Y$ 后只需要再确定 $X$ 就能确定唯一的位置，首先要让这个位置 $(X,N-X)$ 在矩形内，这可以确定 $X$ 的一个取值范围 $[l,r]$。

然后还需要保证 $X(N-X) \ge k$，可以转换成二次函数 $-X^2 + NX - k \ge 0$ 并解出它的解集，事实证明直接用浮点数不会爆精度。

将这两个区间取交后即可得到有多少个值会被计入，[AC记录](https://codeforces.com/contest/1924/submission/243699222)，感觉没啥好注释的。

---

## 作者：Leasier (赞：2)

不难把题意转化为：

- 一开始位于 $(n, m)$。
- 每次可以走到 $\forall 1 \leq i < n, (i, m)$ 和 $\forall 1 \leq i < m, (n, i)$。
- 走到满足 $xy < k$ 的 $(x, y)$ 时停止。
- 求停止前期望走了几步。

首先判掉 $nm < k$ 的情况。

设 $E(x, y)$ 表示现在位于 $(x, y)$，期望走几步后停止。

当 $xy < k$，$E(x, y) = 0$；否则，$E(x, y) = \dfrac{\displaystyle\sum_{i = 1}^{x - 1} E(i, y) + \sum_{i = 1}^{y - 1} E(x, i)}{x + y - 2} + 1$。

直接前缀和优化可以做到 $O(\sum nm)$，但显然不能通过。

考虑算贡献，即对于每个 $(x, y)$，计算经过它的概率。

设 $P(x, y)$ 表示从 $(n, m)$ 出发经过 $(x, y)$ 的概率。

- $P(n, m) = 1$。
- $\mathcal{A}$：当 $1 \leq x < n, xm \geq k$，$P(x, m) = \displaystyle\sum_{i = x + 1}^n \dfrac{P(i, m)}{i + m - 2}$，可利用裂项归纳证明 $P(x, m) = \dfrac{1}{x + m - 1}$。
- $\mathcal{B}$：当 $1 \leq y < m, ny \geq k$，同理可得 $P(n, y) = \dfrac{1}{n + y - 1}$。
- $\mathcal{C}$：当 $1 \leq x < n, 1 \leq y < m, xy \geq k$，可类似地利用裂项归纳证明 $P(x, y) = \dfrac{2}{(x + y)(x + y - 1)}$。

对于 $\mathcal{A}, \mathcal{B}$，直接枚举 $x, y$ 即可。

对于 $\mathcal{C}$，注意到贡献只与 $x + y$ 有关，枚举其后不难解二次方程求出 $x$ 的范围。

预处理逆元即可。时间复杂度为 $O(\sum(n + m))$。

代码：
```cpp
#include <stdio.h>
#include <math.h>

typedef long long ll;

const int N = 2e6, mod = 1e9 + 7;
int inv[N + 7];

inline void init(){
	inv[0] = inv[1] = 1;
	for (register int i = 2; i <= N; i++){
		inv[i] = mod - 1ll * (mod / i) * inv[mod % i] % mod;
	}
}

inline void add(int &x, int y){
	if ((x += y) >= mod) x -= mod;
}

inline int max(int a, int b){
	return a > b ? a : b;
}

inline int min(int a, int b){
	return a < b ? a : b;
}

int main(){
	int t;
	scanf("%d", &t);
	init();
	for (register int i = 1; i <= t; i++){
		int n, m;
		ll k;
		scanf("%d %d %lld", &n, &m, &k);
		if ((ll)n * m < k){
			printf("0\n");
			continue;
		}
		int up = n + m - 2, ans = 1;
		for (register int j = n - 1; (ll)j * m >= k; j--){
			add(ans, inv[j + m - 1]);
		}
		for (register int j = m - 1; (ll)n * j >= k; j--){
			add(ans, inv[n + j - 1]);
		}
		for (register int j = 2; j <= up; j++){
			ll delta = (ll)j * j - k * 4;
			if (delta >= 0){
				int l, r;
				double x = sqrt(delta);
				l = max((int)ceil((j - x) / 2.0), max(j - m + 1, 1));
				r = min((int)((j + x) / 2.0), min(j + 1, n - 1));
				if (l <= r) add(ans, 2ll * inv[j] % mod * inv[j - 1] % mod * (r - l + 1) % mod);
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
```

---

## 作者：NaCly_Fish (赞：2)

[题目链接](https://codeforces.com/contest/1924/problem/E)  

今天随便看到这题，就来口胡一下做法。
****

首先对于 $nm\geq k$ 有一个显然的 DP，设答案为 $f_{n,m}$：
$$(n+m-2)(f_{n,m}-1)=\left(\sum_{i=0}^{n-1}f_{i,m}\right)+\left( \sum_{i=0}^{m-1}f_{n,i}\right)\quad \texttt{(1)}$$
而对于 $nm<k$ 的地方取值为零，现在要考虑优化这个 DP。
****
尝试对 $n,m$ 方向上各做一次差分，就可以发现对于**充分大**的 $nm$ 有
$$f_{n,m}=f_{n-1,m}+f_{n,m-1}-f_{n-1,m-1} \quad \texttt{(2)}$$
说是充分大，实际上只要 $n,m$ 在包围 $nm<k$ 区域的**轮廓线**（轮廓线上的点本身有 $nm\geq k$）之外就有这个式子。如 $n=23,m=15$ 时，设 $a_{i,j}$ 表示 $\texttt{(2)}$ 是否成立（成立为 $0$，不成立为 $1$）就得到了轮廓线：

```
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 1 1 1 1 1 1 
0 0 0 0 0 0 0 0 1 1 1 1 1 1 1 1 1 0 0 0 0 0 0 
0 0 0 0 0 1 1 1 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
0 0 0 0 1 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
0 0 0 1 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
0 0 1 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
0 1 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
```


固定 $k$，则答案的生成函数可以表示为这种形式

$$F(x,y)=(x+y-xy)F(x,y)+R(x,y)$$
这里 $R$ 就是一个补误差的项，顾及 $\texttt{(2)}$ 不成立的情况。
也是一个二元幂级数，它只在**轮廓线**上的取值可能非零（因为 $nm<k$ 的位置本身都是 $0$，做差分当然还是 $0$，没有影响）。设轮廓线的点集为 $S_k$，则
$$R(x,y)=\sum_{(i,j)\in S_k}[i\leq n][j\leq m](f_{i,j}-f_{i-1,j}-f_{i,j-1}+f_{i-1,j-1})x^iy^j$$
容易发现其只有 $\Theta(n+m)$ 项，要提取 $F$ 的 $x^ny^m$ 系数，就只需要对若干连续的点 $i,j$ 求出
$$[x^iy^j]\frac{1}{1-(x+y-xy)}$$
这个东西是什么？因为 $1-(x+y-xy)=(1-x)(1-y)$，所以它总是 $1$（对于自然数 $i,j$）。答案就是 $R(1,1)$。

至于轮廓线上的点怎么求 $f$ 值，直接用 $\texttt{(1)}$ 计算就可以。不过要注意使用前缀和优化一下。

回来补个代码，实现细节还是稍有点麻烦的：
```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<vector>
#define N 2000003
#define ll long long
#define p 1000000007
using namespace std;

int inv[N];

void init(int n){
    inv[1] = 1;
    for(int i=2;i<=n;++i) inv[i] = (ll)(p-p/i)*inv[p%i]%p;
}

ll ans,k;
int n,m;
vector<int> fr[N>>1];
int st[N],len[N]; 

inline int F(const int& i,const int& j){
	if(j<st[i]||j-st[i]>=fr[i].size()) return 0;
	return fr[i][j-st[i]];
}

inline int G(const int& i,const int& j){
	return F(i,j)-F(i-1,j)-F(i,j-1)+F(i-1,j-1);
}

int main(){
    init(2000000);
    int T,px,py;
	scanf("%d",&T);
	while(T--){
		scanf("%d%d%lld",&n,&m,&k);
		if((ll)n*m<k){
			puts("0");
			continue;
		}
		if((ll)n*m==k){
			puts("1");
			continue;
		}
		if(n<m) swap(n,m);
		int fir = (k%n==0?k/n:k/n+1);
		st[fir-1] = n,ans = 0;
		for(int i=fir;i<=m;++i){
			st[i] = k%i==0?k/i:k/i+1; // 确定轮廓线在当前行的起始位置
			int L = st[i-1]-st[i]+1,sum = 0;
			fr[i].resize(L);
			if(st[i]<i){ // 利用对称性简化计算
				px = i,py = st[i];
				fr[i][0] = F(py,px);
			}else fr[i][0] = 1;
			sum = fr[i][0],ans += G(i,st[i]);
			for(int j=1;j<L-1;++j){
				fr[i][j] = (ll)sum*inv[i+j+st[i]-2]%p+1;
				ans += G(i,j+st[i]);
				sum = (sum+fr[i][j])%p;
			}
			if(L==1) continue;
			if(L+st[i]>=i){  // 同样利用对称性
				for(int j=1;;++j){
					px = L-1+st[i]-st[i-j];
					if(px>=fr[i-j].size()||px<0) break;
					sum = (sum+fr[i-j][px])%p;
				}
				fr[i][L-1] = (ll)sum*inv[i+L+st[i]-3]%p+1;
			}else{
				px = i,py = L-1+st[i];
				fr[i][L-1] = fr[py][px-st[py]];
			}
			ans += G(i,L-1+st[i]);
		}
		for(int i=fir;i<=m;++i) fr[i].clear();
		printf("%lld\n",(ans%p+p)%p);
	}
    return 0; 
}
```

---

## 作者：123456xwd (赞：1)

[[CF1924E] Paper Cutting Again](https://www.luogu.com.cn/problem/CF1924E)

首先，若 $n\times m<k$，则期望为 0。

根据期望的线性，总期望值其实就为每一个线被选的概率之和（再次选了一个就是一次操作）。

我们若考虑这条折线为最后一次被选的，特别麻烦，不如考虑它不是最后一次被选的期望，而最后一个线被选对期望的贡献为 1。

我们考虑横线 $i$，设 $j=\lfloor\frac{k-1}{i}\rfloor$，若它可以被当作非最后一条线被选，则代表左下角为 $(0,0)$，右下角为 $(i,j)$ 的这个矩形以内的线都没被选过，概率就是 $\frac{1}{i+j}$。（注意，若 $j\ge m$，则他不可以被选，因为此时若计算的话会把边界以及边界外面也算进去）。

竖线也同理。

代码：
```c++
#include<bits/stdc++.h>
#define int long long 
using namespace std;

const int N=2e6+5,mod=1e9+7;
int inv[N];
int n,m,k;
signed main(){
	inv[1]=1;
	for(int i=2;i<N;i++){
		inv[i]=inv[mod%i]*(mod-mod/i)%mod;	
	}	
	int T;
	scanf("%lld",&T);
	while(T--){
		scanf("%lld%lld%lld",&n,&m,&k);
		if(n*m<k){
			puts("0");
			continue;
		}
		k--;
		int ans=1;//最后一次选
		for(int i=1,j;i<n;i++){
			j=floor((double)k/i);
			if(j>=m) continue;
			ans=(ans+inv[i+j])%mod;
		}
		for(int i=1,j;i<m;i++){
			j=floor((double)k/i);
			if(j>=n) continue;
			ans=(ans+inv[i+j])%mod;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：Aigony (赞：1)

每步都不会系列。

根据期望的线性性，从 $n\times m$ 操作到结束的期望次数等于每个 $x\times y$ 的矩形在过程中出现的概率之和。  
问题变成了怎么算 $x\times y$ 在过程中出现的概率。

在研究这个前，先考虑一维的情况怎么算：

> 给一个长度为 $n$ 的线段，每次在 $n-1$ 个位置中随机一个切开，保留左半部分。求过程中线段长为 $x$ 出现的概率。

上面的随机方式等价于给 $n-1$ 个位置随机赋上互不相同的权值 $p_i$，每次挑剩下的段中权值最小的位置切开。那么第 $x$ 个位置恰好被切开的充要条件即为 $p_1,\dots,p_{x-1}$ 均大于 $p_x$，易知这个概率为 $\frac{1}{x}$。

回到本题，我们令横线和竖线的权值构成长为 $n+m-2$ 的排列，并分别考虑贡献。  
设现在正在考虑横线 $i$，那么它会被切的条件是前 $i-1$ 条横线、前 $\lfloor \frac{k}{i}\rfloor$ 条竖线的权值均大于它。概率为 $\dfrac{1}{i+\lfloor \frac{k}{i}\rfloor}$。

枚举每条线求和即可，预处理逆元可以做到单次时间复杂度 $\mathcal{O}(n+m)$。

---

