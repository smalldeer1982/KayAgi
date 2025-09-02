# Okabe and El Psy Kongroo

## 题目描述

Okabe likes to take walks but knows that spies from the Organization could be anywhere; that's why he wants to know how many different walks he can take in his city safely. Okabe's city can be represented as all points $ (x,y) $ such that $ x $ and $ y $ are non-negative. Okabe starts at the origin (point $ (0,0) $ ), and needs to reach the point $ (k,0) $ . If Okabe is currently at the point $ (x,y) $ , in one step he can go to $ (x+1,y+1) $ , $ (x+1,y) $ , or $ (x+1,y-1) $ .

Additionally, there are $ n $ horizontal line segments, the $ i $ -th of which goes from $ x=a_{i} $ to $ x=b_{i} $ inclusive, and is at $ y=c_{i} $ . It is guaranteed that $ a_{1}=0 $ , $ a_{n}<=k<=b_{n} $ , and $ a_{i}=b_{i-1} $ for $ 2<=i<=n $ . The $ i $ -th line segment forces Okabe to walk with $ y $ -value in the range $ 0<=y<=c_{i} $ when his $ x $ value satisfies $ a_{i}<=x<=b_{i} $ , or else he might be spied on. This also means he is required to be under two line segments when one segment ends and another begins.

Okabe now wants to know how many walks there are from the origin to the point $ (k,0) $ satisfying these conditions, modulo $ 10^{9}+7 $ .

## 说明/提示

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF821E/f658e3b02a94b26e1ceda15b31b9ad31fd8decfb.png)The graph above corresponds to sample 1. The possible walks are:

- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF821E/fe5ddffd345db7dbc9811066d89af8164e156a48.png)
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF821E/3c1f68141260e9f0faf2c18d37cc945fe3064803.png)
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF821E/6d7eca326042aa73d0e36209e3dcf0b53f326988.png)
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF821E/b384b506ab41aac1cef00012023de00c92c6ca52.png)

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF821E/808ba51553ca63393b29c100184e006bbe68cb46.png)The graph above corresponds to sample 2. There is only one walk for Okabe to reach $ (3,0) $ . After this, the possible walks are:

- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF821E/c65499d5e0d037bc0e099631cfbdc3b47191ec5c.png)
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF821E/ea64d72ce9bbedf50ad31137fb330842e8e48b14.png)
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF821E/f552304e1f485b618079fd34e72f22adaf988bc2.png)
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF821E/9c27a4273309f39ff98075265ceb3af61e3cd1cb.png)

## 样例 #1

### 输入

```
1 3
0 3 3
```

### 输出

```
4
```

## 样例 #2

### 输入

```
2 6
0 3 0
3 10 2
```

### 输出

```
4
```

# 题解

## 作者：Grisses (赞：2)

[]()

你在 $(0,0)$。

在 $(x,y)$ 时，每次移动可以到达 $(x+1,y+1),(x+1,y),(x+1,y-1)$。

平面上有 $n$ 条线段，平行于 $x$ 轴，参数为$a_i$，$b_i$，$c_i$，表示在 $(a_i,c_i)$ 到 $(b_i,c_i)$ 的一条线段，保证 $b_i=a_{i+1}$。

要求你一直在线段的下方且在 $x$ 轴上方，即 $a_i \leq x \leq b_i$ 时， $0 \leq y \leq c_i$。

问：到达 $(k,0)$ 的方案数，方案数对 $10^9+7$ 取模。

我们设 $dp_{i,j}$ 表示走到 $(i,j)$ 的方案数，$k_i$ 表示 $x$ 坐标为 $i$ 时行动的上界。

按照题意，递推式：
$$dp_{i,j}=\begin{cases}dp_{i-1,j-1}+dp_{i-1,j}&(j=k_i)\\dp_{i-1,j-1}+dp_{i-1,j}+dp_{i-1,j+1}&(0<j<k_i)\\dp_{i-1,j}+dp_{i-1,j+1}&(j=0)\end{cases}$$

