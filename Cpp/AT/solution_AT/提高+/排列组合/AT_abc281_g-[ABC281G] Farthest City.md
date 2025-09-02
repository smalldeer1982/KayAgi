# [ABC281G] Farthest City

## 题目描述

给定正整数 $N,\ M$。  
请计算满足以下条件的 $N$ 个顶点的简单连通无向图（顶点编号为 $1,\dots,N$）的总数，并输出其对 $M$ 取余的结果。

- 对于所有 $u=2,\dots,N-1$，从顶点 $1$ 到顶点 $u$ 的最短距离严格小于从顶点 $1$ 到顶点 $N$ 的最短距离。

这里，从顶点 $u$ 到顶点 $v$ 的最短距离指的是连接顶点 $u$ 和 $v$ 的所有简单路径中所包含的边数的最小值。  
另外，若存在某一对顶点 $u,v$，使得连接这两个顶点的边只存在于其中一个图中，则这两个图被认为是不同的。

## 说明/提示

## 限制条件

- $3 \leq N \leq 500$
- $10^8 \leq M \leq 10^9$
- $N,\ M$ 均为整数

## 样例解释 1

以下 $8$ 种情况满足条件。  
![](https://img.atcoder.jp/abc281/5c77dfe15dfa3c03666e654bf8cfdc01.png)

## 样例解释 3

请注意要对 $M$ 取余。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4 1000000000```

### 输出

```
8```

## 样例 #2

### 输入

```
3 100000000```

### 输出

```
1```

## 样例 #3

### 输入

```
500 987654321```

### 输出

```
610860515```

# 题解

## 作者：_GaP (赞：21)

## 题目分析
首先分析一下 $d_1,d_2 \cdots d_{n-1}$，因为它们皆严格小于 $d_n$，且这是一个无向连通图。  
所以我们便可以将 $d_1,d_2 \cdots d_{n-1}$ 看成一个个点，分在 $1$ 到 $d_n-1$ 上，并且每个值上均有点，否则图就一定不联通。

分出层后，我们就可以利用**乘法原理**分层求解方案数。

令 $F_{i,j}$ 为前若干层有 $i$ 个点且最外层有 $j$ 个点时的方案数，那么有方程如下：
$$F_{i,j}=\sum_{k=1}^{i-j} F_{i-j,k} \times C_{n-i+j-1}^{j}\times (2^k-1)^j \times 2^{\frac{j \times (j-1)}{2}}$$  

枚举上一排也就是前 $i-j$ 个的最后一层点的数目 $k$，则 $k\in[1,i-j]$。   

如图：  

![](https://cdn.luogu.com.cn/upload/image_hosting/mlhvu5b5.png)  

方案的计算一共分为三部分：

1. 选择 $j$ 个数作为点的编号，那么应该是从 $n-(i-j)-1$ 个数（不要忘记把 $n$ 这个点剪掉）中选出 $j$ 个,也就是 $C_{n-i+j-1}^j$。  

2. 向上一层 $k$ 个数连线，考虑每个点均可以选 $1$ 到 $k$ 个点进行连接，也就是 $C_k^1+C_k^2\cdots+C_k^k=2^k-1$。每个点都有 $(2^k-1)$ 种选择，所以总方案数就是 $(2^k-1)^j$。  

3. $j$ 个点内部可以互相连线，$j$ 个点的完全图共有 $C_j^2$ 条边，也就是 $\frac{j\times (j-1)}{2}$ 条边。所以这 $j$ 个点内部最多可以连 $\frac{j \times (j-1)}{2}$ 条边。令 $x=\frac{j \times(j-1)}{2}$，则总方案数应为 $C_x^0+C_x^1+ \cdots +C_x^x$，根据二项式定理应等于 $2^x$。所以此部分的方案数应是 $2^{\frac{j \times (j-1)}{2}}$。

最终根据乘法原理三项相乘即为这一层的方案数。

最终答案就是 $F_{n,1}$。

**注意**：long long 很重要。

## 代码


```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define N 510
long long n,mod,c[N][N],_2[N*N],f[N][N],p[N][N];
inline long long ksm(long long x,long long p)
{
	if(p==0)return 1%mod;
	if(p==1)return x%mod;
	long long o=ksm(x,p/2)%mod;
	if(p&1)return o*o%mod*x%mod;
	return o*o%mod;
 } 
inline void init()
{
	c[0][1]=c[0][0]=1;
	for(long long i=1;i<=n;i++)
	{
		c[i][0]=c[i][i]=c[0][i]=1;
		for(long long j=1;j<i;j++)c[i][j]=(c[i-1][j]+c[i-1][j-1])%mod;
	}
	_2[0]=1;
	for(long long i=1;i<=n*(n-1)/2;i++)_2[i]=_2[i-1]*2%mod;
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)p[i][j]=ksm(_2[i]-1,j)%mod;
	
} 
int main ()
{
	scanf("%lld%lld",&n,&mod);
	init();
	f[1][1]=1;
	for(long long i=2;i<=n;i++)
	{
		for(long long j=1;j<i;j++)
		{
			for(long long k=1;k<=i-j;k++)f[i][j]=(f[i][j]+f[i-j][k]*c[n-i+j-1][j]%mod*_2[j*(j-1)/2]%mod*p[k][j]%mod)%mod;
		}
	}
	printf("%lld\n",f[n][1]);
	return 0;
}
```



------------
撒花~

---

## 作者：Obviathy (赞：11)

## solution：

当你在手模样例的时候，就会思考以生么样的顺序去枚举会更加美妙。

于是就发现一些很好的性质：

- 从 $1$ 到 $d_N$ 的所有距离都有点。所有点的距离去重就是 $1$ 到 $d_N$ 的排列。
- 考虑像 BFS 一样按照从 $1$ 号点搜的距离来对这个图分层，发现第 $i$ 层的每一个点都至少跟上一层的一个点相连，且仅能跟上一层的点相连，每一层内可以相连。

那么我们发现它是十分可以 DP 的！考虑 $f_{i,j}$ 记录这个图中前 $i$ 个点，按深度分的最后一层上有 $j$ 个点的答案。

- 首先，我们最后需要输出的答案是 $f_{n,1}$ 即全部 $n$ 个点，最后一层是终点 $n$。
- 初始化，就是 $f_{1,1} = 1$ 即第一个起点只有一种方案。

现在考虑转移，我们首先需要枚举一下 $i$，然后枚举一下 $j$，这时候考虑如何转移 $f_{i,j}$。

我们发现 $f_{i,j}$ 究竟答案是多少取决于上一层的点的个数，考虑枚举一下，设其为 $k$。那么 $k$ 的范围及应该是 $[1,i-j]$，值得注意的是，理论 $k$ 应该取不到 $i-j$，但多算一点对答案没有影响，而且在最开始 $j$ 表示深度为 $1$ 的那一层是，就必须考虑 $k=i-j$ 的情况了，为了简便，就不需要分情况写了。

现在我们拿到了三个变量，可以正式开始推式子了。

我们得到：

$$f_{i,j} = \sum\limits_{k=1}^{i-j}\color{red}f_{i-j,k}\color{green}\dbinom{n-(i-j)-1}{j}\color{brown}2^{\frac{j(j-1)}{2}}\color{blue}(2^k-1)^j$$

我将这个方程分成了 $4$ 部分，下面将逐一进行解释：

- $\color{red}f_{i-j,k}$：我们枚举了上一层的个数 $k$，那么自己画画就能知道，就应该在现在的 $i$ 中减掉这一层的 $j$ 后剩余的点中，最后一层就是 $k$ 个了，那么就是从 $f_{i-j,k}$ 转移过来了。

- $\color{green}\dbinom{n-(i-j)-1}{j}$：考虑这一层的 $j$ 个点有多少种可以选择的标号。包括上一层的那些点，已经用了 $i-j$ 个标号，最后的终点也用了一个，那么总的数量就是 $n-(i-j)-1$，在里面选 $j$ 个就行，预处理组合数。

- $\color{brown}2^{\frac{j(j-1)}{2}}$ 可能 $\LaTeX$ 这里不太清楚，是次方。这里我们考虑这一层的 $j$ 个点互相连有几种选法。我们知道 $j$ 个节点的完全图的边数是 $\frac{j(j-1)}{2}$，在这些边中我们可以任意选择若干，那么每一条边都有两种情况：选或不选，那么就是 $2^{\frac{j(j-1)}{2}}$ 种。

- $\color{blue}(2^k-1)^j$ 然后考虑 $j$ 那层和 $k$ 那层之间连边的情况。每一个 $j$ 是孤立的，分开讨论。拿出一个 $j$ 里的点看，它可以任选若干 $k$ 里的点连，就有 $2^k$ 种，但不能一个都不选，减掉即可。这里是 $j$ 个点，所以乘法原理就得到了答案。

最后答案相加即可。

于是我们就得到了状态转移方程，初始化一些必要的量，比如组合数，$2^n$ 和 $(2^k-1)^j$，时间复杂度 $O(n^3)$。

特别注意的是，在 $i = n$ 的时候，终点的标号有一种选法，只需要在初始化的时候把 $C_{0,i}$ 都变成 $1$ 就行。

## AC code:

```cpp
#include<bits/stdc++.h>
const int N = 501;
long long n,mod,c[N][N]={1},f[N][N],_2[N*N]={1},_2k_1[N][N];
int main(){
	std::cin>>n>>mod;
	f[1][1]=1;
	for(int i = 1;i <= n*n;i ++)_2[i] = _2[i-1] * 2 % mod;
	for(int i = 1;i <= n;i ++){_2k_1[i][0] = 1;for(int j = 0;j <= n;j ++)c[i][j] = (c[i-1][j] + c[i-1][j-1])%mod,_2k_1[i][j] = (j == 0)?_2k_1[i][j]:(_2k_1[i][j-1] * (_2[i]-1) % mod);c[0][i] = 1;}
	for(int i = 1;i <= n;i ++)
		for(int j = 1;j < i;j ++)
			for(int k = 1;k <= i-j;k ++)
				f[i][j] = (f[i][j] + f[i-j][k]*c[n-i+j-1][j]%mod*_2[j*(j-1)/2]%mod*_2k_1[k][j]% mod)%mod;
	std::cout<<f[n][1]<<std::endl;
	return 0;
}
```

---

## 作者：DeaphetS (赞：8)

和 [CF1657E](https://codeforces.com/contest/1657/problem/E) 的做法十分相似

考虑最短路的值一定是连续的，那么若最短路为 $i$ 的点数有 $c_i$ 个，且 $dis_n=k$，则方案数可以计算

$$Ans=\binom{n-2}{c_2,c_3,...,c_{k-1}}\times \prod_{i=1}^{k} (2^{c_{i-1}}-1)^{c_i}\times 2^{\binom{c_i}{2}}$$

其中，$\sum_{i=0}^{k}c_i=n,c_0=c_k=1$。$(2^{c_{i-1}}-1)^{c_i}$ 的含义为最短路为 $i$ 的点是从最短路为 $i-1$ 的点连接过来的，那么对于每个这样的点，他可以选择上一层的任意一个非空子集进行连接。$2^{\binom{c_i}{2}}$ 的含义则是，对当前层的所有点，两两之间可以任意连接，对应可连接的边数为 $\binom{c_i}{2}$，于是会有 $2^{\binom{c_i}{2}}$ 的系数。

考虑背包，按最短路的值从小到大一批批安排当前点，那么有一个初始的 DP 想法，就是令 $f_{i,j,k}$ 表示当前已经安排了 $i$ 个点，目前最短路的最大值为 $j$，对应点的个数为 $k$ 的方案数，那么枚举最短路值为 $j+1$ 的点的数量 $cnt$，可以转移到 $f_{i+cnt,j+1,cnt}$，转移系数为 $\binom{n-1-i}{cnt}\times (2^{j}-1)^{cnt}\times 2^{\binom{cnt}{2}}$。但是直接这样做是 $O(n^4)$ 的。

发现转移系数与 $j$ 无关，所以这一维可以直接省去，于是 DP 方式就变成，设 $f_{i,j}$ 表示当前已经安排了 $i$ 个点，且目前最短路最大的点数为 $j$ 的方案数，那么同样枚举下一层的点数 $k$，就能转移到 $f_{i+k,k}$，转移系数为 $\binom{n-1-i}{k}\times (2^{j}-1)^{k}\times 2^{\binom{k}{2}}$。初始值设 $f_{1,1}=1$，最后答案即为 $\sum_{j=1}^{n-1} f_{n-1,j}\times (2^j-1)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 510
#define LL long long
int n,MOD,f[N][N],c[N][N],p[N*N],ans;
LL qow(LL x,LL y){return y?(y&1?x*qow(x,y-1)%MOD:qow(x*x%MOD,y/2)):1;}
int main()
{
	scanf("%d%d",&n,&MOD);
	p[0]=c[0][0]=1;
	for(int i=1;i<=n;i++){
		c[i][0]=c[i][i]=1;
		for(int j=1;j<i;j++)
			c[i][j]=(c[i-1][j]+c[i-1][j-1])%MOD;
	}
	for(int i=1;i<=n*n;i++)p[i]=2ll*p[i-1]%MOD;
	f[1][1]=1;
	for(int i=1;i<n;i++)
	for(int j=1;j<=i;j++)if(f[i][j])
		for(int k=1;i+k<n;k++)
			f[i+k][k]=(f[i+k][k]+1ll*f[i][j]*c[n-i-1][k]%MOD*qow(p[j]+MOD-1,k)%MOD*p[k*(k-1)/2]%MOD)%MOD;
	for(int j=1;j<=n-1;j++)
		ans=(ans+1ll*f[n-1][j]*(p[j]+MOD-1)%MOD)%MOD;
	printf("%d\n",ans);
}
```

