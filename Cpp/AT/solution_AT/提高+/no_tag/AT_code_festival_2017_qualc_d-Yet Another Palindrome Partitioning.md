# Yet Another Palindrome Partitioning

## 题目描述

给定一个字符串$\texttt{s}$，把$\texttt{s}$分成$N$个子串，要求每个子串中的字母经过一定的移动，会变成一个回文串（如`aab`经过一定的移动，变成了`aba`，`aba`是一个回文串），**且$N$最少**。

## 样例 #1

### 输入

```
aabxyyzz```

### 输出

```
2```

## 样例 #2

### 输入

```
byebye```

### 输出

```
1```

## 样例 #3

### 输入

```
abcdefghijklmnopqrstuvwxyz```

### 输出

```
26```

## 样例 #4

### 输入

```
abcabcxabcx```

### 输出

```
3```

# 题解

## 作者：yx666 (赞：5)

# Yet Another Palindrome Partitioning 题解
$$\text{Preface}$$

状压、位运算与哈希优化 DP。

$$\text{Description}$$

给定一个字符串 $\texttt s$，把 $\texttt s$ 分成尽量少的子串，要求每个子串中的字母经过一定的移动，会变成一个回文串（如 `aab` 经过一定的移动，变成了 `aba`，`aba` 是一个回文串），**且 $N$ 最少**（$1 \le |\texttt s| \le 2 \times 10^5$）。

请你输出满足条件的最少子串数。

$$\text{Solution}$$

考虑 DP。

（下文中 $n$ 表示 $\texttt s$ 的长度 $|\texttt s|$，$\texttt s$ 下标从 $1$ 开始。）

### Part 1：定义问题状态
定义 $dp_i$ 表示合法分割前 $i$ 个字符的最少子串数。

定义 $c(l,r)$ 表示 $s_ls_{l+1}\ldots s_r$ 是否可以组成回文串。

### Part 2：状态转移方程
$$dp_i=\min_{j=0}^i\{dp_j\}+1$$

其中 $j$ 必须满足 $c(j+1,i)=1$。

解释：从 $1\sim i$ 枚举划分点 $j$，当 $s_{j+1}s_{j+2}\ldots s_i$ 可以构成回文串（$c(j+1,i)=1$）时，更新 $dp_i=\min(dp_i,dp_j+1)$。

### Part 3：边界状态与初始化
1. 边界状态：$i=n$。

2. 初始化：$dp_i=\begin{cases}0&i=0\\\infin &\text{otherwise}\end{cases}$

### Part 4：计算顺序与答案
1. 计算顺序：$1\to n$。

2. 答案：$dp_n$。

### Part 5：时间复杂度
$O(n^2\cdot c(n))$，一个 $n$ 枚举 $i$，一个 $n$ 枚举 $j$，$c(n)$ 表示找到判断长度为 $n$ 的串是否可以组成回文串的时间复杂度。

### Part 6：优化
注意到 $O(n)$ 的 DP 无法优化，瓶颈在于枚举得到 $dp_j$ 与判断 $c(n)$ 的复杂度。

由于 $1\le n\le 2\times10^5$，所以我们期望得到 $dp_j$ 与判断 $c(n)$ 的复杂度，最差为 $O(\log n)$ 或 $O(\sqrt n)$。

#### Part 6.1：优化 $c(n)$
注意题目中：“每个子串中的字母**经过一定的移动**，会变成一个回文串”。

所以 $c(n)$ 中的判断，只需判断其是否满足：不存在或仅存在单个数量为奇数的字符，其余字符数皆为偶数。

