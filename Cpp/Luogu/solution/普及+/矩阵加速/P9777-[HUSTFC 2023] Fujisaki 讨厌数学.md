# [HUSTFC 2023] Fujisaki 讨厌数学

## 题目描述

众所周知，Fujisaki 在微积分（一）（上）、微积分（一）（下）、线性代数、离散数学（一）、概率论与数理统计这些课程中，只取得了非常低的分数，这导致他十分痛恨高等数学，因此他给大家带来了一道初等数学题。

已知 $x+x^{-1}=k$，其中 $k$ 是一个整数且 $k\ge 2$，Fujisaki 想让你帮他求出 $x^n+x^{-n}$ 的值。可以证明对于任意的整数 $n \ge 0$，这个值都是一个整数。由于结果可能会非常大，你只需要求出其对 $M$ 取模后的值。

## 样例 #1

### 输入

```
998244353 10 1
```

### 输出

```
10```

## 样例 #2

### 输入

```
998244353 2 3
```

### 输出

```
2```

## 样例 #3

### 输入

```
100 4 5
```

### 输出

```
24```

# 题解

## 作者：isletfall (赞：9)

# 题意
 
 已知 $x+x^{-1}=k$，求 $(x^{n}+x^{-n})\bmod M$。
 
# 思路

我们先考虑 $n$ 很小的情况：

当 $n$ 等于 $2$ 时，我们发现这就是一个完全平方公式，即 $x^{2}+x^{-2}=(x+x^{-1})^2-2$，所以我们可以通过 $n=1$ 推出 $n=2$ 时的结果。

当 $n$ 等于 $3$ 时，我们突然想到自己背过立方和公式，即 $x^{3}+x^{-3}=(x+x^{-1})(x^2+x^{-2}-2)$，所以我们也可以通过 $n=2$ 推出 $n=3$ 时的结果。

当 $n$ 等于 $4$ 的时候，我们发现我们不会背公式了，但是由前面的分析可知，$n=4$ 是一定可以由 $n=3$ 推出的。那我们直接对 $x^{3}+x^{-3}$ 乘上一个 $x+x^{-1}$ ，发现结果为 $x^{4}+x^{-4}+x^{2}+x^{-2}$ ，移项一下我们惊奇的发现： 
$x^{4}+x^{-4}=(x^{3}+x^{-3})×(x+x^{-1})-(x^{2}+x^{-2})$ 。

如果我们用 $F_n$ 记录结果，那我们可以得到是不是 $F_4=F_1×F_3-F2$，那我们可以大胆地猜想，是不是 $F_n=F_1×F_{n-1}-F_{n-2}$,然后我们按照上面相同的方法一验证，果然是这样。

这时候我们想到我还是个蒟蒻时曾经写过斐波那契数列这道题，但我们发现这题的 $n$ 的范围非常大，不能直接递推求解。然后我又想到了我在机房垫底时学到的矩阵快速幂优化斐波那契数列，所以我们构造出矩阵：

$\begin{bmatrix}
F_n & F_{n-1}  \\
\end{bmatrix}×\begin{bmatrix}
k & 1\\
-1 & 0\\
\end{bmatrix}$

然后套矩阵快速幂模板即可，时间复杂度 $O(\log{N})$。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
long long n,k,mod;
struct Matrix {
  long long a[3][3];

  Matrix() { memset(a, 0, sizeof a); }

  Matrix operator*(const Matrix &b) const {
    Matrix res;
    for (register int i = 1; i <= 2; ++i)
      for (register int j = 1; j <= 2; ++j)
        for (register int k = 1; k <= 2; ++k)
          res.a[i][j] = (res.a[i][j] + a[i][k] * b.a[k][j]) % mod;
    return res;
  }
} ans, base;

inline void init() {
  base.a[1][1] = k;
  base.a[1][2] = 1;
  base.a[2][1] =-1;
  ans.a[1][1] = (k*k-2)%mod;
  ans.a[1][2] = k%mod;
}

inline void qpow(long long b) {
  while (b) {
    if (b & 1) ans = ans * base;
    base = base * base;
    b >>= 1;
  }
}
long long read(){
    long long a=0;int op=1;char ch=getchar();
    while(ch<'0'||'9'<ch){if(ch=='-')op=-1;ch=getchar();}
    while('0'<=ch&&ch<='9'){a=(a<<3)+(a<<1)+(48^ch);ch=getchar();}
    return a*op;
}
int main() {
  mod=read();
  k=read();
  n=read();
  if (n == 0) {
  	printf("2");
	return 0;
  } 
  if (n == 1) {
  	printf("%lld",k%mod);
  	return 0;
  }
  if (n == 2) {
  	printf("%lld",(k*k-2)%mod);
  	return 0;
  }
  init();
  qpow(n - 2);
  printf("%lld",(ans.a[1][1] +mod)% mod);
}
```
## 后记
赛时这题给我整破防了，写题解的时候也在破防。(怎么有人不考虑 $n=0$ 的情况啊）。

---

## 作者：Kagamino_Natsumi (赞：7)

赛时并没有想到矩阵加速，使用奇怪的思路解决了本题。

首先令 $f(n)=x^{n}+x^{-n}$，容易发现性质：

$$f(n)f(m)=x^{n-m}+x^{m-n}+x^{n+m}+x^{-n-m}=f(n-m)+f(n+m)$$

考虑如何使用该性质。如果令 $m=1$，便可得到 $ k \cdot f(n)=f(n-1)+f(n+1) $，移项后采用矩阵加速递推可以解决。

但是我的思路比较清奇，并没有采取如上解法。考虑下面两个式子：

$$f^2(n)=f(0)+f(2n)=f(2n)+2$$

$$f(n+1)f(n)=f(1)+f(2n+1)=f(2n+1)+k$$

这样对于 $n$，我们分奇偶讨论，并递归求解，复杂度理论上为常数很小的 $O(n)$。

[Link](https://www.luogu.com.cn/record/132753427)

但鉴于 $n \leq 10^{18}$，上述算法并不足以 AC 此题。赛时吃了两发罚时之后，想到了一个非常抽象的方法：**记忆化**。

对于 $1 \leq n \leq 5 \times 10^7$，需要求解时用一个数组存储 $f(n)$ 的结果，若再一次调用即可直接返回值，不需递归计算。这样再次减小了算法的常数，足以通过本题。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll mod,n,k;
int ans[50000007];
ll solve(ll n){
	if(n<=50000000&&ans[n])return ans[n];
	ll res=0;
	if(n&1){
		res=solve(n/2)*solve(n/2+1)%mod+(mod-k);
		res%=mod;
	}
	else{
		ll a=solve(n/2);
		res=a*a%mod+(mod-2);
		res%=mod;
	}
	if(n<=50000000)ans[n]=res;
	return res;
}
int main()
{
	cin>>mod>>k>>n;
	ans[0]=2,ans[1]=k;
	cout<<solve(n)<<endl;
	return 0;
}
```



