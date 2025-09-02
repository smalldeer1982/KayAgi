# Nobody is needed

## 题目描述

Oleg 收到了一份长度为 $n$ 的排列 $a$ 作为生日礼物。

Oleg 的朋友 Nechipor 向 Oleg 提出了 $q$ 个问题，每个问题由两个数字 $l$ 和 $r$ 表示，Oleg 需要回答 Nechipor 的每个问题，对于每个问题，Oleg 需要说出满足以下条件的所有下标集合 $(t_1, t_2, \ldots, t_k)$（任意长度 $k \ge 1$）的数量：

- 对于每个 $i$，$1 \le i \le k$，都有 $l \le t_i \le r$。
- 对于每个 $i$，$1 \le i \le k-1$，都有 $t_i < t_{i+1}$。
- 对于每个 $i$，$1 \le i \le k-1$，都有 $a_{t_{i+1}}$ 能被 $a_{t_i}$ 整除。

请帮助 Oleg 回答所有 Nechipor 的问题。

## 说明/提示

第一组输入数据中所有符合条件的数组有：（$1$）、（$2$）、（$3$）、（$4$）、（$5$）、（$6$）、（$7$）、（$8$）、（$1, 3$）、（$1, 6$）、（$1, 7$）、（$1, 6, 7$）、（$2, 3$）、（$2, 4$）、（$2, 5$）、（$2, 6$）、（$2, 7$）、（$2, 8$）、（$2, 6, 7$）、（$6, 7$）。

