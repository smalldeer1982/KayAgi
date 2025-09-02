# Backspace

## 题目描述

You are given two strings $ s $ and $ t $ , both consisting of lowercase English letters. You are going to type the string $ s $ character by character, from the first character to the last one.

When typing a character, instead of pressing the button corresponding to it, you can press the "Backspace" button. It deletes the last character you have typed among those that aren't deleted yet (or does nothing if there are no characters in the current string). For example, if $ s $ is "abcbd" and you press Backspace instead of typing the first and the fourth characters, you will get the string "bd" (the first press of Backspace deletes no character, and the second press deletes the character 'c'). Another example, if $ s $ is "abcaa" and you press Backspace instead of the last two letters, then the resulting text is "a".

Your task is to determine whether you can obtain the string $ t $ , if you type the string $ s $ and press "Backspace" instead of typing several (maybe zero) characters of $ s $ .

## 说明/提示

Consider the example test from the statement.

In order to obtain "ba" from "ababa", you may press Backspace instead of typing the first and the fourth characters.

There's no way to obtain "bb" while typing "ababa".

There's no way to obtain "aaaa" while typing "aaa".

In order to obtain "ababa" while typing "aababa", you have to press Backspace instead of typing the first character, then type all the remaining characters.

## 样例 #1

### 输入

```
4
ababa
ba
ababa
bb
aaa
aaaa
aababa
ababa```

### 输出

```
YES
NO
NO
YES```

# 题解

## 作者：江户川·萝卜 (赞：14)

我们首先来观察退格在各种情况下的**实质作用**：
1. 将首个字符改成退格

由于在首个字符按下退格时，前面没有字符，所以这个退格没有删除前面字符的作用，仅仅起到了删除首个字符的作用。

**下面的讨论将排除这种情况。**

2. 单独的一个退格

这一个退格将原来的字符和前面一个字符通通删去，也就是连续删除了2个字符。

3. 连续的 $k$ 个退格

将这 $k$ 个退格进行编号，从 $1$ 到 $k$，且在它删除的字符的位置记录编号。

则形如 $[k,k-1,k-2,\dots,2,1,1,2,\dots,k-2,k-1,k]$ 共 $2k$ 个字符被删除。

在效果上相当于 $[1,1,2,2,\dots,k-1,k-1,k,k]$，也即 $k$ 个单独的退格的效果。

---
从而，所有的删除操作，除去首位删除1字符外，均删除了连续2字符。

所以，当 $n,m$ 奇偶性不同时，首先必须要删除首位。

接着，用贪心，从前往后在`s`串依次匹配`t`串的各个字符，如在`s`串这一位没匹配到，则说明这一位和下一位必须删除。检查是否匹配完成即可。

易证贪心策略正确。
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
int main(){
	int t;
	cin>>t;
	while(t--){
		string s,t;
		cin>>s;
		cin>>t;
		int sl=s.length(),tl=t.length();
		string ss="";int j=0,k=0;
		if(sl%2!=tl%2) j=1;
		for(int i=j;i<sl;i++){
			if(s[i]==t[k]) k++;
			else i++;
			if(k>=tl) break;
		}
		if(k<tl) puts("NO");
		else puts("YES");
	}
	return 0;
}
```

---

## 作者：Alex_Wei (赞：6)

> [题目传送门](https://www.luogu.com.cn/problem/CF1553D)。
>
> 题意简述：给定 $s,t$，现在要依次输入 $s$ 中的字符。对于每个字符 $s_i$，你可以选择输入 $s_i$ 或者使用退格键，判断是否能得到 $t$。

不妨将字符串反过来贪心考虑：设 $i=|s|$，$p=|t|$。

- 如果 $s_i=t_p$，那么显然选择输入这个字符，$p\gets p-1$，$i\gets i-1$。
- 否则只能退格，不输入 $s_i$ 并删除 $s_{i-1}$，所以 $i\gets i-2$。

若 $p=0$ 则能得到 $t$，反之则不行。

也许有人会问，如果 $s_{i-1}$ 也是退格怎么办？实际上**若干个连续的退格等价于若干个不连续的退格：**不妨设 $s_{i-1}$ 的退格删了 $s_j$，而 $s_i$ 的退格删了 $s_k$，显然有 $k<j$。也就是说 $s_{k+1}\sim s_{j-1}$ 以及 $s_{j+1}\sim s_{i-2}$ 全部被删掉了。因此它等价于在 $s_j$ 处**不输入而选择使用退格删除输入的 $s_k$**，在 $s_i$ 出不输入而选择使用退格删除输入的 $s_{i-1}$。若 $k+1=j$，那么刚好是我们想要的；而如果 $k,j$ 不连续，那么可以递归证明下去。所以我们可以认为**每次退格删除的必定是该位置的前一个字符**，贪心算法的正确性就得到了证明。

```cpp
#include <bits/stdc++.h>
using namespace std;