---

## 作者：sky_chen (赞：7)

令 $f(n)=x^n+x^{-n}$ 

有 $f(n) \cdot f(1)=x^{n+1}+x^{n-1}+x^{-(n-1)}+x^{-(n+1)}=f(n+1)+f(n-1)$

所以有  $f(n+1)=f(1)f(n)-f(n-1)$

又因为 $f(1)=k$ ，$f(n+1)=kf(n)-f(n-1)$，矩阵快速幂即可。

时间复杂度 $O(\log n)$。

---

## 作者：Sk_sync_opener (赞：3)

首先学过初中数学的都知道 $\left( x ^ {i} + x ^ {-i} \right) \times \left(x + x ^ {-1}\right) = \left(x ^ {i + 1} + x ^ {-i-1}\right) + \left(x ^ {i - 1} + x ^ {-i + 1}\right)$。

令 $f(i) = x ^ {i} + x ^ {i - 1}$，则上式转化为 $f(i) \times k = f(i + 1) + f(i - 1)$。

移项，得 $f(i) \times k - f(i - 1) = f(i + 1)$。那么就可以愉快地矩阵快速幂了！

注意特判 $0 \leq n \leq 2$ 的情况。然后注意输出答案需要使用 ``write((ans + mod) % mod);`` 防止出现负数。

---

## 作者：封禁用户 (赞：2)

### 题意
给出 $x+\frac{1}{x}(k)$ 求 $x^n+ \frac{1}{x^n}$。

### 思路
首先可以想到递推。

令 $f_i=x^i+ \frac{1}{x^i}$。

考虑转移。

$
\begin{aligned}
f_i&=x^i+ \frac{1}{x^i}&\\
&=x^i+ \frac{1}{x^i}+x^{i-2}+\frac{1}{x^{i-2}}-(x^{i-2}+\frac{1}{x^{i-2}})&\\
&=(x^{i-1}+\frac{1}{x^{i-1}})(x+\frac{1}{x})-(x^{i-2}+\frac{1}{x^{i-2}})&\\
&=k\times f_{i-1}-f_{i-2}
\end{aligned}
$

$n\le 10^{18}$，矩阵加速即可。

### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int m,k,n;

struct mat{
	int a[3][3];
	void build(){
		for(int i=1;i<=2;++i)
			for(int j=1;j<=2;++j)
				a[i][j]=0;
	}
	mat operator*(const mat x)const{
		mat res;
		res.build();
		for(int i=1;i<=2;++i){
			for(int j=1;j<=2;++j){
				for(int p=1;p<=2;++p){
					res.a[i][j]+=a[i][p]*x.a[p][j]%m;
					res.a[i][j]%=m;
				}
			} 
		} 
		return res;
	}
};

