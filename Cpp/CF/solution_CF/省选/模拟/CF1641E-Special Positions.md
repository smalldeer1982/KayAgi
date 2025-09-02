# Special Positions

## 题目描述

You are given an array $ a $ of length $ n $ . Also you are given $ m $ distinct positions $ p_1, p_2, \ldots, p_m $ ( $ 1 \leq p_i \leq n $ ).

A non-empty subset of these positions $ T $ is randomly selected with equal probability and the following value is calculated: $ $$$\sum_{i=1}^{n} (a_i \cdot \min_{j \in T} \left|i - j\right|). $ $  In other word, for each index of the array,  $ a\_i $  and the distance to the closest chosen position are multiplied, and then these values are summed up.</p><p>Find the expected value of this sum.</p><p>This value must be found modulo  $ 998\\,244\\,353 $ . More formally, let  $ M = 998\\,244\\,353 $ . It can be shown that the answer can be represented as an irreducible fraction  $ \\frac{p}{q} $ , where  $ p $  and  $ q $  are integers and  $ q \\neq 0 $  (mod  $ M $ ). Output the integer equal to  $ p \\cdot q^{-1} $  (mod  $ M $ ). In other words, output such integer  $ x $  that  $ 0 \\leq x &lt; M $  and  $ x \\cdot q = p $  (mod  $ M$$$).

## 说明/提示

In the first test:

- If only $ 1 $ is choosen, than the value equals to $ 1 \cdot 0 + 2 \cdot 1 + 3 \cdot 2 + 4 \cdot 3 = 20 $ .
- If only $ 4 $ is choosen, than the value equals to $ 1 \cdot 3 + 2 \cdot 2 + 3 \cdot 1 + 4 \cdot 0 = 10 $ .
- If both positions are chosen, than the value equals to $ 1 \cdot 0 + 2 \cdot 1 + 3 \cdot 1 + 4 \cdot 0 = 5 $ .

The answer to the problem is $ \frac{20 + 10 + 5}{3} = \frac{35}{3} = 665\,496\,247 $ (modulo $ 998\,244\,353 $ ).

## 样例 #1

### 输入

```
4 2
1 2 3 4
1 4```

### 输出

```
665496247```

## 样例 #2

### 输入

```
6 6
4 2 4 2 4 2
1 2 3 4 5 6```

### 输出

```
855638030```

# 题解

## 作者：周子衡 (赞：5)

考虑对每个 $i$，计算出 $\min_{j\in T}\{|i-j|\}$ 的期望值，记为 $f_i$。答案即为 $\sum a_if_i$。

计算 $f_i$ 可以通过计算对每个 $k\geq 1$，有多少个 $T$ 使得 
$\min_{j\in T}\{|i-j|\}\geq k$，再累和而求出。这等价于所有 $[i-(k-1),i+(k-1)]$ 中的关键点都强制不选的方案数。不妨设 $s_k$ 表示 $1\sim k$ 中有多少个关键点，那么 $[i-(k-1),i+(k-1)]$ 中关键点数为 $s_{i+(k-1)}-s_{i-k}$，区间外的关键点数为 $m-s_{i+(k-1)}+s_{i-k}$，总的非空子集数量即为 $2^{m-s_{i+(k-1)}+s_{i-k}}-1=2^m\times \dfrac{2^{s_{i+(k-1)}}}{2^{s_{i-k}}}-1$。也就是说，我们知道

$$
f_i=\sum_{k\geq 1}(2^m\times \dfrac{2^{s_{i+(k-1)}}}{2^{s_{i-k}}}-1)
$$

在此已经可以看出卷积的形式了。

注意这里下标的范围有超过 $[0,n]$ 的可能性，为符合题意，可以人为设定 $i < 0$ 时 $s_i=0$，$i > n$ 时 $s_i=m$（这相当于人为补充了若干个非关键位置）。观察到下标超过 $[-n,2n]$ 的范围的 $s$ 值是没有意义的，我们接下来只考虑 $i+(k-1),i-k\in[-n,2n]$ 的情形。为了让卷积形式更明显，我们写成下式：

$$
f_i=\sum_{-n\leq j<k\leq 2n,j+k=2i-1}(2^m\times 2^{s_k}\times \dfrac{1}{2^{s_j}}-1)
$$

后面的 $-1$ 单独处理。前面的一项可以利用卷积来解决，注意到这里要求 $j < k$，我们考虑采用分治 NTT，每次将区间一分为二，用一次 NTT 处理两个区间之间的贡献（用左区间的 $\dfrac{1}{2^{s_j}}$ 卷上右区间的 ${2^{s_k}}$，再递归下去。

