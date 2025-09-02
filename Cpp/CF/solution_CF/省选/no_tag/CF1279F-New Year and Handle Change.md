# New Year and Handle Change

## 题目描述

New Year is getting near. So it's time to change handles on codeforces. Mishka wants to change his handle but in such a way that people would not forget who he is.

To make it work, he only allowed to change letters case. More formally, during one handle change he can choose any segment of his handle $ [i; i + l - 1] $ and apply tolower or toupper to all letters of his handle on this segment (more fomally, replace all uppercase letters with corresponding lowercase or vice versa). The length $ l $ is fixed for all changes.

Because it is not allowed to change codeforces handle too often, Mishka can perform at most $ k $ such operations. What is the minimum value of $ min(lower, upper) $ (where $ lower $ is the number of lowercase letters, and $ upper $ is the number of uppercase letters) can be obtained after optimal sequence of changes?

## 样例 #1

### 输入

```
7 1 4
PikMike
```

### 输出

```
0
```

## 样例 #2

### 输入

```
15 2 2
AaAaAAaaAAAAaaA
```

### 输出

```
2
```

## 样例 #3

### 输入

```
14 2 6
aBcdEFGHIJklMn
```

### 输出

```
0
```

## 样例 #4

### 输入

```
9 2 2
aAaAAAaaA
```

### 输出

```
1
```

# 题解

## 作者：aaaaaaaawsl (赞：4)

困了我一下午加晚上的 wqs 二分终于差不多弄懂了，找的很多博客和题解都或多或少没有详细的讲 wqs 二分，那么下面我详细的讲讲我关于wqs 二分的各种疑惑和理解。

简化题意和一些小转化看其他题解就行，不是这篇题解的重点。

--------

### wqs 二分在哪里可以应用

wqs 二分常常应用于带有某些特征动态规划问题的优化方面。该类可以使用 wqs 二分优化的问题常常形如 **给定若干个物品，要求恰好进行 $m$ 次操作，最大化或最小化操作后的价值（根据题目计算）。** 在此的操作可以为选取，或变换等等，但是我们总归可以把他转化为背包问题。

特征为：

1.**一般来说**，随着操作次数的增加，价值是单调变化的。比如此题，随着操作的增加，答案是单调下降的。

2.如果不限制选的个数，那么很容易求出最优方案。

此外，全面的来说，如果把操作次数（$x$）和在此操作次数下的**最优**价值（$g(x)$）以函数形式表示，如果该函数是个凸函数，那么可以使用。

-------------

### wqs 二分的思想及实现