int main(){
	int T=1; cin>>T;
	while(T--){
		string s,t; cin>>s>>t;
		int p=t.size()-1;
		for(int i=s.size()-1;i>=0;i--)~p&&s[i]==t[p]?p--:i--;
		puts(~p?"NO":"YES");
	}
	return 0;
}
```

---

## 作者：lylcpp (赞：2)

## 思路

### 题面描述

给你两个字符串 $S,T$，问你能否通过将 $S$ 中的若干个数换成 Backspace 来使其变成 $T$。Backspace 能删去前一个输入的字符。

居然直接判断 $S$ 能否通过 Backspace 变为 $T$，那么我们就从最后一位开始判断。

假设 $i = |S|, p = |T|$，如果 $S_i = T_i$，那么就继续比对下去，即 $i = i-1, p = p - 1$。否则，我们放弃输入 $S_i$，并将 $S_{i-1}$ 删去。

## 代码

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>

using namespace std;

int read() {
	int x = 0, f = 1; char ch = getchar();
	while (!isdigit(ch)) {
		if (ch == '-') f = -1;
		ch = getchar();
	}
	while (isdigit(ch)) {
		x = (x << 3) + (x << 1) + (ch ^ 48);
		ch = getchar(); 
	}
	return x * f;
}

int t, n, m;
string a, b;

int main() {
	int T;
	T = read();
	while (T--) {
		cin >> a >> b;
		n = a.size();
		m = b.size();
		a = " " + a, b = " " + b; // 增添一位空格方便比较 
		while (n >= 0) {
			if (a[n] == b[m] && m >= 1) n--, m--; // 相同 
			else n -= 2; // 不相同 
		}
		if (m >= 1) // 没有比较完，说明无法转换 
			printf("NO\n");
		else
			printf("YES\n");
	}
	return 0;
}
``````

---

## 作者：cunzai_zsy0531 (赞：2)

## CF1553D题解-by cunzai_zsy0531

[题面](https://www.luogu.com.cn/problem/CF1553D)

正着考虑不太好办，可能会出现连续的两个字母，不知道该取哪一个之类的，讨论起来很麻烦而且正确性不一定能保证。

考虑倒过来计算。注意到，$t$ 中最后一位，在 $s$ 中一定取到从后往前数第奇数个的位置上。如果从后往前数它是第偶数个，那无论怎么样，要么会后面剩下一个，要么就把这个数也删除了。最后一位找到之后继续用同样的方法找倒数第二位，以此类推就行了。

code：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int N=1e5+13;
char s[N],t[N];
int n,m;
inline void solve(){
	scanf("%s%s",s+1,t+1);n=strlen(s+1),m=strlen(t+1);
	if(m>n) return void(puts("NO"));//特判一下m>n
	int flag=0;从后往前数不可以取到的奇偶性
	for(int i=m,j=n;i>=1;--i){
		while(j>=1&&(s[j]!=t[i]||(((n-j+1)&1)==flag))) --j;//如果不能取到，就继续找前面的
		if(!j) return void(puts("NO"));//s串已经没了，肯定无法满足要求了
		flag^=1,--j;//每次的奇偶性会改变
	}
	puts("YES");
}
int main(){
	int T;scanf("%d",&T);
	while(T--) solve();
	return 0;
}
//D
```


---

## 作者：wheneveright (赞：2)

## 题意

$T$ 组询问，每次给出两个长度不一定相同的字符串 $a,b$，模拟键入第一个字符串 $a$，当你要键入 $i$ 位时，你可以选择键入 Backspace 来代替键入 $a_i$，Backspace 的效果是删除最后输入的字符，如果没有可以删除的那就什么都不用做，问是否有可能有一个输入方式使得最后留下的字符串为 $b$。

## 分析

考虑将 Backspace 换一种理解，就是在 $a$ 中消除连续的两个字符或者消除第一个字符，那么我们正向考虑的话要枚举删除一个字符还是两个字符，所以可以反向考虑，如果当前 $a_i \not = b_j$ 就令 $i - 2$，否则 $i - 1, j - 1$，如果当 $i \le 0$ 时 $j \le 0$ 那么输出 `YES`，否则输出 `NO`。

## 代码

