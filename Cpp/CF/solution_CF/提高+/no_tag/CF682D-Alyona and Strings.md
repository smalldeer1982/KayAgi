# Alyona and Strings

## 题目描述

After returned from forest, Alyona started reading a book. She noticed strings $ s $ and $ t $ , lengths of which are $ n $ and $ m $ respectively. As usual, reading bored Alyona and she decided to pay her attention to strings $ s $ and $ t $ , which she considered very similar.

Alyona has her favourite positive integer $ k $ and because she is too small, $ k $ does not exceed $ 10 $ . The girl wants now to choose $ k $ disjoint non-empty substrings of string $ s $ such that these strings appear as disjoint substrings of string $ t $ and in the same order as they do in string $ s $ . She is also interested in that their length is maximum possible among all variants.

Formally, Alyona wants to find a sequence of $ k $ non-empty strings $ p_{1},p_{2},p_{3},...,p_{k} $ satisfying following conditions:

- $ s $ can be represented as concatenation $ a_{1}p_{1}a_{2}p_{2}...\ a_{k}p_{k}a_{k+1} $ , where $ a_{1},a_{2},...,a_{k+1} $ is a sequence of arbitrary strings (some of them may be possibly empty);
- $ t $ can be represented as concatenation $ b_{1}p_{1}b_{2}p_{2}...\ b_{k}p_{k}b_{k+1} $ , where $ b_{1},b_{2},...,b_{k+1} $ is a sequence of arbitrary strings (some of them may be possibly empty);
- sum of the lengths of strings in sequence is maximum possible.

Please help Alyona solve this complicated problem and find at least the sum of the lengths of the strings in a desired sequence.

A substring of a string is a subsequence of consecutive characters of the string.

## 说明/提示

The following image describes the answer for the second sample case:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF682D/2e74041884d67a1d079badb418366bd0a678e7b0.png)

## 样例 #1

### 输入

```
3 2 2
abc
ab
```

### 输出

```
2
```

## 样例 #2

### 输入

```
9 12 4
bbaaababb
abbbabbaaaba
```

### 输出

```
7
```

# 题解

## 作者：_masppy_ (赞：1)

### 题目链接：[Link](https://www.luogu.com.cn/problem/CF682D)

&nbsp;

### 题目大意：
给定长度为 $n$ 的字符串 $c$ 和长度为 $m$ 的字符串 $s$。现从 $c$ 中有序地选出 $x$ 个子串，使得这些子串在 $s$ 中也存在，且先后顺序和 $c$ 中相同。求这些子串的长度之和最大为多少。

&nbsp;

### 解题思路：
考虑 `LCS`,发现有选取一定数量子串的要求，于是设状态为 $dp[k][i][j]$，意为从 $c$ 的前 $i$ 个字符和 $s$ 的前 $j$ 个字符中选取 $k$ 个子串时的最大答案。

那么先处理当选取 $k$ 个子串时，$c$ 中最后被选取的字符下标是 $i$，$s$ 中是 $j$ 时的最大答案。先判断这样选取是否合法，即 $c_i=s_j$，然后转移，转移方程如下：
$$dp_{k,i,j}=\max(dp_{k,i-1,j-1},dp_{k-1,i-1,j-1})+1$$

然后再根据转移得出的值处理出真正的 $dp_{k,i,j}$，转移方程如下：
$$dp_{k.i.j}=\max(dp_{k,i,j},dp_{k,i-1,j},dp_{k,i,j-1})$$

最后输出 $dp_{x,n,m}$ 即可。

代码如下：
```cpp
for(int k=1;k<=x;k++){
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(c[i]==s[j]) dp[k][i][j]=max(dp[k][i-1][j-1],dp[k-1][i-1][j-1])+1;
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			dp[k][i][j]=max(dp[k][i][j],max(dp[k][i-1][j],dp[k][i][j-1]));	
		}	
	}
}
```

然后发现可以滚动数组优化一下，即多设一个 $tmp_{i,j}$，对于第 $k$ 轮转移， $tmp$ 便代表 第 $k-1$ 轮的枚举结果。