signed main(){
	cin>>m>>k>>n;
	if(n==1){
		cout<<k;
		return 0;
	}
	if(n==0){
		cout<<2;
		return 0;
	}
	mat x;
	x.a[1][1]=0,x.a[1][2]=-1;
	x.a[2][1]=1,x.a[2][2]=k;
	mat res;
	res.build();
	res.a[1][1]=res.a[2][2]=1;
	--n;
	while(n){
		if(n&1)
			res=res*x;
		x=x*x;
		n>>=1;
	}
	cout<<((2*res.a[1][2]+k*res.a[2][2])%m+m)%m;
}
```

---

## 作者：lidagua1004 (赞：2)

数学题，推式子即可。

设 $f(n)=x^n+x^{-n}$ 则可以发现 $f(m)f(n)=(x^m+x^{-m})(x^n+x^{-n})=x^{m+n}+x^{m-n}+x^{-(m-n)}+x^{-(n+m)}=f(m+n)+f(m-n)$，当 $m=1$ 时，$kf(n)=f(1)f(n)=f(n+1)+f(n-1)$ 所以 $f(n)=kf(n-1)-f(n-2)$。接下来用矩阵快速幂即可。

时间复杂度 $O(\log n)$。

---

## 作者：锦依卫小生 (赞：2)

# P9777
## 思路
为了描述方便，我们把 $x^{t}+x^{-t}$ 记作 $t$ 次式。由于 $n$ 很大，我们很容易想到可以考虑用类似 **快速幂** 的方法求得答案。  

```cpp
__int128 quick_pow(__int128 a,__int128 b){//快速幂
	__int128 res=1;
	while(b){
		if(b%2==1)
			res=res*a%p;
		a=a*a%p;
		b=b/2;
	}
	return res;
}
```
  
现在新的问题是，不同于普通快速幂，我们的 $res$ 无法直接由 $res$ 与 $a$ 相乘得到。直接相乘的结果多出了一项。然而，巧妙的地方在于，多出的部分刚好是快速幂运算过程中我们本不需要的项数多一项的结果，多么巧妙。如此一来想我这种不会矩阵快速幂的蒟蒻也可以通过啦。  
  
```cpp
#include<bits/stdc++.h>
using namespace std;
__int128 MOD,n,k;//__int128 不必要，但开了更安全？
__int128 read()
{
	__int128 res=0;
	char scan[1005];
	scanf("%s",scan);
	for(int i=0;i<strlen(scan);i++)
		res*=10,res+=scan[i]-'0';
	return res;
}
void print(__int128 num)
{
	if(num>9) 
		print(num/10);
	putchar(num%10+'0');
}
__int128 quick_pow(__int128 a,__int128 b){
	__int128 res1=2;//规定 0 次式位 2。
	__int128 res2=a;//多出 1 次。
	while(b){
		if(b%2){
			res1=(res1*a-res2)%MOD;//不需要的项。
		}
		else{
			res2=(res2*a-res1)%MOD;//不需要的项。
		}
		a=(a*a-2)%MOD;
		b/=2;
	}
	return res1;
}
int main(){
	MOD=read();
	k=read();
	n=read();
	print(quick_pow(k,n));
}
```




---

## 作者：fish_love_cat (赞：1)

设 $f_n=x^n+x^{-n}$。

已知 $f_0=2,f_1=k$。

同时利用完全平方公式可知 $f_2=k^2-2$。

---

由定义可知

$$f_n\times f_1=(x^n+x^{-n})\times(x+x^{-1})=x^{n+1}+x^{-(n-1)}+x^{n-1}+x^{-(n+1)}$$

所以

$$f_n\times f_1=f_{n+1}+f_{n-1}$$

移项得

$$f_{n+1}=f_{1}\times f_n-f_{n-1}$$

容易得到

$$\begin{bmatrix}
f_n&f_{n-1}
\end{bmatrix}\times
\begin{bmatrix}
k&1\\
-1&0
\end{bmatrix}=
\begin{bmatrix}
f_{n+1}&f_{n}
\end{bmatrix}
$$

所以

$$\begin{bmatrix}
f_n&f_{n-1}
\end{bmatrix}=
\begin{bmatrix}
f_{2}&f_{1}
\end{bmatrix}\times
\begin{bmatrix}
k&1\\
-1&0
\end{bmatrix}^{n-2}
$$

---

然后做完了。

注意负数取模。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int M,K,N;
vector<vector<int> >build_1(int n){
    vector<vector<int> >ret;
    for(int i=0;i<n;i++){
        vector<int>x;
        for(int j=0;j<n;j++){
            if(i==j)x.push_back(1);
            else x.push_back(0);
        }
        ret.push_back(x);
    }
    return ret;
}
vector<vector<int> >m_cheng(vector<vector<int> >a,vector<vector<int> >b,int p=LLONG_MAX){
    vector<vector<int> >c;
    for(int i=0;i<a.size();i++){
        vector<int>x;
        for(int j=0;j<b[0].size();j++){
            int flc=0;
            for(int k=0;k<b.size();k++)
            flc+=a[i][k]*b[k][j]%p,flc%=p;
            x.push_back(flc);
        }
        c.push_back(x);
    }
    return c;
}
vector<vector<int> >m_qpow(vector<vector<int> >a,int b,int p){
    vector<vector<int> >ans=build_1(a.size());
    while(b){
        if(b&1){
            ans=m_cheng(a,ans,p);
        }
        a=m_cheng(a,a,p);
        b>>=1;
    }
    return ans;
}
int fib(int x,int p=LLONG_MAX){
    if(x==0)return 2;
    if(x==1)return K;
    if(x==2)return (K*K-2)%p;
    vector<vector<int> >v={{K,1},{-1,0}},V={{(K*K-2)%p,K}};
    v=m_cheng(V,m_qpow(v,x-2,p),p);
    return (v[0][0]%p+p)%p;
}
signed main(){
    cin>>M>>K>>N;
    cout<<fib(N,M);
    return 0;
}
```

---

## 作者：will1111 (赞：1)

# P9777 [HUSTFC 2023] Fujisaki 讨厌数学 题解

### 思路

为了方便，我们令 ${f(i)=x^i+ \frac{1}{x^i}}$。

根据题目可得 $f(1)=k,f(2)=x^0+ \frac{1}{x^0}=2$。

现在我们考虑如何将 $f(i-1)$ 转移为 $f(i)$。

将 $f(i-1)$ 和 $f(i)$ 展开，相当于将 $x^{i-1}+ \frac{1}{x^{i-1}}$ 转移为 $x^{i}+ \frac{1}{x^{i}}$。

首先将次数加上一，将 $x^{i-1}+ \frac{1}{x^{i-1}}$ 乘上 $x+ \frac{1}{x}$。

$$\large{(x^{i-1}+ \frac{1}{x^{i-1}})\cdot (x+ \frac{1}{x})}$$

展开。

$$\large{x^{i}+ \frac{1}{x^{i}}+x^{i-2}+ \frac{1}{x^{i-2}}}$$

这时只需要减去 $x^{i-2}+ \frac{1}{x^{i-2}}$ 也就是减去 $f(i-2)$。

于是得到递推式：

$$\large{f(i)=k \cdot f(i-1)-f(i-2)}$$

由于 $n$ 很大，考虑矩阵快速幂。

这里属于矩阵加速基础写法，原矩阵为：

$$ \begin{bmatrix}
 0&-1\\
 1&k
\end{bmatrix} $$

### 代码

