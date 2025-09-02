# Chip Move

## 题目描述

There is a chip on the coordinate line. Initially, the chip is located at the point $ 0 $ . You can perform any number of moves; each move increases the coordinate of the chip by some positive integer (which is called the length of the move). The length of the first move you make should be divisible by $ k $ , the length of the second move — by $ k+1 $ , the third — by $ k+2 $ , and so on.

For example, if $ k=2 $ , then the sequence of moves may look like this: $ 0 \rightarrow 4 \rightarrow 7 \rightarrow 19 \rightarrow 44 $ , because $ 4 - 0 = 4 $ is divisible by $ 2 = k $ , $ 7 - 4 = 3 $ is divisible by $ 3 = k + 1 $ , $ 19 - 7 = 12 $ is divisible by $ 4 = k + 2 $ , $ 44 - 19 = 25 $ is divisible by $ 5 = k + 3 $ .

You are given two positive integers $ n $ and $ k $ . Your task is to count the number of ways to reach the point $ x $ , starting from $ 0 $ , for every $ x \in [1, n] $ . The number of ways can be very large, so print it modulo $ 998244353 $ . Two ways are considered different if they differ as sets of visited positions.

## 说明/提示

Let's look at the first example:

Ways to reach the point $ 1 $ : $ [0, 1] $ ;

Ways to reach the point $ 2 $ : $ [0, 2] $ ;

Ways to reach the point $ 3 $ : $ [0, 1, 3] $ , $ [0, 3] $ ;

Ways to reach the point $ 4 $ : $ [0, 2, 4] $ , $ [0, 4] $ ;

Ways to reach the point $ 5 $ : $ [0, 1, 5] $ , $ [0, 3, 5] $ , $ [0, 5] $ ;

Ways to reach the point $ 6 $ : $ [0, 1, 3, 6] $ , $ [0, 2, 6] $ , $ [0, 4, 6] $ , $ [0, 6] $ ;

Ways to reach the point $ 7 $ : $ [0, 2, 4, 7] $ , $ [0, 1, 7] $ , $ [0, 3, 7] $ , $ [0, 5, 7] $ , $ [0, 7] $ ;

Ways to reach the point $ 8 $ : $ [0, 3, 5, 8] $ , $ [0, 1, 5, 8] $ , $ [0, 2, 8] $ , $ [0, 4, 8] $ , $ [0, 6, 8] $ , $ [0, 8] $ .

## 样例 #1

### 输入

```
8 1```

### 输出

```
1 1 2 2 3 4 5 6```

## 样例 #2

### 输入

```
10 2```

### 输出

```
0 1 0 1 1 1 1 2 2 2```

# 题解

## 作者：蒟蒻炒扇贝 (赞：29)

### Part 1：dp 状态设计与暴力 dp。
由于这一道题中步数和目前到达的位置至关重要，考虑将这两个量设为状态。故设 $f_{i,j}$ 为走了 $i$ 步之后到达 $j$ 的方案数。

根据这个状态，我们不难想到临界状态为 $f_{0,0}=1$，毕竟在最开始时，chip 的位置就在原点上。

考虑一个十分暴力的 dp 转移，对于任意的 $i$ 和 $j$，设 $l$ 为在第 $i-1$ 步时从 $l$ 点出发，能够到达点 $j$ 的坐标。依照题意，$l$ 便满足 $l\in [0,j-(k+i-1)]$，且 $l=j-num\times(k+i-1),num\in\mathbb{N}^+$。设满足以上条件的任意数组成的集合为 $S_{i,j}$，则状态转移方程如下：

$f_{i,j}=\sum_{l\in S_{i,j}}f_{i-1,l}$

这个方法需要我们枚举步数，枚举目前所在的下标，还要枚举出发点，总的时间复杂度为 $\mathop{O(n^3)}$，不能通过本题。

### Part 2：缩小值域优化时空复杂度。

~~貌似我们能走的步数并不会很多，所以考虑从这个地方入手。~~ 设 $m$ 为 chip 可以走的步数，则有下式：

$k+(k+1)+(k+2)+...+(k+m-1)=\frac{(k+k+m-1)\times m}{2}\le n$

当 $k=1$ 时 $m$ 可以取最大值。我们发现 $m$ 的最大值不会超过 $\sqrt{2n}$，也就是说，我们可以把步数的值域缩小到根号级别的，这样时间复杂度就会达到 $\mathop{O(n^2\log{\sqrt{n}})}$，还是无法通过本题。

### Part 3：利用前缀和优化时间复杂度。

考虑把原先的状态转移方程拆开：

$f_{i,j}=f_{i-1,j-(k+i-1)}+f_{i-1,j-2\times(k+i-1)}+...+f_{i-1,j-num\times(k+i-1)}$

~~这个状态转移方程好刁钻，貌似不太好用前缀和优化欸。~~

确实，不同于传统的前缀和 $pre_j=pre_{j-1}+a_j$，这一个状态转移方程并非是一步一步转移的，而是以 $k+i-1$ 为一步转移的。这样看似就困难了不少，其实不然。因为当 $i$ 定下来后，$k+i-1$ 是一个定值，就像原来的前缀和公式中，$1$ 是个定值一样。

