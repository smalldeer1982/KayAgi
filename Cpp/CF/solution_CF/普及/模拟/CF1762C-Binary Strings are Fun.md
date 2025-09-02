# Binary Strings are Fun

## 题目描述

A binary string $ ^\dagger $ $ b $ of odd length $ m $ is good if $ b_i $ is the median $ ^\ddagger $ of $ b[1,i]^\S $ for all odd indices $ i $ ( $ 1 \leq i \leq m $ ).

For a binary string $ a $ of length $ k $ , a binary string $ b $ of length $ 2k-1 $ is an extension of $ a $ if $ b_{2i-1}=a_i $ for all $ i $ such that $ 1 \leq i \leq k $ . For example, 1001011 and 1101001 are extensions of the string 1001. String $ x= $ 1011011 is not an extension of string $ y= $ 1001 because $ x_3 \neq y_2 $ . Note that there are $ 2^{k-1} $ different extensions of $ a $ .

You are given a binary string $ s $ of length $ n $ . Find the sum of the number of good extensions over all prefixes of $ s $ . In other words, find $ \sum_{i=1}^{n} f(s[1,i]) $ , where $ f(x) $ gives number of good extensions of string $ x $ . Since the answer can be quite large, you only need to find it modulo $ 998\,244\,353 $ .

 $ ^\dagger $ A binary string is a string whose elements are either $ \mathtt{0} $ or $ \mathtt{1} $ .

 $ ^\ddagger $ For a binary string $ a $ of length $ 2m-1 $ , the median of $ a $ is the (unique) element that occurs at least $ m $ times in $ a $ .

 $ ^\S $ $ a[l,r] $ denotes the string of length $ r-l+1 $ which is formed by the concatenation of $ a_l,a_{l+1},\ldots,a_r $ in that order.

## 说明/提示

In the first and second test cases, $ f(s[1,1])=1 $ .

In the third test case, the answer is $ f(s[1,1])+f(s[1,2])=1+2=3 $ .

In the fourth test case, the answer is $ f(s[1,1])+f(s[1,2])+f(s[1,3])=1+1+1=3 $ .

 $ f(\mathtt{11})=2 $ because two good extensions are possible: 101 and 111.

 $ f(\mathtt{01})=1 $ because only one good extension is possible: 011.

## 样例 #1

### 输入

```
6
1
1
1
0
2
11
3
010
9
101101111
37
1011011111011010000011011111111011111```

### 输出

```
1
1
3
3
21
365```

# 题解

## 作者：Special_Tony (赞：3)

# 思路
我们手搓一个数据：$111011$。

第一个前缀：$1$。没什么好说，只有 $2^0=1$ 种情况。

第二个前缀：$11$。这时在中间可以填 $0$ 或 $1$，出现 $2^1=2$ 种情况。

第三个前缀：$111$。这时它们之间还是可以随便填，有 $2^2=4$ 种情况。

第四个前缀：$1110$。此时出现转折——因为出现了子串 $10$，所以前面的所有空位都必须填 $0$，只有一种情况。

第五个前缀：$11101$。它还是顺顺利利可以填任何数字，$2$ 种情况。

第六个前缀：$111011$。它依然可以填任何数字，$4$ 种。

然后我们发现，如果出现 $10$ 或 $01$，那么瞬间归 $1$，否则可以填任何数字，方案数是上一个前缀的 $2$ 倍。最后把所有前缀的方案数累加起来就好。
# 代码
```cpp
# include <bits/stdc++.h>
typedef long long ll;
using namespace std;
const int mod = 998244353;
int t, n, sum, now;
string a;
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> t;
	while (t --) {
		cin >> n >> a;
		sum = now = 1;
		for (int i = 1; i < n; ++ i) {
			if (a[i] != a[i - 1])
				now = 1;
			else
				now <<= 1, now %= mod;
			sum += now, sum %= mod;
		}
		cout << sum << '\n';
	}
	return 0;
}
```

