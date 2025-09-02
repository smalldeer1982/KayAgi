# GCDEX - GCD Extreme

## 题目描述

得定 $n$ ，求
$$\sum\limits_{i=1}^n\sum\limits_{j=i+1}^n\gcd(i,j)$$
其中 $\gcd(i,j)$ 指的是 $i$ 和 $j$ 的最大公约数。

## 说明/提示

对于 $100\%$ 的数据，$1 \le n \le 10^6$，不超过 $20000$ 组数据。

## 样例 #1

### 输入

```
10
100
200000
0```

### 输出

```
67
13015
143295493160

Time limit has been changed. Some AC solutions get TLE```

# 题解

## 作者：周道_Althen (赞：39)

我们要求的式子：
$$\sum_{i=1}^{n}\sum_{j=i+1}^{n}{\rm gcd}(i,j)$$

令：$$g(n)=\sum_{i=1}^{n-1}{\rm gcd}(i,n)$$

那么答案就是：$$\sum_{i=1}^{n}g(n)$$

现在我们逐步化简：

$$\begin{aligned}g(n)&=\sum_{i=1}^{n-1}{\rm gcd}(i,n)\\&=\sum_{d|n}d\times\sum_{i=1}^{n-1}[{\rm gcd}(i,n)=d]\\&=\sum_{d|n}d\times\sum_{i=1}^{\frac{n}{d}-1}[{\rm gcd}(i,\frac{n}{d})=1]\\&=\sum_{d|n}d\times\varphi\left(\frac{n}{d}\right)\end{aligned}$$

(注意本题的特殊性，我们需要重新定义$\varphi(1)=0$)

容易观察出，$g(d)$可以用类似于埃式筛法的方法$O(n{\rm log}n)$筛出。

预处理前缀和，就可以做到$O(1)$询问，总复杂度$O(n{\rm log}n+T)$。

那么这道题就完结撒花啦。

```cpp
#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cctype>
#include<cstdio>
#include<vector>
#include<string>
#include<queue>
#include<stack>
#include<cmath>
#include<map>
#include<set>
using namespace std;
const int inf=0x7fffffff;
const double eps=1e-10;
const double pi=acos(-1.0);
//char buf[1<<15],*S=buf,*T=buf;
//char getch(){return S==T&&(T=(S=buf)+fread(buf,1,1<<15,stdin),S==T)?0:*S++;}
inline int read(){
	int x=0,f=1;char ch;ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') f=0;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch&15);ch=getchar();}
	if(f)return x;else return -x;
}
const int N=1000010; 
bool vis[N];
long long prim[N],phi[N],ans[N];
void get_phi(int n){
  phi[1]=0;
  for(int i=2;i<=n;i++){
    if(!vis[i]){phi[i]=i-1;prim[++prim[0]]=i;}
    for(int j=1;j<=prim[0]&&i*prim[j]<=n;j++){
      vis[i*prim[j]]=1;
      if(i%prim[j]==0){phi[i*prim[j]]=phi[i]*prim[j];break;}
      else phi[i*prim[j]]=phi[i]*(prim[j]-1);
    }
  }
  for(int i=1;i<=n;i++)ans[i]=phi[i];
  for(int i=2;i*i<=n;i++){
    ans[i*i]+=phi[i]*i;
    for(int j=i+1;j*i<=n;j++)
    ans[j*i]+=phi[i]*j+phi[j]*i;
  }
  ans[1]=0;
  for(int i=2;i<=n;i++)ans[i]+=ans[i-1];
}
int n;
int main()
{
	get_phi(1000000);
  while(scanf("%d",&n)==1&&n){printf("%lld\n",ans[n]);}
	return 0;
}

```

