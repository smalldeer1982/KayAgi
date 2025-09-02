# [ABC318F] Octopus

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc318/tasks/abc318_f

数直線上に $ 1 $ 体のタコ型ロボットと $ N $ 個の宝があります。 $ i $ $ (1\leq\ i\leq\ N) $ 個目の宝はそれぞれ座標 $ X_i $ にあります。  
 タコ型ロボットは $ 1 $ つの頭と $ N $ 本の足を持っており、$ i $ 本目の足の長さは $ L_i $ $ (1\leq\ i\leq\ N) $ です。

タコ型ロボットが次のようにして $ N $ 個の宝すべてを掴む事ができるような**整数** $ k $ の個数を求めてください。

- 頭を座標 $ k $ におく。
- $ i=1,2,\ldots,N $ の順に、「頭から距離 $ L_i $ 以下の範囲、すなわち $ k-L_i\leq\ x\leq\ k+L_i $ をみたす座標 $ x $ にまだ掴んでいない宝が存在する場合、そのうちの $ 1 $ つを選んで掴む」ことを繰り返す。

## 说明/提示

### 制約

- $ 1\ \leq\ N\leq\ 200 $
- $ -10^{18}\ \leq\ X_1\ <\ X_2\ <\ \cdots\ <\ X_N\leq\ 10^{18} $
- $ 1\leq\ L_1\leq\ L_2\leq\cdots\leq\ L_N\leq\ 10^{18} $
- 入力はすべて整数
 
### Sample Explanation 1

$ k=-3,-2,-1,2,3,4 $ が条件をみたします。例えば、$ k=-3 $ のときは、次のようにして $ 3 $ 個の宝をすべて掴む事ができます。 - $ 1 $ 本目の足は $ -6\leq\ x\leq\ 0 $ にある宝を掴む事ができる。このうち座標 $ -6 $ にある $ 1 $ 個目の宝を掴む。 - $ 2 $ 本目の足は $ -8\leq\ x\leq\ 2 $ にある宝を掴む事ができる。このうち座標 $ 0 $ にある $ 2 $ 個目の宝を掴む。 - $ 3 $ 本目の足は $ -13\leq\ x\leq\ 7 $ にある宝を掴む事ができる。このうち座標 $ 7 $ にある $ 3 $ 個目の宝を掴む。

### Sample Explanation 2

$ -10^{18} $ 以上 $ 10^{18} $ 以下のすべての整数が $ k $ として条件をみたします。

### Sample Explanation 3

条件をみたす $ k $ は存在しません。

## 样例 #1

### 输入

```
3
-6 0 7
3 5 10```

### 输出

```
6```

## 样例 #2

### 输入

```
1
0
1000000000000000000```

### 输出

```
2000000000000000001```

## 样例 #3

### 输入

```
2
-100 100
1 1```

### 输出

```
0```

# 题解

## 作者：Zelotz (赞：31)

首先考虑如何判断当头部位于 $k_0$ 时是否可以抓住所有 $n$ 个宝物。

显然可以排序后贪心将触手与宝藏配对。

然后考虑怎样的 $k_0$ 作为分界点，即头部位于 $k_0$ 满足条件而头部位于 $k_0+1$ 不满足条件和头部位于 $k_0$ 不满足条件而头部位于 $k_0+1$ 满足条件的所有 $k_0$。

- 头部位于 $k_0$ 满足条件而头部位于 $k_0+1$ 不满足条件

在这种情况下，一定有这样的 $i,j$ 满足 $k_0-L_j\le x_i \le k_0+L_j$ 且 $k_0+1-L_j >x_i$ 或 $k_0+1+L_j < x_i$。

解不等式得 $k_0=x_i+L_j$。

- 头部位于 $k_0$ 不满足条件而头部位于 $k_0+1$ 满足条件

在这种情况下，一定有这样的 $i,j$ 满足 $k_0+1-L_j\le x_i \le k_0+1+L_j$ 且 $k_0-L_j >x_i$ 或 $k_0+L_j < x_i$。

解不等式得 $k_0=x_i-L_j-1$。

至此，我们找出了所有分界点，所以相邻分界点内的点一定相同，即将所有分界点按升序排序后放入 $S$ 后，当 $k_0=S_i$ 满足条件时，所有 $S_{i-1}+1\le k_0 \le S_i$ 的 $k_0$ 均满足条件。

