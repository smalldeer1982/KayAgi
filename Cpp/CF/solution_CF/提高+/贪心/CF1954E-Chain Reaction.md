# Chain Reaction

## 题目描述

There are $ n $ monsters standing in a row. The $ i $ -th monster has $ a_i $ health points.

Every second, you can choose one alive monster and launch a chain lightning at it. The lightning deals $ k $ damage to it, and also spreads to the left (towards decreasing $ i $ ) and to the right (towards increasing $ i $ ) to alive monsters, dealing $ k $ damage to each. When the lightning reaches a dead monster or the beginning/end of the row, it stops. A monster is considered alive if its health points are strictly greater than $ 0 $ .

For example, consider the following scenario: there are three monsters with health equal to $ [5, 2, 7] $ , and $ k = 3 $ . You can kill them all in $ 4 $ seconds:

- launch a chain lightning at the $ 3 $ -rd monster, then their health values are $ [2, -1, 4] $ ;
- launch a chain lightning at the $ 1 $ -st monster, then their health values are $ [-1, -1, 4] $ ;
- launch a chain lightning at the $ 3 $ -rd monster, then their health values are $ [-1, -1, 1] $ ;
- launch a chain lightning at the $ 3 $ -th monster, then their health values are $ [-1, -1, -2] $ .

For each $ k $ from $ 1 $ to $ \max(a_1, a_2, \dots, a_n) $ , calculate the minimum number of seconds it takes to kill all the monsters.

## 样例 #1

### 输入

```
3
5 2 7```

### 输出

```
10 6 4 3 2 2 1```

## 样例 #2

### 输入

```
4
7 7 7 7```

### 输出

```
7 4 3 2 2 2 1```

## 样例 #3

### 输入

```
10
1 9 7 6 2 4 7 8 1 3```

### 输出

```
17 9 5 4 3 3 3 2 1```

# 题解

## 作者：未来姚班zyl (赞：23)

## 题目大意

有 $n$ 个怪兽站成一派，第 $i$ 只血量为 $a_i$。当你的攻击力是 $k$ 时，你可以选择一段极长的连续的存活的怪兽，使它们血量同时减少 $k$，对于每个 $k$ 求出最少攻击多少次可以杀死所有的怪兽。

## 题目分析

提供一个非常简单直观的 $O(n\log n+V)$ 做法。首先可以发现最小攻击次数和顺序无关，我们每次都是随便选一个连续段攻击。那么我们可以转换一下攻击的表达：

- 设存活的怪兽为 $1$，死亡的怪兽为 $0$，则每次可以花费极长 $1$ 的连续段的数量的代价使得所有怪兽的血量减少 $k$。

这时候可以发现，所有怪兽减少的血量总是相等，$01$ 序列的取值只与造成伤害的**总量**有关，设总量为 $x$。显然，怪兽 $i$ 在 $x<a_i$ 时取 $1$，在 $x\ge a_i$ 时取 $0$。所以我们可以按照 $x$ 扫描线，维护一个初始全为 $1$ 的序列，支持将一个 $1$ 改成 $0$，并维护 $1$ 的极长连续段个数。直接简单讨论就可以 $O(1)$ 完成。这一部分复杂度 $O(V+n)$。

然后就直接暴力模拟就可以了，复杂度为调和级数 $O(n\log n)$。

代码很简单，是优雅的 410B。

```cpp
#include<bits/stdc++.h>
#define rep(x) for(int i=1;i<=x;i++)
using namespace std;
const int N=2e5;
int n,m,b[N],c[N],x;
vector<int>p[N];
int main(){
	cin>>n;
	rep(n)cin>>x,m=max(m,x),p[x+1].push_back(i),b[i]=1;
	rep(m){
		c[i]=c[i-1];
		for(auto y:p[i])c[i]+=(b[y-1]&b[y+1])-(!(b[y-1]|b[y+1])),b[y]=0;
	}
	rep(m){
		long long ans=0;
		for(int j=1;j<=m;j+=i)ans+=c[j]+1;
		cout<<ans<<' ';
	}
}
```

---

## 作者：Halberd_Cease (赞：10)

容易想到，在已经将所有的 $a_i$ 减去同一个值之后，如果要再减去同一个值（已经死亡的怪物不需要减也不能减，因此不算在内），所需步数为当前序列中连续大于 $0$ 的段数。

考虑预处理出减去每一个值 $k\in[1,\max(a_1,a_2,\dots,a_n)]$ 后再次操作需要的操作次数，记为 $ans_k$。

初始连通块（即连续大于 $0$ 的块）个数是 $1$，考虑对于所有的 $a_i=k$，由于 $a_i$ 在 $k=a_i-1$ 时没有被消掉，而在当前 $k$ 下会被消掉，因此 $k=x$ 相对 $k=x-1$ 时变化的地方只有 $a_i=k$。

枚举每一个 $a_i=k$，如果 $a_{i-1}$ 和 $a_{i+1}$ 已经全部消掉了，那么就减少一个连通块，如果两边都没有消掉就增加一个，一边有一边没有就不变。

那么我们就可以通过 $k=x-1$ 的状态转移出 $k=x$ 的状态，由于只有 $n$ 个 $a_i$，这一步是 $O(n)$ 的（令 $n$ 和 $\max(a_1,a_2,\dots,a_n)$ 同阶）。

接着对于每一个间隔 $k$，其答案就应该是 $ans_0+ans_k+ans_{2k}+\dots+ans_{xk}$，有 $xk<\max(a_1,a_2,\dots,a_n)$，这一步的复杂度是调和级数 $O(n\ln n)$ 的。

