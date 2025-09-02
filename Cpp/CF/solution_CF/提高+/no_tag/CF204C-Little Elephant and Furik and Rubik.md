# Little Elephant and Furik and Rubik

## 题目描述

Little Elephant loves Furik and Rubik, who he met in a small city Kremenchug.

The Little Elephant has two strings of equal length $ a $ and $ b $ , consisting only of uppercase English letters. The Little Elephant selects a pair of substrings of equal length — the first one from string $ a $ , the second one from string $ b $ . The choice is equiprobable among all possible pairs. Let's denote the substring of $ a $ as $ x $ , and the substring of $ b $ — as $ y $ . The Little Elephant gives string $ x $ to Furik and string $ y $ — to Rubik.

Let's assume that $ f(x,y) $ is the number of such positions of $ i $ ( $ 1<=i<=|x| $ ), that $ x_{i}=y_{i} $ (where $ |x| $ is the length of lines $ x $ and $ y $ , and $ x_{i} $ , $ y_{i} $ are the $ i $ -th characters of strings $ x $ and $ y $ , correspondingly). Help Furik and Rubik find the expected value of $ f(x,y) $ .

## 说明/提示

Let's assume that we are given string $ a=a_{1}a_{2}...\ a_{|a|} $ , then let's denote the string's length as $ |a| $ , and its $ i $ -th character — as $ a_{i} $ .

A substring $ a[l...\ r] $ $ (1<=l<=r<=|a|) $ of string $ a $ is string $ a_{l}a_{l+1}...\ a_{r} $ .

String $ a $ is a substring of string $ b $ , if there exists such pair of integers $ l $ and $ r $ $ (1<=l<=r<=|b|) $ , that $ b[l...\ r]=a $ .

Let's consider the first test sample. The first sample has $ 5 $ possible substring pairs: ("A", "B"), ("A", "A"), ("B", "B"), ("B", "A"), ("AB", "BA"). For the second and third pair value $ f(x,y) $ equals $ 1 $ , for the rest it equals $ 0 $ . The probability of choosing each pair equals ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF204C/9afdc5b93ef27ce72945708dcc66dfa8da5502ae.png), that's why the answer is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF204C/9afdc5b93ef27ce72945708dcc66dfa8da5502ae.png) $ · $ $ 0 $ $ + $ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF204C/9afdc5b93ef27ce72945708dcc66dfa8da5502ae.png) $ · $ $ 1 $ $ + $ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF204C/9afdc5b93ef27ce72945708dcc66dfa8da5502ae.png) $ · $ $ 1 $ $ + $ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF204C/9afdc5b93ef27ce72945708dcc66dfa8da5502ae.png) $ · $ $ 0 $ $ + $ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF204C/9afdc5b93ef27ce72945708dcc66dfa8da5502ae.png) $ · $ $ 0 $ $ = $ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF204C/9c850bc21c4ea1d02a70f568adcdf814d6e0ee9d.png) $ = $ $ 0.4 $ .

## 样例 #1

### 输入

```
2
AB
BA
```

### 输出

```
0.400000000
```

## 样例 #2

### 输入

```
3
AAB
CAA
```

### 输出

```
0.642857143
```

# 题解

## 作者：XL4453 (赞：2)

### 注意：

子串是连续的，子序列是不连续的。这道题用的是子串。

---
### 解题思路：

考虑计算每一对相等字符的贡献，然后用其除以所有可能的子串个数。

---
#### 求所有可能的子串个数：

由于子串长度相等，考虑分别计算每一种长度的子串数目人后累加。

对于一个长度 $i$，可能起点一共有 $n-i+1$ 种，由于是两串，总共有 $(n-i+1)^2$ 种。

然后累加，总方案就是：$\sum_{i=1}^{n}(n-i+1)^2$，不太好看，转换为：$\sum_{i=1}^{n}i^2$，这样就是一个平方求和。
立刻有：$\sum_{i=1}^{n}i^2=\dfrac{n(n+1)(2n+1)}{6}$。

具体证明方法有很多，这里不赘述。

---
#### 求每一对相等字符的贡献

若现在有一对相等的字符，一个在 $i$，一个在 $j$，不妨设 $i<j$（其实这里并不关心两个字符到底哪个在 $x$ 哪个在 $y$，直接根据位置决定就行了）。

那么可以选择从 $[1,i]$ 之间的任意一个位置开始，$[j,n]$ 之间的任意一个位置结束，由于之前的 $i<j$，那么这样一定可以在另一个字符串中找到相应的字符长度与之对应。

但如果直接这样求复杂度是 $O(n^2)$，无法接受，所以考虑用一个前缀和一个后缀和维护一下每一个字符在前面的贡献和在后面的贡献。

---
### 代码：

