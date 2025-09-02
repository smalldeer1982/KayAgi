# Neural Network country

## 题目描述

Due to the recent popularity of the Deep learning new countries are starting to look like Neural Networks. That is, the countries are being built deep with many layers, each layer possibly having many cities. They also have one entry, and one exit point.

There are exactly $ L $ layers, each having $ N $ cities. Let us look at the two adjacent layers $ L_{1} $ and $ L_{2} $ . Each city from the layer $ L_{1} $ is connected to each city from the layer $ L_{2} $ with the traveling cost $ c_{ij} $ for ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF852B/945db37d32744d415049d069cc0844aba4f66789.png), and each pair of adjacent layers has the same cost in between their cities as any other pair (they just stacked the same layers, as usual). Also, the traveling costs to each city from the layer $ L_{2} $ are same for all cities in the $ L_{1} $ , that is $ c_{ij} $ is the same for ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF852B/c68efb3baed3cf7572378486b7c111ddb2e0536c.png), and fixed $ j $ .

Doctor G. needs to speed up his computations for this country so he asks you to find the number of paths he can take from entry to exit point such that his traveling cost is divisible by given number $ M $ .

## 说明/提示

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF852B/a69d8a08d51c12997ef7e1fffeead190caef4b9f.png)

This is a country with $ 3 $ layers, each layer having $ 2 $ cities. Paths ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF852B/ec8d7c564cdb67dc57f9922091a73334d330a237.png), and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF852B/4299965c61d16bcfc0b10fce7b833b4b1e5fc7b5.png) are the only paths having total cost divisible by $ 13 $ . Notice that input edges for layer cities have the same cost, and that they are same for all layers.

## 样例 #1

### 输入

```
2 3 13
4 6
2 1
3 4
```

### 输出

```
2```

# 题解

## 作者：_Life_ (赞：8)

### 题意
有一幅有向图，除了源点和汇点有 $L$ 层，每层 $N$ 个点。 第 $i$ 层的每个点到第 $i+1$ 层的每个点都有一条边，给出源点到第一层的边权，层与层之间的边权，最后一层到汇点的边权，求源点到汇点的路径长度能被 $M$ 整除的方案数。

$1\le N\le 10^6,2\le L \le 10^5,2\le M \le 100$

### 题解
观察一下数据范围，发现 $M$ 相对于 $N$ 和 $L$ 很小，并且层与层之间的边权相同，联想到矩阵快速幂。

但是用矩阵似乎并不好表示路径方案数的转移，所以我们需要自己口胡一个东西来替代矩阵进行快速运算。

想一下这道题怎么暴力转移状态：
- $dp_{i,j}$ 表示到达第 $i$ 层，路径长度为 $j$ 的方案数。
- $w_{k}$ 表示两层间边权为 $k$ 的边数量
- $dp_{i,j}=\sum{dp_{i-1,j-w_{k}}}$

暴力的代码是这样的：
```cpp
//代码里要加膜法，为了方便阅读没加
dp[0][0]=1;
for(int i=1;i<=n;i++)
	for(int j=0;j<m;j++)
		for(int k=0;k<m;k++)
			dp[i][j+k]+=dp[i-1][j]*w[k];
```

现在好像还看不出什么东西，不如压个维？
```cpp
dp[0][0]=1;
for(int i=1;i<=n;i++)
	for(int j=0;j<m;j++)
		for(int k=0;k<m;k++)
			dp[i&1][j+k]+=dp[(i-1)&1][j]*w[k];
```

我们可以用一个一维数组表示到达一层的路径长度方案数！数组 $w$ 也可以这样处理！

我们可以把 $dp_i$ 看作 $dp_{i-1}\times w$ 的结果！那 $dp_i \times dp_i$ 得到的东西是什么？$dp_{2i}$ ！

~~我也不知道这个运算算不算乘法，但是同样具有交换律结合律之类的性质，这就够了~~

想到了什么？快速幂！就算这个运算看起来很怪，但还是可以快速幂！

记得把汇点和最后一层合并起来，避免出现各种奇奇怪怪的问题。

