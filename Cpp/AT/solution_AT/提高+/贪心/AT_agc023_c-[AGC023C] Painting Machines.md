# [AGC023C] Painting Machines

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc023/tasks/agc023_c

$ N $ 個のマスが横一列に並んでおり、左から右へ $ 1 $ から $ N $ までの番号がついています。 最初、すべてのマス目は白いです。 また、$ N-1 $ 台のペイントマシンがあり、$ 1 $ から $ N-1 $ までの番号が付けられています。 ペイントマシン $ i $ は、稼働すると、マス $ i $ とマス $ i+1 $ を黒く塗ります。

すぬけ君は、これらのペイントマシンを、$ 1 $ 台ずつ順番に稼働させます。 すぬけくんがマシンを稼働させる順番は、$ (1,\ 2,\ ...,\ N-1) $ の順列 $ P $ によって表されます。 これは、$ i $ 番目に稼働させるマシンの番号が $ P_i $ であることを意味します。

ここで、ある順列 $ P $ のスコアは、その順列に従ってマシンを稼働させたとき、 すべてのマスが黒く塗られた状態に初めてなるまでに稼働させたマシンの台数と定義されます。 すぬけ君はまだ順列 $ P $ を決めていませんが、スコアに興味があります。 すぬけ君のために、すべての順列についてそのスコアを求め、その総和を求めてください。 ただし、答えは非常に大きくなることがあるので、$ 10^9\ +7 $ で割った余りを求めてください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 10^6 $

### Sample Explanation 1

順列 $ P $ としてありうるものは $ 6 $ つあります。 この中で、$ P\ =\ (1,\ 3,\ 2) $ または $ P\ =\ (3,\ 1,\ 2) $ のときだけスコアは $ 2 $ になり、 それ以外のときはスコアは $ 3 $ になります。 よって、求める答えは $ 2\ \times\ 2\ +\ 3\ \times\ 4\ =\ 16 $ となります。

### Sample Explanation 2

ありうる唯一つの順列は $ P\ =\ (1) $ で、スコアは $ 1 $ です。

## 样例 #1

### 输入

```
4```

### 输出

```
16```

## 样例 #2

### 输入

```
2```

### 输出

```
1```

## 样例 #3

### 输入

```
5```

### 输出

```
84```

## 样例 #4

### 输入

```
100000```

### 输出

```
341429644```

# 题解

## 作者：w4p3r (赞：19)

一道挺不错的计数题。

考虑$ans=\sum_{i=1}^{n-1}[$前$i$步没有结束覆盖的排列数量$]+(n-1)!$

（加上$(n-1)!$是因为每个排列少计数了一次）

前面那个$\sum$应该等于$\sum_{i=1}^{n-1}(n-1)!-[$前$i$步结束了覆盖的排列数量]

一个排列前$i$步是否结束覆盖，显然只与其前$i$个数组成的集合有关，而与其排列顺序无关，所以进一步可以得到原式等于：

$\sum_{i=1}^{n-1}(n-1)!-$[大小为$i$且能结束覆盖的集合数量]$*i!*(n-1-i)!$

（注意你要求的是排列而不是集合，因此要乘上阶乘的贡献）

不妨假设[大小为$i$且能结束覆盖的集合数量]为$f_i$，考虑$f_i$是什么。

可以发现，一个大小为$t$集合$S$能结束覆盖，需要满足以下两点条件（假设$S_i$为集合$S$所有数中第$i$小的）





 $1.1,n-1 \in S$（因为$1$只能被$1$覆盖，$n$只能被$n-1$覆盖）






$2.{\forall i<t},S_{i+1}-S_i\le 2$（不然$S_i+2$不会被覆盖）




这个问题运用类似于隔板法的组合技巧可以转化为这样一个问题：

存在一个方程$t$元方程：

$x_1+x_2+x_3...+x_{t-1}+x_t=n-1-t$

其中$0\le x_i \le1$，求这个方程的解数。

（意思大概就是考虑集合中相邻两个数的间隙是多少，间隙大小只能是$0$或$1$，且最后间隙需要有$n-1-t$个数）

