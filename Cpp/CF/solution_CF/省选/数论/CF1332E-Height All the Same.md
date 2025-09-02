# Height All the Same

## 题目描述

最近，Alice 迷上了一款名为 Sirtet 的游戏。

在 Sirtet 中，玩家会得到一个 $n \times m$ 的网格。初始时，格 $(i, j)$ 上码放有 $a_{i, j}$ 个方块。若两个格子有一条公共边，我们称这两个格子时相邻的。玩家可以进行以下两种操作：

- 在两个相邻的格子上各码上一个方块。
- 在一个格子上码上两个方块。

上述中所提到的所有方块都具有相同的高度。

以下是该游戏的一个图例说明。图中右侧的状态是由图中左侧的状态经过一次上述操作得到，灰色的方块表示操作中新加入的方块。

![题目中的图](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1332E/b28d1e8feb96f79180d1281fb0ba495f60c5b884.png)

玩家的目标是通过这些操作，使得所有的格子拥有同样的高度（也就是说，每个格子上堆放的方块数相同）。

然而，Alice 发现存在有某些初始局面，使得无论她采用什么策略，都无法达到目标。因此，她希望知道有多少初始局面，满足，

- 对于所有的 $1 \le i \le n$，$1 \le j \le m$，$L \le a_{i, j} \le R$。
- 玩家可以通过执行这些操作，达到目标。

请帮助 Alice 解决这个问题。注意答案可能很大，请输出所求答案对 $998, 244, 353$ 取模的值。

## 说明/提示

在第一个样例中，唯一一种符合要求的初始局面是 $a_{1, 1} = a_{2, 1} = a_{1, 2} = a_{2, 2} = 1$。因此答案为 $1$。

在第二个样例中，符合要求的初始局面有 $a_{1, 1} = a_{1, 2} = 1$ 和 $a_{1, 1} = a_{1, 2} = 2$。因此答案为 $2$。

## 样例 #1

### 输入

```
2 2 1 1```

### 输出

```
1```

## 样例 #2

### 输入

```
1 2 1 2```

### 输出

```
2```

# 题解

## 作者：syksykCCC (赞：29)