### 代码
```cpp
#include<cstdio>
#include<cstring>
#define int long long
#define mod 1000000007
using namespace std;
int n,l,m,dp[2][105],t[1000005],ans;
struct vec
{
	int x[105]={0};
	vec operator *(vec a)
	{
		vec ans;
		for(int i=0;i<m;i++)
			for(int j=0;j<m;j++)
				ans.x[(i+j)%m]+=x[i]*a.x[j],ans.x[(i+j)%m]%=mod;
		return ans;
	}
}a,b,c;
vec qpow(vec base,int k)
{
	vec ans;ans.x[0]=1;
	while(k)
	{
		if(k&1)
			ans=ans*base;
		k>>=1;
		base=base*base;
	}
	return ans;
}
signed main()
{
	scanf("%lld %lld %lld",&n,&l,&m);
	for(int i=1,x;i<=n;i++)scanf("%lld",&x),a.x[x%m]++;
	for(int i=1,x;i<=n;i++)scanf("%lld",&x),b.x[x%m]++,t[i]=x;
	for(int i=1,x;i<=n;i++)scanf("%lld",&x),x+=t[i],c.x[x%m]++;
	b=a*qpow(b,l-2)*c;
	//for(int i=0;i<m;i++)printf("%lld ",b.x[i]);
	printf("%lld",b.x[0]);
}
```

---

## 作者：hater (赞：7)

原先那篇题解感觉有点怪怪的 ..... 

运用矩乘快速幂的思想但不是矩乘 

标准的矩乘 

观察数据范围 M 很小 L 很大 应该是矩乘无疑 

但是我们进一步读题后发现 

在最后一层时 转移可能与当前所在节点位置有关

那我们的矩乘里会套一个 N ~~光荣的负优化~~ 

但是真的需要吗 其实在分层图中 下一步转移与当前位置无关

那我们手动做最后一层就好了 

代码 : 

$S.a_{i}$ 表示到某一层长度 %M 后为i 的路径数量 

$g$是转移矩阵 注意$cost$可能为 M 最好都 % 一下 

```cpp
#include<bits/stdc++.h> 
#define rg register 
#define i60 long long  
#define int long long 
#define fp( i , x , y ) for( rg int i=(x); i<=(y); ++i ) 
#define fq( i , x , y ) for( rg int i=(y); i>=(x); --i )  
using namespace std ; 
const int N = 105 ; 
const i60 hgs = 1e9+7 ; 
int n , l , m , A[N*10000] ;   
struct Matrix { 
  int a[N][N] ; 
  void clean( ) { memset( a , 0 , sizeof(a) ) ; } 
  friend Matrix operator *  ( Matrix A , Matrix B ) { 
     Matrix C ; C.clean( ) ;  
     fp( i , 0 , m-1 ) fp( j , 0 , m-1 ) fp( k , 0 , m-1 ) 
       C.a[i][j] += ( A.a[i][k] * (i60)B.a[k][j] % hgs ) , C.a[i][j] %= hgs ; 
     return C ; 
  } // f[j] += f[i] * g[i][j] 
  Matrix qpow( Matrix A , int B ) { 
    Matrix C ; C.clean( ) ; 
    fp( i , 0 , m-1 ) C.a[i][i] = 1 ; 
    for( ; B ; B >>= 1 ) { 
       if( B & 1 ) C = C * A ;  
       A = A * A  ; 
	} return C ; 
  }  
} S , g ;  
signed main( ) {  
  int x ; 
  scanf( "%lld %lld %lld" , &n , &l , &m ) ; 
  fp( i , 1 , n )  
    scanf( "%lld" , &x ) , S.a[0][x%m] ++ ; 
  fp( i , 1 , n ) { 
    scanf( "%lld" , &A[i] ) ; A[i] %= m ; 
    fp( j , 0 , m-1 ) 
       g.a[j][(j+A[i])%m] ++ ; 
  } 
  S = S * g.qpow ( g , l-2 ) ; 
  int ans = 0 ; 
  fp( i , 1 , n ) { 
     scanf( "%lld" , &x ) ; x %= m ;  
	 ans = ( ans + S.a[0][(2*m-x-A[i])%m] ) % hgs ; 
  } 
  printf( "%lld\n" , ans ) ; 
  return 0 ; 
} 
```




---

## 作者：LJ07 (赞：1)

看到分层，每层转移形似，考虑做转移的快速幂。

完全图，所以当前每个点完全不影响接下来的决策的贡献。同时边权只跟接下来的点的标号在膜 $m$ 下的值有关。

所以我们只需要关注标号在膜 $m$ 下的值。

怎么暴力 dp。设 $f_{i,j}$ 表示第 $i$ 层，和在膜 $m$ 下的值为 $j$。$c_{i}$ 表示点标号膜 $m$ 下的值为 $i$ 的个数。转移：$f_{i,j}\leftarrow \sum_{z} c_{z}f_{i-1,(j-z+m)\bmod m}$。

发现这可以看作乘上一个矩阵，矩阵快速幂即可。复杂度 $O(m^3\log L)$。开头和结尾的矩阵特殊处理即可。

当然你也可以把这个卷积快速幂了，可以做到 $O(m^2\log L)$。

下面给出矩阵快速幂的代码。卷积是类似的。

