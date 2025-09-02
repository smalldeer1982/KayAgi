# [USACO20DEC] Sleeping Cows P

## 题目描述


Farmer John 有 $N$（$1≤N≤3000$）头各种大小的奶牛。他原本为每头奶牛量身定制了牛棚，但现在某些奶牛长大了，使得原先的牛棚大小不够用。具体地说，FJ 原来建造了 $N$ 个牛棚的大小为 $t_1,t_2,…,t_N$，现在奶牛的大小为 $s_1,s_2,…,s_N$（$1≤s_i,t_i≤10^9$）。

每天晚上，奶牛们都会按照某种方式寻找睡觉的牛棚。奶牛 $i$ 可以睡在牛棚 $j$ 中当且仅当她的大小可以进入牛棚（$s_i≤t_j$）。每个牛棚中至多可以睡一头奶牛。

我们称奶牛与牛棚的一个匹配是极大的，当且仅当每头奶牛可以进入分配给她的牛棚，且对于每头未被分配牛棚的奶牛无法进入任何未分配的空牛棚。

计算极大的匹配的数量模 $10^9+7$ 的结果。 

## 说明/提示

以下是全部九种极大的匹配。有序对 $(i,j)$ 表示奶牛 $i$ 被分配到了牛棚 $j$。

```
(1, 1), (2, 2), (3, 4)
(1, 1), (2, 3), (3, 4)
(1, 1), (2, 4)
(1, 2), (2, 3), (3, 4)
(1, 2), (2, 4)
(1, 3), (2, 2), (3, 4)
(1, 3), (2, 4)
(1, 4), (2, 2)
(1, 4), (2, 3)
```

 - 测试点 2-3 中，$N≤8$。
 - 测试点 4-12 中，$N≤50$。
 - 测试点 13-20 没有额外限制。

供题：Nick Wu 

## 样例 #1

### 输入

```
4
1 2 3 4
1 2 2 3```

### 输出

```
9```

# 题解

## 作者：CXY07 (赞：23)

## 动态规划优化

