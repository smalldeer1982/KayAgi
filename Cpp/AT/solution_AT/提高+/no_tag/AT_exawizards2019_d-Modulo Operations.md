# Modulo Operations

## 题目描述

[problemUrl]: https://atcoder.jp/contests/exawizards2019/tasks/exawizards2019_d

すぬけ君は黒板と $ N $ 個の整数からなる集合 $ S $ を持っています。 $ S $ の $ i $ 番目の要素は $ S_i $ です。

すぬけ君は黒板に整数 $ X $ を書いたのち、以下の操作を $ N $ 回行います。

- $ S $ から要素を $ 1 $ つ選んで取り除く。
- その後、現在黒板に書かれた数を $ x $、$ S $ から取り除かれた整数を $ y $ として、黒板に書かれた数を $ x\ \bmod\ {y} $ に書き換える。

$ S $ から要素を取り除く順序は $ N! $ 通りありえます。 それぞれの場合について、$ N $ 回の操作後に黒板に書かれている数を求め、その総和を $ 10^{9}+7 $ で割ったあまりを求めてください。

## 说明/提示

### 制約

- 入力は全て整数である。
- $ 1\ \leq\ N\ \leq\ 200 $
- $ 1\ \leq\ S_i,\ X\ \leq\ 10^{5} $
- $ S_i $ たちは相異なる。

### Sample Explanation 1

\- $ S $ から数を取り除く順序は $ 2 $ 通りあります。 - $ 3,7 $ の順で取り除いたとき、黒板に書かれた数は $ 19\ \rightarrow\ 1\ \rightarrow\ 1 $ と変化します。 - $ 7,3 $ の順で取り除いたとき、黒板に書かれた数は $ 19\ \rightarrow\ 5\ \rightarrow\ 2 $ と変化します。 - これらの総和である $ 3 $ を出力してください。

### Sample Explanation 3

\- 総和を $ 10^{9}+7 $ で割ったあまりを求めるのを忘れずに。

## 样例 #1

### 输入

```
2 19
3 7```

### 输出

```
3```

## 样例 #2

### 输入

```
5 82
22 11 6 5 13```

### 输出

```
288```

## 样例 #3

### 输入

```
10 100000
50000 50001 50002 50003 50004 50005 50006 50007 50008 50009```

### 输出

```
279669259```

# 题解

## 作者：igAC (赞：1)

# $\text{Describe}$