先不着急，我们来看看另一种算法为什么会$\color{#00E}{\tt TLE}$。
比如说[UVA11426 GCD - Extreme (II)](https://www.luogu.org/problemnew/show/UVA11426)的算法。

我们要求的式子：
$$\sum_{i=1}^{n}\sum_{j=i+1}^{n}{\rm gcd}(i,j)$$

现在我们逐步化简：
$$\begin{aligned}\sum_{i=1}^{n}\sum_{j=i+1}^{n}{\rm gcd}(i,j)&=\sum_{j=1}^{n}\sum_{i=1}^{j-1}{\rm gcd}(i,j)\\&=\sum_{d=1}^{n}d\times \sum_{j=1}^{n}\sum_{i=1}^{j-1}\left[{\rm gcd}(i,j)=d\right]\\&=\sum_{d=1}^{n}d\times \sum_{j=1}^{\left\lfloor\frac{n}{d}\right\rfloor}\sum_{i=1}^{j-1}\left[{\rm gcd}(i,j)=1\right]\\&=\sum_{d=1}^{n}d\times \sum_{j=1}^{\left\lfloor\frac{n}{d}\right\rfloor}\varphi(j)\end{aligned}$$

运用数论分块，我们可以做到$O(n+T\sqrt n)$的复杂度。
仔细算一算，发现……确实有点卡……，但是$O(n{\rm log}n+T)$也没有比$O(n+T\sqrt n)$好多少。~~（毒瘤）~~

不过，你要是都已经算到这一步了，还有一种方法可以得到我们理想的答案。

已知：$$\sum_{i=1}^{n}\sum_{j=i+1}^{n}{\rm gcd}(i,j)=\sum_{d=1}^{n}d\times \sum_{j=1}^{\left\lfloor\frac{n}{d}\right\rfloor}\varphi(j)$$

我们做差：
$${\color{#F00}{X}}=\sum_{d=1}^{n}d\times \sum_{j=1}^{\left\lfloor\frac{n}{d}\right\rfloor}\varphi(j)-\sum_{d=1}^{n-1}d\times \sum_{j=1}^{\left\lfloor\frac{n-1}{d}\right\rfloor}\varphi(j)$$

令：
$${\rm size}(n,x)=\sum_{i=1}^{n}i\times\left[\left\lfloor \frac{n}{i}\right\rfloor\geq x\right]$$
代表在输入为$n$时，$\varphi(x)$被计算了多少次。

容易得到：

$$\begin{aligned}{\color{#F00}{X}}&=\sum_{d=1}^{n}d\times \sum_{j=1}^{\left\lfloor\frac{n}{d}\right\rfloor}\varphi(j)-\sum_{d=1}^{n-1}d\times \sum_{j=1}^{\left\lfloor\frac{n-1}{d}\right\rfloor}\varphi(j)\\&=\sum_{i=1}^{n}\varphi(i)\times\left({\rm size}(n,i)-{\rm size}(n-1,i)\right)\\&=\sum_{x=1}^{n}\varphi(x)\times\left(\sum_{i=1}^{n}i\times\left[\left\lfloor \frac{n}{i}\right\rfloor\geq x\right]-\sum_{i=1}^{n}i\times\left[\left\lfloor \frac{n-1}{i}\right\rfloor\geq x\right]\right)\\&=\sum_{x=1}^{n}\varphi(x)\times\left(\sum_{i=1}^{n}i\times\left(\left[\left\lfloor \frac{n}{i}\right\rfloor\geq x\right]-\left[\left\lfloor \frac{n-1}{i}\right\rfloor\geq x\right]\right)\right)\end{aligned}$$

已知$n$和$n-1$是互质的，且$n>n-1$，所以只有当i是n因数时，$\lfloor\frac{n-1}{i}\rfloor=(\lfloor \frac{n}{i}\rfloor-1)\neq\lfloor \frac{n}{i}\rfloor$；其他情况下，无论$i$与$n-1$的关系，$\lfloor\frac{n-1}{i}\rfloor=\lfloor \frac{n}{i}\rfloor$。

所以有：

$$\begin{aligned}{\color{#F00}{X}}&=\sum_{x=1}^{n}\varphi(x)\times\left(\sum_{i=1}^{n}i\times\left(\left[\left\lfloor \frac{n}{i}\right\rfloor\geq x\right]-\left[\left\lfloor \frac{n-1}{i}\right\rfloor\geq x\right]\right)\right)\\&=\sum_{x|n}\varphi(x)\times\left(\sum_{i=1}^{n}i\times\left(\left[\left\lfloor \frac{n}{i}\right\rfloor\geq x\right]-\left[\left\lfloor \frac{n-1}{i}\right\rfloor\geq x\right]\right)\right)\\&=\sum_{x|n}\varphi(x)\times i\times\left(\left[\left\lfloor \frac{n}{i}\right\rfloor\geq x\right]-\left[\left\lfloor \frac{n-1}{i}\right\rfloor\geq x\right]\right)\ \ \ \ \ (i=\frac{n}{x})\\&=\sum_{x|n}\varphi(x)\times i\times\left(\left[\left\lfloor \frac{n}{i}\right\rfloor\geq x\right]-\left[\left\lfloor \frac{n}{i}\right\rfloor-1\geq x\right]\right)\ \ \ \ \ (i=\frac{n}{x})\\&=\sum_{x|n}\varphi(x)\times i\times\left(\left[x\geq x\right]-\left[x-1\geq x\right]\right)\ \ \ \ \ (i=\frac{n}{x})\\&=\sum_{x|n}\varphi(x)\times i\ \ \ \ \ (i=\frac{n}{x})\\&=\sum_{x|n}\varphi(x)\times \frac{n}{x}\end{aligned}$$

所以有：

$$\sum_{d=1}^{n}d\times \sum_{j=1}^{\left\lfloor\frac{n}{d}\right\rfloor}\varphi(j)=\sum_{d=1}^{n}d\times \sum_{j=1}^{\left\lfloor\frac{n}{d}\right\rfloor}\varphi(j)+{\color{#F00}{\sum_{x|n}\varphi(x)\times \frac{n}{x}}}$$

然后我们就得到上面的式子啦:
$$\sum_{d=1}^{n}\sum_{d'|d}d\times\varphi\left(\frac{d}{d'}\right)$$

最后推荐几道题，7倍经验的哦！

[UVA11417 GCD](https://www.luogu.org/problemnew/show/UVA11417)；

[UVA11424 GCD - Extreme (I)](https://www.luogu.org/problemnew/show/UVA11424)；

[UVA11426 GCD - Extreme (II)](https://www.luogu.org/problemnew/show/UVA11426)；

[P1390 公约数的和](https://www.luogu.org/problemnew/show/P1390)；

[P2398 GCD SUM](https://www.luogu.org/problemnew/show/P2398)；

[P2568 GCD](https://www.luogu.org/problemnew/show/P2568)；

[SP3871 GCDEX - GCD Extreme](https://www.luogu.org/problemnew/show/SP3871)。

---

## 作者：ForgotMe (赞：25)

看了下这题的所有的题解，感觉时间复杂度都不够好，发一个 $\mathcal{O(n)}$ 预处理，$\mathcal{O(1)}$ 回答的题解。

首先，题目让我们求的是:
$$
ans=\sum\limits_{i=1}^{n-1}\sum\limits_{j=i+1}^n\gcd(i,j)
$$
转换一下可以得到
$$
ans=\dfrac{\sum\limits_{i=1}^{n}\sum\limits_{j=1}^n\gcd(i,j)-\dfrac{n^2+n}{2}}{2}
$$
设
$$
f(n)=\sum\limits_{i=1}^{n}\sum\limits_{j=1}^n\gcd(i,j)
$$
现在的问题是怎么快速求出 $f(n)$。

考虑对 $f(n)$ 差分，可以得到：

$$
f(1)=1,f(i)=f(i-1)+2\sum\limits_{j=1}^i\gcd(j,i)-i
$$
设
$$
g(n)=\sum\limits_{i=1}^n\gcd(i,n)
$$
那么
$$
f(n)=f(n-1)+2\times g(n)-n
$$
于是问题又转变为怎么快速求出 $g(n)$。

首先你得知道当 $n$ 固定时，$\gcd(i,n)$ 是积性函数，但不是完全积性函数。

换句话说：当 $i,j$ 互质时，$\gcd(i\times j,n)=\gcd(i,n)\times \gcd(j,n)$。

猜想 $g(n)$ 也是一个积性函数，这里给出证明(来自与 @alpha1022 大佬的证明)：

$$
g(n)=\sum\limits_{i=1}^n\gcd(i,n)=\sum\limits_{i=1}^n\sum\limits_{d|\gcd(i,n)}φ(d)=\sum\limits_{d|n}φ(d)\dfrac{n}{d}
$$

这是两个积性函数的狄利克雷卷积，所以 $g$ 函数为积性函数。

于是准备用线性筛去筛出 $g$ 函数，筛这种一般积性函数一般先要知道三个东西：$g(1),g(p),g(p^k)$（$p$ 为质数）。

前两个东西都易知 $g(1)=1,g(p)=2\times p-1$，关键是 $g(p^k)$ 怎么算。

因为 $p$ 为素数，可以知道只有当数 $x$ 是 $p$ 的倍数时 $\gcd(x,p^k)$ 才不为 $1$，否则一定是 $1$,于是考虑算 $x$ 是 $p$ 的倍数的情况。

老套路，枚举 $p^k$ 的因子 $d$，当然 $p^k$ 只有 $k$ 个因子（$p^1,p^2,\cdots,p^k$）。

于是可以得到 $g(p^k)=p^k+\sum_{i=1}^np^{k-i}\times(p^i-p^{i-1})=p^k+k\times p^k+k\times p^{k-1}=(k+1)\times p^k-k\times p^{k-1}$。

再讲一讲怎么线性筛。考虑在筛的过程中，$i\times prime_j$ 被 $i$ 乘上 $prime_j$ 筛掉了（$prime_j$ 是 $i$ 的最小质因子）。

于是将 $i$ 唯一分解为 $i=p_1^{a_1}p_2^{a_2}\cdots p_k^{a_k}$（$p_1<p_2<p_3<p_4<\cdots <p_k$），并记 $low_i=p_1^{a_1}$。

现在分类讨论

- 当 $prime_j\nmid i$ 时，$i$ 肯定与 $prime_j$ 互质，$g(i\times prime_j)=g(i)\times g(prime_j)$。
- 当 $prime_j\mid i$ 且 $low_i=i$ (也就是 $i\times prime_j=p^k$ ($p$ 为质数) 时，根据上面的 $g(p^k)$ 的公式算就行了，不过你需要再开一个 $cnt$ 数组去记录 $p^k$ 的 $k$ 的值。
- 当 $prime_j\mid i$ 且 $low_i\neq i$ 时，先给出转移公式：$g(i\times prime_j)=g(\dfrac{i}{low_i})\times g(prime_j\times low_i)$。为啥呢，首先可以知道 $prime_j$ 其实就等于 $low_i=p_1^{a_1}$ 中的 $p_1$，因为都是最小质因子呀，你把 $i$ 中的最小质因子 $p_1$ 的除干净了，肯定与 $low_i\times prime_j$ 互质啊，于是直接用积性函数里的公式：当 $p,q$ 互质时，积性函数 $g(p\times q)=g(p)\times g(q)$。

筛完 $g$ 函数后直接再按照上面的 $f$ 函数的公式做一遍前缀和就行了。

最后上代码 ~~（真的是写死我了）~~。

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
#define LL long long
#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 19, stdin), p1 == p2) ? EOF : *p1++)
char buf[1 << 19], *p1 = buf, *p2 = buf;
LL read() {
    LL ret = 0, f = 1;
    char ch = getchar();
    while (!isdigit(ch)) {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    for (; isdigit(ch); ch = getchar()) ret = ret * 10 + ch - 48;
    return ret * f;
}
const int MAXN = 1e6 + 5;
bool vis[MAXN];
LL n, m, len, phi[MAXN], prime[MAXN], f[MAXN], low[MAXN], cnt[MAXN];
void seive1() {
    phi[1] = 1;
    for (int i = 2; i < MAXN; i++) {
        if (!vis[i])
            prime[++len] = i, phi[i] = i - 1;
        for (int j = 1; j <= len && i * prime[j] < MAXN; j++) {
            vis[i * prime[j]] = 1;
            if (i % prime[j] == 0) {
                phi[i * prime[j]] = phi[i] * prime[j];
                break;
            }
            phi[i * prime[j]] = phi[i] * (prime[j] - 1);
        }
    }
    for (int i = 1; i < MAXN; i++) phi[i] += phi[i - 1];
}
void seive2() {
    low[1] = f[1] = 1;
    for (int i = 2; i < MAXN; i++) {
        if (!vis[i])
            prime[++len] = low[i] = i, f[i] = 2 * i - 1, cnt[i] = 1;
        for (int j = 1; j <= len && i * prime[j] < MAXN; j++) {
            vis[i * prime[j]] = 1;
            if (i % prime[j] == 0) {
                low[i * prime[j]] = low[i] * prime[j];
                if (low[i] == i)
                    cnt[i * prime[j]] = cnt[i] + 1,
                            f[i * prime[j]] = (cnt[i * prime[j]] + 1) * i * prime[j] - cnt[i * prime[j]] * i;
                else
                    f[i * prime[j]] = f[i / low[i]] * f[low[i] * prime[j]];
                break;
            }
            low[i * prime[j]] = prime[j];
            f[i * prime[j]] = f[i] * f[prime[j]];
        }
    }
    for (int i = 2; i < MAXN; i++) f[i] = 2 * f[i] - i, f[i] += f[i - 1];
}
LL calc(LL n, LL m) {
    LL ans = 0, l, r;
    for (l = 1; l <= min(n, m); l = r + 1) {
        r = min(n / (n / l), m / (m / l));
        ans += (phi[r] - phi[l - 1]) * (n / l) * (m / l);
    }
    return ans;
}
int main() {
    seive2();
    while (1) {
        n = read();
        if (!n) break;
        printf("%lld\n", (f[n] - n * (n + 1) / 2) / 2);
    }
    return 0;
}
```

码字不易，点个赞吧！！！

---

## 作者：shame_djj (赞：9)

原题连接【[SP3871 GCDEX - GCD Extreme](https://www.luogu.org/problem/SP3871)】

大体思路和其他题解是相同的

但是我没有使用大量数学符号，而是用编程语言来描绘同样的东西

个人觉得会比较好理解一些

首先，我们看到了题目中给的代码（记为ans0）：

```cpp

	G=0;

	for(i = 1 ; i < N ; i++) 
		
		for(j = i+1 ; j <= N ; j++) 
			
			G+=gcd(i,j);
                    
```


仔细看一下，我们发现了一些有趣的东西

每一个 i ，对于每一个 j 都会有一个贡献

那么我们反着想一想，反着枚举i，j

题目中的代码就变成了这么个东西（记为ans1）：

```cpp
	G = 0；

	for (j = 2; j <= N; j ++)

		for (i = 1; i < j; i ++)

			G += gcd (i, j);
```

然后呢~~

如果你做过这道题目【[[SDOi2012]Longge的问题](https://www.luogu.org/problem/P2303)】~~

那么本题你已经解决了

在那道题中，我们求这么一个东西（记为f[]）：

```cpp
	G = 0;

		for (i = 1; i <= N; i ++)
                          
			G += gcd (i, N);
```

把f[]套到ans1中，得到ans2

```cpp
	G = 0；

	for (i = 2; i <= n; i ++)

		G += f[i];
```
处理多测的话，只需要预处理一下前缀和就好了

至此，本题只剩下最后一个难点：

		f[]的处理~~
        
可以看一下来自[siyuan大佬博客](http://old.orzsiyuan.com/articles/problem-SDOI-2012-Longge-Problem/)的式子（~~请点进去，并和我一起%他~~）

（~~所以我刚才说，如果你做过P2303的话，本题就已经结束了~~）

但他那个式子其实是O（sqrt（n））的

继续优化

可以考虑一下一种类似于埃氏筛的想法

当然积性函数其实是可以线性筛的，不过我不会

但本题的话已经够了

弄出来就是这样：
```cpp
	for (register int i = 1; i < maxn; i ++)

		for (register int j = i * 2; j < maxn; j += i)

			f[j] += i * phi[j / i];
```

然后就没有然后了啊

至于怎么线性筛出欧拉函数~~

这里给出我的模板
```cpp
	phi[1] = 1;
	for (register int i = 2; i <= maxn; i ++) {
		if (!phi[i])
			phi[i] = i - 1, prime[++ cnt] = i;
		for (register int j = 1; j <= cnt && i * prime[j] <= maxn; j ++) {
			if (i % prime[j] == 0) {
				phi[i * prime[j]] = phi[i] * prime[j];
				break;
			}
			else phi[i * prime[j]] = phi[i] * prime[j] - phi[i];
		}
	}
```
数论板子什么的，还是要背的，

当然你要是能现推出来就更好了

板子的话，最好是能每一次打出来都是一个样子

然后本题就完了啊，

预处理完前缀和后就能 O（1） 回答每一次询问

我们类似于埃氏筛的东西是 O(n * logn) 的

当然其实这个东西是能 O（n）筛的（~~肯定的吖~~）

然后主函数就不给出了，给了也没什么用

新 Noip 就要来了

祝大家 rp++

也希望自己能更努力一些，加油！

---

## 作者：SSerxhs (赞：7)

把式子推到g[n]的过程楼下已经说得很清楚了，但nlogn求g[n]并不是极限复杂度。

改变一下g[n]的定义，令g[n]包含gcd(n,n)这一项，则ans为g[n]前缀和-(1+n)*n/2

这样做有什么好处呢？原g[n]化为关于phi的式子的时候，必须强制定义phi[1]=0，这会破坏phi的积性。而新的g[n]并不需要改变phi，这意味着phi依然是积性函数，而g为一个积性函数狄利克雷卷积另一个，显然也是积性函数，故可以线性筛。详见代码

```
#include <stdio.h>
#include <string.h>
const int N=1e6;
typedef long long ll;
int ss[N],phi[N+2],zx[N+2];
int n,i,j,k,gs,c;
ll g[N+2];
bool ed[N+2];
inline void read(int &x)
{
	c=getchar();
	while ((c<48)||(c>57)) c=getchar();
	x=c^48;c=getchar();
	while ((c>=48)&&(c<=57))
	{
		x=x*10+(c^48);
		c=getchar();
	}
}
int main()
{
	g[1]=phi[1]=1;
	for (i=2;i<=N;i++)
	{
		if (!ed[i])
		{
			phi[ss[++gs]=i]=i-1;
			zx[i]=i;
			g[i]=(i<<1)-1;
		}
		k=N/i;
		for (j=1;(j<=gs)&&(ss[j]<=k);j++)
		{
			ed[ss[j]*i]=1;
			if (i%ss[j]==0)
			{
				zx[i*ss[j]]=zx[i]*ss[j];
				phi[i*ss[j]]=phi[i]*ss[j];
				if (zx[i]==i) g[i*ss[j]]=g[i]*ss[j]+phi[i*ss[j]]; else g[i*ss[j]]=g[i/zx[i]]*g[zx[i]*ss[j]];
				break;
			}
			zx[i*ss[j]]=zx[ss[j]];
			g[i*ss[j]]=g[i]*((ss[j]<<1)-1);
			phi[i*ss[j]]=phi[i]*(ss[j]-1);
		}
	}
	for (i=2;i<=N;i++) g[i]+=g[i-1];
	while (1)
	{
		read(n);
		if (n==0) return 0;
		printf("%lld\n",g[n]-((1ll+n)*n>>1));
	}
}

```


---

## 作者：Gauss0320 (赞：5)

共享两种解法：

## 法$1$：适用于一组数据

考虑到
$$\sum_{i=1}^n\sum_{j=1}^n\gcd(i,j)=\sum_{i=1}^n\sum_{j=i+1}^n\gcd(i,j)+\sum_{i=1}^n\sum_{j=1}^{i-1}\gcd(i,j)+\sum_{i=1}^n\gcd(i,i)$$
化简一下得到
$$\sum_{i=1}^n\sum_{j=i+1}^n\gcd(i,j)=\frac{1}{2}\Bigg(\sum_{i=1}^n\sum_{j=1}^n\gcd(i,j)-\frac{n(n+1)}{2}\Bigg)$$
于是我们只需要处理后面那个式子就好了.

不难想到
$$\sum_{i=1}^n\sum_{j=1}^n\gcd(i,j)=\sum_{d=1}^nd\sum_{i=1}^n\sum_{j=1}^n[\gcd(i,j)=d]$$
将后面的式子反演一下
$$\sum_{i=1}^n\sum_{j=1}^n\gcd(i,j)=\sum_{d=1}^nd\sum_{i=1}^{\left\lfloor\frac{n}{d}\right\rfloor}\sum_{j=1}^{\left\lfloor\frac{n}{d}\right\rfloor}[\gcd(i,j)=1]$$
$$\ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ =\sum_{d=1}^nd\sum_{i=1}^{\left\lfloor\frac{n}{d}\right\rfloor}\sum_{j=1}^{\left\lfloor\frac{n}{d}\right\rfloor}\sum_{k|\gcd(i,j)}\mu(k)$$
$$\ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ =\sum_{d=1}^nd\sum_{k=1}^{\left\lfloor\frac{n}{d}\right\rfloor}\mu(k)\left\lfloor\frac{n}{kd}\right\rfloor^2$$
想到一个常见的套路，令$t=kd$
$$=\sum_{t=1}^n\sum_{d|t}\frac{t}{d}×\mu(d)\left\lfloor\frac{n}{t}\right\rfloor^2$$
$$=\sum_{t=1}^n\left\lfloor\frac{n}{t}\right\rfloor^2\sum_{d|t}\frac{t}{d}×\mu(d)$$
$$=\sum_{t=1}^{n}\varphi(t)\left\lfloor\frac{n}{t}\right\rfloor^2\ \ \ \ \ \ \ \ \ \ \ \ \ \ \ $$
时间复杂度$O(n+T\sqrt{n})$
## 法$2$：适用于多组数据询问
想到令
$$f(n)=\sum_{i=1}^n\gcd(i,n)$$
带回原式，我们有
$$\sum_{i=1}^n\sum_{j=i+1}^n\gcd(i,j)=\sum_{i=1}^nf(i)$$
$f(n)$为积性函数，易得其前缀和.

先化简$f(n)$
$$f(n)=\sum_{d|n}d\sum_{i=1}^n[\gcd(i,n)=d]$$
$$\ \ \ \ \ \ \ \ \ \ =\sum_{d|n}d\sum_{i=1}^{\left\lfloor\frac{n}{d}\right\rfloor}[\gcd(i,\frac{n}{d})=1]$$
$$=\sum_{d|n}d×\varphi\left(\frac{n}{d}\right)\ \ \ \ \ \ $$
总时间复杂度$O(n\log_2 n+T)$，比上述算法优越的是所有答案都可以预处理

---

## 作者：Arghariza (赞：4)

看到这个式子发现和普通的反演题很像，化简有：

$$\sum\limits_{i=1}^{n}\sum\limits_{j=i+1}^{n}\gcd(i,j)=\frac{\sum\limits_{i=1}^{n}\sum\limits_{j=1}^{n}\gcd(i,j)-\begin{pmatrix}n\\2\end{pmatrix}}{2}$$

莫比乌斯反演 $O(n+T\sqrt{n})$：

$$\begin{aligned}\sum\limits_{i=1}^{n}\sum\limits_{j=1}^{n}\gcd(i,j)&=\sum\limits_{i=1}^{n}\sum\limits_{j=1}^{n}\gcd(i,j)\\&=\sum\limits_{i=1}^{n}\sum\limits_{j=1}^{n}\sum\limits_{d=1}^{n}d[\gcd(i,j)=d]\\&=\sum\limits_{d=1}^{n}d\sum\limits_{i=1}^{n/d}\sum\limits_{j=1}^{n/d}[\gcd(i,j)=1]\\&=\sum\limits_{d=1}^{n}d\sum\limits_{i=1}^{n/d}\sum\limits_{j=1}^{n/d}\sum\limits_{k\mid i,k\mid j}\mu(k)\\&=\sum\limits_{d=1}^{n}d\sum\limits_{k=1}^{n/d}\mu(k)\sum\limits_{i=1}^{n/d}\sum\limits_{j=1}^{n/d}1\\&=\sum\limits_{d=1}^{n}d\sum\limits_{k=1}^{n/d}\mu(k)\left\lfloor\frac{n}{kd}\right\rfloor^2\end{aligned}$$
令 $p=kd$ 则有：

$$\begin{aligned}\text{原式}&=\sum\limits_{p=1}^{n}\sum\limits_{d\mid p}\frac{p}{d}\left\lfloor\frac{n}{p}\right\rfloor^2\mu(d)\\&=\sum\limits_{p=1}^{n}\left\lfloor\frac{n}{p}\right\rfloor^2\sum\limits_{d\mid p}\frac{p}{d}\times\mu(d)\end{aligned}$$

然后我们发现右边这个 $\sum$ 就是 $id*\mu=\varphi(\varphi*I=id)$

$$\begin{aligned}\text{原式}&=\sum\limits_{p=1}^{n}\varphi(p)\left\lfloor \frac{n}{p}\right\rfloor^2\end{aligned}$$

线筛 $\varphi$ 整除分块即可。

但我们更快的：

$$\begin{aligned}\sum\limits_{i=1}^{n}\sum\limits_{j=i+1}^{n}\gcd(i,j)&=\sum\limits_{i=1}^{n}\sum\limits_{j=1}^{i}\gcd(i,j)\\&=\sum\limits_{i=1}^{n}\sum\limits_{d\mid i}^{}d\sum\limits_{k=1}^{i}[\gcd(i,k)=d]\\&=\sum\limits_{i=1}^{n}\sum\limits_{d\mid i}^{}d\times\varphi(\frac{i}{d})\end{aligned}$$

线性筛 $\varphi$ 然后求出后面这个 $\sum$ 的前缀和就可以预处理出所有答案了。

你可能发现这个东西其实是 $id * \varphi$，但貌似没什么卵用。

```cpp
#include <bits/stdc++.h>
#define maxn 1000200
#define int long long
namespace mystd {
	using namespace std;
	inline int read() {
	    int w = 1, q = 0;
	    char ch = ' ';
	    while (ch != '-' && (ch < '0' || ch > '9')) ch = getchar();
	    if (ch == '-') w = -1, ch = getchar();
	    while (ch >= '0' && ch <= '9') q = q * 10 + ch - '0', ch = getchar();
	    return w * q;
	}
	
	inline void write(int x) {
	    if (x < 0) {
	        x = ~(x - 1);
	        putchar('-');
	    }
	    if (x > 9) write(x / 10);
	    putchar(x % 10 + '0');
	}
	int min(int x, int y) {
		return x < y ? x : y;
	}
}
using namespace mystd;

int n;
int s[maxn + 1], f[maxn + 1], phi[maxn + 1];

void init() {
	phi[1] = 1;
    for (int i = 2; i <= maxn; i++) {
    	if (!phi[i]) {
    		for (int j = i; j <= maxn; j += i) {
            	if (!phi[j]) phi[j] = j;
            	phi[j] = phi[j] / i * (i - 1);
        	}
		}
	}
	for (int i = 1; i <= maxn; i++) {
		for (int j = i * 2; j <= maxn; j += i) {
			f[j] += i * phi[j / i];
		}
	}
	for (int i = 3; i <= maxn; ++i) f[i] += f[i - 1];
}

signed main() {
    init();
    n = read();
    while (n) {
    	write(f[n]);
    	puts("");
    	n = read();
	}
    return 0;
}  
```

---

## 作者：翼德天尊 (赞：2)

时限毒瘤的一道题……

由于数据组数过大，我们只能考虑预处理然后 $O(1)$ 询问。

先把原式子贴出来，题目要我们求：

$$ans_n=\sum_{i=1}^n\sum_{j=i+1}^n\gcd(i,j)$$

首先先把右边的循环变为类似前缀和的形式：

$$ans_n=\sum_{i=1}^n\sum_{j=1}^{i-1}\gcd(i,j)$$

由于我们肯定是要 $O(1)$ 询问，所以我们肯定要预处理出所有 $n$ 的答案，那么只能从 $ans_{n-1}$ 推出 $ans_n$，而 $ans_{n-1}$ 为：

$$ans_{n-1}=\sum_{i=1}^{n-1}\sum_{j=1}^{i-1}\gcd(i,j)$$

设 $pre_n$ 表示 $ans_n$ 和 $ans_{n-1}$ 的差，则作差得：

$$pre_n=\sum_{i=1}^{n}\gcd(i,n)$$

将原式转化为含有条件判断式的形式：

$$pre_n=\sum_{d=1}^nd\times\sum_{i=1}^{n}[\gcd(i,n)=d]$$

将条件转化为等于 $1$：

$$pre_n=\sum_{d=1}^nd\times\sum_{i=1}^{\left\lfloor\frac{n}{d}\right\rfloor}[\gcd(i,j)=1]$$

利用 $\varphi$ 函数的定义将最后一个循环转化得：

$$pre_n=\sum_{d=1}^nd\times\varphi(\frac{n}{d})$$

考虑对于每一个 $\frac{n}{d}$，反向枚举它的倍数 $\frac{nk}{d}$，则它对于每一个 $pre_\frac{nk}{d}$ ，都会产生 $d\times\varphi(\frac{n}{d})$ 的贡献。关于 $\varphi$ 的值可以通过线性赛 $O(n)$ 解决。
 
如此以来，我们可以以仅仅调和数的复杂度，算出所有 $n$ 差分的答案。算出之后再 $O(n)$ 求出前缀和即可。

于是我们就顺利地完成单次询问 $O(1)$ 处理了。预处理复杂度约为 $O(n\text{ log } n)$。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define N 1000000
#define re register
ll zhi[N+5],ztot,phi[N+5],ans[N+5];
bool izhi[N+5]; 
inline int read(){
	int w=0,f=1;
	re char ch=getchar();
	while (ch>'9'||ch<'0'){
		if (ch=='-') f=-1;
		ch=getchar();
	}
	while (ch>='0'&&ch<='9'){
		w=(w<<3)+(w<<1)+(ch^48);
		ch=getchar();
	}
	return w*f;
}
inline void init(){
	izhi[1]=1;
	for (re int i=2;i<=N;i++){
		if (!izhi[i]) zhi[++ztot]=i,phi[i]=i-1;
		for (re int j=1;j<=ztot,i*zhi[j]<=N;j++){
			izhi[i*zhi[j]]=1;
			if (i%zhi[j]==0){
				phi[i*zhi[j]]=phi[i]*zhi[j];
				break;
			} 
			phi[i*zhi[j]]=phi[i]*phi[zhi[j]];
		}
	} 
	//for (re int i=1;i<=N;i++) phi[i]+=phi[i-1];
	for (re int i=1;i<=N;i++){
		for (re int j=1;j*i<=N;j++){
			ans[j*i]+=phi[i]*j;
		}	
	}
	for (int i=1;i<=N;i++) ans[i]+=ans[i-1]; 
}
int main(){
	init();
	re int n;
	while ((n=read())!=0){
		printf("%lld\n",ans[n]);
	}
	return 0;
}
```


---

## 作者：_•́へ•́╬_ (赞：2)

### 题面

$$
\texttt{求}G(n)=\sum\limits_{i=1}^{i<n}\sum\limits_{j=i+1}^{j\leq n}\gcd(i,j)
$$

显然 $i=n$ 时找不到 $j$，所以写了小于号。

$20000$ 组数据，$n$ 范围 $1000000$。

### 前置知识

$$
\varphi\texttt{，欧拉函数，欧拉筛素数}
$$

$$
\texttt{前缀和}
$$

### 思路

$$
G(n)=\sum\limits_{i=1}^{i<n}\sum\limits_{j=i+1}^{j\leq n}\gcd(i,j)
$$

$$
G(n)=\sum\limits_{j=2}^{j\leq n}\sum\limits_{i=1}^{i<j}\gcd(i,j)
$$

$$
G(n)=G(n-1)+\sum\limits_{i=1}^{i<n}\gcd(i,n)
$$

$$
preG(n)=\sum\limits_{i=1}^{i<n}\gcd(i,n)\texttt{,最后把preG做一个前缀和就是G}
$$

$$
preG(n)=\sum\limits_{k=1}^{k<n}k\times\sum\limits_{\gcd(i,n)=k}^{i<n}1
$$

$$
preG(n)=\sum\limits_{k=1}^{k<n}k\times\sum\limits_{\gcd(i,\frac{n}{k})=1}^{i<\frac{n}{k}}1
$$

$$
preG(n)=\sum\limits_{k=1}^{k<n}k\times\varphi(\frac{n}{k})
$$

倒数第三个式子有$\gcd(i,n)=k$，显然有约束：$k|n$。

所以倒过来算：$\forall i$，$\varphi(i)$对 $preG(ik)$ 有贡献 $k\times\varphi(i)$。

枚举 $k$。因为 $ik\leq n$，所以时间复杂度为调和级数 $O(nlg_n)$。

别忘了前缀和！

### $code$

```cpp
#include<stdio.h>
#define N 1000001
inline void read(int&x)
{
	register char c=getchar();for(;c<'0'||'9'<c;c=getchar());
	for(x=0;'0'<=c&&c<='9';x=(x<<3)+(x<<1)+(c^48),c=getchar());
}
int n,primes[100000],m,phi[N];bool np[N];long long sum[N],g[N];
main()
{
	for(register int i=2;i<=N;++i)//欧拉筛求phi模板
	{
		if(!np[i])
		{
			primes[m++]=i;
			phi[i]=i-1;
		}
		for(register int j=0;j<m&&i*primes[j]<N;++j)
			if(i%primes[j])phi[i*primes[j]]=phi[i]*(primes[j]-1),np[i*primes[j]]=1;
			else{phi[i*primes[j]]=phi[i]*primes[j];np[i*primes[j]]=1;break;}
	}
	for(register int i=1;i<N;++i)for(register int k=1;k*i<N;++k)g[k*i]+=k*phi[i];//计算phi(i)对preG的贡献
	for(register int i=1;i<N;++i)g[i]+=g[i-1];//通过preG计算G
	for(;read(n),n;printf("%lld\n",g[n]));//
}
```



---

## 作者：云浅知处 (赞：1)

我们考虑递推地预处理答案。记 

$$
f(n)=\sum_{i=1}^n\sum_{j=i+1}^n\gcd(i,j)
$$

那么有

$$
f(n)-f(n-1)=\sum_{i=1}^{n-1}\gcd(i,n)
$$

记

$$
g(n)=\sum_{i=1}^{n}\gcd(i,n)
$$

枚举 $\gcd$

$$
\sum_{d|n}d\cdot\sum_{i=1}^n[\gcd(i,n)=d]
$$

注意到 $\gcd(i,n)=d\iff\gcd(i/d,n/d)=1,d|i,d|n$，因此上式即

$$
\sum_{d|n}d\cdot\sum_{d|i}[\gcd(i/d,n/d)=1]
$$

即

$$
\sum_{d|n}d\cdot\sum_{i=1}^{n/d}[\gcd(i,n/d)=1]
$$

注意到 $\sum\limits_{i=1}^{n/d}[\gcd(i,n/d)=1]=\varphi(n/d)$，因此上式化为

$$
\sum_{d|n}d\cdot\varphi(n/d)
$$

注意到这个东西就是 $\varphi * \text{Id}$，因此这也是一个积性函数，可以线性筛。

所以我们就做到了 $O(n)$ 的预处理。每次询问 $O(1)$ 输出即可。

时间复杂度为 $O(n+T)$。

不过 $n$ 只有 $2\times 10^6$，而且严格 $O(n)$ 的线性筛我写挂了没调出来，所以我并没有写严格 $O(n)$ 的线性筛（

```cpp
#include<cstdio>
#include<cmath>
#include<iostream>
#include<algorithm>

#define int long long
const int MN=2e6+6;

using namespace std;

int pri[MN],phi[MN],ans[MN],g[MN],f[MN],pi[MN];
bool vis[MN];

int ksm(int y,int z){
    int ans=1;
    for(int i=z;i;i>>=1,y=y*y)if(i&1)ans=ans*y;
    return ans;
}

int cnt=0;
void Pre(){
    vis[1]=1,phi[1]=1,g[1]=1;
    for(int i=2;i<MN;i++){
        if(!vis[i])pri[++cnt]=i,phi[i]=i-1,g[i]=2*i-1;
        for(int j=1;j<=cnt;j++){
            int id=i*pri[j];
            if(id>=MN)break;
            vis[id]=1;
            if(i%pri[j]==0){
                pi[id]=i;
                phi[id]=phi[i]*pri[j];
                int x=i,num=0;
                while(x%pri[j]==0)x/=pri[j],num++;
                g[id]=g[i]*pri[j]+ksm(pri[j],num)*(pri[j]-1)*g[x];
                break;
            }
            phi[id]=phi[i]*(pri[j]-1);
            g[id]=g[i]*g[pri[j]];
        }
    }
}

void init(){
    ans[1]=0;
    for(int i=2;i<MN;i++)ans[i]=ans[i-1]+g[i]-i;
}

signed main(void){

    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);

    Pre();
    init();

    int n;cin>>n;
    while(n!=0){
        cout<<ans[n]<<'\n';
        cin>>n;
    }

    return 0;
}
```

---

## 作者：HohleFeuerwerke (赞：1)

### 前言

[SP3871 GCDEX - GCD EXtreme](https://www.luogu.com.cn/problem/SP3871)。

双倍经验（完全一致）的题是主题库里面公约数的和。

~~吐槽一波你谷的 RMJ，隔壁 vjudge 都随手过了。~~

公式可能会炸，如果有需要请到 blog 里面来看。

---

### 正文

显然题解大多 $\Theta(n\log n)$ 或者 $\Theta(n)$ 预处理，每组询问可以 $\Theta(1)$。这样做的繁琐性就在于预处理出这个 $\sum_{d|n}d\times\phi(\frac{n}{d})$。

显然这个东西因为 $id$ 和 $\phi$ 都是积性函数，他也是积性函数，根据定义爆筛是 $\Theta(n\log n)$，线性筛是 $\Theta(n)$。

如果我不想预处理这个东西呢？

$$\sum_{i=1}^n\sum_{j=i+1}^n\gcd(i,j)$$

把表列出来：$(i,j)=\gcd(i,j)$。

| $1$ | $1$ | $1$ | $1$ | $1$ | $1$ |
| -----------: | -----------: | -----------: | -----------: | -----------: | -----------: |
| $1$ | $2$ |  |  |  |  |
| $1$ | $1$ | $3$ |   |  |  |
| $1$ | $2$ |  | $4$ | |  |
| $1$ | $1$ |  |  | $5$  |  |
| $1$ | $2$ |  |  |  | $6$ |

显然你会发现我们要求的和都在这张表的斜下方。

于是容斥一下：

$$ys=\frac{\sum_{i=1}^n\sum_{j=1}^n\gcd(i,j)-\sum_{i=1}^n\gcd(i,i)}{2}$$

然后分开来做。

$$\sum_{i=1}^n\sum_{j=1}^n\gcd(i,j)$$

这个东西我们再熟悉不过了。两条路子：欧拉反演和莫比乌斯反演。

欧拉反演本质是什么呢：$\sum_{d|n}\phi(d)=n$。

这个式子怎么运用呢？把 $\gcd(i,j)$ 换成 $n$ 即可。

$$\begin{aligned}\sum_{i=1}^n\sum_{j=1}^n\gcd(i,j)&=\sum_{i=1}^n\sum_{j=1}^n\sum_{d|\gcd(i,j)}\phi(d)\\&=\sum_{i=1}^n\sum_{j=1}^n\sum_{d|i,d|j}\phi(d)\\&=\sum_{d=1}^n\phi(d)\sum_{i=1}^n\sum_{j=1}^n[d|i,d|j]\\&=\sum_{d=1}^n\phi(d)\lfloor\frac{n}{d}\rfloor^2\end{aligned}$$

然后分块，就单组询问 $\sqrt n$ 了。

莫比乌斯反演本质是什么呢：$\sum_{d|n}\mu(d)=[n=1]$。

所以你需要构造出一个式子 $=1$。那么很明显，枚举一下 $\gcd$ 就行了。

$$\begin{aligned}\sum_{i=1}^n\sum_{j=1}^n\gcd(i,j)&=\sum_{d=1}^nd\sum_{i=1}^n\sum_{j=1}^n[\gcd(i,j)=d]\\&=\sum_{d=1}^nd\sum_{i=1}^\frac{n}{d}\sum_{j=1}^\frac{n}{d}[\gcd(i,j)=1]\\&=\sum_{d=1}^nd\sum_{i=1}^\frac{n}{d}\sum_{j=1}^{\frac{n}{d}}\sum_{t|i,t|j}\mu(t)\\&=\sum_{d=1}^nd\sum_{t=1}^{\frac{n}{d}}\mu(t)\lfloor\frac{n}{dt}\rfloor^2\\&=\sum_{T=1}^n\lfloor\frac{n}{T}\rfloor^2\sum_{d|T}d\mu(\frac{n}{d})\\&=\sum_{T=1}^n\lfloor\frac{n}{T}\rfloor^2\phi(T)\end{aligned}$$

然后分块。

好的我们得到这个了，另一个呢？

$$\sum_{i=1}^n\gcd(i,i)=\sum_{i=1}^ni=\frac{n(n+1)}{2}$$

然后把这俩合并一下就行了。

总复杂度 $\Theta(n+T\sqrt n)$。能过。

```cpp
#include<bits/stdc++.h>
#define HohleFeuerwerke using namespace std
#pragma GCC optimize(3,"Ofast","-funroll-loops","-fdelete-null-pointer-checks")
#pragma GCC target("ssse3","sse3","sse2","sse","avx2","avx")
#define int long long
HohleFeuerwerke;
inline int read(){
	int s=0,f=1;char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
	for(;isdigit(c);c=getchar()) s=s*10+c-'0';
	return s*f;
}
inline void write(int x){
	if(x<0) putchar('-'),x=-x;
	if(x>=10) write(x/10);
	putchar('0'+x%10);
}
const int MAXN=2e6+5;
int n;
int phi[MAXN],pri[MAXN],tot;
int Sphi[MAXN];
bool ispri[MAXN];
void init(){
    ispri[1]=phi[1]=true;
    for(int i=2;i<=MAXN-5;i++){
        if(!ispri[i]) pri[++tot]=i,phi[i]=i-1;
        for(int j=1;j<=tot&&i*pri[j]<=MAXN-5;j++){
            ispri[i*pri[j]]=true;
            if(i%pri[j]) phi[i*pri[j]]=phi[i]*phi[pri[j]];
            else{phi[i*pri[j]]=phi[i]*pri[j];break;}
        }
    }
    for(int i=1;i<=MAXN-5;i++) Sphi[i]=Sphi[i-1]+phi[i];
}
signed main()
{
	init();
	int n=read();
	while(n){
		int ans=0;
		for(int l=1,r;l<=n;l=r+1){
			r=n/(n/l);
			ans+=(Sphi[r]-Sphi[l-1])*(n/l)*(n/l);
		}
		ans-=n*(n+1)/2;
		write(ans/2);putchar('\n');
		n=read();
	} 
}
```





---

## 作者：wurzang (赞：0)

水一水社区分


题意转化之后就变成求 $\sum_{i=1}^n\sum_{j=1}^n \gcd(i,j)$

$$
\sum_{i=1}^n\sum_{j=1}^n \gcd(i,j) 

$$
$$
\sum_{i=1}^n \sum_{j=1}^n \sum_{d|\gcd(i,j)} \varphi(d) 
$$

$$
\sum_{d=1}^n \varphi(d) \sum_{i=1}^n \sum_{j=1}^n [d|\gcd(i,j)] 
$$
$$
\sum_{d=1}^n \varphi(d) (\left\lfloor\frac{n}{d}\right\rfloor)^2
$$


然后就可以 $\mathcal{O}(n+T \sqrt{n})$ 做了。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long sum[1145140];
int euler[1145140],vis[1145140],prime[1145140],cnt;
void init(int n){
	euler[1]=1;
	for(int i=2;i<=n;++i){
		if(!vis[i]) prime[++cnt]=i,euler[i]=i-1;
		for(int j=1;j<=cnt;++j){
			if(1ll*i*prime[j]>n) break;
			vis[i*prime[j]]=1;
			if(i%prime[j]) euler[i*prime[j]]=(prime[j]-1)*euler[i];
			else{
				euler[i*prime[j]]=prime[j]*euler[i];
				break;
			}
		}
	}
	for(int i=1;i<=n;++i)
		sum[i]=sum[i-1]+euler[i];
}
int main(){
	init(1000000);
	long long n,m,ans=0;
	while(cin>>n){
		if(n==0) break;
		ans=0;		
		for(int d=1,r;d<=n;d=r+1){
			r=n/(n/d);
			ans+=1ll*(sum[r]-sum[d-1])*(n/d)*(n/d);
		}
		//cout<<ans<<endl;
		ans=(ans-1ll*n*(n+1)/2)/2;
		cout<<ans<<endl;
	}
	return 0;
}
```


---

