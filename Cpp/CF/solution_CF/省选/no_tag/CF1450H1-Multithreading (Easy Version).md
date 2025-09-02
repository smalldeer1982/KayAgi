# Multithreading (Easy Version)

## 题目描述

The only difference between the two versions of the problem is that there are no updates in the easy version.

There are $ n $ spools of thread placed on the rim of a circular table. The spools come in two types of thread: the first thread is black and the second thread is white.

For any two spools of the same color, you can attach them with a thread of that color in a straight line segment. Define a matching as a way to attach spools together so that each spool is attached to exactly one other spool.

Coloring is an assignment of colors (white and black) to the spools. A coloring is called valid if it has at least one matching. That is if the number of black spools and the number of white spools are both even.

Given a matching, we can find the number of times some white thread intersects some black thread. We compute the number of pairs of differently colored threads that intersect instead of the number of intersection points, so one intersection point may be counted multiple times if different pairs of threads intersect at the same point. If $ c $ is a valid coloring, let $ f(c) $ denote the minimum number of such intersections out of all possible matchings.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1450H1/abdb0173d8eb58260cfc140f8631bb5b43b65a75.png) The circle above is described by the coloring bwbbbwww. After matching the spools as shown, there is one intersection between differently colored threads. It can be proven that it is the minimum possible, so $ f(\text{bwbbbwww}) = 1 $ . You are given a string $ s $ representing an unfinished coloring, with black, white, and uncolored spools. A coloring $ c $ is called $ s $ -reachable if you can achieve it by assigning colors to the uncolored spools of $ s $ without changing the others.