[submission](https://codeforces.com/contest/1954/submission/256609109)

---

## 作者：2huk (赞：5)

> - 给定一个长度为 $n$ 的序列 $a$，你还有一个属性 $k$，定义一次操作为：
>
>   - 选择 $a$ 中一段**极长的**区间 $[l, r]$，满足 $\min \limits_{i = l} ^ r a_i > 0$。在这里，**极长的**区间定义为 $[l, r]$ 满足条件但 $[l - 1, r]$ 与 $[l, r + 1]$ 不满足条件。
>   - $\forall i \in [l, r] \cap \mathbb{N}$，执行 $a_i \gets a_i - k$。
>
>   定义 $f(k_0)$ 为当 $k = k_0$ 时，为使 $\max a_i \le 0$ 的最小操作数。
>
>   你需要分别求出 $f(1), f(2), f(3), \dots, f(\max a_i)$ 的值。
>
> - $n, m \le 10 ^ 5$，$m = \max a_i$。

发现操作顺序是无所谓的。每次随便选择一个合法区间操作均可。

对于一个数 $a_i$ 而言，如果有一次操作覆盖了它，那么它的值会减少 $k$。因此需要 $\lceil \frac {a_i}k \rceil$ 次操作就能将其变成非正数。

然后仿照 [积木大赛](https://www.luogu.com.cn/problem/P1969) 可得：
$$
f(k) = \sum_{i=1}^n \max\left(0, \left \lceil \dfrac {a_i}k \right \rceil - \left \lceil \dfrac {a_{i-1}}k \right \rceil \right)
$$
暴力求解是 $\Theta(nm)$ 的。无法通过。思考整除分块做法。

可以发现对于 $a_i$ 而言，如果 $a_i < a_{i - 1}$，那么 $(a_{i-1}, a_i)$ 的组合是没有贡献的，其组合有贡献当且仅当 $a_i > a_{i - 1}$，此时 $a_i$ 的贡献为正。同理，$(a_i, a_{i + 1})$ 有贡献当且仅当 $a_i < a_{i + 1}$，此时 $a_i$ 的贡献为负。

所以我们考虑整除分块，即计算每一个极长的区间 $[l, r]$ 使得对于所有 $k_1, k_2 \in [l, r]$ 都满足 $\lceil \frac{a_i}{k_1} \rceil = \lceil \frac{a_i}{k_2} \rceil$。那么如果 $a_i > a_{i - 1}$ 会对 $f(l), f(l + 1), \dots, f(r)$ 贡献 $\lceil \frac{a_i}l \rceil$，如果 $a_i < a_{i + 1}$ 会对 $f(l), f(l + 1), \dots, f(r)$ 贡献 $-\lceil \frac{a_i}l \rceil$。

维护差分即可。

```cpp
int n, a[N], f[N], s[N];

int calc(int a, int b) {
	// 最大的 c 使得 ↑a / c↑ = b
	if (b == 1) return 1e9;
	return (a - 1) / (b - 1);
}

void Luogu_UID_748509() {
	fin >> n;
	for (int i = 1; i <= n; ++ i ) fin >> a[i];
	int m = *max_element(a + 1, a + n + 1);
	
	for (int i = 1; i <= n; ++ i ) {
		for (int l = 1, r; l <= m; l = r + 1 ) {
			int t = (a[i] + l - 1) / l;
			r = min(m, calc(a[i], t));
			if (a[i] > a[i - 1]) s[l] += t, s[r + 1] -= t;
			if (a[i] < a[i + 1]) s[l] -= t, s[r + 1] += t;
		}
	}
	
	for (int i = 1; i <= m; ++ i ) {
		s[i] += s[i - 1];
		fout << s[i] << ' ';
	}
}
```

---

## 作者：_determination_ (赞：4)

这是五月末高中部学长给我们出的题，当时的看到 std 的感觉就是巧妙，优雅。

注意到我们每次攻击都是随便选一个极长合法段攻击即可，所以我们改写攻击描述：

对于一次攻击，将全部怪物的血量减少 $k$，代价为极长合法段的个数。

这样有什么用呢？显然每次查询直接累加总伤害值并处理出每次攻击的代价即可。

具体的，设当伤害为 $x$ 时极长合法段的段数为 $g(x)$。$f(x)=g(x)+g(2x)+\dots+g(kx)(kx>\max_{a_i})$。显然暴力计算复杂度是调和级数的。问题变为计算 $g(x)$。

考虑维护这个东西，$x$ 每增加 1 就会有一些点的值小于 0，我们可以把这些点先拿出来扔到一个 `vector` 里。这些点变成 0 之后对于总段数的贡献显然可以分讨然后 $O(1)$ 计算。

总复杂度 $O(n \ln n+n)$。

---

## 作者：Otue (赞：4)

为了简单起见，我们从 $k = 1$ 开始。

第一道闪电可以向任何怪物发射，因为它总是会扩散到所有怪物身上。我们将继续发射闪电，直到有怪物死亡。当一个或多个怪物死亡时，问题就会分解成几个独立的子问题，因为没有闪电会穿过死亡的怪物。而且我们不管选择什么怪物来发射闪电，分成的子问题都是相同的。**这意味着不存在最少秒数的概念——答案并不取决于发射闪电的怪物的选择。** 

那么我们该如何计算这个答案呢？攻击第一个怪物，直到它死亡。这需要 $a_1$ 秒。然后我们继续攻击第二个怪物。如果它的生命值比第一个怪物高，我们就需要额外发射 $a_2 - a_1$ 枚闪电来杀死它。否则，它已经死亡。在这两种情况下，第三个怪物会受到多少伤害？假设它的生命值很高。在第一种情况下，它会受到 $a_2$ 伤害，因为所有的闪电都会击中它。但在第二种情况下，它也会受到 $a_2$ 次伤害。以此类推。这就意味着 $i$ 个怪物需要被 $\max(0, a_i - a_{i - 1})$ 个闪电击中。

那么 $k = 1$ 的答案就等于 $a_1 + \sum\limits_{i = 2}^{n} \max(0, a_i - a_{i - 1})$。

如何计算任意 $k$ 的答案呢？事实上，两者的差别并不大。只需将每个怪物的健康值从 $a_i$ 改为 $\lceil \frac{a_i}{k} \rceil$ 即可，而前面所述的整个过程将保持不变。因此，任何 $k$ 的答案都等于 $\lceil \frac{a_1}{k} \rceil + \sum\limits_{i = 2}^{n} \max(0, \lceil \frac{a_i}{k} \rceil - \lceil \frac{a_{i - 1}}{k} \rceil)$。

继续优化。把 $\max$ 拆开，看每一个 $\lceil \frac{a_i}{k} \rceil$ 的系数，取决于两个条件：

- 如果是 $i = 1$ 或 $a_i \ge a_{i - 1}$，则系数增加 $1$。
- 如果是 $i = n$ 和 $a_i < a_{i + 1}$，则系数减少 $1$。

我们把 $i$ 怪兽的这个系数称为 $c_i$。因此，我们需要计算 $\sum\limits_{i = 1}^n c_i \cdot \lceil \frac{a_i}{k} \rceil$。注意，$c_i$ 是固定的。

这是什么？数论分块，只不过是向上取整的数论分块，但是我们知道 $\lceil \frac{n}{l} \rceil=\lfloor \frac{n-1}{l} \rfloor+1$，所以依然可以转化为下取整。

我们可以考虑每个 $a_i$ 对答案的贡献，比如当前极长 $[l,r]$ 使得 $\lceil\frac{a_i}{l}\rceil=\lceil\frac{a_i}{r}\rceil$，那么答案区间 $[l,r]$ 整体就加上 $c_i\times \lceil\frac{a_i}{l}\rceil$。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define PII pair<int, int>
#define _for(i, a, b) for (int i = (a); i <= (b); i++)
#define _pfor(i, a, b) for (int i = (a); i >= (b); i--)
#define int long long
const int N = 3e5 + 5;

int n, a[N], maxn, ans[N];

signed main() {
	cin >> n;
	_for(i, 1, n) cin >> a[i], maxn = max(maxn, a[i]);
	_for(i, 1, n) {
		int cnt = 0;
		if (i == 1 || a[i] > a[i - 1]) cnt++;
		if (i < n && a[i + 1] > a[i]) cnt--;
		int l = 1, r;
		while (l <= a[i]) {
			int t = (a[i] - 1) / l;
			if (t) r = (a[i] - 1) / t;
			else r = a[i];
			ans[l] += cnt * (t + 1);
			ans[r + 1] -= cnt * (t + 1);
			l = r + 1; 
		} 
		ans[a[i] + 1] += cnt; // warning!
	}
	_for(i, 1, maxn) ans[i] += ans[i - 1];
	_for(i, 1, maxn) cout << ans[i] << ' ';
}
```

---

服了，我这题解是不能看吗？一个空格多打就被打回，服。

---

## 作者：Poncirus (赞：3)

莫名其妙且又臭又长的根号做法。

容易发现一个怪被杀掉了序列就会裂开成两段连续子序列，以及最先被杀掉的怪物一定血量最少。在裂开来的两段连续子序列中也满足此规律，以此类推。

考虑对序列建立笛卡尔树。令树根为 $rt$，当前攻击力为 $k$，记 $t_{x, k}=\left\lceil \dfrac {h_x}k \right\rceil$，即不考虑其他条件时击倒 $x$ 所需次数。

那么对于 $rt$ 的左、右儿子 $l,r$，单考虑这三个怪物所需的总击倒次数，容易发现为 $t_{rt,k}+(t_{l,k}-t_{rt,k})+(t_{r,k}-t_{rt,k})$。

对于 $l$ 引导的子树，此时的实际已攻击次数为 $t_{l,k}$；所以对于 $l$ 的左右儿子 $l',r'$，击倒这两个怪物的所需次数为 $(t_{l',k} - t_{l,k})+(t_{r',k}-t_{l,k})$。$r$ 引导的子树同理。

所以我们就可以知道，如果存在树边 $u\to v$，那么击倒 $v$ 的所需次数为 $t_{v,k}-t_{u,k}$；特别地，击倒 $rt$ 的所需次数为 $t_{rt,k}$。

那么我们就可以通过一次 $\mathcal O(n)$ 的树上 DFS 对于一个 $k$ 找到答案了。

那么对于 $2\times 10^4$ 范围内的所有 $k$，应该怎么办呢？这个时候就要利用到 $t$ 的性质了进行根号分治了。

- 对于 $k\le \sqrt {2\times 10^4}$，我们大可以直接做这么多次 DFS 得到答案；

- 对于 $k>\sqrt {2\times 10^4}$：

  我们容易发现最终的结果是若干个 $t$ 的值相加减得到的，而每个 $t$  的权值 $cnt$ 取决于其在笛卡尔树上的儿子个数，有多少就在 $1$ 的基础上减去多少。

  由于 $t$ 实在过于特殊，考虑整除分块 / 数论分块。对于每个 $x$，对于任意 $k'\in (\sqrt {2\times 10^4}, 2\times 10^4]$，可能的 $t$ 值只有 $\sqrt {2\times 10^4 }$ 种。计算出对于每个 $t'$，满足 $\left\lceil \dfrac {h_x}{k'} \right\rceil=t'$ 的 $k'$ 范围，对该范围 $k'$ 的答案区间加上 $t'\times cnt$ 即可，可以使用差分。

  至此，就可以在一次 DFS 内解决这种情况下的问题。

总时间复杂度为 $\mathcal O(n\sqrt {2\times 10^4})$。

```cpp
/*
	值得注意的是，我在做这道题的时候并没有意识到自己用到了笛卡尔树，
	所以代码中笛卡尔树的建树部分可能长得特别抽象（
	我这里是使用了下标上的 ST 表带 log 地求解了左右儿子。
*/
#include <bits/stdc++.h>
const int maxm = 35;
const int maxn = 1e5 + 5;
using ll = long long;
ll res;
int n, k, l;
int g[maxn][2];
int f[maxn][maxm];
int a[maxn], t[maxn];
ll dif[maxn], cnt[maxn];
int ask(int l, int r) {
	if (l > r) return 0;
	int k = log(r - l + 1) / log(2.0);
	return (a[f[l][k]] < a[f[r - (1 << k) + 1][k]]) ? f[l][k] : f[r - (1 << k) + 1][k];
}
void bld(int rt, int l, int r) {
	if (rt != l) {
		g[rt][0] = ask(l, rt - 1);
		bld(g[rt][0], l, rt - 1);
	}
	if (rt != r) {
		g[rt][1] = ask(rt + 1, r);
		bld(g[rt][1], rt + 1, r);
	}
	return;
}
// k <= sqrt(lim)
void DFS(int x, int k, int fa) {
	t[x] = (a[x] + k - 1) / k;
	res += t[x] - t[fa];
	for (int i = 0; i < 2; ++i) {
		if (g[x][i])
			DFS(g[x][i], k, x);
	}
	return;
}
// k > sqrt(lim)
void DFS(int x, int fa) {
	++cnt[x];
	--cnt[fa];
	for (int i = 0; i < 2; ++i) {
		if (g[x][i])
			DFS(g[x][i], x);
	}
	int l = k + 1, r;
    // 注意这里 i 的范围判定，如果直接写成 i * i <= k 会少计算一些情况
	for (int i = 1; (i - 1) * (i - 1) < k; ++i) {
		r = l - 1;
		l = (a[x] + i - 1) / i;
		// fprintf(stderr, "%d: [%d, %d] += %d * %d\n", a[x], l, r, cnt[x], i);
		dif[l] += i * cnt[x], dif[r + 1] -= i * cnt[x];
	}
	return;
}
int main() {
#ifdef ONLINE_JUDGE
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
#endif
	std::cin >> n;
	for (int i = 1; i <= n; ++i) {
		std::cin >> a[i];
		f[i][0] = i;
		k = std::max(k, a[i]);
	}
	for (int j = 1; (1 << j) <= n; ++j)
		for (int i = 1; i + (1 << j) - 1 <= n; ++i)
			f[i][j] = (a[f[i][j - 1]] < a[f[i + (1 << (j - 1))][j - 1]]) ? f[i][j - 1] : f[i + (1 << (j - 1))][j - 1];
	int rt = ask(1, n);
	bld(rt, 1, n);
	for (int i = 1; i * i <= k; ++i) {
		res = 0;
		DFS(rt, i, 0);
		std::cout << res << ' ';
		l = i + 1;
	}
	// fputs("\n", stderr);
	DFS(rt, 0);
	std::partial_sum(dif + 1, dif + k + 1, dif + 1);
	for (int i = l; i <= k; ++i)
		std::cout << dif[i] << ' ';
	std::cout << '\n';
	return 0;
}
```

---

## 作者：elbissoPtImaerD (赞：2)

挺 edu 的题。

我们只能着手刻画这个操作的特质：由于每次操作的对象其实是一个极大连通段，所以最小步数和操作次序无关。

尝试按连通性刻画操作：在当前状态下，对全体序列操作一次花费的代价是极大活怪兽的连通段个数。

此时我们对每个怪兽造成的伤害均等，可以只用一个 $x$ 刻画。

怪兽死活的改变点 $x$ 只有 $O(n)$ 个，把这些拎出来暴力修改。

从而可以维护出 $c_i$ 表示当总伤害为 $i$ 时，欲要对每个怪兽各进行一次攻击所花费的代价，注意这是一个和 $k$ 无关的问题，可以做到 $O(n+V)$ 预处理。

至于求解每次询问 $k$，只需暴力求 $\sum\limits_{k|d}c_d$，复杂度调和级数。

[$\color{green}{\checkmark}$](https://codeforces.com/contest/1954/submission/258565445)

---

## 作者：_•́へ•́╬_ (赞：2)

复习整除分块。

## 思路

考虑 P1969。对于某个 $k$，答案就是 $\sum\max(0,\lceil\frac{a_{i+1}}{k}\rceil-\lceil\frac{a_i}{k}\rceil)$。

显然 $\lceil\frac{a_i}{k}\rceil$ 会分成根号段。那么差分累加一下贡献就行了。

注意上取整整除分块的写法。

## code

```cpp
#include<stdio.h>
#define max(x,y) ((x)>(y)?(x):(y))
#define min(x,y) ((x)<(y)?(x):(y))
#define N 100009
int n,a[N],maxn;long long ans[N];
main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;scanf("%d",a+i),maxn=max(maxn,a[i]),++i);
	for(int i=0;i<n;++i)for(int l=1,r;;l=r+1)
	{
		r=min(l<a[i]?(a[i]-1)/((a[i]-1)/l):N,
			l<a[i+1]?(a[i+1]-1)/((a[i+1]-1)/l):N);
		if(r==N)break;
		int x=(a[i+1]-1)/l-max(a[i]-1,0)/l;
		if(x>0)ans[l]+=x,ans[r+1]-=x;
	}
	++ans[0];
	for(int i=1;i<=maxn;printf("%lld ",ans[i]+=ans[i-1]),++i);
}
```

---

## 作者：C_Pos_Princess (赞：2)

# 数论分块

#### 问题

计算形如函数 $H()$ 的式子：

 $$
 H (n) = \sum_{i = 1} ^{n}f(i)*g(\lfloor \frac{n}{i}\rfloor)
 $$
	
    
   注意到，我们可以将 $\frac{n}{i}$ 相同的打包计算，以此降低时间复杂度。
   
   
 #### 结论
 
 对于常数 $n$ ,使得：
 
 $$
 \lfloor \frac{n}{i}\rfloor = \lfloor \frac{n}{j} \rfloor
 $$
 
 其中，满足条件的最大的 $j$ 为 $\lfloor \frac{n}{\lfloor \frac{n}{i} \rfloor} \rfloor$ 。
 
 
 #### 扩展——向上取整
 由于：
 
 $$
 \lceil \frac{n}{i} \rceil = \lfloor \frac{n-1}{i} \rfloor +1
 $$
 
 所以， $n$ 的上取整分块与 $n-1$ 的下取整分块是一样的,即：
 
 $$
 \lceil \frac{n}{i} \rceil 所在块的右端点为 \lfloor \frac{n-1}{\lfloor \frac{n-1}{i} \rfloor} \rfloor
 $$
 
 ps: 一定要注意 $0$ 的情况不符合公式
 
 ### 扩展——二维数论分块
 
 本质上就是多了一个限制条件，保证两个限制条件都能取到即可。

题解：[CF1954E Chain Reaction](https://www.luogu.com.cn/problem/CF1954E)
 
 代码（摘自 oi.wiki）
 ```cpp
