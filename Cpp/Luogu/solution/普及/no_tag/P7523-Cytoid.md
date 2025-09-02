# Cytoid

## 题目背景

![Welcome to Cytoid!](https://cdn.luogu.com.cn/upload/image_hosting/zzg1blb0.png)

众所周知，尽管很菜，但 colazcy 仍然很喜欢玩 Cytus。

## 题目描述

一天，colazcy 又在越级打谱。不到一分钟，colazcy 把手机一摔，骂道：“什么垃圾铺面！” 于是他准备在 Cytoid 上面做一个自制铺恶心别人。

colazcy 准备上一波劲爆 $m$ 押，共有 $n$ 排。也就是说，他的铺面是一个 $n\times m$ 的矩阵，其中每一个位置可以是 Drag 也可以是 Click。colazcy 已经确定了其中一些位置应该是什么元素，但剩下的还没有确定。

但是 colazcy 发现，他铺面对应的矩形如果有一个子矩形中所有元素都是 Drag，那么玩家就可以一直按住糊过去。colazcy 定义一张铺面的简单度为这张铺面对应的矩形中全都是 Drag 的子矩形个数。

现在 colazcy 把他还未完成的铺面给了你，希望你告诉他：如果他等概率随机地把剩下没有决定的元素填成 Drag / Click，最终铺面简单度的期望是多少。不难观察到答案总是一个有理数，你只需要输出这个答案对 $998244353$ 取模的结果。如果你不知道如何将一个有理数对质数取模，可以参考 [有理数取模](https://www.luogu.com.cn/problem/P2613)。

## 说明/提示

### 样例解释

样例一：整个铺面已经确定，而简单度 = 全是 Drag 的子矩阵数目 = $5$。

样例二：只有一个位置没有确定：当这个位置填 Drag 时，简单度为 $9$；当这个位置填 Click 时，简单度为 $5$。则期望简单度为 $\dfrac{9+5}2=7$。

### 数据范围

对于全部数据，有 $1\le n,m\le 100$。

Subtask 1 (15 pts)：保证没有尚未确定的元素（即输入没有 `?`）。

Subtask 2 (15 pts)：保证尚未确定的元素个数 $\le 3$。

Subtask 3 (30 pts)：保证 $n\le 30$。

Subtask 4 (40 pts)：无特殊限制。

## 样例 #1

### 输入

```
2 2
oo
xo```

### 输出

```
5```

## 样例 #2

### 输入

```
2 2
oo
?o```

### 输出

```
7```

## 样例 #3

### 输入

```
3 4
o?o?
?xox
o?xo```

### 输出

```
499122189```

# 题解

## 作者：Mivik (赞：17)


### Subtask 1

我会单调栈！

### Subtask 2

我会爆搜！

### Subtask 3 & 4

不难发现由于 $n\le 100$，我们直接枚举每一个可能的子矩阵算它全是 Drag 的概率然后加起来即可。如果这个矩阵中有 Click 概率就是 $0$，否则概率为 $\dfrac 1{2^c}$，其中 $c$ 为矩阵中 `?` 的个数。

[mivik.h](https://mivik.gitee.io/mivik.h) / [代码](https://paste.ubuntu.com/p/Gyrm8FvMqQ/)


---

## 作者：日居月诸 (赞：7)

先考虑这样一个问题：对于一个 0/1 矩形，要求其全 0 子矩形的数量。

这个可以先枚举 矩形右下角，再枚举左下角（或者说，枚举矩形的横长度），快速转移出全 0 子矩形的最大高度（这个可以直接从上一行转移过来），做到 $O(n^3)$。

这题也类似，只是计算的是期望高度。时间复杂度 $O(n^3)$（似乎很多人写的是 $O(n^4)$？

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
char In[1 << 20], *ss = In, *tt = In;
#define getchar() (ss == tt && (tt = (ss = In) + fread(In, 1, 1 << 20, stdin), ss == tt) ? EOF : *ss++)
ll read() {
	ll x = 0, f = 1; char ch = getchar();
	for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + int(ch - '0');
	return x * f;
}
int readox() {
	char ch = getchar();
	for(; ch != 'o' && ch != 'x' && ch != '?'; ch = getchar());
	return ch == 'o' ? 0 : (ch == 'x' ? 1 : 2);
}
const int P = 998244353, MAXN = 105;
int pls(int a, int b) {return a + b < P ? a + b : a + b - P;}
int mns(int a, int b) {return a < b ? a + P - b : a - b;}
int mul(int a, int b) {return 1ll * a * b % P;}
int qpow(int a, int n=P-2) {int ret = 1; for(; n; n >>= 1, a = mul(a, a)) if(n & 1) ret = mul(ret, a); return ret;}
int n, m, bo[MAXN][MAXN], he[MAXN][MAXN][MAXN], cnt[MAXN][MAXN][3], inv2k[MAXN], ans;
int main() {
	n = read(); m = read();
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			bo[i][j] = readox();
	for(int i = 1; i <= n; i++) {
		for(int k = 0; k <= 2; k++) cnt[i][0][k] = 0;
		for(int j = 1; j <= m; j++)
			for(int k = 0; k <= 2; k++)
				cnt[i][j][k] += cnt[i][j-1][k] + (bo[i][j] == k);
	}
	inv2k[0] = 1; inv2k[1] = 499122177;
	for(int i = 2; i <= n; i++) inv2k[i] = mul(inv2k[i-1], inv2k[1]);
	for(int i = 1; i <= n; i++) 
		for(int j = 1; j <= m; j++) {
			for(int k = j; k >= 1; k--) {
				if(cnt[i][j][1] - cnt[i][k-1][1] > 0) break;
				int t = cnt[i][j][2] - cnt[i][k-1][2];
				he[i][j][k] = mul(inv2k[t], he[i-1][j][k] + 1);
				ans = pls(ans, he[i][j][k]);
			}
		}
	/*
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			for(int k = j; k >= 1; k--)
				printf("(%d, %d, %d): %d\n", i, j, k, he[i][j][k]);
				*/
	printf("%d\n", ans);
	return 0;
}

```

---

## 作者：lcyxds (赞：1)

算法：二维前缀和

数学：逆元，期望

数据范围较小，考虑枚举每个子矩阵，计算每个子矩阵对简单度的贡献。

依题意可得，如果子矩阵中全都是 Drag，这个子矩阵就会对答案产生 1 的贡献。

那么如何计算子矩阵的期望贡献呢？如果子矩阵中本身有 `x`，则这个子矩阵一定不能产生贡献；如果没有 `x` 而有 $t$ 个 `?`，那么这个子矩阵将有 $\frac1{2^t}$ 的概率全都是 Drag，于是该子矩阵的期望贡献就是 $\frac1{2^t}$。

由于期望的可加性，把所有子矩阵的贡献加起来即为答案。

具体实现：使用二维前缀和，可以 $O(1)$ 求一个子矩阵是否有 `x` 以及有多少个 `?`。预处理所有 $\frac1{2^i}\mod998244353$ 的值，可以省去一个 $\log$。

时间复杂度 $\Theta(n^4)$，空间复杂度 $\Theta(n^2)$。

```cpp
#include <iostream>
#include <cstdio>
#define ll long long

const ll MOD = 998244353;
const ll _2 = (MOD+1)/2;

using namespace std;

int click[110][110];
int wen[110][110];
ll pow2[12100];
int n, m;
ll res;

bool Cube(int x1, int x2, int y1, int y2) {
  return click[x2][y2]-click[x1][y2]-click[x2][y1]+click[x1][y1];
}

ll Count(int x1, int x2, int y1, int y2) {
  //cout << x1 << ',' << x2 << ',' << y1 << ',' << y2 << endl;
  return pow2[wen[x2][y2]-wen[x1][y2]-wen[x2][y1]+wen[x1][y1]];
}

int main() {
  freopen("P7523.in", "r", stdin);
  scanf("%d%d", &n, &m);
  char c;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      do {
	c = getchar();
      } while (c!='o'&&c!='x'&&c!='?');
      switch(c) {
      case 'x':
	click[i][j]++;
	continue;
      case '?':
	wen[i][j]++;
      }
    }
  }
  fclose(stdin);
  pow2[0] = 1ll;
  for (int i = 1; i <= n*m; i++) {
    pow2[i] = pow2[i-1]*_2%MOD;
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 2; j <= m; j++) {
      click[i][j]+=click[i][j-1];
      wen[i][j]+=wen[i][j-1];
    }
  }
  for (int j = 1; j <= m; j++) {
    for (int i = 2; i <= n; i++) {
      click[i][j]+=click[i-1][j];
      wen[i][j]+=wen[i-1][j];
    }
  }
  for (int x1 = 0; x1 < n; x1++) {
    for (int x2 = x1+1; x2 <= n; x2++) {
      for (int y1 = 0; y1 < m; y1++) {
	for (int y2 = y1+1; y2 <= m; y2++) {
	  if (!Cube(x1, x2, y1, y2)) res+=Count(x1, x2, y1, y2);
	}
      }
    }
  }
  printf("%lld\n", res%MOD);
  return 0;
}