> 题目链接：[P7154 [USACO20DEC] Sleeping Cows P](https://www.luogu.com.cn/problem/P7154)

> **本题解同步发布于 [My Blog](http://www.cxy07.blog/index.php/archives/60/)**

题意：

> 现给定长度均为 $n$ 的数组 $s_i$ 与 $t_i$，$s_i$ 能与 $t_j$ 匹配当且仅当 $s_i\le t_j$。一组匹配是极大的，当且仅当对于任意一个匹配对 $(s_i,t_j)$ 均满足 $s_i\le t_j$ ，且任意未被匹配的 $s$ 与 $t$ 中无法再组成匹配对。

> 求所有极大匹配的方案数。

> $n\le 3000,s_i,t_i\le 10^9$。

考虑将 $s$ 与 $t$ 都从小到大排序，那么对于一个 $t_i$，能与之匹配的 $s_j$ 应该是 $s$ 的一段前缀。

那么考虑从小到大讨论每一个 $t$，每一个 $t$ 有两种选择：选择一个合法的 $s$ 与之匹配，或放弃将这个 $t$ 加入匹配。

不难发现，当我们将 $t$ 升序排序后，对于一个 $s_j$，若其可与 $t_i$ 匹配，那么一定可以与 $t_{i+1}$ 匹配。此时考虑什么情况下，我们才可以选择放弃将当前的 $t$ 加入匹配。

若当前 $t_i$ 所能匹配的 $s$ 的最大下标为 $\text{lim}_ i$，那么若要放弃 $t_i$，则 $s_1$ 到 $s_{\text{lim}_ i}$ 均需要被匹配。因为如果放弃 $t_i$ 且放弃 $s_1$ 到 $s_{\text{lim}_ i}$ 中的任意一个，那么他们一定可以组成一个新的匹配对，这是我们不希望看到的。

也就是说，当存在一个 $s_i$ 被放弃加入匹配时，任意满足 $i\le \text{lim}_ j$ 的 $t_j$ 都**不可以被放弃**。

同时，我们实际上只关注最小的，被放弃的 $s_i$。那么一个 $\mathcal{O}(n^3)$ 的算法就很显然了：

考虑最小的被放弃的 $s_i$ 是谁，那么对于任意 $j < i$ 的 $s_j$ 都需要加入匹配，$\text{lim}_ j \ge i$ 的 $t_j$ 均不能放弃。$\mathcal{O}(n)$ 枚举 $s_i$ 后可以通过 $\mathcal{O}(n^2)$ 的 $\text{dp}$ 解决。

考虑在这个思路上进行优化。实际上，我们并不需要枚举 $s_i$ 是谁，而是只关心 $s$ 的一个前缀是否全部加入了匹配。也就是说，我们可以将上面枚举 $s_i$ 的过程转变为一个 $\text{bool}$ 变量 $0/1$ 表示某一个前缀是否全部选入。

那么可以维护两个指针，分别指向当前还未考虑的最小的 $s$ 与 $t$，每次选择较小的一边进行更新，特殊地，对于 $s=t$ 的情形，则优先更新 $s$ 一边。

更简单的实现方法，可以将两个数组合并为一个，进行双关键字排序，依次分类讨论更新即可。以下的 $\text{dp}$ 均在这个新的数组上进行讨论。

考虑 $\text{dp}$，设 $\text{dp}_ {i,j,0/1}$ 表示考虑到第 $i$ 个位置，目前有 $j$ 个被选入匹配，但是还未选定匹配谁的 $s$，$1$ 到 $i-1$ 位置中的 $s$ 是否都被选择加入的方案数，其中第三位的 $1$ 表示前缀中的 $s$ 全部加入匹配。

那么可以分类进行转移：

若第 $i$ 个位置是 $s$ 中的元素，那么：

$$\text{dp}_ {i,j,0}=\text{dp}_ {i-1,j-1,0}+\text{dp}_ {i-1,j,0}+\text{dp}_ {i-1,j,1}$$

$$\text{dp}_ {i,j,1}=\text{dp}_ {i-1,j-1,1}$$

可以考虑是否将这个 $s$ 加入匹配，若加入，则 $j\leftarrow j+1$ ，否则不变。需要注意的是若选择放弃当前 $s$ 则第三位必然为 $0$。

若第 $i$ 个位置是 $t$ 中的元素，那么：

$$\text{dp}_ {i,j,0}=\text{dp}_ {i-1,j+1,0}\times (j+1)$$

$$\text{dp}_ {i,j,1}=\text{dp}_ {i-1,j,1}+\text{dp}_ {i-1,j+1,1}\times (j+1)$$

若当前第三位为 $0$，那么不能放弃当前 $t$，$j\leftarrow j-1$，同时从当前所有还未确定的 $s$ 中选择一个与当前 $t$ 匹配；若第三位为 $1$，则可以选择放弃当前位，同样也可以选择进行一次匹配。

最后的答案就是：

$$\text{dp}_ {n,0,0}+\text{dp}_ {n,0,1}$$

也就是最后没有在匹配中，却未选择与谁匹配的 $s$。

时间复杂度 $\mathcal{O}(n^2)$。

$\texttt{Code:}$

```cpp
//Code By CXY07
#include<bits/stdc++.h>
using namespace std;

//#define FILE
#define int long long
#define debug(x) cout << #x << " = " << x << endl
#define file(FILENAME) freopen(FILENAME".in", "r", stdin), freopen(FILENAME".out", "w", stdout)
#define LINE() cout << "LINE = " << __LINE__ << endl
#define LL long long
#define ull unsigned long long
#define pii pair<int,int>
#define mp make_pair
#define pb push_back
#define fst first
#define scd second
#define inv(x) qpow((x),mod - 2)
#define lowbit(x) ((x) & (-(x)))
#define abs(x) ((x) < 0 ? (-(x)) : (x))
#define randint(l, r) (rand() % ((r) - (l) + 1) + (l))
#define vec vector

const int MAXN = 6010;
const int INF = 2e9;
const double PI = acos(-1);
const double eps = 1e-6;
const int mod = 1e9 + 7;
//const int mod = 998244353;
//const int G = 3;
//const int base = 131;

int n, m;
int dp[2][MAXN][2]; //dp[i][j][0/1] 还有j头牛需要加入，是否填满
int now, pre = 1;//滚动数组
pii s[MAXN];

template<typename T> inline bool read(T &a) {
	a = 0; char c = getchar(); int f = 1;
	while(c < '0' || c > '9') {if(c == '-') f = -1; c = getchar();}
	while(c >= '0' && c <= '9') {a = a * 10 + (c ^ 48); c = getchar();}
	a *= f;
	return 1;
}

template<typename A, typename ...B>
inline bool read(A &x, B &...y) {return read(x) && read(y...);}

signed main () {
#ifdef FILE
	freopen(".in","r",stdin);
	freopen(".out","w",stdout);
#endif
	read(n);
	for(int i = 1; i <= n; ++i) read(s[i].fst), s[i].scd = 0;
	for(int i = 1; i <= n; ++i) read(s[i + n].fst), s[i + n].scd = 1;
	sort(s + 1, s + n * 2 + 1);
	dp[now][0][1] = 1;
	for(int i = 1; i <= n * 2; ++i) {
		swap(now, pre);//滚动数组
		memset(dp[now], 0, sizeof dp[now]);
		if(!s[i].scd) {//若当前是 s 中元素
			for(int j = 0; j <= n; ++j) {
				if(j) (dp[now][j][0] += dp[pre][j - 1][0]) %= mod;
				if(j) (dp[now][j][1] += dp[pre][j - 1][1]) %= mod;
				(dp[now][j][0] += dp[pre][j][0] + dp[pre][j][1]) %= mod;
			}
		} else {//若当前是 t 中元素
			for(int j = 0; j <= n; ++j) {
				(dp[now][j][1] += dp[pre][j][1]) %= mod;
				(dp[now][j][1] += dp[pre][j + 1][1] * (j + 1) % mod) %= mod;
				(dp[now][j][0] += dp[pre][j + 1][0] * (j + 1) % mod) %= mod;
			}
		}
	}
	printf("%lld\n", ((dp[now][0][0] + dp[now][0][1]) % mod + mod) % mod);
	return 0;
}
```

---

## 作者：¶凉笙 (赞：15)

## [题解] P7154 [USACO20DEC] Sleeping Cows P

> [点此看题](https://www.luogu.com.cn/problem/P7154)

> [不一定更好的阅读体验](https://www.cnblogs.com/Liang-sheng/p/15165901.html)

### 解题报告

> 有 $n$ 头奶牛和 $n$ 个牛棚，一个奶牛 $u_i$ 能进入一个牛棚 $v_i$ 当且仅当 $s_{u_i}\leq t_{v_i}$，一个牛棚最多只能容纳一头牛。
>
> 定义一个完美匹配为：**对于所有未分配的奶牛，都不能有任何一个未匹配的牛棚满足条件**，求完美匹配的方案数。

关键是找到那些没有匹配的牛棚来计算。

考虑把 $s$ 和 $t$ 都放到一起排序，这样做的好处就是：对于一个牛棚，如果前面有不需要匹配的牛，那么这个牛棚必须匹配一头牛。

于是设计状态为 $f[i,j,0/1]$ 表示当前考虑了前 $i$ 个元素，有 $j$ 头牛**准备被分配到牛棚里但是还没有分配**，**$0/1$** 表示有没有丢掉牛（不匹配的牛），$0$ 表示有，$1$ 表示没有。

注意：$j$ 和第三维的 $0/1$ **没有任何关系**。

初始为 $f[0][0][1]=1$，因为任何牛都没有丢掉。

> 状态转移

设考虑到了第 $i$ 个位置。

- 第 $i+1$ 位置为牛。

$f[i,j,0]->f[i+1,j+1,0],f[i+1,j,0]$

$f[i,j,1]->f[i+1,j+1,1],f[i+1,j,0]$​​

分为下一轮丢没丢奶牛进行考虑。

- 第 $i+1$ 个位置为牛棚。

$j\times f[i,j,0]->f[i+1,j-1,0]$

$j\times f[i,j,1]->f[i+1,j-1,1]$

$f[i,j,1]->f[i+1,j,1]$

前两种情况是考虑把当前需要分配的 $j$ 头牛分配进去。

第三种情况是这个牛棚直接作废。

注意：**如果当前丢掉了一些奶牛，那么这个牛棚必须被填满，所以 $f[i,j,0]$ 是无法转移到 $f[i+1,j,0]$ 的。**

```c++
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
template <typename T>
inline T read(){
    T x=0;char ch=getchar();bool fl=false;
    while(!isdigit(ch)){if(ch=='-')fl=true;ch=getchar();}
    while(isdigit(ch)){
        x=(x<<3)+(x<<1)+(ch^48);ch=getchar();
    }
  	return fl?-x:x;
}
#define LL long long
const int maxn = 3000 + 10;
const int P = 1e9 + 7;
struct node{
	int val,type;
	bool operator <(const node &x)const{
		if(val!=x.val)return val<x.val;
		return type<x.type;
	}
}a[maxn<<1];
int s[maxn],t[maxn],n;
int f[maxn<<1][maxn][2],ans;
inline void add(int &a,int b){
	a+=b;
	if(a>=P)a-=P;
}
#define read() read<int>()
int main(){
	n=read();
	for(int i=1;i<=n;i++)s[i]=read(),a[i]=(node){s[i],0};
	for(int i=1;i<=n;i++)t[i]=read(),a[i+n]=(node){t[i],1};
	sort(a+1,a+1+n*2);
	f[0][0][1]=1;
	for(int i=0;i<n*2;i++){
		if(a[i+1].type==0){
			for(int j=0;j<=n+1;j++){
				add(f[i+1][j+1][0],f[i][j][0]);
				add(f[i+1][j][0],f[i][j][0]);
				add(f[i+1][j+1][1],f[i][j][1]);
				add(f[i+1][j][0],f[i][j][1]);
			}
		}
		else {
			for(int j=0;j<=n+1;j++){
				if(j>0)add(f[i+1][j-1][0],1LL*j*f[i][j][0]%P);
				if(j>0)add(f[i+1][j-1][1],1LL*j*f[i][j][1]%P);
				add(f[i+1][j][1],f[i][j][1]);
			}
		}
	}
	ans=f[n*2][0][0]+f[n*2][0][1];ans%=P;
	printf("%d\n",ans);
	return 0;
}
```

> 小结

核心是放在一起排序DP，保证了**合法状态方便转移**。



---

## 作者：Rainybunny (赞：7)

&emsp;&emsp;[来这里看嘛~](https://www.cnblogs.com/rainybunny/p/14490990.html).

# $\mathcal{Description}$

&emsp;&emsp;[Link](https://www.luogu.com.cn/problem/P7154).

&emsp;&emsp;有 $n$ 个牛棚，大小为 $t_{1..n}$，$n$ 头奶牛，大小为 $s_{1..n}$，奶牛只能住进不小于自己的牛棚，每个牛棚最多住一头奶牛。求满足不能让更多奶牛住进牛棚的安排方案数，答案对 $(10^9+7)$ 取模。

&emsp;&emsp;$n\le3\times10^3$。

# $\mathcal{Solution}$

&emsp;&emsp;把 $s$ 和 $t$ 倒一块儿升序排序，大小相同奶牛优先。那么相当于奶牛只能住进自己后面的某个房间，转化成了熟悉的括号问题。

&emsp;&emsp;考虑一个方案合法的条件：**最左侧失配的左括号（奶牛）在最右侧失配的右括号（牛棚）右侧**（否则它们就能够再匹配了）。

&emsp;&emsp;接下来的 DP 就比较平凡啦，令 $f(i,j,0/1)$ 表示考虑了序列前 $i$ 个元素，有 $j$ 个左括号预定了接下来的右括号和它匹配，出现 / 未出现“最左侧失配的左括号”时的方案数。分第 $i$ 个位置是奶牛还是牛棚转移（$\longleftarrow$ 表示前者被后者贡献）：

- 奶牛转移：
    - 预定后方房间，$f(i,j,0/1)\longleftarrow f(i-1,j-1,0/1)$；
    - 成为最左侧失配，$f(i,j,1)\longleftarrow f(i-1,j,0)$；
    - 再次失配，$f(i,j,1)\longleftarrow f(i-1,j,1)$。
- 牛棚转移：
    - 去满足某个房间预定，$f(i,j,0/1)\longleftarrow (j+1)\cdot f(i-1,j+1,0/1)$；
    - 失配，$f(i,j,0)\longleftarrow f(i-1,j,0)$。

&emsp;&emsp;转移最后一步体现了合法限制。最后答案显然是 $f(2n,0,0)+f(2n,0,1)$。

&emsp;&emsp;最终，$\mathcal O(n^2)$ 解决问题。

## $\mathcal{Code}$

&emsp;&emsp;代码中最后一维 $0/1$ 状态是反过来的 awa。

```cpp
/* Clearink */

#include <cstdio>
#include <algorithm>

#define rep( i, l, r ) for ( int i = l, rpbound##i = r; i <= rpbound##i; ++i )
#define per( i, r, l ) for ( int i = r, rpbound##i = l; i >= rpbound##i; --i )

typedef std::pair<int, int> PII;
#define fi first
#define se second

const int MAXN = 3e3, MOD = 1e9 + 7;
int n, f[MAXN * 2 + 5][MAXN + 5][2]; // !!!
PII s[MAXN * 2 + 5];

inline int mul( const long long a, const int b ) { return a * b % MOD; }
inline int sub( int a, const int b ) { return ( a -= b ) < 0 ? a + MOD : a; }
inline int add( int a, const int b ) { return ( a += b ) < MOD ? a : a - MOD; }
inline void addeq( int& a, const int b ) { ( a += b ) >= MOD && ( a -= MOD ); }

int main() {
//	freopen ( "sleeping.in", "r", stdin );
//	freopen ( "sleeping.out", "w", stdout );
	scanf( "%d", &n );
	rep ( i, 1, n ) scanf( "%d", &s[i].fi ), s[i].se = 0;
	rep ( i, n + 1, n << 1 ) scanf( "%d", &s[i].fi ), s[i].se = 1;
	std::sort( s + 1, s + ( n << 1 | 1 ) );
	f[0][0][1] = 1;
	rep ( i, 1, n << 1 ) {
		if ( !s[i].se ) rep ( j, 0, n ) { // cow.
			if ( j ) {
				addeq( f[i][j][1], f[i - 1][j - 1][1] );
				addeq( f[i][j][0], f[i - 1][j - 1][0] );
			}
			addeq( f[i][j][0], add( f[i - 1][j][0], f[i - 1][j][1] ) );
		} else rep ( j, 0, n ) { // house.
			f[i][j][0] = mul( j + 1, f[i - 1][j + 1][0] );
			f[i][j][1] = add( mul( j + 1, f[i - 1][j + 1][1] ),
				f[i - 1][j][1] );
		}
	}
	printf( "%d\n", add( f[n << 1][0][0], f[n << 1][0][1] ) );
	return 0;
}

```


---

## 作者：Kubic (赞：7)

看到题解里没有跟我做法一样的，就来写一篇（

首先很容易想到把 $s,t$ 分别从小到大排序，不影响答案。

然后可以暴力统计出 $s$ 中每个数可以跟 $t$ 中多少数匹配（记为 $a_i$）。以及 $t$ 中每个数可以跟 $s$ 中多少数匹配（记为 $b_i$）。

接下来我们考虑枚举一个 $i$，并计算出所有未匹配的牛中编号最小值为 $i$ 时的方案数。

设这个 $i$ 可以匹配到的牛棚中编号最小值为 $t$。

此时我们发现，编号在 $[t,n]$ 中的牛棚必须被其它的牛匹配完毕，否则这个匹配就不是极大的。

现在有这样几种匹配方式：
- $[1,i)$ 中的牛匹配 $[1,t)$ 中的牛棚
- $[1,i)$ 中的牛匹配 $[t,n]$ 中的牛棚
- $(i,n]$ 中的牛匹配 $[t,n]$ 中的牛棚

显然 $[1,i)$ 中的每一头牛都可以与 $[t,n]$ 中的任何一个牛棚匹配。而 $[1,i)$ 中不与 $[t,n]$ 中某一个牛棚匹配的牛一定全部都与 $[1,t)$ 中某一个牛棚匹配。

我们就可以考虑枚举一个 $j$，并算出 $[1,i)$ 中的牛与 $[t,n]$ 中的牛棚一共匹配了 $j$ 对的方案数。

此时可以发现：
- $[1,i)$ 中剩下的牛有 $i-j-1$ 头，全部都与 $[1,t)$ 中的牛棚匹配。
- $[t,n]$ 中剩下的牛棚有 $n-t-j+1$ 个，全部都与 $(i,n]$ 中的牛匹配。

这样就可以利用很久之前算出的 $a,b$ 来预处理。

$f_{i,j}$ 表示 $[1,i]$ 中的**牛棚**与所有**牛**匹配 $j$ 对的方案数。

$g_{i,j}$ 表示 $[i,n]$ 中的**牛**与所有**牛棚**匹配 $j$ 对的方案数。

具体转移比较显然，可以看代码（

然后我们利用计算出的 $f,g$ 来求答案。枚举到 $i,j$ 时的答案就是 $f_{t-1,i-j-1}\times g_{i+1,n-t-j+1}\times j!$。其中 $j!$ 的意思就是 $[1,i)$ 中的牛与 $[t,n]$ 中的牛匹配 $j$ 对的方案数，因为可以任意匹配。

注意答案还要加上 $f_{n,n}$，表示全部牛都匹配完的方案数。

注：代码中变量名与题解中不太一样，$a1=s,a2=t,b1=a,b2=b,dp1=f,dp2=g$。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 3005
#define MOD 1000000007
int n,ans,fc[N],a1[N],a2[N],b1[N],b2[N],dp1[N][N],dp2[N][N];
int main()
{
    scanf("%d",&n);fc[0]=dp1[0][0]=dp2[n+1][0]=1;
    for(int i=1;i<=n;++i) fc[i]=1ll*fc[i-1]*i%MOD;
    for(int i=1;i<=n;++i) scanf("%d",&a1[i]);sort(a1+1,a1+n+1);
    for(int i=1;i<=n;++i) scanf("%d",&a2[i]);sort(a2+1,a2+n+1);
    for(int i=1;i<=n;++i) for(int j=1;j<=n;++j) if(a1[i]<=a2[j]) ++b1[i],++b2[j];
    for(int i=1;i<=n;++i)
    {
        dp1[i][0]=1;
        for(int j=1;j<=i;++j)
            dp1[i][j]=(dp1[i-1][j]+1ll*dp1[i-1][j-1]*max(b2[i]-j+1,0))%MOD;
    }
    for(int i=n;i;--i)
    {
        dp2[i][0]=1;
        for(int j=1;j<=n-i+1;++j)
            dp2[i][j]=(dp2[i+1][j]+1ll*dp2[i+1][j-1]*max(b1[i]-j+1,0))%MOD;
    }
    for(int i=1,t=1;i<=n;++i)
    {
        while(t<=n && a1[i]>a2[t]) ++t;
        for(int j=0;j<=min(i-1,n-t+1);++j)
            ans=(ans+1ll*dp1[t-1][i-j-1]*dp2[i+1][n-t-j+1]%MOD*fc[j])%MOD;
    }printf("%d\n",(ans+dp1[n][n])%MOD);return 0;
}
```

---

## 作者：Time_tears (赞：6)

来一篇比较简单的做法。

考虑一种方案如何被我们统计到，我们可以找到这个方案中最小的不在牛棚中的牛，显然这个牛是唯一的（或者没有这样的牛）。

所以总方案数是等价于我们去枚举体积最小的不在牛棚中的牛的合法方案数相加。

将牛从小到大排序，令枚举的这个牛为 $x$，第一个大于等于 $x$ 的牛棚 $a$，现在我们要满足的条件就是：

1. 比 $x$  小的 $x-1$ 个牛必须都在牛棚中。

1. $a$ 与比 $a$ 大的所有牛棚都必须有牛。

再来考虑牛与牛棚的对应方法，共三种：

1. 比 $x$ 小的与比 $a$ 小的。

1. 比 $x$ 大的与比 $a$ 大的。

1. 比 $x$ 小的与比 $a$ 大的。

注意到第三种对应方式非常特殊，当我们确定了有 $j$ 个在其中对应了之后它的方案数就有 $j!$ 种。

所以我们设计两个 Dp $f_{i,j},g_{i,j}$ 分别表示在比 $i$ 大的牛中选 $j$ 个去对应牛棚的方案数，在比 $i$ 小的所有牛棚中选 $j$ 个去装牛的方案数。($f$ 从 $n$ 推到 $0$)

设比牛 $i$ 大的牛棚数为 $a_i$，比牛棚 $i$ 小的牛棚数为 $b_i$

那么可以很好的列出 $f_{i,j},g_{i,j}$ 的转移式：

$f_{i-1,j}+=f_{i,j},f_{i-1,j+1}+=f_{i,j} \times (a_{i-1}-j)$ （就是枚举这个牛选与不选牛棚）

$g$ 的转移式同理。


算出 $f,g$ 后我们只需枚举最小的不在牛棚中的牛 $i$ ,以及第三种对应关系有 $j$ 个然后就可以 $O(1)$ 计算，总复杂度 $O(n^2)$。

```cpp
#include<bits/stdc++.h>
#define N 3005
using namespace std;
const int mod=1e9+7;
int n,f[N][N],g[N][N],ans;
int s[N],t[N],a[N],b[N],fac[N];
inline int Mod(int x) {return x<mod?x:x-mod;}
int main() {
	cin>>n;
	for(int i=1; i<=n; ++i)cin>>s[i];
	for(int i=1; i<=n; ++i)cin>>t[i];
	for(int i=fac[0]=1; i<=n; ++i)fac[i]=1ll*fac[i-1]*i%mod;
	sort(s+1,s+n+1),sort(t+1,t+n+1);
	for(int i=n,j=n+1; i; --i){while(j>1&&t[j-1]>=s[i])--j;a[i]=n+1-j;}//算一个牛有多少个比它大的牛棚
	for(int i=1,j=0; i<=n; ++i) {while(j<n&&s[j+1]<=t[i])++j;b[i]=j;}//算一个牛棚有多少个比它小的牛
	f[n+1][0]=g[0][0]=1;
	for(int i=n+1; i; --i)
		for(int j=0; j<=n-i+1; ++j)f[i-1][j]=Mod(f[i-1][j]+f[i][j]),f[i-1][j+1]=(f[i-1][j+1]+1ll*f[i][j]*(a[i-1]-j))%mod;
	for(int i=0; i<=n; ++i)
		for(int j=0; j<=i; ++j)g[i+1][j]=Mod(g[i+1][j]+g[i][j]),g[i+1][j+1]=(g[i+1][j+1]+1ll*g[i][j]*(b[i+1]-j))%mod;
	ans=g[n][n];
	for(int i=1; i<=n; ++i)//枚举大小最小的不在牛棚中的牛
		for(int j=0; j<=i-1&&j<=a[i]; ++j)ans=(ans+1ll*f[i+1][a[i]-j]*g[n-a[i]][i-1-j]%mod*fac[j])%mod;
	cout<<ans<<"\n";
	return 0;
}
```


---

## 作者：tzc_wk (赞：4)

[Portal](https://www.luogu.com.cn/problem/P7154)

题意：

> 给出两个序列 $a_1,a_2,\dots,a_n$，$b_1,b_2,\dots,b_n$，$i$ 与 $j$ 能匹配当且仅当 $a_i\leq b_j$。
>
> 定义一个匹配是极大的，当且仅当对于匹配的 $(i,j)$ 都有 $a_i\leq b_j$ 并且未被匹配的 $a_i,b_j$ 两两无法匹配。
>
> 求极大匹配的个数 $\bmod(10^9+7)$。
>
> $1\leq n\leq 3000$

真·Pt 三个 $\bmod (10^9+7)$。

真·去年 Pt bao0 今年还是 bao0

我还有什么好说的呢？/kk

现场只会 $n^3$ 的做法，赛后看了题解才发现我们做法里正解只差一步之遥。

显然，一个匹配是极大匹配的充要条件最小的未被匹配的 $a_i$ $\gt$ 最大的未被匹配的 $b_j$。

$a,b$ 的下标对匹配个数显然是没有影响的，故不管三七二十一先将 $a,b$ 从小到大排个序。

定义 $p_j$ 为最大的满足 $a_i\leq b_j$ 的 $i$。那么 $j$ 能匹配的 $a_i$ 是 $a$ 的一段前缀——一段长度为 $p_j$ 的前缀。那么这样一来，每个 $b_j$ 有两种选择，一种是选择一个下标 $\leq p_j$ 的，被钦定“要被匹配”却还没有被匹配的 $a_i$ 并与其进行匹配。一种是干脆不匹配。但是，如果在 $1$~$p_j$ 中存在某个 $a_i$ 被钦定“不被匹配”，那么就不能选择第二种情况。因为这样一来就会存在一个未被匹配的 $a_i\leq b_j$，不符合极大匹配的条件。

我们可以因此设计出 $dp$ 状态：$dp_{i,x,f}$ 表示我们在前 $p_i$ 个 $a_i$ 和前 $i$ 个 $b_j$ 中匹配 ，现在有 $x$ 个 $a_i$ 被钦定“要被匹配”却还没有被匹配，$f$ 表示是否存在某个 $a_i$ 被钦定“不被匹配”。考虑 $(p_i,p_{i+1}]$ 中的 $a_i$，我们枚举其当中被钦定“要被匹配”的个数 $k$，然后可以得到下面两个转移方程式：

- $dp_{i+1,x+k-1,f|(k!=(p_{i+1}-p_i))}+=dp_{i,j,k}\times \binom{p_{i+1}-p_i}{k}\times(x+k)$
- $dp_{i+1,x+k,f|(k!=(p_{i+1}-p_i))}+=dp_{i,j,k}\times \binom{p_{i+1}-p_i}{k}$ 这种转移要求 $f|(k!=(p_{i+1}-p_i))=0$

稍微解释一下这两个转移方程：第一个方程对应上面的第一种情况，从 $p_{i+1}-p_i$ 个 $a_i$ 当中钦定选择 $k$ 个的方案数为 $\binom{p_{i+1}-p_i}{k}$，再选择一个与 $b_{i+1}$ 匹配有 $x+k$ 种选法。第二个方程对应上面的第二种情况，即 $b_{i+1}$ 不与任何 $a_i$ 匹配。但这种转移有个前提条件，那就是 $[1,p_{i+1}]$ 中所有的 $a_i$ 都要被钦定匹配，即 $f|(k!=(p_{i+1}-p_i))=0$。

最终答案即为 $dp_{n,0,0}+dp_{n,0,1}$。时间复杂度乍一看是 $n^3$ 的，但 $\sum p_{i+1}-p_i=n$，故转移均摊 $\mathcal O(1)$，总复杂度 $\mathcal O(n^2)$。 

看到没？什么超纲的算法都没有。所以啊，菜是原罪/kk

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define fz(i,a,b) for(int i=a;i<=b;i++)
#define fd(i,a,b) for(int i=a;i>=b;i--)
#define ffe(it,v) for(__typeof(v.begin()) it=v.begin();it!=v.end();it++)
#define fill0(a) memset(a,0,sizeof(a))
#define fill1(a) memset(a,-1,sizeof(a))
#define fillbig(a) memset(a,63,sizeof(a))
#define pb push_back
#define ppb pop_back
#define mp make_pair
template<typename T1,typename T2> void chkmin(T1 &x,T2 y){if(x>y) x=y;}
template<typename T1,typename T2> void chkmax(T1 &x,T2 y){if(x<y) x=y;}
typedef pair<int,int> pii;
typedef long long ll;
template<typename T> void read(T &x){
	x=0;char c=getchar();T neg=1;
	while(!isdigit(c)){if(c=='-') neg=-1;c=getchar();}
	while(isdigit(c)) x=x*10+c-'0',c=getchar();
	x*=neg;
}
const int MAXN=3000;
const int MOD=1e9+7;
int n,a[MAXN+5],b[MAXN+5],p[MAXN+5],dp[MAXN+5][MAXN+5][2],c[MAXN+5][MAXN+5];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);sort(a+1,a+n+1);
	for(int i=1;i<=n;i++) scanf("%d",&b[i]);sort(b+1,b+n+1);
	for(int i=0;i<=MAXN;i++){
		c[i][0]=1;
		for(int j=1;j<=i;j++) c[i][j]=(c[i-1][j]+c[i-1][j-1])%MOD;
	}
	int pos=1;
	for(int i=1;i<=n;i++){
		while(pos<=n&&a[pos]<=b[i]) pos++;
		p[i]=--pos;
	}
	dp[0][0][0]=1;
	for(int i=0;i<n;i++) for(int j=0;j<=p[i];j++){
		for(int k=0;k<2;k++) for(int l=0;l<=p[i+1]-p[i];l++){
			int nk=(k||(l!=(p[i+1]-p[i])));
			if(j+l-1>=0) dp[i+1][j+l-1][nk]=(dp[i+1][j+l-1][nk]+1ll*dp[i][j][k]*(j+l)%MOD*c[p[i+1]-p[i]][l]%MOD)%MOD;
			if(!nk) dp[i+1][j+l][nk]=(dp[i+1][j+l][nk]+1ll*dp[i][j][k]*c[p[i+1]-p[i]][l])%MOD;
		}
	}
//	for(int i=1;i<=n;i++) for(int j=0;j<=p[i];j++) for(int k=0;k<2;k++)
//		printf("%d %d %d %d\n",i,j,k,dp[i][j][k]);
	printf("%d\n",(dp[n][0][0]+dp[n][0][1])%MOD);
	return 0;
}
```



---

## 作者：OldDriverTree (赞：1)

# Solution

先把所有牛和牛棚放一起按从小到大的顺序排序。

注意到未分配的牛棚一定都在未分配的牛的前面，考虑 $\texttt{DP}$。

设 $f_{i,j,0/1}$ 表示当前考虑到前 $i$ 个牛 / 牛棚，有 $j$ 个强制匹配的牛还未匹配，没有 / 有强制不匹配的牛。

考虑转移，如果第 $i$ 个是牛，对于状态 $f_{i,j,0}$，由于 $i$ 必须要匹配，$f_{i,j,0}=f_{i-1,j-1,0}$，对于状态 $f_{i,j,1}$，$i$ 可以匹配也可以不匹配，$f_{i,j,1}=f_{i-1,j,0}+f_{i-1,j,1}+f_{i-1,j-1,1}$。

如果第 $i$ 个是牛棚，对于状态 $f_{i,j,0}$，$i$ 可以和前面的牛匹配，也可以不匹配，匹配就可以选择和前面的 $j+1$ 头牛中的一头进行匹配，$f_{i,j,0}=f_{i-1,j,0}+(j+1)f_{i-1,j+1,0}$，对于状态 $f_{i,j,1}$，$i$ 必须和前面的牛匹配，$f_{i,j,1}=(j+1)f_{i-1,j+1,1}$。

答案为 $f_{2n,0,0}+f_{2n,0,1}$，时间复杂度 $O(n^2)$。

# Code
```c++
#include<bits/stdc++.h>
#define P pair<int,bool>
#define w first
#define o second
using namespace std;
const int N=3002,mod=1e9+7;
int n,f[N+N][N][2];
P a[N+N];

int read() {
	int x=0; char c=0; while (!isdigit(c) ) c=getchar();
	while (isdigit(c) ) x=(x<<3)+(x<<1)+(c&15),c=getchar();
	return x;
}
int main()
{
	n=read();
	for (int i=1;i<=n;i++) a[i]={read(),0};
	for (int i=1;i<=n;i++) a[n+i]={read(),1};
	sort(a+1,a+n+n+1),f[0][0][0]=1;
	for (int i=1;i<=n<<1;i++) for (int j=0;j<=n;j++)
	if (a[i].o) f[i][j][0]=(f[i-1][j][0]+1ll*(j+1)*f[i-1][j+1][0]%mod)%mod,f[i][j][1]=1ll*(j+1)*f[i-1][j+1][1]%mod;
	else f[i][j][0]=j?f[i-1][j-1][0]:0,f[i][j][1]=( (f[i-1][j][0]+f[i-1][j][1])%mod+(j?f[i-1][j-1][1]:0) )%mod;
	printf("%d",(f[n+n][0][0]+f[n+n][0][1])%mod);
	return 0;
}
```

---

## 作者：hsfzLZH1 (赞：1)

### 解题思路

考虑没有要求匹配极大这一条件的做法。假设我们选出了一些牛和棚的集合。将棚的大小从小到大排序，从 $1$ 到 $n$ 编号，那么将牛放进棚且匹配的方案数为 $\prod_{i=1}^n ( \text{小于等于棚} i \text{大小的牛数} -i+1)$ 。

如何理解？考虑最小的牛棚，它里面装的牛要从小于等于该棚大小的牛中选一个；而更大的牛棚可以选择的牛的集合，必定包含比它小的牛棚的集合，此时可以选择的牛的数量就为“小于等于棚的牛数 $-$ 已经被选择的牛数”。

将棚和牛一起从小到大排序，大小相同时将牛排在棚前。这样就可以选择一些棚和牛，记录已经选择的棚和牛的数量，选择棚时就可以知道小于等于该棚的牛的数量。

令 $f[i][j][k]$ 表示选择到棚和牛一起排序的第 $i$ 个，已经选择了 $j$ 个牛，$k$ 个棚的方案数。有状态转移 $f[i-1][j][k]\to f[i][j][k],f[i-1][j-1][k]\to f[i-1][j][k],f[i-1][j][k-1]\times (j-k+1)\to f[i][j][k]$ ，分别对应不选当前，选当前牛和选当前棚的情况。

初始时令 $f[0][0][0]=1$ ，最后 $\sum_{i=0}^n f[n\times 2][i][i]$ 为没有要求匹配极大的方案数。

观察到在状态转移的过程中， $j,k$ 的值只会以 $j-k$ 的形式出现。可以只记录 $j-k$ 的值，将 $j,k$ 两维变成一维。最后 $f[n\times 2][0]$ 为方案数。

现在考虑要求匹配极大的条件，这一条件可以等价为“没有选择的最小牛 $>$ 没有选择的最大棚”。新增一维 $0/1$ 来记录之前是否有没有选择的牛，要满足匹配极大的条件，之后每个棚都必须选。最后 $f[n\times 2][0][0]+f[n\times 2][0][1]$ 为方案数。

时间复杂度 $O(n^2)$ ，空间复杂度 $O(n^2)$ ，通过滚动数组可以降至 $O(n)$ 。

### 参考实现

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define int long long
const int maxn=6010;
const int mod=1000000007;
int n,cur;
struct node
{
	int siz,op;//op=0 cow,op=1 farm
	bool operator<(node x)const{if(siz!=x.siz)return siz<x.siz;return op<x.op;}
}s[maxn];
int f[2][maxn][2];
main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)scanf("%lld",&s[i].siz),s[i].op=0;
	for(int i=1;i<=n;i++)scanf("%lld",&s[n+i].siz),s[n+i].op=1;
	sort(s+1,s+n+n+1);
	//for(int i=1;i<=n+n;i++)printf("%lld %lld\n",s[i].siz,s[i].op);
	f[0][0][0]=1;
	for(int i=1;i<=n+n;i++)
	{
		cur^=1;memset(f[cur],0,sizeof f[cur]);
		for(int j=0;j<=n;j++)
		{
			if(s[i].op==1)f[cur][j][0]=(f[cur][j][0]+f[cur^1][j][0])%mod;
			else f[cur][j][1]=(f[cur][j][1]+f[cur^1][j][0])%mod;
			if(s[i].op==0)f[cur][j][1]=(f[cur][j][1]+f[cur^1][j][1])%mod;
			if(s[i].op==0&&j)
			f[cur][j][0]=(f[cur][j][0]+f[cur^1][j-1][0])%mod,
			f[cur][j][1]=(f[cur][j][1]+f[cur^1][j-1][1])%mod;
			if(s[i].op==1)
			f[cur][j][0]=(f[cur][j][0]+f[cur^1][j+1][0]*(j+1))%mod,
			f[cur][j][1]=(f[cur][j][1]+f[cur^1][j+1][1]*(j+1))%mod;
		}
	}
	printf("%lld\n",(f[cur][0][0]+f[cur][0][1])%mod);
	return 0;
}
```

---

## 作者：Anonymely (赞：0)

以前做过的 dp。首先按照 $s$，$t$ 排序，暴力的考虑是枚举 $s$ 未选的最小值，然后大于 $s$ 的 $t$ 就必须选择了，$O(n^3)$。

发现只需要在 dp 时知道前面是否已经选定过最小值就行了，不需要知道具体，$O(n^2)$。

---

## 作者：daniEl_lElE (赞：0)

考虑什么情况下是符合要求的匹配。记 $x$ 为最小没地方睡觉的奶牛，$y$ 为最大空的牛棚。显然要求 $y<x$。

将奶牛大小和牛棚大小序列合并。

考虑 $dp_{i,j,0/1}$，表示看到第 $i$ 大的位置，目前有 $j$ 只奶牛待匹配，目前属于空牛棚阶段/属于跳过奶牛阶段。

考虑转移，将连续相同大小的牛棚合并成一个，如果是牛棚枚举选了 $k$ 个，从待匹配奶牛中选出 $k$ 个，然后一对一匹配。如果 $k$ 不是总相同牛棚数则 $dp$ 可以从 $0\to 1$。只有 $k$ 是总相同牛棚数才能转移 $dp_{i,j,1}$。

对于相同的奶牛转移类似。

总复杂度平方，注意开 long long 会 MLE。

```cpp
#include <bits/stdc++.h>
#define int long long
#define double long double
using namespace std;
const int mod=1e9+7;
int qp(int a,int b){
	if(b<0){
		return qp(qp(a,mod-2),-b);
	}
	int ans=1;
	while(b){
		if(b&1) (ans*=a)%=mod;
		(a*=a)%=mod;
		b>>=1;
	}
	return ans;
}
int fac[3000005],inv[3000005];
void init(){
	fac[0]=1; for(int i=1;i<=3000000;i++) fac[i]=fac[i-1]*i%mod;
	inv[3000000]=qp(fac[3000000],mod-2); for(int i=2999999;i>=0;i--) inv[i]=inv[i+1]*(i+1)%mod;
}
int C(int i,int j){
	if(i<0||j<0||i<j) return 0;
	return fac[i]*inv[j]%mod*inv[i-j]%mod;
}
struct node{
	int pos,tp;
}f[6005];
bool cmp(node x,node y){
	if(x.pos!=y.pos) return x.pos<y.pos;
	return x.tp<y.tp;
}
signed dp[6005][3005][2];
signed main(){
	init();
	int n; cin>>n;
	for(int i=1;i<=n;i++){
		int a; cin>>a;
		f[i].pos=a,f[i].tp=1;
	}
	for(int i=1;i<=n;i++){
		int a; cin>>a;
		f[i+n].pos=a,f[i+n].tp=2;
	}
	sort(f+1,f+2*n+1,cmp);
	dp[0][0][0]=dp[0][0][1]=1;
	for(int i=1;i<=2*n;i++){
		int j=i;
		while(f[j+1].pos==f[i].pos&&f[j+1].tp==f[i].tp) j++;
		if(f[i].tp==2){
			for(int k=0;k<=n;k++){
				for(int l=0;l<min(j-i+1,k+1);l++){
					(dp[j][k-l][0]+=1ll*dp[i-1][k][0]*C(j-i+1,l)%mod*C(k,l)%mod*fac[l]%mod)%=mod;
					(dp[j][k-l][1]+=1ll*dp[i-1][k][0]*C(j-i+1,l)%mod*C(k,l)%mod*fac[l]%mod)%=mod;
				}
				if(k>=(j-i+1)){
					(dp[j][k-(j-i+1)][0]+=1ll*dp[i-1][k][0]*C(k,j-i+1)%mod*fac[j-i+1]%mod)%=mod;
					(dp[j][k-(j-i+1)][1]+=1ll*dp[i-1][k][1]*C(k,j-i+1)%mod*fac[j-i+1]%mod)%=mod;
				}
			}
		}
		else{
			for(int k=0;k<=n;k++){
				for(int l=0;l<j-i+1;l++){
					(dp[j][k+l][1]+=1ll*dp[i-1][k][1]*C(j-i+1,l)%mod)%=mod;
				}
				(dp[j][k+j-i+1][0]+=1ll*dp[i-1][k][0])%=mod;
				(dp[j][k+j-i+1][1]+=1ll*dp[i-1][k][1])%=mod;
			}
		}
		i=j;
	}
	cout<<dp[2*n][0][1];
	return 0;
}
```

---

## 作者：Caiest_Oier (赞：0)

# [P7154](https://www.luogu.com.cn/problem/P7154)    

参照了机房某佬的思路，在此先 orz。     

首先将牛和牛棚混到一起按体积从小到大排个序。排完后就变成在一个序列上从小往大遍历配对的问题了。    

考虑极大匹配是一个什么意思的限制。对于最小的未分配牛棚的那只牛，则要满足后面不存在空牛棚。这个限制其实不是很难描述，于是我们考虑 DP。因为数据很小，所以随便设计一下就可以过了。令 $dp_{i,j,0/1}$ 表示对于前 $i$ 位而言，当前还剩 $j$ 只牛需要让后面的牛棚来匹配，是/否出现了放弃一头牛不选的情况。     

转移很简单。对于当前点是牛，考虑要不要放弃这头牛，转移即可。如果是牛棚，对于已经放弃牛不选的情况，这个牛棚是不能空置的，否则可以在所有剩余的牛中任选一头。      

代码：      


```cpp
#include<bits/stdc++.h>
#define int long long
#define MOD 1000000007
using namespace std;
int n;
struct obj{
	int v;
	int tp;
}P[10003];
bool comp(obj X,obj Y){
	if(X.v!=Y.v)return X.v<Y.v;
	return X.tp<Y.tp;
}
int dp[6003][3003][2];
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n*2;i++){
		scanf("%lld",&P[i].v);
		P[i].tp=(i>n);
	}
	sort(P+1,P+n*2+1,comp);
	dp[0][0][1]=1;
	for(int i=1;i<=n*2;i++){
		for(int j=0;j<=i&&j<=n;j++){
			if(P[i].tp==0){
				dp[i][j][0]+=dp[i-1][j][1]+dp[i-1][j][0];
				if(j)dp[i][j][0]+=dp[i-1][j-1][0],dp[i][j][1]+=dp[i-1][j-1][1];
				dp[i][j][0]%=MOD;
				dp[i][j][1]%=MOD;
			}
			else{
				dp[i][j][0]=(dp[i-1][j+1][0]*(j+1))%MOD;
				dp[i][j][1]=(dp[i-1][j+1][1]*(j+1)+dp[i-1][j][1])%MOD;
			}
		}
	}
	printf("%lld",(dp[n*2][0][0]+dp[n*2][0][1]+MOD*10ll)%MOD);
	return 0;
} 
```


---

## 作者：LiveZoom (赞：0)

## Description

[link](https://www.luogu.com.cn/problem/P7154)

## Solution

考虑把这 $n$ 个牛和 $n$ 个牛棚放到一起排序。

那么方案是极大的就意味着对于每个没匹配的牛，他之后没有任何一个牛棚是没有匹配的，那么就能够以当前的牛是否全选为状态来 dp。

设 $f_{i,j,0/1}$ 表示考虑到 $1\sim i$ 的牛或牛棚，有 $j$ 头牛待匹配，以及当前的所有牛是否全选上了。

- $i+1$ 是牛

  先考虑当前没有全选的转移：

  1. 如果 $i+1$ 选，那么 $f_{i,j,0}$ 就能够转移到 $f_{i+1,j+1,0}$。

  2. 如果 $i+1$ 不选，那么 $f_{i,j,0}$ 就能够转移到 $f_{i+1,j,0}$。

  当前全选的转移：

  1. 如果 $i+1$ 选，$f_{i,j,1}$ 就转移到了 $f_{i+1,j+1,1}$。
  2. 如果 $i+1$ 没选，$f_{i,j,1}$ 就转移到 $f_{i+1,j,0}$。

- $i+1$ 是牛棚

  同样的，先考虑当前没有全选的转移：

  1. 由于前面已经有牛没选，则这个牛棚必须要和前面的牛匹配，那么 $f_{i,j,0}$ 就转移到 $f_{i+1,j-1,0}$。而这里可以随便选一头奶牛匹配，所以还要乘上一个系数 $j$。

  当前全选的转移：

  1. $i+1$ 用来和前面的牛匹配，那么 $f_{i,j,1}\times j$ 转移到了 $f_{i+1,j-1,1}$。
  2. $i+1$ 不用来匹配，那么 $f_{i,j,1}$ 转移到了 $f_{i+1,j,1}$。

初始状态：$f_{0,0,1}=1$。

输出：$f_{2\times n,0,0}+f_{2\times n,0,1}$。

时间复杂度：$O(n^2)$。

感觉这题把牛和牛棚放到一起处理很妙，不仅节省的代码长度还使转移更加自然。

## Code

```cpp
#include <bits/stdc++.h>

// #define int long long

using namespace std;

const int kMaxN = 3005, kMod = 1e9 + 7;

int n;
int f[kMaxN << 1][kMaxN][2];
pair<int, bool> a[kMaxN << 1];

void dickdreamer() {
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i].first;
    a[i].second = 0;
  }
  for (int i = 1; i <= n; ++i) {
    cin >> a[i + n].first;
    a[i + n].second = 1;
  }
  sort(a + 1, a + 1 + 2 * n);
  f[0][0][1] = 1;
  for (int i = 0; i < 2 * n; ++i) {
    if (a[i + 1].second == 0) {              // i + 1 是牛
      for (int j = 0; j <= min(i, n + 1); ++j) {
        f[i + 1][j + 1][0] = (f[i + 1][j + 1][0] + f[i][j][0]) % kMod;
        f[i + 1][j][0] = (f[i + 1][j][0] + f[i][j][0]) % kMod;
        f[i + 1][j + 1][1] = (f[i + 1][j + 1][1] + f[i][j][1]) % kMod;
        f[i + 1][j][0] = (f[i + 1][j][0] + f[i][j][1]) % kMod;
      }
    } else {                                // i + 1 是牛棚
      for (int j = 0; j <= min(i, n + 1); ++j) {
        if (j) f[i + 1][j - 1][0] = (f[i + 1][j - 1][0] + 1ll * j * f[i][j][0] % kMod) % kMod;
        if (j) f[i + 1][j - 1][1] = (f[i + 1][j - 1][1] + 1ll * j * f[i][j][1] % kMod) % kMod;
        f[i + 1][j][1] = (f[i + 1][j][1] + f[i][j][1]) % kMod;
      }
    }
  }
  cout << (f[2 * n][0][0] + f[2 * n][0][1]) % kMod << '\n';
}

int32_t main() {
#ifdef ORZXKR
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
#endif
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  int T = 1;
  // cin >> T;
  while (T--) dickdreamer();
  // cerr << 1.0 * clock() / CLOCKS_PER_SEC << 's';
  return 0;
}
```



---

