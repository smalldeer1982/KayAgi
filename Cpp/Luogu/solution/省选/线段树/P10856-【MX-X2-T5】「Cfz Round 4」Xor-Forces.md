# 【MX-X2-T5】「Cfz Round 4」Xor-Forces

## 题目背景

原题链接：<https://oier.team/problems/X2E>。

---

✿(。◕ᴗ◕。)✿


## 题目描述

给定一个长度为 $n=2^k$ 的数组 $a$，下标从 $0$ 开始，维护 $m$ 次操作：

1. 操作一：给定 $x$，设数列 $a'$ 满足 $a'_i=a_{i\oplus x}$，将 $a$ 修改为 $a'$。其中 $\oplus$ 表示按位异或运算。
2. 操作二：给定 $l,r$，查询 $a$ 的下标在 $l,r$ 之间的子数组有多少颜色段。**不保证 $\bm {l\le r}$，若 $\bm{l > r}$，请自行交换 $\bm{l,r}$。**

其中，一个极长的所有数都相等的子数组称为一个颜色段。

部分测试点要求强制在线。

## 说明/提示

**【样例解释 #1】**

此样例允许离线。

初始时 $a=[1,2,1,3,2,4,5,1]$。

$a$ 的下标在 $1,5$ 之间的子数组为 $[2,1,3,2,4]$，它的颜色段数为 $5$。

进行重排操作后，$a=[3,1,2,1,1,5,4,2]$。

$a$ 的下标在 $5,1$ 之间的子数组为 $[1,2,1,1,5]$，它的颜色段数为 $4$。

**【样例解释 #2】**

此样例除强制在线外，与样例 \#1 完全一致。

**【数据范围】**

对于所有测试数据，$T \in \{ 0, 1 \}$，$0\le k\le 18$，$n=2^k$，$1\le m\le 2\times 10^5$，$1\le a_i\le n$，$\mathit{op} \in \{ 1, 2 \}$，$0\le x,l,r < n$。

**本题采用捆绑测试。**

- Subtask 1（15 points）：$T=1$，$k\le 10$，$m\le 10^3$。
- Subtask 2（15 points）：$T=1$，不存在操作一。
- Subtask 3（20 points）：$T=1$，对于所有操作二，要么 $l=0,r=n-1$，要么 $l=n-1,r=0$。
- Subtask 4（20 points）：$T=0$。
- Subtask 5（30 points）：$T=1$。

**注意：Subtask 5 依赖前四个 Subtask，只有通过前四个 Subtask 才能尝试获得该 Subtask 的分数。**

## 样例 #1

### 输入

```
0 3 3
1 2 1 3 2 4 5 1
2 1 5
1 3
2 5 1```

### 输出

```
5
4```

## 样例 #2

### 输入

```
1 3 3
1 2 1 3 2 4 5 1
2 1 5
1 6
2 0 4```

### 输出

```
5
4```

## 样例 #3

### 输入

```
1 4 16
12 9 5 9 12 12 9 12 9 16 5 9 12 16 9 5
2 0 4
1 15
2 14 0
1 15
2 6 0
2 4 14
1 0
1 14
2 4 10
2 6 3
1 7
2 4 13
1 3
1 3
2 4 3
2 15 2```

### 输出

```
5
7
4
7
9
5
7
2
11```

# 题解

## 作者：xhgua (赞：15)

首先我们发现操作 $1$ 具有结合律，于是我们要解决的就是每次给定一个 $x$，令 $a'_i = a_{i\oplus x}$，查询 $a'$ 下标在 $[l, r]$ 内的子数组的颜色段个数。

有个显然的转化：区间颜色段个数等于区间长度减去相邻同色对数，只需考虑如何计算 $l\lt i\leq r, a_{i\oplus x} = a_{(i - 1)\oplus x}$ 的 $i$ 个数即可。 

考虑线段树，当询问跨过区间中点 $m$ 时，可以直接判断 $a_{m \oplus x}$ 和 $a_{(m - 1)\oplus x}$ 这一对是否相等，并递归到两个儿子去计算。

现在我们要解决的就是线段树上某个节点对应的答案，因为每次异或的 $x$ 不同，一个节点对应的区间中的元素顺序会被打乱，每个节点对应的答案也不是唯一的，此时我们显然无法对于每个节点储存单一的答案。

这里给出一个结论：如果一个节点对应的区间长度为 $l$，那么对这个区间有用的 $x$ 只有 $l$ 种！

这是为什么呢？考虑询问的是 $\texttt{0 1 2 3}$ 这一段区间，$x = 5$，此时区间长度 $l$ 为 $4$，区间内下标异或上 $x$ 后结果是 $\texttt{5 4 7 6}$，正好对应区间 $\texttt{4 5 6 7}$ 在 $x = 1$ 时的答案！

我们发现，对于 $x\geq l$ 的部分，我们其实相当于将该区节点对应区间的答案转化为了线段树上同一层另一个节点在 $x' = x \bmod l$ 时的答案，而这个节点通过位运算是不难找到的。

于是对于每个节点，我们只需要维护 $0\sim l - 1$ 这 $l$ 种不同的 $l$ 对应的答案，查询时只需计算出另一个节点的位置，并查询其在 $x' = x \bmod l$ 的答案即可。

由于线段树一共 $\log n$ 层，每层节点的总长度之和为 $n$，于是时间复杂度和空间复杂度均为 $\mathcal{O}(n\log n)$。

代码中线段树的实现是左闭右开。

```cpp
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 3e5 + 5, LOG = 20;

int o, k, m, n;
int a[N], sum[N], M[LOG][N];
std::vector<int> f[N << 2];

#define ls(u) (u << 1)
#define rs(u) (u << 1 | 1)

void build(int u, int l, int r) {
	int len = r - l, bit = std::__lg(len); f[u].resize(len); M[bit][l] = u;
	if (len == 1) return f[u][0] = 0, void();
	int mid = (l + r) >> 1;
	build(ls(u), l, mid); 
	build(rs(u), mid, r);
	for (int x = 0; x < len; x++) {
		if (x < len / 2) f[u][x] = f[ls(u)][x] + f[rs(u)][x] + (a[mid ^ x] == a[(mid - 1) ^ x]);
		else f[u][x] = f[ls(u)][x - (len / 2)] + f[rs(u)][x - (len / 2)] + (a[mid ^ x] == a[(mid - 1) ^ x]);
	}
}

int query(int u, int l, int r, int ql, int qr, int y) {
	int bit = std::__lg(r - l); 
	if (ql <= l && r - 1 <= qr) return f[M[bit][l ^ (y >> bit << bit)]][y % (1 << bit)];
	int mid = (l + r) >> 1, L = 0, R = 0; bool fL = false, fR = false;
	if (ql < mid)  L = query(ls(u), l, mid, ql, qr, y), fL = true;
	if (qr >= mid) R = query(rs(u), mid, r, ql, qr, y), fR = true;
	return fL ? (fR ? L + R + (a[mid ^ y] == a[(mid - 1) ^ y]) : L) : R;
}

int main() {

	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> o >> k >> m; n = (1 << k);
	for (int i = 0; i < n; i++) std::cin >> a[i];

	build(1, 0, n);

	int lst = 0, y = 0;
	for (int i = 1; i <= m; i++) {
		int op; std::cin >> op;
		if (op == 1) {
			int x; std::cin >> x; x ^= (o * lst);
			y ^= x;
		}
		if (op == 2) {
			int l, r; std::cin >> l >> r; l ^= (o * lst), r ^= (o * lst);
			if (l > r) std::swap(l, r);
			std::cout << (lst = r - l + 1 - query(1, 0, n, l, r, y)) << "\n";
		}
	}

	return 0;
}
```