时间复杂度为 $O(n^3 \log n)$，预处理了 $2^i$ 的值稍微进行了点常数优化。实际上是可以通过 $O(n^2)$ 预处理每个 $(2^j-1)^k$ 的值把复杂度降到 $O(n^3)$ 的，但是既然能过就不优化了。`╮(╯▽╰)╭`

---

## 作者：SnowFlavour (赞：3)

# ABC281G 题解

首先，我们会注意到显然如果存在长度为 $l$ 的路径，就一定会有一条长度为 $l-1$ 的路径，因为每一条边的长度都是 $1$。

因此我们考虑在图上按照最短路径分层（其实就是按照 BFS 序分层）。会发现分层以后正好满足动态规划的性质。设 $f_{i,j}$ 表示在 $i$ 个节点中，最后一层有 $j$ 个节点的方案数，则有如下的等式：


$$
f_{i,j}= 
\sum^{i-j}_{k=1}\color{red}f_{i-j,k}
\color{black}\times\color{green}(2^k-1)^j
\color{black}\times\color{blue}2^{\frac{j(j-1)}{2}}
\color{black}\times\color{purple}C^j_{n-i+j-1}
$$


下面我们来一点点拆分。

首先，$k$ 表示倒数第二层的节点数量。

红色部分表示前面一层有 $k$ 个节点的方案数量。

