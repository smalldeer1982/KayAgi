# Python Indentation

## 题目描述

CF909C Python的缩进 
Python的代码中不需要写begin、end或者大括号去标记开头或结尾。
我们将考虑一种Python非常简化的子集，它的语句只有两种类型。 
每行只写一个简单语句，比如赋值。
For语句是一个较复杂的语句，他们可能包含一个或多个其他的语句。
For语句由一个单独的行组成，以“For”前缀和循环体开头。
循环体是一个语句块，比循环头缩进一级。
循环体可以包含这两种类型的语句。循环体不能为空。
给你一个没有缩进的序列，求有多少种方式添加缩进可以形成一个完整的Python代码。

## 样例 #1

### 输入

```
4
s
f
f
s
```

### 输出

```
1
```

## 样例 #2

### 输入

```
4
f
s
f
s
```

### 输出

```
2
```

# 题解

## 作者：LesterYu (赞：6)

这显然是一道DP。

考虑用数组dp[ i ][ j ]来储存状态，即第 i 条语句后放在缩进 j 层的循环内的方案种数，观察可知，当前一条语句为“s”时放在第 j 层循环内的所有方案数都可以放在0~j-1层，那么就应该将0~j-1的方案数都加上这个值。当前一条语句为“f”时，就往外拓展一层，即放在第 j 层循环内的方案数等于放在第 j-1 层循环内的所有方案数。注意，读入后不能处理当前的语句，应处理前一条，因为我们存的相当于在添加一句“s”后的选择数，所以每遍循环处理上一条语句。

由于n<=5000，所以一个5000 * 5000的数组会妥妥地MLE，因此考虑用滚动数组，last记录前一个状态。

代码如下：


```cpp
#include<cstdio>
#define MAX 1000000007
using namespace std;
long long n,ans,max;
long long a[5001],dp[5001],last[5001];
char s[2];
int main(){
    scanf("%lld",&n);
    last[0]=1;//一开始只有一种方案,放在0层循环里
    for(int i=1;i<=n;i++){
        scanf("%s",s);
        if(s[0]=='f') a[i]=1;
        if(!a[i-1]){
            for(int j=max;j>=0;j--)
            dp[j]=dp[j+1]+last[j],dp[j]%=MAX;
        }
        else{//若上一条语句为“f”，则拓展一层
            for(int j=++max;j>=1;j--)
            dp[j]=last[j-1];
        }
        for(int j=0;j<=max;j++) 
        last[j]=dp[j],dp[j]=0;
    }
    for(int i=0;i<=max;i++) 
    ans+=last[i],ans%=MAX;//总方案数为各方案数之和
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：STrAduts (赞：5)

一 道 好 题。

题目描述不在赘述，这道题抽象概括出模型后反而更复杂 ））

首先，不难往 $dp$ 方向去想。

我们定义 $dp[i][j]$ 表示处理到第 $i$ 个语句时，第 $i$ 个语句处在第 $j$ 个缩进时的总共方案数。

找边界，你会发现只有 for 语句能贡献新的缩进，即有多少个 for 语句就最多有多少个缩进，故我们记 for 语句的个数为为 $m$。

如果第 $i-1$ 个语句是一个 for 语句，则当前语句一定在上一个语句的下一个缩进。

这很显然吧，毕竟 for 语句一定不能在整个代码的最后一个。这个时候更新就很简单了。

$dp[i][j] = dp[i - 1][j - 1] (\forall j, 1 \leq j \leq m)$。

那如果不是 for 语句呢？

我们想一想一个缩进的性质，如果上一个语句可以处于第 $j$ 个缩进，则当前语句处于 $i,0 \leq i \leq j$ 都是合法的。

因为如果上一个语句处于第 $j$ 个缩进，则一定能在上面找到对应的使它合法的 for（当然如果 $j = 0$ 就找不到），那么在下面再接一个语句都是没问题的，相当于我们在我们找到的那个 for 下再接了一个语句。

这样就很明朗了。

$dp[i][j] = \sum_{k = j}^m dp[i - 1][k]$。

当然，你会发现这里其实有个后缀和，那么每次维护上一个状态的后缀和就可以实现优化。

注意，这道题玄学卡前缀和（或许是卡 **long long**？？），我下来调就是因为这个 $80pt$ 的。

实现就按以上转移即可。注意取模。

```cpp
#include <cstdio>

