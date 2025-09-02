# [USACO20JAN] Farmer John Solves 3SUM G

## 题目描述

Farmer John 相信他在算法设计上实现了一个重大突破：他声称他发现了一个 3SUM 问题的近似线性时间算法，这是一个有名的算法问题，尚未发现比运行速度比平方时间明显更优的解法。3SUM 问题的一个形式是：给定一个整数数组 $s_1,\ldots,s_m$，计算不同索引组成的无序不重三元对 $i,j,k$ 的数量，使得 $s_i+s_j+s_k=0$（$i, j, k$ 互不相同）。

为了测试 Farmer John 的断言，Bessie 提供了一个 $N$ 个整数组成的数组 $A$（$1 \leq N \leq 5000$）。Bessie 还会进行 $Q$ 次询问（$1 \leq Q \leq 10^5$），每个询问由两个索引 $1 \leq a_i \leq b_i \leq N$ 组成。对于每个询问，Farmer John 必须在子数组 $A[a_i \ldots b_i]$ 上求解 3SUM 问题。

不幸的是，Farmer John 刚刚发现了他的算法中的一个错误。他很自信他能修复这个算法，但同时，他请你帮他先通过 Bessie 的测试！

## 说明/提示

### 样例解释

对于第一个询问，所有的三元对为 $(A_1,A_2,A_5)$ 和 $(A_2,A_3,A_4)$。

### 子任务

- 测试点 $2 \sim 4$ 满足 $N \leq 500$。
- 测试点 $5 \sim 7$ 满足 $N \leq 2000$。
- 测试点 $8 \sim 15$ 没有额外限制。

## 样例 #1

### 输入

```
7 3
2 0 -1 1 -2 3 3
1 5
2 4
1 7```

### 输出

```
2
1
4```

# 题解

## 作者：fighter (赞：32)

发现$n \leq 5000$，那么我们自然想到$O(n^2)$预处理之后$O(1)$回答询问。

先考虑一个更简单的问题，如果$f[i][j]$表示在区间$[l,r]$中，满足$k \in (l,r), a[k]+a[l]+a[r]=0$的$k$的数量，那么我们是可以枚举左右端点，用一个桶做到$O(n^2)$预处理$f$的。

那么$f$与最后的答案是什么关系呢？最后要求的是：在一段区间内，左右端点**不强制**选的方案数。这隐隐约约的有点像是$f$数组的一个前缀和。

我们可以考虑先求出$s[l][r]$表示左端点在$[1,l]$内，右端点在$[1,r]$内的总方案数。这就真的是$f$的二位前缀和了。

可以这么理解，把$f[l][r]$对应到平面上的一个点，那么$s[l][r]$就是从$(1,1)$到$(l,r)$的这个矩形中所有点的和。这样我们也就可以在$O(n^2)$的时间内求出$s$。

同样的，最后的答案实际上是区间左右端点都在$[l,r]$内总答案。对应到平面上也就是左上角为$(l,l)$，右下角为$(r,r)$的矩形中所有点的和。这样就可以通过$s$来$O(1)$求答案了。

## 代码

注意开桶的时候需要平移值域

```cpp
#include <bits/stdc++.h>
#define ll long long
#define MAX 5005
#define K 1000000
using namespace std;

int n, Q;
int a[MAX], cnt[2000005];
ll s[MAX][MAX];

int main()
{
    cin >> n >> Q;
    for(int i = 1; i <= n; ++i){
        scanf("%d", &a[i]), a[i] += K;
    }
    for(int i = 1; i <= n; ++i){
        for(int j = i+1; j <= n; ++j){
            if(j > i+1){
                if(a[i]+a[j] <= K*3 && a[i]+a[j] >= K) s[i][j] = cnt[K*3-a[i]-a[j]];
            }
            cnt[a[j]]++;
        }
        for(int j = i+1; j <= n; ++j){
            cnt[a[j]]--;
        }
    }
    for(int i = 1; i <= n; ++i){
        for(int j = 1; j <= n; ++j){
            s[i][j] += s[i-1][j]+s[i][j-1]-s[i-1][j-1];
        }
    }
    int l, r;
    while(Q--){
        scanf("%d%d", &l, &r);
        printf("%lld\n", s[r][r]-s[l-1][r]-s[r][l-1]+s[l-1][l-1]);
    }

    return 0;
}
```



