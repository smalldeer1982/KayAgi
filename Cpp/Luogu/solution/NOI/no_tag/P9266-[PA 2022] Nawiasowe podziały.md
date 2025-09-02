# [PA 2022] Nawiasowe podziały

## 题目描述

**题目译自 [PA 2022](https://sio2.mimuw.edu.pl/c/pa-2022-1/dashboard/) Runda 5 [Nawiasowe podziały](https://sio2.mimuw.edu.pl/c/pa-2022-1/p/naw/)**

我确信你是知道括号序列的，但是以防万一，并且作为回顾，让我们回忆一下它的定义：

- `()` 是一个合法的括号序列。
- 如果 $S$ 是一个合法的括号序列，那么 `(S)` 也是一个合法的括号序列。
- 如果 $S_1$ 和 $S_2$ 都是合法的括号序列，那么 $S_1S_2$ 也是一个合法的括号序列。
- 不符合上述规则的括号序列都不是合法的括号序列。

给出一个长度为 $n$ 且仅由字符 `(` 和 `)` 组成的字符串，以及一个数字 $k$，这个字符串不一定是合法的括号序列。你的任务是把它分成 $k$ 个非空段（每个字符必须恰好属于一段内），使得每段中是合法括号序列的子串个数之和最小。

## 说明/提示

对于 $100\%$ 的数据，满足：

$1\le k\le n\le 10 ^ 5$。

## 样例 #1

### 输入

```
15 2
())(()())()(())
```

### 输出

```
6
```

## 样例 #2

### 输入

```
15 3
())(()())()(())
```

### 输出

```
3
```

# 题解

## 作者：Fucious_Yin (赞：9)

这是 wqs 加广义笛卡尔树加斜率优化的 $O(n \log n)$ 题解，尾附 **带注释代码**。

~~欢迎收看，花子早早挂飞赶来上课，群友和我艰难保平差点迟到~~

先给链接：[洛谷P9266 Nawiasowe podziały](https://www.luogu.com.cn/problem/P9266)
和 [loj3919 Nawiasowe podziały](https://loj.ac/p/3919)。

## 题意

定义一个括号序列的代价为，其是合法括号序列的子串的个数。

给定一个长为 $n$ 的括号序列，要求将其分成 $k$ 段，使得总代价最小。

$k \le n \le 1 \times 10^5$

## 题解

好像有很多什么诸如莫队或者 CDQ 的奇异一车 $\log$ 的做法，但花子手动把题加强到 $n \le 1 \times 10^6$，那么我们还是考虑单 $\log$ 做法。

括号序列先~~套路~~变成 +1-1 的序列，令前缀和为 $S_i$，看成一条折线。我们先考虑给一个区间 $[L + 1, R]$ 怎么去求代价。往折线上考虑，再回到序列上的形式化表示就是：

* $\sum_{L \le l < r \le R}{[S_l = S_r = \min_{i \in [l,r]}{S_i}]}$.

显然要求内部括号匹配且折线的最低点不爆。

因为这里有 $\min$，所以我们可以建出广义笛卡尔，同样的最小值同时提出来得到一棵多叉树，新建的方点代表管辖的区间，方点下挂圆点表示最小值位置，方点下方点代表子区间，区间之间顺序不变。这样就把序列问题转化到了树上。~~这个玩意是我用单调栈手搓出来的~~

考虑一个方点 $u$ 对一个分割出的区间 $[L + 1,R]$ 的贡献，令 $v_i$ 为下挂的第 $i$ 个圆点，就是 $\binom{\sum{[v_i \in [L,R]]}}{2}$。这里只用算在这个最小值上的贡献。

直观理解~~猜~~到答案关于 $k$ 是凸的，具体证明可以考察上面的贡献函数。最外层显然套一个 wqs，再把分成 $k$ 段转化为切 $k - 1$ 刀，那么我们只要考虑有切刀代价时的最优 $dp$ 即可，考虑在这个笛卡尔树上 $dp$。注意，这是一个双关键字的 dp，即要求在代价最小的前提下，切刀数最少，方便 wqs 判断。

还是从贡献函数上考虑，发现在 $u$ 这个点的贡献只与其下挂圆点的划分方式有关，也就是说，我们不关心他的一个儿子的子区间内究竟切了多少刀、切在哪里，只关心是否切刀。这样就好设计 dp 了。

设 $f_u$ 为 $u$ 子树内的**至少切一刀**最小代价。这样显然也无法转移，再设 $g_i$ 为 $u$ 的前 $i$ 个儿子的子树，第 $i$ 棵内一定切一刀的最小代价，这样每个 $g_i$ 加上后缀的代价贡献给 $f_u$。朴素的转移是枚举上一个吃刀的子树，计算之间的 $u$ 下挂圆点的代价，并加上中间子树内不切的代价，前者直接在这一层前缀和算，后者可以预处理再前缀和。

$sum_u$ 为 $u$ 子树内不切刀的代价，可以一遍 dfs 预处理。$prs_i$ 为当前节点 $u$ 的前 $i$ 个儿子子树不吃刀的代价和，$pre_i$ 为下挂圆点个数前缀合，$sons_u$ 为 $u$ 的儿子个数。则转移为：

* $g_i = \min_{j}(g_j + prs_i - prs_{j} + \binom{pre_i-pre_j}{2})$
* $f_u = \min_{i}(g_i + prs_{sons_u} - prs_i)$

直接做是 $O(n^2)$ 的，考虑优化。观察 $g$ 的转移式，发现同时关于 $i$ 和 $j$ 的项只有 $\binom{pre_i-pre_j}{2}$，令 $s_{i,j} = pre_i - pre_j$，也就是 $\frac{1}{2} \times (s_{i,j}^2 - s_{i,j})$，这是一个关于 $s$ 的极其优美的递增凸函数。同时又因为随着转移点 $j$ 的增大，$pre_j$ 也不降，那么每个转移点起始的斜率就不增，这就可以做我们经典的斜率优化，维护一个如上凸的函数图像，直接转移即可。建议手推推式子更清晰，这就是斜率优化的事情了，两个转移点的比较是可以 $O(1)$ 数学算的。

还有诸多细节，比如整棵树也可以不切，在根的时候得取个 $\min$；可以切在子树的缝隙里，儿子个数翻倍处理；还有 $pre_i$ 可能相同，那维护的图像中同样斜率的只能保留一条；还有由于是双关键字，哪怕几条线交在同一点也不能随便 pop，还要第二关键字比出内部偏序关系。

非常牛的一题啊。

[我的代码喵](https://loj.ac/s/2150939)

---

## 作者：CaoXian (赞：6)

模拟赛 T1 放了这道题的加强版，打了一上午的三 $\log$ 做法结果发现 $n$ 被毒瘤搬题人开到了 $5 \times 10^{5}$，直接气吐血。

---

这种题看着就很有 dp 的感觉，但是状态太多开不下。发现是“强制划分为 $k$ 段”这个条件很烦人，于是用 wqs 二分把这一维优化掉。

具体地，二分一个 $\Delta$，表示每分一段就会多出来的代价，在 dp 的过程中忽略强制选 $k$ 段的限制，直接统计最小代价并记录划分的段数。如果段数比 $k$ 小则将 $\Delta$ 调小，否则调大。

考虑 `check` 怎么写，先把 dp 的状态转移方程写出来：

$$
dp_{i} = \min\limits_{0 \leqslant j < i}\left\{dp_{j} + w(j + 1, i) + \Delta\right\}
$$

其中 $w(l, r)$ 表示字符串的子串 $S[l..r]$ 中有多少个合法括号子串。

从直觉上来看，上面这个式子是满足决策单调性的，因为在 $r$ 逐渐增大的过程中，最优决策的 $l$ 肯定也是逐渐增大或不变才能保证代价最小，如果某个时刻 $l$ 倒退了的话那么在前面的决策中 $l$ 也应该倒退才对。

或者说可以证明一下 $w(l, r + 1) + w(l - 1, r) \leqslant w(l - 1, r + 1) + w(l, r)$。这个东西我只会一种比较感性的证明方式：发现 $S[l..r]$ 这里的子串贡献是一定的，所以只用考虑 $l - 1$ 和 $r + 1$ 处的贡献。

而每个在 $[l, r]$ 中可以和 $l - 1$ 产生贡献的位置会在 $w(l - 1, r)$ 和 $w(l - 1, r + 1)$ 中产生贡献，并且它们的贡献相同。$r + 1$ 同理。

但是在 $w(l - 1, r + 1)$ 中 $l - 1$ 和 $r + 1$ 还可能产生贡献，所以 $w(l - 1, r) + w(l, r + 1) \leqslant w(l - 1, r + 1) + w(l, r)$。

有了这个我们就可以利用决策单调性优化 dp 了，但是因为决策的过程中有 dp 本身，所以要使用 CDQ 分治来规避掉未知的 dp 值无法转移的情况。

现在你已经打出了 wqs 二分，短短几行的 CDQ 分治以及决策单调性优化 dp 的函数，但是你发现 $w(l, r)$ 无法快速计算，这让人很头疼。

如果你做过 [CF868F](https://www.luogu.com.cn/problem/CF868F) 那么你应该能想到可以利用一个类莫队的方法来计算 $w(l, r)$ 的值，并且它的时间复杂度是均摊单次 $\mathcal{O}(1)$ 的。

但这也是本题的三 $\log$ 做法最难的部分。（也许不是，我在赛后听到学长在谈论什么染色的方法，但是我不会。）

假设我们已经维护好一段子串的贡献了，现在要在这个子串右端加入一个右括号 `)`。

下面为了方便并且直观，使用了许多不同的颜色来代表不同的括号。

![](https://cdn.luogu.com.cn/upload/image_hosting/qm34fmvc.png)

上面的红色右括号 $\color{red}\texttt{)}$ 表示新加入的右括号，蓝色左括号 $\color{blue}\texttt{(}$ 表示在原串中与 $\color{red}\texttt{)}$ 相匹配的括号。

（注意，因为这个字符串是不变的，所以每个括号的匹配情况也是不变的，只是有些时候匹配的括号不在当前区间内而已。并且两个匹配的括号之间的子串一定是合法子串，否则它们无法匹配）

如果 $\color{blue}\texttt{(}$ 不在当前区间 $[l, r]$ 内那肯定无法造成贡献，所以只考虑 $\color{blue}\texttt{(}$ 在区间 $[l, r]$ 内的情况。


首先 $\color{blue}\texttt{(}$ 和 $\color{red}\texttt{)}$ 一定可以产生 $1$ 的贡献。并且在 $\color{blue}\texttt{(}\color{black}\cdots\color{red}\texttt{)}$ 前“拼接”一个合法子串又能产生大小为 $1$ 的贡献，“拼接”之后还可以再“拼接”继续产生贡献。可以一直重复下去。

所以只要知道 $\color{blue}\texttt{(}$ 前有多少个**独立且相邻**的合法子串，**独立**是指这些子串没有包含关系，**相邻**是指将这些合法子串按顺序排列后，它们之间没有多余括号，在上图已经画出来的部分就有两个**独立且相邻**的合法子串。

直接扫一遍显然是不优的，可以构造 `()()()()()` 这样的数据卡掉，于是考虑将贡献“提前计算”，储存到 $\color{red}\texttt{)}$ 的位置，当加入 $\color{red}\texttt{)}$ 时把这个贡献加上。把这个“提前计算”的贡献称为 $sum$。

![](https://cdn.luogu.com.cn/upload/image_hosting/qkm6oi2h.png)

这里的 $\color{lime}\texttt{(}\color{black}\cdots\color{orange}\texttt{)}$ 是与 $\color{blue}\texttt{(}\color{black}\cdots\color{red}\texttt{)}$ 直接相邻的一个合法子串，考虑利用 $\color{orange}\texttt{)}$ 的 $sum$ 推出 $\color{red}\texttt{)}$。

注意到 $\color{lime}\texttt{(}\color{black}\cdots\color{orange}\texttt{)}$ 和 $\color{blue}\texttt{(}\color{black}\cdots\color{red}\texttt{)}$ 也是**独立且相邻**的，而在上述定义中所有和 $\color{lime}\texttt{(}\color{black}\cdots\color{orange}\texttt{)}$ **独立且相邻**的合法子串再加上 $\color{lime}\texttt{(}\color{black}\cdots\color{orange}\texttt{)}$ 本身，它们也是和 $\color{blue}\texttt{(}\color{black}\cdots\color{red}\texttt{)}$ **独立且相邻**的，所以 $\color{red}\texttt{)}$ 处的 $sum$ 值为 $\color{orange}\texttt{)}$ 处的 $sum + 1$。

左括号的情况类似，如果无法理解你就把上面的图旋转 180 度看就行（

但是，我们还漏掉了一种情况：我们在 $\color{lime}\texttt{(}\color{black}\cdots\color{orange}\texttt{)}$ 右端“拼接”上了 $\color{blue}\texttt{(}\color{black}\cdots\color{red}\texttt{)}$ 后 $\color{lime}\texttt{(}$ 处的 $sum$ 值并没有更新（它理应是 $2$ 但此时仍然是 $1$）。

暴力更新是显然不可以的，`()()()()()` 这样的数据同样能卡掉，每加入一个 `()` 都会将前面所有括号的 $sum$ 重新计算一遍。

这时我们要利用类莫队计算方法的特性：它只会在两边加入和删除。换句话说，我们只需要维护一个**极长独立且相邻**的合法子串段的左右端点处的 $sum$ 即可。

于是额外维护一个位置 $ps$，表示当前括号所处的**极长独立且相邻**的合法子串段的左/右端点。

（这里只需要维护一个 $ps$ 即可，因为维护右端点对 $\texttt{)}$ 的加入和删除操作没有意义，左端点对 $\texttt{(}$ 的加入和删除没有意义，而且这么做还可以大幅度减小码量。）

那么当我们在 $\color{lime}\texttt{(}\color{black}\cdots\color{orange}\texttt{)}$ 右端“拼接”$\color{blue}\texttt{(}\color{black}\cdots\color{red}\texttt{)}$ 后，只需要将 $\color{orange}\texttt{)}$ 处的 $ps$ 指向的位置的 $sum$ 值更改即可。注意这里还要同时维护 $\color{blue}\texttt{(}$，$\color{red}\texttt{)}$ 和 $\color{orange}\texttt{)}$ 的 $ps$ 指向的位置，这三个地方的 $ps$ 值。显然 $\color{blue}\texttt{(}$ 应指向 $\color{red}\texttt{)}$，$\color{red}\texttt{)}$ 和 $\color{orange}\texttt{)}$ 处的 $ps$ 指向的位置互相指向。

