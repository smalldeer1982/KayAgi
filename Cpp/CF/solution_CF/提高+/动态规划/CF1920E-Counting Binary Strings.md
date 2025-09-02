# Counting Binary Strings

## 题目描述

Patrick calls a substring $ ^\dagger $ of a binary string $ ^\ddagger $ good if this substring contains exactly one 1.

Help Patrick count the number of binary strings $ s $ such that $ s $ contains exactly $ n $ good substrings and has no good substring of length strictly greater than $ k $ . Note that substrings are differentiated by their location in the string, so if $ s = $ 1010 you should count both occurrences of 10.

 $ ^\dagger $ A string $ a $ is a substring of a string $ b $ if $ a $ can be obtained from $ b $ by the deletion of several (possibly, zero or all) characters from the beginning and several (possibly, zero or all) characters from the end.

 $ ^\ddagger $ A binary string is a string that only contains the characters 0 and 1.

## 说明/提示

In the first test case, the only suitable binary string is 1. String 01 is not suitable because it contains a substring 01 with length $ 2 > 1 $ .

In the second test case, suitable binary strings are 011, 110 and 111.

In the third test case, suitable binary strings are 101, 0110, 0111, 1110, and 1111.

## 样例 #1

### 输入

```
6
1 1
3 2
4 2
5 4
6 2
2450 2391```

### 输出

```
1
3
5
12
9
259280854```

# 题解

## 作者：WerChange (赞：11)

被这种题卡了，脸都不要了。

仔细读题，发现序列可以分成两部分（$0$ 和 $1$）来考虑。

在合法序列中，对于一个 $1$，它产生的子串贡献一定是（假设与上一个 $1$ 之间有 $x$ 个 $0$，与下一个 $1$ 之间有 $y$ 个 $0$）：
$$(x+1)(y+1)$$

如果去 DP 这 $n$ 个 $1$，易得转移方程：
$$f_{i,j}=\sum f_{i-p\times j,p}$$

$f_{i,j}$ 表示：当前贡献了 $i$ 个合法子串，上一个 $1$ 到现在的 $1$ 的长度为 $j$ 的组成序列方案数。

接下来考虑 $p$ 的值域。

要使式子成立，有：$p\in [1, \frac{i}{j}]$。

考虑题目限制（最长合法串长度不大于 $k$），有：$p\in [1,k+1-j]$。

所以 $p\in [1,\min\{\frac{i}{j},k+1-j\}]$，即：
$$f_{i,j}=\sum\limits_{p=1}^{\min\{\frac{i}{j},k+1-j\}} f_{i-p\times j,p}$$