```cpp
# include <bits/stdc++.h>
using namespace std;

int T, N, M;
string a, b;

int main () {
    cin >> T;
    while (T--) {
        cin >> a >> b;
        N = a.size (); a = "0" + a;
        M = b.size (); b = "0" + b;
        while (N >= 0) { // 图方便直接把 N 和 M 拿来操作了
            if (a[N] == b[M] && M >= 1) N--, M--;
            else N -= 2;
        }
        puts (M >= 1 ? "NO" : "YES");
    }
    return 0;
}
```

---

## 作者：do_while_true (赞：1)

看到字符串就害怕傻眼到降智，赢得番薯田大丰收。

注意到问题等价于是否存在一种 $t$ 的字符先后一一映射到 $s$ 的方案，使得在 $s$ 中的下标奇偶性不同，**并且要满足最后 $s$ 没有被映射到的极长后缀长度为偶数，这样才能保证能把多余的删完**。

考虑类似于子序列自动机的形式处理出 $fir_{i,j}$ 代表第 $i$ 位之后最近的下标奇偶性不同的字符 $j$ 在哪里。

在 $t$ 串上设计一个 dp，设 $f_{i,0/1}$ 代表匹配完 $t$ 串的前 $i$ 位，第 $i$ 位匹配的下标奇偶性为偶数/奇数，最靠前的匹配位置。

由于预处理出了 $fir$，$f$ 的转移就很明显了，不多赘述。注意到由于要保证最后多余的能删完，仅需要判断 $f_{m,n\&1}$ 中的值。

### $\mathcal{Code}$

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
template <typename T> T Max(T x, T y) { return x > y ? x : y; }
template <typename T> T Min(T x, T y) { return x < y ? x : y; }
template <typename T>
T& read(T& r) {
	r = 0; bool w = 0; char ch = getchar();
	while(ch < '0' || ch > '9') w = ch == '-' ? 1 : 0, ch = getchar();
	while(ch >= '0' && ch <= '9') r = r * 10 + (ch ^ 48), ch = getchar();
	return r = w ? -r : r;
}
const int N = 100010;
char s[N], t[N];
int n, m, vis[2][27], fir[N][27], f[N][2];
void solve() {
	scanf("%s", s+1);
	scanf("%s", t+1);
	n = std::strlen(s+1); m = std::strlen(t+1);	
	for(int i = 0; i < 27; ++i) vis[0][i] = vis[1][i] = 0;
	for(int i = n; ~i; --i) {
		for(int j = 0; j < 27; ++j) fir[i][j] = vis[!(i&1)][j];
		vis[i&1][s[i]-'a'] = i;
	}
	f[1][0] = vis[0][t[1]-'a'];
	f[1][1] = vis[1][t[1]-'a'];
	if(!f[1][0]) f[1][0] = -1;
	if(!f[1][1]) f[1][1] = -1;
	for(int i = 2; i <= m; ++i) {
		if(~f[i-1][1]) f[i][0] = fir[f[i-1][1]][t[i]-'a'];
		else f[i][0] = -1;
		if(~f[i-1][0]) f[i][1] = fir[f[i-1][0]][t[i]-'a'];
		else f[i][1] = -1;
		if(!f[i][0]) f[i][0] = -1;
		if(!f[i][1]) f[i][1] = -1;
	}
	printf("%s\n", f[m][n&1] != -1 ? "YES" : "NO");
}
signed main() {
	int T; read(T);
	while(T--) solve();
	return 0;
}
```

---

## 作者：lizhixun (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF1553D)

### $\texttt{Description}$

给定一个字符串 $S$，问能否改变输入，将字符串中的若干个字符换成 $\texttt{Backspace}$ 键，使得 $S$ 变为另一个字符串 $T$。

### $\texttt{Solution}$

实际上把第 $i$ 个字符换成 $\texttt{Backspace}$ 键就是删去 $S_i$ 以及 $S_{i-1}$ 两个字符。

我们可以从最右侧开始考虑，用一个双指针的写法，如果 $S_l=T_r$ 的话，就让 $l$ 和  $r$ 都向左移，否则删除，即为 $l$ 左移两位。然后还需要判断是否越界，否则会 $\texttt{RE}$ 的。

最后判断 $r$ 是不是还没有越界即可。

### $\texttt{Code}$

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

string add(string ss) {
	ss = "@" + ss;
	return ss;
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	
	int t;
	cin >> t;
	
	while (t--) {
		string s, t;
		cin >> s >> t;
		
		int l = s.size(), r = t.size();
		s = add(s), t = add(t);
		
		while (l >= 0) {
			if (r >= 1 && s[l] == t[r]) l--, r--;
			else l -= 2;
		}
		
		if (r >= 1) cout << "No\n";
		else cout << "Yes\n";
	}
	return 0;
}
```

---

## 作者：Doubeecat (赞：0)