绿色部分是由二项式定理得到的。

我们对于当前层的每一个节点 $j$，都需要与至少一个 $k$ 连接。也就是说，答案就是这样：

$$
\sum^{k}_{x=1}C^x_k
$$

这个式子的意义就是从 $k$ 个节点中选择 $x$ 个节点的答案的和。

根据二项式定理，这个式子可以化成上面绿色式子的底数。**注意！这里的 $x$ 是从 $1$ 开始的，所以要减 $1$。**

对于每一个当前层上面的节点 $j$，我们都有上面的式子，因此答案就是所有的结果的乘积，也就是 $j$ 次方。

蓝色部分是表示在这些边之间也能连边。虽然我们是按照最短路分层，但是我们依然可以在同一层的边之间连接，这并不会影响这些点的最短路。这些边总共有 $\frac{j(j-1)}{2}$ 条，于是再像上面一样跑一遍二项式定理，即可得到蓝色部分。

紫色部分是指我们的 $j$ 个节点有多少种选择方式。我们要有 $i-j$ 个节点是原来不可改变的，剩下的点都可以自由选择……吗？

**别忘了，最后一个节点的长度要大于前面的所有节点，他不能被选择！**

于是我们就得到了上面的答案。

最后的答案就是 $f_{n,1}$。

不对。这个时候我们会发现一个严重的问题：为什么输出都是 $0$ 啊？！

观察答案，我们可以发现紫色的部分有锅。

要不把 $i=n,j=1$ 代入这个式子看看？会发现 $n-i+j-1=n-n+1-1=0$。

这个时候回到上面，就会发现这个式子的一个重要要求就是最后一个点不能选。但是我们的答案其实就是第 $n$ 个点，所以我们要特判。

最后就是排列数的快速计算方法：

$$
C^i_j=C_{j-1}^i+C_{j-1}^{i-1}

$$

这样我们来考虑一下复杂度：预处理 $O(N^2)$，DP的循环 $O(N^3)$，但是我们的答案的绿色部分会有一点问题，我们可以预处理（用快速幂枚举所有的 $j$ 和 $k$），也可以直接在循环的时候再算，所以答案的复杂度是 $O(N^3\log n)$ 或者 $O(N^3)$。反正时限大，都能过。

AC Code:

```cpp
#include<iostream>
using namespace std;
const int N=600;
int MD;
typedef long long ll;
ll C[N][N],p2[N*N],f[N][N];
ll fast(ll n,ll p){ll s=n,ans=1;while(p){if(p&1)ans*=s;ans%=MD;s*=s;s%=MD;p>>=1;}return ans;}
void init(){
    C[1][0]=C[1][1]=C[0][1]=1;
    for(int i=2;i<N;i++){
        C[i][0]=C[0][i]=1;
        for(int j=1;j<=i;j++){
            C[i][j]=(C[i-1][j]+C[i-1][j-1])%MD;
        }
    }
    p2[0]=1;
    for(int i=1;i<N*N;i++){
        p2[i]=(p2[i-1]<<1)%MD;
    }
}

int main(){
    int n;
    cin>>n>>MD;
    init();
    f[1][1]=1;
    for(int i=2;i<=n;i++){
        for(int j=1;j<i;j++){
            for(int k=1;k<=i-j;k++){
                f[i][j]=f[i][j]+f[i-j][k]*fast(p2[k]-1,j)%MD*p2[j*(j-1)/2]%MD*C[n-i+j-1][j]%MD;
                f[i][j]%=MD;
              
            }
            // cout<<n-i+j-1<<" ";
            // cout<<i<<" "<<j<<" "<<f[i][j]<<endl;
        }
    }
    cout<<f[n][1]<<endl;
}
```