---

## 作者：wmy_goes_to_thu (赞：15)

一月份 USACO 考场上的做法。

由于询问没有什么太大的关系，所以我们可以采用预处理答案的方式。

设 $f_{i,j}$ 表示 $i \sim  j$ 的 3SUM 数量，这是一个区间 dp，根据容斥原理，容易退出 $f_{i,j}=f_{i+1,j}+f_{i,j-1}-f_{i+1,j-1}+p_{i,j}$，其中 $p_{i,j}$ 是 $[i+1,j-1]$ 这个区间内的 $r$ 的数量，满足 $a_i+a_r+a_j=0$。

那么 $p$ 数组怎么求呢？

我们来想这样的一个问题：

给定一个长度为 $3000$ 的数列 $a$ 以及一个数 $t$，求出所有的 $(i,j)$，满足 $\sum\limits_{l=i}^j a_l=t$。那么如果暴力枚举是立方的，肯定不行，但是我们可以枚举左端点，然后右端点依次推出来，这就可以了！所以这道题也可以这么做：枚举左端点，顺推右端点。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[10005];
int h[3000005];
long long f[5005][5005];
int main()
{
	freopen("threesum.in","r",stdin);
	freopen("threesum.out","w",stdout);
	int n,q;
	cin>>n>>q;
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)
	{
		for(int j=i;j<=n;j++)h[a[j]+1000000]=0;
		for(int j=i+1;j<=n;j++)
		{
			if(-a[i]-a[j]+1000000>=0)f[i][j]=h[-a[i]-a[j]+1000000];
			h[a[j]+1000000]++;
		}
	}
	for(int l=2;l<=n;l++)for(int i=1;i<=n;i++)
	{
		int j=i+l-1;
		if(j<=n)
		{
			f[i][j]+=f[i+1][j]+f[i][j-1]-f[i+1][j-1];
		}
	}
	for(int i=1;i<=q;i++)
	{
		int ll,rr;
		scanf("%d%d",&ll,&rr);
		printf("%lld\n",f[ll][rr]);
	}
	return 0;
}
```

---

## 作者：__Watcher (赞：10)

要是想不到这道题的算法区间 dp 好好反思。

---

令 $dp_{i,j}$ 为区间 $i$~$j$ 的最终答案。$dp_{i+1,j}$ 为不选左端点的情况，$dp_{i,j-1}$ 为不选右端点的情况答案，两者都可以贡献在 $dp_{i,j}$ 上。主要，$dp_{i+1,j-1}$ 表示的左右端点同时不选的情况被重复计算了，因此需要减去 $dp_{i+1,j-1}$。

那么若 $a_i$ 和 $a_j$ 同时选取呢？因此我们需要预处理出 $i\rm{+}1$~$j\rm{-}1$ 区间内值为 $-a_i-a_j$ 的元素个数（自行理解）。于是，枚举左端点 $i$，并且在右端点右移时开个桶就完事了。

---

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int M=1e6;
ll read() {
	ll x=0, f=1; char ch=' ';
	while(!isdigit(ch)) {ch=getchar(); if(ch=='-') f=-1;}
	while(isdigit(ch)) x=(x<<3)+(x<<1)+(ch^48), ch=getchar();
	return x*f;
}
int n, q, a[5005], f[5005][5005], cnt[3000005];
ll dp[5005][5005];
// f[i][j]:i+1~j-1 区间内值为 -a[i]-a[j] 的元素个数
// cnt：统计数字用的桶
int main() {
	cin>>n>>q;
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1;i<=n;i++) {
		for(int j=i+1;j<=n;j++) {
			f[i][j]=cnt[-a[i]-a[j]+M*2];
			cnt[a[j]+M*2]++;//由于有负数，需要加上一个固定数使下标非负
		}
		for(int j=i+1;j<=n;j++) cnt[a[j]+M*2]=0;//不能 memset，复杂度不对
	}
	for(int len=3;len<=n;len++) {
		for(int i=1;i+len-1<=n;i++) {
			int j=i+len-1;
			dp[i][j]=dp[i+1][j]+dp[i][j-1]-dp[i+1][j-1]+f[i][j];//转移，注意需要先枚举区间长度，保证转移所需要的值已经处理完成
		}
	}
	while(q--) {
		int a=read(), b=read();
		printf("%lld\n", dp[a][b]);
	}
}
```