```cpp
#include<iostream>
#include<cstdio>
#include<vector>

#define int long long

using namespace std;

int MOD;

class Mat
{
	public:
		int v[3][3]={{0,0,0},{0,0,0},{0,0,0}};
};

Mat mul(Mat&a,Mat&b)
{
	Mat ans;
	for(int i=1;i<=2;i++)
	{
		for(int j=1;j<=2;j++)
		{
			for(int k=1;k<=2;k++)
			{
				ans.v[i][j]+=a.v[i][k]*b.v[k][j];
				ans.v[i][j]%=MOD;
			}
		}
	}
	return ans;
}

Mat qpow(Mat a,int b)
{
	Mat ans,t=a;
	ans.v[1][1]=ans.v[2][2]=1;
	while(b>0)
	{
		if(b&1)
		{
			ans=mul(ans,t);
		}
		t=mul(t,t);
		b>>=1;
	}
	return ans;
}

signed main()
{
	int k,n;
	scanf("%lld%lld%lld",&MOD,&k,&n);
	if(n==0)
	{
		cout<<2;
		return 0;
	}
	if(n==1)
	{
		cout<<k;
		return 0;
	}
	Mat tmp;
	tmp.v[1][1]=0;tmp.v[1][2]=-1;
	tmp.v[2][1]=1;tmp.v[2][2]=k;
	Mat tt=qpow(tmp,n-1);
	cout<<((tt.v[1][2]*2+tt.v[2][2]*k)%MOD+MOD)%MOD<<endl;
	return 0;
}
```

---

## 作者：kczw (赞：1)

# 题意
已知 $x+x^{-1}=k$，求 $(x^n+x^{-n})\pmod m$。
# 思路
令 $f_a=x^a+x^{-a}$，易得 $f_0=2$。

相乘移项可得 $f_{a+b}=f_a\times f_b-f_{|a-b|}$，同理 $f_{2^c}={f_{2^{c-1}}}^2-f_0={f_{2^{c-1}}}^2-2$。于是，我们可以快速处理所有二次幂的 $f$ 值，然后从低到高地枚举二进制下每位的值相加，例如 $11011_{(2)}$，记忆化搜索即可。

关于此处为什么不会 TLE，例如 $n=148$，其二进制是 $10010100_{(2)}$，第一个 $|a-b|=100_{(2)}$,第二个 $1100_{(2)}$，第三个 $1101100_{(2)}$，你会发现它们可以看作是被减部分依次按位取反然后最低位加一，这样的产生效果就是所有临近的两个 $|a-b|$ 二进制都只是后者多一些高位 $1$ ，加之我们的记搜方式，效率是搜索时计算次数是 $\log n$ 的。

再看计算这些 $f_{|a-b|}$，$100_{(2)}$ 是二次幂的不必多说，$1100_{(2)}$ 中的 $100_{(2)}$ 的 $f$ 值已知晓，直接求得 $f_{1100_{(2)}}=f_{100_{(2)}}\times f_{1000_{(2)}}-f_{100_{(2)}}$。然后求 $1101100_{(2)}$，其中已知 $f_{1100_{(2)}}$，先求 $f_{101100_{(2)}}=f_{1100_{(2)}}\times f_{100000_{(2)}}-f_{100_{(2)}}$，再求 $f_{1101100_{(2)}}=f_{101100_{(2)}}\times f_{1000000_{(2)}}-f_{10100_{(2)}}$。你发现，它减去的 $|a-b|$ 就是 $n$ 的低位，从另一个方向来讲，这些数需要求的数是 $n$ 的一些连续低位二进制按位取反然后最低位加一得到，那么它们按位取反然后最低位加一也就能得到原来 $n$ 的连续低位二进制了。而 $n$ 低位 $f$ 值伴随记搜求得，所以总复杂度就是 $O({\log n}^2)$ 的，这里的另一个 $\log n$ 是因为一次搜索需要 $\log n$ 次枚举二进制。
# code
```cpp
#include<bits/stdc++.h>
using namespace std;
map<long long,long long>f;
int k;
long long m,n,x;
inline long long dfs(long long u){
	if(f.find(u)!=f.end())return f[u];
	long long res=0;
	for(long long i=0;i<60;i++)
		if(u>>i&1){
			if(f.find(res+(1ll<<i))==f.end())
				f[res+(1ll<<i)]=(f[res]*f[(1ll<<i)]%m-dfs((1ll<<i)-res)+m)%m;
			res+=1ll<<i;
		}
	return f[u];
}
int main(){
	scanf("%lld%d%lld",&m,&k,&n);
	f[0]=2;
	f[1]=k;
	x=2;
	while(x<=n){
		f[x]=(f[x>>1]*f[x>>1]%m-2+m)%m;
		x<<=1ll;
	}
	printf("%lld",dfs(n));
	return 0;
}
```

---

## 作者：Nuclear_Fish_cyq (赞：1)

首先看眼式子。$x+x^{-1}$，等等，这不昨天做的数学题吗？

关于这个式子的递推有一个很常用的技巧。我们考虑平方这个式子：

$$(x+x^{-1})^2=x^2+2xx^{-1}+x^{-2}=x^2+x^{-2}+2$$。

我们可以尝试把这个规律拓展一下。设 $f_i=x^i+x^{-i}$。

$$f_if_1=(x^i+x^{-i})(x+x^{-1})=x^{i+1}+x^{-(i+1)}+x^{i-1}+x^{-(i-1)}=f_{i+1}+f_{i-1}$$

$$kf_i=f_{i+1}+f_{i-1},f_{i+1}=kf_{i}-f_{i-1}$$

不对，这是什么？？？递推式，系数与 $i$ 无关，正解 $O(\log n)$？？？？

这不矩阵快速幂吗。然后问题就变成了矩阵咋推。

我们考虑矩阵 $G$，使：

$$\begin{bmatrix}
f_{i-1}  & f_{i-2}
\end{bmatrix}G=\begin{bmatrix}
f_i  & f_{i-1}
\end{bmatrix}$$

一列一列的填。第一列，我们有 $f_{i}=kf_{i-1}-f_{i-2}$，系数依次填进去，然后 $f_{i-1}$ 就是 $f_{i-1}$，不用递推：

$$G=\begin{bmatrix}
k  & 1\\
-1  & 0
\end{bmatrix}$$

然后写个矩阵快速幂。注意 $n$ 很小的情况。

代码：

