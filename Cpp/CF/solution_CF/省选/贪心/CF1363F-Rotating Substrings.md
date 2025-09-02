# Rotating Substrings

## 题目描述

You are given two strings $ s $ and $ t $ , each of length $ n $ and consisting of lowercase Latin alphabets. You want to make $ s $ equal to $ t $ .

You can perform the following operation on $ s $ any number of times to achieve it —

- Choose any substring of $ s $ and rotate it clockwise once, that is, if the selected substring is $ s[l,l+1...r] $ , then it becomes $ s[r,l,l + 1 ... r - 1] $ . All the remaining characters of $ s $ stay in their position. For example, on rotating the substring $ [2,4] $ , string "abcde" becomes "adbce".

A string $ a $ is a substring of a string $ b $ if $ a $ can be obtained from $ b $ by deletion of several (possibly, zero or all) characters from the beginning and several (possibly, zero or all) characters from the end.

Find the minimum number of operations required to convert $ s $ to $ t $ , or determine that it's impossible.

## 说明/提示

For the $ 1 $ -st test case, since $ s $ and $ t $ are equal, you don't need to apply any operation.

For the $ 2 $ -nd test case, you only need to apply one operation on the entire string ab to convert it to ba.

For the $ 3 $ -rd test case, you only need to apply one operation on the entire string abc to convert it to cab.

For the $ 4 $ -th test case, you need to apply the operation twice: first on the entire string abc to convert it to cab and then on the substring of length $ 2 $ beginning at the second character to convert it to cba.

For the $ 5 $ -th test case, you only need to apply one operation on the entire string abab to convert it to baba.

For the $ 6 $ -th test case, it is not possible to convert string $ s $ to $ t $ .

## 样例 #1

### 输入

```
6
1
a
a
2
ab
ba
3
abc
cab
3
abc
cba
4
abab
baba
4
abcc
aabc```

### 输出

```
0
1
1
2
1
-1```

# 题解

## 作者：一扶苏一 (赞：14)

## 【DP】CF1363F Rotating Substrings

### Description

给定两个长度为 $n$ 的字符串 $s$，$t$。定义一次操作为选择 $s$ 的一个子串 $s_{l, l +1, \dots, r}$，然后将之修改为 $s_{r, l, l + 1, l + 2, \dots, r - 1 }$。请求助使 $s$ 与 $t$ 相等的最小操作次数。无解输出 $-1$。

多组数据，$\sum n \leq 2000$，$s, t$ 中只有小写字母。

### Analysis

首先如果 $s$ 和 $t$ 中，各个字母出现的次数都相同，则显然可以凑数解，否则显然无解。

考虑一次操作的本质是，我们可以任选 $s$ 中的一个字符，将之**向前**移动任意个位置。我们要最小化选择的字符数。

考虑 dp。设 $f_{i, j}$ 是 $s$ 长度为 $i$ 的前缀，插入 $i$ 后面的若干个字符后，等于 $t$ 长度为 $j$ 的前缀的最小花费。这里要求 $i \leq j$。转移如下：

1. 可以不让 $s_i$ 与 $t_j$ 匹配，而是把 $s_i$ 向前移动，花费 $1$，转移为 $f_{i, j} = f_{i - 1, j} + 1$。
2. 若 $s_i  = t_j$，那么可以直接令二者匹配，转移为 $f_{i, j} = f_{i - 1, j - 1}$。
3. 若 $i$ 的后面有“富余”的字符 $t_j$，那么可以从 $i$ 后面抽出一个等于 $t_j$ 的字符放在这里，与 $t_j$ 匹配，转移为 $f_{i, j} = f_{i, j - 1}$。需要注意的是，这条转移的花费会在后面的某个位置在第一条转移被计算，所以这里不需要计算花费。

三种转移取最小值即可。时间复杂度 $O(n^2)$。

### Code