第四组输入数据中所有符合条件的数组有：（$1$）、（$2$）、（$3$）、（$4$）、（$5$）、（$6$）、（$7$）、（$8$）、（$1, 2$）、（$1, 3$）、（$1, 4$）、（$1, 5$）、（$1, 6$）、（$1, 7$）、（$1, 8$）、（$1, 2, 4$）、（$1, 2, 6$）、（$1, 2, 8$）、（$1, 2, 4, 8$）、（$1, 3, 6$）、（$1, 4, 8$）、（$2, 4$）、（$2, 6$）、（$2, 8$）、（$2, 4, 8$）、（$3, 6$）、（$4, 8$）。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4
8 8
2 1 6 3 5 4 8 7
1 8
2 8
1 7
1 6
1 3
5 8
4 4
2 3
1 1
1
1 1
3 3
3 2 1
1 2
1 3
2 3
8 1
1 2 3 4 5 6 7 8
1 8```

### 输出

```
20 15 18 12 5 5 1 3
1
2 3 2
27```

# 题解

## 作者：xhhhh36 (赞：8)

[传送门](https://www.luogu.com.cn/problem/CF1946F)

好题！~~我调了一下午~~。注意维护区间和不能用线段树，常数过大会超时，只能用树状数组。记得多测要清空。

首先可以[证明](https://www.cnblogs.com/qscqesze/p/4317860.html)在长度为 $n$ 的全排列中只有 $n\log n$ 个子区间 $[a_l,a_r]$ 满足 $a_l\mid a_r$。

设 $f_i$ 为以 $a_i$ 为区间右端点的满足条件的区间个数。然后我们就可以对询问做离线，开一个 vector 来存每个左端点为 $l$ 时每个询问 $r$ 的值和询问的编号，由后向前枚举询问的左端点 $l$，每次从 $a_{l+1}$ 向 $a_{l}$ 扩展，然后计算 $a_{l}$ 作为区间的左端点对 $f$ 数组产生的影响。

那么询问 $[l,r]$ 的答案为 $\sum_{i=l}^r f_i$。用树状数组维护 $f$ 数组的区间和即可，每到达一个 $l$ 都将对应 vector 中的所有询问 $r$ 的答案查出来并记录下来，最后在正序输出即可。
### 如何计算 $x$ 作为区间的左端点带来的贡献？
因为 $x$ 要作为左端点对答案产生贡献，那么右端点只能是 $2\times x,3\times x\dots k\times x$ 这些数中小于等于 $n$ 并且位于 $x$ 所在位置的右边的数。

此时贡献又分两种，一种是当 $x\mid y$ 时，$x$ 对 $f_y$ 直接造成的贡献，另一种是当 $x\mid y$ 并且 $y\mid z$ 时，$x$ 对 $f_z$ 间接造成的贡献。因为 $z$ 也是 $x$ 的倍数，所以贡献只有这两种。

对贡献的计算可以使用 dp 来解决。设 $dp_i$ 为数值 $i$ 要增加的贡献，初始值为 $dp_x\gets 1$。枚举 $x$ 满足条件的倍数 $y$ 和 $y$ 满足条件的倍数 $z$，让 $dp_z\gets dp_x+dp_y$。

最后将 $dp_i$ 对应的数值 $i$ 的 $f_i$ 在维护的树状数组上实现 $f_i\gets f_i+dp_i$ 即可。不要忘了清空 $dp$ 数组。
# AC code
```cpp
#include <bits/stdc++.h>
#define int long long
#define lowbit(i) i&(-i)
using namespace std;
int T,n,q,dp[1000005],ans[1000005],tmp[1000005],a[1000005];
int t[1000005];
void add(int x,int c)
{
	while (x<=n)
	{
		t[x]+=c;
		x+=lowbit(x);
	}
}
int get_sum(int x)
{
	int sum=0;
	while (x>0)
	{
		sum+=t[x];
		x-=lowbit(x);
	}
	return sum;
}
int query(int l,int r)
{
	return get_sum(r)-get_sum(l-1);
}
void work()
{
	scanf("%d%d",&n,&q);
	vector<int> r[n+1];
	vector<int> no[n+1];
	for (int i=1;i<=n;i++)
	{
		scanf("%d",a+i);
		tmp[a[i]]=i;
	}
	for (int i=1;i<=q;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		r[x].push_back(y);
		no[x].push_back(i);
	}
	for (int i=n;i>=1;i--)
	{
		int x=a[i];dp[x]=1;
		for (int y=x;y<=n;y+=x)
		{
			if (tmp[y]<tmp[x]) continue;
			for (int z=y*2;z<=n;z+=y)
			{
				if (tmp[z]<tmp[y]) continue;
				dp[z]+=dp[y];
			}
		}
		for (int j=x;j<=n;j+=x)
		{
			add(tmp[j],dp[j]);
			dp[j]=0;
		}
		for (int j=0;j<r[i].size();j++)
		{
			ans[no[i][j]]+=query(i,r[i][j]);
		}
	}
	for (int i=1;i<=q;i++)
	{
		cout<<ans[i]<<" ";
	}
	cout<<"\n";
	for (int i=1;i<=q;i++)
	{
		ans[i]=0;
	}
	for (int i=1;i<=n;i++)
	{
		t[i]=0;
	}
}
signed main()
{
	cin>>T;
	while (T--)
	{
		work();
	}
	return 0;
}
```

---

## 作者：Eraine (赞：7)

编号：CF1946F

tag：动态规划，数据结构优化动态规划

难度：*2500

一眼丁真，鉴定为，歪果仁不会 DP。

很容易发现符合条件的连边都是从左往右，所以将所有符合条件的边建出来是一个 DAG。问方案总数容易想到 DP。

设 $f_{i,j}(i\le j)$ 为以 $i$ 为起点，$j$ 为终点的方案总数。由于此时所有的边都是从左指向右，固有如下转移：

$$f_{i,j}=\begin{cases}
   \sum_{i\lt k\le j,a_i\mid a_k}f_{k,j} &\text{if } i\neq j \\
   1 &\text{if } i=j
\end{cases}$$

很容易想到的一个做法就是暴力 dp。这里状态总数为 $\Theta(n^2)$，转移 $\Theta(n)$。总时间复杂度为 $\Theta(n^3)$。

$n\le 10^6$。明显过不了。考虑优化。容易发现，对于绝大部分的三元组 $(i,k,j)$ 都不满足条件 $a_i\mid a_k,a_k\mid a_j$。我们希望类似搜索剪枝减去大量无用的三元组。

考虑枚举 $a_j$ 的所有的因数 $a_k$，$a_i$ 同理，这时这个三层循环的时间复杂度为 $\Theta(n \log^2 n)$。对于每一个符合条件 $a_i\mid a_k,a_k\mid a_j$ 的三元组 $(i,k,j)$，暴力判断是否满足条件 $i\le k\lt j$，若满足暴力更新即可。

第二个问题是状态数。没有优化前，空间复杂度为 $\Theta(n^2)$。随即我们发现，在同一个 $j$ 中，第二维转移都是 $j$。就发现 $j$ 是没有用的，若要求 $\sum f_{i,j}$ 更新直接存进 $f_i$ 的桶里。查询只需 $\Theta(1)$。

第三个问题是查询。一个很明显的优化是把所有询问区间离线下来按右端点排序，扫描线即可。可是这样要查询也是 $\Theta(n^2)$ 的。考虑优化。由于查询的是一段连续区间，而 dp 数组只会最多被更改 $\Theta(n\log n)$ 次，我们想到用树状数组优化，使得更改 $\Theta(n\log^2 n)$，查询 $\Theta(n\log n)$。

$\Theta(n\log^2 n)$。

[submission](https://codeforces.com/contest/1946/submission/252804697)

**附：对三层枚举时间复杂度 $\Theta(n\log^2n)$ 的证明**

感谢 @honglan0301 提供的证明方式。

对于三元组 $(i,j,k)$ 满足 $a_i\mid a_j,a_j\mid a_k$ 的条件（注意这里为了方便，$i,j,k$ 的顺序与上文并不一样），我们考虑先枚举 $i$，$j$ 作为 $i$ 的倍数，直接枚举 $i$ 的倍数即可，$k$ 同理。这样可以确保不会枚举到一个三元组不满足 $a_i\mid a_j,a_j\mid a_k$ 的条件。

对于循环总数，我们可以看做如下式子：

$$\sum_{i=1}^{n}d(i)\lfloor\frac{n}{i}\rfloor$$

其中，$d(i)$ 表示 $i$ 的约数个数。

很容易发现，$i$ 的部分对应三元组的 $j$，$d(i)$ 的部分对应三元组的 $i$，$\lfloor\frac{n}{i}\rfloor$ 的部分对应三元组中的 $k$。

考虑倍增分段求此式子。对于 $i\in[2^k,2^{k+1}-1)$，显然有 $\lfloor\frac{n}{2^{k+1}}\rfloor\sum_{i=2^k}^{2^{k+1}-1}d(i)\le \sum_{i=2^k}^{2^{k+1}-1}d(i)\lfloor\frac{n}{i}\rfloor\le \lfloor\frac{n}{2^k}\rfloor\sum_{i=2^k}^{2^{k+1}-1}d(i)$。对于左右两式 $\sum$ 的部分，易证是 $\Theta(2^kk)$ 的。乘上左边式子，也就变成 $\Theta(nk)$。间接说明 $\sum_{i=2^k}^{2^{k+1}-1}d(i)\lfloor\frac{n}{i}\rfloor$ 是 $\Theta(nk)$ 级别的。易知 $k\le\log n$，所以每一段都是 $\Theta(n\log n)$ 的。由于倍增分段，固有 $\Theta(\log n)$ 段。总时间复杂度为 $\Theta(n\log^2n)$。

各位看官点个赞再走吧 qwq

---

## 作者：Svemit (赞：6)

[blog](https://www.cnblogs.com/Svemit/p/18099604)

赛时没看 F,写完 E 就没时间了，唉唉，唉唉唉唉。

思路是 t 宝的代码。

# Solution

考虑只有一组询问 $l = 1, r = n$ 的时候怎么做。

此时显然可以 dp，设 $f_i$ 为以 $a_i$ 结尾的合法子序列的个数。

得到方程

$$f_i = 1 + \sum_{a_j \mid a_i} f_j$$

$1$ 是子序列中只有自己的情况。

答案即为 $\sum f_i$。

对于原问题，考虑扫描线。

发现枚举 $r$ 的话不是很好维护 dp 数组，因为对于每个 $l$  的 dp 数组是不一样的，所以这里枚举 $l$。

假设此时枚举到 $l$，那所有 $dp_i$ 的值是 $[l + 1, i]$ 区间内以 $i$ 结尾的合法子序列的数量。

将 $f_l$ 初始化为 $1$。

如果直接按之前那样枚举的话，复杂度会炸到 $n^2$。考虑 $a_l$ 能影响到的数只有 $a_l$ 的倍数，考虑每次只枚举这些数。

这些数每个会有一个增量，根据之前的 dp，发现增量也可以 dp 算出来，只需要将方程改成 $f_i = \sum_{a_j \mid a_i} f_i$ 即可。

优化这个过程，可以通过先枚举 $a_l$ 的倍数，假设是 $k$，此时 $k$ 的增量已经被算出，再枚举 $k$ 的倍数 $k'$ 让 $k'$ 的增量加上 $k$ 的增量，就能够保证 $a_l$ 的所有倍数能够算出增量。

算出增量后，用树状数组维护 $f$ 数组的区间和即可。

一轮枚举倍数是 $O(n \ln n)$ 的，要枚举所有倍数的倍数即为 $O(n \ln ^ 2 n)$，用树状数组让所有倍数加上增量是 $O(n \ln n \log n)$ 的，所以总复杂度为 $O(n \log ^ 2 n)$。

```cpp
struct BIT {
	int n;
	vector<ll> c;

	BIT(int _n) {
		n = _n;
		c.resize(n + 1, 0);
	}

	void add(int x, int v) {
		for (; x <= n; x += x & -x) c[x] += v;
	}

