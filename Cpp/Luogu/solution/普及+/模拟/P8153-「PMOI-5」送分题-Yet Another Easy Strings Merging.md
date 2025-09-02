# 「PMOI-5」送分题/Yet Another Easy Strings Merging

## 题目背景

**本题征集假做法和 hack 数据，如果您用假做法 AC 了，欢迎私信出题人提供 hack。**

> 信息可能有冗余。

——command_block 《考前小贴士》

djy 在看 P8001，看错题了，很自闭，然后就有了这个题。

## 题目描述

给定 $n$ 个 01 串，每次你可以从某个串开头移除一个字符并把**剩下的字符串**加入一个新串 $S$ 的末尾。最大化 $S$ 中相邻两个字符相同的对数。

例如你有 `1010 111` 两个串，如果你移除第一个串的第一个字符，则 `010` 被加入到 $S$ 中。

**串可以重复使用。**

## 说明/提示

【样例解释】

依次取走第一个字符，$S$ 的变化过程为 `100->10000->100000`，答案为 $4$。

【数据范围】

记 $|s|$ 为字符串 $s$ 的长度，$s_i$ 为第 $i$ 个字符串  。    
**本题采用捆绑测试。**

- Subtask 1（30 pts）：$n,\sum|s_i|\le 11$；
- Subtask 2（30 pts）：$n,\sum|s_i|\le 10^3$；
- Subtask 3（30 pts）：$n,\sum|s_i|\le 10^5$；
- Subtask 4（10 pts）：无特殊限制。   

对于 $100\%$ 的数据，$1\le n\le 10^6$，$n\le \sum |s_i|\le 10^6$，$\forall i\in [1,n]$，$|s_i|\ge 1$。



## 样例 #1

### 输入

```
1
1100```

### 输出

```
4```

## 样例 #2

### 输入

```
5
10010
10000
01110
111111
000000```

### 输出

```
48 ```

# 题解

## 作者：Buried_Dream (赞：15)

> 思路来自：@wsyear 大佬，十分感谢。

## 题意：

给你 $n$ 个 $01$ 字符串，每次取一个串后删除第一个字符，将剩下的串加入到答案串中，最大化答案串中相邻字符相等的对数。

## 思路：

- Sub1：爆搜。

我的爆搜写的比较奇怪。

[记录](https://www.luogu.com.cn/record/69305629)
[暴力代码](https://www.luogu.com.cn/paste/082exfcr)

- Sub2，Sub3

我们考虑贪心，首先我们把所有的字串全加进去是最优的，因为有更多的字符就有更多的可能去最大化答案串中相邻字符相等的对数。

既然是全加进去，每个字串中间是什么无法改变，只能改变头尾相接的顺序，所以我们预处理出所有串的字串中相等的对数。

这个时候我们就只需要考虑每个串的头和尾了，头尾相接有 $4$ 中情况：

- $1 \ 0$

- $1 \ 1$

- $0 \ 1$

- $0 \ 0$

我们只需要统计出以 $1$ 为前缀，后缀的串的个数，以 $0$ 为前缀的串的个数即可。

我们还要考虑这个答案串一开始是要填 $0$ 还是填 $1$。

所以我们将一开始填 $0$ 和一开始填 $1$ 的情况做比较即可。

## AC code：

```cpp
/*
work by: TLE_Automation
Time: O(轻轻松松过)
knowledge: 垃圾算法
*/
#include<bits/stdc++.h>
#define il inline
#define re register
#define Orz puts("Szt Lps Fjh AK IOI!");
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
// #define int long long
using namespace std;

const int INF = 1e9 + 7, mod = 1e9 + 7;
const int maxn = 2e5 + 10, MAXN = 3e3 + 10, N = 1e6 + 10;

typedef long long LL;
string s[N];
LL ans, n;
int L[N], sum = 0;
bool f1, f2; 
int sum1, sum2, sum3, sum4;
 
// sum1 是以 0 为后缀的串的个数 
// sum2 是以 1 为后缀的串的个数 
// sum3 是以 0 为前缀的串的个数 
// sum4 是以 1 为前缀的串的个数 
// f1 是否有开头就是 0 的
// f2 是否有开头就是 1 的
 
signed main() {
	IOS
	cin >> n;
	for(re int i = 1; i <= n; i++) cin >> s[i], s[i] = "$" + s[i], L[i] = s[i].length() - 1;
	for(re int i = 1; i <= n; i++) sum += L[i];
//	for(int i = 1; i <= n; i++) cout << L[i] << " ";
	if(!(sum ^ n)) return printf("0"), 0;
	for(re int i = 1; i <= n; i++) {
		int cnt = 0; 
		for(re int j = L[i] - 1; j >= 2; j--) {
			if(s[i][j] == s[i][j + 1]) cnt++;
			ans += cnt;
		}
	}
//	cout << ans << endl; 
	for(re int i = 1; i <= n; i++) {
		if(L[i] == 1) continue; // 长度为 1 的串删完就成了空串，没用 
 		if(s[i][L[i]] == '0') sum1 += L[i] - 1; 
		else sum2 += L[i] - 1;		
		for(re int j = 2; j <= L[i]; j++) {
			if(s[i][j] == '0') sum3++;  
			else sum4++;
		}
		if(s[i][2] == '0') f1 = true;
		else if(s[i][2] == '1') f2 = true;	
	}
	if(f1 && f2) ans += max(min(sum3, sum1) + min(sum4 - 1, sum2), min(sum3 - 1, sum1) + min(sum4, sum2));
	else if(f1) ans += min(sum3 - 1, sum1) + min(sum4, sum2);
	else ans += min(sum3, sum1) + min(sum4 - 1, sum2);
	cout << ans << endl;
}
```

---

## 作者：lndjy (赞：13)

Sub 1 是爆搜，Sub 2 是想到贪心策略但是没有预处理串之间，$O(n^2)$，Sub 3 是给可能有的奇怪的数据结构做法。


可以把题目中的取的方式抽象为 $n$ 个栈，每个栈里依次有所有后缀。

但是这样串长之和就是平方级别的了，所以考虑简化：对于每个串，中间的字符的贡献我们是已经确定的，先提前算好，现在只需要最大化串和串之间的贡献，也就是只有串的开头和结尾的信息有用。这样我们就把串长之和变成线性。且串只有 00 01 10 11 四种。

下面考虑贪心策略，重复执行以下策略直到所有栈为空：

如果当前最后一位是 0，先把 00 都用上，用不了了然后用 01。如果这也没有那么就用 11，如果同时有 10 11 那么先用 11 后面还能用上 10，比直接 10 合适。

如果当前最后一位是 1，先把 11 都用上，用不了了然后用 10。如果这也没有那么就用 00，如果同时有 00 01 那么先用 00 后面还能用上 01，比直接 01 合适。

枚举第一位是 0 还是 1 即可。复杂度 $O(n)$。

---