```cpp
namespace Fusu {

const int maxn = 2003;
const int maxt = 26;

int T;
int n;
int cnt[2][maxn][maxt], f[maxn][maxn];
char s[maxn], t[maxn];

void Main() {
  for (qr(T); T; --T) {
    qr(n);
    qrs(s + 1); qrs(t + 1);
    for (int i = 1; i <= n; ++i) {
      for (int j = 0; j < maxt; ++j) {
        for (int t = 0; t < 2; ++t) {
          cnt[t][i][j] = cnt[t][i - 1][j];
        }
      }
      ++cnt[0][i][s[i] - 'a'];
      ++cnt[1][i][t[i] - 'a'];
    }
    bool flg = false;
    for (int i = 0; i < maxt; ++i) if (cnt[0][n][i] != cnt[1][n][i]) {
      puts("-1");
      flg = true;
      break;
    }
    if (flg) continue;
    memset(f, 0x3f, sizeof f);
    for (int i = 0; i <= n; ++i) f[0][i] = 0;
    for (int i = 1; i <= n; ++i) {
      for (int j = i; j <= n; ++j) {
        f[i][j] = f[i - 1][j] + 1;
        if (s[i] == t[j]) f[i][j] = std::min(f[i][j], f[i - 1][j - 1]);
        if (cnt[0][i][t[j] - 'a'] < cnt[1][j][t[j] - 'a']) {
          f[i][j] = std::min(f[i][j], f[i][j - 1]);
        }
      }
    }
    qw(f[n][n], '\n');
  }
}

} // namespace Fusu
```



---

## 作者：zifanwang (赞：13)

