# Majority

## 题目描述

Everyone was happy coding, until suddenly a power shortage happened and the best competitive programming site went down. Fortunately, a system administrator bought some new equipment recently, including some UPSs. Thus there are some servers that are still online, but we need all of them to be working in order to keep the round rated.

Imagine the servers being a binary string $ s $ of length $ n $ . If the $ i $ -th server is online, then $ s_i = 1 $ , and $ s_i = 0 $ otherwise.

A system administrator can do the following operation called electricity spread, that consists of the following phases:

- Select two servers at positions $ 1 \le i < j \le n $ such that both are online (i.e. $ s_i=s_j=1 $ ). The spread starts only from online servers.
- Check if we have enough power to make the spread. We consider having enough power if the number of turned on servers in range $ [i, j] $ is at least the number of turned off servers in range $ [i, j] $ . More formally, check whether $ 2 \cdot (s_i + s_{i+1} + \ldots + s_j) \ge j - i + 1 $ .
- If the check is positive, turn on all the offline servers in range $ [i, j] $ . More formally, make $ s_k := 1 $ for all $ k $ from $ i $ to $ j $ .

We call a binary string $ s $ of length $ n $ rated if we can turn on all servers (i.e. make $ s_i = 1 $ for $ 1 \le i \le n $ ) using the electricity spread operation any number of times (possibly, $ 0 $ ). Your task is to find the number of rated strings of length $ n $ modulo $ m $ .

## 说明/提示

In the first example, the only rated string is 11. So the answer is $ 1 $ .

In the second example, the rated strings are:

- 111;
- 101, because we can perform an operation with $ i = 1 $ and $ j = 3 $ .

 So the answer is $ 2 $ .In the third sample, the rated strings are:

- 1001;
- 1111;
- 1011;
- 1101.

 So the answer is $ 4 $ .

## 样例 #1

### 输入

```
2 100```

### 输出

```
1```

## 样例 #2

### 输入

```
3 10```

### 输出

```
2```

## 样例 #3

### 输入

```
4 3271890```

### 输出

```
4```

## 样例 #4

### 输入

```
17 123456```

### 输出

```
32347```

# 题解

## 作者：Leasier (赞：22)

直接考虑合法条件似乎不太方便，考虑来观察一下一个长为 $n$ 的 01 串不合法的条件。

- 两端不全为 $1$。
- 或操作到不能操作时每一个 $0$ 连续段的长度皆 $>$ 其两边 $1$ 连续段的长度之和。

考虑 dp，设 $dp_{i, j}$ 表示长为 $i$，钦定两端为 $1$，一直操作直到不能再操作时最后一个 $1$ 连续段长度为 $j$ 的方案数。

初值：$dp_{1, 1} = 1$。

转移：对于 $dp_{i, i}$，考虑容斥，则有：$dp_{i, i} = 2^{i - 2} - \displaystyle\sum_{j = 1}^{\lfloor \frac{i - 1}{2} \rfloor} dp_{i, j}$。

对于其他 $dp_{i, j}$，考虑在 $dp_{j, j}$ 的基础上在前面依次添加一个 $0$ 连续段和一个 $1$ 连续段，则：$dp_{i, j} = dp_{j, j} \displaystyle\sum_{k = j + 2}^{i - j - 1} \sum_{l = 1}^{k - j - 1} dp_{i - j - k, l}$（后面这两坨本来是 $j + k < i, j + l < k$，这个限制可以被改写为 $(i - j - k) + l < i - 2j$）。

答案：$dp_{n, n}$。

前缀和优化 dp 即可。具体地，维护一个 $sum_i$ 表示所有满足 $j + k \leq i$ 的 $dp_{i, j}$ 之和。

时间复杂度为 $O(n^2)$。

代码：
```cpp
#include <stdio.h>

typedef long long ll;

int power[5007];
ll dp[5007][5007], sum1[10007], sum2[10007];

inline void init(int n, int m){
	power[0] = 1;
	for (int i = 1; i <= n; i++){
		power[i] = power[i - 1] * 2 % m;
	}
}

int main(){
	int n, m, k;
	scanf("%d %d", &n, &m);
	init(n, m);
	k = n * 2;
	dp[1][1] = sum1[2] = 1;
	for (int i = 2; i <= n; i++){
		for (int j = 1; j <= k; j++){
			sum2[j] = (sum2[j - 1] + sum1[j]) % m;
		}
		dp[i][i] = power[i - 2];
		for (int j = 1; j * 2 < i; j++){
			dp[i][j] = dp[j][j] * sum2[i - j * 2 - 1] % m;
			dp[i][i] = ((dp[i][i] - dp[i][j]) % m + m) % m;
		}
		for (int j = 1; j <= i; j++){
			int t = i + j;
			sum1[t] = (sum1[t] + dp[i][j]) % m;
		}
	}
	printf("%lld", dp[n][n]);
	return 0;
}
```

---

## 作者：dottle (赞：14)

首先，我们考察一个不合法的情况是什么样的：

- 原数列可以被划分为 $2p+1$ 段，奇数段可以变为全 $1$，偶数段全是 $0$。并且每个偶数段的长度大于与其相邻的两个奇数段长度之和。

