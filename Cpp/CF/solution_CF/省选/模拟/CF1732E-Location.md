# Location

## 题目描述

You are given two arrays of integers $ a_1, a_2, \ldots, a_n $ and $ b_1, b_2, \ldots, b_n $ . You need to handle $ q $ queries of the following two types:

- $ 1 $ $ l $ $ r $ $ x $ : assign $ a_i := x $ for all $ l \leq i \leq r $ ;
- $ 2 $ $ l $ $ r $ : find the minimum value of the following expression among all $ l \leq i \leq r $ : $ $$$\frac{\operatorname{lcm}(a_i, b_i)}{\gcd(a_i, b_i)}. $ $ </li></ul><p>In this problem  $ \\gcd(x, y) $  denotes the <a href="https://en.wikipedia.org/wiki/Greatest_common_divisor">greatest common divisor</a> of  $ x $  and  $ y $ , and  $ \\operatorname{lcm}(x, y) $  denotes the <a href="https://en.wikipedia.org/wiki/Least_common_multiple">least common multiple</a> of  $ x $  and  $ y$$$.

## 说明/提示

In the first example:

- For the first query we can choose $ i = 4 $ . So the value is $ \frac{\operatorname{lcm}(4, 4)}{\gcd(4, 4)} = \frac{4}{4} = 1 $ .
- After the second query the array $ a = [6, 10, 15, 4, 9, 25, 9, 9, 9, 9] $ .
- For the third query we can choose $ i = 9 $ . So the value is $ \frac{\operatorname{lcm}(9, 18)}{\gcd(9, 18)} = \frac{18}{9} = 2 $ .

In the second:

- For the first query we can choose $ i = 4 $ . So the value is $ \frac{\operatorname{lcm}(1, 5)}{\gcd(1, 5)} = \frac{5}{1} = 5 $ .
- After the second query the array $ a = [10, 18, 18, 5] $ .
- After the third query the array $ a = [10, 10, 18, 5] $ .
- For the fourth query we can choose $ i = 2 $ . So the value is $ \frac{\operatorname{lcm}(10, 12)}{\gcd(10, 12)} = \frac{60}{2} = 30 $ .

## 样例 #1

### 输入

```
10 10
6 10 15 4 9 25 2 3 5 30
1 2 3 4 6 9 12 15 18 30
2 1 10
1 7 10 9
2 5 10
1 1 6 14
2 4 7
2 3 9
1 2 9 30
2 1 4
2 3 7
2 5 10```

### 输出

```
1
2
12
2
10
5
2```

## 样例 #2

### 输入

```
4 4
10 2 12 5
1 12 16 1
2 2 4
1 2 3 18
1 2 2 10
2 2 3```

### 输出

```
5
30```

# 题解

## 作者：JackF (赞：10)

注意到 $n,q$ 范围很小，考虑对序列分块。

设块长为 $B$，要对 $\frac{n}{B}$ 个块维护每个块中 $\frac{\operatorname{lcm}(a_i,b_i)}{\gcd(a_i,b_i)}$ 的最小值。

整块修改：当一个块内的 $a_i$ 全部被赋值为 $v$，相当于需要快速找到 $\frac{\operatorname{lcm}(v,b_i)}{\gcd(v,b_i)}$ 的最小值。先对于每个块都预处理出 $mn_{d}$ 表示该块内最小的 $b_i$ 满足 $d\mid b_i$。枚举 $d=\gcd(v,b_i)$，取最小的 $\frac{mn_d\cdot v}{d^2}$ 即可。  
上述做法在未知 $b_i$ 的情况下无法确定 $d$ 为 $\gcd(v,b_i)$ 还是 $\gcd(v,b_i)$ 的约数，但是把 $\gcd$ 当作小的不会使得答案更小，因此不影响正确性。

散块暴力修改即可，查询平凡。

时间复杂度为 $O(n\max d(V)+q(\frac{n}{B}\max d(V)+B\cdot \gcd))$，$d(V)$ 在 $V=45360$ 时取到最大 $100$，实测 $B=550$ 时跑得较快。

**优化常数：**