---

## 作者：Walrus (赞：3)

## 题意
给你一个长度为 $m$ 的**二进制**字符串 $a$，我们对于此长度为 $m$ 的字符串，以每两位为单位，分别向其中插入 $0$ 或 $1$。可以证明，这一共有 $2^{m-1}$ 种情况，因为在补充时，每一位都有 $0$ 或 $1$ 两种选择，一共 $m-1$ 组，所以一共有这么多种情况。现在需要在这些情况中，求出“好字符串”的数量。

**关于“好字符串”的定义：在一个长度为 $m$ 的字符串中，已经完成插入操作，得到新字符串后，若对于所有在 $1\leq i \leq 2\times m - 1$ 的奇数 $i$，$a_i$ 是在 $a_1\sim a_i$ 中出现次数最多的字符， 则该字符串是“好字符串**”。

这个“好字符串”的定义比较难懂，关键是理解它的定义才能入手，话说这题目翻译问题有点多啊。

## 分析
因为是每一组统计方案数，考虑使用类似于**递推**的方式求解。

新字符串的奇数位其实对应着老字符串的每一位，于是发现有以下结论。

对于每两位之间的情况，可以发现，应该有两种情况讨论。

- 如果在左右两边相同的两位之间插入一个 $0$ 或 $1$，则二者都可以插入其中，用乘法原理，应将最后的答案 $ans\times 2$。
- 反之，如果这一组左右两边不相同，不同于上述情况，答案应该归 $1$。

我在这里用另一种比较简单通俗好理解的方式证明。

**在递推到这一组时，我们假设为字符串 $a$ 的第 $i$ 和 $i - 1$ 号位，你肯定要保证前面 $a_1\sim a_{(i-1)\times 2-1}$ 得是一个“好字符串”。假设前面一共有 $x$ 个 $0$，$y$ 个 $1$，假设 $a_{i-1}=1$，那么有 $y>x$，又因为你 $a_i \neq a_{i-1}$，如果现在是个“好字符串”，说明你加了原来一个和插入一个 $0$ 或 $1$ 得有 $x>y$，也就是你在 $y>x$ 的基础上又要通过插入操作变成 $x>y$，所以 $x$ 和 $y$ 的差**至少增加了 $2$**，$y$ 又不可能减少，那你的 $x$ 就必须增加 $2$，你的 $x$ 也最多只能增加 $2$，所以当遇到这种情况时，你原来必须要有 $y>x$ 且 $y-x=1$，在进行了这一位的操作后，你的 $x$ 增加了 $2$，又因为你原来的 $a_i$ 会为 $x$ 做贡献，所以这一位只能有一种情况，也就是这一位只能填 $a_i$，为了满足 $y>x$ 且 $y-x=1$，你前面也只能有一种情况，也就是你前面能填两种情况的现在都只能填 $a_i$。所以答案归 $1$。**

举个例子吧，假设原来有一个长度为 $4$ 的字符串 $1110$。

- 第一组：$1$ 和 $1$ 之间不管插入 $0$ 或 $1$，得到的字符串 $101$ 或 $111$ 均为“好字符串”。
- 第二组：又是 $1$ 和 $1$，同上。
- 第三组：我们可以试着填一下，假设第一组与第二组均填 $1$，则这个字符串有两种可能性，即 $1111100$ 或 $1111110$，显然，二者均不为“好字符串”，如果在这长度为 $7$ 的字符串中，它要满足“好字符串”，原来已有 $3$ 个 $1$，于是你剩下的必须都填 $0$，故有且仅有 $1$ 种填法。此结论可以推广到任意长度的字符串。

