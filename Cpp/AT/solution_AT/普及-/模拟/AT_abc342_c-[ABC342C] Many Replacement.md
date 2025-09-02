# [ABC342C] Many Replacement

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc342/tasks/abc342_c

英小文字からなる長さ $ N $ の文字列 $ S $ が与えられます。

文字列 $ S $ に対して操作を $ Q $ 回行います。 $ i $ 回目 $ (1\leq\ i\leq\ Q) $ の操作は文字の組 $ (c\ _\ i,d\ _\ i) $ で表され、次のような操作に対応します。

- $ S $ に含まれる文字 $ c\ _\ i $ をすべて文字 $ d\ _\ i $ で置き換える。
 
すべての操作が終わったあとの文字列 $ S $ を出力してください。

## 说明/提示

### 制約

- $ 1\leq\ N\leq2\times10^5 $
- $ S $ は英小文字からなる長さ $ N $ の文字列
- $ 1\leq\ Q\leq2\times10^5 $
- $ c\ _\ i,d\ _\ i $ は英小文字 $ (1\leq\ i\leq\ Q) $
- $ N,Q $ は整数
 
### Sample Explanation 1

$ S $ は `atcoder` → `atcodea` → `aecodea` → `aecovea` → `recover` と変化します。 たとえば、$ 4 $ 番目の操作では $ S={} $`aecovea` に含まれる `a` （$ 1 $ 文字目と $ 7 $ 文字目）をすべて `r` に置き換えるので $ S={} $`recover` となります。 すべての操作が終わったときには $ S={} $`recover` となっているため、`recover` を出力してください。

### Sample Explanation 2

$ c\ _\ i=d\ _\ i $ であるような操作や $ S $ に $ c\ _\ i $ が含まれないような操作もあります。

## 样例 #1

### 输入

```
7
atcoder
4
r a
t e
d v
a r```

### 输出

```
recover```

## 样例 #2

### 输入

```
3
abc
4
a a
s k
n n
z b```

### 输出

```
abc```

## 样例 #3

### 输入

```
34
supercalifragilisticexpialidocious
20
g c
l g
g m
c m
r o
s e
a a
o f
f s
e t
t l
d v
p k
v h
x i
h n
n j
i r
s i
u a```

### 输出

```
laklimamriiamrmrllrmlrkramrjimrial```

# 题解

## 作者：Programming_Konjac (赞：4)

