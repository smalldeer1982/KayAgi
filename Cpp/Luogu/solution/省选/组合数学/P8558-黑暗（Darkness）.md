# 黑暗（Darkness）

## 题目描述

铃在一个黑暗的三维空间内寻找澪。这个空间可以表示为 $\{(x,y,z) \mid x \in[0,A],y \in [0,B],z\in [0,C] \}$。铃初始站在坐标为 $(A,B,C)$ 处，澪站在 $(0,0,0)$ 处。假设铃在 $(x,y,z)$ 处，她每次移动会**均匀随机**地尝试移动到 $(x-1,y,z)$ 或 $(x,y-1,z)$ 或 $(x,y,z-1)$。

这个空间的外围是墙壁，不可穿过。由于空间内很暗，铃并不知道自己是否走到了墙边。也就是说，她在随机选择三种方向尝试移动时，有可能撞在墙上。

铃想要知道，自己在第一次撞墙时，「到澪的曼哈顿距离（在本题中的情况就是 $x,y,z$ 坐标之和）」的 $k$ 次方的期望值。

你只需要求出答案对 $998244353$ 取模的结果。

## 说明/提示

【样例 $1$ 解释】 

下表列出了走到各处并撞到墙的概率：

| $(0,0,0)$ | $(1,0,0)$ | $(0,1,0)$ | $(0,0,1)$ | $(1,1,0)$ | $(1,0,1)$ | $(0,1,1)$ |
| :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: |
| $2/9$ | $4/27$ | $4/27$ | $4/27$ | $1/9$ | $1/9$ | $1/9$ |

可以发现只有在这 $7$ 个位置有可能撞到墙。由此算出期望值为 $\dfrac{10}{9}$，在模 $998244353$ 意义下为 $443664158$。


【样例 $2,3$ 解释】   

这里要算的都是距离的平方的期望。实际答案分别为 $\dfrac{30083}{2187}$ 和 $\dfrac{22748643655}{387420489}$。

【数据范围】  

**本题采用捆绑测试。**

Subtask1（8 pts）：$1\le A,B,C,k\le 6$；   
Subtask2（19 pts）：$1\le A,B,C \le 100$；  
Subtask3（13 pts）：$k=1$；  
Subtask4（23 pts）：$1\le A,B,C,k \le 10^5$；  
Subtask5（37 pts）：无特殊限制。

对于 $100\%$ 的数据，$1\le A,B,C \le 5\times 10^6$，$1\le k \le 10^7$。

【提示】  

对于离散随机变量 $X$，其取值等于 $k$ 的概率设为 $P_k$，则 $X$ 的期望值定义为：

$$\sum_k kP_k$$

对于有理数 $a/b$（$a,b$ 均为正整数），若整数 $r$ 满足 $r\in[0,p-1]$ 且 $rb \equiv a \pmod p$，则 $r$ 就是 $a/b$ 对 $p$ 取模的结果。

## 样例 #1

### 输入

```
1 1 1 1```

### 输出

```
443664158```

## 样例 #2

### 输入

```
2 3 4 2```

### 输出

```
128260948```

## 样例 #3

### 输入

```
4 6 9 2```

### 输出

```
622775535```

## 样例 #4

### 输入

```
58 88 133 233```

### 输出

```
128518400```

## 样例 #5

### 输入

```
114514 1919810 4999231 8214898```

### 输出

```
823989766```

# 题解

## 作者：NaCly_Fish (赞：7)

