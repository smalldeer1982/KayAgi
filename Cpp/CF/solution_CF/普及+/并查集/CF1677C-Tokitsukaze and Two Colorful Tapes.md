# Tokitsukaze and Two Colorful Tapes

## 题目描述

Tokitsukaze has two colorful tapes. There are $ n $ distinct colors, numbered $ 1 $ through $ n $ , and each color appears exactly once on each of the two tapes. Denote the color of the $ i $ -th position of the first tape as $ ca_i $ , and the color of the $ i $ -th position of the second tape as $ cb_i $ .

Now Tokitsukaze wants to select each color an integer value from $ 1 $ to $ n $ , distinct for all the colors. After that she will put down the color values in each colored position on the tapes. Denote the number of the $ i $ -th position of the first tape as $ numa_i $ , and the number of the $ i $ -th position of the second tape as $ numb_i $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1677C/ba8639f69fd74760b5261096016619c105b9cbe6.png)For example, for the above picture, assuming that the color red has value $ x $ ( $ 1 \leq x \leq n $ ), it appears at the $ 1 $ -st position of the first tape and the $ 3 $ -rd position of the second tape, so $ numa_1=numb_3=x $ .

Note that each color $ i $ from $ 1 $ to $ n $ should have a distinct value, and the same color which appears in both tapes has the same value.

After labeling each color, the beauty of the two tapes is calculated as $ $$$\sum_{i=1}^{n}|numa_i-numb_i|. $ $$$

Please help Tokitsukaze to find the highest possible beauty.

## 说明/提示

An optimal solution for the first test case is shown in the following figure:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1677C/eb5a2fd8a44a35877d106dc26e9dcf9fd0a2a486.png)The beauty is $ \left|4-3 \right|+\left|3-5 \right|+\left|2-4 \right|+\left|5-2 \right|+\left|1-6 \right|+\left|6-1 \right|=18 $ .

An optimal solution for the second test case is shown in the following figure:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1677C/ec6542f7ba45f38760ee0d113e52ba6999ceef87.png)The beauty is $ \left|2-2 \right|+\left|1-6 \right|+\left|3-3 \right|+\left|6-1 \right|+\left|4-4 \right|+\left|5-5 \right|=10 $ .

## 样例 #1

### 输入

```
3
6
1 5 4 3 2 6
5 3 1 4 6 2
6
3 5 4 6 2 1
3 6 4 5 2 1
1
1
1```

### 输出

```
18
10
0```

# 题解

## 作者：I_am_Accepted (赞：9)

### Analysis

将一个位置看成两个色带对应位置颜色之间的边。

这样我们得到了一张 $n$ 个点的图，由许多分离的环构成。

我们要给每个点赋值 $1\to n$，使得每条边权（为两端点点权差的绝对值）之和最大。

若一个点的权值小于两边，则称为「山谷」；若一个点的权值大于两边，则称为「山峰」；剩下的为「山坡」。显然山峰与山谷个数相同。

我们用另一种方式算边权和：设山峰的点权和为 $x$，山谷为 $y$，则边权和为 $2(x-y)$。

由于山坡对答案没贡献，我们尽量多山峰（$=$ 山谷）。考虑单个环，设环长为 $L$，则山峰（$=$ 山谷）个数最多

$$\left\lfloor\frac{L}{2}\right\rfloor$$

设这样算出来山峰最多 $a$ 个。

所以我们将山峰们设为最大的值 $[n-a+1,n]\cap\mathbb{Z}$，山谷们设为最小的 $[1,a]\cap\mathbb{Z}$。

答案也就呼之欲出：

$$2a(n-a)$$

### Code

```cpp
//Said no more counting dollars. We'll be counting stars.
#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define For(i,j,k) for(int i=j;i<=k;i++)
#define Rof(i,j,k) for(int i=j;i>=k;i--)
#define int long long
#define N 100010

int n,a[N],b[N],ans;
bool vis[N];
int dfs(int x){
	vis[x]=1;
	if(vis[b[x]]) return 1;
	else return 1+dfs(b[x]);
}
void work(){
	cin>>n;
	int x;
	For(i,1,n){
		cin>>x;
		a[x]=i;
	}
	For(i,1,n){
		cin>>x;
		b[i]=a[x];
	}
	ans=0;
	For(i,1,n) vis[i]=0;
	For(i,1,n) if(!vis[i]) ans+=dfs(i)>>1;
	cout<<2*ans*(n-ans)<<endl;
}
signed main(){IOS;
	int T;cin>>T;
	while(T--)work();
return 0;}
```


---

## 作者：Leasier (赞：3)

这种排列上的问题不难想到置换环。考虑抓出形如 $a_{x_1} \to b_{x_1} \to a_{x_2} \to b_{x_2} \to \cdots \to a_{x_k} \to b_{x_k} \to a_{x_1}$ 的环（其中 $b_{x_i} = a_{x_{i \bmod k + 1}}$）。

问题转化为给每种颜色编号（即为排列 $p$），使得每个环中 $\displaystyle\sum_{i = 1}^k |p_{a_{x_i}} - p_{b_{x_i}}|$ 的和最大。

绝对值可以拆成两种情况：$|a - b| = a - b \operatorname{or} b - a$。

由于环与环之间独立，我们考虑每个单独的环。

在一个环中，一个数 $x$ 有三种情况：

- 始终为正，贡献为 $2x$。
- 一正一负，贡献为 $0$。
- 始终为负，贡献为 $-2x$。

贪心地，我们希望尽量让大的数符号为正，小的数符号为负。

每让一个大的数的符号为正，就会产生一个小的数符号为负。显然，在每个环内，正的较大的数越多越好。