注意如果在 $\color{blue}\texttt{(}\color{black}\cdots\color{red}\texttt{)}$ 前面没有**独立且相邻**的合法子串，那么直接将 $\color{blue}\texttt{(}$ 和 $\color{red}\texttt{)}$ 的 $sum$ 设为 $1$ 即可，意义显然。

有了加入操作的经验，不难想到把“删掉一个括号造成的贡献”也提前计算储存起来。

事实上，可以直接用 $sum$ 表示这个贡献，因为一个括号不可能同时处于会被删除的状态和会被加入的状态。或者说，将 $sum$ 定义为一个括号改变自身状态后会造成的贡献。

把上面那张图搬下来一下。

![](https://cdn.luogu.com.cn/upload/image_hosting/qkm6oi2h.png)

假设待删除的括号是 $\color{red}\texttt{)}$，其余括号的意义不变。

删除括号后的贡献也用同样的方法考虑，一次删除减少的合法子串数为“和 $\color{blue}\texttt{(}\color{black}\cdots\color{red}\texttt{)}$ **独立且相邻**的子串数”，同样地，我们需要减去 $\color{red}\texttt{)}$ 处的 $sum$ 大小的贡献。

继续考虑将 $\color{red}\texttt{)}$ 删除后会引起哪些位置的 $sum$ 的改变，它们应该是 $\color{blue}\texttt{(}$，$\color{red}\texttt{)}$，$\color{lime}\texttt{(}$，$\color{orange}\texttt{)}$ 和 $\color{red}\texttt{)}$ 处的 $ps$ 指向的位置，它们应分别改变为 $0$，$0$，$1$，$\color{red}\texttt{)}$ 处的 $sum - 1$ 和 $\color{red}\texttt{)}$ 处的 $ps$ 指向的位置的 $sum - 1$，这里的意义不用过多阐述。