[code](https://codeforces.com/contest/1920/submission/242206913)

---

## 作者：huangrenheluogu (赞：5)

首先进行一个题意转换。

考虑怎样的子串是合法的。

显然，我们可以让一个串的两头放上虚拟的 $1$，那么对于每一个原来的 $1$，两头必然有 $1$。

$\begin{matrix}1,\underbrace{0,\cdots,0},1,\underbrace{0,\cdots,0},1\end{matrix}$。

左边有 $x$ 个 $0$，右边有 $y$ 个 $0$。

那么，中间这个 $1$ 对答案的贡献就是 $(x+1)(y+1)$，需要满足的条件是 $x+y+1<k$。

发现这个条件比较丑，所以可以记 $a_i=x+1,a_{i+1}=y+1$，那么，这两个 $0$ 中间的贡献就是 $a_ia_{i+1}$，需要满足条件 $a_i+a_{i+1}\le k+1$。

所以，题目转换成了，求数列 $a_1,a_2,\cdots,a_n$，满足 $\forall 1\le i<n,a_i+a_{i+1}\le k+1,\sum\limits_{i=1}^{n-1}a_ia_{i+1}=n$。

转移方程就很简单了。

记 $f_{i,j}$ 为剩余 $i$ 要被分掉，上一个数是 $j$ 的方案总数。

枚举第一个数，统计贡献即可。

由于我是个蒟蒻，所以只会用记搜的方式写。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2505, mod = 998244353;
int T, n, k, f[N][N], ans;
inline int solve(int x, int y){
	if(~f[x][y]) return f[x][y];
	f[x][y] = 0ll;
	for(int i = 1; i <= k - y && i * y <= x; i++){
		(f[x][y] += solve(x - i * y, i)) %= mod;
	}
	return f[x][y];
}
signed main(){
	scanf("%lld", &T);
	while(T--){
		scanf("%lld%lld", &n, &k);
		k++;
		for(int j = 1; j <= n; j++) f[0][j] = 1;
		for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) f[i][j] = -1;
		ans = 0ll;
		for(int j = 1; j <= n && j < k; j++){
			(ans += solve(n, j)) %= mod;
		}
		printf("%lld\n", ans);
	}
	return 0;
}
/*
1
3 2
*/
```

---

## 作者：waauto (赞：5)

[CF1920E](https://www.luogu.com.cn/problem/CF1920E)

感觉有点过于简单了这一场的 E。

考虑序列从 $1$ 断开。

对于一个 $01$ 串的数量就是 $\sum (a_i+1)\times (a_{i-1}+1)$

设 $f_{i,j}$ 表示还差 $j$ 达到答案，最后一个长度是 $i$ 的方案数。

那么就有：

$$
f_{i,j}=\sum_{k=0}^{(k+1)\times(i+1)\le j} f_{k,j-(k+1)\times(i+1)}
$$

第二维一直减小，并且枚举次数调和级数，直接记忆化搜索就行。

```cpp
int f[N][N];
int n,maxn;
inline int dfs(int lst,int now){
	if(f[lst][now]!=-1)return f[lst][now];
	if(!now)return 1;
	f[lst][now]=0;
	F(i,0,n){
		if((lst+1)*(i+1)>now or lst+i>=maxn)break;
		f[lst][now]+=dfs(i,now-(lst+1)*(i+1));
		f[lst][now]%=mod;
	}
	return f[lst][now];
}
inline void mian(){
	cin>>n>>maxn;
	F(i,0,n)F(j,0,n)f[i][j]=-1;
	int ans=0;
	F(i,0,n){
		ans=(ans+dfs(i,n))%mod;
	}
	cout<<ans<<'\n';
}
```

---

## 作者：toolong114514 (赞：2)

# CF1920E Counting Binary Strings 题解
upd on 2024/7/4：修正一处关于时间复杂度的笔误。
## 题面大意
[传送门。](https://www.luogu.com.cn/problem/CF1920E)
## 解题思路
### 准备工作
首先考虑计算好串的贡献。

注意到好串中有且仅有一个 $1$，那么可以讨论串中每个 $1$ 带来的贡献。

定义“边界”为串中一个 $1$ 到字符串末尾或相近的另一个 $1$ 之间连续 $0$ 串的最远处。

容易发现，一个 $1$ 只有两个边界，边界有可能是当前 $1$ 本身。

定义 $1$ 到左侧边界长为 $dis_1$，到右侧边界长为 $dis_2$。

根据[乘法原理](https://baike.baidu.com/item/%E4%B9%98%E6%B3%95%E5%8E%9F%E7%90%86/7538447?fr=ge_ala)，一个 $1$ 的贡献可以用下列式子表示：

$$dis_1\cdot dis_2$$
### 正题
定义 $f_{i,j}$ 为当前串产生的贡献为 $i$，最右端的的 $1$ 到其右侧边界的长为 $j$ 时的方案数。

考虑如何构建当前的状态。

我们可以从其它的串末尾拼接一个 $1$，加上若干个 $0$ 得到。

这时，枚举并反推上一个状态（贡献和边界长）是容易的。

根据上述结论，可以得到以下 DP 转移方程：

$$f_{i,j}=\sum_{\text{t 是合法的}}f_{i-t\cdot j,t}$$

接下来要讨论 $t$ 的限制。

发现减去后贡献必须为正，那么有；$i-t\cdot j\geqslant0$。

解得 $t\le \frac{i}{j}$。

注意到好串长度不能超过 $k$，那么有：$j+t-1\le k$。

解得 $t\le k+1-j$。

综上所述，$t$ 满足的限制如下：
$$\begin{cases}t\le \frac{i}{j}\\t\le k+1-j\end{cases}$$

剩下的还有一些常规的操作，比如下界和初始值为 $1$ 的状态，就不多说了。

最终状态转移方程为：
$$f_{i,j}=\sum_{t=1}^{\min(\frac{i}{j},k+1-j)}f_{i-t\cdot j,t}$$

按上述思路写代码即可。

时间复杂度的上界似乎是 $O(n^3)$，其实由于存在 $\min(\frac{i}{j},k+1-j)$ 的缘故，时间复杂度的其实约为 $O(n^2\ln n)$（用 $\LaTeX$ 计算器算的是 $O(\sum_{i=1}^{n} i \operatorname{harmonic}i)$），可以通过本题。
## 参考代码
```cpp
#include<iostream>
#include<cstring>
using namespace std;
const int mod=998244353;
#define int long long
int f[5005][5005];
int t,n,k,ans;
signed main(){
    ios::sync_with_stdio(false);
    cin>>t;
    while(t--){
        cin>>n>>k;
        for(int i=1;i<=k;i++){
            f[0][i]=1;
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=i;j++){
                for(int t=1;t<=min(i/j,k+1-j);t++){
                   f[i][j]+=f[i-t*j][t];
                    f[i][j]%=mod;
                }
            }
        }
        ans=0;
        for(int i=0;i<=n;i++){
            ans+=f[n][i];
            ans%=mod;
        }
        cout<<ans<<'\n';
        for(int i=1;i<=n;i++){
        	for(int j=1;j<=n;j++){
        		f[i][j]=0;
			}
		}
    }
    return 0;
}
```
[本代码可以通过 CF 的评测。](https://www.luogu.com.cn/record/163631101)

Written by [toolong114514](www.luogu.com/user/477821) on 2024/7/2.

---

## 作者：nullqtr_pwp (赞：1)

首先考虑枚举 $1$ 的个数为 $t$，设任意相邻两个 $1$ 中间 $0$ 的个数为 $a_i$，那么有数列 $a_0,a_1,\cdots,a_t$，其中 $a_0,a_t$ 分别为首尾 $0$ 的个数。

考虑对每个 $1$ 统计答案，好子串的个数即为：$\sum_{i=0}^{t-1}(a_i+1)(a_{i+1}+1)$，这个柿子是在分别取左端点以及右端点然后相乘。对于 $a$ 序列，要求：$\sum_{i=0}^t{a_i}+t=n,a_i+a_{i+1}\leq k-1$。

计数问题容易想到用 dp 求解。考虑设计状态。若 $f_{p,i,j}$ 表示当前状态下有 $p$ 个 $1$，好串个数为 $i$，$a_t=j$，由于需要枚举 $p$ 以及最后的两个数进行转移，实际上是 $O(n^3\log n)\sim O(n^4)$ 的，无法通过本题。

$O(n^3\log n)$ 做法：
```cpp
F(i,0,n) F(j,0,n) f[i][j]=0;
F(i,0,n) f[0][i]=1;
mint ans=0;
F(i,1,n){
	F(x,0,n) F(y,0,n) g[x][y]=f[x][y],f[x][y]=0;
	F(x,0,n) F(y,0,min(k-x-1,n/(x+1))){
		int t=(x+1)*(y+1);
		F(p,0,n-t) f[p+t][y]+=g[p][x];
	}
	F(j,0,n) ans+=f[n][j];
}
```
这个状态已经没法要了，考虑优化状态设计。重新审视转移，只考虑枚举最后两个数为 $x,y$，然后对好串个数产生新的贡献 $(x+1)(y+1)$，与有多少个 $1$ 没有太大的关系。所以我们发现 $t$ 那一维度可以去掉，直接枚举好子串个数为 $1\sim n$ 即可。改为 $f_{i,j}$ 为好串个数 $i$，$a_t=j$ 的个数。这样做可以去掉枚举 $1$ 的个数所带来的 $O(n)$ 的不必要的复杂度。

转移方程为 $f_{i,j}=\sum_{p=0}^{k-1} f_{i-(j+1)(p+1),p}$，枚举最后两个数为 $j,p$，要求 $(j+1)(p+1)\leq i$ 且 $j+p+3\leq k$。注意有第一个限制条件，$(j,p)$ 的个数是 $O(n\log n)$ 的。

乘上枚举好串个数的 $O(n)$，那么时间复杂度为 $O(n^2\log n)$。

```cpp
int n=read(),m=read();
F(i,1,m) f[0][i]=1;
F(i,1,n) F(j,1,m){
	f[i][j]=0;
	F(k,1,m){
		if(j+k-1>m||j*k>i) break;
		f[i][j]+=f[i-j*k][k];
	}
} 
mint ans=0;
F(i,1,m) ans+=f[n][i];
printf("%lld\n",ans.x);
```

---

## 作者：hanjinghao (赞：1)

## 题意

多组询问。对于每组询问，给定两个正整数 $ n, k $，满足 $ 1 \le k \le n \le 2500 $。保证所有询问中 $ n $ 的总和不超过 $ 2500 $。

定义一个 $ 0/1 $ 字符串是好的，当且仅当它恰好有一个 $ 1 $。

问有多少种 $ 0/1 $ 字符串，满足其恰好有 $ n $ 个好的子串，且任意一个好的子串长度不超过 $ k $。

## 思路

设 $ f_{i, j, 0} $ 表示当前已经有 $ i $ 个好的子串，字符串末尾是 $ 0 $，末尾的 $ 0 $ 的连续段长度为 $ j $ 的方案数；$ f_{i, j, 1} $ 表示当前已经有 $ i $ 个好的子串，字符串末尾是 $ 1 $，末尾的 $ 1 $ 的左边的 $ 0 $ 的连续段长度为 $ j $ 的方案数。

令第一个 $ 1 $ 的位置为 $ x $，则 $ f_{x, x - 1, 1} = 1 $。显然，$ 1 \le x \le k $。

接下来，对于 $ f_{i, j, 0} $，在末尾加上一个 $ 1 $，好的子串个数会增加 $ j + 1 $，因此 $ f_{i, j, 0} $ 要转移到 $ f_{i + j + 1, j, 1} $。

对于 $ f_{i, j, 1} $，在末尾加上 $ l $ 个 $ 0 $，好的子串个数会增加 $ l \times (j + 1) $，因此 $ f_{i, j, 1} $ 要转移到 $ f_{i + l \times (j + 1), l, 0} $。因为 $ i + l \times (j + 1) \le n $，所以 $ l \le (n - i) \div (j + 1) $。又因为 $ 0 \le j \le k - 1 $，所以这部分的时间复杂度是调和级数。

总时间复杂度为 $ O(n ^ 2 \log n) $，空间复杂度为 $ O(n ^ 2) $。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

template < typename T >
inline void read(T &x)
{
	bool flg = x = 0;
	char c;
	while ((c = getchar()) < 48 || c > 57)
		flg |= c == '-';
	do
		x = (x << 1) + (x << 3) + (c ^ 48);
	while ((c = getchar()) > 47 && c < 58);
	if (flg) x = -x;
}

int OUTPUT[45];

template < typename T >
inline void write(T x)
{
	if (x < 0)
	{
		putchar('-');
		x = -x;
	}
	int len = 0;
	do
	{
		OUTPUT[++len] = x % 10 | 48;
		x /= 10;
	}while (x);
	while (len)
		putchar(OUTPUT[len--]);
}

template < typename T >
inline void writesp(T x)
{
	write(x);
	putchar(32);
}

template < typename T >
inline void writeln(T x)
{
	write(x);
	putchar(10);
}

const int N = 3005, P = 998244353;
int f[N][N][2];

inline void Add(int &x, int y)
{
	x += y;
	if (x >= P) x -= P;
}

int main()
{
	int T;
	read(T);
	while (T--)
	{
		int n, k;
		read(n);
		read(k);
		for (int i = 0; i <= n; ++i)
			for (int j = 0; j <= k; ++j)
				f[i][j][0] = f[i][j][1] = 0;
		for (int i = 1; i <= k; ++i)
			f[i][i - 1][1] = 1;
		for (int i = 1; i < n; ++i)
		{
			for (int j = 0; j < k; ++j)
			{
				if (f[i][j][1])
				{
					int tmp;
					for (int l = 0; j + l + 1 <= k && (tmp = i + l * (j + 1)) <= n; ++l)
						Add(f[tmp][l][0], f[i][j][1]);
				}
			}
			for (int j = 0; j < k; ++j)
			{
				if (f[i][j][0])
				{
					int tmp = i + j + 1;
					if (tmp <= n) Add(f[tmp][j][1], f[i][j][0]);
				}
			}
		}
		int ans = 0;
		for (int i = 0; i < k; ++i)
		{
			Add(ans, f[n][i][0]);
			Add(ans, f[n][i][1]);
		}
		writeln(ans);
	}
	return 0;
}
```