那么，设 $g_{i,j}$ 表示当前的 $2p+1$ 段长度和为 $i$，最后一段长度为 $j$ 的方案数是多少。再设 $f_i$ 表示长为 $i$ 的合法段的数量。为了在这里方便考虑，虽然 $p=0$ 的时候实际上数列是合法的，但是我们仍然把他放到 $g$ 里面算，即 $g_{i,i}=f_i$。

这样，对于 $n\ge 2$，不合法加合法的数量是一定的，则有数量关系：

$$
f_i+\sum_{j=1}^{i-1}g_{i,j}=2^{n-2}
$$

因此，我们只需考虑如何递推 $g$，便可同时算出 $f$。

考虑根据定义写出 $g$ 的递推式：

$$
g_{i,j}=f_j \sum_{x=1}^i\sum_{k=1}^{i-x}[j+k<x]g_{i-x-j,k}
$$

即，最后一段的长度固定为 $j$，我们枚举上一段和上上段的长度。根据定义，最后一段有 $f_j$ 种方案。

直接根据这个写是 $O(n^4)$ 的考虑优化。把能转移到的 $g$ 写下来是这样的形式：$g_{d,1},g_{d-1,1\sim 2},\dots,g_{1,1\sim d}$，$d=i-2j-2$。那么我们只需要求每个点向左上角的射线的和，就可以递推这个 $s_d$ 表示上面那些 $g$ 的和了。可以参考代码来理解。

时间复杂度 $O(n^2)$。

```cpp
#include<bits/stdc++.h>
#define int long long
const int N=5005;
using namespace std;

int f[N],g[N][N],s[N],h[N][N];
// h 斜线之和 
int n,mod;

void add(int&x,int y){
	x+=y;
	x%=mod;
}

int gsc(int x,int y){
    int ans=1;
    for(int i=1;i<=y;i<<=1,x=x*x%mod)
        if(y&i)
            ans=ans*x%mod;
    return ans;
}int inv(int k){return gsc(k,mod-2);}

void solve(){
	cin>>n>>mod;
	f[1]=1;
	g[1][1]=1;
	s[1]=1;
	for(int i=2;i<=n;i++){
		for(int j=1;j*2-2<i;j++)
			g[i][j]=f[j]*s[i-j-2-j]%mod;
		f[i]=gsc(2,i-2);
		for(int j=1;j<=i;j++)
			add(f[i],mod-g[i][j]);
		add(g[i][i],f[i]);
		for(int j=1;j<=i;j++)
			h[i][j]=(h[i-1][j+1]+g[i][j])%mod;
		s[i]=(s[i-1]+h[i][1])%mod;
	}
	f[n]=(f[n]%mod+mod)%mod;
	cout<<f[n]<<endl;
}

main(){
	solve();
}

```


---

## 作者：Alex_Wei (赞：7)

### [CF1750F Majority](https://www.luogu.com.cn/problem/CF1750F)

很棒的题目。

我们称合并两个极长 $1$ 段 $[a, b], [c, d] (a\leq b < c \leq d)$ 为操作 $(a, d)$。显然，它们可合并当且仅当 $(b - a + 1) + (d - c + 1) \geq (c - b - 1)$。

首先，如果我们操作 $(i, j)$ 且 $[i, j]$ 有三段 $1$，则至少存在一对相邻的段可以合并。设交替的 $1$ 段和 $0$ 段长分别为 $o_1, z_1, o_2, z_2, o_3$，假设 $o_1, o_2$ 不可合并，$o_2, o_3$ 不可合并，则 $z_1 > o_1 + o_2$，$z_2 > o_2 + o_3$，不等式同侧相加后两侧加上 $o_1 + o_2 + o_3$ 得 $2(o_1 + o_2 + o_3) + o_2$ 小于总长，与 $2(o_1 + o_2 + o_3)$ 不小于总长的限制矛盾。对于更多段 $1$，可以类似证明。

考虑一个串合法的充要条件。则它一定可以通过若干次合并相邻的 $1$ 段，使得最终全为 $1$。

直接对合法串计数，我们无法优秀地描述所有 $1$ 段合并的过程。

正难则反，考虑对非法串计数。这样有一个非常大的好处，就是对于非法串，在尽可能地合并后，总存在一个态，使得任意相邻两段 $1$ 均无法合并。每个无法继续合并的态对应的非法串数量，等于每个 $1$ 段长度对应的合法串数量之积，这是因为，我们需要合并得到每个极长 $1$ 段，相当于长度为该极长 $1$ 段长度的合法串数量。这就是子结构，启发我们进行 DP。

为了避免转移时较繁琐地化简不等式，我们可以这样刻画合并操作：将所有 $1$ 段向左向右延伸它的长度，此时若两个 $1$ 段相邻或重合，则它们可合并。

设 $f_i$ 表示 $n = i$ 的答案，则首先两端必须是 $1$，有 $2 ^ {i - 2}$ 种方案。再减去两端为 $1$ 段但非法的串的数量。

具体地，设 $g_{i, j}$ 表示长为 $i$ 的串，以 $1$ 段开头，合并完（此时任意相邻两端均不可合并）以长度为 $j$ 的 $1$ 段结尾的方案数。则 $f_i$ 需要减去所有 $g_{i, j}$。

