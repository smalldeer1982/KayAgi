# Manga Market

## 题目描述

[problemUrl]: https://atcoder.jp/contests/hitachi2020/tasks/hitachi2020_d

$ N $ 個の店があり、それぞれ店 $ 1 $、 店 $ 2 $ 、 $ \cdots $ 、店 $ N $ という名前が付けられています。高橋君は時刻 $ 0 $ に自宅にいて、これからいくつかの店を訪れる予定です。

高橋君が自宅から各店へ移動する際及び任意の $ 2 $ つの店の間を移動する際に要する時間は $ 1 $ 単位時間です。

高橋君が時刻 $ t $ に店 $ i $ に着いたとき、その店の列に並び、 $ a_i\ \times\ t\ +\ b_i $ 単位時間待つことにより、その店で買い物をすることが出来ます。(待ち時間以外の時間はかからないとします。)

全ての店の閉店時刻は $ T\ +\ 0.5 $ です。ある店で列に並んでいる途中に閉店時刻を迎えた場合、その店で買い物をすることは出来ません。

高橋君は同じ店で $ 2 $ 回以上買い物をしません。

高橋君が閉店時刻までに買い物を出来る店の数の最大値を答えてください。

## 说明/提示

### 制約

- 入力は全て整数
- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 0\ \leq\ a_i\ \leq\ 10^9 $
- $ 0\ \leq\ b_i\ \leq\ 10^9 $
- $ 0\ \leq\ T\ \leq\ 10^9 $

### Sample Explanation 1

店の回り方の例を $ 1 $ つ示します。 - 時刻 $ 0 $ から時刻 $ 1 $ : 自宅から店 $ 1 $ へ $ 1 $ 単位時間掛けて移動します。 - 時刻 $ 1 $ から時刻 $ 3 $ : 店 $ 1 $ で $ 2 $ 単位時間待ち、買い物をします。 - 時刻 $ 3 $ から時刻 $ 4 $ : 店 $ 1 $ から店 $ 3 $ へ $ 1 $ 単位時間掛けて移動します。 - 時刻 $ 4 $ から時刻 $ 7 $ : 店 $ 3 $ で $ 3 $ 単位時間待ち、買い物をします。 以上の回り方では、時刻 $ 7.5 $ までに $ 2 $ 箇所の店で買い物を行うことが出来ます。

## 样例 #1

### 输入

```
3 7
2 0
3 2
0 3```

### 输出

```
2```

## 样例 #2

### 输入

```
1 3
0 3```

### 输出

```
0```

## 样例 #3

### 输入

```
5 21600
2 14
3 22
1 3
1 10
1 9```

### 输出

```
5```

## 样例 #4

### 输入

```
7 57
0 25
3 10
2 4
5 15
3 22
2 14
1 15```

### 输出

```
3```

# 题解

## 作者：jdsb (赞：6)

## 题意
给定$n$个商店和总时间$T$，每个商店$i$有两个系数$a_i$，$b_i$，当你在时间$t$时处于商店$i$，就可以花$a_i * t+b_i$的时间在这个商店等待，然后进行购物，购物不用花费时间，你原本在家中，从家到商店或在任意两个商店中往来的时间是$1$，求在给定的时间内最多能在几个商店中购物。

## 分析
1. 我们首先要对原给定商店进行排序，设我们当前时间为$t$，我们现在有两个商店$i$和$j$可以去，如果先去商店$i$再去商店$j$的时间更短，则需满足这个式子: $(t+1)*(a_i+1)+b_i+((t+1)*(a_i+1)+b_i+1)*a_j+b_j+1<(t+1)*(a_j+1)+b_j+((t+1)*(a_j+1)+b_j+1)*a_i+b_i+1$，对上式进行化简可得$a_i*(b_j+1)>a_j*(b_i+1)$，所以我们就可根据这个来对原序列进行排序，保证先选的性价比更优。

2. 我们先来考虑一个$O(n^2)$的$dp$，$f[i][j]$表示在前$i$个商店中在$j$个商店中购物的最小时间，对于这个$dp$可用$01$背包的思想来做，$f[i][j]=min\{(f[i-1][j-1]+1)*(a[i]+1)+b[i]\}(j<=i)$这是选的情况，如果不选则$f[i][j]=f[i-1][j]$，然后$f[n][i]<=T$的最大$i$即是答案，对于第一维可用直接压掉，让空间达到$O(n)$。

3. 对于上面的$dp$，我们其实可以进行优化，我们可以发现，对于$a_i≠0$的情况，因为$a_i$为正整数，所以我们如果在商店$i$等待的话，等待结束后的时间为$a_i*t+b_i$，而$a_i*t+b_i>=2*t$，所以也就是说我们如果要在一个商店购物，时间至少要翻两倍，所以我们最多能在$log(T)$的商店中购物。所以我们的$dp$转移的时间就从$O(n)$降为$O(log(T))$，时间大大降低。而对于$a_i=0$的情况，我们发现不管当前的时间为多少，在这个商店购物的时间都是固定的，所以对于这个商店，它在后面的时间购物肯定比在前面的时间购物更优。

