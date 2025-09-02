# [ARC107D] Number of Multisets

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc107/tasks/arc107_d

正整数 $ N,\ K $ が与えられます。以下の条件を全て満たす有理数の多重集合は何種類存在しますか？

- 多重集合の要素数は $ N $ で、要素の総和は $ K $
- 多重集合の要素は全て $ 1,\ \frac{1}{2},\ \frac{1}{4},\ \frac{1}{8},\ \dots $ 、つまり $ \frac{1}{2^i}\ (i\ =\ 0,1,\dots) $ のいずれか。

答えは大きくなるかもしれないので、$ \bmod\ 998244353 $ で出力してください。

## 说明/提示

### 制約

- $ 1\ \leq\ K\ \leq\ N\ \leq\ 3000 $
- 入力される数は全て整数である。

### Sample Explanation 1

以下の $ 2 $ つが条件を満たします。 - $ {1,\ \frac{1}{2},\ \frac{1}{4},\ \frac{1}{4}} $ - $ {\frac{1}{2},\ \frac{1}{2},\ \frac{1}{2},\ \frac{1}{2}} $

## 样例 #1

### 输入

```
4 2```

### 输出

```
2```

## 样例 #2

### 输入

```
2525 425```

### 输出

```
687232272```

# 题解

## 作者：lsj2009 (赞：9)

好题！

考虑到一个集合的元素是无序的，我们不妨将其按从小到大排序，例如这么一个集合：$\{\frac{1}{8},\frac{1}{2},\frac{1}{2},1\}$，他是如何得到的？先得到一个集合 $\{1,1,1,1\}$，然后将 $1\sim 1$ 的前缀乘两个 $\frac{1}{2}$，再将 $1\sim 3$ 的前缀乘一个 $\frac{1}{2}$。

也就是说，任意一个题目所求的集合均可以表示成先加入 $n$ 个 $1$，然后对于每个前缀乘上若干个 $\frac{1}{2}$。

通过上面那个思路，我们每一次拓展集合，我们不妨先加入一个 $1$，然后**可以**选择将 $1\sim i$ 这个前缀乘上若干个 $\frac{1}{2}$，再考虑如何实现。

设 $f_{i,j}$ 表示前 $i$ 个数和为 $j$ 的方案总数，加入 $1$ 相当于 $f_{i,j}\gets f_{i-1,j-1}$。

而乘 $\frac{1}{2}$，则是将 $j$ 减半，即 $f_{i,j}\gets f_{i,j\times 2}$。需要注意的是，这里之所以是 $f_{i,j\times 2}$ 而不是 $f_{i-1,j\times 2}$，是因为我们可以选择若干个 $\frac{1}{2}$，也就是相当于一个完全背包。

然后就做完了，复杂度 $\Theta(n^2)$。


```cpp
#include<bits/stdc++.h>
//#define int long long
#define ll long long
#define ull unsigned long long
#define ld long double
#define PII pair<int,int>
#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f
#define chkmax(a,b) a=max(a,b)
#define chkmin(a,b) a=min(a,b)
#define rep(k,l,r) for(int k=l;k<=r;++k)
#define per(k,r,l) for(int k=r;k>=l;--k)
#define cl(f,x) memset(f,x,sizeof(f))
using namespace std;
const int N=3e3+5,MOD=998244353;
int f[N][N];
signed main() {
    int n,k;
    scanf("%d%d",&n,&k);
    f[0][0]=1;
    rep(i,1,n) {
        per(j,i,0) {
            f[i][j]=f[i-1][j-1];
            if(j*2<=i)
                f[i][j]=(f[i][j]+f[i][j*2])%MOD;
        }
    }
    printf("%d\n",f[n][k]);
    return 0;
}
```

---

## 作者：GGrun (赞：7)

## 写一个新的 DP 思路:

首先题目要求 $n$ 个数 $x$ 加和为 $k$ 的方案数，其中 $x$ $\in \frac{1}{2^i}$，$i \in N$（接下来所说的第 $i$ 种数，就是 $\frac{1}{2^i}$）。

由于有很多小数，一开始脑子很乱，觉得比较难处理，但是注意到最后加和是一个整数，**也就是所有小数的加和是一个整数**。

也就是说我们还需要限制每种小数的个数，听起来似乎更麻烦了，其实这可以启发我们含一种方式来思考：



**把一些小数合并起来是整数，也就是说，这些小数其实是由 1 分裂而来的。**