代码如下：
```cpp
for(int k=1;k<=x;k++){
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(c[i]==s[j]) dp[i][j]=max(dp[i-1][j-1],tmp[i-1][j-1])+1;
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			dp[i][j]=max(dp[i][j],max(dp[i-1][j],dp[i][j-1]));
			tmp[i][j]=dp[i][j];
		}
	}
}

```
完结撒花 OvO！！！

---

## 作者：BruteForcer (赞：1)

题意：有两个字符串$s$、$t$，长度分别为$n$、$m$。要求在$s$、$t$中分别找出$k$个**顺序一致**的公共子串，求这$k$个子串的最大长度和。

首先，你需要会原版LCS（最长公共子串）。但是，这不是一个子串，而是$k$个子串。

那就再加一维，$dp[l][i][j]$表示在$s$的前$i$位和$t$的前$j$位中取了$l$个公共子串时的答案。

先按**必须取**$s[i]$和$t[j]$转移。若可以匹配，则有计入新的公共子串或接到上一个公共子串两种选择，取较大值。否则不用处理。当然，若接到上一个公共子串上，$s[i-1]$和$t[j-1]$也得是可以匹配的，否则$dp$值就$=0$。不合法的情况都未转移到，$dp$值都$=0$，这就体现出了按必须取转移的作用。

转移完一遍后，就要将$dp[l][i][j]$的值改为从$s$的**前**$i$位和$t$的**前**$j$位取的最大值，准备下一轮转移。

$n,m≤1000, k≤10$，$O(nmk)$可以过。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
char s[1005],t[1005];
int dp[15][1005][1005];
int main()
{
	int n,m,k;
	scanf("%d%d%d",&n,&m,&k);
	cin>>s+1;cin>>t+1;
	for(int l=1;l<=k;l++)
	{
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=m;j++)
			{
				if(s[i]==t[j]) dp[l][i][j]=max(dp[l][i-1][j-1],dp[l-1][i-1][j-1])+1;
			}
		}
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=m;j++) dp[l][i][j]=max(dp[l][i][j],max(dp[l][i-1][j],dp[l][i][j-1]));
		}
	}
	printf("%d",dp[k][n][m]);
	return 0;
}
```


---

## 作者：Bosun (赞：0)

因为看到“顺序相同”，我们联想到了LCS（最长公共子序列）,只不过LCS是对于每个选出来的字符相等且顺序相同，而这里是每个选出来的子串。所以我们按照lcs的套路做，设f[i][j][k][0/1]为：匹配到s的第i位，t的第j位，已经到了第k个字符串，第k个字符串是否继续拓展。

如果s[i]==t[j] 那么f[i][j][k][0]最优决策肯定是f[i-1][j-1][k-1][1]+1或者f[i-1][j-1][k][0]+1（自己新建一段或者拓展之前的一段）

否则，f[i][j][k][1]的最优决策，只能从f[i-1][j]或者f[i][j-1]转移而来，这样就完事了？？？？

Fake！！！如果我s[i]==t[j]的时候，也就是说我这一段是可以选择拓展和不拓展的，如果可以拓展，那不拓展的答案也该有max(f[i-1][j-1][k-1],f[i-1][j-1][k][0])+1，其实就是f[i][j][k][0],对吧

整理一下：

如果s[i]==t[j]:f[i][j][k][0]=max(f[i-1][j-1][k-1][1],f[i-1][j-1][k][0])+1;

f[i][j][k][1]=max(f[i-1][j][k-1][1],f[i][j-1][k-1][1],f[i][j][k][0]);

上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k,f[1001][1001][11][2];
char s[1001],t[1001];
int main(){
	int i,j,l;
	cin>>n>>m>>k;
	scanf("%s",s+1),scanf("%s",t+1); 
	for(i=1;i<=n;i++){
		for(j=1;j<=m;j++){
			if(s[i]==t[j]){
				for(l=1;l<=k;l++){
					f[i][j][l][0]=max(f[i-1][j-1][l][0],f[i-1][j-1][l-1][1])+1;
				}
			}
			for(l=1;l<=k;l++)f[i][j][l][1]=max(f[i-1][j][l][1],max(f[i][j-1][l][1],f[i][j][l][0]));			
		}
	}
	cout<<f[n][m][k][1]<<endl;
	return 0;
}
```