typedef long long LL;
const int MAXN = 5e3 + 5;
const LL mod = (LL)1e9 + 7;
int a[MAXN];
LL dp[MAXN][MAXN], sum[MAXN];
// 第 i 个数，当前 j 个缩进。 

int main() {
	int n, m = 0;
	scanf ("%d", &n);
	for(int i = 1; i <= n; i++) {
		char st[5];
		scanf ("%s", &st);
		if(st[0] == 's')
			a[i] = 0;
		else 
			a[i] = 1;
		m += a[i];
	}
	m++;
	dp[1][0] = 1;
	for(int i = 2; i <= n; i++) {
		sum[m + 1] = 0;
		for(int j = m; j >= 0; j--)
			sum[j] = (sum[j + 1] % mod + dp[i - 1][j] % mod) % mod;
		if(a[i] == 0) {		
			if(a[i - 1] == 1) {
				for(int j = 1; j <= m; j++)
					dp[i][j] = dp[i - 1][j - 1] % mod;
				continue;
			}				
			for(int j = 0; j <= m; j++)	
				dp[i][j] = sum[j] % mod; 
		}
		else {
			if(a[i - 1] == 1) {
				for(int j = 1; j <= m; j++)
					dp[i][j] = dp[i - 1][j - 1] % mod;
				continue;
			}
			for(int j = 0; j <= m; j++)	
				dp[i][j] = sum[j] % mod;
		}
	} 
	LL ans = 0;
	for(int i = 0; i <= m; i++)
		ans = (ans % mod + dp[n][i] % mod) % mod; 
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：White_AL (赞：3)

# 分析
这是一道 dp 题。我看到其他很多题解的大佬都是写的二维数组 dp，但这道题是可以优化到一维的。遂写一下一维的方法，并且说说几个细节。 

首先得到状态转移方程。考虑对于每一行，它不同缩进下的方案数，并且分为两种情况：上一行为 ```f``` 或 ```s```。
我们用 $dp[i][j]$ 表示第 $i$ 行缩进数为 $j$ 时的方案数量。
1. $code[i-1] = \text{f}$，因为上一行是 ```f```，所以这一行的缩进数必定是上一行缩进数加一。对于这一行的每一种缩进，方案数等于上一行缩进数为 $j - 1$ 的方案数。因此有 $dp[i][j] = dp[i - 1][j - 1]$。特别地，$dp[i][0] = 0$。
2. $code[i-1] = \text{s}$，因为上一行是 ```s```，所以这一行的缩进数可以为 $0 \sim maxj$（$maxj$ 为缩进数量的最大值）的任意值。因此对于这一行的每一种缩进，方案数为上一行缩进数大于 $j$ 个的方案数之和。因此有 $dp[i][j] = \sum_{m=j}^{maxj} dp[i - 1][m]$。

整理一下，

$$dp[i][j]=\begin{Bmatrix}
 dp[i - 1][j - 1]\space(code[i-1] = \text{f})\\
\sum_{m=j}^{maxj} dp[i - 1][m]\space(code[i-1] = \text{s})\end{Bmatrix}\space(2≤i≤n,0≤j≤maxj)$$

其中初始状态为 $dp[1][0] = 1$。

# 优化
注意到 $dp[i][j]$ 只和 $dp[i-1][j-1]$ 或 $dp[i-1][j+n]$ 有关。于是可以运用滚动数组的思想优化一个维度。如果数据范围更大一点就不会 MLE 了。

如果要使用滚动数组并且只使用一个 dp 数组，那么必须考虑状态更新顺序的问题。事实上，这道题中并不需要。

我们需要维护 dp 数组的两个操作：整体右移一格以及对于每个元素求后缀和。后者显然可以通过每次更新一遍后求所有元素的后缀和以达到每一遍更新 $O(n)$ 的时间复杂度。

其实，求后缀和的过程就是储存前一次更新后 dp 数组的内容。因此，可以把两个操作都基于后缀和数组进行，这样 dp 数组修改的结果一定不会互相影响，也不需要考虑更新的顺序了。最后的代码时间复杂度 $O(n^2)$，空间复杂度 $O(n)$。

# AC CODE
```cpp
#include <bits/stdc++.h>
using namespace std;
const int mod = 1000000007;
int n;
bitset<30010> code;		//数值只有两种便使用了bitset，其实没有必要
int dp[30010];
int pre[30010] = { 0 };
int main() {
	scanf("%d", &n);
	getchar();
	for (int i = 1; i <= n; i++) {
		char c;
		scanf("%c", &c);
		if (i != n) getchar();		//用于把输入中的回车清除
		if (c == 'f') code[i] = 1;
		else code[i] = 0;
	}
	if (code[n]) {
		printf("%d\n", 0);
		return 0;
	} 
	int maxj = 0;
	dp[0] = 1;
	pre[0] = 1;
	for (int i = 2; i <= n; i++) {
		if (code[i - 1] == 1) {		//上一个是f 
			maxj++;
			for (int j = maxj; j >= 0; j--) {
				if (j == 0) dp[j] = 0;
				else dp[j] = (pre[j - 1] - pre[j] + mod) % mod;
			}
		} else {
			for (int j = 0; j <= maxj; j++) {
				dp[j] = (pre[j] + mod) % mod;
			}
		}
		//memset(buf, 0, sizeof(buf));
		for (int j = maxj; j >= 0; j--) {		//求后缀和
			pre[j] = (dp[j] + pre[j + 1]) % mod; 
		}
	}
  	int ans = 0;
	for (int i = 0; i <= maxj; i++) {
		ans += dp[i];
		ans %= mod;
	}
	printf("%d\n", ans);
	return 0;
```


---

## 作者：Grisses (赞：3)

[题面](https://www.luogu.com.cn/problem/CF909C)

一道 DP 题。我们设 $dp_{i,j}$ 表示第 $i$ 行有 $j$ 个缩进（Tab）时的方案数，$s_i$ 表示第 $i$ 行是什么语句（$s/f$），$Maxn_i$ 表示第 $i$ 行之前的 $f$ 的数量。则：

- 如果 $s_{i-1}=f$，则 $dp_{i,j}=dp_{i-1,j-1}(j>0)$，这是应为如果 $s_{i-1}=f$ 那么第 $i$ 行就一定比第 $i-1$ 行多一个缩进。

- 如果 $s_{i-1}=s$，则 $dp_{i,j}=\sum\limits_{k=j}^{Maxn_{i-1}}dp_{i-1,k}$，这是因为如果 $s_{i-1}=s$，那么第 $i-1$ 行的缩进数量会比第 $i$ 行多。另外第 $i-1$ 行最多会有 $Maxn_{i-1}$ 个缩进。但这样时间复杂度会高达 $\operatorname{O}(n^3)$。不过，我们可以发现：他们的区间右端点都是 $i-1$，所以可以反着枚举。

代码：
```cpp
  #include<bits/stdc++.h>
  using namespace std;
  const int mod=1e9+7;
  int n,maxn,ans,dp[5005][5005];
  char s[5005];
  int main()
  {
      scanf("%d",&n);
      for(int i=1;i<=n;i++)scanf("\n%c",&s[i]);
      dp[0][0]=1;
      for(int i=1;i<=n;i++){
          for(int j=maxn;j>=0;j--){//倒着枚举
              if(s[i-1]=='f'){if(j)dp[i][j]=dp[i-1][j-1];}//为‘f’
              else dp[i][j]=(dp[i-1][j]+dp[i][j+1])%mod;//为‘s’	
          }
          if(s[i]=='f')maxn++;//最多会有的缩进数量（‘f’的数量）
      }
      for(int i=0;i<=maxn;i++)ans=(ans+dp[n][i])%mod;
      printf("%d",ans);
      return 0;
  }
```

---

## 作者：cqbz_lipengcheng (赞：2)

## 前言：
这道题开始将题意看错了，将它打成了一道思维题，事后才发现这是一道DP。果然还是我太菜了
## 题解：
### 1.状态：
$dp[i][j]$表示第$i$行j个缩进的总方案数。
### 2.状态转移：
(1) 当前一行为$f$

这时由题意得这一行必须在上一行的基础上缩进一格（且只能为一格）
所以$dp[i][j] = dp[i - 1][j - 1];$

(2)当前一行为$s$

这时我们可以任意缩进，但是要注意因为上一格是$s$所以这一行不能缩进，即若这一行为i，上一行只能在i~n中取值。所以我们可以用一个倒叙循环对每一次的个数累加。
## 代码：
```cpp
#include <iostream>
#include <cstdio>
using namespace std;
const int MAXN = 5005, mod = 1e9 + 7;
long long dp[MAXN][MAXN], n;
char a[MAXN];
int main() {
    scanf("%lld", &n);
    for (int i = 1; i <= n; i++) cin>>a[i];
    dp[1][0] = 1;
    for (int i = 2; i <= n; i++) {
        if (a[i - 1] == 'f') {
            for (int j = 1; j <= i; j++) dp[i][j] = dp[i - 1][j - 1];
        } else {
            long long sum = 0;
            for (int j = i; j >= 0; j--) {
                sum = (sum + dp[i - 1][j]) % mod;
                dp[i][j] = sum;
            }
        }
    }
    long long zsum = 0;
    for (int i = 0; i <= n; i++) zsum = (zsum + dp[n][i]) % mod;
    printf("%lld", zsum);
    return 0;
}

```

---

## 作者：cqbz_luoyiran (赞：1)

# 分析
看一眼题目与数据范围，搜索时间一定炸，显然是一道$Dp$。

设$dp[i][j]$为以$i$结尾，前面有$j$个空格的总方案数。

我们可以分为两种情况：

## 1.s[i-1]='f'
这种情况比较简单，因为有一个限制是每一个$f$下面必须不为空，所以说当前这个的位置必须是在上一个字符的下一层，也就是下一个包含在上一个中，

**for example**:

---
```
f
 x
 
x表示'f'或's'
```
---
于是我们就可以推出来这样一个转移方程：
$$dp[i][j] = dp[i - 1][j - 1](s[i-1]=='f')$$

## 2.s[i-1]='s'
这种情况稍显复杂，因为如果上一个字符为$s$的话，那么下面一个字符就可以在不超过上一个的层数的任何位置，设上一个在第x层，那么这一个位置就可以在x-1,x-2,x-3...2,1这一些层数在0~x-1的位置，故上一个$dp[i-1][j]$的方案数可以加到$dp[i][k](0<=k<=j)$这里面。

**for example**:

---
```
  s
x

  s
 x
 
  s
  x
  
x表示'f'或's'
```
---
于是我们就可以推出来这样一个转移方程：
$$dp[i][j] = \sum(dp[i - 1][k])$$

其中k>=j。

## 时间复杂度问题

如果第二种世界暴力写的话，可以发现最坏时间复杂度为$O(n^3)$，绝对会T。于是考虑后缀和，优化一下时间复杂度，在第二种情况就可以$O(n)$更新，于是总的时间复杂度为$O(n^2)$。

# 代码

```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
#define MOD 1000000007
const int MAXN = 5e3 + 5;
int n,sum[MAXN],dp[MAXN][MAXN],ans,Sum[2][MAXN];
char s[MAXN];
int main() {
	scanf("%d",&n);
	for(int i = 1;i <= n;i ++) {
		scanf("\n%c",&s[i]);
		if(s[i] == 'f') sum[i + 1] = sum[i] + 1;
		else sum[i + 1] = sum[i];
	}
	if(s[n] == 'f') return printf("0"),0;
	dp[1][0] = 1,Sum[0][0] = 1;
	for(int i = 2;i <= n;i ++) {
		if(s[i - 1] == 's')
		for(int j = sum[i];j >= 0;j --) {
			dp[i][j] += Sum[0][j],dp[i][j] %= MOD;
			Sum[1][j] = Sum[1][j + 1] + dp[i][j],Sum[1][j] %= MOD;
		}	
		else for(int j = sum[i];j >= 0;j --)
		dp[i][j] = dp[i - 1][j - 1],dp[i][j] %= MOD,Sum[1][j] = Sum[1][j + 1] + dp[i][j],Sum[1][j] %= MOD;
		memcpy(Sum[0],Sum[1],sizeof(Sum[1]));
	}
	for(int i = 0;i <= sum[n];i ++)
	ans += dp[n][i],ans %= MOD;
	printf("%d",ans);
	return 0;
}
```


---

## 作者：Fool_Fish (赞：1)

## 思路

`dp[i][j]` 表示前 `i` 行语句，且第 `i` 行语句前面有 `j` 个缩进时的总方案数

转移时，需要按前一行语句来进行分类

### 前一行为 f

当前一行为 `f` 时，很明显，这一行必须在前一行的基础上再加一个缩进，并且有且仅有这一种方法，所以枚举这一行的缩进个数，通过前一行来转移这一行即可

另外，这一行的缩进数最多也就是当前 `f` 的总个数（每个 `f` 都缩进），所以循环时就不用每次都从很大开始枚举

```cpp
if(a[i-1]=='f'){
	fcnt++;
	for(int j=1;j<=fcnt;j++){
		dp[i][j]=dp[i-1][j-1];
		dp[i][j]%=MOD;
	}
}
```

### 前一行为 s

由于我们保证了合法，所以前一行为 `s` 时就可以理解为前面已经形成了一个完整的代码块，具体如下

![](http://61.186.173.89:2019/2020/12/29/60b763bf3bb7f.png)

在这张图中，我们发现在第 $7$ 行的时候，图中用 $-$ 标出的位置是都可以放的

所以对于这样的一种情况，我们也有了转移的方法

```cpp
for(int j=0;j<=m;j++){
	for(int k=j;k<=m;k++){
		dp[i][j]+=dp[i-1][k];
		dp[i][j]%=MOD;
	}
}
```

### 答案统计

枚举最终有多少缩进，加起来即可

```cpp
int ans=0;
for(int i=0;i<=fcnt;i++){
	ans+=dp[n][i];
	ans%=MOD;
}
```

### 优化

我们发现，在第二种情况时，时间复杂度可以达到 $\mathcal {O}(n^3)$,根（ka）本(chang)无(ji)法(ke)通过这道题，于是很简单的考虑到后缀和来优化：

```cpp
sum[fcnt+1]=0;
for(int j=fcnt;j>=0;j--){
	sum[j]=dp[i-1][j]+sum[j+1];
	sum[j]%=MOD;
}
//第二种情况时 
for(int j=0;j<=fcnt;j++){
	dp[i][j]=sum[j];
	dp[i][j]%=MOD;
}
```

## code

```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
const int MAXN=5005;
const int MOD=1e9+7;
char a[MAXN];
int dp[MAXN][MAXN];
int sum[MAXN];
int main(){
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		char t[5];
		scanf("%s",t+1);
		a[i]=t[1];
	}
	dp[1][0]=1;
	int fcnt=0;
	for(int i=2;i<=n;i++){
		sum[fcnt+1]=0;
		for(int j=fcnt;j>=0;j--){
			sum[j]=dp[i-1][j]+sum[j+1];
			sum[j]%=MOD;
		}
		if(a[i-1]=='f'){
			fcnt++;
			for(int j=1;j<=fcnt;j++){
				dp[i][j]=dp[i-1][j-1];
				dp[i][j]%=MOD;
			}
		}
		else{
			for(int j=0;j<=fcnt;j++){
				dp[i][j]=sum[j];
				dp[i][j]%=MOD;
			}
		}
	}
	int ans=0;
	for(int i=0;i<=fcnt;i++){
		ans+=dp[n][i];
		ans%=MOD;
	}
	printf("%d",ans);
return 0;
} 
/*
4
s
f
f
s

1 s
2 f
3 	f
4 		s
*/
```

---

## 作者：cqbzhyf (赞：0)

[题目在这里](https://www.luogu.com.cn/problem/CF909C)

作为一个 `DP` 蒟蒻，看见这到题首先想到的是 `记忆化搜索` ，结果搜索中处理不善（套了一层循环），然后得到了十分可观的分数—— $10pts$。

考虑定义状态：

$dp[i][j]$ 表示第 $i$ 行有 $j$ 个缩进的方案总数，不难发现有两种类型：

1.如果第 $i-1$ 行是 `f`，那么一定比上一行多了一个缩进，于是 $dp[i][j]=dp[i-1][j-1]$；

2.如果第 $i-1$ 行是 `s`,那么本行的缩进数一定 $\le$ 上一行的缩进数，于是 $dp[i][j]=\displaystyle \sum_\ dp[i-1][k] ({i-2 \le k \le j})$。

这样时间复杂度就到达了 $O(n^{3})$，但是看数据范围显然会 `TLE` 。

于是考虑优化对于 $k$ 的枚举：

1.可以预处理出上一行的前缀和方便下一行运算（注意考虑负数取模）；

2.倒着枚举，用一些背包的思想。

这样时间复杂度就优化到了 $O(n^{2})$，不过有一些细节需要处理

在此是对方案1的实现：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
inline int read(){
	int num=0,ch=0;
	char c=getchar();
	while(!isdigit(c))ch|=(c=='-'),c=getchar();
	while(isdigit(c))num=(num<<1)+(num<<3)+(c^48),c=getchar();
	return ch?-num:num;
}
inline void write(int x){
	if(x<0)putchar('-'),x=-x;
	if(x>=10)write(x/10);
	putchar(x%10+'0');
}
char a[5005];
int dp[5005][5005],n,sum[5005];
signed main(){
//	freopen("python.in","r",stdin);
//	freopen("python.out","w",stdout);
	n=read();
	for(int i=1;i<=n;++i)cin>>a[i];
	dp[1][0]=1;
	for(int i=1;i<=n;++i){
		for(int j=0;j<=i;++j){
			if(a[i-1]=='f')dp[i][j]=dp[i-1][j-1];
			else{
				dp[i][j]=(dp[i][j]+sum[i-2]-sum[j-1]+mod)%mod;
			}
		}
		for(int j=0;j<=i;++j)sum[j]=(sum[j-1]+dp[i][j])%mod;
	}
	int ans=0;
	for(int i=0;i<=n;++i)ans=(ans+dp[n][i])%mod;
	write(ans);
	return 0;
}

```

---

## 作者：cqbzjyh (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF909C)

### Solution.

很显然的一道 DP 。

定义状态 $dp_{i,j}$ 为在第 $i$ 行有 $j$ 个换行的方案数。

假设第 $i-1$ 行为 $\texttt{f}$ ，那么第 $i$ 行就必须多一个换行，所以 $dp_{i,j}=dp_{i-1,j-1}$

否则第 $i-1$ 行为 $\texttt{s}$ ,此时不难推出第 $i$ 行换行个数的范围是 $j\sim i-2$ ，则 $dp_{i,j}=\sum\limits_{k=j}^{i-2}dp_{i-1,k}$ 。

此时时间复杂度为 $\mathcal O(n^3)$ ，还不够优秀。

我们可以注意到 $\sum\limits_{k=j}^{i-2}dp_{i-1,k}$ 可以用前缀和来维护。这样复杂度就降为 $\mathcal O(n^2)$ 。

### Code.

```cpp


#include <bits/stdc++.h>
#define int long long
using namespace std;
template <typename T>
void read(T &x) {
	x = 0; T f = 1;
	char c;
	c = getchar();
	while (c < '0' || c > '9') {
		if (c == '-') f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = (x << 1) + (x << 3) + c - '0';
		c = getchar();
	}
	x *= f;
} 

const int MOD = 1e9 + 7;
char a[5005];
int dp[5005][5005];
int sum[5005];
int n;
signed main() {
	read(n);
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	dp[1][0] = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= i; j++) {
			if (a[i - 1] == 'f') dp[i][j] = dp[i - 1][j - 1] % MOD;
			else {
				dp[i][j] = (dp[i][j] + sum[i - 2] - sum[j - 1] + MOD) % MOD;
			}
		}
		for (int j = 0; j <= i; j++) {
			sum[j] = (sum[j - 1] + dp[i][j]) % MOD;
		}
	}
	int ans = 0;
	for (int i = 0; i <= n; i++) {
		ans = (ans + dp[n][i]) % MOD;
	}
	printf("%lld", ans);
	return 0;
}
```

---

## 作者：qwq___qaq (赞：0)

我们分几种情况来讨论（设第 $i$ 行缩进数为 $x_i$）：

1. 上一行是 `f`

那么这一行只能添加缩进，所以 $x_i\gets x_{i-1}+1$。

2. 上一行不是 `f`

那么我们就可以在上一行之后推出若干层循环（包括 $0$），那么 $x_i\le x_{i-1}$。又因为第 $i$ 行前最多有 $i-1$ 个循环，所以 $x_i\le x_{i-1}\le i-2$。

现在，我们进入正题：设 $dp_{i,j}$ 表示当前处理第 $i$ 个语句，并且缩进数为 $j$ 时的答案。

此时，第一种情况下，状态转移方程为 $dp_{i,j}\gets dp_{i-1,j-1}$。

第二种情况下，我们可以得到 $dp_{i,j}\gets\sum\limits_{k=j}^{i-1}dp_{i-1,k}$。

那么，一层 $i$，一层 $j$，一层 $k$，时间复杂度 $O(n^3)$，远远不够。

我们可以观察 $k$，可以得到 $\sum\limits_{k=j}^{i-1}dp_{i-1,k}=\sum\limits_{k=j+1}^{i-1}dp_{i-1,k}+dp_{i-1,j}$，而 $\sum\limits_{k=j+1}^{i-1}dp_{i-1,k}=dp_{i,j+1}$，也就是说 $dp_{i,j}=dp_{i-1,j}+dp_{i,j+1}$。

因为 $n$ 个操作后最多有 $n-1$ 个缩进，所以答案即为 $\sum\limits_{i=0}^{n-1}dp_{n,i}$。

时间复杂度 $O(n^2)$，注意取模。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;//取模
int n,m,a[5005],dp[5005][5005],ans,s;
char c;
signed main(){
	cin>>n;
	for(int i=1;i<=n;++i){
		cin>>c;
		a[i]=(c=='f');
	}
	dp[0][0]=1;
	for(int i=1;i<=n;++i)
		if(a[i-1]){
			for(int j=1;j<n;++j)
				dp[i][j]=dp[i-1][j-1];//第一种情况
		} else{
			for(int j=i-1;j>=0;--j)
				dp[i][j]=(dp[i][j+1]+dp[i-1][j])%mod;//第二种情况
		}
	for(int j=0;j<n;++j)
		ans=(ans+dp[n][j])%mod;//求解答案
	cout<<ans<<endl;
	return 0;
}
```

---

