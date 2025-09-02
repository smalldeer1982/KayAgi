# [AGC007D] Shik and Game

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc007/tasks/agc007_d

一直線上でゲームを行います。はじめプレイヤーは座標 $ 0 $ におり、キャンディを $ N $ 個持っています。座標 $ E $ に出口があります。プレイヤーの他に、この直線上には $ N $ 匹のクマがおり、$ i $ 匹目のクマは座標 $ x_i $ で静止しています。プレイヤーは直線上を $ 1 $ 以下の速度で動くことができます。

プレイヤーがクマにキャンディを $ 1 $ 個与えると、クマは $ T $ 単位時間後に $ 1 $ 枚のコインをその場に吐き出します。すなわち、時刻 $ t $ にクマにキャンディを $ 1 $ 個与えると、時刻 $ t+T $ にそのクマの位置に $ 1 $ 枚のコインが出現します。このゲームの目的は、$ N $ 匹すべてのクマにキャンディを与え、$ N $ 枚のコインをすべて回収して出口から脱出することです。クマにキャンディを与えるためには、プレイヤーはクマと同じ位置にいなければなりません。また、$ 1 $ 匹のクマに $ 2 $ 回以上キャンディを与えることはできません。コインは、出現した瞬間以降にプレイヤーがコインと同じ位置にいれば回収できます。プレイヤーが回収する前にコインが消滅することはありません。

シックはこのゲームの達人です。シックがクマにキャンディを与えたり、コインを拾うのに必要な時間は極めて短く、無視することができます。ゲームの設定が与えられるので、シックがすべてのコインを集めて出口から脱出するまでに必要な最短時間を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 100,000 $
- $ 1\ \leq\ T,\ E\ \leq\ 10^9 $
- $ 0\ <\ x_i\ <\ E $
- $ x_i\ <\ x_{i+1} $ ($ 1\ \leq\ i\ <\ N $)
- 入力値はすべて整数である。

### 部分点

- $ 600 $ 点分のデータセットでは、$ N\ \leq\ 2,000 $ が成り立つ。

### Sample Explanation 1

出口に向かいながら、クマに会うたびにキャンディを与え、その場でコインが出るのを待つのが最適です。このとき、移動に $ 9 $ 単位時間、$ 3 $ 回の待機に $ 3 $ 単位時間、合計で $ 12 $ 単位時間を要します。

## 样例 #1

### 输入

```
3 9 1
1 3 8```

### 输出

```
12```

## 样例 #2

### 输入

```
3 9 3
1 3 8```

### 输出

```
16```

## 样例 #3

### 输入

```
2 1000000000 1000000000
1 999999999```

### 输出

```
2999999996```

# 题解

## 作者：C_S_X_ (赞：13)

考虑这是一个怎样的过程，我们发现，每个
$
[0,E]
$的数轴上的位置要么被经过一次，要么被经过三次。我们想象一下操作的过程，首先连续往右走一段给熊喂糖果，然后等到一个合适的时机，回头把硬币捡起来，再往右走，然后一直重复这个动作。

于是设计状态
$
f_i
$
表示第1到
$
i
$
只熊的硬币都已经捡起来了并到了
$
x_i
$
位置，且其他熊的糖还没喂的最小花费。

$$
f_i=\min \{ f_j+a_i-a_j+\max\{2(a_i-a_{j+1}),T\}\}
$$

T是因为我可以选择在这个位置不走等着他吐硬币。
发现
$
a_i-a_j
$
的求和其实就是
$
x_n
$
，以这一项不看，最后加上E即可。

$$
f_i=\min \{ f_j+\max\{2(a_i-a_{j+1}),T\}\}
$$

分类讨论：

- $
2(a_i-a_{j+1}) \leq T
$

$
f_i=\min \{ f_j+T\}
$

- $
2(a_i-a_{j+1}) > T
$

$
f_i=\min \{ f_j+2(a_i-a_{j+1})\}
$

由于$a_i-a_{j+1}$在$a_i$增大时是单调递增的，所以维护一个队列，满足条件1的j留在队列里，每次队首转移，所有出队的j都满足条件2，记录一下它们的最小值，复杂度$O(n)$

