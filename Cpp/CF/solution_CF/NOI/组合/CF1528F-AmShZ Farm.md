# AmShZ Farm

## 题目描述

To AmShZ, all arrays are equal, but some arrays are more-equal than others. Specifically, the arrays consisting of $ n $ elements from $ 1 $ to $ n $ that can be turned into permutations of numbers from $ 1 $ to $ n $ by adding a non-negative integer to each element.

Mashtali who wants to appear in every problem statement thinks that an array $ b $ consisting of $ k $ elements is compatible with a more-equal array $ a $ consisting of $ n $ elements if for each $ 1 \le i \le k $ we have $ 1 \le b_i \le n $ and also $ a_{b_1} = a_{b_2} = \ldots = a_{b_k} $ .

Find the number of pairs of arrays $ a $ and $ b $ such that $ a $ is a more-equal array consisting of $ n $ elements and $ b $ is an array compatible with $ a $ consisting of $ k $ elements modulo $ 998244353 $ .

Note that the elements of $ b $ are not necessarily distinct, same holds for $ a $ .

## 说明/提示

There are eight possible pairs for the second example:

1. $ a = \{1, 1\}, b = \{1, 1\} $
2. $ a = \{1, 1\}, b = \{1, 2\} $
3. $ a = \{1, 1\}, b = \{2, 1\} $
4. $ a = \{1, 1\}, b = \{2, 2\} $
5. $ a = \{1, 2\}, b = \{1, 1\} $
6. $ a = \{1, 2\}, b = \{2, 2\} $
7. $ a = \{2, 1\}, b = \{1, 1\} $
8. $ a = \{2, 1\}, b = \{2, 2\} $

## 样例 #1

### 输入

```
1 1```

### 输出

```
1```

## 样例 #2

### 输入

```
2 2```

### 输出

```
8```

## 样例 #3

### 输入

```
5 4```

### 输出

```
50400```

## 样例 #4

### 输入

```
20 100```

### 输出

```
807645526```

## 样例 #5

### 输入

```
10000000 10000```

### 输出

```
883232350```

# 题解

## 作者：Mihari (赞：7)

# 壹、题目描述 &para;

