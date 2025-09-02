# Sereja and Squares

## 题目描述

Sereja在平面上画了n个点，第i点(1<=i<=n)坐标为(i,0)。然后Seraja在每个点上标记了一个大写或小写的英文字母。Seraja不喜欢字母'x'，所以她没有用'x'标记任何点。Seraja认为，当标记方式满足以下条件时，这些点就被“美丽地”标记了：

1.所有点能够被分成若干点对，每个点在且仅在一个点对中；
2.在每个点对中，横坐标较小的点被小写字母标记，横坐标较大的点被同一字母的大写形式标记；
3.以每组点对连线为对角线作正方形，所有作出的正方形的边没有交点且没有顶点重合；

小Petya擦去了标记在点上的一些小写或大写字母。现在Seraja想知道有几种方式标记被擦去字母的点，能够使所有点被“美丽地”标记了。

## 样例 #1

### 输入

```
4
a???
```

### 输出

```
50
```

## 样例 #2

### 输入

```
4
abc?
```

### 输出

```
0
```

## 样例 #3

### 输入

```
6
abc???
```

### 输出

```
1
```

# 题解

## 作者：ywy_c_asm (赞：10)

~~没想到吧，这题正解居然是$O(n^2)$暴力卡常……~~

首先这题有个坑点：