```


---

## 作者：xvl_ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P7523)

一道二维前缀和题。

先想想怎么求出某个矩阵有多少种可能全是 Drag。

如果一个子矩阵中有 Click 就不可能对答案有贡献（概率为 $0$），所以只需要考虑子矩阵中只包含 `?` 和 Drag 的情况。此时必须每个 `?` 都是 Drag 才会对答案有贡献，也就是有 $\dfrac{1}{2^k}$ 的概率。其中 $k$ 为 `?` 的个数。

于是我们用二维前缀和维护某个子矩阵中 `?` 和 Click 的数量，然后 $O(n^4)$ 暴力枚举子矩阵，将每个子矩阵产生贡献的概率全部加起来即是答案。

### Code

```cpp
#include <bits/stdc++.h>

const long long IMX = 1ll << 30;
const long long LMX = 1ll << 60;

const long long MOD1 = 998244353;
const long long MOD2 = 1000000007;
const long long MOD3 = 1000000009;

using ll = long long;
using i128 = __int128;
using ld = long double;
using f128 = __float128;

namespace xvl_ {
    #define SP(n, x) std :: setprecision(n) << std :: fixed << x
    #define DEBUG(x) std :: cerr << #x << " = " << x << '\n'
    #define fst first
    #define snd second
    template <typename T> T Max(T a, T b) { return a > b ? a : b; } template <typename T, typename... Args> T Max(T a, Args... args) { return a > Max(args...) ? a : Max(args...); }
    template <typename T> T Min(T a, T b) { return a < b ? a : b; } template <typename T, typename... Args> T Min(T a, Args... args) { return a < Min(args...) ? a : Min(args...); }
}
using namespace std;
using namespace xvl_;
const int N = 105, M = 105, MOD = MOD1;
ll n, m, ans;
ll sum1[N][M], sum2[N][M]; // sum1 维护 Click 的数量，sum2 维护 ? 的数量
char c[N][M];
ll query1(int sx, int sy, int tx, int ty) { 
    return sum1[tx][ty] - sum1[sx - 1][ty] - sum1[tx][sy - 1] + sum1[sx - 1][sy - 1]; 
}
ll query2(int sx, int sy, int tx, int ty) { 
    return sum2[tx][ty] - sum2[sx - 1][ty] - sum2[tx][sy - 1] + sum2[sx - 1][sy - 1]; 
}
ll qpow(ll n, ll m, ll p) {
    ll res = 1;
    while (m) {
        if (m & 1) res = res * n % p;
        m >>= 1, n = n * n % p;
    }
    return res;
}
int main() {
    // freopen("InName.in", "r", stdin);
    // freopen("OutName.out", "w", stdout);
    ios :: sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) { for (int j = 1; j <= m; j++) cin >> c[i][j]; }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            sum1[i][j] = sum1[i - 1][j] + sum1[i][j - 1] - sum1[i - 1][j - 1] + (c[i][j] == 'x');
            sum2[i][j] = sum2[i - 1][j] + sum2[i][j - 1] - sum2[i - 1][j - 1] + (c[i][j] == '?');
        }
    }
    for (int sx = 1; sx <= n; sx++) {
        for (int sy = 1; sy <= m; sy++) {
            for (int tx = sx; tx <= n; tx++) {
                for (int ty = sy; ty <= m; ty++) {
                    ll c1 = query1(sx, sy, tx, ty), c2 = query2(sx, sy, tx, ty);
                    if (!c1) ans = (ans + qpow(qpow(2, c2, MOD), MOD - 2, MOD)) % MOD;
                }
            }
        }
    }
    cout << ans;
    return 0;
}
```

---

## 作者：DP王子 (赞：0)

暴力枚举每个矩阵的贡献，若矩阵内有 `x` 那贡献为 $0$，剩下的情况设 `?` 个数为 $x$，则贡献为 $\dfrac{1}{2^x}$，原因是只有当所有 `?` 为 `o` 才会有贡献。

二维前缀和可以维护这个。再预处理一下 $2$ 的次幂，最后复杂度是 $O(n^4)$。

很丑的代码：

```cpp
//by DP王子 
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll mod=998244353;
int n,m;
char a[101][101];
int sum1[101][101],sum2[101][101];
ll ans,po[100001];
ll ksm(ll x,ll y)
{
	if (y==0) return 1;
	ll t=ksm(x,y/2);
	t=t*t%mod;
	if (y%2==0) return t;
	return t*x%mod;
}
int ask(int i,int j,int k,int p,int t)
{
	if (t==1) return sum1[j][p]-sum1[i-1][p]-sum1[j][k-1]+sum1[i-1][k-1];
	else return sum2[j][p]-sum2[i-1][p]-sum2[j][k-1]+sum2[i-1][k-1];
 } 
int main()
{
	cin >> n >> m;
	po[0]=1;
	for (int i=1;i<=n*m;i++) po[i]=po[i-1]*2ll%mod;
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=m;j++)
		{
			cin >> a[i][j];
			if (a[i][j]=='?') sum1[i][j]=1;
			else if (a[i][j]=='x') sum2[i][j]=1;
		}
	}
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=m;j++)
		{
			sum1[i][j]=sum1[i-1][j]+sum1[i][j-1]-sum1[i-1][j-1]+sum1[i][j];
			sum2[i][j]=sum2[i-1][j]+sum2[i][j-1]-sum2[i-1][j-1]+sum2[i][j];
		}
	}
	for (int i=1;i<=n;i++)
	{
		for (int j=i;j<=n;j++)
		{
			for (int k=1;k<=m;k++)
			{
				for (int p=k;p<=m;p++)
				{
					int u=ask(i,j,k,p,2);
					if (u>0) break;
					u=ask(i,j,k,p,1);
					ans=(ans+po[n*m-u])%mod;
				}
			}
		}
	}
	ll res=ksm(po[n*m],mod-2);
	ans=(ans*res)%mod;
	cout << ans;
	return 0;
}
```


---