	ll query(int x) {
		ll res = 0;
		for (; x; x -= x & -x) res += c[x];
		return res;
	}

	ll query(int l, int r) {
		l --;
		return query(r) - query(l);
	}
};

void solve() {
	int n, m;
	cin >> n >> m;
	vector<int> a(n + 1), p(n + 1);
	for (int i = 1; i <= n; i ++) {
		cin >> a[i];
		p[a[i]] = i;
	}
	
	vector<vector<pair<int, int>>> qry(n + 1);
	for (int i = 1; i <= m; i ++) {
		int l, r;
		cin >> l >> r;
		qry[l].emplace_back(r, i);
	}

	vector<ll> ans(m + 1);
	vector<ll> g(n + 1);
	BIT bit(n);

	for (int l = n; l >= 1; l --) {
		int x = a[l];
		g[x] = 1;
		for (int i = x; i <= n; i += x) {
			if (p[i] < p[x]) continue;
			for (int j = i + i; j <= n; j += i) {
				if (p[j] < p[i]) continue;
				g[j] += g[i];
			}
		}
		for (int i = x; i <= n; i += x) {
			if (p[i] < p[x]) continue;
			bit.add(p[i], g[i]);
			g[i] = 0;
		}
		for (auto [r, id] : qry[l]) ans[id] = bit.query(r);
	}
	for (int i = 1; i <= m; i ++) cout << ans[i] << " \n"[i == m];
} 
```

---

## 作者：快乐的大童 (赞：4)

赛时想出来但是没写出来。
### 题意简述
定义一个合法序列 $a_1,a_2,\cdots a_m$ 满足以下条件：

- 对于 $1\le i<m$，$a_{i+1}$ 被 $a_i$ 整除。

初始给定**排列** $a$，$q$ 次询问，每次询问给出 $l,r$，求出 $a_{[l,r]}$ 的所有可以不连续的子序列中，合法的序列的数目。

$n,q\le 10^6$，时间限制 6s。
### 分析
如果我们知道的原本的序列，考虑 dp。设 $f_i$ 表示以 $i$ 结尾的合法序列个数，转移方程即为 $f_i=1+\sum_{1\le j<i,a_j|a_i}f_j$。因为原序列是一个排列，保证了没有相同的数字，所以考虑直接枚举 $a_j$ 的倍数进行转移，时间复杂度是调和级数的。

现在有了区间查询。我们先用个数据结构维护 dp 值，下文出于某些原因，$f_i$ 是以 $i$ 为开头的合法序列个数。

考虑离线，从后往前枚举左端点 $l$，$f_l$ 的值可以直接枚举倍数求，时间复杂度调和级数。

考虑如何去除掉包含 $(r,n]$ 范围内的合法序列。我们发现沿用 $f$ 的状态定义难以去除掉所有不在范围内的合法序列，所以我们新设 $g_i$ 表示以 $i$ 为结尾的合法序列（同时也用数据结构维护），容易发现这样的话一次查询的答案就是 $\sum_{i=l}^nf_i-\sum_{i=r+1}^ng_i$（因为 $g_i$ 同时也计算了所有数都在 $(r,n]$ 范围内的序列，所以我们要把 $(r,n]$ 范围内的 $f_i$ 也加进来）。

现在考虑如何在左移左端点 $l$ 时计算 $g_i$。显然只有 $a_l$ 的倍数才会被更新 $g_i$。所以同样枚举 $a_l$ 的倍数，首先对这些数记录一个 $delta_i$ 表示这次更新中 $g_i$ 的变化量，初始化为 $1$（因为无论如何该数和 $a_l$ 构成一个合法序列，当然初始化为 $0$ 也可以做）。然后对每个数开一个 vector 记录它的约数。枚举 $a_i$ 的每个约数 $a_j$，若 $a_l|a_j$，则将 $delta_i\leftarrow delta_i+delta_j$，最后将 $delta_i$ 加进维护 $g$ 的数据结构里。

那么这道题就做完了，我们发现该数据结构需要支持单点加和后缀求和，树状数组即可。

时间复杂度大体是 $O(n\log n\cdot d(n))$ 的，但这个 log 和这个 $d(n)$ 都是远远跑不满的。关于卡常，优化一下读入，再加个 `inline`，就能过了。

[code](https://codeforces.com/contest/1946/submission/252912310)

---

## 作者：LinkCatTree (赞：2)

毒瘤卡常，来写题解了。

设计 dp 状态 $f_{l, r}$ 表示区间 $[l, r]$ 中整除序列的个数，可知 dp 转移为 $f_{l, r}=\sum_{l \leq k < r} [a_k | a_r] f_{l, k}$，这样朴素 dp 的时间复杂度是 $\mathcal{O}(qn^2)$ 的，~~卡常都过不了~~。而我们发现转移的 dp 状态第一维都是**相同**的，自然想到滚动第一维 $l$。

于是我们运用常用技巧，从 $n$ 到 $1$ 枚举 $l$，对 $l$ 分组进行**离线**查询，我们可以运用线段树或者树状数组之类的做到 $\mathcal{O}(\log n)$ 单次询问。考虑从以 $n$ 到 $1$ 的顺序枚举 $l$，我们希望可以以较优的时间复杂度将**以 $l+1$ 为左端点**时的 $f_{l+1 \cdots n}$ 转移为**以 $l$ 为左端点**时的 $f_{l \cdots n}$。

此时 dp 转移上无法较显然的进一步优化，我们挖掘题目性质。我们发现由于加入了 $a_l$ 产生了以 $a_l$ 为第一个的整除序列使 $f$ 值改变：假设一个整除序列为 $a_l, \cdots, a_r$，则 $f_{r \cdots n} \leftarrow f_{r \cdots n} + 1$。若我们对 $f$ 进行**差分**得到 $h$，那么该整除序列相当于使 $h_r \leftarrow h_r + 1$。而由于 $a_l | \cdots | a_r$ 即 $a_r$ 为 $a_l$ 的倍数，我们发现：对于排列 $a$，**至多**只有不超过 $\dfrac n{a_l}$ 个 $h_i$ **会改变**，而且每个 $a_l$ 均摊仅会使 $\mathcal{O}(\log n)$ 个 $h_i$ 改变！

于是我们再维护一个 $g_i$ 来表示每次 $h_i$ 的**增加量**（第二次差分），我们发现：

$$g_i = \begin{cases}
0 & a_i \not| a_l\\
1 & i=l\\
\sum_{a_j | a_i, j < i} g_j & a_i | a_l,i \neq l
\end{cases}$$

由于非零的 $g$ 较少，于是我们可以 $\mathcal{O}(\log^2 n)$ 枚举 $g_i$ 和 $g_j$ 进行转移。处理出 $g$ 值后，使用线段树进行 $\mathcal{O}(\log n)$ 次 $\mathcal{O}(\log n)$ 的修改操作，再维护 $\sum \sum g_i$ $\mathcal{O}(\log n)$ 查询，总时间复杂度 $\mathcal{O}(n \log^2 n+q \log n)$，不卡常不能过（也有可能是因为我程序天生常数大）。

接下来是一点奇怪的优化？卡常？

1. 用树状数组而非线段树，我不信有人能写线段树过了这题（

2. 预处理加入 $a_l$ 时会有哪些 $h_i$ 会变化，即提前枚举并存储好在 $a_l$ 右侧的 $a_l$ 的倍数。

代码仅供参考并安利博客：[here](https://www.cnblogs.com/LinkCatTree/p/19001352)。

---

## 作者：_•́へ•́╬_ (赞：2)

典型的傻逼 74 数学题。从做法傻逼到数据范围。

## 思路

考虑从右往左扫描线，根据扫描线的套路，要有一个树状数组维护确定右端点的答案，查询就是一个前缀和。

扫描线的时候要修改树状数组。我们按照从小到大的顺序处理当前位置上数字的倍数 $j$，更新 $j$ 的位置的树状数组值。

另开一个临时的数组，存储左右端点都固定的答案，这个数组在移动扫描线指针的时候要清空。

对于处理到的某个倍数 $j$，再枚举它的因数 $k$，如果 $k$ 的位置在 $j$ 之前，说明可以在 $i$ 到 $k$ 的链条后面直接加上 $j$ 得到 $i$ 到 $j$ 的链条，加上贡献即可。

## 复杂度

由于这个是排列，复杂度是 $\mathcal O(\sum\limits_{i=1}^n\sigma_0^2[i])$，其中 $\sigma_0[i]$ 表示 $i$ 的约数个数。这玩意[这么](/discuss/937862)算下来是 $\mathcal O(n\log^3n)$ 的。

## code

[按照上面叙述的思路写的](https://codeforces.com/contest/1946/submission/252772798)

[略有区别但是常数更小的](https://codeforces.com/contest/1946/submission/252782293)

---

## 作者：KSCD_ (赞：2)

### 思路
注意到给出的是一个排列，也就是每个数只会出现一次。所以如果枚举倍数或因数，总复杂度都是 $O(n\ln n)$ 的，这是本题复杂度正确的关键。

考虑对整个序列怎么做，设 $f_i$ 表示以 $i$ 为结尾的合法子序列数量，转移为 $f_i=\sum_{j=1}^{i-1}f_j[a_j\mid a_i]+1$，也就是在结尾是 $a_i$ 因数的子序列后接上 $a_i$，或 $a_i$ 自身作为一个子序列。

再扩展到区间询问。考虑把所有询问离线下来，然后从后往前依次处理整个序列，$f_i$ 也变成结尾为 $i$ 且开头已被处理的子序列数量。那么对于询问 $[l,r]$，只需要在处理完 $l$ 后计算 $\sum_{i=l}^r f_i$ 即为答案。

考虑如何计算 $a_i$ 对后面 $f$ 值的贡献。设 $d_j$ 表示 $f_j$ 在这一次维护中增多的数量，显然后面所有满足 $a_i\mid a_j$ 的 $f_j$ 都可以接在 $a_i$ 后面，也即 $d_j=1$。另外也可以从 $j$ 继续往后接上 $k$，需要满足 $a_j\mid a_k$。所以按照递增顺序依次处理每个 $j$，在处理完 $d_j$ 后给后面所有 $a_j\mid a_k$ 的 $d_k$ 加上 $d_j$，也就是在 $a_i$ 后面接上了一段子序列。

这样处理完所有 $d_j$ 后再全部加入 $f$ 数组即可。可以发现维护 $f$ 数组的过程是单点修改，同时会有对 $[l,r]$ 的区间查询，可以使用树状数组维护。时间复杂度为 $O(n\ln n(\ln n+\log n)+q \log n)$，分别为两重枚举倍数、单重枚举倍数修改和查询的复杂度。
### 代码
代码中预处理了 $tp_i$ 记录 $i$ 后面所有是 $a_i$ 倍数的位置。
```cpp
#include<iostream>
#include<algorithm>
#include<vector>
#define int long long
#define pii pair<int,int>
using namespace std;
const int N=1e6+10;
int n,q,d[N],a[N],pos[N],res[N]; 
vector <pii> ask[N]; 
vector <int> tp[N];
struct bit
{
	int b[N];
	void clear() {for(int i=0;i<=n;i++) b[i]=0;}
	int lowbit(int x) {return x&(-x);}
	void add(int p,int k) {for(;p<=n;p+=lowbit(p)) b[p]+=k;}
	int query(int p) {int tr=0; for(;p;p-=lowbit(p)) tr+=b[p]; return tr;}
}f;
void sol()
{
	cin>>n>>q,f.clear();
	for(int i=1;i<=n;i++) cin>>a[i],pos[a[i]]=i,ask[i].clear(),tp[i].clear();
	for(int i=1;i<=n;i++)
	{
		for(int j=a[i]*2;j<=n;j+=a[i]) if(pos[j]>i) tp[i].push_back(pos[j]);
		sort(tp[i].begin(),tp[i].end());
	}
	for(int i=1,l,r;i<=q;i++) cin>>l>>r,ask[l].push_back({r,i});
	for(int i=n;i>=1;i--)
	{
		f.add(i,1);
		for(int j:tp[i]) d[j]=1;
		for(int j:tp[i]) for(int k:tp[j]) d[k]+=d[j];
		for(int j:tp[i]) f.add(j,d[j]);
		for(pii te:ask[i]) res[te.second]=f.query(te.first);
	}
	for(int i=1;i<=q;i++) cout<<res[i]<<' ';
	cout<<'\n';
}
signed main()
{
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	int TT; cin>>TT;
	while(TT--) sol();
	return 0;
}
```

---

## 作者：ssy666666 (赞：2)

# 题解：CF1946F Nobody is needed

## 前置知识——级数求和量级

调和级数 $H_n$ 求和，即求下面式子的近似值：

$$H_n=\sum_{i=1}^\infty \frac{1}{i}$$

可以证明，$H_n$ 的数量级是 $\log$ 级别的。

这里给出一个不太严谨的证明方法：

$$H_n=\sum_{i=1}^\infty \frac{1}{i}$$

$$=\frac{1}{1}+\frac{1}{2}+\frac{1}{3}+\frac{1}{4}+\frac{1}{5}+\frac{1}{6}+\frac{1}{7}+\frac{1}{8}...$$

$$\approx \frac{1}{1}+\frac{1}{2}+\frac{1}{2}+\frac{1}{4}+\frac{1}{4}+\frac{1}{4}+\frac{1}{4}+...$$

当一共有 $n$ 项时，$H_n$ 的大小的**数量级**为 $\log n$

实际上，$H_n=\ln n + \gamma + \varepsilon_n$，可以通过积分比较法证明，这里不做展开。

## 题目做法

先考虑简化版，当 $l=1$ 时，所有的情况。

我们可以设计 `dp` 方程，令 $dp[i]$ 为以 $a_i$ 为结尾的方式数，可得到：

$$dp[i]=1+\sum_{a_j \mid a_i \land j<i} dp[j]$$

所以每个状态向其他状态贡献的次数为：

$$\sum_{i=1}^n \frac{n}{i}$$

$$=n\sum_{i=1}^n \frac{1}{i}$$

所以这个转移方程的的时间复杂度是 $n \log n$。

接着考虑如何将左端点向右移动。

首先，向右移动一位相当于消除当前这一位的贡献，而当前这一位 $i$ 只会对 $i<j \land a_i \mid a_j$ 的 $j$ 做出贡献！

所以问题转化为，以 $a_i$ 作为第一位的数列有多少种？

沿用初始的思想，再做一次 `dp` 就可以了。

所以 `dp` 方程为：

$$dp[i]=\sum_{a_j \mid a_i \land j<i} dp[j]$$

但是我们只用对 $a_i$ 和 $a_i$ 的倍数进行 `dp` 就可以了。时间复杂度仍为 $n \log n$。

新的问题出现，我们应该如何存储当前的值？

我们需要进行单点加（初始化时的第一遍 `dp`），区间求和（查询），单点减（左端点向右移时消除的贡献）。

因此，树状数组闪亮登场！！！

最后，只需要将询问离线下来，按左端点排序，依次处理即可。

## AC code
```cpp
#include<bits/stdc++.h>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<stack>
#include<vector>
//#include<conio.h>
#include<string>
#include<map>
#include<cstdlib>
#include<queue>
#include<math.h>
#include<time.h>
#include<set>
#include<cstdio>
#include<stdio.h>
#include<algorithm>
#pragma GCC optimize(3)
#pragma GCC target("avx")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#pragma GCC optimize(2)
#define int long long
using namespace std;