你可能会有疑问：像 $\color{red}\texttt{)}$ 这样的位置都被删除掉了，为什么还要维护？因为 $\color{red}\texttt{)}$ 被删除后，它的状态就由“可以被删除”变为“可以被加入”，此时它的 $sum$ 就表示了它被加入后会产生的贡献，所以需要及时维护。

左括号仍然同理，你只需要将上面的图旋转 180 度看就可以了（

你可能会想到，我还没有说明在右侧加入左括号的情况和在左侧加入右括号的情况。这两种情况显然不会造成任何贡献，直接忽略即可。

因为左括号和右括号的情况是对称的（从“旋转 180 度”也可以看出来），所以只要打出来左括号的情况那么右括号也迎刃而解了。

贴一份代码，其中 `check()` 函数是 wqs 二分时的检查函数；`CDQ(l, r)` 函数是 CDQ 分治（作用在上文中已说明，需注意我这里脑抽打了个左闭右开的区间）；`solve(dl, dr, l, r)` 是决策单调性优化 dp 的函数，`dl` 和 `dr` 是待决策的区间，`l` 和 `r` 是可以转移的区间；`calc` 是类莫队计算 $w(l, r)$ 的函数；`add` 和 `del` 就是加入和删除括号时计算贡献的函数。

时间复杂度 $\mathcal{O}(n \log^{2} n \log V)$ 跑了两分半喜提最劣解！其中 $V$ 表示 wqs 二分时的值域。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n, k, l, r, delta, ans, L, R, res, p[100005], dp[100005], s[100005], sum[100005], ps[100005];
string str;
stack<int> stk;
void add(int pos) {
	if(str[pos] == '(') {
		if(p[pos] <= R) {
			if(str[p[pos] + 1] == '(' && p[p[pos] + 1] <= R) {
				sum[pos] = sum[p[pos] + 1] + 1;
				ps[pos] = ps[p[pos] + 1];
				ps[ps[pos]] = pos;
				++sum[ps[pos]];
			}
			else sum[pos] = 1, ps[pos] = p[pos];
			++sum[p[pos]];
			ps[p[pos]] = pos;
			res += sum[pos];
		}
	}
	if(str[pos] == ')') {
		if(p[pos] >= L) {
			if(str[p[pos] - 1] == ')' && p[p[pos] - 1] >= L) {
				sum[pos] = sum[p[pos] - 1] + 1;
				ps[pos] = ps[p[pos] - 1];
				++sum[ps[pos]];
				ps[ps[pos]] = pos;
			}
			else sum[pos] = 1, ps[pos] = p[pos];
			++sum[p[pos]];
			ps[p[pos]] = pos;
			res += sum[pos];
		}
	}
}
void del(int pos) {
	if(str[pos] == '(') {
		if(p[pos] <= R) {
			res -= sum[pos];
			if(str[p[pos] + 1] == '(' && p[p[pos] + 1] <= R) {
				--sum[ps[pos]];
				sum[p[pos] + 1] = sum[pos] - 1;
				sum[p[p[pos] + 1]] = 1;
				ps[p[p[pos] + 1]] = p[pos] + 1;
				ps[ps[pos]] = p[pos] + 1;
				ps[p[pos] + 1] = ps[pos];
				ps[pos] = 0;
			}
			else sum[pos] = 0, ps[pos] = 0;
			--sum[p[pos]];
			ps[p[pos]] = 0;
		}
		sum[pos] = 0;
	}
	if(str[pos] == ')') {
		if(p[pos] >= L) {
			res -= sum[pos];
			if(str[p[pos] - 1] == ')' && p[p[pos] - 1] >= L) {
				--sum[ps[pos]];
				sum[p[pos] - 1] = sum[pos] - 1;
				sum[p[p[pos] - 1]] = 1;
				ps[p[p[pos] - 1]] = p[pos] - 1;
				ps[ps[pos]] = p[pos] - 1;
				ps[p[pos] - 1] = ps[pos];
				ps[pos] = 0;
			}
			else sum[pos] = 0, ps[pos] = 0;
			--sum[p[pos]];
			ps[p[pos]] = 0;
		}
		sum[pos] = 0;
	}
}
ll calc(int l, int r) {
	while(L > l) add(--L);
	while(R < r) add(++R);
	while(L < l) del(L++);
	while(R > r) del(R--);
	return res;
}
void solve(int dl, int dr, int l, int r) {
	if(dl > dr || l > r) return;
	int mid = (dl + dr) >> 1, pos = l;
	ll mn = dp[l] + calc(l + 1, mid) + delta, tmp;
	for(int i = l; i <= r; ++i) {
		tmp = dp[i] + calc(i + 1, mid) + delta;
		if(tmp <= mn || (tmp == mn && s[i] > s[pos])) {
			pos = i, mn = tmp;
		}
	}
	if(mn < dp[mid] || (dp[mid] == mn && s[pos] + 1 > s[mid])) {
		dp[mid] = mn;
		s[mid] = s[pos] + 1;
	}
	solve(dl, mid - 1, l, pos);
	solve(mid + 1, dr, pos, r);
}
void CDQ(int l, int r) {
	if(l + 1 >= r) return;
	int mid = (l + r) >> 1;
	CDQ(l, mid);
	solve(mid, r - 1, l, mid - 1);
	CDQ(mid, r);
}
bool check() {
	fill(dp + 1, dp + 1 + n, 0x7f7f7f7f7f7f7f7f);
	dp[0] = 0;
	CDQ(0, n + 1);
	return s[n] >= k;
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> n >> k >> str;
	str = '$' + str;
	for(int i = 1; i <= n; ++i) {
		if(str[i] == '(') p[i] = n + 1;
		else p[i] = 0;
	}
	for(int i = 1; i <= n; ++i) {
		if(str[i] == '(') stk.push(i);
		else if(!stk.empty()) {
			p[i] = stk.top();
			p[stk.top()] = i;
			stk.pop();
		}
	}
	L = 1, R = 0, res = 0;
	l = -10000000000ll, r = 10000000000ll;
	while(l <= r) delta = (l + r) >> 1, check() ? (ans = dp[n] - delta * k, l = delta + 1) : (r = delta - 1);
	cout << ans;
	cerr << '\n' << clock() << '\n';
	return 0;
}
```

---

话说我这份题解是不是对患有色盲症的同学有点不太友好qwq

---

## 作者：lingying (赞：5)

这道题的加强版（数据范围开到 $10^6$）被放到了我们模拟赛 T1？我的评价是非常毒瘤。

# 题意

给定一个长度为 $N$ 的括号字符串 $S$。

定义一个函数 $c(l,r)$ 表示所有子串在 $[l,r]$ 区间中为合法括号串的数量。

现在你要将这个字符串分成 $K$ 段，每一段的代价为 $c(l,r)$，要求总代价最小。

$1\le K\le N\le 10^5$。

# 解法

## 做法 $1$

考虑列出朴素 dp。

$f_{i,j}$ 表示前 $i$ 个数分成 $j$ 段的最小代价。转移有：

$$

f_{i,j}=\min\limits_{0\le k<i}(f_{k,j-1}+c(k+1,i))

$$

暴力转移时间复杂度为 $O(N^2 K)$，不能接受。

注意到 $c(l,r)$ 满足四边形不等式 $c(l,r)+c(l-1,r+1)\ge c(l,r+1)+c(l-1,r)$。于是我们可以预处理下来 $c$ 函数然后 $O(N^2)$ 完成 dp。

还是不能接受。

我们发现现在的转移已是均摊 $O(1)$，再想优化得从状态入手。我们注意到对于任意的 $1\le i\le n$，我们在坐标轴上标出 $(1,f_{i,1}),(2,f_{i,2}),...,(m,f_{i,m})$，不难发现这是个凸包，于是我们可以用 wqs 二分去掉第二维。没有了分成 $m$ 段的限制，我们现在的 dp 方程为：

$$

f_i=\min\limits_{0\le j<i}(f_j+c(j+1,i)+v)

$$

其中 $v$ 为二分的值。

由于满足四边形不等式，所以其具有决策单调性，我们可以用 cdq 套分治维护决策单调性。

时间复杂度为 $O(N\log^3 N)$。

据说可以用二分栈做到 $O(N\log ^2N)$。

## 做法 $2$

我们重新考虑合法括号序列的本质。如果我们视左括号为 $1$，右括号为 $-1$。其前缀和序列为 $A$。我们称一个子串 $S[l,...,r]$ 是合法括号序列当且仅当：

* $S_{l-1}=S_r=\min\limits_{i=l-1}^r S_i$

由于有 $\min$，我们可以对原串建出广义笛卡尔树。每一个节点 $u$ 对应着一个管辖区间 $[l,r]$，一个集合 $s$ 对应着这个区间最小值的所有位置，以及它的儿子，也就是最小值的所有位置划分出来的子区间。对于一个管辖 $[l,r]$ 的节点，它对询问 $c(L+1,R)$ 的贡献可以写成 $5$ 种：

* $l\notin [L,R],r\notin [L,R]$，则贡献为 $0$。

* $l\in [L,R],r\in [L,R]$，则贡献为 $\dbinom{|s|}{2}$。

* $L\in [l,r],R\notin [l,r]$，则贡献为 $\dbinom{\sum_{i\in s}[i\ge L]}{2}$。

* $L\notin [l,r],R\in[l,r]$，则贡献为 $\dbinom{\sum_{i\in s}[i\le R]}{2}$。

* $L\in [l,r],R\in [l,r]$，则贡献为 $\dbinom{\sum_{i\in s}[L\le i\le R]}{2}$。

注意到上面的贡献方式，我们还是先 wqs 二分，接着我们把划分为 $K$ 个区间这一条件换为切了 $K-1$ 刀，然后在我们建出来的广义笛卡尔树上动态规划。由于已经 wqs 二分，转移时不需要关心切了具体多少刀，我们设状态 $g_u$ 表示在 $u$ 的子树至少切了一刀的贡献。假设我们切了 $k$ 刀，位置分别在 $l\le i_1< i_2<...<i_k\le r$ 处，则贡献显然为 $cost(l,i_1,3)+\sum\limits_{j=1}^{k-1}cost(i_j,i_{j+1},\{1,2,3,4,5\})+cost(i_k,r,4)$。其中 $cost(l,r,S)$ 表示区间 $[l,r]$ 的第 $x\in S$ 种贡献。当我们在 $u$ 合并两个区间的时候，则只需要考虑第 $5$ 种贡献。具体地，当前 $u$ 的区间为 $[L,R]$，你要合并 $[R+1,r]$ 进来，假设 $[L,R]$ 区间的最后一刀的位置是 $i$，$[R+1,r]$ 区间的第一刀的位置是 $j$，显然你只计算了 $cost(i,R,4)$ 和 $cost(R+1,j,3)$，你需要把第 $5$ 种贡献加进来，当然别忘了加 wqs 二分的 $mid$。当然，我们发现只有 $g_u$ 是无法完成的，因为有些子树是不会切的，所以我们设 $f_{u,i}$ 表示在 $u$ 这个子树中，$v_i$ 这个子树内必定切了一刀，前 $i$ 棵子树的总贡献。 转移可以得到：

$$
f_{i}=\min\limits_{j=0}^{i-1}(0,f_j + g_{v_j}+sum_{i-1}-sum_j+\binom{pre_i-pre_j}{2})
$$

为了方便这里省略了第一维 $u$。其中 $v_i$ 表示 $u$ 的第 $i$ 个儿子，$sum_i$ 表示前 $i$ 个儿子的第 $2$ 类贡献之和，$pre_i$ 表示前 $i$ 个儿子有多少个是集合元素，也就是有多少个儿子在其他节点的集合 $s$ 中。

这样子转移配合着 wqs 二分时间复杂度是 $O(n^2 \log n)$。但是我们发现转移式子可以使用斜率优化，所以总时间复杂度可以作到 $O(n\log n)$。



---

## 作者：ღꦿ࿐ (赞：4)

模拟赛考到这个题，数据范围加个 $0$ 卡掉三只 $\log$ 和大常数两只 $\log$，很可恶，没有写完两只 $\log$。

令 $\text{cost}(l,r)$ 表示 $[l,r]$ 的代价，即一个区间内合法的括号子串个数，显然一个合法括号串不会包含任何不合法的括号，所以用不合法括号将串分成若干段，形成括号树森林，一个合法的括号串一定是一个点的某一段完整的儿子组成的，然后查询时即查询了如下这样一个区域内的括号构成的合法括号串数：

![](https://cdn.luogu.com.cn/upload/image_hosting/x5d3n430.png)



维护 $cr_x$ 表示这个括号到根的这条链上所有右侧的兄弟及其子树内的合法的括号串数，$cl_x$，表示这个括号到根的这条链上所有左侧的兄弟及其子树内的合法的括号串数，$ctot_x$ 表示 $x$ 子树内合法的括号串数，这三者均可以提前在括号树上 dfs 求出。

查询 $[u,lca),[v,lca)$ 这两条链上的 $vr,vl$ 的和，然后再算上两者在 $lca$ 处中间夹住的兄弟及其 $ctot$ 就行了。区间的开或闭需要手动处理细节较多。


于是我们现在可以 $O(\log n)$ 计算一个区间的代价了。

---

回到划分问题上，肯定得先对划分 dp，令 $f_{i,K}$ 表示 $[1,i]$ 分 $K$ 段的最小代价，$f_{i,K}=\min(f_{j,K-1}+\text{cost}(j+1,i))$，经典分 $K$ 段，考虑这个代价和区间长度的关系，两个包含的区间加上同样的部分，被包含的区间增加的代价感觉是更少的，猜测其具有决策单调性和凸完全单调性，打表可以验证其代价满足四边形不等式，证明如下：

首先对于一个括号串 $S$，在左侧任意添加任意括号都不会改变 $S$ 中合法的括号串的情况，右侧同理。

将四边形不等式变形成 $\text{cost}(b,d)-\text{cost}(b,c) \leq \text{cost}(a,d)-\text{cost}(a,c)$，称左侧为 $\Delta_b$，右侧为 $\Delta_a$，两者都包含了左右端点都在 $(c,d]$ 之间的合法括号串，而对于右端点在 $(c,d]$ 之间的括号串，$\Delta_b$ 限制了左端点在 $[b,c]$ 中而 $\Delta_a$ 的限制是其超集 $[a,c]$，所以 $\Delta_a$ 中此类串的出现次数一定不少于 $\Delta_b$，所以四边形不等式成立。


在具有决策单调性和凸完全单调性后剩下的就是套路了。

我们得到 $f_{i,K}$ 关于 $K$ 下凸，考虑 wqs 二分，每分一段产生惩罚代价 $\Delta$，二分 $\Delta$ 去掉第一维度，现在转移为 $f_i = \min (f_j+\text{cost}(j+1,i)+\Delta)$。

接下来对这个具有决策单调性的 dp 转移维护队列，每次在队尾二分可以弹掉的区间，每次 dp 需要查询 $O(n\log n)$ 次 $\text{cost}(l,r)$。

目前时间复杂度 $O(n\log^3 n)$，可以通过本题，有如下继续优化的方式。

我们的三只 $\text{log}$ 分别来源于 wqs 二分，决策单调性（二分队列），查询区间代价，其实后面两只 $\log$ 都可以去掉，查询区间代价可以使用 $O(1)$ 的 LCA 和 $k$ 级祖先（长链剖分）找到 LCA 处对应的儿子并查询。决策单调性部分可以使用 SMAWK 算法做到线性，最终时间复杂度 $O(n\log n)$。

---

## 作者：Leasier (赞：4)

首先不难想到如下 $O(n \log^3 n)$ 做法：

- 感性理解答案关于 $k$ 是凸的，考虑 wqs 二分一个 $mid$。
- 于是有 dp：$dp_i = \displaystyle\min_{j = 1}^i (dp_{j - 1} + w(j, i) - mid)$。
- 不难发现 $w(l, r)$ 满足四边形不等式，则 $dp_i$ 有决策单调性。
- cdq 分治套整体二分，莫队式移动指针时对前缀和相同的位置双指针维护即可。

以上做法可以通过二分栈优化到 $O(n \log^2 n)$，但这并不能从根本上优化时间复杂度。

还是考虑 wqs 二分，但我们尝试换一种方式计算贡献。

考虑合法括号串的本质：

- 设 $sum_i$ 表示 $s[1, i]$ 中，`(` 的个数减去 `)` 的个数。
- $[l, r]$ 合法当且仅当 $sum_{l - 1} = sum_r = \displaystyle\min_{i = l - 1}^r sum_i$。

考虑建出 $sum_i$ 的笛卡尔树，一个点 $p$ 包含若干 $i \in [l_p, r_p], sum_i = p$（设这些 $i$ 的集合为 $S$）和若干儿子 $son_p$，当前层的合法括号串即为 $x, y \in S, x < y, (x, y]$。

考虑将划分为 $k$ 段转化为切 $k - 1$ 刀，设 $f_i$ 表示在点 $i$ 所示子树内切至少一刀的最小值。

设 $i$ 的第 $j$ 个 $S$ 中位置或儿子为 $pos_j$，$g_j$ 表示目前最后一刀切在 $pos_j$ 内，$pos_{[1, j]}$ 总贡献的最小值。

转移不难写出，且可以发现转移式可斜率优化。

时间复杂度为 $O(n \log n)$。记得特判划分为 $1$ 段即不切的情况。

代码：
```cpp
#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

