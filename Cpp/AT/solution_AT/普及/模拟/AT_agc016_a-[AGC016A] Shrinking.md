# [AGC016A] Shrinking

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc016/tasks/agc016_a

すぬけ君は、次のルールに従い、長さ $ N $ の文字列 $ t $ を長さ $ N\ -\ 1 $ の文字列 $ t' $ へ変えることができます。

- 各 $ i $ ($ 1\ <\ =\ i\ <\ =\ N\ -\ 1 $) について、$ t' $ の $ i $ 文字目は $ t $ の $ i $, $ i\ +\ 1 $ 文字目のどちらかである。

英小文字のみからなる文字列 $ s $ があります。 すぬけ君の目標は、$ s $ に上記の操作を繰り返し行い、$ s $ が単一の文字のみからなるようにすることです。 目標を達成するために必要な操作回数の最小値を求めてください。

## 说明/提示

### 制約

- $ 1\ <\ =\ |s|\ <\ =\ 100 $
- $ s $ は英小文字のみからなる。

### Sample Explanation 1

例えば、`serval` → `srvvl` → `svvv` → `vvv` と変えればよいです。

### Sample Explanation 2

例えば、`jackal` → `aacaa` → `aaaa` と変えればよいです。

### Sample Explanation 3

最初から $ s $ が単一の文字のみからなっています。

### Sample Explanation 4

$ 8 $ 回の操作によって、$ s $ を `rrrrrrrrrrrrrrrrrr` へ変えることができます。

## 样例 #1

### 输入

```
serval```

### 输出

```
3```

## 样例 #2

### 输入

```
jackal```

### 输出

```
2```

## 样例 #3

### 输入

```
zzz```

### 输出

```
0```

## 样例 #4

### 输入

```
whbrjpjyhsrywlqjxdbrbaomnw```

### 输出

```
8```

# 题解

## 作者：Jairon314 (赞：5)

$$ \textbf{\huge AT2385 [AGC016A]} $$
$$ \textbf{\LARGE Shrinking} $$
$$ \text{\large ————Jair} $$