于是完美的 MLE 了。发现 $f$ 数组可以重复利用，删掉 $dp$ 数组，才能卡进空间。

提供代码，仅供参考：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int M=1e6;
ll read() {
	ll x=0, f=1; char ch=' ';
	while(!isdigit(ch)) {ch=getchar(); if(ch=='-') f=-1;}
	while(isdigit(ch)) x=(x<<3)+(x<<1)+(ch^48), ch=getchar();
	return x*f;
}
int n, q, a[5005], cnt[4000005];
ll f[5005][5005];
int main() {
	cin>>n>>q;
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1;i<=n;i++) {
		for(int j=i+1;j<=n;j++) {
			f[i][j]=cnt[-a[i]-a[j]+M*2];
			cnt[a[j]+M*2]++;
		}
		for(int j=i+1;j<=n;j++) cnt[a[j]+M*2]=0;
	}
	for(int len=3;len<=n;len++) {
		for(int i=1;i+len-1<=n;i++) {
			int j=i+len-1;
			f[i][j]+=f[i+1][j]+f[i][j-1]-f[i+1][j-1];
		}
	}
	while(q--) {
		int a=read(), b=read();
		printf("%lld\n", f[a][b]);
	}
}
```


---

## 作者：Leap_Frog (赞：10)

### P.S.
提供一个其他题解没有的做法。  
感谢 @[\_DXL\_](https://www.luogu.com.cn/user/98618 "巨佬") 提供此题的思路。  
题目还善意地提醒了我们没有低于 $O(n^2)$ 的做法，真是凉心出题人（
### Description.
给定一个长度为 $N$ 序列 $\{a_k\}$，有 $Q$ 次询问。  
每次询问查询 $[L,R]$ 求有多少个无序三元组 $L\le i,j,k\le R$，满足 $a_i+a_j+a_k=0$。  
（ $i,j,k$ 互不相同
### Solution.
首先，我们考虑一个弱化版：求无序二元组 $1\le i,j\le n$ 满足 $a_i+a_j=0$。  
~~水死了，但是再水也得讲啊。。。~~  
首先，因为它是无序二元组，所以我们钦定 $i<j$，上面的式子可以化成 $a_j=-a_i$。  
所以我们遍历一遍所有数，每次查询之前有多少个数是当前这个数的相反数。  
具体实现可以直接开桶，注意因为有负数必须要值域平移。  
![](https://cdn.luogu.com.cn/upload/image_hosting/iy59r7tg.png "ZK AK IOI!")  

然后，我们来考虑原题。  
初题人善意地提醒了我们没有 $O(n^2)$ 以下的做法。  
说明正解应该是 $O(n^2)$ 的预处理，以及 $O(1)$ 的回答。  
同时，我们也可以钦定三元组 $i,j,k$ 中，$i<j<k$。  
我们思考如何把这题转化成为上面的弱化版，@[\_DXL\_](https://www.luogu.com.cn/user/98618 "巨佬") 此时提供了思路。  
我们考虑把上面的式子转化成为 $(a_j+\frac{a_i}{2})+(a_k+\frac{a_i}{2})=0$  
然后我们固定 $i$ ，直接枚举所有的 $i<j,k$，对它作弱化版。  
因为最后答案并没有固定 $i$，所以我们需要再对区间的左端点进行前缀和。  
同时，因为上面的 $\frac{a_i}{2}$ 并不一定是整数，所以我们需要对所有 $a_i$ 翻倍，这样显然是对的。  
然后这题就做完了，完结撒花，具体见代码。  
### Code.
![](https://cdn.luogu.com.cn/upload/image_hosting/zv5a3lzf.png "ZK txdy yyds")

---

## 作者：gznpp (赞：7)

### 题意简述：

在一个长为 $N\ (5000)$ 的序列上有 $Q\ (10^5)$ 次询问，每次询问 区间上有多少个三元下标集 满足 对应的数之和为 $0$。

----------------

题目里已经说了，"3sum" 问题没有复杂度小于 $O(N^2)$ 的算法，所以本题应该是 $O(N^2)$ 级别预处理之后 $O(1)$ 回答每个询问。

这里我们采用 $O(N^2 \log N)$ 预处理。

首先求出一个区间 $(i, j)\ (j \ge i + 2)$ 内部有多少个下标 $k$ 满足 $a_i + a_ j = -a_k$，令其为 $3sum_{i, j}$。因为不带修，所以可以直接用一个值域大小的 `vector` 保存每个数位置，查询时在 `vector` 上二分即可。每次查询复杂度 $O(\log N)$。

我们已经求出了两端处 $3sum$ 数组，容易想到区间 $[i, j]$ 的最终答案就是
$$
\sum_{u = i}^{j - 2} \sum_{v = u + 2}^j 3sum_{u, v}
$$

很容易联想到二维前缀和。实际操作时可以把 $j < i + 2$ 时的 $3sum$ 数组全部赋值为 $0$，处理边界时会简单许多。

本题空间限制较严，$3sum$ 数组可以隐去，二维前缀和 dp 时再调用二分函数直接求出对应 $3sum$ 值即可。没必要把最终答案也保存在一个数组里，输出时要现跑一次二维前缀和查询操作。

Code:
```cpp
#include <cstdio>
#include <vector>
#include <algorithm>
#define rg register
#define ll long long