---

## 作者：rui_er (赞：11)

本题解为 Xor-Forces 的官方题解。

**解法一：我会暴力（子任务一，期望得分 $15$ 分）**

按题意模拟即可。

时间复杂度 $\mathcal O(nm)$，空间复杂度 $\mathcal O(n)$。

**解法二：我会线段树（子任务二，期望得分 $15$ 分）**

没有修改操作，就是查询区间颜色段数量，线段树每个节点维护左端点颜色、右端点颜色、颜色段数量即可。

时间复杂度 $\mathcal O(n+m\log n)$，空间复杂度 $\mathcal O(n)$。

**解法三：我会预处理（子任务三，期望得分 $20$ 分）**

我们发现不管如何进行操作，数列都只有 $n$ 种，分别是 $b_x:b_{x,i}=a_{i\oplus x}$（$0\le x < n$）。我们记 $b_x$ 的颜色段个数为 $ans_x$，问题转化为求出所有 $ans_x$。

直接做还是 $\mathcal O(n^2)$ 的，但是我们可以递推。我们可以暴力求出 $ans_0$，假设我们已经求出了 $ans_{0\cdots p-1}$，接下来我们要求 $ans_p$。

我们设 $t$ 为 $p$ 的二进制最高位，尝试由 $ans_{p\oplus t}$ 推出 $ans_p$。考虑 $b_{p\oplus t}\to b_p$ 的变化，其实就是按照下标比 $t$ 高的位的异同分为 $\frac{n}{2t}$ 组，则这次操作就是将每组内下标的 $t$ 的这一位为 $1$ 的元素放在为 $0$ 的元素前面，可能影响 $ans_p$ 的只有每组正中间的断点以及两组中间的连接处，共 $\frac{n}{t}$ 个。

我们令 $ans_p\gets ans_{p\oplus t}$，然后枚举这 $\frac{n}{t}$ 个可能影响答案的位置，计算答案的变化量即可。

其实是个类似于格雷码的 trick。

时间复杂度 $\mathcal O(n\log n+m)$，空间复杂度 $\mathcal O(n)$。

**解法四：我会离线（子任务四，期望得分 $20$ 分）**

这次是区间询问，无法像「子任务三」一样预处理，但是可以离线，因此考虑按照下标异或的 $x$ 将所有询问分类。

分类后，对于每一类询问，是不带修改的，这部分和「子任务二」是一样的，我们可以简单地线段树来做。问题转化成了如何快速地执行下标异或操作。

由于 $n=2^k$，线段树其实相当于一棵 01trie。「解法三」告诉我们：在下标 $\oplus$ 一个 $2$ 的幂时，数列的变化相当于是交换了一层线段树节点的左右子树，这个线段树是支持的。

可以继续使用类似于格雷码的维护技巧，使得相邻两个异或的 $x$ 只有一个二进制位不同，使用线段树维护求解即可。

时间复杂度 $\mathcal O(n\log n+m\log n)$，空间复杂度 $\mathcal O(n)$。

**解法五：我依然会线段树（正解，期望得分 $100$ 分）**

这个解法的难点可能在于发现暴力是正确的（？）。

转化一下操作，也就是：

> 给定 $l,r,x$，求 $a_{l\oplus x},a_{(l+1)\oplus x},\cdots,a_{r\oplus x}$ 的颜色段数量。

接着考虑如何使用线段树维护它。

在「解法四」中我们说过，这棵线段树相当于一棵 01trie，因此我们知道一个节点代表的下标区间，一定是二进制高位已经确定，低位随便取的状态。于是我们不妨对于每一种取值都维护一个答案。

考虑向上合并两个节点信息的过程，我们记 $\operatorname{lc}(u),\operatorname{rc}(u)$ 为节点 $u$ 的左右儿子。现在希望求节点 $u$ 在下标异或 $x$ 时的答案，怎么求？

- 记 $x$ 去掉最高位的结果为 $x'$。请注意这里是用的 01trie 的理解方式，因此 $x$ 是定长二进制串，包含前导零，与前文意义略有不同。
- 若 $x$ 的最高位为 $0$，则合并 $\operatorname{lc}(u)$ 在 $x'$ 处的答案和 $\operatorname{rc}(u)$ 在 $x'$ 处的答案即可。
- 若 $x$ 的最高位为 $1$，则合并 $\operatorname{rc}(u)$ 在 $x'$ 处的答案和 $\operatorname{lc}(u)$ 在 $x'$ 处的答案即可。

最后是区间查询操作：

- 若查询区间完全包含于节点代表的区间，返回对应 $x$ 的答案即可。
- 若 $x$ 的最高位为 $0$，则没啥特殊的，正常查询即可。
- 若 $x$ 的最高位为 $1$，则查询到这里后需要交换左右子树，我们算出在右子树和左子树对应的查询区间，继续查询即可。

时间复杂度 $\mathcal O(n\log n+m\log n)$，空间复杂度 $\mathcal O(n\log n)$。