时间复杂度 $\mathcal O(N^3 \log n)$。

```cpp
const int N = 205;
#define int ll
int n, x[N], l[N], s[N * N << 1], ans;
bool chk(int k)
{
	priority_queue <int> q;
	R(i, 1, n) q.push(abs(x[i] - k));
	R(i, 1, n)
	{
		if (q.top() > l[i]) return false;
		q.pop();
	}
	return true;
}
signed main() 
{
	cin >> n;
	R(i, 1, n) cin >> x[i];
	R(i, 1, n) cin >> l[i];
	sort(l + 1, l + n + 1, greater <int> ());
	int tot = 0;
	R(i, 1, n)
	{
		R(j, 1, n)
		{
			s[++tot] = x[i] - l[j] - 1;
			s[++tot] = x[i] + l[j];
		}
	}
	sort(s + 1, s + tot + 1);
	R(i, 2, tot) 
	{
		if (chk(s[i])) ans += s[i] - s[i - 1];
	}
	cout << ans << endl;
    return 0;
}
```



---

## 作者：xieyikai2333 (赞：10)

- [题目传送门-洛谷](https://www.luogu.com.cn/problem/AT_abc318_f)

- [题目传送门-AtCoder](https://atcoder.jp/contests/abc318/tasks/abc318_f)

---

## 0x00 闲话

- 赛时写了 ABCDEG 唯独没写 F，补一篇题解。

- 这是一篇似乎和其他题解思路不一样的题解。（可能是我没理解其他题解导致我自以为如此。）

---

## 0x01 解题思路

### 引入

先来看一个子问题：已知机器人的位置 $p$，询问是否可以拿到所有物品。

- 显然可以贪心，将物品按 $|x_i-p|$（即机器人到物品的距离）排序，显然距离最近的我们用最短的触手拿，次近的用第二短的拿，以此类推判断是否每个都可以拿即可。

- 证明：较长的触手一定比较短的更有用（可以够到的更多），所以尽可能先用短的；而如果发现排序后有一个触手拿不到对应的物品，那它一定拿不到之后更远的物品，所以可以直接判断不可行。

### 正题

我们尝试将原问题向子问题转化，发现一个问题：机器人到物品的距离在变化，我们无法判断排序后的物品序列长什么样。

但是，当机器人在数轴上从负无穷向正无穷移动时，不同的物品序列只有 $\Theta(N^2)$ 个。

- 证明：考虑将数轴在 $p$ 左边的部分向右折叠，形成的以 $p$ 为端点的射线上即为按照距离排好序的物品序列。这个序列发生变化当且仅当 $p$ 移动时两个物品重合。所以枚举物品两两重合时的情况即可得到 $\Theta(N^2)$ 种情况。

于是我们枚举物品两两重合时 $p$ 的位置（下取整）并排序成一个 $P$ 序列，至此时间复杂度 $\Theta(N^2 \log (N^2))$

排好序以后，对于每一对 $P_i,P_{i+1}$，$p$ 在区间 $(P_{i},P_{i+1}]$ 中时我们有相同的物品序列，求出这个物品序列。

- 注意：由于之前计算 $P$ 序列时，我们进行了下取整，所以区间是左开右闭的。又因为区间是左开右闭的，所以两个物品重合的情况可能出现在右端点上，所以两个物品重合时我们应该让原位置在左半部分的物品排在前面。

现在我们已经有了一个确定的物品序列，也就是说，我们已经知道了每一个触手该去抓哪个物品了。

接下来我们进一步确定 $p$ 的范围。（这里用到的 $x$ 数组是已经排好序的物品序列。）

1. 大前提： $p \in (P_{i},P_{i+1}]$；
2. 对于每个在 $p$ 左边的物品，要求 $p-x_i\le l_i$，即 $p \in (-\infty,x_i+l_i]$；
2. 对于每个在 $p$ 右边的物品，要求 $x_i-p\le l_i$，即 $p \in [x_i-l_i,+\infty)$。

对上述区间取交集即为当前物品序列对应的 $p$ 的取值范围。

对于每个物品序列，其对应的 $p$ 的取值范围的并集即为最终 $p$ 的取值范围。

- 最终时间复杂度：$\Theta(N^3)$。

---

## 0x02 代码实现

- 前面没完全看懂的可以看看代码，很短很好理解。

- 注意：若求物品序列时使用 $\operatorname{std::sort}$ 函数，时间复杂度为 $\Theta(N^3 \log N)$，可以通过；但是我们可以用二路归并的思想排序做到 $\Theta(N^3)$。

- [CODE](https://atcoder.jp/contests/abc318/submissions/45277386)（喜报：编译一遍过，样例一遍过，提交一遍 AC）


---

## 作者：taozhiming (赞：5)

### 题意：

在一条数线上有一个章鱼形机器人和 $N$ 个宝物。第 $i$ 个宝物 $(1\leq i\leq N)$ 位于坐标 $X_i$ 处。
机器人有一个头和 $N$ 条腿， $i$ 条腿 $(1\leq i\leq N)$ 的长度为 $L_i$。

求机器人能抓住所有 $N$ 个宝物的**整数** $k$ 的个数如下。

- 将头部置于坐标 $k$ 处。
- 依次对 $i=1,2,\ldots,N$ 重复以下步骤：如果在距离头部 $L_i$ 的距离内，即在满足 $k-L_i\leq x\leq k+L_i$ 的坐标 $x$ 处，有一件宝物尚未被抓取，则选择其中一件宝物并抓取。

### 分析：

先考虑如果固定 $k$ 怎么判断，直接贪心的从大到小排序到 $k$ 的距离和腿的距离，让其一一匹配即可。

可以发现一个性质，如果 $k$ 出现在 $[l,r]$ 中，前提是其中没有任何一条腿正好碰到某一个宝藏，（正好碰到的意思是这个宝藏到 $k$ 的距离等于腿的长度），那么对于任意的 $i,j\in[l,r]$，如果 $i$ 作为 $k$ 合法，那么 $j$ 作为 $k$ 也合法。

接下来证明这个结论：如果 $i$ 能触摸到宝藏 $j$ ，那么不管 $k$ 在 $[l,r]$ 的任意一个位置，$i$ 都能触摸到 $j$。（其实这个结论是可以打表打出来的）

考虑反证：如果一个点合法，说明每一条腿的长度至少比和他匹配的宝藏的距离大于 $1$ ，那么如果出现 $i$ 不能摸到 $j$ ，那么说明在左右移动的过程中，有一个 $i$ 他摸不到宝藏了，从能到不能，那么一定有一个边界导致 $i$ 刚好摸到 $j$ ，与前提相反，所以不会出现这种情况。

接下来直接钦定某一个宝藏是由那一条腿碰到的，这样会有 $O(n^2)$ 个 $k$ ，把他们分成了 $O(n^2)$ 段区间。

只要在每一段随便选一个数判断合不合法即可，复杂度 $O(n^3logn)$ 可过。

### 代码：

[Code](https://www.cnblogs.com/taozhiming/articles/17676127.html)（翻到 $F$ 题下面即可看到。

---

## 作者：Creeper_l (赞：4)

## 前言

赛时只做到了 E 题，赛后才来补的 F 题，还没做出来，看来还是我太菜了。看了题解过后感觉这道题的思路特别巧妙，于是就来写了这篇题解。

## 题意

简述一下题意。

有 $n$ 个宝藏位置分别在 $a_{i}$，另外有一只章鱼有 $n$ 条触手，每条触手的长度为 $b_{i}$。

求有多少个点 $k$ 满足：章鱼站在点 $k$ 的时候可以用触手抓到所有宝藏，且每个触手只能抓一个宝藏。

数据范围：$n\le200,a_{i},b_{i}\le10^{18}$。

## 思路

因为宝藏位置的范围很大，所以不可能枚举所有位置，需要优化。我们可以把这些位置分成几个不同的区间，对于每个区间去计算答案，这样效率更高。

首先考虑如何判断 $k$ 这一个点是否合法。首先把点 $k$ 到每个宝藏的距离算出来，然后升序排一遍序。然后和 $b$ 数组进行比较，如果有一位不合法（触手的长度不够）的话，那么点 $k$ 就是不合法的；否则点 $k$ 是合法的。时间复杂度 $O(n \log n)$。

然后我们考虑如何计算区间中的答案。考虑一个区间 $l$ 到 $r$ 满足 $l$ 可以刚好够到一个宝藏，$r$ 也可以刚好够到一个宝藏，但是 $l+1$ 到 $r-1$ 中间没有一个点能刚好够到一个宝藏。那么只要 $l+1$ 是合法的，那么 $l+1$ 到 $r-1$ 中间的这些数也一定是合法的。

证明：因为 $l$ 可以刚好够到一个宝藏，$r$ 也可以刚好够到一个宝藏，$l+1$ 到 $r-1$ 中没有一个点能够刚刚好够到宝藏。我们又知道从合法（触手长度大于等于离宝藏的距离）到不合法（触手长度小于离宝藏的距离）这个过程中一定会经过一个点能够刚刚好够到宝藏（触手长度等于离宝藏的距离），所以 $l+1$ 到 $r-1$ 中一定没有不合法的点。对于 $l$ 点和 $r$ 点，单独判断一下是否合法，合法的话也加到答案中就行了。

这里 $l$ 和 $r$ 的计算方式是 $a_{i}-b_{j}$ 和 $a_{i}+b_{j}$，即每一个刚好可以够到一个宝藏的点，记得排序过后还要去重。这样的点的个数是 $O(n^{2})$ 的，因为枚举了 $i$ 和 $j$。而 Check 的时间复杂度是 $O(n \log n)$，所以总时间复杂度 $O(n^{3} \log n)$，可以通过。 

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define inf 0x3f
#define inf_db 127
#define ls id << 1
#define rs id << 1 | 1
#define register re
#define endl '\n'
typedef pair <int,int> pii;
const int MAXN = 2e3 + 10;
int n,a[MAXN],b[MAXN],p[MAXN * MAXN],cnt,tmp[MAXN],ans;
inline bool Check(int x)
{
	for(int i = 1;i <= n;i++) tmp[i] = abs(x - a[i]);
	sort(tmp + 1,tmp + n + 1);
	for(int i = 1;i <= n;i++) if(b[i] < tmp[i]) return false;
	return true;
}
signed main()
{
	cin >> n;
	for(int i = 1;i <= n;i++) cin >> a[i];
	for(int i = 1;i <= n;i++) cin >> b[i];
	for(int i = 1;i <= n;i++) for(int j = 1;j <= n;j++) p[++cnt] = a[i] - b[j],p[++cnt] = a[i] + b[j];
	sort(p + 1,p + cnt + 1);
	cnt = unique(p + 1,p + cnt + 1) - p - 1; 
	for(int i = 1;i < cnt;i++) if(Check(p[i] + 1)) ans += (p[i + 1] - p[i] - 1);
	for(int i = 1;i <= cnt;i++) if(Check(p[i])) ans++;
	cout << ans;
	return 0; 
}
```


---

## 作者：Xy_top (赞：3)

赛时想到了对 $n^2$ 种状态进行分类，但是判断有没有解，我选择二分图就 T 了。。。

只要再多想一步就能做出来了，章鱼的位置为 $l\cdots r$，$l\cdots r$ 中每个触手能碰到哪个宝藏的状态是相同的，此时如果在位置 $l$ 能摸到所有宝藏，那在位置 $r$ 也能，$l$ $r$ 中任意一点也能。

怎么证明呢？可以用二分图来理解。如果 $l$ 可以，那么就说明一定存在一组合法的二分图的解，而 $l$ $r$ 位置的二分图形态一样，所以得证。

然后这么简单的题我没做出来，我是什么彩笔，就差最后一步没想到。

看来还是太不会猜结论了，附上很短的代码：

```cpp
#include <bits/stdc++.h>
#define int long long
#define For(i, a, b) for (int i = (a); i <= (b); i ++)
#define foR(i, a, b) for (int i = (a); i >= (b); i --)
using namespace std;
int n, ans, cnt;
int x[205], l[205], t[205];
vector <int> v;
bool check (int loc) {
	cnt = 0;
	For (i, 1, n) t[++ cnt] = abs (x[i] - loc);
	sort (t + 1, t + cnt + 1);
	For (i, 1, cnt) if (t[i] > l[i]) return false;
	return true;
}
void solve () {
	cin >> n;
	For (i, 1, n) cin >> x[i];
	For (i, 1, n) cin >> l[i];
	sort (l + 1, l + n + 1);
	For (i, 1, n) {
		For (j, 1, n) {
			v.push_back (x[i] - l[j]);
			v.push_back (x[i] + l[j] + 1);
		}
	}
	sort (v.begin (), v.end () );
	For (i, 0, v.size () - 2) if (check (v[i]) ) ans += v[i + 1] - v[i];
	cout << ans;
}
signed main () {
	ios :: sync_with_stdio (false);
	int _ = 1;
//	cin >> _;
	while (_ --) {
		solve ();
		cout << '\n';
	}
	return 0;
}
```


---

## 作者：cosf (赞：2)

## [ABC318F](https://atcoder.jp/contests/abc318/tasks/abc318_f) [章鱼](https://www.luogu.com.cn/problem/AT_abc318_f)

题目就不翻译了，~~毕竟我语文不行。~~

## 思路

可以发现，良心的出题人已经把 $X$ 和 $L$ 都排好序了。

容易想到，这题应当用贪心。我们肯定想要用长的 $L$ 去拿离得远的 $X$。如果连最长的 $L$，也就是 $L_N$，都拿不到离得最远的 $X$ 的话，那这个 $k$ 肯定是不符合要求的。那么层层递推之后，可以得出：

我们假设根据 $X_i$ 到 $k$ 的距离从小到大排序，得到 $S_1, \dots S_N$ 的话，当前这个 $k$ 满足要求的充要条件就是 $S_i - L_i \le j \le S_i + L_i, \forall 1 \le i \le N$。

这个时候，我们可以发现，我们可以用区间并的方式得到哪一些 $k$ 是满足要求的。例如说，在 $k \le X_1$ 时，排完序的 $S$ 和 $X$ 时一模一样的。又比如说当 $X_1 \lt k \le \lfloor\frac{X_1 + X_2}{2}\rfloor$ 时，此时的 $S$ 和 $X$ 还是完全一样。

也就是说，从 `LLONG_MIN` 到 `LLONG_MAX` 这个大区间可以划分成很多个小区间（默认左开右闭），使得每一个区间内的 $k$ 对应的 $S$ 都是一样的。

那么只要我们得到了这些区间的断点，我们就可以统计答案了。

下面的代码是除了计算断点的其他部分。

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

#define MAXN 205

using ll = long long;

int n;

ll x[MAXN], l[MAXN];

ll s[MAXN];

vector<ll> pos;

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> x[i];
    }
    for (int i = 1; i <= n; i++)
    {
        cin >> l[i];
    }
    pos.push_back(LLONG_MIN);
    pos.push_back(LLONG_MAX);

    /*
     * 这一段处理断点（省略了）
     * 不过 LLONG_MIN 和 LLONG_MAX 是不能省略的
     */

    sort(pos.begin(), pos.end());
    int len = unique(pos.begin(), pos.end()) - pos.begin();
    ll res = 0;
    for (int i = 1; i < len; i++)
    {
        int p = lower_bound(x + 1, x + n + 1, pos[i]) - x - 1;
        int le = p, ri = p + 1, ct = 0;
        while (le != 0 || ri != n + 1)
        {
            if (le == 0)
            {
                s[++ct] = x[ri++];
            }
            else if (ri == n + 1)
            {
                s[++ct] = x[le--];
            }
            else if (pos[i] - x[le] < x[ri] - pos[i])
            {
                s[++ct] = x[le--];
            }
            else
            {
                s[++ct] = x[ri++];
            }
        }
        ll lef = pos[i - 1] + 1;
        ll rig = pos[i];
        for (int j = 1; j <= n; j++)
        {
            lef = max(lef, s[j] - l[j]);
            rig = min(rig, s[j] + l[j]);
            if (lef > rig)
            {
                break;
            }
        }
        if (lef <= rig)
        {
            res += (rig - lef + 1);
        }
    }
    cout << res << endl;
    return 0;
}

```

---

显而易见，一套“可行”的断点就是 $\{\lfloor\frac{X_i + X_j}{2}\rfloor|1 \le i \lt j \le N\}$。因为，经过 $\lfloor\frac{X_i + X_j}{2}\rfloor$ 这一个断点，$X_i$ 和 $X_j$ 在 $S$ 中的位置会发生改变。

这一套断点对应的代码是：

```cpp
    for (int i = 1; i < n; i++)
    {
        for (int j = i + 1; j <= n; j++)
        {
            pos.push_back((x[i] + x[j]) / 2);
        }
    }
```

这个时候可以恭喜你，获得了 $0$ 分的好成绩（WA 了 11 个点）。至于为什么，我也不太清楚。

不过，我们可以发现，如果存在 $1 \le i, j \le N, 1 \le l \lt N$，使得 $k$ 到 $X_i$ 和 $X_j$ 的距离均在 $L_l$ 到 $L_{l + 1}$ 之间，那么 $X_i$ 和 $X_j$ 在 $S$ 中的顺序其实是不重要的。

根据这个思路，我们可以得到这一套断点：$\{X_i \pm L_j | 1 \le i, j \le N\}$。

对应的代码是：

```cpp
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            pos.push_back(x[i] - l[j]);
            pos.push_back(x[i] + l[j]);
        }
    }
```

这样就可以得到满分的好成绩了。

总共的时间复杂度是 $O(n^2\log(n^2) + n^2\log n + n^3)$。（$n$ 仅用于复杂度，量级与 $N$ 相同）

---

下面一段是关于复杂度的闲话。

如果用我这个思路来做题的话（加上一些优化），这道题的时间复杂度是应该不会低于 $O(n^3)$ 的。

这是因为，对于所有的 $k$，$X$ 与 $L$ 的配对是有 $O(n^2)$ 种方法的。$k$ 从 `LLONG_MIN` 取到 `LLONG_MAX` 时，每一个 $X_i$ 会从右边的第 $i$ 个逐步跨越到左边第 $(N - i + 1)$ 个，历经 $N - 1$ 次 排名的变化。而对于不同的 $X$，它们之间的变化的顺序没有必然的联系，也就是说，它们的排名只少会有 $\frac{N(N-1)}{2}$ 次改变，量级为 $O(n^2)$。而对于每一种情况，都至少用 $O(n)$ 的时间来做区间并。总共的时间是 $O(n^3)$。


---

## 作者：zhongpeilin (赞：1)

## 题目大意：
有 $N$ 个宝藏，位置分别在 $a_{1}, a_{2}, \dots a_{n}$。还有只 `1` 个头，$N$ 个触角的章鱼，触角长度分别为 $L_{1}, L_{2}, L_{3} \dots L_{N}$。如果章鱼在 $x$， 宝藏在 $y$，那么一个长度至少为 $\operatorname{abs}(x-y)$ 的长度的触角才能抓住宝藏，每个触角只能抓一个宝藏。现在求有多少个位置使得每个宝藏都可以同时被章鱼抓住？

## 解题思路：
我们先不着急来直接想正解，可以先来思考一下如何在已知章鱼头在 $k$ 的条件下快速的算一下章鱼能不能抓住所有宝藏。那么对于一个在 $a_{i}$ 位置的宝藏，他的值相当于 $\operatorname{abs}(k-a_{i})$。而章鱼的触角和宝藏数量一样，则将 $\operatorname{abs}(k-a_{i})$ 和 $L_{i}$ 分别从小到大排序，来判断是否 $\operatorname{abs}(k-a_{i}) \leq L_{i}$。如果全部的 $i$ 都满足的话，那么章鱼可以抓到所有宝藏，否则不行。  
接下来我们来考虑如何确定有多少个 $k$ 满足章鱼可以抓到所有宝藏。  
因为位置个数是 $10^{18}$，**但发现，如果一个位置 $x$，满足：$x+1$, $x+2$， $x + 3$ ... $x + len - 1$ 都没有形如 $a_{i}+L_{j}$ 或者 $a_{i} - L_{j}$ 的位置，那么如果 $x$ 这里可以抓住所有宝藏，那么 $x \sim x + len$ 都可以抓住所有宝藏**！而这些形如 $a_{i}+L_{j}$ 或者 $a_{i} - L_{j}$ 的位置只有 $O(n^2)$ 个，而我们判断只需要 $O(n \log n)$。所以我们只需要将这些 $a_{i}+L_{j}$ 和 $a_{i} - L_{j}$ 排一下序，然后对于每一个$a_{i}+L_{j}$ 和 $a_{i} - L_{j}$ 的点，算一下答案即可。$O(n^3 \log n)$

## 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

int n, a[205], b[205], hd;
vector<int> vec;

bool cmp(int x, int y){
	return abs(hd - x) < abs(hd - y);
}
signed main(){
	ios::sync_with_stdio(false);
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> a[i];
	for(int i = 1; i <= n; i++) cin >> b[i];
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++){
			vec.push_back(a[i] - b[j] - 1); //因为直接用a[i]-b[j]会算重，但a[i]-b[j]-1就不会
			vec.push_back(a[i] + b[j]);
		}
	}
	sort(vec.begin(), vec.end());
	
	int ans = 0;
	for(int i = 1; i < vec.size(); i++){
		hd = vec[i];
		sort(a + 1, a + n + 1, cmp);
		
		bool flag = true;
		for(int j = 1; j <= n; j++){
			if(abs(hd - a[j]) > b[j]) flag = false;
		}
		ans += flag * (vec[i] - vec[i - 1]);
	}
	cout << ans << endl;
	return 0;
}

---

## 作者：MoyunAllgorithm (赞：1)

# 题意

有 $N$ 个宝藏。有一个章鱼机器人有 $N$ 个触手，第 $i$ 个触手可以够到机器人的位置 $k$ 左右 $l_i$ 距离范围内的一个宝藏（触手长度升序）。请问有多少个位置 $k$ 满足机器人可以够到所有宝藏。

$N \le 200$

# 分析

首先，数据范围较小，通常是 dp 或者需要枚举大量情况。不如考虑枚举大量情况。

第一个问题是，假设我们知道机器人的位置 $k$，如何判断它可以够到所有宝藏呢？非常简单，我们把宝藏和 $k$ 的距离从小到大排序，这样第 $i$ 个触手被分配第 $i$ 个宝藏，如果够不到就不行。容易发现时间复杂度是 $O(N \log N)$。

假设我们枚举所有位置，那时间复杂度是 $O(\max(x_i)N \log N)$，而第一个东西是 $10^{18}$ 级别的，不行。但是，你会发现：**很多时候，一个 $k$ 时的触手分配情况和它相邻的位置的触手分配情况相同。** 那什么时候触手分配情况会变化？那就是当存在一个宝藏，在位置 $k$ 时恰好在某个触手的范围边缘。这样当 $k$ 移动一格，它就会离开触手范围，导致触手分配情况变化。

那也就是说，我们存下所有满足以下条件的位置 $k$：

- 存在 $(i,j)$，满足 $x_i=k + l_j$ 或 $x_i = k -  l_j$。

我们将这些位置排序后形成一个个区间。你会发现，区间的数量是 $N^2$ 量级。枚举这些区间，它们的触手分配情况相同，依次用上面的方法判断是否合法即可。为了保险，你可以单独判断区间端点。时间复杂度为 $O(N^3 \log N)$。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=205,MAXM=80005;
int N,M;
int x[MAXN],dis[MAXN],l[MAXN];
int pos[MAXM];
int cnt[MAXN];
int ans=0;
bool Check(int k)
{
	for(int i=1;i<=N;i++) dis[i]=abs(x[i]-k);
	sort(dis+1,dis+N+1);
	for(int i=1;i<=N;i++) if(dis[i]>l[i]) return 0;
   	//也就是上面说的按位置排序依次分配
	return 1;
}
signed main()
{
	scanf("%lld",&N);
	for(int i=1;i<=N;i++) scanf("%lld",&x[i]);
	for(int i=1;i<=N;i++) scanf("%lld",&l[i]);
	for(int i=1;i<=N;i++)
	{
		for(int j=1;j<=N;j++)
		{
			pos[++M]=x[i]-l[j];
			pos[++M]=x[i]+l[j];
		}
	}
    //找到所有触手分配情况的变化点
    sort(pos+1,pos+M+1);
	M=unique(pos+1,pos+M+1)-pos-1;//去重更方便
	for(int i=1;i<=M;i++)
	{
		ans+=Check(pos[i]);／／首先判断端点是否可行
		if(i<M&&pos[i+1]!=pos[i]+1) ans+=(pos[i+1]-pos[i]-1)*Check(pos[i]+1);
        ／／判断pos[i]和pos[i+1]构成的开区间是否可行。注意：若pos[i]=pos[i+1]-1，那该开区间无整点，必须跳过否则会算重	}
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：Register_int (赞：1)

[Over all](/blog/const1e7/abc318-solution)

先来考虑位置固定时怎么判断是否满足要求。此时显然可以排序后贪心将触手与宝藏配对，能全匹配就有解。

接下来怎么办？考虑把所有宝藏与所有触手**任意配对**的区间端点都存起来，同时存下端点左右两侧的点。这样，当一个点与上一个点均满足要求时，这两个点间的所有点就都满足要求，直接计算即可。时间复杂度 $O(n^3\log n)$。

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 2e2 + 10;
const ll inf = 0x3f3f3f3f3f3f3f3fll;

int n; ll a[MAXN], b[MAXN], t[MAXN];

inline 
ll calc(ll x) {
	for (int i = 1; i <= n; i++) t[i] = abs(a[i] - x);
	sort(t + 1, t + n + 1); ll res = 0;
	for (int i = 1; i <= n; i++) if (b[i] >= t[res + 1]) res++;
	return res;
}

set<ll> v;

int main() {
	scanf("%d", &n), v.insert(-inf), v.insert(inf);
	for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	for (int i = 1; i <= n; i++) scanf("%lld", &b[i]);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			ll x = a[i] + b[j]; v.insert(x - 1), v.insert(x), v.insert(x + 1);
			x = a[i] - b[j]; v.insert(x - 1), v.insert(x), v.insert(x + 1);
		}
	}
	ll ans = 0, lst = -inf - 1;
	for (ll i : v) {
		if (lst == -inf - 1) { lst = i; continue; }
		if (calc(lst) == n && calc(i) == n) ans += i - lst - 1; lst = i;
	}
	for (ll i : v) if (calc(i) == n) ans++;
	printf("%lld", ans);
}
```

---

## 作者：梦应归于何处 (赞：1)

### 题目大意

在一条数线上有一个章鱼形机器人和 $N$ 个宝物。第 $i$ 个宝物 $(1\leq i\leq N)$ 位于坐标 $X_i$ 处。
机器人有一个头和 $N$ 条腿。$i$ 条腿 $(1\leq i\leq N)$ 的长度为 $L_i$。

求机器人能抓住所有 $N$ 个宝物的整数 $k$ 的个数如下。

- 将头部置于坐标 $k$ 处。
- 依次对 $i=1,2,\ldots,N$ 重复以下步骤：如果在距离头部 $L_i$ 的距离内，即在满足 $k-L_i\leq x\leq k+L_i$ 的坐标 $x$ 处，有一件宝物尚未被抓取，则选择其中一件宝物并抓取。

### 思路

首先想暴力，枚举每一个点判断行不行？一看数据范围就直接把这个想法放弃了，不抱有任何希望。

进入正题。我们可以把每个宝藏用每个触手拿它的左边界和右边界给处理出来，时间复杂度：$O(N^2)$。看起来应该不会超时。我们在把这些数放到一个数组中排一遍序。然后我们就去枚举这些点。去判断他们行不行。

怎么判断行不行可以看代码，很简单，一看就懂了。

### 代码

~~~cpp
#include <bits/stdc++.h>
#define TNTMAX INT_MAX
#define db double
#define ll long long
#define ex exit(0);
#define endl "\n"
#define inl inline
#define null NULL
using namespace std;
ll x[300], l[300];
vector<ll> g;
int main() {
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	ll n;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> x[i];
	}
	for (int i = 1; i <= n; i++) {
		cin >> l[i];
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			g.push_back(x[i] + l[j] + 1);
			g.push_back(x[i] - l[j]);
		}
	}
	sort(g.begin(), g.end());
	g.erase(unique(g.begin(), g.end()), g.end());
	ll ans = 0, len = g.size() - 1;
	for (int k = 0; k <= len ; k++) {
		ll p = g[k];
		vector<ll> v;
		for (int i = 1; i <= n; i++) {
			v.push_back(abs(p - x[i]));
		}
		sort(v.begin(), v.end());
		bool flag = 1;
		for (int i = 1; i <= n; i++) {
			if (l[i] < v[i - 1]) {
				flag = 0;
				break;
			}
		}
		if (flag) {
			ans += g[k + 1] - g[k];
		}
	}
	cout << ans;
	return 0;
}
~~~

[洛谷AC记录](https://www.luogu.com.cn/record/123718549)

[AT上的AC记录（代码也可以在这里看）](https://atcoder.jp/contests/abc318/submissions/45219460)

---

