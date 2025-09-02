# [ABC301F] Anti-DDoS

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc301/tasks/abc301_f

英大文字・英小文字からなる長さ $ 4 $ の文字列で、以下の $ 2 $ 条件をともに満たすものを `DDoS` 型文字列と呼ぶことにします。

- $ 1,2,4 $ 文字目が英大文字で、$ 3 $ 文字目が英小文字である
- $ 1,2 $ 文字目が等しい

例えば `DDoS`, `AAaA` は `DDoS` 型文字列であり、`ddos`, `IPoE` は `DDoS` 型文字列ではありません。

英大文字・英小文字および `?` からなる文字列 $ S $ が与えられます。 $ S $ に含まれる `?` を独立に英大文字・英小文字に置き換えてできる文字列は、$ S $ に含まれる `?` の個数を $ q $ として $ 52^q $ 通りあります。 このうち `DDoS` 型文字列を部分列に含まないものの個数を $ 998244353 $ で割ったあまりを求めてください。

## 说明/提示

### 注記

文字列の**部分列**とは、文字列から $ 0 $ 個以上の文字を取り除いた後、残りの文字を元の順序で連結して得られる文字列のことをいいます。  
例えば、`AC` は `ABC` の部分列であり、`RE` は `ECR` の部分列ではありません。

### 制約

- $ S $ は英大文字・英小文字および `?` からなる
- $ S $ の長さは $ 4 $ 以上 $ 3\times\ 10^5 $ 以下

### Sample Explanation 1

`?` の少なくとも一方が英小文字のとき、`DDoS` 型文字列を部分列に含みます。

### Sample Explanation 2

$ 998244353 $ で割ったあまりを求めてください。

## 样例 #1

### 输入

```
DD??S```

### 输出

```
676```

## 样例 #2

### 输入

```
????????????????????????????????????????```

### 输出

```
858572093```

## 样例 #3

### 输入

```
?D??S```

### 输出

```
136604```

# 题解

## 作者：cwfxlh (赞：9)

## [ABC301F](https://www.luogu.com.cn/problem/AT_abc301_f)   
小清新计数题。   

考虑把 DDoS 分成多个阶段，不难设计出如下几种 dp 状态：   
前 $i$ 个字符不出现形如 DD 的子序列的方案数，记为 $dp1_i$。  
前 $i$ 个字符不出现形如 DDo 的子序列的方案数，记为 $dp2_i$。  
前 $i$ 个字符不出现形如 DDoS 的子序列的方案数，记为 $dp3_i$。  

答案就是 $dp3_n$，那么考虑如何求这几种值。   

对于第一种状态，首先统计明确出现的大写字符，如果有出现 $2$ 次的，就直接为 $0$，否则考虑安排问号该如何选择。考虑选择 $j$ 个问号变为大写（小写不受限制所以直接乘就可以了），那么问号所变成的大写字符不能与出现过的大写字符重复，令还剩 $a$ 个未出现的大写字符，有 $b$ 个问号，则方案数为 $dp1_i=\sum_{j=0}^{\min(a,b)}{C_a^j\times A_b^j \times 26^{b-j}}$。   

考虑第二种状态，如果当前字符为小写，则 $dp2_i=dp1_{i-1}$，大写则 $dp2_i=dp2_{i-1}$，如果是问号就把两种合并一下，$dp2_i=26\times dp1_{i-1}+26\times dp2_{i-1}$。    

第三种状态和上面是一个道理。    

upd on 2023.10.25：感谢 @TankYu 的提醒，我代码中的 dp123 与题解中的 dp123 是反过来的，即代码中的 dp1 对应题解的 dp3，代码中的 dp3 对应题解的 dp1。现代码已修改。

代码：   

```cpp
#include<bits/stdc++.h>
#define int long long
#define MOD 998244353
using namespace std;
string s;
int n,dp3[300003],dp2[300003],dp1[300003],C[300003][33],A[300003][33],jc[300003],fsp[300003];
int apr[300003],num,sum,flg;
signed main(){
	jc[0]=1;
	fsp[0]=1;
	for(int i=1;i<=300000;i++){
		jc[i]=(jc[i-1]*i)%MOD;
		fsp[i]=(fsp[i-1]*26ll)%MOD;
	}
	for(int i=0;i<=300000;i++){
		C[i][0]=1;
		A[i][0]=1;
	}
	for(int i=1;i<=300000;i++){
		for(int j=1;j<=26;j++){
			C[i][j]=(C[i-1][j]+C[i-1][j-1])%MOD;
			A[i][j]=(C[i][j]*jc[j])%MOD;
		}
	}
	cin>>s;
	n=s.length();
	dp3[0]=dp2[0]=dp1[0]=1;
	num=26;
	for(int i=1;i<=n;i++){
		if(s[i-1]!='?'){
			if(s[i-1]>='A'&&s[i-1]<='Z'){
				if(apr[s[i-1]-'A'+1]==0)num--;
				else flg=1;
				apr[s[i-1]-'A'+1]=1;
			}
			for(int j=0;j<=num&&j<=sum;j++){
				dp1[i]+=(((C[num][j]*A[sum][j])%MOD)*fsp[sum-j])%MOD;
				dp1[i]%=MOD;
			}
			if(flg==1)dp1[i]=0;
			if(s[i-1]>='A'&&s[i-1]<='Z')dp2[i]=dp2[i-1];
			else dp2[i]=dp1[i-1];
			if(s[i-1]>='A'&&s[i-1]<='Z')dp3[i]=dp2[i-1];
			else dp3[i]=dp3[i-1];
		}
		else{
			sum++;
			for(int j=0;j<=num&&j<=sum;j++){
				dp1[i]+=(((C[num][j]*A[sum][j])%MOD)*fsp[sum-j])%MOD;
				dp1[i]%=MOD;
			}
			if(flg==1)dp1[i]=0;
			dp2[i]=(dp2[i-1]*26ll)%MOD;
			dp2[i]+=(dp1[i-1]*26ll)%MOD;
			dp2[i]%=MOD;
			dp3[i]=(dp3[i-1]*26ll)%MOD;
			dp3[i]+=(dp2[i-1]*26ll)%MOD;
			dp3[i]%=MOD;
		}
	}
	dp3[n]%=MOD;
	dp3[n]+=MOD;
	dp3[n]%=MOD;
	printf("%lld",dp3[n]);
	return 0;
}
```


---

## 作者：Emplace (赞：4)

## 思路
分为三种情况。

* 没有 两个相同的大写字母设为 $dp1$。
* 没有 两个相同的大写字母加小写字母设为 $dp2$。
* 没有 两个相同的大写字母加小写字母再加大写字母设为 $dp3$。

### 第一种

对于 $dp_1$，当已经有 两个相同的大写字母了，那么肯定直接为 $0$。否则应该从任意选取多个字母当作不同的大写字母。而剩下的为任意小写字母。则可写出一个公式。

$dp1_i=\sum_{j = 1}^{ min(qm,ch) } \ C_{ch}^{j} \cdot A_{qm}^{j} \cdot 26^{qm-j}$

