# Unicyclic Graph Counting

## 题目描述

### 题目大意
求有多少$N$个点的环套树，满足第$i$个点的度数为给定的$d_i$。答案对$10^9+7$取模。

环套树是一个$n$个点、$n$条边的简单（无重边、无自环）联通无向图。

## 说明/提示

- $3 \le N \le 300$
- $1 \le d_i \le N - 1$
- $\Sigma{d_i} = 2N$

翻译提供者：浮尘ii

## 样例 #1

### 输入

```
5
1 2 2 3 2```

### 输出

```
6```

## 样例 #2

### 输入

```
16
2 1 3 1 2 1 4 1 1 2 1 1 3 2 4 3```

### 输出

```
555275958```

# 题解

## 作者：Yahbim (赞：15)

因为环上节点不成为叶子，根据 prufer 序性质，最后只剩下环、以及环旁边某一个点。

普通的无根树 prufer 序中，每个节点都出现 $deg_i-1$ 次，设 prufer 序即无根树形态有 $ret$ 种，那么 $ret=\dfrac{(n-2)!}{\prod (d_i-1)!}$。而基环树上略有不同：

1. 树节点出现 $deg_i-1$ 次
2. 环节点出现 $deg_i-2$ 次
3. 环旁边最后剩下的那一个点相邻的环节点出现 $deg_i-3$ 次

设环为点集 $S$，情况3中的特殊环节点为 $p$，列出式子为：