---

## 作者：_Flame_ (赞：0)

### $\text{solution}$

萌萌数数题。

考虑每个 $1$ 能产生多少贡献，发现一个一的贡献显然为两边 $0$ 的个数的乘积。

考虑对 $1$ 进行转移，设一个状态 $dp_{i,j}$ 表示当前已经有 $i$ 个合法子串，现在是 $1$ 且到上一个 $1$ 之间距离为 $j$ 的方案数，枚举一个距离 $len$，不考虑长度最大为 $k$ 的条件下，显然有转移如下：

$$dp_{i,j}=\sum\limits_{len=1}^{\frac{i}{j}} dp_{i-len\times j,len}$$

考虑长度最大为 $k$ 的条件，发现 $len$ 的长度应为 $k+1-j$ 与 $\frac{i}{j}$ 中的最小值，于是转移变为：

$$dp_{i,j}=\sum\limits_{len=1}^{\min(\frac{i}{j},k+1-j)} dp_{i-len\times j,len}$$

转移即可。答案为 $\sum\limits_{i=1}^{n} dp_{n,i}$。



---

## 作者：MaxBlazeResFire (赞：0)

身败名裂的一集，$75$ 分钟做不出来这么个破玩意。

考虑到一个 $01$ 串最终的形态，要求的串的个数就是所有极近的两个两端均为 $1$ 的串的长度之积的和，直接对这个东西做 DP，记 $f_{i,j}$ 表示总贡献为 $i$，上一段长度为 $j$ 的方案数，转移为 $\displaystyle f_{i,j}=\sum_{p=1}^{\min\{\frac{i}{j},k+1-j\}}f_{i-p\times j,p}$，复杂度 $O(n^2\ln n)$。

赛时打一开始就想着对原序列直接做，属实是糖丸了。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long

#define mod 998244353
#define MAXN 2505

inline void chkadd( int &x , int k ){ x += k; if( x >= mod ) x -= mod; }

int n,k,f[MAXN][MAXN];

inline void solve(){
	scanf("%lld%lld",&n,&k);
	for( int i = 1 ; i <= k ; i ++ ) f[0][i] = 1;
	for( int i = 1 ; i <= n ; i ++ )
		for( int j = 1 ; j <= i ; j ++ )
			for( int p = 1 ; p <= min( i / j , k + 1 - j ) ; p ++ )
				chkadd( f[i][j] , f[i - p * j][p] );
	int Ans = 0;
	for( int i = 1 ; i <= n ; i ++ ) chkadd( Ans , f[n][i] );
	printf("%lld\n",Ans);
	for( int i = 0 ; i <= n ; i ++ ) for( int j = 1 ; j <= n ; j ++ ) f[i][j] = 0;
}

signed main(){
	int testcase; scanf("%lld",&testcase);
	while( testcase -- ) solve();
	return 0;
}
```

---

