# Archaeology

## 题目描述

Alice bought a Congo Prime Video subscription and was watching a documentary on the archaeological findings from Factor's Island on Loch Katrine in Scotland. The archaeologists found a book whose age and origin are unknown. Perhaps Alice can make some sense of it?

The book contains a single string of characters "a", "b" and "c". It has been pointed out that no two consecutive characters are the same. It has also been conjectured that the string contains an unusually long subsequence that reads the same from both sides.

Help Alice verify this by finding such subsequence that contains at least half of the characters of the original string, rounded down. Note that you don't have to maximise the length of it.

A string $ a $ is a subsequence of a string $ b $ if $ a $ can be obtained from $ b $ by deletion of several (possibly, zero or all) characters.

## 说明/提示

In the first example, other valid answers include "cacac", "caac", "aca" and "ccc".

## 样例 #1

### 输入

```
cacbac
```

### 输出

```
aba
```

## 样例 #2

### 输入

```
abc
```

### 输出

```
a
```

## 样例 #3

### 输入

```
cbacacacbcbababacbcb
```

### 输出

```
cbaaacbcaaabc```

# 题解

## 作者：tXX_F (赞：2)

# Archaeology

## [传送门](https://www.luogu.com.cn/problem/CF1178E)

## 题面翻译

给定一个由 ```a```,```b```,```c```组成的字符串  $s$。

 $s$ 没有两个相邻的字符是相同的。

现在需要你求出字符串  $s$ 的一个回文子序列  $t$，且满足  $|t|\ge\left\lfloor\dfrac{|s|}{2}\right\rfloor$（其中  $|S|$ 表示字符串  $S$ 的长度）。

如果有多种情况，输出任意一个即可。

如果没有满足要求的字符串  $t$，输出```IMPOSSIBLE```。

## 解题思路
由于题目中只要求找到长度不低于 $\frac{|s|}{2}$ 的回文子序列，所以不用考虑是否连续。只要每次在当前字符串长度范围（初始范围为整个字符串）内取首两位与末两位，由于字符串只由 ```a```,```b```,```c```组成，所以必定有两位相同，抛弃不同的两位，将这两位定位新的区间，重复以上操作。由于每次操作抛弃两位，是 $4$ 的 $\frac{1}{2}$ ，所以不存在无解情况。

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int Maxn = 1e6 + 5;
char s[Maxn];
int len, l, r;
char ans[Maxn];
inline void work() {
	cin >> s + 1;
	for (l = 1, r = strlen(s + 1); r - l + 1 >= 4; l += 2, r -= 2) {
		if (s[l] == s[r]) {
			ans[len++] = s[l];
		} else if (s[l + 1] == s[r]) {
			ans[len++] = s[l + 1];
		} else if (s[l] == s[r - 1]) {
			ans[len++] = s[l];
		} else if (s[l + 1] == s[r - 1]) {
			ans[len++] = s[l + 1];
		}
	}
	for (int i = 0; i < len; i++) {
		cout << ans[i];
	}
	if (l < r) {
		cout << s[l];
	}
	for (int i = len - 1; i >= 0; i--) {
		cout << ans[i];
	}
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	work();
	return 0;
}
```

---

## 作者：_soul_ (赞：1)

这题放在E题着实不合适啊。。但是比赛的时候还想了好久，zbl

首先考虑到只有a，b，c三个字符，那么如果我在当前串的开头和结尾都取两个字符，一共四个字符，这四个字符中必然存在两个相同的字符，那么我们只需要取当前相同的这两个字符，另外的全都都舍去。然后只需要不断重复这个操作，往中间缩进即可。这样做不仅满足了回文串的条件，又因为我每次都是从4个中选取两个抛弃两个，那么也能保证最后得到的结果串也一定是原串的一半。
```cpp
#include<bits/stdc++.h>
using namespace std;
char s[1100000];
int tot1,tot2;
char ans1[1100000],ans2[1100000];
int main(){
	ios::sync_with_stdio(false);
	scanf("%s",s+1);
	int l=1,r=strlen(s+1);
	while (1){
		if (r-l+1<4) break;
		if (s[l]==s[r]){
			ans1[tot1++]=s[l];
			ans2[tot2++]=s[r];
			l++; r--; l++; r--;
		} else 
		if (s[l+1]==s[r]){
			ans1[tot1++]=s[l+1];
			ans2[tot2++]=s[r];
			l++; r--; l++; r--;
		} else 
		if (s[l]==s[r-1]){
			ans1[tot1++]=s[l];
			ans2[tot2++]=s[r-1];
			l++; r--; l++; r--;
		} else 
		if (s[l+1]==s[r-1]){
			ans1[tot1++]=s[l+1];
			ans2[tot2++]=s[r-1];
			l++; r--; l++; r--;
		}
	}
	printf("%s", ans1);
	if(l < r) putchar(s[l]);
	reverse(ans1, ans1 + tot1);
	puts(ans1);
	return 0;
}
```


---

## 作者：mraymes (赞：1)

本文章将同步到 [Hexo 博客](https://mraymes.github.io).

本题中有两个细节特别重要.
1. 原字符串中相邻的字符都是不同的.
2. 字符串只包含 `a`, `b`, `c` 三种字符.

我们可以从两端同时开始匹配. 一开始 $i = 1$, $j = |s|$.  
如果 $s_i = s_j$, 则 `i++`, `j--`.  
如果 $s_i \ne s_j$, 那么必定有满足 $s_{i + 1} = s_j$, $s_i = s_{j - 1}$, $s_{i + 1} = s_{j - 1}$, 看情况改变 $i$, $j$ 的值.

证明:  
$s_i$, $s_{i + 1}$, $s_j$, $s_{j - 1}$ 最少有两个字符是相等的, 因为这些字符只可能是 `a`, `b`, `c` 中的一个. 又因为 $s_i \ne s_j$, $s_i \ne s_{i + 1}$, $s_j \ne s_{j - 1}$, 所以 $s_{i + 1} = s_j$, $s_i = s_{j - 1}$, $s_{i + 1} = s_{j - 1}$ 中必定有一个满足. 因此并不需要用什么高深的算法解决此题. 具体实现并不难.

```cpp
#include <bits/stdc++.h>