+ 运用 [基于值域预处理的快速 GCD](https://www.luogu.com.cn/problem/P5435) 中的套路，可以 $O(1)$ 求 $\gcd$。
+ 运算乘法的时候最大是 $50000^2$，用 $\text{unsigned int}$ 而不是 $\text{long long}$。

---

## 作者：喵仔牛奶 (赞：3)

看到操作一，考虑颜色段均摊，每个段维护段内 $\frac{\operatorname{lcm}(a_i,b_i)}{\gcd(a_i,b_i)}$ 的最小值。查询时，整段直接线段树维护最小值，散段最多只会跨越两个，需要散段查最小值，且区间推平需要更新最小值，问题便可以转换：
- 给定 $\{b_n\}$，每次查询给定 $l,r,x$，求 $\min\limits_{l\leq i\leq r}\{\frac{\operatorname{lcm}(x,b_i)}{\gcd(x,b_i)}\}$。

$\min\limits_{l\leq i\leq r}\{\frac{\operatorname{lcm}(x,b_i)}{\gcd(x,b_i)}\}=x\times\min\limits_{l\leq i\leq r}\{\frac{b_i}{\gcd(x,b_i)^2}\}$，令 $d=\gcd(x,b_i)$，原式化为 $x\times\min\limits_{l\leq i\leq r\land d|x\land d|b_i}\{\frac{b_i}{d^2}\}$。

事实上，$d$ 可能不为 $\gcd(x,b_i)$ 而是它的约数，但是这样肯定不是最优的。因为 $d$ 作为分子，$d$ 越大原式越小。不是最大公约数求出的值比是最大公约数求出的值要大，肯定不优。

问题变为求 $\min\limits_{l\leq i\leq r\land d|x\land d|b_i}\{\frac{b_i}{d^2}\}$。发现可以离线，于是枚举所有 $d|x$，将其离线，按 $d$ 扫描线处理询问。设当前枚举到 $d$，则处理出所有 $d|b_i$ 的 $b_i$，问题变成了 RMQ。那么把 $d|b_i$ 的 $b_i$ 放入线段树，然后处理询问，再将 $d|b_i$ 的 $b_i$ 删去。所有 $d$ 中 $b_i$ 的个数为 $\sum_{i=1}^{n}\sigma(b_i)$（$\sigma(x)$ 为 $x$ 的约数个数），不会很大。

然后将离线求出的答案带入，再跑一遍颜色段均摊+线段树即可。

时间复杂度 $\mathcal{O}((n+q)d\log n)$，$d=\max\limits_{1\leq i\leq V}\{\sigma(i)\}$，空间复杂度 $\mathcal{O}(qd)$。

---

## 作者：imsaileach (赞：2)

## **警告&题外话**

赛时看都没看这道题，赛后看感觉还行。

（~~虽然这题我两个小时写不完，TLE十几次~~）

**此题偏难，代码难度较大（对于我的方法），建议评黑，不建议没做完 [数列分块入门九道](https://www.luogu.com.cn/blog/Rong7/post-tui-jian-loj-fen-kuai-shuo-lie-fen-kuai-ru-men-18-post) 的人做，因为不会讲分块基本操作。**

如果有更好方法的不要嘲讽我。

如果发现我方法正确性与时空复杂度有误的请私聊。~~（免得丢脸）~~


------------


## **题意**

见翻译。


------------


## **思路**

分析操作的可实现性和数据范围，凭借做题经验，我们可以初步估计此题采用分块是最合适的。

Codeforces 评论区中也有更快的做法，好像是线段树，我也想讲，可惜我不会。

如何分块？我们会发现根据题目要求，对于分块中整体处理的块，我们必须 $O(1)$ 解决，但修改操作是区间赋值，怎么办？

### $ 1 \leq x,a_i,b_i \leq 5 \cdot 10^4 $

实际上，此题的值域全是 $5\times 10^4$，设 $W$ 表示 $a_i$ 的最大取值，则遍历全体整数可能值与所有块的总时间复杂度可表示为 $O(W \cdot \sqrt{n})$，而不会超时。

这个条件给了我们启发——如果可以将每个块中整体赋给 $a_i$ 每种可能值时整个块查询的最小值预处理出来，那么就可以对分块中整体处理的块 $O(1)$ 解决。

这又如何做？

首先，此题求：

### $\min\limits_{i \in [l,r]}\frac{\operatorname{lcm}(a_i,b_i)}{\gcd(a_i,b_i)}$

我们会发现把分母从 $\gcd(a_i,b_i)$ 换成 $a_i,b_i$ 的任何一个公因数然后取 $\min$，那么最小的结果仍然是 $\frac{\operatorname{lcm}(a_i,b_i)}{\gcd(a_i,b_i)}$。

所以我们尝试先走弯路，考虑枚举一个块中所有 $b_i$ 的所有因子，将其存入一个大小为 $5 \times 10 ^ 4$ 的有序数对桶中（因子为下标，（$b_i/$ 因子，因子）成为有序数对作为其中值），然后用类似线性筛的思路向上找倍数对其关于自身的有序数对取 $\min$ 更新桶中当前值，大小比较的方式为：

对于两个有序数对 $(A,B)(C,D)$

若满足：$\frac{A}{B} \leq \frac{C}{D}$

即：$A \cdot D \leq B \cdot C$

则称 $(A,B) \leq (C,D)$

认真思考，对于一个更新完毕的有序数对桶：

### $ton_{first/second}$

计算对于一个可能的整数 $i$ 赋值给整个块的 $a_i$，那么此时整个块查询的最大值即为：

# $\frac{i \cdot ton_{i_{first}}}{ton_{i_{second}}}$

由此，我们将每个块中整体赋给 $a_i$ 每种可能值时整个块查询的最大值预处理出来了，设 $W$ 表示 $a_i$ 最大取值，则单块时间复杂度 $O(W + \log_{2}{n} \cdot \sqrt{n})$。

所以预处理总时间复杂度 $O(W \cdot \sqrt{n} + n \cdot \log_{2}{n})$，剩下的就是分块基本操作，如果不会可以先练[数列分块入门九道](https://www.luogu.com.cn/blog/gnorc/post-tui-jian-loj-fen-kuai-shuo-lie-fen-kuai-ru-men-18-post) 。

~~（推销博客中）~~

此题常数较大，建议加：

### 火车头，超级快读，快输，以及其他卡常技艺。


------------


## 代码
```cpp
//火车头略
#include <bits/stdc++.h>
#include <immintrin.h>
using namespace std;
#define int unsigned int
int n, Q, a[50005], b[50005], Typ, L, R, X, prime[50005], cnt;
int sq, len, block[50005], bl[505], br[505], bmin[505], bcg[505], bres[505][50005], pl;
long long minn[50005], tlp[50005];
bool ton[50005], not_prime[50005];
vector < int > fac[50005];
static char buf[1000000], * p1 = buf, * p2 = buf;
#define getchar() p1 == p2 && (p2 = (p1 = buf) + fread (buf, 1, 1000000, stdin), p1 == p2) ? EOF : * p1 ++
inline int read()
{
	register int x = 0;
	register char c = getchar ();
	while (c < '0' || c > '9') c = getchar ();
	while (c >= '0' && c <= '9') x = (x << 1) + (x << 3) + (c ^ 48),c = getchar ();
	return x;
}
void inline print (register int a){
	if (a < 0){
		putchar ('-');
		a = - a;
	}
	if (a < 10)
		putchar (a ^ 48);
	else {
		print (a / 10);
		putchar ((a % 10) ^ 48);
	}
}
inline int gcd (register int i, register int j){
	if (j == 0)
		return i;
	return gcd (j, i % j);
}
void inline push_d (register int i){
	if (bcg[i]){
		for (register int j = bl[i];j <= br[i];++ j)
			a[j] = bcg[i];
		bcg[i] = 0;
	}
}
void inline push_u (register int i){
	bmin[i] = INT_MAX;
	for (register int j = bl[i];j <= br[i];++ j){
		pl = gcd (a[j], b[j]);
		bmin[i] = min (bmin[i], a[j] / pl * b[j] / pl);
	}
}
void inline Build (){
	len = 100;
	sq = n / len;
	while (sq * len < n)
		++ sq;
	for (register int i = 1;i <= sq;++ i){
		for (register int j = 1;j <= 5e4;++ j){
			minn[j] = 5e9;
			tlp[j] = j;
			ton[j] = false;
		}
		bl[i] = br[i - 1] + 1;
		br[i] = min (n, bl[i] + len - 1);
		push_u (i);
		for (register int j = bl[i];j <= br[i];++ j){
			block[j] = i;
			if (! ton[b[j]]){
				ton[b[j]] = true;
				for (register int k = 0;k < (int) fac[b[j]].size ();++ k)
					minn[fac[b[j]][k]] = min (minn[fac[b[j]][k]], 1ll * b[j] / fac[b[j]][k]);
			}
		}
		for (register int j = 1;j <= 5e4;++ j){
			bres[i][j] = j / tlp[j] * minn[j];
			for (register int k = 1;k <= cnt && j * prime[k] <= 5e4;++ k)
				if (1ll * minn[j * prime[k]] * tlp[j] > 1ll * minn[j] * tlp[j * prime[k]]){
					minn[j * prime[k]] = minn[j];
					tlp[j * prime[k]] = tlp[j];
				}
		}
	}
}
void inline Update (register int l, register int r, register int x){
	push_d (block[l]);
	for (register int i = l;i <= min (br[block[l]], r);++ i)
		a[i] = x;
	push_u (block[l]);
	for (register int i = block[l] + 1;i < block[r];++ i){
		bcg[i] = x;
		bmin[i] = bres[i][x];
	}
	if (block[l] == block[r])
		return ;
	push_d (block[r]);
	for (register int i = bl[block[r]];i <= r;++ i)
		a[i] = x;
	push_u (block[r]);
}
inline int Query (register int l, register int r){
	register int Ans = INT_MAX * 2ll - 1;
	push_d (block[l]);
	for (register int i = l;i <= min (br[block[l]], r);++ i){
		pl = gcd (a[i], b[i]);
		Ans = min (Ans, a[i] / pl * b[i] / pl);
	}
	for (register int i = block[l] + 1;i < block[r];++ i)
		Ans = min (Ans, bmin[i]);
	if (block[l] == block[r])
		return Ans;
	push_d (block[r]);
	for (register int i = bl[block[r]];i <= r;++ i){
		pl = gcd (a[i], b[i]);
		Ans = min (Ans, a[i] / pl * b[i] / pl);
	}
	return Ans;
}
signed main (){
	for (register int i = 1;i <= 5e4;++ i){
		if (! not_prime[i])
			prime[++ cnt] = i;
		for (register int j = 1;i * j <= 5e4;++ j){
			if (i != 1)
				not_prime[i * j] = true;
			fac[i * j].push_back (i);
		}
	}
	n = read ();
	Q = read ();
	for (register int i = 1;i <= n;++ i)
		a[i] = read ();
	for (register int i = 1;i <= n;++ i)
		b[i] = read ();
	Build ();
	while (Q --){
		Typ = read ();
		L = read ();
		R = read ();
		if (Typ == 1){
			X = read ();
			Update (L, R, X);
		}
		if (Typ == 2){
			print (Query (L, R));
			putchar ('\n');
		}
	}
	return 0;
}
```

---

## 作者：蒟蒻君HJT (赞：1)

这题分块。

需要用到一个科技 [P5435 基于值域预处理的快速 GCD](https://www.luogu.com.cn/problem/P5435)。

这是 cf 官方题解的做法，令块长为 $B$，值域为 $m$，则复杂度 $\Theta(\displaystyle \frac{nm\log \log m}{B}+nd(m)+q(B+\frac{n}{B}))$。

将序列按长度 $B$ 分块。

根据分块的套路，发现主要遇到瓶颈的是一整块的 $a_x$ 推平时不好维护答案。我们不妨考虑直接处理出第 $i$ 块推平为 $j$ 时的答案 $f_{i,j}$。

由 $\displaystyle\frac{\operatorname{lcm}(a_i,b_i)}{\gcd(a_i,b_i)}=\frac{a_ib_i}{\gcd^2(a_i,b_i)}$，考虑当 $a_i$ 固定时，枚举 $g=\gcd(a_i,b_i)\mid a_i$。显然此时只需要最小的能被 $g$ 整除的 $b_i$ 就可以了。当然也有可能实际的 $\gcd(a_i,b_i)$ 会是 $g$ 的倍数，但没关系，这样的更新是无效的（偏大了）。

因此需要预处理 $c_{i,j}$ 表示第 $i$ 块中是 $j$ 的倍数的 $b_{x}$ 的最小值。直接枚举每个 $b_i$ 的约数即可。

但是求 $f_{i,j}$ 总复杂度为 $\Theta(\displaystyle \frac{nm\log m}{B})$，还是有点慢。

考虑枚举出 $j$ 所有的质因子 $p$。发现相对于所有 $\displaystyle \frac{j}{p}$，$j$ 多出的 $\gcd$ 只有 $j$ 本身。那么令 $f_{i,j}=\displaystyle\max(\max_{p\in \text{Prime},p\mid j}(f_{i,\frac{j}{p}}\times p),\frac{c_{i,j}}{j})$ 即可。

于是预处理的复杂度 $\Theta(\displaystyle \frac{nm\log \log m}{B}+nd(m)))$。

那么之后的事情就简单了：修改时整块打标记，并用 $f_{i,j}$ 更新整块的答案，散块暴力下传之前的标记并修改，再合并出整块答案。查询时整块直接查，散块暴力下传标记，并逐个求答案。

你会发现你在标记下传和散块单点修改时需要一个快速以至于 $\Theta(1)$ 的求值域为 $m=50000$ 的两数的 $\gcd$ 的方法。用上文的科技即可。

[code](https://www.luogu.com.cn/paste/3kmyd06d)


---

## 作者：Exschawasion (赞：1)

数据范围是 $n,q,V \leq 50000$，而且还开三秒，说明这题 $O(n^{\frac 3 2})$ 大概率能过，甚至可能多一个 $\log V$ 也行。所以考虑分块。设一共分成 $B$ 块。

要求的式子可以转化为求 $\frac{a_i\times b_i}{\gcd(a_i,b_i)^2}$ 的值。因此维护这个东西就可以了。简便起见，令 $f(i)=\frac{a_i\times b_i}{\gcd(a_i,b_i)^2}$。

如果没有修改操作，那么就可以一开始求出所有 $f(i)$ 的值，然后维护块内 $\min$，查询就是 $O(B+\frac n B)$ 的了（请考虑拓展性，四毛子能做到 $O(n)$，但是不方便接下来要拓展的修改）。

思考如何修改。暴力就是直接把整个修改区间的 $f(i)$ 重新计算，这样单次是 $O(n)$ 的。零散块暴力修改属于基础操作。整块有没有什么办法可以 $O(1)$ 修改呢？

很显然，可以提前预处理出 $v_{i,j}$ 表示第 $i$ 块在修改为 $j$ 之后**新的**答案。这样在修改时直接把整块的答案赋值为 $v_{i,j}$ 就行了。暴力预处理是 $O(nV \log V)$ 的，过不去。

解决办法是首先预处理出 $[1,5\times 10^4]$ 中所有数的因子。然后对于每一块，开个桶 $t_x$ 记录在这一块中因子含 $x$ 的最小的 $b_i$ 是多少。这一部分是单次 $O(\frac{n}{B}\times d)$ 的。接着再枚举整个值域区间，利用算出的 $t_x$ 计算出 $v_{i,j}$。

预处理时间复杂度是 $O(B(\frac n B \times d+V))$，单次查询与修改都是 $O(B+\frac n B)$ 的，总时间复杂度为 $O(nd+VB+q(B+\frac n B))$。$d$ 代表的是因子个数的上限，在这题里 $d=100$。这里 $n,V,q$ 同阶，大概 $B= \sqrt{\frac 1 2 n}$ 的时候可以最快。

需要卡常……注意 $50000^2$ 开 `unsigned int` 就行了，`long long` 常数大。以及最大值一定要够大，建议手动赋值而不是 `memset`...


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int unsigned
namespace fastio{   
    namespace io{
        const int MaxBuff=1<<15;
        const int Output=1<<25;
        char B[MaxBuff],*S=B,*T=B;
        #define getc() ((S==T)&&(T=(S=B)+fread(B,1,MaxBuff,stdin),S==T)?0:*S++)
        char Out[Output],*iter=Out;
        inline void flush(){
            fwrite(Out,1,iter-Out,stdout);
            iter=Out;
        }
    }
    inline int rd(){
        using namespace io;
        register char ch;
        register int ans=0; 
        register bool neg=0;
        while(ch=getc(),(ch<'0' || ch>'9') && ch!='-');
        ch=='-'?neg=1:ans=ch-'0';
        while(ch=getc(),'0'<= ch && ch<='9') ans=ans*10+ch-'0';
        return neg?-ans:ans;
    }
    inline void wr(register long long x,register char ch='\n'){
        using namespace io;
        if(!x) *iter++='0';
        else{
            if(x<0) *iter++='-',x=-x;
            static int s[100]; 
            register int t=0;
            while(x) s[++t]=x%10,x/=10;
            while(t) *iter++='0'+s[t--];
        }
        *iter++=ch;
    }
}
using namespace fastio;
const int inf=0xffffffffu;
const int maxv=50000;
const int maxn=50000+5;
const int Blccnt=600+1;
const int Bsiz=100;
int blccnt,bsiz;
int n,q;
int tmp[maxn],val[Blccnt][maxn],mn[Blccnt];
int tag[maxn];
int a[maxn],b[maxn],L[maxn],R[maxn],bel[maxn];
vector<int> d[maxn];
inline int Sqr(int x){
	return x*x;
}
inline int F(int x){
	return a[x]*b[x]/Sqr(__gcd(a[x],b[x]));
}
void pushdown(int x){
	if(tag[x])for(int i=L[x];i<=R[x];i++)a[i]=tag[x];
	tag[x]=0;
}
void edit_sml(int blc,int l,int r,int v){
	pushdown(blc);
	for(int i=l;i<=r;i++)a[i]=v;
	mn[blc]=inf;
	for(int i=L[blc];i<=R[blc];i++)mn[blc]=min(mn[blc],F(i));
}
int qry_sml(int blc,int l,int r){
	pushdown(blc);
	int ans=inf;
	for(int i=l;i<=r;i++)ans=min(ans,F(i));
	return ans;
}
void edit(int l,int r,int v){
	if(bel[l]==bel[r])return edit_sml(bel[l],l,r,v);
	edit_sml(bel[l],l,R[bel[l]],v),edit_sml(bel[r],L[bel[r]],r,v);
	for(int i=bel[l]+1;i<=bel[r]-1;i++)tag[i]=v,mn[i]=val[i][v];
}
int qry(int l,int r){
	if(bel[l]==bel[r])return qry_sml(bel[l],l,r);
	int ans=inf;
	ans=min(ans,qry_sml(bel[l],l,R[bel[l]]));
	ans=min(ans,qry_sml(bel[r],L[bel[r]],r));
	for(int i=bel[l]+1;i<=bel[r]-1;i++)ans=min(ans,mn[i]);
	return ans;
}
void pre1(){
	for(int i=1;i<=blccnt;i++){
		mn[i]=inf;
		for(int j=L[i];j<=R[i];j++)mn[i]=min(mn[i],F(j));
	}
	for(int i=1;i<=blccnt;i++){
		for(int j=1;j<=maxv;j++)tmp[j]=inf;
		for(int j=L[i];j<=R[i];j++){
			for(auto a:d[b[j]])tmp[a]=min(tmp[a],b[j]);
		}
		for(int j=1;j<=maxv;j++)val[i][j]=inf;
		for(int j=1;j<=maxv;j++){
			for(auto a:d[j])if(tmp[a]!=inf)val[i][j]=min(val[i][j],j*tmp[a]/Sqr(a));
		}
	}
}
void pre2(){
	for(int i=1;i<=maxv;i++){
		for(int x=1;x*x<=i;x++)if(i%x==0){
			d[i].emplace_back(x);
			if(x*x==i)continue;
			d[i].emplace_back(i/x);
		}
	}
}
signed main(){
	n=rd(),q=rd(),bsiz=sqrt(n/2)+1,blccnt=n/bsiz;
	for(int i=1;i<=n;i++)a[i]=rd();
	for(int i=1;i<=n;i++)b[i]=rd();
	for(int i=1;i<=blccnt;i++)L[i]=(i-1)*bsiz+1,R[i]=i*bsiz;
	if(R[blccnt]!=n)blccnt++,L[blccnt]=R[blccnt-1]+1,R[blccnt]=n;
	for(int i=1;i<=blccnt;i++){
		for(int j=L[i];j<=R[i];j++)bel[j]=i;
	}
	pre2(),pre1();
	for(int i=1;i<=q;i++){
		int op,x,y,v;op=rd(),x=rd(),y=rd();
		if(op==1)v=rd(),edit(x,y,v);
		else wr(qry(x,y));
	}
	io::flush();
}
```


---