```cpp
//By: OIer rui_er
#include <bits/stdc++.h>
#define rep(x, y, z) for(int x = (y); x <= (z); ++x)
#define per(x, y, z) for(int x = (y); x >= (z); --x)
#define debug(format...) fprintf(stderr, format)
#define fileIO(s) do {freopen(s".in", "r", stdin); freopen(s".out", "w", stdout);} while(false)
#define endl '\n'
using namespace std;
typedef long long ll;

mt19937 rnd(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
int randint(int L, int R) {
    uniform_int_distribution<int> dist(L, R);
    return dist(rnd);
}

template<typename T> void chkmin(T& x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T& x, T y) {if(x < y) x = y;}

template<int mod>
inline unsigned int down(unsigned int x) {
	return x >= mod ? x - mod : x;
}

template<int mod>
struct Modint {
	unsigned int x;
	Modint() = default;
	Modint(unsigned int x) : x(x) {}
	friend istream& operator>>(istream& in, Modint& a) {return in >> a.x;}
	friend ostream& operator<<(ostream& out, Modint a) {return out << a.x;}
	friend Modint operator+(Modint a, Modint b) {return down<mod>(a.x + b.x);}
	friend Modint operator-(Modint a, Modint b) {return down<mod>(a.x - b.x + mod);}
	friend Modint operator*(Modint a, Modint b) {return 1ULL * a.x * b.x % mod;}
	friend Modint operator/(Modint a, Modint b) {return a * ~b;}
	friend Modint operator^(Modint a, int b) {Modint ans = 1; for(; b; b >>= 1, a *= a) if(b & 1) ans *= a; return ans;}
	friend Modint operator~(Modint a) {return a ^ (mod - 2);}
	friend Modint operator-(Modint a) {return down<mod>(mod - a.x);}
	friend Modint& operator+=(Modint& a, Modint b) {return a = a + b;}
	friend Modint& operator-=(Modint& a, Modint b) {return a = a - b;}
	friend Modint& operator*=(Modint& a, Modint b) {return a = a * b;}
	friend Modint& operator/=(Modint& a, Modint b) {return a = a / b;}
	friend Modint& operator^=(Modint& a, int b) {return a = a ^ b;}
	friend Modint& operator++(Modint& a) {return a += 1;}
	friend Modint operator++(Modint& a, int) {Modint x = a; a += 1; return x;}
	friend Modint& operator--(Modint& a) {return a -= 1;}
	friend Modint operator--(Modint& a, int) {Modint x = a; a -= 1; return x;}
	friend bool operator==(Modint a, Modint b) {return a.x == b.x;}
	friend bool operator!=(Modint a, Modint b) {return !(a == b);}
};

const int N = 1 << 18 | 5;

int T, k, n, m, a[N], now, lst;

struct Node {
    int l, r, cnt;
    Node(int a = 0, int b = 0, int c = 0) : l(a), r(b), cnt(c) {}
    friend bool operator==(const Node& u, const Node& v) {
        return u.l == v.l && u.r == v.r && u.cnt == v.cnt;
    }
    friend Node operator+(const Node& u, const Node& v) {
        if(u == Node()) return v;
        if(v == Node()) return u;
        return Node(u.l, v.r, u.cnt + v.cnt - (u.r == v.l));
    }
};
struct SegTree {
    vector<Node> t[N << 2];
    #define lc(u) (u << 1)
    #define rc(u) (u << 1 | 1)
    void build(int* a, int u, int l, int r) {
        int len = r - l + 1;
        t[u].resize(len);
        if(l == r) {
            t[u][0] = Node(a[l], a[r], 1);
            return;
        }
        int mid = (l + r) >> 1;
        build(a, lc(u), l, mid);
        build(a, rc(u), mid + 1, r);
        rep(i, 0, len - 1) {
            if(i < (len >> 1)) t[u][i] = t[lc(u)][i] + t[rc(u)][i];
            else t[u][i] = t[rc(u)][i ^ (len >> 1)] + t[lc(u)][i ^ (len >> 1)];
        }
    }
    Node query(int u, int l, int r, int ql, int qr, int qx, int pos) {
        if(qr < l || r < ql || qr < ql) return Node();
        if(ql <= l && r <= qr) {
            if(l == r) return t[u][0];
            else return t[u][qx & ((1 << (pos + 1)) - 1)];
        }
        int mid = (l + r) >> 1;
        if(!((qx >> pos) & 1)) {
            return query(lc(u), l, mid, ql, qr, qx, pos - 1)
                 + query(rc(u), mid + 1, r, ql, qr, qx, pos - 1);
        }
        else {
            int ql1 = ql, qr1 = min(mid, qr), ql2 = max(mid + 1, ql), qr2 = qr;
            return query(rc(u), mid + 1, r, mid + 1 + ql1 - l, mid + 1 + qr1 - l, qx, pos - 1)
                 + query(lc(u), l, mid, l + ql2 - (mid + 1), l + qr2 - (mid + 1), qx, pos - 1);
        }
    }
}sgt;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> T >> k >> m;
    n = 1 << k;
    rep(i, 0, n - 1) cin >> a[i];
    sgt.build(a, 1, 0, n - 1);
    while(m--) {
        int op;
        cin >> op;
        if(op == 1) {
            int x;
            cin >> x;
            x ^= T * lst;
            now ^= x;
        }
        else {
            int x, y;
            cin >> x >> y;
            x ^= T * lst; y ^= T * lst;
            if(x > y) swap(x, y);
            cout << (lst = sgt.query(1, 0, n - 1, x, y, now, k - 1).cnt) << endl;
        }
    }
    return 0;
}
```

---

## 作者：vectorwyx (赞：8)

> 提示：学习过 01trie **可能**有助于理解本题结构

首先注意到区间 $[l,r]$ 的颜色段数等于 $1+\sum_{i=l}^{r-1}[a_i\not=a_{i+1}]$。那么假设当前所有操作 1 的 $x$ 的异或和为 $X$，操作 2 即为查询 $1+\sum_{i=l}^{r-1}[a_{i\oplus X}\not=a_{(i+1)\oplus X}]$，即我们需要的信息是 $\sum_{i=l}^{r-1}[a_{i\oplus X}\not=a_{(i+1)\oplus X}]$。