---

## 作者：2huk (赞：0)

经典题。

考虑 DP。设 $f(i, j, k, 0/1)$ 表示只考虑 $s_{1\dots i},t_{1\dots j}$，总共选了 $k$ 个**非空**子串，且 $s_i, t_j$ 是否**匹配**。

这里比较重要的是第四维。**匹配**的意思是指，$s_i, t_j$ 最终都被选择，且都被选择在了同一个（也就是第 $k$ 个）子串里。同理，不匹配就是指 $s_i, t_j$ 中有至少一个没有被选择。

考虑转移：

$$
f(i, j, k, 0) = \max\{f(i-1,j-1,k,0/1), f(i-1,j,k,0/1), f(i,j-1,0/1)\} \\
f(i,j,k,1) = \begin{cases}\max\{f(i-1,j-1,k,1),f(i-1,j-1,k-1,0)\} + 1 & s_i = t_j \\ 0 & s_i \ne t_j\end{cases}
$$

$f(i, j, k, 0)$ 不难理解。$f(i, j, k, 1)$ 中的 $\max\{f(i-1,j-1,k,1),f(i-1,j-1,k-1,0)\} + 1$ 是指，要么 $i, j$ 和上一个子串接起来，要么重开一个，但是最终都要 $+1$ 表示被选择的数多了一个。

原题允许子串为空，但我们的状态里规定不为空，所以答案不是 $f(n, m, k, 0/1)$ 而是 $\max_{i \le k} f(n, m, i, 0/1)$。

---

## 作者：Thunder_S (赞：0)

[不同的阅读体验](https://www.cnblogs.com/Livingston/p/15226659.html)
## Solution

比较经典的 $dp$​。

考虑 $f_{i,j,k}$ 表示 $S$ 到了第 $i$ 位，$T$ 到了第 $j$ 位，已经选择了 $k$ 个子串的最大长度和。

但是由于当前位能否匹配与上一位有关，因此再开一维 $0/1$ 表示 $i-1$ 和 $j-1$ 是否匹配。

转移：

如果 $S_i=T_j$，说明当前位可以匹配，那么 $f_{i,j,k,1}=\max(f_{i-1,j-1,k,1},f_{i-1,j-1,k-1,0})+1$。

然后 $f_{i,j,k,0}=\max\{f_{i-1,j-1,k,0/1},f_{i,j-1,k,0/1},f_{i-1,j,k,0/1}\}$。

因为可以有空串，所以 $ans=\max\{f_{n,m,1\texttt{->}k,0/1}\}$。

## Code

```cpp
#include<cstdio>
#include<algorithm>
#define N 1005
#define K 11
using namespace std;
int n,m,kk,x,ans,f[N][N][K][3];
char ch,a[N],b[N];
int main()
{
	scanf("%d%d%d",&n,&m,&kk);
	ch=getchar();
	while (ch<'a'||ch>'z') ch=getchar();
	x=0;
	while (ch>='a'&&ch<='z') a[++x]=ch,ch=getchar();
	while (ch<'a'||ch>'z') ch=getchar();
	x=0;
	while (ch>='a'&&ch<='z') b[++x]=ch,ch=getchar();
	for (int i=1;i<=n;++i)
		for (int j=1;j<=m;++j)
			for (int k=1;k<=kk;++k)
			{
				if (a[i]==b[j]) f[i][j][k][1]=max(f[i-1][j-1][k-1][0],f[i-1][j-1][k][1])+1;
				f[i][j][k][0]=max(max(max(f[i-1][j-1][k][0],f[i-1][j-1][k][0]),max(f[i][j-1][k][0],f[i][j-1][k][1])),max(f[i-1][j][k][0],f[i-1][j][k][1]));
			}
	for (int i=1;i<=kk;++i)
		ans=max(max(f[n][m][i][1],f[n][m][i][0]),ans);
	printf("%d\n",ans);
	return 0;
} 
```



---