```cpp
void gen(Matrix &mat) {
  U(i, 0, m - 1) {
    U(j, 0, m - 1) {
      mat[i][(i + j) % m] = d[j];
    }
  }
}

int main() {
  rd(n), rd(L), rd(m);
  U(i, 1, n) {
    rd(a[i]);
  }
  U(i, 1, n) {
    rd(b[i]);
  }
  U(i, 1, n) {
    rd(c[i]);
  }
  U(i, 1, n) {
    ++d[a[i] % m];
  }
  gen(beg);
  memset(d, 0, m << 2);
  U(i, 1, n) {
    ++d[(c[i] + b[i]) % m];
  }
  gen(ed);
  memset(d, 0, m << 2);
  U(i, 1, n) {
    ++d[b[i] % m];
  }
  gen(trs);
  printf("%d\n", (beg * qpow(trs, L - 2) * ed)[0][0]);
  return 0;
}
```

---

## 作者：vvauted (赞：1)

## Solution of CF852B

可以对分层图做暴力 dp：

> $dp_{i,j}$ 表示到第 $i$ 个节点路径长 $\bmod m$ 意义下等于 $j$ 的方案种数 

显然这个转移是 $O(Ln^2m)$ 的。考虑层与层之间到同一节点的边权相同，那么前一层每个节点的转移都相同的，考虑对层与层之间 $dp$：

> $tp_{i,j}$ 表示到第 $i$ 个层路径长 $\bmod m$ 意义下等于 $j$ 的方案种数 

这个转移是 $O(Lnm)$ 的，显然还是过慢，而我们观察到中间层之间的边权不变，那么说明中间层之间的转移也是相同的。

如果我们把这个 $tp$ 看成一个生成函数，显然它在 $\bmod x^n$ 下满足指数相加，系数相乘的多项式乘法法则，我们可以通过多项式快速幂求出 $tp$，复杂度 $O(m\log L)$。

而知道了 $tp_{n-2}$，就可以推得所有 $dp_{i}(i\in S_{n-1})$，那么记录答案也就很简单了。

```cpp
#include <bits/stdc++.h>
#define Maxn 2000006
#define Maxm 105
#define Nep(i, l, r) for(int i = l; i != r; ++ i)
#define Rep(i, l, r) for(int i = l; i <= r; ++ i)
#define rep(i, l, r) for(int i = l; i < r; ++ i)
#define Lep(i, l, r) for(int i = l; i >= r; -- i)
#define lep(i, l, r) for(int i = l; i > r; -- i)
#define Max(a, b) a = std :: max(a, b)
#define ll long long
#define ull unsigned long long
#define int long long

const int mod = 1e9 + 7;

int read() {
	int x = 1, res = 0, ch = getchar();
	while(ch < '0' || ch > '9') { if(ch == '-') x = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9') res = (res << 3) + (res << 1) + (ch ^ 48), ch = getchar();
	return x * res;
}

int m, L, n, d[Maxn];
int add(int x, int y) { return (x + y) % mod; }
int mul(int x, int y) { return (x * y) % mod; }

struct poly {
    int x[Maxm];

    friend poly operator * (poly x, poly y) {
        poly z = {}; 
        rep(i, 0, m) rep(j, 0, m) z.x[(i + j) % m] = add(z.x[(i + j) % m], mul(x.x[i], y.x[j]));
        return z; 
    }
};

poly qpow(poly x, int y) {
    poly ret = {1};

    for (; y; y >>= 1, x = x * x)
        if (y & 1) ret = ret * x;
    return ret;
}

signed main() {
    n = read(), L = read(), m = read();
    poly A = {}, B = {}, ans;
    Rep(i, 1, n) A.x[read() % m] ++; 
    Rep(i, 1, n) B.x[d[i] = read() % m] ++; 
    ans = L > 1 ? A * qpow(B, L - 2) : A; int res = 0;  
    Rep(i, 1, n) res = add(res, ans.x[(m + (- read() - d[i]) % m) % m]);
    return printf("%lld", res), 0;
}
```


---

## 作者：Jay142753869 (赞：1)