#include <algorithm>
#include <iostream>

constexpr int N = 100009;
int n, a[N], maxn;
long long ans[N];

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
    maxn = max(maxn, a[i]);
  }
  for (int i = 0; i < n; ++i)
    for (int l = 1, r;; l = r + 1) {
      r = std::min(l < a[i] ? (a[i] - 1) / ((a[i] - 1) / l) : N,
                   l < a[i + 1] ? (a[i + 1] - 1) / ((a[i + 1] - 1) / l)
                                : N);  // 二维数论分块
      if (r == N) break;
      int x = (a[i + 1] - 1) / l - std::max(a[i] - 1, 0) / l;
      if (x > 0) ans[l] += x, ans[r + 1] -= x;  // 累加贡献
    }
  ++ans[0];  // ⌈a/l⌉=(a-1)/l+1的式子当a=0时不成立，需要修正（就是最初最前面的位置会因为0的存在多减去1）
  for (int i = 1; i <= maxn; ++i)
    cout << (ans[i] += ans[i - 1]) << " \n"[i == maxn];
  return 0;
}
```
完结撒花！！！

---

## 作者：gcx114514 (赞：2)

### 题目分析
我们发现关于每个 $k$ 对整个序列进行一次操作后的结果一定是由若干个连续正整数区间，称一个连续区间为一个连通块，那么我们必须对每个连通块做至少一次操作。考虑在进行一次操作后剩下的元素形成的连通块是怎么样的。可以发现这会使其变成对整个序列进行一次 $2k$ 后的结果（注意，实在进行一次 $k$ 后对每个连通块进行一次操作后）。若第 1 进行 $i$ 操作后所剩下的联通块个数为 $a[i]$ 那么 $i$ 的答案就是 $ans[i]=1+\sum_{j=1}^{ij \leqslant n }a[ij]$。

现在考虑如何求 $a[i]$，其实很简单，我们可以从大到小递推，将权值大于 $i$ 的位置的贡献加入即可。

关于时间复杂度，我们知道在 $n$ 以内 $i$ 的倍数有 $\lfloor \frac{n}{i}\rfloor$ 个，那么就是要求 $\sum_{i=1}^{n}\frac{n}{i}$ 这个式子就是调和级数的一部分，不会的可以上网查 ~~（主要是我不会）~~ ，根据调和级数的知识，我们可以将其近似的看为 $\ln(n)$ 的这样复杂度近似看为 $O(n \log n)$ 的。

### Code
```cpp
#include <bits/stdc++.h> 
#define int long long
using namespace std;
const int Max=1e5+10;
int A[Max],vis[Max],ans[Max],a[Max],pos;
vector<int>dis[Max];