接下来考虑一个区间 $[l,r)$ 内的所有下标异或上 $X$ 有什么影响。直觉是 $[l,r)$ 顶多变成 $O(\log (r-l+1))$ 个不交的区间（当然，区间内部顺序可能改变）。为什么？因为如果一个区间形如 $[a2^b,(a+1)2^b)$，那么对于任意的 $X$ 存在 $a'$ 使得 $\forall i\in[a2^b,(a+1)2^b),(i\oplus X)\in[a'2^b,(a'+1)2^b)$，我们把这样的区间称作**特殊**的。实际上可以直接算出 $a'=a\oplus\lfloor\frac{X}{2^b}\rfloor$。放到 01trie 上理解可能更直观，就是说一棵子树异或上一个数之后还是一棵子树，只不过是把某些点的左右儿子互换了而已。

而如果对整个序列建一棵线段树，那它的每个结点对应的都是特殊区间（比如根结点是 $[0,2^k)$），只需按照正常线段树的查询方式就可以将 $[l,r)$ 分裂成 $O(\log (r-l+1))$ 个特殊区间。区间接壤处的贡献是好处理的，而分裂出的每个特殊区间异或上 $X$ 之后还是一个特殊区间，所以问题只剩下求某个特殊区间的信息。注意到一个区间的信息只与它在异或 $X$ 后的内部顺序有关，假设区间长度为 $2^w$，那么内部顺序只与 $X$ 最低的 $w$ 位有关，所以一共有 $2^w$ 种。我们直接把所有情况的答案预处理出来，即对于每个结点 $[l,r](r-l+1=2^w)$ 和 $[0,2^w)$ 中的每个 $x$ 求出 $\sum_{i=l}^{r-1}[a_{i\oplus x}\not=a_{(i+1)\oplus x}]$。这个当然不能暴力枚举，但是可以由这个结点的左右儿子的信息合并上来。具体就是按 $x<2^{w-1}$ 和 $x\ge 2^{w-1}$ 分类讨论，因为 $x$ 的最高位会影响左右儿子在异或 $x$ 后的顺序，抛却最高位剩下的信息都在左右儿子那里处理过了，直接加起来就行。合并的复杂度是 $O(1)$ 的，于是预处理的时空复杂度都是 $O(2^k k)$，因为每个位置都被 $k$ 个结点的区间包含，因此贡献了 $O(k)$ 的复杂度。如果你学过猫树，理解起来应该并不困难；如果你没学过猫树，我建议你去学一学（x

预处理完毕后，查询某个特殊区间的信息的复杂度变成 $O(1)$，那么询问 $[l,r]$ 的复杂度是 $O(k)$ 的。至此我们解决了本题。

赛时懒得写线段树了，就差分了一下，毕竟 $[0,r)$ 是很容易裂成 $O(\log r)$ 个特殊区间的。

代码如下：（码字不易，点个赞再走呗 QAQ，非常感谢！！）

```cpp
#include<bits/stdc++.h>
namespace vectorwyx{
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define mk make_pair
#define sml(x,y) (x=min(x,y))
#define big(x,y) (x=max(x,y))
#define ll long long
#define uint unsigned
#define ull unsigned long long
#define umap unordered_map
#define db double
#define fo(i,x,y) for(int i=(x);i<=(y);++i)
#define go(i,x,y) for(int i=(x);i>=(y);--i)
#define ptc putchar
#define gtc getchar
#define emp emplace
#define re return
#define co continue
#define brk break
#define HH (ptc('\n'))
#define bctz __builtin_ctz
#define bclz __builtin_clz
#define bppc __builtin_popcount
using namespace std;
ll seed=chrono::system_clock::now().time_since_epoch().count();
mt19937 rnd(seed);
inline int rm(int x,int y){return (int)(rnd()%(y-x+1ll)+x);}
inline int read(){signed ch=getchar();int x=0,f=1;while(!isdigit(ch)){if(ch==(int)('-'))f=-1;ch=getchar();}while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
template<typename T> void out(T *a,int l,int r){fo(i,l,r) cout<<*(a+i)<<' ';puts("");}

const int N=1<<19;
int a[N],n,lg,q,ct,X,f[19][N];
struct Node{
    int l,r,v;
}bit[30];

namespace Pool{
const int N=1e7;
int pool[N],id=1;
int* get(int len){
    int* ret=&pool[id];
    id+=len;
    re ret;
}
}

namespace Seg{
int* tr[20][N<<1];

void build(){
    for(int i=0;i<lg;i++){
        for(int j=0;j<n;j+=1<<i){
            tr[i][j]=Pool::get(1<<i);
            if(!i) co;
            int mid=j+(1<<(i-1))-1;
            int s=(1<<(i-1));
            fo(k,0,s-1){
                tr[i][j][k]=tr[i-1][j][k]+tr[i-1][j+s][k]+(a[mid^k]!=a[(mid+1)^k]);
                tr[i][j][k|s]=tr[i-1][j^s][k]+tr[i-1][(j+s)^s][k]+(a[mid^(k|s)]!=a[(mid+1)^(k|s)]);
            }
        }
    }
}
}

int ask(int r){//开区间
    int l=0,ret=0;
    ct=0;
    go(i,lg-1,0) if(r>>i&1){
        ++ct;
        bit[ct].v=i;
        bit[ct].l=l;
        bit[ct].r=l+(1<<i)-1;
        l+=1<<i;
    }
    int lst=0;
    fo(j,1,ct){
        int i=bit[j].v;
        int qwq=(bit[j].l^((X>>i<<i)));
        ret+=Seg::tr[i][qwq][X&((1<<i)-1)];
        ret+=a[bit[j].r^X]!=a[(bit[j].r+1)^X];
    }
    re ret;
}

signed main(){
    int oo=read();cin>>lg>>q;
    n=1<<lg;
    fo(i,0,n-1) a[i]=read();
    Seg::build();
    int lst=0;
    while(q--){
        int o=read();
        if(o==1){
            int x=read();if(oo) x^=lst;
            X^=x;
            co;
        }
        int l=read(),r=read();if(oo) l^=lst,r^=lst;
        if(l>r) swap(l,r);
        int ans=1+ask(r)-ask(l);
        cout<<ans<<'\n';
        if(oo) lst=ans;
    }
    return 0;
}
}
/*
-------------------------------------------------
*/










signed main(){re vectorwyx::main();}
```

---

## 作者：Cindy_Li (赞：5)

对于颜色段，可以用 $(cl,cr,cnt)$ 三元组维护区间信息，支持合并。

显然操作一有结合律，于是转化为给定 $(l,r,x)$，找出 $a_{l\oplus x},\dots,a_{r\oplus x}$，求颜色段。

异或问题容易想到 01trie，异或 $1$ 就是交换左右子树。注意到 $n=2^k$，直接建线段树就是 01trie 结构。

经过一定的手玩和观察，可以发现：对于一个长为 $len=2^j$ 的线段树节点，异或 $x\in [0,len-1]$ 时是内部顺序变，异或 $x\ge len$ 时会整体变到同层的另一个节点上。

于是对于每个节点只需维护 $len$ 个版本的信息。

到这里，一种写法是直接在线段树上维护 $len$ 个三元组，查询时再考虑是否交换左右区间等。

我写的是另外一种，用主席树直接维护 $n$ 种序列的形态，查询更加简单。

具体的，考虑新增 $x$ 的版本，注意到第一次交换左右儿子是在最高位，而下面的子树信息和 $x\oplus highbit(x)$ 是一样的，就不需要继续递归。

这样每个节点仍然只有 $len$ 个版本，每层的版本总数是 $n$，空间复杂度 $O(n\log n)$，时间复杂度 $O((n+m)\log n)$。

```c++
const int N=(1<<18)+5,M=N*19;
int a[N];
namespace seg{
    int rt[N];
    int ls[M],rs[M];
    struct data{
        int cl,cr,ct;
        inline data operator+(const data &b)const{
            return {cl,b.cr,ct+b.ct-(cr==b.cl)};
        }
    }info[M];
    int tot;
    inline void pushup(int x){info[x]=info[ls[x]]+info[rs[x]];}
    inline int build(int l,int r){
        int x=++tot;
        if(l==r) return info[x]={a[l],a[l],1},x;
        int mid=(l+r)>>1;
        ls[x]=build(l,mid);
        rs[x]=build(mid+1,r);
        return pushup(x),x;
    }
    inline void upd(int &x,int y,int l,int r,int v){
        x=++tot;
        int len=r-l+1;
        if(v&(len>>1)) ls[x]=rs[y],rs[x]=ls[y];
        else {
            int mid=(l+r)>>1;
            upd(ls[x],ls[y],l,mid,v);
            upd(rs[x],rs[y],mid+1,r,v);
        }
        return pushup(x);
    }
    inline data que(int x,int l,int r,int s,int t){
        if(l>=s && r<=t) return info[x];
        int mid=(l+r)>>1;
        if(s>mid) return que(rs[x],mid+1,r,s,t);
        if(t<=mid) return que(ls[x],l,mid,s,t);
        return que(ls[x],l,mid,s,t)+que(rs[x],mid+1,r,s,t);
    }
}
using namespace seg;
int T,n,m,lst;
inline int get(int x){
    return x^(T*lst);
}
int main(){
    read(T),read(n),read(m);n=1<<n;
    lst=0;
    rep(i,0,n-1) read(a[i]);
    rt[0]=build(0,n-1);
    rep(i,1,n-1) {
        int k=31-__builtin_clz(i);
        upd(rt[i],rt[i^(1<<k)],0,n-1,i);
    }
    int nwx=0;
    rep(i,1,m){
        int o;read(o);
        if(o==1){
            int x;read(x);x=get(x);
            nwx^=x;
        }else{
            int l,r,x;read(l),read(r);
            l=get(l),r=get(r);
            if(l>r) swap(l,r);
            printf("%d\n",lst=que(rt[nwx],0,n-1,l,r).ct);
        }
    }
    return 0;
}
```

---

## 作者：P_Bisector (赞：5)

场切。（我固执地认为 T4 比 T5 难）

首先考虑怎么维护颜色段数。我们可以写一个struct维护左断电颜色 `L`，右端点颜色 `M`，总颜色段数 `R` 并开一个struct。合并时直接总颜色段数相加，如果左边的右端点颜色与右边的左端点颜色相同则颜色段数减一。代码如下：
```cpp
struct stt{
	int L,R,M;
	void operator=(int a){
		M=1;
		L=R=a;
	}
}O; 
inline stt operator+(stt a,stt b){
	if(a.M==0)return b;
	return{a.L,b.R,a.M+b.M-(a.R==b.L)};
}
```
特别的，我们可以开一个状态 `O` 表示空的序列的状态。

然后这样写线段树可以轻松获得 30pts。接下来我们考虑如何处理操作一。

容易发现，如果我们把整个序列分成长度为 $2^t(t<k)$ 的块，且每次操作一的时候如果 $x$ 的后 $t$ 位（二进制位）都是 $0$，那么操作时只会改变块与块之间的相对位置。相应的，如果 $x$ 只有后 $t$ 位有非零位，那么只有块内的顺序会被打乱，而块与块之间的相对位置不变。除此以外，设第一次操作一 $x$ 为 $a_1$，第二次操作一 $x$ 为 $a_2$，那么几次操作之后就相当于进行了一次 $x$ 为 $a_1 \oplus a_2 \oplus ...$ 的操作一。

据此我们可以将序列分成 $2^{\lfloor \frac{k}{2}\rfloor}$ 块，存一个 $tag$ 记录所有的操作一的 $x$ 后 $t$ 位的异或和，并预处理每一个块在进行了不同的操作一后的状态（即前文所说的 `L`，`R`，`M`），然后开一个 $R$ 数组来记录各个块之间的相对位置。进行操作一时维护 $tag$ 和 $R$ 即可，询问时和普通分块差别不大。

时间复杂度 $O(n \sqrt{n})$（比标算慢多了）。因此注意卡常。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=500005;
struct stt{
	int L,R,M;
	void operator=(int a){
		M=1;
		L=R=a;
	}
}O,s[1000][1000]; 
inline stt operator+(stt a,stt b){
	if(a.M==0)return b;
	return{a.L,b.R,a.M+b.M-(a.R==b.L)};
}
int T,k,m,t,t2,B,B2,n,a[1000][1000],b[1000],R[1000],TAG,R2[1000];
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>T>>k>>m;
    t=k/2,t2=k-t;
    B=(1<<t),B2=(1<<t2);
    n=(1<<k);
    for(int i=0;i<B2;i++){
    	R[i]=i;//R的初始化
    	for(int j=0;j<B;j++){
    		cin>>a[i][j]; 
		}
		for(int k=0;k<B;k++){//块内预处理
			s[i][k]=O; 
			for(int j=0;j<B;j++){
				stt tmp;tmp=a[i][j^k];
				s[i][k]=s[i][k]+tmp;
			}
		}
	}
	int lst=0;
	for(int i=1;i<=m;i++){
		int op;
		cin>>op;
		if(op==1){
			int x;
			cin>>x;
			if(T)x^=lst;
			int xl=x>>t,xr=x-(xl<<t);
			TAG^=xr;
			for(int i=0;i<B2;i++){
				R2[i]=R[i^xl];
			}
			for(int i=0;i<B2;i++){
				R[i]=R2[i];
  			}
  			//对R的修改
		}else{
			int l,r;
			cin>>l>>r;
			if(T)l^=lst,r^=lst;
			if(l>r)swap(l,r);
			int Xl=l/B,Xr=r/B;
			stt ans=O;
			for(int i=l%B;i<B;i++){
				stt tmp;
				tmp=a[R[Xl]][i^TAG];
				ans=ans+tmp;
				if(i==r%B&&Xl==Xr){//注意l和r在一个块的情况。这里处理的比较丑陋
					goto ZHEN_CONTINUE;//真·continue
				}
			}
			for(int i=Xl+1;i<Xr;i++){
				ans=ans+s[R[i]][TAG];
			}
			for(int i=0;i<=r%B;i++){
				stt tmp;
				tmp=a[R[Xr]][i^TAG];
				ans=ans+tmp;
			}
			ZHEN_CONTINUE:;
			cout<<ans.M<<"\n";
			lst=ans.M;
		}
	}
}
```

---

## 作者：fengenrong (赞：4)

### 题解

首先，我们先考虑简单的情况，没有修改操作。

由题意得，一段区间颜色段个数可以转化为区间长度减去相邻同色个数，即区间 $[l,r]$ 的颜色段数为 $r-l+1- \sum^r_{i=l+1}[a_i=a_{i-1}]$。

考虑线段树，那么一段区间所作的贡献即为左右两段区间的贡献之和，如果左子树右端和右子树左端相等，则减一，否则不做贡献。

```cpp
void update(int rt){
    ans[rt]=ans[ls[rt]]+ans[rs[rt]]-(point[ls[rt]]r==point[rs[rt]].l);
    point[rt].l=point[ls[rt]].l,point[rt].r=point[rs[rt]].r;
}
```

接下来考虑修改操作，当异或到 $x$ 的某一位为 $1$ 时，我们就相当于将左右子树互换。

然后继续向下继续异或操作，由于异或具有交换律，我们只有在询问的时候考虑异或操作，修改直接 $O(1)$ 即可。

但是，在查询时，每次都修改、打标记，就超时了！

注意到，$x<n$，那么我们可以预处理，对于每一个答案提前求出来。

我们第 $i$ 个答案可以通过 $i-w$ 计算得出，其中 $w$ 为 $i$ 的最高位。举个例子：

当 $i$ 为 `01011` 时，我们让它减去它最高位 `01000` 得到 `00011`，我们通过 `00011` 的线段树去更新 `01011` 的线段树。

我们不可能开 $n$ 棵线段树，所以我们可以用可持久化线段树。

由于查询 $m$ 次，每次查询一棵线段树，所以查询为 $O(m \log n)$。再来看预处理，我们一开始建树是 $O(n)$ 的，接下来更新 $[1,n]$ 的答案，我们考虑每一个最高位 $i$，那么它在 $[1,n]$ 中会出现 $2^i$ 次，每次修改 $\frac{n}{2^{i+1}}$ 个点，所以修改为 $O(\sum_{i=0}^{k-1}2^i \times \frac{n}{2^{i+1}})$，即 $O(n \log n)$。综上，时间复杂度为 $O(n \log n+m\log n)$。

### Code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int T, k, q, n, a[300005], rt[300005], cnt, op, l, r, x, lastans, w;
struct SegTree {
    int ls[300005 << 5], rs[300005 << 5], ans[300005 << 5];
    struct node {
        int l, r;
    } point[300005 << 5];  //记录每个节点左右两端的节点
    void update(int rt) {
        ans[rt] = ans[ls[rt]] + ans[rs[rt]] - (point[ls[rt]].r == point[rs[rt]].l);
        point[rt].l = point[ls[rt]].l, point[rt].r = point[rs[rt]].r;
    }
    void build(int &rt, int l, int r) {
        if (!rt)
            rt = ++cnt;
        if (l == r)
            return ans[rt] = 1, point[rt] = { a[l], a[r] }, void();
        int mid = l + r >> 1;
        build(ls[rt], l, mid), build(rs[rt], mid + 1, r);
        update(rt);
    }
    void change(int &rt1, int rt2, int l, int r, int x) {
        rt1 = ++cnt, ls[rt1] = ls[rt2], rs[rt1] = rs[rt2], ans[rt1] = ans[rt2], point[rt1] = point[rt2];
        if (r - l + 1 == (1 << x))
            swap(ls[rt1], rs[rt1]);
        else {
            int mid = l + r >> 1;
            change(ls[rt1], ls[rt2], l, mid, x), change(rs[rt1], rs[rt2], mid + 1, r, x);
        }
        update(rt1);
    }
    int query(int rt, int l, int r, int L, int R) {
        if (l == L && r == R)
            return ans[rt];
        int mid = l + r >> 1;
        if (R <= mid)
            return query(ls[rt], l, mid, L, R);
        else if (mid + 1 <= L)
            return query(rs[rt], mid + 1, r, L, R);
        else
            return query(ls[rt], l, mid, L, mid) + query(rs[rt], mid + 1, r, mid + 1, R) -
                   (point[ls[rt]].r == point[rs[rt]].l);
    }
} tree;
signed main() {
    scanf("%lld%lld%lld", &T, &k, &q), n = (1 << k);
    for (int i = 0; i < n; i++) scanf("%lld", &a[i]);
    tree.build(rt[0], 0, n - 1);
    for (int i = 1, j = k; i < n; i++, j = k) {
        while (!((i >> j) & 1)) j--;                              //求最高位
        tree.change(rt[i], rt[(i ^ (1 << j))], 0, n - 1, j + 1);  //注意j+1
    }
    while (q--) {
        scanf("%lld", &op);
        if (op == 1)
            scanf("%lld", &x), x = (x ^ (T * lastans)), w = (w ^ x);
        else {
            scanf("%lld%lld", &l, &r), l = (l ^ (T * lastans)), r = (r ^ (T * lastans));
            if (l > r)
                swap(l, r);
            printf("%lld\n", lastans = tree.query(rt[w], 0, n - 1, l, r));
        }
    }
    return 0;
}
```

