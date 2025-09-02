# [ABC270G] Sequence in mod P

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc270/tasks/abc270_g

次の漸化式で定められる数列 $ X=(X_0,X_1,\ldots) $ があります。

$ X_i\ =\ \left\{
\begin{array}{ll}
S\  \ (i\ =\ 0)\\
(A\ X_{i-1}+B)\ \bmod\ P\  \ (i\ \geq\ 1)
\end{array}
\right. $

$ X_i=G $ となる $ i $ が存在するか判定し、存在するならばそのような最小の $ i $ を求めてください。  
ここで、$ x\ \bmod\ y $ は、$ x $ を $ y $ で割ったあまり(最小非負剰余)を表すものとします。

$ 1 $ ファイルにつき $ T $ 個のテストケースが与えられます。

## 说明/提示

### 制約

- $ 1\ \leq\ T\ \leq\ 100 $
- $ 2\ \leq\ P\ \leq\ 10^9 $
- $ P $ は素数
- $ 0\leq\ A,B,S,G\ <\ P $
- 入力に含まれる値は全て整数である

### Sample Explanation 1

$ 1 $ 番目のケースについて、$ X=(1,3,2,0,\ldots) $ であることから、$ X_i=0 $ となる最小の $ i $ は $ 3 $ です。 $ 2 $ 番目のケースについて、$ X=(3,3,3,3,\ldots) $ であることから、$ X_i=0 $ となる $ i $ は存在しません。

## 样例 #1

### 输入

```
3
5 2 1 1 0
5 2 2 3 0
11 1 1 0 10```

### 输出

```
3
-1
10```

# 题解

## 作者：August_Light (赞：3)

# [ABC270G] Sequence in mod P 题解

矩阵 BSGS。

[题目传送门](https://www.luogu.com.cn/problem/AT_abc270_g)

## 题意简述

定义数列：

$$x_i = \begin{cases} s & i = 0 \\ (a \times x_{i-1} + b) \bmod p & i \geq 1 \end{cases}$$

求最小的 $i$ 满足 $x_i = g$，没有输出 `-1`。

$100$ 组数据。$p$ 是质数，$2 \le p \le 10^9$。

## 前置知识

普通 BSGS：[P3846 [TJOI2007] 可爱的质数/【模板】BSGS](https://www.luogu.com.cn/problem/P3846)

## 解法

定义两个向量 / 方阵在模 $p$ 意义下同余，当且仅当对应位置上的数在模 $p$ 意义下同余。

$$\begin{bmatrix} x_{i+1} \\ 1 \end{bmatrix} \equiv \begin{bmatrix} a & b \\ 0 & 1 \end{bmatrix} \begin{bmatrix} x_i \\ 1 \end{bmatrix} \pmod p$$

即问题转化为，解方程：

$$\begin{bmatrix} a & b \\ 0 & 1 \end{bmatrix}^{ans} \begin{bmatrix} s \\ 1 \end{bmatrix} \equiv \begin{bmatrix} g \\ 1 \end{bmatrix} \pmod p$$

不难联想到 BSGS 算法。

仿照普通 BSGS，设计一个矩阵 BSGS：

不难证明答案不会超过 $p$。

设 $M = \begin{bmatrix} a & b \\ 0 & 1 \end{bmatrix}$，设 $t$ 为块长，令答案为 $A \times t - B$：

$$M^{A \times t - B} \begin{bmatrix} s \\ 1 \end{bmatrix} \equiv \begin{bmatrix} g \\ 1 \end{bmatrix} \pmod p$$

$$M^{A \times t} \begin{bmatrix} s \\ 1 \end{bmatrix} \equiv M^B \begin{bmatrix} g \\ 1 \end{bmatrix} \pmod p$$

用一个哈希表存下 $1 \le B \le t$ 时等式右边的值。枚举 $1 \le A \le \dfrac p t$，看等式左边有没有配上哈希表内的值。

$t$ 取 $\Theta(\sqrt p)$ 时时间复杂度达到最优，为 $O(\sqrt p)$。

```cpp
// 此代码中用了 map。时间复杂度会比哈希表多一个 log。
// a 为矩阵，v1 为等式左侧的向量，v2 为等式右侧的向量。
ll BSGS(Matrix a, Matrix v1, Matrix v2) {
    map<Matrix, ll> mp;
    ll t = sqrt(MOD) + 1;
    Matrix cur; cur.reset();
    for (ll i = 1; i <= t; i++) {
        cur = a * cur;
        mp[cur * v2] = i;
    }
    Matrix cur2 = cur;
    for (ll i = 1; i <= t; i++) {
        auto it = mp.find(cur2 * v1);
        if (it != mp.end())
            return i * t - it->second;
        cur2 = cur * cur2;
    }
    return -1;
}
```

那么这题就做完了。

吗？

重新审视我们的算法。

$$M^{A \times t - B} \begin{bmatrix} s \\ 1 \end{bmatrix} \equiv \begin{bmatrix} g \\ 1 \end{bmatrix} \pmod p$$

$$M^{A \times t} \begin{bmatrix} s \\ 1 \end{bmatrix} \equiv M^B \begin{bmatrix} g \\ 1 \end{bmatrix} \pmod p$$

不难发现，一式能推出二式，但二式推不出一式。

要二式能够推出一式，当且仅当 $M$ 有逆元，即 $\begin{vmatrix} a & b \\ 0 & 1 \end{vmatrix} \not \equiv 0 \pmod p$，即 $a \ne 0$。

所以需要特判 $a=0$ 的情况，具体特判不赘述。

## 代码

时间复杂度 $O(\sqrt p \log p)$。用哈希表可以做到 $O(\sqrt p)$，但是我懒。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll MOD;

const int L = 2;
struct Matrix {
    ll M[L+1][L+1];
    ll *operator[](int p) {
        return M[p];
    }
    void clear() {
        memset(M, 0, sizeof M);
    }
    void reset() {
        clear();
        for (int i = 1; i <= L; i++)
            M[i][i] = 1;
    }
    Matrix() {
        clear();
    }
    Matrix friend operator*(Matrix A, Matrix B) {
        Matrix C; C.clear();
        for (int i = 1; i <= L; i++)
            for (int k = 1; k <= L; k++)
                for (int j = 1; j <= L; j++)
                    (C[i][j] += A[i][k] * B[k][j] % MOD) %= MOD;
        return C;
    }
    bool friend operator<(Matrix A, Matrix B) {
        for (int i = 1; i <= L; i++)
            for (int j = 1; j <= L; j++)
                if (A[i][j] < B[i][j])
                    return 1;
                else if (A[i][j] > B[i][j])
                    return 0;
        return 0;
    }
};

ll BSGS(Matrix a, Matrix v1, Matrix v2) {
    map<Matrix, ll> mp;
    ll t = sqrt(MOD) + 1;
    Matrix cur; cur.reset();
    for (ll i = 1; i <= t; i++) {
        cur = a * cur;
        mp[cur * v2] = i;
    }
    Matrix cur2 = cur;
    for (ll i = 1; i <= t; i++) {
        auto it = mp.find(cur2 * v1);
        if (it != mp.end())
            return i * t - it->second;
        cur2 = cur * cur2;
    }
    return -1;
}

int main() { ios::sync_with_stdio(0); cin.tie(0);
    int T; cin >> T; while (T--) {
        ll a, b, s, g; cin >> MOD >> a >> b >> s >> g;
        Matrix A;
        A[1][1] = a; A[1][2] = b;
        A[2][1] = 0; A[2][2] = 1;
        Matrix V1;
        V1[1][1] = s;
        V1[2][1] = 1;
        Matrix V2;
        V2[1][1] = g;
        V2[2][1] = 1;

        ll ans;
        if (a == 0) {
            if (s == g)
                ans = 0;
            else if (b == g)
                ans = 1;
            else
                ans = -1;
        } else
            ans = BSGS(A, V1, V2);
        cout << ans << '\n';
    }
    return 0;
}
```


---

## 作者：yukimianyan (赞：3)

~~有个地方写错了，改一下~~
## problem
Soso 有一个无穷序列 $\{X_i\}$ 定义如下：

$$X_i=\begin{cases}
S,&(i=0)\\
(A\cdot X_{i-1}+B)\bmod P,&(i\geq 1)
\end{cases}$$

其中 $0\leq S,A,B<P\leq 10^9$ 均为常数，$P\in\textrm{Prime}$。现在求最小的 $i$ 使得 $X_i=G$。多测 $100$ 组数据。

## solution
### general
思路：将式子化为只与 $k$ 有关的东西。
$$\begin{aligned}
X_k&=SA^k+BA^{k-1}+BA^{k-2}+\cdots+BA^0\\
&=SA^k+B(A^{k-1}+A^{k-2}+\cdots+A^0)\\
&=SA^k+B\frac{A^k-1}{A-1}\\
&=SA^k+\frac{B}{A-1}A^k-\frac{B}{A-1}\\
&=(S+\frac{B}{A-1})A^k-\frac{B}{A-1}=G.
\end{aligned}$$

令 $C=\frac{B}{A-1}$，欲求 $A^k\equiv \frac{G+C}{S+C}\pmod P$，因为 $P$ 为质数，故使用 [BSGS](https://www.luogu.com.cn/problem/solution/P3846) 求得最小的 $k$。

### special judge
- $S=G\Rightarrow0$。
- $A=0$：check if $B=G$ or $S=G$。
- $A=1$：$X_n=S+Bn\Rightarrow n=\frac{G-S}{B}$。
- $S=B=0$：$X_n=0$。

## code
```cpp
#include <map>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
LL qpow(LL a,LL b,int p){LL r=1;for(;b;b>>=1,a=a*a%p) if(b&1) r=r*a%p;return r;}
LL inv(LL a,int p){return qpow(a,p-2,p);}
LL bsgs(LL x,LL y,int p){
//	fprintf(stderr,"bsgs(%lld,%lld,%d)\n",x,y,p);
	if(x%=p,y%=p,y==1||x==y) return y!=1;
	//x^(am-b)=(x^m)^a/x^b=y =>(x^m)^a=y*x^b
	int m=ceil(sqrt(p));
	map<int,int> mp;
	for(int i=m;i>=1;i--) mp[qpow(x,i*m,p)]=i*m;
	int res=1e9;
	for(int i=0;i<=m;i++){
		if(mp.count(y*qpow(x,i,p)%p)) res=min(res,mp[y*qpow(x,i,p)%p]-i);
	}
	return res==1e9?-1:res;
}
LL p,a,b,s,g;
int mian(){
	if(s==g) puts("0");
	else if(a==0) printf("%lld\n",b==g?1ll:-1ll);
	else if(a==1){
		if(!b) puts("-1");
		else printf("%lld\n",(g-s+p)%p*inv(b,p)%p);
	}else{
		LL cmb=b*inv(a-1,p)%p;
		printf("%lld\n",bsgs(a,(g+cmb)%p*inv(s+cmb,p)%p,p));
	}
	return 0;
}
int main(){
	for(scanf("%*d");~scanf("%lld%lld%lld%lld%lld",&p,&a,&b,&s,&g);mian());
	return 0;
}
```


---

## 作者：一只小咕咕 (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc270_g)

### 思路
题目给出了一个数列
$$
x_{i+1}\equiv {a\times x_i+b}\pmod{p}
$$
并想要求最小的 $x_i=G$，那我们可以考虑求出这个数列的通项公式。

具体的，观察到原式可以转化成一个等比数列的形式，所以我们可以先设一个常数 $k$，使得
$$
x_{i+1}+k=a(x_i+k)
$$
替换进原先的式子
$$
a(x_i+k)-k ax_i+b
$$
$$
ak-k=b
$$
$$
k=\frac{b}{a-1}
$$
于是就有
$$
x_{i+1}+\frac{b}{a-1}=a\left( x_i+\frac{b}{a-1} \right)
$$
这样就把原式化成等比数列的形式了
$$
x_{i+1}+\frac{b}{a-1}\equiv a\left( x_i+\frac{b}{a-1} \right) \pmod p
$$
由等比数列的通项公式得
$$
x_n+\frac{b}{a-1}\equiv a^{n}\times \left( x_0+\frac{b}{a-1} \right)\pmod p
$$
题目是求 $n$，移个项
$$
a^{n}\equiv \frac{{x_n+\frac{b}{a-1}}}{x_0+\frac{b}{a-1}}
$$
然后求下逆元就能 BSGS 了。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
inline int read();
int T;
long long p,a,b,x0,xn;
long long ksm(long long a,long long b,long long p)
{
	long long ans=1;
	while(b)
	{
		if(b&1) ans=(a*ans)%p;
		a=(a*a)%p;
		b>>=1;
	}
	return ans;
}
long long bsgs(long long a,long long b,long long p)
{
	map<int,int> ma;ma.clear();
	b%=p;
	int t=sqrt(p)+1;
	for(int i=0;i<=t;i++)
	{
		int val=b*ksm(a,i,p)%p;
		ma[val]=i;
	}
	a=ksm(a,t,p);
	for(int i=0;i<=t;i++)
	{
		int val=ksm(a,i,p);
		int j=ma.find(val)==ma.end()?-1:ma[val];
		if(j>0&&i*t-j>=0) return i*t-j;
	}
	return -1;
}
int main()
{
	T=read();
	while(T--)
	{
		p=read();a=read();b=read();x0=read();xn=read();
		if(x0==xn)
		{
			puts("0");
			continue;
		}
		if(a==0)
		{
			if(xn==b) puts("1");
			else puts("-1");
			continue;
		}
		if(a==1&&b==0)
		{
			puts("-1");
			continue;
		}
		if(a==1)
		{
			long long ans=((xn-x0)%p+p)%p*ksm(b,p-2,p)%p;
			printf("%lld\n",ans);
			continue;
		}
		long long inv=b%p*ksm(a-1,p-2,p)%p;
		long long b1=(xn%p+inv)%p;
		long long b2=ksm(x0%p+inv,p-2,p)%p;
		int ans=bsgs(a,b1*b2%p,p);
		printf("%d\n",ans);
	}
	return 0;
}

inline int read()
{
	int x=0,f=1;
	char ch;
	ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-') f=-f;ch=getchar();}
	while(ch<='9'&&ch>='0')
	{
		x=(x<<1)+(x<<3)+(ch&15);
		ch=getchar();
	}
    return x*f;
}
```

[也许更好的阅读体验](https://www.cnblogs.com/yzxgg/p/18237528/solution-ABC270G)

---

## 作者：huangkx (赞：2)

## 思路

首先处理 $i = 0$ 的情况：

$$
S \equiv G \pmod P
$$

直接判断即可。

接下来处理 $i \geq 1$ 的情况。

当 $A \equiv 0 \pmod p$ 时：

$$
B \equiv G \pmod P
$$

直接判断即可。

当 $A \equiv 1 \pmod p$ 时：

$$
S + i B \equiv G \pmod P
$$
$$
i \equiv \frac { G - S } { B } \pmod P
$$

用乘法逆元求解即可。若 $B \equiv 0 \pmod P$，则无解。

当 $A > 1 \pmod p$ 时：

$$
X _ i \equiv G \pmod P
$$
$$
A ^ i S + \sum _ { j = 0 } ^ { i - 1 } A ^ j B \equiv G \pmod P
$$
$$
A ^ i S + \frac { ( A ^ i - 1 ) B } { A - 1 } \equiv G \pmod P
$$
$$
A ^ i \equiv \frac { A G - G + B } { A S - S + B } \pmod P
$$

用乘法逆元和 $\texttt {BSGS}$ 算法求解即可。

## 代码

```cpp
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define int long long
using namespace std;
int T, P, A, B, S, G;
int Power(int a, int b)
{
	int res = 1;
	while(b){
		if(b & 1) res = res * a % P;
		a = a * a % P;
		b >>= 1;
	}
	return res;
}
int Inv(int a)
{
	return Power(a, P - 2);
}
int BSGS(int a, int b)
{
	if(b % P == 1) return 0;
	int m = ceil(sqrt(P)), x = 1, y = 1;
	unordered_map < int, int > h;
	for(int i = 1; i <= m; i ++){
		x = x * a % P;
		h[b * x % P] = i;
	}
	for(int i = 1; i <= m; i ++){
		y = y * x % P;
		if(h[y]) return m * i - h[y];
	}
	return - 1;
}
signed main()
{
	scanf("%lld", & T);
	while(T --){
		scanf("%lld%lld%lld%lld%lld", & P, & A, & B, & S, & G);
		A %= P, B %= P, S %= P, G %= P;
		if(S == G) printf("%d\n", 0);
		else{
			if(A == 0) printf("%lld\n", B == G ? 1ll : - 1ll);
			if(A == 1) printf("%lld\n", B == 0 ? - 1ll : (G - S + P) * Inv(B) % P);
			if(A > 1) printf("%lld\n", BSGS(A, (A * G % P - G + B + P) * Inv(A * S % P - S + B + P) % P));
		}
	}
	return 0;
}
```

2022.12.13

---

## 作者：翼德天尊 (赞：1)

想不到什么好的做法，就先考虑将式子展开：
$$
\begin{aligned}
X_i
&=(AX_{i-1}+B)\bmod P\\
&=(A^2X_{i-2}+AB+B)\bmod P\\
&=(A^3X_{i-3}+A^2B+AB+B)\bmod P\\
&=\dots\\
&=(A^iS+B(A^{i-1}+\dots +1))\bmod P\\
&=(A^iS+B\frac{A^i-1}{A-1})\bmod P\\
&=G
\end{aligned}
$$
 我们把所有和 $A_i$ 有关的项全部放到右边，剩下的扔到左边，将等式两边同时乘上 $A-1$ 再加 $B$，则有：
$$
AG-G+B=(AS-S+B)A^i\ (\bmod P)
$$
左边的常数看作 $x$，右边的常数看作 $y$，则有：
$$
yA^i=x\ (\bmod P)
$$
也就是一个经典的高次同余方程。我们可以采用 BSGS 算法求解。

哈希用 map 实现，时间复杂度 $O(T\sqrt{P}\log \sqrt{P})$。

需要注意当 $A=1$ 的时候，上面的式子是不成立的，我们会得到：
$$
X_i=S+iB=G\ (\bmod P)
$$
此时 $i=\frac{G-S}{B}$，作个逆元即可。同样此时也需要判断 $B$ 是否为 $0$，如果为 $0$ 则需要进一步特判。

除此之外还需要特判一下 $X_0=S$ 是否等于 $G$，以及 $A$ 是否为 $0$。 

总结来说，本题的本质实际上就是根号优化，细拆 BSGS 根号优化的本质其实就是一个 meet in the middle。$X_i$ 显然是不好做的，因为我们无法将两个 $X_i$ 的答案拼起来得到另一个 $X_i$，因为这个式子不满足结合律。于是我们将 $X_i$ 的式子拆开，将高次幂项和其它项分离，发现可以化成一个满足结合律的高次同余方程的形式，于是就可以使用 BSGS 进行根号优化。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int long long
int p,a,b,s,g;
map<int,int> m;
ll read(){
	ll w=0,f=1;
	char c=getchar();
	while (c>'9'||c<'0'){
		if (c=='-') f=-1;
		c=getchar();
	}
	while (c>='0'&&c<='9'){
		w=(w<<3)+(w<<1)+(c^48);
		c=getchar();
	}
	return w*f;
}
int ksm(int x,int y){
	int ans=1;
	while (y){
		if (y&1) ans=ans*x%p;
		x=x*x%p;
		y>>=1;
	}
	return ans;
}
int inv(int x){
	return ksm(x,p-2);
}
signed main(){
	int t=read();
	while (t--){
		m.clear();
		p=read(),a=read(),b=read(),s=read(),g=read();
		if (s==g){
			puts("0");
			continue;	
		}
		if (a==0){
			if (b==g) puts("1");
			else puts("-1");
			continue;
		}
		if (a==1){
			if (b==0){
				puts("-1");
			}else cout<<(g-s+p)%p*inv(b)%p<<'\n';
			continue;
		}
		int x=(a*g%p-g+b+p)%p,y=(a*s%p-s+b+p)%p,sq=sqrt(p)+1,now=1;
		for (int i=0;i<sq;i++){
			int zc=now*x%p;
			m[zc]=i;
			now=now*a%p;
		}
		int sum=now;
		bool flag=0;
		for (int i=1;i<=sq;i++){
			if (m.count(sum*y%p)){
				cout<<i*sq-m[sum*y%p]<<'\n';
				flag=1;
				break;
			}
			sum=sum*now%p;
		}
		if (!flag) puts("-1");
	}
	
	return 0;
}
```

---

## 作者：shyr (赞：1)

我们将 $X$ 进行展开：

$X_0=S$。

$X_1=S\times A+B$。

$X_2=A\times X_1+B=S\times A^2+AB+B$。

$X_3=A\times X_2+B=S\times A^3+A^2B+AB+B$。

$$\vdots$$

$X_n=S\times A^n+B(A^0+A^1+\dots+A^{n-1})(n\neq0)$。

根据等比数列求和公式 $x_0+x_1+x_2+\cdots+x_{n-1}=\frac{x^n-1}{x-1}$，化简可得：

$X_n=S\times A^n+B\times \frac{A^n-1}{A-1}$。

所以我们求的是 $G\equiv S\times A^n+B\times \frac{A^n-1}{A-1}(\bmod P)$。

化式子可得 $AG-G+B\equiv (AS-S+B)A^n(\bmod P)$。

令左边一坨为 $a$，右边 $A^n$ 的系数为 $b$，则原式相当于 $a\equiv bA^n(\bmod P)$。

由于 $P\in[2,10^9]$，我们可以采用广为人知的 BSGS 算法解决本问题。

我用了 std::map 实现了哈希，时间复杂度 $\mathrm{O}(T\sqrt p \log \sqrt p)$。

注意我的 BSGS 求的是最小非负整数解，所以记得特判 $S=G$ 的情况。

同时原式在 $A=1$ 时由于 $A-1=0$ 所以我们不能用这个式子算，考虑 $1$ 的任何次方等于 $1$，结合之前的公式可得 $G\equiv S+Bn(\bmod P)$，所以答案即为 $\frac{G-S}{B}$，特别的，若 $B=0$ 则类比 $S=G$ 的情况。

如果 $S=0\land B=0$，此时 $\forall X_i=0(i\in \mathbb{N})$，若 $G\neq 0$ 则无解。

在 $G\neq S$ 的前提下，若 $A=0$ 则 $\forall b_i=B(i\in(0,+\infty))$，若 $B\neq G$ 则无解，反之为 $1$。

代码不给了。



---

## 作者：luuia (赞：0)

### Question

给定序列 $x$，满足 $x_0=s,x_i = ax_{i-1}+b$，求最小的 $n$，使得 $x_n=g$。

### Solution

先考虑求出 $x$ 的通项公式。

设 $x_i + \lambda = a\,(x_{i-1}+\lambda)$，解得 $\lambda = \dfrac{b}{a-1}$，因此我们构造序列 $y_i = x_i+\dfrac{b}{a-1}$，则 $y$ 是一个首项为 $s+\dfrac{b}{a-1}$，公比为 $a$ 的等比数列。

因此我们得到 $x_n = a^n\,(s+\dfrac{b}{a-1})-\dfrac{b}{a-1} = g$。

化简上式，得到 

$$a^n \equiv \frac{ag-g+b}{as-s+b} \pmod p$$

对右边分母求逆元，再 BSGS 即可解决，注意特判 $a \le 1$ 和 $s=g$ 的情况。

### Code


```cpp
#include<bits/stdc++.h>
using namespace std;

long long read()
{
    long long s = 0,w = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9')
    {
        if(ch == '-') w = -1;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9')
    {
        s = (s << 1) + (s << 3) + (ch ^ 48);
        ch = getchar();
    }
    return s * w;
}

long long T,p,a,b,s,g,A,B,P;

long long quickpow(long long c,long long n,long long m)
{
	long long res = 1;
	while(n)
	{
		if(n & 1) res = res * c % m;
		c = c * c % m;
		n >>= 1;
	}	
	return res;
}

long long BSGS(long long c,long long b,long long p)
{
    map<long long,long long> a;
    long long m = (int)ceil(sqrt(p)),t = b % p,s = 1;
    a[t] = 0;
    for(int i = 1;i <= m;i++)
    {
        t = t * c % p;
        a[t] = i;
    }
    t = quickpow(c,m,p);
    for(int i = 1;i <= m;i++)
    {
        s = s * t % p;
        if(a[s]) return ((i * m - a[s]) % p + p) % p;
    }
    return -1;
}

int main()
{
    // freopen("input.in","r",stdin);
    T = read();
    while(T--)
    {
        p = read(),a = read(),b = read(),s = read(),g = read();
        if(s == g) {cout << 0 << endl;continue;}
        if(a == 0) {cout << (b == g ? 1 : -1) << endl;continue;}
		if(a == 1) {cout << (b == 0 ? -1 : (g - s + p) * quickpow(b,p - 2,p) % p) << endl;continue;}
        a %= p,b %= p,g %= p,s %= p;
        B = ((a * g % p + b - g) % p + p) % p * quickpow(((a * s % p + b - s) % p + p) % p,p - 2,p) % p;
        long long ans = BSGS(a,B,p);
        cout << ans << endl;
    }
    return 0;
}
```

---

## 作者：hzoi_Shadow (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc270_g)

# 前置知识

[大步小步算法](https://oi-wiki.org/math/number-theory/discrete-logarithm/#大步小步算法)

# 解法

- 递推式为 $x_{n}=(ax_{n-1}+b) \bmod p$，发现可以统一消去 $\bmod p$ ，只在最后参与计算。以下过程省去模运算。
- 当 $x_{0}=t$ 时，则 $n=0$ 即为所求。
- 当 $a=0,x_{0} \ne t$ 时，递推式转化为 $x_{n}=b \bmod p$ 。若 $b=t$ ，则 $n=1$ 即为所求；否则无解。
- 当 $a \ne 0,x_{0} \ne t$ 时，设 $x_{n}+c=a(x_{n-1}+c)$ 。
  - 当 $a=1$ 时，递推式转化为 $\begin{aligned} x_{n}&=x_{n-1}+b \\ &=x_{n-2}+2b \\ &=x_{n-3}+3b \\ &= \dots \\ &=x_{0}+nb \end{aligned}$，将 $x_{n}=t$ 代入得 $t=(x_{0}+nb) \bmod p$，移项得 $nb \equiv (t-x_{0}) \pmod {p}$。当 $\gcd(b,p)|(t-x_{0})$ 时，移项得 $n \equiv \dfrac{t-x_{0}}{b} \pmod {p}$，解得 $n \equiv \dfrac{t-x_{0}}{b} \pmod {p}$；否则无解。
  - 当 $a \ne 1$ 时，解得 $c=\dfrac{b}{a-1}$ 并和 $x_{n}=t$ 一起代入原式得 $\begin{aligned} t+\dfrac{b}{a-1}&=a(x_{n-1}+\dfrac{b}{a-1}) \\ &=a^{2}(x_{n-2}+\dfrac{b}{a-1}) \\ &=a^{3}(x_{n-3}+\dfrac{b}{a-1}) \\ &= \dots \\ &=a^{n}(x_{0}+\dfrac{b}{a-1}) \end{aligned}$ 。当 $\gcd(x_{0}+\dfrac{b}{a-1},p)|(t+\dfrac{b}{a-1})$ 时，移项得 $a^{n} \equiv \dfrac{t+\dfrac{b}{a-1}}{x_{0}+\dfrac{b}{a-1}} \pmod {p}$ ，跑遍 BSGS 求解即可；否则无解。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
#define ull unsigned long long
#define sort stable_sort 
#define endl '\n'
ll qpow(ll a,ll b,ll p)
{
	ll ans=1;
	while(b>0)
	{
		if(b&1)
		{
			ans=ans*a%p;
		}
		b>>=1;
		a=a*a%p;
	}
	return ans;
}
ll gcd(ll a,ll b)
{
	return b?gcd(b,a%b):a;
}
ll bsgs(ll a,ll b,ll p)
{
	if(1%p==b%p)
    {
        return 0;
    }
    else
    {
        map<ll,ll>vis;
        ll k=sqrt(p)+1,i,sum;
        for(i=0;i<=k-1;i++)
        {
            vis[b*qpow(a,i,p)%p]=i;
        }
        a=qpow(a,k,p);
		for(i=0;i<=k;i++)
		{
			sum=qpow(a,i,p);
			if(vis.find(sum)!=vis.end())
			{
				if(i*k-vis[sum]>=0)
				{
					return i*k-vis[sum];
				}
			}
		}
		return -1;
    }
}
int main()
{
	ll t,p,a,b,x0,day,ans,sum,i;
	cin>>t;
	for(i=1;i<=t;i++)
	{
		cin>>p>>a>>b>>x0>>day;
		if(x0==day)
		{
			cout<<0<<endl;
		}
		else
		{
			if(a==0)
			{
				cout<<((b==day)?1:-1)<<endl;
			}
			else
			{
				if(a==1)
				{
					if((day-x0)%gcd(b,p)==0)
					{
						cout<<qpow(b,p-2,p)*(day-x0+p)%p<<endl;
					}
					else
					{
						cout<<-1<<endl;
					}
				}
				else
				{
					sum=qpow(a-1,p-2,p)*b%p;
					if((day+sum)%gcd(x0+sum,p)==0)
					{
						ans=bsgs(a,((day+sum)%p)*qpow(x0+sum,p-2,p)%p,p);
						cout<<ans<<endl;
					}
					else
					{
						cout<<-1<<endl;
					}
				}
			}
		}
	}
	return 0;
}
``` 

# 后记

多倍经验：P3306 | Gym103486C

---

## 作者：HappyJaPhy (赞：0)

- [[ABC270G] Sequence in mod P](https://www.luogu.com.cn/problem/AT_abc270_g)
- [博客阅读~~可能~~体验更佳](https://www.luogu.com.cn/blog/ImDustSans/solution-at-abc270-g)
# 题意
- 给出递推式如下，求最小的使 $X_i=G$ 成立的 $i$。
$$X_i=\begin{cases}
S&i=0\\
(A\times X_{i-1}+B)\bmod p&i\ge1
\end{cases}$$

# 分析
- 这里分几种情况来分析：当 $A=0$ 时，$X_i$ 要么等于 $S$，要么等于 $B$，直接判断即可；当 $A=1$ 时，$X_i$ 为等差数列，通项公式为 $X_i=(S+i\times B)\bmod p$，于是求解同余方程 $S+i\times B\equiv G\pmod p$ 即可。
- 最后一种情况，当 $A\ge2$ 时，根据高中的一些知识我们可以知道，这个是可以转化成一个等比数列的。待定系数 $C$ 有 $X_i+C\equiv A(X_{i-1}+C)\pmod p$，解得 $C=(A-1)^{-1}\cdot B\bmod p$。令 $Y_i=(X_i+C)\bmod p$，那么 $Y_i\equiv A^i\cdot Y_0\equiv A^i\cdot(S+C)\pmod p$。因此原问题转化为关于 $i$ 的同余方程 $G+C\equiv A^i\cdot(S+C)\pmod p$ 是否有解和最小正整数解的问题了。这是离散对数问题，利用大步小步算法求解即可。

## 大步小步算法（BSGS）
- 用于求解形如方程 $A^x\equiv B\pmod p$ 的离散对数问题，其基于 meet-in-the-middle 的思想，复杂度 $\tilde{O}(\sqrt n)$。
- 首先因为 $A^{x+n(p-1)}\equiv A^x(A^{p-1})^n\equiv A^x\pmod p$，所以如果原方程有解，则在 $[0,n-2]$ 的范围也一定有解。
- 我们拆分 $x$，令 $B=\lceil\sqrt p\rceil$，则一定存在 $0\le L,R\le B$ 使得 $x=L\cdot B-R$。此时方程转化为求解 $0\le L,R\le B$ 满足
$$A^{LB}\equiv B\cdot A^R\pmod p$$
- 根据这个式子，我们先预处理出 $S=\left\{(A^B)^L\bmod p|0\le L\le B\right\}$ 中的所有值，然后对于每一个 $0\le R\le B$ 计算出 $B\cdot A^R\bmod p$ 并判断是否在集合 $S$ 中即可。

# 代码
```cpp
#include <bits/stdc++.h>
#define int long long
#define inf 1e10
using namespace std;
int a, b, s, g, p;
int A, B, C;

inline void read(int &x) {
	char ch = x = 0;
	int m = 1;
	while (ch < '0' || ch > '9') ch = getchar();
	while (ch >= '0' && ch <= '9') {
		x = (x << 1) + (x << 3) + ch - 48;
		ch = getchar();
	}
	x *= m;
	return ;
}

inline void print(int x) {
	if (x < 0) putchar('-'), x = -x;
	static int stk[50];
	int top = 0;
	do {
		stk[top++] = x % 10;
		x /= 10;
	} while (x);
	while (top) {
		putchar(stk[--top] + 48);
	}
	putchar('\n');
	return ;
}

inline int ksmi(int a, int b, int p) {
	a %= p;
	int res = 1;
	while (b) {
		if (b & 1) res = res * a % p;
		a = a * a % p;
		b >>= 1;
	}
	return res;
}

inline int BSGS(int a, int b, int p) {
	a %= p, b %= p;
	if (b == 1 || a == b) return b != 1;
	map<int, int> mp;
	int B = ceil(sqrt(p)), res = inf;
	for (int i = B; i; i--) {
		mp[ksmi(a, i * B, p)] = i * B;
	}
	for (int i = 0; i <= B; i++) {
		if (mp.find(b * ksmi(a, i, p) % p) != mp.end()) {
			res = min(res, mp[b * ksmi(a, i, p) % p] - i);
		}
	}
	if (res == inf) {
		return -1;
	} else {
		return res;
	}
}

signed main() {
	int T;
	read(T);
	while (T--) {
		read(p), read(a), read(b), read(s), read(g);
		if (s == g) print(0);
		else if (a == 0) {
			if (b == g) print(1);
			else print(-1);
		} else if (a == 1) {
			if (b == 0) print(-1);
			else {
				int x = ((g - s) % p + p) % p * ksmi(b, p - 2, p) % p;
				print(x);
			}
		} else if (s == 0 && b == 0) {
			print(-1);
		} else {
			A = a, C = ksmi(A - 1, p - 2, p) * b % p;
			B = ksmi(s + C, p - 2, p) * ((g + C) % p) % p;
			print(BSGS(A, B, p));
		}
	}
	return 0;
}
```


---

## 作者：BreakPlus (赞：0)

首先这个是组合数学的一个基础 trick，非常非常典：

$X_i = AX_{i-1} + B$ （以下省略同余）

我们试图利用 $A$ 作为转移两求出通项公式，那么对于 $X_i$ 进行换元和调整。定义未知量 $C$，想要变成下面的形式：

$X_i + C = A(X_{i-1} + C)$ 

定义 $Y_i = X_{i} + C$ 即可求出通项。

那么把它与原递推式结合可以解得 $C = \dfrac{B}{A-1}$。注意看分母，所以我们得做掉 $A=0$ 和 $A=1$ 的情况。

下面整理以下我们的具体做法。

1. 当 $A=0$ 时，判断 $G=B$ 和 $G=S$ 两种情况。
2. 当 $A=1$ 时候，发现 $X_i = S + Bi$，解得 $i = \dfrac{G-S}{B}$。需要特判 $B=0$。
3. 否则利用通项公式 $X_i = (S + C) \times A^i - C$ 解方程。是 BSGS 的板子。

Tip：实现的时候把 $P$ 和头文件的 $\text{mod}$ 搞混，然后又出现遗留问题，警钟敲烂。

```cpp
map<ll,ll>lot;
ll solve(ll a,ll b,ll p){
	if(b==1||a==b) return b!=1;
	lot.clear();
    ll m=ll(sqrt(p))+1;ll tmp=b,ttmp=1;
    lot[m]=0;
    for(ll i=1;i<=m;i++){
        tmp=(tmp*a)%p;
        ttmp=(ttmp*a)%p;
        lot[tmp]=i;
    }
    ll cnt=1;
    for(ll i=1;i<=m;i++){
        cnt=(cnt*ttmp)%p;
        if(lot[cnt]) return (i*m-lot[cnt]+2*p)%p;
    }
    return -1;
} // BSGS 板子
ll A,B,S,G,P;
void solve(){
	P=read(), A=read(), B=read(), S=read(), G=read();
	if(S == G) {puts("0"); return;}
	if(A == 0){
		if(G == B) puts("1");
		else puts("-1");
	}else if(A == 1){
		// Xi = S + B * i
		// S + B * i = G
		// B * i = G - S
		// i = (G - S) / B
		
		ll temp = (G - S + P) % P;
		if(B == 0){
			if(temp == 0){
				puts("0");
			}else puts("-1");
		}else{
			ll niyuan = qpow(B, P-2, P);
			printf("%lld\n", temp * niyuan % P);
		}
	}else{
		// X[i] = AX[i-1] + B
		// X[i] + B/(A-1) = AX[i-1] + A * B / (A-1)
		// X[i] + B/(A-1) = A(X[i-1] + B/(A-1))
		
		ll add = B * qpow(A-1, P-2, P) % P;
		S = (S + add) % P;
		G = (G + add) % P;
		// G = S * (A ^ i)
		// (A ^ i) * S = G
		ll T = G * qpow(S, P-2, P) % P;
		// A^i = T
		// BSGS
		printf("%lld\n", solve(A, T, P));
	}
}
```

---