可以先考虑计算从 $(A,B,C)$ 走到 $(0,0,0)$ 而不撞墙的概率，有递推关系：
$$f_{A,B,C}=\frac 13 (f_{A-1,B,C}+f_{A,B-1,C}+f_{A,B,C-1})$$
建立生成函数，设 $f_{A,B,C}=[x^Ay^Bz^C]F$，则有
$$F= \frac 13(x+y+z)F+1$$
多出来的这个 +1 就是因为要补上 $f_{0,0,0}=1$ 这一项。
$$F = \frac{1}{1-(x+y+z)/3}=\sum_{i=0}^\infty \frac{1}{3^i}(x+y+z)^i$$
提取系数即得
$$f_{A,B,C}= \frac{1}{3^{A+B+C}}\binom{A+B+C}{A,B,C}$$
那么计算从 $(A,B,C)$ 走到 $(i,j,k)$ 而不撞墙概率就容易计算了。其递推式与 $f$ 很像，再稍加分析就可以发现所求是 $f_{A-i,B-j,C-k}$。

现在只需要枚举墙边的位置，根据走到那撞到墙的概率，就可以将答案表示为：
$$g(A,B,C)+g(A,C,B)+g(B,C,A)$$
$$g(d_1,d_2,d_3)=\frac 13\sum_{i=0}^{d_1}\sum_{j=0}^{d_2} \binom{i+j+d_3}{i,j,d_3}\frac{(d_1+d_2-i-j)^k}{3^{i+j+d_3}}$$
你会发现有些位置可能被重复计算了，但没关系。被计了两次的位置，都是有两个方向面对墙的位置。  

这里就说 $g(A,B,C)$ 的计算方法，剩下的两部分也是一样的。可以发现 $i+j$ 在和式中频繁出现，考虑换元枚举 $t=i+j$：

$$3g(A,B,C)=\frac{1}{3^C}\sum_{t=0}^{A+B} \frac{(A+B-t)^k}{3^t}\sum_{j=t-A}^B \binom{t+C}{t-j,j,C}$$  
后面那个和式可以单独计算，先化简为
$$\binom{t+C}{C} \sum_{j=t-A}^B \binom{t}{j}$$


这种超几何式显然可以整式递推计算，利用二项式系数的递推公式：
$$D_n=\sum_{i=n-A}^B \binom ni = \sum_{i=n-A}^B \binom{n-1}{i}+\binom{n-1}{i-1}$$
$$ D_n=2D_{n-1} -\binom{n-1}{A}- \binom{n-1}{B} $$
可以在线性时间内递推计算，最后用线性筛来求 $t^k$ 即可。

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cmath>
#define N 10000003
#define ll long long
#define p 998244353
using namespace std;

inline int power(int a,int t){
    int res = 1;
    while(t){
        if(t&1) res = (ll)res*a%p;
        a = (ll)a*a%p;
        t >>= 1;
    }
    return res;
}

const int inv3 = 332748118;
int fac[N],ifac[N],pw[N],pr[N>>3],inv[N];
int cnt;

void init(int n,int k){
    inv[1] = pw[1] = fac[0] = fac[1] = ifac[0] = ifac[1] = 1;
    for(int i=2;i<=n;++i) fac[i] = (ll)fac[i-1]*i%p;
    ifac[n] = power(fac[n],p-2);
    for(int i=n-1;i;--i) ifac[i] = (ll)ifac[i+1]*(i+1)%p;
    for(int i=2;i<=n;++i){
        inv[i] = (ll)fac[i-1]*ifac[i]%p;
        if(!pw[i]){
            pr[++cnt] = i;
            pw[i] = power(i,k);
        }
        for(int j=1;j<=cnt&&i*pr[j]<=n;++j){
            pw[i*pr[j]] = (ll)pw[i]*pw[pr[j]]%p;
            if(i%pr[j]==0) break;
        }
    }
}

int g(int A,int B,int C,int k){
    if(A>B) swap(A,B);
    ll res = 0;
    int bc = 1,f = 1,ifa = ifac[A],ifb = ifac[B],ipw3 = 1;
    for(int i=0;i<=A+B;++i){
        res += (ll)pw[A+B-i]*f%p*ipw3%p*bc%p;
        ipw3 = ipw3*332748118ll%p;
        bc = (ll)bc*(i+C+1)%p*inv[i+1]%p;
        if(i<A) f = (f<<1)>=p?(f<<1)-p:f<<1;
        else if(i<B) f = ((f<<1)-(ll)fac[i]*ifa%p*ifac[i-A])%p;
        else f = ((f<<1)-((ll)ifa*ifac[i-A]+(ll)ifb*ifac[i-B])%p*fac[i])%p;
    }
    return res%p*power(3,p-C-1)%p;
}