感谢 @[DepletedPrism](https://www.luogu.com.cn/user/109751)，修了一个锅。

感谢 @[F_Mu](https://www.luogu.com.cn/user/147428)，又修了一个锅。

~~为啥我这么多锅啊~~，要不点个赞再走吧 /qq

-----

首先，可以观察到结果和实际的高度无关，之和高度的奇偶性有关。

这个很好理解，因为我们可以用操作 2 使得在同奇偶性的数域内变化。

现在只考虑操作 1。

我们用 $E$ 表示 $[L,R]$ 中的偶数个数，$O$ 表示 $[L,R]$ 中的奇数个数。

接下来要分两种情况。

如果 $n \cdot m$ 是奇数的话，可以证明，任何一种方式都是合法的。

为什么？因为这以为着图中要么有偶数个 $a \in \text{Even}$，要么有偶数个 $a \in \text{Odd}$，无论是哪种，我们都可以用操作 1 使得这部分变成与它相反的奇偶性，那么奇偶性都相等，答案也就相等了。

所以这时有答案为：

$$ \prod_{i = 1}^{n} \prod_{j = 1}^{m}(R-L+1) = (R-L+1)^{nm}$$

否则就是 $n \cdot m$ 是偶数。

设最终是 $h$ 层，那么最终 $\sum_{i=1}^{n}\sum_{j=1}^{m} a_{i, j} = nmh$，显然是个偶数。这时我们把过程倒过来想，无论怎么操作，$\sum_{i=1}^{n}\sum_{j=1}^{m} a_{i, j}$ 始终是偶数，所以我们只要保持局面的和是偶数，就一定有解。

可能你又想问为什么这个是充要条件，因为和是偶数，说明一定有偶数个 $a \in \text{Odd}$，所以类比上面就可知了。

但是这个怎么求呢？

显然，我们只要保持局面上 $a \in \text{Odd}$ 的个数为偶数就行了。不妨设有 $2i$ 个位置是奇数，$[L,R]$ 中有 $O$ 个奇数，$E$ 个偶数。

答案为：

$$ \sum_{i = 0}^{\frac{nm}{2}}\left(\begin{matrix} nm \\ 2i \end{matrix} \right )O^{2i} E^{nm - 2i} $$

可是这个式子怎么求呢？

这让我们想到二项式定理。

二项式定理的表述为：

$$ (x+y)^{z} = \sum_{i=0}^{z}\left(\begin{matrix} z \\i \end{matrix}\right)x^i y^{z-i} $$

是不是比较相似呢？

$$ (O + E)^{nm} = \sum_{i = 0}^{nm} \left(\begin{matrix} nm \\ i \end{matrix} \right) O^i E^{nm - i}$$

然后偶数项和奇数项分别拉出来。

$$(O+E)^{nm} = \sum_{i = 0}^{\frac{nm}{2}} \left(\begin{matrix} nm \\ 2i \end{matrix} \right ) O^{2i} E^{nm - 2i}  + \sum_{i = 1}^{\frac{nm}{2}} \left(\begin{matrix} nm \\ 2i-1 \end{matrix} \right ) O^{2i-1} E^{nm - (2i-1)}$$

发现左半边就是我们想要的东西。

怎么消掉右半边？发现：

$$ (O-E)^{nm} = \sum_{i = 0}^{\frac{nm}{2}} \left(\begin{matrix} nm \\ 2i \end{matrix} \right ) O^{2i} E^{nm - 2i}  - \sum_{i = 1}^{\frac{nm}{2}} \left(\begin{matrix} nm \\ 2i-1 \end{matrix} \right ) O^{2i-1} E^{nm - (2i-1)} $$

两式相加，得到：

$$ (O + E)^{nm} + (O - E)^{nm} = 2 \sum_{i = 0}^{\frac{nm}{2}} \left(\begin{matrix} nm \\ 2i \end{matrix} \right ) O^{2i} E^{nm - 2i}$$

所以，答案就是：

$$ \frac{(O + E)^{nm} + (O - E)^{nm}}{2} $$

使用快速幂可以做到 $\mathcal O(\log (nm))$，值得注意的是使用欧拉定理应当特判底数等于 $0$ 的情况，否则会被极端数据卡掉，例如：

```plain
998244352 2 1 998244353
```

答案是 $499122177$。

具体细节看代码吧。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL MOD = 998244353; 
LL qpow(LL a, LL p)
{
	if(a == 0) return 0;
	LL res = 1;
	while(p)
	{
		if(p & 1) res = res * a % MOD;
		a = a * a % MOD;
		p >>= 1;
	}
	return res;
}
int main()
{
	LL n, m, l, r;
	cin >> n >> m >> l >> r; 
	if(n * m & 1) cout << qpow((r - l + 1) % MOD, n * m % (MOD - 1)) << endl;
	else
	{
		LL E = (r >> 1) - (l - 1 >> 1);
		LL O = r - l + 1 - E;
		cout << ((qpow((O + E) % MOD, n * m % (MOD - 1)) + qpow((O - E + MOD) % MOD, n * m % (MOD - 1))) * 499122177 % MOD) << endl; // 499122177 是 mod 998244353 意义下 2 的逆元
	}
	return 0;
}
```

---

## 作者：George1123 (赞：7)

# 题解-Height All the Same

## [博客中阅读](https://www.cnblogs.com/Wendigo/p/12611937.html#E)

> [Height All the Same](https://codeforces.com/contest/1332/problem/E)

> 给定 $n,m,L,R$，求大小为 $n\times m$ 的矩阵 $a_{i,j}$ 中满足 $L\le a_{i,j}\le R$ 并且可以通过相邻元素一起 $+1$、元素 $+2$ 两种操作使整个矩阵相等的数量 $\bmod 998244353$。

> 数据范围：$1\le n,m,L,R\le 10^9$，$L\le R$。

很明显 $L$ 和 $R$ 的绝对大小不重要，所以设 $H=R-L+1$。

如果没有后一个限制，答案应该是 $H^{nm}$。

手玩几下会发现，只要奇偶性满足要求，该矩阵就满足要求（每一次操作不改变矩阵和奇偶性，可以把每个元素加得无限大），所以：

1. 如果 $nm\in\mathbb{odd}$：答案就为 $H^{nm}$。
2. 如果 $nm\in\mathbb{even}$：答案就为 $\lceil\frac{H^{nm}}{2}\rceil$。

**易错点：**

1. 要 $\bmod 998244353$，除法用逆元，幂 $\bmod 998244352$（欧拉定理）。
2. 快速幂的时候，因为可能 $H\bmod 998244353=0$，如果 $nm\bmod 998244352=0$，普通人写的快速幂很容易得到 $1$，其实应该得到 $0$（因此我 $FST$ 了）。

**代码：**

```cpp
//Data
const int Mo=998244353;
int n,m,a,b,h;
lng sz;
il int Pow(re int a,re int x){
	if(a==0) return 0;
	re int res=1;
	for(;x;a=1ll*a*a%Mo,x>>=1)if(x&1)res=1ll*res*a%Mo;
	return res;
}

//Main
int main(){
	scanf("%d%d%d%d",&n,&m,&a,&b);
	h=b-a+1,sz=1ll*n*m;
	if(sz&1) printf("%lld\n",1ll*Pow(h,sz%(Mo-1)));
	else if(h&1) printf("%lld\n",1ll*(Pow(h%Mo,sz%(Mo-1))+1+Mo)%Mo*Pow(2,Mo-2)%Mo);
	else printf("%lld\n",1ll*Pow(h%Mo,sz%(Mo-1))*Pow(2,Mo-2)%Mo);
	return 0;
}
```

---

**祝大家学习愉快！**

---

## 作者：gyh20 (赞：5)

要做这道题，我们需要先证明一些结论。

$1.$每个位置的积木个数仅和奇偶性有关。

证明：如果一个位置比其他位置高的是一个偶数，那么可以一直加 $2$。

$2.$可以同时将任意两个位置的积木同时 $+1$。

证明：可以找到两点之间的一条路径，然后将相邻的两个点增加一个积木（除了起点和终点被算了一遍，其他点都算了两遍，根据结论 $1.$ ，这就相当于没有变化）

所以说，我们只要满足初始状态奇偶性等于结束状态奇偶性相同即可。

当 $n\times m$ 为奇数时，结束状态奇偶都可以，所以怎么摆都可以。

否则，结束状态一定是偶数，其实就是求用 $s$ 个奇数和 $t$ 个偶数组成偶数的方案（其中 $s$ 为可用奇数个数，$t$ 为可用偶数个数）。

听说有 oeis 方法？但我没想到。

令 $f_i$ 为用 $i$ 个数和为奇数方案数， $g_i$ 为用 $i$ 个数和为偶数的方案数，则可以得到下列递推式：

$f_i=f_{i-1}\times t+g_{i-1}\times s$

$g_i=g_{i-1}\times t+f_{i-1}\times s$

可以发现：这是一个线性递推式，加速递推式最常用的是：矩阵乘法。

构造矩阵 $h_i=\begin{bmatrix}
f_i&g_i\\
\end{bmatrix}$

转移矩阵为 $a=$
$\begin{bmatrix}
t&s\\
s&t
\end{bmatrix}$

矩阵乘法求解即可。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
long long n,m,mod,a[5][5],f[5],b[5][5],g[5],cs,aa[5][5];
inline void mul() {
	memset(g,0,sizeof(g));
	for(register int i=1; i<=n; ++i) {
		for(register int j=1; j<=n; ++j) {
			g[i]+=(f[j]*a[j][i])%mod;
			g[i]%=mod;
		}
	}
	memcpy(f,g,sizeof(g));
}
inline void mulself() {
	memset(b,0,sizeof(b));
	for(register int i=1; i<=n; ++i) {
		for(register int j=1; j<=n; ++j) {
			for(register int k=1; k<=n; ++k){
				b[i][j]+=a[i][k]*a[k][j]%mod;
				b[i][j]%=mod;
			}
		}
	}
	memcpy(a,b,sizeof(b));
}
int k,l,r;
#define re register
const int Mxdt=100000;
inline char gc() {
	static char buf[Mxdt],*p1=buf,*p2=buf;
	return p1==p2&&(p2=(p1=buf)+fread(buf,1,Mxdt,stdin),p1==p2)?EOF:*p1++;
}
#define gc getchar
inline int read() {
	int res=0,bj=0;
	char ch=gc();
	while(ch<'0')bj|=(ch=='-'),ch=gc();
	while(ch>='0')res=(res<<3)+(res<<1)+(ch^48),ch=gc();
	return bj?-res:res;
}
inline int ksm(re int x,re int y){
	re int ans=1;
	while(y){
		if(y&1)ans=ans*x%mod;
		x=x*x%mod;
		y>>=1;
	}
	return ans;
}
int s,t;
signed main() {mod=998244353;
	n=read();m=read();l=read();r=read();re int kk=n*m;
	k=m*n;s=(r-l+1)/2;
	if((r&1)&&(l&1))++s;t=r-l+1-s;
	n=2;f[1]=1,f[2]=0;
	a[2][1]=s,a[2][2]=t;
	a[1][1]=t,a[1][2]=s;
	
if(kk%2==0){
	while(k) {

		if(k&1)mul();
		mulself();	
		k>>=1;
	}
	long long ans=f[1];
	printf("%lld",ans);}
	else{printf("%lld",ksm(r-l+1,kk));
	}
}
```
[广告](https://www.luogu.com.cn/blog/gyh20/post-di-cfat-ti-xie-ji-lie)


---

## 作者：wsyhb (赞：4)

## 题意简述

给定 $n,m,L,R$，求有多少种 $n \times m$ 大小的矩阵 $a$ 满足下列条件：

- $L \le a_{i,j} \le R \;(1 \le i \le n,1 \le j \le m)$
- 可执行若干次下列操作，使得 $a$ 中所有数相等。
	- 操作 1：任选一个数 $+2$。
	- 操作 2：任选两个**相邻**的数同时 $+1$。
   
答案对 $998244353$ 取模。

**数据范围**：$1 \le n,m,L,R \le 10^9$，$L \le R$。

## 题解

操作 1 其实就是把 $a$ 中所有数相等的限制，变成了 **$a$ 中所有数在 $\bmod \; 2$ 意义下相等**。因此只需考虑操作 2。

一个显然的结论是，通过操作 2，我们可以限制 $n \times m-1$ 个数在 $\bmod \; 2$ 意义下的取值。（一种可行的调整方法：从左到右、从上到下调整。对于 $1 \le i <n$，$1 \le j \le m$ 的 $a_{i,j}$，可以通过使 $a_{i,j}$ 和 $a_{i+1,j}$ 同时加一来调整；对于 $i=n$，$1 \le j < m$ 的 $a_{i,j}$，可以通过使 $a_{i,j}$ 和 $a_{i,j+1}$ 同时加一来调整）

另一个显然的结论是，在操作 2 执行前后，所有数之和在 $\bmod \; 2$ 意义下不变。

于是，若 $n \times m$ 为奇数，所有初始状态均可行——因为我们可以使 $n \times m-1$ 个数的奇偶性，和数的总和的奇偶性相同，那么剩余的一个数奇偶性也相同。此时答案为 $(R-L+1)^{nm}$。

------------

否则，若 $n \times m$ 为偶数，则初始时数的总和必须为偶数——必要性：因为要使 $n \times m$ 个数奇偶性相同；充分性：同 $n \times m$ 为奇数时的理由。

对于 $n \times m$ 为偶数的情况，答案即为下列式子：

$$\sum_{0 \le i \le nm,2 \mid i}\binom{nm}{i}x^iy^{nm-i}$$

其中 $x$ 为 $[L,R]$ 中奇数的个数，$y$ 为 $[L,R]$ 中偶数的个数。即 $nm$ 个数中选 $i$ 个奇数（$i$ 为偶数），$nm-i$ 个偶数。

这式子显然与**二项式定理**有关。

而什么东西可以把奇数项和偶数项分离开呢？容易想到 $-1$ 的幂。

于是考虑如下式子：

$$
\begin{aligned}
(x+y)^{nm}&=\sum_{i=0}^{nm}\binom{nm}{i}x^iy^{nm-i}\\
(-x+y)^{nm}&=\sum_{i=0}^{nm}\binom{nm}{i}(-1)^ix^iy^{nm-i}
\end{aligned}
$$

发现原问题答案即为 $\dfrac{(x+y)^{nm}+(-x+y)^{nm}}{2}$。

使用**快速幂**，时间复杂度为 $O(\log{nm})$。

可以使用欧拉定理，即把指数 $nm$ 对 $\varphi(\mathit{mod})=\mathit{mod}-1=998244352$ 取模，但请注意此题 $0^0=0$ 的处理。

## 代码

``` cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=998244353;
const int phi=998244352;
inline int qpow(int a,int n)
{
	int res=1;
	while(n)
	{
		if(n&1)
			res=1ll*res*a%mod;
		a=1ll*a*a%mod;
		n>>=1;
	}
	return res;
}
int main()
{
	int n,m,L,R;
	scanf("%d%d%d%d",&n,&m,&L,&R);
	int ans,expo=1ll*n*m%phi+phi; // expo 加上了 phi
	if(n&m&1)
		ans=qpow(R-L+1,expo);
	else
	{
		int l=L+(L&1),r=R-(R&1),x=l<=r?(r-l+2)>>1:0,y=(R-L+1)-x;
		ans=qpow(x+y,expo)+qpow(x-y+mod,expo);
		ans-=ans>=mod?mod:0;
		if(ans&1)
			ans+=mod;
		ans>>=1;
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：CrTsIr400 (赞：3)

## CF1332E [Height All the Same](https://www.luogu.com.cn/problem/CF1332E)

题意：给定 $n,m,L,R$，求大小为 $n\times m$ 的矩阵 $a_{i,j}$ 中满足 $L\le a_{i,j}\le R$ 并且可以通过相邻元素一起 $+1$、元素 $+2$ 两种操作使整个矩阵相等的数量，取模 $998244353$ 后输出。

---

设 $H=R-L+1$。很明显和**绝对高度没有关系**，因为最终要达成的目标是削平的。

若是没有条件约束，答案应该为 $H^{nm}$。

---

结论 1：加偶数相当于没加。

显然，可以通过给矩阵内其他元素，通过单位置加 $2$ 的这个操作，来弥补这个问题。

结论 2：可以任意加矩阵中两个元素。

显然，可以通过给矩阵中这两个元素的一条路径，每次做相邻 $+1$ 的操作，来弥补缺陷。

结论 3：变成了结论题，一个矩阵可行不可行，只看其每个位置高度的奇偶性。

结论 4：根据 结论 2 和 结论 3 ，一个矩阵可行不可行，只用看它**高度为奇数的必须有偶数个**即可。

---

若 $nm$ 为奇数，那么所有矩阵都可以（因为要么有偶数个偶数，奇数个奇数高度，要么有奇数个偶数高度，偶数个奇数高度，两种情况可以通过 1 操作 转换）。

---

若 $nm$ 为偶数，那么只有约莫一半的矩阵可以（因为有奇数个偶数高度，奇数个奇数高度的情况不能转化）。

具体而言，设 $O$ 为 $H$ 值域内奇数个数，$E$ 为偶数个数，那么 $nm$ 为偶数的合法情况为：

$$\Large{B=\sum_{i=0}^{\frac{nm}{2}} \binom{nm}{2i} O^{2i}E^{nm-2i}}$$

怎么算 $B$ 值呢？直接不好算，考虑计算这两个式子：

$\Large{A=(O+E)^{nm}=\sum_{i=0}^{nm}\binom{nm}{i}O^iE^{nm-i}=\sum_{i=0}^{\frac{nm}{2}} \binom{nm}{2i} O^{2i}E^{nm-2i}+\sum_{i=0}^{\frac{nm}{2}}\binom{nm}{2i+1}O^{2i+1}E^{nm-2i-1}=B+C}$

考虑把 $B$ 值分离出来。这个时候考虑使用一些数学思维。

**分离奇数、偶数项之和**通常使用**改变符号**的方法。这道题也是一样。

于是设 $\Large{D=(O-E)^{nm}=\sum_{i=0}^{nm}\binom{nm}{i}O^iE^{nm-i}(-1)^{nm-i}=\sum_{i=0}^{\frac{nm}{2}} \binom{nm}{2i} O^{2i}E^{nm-2i}-\sum_{i=0}^{\frac{nm}{2}}\binom{nm}{2i+1}O^{2i+1}E^{nm-2i-1}=B-C}$

整理一下，$A+D=2B$，所以答案就是 $\dfrac{A+D}{2}$。

这个答案很容易算，用快速幂即可，此处不做赘述。注意 $0^0=0$。

---

## 作者：ZHR100102 (赞：1)

小清新二项式定理题。

话说这玩意真的有紫吗，不管是推式子部分还是观察部分都比较显然吧，感觉可以蓝。

# 转化

首先看到每次进行 $1,2$ 的增加，不难联想到奇数和偶数的性质。我们以 $2$ 为粒度变化，操作 $1$ 就相当于给网格中相邻两个格子的奇偶性发生改变，而操作 $2$ 是在所有的格子奇偶性相同的时候把网格图的所有数字变得相等的。**所以本题中只有操作 $1$ 的改变相邻两个格子的奇偶性的操作是有用的，并且我们可以由此转化为网格上的 $0,1$ 问题（按照奇偶性）。**

# 观察

那么操作 $1$ 有啥性质呢？不难发现，假设相邻的两个有一个 $0$ 和一个 $1$，那么我们执行操作，就相当于把这个 $1$ 进行了一次上下左右的移动，$0$ 也是同理的。而如果操作的两个数奇偶性相同，那么执行操作后奇偶性还是相同，就相当于没有用。

也就是说，我们要消除 $1$，让它全变 $0$；或者要消除 $0$，让它全变 $1$。

消除该如何做呢？显然是将两个本来不挨在一起的两个 $0$ 或 $1$ 通过操作 $1$ 挨在一起，然后再对这个两个数执行一次操作 $1$，就能起到消除这两个 $0$ 或 $1$ 的效果。**因为是两两相消的，所以要消除的数字必须出现偶数次。**

但到底要消除 $0$ 还是消除 $1$ 呢？这个我们就要分讨了。

# 当 $n\times m$ 为奇数时

显然填什么数都合法，因为奇数要拆分成奇数和偶数，而 $0$ 和 $1$ 的个数在 $n\times m$ 为奇数的情况下不可能同奇偶性，必然存在 $0$ 或 $1$ 满足个数为偶数的要求，所以所有状态都合法，答案为 $(r-l+1)^{n\times m}$。

# 当 $n\times m$ 为偶数时

这时候就不是填啥都合法了，因为 $0,1$ 的个数同奇偶性，所以 $0,1$ 的个数都必须是偶数才能两两消除完。

假设 $[l,r]$ 中的奇数个数为 $odd$，偶数个数为 $even$。

那么这时候的答案是 $\sum_{i \bmod 2 =0} C_{n\times m}^{i}\times odd^i \times even^{n\times m -i}$。暴力计算显然会超时。

观察到式子只对偶数项求和，并且还有组合数，很容易想到用二项式来加速计算。所以我们考虑对所有项求和，然后把奇数项乘一个 $-1$，最后将结果再加上所有项的和，就是偶数项的两倍了。因为奇数项全部被抵消了。

这个结果式子就是 $\cfrac{\sum_{i=0}^{n\times m} C_{n\times m}^{i}\times odd^i \times even^{n\times m -i}\times (-1)^i+\sum_{i=0}^{n\times m} C_{n\times m}^{i}\times odd^i \times even^{n\times m -i}}{2}$。

那么我们现在就可以用二项式定理来化简了，最后的结果是：

$$\cfrac{\sum_{i=0}^{n\times m} C_{n\times m}^{i}\times (-odd)^i \times even^{n\times m -i}\times+\sum_{i=0}^{n\times m} C_{n\times m}^{i}\times odd^i \times even^{n\times m -i}}{2}=\cfrac{(-odd+even)^{n\times m}+(odd+even)^{n\times m}}{2}$$

快速幂计算即可，时间复杂度 $O(\log n\times m)$。

# 代码

```cpp
#include <bits/stdc++.h>
#define fi first
#define se second
#define eb(x) emplace_back(x)
#define pb(x) push_back(x)
#define lc(x) (tr[x].ls)
#define rc(x) (tr[x].rs)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ldb;
using pi=pair<int,int>;
const ll mod=998244353;
ll n,m,l,r;
ll qpow(ll a,ll b)
{
    ll res=1;
    while(b)
    {
        if(b&1)res=(res*a)%mod;
        b>>=1;
        a=(a*a)%mod;
    }
    return res;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>m>>l>>r;
    ll odd=(r+1)/2-(l-1+1)/2,even=r/2-(l-1)/2;
    if((1ll*n*m)&1)cout<<qpow(r-l+1,1ll*n*m);
    else cout<<(qpow(even-odd,1ll*n*m)+qpow(even+odd,1ll*n*m))%mod*qpow(2,mod-2)%mod;
    return 0;
}
```

---

## 作者：Michael_114 (赞：1)

想到方法来交了，~~结果洛谷 RMJ 爆了，交不成喽。~~

这道题容易发现，使用若干次加二操作，可以将一个奇/偶数变成一个比他大的任意一个奇/偶数。因此，只要能够使所有格子中的数字奇偶性相同，就可以达成最终的目的。因此对于本体，可以考虑从奇偶性入手。

接下来开始考虑操作 $1$ 的作用。每使用一次操作 $1$ 会使两个相邻的数奇偶性发生改变。若原来有 $a$ 个奇数，则操作后可能会出现 $a-2$ 个奇数、$a$ 个奇数、$a+2$ 个奇数共三种情况；而无论是哪种情况，$a$ 的奇偶性都是不变的。偶数也是如此。

由于最后需要将所有数全部变为奇数或偶数，则最后要将奇数或偶数中某一个的个数变成 $0$。不妨假设原来奇数、偶数的个数分别为 $a,b$。由于 $0$ 是偶数，因此 $a$ 和 $b$ 中至少有一个为偶，否则就不可能满足题意。

那么是不是只需要 $a$ 或 $b$ 中至少一个为偶，就可以满足题意呢？

事实上，对于任意两个奇数（或偶数），只需要选择一条由若干组相邻格子组成的“路径”，将所有路径上的每组格子分别进行一次操作 $1$，就可以将这两个数全部变成偶数（奇数），并且不对其他任何一个数字的奇偶性产生影响。

因此，只需要 $a,b$ 中有任意一者为偶数（不妨设 $a$ 为偶数），则只需要将所有的奇数两两配对，并通过上述方式将其全部变为偶数即可。综上所述，符合题意的初始情况等价于存在偶数个格子是奇数或偶数个格子是偶数。

那么如何统计可行的方案数呢？

首先，若 $n \times m$ 为奇数，则显然 $a,b$ 一奇一偶，满足条件。由于需要每个格子有 $R-L+1$ 种选择，故答案为 $(R-L+1)^{n\times m}$。

接下来考虑 $n \times m$ 为偶数的情况。由于 $a+b = n\times m$，因此需要满足 $a$ 与 $b$ 分别为偶数。从所有格子中选出 $a$（$a$ 为偶数）个并指定这些位置为奇数，剩余为偶数。假设 $[L,R]$ 中的奇数有 $k$ 个，偶数有 $l$ 个，则最终的答案为 $\sum_{2|a} C_{n \times m}^{a} \times k^a \times l^b$（其中 $b = n \times m-a$）。

接着，考虑如何求解这个公式。由二项式定理，$(k+l)^{n \times m} = \sum_{a=0}^{n \times m} C_{n \times m}^{a} \times k^a \times l^b$。可以发现，需要求的是这里面次数为偶数的部分，因此只需要消去其中次数为奇数的部分即可。同理，由二项式定理，$(k-l)^{n \times m} = \sum_{a=0}^{n \times m} C_{n \times m}^{a} \times k^a \times l^b$，需要的同样是其次数为偶数的部分。而这两个式子的奇数次幂抵消，偶数次幂相同。因此只需要将两者相加并除以二，即 $\frac{(k+l)^{n \times m} + (k-l)^{n \times m}}{2}$，就是最终的结果。参考代码如下：
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const int maxp = 998244353;
typedef long long ll;
ll fp(ll a,ll b){
	ll res = 1;
	while(b){
		if(b&1){
			res = res*a%maxp;
		}
		a = a*a%maxp,b>>=1;
	}
	return res;
}
int main() {
    ll n,m,l,r;
    cin>>n>>m>>l>>r;
    if((n&1)&&(m&1)){
		cout<<fp(r-l+1,n*m);
	}else{
		ll a = r/2-(l-1)/2;
		ll b = r-l+1-a;
		cout<<(fp((a+b)%maxp,n*m)+fp((a-b+maxp)%maxp,n*m))*499122177%maxp;
	}
    return 0;
}
```

---

## 作者：Wind_love (赞：1)

## 题解：CF1332E Height All the Same
### 前置知识
二项式定理，快速幂。  
### 题意
在一个 $n \times m$ 的矩阵中，有相邻两个格上的数组加一和一个格子上的数字加二这两种操作。问能不能把矩阵填平。
### 做法
首先，因为加二的操作，所以跟绝对高度没什么关系。

我们可以发现，若有奇数或偶数的数量为偶数，则可以将他们两两配对，则当奇数或偶数的个数有一个是偶数时，就一定能满足要求，于是有了如下做法：

我们将这 $n \times m$ 个数中，奇数的个数为 $x$，偶数的个数为 $y$。

若 $n \times m$ 为奇数，则所有情况都可以满足要求，显然方案数为 $(r-l+1)^{n m}$。

若 $n \times m$ 为偶数，则需要满足 $x$，$y$ 均为偶数，可知能满足条件的情况共有 $\sum_{i = 0}^{\frac{nm}{2}}\binom{nm}{2i}x^{2i}y^{nm-2i}$ 种，通过二项式定理转化为 $\frac{(x+y)^{nm}+(x-y)^{nm}}{2}$，然后使用快速幂计算。  
因为要取余，所以记得用一下逆元。
### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int p=998244353;
long long qpow(long long a,long long b){
	long long ans=1;
	while(b!=0){
		if(b&1)ans=ans*a%p;
		a=a*a%p;
		b>>=1;
	}
	return ans;
}
signed main(){
	int n,m,l,r;
	cin>>n>>m>>l>>r;
	int t=r-l+1;
	if(n*m%2==1){
		cout<<qpow(t,n*m);
	}
	else{
		int a=t/2;
		int b=t-a;
		cout<<((qpow(a+b,m*n)+qpow(a-b+p,m*n)%p)*(qpow(2,p-2)))%p;                                    ;
	}
	return 0;
}
```
### 结尾
希望大家遇题多思考，可以用到转化的数学思想，更多的做题练习。

---

## 作者：analysis (赞：1)

## CF1332E 题解

这种题一开始没思路，可以从找性质开始。

感觉操作很奇怪，从这开始思考性质：

- 结果只与奇偶性有关，当所有位置的奇偶性相同时，可以完成题目要求（事实上很多操作仅加 $1$、$2$ 的都与奇偶有关）。

考虑操作二，给一个位置加 $2$，显然不改变奇偶性。

操作一，两个相邻的位置加一，翻转奇偶性。

我们可以利用操作一，把奇偶性相同的值“移动”到相邻位置统一改变奇偶性。

综上，进一步讨论：

- $nm$ 为奇数

显然 奇数 = 偶数 + 奇数，所以图中一定有偶数个奇数或偶数，这些可以利用操作一转换。

即：当 $nm$ 为奇数，玩家一定可以通过执行这些操作，达到目标。

- $nm$ 位偶数

图中只有为偶数个奇数和偶数个偶数时成立，即局面有：

$$
\sum_{i \bmod 2 = 0}^{nm}\begin{pmatrix}nm\\i\end{pmatrix}J^iO^{nm-i} 
$$

其中 $J$ 为 $[L,R]$ 中奇数个数，$O$ 相反。

直接计算时间复杂度很大，需要化简。

化简式子要向一般形式靠拢。

即：

$$
F(nm) = \sum_{i=0}^{nm}\begin{pmatrix}nm\\i\end{pmatrix}J^iO^{nm-i} = (J + O)^{nm}
$$

发现我们是要消去其奇数项，所以我们可以乘上 $-1$。

$$
G(nm) = \sum_{i=0}^{nm}(-1)^i\begin{pmatrix}nm\\i\end{pmatrix}J^iO^{nm-i} = (J - O) ^ {nm}
$$

所以：

$$
ans = \frac{F(nm) - G(nm)}{2}
$$

注意，如果使用费马小定理（欧拉定理）降幂，注意指数因为模除法变为 $0$ 且底数也为 $0$ 的情况（$nm>0$ 所以实际上只需要考虑底数为 $0$ 即可）。

```cpp
#include<bits/stdc++.h>
#define int long long
const int mod = 998244353,inv2=499122177;
using namespace std;
int n,m,l,r,V;
int fpow(int a,int b)
{
    if(a == 0)return 0;
    int res = 1;
    while(b)
    {
        if(b & 1)res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res % mod;
}
int J,O;
void jo()
{
    if(l & 1)
    {
        if(r & 1)
        {
            J = (r + 1 - l + 1) >> 1;
            O = J - 1;
        }
        else
        {
            J = O = (r - l + 1) >> 1;
        }
    }
    else
    {
        if(r & 1)
        {
            J = O = (r - l + 1) >> 1;
        }
        else
        {
            O = (r + 1 - l + 1) >> 1;
            J = O - 1;
        }
    }
}
signed main()
{
    cin>>n>>m>>l>>r;
    V = r - l + 1;
    if(n * m % 2 == 0)
    {
        jo();
        if(J < O)swap(J,O);
        int ans = fpow((J + O) % mod,n * m % (mod-1));
        ans = (ans + fpow((J - O) % mod,n * m % (mod-1))) % mod;
        ans = ans * inv2 % mod;
        cout<<ans;
    }
    else
    {
        cout<<fpow(V % mod,n * m % (mod-1));
    }
    return 0;
}
```

---

## 作者：Wf_yjqd (赞：1)

蒟蒻第一次自己完整地推出紫色的数数题诶！！

建议不要直接贺结论，多少看看过程。

------------

显然可以根据奇偶性将所有格子的值控制在极差为 $1$ 的情况。

然后考虑有一些凸起。

可以相邻两个加一然后把凹的填起来以随意改变凸起的位置。

若最初奇偶个数都为奇数则不能成功。

考虑正难则反，求不能的个数。

$n\times m$ 必须是偶数，否则全部可行，输出 $(R-L+1)^{n\times m}$。

暴力的思路是枚举奇数然后从 $n\times m$ 个中选奇数个再乘上奇偶分别方案数（即 $L$ 到 $R$ 中奇偶数分别的个数）。

设 $d=\lfloor\frac{R-L+1}{2}\rfloor$，则不能的个数为 $\sum\limits_{i=1}^{\frac{n\times m}{2}}{{n\times m}\choose{i\times2-1}}\times d^{i\times2-1}\times(R-L+1-d)^{n\times m-i\times2+1}$。

突然有种莫名的熟悉感，那就对了。

根据二项式定理，$(R-L+1)^{n\times m}=\sum\limits_{i=0}^{n\times m}{n\times m\choose i}\times d^i\times(R-L+1-d)^{n\times m-i}$。

这样就可以求出和为任意数的方案和了。

考虑减去和为偶数的情况，构造出式子 $(R-L+1-d\times2)^{n\times m}=\sum\limits_{i=0}^{n\times m}{n\times m\choose i}\times (-d)^i\times(R-L+1-d)^{n\times m-i}$。

其中所有 $i$ 为偶数时为正，奇数时为负。

$\frac{(R-L+1)^{n\times m}-(R-L+1-d\times2)^{n\times m}}{2}$（上式减去下式再除以二）即为不能的个数。

那么能的个数为 $(R-L+1)^{n\times m}-\frac{(R-L+1)^{n\times m}-(R-L+1-d\times2)^{n\times m}}{2}=\frac{(R-L+1)^{n\times m}+(R-L+1-d\times2)^{n\times m}}{2}$。

快速幂即可，逆元就一个，可以手算。

------------

注意特判 $n\times m$ 为奇数的情况。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll Mod=998244353,Inv=499122177;//2 在模 998244353 意义下的逆元
ll n,m,l,r;
inline ll Pow(ll x,ll y){
    if(!y)
        return 1;
    if(y&1)
        return Pow(x,y-1)*x%Mod;
    ll res=Pow(x,y>>1);
    return res*res%Mod;
}
int main(){
    scanf("%lld%lld%lld%lld",&n,&m,&l,&r);
    if((n*m)&1)
        printf("%lld",Pow(r-l+1,n*m));
    else
        printf("%lld",(Pow(r-l+1,n*m)+Pow((r-l+1)%2,n*m))%Mod*Inv%Mod);//R-L+1-d*2=(R-L+1)%2
    return 0;
}
```


---

## 作者：_Cheems (赞：0)

观察到奇偶性相同的元素一定可以对较小者不断放两个方块，使得它们相等。于是条件可以转化为所有 $a$ 奇偶性相等。

记 $b_{i,j}=0/1$ 表示 $a_{i,j}$ 偶数还是奇数，将原矩阵视作网格图，那么相邻元素同时 $+1$ 等价于将这条边的两端的 $b$ 取反。

然后考虑一条路径 $p_1\to p_2\dots \to p_m$，那么可以对路径上的边操作，使得恰好只有 $p_1,p_m$ 取反。假如是让所有 $b$ 变成 $0$，那么可以让两个 $1$ 按照上面方式都变成 $0$。

全变成 $1$ 也同理，所以 $1$ 或 $0$ 的个数为偶数时合法。

记 $c_0,c_1$ 表示 $b_{i,j}=0/1$ 时，$a_{i,j}$ 有几种可选方案。可以分类计算答案：

* 当 $2\nmid nm$：

$$ans=\sum\limits_{i=0}^{nm} {{nm}\choose i} {c_0}^i{c_1}^{nm-i}$$

* 当 $2\mid nm$：

$$ans=\sum\limits_{2\mid i}^{nm} {{nm}\choose i} {c_0}^i{c_1}^{nm-i}$$

看了看数据范围，暴力计算是不可能的。注意到 $2\nmid nm$ 的情况符合优美的二项式定理，即等价于 $(c_0+c_1)^{nm}$。

但是 $2\mid nm$ 中只看偶数，怎么办？回想起数学课上学等比数列求和也有类似的题，是加入 $-1$ 然后和原序列加起来，消掉我们不想要的项。

所以不难想出：

$$ans=\frac {(c_0+c_1)^{nm}+(-c_0+c_1)^{nm}} 2$$

随便敲个快速幂就好，欧拉定理？感觉没啥必要。
#### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long
const int mod = 998244353; 
int n, m, l, r, _l, _r, c0, c1;
int ans;

inline int qstp(int a, int k) {int res = 1; for(; k; k >>= 1, a = a * a % mod) if(k & 1) res = res * a % mod; return res;}
signed main(){
	cin >> n >> m >> l >> r;
	_l = (l + 1) / 2 * 2, _r = r / 2 * 2;
	c0 = ((_r - _l) / 2 + 1) % mod;
	c1 = (r - l + 1 - c0) % mod;
	if((n * m) % 2 == 1)
		cout << qstp((c0 + c1) % mod, n * m) % mod;
	else
		cout << (qstp((c0 + c1) % mod, n * m) + qstp((-c0 + c1 + mod) % mod, n * m)) % mod * qstp(2, mod - 2) % mod;
	return 0;
}
```

---

## 作者：zzzmlz (赞：0)

# [CF1332E Height All the Same](https://www.luogu.com.cn/problem/CF1332E)

参考：《深入浅出程序设计竞赛 进阶篇》

## 题意
给一个 $n\times m$ 的网格，格子上有数字 $a_{i,j}\in [L,R]$。有两种操作：给两个相邻格子中的数字各加 1；给一个格子中的数加 2。给定 $n,m,L,R$，问有多少种初始状态可以经过若干次操作后达到所有数字相等。

## 题解

### 第一波思路

- 1 和 2 的特殊之处在于奇偶不同，解题关键点是**奇偶性**。

- 加 2 不改变原数奇偶性，且同奇偶的两个数一定可以加成相等的数。而加 1 是会改变数的奇偶性的，只不过这个加 1 带了点花活，还需要具体分析。  
所以原目标“所有数相同”，就等价于，通过相邻两数加 1 操作使所有数同奇偶。

### 第二波思路

- 相邻位置加 1，则两个位置奇偶性都发生改变。具体研究一下这种变化：假设现在奇数有 $a$ 个，偶数有 $b$ 个，若两个数同为奇数，则 $a-2,b+2$；若两个数一奇一偶，则没有变化；若同为偶数，则 $a+2,b-2$。  
哇，**奇数和偶数的个数竟然也是同奇偶变化的**！

- 也就是说，要达到所有数同奇偶，即奇数或偶数的个数为零，就需要奇数的个数 $a$ 和偶数的个数 $b$ 有一个为偶数。这样就能每次找两个数出来变奇偶行，不断减到零了。

### 第三波思路

- 等一下，还有一个“相邻数各加 1”的“相邻”要求没有满足，怎么办？

- 看一下如果两个奇数（或偶数）不相邻，我能不能一起改变他俩的奇偶性？

- 可以，**只需要在他俩的路径上相邻两个都做一次加 1 操作就可以了**，中间的数都经历了两次加 1，不会改奇偶性，两头只有一次加 1，很成功。

### 第四波思路

- 解决了实际改数的问题，回到奇数个数 $a$ 和偶数个数 $b$ 的变化上。如何计算答案？

- $n\times m = a+b$

- 如果 $n\times m$ 是奇数，那任意局面 $a$ 和 $b$ 一定是一奇一偶。答案就是 ${(R-L+1)}^{n\times m}$。

- 如果 $n\times m$ 是偶数，那 $a$ 和 $b$ 需要都是偶数，那 $(a,b)$ 可能的情况就是 $(0,n\times m),(2,n\times m -2),...,(n\times m,0)$。

- 然后是奇数和偶数填在哪个格子，这个就是简单的组合数

- 最后考虑具体填什么数，$[L,R]$ 区间内奇数和偶数的个数是确定的，设为 $k$ 和 $l$。这个很好计算。

- 那么答案就是，写的大一点点

$$\sum_{2|a,a=0}^{n\times m}{C_{n\times m}^{a}\times k^a \times l^b}$$

### 第五波思路

- 看一眼 $1\le n,m \le 10^9$，爆！

- 观察一下式子，发现他长的和**二项式定理**有点像，具体有多像，写出来看看

$$(k+l)^{n\times m}=\sum_{a=0}^{n\times m}{C_{n\times m}^{a}\times k^a \times l^b}$$

- 懂了！只有 $2|a$ 偶数项，没有奇数项。那接下来这个课内都学过的操作就解决掉这个问题了

$$(k-l)^{n\times m}=\sum_{a=0}^{n\times m}{(-1)^{b} \times C_{n\times m}^{a}\times k^a \times l^b}$$

- 偶数项还是正的，奇数项变负了，两式相加加再除以 2，就是答案。

参考代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int mod=998244353;
ll ksm(ll x,ll n)
{
    ll res=1;
    while(n){
        if(n&1)res=res*x%mod;
        x=x*x%mod;n>>=1;
    }
    return res;
}
ll n,m,L,R;
int main()
{
    cin>>n>>m>>L>>R;
    if((n*m)%2==1)
        cout<<ksm((R-L+1),n*m)<<endl;
    else{
        //[L,R]端点奇偶性,len=R-L+1
        //奇奇:      k=len/2+1,l=len/2
        //奇偶、偶奇: k=l=len/2
        //偶偶:      k=len/2,l=len/2+1
        ll len=R-L+1,k,l;
        if(L%2==1 && R%2==1){
            k=len/2+1;
            l=len/2;
        }
        else if(L%2==0 && R%2==0){
            k=len/2;
            l=len/2+1;
        }
        else k=l=len/2;
        cout<<(ksm(k+l,n*m)+ksm(k-l,n*m))*ksm(2,mod-2)%mod<<endl;
        //模意义下除以2等价于乘2的逆元
        
    }
    return 0;
}
```

---

## 作者：lrqlrq250 (赞：0)

## 题意简述
给定一个 $n \times m$ 的棋盘，每个格子里有一个数字，你有两种操作，分别是将相邻（四联通）的两个格子中的数分别 $+1$，或者将一个格子 $+2$。询问你在初始每个格子中的数都在 $[L, R]$ 时，有多少种初始局面可以使得在经过若干次操作后，所有格子中的数均相等。

## 解题思路

首先可以注意到，每个位置最后究竟是多少不重要，只有奇偶性是重要的，因为对于奇偶性相同的位置，你可以不断用操作 $2$ 使其相等。

于是后面我们就只考虑奇偶性了。将两种操作在奇偶性上的影响提取出来：

- 第一种操作：交换两个奇偶性不同的位置的奇偶性，或消除两个奇数/偶数。

- 第二种操作：在所有位置的奇偶性都相同后用于推平所有位置。

我们发现操作 $1$ 一次只能消除 $2$ 个位置，这启发我们先考虑全局的奇偶性。如果总共有奇数个格子，那么奇数和偶数一定有且仅有一种有偶数个，不妨用奇数有偶数个举例，那么通过第一种操作一定可以把所有奇数都变成另一种奇偶性，操作大概类似于：

- 如果存在相邻的奇数，执行一次操作 $1$，把它们都变成偶数。

- 否则，所有奇数的周围都是偶数，通过操作 $1$ 可以“移动”奇数的位置，再次让奇数相邻。

于是如果 $nm$ 是奇数，那么随便填都是有解的，此时答案即为 $(R-L+1)^{nm}$。

下面考虑 $nm$ 为偶数的情况。

$\text{Lemma}\ \alpha$：有解的充要条件为一共有偶数个奇数。

必要性：考虑反证，如果有奇数个奇数，那么所有位置上数的和应为奇数。但显然最后所有位置的和一定是 $nm$ 的倍数，是偶数，矛盾。

充分性：和 $nm$ 为奇数中给出的操作方式相同。

因此，令 $num_o$ 为 $[L, R]$ 中的奇数个数，$num_e$ 为偶数个数，可以得出方案数为：
$$\sum\limits_{i=0}^{nm/2}{\binom{nm}{2i} num_o^{2i}num_e^{nm-2i}}$$
注意到这个形式非常像二项式定理展开的 $(num_o + num_e)^{nm}$，实际上这是其展开式中的奇数项。

那么套路地，我们可以构造其对偶式 $(num_o - num_e)^{nm}$，两式相加即为二倍原式。

即，答案为 $\dfrac{(num_o + num_e)^{nm} + (num_o - num_e)^{nm}}{2}$，可以直接快速幂，在 $O(\log(nm))$ 内求解。当然，使用扩展欧拉定理可以将其优化为 $O(\log P)$，不过个人认为没有什么必要。

## AC Code
```cpp
#include <bits/stdc++.h>
#define ll long long
#define mod 998244353
using namespace std;
ll n, m, L, R, len, no, ne;

inline ll fpow(ll a, ll k){
	if (!a) return 0;//偶数和奇数个数可能相同，所以这个必须有
	ll res = 1;
	for (; k; a = a * a % mod, k >>= 1) if (k & 1) res = res * a % mod;
	return res;
}

int main(){
	scanf("%lld%lld%lld%lld", &n, &m, &L, &R); len = R - L + 1;
	if ((n * m) & 1){printf("%lld\n", fpow(len, n * m)); return 0;}
	ne = (R >> 1) - ((L - 1) >> 1); no = len - ne;
	printf("%lld\n", ((fpow(no + ne, n * m) + fpow((no - ne + mod) % mod, n * m) + mod) % mod) * fpow(2, mod - 2) % mod);
	return 0;
}
```


---

## 作者：jnzg (赞：0)

对于在一个格子上放两个方块的操作，方块数奇偶性未变；对于在两个格子上各放一个方块的操作，两个格子上方块数奇偶性改变。当所有格子方块数奇偶性相同时，一定可以通过第一种操作使方块数相同。

因此，实际上问的是有多少种初始状态，可以通过每次改变相邻格子的奇偶性，使得所有格子奇偶性相同。

考虑一种初始状态，令奇数为 $1$，偶数为 $0$，可以得到这样一张表：

![](https://cdn.luogu.com.cn/upload/image_hosting/40nn4745.png)

每次操作可以将相邻两格的 $0$ 和 $1$ 翻转。

考虑从左到右将 $1$ 移到最后一列，再移到最后一列的最后一格：

![](https://cdn.luogu.com.cn/upload/image_hosting/feurlzlb.png)

显然，每一行移到最后一列上的数是否为 $1$，取决于这一行 $1$ 的个数。具体而言，当一行 $1$ 的个数为奇数时，最后一列的数为 $1$，否则为 $0$。将最后一列的数移到最后一格同理。

当 $n$ 和 $m$ 都为奇数时，对于最后剩下 $0$ 的状态，是符合条件的状态；对于最后剩下 $1$ 的状态，画图可得可以构造成全部为 $1$。因此所有状态都符合条件，答案为 $(r-l+1)^{mn}$。

其他情况，总格数为偶数，画图可得，如果能使所有格子为 $1$，也一定能使所有格子为 $0$；如果能使所有格子为 $0$，也一定能使所有格子为 $1$。所以只需要计算一种情况。

令能选的偶数数量为 $E$，奇数数量为 $O$。

$f_1$ 为每行 $1$ 个数为奇数状态数，$f_2$ 为每行 $1$ 个数为偶数状态数。

$m$ 为偶数时：

$f_1=\binom{m}{1}OE^{m-1}+\binom{m}{3}O^3E^{m-3}+...+\binom{m}{m-1}O^{m-1}E=\frac{(E+O)^m-(E-O)^m}{2}$。

$f_2=\binom{m}{0}E^{m}+\binom{m}{2}O^2E^{m-2}+...+\binom{m}{m}O^{m}=\frac{(E+O)^m+(E-O)^m}{2}$。

$m$ 为奇数时：

$f_1=\binom{m}{1}OE^{m-1}+\binom{m}{3}O^3E^{m-3}+...+\binom{m}{m}O^{m}=\frac{(E+O)^m-(E-O)^m}{2}$。

$f_2=\binom{m}{0}E^{m}+\binom{m}{2}O^2E^{m-2}+...+\binom{m}{m-1}O^{m-1}E=\frac{(E+O)^m+(E-O)^m}{2}$。

两种情况相同。

类似的，令 $ans$ 为将最后一列 $1$ 个数为偶数的方案数，即最终答案。

$n$ 为奇数时：

$ans=\binom{n}{1}f_1^{n-1}f_2+\binom{n}{3}f_1^{n-3}f_2^{3}+...+\binom{n}{n}f_2^{n}=\frac{(f_1+f_2)^n+(f_2-f_1)^n}{2}$。

$n$ 为偶数时：

$ans=\binom{n}{0}f_1^{n}+\binom{n}{2}f_1^{n-2}f_2^{2}+...+\binom{n}{n}f_2^{n}=\frac{(f_1+f_2)^n+(f_2-f_1)^n}{2}$。

两种情况相同。

因此，将 $f_1$ 和 $f_2$ 代入，得 $ans=\frac{(E+O)^{mn}+(E-O)^{mn}}{2}$。

Code:

```cpp
#include <bits/stdc++.h>
#define ll long long
#define lp(i, j, n) for(int i = j; i <= n; ++i)
#define dlp(i, n, j) for(int i = n; i >= j; --i)
#define mst(n, v) memset(n, v, sizeof(n))
#define mcy(n, v) memcpy(n, v, sizeof(v))
#define INF 1e18
#define MAX4 0x3f3f3f3f
#define MAX8 0x3f3f3f3f3f3f3f3f
#define lc(x) (x << 1)
#define rc(x) ((x << 1) ^ 1)
#define co(x) cout << x << ' '
#define cod(x) cout << x << endl
#define pb(x) emplace_back(x)
#define mkp(x, y) makepair(x, y)
#define pii pair<int, int>
#define pll pair<ll, ll>,
#define fi first
#define se second

using namespace std;

const ll MOD = 998244353;

ll n, m, l, r;

ll qpow(ll x, ll k) {
    ll res = 1; x = x % MOD + MOD;
    while(k) {
        if(k & 1) res = res * x % MOD;
        x = x * x % MOD, k >>= 1;
    }
    return res;
}

signed main() {
    //freopen(".in", "r", stdin);
    //freopen(".out", "w", stdout);
    #ifndef READ
        ios::sync_with_stdio(false);
        cin.tie(0);
    #endif
    cin >> n >> m >> l >> r;
    if(n & 1 && m & 1) return cout << qpow(r - l + 1, m * n), 0;
    ll E = (r - l + 1) / 2 + ((l & 1) && (r - l + 1) & 1), O = (r - l + 1) / 2 + (!(l & 1) && (r - l + 1) & 1);
    ll res = (qpow(E + O, m * n) + qpow(E - O, m * n)) % MOD * (MOD + 1) / 2 % MOD;
    cout << res;
    return 0;
}
```


---

## 作者：w9095 (赞：0)

[CF1332E Height All the Same](https://www.luogu.com.cn/problem/CF1332E)

考虑到可以在一个格子上码上两个方块，易得如果每个格子奇偶性相同，则一定可以到达同样高度。对于任意点对 $(x,y)$，我们可以通过找到一条路，路径上可以互达的两点有一边相邻，$x\to b\to c\dots\to y$，每次增加相邻两个点，这样除了 $x,y$ 各自加 $1$，其余的点均加 $2$，奇偶性不变。 

所以，我们每次可以改变两个点的奇偶性。对于 $nm$ 为奇数的情况，我们一定可以找到一种奇偶性的数有偶数个，每次修改一对为另一种奇偶性。也就是说，对于任意一种初始情况，均可以修改至完全相同。数量为 $(r-l+1)^{nm}$。

对于 $nm$ 为偶数的情况，只有奇偶数个数均为偶数时才满足要求。考虑枚举奇数数量方案数累加，运用乘法原理求出每种情况的方案数。我们先选位置，如果现在有 $i$ 个奇数，则有 $C_{nm}^{i}$ 种选法。设 $[l,r]$ 有 $a$ 个奇数，$b$ 个偶数，则奇数有 $a^i$ 种方法，偶数有 $b^{nm-i}$ 种选法。

$$\sum_{i=0,2\mid i}^{nm}C_{nm}^{i}a^ib^{nm-i}$$

看到这个式子，容易联想到二项式定理。但是这个式子不好转化，需要转化为对于每一个 $i$ 都有一个计算式。我们考虑用整体减去部分，可是还是不行。顺着这个思路，可以想到利用 $-1$ 的幂构造摆动数列，当 $i$ 为奇数时，$(-1)^i$ 刚好为负数，表示减去奇数项；当 $i$ 为偶数时，$(-1)^i$ 为正数，尽管有重复计算，可是恰好答案中的每种情况算了两遍，最后除以 $2$ 即可。

$$\frac{(r-l+1)^{nm}-\sum_{i=0}^{nm}(-1)^iC_{nm}^{i}a^ib^{nm-i}}{2}$$

直接利用二项式定理进行转化，达到复杂度 $O(\log(nm))$。

$$\frac{(r-l+1)^{nm}-(b-a)^{nm}}{2}$$

```cpp
#include <bits/stdc++.h>
using namespace std;
long long n,m,l,r,mod=998244353;
long long power(long long a,long long p)
{
	long long x=a,ans=1;
	while(p)
	   {
	   	if(p%2==1)ans=ans*x%mod;
	   	p/=2;
	   	x=x*x%mod;
	   }
	return ans;
}

int main()
{
	scanf("%lld%lld%lld%lld",&n,&m,&l,&r);
	if(n*m%2==1)printf("%lld",power(r-l+1,n*m));
	else 
	    {
	    	long long a=(r-l+1)/2,b=0;
	    	if((r-l+1)%2==1&&l%2==1)a++;
	    	b=r-l+1-a;
	    	printf("%lld",(power(r-l+1,n*m)+power((b-a+mod)%mod,n*m))%mod*499122177%mod);
		}
	return 0;
}
```


---

## 作者：Pwtking (赞：0)

做这道题之前，你需要掌握**二项式定理**，并且有一个思维强大的头脑（~~这其实更重要~~）。

首先我们可将立体图形转化为一个 $n \times m$ 的平面矩阵，其中每个数代表坐标位置的方块个数。

我们看到操作数的性质，可以考虑用奇偶性来解决这道题。众所周知，一**个数无论奇偶加上二之后奇偶性都不会改变**，所以若所有起始数的奇偶性都相同，那么一定可以通过若干次操作二变成相同的数，那么我们现在只需要考虑如何将所有的数都变成同奇偶性即可。

通过多次的举例我们可以发现一个规律，若这 $n \times m$ 个数奇数或偶数的个数有一个为偶数就可将他们变为奇偶性相同。

为什么？

若其中一个的数量为偶数，则可将他们其中任两个数两两配对，通过若干次操作一的方式全部改变他们的奇偶性且不改变其他数的奇偶性（读者可以画图自证）。

接下来分类讨论。

我们将这 $n \times m$ 个数中，奇数的个数为 $a$，偶数的个数为 $b$。

若 $n \times m$ 为奇数，则显然方案数为 $( r-l+1)^n \times m$。

若 $n \times m$ 为偶数，则需要满足 $a$，$b$ 均为偶数，方案数可以通过二项式定理转化为 $\frac{(k+l)^M+(k-l)^M}{2} $，其中 $M=n \times m$。

---

## 作者：pengyule (赞：0)

[1332E Height All the Same](http://codeforces.com/problemset/problem/1332/E)
> 对于一个 $n*m$ 的矩阵，可以执行任意次操作，每一次操作任选下列两种之一：
> - 将一对相邻元素同 $+1$
> - 将一个元素 $+2$
> 
> 有多少个矩阵 $a$ 同时满足：
> - $L\le a_{i,j}\le R$
> - 可以使最终所有元素相等
> 
> $n,m,L,R\le 10^9$



容易看出问题的本质在于奇偶性。关键在发现：**任意一对矩阵中的偶数都可以通过修改一条“路径”（类似曼哈顿距离）同时改变其奇偶性，而不改变矩阵中其他元素奇偶性；任意一对矩阵中的奇数都可以通过修改一条“路径”（类似曼哈顿距离）同时改变其奇偶性，而不改变矩阵中其他元素奇偶性**。所以问题转为求【含偶数的个数是偶数或奇数的个数是偶数的矩阵数量】。

![image3149b8f1d3772346.png](https://www.z4请更换图床a.net/images/2022/04/26/image3149b8f1d3772346.png)

当 $2\nmid n$，必然成立。
当 $2\mid n$，显然需要偶/奇数的个数是偶数，$\sum_{0\le i\le nm,2|i}{n\choose i}p^iq^{nm-i}$，这个类似于二项式定理的一半，通过 $(p+q)^{nm}+(p-q)^{nm}$ 消去奇数项。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353;
int n,m,l,r;
int qp(int a,int b){
	int c=1;
	for(;b;b>>=1,a=a*a%mod)if(b&1)c=c*a%mod;
	return c;
}
signed main(){
	cin>>n>>m>>l>>r;
	if(n*m&1)cout<<qp(r-l+1,n*m);
	else cout<<(mod+1)/2*(qp(r-l+1,n*m)+(r-l+1&1))%mod;
}
```

---

## 作者：F_Mu (赞：0)

**题意**

对于一个$n\cdot m$的矩阵，有两种操作

+ 一个格子加二
+ 一个格子和另一个相邻的格子同时加一

通过这两种操作最终使得所有矩阵元素相等

对于矩阵元素来说，有$L\leq a_{i,j}\leq R(1\leq i\leq n,1\leq j\leq m)$

问有多少种方案数，答案$\mod 998244353$


**分析**

由于最终相等的值与答案无关，所以我们不妨所有元素减去$L$，即所有元素的值在$[0,R-L]$区间内

而所有元素通过操作可以相差最多为$1$（仅仅分奇偶）

这种操作可以不断进行，所以我们只需看数字的奇偶性

为描述，我们不妨将所有元素视为$0,1$

对于$1$来说，其周围一定没有$1$，否则可以填上使两元素变为$0$，那么如果该$1$和旁边的$0$同时加$1$，我们可以发现$0$和$1$互换位置了

这种操作的意义在于，对于任意的一个$1$，我们可以通过操作使其变到其他任意的位置

那么如果矩阵中有奇数个$1$，我们可以将其变为$1$个$1$，而偶数个$1$，我们一定可以将两个$1$进行配对，从而消去

我们思考$n\cdot m$的奇偶性

+ 若$n\cdot m$为奇数，若有偶数个$1$，则满足条件，若有奇数个$1$，我们将其变为$1$个$1$，并将其移动到边角上，通过蛇形配对，我们可以将除该元素的其他元素同时加上$1$，所有元素相等，因此所有取值皆满足答案就是$(R-L+1)^{n\cdot m}$(每个数有$R-L+1$中取法)
+ 若$n\cdot m$为偶数，若有偶数个$1$，则满足条件，若有奇数个$1$，我们可以发现元素和为奇数，而$n\cdot m$为偶数，元素和无论怎么增加（每次加二），一定是奇数，无法整除$n\cdot m$一定不满足，因此答案为偶数个$1$的取值方式

接下来分析$n\cdot m$为偶数时，有多少种偶数个$1$的取值方式：

如果$R-L+1$为奇数，则可以取$\frac {R-L+2} {2}$种奇数，否则为$\frac {R-L+1} {2}$种奇数，设为$j$，设$R-L+1$为$t$

答案为$C_{n\cdot m}^0\cdot j^0\cdot (t-j)^{n\cdot m}+C_{n\cdot m}^2\cdot j^2\cdot (t-j)^{n\cdot m-2}+\cdots+C_{n\cdot m}^{n\cdot m}\cdot j^{n\cdot m}\cdot (t-j)^{0}$，意思为挑偶数（$2\cdot k$）个奇数（$C_{n\cdot m}^{2\cdot k}$），每个奇数有$j$中取值，其余偶数有$t-j$种取值

发现这个式子是二项展开式的偶数项，那么可以推导下（半小时无从下手，我对不起高中数学老师）

答案为
$
\frac{(j+(t-j))^{n\cdot m}+(j-(t-j))^{n\cdot m}}{2}
$
，原因可自己手写下两个式子的展开式，$LaTeX$老炸，心累

完整版为[CF1332E 【Height All the Same】](https://www.luogu.com.cn/blog/Giant-Mu/solution-cf1332E-post)
```cpp
#pragma GCC optimize(3, "Ofast", "inline")

#include <bits/stdc++.h>

#define start ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define ll long long
#define int ll
#define ls st<<1
#define rs st<<1|1
#define pii pair<int,int>
#define rep(z, x, y) for(int z=x;z<=y;++z)
#define com bool operator<(const node &b)
using namespace std;
const int maxn = (ll) 3e5 + 5;
const int mod = 998244353;
const int inf = 0x3f3f3f3f;

int qp(int x, int y) {
    int ans = 1;
    while (y) {
        if (y & 1)
            ans = ans *  x % mod;
        x = x *  x % mod;
        y >>= 1;
    }
    return ans;
}

signed main() {
    start;
    int n, m, L, R;
    cin >> n >> m >> L >> R;
    int t = R - L + 1;
    if ((n *  m) & 1) {
        cout << qp(t, n *  m) % mod;
    } else {
        int j;
        if (t & 1)
            j = (t + 1) / 2;
        else
            j = t / 2;
        int ans = ((qp(t, m *  n) + qp((2 *  j - t), m *  n)) % mod + mod) % mod *  qp(2, mod - 2) % mod;
        cout << ans;
    }
    return 0;
}
```

---