[洛谷 link](https://www.luogu.com.cn/problem/AT_exawizards2019_d)

[ATlink](https://atcoder.jp/contests/exawizards2019/tasks/exawizards2019_d)

[更好的阅读体验？](https://www.luogu.com.cn/blog/780168/solution-at-exawizards2019-d)

简要题意：

黑板上有个数字 $x$，你有一个长度为 $n$ 的序列 $a$。

你可以选择 $a$ 中的一个数 $a_i$，将它从序列中删去，并且让黑板上的数字变成 $x \bmod a_i$。

问每一种方案最后黑板上剩下的那个数的总和对 $10^9+7$ 取模后的结果。

# $\text{Solution}$

简单 $\text{DP}$ 题。

我们要知道黑板上最后剩下那个数的总和，我们只需知道每个数最后剩在黑板上的方案数即可。

显然，可能对黑板上这个数有影响的只有前缀最小值。

所以如果一个较大的数放在一个较小的数后面，那么这个大数对答案是没有影响的。

我们设 $f_{i,j}$ 表示考虑前 $i$ 大的数，黑板上的数为 $j$ 的方案数。

将 $a$ 数组按降序排序，转移只有两种。

若我们选择这个数：$f_{i,j \bmod a_i}=f_{i,j \bmod a_i}+f_{i,j}$。

若我们不选择这个数，那么这个数就只能在后面 $n-i$ 个操作里面选择。

即：$f_{i,j}=f_{i,j}+f_{i-1,j} \times (n-i)$。

最后的答案为：$\sum^{x}_ {i=0} i \times f_{n,i}$。

具体实现可参考代码。

# $\text{Code}$

时空复杂度都为 $O(nX)$。

```cpp
#include<bits/stdc++/h>
#define int long long
#define N 205
#define M 100005
#define Mod 1000000007
using namespace std;
int read(){
	int x=0,f=1,ch=getchar();
	for(;!isdigit(ch);ch=getchar()) f=(ch=='-')?-1:1;
	for(;isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch^48);
	return x*f;
}
int n,x,a[N],f[N][M],ans;
signed main(){
	n=read(),x=read();
	for(int i=1;i<=n;++i) a[i]=read();
	sort(a+1,a+n+1),reverse(a+1,a+n+1);
	f[0][x]=1;
	for(int i=1;i<=n;++i){
		for(int j=0;j<=x;++j){
			if(f[i-1][j]){
				f[i][j]=(f[i][j]+f[i-1][j]*(n-i)%Mod)%Mod;
				f[i][j%a[i]]=(f[i][j%a[i]]+f[i-1][j]%Mod)%Mod;
			}
		}
	}
	for(int i=0;i<=x;++i) ans=(ans+f[n][i]*i%Mod)%Mod;
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：RAND_MAX (赞：0)

一道动态规划好题。

我们要求的是最后留在黑板上数的所有情况的总和。所以只需要对于每一种可能的留在黑板上的数 $x$，求有多少种方案可以剩下 $x$。设方案数为 $f(x)$，最后的答案就是 $\sum x\times f(x)$。

由于取模的性质，我们不难发现黑板上的数**单调不增**。所以最多只有 $X$ 种情况，考虑进行 DP。

我们设 $f_{i,j}$ 为当前选了 $i$ 个，目前黑板上的数为 $j$ 的方案数，不过我们发现这种情况转移是困难的。于是考虑再分析一些性质。

很难不发现对于一个 $s_i$，若是前面已经删除了比它更小的数，那么黑板上的数此刻必定小于 $s_i$，对于这个 $s_i$ 是不会对答案产生任何贡献的。那么我们将 $s$ 数组从大到小排序之后便可以按照上面所设计的状态进行 DP。

考虑状态转移，如果我们选择把这个数计入贡献（前面没有比它小的），那么有转移式子 $f_{i,j\bmod s_i}=f_{i,j\bmod s_i}+f_{i,j}$。

如果我们不选择这个数，那么只有之后的 $(n-i)$ 种操作之后才选择，所以有  $f_{i,j}=f_{i,j}+f_{i,j}\times (n-i)$。

答案即为 $\sum^X_{i=0} i\times f_{n,i}$。


```cpp
#include<bits/stdc++.h>
#define int long long
#define R read()
#define mod 1'000'000'007
using namespace std;
bool cmp(int x,int y)
{
	return x>y;
}
int read()
{
	int x=0,f=1;
	char c=getchar();
	while(c>'9'||c<'0')
	{
		if(c=='-')
		{
			f=-1;
		}
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		x=(x<<1)+(x<<3)+c-48;
		c=getchar();
	}
	return x*f;
}
void write(int x)
{
	static int st[35],top=0;
	if(x<0)
	{
		x=-x;
		putchar('-');
	}
	do
	{
		st[top++]=x%10;
		x/=10;
	}while(x);
	while(top)
	{
		putchar(st[--top]+48);
	}
	putchar('\n');
}
int n,a[1010],x,f[210][100010],ans;
signed main()
{
	n=R,x=R;
	for(int i=1;i<=n;i++)
	{
		a[i]=R;
	}
	sort(a+1,a+n+1,cmp);
	f[0][x]=1;
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<=x;j++)
		{
			if(f[i-1][j])
			{
				f[i][j]+=f[i-1][j]%mod*(n-i)%mod;
				f[i][j]%=mod;
				f[i][j%a[i]]+=f[i-1][j]%mod;
				f[i][j%a[i]]%=mod;
			}
		}
	}
	for(int i=0;i<=x;i++)
	{
		ans+=(i*f[n][i])%mod;
		ans%=mod;
	}
	write(ans);
 	return 0;
}

```

---

## 作者：_Flame_ (赞：0)

### $\text{solution}$

简单 `dp` 题。

要求出题目中要求的最后剩下的数的总和，显然对于 $0$ 到 $x$ 求出每一个每一个值最后出现的次数即可。

考虑怎么求这个次数，发现一个性质，若 $y>x$ 且 $y$ 放在 $x$ 后面，则进行一次操作后留下的 $x\bmod y=x$，对最后的答案是没有影响的。所以能影响答案的只有数列的前缀最小值。

利用这个性质设计状态，设 $dp_{j,i}$ 表示考虑到前 $i$ 大的数，当前数是 $j$ 的情况，分类讨论：

- 若 $a_i$ 对最后的答案会有影响，则有转移 $dp_{j\bmod a_{i},i}=dp_{j,i-1}+dp_{j\bmod a_i,i}$。

- 若 $a_i$ 对最后的答案没有影响，则这个数可以在数列中随便填，有转移 $dp_{j,i}=dp_{j,i}+dp_{j,i-1}\times (n-i)$。

最后计算 $\sum\limits_{i=0}^{x} i\times dp_{i,n}$ 即为答案。

### $\text{code}$

```cpp
int n,x;

int a[maxn];

int dp[maxn][maxm];

bool cmp(int a,int b){
	return a>b;
}

void solve(){
	n=read(),x=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
	}
	sort(a+1,a+n+1,cmp);
	dp[x][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=x;j++){
			int cnt=dp[j][i-1];
			if(cnt==0){
				continue ;
			}
			else{
				dp[j][i]=(dp[j][i]+cnt*(n-i)%mod)%mod;
				dp[j%a[i]][i]=(dp[j%a[i]][i]+cnt)%mod;
			}
		}
	}
	int ans=0;
	for(int i=0;i<=x;i++){
		int cnt=i*dp[i][n]%mod;
		ans=(ans+cnt)%mod;
	}
	write(ans);
	puts("");
	return ;
}
```

---

## 作者：zdd6310 (赞：0)

# solution
抽象 $dp$ 题。

首先玩一下样例，发现取模操作有一个特殊的性质：

**一个数取模后严格不大于原来的数。**

相当于 $X$ 在操作中单调不升。

于是在转移时可以从大到小考虑。

观察数据范围，发现可以用 $N\times X$ 的 $dp$。

设计 $dp$ 状态：$dp_{i,j}$ 表示考虑到第 $i$ 个数，当前的数是 $j$ 的方案数。

因为对于 $a_i$，这个数对答案的影响不好考虑。

考虑刷表法。
1. 如果 $a_i$ 对答案有影响：$dp_{i,j\bmod a_i}=dp_{i-1,j}$。
2. 如果 $a_i$ 对答案没有影响，那么这一个数可以放在操作序列的任意一个地方。
$dp_{i,j}=dp_{i-1,j}\times (n-i)$。

发现每一个状态只有前面一个状态转移过来。

可以状态压缩。

时间复杂度 $O(nX)$，空间复杂度 $O(X)$。
## code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=200+5;
const int MAX=1e5+5;
const int mod=1e9+7;
int n,x;
int a[MAXN];
int dp[2][MAX];
void Add(int& a,int b){a=(a+b)%mod;}
signed main(){
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(false);
    cin>>n>>x;
    for(int i=1;i<=n;i++)cin>>a[i];
    sort(a+1,a+n+1,[](int a,int b){return a>b;});
    dp[0][x]=1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=x;j++)dp[i%2][j]=0;
        for(int j=1;j<=x;j++){
            Add(dp[i%2][j%a[i]],dp[(i-1)%2][j]);
            Add(dp[i%2][j],dp[(i-1)%2][j]*(n-i)%mod);
        }
    }
    int ans=0;
    for(int i=1;i<=x;i++){
        Add(ans,dp[n%2][i]*i%mod);
    }
    cout<<ans<<"\n";
}
```