### 第二种

* 如果为问号，那么肯定是从 $dp2_{i-1}+dp1_{i-1}$ 来的，因为这两个都可以保证没有两个相同的大写字母加小写字母，而且因为是问好且要为大写字母，所以再乘一个 $26$。

* 如果为大写字母，则直接从 $dp2_{i-1}$ 来，不用从 $dp1_{i-1}$ 来，是因为已经包含了。

* 如果为小写字母，那就只能从 $dp1_{i-1}$ 来了。

### 第三种

推法跟 $dp2$ 其实一样,就不细讲了。

* 为问号，$dp3_i=dp3_{i-1}+dp2_{i-1}$。

* 为大写字母，$dp3_i=dp2_{i-1}$。

* 为小写字母，$dp3_i=dp3_{i-1}$。

最后再警示后人，要取模！！！！！！！！！！
## Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
char s[1919810];
int dp1[514514],dp2[514514],dp3[514514],fac[514514],c[514514][30],c_26[514514],mod=998244353,f=1,qm,ch=26,tong[300];
signed main(){
	cin>>(s+1);
	int n=strlen(s+1);
	dp1[0]=1,dp2[0]=1,dp3[0]=1,fac[0]=1,c[0][0]=1,c_26[0]=1;
	for(int i=1;i<=400000;i++){
		c_26[i]=c_26[i-1]*26%mod;
		fac[i]=fac[i-1]*i%mod;
		c[i][0]=1;
		for(int j=1;j<=26;j++){
			c[i][j]=(c[i-1][j]+c[i-1][j-1])%mod;
		}
	} 
	for(int i=1;i<=n;i++){
		if(s[i]=='?'){
			qm++;
			dp2[i]=(dp2[i-1]+dp1[i-1])*26%mod;
			dp3[i]=(dp3[i-1]+dp2[i-1])*26%mod;
			for(int j=0;j<=min(qm,ch);j++){
				dp1[i]=(dp1[i]+f*c[ch][j]%mod*c[qm][j]%mod*fac[j]%mod*c_26[qm-j]%mod)%mod;
			}
		}
		else{
			if(s[i]>='A'&&s[i]<='Z'){
				if(!tong[s[i]]){
					ch--,tong[s[i]]++;
				}
				else{
					f=0;
				}
			}
			for(int j=0;j<=min(qm,ch);j++){
				dp1[i]=(dp1[i]+f*c[ch][j]%mod*c[qm][j]%mod*fac[j]%mod*c_26[qm-j]%mod)%mod;
			}
			if(s[i]>='A'&&s[i]<='Z'){
				dp2[i]=dp2[i-1],dp3[i]=dp2[i-1];
			}
			else{
				dp2[i]=dp1[i-1],dp3[i]=dp3[i-1];
			}
		}
	} 
	cout<<dp3[n];
	return 0;
}

```

---

## 作者：Ybll_ (赞：4)

[前置芝士——杨辉三角](https://baike.baidu.com/item/%E6%9D%A8%E8%BE%89%E4%B8%89%E8%A7%92/215098)
# 题意：
定义形如 `DDoS` 的序列为类 `DDoS` 序列，其中 `DD` 表示两个**相同**的**任意大写字母**，`o` 表示**任意小写字母**，`S` 表示**任意大写字母**。

给你一个字符串，里面有若干个问号，求有多少种将**问号**替换成**字母**使该字符串的**子串**中**不会有** `DDoS` 序列。
# 思路：
用**杨辉三角**预处理进行优化，然后对于第 $i$ 个点，当前已有 $b$ 个问号，还有 $a$ 个大写字母没用过时，它所造成的贡献为：

$$\sum_{j = 0}^{\min(a,b)} C_b^j \cdot A_a^j \cdot26^{b-j}$$

**重要的事情说三遍，记得取模！！！记得取模！！！记得取模！！！**
# 代码：
```cpp
#include<bits/stdc++.h>
#define mod 998244353
#define int long long
#define N 300005
using namespace std;
int A[N][27],C[N][27],p[N],f[N],g[N],h[N],pre[N];
map<char,bool>mp;
signed main()
{
	g[0]=h[0]=f[0]=p[0]=pre[0]=1;
	for(int i=0;i<300004;i++)
	{
		C[i][0]=1;
		A[i][0]=1;
		pre[i+1]=pre[i]*(i+1)%mod;
		p[i+1]=p[i]*26%mod;
	}
	for(int i=1;i<300005;i++)
	{
		for(int j=1;j<27;j++)
		{
			C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
			A[i][j]=(C[i][j]*pre[j])%mod;
		}
	}//以上为阶乘和杨辉三角的预处理 
	string s;
	cin>>s;
	int len=s.size();
	s=' '+s;
	for(int i=1,a=26,b=0,t=1;i<=len;i++)
	{
		if(s[i]=='?')
		{
			b++;//问号数+1 
			for(int j=0;j<=min(a,b);j++)
			{
				f[i]=(f[i]+t*C[b][j]*A[a][j]%mod*p[b-j]%mod)%mod;//计算贡献 
			}
			g[i]=(g[i-1]+f[i-1])*26%mod;//如果这个问号是大写
			h[i]=(h[i-1]+g[i-1])*26%mod;//如果这个问号是小写
		}
		else
		{
			if(s[i]>='A'&&s[i]<='Z')
			{
				if(mp[s[i]])t=0;//已经出现形如DD的字串了 
				else
				{
					mp[s[i]]=1;
					a--;//字母数-1 
				}
			}
			for(int j=0;j<=min(a,b);j++)
			{
				f[i]=(f[i]+t*C[b][j]*A[a][j]%mod*p[b-j]%mod)%mod;//计算贡献 
			}
			if(s[i]>='A'&&s[i]<='Z')h[i]=g[i]=g[i-1];//这个字符是大写
			else//这个字符是小写
			{
				g[i]=f[i-1];
				h[i]=h[i-1];
			}
		}
	}
	cout<<h[len];
	return 0;
}
```

---

## 作者：player_1_Z (赞：2)

### 理解题目
[atcoder 原题](https://atcoder.jp/contests/abc301/tasks/abc301_f)

### 思路
我们拆解一下条件，发现有以下三点：
1. 第一、二个字符为相同大写英文字母。
2. 第三个字符为小写英文字母。
3. 第四个字符为小写英文字母。

其中只有第一个条件不易满足，于是我们可以根据第一个条件分成三种情况：
1. 字符串中没有两个相同的大写字母。
2. 字符串中有两个相同的大写字母并且后面没有小写字母。
3. 字符串中有两个相同的大写字母并且后面没有大写字母。

计算方式为：
$$
  \sum_{j=0}^{\min(a,b)} C^j_b  \cdot A^j_a \cdot 26^{b-j}
$$
其中 $A$，$C$ 可以用[杨辉三角](https://blog.csdn.net/leadera_/article/details/128767788)预处理，$b$ 为问号数量，$a$ 为在不存在重复大写字母的情况下当前可用的大写字母数量。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const long long mod=998244353;
long long C[300005][27],p[300005],f[300005],pre[300005];
long long g[300005],h[300005],a=26,b=0,t=1,A[300005][27];
string s;
map<char,bool>mp;
int main(){
	cin>>s;
	long long len=s.size();
	s=' '+s;
	g[0]=h[0]=f[0]=p[0]=pre[0]=1;
	for(long long i=1;i<=300001;i++){
		C[i][0]=1;//C i j 
		A[i][0]=1;//A i j 
		for(long long j=1;j<=26;j++){//用杨辉三角求C i j和A i j 
			C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
			A[i][j]=(C[i][j]*pre[j])%mod;
		}
		pre[i+1]=pre[i]*(i+1)%mod;//阶乘 
		p[i+1]=p[i]*26%mod;//26的i次方
	}
	for(long long i=1;i<=300001;i++)
	for(long long i=1;i<=len;i++){
		if(s[i]=='?'){
			b++;//问号数 
			for(long long j=0;j<=min(a,b);j++)
				f[i]=(f[i]+t*C[b][j]*A[a][j]%mod*p[b-j]%mod)%mod;//前面没有两个相同的大写字母 
			g[i]=(g[i-1]+f[i-1])*26%mod;//i为小写，后面没有大写 
			h[i]=(h[i-1]+g[i-1])*26%mod;//i为大写，后面没有小写
		}
		else{
			if(s[i]>='A'&&s[i]<='Z'){
				if(mp[s[i]]) t=0;//前面有相同的大写字母，所以存在两个相同的大写字母
				else{//这是一个新的大写字母，所以可用大写字母数少了一个 
					mp[s[i]]=1;
					a--;
				}
			}
			for(long long j=0;j<=min(a,b);j++)//计算数量 
				f[i]=(f[i]+t*C[b][j]*A[a][j]%mod*p[b-j]%mod)%mod;
			if(s[i]>='A'&&s[i]<='Z')h[i]=g[i]=g[i-1];
			else g[i]=f[i-1],h[i]=h[i-1];
		}
	}
	cout<<h[len];//h包含了f和g所以更全面 
	return 0;
}
```