所以这里我们就可以稍微更改一下前缀和的公式，改成 $pre_j=pre_{j-(k+i-1)}+a_j$。设 $a_j=f_{i-1,j}$，那么我们便可以提前将状态转移右边的那一堆提前利用前缀和预处理出来，这样我们就不用再枚举 $l$ 来进行转移了。$f_{i,j}$ 便等于 $pre_{j-(k+i-1)}$。

时间复杂度为 $\mathop{O(n\sqrt n)}$。

### Part 4：利用滚动数组优化空间复杂度。

然而这一道题还没有做完。$\mathop{O(n\sqrt n)}$ 的空间复杂度是我们接受不了的，观察发现第 $i$ 步的状态只和第 $i-1$ 步有关，所以我们可以利用滚动数组滚掉一维，空间复杂度便能降到 $\mathop{O(n)}$，可以通过本题。

### Part 5：Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=998244353,MAXN=2e5+5;
void MOD(int &x)
{
	if(x>=mod)x-=mod;
}
int k,n,f[2][MAXN],sum[MAXN],ans[MAXN],pre[MAXN];
signed main()
{
	cin>>n>>k;
	f[0][0]=1;
	int cnt=k,m=0,x=0;
	while(x<=n)
	{
		x+=cnt;
		cnt++;
		m++;
	}
	for(int i=1;i<=m;i++)
	{
		memset(pre,0,sizeof(pre));
		for(int j=0;j<=n;j++)if(j>=(k+i-1))MOD(pre[j]=pre[j-(k+i-1)]+f[(i-1)&1][j]);else pre[j]=f[(i-1)&1][j];
		for(int j=0;j<=n;j++)if(j>=(k+i-1))MOD(f[i&1][j]+=pre[j-(k+i-1)]);//注意数组下标不能为负。
		memset(f[(i-1)&1],0,sizeof(f[(i-1)&1]));
		for(int j=1;j<=n;j++)MOD(ans[j]+=f[i&1][j]);
	}
	for(int i=1;i<=n;i++)cout<<ans[i]<<" ";
}
```
感谢阅读！

---

## 作者：Yusani_huh (赞：7)

## 题意

给出 $n,k$，对于所有在 $[1,n]$ 范围内的 $x$，求出在数轴上用如下走法从 $0$ 走到 $x$ 的方案数：第一步的长度须为 $k$ 的倍数，第二步的长度须为 $k+1$ 的倍数，第三步的长度须为 $k+2$ 的倍数，以此类推。

## 做法

首先这是一个计数类问题，其次这是一个计数类问题，以及对于所有 $[1,n]$ 范围内的 $x$ 都需要求方案数，那么转化一下容易想到用完全背包来解决。

具体一点，就是有 $k,k+1,k+2,\cdots,n$ 这样若干个物品，每个物品都可以拿无穷多次（因为每步可以走其中一个数的若干倍），求填满容量为 $[1,n]$ 的背包的方案数。

但是发现直接套模板做的复杂度最坏是 $O(n^2)$，无法承受。考虑优化。

我们看到由于题目要求，我们的背包里会有一个依赖关系，即必须先拿了 $k$ 才能拿 $k+1$，拿了 $k+1$ 才能拿 $k+2$，因此上面的做法非但时间不对，而且答案错误。

但是建立在这个依赖关系的基础上，可以发现在最坏情况下最多也仅需走 $
\sqrt n$ 步。设当前已走 $m$ 步，最坏情况即当 $k=1$，且每一步都只走 $k+m$ 的一倍时，可以发现有 $1+2+\cdots+m=n$，那么 $m$ 就是 $
\sqrt n$ 级别的数。

因此可以使用完全背包解决。不过需要注意，由于依赖关系的存在，完全背包不能压缩空间，每一个物品的选择取决于上一个物品有没有选。设当前选择到第 $j$ 个物品（费用即为 $w_j=k+j-1$），背包的第 $i$ 个位置，则

$$dp_{i,j}=dp_{i,j}+dp_{i-w_j,j}+dp_{i-w_j,j-1}$$

其中 $dp_{i-w_j,j}$ 表示在当前这步已走过的情况下再走一个 $k+j-1$，$dp_{i-w_j,j-1}$ 表示在当前这步还没走的情况下**在走了上一步的基础上**走一个 $k+j-1$。

## 代码

注意到 DP 只取决于当前位和上一位，使用滚动数组优化。特别要注意边界处理。

```
#include<bits/stdc++.h>
using namespace std;
#define N 200003
#define LL long long
#define INF 0x3f3f3f3f
#define MOD 998244353
int n,k,dp[2][N],ans[N];
int main(){
    scanf("%d%d",&n,&k);
    int nw=k,id=1;  //使用nw记录当前所有物品的费用和（保证复杂度）
    dp[0][0]=1;
    for(int i=k;nw<=n;++i){  //枚举当前物品的费用
        id^=1;
        for(int j=i;j<=n;++j)  //枚举背包位置
            dp[id][j]=(dp[id][j]+dp[id^1][j-i]+dp[id][j-i])%MOD;
        dp[id][0]=0,nw+=i;  //注意边界处理，除了第一步之后的0都不能置为1
        for(int l=1;l<=n;++l){  //因为可以走任意步终止，每次统计答案
            ans[l]=(ans[l]+dp[id][l])%MOD;
            dp[id^1][l]=0;
        }
    }
    for(int i=1;i<=n;++i)
        printf("%d ",ans[i]);
    puts("");
    return 0;
}
```

---

## 作者：piggy123 (赞：6)

引理：若设总共跳的步数为 $d$，则 $\Theta(d)=\Theta(\sqrt n)$。

证明：最坏情况取 $k=1,n=2\times 10^5$，每次跳步数的一倍，则 $(1+d)\times d\leq 2n$，则 $\Theta(d)=\Theta(\sqrt n)$。

考虑 DP ，设 $dp[i][j]$ 表示跳了 $i$ 步，到达 $j$ 的方案数，状态复杂度为 $\Theta(n\sqrt n)$。

于是转移复杂度必然只能为 $\Theta(1)$，注意到若 $i$ 在 本次要走 $s$ 步的情况下对 $j$ 有贡献，则 $i\equiv j(\bmod\ s)$。所以可以在外层循环枚举 $s$，用一个数组 $sm_i$ 记录下模 $s$ 余 $i$ 的贡献即可。

注意需要使用滚动数组技巧压维，并且注意读入输出效率。

AC Code：
```cpp
#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
using namespace std;

