# Anniversary

## 题目描述

There are less than 60 years left till the 900-th birthday anniversary of a famous Italian mathematician Leonardo Fibonacci. Of course, such important anniversary needs much preparations.

Dima is sure that it'll be great to learn to solve the following problem by the Big Day: You're given a set $ A $ , consisting of numbers $ l $ , $ l+1 $ , $ l+2 $ , $ ... $ , $ r $ ; let's consider all its $ k $ -element subsets; for each such subset let's find the largest common divisor of Fibonacci numbers with indexes, determined by the subset elements. Among all found common divisors, Dima is interested in the largest one.

Dima asked to remind you that Fibonacci numbers are elements of a numeric sequence, where $ F_{1}=1 $ , $ F_{2}=1 $ , $ F_{n}=F_{n-1}+F_{n-2} $ for $ n>=3 $ .

Dima has more than half a century ahead to solve the given task, but you only have two hours. Count the residue from dividing the sought largest common divisor by $ m $ .

## 样例 #1

### 输入

```
10 1 8 2
```

### 输出

```
3
```

## 样例 #2

### 输入

```
10 1 8 3
```

### 输出

```
1
```

# 题解

## 作者：Hisy (赞：5)

# 说明
设 $F$ 为斐波那契数列。
# 性质
首先，你需要知道一个性质：
$$\Large\gcd(F_n,F_{n+1})=1$$
证明可以用辗转相减法，~~由于本人不会 Latex~~，那么直接用文字证明：
- $F_{n+1}-F{n}=F{n-1}$，所以：
- $\gcd(F_n,F_{n+1})=\gcd(F_{n-1},F_n)$。
- 那么，当 $n$ 递归到 2 的时候就得 $\gcd(1,1)=1$。
- 固得证。

之后，我们要证明一个东西。

设 $n<m$，$x=F_n$，$y=F_{n+1}$，那么：
- $F_{n+1}=x+y$，$F_{n+2}=x+2y$，$F_{n+3}=2x+3y$……$F_{m}=F_{m-n-1}\times x+F_{m-n}\times b$。
- 那么，$F_m=F_{m-n-1}\times F_n+F_{m-n}\times F_{n+1}$。
- 那么，$\gcd(F_n,F_m)=\gcd(F_n,F_{m-n}\times F_{n+1})$。
- 由互质性质可知，$\gcd(F_n,F_m)=\gcd(F_n,F_{m-n})$。
- 递归下去，可以知道答案就是 $F_{\gcd(n,m)}$。
# 分析
我们需要求出一个最大的 $res$，使得 $\sum_{i=l}^{r}[res|fib_i]\ge k$。由于上述的性质，所以可以变为：$\sum_{i=1}^{r}[res|i]\ge k$。注意！这个 $res$ 不可以二分。证明：
- 设计数函数 $cnt(res)=\lfloor\frac{r}{res}\rfloor-\lfloor\frac{l-1}{res}\rfloor$。那么二分所需要的单调性是 $cnt(res)\ge cnt(res+1)$。
- 但是，$l=4,r=8$ 的情况可以知道 $cnt(3)<cnt(4)$，原因是向下取整会有精度流失，不能够强行证明。而且如果两端都是 $res+1$ 的倍数，那么 $cnt(res+1)\ge2$，但是只能保证 $cnt(res)\ge1$。

那么怎么样才能够求出这一个 $res$ 呢？其实可以用根号枚举。我们需要的是 $cnt(res)$ 不同的结果，这样的结果最多有 $\lfloor\sqrt{r}\rfloor$ 个，有时候会多一些。那么，我们求：
$$\Large res=\max_{i=1}^{\lfloor\sqrt{r}\rfloor}(\max(cnt(i),cnt(\lfloor\frac{n}{i}\rfloor)))$$
即可。
# 加速
可以发现这一个值可能会很大，那么我们需要很高效的算法，求出 $F_{res}$。这个算法就是矩阵快速幂优化 dp。

可以发现斐波那契数列本质上是一个 dp，即：
$$dp_i=\begin{cases}
1&i\le2\\
dp_{i-2}+dp_{i-1}&i>3
\end{cases}$$
矩阵快速幂的本质是利用矩阵乘法的乘法结合律来用 $\log n$ 的时间复杂度来求出分矩阵，然后乘上原矩阵。

