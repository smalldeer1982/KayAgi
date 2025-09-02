# Make Them Equal

## 题目描述

#### 【题目大意】

你有一个长度为 $n$，初始全为 $1$ 的数组 $a$，和两个长度为 $n$ 的数组 $b,c$。

你可以**最多**进行 $k$ 次如下的操作：选择两个**正整数** $i,x$，使 $a_{i}$ 变成 $ \left ( a_{i}+\left \lfloor \dfrac{a_{i}}{x} \right \rfloor \right )$。

最后，如果 $a_{i}=b_{i}$，你将会获得 $c_{i}$ 的收益。

最大化总收益。

## 说明/提示

- $1 \leq t \leq 100,1 \leq n \leq 1000, 1 \leq k \leq 1 \times 10^{6}$；
- $1 \leq b_{i} \leq 1000,1 \leq c_{i} \leq 1 \times 10^{6}$；
- $n$ 的总和不大于 $1000$。

Translated by HPXXZYY.

## 样例 #1

### 输入

```
4
4 4
1 7 5 2
2 6 5 2
3 0
3 5 2
5 4 7
5 9
5 2 5 6 3
5 9 1 9 7
6 14
11 4 6 2 8 16
43 45 9 41 15 38```

### 输出

```
9
0
30
167```

# 题解

## 作者：CSP_Sept (赞：15)

### 视频讲解

![](bilibili:BV1pq4y1h72x)

### 大意

数列 $a_n$ 初始均为 $1$，每次可以选择 $i,x(x>0)$，进行操作 $a_i:a_i+\left\lfloor\frac{a_i}x\right\rfloor$。

可以进行最多 $k$ 次操作，操作后若 $a_i=b_i$ 可以得到得分 $c_i$，最大化得分。

### 解法

考虑预处理出对于所有 $x$，$1\to x$ 所需的最小操作数 $f_x$。

直接暴力处理，复杂度 $O(n^2)$。

接下来我们转化题意，得到：

>你有 $k$ 个金币，第 $i$ 个货物需要 $f_i$ 个金币，价值为 $c_i$，求最大价值。

这显然是一个简单背包问题，我们直接 dp 即可。

但注意到此时时间复杂度为 $O(nk)$，不能通过。

我们记录 $m=\max\{f_i\}$，若 $k\ge m\cdot n$，则我们可以直接得到所有 $c_i$，直接输出即可。

当然也可以判断是否有 $k\ge\sum f_{b_i}$。

### 核心代码

```cpp
// 预处理 f(i)
#define M 1000

void init(){
	for(int i = 1 ; i <= M ; i++)
		f[i] = INF;
	f[1] = 0;
	for(int i = 1 ; i <= M ; i++)
		for(int j = 1 ; j <= i ; j++)
			f[i + i / j] = min(f[i + i / j], f[i] + 1),
			mx = max(mx, f[i + i / j]);
}

// 直接 dp
memset(dp, 0, sizeof(dp));
for(int i = 1 ; i <= n ; i++)
	for(int j = k ; j >= f[b[i]] ; j--)
		dp[j] = max(dp[j - f[b[i]]] + c[i], dp[j]);
printf("%lld\n", dp[k]);
```

