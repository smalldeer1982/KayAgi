# VLATTICE - Visible Lattice Points

## 题目描述

Consider a N\*N\*N lattice. One corner is at (0,0,0) and the opposite one is at (N,N,N). How many lattice points are visible from corner at (0,0,0) ? A point X is visible from point Y iff no other lattice point lies on the segment joining X and Y.   
   
Input :   
The first line contains the number of test cases T. The next T lines contain an interger N   
   
Output :   
Output T lines, one corresponding to each test case.   
   
Sample Input :   
3   
1   
2   
5   
   
Sample Output :   
7   
19   
175   
   
Constraints :   
T <= 50   
1 <= N <= 1000000

# 题解

## 作者：lrqcs (赞：12)

无需用到莫比乌斯反演，可能是这个题最简单的做法了。

首先设每个点的坐标为 $(x,y,z)$，再将 $\max(x,y,z)$ 的值相同的点分为一组。  
不难发现，这就相当于把题面中给定的正方体拆成很多层。

然后对于每一层进行讨论：

设 $(0,0,0)$ 所在的层为第 $0$ 层。

根据正方体公式可知第 $x$ 层的点数为 $(x+1)^3-x^3$，化简可得 $3x^2+3x+1$。

对于点 $(x,y,z)$，发现其会遮挡 $\forall k\in\mathbb{N^*},k\geq2,(kx,ky,kz)$ 对应点。

所以第 $x$ 层的有效点数为 $3x^2+3x+1-$ 该层所有被遮挡的点的数量。

观察到对于 $\forall k\in\mathbb{N^*},k\geq2,(kx,ky,kz)$ 对应点，它能遮挡的点都会被点 $(x,y,z)$ 遮挡，所以已被遮挡的点对于任何一层无贡献。

可设 $dp_i$ 表示第 $i$ 层未被遮挡的点数，则 $dp_i=3i^2+3i+1-\sum_{d|i\wedge d<i}{dp_d}$

则对于 $(0,0,0)$ 到 $(n,n,n)$ 的正方体，答案为 $\sum_{i=1}^{n}dp_i$。
对于 $dp$ 数组的建立，运用类似普通筛的筛法可做到 $O(n\log n)$，对答案进行前缀和预处理，查询时 $O(1)$ 查询，总时间复杂度为 $O(n\log n+T)$，空间复杂度为 $O(n)$，稍劣于莫比乌斯反演写法，但仅仅使用加减乘及位运算，常数更小也更好写。

代码：
```cpp
#include<stdio.h>
#define int long long
#define N 1000000
int n,ans[N+40];
signed main(){
	for(int i=1;i<=N;++i){
		ans[i]+=3*i*i+3*i+1;//注意是+=而非=，因为ans[i]在这之前可能被修改过
		for(int j=i<<1;j<=N;j+=i)
			ans[j]-=ans[i];
	}
	for(int i=1;i<N;++i)
		ans[i+1]+=ans[i];
	int T;scanf("%lld",&T);
	while(T--){
		scanf("%lld",&n);
		printf("%lld\n",ans[n]);
	}
}
```

实际上这个做法可以方便的扩展到多维：  
对于 $x$ 维空间，起始点坐标都为 $0$，终点坐标都为 $n$ 的情况下，只需更改第 $7$ 行为 `ans[i]+=fpow(i+1,x)-fpow(i,x);` 即可，其中 `fpow` 为快速幂。（当然有时也要取模）

---

## 作者：TKXZ133 (赞：7)

