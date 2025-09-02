# [ARC067E] Grouping

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc067/tasks/arc067_c

$ 1 $ から $ N $ までの番号のついた $ N $ 人の人がいます。 以下の二つの条件を満たすように、彼らをいくつかのグループに分けたいです。

- どのグループも、そのグループに含まれる人数が $ A $ 人以上 $ B $ 人以下である。
- ちょうど $ i $ 人の人が含まれるようなグループの数を $ F_i $ で表したとき、 すべての $ i $ について、$ F_i=0 $ または $ C≦F_i≦D $ が成り立っている。

このようなグループ分けが何通りあり得るか求めてください。 ただし、ある二つのグループ分けが異なるとは、二人の人の組であって、 片方のグループ分けでは同じグループに含まれ、他方では同じグループに含まれないようなものが存在することを意味します。 なお、答えは非常に大きくなることがあるので、$ 10^9+7 $ で割った余りを出力してください。

## 说明/提示

### 制約

- $ 1≦N≦10^3 $
- $ 1≦A≦B≦N $
- $ 1≦C≦D≦N $

### Sample Explanation 1

以下の $ 4 $ 通りの分け方があります。 - $ (1,2),(3) $ - $ (1,3),(2) $ - $ (2,3),(1) $ - $ (1,2,3) $ $ (1),(2),(3) $ のような分け方は、一つ目の条件は満たしていますが、 二つ目の条件を満たしていないために数えられません。

### Sample Explanation 2

$ 2 $ 人グループ、$ 2 $ 人グループ、$ 3 $ 人グループの三つに分ける以外に適切な分け方はありません。 そして、このような分け方は $ 105 $ 通りあります。

### Sample Explanation 4

答えが $ 0 $ になることもあり得ます。

## 样例 #1

### 输入

```
3 1 3 1 2```

### 输出

```
4```

## 样例 #2

### 输入

```
7 2 3 1 3```

### 输出

```
105```

## 样例 #3

### 输入

```
1000 1 1000 1 1000```

### 输出

```
465231251```

## 样例 #4

### 输入

```
10 3 4 2 5```

### 输出

```
0```

# 题解

## 作者：Krimson (赞：5)

非常一眼的dp题,不知道当初为啥每看出来  

设$f[i][j]$表示目前已经分到了人数为$i$的组,用了$j$个人的方案数是多少  
不难得到转移方程  
$$
\begin{aligned}
f[i][j]&=f[i-1][j]+\sum^{D}_{k=C} f[i-1][j-ki]\times C^{n-(j-ki)}_{ki}\times\ g[i][k] \\
\end{aligned}
$$  
其中$g[i][k]$是一个系数,表示有$ik$个人,$i$个人为一组,分成$k$组的方案数有多少  
而$g[i][k]$也非常好计算,其实依次从总人数中选出$i$个人的方案数,即$\sum C^{ik-it}_{i}$  
但是由于先选后选都属于同一种方案,因此最后还要再除一个$k!$  
初始化为$f[A-1][0]=1$,$ans=f[B][N]$  
因为枚举$k$的过程是调和级数,因此复杂度为$O(n^2logn)$


 _Code_ 