---

## 作者：lhc0707 (赞：2)

AT_abc281_g 题解

首先我们注意到 $[0,d_n]$ 这些数必须全部取到，因为最短路是由之前的 $d$ 值确定的，且每条边长度都为 $1$，如果其中一个数没有取到的话，那比这个数大的数都取不到。那么我们就可以考虑将图按 $d$ 值分层，然后一层一层数数。我们知道前一层对后一层是一个子问题，于是可以 DP。

设 $f_{i,j}$ 表示我们已经安排了 $i$ 个点，最后一层有 $j$ 个点共有多少种情况，这样答案就是 $f_{n,1}$。考虑转移。

第一步，我们要选出 $j$ 个数，选的范围是除去终点和选好的点，对答案的贡献是 $C_{n-(i-j)-1}^j$。但要注意$i=n$的时候终点是必须选的，需要特判。

第二步，假设前面一层有 $k$ 个点，那么这 $j$ 个点最少要和前一层的某一个点连一条边，否则这个点就不在这一层里了。每个点的贡献是 $\sum_{k=1}^n C_{k}^i$，由二项式定理定理知道这就是 $2^k-1$，总共 $j$ 个点的贡献就是 $(2^k-1)^j$。

第三步，这 $j$ 个点之间可以随便连，贡献是 $2^{\frac{j(j-1)}{2}}$。

最后我们根据加乘原理得到转移式 ：

$$
f_{i,j}=\sum_{k=1}^{i-j} f_{i-j,k}C_{n-i+j-1}^j(2^k-1)^j2^{\frac{j(j-1)}{2}}

$$

我们预处理组合数和 $2$ 的次幂，然后敲个快速幂就可以过了，复杂度 $O(n^3\log n)$，如果预处理 $(2^k-1)^j$ 的话可以做到 $O(n^3)$，预处理会挂上常数，而且时间限制 4s，稳稳地过去了。

code:

```cpp

#include<iostream>
#include<cstdio>
#define int long long
using namespace std;
const int N=505;
int n,mod,f[N][N],C[N][N],pw[N*N];
inline int qpow(int a,int b)
{
    int res=1;a%=mod;
    while(b)
    {
        if(b&1)res=res*a%mod;
        a=(a*a)%mod; b>>=1;
    }
    return res%mod;
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin>>n>>mod;
    for(int i=0;i<=n;i++)C[i][0]=1; 
    for(int i=1;i<=n;i++)for(int j=1;j<=i;j++)C[i][j]=(C[i-1][j-1]+C[i-1][j])%mod;
    pw[0]=1;f[1][1]=1;
    for(int i=1;i<=n*(n-1)/2;i++)pw[i]=(pw[i-1]*2)%mod;
    for(int i=2;i<=n;i++)for(int j=1;j<i;j++)for(int k=1;k<=i-j;k++)
        f[i][j]=(f[i][j]+f[i-j][k]*C[n-(i-j)-(i<n)][j]%mod*qpow(pw[k]-1,j)%mod*pw[j*(j-1)/2]%mod)%mod;
    cout<<f[n][1]%mod<<"\n";
    return 0;
}
```

制作不易，望管理员大大过审。

---

## 作者：I_am_Accepted (赞：2)

看到距离限制，想到 BFS 树。

由于 $2,\dots,n-1$ 点之间无区分，可以 DP。

$f_{i,j}$ 表示 $2,\dots,n-1$ 中有 $i$ 个还没被选上，选上的中有 $j$ 个取到了目前最大距离（离 $1$ 号点）的方案数。

考虑转移，枚举下一层距离相同的点有 $k$ 个，则有：
$$
f_{i,j}\times\binom{i}{k}\times 2^{\binom{k}{2}}\times (2^j-1)^k\to f_{i-k,k}
$$
各项系数为：剩下选择 $k$ 个、内部连边、与上一层连边。

初始 $f_{n-2,1}=1$。

答案为
$$
\sum_{i=1}^{n-2} f_{0,i}\times (2^i-1)
$$
代码有必要放吗？

---

## 作者：real60t (赞：2)

### 题目描述
>给定 $n$，求点数为 $n$ 并满足 $1$ 到 $n$ 的最短路严格大于 $1$ 到其他点的最短路的简单联通无向图的数量

>$n\le500$

### 分析
考虑计数 dp。将原图分层，结点 $1$ 属于第 $1$ 层，第 $k$ 层的点到 $1$ 的最短路长度均为 $k-1$。由于层数没有限制，我们枚举最外层的点数。$f_{i,j}$ 表示前 $i$ 个点，当前最外层的点数为 $j$ 的图的数量。

转移时枚举上一层的点数进行转移。

于是有：

$$f_{i,j}=\sum\limits_{k=1}^{i-j}f_{i-j,k}\times \binom{n-i+j-1}{j}\times (2^k-1)^j\times 2^{\binom{j}{2}}$$

初始状态：$f_{1,1}=1$

稍微解释一下，每层的点是没有顺序之分的，共 $n-i+j-1$ 个点可选，所以有 $\dbinom{n-i+j-1}{j}$ 种选法。对于连边，第一种我们可以向上一层连至少一条边，所以每个点有 $2^k-1$ 种连法；第二种可以连向同层，有 $\dbinom{j}{2}$ 条边可连，所以共 $2^{\binom{j}{2}}$ 种连法。

最后答案为 $f_{n,1}$。