若 $g_{i, j}$ 从 $g_{i', j'}$ 转移，因为前一个 $1$ 段向右延伸到 $i' + j'$，而当前 $1$ 段向左延伸到 $i - 2j + 1$，为避免它们相邻或重合，显然要有 $i' + j' + 1 < i - 2j + 1$。此外还有贡献系数 $f_{j}$。为此，设 $h_i$ 表示 $i' + j' + 1 \leq i$ 的 $g_{i', j'}$ 之和，即可做到 $\mathcal{O}(n ^ 2)$。

注意 $g_{i, i} = f_i$，且初始值 $f_1 = 1$。

```cpp
#include <bits/stdc++.h>
using namespace std;
using ull = unsigned long long;
using L = __uint128_t;
struct FastMod {
  ull b, m;
  FastMod(ull b): b(b), m(ull((L(1) << 64) / b)) {}
  ull R(ull a) {
    ull q = ull((L(a) * m) >> 64), r = a - q * b;
    return r >= b ? r - b : r;
  }
};
constexpr int N = 5e3 + 5;
int n, m, pw[N], f[N], h[N << 1];
void add(int &x, int y) {x += y, x >= m && (x -= m);}
int main() {
  cin >> n >> m;
  FastMod F(m);
  for(int i = pw[0] = 1; i < N; i++) pw[i] = F.R(pw[i - 1] + pw[i - 1]);
  f[1] = 1, h[3] = 1;
  for(int i = 2; i <= n; i++) {
    add(h[i], h[i - 1]), f[i] = pw[i - 2];
    for(int j = 1; j < i >> 1; j++) {
      int val = F.R(1ll * h[i - 2 * j] * f[j]);
      add(f[i], m - val), add(h[i + j + 1], val);
    };
    add(h[i * 2 + 1], f[i]);
  }
  cout << f[n] << "\n";
  return 0;
}
```

---

## 作者：_SeeleVollerei_ (赞：4)

upd on 2022.11.9：修改了一些小错误，感谢 @Zigh_Wang。

判断一个串合法是比较困难的，考虑如何判断这个串不合法。

对于一个不合法的串，我们考虑让它一直操作到不能操作为止。

意思就是说，有 $x$ 段连续的 0 和 $x+1$ 段连续的 1，且每段 0 的数量都比它相邻两段 1 的数量的和要大。

假设我们统计了这个串的数量，怎么返回操作前的不合法的串呢？

显然每一段 0 就不变了，每一段 1 是独立的。我们按照 dp 的思路，令 $g_i$ 表示 $n=i$ 时的答案。那么一段长为 $len$ 的 1 的贡献就是 $g_{len}$。

那么我们考虑从左往右填 01 段。令 $f_{i,j}$ 表示填了 $i$ 位，且最后一段为 $j$ 个 1。这里的 $j$ 个 1 指的是操作到不能再操作后的连续段。

假设知道了 $f_{i,j}$，那么有 $g_i=2^{i-2}-\sum_{j<i}{f_{i,j}}$。就是总方案减去不合法的方案。

那么转移的时候每次枚举往后加一段 0，加一段 1，枚举这两段的长度即可。

把转移方程列出来，就是 $f_{i,j}=g_j\times\sum_{k,l\ge 1,k>l+j}f_{i-j-k,l}$。

然后我们发现，同一个 $f_{p,l}$ 至多只会向同一个 $f_{i,j}$ 转移一次，这启发我们直接根据条件去优化。

令 $p=i-j-k$，则 $k=i-j-p$。

当 $l<1$ 时，显然 $f_{p,l}$ 的值一定为 0，所以这个条件可以忽略。

把剩下的条件列出来，分别为 $k\ge 1$ 和 $k>l+j$。

然后后面的式子满足，前面的一定就满足，把 $p$ 代入进去就是 $i-j-p>l+j$。

移项得到 $p+l<i-2j$，即 $p+l\le i-2j-1$。所以我们只需要存一个 $pre_{i}$ 表示 $p+l\le i$ 的所有 $f_{p,l}$ 的和即可。

因为 $i=p$ 时不会互相转移，所以我们每次集体更新所有的 $f_{i,j}$，然后直接 $O(n)$ 扫一遍 $pre$ 的前缀和即可。

复杂度 $O(n^2)$。

https://codeforces.com/contest/1750/submission/179942892

---

## 作者：ListenSnow (赞：3)