显然地，这个东西是$\binom{t-1}{n-1-t}$。

因此$f_i=\binom{i-1}{n-1-i}$。

然后直接求解上面的式子即可，即$ans=n*(n-1)!-\sum_{i=1}^{n-1}f_i*i!*(n-1-i)!$


代码：

```cpp
//W4P3R
#include<bits/stdc++.h>
#define inf 1e9
#define eps 1e-6
#define mp make_pair
#define pb push_back
#define re register int
#define fr first
#define sd second
#define pa pair<int,int>
#define FOR(i,a,b) for(re i=a;i<=b;i++)
#define REP(i,a,b) for(re i=a;i>=b;i--)
#define MEM(a) memset(a,0,sizeof(a))
#define N 1000010
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
inline ll read()
{
	char ch=getchar();
	ll s=0,w=1;
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){s=s*10+ch-'0';ch=getchar();}
	return s*w;
}
inline int lowbit(int x){return x&(-x);}
const int mod=1e9+7;
int fac[N],inv[N],f[N];
int n;
inline int Z(int x){return (x>=mod?x-mod:x);}
inline int C(int n,int m){if(n<m)return 0;return 1LL*fac[n]*inv[m]%mod*inv[n-m]%mod;}
int main()
{
	//ios::sync_with_stdio(false);
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	n=read();
	fac[0]=1;
	FOR(i,1,n)fac[i]=1LL*fac[i-1]*i%mod;
	inv[0]=inv[1]=1;
	FOR(i,2,n)inv[i]=1LL*inv[mod%i]*(mod-mod/i)%mod;
	FOR(i,2,n)inv[i]=1LL*inv[i]*inv[i-1]%mod;
	FOR(i,1,n)f[i]=C(i-1,n-1-i);
	int ans=0;
	FOR(i,1,n-1)ans=Z(ans+mod-1LL*f[i]*fac[i]%mod*fac[n-i-1]%mod);
	ans=Z(ans+1LL*fac[n-1]*n%mod);
	cout<<ans<<'\n';
	return 0;
}
//gl

```
**如果你觉得这篇题解对你有帮助，那你可以点个赞支持我一下qwq。如果你对题解有任何问题/认为我的题解有任何问题，可以私信/在评论区发出来，当然如果你对我的题解有任何意见/建议也欢迎指出。我会尽我全力把我题解写到最好的qwq**


---

## 作者：rong_nian (赞：8)

UPD 2021/4/4 : 改了一些措辞, 让它更易读了些 && 修复组合数的锅.  
### Solution : 

~~离谱题~~  

看到这种 每种方案都有一个权值 的题, 一般考虑 把它带入式子一起化 / 枚举这个权值 去消去这个影响.

这题我们考虑枚举染色次数, 这样我们就只需要去统计方案数了.

~~相信大家都会~~

这个染色次数 $x \in [\lceil \frac{n}{2} \rceil, n - 1]$ 看一眼数据范围, 这个权值枚举 $10^6$ , 看起来得推个 $O(1)$ 式子了.

仔细想一下, 我们首先会在第一个位置染一下, 然后还有 $cnt = n - 2$ 个地方没染, 而对于每一次染色, 对 $cnt$ 的影响有两种, $cnt-1$ 或 $cnt - 2$ .

那这个方案数不就是 : $i-1$ 次操作后 让 $cnt = 0$ 的 方案数.

仔细想想, 这也不会求啊.

再转化一下, 如果我们求出至多 $i$ 次操作后, $cnt = 0$ 的方案数, 再把 至多 $i-1$ 次操作后, $cnt = 0$ 的方案数 减去. 恰好操作 $i$ 次, $cnt = 0$ 的方案数不就得出来了吗.

所以, 我们可以先把让 $cnt = n- 2$ 减去 $i - 1$ , 那么每次操作的贡献就是 $-1 / 0$ 所以在剩下的 $i - 1$ 次操作中 只要有 $(n - 2) - (i - 1)$ 次 贡献为 $-1$ 的操作就行了.

这个的方案数是 $C_{i - 1}^{n - i - 1}$ 

