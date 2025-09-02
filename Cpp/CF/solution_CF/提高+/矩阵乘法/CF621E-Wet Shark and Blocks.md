# Wet Shark and Blocks

## 题目描述

有 $b$ 个格子，每个格子有 $n$ 个数字，各个格子里面的数字都是相同的. 求从 $b$ 个格子中各取一个数字, 构成一个 $b$ 位数, 使得这个 $b$ 位数模 $x$ 为 $k$ 的方案数（同一格子内相同的数字算不同方案）.答案对 $1\times 10^9+7$ 取模.

## 样例 #1

### 输入

```
12 1 5 10
3 5 6 7 8 9 5 1 1 1 1 5
```

### 输出

```
3
```

## 样例 #2

### 输入

```
3 2 1 2
6 2 2
```

### 输出

```
0
```

## 样例 #3

### 输入

```
3 2 1 2
3 1 2
```

### 输出

```
6
```

# 题解

## 作者：ChinaNB (赞：10)

首先，一个dp应该是显然的。

$dp[i][j]$ 表示选到第 $i$ 个格子，余数是 $j$ 的方案数，枚举取数 $l$，得到

$$dp[i+1][(10j+a_{l})\bmod x]\text{ += }dp[i][j]$$

可以发现对于每一个 $dp[i]$，转移都是类似的。

然后我们考虑用矩阵快速幂优化转移。

初始状态 $dp[0]$ 是
$$\begin{bmatrix}1\\0\\\vdots\\0\end{bmatrix}$$

然后对于每个数 $v$，我们修改转移矩阵$A$
$$A\left[j\right]\left[\left(10j+v\right)\bmod x\right]\text{ += }1$$
然后最终答案就是 $A^b\times dp[0]$ 的第 $k$ 行了。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
ll n, b, k, x;
const ll P = 1000000007;
struct Matrix {
	ll a[105][105];
};

Matrix A, I;