```cpp
#include <bits/stdc++.h>
#define ll long long
#define db double
#define ull unsigned long long
#define inf INT_MAX
#define linf LLONG_MAX
#define ninf INT_MIN
#define nlinf LLONG_MIN
#define mod m
#define lwbd lower_bound
#define upbd upper_bound
//#define range
using namespace std;
void read(int &x){
	cin >> x;
	return;
}
void readll(ll &x){
	cin >> x;
	return;
}void readdb(db &x){
	cin >> x;
	return;
}
ll n, m, a;
struct matrix{
	ll col, row;
	ll mat[100][100];
	matrix(ll x, ll y){
		col = y;
		row = x;
		for(int i = 0; i < x; i++){
			for(int j = 0; j < y; j++){
				mat[i][j] = 0;
			}
		}
	}
	matrix operator *(matrix p){
		matrix res(row, p.col);
		for(int i = 0; i < res.row; i++){
			for(int j = 0; j < res.col; j++){
				for(int k = 0; k < col; k++){
					res.mat[i][j] += mat[i][k] * p.mat[k][j] % mod;
					res.mat[i][j] %= mod;
				}
			}
		}
		return res;
	}
	matrix operator +(matrix p){
		matrix res(row, col);
		for(int i = 0; i < res.row; i++){
			for(int j = 0; j < res.col; i++){
				res.mat[i][j] = mat[i][j] + p.mat[i][j];
				res.mat[i][j] %= mod;
			}
		}
		return res;
	}
	matrix unit(ll x){
		matrix p(x, x);
		for(int i = 0; i < x; i++){
			p.mat[i][i] = 1;
		}
		return p;
	}
};
matrix qpow(matrix p, ll q){
	if(q == 0){
		return p.unit(p.col);
	}
	if(q == 1){
		return p;
	}
	matrix res = qpow(p, q / 2);
	if(q % 2){
		return res * res * p;
	}
	return res * res;
}
//如果再忘记把题目给的1~n变为0~n-1自罚20仰卧起坐
int main(){
	std::ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> m >> a >> n;
	if(n == 0){
		cout << 2 << endl;
	}
	if(n == 1){
		cout << a % mod << endl;
	}
	if(n == 2){
		cout << (a * a - 2) % mod << endl;
	}
	if(n < 3){
		return 0;
	}
	matrix p(2, 2), q(1, 2);
	q.mat[0][0] = (a * a - 2) % mod;
	q.mat[0][1] = a;
	p.mat[0][0] = a;
	p.mat[0][1] = 1;
	p.mat[1][0] = m - 1;
	matrix ans = q * qpow(p, n - 2);
	cout << ans.mat[0][0] << endl;
	return 0;
}


```

---

## 作者：coderJerry (赞：1)

- 令 $f(n)=x^n+x^{-n}$，考虑 $f(a)f(b)=(x^a+x^{-a})(x^b+x^{-b})=(x^{a+b}+x^{-a-b})+(x^{a-b}+x^{b-a})=f(a+b)+f(a-b)$。取 $b=1$ 代入，便有 $\red{f(n+1)=kf(n)-f(n-1)}$。

- 考虑到 $n≤10^{18}$，我们使用矩阵加速递推。确定初始矩阵：

$$\begin{bmatrix} f(1) \\ f(0)\end{bmatrix}  $$

- 目标矩阵：

$$\begin{bmatrix} f(n) \\ f(n-1)\end{bmatrix}  $$

- 转移时有：
  $f(n)=k\times f(n-1)+(-1)\times f(n-2),f(n-1)=1\times f(n-1)+0\times f(n-2)$。

- 转移矩阵：

$$\red{\begin{bmatrix} k & -1 \\ 1&0\end{bmatrix}}  $$

- 矩阵快速幂求解即可，复杂度 $O(n\log n)$。


```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
vector<vector<int>> a(2,vector<int>(2));
namespace matrix{
	vector<vector<int>> mul(vector<vector<int>> a,vector<vector<int>> b,int mod){
		int n=a.size();
		vector<vector<int>> ans(n,vector<int>(n,0));
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				for(int k=0;k<n;k++){
					ans[i][j]=(ans[i][j]+(a[i][k]*b[k][j])%mod)%mod;
				}
			}
		}
		return ans;
	}
    vector<vector<int>> qpow(vector<vector<int>> a,int b,int mod){
		if(b==1) return a;
		vector<vector<int>> ans=matrix::qpow(a,b/2,mod);
		ans=matrix::mul(ans,ans,mod);
		if(b%2==1) ans=matrix::mul(ans,a,mod);
		return ans;
	}
}
signed main(){
    int m,k,n;
    cin>>m>>k>>n;
    a[0][0]=k;a[0][1]=-1;
    a[1][0]=1;a[1][1]=0;
	if(n==0){cout<<2;return 0;}
	if(n==1){cout<<k;return 0;}
	else{
	    a=matrix::qpow(a,n-1,m);
	    cout<<(k*a[0][0]+2*a[0][1]+m*(k+2))%m;
	}
    return 0;
}
```

---

## 作者：zhangjiting (赞：1)

## 思路

令 $f(n)=x^n+x^{-n}$。

$f(n)f(1)=(x^n+x^{-n})(x+x^{-1})=f(n+1)+f(n-1)$

$f(n+1)=f(1)f(n)+f(n-1)$

把 $f(1)=k$ 带入得：

$f(n+1)=kf(n)+f(n-1)$

很熟悉的格式，很熟悉的数据范围，考虑矩阵快速幂。

构造出递推矩阵：

$$
\begin{bmatrix}
  k & 1 \\
  -1 & 0 \\
\end{bmatrix}
$$


原式化为：
$$
\begin{bmatrix}
  f(n-1) & f(n-2)
\end{bmatrix}

=

\begin{bmatrix}
  k & 1 \\
  -1 & 0 \\
\end{bmatrix}



\cdot

\begin{bmatrix}
  f(n) & f(n-1)