typedef struct Line_tag {
	int k;
	pair<ll, int> pr;
	
	Line_tag(){}
	
	Line_tag(int k_, pair<ll, int> pr_){
		k = k_;
		pr = pr_;
	}
	
	inline pair<ll, int> calc(ll x){
		return make_pair(k * x + pr.first, pr.second);
	}
} Line;

inline bool check(Line a, Line b, Line c){
	return (b.pr.first - a.pr.first) * (c.k - b.k) >= (c.pr.first - b.pr.first) * (b.k - a.k);
}

typedef struct {
	int head;
	int tail;
	Line q[100007];
	
	inline void init(){
		head = 1;
		tail = 0;
	}
	
	inline int size(){
		return tail - head + 1;
	}
	
	inline void insert(Line line){
		while (size() >= 1 && ((q[tail].k == line.k && q[tail].pr >= line.pr) || (size() >= 2 && check(line, q[tail], q[tail - 1])))) tail--;
		q[++tail] = line;
	}
	
	inline pair<ll, int> query(ll x){
		if (head > tail) return make_pair(0x7fffffffffffffffll, 0);
		while (size() >= 2 && q[head].calc(x) >= q[head + 1].calc(x)) head++;
		return q[head].calc(x);
	}
} ConvexHull;

typedef struct {
	int cnt;
	vector<int> v;
} Node;