所以我们在一个大小为 $k$ 的环里让其中 $\lfloor \frac{k}{2} \rfloor$ 个较大的数为正，$\lfloor \frac{k}{2} \rfloor$ 个较小的数为负，剩下的 $k \bmod 2$ 个数为 $0$。

于是我们统计出所有环中为正的数的个数，设之为 $k$，则让 $1 \sim k$ 为负，让 $n - k + 1 \sim n$ 为正，其余数为 $0$。

推一下式子就可以得到答案为 $2k(n - k)$。

代码：
```cpp
#include <stdio.h>

typedef long long ll;

int a[100007], b[100007], pos[100007];
bool vis[100007];

int main(){
	int t;
	scanf("%d", &t);
	for (int i = 1; i <= t; i++){
		int n, m = 0, sum = 0;
		scanf("%d", &n);
		for (int j = 1; j <= n; j++){
			vis[j] = false;
		}
		for (int j = 1; j <= n; j++){
			scanf("%d", &a[j]);
			pos[a[j]] = j;
		}
		for (int j = 1; j <= n; j++){
			scanf("%d", &b[j]);
		}
		for (int j = 1; j <= n; j++){
			if (!vis[j]){
				int size = 0;
				for (int k = j; !vis[k]; k = b[pos[k]]){
					vis[k] = true;
					size++;
				}
				sum += size / 2;
			}
		}
		printf("%lld\n", (ll)2 * sum * (n - sum));
	}
	return 0;
}
```

---

## 作者：Renshey (赞：3)

#### 题意

给定两个排列 $\{p_n\}$ 与 $\{q_n\}$，构造一个排列 $\{r_n\}$，求 $\sum_{i=1}^n \lvert r_{p_i} - r_{q_i} \rvert$ 的最大值。

#### 数据范围

$n \le 10^5$

#### 题解

首先转化题意，相当于给定若干个环，然后要给点重编号，使得所有边的端点编号差之和最大。

考虑拆绝对值，总共会贡献 $n$ 次 $-1$ 与 $n$ 次 $+1$，尽可能地让较小数分配到 $-1$，较大数分配到 $+1$ 显然是最优的。注意到长度为 $l$ 的环上能贡献 $\lfloor \frac{l}{2} \rfloor$ 次 $-1$ 与 $+1$，$l \bmod 2$ 次 $0$。因此直接统计出 $w = \sum \lfloor \frac{l}{2} \rfloor$，则答案即为 $(\sum_{i=1}^w -2i)+(\sum_{i=1}^w2(n-i+1))=2(n-w)w$。

时间复杂度和空间复杂度均为 $O(n)$。

#### 代码

```cpp
#include <bits/stdc++.h>
#define Getchar() p1 == p2 and (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++
char buf[1 << 21], *p1, *p2;
inline int read (void)
{
	int x = 0; char c = Getchar(); bool f = (c != '-');
	while (c < '0' or c > '9') c = Getchar(), f &= c != '-';
	while (c >= '0' and c <= '9') x = x * 10 + c - 48, c = Getchar();
	return f ? x : -x;
}
const int maxn = 100000 + 10;
int n, a[maxn], b[maxn]; bool vis[maxn];
inline void solve (void)
{
	n = read(); int w = 0;
	for (int i = 1; i <= n; i++) a[i] = read();
	for (int i = 1; i <= n; i++) b[read()] = i;
	for (int i = 1; i <= n; i++) if (!vis[i])
	{
		int len = 0;
		for (int j = i; !vis[j]; j = b[a[j]]) vis[j] = true, len++;
		w += len >> 1;
	}
	printf("%lld\n", 2LL * (n - w) * w);
	for (int i = 1; i <= n; i++) vis[i] = false;
}
signed main ()
{
	for (int T = read(); T--; ) solve();
	return 0;
}
```

---

## 作者：Union_Find (赞：0)

这是一道比较板的题。

首先这种题，我们发现，如果将上下两种颜色连接，就会形成一个环。比如样例 1，其中 $1,5,3,4$ 和 $2,6$ 形成了两个环。而且每个环是独立的，所以我们可以先只考虑一个环。

我们会发现，$\left | a-b \right | $ 只有 $a-b$ 或者 $b-a$ 两种情况。所以说，对于环中的一个数 $x$，它要么是都是被减去，要么只减去一次，要么都是减去其它数。所以他的贡献只有 $-2x,0,2x$ 三种。并且都是减去其它数的数在大小为 $t$ 的环中至多有 $\left \lfloor \frac{t}{2}  \right \rfloor $ 个。所以我们设总共有 $k$ 个都是减去其它数的数，那么会有 $2k$ 的贡献。再乘上剩下的数 $n-k$，就是答案。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define il inline
ll T, n, a[100005], b[100005], fa[100005], t[100005], k;
il ll find(ll x){
	if (fa[x] == x) return x;
	return fa[x] = find(fa[x]);
}
int main(){
	scanf ("%lld", &T);
	while (T--){
		scanf ("%lld", &n);
		for (int i = 1; i <= n; i++) scanf ("%lld", &a[i]);
		for (int i = 1; i <= n; i++) scanf ("%lld", &b[i]);
		for (int i = 1; i <= n; i++) fa[i] = i, t[i] = 0;
		k = 0;
		for (int i = 1; i <= n; i++){
			ll u = find(a[i]), v = find(b[i]);
			if (u != v) fa[u] = v;
		}
		for (int i = 1; i <= n; i++) t[find(i)]++;
		for (int i = 1; i <= n; i++) if (fa[i] == i) k += t[i] / 2;
		printf ("%lld\n", 2 * k * (n - k));
	}
	return 0;
}

```

---