## 代码
RMJ 炸了，在 CF 上提交正确。
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e6 + 5;
const int mod = 998244353;
int n, m, h, t;
string s;

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin >> t;	
	while(t--) {
		cin >> n;
		cin >> s;
		int ans = 0, cnt = 2;
		for(int i = 1;i < n;i++) {
			if(s[i] == s[i - 1])
				cnt = (cnt << 1ll) % mod;
			else {
				ans = (ans + cnt - 1) % mod;
				cnt = 2;
			}
		}		
		ans = (ans + cnt - 1) % mod;
		cout << ans << '\n';
	}
}
```
注意，本帖子所有“字符串”的描述均指 $01$ 串。


---

## 作者：郑朝曦zzx (赞：2)

### 题解

结论如下：

- 如果 $s_i = s_{i - 1}$ 那么那么这一位填啥都可以，即 `ans *= 2`
- 否则，答案归 $1$

第二个结论没那么显然，此处证明一下。在前 $2i - 3$ 位 $s_{i - 1}$ 多，即 $s_i \lt s_{i-1}$，在前 $2i-1$ 位 $s_i$ 多，即 $s_{i-1} \lt s_i + 2$。这是第 $2i-1$ 和 $2i-2$ 位都填 $s_i$ 的情况，才刚刚够满足条件。所以上一次 $s_{i-1}$ 正好多一个，这次 $s_i$ 正好多一个，想想我们递归到 $s{1}$，也只有 $1$ 种情况（很显然，只有一种情况能满足 $s_1$）。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define pf printf
#define test int T = rd(); while (T--)
#define F(i, a, b) for (int i = (a); i <= (b); ++i)
#define fr freopen("input.txt", "r", stdin);
#define IO ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#define yes printf("YES\n");
#define no printf("NO\n");
#define int long long
inline int rd()
{
    char c=getchar(); int x=0, s=1;
    while(c<'0'||c>'9') { if(c=='-')s=-1;c=getchar();}
    while(c>='0'&&c<= '9') { x=(x<<3)+(x<<1)+c-'0';c=getchar();}
    return x*s;
}
char a[2000010];
const int mod = 998244353;
signed main()
{
	test
	{
		int n, ans = 1, tot = 0;
		cin >> n;
		a[0] = '!';
		F(i, 1, n)
		{
			cin >> a[i];
			if (a[i] == a[i - 1]) ans = ans * 2 % mod;
			else ans = 1;
			tot = (tot + ans) % mod;
		}
		printf("%lld\n", tot);
	}
    return 0;
}
```


---

## 作者：winter2020 (赞：0)

关于题意...这个咕咕咕的人写不动啦！

一个一个前缀处理，很容易想到从上一个转移。

先放结论：

- 当 $s_i \neq s_{i-1}$ 时，这里两种数都可以插，也就是上一个的方案数乘2。

- 如果不相等，就只有一种情况。

相等的情况很显然，不等的情况网上有的题解证的不太严谨，我试试证一个吧。

设 $s_i=1$，$s_{i-1}=0$，显然这里插进来的数必须是1，而且要从中间数是0变到中间数是1。也就是 `s[1, i-1]` 中1的个数只能跟 `s[1, i-1]` 中0的个数差1。

两位两位对前面的字符考虑，如果出现：

- $1\ 1$ 中间填0。
- $0\ 1$ 中间填1。
- $1\ 1$ 中间填0。
- $0\ 0$ 中间只能填1！

如果中间填0，显然之后的1只能在插进去的数里出现了，在原本的字符串上出现是不可能的。可以用数学归纳法，（这里全是插完数的字符串）前3个数全是0，第5个数只能是1，这样第七个数也只能是1...

所以只有一种情况。

```cpp
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long LL;
const int mod = 998244353;
int n;
string s;

int main() {
    int T;
    cin >> T;
    while (T -- ) {
        cin >> n >> s;
        int now = 1, ans = 1;
        for (int i = 1; i < n; i ++ ) {
            if (s[i] != s[i - 1]) now = 1;
            else now = now * 2ll % mod;
            ans = ((LL)ans + now) % mod;
        }
        cout << ans << endl;
    }
    return 0;
}
```

---