```cpp
#include<cstdio>
using namespace std;
#define ULL unsigned long long
int n;
ULL fr[200005][26],ba[200005][26];
char a[200005],b[200005];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		a[i]=getchar();
		while(a[i]<'A'||a[i]>'Z')a[i]=getchar();
		fr[i][a[i]-'A']=i;ba[i][a[i]-'A']=n-i+1;
	}
	for(int i=1;i<=n;i++){
		b[i]=getchar();
		while(b[i]<'A'||b[i]>'Z')b[i]=getchar();
	}
	for(int i=1;i<=n;i++)for(int j=0;j<=25;j++)fr[i][j]+=fr[i-1][j];
	for(int i=n;i>=1;i--)for(int j=0;j<=25;j++)ba[i][j]+=ba[i+1][j];
	double ans=0;
	for(int i=1;i<=n;i++){
		ans+=(ULL)i*ba[i+1][b[i]-'A'];
		ans+=fr[i][b[i]-'A']*(ULL)(n-i+1);
	}
	double E=ans/((double)n*(double)(n+1)*(double)(2*n+1)/6.0);
	printf("%.8lf",E);
	return 0;
}
```


---

## 作者：YCS_GG (赞：1)

先推一下式子：

$E(F(x,y))=\sum_{x,y} P_i\times F(x,y)$

因为等概率随机，所以所有$P_i$均相等，记作$P$，也就是所有合法的$x,y$的个数

容易发现其实$P=\dfrac{1}{\sum^n_i i^2}=\dfrac{n(n+1)(2*n+1)}{6}$
$F(x,y)=\sum^{len}_{i=0}[x_i=y_i]$

$E(F(x,y))=P\times\sum_{x,y}\sum^{len}_{i=0}[x_i=y_i]$

所以本质上就是求所有子串中相同位置字符一样的个数

那么我们能枚举字符$c$考虑所有$x_i=c$和$y_i=c$的贡献

我们想对于$c$来说如果$x$中有一个位置在$i$，$y$中位置在$j$

那么从$[1,i]$中作为$x$字串起点，$[j,n]$中作为$y$字串结尾都是合法的

假设$i<j$那么贡献就是$i*(n-j+1)$，反之同理

这样的复杂度是$O(n^2)$，可以用前缀后缀和扫一遍来记录两个字符串中的某个字符所带来的贡献

最后累加乘$P$即可

注意会爆$ull$，因为精度只要$10^{-6}$所以用double存

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
const int N = 200100;
char a[N], b[N];
unsigned long long n;
unsigned long long cnt_forward[27][N], cnt_backward[27][N];
int main() {
    cin >> n;
    cin >> a + 1;
    cin >> b + 1;
    for (int i = 1; i <= n; i++) {
        cnt_forward[a[i] - 'A'][i] = i;
    }
    for (int i = n; i >= 1; i--) {
        cnt_backward[a[i] - 'A'][i] = n - i + 1;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < 26; j++) {
            cnt_forward[j][i] += cnt_forward[j][i - 1];
        }
    }
    for (int i = n; i >= 1; i--) {
        for (int j = 0; j < 26; j++) {
            cnt_backward[j][i] += cnt_backward[j][i + 1];
        }
    }
    double sum = 0;
    for (int i = 1; i <= n;i++){
        char c = b[i] - 'A';
        sum += cnt_forward[c][i] * (n - i + 1);
        sum += cnt_backward[c][i + 1] * i;
    }
    double ans = (double)sum / (double)(n * (n + 1) * (2 * n + 1) / 6.0);
    printf("%.9lf", ans);
    return 0;
}
```





---

## 作者：Dea_He (赞：0)

### 题目大意

枚举 $A$ 的子串 $x$ 和 $B$ 的子串 $y$，求 $|x_i|$ 等于 $|y_i|$ 的个数的期望。

### 解题思路

考虑正难则反，枚举 $x_i$ 等于 $y_j$ 在所有可能的子串匹配中的贡献。即 $Ans = \sum_{i = 1}^{n} \sum_{j=1}^n \min(i,j) \times \min(n-i+1,n-j+1)，A[i] = B[j]$。复杂度 $O(N^2)$。

前缀/后缀桶优化，设 $pre[i][c]$ 表示在 $1$ 到 $i$ 中，$B[i] = c$ 的 $i$ 的和，后缀类比，为 $(n-i+1)$ 的和。答案转化为 $Ans = \sum_{i = 1}^{n} i \times suf[i][A[i]]+(n-i+1) \times pre[i-1][A[i]]$。

附代码。


```cpp
#include<bits/stdc++.h>

#define ll long long
#define LL __int128

using namespace std;

namespace hwq
{
	const int MAXN=2e5+5;
	
	int n;
	
	ll f[MAXN],pre[MAXN][30],suf[MAXN][30];
	
	char s[MAXN],t[MAXN];
	