[完整版（$\textit{144834977}$）](https://codeforces.com/contest/1633/submission/144834977)

---

## 作者：include_BM (赞：5)

对于每个 $a_i$ 的操作都是独立的，所以如果能算出 $1\rightarrow b_i$ 最小操作次数，问题转化为背包问题。

设 $s[i]$ 表示 $1\rightarrow i$ 最少操作次数，那么只需要枚举 $i$，若 $\exists x,i+\left\lfloor\frac{i}{x}\right\rfloor=j$，则可以由 $s[i]$ 转移给 $s[j]$，即 $s[j]=min\left(s[j],s[i]+1\right)$，边界条件 $s[1]=0$。

可以发现当 $i\le 1000$ 时 $\max s[i]=12$，即最多需要 $12\times n$ 次可以将全部 $a_i\rightarrow b_i$，故 $k>12\times n$ 的部分并没有用。

计算出每个 $b_i$ 最小操作次数 $s[b_i]$ 后跑背包即可。

代码：

```cpp
const int N=1e3+10;
ll n,k,b[N],c[N],s[N],f[N*12];
signed main(){
    for(int i=2;i<N;++i) s[i]=2e9;
    for(int i=1;i<N;++i)
        for(int j=1;j<=i;++j) s[i+i/j]=min(s[i+i/j],s[i]+1);
    for(int T=read();T;--T){
        n=read(),k=read();
        for(int i=1;i<=n;++i) b[i]=read();
        for(int i=1;i<=n;++i) c[i]=read();
        for(int i=0;i<=n*12;++i) f[i]=0;
        for(int i=1;i<=n;++i)
            for(int j=n*12;j>=s[b[i]];--j) f[j]=max(f[j],f[j-s[b[i]]]+c[i]);
        printf("%lld\n",f[min(k,n*12)]);
    }
    return 0;
}
```

---

## 作者：BigJoker (赞：5)

# 前言

这个题确实挺有意思，dp 好题。

# Solution

很显然，每个数字操作的次数是花费，而经过操作后得到的就是价值，不难想到 $01$ 背包问题。

$01$ 背包问题的复杂度是背包容量与物品数量的乘积。

但是 $n\times k$ 是个极大的数，不要慌，先继续看着。

考虑求一下花费，很自然的想到了 DP。

$f_{i+\frac{i}{j}}\gets \min\{f_i+1\}$

复杂度是 $10^6$。

没有问题。

其实这个值是有个 $\log$ 级别的趋势，因为每次最多涨一倍，我们可以猜测一下这个结论，大致操作在 $10$ 次左右。

当然这只是猜测，当我们跑一遍，把这个最大值求出来。

发现是才 $12$，所以可以优化背包容量，这样就行了。

最后跑一遍背包就行了。

# Code

```cpp
#include<bits/stdc++.h>
#define mem(a,x) memset(a,x,sizeof(a))
#define inf 0x3f3f3f3f
using namespace std;
int t,n,k;
int b[1005],c[1005];
int dp1[1005],dp[100005];
void init(){
	mem(dp1,inf);
	dp1[1]=0;
	for(int i=1;i<=1000;i++){
		for(int j=1;j<=1000;j++){
			int u=i*1.0/j;
			if(u+i<=1000) dp1[u+i]=min(dp1[u+i],dp1[i]+1);
		}
	}
}
int main(){
	init();
	scanf("%d",&t);
	while(t--){
		scanf("%d %d",&n,&k);
		k=min(k,12*n);
		mem(dp,0);
		for(int i=1;i<=n;i++) scanf("%d",&b[i]),b[i]=dp1[b[i]];
		for(int i=1;i<=n;i++) scanf("%d",&c[i]);
		for(int i=1;i<=n;i++){
			for(int j=k;j>=b[i];j--) dp[j]=max(dp[j],dp[j-b[i]]+c[i]); 
		}
		printf("%d\n",dp[k]);
	}
	return 0; 
} 
```

---

## 作者：听取MLE声一片 (赞：3)

修改：`20` 后面去了一个空格。

这道题有很多坑点，赛时把我卡到了最后 5 分钟才过。

我们发现 $b_i$ 的范围只有 `1000`，所以我们就可以预处理出从 `1` 变换到 $b_i$ 最少步数。这可以用类似 dp 的方法解决。

```
for(int i=2;i<N;i++)
		g[i]=1e18;
	for(int i=1;i<N;i++)
		for(int j=1;j<=i;j++)
			g[(int)(i+i/j)]=min(g[(int)(i+i/j)],g[i]+1);
```

注意此处的 $g_1=0$。

预处理完之后，我们发现这题可以进行 01 背包，但是 $m\times n=10^9$ 会在第 `12` 个点上 TLE。

通过输出刚才预处理的表，我们发现最大值都不超过 `20`（这里为了保险只是取了一个非常大的值），而物品数最多只有 $n$ 个，所以如果 $m\geq n\times 20$，就可以把所有物品全部打包带走，大量的剩余都是浪费的。

下面是~~简短~~的代码。

```
#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<algorithm>
#define int long long
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int N=2e3+10;
const int M=2e6+10;
int T,n,m,a[N],b[N],f[2][M],g[N*2];
signed main()
{
	T=read();
	for(int i=2;i<N;i++)
		g[i]=1e18;
	for(int i=1;i<N;i++)
		for(int j=1;j<=i;j++)
			g[(int)(i+i/j)]=min(g[(int)(i+i/j)],g[i]+1);
	while(T--){
		n=read(),m=read();
		for(int i=1;i<=n;i++)
			a[i]=g[read()];
		for(int i=1;i<=n;i++)
		m=min(20*n,m);
		for(int i=0;i<=m;i++)
			f[0][i]=f[1][i]=0;
		for(int i=1;i<=n;i++)
			for(int j=0;j<=m;j++){
				if(j>=a[i])
					f[i%2][j]=max(f[(i+1)%2][j],f[(i+1)%2][j-a[i]]+b[i]);
      			else f[i%2][j]=f[(i+1)%2][j];
			}
		cout<<f[n%2][m]<<endl;
	}
	return 0;
}


```

---

## 作者：Eason_AC (赞：2)

## Content
给定一个长度为 $n$ 的数组 $a$，一开始所有元素均为 $1$。你可以执行最多 $k$ 次操作，每次操作你可以选择数组 $a$ 中的一个元素 $a_i$ 和一个正整数 $x$，并将 $a_i$ 替换为 $a_i+\lfloor\frac{a_i}{x}\rfloor$。对于每一个位置 $i$，如果你能够通过若干次操作使得 $a_i=b_i$，那么你将获得 $c_i$ 枚硬币。求你最多可以获得多少枚硬币。

**数据范围：$t$ 组数据，$1\leqslant t\leqslant 100$，$1\leqslant n,\sum n,b_i\leqslant 10^3$，$0\leqslant k\leqslant 10^6$，$1\leqslant c_i\leqslant 10^6$。**
## Solution
DP 简单题。
 
不难发现，从 $1$ 变到 $i$ 需要的操作次数是固定的，因此我们先令 $f_i$ 表示从 $1$ 到 $i$ 需要的操作次数，转移的时候我们再枚举 $j$，不难得到转移方程为 $f_{i+\lfloor\frac ij\rfloor}\leftarrow \min\{f_{i+\lfloor\frac ij\rfloor},f_i+1\}$，由于 $\lfloor\frac ij\rfloor$ 在 $i<j$ 的情况下始终为 $0$，因此我们的 $j$ 只需要从 $1$ 枚举到 $i$ 即可。

然后我们发现，在 $[1,1000]$ 的范围内，$\max f_i$ 的值只有 $12$，因此最多只需要 $12\times 1000=12000$ 次操作就能够将所有的 $a_i$ 变为 $b_i$。因此我们加一个特判：当 $k>12000$ 时，答案就是 $\sum c_i$。否则，看到每件物品的花费和价值，想到什么？没错，01 背包。因此，我们直接令 $dp_j$ 表示在最多花费 $j$ 次操作的前提下最多能够获得的硬币个数，然后套用 01 背包的式子转移，枚举每一个元素 $i$，则有 $dp_j\leftarrow\max\{dp_j,dp_{j-f_{b_i}}+c_i\}$。答案即为 $\max\limits_{0\leqslant i\leqslant k}dp_i$。
## Code
```cpp
namespace Solution {
	const int N = 12007;
	int n, k, b[N], c[N], f[N], dp[N];
	
	iv Main() {
		F(int, i, 1, 2000) f[i] = iinf; f[1] = 0;
		F(int, i, 1, 1000) F(int, j, 1, i) f[i + i / j] = min(f[i + i / j], f[i] + 1);
		int mx = 0;
		F(int, i, 1, 1000) mx = max(mx, f[i]);
		MT {
			read(n, k);
			F(int, i, 1, n) read(b[i]);
			F(int, i, 1, n) read(c[i]);
			if(k > 12000) {
				int sum = 0;
				F(int, i, 1, n) sum += c[i];
				println(sum); continue;
			}
			F(int, i, 0, k) dp[i] = 0;
			F(int, i, 1, n) R(int, j, k, f[b[i]]) dp[j] = max(dp[j], dp[j - f[b[i]]] + c[i]);
			int ans = 0;
			F(int, i, 0, k) ans = max(ans, dp[i]);
			println(ans);
		}
		return;
	}
}
```

---

## 作者：EnofTaiPeople (赞：2)

很容易发现，从 $a_i$ 到 $b_i$ 所需变化次数只与 $b_i$ 有关，而 $1\le b_i\le10^3$，故我们可以进行一次线性动态规划。在此之后，可以将原题转换成一个 $01$ 背包问题，每次从上往下循环转移即可，时间复杂度 $O(n^2+nk)$，跑不满，可以通过以下是考场 AC 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e6+6;
int b[N],c[N],T,n,dp[N],g[N];
int main(){
	ios::sync_with_stdio(false);cin>>T;int i,j,k,w;
	for(i=2;i<=1000;++i)dp[i]=INT_MAX;
	for(i=1;i<=1000;++i)
		for(j=i,k=0;j;--j)
			if(i/j>k){
				k=i/j;if(dp[i+k]>dp[i]+1)dp[i+k]=dp[i]+1;
			}
	while(T--){
		for(i=1,cin>>n>>k;i<=n;++i)cin>>b[i],b[i]=dp[b[i]];
		for(i=0;i<=k;++i)g[i]=0;b[n+1]=0; 
		for(w=min(b[i=1],k);i<=n;w=min(w+b[++i],k)){
			for(j=w,cin>>c[i];j>=b[i];--j)
				if(g[j-b[i]]+c[i]>g[j])g[j]=g[j-b[i]]+c[i];
		}
		for(i=1;i<=w;++i)if(g[i]>g[0])g[0]=g[i];
		printf("%d\n",g[0]);
	}
	return 0;
} 
```

---

## 作者：feicheng (赞：2)

## Description

给定长度为 $n$ 的序列 $b,c$ 和一个初值均为 $1$ 的序列 $a$，你可以进行不超过 $k$ 次操作，每次可以选择一个下标 $i(1\le i\le n)$ 和一个正整数 $x$，给 $a_i$ 加上 $\left\lfloor\dfrac{a_i}{x}\right\rfloor$，在进行 $k$ 次操作之后，你的收益为 

$$
\sum_{i=1}^nc_i[a_i=b_i]
$$

你需要最大化这个收益，并求出最大值。

多测。

$1\le n,\sum n\le 10^3$，$1\le b_i\le 10^3$，$1\le c_i\le 10^6$，$0\le k\le 10^6$。

## Solution

发现每个数的操作是独立的，所以我们分别考虑贡献。

如果我们能算出得到某个数所需要的最小操作次数，那么这个题很显然转化为了一个 $01$ 背包问题。

对于一个数 $x$，可以对所有的 $1\le i\le x$，转移到 $x+\left\lfloor\dfrac{x}{i}\right\rfloor$，所以只需要对所有的转移取最小值即可。

这个的时间复杂度是 $\mathcal O(b_i^2)$ 的，可以提前进行预处理。

跑 $01$ 背包的复杂度是 $\mathcal O(nk)$ 的，虽然看起来很大， 但是仍然可以过。

事实上，在值域内的最大花费为 $12$ 次，也就是说最多 $12n$ 次就可以将所有数全部变为目标数。

所以将 $k$ 和 $12n$ 取 $\min$ 作为新的 $k$ 就可以取得一个很大的优化。

最终的时间复杂度为 $\mathcal O(n\cdot\min\{12n,k\})$。

## Code

```cpp
 
constexpr int N = 1'005;
constexpr int V = 1'000'005;
constexpr int inf = 0x3f3f3f3f;
 
int n, k;
int b[N], c[N], val[N], f[V];
 
inline void init() {
  std::fill(val + 1, val + 1001, inf);
  val[1] = 0;
  for (int i = 1; i <= 1000; ++i) {
    for (int j = 1; j <= i; ++j) {
      val[i + (i / j)] = std::min(val[i + (i / j)], val[i] + 1);
    }
  }
}
 
inline void solve() {
  in >> n >> k;
  k = std::min(k, 12 * n);
  for (int i = 1; i <= n; ++i) {
    in >> b[i];
    b[i] = val[b[i]];
  }
  for (int i = 1; i <= n; ++i) {
    in >> c[i];
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = k; j >= b[i]; --j) {
      f[j] = std::max(f[j - b[i]] + c[i], f[j]);
    }
  } 
  out << f[k] << '\n';
  std::fill(f, f + 1 + k, 0);
}
```

---

## 作者：PLDIS (赞：1)

我们考虑对于每一个 $b_i$，都算出 $1$ 到 $b_i$ 需要的**最小**步数。显然，这可以用 BFS 做。又因 $1 \leq b_i \leq 1000$，我们可以**将步数预处理出来**，或者可以记忆化搜索。

容易得出，对于每一个元素，**只有将它通过最小步数变成 $b_i$ 或者将它原封不动**两种选择。

又知道步数不能小于 $k$，所以这是一个 01 背包，步数就是体积，得到的金币数量就是价值。

时间复杂度 $O(nk)$，面对毒瘤数据，显然 TLE。

实验表明，从 $1$ 到 $1000$ 的任意的数，**步数一律不会超过 $12$**。于是，即使我们选中所有的数，即我们将所有数都从 $1$ 移动到 $b_i$，最多只需要 $12n$ 步就行了。这样，让 $k$ 变成 $k$ 和步数总和的最小值，就可以了。

时间复杂度 $O(n\times\min(12n, k))$，就可以过了。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int dp[1000001], mem[1000001];
// BFS
int tb(int b) {
    if (mem[b] != 0x3f3f3f3f) {
        return mem[b];
    }

    int vis[1001] = {0};

    for (int i = 0; i <= b; i++) {
        vis[i] = 0;
    }

    queue<pair<int, int>> q;
    q.push(make_pair(1, 0));

    while (!q.empty()) {
        int x = q.front().first, y = q.front().second;
        q.pop();

        if (x == b) {
            return mem[b] = y;
        }

        for (int i = 1; i <= x; i++) {
            if (x + (x / i) > b || vis[x + (x / i)]) {
                continue;
            }

            vis[x + (x / i)] = true;
            q.push(make_pair(x + (x / i), y + 1));
        }
    }

    return mem[b] = -1;
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    for (int i = 0; i <= 1000; i++) {
        mem[i] = 0x3f3f3f3f;
    }

    int t;
    cin >> t;

    while (t--) {
        int n, v;
        cin >> n >> v;

        for (int i = 0; i <= v; i++) {
            dp[i] = 0;
        }

        int c[n], w[n];

        for (int i = 0; i < n; i++) {
            cin >> w[i];
            w[i] = tb(w[i]);
        }

        int sum = 0;

        for (int i = 0; i < n; i++) {
            cin >> c[i];

            if (w[i] == -1) {
                w[i] = 100000000, c[i] = 0;
            } else {
                sum += w[i];
            }
        }

        v = min(sum, v); // sum 最多为 12*n

        // 背包
        for (int i = 0; i < n; i++) {
            for (int j = v; j >= w[i]; j--) {
                dp[j] = max(dp[j], dp[j - w[i]] + c[i] + 1 - 1);
            }
        }

        int ans = 0;

        for (int i = 0; i <= v; i++) {
            ans = max(ans, dp[i]);
        }

        cout << ans << endl;
    }

    return 0;
}
```