signed main(){
	int n;
	scanf("%lld",&n);
	int z=0;
	for(int i=1;i<=n;++i){
		scanf("%lld",&A[i]);
		z=max(z,A[i]);
		dis[A[i]].push_back(i);
	}
	ans[z]=1;
	for(int i=z-1;i>=1;--i){
		for(int j:dis[i+1]){    //将大于i的数倒序加入 
			if(!vis[j-1]&&!vis[j+1])pos++;
			if(vis[j-1]&&vis[j+1])pos--;
			vis[j]=1;
		}
		a[i]=pos;
		ans[i]=1;
		for(int j=1;j*i<=z;++j){ //统计i对应的答案 
			ans[i]=ans[i]+a[j*i];
		}
	}
	for(int i=1;i<=z;++i){
		printf("%lld ",ans[i]);
	}
	return 0;
}
```

---

## 作者：Alear (赞：1)

[题面传送门](https://www.luogu.com.cn/problem/CF1954E)

发现自己的做法暂时没有出现在题解区，姑且写一篇题解抛砖引玉。

首先考虑固定 $k$ 的做法。当 $n=1$ 时答案显然。假设前 $i-1 (i \gt 1)$ 个怪兽的最小击杀时间已经计算完成，现在将怪兽 $a_i$ 添加到序列末尾，我们发现对 $a_{i-1}$ 造成的伤害也会对 $a_i$ 造成伤害，此时只需要额外计算 $a_i$ 的贡献即可，即产生的贡献为
$$\max(0, \lceil\frac{a_i}{k}\rceil-\lceil\frac{a_{i-1}}{k}\rceil).$$ 

这时候我们发现式子里面产生了一个有趣的取整符号，我们可以使用整除分块同时在 $O(\sqrt n)$ 的时间完成所有 $k$ 的扩展。对于一段连续的 $k$，加上一个数，即需要完成区间加，最后查，使用差分即可。

总时间复杂 $O(n\sqrt n)$ 不是最优解法，但足以通过本题。

code

```cpp
#include<bits/stdc++.h>
#define TLE {int sum=0;for(int i=0;i<1e10;i++)sum+=i;cout<<sum;}
#define int long long
#define endl '\n'
#define rep(i, x, y) for(int i=(x), _=(y);i<=_;i++)
#define rrep(i, x, y) for(int i=(x), _=(y);i>=_;i--)
using namespace std;
const int mod = 998244353;
const double eps = 1e-6;

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

