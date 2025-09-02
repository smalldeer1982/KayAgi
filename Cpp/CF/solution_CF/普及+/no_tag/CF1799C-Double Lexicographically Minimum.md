# Double Lexicographically Minimum

## 题目描述

You are given a string $ s $ . You can reorder the characters to form a string $ t $ . Define $ t_{\mathrm{max}} $ to be the lexicographical maximum of $ t $ and $ t $ in reverse order.

Given $ s $ determine the lexicographically minimum value of $ t_{\mathrm{max}} $ over all reorderings $ t $ of $ s $ .

A string $ a $ is lexicographically smaller than a string $ b $ if and only if one of the following holds:

- $ a $ is a prefix of $ b $ , but $ a \ne b $ ;
- in the first position where $ a $ and $ b $ differ, the string $ a $ has a letter that appears earlier in the alphabet than the corresponding letter in $ b $ .

## 说明/提示

For the first test case, there is only one reordering of $ s $ , namely "a".

For the second test case, there are three reorderings of $ s $ .

- $ t = \mathtt{aab} $ : $ t_{\mathrm{max}} = \max(\mathtt{aab}, \mathtt{baa}) = \mathtt{baa} $
- $ t = \mathtt{aba} $ : $ t_{\mathrm{max}} = \max(\mathtt{aba}, \mathtt{aba}) = \mathtt{aba} $
- $ t = \mathtt{baa} $ : $ t_{\mathrm{max}} = \max(\mathtt{baa}, \mathtt{aab}) = \mathtt{baa} $

The lexicographical minimum of $ t_{\mathrm{max}} $ over all cases is "aba".

## 样例 #1

### 输入

```
12
a
aab
abb
abc
aabb
aabbb
aaabb
abbb
abbbb
abbcc
eaga
ffcaba```

### 输出

```
a
aba
bab
bca
abba
abbba
ababa
bbab
bbabb
bbcca
agea
acffba```

# 题解

## 作者：y_kx_b (赞：12)

题意：

给你一个字符串 $s$，你可以重排 $s$ 中的字母而得到字符串 $t$。定义 $t_{\max}$ 为 $t$ 和 $\operatorname{rev}(t)$（$\operatorname{rev}(t)$ 表示把 $t$ 前后翻转得到的字符串）中字典序较大者。现在你需要让 $t_{\max}$ 的字典序最小，并输出 $t_{\max}$（而不是 $t$，所以答案是唯一的）。

$T\leqslant 10^5$，$\sum |s|\leqslant 10^5$。

---
确实有点难度的贪心。

首先发现答案显然和 $s$ 中的字母排列顺序无关，我们只关系 $s$ 中每个字母出现了多少次。

然后观察样例寻找贪心规律，发现有几组比较重要的样例：

0. $\ \ s\ \to\ t_{\max}$
1. $\tt aab\to aba$
2. $\tt abb\to bab$
3. $\tt abbcc\to bbcca$

设当前已经放到了字母 $\tt a$，其他字母同理。

先看第一组，我们发现 $\tt a$ 有超过一个时，我们可以在两端各放一个然后继续在中间放。显然最优（$t_{\max}$ 中该位 $\tt a$ 达到最小）。

再看第二组，我们**猜想** $\tt a$ 只剩一个时，最后再放 $\tt a$，因为只剩一个 $\tt a$ 所以 $t_{\max}$ 中该位至少是 $\tt b$，不如把这个 $\tt a$ 留到中间，否则 $\tt bba > bab$，先放 $\tt a$ 结果帮了倒忙。

但是你写完后发现过不了第 $10$ 组样例（即上面的 3.），你开始研究这一组。此时 $\tt a$ 只有一个，但是先放了 $\tt a$，为什么呢？发现上面“把这个 $\tt a$ 留到中间”是为了减小中间的字典序（因为答案该位已经是 $\tt b$ 改变不了了），但这里失败了：中间 $\tt cac > bcc$。你想想，如果 $\tt a$ 放中间，那么 $\tt c$ 那坨必定放在了前面，影响了答案，此时**你的 $\tt a$ 留在中间毫无作用**（因为前面已经变大了），完全可以和最后的 $\tt b$ 互换（），互换后把中间的字母从小到大排列一定比现在优（因为原来放 $\tt c$ 的位置变成了 $\tt b$)。但是如果只剩 $\tt a$ 和 $\tt b$，互换后只有副作用，只增加中间那里的字典序（$\tt b>a$），其他都没变。所以，上面第二个样例的结论只有在只剩 $\tt a$ 和最多一种字母时才能用，否则就左摆 $\tt b$ 右摆 $\tt a$ 中间摆烂（全部从小到大排）。

[我们发现，$\tt bbcca$ 中因为第一位 $\tt b > a$ 所以中间可以从小到大排列；但如果第一位左右两边都是 $\tt b$ 那中间还得从左右考虑，限制多了自然不会更优。]:wrong_证明,commented.

给几组手造样例，~~观察即猜得结论，写完交上去，A 了，所以结论正确~~ 自己感性理解一下（证明见上）：