```cpp
#include<bits/stdc++.h>
#define FOR(i,a,b) for (register ll i=(a);i<=(b);i++)
#define For(i,a,b) for (register ll i=(a);i>=(b);i--)
#define mem(i,j) memset(i,j,sizeof(i))
using namespace std;
typedef long long ll;
const ll N=2e5+5;
ll n,E,T,x[N],f[N],Ans,k=1e18;
ll l=1,r=1,q[N];
ll read()
{
	ll x=0,f=1;
	char c=getchar();
	while (c<'0'||c>'9') {if (c=='-') f=-1;c=getchar();}
	while (c>='0'&&c<='9') {x=(x<<1)+(x<<3)+c-'0';c=getchar();}
	return f*x;
}
int main()
{
	mem(f,0x3f);
	n=read(),E=read(),T=read();
	FOR(i,1,n) x[i]=read();
	f[0]=0;
	FOR(i,1,n)
	{
		while (l<=r&&2*(x[i]-x[q[l]+1])>T)
		{
			k=min(k,f[q[l]]-2*x[q[l]+1]);
			l++;
		}
		f[i]=min(f[i],f[q[l]]+T);
		f[i]=min(f[i],k+2*x[i]);
		q[++r]=i;
	}
	Ans=f[n]+E;
	printf("%lld\n",Ans);
	return 0;
}
```


---

## 作者：louhao088 (赞：8)

一道简单的 dp 。


------------


首先根据题意，如果要往回走那一定要走到之前第一个只走到一次的位置，不然之后还要再走回来，回来，肯定不会变优。

那么我们设 $f[i]$ 表示收到前 i 个糖果的最小时间，那么他必然在第 $x[i]$ 这个位置。

那么很容易推出：

$f[i]=\min(f[j]+x[i]-x[j]+\max(2\times(x[i]-x[j+1]),T))$。

其中

$x[i]-x[j]$ 表示第一遍从 j 走到 i。

$2\times(x[i]-x[j+1])$ 表示再走回去再走回来，与 $T$ 取大的是因为至少要T才能吃到糖果。


------------

首先对于 $x[i]-x[j]$ ，所有 $f[n]$ 必然是从头走到尾，只要加上 $x[n]$ 就好了。

对于剩下的我们分类讨论，我们只要枚举 $2\times(x[i]-x[j+1])$ 大于 $T$ 的转折点。

因为 $x[i]$ 单调递增，所以这个转折点 $l$ 必然也递增。可以做到 $O(n)$，我们要记录这一段的 $f[j]-x[j+1]$ 的最小值，答案只要加上 $x[i]$ 就好了。

对于后面一段，答案是 $f[j]+T$ ,因为 $f[j]$ 单调递增（都能拿后面的糖果了，前面肯定已经拿到了）。我们只要取 j 最小，即 $f[l+1]+T$。

故最后每次答案只要在上述两个之中取较大值。

再在最后加上 $x[n]$ 就可以了。

最终复杂度 $O(n)$。

------------
代码非常短
```cpp
#include<bits/stdc++.h>
using namespace std;
//static char buf[1000000],*p1=buf,*p2=buf;
//#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
#define re register
#define int long long
const int maxn=1e5+5,M=34005;
inline int read()
{
	char ch=getchar();bool f=0;int x=0;
	for(;!isdigit(ch);ch=getchar())if(ch=='-')f=1;
	for(;isdigit(ch);ch=getchar())x=(x<<1)+(x<<3)+(ch^48);
	if(f==1)x=-x;return x;
}
inline void print(int x)
{
    static int a[55];int top=0;
    if(x<0) putchar('-'),x=-x;
    do{a[top++]=x%10,x/=10;}while(x);
    while(top) putchar(a[--top]+48);
}
int n,m,t,a[maxn],f[maxn],Min;
signed main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	n=read(),m=read();t=read();
	for(int i=1;i<=n;i++)a[i]=read();int l=0,Min=1e15;
	for(int i=1;i<=n;i++)
	{
		while(2*(a[i]-a[l+1])>=t&&l<n)Min=min(Min,f[l]-2*a[l+1]),l++;
		f[i]=Min+2*a[i];f[i]=min(f[i],f[l]+t);
	}
	cout<<f[n]+m<<endl;
 	return 0;
}

```