int id = 0;
ConvexHull conv;
int sum[100007], _log2[100007], st[17][100007], cnt[100007];
ll complete[100007], inside[100007];
char s[100007];
Node tree[100007];
pair<ll, int> pr1[100007], pr2[100007];
vector<int> v[200007];

pair<ll, int> operator +(const pair<ll, int> a, const pair<ll, int> b){
	return make_pair(a.first + b.first, a.second + b.second);
}

void operator +=(pair<ll, int> &a, const pair<ll, int> b){
	a = a + b;
}

inline void init(int n){
	int ni = n + 1, m;
	for (register int i = 2; i <= ni; i++){
		_log2[i] = _log2[i / 2] + 1;
	}
	m = _log2[ni];
	for (register int i = 0; i <= n; i++){
		st[0][i] = sum[i];
	}
	for (register int i = 1; i <= m; i++){
		int id = i - 1, t1 = n - (1 << i) + 1, t2 = 1 << id;
		for (register int j = 0; j <= t1; j++){
			st[i][j] = min(st[id][j], st[id][j + t2]);
		}
	}
}

inline int get_min(int l, int r){
	int t = _log2[r - l + 1];
	return min(st[t][l], st[t][r - (1 << t) + 1]);
}

int build(int l, int r, int n){
	int min_val = get_min(l, r), lst = l, ans = ++id;
	for (register vector<int>::iterator i = lower_bound(v[min_val + n].begin(), v[min_val + n].end(), l); i != v[min_val + n].end() && *i <= r; i++){
		if (lst <= *i - 1) tree[ans].v.push_back(build(lst, *i - 1, n));
		tree[ans].cnt++;
		tree[ans].v.push_back(-*i);
		lst = *i + 1;
	}
	if (lst <= r) tree[ans].v.push_back(build(lst, r, n));
	return ans;
}