------------
```cpp
#include<bits/stdc++.h>
using namespace std;
#define il inline
#define ri register int
#define ll long long
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
il int max(const int &a,const int &b){return a>b?a:b;}
il int min(const int &a,const int &b){return a<b?a:b;}
/*
*/
const ll mod=1e9+7;
const int MAXN=1e3+7;
il ll ksm(ll d,ll tim){
    ll rest=1;
    while(tim){
        if(tim&1) rest=rest*d%mod;
        d=d*d%mod;
        tim>>=1;
    }
    return rest;
}
ll jc[MAXN],inv[MAXN];
void init(int n=1e3){
    jc[0]=1;
    for(ri i=1;i<=n;++i)
        jc[i]=i*jc[i-1]%mod;
    inv[n]=ksm(jc[n],mod-2);
    for(ri i=n-1;~i;--i)
        inv[i]=(i+1)*inv[i+1]%mod;
}
il ll C(ll x,ll y){
    if(x<y) return 0;
    return jc[x]*inv[y]%mod*inv[x-y]%mod;
}
ll f[MAXN][MAXN],g[MAXN][MAXN],n,a,b,c,d;
int main(){
    init();
    n=read(),a=read(),b=read(),c=read(),d=read();
    for(ri i=1;i<=n;++i){
        for(ri j=1;j*i<=n;++j){
            g[i][j]=1;
            for(ri k=i*j;k;k-=i) g[i][j]=g[i][j]*C(k,i)%mod;
            g[i][j]=g[i][j]*inv[j]%mod;
        }
    }
    f[a-1][0]=1;
    for(ri i=a;i<=b;++i){
        for(ri j=0;j<=n;++j){
            f[i][j]=f[i-1][j];
            for(ri k=c;k*i<=j&&k<=d;++k){
                f[i][j]=(f[i][j]+f[i-1][j-k*i]*C(n-(j-k*i),k*i)%mod*g[i][k]%mod)%mod;
            }
        }
    }
    print(f[b][n]);
    return 0;
}
```


---

## 作者：james1BadCreeper (赞：3)

发现数据范围很小，因此直接考虑暴力 DP。

设 $f_{i,j}$ 代表考虑到分人数为 $i$ 的组，当前有 $j$ 个人的方案数。决策有两种：不存在这个人数的组，这个人数的组的个数在 $[c,d]$ 之间。那么有：

$$
f_{i,j}=f_{i-1,j}+\sum_{j=c}^d f_{i-1,j-ki}\binom{n-(j-ki)}{ki}g_{i,k}
$$

组合数代表在剩余的人中选择 $ki$ 个人来完成人数为 $i$ 的组的填充，$g_{i,k}$ 代表将 $ki$ 个人分成 $k$ 组，一组 $i$ 个人的方案数。

其计算的过程是这样的：现在 $ki$ 个人中选择 $i$ 个人，再在 $(k-1)i$ 个人中选择 $i$ 个人……由于组之间不区分，因此最后除掉 $k!$ 去重。因此：

$$
g_{i,k}=\frac {\prod_{j=1}^k \binom{ji}{i}} {(ki)!}
$$

直接递推分子，分母在计算 $f$ 时除掉即可。由于枚举 $j$ 的时候是调和级数复杂度，因此时间复杂度为 $O(n^2\log n)$。

```cpp
#include <bits/stdc++.h>
using namespace std; 
const int P = 1000000007; 

int poww(int a, int b) {
    int r = 1; 
    for (; b; b >>= 1, a = 1ll * a * a % P) if (b & 1) r = 1ll * r * a % P; 
    return r; 
}

int n, a, b, c, d; 
int f[1005][1005]; // 人数为 i 的组，用了 j 人
int g[1005][1005]; 
int fac[1005], ifac[1005]; 
inline int C(int n, int m) {
    if (n < m) return 0; 
    return 1ll * fac[n] * ifac[m] % P * ifac[n - m] % P; 
}

int main(void) {
    cin >> n >> a >> b >> c >> d; 
    for (int i = fac[0] = 1; i <= n; ++i) fac[i] = 1ll * fac[i - 1] * i % P; 
    ifac[n] = poww(fac[n], P - 2); 
    for (int i = n - 1; i >= 0; --i) ifac[i] = 1ll * ifac[i + 1] * (i + 1) % P; 

    for (int i = 1; i <= n; ++i) {
        g[i][0] = 1; 
        for (int k = 1; k <= n; ++k)
            g[i][k] = 1ll * g[i][k - 1] * C(k * i, i) % P; 
    }

    f[a - 1][0] = 1; 
    for (int i = a; i <= b; ++i)
        for (int j = 0; j <= n; ++j) {
            f[i][j] = f[i - 1][j]; 
            for (int k = c; k <= d && k * i <= j; ++k) {
                int v = 1ll * g[i][k] * ifac[k] % P; 
                // printf("%d %d %d %d %d\n", i, k, g[i][k], ifac[k], v); 
                f[i][j] = (f[i][j] + 1ll * f[i - 1][j - k * i] * C(n - j + k * i, k * i) % P * v) % P; 
            }
        }
    cout << f[b][n] << "\n"; 
    return 0; 
}
```

