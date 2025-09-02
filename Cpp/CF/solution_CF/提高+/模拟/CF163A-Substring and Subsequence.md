# Substring and Subsequence

## 题目描述

One day Polycarpus got hold of two non-empty strings $ s $ and $ t $ , consisting of lowercase Latin letters. Polycarpus is quite good with strings, so he immediately wondered, how many different pairs of " $ x $ $ y $ " are there, such that $ x $ is a substring of string $ s $ , $ y $ is a subsequence of string $ t $ , and the content of $ x $ and $ y $ is the same. Two pairs are considered different, if they contain different substrings of string $ s $ or different subsequences of string $ t $ . Read the whole statement to understand the definition of different substrings and subsequences.

The length of string $ s $ is the number of characters in it. If we denote the length of the string $ s $ as $ |s| $ , we can write the string as $ s=s_{1}s_{2}...\ s_{|s|} $ .

A substring of $ s $ is a non-empty string $ x=s[a...\ b]=s_{a}s_{a+1}...\ s_{b} $ ( $ 1<=a<=b<=|s| $ ). For example, "code" and "force" are substrings or "codeforces", while "coders" is not. Two substrings $ s[a...\ b] $ and $ s[c...\ d] $ are considered to be different if $ a≠c $ or $ b≠d $ . For example, if $ s $ ="codeforces", $ s[2...2] $ and $ s[6...6] $ are different, though their content is the same.

A subsequence of $ s $ is a non-empty string $ y=s[p_{1}p_{2}...\ p_{|y|}]=s_{p1}s_{p2}...\ s_{p|y|} $ ( $ 1<=p_{1}&lt;p_{2}&lt;...&lt;p_{|y|}<=|s| $ ). For example, "coders" is a subsequence of "codeforces". Two subsequences $ u=s[p_{1}p_{2}...\ p_{|u|}] $ and $ v=s[q_{1}q_{2}...\ q_{|v|}] $ are considered different if the sequences $ p $ and $ q $ are different.

## 说明/提示

Let's write down all pairs " $ x $ $ y $ " that form the answer in the first sample: " $ s[1...1] $ $ t[1] $ ", " $ s[2...2] $ $ t[1] $ ", " $ s[1...1] $ $ t[2] $ "," $ s[2...2] $ $ t[2] $ ", " $ s[1...2] $ $ t[1 2] $ ".

## 样例 #1

### 输入

```
aa
aa
```

### 输出

```
5
```

## 样例 #2

### 输入

```
codeforces
forceofcode
```

### 输出

```
60
```

# 题解

## 作者：KING_OF_TURTLE (赞：10)

题意：告诉你一个字符串s,一个字符串t，让你从s中选出不同的子串x，从t中选出不同的子序列y（子串、子序列傻傻分不清的自行百度），总共有多少种组合使得x，y的内容相同。



思路：粗略思考的话似乎除了dp就没有其他想法了把。dp[i][j]表示在s中以第i个字符结尾的子串，在t中以第j位结尾的子序列，满足题意的组合的个数。那么容易得到转移方程

dp[i + 1][j + 1] = (dp[i + 1][j] + (s[i] == s[j]) * (dp[i][j] + 1))

答案只要求1 <= i <= s.length()的dp[i][t.length()]的总和即可

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
long long sum,len1,len2,dp[5050][5050];
const long long mod=1e9+7;
string a,b;
int main()
{
	while(cin>>a>>b)
	{
		sum=0;
		memset(dp,0,sizeof(dp));
		len1=a.size();
		len2=b.size();
		for(int i=0;i<len1;i++)
		{
			for(int j=0;j<len2;j++)
			dp[i+1][j+1]=(dp[i+1][j]+(a[i]==b[j])*(dp[i][j]+1))%mod;
		}
		for(int i=1;i<=len1;i++)
		sum=(sum+dp[i][len2])%mod;
		printf("%lld\n",sum);
	}
	return 0;
}

