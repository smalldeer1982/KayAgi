# Sleeping Schedule

## 题目描述

Vova有个非常奇怪的睡眠日程表。一天有$h$个小时，Vova将正好睡$n$次觉，从每次刚醒来的那一刻计起，他将在$a_i$小时后睡第$i$次觉。你可以假设Vova在故事开始时是刚醒来的。(初始时间为0)每次Vova正好睡一天(也就是$h$小时)。

如果他在$[l,r]$时间段内开始睡觉，便认为这一次睡眠是优秀的。

Vova可以控制自己，在第$i$次睡眠前，选择在$a_i$或$a_i-1$小时后开始睡觉。

你的任务是计算出优秀睡眠次数的最大值。

## 样例 #1

### 输入

```
7 24 21 23
16 17 14 20 20 11 22```

### 输出

```
3```

# 题解

## 作者：C　C　A (赞：15)

# $CF1324E\ Sleeping\ Schedule's\ Solution$
						
$\qquad\qquad\qquad\qquad\qquad\qquad\qquad\qquad\qquad\qquad\qquad\qquad\qquad\qquad\qquad By$ [$CCA$](https://www.luogu.com.cn/user/78645)

## $Problem$

$\qquad$给定一个数组$a$，可以选择将其中一些减$1$（也可以不减），问前缀和数组对$h$取模后在区间$[L,R]$内的元素最多有多少个。

## $Solution$

$\qquad$这就是个暴力$~~DP~~$递推。

$\qquad$我们考虑令$dp[i][j]$表示在前$i$个数中，所有数之和对$h$取模的值为$j$时，答案最大为多少。

$\qquad$转移很暴力也很显然:

$$dp[i][j] = max(dp[i - 1][(j - a[i] + h) \% h] , dp[i - 1][(j - a[i] + 1 + h) \%h]) + (L<=j\&\&j<=R)$$

$\qquad$没什么细节，就是初始化注意一下，要赋成极小值，因为我们不能从非法条件中更新答案。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 2e3 + 10;

int n , m , L , R , a[N] , dp[N][N];

int Inc(int x){
	return (x + m) % m;
}

int check(int x){
	return L <= x && x <= R;
}

int main(){
	memset(dp , -63 , sizeof(dp)) , dp[0][0] = 0;
	scanf("%d %d %d %d" , &n , &m , &L , &R);
	for(int i = 1; i <= n; i++) scanf("%d" , &a[i]);
	for(int i = 1; i <= n; i++)
		for(int j = 0; j < m; j++){
			dp[i][j] = max(dp[i - 1][Inc(j - a[i])] , dp[i - 1][Inc(j - a[i] + 1)]) + check(j);	
		}
	int Max = 0;
	for(int i = 0; i < m; i++) Max = max(Max , dp[n][i]);
	printf("%d" , Max);
	return 0;
}
```

自认为码风还是比较清奇可看的，大家可以对着$Solution$仔细看一下。

最后，[$This\ is\ my\ blog$](https://www.luogu.com.cn/blog/A66-888/) , 有兴趣的可以逛一下，应该能有所收获。

---

## 作者：Scintilla (赞：4)

[luogu传送门](https://www.luogu.com.cn/problem/CF1324E) & [CF传送门](https://codeforces.com/contest/1324/problem/E)

作为一名 dp 菜鸡，把大量时间花在 F 题上，可惜怎么调也调不出来，于是就回来看 E 题。我在 1h58min 时写完了，测了一波样例，感觉没问题，以为自己能绝杀。可是，神奇的 CF 竟然让我再登录一遍，登录完后还卡，交个题还 502，真是气死人了QAQ

但是能在考场上做出这题，本 dp 菜鸡还是有点小激动，于是写了这篇题解。

### 题意

一天有 $h$ 个小时，初始时你是醒着的，你需要睡 $n$ 觉。第 $i$ 次醒后（包括初始时），你可以选择在 $a_i$ 小时后或 $a_i-1$ 小时候再次睡去。每次睡觉都是正好一天，即 $h$ 小时。如果你在 $[l,r]$ 这段时间内睡下，那么称这段睡眠是“好的”。求最多能有几次“好的” 睡眠。

### 思路

再显然不过的 DP 了。

最初的想法：设 $f[i][j]$ 表示在 $j$ 小时后第 $i$ 次睡下的最大“好”睡眠数。很显然，时空都超了。

因为每次睡觉是正好一天，所以相当于没睡。注意到天数并不重要，于是可以把 $j$ 改成：在 $j$ 点时睡下。这样的话，转移方程就是：
```cpp
f[i][j] = max(f[i - 1][(j - a[i] + h) % h], f[i - 1][(j - a[i] + h + 1) % h]) + (l <= j & j <= r);
```
然后就是转移的时候注意时间。因为 $i < h$ 时，第 $i$ 次睡下的时间最早是第  $sum[i]-i$ 小时，最晚是在第 $sum[i]$ 小时，不能保证每个时间点都能睡下。

嗯... 然后这题就能愉快地 AC 了。

### $Code:$
```
#include <bits/stdc++.h>

using namespace std;

#define il inline
#define re register
#define Rep(i, s, e) for (re int i = s; i <= e; ++i)
#define Dep(i, s, e) for (re int i = s; i >= e; --i)
#define file(a) freopen(#a".in", "r", stdin), freopen(#a".out", "w", stdout)

il int read() {
    int x = 0; bool f = true; char c = getchar();
    while (c < '0' || c > '9') {if (c == '-') f = false; c = getchar();}
    while (c >= '0' && c <= '9') x = (x << 1) + (x << 3) + (c ^ 48), c = getchar();
    return f ? x : -x;
}

int n, h, l, r, a[2010];

int nmax, f[2010][2010], sum[2010];

int main() {
    n = read(), h = read(), l = read(), r = read();
    Rep(i, 1, n) a[i] = read(), sum[i] = sum[i - 1] + a[i];
    Rep(i, 1, n) {
        int x = (sum[i] - i), y = sum[i];
        if (i >= h) x = 0, y = h - 1;
        Rep(j, x, y) {
            int tp = j % h;
            f[i][tp] = max(f[i - 1][(tp - a[i] + h) % h], f[i - 1][(tp - a[i] + h + 1) % h]);
            if (l <= tp && tp <= r) ++f[i][tp];
            if (i == n) nmax = max(nmax, f[i][tp]);
        }
    }
    printf("%d", nmax);
    return 0;
}
```


---

## 作者：WYXkk (赞：3)

题目大意：给定 $h,l,r,a_1,a_2,\cdots,a_n$，你可以让某些 $a_i$ 减一，之后令 $x_0=0$，$x_i=(x_{i-1}+a_i)\mod h$，求 $x_1,x_2,\cdots,x_n$ 中至多有多少个在 $[l,r]$ 之间。$n,h\le 2\times10^3$。

解析：思博 dp。

假设 $dp(i,j)$ 表示 $x_{i-1}=j$ 时 $x_i,x_{i+1},\cdots,x_n$ 中至多有多少个在 $[l,r]$ 之间，那么很显然我们有

$$dp(i,j)=\max\left(\begin{matrix}dp(i+1,(j+a_i)\mod h)+[l\le (j+a_i)\mod h\le r]\\dp(i+1,(j+a_i-1)\mod h)+[l\le (j+a_i-1)\mod h\le r]\end{matrix}\right)$$

于是倒着 dp 一下就好了。

$\texttt{code:}$

```cpp
#include<cstdio>
#include<iostream>
#include<fstream>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
#define Set(a) memset(a,0,sizeof(a))
#define F(i,a,b) for(register int i=a,i##end=b;i<=i##end;++i)
#define UF(i,a,b) for(register int i=a,i##end=b;i>=i##end;--i)
#define openf(a) freopen(#a".in","r",stdin);freopen(#a".out","w",stdout)
#define re register
#define ri re int
#define il inline
typedef long long ll;
typedef unsigned long long ull;
template<typename T> inline T rd(T& x)
{
	T f=1;x=0;char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
	for(; isdigit(c);c=getchar()) x=(x<<3)+(x<<1)+(T)(c-'0');
	x*=f;
	return x;
}
ll rd(){ll x;rd(x);return x;}
inline int max(int a,int b){return a>b?a:b;}
inline int min(int a,int b){return a<b?a:b;}
const int inf=1<<30;

int n,h,l,r;
int dp[2005][2005],a[2005];
bool good(int x){return (l<=x)&&(x<=r);}
int main()
{
	rd(n);rd(h);rd(l);rd(r);
	F(i,1,n) rd(a[i]);
	UF(i,n,1) F(t,0,h-1) dp[i][t]=max(dp[i+1][(t+a[i])%h]+good((t+a[i])%h),dp[i+1][(t+a[i]-1)%h]+good((t+a[i]-1)%h));
	printf("%d\n",dp[1][0]);
	return 0;
}
```



---

## 作者：cyh_toby (赞：1)

# 题意
原题：[CF1324E 【Sleeping Schedule】](https://www.luogu.com.cn/problem/CF1324E)

给定正整数序列 $a$ ，对于每个数可以选择是否 $-1$ ，最终使其前缀和满足：在给定区间 $[l,r]$ 中的出现的值次数最多。

# 分析

不难想到，这种比较关心结果而不关心过程的问题很适合 DP 。

考虑构造状态。

由于涉及到取模等不好处理的运算，状态可以不包含当前的前缀，而只记录位置及使用 $-1$ 操作的次数。也即
$f_{i,j}$ 表示 **处理前 $i$ 个数，使用了 $j$ 次 $-1$ 操作** 的最优解。

那么就需要新开一个变量 $s$ 记录到目前为止的前缀和。可以不开数组，因为 DP 是按顺序进行的。

有点类似于背包问题。

因此状态转移就是

$$f_{i,j}=\bigg((s-j)\text{是否在给定区间中}\bigg)+\max\begin{cases}f_{i-1,j-1}\qquad(\text{在当前位置使用一次操作})\\f_{i-1,j}\qquad(\text{在当前位置不使用操作})\end{cases}$$

此外每次处理 $i$ 的状态时，需要 $s$ 自增 $a_i$ 。

可见是个 $O(n^2)$ 的 DP。

对于判断 $s\!-\!j$ 是否在给定区间中，需要进行一些模处理。具体见代码。

另外，注意 $j$ 的**取值范围**，应该是 $\big[0,i\big]$ 。

有些状态不合法，**要事先初始化为极小值**。

# 源码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2005;
int n, p, l, r, s;
int f[N][N];
int ans = 0;
int main()
{
	memset(f, -0x3f, sizeof(f)); 
	scanf("%d%d%d%d", &n, &p, &l, &r);
	f[0][0] = 0;
	for (int i = 1; i <= n; i++) {
		int x;
		scanf("%d", &x);
		s = (s+x) % p;
		f[i][0] = f[i-1][0] + (l<=s && s<=r);
		for (int j = 1; j <= i; j++)
			f[i][j] = (l<=((s-j)%p+p)%p && ((s-j)%p+p)%p<=r)+max(f[i-1][j-1], f[i-1][j]);
	}
	for (int i = 0; i <= n; i++) 
		ans = max(ans, f[n][i]);
	printf("%d", ans);
}
```

---

## 作者：devout (赞：1)

[博客内食用更佳](https://blog.csdn.net/devout_/article/details/104858457)

考虑DP（显然的）

设计一下状态$f_{i,j}$表示前$i$次睡觉，用了$j$次-1操作的最大好的睡眠数，那么我们用前缀和-j就是当前的睡眠时间了

转移非常的简单，就一行：
$$f_{i,j}=\max\{f_{i-1,j},f_{i-1,j-1}\}+((sum[i]-j+h)\bmod h)\in[l,r]$$

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

# define Rep(i,a,b) for(int i=a;i<=b;i++)
# define _Rep(i,a,b) for(int i=a;i>=b;i--)
# define RepG(i,u) for(int i=head[u];~i;i=e[i].next)

typedef long long ll;

const int N=2005;

template<typename T> void read(T &x){
   x=0;int f=1;
   char c=getchar();
   for(;!isdigit(c);c=getchar())if(c=='-')f=-1;
   for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+c-'0';
    x*=f;
}

int n,h,l,r;
int a[N],sum[N];
int f[N][N],ans;//f[i][j]表示前i次睡觉，用了j次-1操作时最多的good sleeping次数

int main()
{
    memset(f,-0x3f,sizeof(f));
    read(n),read(h),read(l),read(r);
    Rep(i,1,n)read(a[i]),sum[i]=sum[i-1]+a[i],sum[i]%=h;
    f[0][0]=0;
    Rep(i,1,n){
        int top=min(i,h);
        Rep(j,0,i){
            int val=(sum[i]-j%h+h)%h;
            f[i][j]=max(f[i][j],f[i-1][j]+(val>=l&&val<=r));
            f[i][j]=max(f[i][j],f[i-1][j-1]+(val>=l&&val<=r));
        }
    }
    Rep(i,0,n)ans=max(ans,f[n][i]);
    printf("%d\n",ans);
    return 0;
}
```


---

## 作者：chenxia25 (赞：1)

>### [洛谷题目页面传送门](https://www.luogu.com.cn/problem/CF1324E) & [CodeForces题目页面传送门](https://codeforces.com/contest/1324/problem/E)

>在Vova的世界里，一天$h\mathrm h$。Vova会睡$n$次觉，每次睡刚好$1$天。第$i$次会在第$i-1$次睡觉醒来后$(a_i-1)\mathrm h$或$a_i\mathrm h$后入睡，特殊地，第$0$次睡觉在第$0\mathrm h$醒来。设一次睡觉是在入睡当天的第$x\mathrm h$入睡，若$x\in[l,r]$，则称此次睡觉是好的。问最多能有多少次好的睡觉。

>$n\in[1,2000],h\in[3,2000],0\leq l\leq r<h,a_i\in[1,h)$。

可以说是基础DP。

设$dp_{i,j}$表示考虑到第$i$次睡觉，第$i$次睡觉在当天第$j\mathrm h$醒来时最多的好的睡觉次数。边界为$dp_{i,j}=\begin{cases}0&j=0\\-
\infty&j\neq0\end{cases}$（$j\neq0$时状态不合法），目标为$\max\limits_{i=0}^{h-1}\{dp_{n,i}\}$，状态转移方程为$dp_{i,j}=\max\!\left(dp_{i-1,(j-(a_i-1))\bmod h},dp_{i-1,(j-a_i)\bmod h}\right)+[j\in[l,r]]$（选择在上一次睡觉醒来后$(a_i-1)\mathrm h$还是$a_i\mathrm h$后入睡）。时间复杂度$\mathrm O(nh)$。

下面是AC代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int inf=0x3f3f3f3f;
const int N=2000,H=2000;
int dp[N+1][H];
int n,h,l,r;
int a[N+1];
bool in(int x){return l<=x&&x<=r;}//[x in [l,r]]
int main(){
	cin>>n>>h>>l>>r;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<h;i++)dp[0][i]=-inf;//不合法状态 
	for(int i=1;i<=n;i++)for(int j=0;j<h;j++)//DP 
		dp[i][j]=max(dp[i-1][(j-a[i]+1+h)%h],dp[i-1][(j-a[i]+h)%h])+in(j);//状态转移方程 
	cout<<*max_element(dp[n],dp[n]+h);//目标 
	return 0;
}
```


---

## 作者：F_Mu (赞：1)

**题意**

$Vova$有一个睡眠时间表，一天有$h$小时，$Vova$会睡$n$次觉，一次睡一天，在第$i-1$次睡醒后，$Vova$在$a_i$或$a_i-1$个小时候可以再次入睡，一开始时间为第$0$时（可以视作$Vova$刚醒），$Vova$在$[l,r]$区间时睡觉会睡得舒服，问$Vova$最多可以睡几次舒服觉

**分析**

发现第$i$次睡眠的时间是由第$i-1$次睡眠时间决定的，一个显然的转移，因此这道题采用$DP$

首先我们可以设第$0$次睡眠时，$Vova$是在第$0$时刻睡的

假设$Vova$在第$i-1$次睡眠时在第$j$时刻，那么第$i$次$Vova$可以在第$(j+a_i)\%h$时刻或者在第$(j+a_i-1)\%h$时刻睡觉，我们可以记录一个$vis[i][j]$表示$Vova$在第$i$次睡眠时在第$j$时刻可以睡

而如果$(j+a_i)\%h$在$[l,r]$区间内，则第$i$次睡眠在第$(j+a_i)\%h$时刻的答案数为第$i-1$次睡眠时$j$时刻的答案数加一，因为有多种方案使得$Vova$能在第$i-1$次睡眠时在第$j$时刻，因此取最大值，可以记录$dp[i][j]$表示在第$i$次睡眠时在第$j$时刻的答案，$dp[i][(j+a_i)\%h]=max(dp[i-1][j]+1,dp[i][(j+a_i)\%h])$

如果$(j+a_i)\%h$不在$[l,r]$区间内，则$dp[i][(j+a_i)\%h]=max(dp[i-1][j],dp[i][(j+a_i)\%h])$

答案可以在每次更新$dp[i][j]$时更新

$(j+a_i-1)\%h$同理

这题不卡空间，可以不使用滚动数组

```cpp
#pragma GCC optimize(3, "Ofast", "inline")

#include <bits/stdc++.h>

#define start ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define ll long long
#define int ll
#define ls st<<1
#define rs st<<1|1
#define pii pair<int,int>
using namespace std;
const int maxn = (ll) 3e5 + 5;
const int mod = 1000000007;
const int inf = 0x3f3f3f3f;
int dp[2005][2005];
bool vis[2005][2005];
int ans;

signed main() {
    start;
    int n, h, l, r;
    cin >> n >> h >> l >> r;
    vis[0][0] = true;
    for (int i = 1; i <= n; ++i) {
        int x;
        cin >> x;
        for (int j = 0; j < 2000; ++j) {
            if (vis[i - 1][j]) {
                int t = (j + x) % h;
                vis[i][t] = true;
                if (t >= l && t <= r)
                    dp[i][t] = max(dp[i][t], dp[i - 1][j] + 1);
                else
                    dp[i][t] = max(dp[i][t], dp[i - 1][j]);
                ans = max(ans, dp[i][t]);
                t = (j + x - 1) % h;
                vis[i][t] = true;
                if (t >= l && t <= r)
                    dp[i][t] = max(dp[i][t], dp[i - 1][j] + 1);
                else
                    dp[i][t] = max(dp[i][t], dp[i - 1][j]);
                ans = max(ans, dp[i][t]);
            }
        }
    }
    cout << ans;
    return 0;
}
```

---

## 作者：__OwO__ (赞：1)

这题一看就是一道DP

因为提前了几次对后面的决策有影响,所以我们把它加为一个维度

所以有

```f[i][o]=min(f[i-1][o],f[i-1][o-1])+isgood(i,o)```

$o$表示包括这次的早睡次数,$i$表示这是第几次,我们枚举$o$,$i$($o$范围是$[0,i]$),然后递推即可

```isgood(i,o)```判断前$i$次提前$o$次是否会使第$i$次是good

可以通过前缀和优化

上代码:
```cpp
#include<bits/stdc++.h>
#define ull long long
using namespace std;
int f[2010][2010];
int sum[2010],arr[2010];
int n,h,l,r;
int isgood(int i,int t){
	int time=(sum[i]-t)%h;
	if(time>=l&&time<=r)return true;
	return false;
}//前缀和优化
int main(){
	cin>>n>>h>>l>>r;
	for(int i=1;i<=n;i++){
		cin>>arr[i];
		sum[i]=sum[i-1]+arr[i];
	}
	long long good=0;
	for(int i=1;i<=n;i++){
		for(int t=0;t<=i;t++){
			f[i][t]=max(f[i-1][t],f[i-1][t-1])+isgood(i,t);
			good=max(good,(long long)f[i][t]);
		}
	}//递推
	cout<<good;
	return 0;
}
```

---

