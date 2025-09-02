# [ARC187B] Sum of CC

## 题目描述

对于序列 $A=(A_1,A_2,\cdots,A_N)$ ，定义 $f(A)$ 如下：

- 图中包含 $N$ 个点，编号 $1\sim N$，初始没有边。对于每个满足 $1\le i<j\le N$ 的二元组 $(i,j)$，如果 $A_i\le A_j$，则在节点 $i,j$ 之间连接一条双向边。
- $f(A)$ 是图中的连通块数量。

给定序列 $B=(B_1,B_2,\cdots,B_N)$，每一项的值 $1\le B_i\le M$ 或者 $B_i=-1$。

将 $B$ 序列中的 $-1$ 替换为 $1$ 到 $M$ 中的整数，有 $M^q$ 种不同的序列 $B'$，其中 $q$ 是 $B$ 序列中 $-1$ 的数量。

求所有 $B'$ 序列的 $f(B')$ 之和 $\bmod 998\ 244\ 353$。

## 样例 #1

### 输入

```
3 3
2 -1 1```

### 输出

```
6```

## 样例 #2

### 输入

```
10 8
-1 7 -1 -1 -1 2 -1 1 -1 2```

### 输出

```
329785```

## 样例 #3

### 输入

```
11 12
-1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1```

### 输出

```
529513150```

# 题解

## 作者：Polarisx (赞：8)