总时间复杂度 $O(n\log^2n)$。似乎有点卡常，建议找一份快一点的多项式板子。

```cpp
#include<cstdio>
#include<vector>
#include<algorithm>

using namespace std;

typedef vector<long long> poly;

const long long MOD=998244353,G=3;
int add(int x,int y){return x+y>=MOD?x+y-MOD:x+y;}
int sub(int x,int y){return x>=y?x-y:x+MOD-y;}

long long fast_pow(long long b,long long p)
{
	long long ans=1;while(p){if(p&1)ans=ans*b%MOD;b=b*b%MOD;p>>=1;}
	return ans;
}
long long INV(long long x){return fast_pow(x,MOD-2);}
long long w[2000000],invw[2000000];

void init_w(int n)
{
	int N=1<<n;
	for(int d=2;d<=N;d<<=1)
	{
		int m=d>>1;w[m]=1;long long g=fast_pow(G,(MOD-1)/d);
		for(int i=1;i<m;i++)w[i+m]=w[i+m-1]*g%MOD;
	}
	for(int i=1;i<N;i++)invw[i]=INV(w[i]);
}


void NTT(poly &a,int n,int type)
{
	int N=1<<n;poly b(N);
	for(int i=1;i<N;i++)b[i]=(b[i>>1]>>1)|((i&1)*(N>>1));
	for(int i=1;i<N;i++)if(i<b[i])swap(a[i],a[b[i]]);
	
	for(int d=2;d<=N;d<<=1)
	{
		int m=d>>1;
		for(int i=0;i<N;i+=d)
		{
			for(int j=0;j<m;j++)
			{
				long long x=a[i+j],y=a[i+j+m]*(type==-1?invw[j+m]:w[j+m])%MOD;
				a[i+j]=add(x,y),a[i+j+m]=sub(x,y);
			}
		}
	}
	if(type==-1){long long x=INV(N);for(int i=0;i<N;i++)a[i]=a[i]*x%MOD;}
}
poly operator*(poly a,poly b)
{
	int N=a.size()+b.size(),n=0;while((1<<n)<N)n++;N=1<<n;
	while(a.size()<N)a.push_back(0);while(b.size()<N)b.push_back(0);
	NTT(a,n,1),NTT(b,n,1);
	poly c(N);for(int i=0;i<N;i++)c[i]=a[i]*b[i]%MOD;
	NTT(c,n,-1);return c;
}

int n,m;
int s[400000],p[400000];
long long a[400000],c[400000],pw2[400000],inv_pw2[400000];

void Solve(int l,int r)
{
	if(l==r)return;
	int mid=(l+r)>>1;Solve(l,mid),Solve(mid+1,r);
	poly X,Y;
	for(int i=l;i<=mid;i++)X.push_back(pw2[s[max(min(n,i),0)]]);
	for(int i=mid+1;i<=r;i++)Y.push_back(inv_pw2[s[max(min(n,i),0)]]);
	X=X*Y;for(int i=0;i<X.size();i++)if(i+l+(mid+1)>=0&&i+l+(mid+1)<=2*n)c[i+l+(mid+1)]=add(c[i+l+(mid+1)],X[i]);
}

int main()
{
	init_w(20);
	scanf("%d%d",&n,&m);for(int i=1;i<=n;i++)scanf("%d",&a[i]);for(int i=1;i<=m;i++)scanf("%d",&p[i]),s[p[i]]=1;
	for(int i=1;i<=n;i++)s[i]+=s[i-1];//for(int i=1;i<=n;i++)printf("%d ",s[i]);puts("");
	pw2[0]=1;for(int i=1;i<=n;i++)pw2[i]=add(pw2[i-1],pw2[i-1]);
	inv_pw2[n]=INV(pw2[n]);for(int i=n-1;i>=0;i--)inv_pw2[i]=add(inv_pw2[i+1],inv_pw2[i+1]);
	Solve(-n,2*n);
	//for(int i=0;i<=2*n;i++)printf("%lld ",c[i]*pw2[m]%MOD);puts("");
	long long ans=0;for(int i=1;i<=n;i++)ans=add(ans,sub(pw2[m]*c[2*i-1]%MOD,min(i+n,2*n-i+1))*a[i]%MOD);
	printf("%lld",ans*INV(sub(pw2[m],1))%MOD);
}
```

**后记**