\end{bmatrix}
$$

时间复杂度 $O(\log n)$。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
#define debug(x) cout<<#x<<':'<<x<<endl
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
using namespace std;
int n,mod,k;
struct mat{
	int a[3][3];
	mat operator*(const mat &b) const{
		mat res;
		for(int i=1;i<=2;i++)
			for(int j=1;j<=2;j++)
				for(int k=1;k<=2;k++)
					res.a[i][j]=(res.a[i][j]+a[i][k]*b.a[k][j])%mod;
		return res;
	}
}ans,base;
void qpow(int b) {
	while(b){
		if(b&1) ans=ans*base;
		base=base*base;
		b>>=1;
	}
}
signed main(){
	cin>>mod>>k>>n;
	if(n==0) return cout<<2,0;
	if(n==1) return cout<<k%mod,0;
	if(n==2) return cout<<(k*k-2)%mod,0;
	base.a[1][1]=k,base.a[1][2]=1,base.a[2][1]=-1;
	ans.a[1][1]=(k*k-2)%mod,ans.a[1][2]=k%mod;
	qpow(n-2);
	cout<<(ans.a[1][1]+mod)%mod;
	return 0;
}
```

---

## 作者：细数繁星 (赞：0)

此题细节较多，注意勤取模和特判。

设数列 $F_n=x^{n}+x^{-n}$，有 $F_1=k$，$F_2=F_1^2-2=k^2-2$。可以想到：$x^n+x^{-n}=(x^{n-1}+x^{-(n-1)})(x+x^{-1})-(x^{n-2}+x^{-(n-2)})$。即：$F_n=kF_{n-1}-F_{n-2}$

但 $n\le 10^{18}$，递推会 T 飞。所以考虑矩阵快速幂。

给不了解的同学们介绍一下矩阵这个东西：

其相当于一个二维数组，一个 $n$ 行 $m$ 列的矩阵表示为 $A_{n\times m}$。矩阵有乘法，**其不满足交换律**，但满足结合律。只有矩阵 $A_{n\times m}$ 和 $B_{m\times s}$ 可以相乘，积为 $C_{n\times s}$：

$$
C_{i,j}=\sum_{k=1}^mA_{i,k}B_{k,j}
$$

接下来我们设一个矩阵 $\begin{bmatrix}F_{n-1}&F_{n-2}\end{bmatrix}$，根据矩阵乘法的定义可以想到：

$$
\begin{bmatrix}F_{n-1}&F_{n-2}\end{bmatrix}\times\begin{bmatrix}k&1\\-1&0\end{bmatrix}=\begin{bmatrix}F_n&F_{n-1}\end{bmatrix}
$$
正确性显然。

设后面的 $2\times 2$ 矩阵为 $Z$，有 $\begin{bmatrix}F_2&F_{1}\end{bmatrix}Z^{n-2}=\begin{bmatrix}F_n&F_{n-1}\end{bmatrix}$。由于矩阵乘法满足结合律，可以使用快速幂。

但是 $Z$ 有 $-1$ 项，答案需要取模，**注意考虑取模后为负数的情况**，可以先加上模数再去取模以避免此情况。

$0\le n\le2$ 时无法输出预期结果，注意特判。

代码：

```cpp
#include <bits/stdc++.h>
#define rty printf("Yes\n");
#define RTY printf("YES\n");
#define rtn printf("No\n");
#define RTN printf("NO\n");
#define rep(v,b,e) for(int v=b;v<=e;v++)
#define repq(v,b,e) for(int v=b;v<e;v++)
#define rrep(v,e,b) for(int v=b;v>=e;v--)
#define rrepq(v,e,b) for(int v=b;v>e;v--)
#define stg string
#define vct vector
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

void solve() {
	
}

ll mod, k, n;
struct Matrix {
    ll mat[3][3];
    Matrix() {
        memset(mat, 0, sizeof mat);
    }
    Matrix operator * (const Matrix b) {
        Matrix ans;
        rep(i, 1, 2) {
            rep(j, 1, 2) {
                rep(k, 1, 2) {
                    ans.mat[i][j] += mat[i][k] * b.mat[k][j] % mod;
                    ans.mat[i][j] += mod;
                    ans.mat[i][j] %= mod;
                }
            }
        }
        return ans;
    }
}fst, dw;

