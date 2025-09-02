# Steps to One

## 题目描述

Vivek 最初有一个空数组 $a$ 和一个整数常数 $m$。

他执行如下算法：

1. 从 $1$ 到 $m$ 的范围内等概率随机选择一个整数 $x$，并将其添加到 $a$ 的末尾。
2. 计算数组 $a$ 中所有整数的最大公约数。
3. 如果最大公约数等于 $1$，则停止操作。
4. 否则，返回第 1 步。

求数组 $a$ 的期望长度。可以证明，这个期望值可以表示为 $\frac{P}{Q}$，其中 $P$ 和 $Q$ 是互质的整数，且 $Q\neq 0 \pmod{10^9+7}$。请输出 $P \cdot Q^{-1} \pmod{10^9+7}$。

## 说明/提示

在第一个样例中，Vivek 只能从 $1$ 到 $1$ 选择整数，因此第一次添加后 $a=[1]$，算法立即结束。数组长度始终为 $1$，所以期望值也是 $1$。

在第二个样例中，Vivek 每次会添加 $1$ 或 $2$，最终数组中会有若干个 $2$（可能为零），最后有一个 $1$。期望长度为 $1\cdot \frac{1}{2} + 2\cdot \frac{1}{2^2} + 3\cdot \frac{1}{2^3} + \ldots = 2$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
2
```

### 输出

```
2
```

## 样例 #3

### 输入

```
4
```

### 输出

```
333333338
```

# 题解

## 作者：George1123 (赞：39)

更好的体验$\to $ [$\color{#142857}{\it George1123}$](https://www.cnblogs.com/George1123/p/13586454.html)。

---
## 题面

> [CF1139D Steps to One](https://www.luogu.com.cn/problem/CF1139D) 

> 一个数列，每次随机选一个 $[1,m]$ 之间的数加在数列末尾，数列中所有数的 $\gcd=1$ 时停止，求期望长度 $\bmod 10^9+7$。

> 数据范围：$1\le m\le 10^5$。

---
## 蒟蒻语

这题的非 dp 做法讲得太玄了而且写题解的人貌似不屑于解释，于是蒟蒻来写一篇。

---
## 蒟蒻解

先推一波概率期望式（$E(x)$ 是 $x$ 的期望，$P(x)$ 是 $x$ 事件的概率）。

$$
\begin{aligned}
E(len)=&\sum_{i\ge 1}P(len=i)\cdot i\\
=&\sum_{i\ge 1}P(len=i)\sum_{j=1}^i\\
=&\sum_{j\ge 1}\sum_{i\ge j}P(len=i)\\
=&\sum_{i\ge 1}P(len\ge i)\\
=&1+\sum_{i\ge 1}P(len>i)\\
\end{aligned}
$$

因为 $\gcd_{i=1}^{len} a_i=1$ 就结束了，所以：

$$
\begin{aligned}
P(len>i)=&P\left(\left(\gcd_{j=1}^{i} a_i\right)>1\right)\\
=&1-P\left(\left(\gcd_{j=1}^{i} a_i\right)=1\right)\\
=&1-\frac{\sum_{a_1=1}^m\sum_{a_2=1}^m\cdots\sum_{a_i=1}^m\epsilon\left(\left(\gcd_{j=1}^{i} a_i\right)\right)}{m^i}\\
=&^{\color{#aa88cc}{(1)}}1-\frac{\sum_{a_1=1}^m\sum_{a_2=1}^m\cdots\sum_{a_i=1}^m\sum_{d|\left(\gcd_{j=1}^{i} a_i\right)}\mu(d)}{m^i}\\
=&1-\frac{\sum_{d=1}^m\mu(d)\sum_{a_1=1}^m[d|a_1]\sum_{a_2=1}^m[d|a_2]\cdots\sum_{a_i=1}^m[d|a_i]}{m^i}\\
=&1-\frac{\sum_{d=1}^m\mu(d)\left(\lfloor\frac{m}{d}\rfloor\right)^i}{m^i}\\
=&^{\color{#eeaa22}{(2)}}-\frac{\sum_{d=2}^m\mu(d)\left(\lfloor\frac{m}{d}\rfloor\right)^i}{m^i}\\
\end{aligned}
$$

$\color{#aa88cc}{(1)}$ 就是一个莫反，$\color{#eeaa22}{(2)}$ 就是把 $d=1$ 的值和 $1$ 抵消掉。

带回上式：

$$
\begin{aligned}
E(len)=&1+\sum_{i\ge 1}P(len>i)\\
=&1-\sum_{i\ge 1}\frac{\sum_{d=2}^m\mu(d)\left(\lfloor\frac{m}{d}\rfloor\right)^i}{m^i}\\
=&1-\sum_{i\ge 1}\frac{1}{m^i}\sum_{d=2}^m\mu(d)\left(\lfloor\frac{m}{d}\rfloor\right)^i\\
=&1-\sum_{d=2}^m\mu(d)\sum_{i\ge 1}\left(\frac{\lfloor\frac{m}{d}\rfloor}{m}\right)^i\\
=&^{\color{#ff2211}{(3)}}1-\sum_{d=2}^m\mu(d)\frac{\lfloor\frac{m}{d}\rfloor}{m-\lfloor\frac{m}{d}\rfloor}\\
\end{aligned}
$$

$\color{#ff2211}{(3)}$ 是无穷等比数列求值：

$$s=x+x^2+x^3+\cdots$$

$$sx=x^2+x^3+x^4+\cdots$$

$$s-sx=x$$

$$s=\frac{x}{1-x}$$

然后就可以筛个 $\mu(i)$ 就可以 $\Theta(m)$ 地算了，当然您可以杜教到 $\Theta(m^{\frac 23})$，但是那么秀有什么意思呢……

---
## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

//Start
typedef long long ll;
typedef double db;
#define mp(a,b) make_pair((a),(b))
#define x first
#define y second
#define be(a) (a).begin()
#define en(a) (a).end()
#define sz(a) int((a).size())
#define pb(a) push_back(a)
#define R(i,a,b) for(int i=(a),I=(b);i<I;i++)
#define L(i,a,b) for(int i=(a),I=(b);i>I;i--)
const int iinf=0x3f3f3f3f;
const ll linf=0x3f3f3f3f3f3f3f3f;

//Data
const int mod=1e9+7;

//Sieve
struct sieve{
	int n;
	vector<bool> np;
	vector<int> prime,mu,inv;
	void Sieve(){
		np[1]=true,mu[1]=1;
		R(i,2,n){
			if(!np[i]) prime.pb(i),mu[i]=-1;
			for(int p:prime){
				if(!(i*p<n)) break;
				np[i*p]=true;
				if(i%p==0){mu[i*p]=0;break;}
				mu[i*p]=mu[i]*mu[p];
			}
		}
		inv[1]=1;
		R(i,2,n) inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
	}
	sieve(int _n){
		n=_n,np.assign(n,false),inv.resize(n);
		prime.clear(),mu.resize(n),Sieve();
	}
};

//Main
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	int n; cin>>n;
	sieve math(n+1);
	int ans=1;
	R(i,2,n+1) (ans+=mod-1ll*(mod+math.mu[i])%mod
			   *(n/i)%mod*math.inv[n-n/i]%mod)%=mod;
	cout<<ans<<'\n'; 
	return 0;
}
```
---
**祝大家学习愉快！**

---

## 作者：封禁用户 (赞：24)