namespace IN{
    const int MAX_INPUT = 1000000;
    #define getc() (p1==p2&&(p2=(p1=buf)+inbuf->sgetn(buf,MAX_INPUT),p1==p2)?EOF:*p1++)
    char buf[MAX_INPUT],*p1,*p2;
    template<typename T>inline bool read(T &x) {
        static std::streambuf *inbuf=cin.rdbuf();
        x=0;
        register int f=0,flag=false;
        register char ch=getc();
        while(!isdigit(ch)){
            if (ch=='-') f=1;
            ch=getc();
        }
        if(isdigit(ch)) x=x*10+ch-'0',ch=getc(),flag=true;
        while(isdigit(ch)) {
            x=x*10+ch-48;
            ch=getc();
        }
        x=f?-x:x;
        return flag;
    }
    template<typename T,typename ...Args>inline bool read(T& a,Args& ...args) {
       return read(a)&&read(args...);
    }
    #undef getc
}
using namespace IN;

struct Node
{
	signed l,r;
	signed w;
};

bool cmp(Node i,Node j)
{
	return i.l<j.l;
}
signed n,q;
signed a[1000005];

int tr[1000005];
int dp[1000005];
Node ques[1000005];
int ans[1000005];

void add(int u,int num)
{
	while(u<=n)
		tr[u]+=num,u+=u&(-u);
}