Matrix qpow(Matrix a, ll b) {
    Matrix res;
    rep(i, 1, 2) res.mat[i][i] = 1;
    while (b) {
        if (b & 1) res =  res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}

main() {
//	intt; cin >> t; while (t--) solve();
    cin >> mod >> k >> n;
    k %= mod;
    if (n == 0) { cout << 2; return 0; }
    else if (n == 1) { cout << k; return 0; }
    else if (n == 2) { cout << (k * k - 2) % mod; return 0; }
    fst.mat[1][1] = (k * k - 2) % mod;
    fst.mat[1][2] = k; 
    dw.mat[1][1] = k;
    dw.mat[1][2] = 1;
    dw.mat[2][1] = -1;
    fst = fst * qpow(dw, n - 2);
    cout << fst.mat[1][1];
	return 0;
}
```

---

## 作者：copper_ingot (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P9777)

用矩阵加速 DP 做。

下文设 $f_n=x^n+x^{-n}$。

首先我们写一个式子。

$$(x^{n-1}+x^{-n+1})(x+x^{-1})=x^n+x^{-n+2}+x^{n-2}+x^{-n}$$

所以

$$k\times f_{n-1}-f_{n-2}=f_n$$

于是我们可以得到矩阵递推式：

$$\begin{bmatrix} f_{n-1} & f_{n-2} \end{bmatrix}\times\begin{bmatrix} k & 1 \\ -1 & 0 \end{bmatrix}=\begin{bmatrix} f_n & f_{n-1} \end{bmatrix}$$

初始矩阵：

$$\begin{bmatrix} k & 2 \end{bmatrix}$$

注意特判 $n=0$ 的情况输出 $2$，否则会 TLE #4。

代码：


```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int mod;
const int siz = 2;
struct matrix{int a[siz][siz];}base, ans;
matrix times(matrix x, matrix y){//矩阵乘法
    matrix z;
    memset(z.a, 0, sizeof(z.a));
    for (int i = 0; i < siz; i++)
        for (int j = 0; j < siz; j++)
            for (int k = 0; k < siz; k++)
                z.a[i][j] = (z.a[i][j] + x.a[i][k] * y.a[k][j] % mod) % mod;
    return z;
}
matrix fpow(matrix aa, int b){//快速幂
    matrix ans;
    memset(ans.a, 0, sizeof(ans.a));
    for (int i = 0; i < siz; i++) ans.a[i][i] = 1;
    while (b){
        if (b & 1) ans = times(ans, aa);
        aa = times(aa, aa); b >>= 1;
    }
    return ans;
}
int n, k;
signed main(){
	scanf("%lld%lld%lld", &mod, &k, &n);
	if (n == 0){puts("2"); return 0;}//记得特判
    base.a[0][0] = k, base.a[0][1] = 1, base.a[1][0] = -1;
    ans.a[0][0] = k, ans.a[0][1] = 2;//初始化
	ans = times(ans, fpow(base, n - 1));
    printf("%lld\n", (ans.a[0][0] + mod) % mod);//最终计算结果可能小于0，不取正数会WA#5
    return 0;
}
```

---

## 作者：_February20th_ (赞：0)

## 题目分析

已知方程：$x + x^{-1} = k$，要求计算 $x^n + x^{-n}$ 对 $M$ 取模的值。

## 解题思路

定义：
$a_n = x^n + x^{-n}$。

从题意和已知条件 $x + x^{-1} = k$ 出发，可以推导出以下递推关系：
$a_{n+1} = k \cdot a_n - a_{n-1}$。

#### 初始条件：

- $a_0 = 2$（因为 $x^0 + x^{-0} = 2$）
- $a_1 = k$（因为 $x + x^{-1} = k$）

将递推式转化为矩阵形式，使得我们可以利用矩阵快速幂快速计算任意 $n$ 时的 $a_n$ 值。

将递推式转换为矩阵乘法形式：
$$
\begin{bmatrix} a_{n+1} \\ a_n \end{bmatrix} = \begin{bmatrix} k & -1 \\ 1 & 0 \end{bmatrix} \times \begin{bmatrix} a_n \\ a_{n-1} \end{bmatrix}
$$

这样，我们就可以通过矩阵幂快速计算出任意 $n$ 时的 $a_n$ 值。

通过矩阵快速幂方法，我们可以快速求出矩阵：
$$
\begin{bmatrix} k & -1 \\ 1 & 0 \end{bmatrix}
$$
的 $n-1$ 次幂，并作用在初始向量 $\begin{bmatrix} k \\ 2 \end{bmatrix}$ 上，从而得到 $a_n$ 的值。

## 代码
```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

using Matrix = vector<vector<int>>;

int M;

Matrix matrix_mul(const Matrix &a, const Matrix &b) {
    int n = a.size();
    Matrix c(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % M;
            }
        }
    }
    return c;
}

Matrix matrix_pow(Matrix base, int exp) {
    int n = base.size();
    Matrix res(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        res[i][i] = 1;
    }
    while (exp > 0) {
        if (exp % 2 == 1) {
            res = matrix_mul(res, base);
        }
        base = matrix_mul(base, base);
        exp /= 2;
    }
    return res;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int k, n;
    cin >> M >> k >> n;
    if (n == 0) {
        cout << 2 % M << '\n';
        return 0;
    }
    Matrix base = {{k, M - 1}, {1, 0}};
    Matrix res = matrix_pow(base, n - 1);
    int a_n = (res[0][0] * k % M + res[0][1] * 2 % M) % M;
    cout << a_n << '\n';
    return 0;
}
```

---

## 作者：RainDuckling (赞：0)

# Description
 已知 $x+x^{-1}=k$ ，求 $x^n+x^{-n}$对 $M$ 取模的结果。
# Solution

我们从已知入手：

+ 当 $n=2$ 时，我们发现，$x^2$ 和 $x^{-2}$ 都可以由已知的 $x+x^{-1}$ 求得：

$x^2=(x+x^{-1}) \times x-1
=(x+x^{-1}) \times x-1$

$x^{-2}=(x+x^{-1}) \times x^{-1}-1
=(x+x^{-1}) \times x^{-1}-1$


两式相加，得到：


$x^2+x^{-2}=(x+x^{-1}) \times (x+x^{-1})-2$

（这里我们之所以不套用完全平方公式，是因为方便 $n$ 较大时，仍能以此类推）

+ 当 $n=3$ 时，因为 $(x^2+x^{-2})$ 此时为已知量，所以考虑如何由其求得 $(x^3+x^{-3})$：

$x^3=(x^2+x^{-2}) \times x-x^{-1} $

$x^{-3}=(x^2+x^{-2}) \times x^{-1}-x$

两式相加，得到：

$x^3+x^{-3}=(x+x^{-1}) \times (x^2+x^{-2})-(x+x^{-1}) $

+ 当 $n=4$ 时，同理：

$x^4+x^{-4}=(x+x^{-1}) \times (x^3+x^{-3})-(x^2+x^{-2}) $

经过几轮的试验，我们可以大胆的猜想：

对于所有的整数 $n \ge 2$ ，令 $f(n)=x^n+x^{-n}$ ，则：

$f(n)=(x+x^{-1}) \times f(n-1)-f(n-2)$

将 $x+x^{-1}=k$ 带入:

$f(n)=k \cdot f(n-1)-f(n-2)$

对于这个式子，用简单的递推法显然会超时，考虑矩阵加速。

我们希望将：

$$
\begin{bmatrix} f(n-1) \\ f(n-2) \end{bmatrix}
$$

转移为：

$$
\begin{bmatrix} f(n) \\ f(n-1) \end{bmatrix}
$$

于是构造转移矩阵为：
$$
\begin{bmatrix} k & -1 \\ 1 & 0 \end{bmatrix}
$$

即：

$$
\begin{bmatrix} f(n) \\ f(n-1) \end{bmatrix}
=
\begin{bmatrix} k & -1 \\ 1 & 0 \end{bmatrix}
\times
\begin{bmatrix} f(n-1) \\ f(n-2) \end{bmatrix}
$$

而初始矩阵为：

$$
\begin{bmatrix} f(1)\\ f(0) \end{bmatrix}

$$

这是一个很通用的方法，用于求满足下类数列的某一项：

$f(n)=a_1\cdot f(n-1)+a_2\cdot f(n-2)+a_3\cdot f(n-3)+ ... +a_k\cdot f(n-k)$

也可以用矩阵加速以 $O(k^3\log(n))$ 的时间复杂度求出每一项。 

以这样的规律形成的数列，我们称其满足**常系数齐次线性递推**。

# Code
```cpp
#include <bits/stdc++.h>
#define rep(a, b, c) for (ll a = b; a <= c; ++a)
using namespace std;
typedef long long ll;