> [CF1553D](https://www.luogu.com.cn/problem/CF1553D)
>
> 给定两个字符串 $s,t$，你可以逐字符键入字符串 $s$。
> 
> 在键入过程中，你可以选择不键入当前字符，而是删去前面的一个字符，例如当 $s =$ `abcbd` 时，当你键入到字符 `c` 时选择删除，后面正常键入，则最后得到的字符串就为 `abd`
> 
> 特别地，当你选择删去的这个字符前没有字符时，只会令当前的字符不出现而已。
> 
> 现在请问对于 $s$ ，是否可以经过若干次删除（或者不删除）得到 $t$
> 
> $|s|,|t| \leq 2\times 10 ^5$

<!-- more -->

## 解题思路：

比较巧妙的贪心。 

删除的操作我们可以直接考虑为删掉两个相邻的字母。

首先我们考虑两个在 $t$ 中相邻的字符在 $s$ 中满足什么条件，观察到我们不论按照什么顺序删除，实际上都是与相邻的两个一起删除是等价的。

举个例子。如字符串 `abcdef`，我们先删除 `cd`，然后在 `e` 处按下删除键，删除了 `be`。这两个操作等价于删除 `bc` 再删除 `de`。所以我们可以得出一个重要条件：**两个在 $t$ 中相邻的字符在 $s$ 中间隔的字母数必定为偶数**。正确性显然。

接下来，我们考虑怎么去在 $s$ 中匹配这样的一个 $t$ 出来。暴力的思路是枚举每个 $s_i = t_1$ 的 $i$，但这样的程序会被形如 `aaaaa...` 的数据 hack 掉。所以我们考虑能不能只对 $t$ 中的每个字符匹配一次？

结论是可以的，例如这个串：`abacabe`，我们的文本串为 `abe`，那么我们实际上选哪个 `a` 作为开头都是等价的，因为我们对于每个 `a` 开头我们都需要找到对应的 `b`，基于贪心的思想，我们直接找我们能够找到的第一个 `a` 把它与文本串中的 `a` 匹配上。如果失配了，很简单，我们只需要移除 $s_i$ 与 $s_{i+1}$ 就行了（为了满足重要条件）

最后，考虑到匹配的最后一个位置到末尾实际上也是需要偶数个位置的，我们不妨调整一下开始匹配的位置，若 $(n-m)\bmod 2 = 0$，两串长度奇偶性相同，我们直接从第一个位置开始匹配即可，否则奇偶性不相同，我们从第二个位置开始匹配。

时间复杂度 $O(n)$

## 代码：

```cpp
void solve() {
    scanf("%s",s+1);
	scanf("%s",t+1);
	int n = strlen(s+1),m = strlen(t+1);
	if (m > n) {
		puts("NO");
		return ;
	}
	
	if (m == 1)  {
		bool flag = 0;
		for (int i = 1;i <= n;++i) {
			if (s[i] != t[m]) continue;
			if ((n - i) % 2 == 0) {
				flag = 1;
				break;
			}
		}
		if (flag) puts("YES");
		else puts("NO");
		return ;
	}
	bool fail = 0;
	int pos = 1;
	for (int i = (n-m) % 2 + 1;i <= n;++i) {
		if (fail) {fail = 0;continue;}
		if (s[i] == t[pos] && pos <= m) ++pos;
		else fail = 1;
	} 
	if (pos > m) puts("YES");
	else puts("NO");
}
```

---

## 作者：5ab_juruo (赞：0)

题意即为：给定 $s$，$t$，从 $s$ 开头删去若干字符和中间删去长为偶数的字串能否得到 $t$。

如果不计算开头部分，我们显然可以贪心匹配，容易证明正确性。同时，我们可以将字符串翻转，进行倒序匹配，就不需要考虑开头部分。最后只需判断 $t$ 的指针是否指向开头即可。

Code：

```cpp
#include <iostream>
using namespace std;

typedef long long ll;
const int max_n = 100000;

char s[max_n+1], t[max_n+1];

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
	int cas, ptr, ls, lt;
	
	cin >> cas;
	while (cas--)
	{
		cin >> s >> t;
		for (ls = 0; s[ls]; ls++);
		for (lt = 0; t[lt]; lt++);
		
		s[ls++] = 'A', t[lt++] = 'A';
		for (int i = ls - 1, j = lt - 1; i >= 0; i -= 2)
		{
			while (i >= 0 && j >= 0 && s[i] == t[j])
				i--, j--;
			ptr = j;
		}
		
		if (ptr < 0)
			cout << "YES" << endl;
		else
			cout << "NO" << endl;
	}
	
	return 0;
}
```

---