还要注意一点, 这些操作都是 不互相同的 . 所以我们要乘上 排列数. (代码中第30行)

### Code : 

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5, mod = 1e9 + 7;
int n, fac[N], inv[N], f[N], ans;

inline int fpow(int x, int b) {
    int res = 1;
    while (b) {
        if (b & 1) res = 1ll * res * x % mod;
        x = 1ll * x * x % mod;
        b >>= 1;
    }
    return res;
}

inline int C(int x, int y) {
    if (x < y) return 0;
    return 1ll * fac[x] * (1ll * inv[y] * inv[x - y] % mod) % mod;
}

int main() {
    cin >> n;
    fac[0] = inv[0] = 1;
    for (int i = 1; i <= N - 5; ++i) fac[i] = 1ll * fac[i - 1] * i % mod;
    inv[N - 5] = fpow(fac[N - 5], mod - 2);
    for (int i = N - 6; i; --i) inv[i] = 1ll * (i + 1) * inv[i + 1] % mod;
    int l = (n + 1) / 2;
    for (int i = l; i < n; ++i) {
        f[i] = 1ll * C(i - 1, n - i - 1) * (1ll * fac[i] * fac[n - i - 1] % mod) % mod;
    }
    for (int i = l; i < n; ++i) ans = (ans + 1ll *  i * (0ll + f[i] - f[i - 1] + mod) % mod) % mod;
    cout << ans << endl;
    return 0;
}
```
一天改了四次, 麻烦管理了QAQ

---

## 作者：Refined_heart (赞：2)

$\text{Solution:}$

首先可以考虑对每个数拆贡献，一个数如果有贡献显然是它自己有贡献或者排在它后面的数有贡献。

这个东西看起来就不好做。所以直接容斥掉，变成求它有多少情况不贡献。

此时当且仅当它后面的数和它自己全部没有贡献。

那么从这一步开始，我们发现，这个数具体是多少已经不重要了，我们现在只需要知道，有多少长度为 $i$ 的后缀，其全部没有贡献。

现在需要明确一下：先考虑转化为 **有多少长度为 $i$ 的排列可以覆盖全部格子。** 接下来我们发现，后面的 $n-i-1$ 是可以随便排列的，而前面这 $i$ 个也是可以随便排的，现在就剩下如何确定有多少种方案有 $i$ 个可以覆盖所有格子。

剩下就是我没有想到的地方了）

考虑设集合为 $S$ （由于之前把随便排给去掉了，所以此时是没有顺序的，后面要乘一个 $i!\times (n-i-1)!$ ）

那么不妨认定它是有顺序的，它需要满足下列条件：

* $1\in S,n-1\in S$
* $\forall i,S_{i+1}-S_i\leq 1$

第一步是因为 $1,n$ 只能被这样覆盖，第二步是因为，如果不满足，那么 $S_i+2$ 就无法覆盖。

考虑怎么求 $S$ 的个数。我们发现，现在可以从元素位置差的角度来考虑。

首先要发现一个性质：$\left(\sum S_i-S_{i-1}\right)=n$

那么考虑这个间隙应当满足什么条件：设 $|S|=t,$ 则我们需要空出 $n-t-1$ 个位置，而一共有 $t$ 个元素，所以一共有 $t-1$ 个空隙。

那么不妨表示为方程，则有：

$$\sum _{i=1}^{t-1} x_i=n-t-1,x_i\in\{0,1\}$$

考虑生成函数，将每个 $x$ 写成 GF 形式，所求即为：

$$
\begin{aligned}
F&=\prod_{i=1}^{t-1} (1+x), \\
Ans&=[x^n]F(x)
\end{aligned}
$$

考虑其 $n$ 次项的系数，容易发现这个是杨辉三角。

那么就有：

$$
Ans=\binom{t-1}{n-t-1}
$$

于是整理上述过程，设 $f_i=\binom{t-1}{n-t-1},$

$$
Ans=\sum f_i\times i!\times (n-i-1)!
$$

组合意义就是：找到大小为 $i$ 的合法集合方案数，集合内部随便排，外部随便排。注意其不能交叉，是因为这里强制了 $S$ 排在前面。

预处理阶乘就可以线性了。最后要用 $n\times (n-1)!-Ans.$

---

## 作者：Acfboy (赞：2)

这计数挺妙的！

首先 $1$ 号位先把它填上，然后剩下 $(n-2)$ 个需要填上，我们枚举一个 $i$ 然后如果有个办法可以在 $O(1)$ 的时间内求出用**不超过** $i$ 次操作把它填完的方案数就好了。

这里有一个巧妙的转化，就是考虑每次往后怎么放，如果空一格，那么就是空白格少了两个，直接放，空白格就少了一个。这样就可以把问题转化为 $(n-2)$ 每次减去 $1$ 或 $2$，用 $(i-1)$ 次，最后变成 $0$ 的方案数是多少就可以了，因为不同总次数肯定不一样，相同总次数超出的不会恰好变成 $0$，不超出的因为中间一定有选择放的地方不一样，所以不重不漏。

然后发现每次反正都要减去 $1$ 的，那先给它减掉 $(i-1)$ 个 $1$，问题就变成了要么减去 $0$ 要么减去 $1$，这样在 $i-1$ 中个选出 $(n-2)-(i-1) = n-i-1$ 个就行了，那么答案就是 $i-1 \choose n-i-1 $。最后前后面都可以随便排，乘上两个阶乘即可。

```cpp
for (int i = (n+1) / 2; i < n; i++)
		f[i] = C(i-1, n-i-1) * fac[i] % P * fac[n-i-1] % P,
		ans = (ans + (f[i] - f[i-1] + P) % P * i % P) % P;