const ll N = 107;
ll M,k,n;

class Matrix{
    public:
        ll n,m;
        ll mat[N][N];
        Matrix(){
            memset(mat,0,sizeof(mat));
        }
        Matrix(ll _n,ll _m){
            n = _n,m = _m;
            memset(mat,0,sizeof(mat));
        }
        void init(){
            memset(mat,0,sizeof(mat));
            rep(i,1,n)
                mat[i][i] = 1;
        }
}base(2,2),ans(2,1);

Matrix operator*(const Matrix& a, const Matrix& b){
    ll n = a.n, m = b.m, k = a.m;
    Matrix ans(n,m);
    rep(i,1,n){
        rep(j,1,m){
            rep(x,1,k){
                ans.mat[i][j] = (ans.mat[i][j] + a.mat[i][x] * b.mat[x][j]) % M;
                ans.mat[i][j] = (ans.mat[i][j] + M) % M;
            }
        }
    }
    return ans;
}

void init(){
    /*
    base:
    k -1
    1 0
    */
    memset(base.mat,0,sizeof(base.mat));
    memset(ans.mat,0,sizeof(ans.mat));
    base.mat[1][1] = k;
    base.mat[1][2] = -1;
    base.mat[2][1] = 1;
    ans.mat[1][1] = k;
    ans.mat[2][1] = 2;
}

void qpow(ll K){
    while(K){
        if(K & 1)ans = base * ans;
        base = base * base;
        K >>= 1;
    }
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> M >> k >> n;
    if(n == 0){//注意特判边界条件
        puts("2\n");
        return 0;
    }
    if(n == 1){
        cout << k <<'\n';
        return 0;
    }
    init();
    qpow(n - 1);
    cout << (ans.mat[1][1] + M) % M<< '\n';
    return 0;
}
``

---

## 作者：zk_y (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P9777)

我们先看 $n$ 的范围，$0\le n\le 10^{18}$。

我们定义一个函数 $f(n)=x^n+x^{-n}$ 来帮助我们更好的理解问题。

我们从小到大考虑：

当 $n=0$ 时，$f(0)=x^0+x^0=2$。

当 $n=1$ 时，$f(1)=x^1+x^{-1}=k$。

我们接下来思考如何处理 $n>1$ 的情况。

我们想要凑出 $f(n)=x^n+x^{-n}$，我们发现 $(x^{n-1}+x^{-(n-1)})*(x^1+x^{-1})=f(n)+x^{n-2}+x^{-(n-2)}$。

我们惊奇地发现，$x^{n-2}+x^{-(n-2)}=f(n-2)$。

所以，我们移项，就可以得到：

 $$f(n)=f(n-1)*f(1)-f(n-2)$$

鉴于 $n$ 的范围较大，于是使用矩阵快速幂求解即可。

## AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
//f(n)=k*f(n-1)-f(n-2)
#define ll long long
const int N=10;
struct node{
	ll num[N][N];
}x;
ll mod,k,n;
void mem(node &x){
	memset(x.num,0,sizeof(x.num));
	x.num[1][1]=k;
	x.num[1][2]=1;
	x.num[2][1]=-1;
}
node operator *(const node &x,const node &y){
	node z;
	memset(z.num,0,sizeof(z.num));
	for(int k=1;k<=2;k++){
		for(int i=1;i<=2;i++){
			for(int j=1;j<=2;j++){
				z.num[i][j]=(z.num[i][j]+x.num[i][k]*y.num[k][j]%mod)%mod;
			}
		}
	}
	return z;
}
void qpow(ll a){
	node ans;
	memset(ans.num,0,sizeof(ans.num));
  	ans.num[1][1]=(k*k-2)%mod;
  	ans.num[1][2]=k%mod;
	mem(x);
	while(a){
		if(a&1)ans=ans*x;
		x=x*x;
		a>>=1;
	}
	printf("%lld",(ans.num[1][1]+mod)%mod);
}
int main(){
	scanf("%lld %lld %lld",&mod,&k,&n);
	if(n==0){
		printf("2");
		return 0;
	}
	if(n==1){
		printf("%lld",k%mod);
		return 0;
	}
	qpow(n-2);
	return 0;
}
```


---

## 作者：封禁用户 (赞：0)

令 $f(n)=x^{n}+x^{-n}$。

可以发现 $f(n)f(m)=x^{n-m}+x^{m-n}+x^{n+m}+x^{-n-m}=f(n-m)+f(m+n)$。

若 $m=1$ 可得 $f(1)f(n)=k\cdot f(n)=f(n-1)f(n+1)$。

取得这个式子后，用递归矩阵加速即可。

---