---

## 作者：Cocoly1990 (赞：0)

发现题目很像 01 背包，思考如何求出对于每个 $a_i$，使其变成 $b_i$ 的最小花费，我们不妨记为 $f_i$.

容易有状态转移方程
$$f_{i+\lfloor \frac{i}{j}\rfloor}\leftarrow \min\{f_{i+\lfloor \frac{i}{j}\rfloor},f_i+1\}$$

事实上，本题可以直接 $\mathcal{O}\left(n^2\right)$ 转移，但笔者使用了数论分块，加速转移，转移复杂度 $\mathcal{O}\left(n\sqrt n\right)$.

容易发现对于 $\lfloor \frac{i}{j}\rfloor$，在 $i$ 固定不变时，他的取值是连续的，具体的讲，每一段起始未知如果是 $l$，那么他的结束位置是 $\lfloor \frac{i}{\lfloor \frac{i}{l}\rfloor}\rfloor$.

![HMVN5R.png](https://s4.ax1x.com/2022/02/07/HMVN5R.png)

考虑背包部分，一般的背包复杂度是 $\mathcal{O}\left(nk\right)$，因为 CF 神机的特殊性，这种做法也可以通过本题。

但把上述的 $f$ 打表输出之后会发现，对于 $a_i=1,b_i=1000$，即极限数据，$f_i=12$，也就是对于任意一个 $i$，最多只需要 $12$ 次操作，而总共也就最多只需要 $12\times n$ 次操作，所以，$k$ 的范围降到了 $12\times n$，直接 01 背包 处理即可，总复杂度 $\mathcal{O}\left(n\sqrt n+12\times n^2\right)$.

---

## 作者：Arctic_1010 (赞：0)

场上一眼看出做法，但是由于不会算操作数而导致悲剧。我太菜了。

### 题目翻译

你有一个初始值全为 $1$ 的长为 $n$ 的数组 $a$，你可以执行最多 $k$ 次操作，每次操作可以让 $a_i$变为 $a_i+\lfloor \dfrac{a_i}{x}\rfloor$，其中 $x$ 为你任意选择的**正**整数。

当你做完你想做的所有操作后，你将会得到 $\sum_{i=1}^{n} [a_i=b_i]\times c_i$ 的金币奖励。

你想让你得到的金币数量最大。

多组数据，$\sum n\leq 10^3$，$1\leq b_i\leq 10^3$，$1\leq k,c_i\leq 10^6$。

### 思路

首先可以 dp 出来最少用多少次操作来让 $1$ 变成其他数。

对于每一个 $b_i$，把最少的操作次数设为每个物品的体积，把 $c_i$ 设为物品价值。

直接做非满包 01 背包即可。

时间复杂度 $O(n^2 +k\times \sum n)$。~~竟然可以过，最慢的点 1.64s。~~ 可见 CF 的评测机真的很好。

~~不怪评测机，其实 01 背包的复杂度通常也跑不满。~~

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1000010;
int t,b[N],c[N],f[N],dp[N];
signed main()
{
	cin>>t;
	memset(f,0x3f,sizeof(f));//初始化不能错！
	f[1]=0;
	for(int i=1;i<=1000;i++)//dp操作次数部分
		for(int j=1;j<=i;j++)
		{
			int u=i+i/j;
			f[u]=min(f[u],f[i]+1);
		}
	while(t--)
	{
		int n,k;
		vector<int>v,w;
		cin>>n>>k;
		for(int i=1;i<=n;i++) cin>>b[i];
		for(int i=1;i<=n;i++)
		{
			cin>>c[i];
			v.push_back(f[b[i]]);//通过查表法得到操作次数，转化为01背包
			w.push_back(c[i]);
		}
		memset(dp,0,sizeof(dp));//01背包部分
		for(int i=0;i<n;i++)
			for(int j=k;j>=v[i];j--)
				dp[j]=max(dp[j],dp[j-v[i]]+w[i]);
		
		cout<<dp[k]<<'\n';//01背包的状态表示不能忘！
	}
    return 0;
}
```

~~真就 Div.2 ABC 走人呗~~

---

## 作者：rsg26 (赞：0)

**题外话**

CF 机子太快了，直接被 $\mathcal{O}(nk)$ 卡过去了。

**正题**

我们首先考虑 $1$ 到 $x$ 的最小步骤。

* 状态：设 $dp_x$ 表示 $1$ 到 $x$ 的最小步骤
* 初值：$dp_1 = 0$
* 转移：这里采用 $\text{PUSH}$ 型，即对于每个 $i$ ，枚举一个 $j(1\le j\le i)$ ，并将 $dp_{i + \left \lfloor  \frac ij\right \rfloor}$ 与 $dp_i + 1$ 取 $\min$ 


有了这个 $dp$ 数组以后，问题变为了：背包体积为 $k$ ，共 $n$ 个物品，第 $i$ 个物品的体积为 $dp_{b_i}$ ，价值为 $c_i$ ，求最大的价值和。容易发现这是经典的“01背包”问题，所以 $\mathcal{O}(nk)$ 枚举即可。这样的做法大概是 $10^9$ 的，显然~~不会但做法不太好~~会 TLE， 所以考虑优化。

根据直觉，我们感觉 $dp$ 数组的数值是 $\log$ 级的，所以输出了一下，然后发现最大值只有 $12$ ！！！因为 $\sum dp_{b_i} \le 12\times n$ ，所以当 $k\ge \sum dp_{b_i}$ 时所有都可以成立，直接输出 $\sum c_i$ 即可，否则进行 “01背包”。此时，时间复杂度降到了 $\mathcal{O}(n\times \sum dp_{b_i}) = \mathcal{O}(12\times n ^ 2) = \mathcal{O}(n ^ 2)$  ，可以通过。

**代码**

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>

#define int long long

using namespace std;

const int NR = 1e3 + 5;
const int MR = 1e6 + 5;

int T, n, k, stp[MR], b[NR], w[NR], c[NR], f[MR];

signed main() {
    memset(stp, 0x3f, sizeof(stp)); stp[1] = 0;
    for (int i = 1; i <= NR; i++)
        for (int j = 1; j <= i; j++) stp[i + i / j] = min(stp[i + i / j], stp[i] + 1);
    scanf("%lld", &T);
    while (T --) {
        scanf("%lld %lld", &n, &k); int totb = 0, totc = 0;
        for (int i = 1; i <= n; ++i) scanf("%lld", &b[i]), w[i] = stp[b[i]], totb += w[i];
        for (int i = 1; i <= n; ++i) scanf("%lld", &c[i]), totc += c[i];
        if (k >= totb) printf("%lld\n", totc);
        else {
            memset(f, 0, sizeof(f));
            for (int i = 1; i <= n; ++i)
                for (int j = k; j >= w[i]; --j) f[j] = max(f[j - w[i]] + c[i], f[j]);
            printf("%lld\n", f[k]);
        }
    }

    return 0;
}
```

---

## 作者：Misaka_Mik0t0 (赞：0)

前置知识：[01 背包](https://www.luogu.com.cn/problem/P1048)、基础的 dp、[整除分块（其实不用）](https://www.luogu.com.cn/problem/P2261)。

首先有一个非常显然的想法，就是构造一个有 $n$ 个物品的 01 背包，背包的体积为 $k$。第 $i$ 个物品的体积为把 $a_i$ 从 $1$ 变到 $b_i$ 的最小步数，价值为 $c_i$。

那么现在问题变成了如何求出【把 $a_i$ 从 $1$ 变到 $b_i$ 的最小步数】。

数据范围上写着 $1\leq b_i\leq10^3$。于是不难想到把每个数都预处理一遍。

那么到底怎么实现呢？答案是 dp。

设 $dp_i$ 表示当 $b_x$ 为 $i$ 时所需要的步数。（不用关心 $x$，它是几都一样）

转移方程为 $b_i=\min\limits_{1\leq j<i\&\exists1\leq k\leq j\ \text{s.t.}j+\left\lfloor\frac{j}{k}\right\rfloor=i}dp_j+1$。

可以看出，填表法不行，要用刷表法。

这道题数据非常仁慈，可以遍历所有 $1\leq k\leq j$。但如果 $b_i$ 的范围不是 $10^3$ 而是 $10^5$，就需要用到整除分块。因为我们并不关心 $k$，只关心 $\left\lfloor\frac{j}{k}\right\rfloor$。

这是我在赛场上的代码：

```cpp
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
#define inf 0x3f3f3f3f
#define RI register signed
#define RC register char
#define RB register bool
inline int read(){
	RI res=0;RC ch=getchar();RB sng=false;
	while(ch<'0'||ch>'9'){
		if(ch=='-')sng=true;else sng=false;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		res=(res<<1)+(res<<3)+(ch^48);
		ch=getchar();
	}
	return sng?(-res):res;
}
int T,n,k,b[1005],c[1005],dp[1005],_19260817[1000005];
int main(){
	memset(dp,0x3f,sizeof(dp));
	dp[1]=0;
	for(int i=1;i<=1000;++i){
		for(int j=1,gx;j<=i;j=gx+1){
			gx=min(i,i/(i/j));
			dp[i+i/j]=min(dp[i+i/j],dp[i]+1);
		}
	}
	T=read();
	while(T--){                               
		n=read();k=read();
		for(int i=1;i<=n;++i)b[i]=dp[read()];
		for(int i=1;i<=n;++i)c[i]=read();
		memset(_19260817,0,sizeof(_19260817));
		for(int i=1;i<=n;++i)for(int j=k;j>=b[i];--j)_19260817[j]=max(_19260817[j],_19260817[j-b[i]]+c[i]);
		int ans=0;
		for(int i=0;i<=k;++i)ans=max(ans,_19260817[i]);
		printf("%d\n",ans);
	}
	return 0;
}
```

CF 的机器非常快，2s 能跑 $10^9$。

---

## 作者：cszhpdx (赞：0)

首先分析每一次操作，我们发现这些操作有两个重要的特征：

1. 互相独立
2. 操作过程中每一个 $a_i$ 单调不减

由此我们可以分析出，每一个 $a_i$ 要么一直操作到 $a_i=b_i$，要么不动，这很像一个背包，考虑如何转化。

我们发现对于相同的 $b_i$，最优操作的步数一定相同（特征 1），令 $p_i$ 表示将 1 变换成 $i$ 的最少次数，那么此时我们有 $n$ 个物品，第 $i$ 个代价为 $p_{b_i}$，价值为 $c_i$，这就变成了一个普通的背包问题，我们考虑 $p$ 的计算。

首先猜到动态规划，出题人非常善良，告诉我们 $b_i\le 1000$， 也就是 $p$ 允许在 $O(n^2)$ 的复杂度下计算。

转移很显然，对于 $p_i$ 我们枚举 $j$。将 $p_{i+\lfloor \frac{i}{j} \rfloor}$ 的值更新为 $\min\{p_{i+\lfloor \frac{i}{j} \rfloor},p_i+1\}$ 即可。复杂度 $O(n^2)$，但是 $\lfloor \frac{i}{j} \rfloor$ 对于不同的 $j$ 有很多是重复的，所以我们可以使用数论分块优化到 $O(n\sqrt{n})$。

接下来还剩最后一个问题，我们的背包容量是 $k\le10^6$，物品数量最多是 $n=1000$。显然会超时，神奇海螺告诉聪明的你其实物品的代价 $p_{b_i}\le 12$，可以先算出来 $p$ 然后利用魔法取最大得到这个结论，其实也很好理解，因为如果我们每次操作的 $x=1$ 的话，那么相当于倍增，所以这玩意最大差不多就是 $\lg$ 级别的。

于是我们快乐地搞完了这题。

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define cmin(a, b) (a)=min((a), (b))
#define cmax(a, b) (a)=max((a), (b))
#define mem(a, x) memset(a, x, sizeof(a))
#define rps(i, b, e) for(int i=(b);i<=(e);i++)
#define prs(i, e, b) for(int i=(e);i>=(b);i--)
#define rpg(i, g, x) for(int i=g.head[x];i;i=g.e[i].nxt)
#define opf(s) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)
using namespace std;
template<class T>
inline void read(T &x) {
	x=0;
	bool f=false;
	char c=getchar();
	while(!isdigit(c))f|=(c=='-'), c=getchar();
	while(isdigit(c))x=x*10+(c-'0'), c=getchar();
	if(f)x=-x;
}
//前面这一坨请自动忽略
const int NR=1010, NN=1e3, STEP=12;
int T, n, k, w[NR], v[NR], dp[NR], f[STEP*NN+10];
//dp[i]=p[i]
void prework() {
	mem(dp, 999999);
	dp[1]=0;
	rps(i, 1, NN)
		rps(j, 1, i)
			if(i+i/j<=NN)
				cmin(dp[i+i/j], dp[i]+1);
}
int main() {
	prework();
	read(T);
	while(T--) {
		read(n), read(k);
		int trk=0, sum=0;
		rps(i, 1, n)read(w[i]), w[i]=dp[w[i]], trk+=w[i];
		rps(i, 1, n)read(v[i]), sum+=v[i];
		if(k>=trk) {
			printf("%d\n", sum);
			continue;
		}
		mem(f, 0);
		rps(i, 1, n)prs(j, k, w[i])
			cmax(f[j], f[j-w[i]]+v[i]);
		printf("%d\n", f[k]);
	}
	return 0;
}
```



---

## 作者：Presentation_Emitter (赞：0)

因为 $a$ 数组初始全为 $1$，所以使用 DP 求出 $1$ 到 $[2,V](V=10^3)$ 内所有数字的最短步数，转移方程 $f_{i+\lfloor i/j \rfloor} \leftarrow \min\{f_i+1\}$，使用刷表法较为方便。

之后对于每一组数据，做一个体积为 $f_i$，收益为 $c_i$ 的背包即可。

观察到 $k$ 的范围巨大，但是 $k^\prime =n \max f_i$ 之后的值都是无用的。于是直接 $k \leftarrow \min(k,k^\prime)$。

$\max f_i=O(\log V)$，总时间复杂度 $\Theta(Tn\log V)$。

```cpp
ll T,n,k,b[1005],c[1005],f[1005],g[12005],bd;
int main()
{
	memset(f,0x3f,sizeof(f));f[1]=0;
	for(int i=1;i<=1000;++i)
		for(int j=1;j<=i;++j)
			if(i+i/j<=1000)tomin(f[i+i/j],f[i]+1);
	for(int i=1;i<=1000;++i)if(f[i]<inf)tomax(bd,f[i]);
	cerr<<bd<<endl;
	T=rd();
	while(T --> 0)
	{
		n=rd();k=rd();tomin(k,n*bd);clr(g,k+5);
		for(int i=1;i<=n;++i)b[i]=f[rd()];
		for(int i=1;i<=n;++i)c[i]=rd();
		for(int i=1;i<=n;++i)
			for(int j=k;j>=b[i];--j)tomax(g[j],g[j-b[i]]+c[i]);
		prt(g[k]);
	}
	ret 0;
}
```

---

## 作者：BootsH (赞：0)

__注：本文使用的缺省源在[这](https://www.luogu.com.cn/paste/7rwlw6tv)，且本文直接贴出来的代码只放 `namespace Solution` 部分。__

## 思路

我们发现，每次对 $a_{i}$ 的操作是独立的，且初始的所有 $a_{i}$ 都是 $1$，而且最后得到的所有 $b_{i}$ 满足 $1 \leq b_{i} \leq 1 \times 10^{3}$，那我们可以想到：预处理出每一个 $a_{i}$ 变成 $b_{i}$ 的操作次数。

然后，问题就转化成了一个 01 背包问题。它等价于：（下文中的 $b_{i}$ 均指的是 $a_{i}$ 转化成原题中 $b_{i}$ 的次数。）

你有一个容量为 $k$ 的背包，有 $n$ 个物品，每个物品占 $b_{i}$ 的体积，价值为 $c_{i}$，求能获得的最大价值。

## 注意

1. 可以另写一个程序打表预处理 $1$ 到达每一个数字的步数，或是在多测之前，在同一个程序内先写好。明显地，这一步可以通过 bfs 来完成。
2. 注意到如果我们直接 01 背包来做，时间复杂度是 $O(k \times n)$ 的，时间显然会爆（[我同学](https://www.luogu.com.cn/user/290023) 就被 [hack](https://codeforces.com/contest/1633/submission/144746896) 了，~~但是我幸免于难，不知道是超快读太快了还是没被发现~~赛后还是被[这位神仙](https://www.luogu.com.cn/user/306090)的[~~毒瘤~~数据](https://codeforces.com/contest/1633/hacks/782806/test)给 hack 了）。所以我们可以注意一个细节：所有的（$a_{i}$ 转化成原题中 $b_{i}$ 的次数）都小于 $12$，那么所需要的总次数不会大于 $12 \times n$，那么我们可以令 $k=\min\{k, 12 \times n\}$，这样就可以大大降低时间复杂度。

## 代码

#### 预处理(init.cpp)

```cpp
#include <queue>

namespace Solution
{
    #ifndef ONLINE_JUDGE
        std::ifstream cin; 
        std::ofstream cout;
    #else  
        using std::cin;
        using std::cout;
    #endif
    using namespace AKA;
    using IO::gc; using IO::pc; 
    using IO::iget; using IO::ipr; using IO::iwsp; using IO::iwln;
    using IO::llget; using IO::llpr; using IO::llwsp; using IO::llwln;
    using IO::ullget; using IO::ullwsp; using IO::ullwln;
    using IO::spr; using IO::swsp; using IO::swln;
    using IO::pr; using IO::wsp; 
    #define flp(name, lpst, lped) for (int name = lpst, name##end = lped; name <= name##end; ++name)
    #define plf(name, lpst, lped) for (int name = lpst, name##end = lped; name >= name##end; --name)


    std::vector<int> vis(1e3 + 5, -1);


    void main(void)
    {
        std::ios::sync_with_stdio(false);
        #ifndef ONLINE_JUDGE
            cin.open("main.in"), cout.open("1.out");
            IO::inbuf = cin.rdbuf(); IO::outbuf = cout.rdbuf();
        #else
            #if __cplusplus >= 201103L
                cin.tie(nullptr); cout.tie(nullptr);
            #else
                cin.tie(NULL); cout.tie(NULL);
            #endif
            IO::inbuf = cin.rdbuf(); IO::outbuf = cout.rdbuf();
        #endif


        int n = 1000;
        std::queue<int> qaq;
        qaq.push(1);
        vis[1] = 0;
        while (!qaq.empty())
        {
            int x = qaq.front(); qaq.pop();
            flp (i, 1, x / 2 + 1)
            {
                if (x + x / i <= n && !~vis[x + x / i])
                {
                    vis[x + x / i] = vis[x] + 1;
                    qaq.push(x + x / i);
                }
            }
        }
        flp (i, 1, n)
        {
            ipr(vis[i]), spr(", ");
        }


        #ifndef ONLINE_JUDGE
            cin.close(); cout.close();
        #endif
    }
} // namespace Solution
```

#### 主要部分(main.cpp)

```cpp
namespace Solution
{
    #ifndef ONLINE_JUDGE
        std::ifstream cin; 
        std::ofstream cout;
    #else  
        using std::cin;
        using std::cout;
    #endif
    using namespace AKA;
    using IO::gc; using IO::pc; 
    using IO::iget; using IO::ipr; using IO::iwsp; using IO::iwln;
    using IO::llget; using IO::llpr; using IO::llwsp; using IO::llwln;
    using IO::ullget; using IO::ullwsp; using IO::ullwln;
    using IO::spr; using IO::swsp; using IO::swln;
    using IO::pr; using IO::wsp; 
    #define flp(name, lpst, lped) for (int name = lpst, name##end = lped; name <= name##end; ++name)
    #define plf(name, lpst, lped) for (int name = lpst, name##end = lped; name >= name##end; --name)


    constexpr int maxn = 1e3 + 5, maxk = 1e6 + 25; 

    constexpr int w[maxk] = {0, 0, 1, 2, 2, 3, 3, 4, 3, 4, 4, 5, 4, 5, 5, 5, 4, 5, 5, 5, 5, 5, 6, 6, 5, 6, 6, 6, 6, 7, 6, 6, 5, 6, 6, 6, 6, 6, 6, 7, 6, 7, 6, 7, 7, 7, 7, 7, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 8, 8, 7, 8, 7, 7, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 8, 7, 8, 8, 8, 7, 8, 8, 8, 7, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 8, 9, 9, 9, 8, 9, 8, 8, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 8, 9, 8, 9, 8, 9, 8, 8, 9, 9, 8, 8, 9, 9, 9, 9, 9, 9, 8, 9, 9, 9, 9, 9, 9, 9, 8, 9, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 10, 10, 9, 10, 9, 9, 9, 10, 9, 9, 9, 10, 9, 10, 9, 9, 9, 10, 10, 10, 10, 10, 10, 10, 10, 10, 9, 10, 10, 10, 10, 10, 10, 10, 9, 10, 10, 10, 9, 10, 9, 9, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 10, 10, 9, 10, 10, 10, 9, 10, 10, 10, 9, 10, 10, 10, 9, 10, 9, 10, 10, 10, 10, 10, 9, 10, 9, 9, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 9, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 9, 10, 10, 10, 9, 9, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 11, 10, 10, 10, 10, 10, 10, 10, 11, 10, 10, 10, 10, 9, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 11, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 11, 10, 10, 10, 11, 10, 10, 10, 11, 11, 11, 11, 11, 10, 11, 11, 11, 10, 11, 10, 11, 10, 11, 11, 11, 10, 11, 10, 10, 10, 11, 11, 11, 10, 10, 10, 11, 10, 11, 10, 10, 10, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 10, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 10, 11, 11, 11, 11, 11, 11, 11, 10, 11, 11, 11, 10, 11, 10, 10, 9, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 11, 10, 11, 10, 11, 10, 11, 10, 11, 10, 11, 10, 10, 10, 11, 10, 11, 10, 11, 10, 11, 10, 11, 10, 10, 11, 11, 11, 11, 10, 11, 11, 11, 11, 11, 11, 11, 10, 11, 11, 11, 11, 11, 11, 11, 10, 10, 11, 11, 11, 11, 11, 11, 10, 11, 11, 11, 10, 10, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 10, 11, 11, 11, 10, 11, 10, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 10, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 10, 11, 11, 11, 11, 11, 11, 11, 10, 11, 10, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 12, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 12, 11, 12, 11, 11, 11, 11, 12, 12, 11, 11, 11, 12, 11, 11, 11, 12, 11, 12, 11, 11, 11, 11, 12, 12, 11, 12, 11, 12, 11, 11, 11, 11, 10, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 12, 11, 11, 11, 11, 11, 12, 11, 12, 11, 11, 12, 12, 11, 12, 11, 11, 11, 12, 11, 12, 11, 11, 11, 11, 11, 12, 11, 11, 11, 12, 11, 12, 11, 11, 12, 12, 11, 12, 11, 11, 11, 12, 12, 12, 11, 12, 11, 12, 11, 11, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 11, 12, 12, 12, 12, 12, 12, 12, 11, 12, 12, 12, 11, 11, 12, 12, 11, 12, 12, 12, 12, 12, 12, 12, 11, 12, 12, 12, 11, 12, 11, 11, 11, 12, 12, 12, 12, 12, 12, 12, 11, 12, 11, 12, 11, 11, 12, 12, 11, 12, 12, 12, 11, 12, 11, 12, 11, 11, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 11, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 11, 12, 12, 12, 12, 12, 12, 12, 12};

    int dp[maxk], c[maxn], b[maxn];

    // #define max(a, b) ((a) > (b) ? (a) : (b))

    inline void real_main()
    {
        int n = iget(), k = iget();
        flp (i, 1, n)
        {
            b[i] = w[iget()];
        }
        flp (i, 1, n)
        {
            c[i] = llget();
        }
        std::memset(dp, 0, sizeof(int) * (k + 5));
        k = std::min(k, 12 * n);
        flp (i, 1, n)
        {
            plf (j, k, b[i])
            {
                dp[j] = std::max(dp[j], dp[j - b[i]] + c[i]);
            }
        }
        // ll ans = 0;
        // flp (i, 1, k)
        // {
        //     ans = std::max(dp[i], ans);
        // }
        // llwln(ans);
        iwln(dp[k]);
    }


    void main(void)
    {
        std::ios::sync_with_stdio(false);
        #ifndef ONLINE_JUDGE
            cin.open("main.in"), cout.open("main.out");
            IO::inbuf = cin.rdbuf(); IO::outbuf = cout.rdbuf();
        #else
            #if __cplusplus >= 201103L
                cin.tie(nullptr); cout.tie(nullptr);
            #else
                cin.tie(NULL); cout.tie(NULL);
            #endif
            IO::inbuf = cin.rdbuf(); IO::outbuf = cout.rdbuf();
        #endif


        int General_Q = iget();
        flp (general_q, 1, General_Q)
        {
            real_main();
        }


        #ifndef ONLINE_JUDGE
            cin.close(); cout.close();
        #endif
    }
} // namespace Solution
```

---

