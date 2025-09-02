# Catching Cheaters

## 题目描述

You are given two strings $ A $ and $ B $ representing essays of two students who are suspected cheaters. For any two strings $ C $ , $ D $ we define their similarity score $ S(C,D) $ as $ 4\cdot LCS(C,D) - |C| - |D| $ , where $ LCS(C,D) $ denotes the length of the Longest Common Subsequence of strings $ C $ and $ D $ .

You believe that only some part of the essays could have been copied, therefore you're interested in their substrings.

Calculate the maximal similarity score over all pairs of substrings. More formally, output maximal $ S(C, D) $ over all pairs $ (C, D) $ , where $ C $ is some substring of $ A $ , and $ D $ is some substring of $ B $ .

If $ X $ is a string, $ |X| $ denotes its length.

A string $ a $ is a substring of a string $ b $ if $ a $ can be obtained from $ b $ by deletion of several (possibly, zero or all) characters from the beginning and several (possibly, zero or all) characters from the end.

A string $ a $ is a subsequence of a string $ b $ if $ a $ can be obtained from $ b $ by deletion of several (possibly, zero or all) characters.

Pay attention to the difference between the substring and subsequence, as they both appear in the problem statement.

You may wish to read the [Wikipedia page about the Longest Common Subsequence problem](https://en.wikipedia.org/wiki/Longest_common_subsequence_problem).

## 说明/提示

For the first case:

abb from the first string and abab from the second string have LCS equal to abb.

The result is $ S(abb, abab) = (4 \cdot |abb| $ ) - $ |abb| $ - $ |abab| $ = $ 4 \cdot 3 - 3 - 4 = 5 $ .

## 样例 #1

### 输入

```
4 5
abba
babab```

### 输出

```
5```

## 样例 #2

### 输入

```
8 10
bbbbabab
bbbabaaaaa```

### 输出

```
12```

## 样例 #3

### 输入

```
7 7
uiibwws
qhtkxcn```

### 输出

```
0```

# 题解

## 作者：AFOier (赞：8)

注意到LCS长一位对答案贡献为$4-2=2$，子串长一位对答案贡献的$-1$

于是直接DP即可

设$dp[i][j]$表示考虑到$A$中以第$i$位为最后一位，$B$中以第$j$位为最后一位的子串的最大相似度

易得转移方程：

$$dp[i][j]=max(dp[i-1][j],dp[i][j-1])-1$$

$$dp[i][j]=max(dp[i][j],dp[i-1][j-1]+2),A[i]=B[j]$$

```
#include <bits/stdc++.h>
#define ll long long
using namespace std;
int n, m, dp[5011][5011], ans;
char a[5011], b[5011];
void solve() {
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++) cin >> a[i];
    for(int i = 1; i <= m; i++) cin >> b[i];
    for(int i = 1; i <= n; i++)
    for(int j = 1; j <= m; j++) {
        if(a[i] == b[j]) dp[i][j] = dp[i-1][j-1] + 2;
        dp[i][j] = max(dp[i][j], dp[i-1][j] - 1);
        dp[i][j] = max(dp[i][j], dp[i][j-1] - 1);
        ans = max(ans, dp[i][j]);
    }
    cout << ans << endl;
}
int main() {
    int T = 1;
    while(T--) solve();
    return 0;
}
```

---

## 作者：Eddie08012025 (赞：6)

## 本篇题解主要讲解一下状态转移方程

这题一看就是一道 DP 题。

$dp_{i,j}$ 代表以 $s_i,t_j$ 结尾的最大相似度。

首先外两层循环枚举 $i,j$，这时，会出现两种可能：

① $s_{1_i}=t_j$： 最长公共子序列的长度会 $+1$，会产生 $4$ 的相似度，而两个字串的长度也 $+1$，所以总共会产生 $4-1-1=2$ 的相似度。

② $s_i\ne t_j$：$dp_{i,j}$ 的结果会与 $dp_{i-1,j}$， $dp_{i,j-1}$ 有关系，$s$ 或 $t$ 的字串长度 $+1$，所以会产生 $-1$ 的相似度，由于 $dp_{i-1,j} -1$ 和 $dp_{i,j-1} -1$ 会产生负数，所以还要和 $0$ 取 $\max$。

得出状态转移方程：

$$dp_{i,j}=dp_{i-1,j-1}+2(s_i=t_j)$$

$$dp_{i,j}=\max(0,\max(dp_{i-1,j}-1,dp_{i,j-1}-1))    (s_i\ne t_j)$$

注：输出结果不是 $dp_{n,n}$，而是取 $\max_{i=1}^{n}\max_{j=1}^{n} dp_{i,j}$。

相信你已经知道这题怎么做了，不过我还是放出代码方便大家~~抄袭~~借鉴。
```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,dp[5001][5001],maxn;//dp[i][j]代表s前i个字母与t前j个字母的最大相似度 
char s[5001],t[5001];
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>a>>b;
	for(int i=1;i<=a;i++)cin>>s[i];
	for(int i=1;i<=b;i++)cin>>t[i];
	//↑以上是输入部分↑ 
	for(int i=1;i<=a;i++){//枚举i和j 
		for(int j=1;j<=b;j++){
        //刚才讲解的状态转移方程
			if(s[i]==t[j])dp[i][j]=dp[i-1][j-1]+2;
			else dp[i][j]=max(0,max(dp[i-1][j]-1,dp[i][j-1]-1));
			maxn=max(maxn,dp[i][j]);//由于要找最大相似度，所以要取max值 
		}
	}cout<<maxn;//输出即可 
	return 0;
}
```
 感谢观看！

---

## 作者：Eibon (赞：4)

先考虑正常的 LCS，设 $dp_{i,j}$ 表示 $a$ 数组的前 $i$ 位与 $b$ 数组的前 $j$ 位的最大公共子序列，易得转移方程为
$$dp[i][j]\gets\max(dp[i][j-1],dp[i-1][j])$$
$$dp[i][j]\gets\max(dp[i][j],dp[i-1][j-1]+1),(a[i]=b[j])$$
考虑到每增加一个子串长度，$ans$ 就要减 $1$，答案每加 $1$，$ans$ 加 $4$。

令 $dp_{i,j}$ 表示表示 $a$ 数组的前 $i$ 位与 $b$ 数组的前 $j$ 位的最大贡献。则转移方程为
$$dp[i][j]\gets dp[i-1][j-1]+2,(a[i]=b[j])$$
$$dp[i][j]\gets\max(dp[i][j],\max(dp[i][j-1],dp[i-1][j])-1)$$
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=5000+5;
int n,m,c,ans;
int dp[maxn][maxn],num1[maxn],num2[maxn];
char a[maxn],b[maxn];
signed main()
{
	scanf("%lld%lld",&n,&m);
	scanf("%s%s",a+1,b+1);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(a[i]==b[j]){
				dp[i][j]=dp[i-1][j-1]+2;
			}
			dp[i][j]=max(dp[i][j],max(dp[i][j-1],dp[i-1][j])-1);
			ans=max(ans,dp[i][j]);
		}
	}
	printf("%lld\n",ans);
	return 0;
}
//dyyyyds
```

---

## 作者：ykzzldz (赞：2)

说真的，这题我一开始想的有些复杂了，后来想想，其实挺简单的。

观察题目，发现与最长公共子序列有点像，无非是增加了一个条件。所以，定义 $dp[i][j]$ 表示在 $s1$ 中第 $i$ 位为结尾，$s2$ 中第 $j$ 位为结尾的最大答案。当 $s1_i=s2_j$，也就是当这两位相同时，可以由上一位转移过来，对当前位的贡献为 $2$（也就是公共子序列的贡献 $4$ 减去子串长度的 $2$）。另外，当前状态还能由 $dp[i-1][j]-1$ 和 $dp[i][j-1]-1$ 转移而来，原因显然。最后，只要选一个最大的就可以了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,dp[5100][5100],ans;
string ss1,ss2,s1=" ",s2=" ";
signed main(){
	cin>>n>>m>>ss1>>ss2;
	s1+=ss1,s2+=ss2;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(s1[i]==s2[j])dp[i][j]=dp[i-1][j-1]+2;
			dp[i][j]=max(dp[i][j],dp[i][j-1]-1);
			dp[i][j]=max(dp[i][j],dp[i-1][j]-1);
			ans=max(ans,dp[i][j]);
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：vectorwyx (赞：2)

提供一种比较清奇的dp思路（

令 $dp_{i,j}$ 表示 $A,B$ 两个字符串分别以 $i,j$ 位结尾的公共子序列对应的子串的最大值（下标从 $1$ 开始）。显然只有当 $A_{i}=B_{j}$ 时 $dp_{i,j}$ 才有意义，初始化为 $2$，其余状态除 $dp_{0,0}$ 为 $0$ 之外均初始化为 $-inf$。

转移：枚举所有可能和 $i,j$ 这两个位置“接上”的公共子序列，$dp_{i,j}=\max \ (dp_{k,w}+4-(i-k)-(j-w))=4-i-j+\max \ (dp_{k,w}+k+w$)($k<i,w<j$)。

观察发现最后一项 $dp_{k,w}+k+w$ 可以用二维前缀最大值维护，因此就做到了 $O(1)$ 的转移，总时间复杂度为 $O(nm)$。

代码如下：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define ll long long
#define fo(i,x,y) for(register int i=x;i<=y;++i)
#define go(i,x,y) for(register int i=x;i>=y;--i)
using namespace std;

inline int read(){
	int x=0,fh=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-') fh=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	return x*fh;
}

const int N=5005;
string A,B;
int dp[N][N],n,m,a[N],b[N],ans,sum[N][N];

int main(){
	n=read(),m=read();
	cin>>A>>B;
	fo(i,1,n) a[i]=A[i-1]-'a'+1;
	fo(i,1,m) b[i]=B[i-1]-'a'+1;
	memset(dp,-0x3f,sizeof dp);
	memset(sum,-0x3f,sizeof sum);
	//dp[0][0]=sum[0][0]=0;
	fo(i,1,n)
		fo(j,1,m){
			if(a[i]==b[j]){
				dp[i][j]=2;
				dp[i][j]=max(dp[i][j],sum[i-1][j-1]+4-i-j);
				ans=max(ans,dp[i][j]);
			}
			sum[i][j]=max(max(sum[i-1][j],sum[i][j-1]),dp[i][j]+i+j);
			//printf("(%d,%d):%d %d\n",i,j,dp[i][j],sum[i][j]);
		} 
	cout<<ans;
	return 0;
}

```