状态数有 $\mathcal{O}(n^2)$，转移 $\mathcal{O}(n)$，所以时间复杂度 $\mathcal{O}(n^3)$。

注意 $i=n$ 时转移略有不同，具体细节见代码。

### [Code](https://atcoder.jp/contests/abc281/submissions/37305120)

---

## 作者：WaterSun (赞：1)

# 思路

定义 $dp_{i,j}$ 表示前若干层一共有 $i$ 个点，且在这些层中最外层的点数为 $j$ 的方案数。

那么，我们先求出最外层的方案数，在 $n - (i - j) - 1$（即减去前若干层中除最外层点的数量再减去 $n$ 号点）中选出 $j$ 个作为最外层的点。所以，贡献为 $C_{n - (i - j) - 1}^j$。

令 $k$ 为前 $i - j$ 个数的最后一层的点数。那么，最后一层的 $j$ 个数可以与上一层的 $k$ 个点两两连一条边（如果连接了上上层，则 $d$ 会发生改变，所以不行），即对于每一个点都有 $\sum_{p = 1}^{k}C_{k}^{p}$，又根据二项式定理，化简为 $2^k - 1$。因此，对于所有的 $j$ 个点，贡献为 $(2^k - 1)^j$。

然后，对于那 $j$ 个点，内部也可以两两连边，而最多建为一张完全图，边数为 $\frac{j \times (j - 1)}{2}$，记作 $x$。所以，方案数为 $\sum_{p = 1}^xC_{x}^p$，又由二项式定理得 $2^x$，也就是 $2^{\frac{j \times (j - 1)}{2}}$。

综上，可得出状态转移方程：

$$
dp_{i,j} = \sum_{k = 1}^{i - j}(dp_{i - j,k} \times C_{n - (i - j) - 1}^j \times (2^k - 1)^j \times 2^{\frac{j \times (j - 1)}{2}})
$$

答案为：$dp_{n,1}$。

注意要初始化 $2^k,(2^k - 1)^j,C_n^m$。

# code

```cpp
#include <bits/stdc++.h>
#define int long long
#define re register

using namespace std;

const int N = 510;
int n,mod;
int pot[N * N];
int C[N][N],q[N][N],dp[N][N];

inline int read(){
	int r = 0,w = 1;
	char c = getchar();
	while (c < '0' || c > '9'){
		if (c == '-') w = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9'){
		r = (r << 3) + (r << 1) + (c ^ 48);
		c = getchar();
	}
	return r * w;
}

inline int qmi(int a,int b){
	int res = 1;
	while (b){
		if (b & 1) res = res * a % mod;
		a = a * a % mod;
		b >>= 1;
	}
	return res;
}

inline void init(){//初始化 
	C[0][0] = C[0][1] = pot[0] = 1;
	for (re int i = 1;i <= n;i++){
		C[i][0] = C[i][i] = 1;
		for (re int j = 1;j < i;j++) C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod;
	}
	for (re int i = 1;i <= n * (n - 1) / 2;i++) pot[i] = pot[i - 1] * 2 % mod;
	for (re int i = 1;i <= n;i++){
		for (re int j = 1;j <= n;j++) q[i][j] = qmi(pot[i] - 1,j);
	}
}


signed main(){
	n = read();
	mod = read();
	init();
	dp[1][1] = 1;
	for (re int i = 2;i <= n;i++){
		for (re int j = 1;j < i;j++){
			for (re int k = 1;k <= i - j;k++) dp[i][j] = (dp[i][j] + dp[i - j][k] * C[n - (i - j) - 1][j] % mod * q[k][j] % mod * pot[j * (j - 1) / 2] % mod) % mod;
		}
	}
	printf("%lld",dp[n][1]);
	return 0;
}
```

---

## 作者：honglan0301 (赞：1)

## 题意简述
求有 $n$ 个点，且满足点 $n$ 到点 $1$ 的最短路径长度 $dis(1,n)$ 严格大于 $dis(i,n)\ (1<i<n)$ 的无向连通图数量。

## 题目分析
根据距离的限制，想到按照分层图的形式计算。显然前 $n-1$ 个点可以任意分层连边，而点 $n$ 与且仅与最后一层的点连边。

于是我们想到记录最后一层的点来 dp, 令 $f(i,j)$ 表示总共放了 $i$ 个点，其中最后一层放了 $j$ 个点的方案数。而转移则是从 $f(i,j)$ 到 $(i+k,k)$, 即再放上一层的点，下面来讨论转移时乘的系数。

先考虑点，可以发现这一层的点要在 $(n-1-i)$ 个点中选出 $k$ 个，有 $C^k_{n-1-i}$ 种选择。

再考虑边，先是这一层内部可以任意连边，共有 ${k\times(k-1)}\over 2$ 条边可以连，所以有 $2^{{k\times(k-1)}\over 2}$ 种选择。再是对于这一层的每一个点，都可以向上一层的任意点连边，且至少连一条边，所以每个点有 $(2^j-1)$ 种选择，合起来就是 $(2^j-1)^k$ 种选择。

于是我们得到 $f(i+k,k)=f(i+k,k)+f(i,j)\times C^k_{n-1-i}\times 2^{{k\times(k-1)}\over 2}\times (2^j-1)^k$。据此 dp，时间复杂度 $O(n^3)$, 可以通过本题。

注意统计答案时还要算上点 $n$ 向上一层的连边方案数，与上面同理。