矩阵乘法的规则如下：
- 定义 $x$ 为长度 $n,m$ 的矩阵，$y$ 为长度 $m,k$ 的矩阵，那么它们相乘的结果为长度为 $n,k$ 的矩阵 $res$。
- $res_{i,j}=\sum_{k=1}^{m}x_{i,k}\times y_{k,j}$。

可以看出这一个式子似乎能够优化所有转移方程只带加法和乘法的 dp。但是，要证明两点：
- 矩阵乘法不满足乘法交换律，因为交换后 $n$ 可能不等于 $k$。
- 矩阵乘法满足结合律。因为 $\{n,m\}\times\{m,k\}\times\{k,l\}$，不管先算哪一个，要么得出 $\{n,k\}\times\{k,l\}=\{n,l\}$，要么得出 $\{n,m\}\times\{m,l\}=\{n,l\}$。

所以，矩阵乘法满足结合律。那么，矩阵乘法的递推式要视情况而定。比如这一道题目需要：

$$\Large\begin{pmatrix}
0&1
\end{pmatrix}\times\Large\begin{pmatrix}
1&1\\
1&0
\end{pmatrix}^{res}$$
因为可以知道 $res$ 等于 1 的时候，乘完之后会得：
$$
\Large\begin{pmatrix}
1&1
\end{pmatrix}
$$
这时候可能不太明显，再乘 $n$ 次：
$$
\Large\begin{pmatrix}
1&2
\end{pmatrix}
$$
$$
\Large\begin{pmatrix}
2&3
\end{pmatrix}
$$
$$
\Large\begin{pmatrix}
3&5
\end{pmatrix}
$$
$$
\Large\begin{pmatrix}
5&8
\end{pmatrix}
$$
这是斐波那契数列。为什么是斐波那契数列呢？因为可以变成：
$$\Large\begin{pmatrix}
dp_{i-1}&dp_{i}
\end{pmatrix}\times\Large\begin{pmatrix}
1&1\\
1&0
\end{pmatrix}=\begin{pmatrix}
dp_{i}&dp_{i-1}+dp_{i}
\end{pmatrix}$$
这就是矩阵快速幂优化 dp 的过程。在一些线性 dp 会超时的时候就可以用矩阵快速幂优化。可以优化到 $\log n$ 级别的递推式。

所以，可以构造如上的矩阵然后求矩阵快速幂。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
struct matrix{
	int n,m;
	ll a[3][3];
	matrix(){
		memset(a,0,sizeof(a));
	}
	inline ll *operator[](int index){
		return a[index];
	} 
};
int mod;
ll l,r,k;
inline matrix operator*(matrix x,matrix y){
	matrix res;
	res.n=x.n;
	res.m=y.m;
	for(int i=1;i<=x.n;++i){
		for(int j=1;j<=x.m;++j){
			for(int k=1;k<=y.m;++k){
				(res[i][k]+=x[i][j]*y[j][k])%=mod;
			}
		}
	}
	return res;
}
inline matrix power(matrix x,ll y){
	matrix res=x;
	while(y){
		if(y&1){
			res=res*x;
		}
		y>>=1;
		x=x*x;
	}
	return res;
}
int main(){
	scanf("%d %lld %lld %lld",&mod,&l,&r,&k);
	ll res=0;
	for(ll i=1;i*i<=r;++i){
		if(r/i-(l-1)/i>=k){
			res=max(res,i);
		}
		if(r/(r/i)-(l-1)/(r/i)>=k){
			res=max(res,r/i);
		}
	}
	matrix x,y;
	x.n=x.m=y.n=2;
	y.m=1;
	x[1][1]=x[1][2]=x[2][1]=y[2][1]=1;
	printf("%lld",matrix(power(x,res-1)*y)[1][1]);
	return 0;
}
```

---

## 作者：naoliaok_lovely (赞：4)

## 题目大意
在 $F_{l\sim r}$ 中选 $k$ 个数，使得这些数的 $\gcd$ 最大，求这个最大值。其中，$F$ 表示斐波那契数列。

# 切入点
由于 $l,r$ 很大，而题目还要求 $\gcd$ 模上一个数，所以会感觉到答案应该是一个很特殊的结果。事实也确实如此——答案一定为斐波那契数列中的某一项！观察到这一点是很重要的，下面考虑如何证明：

设答案为 $d$，满足 $d|F_i$ 的最小的 $i$ 为 $res$（显然，$res$ 是必然存在的）。根据斐波那契的另一种递推形式（若斐波那契数列的前两项为 $a,b$，则 $f_i=F_{i-2}a+F_{i-1}b$），我们有：$F_i=F_{i-res-1}F_{res}+F_{i-res}F_{res+1}(i>res)$。注意到，斐波那契数列的相邻两项一定互质。又因为 $d|F_i$（我们选择了第 $i$ 项）且 $d|F_{res}$，那么可推导出：$d|F_{i-res}$。由于 $F_{res}$ 是最小的 $d$ 的倍数，那么 $i$ 的最小值就只能是 $2res$。同理可得，$i$ 一定要满足：$i\in\{k\times res|k\in\Z_+\}$。显然，这些数的最大公因数为 $F_{res}$！所以，答案一定为数列中的某一个值。

# 思路
先求出上述的 $res$，再用矩阵快速幂求出 $F_{res}$ 即可。

# 代码
注意一点，求 $res$ 到底应该怎么写？二分和暴力都是不行的，这里作者用了整除分块，可能有些麻烦。
```
#include<bits/stdc++.h>
using namespace std;
#define LL long long