[题目传送门](https://www.luogu.com.cn/problem/AT_arc187_b)。

啊。简单题。

## 思路

首先很容易发现连通块一定是以区间形式呈现在该序列上的，这个是容易证明的：

对于点 $i,j(i<j)$，若 $a_i\le a_j$，那么对于 $\forall k\in [i,j]$：

- 若 $a_k\ge a_j$，$(i,k)$ 存在连边。
- 若 $a_k<a_j$，$(k,j)$ 存在连边。

综上，$[i,j]$ 每个点互相连通。

此时对于一个序列，连通块数等于分割点数量加 $1$（分割点指将序列分成若干个区间中间那些点）。

考虑枚举这些分割点，假设为 $i$，这个点能成为分割点当且仅当左边的点与右边的点之间没有连边，即 $\min_{j\le i} b_j>\max_{j>i}b_j$。

记 $gmin_j$ 表示当前位置 $i$ 左边最小值**大于等于** $j$ 的方案数，$p$ 为 $i$ 前面有多少个 $-1$，那么显然有 $gmin_j=(m-j+1)^p$，同理可以求出位置 $i$ 右边最大值**小于等于** $j$ 的方案数，紧接着可以求出最大值**恰好**等于 $j$ 的方案数 $gmax_j$，位置 $i$ 的贡献就是 $\sum_{j=2}^m gmin_j\times gmax_{j-1}$。

时间复杂度 $\mathcal O (nm\log n)$。


```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int Mod=998244353;
const int Maxn=2010;
int n,m;
int b[Maxn],pre[Maxn],suf[Maxn];
int pmn[Maxn],pmx[Maxn];

ll gmin[Maxn],gmax[Maxn];

inline ll ksm(ll a,int b,int mod){
    ll z=1;
    while(b){
        if(b&1) z=z*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return z;
}
ll ans;

int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",&b[i]);
    pmn[0]=m;
    for(int i=1;i<=n;i++){
        if(b[i]==-1) pmn[i]=pmn[i-1];
        else pmn[i]=min(pmn[i-1],b[i]);
    }
    for(int i=n;i;i--){
        if(b[i]==-1) pmx[i]=pmx[i+1];
        else pmx[i]=max(pmx[i+1],b[i]);
    }
    for(int i=1;i<=n;i++) pre[i]=pre[i-1]+(b[i]==-1);
    for(int i=n;i;i--) suf[i]=suf[i+1]+(b[i]==-1);

    for(int p=1;p<=n;p++){
        for(int j=1;j<=m;j++) gmin[j]=gmax[j]=0;
        for(int j=1;j<=pmn[p];j++) gmin[j]=ksm(m-j+1,pre[p],Mod);
        for(int j=pmx[p+1];j<=m;j++) gmax[j]=ksm(j,suf[p+1],Mod);
        for(int j=2;j<=m;j++) ans=(ans+gmin[j]*(gmax[j-1]-gmax[j-2])%Mod)%Mod;
    }
    ans=(ans+ksm(m,pre[n],Mod))%Mod;
    ans=(ans%Mod+Mod)%Mod;
    printf("%lld",ans);
    
    system("pause");
    return 0;
}
```

---

## 作者：Hadtsti (赞：4)

### 题目分析

考虑一下连通块数该怎么转化。首先明确一点就是每个连通块一定包含的是编号在一定区间内的结点，也就是如果有两个点在同一连通块中，夹在它们中间的也在这一连通块中。证明可考虑反证，若存在 $i,i+2$ 在同一连通块而 $i+1$ 不在，则有 $a_i>a_{i+1},a_i\le a_{i+2},a_{i+1}>a_{i+2}$，矛盾！

也就是说我们将原序列分成了好几段，那么我们只需要在每段的左端点统计一下就可以了。现在的问题是什么情况下 $i$ 点会新开一段。显然，如果 $\exist j\in[i,n],k\in[1,i)$ 使得 $a_j\le a_k$，$j$ 一定会向 $k$ 连边，那么 $i$ 显然不合法。设 $a$ 的前缀 $\min$ 数组为 $b_i$，后缀 $\max$ 数组为 $c_i$，则上述条件等价于 $b_{i-1}>c_i$。事实上这也是充分条件，因为这样的话 $i$ 前面的点就压根不会向 $i$ 及之后的点连边，也就是 $i$ 一定会新开一段。

那么我们直接维护只考虑 $a_1,a_2,\cdots,a_i$ 时 $b_i=j$ 的方案数 $f_{i,j}$，以及只考虑 $a_i,a_{i+1},\cdots,a_n$ 时 $c_i\le j$ 的方案数 $g_{i,j}$。我们统计一下 $\sum\limits_{i=1}^nf_{i-1,j+1}g_{i,j}$ 即可。

### 代码实现


```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=998244353;
int n,m,a[2010],f[2010][2010],g[2010][2010],ans;
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	f[0][m+1]=1;
	for(int i=1;i<=n;i++)
	{
		if(~a[i])
		{
			for(int j=1;j<=a[i];j++)
				f[i][j]=f[i-1][j];
			for(int j=a[i]+1;j<=m+1;j++)
				(f[i][a[i]]+=f[i-1][j])%=mod,f[i][j]=0;
		}
		else
		{
			int s=f[i-1][m+1];
			for(int j=m;j;j--)
			{
				f[i][j]=(1ll*f[i-1][j]*(m-j+1)+s)%mod;
				(s+=f[i-1][j])%=mod;
			}
		}
	}
	g[n+1][0]=1;
	for(int i=n;i;i--)
	{
		if(~a[i])
		{
			for(int j=a[i];j<=m;j++)
				g[i][j]=g[i+1][j];
			for(int j=0;j<a[i];j++)
				(g[i][a[i]]+=g[i+1][j])%=mod,g[i][j]=0;
		}
		else
		{
			int s=g[i+1][0];
			for(int j=1;j<=m;j++)
			{
				g[i][j]=(1ll*g[i+1][j]*j+s)%mod;
				(s+=g[i+1][j])%=mod;
			}
		}
	}
	for(int i=1;i<=n;i++)
	{
		int s=0;
		for(int j=1;j<=m;j++)
		{
			(s+=g[i][j])%=mod;
			(ans+=1ll*f[i-1][j+1]*s%mod)%=mod;
		}
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：Mirage_Insane (赞：3)

我们先来证一个重要的结论：每个连通块的节点的编号一定是**连续的**。

要证明这个结论，我们需要说明若 $i$ 和 $j$ 之间有连边，则 $i$ 到 $j$ 的所有点都在同个连通块上。显然，我们有 $a_i \leq a_j$，我们对 $i < k < j$ 的所有 $k$ 分类讨论，若 $a_k \leq a_j$，则 $k$ 与 $j$ 有连边，若 $a_k > a_j$，则必有 $a_i \leq a_k$，故 $k$ 与 $i$ 有连边。至此，结论得证。

我们设有 $num$ 个 $i$ 与 $i + 1$ 不在一个联通块上，则答案为 $1 + num$。考虑什么情况下 $i$ 与 $i + 1$ 对答案有贡献，显然需要满足 $\min\limits^{i}_{j = 1}a_j > \max\limits^{n}_{j = i + 1}a_j$，因此我们对于每一个 $i$，枚举其前缀最小值再计算有多少种情况有贡献就可以了。

具体而言，先预处理出前缀最小值 $Min$ 与后缀最大值 $Max$，再预处理出 $pre$ 与 $suf$ 分别表示一段前缀有多少个可变点以及一段后缀有多少个可变点。

然后，我们枚举当前位置 $i$ 的前缀最小值 $j$，显然 $j$ 的范围只能是 $[Max_{i + 1} + 1, Min_i]$。而要对答案有贡献，后面 $suf_{i + 1}$ 个点显然只能在 $[1, j - 1]$ 范围取，即有 $(j - 1)^{suf_{i + 1}}$ 种情况。前面 $pre_i$ 个点的取值情况需要分讨一下。

当 $j = Min_i$ 时，是简单的，这 $pre_i$ 个点只需要在 $[j, m]$ 的范围内即可，一共有 $(m - j + 1)^{pre_i}$ 种情况。否则，这 $pre_i$ 个点中必须要有若干个点变成 $j$，剩余点在 $[j, m]$ 的范围内即可。

但是若干点是多少个点呢？不知道。所以就只能枚举，这样复杂度就达到了 $O(n^2m)$，过不了。因此我们考虑预处理一个 $dp_{i, j}$，表示有 $i$ 个点的取值范围为 $[1, m]$，且他们的最小值为 $j$ 的方案数，这样我们的答案即为 $dp_{pre_i, j}$。

怎么转移呢？显然有 $dp_{i, j} = dp_{i - 1, j} \times (m - j + 1) + \sum\limits^{m}_{k = j + 1}dp_{i - 1, k}$。前面一坨表示当前最小值已经达到了 $j$，那当前点只需要在 $[j, m]$ 任取即可。后面一坨表示当前最小值还未达到 $j$，那当前点必选 $j$。观察式子，容易发现加上一个后缀和优化后可以做到 $O(1)$ 转移。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define SF scanf
#define PF printf
#define int long long
const int mod = 998244353;
int qkpow(int a, int b) {
    int ans = 1;
    while(b) {
        if(b & 1) ans = ans * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return ans;
}
int a[2005], pre[2005], suf[2005], Min[2005], Max[2005], dp[2005][2005], Suf[2005][2005];
signed main() {
    int n, m;
    SF("%lld%lld", &n, &m);
    for(int i = 1; i <= m; i++) dp[1][i] = 1, Suf[1][i] = m - i + 1;
    for(int i = 2; i <= n; i++) {
        for(int j = m; j; j--) {
            dp[i][j] = (dp[i - 1][j] * (m - j + 1) % mod + Suf[i - 1][j + 1]) % mod;
            Suf[i][j] = (Suf[i][j + 1] + dp[i][j]) % mod;
        }
    }
    Min[0] = m, Max[n + 1] = 1;
    for(int i = 1; i <= n; i++) SF("%lld", &a[i]), pre[i] = pre[i - 1] + (a[i] == -1), Min[i] = min(Min[i - 1], a[i] == -1 ? m : a[i]);
    for(int i = n; i; i--) suf[i] = suf[i + 1] + (a[i] == -1), Max[i] = max(Max[i + 1], a[i]);
    int ans = 0;
    for(int i = 1; i < n; i++) {
        for(int j = Min[i]; j > Max[i + 1]; j--) {
            if(j == Min[i]) ans = (ans + qkpow(j - 1, suf[i + 1]) * qkpow(m - j + 1, pre[i]) % mod) % mod;
            else ans = (ans + qkpow(j - 1, suf[i + 1]) * dp[pre[i]][j] % mod) % mod;
        }
    }
    PF("%lld", (ans + qkpow(m, pre[n])) % mod);
    return 0;
}
```

---

## 作者：wangziyue_AK (赞：2)

## 思路历程
考虑一个给定的序列有什么简洁地计算其连边后的联通块个数的方式，初步想法是建出单调栈，输出单调栈中的元素个数，但这个东西显然不好计算（~~而且也很假~~）。然后我们发现每个后缀最大值不可能向后连边(对完了)，所以它肯定自成一个联通块，但打出代码会发现过不了样例，答案会大很多。仔细思考后会发现它会被形如 $1,5,2,3$ 这样的数据卡掉，因为虽然后缀最大值不可能向后连边，但前面的一些点可能同时向它和它后方的点连边，使该点也被连进其他联通块。那么这是就给了我们一个启示，两个联通块分开当且仅当前者的最低点高于右边的最高点。
## 维护方式
考虑拆贡献，对于所以 $1 \le i \le n-1$ 计算把 $i$ 和 $i + 1$ 分成两部分的方案数，对于每种方案把联通块的个数加一。最后在加上原有的联通块个数，即任意选择的方案数。
那么我们维护确定值的前缀最小值和后缀最大值，若前缀最小值大于后缀最大值，则存在分割开的方案，那么我们钦定前缀最小值，则前缀有 $q$ 个问号，最小值为 $V+1$ 的方案数为 $(m-V)^{q}-(m-V-1)^q$(因为要减去最小值大于 $V+1$ 的方案数)，再乘上 $V^{Q-q}$(Q为总问号数)。注意还有一个细节，当 $V+1=premin$ 时不需要减。所以最后的式子就是$m^Q+\sum_{i=1}^{n-1} \sum_{V=sufmax}^{premin-1}((m-V)^{q}-(m-V-1)^q) \times V^{Q-q}$。算这个式子时要特判 $V+1=premin$ 。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pr;
#define fi first
#define se second
typedef double db;
#define pb push_back
#define eb emplace_back
#define bcnt __builtin_popcount
#define TS printf("!!!tiaoshi\n")
const int p=998244353;
const int N=3005;
//inline void add(int &x,int y){ (x+=y)>=p&&(x-=p);}
inline void add(int &x,int y){ x=(x+y)%p;}
inline int jia(int x,int y){ return (x+y)>=p?x+y-p:x+y; }
inline int mul(int x,int y){ return (1ll*x*y)%p;}
inline void del(int &x,int y){ (x-=y)<0&&(x+=p);}
inline int fp(int x,int y){
	if(y<0) return 0;
	int res=1;
	while(y){
		if(y&1) res=mul(res,x);
		x=mul(x,x),y>>=1;
	}
	return res;
}
int n,m,a[N],pre[N],suf[N],cnt[N];
void sol(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	pre[0]=m;
	for(int i=1;i<=n;i++){
		if(a[i]==-1) cnt[i]=cnt[i-1]+1,pre[i]=pre[i-1];
		else cnt[i]=cnt[i-1],pre[i]=min(pre[i-1],a[i]);
	}
	for(int i=n;i;i--) suf[i]=max(suf[i+1],a[i]);
	int ans=fp(m,cnt[n]);
	for(int i=1;i<n;i++){
		if(pre[i]<=suf[i+1]) continue;
		for(int j=suf[i+1];j<pre[i];j++){
			int g=1;
			if(cnt[i]){
				g=fp(m-j,cnt[i]);
				if(j+1!=pre[i]) del(g,fp(m-j-1,cnt[i]));
			}
			g=mul(g,fp(j,cnt[n]-cnt[i]));
			add(ans,g);
		}
	}
	printf("%d",ans);
}
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout); 
	int T=1;
	//scanf("%d",&T);
	while(T--) sol(); 
	
	return 0;
}
```

---

## 作者：HNOIRPplusplus (赞：2)

根据题目，如果 $i<j$ 且 $A_i\le A_j$ 就会有一条边，则 $i$ 和 $i+1$ 之间断开成两个连通分量的充要条件就是 $i$ 及以前的最小值大于 $i+1$ 及以后的最大值。

设 $dp_{i,j}$ 表示前 $i$ 个数，最小值为 $j$ 的可能填法一共有多少种。假设第 $i$ 位填写 $k$，则可以有转移

$$
\sum_{j=k}^M dp_{i-1,j}\rightarrow dp_{i,\min(j,k)}
$$

对其进行前缀和优化转移即可做到 $O(NM)$。后缀最大值同样转移。

接下来，我们计算下列表达式的值：

$$
\sum_{i=1}^{N-1}\sum_{j=1}^M\sum_{k=1}^{j-1}dp_{i,j}\times dp_{i+1,k}
$$

该表达式表达了所有的两个连通分量中间的间隔，同样使用前缀和优化可以做到 $O(NM)$。由于连通分量的实际个数为间隔加一，所以我们再加上所有的填法一种一个就可以得到答案。

``` cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int N = 2005, mod = 998244353;