## 代码
```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <cctype>
#include <queue>
#include <map>
#include <vector>
#define int long long
using namespace std;

int n,mod,cf[250005],ycl[505][505],dp[505][505],ans,c[505][505];

signed main()
{
	cin>>n>>mod;
	cf[0]=1;
	for(int i=1;i<=n*n;i++)
	{
		cf[i]=(cf[i-1]*2)%mod;
	}
	c[0][0]=1;
	for(int i=1;i<=n;i++)
	{
		c[i][0]=1;
		for(int j=1;j<=i;j++)
		{
			c[i][j]=c[i-1][j]+c[i-1][j-1];
			c[i][j]%=mod;
		}
	}
	dp[1][1]=1;
	for(int i=1;i<=n;i++)
	{
		ycl[i][1]=(cf[i]-1+mod)%mod;
		for(int j=2;j<=n;j++)
		{
			ycl[i][j]=(ycl[i][j-1]*ycl[i][1])%mod;
		}
	}
	for(int i=1;i<=n-1;i++)
	{
		for(int j=1;j<=i;j++)
		{
			for(int k=1;k<=n-i;k++)
			{
				dp[i+k][k]+=(((dp[i][j]*c[n-i-1][k])%mod*cf[k*(k-1)/2])%mod*ycl[j][k])%mod;
				dp[i+k][k]%=mod;
			}
		}
	}
	for(int j=1;j<=n-1;j++)
	{
		ans+=(dp[n-1][j]*ycl[j][1])%mod;
		ans%=mod;
	}
	cout<<ans<<endl;
}
```


---

## 作者：WaterSky (赞：0)

# [AT_abc281_g [ABC281G] Farthest City](https://www.luogu.com.cn/problem/AT_abc281_g)
## 写在前面：
这篇题解在代码上没有什么与他人不同的地方，但是在思考过程中加入了一些自己的想法，应该能够更好理解一点。
## 正文：
先分析一下题目，题目求点数为 $n$ 并满足 $1$ 到 $n$ 的最短路严格大于 $1$ 到其他点的最短路的简单联通无向图（无重边和自环）的数量。

应该很多人没法一眼定正解，所以可以将问题再转化一下。

可以定义一棵以 $1$ 为根节点，共 $n$ 个节点的树，将它称为**原始树**。很明显，原始树应该满足第 $n$ 个节点应该距离 $1$ 最远。

但是还需要在每个原始树的节点间连边才能使树变为图，使答案准确。

于是题目就变成了求满足条件的原始树形态数再乘任意连边的方案数。

那么可以发现，可以将原始树根据深度将每一层拆开，并且计算方案树。

那么接下来就和别的题解基本一样了，也就不详细写了。

考虑计数类 DP，设置状态 $f_{i,j}$ 表示前 $i$ 个数已经在原始树中，且最后一层有 $j$ 个节点时的方案数。

那么状态转移方程即为：
$$f_{i,j}=\sum_{k=1}^{i-j}{f_{i-j,k} \times C^j_{n-(i-j)-1} \times (2^k -1)^j \times 2^{\frac{j(j-1)}{2} }}$$
稍微解释一下：
这个方程共分为了四个部分。
- 原先的树的方案数，即为 $f_{i-j,k}$。
- 在剩余的编号中选择 $j$ 个点作为编号加入新的层中，方案数为 $C^j_{n-(i-j)-1}$，注意将第 $n$ 个点先去掉。
- 在目前的叶子节点中任意增加子节点使其称为新的叶子节点，共有 $(2^k -1)^j$ 可能的方案数。
- 这 $j$ 个点间可以任意连线使这棵树成为图，则最多能连 $\frac{j(j-1)}{2}$ 条边，则总方案数为：$C_{\frac{j(j-1)}{2}}^{0}+C_{\frac{j(j-1)}{2}}^{2}+...+C_{\frac{j(j-1)}{2}}^{\frac{j(j-1)}{2}}$，根据二项式定理可以得出此项为 $2^{\frac{j(j-1)}{2}}$。

最后再根据乘法原理将所有相乘即为状态转移方程。

## 代码：
```
#include<bits/stdc++.h>
using namespace std;
long long n,mod;
long long K[1000005];
long long dp[505][505],C[505][505],p[505][505];
//dp 表示 DP 数组。
//C 表示组合数
//K[i] 表示2^i 
long long power(long long x,long long y){//快速幂 
	long long a=x,b=y,c=1;
	while(b){
		if(b%2) c*=a;
		a*=a,a%=mod,c%=mod,b/=2;
	}	
	return c;
}
void init(){//预处理函数 
	K[0]=1,C[0][1]=C[0][0]=1;
	//预处理 C 数组 
	for(long long i=1;i<=n;i++)
	{
		C[i][0]=C[i][i]=C[0][i]=1;
		for(long long j=1;j<i;j++)C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
	}
	//预处理 K 数组 
	for(long long i=1;i<=n*(n-1)/2;i++)K[i]=K[i-1]*2%mod;
	//预处理 p 数组 
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			p[i][j]=power(K[i]-1,j)%mod;
} 
int main(){
	scanf("%lld%lld",&n,&mod);
	init(),dp[1][1]=1;
	//第一个节点作为根节点放在第一层 
	for(int i=2;i<=n;i++)
		for(int j=1;j<i;j++)
			for(int k=1;k<=i-j;k++)
				dp[i][j]=(dp[i][j]+dp[i-j][k]*C[n-i+j-1][j]%mod*K[j*(j-1)/2]%mod*p[k][j]%mod)%mod;
				//状态转移。 
	printf("%lld",dp[n][1]);
	//将最后一个节点放在最后一层时的方案数即为答案。 
	return 0;
} 
```
感谢读者的阅读与管理员的审核。

---

## 作者：CrTsIr400 (赞：0)

## [7. [ABC281G] Farthest City](https://www.luogu.com.cn/problem/AT_abc281_g)

~~如果模数固定的话估计就可以打表 AC 了。~~

观察这是无边权的最短路，于是考虑 `bfs` 树。我们不妨先构建一棵 `bfs` 树，然后再在上面连一些边。

如果 `bfs` 树建出来了，同层之间可以连一些边，相差一层之间可以连一些边，$n$ 节点要独立为最后一层。

这种东西往往 DP 来做会很见效，设 $f[i][j][k]$ 为前 $i$ 个，上一层有 $j$ 个，这层有 $k$ 个，前 $i$ 个编号都分配好的方案数，注意其实我并不需要强制把 $i$ 加进去，只要加入 $[i,n]$ 之中就行了，答案就是 $\sum f[n][j][1]$。

首先先要钦定 $f[1][0][1]=1$，这是显然的。

转移：新开一层，$(n-i)\times f[i][j][k]\times(2^{k}-1)\to f[i+1][k][1]$；