---

## 作者：Mason123456 (赞：1)

# Catching Cheaters

### 题目翻译

给我们两个字符串，算出它们的最大公共子序列长度。然后将它乘 $4$ 再减去两个**子序列所在的子串**的长度和。问你这个数最大是多少。

定义：子序列，可以不连续。子串，必须连续。

### 解题思路

求最长公共子序列的方法无非就是 `DP`。

$dp_{ij}$ 表示序列 $a$ 于 $b$ 中 $a_{1\sim i}$ 和 $b_{1\sim j}$ 的最长公共子序列的长度。

于是就有转移方程：

$$
dp_{ij} = \max(dp_{i-1,j}, dp_{i,j-1})
$$

$$
dp_{ij} = \max(dp_{ij}, dp_{i-1, j-1}+1)\space_{a_i=b_j}
$$

求出最长公共子序列后，我们看对于每个数的贡献。

如果 $a_i, b_j$ 加进来，并且 $a_i \ne b_j$，它的贡献就是 $4 \times 0 - 1 = -1$，如果 $a_i = b_j$，它的贡献就是 $4\times 1 - 1 - 1 = 2$，所以 `DP` 方程就成了这样：

$$
dp_{ij} = \max(dp_{i-1,j}, dp_{i,j-1})-1
$$