using namespace std;

const int maxn = 5001;
const int maxw = 1000000;
const ll maxwll = 1000000ll;
int n, m, a[maxn];
ll dp[maxn][maxn];
vector<int> b[maxw << 1 | 1];

int getnum(int l, int r, ll numll) { // 二分
	if (numll > maxwll || numll < -maxwll) return 0;
	int num = numll + maxwll;
	int t1 = upper_bound(b[num].begin(), b[num].end(), l - 1) - b[num].begin();
	int t2 = upper_bound(b[num].begin(), b[num].end(), r) - b[num].begin();
	return t2 - t1;
}

signed main() {
	
	scanf("%d %d", &n, &m);
	
	for (rg int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
		b[a[i] + maxw].push_back(i);
	}
	
	for (rg int i = 1; i <= n; ++i)
		for (rg int j = 1; j <= n; ++j) { // 二维前缀和 dp
			dp[i][j] = dp[i - 1][j] + dp[i][j - 1] - dp[i - 1][j - 1];
            if (j >= i + 2) dp[i][j] += (ll)getnum(i + 1, j - 1, -((ll)a[i] + a[j])); // 3sum 数组现制现用
        }
	
	while (m--) {
		int l, r;
		scanf("%d %d", &l, &r);
		printf("%lld\n", dp[r][r] + dp[l - 1][l - 1] - dp[l - 1][r] - dp[r][l - 1]); // 最终答案现查现输出
	}
	
	return 0;
}
```

---

## 作者：一只书虫仔 (赞：3)

#### Description

> （3SUM 问题的 $\mathcal O(n^2)$ 解法）给定一个序列 $s_i$，给定 $Q$ 组询问 $l,r$，求 $s_{[l,r]}$ 中有多少个三元组 $(i,j,k)$ 使得 $s_i+s_j+s_k=0$。

#### Solution

首先考虑普通序列的 3SUM 问题如何求解，设 $f_{i,j}$ 为满足要求的三元组 $(i,j,k)$ 的数量，其中 $k \in (i,j)$，我们可以考虑开一个桶 $x_i$，从 $1$ 到 $n$ 枚举 $i$，然后从 $i+1$ 到 $n$ 枚举 $j$，将 $s_i+s_j+s_k=0$ 变形为 $s_k=-s_i-s_j$ 后，我们就可以统计 $[i,j]$ 中有多少个 $-s_i-s_j$ 即可，即 $f_{i,j}=x_{-s_i-s_j}$，然后让 $x_{a_j}\leftarrow x_{a_j}+1$ 即可。

但问题是我们是有 $Q$ 组询问，因此我们可以预处理出答案，利用容斥原理，定义 $g_{i,j}$ 为询问为 $i,j$ 时的答案，有：

$$g_{i,j}=g_{i+1,j}+g_{i,j-1}-g_{i+1,j-1}+f_{i,j}$$

随后对于每一组询问输出 $g_{l,r}$ 即可。

但是上面的方法有两个小细节有点问题：

- $s_i$ 的值域为 $[-10^6,10^6]$，下标不能为负数：平移，加一个 $10^6$ 即可。
- 新开一个数组可能会 MLE：将 $g$ 数组和 $f$ 数组合并，即将上面的式子改成：

$$f_{i,j} =f_{i,j}+f_{i+1,j}+f_{i,j-1}-f_{i+1,j-1}$$

#### Code

因为有些细节需要注意，故本文放出完整代码：

```cpp
#include <bits/stdc++.h>

