# Baby Ehab Plays with Permutations

## 题目描述

This time around, Baby Ehab will play with permutations. He has $ n $ cubes arranged in a row, with numbers from $ 1 $ to $ n $ written on them. He'll make exactly $ j $ operations. In each operation, he'll pick up $ 2 $ cubes and switch their positions.

He's wondering: how many different sequences of cubes can I have at the end? Since Baby Ehab is a turbulent person, he doesn't know how many operations he'll make, so he wants the answer for every possible $ j $ between $ 1 $ and $ k $ .

## 说明/提示

In the second example, there are $ 3 $ sequences he can get after $ 1 $ swap, because there are $ 3 $ pairs of cubes he can swap. Also, there are $ 3 $ sequences he can get after $ 2 $ swaps:

- $ [1,2,3] $ ,
- $ [3,1,2] $ ,
- $ [2,3,1] $ .

## 样例 #1

### 输入

```
2 3```

### 输出

```
1 1 1```

## 样例 #2

### 输入

```
3 2```

### 输出

```
3 3```

## 样例 #3

### 输入

```
4 2```

### 输出

```
6 12```

# 题解

## 作者：pigstd (赞：8)

考虑反着思考，设 $f_{i,j}$ 表示长度为 $i$ 的所有排列中，最少需要交换 $j$ 次可以得到原排列（$p_i=i$）的排列数，状态转移的时候可以考虑对 $p_i$ 分类讨论，如果 $p_i=i$，那么不用管它，$f_{i,j}=f_{i-1,j}$，否则，对于 $p_i = 1 \dots (n-1)$ 的情况，需要把 $p_i$ 和前面的数进行一次交换，有 $f_{i,j}=(i-1) \times f_{i-1,j-1}$，总的来说，得到 $f_{i,j}=f_{i-1,j}+(i-1)\times f_{i-1,j-1}$，一开始所有的 $f_{i,0}=1$。因为这只是最少需要的交换次数，那么交换 $i$ 次的答案就是 $f_{n,i}+f_{n,i-2}+ \dots$。看上去非常正确，只可惜时间复杂度 $O(n \times k)$，过不去。

注意到，因为最多交换 $k$ 次，那么最多有 $2k$ 的数位置会变化，可以尝试着从这里入手。一个很 naive 的想法是枚举有 $i$ 个位置变化，但是这样子做会算重。可以尝试着设 $g_{i,j}$ 表示长度为 $i$ 的所有排列中，满足 $p_l \ne l$，需要 $j$ 次交换的答案，那么交换 $x$ 次的答案就是 $\displaystyle \sum_{i=0}^{\min(n,2\times x)}(\dbinom{n}{i} \times  \sum_{j=0}^{\frac x 2 } g_{i,x-2\times j})$。这样就不会算重了。

然而怎么算出 $g_{i,j}$ 呢？可以考虑在原来算出来的 $f_{i,j}$ 上做容斥。根据容斥定理就很容易得到：$\displaystyle g_{i,j}= \sum_{x=0}^i (-1)^x \times f_{i-x,j} \times \dbinom{i}{x}$。

然后就可以 $O(k^3)$ 计算出 $g$ 然后得出答案了。


```cpp
#include<bits/stdc++.h>
#define int long long
#define pb push_back
#define WT int T=read();while(T--) 
#define NO puts("NO");
#define YES puts("YES");
using namespace std;

inline int read()
{
    char c=getchar();int x=0;bool f=0;
    for(;!isdigit(c);c=getchar())f^=!(c^45);
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    if(f)x=-x;return x;
}

const int Mod=1e9+7;
const int M=410;
int n,k,f[M][M],g[M][M],fac1[M],ifac[M],fac2[M];

int C(int k){return fac2[k]*ifac[k]%Mod;}
int C(int m,int n){return fac1[m]*ifac[n]%Mod*ifac[m-n]%Mod;}

int poww(int a,int b)
{
	int res=1;
	while(b)
	{
		if (b&1)res=res*a%Mod;
		a=a*a%Mod,b>>=1;
	}return res;
}

void init(int n,int k)
{
	fac1[0]=ifac[0]=1,fac2[0]=1;
	for (int i=1;i<=min(n,2*k);i++)
		fac1[i]=fac1[i-1]*i%Mod,
		ifac[i]=poww(fac1[i],Mod-2),
		fac2[i]=fac2[i-1]*(n-i+1)%Mod;
}

signed main()
{
	n=read(),k=read();init(n,k);f[0][0]=1;
	for (int i=1;i<=min(n,2*k);i++)
	{
		f[i][0]=1;
		for (int j=1;j<=min(2*k,n);j++)
			f[i][j]=(f[i-1][j]+f[i-1][j-1]*(i-1))%Mod;
	}
	for (int i=0;i<=min(n,2*k);i++)
		for (int j=0;j<=k;j++)
			for (int ff=0;ff<=i;ff++)
				g[i][j]=(g[i][j]+((ff&1)?-1:1)*f[i-ff][j]*C(i,ff))%Mod;
//	for (int i=0;i<=n;i++)
//		for (int j=0;j<=n;j++)
//			cout<<i<<' '<<j<<' '<<g[i][j]<<endl;
	for (int i=1;i<=k;i++)
	{
		int ans=0;
		for (int j=min(2*i,n);j>=0;j--)
		{
			int sum=0;
			for (int p=i;p>=0;p-=2)
				sum=(sum+g[j][p])%Mod;
			sum=sum*C(j)%Mod;ans=(ans+sum)%Mod;
		}
		ans=(ans+Mod)%Mod;
		cout<<ans<<' ';
	}
	return 0;
}
// 2 3
```

---

## 作者：Leap_Frog (赞：8)