$$
dp_{ij} = \max(dp_{ij}, dp_{i-1, j-1}+2)\space_{a_i=b_j}
$$

最后，答案取 $\max$ 即可。

### CODE

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 5e3 + 5;
int n, m;
char a[N], b[N];
int f[N][N];
int main(){
	cin>>n>>m;
	for(int i = 1;i <= n;i++){
		cin>>a[i];
	}
	for(int j = 1;j <= m;j++){
		cin>>b[j];
	}
	int ans = 0;
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= m;j++){
			f[i][j] = max(f[i-1][j], f[i][j-1])-1;
			if(a[i] == b[j]){
				f[i][j] = f[i-1][j-1] + 2;
			}
			f[i][j] = max(0, f[i][j]);
			ans = max(ans, f[i][j]);
		}
	}
	cout<<ans;
	return 0;
	
} 
```

---

## 作者：huanglihuan (赞：0)

### 思路

首先，如果你不知道怎么求最长公共子序列，可以参考[这里](https://www.luogu.com.cn/paste/73o10bz7)。

而这题要求的答案是 $4 \times \texttt{两个字符串的最长公共子序列长度} - \texttt{两个字符串的长度}$。

定义 $dp_{i,j}$ 为以字符串 $a$ 以 $i$ 结尾，字符串 $b$ 以 $j$ 结尾的最长公共子序列长度。

如果 $a_i = b_j$，则 $dp_{i,j} = dp_{i-1,j-1}+1$。

否则，$dp_{i,j} = \max(0,\max(dp_{i-1,j},dp_{i,j-1})-1)$。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
char a [5005],b [5005];
int dp [5005] [5005];
int max (int a,int b)
{
	if (a > b) return a;
	else return b;
}
signed main ()
{
	int n,m;
	cin >> n >> m;
	cin >> (a + 1) >> (b + 1);
	int ans = 0;
	for (int i = 1;i <= n;i ++)
	{
		for (int j = 1;j <= m;j ++)
		{
			if (a [i] == b [j]) dp [i] [j] = dp [i - 1] [j - 1] + 2;
			else dp [i] [j] = max (0,max (dp [i - 1] [j],dp [i] [j - 1]) - 1);
			ans = max (ans,dp [i] [j]);
		}
	}
	cout << ans;
	return 0;
}
```