新加一个，$\dfrac{1}{k+1}(n-i)\times f[i][j][k]\times 2^{j-1+k}\to f[i+1][j][k+1]$。为什么要算一个分母呢？因为顺序可能有重复。

这就是 $O(n^3)$ 的做法，但是空间会爆炸。

---

此时考虑把 DP 维度再压缩一下，因为空间访问永远是要比运算慢的。

设 $f[i][j]$ 为当前选了 $i$ 个点，最深层有 $j$ 个点，注意这里可选的节点只有 $[2,n-1]$ 区间内。于是 $\sum f[0][j]\times (2^{j}-1)$ 就是答案。

考虑直接按层转移，枚举新层 $k$，$\binom{n-i-1}{k}f[i][j]\times 2^\binom{k}{2}\times (2^{j}-1)^k\to f[i+k][k]$。这里求组合数需要用杨辉三角，不能直接求逆。

于是这题就结束了。我使用了 AtCoder modint 简化编码。

```cpp
#pragma GCC optimize(3,"Ofast","inline")
#include<bits/stdc++.h>
#include<atcoder/modint>
#define fo(i,a,b) for(I i(a),_ed(b);i<=_ed;++i)
using namespace std;using I=int;using LL=long long;using V=void;
using MI=atcoder::modint;
const I N=505;
MI f[N][N],c[N][N],pw2[N*N],k2[N][N],ans;I n,m;
I main(){ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>m;MI::set_mod(m);
	f[1][1]=1;
	pw2[0]=1;
	fo(i,1,n*n)pw2[i]=pw2[i-1]*2;
	fo(j,1,n){k2[j][1]=pw2[j]-1;
		fo(k,2,n)k2[j][k]=k2[j][k-1]*k2[j][1];}
	c[0][0]=1;
	fo(i,1,n){
		c[i][0]=1;
		fo(j,1,i)c[i][j]=c[i-1][j-1]+c[i-1][j];
	}fo(i,1,n-1)
		fo(j,1,i)fo(k,1,n-i)
			f[i+k][k]+=f[i][j]*c[n-i-1][k]*pw2[k*(k-1)/2]*k2[j][k];
	fo(i,1,n-1)ans+=f[n-1][i]*k2[i][1];
	printf("%d\n",ans.val());
	return 0;}
```



---

## 作者：SkyRainWind (赞：0)

这个题挺有意思。考虑什么样的图符合条件
设 $d_u$ 表示 1 到 $u$ 的最短距离，$u = 1 .. n-1$ 那么显然 $d_1=1$
如果该图符合条件，那么必然有：
- 如果存在 $(u,v) \in E$ ，那么 $|d_u-d_v| \leq 1$ ，否则 $|d_u-d_v| \geq 2$

考虑构造这么个图
- 先把 $d_u = \inf, u=2..n-1, m=1$
- 选任意多 $d_u = \inf$，再选任意多 $d_v=m-1$，将$u$集合中的所有点和$v$中的点连边
- $u$中的所有点任意连边（可以不连）
- $m$加一
- 最后，选任意多 $d_v=m-1$ 和 $n$ 连边
显然这就包含了所有的合法情况

考虑dp这个过程，注意到两个图不同当且仅当有一条边在一个图中有另一个图中没有，因此可以对边进行计数，这样我们就把图的问题转化为了序列问题

设 $dp[i][j]$ 表示已经加入了 $i$ 个点，$m=j$ 时的方案数
考虑 $dp[i][j] \rightarrow dp[i+k][k]$
从 $n-i-1$ 个点中挑 $k$ 个 $u$ ，$C(n-i-1,k)$ ，挑 $v$ 显然是 $2^{j}-1$ 注意这些 $v$ 都要和 $u$ 连边，因此如果有 $k$ 个 $u$ 需要 $k$次方，然后 $u$ 内部随意连是 $2^{\frac{k(k-1)}{2}}$

最后统计答案
```cpp
// by SkyRainWind
#include <cstdio>
#include <vector>
#include <cassert>
#include <cstring>
#include <iostream>
#include <algorithm>
#define mpr make_pair
#define debug() cerr<<"Yoshino\n"
#define rep(i,a,b) for(int (i)=(a);(i)<=(b);(i)++)
#define pii pair<int,int>

using namespace std;

typedef long long LL;

const int inf = 1e9, INF = 0x3f3f3f3f;

int n,mod;
int dp[505][505],C[505][505], p2[505], p22[505];

int pw(int x,int y){
	if(!y)return 1;
	if(y==1)return x;
	int mid=pw(x,y>>1);
	if(y&1)return 1ll*mid*mid%mod*x%mod;
	return 1ll*mid*mid%mod;
}

signed main(){
	scanf("%d%d",&n,&mod);
	C[0][0] = 1;
	for(int i=1;i<=500;i++){
		C[i][0] = 1;
		for(int j=1;j<=500;j++)
			C[i][j] = (C[i-1][j] + C[i-1][j-1]) % mod;
	}
	
	p2[0] = 1;
	for(int i=1;i<=500;i++)p2[i] = 2ll*p2[i-1]%mod;
	for(int i=1;i<=500;i++)p22[i] = pw(2, i*(i-1)/2);
	
	dp[1][1] = 1;
	for(int i=1;i<=n-2;i++){
		for(int j=1;j<=i;j++)if(dp[i][j]){
			int coef = 1;
			for(int k=1;i+k<=n-1;k++){
				coef = 1ll*coef*(p2[j]-1)%mod;
				(dp[i+k][k] += 1ll*dp[i][j]*C[n-1-i][k]%mod*p22[k]%mod*coef%mod) %= mod;
			}
		}
	}
	
	int ans = 0;
	for(int i=1;i<=n-1;i++)
		(ans += 1ll*dp[n-1][i]*(p2[i]-1)%mod) %= mod;
	printf("%d\n",ans);

	return 0;
}
```

---

## 作者：enucai (赞：0)

## Analysis

令 $f_{i,j}$ 表示 $i$ 个点，最远一层点共有 $j$ 个的图的数量（由于编号需要，我们先不考虑 $n$ 号点）。

