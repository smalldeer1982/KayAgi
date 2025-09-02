# Choosing Carrot

## 题目描述

下个月就是奶牛Z的生日啦，为了给奶牛Z购买生日礼物，奶牛A和奶牛B决定去挑选奶牛Z最喜欢的青草来作为送给奶牛Z的生日礼物。
现在，奶牛A和奶牛B买来了n堆青草，从左数起，第i堆青草的甜度为ai。奶牛A认为奶牛Z喜欢甜的青草，而奶牛B认为奶牛Z喜欢不甜的青草。因此，奶牛A希望选出来的青草是最甜的，奶牛B希望选出来的是最不甜的青草。
为了解决这个问题，奶牛A与奶牛B决定玩一个游戏，他们俩每次可以从两端的青草开始，选择其中一堆并把这一堆青草吃掉，最后剩下的那一堆青草就是送给奶牛Z的生日礼物，奶牛A先开始吃。
在玩游戏之前，奶牛B去上了一次厕所，奶牛A乘机进行了K次操作，每次操作也是按照要求从这些草堆当中，选择两端的草堆并吃掉其中一堆。在奶牛B回来之后，同样也是奶牛A先开始吃。
奶牛A想知道，对于每一个K（0≤K≤n-1），最后送给奶牛Z的青草甜度分别是多少？

## 样例 #1

### 输入

```
4
1 2 3 5
```

### 输出

```
3 3 5 5
```

## 样例 #2

### 输入

```
5
1000000000 1000000000 1000000000 1000000000 1
```

### 输出

```
1000000000 1000000000 1000000000 1000000000 1000000000
```

# 题解

## 作者：是个汉子 (赞：14)



### 题解：
\
1.我们可以先考虑不进行 $k$ 操作的情况

​		当取完的时候，**因为最优**（B可以通过他的 $\dfrac{n}2-1$ 次机会取走，所以 $mid$ 和 $mid+1$ 对于B是拿不到的），肯定是剩下中间的几个

​		然后由A选择小的那个，剩下大的，则有两种情况：
$$
ans=\begin{cases}\max(a[mid],a[mid+1])~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~n为偶数\\\max(\min(a[mid],a[mid-1]),\min(a[mid],a[mid+1]))~~~~~n为奇数\end{cases}
$$
\
2.然后考虑进行 $k$ 操作

​		当A多吃，只有 $mid$ 会被影响，发生变化，而每个 $i\in [1,k-2]$ 是由 $i+2$ 转移过来的，三种可能：

要么左右各拿一个 $mid$ 不变，要么左边或者右边拿俩 $mid$ 变化，而我们考虑奇偶即可，左右拿俩可以合并到一个数组，但是如果要求左右拿俩的情况，则需要用到动态规划

​		设 $h[i]$ 为偶数个数当 $i$ 为中点时最大值， $g[i]$ 为奇数个数当 $i$ 为中点时最大值， $ans[i]$ 为剩下 $i$ 个元素能取到的最大值，转移方程为：
$$
ans[2*i]=\max(ans[2*i+2],h[i])\\
ans[2*i+1]=\max(ans[2*i+3],g[i])
$$
\
最后倒序输出，时间复杂度 $O(n)$ 

### 代码

```c++
#include <cstdio>
#include <iostream>

using namespace std;
const int MAXN=300005;
int n,a[MAXN],h[MAXN],g[MAXN],ans[MAXN];

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        ans[1]=max(ans[1],a[i]);
    }
    for(int i=1;i<n;i++) h[min(i,n-i)]=max(h[min(i,n-i)],max(a[i],a[i+1]));//代表偶数下的最值 
    for(int i=2;i<n;i++) g[min(i-1,n-i)]=max(g[min(i-1,n-i)],max(min(a[i-1],a[i]),min(a[i],a[i+1])));//代表奇数下的最值 
    for(int i=n/2;i>=1;i--)
    {
        ans[i<<1]=max(ans[(i+1)<<1],h[i]);
        ans[i<<1|1]=max(ans[(i+1)<<1|1],g[i]);
    }
    for(int i=n;i>=1;i--)
        printf("%d ",ans[i]);
}
```



---

## 作者：crashed (赞：6)