![niumo](https://cdn.luogu.com.cn/upload/image_hosting/71znlrif.png)

然后我们就可以注意到两个性质：
1. 无论我怎么分裂，最终总和不变。
2. 每一次分裂，数量加 1。

**那么我们一开始就将 整个集合设为 $k$ 个 1 ，然后就可以在总和不变的情况下，毫无顾忌的去分裂，直到个数到达了给的限制 $n$，统计答案即可。**

为了避免重复，我们依次将每种数一次分裂确定的数量，不要反复横跳的一会分 1，一会分 $\frac{1}{2}$。

### 初步状态转移方程：

设 $f_{i,j,p}$ 表示要分裂出 $j$ 个 $\frac{1}{2^i}$，分裂之后还要分裂 $p$ 次才能分裂出 $n$ 个数的方案数（可能有点绕）。

**因为分裂出来 $j$ 个数，也就对 $p$ 有 $\frac{j}{2}$ 的贡献，那么要想分裂出来 $j$ 个数，原来的第 $i-1$ 种数也就至少得有 $\frac{j}{2}$ 个。**

那么就有了状态转移方程：
$$f_{i,j,p}= \sum_{l= \frac{j}{2} }^{n}f_{i-1,l,p+ \frac{j}{2}}$$

初始化时，**按照定义 $f_{0,k,n-k}=1$**，最后 ans 就是将所有的答案是 $f_{i,j,0}$ 的方案数统计起来，输出即可。

那么时间复杂度直接来到了逼近暴力的  $O(n^4)$，包 T 了。

### 考虑更改成新的状态：

在上一步的答案统计中，我们只关注了最后一维，也就是还需要分裂多少次那一维。这就可以启发我们：**只要最后不需要分裂了，不管我目前分裂到了第几种数都不重要，都是答案的一种。**
但是我们只记录还需要转移多少次是无法转移的，因为每种数会被上一种数的个数限制，所以记一下本次分裂出来了多少个这种数，就可以很方便的转移了。那么设 $f_{i,j}$ 表示分裂出来了 $i$ 个这种数，还需要分裂 $j$ 次才能达到 $n$ 个数，就获得了状态转移方程：
$$f_{i,j}=\sum_{l=\frac{i}{2}}^{n}f_{l,j+\frac{i}{2}} $$

**初始化 $f_{k,n-k}=1$**,时间复杂度是  $O(n^3)$，还是得 GG。

### 最后的优化：

观察上面给出的状态转移方程，对于一个确定的 $i$、$j$ 来说，后面求和的 $j+\frac{i}{2}$ 也是确定的，第一维的范围是 $[\frac{i}{2},n]$，就是一个后缀和，那么我们直接抛弃 $f$ 数组，用 $pre_{i,j}$ 表示 $\sum_{l=i}^{n}f_{l,j} $，那么就有：
$$pre_{i,j}=pre_{i+1,j}+pre_{\frac{i}{2},j+\frac{i}{2}}$$

直接做到了 $O(n^2)$ 转移。

### 一些细节：

1. 初始化时， $pre_{i,n-k}$，$i \in [0,k]$ 全部 $ \gets 1$。
2.  因为是分裂而来的，所以只能枚举 $i$ 是偶数的情况，否则转移是非法的。

## code：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2e6+10,inf=0x3f3f3f3f;
const ll linf=0x3f7f7f7f7f7f7f7f,mod=998244353;
inline ll read(){
	char c=getchar();ll x=0,f=1;
	while(!isdigit(c))f=c=='-'?-1:1,c=getchar();
	while(isdigit(c))x=(x<<1)+(x<<3)+(c^48),c=getchar();
	return x*f;
}
int n,k,pre[5100][5100];
signed main(){
    
    // freopen("in.in","r",stdin);
    // freopen("out.out","w",stdout);
    n=read(),k=read();
    for(int i=k;i>=0;--i)
    	pre[i][n-k]=1;
    for(int j=n-k-1;j>=0;--j){
    	for(int i=(n-j)/2*2;i>=0;i-=2){
    		pre[i+1][j]=pre[i+2][j];
    		pre[i][j]=((ll)pre[i+1][j]+pre[i>>1][j+(i>>1)])%mod;
    	}
    }
    cout<<pre[0][0];
}
```

$$\color{salmon}EOF$$

---

## 作者：菲斯斯夫斯基 (赞：5)

## AT_arc107_d [ARC107D] Number of Multisets 题解

题意很明了，不再赘述。

还是很明显的动态规划，考虑 $dp$ 数组的含义是什么。比较麻烦的是有很多小数，不好处理。但是要的和 $K$ 是自然数，所以可以定义 $dp_{i,j}$ 的含义是选了 $i$ 个数，和为 $j$。

但是假如现在选了 $\frac{1}{4}$ 和 $\frac{1}{2}$，它们的和是 $\frac{3}{4}$ 怎么办？$\frac{3}{4}$ 不是自然数，所以我们的操作是：不用管它，因为不会对答案造成影响。

注意到 $1$ 是自然数，所以 $dp_{i,j}$ 可以从	$dp_{i-1,j-1}$ 转移而来，第 $i$ 个数选了 $1$。

同时因为可以选的数是 $\frac{1}{2^i}(i\ge1)$，所以我们可以将所有的数都翻倍，那么翻倍后的数也是可以得到的。


整理上面的结论，可以得到动态转移方程（注意边界的判断）：

$$dp_{i,j}=dp_{i-1,j-1}+dp_{i,j\times2}$$

当然还有初始化：$dp_{0,0}=1$。

**代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k;
int dp[5010][5010];
int main()
{
	cin>>n>>k;
	dp[0][0]=1;
	for(int i=1;i<=n;i++)
	{
		for(int j=i;j>=1;j--)
		{
			dp[i][j]=dp[i-1][j-1];
			if(j*2<=i)dp[i][j]+=dp[i][j*2];
			dp[i][j]%=998244353;
		}
	}
	cout<<dp[n][k];
	return 0;
}

```

---

## 作者：bsTiat (赞：4)

有趣的递推。

设 $ f_{i,j} $ 表示当 $ N=i,K=j $ 时满足条件的集合数。

为了方便起见，我们将集合中的元素按降序排序，显然，初始边界有 $ f_{i,i} = 1$，此时集合中只有一个 $ 1 $，然后我们考虑，$ f_{i,j} $ 可以由哪些状态转移过来。

考虑，不重不漏地转移，一个集合可以只由另一个集合，添加元素或将所有元素除二得到。

- 在某个集合最前面添加一个1得到， $ f_{i,j}+=f_{i-1,j-1} $ 。
- 将某个集合的所有元素除二得到，$ f_{i,j}+=f_{i,j\times2} $ 。

然后就做完了，稍微注意下转移顺序。

```cpp
for(int i=1;i<=n;++i){
		f[i][i]=1;
		for(int j=i-1;j>=0;--j){
			f[i][j]+=f[i-1][j-1];
			if(j*2<=i)f[i][j]+=f[i][j*2];
			f[i][j]%=mod;
		}
	}
```


---

## 作者：analysis (赞：3)

好像还没有人写这个 DP 思路，就写一下。

先考虑把 $n$ 个数加起来和为 $j$，没有秒掉这道题，所以弃掉这个做法。

转换思路，把 $k$ 个 $1$ 拆成 $n$ 个数。

可以设 $f_{i,j}$ 表示把 $i$ 个数拆成 $i + j$ 个数的方案数。

则有：

$$
f_{i,j} = \sum_{l=1}^{n}f_{2l,j - l} = f_{i-1,j} + f_{2i,j-i}
$$

秒掉了，答案是 $f_{k,n - k}$。

```cpp
#include<bits/stdc++.h>
#define int long long
const int mod = 998244353;
using namespace std;
int n,k;
int f[3005][3005];
signed main()
{
    cin >> n >> k;
    if(n == k)
    {
        cout<<1;
        return 0;
    }
    for(int i=1;i<=n;i++)
    {
        f[i][0] = 1;
    }
    for(int j=1;j <= n - k;j++)
    {
        for(int i=1;i<=n;i++)
        {
            f[i][j] = f[i-1][j];
            if(j - i >= 0 && 2 * i <= n)
            {
                f[i][j] = (f[i][j] + f[2 * i][j - i]) % mod;
            }
        }
    }
    cout<<f[k][n - k];
    return 0;
}
```

---

## 作者：tXX_F (赞：2)

# Solution

这题其实很好想到用 DP。设 $DP_{i,j}$ 表示选 $i$ 个数和为 $j$ 的情况。由于题目中到只能放入值 $2^{-x}$ 的数，那么 $i$、$j$ 一定满足 $i \geq j$。

现在考虑如何转移。

* 边界： $DP_{0,0}=1$；
* 若放入 $1$，则显然 $DP_{i,j}=DP_{i-1,j-1}$；
* 若放入的是分数，由于分数都等于 $2^{-x},x \in N_{+}$，那么可以考虑将原序列所有元素乘 $2$，再加入一个元素使得该序列和为 $2 \times j$，此时 $DP_{i,j}=\sum DP_{i,j \times 2}(j \times 2 \leq i)$。

**注意 $j$ 要从大到小操作**，因为要先求出 $DP_{i,j \times 2}$。

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int N, K;
int DP[5005][5005];
signed main() {
	ios::sync_with_stdio(false), cin.tie(0), cout.tie(0), cin >> N >> K, DP[0][0] = 1;
	for (register int i = 1; i <= N; ++i) for (register int j = i; j >= 1; j--) {
			DP[i][j] = DP[i - 1][j - 1];
			if ((j << 1) <= i) DP[i][j] = (DP[i][j] + DP[i][j << 1] > 998244353 ? DP[i][j] + DP[i][j << 1] - 998244353 : DP[i][j] + DP[i][j << 1]);
		}
	cout << DP[N][K] << endl;
	return 0;
}
```

---

## 作者：山田リョウ (赞：2)

这也太魔怔了吧？？？

![](https://cdn.luogu.com.cn/upload/image_hosting/oitbq8tj.png)

完全想不到，直接红温了呜呜呜

核心注意点大概是固定的底数的幂之和是可以很容易平移的（直接做除法就好了），然后我们不太希望出现分数，所以从小往大填，始终认为此时填的是 1 即可，然后再向自己除以 $2$ 后的结果转移即可。

具体来说记 $f_{i,j}$ 表示填了 $i$ 个数，和为 $j$ 的方案数（只考虑 $j$ 为整数，故 $j\in [0,N]\cap\mathbb{Z}$），有转移方程：

$$ f_{i,j}=\sum\limits_{k}f_{i-1,2^kj-1} $$

做一个类似前缀和的过程即可做到 $O(NK)$，[code](https://atcoder.jp/contests/arc107/submissions/59502172)。

---

## 作者：Lib_Zhang (赞：2)

#### 题意简述:
给定 $n$ 和 $k$，求 $n$ 个可表示为 $\frac{1}{2^i}$ $(i \in  \mathbb{N})$ 的数和为 $k$ 的方案数，结果对 $998244353$ 取模。

#### 分析:
本题思维难度不高，考虑 dp，$dp_{i,j}$ 表示选 $i$ 个满足题目要求的数使它们的和等于 $j$，同时因为满足题目要求的数都 $\le1$ 所以对于 $i,j$ 一定满足 $0 \le j \le i$，否则方案不存在。

因为 $\frac{1}{2^0}$ 为整数，所以分成两个子问题考虑。

考虑整数的情况，那么就转换为了 $dp_{i-1,j-1}$。

考虑分数的情况，不妨再将其转换为 $1$ 的情况，因为满足题目要求的数的分母都为 $2$ 的倍数，所以将所有数乘 $2$，即转换为 $dp_{i,2 \times j}$。

综上，得出转移方程：
$dp_{i,j} = 
\left\{
\begin{aligned}
&0 , j = 0\\
&0 , i < j\\
&dp_{i-1,j-1} + dp_{i,2 \times j} , \text{otherwise}\\
\end{aligned}
\right.
$

### 代码:

```
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<vector>
#include<set>
#include<stack>
#include<map>
#include<queue>
#include<cstdlib>
#include<iomanip>
#include<utility>
#define endl '\n'
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pai;
const double eps = 1e-10;
const int base = 13331;
const ll mod = 998244353;
ll maxn = -2147483647-1,minn = 0x7f7f7f7f;
ll n,k,dp[3005][3005];
ll solve(ll i,ll j){
	if(!j||i<j){
		return 0;
	}
	if(dp[i][j]){
		return dp[i][j];
	}
	else{
		return dp[i][j] = (solve(i-1,j-1)+solve(i,2*j))%mod;
	}
}
int main(){
	//freopen("filename.in","r",stdin);
	//freopen("filename.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>k;
	for(int i=1;i<=n;++i){
		dp[i][i] = 1;
	}
	cout<<solve(n,k)%mod<<endl;
	//fclose(stdin);
	//fclose(stdout);
	return 0;
}
```

#### 总结:
这种类型的题目比较典，很容易想到 dp，分数转为整数比较巧妙。



---

## 作者：AC_love (赞：1)

设 $f(i, j)$ 表示剩下 $i$ 个数可用，当前还差 $j$ 才能到 $K$，且此时最大能够使用的数是 $1$。

假设我们此时 $i$ 个数里只有 $k$ 个 $1$，那么还剩 $i - k$ 个数可用，还差 $(j - k)$ 才能到 $K$，而此时最大可以使用的数是 $\dfrac{1}{2}$。

我们不妨把所有能够使用的数和 $(j - k)$ 一起乘个 $2$，这样我们当前能使用的最大的数还是 $1$。于是当前的状态其实等价于 $f(i - k, (j - k) \times 2)$。

按照这个思路设计 DP，枚举用了 $k$ 个 $1$，则有：

$$f(i, j) = \sum_{k = 0} f(i - k, (j - k) \times 2)$$

状态数 $O(n^2)$，转移 $O(n)$，总复杂度 $O(n^3)$，不太行，考虑能不能 $O(1)$ 转移。

不难发现有：

$$f(i - 1, j - 1) = \sum_{k = 0} f(i - 1 - k, (j - 1 - k) \times 2)$$

即：

$$f(i - 1, j - 1) = \sum_{k = 0} f(i - (k + 1), (j - (k + 1)) \times 2)$$

即：

$$f(i - 1, j - 1) = \sum_{k = 1} f(i - k, (j - k) \times 2)$$

而我们知道：

$$f(i, j) = \sum_{k = 0} f(i - k, (j - k) \times 2)$$

所以有：

$$f(i, j) = f(i - 1, j - 1) + f(i, j \times 2)$$

直接转移即可。

[code](https://atcoder.jp/contests/arc107/submissions/59461213)

---

## 作者：harmis_yz (赞：1)

题解摘自 [CSP2024 前做题情况](https://www.luogu.com.cn/article/9zpicw3e)。

## 分析

对于一个合法的序列，将其排序后一定形如：$(\dots,\frac{1}{16},\frac{1}{8},\frac{1}{4},\frac{1}{2})$。会发现，这个序列相当于在每个位置进行了若干次形如“将该位置的前缀整体除以 $2$”的操作。然后就好做了，定义状态函数 $f_{i,j}$ 表示前 $i$ 个数，和为 $j$ 的方案数。那么对于这个数，有 $2$ 种情况：

1. 不进行操作，$f_{i,j}=f_{i,j}+f_{i-1,j-1}$。
2. 进行若干次操作。因为没有次数限制，所以是个完全背包的形式。有：$f_{i,j}=f_{i,j}+f_{i,j\times 2}$。

 该算法的时间复杂度为 $O(n^2)$。

## 代码

```cpp
il void solve(){
	n=rd,k=rd;
	f[0][0]=1;
	for(re int i=1;i<=n;++i)
	for(re int j=i;j>=1;--j) f[i][j]=(f[i][j]+f[i-1][j-1]+f[i][j*2])%p;
	printf("%lld\n",f[n][k]);
    return ;
}
```

---

## 作者：NKL丶 (赞：1)

## Description

给出两个整数 $N,K$，现将 $K$ 分成 $N$ 个数的和，满足每个数均可表示为 $\frac{1}{2^i}$（其中 $i$ 为自然数），问符合题意的方案数，结果对质数取模。（$1 \le K \le N \le 3000$）

## Solution

考虑 DP，记 $f_{n,k}$ 表示将 $k$ 分为 $n$ 个数相加的和的情况。对于分数的处理，我们不妨换一种思考方式，我们由原来的填入分数改为将前面所有位上的数 $\times 2$，同时将 $k \times 2$，那么我们就能保证我们每一次填入的数均为 1，避免了分数的处理。

因此，我们可以得到如下转移方程：$f_{n,k}= \begin{cases}
0 , n < k \\
[n=0], k=0 \\
f_{n-1,k-1} +f_{n,k \times 2},otherwise
\end{cases}$

## [Code](https://www.luogu.com.cn/paste/rn7ibsob)

---

## 作者：_Cheems (赞：0)

小清新题。一开始往树上想，有个 2D/1D 的 dp，不太能优化。

这题恶心在不好设计状态。我们称一个可重集合法指其元素总和为整数。需要发现一个显然但挺重要的结论，对于合法的可重集，可以让它总体乘 $2$ 直到出现 $1$，去掉一个 $1$ 得到的可重集也是合法的。

这样就出现了子问题结构，考虑 $f_{i,j}$ 表示可重集元素个数为 $i$、总和为 $j$ 的方案数。对于 $f_i$，首先计算最大元素为 $1$ 的方案数，即 $f_{i,j}\gets f_{i-1,j-1}$；然后计算最大元素为 $\frac 12$ 的方案数，$f_{i,\frac j2}\gets f_{i,j}$，前提是 $2\mid j$，对于 $\frac 14,\frac 18\dots$ 同理，可以像完全背包一样从大到小转移。

最后答案为 $f_{n,m}$，复杂度 $O(n^2)$。
#### 代码


```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long
const int N = 3e3 + 5, mod = 998244353;
int n, m, f[N][N];

signed main(){
	cin >> n >> m;
	f[0][0] = 1;
	for(int i = 1; i <= n; ++i){
		for(int j = 1; j <= i; ++j) f[i][j] = f[i - 1][j - 1];
		for(int j = i; j; --j)
			if(j % 2 == 0) f[i][j / 2] = (f[i][j / 2] + f[i][j]) % mod; 
	}
	cout << f[n][m];
	return 0;
}
```

---

## 作者：shinkuu (赞：0)

好像对于题解区主流 dp，并没有一个详细的正确性证明。

考虑将操作放到二叉树森林中。限制就是二叉树一共有 $k$ 个根，$n$ 个叶子，并且没有只有一个儿子的节点。合法的二叉树和可重集形成双射。

自底往上考虑每一层，于是就有两种操作：在这一层新增一个点，或者在上面新增一层。第二种操作要求当前层有偶数个节点，随后每两个相邻节点都会并到一个父亲下面。

再考虑两种操作对原问题的影响：第一种显然是使元素数 $+1$，和 $+1$。第二种会使全部元素对和的贡献 $\times\frac{1}{2}$，也就是使和 $\times\frac{1}{2}$，并要求和此时为偶数。

于是就得到了那种 dp 了。

感觉这其实是阶梯状 dp 的一个变种。还是挺有意思的。

---

## 作者：eb0ycn (赞：0)

传送门：[AT_arc107d](https://www.luogu.com.cn/problem/AT_arc107_d)。

## 题意

求有多少有理数集满足以下所有条件：

1. 集合有且只有 $n$ 个元素，并且元素和为 $k$。

1. 每个元素须可表示为 $\frac {1}{2^{i}}$ $(i\in N)$。

## 思路

首先肯定不能暴力枚举每一位取什么数。因为每一位的取值是可以到无限小的，但是注意到 $k$ 必须是正整数，并且只有 $3000$，可以考虑记录 $k$ 这个状态。

设 $f_{i,j}$ 表示到了 $i$ 位置，目前和为 $j$ 的方案数。考虑怎么转移。

显然，$f_{i,j}$ 可以从 $f_{i-1,j-1}$ 转移过来。（第 $i$ 位填 $1$ 的情况）

但是我们不一定要填 $1$ 啊，怎么办呢？

由于集合里面的所有元素必须是 $2^{-i}$，所以在这一位填 $1$ 的基础上除以若干个 $2$，不就相当于得到了其他状态了吗？只要第 $1 \sim i$ 位的和可以是 $p \times 2^i$，那么 $p \times 2^{i-1}$，$p \times 2^{i-2}$，$\dots$，$p \times 2^0$ 肯定也可以。

所以我们就得出来了状态转移方程：

$$f_{i,j} \gets f_{i-1,j-1}+f_{i,j \times 2}$$

分别代表第 $i$ 位填 $1$ 和不填 $1$ 的情况。

## 注意

由于可以每一位都填 $1$，并且 $j$ 小的状态要从 $j$ 大的状态转移过来，所以 $j$ 要从 $i$ 枚举到 $1$。

并且由于不可能有一位填 $0$，所以初始状态有且仅有 $f_{0,0}=1$。

## 代码

在实现时，我加了一个滚动数组优化，暂时位列最优解第一名。

时间复杂度 $O(n^2)$，空间复杂度 $O(k)$。

```cpp
#include<cstdio>
using namespace std;
int n,k,f[3001][2],op;
int main(){
	scanf("%d%d",&n,&k),f[0][0]=1;
	for(int i=1;i<=n;++i){
		for(int j=i;j;--j){
			op=i&1,f[j][op]=f[j-1][op^1],f[j][op^1]=f[j][op];
			if(j<<1<=i)f[j][op]=(f[j][op]+f[j<<1][op])%998244353;
		}f[0][op^1]=f[0][op];
	}return 0*printf("%d",f[k][n&1]);
}
```

---

## 作者：coding_goat (赞：0)

## 基础思路

设 $f_{i,j}$ 为当有 $i$ 个元素，元素和为 $j$ 的时候的方案总数。

显而易见，初始状态 $f_{i,i} = 1$，因为只有全选 $1$ 的情况。

那么我们想到，$f_{i,j}$ 可以由有 $i-1$ 个元素，元素和为 $j-1$ 的情况，加入元素 $1$ 得到。

$f_{i,j}$ 同时也可以由有 $i$ 个元素，元素和为 $j \times 2$ 的情况，将所有的元素除以 $2$ 得到。

那么 $f_{i,j} = f_{i-1,j-1}+f_{i,j \times 2}$，所以倒序枚举即可。

为什么不可以正序枚举 $j$？

因为元素中会出现 $2$ 的东西。

比如一种情况是 $\{ 1,\frac{1}{4} ,\frac{1}{4} , \frac{1}{4}  , \frac{1}{4} \}$，将所有元素乘 $2$ 了后就变成了 $\{ 2,\frac{1}{2} , \frac{1}{2} , \frac{1}{2} , \frac{1}{2} \}$，不是题目所规定的。

$
% w, h, fillcol, bordercol
\newcommand\BorderRect[4]{
  \color{#3}\rule{#1}{#2}\kern{-#1}
  \color{#4}\rule{0.5px}{#2}\kern{-0.5px}
  \rule{#1}{0px}\rule{0.5px}{#2}\kern{-0.5px}
  \kern{-#1}\rule[#2]{#1}{0px}
}
% w, h, title, subtitle, fillcol, iconch ,iconcol
\newcommand\BasicInfoBarFather[8]{
  \BorderRect{#1}{#2}{#5}{ghostwhite}
  \kern{-#1}
  \raisebox{#2}{
    \raisebox{-26pt}{
      \color{black}\kern{-4px}
      \raisebox{7px}{
        \color{#7}\Huge{∙}\kern{-1px}
      }
      \raisebox{10.6px}{
        \kern{-20.2px}
        \color{white}\scriptsize\textbf{#6}
      }
      \kern{-7px}\footnotesize
      \raisebox{10.2px}{\textbf{\textsf{\color{#8}#3}}}\kern{2px}
      \raisebox{10.2px}{\textsf{#4}}
    }
  }
}
\def\BasicInfoBarColorFill{#F4F4F4}\def\BasicInfoBarColorIcon{#0078D4}
\def\BasicWarnBarColorFill{#FFF4CE}\def\BasicWarnBarColorIcon{#9D5D00}
\def\BasicOkBarColorFill{#DFF6DD}\def\BasicOkBarColorIcon{#0F7B0F}
\def\BasicErrBarColorFill{#FDE7E9}\def\BasicErrBarColorIcon{#C42B1C}
\newcommand\BasicInfoBar[5]{
  \BasicInfoBarFather{#1}{#2}{#3}{#4}
  {\BasicInfoBarColorFill}{i}{\BasicInfoBarColorIcon}{\BasicInfoBarColorIcon}
}
\newcommand\BasicWarnBar[5]{
  \BasicInfoBarFather{#1}{#2}{#3}{#4}
  {\BasicWarnBarColorFill}{i}{\BasicWarnBarColorIcon}{\BasicWarnBarColorIcon}
}
\newcommand\BasicOkBar[5]{
  \BasicInfoBarFather{#1}{#2}{#3}{#4}
  {\BasicOkBarColorFill}
  {\tiny\kern{-2px}\raisebox{0.8px}{√}}
  {\BasicOkBarColorIcon}{\BasicOkBarColorIcon}
}
\newcommand\BasicErrBar[5]{
  \BasicInfoBarFather{#1}{#2}{#3}{#4}
  {\BasicErrBarColorFill}
  {\kern{-2px}\raisebox{0.6px}{×}}
  {\BasicErrBarColorIcon}{\BasicErrBarColorIcon}
}
\\
\BasicOkBar{200px}{26px}{tips}{对常数取模会快很多哦。}{#2CA9E1}\\
$

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define maxint 0x7fffffff
#define gc getchar()
inline int read(){
	int x=0,f=1;
	char c=gc;
	while(c>'9'||c<'0'){
		if(c=='-') f=-1;
		c=gc;
	}
	while(c>='0'&&c<='9'){
		x=(x<<1)+(x<<3)+(c^48);
		c=gc;
	}
	return x*f;	
}
int n,k;
#define maxn 3030
int f[maxn][maxn];
const int p=998244353;
int main(){
	n=read(),k=read();
	for(int i=1;i<=n;i++)
		f[i][i]=1;
	for(int i=1;i<=n;i++){
		for(int j=i-1;j>=1;j--){
			f[i][j]+=f[i-1][j-1];
			if((j<<1)<=i) f[i][j]+=f[i][j<<1];
			f[i][j]%=p;
		}
	}
	cout<<f[n][k];
	return 0;
}
```

---

## 作者：Acheron_RBM (赞：0)

很显然的动态规划。

令 $f_{i,j}$ 为 $n=i$，$k=j$ 时满足题意的集合数。

依题意可得：一个集合可以只由另一个集合添加元素或将所有元素除二得到。

初始：$f_{0,0}=1$。

目标：$f_{n,k}$。

所以可得：

- $f_{i,j}=f_{i-1,j-1}+f_{i,j}$。
- $f_{i,j}=f_{i,j×2}+f_{i,j}$。

#### 代码：

```cpp
int main()
{
	int n,k;
	cin>>n>>k;
	f[0][0]=1;
	for(int i=1;i<=n;i++)
	{
		for(int j=i;j>=1;j--)
		{
			f[i][j]=f[i-1][j-1];
			if(j*2<=i)
			{
				f[i][j]+=f[i][j*2];
			}
			f[i][j]%=998244353;
		}
	}
	cout<<f[n][k];
	return 0;
}
```

---

## 作者：codwarm (赞：0)

[原题链接](https://www.luogu.com.cn/problem/AT_arc107_d)

在反复拜读题解对于 DP 式子的解释后终于搞懂了，于是来交一发题解，总结一下心得。因此本篇题解主要针对 DP 式的解释。
## 题目分析
首先，很明显可以设出一个 $dp_{n,k}$ 的状态表示选择 $n$ 个数和为 $k$。
状态转移如下：

若第 $n$ 个数取 $1$，则有 $dp_{n,k} = dp_{n-1,k-1}$。这点应该还是比较好理解的。

若第 $n$ 个数取分数，因为分数均为 $2$ 的 $-x$ 次幂，可以这样想象：相当于将原来的集合全部乘 $2$，然后选择 $n$ 个数，满足和为 $2k$，然后让新集合的第 $n$ 位做出选择。接着集合全部除回去，我们会惊奇地发现我们选择的第 $n$ 个数恰好不等于 $1$ 且同样是 $2$ 的 $-x$ 次幂。

即 $dp_{n,k} = dp_{n,2 \times k}$。

最终的 $dp_{n,k}$ 为上述两种情况的和。
即 $dp_{n,k} = dp_{n,2 \times k} + dp_{n-1,k-1}$。

再处理一下边界条件 $dp_{0,0} = 1$ 和一些小细节就搞定了！

```cpp
#include<bits/stdc++.h>
using namespace std;
//记得开两倍N
const int N = 6005,mod = 998244353;
int dp[N][N],n,k;
int main()
{
	scanf("%d%d",&n,&k);
	dp[0][0] = 1;// 边界条件
	for (int i = 1;i <= n;i++)
		for (int j = i;j >= 1;j--) // 转移，由于需要先得出dp[i][j*2]，所以倒序枚举。
			dp[i][j] += dp[i-1][j-1] % mod + dp[i][j*2] % mod,dp[i][j] %= mod;
	cout << dp[n][k] << endl;
	return 0;
}
```


---

## 作者：Xy_top (赞：0)

一直在往一些奇奇怪怪的地方想，没想到竟如此简单！

设 $f_{i,j}$ 为 $n=i$ $k=j$ 时的答案，不难发现一个集合可以从某个集合中所有的元素除以二，或者从一个集合中加上一得到，然后就结束了...

```cpp
#include <bits/stdc++.h>
#define int long long
#define For(i, a, b) for (int i = (a); i <= (b); i ++)
#define foR(i, a, b) for (int i = (a); i >= (b); i --)
using namespace std;
int n, k;
int f[3005][3005];
const int mod = 998244353;
void solve () {
	cin >> n >> k;
	For (i, 1, n) {
		f[i][i] = 1;
		foR (j, i - 1, 1) {
			f[i][j] += f[i - 1][j - 1];
			if (j * 2 <= i) f[i][j] += f[i][j * 2];
			f[i][j] %= mod;
		}
	}
	cout << f[n][k];
}
signed main () {
	int _ = 1;
//	cin >> _;
	while (_ --) {
		solve ();
		cout << '\n';
	}
	return 0;
}
```


---