[Visible Lattice Points](https://www.luogu.com.cn/problem/SP7001)

### 题目大意

给定一个 $N×N×N$ 的由若干点组成的立方体，点的坐标从 $(0,0,0)$ 到 $(N,N,N)$，求从点 $(0,0,0)$ 处可以看见多少个点。

### 思路分析

我们将立方体上的点分成三类：

- 在 $xy,yz,xz$ 平面上的点。
- 在 $x,y,z$ 轴上的点。
- 即不在平面，也不在坐标轴上的点。

就可以简单得出我们需要求的式子：

$$\sum_{i=1}^n\sum_{j=1}^n\sum_{k=1}^n[\gcd(i,j,k)=1]+3\sum_{i=1}^n\sum_{j=1}^n[\gcd(i,j)=1]+3$$

然后就可以开始愉快的颓柿子了：

$$\begin{aligned}&\sum_{i=1}^n\sum_{j=1}^n\sum_{k=1}^n[\gcd(i,j,k)=1]\\&=\sum_{d=1}^n\mu(d)\sum_{i=1}^n\sum_{j=1}^n\sum_{k=1}^n[d|i][d|j][d|k]\\&=\sum_{d=1}^n\mu(d)\lfloor\frac{n}{d}\rfloor^3\end{aligned}$$

类似的，

$$\begin{aligned}&\sum_{i=1}^n\sum_{j=1}^n[\gcd(i,j)=1]\\&=\sum_{d=1}^n\mu(d)\sum_{i=1}^n\sum_{j=1}^m[d|i][d|j]\\&=\sum_{d=1}^n\mu(d)\lfloor\frac{n}{d}\rfloor^2\end{aligned}$$

因此，我们的答案就是：

$$3+\sum_{d=1}^n\mu(d)\lfloor\frac{n}{d}\rfloor^2(\lfloor\frac{n}{d}\rfloor+3)$$

只需要线性筛出 $\mu$ 的前缀和，再通过整除分块就可以在 $O(\sqrt n)$ 的时间复杂度内得出结果。

### 代码：

```
#include <bits/stdc++.h>
using namespace std;
const int N=1111111,L=1000000;
#define int long long\\好习惯

int T,n,ans,cnt;
int v[N],prime[N],mu[N];

void sieve(){
    mu[1]=1;
    for(int i=2;i<=L;i++){
        if(!v[i]){prime[++cnt]=i;mu[i]=-1;}
        for(int j=1;j<=cnt&&i*prime[j]<=L;j++){
            v[i*prime[j]]=1;
            if(i%prime[j]==0) break;
            mu[i*prime[j]]=-mu[i];
        }
    }
    for(int i=1;i<=L;i++) mu[i]+=mu[i-1];\\计算前缀和
}

signed main(){
    sieve();
    scanf("%lld",&T);
    while(T--){
        scanf("%lld",&n);
        ans=0;
        for(int l=1,r;l<=n;l=r+1){//简单的整除分块
            r=n/(n/l);
            ans+=(mu[r]-mu[l-1])*((n/l)*(n/l)*(3+(n/l)));\\根据式子计算结果
        }ans+=3;
        cout<<ans<<'\n';
    }
    return 0;
}
```

---

## 作者：yuzhechuan (赞：4)

简单的莫比乌斯反演题

---

### 题解：

首先这道题有个众所周知的可以用欧拉函数水过的二维版本[P2158仪仗队](https://www.luogu.com.cn/problem/P2158)

先摆出二维版本的简单解析：

初步分析：答案分成“两个坐标轴”和“一个面”两部分
**（那个常数2和3是坐标轴的贡献，下同）**

$$ans=2+\sum\limits_{i=1}^{n}\sum\limits_{j=1}^{n}[\gcd(i,j)=1]$$

设：

$$f(x)=\sum\limits_{i=1}^{n}\sum\limits_{j=1}^{n}[\gcd(i,j)=x]$$

$$g(x)=\sum\limits_{x\mid y}f(y)=\left \lfloor \frac{n}{x} \right \rfloor^{2}$$

根据莫比乌斯反演：

$$f(x)=\sum\limits_{x\mid y}\mu (\left \lfloor \frac{y}{x} \right \rfloor)\cdot g(y)=\sum\limits_{x\mid y}\mu (\left \lfloor \frac{y}{x} \right \rfloor)\cdot \left \lfloor \frac{n}{y} \right \rfloor^{2}$$

所以答案就是：

$$ans=2+f(1)=2+\sum\limits_{i=1}^{n}\mu (i)\cdot \left \lfloor \frac{n}{i} \right \rfloor^{2}$$

---

再来看三维的情况，基本相同，只是答案由“三个坐标轴”，“三个面”和“一个体”组成:

$$ans=3+3*p+\sum\limits_{i=1}^{n}\sum\limits_{j=1}^{n}\sum\limits_{k=1}^{n}[\gcd(i,j,k)=1]$$

其中$p$是一个面上的贡献，上面已经算出，即$p=\sum\limits_{i=1}^{n}\mu (i)\cdot \left \lfloor \frac{n}{i} \right \rfloor^{2}$，我们先放着不管，只考虑后半部分

（与二维几乎一模一样）设：

$$f(x)=\sum\limits_{i=1}^{n}\sum\limits_{j=1}^{n}\sum\limits_{k=1}^{n}[\gcd(i,j,k)=x]$$

$$g(x)=\sum\limits_{x\mid y}f(y)=\left \lfloor \frac{n}{x} \right \rfloor^{3}$$


根据莫比乌斯反演：

$$f(x)=\sum\limits_{x\mid y}\mu (\left \lfloor \frac{y}{x} \right \rfloor)\cdot g(y)=\sum\limits_{x\mid y}\mu (\left \lfloor \frac{y}{x} \right \rfloor)\cdot \left \lfloor \frac{n}{y} \right \rfloor^{3}$$

（好像只改了个指数呢）所以答案就是：

$$ans=3+3*p+f(1)$$

$$ans=3+3*\sum\limits_{i=1}^{n}\mu (i)\cdot \left \lfloor \frac{n}{i} \right \rfloor^{2}+\sum\limits_{i=1}^{n}\mu (i)\cdot \left \lfloor \frac{n}{i} \right \rfloor^{3}$$

$$ans=3+\sum\limits_{i=1}^{n}\mu (i)\cdot \left \lfloor \frac{n}{i} \right \rfloor^{2}\cdot (3+\left \lfloor \frac{n}{i} \right \rfloor)$$

照着答案式子打，我们便得到了复杂度$O(tn)$的代码：

```cpp
	ans=3;
	for(int i=1;i<=n;i++)
		ans+=mu[i]*(pow(n/i,3)+3*pow(n/i,2));
```

接着注意到答案的式子还可以经典地整除分块一下，记个$\mu$的前缀和，接着便有了下面的代码，复杂度降为$O(t\sqrt{n})$：

---

### 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
template<class t> inline t read(t &x){
	char c=getchar();bool f=0;x=0;
	while(!isdigit(c)) f|=c=='-',c=getchar();
	while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
	if(f) x=-x;return x;
}
template<class t> inline void write(t x){
	if(x<0) putchar('-'),write(-x);
	else{if(x>9) write(x/10);putchar('0'+x%10);}
}

const int N=1e6+5;
bool v[N];
int p[N],pn,mu[N],pre[N];

void muin(int n){
	mu[1]=1;
	for(int i=2;i<=n;i++){
		if(!v[i]){
			p[++pn]=i;
			mu[i]=-1;
		}
		for(int j=1;j<=pn&&p[j]*i<=n;j++){
			v[i*p[j]]=1;
			if(i%p[j]) mu[i*p[j]]=-mu[i];
			else{
				mu[i*p[j]]=0;
				break;
			}
		}
	}
	for(int i=1;i<=n;i++) pre[i]=pre[i-1]+mu[i]; //前缀和
}

void doit(){
	int n;
	long long ans=0;
	read(n);
	for(int l=1,r;l<=n;l=r+1){
		r=n/(n/l); //块的左右边界
		ans+=1ll*(pre[r]-pre[l-1])*((n/l)+3)*(n/l)*(n/l); //代入公式
	}
	write(ans+3);puts(""); //最后的坐标轴贡献
}

signed main(){
	muin(1e6);
	int t;
	read(t);
	while(t--) doit();
}
```

---

## 作者：Fatalis_Lights (赞：2)

**题目传送门：** [Link](https://www.luogu.com.cn/problem/SP7001)

**题意简述：**

> 求

> $$\sum_{i=1}^n\sum_{j=1}^n\sum_{k=1}^n[\gcd(i,j,k)==1]+3\sum_{i=1}^n\sum_{j=1}^n[\gcd(i,j)==1]+3$$

> （不取模，共 $T$ 组数据，$1\leq T\leq50,1 \leq n \leq 1000000$）

## Solution

老套路题了，[P2158 的三维版](https://www.luogu.com.cn/problem/P2158)。

直接颓柿子吧，先看第一坨：

$$\sum_{i=1}^n\sum_{j=1}^n\sum_{k=1}^n[\gcd(i,j,k)==1]$$

显然可以得出：

$$\sum_{i=1}^n\sum_{j=1}^n\sum_{k=1}^n\sum_{d|\gcd(i,j,k)}\mu(d)$$

把 $d$ 提到前面来：

$$\sum_{d=1}^n\mu(d)*[\frac{n}{d}]^3$$

第二坨只需要把指数改一改就行了，推柿子的过程一模一样。

所以原式变为：

$$\sum_{d=1}^n\mu(d)*[\frac{n}{d}]^2*([\frac{n}{d}]+3)+3$$

$\mu(d)$ 的前缀和可线性筛，整个式子可整除分块。时间复杂度 $\Theta(T\sqrt{n})$ 。

code:

```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 1000009
using namespace std;

ll pri[N],vst[N],mu[N],sum[N];
ll n,t;

inline ll read(){
    ll x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}

inline void print(ll x){
    if(x<0)putchar('-'),x=-x;
    if(x>9)print(x/10);
    putchar(x%10+'0');
}

void init(ll n){
	mu[1]=1;
	for(ll i=2;i<=n;i++){
		if(!vst[i]) pri[++pri[0]]=i,mu[i]=-1;
		for(ll j=1;j<=pri[0] && i*pri[j]<=n;j++){
			vst[i*pri[j]]=1;
			if(i%pri[j]==0){
                mu[i*pri[j]]=0; 
                break; 
            }
			mu[i*pri[j]]=-mu[i];
		}
	}
	for(ll i=1;i<=n;i++) sum[i]=sum[i-1]+mu[i];
}

inline ll f(ll n){
	ll res=0;
	for(int left=1,right;left<=n;left=right+1){
		right=n/(n/left);
		res+=(sum[right]-sum[left-1])*((n/left)+3)*(n/left)*(n/left);
	}
	return res;
}

int main(){
    t=read();
    init(1000009);
    while(t--){
        n=read();
        print(f(n)+3);
        puts("");
    }
    return 0;
}
```

---

## 作者：Drifterming (赞：2)

$\quad$就是把那道[P2158 \[SDOI2008\]仪仗队](https://www.luogu.org/problemnew/show/P2158)从二维扩展到了三维。
我们发现，对于交在$(0,0,0)$处的三个平面，它与二维的是一样的，我们把$(0,0,1),(0,1,0),(1,0,0)$三点先拿出来，剩下的就变成了三个$N*N$的平面和一个$N*N*N$的立方体。
$\quad$我们仍然从斜率入手，三个平面的与二维的相同。对于立方体，如果一个点$(x,y,z)$没有被遮挡，那说明它是方向向量$(x,y,z)$的基线(这儿把它看成是有方向的直线)上的第一个点，且$(x,y,z)$是第一个点当且仅当$\gcd(x,y,z)=1$，否则$(x,y,z)$就是$g(x',y',z')$，会被$(x',y',z')$遮挡。所以，三个面和一个立方体的贡献就是
$$3\sum_{i=1}^n\sum_{j=1}^n [\gcd(i,j)=1]+\sum_{i=1}^n \sum_{j=1}^n \sum_{k=1}^n [\gcd(i,j,k)=1]$$
那么这个式子我们可以很轻易的化成
$$3\sum_{d=1}^n \mu(d) \left( \lfloor \frac{n}{d} \rfloor \right)^2 + \sum_{d=1}^n\mu(d) \left( \lfloor \frac{n}{d} \rfloor \right)^3$$
所以
$$Ans=3+3\sum_{i=1}^n\sum_{j=1}^n [\gcd(i,j)=1]+\sum_{i=1}^n \sum_{j=1}^n \sum_{k=1}^n [\gcd(i,j,k)=1]$$
于是我们就筛出$\mu$的前缀和，然后数论分块即可在$O(N+T\sqrt{n})$内出解。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;

typedef long long LL;

inline int read()
{
	char c=getchar();int num=0;
	for(;!isdigit(c);c=getchar());
	for(;isdigit(c);c=getchar())
		num=num*10+c-'0';
	return num;
}

const int MXN=1e6+5;
const int mod=1000000007;

int prime[MXN],cnt;bool ntp[MXN];
int mu[MXN];
void init()
{
	mu[1]=1;LL t;
	for(int i=2;i<MXN;++i)
	{
		if(!ntp[i])
			prime[++cnt]=i,mu[i]=-1;
		for(int j=1;j<=cnt&&(t=1ll*i*prime[j])<MXN;++j)
		{
			ntp[t]=1;
			if(i%prime[j]==0)
			{
				mu[t]=0;
				break;
			}
			mu[t]=-mu[i];
		}
		mu[i]+=mu[i-1];
	}
}

int main()
{
	init();
	int T=read();
	while(T--)
	{
		int N=read();
		if(N<1)
		{
			puts("0");
			continue;
		}
		LL ans=3;
		for(int l=1,r;l<=N;l=r+1)
		{
			r=N/(N/l);
			ans+=1ll*(mu[r]-mu[l-1])*(N/l)*(N/l)*(N/l);
			ans+=3ll*(mu[r]-mu[l-1])*(N/l)*(N/l);
		}
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：替罪羊树 (赞：2)

# 题目描述
一共T组数据，每组数据一个整数n，表示有一个大小为$n^3$的正方体。求：在(0,0,0)位置能够看到多少个不被遮挡的点(i,j,k)

特别地，i，j，k均为整数。

### 思路
不妨从二维的情况开始考虑。事实上，这道题目的确有二维形式。

[POJ3090 Visible Lattice Points](http://poj.org/problem?id=3090)

不妨这样想，点(i,j)为什么会被看到？是因为它和(0,0)的连线上面没有点了。我们知道这条直线的斜率为$$\frac{j-0}{i-0}=\frac{j}{i}$$
这说明j和i的最大公因数为1，i，j互质。

那么这道题就成了对于每一个$s<=n$，求得所有小于等于s的与s互质的数字的个数，而这就是求欧拉函数
$\varphi(s)$的值，乘以2，再去除被计算两次的点(1,1).
所以$ans=2*\sum_{s=1}^{n}\varphi(s)-1$，利用线性筛求得n以内所有欧拉函数的值即可。

### 升维打击！
多了一维，思路保持不变。对于所有的i，j，k，我们要找出一共有多少种情况，使得$gcd(i,j,k)=1$.我们可以这样表达这个公式:
- $g(n)=\sum_{i=1}^{n}\sum_{j=1}^{n}\sum_{k=1}^{n}pd(i,j,k)$
- 其中当且仅当$gcd(i,j,k)=1$时$pd(i,j,k)=1$,否则为0.

显然，我们可以利用三重循环暴力枚举ijk，再用$log_{2}n$的时间完成gcd，但是在$n=1000000$多组数据的情况下分分钟就T飞了！于是我们来考虑一下新的算法：
### 变换大法+数学~~乱搞~~
如果现在有一个函数$f(x)$,满足如下条件：
- $f(n)=\sum_{i=1}^{N}\sum_{j=1}^{N}\sum_{k=1}^{N}pd(i,j,k)$
- 其中当且仅当$gcd(i,j,k)=n$时$pd(i,j,k)=1$,否则为0.

很容易看出这个函数表示在0-N范围内有多少对公因数为n的三数对。
很显然$f(1)$就是我们要求的数值。
但是这个函数看起来不好求啊？？

请看：

---
## 莫比乌斯反演变换
定义：如果有$F(n)=\sum_{d|n}f(d)(d|n$表示d整除n$)$

那么必然能够得到$f(n)=\sum_{d|n}μ(\frac{n}{d})F(d)$

这被称作莫比乌斯反演公式，其中$μ()$函数代表莫比乌斯函数。关于这个函数，我们需要知道的是：
如果给出一个合数p的标准分解式：$p=p_1^{α_1}p_2^{α_2}...p_m^{α_m}$
那么就有


$μ(p)=\begin{cases} 1 && {p=1}\\ (-1)^m && each         α=1\\ 0 &&otherwise\end{cases}$

这是莫比乌斯函数的定义公式

---
### 定义函数，进行反演
经验告诉我们，$f(n)$的选取常常与等于有关，而$F(n)$的选取通常与整除有关。
这里，我们定义：
- $f(n)=\sum_{i=1}^{N}\sum_{j=1}^{N}\sum_{k=1}^{N}pd(i,j,k)$
- 其中当且仅当$gcd(i,j,k)=n$时$pd(i,j,k)=1$,否则为0.

那么相应地，我们这样定义大F(n)
- $F(n)=\sum_{i=1}^{N}\sum_{j=1}^{N}\sum_{k=1}^{N}pd(i,j,k)$
- 其中当且仅当${n}\equiv 0\mod{gcd(i,j,k)} $时$pd(i,j,k)=1$,否则为0.那么我们知道$gcd(i,j,k)$必须是n的因数。

好了，很容易推导出：$F(n)=\sum_{d|n}f(d)$

莫比乌斯反演变换后得到$f(n)=\sum_{d|n}μ(\frac n d)F(d).$

接下来我们对这个式子做一点处理。因为要求得$f(1)$的值，我们令$n=1$，得到$f(1)=\sum_{d=1}^Nμ(d)F(d)=\sum_{d}μ(d)\sum_{i=1}^{N}\sum_{j=1}^{N}\sum_{k=1}^{N}pd(i,j,k).$

对右边部分处理。不妨设$i=ad,j=bd,k=cd$,那么d一定是从1到N的。对于每一个d，abc都只能是1-[N/d]中的某一个，因此可得$F(d)={[\frac N d]}^3$.如果是二维，同理可得$F(d)={[\frac N d]}^2$

考虑到N的因数只有$\sqrt N$个，我们可以在线性筛莫比乌斯函数的时候预处理莫比乌斯函数的前缀和。利用整除分块，对$[\frac N d]$相同的d进行组合处理.至此，本题得解。最终的答案应该是立体处理+三个平面的处理（分别是$x=0, y=0, z=0$）+$(0,1,1),(1,1,0),(1,0,1)$三个点.

$ans=\sum_{d=1}^Nμ(d)({[\frac N d]}^2([\frac N d]+1))+3$

总的时间复杂度为$O(T\sqrt N)$,不用整除分块是$O(TN)$,本来是过不掉的，但是~~数据似乎太水了~~
```
#include<bits/stdc++.h>
using namespace std;
inline int re()
{
    int n=0,k=1;
    char c=getchar();
    while(c>'9'||c<'0'){if(c=='-') k=-1; c=getchar();	}
    while(c<='9'&&c>='0'){n=(n<<1)+(n<<3)+(c^48); c=getchar();	}
    return n*k;
}
bool pd[10010010];
int prime[10010010];
int miu[10010010];
int he[10010010];
inline int shai(int n)
{
    int tot=0;
    memset(pd,true,sizeof(pd));
    miu[1]=1;
    he[1]=1;
    for(int i=2;i<=n;i++)
    {
        if(pd[i])
        {
            prime[++tot]=i;
            miu[i]=-1;
        }
        for(int j=1;j<=tot&&i*prime[j]<=n;j++)
        {
            pd[i*prime[j]]=false;
            if(i%prime[j]==0){miu[i*prime[j]]=0;break;}
            else miu[i*prime[j]]=-miu[i];
        }
        he[i]=he[i-1]+miu[i];
    }
    return tot;
}
int n,T;
int main()
{
    T=re();
    shai(1001000);
    long long ans=0;
    while(T--)
    {
        n=re();
        ans=3ll;
        long long l=1,r;
        while(l<=n)
        {
            long long k=n/l;
            r=n/k;
            ans+=(he[r]-he[l-1])*k*k*(k+3);
            l=r+1;
        }		
        printf("%lld\n",ans);
    }
    return 0;
}
```

---

## 作者：dalao_see_me (赞：2)

题目传送门：[Link](https://www.luogu.com.cn/problem/SP7001)

注意：luogu 上可能交不上去，需要去 vjudge 上提交。
## 题目大意
求
$$
3+\sum_{i=1}^{n}\sum_{j=1}^{n}\sum_{k=1}^{n}[\gcd(i,j,k) = 1] + 3\times\sum_{i=1}^n\sum_{j=1}^{n}[\gcd(i,j) =1]
$$
的值。
## 做法
显然这是一个莫比乌斯反演。

我们先对
$$
\sum_{i=1}^{n}\sum_{j=1}^{n}\sum_{k=1}^{n}[\gcd(i,j,k) = 1]
$$
这个式子反演。
$$
\begin{aligned}
&\sum_{i=1}^{n}\sum_{j=1}^{n}\sum_{k=1}^{n}[\gcd(i,j,k) = 1]\\=&
\sum_{i=1}^{n}\sum_{j=1}^{n}\sum_{k=1}^{n}\sum_{d|\gcd(i,j,k)}\mu(d)\\=&
\sum_{d=1}^n\mu(d)\sum_{d|i}^n\sum_{d|j}^n\sum_{d|k}^n 1\\=&
\sum_{d=1}^n\mu(d)\sum_{i=1}^{\lfloor\frac{n}{d}\rfloor}\sum_{j=1}^{\lfloor\frac{n}{d}\rfloor}\sum_{k=1}^{\lfloor\frac{n}{d}\rfloor}1\\=&
\sum_{d=1}^n\mu(d)\lfloor\frac{n}{d}\rfloor^3
\end{aligned}
$$
显然，
$$
\begin{aligned}
&\sum_{i=1}^n\sum_{j=1}^{n}[\gcd(i,j) =1]\\=&
\sum_{d=1}^n\mu(d)\lfloor\frac{n}{d}\rfloor^2
\end{aligned}
$$
那么最终的柿子就是
$$
\sum_{d=1}^n\mu(d)\lfloor\frac{n}{d}\rfloor^2(\lfloor\frac{n}{d}\rfloor+3)
$$
整除分块一下就好了。~~虽然数据很水不整除分块也能过~~。
## 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e6;
int mu[N + 5], chk[N + 5], prime[N + 5];
int tot, _, n, ans;
inline void init() {
	mu[1] = 1;
	for (int i = 2; i <= N + 1; i++) {
		if (!chk[i]) {
			prime[++tot] = i;
			mu[i] = -1;
		}
		for (int j = 1; j <= tot && prime[j] * i <= N + 1; j++) {
			chk[prime[j] * i] = 1;
			if (i % prime[j] == 0) {
				mu[prime[j] * i] = 0;
				break;
			}
			mu[prime[j] * i] = -mu[i];
		}
	}
	for (int i = 2; i <= N; i++) mu[i] += mu[i - 1]; 
}
inline int read() {
	int x = 0, f = 1; char c = getchar();
	while (c < '0' || c > '9') {if (c == '-') f = -f; c = getchar();}
	while (c >= '0' && c <= '9') {x = (x << 3) + (x << 1) + (c ^ 48); c = getchar();}
	return x * f;
}
signed main() {
	init();
	_ = read();
	while (_--) {
		n = read();
		int l, r; ans = 0;
		for (l = 1; l <= n; l = r + 1) {
			r = n / (n / l);
			ans += (n / l) * (n / l) * (n / l + 3) * (mu[r] - mu[l - 1]);
		}
		printf("%lld\n", ans + 3);
	}
	return 0;
}
```

---

## 作者：Mihari (赞：1)

# 题目

[传送门](https://www.luogu.com.cn/problem/SP7001)

# 题解

这里有个[弱化版本](https://www.luogu.com.cn/problem/P2158).

在二维上，如果 $(x,y)$ 在 $(0,0)$ 可视，那么有 $\gcd(x,y)=1$，即这俩数互质，虽然这道题在三维视角上，但是也是一样的.

现在，我们的任务就是求：使得 $\gcd(a,b,c)=1$ 的三元组 $\lang a,b,c\rang$ 的个数是多少.

使用同样的套路，定义 $F(d)$ 表示 $(a,b,c)$ 为 $d$ 的倍数的三元组个数，再定义 $f(a,b,c)$ 为 $(a,b,c)$ 刚刚好为 $d$ 的三元组个数，那么有
$$
F(d)=\sum_{d|n}f(n)
$$
同时也有
$$
F(d)=\left \lfloor \frac{n}{d} \right\rfloor^3
$$
那么，反演一下有
$$
f(n)=\sum_{n|d}\mu(\frac{d}{n})F(d)
$$
我们要求的是 $f(1)$，对于 $f(1)$ 有
$$
f(1)=\sum_{d=1}^{n}\mu(d)F(d)
$$
整除分块即可.

但是，我们还要考虑三个面上的情况，这就是退化到二维的情形了，再推一个式子即可（~~其实就是三次方变二次方，没啥必要推的~~）

记得最后加上三个特殊点——$\lang 0,0,1\rang,\;\lang 0,1,0\rang,\;\lang 1,0,0\rang$ 的贡献.

总而言之，实际上我们要求的就是
$$
\sum_i^n\sum_j^n\sum_k^n[\gcd(a,b,c)=1]+3\sum_i^n\sum_j^n[\gcd(i,j)=1]+3
$$
这个式子.

# 代码

```cpp
inline ll pow3(const ll x){
    return x * x * x;
}

inline ll pow2(const ll x){
    return x * x;
}

inline ll f(const int n){
    ll ret = 0;
    for(int l = 1, r; l <= n; l = r + 1){
        r = n / (n / l);
        ret += 1ll * (pre[r] - pre[l - 1]) * pow3(n / l);
    }
    return ret;
}

inline ll g(const int n){
    ll ret = 0;
    for(int l = 1, r; l <= n; l = r + 1){
        r = n / (n / l);
        ret += 1ll * (pre[r] - pre[l - 1]) * pow2(n / l);
    }
    return ret;
}

signed main(){
    sieve();
    rep(i, 1, maxn) pre[i] = pre[i - 1] + mu[i];
    int T = readin(1);
    while(T --){
        int n = readin(1);
        writc(f(n) + 3 * g(n) + 3, '\n');
    }
	return 0;
}
```



---

## 作者：MZAutomata (赞：0)

简化题意可知，题目的本质是让我们求出
$$\sum\limits_{i=1}^n\sum\limits_{j=1}^n\sum\limits_{l=1}^n\left[\gcd(i,j,l)=1\right]+3\sum\limits_{i=1}^n\sum\limits_{j=1}^n\left[\gcd(i,j)=1\right]+3$$
的值。

我们按加号将该式分为三个部分，对应到题目即分别为立方体的 “体” ，“面” 与 “轴” 。

考虑推式子：
$$\sum\limits_{i=1}^n\sum\limits_{j=1}^n\sum\limits_{l=1}^n\left[\gcd(i,j,l)=1\right]$$
$$=\sum\limits_{i=1}^n\sum\limits_{j=1}^n\sum\limits_{l=1}^n\sum\limits_{x|i}\sum\limits_{x|j}\sum\limits_{x|l}\mu(x)$$
$$=\sum\limits_{x=1}^n\sum\limits_{i=1}^n\sum\limits_{j=1}^n\sum\limits_{l=1}^n\left[x|i\right]\left[x|j\right]\left[x|l\right]\mu(x)$$
$$=\sum\limits_{x=1}^n\mu(x)\sum\limits_{i=1}^n\sum\limits_{j=1}^n\sum\limits_{l=1}^n\left[x|i\right]\left[x|j\right]\left[x|l\right]$$
$$=\sum\limits_{x=1}^n\mu(x)\left\lfloor\dfrac{n}{x}\right\rfloor^3$$
同理可将第二部分变形为
$$3\sum\limits_{x=1}^n\mu(x)\left\lfloor\dfrac{n}{x}\right\rfloor^2$$
于是用线性筛+数论分块即可，时间复杂度 $\mathcal O(T\sqrt n)$ 。
### $Code$
```cpp
#include<cstdio>
typedef long long ll;
const int N(1e6+5);
ll pr[N>>1],mo[N];
bool vis[N];
int main()
{
	ll t,n,tot(0),ans,i,j;
	for(i=2,mo[1]=1;i<N;i++)
	{
		if(!vis[i])mo[pr[++tot]=i]=-1;
		for(j=1;j<=tot&&pr[j]*i<N;j++)
		{
			vis[pr[j]*i]=true;
			if(i%pr[j]==0)break;
			mo[pr[j]*i]=-mo[i];
		}
		mo[i]+=mo[i-1];
	}
	for(scanf("%lld",&t);t--;)
	{
		scanf("%lld",&n);
		for(i=1,ans=3;i<=n;i=j+1)
		  j=n/(n/i),ans+=(n/i)*(n/i)*(n/i+3)*(mo[j]-mo[i-1]);
		printf("%lld\n",ans);
	}
	return ~~(0-0);
}
```


---

## 作者：little_cindy (赞：0)

## 算法
莫比乌斯反演
## 思路
### 二维（类似于[P2158 [SDOI2008] 仪仗队](https://www.luogu.com.cn/problem/P2158)，从 $(0,0)$ 开始）
先考虑二维

我们可以发现，如果一个点 $A(x,y)$ 会挡住 $A'(x',y')$，那么 $\frac x y=\frac{x'}{y'}$，所以只需要 $gcd(x,y)=1$，就不会被挡住。（由于坐标轴上的点横坐标或纵坐标为 $0$ 所以需要特殊考虑）

所以 $ans=2+\sum\limits^{n}_{i=1}\sum\limits^{n}_{j=1}[gcd(i,j)=1]$，通过[P2158 [SDOI2008] 仪仗队](https://www.luogu.com.cn/problem/P2158)的[这篇题解](https://www.luogu.com.cn/blog/user26461/solution-p2158)的方式推柿子，可以得到 $ans=2+\sum\limits_{d=1}^n\mu(d)\lfloor\frac n d\rfloor^2$。

### 三维
和二维同理，其实可以分别讨论：坐标中有两个为 $0$（三条坐标轴）、坐标中有一个为 $0$（三个面）、坐标中有没有 $0$。

所以 $ans=3+3\sum\limits^{n}_{i=1}\sum\limits^{n}_{j=1}[gcd(i,j)=1]+\sum\limits^{n}_{i=1}\sum\limits^{n}_{j=1}\sum\limits^{n}_{k=1}[gcd(i,j,k)=1]$。

由二维的部分可以转换为：$ans=3+3\sum\limits_{d=1}^n\mu(d)\lfloor\frac n d\rfloor^2+\sum\limits^{n}_{i=1}\sum\limits^{n}_{j=1}\sum\limits^{n}_{k=1}[gcd(i,j,k)==1]$。

我们只需化简 $\sum\limits^{n}_{i=1}\sum\limits^{n}_{j=1}\sum\limits^{n}_{k=1}[gcd(i,j,k)==1]$ 即可。

同理可得，$\sum\limits^{n}_{i=1}\sum\limits^{n}_{j=1}\sum\limits^{n}_{k=1}[gcd(i,j,k)==1]=\sum\limits_{d=1}^n\mu(d)\lfloor\frac n d\rfloor^3$。

所以 $ans=3+3\sum\limits_{d=1}^n\mu(d)\lfloor\frac n d\rfloor^2+\sum\limits_{d=1}^n\mu(d)\lfloor\frac n d\rfloor^3$。

## code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=1e7+5;
int vis[maxn];
int mu[maxn];
vector<int> primes;
int sum[maxn];
int n;
void mobius(int n){
	mu[1]=1;
	for(int i=2;i<=n;i++){
		if(!vis[i]){
			primes.push_back(i);
			mu[i]=-1;
		}
		for(int j=0;j<primes.size();j++){
			int p=primes[j];
			if(p*i>n){
				break;
			}
			vis[p*i]=1;
			if(i%p==0){
				mu[p*i]=0;
				break;
			}
			else{
				mu[p*i]=mu[p]*mu[i];
			}
		}
	}
	for(int i=1;i<=n;i++){
		sum[i]=sum[i-1]+mu[i];
	}
	return;
}
int _2D(int n){
	int ans=0;
	for(int L=1,R;L<=n;L=R+1){
		R=min(n,n/(n/L));
		ans+=(n/L)*(n/L)*(sum[R]-sum[L-1]);
	}
	return ans;
}
int _3D(int n){
	int ans=0;
	for(int L=1,R;L<=n;L=R+1){
		R=min(n,n/(n/L));
		ans+=(n/L)*(n/L)*(n/L)*(sum[R]-sum[L-1]);
	}
	return ans;
}
signed main(){
	mobius(1e7);
	int T;
	cin>>T;
	while(T--){
		cin>>n;
		cout<<3+3*_2D(n)+_3D(n)<<endl;
	}
	return 0;
} 
```

---