[题目传送门](https://www.luogu.com.cn/problem/CF1363F)

首先很容易发现如果两个字符串的字符集相同，那么一定可以在 $n$ 次操作内使 $s$ 与 $t$ 相等。

考虑保留尽量多的字符不动，那么操作次数就是 $n$ 减去这个最大值。

考虑一个 $s$ 与 $t$ 的公共子序列满足什么条件可以不动。发现 $s$ 中一个不动的字符前面的所有字符不可能移到这个不动的字符后面，所以只需要满足公共子序列中，每一项在 $s$ 中对应的字符前面的字符集包含于在 $t$ 中对应的字符前面的字符集即可。

那么答案就是 $n$ 减去满足上述条件的最长公共子序列的长度，直接 dp 即可，时间复杂度 $O(n^2)$。

参考代码：
```cpp
#include<bits/stdc++.h>
#define mxn 2003
#define rep(i,a,b) for(int i=a;i<=b;++i)
#define drep(i,a,b) for(int i=a;i>=b;--i)
using namespace std;
int T,n,r,c[26],p[mxn],f[mxn];
char s[mxn],t[mxn];
signed main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%s%s",&n,s+1,t+1);
		memset(c,0,sizeof(c));
		r=1;
		rep(i,1,n){
			c[t[i]-'a']++;
			while(r<=n&&c[s[r]-'a'])c[s[r]-'a']--,r++;
			p[i]=r-1;
		}
		if(p[n]<n){
			puts("-1");
			continue;
		}
		rep(i,1,n)f[i]=0;
		rep(i,1,n){
			drep(j,p[i],1)f[j]=max(f[j],f[j-1]+(t[i]==s[j]));
			rep(j,1,n)f[j]=max(f[j],f[j-1]);
		} 
		printf("%d\n",n-f[n]);
	}
	return 0;
}
```

---

## 作者：UperFicial (赞：6)

> [**CF1363F Rotating Substrings**](https://www.luogu.com.cn/problem/CF1363F) *2600

> 解题报告。

> [**不一定更好的阅读体验**](https://www.cnblogs.com/UperFicial/p/16736770.html)。

感觉楼上的 DP 状态设计与 DP 转移方程的联系是说不通的，有些地方没有讲明白，所以这篇题解就详细讲一下。

首先，一次操作的本质是，将一个 $S$ 的一个字符插到前面的某一个位置。

判 `-1` 是容易的，即对于任意一个字符 $c$，在 $S$ 中的出现次数和 $T$ 中的出现次数是相等的。

那么我们就可以设 $f_{i,j}$ 表示将 $S$ 的长度为 $i$ 的前缀，插入最少几个字符，使得和 $T$ 的长度为 $j$ 的前缀相同。显然这里 $i,j$ 的大小关系为 $i\le j$。

考虑 $f_{i,j}$ 的转移，首先，我们可以不让 $s$ 的前缀 $i$ 和 $t$ 的前缀 $j$ 匹配，而是让 $s$ 的前缀 $i$ 和 $t$ 的前缀 $(j-1)$ 进行匹配，这时候会多出一个 $s_j$ 没有匹配。我们让 $i$ 之后的某一个 $s_k=t_j$ 的字符 $s_k$ 向前移动到 $i$ 的前面，与 $s_j$ 进行匹配，花费为 $1$。注意，这里一定会找到一个合法的 $s_k$，因为每一个字符都是两两配对的。于是我们有状态转移方程 $f_{i,j}=f_{i,j-1}+1$。

其次是比较简单的 case，若 $s_i=t_j$，那么可以通过 $f_{i-1,j-1}$ 来继承。$f_{i,j}=f_{i-1,j-1}$。

最后一种情况，设 $x$ 表示 $s_i$ 在 $S$ 的前缀 $i$ 中出现次数，$y$ 表示 $s_i$ 在 $T$ 的前缀 $j$ 中出现次数。

若 $x\le y$ 说明了什么？考虑 $f_{i-1,j}$，$S$ 的前缀 $(i-1)$ 与 $T$ 的前缀 $j$ 中 $s_i$ 的数量 $x',y$ 一定满足 $x'<y$。这也就说明，要想完成 $(i-1)$ 和 $j$ 的匹配，就必须**至少**把 $s_i$ 移动到前面。然后再移动若干字符。把 $s_i$ 移动到前面后再插入若干字符本质上是前缀 $i$ 与 $j$ 进行匹配，也就是 $f_{i,j}$ 的值，所以这个部分就直接继承：$f_{i,j}=f_{i-1,j}$。

$x,y$ 求法可以用一个 $\Theta(26n)$ 的前缀和搞定，转移的复杂度是 $\Theta(n^2)$ 的，总复杂度为 $\Theta(n^2)$。

代码实现非常简单，不放了，想要的私信我就好。

---

## 作者：7KByte (赞：6)

CF思维题。

观察操作的本质，就是把一个字符拿出来塞到另一个位置（感性分析

要使操作数最小可以想到使用``DP``。

我们需要一个$N^2$算法，所以可以定义$N^2$的状态。

$f[i][j]$表示$S$的前$i$个字符和$T$的前$j$个字符匹配的最小花费。

现在你肯定会问$i$和$j$不相等，也就是两个串长度不相等怎么匹配啊。

我们从$S$串的$i+1\sim N$先借$j-i$个与$T$串匹配。

这样我们就有三种转移。

第一种是直接匹配

$S_i=T_j$时，$f[i][j]=f[i-1][j-1]$

第二种是从后面借一个字符

对于当前$f[i][j]$，$S$串后面有多余的字符$T_j$才可以借，否则借了换不起。

在满足有多余字符情况下，这时$f[i][j]=f[i][j-1]+1$

第三种是还先前借的字符。因为先前保证还的起，所以现在直接还回去即可，不需要条件。

这时，$f[i][j]=f[i-1][j]$，即把第$i$个字符还回去。


-----------------------------

### Attention

其实读到这里你还没有发现这篇题解与前两篇题解有什么区别。。。

我发题解因为想一个细节想了很久。

就是在还的操作时，如果当前字符$S_i$没有被借过，直接还不显然是错的？

比如$\texttt{azaaa,aaaaz}$。

这里$f[2][2]$可以由$f[1][2]$转移，但是显然$f[2][2]$是不存在的。

但仔细琢磨下会发现我们更新了$f[2][2]$对答案并没有影响，因为这里还了一个没有借过的字符，那么后面匹配的时候肯定会少一个字符，匹配不能正常进行。上面的例子发现$f[2][2]$只能影响状态$f[3][3],f[4][4]$，不可能对$f[i][5]$产生影响。

所以并不会影响答案。


```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 2005
using namespace std;
int n;char s[N],t[N];
int f[N][N],u[N][28],v[N][28];
void solve(){
	scanf("%d",&n);
	scanf("%s%s",s+1,t+1);
	memset(u,0,sizeof(u));
	memset(v,0,sizeof(v));
	rep(i,1,n)u[i][s[i]-'a']++,v[i][t[i]-'a']++;
	rep(i,1,n)rep(j,0,25)u[i][j]+=u[i-1][j],v[i][j]+=v[i-1][j];
	rep(i,0,25)if(u[n][i]!=v[n][i]){puts("-1");return ;}
	rep(i,0,n)rep(j,0,n)f[i][j]=0x3f3f3f3f;
	rep(i,0,n)f[0][i]=0;
	rep(i,1,n){
		rep(j,i,n){
			f[i][j]=f[i-1][j]+1;
			if(s[i]==t[j])f[i][j]=min(f[i-1][j-1],f[i][j]);
			if(u[i][t[j]-'a']<v[j][t[j]-'a'])f[i][j]=min(f[i][j],f[i][j-1]);
		}
	}
	printf("%d\n",f[n][n]);
}
int main(){
	int T;scanf("%d",&T);
	while(T--)solve();
	return 0;
}
/*
1
3
aab
aba
*/
```

---

## 作者：Liuxizai (赞：2)

[My Blog](https://liuxizai.ac.cn/archives/solutions-2024-1.html)

开始做了半天不会，看到题解开头发现题看错了。

题目中的操作等价于将一个字符向前移动。考虑如果我们知道 $s$ 中每个字符最后移动到了什么位置，我们断言一个字符需要被移动当且仅当存在一个原来在它前面的字符最后出现在了它之后，这可以通过构造证明。

我们考虑 dp，从前往后对 $s$ 中的字符匹配一个 $t$ 与之相同的字符。根据上面判断一个字符是否需要移动的条件，在考虑 $s_i$ 时，我们需要知道 $s_{1\dots i-1}$ 在 $t$ 中匹配的最靠后的字符在什么位置。于是设 $f_{i,j}$ 表示已经考虑了前 $i$ 个字符，在 $t$ 中匹配的最靠后的字符是 $t_j$，对于 $s_{i+1}$，我们考虑它匹配的字符在 $t_j$ 之前还是之后，可以证明若在 $t_j$ 之后，匹配第一个和 $s_{i+1}$ 相同的字符总是不劣的，基于此进行转移即可。总复杂度 $O(n^2)$。

这种做法其实最后得到的 dp 和题解做法一模一样，不过我觉得这种思路更加直观一些。

[Submission #240200868](https://codeforces.com/contest/1363/submission/240200868)

---

## 作者：loveJY (赞：1)

简要题意



给定两个长度为 $n$ 的字符串 $s，t$。定义一次操作为选择 $s$ 的一个子串$s_{l, l +1, \dots, r}$然后将之修改为 $s_{r, l, l + 1, l + 2, \dots, r - 1 }$。请求助使 $s$ 与 $t$ 相等的最小操作次数。无解输出 $-1$。

多组数据，$\sum n \leq 2000$，$s, t$ 中只有小写字母。

考虑一次操作的实质是把一个字符和之前的某个字符swap了

也就是说这个东西对于字符之间的相对顺序要求不大，而对于我们字符的个数要求很严格qwq

那么我们可以发现-1的就是存在某个字符x，s和t的数量不相等

否则我们可以dp

设$dp[i][j]$表示s串前i个字符加上后面的一些字符凑齐了t串的前j个字符

然后考虑转移

**case1**

$dp[i][j]=dp[i-1][j]+1$

这个是把字符i移到前面去而不和j匹配

你会发现这个转移看上去很没用？但并不是，因为下面两种case都是有限制的

**case2**

$dp[i][j]=dp[i-1][j-1],s_i==t_j$

显然

**case3**

$dp[i][j]=dp[i][j-1]$

这个是我们把后面的某个字符换到i然后强制让他们匹配，你发现这里没有算贡献，因为一定会在之后的某个位置，我们case1把贡献算好

感性理解一下就是这个case3一定会对应后面case1的转移qwq

然而这个转移是有限制的，就是后面的s串中还有多余的$t_j$

即$pre_s[i][t_j]>pre_t[j][t_j]$

## 

如果您TLE on test164，那可能是因为那个点n=2000,len=1，然后您把2000*2000的数组清零了2000次

~~所以面向数据改程序就可以过~~

code:

```cpp

//#pragma g++ optimize("O2")
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int MAXN = 2004;
int n, flag;
int dp[MAXN][MAXN];
int cnt1[MAXN][30], cnt2[MAXN][30];
char s1[MAXN], s2[MAXN];

namespace fastIO {
#define BUF_SIZE (1<<19)
	static char buf[BUF_SIZE], *p1 = buf, *pend = buf;
	inline char nc() {
		if(p1 == pend) {
			p1 = buf;
			pend = buf + fread(buf, 1, BUF_SIZE, stdin);
		}
		return *p1++;
	}
	inline int read() {
		int x = 0;
		char s = nc();
		for(; !isdigit(s); s = nc());
		for(; isdigit(s); s = nc())x = (x << 1) + (x << 3) + s - '0';
		return x;
	}
	inline void str(char *t) {
		char s = nc();
		int cnt = 0;
		for(; !isalpha(s); s = nc());
		for(; isalpha(s); s = nc())t[++cnt] = s;
		return;
	}
}
using namespace fastIO;
inline void init() {

	n = read();
	str(s1);
	str(s2);
	for(int i = 1; i <= n; ++i) {

		for(int j = 0; j < 26; ++j)cnt1[i][j] = cnt1[i - 1][j], cnt2[i][j] = cnt2[i - 1][j];
		cnt1[i][s1[i] - 'a']++;
		cnt2[i][s2[i] - 'a']++;

	}
	flag = 1;
	for(int i = 1; i <= 29; ++i) {
		if(cnt1[n][i] != cnt2[n][i]) {
			flag = 0;
			break;
		}
	}
	if(!flag) {
		puts("-1");
	}
	int qwq = 0;
	for(int i = 1; i <= n; ++i) {
		if(s1[i] != s2[i]) {
			qwq = 1;
			break;
		}
	}
	if(!qwq) {
		puts("0");
		flag = 0;
	}
}

inline void solve() {
	memset(dp, 0x3f3f3f3f, sizeof(dp));
	for(int i = 0; i <= n; ++i)dp[0][i] = 0;

	for(int i = 1; i <= n; ++i) {
		for(int j = i; j <= n; ++j) {
			dp[i][j] = dp[i - 1][j] + 1;
			if(s1[i] == s2[j])
				dp[i][j] = min(dp[i - 1][j - 1], dp[i][j]);
			else if(cnt1[i][s2[j] - 'a'] < cnt2[j][s2[j] - 'a']) {
				dp[i][j] = min(dp[i][j - 1], dp[i][j]);
			}
		}
	}
	//	for(int i=1; i<=n; ++i) {
	//		for(int j=i; j<=n; ++j) {
	//			printf("%d ",dp[i][j]);
	//		}
	//		puts("");
	//	}
	printf("%d\n", dp[n][n]);
	return ;
}

int main() {
	//	freopen("test.in","r",stdin);
	int T;
	T = read();
	while(T--) {
		init();
		if(flag)
			solve();
	}
	return 0;
}

```

---