inline int read(){int c;cin>>c;return c;}
inline void read(vi &v){
	for(auto &i: v)
		cin >> i;
}
inline auto readvi(int n){
	vi v(n);
	for(auto &i: v)
		cin >> i;
	return v;
}
inline void readn(int a[], int n){
    for_each(a + 1, a + n + 1, [](int &x){cin>>x;});
}
inline void printn(int a[], int n){
	for_each(a + 1, a + n + 1, [](int &x){
		cout<<x<<' ';
	});
	cout<<endl;
}
template<typename T, typename... Args>
void print(const T& first, const Args&... args) {
    cout << first;
    ((cout << ' ' << args), ...);
    cout << endl;
}
template<typename T, typename... Args>
void eprint(const T& first, const Args&... args) {
	cerr<<'*';
    cerr << first;
    ((cerr << ' ' << args), ...);
    cerr << endl;
}
#define eprintn(a, n) cerr << #a << ' ';\
for(int _=1;_<=n;_++)\
	cerr<<(a)[_]<<' ';\
cerr<<endl;

const int N=1e6 + 20,M=5e3;

int n, m, k;
char out[2][10] = {"No", "Yes"};
int a[N], b[N];
int f[N];

void add(int ql, int qr, int x){
	f[ql] += x;
	f[qr + 1] -= x;
}