```

那么这个妙在哪儿呢？我觉得最神奇的地方就在于它没有直接考虑这个排列本身，而是用了另一个不重不漏的方式去构造了这个排列。

---

## 作者：约瑟夫用脑玩 (赞：2)

~~其实我是来化简公式的~~，那就尽量说简洁一点。

首先我们直接考虑计数贡献：

$ans=\sum_i\text{在 i 结束的排列数}* i$

$=\sum_i\text{在 i 后结束的排列数}$

$=\sum_i(n-1)!-\text{在 i 前结束的排列数}$

这就是我没想到的了，~~然后我路就走偏了~~。

从 $i$ 处断开，后面不关心，随便排直接乘 $(n-i-1)!$。

前面结束的排列数恰好不关心在哪里结束，任意排直接乘 $i!$ 和能结束的集合方案。

$=\sum_i(n-1)!-i!* (n-i-1)!* \text{i 个能结束的集合数}$

这个问题就可做了许多，~~然后我从偏路走到这里来又走错路了~~。

首先得选 $1,n-1$ 两个点，然后中间的不能超过两个不选，设选了 $t$ 个，每个在 $p_i$。

有 $\forall i\in \left[1,t\right),p_{i+1}-p_{i}\le2$

设 $x_i=p_{i+1}-p_i-1$，$\forall i\in \left[1,t\right),x_i\le1$

显然还有：

$\sum_ix_i=\sum_ip_{i+1}-p_i-1$

$=(\sum_ip_{i+1}-p_i)-t+1$

$=p_t-t+1$

$=n-t-1$

反正我没想到，做到这里就是经典的隔板，即方案数为 $\dbinom{t-1}{n-1-t}$

然后就是化简式子，最后化出来长这样：

$ans=n!-\sum\limits_{i=\frac{n}{2}}^{n-1}\dfrac{i!* (i-1)!}{(2i-n)!}$

代码就四行的事：

```
	n=read();for(i=fac[0]=1;i<=n;fac[i]=Ml(fac[i-1],i),i++);
	for(inv[n]=Inv(fac[n]),i=n-1;~i;inv[i]=Ml(inv[i+1],i+1),i--);
	for(i=n>>1;i<n;i++)Add(s,Ml(Ml(fac[i],fac[i-1]),inv[(i<<1)-n]));
	writenum(Ad(fac[n],Mod-s),10);