---

## 作者：dengchengyu (赞：1)

## arc067_e

首先考虑我们每次新建 $k$ 个大小为 $j$ 的组，由于 $k\times j\le n$，所以合法的 $(j,k)$ 对的个数是调和级数 $O(n\ln n)$。 

那么设 $f_{i,j}$ 表示有 $i$ 个人已分好组，组的大小最大为 $j$，且以后分的组的大小一定大于 $j$ 的方案数。

那么转移就是枚举 $k,j$，得
$$
\text{calc}(k,j)\times \sum_{x<j}f_{i-1,x}\to f_{i+k\times j-1,j}
$$
其中 $k,j$ 表示新建了 $k$ 个大小为 $j$ 的组，$\text{calc}(x,y)$ 就表示从剩下的人中选出 $x\times y$ 个人，然后分成 $x$ 个无标号的大小为 $y$ 的组的方案数。

首先后面的和式可以前缀和优化。

考虑 $\text{calc}(x,y)$ 怎么计算，首先选出 $x\times y$ 个人 $\binom{n-i+1}{x\times y}$。
我们先把这些人排列 $(x\times y)!$，然后每 $y$ 个人分一组，除去组内的顺序 $(y!)^{-x}$，除去组的标号 $(x!)^{-1}$。即
$$
\text{calc}(x,y)=\frac{\binom{n-i+1}{x\times y}(x\times y)!}{(y!)^x\times x!}
$$
组合数可以用预处理阶乘，于是预处理 $\text{calc}(x,y)$ 可以做到 $O(n^2\log n)$。

初始状态 $f_{0,0}=1$，答案为 $\sum_j f_{n,j}$。

最终时间复杂度为 $O(n^2\log n)$ 或 $O(n^2\log^2n)$。

AC 代码：

```cpp
const int N=1e3+5;
const int mod=1e9+7;
int n,A,B,C,D;
int pow1(int x,int y){
	int res=1;
	for(;y;y>>=1,x=(ll)x*x%mod)if(y&1)res=(ll)res*x%mod;
	return res;
}
int fac[N],inv[N];
int c(int x,int y){
	return (ll)fac[x]*inv[y]%mod*inv[x-y]%mod;
}
int sol(int x,int y){
	return (ll)fac[x*y]*pow1(inv[y],x)%mod*inv[x]%mod;
}
int f[N][N];
signed main(){
	read(n,A,B,C,D);
	f[0][0]=1;
	fac[0]=1;
	inv[0]=1;
	fo(i,1,n)fac[i]=(ll)fac[i-1]*i%mod,inv[i]=pow1(fac[i],mod-2);
	fo(i,1,n){
		fo(j,1,n)(f[i-1][j]+=f[i-1][j-1])%=mod;
		fo(j,A,B){
			fo(k,C,D){
				if(j*k>n-i+1)break;
				(f[i+j*k-1][j]+=(ll)sol(k,j)*f[i-1][j-1]%mod*c(n-i+1,j*k)%mod)%=mod;
			}
		}
	}
	int ans=0;
	fo(i,0,n)(ans+=f[n][i])%=mod;
	cout<<ans;
	return 0;
}
```

---

## 作者：CQ_Bob (赞：1)