---

## 作者：crashed (赞：5)

# 题目
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[点这里](https://www.luogu.org/problem/CF163A)看题目。
# 分析
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;题目有误，应该是$x$是$s$的字串，$y$是$t$的**子序列**，然后$x$和$y$应该长得一样。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;所以我们可以想到这样的$DP$：  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$DP(i,j)$：$s$中以$i$结尾的字串，$t$中前$j$个字符组成的序列的相同的个数。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;分成两类情况思考转移：  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$s[i]==t[j]$：此时比$DP(i-1,j-1)$多了一种组合情况，于是此时有$DP(i-1,j-1)+1$种情况。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$s[i]\not=t[j]$：失配的话就只能让$j$往前跳，此时有$DP(i,j-1)$中情况。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;综上有：  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$\displaystyle DP(i,j)=DP(i,j-1)+\begin{cases}0&s[i]\not=t[j]\\DP(i-1,j-1)+1&s[i]==s[j]\end{cases}$  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;答案为$\sum_{i=1}^{len(s)}DP(i,len(t))$  
# 代码
```cpp
#include <cmath>
#include <cstdio>
#include <cstring>

typedef long long LL;

const int mod = 1e9 + 7;
const int MAXS = 5005, MAXT = 5005, MAXSIZ = 205, MAXL = MAXS + MAXT, MAXLOG = 16;

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

LL DP[MAXS][MAXT];
int a[MAXS], b[MAXT];
char s[MAXS], t[MAXT];
int N, M;

int main()
{
	scanf( "%s%s", s + 1, t + 1 );
	N = strlen( s + 1 ), M = strlen( t + 1 );
	for( int i = 1 ; i <= N ; i ++ ) a[i] = s[i];
	for( int i = 1 ; i <= M ; i ++ ) b[i] = t[i];
	LL res = 0;
	for( int i = 1 ; i <= N ; i ++ )
	{
		for( int j = 1 ; j <= M ; j ++ )
		{
			DP[i][j] = DP[i][j - 1];
			if( a[i] == b[j] )
			{
				DP[i][j] = ( DP[i][j] + DP[i - 1][j - 1] + 1 ) % mod;
			}
		}
		res = ( res + DP[i][M] ) % mod;
	}
	write( res ), putchar( '\n' );
	return 0;
}
```

---

## 作者：liuyifan (赞：4)

## DP（最长公共子串变种)

设f[i][j]表示第一个以i结尾第二个以j结尾的方案总数

所以容易得出状态转移就是f[i][j]=1+f[i-1][j-1]+f[i-1][j-2]+...+f[i-1][1]

所以短小精干的code:
```cpp
#include<bits/stdc++.h>//万能头文件
#define reg register//register卡常
#define ll long long
using namespace std;
ll f[5005][5005],ans,len1,len2;//注意long long，CF的题很喜欢卡精度
char a[5005],b[5005];
int main()
{
    scanf("%s%s",a+1,b+1);//使字符串下标从1开始
    len1=strlen(a+1);
    len2=strlen(b+1);//注意以后调用的时候也都要+1
    for(reg int i=1;i<=len1;i++)
    for(reg int j=1;j<=len2;j++)
    {
        if(a[i]==b[j])f[i][j]=(f[i][j]+f[i-1][j-1]+1)%1000000007;
        f[i][j]=(f[i][j]+f[i][j-1])%1000000007;//状态转移如上
        //注意随时取模,这种题（尤其是还要累加的）很容易爆掉
    }
    for(reg int i=1;i<=len1;i++)ans=(ans+f[i][len2])%1000000007;//求和,同上
    printf("%lld",ans);//输出
    return 0;//圆满的结束
}
```


---

## 作者：fjy666 (赞：3)

## 题目链接：[子串和子序列](https://www.luogu.com.cn/problem/CF163A)
题目大意	
输入两个字符串s和t，他们都仅由小写字母构成。令x是s的**非空子串**，y是t的**非空子序列**，问有多少种方式构造x和y，使得x与y相等（**构造子串和子序列时，只要位置不一样，就算不同的构造方式**），答案对10^9+7取模。

------------
20pts:
因为字母都一样，所以只要统计每种长度的串对答案的贡献	
s中长度为i的子串有$n-i+1$种	
t中长度为i的子序列有$C_m^i$种	
所以总和是$(n-i+1) \times C_m^i$种	
```cpp
for(int i=1;i<=m;++i)
{
	C[i][0]=C[i][i]=1;
	for(int j=1;j<i;++j)
		C[i][j]=(C[i-1][j-1]+C[i-1][j])%P;
}
for(int i=1;i<=min(n,m);++i)
	ans+=(C[m][i]*(n-i+1))%P;
```

注：这里我们可以用杨辉三角来计算组合数，时间复杂度$O(n^2)$



------------
30pts:
我们可以直接暴力O(n^2)枚举子串，再匹配
```cpp
void dfs(int x,int y)
{
	if(y==w+1){++ans;return;} 
	if(x>m)return;
	if(t[x]==r[y])dfs(x+1,y+1);
	dfs(x+1,y);
}
for(int i=1;i<=n;++i)
{
	w=0;
	for(int j=i;j<=n;++j)
	{
		r[++w]=s[j];
		//r代表每一个子序列 
		dfs(1,1);
	}
}
```

ans即为结果

------------
100pts:
DP思想:设$dp[i][j]$表示在s的第i个字符结尾和t的前j个字符所有的子串
若$s[i]=t[j]$
	则$dp[i][j]$
	1. 可以从$dp[i][j-1]$继承下来
	2. 还可以$s[i]$,$t[j]$单独成串
	3. 还可以用$dp[i-1][j-1]$中都用$s[i]$延长

所以总和等于$dp[i][j-1]+dp[i-1][j-1]+1$	
否则，就只能继承$dp[i][j-1]$的了
($t[j]$在$dp[i][j]$里不可能用到了)
    
```cpp
#include <cstring>
#include <cstdio>
using namespace std;
const int P=1000000007;
char s[5001],t[5001];
int dp[5001][5001];
int main()
{
	scanf("%s%s",s+1,t+1);
//	printf("%d",P);
	int slen,tlen;
	slen=strlen(s+1);tlen=strlen(t+1);
	dp[0][0]=0;
	for(int i=1;i<=slen;++i)
		for(int j=1;j<=tlen;++j)
			if(s[i]==t[j])
				dp[i][j]=(dp[i][j-1]%P+dp[i-1][j-1]%P+1/*s[i],t[j]*/)%P;
			else
				dp[i][j]=dp[i][j-1];
	/*
	dp[i][j]表示在s的第i个字符结尾和t的前j个字符所有的子串
	若s[i]==t[j]
	则dp[i][j]可以从dp[i][j-1]继承下来，还可以s[i],t[j]单独成串，
	还可以用dp[i-1][j-1]中都用s[i]延长
	所以等于 dp[i][j-1]+dp[i-1][j-1]+1
	否则，就只能继承dp[i][j-1]的了(t[j]在dp[i][j]里不可能用到了)
	*/
	int ans=0;
	for(int i=1;i<=slen;++i)
		ans=(ans+dp[i][tlen])%P;
	printf("%d",ans);
	return 0;
}

```


---

## 作者：a1ioua (赞：2)

### 题意
输入字符串 $s$ 和 $t$，输出有多少对不同的 $x$ 与 $y$，使得 $x$ 是 $s$ 的**子串**，$y$ 是 $t$ 的**子序列**，$x$ 和 $y$ 的内容是相同的。答案对 $10^9+7$ 取模。
### 解决办法
考虑 DP。

设 $dp_{i,j}$ 是 $s$ 中以 $i$ 结尾的字串， $t$ 中前 $j$ 个字符组成的序列里面的相同的个数。

很显然，分类讨论 $dp_{i,j}$：
1. 当 $s_i=t_i$ 时，可以再配成一组。所以比 $dp_{i-1,j-1}$ 多了 $1$ 种情况。所以此时情况为 $dp_{i,j - 1}+dp_{i-1,j-1}+1$。
1. 当 $s_i\ne t_i$ 时，不能再配成一组了，只能让 $j$ 向后跳。所以此时情况为 $dp_{i,j - 1}$。

所以，转移方程：
$$dp_{i,j}=\begin{cases}dp_{i,j - 1}+dp_{i-1,j-1}+1\qquad s_i=t_i\\dp_{i,j - 1}\qquad\qquad\qquad\qquad\ \ \, s_i\ne t_i\end{cases}$$

很显然，答案为 $\sum^{\text{length(s)}}_{i=1}dp_{i,\text{length(t)}}$。

**注意取模。**

### 代码
```cpp
#include <bits/stdc++.h>
#define mod 1000000007
using namespace std;
int n;
unsigned long long dp[5005][5005], ans;
string s, t;
signed solve() {
	
	cin >> s >> t;
	for (int i = 1; i <= (int)s.length(); i++)
		for (int j = 1; j <= (int)t.length(); j++)
			if (s[i - 1] == t[j - 1])
				dp[i][j] = (dp[i][j - 1] + dp[i - 1][j - 1] + 1) % mod;
			else
				dp[i][j] = dp[i][j - 1];
	for (int i = 1; i <= (int)s.length(); i++)
		ans = (ans + dp[i][(int)t.length()]) % mod;
	printf("%llu\n", ans);
	return 0;
}
signed main() { return solve(); }
```

---

## 作者：Islauso (赞：2)

印象中好像是唯一一道自己做对的除背包以外的线性DP题（~~我太菜了QAQ~~），因此想写篇题解纪念一下

# 题目大意

[题目传送门](https://www.luogu.com.cn/problem/CF163A)

翻译有点问题，我这里重新翻一下

大概意思就是说，给你两个字符串$s$和$t$，求出有多少对字符串$x$和$y$，满足$x$是$s$的子串且$y$是$t$的子序列，答案对$1000000007(10^9+7)$取模

关于子串和子序列的区别，可以理解为子串是一段连续的区间，而子序列则不一定是连续的

# 思路

这道题乍一看其实很像最长公共子序列，唯一不同的在于对于$s$要取它的子串，我们类比一下最长公共子序列的状态转移方程

$$dp[i,j]=\begin{cases}0\ (i=0 \text{ or }j=0)\\dp[i-1,j-1]+1\ (s[i]=t[j])\\\max(dp[i-1,j],dp[i,j-1])\ (s[i]\not =t[j])\end{cases}$$

$dp[i,j]$表示的是在$s$的前$i$个字符和$t$的前$j$个字符中的最长公共子序列的长度，因此，对于这道题，我们不妨设$dp[i,j]$为**以**$s$**的第**$i$**个字符为结尾的子串与**$t$**的前**$j$**个字符中的子序列相同的个数**，同样，我们分成两种情况来讨论，一种是$s[i]=t[j]$，一种是$s[i]\not =t[j]$

如果$s[i]=t[j]$，那么当前状态首先应该包括了$dp[i-1,j-1]$的所有情况，因为这两个字符是相同的，那么我们相当于是可以在$dp[i-1,j-1]$的所有情况后面加上一个相同的字符，结果一定还是成立的，然后还应该包括$dp[i,j-1]$的所有情况，因为不管当前两个字符是否相同，$dp[i,j-1]$的所有情况肯定都适用于$dp[i,j]$，最后，$dp[i,j]$还应该包括$s[i]$和$t[j]$这对组合，因为很明显前面两种情况都没有把$t[j]$算进去，所以最后的状态转移方程应该是这样的

$$dp[i,j]=dp[i,j-1]+dp[i-1,j-1]+1$$

如果$s[i]\not = t[j]$，那么上面所说的$dp[i-1,j-1]$的情况就不适用于当前情况，也没有$s[i]$和$t[j]$这对组合，所以状态转移方程就是这样的

$$dp[i,j]=dp[i,j-1]$$

最后，由于$dp[i,j]$只统计了以$s[i]$为结尾的子串，所以最终答案应该把所有的$dp[i,|s|]$加起来，另外，不要忘记取模

# 参考代码

```cpp
#include<bits/stdc++.h>
#define mod 1000000007
using namespace std;
string a,b;
int n,m,ans,dp[5001][5001];
int main()
{
	getline(cin,a);
	getline(cin,b);
	n=a.length();
	m=b.length();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(a[i-1]==b[j-1])
				dp[i][j]=(dp[i][j-1]+dp[i-1][j-1]+1)%mod;//取模！！
			else
				dp[i][j]=dp[i][j-1];
	for(int i=1;i<=n;i++)
		ans=(ans+dp[i][m])%mod;
	printf("%d",ans);
	return 0;
}
```



---

## 作者：ny_jerry2 (赞：1)

## 前言
又是一道字符串 dp。

## 思路
设状态 $f_{i,j}$ 表示在 ${x_i,y_j}$ 都**必选**的情况下满足条件的个数。

对于 $s_i \ne t_j$：显然，一种情况都没有，因此可以得到 $f_{i,j} = 0$。下面重点解释 $s_i = t_j$。

$\because$ 它可以与前面的情况配对，即有：  

$$
f_{i,j} = \sum_{k=1}^{j-1} f_{i-1,k} + 1
$$


为什么由 $i-1$ 转移而非 $\sum_{a=1}^{i-1}$ 呢？是因为它必须是一个子串，该状态只能取决于上一个值，否则就变成子序列了。  
而后面的 $1$ 是因为这两个字符本身就可以配对。

观察到上面的式子，发现可以前缀和优化。

设 $sum_{i,j} = \sum_{k=1}^j f_{i,k}$，则 $sum_{i,j-1} = \sum_{k=1}^{j-1} f_{i,k}$。  

$\therefore$ 可以得到递推式：
$$
sum_{i,j} = sum_{i,j-1} + f_{i,j}
$$

$\therefore$ 状态转移就变成了 $f_{i,j} = sum_{i-1,j-1} + 1$。

当然不论字符相不相等，都要更新前缀和。


答案：
$$ans = \sum_{i=1}^n \sum_{j=1}^m f_{i,j}$$
## 代码
```cpp
#include<iostream>
#include<cstring>
using namespace std;
const int N=5010,mod=1e9+7;
char s[N],t[N];
int n,m;
int f[N][N],sum[N][N];
int ans;
void dp(){
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(s[i]!=t[j]){
				f[i][j]=0;
			}else{
				f[i][j]=(sum[i-1][j-1]+1)%mod;
			}
			sum[i][j]=(sum[i][j-1]+f[i][j])%mod;
			ans=(ans+f[i][j])%mod;
		}
	}
}
int main(){
	scanf("%s%s",s+1,t+1);
	n=strlen(s+1),m=strlen(t+1);
	dp();
	cout<<ans;
}
```

---

## 作者：Super_Cube (赞：1)

# Solution

设 $dp_{i,j}$ 表示 $s$ 中前 $i$ 个字符与 $t$ 中前 $j$ 个字符能匹配出的方案数。由于只要求 $t$ 取出的是子序列，那么第 $j$ 个字符可以不去匹配，于是直接继承 $dp_{i,j-1}$。还有一种情况是 $s_i=t_j$，此时可以进行匹配，因为要求 $s$ 取出子串，所以只能取 $dp_{i-1,j-1}$ 处的方案，还可以单独以 $s_i$ 开头成立一种与 $t_j$ 匹配的新方案。答案自然是 $\displaystyle\sum_{i=1}^ndp_{i,m}$。

# Code

```cpp
#include<bits/stdc++.h>
const int mod=1e9+7;
int dp[5005][5005];
char a[5005],b[5005];
int n,m,ans;
int main(){
	scanf("%s%s",a+1,b+1);
	n=strlen(a+1);m=strlen(b+1);
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			dp[i][j]=dp[i][j-1];
			if(a[i]==b[j]&&(dp[i][j]+=dp[i-1][j-1]+1)>=mod)dp[i][j]-=mod;
		}
		if((ans+=dp[i][m])>=mod)ans-=mod;
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：ny_Dacong (赞：0)

# 思路

可以从集合的角度考虑本题。

## 状态设计

令 $dp_{i,j}$ 表示必选 $s_i$ 且以 $s_i$ 结尾的子串与截止到 $t_j$ 及以前的子序列中，相同的个数。

注意，根据这里的定义，$s_i$ 必选，但 $t_j$ 可以不选。

## 集合划分

“必选 $s_i$ 且以 $s_i$ 结尾的子串”可以看做是“必选 $s_{i-1}$ 且以 $s_{i-1}$ 结尾的子串”的后面加上一个 $s_i$ 组成的子串。

“截止到 $t_j$ 及以前的子序列”可以看做是“截止到 $t_{j-1}$ 及以前的子序列”的后面加上一个 $t_j$ 组成的子序列，或者“截止到 $t_{j-1}$ 及以前的子序列”不加上 $t_j$ 这两种情况。

于是考虑转移。

## 状态转移

当 $s_i = t_j$ 时，可以在 $dp_{i-1,j-1}$ 这个集合中的所有方案的后面同时加上 $s_i$ 以及 $t_j$。

![](https://cdn.luogu.com.cn/upload/image_hosting/ju9grh39.png?x-oss-process=image/resize,m_lfit,h_350)

不要忘记 $t_j$ 是可以不选的。所以 $dp_{i,j}$ 还可以由 $dp_{i,j-1}$ 直接转移过来。

因此状态转移方程就出来了：

- $dp_{i,j} = dp_{i,j-1}$。
- 当 $s_i = t_j$ 时，$dp_{i,j}$ 需额外加上 $dp_{i-1,j-1}$。

最后别忘了取模。

# AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,ans = 0;
const int MOD = 1e9+7;
char s[5005],t[5005];
int dp[5005][5005];
int main(){
	scanf("%s%s",s+1,t+1);
	n = strlen(s+1),m = strlen(t+1);
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			dp[i][j] = dp[i][j-1];
			if(s[i] == t[j]){
				dp[i][j] += dp[i-1][j-1]+1;
			}
			dp[i][j] %= MOD;
		}
	}
	for(int i = 1; i <= n; i++){
		ans += dp[i][m];
		ans %= MOD;
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：revolutionary_oier (赞：0)

# CF163A Substring and Subsequence

## 思路分析

明晰一下**概念**：
- 子序列：不一定连续的字符串子集（顺序）。
- 子串：连续的字符串子集（顺序）。

**状态定义**:定义 $f_{i,j}$ 表示以 $s_i$ 为结尾的子串，与以前 $j$ 个第二个字符串的字符组成的子序列，相等的组合数量。

**状态转移方程**：$f_{i,j}=f_{i,j-1}+\begin{cases}
  f_{i-1,j-1}+1 & s_i=t_j \\
  0 & s_i≠t_j
\end{cases}$。

**状态初始化**：$f_{0,x}=1(x\in (0,len_t],x\in \mathbb{Z})$。


## 代码实现
```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;

const int maxn=5e3+10;
const int mod=1e9+7;
int n,m;
char s[maxn],t[maxn];
int f[maxn][maxn];
inline void ipt(){
    scanf("%s%s",s,t);
    n=strlen(s);
    m=strlen(t);
    for(int i=n;i>=1;i--)s[i]=s[i-1];
    for(int i=m;i>=1;i--)t[i]=t[i-1];
}
inline void dp(){
    // for(int i=1;i<=m;i++)f[0][i]=1;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            f[i][j]=(f[i][j-1]+((s[i]!=t[j])?0:(f[i-1][j-1]+1)))%mod;
    int ans=0;
    for(int i=1;i<=n;i++)ans=(ans+f[i][m])%mod;
    printf("%lld\n",ans);
}
signed main(){
    ipt();
    dp();
    return 0;
}
```

---

## 作者：CQ_Bob (赞：0)

## 分析

考虑 DP。

定义状态函数 $f_{i,j}$ 表示在 $s[1\dots i]$ 中选一个子串 $a$，在 $t[1 \dots j]$ 中选一个子序列 $b$，且 $s_i,t_j$ 必选时 $a=b$ 的方案数。则有两种情况：

1. $s_i \ne t_j$。此时 $a$ 和 $b$ 是不可能相同的了，所以 $f_{i,j}=0$。
2. $s_i = t_j$。在只选 $s_i,t_j$ 时有 $1$ 种方案，而不止选 $s_i,t_j$ 时根据枚举前一个字符选的位置，有 $\sum\limits_{k=1}^{j-1} f_{i-1,k}$ 种方案。所以 $f_{i,j}=1+\sum\limits_{k=1}^{j-1} f_{i-1,k}$。

整合一下有转移方程：$f_{i,j}=[s_i=t_j]\times(\sum\limits_{k=1}^{j-1}f_{i-1,k}+1)$。定义 $s_{i,j}=\sum\limits_{k=1}^{j} f_{i,k}$，则有：$f_{i,j}=[s_i=t_j]\times(s_{i,j-1}+1)$。这就是个前缀和优化，在更新完 $f_{i,j}$ 只后直接更新 $s_{i,j}$ 即可。

答案就是 $\sum\limits_{i=1}^{|s|}\sum\limits_{j=1}^{|t|}f_{i,j}$。复杂度 $O(n^2)$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
//#define int long long
#define re register
#define il inline
#define pii pair<int,int>
#define x first
#define y second
#define gc getchar()
#define rd read()
#define debug() puts("------------")

namespace yzqwq{
	il int read(){
		int x=0,f=1;char ch=gc;
		while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=gc;}
		while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=gc;
		return x*f;
	}
	il int qmi(int a,int b,int p){
		int ans=1;
		while(b){
			if(b&1) ans=ans*a%p;
			a=a*a%p,b>>=1;
		}
		return ans;
	}
	il auto max(auto a,auto b){return (a>b?a:b);}
	il auto min(auto a,auto b){return (a<b?a:b);}
	il int gcd(int a,int b){
		if(!b) return a;
		return gcd(b,a%b);
	}
	il int lcm(int a,int b){
		return a/gcd(a,b)*b;
	}
	il void exgcd(int a,int b,int &x,int &y){
		if(!b) return x=1,y=0,void(0);
		exgcd(b,a%b,x,y);
		int t=x;
		x=y,y=t-a/b*x;
		return ;
	}
	mt19937 rnd(time(0));
}
using namespace yzqwq;

const int N=5005,p=1e9+7;
int f[N][N],s[N][N];
char a[N],b[N];
int n,m;

il void solve(){
	scanf("%s",a+1),n=strlen(a+1);
	scanf("%s",b+1),m=strlen(b+1);
	for(re int i=1;i<=n;++i)
	for(re int j=1;j<=m;++j){
		f[i][j]=(long long)((a[i]==b[j])*(s[i-1][j-1]+1))%p;
		s[i][j]=(long long)(s[i][j-1]+f[i][j])%p;
	}
	long long ans=0;
	for(re int i=1;i<=n;++i) ans=(ans+s[i][m])%p;
	printf("%lld\n",ans);
	return ;
}

signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	int t=1;while(t--)
	solve();
	return 0;
}
```


---