那么，我们可以构造一个形如 $\begin{pmatrix}1&1&0&\cdots&0&0&0\\1&1&1&\cdots&0&0&0\\\vdots&&&\ddots&&&\vdots\\0&0&0&\cdots&1&1&1\\0&0&0&\cdots&0&1&1\end{pmatrix}$ 的矩阵进行转移。用快速幂优化即可。

对于矩阵快速幂，这是一种优化递推的算法，可以用 $O(\lg n)$ 的时间复杂度进行 $n$ 次递推。

首先，定义矩阵乘法：

对于一个 $n\times k$ 的矩阵 $A$ 和一个 $k\times m$ 的矩阵 $B$ 还有一个矩阵 $C=A\times B$。那么 $C$ 是一个 $n\times m$ 的矩阵，且 $C_{ij}=\sum\limits_{p=1}^kA_{i,p}\times B_{p,j}(i=\overline{1,2,\cdots,n},j=\overline{1,2,\cdots,m})$。

然后，因为矩阵乘法满足结合律，所以我们有了矩阵快速幂。矩阵快速幂的话就是把快速幂的板子套在矩阵上而已。

代码：
```cpp
  #include<bits/stdc++.h>
  #define int long long 
  using namespace std;
  const int mod=1e9+7;
  int n,k,a,b,c;
  struct M{
      int a[20][20];
      M operator*(M t){
          M res;
          for(int i=0;i<=15;i++)for(int j=0;j<=15;j++)res.a[i][j]=0;
          for(int i=0;i<=15;i++){
              for(int j=0;j<=15;j++){
                  for(int k=0;k<=15;k++){
                      res.a[i][j]=(res.a[i][j]+a[i][k]*t.a[k][j]%mod)%mod;
                  }
              }
          }
          return res;
      }
      M operator^(int k){
          M res,_=*this;
          for(int i=0;i<=15;i++)for(int j=0;j<=15;j++)res.a[i][j]=(i==j);
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
      scanf("%lld%lld",&n,&k);
      for(int j=0;j<=15;j++)for(int k=0;k<=15;k++)ans.a[j][k]=0;
      ans.a[0][0]=1;
      for(int i=1;i<=n;i++){
          scanf("%lld%lld%lld",&a,&b,&c);
          if(b>=k)b=k;
          for(int j=0;j<=15;j++)for(int l=0;l<=15;l++)base.a[j][l]=0;
          for(int j=0;j<=c;j++){
              base.a[j][j]=1;
              if(j<c)base.a[j][j+1]=1;
              if(j)base.a[j][j-1]=1;
          }
          ans=(base^(b-a))*ans;
          if(b>=k)break;
      }
      printf("%lld",ans.a[0][0]);
      return 0;
  }
```

---

## 作者：Mr_Avalon (赞：1)

~~El Psy Kongroo。~~

**题目分析**

因为每次只能向前走，所以状态的转移就很 simple 了。我们设 $f_{i,j}$ 表示 okabe 走到 $(i,j)$ 时的总方案数，显然有：

$$f_{i,j}=f_{i-1,j}+f_{i-1,j-1}\times[j>0]+f_{i-1,j+1}\times[j<c_i]$$

复杂度 $O(c\times k)$，无法通过此题。

$k$ 的级别是 $1e18$ 的，$c$ 却很小，这启发我们对 $k$ 这一维进行优化。我们进一步观察，发现 **$f_{i,* }$ 只与 $f_{i-1,* }$ 有关**，而且转移的也十分有规律，根据套路，我们容易列出下面的带状矩阵：

$$
\begin{bmatrix}
1&1&0&0&\cdots&0&0&0&0\\
1&1&1&0&\cdots&0&0&0&0\\
0&1&1&1&\cdots&0&0&0&0\\
\vdots&&&&\ddots&&&&\vdots\\
0&0&0&0&\cdots&1&1&1&0\\
0&0&0&0&\cdots&0&1&1&1\\
0&0&0&0&\cdots&0&0&1&1
\end{bmatrix}
$$