---

## 作者：happy_dengziyue (赞：0)

### 1 思路

设两个字符串为 $a$ 和 $b$。

设 $dp[i][j]$ 为，以 $a$ 的第 $i$ 位和 $b$ 的第 $j$ 位为尾端，能够做到的最优解。

那么，我们可以发现：

+ 如果 $a[i]=b[j]$，则有 $2$ 的贡献：$dp[i][j]=dp[i-1][j-1]+2$。

+ 无论 $a[i]=b[j]$ 是否成立，$dp[i][j]$ 都可以由 $dp[i-1][j]$ 和 $dp[i][j-1]$ 转移而来，贡献为 $-1$：$dp[i][j]=\operatorname{max}(dp[i-1][j],dp[i][j-1])-1$。

综上，我们可以有方程：

$$dp[i][j]=\operatorname{max}(dp[i-1][j],dp[i][j-1])-1$$

如果 $a[i]=b[j]$，$dp[i][j]$ 可以跟 $dp[i-1][j-1]+2$ 比较，取两者最大值。

答案为 $dp[|a|][|b|]$，其中 $|s|$ 为字符串 $s$ 的长度。

### 2 代码与记录

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
#define max_n 5000
int n;
int m;
char a[max_n+2];
char b[max_n+2];
int dp[max_n+2][max_n+2];
int ans=0;
inline int ma(int a,int b){
	return a>b?a:b;
}
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1446B_1.in","r",stdin);
	freopen("CF1446B_1.out","w",stdout);
	#endif
	scanf("%d%d%s%s",&n,&m,a+1,b+1);
	memset(dp,0,sizeof(dp));
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			if(a[i]==b[j])dp[i][j]=dp[i-1][j-1]+2;
			dp[i][j]=ma(dp[i][j],ma(dp[i-1][j]-1,dp[i][j-1]-1));
		}
	}
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j)ans=ma(ans,dp[i][j]);
	}
	printf("%d\n",ans);
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/58324141)

By **dengziyue**

---

## 作者：zztqwq (赞：0)

# Codeforces 1446B

## Solution

令 $f(i,j)$ 表示 $A$ 的前 $i$ 位，$B$ 的前 $j$ 位能够得到的最大分数，则容易得到转移方程：

$$f(i,j)=\begin{cases}\max\{f(i,j-1),f(i-1,j)\}-1, &A_i\not=B_j\\ f(i-1,j-1)+2, &A_i=B_j\end{cases}$$

注意过程中分数有可能是负数，随时和 $0$ 取 $\max$ 即可。

## Code

```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstring>
using namespace std;
const int N=5000;
int dp[N+10][N+10];
char s1[N+10],s2[N+10];
int main()
{
	int n,m,ans=0;
	scanf("%d%d%s%s",&n,&m,s1+1,s2+1);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			dp[i][j]=max(0,max(dp[i][j-1],dp[i-1][j])-1);
			if(s1[i]==s2[j]) dp[i][j]=max(dp[i][j],dp[i-1][j-1]+2);
			ans=max(ans,dp[i][j]);
		}
	printf("%d",ans);
}
```



---

## 作者：Piwry (赞：0)

## 解析

直接魔改下 $O(n^2)$ 最长公共子序列的 dp 式子即可

具体来说，设 $dp(i, j)$ 表示 $C$ 为 $0..A_{i-1}$ 后缀，$D$ 为 $0..B_{j-1}$ 后缀，的最大贡献

转移时也和公共子序列一样，考虑匹配 $i, j$ 或不匹配 $i, j$ 的情况即可。但要注意**更长的子串（$C, D$）不一定能获得更大的贡献**，因此还要考虑一种仅选择 $i, j$ 这两处的情况（由于上面的 dp 状态定义，这不能从 $dp(i-1, j-1)$ 或 $dp(i-1, j)$ 或 $dp(i, j-1)$ 转移得到）

还有不理解的地方可参考代码

## CODE