int b[N];
int dp[N][N], dp2[N][N];
int pre[N][N], nxt[N][N];

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  int n, m;
  cin >> n >> m;
  for(int i = 1; i <= n; i++) {
    cin >> b[i];
  }
  if(b[1] == -1) {
    for(int j = m; j; j--) {
      dp[1][j] = 1;
      pre[1][j] = pre[1][j + 1] + dp[1][j];
    }
  } else {
    dp[1][b[1]] = 1;
    for(int j = m; j; j--) {
      pre[1][j] = pre[1][j + 1] + dp[1][j];
    }
  }
  for(int i = 2; i <= n; i++) {
    if(b[i] > 0) {
      for(int j = 1; j < b[i]; j++) {
        (dp[i][j] += dp[i - 1][j]) %= mod;
      }
      (dp[i][b[i]] += pre[i - 1][b[i]]) %= mod;
    } else {
      for(int j = 1; j <= m; j++) {
        (dp[i][j] += dp[i - 1][j] * (m - j + 1) + pre[i - 1][j + 1]) %= mod;
      }
    }
    for(int j = m; j; j--) {
      pre[i][j] = (pre[i][j + 1] + dp[i][j]) % mod;
    }
  }

  if(b[n] == -1) {
    for(int j = 1; j <= m; j++) {
      dp2[n][j] = 1;
      nxt[n][j] = nxt[n][j - 1] + dp2[n][j];
    }
  } else {
    dp2[n][b[n]] = 1;
    for(int j = 1; j <= m; j++) {
      nxt[n][j] = nxt[n][j - 1] + dp2[n][j];
    }
  }
  for(int i = n - 1; i; i--) {
    if(b[i] > 0) {
      for(int j = b[i] + 1; j <= m; j++) {
        (dp2[i][j] += dp2[i + 1][j]) %= mod;
      }
      (dp2[i][b[i]] += nxt[i + 1][b[i]]) %= mod;
    } else {
      for(int j = 1; j <= m; j++) {
        (dp2[i][j] += dp2[i + 1][j] * j + nxt[i + 1][j - 1]) %= mod;
      }
    }
    for(int j = 1; j <= m; j++) {
      nxt[i][j] = (nxt[i][j - 1] + dp2[i][j]) % mod;
    }
  }
  int ans = 0, ans2 = 1;
  for(int i = 1; i < n; i++) {
    nxt[i][0] = 0;
    for(int j = 1; j <= m; j++) {
      nxt[i][j] = (nxt[i][j - 1] + dp2[i + 1][j]) % mod;
    }
    for(int j = m; j; j--) {
      (ans += dp[i][j] * nxt[i][j - 1]) %= mod;
    }
  }
  for(int i = 1; i <= n; i++) {
    if(b[i] < 0) {
      (ans2 *= m) %= mod;
    }
  }
  cout << (ans + ans2) % mod;
}
```

---

## 作者：TonviaSzt (赞：2)

[Problem Link](https://www.luogu.com.cn/problem/AT_arc187_b)

赛时被 A 硬控了 1h，Contest End 才会的 B，难绷。血的教训。

**题目大意**

> 给定长为 $N$ 的序列 $B$，$B_i=[1,M]\cap\{-1\}$，称 $i$ 和 $j$ 是连通的当且仅当 $i<j$ 且 $B_i\le B_j$。
>
> 要求你在所有 $B_i=-1$ 的位置填入值在 $[1,M]$ 的数，求出所有填法的联通块总数。
>
> **Hint**：记 $B_i=-1$ 的位置个数为 $k$，可知共有 $M^k$ 种填法。

**思路分析**

联想到 [CF2031D](https://codeforces.com/contest/2031/problem/D) Editorial 给出的巧妙性质。

对于 $i<j$ 且 $B_i\le B_j$ 的条件，考虑 $i,i+1$ 是如何连通的。

- 情况一：$B_i\le B_{i+1}$

- 情况二：$\exist\  j<i<i+1<k$ 且 $B_j\le B_i,B_{i+1}\le B_k$，可以通过 $i\rarr j\rarr k\rarr i+1$​ 连通。

换句话说，若 $i,i+1$ 不连通，需要满足 $\forall j\in[1,i],k\in[i+1,n],B_j>B_k$。

于是每个连通块是一段区间，值域以单调下降的方式呈现。

![](https://cdn.luogu.com.cn/upload/image_hosting/yj795abk.png)

不妨设 $f_{i,j}$ 为 $i$ 与 $i+1$ 不连通，$[1,i]$ 值域为 $[j+1,m]$ 的方案数，连通块数目即 $M^k+\sum f_{i,j}$，时间复杂度 $O(NM)$。

[Submission](https://atcoder.jp/contests/arc187/submissions/59933571)

---

## 作者：cancan123456 (赞：1)

这一场先过了 B 再过了 A /fendou

性质 1：一个连通分量内点的编号连续。

证明：反证法，设 $l<i<r$ 使得 $l,r$ 在一个连通分量内但 $i$ 不在这个连通分量内。

1. $A_l\le A_r$，若 $A_i\ge A_l$，则 $i,l$ 之间有边，在一个连通分量内，否则 $A_i<A_l\le A_r$，$i,r$ 之间有边，也在一个连通分量内。
2. $A_l>A_r$，考虑任意一条从 $l$ 到 $r$ 的路径，显然路径中一定存在 $p,q$ 满足 $p<i<q$ 且 $p,q$ 间有边，即 $A_p\le A_q$，转化为情况 1。

所以我们知道 $f(A)=1+\sum_{i=1}^{n-1}[i,i+1\text{ 不在一个连通分量内}]$。

性质 2：$i,i+1$ 不在一个连通分量内 $\iff$ $\min_{j=1}^i A_j>\max_{j=i+1}^n A_j$。

左推右：反证法，若 $\min_{j=1}^i A_j\le\max_{j=i+1}^n A_j$，则存在 $1\le p\le i<i+1\le q\le n$ 使得 $A_p\le A_q$，此时因为 $A_p,A_q$ 是最小值，我们有 $A_p\le A_i,A_{i+1}\le A_q$，则 $i,i+1$ 之间存在路径 $i\to p\to q\to i+1$。

右推左：反证法，取 $i,i+1$ 间任意一条路径中任意一条跨过 $i,i+1$ 的边 $(p,q)$，此时有 $A_p\le A_q$ 且 $p\le i<i+1\le q$，则此时有 $\min_{j=1}^iA_i\le A_p\le A_q\le\max_{j=i+1}^nA_j$，与假设矛盾。

现在我们枚举 $i$ 与 $x=\min_{j=1}^iA_j$，用 DP 算出前缀的 $B_i$ 选择的方案数（需要后缀和优化），对于后缀，显然应当满足 $\max_{j=i+1}^nB_j<x$，则此时若后缀有 $y$ 个 $-1$，后缀的方案数就是 $(x-1)^y$。

时间复杂度为 $O(nm)$，可以通过此题。

```cpp
#include <cstdio>
using namespace std;
typedef long long ll;
const ll mod = 998244353;
const int N = 2005;
ll f[N][N], suf[N][N], pow[N][N];
int b[N], suf_max[N], suf_cnt[N];
int max(int a, int b) {
	return a > b ? a : b;
}
int main() {
//	freopen("in.txt", "r", stdin);
	int n, m;
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &b[i]);
	}
	for (int i = n; i >= 1; i--) {
		suf_max[i] = max(suf_max[i + 1], b[i]);
		suf_cnt[i] = suf_cnt[i + 1];
		if (b[i] == -1) {
			suf_cnt[i]++;
		}
	}
	for (int i = 0; i <= m; i++) {
		pow[i][0] = 1;
		for (int j = 1; j <= n; j++) {
			pow[i][j] = pow[i][j - 1] * i % mod;
		}
	}
	f[0][m] = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = m; j >= 1; j--) {
			suf[i - 1][j] = (suf[i - 1][j + 1] + f[i - 1][j]) % mod;
		}
		if (b[i] == -1) {
			for (int j = 1; j <= m; j++) {
				f[i][j] = (suf[i - 1][j] + f[i - 1][j] * (m - j)) % mod;
			}
		} else {
			for (int j = 1; j < b[i]; j++) {
				f[i][j] = f[i - 1][j];
			}
			for (int j = b[i]; j <= m; j++) {
				f[i][b[i]] = (f[i][b[i]] + f[i - 1][j]) % mod;
			}
		}
	}
	ll ans = 0;
	for (int i = 1; i < n; i++) {
		for (int j = suf_max[i + 1] + 1; j <= m; j++) {
			ans = (ans + pow[j - 1][suf_cnt[i + 1]] * f[i][j]) % mod;
		}
	}
	ll add = 1;
	for (int i = 1; i <= n; i++) {
		if (b[i] == -1) {
			add = add * m % mod;
		}
	}
	printf("%lld", (ans + add) % mod);
	return 0;
}
```

---

## 作者：yanzihe (赞：1)

赛后5分钟过题，写篇题解记录一下。

## 一个结论
这题显然要找到序列A和建出的图的连通块个数之间的关系，考虑手算一组数据来启发思路:  
> 11 5 6 10 1 2 4 2


发现 $1$ 可以和 $2$，$4$，$2$ 连边，所以得出了结论：  
> 全局最小值右侧（包括最小值）的所有数相互连通。


回到原序列，$1, 2, 4, 2$ 已经形成了一个连通块，那么 $1$ 左侧的情况如何呢？模仿之前的思路，发现 $11, 5, 6, 10$ 中的最小值 $5$ 可以向它右侧的点 $6, 10$ 连边，于是 $5, 6, 10$ 形成了一个连通块。

在这个数据的启发下，可以得到结论：
> 任意一个区间内，区间最小值右侧的所有数相互连通。

接下来我们再看一组数据：
> 11 5 6 10 1 2 4 200

使用之前得到的结论发现，$1, 2, 4, 200$ 是一个连通块，而 $5, 6, 10$ 是一个连通块。

然而，这次情况似乎有所不同，$5$ 的确和 $6, 10$ 连通，但是 $1$ 右侧的数中有一个特别大的 $200$，导致 $5$ 还和 $200$ 连通，所以 $5$ 右侧的所有数其实是一个连通块，而非两个。

现在，我们总结以上得到的经验，得出结论：
> 某一个位置左侧的数和右侧的数不连通，当且仅当左侧的最小值大于右侧的最大值。

(请确保你理解这个结论)



## 解法
然后回到本题，题目所求的连通块个数，可以转化为断点（左侧的数和右侧的数不连通的位置）个数加一，而断点显然可以用DP来计数。    
具体来说：$f[i][j]$ 表示前 $i$ 个数中，有多少种情况使得它们的最小值是 $j$。  
$g[i][j]$ 表示第 $i$ 个到第 $n$ 数中，有多少种情况使得它们的最大值是 $j$。  
转移十分显然，只需要讨论 $b[i]$ 和 $j$ 的大小关系即可，使用前/后缀和优化容易做到 $\mathcal{O}(nm)$。

```cpp
 for(ll i=2;i<=n;i++){
        for(ll j=1;j<=Min[i];j++){//Min[i]是前i个数中已经被固定的数的最小值
            if(b[i]!=-1){
                if(b[i]==j)f[i][j]=s[i-1][j];//s[i][j]是f[i][j]的后缀和，即s[i][j]=f[i][j]+f[i][j+1]+...+f[i][m]
                else f[i][j]=f[i-1][j];
            }else{
                (f[i][j]=f[i-1][j]*(m-j)%MOD+s[i-1][j])%=MOD;;//分b[i]>j和b[i]=j两种情况
            }
        }
        for(ll j=Min[i];j>=1;j--){
            (s[i][j]=s[i][j+1]+f[i][j])%=MOD;
        }
    }