signed main(){
	int n = read();
	readn(a, n);
	int mx = *max_element(a + 1, a + n + 1);
	rep(i, 1, mx)
		f[i] = (a[1] + i - 1) / i;
	rrep(i, mx, 2)
		f[i] -= f[i - 1];
	rep(i, 2, n){
		int x = a[i], y = a[i - 1];
		if(x <= y)
			continue;
		x--, y--;
		for(int j = 1, jr; j <= x; j = jr + 1){
			jr = x / (x / j);
			if(j <= y)
				jr = min(y / (y / j), jr);
			add(j, jr, x / j - y / j);
		}
	}
	rep(i, 1, mx)
		f[i] += f[i - 1];
	printn(f, mx);
	
}
```

---

## 作者：zhenghanyun (赞：0)

场上写了一个 $\mathcal{O}(n \sqrt V)$ 的做法，被卡常喜提 $4$ 发罚时。

题目链接：[Link](https://www.luogu.com.cn/problem/CF1954E)

## 思路分析

一个显然的结论是，如果相邻的一段怪兽初始血量均相同，那么把这一段怪兽当成一只怪兽，答案不变。

那么我们可以对相邻的初始血量相同的怪兽进行合并，这样只需考虑 $a_i \ne a_{i - 1}$ 且 $a_i \ne a_{i + 1}$ 的情况。

令 $b_i = \lceil \frac{a_i}{k} \rceil$，表示第 $i$ 头怪兽需要攻击 $b_i$ 次才能使其死亡。

设 $f(l, r)$ 表示区间 $[l, r]$ 内的答案，$pos$ 为 $[l, r]$ 内 $a_i$ 的最小值下标，则有：

$$f(l, r) = \begin{cases} b_l, &l = r \\ f(l + 1, r), &l < r \land pos = l \\ f(l, r - 1), &l < r \land pos = r \\ f(l, pos - 1) + f(pos + 1, r) - b_{pos}, &l < pos < r \end{cases}$$

前三个式子显然成立，最后一个式子的意思是先计算区间 $[l, pos - 1]$ 和 $[pos + 1, r]$ 的答案之和，再去掉两段同时进行操作的次数。

最终答案即为 $f(1, n)$。

类似整除分块的结论，当 $k$ 取遍 $1 \sim \max \limits_{i = 1} ^ n a_i$ 时，$b_i = \lceil \frac{a_i}{k} \rceil$ 最多有 $\mathcal{O}(\sqrt V)$ 种取值，也就是说 $b_i$ 至多改变 $\mathcal{O}(\sqrt V)$ 次。

那么 $b$ 数组总的改变次数不会超过 $\mathcal{O}(n \sqrt V)$。

当 $k = \max \limits_{i = 1} ^ n a_i$ 时，答案显然为 $1$，考虑从大到小枚举 $k$ 的值，并在此过程中修改 $b_i$，同时更新答案。

现在问题转化为如何在修改 $b$ 数组的同时 $\mathcal{O}(1)$ 更新答案。

观察上述 $f$ 的递推式可以发现，当 $b_i \gets b_i + t$ 时：

- 若 $a_{i - 1} < a_i < a_{i + 1}$ 或 $a_{i - 1} > a_i > a_{i + 1}$，答案不变。

- 若 $a_{i - 1} < a_i \land a_i > a_{i + 1}$，答案增加 $t$。

- 若 $a_{i - 1} > a_i \land a_i < a_{i + 1}$，答案减少 $t$。

那么我们只需使用类似整除分块的做法预处理出所有 $b_i$ 更新时 $k$ 的值，即可解决原问题。

有点卡常，但不是很卡，在场上把所有不该开 `long long` 的地方全部换成 `int` 就过了。

## 代码

``` cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 1e5 + 5;

int n, m, cnt = 1, a[N], b[N];

vector <int> vec[N];

ll ans = 1, res[N];

inline void solve() {
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		b[i] = 1;
		m = max(m, a[i]);
		if (a[i] != a[cnt]) {
			a[++cnt] = a[i];
		}
	}
	n = cnt;
	a[n + 1] = 0;
	for (int i = 1; i <= n; ++i) {
		int l = 1, r = 0;
		while (l < a[i]) {
			r = (a[i] - 1) / ((a[i] + l - 1) / l - 1);
			vec[r].emplace_back(i);
			l = r + 1;
		}
	}
	for (int i = m; i >= 1; --i) {
		for (auto j: vec[i]) {
			int t = (a[j] + i - 1) / i;
			if (a[j] > a[j + 1] && a[j] > a[j - 1]) {
				ans += t - b[j];
			} else if (a[j] < a[j + 1] && a[j] < a[j - 1]) {
				ans -= t - b[j];
			}
			b[j] = t;
		}
		res[i] = ans;
	}
	for (int i = 1; i <= m; ++i) {
		cout << res[i] << " ";
	}
}