我们枚举下一次增加几个点，设为 $k$，那么有：

$$
f_{i+k,k}\gets f_{i,j}\times\binom{n-i-1}{k}\times (2^j-1)^k\times2^{\binom{k}{2}}
$$

解释一下，$\binom{n-i-1}{k}$ 表示在剩下的 $n-i-1$ 个点中选择 $k$ 个点的编号，$2^j-1$ 表示上一层的每个点都可以向下一层点连边，但是不能全都不连边，$(2^j-1)^k$ 表示下一层的每一个点都有这样的选择。$2^{\binom{k}{2}}$ 表示下一层 $k$ 个点之间能互相连边。

最后统计答案时枚举最后一层有几个点，他们是否向 $n$ 号点连边。

## Code

```cpp
const int N = 510;

int n, m, dp[N][N], c[N][N], mi[N], a[N][N], b[N];

int ksm(int a, int p) {
  int res = 1;
  while (p) {
    if (p & 1) res = 1ll * res * a % m;
    a = 1ll * a * a % m, p >>= 1;
  }
  return res;
}

int main() {
  n = read(), m = read();
  rep (i, 1, n) {
    c[i][0] = c[i][i] = 1;
    rep (j, 1, i - 1) c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % m;
  }
  mi[0] = 1;
  rep (i, 1, n) mi[i] = mi[i - 1] * 2 % m;
  rep (i, 1, n) {
    int k = mi[i] - 1;
    a[i][0] = 1;
    rep (j, 1, n) a[i][j] = 1ll * a[i][j - 1] * k % m;
  }
  rep (i, 1, n) b[i] = ksm(2, 1ll * i * (i - 1) / 2);
  dp[1][1] = 1;
  rep (i, 1, n - 1) rep (j, 1, i) rep (k, 1, n - i - 1) {
    dp[i + k][k] = (dp[i + k][k] + 1ll * dp[i][j] * c[n - i - 1][k] % m * a[j][k] % m * b[k] % m) % m;
  }
  int ans = 0;
  rep (i, 1, n - 1) ans = (ans + 1ll * dp[n - 1][i] * (mi[i] - 1) % m) % m;
  write(ans);
}
```

---

## 作者：王熙文 (赞：0)

场上有思路但是写挂了 /fn，挂在了最觉得不会错的地方。写一篇题解记录一下做法，这种题比较经典。

## 思路

考虑对每一个 $dis$ 相等的层进行 dp。

先不考虑 $n$。设 $dp_{i,j}$ 表示一共有 $i$ 个点（包含 $1$ 号节点），最深的层中有 $j$ 个点时的图的方案数。这样的状态看起来比较别扭，因为没有一共有多少层这一维（实际上不需要），可以想象成在距离排序后的数组上 dp，没有段数要求的线性 dp 是不需要一共分了多少段这一维的。

首先，这一层选点的方案数为 $i-1$（不能选 $1$ 号节点）中选 $j$ 个点，即 $C_{i-1}^j$。

连边只存在于同层或相邻两层之间，因为如果有跨层的连边，则其中有一个点一定不属于它那一层了。所以考虑枚举上一层的点数 $k$。先处理层与层之间的连边。对于每一个当前层的点，都需要连到上一层至少一条边，所以两层之间连边的总方案数为 $(2^k-1)^j$。还有一种情况，即同层的连边。同层的一共有 $\dfrac{j(j-1)}{2}$ 条边，每条边都可连可不连，所以方案数是 $2^{\frac{j(j-1)}{2}}$。这样，转移就出来了：

$$dp_{i,j}=C_{i-1}^j \times 2^{\frac{j(j-1)}{2}} \times \sum_{k=1}^{i-j} dp_{i-j,k} \times (2^k-1)^j$$

最后，只要选了 $n-1$ 个点，都会产生贡献。最后一层要选至少一个点连到 $n$，所以当前的方案数为 $dp_{n-1,j} \times (2^j-1)$。最后的答案为：

$$\sum_{j=1}^{n-1} dp_{n-1,j} \times (2^j-1)$$

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,mod;
int dp[510][510];
int pow2[1000010],c[510][510];
int qpow(int a,int b)
{
	int ans=1;
	while(b)
	{
		if(b&1) ans=ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ans;
}
int ycl[510][510];
signed main()
{
	cin>>n>>mod;
	pow2[0]=1; for(int i=1; i<=1e6; ++i) pow2[i]=pow2[i-1]*2%mod;
	c[0][0]=1;
	for(int i=1; i<=500; ++i) for(int j=0; j<=500; ++j) c[i][j]=(c[i-1][j]+(!j?0:c[i-1][j-1]))%mod;
	for(int i=1; i<=500; ++i) for(int j=1; j<=500; ++j) ycl[i][j]=qpow(pow2[i]-1,j);
	dp[1][1]=1;
	int ans=0;
	for(int i=2; i<=n-1; ++i)
	{
		for(int j=1; j<i; ++j)
		{
			for(int k=1; k<=i-j; ++k)
			{
				dp[i][j]=(dp[i][j]+dp[i-j][k]*ycl[k][j])%mod;
			}
			dp[i][j]=dp[i][j]*c[i-1][j]%mod*pow2[j*(j-1)/2]%mod;
			if(i==n-1) ans=(ans+dp[i][j]*(pow2[j]-1+mod))%mod;
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Raisetsu41 (赞：0)

图的计数问题要注意一些定理的使用和从生成树的角度思考，看到题目中有对于距离的限制，考虑把每一层分开，使得 $1$ 在最深的一层，那么此时计数就简单了，定义 $dp_{i, j}$ 表示用了前 $i$ 个点，后面的 $j$ 个点分在一层时的方案数，主要到并没有考虑现在是第几层，因为计数的原则只要是问题答案等价且转移后的状态合法就可以了，那么转移就变成了当前层自身连边和向上一层连边，方程是   
$$dp_{i, j} = \sum_{k = 1}^{i - j} dp_{i - j, k} \times \binom{n - 1 - i + j}{j} \times (2^{k} - 1)^j \times 2^{j\times(j - 1)}$$

---