	inline double Solve()
	{
		for (int i=1; i<=n; i++)
		{
			for (int j=0; j<26; j++) pre[i][j]=pre[i-1][j];
			pre[i][t[i]-'A']+=i;
		}
		for (int i=n+1; i>=1; i--)
		{
			for (int j=0; j<26; j++) suf[i][j]=suf[i+1][j];
			suf[i][t[i]-'A']+=n-i+1;
		}
		LL ans=0;
		for (int i=1; i<=n; i++)
		{
			ans+=1ll*i*suf[i][s[i]-'A']+1ll*(n-i+1)*pre[i-1][s[i]-'A'];
		}
		return 1.0*ans/(1ll*n*(n+1)*(2*n+1)/6);
	}
	
	int main()
	{
		scanf("%d",&n);
		scanf(" %s %s",s+1,t+1);
		printf("%.8lf",Solve());
		return 0;
	}
}
int main()
{
	hwq::main();
	return 0;
}
/*
*/
```

---

## 作者：skyskyCCC (赞：0)

## 前言。
题意简述：给定两个长度均为 $n$ 的字符串 $a$ 和 $b$。我们定义两个长度均为 $m$ 的字符串 $s$ 和 $t$ 的函数关系为 $f\left(s,t\right)=\sum_{i=1}^m\left[s_i=t_i\right]$。求问随机分别选取 $a$ 和 $b$ 中的两个子串 $s$ 和 $t$ 是 $f\left(s,t\right)$ 的期望值。

这是一道奇奇怪怪分析题。注意题意简述中的式子题目中并没有给到，根据原来的题意化简一下也不难得到。
## 分析。
求概率的话一般很容易先考虑期望，比如动态规划。但是对于这种题，我们发现选取是需要分别考虑子串的，所以我们断定这道题绝不是概率题。化简式子可以得到前言中的式子。

暴力求解的做法很显然，枚举 $a$ 和 $b$ 中的所以子串，然后在子串中枚举所有的位置，根据 $f$ 函数的定义，暴力累加答案即可。时间复杂度是 $O\left(n^2\right)$ 的样子。我们通过暴力尝试，又因为对答案做出贡献的一定是相同的字符，所以我们考虑先处理出来两个字符串中相同的部分，然后判断是不是在子串中的相同位置即可。换言之，这两个字符左边被选定的字符一定要同样多，右边也要一样多，这样才能对答案产生贡献。

我们不妨看一组例子：
```
s1:abba
s2:baab
```
我们如果想固定 $s_1$ 中的第一个字符 $a$ 作为标准，那么如果我们想让它和 $s_2$ 中的第一个 $a$ 进行配对，那么显然我们必须在 $s_2$ 的第一个 $b$ 之后进行分割，所以这两个我们需要进行配对的字符前面的字符个数均为 $0$ 个。同理，如果我们对于 $a_1$ 中的第二个 $b$ 进行配对，那么我们想让其和 $s_2$ 的第二个 $b$ 配对则它前面至少需要 $2$ 个字符。

我们发现，每次在子串左边中最多的字符数量，只与最靠左的字符能不能与另一个字符串中的子串配对有关。相应的，每次在子串右边中最多的字符的数量只与最靠右的字符有关。即子串中的字符位置取决于另一个与它配对的字符在另一个子串中的位置。也就是说，我们可以枚举最靠右的字符，再去计算和那些在它左侧的字符对答案做出贡献的字符。进一步我们可以推论：答案的贡献于该字符的下标有关，具体来说，我们设这个字符的下标为 $i$ 则每个字符的贡献只和另一个字符串中下标 $\leq i$ 的字符的下标之和有关。

这样我们直接采用累加和的方式，便可以在 $O\left(n\right)$ 中解决问题。可能的子串数量可以采用设的方法。我们设 $i$ 为子串的长度，则起点有 $n-i+1$ 中可能，两个字符串就是 $\left(n-i+1\right)^2$ 种可能。累加就是 $\sum_{i=1}^n\left(n-i+1\right)^2$ 的形式，化简可以得到 $\sum_{i=1}^ni^2=\frac{n\times\left(n+1\right)\times\left(2\times n+1\right)}{6}$ 的样子，这就是所有的方案。

代码如下，仅供参考：
```
#include<cstdio>
#include<iostream>
using namespace std;
int n;
char s1[200005],s2[200005];
double ans;
double a[300],b[300];
int main(){
    cin>>n;
    for (int i=1;i<=n;i++){
    	cin>>s1[i];
	}
	for (int i=1;i<=n;i++){
		cin>>s2[i];
	}
    for(int i=1;i<=n;i++){
        b[s2[i]]+=i;
        ans+=1LL*(n-i+1)*(a[s2[i]]+b[s1[i]]);
        a[s1[i]]+=i;
    }
    ans=6.0*ans/n/(n+1)/(n*2+1);
    printf("%.10lf\n",ans);
    return 0;
}
```
## 后记。
大家如有疑问，可以在评论区提出，我会尽力解答的。

---