---

## 作者：Lyrella (赞：3)

# 前言

一道非常不错的题！

# 题解

先找题目性质，然后发现操作一可以合并，所以只用考虑如何快速做完操作一并得到操作二的答案。先考虑如何在动态序列上维护颜色段，我们可以维护满足 $col_{i-1}=col_{i}=col_{i+1}$ 的数量再用总数减去就是答案。对于区间的端点我们暴力判断就行因为不会超过 $O(\log n)$。那么操作一又如何处理呢？

考虑每次操作后有的区间会交换但是有的却**保持相对静止**，然后建议随便写几个数用纸和笔手摸一下操作。

![](https://cdn.luogu.com.cn/upload/image_hosting/zhs3e544.png)

你会发现我其实是把 $[0,1]$ 这个区间平移到了 $[6,7]$，其他可以类比。试想对于线段树上一段长度为 $len$ 的区间，我做操作一后出现的情况只会有 $len$ 种。设异或上 $sum$，若 $sum>len$ 其实就可以看成 $sum\bmod len$，因为把这些东西都放在二进制下你会发现他多出来的那些数位上的一都没有用，而 $sum$ 取零到 $len-1$ 时序列的变换方式又互不相同，所以有 $len$ 种情况。然后我其实可以直接把这些情况记下来。时间复杂度是 $\sum_{i=0}^{2^i\le len}\frac{len}{2^i}=2\times len$ 的，所以建树总复杂度还是 $O(n\log n)$ 的。

然后其实就直接在线段树上走就行了，对于查询到的区间，若当前操作的值小于等于就可以直接把答案取出来，否则就需要**平移**到同一层的某个点上，调用它的答案。对于平移操作我们又如何处理呢？

我们可以记录一个数组 $jump_{l,i}$ 代表序列上左端点是 $l$ 且线段树节点大小为 $2^i$ 的点是谁，然后跳的时候相当于二进制下**数位小于等于当前走到的点**就直接调用平移后的答案，大于等于的部分就异或上区间左端点直接跳，最后中点的答案就暴力合并即可。

（如果有点晕建议结合上面的图画一下）

# 代码：

```cpp
void bld(int x, int l, int r){
	int len = r - l, mid = l + r >> 1;
	jump[l][lg[len]] = x; f[x].rsz(len);
	if(l + 1 == r)return;
	bld(ls, l, mid), bld(rs, mid, r);
	for(int i = 0; i < len; ++i)
		if(i < (len >> 1))f[x][i] = f[ls][i] + f[rs][i] + (a[mid - 1 ^ i] == a[mid ^ i]);
		else f[x][i] = f[ls][i - (len >> 1)] + f[rs][i - (len >> 1)] + (a[mid - 1 ^ i] == a[mid ^ i]);
}
int qry(int x, int l, int r, int ql, int qr){
	if(ql <= l and r - 1 <= qr)return f[jump[l ^ (opt >> lg[r - l] << lg[r - l])][lg[r - l]]][opt % (1 << lg[r - l])];
	int mid = l + r >> 1, ansl(0), ansr(0); bool fl(false), fr(false);
	if(ql < mid)fl = true, ansl = qry(ls, l, mid, ql, qr);
	if(mid <= qr)fr = true, ansr = qry(rs, mid, r, ql, qr);
	return fl ? (fr ? (ansl + ansr + (a[mid ^ opt] == a[mid - 1 ^ opt])) : ansl) : ansr;
}
```

---

## 作者：Tachibana_Kimika (赞：2)

观察题目中操作的性质，不难发现可以对每次操作的 $x$ 按位考虑，位与位之间不会互相影响，且对某一位操作两次会还原。所以我们可以只用一个数 $x$ 来保存整个区间的信息。

更深一步发掘性质，我们发现对于某一位修改，等同于把若干个连续，长为 $2^k$ 的子段进行交换（1 和 2 交换，3 和 4 交换，以此类推）。可以从异或的角度进行理解。

这个时候我们可以得到一个 $O(n^2)$ 的暴力，具体来说，预处理每种不同的 $x$ 会把区间变成什么样子，然后预处理前缀里有多少颜色段，查询的时候就可以 $O(1)$ 回答询问。

我们又得到一种 $O(n^2)$ 的暴力，具体来说，我们用一颗线段树，每次暴力 swap 交换左右儿子，然后上层重构。

好熟悉啊，有两种 $O(n^2)$ 的暴力，这个时候我们是不是该考虑根号分治了。具体地应该算是分块，我们对于每一块暴力预处理出所有小于 $\sqrt n$ 的操作（也就是只考虑前 $\frac{k}{2}$ 位），然后对于大于 $\sqrt n$ 的操作，我们暴力 swap，就可以做到单次询问 $O(\sqrt n)$，也就是总复杂度 $O(n\sqrt n)$，或者 $O(2^{\frac{3}{2}k})$。

实际跑的时候有一点卡常，洛谷上挺好过的，梦熊机子就不一定了（但是我还是过了）。

```cpp
#include<bits/stdc++.h>
#define int unsigned int
using namespace std;
const int N=262244,M=522,B=522;
int _abs(int x){if(x<0) return -x; return x;}

char *p1,*p2,buf[100000];
#define nc() (p1==p2 && (p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
int read(){
    int x=0,f=1;
    char ch=nc();
    while(ch<48||ch>57) ch=nc();
    while(ch>=48&&ch<=57) x=x*10+ch-48,ch=nc();
   	return x*f;
}
void write(int x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
    return;
}//用了一个奇技淫巧快读

int a[N];
//int tmp[M][N];
int tmp[N];
int pos[N],st[M],ed[M];
int lft[M][B],rgt[M][B],cnt[M][B];
int siz;

int tb(int p,int cover){
	return p^cover;
}//这个的意思是，当前序列被cover 操作，p这个位置实际上代表的位置是
//为什么需要这个函数？
//因为我们没法把空间开到n根号n（会炸，我试过）
//所以不能存下n根号n种不同的序列
//只能做一个变换来得到被修改过后的序列

int cb(int bp,int cover){
	return pos[st[bp]^cover];
}
//这个跟上面大差不差
//只是改成当前块操作后会变成哪个块了而已
//实现方法就是在块内随便找一个点，做上面的变换
//然后再返回这个点所在块

//这个貌似也可以直接预处理，因为空间是根号平方的。

int query(int l,int r,int cover){
	if(l>r) swap(l,r);
	int bl=pos[l],br=pos[r];
	int down=cover&(siz-1);//down是操作的前k/2位
	if(bl==br){//同一块内暴力
		int ans=1;
		for(int i=l+1;i<=r;i++){
			if(a[tb(i-1,cover)]!=a[tb(i,cover)]) ans++;
		}//注意所有的下标全部都要变换
		
		return ans;
	}
	
	int ans=1;
	for(int i=l+1;i<=ed[bl];i++) if(a[tb(i-1,cover)]^a[tb(i,cover)]) ans++;//散块暴力
	int lst=a[tb(ed[bl],cover)]; 
	for(int i=bl+1;i<br;i++){//整块操作
		int nowb=cb(i,cover);
		if(!(lft[nowb][down]^lst)) ans--;//块与块合并
  //这边用了一些奇技淫巧，就是a!=b可以写成a^b，不知道会不会快
		ans+=cnt[nowb][down]; lst=rgt[nowb][down];
	}
	if(a[tb(st[br],cover)]^lst) ans++;//块与散块合并
	for(int i=st[br]+1;i<=r;i++) if(a[tb(i-1,cover)]^a[tb(i,cover)]) ans++;//散块暴力
	return ans;
}

inline void fake_main(){
	int t,k,m; t=read(); k=read(); m=read();
	int n=(1<<k);
	for(int i=0;i<n;i++) a[i]=read();
	siz=(1<<(k/2));
	
	for(int i=0;i<n;i++) pos[i]=i/siz+1;
	for(int i=1;i<=pos[n-1];i++) st[i]=siz*(i-1),ed[i]=siz*i-1;
	//上面都是分块
	for(int i=0;i<siz;i++){//暴力预处理小于根号的询问
		for(int j=0;j<n;j++) tmp[j]=a[j];
		
		for(int j=0;j<n;j++) if(j<(j^i)) swap(tmp[j],tmp[j^i]);//暴力swap
		
		//cout<<"case "<<i<<"\n";
		//for(int j=0;j<n;j++) cout<<tmp[j]<<" "; cout<<"\n";
		
		for(int j=1;j<=pos[n-1];j++){
			cnt[j][i]=1;
			for(int r=st[j]+1;r<=ed[j];r++){
				if(tmp[r-1]^tmp[r]) cnt[j][i]++;
			}
			lft[j][i]=tmp[st[j]];
			rgt[j][i]=tmp[ed[j]];
      //预处理块内颜色段个数，左边颜色和右边颜色，都是老生常谈了。
		}
	}	
	
	//for(int i=0;i<n;i++) cout<<tmp[1][i]<<" "; cout<<"\n";
	
	///cout<<lft[2][1]<<" "<<rgt[2][1]<<"\n";
	
	int lst=0,cover=0;
	for(int i=1;i<=m;i++){
		int op; op=read();
		if(op==1){
			int x; x=read();
			if(t) x=x^lst;
			cover^=x;//我们直接用一个 cover 变量记录当前序列，不需要显式的修改
		}else{
			int l,r; l=read(); r=read();
			if(t){
				l=l^lst; r=r^lst;
			}
			lst=query(l,r,cover);
			write(lst); puts("");
		}
	}
	
}


signed main(){
	//ios::sync_with_stdio(false);
	//cin.tie(0); cout.tie(0);
	int t; t=1;
	while(t--) fake_main();
}

```

---

## 作者：ni_ju_ge (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P10856)

人傻常数大，喜提最劣解。
## 思路
注意到第一个操作具有结合律，因此可以将问题转化为给定 $x$，令 $a'_i=a_{i\oplus x}$，求 $a'_{l\sim r}$ 中的不同颜色段数。

先考虑 $x=0$（Subtask 2）时该怎么做。先建一颗线段树，现在 $pos$ 的左右儿子上的答案已经计算完，考虑 $pos$ 的答案怎么算。发现可以直接将两个儿子的答案相加，若中点两边的点颜色相同，将答案减一即可。可以直接保存区间两端的 $a_i$ 方便查询。

接下来要进一步解决 $x\not= 0$ 的情况。注意到由于 $n=2^k$ 所以此时的线段树相当于一棵 01trie。到第 $i$ 层时往左儿子/右儿子走就相当于查询编号在二进制下从高到低第 $i$ 位为 $0/1$ 的点。那么若 $x$ 的这一位为 $1$，就相当于换为另一个儿子继续查询。因此对于区间长为 $2^l$ 的节点，对它有效的 $x$ 只有 $2^l$ 个（因为只有 $x$ 的后 $l$ 位的取值会影响查询的顺序），所以可以将这 $2^l$ 种取值的答案在预处理时求出来，查询的时候若该节点恰好被包含直接返回对应 $x$ 的答案即可（若不恰好包含，则依据上文决定是否交换左右儿子，然后继续递归查询）。

线段树共有 $\log n$ 层，每一层节点遍历的取值个数之和均为 $n$，那么预处理的复杂度为 $O(n\log n)$；查询的复杂度为 $O(m\log n)$，总时间复杂度为 $O(n\log n+m\log n)$。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+5;
struct seq {
	int l,r,dif;//l,r 是左右端点颜色，dif 是不同个数
};
struct node {//线段树
	int l,r;
	vector<seq> res;
} tr[N*4];
int t,k,m,n;
int l,r,x,lst,xx,opt,a[N],px;
void build(int pos,int l,int r) {
	tr[pos].l=l,tr[pos].r=r;
	if(l==r) {
		tr[pos].res.push_back({a[l],a[r],1});
		return;
	}
	int mid=(l+r)/2;
	build(pos*2,l,mid);build(pos*2+1,mid+1,r);
	for(int i=0;i<=r-l;i++) {//预处理对应每种 x 的答案
		if(i<(r-l+1)/2) {
			int l1=tr[pos*2].res[i].l,r1=tr[pos*2].res[i].r;
			int l2=tr[pos*2+1].res[i].l,r2=tr[pos*2+1].res[i].r;
			int sdif=tr[pos*2].res[i].dif+tr[pos*2+1].res[i].dif;
			if(r1==l2) sdif--;
			tr[pos].res.push_back({l1,r2,sdif});
		} else {
			int p=(i^((r-l+1)>>1));
			int l1=tr[pos*2+1].res[p].l,r1=tr[pos*2+1].res[p].r;
			int l2=tr[pos*2].res[p].l,r2=tr[pos*2].res[p].r;
			int sdif=tr[pos*2+1].res[p].dif+tr[pos*2].res[p].dif;
			if(r1==l2) sdif--;
			tr[pos].res.push_back({l1,r2,sdif});
		}
	} 
}
seq sch(int pos,int l,int r,int w,int px) {
	if(tr[pos].l>r||tr[pos].r<l) return {-1,-1,0};
	if(tr[pos].l>=l&&tr[pos].r<=r) {
		if(tr[pos].l==tr[pos].r) return tr[pos].res[0];
		else return tr[pos].res[px&((1<<(w+1))-1)];
	}
	int mid=(tr[pos].l+tr[pos].r)/2,ll,rr;
	if((px>>w)&1) {//交换左右儿子
		tr[pos*2+1].l=tr[pos].l,tr[pos*2+1].r=mid;
		tr[pos*2].l=mid+1,tr[pos*2].r=tr[pos].r;//交换左右儿子的区间
		int sdif=0;
		seq ls=sch(pos*2+1,l,r,w-1,px);//原本应该查询 pos*2，由于交换了，所以查询 pos*2+1，下同
		seq rs=sch(pos*2,l,r,w-1,px);
		sdif=ls.dif+rs.dif;//直接将答案相加
		if(ls.r==rs.l&&ls.r!=-1) sdif--;//相同则将答案减一
		tr[pos*2].l=tr[pos].l,tr[pos*2].r=mid;
		tr[pos*2+1].l=mid+1,tr[pos*2+1].r=tr[pos].r;
		ll=ls.l,rr=rs.r;
		if(rr==-1) rr=ls.r;
		if(ll==-1) ll=rs.l;//注意若只有一边在查询区间内，返回的左右端点应该都属于这一边
		return {ll,rr,sdif};
	} else {
		tr[pos*2].l=tr[pos].l,tr[pos*2].r=mid;
		tr[pos*2+1].l=mid+1,tr[pos*2+1].r=tr[pos].r;
		int sdif=0;
		seq ls=sch(pos*2,l,r,w-1,px);
		seq rs=sch(pos*2+1,l,r,w-1,px);
		sdif=ls.dif+rs.dif;
		if(ls.r==rs.l&&ls.r!=-1) sdif--;
		ll=ls.l,rr=rs.r;
		if(rr==-1) rr=ls.r;
		if(ll==-1) ll=rs.l;
		return {ll,rr,sdif};
	}
}
int main() {
	cin>>t>>k>>m;
	n=(1<<k);
	for(int i=0;i<n;i++) cin>>a[i];
	build(1,0,n-1);
	for(int i=1;i<=m;i++) {
		cin>>opt;
		if(opt==1) {
			cin>>xx;
			x=(x^xx^(t*lst));
		} else {
			cin>>l>>r;
			l^=(t*lst);r^=(t*lst);
			if(l>r) swap(l,r);
            lst=sch(1,l,r,k-1,x).dif;
			cout<<lst<<endl;
		}
	}
}
```

---

## 作者：R_shuffle (赞：0)

考虑暴力做法，对于每种 $x$ 维护一棵线段树，表示 $a_{i\oplus x}$ 这个序列，然后就可以做了。

考虑优化，显然在暴力做法中，有很多节点是相同的，考虑合并这些相同的节点。具体的，比如 $x=1$ 和 $x=0$ 两种，只需要用动态开点线段树，把线段树最底层的左右儿子交换一下即可，除了最底层的，上面的直接新建节点。

实现的时候需要注意，每次选择最高的二进制位改变，这样能保证节点个数不会太多。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define __MY_TEST__ 0
inline int read()
{
    int re=0,f=1;
    char ch=getchar();
    while(!isdigit(ch)){if(ch=='-') f=-1; ch=getchar();}
    while( isdigit(ch)) re=(re<<3)+(re<<1)+(ch^48),ch=getchar();
    return re*f;
}
const int N=(1<<18)+5,M=N<<5;
int k,m,a[N],rt[N],sum[M],lc[M],rc[M],ls[M],rs[M],tot;
void push_up(int num)
{
    sum[num]=sum[ls[num]]+sum[rs[num]];
    if(rc[ls[num]]==lc[rs[num]]) sum[num]--;
    lc[num]=lc[ls[num]],rc[num]=rc[rs[num]];
}
void build(int &num,int l,int r)
{
    if(!num) num=++tot;
    if(l==r)
    {
        sum[num]=1;
        lc[num]=rc[num]=a[l];
        return ;
    }
    int mid=(l+r)>>1;
    build(ls[num],l,mid);
    build(rs[num],mid+1,r);
    push_up(num);
}
void rever(int lst,int &num,int l,int r,int x)
{
    if(!num) num=++tot;
    if(r-l+1==x*2) ls[num]=rs[lst],rs[num]=ls[lst];
    else
    {
        int mid=(l+r)>>1;
        rever(ls[lst],ls[num],l,mid,x);
        rever(rs[lst],rs[num],mid+1,r,x);
    }
    push_up(num);
}
array<int,3>query(int num,int l,int r,int pl,int pr)
{
    if(l>=pl&&r<=pr) return {sum[num],lc[num],rc[num]};
    int mid=(l+r)>>1;
    if(pr<=mid) return query(ls[num],l,mid,pl,pr);
    if(pl>mid) return query(rs[num],mid+1,r,pl,pr);
    array<int,3>lv=query(ls[num],l,mid,pl,pr),rv=query(rs[num],mid+1,r,pl,pr);
    int sum=lv[0]+rv[0];
    if(lv[2]==rv[1]) sum--;
    return {sum,lv[1],rv[2]};
}
signed main(){
#if __MY_TEST__
    freopen(".in","r",stdin);
    freopen(".out","w",stdout);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    int tp=read();
    k=read(),m=read();
    for(int i=0;i<(1<<k);i++) a[i]=read();
    build(rt[0],0,(1<<k)-1);
    for(int i=1;i<(1<<k);i++)
    {
        int lowbit=1<<(31-__builtin_clz(i));
        rever(rt[i^lowbit],rt[i],0,(1<<k)-1,lowbit);
    }
    int lans=0,nw=0;
    for(int i=1;i<=m;i++)
    {
        int opt=read();
        if(opt==1)
        {
            nw^=read()^(tp*lans);
        }
        else
        {
            int l=read()^(tp*lans),r=read()^(tp*lans);
            if(l>r) swap(l,r);
            cout<<(lans=query(rt[nw],0,(1<<k)-1,l,r)[0])<<'\n';
        }
    }
}
```

---

## 作者：Robin_kool (赞：0)

询问了区间不同颜色段。

不同颜色段=总长度-相邻颜色相等的数量。

考虑维护第三者。

$n$ 是 $2^k$，这启发我们从朴素线段树的根本原理上做文章。对于一个节点维护的信息，显然是连续的，而且只有 $x$ 的某一段 $01$ 位是可以改变它的值的。

打表后发现，对于某一个节点，异或 $x$ 后总会变成同一深度的另一个节点。

然后注意到异或可以先运算 $x$，询问的时候暴力查找即可。合并只需要对于每一二进制位，判断它的左右区间的颜色是否相等。

复杂度 $O(n\log n)$。略有常数。

直接开空间会爆炸，建议使用 vector。

---

## 作者：Iratis (赞：0)

书接上文，比 D 简单的题来了，*1900。

首先，由异或的可加性，可得操作一是具有可加性的，我们可以把迄今为止所有操作一的 $ x_i $ 异或起来，得到当前所求的 $ x $。

继续考虑 $ x $ 的具体含义，如果我们将原序列建成线段树的形式，自底向上标层 $ 0,1,\cdots,k $。那么若 $ x $ 的第 $ i $ 位为 $ 1 $，所做的操作即为将第 $ i $ 层的每个节点与他的兄弟交换。

再考虑询问，既然已经建出线段树了，故考虑将区间拆成线段树上的若干个节点，如果能够求出每个点内的颜色段，再辅以该节点两段的颜色，那么就能够求出答案。

观察其中任意的一个节点 $ v $，其有表示区间 $ [l_v,r_v] $。发现对于这个节点来说，其中包含的下标的二进制表示必定存在一段长度为 $ h=k-dep_v $ 的公共前缀，去除这段前缀后剩余下标完整包含了 $ [0,2^{dep_v}) $。故将 $ x $ 的前 $ h $ 位先异或进来，那么可得这必然对应到了一个同层节点 $ v' $，所做的询问变为只保留 $ x $ 的后 $ dep_v=dep_{v'} $ 位，记 $ x' $。发现有 $ x'\in [0,2^{dep_{v'}}) $，而整个 $ v' $ 都要被查询，这提示我们 sub3 即为正解。

接下来考虑 sub3，即查询全局。如果能够提前维护出全局异或每一个数的答案 $ f_x $，那么每次 $ O(1) $ 查表即可。仍然建出线段树，重定义 $ f_{v,x} $ 表示节点 $ v $ 异或 $ x $ 的答案，那么 $ f_{v,x} $ 就可以通过 $ f_{ls,?} $ 和 $ f_{rs,?} $ 合并得到，这一步是容易的，留给读者思考。分析一下，$ f $ 的空间开销为  $ \displaystyle\sum_{d=1}^k\frac{2^k}{2^d}2^d=2^kk $，能够支持。

至此，已经解决，时间复杂度 $ O(n\log^2 n) $。

---

## 作者：xxxxxzy (赞：0)

感觉还是比较显的。

容易发现发现，一个区间异或上一个数和某个这个区间的平移区间异或上另一个数相同。

比如 $[1,2,3,4]$ 异或 $2$ 得到 $[3,0,1,6]$，与 $[5,6,7,8]$ 异或 $6$ 相等。

然后就可以考虑线段树维护，每个点维护 $f_{u,i}$ 代表 $u$ 所在的区间异或上 $i$ 的答案。

由于上面说的性质，所以每一层的答案都是长度级别的，大于长度的可以在另一块找到答案。

答案合并是 $O(1)$ 的，信息合并总共是 $O(n \log n)$。

总时空复杂度 $O(n\log n)$。

---