ll dp[2][200005],sm[200005],sm2[200005],mod=998244353;

int main(){
	ll n,k;
	scanf("%lld%lld",&n,&k);
	
	for (ll j=0;j<=sqrt(n*2);j++){
		ll stp=k+j;
		for (ll i=1;i<=n;i++){
			sm[i]=0;
			dp[j&1][i]=0;
		}
		sm[0]=(j==0);
		for (ll i=1;i<=n;i++){
			
			dp[j&1][i]+=sm[i%stp];
			dp[j&1][i]%=mod;
			sm[i%stp]+=dp[j&1^1][i];
			sm[i%stp]%=mod;
			sm2[i]+=dp[j&1][i];
			sm2[i]%=mod;
		}
	}
	for (ll i=1;i<=n;i++)printf("%lld ",sm2[i]);
	return 0;
}
```


---

## 作者：cbdsopa (赞：3)

[更好的体验](https://www.cnblogs.com/cbdsopa/p/16554340.html)

### CF1716D 解题报告

题目大意：给 $n,k$，问从 $0$ 开始，第 $i$ 步只能走 $(k+i-1)$ 的倍数，问分别走到 $x\in[1,n]$ 的方案数。

#### 题解

转换题意，有若干个 $(k+i)$ 大小的物品，取 $y$ 时 $[k,y)$ 都要至少选过一次，问拿出总大小为 $x\in[1,n]$ 的物品的方案数。

现场打的时候完全没想背包，于是寄了。容易发现这是个完全背包，但是前提是一定每个物品至少选一个。于是考虑滚动数组，分层后每次只由当前层和上一层贡献即可。初始状态第 $0$ 层容量为 $0$ 的方案数为 $1$。

考虑证明这个复杂度，容易发现对于每个容积 $i$ ，其能选的物品 $t$ 满足 $tk+\sum_{j=1}^t(j-1)\le i$ ，那么 $t$ 的上界是 $O(\sqrt{n})$。然后对于每个 $i\in[1,n]$ 求出这个上界，选第 $t$ 个物品时如果超过 $i$ 的上界，那么 $i$ 就不必枚举了（这个是个小的卡常技巧）。复杂度是 $O(n\sqrt{n} )$ 未满。

关于就这个玩意为什么我考场上没想出来？我也不知道。

#### 参考代码

```cpp
#include<bits/stdc++.h>
#define ll long long
#define db double
#define file(a) freopen(#a".in","r",stdin),freopen(#a".out","w",stdout)
#define sky fflush(stdout)
#define gc getchar
#define pc putchar
namespace IO{
	template<class T>
	inline void read(T &s){
		s=0;char ch=gc();bool f=0;
		while(ch<'0'||'9'<ch) {if(ch=='-') f=1;ch=gc();}
		while('0'<=ch&&ch<='9') {s=s*10+(ch^48);ch=gc();}
		if(ch=='.'){
			T p=0.1;ch=gc();
			while('0'<=ch&&ch<='9') {s=s+p*(ch^48);p/=10;ch=gc();}
		}
		s=f?-s:s;
	}
	template<class T,class ...A>
	inline void read(T &s,A &...a){
		read(s);read(a...);
	}
};
using IO::read;
const int N=2e5+3;
const int mods=998244353;
inline int inc(int x,int y){
	return (x+=y)>=mods?x-mods:x;
}
inline int dec(int x,int y){
	return (x-=y)<0?x+mods:x;
}
inline int mul(int x,int y){
	return 1ll*x*y%mods;
}
int n,k;
int len[N];
int f[2][N],g[N];
int main(){
	file(a);
	read(n,k);
	int t=0,sum=0;
	for(int i=1;i<=n;++i){
		while(i>=(t+1)*k+sum+t){
			sum+=t;
			++t;
		}
		len[i]=t;
	}
	int l=0;bool cur=0;
	f[cur^1][0]=1;
	for(int i=1;i<=len[n];++i,cur^=1){
		while(len[l]<i-1) ++l;
		int b=k+i-1;
		memset(f[cur],0,sizeof(f[cur]) );
		for(int j=l;j+b<=n;++j){
			f[cur][j+b]=inc(f[cur][j+b],inc(f[cur][j],f[cur^1][j]) );
			g[j+b]=inc(g[j+b],f[cur][j+b]);
		}
	}
	for(int i=1;i<=n;++i){
		printf("%d ",g[i]);
	}
	return 0;
}
```

---

## 作者：Ender_hz (赞：2)

# 题意

Chip 在数轴原点处，给定一个正整数 $k$，使得 Chip 可以向数轴正方向移动若干次，第 $i$ 次的步长必须为 $k+i-1$ 的倍数。求对于给定正整数 $n\ (n\le2\times10^5)$，对于数轴上区间 $[1,n]$ 中的点，Chip 到达每个点的方案数。

# 分析

注意到第 $i$ 次的步长一定为 $k + i - 1$ 的任意倍数，我们不妨将该问题转化为与之等价的下面这个问题：

有 $n$ 个背包，容积分别为 $1,2,\cdots,n$，给定一个正整数 $k$，对于每个背包，你可以进行若干次操作，第 $i$ 次操作可以向该背包内放入任意数量 $(>0)$ 的体积为 $k + i - 1$ 的物品，求恰好将该背包装满的方案数。

对于背包问题，我们从以下三个角度考虑代码实现：

+ 初始状态：显然，第 $1$ 步能装满的背包容积一定为 $k$ 的倍数，且方案数为 $1$；
+ 状态转移方程：让 $f_{i,j}$ 维护当前物品体积为 $i$，容积为 $j$ 的背包装满的方案数，则状态转移方程为 $f_{i, j} = f_{i-1,j-i}+f_{i,j-i}$；
+ 边界条件：不难想到，边界条件一定在枚举物品体积时出现，当放入第 $i$ 个物品时，背包的容积至少为 $k+(k+1)+\cdots+(k+i-1)$，当该数 $>n$ 时，没有继续枚举的必要，循环结束。

关于状态转移方程的进一步解释：放入体积为 $i$ 的物品后，容积为 $j$ 的背包恰好装满的方案数 $(f_{i,j})$ 一定从容积为 $j-i$ 的背包的方案数转移而来，又因为当前物品的体积为 $i$，所以上一个物品的体积一定为 $i$ 或 $i-1$，两种情况的方案数分别为 $f_{i, j-i}$ 和 $f_{i-1,j-i}$，由此可得状态转移方程。

通过估算可得，时间复杂度约为 $\mathcal O(n\sqrt n)$，$f$ 数组大小同样约为 $\sqrt n\times n$，显然超限，由于转移时只涉及两行 $(f_i,f_{i-1})$，这里采用滚动数组记录。

最后通过 $g_j$ 维护装满容积为 $j$ 的背包的总方案数。

文章最后附有两组样例对应的 $f,g$ 数组的值便于理解。

# 代码

```cpp
#include<iostream>
#define sfor(i, h, t) for(int i = (h); i <= (t); ++i)
using namespace std;
const int MAXN = 0x30D48;
const int P = 0x3B800001;
int N, K;
int f[2][MAXN], g[MAXN];
int sum;
signed main(void) {
    ios::sync_with_stdio(false);
    cin >> N >> K;
    for(int j = K; j <= N; j += K)
        g[j] = f[1][j] = 1;
    sum = K + 1;
    for(int i = K + 1; sum < N; sum += ++i) {
        sfor(j, sum - i, sum - 1) {
            f[0][j] = f[1][j];
            f[1][j] = 0;
        }
        sfor(j, sum, N) {
            f[0][j] = f[1][j];
            (f[1][j] = f[0][j - i] + f[1][j - i]) %= P;
            (g[j] += f[1][j]) %= P;
        }
    }
    sfor(j, 1, N)
        cout << g[j] << ' ';
    cout << '\n';
    return 0;
}
```

# 样例解释

样例1：

| 数组 \ $j$ | 1    | 2    | 3    | 4    | 5    | 6    | 7    | 8    |
| ---------- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |
| $f_1$      | 1    | 1    | 1    | 1    | 1    | 1    | 1    | 1    |
| $f_2$      | 0    | 0    | 1    | 1    | 2    | 2    | 3    | 3    |
| $f_3$      | 0    | 0    | 0    | 0    | 0    | 1    | 1    | 2    |
| $g$        | 1    | 1    | 2    | 2    | 3    | 4    | 5    | 6    |

样例2：

| 数组 \ $j$ | 1    | 2    | 3    | 4    | 5    | 6    | 7    | 8    | 9    | 10   |
| ---------- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |
| $f_2$      | 0    | 1    | 0    | 1    | 0    | 1    | 0    | 1    | 0    | 1    |
| $f_3$      | 0    | 0    | 0    | 0    | 1    | 0    | 1    | 1    | 1    | 1    |
| $f_4$      | 0    | 0    | 0    | 0    | 0    | 0    | 0    | 0    | 1    | 0    |
| $g$        | 0    | 1    | 0    | 1    | 1    | 1    | 1    | 2    | 2    | 2    |



---

## 作者：jzcrq (赞：2)

### 题意概述

最初你有一个整数 $x=0$，你将对其连续进行多次操作。

给定正整数 $k$，在第 $i$ 次操作中，你可以令 $x$ 加上一个正整数 $y$，要求 $y$ 是 $k+i-1$ 的倍数（注意：$y \neq 0$）。

给定正整数 $n$，对于正整数 $j \in [1,n]$ ，求令 $x=j$ 的方案数。

$(1 \leq k \leq n \leq 2 \cdot 10^5)$

---

### 思路

题目的操作形式很像完全背包，不难想到设 $f_{i,j}$ 表示第 $i$ 次操作得到数字 $j$ 的方案数。

每层内转移类似完全背包：$\large f_{i,j}+=f_{i,j-(k+i-1)}$，由小向大更新。

为了保证转移连续，层间转移则为：$\large f_{i,j}=f_{i-1,j-(k+i-1)}$

至此，该算法时间复杂度，空间复杂度均为 $\mathcal{O}(nk)$。不能接受，考虑优化。

因为转移只在相邻层之间进行，所以可以滚动数组消去一维，空间复杂度降至 $\mathcal{O}(n)$。

因为操作是连续的，每次操作都会让可以得到的最小的数增大 $k+i-1$，所以可以得到的最小的数的增长与 $i$ 是平方关系，当可以得到的最小的数大于 $n$ 时，就可以终止递推，时间复杂度降至 $\mathcal{O}(n \sqrt{n})$。

---

### Code

```cpp
#include <cstdio>
#define MAXN (int)(2e5+233)
#define rep(i,l,r) for (int i=l;i<=r;i++)
#define per(i,r,l) for (int i=r;i>=l;i--)