```

---

## 作者：do_it_tomorrow (赞：1)

这么好的 $2500$ 的题目为什么不评紫。

考虑枚举排列 $P$ 的得分 $i$，但是想要快速计算比比较困难。

所以考虑设 $f_i$ 表示操作了前 $i$ 个之后全部染黑的方案数，需要注意并不是恰好 $i$ 次。

对于一个第 $i$ 次操作之后就全部被染黑的方案 $P$，从 $[1,i]$ 的顺序是不重要的，影响答案的只有在 $i$ 之前选择了哪些。

那么我们将 $P_1$ 到 $P_i$ 从小到大排序排序，容易理解 $P_1=1,P_i=n-1$。

在满足上面要求的同时，还需要满足 $\forall k\in[1,i-1]\cap\mathbb{Z}$ 都有 $p_{k+1}-p_k\le 2$。

我们记 $x_k=p_{k+1}-p_k-1$，那么显然所有 $x_k\in\{0,1\}$。

而他们之间有满足等式：

$$\sum\limits_{k=1}^{i-1}x_k=(\sum\limits_{k=1}^{i-1} p_{i+1}-p_i)-(i-1)$$

同时：

$$\sum\limits_{k=1}^{i-1} p_{i+1}-p_i=p_i-p_1=n-2$$

所以就有：

$$x_k\in\{0,1\}\wedge\sum\limits_{k=1}^{i-1} x_k=n-i-1$$

那么显然 $x$ 的方案数就是 $i-1\choose n-i-1$，再乘上排列 $P$ 带来的贡献，得到：

$$f_i={i-1\choose n-i-1}\times i!\times (n-i-1)!$$

所以得分为 $i$ 的数量就是 $f_i-f_{i-1}$，那么就有：

$$Ans=\sum\limits_{i=\lceil\frac{n}{2}\rceil}^{n-1} i\times (f_{i}-f_{i-1})$$

时间复杂度为 $O(n)$。

```cpp
#include<iostream>
#define int long long
using namespace std;
const int N=1e6+5,mod=1e9+7;
int n,jc[N],inv[N],ans,f[N];
int ksm(int a,int b=mod-2){
    int ans=1;
    while(b){
        if(b&1) ans=ans*a%mod;
        a=a*a%mod,b>>=1;
    }
    return ans;
}
void init(int n){
    jc[0]=1;
    for(int i=1;i<=n;i++){
        jc[i]=jc[i-1]*i%mod;
    }
    inv[n]=ksm(jc[n]);
    for(int i=n-1;i>=0;i--){
        inv[i]=inv[i+1]*(i+1)%mod;
    }
}
int C(int n,int m){
    return jc[n]*inv[m]%mod*inv[n-m]%mod;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr),init(N-1);
    cin>>n;
    for(int i=(n+1)/2;i<n;i++){
        f[i]=C(i-1,n-i-1)*jc[i]%mod*jc[n-i-1]%mod;
        ans=(ans+(f[i]-f[i-1])*i)%mod;
    }
    cout<<(ans+mod)%mod<<'\n';
    return 0;
}
```

---

## 作者：GIFBMP (赞：1)

一道计数好题。

我们考虑统计每一步的贡献，设 $F_i$ 表示在第 $i$ 步还没有覆盖完的排列数，则答案等于 $\sum\limits_{i=1}^{n-1}(F_i+(n-1)!)$。但是这个东西很不好算，于是我们设 $G_i$ 表示在第 $i$ 步已经能覆盖完的方案数，则此时答案等于 $(n-1)!+\sum\limits_{i=1}^{n-1}((n-1)!-G_i)$。接着我们发现，能不能覆盖满只和排列中 $[1,i]$ 下标有什么元素有关，考虑统计满足条件的集合数 $f_i$，则答案等于 $(n-1)!+\sum\limits_{i=1}^{n-1}f_i\times i!\times(n-i-1)!$。

我们把集合中的元素从小到大排序，对于一个合法的集合 $S$，需要满足：

1. $S_1=1$；
2. $S_{|S|}=n-1$；
3. $\forall2\le i\le |S|$，$S_i-S_{i-1}\le2$。

我们设 $T_i=S_{i+1}-S_i$，则我们只要统计满足 $\sum\limits_{i=1}^{|S|-1}T_i=n-2$，且 $\forall1\le i<|S|$，$1\le T_i\le 2$ 的 $T$ 方案数即可。运用基本的套路，设 $T'_i=T_i-1$，则条件转化为 $0\le T'_i\le1$，$\sum\limits_{i=1}^{|S|-1}T'_i=n-|S|-1$，那么方案数显然为 $C_{|S|-1}^{n-|S|-1}$，则 $f_i=C_{i-1}^{n-i-1}$。

然后就做完了，时间复杂度 $\Theta(n)$。

Code:

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std ;
const int MAXN = 1e6 + 10 , mod = 1e9 + 7 ;
typedef long long ll ;
int n ; 
ll fac[MAXN] , ans , inv[MAXN] ;
void U (ll &x , ll y) {x = x + y >= mod ? x + y - mod : x + y ;}
ll qpow (ll x , ll p = mod - 2) {
	ll ret = 1 ;
	for (; p ; p >>= 1 , x = x * x % mod)
		if (p & 1) ret = ret * x % mod ;
	return ret ; 
}
ll C (int x , int y) {
	if (x < 0 || y < 0 || x < y) return 0 ;
	return fac[x] * inv[y] % mod * inv[x - y] % mod ;
}
int main () {
	scanf ("%d" , &n) , fac[0] = 1 ;
	for (int i = 1 ; i <= n ; i++) fac[i] = fac[i - 1] * i % mod ;
	inv[n] = qpow (fac[n]) ;
	for (int i = n - 1 ; ~i ; i--) inv[i] = inv[i + 1] * (i + 1) % mod ;
	for (int i = 1 ; i <= n ; i++)
		U (ans , (fac[n - 1] - C (i - 1 , n - i - 1) * fac[i] % mod * fac[n - 1 - i] % mod + mod) % mod) ;
	printf ("%lld\n" , ans) ;
	return 0 ;
}
```