---

## 作者：spire001 (赞：2)

## AT_abc301_f 题解
看到同学写的这题题解，说是好题，就过来看看，一看就是一上午。

详细的说一下我的想法。

一看这限制条件这么强又看到 $3\times 10^5$，立刻想到了 $O(n)$ 乘上分类讨论大常数这种复杂度。

题目中给出的字符串那么短，那就直接每个阶段设立状态，$0$ 状态表示空串或全是小写字母的串，$1$ 状态表示不存在重复的大写字母，$2$ 状态表示有两个重复的字母，而且这后面没有小写字母，$3$ 状态就有两个重复的大写字母以及一个小写字母，且不存在 `DDos` 子序列。

做一个计数 dp，$dp_{c,i}$ 表示确定了 $i$ 个字符后字符串是情况 $c$ 的方案数。
你会发现一些情况不好写，那就是给定大写字母和问号拿大写字母的时候，你不知道前面有没有拿一个大写字母，你就不知道是情况 $1$ 还是情况 $2$。

第一想法是状态压缩，$26$ 个大写字母有没有拿过，进一步发现只关心有哪些字母拿过，那就加一维状态，表示拿过多少不同的字母。

然后写起来发现大多数情况都可以写，唯独一种情况，给定你大写字母的时候怎么办，你不知道你手头拿的字母里面是否包含这个大写字母。

应该有两种想法值得考虑，第一是你发现这种想法不太好，其实你可以直接枚举第一个重复出现的大写字母，~~于是你舍弃了你刚刚的想法~~。

另一种则是继续挖掘性质，你发现给定的大写字符数量是已知的，你知道手头的有些字符是给定的，那剩下的拿的是什么？前面已经发现了，对于从 $1$ 状态到 $2$ 状态，是哪一个字符并不重要，也就是说方案数是相等的，以概率的角度讲就是拿不是给定的大写字母的概率模型是一个古典概型，这种情况下手头的字母是否包含当前字母的方案数都是可知的。

然后就可以做了，我还是选择了看起来讨论更多的做法。

### 状态方程转移

为了叙述方便，将拿完字母后状态不变的叫继承，否则叫递推。

$0$ 状态拿小写字母时为继承，拿大写字母时递推到 $1$ 状态。

$1$ 状态在拿小写字母时为继承，拿大写字母时需根据字母数量分别计算递推与继承的数量。

$2$ 状态在拿大写字母时为继承，拿小写字母时全部递推到 $3$ 状态。

$3$ 状态只能拿小写字母，此时为继承。

对于给定的大写字符，手头有 $x$ 种大写字符，已经给定过 $y$ 种大写字符，那么拿过这次给定的字符的概率是：
$$
1-\prod_{i=27-x}^{26-y}\frac{i-1}{i}=\frac{x-y}{26-y}
$$

按照这个比例递推就可以了。

