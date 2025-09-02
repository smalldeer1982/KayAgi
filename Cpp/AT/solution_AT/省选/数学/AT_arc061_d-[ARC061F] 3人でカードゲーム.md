# [ARC061F] 3人でカードゲーム

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc061/tasks/arc061_d

A さん、B さん、C さんの $ 3 $ 人が以下のようなカードゲームをプレイしています。

- 最初、$ 3 $ 人はそれぞれ `a`、`b`、`c` いずれかの文字が書かれたカードを、A さんは $ N $ 枚、B さんは $ M $ 枚、C さんは $ K $ 枚持っている。$ 3 $ 人は、持っているカードを並べ替えることはできない。
- A さんのターンから始まる。
- 現在自分のターンである人がカードを $ 1 $ 枚以上持っているならば、そのうち先頭のカードを捨てる。その後、捨てられたカードに書かれているアルファベットと同じ名前の人 (例えば、カードに `a` と書かれていたならば A さん) のターンとなる。
- 現在自分のターンである人がカードを $ 1 $ 枚も持っていないならば、その人がゲームの勝者となり、ゲームは終了する。

$ 3 $ 人が最初に配られるカードに書いてある文字の並びは、全部で $ 3^{N+M+K} $ 通りの組み合わせがあります。このうち、A さんが勝者となってゲームが終了するのが何通りあるかを求めてください。

答えは大きくなる可能性があるので、$ 1\,000\,000\,007\ (=10^9+7) $ で割った余りを出力してください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 3×10^5 $
- $ 1\ \leq\ M\ \leq\ 3×10^5 $
- $ 1\ \leq\ K\ \leq\ 3×10^5 $

### 部分点

- $ 1\ \leq\ N\ \leq\ 1000 $、 $ 1\ \leq\ M\ \leq\ 1000 $、 $ 1\ \leq\ K\ \leq\ 1000 $ を満たすデータセットに正解した場合は、 $ 500 $ 点が与えられる。

### Sample Explanation 1

\- A さんが `a` を持っている場合は、他の $ 2 $ 人の持っているカードに関わらず A さんが勝ちます。これは $ 3×3=9 $ 通りあります。 - A さんが `b` を持っている場合は、B さんが `a` を持っているか、 B さんが `c` を持っていてかつ C さんが `a` を持っている場合に限り A さんが勝ちます。これは $ 3+1=4 $ 通りあります。 - A さんが `c` を持っている場合は、C さんが `a` を持っているか、 C さんが `b` を持っていてかつ B さんが `a` を持っている場合に限り A さんが勝ちます。これは $ 3+1=4 $ 通りあります。 合計すると、 $ 9+4+4=17 $ 通りとなります。

## 样例 #1

### 输入

```
1 1 1```

### 输出

```
17```

## 样例 #2

### 输入

```
4 2 2```

### 输出

```
1227```

## 样例 #3

### 输入

```
1000 1000 1000```

### 输出

```
261790852```

# 题解

## 作者：command_block (赞：39)

**题意** ： 有三堆牌，分别有 $n_1,n_2,n_3$ 张。牌上写着数字 
$1,2,3$ 中的一个。

先从牌堆 $1$ 中抽一张，接下来，牌上写着几就从几号牌堆抽取。

求在所有可能的 $3^{n_1+n_2+n_3}$ 种方案中，先把牌堆 $1$ 抽空的方案数。

答案对 $10^9+7$ 取模。

$n_1,n_2,n_3\leq 3\times 10^5$ ，时限 $\texttt{3s}$。

------------

条件计数的路子无非两条，要么寻找更简洁的充要条件，要么容斥。

题目中的过程比较精巧，考虑寻找充要条件。

把抽取出的牌排成一个序列，显然，每种放置方式都恰好对应一个序列。（构造映射）

但是，由于可能拿不完牌，所以一个序列可能对应很多种方案，具体地，一个长为 $m$ 的序列对应 $3^{n_1+n_2+n_3-m}$ 种方案。（检查反映射）

我们思考对这个序列的约束，可以发现，除了率先将堆 $1$ 拿空之外，没有任何约束。（检查充要条件）

于是，问题就变成了 ： 对每个长度，求先将堆 $1$ 拿空的序列个数。

显然，操作序列中一定恰有 $n_1$ 个 $1$ ，且最后一个必须是 $1$。

枚举抽出的非 $1$ 牌个数 $k$ ，方案数为 $\dbinom{k+n_1-1}{k}\sum\limits_{i=0}^k[i\leq n_2][k-i\leq n_3]\dbinom{k}{i}$

解释一下，$\binom{k+n_1-1}{k}$ 表示 $n_1-1$ 个自由的 $1$ 与非 $1$ 混合的方案数，后面的求和是瓜分非 $1$ 牌的方案数。

但糟糕的是，后半部分是一个组合数部分和，这似乎没有什么快速的方法分别求解，考虑递推。

$S(k)=\sum\limits_{i=0}^k[i\leq n_2][k-i\leq n_3]\dbinom{k}{i}$

$=\sum\limits_{k-n_3\leq i\leq n_2}\dbinom{k}{i}$

将组合数裂开 ;

$=\sum\limits_{k-n_3\leq i\leq n_2}\dbinom{k-1}{i}+\dbinom{k-1}{i-1}$

$=\sum\limits_{k-n_3\leq i\leq n_2}\dbinom{k-1}{i}+\sum\limits_{k-n_3-1\leq i\leq n_2-1}\dbinom{k-1}{i}$

$=2S(k-1)-\dbinom{k-1}{k-n_3-1}-\dbinom{k-1}{n_2}$

注意组合数可能不合法，此时值为 $0$。

求出各个 $S(k)$ 之后，答案即为下式 ：

$$\sum\limits_{k=0}^{n_2+n_3}3^{n_1+n_2+n_3-k}\dbinom{n_1-1+k}{k}S(k)$$

不看题解玩出来还是有点小激动的……

```cpp
#include<algorithm>
#include<cstdio>
#define ll long long
#define MaxN 900500
using namespace std;
const int mod=1000000007;
ll powM(ll a,int t=mod-2){
  ll ret=1;
  while(t){
    if (t&1)ret=ret*a%mod;
    a=a*a%mod;t>>=1;
  }return ret;
}
ll fac[MaxN],ifac[MaxN];
ll C(int n,int m){
  if (m<0||n<m)return 0;
  return fac[n]*ifac[m]%mod*ifac[n-m]%mod;
}
void Init(int n)
{
  fac[0]=1;
  for (int i=1;i<=n;i++)
    fac[i]=fac[i-1]*i%mod;
  ifac[n]=powM(fac[n]);
  for (int i=n;i;i--)
    ifac[i-1]=ifac[i]*i%mod;
}
void preS(int n2,int n3,ll *S)
{
  S[0]=1;
  for (int k=1;k<=n2+n3;k++)
    S[k]=(2*S[k-1]-C(k-1,k-1-n3)-C(k-1,n2))%mod;
    
}
int n1,n2,n3,N;
ll S[MaxN],pw3[MaxN];
int main()
{
  scanf("%d%d%d",&n1,&n2,&n3);
  Init(N=n1+n2+n3);
  preS(n2,n3,S);
  ll ans=0,buf=powM(3,N-n1),sav=powM(3);
  for (int k=0;k<=n2+n3;k++){
    ans=(ans+buf*C(n1+k-1,k)%mod*S[k])%mod;
    buf=buf*sav%mod;
  }printf("%lld",(ans+mod)%mod);
  return 0;
}
```