[传送门to CF](https://codeforces.com/contest/1528/problem/F).

# 贰、题解 &para;

~~洛谷的博客打不了斯特林数的符号，差评.~~

推荐去[这里](https://www.cnblogs.com/Arextre/p/14824963.html)看，可以使用斯特林符号. 当然，公式炸了也可以去那里看.

>这一部分引用自知名博主 [C202044zxy](https://www.cnblogs.com/C202044zxy/p/14819023.html).
>
>发现 $a,b$ 两个数组的计数还算比较独立吧，我们先考虑 $a$ 数组怎么计数。
>
>设 $c_i$ 为数字 $i$ 的出现次数，则限制可以翻译为 $\sum_{j=i}^{n} c_j\leq n-i+1$ ，但是这样根本算不出来，因为这个限制牵扯到的东西太多了，**我们想要更加独立的限制**。
>
>不妨把题目换个说法：我们有 $n+1$ 个位置排成一排，有 $n$ 个人要坐进来，第 $i$ 个人一开始会到位置 $a_i(1\leq a_i\leq n)$，如果位置已满就往编号大的位置走，如果最后剩下的位置是 $n+1$ 的话就是一个合法的 $a$ 序列。
>
>这是一个经典的**序列转等概率环模型**（第二次见了），所以我们可以改写题目为：有 $n+1$ 个位置**排成一个环**，有 n 个人要坐进来，第 $i$ 个人一开始会到位置 $a_i(1\leq a_i\leq n+1)$，如果位置已满就**往右边走**，如果最后剩下的位置是 $n+1$ 的话就是一个合法的 $a$ 序列。
>
>因为是一个环并且初始到每个点的概率相同，**所以每个点被空出来的概率也是相同的**，不难发现方案数就是 $(n+1)^{n-1}$.
>
>我们再深入下去剖析这个模型，对于每种合法的 $a$ 序列都可以映射到 $n$ 种不同的不合法序列，因为如果我们让 $a_i$ 变成 $[(a_i+x-1)\bmod(n+1)]+1$ ，那么空出的位置 $t$ 会变成 $[(x+t-1)\bmod(n+1)]+1$ ，由此引出一个重要的性质：对于这 $n+1$ 个方案来说，**数字的分布情况是不会改变的，所以我们可以统计出所有排列的答案再除以 $n+1$**.

对于 $b$ 的计算，实际上我们枚举 $a$ 里面有多少个相同的数字，让 $b$ 来对应选择就行了。

实际上我们要算的就是
$$
\sum_{i=0}^n{n\choose i}\times n^{n-i}i^k
$$
由于 $b$ 并不要求不同，所以我们可以随便选择。考虑这个式子的化简：

$$
\begin{aligned}
&\sum_{i=0}^n{n\choose i}\times n^{n-i}i^k \\
=&\sum_{i=0}^n{n\choose i}\times n^{n-i}\sum_{j=0}^i{i\choose j}S(k,j)j! \\
=&\sum_{i=0}^n\sum_{j=0}^i{n\choose i}{i\choose j}S(k,j)j!n^{n-i} \\
=&\sum_{i=0}^n\sum_{j=0}^i{n\choose j}{n-j\choose i-j}S(k,j)j!n^{n-i} \\
=&\sum_{j=0}^n{n\choose j}S(k,j)j!\sum_{i=j}^n{n-j\choose i-j}n^{n-i} \\
=&\sum_{j=0}^n{n\choose j}S(k,j)j!\sum_{i=0}^{n-j}{n-j\choose i}n^{n-j-i} \\
=&\sum_{j=0}^n{n\choose j}S(k,j)j!(n+1)^{n-j}
\end{aligned}
$$

而由于
$$
S(k,j)=0\quad (j>k)
$$
所以我们可以调整一下 $j$ 的取值：
$$
\sum_{j=0}^k{n\choose j}S(k,j)j!(n+1)^{n-j}
$$
这样组合数就不需要算到 $n\le 10^9$ 了，但是还是只能使用递推。

若
$$
\begin{aligned}
f(i)&\overset\Delta={n\choose i}S(k,i)i! \\
g(i)&\overset\Delta=(n+1)^i
\end{aligned}
$$
那么，最后的答案就是
$$
(f\cdot g)(n)
$$
使用 $\tt fft$ 或者 $\tt ntt$ 进行计算。

至于如何求 $S(k,i)$，因为我们有
$$
S(k,i)={1\over i!}\sum_{j=0}^i(-1)^j{i\choose j}(i-j)^k=\sum_{j=0}^i{(-1)^j\over j!}\cdot {(i-j)^k\over (i-j)!}
$$


若
$$
\begin{aligned}
h(i)\overset\Delta=&{(-1)^i\over i!} \\
u(i)\overset\Delta=&{i^k\over i!}
\end{aligned}
$$
那么
$$
S=h\cdot u
$$
就可以得到斯特林数组了.

# 叁、参考代码 &para;

```cpp
#include<cstdio>
#include<vector>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
using namespace std;

// #define NDEBUG
#include<cassert>

#define rep(i, l, r) for(int i=(l), i##_end_=(r); i<=i##_end_; ++i)
#define drep(i, l, r) for(int i=(l), i##_end_=(r); i>=i##_end_; --i)
#define fi first
#define se second
#define mp(a, b) make_pair(a, b)
#define Endl putchar('\n')
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
template<class T>inline T fab(T x){ return x<0? -x: x; }
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

const int mod=998244353;
const int primitive_root=3;
const int inverse_primitive_root=332748118;
const int maxk=1e5;

inline int qkpow(int a, int n){
    int ret=1;
    for(; n>0; n>>=1, a=1ll*a*a%mod)
        if(n&1) ret=1ll*ret*a%mod;
    return ret;
}

namespace poly{
    int G[2][55], n, invn;
    vector<int>rev;
    inline void initial(){
        rep(j, 1, 50){
            G[0][j]=qkpow(primitive_root, (mod-1)/(1<<j));
            G[1][j]=qkpow(inverse_primitive_root, (mod-1)/(1<<j));
        }
    }
    inline void prepare(int N){
        for(n=1; n<N; n<<=1);
        invn=qkpow(n, mod-2);
        rev.resize(n);
        rep(i, 0, n-1) rev[i]=(rev[i>>1]>>1)|((i&1)? (n>>1): 0);
    }
    inline void ntt(vector<int>&f, int opt){
        f.resize(n);
        rep(i, 0, n-1) if(i<rev[i])
            swap(f[i], f[rev[i]]);
        for(int p=2, cnt=1; p<=n; p<<=1, ++cnt){
            int len=p>>1, w=G[opt][cnt];
            for(int k=0; k<n; k+=p){
                int buf=1, tmp;
                for(int i=k; i<k+len; ++i, buf=1ll*buf*w%mod){
                    tmp=1ll*f[i+len]*buf%mod;
                    f[i+len]=(f[i]+mod-tmp)%mod;
                    f[i]=(f[i]+tmp)%mod;
                }
            }
        }
        if(opt==1){
            rep(i, 0, n-1)
                f[i]=1ll*f[i]*invn%mod;
        }
    }
}

int fac[maxk+5], finv[maxk+5], C[maxk+5];

inline void precalc(){
    fac[0]=1;
    rep(i, 1, maxk) fac[i]=1ll*fac[i-1]*i%mod;
    finv[maxk]=qkpow(fac[maxk], mod-2);
    drep(i, maxk-1, 1) finv[i]=1ll*finv[i+1]*(i+1)%mod;
    finv[0]=1;
}

int n, k;

vector<int>f, u;

signed main(){
    poly::initial(); // pay attention!
    precalc();
    n=readin(1), k=readin(1);
    C[0]=1;
    rep(i, 1, k) C[i]=1ll*C[i-1]*(n-i+1)%mod*qkpow(i, mod-2)%mod;
    f.resize(k+1); u.resize(k+1);
    rep(i, 0, k){
        f[i]=(i&1)? (mod-finv[i]): finv[i];
        u[i]=1ll*qkpow(i, k)*finv[i]%mod;
    }
    poly::prepare(k*2+5);
    poly::ntt(f, 0); poly::ntt(u, 0);
    rep(i, 0, poly::n-1) f[i]=1ll*f[i]*u[i]%mod;
    poly::ntt(f, 1);
    int ans=0;
    rep(i, 0, k) {
        ans=(ans+1ll*C[i]*f[i]%mod*fac[i]%mod*qkpow(n+1, n-i)%mod)%mod;
    }
    writc(ans);
    return 0;
}
```



---

## 作者：Aleph1022 (赞：4)

根据[之前的结果](https://www.luogu.com.cn/blog/_post/340333)我们把问题转化成了对所有 $n+1$ 点有标号 $1$ 根树的所有点的儿子个数的 $k$ 次方求和。  
不妨直接大力计算这个，首先假装根任意，再除以 $n+1$ 就行了。  
发现权值作为和出现，则不妨直接用一个元 $t$ 的指数来计量权值，最后计算 $\left.\frac{\partial}{\partial t} F(z,t) \right|_{t=1}$。  
那么
$$
F(z,t) = z\sum\limits_{c\ge 0} \frac{t^{(c^k)} F^c(z,t)}{c!}
$$

根据拉格朗日反演
$$
\frac1{n+1} \left[\frac{z^{n+1}}{(n+1)!}\right] F(z,t) = \frac1{n+1} \left[\frac{z^n}{n!}\right]\left[\sum\limits_{c\ge 0} \frac{t^{(c^k)} z^c}{c!}\right]^{n+1}
$$

则
$$
\begin{aligned}
&\quad\; \left.\frac{\partial}{\partial t} \frac1{n+1} \left[\frac{z^n}{n!}\right]\left[\sum\limits_{c\ge 0} \frac{t^{(c^k)} z^c}{c!}\right]^{n+1} \right|_{t=1} \\
&= \left.\left[\frac{z^n}{n!}\right] \left[\sum\limits_{c\ge 0} \frac{t^{(c^k)} z^c}{c!}\right]^n \left[\sum\limits_{c\ge 0} \frac{c^k t^{c^k-1} z^c}{c!}\right]\right|_{t=1} \\
&= \left[\frac{z^n}{n!}\right] \mathrm e^{nz} \left[\sum\limits_{c\ge 0} \frac{c^k z^c}{c!}\right] \\
&= \sum\limits_{i=0}^n \binom ni i^k n^{n-i}
\end{aligned}
$$

看似接下来要用斯特林数展开，但实际上
$$
\begin{aligned}
\sum\limits_{i=0}^n \binom ni i^k n^{n-i}
&= \left[\frac{u^k}{k!}\right] \sum\limits_{i=0}^n \binom ni \mathrm e^{iu} n^{n-i} \\
&= \left[\frac{u^k}{k!}\right] (\mathrm e^u + n)^n
\end{aligned}
$$

换句话说，这就是 Binomial Sum 的一个变体。几乎大部分（大概？）对 Binomial Sum 的 $\Theta(k + \log n)$ 做法都很容易用来把这题做到 $\Theta(k + \log n)$。  
不过我写出的这个形式可以直接基于 EI 的载谭 Binomail Sum 科技处理。  
时间复杂度 $\Theta(k + \log n)$。

---

## 作者：tzc_wk (赞：3)

upd on 2021.6.24：修了个 typo

[Codeforces 题目传送门](https://codeforces.com/contest/1528/problem/F) & [洛谷题目传送门](https://www.luogu.com.cn/problem/CF1528F)

神仙题，只不过感觉有点强行二合一（？）。

首先考虑什么样的数组 $a$ 符合条件，我们考虑一个贪心的思想，我们从前到后遍历，对于每一个 $a_i$ 如果它已经在前面出现了就不断给它加 $1$ 直到它没有出现过为止。如果某个 $a_i$ 超过了 $n$ 则不符合条件，正确性显然。这样看起来还是有点抽象，我们不妨把它转化成这样的模型：有一架飞机有 $n$ 个位置，有 $n$ 个乘客要登飞机，每个乘客都预定了一个位置 $a_i$，每个乘客上飞机的时候，如果它的位置已经被占了，那么它会一直向前走直到到达一个空位为止并坐下，如果有乘客没位置坐则不符合题意。

这是[一个非常经典的问题](https://www.luogu.com.cn/problem/CF838D)，仿照那题的解法可以考虑这样的转化：添加一个 $n+1$ 号位并接链成环（？），将原先在链上走转化为在环上走，那么 $a$ 符合条件当且仅当 $n+1$ 位置最后没有被占。由于这 $n+1$ 个点组成一个环，故 $n+1$ 个点是对称的，它们被占的概率都是相同的，为 $\dfrac{1}{n+1}$，因此合法的 $a$ 的个数就是总序列数乘 $\dfrac{1}{n+1}$，即 $(n+1)^{n-1}$（注意：这里我们要做一个微调，即将 $a_i$ 的上界扩大到 $n+1$，否则就无法保证每个点都是对称的了，这个 $\dfrac{1}{n+1}$ 也就不成立了，故总序列个数实际上是 $(n+1)^n$，并且如果 $\exists a_i=n+1$ 那么肯定就不合法了，因此你改就改呗，也不影响我合法的序列 $a$ 的个数）。

到这里我们只分析完了序列 $a$ 的性质，即将序列 $a$ 的贡献全当作 $1$ 来算后得到的答案，可实际上对于某个 $a$ 它对答案的贡献并不是 $1$，而是 $\sum\limits_{i=1}^{n+1}c_i^k$，其中 $c_i$ 为 $i$ 的出现次数。这时候又到了动用咱们聪明才智的时候了。考虑继续分析 $a$ 的性质，还是从「$n+1$ 个点组成一个环」这个条件入手，显然我们将每个点都向右平移 $C$ 格后每个数的出现次数不变，即合法的 $b$ 的个数 $cntb(a)$ 不变，但最后留下来的位置也会跟着平移 $C$ 格。因此考虑对每个合法的序列 $a$ 做 $n$ 次映射，即 $a_i:=(a_i+C-1)\bmod(n+1)+1$，$C=1,2,3,\cdots,n$。由于 $a$ 是合法的序列，故映射后的序列肯定不是合法序列，显然这 $n+1$ 个序列的 $cntb$ 都是相同的，又所有合法序列映射后肯定恰好包含全部序列，因此我们可以求出所有序列的答案之和后除以 $n+1$ 即可算出答案。

接下来考虑怎么计算所有序列的答案之和，显然每个数的贡献都是相同的，计算出一个数的贡献后乘以 $n+1$ 即为总贡献，又最后要除掉一个 $n+1$，他俩刚好怼调了。计算一个数的贡献还算好办，枚举出现次数排列组合求一下即可，即
$$
\text{ans}=\sum\limits_{i=0}^n\dbinom{n}{i}i^kn^{n-i}
$$
接下来就是愉快地推式子环节了，至此我们进入了本题的第二部分：
$$
\begin{aligned}
\text{ans}&=\sum\limits_{i=0}^n\dbinom{n}{i}i^kn^{n-i}
\\&=\sum\limits_{i=0}^n\dbinom{n}{i}n^{n-i}\sum\limits_{j=0}^i\begin{Bmatrix}k\\j\end{Bmatrix}j!\dbinom{i}{j}&(\text{第二类斯特林数的性质})
\\&=\sum\limits_{i=0}^n\sum\limits_{j=0}^i\dbinom{n}{i}\dbinom{i}{j}n^{n-i}\begin{Bmatrix}k\\j\end{Bmatrix}j!
\\&=\sum\limits_{i=0}^n\sum\limits_{j=0}^i\dbinom{n}{j}\dbinom{n-j}{i-j}n^{n-i}\begin{Bmatrix}k\\j\end{Bmatrix}j!&(\text{吸收恒等式})
\\&=\sum\limits_{j=0}^n\dbinom{n}{j}\begin{Bmatrix}k\\j\end{Bmatrix}j!\sum\limits_{i=j}^n\dbinom{n-j}{i-j}n^{n-i}&(\text{交换求和号})
\\&=\sum\limits_{j=0}^n\dbinom{n}{j}\begin{Bmatrix}k\\j\end{Bmatrix}j!\sum\limits_{i=0}^{n-j}\dbinom{n-j}{i}n^{n-i-j}·1^i
\\&=\sum\limits_{j=0}^n\dbinom{n}{j}\begin{Bmatrix}k\\j\end{Bmatrix}j!(n+1)^{n-j}
\end{aligned}
$$
$\begin{Bmatrix}k\\j\end{Bmatrix}$ 可以通过[第二类斯特林数·行](https://www.cnblogs.com/ET2006/p/fftnttdxsschs2.html)求出，于是这道二合一的缝合怪题终于做完了（

```cpp
const int MAXP=1<<18;
const int MAXN=1e5;
const int pr=3;
const int MOD=998244353;
const int ipr=(MOD+1)/3;
int qpow(int x,int e){
	int ret=1;
	for(;e;e>>=1,x=1ll*x*x%MOD) if(e&1) ret=1ll*ret*x%MOD;
	return ret;
}
int n,k,rev[MAXP+5],fac[MAXN+5],ifac[MAXN+5];
void init_fac(int n){
	for(int i=(fac[0]=ifac[0]=ifac[1]=1)+1;i<=n;i++) ifac[i]=1ll*ifac[MOD%i]*(MOD-MOD/i)%MOD;
	for(int i=1;i<=n;i++) fac[i]=1ll*fac[i-1]*i%MOD,ifac[i]=1ll*ifac[i-1]*ifac[i]%MOD;
}
void NTT(vector<int> &a,int len,int type){
	int lg=31-__builtin_clz(len);
	for(int i=0;i<len;i++) rev[i]=(rev[i>>1]>>1)|((i&1)<<lg-1);
	for(int i=0;i<len;i++) if(i<rev[i]) swap(a[i],a[rev[i]]);
	for(int i=2;i<=len;i<<=1){
		int W=qpow((type<0)?ipr:pr,(MOD-1)/i);
		for(int j=0;j<len;j+=i){
			for(int k=0,w=1;k<(i>>1);k++,w=1ll*w*W%MOD){
				int X=a[j+k],Y=1ll*a[(i>>1)+j+k]*w%MOD;
				a[j+k]=(X+Y)%MOD;a[(i>>1)+j+k]=(X-Y+MOD)%MOD;
			}
		}
	}
	if(type==-1){
		int ivn=qpow(len,MOD-2);
		for(int i=0;i<len;i++) a[i]=1ll*a[i]*ivn%MOD;
	}
}
vector<int> conv(vector<int> a,vector<int> b){
	int LEN=1;while(LEN<a.size()+b.size()) LEN<<=1;
	a.resize(LEN,0);b.resize(LEN,0);NTT(a,LEN,1);NTT(b,LEN,1);
	for(int i=0;i<LEN;i++) a[i]=1ll*a[i]*b[i]%MOD;
	NTT(a,LEN,-1);return a;
}
int main(){
	scanf("%d%d",&n,&k);init_fac(k);
	vector<int> a(k+1),b(k+1);
	for(int i=0;i<=k;i++){
		a[i]=(i&1)?(MOD-ifac[i]):ifac[i];
		b[i]=1ll*qpow(i,k)*ifac[i]%MOD;
	} a=conv(a,b);int cur=1,ans=0;
	for(int j=1;j<=min(n,k);j++){
		cur=1ll*cur*(n-j+1)%MOD*qpow(j,MOD-2)%MOD;
		ans=(ans+1ll*a[j]*fac[j]%MOD*cur%MOD*qpow(n+1,n-j))%MOD;
	} printf("%d\n",ans);
	return 0;
}
```



---

## 作者：Aleph1022 (赞：2)

首先条件等价于对于 $i$ 有 $\sum_j [a_j \le i] \ge i$。  
记 $c_i = \sum_j [a_j = i]$，那么也即 $\sum_{j\le i} c_j \ge i$。  
对于方案数，只需要考虑枚举 $c_i$ 序列再给每个方案 $\frac{n!}{\prod c_i!}$ 的贡献。

考虑它的组合意义。我们考虑 $n+1$ 个点的有标号有根树，根为 $1$，定义其 DFS 序是按照儿子的编号从小到大进入的 DFS 序。  
我们按照这样的 DFS 序把每个对应结点的儿子个数记录下来，会得到一个长度为 $n+1$ 的序列。忽略最后的一个 $0$，就是长度为 $n$ 的序列。  
考虑记这个序列为 $c_i$，那么为了能构造出树，当且仅当 $\sum_{j\le i} c_j \ge i$ 时合法。这样，再考虑分配 $2,\dots,n+1$ 到每个点的儿子，由于规定了 DFS 序按儿子编号顺序，所以贡献就是 $\frac{n!}{\prod c_i!}$。

因此方案数就是 $n+1$ 个点的无根树个数，即 $(n+1)^{n-1}$。

接下来考虑统计贡献，为了好做先统计下降幂，再用斯特林数组合到 $k$ 次方。  
这就是对于一棵树造成 $\sum c_i^{\underline k}$ 的贡献。

我们用生成函数的复合方程描述这个问题，记 $W(z)$ 是有根树的生成函数，$F(z)$ 是有根树带上这个贡献的生成函数，考虑 $F(z)$ 的构造，需要注意到
$$
\sum\limits_{i\ge 0} i^{\underline k} \frac{z^i}{i!} = z^k \mathrm e^z,\sum\limits_{i\ge 0} \frac{z^i w}{(i+1)!} \cdot (i+1) = w\mathrm e^z
$$

因此
$$
\begin{aligned}
F(z) &= z\left(W^k(z) \mathrm e^{W(z)} + F(z) \mathrm e^{W(z)}\right) \\
F(z) &= \frac{W^{k+1}(z)}{1-W(z)}
\end{aligned}
$$

考虑其组合意义，即至少 $k+1$ 棵有根树的森林，且不同树的顺序有区别。  
将结点编号扩展到 $0,1,\dots,n+1$，考虑其 Prufer 序列，其中 $0$ 至少出现 $k$ 次，出现 $i$ 则附有 $(i+1)!$ 的贡献，枚举 $i$ 得
$$
\begin{aligned}
&\quad\; \sum\limits_{i=k}^n (i+1)! \binom ni (n+1)^{n-i} \\
&= \sum\limits_{i=k}^n (i+1)! \left(\binom{n+1}{i+1}-\binom n{i+1}\right) (n+1)^{n-i} \\
&= \left(\left[\frac{z^{n+1}}{(n+1)!}\right] \frac{z^{k+1}}{1-z} \mathrm e^{(n+1)z}\right) - \left((n+1)\left[\frac{z^n}{n!}\right] \frac{z^{k+1}}{1-z} \mathrm e^{(n+1)z}\right) \\
&= \left[\frac{z^{n+1}}{(n+1)!}\right] \frac{z^{k+1}}{1-z} \cdot(1-z)\cdot \mathrm e^{(n+1)z} \\
&= (n+1)^{\underline{k+1}} (n+1)^{n-k}
\end{aligned}
$$

由于规定了根，所以答案实际上是
$$
n^{\underline k} (n+1)^{n-k}
$$

---

## 作者：waauto (赞：2)

[view_in_blog](https://www.luogu.com.cn/blog/355192/solution-cf1528f)

[problem_link](https://www.luogu.com.cn/problem/CF1528F)

前面构造函数和生成函数的题解已经写的非常完美了，这是一个推柿子硬莽NTT的题解，但是从结果来看跑的算非常快的（最优解。

简化题意：

给定 $n,k$，求出：
$$
\sum_{i=0}^n\binom{n}{i}n^{n-i}i^k
$$

证明略(您若不是非常动，也可以看看其他题解的证明)。

前置知识：

斯特林数反演，二项式定理，快速数论变换。

前置题目：

快速求出 ${k\brace j},j=0,1,...k,k\le 10^5$ [link](https://www.luogu.com.cn/problem/P5395)。

斯特林反演得：

$$
\sum_{i=0}^n\binom{n}{i}n^{n-i}\sum_{j=1}^k{k\brace j}i^\frac{j}{}
$$

$$
=\sum_{i=0}^n\sum_{j=1}^k{k\brace j}i^\frac{j}{}\binom{n}{i}n^{n-i}
$$

因为：

$$
i^\frac{j}{}\binom{n}{i}=\binom{n-j}{i-j}n^\frac{j}{}
$$

带入原来式得：

$$
=\sum_{i=0}^n\sum_{j=1}^k{k\brace j}n^\frac{j}{}\binom{n-j}{i-j}n^{n-i}
$$

把无关项提前面得到：

$$
=\sum_{j=1}^k{k\brace j}n^\frac{j}{}\sum_{i=0}^n\binom{n-j}{i-j}n^{n-i}
$$

我们知道在二项式定理中：

$$
(x+y)^n=\sum_{k=0}^n\binom{n}{k}x^ky^{n-k}
$$

带入原式（有个隐藏的1:

$$
=\sum_{j=1}^k{k\brace j}n^\frac{j}{}(n+1)^{n-j}
$$

NTT 预处理第二代斯特林数然后递推即可。

代码的注释只是方便理解步骤，但式子推完了应该都能看懂，或者不懂的可以在评论区问。

甚至一点常数都没卡就达到了目前最优解，249ms。

![](https://cdn.luogu.com.cn/upload/image_hosting/8e2do8on.png)


```cpp
#include <bits/stdc++.h>
using ll = long long;
using namespace std;
const int N = 1e6 + 10;
const ll P = 998244353, gi = 3;
ll k, n ,fac[N], inv[N], f[N], g[N], S2[N];
ll bin[N];
ll qpow(ll a, ll b)
{
    ll res = 1;
    while (b)
    {
        if (b & 1)
            res = res * a % P;
        a = a * a % P;
        b >>= 1;
    }
    return res;
}
void NTT(ll *a, ll k, ll op)        // NTT部分。
{
    for (ll i = 0; i < k; i++)
        bin[i] = (bin[i >> 1] >> 1) | ((i & 1) * (k >> 1));
    for (ll i = 0; i < k; i++)
        if (i < bin[i])
            swap(a[i], a[bin[i]]);
    for (ll i = 1; i < k; i <<= 1)
    {
        ll wn = qpow(gi, op == 1 ? (P - 1) / (2 * i) : (P - 1) - (P - 1) / (2 * i)), w, t;
        for (ll j = 0; j < k; j += i << 1)
        {
            w = 1;
            for (ll k = 0; k < i; k++)
            {
                t = a[i + j + k] * w % P;
                w = w * wn % P;
                a[i + j + k] = (a[j + k] - t + P) % P;
                a[j + k] = (a[j + k] + t) % P;
            }
        }
    }
    if (op == -1)
    {
        ll Inv = qpow(k, P - 2);
        for (ll i = 0; i < k; i++)
            a[i] = a[i] * Inv % P;
    }
}
void get_s2()
{                          //预处理第二代斯特林数
    fac[0] = inv[0] = 1;
    for (int i = 1; i <= k; i++)
        fac[i] = fac[i - 1] * i % P;
    inv[k] = qpow(fac[k], P - 2);
    for (int i = k - 1; i >= 1; i--)
        inv[i] = inv[i + 1] * (i+1) % P;
    for (int i = 0; i <= k; i++)
        f[i] = (qpow(-1, i) + P) % P * inv[i] % P;
    for (int i = 0; i <= k; i++)
        g[i] = qpow(i, k) * inv[i] % P;
    ll len = 1;
    while (len < (k + 1) << 1)
        len <<= 1;
    NTT(f, len, 1);
    NTT(g, len, 1);
    for (int i = 0; i < len; i++)
        S2[i] = (f[i] * g[i]) % P;
    NTT(S2, len, -1);
}
int main()
{
    cin >> n >> k;
    get_s2();
    ll ans = 0;
    ll base = n * qpow(n + 1, n - 1) % P;   //把可以递推的部分先拿出来
    ll inv = qpow(n + 1, P - 2);
    for (ll i = 1; i <= min(n, k); i++)
    {                                        // min(n,k)因为多余那部分无意义
        ans = (ans + S2[i] * base) % P;
        base = base * inv % P * (n - i) % P;
    }
    cout << ans;
    while(1)cout<<"awa is cute"<<endl;    //放抄袭。
    return 0;
}

```

---

## 作者：critnos (赞：0)

牛逼题，看了题解才会做。

一个很明显的贪心是，逐个考虑 $a$ 中的每个数，如果当前的数和之前的数重复了就把当前的数加 $1$，直到不重复为止。这样如果最后不存在 $n+1$ 则说明可以把 $a$ 转化为排列。

现在进行一个等价的描述：把 $a$ 的值域拓展到 $[1,n+1]$，并且如果当前的数为 $n+1$，加 $1$ 改为变成 $1$（就是在一个环上做）。可以把 $a$ 转为排列的条件仍然是最后不存在 $n+1$。

这样对于一个可以被转化被排列的 $a$，将每个数在环上加 $k\in[1,n]$，最终的不存在的数就是 $k$。也就是说，一个可以被转化被排列的 $a$ 对应 $n$ 个不可以被转化被排列的 $a'$。

$b$ 的意义就是一个 $a$ 的贡献是其中每种数数量的 $k$ 次方的和。

若这 $n+1$ 个序列称为一组，显然每一组中每个 $a$ 贡献相同。这意味着，对所有的 $a$ 进行计算后除掉 $n+1$ 即为答案。

现在考虑每个元素的贡献（显然是相同的），答案为这个乘上 $n+1$，然后最后又要除掉 $n+1$，消掉了。

枚举该元素出现次数，那么答案为

$$\sum_{i=0}^n C(n,i)i^kn^{n-i}$$

$n\le k$ 平凡，考虑 $n>k$ 的情况。 

最后用异端推法放松一下。

$$[\dfrac {x^k} {k!}]\sum_{i=0}^n C(n,i)e^{ix}n^{n-i}$$

$$[\dfrac {x^k} {k!}](e^x+n)^n$$

$$[\dfrac {x^k} {k!}](e^x-1+n+1)^n$$

注意到 $e^x-1$ 常数项为 $0$，要求第 $k$ 项，所以展开的时候只用展开到第 $k$ 项。

$$[\dfrac {x^k} {k!}]\sum_{i=0}^kC(n,i)(e^x-1)^i(n+1)^{n-i}$$

$$[\dfrac {x^k} {k!}]\sum_{i=0}^kC(n,i)\sum_{j=0}^i C(i,j)e^{jx}(-1)^{i-j}(n+1)^{n-i}$$


$$\sum_{j=0}^kj^kC(n,j)\sum_{i=j}^kC(n-j,i-j)(-1)^{i-j}(n+1)^{n-i}$$

设 $t=-\dfrac 1 {n+1}$

$$\sum_{j=0}^kj^kC(n,j)(n+1)^{n-j}\sum_{i=0}^{k-j}C(n-j,i)t^i$$

设 $f_j=\sum_{i=0}^{k-j}C(n-j,i)t^i$，那么 $f_j-f_{j+1}=$

$$\sum_{i=0}^{k-j}C(n-j,i)t^i-\sum_{i=0}^{k-j-1}C(n-j-1,i)t^i$$

$$t\sum_{i=0}^{k-j-2}C(n-j-1,i)t^i+C(n-j,k-j)t^{k-j}$$

$$t(f_{j+1}-C(n-j-1,k-j-1)t^{k-j-1})+C(n-j,k-j)t^{k-j}$$

$$tf_{j+1}+C(n-j-1,k-j)t^{k-j}$$

所以 $f_j=(t+1)f_{j+1}+C(n-j-1,k-j)t^{k-j}$，可以 $O(k)$ 递推。

其他的简单处理一下，时间复杂度约为 $O(k)$。

---

## 作者：win114514 (赞：0)

### 思路

首先，原题意要你求：

$$\sum_{i=0}^n \binom{n}{i}i^kn^{n-i}$$

其实比较板子吧。

$$\sum_{i=0}^n \binom{n}{i}i^kn^{n-i}$$

$$\begin{aligned}
&=\sum_{i=0}^{n}\binom{n}{i}\sum_{j=1}^k {k\brace j}\binom{i}{j}j! n^{n-i}&(\text{普通幂拆开})\\
&=\sum_{j=1}^k{k\brace j}j!\sum_{i=0}^n\binom{n}{i}\binom{i}{j}n^{n-i}\\
&=\sum_{j=1}^k{k\brace j}j!\sum_{i=0}^n\frac{n!i!}{i!(n-i)!j!(i-j)!}n^{n-i}\\
&=\sum_{j=1}^k{k\brace j}n!\sum_{i=0}^n\frac{n^{n-i}}{(n-i)!(i-j)!}\\
&=\sum_{j=1}^k{k\brace j}\frac{n!}{(n-j)!}\sum_{i=0}^n\binom{n-j}{n-i}n^{n-i}\\
&=\sum_{j=1}^k{k\brace j}\frac{n!}{(n-j)!}(1+n)^{n-j}&(\text{二项式定理})\\
&=\sum_{j=1}^k\frac{1}{j!}\sum_{i=0}^j\binom{j}{i}(-1)^{j-i}i^k\frac{n!}{(n-j)!}(1+n)^{n-j}&(\text{斯特林数拆开})\\
&=\sum_{j=1}^k\binom{n}{j}\sum_{i=0}^j\binom{j}{i}(-1)^{j-i}i^k(1+n)^{n-j}\\
&=\sum_{i=1}^ki^k(-1)^i\sum_{j=i}^k\binom{n}{j}\binom{j}{i}(-1)^{j}(1+n)^{n-j}\\
&=(1+n)^n\sum_{i=1}^ki^k(-1)^i\sum_{j=i}^k\binom{n}{j}\binom{j}{i}(\frac{-1}{1+n})^{j}\\
&=(1+n)^n\sum_{i=1}^ki^k(-1)^i\sum_{j=i}^k\frac{n!j!}{(n-j)!j!i!(j-i)!}(\frac{-1}{1+n})^{j}\\
&=(1+n)^n\sum_{i=1}^ki^k(-1)^i\binom{n}{i}\sum_{j=i}^k\binom{n-i}{j-i}(\frac{-1}{1+n})^{j}\\
&=(1+n)^n\sum_{i=1}^ki^k\binom{n}{i}(\frac{1}{1+n})^{i}\sum_{j=0}^{k-i}\binom{n-i}{j}(\frac{-1}{1+n})^{j}\\
\end{aligned}$$

设 $f_i=\sum_{j=0}^{k-i}\binom{n-i}{j}(\frac{-1}{1+n})^{j}$。

那么：

$$\begin{aligned}
f_i-f_{i+1}&=\sum_{j=0}^{k-i}\binom{n-i}{j}(\frac{-1}{1+n})^{j}-\sum_{j=0}^{k-i-1}\binom{n-i-1}{j}(\frac{-1}{1+n})^{j}\\
&=\binom{n-i}{k-i}(\frac{-1}{1+n})^{k-i}+\sum_{j=1}^{k-i-1}\binom{n-i-1}{j-1}(\frac{-1}{1+n})^{j}\\
&=\binom{n-i}{k-i}(\frac{-1}{1+n})^{k-i}+\sum_{j=0}^{k-i-2}\binom{n-i-1}{j}(\frac{-1}{1+n})^{j+1}\\
&=\binom{n-i}{k-i}(\frac{-1}{1+n})^{k-i}+f_{i+1}\times \frac{-1}{1+n}-\binom{n-i-1}{k-i-1}(\frac{-1}{1+n})^{k-i}\\
&=\binom{n-i-1}{k-i}(\frac{-1}{1+n})^{k-i}+f_{i+1}\times \frac{-1}{1+n}\\
\end{aligned}$$

所以：

$$\begin{aligned}
f_i=\binom{n-i-1}{k-i}(\frac{-1}{1+n})^{k-i}+f_{i+1}(1+\frac{-1}{1+n})
\end{aligned}$$

递推即可。

发现上面所有的东西都可以线性处理。

时间复杂度：$O(k)$。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;

#define fro(i, x, y) for (int i = (x); i <= (y); i++)
#define pre(i, x, y) for (int i = (x); i >= (y); i--)

typedef long long i64;

const int N = 1e6 + 10;
const int mod = 998244353;

int n, k, ct;
int r, num, sum, ans;
int f[N], iv[N], fc[N], vs[N], pr[N], sm[N];

inline i64 power(i64 x, i64 y) {
  i64 res = 1;
  while (y) {
    if (y & 1) res = res * x % mod;
    x = x * x % mod, y /= 2;
  }
  return res;
}
inline i64 C1(int x, int y) {
  if (x < 0 || y < 0 || x - y < 0) return 0;
  while (r < x) ++r, num = 1ll * num * r % mod;
  return 1ll * num * iv[y] % mod;
}
inline i64 C2(int x, int y) {
  if (x < 0 || y < 0 || x - y < 0) return 0;
  return 1ll * (sum = 1ll * sum * (n - y + 1) % mod) * iv[y] % mod;
}

signed main() {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n >> k;
  i64 p1 = mod - power(1 + n, mod - 2);
  i64 p2 = mod - p1;
  fc[0] = 1;
  fro(i, 1, k) fc[i] = 1ll * fc[i - 1] * i % mod;
  iv[k] = power(fc[k], mod - 2);
  pre(i, k, 1) iv[i - 1] = 1ll * iv[i] * i % mod;
  r = n - k, sum = 1, num = n - k;
  if (n > k) {
    f[k] = 1;
    for (int i = k - 1, pw = p1; i >= 0; i--, pw = p1 * pw % mod) {
      f[i] = (f[i + 1] * (p1 + 1) + C1(n - i - 1, k - i) * pw) % mod;
    }
  } else {
    i64 p = mod + 1 - p2; f[n] = 1;
    for (int i = n - 1; i >= 1; i--) {
      f[i] = f[i + 1] * p % mod;
    }
  }
  sm[1] = 1;
  fro(i, 2, k) {
    if (vs[i] == 0) pr[++ct] = i, sm[i] = power(i, k);
    for (int j = 1; j <= ct && pr[j] * i <= k; j++) {
      vs[pr[j] * i] = 1;
      sm[pr[j] * i] = 1ll * sm[pr[j]] * sm[i] % mod;
      if (i % pr[j] == 0) break;
    }
  }
  for (int i = 1, pw = p2; i <= k; i++, pw = p2 * pw % mod) {
    i64 val = sm[i];
    val = val * C2(n, i) % mod;
    val = val * pw % mod;
    ans = (ans + f[i] * val) % mod;
  }
  ans = ans * power(1 + n, n) % mod;
  cout << (ans % mod + mod) % mod << "\n";
  return 0;
}
```

---