---

## 作者：tZEROちゃん (赞：3)

考虑 dp。

不妨设 $dp_i$ 表示第 $1$ 到 $i$ 只熊的硬币都已经捡起来了，现在到了 $a_i$ 位置，且其他熊的糖还没喂的最小花费。

状态转移是显然的：

$$ dp_i = \min\Big(dp_j + a_i - a_j + \max\big(T, 2(a_i - a_{j + 1})\big)\Big)$$

但你枚举 $i, j$ 转移的复杂度是平方级别的，过不掉。

怎么办捏。

首先那个 $a_i - a_j$ 并没有什么用处，所以你直接给答案加上 $E$ 就行。

然后我们看那个 $\max$，可以把他拆开，变成 $t > 2(a_i - a_{j + 1})$ 和 $t\le 2(a_i - a_{j + 1})$。

然后你对一个固定的 $i$ 找到一个临界值 $p$，使得前者的范围为 $j>p$，后者的范围为 $j\le p$ 。

显然 $p$ 是不减的，所以我们可以维护这个 $p$。

对于后者，我们变形为 $dp_i = 2a_i + \min(dp_j - 2a_{j + 1})$。设 $f_i = \min(dp_i - 2a_{i + 1})$，指针指一下就行，总复杂度就 $O(n)$ 了。

```cpp
#define int long long

const int N = 1e5 + 10;
int a[N], dp[N];

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, E, T, j = 0; cin >> n >> E >> T;
  rep (i, 1, n) cin >> a[i];
  memset(dp, 0x3f, sizeof dp);
  dp[0] = 0; int mn = 0x3f3f3f3f3f3f3f3f;
  rep (i, 1, n) {
    while (T <= 2 * (a[i] - a[j + 1])) {
      mn = min(mn, dp[j] - 2 * a[j + 1]); ++j;
    }
    dp[i] = min({dp[i], dp[j] + T, 2 * a[i] + mn});
  }  
  cout << E + dp[n];
  return ~~(0 ^ 0);
}
```

---

## 作者：xixike (赞：2)