---

## 作者：No21 (赞：6)

### 前置芝士

$$\dbinom{n}{m}=\frac{n!}{m!(n-m)!}$$


------------

### 题意分析

纸牌堆相当于一个序列，所以简单理解即：$a,b,c$ 三个玩家**每个人面前有一个序列**（注意是有三个序列，蒟蒻第一次理解成了三个人共用一个序列，qwq），每个序列由三种字符组成，分别为 $a,b,c$，即为三个玩家的编号。

由 $a$ 开始游戏。$a$ 拿出他序列的第一个字符，然后扔掉它，下一步则由 $a$ 拿出的字符对应的玩家进行，以此类推，直到一个玩家的序列为空，则此玩家获胜，求 $a$ 获胜的情况数，答案对 $10^9+7$ 取模。


------------

### 解题思路

- 首先，求 $a$ 获胜的情况数等价于已处理序列的情况数，所以我们选择处理更具体的已处理序列。
- 我们考虑什么情况下 $a$ 获胜，不难得出 $a$ 获胜的充要条件，设 $a,b,c$ 的序列中分别有 $A,B,C$ 个字符，对已经处理过的序列来说，必须满足：

  1. 已操作序列中必须有 $A$ 个 $a$，（因为 $a$ 要将自己的序列全部处理，即 $a$ 要做 $A$ 次操作），且已操作序列中最后一个字符为 $a$。

  2. 已操作序列中 $b$ 的个数不能超过 $B$（如果有大于 $B$ 个 $b$ ，则 $b$ 已经胜利，游戏结束），$c$ 的个数不能超过 $C$（理由同上）。
 
 - 我们已经知道，对于已处理序列，其中有 $A$ 个 $a$，并且最后一个字符也一定为 $a$。我们设已处理序列中 $b$ 和 $c$ 的个数和为 $k$，所以对于 $a$ 来说（先不考虑 $b$ 和 $c$），有 $\dbinom{k+A-1}{A-1}$ 种情况。我们枚举 $k$，讨论 $b$ 和 $c$ 的的排列情况。对于每个 $k$，我们设 $f(k)$ 为每个 $k$ 下的情况数。则有 $f(k)=\sum\limits_{i=k-C}^{B} \dbinom{k}{i} $。
 
 - 下指标求和显然是要比上指标求和难亿点的（因为后者有公式而前者没有，qwq）。我们考虑用递推公式对其进行展开：
 
   $$ \begin{aligned}f (k)&=\sum\limits_{i=k-C}^{B} \dbinom{k}{i} \\&=\sum\limits_{i=k-C}^{B} \dbinom{k-1}{i}+\dbinom{k-1}{i-1}\\&=\sum\limits_{i=k-C}^{B} \dbinom{k-1}{i}+\sum\limits_{i=k-C}^{B} \dbinom{k-1}{i-1}\end{aligned}$$
   
   转化完成后，$f(k)$ 变成了两部分，不难发现，对每一部分来说，都有与 $f(k-1)$ 相似的部分，我们列出：
   
   $$f(k-1)=\sum\limits_{i=k-C-1}^{B} \dbinom{k-1}{i}$$ 
   
   对于第一部分（即加号前的部分），不难得到：
   
   $$\sum\limits_{i=k-C}^{B} \dbinom{k-1}{i}=\sum\limits_{i=k-C-1}^{B} \dbinom{k-1}{i}-\dbinom{k-1}{k-C-1}$$
   
   对于第二部分（即加号后的部分），不难得到：
   
   $$\sum\limits_{i=k-C}^{B} \dbinom{k-1}{i-1}=\sum\limits_{i-1=k-C-1}^{B} \dbinom{k-1}{i-1}$$
   
   用 $i$ 替换 $i-1$： 
   
   $$\begin{aligned} \sum\limits_{i-1=k-C-1}^{B} \dbinom{k-1}{i-1}&=\sum\limits_{i=k-C-1}^{B-1} \dbinom{k-1}{i}\\&=\sum\limits_{i=k-C-1}^{B} \dbinom{k-1}{i}-\dbinom{k-1}{B} \end{aligned}$$
   
   至此，我们便得到了：
   
   $$f(k)=2f(k-1)-\dbinom{k-1}{k-C-1}-\dbinom{k-1}{B}$$
   
- 结束了吗？当然没有。别忘了我们只是求得了 $f(k)$，我们还要求出总答案，即为：

  $$\sum\limits_{k=0}^{B+C} f(k)\dbinom{k+A-1}{A-1}3^{B+C-k}$$
  
  上代码（码风很丑，大佬勿喷qwq）：

 ```cpp
#include<bits/stdc++.h>
using namespace std;
namespace TO
{
	const int mod=1e9+7, N=3e5+21;
	int A,B,C;
	long long ans;
	int dp[N*3],fac[N*3],ifac[N*3];
	int ksm(int a,int b)
	{
		int c=1;
		while(b)
		{
			if(b&1)
				c=1ll*c*a%mod;
			a=1ll*a*a%mod;
			b/=2;
		}
		return c;
	}
	int CC(int n,int m)
	{
		return n<0||m<0||n<m ? 0 : 1ll*fac[n]*ifac[m]%mod*ifac[n-m]%mod;
	}
	int mian()
	{
		cin>>A>>B>>C;
		fac[0]=1;
		ifac[0]=1;
		for(int i=1;i<N*3;i++)
			fac[i]=1ll*fac[i-1]*i%mod;
		ifac[N*3-1]=ksm(fac[N*3-1],mod-2)%mod;
		for(int i=N*3-1;i;i--)
			ifac[i-1]=1ll*ifac[i]*i%mod;
		dp[0]=1;
		for(int i=1;i<=B+C;i++)
			dp[i]=(1ll*2*dp[i-1]-CC(i-1,i-C-1)-CC(i-1,B)+2*mod)%mod;
		for(int i=0;i<=B+C;i++)
			ans=(1ll*ans+1ll*ksm(3,B+C-i)*CC(i+A-1,A-1)%mod*1ll*dp[i]%mod)%mod;
		cout<<ans;
		return 0;
	}
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	return TO::mian();
}
 ```
 
 完结撒花！

