# How Many of Them

## 题目描述

在无向连通图中，若一条边被删除后，图会分成不连通的两部分，则称该边为割边。

求满足如下条件的无向连通图的数量：

1. 由 $n$ 个结点构成，结点有标号。

2. 割边不超过 $m$ 条。

3. 没有重边和自环。

答案对 $10^{9}+7$ 取模。

## 说明/提示

$2≤n≤50$，$0≤m≤\dfrac{n(n-1)}{2}$。

Source: Gennady Korotkevich (tourist), ITMO University.

## 样例 #1

### 输入

```
3 3```

### 输出

```
4```

## 样例 #2

### 输入

```
5 1```

### 输出

```
453```

# 题解

## 作者：pythoner713 (赞：28)

蒟蒻初学计数DP，这篇题解的代码是照着 lyd 书上的思路写的。希望对初学者有所帮助，望大佬轻喷。

题意十分清晰，求满足三个条件的**连通图数量**。

乍一眼看难以下手。因为「连通图」「割边」这些概念都是沿用自图论，但问题在于统计图的**数量**，而这又是一个数论问题。

如果我们从**图论**角度出发，不难想出一个暴力做法：对于包含 $n$ 个节点的图，一共有 $\frac{n(n-1)}{2}$ 条可能的边，我们二进制枚举每条边是否存在，从而得到所有 $n$ 个节点的图。然后对于每个图，都 $\text{Tarjan}$ 求出割边数量，判断是否符合条件。然而复杂度已经高达 $O(2^{n^2}\times n)$，当场劝退。

于是只能考虑用**数学**方法计算出答案，这时就要请出计数DP了。

计数DP，顾名思义，就是统计数量的DP。~~听上去好像没什么~~，但它统计的一般是诸如「方案数」等更抽象、难以统计的玩意儿，所以思维难度蛮高。光说不练假把戏，我们来到题练练手：

$$\text{求 }n\text{ 个节点的无向联通图有几个？}$$

此处节点有序。是不是跟这题有点像？从DP角度考虑，不妨设 $h[i]$ 表示 **$i$ 个节点的无向连通图数量**。然后重点来了：由于直接统计有些困难，我们先考虑**不合法**的方案数，也就是非联通图数，然后用无向图总数减去非联通图数便是答案。

根据上面的分析，每条边可有可无，因此对于 $i$ 个节点，共有 $2^{\frac{i(i-1)}{2}}$ 个无向图。然后对于非联通图来说，我们考虑 $1$ 号节点，它必定属于某个连通块。我们枚举这个连通块的大小 $j$，也就是在剩下 $i-1$ 个节点中选出 $j-1$ 个与节点 $1$ 相连，有$\binom{i-1}{j-1}$ 种选法。而根据定义，这坨大小为 $j$ 的连通块有 $h[j]$ 个不同形态。然后对于外面剩余的 $i-j$ 个节点随意构成无向图，共有 $2^{\frac{(i-j)(i-j-1)}{2}}$ 种方案。因此不合法方案数便是这三者之积：$h[j]\times\binom{i-1}{j-1}\times2^{\frac{(i-j)(i-j-1)}{2}}$。再用总数减去这些非法方案数就，得到了通项公式：

$$h[i]=2^{\frac{i(i-1)}{2}}-\sum_{j=1}^{i-1}h[j]\times\binom{i-1}{j-1}\times2^{\frac{(i-j)(i-j-1)}{2}}$$

代码实现：

```cpp
	for(int i = 2; i <= n; i++){
		h[i] = qpow(2, i * (i - 1) / 2);
		for(int j = 1; j < i; j++){
			h[i] -= h[j] * C[i - 1][j - 1] % P * qpow(2, (i - j) * (i - j - 1) / 2) % P;
			h[i] = (h[i] % P + P) % P;
		}
	}
```


（感觉我解释得好烂啊）。这便是计数DP的[一道例题](https://www.luogu.com.cn/problem/P4841)了（

我们接下来会发现这个 $h$ 有点用。

回到本题，它只是在上题的基础上加了**割边不超过 $m$ 条**的限制条件，我们考虑给DP数组多加一维：另 $f[i][j]$ 表示 **$i$ 个节点构成的包含 $j$ 条割边的无向连通图数量**。先考虑 $j>0$ 如何转移。

没有割边的图就是双联通分量，于是我们照葫芦画瓢，考虑节点 $1$ 所在的双联通分量。我们枚举这个双联通分量的大小 $k$，也就是在剩下的 $i-1$ 个节点中选出 $k-1$ 个节点与 $1$ 构成双联通分量，共有 $f[k][0]\times\binom{k-1}{i-1}$ 种方案（$f[k][0]$ 割边为0，即双联通分量数）。

然后考虑外部节点的连接方案数，我们开一个新数组记录。由于外部节点不一定连通，我们得多开一维记录有几个连通块：令 $g[i][j][k]$ 表示**由 $i$ 个节点构成的、有 $j$ 个连通块的、含 $k$ 条割边的无向图数量**。其实这个 $g$ 只是 $f$ 的升级版，多了一维记录连通块数量的 $j$ 维度，方便转移。瞧，把每个双联通分量看成一个点，就形成了一棵树，像这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/y75wa20s.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/ms4ojol1.png)

回到 $f[i][j]$，删除了 $1$ 所在这个双联通分量后，还剩  _$i-k$ 个节点_ 。假设还剩  _$x$ 个连通块_ （在上图中 $x=2$），则还剩下 _$j-x$ 个割边_ （因为每个连通块贡献一条割边）。留意标斜体的这三处，不正好**对应 $g$ 的三个维度吗**？即 $g[i-k][x][j-x]$ 。然后外面每个连通块都可以连通到这 $k$ 个点中的任意一个，所以有 $k^x$ 个连接方案。

综上所述，枚举 $x$， 外部节点的方案数即为两者之积之和 $\sum_{x=1}^{\min(i-k,j)}g[i-k][x][j-x]\times k^x$

这时，将外部节点方案数，乘上内部节点方案数 $f[k][0]\times\binom{k-1}{i-1}$ 就得到了总方案数：

$$f[i][j]=\sum_{k=1}^{i-1}\left( f[k][0]\times\binom{k-1}{i-1}\times \sum_{x=1}^{\min(i-k,j)}g[i-k][x][j-x]\times k^x\right)$$

~~这不就是书上的公式么~~。那么对于 $j>0$，$f[i][j]$ 就算完了。What about $f[i][0]$ ?