联想到 **[找筷子](https://www.luogu.com.cn/problem/P1469)** 这道位运算好题，$c(n)$ 可以采用异或实现。

定义 $c_i$ 表示前 $i$ 个字符的异或和，其中 $a$ 映射为 $2^0$，$b$ 映射为 $2^1$，以此类推。

那么 $c(l,r)=1$ 当且仅当 $c_l\operatorname{xor} c_r=0$ 或 $2^x$，其中 $x\in[0,25]$，表示落单的字符对应的映射。

这样，$c(n)$ 可以通过前缀和优化为常数级。

#### Part 6.2：优化枚举
我们的目的是找到所有满足 $c_{j+1}\operatorname{xor} c_i=0$ 或 $2^x$ 的 $j$ 对应的 $dp_j$。

我们可以利用枚举 $x$，常数级得到 $c_{j+1}$，问题在于找到 $j$ 再找到 $dp_j$。

但我们大可不必通过 $O(n)$ 枚举找到 $j$，再通过 $j$ 找到 $dp_j$。我们只需在 $c_{j+1}$ 与 $dp_j$ 建立哈希即可，以空间换时间。

这样，找到 $dp_j$ 的时间复杂度为 $O(A)$，$A$ 表示字符总量，在本题为 $26$。

#### Part 6.3：实现
维护一个哈希表 $hash_i$，表示当前状态为 $i=c_{j+1}$ 时，所对应的最小的 $dp_j$。

对于每个 $i$，每次更新异或和 $c_i$，再枚举 $26$ 个可能的字符 $x$，获得 $c_{j+1}=c_i\operatorname{xor} 2^x$，再通过哈希更新 $dp_i=\min\{dp_j+1\}$，最后更新 $hash_{c_i}$。

总复杂度 $O(An)$，其中 $A$ 为字符总数，为 $26$。

$$\text{Code}$$

变量名与文章稍有不同：

| 代码  |  原文  |          含义          |
| :---: | :----: | :--------------------: |
|  $c$  | $hash$ | 实现状态与 DP 的哈希。 |
| $nw$  | $c_i$  |        异或和。        |

```cpp
#include<bits/stdc++.h>
using namespace std;

#define N 200005

int n,dp,c[1<<26];
string s;
signed main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	
	cin>>s;n=s.length();
	s=' '+s;
	
	memset(c,0x3f,sizeof c);
	c[0]=0;
	
	int nw=0;
	for(int i=1;i<=n;++i){
		nw^=1<<(s[i]-'a');
		
		dp=c[nw];
		for(int j=0;j<26;++j)
			dp=min(dp,c[nw^(1<<j)]);
		
		c[nw]=min(c[nw],++dp);
	}cout<<dp;
	return 0;
}
```

---

## 作者：dd_d (赞：2)

[更好的阅读体验](https://www.cnblogs.com/dd-d/p/15217595.html)
### Sol  
考虑 dp。  
首先容易发现，若一个串为回文串，那么不存在或仅存在一个数量为奇数的字符，其余字符数量皆为偶数。  
我们考虑把 $a$ 到 $z$ 这些字符转化为 $2^0$ 到 $2^{25}$，若一个子串为回文串，当且仅当这个串的异或值为 $0$ 或 $2$ 的幂。  
记 $f_i$ 表示前 $i$ 个数可以分成的最小段数，$sum_i$ 表示异或值的前缀和。  
$f_i=\min \left\{ f_j \right\} +1 \ (sum_i \ xor \ sum_j=0 \ or \ 2^x)$  
最后 $f_n$ 即为答案。  
时间复杂度 $O(26n)$
### Code  
```cpp
//LYC_music yyds!
#include<bits/stdc++.h>
#define IOS ios::sync_with_stdio(0)
#define lowbit(x) (x&(-x))
//#define int long long
using namespace std;
int read()
{
	int pos=1,num=0;
	char ch=getchar();
	while (!isdigit(ch))
	{
		if (ch=='-') pos=-1;
		ch=getchar();
	}
	while (isdigit(ch))
	{
		num=num*10+(int)(ch-'0');
		ch=getchar();
	}
	return pos*num;
}
void write(int x)
{
	if (x<0)
	{
		putchar('-');
		write(-x);
		return;
	}
	if (x>=10) write(x/10);
	putchar(x%10+'0');
}
void writesp(int x)
{
	write(x);
	putchar(' ');
}
void writeln(int x)
{
	write(x);
	putchar('\n');
}
const int N=2e5+1;
string st;
int n,sum[1<<26],dp[N],now;
signed main()
{
	IOS;
	cin>>st; n=st.length(); st=' '+st;
	memset(sum,0x3f,sizeof(sum));
	sum[0]=0;
	for (int i=1;i<=n;i++)
	{
		int x=1<<(st[i]-'a');
		now^=x;
		dp[i]=sum[now];
		for (int j=0;j<26;j++) 
			dp[i]=min(sum[now^(1<<j)],dp[i]);
		dp[i]++;
		sum[now]=min(sum[now],dp[i]);
	}
	writeln(dp[n]);
}



```

---

## 作者：Jur_Cai (赞：1)

先考虑暴力 DP 转移。

设 $dp_i$ 为到字符串第 $i$ 位最少分成几块能满足要求，很快就能推出转移方程 $dp_i=Min_{j=0}^i \{ {dp_j} \} +1$ 且满足 $s_{j+1}$ 到 $s_i$ 能构成回文串。
能否构成回文串的方法也很简单，只要这段区间内个数为奇数的字母不超过 1 个，前缀和处理一下即可。

但是 $O(n^2)$ 的时间复杂度肯定是过不去的，怎么办呢？**状压！**

把 $a$ ~ $z$ 的个数压入一个二进制数中，由于只要考虑字母个数的奇偶性，所以只需要一个 26 位的二进制数作为状态，加入字符改变奇偶性可用异或实现，前缀和处理一下状态。设 $dp_k$ 为状态为 $k$ 时的答案，$sum_i$ 为前 $i$ 位的状态，转移方程 $dp_{sum_i}=Min_{j=0}^{25} \{dp_{sum_{i-1}} \oplus 2^j\}+1$ （$j$ 可看为枚举的字符）。

实现见代码
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define INF 0x3f3f3f3f
using namespace std;
char s[200005];
long long sum[200005];
int dp[70000000];
int main() {
	scanf("%s",s+1);
	int len=strlen(s+1);
	for(int i=1;i<=len;i++)
		sum[i]=sum[i-1]^(1<<(s[i]-'a'));
	memset(dp,INF,sizeof(dp));
	dp[0]=0,dp[1<<(s[1]-'a')]=1;
	for(int i=2;i<=len;i++)
		for(int j=0;j<26;j++) 
			dp[sum[i]]=min(dp[sum[i]],dp[sum[i]^(1<<j)]+1);
	dp[0]=1;
	cout<<dp[sum[len]];
	return 0;
}
```

---

## 作者：AC_love (赞：0)

设 $f(i)$ 表示 $1 \sim i$ 这个子串的最小的分割次数，考虑如何转移。

枚举一个 $j$，如果 $[j + 1, i]$ 这一段字符串可以是回文串，那么 $f(j)$ 可以转移到 $f(i)$。

转移方程：

$$f(i) = \min(f(j) + 1)$$

这样做至少是 $O(n^2)$ 的，能优化吗？

我们发现：一个字符串可以在交换字母之后成为一个回文串，当且仅当这个字符串最多只有一种字母出现了奇数次。

我们在转移的过程中用一个二进制数 $b(i)$ 维护一下当前 $26$ 个字母出现的次数的奇偶性，我们发现符合条件的 $j$ 一定满足：

$$g(i) \oplus g(j) = 0$$

或：

$$g(i) \oplus g(j) = 0\cdots010\cdots0$$

一共只有 $27$ 种情况。

我们只需要分别对于每种情况找到最小的 $g(j)$ 即可。

对于某种情况，怎么找最小的 $g(j)$ 呢？

可以利用前缀和的思想，直接维护一个 $h(g(j))$ 表示 $g(j)$ 情况的最小值，由于 $g(j)$ 可能很大，但可能存在的情况数不会很多，我们可以用 `map` 来存。

复杂度 $O(27n \log n)$，其中 $\log$ 来自 `map`。

[code](https://atcoder.jp/contests/code-festival-2017-qualc/submissions/59622505)

---

## 作者：凤凰工作室 (赞：0)

## Yet Another Palindrome Partitioning 题解

### 题目大意

> 给出一个字符串，求把这个字符串划分成最少的小段，使每个小段都可以经过字母重组后为回文串。

### 题目分析

如果暴力的话，需要 DFS 段数、每一段的左节点、右节点，以及判断是否为回文串，时间复杂度在 $O(|S|^{|S|})$ 左右。

但是本题需要将字符串划分成若干子串，那么就可以考虑 DP。那么可以写出一个状态转移方程：

$$dp_i=\min(dp_j+1) ,j \leq i,S_{i\sim j}为回文串$$

其中 $dp_i$ 表示 $S$ 的前 $i$ 个字符被划分成满足题意的子串最少的划分数，$i$ 是当前这段的右节点，$j$ 是需要匹配的左节点。要使答案最小，肯定是取 $\min$ 值。

时间复杂度 $O(|S|^3)$ (这里判断回文还有线性的时间复杂度)。

那么考虑优化：

#### 优化 1

首先判断回文的线性复杂度是非常可恶的，必须优化掉。

传统的判断回文是将字符串左右对比，那么有没有一种办法可以 $O(1)$ 对比呢？我们可以使用异或进行优化。根据异或的性质,$a \oplus b \oplus b=a$，那么左右相同的字符就会抵消掉。为了不出现冲突（即两个不同的字符异或后有一部分变了），需要给每一个字符一个特定的值，将 `a` 赋 $2^0$，给 `b` 赋 $2^1$ $......$

那么回文串就有两种情况：

1.例如 `abcba` 一样的，奇数个字符的回文串，异或优化后会剩下中间的字符（即剩下 $2^{x}$）。

2.例如 `abba` 一样的，偶数个字符的回文串，异或优化后什么也不剩了（即剩下 0）。

由于本题只考虑小写英文字母，时间复杂度 $O(26|S|^2)$

#### 优化 2

有一点记忆化的思想，将 $dp_i$ 的值存储起来，每次更新更优的，就可以优化取 $\min$ 值的时间。

最后还需要用 bitset 优化 $dp$ 数组，否则要爆（bitset 可以 $O(1)$ 对整个数组进行位运算）。

### 代码放上来

```cpp
#include<bits/stdc++.h>
using namespace std;

string s;
int dp[200005];
int xop[200005];//存储每个字符值的前缀异或
int w[1<<26];//存储每个字符的最优 dp 值

int main(void)
{
    memset(w,0x7f,sizeof(w));
    w[0]=0;
    cin>>s;
    for(int i=0;i<s.length();i++)
        xop[i]=(i==0?1<<s[i]-'a':xop[i-1]^(1<<s[i]-'a'));//预处理前缀异或值
    for(int i=0;i<s.length();i++)
    {
        dp[i]=w[xop[i]];
        for(int j=0;j<26;j++)
            dp[i]=min(dp[i],w[xop[i]^(1<<j)]);
        w[xop[i]]=min(w[xop[i]],dp[i]);//更新更优的 dp 值
        dp[i]++;
    }
    cout<<dp[s.length()-1];
    return 0;
}
```

本题完结散花

Solution By @凤凰工作室

---