inline ll read() {
	ll x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
inline Matrix MatrixMul(const Matrix &A, const Matrix &B) {
	Matrix ret;
	for (int i=0; i<x; i++)
		for (int j=0; j<x; j++) {
			ret.a[i][j] = 0;
			for (int k=0; k<x; k++)
				(ret.a[i][j] += A.a[i][k] * B.a[k][j] % P) %= P;
		}
	return ret;
}
inline Matrix Pow(ll k){
	Matrix ans = I;
	for (; k; k>>=1, A=MatrixMul(A, A)) if (k&1) ans = MatrixMul(ans, A);
	return ans;	
}

int main() {
	n = read(); b = read(); k = read(); x = read();
	for (int i=0; i<x; i++) I.a[i][i] = 1;
	for (int i=0; i<n; i++) {
		ll val = read();
		for (int j=0; j<x; j++)
			++A.a[j][(j*10%x+val%x)%x];
	}
	Matrix ret = Pow(b);
	cout << ret.a[0][k] << endl;
	return 0;
}

```

---

## 作者：Grisses (赞：4)

[题面](https://www.luogu.com.cn/problem/CF621E)

有 $b$ 个格子，每个格子有 $n$ 个数字，各个格子里面的数字都是相同的. 求从 $b$ 个格子中各取一个数字,构成一个 $b$ 位数，使得这个 $b$ 位数模 $x$ 为 $k$ 的方案数（同一格子内相同的数字算不同方案）。

我们设 $dp_{i,j}$ 表示前 $i$ 个格子中取数后，模 $x$ 的结果为 $j$ 的方案数。

递推式也容易推出来：$dp_{i,(j\times10+a_k)\bmod x}=\sum dp_{i-1,j}$。

但是，这样显然会 TLE。所以我们需要一些优化。

对于每一个 $i=\overline{1,2,\cdots,b}$，我们可以把 $dp_{i,j},j=\overline{0,1,\cdots,x-1}$ 当做一个状态。然后根据所给的 $a$ 进行转移。然后用矩阵快速幂优化即可。

对于矩阵快速幂，这是一种好用的优化递推的算法。

首先，定义矩阵乘法：

对于一个 $n\times k$ 的矩阵 $A$ 和一个 $k\times m$ 的矩阵 $B$ 还有一个矩阵 $C=A\times B$。那么 $C$ 是一个 $n\times m$ 的矩阵，且 $C_{ij}=\sum\limits_{p=1}^kA_{i,p}\times B_{p,j}(i=\overline{1,2,\cdots,n},j=\overline{1,2,\cdots,m})$。

然后，因为矩阵乘法满足结合律，所以我们有了矩阵快速幂。矩阵快速幂的话就是把快速幂的板子套在矩阵上而已。

代码：
```cpp
  #include<bits/stdc++.h>
  #define int long long 
  using namespace std;
  const int mod=1e9+7;
  int n,b,x,k,a[50005];
  struct M{
      int a[100][100];//矩阵
      M operator*(M t){//乘
          M res;
          for(int i=0;i<x;i++)for(int j=0;j<x;j++)res.a[i][j]=0;
          for(int i=0;i<x;i++){
              for(int j=0;j<x;j++){
                  for(int k=0;k<x;k++){
                      res.a[i][j]=(res.a[i][j]+a[i][k]*t.a[k][j]%mod)%mod;
                  }
              }
          }
          return res;
      }
      M operator^(int k){//快速幂
          M res,_=*this;
          for(int i=0;i<x;i++)for(int j=0;j<x;j++)res.a[i][j]=(i==j);
          while(k){
              if(k&1)res=res*_;
              _=_*_;
              k>>=1;
          }
          return res;
      }
  }ans,base;
  signed main()
  {
      scanf("%lld%lld%lld%lld",&n,&b,&k,&x);
      for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
      for(int i=0;i<x;i++)for(int j=0;j<x;j++)ans.a[i][j]=0;
      for(int i=0;i<x;i++)for(int j=0;j<x;j++)base.a[i][j]=0;
      ans.a[0][0]=1;
      for(int i=0;i<x;i++){
          for(int j=1;j<=n;j++){
              base.a[(i*10+a[j])%x][i]++;//求出转移式
          }
      }
      ans=(base^(b))*ans;//推！
      printf("%lld",ans.a[k][0]);
      return 0;
  }
```

---

## 作者：aiyougege (赞：3)

#### Solution
　　还是第一次做矩阵乘法优化动态规划的题,如有不妥之处请多多指教.关于矩阵乘法更基础的内容可以看[矩阵乘法](https://www.luogu.org/blog/aiyoupass/ju-zhen-sheng-fa).
  
　　容易写出转移方程

$$f(i,j)=\sum_{p=0}^9tot(p)f(i-1,(j-p)/10\mod k)$$

可以发现每次从$i-1$到$i$的转移是一样的, 这么一次转移可以表示成一次矩阵乘法的形式.

　　其中$f(i,j)$表示前i个格子构成数模$k$为$j$的方案数, 将$tot(p)$放入矩阵中构造出一个矩阵$A$,**第i行第j列为相邻两个格子前一个余数为$i$时的答案对后一个余数为$j$时答案的贡献**(相当于是$f(a,i)+=A_{i,j}\times f(a-1,j)$),$f(a,i)+=A_{i,j}^2\times f(a-2,j)$可以表示第零个格子(没有格子)的答案对前两个格子答案的贡献, 最终为$f(b,i)+=A_{i,j}^b\times f(a-2,j)$.
这样就使得转移变成了$f(i)=Af(i-1)$.这样就可以最终利用**矩阵快速幂**求出最终的矩阵, $A^b$矩阵的第一行的第$k$个数就是答案.

　　如果感觉比较抽象的话就将所有转移全部写出来, 会发现它刚好可以写成一个矩阵乘法的形式,也可以多看看**线代**的书.

#### Code
```c++
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define N 105
#define mod 1000000007
#define int long long
using namespace std;

class matrix {//矩阵的类
    public:
    int n,m,mat[N][N];
    matrix(){}
    matrix(int _n){n=m=_n;for(int i=0;i<_n;++i)mat[i][i]=1;}
    matrix(int _n,int _m){n=_n,m=_m;}
    matrix operator+(const matrix &b)const{
        matrix c=matrix(n,m);
        for(int i=0;i<n;++i)
            for(int j=0;j<m;++j)
                c.mat[i][j]=(mat[i][j]+b.mat[i][j])%mod;
        return c;	
    }
    matrix operator-(const matrix &b)const{
        matrix c=matrix(n,m);
        for(int i=0;i<n;++i)
            for(int j=0;j<m;++j)
                c.mat[i][j]=(mat[i][j]-b.mat[i][j])%mod;
        return c;
    }
    matrix operator*(const matrix &b)const{
        matrix c=matrix(n,b.m);
        for(int i=0;i<n;++i)
            for(int j=0;j<b.m;++j){
                long long tmp=0LL;
                for(int k=0;k<m;++k){
                    tmp+=mat[i][k]*b.mat[k][j];
                    if(tmp>1e9)tmp%=mod;
                }
                c.mat[i][j]=tmp;
            }
        return c;
    }
    matrix operator*(const int &s)const{
        matrix c=*this;
        for(int i=0;i<n;++i)
            for(int j=0;j<m;++j){
                c.mat[i][j]*=s;
                c.mat[i][j]%=mod;
            }
    }
    matrix operator^(const int &s)const{
        int p=s;
        matrix ans=matrix(n);
        matrix bas=*this;
        while(p){
            if(p&1)ans=ans*bas;
            bas=bas*bas;p>>=1;
        }
        return ans;
    }
    void input(int _n,int _m){
        n=_n,m=_m;
        for(int i=0;i<n;++i)
            for(int j=0;j<m;++j)
                scanf("%lld",&mat[i][j]);
    }
    void print(){
        putchar('\n');
        for(int i=0;i<n;++i){
            for(int j=0;j<m;++j)
                printf("%lld ",mat[i][j]);
            putchar('\n');
        }
        putchar('\n');
    }
}A;//即上文中的A

int n,b,k,x;
int cnt[10];//每个格子中数i的个数

main(){
 	scanf("%lld%lld%lld%lld",&n,&b,&k,&x);
    memset(cnt,0,sizeof(cnt));int v;
    for(int i=1;i<=n;i++){
        scanf("%d",&v);cnt[v]++;
    }
    A=matrix(x,x);//初始化矩阵
    for(int i=0; i<x; i++){
        for(int j=0; j<10; j++){
            A.mat[i][(i*10+j)%x]+=cnt[j];
        }
    }//构造矩阵A
    matrix ans=A^b;//b个格子的答案
    printf("%lld\n",ans.mat[0][k]%mod);
    return 0;
}
```

---

## 作者：徐晨熠 (赞：2)

+ 我们先看数据范围 $b$ 有 $10^9$ ,很大。看了题目，我们知道题目的时间复杂度必定与 $b$ 有关，自然而然往 $\log b$ 方向想。值得庆幸的是 $x$ 在 $100$ 之内。若用常规 dp ，时间复杂度为 $\Theta(b\times x^2)$ ，显然不行。但，使用矩阵乘法加速，时间复杂度变为$\Theta(\log b\times x^3)$ ，可用。
+ 根据题目性质，我们发现只有相邻的格之间存在关系，即只有到上一格的余数会影响这一格。例如：到上一格的余数为 $i$ ，这格的数字为$j$，这格的余数为$(i\times10+j)\bmod x$(即余数由 $i$ 变为 $(i\times10+j) \bmod x$ 的方案数 $+1$ )。
+ 凭借这个关系，构造矩阵。  
  
具体细节，请看代码。(已经可以$AC$了)
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair<int,int> PII;
const LL N=105,mod=1e9+7;
LL a[N][N];//a[i][j]中,i为余数,j为余数,a[i][j]的值为余数从i变为j的方案数 
LL ans[N];//ans[i]中,i为余数,ans[i]的值为形成余数i的方案数 
LL n,b,k,x,sz;
void mul()
{
	LL c[N];
	memset(c,0,sizeof c);
	for(int i=0;i<x;i++)
	{
		//对于现在形成余数i的方案数为:余数从j变为i的方案数乘以之前形成余数j的方案数之和 
		for(int j=0;j<x;j++)
		{
			c[i]=(c[i]+ans[j]*a[j][i])%mod;
		}
	}
	//用现在的替换之前的 
	memcpy(ans,c,sizeof ans);
}
void mulself()
{
	LL c[N][N];
	memset(c,0,sizeof c);
	//对于现在余数从i变为j的方案数为:余数从i变为k的方案数乘以余数从k变为j的方案数之和
	//(神似floyd) 
	for(int i=0;i<x;i++)
	{
		for(int j=0;j<x;j++)
		{
			for(int k=0;k<x;k++)
			{
				c[i][j]=(c[i][j]+a[i][k]*a[k][j])%mod;
			}
		}
	}
	memcpy(a,c,sizeof a);
}
int main()
{
    scanf("%lld%lld%lld%lld",&n,&b,&k,&x);
    ans[0]=1;//一开始,显然只有余数是0的一种方案 
    for(int i=0;i<n;i++)
    {
    	scanf("%lld",&sz);//sz 数字(shu zi)
    	for(int j=0;j<x;j++)
    	{
    		a[j][(10*j+sz)%x]++;//余数j与数字sz搭配可形成余数(10*j+sz)%x
		}
	}
	//矩阵乘法加速递推(类似快速幂)
	while(b)
	{
		if(b&1) mul();
		mulself();
		b>>=1;
	}
	//输出 
	printf("%lld\n",ans[k]);
    return 0;
}
```
进一步思考，不难想到时间复杂度为$\Theta(\log b\times x^2)$的方法(理解起来比较难，可以不看，上面的方法已经可以过了)
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair<int,int> PII;
LL a[105];//余数为i，有a[i]种方案 
LL b[105];//在数字有p位时,余数为i，有b[i]种方案 
LL c[105];//用于暂时储存 
LL mod=1e9+7;//用于取模 
LL n,B,k,x,y,z;
LL p; 
void mulself()
{
	for(int i=0;i<x;i++) c[i]=0;
	//数字有p*2位时,余数为(i*y+j)%x[(i*10^p+j)%x=(i*10^p%x+j)%x=(i*y+j)%x]的方案数累加当数字有p位时,余数为i的方案数与余数为j的方案数之积 
	for(int i=0;i<x;i++)
		for(int j=0;j<x;j++)
			c[(i*y+j)%x]=(c[(i*y+j)%x]+b[i]*b[j])%mod;
	memcpy(b,c,sizeof b);
}
void mul()
{
	for(int i=0;i<x;i++) c[i]=0;
	//根据上面mulself()的解释,很容易想 
	for(int i=0;i<x;i++)
		for(int j=0;j<x;j++)
			c[(i*y+j)%x]=(c[(i*y+j)%x]+a[i]*b[j])%mod;
	memcpy(a,c,sizeof a);
}
int main()
{
	scanf("%d%d%d%d",&n,&B,&k,&x);
	for(int i=1;i<=n;i++) scanf("%d",&z),b[z%x]++;
	p=1;
	y=10;//y=10^p%x
	a[0]=1;
	while(B)
	{
		if(B&1) mul();
		mulself();
		p>>=1;
		y=y*y%x;//y=10^p%x
		B>>=1;
	}
	printf("%d",a[k]);
}

```


---

## 作者：hgzxwzf (赞：1)

设 $dp_{i,j}$ 表示从高到低填了前 $i$ 位，当前数模 $x$ 等于 $j$，枚举当前位选哪个数，设 $w=(10\times j+a_h)\bmod x$，假设选 $a_h$，$dp_{i,w}=dp_{i,w}+dp_{i-1,j}$，时间复杂度 $O(nbx)$，大得恐怖。

发现每一次从 $i-1$ 转移到 $i$ 一模一样，即 $j$ 向 $(10\times j+a_h)\bmod x$ 转移，考虑矩阵优化。

设 $x\times x$ 的矩阵 $st$，对于每个 $(j,h)$，我们把 $st_{w,j}$ 加 $1$。

再设 $1\times n$ 的矩阵 $s$，其中 $s$ 的第 $j$ 列表示 $dp_{i-1,j}$，我们发现用 $st$ 矩阵乘上这个矩阵得到的新矩阵 $s\prime$ 的第 $j$ 列就表示 $dp_{i,j}$，所以就可以进行矩阵快速幂优化。

总时间复杂度为 $O(nx+x^2\log_2b)$。

```cpp
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<stack>
#include<vector>
#include<queue>
#include<cstring>

#define rep(x,y,z) for(int x=y;x<=z;x++)
#define per(x,y,z) for(int x=z;x>=y;x--)
#define LL long long

using namespace std;
const int N=5e4+10,K=110,mod=1e9+7;

int a[N],n,b,k,m;
int cnt[N];

struct matrix
{
	int jz[K][K];
	matrix() {memset(jz,0,sizeof(jz));}
	matrix operator * (const matrix &b) const
	{
		matrix c;
		rep(i,0,m-1)
			rep(j,0,m-1)
				rep(h,0,m-1)
					c.jz[i][j]=(c.jz[i][j]+1ll*jz[i][h]*b.jz[h][j]%mod)%mod;
		return c;
	}
};

matrix ksm(matrix x,int y)
{
	matrix s;
	rep(i,0,m-1) s.jz[i][i]=1;
	while(y)
	{
		if(y&1) s=s*x;
		x=x*x;
		y>>=1;
	}
	return s;
}

int main()
{
	scanf("%d%d%d%d",&n,&b,&k,&m);
	rep(i,1,n) scanf("%d",&a[i]);
	matrix st;
	rep(i,0,m-1)
		rep(j,1,n)
			st.jz[(10*i+a[j])%m][i]++;
	st=ksm(st,b-1);
	int ans=0;
	rep(i,1,n) cnt[a[i]%m]++;
	rep(i,0,m-1) ans=(ans+1ll*st.jz[k][i]*cnt[i]%mod)%mod;
	printf("%d",ans);
	return 0;
}
```


---

## 作者：Kingna (赞：0)

定义 $f[i][j]$ 表示第 $i$ 个格子，构成的数模 $m$ 为 $j$ 的方案数。

转移为：$f[i+1][(j\times 10+k)\bmod m] ← f[i][j]$。

因为 $i$ 这一维有 $10^9$ 个，考虑矩阵加速。定义矩阵 $[a_0,a_1,\dots,a_{m-1}]$ 表示当前 $f[i]$ 这一维的状态。考虑如何转移到 $f[i+1]$。

我们对于每一个 $j∈[0,m-1]$，修改转移矩阵 $A[j][(j\times 10+k)\bmod m]$ 加一即可。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define PII pair<int, int>
#define _for(i, a, b) for (int i = (a); i <= (b); i++)
#define _pfor(i, a, b) for (int i = (a); i >= (b); i--)
#define int long long
const int N = 3e5 + 5, mod = 1e9 + 7;

int n, b, k, x, a[N];
int nw[105][105], res[105][105], base[105][105]; 

void mul(auto &a, auto &b, auto &c) {
	_for(i, 0, x - 1) _for(j, 0, x - 1) nw[i][j] = 0;
	_for(i, 0, x - 1) {
		_for(j, 0, x - 1) {
			_for(k, 0, x - 1) {
				nw[i][j] = (nw[i][j] + b[i][k] * c[k][j] % mod + mod) % mod;
			}
		}
	}
	_for(i, 0, x - 1) _for(j, 0, x - 1) a[i][j] = nw[i][j];
}

signed main() {
	cin >> n >> b >> k >> x;
	_for(i, 1, n) cin >> a[i];
	_for(i, 0, x - 1) res[i][i] = 1;
	_for(i, 0, x - 1) {
		_for(j, 1, n) {
			base[i][(i * 10 + a[j]) % x]++;
		}
	}
	while (b) {
		if (b & 1) mul(res, res, base);
		mul(base, base, base);
		b >>= 1;
	}
	cout << res[0][k] << endl;
}
```

---

## 作者：WaterSky (赞：0)

# [CF621E Wet Shark and Blocks.](https://www.luogu.com.cn/problem/CF621E)
## 碎碎念
因为被抓去讲题让我知道了我在台上会忘掉所有东西，并且这题我没有理解透，所以我就写细一点。

因为我们亲爱的 RMJ 还没有修好，所以暂时在洛谷没法显示 AC 记录，但是我在 CF 上已经通过，请放心食用。
## 正文
### 题意
在 $n$ 个数中可重复地选择 $b$ 个数组成一个 $b$ 位数 $v$，求使 $v\bmod{x}=k$ 的方案数。
### 做法
考虑 DP。

设状态：$f_{i,j}$ 表示选择了 $i$ 个数后被 $x$ 取模后为 $j$ 的方案数。

得状态转移方程为：
$$dp_{i,(10j+a_k)}\equiv\sum f_{i−1,j}\pmod x$$
可是因为数据过大，导致时间复杂度爆炸。

故使用矩阵加速 DP。

设初始矩阵 $A$ 为：
$$\begin{bmatrix}
1  \\
0 \\
\vdots \\
0
\end{bmatrix}$$
再设矩阵 $B$，使：
$$\forall j(0\le j<x)B(j,10j+a_i)$$
等于 $1$。
最终答案即：$A\times B^b$ 的第 $k$ 行。
### Copy
```
#include <bits/stdc++.h>
using namespace std;
const long long Mod=1e9+7;
long long n,b,k,x,v;
struct Matrix{
	long long n,m,a[105][105];
	Matrix(long long x,long long y,bool bj){
		//定义矩阵流程。 
		n=x,m=y,memset(a,0,sizeof(a));
		for(int i=1;i<=n&&bj;i++) a[i][i]=1;
	}
	Matrix operator*(const Matrix &A) {
		//重载运算符使矩阵支持乘法运算。 
		Matrix res(x,x,0);
		for(int i=0;i<x;i++)
			for(int j=0;j<x;j++)
				for(int k=0;k<x;k++)
					(res.a[i][j]+=a[i][k]*A.a[k][j]%Mod)%=Mod;
		return res;
	}
	long long* operator[](long long x){return a[x];}
	//重载使矩阵可以以二维数组的形式表示。 
};
Matrix Pow(Matrix B,Matrix A,long long k){
	//矩阵快速幂。 
	Matrix ans=B;
	for (;k;k>>=1,A=A*A) 
		if(k&1) ans=ans*A;
	return ans;	
}
int main() {
	cin>>n>>b>>k>>x;
	Matrix A(n,n,0),B(x,x,0);
	for(int i=0;i<x;i++) B[i][i]=1;
	for (int i=0;i<n;i++){
		cin>>v;
		for(int j=0;j<x;j++)
			A[j][(j*10+v)%x]++;
	}
	Matrix res=Pow(B,A,b);
	cout<<res[0][k];
	return 0;
}
```
感谢管理员的审核！

感谢屏幕前的你！

---

## 作者：Sky_Maths (赞：0)

## 思路
因为 $x\le 100$，发现有一种与 $x^2$ 有关的 DP 方法，即枚举左边和右边直接暴力合并。

举个例子，假如整段 $b = 7$，$1\sim 3$ 和 $4\sim 7$ 内部是一样的，每次直接切分为至多 $3$ 段即可。

定义 $f_{i, j}$ 为连续 $i$ 个格子，$val\bmod x = j$ 的方案数。

发现可以用快速幂优化，和广义矩阵乘法有点像，时间复杂度 $O(n + x^2\log b)$。

## 优化
设 $c = 10^{len}\bmod x$ 为偏移量，$f_{2i, j} = \sum\limits_{xc + y\equiv j\pmod x}f_{i, x}\cdot f_{i, y}$，可以先 $O(x)$ 将左边乘上偏移量，再用 NTT 优化做到 $O(n + x\log x\log b)$。

## 代码
没写 NTT。
```cpp
LL qpow(LL a, LL x, LL mod) {
	a %= mod;
	LL y = 1;
	while (x) {
		if (x & 1) y = y * a % mod;
		x >>= 1;
		a = a * a % mod;
	}
	return y;
}

const int mod = 1e9 + 7;
const int N = 5e4 + 9;

int n, b, k, x;

struct Array {
	int m;
	int f[100];
} e, empty, I;

Array operator *(Array lhs, Array rhs) {
	Array y(empty);
	y.m = lhs.m + rhs.m;
	LL lf = qpow(10, rhs.m, x);
	rep (i, 0, x - 1) {
		rep (j, 0, x - 1) {
			(y.f[(i * lf + j) % x] += 1LL * lhs.f[i] * rhs.f[j] % mod) %= mod;
		}
	}
	return y;
}

int main() {
	I.m = 0, I.f[0] = 1;
	read(n, b, k, x);
	e.m = 1;
	rep (i, 1, n) {
		int t; read(t);
		++e.f[t % x];
	}
	Array y(I);
	while (b) {
		if (b & 1) y = e * y;
		b >>= 1;
		e = e * e;
	}
	printf("%d\n", y.f[k]);
	return 0;
}
```

---

## 作者：亦闻楚歌起 (赞：0)

从给定 $n\leq 50000$ 个一位数中可重复选择 $b\leq 10^9$ 个组成 $b$ 位数，求有多少个对 $x$ 取模为 $k$

定义 $dp_{i,j}$ 为 $i$ 位数中对 $x$ 取模为 $j$ 的个数。然后倍增转移。

首先 $i=1$ 的时候直接统计原始数据就可以了。

然后对于 $dp_{i}$ 转移到 $dp_{2i}$ ，可以发现
$$
dp_{2i,j}=\sum_{10^ij_1+j_2=j} dp_{i,j_1}\times dp_{i,j_2}
$$
看见 $j$ 的范围，毫不犹豫直接暴力卷积（三模NTT可慢了。。。

这样时间复杂度就是 $\mathcal O(x^2\log_2b)$

```cpp
#include <cstdio>
#include <cstring>
#ifndef ONLINE_JUDGE
#define FILEIO
#endif // ONLINE_JUDGE
#ifdef FILEIO
FILE *infile=fopen("CF621E.in","r"), *outfile=fopen("CF621E.out","w");
#define scanf(x...) fscanf(infile,x)
#define printf(x...) fprintf(outfile,x)
#endif // FILEIO

const int mod=1e9+7;
int n,b,k,x,opt,N;
int dp[2][101],d[101];
inline int fastpow(int x,int k,const int mod) {
	int res=1;
	while(k) {
		if(k&1) res=res*x%mod;
		x=x*x%mod; k>>=1;
	}
	return res;
}
inline int plus(int x,int y,const int m=mod) { x+=y-m; return x+((x>>31)&m); }

int main() {
	scanf("%d%d%d%d",&n,&b,&k,&x);
	for(int i=1;i<=n;++i) {
		scanf("%d",&opt);
		++dp[0][opt%x];
	}
	for(int i=0;i<x;++i) d[i]=dp[0][i];
	N=b; n=1; int i=1; opt=0;
	while(n<<1<=N) n<<=1;
	while(n>>=1) {
		memset(dp[opt^=1],0,sizeof(dp[0]));
		const int _10=fastpow(10,i,x);
		for(int j1=0;j1<x;++j1) {
			const int _1=_10*j1%x;
			for(int j2=0;j2<x;++j2) {
				dp[opt][plus(_1,j2,x)]=plus(1ll*dp[opt^1][j1]*dp[opt^1][j2]%mod,dp[opt][plus(_1,j2,x)]);
			}
		}
		i<<=1;
		if(n&N) {
			memset(dp[opt^=1],0,sizeof(dp[0]));
			for(int j1=0;j1<x;++j1) {
				const int _1=10*j1%x;
				for(int j2=0;j2<x;++j2) {
					dp[opt][plus(_1,j2,x)]=plus(1ll*dp[opt^1][j1]*d[j2]%mod,dp[opt][plus(_1,j2,x)]);
				}
			}
			i|=1;
		}
	}
	printf("%d\n",dp[opt][k]);
#ifdef FILEIO
	fclose(infile); fclose(outfile);
#undef scanf
#undef printf
#endif // FILEIO
	return 0;
}

```

---

## 作者：panyanppyy (赞：0)

## $\mathcal{Problem}$
给你 $n$ 个数字，组成一个 $b$ 位数，数字可以重复使用，设最后数字为 $m$，求 $m\mod x=k$ 的次数，对 $10^9+7$ 取模。
$$2≤n≤50000,1≤b≤10^9,0≤k<x≤100,x≥2$$
## $\mathcal{Solution}$
然后就能没有压力地写出暴力 dp 转移方程：
$$f_{k,10\times i+j\mod x}=f_{10\times i+j\mod x}+f_i\times cnt_j\pmod{10^9+7}$$
$f_{k,i}$ 表示填到第 $k$ 位，对 $x$ 取模余数是 $i$ 的方案数。

$cnt_i$ 表示数字 $i$ 在数组中出现的次数。

这样时间复杂度是 $\mathcal O(bx)$。

一看 $b$ 的范围 $\mathbf{10^9!}$

很自然就能想到一个时间复杂度为 $\mathcal O(\log b)$ 的优秀 dp 转移方法：**矩阵快速幂**。

这里 $f_{...,10\times i+j}$ 可以由九种不同的状态转移过来，所以预处理出这十种状态的矩阵 **a**：
```
for(int i=0;i<X;i++)
	for(int j=1;j<=9;j++)
	a[(i*10+j)%X][i]+=t[j];
```
然后答案矩阵就初始化成：
$$
\begin{bmatrix}
1&0&0&\dotsb\\
0&1&0&\dotsb\\
0&0&1&\dotsb\\
\vdots&\vdots&\vdots&\ddots
\end{bmatrix}
$$
最后输出 $ans_{0,k}$ 就过了这道题。

[$\mathfrak{C^od_e}$](https://www.luogu.com.cn/paste/manh0wk9)

---