using namespace std;

int n, q;
int a[5005];
long long dp[5005][5005];
long long cnt[4000005];

int main () {
//	freopen("P6006_2.in", "r", stdin);
//	freopen("P6006ans.out", "w", stdout);
	scanf("%d%d", &n, &q);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for (int i = 1; i <= n; i++) {
		for (int j = i + 1; j <= n; j++) {
			if (0 <= 1000000 - a[i] - a[j] && 1000000 - a[i] - a[j] <= 2000000) dp[i][j] = cnt[1000000 - a[i] - a[j]];
			cnt[a[j] + 1000000]++;
		}
		for (int j = i + 1; j <= n; j++) cnt[a[j] + 1000000] = 0;
	}
	for (int len = 3; len <= n; len++)
		for (int i = 1; i + len - 1 <= n; i++) {
			int j = i + len - 1;
			dp[i][j] += (dp[i + 1][j] + dp[i][j - 1] - dp[i + 1][j - 1]);
		}
	while (q--) {
		int l, r;
		scanf("%d%d", &l, &r);
		printf("%lld\n", dp[l][r]);
	}
	return 0;
}
```

---

## 作者：Vanilla_chan (赞：2)

## Problem

什么是3-SUM？

> 给你一个序列$a$，求有多少组$(i,j,k)(1\le i<j<k\le n)$满足$a_i+a_j+a_k=0$.

这是一个有名的算法问题，尚未发现比运行速度比平方时间明显更优的解法。

这道题给你一个长度为$n(n\le5000)$的序列，之后有$q(q\le10^6)$个询问，查询你区间$[l,r]$的3-SUM的答案。

## Solution

当你看到题目描述的时候，可能会想那位Farmer John的重大突破是啥。但是你只要知道怎么$O(n^2)$，再想想这个$O(n^2)$能不能预处理，然后用更低的时间复杂度查询就好。（别以为真的有啥接近线性的算法）

首先怎么$O(n^2)$做呢？

枚举两个变量，对当前的第三个变量的能取的范围预先开好一个桶计数。这样我们就固定了两个变量$i,j$，去桶里面找$-a_i-a_j$的数量即可。

如果你是枚举$i,j$，对k的取值范围$[j+1,n]$开桶的话，当然也可以但是这个k的限制并不显然（或者是也有向下做的方法只是我没有想到吧）

如果我们枚举$i,k$，这样$k$的取值范围就是$[i+1,k-1]$。记$c_x$表示在当前区间内，等于$x$的$a_k$的数量；设$f_{i,k}$表示选定左端点为$i$，右端点为$k$时的3-SUM方案数。

```c++
for(int i=1;i<=n;i++)
{
	c[a[i+1]+M]++;
	for(int k=i+2;k<=n;k++)
	{
		if(a[i]+a[k]<=M&&a[i]+a[k]>=-M) f[i][k]+=c[M-a[i]-a[k]];
		c[a[k]+M]++;
	}
	c[a[i+1]+M]--;
	for(int k=i+2;k<=n;k++)
	{
		c[a[k]+M]--;//clear
	}
}
```

*代码中的c是桶，M可以先不管（见下文）*

对于一个询问$(l,r)$，这里的$i,k$当然可以选$[l,r]$中的任意值（只要满足$i<k$）。这不就是求
$$
\sum_{i=l}^r\sum_{k=i+1}^r f_{i,k}
$$
这部分可以用二维前缀和预处理出来。

这样对于每一个询问都可以$O(1)$回答了。

### 需要注意的地方

不需要在求二维前缀和的时候判断$i<k$（准确说是$i<\dots<k\Rightarrow i+1<k$），因为不合法部分的$f_{i,k}$依然是$0$.

即直接预处理
$$
sum_{l,r}=\sum_{i=l}^r\sum_{k=l}^r f_{i,k}
$$
对于每个询问用二维前缀和的差分
$$
ans_{l,r}=sum_{r,r}-sum_{r,l-1}-sum_{l-1,r}+sum_{l-1,l-1}
$$
就好了。

以及**注意值域有负数，所以桶的大小要开两倍并且给所有的数都加上一个$10^6$**。

## Code

```c++
/**************************************************************
 * Problem: 6006
 * Author: Vanilla_chan
 * Date: 20210307
**************************************************************/
//快读等已略
#define N 6010
int n,q;
int a[N];
LL f[N][N];
int c[2000010];
#define M 1000000
int main()
{
	n=read();
	q=read();
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1;i<=n;i++)
	{
		c[a[i+1]+M]++;
		for(int k=i+2;k<=n;k++)
		{
			if(a[i]+a[k]<=M&&a[i]+a[k]>=-M) f[i][k]+=c[M-a[i]-a[k]];
			c[a[k]+M]++;
		}
		c[a[i+1]+M]--;
		for(int k=i+2;k<=n;k++)
		{
			c[a[k]+M]--;
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			f[i][j]+=f[i-1][j]+f[i][j-1]-f[i-1][j-1];
		}
	}
	int x,y;
	while(q--)
	{
		x=read();
		y=read();
		if(x>y) swap(x,y);
		write(f[y][y]-f[x-1][y]-f[y][x-1]+f[x-1][x-1]);
	}
	return 0;
}
```

## 说在后面

若有任何问题，恳请管理员斧正，感激不尽！

---

## 作者：似镜流年 (赞：2)

## 第一想法
$\qquad$首先考虑暴力枚举，设$f[i][j]$表示以第$i$个数为三元组的第一个数，以第$j$个数表示三元组的最后一个数.那么每次只要重新从$i+1$开始统计每个数的个数，代入求出答案即可.

$\qquad$然后我们再让$f[i][j]+=f[i][j-1]$，操作完后$f[i][j]$就表示为以第$i$个数为三元组的第一个数，以第 $i$ 到第  $j$ 个数表示三元组的最后一个数的三元组总数.

$\qquad$然后我们再让$f[i][j]+=f[i+1][j]$，操作完后$f[i][j]$就表示第$i$个数到第$j$个数的所有三元组的个数,即为题目所求，然后就可以$O(1)$输出询问了。

$\qquad$预计至少有25分，但是它完美的只过了三个点
## 第二想法
$\qquad$后面$f$数组显然无法优化，所以只能考虑统计的优化,详见代码.

## 代码
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int p=2000005;
int n,q;
ll f[5005][5005];//不开ll可能会炸
int h[5000005],a[5005];
inline int read(){
	register int f=1,x=0;
	register char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=(x<<3)+(x<<1)+(ch^48);
		ch=getchar();
	}
	return f*x;
}
int main () {
	n=read(),q=read();
	for(register int i=1; i<=n; i++)a[i]=read();
	h[a[1]+p]++;
	h[a[2]+p]++;//第一个和第二个数预先加入
	for(register int i=1; i<=n-2; i++) {
		f[i][i]=f[i][i+1]=0;
		h[a[i]+p]--;//删掉第i个数的数据
		if(i&1)for(register int j=i+2; j<=n; j++) {
				f[i][j]=h[p-a[i]-a[j]];
				h[a[j]+p]++;//先计算完个数后，再把数字的统计加进去.
			}//顺着用
		else {
			for(register int j=n; j>=i+2; j--) {
				h[a[j]+p]--;
				f[i][j]=h[p-a[i]-a[j]];//先减完再计算
			}//逆着用
			h[a[i+2]+p]++;//想一下为什么要+1,不加会WA.
		}
	}//通过来回利用来减少修改的次数，省去了清空的复杂度
	for(register int i=1; i<=n; i++) {
		for(register int j=i+1; j<=n; j++) {
			f[i][j]+=f[i][j-1];
		}
	}
	for(register int j=1; j<=n; j++) {
		for(register int i=j-1; i; i--)f[i][j]+=f[i+1][j];
	}
	register int x,y;
	for(int i=1; i<=q; i++) {
		x=read(),y=read();
		printf("%lld\n",f[x][y]);
	}
	return 0;
}
```