---

## 作者：skyskyCCC (赞：0)

## 前言。
动态规划。简单，但是我调了一个多小时。

我们可以这样理解题意：考虑一个给定的取模序列 $a_1,a_2,a_3\ldots,a_N$。其中可能对答案产生影响的是作为前缀最小值出现的 $a_i$。如果在除它之外的 $a_i$ 当前的数值已经不足 $a_i$ 可以视作没有进行取模操作。
## 分析。
既然存在 $a_i$ 使得对答案会产生影响，那么我们就只关心每一个对答案产生影响的 $a_i$ 所以我们考虑动态规划。一个很显然的思路就是将这个数组从小到大排列，然后对于每一个可能的 $a_i$ 进行动态规划。

我们设 $dp\left[i\right]\left[j\right]$ 为考虑前 $i$ 大的模数，得数为 $j$ 的排列方式数。这个的状态主要是由于我们对于任意的模数我们都要去找到可能的方案数。每一个第 $i$ 大的模数都可以转移到比它大的模数即第 $i+1$ 位模数。因为显然我们在计算 $i+1$ 时必须先计算 $i$ 同时对于 $i$ 来说，第 $i+1$ 可能包括该方案数。那么我们就可以从中出发，考虑两种情况：有影响与没有影响。

如果当前的 $a_i$ 对答案有影响，则有：
$$dp\left[i\right]\left[j\right]=dp\left[i+1\right]\left[j\bmod a_i+1\right]$$
如果相反的，没有影响，则有：
$$dp\left[i+1\right]\left[j\right]=dp\left[i+1\right]\left[j\right]\times\left(N-\left(i+1\right)\right)$$

动态转移一下，然后通过对于这两个情况的统筹计算，最后都加到答案上就行了。

代码如下，仅供参考：
```
#include<iostream>
#include<algorithm>
using namespace std;
const int mod=1e9+7;
int n,x,a[205];
int ans,dp[205][100005];
bool cmp(int a1,int a2){
	return a1>a2;
}
void js(int &x,int y){
	x+=y;
	if (x>=mod){
        x-=mod;
    }
}
int main(){
    cin>>n>>x;
	dp[0][x]=1;
	for (int i=1;i<=n;i++){
		cin>>a[i];
	}
    sort(a+1,a+n+1,cmp);
    for (int i=1;i<=n;i++){
	    for (int j=0;j<=x;j++){
		    int cnt=dp[i-1][j];
	    	js(dp[i][j%a[i]],cnt);
		    js(dp[i][j],1ll*cnt*(n-i)%mod);
		}
	}
	for (int i=0;i<=x;i++){
		js(ans,1ll*dp[n][i]*i%mod);
	}
	cout<<ans<<"\n";
	return 0;
}
```
## 后记。
大家如有疑问，可以在评论区提出，我会尽力解答的。

---