int query(int u)
{
	int cnt=0;
	while(u>0)
		cnt+=tr[u],u-=u&-u;
	return cnt;
}

void solve()
{
	read(n,q);
	register signed dir[1000005];
	for(register signed i=1;i<=n;i++)
		read(a[i]),dir[a[i]]=i;
	for(register signed i=1;i<=n;i++)
		dp[i]=1,tr[i]=0;
	
	for(register signed i=1;i<=n;i++)
	{
		for(register signed j=a[i]*2;j<=n;j+=a[i])
		{
			if(dir[j]>i)
				dp[dir[j]]+=dp[i];
		}
		add(i,dp[i]);
	}
	
	for(register signed i=1;i<=q;i++)
		read(ques[i].l,ques[i].r),
		ques[i].w=i;
	
	sort(ques+1,ques+1+q,cmp);
	
	int last=1;
	
	for(register signed i=1;i<=n;i++)
	{
		register signed e=a[i];
		while(ques[last].l==i and last<=q)
			ans[ques[last].w]=query(ques[last].r),
			last++;
			
		for(register signed j=e;j<=n;j+=e)
			dp[dir[j]]=0;
		dp[i]=1;
		
		for(register signed j=e;j<=n;j+=e)
		{
			register signed p=dir[j];
			for(register signed k=j*2;k<=n;k+=j)
			{
				if(dir[k]>p)
					dp[dir[k]]+=dp[p];
			}
			add(p,-dp[p]);
		}
	}
	
	for(signed i=1;i<=q;i++)
		printf("%lld ",ans[i]);
	printf("\n");
}

signed main()
{
	int t;
	read(t);
	
	while(t--)
		solve();
	return 0;
}
```

最后温馨提示，本题**卡常**！

---

## 作者：StayAlone (赞：1)

注意 $a$ 是排列。

考虑离线，对 $l$ 从右往左扫描线。

维护 $g_i$ 表示左端点大于等于当前 $l$，且以 $i$ 结尾的合法子序列数量。那么询问就是区间和。

扫到 $l$ 时，$l$ 只会对 $a_l\mid a_i$ 的 $g_i$ 作贡献（贡献以 $l$ 开头，以 $i$ 结尾的子序列数量），枚举倍数就能找到这些 $i$。作贡献是单点修改，所以可以用树状数组维护 $g$。具体贡献是多少呢？

设此时对 $i$ 的贡献为 $f_i$，首先有 $f_l=1$。考虑 $i$ 的上一位 $j$，也有 $a_j\mid a_i$，所以 $f_i=\sum\limits_{a_j\mid a_i\land j < i} f_j$。写的时候改成 $j$ 向 $i$ 贡献，就是枚举 $j$ 的倍数。

计算一下复杂度。

- 对于每个 $l$，枚举其倍数，再枚举其倍数的倍数。$\sum\limits_{i=1}^n\sum\limits_{j=1}^{n/i}\dfrac{n}{ij}\leq\sum\limits_{i=1}^n\dfrac{1}{i}\cdot\sum\limits_{j=1}^{n}\dfrac{n}{j}=\mathcal O(\sum\limits_{i=1}^n\dfrac{n\ln n}{i})=\mathcal O(n\ln^2 n)$。

- 对于每个 $l$，枚举其倍数，对 $g$ 单点修改。时间复杂度 $\mathcal O(n\ln n\log n)$。

- 对于每个询问，树状数组上查询区间和。时间复杂度 $\mathcal O(q\log n)$。

```cpp
int n, q, a[MAXN], pos[MAXN];
ll ans[MAXN], f[MAXN]; vector <pii> qur[MAXN];

