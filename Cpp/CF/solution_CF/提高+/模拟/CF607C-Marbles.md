# Marbles

## 题目描述

In the spirit of the holidays, Saitama has given Genos two grid paths of length $ n $ (a weird gift even by Saitama's standards). A grid path is an ordered sequence of neighbouring squares in an infinite grid. Two squares are neighbouring if they share a side.

One example of a grid path is $ (0,0)→(0,1)→(0,2)→(1,2)→(1,1)→(0,1)→(-1,1) $ . Note that squares in this sequence might be repeated, i.e. path has self intersections.

Movement within a grid path is restricted to adjacent squares within the sequence. That is, from the $ i $ -th square, one can only move to the $ (i-1) $ -th or $ (i+1) $ -th squares of this path. Note that there is only a single valid move from the first and last squares of a grid path. Also note, that even if there is some $ j $ -th square of the path that coincides with the $ i $ -th square, only moves to $ (i-1) $ -th and $ (i+1) $ -th squares are available. For example, from the second square in the above sequence, one can only move to either the first or third squares.

To ensure that movement is not ambiguous, the two grid paths will not have an alternating sequence of three squares. For example, a contiguous subsequence $ (0,0)→(0,1)→(0,0) $ cannot occur in a valid grid path.

One marble is placed on the first square of each grid path. Genos wants to get both marbles to the last square of each grid path. However, there is a catch. Whenever he moves one marble, the other marble will copy its movement if possible. For instance, if one marble moves east, then the other marble will try and move east as well. By try, we mean if moving east is a valid move, then the marble will move east.

Moving north increases the second coordinate by $ 1 $ , while moving south decreases it by $ 1 $ . Similarly, moving east increases first coordinate by $ 1 $ , while moving west decreases it.

Given these two valid grid paths, Genos wants to know if it is possible to move both marbles to the ends of their respective paths. That is, if it is possible to move the marbles such that both marbles rest on the last square of their respective paths.

## 说明/提示

In the first sample, the first grid path is the one described in the statement. Moreover, the following sequence of moves will get both marbles to the end: NNESWWSWSW.

In the second sample, no sequence of moves can get both marbles to the end.

## 样例 #1

### 输入

```
7
NNESWW
SWSWSW
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
3
NN
SS
```

### 输出

```
NO
```

# 题解

## 作者：tder (赞：1)

妙妙题。

定义倒置就是 $\tt S\leftrightarrow N$ 且 $\tt W\leftrightarrow E$，用 $f(c)$ 表示。而逆序就是 $\{s_1,s_2,\cdots,s_n\}\leftrightarrow\{s_n,s_{n-1},\cdots,s_1\}$。

首先看样例猜想是：

> 若最后一次操作互为倒置则无解，反之有解。

但是可以被 $\tt ES$ 和 $\tt NW$ 卡掉。这样相当于两个路径是互为逆序且倒置的。实际上就是某一个点到达终点后，为了使另一个点也到，就会让这个点回退。推广到有两个后缀即可。

因此，结论是：

> 若存在 $a$ 的后缀 $a'$ 和 $b$ 的后缀 $b'$，满足 $a'$ 和 $b'$ 互为逆序且倒置，则无解，反之有解。

倒置很好处理，可以先把其中一个倒置，于是转化为逆序且相等。而找逆序后缀是困难的，不妨将其中一个逆序，并将另一个拼接上，若得到的新字符串的 border 非零则相当于找到了满足的后缀。形式化的讲，新字符串是：

$$
s=\{f(a_1),f(a_2),\cdots,f(a_n),b_n,b_{n-1},\cdots,b_1\}
$$

新字符串的 border 值用 kmp 处理是简单的。

时间复杂度 $O(n)$。

---

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
const int N = 2e6 + 5;
namespace Kmp {
	int p[N]; string s;
	void init(string t) {
		s = t;
		for(int i = 1, j = 0; i < s.length(); i++, p[i] = j) {
			while(j && s[i] != s[j]) j = p[j];
			if(s[i] == s[j]) j++;
		}
	}
	int border() {
		return p[s.length()];
	}
};
int n;
string a, b, s;
char change(char c) {
	if(c == 'N') return 'S';
	if(c == 'S') return 'N';
	if(c == 'E') return 'W';
	if(c == 'W') return 'E';
}
signed main() {
	cin>>n>>a>>b;
	for(auto &c : a) c = change(c);
	// cout<<a<<endl;
	for(int i = 0, j = a.length() - 1; i < j; i++, j--) swap(a[i], a[j]);
	s = a + b;
	Kmp::init(s);
	if(Kmp::border()) cout<<"NO"<<endl;
	else cout<<"YES"<<endl;
}
```

---

## 作者：Priestess_SLG (赞：0)

手玩了一会儿之后发现，考虑到把一个弹珠移动到终点之后，若另一个弹珠想要移动到终点则必须执行其最后一次操作。此时若这个操作和第一个弹珠的操作相逆，则显然执行这个操作之后会把第一个弹珠给移出来，而若要把第一个弹珠移回去，则第二个弹珠又被移出了。因此这个情况需要被判掉。

但是这显然是不对的。考虑到如果两个弹珠最后两个操作逆序，且逆序对应操作相逆，那么想要把其中一个弹珠移过去，会让另外故一个弹珠以同样的方式被移出来，而要将其移回去就会把第一个弹珠再移出来。这种情况也不符合条件。

同样的，将其扩展，若两个弹珠最后 $k$ 个操作逆序且逆序对应操作相逆，那么两个弹珠将在最后阶段不停的进行死循环。容易（打表）发现其余所有情况均可以满足条件。因此问题被转化为：

> 有两个字符串 $s_1,s_2$，长度均为 $n$。现在问是否存在一个 $k$ 满足 $1\le k<n$，满足 $s_1,s_2$ 分别取出最后 $k$ 个字符，并将 $s_2$ 反序，对 $s_2$ 的每一个字符求逆后，$s_1=s_2$。

这个问题是简单的，直接正反哈希一下就行了。时间复杂度为 $O(n)$ 可以通过。

代码：

```cpp
#pragma GCC optimize(3, "Ofast", "inline")
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1000100;
int a[N];
char s[N], t[N];
inline char anot(char o) {
    if (o == 'N') o = 'S'; else if (o == 'S') o = 'N';
    if (o == 'E') o = 'W'; else if (o == 'W') o = 'E';
    return o;
}
signed main() {
    // cin.tie(0)->sync_with_stdio(false);
    cout << fixed << setprecision(15);
    int n;
    cin >> n;
    scanf("%s%s", s + 1, t + 1);
    for (int i = 1; i < n; ++i) {
        t[i] = anot(t[i]);
    }
    using ull = unsigned long long;
    ull h1 = 0, h2 = 0;
    ull bit = 1, base = 13331;
    for (int i = n - 1; i; --i) {
        h1 = h1 + bit * s[i];
        h2 = h2 * base + t[i];
        if (h1 == h2) {
            cout << "NO\n";
            return 0;
        }
        bit *= base;
    }
    cout << "YES\n";
}
```

---