4. 所以根据上面的分析，我们就可以知道这题的解法了，我们将$a_i≠0$和$a_i=0$的商店存放在两个数组中，先对于$a_i≠0$的商店进行我们最开始的$dp$，然后我们将$a_i=0$的商店按照$b_i$从小到大排序，并求出前缀和$s_i$，然后我们在枚举从$a_i≠0$中的商店选择$k$个，然后我们在二分查找出$s_x≤T-f[k]$的最多商店数$x$，答案即为$max\{x+k\}$。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N=2e5+5;
ll n,T,b[N],ans,f[N],tot1,tot2;
struct node
{
	ll x,y;
}a[N];
bool mycmp(node x,node y)
{
	return x.x*(y.y+1)>y.x*(x.y+1);
}
int main()
{
	scanf("%lld%lld",&n,&T);
	for(ll i=1;i<=n;i++)
	{
		ll x,y;
		scanf("%lld%lld",&x,&y);
		if(x==0) b[++tot2]=y+1;
		else a[++tot1]={x,y};
	}
	sort(a+1,a+tot1+1,mycmp);
	sort(b+1,b+tot2+1);
	for(ll i=1;i<=35;i++) f[i]=T+1;
	for(ll i=1;i<=tot1;i++)
		for(ll j=35;j>=1;j--)
			f[j]=min(f[j],(f[j-1]+1)*(a[i].x+1)+a[i].y);
	for(ll i=1;i<=tot2;i++) b[i]+=b[i-1];
	for(ll i=0;i<=35;i++)
	{
		if(f[i]>T) continue;
		ll x=0;
		if(tot2) x=upper_bound(b+1,b+tot2+1,T-f[i])-(b+1);
		ans=max(ans,i+x);
	}
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：Soulist (赞：4)

一点题外话：

这道题本来我差不多 1h 左右的时候应该过了的

然而我失了智搞错了时间的计算方式，可以理解为我认为时间的计算是：

1. 你在 $t$ 时刻决定要去 $i$，此时花费为 $a\times t+b+1$，那个$+1$ 是什么呢？我以为走过去的时间不会乘$a$

然后就愉快的调了40min后来看样例解释才发现不对(/泪奔)

问题是他还过了 $50$ 个点啊 TAT，搞得我很迷，期间我交了大概5~6发

----

$\rm Sol:$

要注意到两个性质：

第一个性质：

假设 $a_i\ne 0$，那么每次操作至少可以使得时间翻倍。

那么这意味着 $a_i\ne 0$ 的元素至多选 $\log T$ 个。

另一个性质：

假设我们选了一些商店，他们有 $a_i=0$ 也有 $a_i\ne 0$，那么我们肯定会把 $a_i=0$ 的留到最后。

所以我们可以把 $a_i=0$ 和 $a_i\ne 0$ 的分开考虑。

假设 $a_i\ne 0$，那么我们考虑，假设你选择了一个集合 $S\{x_1,x_2...x_m\}$

如何排布这个集合可以保证答案更优？

假设到达 $i$ 之前的时间为 $t$，那么有经过 $i$ 和 $i+1$ 之后的时间为：

$$(a_{i+1}+1)\times (b_i+(t+1)\times (a_i+1)+1)+b_{i+1}$$

即：

$$(a_{i+1}+1)(a_i+1)(t+1)+ a_{i+1}b_i+b_i+a_{i+1}+b_{i+1}+1$$

另一边，如果我们交换了 $i$ 和 $i+1$，那么时间花费为：

$$(a_{i}+1)\times (b_{i+1}+(t+1)\times (a_{i+1}+1)+1)+b_{i}$$

即：

$$(a_{i}+1)(a_{i+1}+1)(t+1)+ a_{i}b_{i+1}+b_{i+1}+a_{i}+b_{i}+1$$

令 $\Delta=$ 交换后 $-$ 交换前，则有：

$$\Delta=a_{i}b_{i+1}+a_i-(b_ia_{i+1}+a_{i+1})$$

若 $\Delta<0$，那么交换后更优：

所以交换后更优的判定为：

$$a_ib_{i+1}+a_i<b_ia_{i+1}+a_{i+1}$$

$$a_i(b_{i+1}+1)<a_{i+1}(b_i+1)$$

所以有，如果：

$$\dfrac{b_{i+1}+1}{a_{i+1}}<\dfrac{b_i+1}{a_i}$$

那么 $i+1$ 排在 $i$ 前面更优秀。

这意味着，对于 $a_i\ne 0$ 的元素，假设我们已经选好了是那些元素，那么最后的访问顺序必然是按照 $\frac{b_{i}+1}{a_i}$ 升序访问。

所以我们可以先按照此值进行排序，然后依次考虑每个数选或不选。

注意到之前的第一个性质，所以我们可以有一个很 naive 的dp状态出来了：

令 $f_{i,j}$ 表示考虑前 $[1,i]$ 的元素，选了 $j$ 个的最小时间。

当然，$j$ 只需要枚举到 $\log T$ 即可。

转移也很显然，就不提了

当然，这个 dp 和 01 背包几乎一致，所以可以轻易的滚动数组，然后我们考虑把 $a_i=0$ 的元素加入。

我们对 $a_i=0$ 的元素，按照 $b_i$ 进行排序，然后预处理一个前缀和，对于每个 $j$ ，用 $T-f_{cnt,j}$ 在内部二分最多能选走多少个即可。复杂度 $O(n\log T)$

当然，为了在一定程度上避免精度误差，排序可以类似于叉积那种搞法直接换成乘积排序。

$Code:$

```cpp
#include<bits/stdc++.h>
using namespace std ;
#define rep( i, s, t ) for( register int i = s; i <= t; ++ i )
#define re register
#define int long long
int gi() {
	char cc = getchar() ; int cn = 0, flus = 1 ;
	while( cc < '0' || cc > '9' ) {  if( cc == '-' ) flus = - flus ; cc = getchar() ; }
	while( cc >= '0' && cc <= '9' )  cn = cn * 10 + cc - '0', cc = getchar() ;
	return cn * flus ;
}
const int N = 2e5 + 5 ; 
const int inf = 1e9 + 7 ;
int n, m, cnt, num, dp[40], Pre[N] ; 
struct Node {
	int a, b ; 
} t[N], p[N], r[N] ;
bool cmp( Node x, Node y ) {
	return x.b < y.b ; 
} 
bool cmp2( Node x, Node y ) {
	return ( 1ll * x.b * y.a + y.a ) < ( 1ll * y.b * x.a + x.a ) ;
}
int check( int x ) {
	int l = 0, r = num, ans = 0 ; 
	while( l <= r ) {
		int mid = ( l + r ) >> 1 ; 
		if( Pre[mid] <= x ) ans = mid, l = mid + 1 ;
		else r = mid - 1 ;
	} return ans ; 
}
signed main()
{
	n = gi(), m = gi() ;
	rep( i, 1, n ) {
		t[i].a = gi(), t[i].b = gi() ; 
		if( t[i].a != 0 ) p[++ cnt] = t[i] ; 
		if( t[i].a == 0 ) r[++ num] = t[i] ; 
	}
	rep( j, 0, 32 ) dp[j] = m + 1 ; 
	sort( p + 1, p + cnt + 1, cmp2 ) ;
	sort( r + 1, r + num + 1, cmp ) ;
	dp[0] = 0 ; 
	for( re int i = 1; i <= cnt; ++ i ) {
		for( re int j = 32; j > 0; -- j ) {
			if( dp[j - 1] > m ) continue ; 	
			if( p[i].a * dp[j - 1] > m ) continue ; 
			dp[j] = min( ( dp[j - 1] + 1 ) * ( p[i].a + 1 ) + p[i].b, dp[j] ) ;
		}
	}
	for( re int i = 1; i <= num; ++ i ) Pre[i] = Pre[i - 1] + r[i].b + 1 ; 
	int Ans = 0 ;
	for( re int i = 0; i <= 32; ++ i ) {
		int ans = i, T = dp[i] ;
		if( T > m ) continue ; 
		ans = ans + check( m - dp[i] ) ;
		Ans = max( Ans, ans ) ;
	}
	printf("%lld\n", Ans ) ;
	return 0 ;
}
```



---

## 作者：tzc_wk (赞：2)

> 题意：

> 有 $n$ 个商店，第 $i$ 个商店有两个参数 $a_i,b_i$。如果你在时刻 $t$ 进入第 $i$ 个商店，那么你在这个商店买东西需要 $a_i \times t+b_i$ 的时间。从一个商店走到另一个商店需要 $1$ 的时间。

> 你现在有 $T$ 的时间，问最多可以在多少家商店里买东西。

> $1 \leq n \leq 10^5$，$0 \leq a_i,b_i \leq 10^9$

看起来非常不可做的亚子啊。我们不妨先来探索一些性质。

我们发现，如果 $a_i \neq 0$，那么在时刻 $t$ 进去至少要到时刻 $2t$ 才能出来。也就是说，最多只能访问 $log_2T$ 个 $a_i \neq 0$ 的商店。

因此我们就可以分出 $a_i=0$ 和 $a_i \neq 0$ 的两类处理。

很明显的一点是，我们一定要先买 $a_i \neq 0$ 的再买 $a_i=0$ 的。因此我们可以设 $dp[i][j]$ 为在前 $i$ 个 $a_i \neq 0$ 的商店中访问了 $j$ 个商店的最小访问时间，根据我们之前的推理，$j$ 不会超过 $30$。最后我们枚举访问了多少个 $a_i \neq 0$ 的商店，然后看看剩余的时间里最多可以访问多少个 $a_i=0$ 的商店就可以了。

因此我们只用求出 $dp[i][j]$ 就可以了。

但是这样有一个问题出现了。例如有两个 $a_i \neq 0$ 的商店 $i,j$，你先买 $i$，后买 $j$，与你先买 $j$，后买 $i$ 需要的时间是不一样的。

不过我们可以用类似 P1417 的套路：推式子。

假设之前的时间为 $t$，那么先买 $i$，后买 $j$ 的代价是：

$$a_i \times t+b_i+1+a_j \times (t+a_i \times t+b_i+1)+b_j$$

化简：

$$a_i \times t+b_i+1+a_j \times t+a_j \times a_i \times t+a_j \times b_i+a_j+b_j$$

同理，那么先买 $j$，后买 $i$ 的代价是：

$$a_j \times t+b_j+1+a_i \times t+a_i \times a_j \times t+a_i \times b_j+a_i+b_i$$

发现有些项可以怼掉，这样一来，先买 $i$，后买 $j$ 的代价，比先买 $j$，后买 $i$ 的代价小，当且仅当。

$$a_j \times b_i+a_j < a_i \times b_j+a_i$$

我们把这些商店按照这个顺序排序就可以了。

最后是 $dp$ 转移，和一般的 $01$ 背包 $dp$ 转移没啥区别，具体见代码。

然后最后统计答案就好了。

```cpp
//Coded by tzc_wk
/*
数据不清空，爆零两行泪。
多测不读完，爆零两行泪。
边界不特判，爆零两行泪。
贪心不证明，爆零两行泪。
D P 顺序错，爆零两行泪。
大小少等号，爆零两行泪。
变量不统一，爆零两行泪。
越界不判断，爆零两行泪。
调试不注释，爆零两行泪。
溢出不 l l，爆零两行泪。
*/
#include <bits/stdc++.h>
using namespace std;
#define fi			first
#define se			second
#define fz(i,a,b)	for(int i=a;i<=b;i++)
#define fd(i,a,b)	for(int i=a;i>=b;i--)
#define foreach(it,v) for(__typeof(v.begin()) it=v.begin();it!=v.end();it++)
#define all(a)		a.begin(),a.end()
#define giveup(...) return printf(__VA_ARGS__),0;
#define fill0(a)	memset(a,0,sizeof(a))
#define fill1(a)	memset(a,-1,sizeof(a))
#define fillbig(a)	memset(a,0x3f,sizeof(a))
#define fillsmall(a) memset(a,0xcf,sizeof(a))
#define mask(a)		(1ll<<(a))
#define maskx(a,x)	((a)<<(x))
#define _bit(a,x)	(((a)>>(x))&1)
#define _sz(a)		((int)(a).size())
#define filei(a)	freopen(a,"r",stdin);
#define fileo(a)	freopen(a,"w",stdout);
#define fileio(a) 	freopen(a".in","r",stdin);freopen(a".out","w",stdout)
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#define put(x)		putchar(x)
#define eoln        put('\n')
#define space		put(' ')
#define y1			y_chenxiaoyan_1
#define y0			y_chenxiaoyan_0
#define int long long
typedef pair<int,int> pii;
inline int read(){
	int x=0,neg=1;char c=getchar();
	while(!isdigit(c)){
		if(c=='-')	neg=-1;
		c=getchar();
	}
	while(isdigit(c))	x=x*10+c-'0',c=getchar();
	return x*neg;
}
inline void print(int x){
	if(x<0){
		putchar('-');
		print(abs(x));
		return;
	}
	if(x<=9)	putchar(x+'0');
	else{
		print(x/10);
		putchar(x%10+'0');
	}
}
inline int qpow(int x,int e,int _MOD){
	int ans=1;
	while(e){
		if(e&1)	ans=ans*x%_MOD;
		x=x*x%_MOD;
		e>>=1;
	}
	return ans;
}
pii x1[200005];
int x2[200005];
int cnt1=0,cnt2=0;
int dp[32];
int n=read(),t=read();
inline bool cmp(pii i,pii j){
	return i.se*j.fi<j.se*i.fi;
}
signed main(){
	dp[0]=0;
	fz(i,1,31)	dp[i]=t+1;
	fz(i,1,n){
		int a=read(),b=read();
		b++;b+=a;
		if(a==0)	x2[++cnt2]=b;
		else		x1[++cnt1]={a,b};
	}
	sort(x1+1,x1+cnt1+1,cmp);
	sort(x2+1,x2+cnt2+1);
	fz(i,1,cnt1){
		fd(j,30,0){
			if(dp[j]<=t)
				dp[j+1]=min(dp[j+1],dp[j]+x1[i].fi*dp[j]+x1[i].se);
		}
	}
	int ans=0;
	fz(i,0,30){
//		cout<<dp[i]<<endl;
		if(dp[i]<=t){
			int lft=t-dp[i],num=i;
			fz(j,1,cnt2){
				if(lft<x2[j]){
					break;
				}
				lft-=x2[j];
				num++;
			}
			ans=max(ans,num);
		}
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：ylxmf2005 (赞：1)


### Description
有 $n$ 个商店，你在家里，初始时间为零。你从家走到一个商店或从一个商店走到另一个商店都需要一个单位时间。如果你在 $t$ 个单位时间到达第 $i$ 家商店，那么你排队 $a_i \times t + b_i$ 个单位时间买东西，一家商店只能买一次。所有的商店会在 $T + 0.5$ 个单位时间关门，这时如果你在排队那么不算你买了东西。求你最多买多少次。

$1 \leq n \leq 2 \times 10^5, 0 \leq a_i, b_i, T \leq 10^9$。

### Solution
可能直觉上排一个序完事了，但~~题目难度~~告诉我们这是错的，因为交换两个商店的顺序对其它的商店也会影响。

贪心不行，考虑可以 dp。令 $f_{i,j}$ 走到的第 $i$ 个商店为 $j$ 的最小时间。不能走到一个商店两次，看上去没法转移。所以还是要排序。考虑在 $t$ 个时间要出发，接下来访问两个商店 $i$ 和 $j$。如果访问第一个商店比第二个商店更优，那么

$$
a_j(b_i+1) < a_i(b_j+1) 
$$


那么可以转移了，而且状态中的 $j$ 没必要可以不写。那么这是一个 $O(n^2)$ 的超时 dp。可以发现 $a_i \times t + b_i$ 即使 $a_i = 1$ 也是成倍增长的，这意味着如果 $a_i > 0$  那么最多经过 $log(T)$ 个商店，所以 $30$ 个商店完全够了。

所以将 $a_i = 0$ 的挑出来，如果答案中经过它们，那么在最后走一定最优。可以将它们按 $b_i$ 从小到大排序。枚举去多少个 $a_i > 0$ 的商店，二分找到可以去的 $a_i = 0$ 的商店，两部分加起来更新答案即可。

时间复杂度 $O(n \log n + n \log T)$。不要用 memset 因为你的正无穷乘上一个数可能爆 long long。

### Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define int long long
#define F first
#define S second
typedef pair<int, int> P;
const int N = 30 + 5, INF = 0x3f3f3f3f;
inline int read() {
	int x = 0, f = 0; char ch = 0;
	while (!isdigit(ch)) f |= ch == '-', ch = getchar();
	while (isdigit(ch)) x = (x << 3) + (x << 1) + (ch ^ 48), ch = getchar();
	return f ? -x : x;
}
bool cmp(P a, P b) {
	return b.F * (a.S + 1) < a.F *(b.S + 1) ;
}
vector <P> a; vector <int> b;
int f[N];
signed main() {
	int n = read(), T = read();
	for (int i = 1; i <= n; i++) {
		int x = read(), y = read();
		if (x) a.pb(make_pair(x, y));
		else b.pb(y + 1);
	}
	sort(a.begin(), a.end(), cmp);
	sort(b.begin(), b.end());
	for (int i = 1; i < b.size(); i++) b[i] += b[i - 1];
	for (int i = 1; i <= 30; i++) f[i] = T + 1;
	for (int i = 0; i < a.size(); i++)
		for (int j = 30; j; j--)
			f[j] = min(f[j], (f[j - 1] + 1) * (a[i].F + 1) + a[i].S);
	int ans = 0;
	for (int i = 0; i <= 30; i++) 
		if (f[i] <= T) ans = max(ans, i + (b.empty() ? 0 : upper_bound(b.begin(), b.end(), T - f[i]) - b.begin()));
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：沉石鱼惊旋 (赞：0)

# 题目翻译

有 $n$ 个节点，每个节点有 $2$ 个参数 $a_i,b_i$。

你时刻 $0$ 在节点 $0$，在节点间往返需要消耗 $1$ 的单位时间。

你在时刻 $t$ 到达第 $i$ 个节点时可以等待 $a_i\times t+b_i$ 后获得 $1$ 的收益。

$T+0.5$ 时刻所有节点都会失效，**包括你所在的节点。**

求你能得到的最大收益，**每个节点不能多次等待，不要求在 $T+0.5$ 时刻之前返回 $0$ 节点。**

$1\leq n\leq 2\times 10^5,0\leq a_i,b_i,T\leq 10^9$。

# 题目思路

考虑 exchange argument。

设目前拥有的访问顺序是最优的，即全部经过且等待之后总时刻最小。

对于相邻的 $i+1=j$，你是时刻 $t$ 到达的，若先等待 $i$ 优于先等待 $j$，需要满足 $1+a_i(t+1)+b_i+1+a_j(t+1+a_i(t+1)+b_i+1)+b_j\lt 1+a_j(t+1)+b_j+1+a_i(t+1+a_j(t+1)+b_j+1)+b_i$。

化简得 $\frac{a_j}{b_j+1}\lt \frac{a_i}{b_i+1}$。

也就是说我们按 $\frac{a_i}{b_i+1}$ 的降序排序得到的访问顺序一定是最优的。

这里的 $a_i=0$ 有点特殊，我们单独先拆出来。

对于 $a_i=0$ 的，设我们还有 $t$ 时间剩余，也就是找到尽可能多的 $b_1,b_2,\dots b_k$ ，满足 $(\sum\limits_{i=1}^{k}b_i)-k\leq t$。

这个显然我们是可以排序之后前缀和处理的。

那么对于 $a_i\neq 0$，既然我们已经钦定了访问顺序的最优策略，就是决定当前点选或不选。

那么 $f_{i,j}$ 表示前 $i$ 个节点你选择了 $j$ 个**并且都等待了**的最少时间。

这个直接类似背包转移即可。第一维可以压掉。

但是这样的转移有个问题，这是 $\mathcal O(n^2)$ 的无法接受。

发现 $a_i\neq 0$ 的情况，你用的时间是指数级增长的，也就是你最多选择的节点数不超过 $\log_2 T$ 个。

那么第二维大小就是 $\mathcal O(\log_2 T)$ 的了，转移复杂度 $\mathcal O(n\log_2 T)$ 可以接受。

然后直接枚举最后选择多少 $a_i\neq 0$ 的，双指针或二分出你能选多少 $a_i=0$ 的即可。

**实现中，如果你需要 dp 数组进行初始化，尽量不要 `memset`，参数不好会炸 `long long`。**

# 丑陋代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
template <typename T>
void chkmx(T &x, T y) { x = max(x, y); }
const int inf = 2e9;
int n, m;
ll T;
vector<int> cst;
struct store
{
    ll a, b;
};
vector<store> v;
ll f[200020][35];
ll pre[200020];
int ans;
int main()
{
    cin >> n >> T;
    for (int i = 1; i <= n; i++)
    {
        int a, b;
        cin >> a >> b;
        if (!a)
            cst.push_back(b);
        else
            v.push_back({a, b});
    }
    sort(v.begin(), v.end(), [&](store x, store y)
         { return 1.0 * x.a / (x.b + 1) > 1.0 * y.a / (y.b + 1); });
    sort(cst.begin(), cst.end());
    for (int i = 1; i <= int(cst.size()); i++)
        pre[i] = pre[i - 1] + cst[i - 1];
    // for (store i : v)
    //     cout << i.a << " " << i.b << endl;
    m = v.size();
    for (int i = 0; i <= m; i++)
        for (int j = 0; j <= 30; j++)
            f[i][j] = inf;
    f[0][0] = 0;
    for (int i = 1; i <= m; i++)
    {
        f[i][0] = 0;
        for (int j = 1; j <= min(30, i); j++)
        {
            f[i][j] = min(f[i - 1][j], f[i - 1][j - 1] + 1 + v[i - 1].a * (f[i - 1][j - 1] + 1) + v[i - 1].b);
            // cout << f[i][j] << " ";
        }
        // cout << endl;
    }
    int pos = cst.size();
    for (int i = 0; i <= min(30, m); i++)
    {
        ll t = T - f[m][i];
        if (t < 0)
            continue;
        while (pre[pos] + pos > t)
            pos--;
        chkmx(ans, pos + i);
        // cout << f[m][i] << " " << i << " " << pre[pos] << " " << pos << endl;
    }
    cout << ans << endl;
    return 0;
}
```



---

## 作者：FelFa_1414666 (赞：0)

[atcoder 传送门](https://atcoder.jp/contests/hitachi2020/tasks/hitachi2020_d?lang=en) & [洛谷传送门](https://www.luogu.com.cn/problem/AT5760)

---

## Step 1

假设我们确定了要去哪些商店，要找完成这一方案的最小时间，那么就要确定一个**最优的顺序**。通常这种问题，要用一个叫 `Exchange Argument` 的思想确定一个贪心的标准，通过这个标准来对商店进行排序。

首先我们考虑两个商店 $i$ 和 $j$，它们在要去的顺序中是相邻的，那么考虑交换它们会对答案造成什么影响。假设在此之前已经花费了 $t$ 的时间。

- 先去 $i$ 再去 $j$ 花费时间：$a_it+b_i+1+a_j(t+a_it+b_i+1)+b_j+1=(a_i+a_j)t+a_ia_jt+a_j(b_i+1)+b_i+b_j+2$
- 先去 $j$ 再去 $i$ 花费时间：$a_jt+b_j+1+a_i(t+a_jt+b_j+1)+b_i+1=(a_i+a_j)t+a_ia_jt+a_i(b_j+1)+b_i+b_j+2$

所以：若先去 $i$ 更优，则满足：

$$(a_i+a_j)t+a_ia_jt+a_j(b_i+1)+b_i+b_j+2<(a_i+a_j)t+a_ia_jt+a_i(b_j+1)+b_i+b_j+2$$

化简得：

$$\dfrac{b_i+1}{a_i}<\dfrac{b_j+1}{a_j}$$

这个比较满足全序关系，所以将所有商店按 $\dfrac{b+1}{a}$ 升序排序，如果 $a=0$ 定义其权值为 $+\infty+b$。

## Step 2

排序过后，由于我们已经证明了这个序列的最优性，所以接下来要去的商店序列一定是这个序列的**一个子序列**。有 $n$ 个商店，总时间不超过 $T$ ，求最多去的商店个数。这就将问题转化成了 **01 背包问题**。

接下来我们考虑状态，用当前时间做状态显然不可行，就用**商店个数**作为状态：

- $dp_{i,j}$ 表示考虑前 $i$ 个商店，已经去了 $j$ 个商店的最小时间。

常规的 01 背包转移，考虑当前商店去或不去：

$$dp_{i,j}=\min(dp_{i-1,j},dp_{i-1,j-1}+a_i\times(dp_{i-1,j-1}+1)+b_i)$$

这样做的时间复杂度是 $O(n^2\times 1)=O(n^2)$ 的，我们要对状态进行优化。

手算几组数据会发现，对于 $a>0$ 的商店，每去一次，当前时间至少翻 $a$ 倍。这提示我们**实际上能去的最大商店数是很少的**。先忽略 $a=0$ 的所有商店，剩下商店即使全部 $a=1$，最终能去的最大商店数仍不超过 $\lg T$ 。所以 dp 状态数优化到了 $O(n\log T)$。最后对每个 $dp_{n,j}$，再对剩下的所有 $a=0$ 的商店跑一遍贪心即可。

---

## Code

```c++
#include <bits/stdc++.h>
#define int long long
#define pb push_back
#define pii pair<int,int>
#define mp make_pair
#define F first
#define S second
using namespace std;
const int INF=1000000000000000007;
int n,T,pos,ans;
struct store//定义商店类
{
	int x,y;
	bool operator<(store &B)//权值比较器
	{
		if (x==0&&B.x==0)
			return y<B.y;
		return (y+1)*B.x<(B.y+1)*x;
	}
}a[200005];
int dp[200005][35];//n*lgT的dp数组
signed main()
{
	ios::sync_with_stdio(false),cin.tie(nullptr);
	cin>>n>>T;
	for(int i=0;i<n;i++)
		cin>>a[i].x>>a[i].y;
	sort(a,a+n);//按权值升序排序
	while(pos<n&&a[pos].x>0)
		pos++;//找到第一个a=0的商店下标
	for(int i=0;i<=pos;i++)
		fill(dp[i],dp[i]+30,INF);
	dp[0][0]=0ll;
	for(int i=0;i<pos;i++)
		for(int j=0;j<30;j++)if (dp[i][j]<=T)//01背包dp
		{
			dp[i+1][j]=min(dp[i+1][j],dp[i][j]);
			dp[i+1][j+1]=min(dp[i+1][j+1],dp[i][j]+1+a[i].x*(dp[i][j]+1)+a[i].y);
		}
	for(int j=0;j<30;j++)if (dp[pos][j]<=T)
	{//对剩下所有a=0的商店,在剩余时间内跑一遍贪心
		int i=pos,t=dp[pos][j],cur=j;
		while(i<n&&t+1+a[i].y<=T)
		{
			t+=1+a[i].y;
			cur++;
			i++;
		}
		ans=max(ans,cur);//记录最大答案
	}
	cout<<ans<<endl;
	return 0;
}
```

- 时间复杂度：$O(n\log n+n\log T)$
- 空间复杂度：$O(n\log T)$

希望题解对你有帮助！

---

## 作者：leoair (赞：0)

### 题意：
有 $n$ 个店铺，每个店铺有两个属性 $a_i$ 和 $b_i$，表示在 $t$时间进入店铺时，需要等待 $a_it + b_i$ 的时间，才能购物。从家或者一个店铺到另一个店铺花费 $1$ 时间。一开始在家里，共有 $T$ 时间，问：最多能在多少个商店里购物。

### 分析：
考虑两个商铺 $i,j$，且到其中一个商铺中购完物就到另一个商铺中购物，则有 $2$ 种方案，即 $i->j$ 和 $j->i$，两种方案的时间花费分别为 $t+a_it+b_i+1+a_j(t+a_it+b_i+1)+b_j$ 和 $t+a_jt+b_j+1+a_i(t+a_jt+b_j+1)+b_i$。

若先逛 $i$ 的方案比先逛 $j$ 的方案更优，即 $t+a_it+b_i+1+a_j(t+a_it+b_i+1)+b_j<t+a_jt+b_j+1+a_i(t+a_jt+b_j+1)+b_i$(其中 $t$ 为逛之前商铺的花费)，化简后便得 $a_i(b_j+1)>a_j(b_i+1)$。

接下来，我们设 $dp_{i,j}$ 表示经过 $i$ 个店铺，逛了 $j$ 个店铺的最小花费，可以 $O(n^2)$ 求解。但是数据范围是 $1\le n\le 10^5$，显然过不去。因此，我们考虑优化。由于 $t'=a_it+b_i$，当 $a\ne0$ 时，$t'$ 显然不小于 $2t$。由此我们可以推出，最多可以逛 $\log_2T$个商铺。对于 $a=0$ 的情况，显然只需要按照 $b$ 的大小排序，在逛了 $j(1\le j\le n)$ 个商铺后选择尽量多的 $a$ 为 $0$ 的商铺。因此，我们可以将方程从二维降为一维，令 $dp_i$ 表示逛 $i$ 个 $ a\ne0$ 的店铺的最小花费。

初始化 $dp_0=0$，$dp_i=T+1(1\le i\le n)$，转移方程为 $dp_{j+1}=min\sum\limits_{i=0}^{size(g)-1}\sum\limits_{j=1}^{\log_2T}((a_i+1)(dp_j+1)+b_i)$，其中 $g$ 为记录店铺信息的向量。

### Code:
```cpp
/*
user:leoair
time:2022.3.20
*/
#include <bits/stdc++.h>
#define int long long
using namespace std;

vector < int > all;
vector < pair < int, int > > g;

int ans, dp[32];// dp[i] 表示当前选出 i 个店铺来的最小时间

inline int read(){
    int s = 0, w = 1;
    char ch = getchar();
    for (; ch < '0' || ch > '9'; w *= ch == '-' ? -1 : 1, ch = getchar());
    for (; ch >= '0' && ch <= '9'; s = s * 10 + ch - '0', ch = getchar());
    return s * w;
}

bool cmp(pair < int, int > u, pair < int, int > v){return u.first * v.second > v.first * u.second;}

signed main(){
    int n = read(), T = read();
    for (int i = 0, u, v; i < n; ++i){
        u = read(), v = read();
        if (!u) all.push_back(v + 1);
        else g.push_back(make_pair(u, v));
    }
    sort(g.begin(), g.end(), cmp);//按照式子排序
    for (int i = 0; i < 32; ++i) dp[i] = T + 1;//初始化，等价于赋值无穷大
    dp[0] = 0;
    for (int i = 0; i < g.size(); ++i){
        pair < int, int > p = g[i];
        for (int j = 30; ~j; --j){
            if (dp[j] > T) continue;
            dp[j + 1] = min(dp[j + 1], (p.first + 1) * (dp[j] + 1) + p.second);//dp[j]+1为从前一家店铺到第i家店铺的时间
        }
    }
    sort(all.begin(), all.end());
    for (int i = 0; i < 32; ++i){
        if (dp[i] > T) continue;
        int t = T - dp[i], pos = 0;//t为进了dp[i]个a>0的商铺之后还剩的时间
        while (pos < all.size() && t >= all[pos]) t -= all[pos], ++pos;//在有限的时间内尽量多选a=0的店铺
        ans = max(ans, pos + i);//答案为a≠0的商铺数i与a=0的商铺数pos之和的最大值
    }
    printf("%lld\n", ans);
    return 0;
}
```

---

## 作者：KokiNiwa (赞：0)

# D - Manga Market

哎，我不会精细实现。

## 题目叙述

有$n$个点，你在$0$号点，每次要走到$1\sim n$种的与当前所在点不同的点，要消耗$1$的时间。经过$i$号点会消耗的时间为$a_iT+b_i$（不能回$0$号点）。

## 题解

首先是一个偏套路的贪心。如果$i$号点在$j$号点前经过，那么一定满足某个式子。这个式子在[Editorial](https://img.atcoder.jp/hitachi2020/editorial.pdf)这里有。

其中$T$是原本经过的点的总时间。

那么有一个很显然的`dp`，设$f_{i,j}$为前$i$个点中选$j$个点走，转移即可。

但是发现这是$n^2$的。但是考虑$f_{i,j}$是指数级增长的，于是考虑如果$f_{i,j}>10^9$就停止继续（因为你最多能走$10^9$的时间）。然而会发现，如果每个点的$a_i$都是0，那么就不会指数级增长。于是考虑把$a_i=0$的都抽出来，对其他的进行$\texttt{dp}$。这样复杂度$n\log_2n$。剩下的$a_i$为0的就排个序，从前向后选即可。

## 代码

注意：

+ 精细实现！
+ 可以选`0`个。
+ 注意转移。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int maxStore = 2e5 + 5;
int nbStore, sj, totNeg, totZer;
ll sum[maxStore];
struct STORE {
	ll slope, add;
	STORE operator = (const STORE &d) {
		slope = d.slope;
		add = d.add;
		return (*this);
	}
} store[maxStore], zero[maxStore];
ll dp[maxStore][35];
bool cmp1(STORE fir, STORE sec) {
	return (1ll * sec.slope * (fir.add + 1) < 1ll * fir.slope * (sec.add + 1));
}
bool cmp2(STORE fir, STORE sec) {
	return fir.add < sec.add;
}
int main() {
	scanf("%d%d", &nbStore, &sj);
	for (int i = 1; i <= nbStore; ++i) {
		STORE tmp;
		scanf("%lld%lld", &tmp.slope, &tmp.add);
		if (tmp.slope != 0)
			store[++totNeg] = tmp;
		else zero[++totZer] = tmp;
	}
	sort(store + 1, store + totNeg + 1, cmp1);
	sort(zero + 1, zero + totZer + 1, cmp2);
	for (int i = 1; i <= totZer; ++i)
		sum[i] = sum[i - 1] + zero[i].add + 1;
	memset(dp, 0x3f, sizeof(dp));
	dp[0][0] = 0;
	for (int pre = 1; pre <= totNeg; ++pre) {
		dp[pre][0] = 0;
		//前几个取0个应该都是0 
		for (int chos = 1; chos <= 30; ++chos) {
			dp[pre][chos] = dp[pre - 1][chos];
			if (dp[pre - 1][chos - 1] > 1e9)
				continue ;
			ll tmp = (dp[pre - 1][chos - 1] + 1) * (store[pre].slope + 1) + store[pre].add; //这里把每条边+的1都带在前面，就是先+1再乘。
			if (tmp > 1e9) break ;
			else dp[pre][chos] = min(dp[pre][chos], tmp);
		}
	}
	int ans = 0;
	for (int chos = 0; chos <= 30; ++chos) {
		ll spare = sj - dp[totNeg][chos];
		if (spare < 0) break ;
		int pos = upper_bound(sum + 1, sum + totZer + 1, spare) - sum;
		ans = max(chos + pos - 1, ans);
	}
	printf("%d\n", ans);
	return 0;
}
```

## 知识点

+ 奇妙的剪枝？算是吧（指数级增长那种分析
+ 前面那个套路的贪心。

---

