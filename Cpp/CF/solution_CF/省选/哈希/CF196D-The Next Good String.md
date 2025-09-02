# The Next Good String

## 题目描述

In problems on strings one often has to find a string with some particular properties. The problem authors were reluctant to waste time on thinking of a name for some string so they called it good. A string is good if it doesn't have palindrome substrings longer than or equal to $ d $ .

You are given string $ s $ , consisting only of lowercase English letters. Find a good string $ t $ with length $ |s| $ , consisting of lowercase English letters, which is lexicographically larger than $ s $ . Of all such strings string $ t $ must be lexicographically minimum.

We will call a non-empty string $ s[a ... b]=s_{a}s_{a+1}...\ s_{b} $ $ (1\le a\le b\le |s|) $ a substring of string $ s=s_{1}s_{2}...\ s_{|s|} $ .

A non-empty string $ s=s_{1}s_{2}...\ s_{n} $ is called a palindrome if for all $ i $ from $ 1 $ to $ n $ the following fulfills: $ s_{i}=s_{n-i+1} $ . In other words, palindrome read the same in both directions.

String $ x=x_{1}x_{2}...\ x_{|x|} $ is lexicographically larger than string $ y=y_{1}y_{2}...\ y_{|y|} $ , if either $ |x|>|y| $ and $ x_{1}=y_{1},x_{2}=y_{2},...\ ,x_{|y|}=y_{|y|} $ , or there exists such number $ r $ $ (r<|x|,r<|y|) $ , that $ x_{1}=y_{1},x_{2}=y_{2},...\ ,x_{r}=y_{r} $ and $ x_{r+1}>y_{r+1} $ . Characters in such strings are compared like their ASCII codes.

## 样例 #1

### 输入

```
3
aaaaaaa
```

### 输出

```
aabbcaa
```

## 样例 #2

### 输入

```
3
zzyzzzz
```

### 输出

```
Impossible
```

## 样例 #3

### 输入

```
4
abbabbbabbb
```

### 输出

```
abbbcaaabab
```

# 题解

## 作者：naive_wcx (赞：2)

# Description
给出字符串$s(|s|≤400000)$正整数$d(d≤|s|)$。定义$good$ $string$表示不包含长度$≥d$的回文子串的字符串。求长度为$|s|$且字典序恰好大于$s$的$good$ $string$。
# Solution
一个$hash$的做法：

定义$hsh1_i$表示前$i$位字符串正着读的$hash$值，$hsh2_i$表示前$i$位字符串倒着读的$hash$值。

注意到长度为$len$的回文串必然包括一个长度为$len-2$的回文串，那么我们找到第一个前面长度为$d$或$d+1$的回文子串，从这个字符串的末尾开始尝试替换即可，正确性显然。

从这个回文串的最后一位依次向前找到第一个不是$'z'$的字母，枚举将它换成什么，合法则退出，接下来依次枚举每一位放置的字母，利用$hash$判断当前是否合法即可。

时间复杂度$O(|s|)$。

我的写法是自然溢出$hash$。
# Code
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define ull unsigned long long
using namespace std;
const ull base = 127, maxn = 4e5 + 10;
ull hsh1[maxn], hsh2[maxn], pow[maxn];
int d, n;
char s[maxn];

bool check(int l, int r) {
	ull a = hsh1[r] - hsh1[l - 1], b = (hsh2[r] - hsh2[l - 1] * pow[r - l + 1]) * pow[l - 1];
	return a == b;
}