---

## 作者：大眼仔Happy (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_agc023_c)

注意到有一些特殊的点，比如说 $1$ 只能被 $1$ 操作，$n$ 只能被 $n - 1$ 操作。

如果考虑全部染黑，那么相当于：

- $1$ 和 $n - 1$ 要出现。
- 两个操作的格子的距离不能超过 $2$。

我们设 $f_i$ 表示钦定 $i$ 个操作使得格子涂黑的方案数，$g_i$ 表示**恰好** $i$ 个操作使得格子涂黑的方案数。

那么有 $g_i = \Delta f_i$，${\rm ans} = \sum g_i\times i$。

假设选了 $i$ 个格子要操作，那么就会剩下 $n - 1 - i$ 个格子，并且被分成了 $i - 1$ 个空。这个时候每个空要满足 $\le 1$ 的限制。于是方案数就是 $i - 1\choose n - 1 - i$，然后前面的 $i$ 个操作和后面的 $n - 1 - i$  个操作随便排列，方案数是 $(n - 1 - i)!\times i!$。

时间复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5;
#define ll long long
const ll mod = 1e9 + 7; 
int inline read() {
	int num = 0, f = 1;
	char ch = getchar();
	while(ch < '0' || ch > '9') {
		if(ch == '-') f = -1;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9') {
		num = (num << 3) + (num << 1) + (ch ^ 48);
		ch = getchar();
	}
	return num * f;
}
int n; ll f[N], ans; 
vector<ll> fac, ifac; 
ll qp(ll a, ll b) {
	ll res = 1; 
	while(b) {
		if(b & 1) (res *= a) %= mod; 
		(a *= a) %= mod, b >>= 1; 
	}
	return res; 
}
void init(int n) {
	fac.resize(n + 1), ifac.resize(n + 1), fac[0] = 1; 
	for(int i = 1; i <= n; ++i) fac[i] = fac[i - 1] * i % mod; 
	ifac[n] = qp(fac[n], mod - 2); 
	for(int i = n; i; --i) ifac[i - 1] = ifac[i] * i % mod; 
}
ll nCr(ll n, ll r) { return r < 0 || n < r ? 0ll : fac[n] * ifac[n - r] % mod * ifac[r] % mod; }
ll nPr(ll n, ll r) { return r < 0 || n < r ? 0ll : fac[n] * ifac[n - r] % mod; }
int main() {
#ifdef file
	freopen("AGC023C.in", "r", stdin);
	freopen("AGC023C.out", "w", stdout);
#endif
	n = read(), init(n);
	for(int i = 1; i < n; ++i) f[i] = nPr(i - 1, n - 1 - i) * fac[i] % mod; 
	for(int i = 1; i < n; ++i) ans = (ans + (f[i] + mod - f[i - 1]) * i) % mod; 
	printf("%lld", ans); 
	return 0;
}
```

---

## 作者：Felix72 (赞：0)

设 $f_i$ 为前 $i$ 次操作正好染色完的方案数，所求即为 $\sum_{i=1}^{n-1} i \times f_i$。

因为 $f_i$ 不好求，我们推断出 $f_i = g_i - g_{i-1}$，其中 $g_i$ 为前 $i$ 次中某一次操作正好染色完的方案数。

因为 $g_i$ 不好求，我们对于每个 $i$ 规定出 $h_i$，表示前 $i$ 次操作选定的机器集合的种类（要求 $i$ 次操作后格子一定全黑，不要求恰好做到），那么 $g_i = h_i \times i! \times (n - i - 1)!$。

因为 $h_i$ 不好求，我们思考它的组合意义：总共 $n - 1$ 个元素，选 $i$ 个，始末元素必选，中间不能有两个相邻元素同时不选的方案数。

因为这个方案数不好求，我们把上述限制改为“相邻两个被选元素的距离小于等于 2”，这个终于能求了。

代码思路同上。

```cpp
/*蛋糕鱼乐园*/
#include <bits/stdc++.h>
using namespace std;