struct BIT {
	ll a[MAXN];
	
	il void add(int x, ll k) {
		while (x <= n) a[x] += k, x += lowbit(x);
	}
	
	il ll query(int x) {
		ll ans = 0;
		while (x) ans += a[x], x -= lowbit(x);
		return ans;
	}
	
	il void clear() {
		rep1(i, 1, n) a[i] = 0;
	}
} T;

il void solve() {
	read(n, q); rer(i, 1, n, a), pos[a[i]] = i;
	rep1(i, 1, q) {
		int l, r; read(l, r);
		qur[l].eb(r, i);
	} T.clear();
	rep2(i, n, 1) {
		for (int x = a[i]; x <= n; x += a[i]) f[x] = 0;
		f[a[i]] = 1;
		for (int x = a[i]; x <= n; x += a[i]) if (pos[x] >= i) {
			T.add(pos[x], f[x]);
			for (int y = x; y <= n; y += x) if (pos[y] > pos[x]) f[y] += f[x];
		}
		for (auto [r, id] : qur[i]) ans[id] = T.query(r);
	}
	rep1(i, 1, q) printf("%lld ", ans[i]); puts("");
	rep1(i, 1, n) qur[i].clear();
}

int main() {
	for (int T = read(); T--; ) solve();
	return 0;
}
```

---

## 作者：Unnamed114514 (赞：1)

注意到 $a$ 是一个排列，这启发我们可以暴力枚举倍数。

对于区间计数问题，我们一般使用扫描线解决。

因为算倍数比算因数易，所以我们考虑按照左端点排序，从左往右扫，然后算以每个位置为左端点对它的倍数的贡献。

定义 $f_i$ 表示以 $i$ 结尾的方案数。

考虑转移：$f_j=\sum\limits_{a_d|a_j} f_d$，观察会加入哪些贡献。

- 首先 $i$ 对它有直接贡献。

- 然后其次若存在 $a_i\mid a_k\mid a_j$，那么 $f_i$ 会对 $f_k$ 贡献那从而导致 $f_j$ 增加。

- 如果 $a_i\mid a_{k_1}\mid a_{k_2}\mid a_j$ 的话可以在算完 $a_{k_2}$ 之后让 $i$ 通过 $k_2$ 贡献 $a_j$，其实就是路径压缩的思想，也可以转化成第一种情况。

那么我们再维护个 $g_i$ 表示 $i$ 的增量就行了。

按照上述思路，我们把贡献分成两种，首先枚举 $a_i$ 的贡献 $a_j$，$g_j\gets g_j+1$，然后枚举 $a_j$ 的倍数 $a_k$，$g_k\gets g_k+g_j$，这一步的时间复杂度是 $O(\sum d^2(i))=O(n\log^3n)$ 的。

然后求出所有增量后发现它就是单点修改区间查询，因为就只有 $a_i$ 的倍数会有变化，所以一共只有 $O(n\log n)$ 次单点加，用树状数组维护即可，这一步是 $O(n\log^2n)$ 的。

$O(n\log^3n)$ 的做法可能有点卡常，不要用 `#define int long long`！

关于答案的上界：显然是 $1,2,\cdots,n$ 的时候答案最大，实际测试方案数并不多。

---

## 作者：WaterSun (赞：1)