const int mod=998244353;
int n,k,f[MAXN]={1},g[MAXN];

int main()
{
	scanf("%d%d",&n,&k);
	rep(i,k,n)
	{
		bool fail=1;
		per(j,n,i) f[j]=f[j-i];
		f[0]=f[i-1]=0;
		rep(j,i,n) f[j]=(f[j]+f[j-i])%mod;
		rep(j,1,n)
		{
			if (f[j]) fail=0;
			g[j]=(f[j]+g[j])%mod;
		}
		if (fail) break;
	}
	rep(i,1,n) printf("%d ",g[i]);
	return 0;
} 
```


---

## 作者：hsy8116 (赞：1)

求通过 QwQ

本文参考了题解区的部分做法，综合了自己的理解，力求解释得更清楚，也为了加深自己对题目的理解。

## 题目

[link](https://codeforces.com/problemset/problem/1716/D)

给定两个数 $n,k$，问从 $0$ 开始，第 $i$ 步只能走 $(k + i - 1)$ 的正倍数（即不能走 $0$），问分别走到 $x \isin [1,n]$ 的方案数，对 $998244353$ 取模。

## 解题

首先考虑对这些位置做 DP。设 `f[i][j]` 表示走到第 $j$ 步时走到第 $i$ 个位置的方案数。

考虑最坏情况下，$k = 1$，从 $1$ 的步长开始走，每多一步，步长只加 $1$。所以 $1 + 2 + \dots + m = n$，$m$ 为最多的步数。

$\therefore \frac{(m + 1) m}{2} = n$

$\because \frac{(\sqrt{2n} + 1) \sqrt{2n}}{2} = \frac{2n + \sqrt{2n}}{2} = n + \frac{\sqrt{2n}}{2} \gt n$

$\therefore m \lt \sqrt{2n}$

枚举步数复杂度 $O(\sqrt{n})$ 枚举每个位置复杂度 $O(n)$ 所以 DP 外面两层循环的复杂度为 $O(n \sqrt{n})$。

不难写出以下暴力：（暂不在意时间、空间复杂度的错误）

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;

const int NR = 2e5 + 10;
const int MR = sqrt(2 * NR);
const long long mod = 998244353;
long long f[NR][MR];

int main()
{
	int n, k;
	scanf("%d%d", &n, &k);
	f[0][0] = 1;
	for (int j = 1; j <= sqrt(2 * n); j ++)
	{
		for (int i = 1; i <= n; i ++)
		{
			if (i - (k + j - 1) < 0) continue;
			for (int o = 1; ; o ++)
			{
				int l = i - o * (k + j - 1);
				if (l < 0) break;
				f[i][j] += f[l][j - 1];
				f[i][j] %= mod;
			}
		}
	}
	for (int i = 1; i <= n; i ++)
	{
		long long sum = 0;
		for (int j = 1; j <= sqrt(2 * n); j ++)
		{
			sum += f[i][j];
			sum %= mod;
		}
		printf("%lld ", sum);
	}
	puts("");
	return 0;
}
```