### 代码
```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cassert>
#include <numeric>

using namespace std;

typedef long long LL;
constexpr int mod = 998244353;
constexpr int N = 300010;
char a[N];
int n;

inline LL quick_pow(LL base, LL ind)
{
  LL res = 1;
  base %= mod;
  for (; ind; ind >>= 1)
  {
    if (ind & 1ll)
    {
      res = res * base % mod;
    }
    base = base * base % mod;
  }
  return res;
}
LL dp[4][27][N]; // dp[i][j][p] case i, j alpha, len p
int box[27], sum;

// constexpr int lim = 4 * 26 * N / 1048576;

/*
case 0: nothing
case 1: A | B | C | AB | ABCXFG...
case 2: AA
case 3: AAa
*/

inline LL _div(LL x, LL y) { return x * quick_pow(y, mod - 2) % mod; }

void print(int x)
{
  fprintf(stderr, "dp[0][0][%d] = %lld\n", x, dp[0][0][x]);

  for (int j = 1; j <= 26; j++)
    for (int i = 1; i != 4; i++)
    {
      fprintf(stderr, "dp[%d][%d][%d] = %lld\n", i, j, x, dp[i][j][x]);
      // assert(dp[i][j][x] >= 0);
    }

  return;
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  cin >> (a + 1);
  n = strlen(a + 1);

  dp[0][0][0] = 1;

  // print(0);

  for (int i = 1; i <= n; i++)
  {
    if (a[i] == '?')
    {
      dp[0][0][i] = dp[0][0][i - 1] * 26 % mod; // case 0
      dp[1][1][i] = dp[0][0][i - 1] * 26 % mod; // case 0
      for (int j = 1; j <= 26; j++) // case upper
      {
        dp[1][j][i] = (dp[1][j][i] + // solve1
                       dp[1][j - 1][i - 1] * (27 - j) % mod) %
                      mod;
        dp[2][j][i] = (dp[2][j][i] + // solve2
                       dp[1][j][i - 1] * j % mod +
                       dp[2][j][i - 1] * j % mod +
                       dp[2][j - 1][i - 1] * (27 - j) % mod) %
                      mod;
      }
      for (int j = 1; j <= 26; j++) // case lower
      {
        dp[1][j][i] = (dp[1][j][i] + // solve1
                       dp[1][j][i - 1] * 26) %
                      mod;
        dp[3][j][i] = (dp[3][j][i] + // solve 3
                       dp[2][j][i - 1] * 26 % mod +
                       dp[3][j][i - 1] * 26 % mod) %
                      mod;
      }
    }
    else
    {
      if (islower(a[i])) // 小写字母没有限制
      {
        dp[0][0][i] = dp[0][0][i - 1];
        for (int j = 1; j <= 26; j++)
        {
          dp[1][j][i] = dp[1][j][i - 1];
          dp[3][j][i] = (dp[2][j][i - 1] + dp[3][j][i - 1]) % mod;
        }
      }
      else
      {
        if (box[a[i] - 'A'])
        {
          assert(dp[0][0][i - 1] == 0);
          for (int j = 1; j <= 26; j++)
            dp[2][j][i] = (dp[1][j][i - 1] + dp[2][j][i - 1]) % mod;
        }
        else
        {
          dp[1][1][i] = dp[0][0][i - 1];
          for (int j = 1; j <= 26; j++)
          {
            dp[2][j][i] = (dp[2][j][i] + dp[1][j][i - 1] * _div(j - sum, 26 - sum)) % mod;    // 以前拿过 a[i]
            dp[2][j][i] = (dp[2][j][i] + dp[2][j][i - 1] * _div(j - sum, 26 - sum)) % mod;    // 以前拿过 a[i]
            dp[2][j][i] = (dp[2][j][i] + dp[2][j - 1][i - 1] * _div(27 - j, 26 - sum)) % mod; // 以前没拿过 a[i]
            dp[1][j][i] = (dp[1][j][i] + dp[1][j - 1][i - 1] * _div(27 - j, 26 - sum)) % mod; // 以前没拿过 a[i]
          }
        }
        sum += !box[a[i] - 'A'];
        box[a[i] - 'A'] = 1;
      }
    }
  }

  LL ans{ 0 };

  for (int i = 0; i != 4; i++)
    for (int j = 0; j <= 26; j++)
      ans = (ans + dp[i][j][n]) % mod;

  cout << ans << endl;

  return 0;
}

/*
begin: 2024年8月8日09:21:59
debug: 2024年8月8日10:25:59
finish: 2024年8月8日14:00:51
*/
```

---

## 作者：ilibilib (赞：2)

### 前言：

长教训了：

1. 不要老是倍增自己代码。
2. 不勤取模真会溢出。

### 解析：

DFA 好题（大概？），可以分为一下状态：

- 0-26 状态分别表示存在 0-26 中大写字母，且不存在重复大写字母。
- 27 存在重复大写字母，后不存在小写字母。
- 28 存在重复大写字母，且后存在小写字母。
- 29 ，存在 DDOS，即不合法状态，不计。

#### **先考虑没有限制的情况（即是 `?` 的情况）：**

**对于状态 $i\in[0,26]$：**

存在 $i$ 个大写字母使重复，$i\to 27$。

存在 $26-i$ 个大写字母使出现新的大写字母，$i\to i+1$。

存在 $26$ 个小写字母，完全不影响状态，$i\to i$。

**对于状态 $i=27$：**

存在 $26$ 个大写字母，完全不影响状态，$i\to i$。

存在 $26$ 个小写字母，使后接小写字母，$i\to 28$。

**对于状态 $i=28$：**

存在 $26$ 个大写字母，使 DDOS 成型，$i\to 29$。

存在 $26$ 个小写字母，完全不影响状态，$i\to i$。

**对于状态 $i=29$：**

不用考虑。

要是给出一个长度为 $n$ 的 `?` 串，$n\le 10^{18}$，那就是个很无聊的矩阵快速幂了。

#### 可是还有限制（即给出了确定的字符）：

**对于字符 $c$ 为小写字母：**

 按照上面规则推就行了，就是只考虑一个小写字母的情况。

**对于字符 $c$ 为大写字母**：

**若 $c$ 曾确定给出过**：
则一定存在重复字母了，对于状态 $i\in[0,26]$ 全推到 $27$，其他状态按照上面规则推就行了。

**若 $c$ 不曾确定给出过：**

对于 $i\notin[0,26]$ 照常推没影响，但是对于 $i\in[0,26]$ 就要仔细想想了。

首先可以确定地是一定也存在两种递推关系：$i\to 27$ 和 $i\to i+1$。但具体多少这样推，多少那样推呢？

我们发现，若曾给过 $cnt$ 个大写字母，剩余 $26-cnt$ 个大写字母就是完全不受限制的，所以都是**等价**的，也就是说**出现的概率相等**，那么对于状态 $i$，$c$ 字符出现的概率就是 $\frac{i-cnt}{26-cnt}$，它们将使大写字母重复，也就是递推到状态 $27$，剩下的 $\frac{26-i}{26-cnt}$ 就将使 $i\to i+1$。分数乘法用逆元刻画。



然后我们就明确了所有状态以及它们的转换，按照指定的字符串递推就行了，复杂度为 $O(n\left|\Sigma \right|)$。



然后就是调试的时候，可以输出一下所有状态的总和看看有没有多，有没有少，免得自己手抖多写了些什么多出或少了状态（当然要把状态 $29$ 算进去，但我的代码里没写）。