```cpp
#include <cstdio>
#include <iostream>
using std::max;

const int MAXN =5050;

int dp[MAXN][MAXN];/*C 为 0..A_{i-1} 后缀，D 为 0..B_{j-1} 后缀，的最大贡献*/

char s1[MAXN], s2[MAXN];

int main(){
	int n, m;
	scanf("%d%d", &n, &m);
	scanf("%s%s", s1, s2);
	int ans =0;/*初值注意下 C, D 均空也是一种答案*/
	for(int i =1; i <= n; ++i)
		dp[i][0] =-i;
	for(int j =1; j <= m; ++j)
		dp[0][j] =-j;
	for(int i =1; i <= n; ++i)
		for(int j =1; j <= m; ++j){
			if(s1[i-1] == s2[j-1]){/*尝试匹配 i, j*/
				int tmp1 =dp[i-1][j-1]+4*1-2,
					tmp2 =4*1-2;
				dp[i][j] =max(tmp1, tmp2);
				
			}
			else{
				int tmp1 =dp[i-1][j-1]-2,
					tmp2 =-2;
				dp[i][j] =max(tmp1, tmp2);
			}
			int tmp01 =dp[i-1][j]-1,/*不尝试匹配 i, j*/
				tmp02 =dp[i][j-1]-1;
			dp[i][j] =max(dp[i][j], max(tmp01, tmp02));
			ans =max(ans, dp[i][j]);
		}
	printf("%d", ans);
}
```

---

## 作者：vеctorwyx (赞：0)

### 题目大意

给定两个字符串，求两个字符串的子串使得两个子串的相似度最高。

两个字符串$A,B$的相似度为$4·LCS(A,B) - |A|-|B|$，其中LCS为[最长公共子序列](https://baike.baidu.com/item/%E6%9C%80%E9%95%BF%E5%85%AC%E5%85%B1%E5%AD%90%E5%BA%8F%E5%88%97/8010952?fr=aladdin)，$|A|$表示字符串$A$的长度。

----

### sol

~~傻*DP题~~

肯定很多人看完题跟我一样先想到求LCS。

~~然后就卡在那里卡了一个多小时~~

其实LCS光从时间复杂度上就说不通（~~我不会优化~~），至少$O(n^2m)$，会TLE。

------

正确解法：

想DP。

1. 设状态：

	设$\large dp_{i,j}$表示$A$处理到第$i$位，$B$处理到第$j$位，且$A$的子串以第$i$位为结尾，$B$的子串以第$j$位为结尾时的答案。

2. 写转移：

	先想每种情况的贡献。
    
    - 如果只有$i$后移一位（$i++$），或只有$j$后移一位（$j++$），则只会曾加子串长度，而不会改变$LCS$，__即答案-1__；
    - 如果$i,j$同时后移一位（$i++,j++$），且后移后$A_i = B_j$，则会使贡献$LCS$增长一位，同时两个子串的长度都增长，__即答案+2__；
    - 特殊的，第二种情况也可能是子串分别以第$i,j$位为开头的情况。
    
	转移就出来了：
    
    ```
    for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++){
			dp[i][j] = max(dp[i - 1][j] - 1 , dp[i][j - 1] - 1);//情况1
			if(a[i] == b[j])
				dp[i][j] = max(dp[i][j],max(dp[i - 1][j - 1] + 2, 2ll));//情况2，情况3
		}
                
    ```
3. 记答案：

	由于每一种状态都有可能使相似度最高，即每种状态都可能做最后答案，直接在把每个状态与答案取max就好。
    
code:

```
#include "iostream"
#include "cstdio"
#include "cstring"
#define int long long
using namespace std;
int read()
{
	int xsef = 0,yagx = 1;char cejt = getchar();
	while(cejt < '0'||cejt > '9'){if(cejt == '-')yagx = -1;cejt = getchar();}
	while(cejt >= '0'&&cejt <= '9'){xsef = (xsef << 1) + (xsef << 3) + cejt - '0';cejt = getchar();}
	return xsef * yagx;
}
int n,m;
int ans;
char a[5010];
char b[5010];
int dp[5010][5010]; 
signed main(){
	n = read(),m = read();
	scanf("%s",a + 1);
	scanf("%s",b + 1);
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++){
			dp[i][j] = max(dp[i - 1][j] - 1 , dp[i][j - 1] - 1);
			if(a[i] == b[j])
				dp[i][j] = max(dp[i][j],max(dp[i - 1][j - 1] + 2, 2ll));
			ans = max(ans, dp[i][j]);
		}
	printf("%lld",ans);
	return 0;
}


```

要是能在比赛期间想出来他不香吗/kk

---