[更好的阅读体验](https://watersun.top/%5B%E9%A2%98%E8%A7%A3%5DCF1946F%20Nobody%20is%20needed)

# 思路

首先考虑只有一个询问，区间为 $[1,n]$ 的做法。

定义 $dp_i$ 表示前 $i$ 个数中，以 $a_i$ 结尾的方案数。容易得到状态转移方程：

$$
dp_i = 1 + \sum_{j < i \wedge a_j \mid a_i}{dp_j}
$$

最后的答案就是 $\sum_{i = 1}^n{dp_i}$。

考虑如何将这种方法推广。首先将询问离线下来，发现枚举 $r$ 不好确定 $dp$ 数组，于是考虑枚举 $l$，维护 $l + 1$ 到 $l$，$dp$ 数组的变化。

你发现，当加入一个 $a_l$ 时，会改变的 $dp$ 值的位置 $i$，一定满足 $i > l \wedge a_l \mid a_i$。于是直接枚举 $a_l$ 的倍数的位置进行转移即可。

发现最后算答案需要累一个前缀和，但是每一个 $l$ 求一个复杂度就不行了，所以需要利用树状数组优化一下。

**注：本题卡常，不要全开 `long long`，需要的才开 `long long`。**

# Code

```cpp
#include <bits/stdc++.h>
#define fst first
#define snd second
#define re register
#define ll long long

using namespace std;

typedef pair<int,int> pii;
const int N = 1e6 + 10;
int n,q;
int arr[N],p[N];
ll dp[N],ans[N];
vector<pii> Q[N];

inline int read(){
    int r = 0,w = 1;
    char c = getchar();
    while (c < '0' || c > '9'){
        if (c == '-') w = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9'){
        r = (r << 3) + (r << 1) + (c ^ 48);
        c = getchar();
    }
    return r * w;
}

struct BIT{
    #define lowbit(x) (x & -x)

    ll tr[N];

    inline void modify(int x,ll k){
        for (re int i = x;i <= n;i += lowbit(i)) tr[i] += k;
    }

    inline ll query(int x){
        ll res = 0;
        for (re int i = x;i;i -= lowbit(i)) res += tr[i];
        return res;
    }

    #undef lowbit
}T;

inline void solve(){
    n = read(),q = read();
    fill(T.tr + 1,T.tr + n + 1,0);
    for (re int i = 1;i <= n;i++){
        p[arr[i] = read()] = i;
        Q[i].clear();
    }
    for (re int i = 1;i <= q;i++){
        int l,r; l = read(),r = read();
        Q[l].push_back({r,i});
    }
    for (re int l = n;l;l--){
        dp[l] = 1;
        for (re int x = arr[l];x <= n;x += arr[l]){
            if (p[x] < p[arr[l]]) continue;
            for (re int y = x;y <= n;y += x){
                if (p[y] <= p[x]) continue;
                dp[p[y]] += dp[p[x]];
            }
            T.modify(p[x],dp[p[x]]); dp[p[x]] = 0;
        }
        for (auto u:Q[l]) ans[u.snd] = T.query(u.fst);
    }
    for (re int i = 1;i <= q;i++) printf("%lld ",ans[i]);
    puts("");
}

signed main(){
    int T; T = read();
    while (T--) solve();
    return 0;
}
```

---

## 作者：SFlyer (赞：0)

一道好题。

- 一定要好好读题，不要看漏。

一个非常非常重要的条件是，$a$ 是一个排列。这就说明可能会有调和级数之类的做法了。

- 考虑怎么处理询问 $[l,r]$ 之类的东西。

有一个普遍的思路，就是 $ans=sol(r)-sol(l-1)$，但是我们发现并不适用。因此朴素的 $f_i$ 表示 $1\sim i$ 的答案就可以了，我们必须再加一维状态，设 $f(l,r)$ 为起点在 $l$，终点在 $r$ 的方案数。

如果我们有了 $f(l,r)$，那么一次询问 $[ql,qr]$ 是要求 $\sum_{x\ge ql,y\le qr}f(x,y)$ 的和，其实就是一个二位数点问题。

- 考虑非 $0$ 的 $f(l,r)$ 有几个。

因为起点终点固定，那么一定 $a_l\mid a_r$。所以合法数量是 $\sum div(n)$ 个，也就是调和级数 $\mathcal{O}(n\ln n)$ 级别。

- 对于单个的 $f(l,r)$，怎么求。

可以固定左端点或者右端点。固定左端点 $l$ 更加容易，因为合法的右端点 $r$ 是找到 $a_l$ 的倍数，而不是找 $a_r$ 的因数。转移方程是 $f(l,r)=\sum_{r'<r}f(l,r')[a_{r'}\mid a_r]$。但是这个又要找因数了，所以考虑把习惯的 pull 改成 push，即对于 $f(l,r)$ 考虑他的贡献。这样，他对 $f(l,r')$ 其中 $a_r\mid a_{r'},r<r'$ 有贡献。

因此我们有了一个 $\mathcal{O}(n\ln^2n)$ 的做法。

- 二维数点的写法。

可以无脑的全部离线下来排序以后 bit 维护，但是发现其实可以从大到小枚举 $f(l,r)$ 的 $l$ 的过程中就把他解决掉，这样常数较小并且空间小、更好写。

因此得到了一个时空较为优秀的做法。

[submission](https://codeforces.com/contest/1946/submission/282484614)

---

## 作者：wnsyou (赞：0)

# [Nobody is needed](https://www.luogu.com.cn/problem/CF1946F)

推销我的[博客园。](https://www.cnblogs.com/wnsyou-blog/p/18340587/CF1946F_solution)
## 题意

多组数据。

给定一个长度为 $n$ 的**排列** $a$，你需要回答 $q$ 组询问，每组询问给出 $l,r$，求有多少个子序列 $t$ 使得：
- $l \leqslant t_1 < t_2 < \cdots < t_k \leqslant r$。
- $a_{t_i} \mid a_{t_{i + 1}}(1 \leqslant i < k)$。
### 数据范围

- $1 \leqslant n,q \leqslant 10^6$。
- $a$ 是**一个排列**。
- $1 \leqslant \sum n,\sum q \leqslant 10^6$。
## 思路

考虑使用 dp，令 $dp_i$ 表示以 $a_i$ 结尾的合法子序列个数，拓扑序为 $i$ 从小到大。

那么转移呢，很显然若是写收集形则 $dp_i$ 可以从所有 $a_i$ 的约数处转移过来，总复杂度是 $O(\sum\limits_{1 \leqslant i \leqslant n}\sqrt{i})$ 的，可以用代码计算一下，当 $n=10^6$ 时，总共需要大约 $6 \times 10^8$，不太能接受。

若是写扩散形，又不便于确定对于每组询问的答案。

可以考虑将拓扑序转为 $i$ 从大到小，那么对于 $i$，会发生修改的 $dp_j$ 只有那些 $i \leqslant j$ 且 $a_i \mid a_j$，也就是说只有 $\frac{n}{a_i}$ 处的 dp 需要修改，总复杂度为 $O(\sum\limits_{1\leqslant i \leqslant n} \frac{n}{i})$，很典型的调和级数 $O(n \log n)$，可以接受。

那么考虑怎么更新 dp 数组，正如上文所说，每次发生修改的只有 $a_i$ 的倍数，而修改的贡献可以分为 $a_i$ 对 $a_i \times x(x \geqslant 2)$ 的贡献和 $a_i \times x(x \geqslant 2)$ 对 $a_i \times x \times y (x,y \geqslant 2)$ 的贡献，但如果 $a_i$ 所对应的下标（即 $i$）在 $a_i \times x$ 的下标后面，则无法产生贡献，$a_i \times x$ 对 $a_i \times x \times y$ 同理。

为了保证查询时答案没有超出 $[l,r]$ 的范围，需要在每次更新完 dp 数组后处理那些 $l = i$ 的查询，答案就是 $\sum\limits_{i\leqslant j \leqslant r} dp_j$，为了快速求出答案，使用树状数组维护 dp 数组的和。

详细见代码。
### 复杂度

- 时间：$O(q \log n + n \log^2 n)$。
- 空间：$O(n + q)$。

## Code
```cpp
#include <iostream>
#include <vector>
#define _1 (__int128)1

using namespace std;
using ll = long long;

const int N = 1e6 + 10;

inline int lowbit (int x) {
  return x & -x;
}

int T, n, q, a[N], b[N];
ll ans[N], tr[N], dp[N];
vector<pair<int, int>> qry[N];

void modify (int x, int y) {
  for (int i = x; i <= n; i += lowbit(i)) tr[i] += y;
}

ll Query (int x) {
  ll ret = 0;
  for (int i = x; i; i -= lowbit(i)) ret += tr[i];
  return ret;
}

void Solve () {
  cin >> n >> q;
  for (int i = 1; i <= n; i++)
    cin >> a[i], b[a[i]] = i, tr[i] = 0, qry[i] = vector<pair<int, int>> (); // 多测要清空，b[i] 用于记录 i 在 a 中对应的下标
  for (int i = 1, l, r; i <= q; i++)
    cin >> l >> r, qry[l].push_back({r, i}); // 离线处理询问
  for (int i = n; i; i--) {
    dp[a[i]] = 1; // 初始状态
    for (int j = a[i]; j <= n; j += a[i]) 
      if (b[j] >= b[a[i]]) // 将两种转移合并可以这样写
        for (int k = j * 2; k <= n; k += j) // 注意是 k += j 而不是 k += a[i]
          if (b[k] > b[j])
            dp[k] += dp[j];
    for (int j = a[i]; j <= n; j += a[i])
      modify(b[j], dp[j]), dp[j] = 0; // 用树状数组维护 dp 和，dp 要清空
    for (auto [j, id] : qry[i])
      ans[id] = Query(j) - Query(i - 1); // 差分处理答案
  }
  for (int i = 1; i <= q; i++)
    cout << ans[i] << ' ';
}

int main () {
  ios::sync_with_stdio(0), cin.tie(0);
  // Solve();
  for (cin >> T; T--; Solve(), cout << '\n') {}
  return 0;
}
```

---

## 作者：苏联小渣 (赞：0)

对于单次询问，我们可以通过以下两种方法做：

- 从左往右做，设 $f_i$ 表示 $i$ 为结尾的方案数，那么可以从所有约数转移过来，时间复杂度 $O(n \sqrt{n})$。

- 从右往左做，设 $f_i$ 表示 $i$ 为开头的方案数，那么可以从所有倍数转移过来，时间复杂度 $O(n \log n)$。

考虑扫描线，每次加入一个点的时候，统计它的贡献。我们发现如果从左往右做的话，每次需要枚举约数等等，时间复杂度一看就很炸，所以考虑从右往左做，也就是按照左端点排序扫描线。

假设此时扫到了 $i$，如果我们只是算以 $i$ 为开头的方案数的话，我们很难确定它的结尾在哪。所以转换思路，在对左端点扫描线的同时，维护 $g_j$ 表示以 $j$ 为结尾的方案数。加入最左端的 $i$ 的时候，显然只会对其倍数的 $g$ 产生影响。枚举其倍数 $a_j$，那么 $i$ 对 $j$ 产生的贡献可以分为：

- 该子序列只包含 $i,j$，那么此时 $i$ 对 $j$ 的贡献为 $1$；

- 该子序列中间还包含其它数，考虑枚举倒数第二个 $k$，那么此时 $i$ 对 $j$ 的贡献为 $i$ 对 $k$ 的贡献。

可以通过简单的 dp 求出 $i$ 对所有倍数的贡献，最后再把这些贡献加到树状数组上就好了。

枚举倍数总复杂度是 $O(n \log n)$，加入树状数组和枚举另一个倍数会多一个 $\log $，所以总时间复杂度为 $O(n \log^2 n)$。

### Code：

```c++
#include <bits/stdc++.h>
using namespace std;
#define int long long
int t, n, q, l, r, a[1000010], ans[1000010], pos[1000010], f[1000010];
struct node{
	int r, id;
};
vector <node> ask[1000010];
struct BIT{
	int d[1000010];
	void clear(int sz){
		for (int i=1; i<=sz; i++) d[i] = 0;
	}
	void add(int p, int x){
		for (; p<=n; p+=p&-p) d[p] += x;
	}
	int query(int p){
		int ret = 0;
		for (; p; p-=p&-p) ret += d[p];
		return ret; 
	}
}S;
signed main(){
	scanf ("%lld", &t);
	while (t --){
		scanf ("%lld%lld", &n, &q);
		S.clear(n);
		for (int i=1; i<=n; i++){
			scanf ("%lld", &a[i]);
			ask[i].clear(), pos[a[i]] = i;
		}
		for (int i=1; i<=q; i++){
			scanf ("%lld%lld", &l, &r);
			ask[l].push_back((node){r, i});
		}
		for (int i=n; i>=1; i--){
			for (int j=a[i]; j<=n; j+=a[i]){
				if (pos[j] >= i) f[j] = 1;
				else f[j] = 0;
			}
			for (int j=a[i]*2; j<=n; j+=a[i]){
				for (int k=j*2; k<=n; k+=j){
					if (pos[k] > pos[j]) f[k] += f[j];
				}
			}
			for (int j=a[i]; j<=n; j+=a[i]){
				if (pos[j] >= i) S.add(pos[j], f[j]);
			}
			for (int j=0; j<ask[i].size(); j++){
				int r = ask[i][j].r, id = ask[i][j].id;
				ans[id] = S.query(r) - S.query(i-1);
			}
		}
		for (int i=1; i<=q; i++){
			printf ("%lld ", ans[i]);
		}
		puts ("");
	}
	return 0;
}

```

---

## 作者：MaxBlazeResFire (赞：0)

从左往右扫描线。记 $f_l$ 表示以 $l$ 为左端点的合法子序列个数。对于一个数 $r$，取出它左侧所有的因子取出一个长度为 $len$ 的新数列，在这个长度为 $len$ 的新序列上，定义 $g_i$ 表示以 $i$ 开头，$r=len$ 为结尾的合法子序列个数，倒着做一个 $O(len^2)$ 的暴力 $\rm DP$ 转移，然后将 $g$ 的结果对位加到 $f$ 上，用一个 $\rm BIT$ 维护 $f$ 的单点加，区间和查询。

复杂度 $O(n\ln^2n+n\log n\ln n+q\log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
#define MAXN 1000005

int n,q,a[MAXN],pos[MAXN];
ll tr[MAXN + 5],f[MAXN],g[MAXN],Ans[MAXN];

inline void add( int x , ll k ){ for( ; x <= n ; x += x & -x ) tr[x] += k; }
inline ll sum( int x ){ ll ret = 0; for( ; x ; x -= x & -x ) ret += tr[x]; return ret; }

inline int read(){
	int x = 0; char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();
	while( ch >= '0' && ch <= '9' ) x = x * 10 + ch - 48,ch = getchar();
	return x;
}

void write( ll x ){
	if( x >= 10 ) write( x / 10 );
	putchar( x % 10 + 48 );
}

vector<int> fac[MAXN];
vector< pair<int,int> > Q[MAXN];

inline void solve(){
	n = read(),q = read();
	for( int i = 1 ; i <= n ; i ++ ) a[i] = read(),pos[a[i]] = i;
	for( int i = 1 ; i <= n ; i ++ )
		for( int j = i ; j <= n ; j += i ) if( pos[i] <= pos[j] ) fac[j].emplace_back( pos[i] );
	for( int i = 1 ; i <= n ; i ++ ) sort( fac[i].begin() , fac[i].end() );
	for( int i = 1 ; i <= q ; i ++ ){
		int l = read(),r = read();
		Q[r].emplace_back( make_pair( l , i ) );
	}
	for( int r = 1 ; r <= n ; r ++ ){
		int siz = fac[a[r]].size(); g[r] = 1;
		vector<int> tmp = fac[a[r]];
		for( int i = siz - 1 ; i >= 0 ; i -- ){
			int v = tmp[i];
			for( int j = siz - 1 ; j > i ; j -- ){
				int k = tmp[j];
				if( a[k] % a[v] == 0 ) g[v] += g[k];
			}
			add( v , g[v] );
		}
		for( int i = siz - 1 ; i >= 0 ; i -- ){
			int v = tmp[i];
			f[v] += g[v],g[v] = 0;
		}
		for( pair<int,int> ele : Q[r] ) Ans[ele.second] = sum( r ) - sum( ele.first - 1 );
	}
	for( int i = 1 ; i <= q ; i ++ ) write( Ans[i] ),putchar(' '); puts("");
	for( int i = 1 ; i <= n ; i ++ ) fac[i].clear(),Q[i].clear(),f[i] = tr[i] = 0;
}

signed main(){
	int testcase = read();
	while( testcase -- ) solve();
	return 0;
}
```

---