const int N = 1000010, mod = 1e9 + 7;
int n; long long fac[N], inv[N];
inline long long qpow(long long a, int b)
{
	long long ans = 1;
	while(b)
	{
		if(b & 1) ans = ans * a % mod;
		b >>= 1, a = a * a % mod;
	}
	return ans;
}
inline long long C(int n, int m)
{return fac[n] * inv[m] % mod * inv[n - m] % mod;}
inline void init()
{
	fac[0] = inv[0] = 1;
	for(int i = 1; i <= 1000000; ++i) fac[i] = fac[i - 1] * i % mod;
	inv[1000000] = qpow(fac[1000000], mod - 2);
	for(int i = 999999; i >= 1; --i) inv[i] = inv[i + 1] * (i + 1) % mod;
}
long long f[N], g[N], ans;
inline long long func(int n, int m) {return C(m, n - m);}

int main()
{
//	freopen("text.in", "r", stdin);
//	freopen("prog.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n; init();
	for(int i = (n + 1) / 2; i <= n - 1; ++i)
	{
		g[i] = func(n - 2, i - 1);
		g[i] = g[i] * fac[i] % mod * fac[n - i - 1] % mod;
	}
	for(int i = 1; i <= n - 1; ++i) f[i] = (g[i] - g[i - 1] + mod) % mod;
	for(int i = 1; i <= n - 1; ++i) ans = (ans + f[i] * i % mod) % mod;
	cout << ans << '\n';
	return 0;
}
/*

*/
```

---

## 作者：AzusidNya (赞：0)

### [AGC023C] Painting Machines 题解

- 有一排 $n$ 个格子，从左到右编号为 $1$ 到 $n$。
- 有 $n - 1$ 个机器，从左到右编号为 $1$ 到 $n - 1$，操作第 $i$ 个机器可以将第 $i$ 个和第 $i + 1$ 个格子染黑。
- 定义一个 $n - 1$ 的排列 $P$ 的分数为，依次操作 $P_1,P_2,\cdots,P_{n-1}$，第一次染黑所有格子的时刻。
- 求所有排列 $P$ 的分数之和，对 $10^9 + 7$ 取模。
- $1\le n\le 10^6$.

#### Solution

考虑操作第 $i$ 个机器。如果在操作第 $i$ 个机器的时候，第 $i$ 个格子和第 $i + 1$ 个格子都已经是黑色的了，那么这次操作就是无效的。并且因为第 $i$ 个格子和第 $i + 1$ 个格子被染黑了，所以在这之前已经操作了第 $i - 1$ 个机器和第 $i + 1$ 个机器。

即，如果对于排列中的一个数 $P_i$，如果有 $P_i - 1$ 和 $P_i + 1$ 出现在 $i$ 前，那么 $P_i$ 就是无效操作。 

那么对于一个排列 $P$，假设在 $t$ 时刻染黑了所有格子，那么意味着第 $t$ 次操作是有效操作，而第 $t + 1$ 到第 $n - 1$ 次操作一定都是无效的。将第 $1$ 到 $t$ 这一序列称为 “有效序列”，第 $t + 1$ 到第 $n$ 序列称为 “无效序列”。

考虑通过枚举无效序列的长度来统计方案，设此时无效序列的长度为 $i$，此时 $t$ 是定值 $n - i - 1$，因此我们只需要算有多少种排列的无效序列长度为 $i$。设 $f_i$ 为无效序列长度大于或等于 $i$ 的方案数。

首先，对第一台机器的操作和对第 $n - 1$ 台机器的操作总是有效的，因为没有办法在不操作这两台机器的情况下染黑第 $1$ 个格子和第 $n$ 个格子。

可以得到一个结论，如果有 $x$ 在无效序列中，那么 $x + 1$ 和 $x - 1$ 都在有效序列中。这个结论可以反证法证明。假设 $x - 1$ 和 $x$ 都在无效序列中，那么对于 $x$ 而言，需要 $x - 1$ 在 $x$ 前面，而对于 $x - 1$ 而言，又需要 $x$ 在 $x - 1$ 前面，可以推出矛盾，$x + 1$ 同理。

我们在原序列中选 $i$ 个数出来组成无效序列，不能选第 $1$ 和第 $n - 1$ 个数，并且不能选择相邻的数。

通过组合数可以得到选数的方案数为 $\binom{n - i - 2}{i}$。

那么有： 
$$f_i = \binom{n - i - 2}{i} \times (n - i - 1)! \times i!$$

那么无效序列长度恰好为 $i$ 的方案数即为 $f_{i} - f_{i + 1}$。

最终答案为 
$$\sum_{i=1}^n f_i \times (n - i - 1)$$

#### code
```cpp
#include<iostream>
#include<fstream>
#include<algorithm>
#define int long long
using namespace std;
const int modd = 1000000007;
int n, m, res = 0;
int ksm(int u, int v){
	int ret = 1;
	while(v){
		if(v & 1) ret = ret * u % modd;
		u = u * u % modd, v >>= 1;
	}
	return ret;
}
int fac[1000005], inv[1000005];
int C(int u, int v){
	return (fac[u] * inv[v] % modd) * inv[u - v] % modd;
}
int f[1000005];
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	fac[0] = inv[0] = 1;
	for(int i = 1; i <= 1000000; i ++)
		fac[i] = (fac[i - 1] * i) % modd;
	inv[1000000] = ksm(fac[1000000], modd - 2);
	for(int i = 999999; i >= 1; i --)
		inv[i] = inv[i + 1] * (i + 1) % modd;
	cin >> n;
	if(n == 2) return cout << 1, 0;
	if(n == 3) return cout << 4, 0; 
	m = n - 3;
	int tk = m;
	for(int i = 0; i <= m; i ++){
		if(2 * i - 1 > m){
			tk = i - 1;
			break;
		}
		int tmp = C(m - i + 1, i);
		f[i] = (tmp * fac[n - 1 - i] % modd) * fac[i] % modd;
	}
	for(int i = 0; i <= tk; i ++)
		f[i] = (((f[i] - f[i + 1]) % modd) + modd) % modd;
	for(int i = 0; i <= tk; i ++)
		res = (res + (f[i] * (n - 1 - i) % modd)) % modd;
	cout << res;
	return 0;
}
```
[record](https://atcoder.jp/contests/agc023/submissions/46714703)

---