int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	solve();
	return 0;
}
```

---

## 作者：NATO (赞：0)

提供一种奇怪的思考方式。

**本题解可能使用了一些不必要的东西作为实现手段，仅当是提供一种思考方式即可，并不是很实用。**

### 思路浅析：

首先可以发现最小操作数是假的，因为你考虑我一次操作后全局减去了 $k$，这样全局做了几次之后如有断点必然是确定的，那么断开形成的各个独立段分别都是要操作的，每次操作就相当于是新的独立段的全局减，这样搞显然分裂出的独立段都是固定的，所以就是要你模拟把序列变成 $0$ 的整个过程，问 $k=1,2,...,a_{maxn}$ 时分别的操作次数。

由于当区间分裂时我们就需要分开操作了，这和未分裂前的操作有差异，所以我们应当考虑一个区间在什么时候会变以及需用的操作次数。

考虑我们最先被变成 $0$ 的点是什么点。显然，我们无法知道有多少个这样的点，但全局最小点必然在其中，那么先认为只有全局最小点，继续考虑分裂出的独立段中先变成 $0$ 的点就又是独立段中的最小点......如此往复直到分裂出的段只有一个点。

那么我们根据这个过程想象一颗树，根是全局最小值，儿子是去掉全局最小值后形成的独立段的最小值，儿子的儿子是去掉去掉全局最小值后形成的独立段的最小值后形成的独立段的最小值......

这是什么？这不就是笛卡尔树吗！

那么我们考虑去模拟笛卡尔树的建树过程，设当前点权为 $a_{now}$，父亲为 $a_{fa}$，那么对于一个确定的 $k$，这个点的贡献是好算的，为 $\lceil\frac{a_{now}}{k}\rceil-\lceil\frac{a_{fa}}{k}\rceil$，意义是很鲜明的，即：我这个点在父亲变成 $0$ 后所需要的操作次数，即我作为一个区间的最小值时多少次后被干掉，即我这个区间分裂前需用的操作次数，所有点这个玩意之和显然即为当前这个 $k$ 的答案。

但是我们要求的是 $k=1,2,...,a_{maxn}$ 时的操作次数，暴力枚举 $k$ 加上模拟笛卡尔树就是 $n^2$ 的，怎么办呢？

观察到 $\lceil\frac{a_{now}}{k}\rceil-\lceil\frac{a_{fa}}{k}\rceil$，这样的形式让我们想到了整除分块，向上取整不过就是有余数的情况入到上面罢了，那么我们就考虑在每个点搞整除分块，求出不同的 $k$ 对应的操作次数，由整除分块可知相同的操作次数 $k$ 是连续的，维护一个差分数组，最后扫一遍输出答案即可。

时间复杂度 $O(n\sqrt n)$，纸张笔者不会线性笛卡尔树，就又写了棵萌萌线段树查询区间最小（~~ST 表？笔者表示不如写线段树顺手~~），所以代码极为丑陋，仅做参考。

#### 参考代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define INF 214748364719260817ll
using namespace std;
ll n,a[100005],maxn;
ll ans[100005];
struct tree
{
	ll minn,where;
}tr[400005];
#define ls(id) id*2
#define rs(id) id*2+1
tree merge(tree a,tree b)
{
	tree c;
	c.minn=min(a.minn,b.minn);
	if(c.minn==a.minn)c.where=a.where;
	if(c.minn==b.minn)c.where=b.where;
	return c;
}
void pushup(ll id)
{
	tr[id]=merge(tr[ls(id)],tr[rs(id)]);
}
void build(ll id,ll l,ll r)
{
	if(l==r)
	{
		tr[id].minn=a[l];tr[id].where=l;return;
	}
	ll mid=l+r>>1;
	build(ls(id),l,mid);
	build(rs(id),mid+1,r);
	pushup(id);
}
tree query(ll id,ll l,ll r,ll ml,ll mr)
{
	if(ml<=l&&r<=mr)return tr[id];
	ll mid=l+r>>1;
	if(mr<=mid)return query(ls(id),l,mid,ml,mr);
	if(ml>mid)return query(rs(id),1+mid,r,ml,mr);
	return merge(query(ls(id),l,mid,ml,mr),query(rs(id),1+mid,r,ml,mr));
}
void done(ll l,ll r,ll val)
{
	if(l>r)return;
	ans[l]+=val;ans[r+1]-=val;
}
void dkr(ll l,ll r)
{
	ll add=1;
	tree now=query(1,1,n,l,r);
	if(now.where!=l)--add,dkr(l,now.where-1);
	if(now.where!=r)--add,dkr(now.where+1,r);
	l=1,r=0;
	for(;l<=now.minn;l=r+1)
	{
		r=now.minn/(now.minn/l);
		if(now.minn%r==0)done(l,r-1,add*(now.minn/l+1)),done(r,r,add*(now.minn/l));
		else done(l,r,add*(now.minn/l+1));
	}
	done(now.minn+1,maxn,add);
}
int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n;
	for(ll i=1;i<=n;++i)cin>>a[i],maxn=max(a[i],maxn);
	build(1,1,n);
	dkr(1,n);
	for(ll i=1;i<=maxn;++i)ans[i]+=ans[i-1],cout<<ans[i]<<' ';
}
```

---

## 作者：mRXxy0o0 (赞：0)

比较有趣的一个题。

# 分析

首先考虑只求 $k=1$ 的答案。如果把 $a$ 数组放到坐标轴上（$(i,a_i)$ 为点的坐标），可以理解为 $y$ 轴上有一根水平线，从下往上扫描。我们希望求出该水平线从某个节点的 $a_i$ 上移到下一个节点的 $a_j$ 所花费的代价，设水平线在 $a_i$ 时，高于水平线的点组成了 $x$ 个极大联通段，代价即为 $x(a_j-a_i)$。

推广一下解法，发现对于其他 $k$，一步的代价是类似的，即为 $x(\lceil \frac {a_j} k\rceil-\lceil\frac{a_i}k\rceil)$。可以预处理每个 $y$ 值对应的 $x$，我是用线段树搞的，比较暴力。