我们把 $f_{i,* }$ 压进一个矩阵和上面的矩阵相乘，得到的新矩阵就是 $f_{i+1,* }$ 压成的矩阵。再套上矩阵快速幂，这道题就做完了，复杂度 $O(c^3\log k)$。

**代码**

```cpp
#include<stdio.h>
#include<string.h>

typedef long long ll;
const int mod=1e9+7;

inline void add(int &x,int y) {x+=y-mod,x+=(x>>31)&mod;}

int n,sz;
ll k,len;

struct Matrix
{
    int a[20][20];
    Matrix() {memset(a,0,sizeof a);}
}A,Empty;

inline Matrix operator * (Matrix A,Matrix B)
{
    Matrix C;

    for(int k=1;k<=sz;k++)
        for(int i=1;i<=sz;i++)
            for(int j=1;j<=sz;j++)
                add(C.a[i][j],1ll*A.a[i][k]*B.a[k][j]%mod);

    return C;
}

inline Matrix operator ^ (Matrix A,ll k)
{
    Matrix Base;
    for(int i=1;i<=sz;i++) Base.a[i][i]=1;

    while(k)
    {
        if(k&1) Base=Base*A;
        A=A*A,k>>=1;
    }

    return Base;
}

int main()
{
    #ifdef Mr_Avalon
    freopen("input","r",stdin);
    freopen("output","w",stdout);
    #endif

    scanf("%d%lld",&n,&k),A.a[1][1]=1;
    for(int i=1;i<=n;i++)
    {
        ll a,b;int c;
        scanf("%lld%lld%d",&a,&b,&c);
        len=(b>k? k:b)-a,sz=c+1;

        Matrix tmp;
        for(int j=1;j<=sz;j++) tmp.a[j][j-1]=tmp.a[j][j]=tmp.a[j][j+1]=1;
        A=A*(tmp^len);
    }
    printf("%d",A.a[1][1]);

    #ifdef Mr_Avalon
    printf("\n%dms\n",int(1.0*clock()/CLOCKS_PER_SEC*1000));
    #endif
}
```


---

## 作者：Lance1ot (赞：1)

首先我们从最简单的dp开始

$dp[i][j]=dp[i-1][j]+dp[i-1][j+1]+dp[i-1][j-1]$

然后这是一个O(NM)的做法，肯定行不通，然后我们考虑使用矩阵加速

$\begin{bmatrix} 1\\ 0 \\0\\0\end{bmatrix}\quad$

鉴于纵坐标很小，考虑全部记录下来。写成一个向量的形式。如上，
第i行的数表示纵坐标为i-1的方案数。

然后我们考虑转移

$\begin{bmatrix} 1&1&0&0\\1&1&1&0 \\0&1&1&1\\0&0&1&1\end{bmatrix}\quad$

我们将不考虑线段的转移写成以上形式，然后考虑一下如果有线段影响呢？

我们可以类比得到，上一个矩阵中的边界是3，如果我们人为规定上边界是2的话。转移就成了这个样子

$\begin{bmatrix} 1&1&0&0\\1&1&1&0 \\0&1&1&0\\0&0&0&0\end{bmatrix}\quad$

然后我们发现，如果不是上边界和下边界时，matrix[i][i].matrix[i][i-1].matrix[i][i+1]都是1，然后上下边界自己处理就可以了。

然后我们上一个矩阵快速幂就可以了