---

## 作者：BF_AlphaShoot (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P6006)。

善良的出题人已经在题面中告诉你了：

> 尚未发现运行速度比平方时间明显更优的解法。

而 $O(qn^2)$ 过不了，所以题目显然是让你以 $O(n^2)$ 进行预处理，再进行 $O(1)$ 查询。

思考在暴力 $O(n^3)$ 处理时，我们是以三元组 $(i,j,k)$ 进行三重循环，逐个检查是否 $s_i+s_j+s_k=0$。不妨对这个式子进行变换，可得 $s_k=-s_i-s_j$。这时利用**桶**统计 $[i,j]$ 中的 $-s_i-s_j$ 数量即可。

在面对 $q$ 次询问时，考虑 用 $v_{i,j}$ 表示区间 $[i,j]$ 中的结果。则有 $v_{i+1,j}$ 为区间 $(i,j]$ 中的结果， $v_{i,j-1}$ 为区间 $[i,j)$ 中的结果， $v_{i+1,j-1}$ 为区间 $(i,j)$ 中的结果。易得：
$$
v_{i,j}=v_{i+1,j}+v_{i,j−1}−v_{i+1,j−1}+f_{i,j}
$$
可惜的是这会导致你 **MLE**。应该把数组 $v$ 去掉，因为 $f$ 就可以了：
$$
f_{i,j}=f_{i+1,j}+f_{i,j−1}−f_{i+1,j−1}
$$
本题代码**细节**较恶心，~~故意跟数组过不去~~，应格外注意：