怎么各位dalao的复杂度都不是$O(m)$啊...瑟瑟发抖qwq
![](https://cdn.luogu.com.cn/upload/pic/55533.png)
```cpp
#include <cstring>
#include <iostream>
using int_t = long long int;
using std::cin;
using std::cout;
using std::endl;

const int_t mod = 1e9 + 7;
const int_t LARGE = 1e5;
int_t inv[LARGE + 1];
int_t m;
int_t mu[LARGE + 1];
int_t factor[LARGE + 1];
bool isPrime[LARGE + 1];

int main() {
    memset(isPrime, 1, sizeof(isPrime));
    cin >> m;
    inv[1] = 1;
    for (int_t i = 2; i <= m; i++)
        inv[i] = (mod - mod / i) * inv[mod % i] % mod;
    for (int_t i = 2; i <= m; i++)
        if (isPrime[i]) {
            for (int_t j = i * i; j <= m; j += i) {
                factor[j] = i;
                isPrime[j] = false;
            }
            factor[i] = i;
        }
    mu[1] = 1;
    for (int_t i = 2; i <= m; i++) {
        int_t p = factor[i];
        if (i / p % p == 0)
            mu[i] = 0;
        else
            mu[i] = mu[i / p] * -1;
    }
    int_t result = 1;
    for (int_t i = 2; i <= m; i++) {
        int_t x = m / i;
        result = (result - mu[i] * x % mod * inv[m - x] % mod + mod) % mod;
    }
    cout << result << endl;
    return 0;
}
```

---

## 作者：CYJian (赞：12)

## 这里是一个$O(NlogN)$的做法!!

好吧..其实前面的步骤和其他的题解差不多了..只不过再往后推一些就好了..

首先,可以设置状态$f[i]$表示当前所有的数的$gcd=i$时,还需要加入的数的期望个数.

显然可知,$f[1]=0$,并且有:

$$ans=1+\frac{\sum_{i=1}^{m}f[i]}{m}$$

$+1$是因为设置状态的原因..显然第一个数是没有考虑在内的...所以需要枚举一下第一个数是什么,每一个数都有$\frac{1}{m}$的概率选上,选上之后还期望在之后加上$f[i]$个数,所以答案就是这个了..

然后考虑转移..

我们可以得到这样一个非常显然的式子:

$$f[i]=1+\frac{\sum_{j=1}^m f[gcd(i,j)]}{m}$$

大致的意思就是,当前的$gcd$不为$1$($gcd=1$,即$f[1]=0$),显然会插入至少一个数,这样我们就会有1的贡献. 然后就可以枚举下一个数可能是什么, 选到任意一个数的概率都是$\frac{1}{m}$,选出这个数之后数列的$gcd$显然就会是前面的数的$gcd$与当前插入的数的$gcd$.所以就会有这个递推..

然后考虑优化转移..首先可以想到的是枚举$gcd$.因为$gcd$一定是$i$的因子,$1$~$n$的因子个数和是接近$n\times ln(n)$的,所以可以优化一定的复杂度.也就是说我们现在需要求的式子变成了这个:

$$f[i]=1+\frac{\sum_{d|i} f[d]\sum_{j=1}^m [gcd(i,j)=d]}{m}$$

怎么快速求$\sum_{d|i} f[d]\sum_{j=1}^m [gcd(i,j)=d]$呢..

~~显然需要懵逼钨丝反演了...~~窝不会反演只会懵逼钨丝函数...

所以可以~~欢乐地~~化式子辣!!

$$\sum_{d|i} f[d]\sum_{j=1}^m [gcd(i,j)=d]$$

$$\sum_{d|i} f[d]\sum_{j=1}^{m/d} [gcd(i/d,j)=1]$$

$$\sum_{d|i} f[d]\sum_{j=1}^{m/d} \sum_{t=1}^{m}\mu(t)[t|(i/d)][t|j]$$

$$\sum_{d|i} f[d]\sum_{t=1}^{m}\mu(t)[t|(i/d)] \sum_{j=1}^{m/d} [t|j]$$

$$\sum_{d|i} f[d]\sum_{t|(i/d)}\mu(t)\lfloor \frac{m}{td} \rfloor$$

然后我们考虑设$T=td$,交换一下枚举顺序:

注意一下,这里的$d$以及$t$的条件,发现满足$(td)|i$,所以需要写成下面这个样子:

$$\sum_{T|i}\lfloor \frac{m}{T} \rfloor \sum_{d|T}f[d]\mu(\frac{T}{d})$$

所以我们可以把这个式子带回到原式中:

$$f[i]=1+\frac{\sum_{T|i}\lfloor \frac{m}{T} \rfloor \sum_{d|T}f[d]\mu(\frac{T}{d})}{m}$$

如果我们设$F[x]=\sum_{d|T}f[d]\mu(\frac{T}{d})$,那么如果我们新求出了一个$f[i+1]$,那么我们可以用$O(\frac{m}{i+1})$的时间更新$F(x)$..这样求$F(x)$的复杂度就是$O(nlogn)$.

但是怎么求$f[i]$呢..上面的式子中,若$T=d=i$的时候出现了未知的$f[i]$,显然我们需要把它移到等号左边去.那么就算一下系数吧..

$T=d=i$,从里到外的系数就是$\mu(1)$, $\lfloor \frac{m}{i} \rfloor$, $\frac{1}{m}$,那么把$f[i]$拆出来就是这个了:

$$f[i]=1+\frac{\sum_{T|i}\lfloor \frac{m}{T} \rfloor \sum_{d|T}f[d]\mu(\frac{T}{d})[d \neq i]}{m}+\frac{f[i]\lfloor \frac{m}{i} \rfloor}{m}$$

再往下推就可以有:

$$f[i]-\frac{f[i]\lfloor \frac{m}{i} \rfloor}{m}=1+\frac{\sum_{T|i}\lfloor \frac{m}{T} \rfloor \sum_{d|T}f[d]\mu(\frac{T}{d})[d \neq i]}{m}$$

$$f[i]=\frac{m+\sum_{T|i}\lfloor \frac{m}{T} \rfloor \sum_{d|T}f[d]\mu(\frac{T}{d})[d \neq i]}{m-\lfloor \frac{m}{i} \rfloor}$$

然后就可以了...等会..上面的$[d \neq i]$好像和之前的东西不太像啊..

其实这个条件只在$T=i$的时候才有限制...然后考虑求狄利克雷卷积的时候,如果外层循环正好枚举到$i$,内层循环还没有进入的时候,$1$~$i-1$的位置的卷积肯定是已经算好了的..第$i$个位置上的值还少了$f[i] \times \mu(1)$..这不就是我们想要的东西么..

所以就可以先算$f[i]$再算$F(i)$了..

贴上代码...

```cpp
#include <bits/stdc++.h>

using namespace std;

const int mod = 1000000007;
const int MAXN = 1000000;

int n;

int tot;
int pri[MAXN + 1];
int miu[MAXN + 1];
int inv[MAXN + 1];
bitset<MAXN + 1>chk;
vector<int>d[MAXN + 1];

int F[MAXN + 1];

inline void prework();
inline int Mod(int);

int main() {
	cin >> n, prework(); int res = 1;
	for(int i = 2; i <= n; i++) { // 狄利克雷卷积
		int si = d[i].size(); int f = n;
		for(int j = 0; j < si; j++) { // 枚举T计算f[i]
			int T = d[i][j];
			f = (f + 1LL * (n / T) * F[T]) % mod;
		} f = 1LL * f * inv[n - n / i] % mod; res = Mod(res + f + 1);
		for(int j = 1, k = i; k <= n; j++, k += i) // 狄利克雷卷积计算F[i]
			F[k] = Mod(F[k] + r * miu[j]);
	} cout << 1LL * res * inv[n] % mod << endl;
	cerr << 1.0 * clock() / CLOCKS_PER_SEC << endl;
	return 0;
}

inline void prework() {
	miu[1] = 1;
	for(int i = 2; i <= n; i++) { // 预处理miu
		if(!chk[i]) pri[++tot] = i, miu[i] = -1;
		for(int j = 1; j <= tot; j++) {
			if(pri[j] * i > n) break;
			chk[pri[j] * i] = 1;
			if(i % pri[j] == 0) break;
			miu[i * pri[j]] = -miu[i];
		}
	}
	for(int i = 1; i <= n; i++) // 预处理每个数的约数
		for(int j = i; j <= n; j += i)
			d[j].push_back(i);
	inv[1] = 1;
	for(int i = 2; i <= n; i++) // 预处理逆元
		inv[i] = 1LL * (mod - mod / i) * inv[mod % i] % mod;
}

inline int Mod(int x) { return x >= mod ? x - mod : (x < 0 ? x + mod : x); }
```

~~好像被别的大佬的$NlogN$吊打了QwQ~~

---

## 作者：AThousandSuns (赞：8)

在我的博客上看效果更佳：[点这里](https://www.cnblogs.com/1000Suns/p/10656969.html)

stm这是div2的D题……我要对不住我这个紫名了……

---
首先很容易想到DP：$f_i$ 表示目前的 $\gcd$ 为 $i$，期望还要多少次才能结束。

那么有 $f_1=0$。

转移，直接枚举即可：$f_i=1+\dfrac{1}{m}\sum\limits^m_{j=1}f_{\gcd(i,j)}$。

如果出现 $\gcd(i,j)=i$（也就是 $i|j$），那么把这种情况特殊判断，那么解个方程可以得到：

$$f_i=\dfrac{1+\dfrac{1}{m}\sum\limits^m_{j=1,i\nmid j}f_{\gcd(i,j)}}{1-\lfloor\frac{m}{i}\rfloor}$$

答案为 $\dfrac{1}{m}\sum\limits^m_{i=1}(f_i+1)$。

这是 $O(m^2\log m)$ 的。我当时就是在这里卡住了，现在感觉自己是个zz……

我们套路地枚举 $\gcd$，设 $c(i,j)$ 表示有多少个 $1\le x\le m$ 满足 $\gcd(i,x)=j$。那么就有：

$$f_i=\dfrac{1+\dfrac{1}{m}\sum\limits_{j|i}f_{j}c(i,j)}{1-\lfloor\frac{m}{i}\rfloor}$$

接下来就要考虑求 $c(i,j)(j|i)$。

$$c(i,j)=\sum\limits^m_{x=1}[\gcd(i,x)=j]$$

$$c(i,j)=\sum\limits^m_{j|x}[\gcd(\frac{i}{j},\frac{x}{j})=1]$$

$$c(i,j)=\sum\limits^{\lfloor\frac{m}{j}\rfloor}_{x=1}[\gcd(\frac{i}{j},x)=1]$$

接下来有两条路可走：分解质因数（官方做法）和莫比乌斯反演（大众做法）。

那我们先来看看大众做法。

---
### 莫比乌斯反演：
$$c(i,j)=\sum\limits^{\lfloor\frac{m}{j}\rfloor}_{x=1}\sum\limits_{d|\gcd(\frac{i}{j},x)}\mu(d)$$

$$c(i,j)=\sum\limits_{d|\frac{i}{j}}\mu(d)\sum\limits^{\lfloor\frac{m}{j}\rfloor}_{d|x}1$$

$$c(i,j)=\sum\limits_{d|\frac{i}{j}}\mu(d)\lfloor\dfrac{m}{jd}\rfloor$$

此时求 $c(i,j)$ 复杂度为 $O(\sqrt{\frac{i}{j}})$。

总复杂度为 $O(\sum\limits^m_{i=2}\sum\limits_{j|i}\sqrt{\frac{i}{j}})=O(\sum\limits^m_{i=2}\sum\limits_{j|i}\sqrt{j})=O(\sum\limits^m_{j=1}\sqrt{j}\lfloor\frac{m}{j}\rfloor)\approx O(m\int^m_1j^{-\frac{1}{2}}\mathrm{d}j)=O(m\sqrt{m})$。

---
### 分解质因数：
我们不妨修改一下定义（只是为了方便）：令 $c(x,y)=\sum\limits^y_{i=1}[\gcd(i,x)=1]$。那么原来的 $c(i,j)$ 就变成了现在的 $c(\frac{i}{j},\lfloor\frac{m}{j}\rfloor)$。

也就是要 $i$ 和 $x$ 的质因子集合没有交集。

我们从反向考虑，考虑与 $x$ 的质因子有交集的 $i$ 的个数。

先对 $x$ 质因数分解，设分解出的不同质因子有 $p_1,p_2\cdots p_k$。那么有 $k\le 6$。

那么与集合 $S$ 有交的 $i$ 的个数就是 $\lfloor\frac{y}{\prod S_i}\rfloor$。

然后还要再容斥一下。那么总的就是：

$$c(x,y)=y-\sum\limits_{S\in x_{pr},S\ne\varnothing}(-1)^{|S|+1}\lfloor\frac{y}{\prod S_i}\rfloor$$

当然也可以写成：（这是代码中的写法）

$$c(x,y)=\sum\limits_{S\in x_{pr}}(-1)^{|S|}\lfloor\frac{y}{\prod S_i}\rfloor$$

此时转移方程为：

$$f_i=\dfrac{1+\dfrac{1}{m}\sum\limits_{j|i}f_{j}c(\frac{i}{j},\lfloor\frac{m}{j}\rfloor)}{1-\lfloor\frac{m}{i}\rfloor}$$

这个可以做到 $O(2^k+\sqrt{x})$。注意最好用DFS，不要用二进制枚举，否则会退化为 $O(2^k\times k+\sqrt{x})$。（虽然也能过）

时间复杂度也是 $O(m\sqrt{m})$。

---
由于大多数人写的都是莫比乌斯反演，我就写一发质因数分解给大家。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=100010,mod=1000000007;
#define FOR(i,a,b) for(int i=(a);i<=(b);i++)
#define ROF(i,a,b) for(int i=(a);i>=(b);i--)
#define MEM(x,v) memset(x,v,sizeof(x))
inline int read(){
    char ch=getchar();int x=0,f=0;
    while(ch<'0' || ch>'9') f|=ch=='-',ch=getchar();
    while(ch>='0' && ch<='9') x=x*10+ch-'0',ch=getchar();
    return f?-x:x;
}
int m,f[maxn],fac[7],fl;
inline int qpow(int a,int b){
    int ans=1;
    for(;b;b>>=1,a=1ll*a*a%mod) if(b&1) ans=1ll*ans*a%mod;
    return ans;
}
int dfs(int dep,int pro,int sgn,int up){    //dep表示正在枚举第几个质因子，pro表示S的乘积，sgn表示容斥系数（1或-1），up表示上界
    if(dep>fl) return up/pro*sgn;
    else return dfs(dep+1,pro,sgn,up)+dfs(dep+1,pro*fac[dep],-sgn,up);
}
int cnt(int x,int y){
    fl=0;
    for(int i=2;i*i<=x;i++)
        if(x%i==0){
            fac[++fl]=i;
            while(x%i==0) x/=i;
        }
    if(x>1) fac[++fl]=x;
    return dfs(1,1,1,y);
}
int main(){
    m=read();int inv=qpow(m,mod-2);
    f[1]=0;
    FOR(i,1,m){
        if(i!=1){    //最后要除以m，加1再除以1-m/i
            f[i]=1ll*f[i]*inv%mod;
            f[i]=(f[i]+1)%mod;
            f[i]=1ll*f[i]*qpow((1-1ll*(m/i)*inv%mod+mod)%mod,mod-2)%mod;
        }
        FOR(j,2,m/i) f[i*j]=(f[i*j]+1ll*f[i]*cnt(j,m/i))%mod;
        //枚举i的倍数，f[i*j]+=f[i]*c((i*j)/i,m/i)
    }
    int ans=0;
    FOR(i,1,m) ans=(ans+f[i]+1)%mod;    //累加答案
    ans=1ll*ans*inv%mod;
    printf("%d\n",ans);
}
```

---

## 作者：lanos212 (赞：7)

这里提供一篇不用莫比乌斯反演的题解 qwq。

~~（很不擅长期望所以可能会有些地方说的不是很恰当）~~

考虑从 $\gcd$ 为 $x$ 时可以转移到哪些状态:

1. 转移到自己。

2. 转移到除了自己外的约数。

第一种会自己和自己套圈比较麻烦，我们想办法用等价的方式去掉它。

有一个定理存在，如果有一个状态每次有 $\frac{1}{x}$ 的概率转移到其它状态，那么它能够转移到其它状态的期望次数是 $x$。（这个定理可以将式子拆成若干个等比数列，每个等比数列的和也形成一个等比数列，再求和就可以得到答案）

考虑一个数 $x$ 和另一个数的 $\gcd$ 还是自己，那么这另一个数一定是 $x$ 的倍数。这样的倍数有 $\left \lfloor \frac{n}{x} \right \rfloor $ 个，所以它转移到自己的概率是 $\frac{\left \lfloor \frac{n}{x} \right \rfloor}{n}$，转移到其它状态的期望长度就是 $\frac{n}{n-
\left \lfloor \frac{n}{x} \right \rfloor}$。

那么就可以转化成，$\gcd$ 为 $x$ 时的期望长度由转移到的所有约数的“（加权）平均期望长度”再加上自己转移到其它状态的期望长度得到。

那么现在我们只需要计算这个“平均期望长度”即可，这个“平均期望长度”的计算方法是每种转移的 **转移概率 $\times$ 转移后状态的期望长度** 之和。

那么我们现在只要考虑如何计算转移概率即可。考虑到从 $x$ 转移到了它的约数 $y$ ，那么这次转移有可能的数是所有 $y$ 的倍数。

那么在这些 $y$ 的倍数里，发现如果被有更大的 $x$ 的倍数用掉了，$y$ 就不能通过这个倍数转移了，所以只需要从大到小找约数，在每一个 $x$ 的约数 $y$ 计算完时，都让后面的 $y$ 的约数减去自己转移可能通过的数的个数，之后算到某个约数时就直接加上有多少个自己的倍数即可，因为在前面更大的约数计算时已经把自己不能取的去掉了。

由于转移到后面约数可以通过的数字个数有 $n-
\left \lfloor \frac{n}{x} \right \rfloor$ 个，如果有 $p$ 个数可以让 $x$ 转移到 $y$，那么转移到某个约数的概率就是 $\frac{p}{n-
\left \lfloor \frac{n}{x} \right \rfloor}$。

只要这样从 $1$ 反推到 $n$，答案是就是 $\gcd$ 分别为 $1$ 到 $n$ 时的期望长度的平均数。

时间复杂度 $O(\sum_{i=1}^{n} ys_i^2)$，其中 $ys_i$ 表示 $i$ 的约数个数。

code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int mo=1e9+7;
long long n,p[100001];
vector<long long> v[100001],f[100001];
inline long long ksm(long long x,long long y){//快速幂 
	if (y==1) return x; if (y==0) return 1;
	long long z=ksm(x,y/2);
	if (y&1) return z*z%mo*x%mo; return z*z%mo;
}
inline long long inv(long long x){return ksm(x,mo-2);}//费马小定理求乘法逆元 
int main(){
	ios::sync_with_stdio(false);
	cin>>n;
	for (int i=n;i;--i) for (int j=i;j<=n;j+=i) v[j].push_back(i),f[j].push_back(0);//v里存有哪些约数，f里存有多少个数使状态转移到某个约数 
	p[1]=1;//gcd为1的期望长度是1
	for (int i=2;i<=n;++i){
		for (int j=0;j<v[i].size();++j){
			f[i][j]+=n/v[i][j];//加上可能可以通过它来转移的数 
			for (int k=j+1;k<v[i].size();++k) if (v[i][j]%v[i][k]==0) f[i][k]-=f[i][j];//为后面的约数去掉不可以通过它来转移的数 
		}
		p[i]=n*inv(n-f[i][0]);//自己传给后面的期望长度 
		for (int j=1;j<v[i].size();++j) p[i]=(p[i]+p[v[i][j]]*f[i][j]%mo*inv(n-f[i][0]))%mo;//加上后面的加权平均期望长度 
	}
	long long ans=0;
	for (int i=1;i<=n;++i) ans=(ans+p[i])%mo;//计算最终答案 
	cout<<ans*inv(n)%mo;
	return 0;
}
```



---

## 作者：clamee (赞：7)


我有一个不一样的推式子方法。

先将问题转换一下，假设当前的 gcd $x=p1^{k1}p2^{k2}\cdots$，即为求：
$$
E(\max(\forall i,\min(k_i)=0))
$$
不妨将每个质数 $p$ 看成一个物品，

假设 $x$ 是新插入集合的数，不妨将 $x$ 看成一个这样的操作：

- 将与 $x$ 互质的物品取走。

现在问题转化成了一个取物品的的问题，即为求：
$$
E(\max(S))
$$
那么直接 Min-max 容斥：
$$
E(max(S)=\sum_{T\in S}(-1)^{|T|+1}E(min(T)=\sum_{T\in S}(-1)^{|T+1|}\frac{1}{P(T)}
$$
考虑当 $\prod_{x\in T}x>n$ 时 $P(T)=1$，且 $x$ 为质数，于是可以将式子改写:
$$
E(max(S))=\sum_{T\in S}(-1)^{|T|+1}-\sum_{i=2}^n \mu(i)+\sum_{i=2}^n \mu(i)\lfloor\frac{n}{i}\rfloor=1-\sum_{i=2}^n \mu(i)+\sum_{i=2}^n \mu(i)\lfloor\frac{n}{i}\rfloor
$$
然后问题就解决了。

```
int qmod(int x,int y)
{
	int ans=1;
	while(y)
	{
		if(y&1)(ans*=x)%=M;
		(x*=x)%=M;
		y>>=1;
	}
	return ans;
}
signed main()
{
	n=read();
	int inv=qmod(n,M-2);
	for(rg int i=2;i<=n;i++)
	{
		if(!vis[i])p[++len]=i,u[i]=1;
		for(rg int j=1;j<=len&&p[j]*i<=n;j++)
		{
			vis[i*p[j]]=1;
			if(i%p[j]==0)break;
			u[i*p[j]]=-u[i];
		}
		sum=(sum-u[i]+M)%M;
	}
	for(rg int i=2;i<=n;i++)
	{
		if(u[i]==0)continue;
		mul[i]=n*qmod(n-n/i,M-2);
		sum=(sum+u[i]*mul[i]%M+M)%M;
	}
	write((sum+1)%M);
}
```



---

## 作者：qwaszx (赞：4)

dp是啥啊，直接算啊

$$
\begin{aligned}E(X)&=\sum_{i\geq 1}P(X=i)i\\&=\sum_{i\geq 1}P(X=i)\sum_{j=1}^i1\\&=\sum_{j\geq 1}\sum_{i\geq j}P(X=i)\\&=\sum_{j\geq 1}P(X\geq j)\\&=1+\sum_{j\geq 1}P(X>j)\\&=1+\sum_{j\geq 1}(1-P(\gcd(a_1,a_2,\cdots,a_j)=1))\\&=1+\sum_{j\geq 1}\frac {m^j-\sum_{k\geq 1}\mu(k)\lfloor\frac{m}{k}\rfloor^j}{m^j}\\&=1-\sum_{k\geq 2}\mu(k)\sum_{j\geq 1}\left(\frac{\lfloor\frac{m}{k}\rfloor}{m^j}\right)^j\\&=1-\sum_{k\geq 2}\mu(k)\frac{\lfloor\frac{m}{k}\rfloor}{m-\lfloor\frac{m}{k}\rfloor}\end{aligned}
$$

管理觉得说明太少没过，于是我来把式子翻译成人话

第一步是期望的定义

第二三四五步好像看式子就比较显然

第六步按照题意，长度大于 $j$ 的概率就是前 $j$ 个不互质的概率，那么我们用 $1$ 减去都互质的概率

剩下的部分是一个很简单的莫反

可以 $O(m^{2/3})$ 甚至 $O(m)$ 计算(雾)

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int mod=1000000007,N=2e5;
int mu[N],inv[N],n,prime[N],p[N],cnt;
int main()
{
    scanf("%d",&n);
    mu[1]=inv[1]=1;
    for(int i=2;i<=n;i++)
    {
        inv[i]=1ll*inv[mod%i]*(mod-mod/i)%mod;
        if(!p[i])mu[i]=-1,prime[++cnt]=i;
        for(int j=1;j<=cnt&&i*prime[j]<=n;j++)
        {
            int x=i*prime[j];p[x]=1;
            if(i%prime[j])mu[x]=-mu[i];
            else break;
        }
    }
    int ans=1;
    for(int i=2;i<=n;i++)ans=(ans-mu[i]*1ll*(n/i)*inv[n-n/i])%mod;
    cout<<(ans+mod)%mod<<endl;
}
```

---

## 作者：xyz32768 (赞：3)

题意
=

- 给定正整数 $m$ ，你有一个空集合 $a$

- 每次你可以等概率随机一个 $[1,m]$ 内的正整数加入集合 $a$

- 加入之后，如果集合 $a$ 内所有数的 $\gcd$ 为 $1$ 则结束过程，否则继续随机

- 求过程结束后集合 $a$ 的期望大小

- $1\le m\le 100000$

算法：莫比乌斯反演 + 期望 DP
=

- 状态 $f[i]$ 表示当前集合 $a$ 的 $\gcd$ 为 $i$ 的情况下，期望加入多少个数之后这个 $\gcd$ 变成 $1$

- 显然有

- $$f[1]=0$$

- $$f[i]=1+\frac 1m\sum_{j=1}^mf[\gcd(i,j)]$$

- 发现 $\gcd(i,j)$ 的取值个数只有 $i$ 的约数个数，所以把枚举 $j$ 改成枚举 $\gcd(i,j)$

- $$f[i]+1+\frac 1m\sum_{d|i}f[d]\times cnt(d,i)$$

- $cnt(d,i)$ 表示 $[1,m]$ 内有多少个数与 $i$ 的 $\gcd$ 等于 $d$

- 另设 $g(i,j)$ 表示 $[1,i]$ 内有多少个数与 $j$ 互质

- 显然有 $cnt(d,i)=g(\lfloor\frac md\rfloor,\frac id)$

- 注意到 $\sum_{i=1}^m\frac mi=O(m\log m)$

- 所以考虑求出所有的 $ij\le m$ ，对应 $g(\lfloor\frac mi\rfloor,j)$ 的值

- 那么对于给定的 $a\ge b$ ，如何求有多少个 $1\le i\le a$ 满足 $\gcd(i,b)=1$ 呢？

- 如果不是满足 $\gcd(i,b)=1$ 而是满足 $x|\gcd(i,b)$ ，则这显然为 $\lfloor\frac ax\rfloor$

- 所以，考虑反演，得

- $$g(a,b)=\sum_{x|b}\mu(x)\lfloor\frac ax\rfloor$$

- 设 $D(x)$ 为 $x$ 的约数个数

- 那么线性筛 $\mu$ 之后就可以在 $O(D(b))$ 的时间内求出 $g(a,b)$

- 对每对 $ij\le m$ 进行计算的总复杂度为

- $$\sum_{i=1}^m\sum_{j=1}^{\lfloor\frac mi\rfloor}D(j)=\sum_{i=1}^m\sum_{j=1}^{\lfloor\frac mi\rfloor}\lfloor\frac{\lfloor\frac mi\rfloor}j\rfloor=\sum_{i=1}^m\lfloor\frac mi\rfloor\log m=O(m\log^2m)$$

- 回到这个转移

- $$f[i]+1+\frac 1m\sum_{d|i}f[d]\times cnt(d,i)$$

- 发现 $d$ 可以等于 $i$ ，得不到转移的目的，所以做一些移项

- $$(1-\frac{cnt(i,i)}m)f[i]=1+\frac1m\sum_{d|i,d\ne i}f[d]\times cnt(d,i)$$

- $$f[i]=\frac1{1-\frac{cnt(i,i)}m}(1+\frac1m\sum_{d|i,d\ne i}f[d]\times cnt(d,i))$$

- 于是我们就可以转移了

- 考虑如何算答案

- 由于第一个数可以随便取，所以答案为

- $$\frac1m\sum_{i=1}^m(1+f[i])$$

- 看到某人的提交记录里有吊打标算的非 DP 做法，复杂度仿佛是 $O(m\log m)$ ，所以有更优做法欢迎提出

代码
=

- 该代码中的 $f[i]$ 表示的是题解中的 $f[i]$ 加一，答案为 $\frac1m\sum_{i=1}^mf[i]$ ，边界为 $f[1]=1$ ，见谅


```cpp
#include <bits/stdc++.h>

// 20030830

inline int read()
{
	int res = 0; bool bo = 0; char c;
	while (((c = getchar()) < '0' || c > '9') && c != '-');
	if (c == '-') bo = 1; else res = c - 48;
	while ((c = getchar()) >= '0' && c <= '9')
		res = (res << 3) + (res << 1) + (c - 48);
	return bo ? ~res + 1 : res;
}

const int N = 1e5 + 5, ZZQ = 1e9 + 7;

int qpow(int a, int b)
{
	int res = 1;
	while (b)
	{
		if (b & 1) res = 1ll * res * a % ZZQ;
		a = 1ll * a * a % ZZQ;
		b >>= 1;
	}
	return res;
}

int n, f[N], miu[N], tot, pri[N], inv[N], wt[N], num[N], res[N], ans;
bool mark[N];
std::vector<int> divi[N], cont[N];

int solve(int n, int m)
{
	int tt = divi[m].size(), res = 0;
	for (int i = 0; i < tt; i++)
	{
		int x = divi[m][i];
		res += miu[x] * (n / x);
	}
	return res;
}

void sieve()
{
	mark[0] = mark[miu[1] = 1] = 1;
	for (int i = 2; i <= n; i++)
	{
		if (!mark[i]) miu[pri[++tot] = i] = -1;
		for (int j = 1; j <= tot; j++)
		{
			if (1ll * i * pri[j] > n) break;
			mark[i * pri[j]] = 1;
			if (i % pri[j] == 0) break;
			else miu[i * pri[j]] = -miu[i];
		}
	}
	for (int i = 1; i <= n; i++)
		for (int j = i; j <= n; j += i)
			divi[j].push_back(i);
	for (int i = 1; i <= n;)
	{
		int nxt = n / (n / i);
		for (int j = 1; j <= n / i; j++) res[j] = solve(n / i, j);
		for (int j = i; j <= nxt; j++)
			for (int k = j; k <= n; k += j)
				cont[k].push_back(res[k / j]);
		i = nxt + 1;
	}
}

int main()
{
	n = read();
	inv[1] = 1;
	for (int i = 2; i <= n; i++)
		inv[i] = 1ll * (ZZQ - ZZQ / i) * inv[ZZQ % i] % ZZQ;
	sieve();
	f[1] = 1;
	for (int i = 2; i <= n; i++)
	{
		int tt = divi[i].size();
		for (int j = 0; j < tt; j++)
			wt[j + 1] = 1ll * inv[n] * cont[i][j] % ZZQ, num[j + 1] = divi[i][j];
		int qt = qpow((1 - wt[tt] + ZZQ) % ZZQ, ZZQ - 2);
		for (int j = 1; j < tt; j++) wt[j] = 1ll * wt[j] * qt % ZZQ;
		f[i] = qt;
		for (int j = 1; j < tt; j++)
			f[i] = (1ll * wt[j] * f[num[j]] + f[i]) % ZZQ;
	}
	for (int i = 1; i <= n; i++)
		ans = (1ll * inv[n] * f[i] + ans) % ZZQ;
	std::cout << ans << std::endl;
	return 0;
}
```

---

## 作者：asuldb (赞：3)

[题目](https://codeforces.com/problemset/problem/1139/D)

打$div2$的时候被这道题锤自闭了

确实是非常神仙的的一道题

我们发现不能和结尾的数互质，结尾的数也不会和前面的数互质，所以我们发现整个序列都是不互质的

那么我们可以考虑把这个关系抽象成一张拓扑图，每一个数$x$向其约数$k$连边，表示我们通过在末尾添加一个数可以使得整个序列的$gcd$从$x$变成$k$

于是我们得到了一张$DAG$，我们再搞一个虚点，向所有数连边，表示起点

每一条边都有一个走的概率，我们已经把问题转化成了求从起点到$1$的期望路径长度

从起点连向各点的边概率显然是$\frac{1}{m}$

从$x$连向其约数$k$的边的概率显然是$\frac{\sum_{i=1}^m[(x,i)=k]}{m}$

现在的问题转化成了如何求

$$f(x,k)=\sum_{i=1}^m[(x,i)=k]$$

考虑反演

设

$$F(x,k)=\sum_{i=1}^m[k|(x,i)]$$

显然存在

$$F(x,k)=\sum_{k|d}f(x,d)=\lfloor\frac{n}{k}\rfloor\times[k|x]$$

直接反演可得

$$f(x,k)=\sum_{k|d}\mu(\frac{d}{k})F(x,d)$$

注意这里的$d$仅能取$x$的约数

我们求$f(x,k)$直接暴力就好了，复杂度基于$\sum_{i=1}^md^2(i)$，不是很会算，大概$O(nlog^2n)$吧

还有一个问题，就是每一个点自己能像自己转移，看起来没有什么办法直接$dp$了呀

照样做就好了

设$dp_x$表示从$1$到$x$的期望路径长度

显然

$$dp_x=\frac{f(x,x)}{m}dp_x+1+\sum_{k|x,k!=x}\frac{f(x,k)}{m}dp_k$$

移项可得

$$(1-\frac{f(x,x)}{m})dp_x=1+\sum_{k|x,k!=x}\frac{f(x,k)}{m}dp_k$$

求出右边之后直接解方程就好

代码

```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<vector>
#define re register
#define LL long long
const int maxn=200005;
const int M=2500005;
const LL mod=1e9+7;
int n,num;
std::vector<int> v[maxn];
int f[maxn],mu[maxn],p[maxn>>1],head[maxn],vis[maxn];
LL a[maxn],g[maxn],dp[maxn];
struct E{int v,nxt;LL w;}e[M];
inline void add(int x,int y,LL w) {
	e[++num].v=y;e[num].nxt=head[x];
	head[x]=num;e[num].w=w;
}
inline LL ksm(LL a,LL b) {LL S=1;while(b) {if(b&1) S=S*a%mod;b>>=1;a=a*a%mod;}return S;}
inline LL dfs(int x) {
	if(vis[x]) return dp[x];
	vis[x]=1;
	for(re int i=head[x];i;i=e[i].nxt) 
		dp[x]=(dp[x]+e[i].w*(dfs(e[i].v)+1ll)%mod)%mod;
	if(a[x]) {
		dp[x]=(dp[x]+a[x])%mod;
		dp[x]=dp[x]*ksm((1-a[x]+mod)%mod,mod-2);
		dp[x]%=mod;
	}
	return dp[x];
}
int main() {
	scanf("%d",&n);
	for(re int i=1;i<=n;i++)
		for(re int j=i;j<=n;j+=i) v[j].push_back(i);
	f[1]=mu[1]=1;
	for(re int i=2;i<=n;i++) {
		if(!f[i]) p[++p[0]]=i,mu[i]=-1;
		for(re int j=1;j<=p[0]&&p[j]*i<=n;j++) {
			f[p[j]*i]=1;
			if(i%p[j]==0) break;
			mu[p[j]*i]=-1*mu[i];
		}
	}
	LL inv=ksm(n,mod-2);
	for(re int i=1;i<=n;i++) {
		for(re int j=0;j<v[i].size();j++) {
			int now=0,x=v[i][j];
			if(v[i][j]==i) continue;
			for(re int k=j;k<v[i].size();k++) {
				int t=v[i][k];
				if(t%x==0) now+=mu[t/x]*(n/t);
			}
			add(i,x,now*inv%mod);
		}
		a[i]=n/i;
		a[i]=(a[i]*inv)%mod;
	}
	for(re int i=1;i<=n;i++) add(0,i,inv);
	vis[1]=0;
	std::cout<<dfs(0);
	return 0;
}
```

---

## 作者：_wkjzyc (赞：2)

提供一种复杂度较劣但易于理解的做法。

考虑枚举加入最后一个数之前，所有数的 $\gcd$。先单独讨论直接加 $1$ 的情况，贡献期望长度 $\frac{1}{m}$。

剩下的答案记为 $ans$。有：

$$\begin{aligned}ans&=\sum\limits_{i=1}^{+\infty}\frac{i+1}{m^{i+1}}\sum\limits_{j=2}^m(\sum\limits_{(a_1,\cdots ,a_i)}[\gcd(a_1,\cdots,a_i)=j])\times(\sum\limits_{k=1}^m[\gcd(k,j)=1])\end{aligned}$$

设 $g(j)=\sum\limits_{k=1}^m[\gcd(k,j)=1]$，直接反演然后筛出。

$$\begin{aligned}ans&=\sum\limits_{i=1}^{+\infty}\frac{i+1}{m^{i+1}}\sum\limits_{j=2}^m g(j)\sum\limits_{(a_1,\cdots ,a_i)}\sum\limits_{d\mid\gcd(a_1/j,\cdots,a_i/j)}\mu(d)    \\&=\sum\limits_{j=2}^{m}g(j)\sum_{d=1}^{\left \lfloor\frac{m}{j} \right \rfloor}\mu(d)\sum\limits_{(a_1,\cdots,a_i)}[\forall k,dj\mid a_k]\frac{i+1}{m^{i+1}}\\&=\sum\limits_{j=2}^{m}g(j)\sum_{d=1}^{\left \lfloor\frac{m}{j} \right \rfloor}\mu(d)\sum\limits_{i=1}^{+\infty}\left \lfloor \frac{m}{dj} \right \rfloor^i\frac {i+1} {m^{i+1}} \\&=\sum\limits_{j=2}^{m}g(j)f(\left \lfloor \frac{m}{j}\right \rfloor) \end{aligned}$$

其中 $f(x)=\sum\limits_{d=1}^x \mu(d)\sum\limits_{i=1}^{+\infty}(\frac{\left\lfloor\frac{x}{d}\right\rfloor}{m})^i(i+1)$。后一个和式就是经典的等差乘等比问题，化简后是关于 $\left \lfloor\frac{x}{d}\right \rfloor$ 的式子，整除分块求出即可。

---

（20211130 更新）

注意到 $f$ 的取值只有 $\sqrt m$ 种，求答案可以 $\mathcal{O}(m)$。再考虑预处理，总的复杂度则是 $\mathcal{O}(m\log m)$。预处理可能可以优化到线性，不过我不会。

---

## 作者：wjyyy (赞：2)

反演套 DP 的好题（不用反演貌似也能做 参考[官方 Tutorial](https://codeforces.com/blog/entry/66101)

在我的博客查看：[**传送门**](http://www.wjyyy.top/3403.html)

因为每一步不会让已经选了的元素的 $\gcd$ 和变大，因此认为是一个除自环外的有向无环图。对于自环我们很好处理，所以把它看成是一道期望 DP。

令 $f[i]$ 表示当前的 $\gcd$ 和为 $i$，到 $\gcd$ 和为 $1$ 的状态的期望步数。因此把状态转移方程写出来 
$$
f[i]=1+\frac{\sum_{j=1}^m f[\gcd(i,j)]}m
$$
这样的转移是 $O(m^2)$ 的。但是我们发现，对于很多 $j$，$\gcd(i,j)$ 都是相等的，因此我们把这样的数整合到一起。

令 $F(n)$ 表示 $1\sim m$ 中有多少个数 $i$ 满足 $\gcd(x,i)=n$，其中视 $x$ 为常数。

则计算 $f[i]$ 就转化为了
$$f[i]=1+\frac{\sum_{d|i}f[d]\times F(d)}n,x=i$$
这样差不多就把枚举优化到了 $\log n$ 的 $d|i$。

考虑怎么计算 $F(n)$
$$F(n)=\sum_{i=1}^m[\gcd(x,i)=n]$$
令 $G(n)=\sum_{n|d}F(d)$，则
$$\begin{aligned}G(n)&=\sum_{n|d}F(d)\\&=\sum_{n|d}\sum_{i=1}^m[\gcd(x,i)=d]\\&=\sum_{i=1}^m[n|\gcd(x,i)]\\?&=\sum_{i=1}^{\left\lfloor\frac mn\right\rfloor}\left[1|\gcd\left(\frac xn,i\right)\right]\end{aligned}$$
实际上这样是有问题的，因为（在后面）无法保证 $n|x$，此时 $G(n)$ 就一定为 $0$ 了。

我们再多化一步：
$$\begin{aligned}G(n)&=\sum_{i=1}^{\left\lfloor\frac mn\right\rfloor}\left[1|\gcd\left(\frac xn,i\right)\right][n|x]\\&=\left\lfloor\frac mn\right\rfloor\cdot[n|x]\end{aligned}$$
根据 $G(n)=\sum_{n|d}F(d)$，我们反演到 $F$，得
$$\begin{aligned}F(n)&=\sum_{n|d}\mu\left(\frac dn\right)G(d)\\&=\sum_{i=1}^{\left\lfloor\frac mn\right\rfloor}\mu(i)G(ni)\\&=\sum_{i=1}^{\left\lfloor\frac mn\right\rfloor}\mu(i)\left\lfloor\frac{m}{ni}\right\rfloor[(ni)|x]\end{aligned}$$
我们发现后面的布尔表达式可以当作条件。原本的条件本来就是 $\to +\infty$ 的，只不过超过了 $\left\lfloor\frac mn\right\rfloor$ 没有意义。因此直接把条件换成 $[(ni)|x]$ 即可。又因为 $n|x$ 在上面的枚举过程中是成立的，同时可以转化为 $\left[i|\frac xn\right]$。
$$F(n)=\sum_{i|\frac xn}\mu(i)\left\lfloor\frac{m}{ni}\right\rfloor$$
这样的一次枚举是 $O\left(d\left(\frac xn\right)\right)$ 的，由于 $1\sim m$ 的约数个数和均摊是 $O(\log m)$ 的，其中最多的有 $128$ 个约数，但是这样的数肯定不是很多，并且其中很多被枚举到的数都是质因数，迭代一下并不会造成很大的复杂度。

然后我们需要再把状态转移方程稍微转化一下，把 $f[i]$ 移到左边
$$\begin{aligned}f[i]&=1+\frac{\sum_{d|i,d<i}f[d]\times F(d)+f[i]\times F(i)}n,x=i\\\frac{n-F(i)}{n}\cdot f[i]&=1+\frac{\sum_{d|i,d\neq i}f[d]\times F(d)}n,x=i\\f[i]&=\frac{n+\sum_{d|i,d<i}f[d]\times F(d)}{n-F(i)},x=i\end{aligned}$$
就得到了真正的转移方程。

时间复杂度 $O(m\log^2 m)$。

## Code：

```cpp
#include<cstdio>
#include<cstring>
#include<vector>
#define ll long long
#define p 1000000007
using std::vector;
vector<int> v[100100];//约数用 vector 存一下，每次 √m 枚举不是很稳
ll qpow(ll x,ll y)
{
    ll ans=1;
    while(y)
    {
        if(y&1)
            ans=ans*x%p;
        x=x*x%p;
        y>>=1;
    }
    return ans;
}
bool is[100100];
int pri[100100],mu[100100],cnt=0;
ll f[100100];
int n;
int calc(int x,int y)//1~n 中 gcd(x,i)=y 的数的个数
{
    int g=x/y,ans=0;
    for(int i=0;i<v[g].size();++i)
        ans+=mu[v[g][i]]*(n/v[g][i]/y);
    return ans;
}
int main()
{
    scanf("%d",&n);
    f[1]=1;
    mu[1]=1;
    for(int i=2;i<=n;++i)
    {
        if(!is[i])
        {
            pri[++cnt]=i;
            mu[i]=-1;
        }
        for(int j=1;j<=cnt&&i*pri[j]<=n;++j)
        {
            is[i*pri[j]]=1;
            if(i%pri[j])
                mu[i*pri[j]]=-mu[i];
            else
            {
                mu[i*pri[j]]=0;
                break;
            }
        }
    }
    for(int i=1;i<=n;++i)
        for(int j=i;j<=n;j+=i)
            v[j].push_back(i);
    ll ans=1,inv=qpow(n,p-2);
    for(int i=2;i<=n;++i)
    {
        for(int j=0;j<v[i].size()-1;++j)
            f[i]=(f[i]+calc(i,v[i][j])*f[v[i][j]]%p)%p;
        f[i]=(f[i]*inv+1)%p;
        ll g=n-calc(i,i);
        f[i]=f[i]*n%p*qpow(g,p-2)%p;
        ans=(ans+f[i])%p;
    }
    printf("%lld\n",ans*qpow(n,p-2)%p);
    return 0;
}
```


---

## 作者：Jerryfish (赞：0)

## Preface
不会 dp，所以反演（感谢@judgelight）。

管理没理，再发一遍。
## Solution
考虑期望式子：
$$
\begin{aligned}
\operatorname{E}(len)&=\operatorname{P}(len=i)\times i\\
&=\sum_i\operatorname{P}(len=i)\sum_{j=1}^i1\\
&=\sum_i\sum_{j=1}^i\operatorname{P}(len=i)\\
&=\sum_j\sum_{i\ge j}\operatorname{P}(len=i)\\
&=\sum_j\operatorname{P}(len\ge j)\\
&=1+\sum_j\operatorname{P}(len>j)\\
&=1+\sum_j1-\operatorname{P}(len\le j)\\
\end{aligned}
$$
设 $\operatorname{f}_{i,j}$ 表示 $len=i,gcd=j$ 的方案数，$\operatorname{F}_{i,j}$ 表示 $len=i,
j|gcd$ 的方案数。

则：

$$
\begin{aligned}
\operatorname{F}_{i,j}&=\sum_{j|d}\operatorname{f}_{i,d}=\lfloor\frac{m}{j}\rfloor^i\\
\operatorname{f}_{i,j}&=\sum_{j|d}\mu(\frac{d}{j})\operatorname{F}_{i,d}\\
\operatorname{f}_{i,j}&=\sum_{j|d}\mu(\frac{d}{j})\lfloor\frac{m}{d}\rfloor^i\\
\end{aligned}
$$

题目要求 $\gcd=1$，所以我们只关注 $\operatorname{f}_{i,1}$，则：

$$
\operatorname{f}_{i,1}=\sum_{d=1}^m\mu(d)\lfloor\frac{m}{d}\rfloor^i
$$

根据定义，$\operatorname{P}(len\le j)=\frac{\operatorname{f}_{j,1}}{m^j}$，为什么上面那一坨不是 $\sum_{k=1}^{j} \operatorname{f}_{k,1}$ 呢，因为如果长度在小于 $j$ 时 $\gcd$ 已经等于 $1$ 了的话，无论怎样添加数，$\gcd$ 都恒为 $1$。

让我们再看回期望式子：

$$
\begin{aligned}
\operatorname{E}(len)&=1+\sum_j1-\operatorname{P}(len\le j)\\
&=1+\sum_j1-\frac{\operatorname{f}_{j,1}}{m^j}\\
&=1+\sum_j1-\frac{\sum_{d=1}^m\mu(d)\lfloor\frac{m}{d}\rfloor^j}{m^{j-1}}\\
&=1+\sum_j\frac{m^{j}-\sum_{d=1}^m\mu(d)\lfloor\frac{m}{d}\rfloor^{j}}{m^j}\\
&=1-\sum_j\sum_{d=2}^m\mu(d)\frac{\lfloor\frac{m}{d}\rfloor^j}{m^{j}}\\
&=1-\sum_{d=2}^m\mu(d)\sum_{j}\left(\frac{\lfloor\frac{m}{d}\rfloor}{m}\right)^j\\
\end{aligned}
$$

现在 $j$ 还无法处理，那我们处理一下。

发现：

令 $S=x^1+x^2+x^3+\dots$

∴$xS=x^2+x^3+x^4+\dots$

∴$(x-1)S=-x$

即 $S=\frac{x}{1-x}$

知道了这个，$j$ 自然就解决了：

$$
\begin{aligned}
\operatorname{E}(len)&=1-\sum_{d=2}^m\mu(d)\sum_{j}\left(\frac{\lfloor\frac{m}{d}\rfloor}{m}\right)^j\\
&=1-\sum_{d=2}^m\mu(d)\frac{\frac{\lfloor\frac{m}{d}\rfloor}{m}}{1-\frac{\lfloor\frac{m}{d}\rfloor}{m}}\\
&=1-\sum_{d=2}^m\mu(d)\frac{\lfloor\frac{m}{d}\rfloor}{m-\lfloor\frac{m}{d}\rfloor}\\
\end{aligned}
$$

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5, mod = 1e9 + 7;

int m;
int primes[N], idx, miu[N], tmp;
bool st[N];

int ksm(int a, int b, int p) {
	int res = 1;
	while(b) {
		if(b & 1) res = (1ll * res * a) % p;
		a = (1ll * a * a) % p;
		b >>= 1;
	}
	return res;
} 
#define inv(x) ksm(x, mod - 2, mod)

void euler(int N){
	miu[1] = 1; N ++ ;
	for (int i = 2; i < N; ++ i ) {
		if(!st[i]) primes[ ++ idx] = i, miu[i] = -1;
		for (int j = 1, p = primes[1]; j <= idx && p * i < N; ++ j , p = primes[j]) {
			st[p * i] = 1;
			if(i % p == 0) {miu[p * i] = 0; break;}
			miu[p * i] = -miu[i];
		}
	}
}

int main(){
	cin >> m; 
	euler(m);
	for (int d = 2; d <= m; ++ d ) 
		tmp = ((tmp + 1ll * miu[d] * (m / d) * inv(m - m / d)) % mod + mod) % mod;
	cout << ((1 - tmp) % mod + mod) % mod;
	return 0;
}
```

---

## 作者：diandian2020 (赞：0)

给一个数列，每次随机选一个 $1$ 到 $m$ 之间的数加在数列末尾，数列中所有数的 $\gcd=1$ 时停止，求期望长度 $\bmod 10^9+7$。

$1 \leq m \leq 10^5$。

莫反神仙题。

开始尽量还是转化一下问题。假设我们最终的序列是 $a_1,a_2,...,a_i$，则有 $\gcd_{j=1}^ia_j=1$。

考虑这件事发生的概率 $P(\gcd_{j=1}^ia_j=1)=\frac{\sum_{a_1=1}^m\sum_{a_2=1}^n...\sum_{a_i=1}^m[\gcd_{j=1}^ia_j=1]}{m^i}$。

$=\frac{\sum_{a_1=1}^m\sum_{a_2=1}^n...\sum_{a_i=1}^m\sum_{d|a_1,d|a_2,...,d|a_i}\mu(d)}{m^i}$。

$=\frac{\sum_{d=1}^m\mu(d)(\lfloor\frac{m}{d}\rfloor)^i}{m^i}$。

设最终长度为 $len$，则它正好是 $P(len \leq i)$。（注意不是 $P(len=i)$，因为可能不到 $i$ 项 $gcd=1$ 就直接停止了，所以 $1 \sim i$ 都有可能）

然后思考其与答案 $E$ 的关系：$E=\sum_{i \geq 1}P(len=i)i$。

$=\sum_{i \geq 1}P(len=i)\sum_{j=1}^i1$。

$\sum_{j \geq 1}\sum_{i \geq j}P(len=i)$。

$=\sum_{i \geq 1}P(len \geq i)$。

$=1+\sum_{i \geq 1}P(len>i)$。

$=1+\sum_{i \geq 1}[1-P(len \leq i)]$。

上述为求离散期望经典套路。——Graygoo佬

然后带入就行了，$E=1+\sum_{i \geq 1}[1-P(len \leq i)]=1+\sum_{i \geq 1}[1-\frac{\sum_{d=1}^m\mu(d)(\lfloor\frac{m}{d}\rfloor)^i}{m^i}]$。

$=1+\sum_{i \geq 1}\frac{\sum_{d=2}^m\mu(d)(\lfloor\frac{m}{d}\rfloor)^i}{m^i}$。

$=1-\sum_{d=2}^m\mu(d)\sum_{i \geq 1}(\frac{\lfloor\frac{m}{d}\rfloor}{m})^i$。

$=1-\sum_{d=2}^m\mu(d)\frac{\lfloor\frac{m}{d}\rfloor}{m-\lfloor\frac{m}{d}\rfloor}$。（最后一步为无穷级数求和）

接下里就简单了，线性筛 $\mu$ 然后对 $d$ 数论分块即可。因为快速幂会多个 $\log$，所以最终时间复杂度为 $\mathcal{O}(m+\sqrt{m} \log m)$。

~~既然预处理复杂度比单次询问慢，为何不多测呢？~~

既然不多测，就不数论分块了，直接暴力枚举 $d$ 好了。

代码如下：
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long LL;
const int N=1e5+9,P=1e9+7;
int qmi(int a,int b){
	int res=1;
	while(b){
		if(b&1) res=(LL)res*a%P;
		a=(LL)a*a%P;
		b>>=1;
	}
	return res;
}
int m; 
int primes[N],cnt,mu[N]; bool st[N];
void init(int n){
	mu[1]=1;
	for(int i=2;i<=n;i++){
		if(!st[i]) primes[++cnt]=i,mu[i]=-1;
		for(int j=1;primes[j]<=n/i;j++){
			int t=primes[j]*i;
			st[t]=1;
			if(i%primes[j]==0){
				mu[t]=0;
				break;
			}
			mu[t]=-mu[i];
		}
	}
}
int main(){
	scanf("%d",&m);
	init(m);
	int res=1;
	for(int d=2;d<=m;d++) res=(res-(LL)mu[d]*(m/d)%P*qmi(m-m/d,P-2)%P+P)%P;
	printf("%d\n",res);
	return 0;
} 
```

---

## 作者：WeLikeStudying (赞：0)

- 归零心态。

**题意**
- 生成值域在 $[1,m]$ 内随机的无穷自然数列，求它的最短满足最大公约数为 $1$ 的前缀的期望长度。
- $m\le 10^5$。

**分析**
- 一下就想到了高斯消元，很快啊！
- 设 $p_i$ 为以 $i$ 为公约数的情况后面的期望长度（$p_1=0$），那么答案是：
$$1+\frac 1m\sum_{i=1}^mp_i$$
- 且满足约束条件：
$$p_i=1+\frac 1m\sum_{j=1}^mp_{\gcd(i,j)}$$
- 你立刻就发现了不对劲：$p_i$ 是单调的，而且 $p_i$ 只和它的约数有关系呢！我们拆开贡献系数：
$$p_i=1+\frac 1m\sum_{d|i}p_d\sum_{j=1}^m[\gcd(i,j)=d]=1+\frac 1m\sum_{d|i}p_d\sum_{j=1}^{\lfloor m/d\rfloor}\epsilon(\gcd(i/d,j/d))$$
- 设：
$$g(n,m)=\sum_{j=1}^m\epsilon(\gcd(n,j))=\sum_{j=1}^m\sum_{d|n,d|j}\mu(d)=\sum_{d|n}\mu(d)\lfloor m/d\rfloor$$
$$p_i=1+\frac 1m\sum_{d|i}p_dg(n/d,\lfloor m/d\rfloor)$$
- 这东西……似乎真可以过，但是我绝对不任它来……真是太离谱了，这是什么鬼，居然是 $O(n\log^2n)$ 的复杂度，[代码](https://www.luogu.com.cn/paste/81civsdg)。
- 如果把里面那个东西展开：
$$p_i=1+\frac 1m\sum_{d|i}\sum_{gd|i}p_d\mu(g)\lfloor m/(d\cdot g)\rfloor=1+\frac 1m\sum_{T|i}\lfloor m/T\rfloor\sum_{d|T}p_d\mu(T/d)$$
- 设：
$$f(n)=\sum_{d|n}p_d\mu(n/d)$$
$$p_i=1+\frac 1m\sum_{d|i}\lfloor m/d\rfloor f(d)$$
- 这个式子显然可以做到 $O(n\log n)$ 的复杂度，[代码](https://www.luogu.com.cn/paste/xhacdobr)。
- 如果想要追求线性乃至更快的复杂度，我们显然需要转换一个角度，另辟蹊径。
- 枚举步数看似极不可行，但却是解决这个问题的突破口。
- 设 $F(n,m,k)$ 为：随机 $n$ 个 $[1,m]$ 的整数，最大公约数为 $k$ 的概率。
- 设 $G(n,m,k)$ 为：随机 $n$ 个 $[1,m]$ 的整数，最大公约数为 $k$ 的倍数的概率。
- 显然：
$$G(n,m,k)=\frac{\lfloor m/k\rfloor^n}{m^n}$$
$$G(n,m,k)=\sum_{k|d}F(n,m,d)$$
$$F(n,m,k)=\sum_{k|d}\mu(d)G(n,m,d)=\frac1{m^n}\sum_{k|d}\mu(d)\lfloor m/d\rfloor^n$$
- 我们要求的就是：
$$1+\sum_{i=1}^{\infty}(1-F(i,m,1))=1+\sum_{i=1}^{\infty}(1-\frac1{m^i}\sum_{d=1}^m\mu(d)\lfloor m/d\rfloor^i)=1-\sum_{i=1}^{\infty}\frac1{m^i}\sum_{d=2}^m\mu(d)\lfloor m/d\rfloor^i$$
- 套路地交换求和号：
$$1-\sum_{d=2}^m\mu(d)\sum_{i=1}^{\infty}\bigg(\frac{\lfloor m/d\rfloor}m\bigg)^i=1-\sum_{d=2}^m\mu(d)\frac{\lfloor m/d\rfloor}{m-\lfloor m/d\rfloor}$$
- 这个可以 $O(n)$ 预处理 $O(\sqrt n)$ 处理单次查询，对于这题，我们能使用杜教筛做到 $O(n^{2/3})$ 的复杂度，[代码](https://www.luogu.com.cn/paste/ymyv8rbu)。
- 最后，值得一提的是：设答案为 $F(m)$，容易发现：
$$F(n)-F(n-1)=\sum_{d|n}\mu(d)\bigg(\frac{1-d}{2d-1}+\frac{1}{1-d}\bigg)$$
- 所以理论上可以用 $O(n\log\log n)$ 筛出 $F(1)$ 到 $F(n)$。

---

## 作者：chenxia25 (赞：0)

很难想象为什么这题只是个 div2D，且难度只有 *2300/qd（可能是我太弱了吧）

考虑枚举第一个选的数 $x$，求期望次数。设 $x=\prod p_i^{\alpha_i}$，那么就是一直选数直到对每个 $p_i$ 都选了至少一个与其互质的数就停。到这儿就是个经典的 minmax 模型了，设 $t_i$ 表示与 $p_i$ 互质的数第一次被选的时间，那么就是求 $\mathrm E(\max\{t_i\})$。反演一下：
$$
\mathrm E(\max\{t_i\})=\sum\limits_{S\subseteq\{p_i\},S\neq\varnothing}(-1)^{|S|+1}\mathrm E\!\left(\min\limits_{i\in S}\{t_i\}\right)
$$
min 就是第一次互质于至少一个 $p\in S$。互质于至少一个 $p\in S$，相当于不被 $y=\prod_{p\in S}p$ 整除。这就很好办，五岁小儿亦可解之：这样的数有 $n-\left\lfloor\dfrac ny\right\rfloor$ 个，取到的概率为 $1-\dfrac{\left\lfloor\frac ny\right\rfloor}n$，所以取到的期望时间是 $\dfrac1{1-\dfrac{\left\lfloor\frac ny\right\rfloor}n}=\dfrac{n}{n-\left\lfloor\frac ny\right\rfloor}$。所以
$$
\mathrm E(\max\{t_i\})=n\sum\limits_{S\subseteq\{p_i\},S\neq\varnothing}(-1)^{|S|+1}\dfrac1{n-\left\lfloor\frac{n}{\prod_{p\in S}p}\right\rfloor}
$$
注意到质因子集合上的容斥系数可以用 $\mu$ 表示，于是
$$
\mathrm E(\max\{t_i\})=-n\sum\limits_{y\mid x,y>1}\mu(y)\dfrac1{n-\left\lfloor\frac{n}{y}\right\rfloor}
$$
到这一步就很简单了。注意到 $\sum$ 后面的式子只与 $y$ 有关，记为 $f(y)$。枚举 $x$ 时，考虑每个 $y$ 贡献了多少次，显然是 $\left\lfloor\dfrac ny\right\rfloor$。最后取平均数正好把 $n$ 消掉了，并且要加上开头选一次的次数，答案就是
$$
1-\sum_{y=2}^n\mu(y)\dfrac{\left\lfloor\frac ny\right\rfloor}{n-\left\lfloor\frac ny\right\rfloor}
$$


---

## 作者：Plozia (赞：0)

宣传博客 $\to$ [link](https://blog.csdn.net/BWzhuzehao/article/details/123216994)

一道莫反好题。

先证个式子：$E(X)=\sum_{i\ge 1}P(X \ge i)$，也就是最终长度为 $X$ 的期望是所有最终长度小于等于 $X$ 的概率之和。

证明：$E(X)=\sum_{i\ge 1}iP(X=i)=\sum_{i\ge 1}\sum_{1\le j\le i}P(X=i)=\sum_{j\ge 1}\sum_{i\ge j}P(X=i)=\sum_{j\ge1}P(x\ge j)$。

考虑容斥，最终长度大于等于 $i$ 等价于长度为 $i-1$ 的序列 $\gcd$ 大于 1，这个可以用 1 减去 $\gcd=1$ 的概率，注意这里的 $i \ge 2$。

概率用满足条件方案数 / 总方案数计算，总方案数 $m^{i-1}$，因此只需要计算 $i-1$ 时 $\gcd=1$ 的方案数即可。

推 $\gcd=1$ 的式子：$\sum_{1 \le a_1,a_2,...,a_{i-1} \le m}[\gcd(a_1,a_2,...,a_{i-1})=1]$

莫比乌斯反演，得到 $\sum_{1 \le a_1,a_2,...,a_{i-1}\le m}\sum_{d \mid \gcd(a_1,a_2,...,a_{i-1})}\mu(d)$

换个枚举顺序，顺便处理一下求和符号得到 $\sum_{d=1}^{m}\mu(d)\lfloor\dfrac{m}{d}\rfloor^{i-1}$

然后开始计算答案式子，为 $1+\sum_{i\ge2}\dfrac{m^{i-1}-\sum_{d=1}^m\mu(d)\lfloor\dfrac{m}{d}\rfloor^{i-1}}{m^{i-1}}$。

$i-1$ 太丑，令 $i \gets i-1$，得到 $1+\sum_{i\ge1}\dfrac{m^i-\sum_{d=1}^m\mu(d)\lfloor\dfrac{m}{d}\rfloor^i}{m^i}$。

注意到 $d=1$ 时 $\sum_{d=1}^{m}\mu(d)\lfloor\dfrac{m}{d}\rfloor^i=m^i$，因此将这一部分提出来与 $m^i$ 消掉。

然后交换求和符号，得到 $1-\sum_{d=1}^{m}\mu(d)(\dfrac{\lfloor\frac{m}{d}\rfloor}{m})^i$。

因为 $\dfrac{\lfloor\frac{m}{d}\rfloor}{m}<1$，根据 $x<1 \to \sum_{i\ge1}x^i=\dfrac{x}{1-x}$（貌似是用生成函数推的），得到 $1-\sum_{d=1}^{m}\mu(d)\dfrac{\dfrac{\lfloor\frac{m}{d}\rfloor}{m}}{m-\dfrac{\lfloor\frac{m}{d}\rfloor}{m}}$，然后整除分块即可。

GitHub：[CodeBase-of-Plozia](https://github.com/Plozia/CodeBase-of-Plozia/blob/main/%E6%95%B0%E5%AD%A6%26%E6%95%B0%E8%AE%BA/%E8%8E%AB%E6%AF%94%E4%B9%8C%E6%96%AF%E5%87%BD%E6%95%B0%E4%B8%8E%E5%8F%8D%E6%BC%94%EF%BC%88%E5%90%AB%E6%95%B4%E9%99%A4%E5%88%86%E5%9D%97%EF%BC%89/CF1139D%20Steps%20to%20One.cpp)

Code：

```cpp
/*
========= Plozia =========
	Author:Plozia
	Problem:CF1139D Steps to One
	Date:2022/3/1
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 1e5 + 5;
const LL P = 1e9 + 7;
int t, n, cntPrime, Prime[MAXN];
LL mu[MAXN], inv[MAXN];
bool book[MAXN];

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = sum * 10 + (ch ^ 48);
	return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }
LL ksm(LL a, LL b = P - 2, LL p = P)
{
	LL s = 1 % p;
	for (; b; b >>= 1, a = a * a % p)
		if (b & 1) s = s * a % p;
	return s;
}

void init()
{
	book[1] = mu[1] = 1;
	for (int i = 2; i <= n; ++i)
	{
		if (!book[i]) { Prime[++cntPrime] = i; mu[i] = -1; }
		for (int j = 1; j <= cntPrime; ++j)
		{
			if (i * Prime[j] > n) break ;
			book[i * Prime[j]] = 1;
			if(i % Prime[j] == 0) { mu[i * Prime[j]] = 0; break ; }
			mu[i * Prime[j]] = -mu[i];
		}
	}
	for (int i = 2; i <= n; ++i) mu[i] = mu[i - 1] + mu[i];
}

int main()
{
	n = Read(); init(); LL ans = 0;
	for (int i = 1; i <= n; ++i) inv[i] = ksm(i);
	for (int l = 2, r; l <= n; l = r + 1)
	{
		r = Min(n / (n / l), n);
		ans = (ans + (mu[r] - mu[l - 1]) * (n / l) % P * inv[n - (n / l)] % P) % P;
	}
	ans = ((1 - ans) % P + P) % P;
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：Tony102 (赞：0)

[Link](https://www.luogu.com.cn/problem/CF1139D)

## Sol

设 $len$ 为随机出来的一个序列长度。

$$E(len) = \sum\limits_{i \geq 1} P(len = i) \times i$$

$$E(len) = \sum\limits_{i \geq 1} P(len = i) \sum\limits_{j=1}^{i} 1$$

$$E(len) = \sum\limits_{j \geq 1} \sum\limits_{i \geq j} P(len = i) = \sum\limits_{i \geq 1} P(len \geq i) = 1 + \sum\limits_{i \geq 1} P(len > i)$$

现在来处理后面的 $\sum\limits_{i \geq 1} P(len > i)$

$$P(len > i) = P((gcd_{j=1}^{i} a_i) > 1)$$

> 阴阳师：“正难则反”

$$P(len > i) = 1 - P((gcd_{j=1}^{i} a_i) = 1)$$

对于序列中的每一个数，其实都可以枚举它们是 $[1,m]$ 中的哪一个，再除掉 $m^i$ 为 $i$ 个球放在 $m$ 个标有数字的盒子中，且允许有数字没出现过的总方案数。

$$lsh = \frac{\sum_{a_1 = 1}^{m}\sum_{a_2 = 1}^{m}\cdots \sum_{a_{i} = 1}^{m} \epsilon(gcd_{j=1}^{i} a_j)}{m^i} $$

对最后一层的求和符号使用莫比乌斯反演

$$lsh = \frac{\sum_{a_1 = 1}^{m}\sum_{a_2 = 1}^{m}\cdots \sum_{a_{i} = 1}^{m}\sum_{d|(gcd_{j = 1}^{i} a_j)} \mu(d)}{m^i} $$

对每一层都莫比乌斯反演，把枚举的 $d$ 提到最前面去

$$lsh = 1 - \frac{\sum_{d=1}^{m} \mu(d)\sum_{a_1=1}^{m} [d|a_1] \cdots}{m^i}$$

后面的部分上指标同时除以 $d$ 之后可以直接拿出来

$$lsh = \frac{\sum_{d=1}^{m} \mu(d) (\lfloor \frac{m}{d} \rfloor)^i}{m^i}$$

$$lsh = 1 - \frac{\sum_{d=2}^{m} \mu(d) (\lfloor \frac{m}{d} \rfloor)^i}{m^i}$$

所以带回原式可得：

$$1 - \frac{1}{m^i} \sum\limits_{i \geq 1}\sum\limits_{d=2}^{m} \mu(d)(\lfloor \frac{m}{d} \rfloor)^i$$

整除分块：

$$1-\sum\limits_{d = 2}^{m} \mu(d)\frac{\lfloor \frac{m}{d} \rfloor}{m - \lfloor \frac{m}{d} \rfloor}$$



马老师告诉你，后面那一坨类似于杜教筛预处理即可。



## Code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int SIZE = 2e5 + 5;
const int mod = 1e9 + 7;

int m, tot;
int isnPri[SIZE], pri[SIZE], mu[SIZE], inv[SIZE];

namespace GTR {
	const int bufl = 1 << 15;
	char buf[bufl], *s = buf, *t = buf;
	inline int fetch() {
		if (s == t) { t = (s = buf) + fread(buf, 1, bufl, stdin); if (s == t) return EOF; }
		return *s++;
	}
	inline int read() {
		int a = 0, b = 1, c = fetch();
		while (c < 48 || c > 57) b ^= c == '-', c = fetch();
		while (c >= 48 && c <= 57) a = (a << 1) + (a << 3) + c - 48, c = fetch();
		return b ? a : -a;
	}
} using GTR::read;

int qPow(int a, int b) {
    int ans = 1ll;
    for ( ; b; b >>= 1, a = a * a % mod) {
        if (b & 1) ans = ans * a % mod;
    }
    return ans % mod;
}

void init() {
    isnPri[1] = mu[1] = 1;
    for (int i = 2; i <= m + 1; ++ i) {
        if (!isnPri[i]) pri[++ tot] = i, mu[i] = -1;
        for (int j = 1; j <= tot && i * pri[j] <= m + 1; ++ j) {
            isnPri[i * pri[j]] = 1;
            if (i % pri[j]) mu[i * pri[j]] = -mu[i];
            else { mu[i * pri[j]] = 0; break; }
        }
    }
    inv[1]=1;
    for (int i = 2; i <= m + 1; ++ i) inv[i] = (mod - mod / i) * inv[mod % i] % mod;
}

signed main() {
    m = read(); init();
    int ans = 1ll;
    for (int i = 2; i <= m + 1; ++ i) ans = (ans - (mu[i] * (m / i) % mod * inv[m - m / i] % mod) + mod) % mod;
    printf("%lld\n", ans % mod);
    return 0;
}
```



---

## 作者：derta (赞：0)

设数列长度为 $k$，$E(k)$ 为 $k$ 的期望，$P(X)$ 为数列满足 $X$ 条件的概率，则
$$
\begin{aligned}
E(k)&=\sum_{i\geq 1}i \cdot P(k=i) \\
&=\sum_{i \geq 1}P(k \geq i) \\
&=1+\sum_{i \geq 1}P(k > i)
\end{aligned}
$$
令 $\gcd_{i=u}^{v}t_i=\gcd(t_u,t_{u+1},\cdots,t_{v-1},t_v)$

注意到，只要满足 $\gcd_{j=1}^{i}a_j \neq 1$，则该序列必然满足 $k > i$，故有
$$
\begin{aligned}
P(k > i)&=P\left(\gcd_{j=1}^{i}a_j \neq 1\right) \\
&=1-P\left(\gcd_{j=1}^{i}a_j = 1\right) \\
&=1-\frac{\sum_{a_1=1}^{m}\sum_{a_2=1}^{m}\cdots\sum_{a_{i-1}=1}^{m}\sum_{a_{i}=1}^{m}[\gcd_{j=1}^{i}a_j = 1]}{m^i} \\
&=1-\frac{\sum_{a_1=1}^{m}\sum_{a_2=1}^{m}\cdots\sum_{a_{i-1}=1}^{m}\sum_{a_{i}=1}^{m}\sum_{d|\gcd_{j=1}^{i}a_j }\mu(d)}{m^i} \\
&=1-\frac{\sum_{d=1}^{m}\mu(d)(\lfloor\frac{m}{d}\rfloor)^i}{m^i} \\
&=1-\frac{\mu(1)(\lfloor\frac{m}{1}\rfloor)^i+\sum_{d=2}^{m}\mu(d)(\lfloor\frac{m}{d}\rfloor)^i}{m^i} \\
&=-\frac{\sum_{d=2}^{m}\mu(d)(\lfloor\frac{m}{d}\rfloor)^i}{m^i}
\end{aligned}
$$

代入，得

$$
\begin{aligned}
E(k)&=1-\sum_{i \geq 1}\frac{\sum_{d=2}^{m}\mu(d)(\lfloor\frac{m}{d}\rfloor)^i}{m^i} \\
&=1-\sum_{i \geq 1}\sum_{d=2}^{m}\mu(d)(\frac{\lfloor\frac{m}{d}\rfloor}{m})^i \\
&=1-\sum_{d=2}^{m}\mu(d)\sum_{i \geq 1}(\frac{\lfloor\frac{m}{d}\rfloor}{m})^i \\
&=1-\sum_{d=2}^{m}\mu(d)\frac{\lfloor\frac{m}{d}\rfloor}{m-\lfloor\frac{m}{d}\rfloor}
\end{aligned}
$$

$O(m)$ 暴力计算即可

---

## 作者：木xx木大 (赞：0)

[CF1139D Steps to One](https://www.luogu.com.cn/problem/CF1139D)

本篇题解主要参考了[同校学长的英文博客](https://www.cnblogs.com/zyt1253679098/p/10584706.html)。（能用 English 写博客太巨了orz）

设 $f_i$ 表示 $gcd=i$ 时，还需要添加个数的期望个数。容易推出
$$
f_1=0,\ \ \ f_i=1+\sum_{j=1}^{m}\frac{f_{gcd(i,j)}}{m},  \ \ \ ans=1+\sum_{i=1}^{m}\frac{f_i}{m}
$$
稍微化简一下得
$$
m\times f_i=m+\sum_{j=1}^{m}{f_{gcd(i,j)}}
$$
这就是 $O(n^2 )$ 的 dp 式。我们考虑优化。看到 gcd ，我们想到莫反。开始推式子：
$$
m\times f_i=m+\sum_{j=1}^{m}{f_{gcd(i,j)}}=m+\sum_{d|i}f_d\sum_{j=1}^{m}[gcd(i,j)==d]
$$
$d=i$ 时，统计答案不方便，于是我们消掉这一影响。$d=i$ 时，$\sum_{j=1}^{m}[gcd(i,j)==d]=\lfloor {\frac{m}{i}}\rfloor$。于是有
$$
(m-\lfloor {\frac{m}{i}}\rfloor)\times f_i=m+\sum_{d|i,d\neq i}f_d\sum_{j=1}^{m}[gcd(i,j)==d]
$$
把右半部分继续演，根据莫反的套路 $\mu*1=\epsilon$，可以得到
$$
\sum_{j=1}^{m}[gcd(i,j)==d]=\sum_{j=1}^{\lfloor {\frac{m}{d}}\rfloor}[gcd(\lfloor {\frac{i}{d}}\rfloor,j)==1]=\sum_{j=1}^{\lfloor {\frac{m}{d}}\rfloor}\sum_{x|j,x|{\lfloor {\frac{i}{d}}\rfloor}}\mu(x)=\sum_{x|{\lfloor {\frac{i}{d}}\rfloor}}\mu(x)\times\lfloor{\frac{\lfloor {\frac{m}{d}}\rfloor}{x}}\rfloor
$$
最后再整理一下
$$
f_i=\frac{m+\sum_{d|i,d\neq i}f_d\sum_{x|{\lfloor {\frac{i}{d}}\rfloor}}\mu(x)\times\lfloor{\frac{\lfloor {\frac{m}{d}}\rfloor}{x}}\rfloor}{m-\lfloor {\frac{m}{i}}\rfloor}
$$

（感谢同机房巨佬 zzc 帮我推式子。）

预处理出每个数的因数和 $\mu$ ，根据上式，我们可以直接求出每一个 $f_i$ 。枚举 $d$ 和 $x$ ，复杂度 $O(能过）$，大概不超过 $O(n\sqrt n)$ 吧，我不太会证。
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
namespace FGF
{
	int n,m;
	const int mo=1e9+7;
	const int N=1e5+5;
	bool vis[N];
	int cnt;
	vector<int> fac[N];
	ll mu[N],p[N],f[N],ans,inv[N];
	void init()
	{
		mu[1]=1;
		for(int i=2;i<=n;i++)
		{
			if(!vis[i])p[++cnt]=i,mu[i]=mo-1;
			for(int j=1;j<=cnt&&p[j]*i<=n;j++)
			{
				vis[p[j]*i]=1;
				if(i%p[j]==0)
				{
					mu[i*p[j]]=0;
					break;
				}
				mu[i*p[j]]=mo-mu[i];
			}
		}
		for(int i=1;i<=n;i++)
			for(int j=i;j<=n;j+=i)
				fac[j].push_back(i);
		inv[1]=1;
		for(int i=2;i<=n;i++)
			inv[i]=inv[mo%i]*(mo-mo/i)%mo;
	}
	void work()
	{
		scanf("%d",&n);
		init();
		for(int i=2;i<=n;i++)
		{
			for(int sz=fac[i].size(),j=0;j<sz;j++)
			{
				int d=fac[i][j];
				if(d==i)continue;
				ll sum=0;
				for(int s=fac[i/d].size(),k=0;k<s;k++)
					sum=(sum+mu[fac[i/d][k]]*(n/d/fac[i/d][k])%mo)%mo;
				f[i]=(f[i]+sum*f[d]%mo)%mo;
			} 
			f[i]=(f[i]+n)*inv[n-n/i]%mo;
			ans=(ans+f[i])%mo;
		}	
		printf("%lld",(ans*inv[n]%mo+1)%mo);
	}
}
int main()
{
	FGF::work();
	return 0;
}
```

---