[原题链接](https://codeforces.com/problemset/problem/1750/F "原题链接")

## 题意

定义一个 01 串 $s$ 是好的，当且仅当 $s$ 可以通过以下操作变成全是 $1$ 的串，可以操作无数次。

选择 $i,j$ 满足 $i<j,s_i=s_j=1,2\sum_{k=i}^js_k\ge j-i+1$，然后将 $k\in[i,j]$ 的 $s_k$ 全部改为 $1$。

给定 $n$ 和 $m$，求有多少个长度为 $n$ 的 $01$ 串是好的，对 $m$ 取模。

$1 \leq n \leq 5000$。

## 思路

注意到好的 01 串两端一定均为 $1$。考虑设 $f_{i,j}$ 表示长度为 $i$ 的 01 串操作到最终状态时，右端点所在的 $1$ 连续段长度为 $j$ 的方案数。

初始时，$f_{1,1}=1$。最终的答案就是 $f_{n,n}$。

对于 $f_{i,i}$，考虑容斥，用总的方案数减去所有的不合法方案数，即：

$$f_{i,i}=2^{i-2}-\sum_{j=1}^{\left \lfloor \frac{i-1}{2} \right \rfloor } f_{i,j}$$

而对于其他状态，中间一定存在一个较长的 $0$ 连续段，于是可以枚举中间 $0$ 连续段的长度和右侧 $1$ 连续段的长度，需要注意边界条件，这里右侧的 $1$ 连续段不能和左侧的进行操作，即：

$$f_{i,j}=f_{j,j}\sum_{k=j+2}^{i-j-1} \sum_{l=1}^{k-j-1} f_{i-j-k,l}$$

其中的两个限制条件也就是 $j+k<i,j+l<k$，稍微改写一下可以得到 $l+(i-j-k)<i-2j$。那么只需要维护一个 $s_i$ 表示所有 $j+k \leq i$ 的 $f_{j,k}$ 之和即可做到 $O(n^2)$ 转移。

## code：

```
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=5010;
int n,m,f[N][N],sum1[N<<1],sum2[N<<1];
void Add(int &a,int b){a+=b;if(a>=m) a-=m;}
void Sub(int &a,int b){a-=b;if(a<0) a+=m;}
int main()
{
	scanf("%d%d",&n,&m);f[1][1]=1;int mul_2=1;sum1[2]=1;
	for(int i=2;i<=n;i++)
	{
		f[i][i]=mul_2;mul_2=mul_2*2%m;
		for(int j=1;j<=n;j++) sum2[j]=(sum2[j-1]+sum1[j])%m;
		for(int j=1;j*2<i;j++)
		{
			Add(f[i][j],1ll*f[j][j]*sum2[i-2*j-1]%m);
			Sub(f[i][i],f[i][j]);
		}
		for(int j=1;j<=i;j++) Add(sum1[i+j],f[i][j]);
	}
	printf("%d\n",f[n][n]);
	return 0;
}
```

---

## 作者：zifanwang (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/CF1750F)

记 $f_i$ 表示长度为 $i$ 的答案，发现不好直接求，考虑用 $2^{i-2}$ 减去两端点为 $1$ 且不合法的串的个数。

考虑一个不合法的串做完全部操作以后长什么样，发现不合法当且仅当对于任意两个全为 $1$ 且中间全为 $0$ 的连续段，长度和小于中间的 $0$ 的个数。

考虑让两段 $1$ 再往中间取同一长度的一段：

![](https://cdn.luogu.com.cn/upload/image_hosting/5jnzoiww.png)

然后直接 dp 计数即可，时间复杂度 $\mathcal O(n^2)$。

参考代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define mxn 5003
#define rep(i,a,b) for(int i=a;i<=b;++i)
#define rept(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int n,md;
ll f[mxn],d[mxn],dp[mxn],d1[mxn];
signed main(){
	cin>>n>>md;
	d[0]=1;
	rep(i,1,n)d[i]=d[i-1]*2%md;
	f[1]=1; 
	rep(i,2,n){
		if(!(i&1))dp[i]=f[i>>1];
		rept(j,1,i){
			if(i-j*3-1<0)break;
			dp[i]=(dp[i]+d1[i-j*3-1]*f[j])%md;
		}
		d1[i]=(d1[i-1]+dp[i])%md;
		f[i]=d[i-2];
		rept(j,1,i){
			if(i-j*2-1<0)break;
			f[i]=(f[i]-d1[i-j*2-1]*f[j])%md;
		}
	}
	cout<<(f[n]+md)%md;
	return 0;
}
```

---

## 作者：xianggl (赞：3)

题意：

你有一个 01 串，你可以执行无数次以下操作：

1、选取两个下标 $1 \leq i < j \leq n$，且 $s[i] = s[j]  = 1$。

2、若 $2 \times \sum_{k = i}^{j} s[k] \geq (i - j + 1)$，则将 $[i, j]$ 区间内所有数赋为 $1$。

求有多少个长度为 $n$ 的串满足最终可以变为一个全 $1$ 串？

题解：

对于一个长度为 $n$ 的合法串，其两端必定为 $1$。

换而言之，我们可以将它的**最终状态**看作若干 $0/1$ 段组成，$1$ 有 $x$ 段，$0$ 有 $y$ 段，且满足每一个 $0$ 段长度 $>$ 其两边 $1$ 段长度之和。

令 $f_{i, j}$ 表示最终状态下长度为 $i$，**两端为 $1$**，且最后一个 $1$ 段有 $j$ 位的方案数，显然 $f[n][n]$ 即为答案。

考虑转移，注意到，$\sum_{j \leq i} f[i][j] = 2 ^ {i - 2}$，所以可以用总数减去不合法方案数得到 $f[i][i]$，然后对于 $j \leq i$，可以枚举上一段 $0$ 和 $1$ 的长度 $k, l$，贡献为 $f[i - j - k][l] \times f[j][j]$，因为中间 $0$ 固定，只需要拼一个合法的长度为 $j$ 的段就可以了。

那么考虑限制，枚举到上一段 $0$ 的长度 $k$，假如我们能从 $f_{p, q}$ 转移过来，那么我们必然有 $k > j + q$，所以 $p < i - j - j - q$，即 $p + q \leq i - 2 \times j - 1$。

那么显然可以用前缀和优化，只需要记 $sum[i]$ 表示 $j + k \leq i$ 的 $f[j][k]$ 之和即可。

代码：

```
#include <bits/stdc++.h>
#define ri register int
#define ll long long
using namespace std;
int Mod;
inline int add(int x,int y) {
	x+=y;
	if(x>=Mod)x-=Mod;
	return x;
}
inline int sub(int x,int y) {
	x=x-y+Mod;
	if(x>=Mod)x-=Mod;
	return x;
}
void solve() {
	int n;
	scanf("%d%d",&n,&Mod);
	vector<vector<int>>f(n+1,vector<int>(n+1));
	vector<int>g(2*n+1);
	f[1][1]=g[2]=1;
	for(ri i=2,mul=1;i<=n;i++,mul=mul*2%Mod) {
		auto sum=g;
		for(ri j=1;j<=2*n;j++)sum[j]=add(sum[j],sum[j-1]);
		for(ri j=1;2*j<i;j++)f[i][j]=1ll*sum[i-2*j-1]*f[j][j]%Mod;
		f[i][i]=mul;
		for(ri j=1;2*j<i;j++)f[i][i]=sub(f[i][i],f[i][j]);
		for(ri j=1;j<=i;j++)g[i+j]=add(g[i+j],f[i][j]);
	}
	printf("%d\n",f[n][n]);
}
int main() {
	int T=1;
	while(T--)solve();
	return 0;
}

```


---

## 作者：蒟蒻君HJT (赞：2)

很好玩的 dp 题，自己想出来的话会很爽。

第一眼看这道题，每次操作选择的子串可能有多种，操作顺序也可能有多种，看起来很难直接计算合法的方案数。这时候必须冷静下来，思考一下其中的性质。

- 1. 合法串的 $s_1,s_n$ 为 $1$。这个很显然。


- 2. 我们任意一次操作选择一个子串 $[l,r]$ 时，一定可以调整左右端点保证 $s_{l-1},s_{r+1}=0$。

这是因为如果该串的边缘还有一些 $1$ 的话，我们把子串的区间往 $1$ 那边扩展一个位置，$1$ 的占比肯定更大，若原先区间合法，则新的区间也必然合法。


- 3. 设一个合法串的连续相同数字构成了 $2c+1$ 个连续段：$c+1$ 段 $1$ 和 $c$ 段 $0$（$c\geq 0$），我们每次操作一定可以只包含其中三段。采用反证法：

假如某次操作包含了 $2k+1$ 段，长度分别为 $l_1,l_2,\cdots l_{2k+1}$ 且 $k\geq 2$，则必然有 $l_1+l_3+\cdots +l_{2k+1}\geq l_2+l_4+\cdots l_{2k}$。假设其中的任意三段都不能操作，则 $l_1+l_3<l_2,l_3+l_5<l_4\cdots l_{2k-1}+l_{2k+1}<l_{2k}$。将左右两边分别求和得 $l_1+2l_3+\cdots +2l_{2k-1}+l_{2k+1}<l_2+l_4+\cdots l_{2k}$，与 $l_1+l_3+\cdots +l_{2k+1}\geq l_2+l_4+\cdots l_{2k}$ 矛盾。故命题得证。

- 4. 考虑一个非法串 $S$，其经过若干次操作后不为全 $1$ 且不能再进行任何操作，得到串 $T$，称其为最终串。则一个 $S$ 仅对应唯一一个最终串 $T$。

这是最关键的结论，但我不太会证明，可以感性理解一下？

在以下过程中，由于任何合法串的 $s_1$ 和 $s_n$ 都为 $1$，因此我们将只考虑所有满足 $s_1=s_n=1$ 的 $2^{n-2}$ 个串以便于计数。

正难则反。既然有很好的性质 $4$，那么我们不妨考虑求出不合法的串的数量，即所有最终串 $T$ 所对应的原始串的数量的总和。

有什么性质可以刻画这个最终串 $T$ 呢？设一个原始串 $S$ 有 $2c+1(c>0)$ 个连续段，长度分别为 $l_1,l_2,\cdots l_{2c+1}$，则 $l_1+l_3<l_2,l_3+l_5<l_4\cdots l_{2k-1}+l_{2k+1}<l_{2k}$ 是 $S$ 为最终串的充要条件。

- 设 $g_i$ 表示长度为 $i$ 的合法串的数量，初始值 $g_1=g_2=1$，我们需要求的是 $g_n$。

- 设 $f_{i,j,1}$ 表示长度为 $i$ 的，最后一段为 $j$ 个 $1$ 的非法串的数量；$f_{i,j,0}$ 表示长度为 $i$ 的，以若干个 $0$ 结尾的，最后一段 $0$ 的数量与最后一段 $1$ 的数量差值为 $j$ 的非法串的数量。注意状态的定义，必须满足 $j>0$。

根据状态的定义，有 $g_i+\sum_{j=1}^{i}f_{i,j,1}=2^{i-2}$（再强调一次，我们始终只考虑所有满足 $s_1=s_n=1$ 的串）。于是当我们算完所有 $f_{i,,1}$ 时，即可立刻得出 $g_i$。

考虑对 $f$ 的两种状态分别转移：

枚举之前的最后一段 $0$ 的数量减去最后一段 $1$ 的数量 $x$：

$$f_{i,j,1}=g_j\sum_{x=j+1}^{i}f_{i-j,x,0}$$

枚举最后加入的这一段的 $0$ 的数量 $x$，则之前的最后一段 $1$ 的数量为 $j-x$：

$$f_{i,j,0}=\sum_{x=j+1}^{i}f_{i-x,x-j,1}$$

第一种转移可以用后缀和优化；

第二种转移我们记 $p_{i}=\sum_{j=1}^{i-1}f_{j,i-j,1}$ 也可轻松完成。

列完转移方程后会发现在第二种转移中可能会遇到之前是整个一段全 $1$ 的情况，需要特判，这不好。所以我们不妨在计算完 $g_i$ 后，将 $i$ 个 $1$ 所构成的串也假设为一个最终串，即令 $f_{i,i,1}=g_i$，就不需要特判了。

时空复杂度均为 $O(n^2)$，注意初始化。

关键 code：

```cpp
int g[5005], f[5005][5005][2], n;
int p[10005], q[5005][5005];
void solve(){
	scanf("%d%d", &n, &mod);
	g[1] = g[2] = 1;
	f[1][1][1] = 1;
	f[2][2][1] = 1;
	p[2] = p[4] = 1;
	for(int i = 3; i <= n; ++i){
		for(int j = 1; j <= i - 2; ++j)
			f[i][j][0] = p[i - j];
		for(int j = 1; j <= i - 2; ++j)
			f[i][j][1] = mul(g[j], q[i - j][j + 1]);
		for(int j = 1; j <= i - 2; ++j)
			p[i + j] = add(p[i + j], f[i][j][1]);
		q[i][n + 1] = 0;
		for(int j = n; j >= 1; --j)
			q[i][j] = add(q[i][j + 1], f[i][j][0]);
		int tmp = 0;
		for(int j = 1; j <= i - 2; ++j)
			tmp = add(tmp, f[i][j][1]);
		g[i] = minus(Qpow(2, i - 2), tmp);
		f[i][i][1] = g[i];
		p[i + i] = add(p[i + i], f[i][i][1]);
	}
	printf("%d\n", g[n]);
	return ;
}
```



---

## 作者：masonpop (赞：1)

很厉害的 DP 啊！感觉难点在于状态设计。

首先注意到我们的合并方式一定是这样的：每次选择相邻两段极长的 $1$，然后合并。注意到如果相邻的两端无法合并，那么跨过它们的也一定无法直接合并。

也就是说，如果一个序列不合法，那么当不可合并时序列一定长这样：序列能被分为 $2k+1$ 段，其中有 $k+1$ 段能被变为全 $1$，中间穿插排布着 $k$ 段 $0$，且设一段 $0$ 长度为 $b$，两端的 $1$ 长度为 $a,c$，则必有 $b>a+c$。

那么考虑如何刻画这样的序列。现在就很容易想到状态 $f_{i,j}$ 表示前 $i$ 个位置中，最后一段连续 $1$ 长度为 $j$ 的方案数。满足条件的序列即为 $f_{i,i}$。

对于 $i=j$ 的情况，我们可以容斥求出来。首先总序列数为除掉两边的 $1$ 外中间随便选，即 $2^{i-2}$。然后再去除中间的，即

$f_{i,i}=2^{i-2}-\sum\limits_{j=1}^{i-1}f_{i,j}$

然后考虑 $j<i$ 的转移。直接枚举上一段 $0$ 和上上段 $1$ 的长度 $p,q$。则有

$f_{i,j}=f_{j,j}\sum\limits_{p,q}f_{i-j-p,q}[p+q+j\le i][p\ge j+q+1]$

首先第一个限制可以去掉，因为 $f_{i-j-p,q}$ 存在的前提就是 $p+q+j\le i$。而后面一个条件可以变成 $p-q\ge j+1$，化为两维和的形式就是 $(i-j-p)+q\le i-2j-1$。

也就是说，只要维护一个数组 $g_{k}$ 表示两维和 $\le k$ 的 $f$ 之和，就能 $O(1)$ 转移。

总复杂度成功变为 $O(n^2)$。[代码](https://www.luogu.com.cn/paste/cdxx6t6w)。

---

## 作者：樱雪喵 (赞：1)


正着不会做，反过来找序列不合法的条件：
- 两端不都是 $1$
- 操作到最后，存在某段连续 $0$ 的长度大于两边 $1$ 的长度之和

设 $f_{i,j}$ 表示长度为 $i$ 的串，钦定开头结尾都是 $1$，操作到不能操作，结尾连续 $1$ 的个数。  
那么 $f_{i,i}$ 是合法情况，由不合法的情况容斥得到：$f_{i,i}=2^{i-2} -\sum\limits_{j=1}^{2j<i} f_{i,j}$。  
求不合法的 $f_{i,j}$，那么序列的最后一段在全部操作后一定是一段连续的 $0$ 后接一段连续的 $1$。枚举 $0$ 的长度为 $k$，$1$ 的长度为 $l$。  
转移有 
$$
\begin{aligned}
f_{i,j}&=f_{j,j}\times (\sum_{j+k<i}\sum_{j+l<k} f_{i-j-k,l})\\
&=f_{j,j}\times \sum_{(i-j-k)+l< i-2j} f_{i-j-k,l}
\end{aligned}
$$
使用前缀和优化，设 $s_k=\sum_{i+j\le k} f_{i,j}$。转移变为 $O(1)$，时间复杂度 $O(n^2)$。

---

## 作者：KaKa_fairy (赞：1)

称“最终态”为不能再操作的、两端为 1 的 01 序列。

找最终态的充要条件：两端为 1 且每一段连续的 0 的个数大于两边连续 1 的个数和。（$\Delta$）

设 $g_n$ 表示长度为 $n$ 全为 1 的最终态对应的初始方案数，即我们最终的答案。

设一个最终态有 $k$ 段连续的 1，且长度分别为 $c_1,\dots,c_k$，则这个最终态对应的初始方案数为
$$
\prod_{i=1}^kg_{c_i}
$$
若 $k=1$，则这个式子恒等，所以我们无法通过知道 $g_1,\dots,g_{n-1}$ 用这个式子求出 $g_n$。

那咋办捏，我们发现长度为 $n$，两边为 1 的共 $2^{n-2}$ 个初始 01 序列，每一个都有最终态（可能是废话）。

所以我们只要求出长度为 $n$ 两边为 1 的 01 序列有多少最终态不为全 1，就得到了多少为全 1。

然而除了全 1 最终态有 $2^{n-2}-1$ 个，有点多。

考虑用 $\Delta$ 式来 DP。

设 $f_{n,m}$ 表示 长度为 $n$、左端必须为 1、右端极长连续 1 有 $m(\in[1,n])$ 个的 01 序列 为最终态的初始态方案数之和。

所以其实有 $g_n=f_{n,n}$。

有一个 $O(n^4)$ 的转移（定义域外不妨设为 $0$）
$$
\begin{cases}
f_{n,m}=1 & n=m=1
\\
f_{n,m}=g_m\sum_{i=1}^{n-m-1}\sum_{j=1}^{n-m-i}[i>j+m]f_{n-m-i,j}&n>1,1\le m< n
\\
f_{n,n}=g_n=2^{n-2}-\sum_{i=1}^{n-1}f_{n,i} & n>1
\end{cases}
$$
$i$ 是枚举上一段 0 的长度，$j$ 是上一段 1 的长度。

由于定义域外的都是 $0$ 了，中间那式子 $i,j$ 的上下界其实就无意义了，改写
$$
\begin{aligned}
f_{n,m}&=g_m\sum_{i>j+m}f_{n-m-i,j}
\\&=g_m\sum_{i+j\le n-2m-1}f_{i,j}
\end{aligned}
$$
发现后面求和其实是变形的二维前缀和形式。

前缀和优化 DP 就做完了，$O(n^2)$。

---

## 作者：Luzhuoyuan (赞：0)

一种不容斥硬做的做法。

首先我们容易证明，一个合法的串一定可以通过若干次合并两段相邻的 $1$ 来变成全 $1$ 串。因为若某次合并了多段 $1$，假设合并的段形如 $a_1,b_1,a_2,b_2,\dots,a_n$ 的若干段（$a$ 为 $1$ 段的长度，$b$ 为 $0$ 段的长度），假设其中任意两个相邻的 $1$ 段都无法合并，则有 $a_1-b_1+a_2,a_2+b_2+a_3,\dots<0$，则有 $0>(a_1-b_1+a_2)+(a_2-b_2+a_3)+\dots>a_1-b_1+a_2-b_2+\dots+a_n$，与“这些段可以直接合并”矛盾。同时一次合并不会使原来能合并的段合并不了，故可以每次只合并两个相邻的段。

接着考虑合并的过程。每个合法串可能有多种合并方法，我们钦定每次只能合并最靠左的可合并的相邻段，这样就不会算重了。考虑每个合法串的最后一次合并，一定是一个全 $1$ 的前缀和一个全 $1$ 的后缀合并起来。考虑对这个东西做 DP。

设 $f_{i,j}$ 表示长度为 $i$，且最后一次合并前前缀 $1$ 的数量为 $j$ 的合法串数量（注意这里没有考虑初始时就是全 $1$ 串的情况）。我们枚举全 $1$ 后缀的长度 $k$，可以发现 $k\in[\max(1,\lceil\frac i 2\rceil-j),i-j-1]$，设 $L=\max(1,\lceil\frac i 2\rceil-j),R=i-j-1$。

先考虑后缀初始是全 $1$ 的情况，可以发现由于前缀总是可以合并，所以总是合法的。

若后缀初始不全 $1$，考虑前缀全合并完后，在合并后缀时不能存在任何一个时刻使得前缀能和后缀的一段全 $1$ 前缀合并，否则顺序就不对了。考虑后缀的全 $1$ 前缀长度在后缀合并完之前何时取到最大（即最有可能被合并），发现正是后缀最后一次合并前。因此我再枚举后缀的“最后一次合并前前缀 $1$ 的数量”$l$，保证 $j,l$ 不能合并即可。于是可以得到转移：

$$f_{i,j}=(1+\sum\limits_{l=1}^{j-2}f_{j,l})\cdot(R-L+1+\sum\limits_{k=L}^{R}\sum\limits_{l=1}^{i-2j-k-1}f_{k,l})$$

这样就是 $O(n^4)$ 的。然后可以前缀和优化，处理 $g_{i,j}=\sum\limits_{k=1}^{i}\sum\limits_{j=1}^{i-k}f_{k,l},s_i=1+\sum\limits_{j=1}^{i-2}f_{i,l}$ 即可 $O(1)$ 转移，最后答案即为 $s_n$。

复杂度 $O(n^2)$。

### 代码

```cpp
#include<bits/stdc++.h>
#define pb push_back
#define SZ(x) (int)(x).size()
using namespace std;
const int N=5005;

// Modint ...

int n,mod;
MI f[N][N],g[N][N];
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>mod;MI::setmod(mod);
	f[1][0]=f[2][0]=1;
	// f[i][0] <- s[i]
	for(int i=3;i<=n;i++){
		for(int j=1;j<=n;j++)g[i][j]=g[i-1][j];
		for(int j=1;j<i-1;j++){
			int L=max(1,(i+1)/2-j),R=i-j-1;
			f[i][j]=R-L+1;
			if(i-j*2-1>0)f[i][j]+=
				g[R][i-j*2-1]-g[L-1][i-j*2-1];
			f[i][j]*=f[j][0];
			f[i][j]+=f[i][j-1];
		}
		for(int j=i-1;j<=n;j++)f[i][j]=f[i][j-1];
		for(int j=1;j+i<=n;j++)g[i][j+i]+=f[i][j];
		f[i][0]=f[i][i-2]+1;
	}
	cout<<f[n][0]<<'\n';
	return 0;
}
```

（逃

---

## 作者：tribool4_in (赞：0)

首先考虑何时无法操作，显然是当 0 和 1 成段出现，且连续两段 1 的长度和小于中间的全 0 段。这个结构比较好 dp，于是考虑由此求出“不好”的串的个数。

考虑如上的结构，对全 1 段进行 dp，设 $dp_{i,j}$ 表示长度为 $i$ 的串，最终会变成末尾全 1 段长度为 $j$ 的串有多少个。转移考虑枚举上一个全 1 段的位置，然后边界判合法。

发现处理 $dp_{i,j}$ 时需要得出“长度为 $j$ 的合法串个数”，发现这就是原问题的子问题，为 $f_j=2^{j-2}-\sum_{j<i} dp_{i,j}$。

于是转移变成了 $\displaystyle dp_{i,j}=f_j\sum_{a=1}^{(i-2j-2)}\sum_{b=1}^{(i-2j-a-1)}dp_{a,b}$，边界啥的手玩一下即可。然后发现会有 $a=b$，显然有 $dp_{i,i}=f_i$。

直接转移是 $O(n^4)$ 的，考虑优化掉转移中的和式。容易发现和式形如 $\displaystyle\sum_{i=1}^n\sum_{j=1}^{n-i+1}dp_{i,j}$，形如一个倒三角。于是前缀和优化，令 $\displaystyle s_{i,j}=\sum_{k=1}^i\sum_{l=1}^{j-k+1}dp_{k,l}$，每次做完一个新的 $i$ 就先对 $dp_i$ 做遍前缀和然后处理 $s$ 即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 5e3 + 10;
int n, mod;
int dp[N][N], s[N][N], tmp[N], pw2[N];
#define chkmod(x) (((x) >= mod) && ((x) -= mod))
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n >> mod;
    for (int i = pw2[0] = 1; i <= n; i++) pw2[i] = pw2[i - 1] * 2, chkmod(pw2[i]);
    dp[1][1] = 1;
    for (int j = 1; j <= n; j++) s[1][j] = s[1][j - 1] + dp[1][j], chkmod(s[1][j]);
    for (int i = 2; i <= n; i++) {
        for (int j = 1; j < i; j++) {
            if (i - 2 * j - 2 < 1) continue;
            int sum = s[i - 2 * j - 2][i - 2 * j - 2];
            // int s = 0;
            // for (int k = 1; k <= i - 2 * j - 2; k++)
            //     for (int l = 1; l <= i - 2 * j - k - 1; l++) s += dp[k][l], chkmod(s);
            dp[i][j] += 1ll * dp[j][j] * sum % mod;
            chkmod(dp[i][j]);
        }
        dp[i][i] = pw2[i - 2];
        for (int j = 1; j < i; j++) (dp[i][i] += mod - dp[i][j]) %= mod;
        for (int j = 1; j <= n; j++) tmp[j] = tmp[j - 1] + dp[i][j], chkmod(tmp[j]);
        for (int j = i; j <= n; j++) s[i][j] = s[i - 1][j] + tmp[j - i + 1], chkmod(s[i][j]);
    }
    cout << dp[n][n] << '\n';
    return 0;
}
```

---

## 作者：huazai676 (赞：0)

[题目](https://www.luogu.com.cn/problem/CF1750F)

随便找一个01串不停的进行操作，发现最终一定会变成类似 $11 \ 00000 \ 1 \ 000000 \ 111 \ 0......$ 这之中1的连续段内的方案数已经成为整个问题的子问题，可以递归的解决，所以只要能对不同1连续段方案的排布计数再容斥出答案。

一个01串不能再进行操作（下称为合法），当且仅当对于任意相邻大小为 $a$ 和 $b$ 的两个1连续段，它们间的0连续段长度 $c>a+b$，考虑 dp，$f_{i,j}$ 表示长为 $i$ 且最后1的连续段长为 $j$ 的合法方案数（钦定首尾为1）。

转移则为：

$f_{i,j}=f_{j,j} \times \sum \limits_{y+j<i-j-x}f_{x,y}$，可以前缀和优化

$f_{i,i}=2^{i-2}-\sum \limits_j f_{i,j}$，$i-2$ 是由于钦定了首尾

$f_{1,1}=1$

[代码](https://codeforces.com/contest/1750/submission/231536951)

---