一道非常常规以至于有点无聊的数学题。从官方题解的说明来看，这题似乎是临时凑上去的。希望以后 CF 题目质量能再进一步吧。

---

## 作者：legendgod (赞：1)

[更好的体验](https://legendgod.ml/)

[题目地址](https://codeforces.com/problemset/problem/1641/E)

题意：

给定长度为 $n$ 的数组 $a$，长度为 $m$ 的数组 $p$，其中 $1 \le p_i \le n$ ，而且 $\forall j, p_i \not = p_j$。

在 $p$ 中等概率选定一个非空集合，求 $\sum_{i = 1} ^ n a_i \times |i - p_j|$ 其中 $p_j$ 是选定集合中 $|i - p_j|$ 最小的 $p$。

$m \le n \le 10^5$。

---

- 我们考虑先将期望拆分成方案数除以总方案，很显然总方案就是 $2^m - 1$。

- 然后我们发现对于每一个数 $a_i$ 本质上是没有影响的，我们只需要计算后面部分总共贡献的次数就好了。

- 再者我们发现 $m$ 是很大的，所以肯定是不能枚举和子集有关的东西了，那么我们可以考虑将数组 $p$ 表示成 $\sum_{i = 1} ^ n [i \in P]$ 的形式。

根据以上的发现我们可以直观感受到这个肯定是和卷积有关的形式。

如果是一个卷积，我们肯定是需要将数组翻转，我们不妨考虑用 $i + j = 2\times pos $ 的形式表示最终的位置。

我们考虑左右两边的贡献，也就是将每个位置的贡献分开算，就是 $i, -i, j, -j$ 四种状况。

我们就拿 $i$ 举例子：

对于 $i$ 对于 $pos$ 的贡献，也就是左边向右的贡献，显然有区间 $(i, 2 \times pos - i]$ 是不能被计算到了。

> 考虑一边取到，为了防止之后算重。
> 
> 当然计算后面的时候就不需要取到了。

我们不妨考虑使用前缀积的形式来表示取到的区间。

然后对于计算贡献需要使用一个分治 $FFT$ 即可。

> 都是左边向右边的贡献。

我们再考虑一下是否还漏掉了什么，一个点在我们这样的计算情况下会被计算几次？

也就是作为 $i, j$ 的时候都分别被计算了一次，那么我们只需要在计算的时候乘一个 $\frac{1}{2}$ 即可。

如果要更详细一点可以参考代码。

```cpp
#include <bits/stdc++.h>
using namespace std;
namespace Legendgod {
	namespace Read {
//		#define Fread
		#ifdef Fread
		const int Siz = (1 << 21) + 5;
		char *iS, *iT, buf[Siz];
		#define gc() ( iS == iT ? (iT = (iS = buf) + fread(buf, 1, Siz, stdin), iS == iT ? EOF : *iS ++) : *iS ++ )
		#define getchar gc
		#endif
		template <typename T>
		void r1(T &x) {
		    x = 0;
			char c(getchar());
			int f(1);
			for(; !isdigit(c); c = getchar()) if(c == '-') f = -1;
			for(; isdigit(c); c = getchar()) x = (x << 1) + (x << 3) + (c ^ 48);
			x *= f;
		}
		template <typename T, typename...Args>
		void r1(T &x, Args&...arg) {
			r1(x), r1(arg...);
		}
		#undef getchar
	}

using namespace Read;

const int maxn = 2e6 + 5;
const int mod = 998244353;

int ksm(int x,int mi) {
    int res(1);
    while(mi) {
        if(mi & 1) res = 1ll * res * x % mod;
        mi >>= 1;
        x = 1ll * x * x % mod;
    }
    return res;
}

int Inv(int x) { return ksm(x, mod - 2); }

int n, m;

int lim, rev[maxn], len;

void getrev(int x) {
    lim = 1, len = 0;
    while(lim <= x) lim <<= 1, ++ len;
    for(int i = 0; i < lim; ++ i) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (len - 1));
}

const int G1 = 3, Gi = Inv(G1);

int w[2][21][maxn], inv[maxn];

void init(int up) {
    for(int i = 1; i <= up; ++ i) {
        w[0][i][0] = w[1][i][0] = 1;
        int w0 = ksm(G1, (mod - 1) / (1 << i));
        int w1 = ksm(Gi, (mod - 1) / (1 << i));
        for(int j = 1; j < (1 << i); ++ j) {
            w[0][i][j] = 1ll * w[0][i][j - 1] * w0 % mod;
            w[1][i][j] = 1ll * w[1][i][j - 1] * w1 % mod;
        }
    }
    for(int i = 1; i < (1 << up); ++ i) inv[i] = ksm(i, mod - 2);
}

void NTT(int *A,int opt = 1) {
    for(int i = 0; i < lim; ++ i) if(i < rev[i]) swap(A[i], A[rev[i]]);
    for(int mid = 1, c = 1; mid < lim; mid <<= 1, ++ c) {
        for(int j = 0, s = (mid << 1); j < lim; j += s) {
            int p = (opt == 1 ? 0 : 1);
            for(int k = 0; k < mid; ++ k) {
                int x = A[j + k], y = 1ll * A[j + k + mid] * w[p][c][k] % mod;
                A[j + k] = (x + y) % mod;
                A[j + k + mid] = (x - y + mod) % mod;
            }
        }
    }
    if(opt == -1) {
        for(int i = 0; i < lim; ++ i) A[i] = 1ll * A[i] * inv[lim] % mod;
    }
}

int Mul(const int *s1, const int *s2, int *Ans,int n,int m) {
    getrev(max(n, m) << 1);
    static int tmp1[maxn], tmp2[maxn];
    memset(tmp1, 0, 4 * lim), memcpy(tmp1, s1, n * 4);
    memset(tmp2, 0, 4 * lim), memcpy(tmp2, s2, m * 4);
    NTT(tmp1), NTT(tmp2);
    for(int i = 0; i < lim; ++ i) Ans[i] = 1ll * tmp1[i] * tmp2[i] % mod;
    NTT(Ans, -1);
    return n + m;
}

int F[maxn], G[maxn];

void Solve(int *x,int *y,int *Ans,int l,int r) {
    if(l == r) return ;
    int mid = (l + r) >> 1;
    Solve(x, y, Ans, l, mid), Solve(x, y, Ans, mid + 1, r);
    static int tmp1[maxn], tmp2[maxn], res[maxn];
    for(int i = l; i <= mid; ++ i) tmp1[i - l] = x[i];
    for(int i = mid + 1; i <= r; ++ i) tmp2[i - mid - 1] = y[i];
    int sz = Mul(tmp1, tmp2, res, mid - l + 1, r - mid);
    for(int i = 0; i < sz; ++ i) Ans[l + mid + 1 + i] = (Ans[l + mid + 1 + i] + res[i]) % mod;
}

void Calc(int *x,int *y,int *z) {
    memset(z, 0, 16 * n);
    Solve(x, y, z, 1, 2 * n);
}

int a[maxn], sp[maxn], sum[maxn];

const int Inv2 = ksm(2, mod - 2);

int A[maxn], B[maxn], C[maxn];
int ans[maxn];

signed main() {
	init(20);
	int i, j;
    r1(n, m);
    for(i = 1; i <= n; ++ i) r1(a[i]);
    for(i = 1; i <= m; ++ i) { int c; r1(c); sp[c] = 1; }
    for(i = 1; i <= 2 * n; ++ i) sum[i] = sum[i - 1] + sp[i];
    // left i
    for(i = 1; i <= n; ++ i) A[i] = 1ll * sp[i] * ksm(2, sum[i]) % mod * Inv2 % mod;
    for(i = 1; i <= 2 * n; ++ i) B[i] = ksm(Inv2, sum[i - 1]);
    Calc(A, B, C);
    for(i = 1; i <= n; ++ i) ans[i] = (ans[i] + 1ll * i * C[i * 2] % mod) % mod;
    // left -j
    for(i = 1; i <= n; ++ i) A[i] = 1ll * A[i] * i % mod;
    Calc(A, B, C);
    for(i = 1; i <= n; ++ i) ans[i] = (ans[i] - C[i * 2] + mod) % mod;
    // ---
    memset(A, 0, sizeof(A)), memset(B, 0, sizeof(B));
    // right -i
    for(i = 1; i <= n; ++ i) A[i + n] = 1ll * Inv2 * sp[i] % mod * ksm(Inv2, sum[i - 1]) % mod;
    for(i = 1; i <= n; ++ i) B[i] = 1; // 2 ^ 0
    for(i = n + 1; i <= 2 * n; ++ i) B[i] = ksm(2, sum[i - n - 1]);
    Calc(B, A, C);
    for(i = 1; i <= n; ++ i) ans[i] = (ans[i] - 1ll * i * C[2 * i + 2 * n] % mod + mod) % mod;
//    for(i = 1; i <= n; ++ i) printf("%d%c", ans[i], " \n"[i == n]);
    // right j
    for(i = 1; i <= n; ++ i) A[i + n] = 1ll * A[i + n] * i % mod;
    Calc(B, A, C);
    for(i = 1; i <= n; ++ i) ans[i] = (ans[i] + C[2 * i + 2 * n]) % mod;
    // ---
    int sum(0);
    for(i = 1; i <= n; ++ i) sum = (sum + 1ll * ans[i] * a[i] % mod) % mod;
    sum = 1ll * sum * ksm(2, m) % mod * ksm(ksm(2, m) - 1, mod - 2) % mod;
    printf("%d\n", sum);
	return 0;
}

}


signed main() { return Legendgod::main(), 0; }

```


---

## 作者：JackF (赞：0)

#### 题意

给定一个长度为 $n$ 的序列 $a$ 和一个长度为 $m$ 的下标序列 $b$，满足 $\forall i\in[1,m],1\le b_i\le n$ 以及 $\forall i\neq j,b_i\neq b_j$。

等概率随机一个 $b$ 的非空子序列 $c$，求 $\sum\limits_{i=1}^{n}a_i\times\min\limits_{p\in c}|i-p|$ 的期望值。答案对 $998244353$ 取模。

$1\le m\le n\le 10^5,0\le a_i\le 998244352,1\le b_i\le n$。

#### 题解

以下过程中的概率计算是依照等概率随机一个 $b$ 的子序列来做的，最后答案要乘 $\frac{2^{m}}{2^{m}-1}$。

定义 $p_{\min}$ 为对于一个位置 $i$，取得 $\min\limits_{p\in c}|i-p|$ 的 $p$。

假设已经选好了 $b$ 的子序列 $c$，那么序列 $a$ 就被划分成了若干段，开头段的 $p_{\min}$ 都为 $c_1$，结尾段的 $p_{\min}$ 都为 $c_{|c|}$，中间段 $[c_i,c_{i+1}]$ 的左半部分 $[c_i,\lfloor\frac{c_i+c_{i+1}}{2}\rfloor]$ 的 $p_{\min}$ 为 $c_i$，右半部分 $[\lfloor\frac{c_{i}+c_{i+1}}{2}\rfloor+1,c_{i+1}]$ 的 $p_{\min}$ 为 $c_{i+1}$。

给 $b$ 排序，贡献可以拆开，考虑分别计算开头段，结尾段和中间段的贡献。其中开头和结尾是简单的，例如枚举 $c_{1}=b_i$，概率为 $\frac{1}{2^i}$，权值为 $\sum\limits_{k=1}^{i}a_k(i-k)$，容易计算。这部分可以 $O(n)$ 解决。

将中间段的总贡献拆成若干个相邻对 $(c_i=b_x,c_{i+1}=b_y)$ 的贡献。枚举 $x,y$，记 $l=b_x,r=b_y$，概率为 $\frac{1}{2^{y-x+1}}$，贡献为 $\sum\limits_{i=l}^{\lfloor\frac{l+r}{2}\rfloor}a_i(i-l)+\sum\limits_{i=\lfloor\frac{l+r}{2}\rfloor+1}^{r}a_i(r-i)$。若预处理 $s_k=\sum_{i\le k} a_i$ 和 $t_{k}=\sum_{i\le k} i\cdot a_i$，可以变换为 $A_{l+r}+B_{l}+C_{r}$。注意到 $B_l$ 和 $C_{r}$ 仅和其中一个变量有关，$(l,*)$ 和 $(*,r)$ 的贡献和可以 $O(n)$ 计算。

最后要解决的就是下式：
$$
\sum_{i=1}^{m-1}\sum_{j=i+1}^{m}\frac{1}{2^{j-i+1}}A_{b_{i}+b_{j}}=\sum_{i=1}^{m-1}\sum_{j=i+1}^{m}\frac{2^{i-1}}{2^j}A_{b_i+b_j}
$$
令 $[x^{b_i}]P(x)=2^{i-1},[x^{b_{j}}]Q(x)=2^{-j}$，那么就变为 $\sum_{1\le i<j\le n}[x^i]P(x)[x^j]Q(x)\times A_{i+j}$ 的形式。很像卷积，但是有 $i<j$ 的限制，也即要对所有在第一个多项式中的 $x$ 的幂次小于在第二个多项式中的 $x$ 的幂次的单项式对算贡献。

考虑 cdq 分治，递归到 $[l,r]$ 的时候直接将 $P[l,mid]$ 和 $Q[mid+1,r]$ 做卷积累加进最终的多项式即可，复杂度 $T(n)=2T(\frac{n}{2})+O(n\log n)$，根据 Master Theorem 分析得到时间复杂度是 $O(n\log^2 n)$。

#### 代码

```c++
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define per(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
typedef long long ll;
typedef vector<int>Poly;
constexpr int N=262144,mod=998244353,inv2=mod+1>>1;
int n,m,a[N],b[N],s[N],t[N],A[N],B[N],C[N],pw[N],ipw[N],s2[N],u[N],v[N],w[N],r[N];
inline int qpow(int a,int b){
	int ans=1;
	for(;b;b>>=1,a=(ll)a*a%mod)if(b&1)ans=(ll)ans*a%mod;
	return ans;
}
inline void NTT(Poly&A,int len,int type){
	rep(i,0,len-1)if(i<r[i])swap(A[i],A[r[i]]);
	for(int mid=1;mid<len;mid<<=1){
		int Wn=qpow(type>0?3:(mod+1)/3,(mod-1)/(mid<<1));
		for(int j=0;j<len;j+=(mid<<1))
			for(int k=0,w=1;k<mid;++k,w=(ll)w*Wn%mod){
				int x=A[j+k],y=(ll)w*A[j+k+mid]%mod;
				A[j+k]=(x+y)%mod,A[j+k+mid]=(x-y+mod)%mod;
			}
	}
	if(type>0)return;
	int iv=qpow(len,mod-2);
	rep(i,0,len-1)A[i]=(ll)A[i]*iv%mod;
}
inline void init_rev(int len){
	rep(i,0,len-1)r[i]=r[i>>1]>>1|((i&1)*(len>>1));
}
inline Poly operator*(Poly a,Poly b){
	int n=a.size(),m=b.size(),l=1;
	while(l<n+m-1)l<<=1;
	init_rev(l);
	a.resize(l),NTT(a,l,1);
	b.resize(l),NTT(b,l,1);
	rep(i,0,l-1)a[i]=(ll)a[i]*b[i]%mod;
	NTT(a,l,-1);
	return a.resize(n+m-1),a;
}
inline void solve(int l,int r){
	if(l>=r)return;
	int mid=l+r>>1;
	solve(l,mid),solve(mid+1,r);
	Poly f,g;
	rep(i,l,mid)f.emplace_back(u[i]);
	rep(i,mid+1,r)g.emplace_back(v[i]);
	f=f*g;
	int n=f.size()-1;
	rep(i,0,n)(w[i+l+mid+1]+=f[i])%=mod;
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n>>m;
	rep(i,1,n)cin>>a[i];
	rep(i,1,m)cin>>b[i];
	pw[0]=1,ipw[0]=1;
	rep(i,1,2e5)pw[i]=pw[i-1]*2LL%mod,ipw[i]=(ll)ipw[i-1]*inv2%mod;
	rep(i,1,n){
		s[i]=(s[i-1]+(ll)a[i]*i%mod)%mod;
		t[i]=(t[i-1]+a[i])%mod;
	}
	rep(i,1,n+n)A[i]=(s[i/2]*2-(ll)i*t[i/2]%mod+mod)%mod;
	rep(i,1,n){
		B[i]=((ll)i*t[i-1]%mod-s[i-1]+mod)%mod;
		C[i]=((ll)i*t[i]%mod-s[i]+mod)%mod;
	}
	rep(i,2,m)s2[i]=(s2[i-1]+ipw[i])%mod;
	int ans=0;
	rep(i,1,m-1)(ans+=(ll)B[b[i]]*s2[m-i+1]%mod)%=mod;
	rep(i,2,m)(ans+=(ll)C[b[i]]*s2[i]%mod)%=mod;
	rep(i,1,m)u[b[i]]=pw[i-1],v[b[i]]=ipw[i];
	solve(1,n);
	rep(i,1,n+n)(ans+=(ll)A[i]*w[i]%mod)%=mod;
	rep(i,1,m)(ans+=(ll)ipw[i]*((ll)t[b[i]]*b[i]%mod-s[b[i]]+mod)%mod)%=mod;
	rep(i,1,m)(ans+=(ll)ipw[m-i+1]*((ll)(s[n]-s[b[i]-1]+mod)%mod-(ll)b[i]*(t[n]-t[b[i]-1]+mod)%mod+mod)%mod)%=mod;
	cout<<(ll)ans*pw[m]%mod*qpow(pw[m]-1,mod-2)%mod<<'\n';
	return 0;
}
```



---