1. 查找 $-s_i-s_j$ 时要加上常数 $M$，因为数组不能访问负的，会**数组越界**。

2. $M$应该在 $10^6$ 以上，这是由于你后面要 $-s_i-s_j$，开的过小容易加后还是负数。
3. 桶应该开为 $2\times M$，如果较小可能会因为 $+M$ 而**数组越界**。

View code：

```cpp
#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define ri register int
#define il inline

const int N=5010,M=2e6+10;
int n,Q;
int s[N],b[M<<1];
ll f[N][N];

il ll read(){
    ll x=0,y=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
            y=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=x*10+c-'0';
        c=getchar();
    }
    return x*y;
}

il void work(){
	for(ri i=1;i<=n;i++){
		for(ri j=i+1;j<=n;j++){
			f[i][j]=b[M-s[i]-s[j]];
			b[s[j]+M]++;
		}
		for(ri j=i+1;j<=n;j++)
			b[s[j]+M]=0;
	}
	for(ri i=3;i<=n;i++){
		for(ri j=1;j<=n-i+1;j++){
			int k=i+j-1;
			f[j][k]+=f[j+1][k]+f[j][k-1]-f[j+1][k-1];
		}
	}
}

signed main(){
	n=read(),Q=read();
    for(ri i=1;i<=n;i++)
		s[i]=read();
	work();
	while(Q--){
		int a=read(),b=read();
		printf("%lld\n",f[a][b]);
	}
    return 0;
}
```