[~~偷几张图。~~](https://blog.csdn.net/Emm_Titan/article/details/124035796)

假设操作次数与价值形成了这样的函数图像：

![](https://cdn.luogu.com.cn/upload/image_hosting/cq56swsx.png)

这里要明确现在：

- 知道每个点的横坐标（$1 ,2,3,4 ……$）。

- 知道这个函数图像的斜率是单调变化的（这个要之前推，推出来才能用 wqs 二分）。

- $y$ 定义成了操作次数为 $x$ 时的最优值。

现在不知道：

- 每个点的实际的 $y$ 值。

现在观察到：

- 当确定了一条直线的斜率，这条直线一定与图像相切在某个点上。

![](https://cdn.luogu.com.cn/upload/image_hosting/avigwupo.png)

- 由于图像的斜率是单调的，如果可以求出某一个给定的斜率切这个图像与哪个点上，就可以二分斜率，使其切在目标点上。此时的 $y$ 值就是答案。
 
```
while(l <= r){
	int mid = (l + r) >> 1;
	if(check(mid) <= m) l = mid + 1, p = mid;
	else r = mid - 1;
}//mid为二分的斜率。

```

所以目标变成了：

- 对于一个斜率，得到它与图像相切点的 $x$ 值。

- 对于 $x$ 值，得到 $y$ 值。

接下来，可以做到：

- 可以预处理不操作（$x=0$）的情况（$y$）。

- 得到一个规律，对于一个给定斜率的直线，在它过图上每一个点的情况下，过切点的情况的截距最大，比如下图。

![](https://cdn.luogu.com.cn/upload/image_hosting/qhu2jj9y.png)

接下来考虑怎么求出该直线的切点的横坐标。

现在有 $x=0$ 时的 $y$ 坐标，看第三个图，由于横坐标之间是彼此相差 $1$，现在二分出的斜率为 $mid$，所以当直线交在某个点上时，它与 $y$ 轴的截距 $b = y - mid x$ 。比 $x-1$ 时的截距小 $mid$。

于是可以通过一个 $O(n)$ 的 DP 来维护 **考虑到第 $i$ 个决策位置的时候，最优操作方案的操作次数和直线的截距**。

注意这里不能用上图来协助思考，因为上图的图形是 **考虑完 $n$ 个决策位置的，对于不同操作数的最优解组成的图形**。与 DP 中的前后决策位置和操作数转移完全没关系。

那么在 DP 中，对 $f_i$ 维护两个值 $f,s$ 表示：

当前处理到了第 $i$ 位，得到一个点 $(f_i.s, j),f_i.s$ 为当前最优方案的操作数，$j$ 为最优方案的值（不记录，使用 $f_i.f$进行转移可以保证正确性，最后可以通过斜率，横坐标和截距计算出来），斜率为 $mid$ 的直线过这个点的截距为 $f_i.f$。

```
int check(int mid){
	for(int i = 1; i <= n; ++ i){
		pair<int, int> tmp = f[i - 1];
		tmp.first += a[i], f[i] = tmp;
		tmp = f[max(i - len, 0)];
		tmp.first -= mid; tmp.second ++;
		f[i] = min(f[i], tmp);
	}
	return f[n].second;
}
```
最后返回的值即为切点的横坐标。

以返回的值与给定的操作数的大小关系维护二分，即可得出切图像与给定点的切线的截距，斜率。结合横坐标可以求出答案。

----------------

### Code

```
// 由于是借助第一篇题解和其他博客进行的学习，代码确实很相似，但是懒得改了。
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;

inline int read(){
	register int x = 0, f = 1; register char ch = getchar();
	for(; ch > '9' || ch < '0'; ch = getchar()) if(ch == '-') f = -1;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return x * f; 
}

const int N = 1e6 + 10;

int a[N];
char s[N];
int n, m, len, ans = 2147483647;
pair<int,int> f[N];

int check(int mid){
	for(int i = 1; i <= n; ++ i){
		pair<int, int> tmp = f[i - 1];
		tmp.first += a[i], f[i] = tmp;
		tmp = f[max(i - len, 0)];
		tmp.first -= mid; tmp.second ++;
		f[i] = min(f[i], tmp);
	}
	return f[n].second;
}

void solve(){
	int l = -n, r = 0, p;
	while(l <= r){
		int mid = (l + r) >> 1;
		if(check(mid) <= m) l = mid + 1, p = mid;
		else r = mid - 1;
	}
	check(p);
	ans = min(ans, f[n].first + p * m);
}

int main(){
	n = read(); m = read(); len = read(); cin >> (s + 1);
	for(int i = 1; i <= n; ++ i) a[i] = (s[i] >= 'a' && s[i] <= 'z'); solve();
	for(int i = 1; i <= n; ++ i) a[i] ^= 1; solve();
	printf("%d\n", ans);
	return 0;
}

```

---

## 作者：似嫩 (赞：3)

## 题意简化

- 给你一个字符串，长度为 $n$，区分大小写，也可看成零一串。
- 每次操作把 $[i,i+len-1]$ 的**所有字符**变成大写或小写（$0$ 或 $1$），最多可以进行 $k$ 次操作。
- 你需要最小化大小写字母个数的最小值（或 $0$，$1$ 个数的最小值）。
- $n,len\le 10^6$

## 分析


显然，我们可以分别最小化小写字母个数，最小化大写字母个数，两者取 $\min$。


设 $s$ 为这个字符串。如果 $s_i$ 为小写字母，将 $a_i$ 记作 $1$，是大写字母记作 $0$，那么最小化小母字母的个数，即为求 $\sum{a_i}$ 的最小值。最小化大母字母同理，想到可能是**动规**。

注意到 $n$ 的范围是 $10^6$，正常的动规过不去。 

朴素的算法可以参考官方题解的第三段文字，复杂度是 $O(nk)$，过不了。
### [官方题解](https://codeforces.com/blog/entry/72577)

这里讲正解，我们考虑**二分+动规**。

摆在我们面前的有两个问题：

- 二分枚举什么？如何判断可行？正确性？
- $dp_i$ 表示什么？ $dp_i$ 如何转移？

我们发现每一次操作的长度为 $len$，那么每次**最多**将小写或大写字母的个数减少 $len$ 个，**最少**一个都没变。（为了和二分的 $l$ 区分，这里用了 $len$，而不是 $l$，注意。）

那么对于小写的情况，我们就可以二分枚举每次操作将小写字母数量**最少减少**了 $mid$。$dp_i$ 表示经历了若干次操作，当前点为 $i$ 时，在每次操作最少减少 $mid$ 个小写字母之外，**额外减少**的个数（就是还多删了几个）。我们可以判断在当前情况下，所需要的操作次数是否小于等于 $k$。这样我们就能找到最小的 $mid$。大写字母的情况相同。

二分具体说是这样：
```cpp
    l = 0, r = len;
    while(l < r){
		int mid = l + r >> 1;
		if(check(mid, 0) <= k)//判断是否满足操作次数小于等于k。
			r = mid;
		else
			l = mid + 1;
    }
    check(l, 1);//表示找到了一个最优解,记录答案。
```
关于二分的正确性，如果我们找到一个满足的值 $mid$,它需要的操作次数不大于 $k$,那么就继续寻找最小的 $mid$ 值。

关于 $dp_i$ 的转移：
$$dp_i = \begin{cases}
	\max(dp_{i-1},sum_i-mid)  &\text i<len\\
	\max(dp_{i-1},dp_{i-len}+sum_i-sum_{i-len}-mid) &\text i\geq len 
		   \end{cases}$$
其中 $sum_i$ 为 $a_i$ 的前缀和，对大小写分别计算，$mid$ 为每次操作最少减少的小写字母数量。

- 第一个式子中， 因为 $i<len$,那么它不可能是从第一个数之前开始操作的，既它操作的左起点一定小于 $1$。它只可能不操作或以 $1$ 为左起点来操作所以它不是终点。$sum_i-mid$ 即为在 $[1,i]$ 中多删的个数。

- 第二个式子中，它仍能不操作或在一个操作之间，或者作为一个操作的**终点**。于是这个操作是从 $i-len+1$ 开始的。那么 $sum_i-sum_{i-len}$ 即为在 $[i-len+1,i]$ 中 $1$ 的个数，减去 $mid$，即为这次操作中多去掉的数。它从 $i-len+1$ 上来，就加上 $dp_{i-len}$，于是就有了上述的转移（注意是 $dp_{i-len}$ 哦）。

我们还需要一个数组 $ans_i$ 来记录当前在第 $i$ 位时，每次操作最小减少 $mid$ 个数，**最少需要几次操作**。
$$ans_i = \begin{cases}
	ans_{i-1}  &\text x<dp_{i-1}\\
	ans_{i-len}+1  &\text x>dp_{i-1} \\
   \min(ans_{i-1},ans_{i-len}+1)  &\text x=dp_{i-1} 
		   \end{cases}$$
$$x = \begin{cases}
	sum_i-mid  &\text i<len\\
	dp_{i-len}+sum_i-sum_{i-len}-mid &\text i\geq len 
		   \end{cases}$$          
$x$ 其实就是上面求 $dp_i$ 中，$\max$ 的右边部分。

不难明白：
- 如果当前多删除的个数比前一个要多，那么肯定以 $i-len+1$ 处进行一次操作更好。
- 如果比之前小，则不用进行操作，因为还不如之前的。
- 如果等于，则取前一个和第 $i-len+1$ 个的最小值（但是算的时候是在 $i-len$ 的）。

那么我们的答案即为：
$$\min(sum_n-dp_n-k\times mid,sum_n-dp_n-k\times mid)$$
上式左右分别是小写和大写的情况。

因为在条件允许的情况下，操作次数肯定越多越好，所以是 $k\times mid$。

到这分析完毕。二分复杂度为 $O(\log n)$, 维护 $dp_i$ 和 $ans_i$ 的复杂度为 $O(n)$。总复杂度为 $O(n\log n)$。

## 总结

思路为二分+动规，关键点在于**二分的条件和状态转移**。

~~又要贴码子了。~~
```cpp
#include <bits/stdc++.h>

using namespace std;
const int N = 1e6 + 5;
string s;
int ans[N], a[N], dp[N], sum[N];
//ans记录当前最小操作次数，sum为前缀和，a表示01串。
int n, k, len, answer = 2100000000;

int check(int mid, int op){//op是判断是否要记录答案
	int x;
	for (int i = 1; i <= n; i ++){
		if (i - len < 0) x =  sum[i] - mid;//其实小于等于0也行。
		else x = dp[i - len] - sum[i - len] + sum[i] - mid;
		dp[i] = max(dp[i - 1], x);//统计个数 
		if (dp[i - 1] > x) ans[i] = ans[i - 1];
		if (dp[i - 1] < x) ans[i] = ans[i - len] + 1;
		if (dp[i - 1] == x) ans[i] = min(ans[i - 1], ans[i - len] + 1);
        //计算最小的操作次数。
	}
	if (op) answer = min(answer, sum[n] - dp[n] - k * mid);//统计最小值。
	return ans[n];//返回最少需要操作次数。 
} 
int main(){
	n = read(), k = read(), len = read();
	cin>>s;
	//小写部分
	for (int i = 1; i <= n; i ++){
		a[i] = islower(s[i - 1]) > 0;//判断是小写字母。
		sum[i] = sum[i - 1] + a[i];
	}
	int l = 0, r = len;
	while (l < r){ 
		int mid = l + r >> 1;
		if (check(mid, 0) <= k) r = mid;
		else l = mid + 1; 
	} 
	check(l, 1);//找到最优解后，这是最后一次运行，统计答案。 
	//大写部分 
	for (int i = 1; i <= n; i ++){
		a[i] = isupper(s[i - 1]) > 0;//判断是大写字母。
		sum[i] = sum[i - 1] + a[i];
	}
	l = 0, r = len;
	while (l < r){
		int mid = l + r >> 1;
		if (check(mid, 0) <= k) r = mid;
		else l = mid + 1; 
	} 
	check(l, 1);//同理。
	printf("%d", answer);
	return 0; 
}
```

---

## 作者：18Michael (赞：2)

来翻译一下 [cf 评论区一老哥的证明](https://codeforces.com/blog/entry/72577?#comment-568669)。

首先问题可以转化为选出 $k$ 个长为 $l$ 的区间使得覆盖的 $1$ 个数最多。

不妨设 $kl\le n$，设选 $k$ 个区间最多能覆盖 $f_k$ 个 $1$，显然存在一种最优方案使得区间两两不交。


下面证明 $f_{k+1}\ge \frac{f_{k}+f_{k+2}}{2}$，即 $f$ 具有凸性。

分别找到 $k$ 时和 $k+2$ 时的一组最优解：

![](https://codeforces.com/predownloaded/e3/e2/e3e237195ee0a82e3a6005e31792d665b6cdf2f1.png)

把相交的区间对应连边，如图：

![](https://codeforces.com/predownloaded/4f/b1/4fb13d8b01fe250190335b3db937c0826a90deb4.png)

形成了若干连通块，每个连通块内 $k$ 和 $k+2$ 的区间数之差不超过 $1$，因此必然有一个连通块在 $k+2$ 中的区间数比在 $k$ 中的区间数多 $1$，翻转这个连通块：

![](https://codeforces.com/predownloaded/be/2c/be2cc9b1d0ac4da0419e24f2974c4a4d011fc609.png)

于是得到了两种 $k+1$ 时的方案，取更优的那组即可，得证。

证明了凸性后就是 wqs 二分的板子题了，时间复杂度 $O(n\log n)$。

## Code

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
int n,l,L,R,mid,t;
LL m,ans;
int a[1000002];
LL f[1000002],g[1000002];
char ch[1000002];
template<class T>void read(T &x)
{
	x=0;int f=0;char ch=getchar();
	while(ch<'0' || ch>'9')f|=(ch=='-'),ch=getchar();
	while(ch>='0' && ch<='9')x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	x=f? -x:x;return ;
}
inline bool check(int o)
{
	t=0;
	for(int i=0;i<l;++i)f[i]=g[i]=0;
	for(int i=l;i<=n;++i)
	{
		if(f[i-l]<f[t] || (f[i-l]==f[t] && (o? g[i-l]>g[t]:g[i-l]<g[t])))t=i-l;
		f[i]=f[t]+a[i-l]+mid,g[i]=g[t]+1;
		if(f[i-1]+a[i]<f[i] || (f[i-1]+a[i]==f[i] && (o? g[i-1]>g[i]:g[i-1]<g[i])))f[i]=f[i-1]+a[i],g[i]=g[i-1];
		f[i]-=a[i];
	}
	if(o || g[n]<=m)ans=min(ans,f[n]+a[n]-min(g[n],m)*mid);
	return g[n]<=m;
}
inline void solve(int c)
{
	for(int i=1;i<=n;++i)a[i]=a[i-1]+(ch[i]!=c);
	for(L=0,R=n;L<=R;)
	{
		mid=((L+R)>>1);
		if(check(0))R=mid-1;
		else L=mid+1;
	}
	mid=L,check(1);
}
int main()
{
	read(n),read(m),read(l);
	if(1LL*m*l>=n)return 0&puts("0");
	scanf("%s",ch+1),ans=n;
	for(int i=1;i<=n;++i)ch[i]=(ch[i]<='Z');
	solve(0),solve(1);
	return 0&printf("%lld",ans);
}
```

---

## 作者：Dzhao (赞：2)

wqs 二分模板题。

我们可以将大小写分开做，分别求小写时的 min 和大写时的 min。

首先可以发现我们肯定是操作越多次越好，所以我们可以假设正好操作 $k$ 次。设 $f(x)$ 为操作 $x$ 次时的最优答案，我们可以发现 $(x, f(x))$ 构成的函数图像是个下凸壳：

![](https://cdn.luogu.com.cn/upload/image_hosting/68uqxqwk.png)

证明：首先 $f(x)$ 肯定是单减的，然后因为你每次操作肯定选最优的操作所以 $f(x)$ 减小的趋势肯定是越来越小的。

然后就是 wqs 二分，我们二分与 $(k, f(k))$ 相切的直线的斜率 $mid$，然后问题就转化为求出这条直线的截距，相当于每次操作每次操作多一个 $-mid$ 的价值，直接 dp 即可，$dp_i$ 表示 $1...i$ 的最优答案。转移是简单的，需注意转移时还需要记录一个当前 $dp_i$ 操作了多少次。

我们求出了截距直接根据斜率即可推出 $f(k)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
using ll = long long;
const int N = 1e6 + 5;
int n, m, len, a[N], ans = 1e9;
char s[N];
pair <int, int> dp[N];
int check(int mid) {
	for (int i = 1; i <= n; i++) {
		pair <int, int> tmp = dp[i - 1];
		tmp.fi += a[i], dp[i] = tmp;
		tmp = dp[max(i - len, 0)];
		tmp.fi -= mid, tmp.se++;
		dp[i] = min(dp[i], tmp);
	}
	return dp[n].se;
}
void solve() {
	int l = -n, r = 0, p;
	while (l <= r) {
		int mid = l + r >> 1;
		if (check(mid) <= m) l = mid + 1, p = mid;
		else r = mid - 1; 
	}
	check(p);
	ans = min(ans, dp[n].fi + p * m);
}

int main() {
	scanf("%d%d%d%s", &n, &m, &len, s + 1);
	for (int i = 1; i <= n; i++) a[i] = s[i] >= 'a' && s[i] <= 'z'; solve();
	for (int i = 1; i <= n; i++) a[i] ^= 1; solve();
	printf("%d\n", ans);
	return 0;
}
```

---

## 作者：hzoi_Shadow (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1279F)

# 前置知识

WQS 二分

# 解法

不妨将大/小写分开做，分别计算大/小写字符的最小值后然后取 $\min$，本质是在取若干个区间令其贡献为 $0$，转移方程比较板。

因具有凸性，故可以使用 WQS 二分求解。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
#define ull unsigned long long
#define sort stable_sort 
#define endl '\n'
const ll inf=1000000000000;
ll a[1000010],b[1000010],f[1000010],g[1000010];
char s[1000010];
bool check(ll n,ll m,ll len,ll mid)
{
    for(ll i=1;i<=n;i++)
    {
        f[i]=f[i-1]+a[i];  g[i]=g[i-1];
        if(i-len>=0)
        {
            if(f[i-len]-mid<f[i])
            {
                f[i]=f[i-len]-mid;  g[i]=g[i-len]+1;
            }
            else  if(f[i-len]-mid==f[i])  g[i]=max(g[i],g[i-len]+1);
        }
    }
    return g[n]>=m;
}
ll solve(ll n,ll m,ll len,ll op)
{
    ll l=-inf,r=inf,ans=0,mid;
    for(ll i=1;i<=n;i++)  a[i]=('a'<=s[i]&&s[i]<='z')^op;
    while(l<=r)
    {
        mid=(l+r)/2;
        if(check(n,m,len,mid)==true)
        {
            ans=mid;
            r=mid-1;
        }
        else  l=mid+1;
    }
    check(n,m,len,ans);
    return f[n]+ans*m;
}
int main()
{
// #define Isaac
#ifdef Isaac
    freopen("in.in","r",stdin);
    freopen("out.out","w",stdout);
#endif
    ll n,m,len;
    cin>>n>>m>>len;  scanf("%s",s+1);
    cout<<((m*len>=n)?0:min(solve(n,m,len,0),solve(n,m,len,1)))<<endl;
    return 0;
}
```

---

