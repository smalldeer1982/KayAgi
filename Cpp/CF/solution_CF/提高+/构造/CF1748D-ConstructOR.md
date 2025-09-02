# ConstructOR

## 题目描述

You are given three integers $ a $ , $ b $ , and $ d $ . Your task is to find any integer $ x $ which satisfies all of the following conditions, or determine that no such integers exist:

- $ 0 \le x \lt 2^{60} $ ;
- $ a|x $ is divisible by $ d $ ;
- $ b|x $ is divisible by $ d $ .

Here, $ | $ denotes the [bitwise OR operation](https://en.wikipedia.org/wiki/Bitwise_operation#OR).

## 说明/提示

In the first test case, $ x=18 $ is one of the possible solutions, since $ 39|18=55 $ and $ 12|18=30 $ , both of which are multiples of $ d=5 $ .

In the second test case, $ x=14 $ is one of the possible solutions, since $ 8|14=6|14=14 $ , which is a multiple of $ d=14 $ .

In the third and fourth test cases, we can show that there are no solutions.

## 样例 #1

### 输入

```
8
12 39 5
6 8 14
100 200 200
3 4 6
2 2 2
18 27 3
420 666 69
987654321 123456789 999999999```

### 输出

```
18
14
-1
-1
0
11
25599
184470016815529983```

# 题解

## 作者：As_Snow (赞：9)

[可能更好的食用体验](https://www.cnblogs.com/As-Snow/p/16894871.html)

既然题目中用到了位运算，那我们就用二进制来解决这道题。
### 1.判无解
观察 $3\,4\,6$ 这个样例，我们将其分解二进制：
$$
\begin{aligned}
(3)_{10} &= (11)_2 \\
(4)_{10} &= (100)_2\\
(6)_{10} &= (110)_2\\
\end{aligned}
$$
我们设 $\operatorname{lowbit}(x)$ 表示 $x$ 最末尾的 $1$ 在第几位，那么我们可以发现一条性质：$\operatorname{lowbit}(d)\le\operatorname{lowbit}(a\operatorname{ or }b)$。如果不满足，那么一定无解。
### 2.构造 $x$
我们来分析样例中的第一组数据：
$$
\begin{aligned}
a &= 1100\\
b &= 100111\\
d &= 101\\
\end{aligned}
$$
$$
\begin{aligned}
1100&\\
100111&\\
\text{---------------}\\
101&\\
101\;\;&\\
101\;\;\;\;\;\;\;\;\;\\
\text{---------------}\\
10101111
\end{aligned}
$$
我们可以发现 $x$ 有若干个 $d$ 相加得到，并且 $(a\operatorname{or}x )=x$,$(b\operatorname{or}x )=x$,所以一定满足 $d\,|\,(a\operatorname{or}x)$ 且 $d\,|\,(a\operatorname{or}x)$。

$x$ 的构造方法如上所示。设 $c\gets (a\operatorname{or}b)$，则对于 $c$ 的每 $i$ 位二进制位为 $1$，如果 $x$ 的第 $i$ 位也为 $1$ 则跳过，否则 $x\gets x+2^{i-\operatorname{lowbit}(d)}$。

### Code
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T,a,b,d,k,x;
void solve(){
	cin>>a>>b>>d;
	k=x=0;//k表示lowbit(d)
	while((d>>k&1)^1)k++;
	for(int i=0;i<30;i++)
		if( ((a|b)>>i&1) && (x>>i&1)==0 )
			if(i<k)return void(puts("-1"));//判无解
			else x+=(d<<i-k);
	cout<<x<<endl;
}
signed main(){
	cin>>T;
	while(T--)solve();
	return 0;
}
```
P.s. 应为构造方式比较特殊，所以输出会和样例输出不一样，~~不要像我一样傻傻的为此去调了二十分钟~~。

#### 样例输出
```
175
14
-1
-1
2
27
64446
143838208856161791
```

---

## 作者：uid_310801 (赞：4)

最优解都被大佬们讲的差不多了，本蒟蒻讲讲我的赛时解法。

设 $k=a$ $or$ $b$，则题目就是要找出一个 $n$ 使得 $d|(n$ $or$ $k)$。

首先因为 $d$ 的倍数一定是 $\operatorname{lowbit}(d)$ 的倍数，所以若 $k$ 不能整除 $\operatorname{lowbit}(d)$ 则一定无解。

设 $p=\operatorname{highbit}(k)\times 2$，若能找出一组解满足 $px+k \mod d=0$，则答案就是 $px$。

简单证明一下，$x$ 的大小不会影响 $p$ 以下位的值，那么 $px+k$ 一定等于 $px$ $or$ $k$.

显然上面那个式子可以用 exgcd 求解。于是这题就做完了。

---

## 作者：jiangtaizhe001 (赞：4)

[可能更好的阅读体验](https://www.cnblogs.com/jiangtaizhe001/p/16886470.html)

[题目传送门](https://codeforces.com/contest/1748/problem/D)

### 题目大意
给定 $a,b,d$，要求找到一个 $0\le x\le 2^{60}$，满足 $a|x,b|x$ 都是 $d$ 的倍数（$|$ 代表按位或）。  
$T\le 10^4$，$0\le a,b,d\le 2^{30}$

### 题目解析
乍一看没什么思路，赛时想了很久才做出来。  

显然当 $a,b$ 的最低位的 $1$ 比 $d$ 的最低位还要低的时候，无解。  
首先我们发现要让两个数字都是 $d$ 的倍数就很麻烦，所以我们可以试着让这两个数字变成一个数字。  
设 $c=a|b$，那么其实只要让 $x|c=x$ 并且 $x$ 是 $d$ 的因数就可以了。  
因为 $x|c=x$，所以不难发现 $x$ 的一些位必定为 $1$。  
从低位到高位考虑 $x$ 的每一个限制。如果当前 $x$ 的这一位是 $0$，但是 $c$ 的这一位是 $1$，那么我们就把 $d$ 的最低位的 $1$ 通过移位操作和这一位对齐，然后加上移位后的数字，这样这一位就是 $1$ 了。  
因为 $a,b,d\le 2^{30}$ 所以这样构造出来的 $x$ 满足 $x\le(a|b)\times d\le 2^{60}$，一定合法。  
时间复杂度 $O(\log a)$  

```cpp
ll a,b,c,d,ans; int cnt;
void work(){
	a=read(); b=read(); c=a|b; d=read(); ans=0; int i;
	cnt=0; for(i=0;i<30;i++) if(d&(1<<i)){ cnt=i; break; }
	for(i=0;i<30;i++) if((c&(1<<i))&&!(ans&(1<<i))){
		if(i<cnt){ puts("-1"); return; }
		ans+=(d<<(i-cnt));
	} print(ans),pc('\n'); assert((a|ans)%d==0&&(b|ans)%d==0); return;
}
```

---

## 作者：VinstaG173 (赞：3)

题外话：场上一眼抽象题，没看到数据范围 $2^{30}$ 就先去开 E 了。好似。

感觉 $a\operatorname{or}k\neq b\operatorname{or}k$ 的情况我不会做。所以考虑 $a\operatorname{or}k=b\operatorname{or}k$。这种情况下我们直接希望 $k=(a\operatorname{or}b)\operatorname{or}k$。

那问题就变成了找一个满足 $k=(a\operatorname{or}b)\operatorname{or}k$ 且 $d\mid k$ 的 $k$。首先如果 $a\operatorname{or}b$ 所含 $2$ 的幂次小于 $d$ 所含 $2$ 的幂次，则显然无解。否则我们同时除掉 $d$ 所含 $2$ 的幂，转化为 $d$ 是奇数的情况。

注意到 $a,b,d<2^{30}$，我们直接从低位到高位枚举，一旦第 $i$ 位上 $k$ 为 $0$ 但 $a\operatorname{or}b$ 为 $1$，我们就将 $k$ 变为 $k+d\cdot2^i$。由于 $a\operatorname{or}b<2^{30}$，故最终的 $k<2^{30}d<2^{60}$。

Code:
```cpp
ll a,d,k;
int b;
inline void solve(){
	a=rd(d)|rd(d),rd(d);
	b=k=0;while((d&1)==0)
		++b,d>>=1;
	if(a&((1<<b)-1)){
		puts("-1");return;
	}a>>=b;
	for(rg int c=0;(1<<c)<=a;++c){
		if((a&(1<<c))&&!(k&(1<<c)))
			k+=d<<c;
	}printf("%lld\n",k<<b);
}
```

---

## 作者：ABlueCat (赞：3)

# CF1748D ConstructOR 题解
## 题意简述
给定三个整数 $a, b, d$，需要找到一个 $x$ ，满足：

* $a|x$ 可被 $d$ 整除；
* $b|x$ 可被 $d$ 整除；
* $0 \leq x \lt 2^{60}$.

其中，$a, b, d \leq 2^{30}$，$|$ 表示按位或运算。

需要给出一个 $x$ 的解，或者报告其无解。

## 题意分析
定义 $\text{ctz(x)}$ 的值为 $x$ 的二进制表示中从最低位开始连续的 $0$ 的个数。那么不难发现，对于按位或运算，$\text{ctz(x)}$ 的值是不增的。

因此，我们可以得出，如果 $\text{ctz(d)} \gt \text{ctz(a)}$ 或 $\text{ctz(d)} \gt \text{ctz(b)}$，则可报告无解。理由如下：

令 $a=2^{\text{ctz(a)}} \times a'$，$b=2^{\text{ctz(b)}} \times b'$， $d=2^{\text{ctz(d)}} \times d'$ （$a', b', d'$ 中均不含因子 $2$ ）

因$\text{ctz(d)} \gt \text{ctz(a)}$ 或 $\text{ctz(d)} \gt \text{ctz(b)}$，且在按位或操作中 $\text{ctz}$ 值不增，因此 $d$ 必然会比 $a,b$ 多至少一个因子 $2$ ，故不可被整除。

观察样例，输出 `-1` 的情况与上述情况符合。

那么，如果不满足上述情况的话，解的存在性如何？由于按位或的性质貌似不是很明显，那么我们就观察大样例：

输入：`987654321 123456789 999999999`

输出：`184470016815529983`

把输出放在计算器中，发现其二进制表示为：

`001010001111010111101000000010111111111111111111111111111111`

这个结果是很具启发性的，因为这个数的二进制近乎后半部分全都是 `1` ，而对于按位或操作后面全都是 `1` 的话，按位或了和没按位或一样。样例也支持了这个想法，因为答案的 $x|a = x$、$x|b = x$ 。数据范围 $0 \leq x \lt 2^{60}$, $a, b, d \leq 2^{30}$ 也貌似在提示需要一个后 $30$ 位均为 `1` 的 $d$ 的倍数 $x$ 。

设：

$$x=k\times2^{30}-1$$

式中 $k$ 为一个无特定意义的数（可感性理解为上述样例中 `001010001111010111101000000010` 的那一部分，也就是“前面”的一部分），而减去 $1$ 是为了让后 $30$ 位都是 `1`。

满足：

$$x \equiv 0 \pmod d$$

代入上式，变形得：

$$k \times 2^{30} \equiv 1 \pmod d$$

至此，问题转化为找到一个 $k$，使得上述同余方程成立。改写为二元线性不定方程为：

$$k \times 2^{30} - dy = 1$$

因为 $1 | \text{gcd}(2^{30}, d)$ 成立（这里的 $|$ 是数论中的整除符号），根据裴蜀定理，必定有整数解。利用扩展欧几里得算法解上述不定方程，找到一个**正整数** $k$ ，那么答案就是 $k\times2^{30}-1$。

另外，由于后 $30$ 位全 `1` 是在 $\text{ctz(d)}=0$ 的前提下做出的，如果非 $0$，那么我们把三个数都右移到 $d$ 没有后导 `0` 为止，解出答案后再左移 $\text{ctz(d)}$ 位即可。

## 代码
```c++
#include <bits/stdc++.h>
#define int long long
using namespace std;

typedef long long ll;

ll exgcd(ll a, ll b, ll &x, ll &y) {
    if (!b) {
        x = 1;
        y = 0;
        return a;
    }
    ll d = exgcd(b, a % b, x, y);
    ll t = x;
    x = y;
    y = t - (a / b) * y;
    return d;
}

inline void solve()
{
    int a, b, d;
    scanf("%lld %lld %lld", &a, &b, &d);
    int a1 = __builtin_ctz(a);
    int b1 = __builtin_ctz(b);
    int d1 = __builtin_ctz(d);
    if (a1 < d1 || b1 < d1)
    {
        printf("-1\n");
        return;
    }
    int mo = 30;
    for (int i = 0; i < d1; ++i)
    {
        a >>= 1;
        b >>= 1;
        d >>= 1;
        mo--;
    }
    int aa = (1 << mo);
    int bb = d;
    int x = 0, y = 0;
    exgcd(aa, bb, x, y);
    int kk = bb / __gcd(aa, bb);
    x = (x + kk) % kk;
    if (x == 0) x += kk;
    int ans = (x << mo) - 1;
    ans <<= d1;
    printf("%lld\n", ans);
}

signed main()
{
    int t;
    scanf("%lld", &t);
    while (t--) solve();
    return 0;
}
```

---

## 作者：chroneZ (赞：2)

# $\texttt{Description}$

$T$ 组询问，每次询问给定 $a,b,d(a,b,d<2^{30})$，求任意一个 $x(x<2^{60})$ 使得 $a|x,b|x$ 均为 $d$ 的倍数（其中 $|$ 指位运算 $\mathrm{or}$ ）

# $\texttt{Analysis}$

提示：解题的关键在于 $a,b,d < 2^{30}$ 而 $x < 2^{60}$。

**由于 $a|x,b|x$ 均为 $d$ 的倍数，这意味着 $a,b$ 二进制表示中为 $1$ 的位一定是 $d$ 的某个倍数的二进制表示中为 $1$ 的位的子集。**

所以若 $\min(\mathrm{lowbit}(a),\mathrm{lowbit}(b))<\mathrm{lowbit}(d)$，就不存在一个 $d$ 的倍数完全包含 $a,b$。此时无解。

那么在有解的情况下，显然这个 $d$ 的倍数需要包含 $a,b$ 的所有位。

## 算法一

记我们需要的 $d$ 的倍数为 $res$，$\mathrm{lowbit}(d)=c$，当前考虑 $res$ 的第 $i$ 位。从低位向高位扫一遍，**如果 $a,b$ 中有一者在这一位上为 $1$，且当前的 $res$ 的第 $i$ 位不为 $1$**，那么 `res += (d << (i - c))`。

最终 $res$ 一定是 $d$ 的倍数且 $res<2^{60}$，直接输出 $res$ 即可。

## 算法二

考虑直接构造一个 $x$ 使得 $x$ 的 $[\mathrm{lowbit}(d),29]$ 位均为 $1$，且 $x$ 是 $d$ 的倍数，这样一来同时保证了 $a|x = b|x = x$。

对 $[\mathrm{lowbit}(d),29]$ 位从低位向高位按同样的道理扫一遍即可。

# $\texttt{Main Code}$

```cpp
void solve(){
	i64 a, b, d;
	cin >> a >> b >> d;
	if(min(__builtin_ffs(a), __builtin_ffs(b)) < __builtin_ffs(d)){
		cout<<"-1\n";
		return;
	}
	int c = __builtin_ctz(d);
	i64 res = 0;
	for(int i = c; i < 30; ++i){
		if((res >> i) & 1) continue;
		if(!(((a | b) >> i) & 1)) continue;	// 算法一就是在算法二的基础上多了这一句
		res += (d << (i - c));
	}
	cout << res << '\n';
}
```


---

## 作者：Imiya (赞：0)

考虑令 $a|x=b|x$，设 $c=a|b$ 那么 $x$ 一定满足 $x|c=x$。然后需要找出一个是 $d$ 的若干倍的 $x$。可以考虑让若干个左移若干位的 $d$ 去填满 $c$ 中的 $1$，余出来的部分让 $x$ 来填。

相当于一开始 $x=0$，然后从低到高遍历 $c$ 的每一位，若 $c$ 这一位为 $1$ 且当前的 $x$ 这一位不是 $1$，则让 $d$ 左移若干位使 $d$ 的最低位 $1$ 与 $c$ 的这一位对齐，然后把这个左移过的 $d$ 加进 $x$ 里。这样求出的 $x$ 一定满足 $x=x|c$ 并且被 $d$ 整除并且小于 $2^{60}$。

需要注意的是，若 $\text{lowbit}(d)<\text{lowbit}(c)$，则无法用这种方法构造出答案。但发现这种情况则一定有 $\text{lowbit}(d)<\text{lowbit}(a)$ 或 $\text{lowbit}(d)<\text{lowbit}(b)$，一定无解。

##### 代码

```cpp
#include<iostream>
using namespace std;
#define int long long
int a,b,c,d,x;
inline int lowbit(int x){return x&-x;}
signed main(){
    // freopen("read.in","r",stdin);
    int t;cin>>t;
    while(t--){
        cin>>a>>b>>d;
        x=0;
        c=a|b;
        if(lowbit(d)>lowbit(c)){cout<<-1<<endl;continue;}
        // cout<<c<<endl;
        for(int i=0;i<30;i++){
            if((c&(1<<i))&&!(x&(1<<i)))x+=(d<<i)/lowbit(d);
        }
        // cout<<(a|b)<<' '<<(a|x)<<' '<<(b|x)<<' ';
        cout<<x<<endl;
    }
    return 0;
}
```


---

## 作者：XL4453 (赞：0)

### $\text{Difficluty : 2100}$
---
### 解题思路：

对于一个特定的 $d$，称一个数 $x$ 是可以表示的当且仅当存在 $k\in Z^+$ 使得 $x|kd=kd$。容易发现是否可以被表示和且仅和二进制下的最低位有关。

如果 $d$ 的最低位较高，则无论如何变化 $k$，$x$ 的最低位都无法被表示，否则只需要用最低位贪心即可在 $O(\log a)$ 的时间求出一组可行解。

回到原题，令 $c=a|b$，判断 $c$ 是否可以被 $d$ 表示，如果不能直接输出 $-1$，否则使用上述方法构造的数就是一组可行解。

不会在代码中体现的一点是，由于 $c,d$ 最多是 $2^{30}$，而可以输出的解最大是 $2^{60}$，不需要考虑越界的情况。

---
### 代码：

```cpp
#include<cstdio>
using namespace std;
#define int long long
int T,a,b,d,c,ans,d_,fi;
signed main(){
	scanf("%lld",&T);
	while(T--){
		scanf("%lld%lld%lld",&a,&b,&d);
		c=a|b;ans=0;d_=d;fi=0;
		while(d_%2==0){
			fi++;
			d_/=2;
		}
		for(int i=fi;i<=31;i++){
			if(((c&(1ll<<i))!=0)&&((ans&(1ll<<i))==0)){
				ans+=d<<(i-fi);
			}
		}
		if((ans|a)==ans&&(ans|b)==ans){
			printf("%lld\n",ans);
		}
		else{
			printf("-1\n");
		}
	}
	return 0;
}
```


---

## 作者：Polaris_Australis_ (赞：0)

很诈骗的一道题。我们发现，我们如果确定了最终答案为 $x$，此时一定满足 $a|x$ 是 $d$ 的倍数，且 $b|x$ 是 $d$ 的倍数，那么我们不妨假设 $\frac{a|x}{d}=\frac{b|x}{d}=t$，那么最终 $x=t$ 一定为一组答案，此时我们希望 $(t\times d)|a=(t\times d)$ 且 $(t\times d)|b=(t\times d)$，则 $t\times d$ 二进制下后 $30$ 位的 $1$ 越多越好，而 $t\times d$ 的二进制表示存在以下性质：

1. 所有比 $d$ 的最低位 $1$ 低的位全部不可能为 $1$。
2. 如果 $t\times d<2^{60}$，且 $d<2^{30}$，设 $d$ 的最低位 $1$ 为 $low$，则存在一种构造方式，使得 $t\times d$ 的 $[low,30]$ 这些二进制位全部为 $1$。

对于第二个性质，可以直接给出一种构造：

设当前答案为 $x$，$x$ 初始为 $0$，枚举 $d\times2^k$，如果当前 $x$ 在 $d\times2^k$ 的最低位 $1$ 上为 $0$，则 $x\leftarrow x+d\times2^k$。

代码：

```cpp
// Problem: D. ConstructOR
// Contest: Codeforces - Codeforces Round #833 (Div. 2)
// URL: https://codeforces.com/contest/1748/problem/D
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
#define gdb
#ifdef gdb
#define dbg cerr << "Wilson_Inversion\n"
#define debug(x) cerr << "[" << #x << "=" << x << "]\n"
#define DEBUG(x, __n) {                                                         \
	cerr << "[" << #x << ":\n";                                                 \
	for (int __i = 0; __i < __n; ++ __i) cerr << __i << ":" << x[__i] << ",\n"; \
	cerr << __n << ":" << x[__n] << "]\n"                                       \
}
#else
#define dbg 0
#define debug(x) 0
#define DEBUG(x, __n) 0
#endif
#define pb push_back
#define mk make_pair
#define ff first
#define ss second
#define int long long
#define db double
#define miny(x, y) x = min(x, y)
#define maxy(x, y) x = max(x, y)
#define lowbit(x) ((x) & (-(x)))
#define fu(i, l, r) for (int i = (l); i <= (r); ++i)
#define fd(i, r, l) for (int i = (r); i >= (l); --i)
#define mem(x, y) memset(x, y, sizeof (x))
#define file(x)                   \
	freopen(x ".in", "r", stdin); \
	freopen(x ".out", "w", stdout);
#define mod 998244353
#ifdef int
#define inf 0x3f3f3f3f3f3f3f3f
#else
#define inf 0x3f3f3f3f
#endif
#define inv(x) qp(x, mod - 2)
using namespace std;
namespace Std {
	void read(int &x) {
		x = 0;
		int y = 1;
		char c = getchar();
		while (c < '0' || c > '9') {
			if (c == '-') y = -1;
			c = getchar();
		}
		while (c >= '0' && c<= '9') {
			x = (x << 1) + (x << 3) + (c & 15);
			c = getchar();
		}
		x *= y;
	}
	void write(int x) {
		char s[50];
		int tot = 0;
		while (x) {
			s[++tot] = (x % 10);
			x /= 10;
		}
		while (tot) putchar(s[tot--]);
	}
	int qp(int x, int y) {
		int cmp = 1;
		while (y) {
			if (y & 1) (cmp *= x) %= mod;
			(x *= x) %= mod;
			y >>= 1;
		}
		return cmp;
	}
	int T, a, b, d, mat[70][70];
	
	void main() {
		read(T);
		while (T --) {
			read(a);
			read(b);
			read(d);
			if (((lowbit(d) - 1) & a) || ((lowbit(d) - 1) & b)) {
				puts("-1");
				continue;
			}
			int low = __builtin_ctzll(d);
			int now = 0;
			for (int i = low; i < 30; ++ i) {
				if (((now >> i) & 1) ^ 1) now += (d << (i - low));
			}
			printf("%lld\n", now);
		}
	}
}  // namespace Std
#undef int
int main() {
	Std :: main();
	return 0;
}
```


---