显然发现，DP 双重循环内部的复杂度要尽量小。

还是考虑使用暴力的部分思路。

```cpp
f[0][0] = 1;
for (int j = 1; j <= sqrt(2 * n); j ++)
{
    for (int i = 1; i <= n; i ++)
    {
        if (i - (k + j - 1) < 0) continue;
        for (int o = 1; ; o ++)
        {
            int l = i - o * (k + j - 1);
            if (l < 0) break;
            f[i][j] += f[l][j - 1];
            f[i][j] %= mod;
        }
    }
}
```

注意到，这里枚举的 `o` 费了时间复杂度。又考虑更新 `i` 的位置 `l` 和 `i` 位置的差都是这一步步长的倍数，因此这两个位置对步长取余的余数相等。

所以可以开一个数组 `mstep` 记录对步长取余余数相同的位置的方案数和，更新每个位置时，直接加上这个数组的对应值即可。

也要注意更新 `i` 的位置 `l` 必须在 `i` 之前，所以对每个步长都要重置一下 `mstep`，然后按位置从小到大在计算新答案的同时将上一步这个位置的方案数放入 `mstep`。这样既保证遍历到后面的位置时使用的 `mstep` 值是之前更小可行的位置转移来的；又保证计算的新答案的值是由上一步得来的，不会出现跳步的情况。