### code：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353,N=3e5+10;
//0~26 状态 存在 0~26 个大写字母，不存在存在两个的
//27 存在存在两个大写字母的
//28 存在存在两个大写字母的，且存在小写字母 
//29 状态，存在DDOS
int dp[N][30];char s[N];bool f[120];
inline int ksm(int a,int b)
{
	int c=1;
	while(b)
	{
		if(b&1) c=(c*a)%mod;
		a=(a*a)%mod;
		b>>=1;
	}
	return c;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int n,cnt=0,ans=0;
	cin>>s+1;
	n=strlen(s+1);
	dp[1][0]=1;
	for(int i=1;i<=n;++i)
	{
		if(s[i]=='?')
		{
			for(int j=0;j<=26;++j)
			{
				dp[i+1][j]=(dp[i+1][j]+dp[i][j]*26)%mod;
				dp[i+1][j+1]=(dp[i+1][j+1]+(26-j)*dp[i][j])%mod;
				dp[i+1][27]=(dp[i+1][27]+dp[i][j]*j)%mod;
			}
			dp[i+1][27]=(dp[i+1][27]+dp[i][27]*26)%mod;
			dp[i+1][28]=(dp[i+1][28]+dp[i][27]*26+dp[i][28]*26)%mod;
		}
		else if(s[i]>='a'&&s[i]<='z')
		{
			for(int j=0;j<=26;++j) dp[i+1][j]=(dp[i+1][j]+dp[i][j])%mod;
			dp[i+1][28]=(dp[i+1][28]+dp[i][27]+dp[i][28])%mod;
		}
		else if(s[i]>='A'&&s[i]<='Z')
		{
			if(f[s[i]])
			{
				for(int j=0;j<=26;++j) dp[i+1][27]=(dp[i+1][27]+dp[i][j])%mod;
				dp[i+1][27]=(dp[i+1][27]+dp[i][27])%mod;
			}
			else
			{
				for(int j=cnt;j<=26;++j)
				{
					dp[i+1][27]=(dp[i+1][27]+((dp[i][j]*(((j-cnt)*ksm(26-cnt,mod-2))%mod))%mod))%mod;
					dp[i+1][j+1]=(dp[i+1][j+1]+((dp[i][j]*(((26-j)*ksm(26-cnt,mod-2))%mod))%mod))%mod;
				}
				dp[i+1][27]=(dp[i+1][27]+dp[i][27])%mod;
				f[s[i]]=true;
				++cnt;
			}
		}
	}
	for(int i=0;i<=28;++i) ans=(ans+dp[n+1][i])%mod;
	cout<<ans%mod;
	return 0;
} 
```

---

## 作者：六楼溜刘 (赞：2)

## 题意
- 定义形如 `DDoS` 的序列为类 DDoS 序列，其中 `DD` 表示两个相同的任意大写字母，`o` 表示任意小写字母，`S` 表示任意大写字母。
- 给定一个由大小写字母和 `?` 组成的序列 $S$，问有多少种将 `?` 替换为大小写字母的方案可以使 $S$ 不含有任何一个类 DDoS 子序列。
- $4 \le \left|S\right| \le 3 \times 10^5$

## 题解

### 闲扯
~~看得出来高桥君真的被攻击怕了。~~

其实这篇题解就是 Atcoder 上的[这篇题解](https://atcoder.jp/contests/abc301/editorial/6346)，但是侧重于讲这个方法是如何得到的。

### 分析

首先我们发现一个类 DDoS 序列可以被那个小写字母分成两部分，一部分是单个大写字母，另一部分是成对的大写字母。而我们只要保证每个**后面有大写字母的小写字母前面没有成对的大写字母**就可以得到一个合法的序列（或者说整个序列只有大写/小写字母，以及所有小写字母都在大写字母后面）。但这样可能会将一个序列计算多次。假如转化后的序列长这样：

```
ABCaDEFbGHIcde
```
比如这个字符串中，`a` 和 `b` 都是满足条件的小写字母。再推广一下，我们发现**最后一个满足条件的小写字母前面所有小写字母均满足条件。**

所以我们可以修改条件为**最后一个后面有大写字母的小写字母前面安没有成对的大写字母**，这样就不重不漏了。

考虑如何实现，我们可以把条件分成三部分解决：**最后一个**、**前面没有成对的大写字母**、**小写字母**。

### 前面没有成对的大写字母

对于这个条件，容易发现只需要预处理所有前缀的方案数即可，我们可以把一个前缀分为两种情况讨论：

- 已经有两个重复的大写字母，显然只有 $0$ 种方案，有趣的是所有包含这样的前缀的前缀都为 $0$，遇到了可以直接 `break` 掉。
- 没有重复的大写字母，那么就可以把 `?` 变为任意小写字母与不重复的大写字母。设某个前缀中有 $q$ 个 `?`，出现过 $m$ 个不同的大写字母，那么可以用以下式子计算方案数：

$$\sum\limits_{i=0}^{\min(q,26-m)}26^{q-i}\cdot\binom{q}{i}\cdot \binom{26-m}{i}\cdot i!$$

这个式子非常好理解，`?` 里最多选 $\min(q,26-m)$ 个变为大写字母，而剩下的变为任意小写字母，再乘以具体选哪些 `?`，具体填哪些大写字母的方案数，再乘以大写字母的排列顺序即可。

这样，预处理的最坏情况就是全为 `?`，复杂度为 $O(26n\log n)$（这个表达方法不太严谨），需要预处理阶乘、逆元、阶乘的逆元，以及用快速幂求幂次方，由于带小常数，不可能跑满，再加点小剪枝（指第一种情况），看起来过不了其实跑得还挺快的。

### 最后一个

对于最后一个小写字母的要求，我们发现非常难处理，试着反过来计算符合条件的小写字母紧挨着的后缀的方案数。

能出现在这样的小写字母后面的后缀一定是由一段连续的大写字母（至少有一个）和一段连续的小写字母（可为空）组成的，而这一段小写字母一定要出现在大写字母后面（不然这个后缀前面的小写字母就不满足**最后**了），我们考虑 DP。

设 $dp_{i,0}$ 表示以 $i$ 开头的后缀全为小写的方案数，$dp_{i,1}$ 表示以 $i$ 开头的后缀由**一段大写字母**加**一段小写字母**组成的方案数。易得转移方程（伪代码）：

```
if S[i] is uppercase
	dp[i][0] <- 0
	dp[i][1] <- dp[i+1][0] + dp[i+1][1]
else if s[i] is lowercase
	dp[i][1] <- 0
	dp[i][0] <- dp[i+1][0]
else if s[i] is ?
	dp[i][1] <- (dp[i+1][0] + dp[i+1][1]) * 26
	dp[i][0] <- dp[i+1][0] * 26
