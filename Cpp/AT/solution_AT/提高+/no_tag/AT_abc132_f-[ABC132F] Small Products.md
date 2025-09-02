# [ABC132F] Small Products

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc132/tasks/abc132_f

正の整数 $ K $ 個を一列に並べたものであって、隣接して並んでいるどの $ 2 $ つの整数の積も $ N $ 以下であるものの個数を $ 10^9+7 $ で割った余りを求めてください。

## 说明/提示

### 制約

- $ 1\leq\ N\leq\ 10^9 $
- 1 $ 2\leq\ K\leq\ 100 $ (21:33 修正)
- $ N,K $ は整数である

### Sample Explanation 1

$ (1,1),(1,2),(1,3),(2,1),(3,1) $ が条件を満たします。

## 样例 #1

### 输入

```
3 2```

### 输出

```
5```

## 样例 #2

### 输入

```
10 3```

### 输出

```
147```

## 样例 #3

### 输入

```
314159265 35```

### 输出

```
457397712```

# 题解

## 作者：Orange_qwq (赞：17)

[洛谷传送门](https://www.luogu.com.cn/problem/AT_abc132_f) && [AT 传送门](https://atcoder.jp/contests/abc132/tasks/abc132_f)

奇妙的根号优化 $\text{dp}$。

# 思路

## $\text{Step 1}$

要求相邻乘积不超过 $n$ 的序列总数，好像关系到一点排列组合。既然答案是累加的，那么很容易想到递推。

然后再想想。似乎有一个东西：对于一定的 $n$，如果前面一个数填的是 $x(x \le n)$，那么填的下一个数必然 $\le \dfrac{n}{x}$。显然，对于 $k$ 个数，答案是累加的。


设 $f_{i,j}$ 表示第 $i$ 个数填 $j$ 的方案总数，$\text{dp} $ 式子如下：

$$ f_{i,j} = \sum^{\lfloor \frac{n}{j} \rfloor}_{x = 1}f_{i - 1,x}$$

## $\text{Step 2}$

上面的 $\text{dp} $ 式子复杂度明显会超时。

考虑优化。

看着式子的 $x$ 和 $\lfloor \dfrac{n}{j} \rfloor$，好像可以优化点什么东西。

如果是下取整的话，那就会出现有好多个数乘上同一个数符合要求。例如，设 $n = 100,j=2$，那么 $x$ 的取值可以是从 $34$ 一直到 $50$。一个数列里必定会有许多如此的“块”，我们可以提前预处理出来，$\text{dp} $ 的时候复杂度就能达到 $O(\sqrt n k)$，足够通过此题。

搞出了优化方法，还要改一下 $\text{dp} $ 式子。设 $cnt$ 为上述预处理出来的“块”的个数，$len_i$ 表示每个“块”的长度（即一个因数相等，符合要求的另一个数的个数），则

$$f_{i,j} = \sum^{cnt}_{x = 1}f_{i - 1,\texttt{所在块的下标}} \times len_x$$

# $\text{AC Code}$

不要忘了取模。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int p = 1e9 + 7;
int n, cnt, k, a[100010], len[100010];
ll f[110][100010];
map < int, int > b;
int main() {
	scanf("%d %d", &n, &k);
	for (int l = 1, r; l <= n; l = r + 1) {
		r = min(n / (n / l), n);
		a[++cnt] = r, b[r] = cnt; // a[i] 表示第 i 块的因数  b[i] 是装下标的桶 
		len[cnt] = r - l + 1;
	}
	for (int i = 1; i <= cnt; ++i) f[0][i] = 1;
	for (int i = 1; i <= k; ++i) 
		for (int j = 1; j <= cnt; ++j) 
			f[i][j] = (f[i][j - 1] + (ll)len[j] * f[i - 1][b[n / a[j]]] % p) % p;
	printf("%lld", f[k][cnt]);
	return 0;
}
```


---

## 作者：Lskkkno1 (赞：11)

- [AT4817 [ABC132F] Small Products](https://www.luogu.com.cn/problem/AT4817)

### 题目描述

给定 $N$, $K$，问有多少个长度为 $K$ 的正整数序列满足相邻元素的乘积不超过 $N$。

### 正解

考虑递推，设 $f_{i,j}$ 表示第 $i$ 个位置填 $j$ 的方案数。

然而值域实在太大，要将所有数存下来实在不太可行。

考虑有哪些状态本质上是相同的。

序列中一个元素 $a_i$，可以转移到下一个位置 $a_{i + 1} \leq \lfloor N / a_i \rfloor$，发现 $\lfloor N / a_i \rfloor$ 只有 $\sqrt N$ 种取值，可以直接记录下来。

那么将 $a_i \le \sqrt N$，$a_i > \sqrt N$ 分别记录即可。

转移要用前缀和优化一下，实现的时候可以从大往小枚举记录前缀和 / 后缀和。

时间复杂度 $O(K \sqrt N)$

$\color{DeepSkyBlue} {Code :}$

```cpp
#include <bits/stdc++.h>
#define N 105
#define V 31627

using namespace std;

const int mod = 1e9 + 7;

int n, K;
int f[N][V], g[N][V];
int cnt[V];

int main() {
	scanf("%d %d", &K, &n); /* 把 n, k 的定义反了一下*/
	
	int p = sqrt(K);
	
	for(int i = 1; i < p; ++i)
		cnt[i] = K / i - K / (i + 1);
	cnt[p] = K / p - p;
	
	for(int i = 1; i <= p; ++i) {
		f[1][i] = 1;
		g[1][i] = cnt[i];
	}
	
	for(int i = 1; i <= n; ++i) {
		int sum = 0;
		for(int j = 1; j <= p; ++j) {
			sum = (sum + f[i][j]) % mod;
			g[i + 1][j] = 1LL * sum * cnt[j] % mod;
		}
		for(int j = p; j >= 1; --j) {
			sum = (sum + g[i][j]) % mod;
			f[i + 1][j] = sum;
		}
	}
	
	printf("%d\n", f[n + 1][1]);
	return 0;
}
```

---

## 作者：极寒神冰 (赞：10)

令$dp[i][x]$，表示第$i$个位置填$x$的方案数。

显然有$dp[i+1][x]=\sum_{z=1} ^ {\lfloor \frac{N}{x} \rfloor} dp[i][z]$

使用前缀和优化，但这样复杂度仍然是是$O(n)\times O(k)=O(nk)$的，由于$k<=100,n<=10^9$ ，显然过不了。

考虑进行优化。

假设有两个正整数$x$,$y$满足$\lfloor \frac{n}{x} \rfloor =\lfloor \frac{n}{y} \rfloor = t$ 可以发现$dp[i+1][x]=dp[i+1][y]$ 。

这里介绍一下**数论分块** (来自[oi-wiki](https://oi-wiki.org/math/mobius/#_3))

![](https://cdn.luogu.com.cn/upload/image_hosting/ct3ut44w.png)

如计算$\sum_{i=1}^n \lfloor \frac{n}{i} \rfloor$

代码

```c++
for(int l=1,r;l<=n;l=r+1)
{
	r=n/(n/l);
	ans+=(r-l+1)*(n/l);
}
```

例题[[CQOI2007]余数求和](https://www.luogu.com.cn/problem/P2261)

那么对于本题我们只需要计算$\sqrt n$个状态，复杂度降为$O(k\sqrt n)$，可以通过本题。



---

## 作者：hyxgg (赞：7)

[题目](https://www.luogu.com.cn/problem/AT_abc132_f)

## 思路

首先考虑一个暴力的 `DP`，我们用 $dp_{i,j}$ 表示长度为 $i$，结尾为 $j$ 时的方案数，

动态转移方程为：
$$dp_{i,j}=\sum_{p=1}^{\lfloor \frac{n}{j} \rfloor}dp_{i-1,p}$$

就算加个前缀和优化，时间复杂度也为 $\mathcal{O}(nk)$，显然过不了，怎么办呢？

注意到 $dp_{i,j_1}$ 和 $dp_{i,j_2}$ 在 $\lfloor \frac{n}{j_1} \rfloor = \lfloor \frac{n}{j_2} \rfloor$ 时是相等的，
不妨将他们放在一起算。

我们先用整除分块处理出 $n$ 作为被除数，且除数不超过 $n$ 的所有的商（此处指带余数除法的商，下文亦然），用 $s_i$ 表示第 $i$ 小的那个商，个数设为 $sd$。同时处理出其对应的除数的个数，用 $g_i$ 表示。



则状态优化为 $dp_{i,j}$，$i$ 仍为长度，$j$ 为 $n$ 除以序列最后值的商。

先不急着求状态转移方程，我们先证一个引理：对于所有 $i \in [1,sd]$，有：
$$\lfloor \frac{n}{s_i} \rfloor=s_{sd-i+1}$$

易证对于 $i \in [1,sd]$，有：
$$\lfloor \frac{n}{\lfloor\frac{n}{s_i}\rfloor}\rfloor=s_i$$

从整除分块的过程中观察，这是显而易见的，不再赘述。


可以确定对于 $s_1$ 和 $s_{sd}$ 有：
$$\lfloor \frac{n}{s_1} \rfloor=s_{sd}$$
和
$$\lfloor \frac{n}{s_{sd}} \rfloor=s_1$$
因为 $s_1$ 一定为一，$s_{sd}$ 一定为 $n$。

需要先解释一下的是，对于 $i \in [1,sd]$，一定有某个 $j \in [1,sd]$ 满足
$\lfloor \frac{n}{s_i} \rfloor=s_{j}$。因为 $\lfloor \frac{n}{s_i} \rfloor$ 也是 $n$ 作为某个被除数的一个商，一定包含在 $s$ 中。

假设对于 $i$ 已知 $j$，使得 $\lfloor \frac{n}{s_{j}}\rfloor=s_i$，则 $\lfloor \frac{n}{s_{i}} \rfloor=s_j$。

设 $x$ 使得 $\lfloor \frac{n}{s_{i+1}} \rfloor=s_{x}$，则$\lfloor \frac{n}{s_{x}} \rfloor=s_{i+1}$。

先证 $x<j$：

因为 
$$\lfloor \frac{n}{s_{j}} \rfloor=s_i$$
同时
$$s_i<s_{i+1}$$

所以 $s_x<s_j$，即 $x<j$。

然后我们采用反证法，假设 $x<j-1$。

考虑 $\lfloor \frac{n}{s_{j-1}} \rfloor$ 在 $s$ 中的位置，先设其为 $k$。

因为 
$$x<j-1<j$$
所以有
$$\lfloor \frac{n}{s_{j}} \rfloor\le\lfloor \frac{n}{s_{j-1}} \rfloor \le\lfloor \frac{n}{s_{x}}\rfloor$$

结合上面的 $\lfloor \frac{n}{\lfloor\frac{n}{s_i}\rfloor}\rfloor=s_i$，
当 $\lfloor \frac{n}{s_{j}} \rfloor=\lfloor \frac{n}{s_{j-1}} \rfloor$ 或 $\lfloor \frac{n}{s_{j-1}} \rfloor=\lfloor \frac{n}{s_{x}} \rfloor$ 时，一定有 $j=j-1$ 或 $j-1=x$，与前面矛盾。

所以
$$\lfloor \frac{n}{s_{j}} \rfloor<\lfloor \frac{n}{s_{j-1}} \rfloor <\lfloor \frac{n}{s_{x}} \rfloor$$
也就是
$$s_i<s_k<s_{i+1}$$

显然不存在这样的 $k$，同时有 $x<j$，所以
$$x=j-1$$

所以当 $\lfloor \frac{n}{s_{i}} \rfloor=s_j$ 时，有：
$$\lfloor \frac{n}{s_{i+1}}\rfloor=s_{j-1}$$

现在我们已经确定了 $\lfloor \frac{n}{s_{1}} \rfloor=s_{sd}$

进而有 
$$\lfloor \frac{n}{s_{2}} \rfloor=s_{sd-1}$$
$$\lfloor \frac{n}{s_{3}} \rfloor=s_{sd-2}$$
$$\dots$$
$$\lfloor \frac{n}{s_{i}} \rfloor=s_{sd-i+1}$$
故引理得证。

现在我们就可以写出状态转移方程了：

对于 $i\in[1,k],j\in[1,sd]$
$$dp_{i,j}=\sum_{k=sd}^{sd-j+1} dp_{i-1,k}\times g_j$$

再加个前缀和优化，时间复杂度为 $\mathcal{O}(k\sqrt{n})$。

## 代码
```
#include<iostream>
#include<cstdio>
#include<map>
#define ll long long
#define mod 1000000007
using namespace std;
ll cs[100005],cd,cg[100005],n,k,dp[105][100005];
int main(){
    scanf("%lld%lld",&n,&k);
    for(ll i=1;i<=n;i++){
        cs[++cd]=n/i;
        ll ni=n/(n/i);
        cg[cd]=ni-i+1;
        i=ni;
    }
    for(ll i=1;i<=cd;i++){
        dp[1][i]=cg[i];
    }
    for(ll i=2;i<=k;i++){
        ll qz=0,d=0;
        for(ll j=cd;j>=1;j--){
            d++;
            qz+=dp[i-1][d];
            qz%=mod;
            dp[i][j]=qz*cg[j];
            dp[i][j]%=mod;
        }
    }
    ll ans=0;
    for(ll i=1;i<=cd;i++){
        ans+=dp[k][i];
        ans%=mod;
    }
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：tour1st (赞：5)

#### 题目大意


------------
求有多少长度为 $k$ 的正整数序列满足任意相邻两数乘积不大于 $n$。



------------
最暴力的解法是设计状态 $f_{i,j}$ 表示第 $i$ 个数为 $j$ 的方案数。

$f_{i,j} = \sum_{k=1}^{\left \lfloor \frac{n}{j} \right \rfloor } f_{i-1,k}$

一个显然的优化是记录前缀和将复杂度降至 $\Theta(nk)$，但这还远不足以通过此题。

考虑合并本质相同的状态以降低复杂度。

不难发现由于 $n$ 是固定的，假设存在两不同正整数 $a,b$ 满足 $\left \lfloor \frac{n}{a} \right \rfloor = \left \lfloor \frac{n}{b} \right \rfloor $ 则一定有 $f_{i,a} = f_{i,b}$，这就是本质相同的状态。

考虑将所有 $\left \lfloor \frac{n}{i} \right \rfloor$ 相同的状态合并，因为它们都可以由同样的状态转移。

首先考虑如何找出这些状态，这里提供一种容易理解的[数论分块](https://oi-wiki.org/math/number-theory/sqrt-decomposition/)方法：

一个显然的结论是所有满足 $\left \lfloor \frac{n}{i} \right \rfloor = k$ 的 $i$ 一定是连续的，考虑找出一段区间使得这段区间中的数都满足 $\left \lfloor \frac{n}{i} \right \rfloor=k$。

假设已知 $\left \lfloor \frac{n}{i} \right \rfloor=k$，问题就转化为求最大的满足 $\left \lfloor \frac{n}{i} \right \rfloor=k$ 的 $i$。

设 $j$ 即为满足题设的最大 $i$，可知 $\left \lfloor \frac{n}{i} \right \rfloor = \left | \frac{n}{j} \right | $ 即 $j$ 为整除 $n$ 的数。

令 $n = pi+q \Rightarrow p = \left | \frac{n}{j} \right | \Rightarrow j = \frac{n}{p}=\frac{n}{\left \lfloor \frac{n}{i} \right \rfloor}$。

至此，就可以求出这段区间的左右边界，可知 $n$ 最多存在 $2\sqrt{n}$ 个区间。

所以只需将状态 $f_{i,j}$ 更改为第 $i$ 个数在第 $j$ 个区间的方案数，记 $cnt$ 为区间总数，则 $f_{i,j}=\sum_{1}^{cnt-k+1}f_{i,k}$，前缀和优化一下就可以通过此题,时间复杂度 $\Theta(\sqrt{n}k)$。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<cmath>
#include<queue>
#include<map>
#include<vector>
#define int long long
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
const int N = 1e5 + 10;
const int M = 1e3 + 10;
inline int read(){
	int x=0,f=1;char ch=getchar();
	for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=-1;
	for(; isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+ch-'0';
	return x*f;
}
int f[110][N],pre[110][N];
int siz[N],idx;
signed main(){
	int n = read() , k = read();
	int l=1,r=0;
	while(l <= n){
		r = n / (n / l);
		siz[++idx] = r - l + 1;
		l = r + 1;
	}
	for(int i=1;i<=idx;i++){
		f[1][i] = siz[i] % mod, pre[1][i] = (pre[1][i-1] + f[1][i]) % mod;
	}
	for(int i=2;i<=k;i++){
		for(int j=1;j<=idx;j++){
			f[i][j] = (siz[j] * pre[i-1][idx-j+1]) % mod;
			pre[i][j] = (pre[i][j-1] + f[i][j]) % mod;
		}
	}
	cout<<pre[k][idx]<<"\n";
	return 0;
}

/*
314159265 35

457397712
*/
```


---

## 作者：Rannio (赞：4)

### 题意
一句话题意不用再翻译了吧。

### 思路
先考虑朴素的 dp，设 $dp_{i,j}$ 表示长度为 $i$ 结尾数字为 $j$ 的序列的方案数，状态很好转移：
$$dp_{i,j}=\sum_{a=1}^{\lfloor \frac{N}{j} \rfloor}dp_{i-1,a}$$
这样时间复杂度是 $\Theta(nk)$ 的，显然过不了。

考虑优化这个 dp。  
我们发现 $\lfloor \frac{N}{j} \rfloor$ 在一段区间内的值是一样的，自然想到整除分块。  
我们预处理出每一块的 $\lfloor \frac{N}{j} \rfloor$ 值 $m_i$、长度 $len_i$ 和块的个数 $cnt$，这时的状态转移如下：
$$dp_{i,j}=\sum_{j=1}^{cnt}dp_{i,j-1}+dp_{i-1,cnt-j+1}\times len_{j}$$
这里状态中的 $j$ 表示第 $j$ 块。

时间复杂度 $\Theta(\sqrt{n}k)$。

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
int n,m;
int dp[105][100005];
int a[100005],len[100005],cnt;
signed main(){
    scanf("%lld%lld",&n,&m);
    for(int l=1,r;l<=n;l=r+1){
        r=(n/(n/l));
        a[++cnt]=r;
        len[cnt]=r-l+1;
    }
    for(int i=1;i<=cnt;i++) dp[0][i]=1;
    for(int i=1;i<=m;i++){
        int d=cnt;
        for(int j=1;j<=cnt;j++){
            dp[i][j]=(dp[i][j-1]+len[j]*dp[i-1][d--]%mod)%mod;
        }
    }
    printf("%lld",dp[m][cnt]);
    return 0;
}
```

---

## 作者：jiazhichen844 (赞：4)

根号算法优化 dp 的好题。

# 思路

## 暴力方法
序列数量计数，一眼 dp。

令序列为 $a$，$f_{i,j}$ 为长度为 $i$，且 $a_i=j$ 的合格序列方案数，答案即为 $\sum_{i=1}^n f_{k,i}$。

转移时考虑 $a_{i-1}$ 的值，若 $i=1$，则 $f_{1,j}=1$。

否则：枚举 $a_{i-1}$，设为 $x$，则 $f_{i,j}=\sum_{j\times x \le n} f_{i-1,x}$。

此时，你就有了一个简单的 dp 思路，时间复杂度 $O(n^2k)$，空间复杂度  $O(nk)$

## 优化

一看数据范围： T 飞，M 飞

考虑优化，先把式子移项为 $f_{i,j}=\sum_{x=1}^{\lfloor \frac n j \rfloor} f_{i-1,x}$。

然后~~瞪眼法~~分析性质：若 $\lfloor \frac n {j_1} \rfloor=\lfloor \frac n {j_2} \rfloor$，则 $f_{i,j_1}=f_{i,j_2}$。

于是数论分块，对 $\lfloor \frac n j \rfloor$ 分块，令 $j$ 所在块编号为 $bl_j$，第 $j$ 块的数为 $num_j$，长为 $len_j$，令 $f_{i,j}$ 为第 $j$ 块的答案，$f_{i,j}=\sum_{x=1}^{num_j}f_{i-1,bl_x}$。

~~结束了~~还没结束，现在时间复杂度为 $O(k\times \sqrt{n}\times \sqrt{n})=O(kn)$，还是超时。

再分析性质发现那个求和其实是 $f(x)=f_{i,bl_x}$ 的前缀和，前缀和优化dp，令 $fs_{i,j}=\sum_{x=1}^{num_j} f_{i,bl_x}$。

则 $fs_{i,j}=fs_{i,j-1}+f_{i,j}\times len_j$，$f_{i,j}=f_{i-1,bl_{num_j}}$。

时间复杂度 $O(k\sqrt n)$，空间复杂度 $O(k\sqrt n)$

code:
```cpp
#include<bits/stdc++.h>
using namespace std;
struct q
{
	int l,r,g;
}a[80005];
int le[80005];
long long dp[105][80005];
long long dpsum[105][80005];
int mod=1e9+7;
int main()
{
	int n,k;
	cin>>n>>k;
	int c=0;
	for(int l=1,r;l<=n;l=r+1)
	{
		r=n/(n/l);
		a[++c]={l,r};
		le[c]=l;
	}
	for(int i=1;i<=c;i++)
		a[i].g=upper_bound(le+1,le+c+1,n/a[i].l)-le-1;
	for(int i=1;i<=c;i++)
		dp[1][i]=1,dpsum[1][i]=a[i].r%mod;
	for(int i=2;i<=k;i++)
		for(int j=1;j<=c;j++)
		{
			dp[i][j]=dpsum[i-1][a[j].g];
			dpsum[i][j]=dpsum[i][j-1]+dp[i][j]*(a[j].r-a[j].l+1)%mod;
			dpsum[i][j]%=mod;
		}
	cout<<dpsum[k][c];
}
```

---

## 作者：紊莫 (赞：3)

模拟赛题，但是搬了 $K = 1$ 并且卡掉了我。  
所以给出一个和现有题解不同的方法。

---

首先考虑 $n<4\times10^4$ 的做法，可以进行朴素的动态规划，设 $f_{i,j}$ 表示第 $i$ 个数字取 $j$ 的方案数，转移显然有 $f_{i,j} \leftarrow f_{i-1,k}\times [j\times k \le n]$。

但是在 $n \le 10^9$ 时无法通过。注意到乘积有非常好的性质，两数不可能都大于 $\sqrt{n}$。

那么我们在枚举 $j$ 的时候只枚举到 $B = \sqrt{n}$，然后考虑 $a_{i-1}$ 的取值，如果 $a_{i-1}\le B$ 那么按照上述转移，否则的话考虑 $a_{i-2}$ 一定小于 $B$，那么改为从 $f_{i-2,k}$ 转移过来，中间 $a_{i-1}$ 的取值也是可以计算的，直接乘上这个范围即可。

然后统计答案的时候因为只统计了第 $K$ 位小于 $B$ 的情况，所以按照上述方法再从 $f_{K-1,k}$ 转移即可。

你注意到每次转移都是连续求和，直接前缀和即可做到 $\mathcal{O}(K \sqrt{n})$。

```cpp
#include <bits/stdc++.h>
#define int long long

#define F(i, a, b) for (int i = (a); i <= (b); i++)
#define dF(i, a, b) for (int i = (a); i >= (b); i--)
using namespace std;

const int N = 105, M = 40005, inf = 0x3f3f3f3f, mod = 1e9 + 7;
int n, K, ans, f[N][M], g[N][M], s[N][M];

signed main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> n >> K;
  int B = sqrt(n);
  f[0][1] = 1, g[0][1] = n - B;
  F(i, 1, B) f[1][i] = 1, s[1][i] = i, s[0][i] = 1;
  F(j, 1, B) {
    g[1][j] = (g[1][j - 1] + f[1][j] * max(0ll, n / j - B) % mod) % mod;
    g[0][j] = (g[0][j - 1] + f[0][j] * max(0ll, n / j - B) % mod) % mod;
  }
  F(i, 2, K) {
    F(j, 1, B) {
      f[i][j] = s[i - 1][B] + max(n / j - B, 0ll) * s[i - 2][j] % mod + g[i - 2][B] - g[i - 2][j];
      f[i][j] = (f[i][j] % mod + mod) % mod;
      if (i == K) ans = (ans + f[i][j]) % mod;
    }
    F(j, 1, B) g[i][j] = (g[i][j - 1] + f[i][j] * max(0ll, n / j - B) % mod) % mod;
    F(j, 1, B) s[i][j] = (s[i][j - 1] + f[i][j]) % mod;
  }
  F(j, 1, B) { ans = (ans + f[K - 1][j] * max(0ll, n / j - B) % mod) % mod; }
  cout << ans;
  return 0;
}
```


---

## 作者：MSqwq (赞：2)

逆天题，调了一下午。。。  
为什么我会 [[CQOI2007]余数求和](https://www.luogu.com.cn/problem/P2261) 但是不会这个呢，因为我是傻逼。  


------------
第一眼，可以一眼看出一个 dp，设 $f_{i,j}$ 表示第 i 个数填 j，那么可以转移 $f_{i,j}=\sum\limits_{k=1}^{\lfloor \frac{n}{j} \rfloor}f_{i-1,k}$，但是你发现当 $j$ 巨小的时候你的 $\lfloor \frac{n}{j} \rfloor$ 巨大，无论是空间还是时间都无法完成。  
然后你手搓一遍发现 $i$ 一定的时候，$j$ 增大，会重复算很多次 $f_{i-1,k}$。那么如何避免过多的计算呢，考虑整除分块。  
对于整除分块，定义就已经讲得很清楚了，可以支持这种操作，具体可以看 [OI Wiki 数论分块](https://oi-wiki.org/math/number-theory/sqrt-decomposition/)。  
那么可以整块整块的处理了，就很简单了，预处理一下每块的块长，可以得到这个式子 $f_{i,j}$ 表示 i 个数，和当前在 j 块，那么就有 $f_{i,j}=\sum\limits_{k=1}^{num}f_{i-1,x}\times len_x$  
前缀和优化一下上一次就行，甚至可以优化成一维，因为，之和前一层有关，但是无所谓了，这题没有卡空间。  
代码如下：  
```
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int mod=1e9+7;
const int INF=0x3f3f3f3f;

inline int read()
{
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-'0',c=getchar();}
	return x*f;
}
const int M=1e5+10,N=110;
ll f[N][M];
ll len[M],num;
int main()
{
	int n=read(),k=read();
	for(ll l=1,r;l<=n;l=r+1)
	{
		r=n/(n/l);
		len[++num]=r-l+1;
	}
	for(int i=1;i<=num;i++)f[0][i]=1;
	for(int i=1;i<=k;i++)
	{
		for(int j=1;j<=num;j++)
			f[i][j]=(f[i][j]+len[j]*f[i-1][num-j+1]%mod)%mod;
		for(int j=1;j<=num;j++)
			f[i][j]=(f[i][j]+f[i][j-1])%mod;
	}
	cout<<f[k][num]<<endl;
	return 0;
}


```


---

## 作者：Hovery (赞：1)

看到乘积，不难想到先把 $n$ 开根，分成 $\le \sqrt{n}$ 和 $> \sqrt{n}$ 两部分。

由于不会同时取两个 $> \sqrt{n}$ 的数，不妨枚举 $\le \sqrt{n}$ 选哪些数，然后找到 $> \sqrt{n}$ 中的取值范围。

不难发现，取值范围是单调的，如下图。

![](https://cdn.luogu.com.cn/upload/image_hosting/5vdk642i.png)

不妨把取值分成几段。

![](https://cdn.luogu.com.cn/upload/image_hosting/py0yqyet.png)

这样就有一个性质：编号大于等于它的段全部可以取。

下面考虑 $\texttt{DP}$。

设 $f_{i,j}$ 表示到了第 $i$ 个位置，取了 $\le \sqrt{n}$ 中的 $j$ 的方案数。

$g_{i,j}$ 表示到了第 $i$ 个位置，取了 $> \sqrt{n}$ 中处于第 $j$ 段的方案数。

这样就有（ $cnt_i$ 表示第 $i$ 个段的数的个数）：

$$f_{i,j}=\sum\limits_{k=1}^{\sqrt{n}} f_{i-1,k}+\sum\limits_{k=j}^{\sqrt{n}} g_{i-1,k}$$

$$g_{i,j}= \sum\limits_{k=1}^j (f_{i-1,k}\times cnt_j)$$

前缀和优化即可。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int n, k, f[34000], g[34000], _1[34000], _2[34000], _[34000], mx[34000];

const int mod = 1e9 + 7;

signed main()
{
    cin >> n >> k;
    int B = sqrt(n);
    for (int i = 1;i <= B;i++)
    {
        mx[i] = n / i;
    }
    mx[B + 1] = B;
    for (int i = 1;i <= B;i++)
    {
        _[i] = max(mx[i] - mx[i + 1], 0ll);
    }
    for (int i = 1;i <= B;i++)
    {
        _1[i] = i;
    }
    for (int i = B;i >= 1;i--)
    {
        _2[i] = (_2[i + 1] + _[i]) % mod;
    }
    for (int i = 2;i <= k;i++)
    {
        for (int j = 1;j <= B;j++)
        {
            f[j] = g[j] = 0;
        }
        for (int j = 1;j <= B;j++)
        {
            f[j] = (_1[B] + _2[j]) % mod;
        }
        for (int j = 1;j <= B;j++)
        {
            g[j] = _1[j] * _[j] % mod;
        }
        for (int j = 1;j <= B;j++)
        {
            _1[j] = _2[j] = 0;
        }
        for (int j = 1;j <= B;j++)
        {
            _1[j] = (_1[j - 1] + f[j]) % mod;
        }
        for (int j = B;j >= 1;j--)
        {
            _2[j] = (_2[j + 1] + g[j]) % mod;
        }
    }
    cout << (_1[B] + _2[1]) % mod;
}
```

---

## 作者：Night_sea_64 (赞：0)

这好像是我独立切的第一道根号分治。

以下 $n$ 是题目中的 $K$，$m$ 是题目中的 $N$。

最暴力的 dp 肯定一眼就看出来了：$f_{i,j}$ 表示前 $i$ 个，第 $i$ 个位置是 $j$ 的方案数。

我们加入第二维显然是为了确定下一位可以填什么。然后就可以想到，当第二维的值 $>\sqrt n$ 时，下一位可以填的值就 $<\sqrt n$ 了。所以在第二维 $>\sqrt n$ 时，转而记录下一位可以填的最大值，也就是 $m$ 除以当前值下取整。于是空间就不炸了。

最后就是前缀和、后缀和优化。因为你上一位的可选状态是连续的。这样时间也不炸了。时空复杂度均为 $O(n\sqrt m)$。

细节啥的就看代码吧，也挺短的肯定很好理解。

```cpp
#include<iostream>
#include<cmath>
#define int long long
using namespace std;
const int mod=1e9+7;
int n,m,sq,cnt[40010];
int f[110][40010],g[110][40010];
/*
cnt[i] 表示 m/j=i 且 j>sqrt(m) 的 j 有多少个
f[i][j] 表示位置 i，值<=sqrt(m)，值<=j 的方案数
g[i][j] 表示位置 i，值>sqrt(m)，m/值>=j 的方案数
*/
signed main()
{
    cin>>m>>n;
    sq=sqrt(m);
    for(int i=1;i<=sq;i++)cnt[i]=m/i-m/(i+1);
    if(m/sq==sq)cnt[sq]--;
    for(int i=1;i<=sq;i++)f[0][i]=1;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=sq;j++)
            f[i][j]=(f[i][j-1]+f[i-1][sq]+g[i-1][j])%mod;
        for(int j=sq;j>=1;j--)
            g[i][j]=(g[i][j+1]+cnt[j]*f[i-1][j]%mod)%mod;
    }
    cout<<(f[n][sq]+g[n][1])%mod<<endl;
    return 0;
}
```

---

## 作者：大眼仔Happy (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc132_f)

这一场就这一题比较牛，但感觉自己可以想出来。感觉一不会就看题解是很错误的行为。

朴素 dp 很显然，设 $f_{i,j}$ 表示考虑到第 $i$ 个数，最后一个为 $j$ 的方案数。显然有

$$f_{i,j}=\sum_{x=1}^{\lfloor\frac{N}{x}\rfloor} f_{i-1,x}$$

但是这个东西不仅时间复杂度不行，而且状态数也是爆炸。然而我花了 3min 想到这里之后就白兰了？？？

但是有一个 $\lfloor\frac{N}{x}\rfloor$，于是就可以整除分块，就把这个相同的归到一块去处理。假设我们当前考虑到第 $i$ 个块 $[L,R]$，有 $\lfloor\frac{N}{L}\rfloor=\lfloor\frac{N}{R}\rfloor$，并且可以发现 $\lfloor\frac{N}{R}\rfloor$ 也是某一个块的右端点。于是对于每一个块，我们记录右端点和长度，对于每一个右端点我们记录所在块的编号，然后套上去那个 dp，再前缀和优化即可。时间复杂度 $O(K\sqrt{N})$。

------------

好这个 $\lfloor\frac{N}{R}\rfloor$ 也是某一个块的右端点似乎不是很显然？那我也顺便解决一下讨论区的问题。

回顾整除分块知识，右端点是由 $R=\bigg\lfloor\dfrac{N}{\lfloor\frac{N}{L}\rfloor}\bigg\rfloor$ 得到的。这其实也可以表明若 $x=\bigg\lfloor\dfrac{N}{\lfloor\frac{N}{x}\rfloor}\bigg\rfloor$ 那就是右端点。由于现在 $x=R$ 满足这个性质，然后你代进去就可以发现 $x=\lfloor\frac{N}{R}\rfloor$ 也是对的。

证明似乎有点粗糙（~~不过能说服自己就行~~），欢迎严谨且简单易懂的证明补充。

------------

好像是可以用矩阵优化做到 $O(N^{\frac{3}{2}}\log K)$ 的，但是这里没必要。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=1e5+5,K=105;
const ll mod=1e9+7;
ll inline read()
{
	ll num=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){num=(num<<3)+(num<<1)+(ch^48);ch=getchar();}
	return num*f;
}
ll n,k,cnt; 
map<ll,ll>pos;
ll f[K][N],id[N],len[N];
int main(){
	n=read();k=read();
	for(ll L=1,R;L<=n;L=R+1)
	{
		R=n/(n/L);
		cnt++;
		id[cnt]=R;
		pos[R]=cnt;
		len[cnt]=R-L+1;
	}
	for(int i=1;i<=cnt;i++)f[0][i]=1;
	for(int i=1;i<=k;i++)
		for(int j=1;j<=cnt;j++)
			f[i][j]=(f[i][j-1]+len[j]*f[i-1][pos[n/id[j]]])%mod;
	printf("%lld",f[k][cnt]);
	return 0;
}
```

---

## 作者：maple_trees_112 (赞：0)

oj 上看到了这道题，在洛谷上考到了就来打篇题解

嗯，这道题一眼看过去就是 dp 暴力。
然后打出来一看，超时了，而且还一半 T 一半 M。

我还不死心，交了一遍又一遍，~~然后被判定成了卡评测封号的后果~~

我冷静下来一想，直接暴力的话时间复杂度是 $O(n ^ 2k)$

再看看数据，这肯定炸。

这里优化最好的是用前缀和，甚至可以极致把数组开成一维。当然没必要，洛谷应该不会专门的卡数据

但是呢我们的状态转移方程得改一下

- 先说没有优化过的方法，考虑 $dp[i][j] = dp[i - 1][j]$，空间和时间复杂度都会炸。

- 再说一下优化过的思路，大概是分块或者说前缀和优化。个人倾向于分块，应为前缀和在处理是不如分块好的。但前缀和在这道题里边更好理解。想了解分块的可以看[这里](https://blog.csdn.net/yanghao5/article/details/102723128)

- 分类讨论 $a_i$ $\le$ 或 $>$ $[n / a_i]$。我们可以发现，$[n / a_i]$ 最多有 $\sqrt{n}$ 种取值，前缀和在枚举时记录一下即可。此时的时间复杂度是 $O(\sqrt{n}k)$,能过。


```cpp

#include<bits/stdc++.h>
#define int long long 
using namespace std;
const int mod = 1e9 + 7;
const int maxn = 1e5 + 10;
int f[110][maxn];
int a[maxn],len[maxn];
map<int, int> b;
signed main()
{
	int n,k;
	cin>>n>>k;
	int cnt = 0;
	for(int l = 1, r; l <= n; l = r + 1)
	{
		r = min(n, (n / (n / l)));
		a[++cnt] = r;  b[r] = cnt;
		len[cnt] = r - l + 1;
	}
	for(int i = 1; i <= cnt; i++)
	{
		f[0][i] = 1;
	}
	for(int i = 1;i <= k; i++)
	{
		for(int j = 1;j <= cnt; j++)
		{
			f[i][j] = (f[i][j - 1] + len[j] * f[i - 1][b[n / a[j]]] % mod) % mod;//取余很重要 
		}
	}
	cout<<f[k][cnt]<<endl;
}
```



---

## 作者：Linghua_dog (赞：0)

## $\textbf{Solution}$

根据题意，我们可以观察到这是一道计数问题,又是序列问题，所以我们考虑 $dp$，$dp$ 的状态我们设为 $dp_{i, j}$ 表示第 $i$ 位填 $j$ 的方案数，那么状态转移方程可以写为： 

$$dp_{i, j} = \sum_{p = 1}^{\left\lfloor N / j \right\rfloor} dp_{i - 1, p}$$

那么我们就有了 $\mathcal O(NK)$ 的暴力算法，再去考虑优化，我们观察到一个很熟悉的东西 $\left\lfloor N / j \right\rfloor$，如果你做过数论的题，你就可以知道这个东西可以用数论分块去做，原理就是 $\left\lfloor N / j \right\rfloor$ 的种类是不超过 $\sqrt{N}$ 个的，所以我们可以把相同的部分缩成一个块在统一去做，就可以把复杂度优化到 $\mathcal O(\sqrt{N}K)$ 就可以愉快的通过此题了。



## $\textbf{AC Code}$

```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <map>

#define int long long 

using namespace std;

const int mod = 1e9 + 7, N = 1e5 + 10, K = 105;

int f[K][N];
int a[N], len[N];
map<int, int> b;

signed main()
{
	int n, k;
	cin >> n >> k;
	int cnt = 0;
	for(int l = 1, r; l <= n; l = r + 1)
	{
		r = min(n, (n / (n / l)));
		a[++cnt] = r;  b[r] = cnt;
		len[cnt] = r - l + 1;
	}
	
	for(int i = 1; i <= cnt; i++) f[0][i] = 1;
	for(int i = 1; i <= k; i++)
	{
		for(int j = 1; j <= cnt; j++)
		{
			f[i][j] = (f[i][j - 1] + len[j] * f[i - 1][b[n / a[j]]] % mod) % mod;
		}
	}
	cout << f[k][cnt] << '\n';
}
```

---

## 作者：daniEl_lElE (赞：0)

根号分治+dp。

## 思路

考虑 $dp_{i,j}$ 表示填到 $a_i$，$a_i=j$ 的方案数。转移时可以枚举一个 $k$，判断 $j\times k\leq n$ 然后转移，这样复杂度是 $O(n^2k)$ 的。

考虑转移符合要求的 $k$ 是连续的一段区间，可以前缀和优化，复杂度 $O(nk)$。

再考虑对于所有 $\lfloor\dfrac{n}{j_1}\rfloor=\lfloor\dfrac{n}{j_2}\rfloor$，$j_1$ 和 $j_2$ 可转移区间完全相同，故可以合并，容易发现最多只有 $O(\sqrt{n})$ 个，加上前缀和优化即可做到 $O(\sqrt{n}k)$。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define double long double
#define mid ((l+r)>>1)
using namespace std;
const int mod=1e9+7;
int qp(int a,int b){
	int ans=1;
	while(b){
		if(b&1) ans=(ans*a)%mod;
		a=(a*a)%mod;
		b>>=1;
	}
	return ans;
}
int fac[10000005],inv[10000005];
void init(){
	fac[0]=1;
	for(int i=1;i<=10000000;i++) fac[i]=fac[i-1]*i%mod;
	inv[10000000]=qp(fac[10000000],mod-2);
	for(int i=9999999;i>=0;i--) inv[i]=inv[i+1]*(i+1)%mod;
}
int C(int i,int j){
	if(i<0||j<0||i<j) return 0;
	return fac[i]*inv[i-j]%mod*inv[j]%mod;
}
int dp[100005][105];
int sz[100005];
signed main(){
	init();
	int n,k;
	cin>>n>>k;
	int tot=0;
	for(int i=1;i*i<n;i++){
		tot++;
		sz[tot]=1;
	}
	tot++;
	sz[tot]=n/(int)sqrt(n)-(int)sqrt(n)+((int)sqrt(n)*(int)sqrt(n)==n);
	for(int i=sqrt(n)-1;i>=1;i--){
		tot++;
		sz[tot]=n/i-n/(i+1); 
	}
	dp[1][0]=1;
	for(int i=1;i<=k;i++){
		int sum=0;
		for(int j=1;j<=tot;j++){
			sum+=dp[j][i-1];
			sum%=mod;
			dp[tot-j+1][i]=sum*sz[tot-j+1]%mod;
		}
	}
	int ans=0;
	for(int i=1;i<=tot;i++) ans=(ans+dp[i][k])%mod;
	cout<<ans;
	return 0;
}
```

---