```cpp
#include<cstdio>
#include<algorithm>
#include<iostream>
using namespace std;
const long long mod=1e9+7;
struct node
{
	int n,m;
	long long base[20][20];
	node operator * (const node &a)const 
	{
		node r;
		r.n=n,r.m=a.m;
		for(int i=0;i<=n;i++)	for(int j=0;j<=a.m;j++)	r.base[i][j]=0;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=a.m;j++)
				for(int k=1;k<=m;k++)
					r.base[i][j]=(r.base[i][j]+base[i][k]*a.base[k][j])%mod;
		return r;
	}
};//矩阵模板
node pas,ans;
long long a[120],b[120],c[120];
node kasumi(long long k)
{
	node res;
	res.n=res.m=pas.n;
	for(int i=0;i<=res.n;i++)	for(int j=0;j<=res.m;j++)	res.base[i][j]=0;
	for(int i=0;i<=res.n;i++)	res.base[i][i]=1;
	while(k)
	{
		if(k&1)	res=res*pas;
		pas=pas*pas;
		k>>=1;
	}
	return res;//快速幂
}
int main()
{
	long long n,k;
	scanf("%lld%lld",&n,&k);
	ans.n=1;ans.m=16;
	for(int i=1;i<=16;i++)	for(int j=1;j<=16;j++)	ans.base[i][j]=0;//读入数据
	ans.base[1][1]=1;//处理初始数据
	pas.n=16;pas.m=16;
	for(int i=1;i<=n;i++)	scanf("%lld%lld%lld",&a[i],&b[i],&c[i]);//输入
	for(int l=1;l<=n;l++)//然后按照顺序遍历线段
	{
		for(int i=0;i<=16;i++)	for(int j=0;j<=16;j++)	pas.base[i][j]=0;//重新清零
		for(int i=1;i<=c[l]+1;i++)
		{//处理转移数组
			if(i!=1)	pas.base[i][i-1]=1;
			pas.base[i][i]=1;
			if(i!=c[l]+1)	pas.base[i][i+1]=1;
		}
		ans=ans*kasumi(min(b[l],k)-a[l]);//快速幂就可以了
	}
	printf("%lld",ans.base[1][1]);
}
```

---

## 作者：Kingna (赞：0)

定义 $f_{i,j}$ 表示走到 $(i,j)$ 的方案数。

转移显然：$f_{i,j}=f_{i-1,j}+f_{i-1,j-1}\times [j>0]+f_{i-1,j+1}\times [j<c_i]$。


有一个重要的信息是：$a_i=b_{i-1}$。这意味着每一条线段都是独立的。而且 $j\leq 15$，只有 $i$ 非常大，启发我们矩阵加速。

定义矩阵 $[a_0,a_1,\dots,a_{15}]$ 表示 $f_{i}$ 这一维的状态，考虑如何转移到 $f_{i+1}$。

我们对于每一个 $j∈[0,15]$，修改转移矩阵 $A[i][i],A[i][i+1],A[i][i-1]$ 加一即可。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define PII pair<int, int>
#define _for(i, a, b) for (int i = (a); i <= (b); i++)
#define _pfor(i, a, b) for (int i = (a); i >= (b); i--)
#define int long long

const int N = 3e5 + 5, mod = 1e9 + 7;

int n, k, a[N], b[N], c[N], nw[20][20], res[20][20], base[20][20];

void mul(auto &a, auto &b, auto &c) {
	_for(i, 0, 15) _for(j, 0, 15) nw[i][j] = 0;
	_for(i, 0, 15) {
		_for(j, 0, 15) {
			_for(k, 0, 15) {
				nw[i][j] = (nw[i][j] + b[i][k] * c[k][j] % mod + mod) % mod;
			}
		}
	}
	_for(i, 0, 15) _for(j, 0, 15) a[i][j] = nw[i][j];
}