```

这个转移我就不解释了，根据状态的定义很好理解。

另外根据定义容易得初值为 $dp_{n+1,0}=1$。

### 小写字母

终于收尾了，我们只要枚举一个位置是否为小写字母（或 `?`），然后将它前缀（不含它）的方案数和后缀（同样不含它自己）的方案数乘起来相加即可（如果是 `?` 还要额外乘以 $26$）。

此外，我们还要统计整个序列只有大写/小写字母，或者所有小写字母都在大写字母后面的情况，我们发现这几种情况加起来恰好是 $dp_{1,0}+dp_{1,1}$（根据 $dp$ 的定义理解）。

### 总结

预处理阶乘、逆元的复杂度为 $O(n)$，处理前缀的复杂度为 $O(26n\log n)$（刚刚解释过为什么不会 TLE），处理后缀复杂度 $O(n)$，可过，注意取模。

## code

```cpp
#include<bits/stdc++.h>
#define mem(a,b) memset(a,b,sizeof(a))
#define forup(i,s,e) for(register int i=(s);i<=(e);i++)
#define fordown(i,s,e) for(register int i=(s);i>=(e);i--)
using namespace std;
#define gc getchar()
inline int read(){//快读
    int x=0,f=1;char c;
    while(!isdigit(c=gc)) if(c=='-') f=-1;
    while(isdigit(c)){x=(x<<3)+(x<<1)+(c^48);c=gc;}
    return x*f;
}
#undef gc
const int N=3e5+5,inf=0x3f3f3f3f,mod=998244353;
int n,dp[N][2],pre[N],ans;//pre 是前缀
char s[N];
int cntup[26],cnt,cntq;
//统计每个大写字母出现次数，出现了多少个不同的大写字母，？ 的个数
int fact[N],inv[N],finv[N];
//阶乘，逆元，阶乘的逆元（或者说逆元的阶乘）
int C(int n,int m){//组合数
	if(n<m) return 0;
	return 1ll*fact[n]*finv[m]%mod*finv[n-m]%mod;
}
int ksm(int a,int b){//快速幂
	int c=1;
	while(b){
		if(b&1) c=1ll*c*a%mod;
		a=1ll*a*a%mod;
		b>>=1;
	}
	return c;
}
int calc(int m,int q){//前缀的转移
	m=26-m;
	if(m<0) return 0;
	int res=0;
	forup(i,0,min(q,m)){
		res=(res+1ll*ksm(26,q-i)*C(q,i)%mod*C(m,i)%mod*fact[i]%mod)%mod;
	}
	return res;
}
signed main(){
	scanf(" %s",s+1);
	n=strlen(s+1);
	fact[0]=fact[1]=inv[1]=finv[0]=finv[1]=1;
	forup(i,2,max(n,26)){
   //注意预处理到 max(n,26)，因为计算时 q 最大是 n，但还要用到 26
		fact[i]=1ll*fact[i-1]*i%mod;
		inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
		finv[i]=1ll*finv[i-1]*inv[i]%mod;
	}
	dp[n+1][0]=1;
	fordown(i,n,1){
		if(islower(s[i])){
        //islower 意思是这个字符是不是小写字母，isupper 同理
			dp[i][0]=dp[i+1][0];
		}else if(isupper(s[i])){
			dp[i][1]=(dp[i+1][0]+dp[i+1][1])%mod;
		}else{
			dp[i][0]=26ll*dp[i+1][0]%mod;
			dp[i][1]=26ll*(dp[i+1][0]+dp[i+1][1])%mod;
		}
	}
	ans=(dp[1][0]+dp[1][1])%mod;
	pre[0]=1;
	forup(i,1,n){
		if(islower(s[i])){
			pre[i]=pre[i-1];
		}else if(isupper(s[i])){
			int val=s[i]-'A';	
			cntup[val]++;
			if(cntup[val]>=2){
				pre[i]=0;
			}else{
				cnt++; 
				pre[i]=calc(cnt,cntq);
			}
		}else{
			cntq++;
			pre[i]=calc(cnt,cntq);
		}
		if(pre[i]==0) break;//小剪枝，避免无用操作
	}
	forup(i,1,n){
		if(islower(s[i])){
			ans=(ans+1ll*dp[i+1][1]*pre[i-1]%mod)%mod;
		}else if(s[i]=='?'){
			ans=(ans+26ll*dp[i+1][1]%mod*pre[i-1]%mod)%mod;
		}
	}
	printf("%d",ans);
}
```


---

## 作者：Otue (赞：1)

定义 $fa_i$ 表示前 $i$ 个不出现子序列 `DD`。

定义 $fb_i$ 表示前 $i$ 个不出现子序列 `DDo`。

定义 $fc_i$ 表示前 $i$ 个不出现子序列 `DDoS`。

转移 $fb$：
* 若 $S_i$ 为大写字母，那么 $S_i$ 不能参与组成子序列 `DDo`，转移为 $fb_i=fb_{i-1}$。
* 若 $S_i$ 为小写字母，那么 $S_i$ 一定会参与组成子序列 `DDo` 的最后一个小写字母。那么此时一定要求前 $i-1$ 个不能出现 `DD` 形式，转移为 $fb_i=fa_{i-1}$。
* 否则 $S_i$ 为问号，那么 $fb_i=fb_{i-1}\times 26+fa_{i-1}\times 26$。

转移 $fc$ 和 $fb$ 同理。

转移 $fa$：如果非问号位置已经存在两个相同的大写字母，则 $fa_i=0$。否则，考虑问号位置如何填写大写字母即可。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define PII pair<int, int>
#define _for(i, a, b) for (int i = (a); i <= (b); i++)
#define _pfor(i, a, b) for (int i = (a); i >= (b); i--)


const int N = 3e5 + 5, mod = 998244353;

int n, fa[N], fb[N], fc[N], vis[27], flg, cnt, fac[N], invfac[N], pw2[N];
char a[N];

int qpow(int a, int k, int p) {
  int res = 1;
  while (k) {
    if (k & 1) res = res * a % p;
    a = a * a % p;
    k >>= 1;
  }
  return res;
} 

void init() {
  fac[0] = invfac[0] = pw2[0] = 1;
  _for(i, 1, N - 5) fac[i] = fac[i - 1] * i % mod;
  _for(i, 1, N - 5) pw2[i] = pw2[i - 1] * 26 % mod;
  _for(i, 1, N - 5) invfac[i] = invfac[i - 1] * qpow(i, mod - 2, mod) % mod;
}

int get_c(int n, int m) {
  if (n < m) return 0;
  return fac[n] * invfac[n - m] % mod * invfac[m] % mod;
}

signed main() {
  init();
  cin >> (a + 1); n = strlen(a + 1);
  fa[0] = fb[0] = fc[0] = 1;
  _for(i, 1, n) {
    if (a[i] != '?') {
      if (a[i] >= 'A' && a[i] <= 'Z') {
        vis[a[i] - 'A']++;
        if (vis[a[i] - 'A'] >= 2) flg = 1;
      }
    }
    if (a[i] == '?') cnt++;
    int tmp = 0;
    _for(j, 0, 25) if (vis[j] == 0) tmp++;
    _for(j, 0, min(cnt, tmp)) {
      fa[i] = (fa[i] + get_c(tmp, j) * get_c(cnt, j) % mod * fac[j] % mod * pw2[cnt - j] % mod) % mod;
    }
    if (flg == 1) fa[i] = 0;
    if (a[i] >= 'A' && a[i] <= 'Z') fb[i] = (fb[i] + fb[i - 1]) % mod;
    else if (a[i] >= 'a' && a[i] <= 'z') fb[i] = (fb[i] + fa[i - 1]) % mod;
    else fb[i] = (fb[i] + fb[i - 1] * 26 % mod + fa[i - 1] * 26 % mod) % mod;
    if (a[i] >= 'A' && a[i] <= 'Z') fc[i] = (fc[i] + fb[i - 1]) % mod;
    else if (a[i] >= 'a' && a[i] <= 'z') fc[i] = (fc[i] + fc[i - 1]) % mod;
    else fc[i] = (fc[i] + fb[i - 1] * 26 % mod + fc[i - 1] * 26 % mod) % mod;
  }
  cout << fc[n] << endl;
}
```

---

## 作者：Starrykiller (赞：1)