在对特定步长下每个位置计算的时候，我们可以直接将这一步长的答案值存入每个位置的最终答案。

最后，如果开 $O(n \sqrt{n})$ 的 DP 数组会炸空间，所以考虑滚动数组，滚掉步数这一维。

## Code

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;

const int NR = 2e5 + 10;
const int MR = sqrt(2 * NR);
const long long mod = 998244353;
long long f[NR][2]; // f[i][j] 表示走到第 j 步，第 i 个位置的方案数，这里将 j 这维滚动
long long mstep[NR]; // 对步长取余余数相同的位置的方案数和
long long ans[NR];

int main()
{
	int n, k;
	scanf("%d%d", &n, &k);
	for (int j = 1; j <= sqrt(2 * n); j ++)
	{
		int step = (k + j - 1); // 步长
		for (int i = 0; i <= step; i ++)
		{
			mstep[i] = 0;
		}
		if (j == 1) mstep[0] = 1; // 走第一步时可从 0 走过来
		for (int i = 1; i <= n; i ++)
		{
			f[i][j % 2] = mstep[i % step]; // 由上一步，位置在 i 之前，这一步可以走到 i 的位置的方案和更新而来
			f[i][j % 2] %= mod;
			mstep[i % step] += f[i][(j % 2) ^ 1]; // 在这一位置对步长取余余数的下标上，放入这个位置上一步的结果
			mstep[i % step] %= mod;
			ans[i] += f[i][j % 2];
			ans[i] %= mod;
		}
	}
	for (int i = 1; i <= n; i ++)
	{
		printf("%lld ", ans[i]);
	}
	puts("");
	return 0;
}
```

---

## 作者：KingPowers (赞：1)

[题目链接](https://www.luogu.com.cn/problem/CF1716D)

萌萌题。

注意到我们每次的步长只能为 $k+i-1$ 的正倍数，那么最坏情况下 $k=1$ 时我们最慢的走法也是走 $1,2,3,4,\ldots$ 这样下去，根据等差数列求和公式，我们的最大步数只有 $O(\sqrt n)$ 级别。

设 $f_{i,j}$ 表示走 $j$ 步到 $i$ 的方案数，对于所有的 $p$ 满足 $p\equiv i\pmod{(k+d-1)}$ 且 $p<i$，都有 $f_{i,j}\leftarrow f_{p,j-1}$。

这样时间复杂度 $O(n^2\sqrt n)$，空间复杂度 $O(n\sqrt n)$，显然过不去。

对于状态第二维可以直接外层先从小到大枚举步数砍掉；对于转移，假设当前步数为 $d$，设 $sum_i$ 表示所有满足 $j\equiv i\pmod{(k+d-1)}$ 的 $f_j$ 之和，可以做到时间 $O(n\sqrt n)$，空间 $O(n)$。

把 `long long` 去了，再换成 64bit 的 C++20，跑得还是挺快的。

```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);i++)
#define Rof(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int N=5e5+5;
const int mod=998244353;
int n,k,f[N],g[N],sum[N];
void work(int d){
    For(i,0,n){
        int pre=f[i];
        f[i]=sum[i%d];
        sum[i%d]=(sum[i%d]+pre)%mod;
        g[i]=(g[i]+f[i])%mod;
    }
    For(i,0,d-1) sum[i]=0;
}
signed main(){
    cin>>n>>k;f[0]=1;
    int now=0,tmp=0;
    while(true){
        now++;tmp+=k+now-1;
        if(tmp>n) break;
        work(k+now-1);
    }
    For(i,1,n) printf("%d ",g[i]);
    return 0;
}
```


---

## 作者：wfc284 (赞：0)

这是一个完全背包，第 $i$ 件物品的重量为 $k+i-1$，求填满背包方案数。注意：每件物品至少选一个。  

按正常的完全背包写，大概是下面的代码：  
```cpp
for i from 1 to numbers of kinds of items
  for j from i+k-1 to n
    f[j] += f[j-(i+k-1)]