inline ll comb_2(int n){
	return (ll)n * (n - 1) / 2;
}

inline pair<ll, int> check(ll k){
	pair<ll, int> ans(0x7fffffffffffffffll, 0);
	for (register int i = id; i >= 1; i--){
		int size = tree[i].v.size();
		pr1[i] = make_pair(0x7fffffffffffffffll, 0);
		for (register int j = 0; j < size; j++){
			if (tree[i].v[j] > 0){
				cnt[j] = 0;
				inside[j] = complete[tree[i].v[j]];
			} else {
				cnt[j] = 1;
				inside[j] = 0;
			}
			if (j > 0){
				cnt[j] += cnt[j - 1];
				inside[j] += inside[j - 1];
			}
		}
		conv.init();
		for (register int j = 0; j < size; j++){
			pair<ll, int> temp = conv.query(cnt[j] * 2 - 1);
			pr2[j] = min(make_pair(j > 0 ? comb_2(cnt[j]) : 0, 0), make_pair(temp.first / 2 + comb_2(cnt[j]), temp.second));
			if (tree[i].v[j] > 0){
				pr2[j] += pr1[tree[i].v[j]];
			} else {
				pr2[j].second++;
				pr2[j].first -= k;
			}
			if (j > 0) pr2[j].first += inside[j - 1];
			pr1[i] = min(pr1[i], make_pair(pr2[j].first + (inside[size - 1] - inside[j]) + comb_2(tree[i].cnt - cnt[j]), pr2[j].second));
			conv.insert(Line(-cnt[j], make_pair((pr2[j].first - inside[j]) * 2 + (ll)cnt[j] * cnt[j], pr2[j].second)));
		}
	}
	return min(pr1[1], make_pair(complete[1], 0));
}