---

## 作者：pldzy (赞：1)

##### 区间内三元组个数（满足 $ai + aj + ak = 0$）

 ~~（GZEZ 新初一第一次测试 第四题）~~

在指定范围 $[l, r]$ 内，求满足 $ai + aj + ak = 0$ 的三元组的个数。


------------


## 思路：
先预处理，时间复杂度是 $O(n^2)$ ; 再查询，时间复杂度是 $O(1)$ 。

### 预处理：

1. 在确定了两端的数之后，中间的数 $= -a[i]-a[j]$,同时用桶去统计各个数的数量，即 $dp[i][j] = cnt[m - a[i] - a[j]]$ （$dp$ 用来记录符合题目条件于 $i$ 到 $j$ 的三元组的个数； $cnt$ 用作桶，统计各个数出现的次数）。

1. 记得在第二层循坏外把 $cnt$ 使用过的部分清空。

1. 之前的 $dp[i][j]$ 统计的是以 $i$ 为首， $j$为末所包含的三元组，若想得到于 $[i,j]$ 内所有的三元组，用一下一维差分即可，即：

	$dp[i][j] += (dp[i + 1][j] + dp[i][j - 1] - dp[i + 1][j - 1])$
    
###  查询：
 
 直接输入 $l,r$ ，输出 $dp[l][r]$ 即可。
 

------------

$Code$
```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long 
int n, q;
const int m = 1000000;
const int maxn = 5005;
int a[maxn];
int dp[maxn][maxn];
int cnt[4000005];

signed main ()
{
	scanf ("%lld %lld", &n, &q);
	for (int i = 1; i <= n; i++)
	{
		scanf ("%lld", &a[i]);
	} 
	for (int i = 1; i <= n; i++)
	{
		for (int j = i + 1; j <= n; j++)
		{
			if (0 <= m - a[j] - a[i] and m - a[i] - a[j] <= 2 * m) dp[i][j] = cnt[m - a[i] - a[j]];
			cnt[a[j] + m]++;
		}
		for (int j = i + 1; j <= n; j++) cnt[a[j] + m]--;
	}
	for (int len = 3; len <= n; len++)
	for (int i = 1; i + len - 1 <= n; i++)
	{
		int j = i + len - 1;
		dp[i][j] += (dp[i + 1][j] + dp[i][j - 1] - dp[i + 1][j - 1]);
	}
	while (q--)
	{
		int l, r;
		scanf ("%lld %lld", &l, &r);
		printf ("%lld\n", dp[l][r]);
	}
	return 0;
}
```
若有排版等错误 烦请管理员斧正 感激不尽！！


---