$\begin{aligned}
&ret=\dfrac{(n-|S|-1)!}{\prod(deg_i-k)!},k=\left\{
	\begin{array}{l}
    	1 & i\notin S\\
        2 & i\in S,i\ne p\\
        3 & i=p
    \end{array}	
\right.    
\end{aligned}$

于是

$\begin{aligned}
ans&=\sum\limits_S ret(|S|-1)!/2\\
&=\sum\limits_{|S|} [\frac{1}{\sum\limits_{T,|T|=|S|}\prod\limits_{i\in T}(deg_i-k)!}(n-|S|-1)!(|S|-1)!/2]
\end{aligned}$

其中 $k$ 的含义同前所述， $ans$ 即为输出结果。因为这样生成的 prufer 序实际上只是 $|S|$ 个无根树的排列，所以还要乘上环的排列，即 $(|S|-1)!/2$。

外层枚举 $|S|$ ，剩下的就在于如何求 $\sum\limits_{|T|=|S|}\prod\limits_{i\in T}(deg_i-k)!$ 了。以 $deg$ 为值，我们关心的条件有：参与决策的结点在 $[1,n]$ 中，环的大小为 $|S|$，且有一个特殊环节点。用这三个维度DP。设计状态 $f_{i,j,k}$ 表示当前参与决策的点在 $[1,i]$ 中，环上有 $j$ 个点，已有 $k$ 个特殊环节点， $i,j\leq n,k\leq 1$。转移方程为：

$\begin{aligned}
	f_{i,j,k}=\left\{
    	\begin{array}{l}
    	f_{i,j,k}+f_{i-1,j,k}\times(deg_i-1)! & deg_i\geq 1\\
        f_{i,j,k}+f_{i-1,j-1,k}\times(deg_i-2)! & deg_i\geq 2\\
        f_{i,j,k}+f_{i-1,j-1,0}\times(deg_i-3)! & deg_i \geq 3,k=1
        \end{array}
    \right.
\end{aligned}
$

这道题就做完了。代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=305;const ll P=1e9+7;
int read(){
    int ret=0;char ch=getchar();
    while(!isdigit(ch)) ch=getchar();
    while(isdigit(ch)) ret=ret*10+ch-'0',ch=getchar();
    return ret;
}

int n,deg[N];
ll fac[N],inv[N],facinv[N],f[N][N][2],ans;

void init(){
    fac[0]=fac[1]=inv[1]=facinv[0]=facinv[1]=1;
    for(int i=2;i<=n;++i){
	    fac[i]=fac[i-1]*i%P;
	    inv[i]=(P-P/i)*inv[P%i]%P;
	    facinv[i]=facinv[i-1]*inv[i]%P;
    }
}

int main(){
    n=read();
    for(int i=1;i<=n;++i) deg[i]=read();
    init();
    for(int i=1,crl=1;i<=n;++i){
	    crl&=deg[i]==2;
	    if(i==n&&crl) printf("%lld\n",fac[n-1]*inv[2]%P),exit(0);
    }
    f[0][0][0]=1;
    for(int i=1;i<=n;++i)
	    for(int j=0;j<=i;++j)
	        for(int k=0;k<=1;++k){
	         	if(deg[i]>=1)
	         	    f[i][j][k]+=f[i-1][j][k]*facinv[deg[i]-1],f[i][j][k]%=P;
		        if(deg[i]>=2)
		            f[i][j][k]+=f[i-1][j-1][k]*facinv[deg[i]-2],f[i][j][k]%=P;
	        	if(deg[i]>=3&&k)
		            f[i][j][1]+=f[i-1][j-1][0]*facinv[deg[i]-3],f[i][j][1]%=P;
	        }
    for(int i=3;i<=n;++i)
	    ans+=f[n][i][1]*fac[n-i-1]%P*fac[i-1]%P*inv[2]%P,ans%=P;
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：Binary_Search_Tree (赞：9)

#### [题目传送门](https://www.luogu.com.cn/problem/AT3617)

看题目很容易想到prufer序。但本题计算的是环的数量，如何处理环呢？

可以只删除树不删除环，把树删完后的prufer序作为最终prufer序。

因为prufer序要求最终留下两个点，所以我们最终留下一个环和一个和环相邻的编号最大的点。

容易看出如果环大小为$k$,我们可以由新的prufer序还原出$\frac{(k-1)!}{2}$个环套树。（即环的排列方案）

在新的prufer序中树上节点出现$d-1$次，环上一个节点出现$d-3$次,其他节点出现$d-2$次。

设环大小为$k$，则prufer序有$\frac{(n-k-1)!}{\prod d_i!}$种。因此可以DP$\frac{1}{\prod d_i!}$的值

设$f_{i,j,k}$表示当前已经选了$i$个点，$j$个是环点，是否选了度数为$d-3$的环点

最后求$\sum\limits_{i=3}^{n-1}f_{n,i,1}(n-i-1)!\frac{(i-1)!}{2}$即可。

注意上面的规律对整个$n$个点构成环的情况不成立（因为没有度数$\ge 3$
的点)，需要特判。

代码:

```cpp
#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
#define M 5005
#define mod 1000000007
int n,D[M];
long long fac[M],inv[M],fac_inv[M],F[M][M][2],ans;
int read(){
	char c=getchar();int ans=0;
	while (c<'0'||c>'9') c=getchar();
	while (c>='0'&&c<='9') ans=ans*10+c-'0',c=getchar();
	return ans;
}
void Write(long long x){
	if (x<10) putchar(x^48);
	else Write(x/10),putchar((x%10)^48);
	return;
}
int main(){
	n=read();bool flag=1;
	fac[0]=fac[1]=inv[1]=fac_inv[0]=fac_inv[1]=1;
	for (register int i=2;i<=n;i++)
		fac[i]=fac[i-1]*i%mod,
		inv[i]=(mod-mod/i)*inv[mod%i]%mod,
		fac_inv[i]=fac_inv[i-1]*inv[i]%mod;
	for (register int i=1;i<=n;i++) D[i]=read(),flag&=(D[i]==2);
	if (flag){Write(fac[n-1]*inv[2]%mod);return 0;}//特判
	F[0][0][0]=1;
	for (register int i=0;i<n;i++)
		for (register int j=0;j<=i;j++)
			for (register int k=0;k<2;k++){
				if (D[i+1]>0)//树点
					F[i+1][j][k]=(F[i+1][j][k]+F[i][j][k]*fac_inv[D[i+1]-1])%mod;
				if (D[i+1]>1)//普通环点
					F[i+1][j+1][k]=(F[i+1][j+1][k]+F[i][j][k]*fac_inv[D[i+1]-2])%mod;
				if (D[i+1]>2&&!k)//特殊环点
					F[i+1][j+1][1]=(F[i+1][j+1][1]+F[i][j][k]*fac_inv[D[i+1]-3])%mod;
			}
	for (register int i=3;i<n;i++)
		ans=(ans+F[n][i][1]*fac[n-i-1]%mod*fac[i-1]%mod*inv[2])%mod;
	Write(ans);
	return 0;
}

```


---

## 作者：EuphoricStar (赞：4)

看到和度数有关的（基环）树计数，可以想到 Prufer 序。

如果要计数一棵树，那么答案就是 $\binom{n - 2}{d_1 - 1, d_2 - 1, \ldots, d_n - 1}$。因为度数为 $d$ 的点在 Prufer 序中恰好出现 $d - 1$ 次。

但是现在是基环树。特判掉 $\forall i \in [1, n], d_i = 2$，然后考虑把环缩成一个点。求树的 Prufer 序最后会剩下两个点，那么这里会剩下一个环往外连一个单点。

设环长为 $k$，若已经确定了环上点的标号集合，那么方案数为 $\frac{(k - 1)!}{2}$。$(k - 1)!$ 是长度为 $k$ 的圆排列数，乘 $\frac{1}{2}$ 是减掉翻转同构的环。

那么有 $k - 1$ 个点在 Prufer 序中出现 $d_i - 2$ 次，$1$ 个特殊点（环上连了一个单点的点）在 Prufer 序中出现 $d_i - 3$ 次，其余点（树点）出现 $d_i - 1$ 次，Prufer 序长度为 $n - |S| - 1$。

那么若确定环点集合 $S$，特殊点为 $u$，那么答案为：

$$\frac{(n - |S| - 1)!}{(\prod\limits_{i \in S \land i \ne u} (d_i - 2)!) (d_u - 3)! (\prod\limits_{i \notin S} (d_i - 1)!)} \times \frac{(|S| - 1)!}{2}$$

考虑 dp 出 $\sum\limits_{S, u} \frac{1}{(\prod\limits_{i \in S \land i \ne u} (d_i - 2)!) (d_u - 3)! (\prod\limits_{i \notin S} (d_i - 1)!)}$。设 $f_{i, j, 0/1}$ 表示考虑了 $i$ 个点，其中有 $j$ 个环点，有没有出现特殊点，前面式子之和。

转移就讨论第 $i$ 个点是环点还是特殊点还是树点即可。答案为：

$$\sum\limits_{i = 3}^{n - 1} (n - i - 1)! f_{n, i, 1} \times \frac{(i - 1)!}{2}$$

时间复杂度 $O(n^2)$。

[code](https://atcoder.jp/contests/cf17-tournament-round3-open/submissions/45976877)

---

## 作者：Garrison (赞：1)

# 提供推导思路
## 前提概要：
在做这道题之前可以先做一下[P2290 [HNOI2004]树的计数](https://www.luogu.com.cn/problem/P2290)主要是来熟悉一个定理：

对于给定度数为 $d_{1\sim n}$ 的一棵无根树共有 $\dfrac{(n-1-1)!}{\prod_{i=1}^n (d_i-1)!}$ 种情况。

因为度数为 $d_i$ 的结点会在 $prufer$ 序列中出现 $d_i-1$ 次,实际上就是多重集合的全排列。

## 正文
### 先不看环
也就是感性理解将环缩为一个点,弄掉，剩下的就是一棵树。

设环的大小为 $L$ ，根据前提概要中的公式，那么
共有 $\dfrac{(n-L-1)!}{\prod_{i=1}^n (d_i-1)!}$ 种情况。

根据圆排列的公式，从 $n$ 个不同元素中不重复地取出 $m(1 \le m \le n)$ 个元素在一个圆周上，叫做这 $n$ 个不同元素的圆排列。如果一个 $m$ 圆排列旋转可以得到另一个 $m$ 圆排列，则认为这两个圆排列相同。特别地，当 $m=n$ 时， $n$ 个不同元素作成的圆排列总数为 $(n-1)!$ 。

**但是，因为这是在一棵树上，所以不能根据某种对称性(可以感性理解下)，需要对圆排列总数 $/2$ ，即 $\frac{(n-1)!}{2}$ 。**


### 那么对于环，
不难发现环的大小一共可能为 $3\sim n-1$ 种。

同时根据特殊性质，根据在 $prufer$ 序列中出现次数与给出度数关系，有三种不同的点：

普通树上的点出现 $d_i-1$ 次。

环上的普通点出现 $d_i-2$ 次。

环上的某一个点出现 $d_i-3$ 次。

### 综合起来
$ans=\sum_{L=3}^{n-1} \dfrac{(n-L-1)!}{\prod Di!}\dfrac{(L-1)!}{2}$ 。

其中 $Di$ 表示根据三种不同点的出现次数(前文已经提及)， $i$ 的范围由环的点集范围决定(后面会讲如何递推)。

对于一个大小为 $L$ 的环，很明显可以先预处理出：

$\dfrac{(n-L-1)!(L-1)!}{2}$

至于 $\dfrac{1}{\prod Di!}$ 可以用类似与树的计数递推组合数的思想，

设计状态 $f_{i,j,k}$ ，其中 $i,j,k$ 表示 $i$ 个点中，环上有 $j$ 个点，已有 $k$ 个特殊环节点。

感觉别的题解应该对于状态的转移讲得比较清楚，那么本篇就补充一下状态的设计思路(即如何想到的)：

根据点的分类和特殊性考虑设计三维的状态，毫无疑问第一维需要统计一共用了多少个点，又因为环套树中环的特殊性，以及统计方式的不同，可以设计出第二维为环上选了多少个点，再根据环上特殊点的**特特特**殊性，用 $0/1$ 判断是不是即可。

最后根据转移即可统计出 $\sum_{L=3}^{n-1}f_{n,i,1}$ .

### 最后，记得用逆元。

---

## 作者：Missa (赞：0)

给一种题解区没有的做法。

我不会 prufer 的构造也不了解带环的 prufer 诶，能不能把它当成黑箱呢。

缩环，假设确定环上点的集合为 $S$，环的度数为 $\sum_{i \in S} (d_i - 2)$，串成环的方案数是 $\dfrac{(|S|-1)!}{2}$，缩环后的树有 $\dfrac{(n - |S|-1)!}{\prod_{i \not\in S} (d_i - 1)! (\sum_{i \in S} (d_i-2) - 1)!}$ 种，注意到与环直接相连的点视作等价，还需要分进 $|S|$ 个等价类中，方案数还需要乘上 $\dfrac{(\sum_{i \in S} (d_i-2))!}{\prod_{i \in S} (d_i - 2)!}$。这里认为阶乘优先级高于求和求积号。

写起来是

$$
\begin{aligned}
& \dfrac{(|S|-1)!}{2} \dfrac{(n - |S| - 1)!}{\prod_{i \not\in S} (d_i - 1)! (\sum_{i \in S} (d_i-2) - 1)!} \dfrac{(\sum_{i \in S} (d_i-2))!}{\prod_{i \in S} (d_i - 2)!} \\
= & \dfrac{(|S|-1)!}{2} \dfrac{(n - |S| - 1)!}{\prod_{i \not\in S} (d_i - 1)!} \dfrac{\sum_{i \in S} (d_i-2)}{\prod_{i \in S} (d_i - 2)!}
\end{aligned}
$$

$f_{i, j, s}$：考虑前 $i$ 数，$|S|=j$，$\sum_{i \in S} d_i=s$，$\dfrac{1}{\prod_{i \not\in S} (d_i - 1)!\prod_{i \in S} (d_i - 2)!}$ 值之和。转移时枚举 $i$ 是否放入 $S$ 集合内，特殊情况是 $d_i = 1$ 时不能放入 $S$。初始化是 $f_{0, 0, 0} = 1$。

转移 $O(1)$，总复杂度 $O(n^3)$，需要一对滚动数组，还需要判 $|S| = n$。

```cpp
#include <bits/stdc++.h>

const int mod = 1e9 + 7;

int qpow(int a, int b) {
  int ans(1);
  for (; b; b >>= 1) {
    if (b & 1) ans = 1ll * ans * a % mod;
    a = 1ll * a * a % mod;
  }
  return ans;
}

std::vector<int> fac, ifac, inv;

void pre(int n) {
  fac.resize(n + 1), ifac.resize(n + 1), inv.resize(n + 1);
  fac[0] = ifac[0] = fac[1] = ifac[1] = inv[1] = 1;
  for (int i = 2; i <= n; i++) {
    fac[i] = 1ll * fac[i - 1] * i % mod;
    inv[i] = 1ll * inv[mod % i] * (mod - mod / i) % mod;
    ifac[i] = 1ll * ifac[i - 1] * inv[i] % mod;
  }
}

void add(int &x, int y) { if ((x += y) >= mod) x -= mod; }

int main() {
  int n; scanf("%d", &n);
  std::vector<int> d(n);
  bool c = 1;
  for (int &u : d) scanf("%d", &u), c &= u == 2;
  pre(n);
  if (c) return printf("%d\n", 1ll * fac[n - 1] * (mod + 1) / 2 % mod), 0;
  std::vector f(2, std::vector (n, std::vector<int> (2 * n))); // |S| < n，不用开全
  int o = 0;
  f[0][0][0] = 1;
  for (int i = 0; i < n; i++, o ^= 1) {
    f[o ^ 1] = std::vector<std::vector<int>> (n, std::vector<int> (2 * n));
    for (int j = 0; j <= i; j++) 
      for (int s = 0; s < 2 * n; s++) if (f[o][j][s]) {
        if (d[i] > 1) 
          add(f[o ^ 1][j + 1][s + d[i]], 1ll * f[o][j][s] * ifac[d[i] - 2] % mod);
        add(f[o ^ 1][j][s], 1ll * f[o][j][s] * ifac[d[i] - 1] % mod);
      }
  }
  int ans = 0;
  for (int i = 3; i < n; i++) 
    for (int j = 2 * i; j < 2 * n; j++) 
      add(ans, 1ll * fac[i - 1] * fac[n - i - 1] % mod * inv[2] % mod * (j - 2 * i) % mod * f[o][i][j] % mod);
  printf("%d\n", ans);
  return 0;
}
/*
stupid mistakes:
  - 清空滚动数组
  - ifac[i] = 1ll * ifac[i] * inv[i] % mod;
  - return printf(), 0;
*/
```

---