![](https://cdn.luogu.com.cn/upload/pic/58903.png)

对，没错，**输入里没有大写字母！**

那么我们的题意就变成了现在只有一些左括号，然后你要把‘？’填成左右括号使得最终是合法的括号序列。同时已有的这些小写字母是啥其实也没有什么关系。

然后有个显然的$O(n^2)$暴力是$dp[i][j]$前$i$个有$j$个左括号还没匹配，然后如果这一位是‘？’就$dp[i][j]=25dp[i-1][j-1]+dp[i-1][j+1]$，否则$dp[i][j]=dp[i-1][j-1]$。

这样显然是过不去的，但是我们可以换另外一个~~常数更小~~的暴力。

我们发现合法的括号序列有个比较显然的性质：**如果对任意$i$都满足在这之前的右括号$\le\lfloor\frac i 2\rfloor$的话，那么这个括号序列是合法的**。那么我们可以在状态里记右括号有多少，这样每次就只需要把$j$循环到$\lfloor\frac i 2\rfloor$就行了，然后现在的转移是，如果这一位是‘？’，$dp[i][j]=dp[i-1][j]*25+dp[i-1][j-1]$，否则$dp[i][j]=dp[i-1][j]$，我们发现后者可以直接用滚动数组，并不用做任何转移，那么只需要在‘？’时做一遍$\lfloor\frac i 2\rfloor$的循环即可。

~~然后就卡常卡的能过了……~~

上代码~

```cpp
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#include <iostream>
#include <cstdio>
#include <cstring>
#define int unsigned int
using namespace std;
namespace ywy {
	int dp[200001];
	char str[200002];
	void ywymain() {
	    int n;
	    cin >> n;
	    if (n & 1) {
	        cout << 0 << endl;
	        return;
	    }
	    scanf("%s", str + 1);
	    dp[0] = 1;
	    for (register int i = 1; i <= n; i++) {
	        if (str[i] == '?') {
	            for (register int j = i / 2; j >= 1; j--) dp[j] = dp[j] * 25 + dp[j - 1];
	            dp[0] = dp[0] * 25;
	        }
	    }
	    cout << dp[n / 2] << endl;
	}
}
signed main() {
    ywy::ywymain();
    return (0);
}
```

---

## 作者：Plus_Ultra (赞：6)

### 题解：

这道题虽然简短，但是思维难度并不小.

解题思路：

左括号与右括号的个数都应该是 n / 2.若n为奇数，则无解.

取模：因为对 4294967296 即 2 ^ 32 取模，我们可以用 unsigned int，但不要所有数都开这个东西，常数太大会TLE.

问题转换：我们可以把小写字母看作左括号，大写字母看作右括号，那么要求正好配对，也就是求括号序列匹配问题，有 25 种括号(没有 x/X ).

首先我们考虑 n ^ 2 且只有一种括号的传统括号序列做法.

  - 我们设状态 f(i, j) 表示已经考虑了前i个数，现在还有j个左括号没有匹配的方案数.
  
  - 则可以有两种转移情况：1.第 i + 1 个数是左括号，则可以转移为 f(i + 1,j + 1). 2.第 i + 1 个数是问号，则可以转移为 f(i + 1,j - 1)与 f(i + 1,j + 1).
  
我们再来看这道题的情况.这与上面传统情况的不同之处是他擦去了所有的右括号以及一部分的左括号.

- 令 f(i, j) 表示 假设括号只有一种，前 i 个数里面，填了 j 个右括号的方案数.
  
- 第 i 个数是问号.1.当前填左括号: f(i, j) += af f(i - 1, j) 2.当前填右括号: f(i, j) += f(i - 1, j - 1).
 
- f(n, n / 2)即为答案
  
- 利用一种情况的方案数计算多种括号的方案数.
  
  - 我们开文章一开始就说了，我们有25种括号，且左括号个数是 n / 2 个.
    
  - 假设序列中已有 p 个左括号，那么 ?(即要填的数的个数) 里面就有 n / 2 - p 个左括号.
    
  - 每一个左括号有 25 种选择，那么 ans = 25 ^ (n / 2 - q) * f(n, n / 2).
  
我们又可以发现，第一位状态可以去掉，则本题就愉快的AC了.

还有一点，对于当前的 j 只需要从合法的方案即i / 2开始倒序枚举即可

下面上代码(我知道各位大佬也不需要代码)：

```
#include<iostream>

#define N 100005
#define LL unsigned int

using namespace std;

int n,p;
LL f[N<<1]={1},ans=1; // 全部开unsigned是要TLE的米多利亚少年.
char c[N];

int main()
{
	cin>>n;
	
	if(n&1)  cout<<"0"<<endl; // n为奇数
	else
	{
		int m=n>>1;cin>>c+1;//最多有m个右括号or左括号.
		for(int i=1;i<=n;i++)
		if(c[i]=='?')
			for(int j=i>>1;j>=i-m&&j;j--)  
			f[j]+=f[j-1];
		else  p++; // 计算当前已有的左括号个数
		for(int i=1;i<=m-p;i++)  ans=ans*25; // 在剩余的左括号中，每个有25种可能性.
		cout<<(LL)ans*f[m]<<endl;  
	}
	
	return 0;
}
```

### [Plus Ultra!!!](https://www.luogu.org/blog/OnePunchManGO/)

祝大家CSP2019 RP++！！！

  

---

## 作者：wsyhb (赞：3)

## 前言

Hint：

1. 题目的第三个条件等价于这 $\dfrac{n}{2}$ 对字符满足括号匹配。
1. 本题输入字符串仅包含小写字母和问号。（这是题目中的已知条件，但不少人会看漏）
1. 这道题很卡常：答案 $\bmod \; 2^{32}$，可以使用 unsigned int。但即使是这样，时限仍为 2s（表面上是 4s，但 CF 老题的用时会被乘 $2$）。
1. 暴力出奇迹！

## 题解

~~由前言中的 Hint 不难想到解法，题解略。~~

容易想到一个 $O(n^2)$ 的 DP：

设 $f_{i,j}$ 表示考虑前 $i$ 个字符，当前有 $j$ 个左括号未匹配。

转移方程如下：

$$f_{i,j}=\begin{cases}
25 \cdot f_{i-1,j-1}+f_{i-1,j+1} \quad (S_i=\texttt{?})\\
f_{i-1,j-1} \quad (S_i \neq \texttt{?})
\end{cases}$$

其中 $S_i$ 表示输入字符串中的第 $i$ 个字符，且 $f_{0,0}=1$。

说明：

1. 当 $S_i=\texttt{?}$ 时，有两种情况：
	- $S_i$ 为小写字母：由于不能包含 `x`，共 $25$ 种选择。由 $f_{i-1,j-1}$ 转移而来。
	- $S_i$ 为大写字母：由于要与最近的一个左括号相对应，共 $1$ 种选择。由 $f_{i-1,j+1}$ 转移而来。
1. 当 $S_i \neq \texttt{?}$ 时，由 $f_{i-1,j-1}$ 转移而来。

使用滚动数组即可做到 $O(n)$ 的空间复杂度。

然后根据前人的经验，这道题的正解就是这个时间复杂度为 $O(n^2)$ 的东西，因此唯一剩下的任务是卡常！

其实只需**维护当前有值且合法的左右端点**即可卡过，具体实现见代码。（不用 register 和手动 O2 等奇技淫巧就能过）

## 代码

注：请不要尝试用额外的循环清空滚动数组，那大概率会 T 飞。

``` cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int max_n=1e5+5;
char S[max_n];
const int max_R=5e4+5;
unsigned int dp[2][max_R];
int main()
{
	int n;
	scanf("%d%s",&n,S+1);
	dp[0][0]=1;
	int L=0,R=0;
	for(int i=1;i<=n;++i)
	{
		int y=i&1,x=y^1;
		if(S[i]=='?')
		{
			if(L==0)
				dp[y][1]=dp[x][0]*25;
			else
				dp[y][L-1]=0;
			dp[y][L]=0;
			for(int j=max(L,1);j<=R;++j)
			{
				dp[y][j+1]=dp[x][j]*25;
				dp[y][j-1]+=dp[x][j];
			}
			L=max(L-1,0),R=min(R+1,n-i);
		}
		else
		{
			for(int j=L;j<=R;++j)
				dp[y][j+1]=dp[x][j];
			++L,R=min(R+1,n-i);
		}
		while(L<=R&&!dp[y][L])
			++L;
		while(L<=R&&!dp[y][R])
			--R;
		if(L>R)
		{
			puts("0");
			return 0;
		}
	}
	printf("%u\n",dp[n&1][0]);
	return 0;
}
```

## 彩蛋

Read the following comments on the problem CF314E, and then answer questions.

![](https://cdn.luogu.com.cn/upload/image_hosting/15naebki.png)

1. Do you think it is suitable to make such a problem? Why or why not?
1. Do you think it is fair to put such a problem in a contest? Why or why not?

---

## 作者：RockyYue (赞：1)

### 题意

给定一个长度为 $n$ 字符串 $s$。每位为小写字母或 ```?```。要求将所有 ```?``` 位填充小写字母或大写字母，使得：

- $s$ 中不含 ```x``` 或  ```X```。
- 将小写字母看做 ```(```，大写看作 ```)```，则构成合法括号序，且一个小写字母在括号序中与对应大写字母配对（如 ```a``` 和 ```A``` 配对）。

求填充方案数对 $4294967296$ 取模。

其中 $n\le 10^5$。

### 题解

首先声明，正解是 $O(n^2)$。

若 $n$ 为奇数，不可能为若干对，故无解，以下考虑 $n$ 偶数。

先不考虑具体字母，只是看做左右括号。括号序列计数题，想到 DP，设 $f_{i,j}$ 为考虑前 $i$ 位，目前 $j$ 个左括号未配对，则：

- 当前位为小写字母：$f_{i,j}=f_{i-1,j-1}$。
- 当前位为问号：$f_{i,j}=f_{i-1,j-1}+f_{i-1,j+1}$。

至此，不考虑具体字母答案为 $f_{n,0}$。

若一位填充后为大写字母，其值完全取决于对应的小写字母，故只考虑小写字母取值即可，设 $t$ 为初始未确定的小写字母个数（即 $\frac{n}{2}$ 减去 $s$ 中小写字母个数），答案为 $f_{n,0}\times 25^t$。

卡常部分不过多赘述。

---