signed main() {
	cin >> n >> k;
	_for(i, 1, n) cin >> a[i] >> b[i] >> c[i];
	res[0][0] = 1;
	_for(i, 1, n) {
		b[i] = min(b[i], k);
		_for(j, 0, 15) _for(k, 0, 15) base[j][k] = 0;
		_for(j, 0, c[i]) {
			base[j][j] = 1;
			if (j < c[i]) base[j][j + 1] = 1;
			if (j) base[j][j - 1] = 1;
		}
		int tmp = b[i] - a[i];
		while (tmp) {
			if (tmp & 1) mul(res, res, base);
			mul(base, base, base);
			tmp >>= 1; 
		}
		if (b[i] >= k) break;
	}
	cout << res[0][0] << endl;
}
```

---

## 作者：Inui_Sana (赞：0)

El Psy Kongroo.

首先有显然的从左往右的 dp：设当前在 $(i,j)$，方案数为 $dp_{i,j}$。转移就是往三个方向转移。

但是 $k$ 很大，怎么办？发现 $c_i$ 也就是纵坐标，dp 数组第二维范围很小，考虑矩阵快速幂。对于每条直线，特判端点，然后剩下部分矩阵快速幂。

矩阵是简单的，就是不要漏某些转移，以及对于结束位置要特判。复杂度 $O(nc^3\log k)$，其中 $c=16$。

code：

```cpp
int n;ll m;
il int Mod(int x,int y){
	return x+y>=mod?x+y-mod:x+y;
}
struct mat{
	int a[16][16];
	mat(int op=0){
		mems(a,0);
		rep(i,0,15){
			a[i][i]=op;
		}
	}
	mat operator*(const mat &rhs)const{
		mat r;
		rep(k,0,15){
			rep(i,0,15){
				rep(j,0,15){
					r.a[i][j]=Mod(r.a[i][j],1ll*a[i][k]*rhs.a[k][j]%mod);
				}
			}
		}
		return r;
	}
}s,t[16];
il mat qpow(mat x,ll y){
	mat ret(1);
	while(y){
		if(y&1){
			ret=ret*x;
		}
		x=x*x,y>>=1;
	}
	return ret;
}
void Yorushika(){
	scanf("%d%lld",&n,&m);
	s.a[0][0]=1;
	rep(k,0,15){
		rep(i,0,k){
			t[k].a[i][i]=1;
			if(i>0){
				t[k].a[i-1][i]=1;
			}
			if(i<15){
				t[k].a[i+1][i]=1;
			}
		}
	}
	int lst=inf;
	rep(i,1,n){
		ll x,y;int z;scanf("%lld%lld%d",&x,&y,&z);
		if(x==m){
			lst=min(lst,z);
			break;
		}
		if(i>1){
			s=s*t[min(lst,z)];
		}
		if(i==n){
			y=min(y,m);
		}
		lst=z;
		s=s*qpow(t[z],y-x-1);
	}
	s=s*t[lst];
	printf("%d\n",s.a[0][0]);
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)
		Yorushika();
}
```

---

## 作者：yizhiming (赞：0)

虽然有相同的题解已经有了，但是作为石头门厨还是想发一篇。

感觉完全没必要评紫，CF 评分也不高。

[Link](https://www.luogu.com.cn/problem/CF821E)

## 题目大意

给定一个平面直角坐标系，初始在 $(0,0)$，每次可以从 $(x,y)$ 走到 $(x+1,y+1),(x+1,y),(x+1,y-1)$ 这几个位置，平面上有 $n$ 条线段，第 $i$ 条线段的端点是 $(a_i,c_i),(b_i,c_i)$，保证这几条线段在横坐标上连续。

问保证全程在线段下方，且在 $x$ 轴上方（可重合）的前提下，走到 $(k,0)$ 的方案数，对 $10^9+7$ 取模。

$1\leq n \leq 100,1\leq k \leq 10^{18},a_{n}\leq k \leq b_n,c_i\leq 15$。

## 题目分析

最朴素的想法，直接 $O(kc)$  暴力 dp 即可，具体的设 $dp_{i,j}$ 表示到达 $(i,j)$ 的方案数，那么显然有：

$dp_{i,j} = dp_{i-1,j-1}+dp_{i-1,j}+dp_{i-1,j+1}$。

边界条件当 $j=0$ 或 $15$ 时特殊处理一下，以及对于当前区间的最大上限处理一下即可。

不难发现 $k$ 是绝对不能沾的，所以考虑更为高妙的方法，不难发现对于上限相同的区间的转移是完全相同的，所以我们考虑将 $n$ 个区间分开来处理，所以问题就变成了如何快速求出上限相同的一段区间的贡献。

发现上面的那个转移可以很好的变成矩阵的形式，在转移矩阵上每个位置是否为 $1$ 表示在转移后能否统计这个位置的贡献即可，例如第一组样例，就可以构造出这样的转移矩阵。

$\begin{bmatrix}
 1& 1 & 0 &0\\
 1& 1 & 1&0\\
 0& 1 & 1&1\\
 0& 0 & 1&1
\end{bmatrix}$

自己手模一下不难得出，直接想也好像，转移矩阵对应能够贡献给下一个矩阵的地方填 $1$ 就好。

如何快速求长为 $x$ 的区间的贡献呢？对转移矩阵求一个矩阵快速幂即可。

所以最终只需要将原序列分段，每次求出对应的转移矩阵，枚举一遍所有段，利用矩阵快速幂优化转移即可。

## Code

封装一下矩阵乘会稍微美观一些。

```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <queue>
#define int long long
using namespace std;
int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int N = 105;
const int S = 16;
int Mod = 1e9+7;
int n,k;
int a[N],b[N],c[N];
struct Matrix{
	int val[S][S],x,y;
	void clear(){
		x = 0;y = 0;
		memset(val,0,sizeof(val));
	}
	Matrix operator*(const Matrix &u)const{
		Matrix res;
		res.clear();
		for(int i=0;i<=x;i++){
			for(int j=0;j<=u.y;j++){
				for(int k=0;k<=y;k++){
					res.val[i][j] = (res.val[i][j]+val[i][k]*u.val[k][j]%Mod)%Mod;
				}
			}
		}
		res.x = x;res.y = u.y;
		return res; 
	}
	void print(){
		cout<<"XY:"<<x<<" "<<y<<'\n';
		for(int i=0;i<=x;i++){
			for(int j=0;j<=y;j++){
				cout<<val[i][j]<<" ";
			}
			cout<<"\n"; 
		}
		cout<<"-----------------------------------\n";
	}
	
}zy,dwy;
Matrix ksm(Matrix x,int y){
	Matrix res = dwy;
	while(y){
		if(y&1){
			res = res*x;
		}
		y>>=1;
		x = x*x;
	}
	return res;
}
void init(int x){
	zy.clear();
	for(int i=0;i<=x;i++){
		zy.val[max(0ll,i-1)][i] = 1;
		zy.val[i][i] = 1;
		zy.val[min(i+1,15ll)][i] = 1;
	}
	zy.x = 15;zy.y = 15;
}
int ans[S];
signed main(){
	n = read();k = read();
	for(int i=1;i<=n;i++){
		a[i] = read();b[i] = read();c[i] = read();
	}
	for(int i=0;i<=15;i++){
		zy.val[max(0ll,i-1)][i] = 1;
		zy.val[i][i] = 1;
		zy.val[min(i+1,15ll)][i] = 1;
		dwy.val[i][i] = 1;
	}
	dwy.x = 15;dwy.y = 15;
	ans[0] = 1;
	for(int i=1;i<n;i++){
		Matrix f;
		f.clear();
		f.x = 0;f.y = 15;
		for(int j=0;j<=c[i];j++){
			f.val[0][j] = ans[j];
		}
		init(c[i]);
		f = f*ksm(zy,b[i]-a[i]);
		for(int j=0;j<=15;j++){
			ans[j] = f.val[0][j];
		}
	}
	Matrix f;
	f.clear();
	f.x = 0;f.y = 15;
	init(c[n]);
	for(int j=0;j<=c[n];j++){
		f.val[0][j] = ans[j];
	}
	f = f*ksm(zy,k-a[n]);
	for(int j=0;j<=15;j++){
		ans[j] = f.val[0][j];
	}
	cout<<ans[0]<<"\n";
	return 0;
}

```

‌在一个我不存在的世界里唯一记得我的你很痛苦吧？

---