[更好的阅读体验](https://www.cnblogs.com/xixike/p/15712797.html)

## Description

[Luogu传送门](https://www.luogu.com.cn/problem/AT2171)

## Solution

考虑一下 Shik 走路的全过程——不停地来回走。

有的路段只经过了一次，有的经过了三次。

那么我们设 $f_i$ 表示拿到了前 $i$ 个金币所花费的最小时间，由于是最小时间，那么他必定在 $a_i$ 这个位置上。

转移方程：
$$
f_i = \min\{f_j + (a_i - a_j) + \max(2(a_i - a_{j + 1}), T)\}
$$
这是什么意思呢？

- 第一个 $a_i - a_j$ 表示的是从 $a_j$ 走到 $a_i$ 花费的时间。

- $2(a_i - a_{j + 1})$ 指折返回去再走回来，所以要乘 2。
- $T$ 是因为可能折回去之后还没有金币，所以还得等到 $T$，所以要取 $\max$。

不难发现，$a_i - a_j$ 的和就是 $a_n$，所以可以不用管，最后输出答案的时候加上 $E$ 即可。

再来看如何转移，要分类讨论一下：

- $2(a_i - a_{j + 1}) > T$ 时，$f_i = f_j + T$.
- $2(a_i - a_{j + 1}) \leq T$ 时，$f_i = f_j + 2(a_i - a_{j + 1})$.

容易发现，对于固定的 $i$，$a_i - a_{j + 1}$ 在 $j = 1 \sim i - 1$ 时是单调递减的，所以直接单调队列跑一遍即可，或者拿个指针扫一遍也行。

## Code

```cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

namespace IO{
    inline ll read(){
        ll x = 0;
        char ch = getchar();
        while(!isdigit(ch)) ch = getchar();
        while(isdigit(ch)) x = (x << 3) + (x << 1) + ch - '0', ch = getchar();
        return x;
    }

    template <typename T> inline void write(T x){
        if(x > 9) write(x / 10);
        putchar(x % 10 + '0');
    }
}
using namespace IO;

const ll N = 1e5 + 10;
ll n, E, T, l, mins = 1e18;
ll a[N], f[N];
ll q[N], head, tail;

signed main(){
    n = read(), E = read(), T = read();
    for(ll i = 1; i <= n; ++i) a[i] = read();
    memset(f, 0x3f, sizeof(f));
    f[0] = 0;
    head = 1, tail = 1;
    for(int i = 1; i <= n; ++i){
        while(head <= tail && 2 * (a[i] - a[q[head] + 1]) > T)
            mins = min(mins, f[q[head]] - 2 * a[q[head] + 1]), head++;
        f[i] = min(f[i], min(f[q[head]] + T, mins + 2 * a[i]));
        q[++tail] = i;
    }
    write(f[n] + E);
    return 0;
}
```

$$
\_EOF\_
$$


---

## 作者：chenxia25 (赞：2)

>### [洛谷题目页面传送门](https://www.luogu.org/problem/AT2171) & [AtCoder题目页面传送门](https://atcoder.jp/contests/agc007/tasks/agc007_d)

>有$1$根数轴，Shik初始在位置$0$。数轴上有$n$只小熊，第$i$只在位置$a_i$。Shik每秒可以向左移动$1$个单位长度、原地不动或向右移动$1$个单位长度。Shik第$1$次到某个小熊的位置$s$秒后，小熊会在原地生产$1$个金币，Shik必须再次到达此小熊的位置才能收集金币。求Shik收集完所有金币后到达位置$m$所花的最小秒数。

>$n\in\left[1,10^5\right],a_i\in(0,m),a_i<a_{i+1}$。

考虑最优情况下，Shik的路线会是怎样的。如果Shik经过了一些小熊，回头收集了这些小熊中后面一部分的金币，然后继续往终点走，留下前面一部分金币等到以后再收，这样肯定不是最优的（感性理解）。可以推出若一个小熊的金币被收了，那么它前面的所有小熊的金币都被收了，即被收了金币的小熊序列是所有小熊序列的一个前缀。考虑将某时刻的前缀分成若干个区间，每个区间内的小熊都是在一次回头中被收了金币的，于是我们就可以DP了。

设$dp_i$表示Shik收完了前$i$个小熊的金币并回到了位置$a_i$所花的最小秒数。不妨设$a_0=0$为起点。那么显然边界是$dp_0=0$，目标是$dp_n+m-a_n$。转移的话，枚举当前被收了金币的小熊前缀被划分的最后一个区间的左端点的前一个小熊$j$，即最后一次回头之前$[1,j]$已经被收了。那么最后一次回头收的是$[j+1,i]$。显然，路线是这样的：先将前$j$个小熊的金币收完，回到位置$a_j$，然后$a_j\to a_i$经过$[j+1,i]$使它们生产金币，然后$a_i\to a_{j+1}$回头到第$j+1$个小熊，等待若干秒直到第$j+1$个小熊生产金币，然后$a_{j+1}\to a_i$依次收完$[j+1,i]$的金币并回到位置$a_i$。那么状态转移方程就很好列了：

$$dp_i=\min_{j=0}^{i-1}\left\{dp_j+(a_i-a_j)+(a_i-a_{j+1})+\max\left(0,s-2(a_i-a_{j+1})\right)+(a_i-a_{j+1})\right\}$$

即

$$dp_i=\min_{j=0}^{i-1}\left\{dp_j+3a_i-a_j-2a_{j+1}+\max\left(0,s-2a_i+2a_{j+1}\right)\right\}$$

暴力转移显然是$\mathrm O\left(n^2\right)$的，于是考虑优化。注意到方程里有个$\max$很不好处理，于是分类讨论，分成$s-2a_i+2a_{j+1}\ge0$和$s-2a_i+2a_{j+1}<0$这$2$种。此时方程变为了：（化简后）

$$dp_i=\min\left(\min_{j\in[0,i),s-2a_i+2a_{j+1}\ge0}\{dp_j+a_i-a_j+s\},\min_{j\in[0,i),s-2a_i+2a_{j+1}<0}\{dp_j+3a_i-a_j-2a_{j+1}\}\right)$$

将关于决策变量$j$的放到一起，关于状态变量$i$的和常量放到一起，得

$$dp_i=\min\left(\min_{j\in[0,i),2a_{j+1}\ge 2a_i-s}\{(dp_j-a_j)+(a_i+s)\},\min_{j\in[0,i),2a_{j+1}<2a_i-s}\{(dp_j-a_j-2a_{j+1})+3a_i\}\right)$$

$2$个$\min$的条件里的$2a_{j+1}$显然有单调性，所以$2$个$\min$取的$j$都构成区间。特殊地，对于第$2$个$\min$，是前缀，即左端点为$0$的区间。又因为$2a_i-s$也有单调性，所以第$1$个$\min$的区间左端点单调递增，对于每个$i$，这个左端点可以two-pointers求出。于是对于第$1$个$\min$维护单调队列，对于第$2$个$\min$维护前缀最小值，$\mathrm O(n)$。

下面贴代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long//防爆int 
const int inf=0x3f3f3f3f3f3f3f3f;
const int N=100000;
int n/*小熊个数*/,m/*终点*/,s/*小熊被Shik碰到至生产金币之间的秒数*/;
int a[N+1];//小熊的位置 
int dp[N+1];//dp[i]表示Shik收完了前i个小熊的金币并回到了位置a[i]所花的最小秒数 
int q[N],head,tail;//对于第1个min维护的单调队列 
signed main(){
	cin>>n>>m>>s;
	for(int i=1;i<=n;i++)cin>>a[i];
	q[tail++]=0;//i=1,j=0满足2a[j+1]>=2a[i]-t，归第1个min，于是压入单调队列 
	int now=-1/*第2个min取的j构成的区间（前缀）的右端点*/,mn=inf/*当前的前缀最小值*/;
	for(int i=1;i<=n;i++){
		while(now+1<i&&2*a[now+2]<2*a[i]-s)now++,mn=min(mn,dp[now]-a[now]-2*a[now+1]);//将now往后移 
		while(head<tail&&q[head]<=now)head++;//维护单调队列，弹出过时元素 
		while(head<tail&&dp[q[tail-1]]-a[q[tail-1]]>=dp[i-1]-a[i-1])tail--;//维护单调队列队尾严格单调递增性 
		q[tail++]=i-1;//将j=i-1入队 
		dp[i]=min(dp[q[head]]-a[q[head]]+a[i]+s,mn+3*a[i]);//状态转移方程 
	}
	cout<<dp[n]+m-a[n]<<"\n";//目标 
	return 0;
}
```

---

## 作者：win114514 (赞：0)

[更好的阅读体验。](https://www.cnblogs.com/Al-lA/p/17655260.html)

一道有意思的 $\text{dp}$ 呀。

### 思路

我们容易发现，一个点最多会往回走一次。

也就是每一个点最多被遍历三次。

因此，我们可以考虑每个点的贡献。

$$dp_i=\min_{j=1}^{i-1}dp_j+x_i-x_j+\max(2\times(x_i-x_{j+1}),T)$$

其中，$dp_i$ 表示前 $i$ 个金币全部取完，此时位于第 $i$ 个位置。

这个式子很容易维护。

我们不妨分类讨论。

1. $2\times(x_i-x_{j+1})>T$

    那么，我们只要维护 $dp_i-x_i-2\times x_{j+1}$ 的最小值即可。
1. $2\times(x_i-x_{j+1})\le T$

    由于 $n$ 只有 $10^5$，那么我们用暴力维护上述式子。
    
    因为 $2\times(x_i-x_{j+1})$ 是在不断变大的。
    
    那么我们只需要用堆维护一下（也可以用单调队列，堆更好写）。

代码就很好写了。

### Code

[AC记录](https://atcoder.jp/contests/agc007/submissions/44897335)。


---