# 题目
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[点这里](https://www.luogu.org/problem/CF794E)看题目。
# 分析
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;这是......结论题呀。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;好吧，从最暴力的方法开始：  
### 50分（OJ数据）
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;考虑区间$DP$：  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$DP(0/1,i,j)$：当奶牛$A$/奶牛$B$对于区间$[i,j]$先手时，剩下的青草的甜度值。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;然后考虑转移：   
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$DP(0,i,j)=\max(DP(1,i+1,j),DP(1,i,j-1))$  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$DP(1,i,j)=\min(DP(0,i+1,j),DP(0,i,j-1))$  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;对于每个$K$，扫一遍出答案。时间是$O(n^2)$。  
### 100分（OJ数据）  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;上面这个$DP$显然是优化不了的，所以我们考虑找规律。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;如果$A$先操作，一个区间$[l,r]$，经过乱搞，应该可以发现如下的规律：  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;若$r-l$为偶数：  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;设$mid=\frac {l+r} 2$，则可以知道此时区间的答案应该是$\max(a_{mid},a_{mid+1})$。因为此时$B$牛有$\frac {r-l} 2 - 1$次操作。所以$B$无论如何都影响不了中间两个，所以这个就靠$A$选了。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;若$r-l$为奇数：  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;设$mid=\lfloor\frac{l+r} 2\rfloor$，则此时区间的答案应该是$\max(\min(a_{mid-1},a_{mid}),\min(a_{mid},a_{mid+1}))$。因为$A$先吃掉了一个，答案就变成了$B$先操作，对于$[l+1,r]$或者$[l,r-1]$的答案较大值。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;然后考虑$A$先啃掉几口之后的情况。实际上，这就是原序列的几个子区间中的答案的最大值。由于同奇偶的区间可以快速转移，所以我们考虑$DP$。~~还是回来了~~  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$f(i)$：原序列长度为$i$的所有区间的答案的最大值。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;考虑转移：  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$f(i)=\begin{cases}\max(f(i+2),g(i)) & i\equiv0\mod 2 \\max(f(i+2),h(i))&i\equiv1\mod2\end{cases}$  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;上面的转移方程实际上是两个部分：  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;1.当前的区间是由长度为$i+2$的区间两边啃一口之后转过来的；  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;2.当前的区间无法由长度为$i+2$的区间两边啃一口转过来。实际上这种情况只有可能当区间的一端为左端点或右端点时发生。所以我们完全可以在开始的时候就把这样的答案处理出来。$g$函数和$h$函数分别为中心点为$i$的，长度为偶数或者奇数，且一端在左右端点的区间的答案的最大值。可以用$O(n)$的时间分别处理出来。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$f$函数的递推也是$O(n)$的，总时间也就是$O(n)$的。
# 代码
```cpp
#include <cstdio>

const int MAXN = 3e5 + 5;

template<typename _T>
void read( _T &x )
{
	x = 0;char s = getchar();int f = 1;
	while( s > '9' || s < '0' ){if( s == '-' ) f = -1; s = getchar();}
	while( s >= '0' && s <= '9' ){x = ( x << 3 ) + ( x << 1 ) + ( s - '0' ), s = getchar();}
	x *= f;
}

template<typename _T>
void write( _T x )
{
	if( x < 0 ){ putchar( '-' ); x = ( ~ x ) + 1; }
	if( 9 < x ){ write( x / 10 ); }
	putchar( x % 10 + '0' );
}

template<typename _T>
_T MAX( const _T a, const _T b )
{
	return a > b ? a : b;
}

template<typename _T>
_T MIN( const _T a, const _T b )
{
	return a < b ? a : b;
}

int f[MAXN], g[MAXN], h[MAXN];
int a[MAXN];
int N;

int main()
{
	read( N );
	for( int i = 1 ; i <= N ; i ++ ) scanf( "%d", &a[i] ), f[1] = MAX( f[1], a[i] );
	for( int i = 1 ; i < N ; i ++ )
		g[MIN( i, N - i )] = MAX( g[MIN( i, N - i )], MAX( a[i], a[i + 1] ) );
	for( int i = 2 ; i < N ; i ++ )
		h[MIN( i - 1, N - i )] = MAX( h[MIN( i - 1, N - i )], MAX( MIN( a[i - 1], a[i] ), MIN( a[i], a[i + 1] ) ) );
	//这里下标单独-1是为了配合f的转移 
	for( int i = N >> 1 ; i >= 1 ; i -- )
	{
		f[i << 1] = MAX( f[( i + 1 ) << 1], g[i] );
		f[i << 1 | 1] = MAX( f[( i + 1 ) << 1 | 1], h[i] );
	}
	for( int k = 0 ; k < N ; k ++ )
		write( f[N - k] ), putchar( k == N - 1 ? '\n' : ' ' );
	return 0;
}```

---

## 作者：Galex (赞：4)

看不懂大佬们的线性解法，我来弱弱的提供一个好想也好写的 $O(n\log n)$ 解法吧。

以下 $mid(l,r)$ 表示 $\frac{l+r}{2}$。

对于一个长度为 $n$ 的序列，如果不提前操作，最后的结果为：

$n$ 为奇数：$\max(\min(a[mid(l,r) - 1], a[mid(l,r)]),\min(a[mid(l,r)],a[mid(l,r)+1]))$。  
$n$ 为偶数：$\max(a[mid(l,r)],a[mid(l,r)+1])$。

那么经过 $k$ 次操作的序列，显然是原序列的长度为 $n-k$ 的一个区间，而且可以是任意一个。那答案就相当于是 $\max\limits_{l=1}^{k+1}\{val(l,l+n-k-1)\}$，其中 $val(x,y)$ 表示把原序列的区间 $[x,y]$ 单独看成一个序列且不提前操作的答案。

按 $n-k$ 的奇偶性分类讨论：

$n-k$ 为奇数：答案为 $\max\limits_{i=mid(1,n-k)}^{mid(k+1,n)}\{\max(\min(a[i],a[i-1]),\min(a[i],a[i+1]))\}$。  
$n-k$ 为偶数：答案为 $\max\limits_{i=mid(1,n-k)}^{mid(k+1,n)}\{\max(a[i],a[i+1])\}$。

而这两个东西显然很容易分别用两个 st 表维护。

最后特判一下 $k=n-1$ 的情况，答案为 $\max\{a_i\}$。

代码：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int read() {
	int s = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9')
		f = (ch == '-' ? -1 : 1), ch = getchar();
	while (ch >= '0' && ch <= '9')
		s = (s << 1) + (s << 3) + (ch ^ 48), ch = getchar();
	return s * f;
}

int n;
int a[300005], ans[300005];
int st[2][300005][20];

#define pw(i) (1 << i)

void build() {
	for (int i = 1; i <= n; i++)
		st[0][i][0] = max(a[i], a[i + 1]), st[1][i][0] = max(min(a[i], a[i - 1]), min(a[i], a[i + 1]));
	for (int j = 1; pw(j) <= n; j++)
		for (int i = 1; i + pw(j) - 1 <= n; i++)
			st[0][i][j] = max(st[0][i][j - 1], st[0][i + pw(j - 1)][j - 1]),
			st[1][i][j] = max(st[1][i][j - 1], st[1][i + pw(j - 1)][j - 1]);
}

int qry(int l, int r, int op) {
	int i = log(r - l + 1) / log(2);
	return max(st[op][l][i], st[op][r - pw(i) + 1][i]);
}

signed main() {
	n = read();
	int maxa = 0;
	for (int i = 1; i <= n; i++)
		a[i] = read(), maxa = max(maxa, a[i]);
	build();
	for (int i = n; i >= 2; i--) {
		int l = (1 + i) >> 1, r = (n + n - i + 1) >> 1;
		printf("%lld ", qry(l, r, i % 2));
	}
	printf("%lld", maxa);
	return 0;
}
```

---

## 作者：lzqy_ (赞：4)

简单博弈论。

先讨论 $n$ 为奇数的情况。设 $mid=\frac n 2$，则有：

1. 若 $\text A$ 先手 $\text B$ 后手，则最终剩下的是 $\min\{a_{mid},\max(a_{mid-1},a_{mid+1})\}$。

2. 若 $\text B$ 先手 $\text A$ 后手，则最终剩下的是 $\max\{a_{mid},\min(a_{mid-1},a_{mid+1})\}$。

显然两种情况对称，只证明第一种情况：

-----

- 如果 $\text{B}$ 每次都与 $\text A$ 取异侧的数，那么显然最后剩下的是 $a_{mid}$，由于 $\text B$ 后手，该数一定可以取到。

- 如果第一次 $\text B$ 与 $\text A$ 取同侧的数，可以理解为将 $mid$ 移动一步，再按照上一步便可以取到 $a_{mid-1}/a_{mid+1}$。由于 $\text{A}$ 先手，第一次取哪一侧是由 $\text A$ 决定的，所以只能取到 $\max(a_{mid-1},a_{mid+1})$。
    
- 当 $mid$ 向某一方向移动一步以后，$\text A$ 只需要一直取另一侧的数，便可保证 $mid$ 不会继续移动（只可能移动回中间的位置，那么情况回到第一步）。

- 综上所述，$\text B$ 能取到 $\min\{a_{mid},\max(a_{mid-1},a_{mid+1})\}$。

------

若初始 $n$ 为奇数则为情况一，若初始 $n$ 为偶数，可以理解成 $\text A$ 多取走一个数（**即 $\textbf{k+1}$**），然后转换为情况二。


-----


接下来正式考虑如何解答。

设 $b_x=\min\{a_{x},\max(a_{x-1},a_{x+1})\},c_x=\max\{a_{x},\min(a_{x-1},a_{x+1})\}$。由上文的结论可知，我们将 $n$ 为偶数的情况也转化成了 $n$ 为奇数的情况，也就是说，该序列一定有中心 $x$，而对应的 $b_x/c_x$ 就是答案。

所以问题转换为了区间最值，可以用st表维护。

中心 $x$ 可移动区间的边界还是挺恶心的，具体看代码吧。

（这个边界判断把人调麻了）

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#define il inline
using namespace std;
const int maxn=300010;
il int read(){
	int x=0;
	char c=getchar();
	for(;!(c>='0'&&c<='9');c=getchar());
	for(;c>='0'&&c<='9';c=getchar())
		x=(x<<1)+(x<<3)+c-'0';
	return x;
}
int a[maxn],b[maxn],c[maxn];
int f[2][maxn][20],n;
void init(int t){
	for(int i=1;i<=n;i++)
		if(!t)f[t][i][0]=b[i];
		else f[t][i][0]=c[i];
	for(int j=1;j<20;j++)
		for(int i=1;i+(1<<j)-1<=n;i++){
			f[t][i][j]=max(f[t][i][j-1],f[t][i+(1<<j-1)][j-1]);
			f[t][i][j]=max(f[t][i][j-1],f[t][i+(1<<j-1)][j-1]);
		}
} 
int Query(int t,int l,int r){
	int LOG=log2(r-l+1);
	return max(f[t][l][LOG],f[t][r-(1<<LOG)+1][LOG]);
}
int main(){
	n=read();
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1;i<=n;i++){
		b[i]=min(a[i],max(a[i+1],a[i-1]));
		c[i]=max(a[i],min(a[i+1],a[i-1]));
	}
	init(0),init(1);//维护两个st表
	int mid=n+1>>1;
	for(int k=0,K=0;k<n;k++,K=k>>1){
		bool fl=n-k&1^1;
		//fl表示提前取走k个后,剩余序列长度的奇偶性
		//也就是答案是b数组还是c数组
		if(n&1) printf("%d ",Query(fl,max(1,mid-K-fl),min(mid+K+fl,n)));
		else printf("%d ",Query(fl,max(1,mid-K),min(mid+K+1,n)));
	}
	return 0;
} 
```



---

## 作者：C20203030 (赞：3)

普及选手又来做省选题啦~~

注：作者只能帮助大家理解，有些地方可能不严谨，敬请谅解。

## 一、题目

[传送门](https://www.luogu.org/problem/CF794E)

## 二、解法

我们先考虑A不多吃的情况。

如果$n$为偶数，可以发现答案一定取$\max(a[mid],a[mid+1])$，为什么呢？考虑还有更大的$a[i]$在其他地方，那么B都可以通过他的$n/2-1$次机会取走，所以只有$mid$和$mid+1$对于B来说是无能为力的，而A会根据$a[mid],a[mid+1]$的大小来决定先取哪一边。

如果$n$为奇数，可以发现答案为$\max(\min(a[i],a[i-1]),\min(a[i],a[i+1]))$，因为A先取之后问题就变成了B先取，从而变成了$n$为偶数的情况，A取哪边对应了两种$\min$的取值，将他们取$\max$即可。

得到了A不多吃的情况，我们再考虑让A多吃的变化。

发现A多吃影响的是中间的取值，对于每一个被A吃过剩下的序列，我们找出它所有可能的中间点取值即可得到答案，这个过程考虑动态规划。

设$ans[k]$为剩下$k$个元素能取到的最大值，我们枚举$i\in [1,n/2]$，奇偶讨论，则有：

$ans[2i]=\max(ans[2i+2],dp1[i])$
$ans[2i+1]=\max(ans[2i+3],dp2[i])$

其中$dp[1/0][i]$表示中间点取$i$的答案，要考虑到最左边和最右边为端点，$dp$将两种情况整合到了一起。

我们可以将这个方程理解为每次多增加一个中间点的取值，其他的取值继承上一个状态。

最后倒着输出$ans$，时间复杂度$O(n)$。

最后附上简洁却不简单的代码。

```cpp
#include <cstdio>
#include <iostream>
using namespace std;
const int MAXN = 300005;
int n,a[MAXN],dp1[MAXN/2],dp2[MAXN/2],ans[MAXN];
int main()
{
    scanf("%d",&n);
    for(int i=1; i<=n; i++)
    {
        scanf("%d",&a[i]);
        ans[1]=max(ans[1],a[i]);
    }
    for(int i=1; i<n; i++)
        dp1[min(i,n-i)]=max(dp1[min(i,n-i)],max(a[i],a[i+1]));
    for(int i=2; i<n; i++)
        dp2[min(i-1,n-i)]=max(dp2[min(i-1,n-i)],max(min(a[i-1],a[i]),min(a[i],a[i+1])));
    for(int i=n/2; i>=1; i--)
    {
        ans[i<<1]=max(ans[(i+1)<<1],dp1[i]);
        ans[i<<1|1]=max(ans[(i+1)<<1|1],dp2[i]);
    }
    for(int i=n; i>=1; i--)
        printf("%d ",ans[i]);
}


```



---

## 作者：do_it_tomorrow (赞：2)

[更好的阅读体验](https://www.doittomorrow.xyz/post/cf794e-choosing-carrot-de-ti-jie/)

## 题目大意

给你一个序列，A 和 B 一次轮流操作，A 希望答案剩余的最大，B 希望答案最小，但是所有的操作都需要满足操作实在端点。

对于 $\forall k\in[1,n]\cap \mathbb{Z}$ ，重新开始一局游戏，A 先在满足要求的情况下选取 $k$。

其中数据范围满足，$1\le n\le 3\times 10^5$。

## 思路

某大佬曾经说过，如果一方用一个简单的操作就能达到某种结果，那他的最终结果不会更差。

对于权值博弈则可以延申为：如果先手能保证不小于某个值，后手能保证不大于某个值，那么答案就是这个。

定义 $mid=\lfloor \dfrac{1+n}{2}\rfloor$，那么**对于 $k=0$ 的情况**，答案的取值如下：

$$
ans=\left\{\begin{matrix}
\max(a_{mid},a_{mid+1}) & n\text{ is even}\\
\max(\min(a_{mid},a_{mid-1}),\min(a_{mid},a_{mid+1}))  & n\text{ is odd}
\end{matrix}\right.\mathbb{} 
$$

**先证明 $n$ 是偶数是的正确性：**

首先 A 可以选择 $a_{mid},a_{mid+1}$ 中最大值的位置 $p$ 与 $1,n$ 中距离较远的位置选择，接着和 B 进行对称的操作，这样就可以保证在选择了 $n-2$ 次只剩 $a_{p-1},a_p$ 或者 $a_p,a_{p+1}$。

接着 A 只需要选择 $a_{p-1}$ 或者 $a_{p+1}$ 就一定可以剩余 $a_p$。

根据某个某个大佬总结的性质，因为 A 可以将答案牢牢控制在 $a_p$，所以这一定是最优解。

**再证明 $n$ 是奇数的情况的正确性：**

首先 A 可以选择 $a_1$ 或者 $a_n$，那么问题就转化为了 $n$ 是偶数的情况，区别只有 B 希望答案更小。

同样的，B 可以使用上面的方法将最后的取值控制在 $\min(a_{mid'},a_{mid'+1})$，其中 $mid'$ 为 A 选择后中间的位置。

容易得到 $mid'=mid$ 或 $mid'=mid-1$，所以答案就是 $\max(\min(a_{mid},a_{mid-1}),\min(a_{mid},a_{mid+1}))$。

**对于 $k\ne 0$ 的情况**，容易想出 A 率先吃肯定只有 $mid$ 的值会受到影响，考虑计算出每一个 $k$ 可以影响的 $mid$ 的取值取值范围。

对于 $k$ 个全部取在左边的情况，$mid=\lfloor \dfrac{n-k+1}{2}\rfloor+k$ 。

同理对于 $k$ 全部取在右边的情况，$mid=\lfloor \dfrac{n-k+1}{2}\rfloor$。

设 $x=\lfloor \dfrac{n-k+1}{2}\rfloor$，那么答案为：

$$
\left\{\begin{matrix}
\max \limits _{{\tiny i=\lceil \dfrac{n-k}{2}\rceil }}^{{\tiny \lceil \dfrac{n+k}{2}\rceil}} a_i& n-k\text{ is odd}\\
\max  \limits_{{\tiny i=\lfloor \dfrac{n-k}{2}\rfloor -1}}^{{\tiny \lfloor \dfrac{n+k}{2}\rfloor}} (\min(a_{i},a_{i+1}))&n-k\text{ is even}
\end{matrix}\right.
$$
另外 $k=n-1$ 的情况需要特判，应为在 A 拿完之后游戏就直接结束了，所以答案为 $\max\limits_{i=1}^{n}a_i$。

[Submission #273106358 - Codeforces](https://codeforces.com/contest/794/submission/273106358)

---

## 作者：nydzsf_qwq (赞：2)

题外话：这题CF评2800感觉有点高了啊

### 题目大意

一排 $n$ 个数，甲乙轮流取，甲先取，每次取的时候都只能从两端取，直到只剩一个数为止。

甲希望剩下的最大，乙希望剩下的最小。

在正式开始之前甲还可以按照同样的规定先取 $k$ 个数，问对于每个 $k$ 剩下的都会是多少。

### 题解：

定义 $mid$ 是最中间的数（$mid=\left[\dfrac{n+1}{2}\right]$）

当 $n$ 是偶数的时候，乙可以采用这样的策略：如果甲取第一个，就取最后一个，如果甲取最后一个，就取第一个，甲最后一个取的时候一定只剩下最中间两个数，因此乙可以让剩下的数不高于 $\max\left\{a_{mid},a_{mid+1}\right\}$。

而甲也可以采用这样的策略：如果 $a_{mid}>a_{mid+1}$，那么第一次取最后一个，否则第一次取第一个，之后每次和乙上一次操作不在同一端取（和上面乙的策略类似），最后就可以留下 $\max\left\{a_{mid},a_{mid+1}\right\}$。所以甲也可以保证最后剩下的数不低于 $\max\left\{a_{mid},a_{mid+1}\right\}$。

因此 $n$ 是偶数时最后剩下的会是 $\max\left\{a_{mid},a_{mid+1}\right\}$。

类似地可以得到 $n$ 是奇数时最后会剩下 $\max\left\{\min\left\{a_{mid-1},a_{mid}\right\},\min\left\{a_{mid},a_{mid+1}\right\}\right\}$。

$k=0$ 的时候的问题就解决了。

$k=1$ 时答案时甲刚开始可以取第一个和最后一个，分别计算结果取最大值。

$k\ge 2$ 时用 $k-2$ 推 $k$，取 $k$ 个时可能的答案比 $k-2$ 时多两个。

以上步骤都要分奇偶。

**注意：$k=n-1$ 时比较特殊，因为最后只剩一个数，结果应该是 $\max\left\{a_{i}\right\}$，要特判！！！**

### 代码

```cpp
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
using namespace std;
inline int max(int a,int b,int c) {
	return max(a,max(b,c));
}
int n,a[300005],ans[300005],mid;
int main() {
	scanf("%d",&n);
	for(int i=1;i<=n;++i) scanf("%d",&a[i]),ans[n-1]=max(ans[n-1],a[i]); //k=n-1 特判
	a[0]=a[n+1]=inf;
	mid=(n+1)/2;
	if(n&1) { //n 是奇数
		ans[0]=max(min(a[mid-1],a[mid]),min(a[mid],a[mid+1])); //k=0
		ans[1]=max(a[mid-1],a[mid],a[mid+1]); //k=1
		for(int i=2;i<=n-2;++i)
			if(i&1) ans[i]=max(ans[i-2],a[mid+i/2+1],a[mid-i/2-1]);
			else ans[i]=max(ans[i-2],min(a[mid+i/2],a[mid+i/2+1]),min(a[mid-i/2],a[mid-i/2-1]));
			//k-2 推 k，要分奇偶
		for(int i=0;i<n;++i) printf("%d ",ans[i]);
	}
	else { //n 是偶数
		ans[0]=max(a[mid],a[mid+1]); //k=0
		ans[1]=max(min(a[mid-1],a[mid]),min(a[mid],a[mid+1]),min(a[mid+1],a[mid+2])); //k=1
		for(int i=2;i<=n-2;++i)
			if(i&1) ans[i]=max(ans[i-2],min(a[mid+i/2+1],a[mid+i/2+2]),min(a[mid-i/2],a[mid-i/2-1]));
			else ans[i]=max(ans[i-2],a[mid+i/2+1],a[mid-i/2]);
			//k-2 推 k，同样要分奇偶
		for(int i=0;i<n;++i) printf("%d ",ans[i]);
	}
	return 0;
}
```

---

## 作者：xwh_hh (赞：1)

不难想到区间 dp 吧。  
考虑设状态 $s_{i,j,k}$ 表示剩余区间 $[i,j]$ 时最终答案（$k=0$ 表示当前轮到 Oleg，$k=1$ 表示当前轮到 Igor）。  
转移时分类讨论拿掉哪堆即可，时间复杂度 $O(n^2)$。  
[代码](https://www.luogu.com.cn/paste/955jcf5w)  
然后第 $11$ 个点 RE 了。  
我们来打个表：  
[打表代码](https://www.luogu.com.cn/paste/cnernk0v)  
输入：
```
12
1 3 2 4 5 7 6 8 18 3 6 8
```
输出：
![](https://cdn.luogu.com.cn/upload/image_hosting/teyijnlf.png)
不难发现副对角线方向经过若干次 dp 后将保持不变。
故可 dp $t$ 轮，然后用 $sum_i$ 记录 $s_{j,i-j}$ 保持不变的值，这部分复杂度降至 $O(tn)$。
统计答案时，我们发现 $k$ 固定时剩余区间长度固定为 $n-k$。设 $ans_i$ 表示剩余区间长为 $i$ 时的答案，可设剩余区间为 $[l,l+n-k-1]$，得：
$$ans_i=\max_{r=0}^{n-i}sum_{2r+i+1}$$
直接算仍然是 $O(n^2)$，不过我们发现：
$$ans_i=\max\{sum_{i+1},sum_{i+3},\dots,sum_{2n-i-1}\}$$
$$ans_{i+2}=\max\{sum_{i+3},sum_{i+5},\dots,sum_{2n-i-3}\}$$
我们发现 $ans_i=\max\{ans_{i+2},sum_{i+1},sum_{2n-i-1}\}$，通过迭代，可将这部分复杂度降至 $O(n)$。  
总时间 $O(tn)$，取 $t=8$ 即可。  
代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int s[300005][10][2];//0:当前Olen 1:当前Igor 
int n; 
int l[300005],r[300005];
int ans[300005];
int sum[600005];
int main(){
	cin>>n;
	int mx=-0x3f3f3f3f;
	for(int i=1;i<=n;i++){
		cin>>s[i][0][0];
		s[i][0][1]=s[i][0][0];
		mx=max(mx,s[i][0][0]);
	}
	for(int len=1;len<9;len++){//先dp8轮，确保正确性 
		int now=0;
		for(int i=1;i<=n;i++){
			int j=i+len;
			if(j>n) break;
			s[i][len][0]=max(s[i][len-1][1],s[i+1][len-1][1]);
			s[i][len][1]=min(s[i][len-1][0],s[i+1][len-1][0]);
			now=max(now,s[i][len][0]);
			sum[i+j]=s[i][len][0];
		}
	}
	if(n==1){
		cout<<mx;
		return 0;
	}
	ans[1]=sum[n+1];
	ans[2]=max(sum[n],sum[n+2]);
	for(int len=n-3;len;len--){//算ans，应该不难吧 
		ans[n-len]=max(ans[n-len-2],max(sum[len+2],sum[2*n-len]));
	}
	ans[n]=mx;
	for(int i=1;i<=n;i++) cout<<ans[i]<<' ';
	return 0;
}
```

---

## 作者：_Cheems (赞：1)

先不考虑 A 提前拿走数。

注意到后手比较厉害，可以做先手相反的操作使得每一轮恰好两侧的数被扔掉。

记 $mid=\frac{l+r}2$。当 $2\mid n$ 时，B 可以使得答案 $\le \max(a_{mid},a_{mid+1})$。A 可以一开始拿走左侧的然后与 B 做相反操作然后得到 $a_{mid+1}$，$a_{mid}$ 同理。故答案为 $\max(a_{mid},a_{mid+1})$。

上述讨论在 B 先手时是对偶情况，可以推出当 $2\nmid n$ 时答案是 $\max(\min(a_{mid-1},a_{mid}),\min(a_{mid},a_{mid+1}))$。注意 $n=1$ 的特殊情况。

加入修改，那么就是对所有 $n-k$ 大小的区间取个 $\max$，显然有个 $st$ 表做法，考虑 $mid$ 的下标范围即可。

但是还有更简单的线性做法，注意到将区间两侧同时缩短 $1$ 答案不变，那么可以递推，$k$ 必然可以继承 $k-2$ 的所有情况（每个区间缩短两侧），然后只需加入两侧的区间答案即可。

复杂度 $O(n)$。
#### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long
const int N = 3e5 + 5;
int n, a[N], ans[N], mx;

inline int get(int l, int r){
	int mid = (l + r) >> 1;
	if((r - l) & 1) return max(a[mid], a[mid + 1]);
	return max(min(a[mid - 1], a[mid]), min(a[mid], a[mid + 1])); 
}
signed main(){
	cin >> n;
	for(int i = 1; i <= n; ++i) scanf("%lld", &a[i]), mx = max(mx, a[i]);
	ans[0] = get(1, n);
	ans[1] = max(get(1, n - 1), get(2, n));
	for(int i = 2; i < n - 1; ++i) ans[i] = max(ans[i - 2], max(get(1, n - i), get(i + 1, n)));
	for(int i = 0; i < n; ++i) printf("%lld ", (i < (n - 1)) ? ans[i] : mx); 
	return 0;
}
```

---

## 作者：andychen_2012 (赞：0)

首先可以考虑区间 dp。

设 $f_{l,r,0/1}$ 表示考虑第 $l$ 堆到第 $r$ 堆，由 A/B 先手能拿到的青草。设 $ans_x$ 表示 A 提前操作了 $n-x$ 次，**留下**了 $x$ 堆草的答案。
$$
f_{l,r,0}=\max(f_{l+1,r,1},f_{l,r-1,1})\\
f_{l,r,1}=\min(f_{l+1,r,0},f_{l,r-1,0})
$$

$$
ans_x=\max\{f_{l,l+x-1,0} \}
$$

删去第三维。有
$$
f_{l,r}=\min(f_{l+1,r-1},\max(f_{l+2,r},f_{l,r-2}))
$$
只留第一维，奇偶分别算，滚动数组，有
$$
f_l=\min(f_{l+1},\max(f_{l+2},f_{l}))
$$
我们将 $f$ 的第一维变为区间长度，则有
$$
f_{x,l}=\min(f_{x-2,l+1},\max(f_{x-2,l+2},f_{x-2,l}))
$$
对 $x$ 分奇偶讨论，以下是 $x$ 为奇数的情况：

当 $x=1$ 时，$f_{1,i}=a_i$。

当 $x=3$ 时，$f_{3,i}=\min(a_{i+1},\max(a_{i},a_{i+2}))$。

当 $x=5$ 时，$f_{5,i}=\min(\min(a_{i+2},\max(a_{i+1},a_{i+3})),\max(f_{3,i},f_{3,i+2}))$。我们对后面的部分展开，得到
$$
\begin{align}
\max(f_{3,i},f_{3,i+2})&=\max(\min(a_{i+1},\max(a_{i},a_{i+2})),\min(a_{i+3},\max(a_{i+2},a_{i+4})))\\
&=\min(\max(a_{i+1},a_{i+3}),\max(a_{i},a_{i+2},a_{i+4}))
\end{align}
$$
因此
$$
f_{5,i}=\min(\max(a_{i+1},a_{i+3}),\max(a_{i},a_{i+2},a_{i+4}))
$$
可以看出
$$
ans_x=\max(ans_{x+2},\max(f_l,f_r))
$$
其中 $f_l=f_{3,l-1}$，同理有 $f_r=f_{3,r-1}$。一开始，$l=\lceil \frac{n}{2} \rceil,r=\lfloor \frac{n}{2} \rfloor+1$。每次 $x$ 减 2 后 $l \leftarrow l-1,r \leftarrow r+1$。

以下是 $x$ 为偶数的情况：

当 $x=2$ 时，$f_{2,i}=\max(a_i,a_{i+1})$。

当 $x=4$ 时，$f_{4,i}=\min(\max(a_{i+1},a_{i+2}),\max(a_i,a_{i+1},a_{i+2},a_{i+3}))=\max(a_{i+1},a_{i+2})$。

当 $x=6$ 时，$f_{6,i}=\min(\max(a_{i+2},a_{i+3}),\max(a_{i+1},a_{i+2},a_{i+3},a_{i+4}))=\max(a_{i+2},a_{i+3})$。

以此类推，当 $x$ 为偶数时，可以得到一个递推数组 $f$ 满足 $f_{x,i}=f_{x-2,i+1}$。因此可以倒着计算 $ans_x$，每次枚举扩展区间大小。
$$
ans_x=\max(ans_{x+2},\max(f_l,f_r))
$$
其中 $f_l=f_{2,l}$，同理有 $f_r=f_{2,r}$。一开始，$l=\lfloor \frac{n}{2} \rfloor,r=\lceil \frac{n}{2} \rceil$。每次 $x$ 减 2 后 $l \leftarrow l-1,r \leftarrow r+1$。

当然，最后要倒着输出 $ans_x$。时间复杂度 $O(n)$。

主要代码：

```cpp
n=read();
for(int i=1;i<=n;++i) a[i]=read();
for(int i=1;i<=n;++i) ans[1]=max(ans[1],a[i]);
for(int i=2;i<n;++i) f[i]=min(a[i],max(a[i-1],a[i+1]));
if((n>1)&&n&1){
	int l=n/2+1,r=l;
	ans[n]=f[l];
	for(int i=n-2;i>=3;i-=2){
		--l,++r;
		ans[i]=max(ans[i+2],max(f[l],f[r]));
	}
}
else if(n>2){
	int l=n/2,r=l+1;
	ans[n-1]=max(f[l],f[r]);
	for(int i=n-3;i>=3;i-=2){
		--l,++r;
		ans[i]=max(ans[i+2],max(f[l],f[r]));
	}
}
ans[2]=ans[1];
for(int i=1;i<=n-1;++i) f[i]=max(a[i],a[i+1]);
if((n>=4)&&n&1){
	int l=n/2,r=l+1;
	ans[n-1]=max(f[l],f[r]);
	for(int i=n-3;i>=4;i-=2){
		--l,++r;
		ans[i]=max(ans[i+2],max(f[l],f[r]));
	}
}
else if(n>=4){
	int l=n/2,r=l;
	ans[n]=max(f[l],f[r]);
	for(int i=n-2;i>=4;i-=2){
		--l,++r;
		ans[i]=max(ans[i+2],max(f[l],f[r]));
	}
}
for(int i=n;i>=1;--i) write(ans[i],' ');
return 0;
```

---