int main(){
	int n, k;
	ll l, r = 0, ans;
	cin >> n >> k;
	cin >> &s[1];
	k--;
	for (register int i = 1; i <= n; i++){
		sum[i] = sum[i - 1] + (s[i] == '(' ? 1 : -1);
	}
	init(n);
	for (register int i = 0; i <= n; i++){
		v[sum[i] + n].push_back(i);
	}
	build(0, n, n);
	for (register int i = id; i >= 1; i--){
		complete[i] = comb_2(tree[i].cnt);
		for (register int j : tree[i].v){
			if (j > 0) complete[i] += complete[j];
		}
	}
	l = -complete[1];
	while (l <= r){
		ll mid = (l + r) >> 1;
		pair<ll, int> pr = check(mid);
		if (pr.second <= k){
			l = mid + 1;
			ans = pr.first + mid * k;
		} else {
			r = mid - 1;
		}
	}
	cout << ans;
	return 0;
}
```

---

## 作者：LJ07 (赞：3)

关键在于怎样计算子串合法括号序列的个数。令 $s_r=\sum_{i=1}^{r}(-1)^{[\texttt{第 i 个为左括号}]}$ 

一个括号序列 $[l,r]$ 合法：
1. $s_r=s_l$
1. $\min_{i=l+1}^{r-1}s_i \ge s_l$

你发现这玩意是什么，他是一个广义笛卡尔树的形式！！！然后你建出小根堆类的广义笛卡尔树。考虑在每层一定是类似于 ```最小值0 区间1 最小值1 区间2 .. 区间n 最小n```。那么每对最小值对合法括号序列就会贡献 $1$。

那么这个时候就可以设计出在广义笛卡尔树上的 dp 了。

---

## 作者：tzl_Dedicatus545 (赞：1)

![](https://qoj.ac/images/sticker/jiehun.png)

三只 $\log$，三只 $\log$，跑的快，跑的快。

首先有个显然的 dp 是说，$f_{r,k}$ 意思是到了 $r$ 你把它分成了 $k$ 段，转移是：

$$
f_{i,k}=\min(f_{j-1,k}+w(j,i))
$$

$w(l,r)$ 的意思是：$[l,r]$ 能分成几个连续合法子串。

然后这个东西显然是满足四边形不等式的。

> 如果转移函数 $w$ 满足四边形不等式，则 $f$ 是凸的。

所以其实所有的那种分成 $k$ 段的题你全可以 WQS 二分（

但是这个转移是在线的，所以你要外面搞个 CDQ 分治。

决策单调性转移的时候，可以用类似莫队的方法，判断合不合法就直接把括号序列匹配栈 Hash 一下就行了。

总复杂度三只 $\log$，但跑的飞快（

来点，易错点！

1. 搞清楚你的决策单调性分治的时候初始值域到底是啥
2. WQS 二分应当在同样情况下尽量分最多的段
3. 不一定段数非得 $=k$ 才行，大于 $k$ 你也照样弄，注意最后仍然减掉 $\text{cost}\times k$。
4. Hash 的时候你要对下标 Hash（不会真有人写错吧）

---

## 作者：MarsCheng (赞：0)

wqs 二分和决策单调性优化 dp 的方法上面题解讲的很清楚了，这里给出一个码量小、易理解的类莫队 $O(1)$ 的 $w(l,r)$ 计算方法。

首先显然对于每一个子串，一个括号如果配对了，那它配对的是哪一个括号是固定的，可以预处理出来。

然后我们考虑对括号进行染色，具体的，“相邻”的括号染同一种颜色，否则染不同的。就比如说 ```()(()())``` 这一个串，可以染色成 ```[][()()]```（用不同的括号代表不同颜色）

然后考虑用莫队维护区间中有多少个配对的某种颜色的括号，如果区间中有 $cnt_i$ 对配对的颜色为 $i$ 的括号，显然答案为 $\sum_{i=1}^c\frac{cnt_i(cnt_i+1)}{2}$，其中 $c$ 表示颜色个数，这是容易维护的。

下面给出预处理和莫队的代码。

预处理：
```cpp
// s[]：原括号串
// mh[]：匹配括号的位置
// c[]：颜色
for (int i = 1; i <= n; ++i) {
    if (s[i] == '(')
        mh[i] = n + 1;
    else {
        int p = i - 1;
        while (s[p] == ')')
            p = mh[p] - 1;
        if (p >= 1) {
            mh[i] = p, mh[p] = i;
            if (p > 1 && c[p - 1])
                c[i] = c[p - 1];
            else
                c[i] = ++ccnt;
            c[p] = c[i];
        } else
            mh[i] = 0;
    }
}
```
莫队：
```cpp
struct P {
    int l, r, cnt[N];
    long long ans;
    P() : l(1), r(0), ans(0) {
        memset(cnt, 0, sizeof(cnt));
    }
    long long query(int ql, int qr) {
        while (r < qr) {
            ++r;
            if (s[r] == ')' && l <= mh[r])
                ++cnt[c[r]], ans += cnt[c[r]];
        }
        while (ql < l) {
            --l;
            if (s[l] == '(' && mh[l] <= r)
                ++cnt[c[l]], ans += cnt[c[l]];
        }
        while (qr < r) {
            if (s[r] == ')' && l <= mh[r])
                ans -= cnt[c[r]], --cnt[c[r]];
            --r;
        }
        while (l < ql) {
            if (s[l] == '(' && mh[l] <= r)
                ans -= cnt[c[l]], --cnt[c[l]];
            ++l;
        }
        return ans;
    }
};
```

---