int mod;
LL l, r, k;

struct Matrix
{
	int n, m;
	int a[3][3];
	Matrix()
	{
		memset(a, 0, sizeof(a));
	}
}A, B;

Matrix operator*(Matrix A, Matrix B)
{
	Matrix C;
	C.n = A.n, C.m = B.m;
	for(int i = 1; i <= A.n; i++)
		for(int j = 1; j <= A.m; j++)
			for(int k = 1; k <= B.m; k++)
				C.a[i][k] = (C.a[i][k] + 1ll * A.a[i][j] * B.a[j][k]) % mod;
	return C;
}

Matrix ksm(Matrix x, LL y)
{
	Matrix res = x;
	y--;
	while(y)
	{
		if(y & 1) res = res * x;
		y >>= 1;
		x = x * x;
	}
	return res;
}

int main()
{
	cin >> mod >> l >> r >> k;
	LL res = (r - l) / (k - 1);
	while(r / res - (l - 1) / res < k) res = r / (r / res + 1);
	
	A.n = A.m = 2, A.a[1][1] = 1, A.a[1][2] = 1, A.a[2][1] = 1;
	B.n = 2, B.m = 1, B.a[2][1] = 1;
	B = ksm(A, res) * B;
	cout << B.a[1][1] << endl;
	return 0;
}
```

---

## 作者：Fuko_Ibuki (赞：3)

我一看可高兴了,觉得此题非常可做.   
首先我们考虑斐波那契数列$F(n)$ 的一个性质:  
$gcd(F(a),F(b))=F(gcd(a,b))$  
我记得这个性质是我从哪里知道的来着?  
[luogu p1306 斐波那契公约数](https://www.luogu.org/problemnew/show/P1306)  
然后只要找到最大的$x$使得$x$的倍数在$[l,r]$里大于或者等于$k$个即可.  
猜猜这个$x$能不能二分?  
这里我不得不把我自己批一顿.  
`我竟然对不能二分的东西写了二分,而且一开始以为自己二分萎了后来才发现根本不能二分,调了5个小时!`  
根据数据范围我们用$\sqrt n$ 的枚举.
假设存在一个数字$q$,对于$q-1$来说,它在$[l,r]$内的倍数的个数变化了,这样的$q$存在$\sqrt(r)$个.  
由于我们要求的只是最大值,我们只需要对于$\sqrt r$之内的每一个$i$判断$i$和$r/i$ 的倍数在$[l,r]$是不是大于或者等于$k$个即可.  
这样可以求出$ans$,答案就是第$ans$个斐波那契数,用矩阵快速幂即可.  
```cpp
#include<bits/stdc++.h> //Ithea Myse Valgulious
namespace chtholly{
typedef long long ll;
#define re0 register int
#define rec register char
#define rel register ll
#define gc getchar
#define pc putchar
#define p32 pc(' ')
#define pl puts("")
/*By Citrus*/
inline int read(){
  int x=0,f=1;char c=gc();
  for (;!isdigit(c);c=gc()) f^=c=='-';
  for (;isdigit(c);c=gc()) x=(x<<3)+(x<<1)+(c^'0');
  return f?x:-x;
  }
template <typename mitsuha>
inline bool read(mitsuha &x){
  x=0;int f=1;char c=gc();
  for (;!isdigit(c)&&~c;c=gc()) f^=c=='-';
  if (!~c) return 0;
  for (;isdigit(c);c=gc()) x=(x<<3)+(x<<1)+(c^'0');
  return x=f?x:-x,1;
  }
template <typename mitsuha>
inline int write(mitsuha x){
  if (!x) return 0&pc(48);
  if (x<0) x=-x,pc('-');
  int bit[20],i,p=0;
  for (;x;x/=10) bit[++p]=x%10;
  for (i=p;i;--i) pc(bit[i]+48);
  return 0;
  }
inline char fuhao(){
  char c=gc();
  for (;isspace(c);c=gc());
  return c;
  }
}using namespace chtholly;
using namespace std;
const int mod=read();
ll l,r,k;