```
以上是计算 $f$ 的代码，计算 $g$ 的代码类似，就不放了。  
算出 $f$ 和 $g$ 后，枚举断点即可算出答案。


```cpp
for(ll i=1;i<=n-1;i++){
    //左侧全部大于等于j，必须有一个等于
    //右侧全部小于j
    for(ll j=Max[i+1]+1;j<=Min[i];j++){//Max[i]是b数组后缀最大值
            (ans+=f[i][j]*sg[i+1][j-1]%MOD)%=MOD;//sg数组是g数组的前缀和，sg[i][j]=g[i][1]+g[i][2]+...+g[i][j]
        }
    }
```
~~什么时候不再赛后5分钟过题呢？~~

---

## 作者：Creeper_l (赞：1)

若 $i$ 与 $j$ 有边，也就是 $a_i<a_j$，那么对于一个 $i < k < j$，会发现 $a_k>a_i$ 和 $a_k<a_j$ 至少满足一个。也就是说 $k$ 也一定和 $i,j$ 联通。于是我们发现了一个关键性质：所有联通块都为一个区间。

那我们考虑 $i$ 和 $i+1$ 什么时候不联通：$i$ 之前的任意一个数都大于 $i$ 之后的任意一个数。也就是前缀 $\min$ 大于后缀 $\max$ 的时候。

那就可以先用 dp 预处理出前 $i$ 个数的前缀 $\min$ 为 $j$ 的方案数，后缀同理。因为联通块数其实就是有多少个 $i$ 和 $i+1$ 不联通，所以直接枚举 $i$ 然后用 dp 值统计答案即可。需要前缀和优化。

```
//dzzfjldyqqwsxdhrdhcyxll
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e3 + 10;
const int mod = 998244353;
int n,m,a[MAXN],f[MAXN][MAXN],sum[MAXN][MAXN],ans,g[MAXN][MAXN];
signed main() {
	cin >> n >> m;
	for(int i = 1;i <= n;i++) cin >> a[i];
	f[0][m] = 1,sum[0][0] = f[0][0];
	for(int i = 1;i <= m;i++) 
		sum[0][i] = (sum[0][i - 1] + f[0][i]) % mod;
	for(int i = 1;i <= n;i++) {
		for(int j = 1;j <= (a[i] == -1 ? m : a[i]);j++) {
			f[i][j] = f[i - 1][j] * (a[i] == -1 ? (m - j + 1) : 1) % mod;
			if(j == a[i] || a[i] == -1) f[i][j] = (f[i][j] + sum[i - 1][m] - sum[i - 1][j] + mod) % mod;
		}
		for(int j = 1;j <= m;j++) sum[i][j] = (sum[i][j - 1] + f[i][j]) % mod;
	}
	memset(sum,0,sizeof sum);
	g[n + 1][0] = 1,sum[n + 1][0] = g[n + 1][0];
	for(int i = 1;i <= m;i++) 
		sum[n + 1][i] = (sum[n + 1][i - 1] + g[n + 1][i]) % mod;
	for(int i = n;i >= 1;i--) {
		for(int j = (a[i] == -1 ? 1 : a[i]);j <= m;j++) {
			g[i][j] = g[i + 1][j] * (a[i] == -1 ? j : 1) % mod;
			if(j == a[i] || a[i] == -1) g[i][j] = (g[i][j] + sum[i + 1][j - 1]) % mod;
		}
		for(int j = 1;j <= m;j++) sum[i][j] = (sum[i][j - 1] + g[i][j]) % mod;
	}
	for(int i = 1;i <= n;i++) 
		for(int j = 1;j <= m;j++) 
			ans = (ans + f[i][j] * sum[i + 1][j - 1]) % mod;
	cout << ans;
	return 0;
}
```

---

## 作者：_determination_ (赞：0)

~~根据 CF1270H 经典结论，这题就做完了。~~

经典结论 1：当 $a_i\leq a_j$ 的时候，$[i,j]$ 是一个联通块。

证明：考虑分讨 $a_k(k\in [i,j])$ 相对于 $a_i$ 和 $a_j$ 的大小。显然一个数要么大于 $a_i$ 要么小于 $a_j$。那么 $k$ 显然会和 $i$ 或 $j$ 连边。而 $i$ 和 $j$ 也会连边，所以这是一个联通块。

经典结论 2：联通块个数等于 1 加断点个数。这个显然。

那么我们枚举断点，一个地方可以成为断点当且仅当左侧的所有数大于右侧所有数。

$f_{i,j}$ 表示前 $i$ 个数的 $\min$ 为 $j$ 的方案数，$g_{i,j}$ 表示 $i$ 之后的 $\max$ 为 $j$ 的方案数。这个好搞，然后枚举断点左侧的 $\max$ 然后统计即可。

https://atcoder.jp/contests/arc187/submissions/59917447

---