$$ \text{\small Warning: This problem's solving belongs to} $$
$$ \textbf {\huge $ \mathbb{TOP\;SECRET} $} $$
$$ \text {\small Unauthorized personnel are prohibited from visiting} $$
$$ \text {\small Perpetrators will be monitored, located, and dealt with} $$

$$ PAY\;ATTENTION: $$
$$ \text {\small 本题解竟然是第一篇题解！} $$

$$ \large· $$
$$ \large· $$
$$ \large· $$

$$ \large \frak {Forward} $$
--------
这题这么水，竟然没人写题解？于是我来水一水叭~

首先，这题是个贪心——~~（是不是很意外~~

那么这题主要的思想就是，找到相同的几个字母，例如：

$$ \text {\small 先看这几个字母每个都在边界上的情况：} $$

$$ \textbf {\large a***a****a*****a} $$

如果我们要把这个字符串全部变成 $ a $ ,那么我们就需要至少5步。现在我们发现，相邻两个相同字母 $str1[i]$ 与$ str1[j] $中间所隔的字母数量就是把 $ str1[i] $ 到 $ str1[j] $ 之间的所有字母变成 $ str1[i] $ 这个字母的最小步数。那么，把整个字符串中的字母都变成这个字母所需的最小步数，就是没相邻两个相同字母之间相隔的字母数量的最大值。

如上面的字符串，前两个 $ a $ 之间隔了三个字母，此时的 $ cnt $ 为 $ 3 $ ；第二个 $ a $ 与第三个 $ a $ 之间隔了四个字母，而 $ 3 < 4 $ ,所以此时的 $ cnt $ 就为 $ 4 $ 。以此类推，最后的cnt就是5。那么把整个字符串变成 $ a $ 所需的操作数量就是 $ 5 $ 。

$$ \text {\small 我们再看一下下面这个字符串：} $$

$$ \textbf {\large ***a} $$

按照上面的方法，我们可以发现，把这个字符串变成 $ a $ 的最小步数是 $ 3 $ 。所以，我们可以让 $ str1[-1]=a $ ，按照上面的操作进行就可以了。

$$ \textbf {\large a***} $$

这个就与上面的字符串类似。只需要让 $ str1[n+1]=a $ 就行。

这里需要注意一下，字符类型不能为负数。所以我们只需要另存一个变量就OK惹！


$$ \large \frak {CodeTime}$$
--------

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<map>
using namespace std;

string str1;
int ans=0x3f3f3f3f;

int main(){
	cin>>str1;
	int len=str1.length();
	for(int i=1;i<=26;i++){
		str1[len]=char(i+'a'-1);
		//str1[len]=str1[-1];
		int cnt=-0x3f3f;
		int ID=-1;
		for(int j=0;j<=len;j++){
			if(str1[j]==str1[len]){
				if(ID!=-0x3f3f){
					cnt=max(cnt,j-ID-1);
				}
				ID=j;
			}
		}
		if(cnt!=-0x3f3f)ans=min(ans,cnt);
	}
	printf("%d",ans);
	return 0;
}
```

$$ \large \frak {in\;the\;end}$$
--------
给个赞呗~

---

## 作者：Ezio__Auditore (赞：1)

## AT2385 [AGC016A] Shrinking
[[Statement]](https://www.luogu.com.cn/problem/AT2385)

Date: Mar. 24th

---
#### 题意：
&emsp;&emsp;Snuke 君有一个字符串 $s$。 每次操作，他可以舍去 $s$ 的最后一个字符，并将 $s_i$ 变为原来的 $s_i$ 或 $s_{i + 1}$。问 Snuke 要使 $s$ 中只有一种字符，最少需要操作几次。

数据范围：$|s|\le 100$

---
#### 思路：
&emsp;&emsp; 先观察一下这个变化的过程，可以得到如下树形图：
$$

\begin{matrix}
s_1 & &s_2 & & s_3 & & s_4 & \cdots & s_{n-1}& s_n\\ 
\downarrow & \swarrow & \downarrow & \swarrow & \downarrow &\swarrow & \downarrow & \cdots & \downarrow & \swarrow \\
s'_1 & & s'_2 & & s'_3 & & s'_4 & \cdots & s'_{n-1}\\
\downarrow & \swarrow & \downarrow & \swarrow & \downarrow &\swarrow & \downarrow & \cdots & \swarrow\\
s''_1 & & s''_2 & & s''_3 && s''_4 & \cdots\\
\vdots & & \vdots & & \vdots & & \vdots \\
\downarrow & \swarrow & \downarrow & \swarrow & \downarrow &\swarrow\\
s^{(n-3)}_1 & & s^{(n-3)}_2 & & s^{(n-3)}_3\\
\downarrow & \swarrow & \downarrow & \swarrow\\
s^{(n-2)}_1 & & s^{(n-2)}_2 \\
\downarrow & \swarrow\\
s^{(n-1)}_1
\end{matrix}

$$
**可以发现，$s_i$ 在 $k$ 轮之后， $s^{(k)}_i$ 只有可能变成 $s_i,s_{i+1} ... s_{i+k-1}$ 中的一个**。

由于要把所有变成一样的，我们可以视最终留下的字符为 $1$ 其余为 $0$。
那么当一个 $0$ 能变成 $1$ 的时候，我们就把贪心的把它变成 $1$。

那么，$s_i$ 在 $k$ 轮之后，能变成 $1$ 的充要条件是 $s_i,s_{i+1}...s_{i+k-1}$ 中至少有一个 $1$。	

易得：**若 $s$ 在 $k$ 轮后能只剩下 $1$，则满足 $\forall i \in[1, n-k], s_{[i, i+k-1]}$ 中有至少一个 $1$。**


由于我们不知道哪一个字符是最终字符，所以得对每个字母都统计，只要有一个字母满足上述条件即可。

可以用 bitset 统计这个过程，位运算 + count() 统计，非常方便。

第 $k$ 轮时，用 b[i][j] 表示 $s_i..s_{i+k-1}$ 中是否有字母 $j$，将 b[i] 全部 and 起来，若某一位上为 $1$ 则说明该位的字母符合了条件；否则，从前往后 b[i] = b[i] | b[i+1]，表示进入 $k+1$ 轮，向后多延伸一个字符。

---
Code:

```cpp
#include <bits/stdc++.h>

const int kMaxN = 1e2 + 5;
std::bitset<26> b[kMaxN];
char s[kMaxN], n, k;
int main() {
  scanf("%s", s);
  n = strlen(s);
  for (int i = 0; i < n; i++) b[i].set(s[i] - 'a');
  while (true) {
    std::bitset<26> check;
    check.set();
    for (int i = 0; i < n - k; i++)
      check &= b[i];
    if (check.count()) {
      printf("%d\n", k);
      break;
    } else {
      k++;
      for (int i = 0; i < n - k; i++)
        b[i] |= b[i + 1];
    }
  }
  return 0;
}
```
---
~~才发现之前题解的 Statement 都少了个 e。~~

UPD：已修改部分 Latex，但不清楚这个 $s$ 的变化表算不算滥用 qwq。

---

## 作者：Butterfly___qwq (赞：0)

枚举最终得到的字符 $c$，则每次操作可以被看作是 $c$ 字符在字符串中往前拓展了一位。

对于字符串长度会减小的问题，我们可以看作 $s$ 的末尾增加了一个万能字符。

那么一个字符 $c$ 覆盖整个串的回合数，就是每个字符 $c$ 之前非 $c$ 连续段长度的最大值。

扫一遍判断即可。

code:
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
const int MN = 105, Sig = 26;
int N;
char S[MN];
int lst[Sig], ans[Sig];
using namespace std;
int main() {
	scanf("%s", S + 1), N = strlen(S + 1);
	for (int i = 1; i <= N; ++i) {
		int x = S[i] - 'a';
		ans[x] = max(ans[x], i - lst[x] - 1);
		lst[x] = i;
	}
	int tans = N;
	for (int x = 0; x < Sig; ++x) tans = min(tans, max(ans[x], N - lst[x]));
	printf("%d\n", tans);
	return 0;
}
```

---