bool judge(ll x){
return r/x-(l-1)/x>=k;
}

struct juzhen{
ll m[3][3];
void clearit(){
  memset(m,0,sizeof m);
  m[1][1]=m[2][2]=1;
  }
void clear(){memset(m,0,sizeof m);}
juzhen operator *(const juzhen &b) const{
  int i,j,k;
  juzhen ans;ans.clear();
  for (i=1;i<3;++i){
    for (j=1;j<3;++j){
      for (k=1;k<3;++k){
        ans.m[i][j]=(ans.m[i][j]+m[i][k]*b.m[k][j])%mod;
        } 
      }
    }return ans;
  }
};

juzhen operator ^(juzhen a,ll b){
juzhen c;c.clearit();
for (;b;b>>=1,a=a*a) if (b&1) c=c*a;
return c;
}

int main(){
read(l),read(r),read(k);
ll ans=0;
for (ll i=1;i*i<=r;++i){
  if (judge(i)) ans=max(ans,i);
  if (judge(r/i)) ans=max(ans,r/i); 
  }
juzhen tmp;
tmp.clear();
tmp.m[1][1]=tmp.m[1][2]=tmp.m[2][1]=1;
tmp=tmp^ans-1;
write((tmp.m[1][1]+mod)%mod);
}
/*
gcd(F(a),F(b))=F(gcd(a,b));
*/
```
谢谢大家.

---

## 作者：chenxia25 (赞：2)

额朋友们好 我是一个看错题号来做这题的人

首先有一个广为人知的结论 $\gcd(fibo_x,fibo_y)=fibo_{\gcd(x,y)}$，这我还不会证。

那么我们只需要找出 $[l,r]$ 中选 $k$ 个数的 $\gcd$ 的最大值即可，然后矩阵快速幂即可求出对应 $fibo$。

$x$ 可以作为一个合法的 $\gcd$ 显然当且仅当 $[l,r]$ 内 $x$ 倍数个数 $\geq k$。运用前缀和有 $\left\lfloor\dfrac rx\right\rfloor-\left\lfloor\dfrac{l-1}x\right\rfloor\geq k$。我们考虑根号分治枚举 $\left\lfloor\dfrac rx\right\rfloor$：暴力的部分就不说了；对于枚举值的部分，算出来可选的区间是 $[L,R]$，那么显然 $R$ 越大，上式的值越大，并且选择的越优，于是我们直接看 $R$ 是否满足并且松弛即可。

---

## 作者：Nylch (赞：1)

首先有个显然的性质：$\gcd(F_a,F_b)=F_{\gcd(a, b)}$，其中 $F$ 指斐波那契数列。

那么问题就转化成在区间 $[l,r]$ 中找 $k$ 个不同的数字使得这些数字的最大公约数最大。

那么在一个区间 $[l,r]$ 中，有因子 $x$ 的数的数量是 $r/x-(l-1)/x$ 个，我们在 $\sqrt{r}$ 中寻找 $i$ 和 $r/i$ 的有因子 $x$ 的数的数量是否大于等于 $k$，记录下最大的一个因子 $id$，那么最后的答案就是 $F_{id}$。

注意要随时取模，模数是数据给出的。

```cpp
#include <bits/stdc++.h>
#define reg register
#define ll long long
#define int long long
#define ull unsigned long long
#define db double
#define pi pair<int, int>
#define pl pair<ll, ll>
#define vi vector<int>
#define vl vector<ll>
#define vpi vector<pi>
#define vpl vector<pl>
#define pb push_back
#define er erase
#define SZ(x) (int) x.size()
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define mkp make_pair
#define dmin(x, y) ((x) < (y) ? (x) : (y))
#define dmax(x, y) ((x) > (y) ? (x) : (y))
#define checkmax(x, y) ((x) < (y) ? ((x) = (y)) : (x))
#define checkmin(x, y) ((x) > (y) ? ((x) = (y)) : (x))
#define ms(data_name) memset(data_name, 0, sizeof(data_name))
#define msn(data_name, num) memset(data_name, num, sizeof(data_name))
#define pls(x, y) ((x) + (y) >= m ? (x) + (y) - m : (x) + (y))
#define mul(x, y) (1ll * (x) * (y) % m)
#define For(i, j) for(reg int (i) = 1; (i) <= (j); ++(i))
#define For0(i, j) for(reg int (i) = 0; (i) < (j); ++(i))
#define Forx(i, j, k) for(reg int (i) = (j); (i) <= (k); ++(i))
#define Forstep(i , j, k, st) for(reg int (i) = (j); (i) <= (k); (i) += (st))
#define fOR(i, j) for(reg int (i) = (j); (i) >= 1; (i)--)
#define fOR0(i, j) for(reg int (i) = (j) - 1; (i) >= 0; (i)--)
#define fORx(i, j, k) for(reg int (i) = (k); (i) >= (j); (i)--)
#define tour(i, u) for(reg int (i) = head[(u)]; (i) != -1; (i) = nxt[(i)])
using namespace std;
char ch, B[1 << 20], *S = B, *T = B;
#define getc() (S == T && (T = (S = B) + fread(B, 1, 1 << 20, stdin), S == T) ? 0 : *S++)
#define isd(c) (c >= '0' && c <= '9')
int rdint() {
  int aa, bb;
  while(ch = getc(), !isd(ch) && ch != '-');
  ch == '-' ? aa = bb = 0 : (aa = ch - '0', bb = 1);
  while(ch = getc(), isd(ch))
    aa = aa * 10 + ch - '0';
  return bb ? aa : -aa;
}
ll rdll() {
  ll aa, bb;
  while(ch = getc(), !isd(ch) && ch != '-');
  ch == '-' ? aa = bb = 0 : (aa = ch - '0', bb = 1);
  while(ch = getc(), isd(ch))
    aa = aa * 10 + ch - '0';
  return bb ? aa : -aa;
}
ll mod, l, r, k;
struct Matrix {
  ll a[3][3];
  Matrix() { memset(a, 0, sizeof a); }
  Matrix operator*(const Matrix &b) const {
    Matrix res;
    for (int i = 1; i <= 2; ++i)
      for (int j = 1; j <= 2; ++j)
        for (int k = 1; k <= 2; ++k)
          res.a[i][j] = (res.a[i][j] + 1ll * a[i][k] * b.a[k][j] % mod) % mod;
    return res;
  }
} ans, base;
void init() {
  base.a[1][1] = base.a[1][2] = base.a[2][1] = 1;
  ans.a[1][1] = ans.a[1][2] = 1;
}
void qpow(int b) {
  while (b) {
    if (b & 1) ans = ans * base;
    base = base * base;
    b >>= 1;
  }
}
inline void work() {
  mod = rdll();
  l = rdll();
  r = rdll();
  k = rdll();
  int id = 0;
  for(reg ll i = 1; i * i <= r; ++i) {
    if(r / i - (l - 1) / i >= k) {
      checkmax(id, i);
    }
    if(r / (r / i) - (l - 1) / (r / i) >= k) {
      checkmax(id, r / i);
    }
  }
  // cout << id << endl;
  if(id <= 2) {
    id = 1 % mod;
    printf("%lld\n", id);
  } else {
    init();
    qpow(id - 2);
    printf("%lld\n", ans.a[1][1] % mod);
  }
}
signed main() {
  // freopen("input.txt", "r", stdin);
  work();
  return 0;
}
```

---