```
其中 $f_j$ 表示当前总重为 $j$ 的方案数。

如何统计答案？
对于每一个 $i$，让 $ans_j$ 加上 $f_j$ 即可，表示可以在任意时刻结束装物品。

但是这个代码没有保证每件物品至少选一个。
我们在第 $i$ 将要更新时，用另一个数组复制 $f$ 的信息，在更新后，$f$ 的每个元素要减去这个数组的对应元素。  
原因：第 $i$ 轮不选的方案，就是前 $i-1$ 轮都选的方案。减去之前的方案，正确性显然。（归纳的思想，易证）

再者，时间复杂度如何保证？  
我们发现，最劣情况，第 $i$ 件物品的重量为 $i$，等差数列求和，显然总共最多有 $O(\sqrt n)$ 种物品。于是 $i$ 的上限就是 $O(\sqrt n)$，随便开个 $800$，跑得飞快。

时间复杂度 $O(n \sqrt n)$。

[submission.](https://codeforces.com/contest/1716/submission/304852956)

---

## 作者：aaalys (赞：0)

# Codeforces 1716D Chip Move 题解

## 题目大意

[题目传送门](https://www.luogu.com.cn/problem/CF1716D)
题目中给的描述很清楚，大家自己看题目（如果想看英文题面请去 [CF](https://codeforces.com/contest/1716/problem/D)）

## 思路

### 第一步：将原问题转化成背包

看到第 $i$ 步只能走 $(k + i - 1)$ 的整倍数，不难发现和完全背包很类似。

可以把第 $i$ 步看做只能走 $(k + i - 1)$，但是能走无限次。

这样就能把这个问题转化成一个完全背包问题：有 $n$ 个物品，第 $i$ 个物品重量为 $(k + i - 1)$，每个物品最少取一个（因为题目中说不能走 0）问你总重量为 $x\in[1,n]$ 的取法数。

### 第二步：设计状态

但这个问题不是裸的完全背包板子，因为原问题是求最大收益，现在的问题是求方案数。

所以现在需要用完全背包的状态修改一下。

完全背包的状态：设 $dp_{i,j}$ 为到第 $i$ 个物品，总重量为 $j$ 时的最大收益。

现在只要修改一点，把最大收益改成方案数就行。

现在的状态：设 $dp_{i,j}$ 为到第 $i$ 个物品，总重量为 $j$ 时的方案数。

### 第三步：转移方程

原来的完全背包转移方程是 $dp_{i,j} = \max(dp_{i-1,j}, dp_{i,j-w_i} + v_i)$。
现在需要在原来的基础上修改几点：

- 把原方程转换成统计方案的形式
- 把原来的 $dp_{i-1,j}$ 删去，不能转移，每个物品最少取一个。
- 因为没有了 $dp_{i-1,j}$，所以统计 $dp_{i,j}$ 时需要加上 $dp_{i-1,j-w_i}$。
- 需要把方程中的 $w_i$ 替换成 $(k+ i - 1)$。

现在的转移方程就变成了 $dp_{i,j} = dp_{i,j-(k+i-1)} + dp_{i-1,j-(k+i-1)}$。

### 初始状态与答案

初始时没有开始选，即选到第 0 个物品，总重量为 0，但是有一种方法（什么也不选）。

初始状态是 $dp_{0,0} = 1$。

由于在原题中走几步到达终点都算答案，所以统计最终答案时要加上每一个 $i$ 对应的 dp 值。

答案为 $ans_x = \sum_{i=1}^n{f_{i,x}}$。

## 代码实现

### 实现细节

建议看完此部分后再看代码。

#### 细节 1：时间优化

按照这种方法，时间复杂度为 $O(n^2)$，无法通过此题，考虑优化。

第二维总重量无法优化，只能优化第一维物品个数。

因为每种物品最少取一个，所以按照取一个计算，这样能让总重量最少。

要让总重量 $\le n$，也就是让 $\sum_{i=1}^x{(k + i - 1)}\le n$。

解得 $x \le \sqrt{2n}$，也就是说最多取 $\sqrt{2n}$ 个物品就能取完 $n$ 的容量，因此 $i$ 只用枚举到 $\sqrt{2n}$ 就行。

优化后的时间复杂度为 $O(n \sqrt{n})$。

#### 细节 2：滚动数组优化

如果直接用上面的状态，那空间复杂度为 $O(n \sqrt{n})$，无法通过此题（开 int 数组需要用 360MB 的空间）。

考虑将第一维滚动掉。

但是这里不能直接压掉一维，需要在第一维再开一个 0/1 表示这轮和上轮的 dp 值。

所以需要再开一个变量 now，表示当前的 dp 值存在 $dp_{now,i}$ 里。那上一轮的 dp 值就存在 $dp_{now \oplus 1,i}$ 里。

每次转移的时候需要让 $now \gets now \oplus 1$，也就是让当前的 dp 值变成下一轮的上一轮的 dp 值。

转移方程也要进行一些改动，变成 $dp_{now,j} = dp_{now,j-(k+i-1)} + dp_{now \oplus 1,j-(k+i-1)}$。

优化后的空间复杂度为 $O(n)$。

#### 细节 3：统计答案

由于滚动数组无法记录所有状态，所以不能在最后统计最终答案，而是要在 dp 过程中累加答案。

也就是在 dp 的过程中将 $ans_j$ 累加上 $dp_{now,j}$。

#### 一些坑点

- **记得取模。**
- $n,k$ 的范围是 $1 \le n,k \le 2\cdot10^5$，不是 $1 \le n,k \le 10^5$。
- 记得要及时清空数组（不然会 WA）。
- 其他的注意事项可以看代码注释

### Code（只展示关键代码）

```cpp
f[0][0] = 1;//初始值
int now = 0;
for (int i = 1; i * i <= n * 2; i++){//i枚举到sqrt(2*n)
    now ^= 1;
    for (int j = i * k + i * (i - 1) / 2; j <= n; j++)//取前i个物品，最少总重量为ik+i*(i-1)/2（读者自行推导），所以j从ik+i*(i-1)/2开始
        (f[now][j] += f[now][j - (k + i - 1)] + f[now ^ 1][j - (k + i - 1)]) %= mod;//转移
    memset(f[now ^ 1], 0, sizeof(f[now ^ 1]));//注意：要清空数组
    for (int j = 1; j <= n; j++)//累加答案
        (ans[j] += f[now][j]) %= mod;
}
```

---

## 作者：WaterSun (赞：0)

# 思路

## part 1

这种题目应该能一眼看出是 DP。

我们令 $dp_{i,j}$ 表示走到 $j$ 这个位置，最后一步花了 $i$ 的倍数。

那么，我们的方程就很好想了：$dp_{i,j} = \sum_{k = 1}^{j - k \times i \geq 0}dp_{i - 1,j - k \times i}$。

因为，我们走到 $j$ 的位置只能走 $i$ 的倍数，所以我们上一步一定是走了 $k \times i(k > 0)$ 的位置。又由于，我们的步长（即每一次的 $i$）每一步都会加 $1$，所以上一次状态的步长一定是 $i - 1$。

然后我们再利用一下前缀和即可。

但是，会有人对这个时间复杂度有所疑惑，这表面上是 $\Theta(N^2)$ 的，实际上这有 $\Theta(N \sqrt N)$。

我们不难发现，我们要枚举的步长是会产生一个上限的。

假如在最不利的情况下，初始步长为 $1$。

因为，我们要满足 $(\sum_{i = 1}^{i \leq x}i) \leq N$（其中，$x$ 为满足条件的任意数，也就是我们程序中代码外层循环的次数）

由等差数列可知，$(\sum_{i = 1}^{i \leq x}i) = \frac{x(x + 1)}{2}$，因此，$x \leq \sqrt {2N}$。

综上，我们的时间复杂度为 $\Theta(N \sqrt N)$。

## part 2

虽然上述方法已经足矣通过此题，但是我们依旧可以对空间进行优化。

我们可以发现，每一次的状态只与它前面的位置有关，于是，我们只需要用前缀和记录上一个状态，再将新的状态覆盖到原位置上即可。

这样我们的空间复杂度由 $\Theta(N \sqrt N)$ 降为了 $\Theta(N)$。

# code

```cpp
#include <bits/stdc++.h>
#define re register

using namespace std;

const int N = 2e5 + 10,mod = 998244353;
int n,k,cnt;
int s[N],ans[N];
int dp[N] = {1};

inline int read(){
	int r = 0,w = 1;
	char c = getchar();
	while (c < '0' || c > '9'){
		if (c == '-') w = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9'){
		r = (r << 3) + (r << 1) + (c ^ 48);
		c = getchar();
	}
	return r * w;
}

int main(){
	n = read();
	k = read();
	while (k <= n && cnt <= n){//需要判断总和是否大于 n 
		for (re int i = 0;i <= n;i++){
			int t = (i - k >= 0 ? s[i - k] : 0);//需要判断一下是否越界 
			s[i] = (t + dp[i]) % mod;//更新前缀和 注意：这里的 dp[i] 还是未更新的值，所以请放心使用 
			dp[i] = t;//更新 
			ans[i] = (ans[i] + dp[i]) % mod;//每一次更新答案 
		}
		cnt += k++;//每次更新总和 
	}
	for (re int i = 1;i <= n;i++) printf("%d ",ans[i] % mod);
	return 0;
}
```

---