# 赛时思路
## 提交记录：
![](https://cdn.luogu.com.cn/upload/image_hosting/fdqd4qb8.png)
## 思路
首先创建一个字符类型的映射数组 $m$，然后下标代表字母，内容存储要替代的字符，比如说，字符 `a` 要变成字符 `r`，那么 $m$ 数组中下标为 `a` 的地方存储的是 `r`。

首先进行初始化 $m$ 数组，字母下标 $x$ 存储的就是字母 $x$。

然后把每一步操作进行存储。

因为后面的操作会影响一开始的操作，所以使用倒推法。

从 $q$ 遍历到 $1$，对于每一次操作，将 $m_{c_i}$ 存储的字母变为 $m_{d_i}$。

为什么是 $m_{d_i}$ 呢？举个例子：$a \rightarrow r$，$r \rightarrow w$，如果赋值为 $d_i$，那么就是错的，$a$ 还是替换成 $r$ 还需要遍历一次字符串，但如果是 $m_{d_i}$，那么 $a\rightarrow r\rightarrow w$，这样就对了。

最后逐位输出 $m_{s_i}$ 即可。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
map<char,char> m;
int main(){
	int n;
	cin>>n;
	for(int i='a'; i<='z'; i++){
		m[(char)i]=(char)i;
	}
	string s;
	cin>>s;
	int q;
	cin>>q;
	char c[200005],d[200005];
	for(int i=1; i<=q; i++) cin>>c[i]>>d[i];
	for(int i=q; i>=1; i--){
		m[c[i]]=m[d[i]];
	}
	for(int i=0;i<n;i++){
		cout<<m[s[i]];
	}
	return 0;
} 
```

---

## 作者：_smart_stupid_ (赞：2)

## [题目](https://atcoder.jp/contests/abc342/tasks/abc342_c)

此题容易被误解成并查集，但是第一个样例就可以 hack 普通并查集做法。

我们直接记录原来字串中那些字母要被替换成另外的字母，一开始所有字母都要被替换成自己，每出现一个替换关系，比如把 $a$ 替换成 $b$，我们就寻找原来要替换成 $a$ 的字母，将其替换成 $b$，最后输出时在原字母中进行替换即可。

## AC Code：

```cpp

```#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#include <stack>
#include <cmath>
#include <list>
#include <set>
#include <map>
using namespace std;
int n, q;
string s;
int f[30];

int main() {
//	ios::sync_with_stdio(0);
//	cin.tie(0);
//	cout.tie(0);
	cin >> n >> s;
	for (int i = 0; i < 26; i++) f[i] = i;
	cin >> q;
	while (q--) {
		string u, v;
		cin >> u >> v;
		int a = u[0] - 'a', b = v[0] - 'a';
		for (int i = 0; i < 26; i++) if (f[i] == a) f[i] = b;
	}
	for (int i = 0; i < n; i ++) cout << char('a' + f[s[i] - 'a']);
	return 0;
}
```

---

## 作者：LaoXu666 (赞：2)

# ABC342C 题解
首先，我们可以对于每次操作暴力枚举每一个可以替换的，时间复杂度为  $\Theta (NQ)$，超时。

然后，我们可以想到，字母只有 $26$ 个，并不多，所以我们可以存下每个字母会变换成什么字母，开始时没有变换，就初始化为变换为自己。但是，可能会有间接变换，比如下样例。
```
3
abc
2
a b
b c
```

我们期望的效果是

| 原字母|   a    |    b    |   c  |
|-------|-------|-------|-----|
|变换字母|c|c|c|

如上表，输出 ```ccc```。

但是在先处理 ```a b``` 的时候，会变成如下：

| 原字母|   a    |    b    |   c  |
|-------|-------|-------|-----|
|变换字母|b|b|c|

（$bh_a = b$）
然后处理 ```b c``` 的时候，会变成如下：

| 原字母|   a    |    b    |   c  |
|-------|-------|-------|-----|
|变换字母|b|c|c|

（$bh_b = c$）

最终输出 ```bcc```，WA。

为了可以间接变换，因为变换是从前往后的，后面的会影响前面的，而变换数组是从前往后的，后面的不会影响前面的，所以我们可以倒着操作，同时设定 $bh_a = bh_b$，在没有间接的情况下是和前面一样的，有的情况情况如下。

先处理 ```b c``` 的时候，会变成如下：

| 原字母|   a    |    b    |   c  |
|-------|-------|-------|-----|
|变换字母|a|c|c|

然后处理 ```a b``` 的时候，会变成如下：

| 原字母|   a    |    b    |   c  |
|-------|-------|-------|-----|
|变换字母|c|c|c|

正确，输出 ```ccc```。

如果出现了环会怎么样？

就拿下样例说吧。

```
2
ab
2
a b
b a
```

先处理 ```b a```，会变成如下：
| 原字母|   a    |    b    | 
|-------|-------|-------|
|变换字母|a|a|

然后处理 ```a b```，又会变成如下：
| 原字母|   a    |    b    | 
|-------|-------|-------|
|变换字母|a|a|

最后输出 ```aa```，正确。

代码如下：
```cpp
#include <iostream>
#include <string>

int N, K;
char Replace1[200005], Replace2[200005];
std::string Str;
char Replace[128];

int main() {
	std::cin >> N >> Str >> K;
	for (int i = 0; i < 128; i++) {
		Replace[i] = char(i);
	}
	for (int i = 1; i <= K; i++) {
		std::cin >> Replace1[i] >> Replace2[i];
	}
	for (int i = K; i >= 1; i--) {
		Replace[Replace1[i]] = Replace[Replace2[i]];
	}
	for (char i: Str) {
		std::cout << Replace[i];
	}
	std::cout << '\n';
	return 0;
}

```

---

## 作者：LittleDrinks (赞：1)

## [AT_abc342_c](https://www.luogu.com.cn/problem/AT_abc342_c)

直接枚举必然超时，可以通过修改标记实现批量修改。

具体而言，用 `x[chr[a]][]` 存储字符 $a$ 在 $S$ 中出现的下标，其中 `chr[a]` 表示在 $x$ 中存放的位置。输入字符串 $S$ 后，枚举字符 $S_i$：

- 如果 $S_i$ 没有出现过，将 `chr[a]` 赋值指向一个空的 `x[][]` 列表，将当前下标 $i$ 存入。
- 如果出现过，即 `chr[a]` 不为 0，直接将 $i$ 存入 `x[chr[a]][]`。

将 $c_i$ 变为 $d_i$ 的过程中：

- 特判 $c_i=d_i$ 的情况，无视这次修改。
- 如果当前字符串 $S$ 中既有 $c_i$ 又有 $d_i$，那么枚举下标，将 `x[c[i]][]` 中的每一个下标存入 `x[d[i]][]`，最后将 `chr[c[i]]` 修改为 0，表示当前 $S$ 中不存在字符 $c_i$。
- 如果当前字符串中只存在 $c_i$，而不存在 $d_i$，直接令 `chr[d[i]]=chr[c[i]], chr[c[i]]=0` 即可。
- 如果只存在 $d_i$，没有 $c_i$，那么无视这次修改。

“令 `chr[d[i]]=chr[c[i]]`” 的这一步会极大减少修改的时间，可以通过本题。

[AC 代码提交记录](https://www.luogu.com.cn/record/148307796)

```cpp
#include <bits/stdc++.h>

using namespace std;

const int MAXN=2e5+5;
string s;
int n, mv, q, chr[26];
char ans[MAXN];
vector <int> x[26];

int main()
{
//	freopen("3.in", "r", stdin);
	cin >> n >> s;
	for (int i = 0; i < n; ++i) {
		int id = chr[s[i]-'a'];
		if (!id) { chr[s[i]-'a'] = id = ++mv; }
		x[id].push_back(i);
	}
	cin >> q;
	for (int i = 1; i <= q; ++i) {
		char c, d;
		cin >> c >> d;
		if (c == d) { continue; }
		else if (chr[c-'a'] && chr[d-'a']) {
			for (int id: x[chr[c-'a']]) { x[chr[d-'a']].push_back(id); }
		} else if (!chr[d-'a']){
			chr[d-'a'] = chr[c-'a'];
		}
		chr[c-'a'] = 0;
	}
	for (int i = 0; i < 26; ++i) {
		for (int id: x[chr[i]]) { ans[id] = 'a'+i; }
	}
	for (int i = 0; i < n; ++i) { cout << ans[i]; }
}
```

---

## 作者：HappyJaPhy (赞：0)

[洛谷传送门](https://www.luogu.com.cn/problem/AT_abc342_c)

[原题传送门](https://atcoder.jp/contests/abc342/tasks/abc342_c)

# 题意

给出由小写字母初始字符串，每次操作将字符串中所有为 $c$ 的字符改为 $d$。输出最终的字符串。

# 分析

很明显只需要开一个 $fa$ 数组，其中 $fa[i]=j$ 表示字母 $i$ 被改为了 $j$。对于每次操作只需要遍历 $26$ 个字母，将 $fa[i]=c$ 的那些字母改成 $fa[i]=d$。时间复杂度 $O(wq),w=26$。

# 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n, q, fa[30];
string s;

inline int read(int &x) {
	char ch = x = 0;
	int m = 1;
	while (ch < '0' || ch > '9') {
		ch = getchar();
		if (ch == '-') m *= -1;
	}
	while (ch >= '0' && ch <= '9') {
		x = (x << 1) + (x << 3) + ch - 48;
		ch = getchar();
	}
	x *= m;
	return x;
}

inline void print(int x) {
	if (x < 0) putchar('-'), x = -x;
	static int stk[50];
	int top = 0;
	do {
		stk[top++] = x % 10;
		x /= 10;
	} while (x);
	while (top) {
		putchar(stk[--top] + 48);
	}
	putchar('\n');
	return ;
}

signed main() {
	for (int i = 0; i < 26; i++) fa[i] = i;
	read(n);
	cin >> s;
	read(q);
	char c, d;
	while (q--) {
		c = d = 0;
		while (c < 'a' || c > 'z') c = getchar();
		while (d < 'a' || d > 'z') d = getchar();
		for (int i = 0; i < 26; i++) {
			if (fa[i] == (int)(c - 'a')) {
				fa[i] = (int)(d - 'a');
			}
		}
	}
	for (int i = 0; i < s.size(); i++) {
		putchar(fa[s[i] - 'a'] + 'a');
	}
	return 0;
}
```


---