int A,B,C,k;

int main(){
    scanf("%d%d%d%d",&A,&B,&C,&k);
    init(A+B+C-min(min(A,B),C),k);
    int ans = (ll)((g(A,B,C,k)+g(A,C,B,k))%p+g(B,C,A,k))*inv3%p;
    printf("%d",(ans+p)%p);
    return 0;  
}
```

---

## 作者：TianyiLemon (赞：5)

考虑 $(A,B,C)$ 走到 $(x,y,z)$ 而不撞墙的概率。

走 $A+B+C-x-y-z$ 步共有 $3^{A+B+C-x-y-z}$ 种方案，而到达 $(x,y,z)$ 的方案数为 $\begin{pmatrix}A+B+C-x-y-z\\ A-x, B-y,C-z\end{pmatrix}$。

所以概率就是 $\frac{\begin{pmatrix}A+B+C-x-y-z\\ A-x,B-y,C-z\end{pmatrix}}{3^{A+B+C-x-y-z}}$。

根据期望的线性性质，我们可以分开计算撞到每面墙的期望。

以墙 $z=0$ 为例：

$$
\begin{aligned}F_z&=\frac{1}{3}\sum_{x=0}^A \sum_{y=0}^B \frac{\begin{pmatrix}A+B+C-x-y\\ A-x,  B-y, C\end{pmatrix}(x+y)^k}{3^{A+B+C-x-y}}\\
&=\frac{1}{3}\sum_{t=0}^{A+B}\frac{t^k}{3^{A+B+C-t}}\sum_{x=\max(0,t-B)}^{\min(A,t)}\begin{pmatrix}A+B+C-t\\ A-x,B-t+x,C\end{pmatrix} \\
&=\frac{1}{3}\sum_{t=0}^{A+B}\frac{t^k}{3^{A+B+C-t}}\binom{A+B+C-t}{C}\sum_{x=\max(0,t-B)}^{\min(A,t)}\binom{A+B-t}{A-x}\end{aligned}
$$

考虑 $f(t)=\sum_{x=\max(0,t-B)}^{\min(A,t)}\binom{A+B-t}{A-x}$ 怎么算。将组合数展开：

$$
\begin{aligned}f(t)&=\sum_{x=\max(0,t-B)}^{\min(A,t)}\binom{A+B-t-1}{A-x}+\sum_{x=\max(0,t-B)}^{\min(A,t)}\binom{A+B-t-1}{A-x-1}
\end{aligned}
$$

而 
$$f(t+1)=\sum_{x=\max(0,t+1-B)}^{\min(A,t+1)}\binom{A+B-t-1}{A-x}$$

代入比较可得

$$f(t)=2f(t+1)-\binom{A+B-t-1}{A}-\binom{A+B-t-1}{B}$$

不难递推计算。

时间复杂度可以做到 $O(A+B+C)$。

---

## 作者：RandomLife (赞：3)

[传送门](https://www.luogu.com.cn/problem/P8558)

## 题意

有一个 $a\times b\times c$ 的封闭立体空间。现在要从 $(a,b,c)$ 走向 $(0,0,0)$，每次只能从 $(x,y,z)$ 等概率地走向 $(x-1,y,z)$，$(x,y-1,z)$ 和 $(x,y,z-1)$。求第一次撞墙时离终点的曼哈顿距离的 $k$ 次方的数学期望。

## 题解

我们先要知道在不撞墙的情况下走到 $(x,y,z)$ 的概率。显然，总共走了 $a+b+c-x-y-z$ 步，因此有 $3^{a+b+c-x-y-z}$ 种可能。在仔细想想，一种合法的路径一定要恰好有 $a-x$ 次向左走、$b-y$ 次向后走和 $c-z$ 次向下走，所以有 $C_{a+b+c-x-y-z}^{a-x}C_{b+c-y-z}^{b-y}$ 种走法。所以，概率为：

$$
\frac{C_{a+b+c-x-y-z}^{a-x}C_{b+c-y-z}^{b-y}}{3^{a+b+c-x-y-z}}
$$

接下来我们考虑分别撞三面墙的答案。这里以撞下面墙（$z$ 轴）为例，其他情况类似：

首先，给出最暴力的公式：

$$
\sum_{x=0}^a\sum_{y=0}^b\frac{C_{a+b+c-x-y}^cC_{a+b-x-y}^{a-x}(x+y)^k}{3^{a+b+c-x-y}}
$$

我们考虑改为先枚举 $x+y$ 再枚举 $x$：

$$
\sum_{t=0}^{a+b}\frac{C_{a+b+c-t}^ct^k}{3^{a+b+c-t}}\sum_{x=\max(0,t-b)}^{\min(t,a)}C_{a+b-t}^{a-x}
$$


不过根据定义，若 $m<0$ 或 $m>n$，则 $C_n^m=0$。因此我们可以将式子改为：

$$
\sum_{t=0}^{a+b}\frac{C_{a+b+c-t}^ct^k}{3^{a+b+c-t}}\sum_{x=0}^{t}C_{a+b-t}^{a-x}
$$

然而这样子的式子效率比原先还差。

我们设 $f(t)=\sum_{x=0}^{t}C_{a+b-t}^{a-x}$，将式子拆开：

$$
f(t)=\sum_{x=0}^{t}C_{a+b-t-1}^{a-x}+\sum_{x=0}^{t}C_{a+b-t-1}^{a-x-1}
$$

又有：

$$
f(t+1)=\sum_{x=0}^{t+1}C_{a+b-t-1}^{a-x}
$$

因此：

$$
f(t)=2f(t+1)-C_{a+b-t-1}^{a-t-1}-C_{a+b-t-1}^a
$$

然后就能过了。

时间复杂度：$\Theta(A+B+C)$。然而常数极大，需要卡卡常。

## Code

```c++
#include<bits/stdc++.h>
using namespace std;
const int N=1.5e7+5,mod=998244353;
int a,b,c,k,fac[N],inv[N],inv3[N],f[N],g[N],h[N],pw[N],ans=0;
inline int power(int a,int b){
	int c=1;
	for(;b;b>>=1){
		if(b&1)c=1ll*c*a%mod;
		a=1ll*a*a%mod;
	}
	return c;
}
inline int C(int n,int m){
	if(m<0||m>n)return 0;
	return 1ll*fac[n]*inv[n-m]%mod*inv[m]%mod;
}
int main(){
	scanf("%d%d%d%d",&a,&b,&c,&k); 
	fac[0]=1;
	for(register int i=1;i<=a+b+c;++i)fac[i]=1ll*fac[i-1]*i%mod;
	inv[a+b+c]=power(fac[a+b+c],mod-2),inv3[a+b+c]=power(power(3,a+b+c),mod-2);
	for(register int i=a+b+c-1;i>=0;--i)inv[i]=1ll*inv[i+1]*(i+1)%mod,inv3[i]=3ll*inv3[i+1]%mod;
	for(register int i=0;i<=max(a+b,max(a+c,b+c));++i)pw[i]=power(i,k);
	f[0]=g[0]=h[0]=1;
	for(register int t=1;t<=a+b;++t)f[t]=(2ll*f[t-1]%mod-C(t-1,t-b-1)+mod-C(t-1,a)+mod)%mod;
	for(register int t=1;t<=a+c;++t)g[t]=(2ll*g[t-1]%mod-C(t-1,t-c-1)+mod-C(t-1,a)+mod)%mod;
	for(register int t=1;t<=b+c;++t)h[t]=(2ll*h[t-1]%mod-C(t-1,t-c-1)+mod-C(t-1,b)+mod)%mod;
	for(register int p=0;p<=a+b;++p)ans=(ans+1ll*C(a+b+c-p,c)*inv3[a+b+c-p]%mod*f[a+b-p]%mod*pw[p]%mod)%mod;
	for(register int p=0;p<=a+c;++p)ans=(ans+1ll*C(a+b+c-p,b)*inv3[a+b+c-p]%mod*g[a+c-p]%mod*pw[p]%mod)%mod;
	for(register int p=0;p<=b+c;++p)ans=(ans+1ll*C(a+b+c-p,a)*inv3[a+b+c-p]%mod*h[b+c-p]%mod*pw[p]%mod)%mod;
	printf("%lld",1ll*ans*inv3[1]%mod);
	return 0;
}
```

---

## 作者：Purslane (赞：1)

# Solution

考虑分开计算我们撞到三个方向上的墙的答案。

不妨假设我们撞到与 $x$ 轴垂直的墙上。也就是最后一刻的坐标的第一维必然为 $0$，我们假设为 $(0,p,q)$。我们能安全抵达这个位置的概率实际上为 $\dfrac{1}{3^{A+(B-p)+(C-q)}} \times C_{A+(B-p)+(C-q)}^{A} \times C_{(B-p)+(C-q)}^{B-p}$。

于是我们尝试枚举 $p+q$，计算上式的总值，再乘上 $\dfrac{(p+q)^k}{3}$ 即可。

然后肉眼可见的，当 $p+q$ 固定的时候，这个式子的前面两项是固定的。我们只需要计算 $\sum C_{(B-p)+(C-q)}^{B-p}$。

然后考虑我们设 $B-p=a$，$C-q=b$。那有啥限制呢？

- $a+b=T$，$T=B+C-(p+q)$，在我们固定 $p+q$ 的时候是一个常数。
- $0 \le a \le B$，$0 \le b \le C$。

所以我们可以据此求出 $a$ 的界：$[\max\{0,T-C\},\min\{B,T\}]$。

然后我们求 $\sum_{a=d}^u C_T^a$。$d$ 和 $u$ 表示上下界。

不过我们发现，根据组合数的定义，当 $a < 0$ 或者 $a>T$ 的时候，都有 $C_T^a=0$。因此我们可以修改上界 $u$ 和下界 $d$，变成 $d=T-C$，$u=B$。于是这个形式就优美啦：$\sum_{a=T-c}^B C_T^a$。

但是这个和式还是超几何形式的，我们可以考虑使用递归求解法。

$$\sum_{a=T-c}^B C_T^a = \sum_{a=T-c}^B C_{T-1}^a+C_{T-1}^{a-1} = 2(\sum_{a=T-1-c}^B C_{T-1}^a)-C_{T-1}^{T-c-1}-C_{T-1}^{B}$$

于是 $O(n)$ 解决了这道题。

话说部分分还可以用生成函数 + NTT 卷，果然部分分比正解好想，但是知识点更高级，~~还获得了更长的代码和更低的分。~~

```cpp
#include<bits/stdc++.h>
#define ll long long 
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=2e7+10,MOD=998244353;
int A,B,C,k,_3,frac[MAXN],inv[MAXN],dp[MAXN],pw[MAXN],flg[MAXN];
ll qpow(ll base,ll p) {
	ll ans=1;
	while(p) {
		if(p&1) ans=ans*base%MOD;
		base=base*base%MOD,p>>=1;
	}
	return ans;
}
void init(int mx) {
	vector<int> pr;
	pw[1]=1;
	ffor(i,2,mx) {
		if(flg[i]==0) pw[i]=qpow(i,k),pr.push_back(i);
		for(auto v:pr) {
			if(i*v>mx) break;
			flg[i*v]=1,pw[i*v]=1ll*pw[i]*pw[v]%MOD;
			if(i%v==0) break;
		}
	}
	frac[0]=1;
	ffor(i,1,mx) frac[i]=1ll*frac[i-1]*i%MOD;
	inv[mx]=qpow(frac[mx],MOD-2);
	roff(i,mx-1,0) inv[i]=1ll*inv[i+1]*(i+1)%MOD;
	return ; 
}
int Com(int u,int d) {if(u<0||u>d) return 0;return 1ll*frac[d]*inv[u]%MOD*inv[d-u]%MOD;}
int solve(int A,int B,int C) {
	int ans=0,_3p=qpow(_3,A);
	dp[0]=1;
	ffor(T,0,B+C) {
		_3p=1ll*_3p*_3%MOD;
		int mul=1ll*_3p*pw[B+C-T]%MOD;
		mul=1ll*mul*Com(A,A+T)%MOD;
		if(T) dp[T]=1ll*(1ll*dp[T-1]*2-1ll*Com(T-C-1,T-1)-1ll*Com(B,T-1))%MOD;
		ans=(ans+1ll*mul*dp[T]%MOD)%MOD;
	}
	return ans;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>A>>B>>C>>k;
	init(20000000),_3=qpow(3,MOD-2);
	cout<<((1ll*solve(A,B,C)+1ll*solve(B,A,C)+1ll*solve(C,A,B))%MOD+MOD)%MOD;
	return 0;
}
```

---

## 作者：Expert_Dreamer (赞：0)

### 题意
有 $3$ 个数 $x,y,z$，每次等概率选择其中一数，让 $x-1\gets x$ 或 $y-1\gets y$ 或 $z-1\gets z$，问当有其中一数 $<0$ 时，$(x+y+z+1)^k$ 的数学期望（$+1$ 是因为不会超格，$-1$ 按照 $0$ 算）。

### 题解

考虑不撞墙走到 $(x,y,z)$ 的概率：

$$
\frac{C_{a+b+c-x-y-z}^{a-x}C_{b+c-y-z}^{b-y}C_{c-z}^{c-z}}{3^{a+b+c-x-y-z}}
$$

撞每一面墙的公式可以直接推导，暴力公式不难：

$$
\sum\limits_{y=0}^b\sum_{z=0}^c\frac{C_{a+b+c-y-z}^aC_{b+c-y-z}^{b-y}}{3^{a+b+c-y-x}}(y+z)^k
$$

$$
\sum\limits_{x=0}^a\sum_{y=0}^b\frac{C_{a+b+c-x-y}^cC_{a+b-x-y}^{a-x}}{3^{a+b+c-x-y}}(x+y)^k
$$

这里有撞 $x,z$ 墙的公式，我们以 $z$ 墙为例：

发现很多时候 $x+y$ 是一起的，所以可以先枚举 $x+y$，再枚举 $x$，得出 $y$：

$$
\sum_{i=0}^{a+b}\frac{C_{a+b+c-t}^ci^k}{3^{a+b+c-i}}\sum_{x=0}^iC_{a+b-i}^{a-x}
$$

于是，时间复杂度从 $O(ab\log k)$ 变成了 $O((a+b)^2\log k)$。

前面的式子已无法化简，可以考虑后面的式子：

$$
\sum_{x=0}^iC_{a+b-i}^{a-x}
$$

拆开：

$$
\sum_{x=0}^iC_{a+b-i-1}^{a-x}+\sum_{x=0}^iC_{a+b-i-1}^{a-x-1}
$$

由数学归纳法可得：

$$
\sum_{x=0}^iC_{a+b-i}^{a-x}=2\sum_{x=0}^{i+1}C_{a+b-i}^{a-x}-\sum_{x=0}^iC_{a+b-i-1}^{a-x-1}-\sum_{x=0}^iC_{a+b-i-1}^{a}
$$

现在预处理就能过了。

```cpp
for(int t=1;t<=a+b;t++) f[t]=(2*f[t-1]%mod-C(t-1,t-b-1)+mod-C(t-1,a)+mod)%mod;
```

给出主要部分代码（其他两面墙同理）。

---