题解摘自 [CSP2024 前做题情况](https://www.luogu.com.cn/article/3yyu431w)。

## 分析

做完之后一看题解，发现好多题解的式子都有问题啊。这题还是太远古了。

考虑 DP。

根据题意就能直接定义状态函数并且正确的一题。定义状态函数 $f_{i,j}$ 表示到 $i$ 个人一组的组，一共分了 $j$ 个人的方案数。那么能够得到转移方程：$f_{i,j}=f_{i-1,j}+\sum\limits_{k=c}^{d}f_{i-1,j-k\times i}\times C_{n-j+k\times i}^{k\times i}\times \frac{\prod\limits_{w=1}^{k}C_{k\times i- (w-1)\times i}^{i}}{k!}$。其中 $f_{i-1,j}$ 表示 $F_i=0$ 的情况。$C_{n-j+k\times i}^{k\times i}$ 表示选出 $k\times i$ 个人的方案数。而 $\frac{\prod\limits_{w=1}^{k}C_{k\times i- (w-1)\times i}^{i}}{k!}$ 表示将这些人分成 $k$ 组的方案数，这里可以简化成 $\frac{\prod\limits_{w=1}^{k}C_{w\times i}^{i}}{k!}$。

考虑快速计算 $\prod\limits_{w=1}^{k}C_{w\times i}^{i}$。发现这是一个前缀积的形式，令 $s_{i,j}=\prod\limits_{k=1}^{i}C_{k\times j}^{j}$，则有：$s_{i,j}=s_{i-1,j}\times C_{i\times j}^{j}$。那么转移方程就可以写成：$f_{i,j}=f_{i-1,j}+\sum\limits_{k=c}^{d}f_{i-1,j-k\times i}\times C_{k\times i}^{n-j+k\times i}\times \frac{s_{k,i}}{k!}$。

因为 $\sum\limits_{k=c}^{d}f_{i-1,j-k\times i}\times V$ 是一个调和级数的形式，所以该算法的时间复杂度为 $O(n^2\log n)$。预处理 $C_{i,j}$ 即可。

## 代码

```cpp
il void solve(){
	for(re int i=0;i<N;++i)
	for(re int j=0;j<=i;++j)
		if(!j) C[i][j]=1;
		else C[i][j]=(C[i-1][j]+C[i-1][j-1])%p;
  	__[0]=1,inv[0]=qmi(1,p-2,p);
  	for(re int i=1;i<N;++i) __[i]=__[i-1]*i%p,inv[i]=qmi(__[i],p-2,p);
  	for(re int i=1;i<N;++i)
  	for(re int j=1;j*i<N;++j) s[i][j]=max(1ll,s[i-1][j])*C[i*j][j]%p;
  	n=rd,a=rd,b=rd,c=rd,d=rd;
  	f[a-1][0]=1;
  	for(re int i=a;i<=b;++i)
  	for(re int j=0;j<=n;++j){
  		f[i][j]=(f[i][j]+f[i-1][j])%p;
  		for(re int k=c;k<=d&&j-k*i>=0;++k){
  			f[i][j]=(f[i][j]+f[i-1][j-k*i]*C[n-j+k*i][k*i]%p*s[k][i]%p*inv[k]%p)%p;
		}
	}
	printf("%lld\n",f[b][n]);
    return ;
}
```

---

## 作者：yizhiming (赞：0)

提供一个式子和其他题解不太一样的做法。

## 题目大意

给定 $n,A,B,C,D$，求把 $n$ 个数分成若干组，满足每个组长度要 $A\leq len \leq B$，且长度为 $len$ 的组要 $C\leq cnt\leq S$，求本质不同的分组方案，两个方案不同当且仅当存在两个编号 $a,b$ 在一个方案中在一组，另一个方案不在同一组。

$1\leq n \leq 10^3$，$1\leq A,B,C,D \leq n$。

## 题目分析

我的思考方向是把整体状态拿出来，对于这种序列计数，可以考虑对 $cnt_i$ 数组计数，一般来说 $cnt_i$ 表示的就是长度为 $i$ 的某个状态的出现次数，满足相同 $i$ 状态不区分，譬如求序列众数之类的玩意，$cnt_i$ 就表示出现次数为 $i$ 的数的个数。

在本题我们设 $cnt_i$ 表示组的长度为 $i$ 的组的个数，假设确定了一个 $cnt$ 数组，要往里面填 $[1,n]$，这个式子是很容易得到的 $ans = \frac{n!}{\prod (i!)^{cnt_i}\times cnt_i!}$。

这个东西是怎么来的呢，首先每个组内部不区分，所以组内元素随意排列算一种方案，这里会除掉 $i!$，然后组不区分，你任意交换组的位置方案不变，所以是 $cnt_i!$。

大体上可以想象成把所有组从小到大排好，然后把 $[1,n]$ 的全排列都扔进去跑一遍分组，然后去掉本质相同。容易发现此时每个 $i$ 就是独立的。

因为 $n!$ 可以提出去，所以对 $cnt$ 数组做计数，我们要满足的条件就是 $\sum cnt_i = n,cnt_i=0$ 或者 $C\leq cnt_i \leq D$，以及所有 $cnt_i$ 不为 $0$ 的 $i$，都满足 $A\leq i \leq B$。

设 $f_{i,j}$ 表示当前已经花费了 $i$ 个数，当前已经填了的最大分组大小为 $j$，转移就枚举当前组大小要选多少个，此时上面那个式子去掉 $n!$ 的系数之后所有方案的和。

$f_{i,j} = [A\leq j \leq B]\sum\limits_{k=C}^D \sum\limits_{l=0}^{j-1} f_{i-jk,l}\times (\frac{1}{j!})^k\times \frac{1}{k!}$。

前缀和优化一下就不用枚举 $l$ 了，然后我们对于第二维需要枚举 $O(\frac{i}{j})$ 的 $k$，显然是调和级数，总复杂度 $O(n^2\log n)$，转移时候的次幂不需要快速幂。

## code


```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <queue>
#include <vector>
#define int long long
using namespace std;
int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int N = 1e3+5;
const int Mod = 1e9+7;
int n,A,B,C,D;
int ksm(int x,int y){
	int res = 1;
	while(y){
		if(y&1){
			res = res*x%Mod;
		}
		y>>=1;
		x = x*x%Mod;
	}
	return res;
}
void add(int &x,int y){
	x+=y;
	x-=(x>=Mod)*Mod;
}
int f[N][N],jc[N],inv[N];
signed main(){
	n = read();A = read();B = read();C = read();D = read(); 
	jc[0] = inv[0] = 1;
	for(int i=1;i<=n;i++){
		jc[i] = jc[i-1]*i%Mod;
		inv[i] = ksm(jc[i],Mod-2);
	}
	for(int i=0;i<=B;i++){
		f[0][i] = 1;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=B;j++){
			int mi = inv[j];
			if(j>=A){
				for(int k=1;k*j<=i;k++){
					if(k>=C&&k<=D){
						add(f[i][j],f[i-k*j][j-1]*mi%Mod*inv[k]%Mod);
					}
					mi = mi*inv[j]%Mod;
				}
			}
			add(f[i][j],f[i][j-1]);
		}
	}
	int ans = f[n][B]*jc[n]%Mod;
	cout<<ans<<"\n";
	return 0;
}
```

---

## 作者：HomuraAkemi (赞：0)

考虑枚举大小为 $i$ 的集合选了 $j$ 个。

相同大小的集合是不区分顺序的，系数是 $\dfrac{(ij)!}{(i!)^jj!}$（也就是 $\displaystyle {ij\choose \underset{j\text{ 个}}{i,\cdots,i}}\frac{1}{j!}$）。

然后，令大小为 $i$ 的集合里面选了 $c_i$ 个元素，这又是一个多重组合数，就是 $\displaystyle{n\choose c_a,\cdots,c_b}$。

然后令 $f(z)$ 为答案的 EGF，立刻得到

$$f(z)=\prod_{a\le i\le b} \left(1+\sum_{c\le j\le d}\frac{z^{ij}}{(i!)^jj!}\right)$$

直接暴力卷积即可，由于中间是调和级数，复杂度是对的。时间复杂度 $\Theta(\mathrm{polylog}(n^2))$。

---

## 作者：Register_int (赞：0)

首先有 $ik$ 个人平均分 $k$ 不区分组的方案数为：

$$
\begin{aligned}
&\dfrac1{(ik)!}\prod^k_{j=1}\dbinom{ij}{i}\\
=&\dfrac1{(ik)!}\prod^k_{j=1}\frac{(ij)!}{i!(ij-i)!}\\
=&\frac{(ik)!}{i!^kk!}
\end{aligned}
$$

设 $dp_{i,j}$ 表示分到人数为 $i$，用了 $j$ 个人，有转移：

$$
\begin{aligned}
dp_{i,j}&=dp_{i-1,j}+\sum^D_{k=C}\dbinom{n-j+ik}{ik}\dfrac{(ik)!}{i!^kk!}dp_{i-1,j-ik}\\
&=dp_{i-1,j}+\sum^D_{k=C}\dfrac{(n-j+ik)!}{(ik)!(n-j)!}\dfrac{(ik)!}{i!^kk!}dp_{i-1,j-ik}\\
&=dp_{i-1,j}+\sum^D_{k=C}\dfrac{(n-j+ik)!}{i!^kk!(n-j)!}dp_{i-1,j-ik}\\
\end{aligned}
$$

第三维枚举量是调和级数，时间复杂度 $O(n^2\log n)$。数组第一维可以滚掉。

# AC 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 1e3 + 10;
const int mod = 1e9 + 7;

inline 
ll qpow(ll b, ll p) {
	ll res = 1;
	for (; p; b = b * b % mod, p >>= 1) if (p & 1) res = res * b % mod;
	return res;
}

int n, a, b, c, d;

ll dp[MAXN], fac[MAXN], ifac[MAXN];

int main() {
	scanf("%d%d%d%d%d", &n, &a, &b, &c, &d), *fac = 1, *dp = 1;
	for (int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % mod;
	ifac[n] = qpow(fac[n], mod - 2);
	for (int i = n; i; i--) ifac[i - 1] = ifac[i] * i % mod;
	for (int i = a; i <= b; i++) {
		for (int j = n; ~j; j--) {
			for (int k = c; k <= d && k <= j / i; k++) {
				dp[j] = (dp[j] + fac[n - j + i * k] * qpow(ifac[i], k) % mod * ifac[k] % mod * ifac[n - j] % mod * dp[j - i * k]) % mod;
			}
		}
	}
	printf("%lld", dp[n]);
}
```

---

## 作者：_edge_ (赞：0)

挺好的计数题，但是有一步还是需要学长来教我一下 qwq。

挺显然的，我们设 $f_{i,j}$ 表示前 $i$ 个人的组已经用了 $j$ 个人。

就是 $i$ 是从 $[a,b]$ 枚举，然后我们考虑转移。

一种简单的想法就是枚举当前这组有多少个 $k$ 在 $[c,d]$ 的 $k$。

然后我们考虑如何在剩下的数里面挑出来一些数，使得他们变成符合条件的组数。

问题转化为给定若干不同的球，把他们装进同样的盒子里面，然后求方案数，每个盒子装的必须一样。

我们可以把球先重排一下，然后对于组内的不能重排就除以 $(\dfrac{n}{m}!)^m$，每个组都本质相同，不能重排于是再除以 $m!$ ，然后选择是从原序列里面选择 $n$ 个。

然后我们发现这样复杂度好像有点不太对，但是进一步优化的话这个 $k$ 的上界是一个类似于调和级数的东西，事实上它是 $O(n^2 \log^2 n)$，还有一个 $\log$ 是内部的快速幂。

```cpp
#include <bits/stdc++.h>
#define int long long 
using namespace std;
const int INF=1005;
const int INFN=1e6+5;
const int Mod=1e9+7;
int fav[INFN],ifav[INFN],f[INF][INF],a,b,c,d,n;

int ksm(int x,int y) {
	int ba=x%Mod,ans=1;
	while (y) {
		if (y&1) ans=(ans*ba)%Mod;
		ba=(ba*ba)%Mod;y>>=1;
	}
	return ans;
}
int C(int x,int y) {
	if (x-y<0) return 0;
	return fav[x]*ifav[y]%Mod*ifav[x-y]%Mod;
}
void init() {
	int N=1e5;fav[0]=1;
	for (int i=1;i<=N;i++) fav[i]=fav[i-1]*i%Mod;
	ifav[N]=ksm(fav[N],Mod-2);
	for (int i=N-1;~i;i--) ifav[i]=ifav[i+1]*(i+1)%Mod;
	return ;
}
int solve(int x,int y,int z) {
	int sum=fav[y*z];
	sum*=ksm(ksm(fav[y],z),Mod-2);sum%=Mod;
	sum*=ksm(fav[z],Mod-2);sum%=Mod;
	// for (int i=1;i<=z;i++)	
	// 	sum*=ifav[y],sum%=Mod;
	// for (int i=1;i<=z;i++)
	// 	sum*=C(x,y),x-=y,sum%=Mod;
	// if (x<0) return 0;
	return C(x,y*z)%Mod*sum%Mod;
}
signed main()
{
	ios::sync_with_stdio(false);
	init();
	cin>>n>>a>>b>>c>>d;
	f[a-1][0]=1;
	for (int i=a;i<=b;i++) {
		for (int j=0;j<=n;j++) {
			for (int k=c;k<=min(d,(j)/i);k++) {
				f[i][j]+=f[i-1][j-k*i]*solve(n-(j-k*i),i,k)%Mod,f[i][j]%=Mod;
			}
			f[i][j]+=f[i-1][j];
			f[i][j]%=Mod;
			// cout<<i<<" "<<j<<" "<<f[i][j]<<" ??\n";
		}
	}
	cout<<f[b][n]<<"\n";
	return 0;
}
```


---

## 作者：小木虫 (赞：0)

### Preface  
好题好题。  
### Problem  

有 $N$ 个人，编号依次是 $1,2,\cdots ,N$, 现在要将他们分成若干组，满足：

- 每一组的人数均在 $[A,B]$ 之间。

- 记$F_i$为当前分组方案中人数为$i$的组的数量，则 $F_i$ 应满足 $F_i=0$ 或   $C\leq F_i\leq D$.

其中 $A,B,C,D$ 均为给定值。

求本质不同的分组方案数对 $10^9+7$ 取模后的结果。两种方案是本质不同的当且仅当存在两个人使得在第一种方案中他们在同一组，而在第二种方案中不是。

数据范围：$1\leq N\leq 10^3,1\leq A\leq B\leq N,1\leq C\leq D\leq N$  
### Solution  
数据范围支持 $O(n^2)$，同时发现这个问题很有规律可以进行 dp。   
于是我们直接设 dp 状态为 $dp_{x,y}$，表示选到人数为 $x$ 的组且还剩 $y$ 个互不相同的人待分配。  
得出状态转移方程为：  
$$dp_{x,y}=\sum _{i=c}^{i\leq d}(\prod _{j=1}^{j\leq i}C^x_{y-x*(j-1)})dp_{x+1,y-xi}×\frac{1}{i!}$$  
最后乘以 $\frac{1}{i!}$ 是因为确定每组中元素后同样的组的组合会有 $i!$ 个。  

其中 $j$ 的连乘可以被优化。  
然后这个柿子的复杂度就大概变成了：  
$$O(n^2\sum_{i=a}^{i\leq b}\frac{n}{i})$$  
根据调和级数，复杂度大致为：  $O(n^2\log n)$  
可以通过本题。
code：  
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1010;
const ll mod=1e9+7;
ll n,a,b,c,d;ll x,y;
ll dp[N][N];ll f[N];ll inv[N];bool vis[N][N];
void exgcd(ll a,ll b){
  	if(!b){x=1,y=0;return;}
  	exgcd(b,a%b);ll t=x;
  	x=y,y=t-a/b*y;
}
ll C(int x,int y){
	if(x==y||y==0)return 1;
	return (f[x]*inv[y]%mod*inv[x-y]%mod)%mod;
}
ll dfs(int x,int y){
	//printf("%d %d\n",x,y);
	if(y==0&&x==b+1)return 1;
	if(x==b+1)return 0;
	if(vis[x][y])return dp[x][y];
	vis[x][y]=true;dp[x][y]+=dfs(x+1,y);ll tmp=1;
	for(int i=1;i<=d;i++){
		if(x*i>y)break;
		tmp*=C(y-x*(i-1),x);tmp%=mod;
		if(i>=c){
			dp[x][y]+=((dfs(x+1,y-x*i)*tmp%mod)*inv[i])%mod;
			dp[x][y]%=mod;
		}
	}return dp[x][y];
}
int main(){
	scanf("%lld%lld%lld%lld%lld",&n,&a,&b,&c,&d);
	f[0]=1;
	for(int i=1;i<=n;i++){
		f[i]=f[i-1]*i;f[i]%=mod;
		exgcd(f[i],mod);
		inv[i]=(x%mod+mod)%mod;
	}
	printf("%lld",dfs(a,n));
	return 0;
}
```


---