题意：有一幅有向图，除了源点和汇点有 $L$ 层，每层 $n$ 个点。第 $i+1$ 层的每个点到第 $i+2$ 层的每个点都有一条边，边的权值为有向边终点的权值。求源点到汇点的路径长度能被 $m$ 整除的个数。  
~~比较容易看出来的~~快速幂。设 $a_i$ 表示从第 $1$ 层到第 $a$ 层总路径长度为 $i (i \mod  m)$ 的数目，同理设 $b_j$ 表示从第 $a+1$ 层到第 $a+1$ 层（也就是自己层）总路径长度为 $j (j \mod  m)$ 的数目，那么第 $a+2$ 层的 $a_{(i+j) \ mod m} = a_i \times b_j$。  
那么如果一个一个乘上去的话会超时。  
我们不难发现从第 $2$ 层到第 $L-1$ 层，每次乘的操作是相同的，可以用快速幂先预处理把第 $2$ 层到第 $L-1$ 层乘起来。这样就不会超时了。  
 _Code_ 
 ```cpp
#include<iostream>
#include<cstdio> 
#include<algorithm>
#include<cstring>
#define mod 1000000007
#define maxn 1000010
using namespace std;
int a[maxn],n,q,m;
inline int read(){
	register int x=0,f=0,ch=getchar();
	while('0'>ch||ch>'9')f^=ch=='-',ch=getchar();
	while('0'<=ch&&ch<='9')x=(x<<1)+(x<<3)+(ch^'0'),ch=getchar();
	return f?-x:x;
}
struct node
{
    long long num[110];
    node(){
    	memset(num,0,sizeof(num));
	}
}l,r,mid;
node mul(node x,node y)
{
    node aa=node();
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<m;j++)
        {
            int k=(i+j)%m;
            aa.num[k]+=x.num[i]*y.num[j]%mod;
            aa.num[k]%=mod;
        }
    }
    return aa;
}
node qpow(node nod,int k)
{
    node sum=nod;
    k--;
    while(k)
    {
        if(k&1)
        {
            sum=mul(sum,nod);
        }
        k>>=1;
        nod=mul(nod,nod);
    }
    return sum;
}
int main()
{
    l=node();
    r=node();
    mid=node();
    n=read(),q=read(),m=read();
    for(int i=1;i<=n;i++)
    {
        int x=read();
        l.num[x%m]++;
    }
    for(int i=1;i<=n;i++)
    {
        int x=read();
        a[i]=x;
        mid.num[x%m]++;
    }
    for(int i=1;i<=n;i++) {
        int x=read();
        r.num[(x+a[i])%m]++;
    }
    node nod;
    if(q-2>0){
        nod=qpow(mid,q-2);    
        nod=mul(nod,l);
        nod=mul(nod,r); 
    }
    else
        nod=mul(l,r);
    long long ans=0;
    for(int j=0;j<=100;j++){
        if(j%m==0){
            ans+=nod.num[j];
            ans%=mod;
        }
    }
    printf("%lld\n",ans);
    return 0;
}
 ```

---

## 作者：CarroT5656 (赞：0)

先考虑暴力。在分层图上跑 dp。

定义转移状态（为了方便优化忽略去模）：

* $dp_{i,j,k}$ 表示到达第 $i$ 层，第 $j$ 个点的所有路径中边权和为 $k$ 的方案数。

* $dp_{i,j,k}=\sum dp_{i-1,l,k-c_l}$

不难想到第二维其实没什么用，压掉。

* $t_k$ 表示当前第 $i$ 层到第 $i-1$ 层之间边权为 $k$ 的边数。

* $dp_{i,j}=\sum dp_{i-1,j-k}\times t_k$

时间复杂度为 $O(nm^2)$。还需要继续优化。

先把转移方程中的第一维忽略。

$dp_{j}=\sum dp_{j-k}\times t_k$

显然可以用一个矩阵来表示 $\{dp_i\}$，每次转移可以转化成一个矩阵乘法。然后用矩阵快速幂来优化这个转移方程。

时间复杂度为 $O(m^2\log n)$，可以通过。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define mod 1000000007
#define M 105
ll n,l,m,t[N];
struct mtrx{
	ll x[M];
	mtrx(){memset(x,0,sizeof(x));}
	mtrx operator*(mtrx a){
		mtrx ans;
		for(ll i=0;i<m;i++) for(ll j=0;j<m;j++)
			(ans.x[(i+j)%m]+=x[i]*a.x[j])%=mod;
		return ans;
	}
}a,b,c;
mtrx qpow(mtrx a,ll b){
	mtrx ans;
	ans.x[0]=1;
	while(b){
		if(b&1) ans=ans*a;
		a=a*a,b>>=1; 
	}
	return ans;
}
int main(){
	scanf("%lld%lld%lld",&n,&l,&m);
	for(ll i=1,v;i<=n;i++) scanf("%lld",&v),a.x[v%m]++;
	for(ll i=1,v;i<=n;i++) scanf("%lld",&v),b.x[v%m]++,t[i]=v;
	for(ll i=1,v;i<=n;i++) scanf("%lld",&v),v+=t[i],c.x[v%m]++;
	b=a*qpow(b,l-2)*c;
	printf("%lld\n",b.x[0]);
	return 0;
}
```

---