using namespace std;

int n;
char str[1000001];
int i = 1, j;
bool is_chosen[1000001]; // 标记在回文串中
int cnt;

int main() {
    scanf("%s", str + 1);
    n = j = strlen(str + 1);
    while (i <= j) {
        if (str[i] == str[j]) { // str[i] 与 str[j] 匹配
            is_chosen[i] = is_chosen[j] = 1;
            cnt += 1 + (i != j); // 如果 i = j, 那么长度只增加 1
            i++, j--;
        } else if (i + 1 <= j && str[i + 1] == str[j]) {
            // str[i + 1] 与 str[j] 匹配
            is_chosen[i + 1] = is_chosen[j] = 1;
            cnt += 1 + (i + 1 != j);
            i += 2, j--; // 跳过 str[i]
        } else if (i <= j - 1 && str[i] == str[j - 1]) {
            // str[i] 与 str[j - 1] 匹配
            is_chosen[i] = is_chosen[j - 1] = 1;
            cnt += 1 + (i != j - 1);
            i++, j -= 2; // 跳过 str[j]
        } else {
            i++, j--;
        }
    }

    if (cnt >= n / 2) {
        for (int i = 1; i <= n; i++) {
            if (is_chosen[i]) {
                putchar(str[i]);
            }
        }
        puts("");
    } else {
        puts("IMPOSSIBLE");
    }

    return 0;
}
```
这种方式效率快, 并且能保证选出的子序列尽量长.


---

## 作者：封禁用户 (赞：0)

## 题解：CF1178E Archaeology

**Upd：优化了打表部分的可读性。**

### 题意简述

给你一个由 `a`、`b`、`c` 组成的字符串 $s$ 满足 $\forall i$ 有 $s_i \neq s_{i-1}$，请你求出任意长度 $\ge \lfloor \frac{s \text{ 的长度}}{2} \rfloor$ 的回文子序列。无解输出：`IMPOSSIBLE`。

### 解题思路

回文串可以看作是“剥洋葱”式，利用**双指针**求算法。

尝试列举所有情况：

|目前第 $1$ 个字母|目前第 $2$ 个字母|$\cdots$|目前倒数第 $2$ 个字母|目前倒数第 $1$ 个字母|
|-|-|-|-|-|
|**a**|b|$\cdots$|**a**|b|
|**a**|b|$\cdots$|**a**|c|
|**a**|b|$\cdots$|b|**a**|
|a|**b**|$\cdots$|**b**|c|
|**a**|b|$\cdots$|c|**a**|
|a|**b**|$\cdots$|c|**b**|
|**a**|c|$\cdots$|**a**|b|
|**a**|c|$\cdots$|**a**|c|
|**a**|c|$\cdots$|b|**a**|
|a|**c**|$\cdots$|b|**c**|
**a**|c|$\cdots$|c|**a**|
|a|**c**|$\cdots$|**c**|b|
|**b**|a|$\cdots$|a|**b**|
|b|**a**|$\cdots$|**a**|c|
|**b**|a|$\cdots$|**b**|a|
|**b**|a|$\cdots$|**b**|c|
|b|**a**|$\cdots$|c|**a**|
|**b**|a|$\cdots$|c|**b**|
|**b**|c|$\cdots$|a|**b**|
|b|**c**|$\cdots$|a|**c**|
|**b**|c|$\cdots$|**b**|a|
|**b**|c|$\cdots$|**b**|c|
|b|**c**|$\cdots$|**c**|a|
|**b**|c|$\cdots$|c|**b**|
|c|**a**|$\cdots$|**a**|b|
|**c**|a|$\cdots$|a|**c**|
|c|**a**|$\cdots$|b|**a**|
|**c**|a|$\cdots$|b|**c**|
|**c**|a|$\cdots$|**c**|a|
|**c**|a|$\cdots$|**c**|b|
|c|**b**|$\cdots$|a|**b**|
|**c**|b|$\cdots$|a|**c**|
|c|**b**|$\cdots$|**b**|a|
|**c**|b|$\cdots$|b|**c**|
|**c**|b|$\cdots$|**c**|a|
|**c**|b|$\cdots$|**c**|b|

上表标记了每种情况的一个可行解，有多组可行解的情况首字母优先标注。

设 $l$ 为目前字符串第 $1$ 个字母，$r$ 为目前字符串最后一个字母。发现可以归结为 $5$ 种情况：

- $l = r$：将坐标 $l$ 加入答案，退出。
- $s_l = s_r$：将坐标 $l , r$ 加入答案，$l \gets l + 1 , r \gets r - 1$。
- $s_l = s_{r - 1}$：将坐标 $l , r - 1$  加入答案，$l \gets l + 1 , r \gets r - 2$。
- $s_{l + 1} = s_r$：将坐标 $l + 1 , r$ 加入答案，$l \gets l + 2 , r \gets r - 1$。
- $s_{l + 1} = s_{r - 1}$：将坐标 $l + 1 , r - 1$ 加入答案，$l \gets l + 2 , r \gets r - 2$。

最后给坐标排序，依次输出即可。

因为每次操作最劣也是抛弃两个拿到两个，所以一定出现合法回文串，**不存在无解**。

### 参考代码

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(2)
using namespace std;
int n , l , r;
string s;
char c[1000005];
priority_queue<int , vector<int> , greater<int>> q;
int main()
{
	ios::sync_with_stdio(0);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> s;
	n = s.size();
	for(int i = 1 ; i <= n ; i++)
	{
		c[i] = s[i - 1];
	}
	l = 1;
	r = n;
	while(l <= r)
	{
		if(l == r)
		{
			q.push(l);
			l++;
			r--;
			continue;
		}
		if(c[l] == c[r])
		{
			q.push(l);
			q.push(r);
			l++;
			r--;
			continue;
		}
		if(c[l] == c[r - 1])
		{
			r--;
			continue;
		}
		l++;
	}
	while(q.size())
	{
		cout << c[q.top()];
		q.pop();
	}
	return 0;
}
```

---