### P.S.
好欸，恭喜 @Leap_Frog 组合数求错调了一年，一度以为自己式子假掉咯！！！！![](//xn--9zr.tk/xk)  
**总之反正人均斯特林数大师，这里提供一个 式子+dp 的做法。**  

### Description.
给定一个长为 $n\ (n\le 10^9)$ 的排列，初始是 $\{1,2,...,n\}$。  
现在进行 $j$ 次操作，每次可以交换任意两个不相同的数。  
现在询问可以得到几个不同的排列，需要对 $j\in[0,k]$ 求出答案。$(k\le200)$  

### Solution.
首先，这里有一个 naive 的 dp 做法（@Leap_Frog 你个大憨憨赛场上没想到![](//xn--9zr.tk/jk)  
设 $dp_{i,j}$ 表示当前有 $i$ 个数，用 $j$ 次操作可以得到多少个本质不同的排列。  
这个看上去似乎很难转移，于是我们设 $dp_{i,j}$ 表示当前 $i$ 个数，从 $\{1,2,...,i\}$ 转移过来的最小次数是 $j$。  
和第一类斯特林数的转移类似，不能考虑新来一个操作会怎么样。  
考虑最后一个数，如果没有位移，那答案就是 $dp_{i-1,j}$。  
否则，操作次数会多一次，可以移动到任意一个数后面，答案就是 $dp_{i-1,j-1}\times(i-1)$。  
$$\therefore dp_{i,j}=dp_{i-1,j}+(i-1)\times dp_{i-1,j-1}$$  
当然，因为这是最小次数等于 $j$，观察 样例I 可以发现可以浪费步数。  
$$\therefore ans_j=\sum_{i\equiv j\pmod2\land i\le j}dp_{n,j}$$
复杂度 $O(n\times k)$，和 $n$ 相关，无法通过此题。  
终于找到一个正确做法了 ![](//xn--9zr.tk/ll)，但看上去很没有前途的样子。  
我们发现，如果仅做 $k$ 次操作，那被涉及到的数至多可能有 $2k$ 个，而 $k$ 很小。  
我们考虑枚举当前有 $i$ 个数被交换操作涉及到了，设当前枚举到的次数是 $j$  
我们首先需要选出 $i$ 个数，有 $\dbinom ni$ 贡献，然后再对它们乱排，有 $dp_{i,j}$  
所以当前答案就是 $\dbinom ni\times dp_{i,j}$。  
好欸！我们找到了个看起来很真的式子欸！而且还是 $O(n^2)$ 的是不是碾标了啊![](//xn--9zr.tk/se)  
可惜，你的做法假掉了咯！  
这样统计是会有重复的，比如 $\{1,2,3\}$ 变成 $\{2,1,3\}$，会在 $i=2$ 时统计一次，$i=3$ 时统计一次。  
考虑重复发生的本质是什么，是因为 $dp_{i,j}$ 并没有限制 $i$ 个数都需要变，这样在 $i+1$ 时可能重复。  
如果想去掉重复，在 $dp$ 过程中基本是不可能了。  
我们设 $g_{i,j}(k)$ 表示恰好有 $k$ 个不变的方案数，$f_{i,j}(k)$ 为钦定 $k$ 个不变其他任意的方案数。  
（这里 $i,j$ 意义和上文一样。  
$$\therefore f_{i,j}(k)=dp_{i-k,j}$$
**注意这边没有组合数因为 $dp$ 内部已经包含组合数了。**  
~~不会真有 nt xtw 在这个问题上看了至少 30min 没看出来吧不会吧不会吧~~  
同时有 $f_{i,j}(k)=\sum_{l=k}^{i}\dbinom il\times g_{i,j}(l)$  
显然二项式反演，反演一下就得到了。  
$$g_{i,j}(k)=\sum_{l=k}^i(-1)^{l-k}\times\dbinom il\times f_{i,j}(l)$$
我们需要求 $g_{i,j}(0)$，带入发现为。  
$$g_{i,j}(0)=\sum_{l=0}^i(-1)^l\times\dbinom il\times dp_{i-l,j}$$
然后，直接 $O(i)$ 暴力反演即可。  
复杂度 $O(k^3)$，可以通过此题。  

### Coding.
```cpp
//是啊……你就是那只鬼了……所以被你碰到以后，就轮到我变成鬼了{{{
#include<bits/stdc++.h>
using namespace std;typedef long long ll;
template<typename T>inline void read(T &x)
{
	x=0;char c=getchar(),f=0;
	for(;c<'0'||c>'9';c=getchar()) if(c=='-') f=1;
	for(;c>='0'&&c<='9';c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	if(f) x=-x;
}/*}}}*/
const int P=1e9+7;int n,K,fc[405],fi[405],iv[405],dp[405][405];
inline int ksm(int x,int q=P-2) {int r=1;for(;q;q>>=1,x=1ll*x*x%P) if(q&1) r=1ll*r*x%P;return r;}
inline int C(int n,int m)
{
	if(n<0||m<0||n<m) return 0;else if(n<=400) return 1ll*fc[n]*fi[m]%P*fi[n-m]%P;
	int r=1;for(int i=1;i<=m;i++) r=1ll*r*iv[i]%P*(n-i+1)%P;return r;
}
inline void pinit(int n)
{
	fc[0]=1;for(int i=1;i<=n;i++) fc[i]=1ll*fc[i-1]*i%P;
	iv[1]=1;for(int i=2;i<=n;i++) iv[i]=1ll*iv[P%i]*(P-P/i)%P;
	fi[0]=1;for(int i=1;i<=n;i++) fi[i]=1ll*fi[i-1]*iv[i]%P;
}
int main()
{
	read(n),read(K),pinit(400);for(int i=1;i<=400;i++) dp[i][0]=1;
	for(int i=1;i<=400;i++) for(int j=1;j<=400;j++) dp[i][j]=(dp[i-1][j]+1ll*(i-1)*dp[i-1][j-1])%P;
	int rs[2]={1,0};for(int j=1;j<=K;printf("%d%c",rs[j&1],j==K?'\n':' '),j++)
	{
		for(int i=1,e=min(j<<1,n),g=0;i<=e;i++,g=0)
		{
			for(int l=0;l<=i;l++) g=(g+1ll*((l&1)?P-1:1)*C(i,l)%P*dp[i-l][j])%P;
			rs[j&1]+=1ll*C(n,i)*g%P,rs[j&1]>=P?rs[j&1]-=P:0;
		}
	}
	return 0;
}
```

---

## 作者：serverkiller (赞：6)

提供一个不需要脑子的做法

## 题意:

$1,2,\cdots,n$ 的排列 定义 $f(i)$ 表示做恰好 $i$ 次操作 每次操作交换两个数 能得到的本质不同的排列数量

对于 $1,2,\cdots,k$ 求 $f(i)$

## solution

考虑你通过两次交换 可以把一个序列从 $i-2$ 变成 $i$ 所以我们可以考虑差分 即设 $g(i)$ 表示至少需要 $i$ 次操作才能形成的序列数量

考虑反过来想 也就是问多少个排列至少需要 $i$ 次交换可以变成递增的

我们有一个结论 对于一个排列 交换两个数让他们变成有序的最少次数是 $n-x$ 其中 $x$ 是排列的环数量

那么显然的是 $g(i)=\left[n\atop n - i\right]$

由于 $n$ 很大 所以我们又想起第二个式子:
$$
\left[n\atop n - i\right]=\sum_{j=0}^i\left<\left<i\atop j\right>\right>{n + j\choose 2i}
$$
直接 $\mathcal O(n^2)$ 递推 第二类欧拉数 就可以了 

```cpp
#include <bits/stdc++.h>
#define int long long
#define N 405
using namespace std;

const int mod = 1e9 + 7;
int n,k,f[N][N],ans[N];

int ksm(int a,int b,int mod = mod)
{
	int res = 1;
	while (b)
	{
		if (b & 1) res = res * a % mod;
		a = a * a % mod;
		b >>= 1;
	}
	return res;
}

int C(int n,int m)
{
	int ans = 1;
	for (int i = 1; i <= m; i++)
		ans = ans * (n - i + 1) % mod * ksm(i,mod - 2) % mod;
	return ans;
}

int clac(int n,int k)
{
	int ans = 0;
	for (int i = 0; i <= k; i++)
		ans = (ans + f[k][i] * C(n + i,2 * k)) % mod;
	return ans;
}

signed main()
{
	scanf("%lld%lld",&n,&k);
	f[0][0] = 1;
	for (int i = 1; i <= k; i++)
	{
		f[i][0] = 1;
		for (int j = 1; j <= i; j++)
			f[i][j] = ((2 * i - j - 1) * f[i - 1][j - 1] + (j + 1) * f[i - 1][j]) % mod;
	}
	ans[0] = 1;
	for (int i = 1; i <= k; i++) ans[i] = clac(n,i);
	for (int i = 2; i <= k; i++) ans[i] = (ans[i] + ans[i - 2]) % mod;
	for (int i = 1; i <= k; i++) printf("%lld ",ans[i]);
	puts("");
	return 0;
}
```

---

## 作者：Xu_brezza (赞：4)

## 前言

此文记录 @shr_ 神仙教我的神仙做法，不用什么乱七八糟的数，不用反演，也不用插值！！qaq。

## Solution

首先考虑钦定 $f[i]$ 为恰好用 $i$ 次操作，得到的排列数。然后发现你可以通过两次操作一正一反回到原点，换句话说，通过这样的操作我们发现 $f[i - 2]$ 对 $i$ 的答案也有贡献。那么对于 $i$，答案就是 $f[i] + f[i - 2] + f[i - 4].....$ 因为可以通过若干偶数次无用操作得到。而这些状态没有交集。

接下来考虑怎么求 $f[i]$。

不难想到我们枚举操作了多少个数，用了多少次操作，那这实际上就可以 $dp[i][j]$ 表示影响了 $i$ 个数，用了 $j$ 次操作，可以得到的不同序列的数。

那么

$$f[i] = \sum dp[j][i] \times {n \choose j}$$

接下来求 $dp$。

考虑交换操作，我们把这个当作连一条 $(i,j)$ 的无向边，那么对于 $x$ 个数，我们要影响到这 $x$ 个数，显然连完边后必然是树的样子，否则要么不连通，要么树上有环操作就被等价掉了，而这恰好只需要 $x - 1$ 次操作。

但是要考虑去重，神仙教我的一个技巧就是你考虑钦定结尾的一个数所在的位置，剩下再选 $x - 1$ 和他一起，也就是 ${i - 1}\choose {x - 1}$ 

而这 $x$ 个数体现在排列上是一个置换环，也就是连 $i \to p[i]$ 这条边，最终是一个环。

我们每次加进来一个置换环，我们一定可以构造出这 $x$ 个数的每一种排列，这里实际上是圆排列，所以方案数还要乘上 $(x - 1)!$

所以我们的 $dp$ 转移可以写成这样：
 
 $$ dp[i][j] = \sum dp[i - w][j - (w - 1)] \times {{i - 1}\choose {w - 1}}\times (w - 1)!$$
 
 这里的 $w$ 是我们枚举加进来的环的大小。
 
 最后愉快合并答案，加一加，就做完哩qwq。
 
 时间复杂度 $O(k^3)$
 
 ``` cpp
 #include<bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define Rep(i,a,b) for(int i=(a);i<(b);++i)
#define rrep(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
template <typename T>
inline void read(T &x){
    x=0;char ch=getchar();bool f=0;
    while(ch<'0'||ch>'9'){if(ch=='-')f=1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    if(f)x=-x;
}
template <typename T,typename ...Args>
inline void read(T &tmp,Args &...tmps){read(tmp);read(tmps...);}
int n,k;
const int mod = 1e9 + 7;
inline int ksm(int x,int y){
    int res = 1;
    while(y){
        if(y & 1)res = 1ll * res * x % mod;
        x = 1ll * x * x % mod;
        y >>= 1;
    }
    return res;
}
inline int Inv(int x){return ksm(x,mod - 2);}
inline void add(int &x,int y){
    if((x += y) >= mod)x -= mod;
}
template <typename T>
inline void write(T x){
    vector<int>s;
    while(x)s.push_back(x % 10),x /= 10;
    while(!s.empty())putchar(s.back() + '0'),s.pop_back();
}
const int K = 205;
int f[K];
int dp[K * 2][K],c[K * 2][K * 2],fac[K * 2];
signed main(){
    read(n,k);
    fac[0] = 1;
    rep(i,1,k * 2)fac[i] = 1ll * fac[i - 1] * i % mod;
    c[0][0] = 1;
    rep(i,1,k * 2){
        c[i][0] = c[i][i] = 1;
        rep(j,1,i - 1){
            add(c[i][j],c[i - 1][j - 1]);
            add(c[i][j],c[i - 1][j]);
        }
    }
    dp[0][0] = 1;
    rep(i,1,k * 2){
        rep(j,0,k){
            rep(w,2,i){
                if(j - w + 1 >= 0)
                add(dp[i][j],1ll * dp[i - w][j - w + 1] * fac[w - 1] % mod * c[i - 1][w - 1] % mod);
            }
        }
    }
    int C = 1;
    f[0] = 1;
    rep(i,1,k){
        C = n;
        rep(j,2,min(k * 2,n)){
            C = 1ll * C * (n - j + 1) % mod * Inv(j) % mod;
            add(f[i],1ll * dp[j][i] * C % mod);
        }
    }
    rep(i,1,k){
        if(i - 2 >= 0)add(f[i],f[i - 2]);
        // printf("%d ",f[i]);
        write(f[i]);
        putchar(' ');
    }
}
```

---

## 作者：tommy0221 (赞：3)

[CF1516E Baby Ehab Plays with Permutations](https://www.luogu.com.cn/problem/CF1516E)

发现交换 $k$ 次意味着至少 $n-k$ 个循环。

交换次数还要和 n-循环数 $\bmod 2$ 同余，因为每交换一次要么循环数少一个，要么多一个。

可以发现满足以上两个条件的排列一定可以得到。

于是通过第一类斯特林数来统计，答案就是
$$
ans_k=\sum_{i=n-k}^{n}[i\bmod 2 = (n-k)\bmod 2]S_1(n,i)
$$
$S_1$ 就是第一类斯特林数。

也就是说要求第一类斯特林数的后 $k$ 项。

众所周知 
$$
x^{\overline{n}}=\prod_{i=0}^{n-1}(x+i)=\sum_{i=0}^{n}\begin{bmatrix}n\\i\end{bmatrix}x^i
$$
如果把常数 $i$ 乘到 $x$ 上，我们就只需要提取前 $k$ 项，方便许多，也就是我们转而计算
$$
\prod_{i=0}^{n}(1+ix)
$$
前 $k$ 项。
$$
f(x)=\prod_{i=0}^{n-1}(1+ix)
$$
套路取 $\ln$ 再 $\exp$ 
$$
\ln f(x)=\sum_{i=0}^{n-1}\ln (1+ix)
$$
$$
=\sum_{i=0}^{n-1}-\sum_{j=1}^{k}\dfrac{(-i)^jx^j}{j}
$$
$$
=\sum_{j=1}^{k}\dfrac{(-1)^{j+1}x^j}{j}\sum_{i=0}^{n-1}i^j
$$
后面是自然数幂和前缀和。

可以构造 EGF 来计算：
$$
\sum_{j=0}^{n-1}\sum_{i=0}^{n-1}i^j\dfrac{x^j}{j!}
=\sum_{j=0}^{n-1}e^{ix}=\dfrac{1-e^{nx}}{1-e^x}
$$
注意分母常数项为 $0$，要上下同时除以 $x$ 再计算。

如果换成 MTT 可以 $O(k\log k)$，但是这么小数据范围不是很划算。于是我去补了套 $O(n^2)$ 的全家桶qwq

```cpp
#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mkp make_pair
#define pb push_back
#define sz(v) (int)(v).size()
typedef long long LL;
typedef double db;
template<class T>bool ckmax(T&x,T y){return x<y?x=y,1:0;}
template<class T>bool ckmin(T&x,T y){return x>y?x=y,1:0;}
#define rep(i,x,y) for(int i=x,i##end=y;i<=i##end;++i)
#define per(i,x,y) for(int i=x,i##end=y;i>=i##end;--i)
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
	while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
	return f?x:-x;
}
const int N = 205;

namespace poly {
#define mod 1000000007
inline int qpow(int n, int k) {
	int res = 1;
	for(; k; k >>= 1, n = 1ll * n * n % mod)
		if(k & 1) res = 1ll * n * res % mod;
	return res; 
}
int inv[N], fac[N], ifc[N];
inline void init(const int &n = N - 1) {
	inv[1] = 1;
	for(int i = 2; i <= n; ++i) inv[i] = 1ll * inv[mod % i] * (mod - mod / i) % mod;
	fac[0] = 1;
	for(int i = 1; i <= n; ++i) fac[i] = 1ll * i * fac[i - 1] % mod;
	ifc[n] = qpow(fac[n], mod - 2);
	for(int i = n - 1; i >= 0; --i) ifc[i] = 1ll * ifc[i + 1] * (i + 1) % mod;
}
vector <int> operator * (const vector <int> &a, const vector <int> &b) {
	int n = a.size(), m = b.size();
	vector <int> res(n + m - 1, 0);
	for(int i = 0 ; i < n; ++i)
		for(int j = 0; j < m; ++j)
			res[i + j] = (res[i + j] + 1ll * a[i] * b[j]) % mod;
	return res;
}
vector <int> poly_inv(const vector <int> &a) {
	int n = a.size();
	vector <int> res(n);
	res[0] = qpow(a[0], mod - 2);
	for(int i = 1; i < n; ++i) {
		int tmp = 0;
		for(int j = 0; j < i; ++j)
			tmp = (tmp + 1ll * res[j] * a[i - j]) % mod;
		res[i] = 1ll * qpow(a[0], mod - 2) * (mod - tmp) % mod;
	}
	return res;
}
vector <int> deriv(const vector <int> &a) {
	int n = a.size();
	vector <int> res;
	if(n == 1) return res;
	res.resize(n - 1);
	for(int i = 0; i < n - 1; ++i) 
		res[i] = 1ll * a[i + 1] * (i + 1) % mod;
	return res;
}

vector <int> integ(const vector <int> &a) {
	int n = a.size();
	vector <int> res(n + 1);
	res[0] = 0;
	for(int i = 1; i < n; ++i)
		res[i] = 1ll * a[i - 1] * inv[i] % mod;
	return res;
}
vector <int> poly_ln(const vector <int> &a) {
	int n = a.size();
	vector <int> res = integ(deriv(a) * poly_inv(a));
	res.resize(n);
	return res;
}
vector <int> poly_exp(const vector <int> &a) {
	int n = a.size();
	vector <int> res(n);
	res[0] = 1;
	for(int i = 1; i < n; ++i) {
		int tmp = 0;
		for(int j = 0; j < i; ++j)
			tmp = (tmp + 1ll * a[j + 1] * (j + 1) % mod * res[i - 1 - j]) % mod;
		res[i] = 1ll * tmp * inv[i] % mod;
	}
	return res;
}

}
using namespace poly;

int n, k;
signed main() {
	cin >> n >> k, ++k, init();
	vector <int> a(k), b(k), ans(k);
	for(int i = 0, j = n; i < k; ++i, j = 1ll * j * n % mod)
		a[i] = 1ll * j * ifc[i + 1] % mod, b[i] = ifc[i + 1];
	a = a * poly_inv(b), a.resize(k);
	for(int i = 0; i < k; ++i) a[i] = 1ll * fac[i] * a[i] % mod;
	b[0] = 0;
	for(int i = 1; i < k; ++i) {
		int tmp = 1ll * a[i] * inv[i] % mod;
		b[i] = i & 1 ? tmp : mod - tmp;
	}
	b = poly_exp(b);
	for(int i = 0; i < k; ++i) {
		ans[i] = b[i];
		if(i - 2 >= 0) ans[i] = (ans[i] + ans[i - 2]) % mod;
	}
	for(int i = 1; i < k; ++i) printf("%d ", ans[i]);
	return 0; 
}
```

---

## 作者：fade_away (赞：3)

# CF1516E. Baby Ehab Plays with Permutations

## Solution

因为组合水平不行所以只弄出来一个$O(k^4)$的做法（虽然随便改改可能就$O(k^3\log k)$或者$O(k^3)$了）而且因为没想清楚而自闭了很久，~~从而导致摸yu时间被阉割~~。

首先大概有个显然的性质：设一个任意的操作方案形成的最终序列为$a_1,a_2...a_n$，把$i$和$a_i$连边，会形成若干个环，有个显然的结论是到达该状态的最少操作次数是所有环长度减一的和，而一个任意方案可以表示为最少操作方案加上若干无用操作，显然无用操作个数为偶数（由逆序对个数奇偶性可得），因此我们只需要计算最少$i$步能到达的状态个数$Ans_i$，再让$Ans'_i=\sum_{k=0}^{\lfloor\frac{i}{2}\rfloor}Ans_{i-2k}$即为最终的答案。

因此我们要对每一个$i$，求出最少$i$步能到达的状态个数。

这就相当于取若干个环，使得所有环的长度减一的和为$i$，也就类似于做一个完全背包，取$j$个数形成环的方案数就是环排列个数$(j-1)!$，因此枚举枚举环长$i$，枚举该种环的个数$p$，再枚举环包含的点数$j$和操作次数$k$，可得：
$$
f_{j,k}=\sum_{p}f_{j-ip,k-(i-1)p} (i-1)^p\binom{j}{ip}\prod_{t=0}^{p-1}\binom{ip-it-1}{i-1}
$$

$$
Ans_{i} = \sum_{j} f_{j,i}\binom{n}{j}
$$

预处理一些东西即可计算。

## Code
```cpp
int fac[405], Inv[405], C[405][405], f[405][205], Ans[405], tmp[405][205], inv[405], Mul[405];
int quick_pow(int x, int y) {
	int ret = 1;
	for (; y ; y >>= 1) {
		if (y & 1) ret = 1ll * ret * x % mods;
		x = 1ll * x * x % mods;
	}
	return ret;
}
signed main() {
#ifndef ONLINE_JUDGE
	freopen("a.in", "r", stdin);
#endif
	int n, k;
	read(n), read(k);
	fac[0] = inv[0] = Inv[0] = 1;
	for (int i = 1; i <= k + k ; ++ i) Inv[i] = quick_pow(i, mods - 2);
	for (int i = 1; i <= k + k ; ++ i) fac[i] = 1ll * fac[i - 1] * i % mods, inv[i] = quick_pow(fac[i], mods - 2);
	for (int i = 0; i <= k + k ; ++ i) C[i][i] = C[i][0] = 1;
	for (int i = 1; i <= k + k ; ++ i)
		for (int j = 1; j < i ; ++ j) C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mods;
	f[0][0] = 1;
	for (int i = 2; i <= min(n, k + 1) ; ++ i) {
		for (int j = 0; j <= k + k ; ++ j)
			for (int t = 0; t <= k ; ++ t) tmp[j][t] = f[j][t], f[j][t] = 0;
		for (int j = 0; j <= k + k ; ++ j) Mul[j] = 1;
		for (int p = 0, mul = 1; p <= k ; ++ p) {
			for (int j = i * p ; j <= k + k ; ++ j) {
				for (int t = (i - 1) * p ; t <= k ; ++ t)
					f[j][t] = (f[j][t] + 1ll * tmp[j - i * p][t - (i - 1) * p] * Mul[i * p] % mods * mul % mods * C[j][i * p] % mods) % mods;
			}	
			for (int j = k + k; j >= 0 ; -- j)
				if (j >= i) Mul[j] = 1ll * Mul[j - i] * C[j - 1][i - 1] % mods;
				else Mul[j] = 0;
			mul = 1ll * mul * fac[i - 1] % mods;
		}
	}
	for (int i = 0, mul = 1; i <= min(k + k, n) ; ++ i) {
		for (int j = 0; j <= k ; ++ j) 
			Ans[j] = (Ans[j] + 1ll * f[i][j] * mul % mods * inv[i] % mods) % mods;
		mul = 1ll * mul * (n - i) % mods;
	}
	for (int i = 2; i <= k ; ++ i) Ans[i] = (Ans[i] + Ans[i - 2]) % mods;
	for (int i = 1; i <= k ; ++ i) print(Ans[i]), putc(' ');
	return 0;
}
```


---

## 作者：Krimson (赞：1)

~~我似乎用了个最不用脑子的做法...~~  

首先最基础的，可以反过来考虑：一个排列 $p$ 如果能通过 $k$ 次交换变回原排列，原排列通过 $k$ 次交换也能变回去。  

然后就可以联想到圆排列了，对于 $i$ 次变换，等价于是一个 $n-i$ 个园排列的方案数，这个玩意是第一类斯特林数（当然不知道这点也可以做）。  

然后可以列出 $dp$ 式子:$s(i,j)=(i-1)s(i-1,j)+s(i-1,j-1)$。  

注意到我们可以交换两次 $i,j$ 来消耗两次变换，所以最终 $k$ 次变换实际上的答案是
$$
\sum^{k}_{i=0}[i \bmod{2} \equiv k]s(n,n-i)  
$$  

$n$ 很大，如果直接暴力做的话复杂度是 $O(n^2)$ 的，但是可以发现 $k$ 比较小，同时我们需要求的值均为 $s(n,n-k)$ 的形式。  

~~打表~~可以发现， $s(n,n-k)$ 恰好是一个 $2k-1$ 次的多项式，直接用线性拉格朗日插值即可，复杂度 $O(k^2)$。  


_Code_
--------------

```cpp
#include<bits/stdc++.h>
using namespace std;
#define il inline
#define ri register int
#define ll long long
#define ui unsigned int
il ll read(){
    bool f=true;ll x=0;
    register char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-') f=false;ch=getchar();}
    while(ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
    if(f) return x;
    return ~(--x);
}
il void write(const ll &x){if(x>9) write(x/10);putchar(x%10+'0');}
il void print(const ll &x) {x<0?putchar('-'),write(~(x-1)):write(x);putchar('\n');}
il ll max(const ll &a,const ll &b){return a>b?a:b;}
il ll min(const ll &a,const ll &b){return a<b?a:b;}
const ll mod=1e9+7;
const int MAXN=205;
ll ksm(ll d,ll t){
    ll res=1;
    for(;t;t>>=1,d=d*d%mod)
        if(t&1) res=res*d%mod;
    return res;
}
ll add(ll x,ll y){return (x+=y)<mod?x:x-mod;}
ll dec(ll x,ll y){return (x-=y)<0?x+mod:x;}
namespace Lagrange{
    ll y[MAXN*2],pre[MAXN*2],suf[MAXN*2],fac[MAXN*2],ifac[MAXN*2];
    void init(int n=MAXN*2-1){
        fac[0]=1;
        for(ri i=1;i<=n;++i) fac[i]=fac[i-1]*i%mod;
        ifac[n]=ksm(fac[n],mod-2);
        for(ri i=n-1;~i;--i) ifac[i]=ifac[i+1]*(i+1)%mod;
    }
    ll solve(int n,int X){
        ll ans=0;
        pre[0]=1,suf[n+1]=1;
        for(ri i=1;i<=n;++i) pre[i]=pre[i-1]*dec(X,i-1)%mod;
        for(ri i=n;i;--i) suf[i]=suf[i+1]*dec(X,i-1)%mod;
        for(ri i=1;i<=n;++i){
            ll res=y[i]*pre[i-1]%mod*suf[i+1]%mod*ifac[i-1]%mod*ifac[n-i]%mod;
            if(n-i&1) res=mod-res;
            ans=add(ans,res);
        }
        return ans;
    }
}
int n,k;
ll w[MAXN],ans[2];
namespace Sub1{
    int f[MAXN*3][MAXN*3];
    void main(){
        f[1][1]=1;
        for(ri i=2;i<=3*k;++i) for(ri j=1;j<=i;++j) f[i][j]=add(1ll*f[i-1][j]*(i-1)%mod,f[i-1][j-1]);
        for(ri i=1;i<=k;++i){
            for(ri j=0;j<=2*i;++j) Lagrange::y[j+1]=f[i+j][j];
            w[i]=Lagrange::solve(2*i+1,n-i);
        }
    }
}
int main(){
    // freopen("rand.in","r",stdin);
    // freopen("1.out","w",stdout);
    n=read(),k=read();
    Lagrange::init(),Sub1::main();
    ans[0]=1;
    for(ri i=1;i<=k;++i){
        ans[i&1]=add(ans[i&1],w[i]);
        printf("%lld ",ans[i&1]);
    }
    fprintf(stderr,"%lf",1.0*clock()/CLOCKS_PER_SEC);
    return 0;
}
```

---

## 作者：7KByte (赞：1)

逆向思考，考虑有多少个排列经过 $k$ 次交换可以复原。

我们只用考虑一个排列所需的最小交换次数。

直接 $\rm DP$ ，定义 $f[i][j]$ 表示长度为 $i$ 的序列，最少交换次数为 $j$ 的排列数，可以得到 $f[i][j]=(i-1)f[i-1][j-1]+f[i-1][j]$ 。

如果不好理解，我们可以直接求第一类斯特林数，显然有$f[i][j]=S_1(i,i-j)$ 。

现在 $n$ 很大，无法直接递推。可以用特殊公式直接计算第一类斯特林数。

也可以分析一下，发现 $i$ 次操作最多只会改变 $2i$ 个位置，我们考虑计算出 $g[i][j]$ 表示长度为 $i$ 的排列，且$p_i\neq i$，最少需要$j$次复原的方案数。

不难得到等式

$$f[i][j]=\sum\limits_{k=0}^{i}\binom{i}{k}g[k][j]$$

我们对于每个$j$分开计算，发现这就是二项式反演，而二项式反演的本质就是容斥原理！

$$g[i][j]=\sum\limits_{k=0}^{i}(-1)^{i-k}\binom{i}{k}f[k][j]$$

这样我们就由最多 $i$ 个位置 $p_i\neq i$ 容斥出了**恰好** $i$ 个位置 $p_i \neq i$。

最后得到

$$Ans_m=\sum\limits_{i=1}^{\min\{n,2m\}}\binom{n}{i}\sum\limits_{2\mid (m-j)}g[i][j]$$

需要特别注意当 $j=0$ 时以上三个等式都不成立，但是 $f[i][0]=1$，直接特判即可。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 405
#define P 1000000007
using namespace std;
const int m = 400;
int n,k,inv[N],fac[N],c[N][N],f[N][N],g[N][N],op[N];
int Pow(int x,int y){int now=1;for(;y;y>>=1,x=1LL*x*x%P)if(y&1)now=1LL*now*x%P;return now;}
int main(){
	rep(i,0,m){c[i][0]=1;rep(j,1,i)c[i][j]=(c[i-1][j]+c[i-1][j-1])%P;}
	fac[0]=inv[0]=1;rep(i,1,m)fac[i]=1LL*i*fac[i-1]%P,inv[i]=Pow(fac[i],P-2);
	rep(i,0,m){f[i][0]=1;rep(j,1,i-1)f[i][j]=(1LL*(i-1)*f[i-1][j-1]+f[i-1][j])%P;}
	op[0]=1;rep(i,1,m)op[i]=op[i-1]*-1;
	rep(i,1,m){
		rep(j,1,i-1)rep(k,0,i)(g[i][j]+=1LL*op[i-k]*c[i][k]*f[k][j]%P)%=P;
	}
	scanf("%d%d",&n,&k);
	rep(i,1,k){
		int ans=0,cur=1;
		rep(j,1,min(n,i*2)){
			cur=1LL*cur*(n-j+1)%P;
			for(int w=i;w>0;w-=2)(ans+=1LL*cur*inv[j]%P*g[j][w]%P)%=P;
		}
		printf("%d ",(P+ans+((i&1)^1))%P);
	}
	return 0;
}
```

---

## 作者：st1vdy (赞：1)

# CF1516E Baby Ehab Plays with Permutations 题解

**链接**：[CF1516E](https://codeforces.com/contest/1516/problem/E)

**题意**：给定一个初始为 $1,2,3,\cdots,n$ 的排列，你可以进行 $j$ 次操作，每次操作可以交换排列中任意两个数，询问 $j$ 次操作后有几种不同的排列。求出 $j=1,2,3,\cdots,k$ 的所有结果。

**题解**：初始状态下，一个 $1$ 到 $n$ 的排列中的所有元素都可以看作是 $n$ 个大小为 $1$ 的圆排列（实际上就是 $n$ 个指向自己的环）。

然后考虑交换 $1$ 次对于这些圆排列的影响，比如 $[1,2,3,4]$ 交换 $1$ 次后可能得到 $[2,1,3,4]$ ，这个时候新的排列实际上由 $3$ 个圆排列（环）构成：$[2,1],[3],[4]$ ，其他情况同理。这意味着，交换 $1$ 次后，$n$ 个圆排列只剩下 $n-1$ 个。然后，我们考虑交换 $2$ 次，经过测试不难发现交换 $2$ 次后圆排列要么有 $n-2$ 个，要么有 $n$ 个，这提示我们每一次的交换，我们都可以让圆排列的数量减少 $1$ （最少为 $1$）或者撤销前一次的交换。

因此如果我们设大小为 $n$ 的排列构成 $k$ 个圆排列的方案数为 $s(n,k)$ ，那么本题的答案就是：$s(n,n-1),s(n,n)+s(n,n-2),s(n,n-1)+s(n,n-3),\cdots$ 。

这里的 $s(n,k)$ 实际上就是第一类斯特林数的定义，我们直接求值就可以解决了。。。等等 $n\leq10^9,k\leq 10^2$ ，但我只会 $O(n^2)$ 递推啊！不要慌，打开无敌的wiki，在 [Stirling Numbers of the First Kind](https://en.wikipedia.org/wiki/Stirling_numbers_of_the_first_kind) 中我们发现了这个式子：
$$
\begin{aligned}
s(n,n-i) = \sum^i_{j=0}(-1)^j\binom{n-1+j}{i+j} \binom{n+i}{i-j}S(i+j, j)
\end{aligned}
$$
上式中 $S(i+j,j)$ 表示第二类斯特林数，因此我们只需要预处理一下第二类斯特林数，就可以在 $O(k^3)$ 的复杂度下解决本题了。

```cpp
#include <bits/stdc++.h>
using namespace std;
constexpr int md = (int)1e9 + 7;
constexpr int N = 666;
int s[N], S[N][N], iv[N];
inline int add(int a, int b) {
    a += b;
    if (a >= md) a -= md;
    return a;
}

inline int sub(int a, int b) {
    a -= b;
    if (a < 0) a += md;
    return a;
}

inline int mul(int a, int b) {
    return (int)((long long)a * b % md);
}

inline int powmod(int a, long long b) {
    int res = 1;
    while (b > 0) {
        if (b & 1) res = mul(res, a);
        a = mul(a, a);
        b >>= 1;
    }
    return res;
}

inline int inv(int a) {
    a %= md;
    if (a < 0) a += md;
    int b = md, u = 0, v = 1;
    while (a) {
        int t = b / a;
        b -= t * a; swap(a, b);
        u -= t * v; swap(u, v);
    }
    assert(b == 1);
    if (u < 0) u += md;
    return u;
}

int binom(int n, int m) {
    if (n < m || n < 0 || m < 0) return 0;
    int res = 1;
    for (int i = n - m + 1; i <= n; i++) {
        res = mul(res, i);
    }
    for (int i = 1; i <= m; i++) {
        res = mul(res, iv[i]);
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, k;
    cin >> n >> k;
    S[0][0] = 1;
    for (int i = 1; i < N; i++) {
        iv[i] = inv(i);
        for (int j = 1; j < N; j++) {
            S[i][j] = add(S[i - 1][j - 1], mul(j, S[i - 1][j]));
        }
    }
    for (int i = 0; i <= 200; i++) {
        for (int j = 0; j <= i; j++) {
            if (j & 1) {
                s[i] = sub(s[i], mul(binom(n - 1 + j, i + j), mul(binom(n + i, i - j), S[i + j][j])));
            } else {
                s[i] = add(s[i], mul(binom(n - 1 + j, i + j), mul(binom(n + i, i - j), S[i + j][j])));
            }
        }
        if (i & 1) {
            s[i] = sub(md, s[i]) % md;
        }
    }
    int s1 = s[1], s0 = s[0];
    vector<int> res = { s1 };
    for (int i = 2; i <= min(n - 1, k); i++) {
        if (i & 1) {
            s1 = add(s1, s[i]);
            res.push_back(s1);
        } else {
            s0 = add(s0, s[i]);
            res.push_back(s0);
        }
    }
    while (res.size() < k) {
        res.push_back(res.back());
    }
    for (int i = 0; i < k; i++) {
        cout << res[i] << " \n"[i == k - 1];
    }
    return 0;
}
```



---

## 作者：Aleph1022 (赞：0)

我不知道那么多神秘的公式，怎么办呢？  
我只会拉格朗日反演，怎么办呢？

首先已经有很多人叙述过第 $k$ 项答案等于
$$
\sum\limits_{i=0}^k [i\equiv k \pmod 2] \left[\begin{matrix}n\\n-i\end{matrix}\right]
$$

瓶颈就是求第一类斯特林数的行后缀。  
根据组合意义容易知道
$$
\left[\begin{matrix}n\\m\end{matrix}\right] = \frac{n!}{m!} [z^n] \left(\ln\frac1{1-z}\right)^m
$$

那么考虑拉格朗日反演
$$
\begin{aligned}
[z^n] \left(\ln\frac1{1-z}\right)^{n-k} &= \frac{n-k}n [z^k] \left(\frac{z}{1-\mathrm e^{-z}}\right)^n \\
\left[\begin{matrix}n\\n-k\end{matrix}\right] &= \frac{(n-1)!}{(n-k-1)!} [z^k] \left(\frac{z}{1-\mathrm e^{-z}}\right)^n
\end{aligned}
$$

模数并不是 NTT 模数，但可以利用 $F=u^{-n}$ 满足 $F'u = -nFu'$ $O(n^2)$ 计算。

当然，第二类斯特林数的行后缀也可以这样计算。

代码：
```cpp
#include <cstdio>
using namespace std;
const int N = 200;
const int mod = 1e9 + 7;
inline int fpow(int a,int b)
{
	int ret = 1;
	for(;b;b >>= 1)
		(b & 1) && (ret = (long long)ret * a % mod),a = (long long)a * a % mod;
	return ret;
}
int n,k;
int fac[N + 5],ifac[N + 5],inv[N + 5];
int f[N + 5],g[N + 5];
int main()
{
	scanf("%d%d",&n,&k);
	fac[0] = 1;
	for(int i = 1;i <= k + 1;++i)
		fac[i] = (long long)fac[i - 1] * i % mod;
	ifac[k + 1] = fpow(fac[k + 1],mod - 2);
	for(int i = k + 1;i;--i)
		ifac[i - 1] = (long long)ifac[i] * i % mod;
	for(int i = 1;i <= k + 1;++i)
		inv[i] = (long long)ifac[i] * fac[i - 1] % mod;
	f[0] = g[0] = 1;
	for(int i = 1;i <= k;++i)
	{
		g[i] = i & 1 ? mod - ifac[i + 1] : ifac[i + 1];
		for(int j = 1;j <= i;++j)
			f[i] = (f[i] + (long long)j * g[j] % mod * f[i - j]) % mod;
		f[i] = (long long)f[i] * n % mod;
		for(int j = 1;j < i;++j)
			f[i] = (f[i] + (long long)j * f[j] % mod * g[i - j]) % mod;
		f[i] = (long long)(mod - f[i]) * inv[i] % mod;
	}
	for(int i = 0,prod = 1;i <= k;++i)
		f[i] = (long long)f[i] * prod % mod,
		prod = (long long)prod * (n - 1 - i) % mod;
	for(int i = 2;i <= k;++i)
		f[i] = (f[i] + f[i - 2]) % mod;
	for(int i = 1;i <= k;++i)
		printf("%d%c",f[i]," \n"[i == k]);
}
```

---

## 作者：syksykCCC (赞：0)

UPD: 原来贴错了代码 QAQ

---

逆向考虑问题。首先，考虑计算有多少个排列它**恰好**需要 $j$ 次 swap 来排序。

考虑一个排列它至少需要多少次 swap 才能排序呢？我们将这个排列进行循环分解，对于一个大小为 $k$ 的循环，显然我们可以通过依次交换相邻两项的方式，在 $k - 1$ 步还原这个循环。

所以，如果一个长度为 $n$ 的排列 $p$ 中有 $c$ 个循环，它就需要 $n - c$ 步来还原。

而，需要 $j$ 次 swap 的排列数量，也就是 $n - c = j \Rightarrow c = n - j$ 的那些排列。

那么，根据**第一类斯特林数**的定义，我们得出了一个重要的结论：需要 $j$ 步来还原的排列数量为 $\begin{bmatrix} n \\ n - j \end{bmatrix}$！

也就是说，题目的答案依次是 
$$
\begin{bmatrix} n \\ n - 1 \end{bmatrix}, \begin{bmatrix} n \\ n \end{bmatrix} + \begin{bmatrix} n \\ n - 2 \end{bmatrix}, \begin{bmatrix} n \\ n - 1 \end{bmatrix} + \begin{bmatrix} n \\ n - 3 \end{bmatrix} \cdots
$$
但正常根据递推式来求第一类斯特林数是 $O(n^2)$ 的，有没有更快的方法呢？

注意到虽然 $n$ 很大，但是 $k \le 200$，考虑利用这个性质。

其实当 $n - m$ 很小的时候，有一种比较快的求值公式：

> $$ (-1)^{n-m}\begin{bmatrix} n \\ m \end{bmatrix} = \sum_{k = 0}^{n - m} (-1)^k \binom{n - 1 + k}{m - 1} \binom{(n - m) + n}{(n - m) - k} \begin{Bmatrix} (n - m) + k \\ k \end{Bmatrix} $$
> <https://mathworld.wolfram.com/StirlingNumberoftheFirstKind.html> 中的 (21) 式，做了一些~~优美的~~变形。
>
> 其实，如果把等号左边的第一类斯特林数改为第二类斯特林数，等号右边的第二类斯特林数改为第一类斯特林数，等式仍然成立。

于是 $O(k^2)$ 递推第二类斯特林数，按照这个式子即可求解。

时间复杂度 $O(k^3)$。要线性预处理逆元。


```cpp
#include <bits/stdc++.h>
#define int long long 
using namespace std;
const int MOD = 1e9 + 7, K = 405;
int S[K][K], ans[K], inv[K];
int C(int n, int m)
{
	if(n < m || n < 0 || m < 0) return 0;
	if(m > n - m) m = n - m;
	int res = 1;
	for(int i = 1; i <= m; i++)
		res = res * (n - i + 1) % MOD * inv[i] % MOD;
	return res;
}
int s(int n, int m)
{
	if(m < 0) return 0;
	int res = 0;
	for(int k = 0; k <= n - m; k++)
	{
		int val = C(n - 1 + k, m - 1) * C(n - m + n, n - m - k) % MOD * S[n - m + k][k] % MOD;
		if(k & 1) res = (res - val + MOD) % MOD;
		else res = (res + val) % MOD;
	}
	return res;
}
int n, k;
signed main()
{
	cin >> n >> k;
	inv[1] = 1;
	for(int i = 2; i < K; i++)
	    inv[i] = (MOD - MOD / i) * inv[MOD % i] % MOD;
	S[0][0] = 1;
	for(int i = 1; i <= k * 2; i++)
		for(int j = 1; j <= i; j++)
			S[i][j] = (S[i - 1][j - 1] + j * S[i - 1][j] % MOD) % MOD;
	for(int i = 0; i <= min(n, k); i++) 
		if(i & 1) ans[i] = MOD - s(n, n - i);
		else ans[i] = s(n, n - i);
	for(int i = 1; i <= k; i++)
	{
		if(i - 2 >= 0) ans[i] = (ans[i] + ans[i - 2]) % MOD;
		printf("%lld ", ans[i]);
	}
	return 0;
}
```

---