4. $\tt abbbb\to bbbba\ >\ bbabb$ 显然 $\tt a$ 放在中间更优。
5. $\tt abbcd\to bbcda\ <\ bdacb(bcdab...)$ ~~显然~~ $\tt a$ 放在末尾更优。



整理一下：

首先从小到大枚举字母 $u$，
1. 当 $cnt_u \geqslant 2$ 时 左右各放一个，然后回到判断语句；
2. 当 $cnt_u = 1$ 时
> 找到比 $u$ 大的最小的字母 $v$（$cnt_v>0$）
> 
> 如果找不到，说明只剩 $u$ 了，把最后一个空位填完就可以跑路了
> 
> 如果 $cnt_v\geqslant2$ 且当前空位可以由 $u$ 和 $v$ 填满（即只剩 $u$ 和 $v$ 没填）那么就左右各放一个 $v$ 然后回到找 $v$ 的判断语句
>
> 否则把 $v$ 放在左边，$u$ 放在右边，然后把剩下的字母升序排满剩下的空位，跑路

完结撒花！！！

~~这么简单的题（bushi~~的题解写了半个上午，如果觉得有帮助一定要点个赞啊 qwq


[提交记录链接（完整代码）](https://codeforces.com/contest/1799/submission/195160925)
```cpp
int cnt[26];
char tmp[N], ans[N];
bool major(int Testcase = 1) {
    scanf("%s", tmp);
    memset(cnt, 0, sizeof cnt);
    int n = 0;
    for(; tmp[n]; n++) cnt[tmp[n] - 'a']++;
    int l = 0, r = n - 1;
    bool flag = 0;//flag = 1 表示要把剩下的字母升序排满剩下的空位
    int u = 0, v = 0;
    for(; u < 26; u++) {
    /**/if(flag) {//tmd应该先判这个再判下面那个while，吃了一发罚时/kk
            while(cnt[u])
                ans[l++] = u/*;*/, cnt[u]--;
            continue;
        }
        while(cnt[u] >= 2) ans[l++] = ans[r--] = u, cnt[u] -= 2;//左右各放一个 u
        if(!cnt[u]) continue;

        v = u + 1;
        fore:;
        for(; v < 26; v++) if(cnt[v] > 0) break;
        if(v == 26) {//只剩 u 了，跑路！
            ans[l++] = u;
            break;
        }
        if(cnt[v] >= 2 && r - l + 1 == cnt[u] + cnt[v]) {
            ans[l++] = ans[r--] = v, cnt[v] -= 2;
            goto fore;
        }
        else
            ans[l++] = v, ans[r--] = u, cnt[v]--, cnt[u]--, flag = 1;
    }
    for(int i = 0; i < n; i++) ans[i] += 'a';
    //之前往字符数组里塞的都是数字，所以要转成 'a'~'z' 的字母
    /**/ans[n] = 0;//否则多测输出会出锅
    puts(ans);
    return Testcase;
}
```

---

## 作者：yimuhua (赞：2)

## 题意

给你一个字符串 $s$，你可以任意重排 $s$ 使其变为一个字符串 $t$。定义 $t_{max}$ 表示取 $t$ 与将 $t$ 翻转后的字符串的字典序中更大的一个，求所有的 $t_{max}$ 中最小的。

## 思路

转化题意，变为求 $s$ 的任意排列中字典序最小的、翻转后的字典序小于等于本身的字符串。

考虑构造，显然可以从小到大枚举 $s$ 的所有字符，设当前枚举到 $x$：

若 $x$ 还剩下至少两个，则将答案的前缀和后缀各加上 $x$；

若除 $x$ 外只剩下一种字符 $y$，设其出现次数为 $k$，则将前缀加上 $\left\lceil\dfrac{k}{2}\right\rceil$ 个 $y$，加上 $x$，再加上 $\left\lfloor\dfrac{k}{2}\right\rfloor$ 个 $y$；

否则将剩下的、不包括 $x$ 的所有字符按字典序加入前缀，再加入 $x$。

这样显然是字典序最小的构造方式。

时间复杂度为 $O(n)$。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
string s, ans;
int t, l, r, p, cnt[30];
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> t;
	while(t--) {
		cin >> s, p = -1, l = 0, r = s.size() - 1, ans.resize(s.size());
		for(auto i : s)
			cnt[i - 'a']++;
		for(int i = 0; i < 26; i++) {
			while(cnt[i] > 1)
				ans[l++] = ans[r--] = i + 'a', cnt[i] -= 2;
			if(cnt[i]) {
				p = i;
				break;
			}
		}
		if(~p) {
			if(*max_element(cnt + p + 1, cnt + 26) == r - l)
				for(int i = 0; i < 26; i++)
					while(cnt[i] > 1)
						ans[l++] = ans[r--] = i + 'a', cnt[i] -= 2;
			ans[r--] = p + 'a', cnt[p]--;
			for(int i = 0; i < 26; i++)
				while(cnt[i])
					ans[l++] = i + 'a', cnt[i]--;
		}
		cout << ans << '\n';
	}
	return 0;
}
```


---