---

## 作者：Soulist (赞：5)

**题意：**

给定 $a,b,c$ 表示 A 有 $a$ 张牌依次排列，B 有 $b$ 张牌依次排列，C 有 $c$ 张牌依次排列，每张牌可以是 A，B，C 中任意一种。

A 先操作，拿出第一张牌，然后让上面写的人重复此流程，谁最先操作完谁 win

求方案数使得 A win

- $a,b,c\le 3\cdot 10^5$。

---

$\rm Sol:$

首先考虑这样的一件事，假设 A 操作完后依次取出来的字符是 AABCAABC 那么其实它固定了一个取牌顺序。

同时任意一个这样的序列都可以对应一个取牌顺序。

然后我们发现 B win 等价于取出了 $b+1$ 个 B，同理于 C，而 A win 则等价于取出了 $a$ 个 A

所以我们枚举其长度，规定最后一个位置为 A，那么剩余位置中至多填入 $b$ 个 B，$c$ 个 C，$a$ 个 A，方便起见我们令 $N=a-1+b+c$，然后令 $a$ 减 $1$

于是所求为：

$$\sum_{i=a}^{N} \binom{i}{a}\cdot 3^{N-i}\sum_{j+k=i-a,j\le b,k\le c} \binom{i-a}{j}$$

后面的条件 $k\le c$ 等价于 $i-a-c\le j\le b$

于是所求为：

$$\sum_{i=a}^{N} \binom{i}{a}\cdot 3^{N-i-1}\sum_{\max\{0,i-a-c\}\le j\le b} \binom{i-a}{j}$$

我们发现后面出现了一个众所周知难以化简的式子，于是考虑递推。

我们设 $x=i-a$，那么如果 $i\le c$ 则所求为 $\sum^b \binom{i-a}{j}$

- 如果 $i\le c,b$，那么其实就是 $2^{i-a}$

- 否则 $b<i\le c$，这个时候考虑相邻两项的变换量。

即考虑 $\sum^b_j \binom{x}{j}$ 与 $\sum_j^b \binom{x+1}{j}$，前者设为 $f$，后者设为 $g$，那么有 $\sum \binom{x+1}{j}=\sum \Big(\binom{x}{j-1}+\binom{x}{j}\Big)$

所以我们得到：$g=\sum^b \binom{x}{j}+\sum^{b-1}\binom{x}{j}=2f-\binom{x}{b}$

- 若 $c<i\le b$，这个时候有 $f=\sum_{l}^x \binom{x}{j},g=\sum_{l+1}^{x+1} \binom{x+1}{j}=\sum_{l+1}^{x+1}\Big(\binom{x}{j}+\binom{x}{j-1}\Big)=2f+\binom{x}{x+1}-\binom{x}{l}$

然后考虑 $M<i$

此时有：$f=\sum_{l}^b \binom{x}{j},g=\sum_{l+1}^b \binom{x+1}{j},g=\sum^b_{l+1} (\binom{x}{j}+\binom{x}{j-1})=2f-\binom{x}{l}-\binom{x}{b}$

如果在处理组合数的递推的时候特判了负数组合数以及大于的情况，那么直接使用最后一个式子递推就可以了。

$Code:$

```cpp
#include<bits/stdc++.h>
using namespace std ;
#define Next( i, x ) for( register int i = head[x]; i; i = e[i].next )
#define rep( i, s, t ) for( register int i = (s); i <= (t); ++ i )
#define drep( i, s, t ) for( register int i = (t); i >= (s); -- i )
#define re register
#define int long long
int gi() {
	char cc = getchar() ; int cn = 0, flus = 1 ;
	while( cc < '0' || cc > '9' ) {  if( cc == '-' ) flus = - flus ; cc = getchar() ; }
	while( cc >= '0' && cc <= '9' )  cn = cn * 10 + cc - '0', cc = getchar() ;
	return cn * flus ;
}
const int N = 1e6 + 5 ; 
const int P = 1e9 + 7 ; 
int a, b, c, n, m, Ans, fac[N], inv[N] ; 
int fpow( int x, int k ) {
	int ans = 1, base = x ;
	while(k) {
		if( k & 1 ) ans = ans * base % P ; 
		base = base * base % P, k >>= 1 ; 
	} return ans % P ; 
}
int C( int x, int y ) {
	if( y > x || x < 0 || y < 0 ) return 0 ; 
	return fac[x] * inv[y] % P * inv[x - y] % P ; 
}
signed main()
{
	a = gi(), b = gi(), c = gi() ; 
	n = a + b + c, fac[0] = inv[0] = 1 ; 
	rep( i, 1, n ) fac[i] = fac[i - 1] * i % P, inv[i] = fpow( fac[i], P - 2 ) ;
	int f = 1, l = - c ; -- a ; 
	for( re int i = a; i < n; ++ i ) {
		int x = i - a ; 
		if( l > b ) break ; 
		Ans = ( Ans + f * C( i, a ) % P * fpow( 3, n - i - 1 ) % P ) % P ;
		f = ( f * 2 + P - C( x, b ) + P - C( x, l ) ) % P, ++ l ; 
	}
	printf("%lld\n", Ans % P ) ;
	return 0 ;
}
```

---

## 作者：WeLikeStudying (赞：4)

- 惭愧，惭愧。