A coloring $ c $ is chosen uniformly at random among all valid, $ s $ -reachable colorings. Compute the [expected value](https://en.wikipedia.org/wiki/Expected_value) of $ f(c) $ . You should find it by modulo $ 998244353 $ .

We can show that the answer can be written in the form $ \frac{p}{q} $ where $ p $ and $ q $ are relatively prime integers and $ q\not\equiv 0\pmod{998244353} $ . The answer by modulo $ 998244353 $ is equal to $ (p\cdot q^{-1}) $ modulo $ 998244353 $ .

## 说明/提示

The first test corresponds closely to the image. Coloring '?' as 'w' does not create a valid coloring because the number of black spools is odd. Then the only reachable valid coloring is 'bwbbbwww' and $ f(\text{bwbbbwww}) = 1 $ , so the expected value is $ 1 $ .

It can be shown that the expected value for the second test is $ \frac{9}{16} $ .

## 样例 #1

### 输入

```
8 0
bwbb?www```

### 输出

```
1```

## 样例 #2

### 输入

```
10 0
???ww?wb??```

### 输出

```
436731905```

## 样例 #3

### 输入

```
4 0
bw?b```

### 输出

```
0```

# 题解

## 作者：zhoukangyang (赞：6)

[更好的阅读体验](https://www.cnblogs.com/zkyJuruo/p/14151575.html)

首先假设没有 $?$ 。

首先蒟蒻先给出一个很容易想到的贪心：

每一次选择相邻的两个颜色相同的位置，然后把他们配对

如果配对不上，那么现在的状态一定就是 $wbwbwbwb...$ ，需要有 $\frac{cnt}{2}$ 个交点。$cnt$ 为 $b$ 的个数。

于是整个问题的答案就是 $|\frac{cnta - cntb}{2}|$ ，$cnta$ 是 $b$ 在下标为奇数位置出现的次数，$cntb$ 是 $b$ 在下标为偶数位置出现的次数。

如何证明这个是最小的？

首先可以让整张图同色的相交的线段变成不相交，答案严格不增。

考虑数学归纳法：

- 一张空图，或一张只有白色点的图，答案 $= 0 \ge |\frac{cnta - cntb}{2}|$

- 非空图，首先找到两个相连的黑点，且在他们在黑点中的位置相邻（一定可以找到）：

  - 两个点一个在下标奇数处一个在下标偶数处：那么两个点一边都是白点，可以自己匹配，另一边的答案 $\ge |\frac{(cnta - 1) - (cntb - 1)}{2}| = |\frac{cnta - cntb}{2}|$ 。于是成立。

  - 两个点都在下标奇数处或都在下标偶数处：那么两个点一边都是白点但是会多出一个点，那么这个白点和其对应点会和现在找到的这条相连的边产生一个交点。答案（不妨选中的是两个下标奇数的点） $\ge 1 + |\frac{(cnta - 2) - cntb}{2}| = 1 + |\frac{cnta - cntb}{2} - 1| \ge   |\frac{cnta - cntb}{2} |$

证毕。

----------------

统计现在已经填了的 $b$ 奇数下标减偶数下标为 $cnta$，$?$ 在奇数下标的个数为 $cntb$，$?$ 在偶数下标的个数为 $cntc$。

直接枚举 ``?`` 中 ``b`` 的个数即可得到下面柿子：

$$ans = \frac{1}{2^{cntb + cntc - 1}} \sum\limits_{i = 0}^{cntb} \sum\limits_{j = 0, cnta + i - j \equiv 0 \pmod 2}^{cntc} |\frac{cnta + i - j}{2}| C_{cntb}^{i} C_{cntc}^{j}$$

$$= \frac{1}{2^{cntb + cntc - 1}} \sum\limits_{i = 0}^{cntb} \sum\limits_{j = 0, cnta + i + cntc - j \equiv 0 \pmod 2}^{cntc} |\frac{cnta + i + (cntc - j)}{2}| C_{cntb}^{i} C_{cntc}^{j}$$

这个东西就是可以卷积的了。

```cpp
#include<bits/stdc++.h>
#define L(i, j, k) for(int i = j, i##E = k; i <= i##E; i++) 
#define R(i, j, k) for(int i = j, i##E = k; i >= i##E; i--)
#define ll long long
#define ull unsigned long long 
#define db long double
#define pii pair<int, int>
#define mkp make_pair
using namespace std;
const int N = 6e5 + 7;
const int mod = 998244353;
const int G = 3;
const int iG = (mod + 1) / G;
int qpow(int x, int y) {
	int res = 1;
	for(; y; x = 1ll * x * x % mod, y >>= 1) if(y & 1) res = 1ll * res * x % mod;
	return res;
}
int ny(int x) { return qpow(x, mod - 2); }
int pp[N];
void NTT(int *f, int len, int flag) {
	L(i, 0, len - 1) if(pp[i] < i) swap(f[pp[i]], f[i]);
	for(int i = 2; i <= len; i <<= 1) 
		for(int j = 0, l = (i >> 1), ch = qpow(flag == 1 ? G : iG, (mod - 1) / i); j < len; j += i) 
			for(int k = j, now = 1; k < j + l; k ++) {
				int pa = f[k], pb = 1ll * f[k + l] * now % mod;
				f[k] = (pa + pb) % mod, f[k + l] = (pa - pb + mod) % mod, now = 1ll * now * ch % mod;
			}
	if(flag == -1) {
		int nylen = ny(len);
		L(i, 0, len - 1) f[i] = 1ll * f[i] * nylen % mod;
	}
}
void George1123(int *f, int *g, int *ans, int lena, int lenb) { // Tornado king
	int lim; for(lim = 1; lim <= lena + lenb; lim <<= 1);
	L(i, 0, lim - 1) pp[i] = ((pp[i >> 1] >> 1) | ((i & 1) * (lim >> 1)));
	NTT(f, lim, 1), NTT(g, lim, 1);
	L(i, 0, lim - 1) ans[i] = 1ll * f[i] * g[i] % mod;
	NTT(ans, lim, -1);
}
int n, m, cnta, cntb, cntc, jc[N], njc[N], ans, f[N], g[N], h[N];
int C(int x, int y) { return 1ll * jc[x] * njc[y] % mod * njc[x - y] % mod; }
char s[N];
int main() {
	scanf("%d%d", &n, &m);
	scanf("%s", s + 1);
	jc[0] = njc[0] = 1;
	L(i, 1, n) jc[i] = 1ll * jc[i - 1] * i % mod, njc[i] = ny(jc[i]);
	L(i, 1, n) {
		if(s[i] == 'b') {
			if(i % 2) cnta ++;
			else cnta --;
		}
		else if(s[i] == '?') {
			if(i % 2) cntb ++;
			else cntc ++;
		}
	}
	L(i, 0, cntb) f[i] = C(cntb, i);
	L(i, 0, cntc) g[i] = C(cntc, i);
	George1123(f, g, h, cntb, cntc);
	L(i, 0, cntb + cntc) if((cnta + i - cntc) % 2 == 0) (ans += 1ll * abs(cnta + i - cntc) / 2 * h[i] % mod) %= mod;
	ans = 1ll * ans * qpow(ny(2), cntb + cntc - 1) % mod;
	printf("%d\n", ans);
	return 0;
}
```

---------

现在已经可以通过 ``H1`` 了，但是给一种更好写，为 ``H2`` 做基础的方法：

考虑如何优化得到的卷积式 $f_t = \sum\limits_{i = 0}^{a} C_{a}^i \sum\limits_{j = 0}^{b}C_{b}^{j}  [i + j = t]$

观察规律发现 $f_t = C_{a+b}^t$ ，如何证明呢？

考虑其组合意义。$C_{a+b}^t$ 相当于从 $a + b$ 个球中取出 $t$ 个，那么我们可以枚举从前 $a$ 个取出的个数和前 $b$ 个取出的个数，也就是 $\sum\limits_{i = 0}^{a} C_{a}^i \sum\limits_{j = 0}^{b}C_{b}^{j}  [i + j = t]$。

（其实就是范德蒙德卷积）

于是答案就是 $\frac{1}{2^{cntb + cntc}} \sum\limits_{i = 0, i \equiv cnta - cntc \pmod 2}^{cnta + cntb} |cnta - cntc + i| C_{cntb + cntc}^{i}$

这个式子看起来很不舒服，让 $cnt = cntb + cntc, t = cntc - cnta$

$ans = \frac{1}{2^{cnt}} \sum\limits_{i = 0, i \equiv t \pmod 2}^{cnt} |i - t| C_{cnt}^{i}$

所以我们得到了更简洁的代码：

```cpp
#include<bits/stdc++.h>
#define L(i, j, k) for(int i = j, i##E = k; i <= i##E; i++) 
#define R(i, j, k) for(int i = j, i##E = k; i >= i##E; i--)
#define ll long long
#define ull unsigned long long 
#define db long double
#define pii pair<int, int>
#define mkp make_pair
using namespace std;
const int N = 2e5 + 7;
const int mod = 998244353;
int qpow(int x, int y) {
	int res = 1;
	for(; y; x = 1ll * x * x % mod, y >>= 1) if(y & 1) res = 1ll * res * x % mod;
	return res;
}
int ny(int x) { return qpow(x, mod - 2); }
int n, m, t, cnt, jc[N], njc[N], ans;
int C(int x, int y) { return 1ll * jc[x] * njc[y] % mod * njc[x - y] % mod; }
char s[N];
int main() {
	scanf("%d%d", &n, &m);
	scanf("%s", s + 1);
	jc[0] = njc[0] = 1;
	L(i, 1, n) jc[i] = 1ll * jc[i - 1] * i % mod, njc[i] = ny(jc[i]);
	L(i, 1, n) {
		if(s[i] == 'b') {
			if(i % 2) t --;
			else t ++;
		}
		else if(s[i] == '?') {
			cnt ++;
			if(i % 2 == 0) t ++;
		}
	}
	L(i, 0, cnt) if((t + i) % 2 == 0) (ans += 1ll * abs(t - i) * C(cnt, i) % mod) %= mod;
	ans = 1ll * ans * qpow(ny(2), cnt) % mod;
	printf("%d\n", ans);
	return 0;
}
```


---

## 作者：JQ6561 (赞：2)

题解说的都好复杂，说说本蒟蒻的方法。

如果字符串确定，显然维护一个栈从左向右扫就行了

由于扫的时候会出现栈空的情况，这很不美观，于是我们考虑在栈的负半轴添上无数wbwbwbwbwb，扫一遍之后的答案就是栈中元素的个数的绝对值

于是可以化简成 $\sum\limits_{i=1, 2|x}^t C_n^{i}\times 2i$，直接写通过H1。进行一些代数变形，可以变成 $\sum\limits_{i=1}^t C_n^i$，是经典问题。

---

## 作者：int08 (赞：1)

## 前言
“[_白と黒のバケモノ_](https://music.163.com/#/program?id=3062356333)”

# Solution
先来思考一下没有问号咋做。

容易想到考虑每个极长同色段，如果是偶数，直接互相配对就好了，奇数必然剩下一个。

但是答案并不是奇数段个数相关，考虑这个样例：`...BWBBWB...` 两个 `W` 看似是奇数段，但是由于中间俩 `B` 互相配对好了，直接连没有产生交点。

换句话说，选中两个相邻同色点连接接之后可以直接看作它们消失了，最后必然剩下 `WBWBWB...` 这样的东西，发现它的长度除以 $4$ 就是答案。

好的为啥一定除得尽？因为 `W,B` 初始数量都是偶数且一次消两个，所以剩下偶数个 `W,B`，又因为最后剩下的 `W,B` 数量相等，所以总数是 $4$ 的倍数。

考虑维护一个栈就可以解决，关于环，由于最后栈底和栈顶必不同，接起来也不会减少了，所以断环为链是对的。

然后带上问号，发现不会做了，咋办？

考虑一个经典 trick：**对 `01` 串的相邻同项操作时可以对奇数位取反。**

是的我们把所有奇数位的 `W,B` 翻转，发现此时由于一次操作必然选择一个奇数位一个偶数位，每次必然可以删除 `WB` 或者 `BW`，这个答案十分好表示，就是 $|cnt_W-cnt_B|$，因为两者都不为 $0$ 时候选交界处一定删得掉。

而且发现取反对于问号没有影响！太好了，直接枚举问号里 `W` 的数量就搞定了。

有一个疑问，万一 `W` 数量为奇数咋办？奇数位取反之后不好判定这个了。

事实上，如果两者数量为奇数，根据上文最后剩下来的元素个数就不是 $4$ 的倍数，直接判掉就好了。

### H2 口胡

发现答案类似于 $\sum_{2|i}\binom{n}{i}|x-\frac{i}{2}|$ 这样的东西，感觉和 $\sum_{i=0}^{x}\binom{n}{i}$ 这种式子一样，没有快速求取的方案，但是单点修改导致 $n,x$ 单次变化量是 $O(1)$，于是直接做就行了？

## AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define N 214514
#define mod 998244353
int n,q,i,j,l,r;
char X,Y,Z;
string t,s;
int jc[N],jic[N];
int qp(int x,int y)
{
	int ans=1;
	while(y) y&1?ans=ans*x%mod:0,y>>=1,x=x*x%mod;
	return ans;
 }
int C(int x,int y)
{
	return jc[x]*jic[y]%mod*jic[x-y]%mod;
}
void solve()
{
	s=t;
	int qc=0,bc=0,ans=0;
	for(i=1;i<=n;i++)
	{
		if(i&1)
		{
			if(s[i]=='w') s[i]='b';
			else if(s[i]=='b') s[i]='w';
		}
		if(s[i]=='?') qc++;
		if(s[i]=='b') bc++;
	}
	for(i=0;i<=qc;i++)
	{
		int d=abs((bc+i)-(n-bc-i));
		if(d%4==2) continue;
		(ans+=d/4*C(qc,i))%=mod;
	}
	cout<<ans*qp(qp(2,qc-1),mod-2)%mod;
}
signed main()
{
	jc[0]=jic[0]=1;
	for(i=1;i<N;i++) jc[i]=jc[i-1]*i%mod,jic[i]=jic[i-1]*qp(i,mod-2)%mod;
	cin>>n>>q>>t,t='#'+t;
	solve();
}
```
# The End.

---

## 作者：Mihari (赞：1)

# 壹、题目描述 &para;

[传送门 to Luogu](https://www.luogu.com.cn/problem/CF1450H1).

# 贰、[题解](https://www.cnblogs.com/Arextre/p/15005861.html) &para;

这东西我是一辈子都想不到的，即使我能够贪心出一点结论，也不会知道具体地数学表示。

若没有 $\tt ?$，设 $B_o$ 为奇数位置 $\tt b$ 的个数，$B_e$ 为偶数位置 $\tt b$ 的个数，类似地定义 $W_o,W_e$，那么，我们有：
$$
f(c)={1\over 2}|B_o-B_e|={1\over 2}|W_o-W_e|
$$
我是真不可能想到这个结论，但是这的确可以证明。

-----

>*注：如果你已经会证明了，则可以跳过证明部分。*
>
>不失普遍性地，我们假设 $B_o\ge B_e$，令 $2k=B_o-B_e$，证明分成两个部分：$f(c)\le k$ 以及 $f(c)\ge k$.
>
>## Proof P#1
>
>证明 $f(c)\le k$，即答案的上界为 $k$.
>
>首先，贪心地将**最近的且奇偶性不同的同色点**连接，由于 $B_o>B_e\;\and\;B_o-B_e=2k$，那么会在奇数位置剩下 $2k$ 的黑色点，同样的，会在偶数位置剩下 $2k$ 个白色点，即我们这样连：
>
>![](https://z3.ax1x.com/2021/07/13/WkYmZQ.png)
>
>有两个重要性质：
>
>- 两个点围成的两个部分没有和他们**颜色相同且没有被匹配的**点，假设存在这样的点，那么它的下标一定会是奇数或偶数，而我们两个端点一奇一偶，那么它一定可以和其中一个端点构成**更近的**匹配；
>- 两个点分开的两个部分，其内部的点一定都是偶数，这比较显然吧；
>
>此时我们证明了这些点都是同色，并且个数还是偶数，那么他们一定可以内部搞定而不会连出去。即这一步操作不会产生异色交点。我们可以把这些部分都忽略了，因为外部的连接无论如何都不会影响到他们了。
>
>接下来，剩下的点一定都是这种情况（将已经连接的部分忽略了）
>
>![](https://z3.ax1x.com/2021/07/13/WkNJUJ.png)
>
>由于有 $2k$ 个黑色的，并且我们发现每两个会产生一个异色交点，故总共就会有 $k$ 个交点，由于这个构造是普适性的，任意一种情况都会存在这样一种构造，所以答案绝不会超过 $k$，即答案至多为 $k$.
>
>-----
>
>## Proof P#2
>
>证明 $f(c)\ge k$，即答案至少为 $k$，此时我们应该考虑最少的交点次数都至少为 $k$.
>
>此处需要使用以下结论：
>
>> 最优构造中可以不存在同色交点。即在最优构造中，同色交点一定可以被避免。
>
>为什么呢？我们对比一下两种连法：
>
>![image](https://z3.ax1x.com/2021/07/13/WkD8Qs.png)
>
>第一种方法存在同色交点，而如果我们将其变成第二种，我们发现，异色交点不可能会增多，而只有可能减少，具体减少的是从 $P_2$ 到 $P_4$ 的连边与两个白色边形成的交点，而这又是最优情况，所以减少也不可能减少。
>
>故而这种调整不会改变异色交点个数，类似地，我们可以将所有同色交点都打开。
>
>由于 $B_o-B_e=2k$，所以一定会有 $k$ 条奇偶性相同的边，而每连这样一条边，将原图分成的两个部分一定点数都为奇数，为奇数则一定会有左部分和右部分的一条边，这条边一定会和我们的分割边产生一个交点，这种交点显然不可避免，然而我们又证明最优构造中同色交点一定可以避免，所以这种交点不可能是同色交点，只有可能为异色交点。
>
>而每一条分割边至少一个这样的交点，有 $k$ 条，自然而然至少 $k$ 个异色交点。
>
>上下界都是 $k$，所以 $f(c)=k={1\over 2}|B_o-B_e|$.
>
>$\blacksquare.$

-----

考虑如何计数。设 $F$ 为 $\tt ?$ 的集合，类似定义 $F_o,F_e$，我们首先枚举 $F$ 的子集 $i$，并强制将 $i$ 中偶数位置填 $\tt b$，奇数位置填 $\tt w$，对于 $\complement_Fi$，我们将偶数位置填 $\tt w$，奇数位置填 $\tt b$，那么，就有
$$
f(c)={1\over 2}|B_e+a-[B_o+|F_o|-(i-a)]|={1\over 2}|B_e-B_o-|F_o|+i|
$$
注意到 $B_o+|F_o|={n\over 2}-W_o$，我们令 $x=B_o+|F_o|-B_e={n\over 2}-W_o-B_e$，那么
$$
f(c)={1\over 2}|i-x|
$$
由于 $i$ 对应的方案有 ${|F|\choose i}$ 种，故而总方案的期望值为
$$
ans={1\over 2^{|F|-1}}\sum_{0\le i\le F}^{i\equiv x\pmod 2}{1\over 2}|i-x|{|F|\choose i}
={1\over 2^{|F|}}\sum_{0\le i\le F}^{i\equiv x\pmod 2}|i-x|{|F|\choose i}
$$
刚开始是 $2^{|F|-1}$ 的原因是我们要保证 $i$ 为 奇数/偶数。

时间复杂度 $\mathcal O(n)$.

# 叁、参考代码 &para;

```cpp
#include<cstdio>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;

// #define NDEBUG
#include<cassert>

namespace Elaina{
    #define rep(i, l, r) for(int i=(l), i##_end_=(r); i<=i##_end_; ++i)
    #define drep(i, l, r) for(int i=(l), i##_end_=(r); i>=i##_end_; --i)
    #define fi first
    #define se second
    #define mp(a, b) make_pair(a, b)
    #define Endl putchar('\n')
    #define mmset(a, b) memset(a, b, sizeof a)
    // #define int long long
    typedef long long ll;
    typedef unsigned long long ull;
    typedef pair<int, int> pii;
    typedef pair<ll, ll> pll;
    template<class T>inline T fab(T x){ return x<0? -x: x; }
    template<class T>inline void getmin(T& x, const T rhs){ x=min(x, rhs); }
    template<class T>inline void getmax(T& x, const T rhs){ x=max(x, rhs); }
    template<class T>inline T readin(T x){
        x=0; int f=0; char c;
        while((c=getchar())<'0' || '9'<c) if(c=='-') f=1;
        for(x=(c^48); '0'<=(c=getchar()) && c<='9'; x=(x<<1)+(x<<3)+(c^48));
        return f? -x: x;
    }
    template<class T>inline void writc(T x, char s='\n'){
        static int fwri_sta[1005], fwri_ed=0;
        if(x<0) putchar('-'), x=-x;
        do fwri_sta[++fwri_ed]=x%10, x/=10; while(x);
        while(putchar(fwri_sta[fwri_ed--]^48), fwri_ed);
        putchar(s);
    }
}
using namespace Elaina;

const int maxn=2e5;
const int mod=998244353;
const int inv2=499122177;

inline int qkpow(int a, int n){
    int ret=1;
    for(; n; n>>=1, a=1ll*a*a%mod)
        if(n&1) ret=1ll*ret*a%mod;
    return ret;
}

int fac[maxn+5], finv[maxn+5];

int n, m, b[2], w[2], f[2];
char s[maxn+5];

inline void init(){
    fac[0]=1;
    rep(i, 1, maxn) fac[i]=1ll*fac[i-1]*i%mod;
    finv[maxn]=qkpow(fac[maxn], mod-2);
    drep(i, maxn-1, 1) finv[i]=1ll*finv[i+1]*(i+1)%mod;
    finv[0]=1;
}

inline int C(int n, int m){
    if(n<m) return 0;
    return 1ll*fac[n]*finv[m]%mod*finv[n-m]%mod;
}

inline void input(){
    n=readin(1), m=readin(1);
    scanf("%s", s+1);
    rep(i, 1, n){
        if(s[i]=='b') ++b[i&1];
        else if(s[i]=='w') ++w[i&1];
        else ++f[i&1];
    }
}

inline void calc(){
    int x=(n>>1)-w[1]-b[0], ans=0;
    rep(i, 0, f[0]+f[1]) if((i&1)==(x&1))
        ans=(ans+1ll*fab(i-x)%mod*C(f[0]+f[1], i)%mod)%mod;
    ans=1ll*ans*qkpow(inv2, f[0]+f[1])%mod;
    writc(ans);
}

signed main(){
    init();
    input();
    calc();
    return 0;
}
```


---