[官方题解](https://atcoder.jp/contests/abc301/editorial/6365)的解释。

有时候，将计数化为计算概率不失为一种好的策略。类似的题目：ABC200F，AGC030D。

考虑状态设计。对于 DDoS，我们可以将它划分成四个阶段：

1. 未出现过大写字母；
1. 出现了一个大写字母（形如 `D`）；
1. 出现了形如 `DD` 的子序列；
1. 出现了形如 `DDo` 的子序列。

我们只需要求这四种情况的概率乘上 $52^q$。

以上均不包含下一个阶段，例如 3. 中不包括 4. 的情况，4. 不包括 DDoS 的状态。

你会发现如果只设计 $f(i,0\sim 3)$ 转移不了；但是将 $2^{26}$ 种字母出现的情况压进状态里又无法接受。神仙的想法就是，记录**一共出现了多少种大写字母**（它们都只出现了一次）。

不妨设 $S(1,i-1)$ 中出现了 $tot$ 种大写字母。设 $T$ 为我们将 `?` 填充后得到的字符串，设 $T(1,i-1)$ 中出现了 $k$ 种大写字母，我们分类讨论：

- $S(i)$ 在 $S(1,i-1)$ 中出现过。

	那么只需要全部转移到状态 3. 即可。
    
- $S(i)$ 在 $S(1,i-1)$ 中未出现过。
	
    此时 $T(1,i-1)$ 中含有 $S(i)$，当且仅当有 `?` 是 $S(i)$。`?` 的个数是 $k-tot$，单个 `?` 是 $S(i)$ 的概率是 $\dfrac{1}{26-tot	}$。
	
设

- $f(i,0)$：未出现大写字母；
- $f(i,k)$（$k\in [1,26]$）：出现了 $k$ 种大写字母（它们都只出现了一次）；
- $f(i,27)$：存在 `DD`；
- $f(i,28)$：存在 `DDo`，且后面没有 `S`。

为考虑到 $1\sim i$ 的对应状态的概率。转移：


- $S(i)$ 是小写字母
    - $f(i,k)\gets f(i-1,k) \quad \text{where } k\in [0,26]$
    - $f(i,28)\gets f(i-1,28)+f(i-1,27)$

- $S(i)$ 是大写字母，且未在 $S(1,i-1)$ 中出现过

    - $\displaystyle f(i,k+1)\gets f(i-1,k)\cdot \left(1-\frac{k-tot}{26-tot}\right) \quad\text{where }k\in [tot,25]$
    - $\displaystyle f(i,27)\gets f(i-1,k)\cdot \frac{k-tot}{26-tot}\quad \text{where }k\in [y,26]$

- $S(i)$ 是大写字母，且在 $S(1,i-1)$ 中出现过
    - $\displaystyle f(i,27)\gets f(i-1,27)+ \sum_{k=1}^{26} f(i,k)$
    - $\displaystyle f(i,28)\gets f(i-1,28)$


- $S(i)$ 是 `?`
    - $\displaystyle f(i,0)\gets f(i-1,0)\cdot \frac{1}{2}$。（$50\%$ 的概率抽到小写字母）
    - $\displaystyle f(i,k)\gets f(i-1,k-1)\cdot \frac{26-k+1}{52}+f(i-1,k)\cdot \frac{1}{2} \quad \text{where } k\in [1,26]$
    - $\displaystyle f(i,27)\gets f(i-1,27)\cdot \frac{1}{2}+\sum_{i=1}^{26} f(i-1,k)\cdot \frac{k}{52}$
    - $\displaystyle f(i,28)\gets f(i-1,27)\cdot \frac{1}{2}+f(i-1,28)\cdot \frac{1}{2}$

时间复杂度 $\Theta(n|\Sigma|)$。[代码](https://atcoder.jp/contests/abc301/submissions/55470911)。

---

## 作者：JWRuixi (赞：1)

~~热知识：`islower` 和 `isupper` 返回值原来不是 `bool`~~

### 题意

定义形如 `DDoS` 的字符串为由两个相同的大写字母、一个小写字母和一个大写字母组成的字符串。给定有英文字母和 `?` 组成的字符串，求有多少种填 `?` 的方式使得所得字符串种没有形如 `DDoS` 的子序列。

$n \le 3 \times 10^5$。

### 分析

“两个相同的大写字母”这个限制条件较强，但“一个大写字母”这个限制较弱，所以不妨将字符串翻转一下，让后做没有 `SoDD` 子序列的字符串数。

合法串大致上有 $3$ 类：

1. 只有大写字母；
2. 小写字母全在大写字母后面；
3. 第一个 `So` 后面不存在相同的两个大写字母。

前两种是好解决的，直接设 $dp_{i,0/1}$ 表示前 $i$ 位，有没有出现小写字母，转移是 trivial 的。第三种可以从后往前算，显然只用考虑 `?` 的计数，且如果出现两个确定的相同大写字母就寄了。

我们设当前在第 $i$ 位，$[i+1,n]$ 中 `?` 的数量为 $q$，大写字母出现的集合为 $S$；我们不妨枚举有 $v$ 个 `?` 填大写字母，显然 $v \le 26 - |S|$，那剩下 $q - v$ 个就随便填小写字母，方案数 $26^{q - v}\dbinom{q}{v}(26 - |S|)^{\underline{v}}$。

复杂度 $\mathcal O(kn)$，其中 $k=\max(n,26)$。

### Code

提交记录：<https://atcoder.jp/contests/abc301/submissions/43498631>。

---

## 作者：ღꦿ࿐ (赞：1)

不需要 dp，$O(n|S|)$。

枚举出现的第一个 DD 的位置。并计算后面没有 oS 的方案数。

如果我们钦定 DD 后面的 D 出现在 $i$ 位置，我们只需要知道前面“?” 的个数 和 大写字母的个数，就可以算出。前面 不出现重复的大写字母，且出现过一个 和这个字母相同的字母的方案数。 

形如

$$
\sum \binom{cnt?}{i} \times (26-cntupper) ^{\underline {i}}\times26^{cnt?-i}
$$

$cnt?$ 表示“?” 个数，$cntupper$ 表示已经出现的大写字母种类数。

如果要钦定之前出现过某一种字符的话减去 没有出现过就行。

注意我们只区分这个“?” 代表的字母之前是否出现过，所以不用枚举字母，只需要知道前面出现过和没出现过的字母个数。

那么没有出现 oS 的怎么算呢？

一个字符串没有 oS 子序列那么它一定形如 $\texttt{SSSSS......ooooo}$，即一段前缀 S 和一段后缀 o。

又因为大写字母和小写字母的种类数是相同的，也就是说对于不同的分界点来说，可行的选择数是相同的，均为 $26^{cnt?}$ 种，所以只用考虑合法的分界点数，即 DD 后的最后一个 S 到第一个 O 之间的位置。

最后再加上整个串没有 DD 的方案数就行了。

[code](https://atcoder.jp/contests/abc301/submissions/42995669)


---

## 作者：EuphoricStar (赞：1)

考虑分类计数，讨论“没有 `DD`”、“有 `DD` 无 `o`”、“有 `DDo` 无 `S`”三种情况。

- 没有 `DD`，枚举有几种大写字母出现过；
- 剩下两种情况，考虑设 $f_{i,0/1}$ 分别表示两种情况的方案数。$f_{i,0}$ 可以从 $f_{i-1,0}$ 填大写字母转移，也可以枚举第一个出现两次的字母，然后枚举剩下出现了几个字母；$f_{i,1}$ 可以从 $f_{i-1,0}$ 和 $f_{i-1,1}$ 填小写字母转移。

时间复杂度 $O(26^2n)$，精细实现可过。

[code](https://atcoder.jp/contests/abc301/submissions/41433496)

---

## 作者：__Ship_ (赞：0)

#### 前提需要

1. 杨辉三角
2. 逆元

### [题目传送门](https://www.luogu.com.cn/problem/AT_abc301_f)

## 核心

对于第 $i$ 个点，当前已有 $b$ 个问号，还有 $a$ 个大写字母没用过时，它所造成的情况为：

$\sum_{j=0}^{\min(a,b)} 26^{j-i}\cdot \operatorname{C}_{j}^{b}\cdot \operatorname{A}_{j}^{b}$

## 思路 1 逆元

现在公式都已经推理出来了，就是看排列组合怎么写了。

我们能发现，我们每次进行排列组合都要去取模，且不能直接取模，且 $998244353$ 为一个**质数**，那不就可以用逆元了吗

```
#include<bits/stdc++.h>
const long long mod=998244353;
#define C(n,m) (pre[n]*inv[m]%mod*inv[n-m]%mod) 
#define A(n,m) (pre[n]*inv[n-m]%mod) 
using namespace std;

long long f[300005],pre[300005],itv[300005],inv[300005];
long long g[300005],h[300005],cl=26,b=0,t=1;
string s;//C为组合数，A代表排列，cl表示当前还能使用的字母，b代表当前有多少个？ 
long long powmod(long long a, long long b, long long p){
    long long ret = 1;
    a%=p;
    while(b){
        if(b&1)
            ret=(ret*a)%p;
        a=a*a%p;
        b>>=1;
    }
    return ret;
}

map<char,bool> mp;
int main(){

	cin>>s;
	long long lens=s.size();
	s=' '+s;
	g[0]=h[0]=f[0]=itv[0]=pre[0]=1;
	pre[1]=1;
	itv[1]=1*26;
	inv[0]=1; 
	for(long long i = 1 ; i < 300005 ; i++){//组合排列中的n
		itv[i+1]=itv[i]*26%mod;
		inv[i]=powmod(pre[i],mod-2,mod);//任意一个数的逆元 
		pre[i+1]=pre[i]*(i+1)%mod;//阶乘 
	}
	for(long long i = 1 ; i <= lens ; i++){
		if(s[i]=='?'){//问号的时候就是我们要考虑的情况 
			b++;//当前有多少个问号 
			g[i]=(g[i-1]+f[i-1])*26%mod;//i为小写，后面没有大写 
			h[i]=(h[i-1]+g[i-1])*26%mod;//i为大写，后面没有小写
			for(long long j = 0 ; j <= min(cl,b) ; j++){
				f[i]=(f[i]+t*C(b,j)*A(cl,j)%mod*itv[b-j]%mod)%mod;//公式套用 
			}
		}
		else{
			if(s[i]>='A'&&s[i]<='Z'){
				if(mp[s[i]]) t=0;//有两个相同的大写字母了，不能再用小写了,用小写的话后面再出一遍大写就废了 
				else{//这是一个新的大写字母，所以可用大写字母数少了一个 
					mp[s[i]]=1;
					cl--;//当前这个字母被榨干净了，再用就会出现DDoS 
				}
			}
			for(long long j = 0 ; j <= min(cl,b) ; j++){//计算数量 
				f[i]=(f[i]+t*C(b,j)*A(cl,j)%mod*itv[b-j]%mod)%mod;//公式套用 
			}
			if(s[i]>='A'&&s[i]<='Z'){
				h[i]=g[i]=g[i-1];
			}
			else{
				g[i]=f[i-1];
				h[i]=h[i-1];
			}
		}
	}
	cout<<h[lens];//h中考虑到了小写字母与大写字母，相当于答案 
	return 0;
}
```

## 思路 2 杨辉三角

有什么方法能不用逆元呢？除了逆元，那就还有杨辉三角，但杨辉三角只能求组合数，怎么办呢。

我们考虑到组合问题的本质：

$C_{n}^{m} = \frac{n!}{m!(n-m)!}$

我们发现这个式子是排列公式上多除以了一个 $m!$。

所以排列只需要在这基础上乘上排列组合中的 $m!$ 不就行了。

```cpp
#include<bits/stdc++.h>
using namespace std;
const long long mod=998244353;
long long C[300005][27],f[300005],pre[300005],itv[300005];
long long g[300005],h[300005],cl=26,b=0,t=1,A[300005][27];
string s;//C为组合数，A代表排列，cl表示当前还能使用的字母，b代表当前有多少个？ 

map<char,bool> mp;
int main(){

	cin>>s;
	long long lens=s.size();
	s=' '+s;
	g[0]=h[0]=f[0]=itv[0]=pre[0]=1;
	C[0][0]=1;
	A[0][0]=1;
	pre[1]=1;
	itv[1]=1*26;
	for(long long i = 1 ; i < 300005 ; i++){//组合排列中的n
		itv[i+1]=itv[i]*26%mod;
		C[i][0]=1; 
		A[i][0]=1;
		pre[i+1]=pre[i]*(i+1)%mod;//阶乘 
		for(long long j = 1 ; j < 27 ; j++){//组合排列中的m预处理操作，杨辉三角 
			C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod; 
			A[i][j]=(C[i][j]*pre[j])%mod;
		}
	}
	for(long long i = 1 ; i <= lens ; i++){
		if(s[i]=='?'){//问号的时候就是我们要考虑的情况 
			b++;//当前有多少个问号 
			g[i]=(g[i-1]+f[i-1])*26%mod;//i为小写，后面没有大写 
			h[i]=(h[i-1]+g[i-1])*26%mod;//i为大写，后面没有小写
			for(long long j = 0 ; j <= min(cl,b) ; j++){
				f[i]=(f[i]+t*C[b][j]*A[cl][j]%mod*itv[b-j]%mod)%mod;//公式套用 
			}
		}
		else{
			if(s[i]>='A'&&s[i]<='Z'){
				if(mp[s[i]]) t=0;//有两个相同的大写字母了，不能再用小写了,用小写的话后面再出一遍大写就废了 
				else{//这是一个新的大写字母，所以可用大写字母数少了一个 
					mp[s[i]]=1;
					cl--;//当前这个字母被榨干净了，再用就会出现DDoS 
				}
			}
			for(long long j = 0 ; j <= min(cl,b) ; j++){//计算数量 
				f[i]=(f[i]+t*C[b][j]*A[cl][j]%mod*itv[b-j]%mod)%mod;
			}
			if(s[i]>='A'&&s[i]<='Z'){
				h[i]=g[i]=g[i-1];
			}
			else{
				g[i]=f[i-1];
				h[i]=h[i-1];
			}
		}
	}
	cout<<h[lens];//h中考虑到了小写字母与大写字母，相当于答案 
	return 0;
}
```

---