int main()
{ 
	pow[0] = 1;
	for(int i = 1; i <= 400000; i++) pow[i] = pow[i - 1] * base;
	scanf("%d", &d);
	scanf("%s", s + 1);
	n = strlen(s + 1);
	int bad = n;
	for(int i = 1; i <= n; i++) {
		hsh2[i] = hsh2[i - 1] * base + (int)s[i];
		hsh1[i] = hsh1[i - 1] + (int)s[i] * pow[i - 1];
		if(i >= d && check(i - d + 1, i)) {
			bad = i;
			break;
		}
		if(i >= d + 1 && check(i - d, i)) {
			bad = i;
			break;
		}
	}
	bool flag = 0;
	for(int i = bad; i; i--) {
		for(char c = s[i] + 1; c <= 'z'; c++) {
			s[i] = c;
			hsh2[i] = hsh2[i - 1] * base + (int)s[i];
			hsh1[i] = hsh1[i - 1] + (int)s[i] * pow[i - 1];
			if(i >= d && check(i - d + 1, i)) continue;
			if(i >= d + 1 && check(i - d, i)) continue;
			flag = 1;
			break;
		}
		if(flag) {
			bad = i;
			break;
		}
	}
	if(!flag) {
		printf("Impossible\n");
		return 0;
	} 
	for(int i = bad + 1; i <= n; i++)
		for(char c = 'a'; c <= 'z'; c++) {
			s[i] = c;
			hsh2[i] = hsh2[i - 1] * base + (int)s[i];
			hsh1[i] = hsh1[i - 1] + (int)s[i] * pow[i - 1];
			if(i >= d && check(i - d + 1, i)) continue;
			if(i >= d + 1 && check(i - d, i)) continue;
			break;
		}
	for(int i = 1; i <= n; i++) printf("%c", s[i]);
	printf("\n");
	return 0;
}
```

---

## 作者：Yizhixiaoyun (赞：1)

来大致翻译一下官方题解吧。

首先是一个特性：我们只需要考虑长度为 $d$ 或 $d+1$ 的回文字符串，因为如果我们找到了一个长度为 $d+2$ 的回文字符串，那么它一定包含了长度为 $d$ 的回文字符串，以此类推。

然后我们令 $pos$ 为所有不合法回文串末尾中的最左边那个，如果不存在不合法回文串，则 $pos=|s|-1$。然后我们从 $pos$ 开始不断向前增加 $s_{pos}$ 直到其不是不合法的回文串末尾。

再令 $pos$ 为所有改变的位置中最左边的那个，显然 $s_{0...pos}$ 中不包含不合法回文串，接着我们就可以从前往后贪心地不断填充 $s_{pos + 1..len - 1}$，其中 $len$ 为 $s$ 的长度。

这样我们就得到了一个算法，而这个算法需要我们能够快速查询：给定字符串是否为回文串？这个问题可以使用哈希或是[二叉索引树](https://zhuanlan.zhihu.com/p/94432288)来解决。

---

## 作者：Little_corn (赞：0)

这是一个 $\rm PAM$ 做法。

下面两个字符的比较定义为字典序上的比较。

首先发现最后答案的形态一定是形如把某个 $S_x$ 变为 $S'_x$，且 $S'_x > S_x$ 并保持 $S[1\dots x - 1]$ 不变。然后 $S[x + 1 \dots n]$ 可以随意更改。且满足这个串中没有长度 $\ge m$ 的回文串。显然我们应该尽量让 $x$ 尽量大，这样构造出来的字符串的字典序才可以尽量小。

令 $l_x$ 为以 $x$ 结尾的最长回文后缀，这个不难使用 $\rm PAM$ $O(n)$ 求出。那么找到第一个 $l_x \ge m$ 的位置 $p$，同时令 $v_{i, c}$ 为将 $S_i$ 改成 $c$，$S[1\dots i]$ 的最长回文串长度是否 $\ge m$，然后在 $[1, p]$ 中最小的 $x$，满足 $\exists c > S_i, v_{i, c} = 1$，同时找到满足 $v_{i, c}$ 的最小的 $c$。如果不存在这样的 $i$，那么显然不可能。

然后把 $S_i$ 改成 $c$，此时 $S[i + 1 \dots n]$ 可以随意更改，于是对于每一位，从小到大贪心的能放就放即可。

那现在还有一个小问题，如何在已知 **好串** $S[1\dots i - 1]$ 时，然后快速的对于每一个 $c$，求出 $S_i = c$ 时，$S[1\dots i]$ 是否合法呢？这个相当于对 $\rm PAM$ 插入，但是每次暴力跳的时间复杂度是错误的，这是由于 $\rm PAM$ 是均摊时间复杂度的，如果出现很多的同字符，使得终止链保持 $O(m)$ 级别，那么时间复杂度就是错的。但是注意到由于前面的串是合法的，$i$ 为结尾长度 $\ge m - 2$ 的回文后缀至多只有两个，于是能导致 $len_p + 2 \ge m$ 的节点至多只有两个，于是每次判断时只需要判断 $O(1)$ 个节点。于是时间复杂度为 $O(|\Sigma|n)$，其中 $|\Sigma| = 26$。

代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define pir pair<int, ll>
#define pb emplace_back
#define fi first
#define se second
#define mkpir make_pair
using namespace std;

const int N = 4e5 + 10, M = 2e5 + 10;
const ll mod = 998244353;

void ADD(ll& x, ll y){x += y; (x >= mod) ? (x -= mod) : 0ll;}
void MUL(ll& x, ll y){x = x * y % mod;}
void chkmax(int x, int y){if(x < y) x = y;}
void chkmax(long long x, long long y){if(x < y) x = y;}
void chkmin(int x, int y){if(x > y) x = y;}
void chkmin(long long x, long long y){if(x > y) x = y;}

ll qpow(ll x, int y){
  ll ret = 1;
  for(; y; y >>= 1, MUL(x, x)) if(y & 1) MUL(ret, x);
  return ret;
}

int n, m, ans[N];
string str;

struct PAM{
  int len[N], fa[N], tot, s[N], n, lst, son[N][26];
  void init(){memset(len, 0, sizeof len); memset(son, 0, sizeof son); memset(fa, 0, sizeof fa); tot = fa[0] = 1; len[1] = -1; n = lst = 0; s[0] = -1;}
  int getfail(int p){while(s[n] != s[n - len[p] - 1]) p = fa[p]; return p;}
  int getlen(int c){
    s[++n] = c; int p = lst; 
    while(len[p] + 2 >= m && s[n] != s[n - len[p] - 1]) p = fa[p];
    n--;
    return len[p] + 2;
  } 
  void add(int c){
    s[++n] = c; int p = getfail(lst);
    if(!son[p][c]){
      len[++tot] = len[p] + 2;
      fa[tot] = son[getfail(fa[p])][c];
      son[p][c] = tot; 
    } lst = son[p][c];
  }
}tr;

int ndpos, ndch;

signed main(){
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cin >> m;
  cin >> str; n = str.size(); str = "*" + str;
  tr.init();
  for(int i = 1; i <= n; i++){
    for(int j = str[i] - 'a' + 1; j < 26; j++) if(tr.getlen(j) < m){ndpos = i; ndch = j; break;}
    tr.add(str[i] - 'a');
    if(tr.len[tr.lst] >= m) break;
  }
  if(!ndpos){cout << "Impossible"; return 0;}
  tr.init();
  for(int i = 1; i < ndpos; i++) ans[i] = str[i] - 'a', tr.add(ans[i]);
  ans[ndpos] = ndch; tr.add(ndch);
  for(int i = ndpos + 1; i <= n; i++){
    for(int j = 0; j < 26; j++){
      if(tr.getlen(j) < m){ans[i] = j; break;}
    }
    tr.add(ans[i]);
  }
  for(int i = 1; i <= n; i++) cout << (char)(ans[i] + 'a');  
  
  return 0;
}
```

---