暴力实现复杂度为 $O(n^2)$，但是我们可以智慧一点，想办法去保证每一次走一些步，使得 $x>0$，那复杂度就是 $\sum\frac ni=n\ln n$ 了。实现也很简单，强制要求每次走最少的步数，使得 $x=1$，二分出该走到的 $y$ 值，加一加贡献就好了。复杂度约为 $O(n\log^2 n)$。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
const int N=1e5+10,inf=1e9;
int n,a[N],m,c[N];
pii b[N];
struct node{
	int l,r,fl,fr,al,s;
}tr[N<<2];
inline void pushup(int u){
	tr[u].al=tr[u<<1].al|tr[u<<1|1].al;
	tr[u].s=tr[u<<1].s+tr[u<<1|1].s-(tr[u<<1].fr&&tr[u<<1|1].fl);
	tr[u].fl=tr[u<<1].fl,tr[u].fr=tr[u<<1|1].fr;
}
inline void build(int u,int l,int r){
	tr[u]={l,r,1,1,0,1};
	if(l==r) return ;
	int mid=l+r>>1;
	build(u<<1,l,mid),build(u<<1|1,mid+1,r);
}
inline void mdf(int u,int x){
	if(tr[u].l==tr[u].r){
		tr[u].al=1;
		tr[u].fl=tr[u].fr=tr[u].s=0;
		return ;
	}
	int mid=tr[u].l+tr[u].r>>1;
	if(x<=mid) mdf(u<<1,x);
	else mdf(u<<1|1,x);
	pushup(u);
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		scanf("%d",&a[i]);
		b[i]={a[i],i};
		m=max(m,a[i]);
	}
	sort(b+1,b+1+n);
	b[0]={0,0};
	c[0]=1;
	build(1,1,n);
	for(int i=1;i<=n;){
		int j=i;
		while(j<=n&&b[i].first==b[j].first) mdf(1,b[j].second),++j;
//		cout<<i<<" "<<j<<" "<<b[i].first<<" "<<tr[1].s<<"\n";
		c[b[i].first]=tr[1].s;
		i=j;
	}
	for(int i=1;i<=m;++i){
		int v=i,p=1;
		ll ans=0;
		while(p<=n){
			p=lower_bound(b+p,b+1+n,(pii){v,inf})-b;
//			cout<<v<<" "<<p<<" "<<b[p-1].first<<" "<<c[b[p-1].first]<<" \n";
			ans+=c[b[p-1].first];
			v+=i;
		}
		printf("%lld ",ans+1);
	}
	return 0;
}
```

---

## 作者：Day_Tao (赞：0)

感觉严格小于蓝，顶多绿，并且到不了 *2200。~~毕竟是我都能一眼秒然后一发过的题~~。

看见这样的数据范围就比较根号。不难发现在整体减去 $i$ 之后的下一次操作只对 $j\mid i$ 有贡献，贡献为当前极大非负连续子段的数量。所以直接枚举 $j$ 的因子都加上这个贡献。至于这个贡献的计算，还是假设已经将整体减去 $i$ 了（但是并不对 $a$ 数组进行更新），记大于当前 $i$ 的数为 $0$，小于当前数的为 $1$，那么我们找到所有原数组中值为 $i$ 的位置，若这个数两边都为 $0$，那么贡献就 $+1$；若两边都为 $1$，那么贡献就 $-1$，否则贡献不变。这点还是比较显然的。最后注意加上最开始操作一次的贡献，由于保证 $a_i\ge1$，所以对于所有的答案贡献都为 $1$。还有统计答案的时候记得开 `long long`。

时间复杂度 $O(n\sqrt{n})$，但是似乎可以优化成 $O(n\ln n)$。

Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
int n,a[N],cnt,mx;
long long ans[N];
bool fl[N];
vector<int>vec[N];
inline int read()
{
	int x=0,y=1;char c=getchar();
	for(;c<'0'||c>'9';c=getchar())if(c=='-')y=-1;
	for(;c>='0'&&c<='9';c=getchar())x=(x<<3)+(x<<1)+(c^48);
	return x*y;
}
inline void solve()
{
	n=read(),cnt=1;for(int i=1;i<=n;i++)a[i]=read(),mx=max(mx,a[i]),vec[a[i]].push_back(i);
	for(int i=1;i<=mx;i++)ans[i]=1;
	for(int i=1;i<=mx;i++)
	{
		for(int j:vec[i]){fl[j]=1;if(j!=1&j!=n&&!fl[j-1]&&!fl[j+1])cnt++;
			if(n==1||j==1&&fl[j+1]||j==n&&fl[j-1]||fl[j-1]&&fl[j+1])cnt--;}
		for(int j=1;j*j<=i;j++){if(i%j==0){ans[j]+=cnt;if(j*j!=i)ans[i/j]+=cnt;}}
	}
	for(int i=1;i<=mx;i++)printf("%lld ",ans[i]);
	return ;
}
signed main()
{
	int T=1;while(T--) solve();system("pause");return 0;
}
```

---

## 作者：yyz1005 (赞：0)

笑点解析：

![](https://cdn.luogu.com.cn/upload/image_hosting/flcvbwt8.png)

卡常卡 long long 不如 c++20。

---

## 题面

给定 $n$ 个在一排怪物血量从左到右依次为 $a_1,a_2,a_3,\cdots,a_n$。

每秒钟，你可以选择一个活着的怪物，并向它发射一道闪电。闪电对它造成 $k$ 的伤害，也会向左边（朝着减少 $i$ 的方向）和右边（朝着增加 $i$）扩散到活着的怪物身上，对每个怪物造成 $k$ 的伤害。当闪电到达一个死去的怪物或一排的开始或结束时，它就会停止。如果怪物的生命值严格大于 $0$，则认为它是活着的。

请对于 $k=1,2,3\cdots,\max\{a_1,a_2,a_3,\cdots,a_n\}$，给出消灭所有怪物的最小时间。

$1 \le n,a_1,a_2,a_3,\cdots,a_n \le 10^5$。

## SOL

请注意本题解中极大点、极小点与极大值点、极小值点或最大值点、最小值点无关。

首先，称 $\{a_n\}$ 中的极大点（$a_{i-1} < a_i,a_i > a_{i+1}$，也就是极大值点），应当注意到一个极大点被消灭时，他的左右两端的不大于他点也会被消灭（每次波及到极大点的闪电都波及到极大点左右两端的不大于他点）。

那么，只用考虑所有的极大点。

我们考虑两个相邻的极大点 $a_i,a_j$，我们设 $a_{i+1}$ 到 $a_{j-1}$ 之间的最小值为 $a_p=x$。

那么注意到当且仅当 $a_p$ 存活，所有波及到 $a_i$ 或 $a_j$ 的闪电会同时波及 $a_i,a_j$。$(*)$

我们考虑记一个 $S = \sum\limits_{a_i \text{是极大点}}{\lceil \dfrac{a_i}{k} \rceil}$。

那么我们注意到答案小于 $S$ 的原因就是 $(*)$ 处会节省攻击次数。

注意到 $(*)$ 处一个 $a_p$ 可以使 $a_i,a_j$ 共用 $\lceil \dfrac{a_p}{k} \rceil$ 次攻击。

所以记所有这样的 $a_p$ 是极小点（所有极小点都是极小值点，但并不是所有极小值点都是极小点）。

记 $T= \sum\limits_{a_i \text{是极小点}}{\lceil \dfrac{a_i}{k} \rceil} $。

那么答案为 $S-T$。

所以只用对所有极大点与极小点，快速计算其除以 $k$ 向上取整的和。

注意到 $\lceil \dfrac{N}{k} \rceil,k = 1,2,3,\cdots,N = 10^5$ 的数量为 $631$，可以对于所有 $a_i$ 做数论分块。

每次分块得到 $[L,R]$ 表示 $\lceil \dfrac{a_i}{k} \rceil$ 在 $k=L,L+1,L+2,\cdots,R$ 相等，对答案的 $[L,R]$ 区间加（或减）$\lceil \dfrac{a_i}{L} \rceil$ 即可（加是 $T$，减是 $S$）。

所以用一个树状数组维护一下就好。

总体是 $O(n\sqrt n\log n)$。

有点卡常，我是用 c++20 创过去的。

[Code](https://codeforces.com/contest/1954/submission/257680653)

---