上 $\text{OEIS}$ 找找，$f[i][0]$ 就是 $i$ 个节点构成的双联通分量数量[A095983](http://oeis.org/A095983)。它不正好等于 $i$ 个点的[无向图数量](http://oeis.org/A001187)减去[至少包含一条割边的无向图数量吗](http://oeis.org/A327071)？

惊奇地发现，前者就是本文开篇讲的 $h$ 数组！而后者，根据定义，就是 $f[i][j] (j>0)$ 的和呀。于是我们就有：

$$f[i][0]=h[i]-\sum_{j=1}^{i-1}f[i][j]$$

因此 $f$ 数组的DP顺序其实是 $j>0$ 先，$j=0$ 后：

```cpp
for(int j = 1; j < i; j++){
			for(int k = 1; k < i; k++){
				int tmp = 0;
				for(int x = 1; x <= min(i - k, j); x++){
					tmp = (tmp + g[i - k][x][j - x] * qpow(k, x) % P) % P;
				}
				f[i][j] = (f[i][j] + f[k][0] * C[i - 1][k - 1] % P * tmp % P) % P;
			}
		}
		f[i][0] = h[i];
		for(int j = 1; j < i; j++){
			f[i][0] -= f[i][j];
			f[i][0] = (f[i][0] % P + P) % P;
		}
```

最后考虑如何求出 $g[i][j][k]$，我们考虑这 $i$ 个点中编号最小的点所在的连通块。枚举该连通块的大小 $p$ 和割边数量 $q$，则这个连通块的方案数为 $f[p][q]\times \binom{i-1}{p-1}$。我们再在这 $p$ 个点中选一个用于与删掉的双连通块相连，显然有 $p$ 种选法。图中其他部分又有 $g[i-p][j-1][k-q]$ 种方案，所以得到转移方程（由于赶时间搬了段书上原话）：

$$g[i][j][k]=\sum_{p=1}^{i}\sum_{q=0}^{k}f[p][q]\times \binom{i-1}{p-1}\times p\times g[i-p][j-1][k-q]$$

至此，这道题大功告成。

---

$$h[i]=2^{\frac{i(i-1)}{2}}-\sum_{j=1}^{i-1}h[j]\times\binom{i-1}{j-1}\times2^{\frac{(i-j)(i-j-1)}{2}}$$

$$f[i][j]=\sum_{k=1}^{i-1}\left( f[k][0]\times\binom{k-1}{i-1}\times \sum_{x=1}^{\min(i-k,j)}g[i-k][x][j-x]\times k^x\right)$$

$$f[i][0]=h[i]-\sum_{j=1}^{i-1}f[i][j]$$

$$g[i][j][k]=\sum_{p=1}^{i}\sum_{q=0}^{k}f[p][q]\times \binom{i-1}{p-1}\times p\times g[i-p][j-1][k-q]$$

---

刚才有个朋友问 $\texttt{pythoner713}$ 发生肾么事了，我说怎么回事，给我发了一几张截图。我一看！噢！原来是 $f,g$ 两个数组，一个两维，一个三维。两者间循环更新，是不是要写记忆化搜索？我说不用，只要跟着这 $4$ 个方程依次转移，就可以保证每个状态都恰好更新到。

```cpp
#include<bits/stdc++.h>
#define int long long
#define P 1000000007
using namespace std;

int ans, n, m, _2[4000], C[60][60], f[60][60], g[60][60][60], h[60];

int qpow(int A, int B){
	int r = 1;
	while(B){
		if(B & 1) r = (r * A) % P;
		A = (A * A) % P, B >>= 1;
	}
	return r;
}

signed main(){
	cin >> n >> m;
	_2[0] = 1;
	for(int i = 1; i <= 2500; i++) _2[i] = (_2[i - 1] << 1) % P;
	for(int i = 0; i <= 50; C[i++][0] = 1){
		for(int j = 1; j <= i; j++){
			C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % P;
		}
	}
	h[1] = 1;
	for(int i = 2; i <= n; i++){
		h[i] = _2[i * (i - 1) / 2];
		for(int j = 1; j < i; j++){
			h[i] -= h[j] * C[i - 1][j - 1] % P * _2[(i - j) * (i - j - 1) / 2] % P;
			h[i] = (h[i] % P + P) % P;
		}
	}
	g[0][0][0] = 1;
	for(int i = 1; i <= n; i++){
		for(int j = 1; j < i; j++){
			for(int k = 1; k < i; k++){
				int tmp = 0;
				for(int x = 1; x <= min(i - k, j); x++){
					tmp = (tmp + g[i - k][x][j - x] * qpow(k, x) % P) % P;
				}
				f[i][j] = (f[i][j] + f[k][0] * C[i - 1][k - 1] % P * tmp % P) % P;
			}
		}
		f[i][0] = h[i];
		for(int j = 1; j < i; j++){
			f[i][0] -= f[i][j];
			f[i][0] = (f[i][0] % P + P) % P;
		}
		for(int j = 1; j <= i; j++){
			for(int k = 0; k < i; k++){
				for(int p = 1; p <= i; p++){
					for(int q = 0; q <= k; q++){
						g[i][j][k] = (g[i][j][k] + (f[p][q] * C[i - 1][p - 1] % P * p % P * g[i - p][j - 1][k - q] % P)) % P;
					}
				}
			}
		}
	}
	for(int i = 0; i <= min(m, n); i++){
		ans = (ans + f[n][i]) % P;
	}
	cout << ans;
	return 0;
}
```



---

## 作者：小木虫 (赞：14)

### Preface
看很多佬写的很麻烦，我来一个复杂度较为优秀的简单算法。  
### Problem  
求 $n$ 个点，且割边数量不大于 $m$ 的有标号简单无向图个数。  
$n\leq 50,m\leq \frac{n(n-1)}{2}$。  

### Solution  
$m$ 大于 $n$ 时没意义，先判掉。

题目给的限制是割边，那么我们先把图缩点双再计数，剩下的图就是一棵树，树的每一个节点都是一个点双。  

有一个较为经典的结论：将有 $n$ 个点，$k$ 个已有联通块的图进行生成树计数的答案为：  
$$T=n^{k-2}\prod_{i=1}^k a_i \space \space(1)$$  
$a$ 为每个联通块的大小。  
证明此结论可以使用 prufer 序列，具体来说，prufer 序列是指向父亲的，我们对每个联通块选出一个点来指向该联通块的父亲，且每个联通块的父亲可以指向任何一个原图中的点，则可以轻易推出该结论。  

那么我们只需要确定联通块个数 $k$ 以及每个联通块的大小即可求出有 $k-1$ 条割边的图有多少个。  

$(1)$ 中的 $n^{k-2}$ 可以提出，我们实际关心的是后面的乘积，考虑动态规划算出乘积和。  

我们设 $f_{i,j}$ 为有 $i$ 个点，$j$ 条割边的所有无向图的边双大小乘积之和。  
形式化地说：  
$$f_{i,j}=\sum_G \prod_k^{j+1}a_k \space \space(2)$$  
其中 $G$ 为枚举所有割边数量为 $j$ 的图，后面的 $a$ 默认为 $G$ 的联通块。  

那么答案应该为：  
$$ans=\sum_{i=1}^m f_{n,i}\times n^{i-1} \space \space(3)$$  

考虑怎么算 $f$，容易列出转移方程：  
$$f_{i,j}=\sum_k^{i-1}f_{i-k,j-1}\times f_{k,0}\times \binom{i}{k}\space \space(4)$$  
这个方程没有限制 $j+1$ 个边双的顺序，去重的话直接最后给每个 $f$ 除 $j+1$ 的阶乘即可。  

这个动态规划还没有边界条件，即 $j=0$ 的时候怎么办，我们考虑容斥，将所有的方案减去不合法方案，即所有联通无向图减去 $j\neq 0$ 时的答案，形式如 $(3)$。  

联通无向图的求法较为简单，设 $g_n$ 为有 $n$ 个点时的答案,同样正难则反，则：  
$$g_n=2^{\binom{n}{2}}-\sum_i^{n-1}g_i\times \binom{n-1}{i-1}\times 2^{\binom{n-i}{2}}\space \space(5)$$
意义为钦定住点 $1$ 所在的联通块，其它不相关的边任选。  

那么我们就在 $O(n^3)$ 的时间复杂度内解决了此问题，此做法思路较为简单，容易理解。  

code：  
```cpp
#include <bits/stdc++.h>
#define mp make_pair
#define mt make_tuple
#define fir first
#define sec second
#define int long long
using namespace std;
const int N=55;
const int mod=1e9+7;
int n,m,f[N][N],g[N],G[N];
int qpow(int a,int b){
	if(b<0)return qpow(qpow(a,-b),mod-2);
	a%=mod;int res=1;
	while(b){
		if(b&1)res=res*a%mod;
		a=a*a%mod;b>>=1;
	}return res;
}
int C[N][N];
signed main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n>>m;m=min(m,n);
	for(int i=0;i<=n;i++){
		C[i][0]=1;
		for(int j=1;j<=i;j++)
			C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<i;j++){
			for(int k=1;k<i;k++){
				f[i][j]+=f[i-k][j-1]*f[k][0]%mod*C[i][k]%mod;
				f[i][j]%=mod;
			}
		}
		g[i]=qpow(2,i*(i-1)/2);
		for(int j=1;j<i;j++){
			g[i]+=mod-C[i-1][j-1]*g[j]%mod*qpow(2,(i-j)*(i-j-1)/2)%mod;
			g[i]%=mod;
		}
		int res=g[i];int fac=1;
		for(int j=1;j<i;j++){
			fac*=(j+1);fac%=mod;
			res-=f[i][j]*qpow(fac,mod-2)%mod*qpow(i,j-1)%mod;
			res+=mod;res%=mod;
		}
		f[i][0]=i*res%mod;
	}
	int ans=0,fac=1;
	for(int i=0;i<=m;i++){
		fac*=(i+1);fac%=mod;
		ans+=f[n][i]*qpow(fac,mod-2)%mod*qpow(n,i-1)%mod;
		ans%=mod;
	}
	cout<<ans<<endl;
	return 0;
}

```

---

## 作者：NaCly_Fish (赞：11)

神仙 $\mathsf i \color{red}\mathsf{ostream}$ 写的有点太简洁了，补一篇详细点的解释吧（
****
题目中要求割边数**不超过** $m$ 条，那可以考虑计算 $f_k$ 为「有 $k$ 个点双连通分量的无向连通图数」，那么求 $f_0,f_1,\dots,f_{m+1}$ 之和就是答案。

注：关于边双连通图计数，可以参考 [此题](https://www.luogu.com.cn/problem/P5828)。

设 $g_k$ 为 $k$ 个点的边双连通图数，暴力枚举每个连通分量大小，可以得到：

$$f_k=\frac{1}{k!} \sum_{a_1+\dots+a_k=n}\binom{n}{a_1,\dots,a_k}n^{k-2}\prod_{i=1}^ka_ig_{a_i} $$
这里需要做一下解释的是，若 $k$ 有个连通块，第 $i$ 个的大小为 $a_i$，总共有 $n$ 个点；则连接 $k-1$ 条边成连通图的方案数就是：

$$n^{k-2}\prod_{i=1}^ka_i$$
这个结论在 [[WC2019] 数树](https://www.luogu.com.cn/problem/P5206) 的题解中有较为详细的证明。

$f_k$ 显然是个 EGF 卷积的形式，具体来讲，设：
$$A(x)=n\sum_{k=0}^\infty \frac{k g_k}{k!}$$
就有
$$f_k= n^{-2}n![x^n]\frac{A(x)^k}{k!}$$
代入计算最终答案
$$ans=n^{-2}n![x^n]\sum_{k=0}^{m+1} \frac{A(x)^k}{k!}$$
求后面这个类似于 $\exp$ 形式的东西，可以考虑求导：
$$B(x)= \sum_{k=0}^{m+1} \frac{A(x)^k}{k!}$$
$$B'(x)=A'(x) \sum_{k=0}^{m} \frac{A(x)^k}{k!}$$
$$B'(x) = A'(x)\left(B(x)-\frac{A(x)^{m+1}}{(m+1)!}\right)$$
括号中右面一项可以提前算好，牛顿迭代解微分方程就可以 $\Theta(n \log n)$ 处理（分治 FFT 实现可能更优秀）。

但是求边双连通图的 EGF 目前还没有很快的算法，比较简单的是用大步小步法，可以 $\Theta(n^2)$ 来算，具体见[【模板】多项式复合逆](https://www.luogu.com.cn/problem/P5809)。

最后吐槽一下这个毒瘤模数 $10^9+7$，，

---

## 作者：Register_int (赞：10)

如何评价老师在“基础 dp”练习里面放了这题。

首先割边不好处理，考虑将原图缩边双会得到一棵树，割边数就是树边的数量，即边双数量减一。

然后边双连通分量还是不好算，然而可以发现一个性质：一个无向连通图内至少包含 $1$ 个边双。所以我们可以考虑计算至少有 $k$ 个边双的图的个数，再进行容斥。

首先计算 $n$ 个点的有标号无向连通图个数。还是容斥，从 $n$ 个点的任意无向图中减去不合法的方案。将 $1$ 号点设置为基准点，再从剩下的 $n-1$ 个点中选出 $i$ 个与 $1$ 在同一连通块，得到：

$$g_n=2^{\binom n2}-\sum^n_{i=1}\dbinom{n-1}{i-1}g_i2^{\binom{n-i}2}$$

当然直接使用 $\ln$ 的组合意义也能得到：

$$g_n=[x^n]\ln\left(\sum_i\dfrac{2^{\binom i2}}{i!}x^i\right)$$

接下来计算至少有 $k$ 个边双的图 $f_k$。考虑枚举每个连通块的大小，再将他们组合成一棵树：

$$
\begin{aligned}
f_k&=\dfrac1{k!}\sum_{\sum^k_{i=1}a_i=n}\left(n^{k-2}\prod^k_{i=1}a_i\right)\dbinom{n}{a_1,a_2,\cdots,a_k}\prod^k_{i=1}g_{a_i}\\
&=\dfrac1{n^2k!}\sum_{\sum^k_{i=1}a_i=n}\dbinom{n}{a_1,a_2,\cdots,a_k}\prod^k_{i=1}na_ig_{a_i}\\
&=\dfrac{n!}{n^2k!}[x^n]\left(\sum_i\dfrac{nig_i}{i!}x^i\right)^k\\
\end{aligned}
$$

朴素计算 $O(n^3)$ 或者 $O(n^2\log n)$，可以进行大步小步分块做到 $O(n^2+n\sqrt n\log n)$。

再计算恰好有 $k$ 个边双的图 $h_k$。还是钦定基准点得到：

$$h_k=\sum^n_{i=k}(-1)^{i-k}\dbinom{i-1}{k-1}f_i$$

最终答案为 $\sum^{m+1}_{i=1}h_i$，时间复杂度 $O(n^2+n\sqrt n\log n)$。

# AC 代码

只给出 $O(n^3)$ 的实现。

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int mod = 1e9 + 7;

inline 
ll qpow(ll b, ll p) {
	ll res = 1;
	for (; p; p >>= 1, b = b * b % mod) if (p & 1) res = res * b % mod;
	return res;
}

inline 
void conv(ll *a, ll *b, int n) {
	static ll c[51];
	for (int i = 0; i < n; i++) c[i] = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= i; j++) c[i] = (c[i] + a[j] * b[i - j]) % mod;
	}
	for (int i = 0; i < n; i++) b[i] = c[i];
}

ll fac[51], ifac[51], t[51];

inline 
void init(int n) {
	*fac = 1;
	for (int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % mod;
	ifac[n] = qpow(fac[n], mod - 2);
	for (int i = n; i; i--) ifac[i - 1] = ifac[i] * i % mod;
	t[1] = 1;
	for (int i = 2; i <= n; i++) t[i] = t[i - 1] * 2 % mod;
	for (int i = 2; i <= n; i++) t[i] = t[i] * t[i - 1] % mod;
}

inline 
ll c(int n, int m) {
	return fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}

ll a[51], b[51], f[51], g[51], ans, x;

int n, m;

int main() {
    scanf("%d%d", &n, &m), init(n);
    for (int i = 1; i <= n; i++) {
    	g[i] = t[i];
    	for (int j = 1; j < i; j++) {
    		g[i] = (g[i] - c(i - 1, j - 1) * g[j] % mod * t[i - j] % mod + mod) % mod;
		}
	}
	*b = 1;
	for (int i = 1; i <= n; i++) a[i] = n * g[i] % mod * i % mod * ifac[i] % mod;
	for (int i = 1; i <= n; i++) {
		conv(a, b, n + 1);
		f[i] = b[n] * fac[n] % mod * qpow(n * n, mod - 2) % mod * ifac[i] % mod;
	}
	for (int i = 1; i <= n; i++) {
		g[i] = 0;
		for (int j = i; j <= n; j++) {
			x = c(j - 1, i - 1) * f[j] % mod;
			if (j - i & 1) x = mod - x;
			g[i] = (g[i] + x) % mod;
		}
	}
	for (int i = 1; i <= m + 1 && i <= n; i++) ans = (ans + g[i]) % mod;
	printf("%lld", ans);
}
```

---

## 作者：iostream (赞：10)

### 容斥（二项式反演）

先计算恰好 $k$ 个桥的方案 $h_k$，容斥，可以计算钦定 $k$ 个桥的方案数 $g_k$，那么显然有：

$$h_i=\sum_{j=i}^{n-1} {j\choose i}(-1)^{j-i}g_j$$

计算 $g_j$ 可以直接 DP 一个 $j+1$ 的点的边双树，可以选择 DP 出边双树的划分，具体来说我们考虑每次加入一个 $p$ 个点的连通块，$dp_{i,j}$ 表示前 $i$ 个点选了 $j$ 个块的方案数，转移时乘以一个连通图的系数即可。

再考虑将这些连通块接成一个树，熟悉数树那个题的做法即知道乘以 $n^{t-2} \prod_{i=1}^t sz_i$ 的额外贡献即可（$t$ 是连通块数目），这个只需要将上述 $dp$ 修改一下，加入大小 $p$ 的连通块的时候多带一个 $n\times p$ 系数即可。

直接 DP 可以做到 $O(n^3)$ 的复杂度。

考虑用 EGF 表达这个过程，记 $f_n$ 表示 $n$ 点的无向连通图数目。

$$f(x)=\sum_{i=1}^\infty {f_inix^i\over i!}$$

则我们需要求

$$g_j(x)={f^j(x)\over j!} (1\le j\le m+1)$$

就可以拿多项式来进行优化成 $O(n^2\log n)$（本题并不需要）。

~~所以这个题为啥范围 50 啊~~

---

## 作者：PassName (赞：6)

# P6596 题解

[题目传送门P6596 How Many of Them](https://www.luogu.com.cn/problem/P6596)

## solution
在解决这道题目之前，我需要对算法竞赛进阶指南上的问题指出一下。

这道题本身热度不高，也并非什么经典题，来做这个题的估计都是看完算法竞赛进阶指南来的，但是如果你直接按照算法竞赛进阶指南上的转移方程写会寄掉。对于关于 $G[i,j,k]$ 的转移方程书上是有误的。在这里会写出正确的转移方程以及此题解题过程。

在无向图中，不含割边的**极大连通子图**就是**双连通分量**，若将所有双连通分量进行缩点处理，那么所有的双连通分量和割边会构成一个树形结构。

设 $f[i][j]$ 表示 $i$ 个点构成的包含 $j$ 条割边的无向连通图数量。

对于计数类动态规划问题要围绕一个基准点来构造一个整体，由于本题所有节点都存在编号，因此以编号为 $1$ 的节点为**基准点**，枚举 $1$ 号节点所在的双连通分量的大小 $k$，从 $2 \sim i$ 这 $i - 1$ 个节点中选出 $k - 1$ 个，与 $1$ 号点共同构成双连通分量，方案数为 $f[k][0] * C_{i-1}^{k-1}$ 。

如果去掉 $1$ 号点所在的双连通分量，那么无向图会分成若干个连通块，从每个连通块出发，都有一条边连接到 $1$ 号点所在的双连通分量上。
设 $g[i][j][k]$ 表示 $i$ 个点构成的、包含 $j$ 条割边的、有 $k$ 个连通块的无向图数量

考虑计算 $f[i][j]$，去掉 $1$ 号节点所在的双连通分量后，图中剩余部分的方案数就是 $g[i - k][j - x][x]$，其中 $x$ 表示图中剩余部分分为 $x$ 个连通块。每个连通块与 $1$ 号节点所在的双连通分量之间的边都是一条割边，所以剩余部分还需要贡献 $j-x$ 条割边。因为 $1$ 号节点所在的双连通分量包含 $k$ 个节点，每个连通块可以连接到这 $k$ 个节点中的任意一个上，所以连接方案有 $k^x$ 种。$f[i][j] (0 < j < i)$ 状态转移方程为

$$f[i][j]=\sum_{k=1}^{i-1}(f[k][0] * C_{i-1}^{k-1}*\sum_{x=1}^{j}G[i-k][j-x][x] * k^x)$$

起始状态是 $f[i][0]$，即 $i$ 个节点构成的不包含割边的无向连通图数量，求出 $i$ 个节点构成的无向连通图数量，再减去用 $i$ 个节点构成的包含 $1 \sim i-1$ 条边的连通图数量，就是不包含割边的连通图数量。设 $h[i]$ 表示 $i$ 个节点的无向连通图数量。

求出 $i$ 个节点构成的无向图总数，再减去 $i$ 个节点构成的不连通图的数量，就是连通图的数量。$i$ 个节点构成的无向图总数为 $2^{i*(i-1)/2}$，还需统计 $i$ 个节点构成的不连通图的数量，枚举编号为 $1$ 的节点所在的连通图包含的节点个数 $k$，从 $2\sim i$ 这 $i-1$ 个节点中选出 $k-1$ 个节点，和 $1$ 号点一起构成大小为 $i$ 的连通块，显然有 $C_{i-1}^{k-1}$ 种选法，剩余 $i-k$ 个节点构成任意无向图，有 $2^{(i-k)*(i-k-1)/2}$ 种方法。$h[i]$ 的状态转移方程为

$$h[i]=2^{i*(i-1)/2}-\sum_{j=1}^{i-1}h[j]*C_{i-1}^{j-1}*2^{(i-j)*(i-j-1)/2}$$

那么，$f[i][0]$ 为

$$f[i][0] = h[i] - \sum_{j=1}^{i-1} f[i][j]$$

考虑计算 $g[i][j][k]$，已编号最小的系欸但所在的连通块为基准，枚举该连通块的大小 $p$ 和 割边数量 $q$，需要从 $i-1$ 个节点中再选出 $p-1$ 个节点构成这个连通块，所以该连通块的方案就有 $f[p][q] * C_{i-1}^{p-1}$ 种。从该连通块中选出一个节点，用于与刚才去掉的 $1$ 号节点所在的双连通分量相连，显然有 $p$ 种选法，图中其他部分的方案数就是 $g[i-p][j-q][k-1]$。注意，算法竞赛进阶指南的的转移方程第二个求和是有问题的，这里得到转移方程为

$$g[i][j][k] = \sum_{p=1}^{i} \sum_{q = 0}^{j} f[p][q] * C_{i-1}^{p-1} * p * g[i-p][j-q][k-1]$$

这里算出的 $g[i][j][k]$ 与刚才的定义稍有差别，每个连通块多乘了一个 $p$，用于与计算 $f[i][j]$ 时去掉的 $1$ 号点所在的双连通分量相连，如果抛开本题，计算 $i$ 个点构成的、包含 $j$ 条割边的、有 $k$ 个连通块的无向图数量，则不需要乘 $p$。

由于 $n$ 个点的无向图最多只有 $n-1$ 条割边，并且我们要求的是割边不超过 $m$ 条的无向连通图数量，所以当 $m \geq n$ 时，我们需要令 $m = n-1$，再进行计算。

## code
```cpp
#include <bits/stdc++.h>

#define rint register int
#define int long long
#define endl '\n'

using namespace std;

const int N = 5e1 + 5;
const int M = N * N;
const int mod = 1e9 + 7;

int n, m;
int f[N][N]; 
//f[i][j] 表示 i 个节点构成的包含 j 条割边的无向连通图数量
int g[N][N][N]; 
//g[i][j][k] 表示 i 个节点构成的、包含 j 条割边的、有 k 个连通块构成的无向图数量
int h[N]; 
//h[i] 表示 i 个节点的无向连通图数量
int c[N][N]; 
//组合数预处理，范围较小
int pow2[M]; //pow2[i] 表示 2 的 i 次方

signed main()
{
    cin >> n >> m;
    if (m >= n) m = n - 1;
    //预处理 c[][]
    for (rint i = 0; i <= n; i++) c[i][0] = 1;
    for (rint i = 1; i <= n; i++)
        for (rint j = 1; j <= i; j++)
            c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % mod;
    //预处理 pow2[]
    pow2[0] = 1;
    for (rint i = 1; i <= n * (n - 1) / 2; i++) 
	{
		pow2[i] = pow2[i - 1] * 2 % mod;
	}
    g[0][0][0] = 1;
    for (rint i = 1; i <= n; i++)
    {
        h[i] = pow2[i * (i - 1) / 2];
        for (rint j = 1; j < i; j++)
        {
            h[i] = (h[i] - h[j] * c[i - 1][j - 1] % mod * pow2[(i - j) * (i - j - 1) / 2] % mod) % mod; 			
		}
        f[i][0] = h[i];
        for (rint j = 1; j < i; j++)
        {
            for (rint k = 1; k < i; k++)
            {
                int k_x = 1; //记录 k 的 x 次方
                for (rint x = 1; x <= j; x++)
                {
                    k_x = k_x * k % mod;
                    f[i][j] = (f[i][j] + f[k][0] * c[i - 1][k - 1] % mod * g[i - k][j - x][x] % mod * k_x % mod) % mod; 
                }
            }
            f[i][0] = (f[i][0] - f[i][j]) % mod;
        }

        for (rint j = 0; j < i; j++)
          for (rint p = 1; p <= i; p++)
            for (rint q = 0; q <= j; q++)
              for (rint k = 1; k <= i; k++)
                g[i][j][k] = (g[i][j][k] + f[p][q] * c[i - 1][p - 1] % mod * p % mod * g[i - p][j - q][k - 1] % mod) % mod; 						

    }

    int res = 0; 
    for (rint i = 0; i <= m; i++) res = (res + f[n][i]) % mod; 
    cout << (res + mod) % mod << endl; 

    return 0;
}
```

---

## 作者：spider_oyster (赞：5)

蓝书讲的很清晰但不是很清晰，所以我只能勉强看懂。

在无向图中，不含割边的极大联通子图称为双连通分量。若把每个双联通分量看为节点，则所有双连通分量和割边构成一棵树的形状。如下图，每个框框是个双连通分量。

![](https://cdn.luogu.com.cn/upload/image_hosting/let5d21f.png)

于是设 $f_{i,j}$ 表示 $i$ 个节点构成的包含 $j$  条割边的无向连通图数量。先考虑 $j>0$ 的情况：

看下面这张图：

![](https://cdn.luogu.com.cn/upload/image_hosting/hxexkknu.png)

如果删除一个双连通分量，图就会变成若干个连通块（上图蓝圈圈出了的两个联通块），从每个连通块出发，有一条边连向删除的双连通分量。

于是可以枚举删除的双连通分量大小，假设为 $k$。然后以 $1$ 号节点为基准点，再从 $i-1$ 个点中选 $k-1$。点选完了，然后大小为 $k$ 的双连通分量有 $f_{k,0}$ 种形态，故方案数为 $f_{k,0}\times C_{i-1}^{k-1}$。

> - 思考为什么要设基准点（为什么不是直接在 $i$ 个点中选 $k$ 个）。这是计数 dp 中的一类思想。如果能围绕这个基准点能构造一个整体，且不重不漏，那么这么做就是对的。
>
>- 以 $1$ 号节点为基准点，删除其所在的双连通分量构造图的方式，肯定能构造出所有情况。每次删除的双连通分量是特定的，这样就不会重复。
>
>- ~~编不下去了，先鸽这~~。感性理解一下（或者画图思考一下）。

设 $g_{i,j,k}$ 表示 $i$ 个节点构成的，有 $j$ 个连通块的，有 $k$ 条割边的无向图数量。

先抛式子：

$f_{i,j}=\sum\limits_{k=1}^{i-1}(f_{k,0}\times C_{i-1}^{k-1}\times \sum\limits_{p=1}^{min(i-k,j)}g_{i-k,p,j-p}\times k^p)$。

>- 外面连通块数量 $p$ 是未知的，故需要枚举。最极限就是每个节点是一个连通块，故向 $i-k$ 取 $\min$。

>- 每个连通块向大小为 $k$ 的双连通分量连边，会产生 $p$ 条割边，所以 $g$ 里割边数量是 $j-p$。

>- 连的 $p$ 条割边每条都能连双连通分量里 $k$ 个点中任意一个，有 $k^p$ 种连法（魔法少女 XD 跟我在这吵了半小时，这里给个图理解。注意相同颜色的边其实是一条边，这里只是把连法全部画出来了）。

>![](https://cdn.luogu.com.cn/upload/image_hosting/dl37927q.png)

>- 先抛出一个问题，这里没有考虑每个连通块内部是哪个节点与双连通分量里的点连的。

对于 $j=0$ 的情况，设 $h_{i}$ 表示 $i$ 个节点的无向连通图数量，则状态转移方程为：

$f_{i,0}=h_{i}-\sum\limits_{j=1}^{i-1}f_{i,j}$。很好理解，不解释了。

>- 关于 $h_{i}$ 的求法，其实就是[这道题](http://poj.org/problem?id=1737)。

>- 用 $i$ 个节点构成的无向图数量减去非连通的无向图数量即可。

>- $h_{i}=2^{i\times (i-1)/2}-\sum\limits_{j=1}^{i=1}h_{j}\times C_{i-1}^{j-1}\times 2^{(i-j)\times (i-j-1)/2}$。

>- $i$ 个节点构成的无向图至多有 $i\times (i-1)/2$ 条边，每条可有可无，故有 $2^{i\times (i-1)/2}$ 种。

>- 一个非连通图可以由多个连通块组成。还是以 $1$ 号节点为基准枚举其所在的连通块大小为 $j$，类比上面分析双连通分量，共 $h_{j}\times C_{i-1}^{j-1}$ 种。

>- 剩下的 $i-j$ 个点构成任意无向图。

最后考虑 $g$ 的计算方法。

注意双连通分量我们已经以 $1$ 为基准了，这里便以编号最小的节点所在的连通块为基准。显然要枚举这个连通块的大小 $p$ 和割边数 $q$。构成这个连通块有 $f_{p,q}\times C_{i-1}^{p-1}$ 种。

回到刚刚抛出的问题，这个连通块里选一个节点与删除的双连通分量相连（算 $f$ 时未考虑到的，因为当时不知道具体每个连通块大小），共有 $p$ 种。

式子：

$g_{i,j,k}=\sum\limits_{p=1}^{i}\sum\limits_{q=0}^{k} f_{p,q}\times C_{i-1}^{p-1}\times p\times g_{i-p,j-1,k-q}$。

然后这道题就做完了。

关于顺序，先算出 $h$，再以 $i$ 为阶段，分别求解 $f$ 和 $g$。观察下标，可以发现这么做是对的。

初值：$g_{0,0,0}=1$，取模勤一点，不然会爆。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int N=51,M=N*(N-1)/2,P=1e9+7;
int n,m;
int C[N][N],f[N][M],g[N][N][M],h[N];

inline int qpow(int a,int b)
{
    int res=1;
    for(;b;b>>=1,a=1ll*a*a%P)
        if(b&1) res=1ll*res*a%P;
    return res;
}

int main()
{
    cin>>n>>m;
    for(int i=0;i<=n;i++)//注意要从 0 开始
    {
        C[i][0]=C[i][i]=1;
        for(int j=1;j<i;j++)
            C[i][j]=(C[i-1][j]+C[i-1][j-1])%P;
    }
    for(int i=1;i<=n;i++)
    {
        h[i]=qpow(2,i*(i-1)/2);
        for(int j=1;j<i;j++)
            h[i]=(h[i]-1ll*h[j]*C[i-1][j-1]%P*qpow(2,(i-j)*(i-j-1)/2)%P+P)%P;
    }
    g[0][0][0]=1;
    for(int i=1;i<=n;i++)
    {
        ll s1=0;
        for(int j=1;j<i;j++)
        {
            for(int k=1;k<i;k++)
            {
                int s2=0;
                for(int p=1;p<=min(i-k,j);p++)
                    s2=(s2+1ll*g[i-k][p][j-p]*qpow(k,p)%P)%P;
                f[i][j]=(f[i][j]+1ll*f[k][0]*C[i-1][k-1]%P*s2)%P;    
            }
            s1=(s1+f[i][j])%P;
        }
        f[i][0]=(h[i]-s1+P)%P;
        for(int j=1;j<=i;j++)
            for(int k=0;k<i;k++)
                for(int p=1;p<=i;p++)
                    for(int q=0;q<=k;q++)
                        g[i][j][k]=(g[i][j][k]+1ll*f[p][q]*C[i-1][p-1]%P*p%P*g[i-p][j-1][k-q])%P;
    }
    ll ans=0;
    for(int i=0;i<=min(n,m);i++) ans=(ans+f[n][i])%P;
    cout<<ans;
}
```


---

## 作者：seajupiter (赞：5)

似乎大佬们都用多项式轻松切掉了~~还懒得放代码~~，这里讲一个稍微“亲切”一点的纯dp方法吧。

**算法：大力计数dp**

先讲一下这个问题：求 $n$ 个点的有标号无向连通图数量。

一般计数dp，为了做到方案计算不重不漏，**往往选择一个“基准点”，并“围绕基准点构造一个整体”**（出自李煜东的《算法竞赛进阶指南》），我们会看到，**下面将以此思想为核心做出整个dp过程**。

首先，直接算连通图似乎不太好从更小的状态转移得来，而非连通图的不同连通块就是天然的状态划分，我们考虑**补集转化**，用总方案数减去非连通图方案数。总方案数很简单，所有的边都可以选择选或者不选，那么方案数就是$2^{\frac{i*(i-1)}{2}}$ 。接下来考虑如何计算非连通图方案数。

那么这个问题的“基准点”是什么呢？有一个很简单的想法，就是取1号点，构造的整体就是1号点所在连通块，那么枚举一号点所在连通块大小，配合组合数，设 $i$ 个点的无向连通图个数为 $h_i$ ，我们可以轻松得到一下状态转移：

$h_i=2^{\frac{i*(i-1)}{2}}-\sum\limits_{j=1}^{i-1}h_j* C_{i-1}^{j-1}* 2^{\frac{(i-j)* (i-j-1)}{2}}$

于是就解决了。

再回到这道题，我们设 $f_{i, j}$ 表示 **$i$ 个点，$j$ 条割边的连通图个数** ，同样选择1号点作为基准点，构造的整体就是1号点所在的边双连通分量，就可以想象把这个双连通分量删掉，然后计算剩余部分若干个连通块的解。

为了方便计算剩余部分，我们再设 $g_{i, j, k}$ 表示 **$i$ 个点，$j$ 个连通块，$k$ 条割边的无向图数量** ，于是

对于 $j>0$ ，有

$f_{i, j}=\sum\limits_{k=1}^{i-1}(f_{k, 0}* C_{i-1}^{k-1}* \sum\limits_{x=1}^{\min(i-k, j)}g_{i-k, x, j-x}* k^x$

这里乘上 $k^x$ 的原因是每个连通块要选择一个点接到1所在的边双连通分量里头去。

另外，有

$f_{i, 0}=h_i-\sum\limits_{j=1}^{i-1}f_{i, j}$

这个很好理解，总连通图数减去所有有割边的连通图数。

再写出 $g$ 的状态转移，选择标号最小的那个点作为基准点，其所在连通块作为构造的整体，枚举连通块大小 $p$ 和割边数量 $q$，可以轻松得到：

$g_{i, j, k}=\sum\limits_{p=1}^{i}\sum\limits_{q=0}^{k}f_{p, q}* C_{i-1}^{p-1}* g_{i-p, j-1, k-q}$


好啦，我们就做完啦？

**不对，还有错误！**

**我们在计算 $f$ 时，虽然考虑了剩下的连通块连向哪些点，但没有考虑他们是从哪一个点连过来的！**

怎么办呢？很好解决，只需要在计算 $g$ 的时候考虑一下就好。很显然，当前连通块的 $p$ 个点都可以用来连向1所在边双连通分量，那么改成：

$g_{i, j, k}=\sum\limits_{p=1}^{i}\sum\limits_{q=0}^{k}f_{p, q}* C_{i-1}^{p-1}* p* g_{i-p, j-1, k-q}$

这道题就做完啦！

注意边界：

$h_1=1$

$f_{0, 0}=1$

$g_{0, 0, 0}=1$

若 $i>j$ 或者是 $i\neq0$ 且 $j=0$ ，则 $g_{i, j, k}=0$

答案： $\sum\limits_{i=0}^{m}f_{n, i}$

在dp的时候我们发现不是特别好把 $f$ 和 $g$ 同时dp，所以可以采用 **$f$ 循环递推，$g$ 记忆化搜索。**

时间复杂度？大概 $O(n^5)$ ，不过跑不满，所以不开 O2 也可以轻松过……（回答其他多项式大佬的问题，这个数据范围就是专门为我们这种蒟蒻准备的……）

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N=55;
const ll mod=1e9+7;

int n, m;

inline ll fp(ll a, ll b){
	ll tot=1;
	for(; b; a=a*a%mod, b>>=1) if(b&1)
		tot=tot*a%mod;
	return tot;
}

ll fac[N], ifac[N], h[N], f[N][N], g[N][N][N], ans;

inline ll C(int n, int m){
	if(n<m) return 0;
	return fac[n]*ifac[m]%mod*ifac[n-m]%mod;
}

inline ll G(int i, int j, int k){
	if(g[i][j][k]!=-1) return g[i][j][k];
	if(j>i||(i&&!j)) return 0;
	ll ans=0;
	for(int p=1; p<=i; ++p)
		for(int q=0; q<=k; ++q)
			ans=(ans+f[p][q]*C(i-1, p-1)%mod*p%mod*G(i-p, j-1, k-q))%mod;
	return (g[i][j][k]=ans);
}

int main(){
	scanf("%d%d", &n, &m);

	fac[0]=ifac[0]=1;
	for(int i=1; i<=n; ++i)
		fac[i]=fac[i-1]*i%mod;
	ifac[n]=fp(fac[n], mod-2);
	for(int i=n-1; i; --i)
		ifac[i]=ifac[i+1]*(i+1)%mod;

	h[1]=1;
	for(int i=2; i<=n; ++i){
		h[i]=fp(2, i*(i-1)/2);
		for(int j=1; j<=i-1; ++j)
			h[i]=(h[i]+mod-h[j]*C(i-1, j-1)%mod*fp(2, (i-j)*(i-j-1)/2)%mod)%mod;
	}
	
	memset(g, 0xff, sizeof(g));
	f[0][0]=g[0][0][0]=1;
	for(int i=1; i<=n; ++i){
		for(int j=1; j<=i-1; ++j)
			for(int k=1; k<=i-1; ++k){
				ll tmp=0;
				for(int x=1; x<=i-k&&x<=j; ++x)
					tmp=(tmp+G(i-k, x, j-x)*fp(k, x)%mod)%mod;
				f[i][j]=(f[i][j]+f[k][0]*C(i-1, k-1)%mod*tmp%mod)%mod;
			}
		f[i][0]=h[i];
		for(int j=1; j<=i-1; ++j)
			f[i][0]=(f[i][0]+mod-f[i][j])%mod;
	}

	for(int i=0; i<=n-1&&i<=m; ++i)
		ans=(ans+f[n][i])%mod;
	
	printf("%lld\n", ans);

	return 0;
}
```


















---

## 作者：D2T1 (赞：3)

[luogu link](https://www.luogu.com.cn/problem/P6596)

部分表述来源于李煜东的《算法竞赛进阶指南》。

## 题意
求满足如下条件的无向连通图数量：

1. 由 $n$ 个节点组成，每个节点有编号，编号为 $1\sim n$;
2. 割边数量 $\leq m$ 条；
3. 无自环，无重边。

数据范围 $2\leq n\leq50,0\leq m\leq \frac{n*(n-1)}2$，输出答案对 $10^9+7$ 取模的值。

## 题解
首先有个结论：

> 在无向图中，不含割边的极大连通子图称为**双连通分量**。若把每个双连通分量看做一个节点，则所有双连通分量和割边构成一棵树。

很容易理解：如果最后不构成树（有环），则环上的所有双连通分量必定能构成一个更大的双连通分量。

------

设 **$f_{i,j}$ 表示 $i$ 个点包含 $j$ 条割边的无向连通图数量**。首先考虑 $j>0$（下面解释为什么）。

计数 dp 有个思想：“围绕基准点构造一个整体”。我们以编号为 $1$ 的节点为“基准点”，枚举 $1$ 所在双连通分量节点数 $k$。这个双连通方案的构造方案数为 $f_{k,0}*\binom{i-1}{k-1}$（$i-1$ 个节点选 $k-1$ 个与 $1$ 构成大小为 $k$ 的双连通分量）。

如果 $j=0$，那么 $k$ 只能取 $i$ 按照上式，$f_{i,j}=f_{k,0}*\binom{i-1}{k-1}$，我等于我自己了。

现在不考虑 $j=0$，考虑图中其他部分。去掉 $1$ 号节点所在的双连通分量，无向图会分成若干连通块，从每个连通块出发都有一条边连接到 $1$ 号点所在的双连通分量上（这条边即为割边）。

设 **$g_{i,j,k}$ 表示 $i$ 个点包含 $j$ 条割边的有 $k$ 个连通块的“有根”无向图数量**，其中的“根”即为与 $1$ 号点所在的双连通分量连边的那个节点。在此处处理更加简便。则去掉 $1$ 号点所在的双连通分量后，图中剩余部分方案数为 $g_{i-k, j-x,x}$，其中 $x$ 表示剩余连通块个数。因为 $1$ 号点所在的双连通分量有 $k$ 个节点，所以 $x$ 个连通块连接上去，共有 $k^x$ 中方案。

综上，$f_{i,j}(0<j<i)$ 的转移方程：

$$f_{i,j} = \sum\limits_{k=1}^{i-1}  \left(f_{k,0}* \dbinom{i-1}{k-1}*\sum_{x=1}^{\min(i-k,j)}\left(g_{i-k,j-x,x}* k^x\right)\right)$$

设 $h_i$ 表示 $i$ 个节点的无向连通图数量，则 $f_{i,0}=h_i-\sum\limits_{j=1}^{i-1}f_{i,j}$。

现在考虑 $h_i,g_{i,j,k}$ 怎么求。

------

首先是 $h_i$：

求连通图个数不好求，考虑求不连通图个数。则 $dp_i=all_i-notConnected_i$。

$i$ 个节点的无向图有 $\binom i2$ 条边，每条边可连可不连，所以 $all_i=2^{\binom i2}$。现在来考虑 $notConnected_i$。枚举节点 $1$ 所在连通块大小 $j\in[1,i)$，对于每个 $j$，节点 $1$ 所在连通块的节点选择数有 $\binom{i-1}{j-1}$ 种（从 $1$ 以外 $i-1$ 个节点中取 $j-1$ 个与 $1$ 在同一个连通块里），而具体边怎么连呢？已经有了答案：$dp_j$。剩下的 $i-j$ 个节点怎么连都行了，答案为 $all_{i-j}$。所以能够得出方程：

$$h_i=2^{\binom i2}-\sum\limits_{j=1}^{i-1}\dbinom{i-1}{j-1}* h_j*2^{\binom{i-j}2}$$

------

$g_{i,j,k}$（$i$ 个点包含 $j$ 条割边的有 $k$ 个连通块的“有根”无向图数量）：

以编号最小的节点所在连通块为基准，枚举该连通块大小 $p$，割边数量 $q$。该连通块的方案有 $f_{p,q}* \binom{i-1}{p-1}$ 种；选连通块中的“根”，有 $p$ 中选法；其它部分的方案数是 $g_{i-p,j-q,k-1}$。得到方程：

$$g_{i,j,k}=\sum\limits_{p=1}^i\sum_{q=0}^{j^*}f_{p,q}* \dbinom{i-1}{p-1}* p* g_{i-p,j-q,k-1}$$

$^*$：这里应该是 $j$，但蓝书写成了 $k$。

------

接下来就是代码细节了。我们可以首先枚举 $i$，接着按 $h_i,f_{i,j(j>0)},f_{i,0},g_{i,j,k}$ 的顺序计算，可以保证每个状态都恰好更新到。

然后就是一些边界问题：

$f_{i,j(j>0)}$ 中的 $j$ 的范围当然是 $(0,i)$，$g_{i,j,k}$ 中的 $j,k$ 呢？$j$ 是割边数，自然不可能取到 $i$，范围 $[0,i)$；$k$ 是连通块个数，不可能是 $0$，范围 $[1,i]$。还要注意一个初始化：$g_{0,0,0} = 1$。这个应该很容易想到，因为如果没有初始化那么算出来的所有 $g$ 都是 $0$，于是套路地初始化 $g_{0,0,0}$。

## 代码

```cpp
//acwing308
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 60; const ll P = 1e9 + 7;
ll A[N], invA[N], h[N], f[N][N], g[N][N][N], ans;
int n, m;

ll qp(ll a, ll b){ ll r=1; while(b){ if(b&1) r=r*a%P; a=a*a%P; b>>=1; } return r; }
ll C(int n, int m){ return A[n] * invA[m] % P * invA[n-m] % P; }

int main(){
	scanf("%d%d", &n, &m); if(m > n) m = n;
	A[0] = 1, invA[0] = 1, g[0][0][0] = 1;
	for(int i = 1; i <= n; ++ i) A[i] = A[i-1] * i % P, invA[i] = qp(A[i], P-2);
	for(int i = 1; i <= n; ++ i){
		h[i] = qp(2, C(i, 2));
		for(int j = 1; j < i; ++ j)
			h[i] = (h[i] - h[j] * C(i-1, j-1) % P * qp(2, C(i-j, 2)) % P + P) % P;
		for(int j = 1; j < i; ++ j)
			for(int k = 1; k < i; ++ k){
				ll tmp = 0;
				for(int x = 1; x <= min(i-k, j); ++ x)
					tmp = (tmp + g[i-k][j-x][x] * qp(k, x) % P) % P;
				f[i][j] = (f[i][j] + f[k][0] * C(i-1, k-1) % P * tmp % P) % P; 
			}
		f[i][0] = h[i];
		for(int j = 1; j < i; ++ j) f[i][0] = (f[i][0] - f[i][j] + P) % P;
		for(int j = 0; j < i; ++ j)
			for(int k = 1; k <= i; ++ k)
				for(int p = 1; p <= i; ++ p)
					for(int q = 0; q <= j; ++ q)
						g[i][j][k] = (g[i][j][k] + f[p][q] * C(i-1, p-1) % P * p % P * g[i-p][j-q][k-1] % P) % P;
	}
	for(int i = 0; i <= m; ++ i) ans = (ans + f[n][i]) % P;
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：Umbrella_Leaf (赞：2)

### 题意

> 定义“割边”：若一个无向图删去一条边后无向图的连通块个数增加，则称这条边为割边。
>
> 求有 $n$ 个点、不超过 $m$ 条割边、节点有标号的简单无向连通图的个数。$n,m\le 50$。

### 分析

> 定义：不存在割边的极大联通子图称为边双连通分量。

显然应该用计数 DP 做。我们设 $f_{i,j}$ 表示有 $i$ 个点，$j$ 条割边、节点有标号的简单无向连通图的个数。

考虑如何转移。首先，考虑 $j>0$ 的情况。

我们枚举 $1$ 号节点所在的边双连通分量的大小 $k$。

那么，组成这个边双连通分量的方案数，就等于 $f_{k,0}\times C_{i-1}^{k-1}$，其中 $C_n^m$ 是组合数。这个式子很好理解：边双连通分量内部是没有割边的，因此从除了 $1$ 号点之外的 $i-1$ 个点中选出 $k-1$ 个点，再组成这个边双连通分量即可。

其他的部分呢？不妨假设删去 $1$ 号节点所在的边双连通分量后还剩下 $p$ 个连通块。这里的方案数为 $g_{i-k.p,j-p}\times k^p$，其中 $g_{i,j,k}$ 表示有 $i$ 个点，$j$ 个连通块、$k$ 条割边、节点有标号的简单无向图的个数。理解起来也很简单：先选择剩下 $i-k$ 个点构成的图，然后把每个连通块向 $1$ 号点所在的边双连通分量 $k$ 个点中的某一个连边。

因此，我们有

$$f_{i,j}=\sum_{1\le k<i}f_{k,0}\times C_{i-1}^{k-1}\times \sum_{1\le p\le \min(i-k,j)}g_{i-k,p,j-p}\times k^p$$

对于 $j=0$ 的情况呢？我们只需要求出 $i$ 个点的有标号简单无向连通图个数 $h_i$，则

$$f_{i,0}=h_i-\sum_{1\le j<i}f_{i,j}$$

应该很易懂，不需要解释。

那么 $h_i$ 如何求呢？我们采用容斥，从所有的无向图中减去不连通的无向图个数。

$$h_i=2^{\frac{i(i-1)}{2}}-\sum_{1\le j<i}h_j\times C_{i-1}^{j-1}\times 2^{\frac{(i-j)(i-j-1)}{2}}$$

后半部分是枚举第 $1$ 个点所在的连通块大小。应该也不需要解释。

最后是 $g_{i,j,k}$。我们枚举 $1$ 号点所在的连通块大小 $p$ 和割边数量 $q$，由于要选出 $p-1$ 个点组成连通块，因此方案数是 $f_{p,q}\times C_{i-1}^{p-1}$。当然，我们还需要从这个连通块中选出一个点与刚才被删掉的那个双连通分量连起来，方案数是 $p$。剩下的 $j-1$ 个连通块方案数是 $g_{i-p,j-1,k-q}$。所以

$$g_{i,j,k}=\sum_{p=1}^i\sum_{q=0}^kf_{p,q}\times c_{i-1}^{p-1}\times p\times g_{i-p,j-1,k-q}$$

最后是边界情况。显然，当全图只有 $0$ 个点（没有点）时，连通块数和割边数都是 $0$。因此初值是 $g_{0,0,0}=1$ ，其余为 $0$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll mod=1e9+7;
int n,m;
ll fac[55],inv[55];
ll f[55][55],g[55][55][55],h[55];
ll power(ll a,int p){
	ll res=1;
	while(p){
		if(p&1)res=res*a%mod;
		p>>=1;
		a=a*a%mod;
	}
	return res;
}
ll C(int n,int m){
	if(m<0||n<m||n<0)return 0;
	return fac[n]*inv[m]%mod*inv[n-m]%mod;
}
int main(){
	fac[0]=1;
	for(int i=1;i<=50;i++)fac[i]=fac[i-1]*i%mod;
	inv[50]=power(fac[50],mod-2);
	for(int i=49;i>=0;i--)inv[i]=inv[i+1]*(i+1)%mod;
	scanf("%d%d",&n,&m);
	h[1]=1;
	for(int i=2;i<=n;i++){
		h[i]=power(2,i*(i-1)/2);
		for(int j=1;j<i;j++)h[i]=(h[i]-h[j]*C(i-1,j-1)%mod*power(2,(i-j)*(i-j-1)/2)%mod+mod)%mod;
	}
	g[0][0][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<i;j++)
			for(int k=1;k<i;k++){
				ll sum=0;
				for(int p=1;p<=min(i-k,j);p++)sum=(sum+g[i-k][p][j-p]*power(k,p)%mod)%mod;
				f[i][j]=(f[i][j]+f[k][0]*C(i-1,k-1)%mod*sum%mod)%mod;
			}
		f[i][0]=h[i];
		for(int j=1;j<i;j++)f[i][0]=(f[i][0]-f[i][j]+mod)%mod;
		for(int j=1;j<=i;j++)
			for(int k=0;k<i;k++){
				for(int p=1;p<=i;p++)
					for(int q=0;q<=k;q++)
						g[i][j][k]=(g[i][j][k]+f[p][q]*C(i-1,p-1)%mod*p%mod*g[i-p][j-1][k-q]%mod)%mod;
			}
	}
	ll ans=0;
	for(int i=0;i<=min(m,n);i++)ans=(ans+f[n][i])%mod;
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：AC_Lover (赞：1)

### 图相关计数

**基本思路：** 以点数、边数为划分阶段，围绕一个整体（通常提出$1$号点考虑）

0. **图计数：** 求 $n$ 个点的（有标号）无向图的个数。

   在那里摆了 $n$ 个点，只需要确定边，总共有 $\frac{n(n-1)}{2}$ 条边，每条边可以连/不连，于是总个数为 $2^{\frac{n(n-1)}{2}}$，我们记 $G_n=2^{\frac{n(n-1)}{2}}$。

1. **连通图计数：** 求 $n$ 个点的（有标号）无向连通图的个数。

这很典，直接定义 $F_i$ 表示 $i$ 个点的无向连通图个数。

直接算连通图的个数不好算，于是考虑使用容斥，即 连通图个数 $=$ 总个数 $-$ 非连通图个数。

总个数就是 $G_i$，考虑如何求出非连通图的个数。

非连通图是由多个连通块构成，根据基本思路，我们可以考虑 $1$ 号点位于的连通块，假设 $1$ 号点所在的连通块大小为 $j$，那么这个连通块的个数就是 $F_j$，我们要从除了 $1$ 以外的 $i-1$ 个点中选择 $j-1$ 个点，由于是有标号的，所以方案数是 $\binom{i-1}{j-1}$，于是我们将 $1$ 所在的连通块与其他的点分离开了，于是对于剩下的 $(i-j)$ 个点，随便怎么组成整个图都是非联通的，那么剩下的点总共就有 $G_{i-j}$ 种，于是总数为 $\binom{i-1}{j-1}F_jG_{i-j}$。于是我们枚举 $j$ 进行求和就可以得到所有非连通图的个数了，所以有
$$
F_i=G_i-\sum_{j=1}^{i-1}\left[\binom{i-1}{j-1}F_jG_{i-j}\right]
$$

2. **连通图+割边计数：** 求 $n$ 个点，$m$ 条割边的（有标号）无向连通图的个数。

有了割边的限制，于是把这个也放进状态中，定义 $f_{i,j}$ 表示 $i$ 个点，$j$ 条割边的无向连通图个数，可以发现此时有  $j<i$

考虑割边的性质，割边就是连接了两个边双，根据基本思路，我们还是考虑 $1$ 点所在的边双，假设其大小为 $k$，那么有 $\binom{i-1}{k-1}$ 种方法来选择，并且可以发现 $k$ 个点的边双个数相当于割边数量等于 $0$，方案为 $f_{k,0}$，所以这一部分方案数为 $\binom{i-1}{k-1}f_{k,0}$，下面研究一下剩余部分。

假设我们删去了 $1$ 号点所在的边双，那么剩余的图会变成一个个边双组成的连通块，假设这些连通块有 $x$ 个，根据边双的极大性，每个连通块都与 $1$ 号点所在的边双连接了恰好一条边，于是相当于贡献了 $x$ 条割边，总共需要 $j$ 条割边，所以还要 $(j-x)$ 条割边。

我们发现涉及到了连通块的个数，于是再定义一个 $g_{i,j,k}$，表示 $i$ 个点、$j$ 个连通块、$k$ 条割边的无向图个数。此时剩余部分中有 $i-k$ 个点，$x$ 个连通块，还需要 $(j-x)$ 条割边，对应 $g_{i-k,x,j-x}$。然后分出来的 $x$ 个连通块每个都要与 $1$ 所在的边双中的 $k$ 个点中的一个相连，总连接方案数为 $k^x$，此处我们暂不考虑割出去的连通块中选择哪个点来相连，所以剩余部分的方案数为
$$
\sum_{x=1}^{\min(i-k,j)}\left(g_{i-k,x,j-x}\times k^x\right)
$$
综上可以得到转移方程：
$$
f_{i,j}=\sum_{k=1}^{i-1}\left\{\binom{i-1}{k-1}f_{k,0}\left[\sum_{x=1}^{\min(i-k,j)}(g_{i-k,x,j-x}\times k^x)\right]\right\}
$$
考虑 $f_{i,0}$ 怎么求，还是用容斥，没有割边 $=$ 总个数 $-$ 有割边，所以
$$
f_{i,0}=F_i-\sum_{j=1}^{i-1}f_{i,j}
$$
$f$ 解决了，再来看 $g_{i,j,k}$ 如何求。

还是围绕一个整体，这次考虑 $i$ 个点中编号最小的点，假设其所在的连通块大小为 $p$，割边数量为 $q$，选择点方案数为 $\binom{i-1}{p-1}$，$q$ 条割边于是方案数为 $f_{p,q}$，并且由于我们在分析 $f$ 时没有考虑割出去的连通块中选择哪个点来相连，所以要从这个连通块中选择一个点来连接，有 $p$ 种方案，对于剩下的 $i-p$ 个点，$j-1$ 个连通块，$k-q$ 条割边，方案数为 $g_{i-p,j-1,k-q}$，所以
$$
g_{i,j,k}=\sum_{p=1}^{i}\sum_{q=0}^{k}\left[\binom{i-1}{p-1}f_{p,q}\times p\times g_{i-p,j-1,k-q}\right]
$$
然后做完了，总时间复杂度 $O(n^5)$，但远远到不了这个上界。

---

对于此题，答案就是

$$
\sum_{i=0}^{m}f_{n,i}
$$

```c++
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long ll;
const int N=55;
int n,m;
namespace Math
{
	const int mod=1e9+7;
	int C[N][N];
	
	inline int qmi(ll a,int b,int p=mod)
	{
		ll res=1;
		while (b)
		{
			if (b&1) res=res*a%p;
			a=a*a%p;
			b>>=1;
		}
		return res;
	}
	inline int Mod(int x) 
	{
		if (x<0) x+=mod;
		if (x>=mod) x-=mod;
		return x;
	}
	inline void adm(int &x,int y) { x=Mod(x+y); }
	inline void dec(int &x,int y) { x=Mod(x-y); }
	
	void init()
	{
		C[0][0]=1;
		for (int i=1;i<=n;i++)
		{
			for (int j=0;j<=i;j++)
			{
				if (!j) C[i][j]=1;
				else C[i][j]=Mod(C[i-1][j]+C[i-1][j-1]);
			}
		}
	}
}
using namespace Math;

int G[N],F[N];
int f[N][N],g[N][N][N];

int main()
{
	cin >> n >> m;
	m=min(n-1,m);
	
	init();
	
	for (int i=1;i<=n;i++) G[i]=qmi(2,i*(i-1)/2);
	
	for (int i=1;i<=n;i++)
	{
		F[i]=G[i];
		for (int j=1;j<i;j++) dec(F[i],1ll*C[i-1][j-1]*F[j]%mod*G[i-j]%mod);
	}
	
	g[0][0][0]=1;
	for (int i=1;i<=n;i++)
	{
		f[i][0]=F[i];
		for (int j=1;j<i;j++)
		{
			for (int k=1;k<i;k++)
			{
				int s=0;
				for (int x=1;x<=min(i-k,j);x++) adm(s,1ll*g[i-k][x][j-x]*qmi(k,x)%mod);
				adm(f[i][j],1ll*C[i-1][k-1]*f[k][0]%mod*s%mod);
			}
			dec(f[i][0],f[i][j]);
		}
		for (int j=1;j<=i;j++)
		{
			for (int k=0;k<i;k++)
			{
				for (int p=1;p<=i;p++)
				{
					for (int q=0;q<=k;q++)
					{
						adm(g[i][j][k],1ll*C[i-1][p-1]*f[p][q]%mod*p%mod*g[i-p][j-1][k-q]%mod);
					}
				}
			}
		}
	}
	
	int ans=0;
	for (int i=0;i<=m;i++) adm(ans,f[n][i]);
	cout << ans << "\n";
	
	return 0;
}
```

---

## 作者：GY程袁浩 (赞：1)

## 解法

（参考蓝书与部分其它题解以及部分评论）。

首先考虑设计状态 $f_{i,j}$ 表示 $i$ 个点，且共有 $j$ 条割边的无向连通图的数量。

然后接下来我们需要讨论 $f_{i,j}$ 的状态转移方程。

首先对于 $f_{i,0}$，实际上就是所有无向连通图的数量 $h_{i}$ 减去 $\sum_{k=1}^{i-1} f_{i,k}$，剩下的就只能是 $f_{i,0}$。但是此时我们发现 $0$ 要从 $j(j>0)$ 转移，这个顺序有点烦人，先不管了，把式子写在下面：

$$
\begin{aligned}
f_{i,0}=h_{i}-\sum_{k=1}^{i-1} f_{i,k}
\end{aligned}
$$

然后考虑 $j>0$ 的转移方程，有割边意味着有几个强连通分量，由于所有我们区分编号，所以枚举 $1$ 所在的强连通分量的大小 $k$，这样的方案数是 $f_{k,0}\times {i-1 \choose k-1}$，意思是，我们除了 $1$ 点还需要选 $k-1$ 个点，然后从 $i-1$ 个点里选。这里惊奇的发现，我们不需要从 $f_{i,0}$ 来转移，因此说明我们可以忍受上面的转移。这里留下一个问题：为什么我们不能直接枚举任意一个连通块的大小，即 ${i \choose k}$？

原因是，我们要做到不重不漏，如果我们只考虑每次选走的是哪些，就会出现这种情况：假设我们有 $5$ 个点，第一次选 $1,2,3$，第二次选 $4,5$，然后又有一种选法，第一次选 $4,5$ 与 $1,2,3$。容易看出，这两种是同一种情况，所以我们多算了。但是如果每次包含点 $1$ 的话，我们就不会出现刚刚的情况，因为我们对于 $1$ 点的连通块大小不同，所以分配也不会相同，同时，容易知道这样我们考虑了所有分法，所以也不会漏。实际上，我们所讲的 $1$ 点就是当前点中最小的点。

  我们再来整理一遍，枚举 $1$ 所在的强连通分量的大小 $k$，这样的方案数是 $f_{k,0}\times {i-1 \choose k-1}$。那么我们还要处理非 $1$ 点所在连通块的方案数。我们设 $g_{i,j,k}$ 表示由 $i$ 个点组成的无向图，有 $j$ 个连通块，这些连通块中一共有 $k$ 条割边，并且算上每个块与 $1$ 所在的连通块相连的方案数，然后，我们还需要在 $1$ 所在的连通块中选择一个与其他连通块连接的点，每次有 $k$ 种选择。枚举剩余的连通块 $x$，那么根据乘法原理总共就有 $k^x$ 种选择方法。并且当剩余的连通块为 $x$ 时，剩余的图有 $g_{i-k,x,j-x}$ 种方案。我们先不管 $g_{i,j,k}$ 的计算方法，此时我们得到了 $f_{i,j}(j>0)$ 的计算方法：

$$
\small
\begin{aligned}
f_{i,j}=\sum_{k=1}^{i-1} f_{k,0}\times {i-1 \choose k-1} \times \sum_{x=1}^{\min(i-k,j)} g_{i-k,x,j-x} \times k^x
\end{aligned}
$$

现在来考虑 $h_{i}$ 的算法（无向连通图的数量）。正难则反，我们考虑用总共的无向图的数量减去不连通的图的数量，$i$ 个点的无向图，总共可以连 $i\times (i-1)\times \frac{1}{2}$ 条边，每条边可有可无，所以总个数为 $2^{i\times (i-1) \times \frac{1}{2}}$。再来考虑不连通的图的数量，仍然的，我们考虑一号点所在的连通块大小 $j$，选出另外 $j-1$ 个点，这个方案数为 ${i-1\choose j-1} \times h_{j}$，然后对于剩余的图，它是什么样子都可以，于是乘上 $2^{(i-j)\times (i-j-1) \times \frac{1}{2}}$。至此得到 $h_{i}$ 的转移式：

$$
\small
\begin{aligned}
h_{i}=2^{i\times (i-1) \times \frac{1}{2}}-\sum_{j=1}^{i-1} h_{j} \times {i-1 \choose j-1} \times 2^{(i-j)\times (i-j-1)\times \frac{1}{2}}
\end{aligned}
$$

好的，现在我们只差 $g_{i,j,k}$（由 $i$ 个点组成的无向图，有 $j$ 个连通块，这些连通块中一共有 $k$ 条割边的方案数）的转移式了。考虑同样 $1$ 号点的连通块的大小为 $p$，这个连通块所含割边数量为 $q$，我们同样要选择，在 $i-1$ 中，选择 $p-1$ 个点，因此方案数为 $f_{p,q}\times {i-1 \choose p-1}$。然后考虑其余部分的方案数其实就是 $g_{i-p,j-1,k-q}$。注意这里我们为了算出上文的每个块与 $1$ 在的连通块相连的方案数，需要乘 $p$。于是我们又得出了 $g_{i,j,k}$ 的状态转移方程。

$$
\begin{aligned}
g_{i,j,k}=\sum_{p=1}^{i}\sum_{q=0}^{k} f_{p,q} \times {i-1 \choose p-1} \times g_{i-p,j-1,k-q} \times p
\end{aligned}
$$

接下来，我们还要讨论转移顺序，对于对于 $f_{i,j}$，它只需要 $g_{i-1,a,b}$ 就行了，也就是 $i-1$ 时的 $g$，我们可以假定 $i$ 从大到小循环，那么此时对于新的 $i$，我们直接计算 $f_{i,j}$ 就行了，因为它的 $g$ 以及 $f_{k,0}$ 在 $i'(i'<i)$ 时都已经计算过了，对于 $g$ 来说，它需要 $f_{a,b}(a\le i)$ 那么只需要在当前 $i$ 的 $f$ 计算过后转移 $g$ 即可（在这之前要转移 $f_{i,0}$）。

此时转移的初始条件为 $f_{1,0}=h_{1}$ 和 $g_{0,0,0}=1$。

至此，我们解决了这道题目。

注意不能根据 $m$ 缩小枚举范围！否则无法正确计算！我们需要完整的计算出一个状态！



## Code

```cpp
// Problem: P6596 How Many of Them
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P6596
// Memory Limit: 32 MB
// Time Limit: 800000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
#define int long long
#define upp(a, x, y) for (int a = x; a <= y; a++)
#define dww(a, x, y) for (int a = x; a >= y; a--)
#define pb(x) push_back(x)
#define endl '\n'
#define x first
#define y second
#define PII pair<int, int>
using namespace std;
const int N = 110, M = 1e5 + 10, X = 1e9 + 7;
int h[M], f[N][N], g[N][N][N], inv[M], fac[M];
int n, m;
int qmi(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) res = res * a % X;
        a = a * a % X;
        b >>= 1;
    }
    return res;
}
void init() {
    inv[0] = 1, fac[0] = 1;
    upp(i, 1, N - 1) {
        fac[i] = fac[i - 1] * i % X;
        inv[i] = qmi(fac[i], X - 2);
    }
    return;
}
int choose(int x, int y) {
    return fac[x] * inv[y] % X * inv[x - y] % X;
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> n >> m;
    init();

    upp(i, 1, n) {
        h[i] = qmi(2, i * (i - 1) / 2);
        upp(j, 1, i - 1) {
            h[i] =
                ((h[i] - h[j] * choose(i - 1, j - 1) % X * qmi(2, (i - j) * (i - j - 1) / 2) % X) % X +
                 X) %
                X;
        }
        f[i][0] = h[i];
    }
    // get h[i]

    g[0][0][0] = 1;
    upp(i, 1, n) {
        upp(j, 1, i - 1) {
            upp(k, 1, i - 1) {
                int tmp = f[k][0] * choose(i - 1, k - 1) % X, sum = 0;
                upp(x, 1, min(i - k, j))(sum += g[i - k][x][j - x] * qmi(k, x) % X) %= X;
                (tmp *= sum) %= X;
                (f[i][j] += tmp) %= X;
            }
            (((f[i][0] -= f[i][j]) %= X) += X) %= X;
        } // for f[i][j]

        upp(j, 1, i) {
            upp(k, 0, i - 1) {
                upp(p, 1, i) {
                    upp(q, 0, k) {
                        (g[i][j][k] +=
                         f[p][q] * choose(i - 1, p - 1) % X * g[i - p][j - 1][k - q] % X * p % X) %= X;
                    }
                }
            }
        }
    }
    // get g[i][j][k] and f[i][j]

    int ans = 0;
    upp(j, 0, m)(ans += f[n][j]) %= X;
    cout << ans << endl;
    return 0;
}
```

---

## 作者：Acoipp (赞：1)

## 分析

首先考虑问题：

- 求 $n$ 个节点的无向简单连通图个数。

这个经典问题使用容斥解决即可，设 $f_i$ 表示 $n=i$ 时候的答案，则有：

$$
f_i=2^{\frac{i(i-1)}2}-\sum_{j=1}^{i-1} C_{i-1}^{j-1} f_j 2^{\frac{(i-j)(i-j-1)}2}
$$

这个式子的意思是用总数来减去有多个连通块的数量，后面枚举的 $j$ 是枚举和 $i$ 号点在同一个连通块的点数，$2^w$ 则表示这 $w$ 条边可以任意选择是否连接。

然后考虑用类似的解法解决这个问题，首先有一个经典的结论，现在有若干个连通块 $a_1,a_2,\dots,a_k$，要求添加 $k-1$ 条边让这 $k$ 个连通块连通，那么方案数为 $\prod_{i=1}^k a_i (\sum_{i=1}^k a_i)^{k-2}$，证明可以用矩阵树定理，此处不展开。

于是我们可以设 $g_{i,j}$ 表示 $i$ 个点有 $j$ 个边双连通分量的答案，最后的答案就是 $\sum_{k=1}^{m+1} g_{n,k}$。

首先考虑算出来 $g_{i,j}(j \ge 2)$，然后用 $g_{i,1}=f_i-\sum_{j=2}^i g_{i,j}$ 求出 $g_{i,1}$。

老套路枚举和 $i$ 在同一个连通块的点数，然后用组合数计算剩下的内容就可以了，具体而言：

$$
g_{i,j}(j \ge 2)= \sum_{k=1}^{i-1} g_{k,1}C_{i-1}^{k-1} \times opt
$$

$opt$ 是上文中我们提到的 $\prod_{i=1}^k a_i (\sum_{i=1}^k a_i)^{k-2}$，因为 $a$ 不好记录，所以还要再设 $h_{i,j}$ 为所有可能的情况中 $\prod_{i=1}^k a_i$ 的乘积的和，根据乘法分配律和结合律，得到：

$$
h_{i,j}(j \ge 2)= \sum_{k=1}^{i-1} h_{i-k,j-1}g_{k,1}C_{i-1}^{k-1} k
$$

最后根据 $h$ 还原出来 $g$（$g_{i,j}=h_{i,j}i^{j-2}$），最后容斥出来 $g_{i,1}$ 即可。

时间复杂度为 $O(n^3)$，不知道 $n$ 为什么只开 $50$。

## 代码

代码如下，仅供参考：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 55
#define mod 1000000007
using namespace std;
ll n,m,ans,i,j,k,l,f[N][N],h[N],g[N],C[N][N],temp[N][N];
inline ll qmi(ll a,ll b,ll p){
	ll res = 1%p,t = a;
	while(b){
		if(b&1) res=res*t%p;
		t=t*t%p;
		b>>=1;
	}
	return res;
}
int main(){
	ios::sync_with_stdio(false);
	cin>>n>>m;
	C[0][0]=1;
	for(i=0;i<=n;i++){
		for(j=0;j<=n;j++){
			if(i) C[i][j]+=C[i-1][j];
			if(i&&j) C[i][j]+=C[i-1][j-1];
			if(C[i][j]>=mod) C[i][j]-=mod;
		}
	}
	h[0]=1;
	for(i=1;i<=n;i++){
		h[i]=qmi(2,i*(i-1)/2,mod);
		for(j=1;j<i;j++) h[i]=(h[i]-h[j]*C[i-1][j-1]%mod*qmi(2,(i-j)*(i-j-1)/2,mod)%mod+mod)%mod;
	}
	m=min(m,n-1);
	g[0]=1;
	for(i=1;i<=n;i++){
		for(j=2;j<=i;j++){
			for(k=1;k<i;k++){
				f[i][j]=(f[i][j]+temp[i-k][j-1]*C[i-1][k-1]%mod*g[k]%mod*k%mod)%mod;
			}
		}
		g[i]=h[i];
		for(j=2;j<=i;j++){
			temp[i][j]=f[i][j];
			f[i][j]=f[i][j]*qmi(i,j-2,mod)%mod;
			g[i]=(g[i]-f[i][j]+mod)%mod;
		}
		temp[i][1]=g[i]*i%mod,f[i][1]=g[i];
	}
	for(i=1;i<=m+1;i++) ans=(ans+f[n][i])%mod;
	cout<<ans<<endl;
	return 0;
} 
```

---

## 作者：MoonPie (赞：1)


fun fact：这是tourist出的题。

[题面](https://www.luogu.com.cn/problem/P6596)

不多于m条割边有标号无向连通图计数。

---

割边不好考虑，考虑边双连通缩点之后得到一棵树，点数为边双连通分量的个数，割边数就是边双连通分量的个数-1。

设 $\mathbb{S} = \{S_1,S_2,\dots,S_k\}$ 注意是点集的集合，设 $F(\mathbb{S})$ 表示边双连通分量**至少**包含 $\mathbb{S}$ 的有标号无向连通图个数数，设 $g(n)$ 表示 $n$ 个点构成的有标号无向连通图的方案数。
$$
g_n = 2^{\binom{n}{2}}-\sum_{i=1}^{n-1}2^{\binom{n-i}{2}}\binom{n-1}{i-1}g_i
$$
你考虑这么一件事，就是说：
$$
\begin{aligned}
F(\mathbb{S}) = \binom{n}{|S_1|,|S_2|,\dots,|S_k|} \prod_{i=1}^{k}g(|S_i|)\times V
\end{aligned}
$$
$V$ 就是将 $k$ 个连通块连成一棵树的方案数。根据 purfer 序列的经典结论：
$$
V = n^{k-2}\prod_{i=1}^{k}|S_i|
$$
然后原式就变得非常阳间了：
$$
\begin{aligned}
F(\mathbb{S}) =& \binom{n}{|S_1|,|S_2|,\dots,|S_k|}n^{k-2} \prod_{i=1}^{k}g(|S_i|)\times |S_i|\\
=&\frac{n!}{n^2}\prod_{i=1}^{k}\frac{n\cdot g(|S_i|)|S_i|}{|S_i|!}
\end{aligned}
$$
考虑到 $\sum |S_i|=n$ 是确定的，所以 $F(\mathbb{S})$ 只与 $k$ 有关，所以不妨改变其定义：$F(k)$ 表示至少有 $k$ 个边双的连通图的个数。
$$
F(k) = \frac{n!}{n^2}\frac{1}{k!}\sum_{\sum_{i=1}^{k}a_i = n}\prod_{i=1}^{k}\frac{n\cdot g(a_i)a_i}{a_i!}
$$
注意这里要在原来的式子的基础上 $\times \frac{1}{k!}$ 因为集合之间是无序的。

已经俨然是一个卷积的形式了。定义生成函数 $\mathcal{F}(x) = \sum_{i}\frac{n\cdot g(i)i}{i!}x^i$。
$$
F(k) = \frac{n!}{n^2}[x^n]\mathcal{F}^k(x)
$$
设 $G(\mathbb{S})$ 表示恰好有边双连通分量 $\mathbb{S} = \{S_1,S_2,\dots,S_k\}$ 的方案数。根据容斥原理：
$$
\begin{aligned}
 &F(\mathbb{S}) = \sum_{\mathbb{S}\subseteq\mathbb{T}} G(\mathbb{T})\\
\rightarrow& G(\mathbb{S}) = \sum_{\mathbb{S}\subseteq\mathbb{T}}(-1)^{|\mathbb{T}|-|\mathbb{S}|}F(\mathbb{T})\\
\end{aligned}
$$
类似地，改变 $G$  地定义：$G(k)$ 表示恰好有 $k$ 个边双连通分量的连通图的个数。
$$
\begin{aligned}
G(k) =& \sum_{i=k}^{n}(-1)^{i-k}\binom{i}{k}F(i)\\
\end{aligned}
$$
然后在计算 $\sum_{i=0}^{m} G(i+1)$ 得到答案。

---

但考虑到是对边进行容斥，所以用上面的式子求出来的答案是错的，而下面的却是对的：
$$
G(k) = \sum_{i=k}^{n}(-1)^{i-k}{\color{red}{\binom{i-1}{k-1}}}F(i)
$$

时间复杂度：$O(n^3)$，用多项式优化可以做到 $O(n^2\log n)$

---

## 作者：Union_of_Britain (赞：0)

暴力 $O(p(n)n)$ 直接冲。

首先需要知道 [边双连通图计数](https://www.luogu.com.cn/problem/P5828) 的做法（至少在 $n=50$ 下）。设 $n$ 个点的边双连通图有 $a_i$ 个。

这道题缩点之后就是 $\le m+1$ 个点的树。以拆分数复杂度枚举树上每个节点缩点前的大小，设为 $p_{1:k}$；方案数是连成一棵树的方案数乘上

$$\binom{n}{p_1,p_2,\dots,p_k}\times \prod a_{p_i}\times \prod \frac{1}{s_i!}$$

$s_i$ 是等于 $i$ 的 $p_j$ 的个数。

连成一棵树的方案根据[结论](https://www.luogu.com.cn/problem/CF156D)是 

$$n^{k-2}\prod p_i$$

直接 $O(n)$ 计算即可（一开始我还写了个矩阵树。。）。总复杂度是 $O(p(n)n)$。

代码由于是从边双连通计数那里直接拿的很丑。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod=1e9+7;
int qp(int a,int b){
	if(b==0)return 1;
	int T=qp(a,b>>1);T=T*T%mod;
	if(b&1)return T*a%mod;
	return T;			
}
namespace BH{
	const int maxn=505,G=3,iG=332748118;
	int lim,L,r[maxn];
	void predo(int n){
		lim=1,L=0;
		while(lim<=n)lim<<=1,L++;
		for(int i=1;i<lim;i++)r[i]=(r[i>>1]>>1)|((i&1)<<L-1);
	}
	#define Poly vector<int> 
	Poly operator +(Poly a,Poly b){
		Poly c(max(a.size(),b.size()));
		for(int i=0;i<c.size();i++){
			c[i]=0;
			if(a.size()>i)c[i]+=a[i];
			if(b.size()>i)c[i]+=b[i];
			c[i]%=mod;
		}
		return c;
	}
	Poly operator -(Poly a,Poly b){
		Poly c(max(a.size(),b.size()));
		for(int i=0;i<c.size();i++){
			c[i]=0;
			if(a.size()>i)c[i]+=a[i];
			if(b.size()>i)c[i]-=b[i]-mod;
			c[i]%=mod;
		}
		return c;
	}
	Poly operator *(Poly a,Poly b){
		Poly c(a.size()+b.size()-1);
		for(int i=0;i<a.size();i++)for(int j=0;j<b.size();j++)(c[i+j]+=a[i]*b[j])%=mod;
		return c;
	}
	Poly operator *(Poly a,int b){
		for(auto &u:a)u=u*b%mod;
		return a;
	}
	Poly inv(const Poly &a,int len){
		if(len==1){	
			Poly b(1);	
			b[0]=qp(a[0],mod-2);	
			return b;	
		}	
		Poly b=inv(a,(len+1)>>1),c(len),D=b*b;	
		for(int i=0;i<len;i++)c[i]=a[i];	
		D.resize(len);	
		b=(b*2)-D*c;	
		b.resize(len);	
		return b;
	}
	Poly ln(const Poly &a,int len){
		Poly b=inv(a,len),F(len-1);
		for(int i=0;i<len-1;i++)F[i]=(i+1)*a[i+1]%mod;
		b=b*F;b.resize(len);
		for(int i=len-1;i>0;i--)b[i]=b[i-1]*qp(i,mod-2)%mod;
		b[0]=0;
		return b;
	}
	Poly deriv(Poly a){
		if(a.size()==1)return (Poly){0};
		Poly b;b.resize(a.size()-1);
		for(int i=0;i<a.size()-1;i++)b[i]=(i+1)*a[i+1]%mod;
		return b;
	}
	Poly integ(Poly a){
		Poly b;b.resize(a.size()+1);
		for(int i=0;i<a.size();i++)b[i+1]=a[i]*qp(i+1,mod-2)%mod;
		return b;
	}
	Poly exp(const Poly &a,int len){
		if(len==1)return (Poly){1};
		Poly b=exp(a,(len+1)>>1);b.resize(len);Poly lnb=ln(b,len);
		for(int i=0;i<len;i++)lnb[i]=(a[i]-lnb[i]+mod)%mod;
		(lnb[0]+=1)%=mod;
		b=b*lnb;b.resize(len);
		return b;
	}
	Poly P,D,bD;
	int N=50,fac[maxn];
	int calc(int n){
		Poly dD(n+1),eD(n+1);
		for(int i=1;i<=n;i++)bD[i]=n*bD[i]%mod;
		eD=exp(bD,n+1);
		for(int i=1;i<=n;i++)bD[i]=qp(n,mod-2)*bD[i]%mod;
		dD=deriv(D);dD.resize(n+1);
		dD=dD*eD;
		return fac[n-1]*qp(n,mod-2)%mod*dD[n-1]%mod;
	}
	void predo(){
		fac[0]=1;
		for(int i=1;i<=N;i++)fac[i]=fac[i-1]*i%mod;
		P.resize(N+1);P[0]=P[1]=1;
		for(int i=2;i<=N;i++)P[i]=qp(2,i*(i-1)/2)*qp(fac[i],mod-2)%mod;
		D=ln(P,N+1);
		for(int i=1;i<=N;i++)D[i]=D[i]*i%mod;
		bD.resize(N+1);
		for(int i=1;i<=N;i++)bD[i]=(-D[i]+mod)%mod;
	}
}
const int maxn=55;
int n,m,a[maxn],fac[maxn],ifac[maxn],p[maxn],cnt=0,ans=0;
void calc(){
	int r=1;
	for(int j=1;j<=cnt;j++)(r*=a[p[j]])%=mod;
	(r*=fac[n])%=mod;
	for(int j=1;j<=cnt;j++)(r*=ifac[p[j]])%=mod;
	map<int,int> mp;
	for(int j=1;j<=cnt;j++)mp[p[j]]++;
	for(auto [a,b]:mp)(r*=ifac[b])%=mod;
	if(cnt>1){(r*=qp(n,cnt-2))%=mod;
	for(int i=1;i<=cnt;i++)(r*=p[i])%=mod;}
	(ans+=r)%=mod;
}
void getpart(int A,int t){
	if(cnt>m+1)return ;
	if(A==0){return calc();}
	for(int j=t;j<=A;j++){
		p[++cnt]=j;
		getpart(A-j,j);
		--cnt;
	}
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n>>m;
	BH::predo();
	for(int i=1;i<=n;i++)a[i]=BH::calc(i);
	fac[0]=1;
	for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
	ifac[n]=qp(fac[n],mod-2)%mod;
	for(int i=n-1;i>=0;i--)ifac[i]=ifac[i+1]*(i+1)%mod;
	getpart(n,1);
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：zhongpeilin (赞：0)

## 題目大意：
给定 $n, m$，求有多少 $n$ 个顶点的联通图，使得割边不超 $m$ 条，节点有编号，$n, m \le 50$。
## 解题思路：
首先我们根据题意，不难想到一种 dp，设 $f_{i, j}$ 表示 $i$ 个点的连通图，恰好 $j$ 条割边的方案数。根据经典不重复算的套路，我们可以枚举最小点所在的边双的大小，设大小其为 $k$，然后考虑剩下的，因为缩点后图有可能是这样：![](https://cdn.luogu.com.cn/upload/image_hosting/ygtoo0za.png)  
所以我们还要枚举将最小的点所在的边双删掉后会有几个连通块，假设有 $l$ 个连通块，那么割边就减少了 $l$ 个。  
为了辅助 $f$，我们设 $g_{i, j, k}$ 表示 $i$ 个点，$j$ 个连通块，$k$ 个割边的方案数。  
$$f_{i, j} = \sum_{k - 1}^{i-1}C_{i-1}^{k-1}\times f_{k, 0} \times \sum_{l = 1}^{\min(i-k,j)} k^l \times g_{i-k, l, j - l}$$
这里的 $C_{i-1}^{k-1}$ 是从最小点外剩下的点里选 $k-1$ 个点和最小点组成一个边双，$f_{k, 0}$ 就是最小点的变双里没有割边的方案数，$k^l$ 是最小点所在的边双删去后的每个连通块和边双之间的边，$g_{i - k, l, j - l}$ 是删掉边双后的其他连通块的方案数。  
**注：$k^l$ 只考虑了在边双连接其他连通块的边的在边双内部的点的方案数，本应再乘个其他连通块的大小乘积，会在后面 $g$ 的过程中算**。  
我们观察 $f$ 的式子，发现 $f_{i, 0}$ 会算成 `0`！单着显然不是我们想要的，所以我们再通过容斥原理，设 $h_{i}$ 表示 $i$ 个点，能构成连通图的方案数。
$$f_{i, 0} = h_{i} - \sum_{j=1}^{i-1}f_{i, j}$$
然后考虑算 $h$，还是容斥，枚举最小点所在的连通块大小，然后设大小为 $j$，那么就有：
$$h_{i} = 2^{C_{i}^2} - \sum_{j = 1}^{i-1}C_{i-1}^{j-1} \times h_{j}$$
就这样，我们只剩了个 $g$，$g_{i, j, k}$ 表示有 $i$ 个点，$j$ 个连通块， $k$ 条割边，求方案数。  
套路，枚举最小点所在的连通块的点数 $p$ 和割边数 $q$，那么有：
$$g_{i, j, k} = \sum_{p = 1}^i \sum_{q=0}^k C_{i-1}^{p-1} \times f_{p, q} \times p \times g_{i - p, j - 1, k - q}$$
$f_{p, q}$ 就是最小点所在连通块中的答案，$p$ 是为了上面求 $f$。  
然后就大功告成啦 QWQ。  
## CODE：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int mod = 1e9 + 7;
int n, m, h[55], f[55][55], g[55][55][55];
int C[55][55], pw[55][25 * 49 + 2];

signed main(){
	ios::sync_with_stdio(false);
	cin >> n >> m;
	for(int i = 1; i <= 50; i++){ //预处理
		pw[i][0] = 1;
		for(int j = 1; j <= n * (n - 1) / 2; j++){
			pw[i][j] = pw[i][j - 1] * i % mod;
		}
	}
	
	for(int i = 0; i <= n; i++){ //组合数
		C[i][0] = 1;
		for(int j = 1; j <= i; j++) C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
	}
	
	h[0] = 1;
	for(int i = 1; i <= n; i++){ //h
		h[i] = pw[2][C[i][2]];
		for(int j = 1; j < i; j++){
			h[i] = (h[i] - h[j] * C[i - 1][j - 1] % mod * pw[2][(i - j) * (i - j - 1) / 2] + mod) % mod;
		}
	}
	f[0][0] = 1;
	g[0][0][0] = 1;
	for(int i = 1; i <= n; i++){
		f[i][0] = h[i];
		for(int j = 1; j < i; j++){ //不需要到m
			for(int k = 1; k < i; k++){
				for(int l = 1; l <= min(i - k, j); l++){ //因为下面有个i-k-l，j-l
					f[i][j] = (f[i][j] + g[i - k][l][j - l] * pw[k][l] % mod * C[i - 1][k - 1] % mod * f[k][0]) % mod;
				}
			}
			f[i][0] = (f[i][0] - f[i][j] + mod) % mod; //特殊计算
		}
		
		for(int j = 1; j <= i; j++){
			for(int k = 0; k < i; k++){
				for(int p = 1; p <= i; p++){
					for(int q = 0; q <= k; q++){
						g[i][j][k] = (g[i][j][k] + f[p][q] * g[i - p][j - 1][k - q] % mod * C[i - 1][p - 1] % mod * p) % mod;
					}
				}
			}
		}
	}
	int sum = 0;
	for(int i = 0; i <= min(n, m); i++) sum = (sum + f[n][i]) % mod; //答案
	cout << sum << endl;
	return 0;
}

---

