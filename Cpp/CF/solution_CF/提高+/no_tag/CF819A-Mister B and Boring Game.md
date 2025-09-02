# Mister B and Boring Game

## 题目描述

Sometimes Mister B has free evenings when he doesn't know what to do. Fortunately, Mister B found a new game, where the player can play against aliens.

All characters in this game are lowercase English letters. There are two players: Mister B and his competitor.

Initially the players have a string $ s $ consisting of the first $ a $ English letters in alphabetical order (for example, if $ a=5 $ , then $ s $ equals to "abcde").

The players take turns appending letters to string $ s $ . Mister B moves first.

Mister B must append exactly $ b $ letters on each his move. He can arbitrary choose these letters. His opponent adds exactly $ a $ letters on each move.

Mister B quickly understood that his opponent was just a computer that used a simple algorithm. The computer on each turn considers the suffix of string $ s $ of length $ a $ and generates a string $ t $ of length $ a $ such that all letters in the string $ t $ are distinct and don't appear in the considered suffix. From multiple variants of $ t $ lexicographically minimal is chosen (if $ a=4 $ and the suffix is "bfdd", the computer chooses string $ t $ equal to "aceg"). After that the chosen string $ t $ is appended to the end of $ s $ .

Mister B soon found the game boring and came up with the following question: what can be the minimum possible number of different letters in string $ s $ on the segment between positions $ l $ and $ r $ , inclusive. Letters of string $ s $ are numerated starting from $ 1 $ .

## 说明/提示

In the first sample test one of optimal strategies generate string $ s= $ "abababab...", that's why answer is $ 2 $ .

In the second sample test string $ s= $ "abcdbcaefg..." can be obtained, chosen segment will look like "bcdbc", that's why answer is $ 3 $ .

In the third sample test string $ s= $ "abczzzacad..." can be obtained, chosen, segment will look like "zzz", that's why answer is $ 1 $ .

## 样例 #1

### 输入

```
1 1 1 8
```

### 输出

```
2```

## 样例 #2

### 输入

```
4 2 2 6
```

### 输出

```
3```

## 样例 #3

### 输入

```
3 7 4 6
```

### 输出

```
1```

# 题解

## 作者：睿智的憨憨 (赞：2)

## 解法分析

不妨用 $\texttt A$ 表示电脑添加的串，$\texttt B$ 表示 Mister B 添加的串。

不难想到 Mister B 每次添加的字符相同时是最优的。照此手玩一下，会发现字符串有长度为 $2(a+b)$ 的循环节。

举 $a>b$ 时的例子 $a=5,b=2$，字符串长这样：$\texttt{abcde,ee,abfgh,hh,abcde\dots}$，发现一个长度大于等于一个循环节的区间内至少有 $2a-b$ 个不同字母。

而 $a\le b$ 时情况又不同，举 $a=3,b=3$ 的例子，字符串长这样：$\texttt{abc,ccc,abd,ddd,abc\dots}$，发现此时长度大于等于一个循环节的区间内至少有 $a+1$ 个字母。

现在只需考虑长度小于循环节的区间了，对于这种区间，Mister B 每次仍然添加相同的字符，但是并不能确定添加的字符是什么。注意到此时区间长度很小，所以 Mister B 需要决策的次数最多只有三次，即跨越了 $\texttt{BABAB}$，有三个 $\texttt B$ 需要决策。直接枚举每个区间填的字母构造的时间复杂度为 $O(k^3(a+b)),k=26$，实际跑下来非常优秀。小麻烦是我们不能只从询问区间开始的地方构造，因为后面的构造中可能需要用到询问区间前的字符，因此可以把询问区间左右都补一补，变成 $\texttt{ABABAB}$，就解决了。

## 参考代码

```
#include <bits/stdc++.h>
#define ll long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define pushf push_front
#define pushb push_back
#define popf pop_front
#define popb pop_back
#define lowbit(x) (x-(x&(x-1)))
using namespace std;

int l, r, a, b;
int len, ans = 2e9, cnt[30];
char ch[3];

int main(){
	scanf("%d %d %d %d", &a, &b, &l, &r);
	len = r - l + 1;
	if (r - l + 1 >= 2 * (a + b)){
		if (a <= b)
			printf("%d\n", a + 1);
		else
			printf("%d\n", a + (a - b));
		return 0;
	}
	l = (l - 1) % (a + b) + 1, r = l + len - 1;
	for (ch[0] = 'a'; ch[0] <= 'z'; ch[0]++)
		for (ch[1] = 'a'; ch[1] <= 'z'; ch[1]++)
			for (ch[2] = 'a'; ch[2] <= 'z'; ch[2]++){
				int cur = -1;
				string s = " ";
				for (int i = 1; i <= r; i++){
					if (i <= a)
						s += char('a' + i - 1);
					else{
						int pos = (i - 1) % (a + b) + 1;
						if (pos == a + 1){
							cur++;
							int p = i;
							while (p < i + b)
								s += ch[cur], p++;
							i = p - 1;
						}
						else{
							static bool f[30];
							memset(f, false, sizeof(f));
							for (int j = i - a; j < i; j++)
								f[s[j] - 'a' + 1] = true;
							int c = 1, p = i;
							while (p < i + a){
								while (f[c])
									c++;
								s += char(c + 'a' - 1);
								c++, p++;
							}
							i = p - 1;
						}
					}
				}
				int tot = 0;
				memset(cnt, 0, sizeof(cnt));
				for (int i = l; i <= r; i++)
					if (++cnt[s[i] - 'a' + 1] == 1)
						tot++;
				ans = min(ans, tot);
			}
	cout << ans << "\n";
	return 0;
}
```

---