**[题意](https://www.luogu.com.cn/problem/AT2070)**
- 有三堆牌，先取第一堆堆顶的牌，接下来牌上写几就抽第几堆堆顶。
- 问牌堆 $1$ 先被抽空的方案数。

**分析**
- 考虑什么样的操作序列可以导致 $1$ 被率先抽空，这个操作序列必须满足：有 $n_1$ 个 $1$，结尾是 $1$，$2$ 的个数不超过 $n_2$，$3$ 的个数不超过 $n_3$。
- 每个操作序列可能对应多个排堆，具体地，一个长度为 $n$ 的操作序列对应 $3^{n_1+n_2+n_3-n}$ 个牌堆。
- 现在我们的任务变成了考虑计算对于每个 $n$，长度为 $n$ 的合法操作序列个数，不论如何，我们都有简单的 $O(n^2)$ 做法是显然的，[代码](https://www.luogu.com.cn/paste/ngvcrxeg)。
- 我们考虑把问题具体化，我们需要求解（由于结尾是 $1$，所以数目要减一）：
$$f(n)=\sum_{i=0}^{n_2}[n_1+i+n_3\ge n]\frac{(n-1)!}{(n_1-1)!i!(n-n_1-i)!}$$
- ~~我们发现这可以表示成卷积的形式，所以直接 MTT~~，别想了作者不会多项式，你发现：
$$f(n)=C(n-1,n_1-1)\sum_{i=\max(n-n_1-n_3,0)}^{n_2}C(n-n_1,i)$$
- 设：
$$g(n,m)=\sum_{i=0}^mC(n,i)$$
- 由于 $C(n,m)=C(n-1,m)+C(n-1,m-1)$，裂项可得：
$$g(n,m)=\sum_{i=0}^mC(n,i)=\sum_{i=0}^{m-1}C(n-1,i)+\sum_{i=0}^{m}C(n-1,i)=2\sum_{i=0}^{m-1}C(n-1,i)+C(n-1,m)$$
$$g(n,m)=2g(n-1,m-1)+C(n-1,m)$$
- 同理：
$$g(n,m)=2g(n-1,m)-C(n-1,m)$$
- 利用这两个简单的递推关系，我们最终可以线性求解 $f(n)$ 的所有取值。
- 对于一类较为复杂的计数问题，也许可以尝试这种思路：即找到一类映射，它比较好计数，对于每个特定的映射对应的组合对象，也比较好计数，如此就有可能对复杂的问题化繁为简，[代码](https://www.luogu.com.cn/paste/8wpf05sw)。

---

## 作者：abruce (赞：4)

考虑进行这样一个双射：构造一个序列，当游戏还在进行时，我们每次将当次处于自己的回合的人堆顶的卡牌放在序列最后。当游戏结束后，我们按照 a b c 的顺序从堆顶到堆底将卡牌依次放在序列最后，不难发现这样与原序列三堆卡牌是一一对应的。  
在这个新序列（我们称之为 $p$）中，a 的胜利条件变成一个前缀出现 $n$ 张 a，b 的胜利条件为一个前缀出现 $m+1$ 张 b,c 和 b 同理。多个胜利条件在 $p$ 中同时满足时谁前缀越靠前谁赢得真正的胜利。考虑对这个序列进行计数。  
我们首先枚举 a 第 $n$ 次出现的位置，设其为 $i$。那么在 $p_1\sim p_{i-1}$ 中，出现了 $n-1$ 次 a，方案数 $\binom{i-1}{n-1}$。$p_{i+1}\sim p_{n+m+k}$ 可以任意放数，方案数 $3^{n+m+k-i}$。考虑在 $p_1\sim p_{i-1}$ 所剩下的 $i-n$ 个放 b 和 c 的位置。  
设第放 $i$ 个 b 和 c 使它们不会提前胜利的方案数为 $f_i$，考虑容斥。我们先在 $f_{i-1}$ 的基础上随便放 b 或 c，方案数 $2f_{i-1}$。考虑在 $i$ 位非法情况即为到第 $i$ 位恰好放了 $m+1$ 个 b 或 $k+1$ 个 c，而这两个条件不能同时满足。于是我们钦定第 $i$ 位放 b，前面 $i-1$ 位再放 $m$ 个 b 即可不合法，c 同理。于是 $f$ 的转移式 $f_i=2f_{i-1}-\binom{i-1}{m}-\binom{i-1}{k}$。  
有了 $f$，a 第 $n$ 次出现的位置为 $i$ 的答案即为 $3^{n+m+k-i}f_{i-n}\binom{i-1}{n-1}$，求和即可。  
时间复杂度 $O(n+m+k)$。代码中用类似滚动变量的方式递推 $f$。  
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=1e6+5,mod=1e9+7;
ll fac[maxn],inv[maxn],ans,pw3[maxn];
int n,m,k;
ll qpow(ll x,int y)
{
	ll w=1;
	while(y)
	{
		if(y&1)w=w*x%mod;
		x=x*x%mod,y>>=1;
	}
	return w;
}
ll C(int x,int y)
{
	if(y>x||y<0)return 0;
	return fac[x]*inv[x-y]%mod*inv[y]%mod;
}
int main()
{
	scanf("%d%d%d",&n,&m,&k),fac[0]=pw3[0]=1;
	for(int i=1;i<maxn;i++)fac[i]=fac[i-1]*i%mod,pw3[i]=pw3[i-1]*3%mod;
	inv[maxn-1]=qpow(fac[maxn-1],mod-2);
	for(int i=maxn-1;i;i--)inv[i-1]=inv[i]*i%mod;
	ll sum=1;
	for(int i=n;i<=n+m+k;i++)ans=(ans+C(i-1,n-1)*sum%mod*pw3[n+m+k-i])%mod,sum=(sum*2-C(i-n,m)-C(i-n,k)+mod*2)%mod;
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：ReTF (赞：2)

首先设状态 $(A,B,C)$ 表示 $a$ 拿了 $A$ 张牌，$b$ 拿了 $B$ 张牌，$c$ 拿了 $C$ 张牌。

题目可以抽象成三维空间里每次向某一维的正方向走一个单位长度，从 $(1,0,0)$ 走到 $(N,i,j)(i\le M,j\le K)$ 的方案数乘上 $3^{M+K-i-j}$ 再求和。

枚举 $i+j$ 的值 $s$，答案是 

$$\sum_{s}\dbinom{N-1+s}{s}\sum_{i=0}^M\sum_{j=0}^K[i+j=s]\dbinom{i+j}{i}3^{M+K-s}$$

即

$$\sum_{s}\dbinom{N-1+s}{s}s!\sum_{i=0}^M\sum_{j=0}^K[i+j=s]\dfrac{3^{M-i}}{i!}\dfrac{3^{K-j}}{j!}$$

发现后半部分是个卷积，使用任意模数 NTT 可以做到线性对数。

---

## 作者：zac2010 (赞：2)

先进行一个模型转换：要求满足以下条件的字符串数量：

* 由 `a`、`b`、`c` 三种字符组成。
* 其中恰好有 $n$ 个 `a`，且以 `a` 结尾。
* `b` 不超过 $m$ 张，`c` 不超过 $k$ 张。

思考转换的过程：每个字符对应抽到的卡牌。其中第二条保证了 `a` 会胜利，第三条保证了这个过程中 `b` 或 `c` 不会出现已经赢了的情况。

那么有：
$$
\text{ans}=\sum_{t=0}^{m+k} (C_{t+n-1}^{n-1}\times(\sum_{x=t-k}^{m} C_{t}^{x})\times 3^{m+k-t})
$$
设：
$$
f(t)=\sum_{x=t-k}^{m} C_{t}^{x}
$$
则：
$$
\begin{aligned}
f(t)&=\sum_{x=t-k}^{m} (C_{t-1}^{x}+C_{t-1}^{x-1}) \\
&=(\sum_{x=t-k}^{m}C_{t-1}^{x})+(\sum_{x=t-k}^{m}C_{t-1}^{x-1}) \\
&=(\sum_{x=t-k}^{m}C_{t-1}^{x})+(\sum_{x=t-k-1}^{m-1}C_{t-1}^{x}) \\
&=(f(t-1)-C_{t-1}^{t-k-1})+(f(t-1)-C_{t-1}^{m}) \\
&=2 \times f(t-1)-C_{t-1}^{t-k-1}-C_{t-1}^{m}
\end{aligned}
$$
发现现在可以在 $O(n \log {10^9+7})$ 的复杂度递推求出 $f(t)$。我们把 $f(t)$ 带入原式：
$$
\text{ans}=\sum_{t=0}^{m+k} (C_{t+n-1}^{n-1}\times f(t)\times 3^{m+k-t})
$$

当然，用来算组合数的逆元以及 $3$ 的幂次可以线性预处理，这样时间复杂度降为线性。

```cpp
#include <bits/stdc++.h>
#define L(i, a, b) for(int i = a; i <= b; i++)
#define R(i, a, b) for(int i = a; i >= b; i--)
using namespace std;
const int N = 3e5 + 10, mod = 1e9 + 7;
int n, m, k, fac[N * 3], f[N * 2], ans;
int qpow(int a, int b){
	int ans = 1;
	while(b){
		if(b & 1) ans = 1ll * ans * a % mod;
		a = 1ll * a * a % mod, b >>= 1;
	}
	return ans;
}
int inv(int x){return qpow(x, mod - 2);}
int C(int n, int m){
	if(m < 0 || m > n) return 0;
	return 1ll * fac[n] * inv(fac[m]) % mod * inv(fac[n - m]) % mod;
}
int main(){
	scanf("%d%d%d", &n, &m, &k); fac[0] = f[0] = 1;
	L(i, 1, n + m + k) fac[i] = 1ll * fac[i - 1] * i % mod;
	L(i, 1, m + k) f[i] = (2ll * f[i - 1] - C(i - 1, i - k - 1) - C(i - 1, m) + mod * 2) % mod;
	L(i, 0, m + k) (ans += 1ll * C(i + n - 1, n - 1) * f[i] % mod * qpow(3, m + k - i) % mod) %= mod;
	printf("%d\n", ans);
	return 0;
}
```


---

## 作者：do_while_true (赞：2)

orz qyc

> 小 A，小 B，小 C 在玩游戏。他们每个人分别有 $n,m,k$ 张牌，每张牌上面写着 $a,b,c$ 三个字母中的其中一个，每个回合有一个人出牌，如果出牌为 $a$ 则小 A 下一个回合出牌，如果出牌为 $b$ 则小 B 下一个回合出牌，小 C 同理。若轮到某位玩家出牌时，其手中无牌，则该位玩家获胜。
>
> 现在小 A 第一个出牌，对所有 $3^{n+m+k}$ 种手牌拥有的可能性计算小 A 获胜的方案数，对 $10^9+7$ 取模。

如果按照打出的顺序排成一个长度为 $l$ 的序列，小 A 获胜当且仅当：$a$ 恰好出现了 $n$ 次且在最后一次出现，$b$ 出现了不多于 $m$ 次，$c$ 出现了不多于 $k$ 次。

而这个长度为 $l$ 的序列对应了 $3^{n+m+k-l}$ 种手牌拥有的情况。

$n$ 次是一定打的，枚举 $b,c$ 出现的次数 $t$，然后枚举 $b$ 出现的次数 $i$：
$$
\sum_{t=0}^{m+k}\binom{n+t-1}{n-1}3^{m+k-t}\sum_{i=t-k}^{m}\binom{t}{i}
$$
第一个组合数是除了最后一个是 $a$，确定 $(n-1)$ 个 $a$ 的位置，$3^{m+k-t}$ 是计算的对应了多少种手牌拥有情况，最后一个组合数为在 $t$ 个 $b,c$ 都可以填的空位挑出 $i$ 个填 $b$，注意这个组合数可能会出现 $i<0$ 或 $i>t$ 的情况，由于是考虑其实际的组合意义，所以当出现这样的情况时视为 $0$．

最后一个实际上是组合数一行的区间和，~~众所周知~~这个的计算是困难的，由于这个区间和的形式比较特殊，考虑递推出这个东西：
$$
\begin{aligned}
S(t)=&\sum_{i=t-k}^{m}\binom{t}{i}
\\
=&\sum_{i=t-k}^{m}\binom{t-1}{i-1}+\sum_{i=t-k}^{m}\binom{t-1}{i}
\\
=&\sum_{i=t-k-1}^{m-1}\binom{t-1}{i}+\sum_{i=t-k}^{m}\binom{t-1}{i}
\\
=&\ 2\cdot\sum_{i=t-k-1}^{m}\binom{t-1}{i}-\binom{t-1}{m}-\binom{t-1}{t-k-1}
\\
=&\ 2\cdot S(t-1)-\binom{t-1}{m}-\binom{t-1}{t-k-1}
\end{aligned}
$$
至此，可以在 $\mathcal{O}(n+\log \bmod)$ 的时间复杂度内解决问题。

 [Code](https://atcoder.jp/contests/arc061/submissions/25189343)

---

## 作者：Register_int (赞：1)

假设当 $A$ 胜利后 $B$，$C$ 还分别剩下 $i$，$j$ 张牌。可以得知，先算出拿走牌的总方案数，再算出剩余牌的所有情况，就是总方案数。那么可以列出如下柿子：
$$
\begin{aligned}
&\sum^m_i\sum^k_j\dfrac{(n+m+k-i-j-1)!}{(n-1)!(m-i)!(k-j)!}\times3^{i+j}\\
=&\sum^{m+k}_{t}\dfrac{(n+m+k-t-1)!}{(n-1)!}\times3^{t}\sum^{\min(m,t)}_i\dfrac1{(m-i)!(k-t+i)!}\\
=&\sum^{m+k}_{t}n^{\overline{m+k-t}}3^{t}\sum^m_{i=\max(0,m-t)}\dfrac1{i!(m+k-t-i)!}\\
\end{aligned}
$$
设 $f(x)=\sum^m_i\dfrac{x^i}{i!},g(x)=\sum^k_i\dfrac{x^i}{i!}$，则：
$$
\begin{aligned}
&\sum^{m+k}_{t}n^{\overline{m+k-t}}3^{t}\sum^m_{i=\max(0,m-t)}\dfrac1{i!(m+k-t-i)!}\\
=&\sum^{m+k}_{t}n^{\overline{m+k-t}}3^{t}[x^{m+k-t}]f(x)g(x)\\
=&\sum^{m+k}_{t}n^{\overline{t}}3^{m+k-t}[x^{t}]f(x)g(x)
\end{aligned}
$$
一次卷积，复杂度 $O(n\log n)$。恶心的一点是，模数不仅不是 NTT 模数，还卡了空间。这里使用了三模 NTT 实现。

# AC 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 2e6 + 10;
const int mod = 1e9 + 7, inv = (mod + 1) / 3;
const ll moda = 998244353, modb = 1004535809, modc = 469762049;

inline 
ll qpow(ll b, ll p, ll m) {
    ll res = 1;
    while (p) {
        if (p & 1) res = res * b % m;
        b = b * b % m, p >>= 1;
    }
    return res;
}

const ll modab = moda * modb, inva = qpow(moda, modb - 2, modb), invab = qpow(modab % modc, modc - 2, modc);

struct num {
	ll a, b, c;
	num() {}
	num(ll t) : a(t), b(t), c(t) {}
	num(ll a, ll b, ll c) : a(a), b(b), c(c) {}
	num reduce() { return num(a + (a >> 63 & moda), b + (b >> 63 & modb), c + (c >> 63 & modc)); }
	num operator + (const num &rhs) const { return num(a + rhs.a - moda, b + rhs.b - modb, c + rhs.c - modc).reduce(); }
	num operator - (const num &rhs) const { return num(a - rhs.a, b - rhs.b, c - rhs.c).reduce(); }
	num operator * (const num &rhs) const { return num(a * rhs.a % moda, b * rhs.b % modb, c * rhs.c % modc).reduce(); }
	ll get(ll mod) {
		ll t = (b - a + modb) % modb * inva % modb * moda + a;
		return ((c - t % modc + modc) % modc * invab % modc * (modab % mod) % mod + t) % mod;
	}
};

int rev[MAXN];

num w[MAXN];

inline 
int getrev(int n) {
	int l = 1;
	while (l < n) l <<= 1;
	for (int i = 1; i < l; i++) rev[i] = (rev[i >> 1] >> 1) | (i & 1 ? l >> 1 : 0);
	w[0] = num(1);
	num t = num(qpow(3, (moda - 1) / l, moda), qpow(3, (modb - 1) / l, modb), qpow(3, (modc - 1) / l, modc));
	for (int i = 1; i <= l; i++) w[i] = w[i - 1] * t;
	return l;
}

inline 
void ntt(num *f, int n, int t) {
	for (int i = 0; i < n; i++) {
		if (i < rev[i]) swap(f[i], f[rev[i]]);
	}
	for (int i = 1; i < n; i <<= 1) {
		int p = n / i >> 1;
        for (int j = 0; j < n; j += i << 1) {
            for (int k = j; k < i + j; k++) {
                num x = (t ? w[n - p * (k - j)] : w[p * (k - j)]) * f[i + k];
                f[i + k] = f[k] - x, f[k] = f[k] + x;
            }
        }
    }
    if (t) {
    	num q = num(qpow(n, moda - 2, moda), qpow(n, modb - 2, modb), qpow(n, modc - 2, modc));
        for (int i = 0; i < n; i++) f[i] = f[i] * q;
	}
}

ll fac[MAXN], ifac[MAXN];

inline 
void init(int n) {
	*fac = 1;
	for (int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % mod;
	ifac[n] = qpow(fac[n], mod - 2, mod);
	for (int i = n; i; i--) ifac[i - 1] = ifac[i] * i % mod;
}

int n, m, k, l;

num f[MAXN], g[MAXN];

ll x = 1, y, ans;

int main() {
	scanf("%d%d%d", &n, &m, &k), init(m + k), y = qpow(3, m + k, mod);
	for (int i = 0; i <= m; i++) f[i] = ifac[i];
	for (int i = 0; i <= k; i++) g[i] = ifac[i];
	l = getrev(m + k + 1);
	ntt(f, l, 0), ntt(g, l, 0);
	for (int i = 0; i < l; i++) f[i] = f[i] * g[i];
	ntt(f, l, 1);
	for (int t = 0; t <= m + k; t++) {
		ans = (ans + x * y % mod * f[t].get(mod) % mod) % mod;
		x = x * n % mod, y = y * inv % mod, n++;
	}
	printf("%lld", ans);
}
```

---

## 作者：Prean (赞：1)

来考虑一件事情

把打牌的顺序串起来，这肯定是一条长度为 $N+M+K$ 的链。

然后相当于是在这个序列上面填数。$A$ 胜利的条件就是有一个前缀有 $n$ 个 $a$，且 $b,c$ 的数量分别不超过 $m,k$。并且容易发现一个序列肯定只对应一种牌序。

第一件事肯定是枚举这个前缀。先用组合数把 $a$ 塞进去。假设前缀的长度是 $i$，那么还剩下 $i-n$ 个位置。

这是一个二维背包。但是直接计算有点儿慢，考虑组合数。

会寄掉只可能是其中一个出现了至少 $m+1$ 或 $k+1$ 次。
$$\sum_{x=m+1}^{i-n}\binom{i-n}{x}+\sum_{x=k+1}^{i-n}\binom{i-n}{x}$$
那么答案就是：
$$\sum_{i=n}^{n+m+k}\binom{i}{n}(2^{i-n}-\sum_{x=m+1}^{i-n}\binom{i-n}{x}-\sum_{x=k+1}^{i-n}\binom{i-n}{x})3^{n+m+k-i}$$
我们设 $f[x]=\sum_{i=m}^{x}\binom{x}{i}$。

考虑这个东西：
$$f[x]=\sum_{i=m}^{x}\binom{x-1}{i}+\binom{x-1}{i-1}$$
$$f[x]=f[x-1]+f[x-1]+\binom{x-1}{m-1}$$
然后就 $O(n+m+k)$ 了。。。
```cpp
#include<cstdio>
typedef unsigned ui;
const ui M=1e6,mod=1e9+7;
ui A,B,C,F[M],G[M],pw2[M],pw3[M],fac[M],ifac[M];
inline ui binom(const ui&n,const ui&m){
	return 1ull*ifac[m]*ifac[n-m]%mod*fac[n]%mod;
}
signed main(){
	ui ans(0);scanf("%u%u%u",&A,&B,&C);
	pw2[0]=1;pw3[0]=1;fac[0]=1;ifac[0]=1;
	pw2[1]=2;pw3[1]=3;fac[1]=1;ifac[1]=1;
	for(ui i=2;i<=A+B+C;++i){
		pw2[i]=2ull*pw2[i-1]%mod;pw3[i]=3ull*pw3[i-1]%mod;ifac[i]=1ull*(mod-mod/i)*ifac[mod%i]%mod;
	}
	for(ui i=2;i<=A+B+C;++i)fac[i]=1ull*fac[i-1]*i%mod,ifac[i]=1ull*ifac[i-1]*ifac[i]%mod;
	for(ui i=B+1;i<=A+B+C;++i)F[i]=(2ull*F[i-1]+binom(i-1,B))%mod;
	for(ui i=C+1;i<=A+B+C;++i)G[i]=(2ull*G[i-1]+binom(i-1,C))%mod;
	for(ui i=A;i<=A+B+C;++i)ans=(ans+1ull*binom(i-1,A-1)*(pw2[i-A]+mod-F[i-A]+mod-G[i-A])%mod*pw3[A+B+C-i])%mod;
	printf("%u",ans);
}
```

---

## 作者：tzc_wk (赞：1)

[洛谷题面传送门](https://www.luogu.com.cn/problem/AT2070) & [Atcoder 题面传送门](https://atcoder.jp/contests/arc061/tasks/arc061_d)

首先考虑合法的排列长什么样，我们考虑将每次操作者的编号记录下来形成一个序列（第一次 A 操作不计入序列），那么显然这个序列中必须恰好含有 $n$ 个 A，且最后一个必须是 A。那么显然一个合法的取卡片方案唯一对应一个操作序列，而一个长度为 $l$ 的操作序列恰好对应 $3^{n+m+k-l}$ 个合法的取卡片方案（证明？就每次下一轮执行操作的人是谁就在对应的操作者所取的卡片上写啥，那么显然对于长度为 $l$ 的操作序列而言，在原卡片堆中恰好有 $l$ 张卡片上的数是确定下来的，另外 $n+m+k-l$ 张可以 randomly 乱填，方案数就是 $3^{n+m+k-l}$）

然后考虑怎样统计方案，我们枚举操作序列中 BC 出现次数 $c$，那么操作序列长度即为 $c+n$，其中有一个 A 的位置已经确定了，那么填好另外 $n-1$ 个 A 的方案数即是 $\dbinom{n+c-1}{n-1}$，如果我们能求出填好 B、C 的方案数 $f_k$，就有 $ans=\sum\limits_{c=0}^{m+k}\dbinom{n+c-1}{n-1}f_c·3^{m+k-c}$。

接下来考虑怎样求 $f_c$，首先列出柿子，枚举 B 的个数然后组合数统计答案，即
$$
f_c=\sum\limits_{i}\dbinom{c}{i}[i\le m][c-i\le k]
$$
上式也可以写作
$$
f_c=\sum\limits_{c-k\le i\le m}\dbinom{c}{i}
$$
我们知道组合数下底数求和是无法直接求的，不过注意到组合数有个递推公式 $\dbinom{n}{k}=\dbinom{n-1}{k}+\dbinom{n-1}{k-1}$，因此考虑从数列递推的角度理解这道题，即：
$$
\begin{aligned}
f_c&=\sum\limits_{c-k\le i\le m}\dbinom{c}{i}\\
&=\sum\limits_{c-k\le i\le m}\dbinom{c-1}{i}+\dbinom{c-1}{i-1}\\
&=\sum\limits_{c-k\le i\le m}\dbinom{c-1}{i}+\sum\limits_{c-k\le i\le m}\dbinom{c-1}{i-1}\\
&=\sum\limits_{c-k\le i\le m}\dbinom{c-1}{i}+\sum\limits_{c-k-1\le i\le m-1}\dbinom{c-1}{i}\\
&=2\sum\limits_{c-1-k\le i\le m}\dbinom{c-1}{i}-\dbinom{c-1}{m}-\dbinom{c-1}{c-k-1}\\
&=2f_{c-1}-\dbinom{c-1}{m}-\dbinom{c-1}{c-k-1}
\end{aligned}
$$
递推求一下即可，时间复杂度线性。

```cpp
const int MAXN=9e5; 
const int MOD=1e9+7;
int n,m,k,fac[MAXN+5],ifac[MAXN+5],f[MAXN+5],pw3[MAXN+5];
void init_fac(int n){
	for(int i=(fac[0]=ifac[0]=ifac[1]=pw3[0]=1)+1;i<=n;i++) ifac[i]=1ll*ifac[MOD%i]*(MOD-MOD/i)%MOD;
	for(int i=1;i<=n;i++) fac[i]=1ll*fac[i-1]*i%MOD,ifac[i]=1ll*ifac[i-1]*ifac[i]%MOD;
	for(int i=1;i<=n;i++) pw3[i]=3ll*pw3[i-1]%MOD;
}
int binom(int x,int y){
	if(x<0||y<0||x<y) return 0;
	return 1ll*fac[x]*ifac[y]%MOD*ifac[x-y]%MOD;
}
int main(){
	scanf("%d%d%d",&n,&m,&k);init_fac(n+m+k);
	f[0]=1;for(int i=1;i<=m+k;i++)
		f[i]=(2ll*f[i-1]-binom(i-1,m)-binom(i-1,i-k-1)+MOD*2ll)%MOD;
	int ans=0;for(int i=0;i<=m+k;i++) ans=(ans+1ll*pw3[m+k-i]*binom(n-1+i,i)%MOD*f[i])%MOD;
	printf("%d\n",ans);
	return 0;
}
```



---

## 作者：Anonymely (赞：0)

模拟赛题。

首先考虑答案是什么。

设三个人手里的分别为 $n_1,n_2,n_3$。

$n_1$ 是一定要取完的，$n_2,n_3$ 是一定取不完的，最暴力的思路就是枚举 $n_2$,$n_3$ 各取了几个，得到答案是 $\sum_{i=0}^{n_2-1}\sum_{j=0}^{n_3-1} 3^{n_2+n_3-i-j} \binom{i+j+n_1-1}{i,j,n_1-1}$，带 $3$ 的那一项是后面可以随便选，组合数是插板。

然后发现这个式子跟 $i+j$ 有很大关系，转过头去枚举 $i+j$，变成 $\sum_{i=0}^{n_2+n_3-2} 3^{n_2+n_3-i}\binom{i+n_1-1}{n_1-1}\sum_{j \in [0,n_2], i-j \in [0,n_3]}\binom{i}{j}$

难点在于最后一个式子，是一行组合数部分求和。

考场上直接把组合数拆开然后暴力 MTT，跑起来很快。

当然有别的方法，考虑从 $i-1$ 递推出 $i$，发现仅仅只需要两项修改。

[submission](https://www.luogu.com.cn/record/181031836 "submission")

---

## 作者：daniEl_lElE (赞：0)

应该是我第一道黑题题解吧。

主要看题解区没有 $\texttt{MTT}$ 解法，来补充一个。

## 解法

考虑在结束的时候，也就是 $A$ 胜利时，$B$ 和 $C$ 分别轮到了 $i,j$ 次的方案数。

首先，第一轮是 $A$ 已经固定了，我们考虑后面 $n-1+i+j$ 轮是 $A,B,C$ 中一个人，通过简单的组合数学即可得知方案数为 $\frac{(n-1+i+j)!}{(n-1)!i!j!}$。

考虑 $B,C$ 后面的牌随便选，故总方案数为 $\sum_{i=0}^m\sum_{j=0}^k\frac{(n-1+i+j)!}{(n-1)!i!j!}\times3^{m-i}\times3^{k-j}$。

考虑如何优化，令 $t=i+j$。

原式 $=\sum_{i=0}^m\sum_{j=0}^k\frac{(n-1+t)!}{(n-1)!i!j!}\times3^{m+k-t}$

$=\sum_{t=0}^{m+k}(\frac{(n-1+t)!}{(n-1)!}\times3^{m+k-t}\times\sum_{i=\max(0,t-k)}^{m}\frac{1}{i!(t-i)!})$

考虑如何求最右边的式子，构造函数 $f(x)=\sum_{i=0}^m\frac{1}{i}$，$g(x)=\sum_{i=0}^{k}\frac{1}{i}$，不难发现其实就是 $f(x)$ 与 $g(x)$ 卷积 $x^t$ 系数。

发现~~可爱~~毒瘤的出题人的模数是 $10^9+7$，于是需要使用 $\texttt{MTT}$ 才可以，时间限制比较宽裕。

那么我们就可以在 $\Theta(n\log n)$ 复杂度解决本题。

## 代码

给出主函数片段代码，也就是主题思路啦。注释：$F(i)=A(i)\times B(i)$。

```cpp
signed main(){
	init();
	int N,M,K;
	cin>>N>>M>>K;
	for(int i=0;i<=M;i++) A[i]=Int(inv[i]);
	for(int i=0;i<=K;i++) B[i]=Int(inv[i]);
	n=M+1;
	m=K+1;
	MTT();
	int ans=0;
	for(int t=0;t<=M+K;t++){
		ans=(ans+fac[N-1+t]*inv[N-1]%mod*f[t]%mod*qp(3,M+K-t)%mod)%mod;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：henry_y (赞：0)

## 总结：组合数

这$F$题好难啊...只会部分分做法，下面两个方法都是部分分做法。满分做法我去看看...会的话就补一下

## 部分分做法

### 方法1：

首先$A$能赢的条件很明显，假设在所有的牌里面取出$A$张$A$牌，$B$张$B$牌，$C$张$C$牌，那么$A$能赢当且仅当$A=n,B<m,C<k$

所以假设我们在拿出了$n$张$A$牌的情况下，中间穿插着拿了$B$张$B$牌，$C$张$C$牌，则有

$$\sum_{i=0}^{i<=m+k}C(n-1,i+n-1)*3^{m+k-i}*\sum_{j=0}^{j<=m,j<=k}C(i,j)$$

首先在$i+n-1$张牌中取$n-1$张$A$牌的方案为$C(n-1,n+i-1)$

注意：最后一张牌一定需要是$A$，所以就只能有$n-1$

而且剩下的牌数的排列为$3^{m+k-i}$，要乘上去

以及在$i+n-1$中$B$和$C$的排列为$C(i,j)$，也要乘起来

所以就得到了上面的公式

但是，上面的做法我打挂了...这个式子是对的，我算后面那个$\sum_{j=0}^{j<=m,j<=k}C(i,j)$那里我没有枚举好...查不出来啊...

我在理解了满分做法之后终于发现我挂在哪里了...

在枚举后面的东西的时候我没有分类讨论。但是改完后貌似还分少了一类...

$subtask_1$10个点我错了$2$个...然后$subtask_2$被我强行水过去$2$个点..

用$C$牌数量来分类：分为$j<k$，$j<m$，$j<i$（第三类我没分...不想去改了...）

对于第一种情况：$x=\sum_{j=0}^{j<k}C(i,j)$

对于第二种情况：$x=\sum_{j=0}^{j<m}C(i,k)$

~~对于第三种情况：请读者独立思考（知道有第三种情况是因为我去看了一下满分的做法...）~~


### 方法2：

换一种想法，在前$i$张卡片中拿出$n$张$A$,$j$张$B$，$C$张$C$

则可以推出一个公式

$$\sum_{i=0}^{i<=n+m+k}\frac{(i-1)!}{(n-1)!j!C!}3^{n+k+m-i}$$

如果看得懂那个方法一的话这个公式大概也是看得懂的吧...

就是$i-1$的全排列数除掉$n-1$的全排列数和$j$的全排列数和$C$的全排列数

这个是很基础的一个组合数的常识，这样子得到的就是我们要的当前情况的方案数，记住也要把当前剩下的那些的方案数也乘上去，即$3^{n+m+k-i}$

然后这里的除法是$mod$ $m$意义下的，所以要求一下逆元，代码中的$fac[i]$即为$i!$的值，$ifac[i]$即为$i!$的逆元

钻研了很久的题解，终于差不多搞懂满分做法了...

## 满分做法

方法一确实是对的。这个满分做法就是用来改进那里的

观察耗时，耗时基本都是花费在枚举后面那一段，所以考虑优化那一段...（这个做法很清奇...正常写组合数不应该是优化那个式子吗...）

$$\sum_{i=0}^{i<=m+k}C(n-1,i+n-1)*3^{m+k-i}*\sum_{j=0}^{j<=m,j<=k}C(i,j)$$

还是这个式子，我们来优化掉后面那个$\sum_{j=0}^{j<=m,j<=k}C(i,j)$（就是我写错了还查不出来的那个玩意...不！我写到这里的时候忽然发现我在枚举的时候没有分类讨论！）

我们把后面那个$\sum$拆掉，分三部分讨论

假设我们现在手上有$x$张$C$牌

当$x<k$时，随便取...（C的数量都比你要取的多了所以肯定不会超限）即$\sum_{i=0}^{x<k}C(x,i)$

当$x<m$时，$C$的数量在$i$以内，同时不能取超过$k$个，即$\sum_{i=0}^{i<m}C(x,i)$

当$m<=x<m+k$时，$B,C$数量均不超过$i$，同时$B$不能取超过$m$个，$C$不能取超过$k$个，即$\sum_{i-m+1}^{i<k}C(x,i)$

然后怎么优化呢

如果你熟知杨辉三角这个东西的话，大概就会知道怎么优化了

假设我们已经知道了$i-1$时$x$的值，那么其实可以推出下面的几个式子：

情况$1$：$x=x*2$

情况$2$：$x=x*2-C(i,k)$

情况$3$：$x-x*2-C(i,k)-C(i,m)$

这个挺容易推的吧...如果部分分做法的第一种有推出来那么这个优化也就顺理成章了的样子（但是我推出来了一半...）

数学题真的虐哭我...这题我研究了$3$天...

不过确实是一道组合数的好题...做完后觉得对组合数这玩意的理解更深了一些...

[代码请戳我的博客QAQ](https://www.cnblogs.com/henry-1202/p/ARC061F.html)

---

