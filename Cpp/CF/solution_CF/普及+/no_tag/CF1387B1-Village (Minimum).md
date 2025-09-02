# Village (Minimum)

## 题目描述

### 题意

[最大值版本](https://www.luogu.com.cn/problem/CF1387B2)

村里 $n$ 个房子构成了一个 $n$ 点 $n-1$ 条边的**树**结构（下标从 $1$ 开始），每条边长度均为 $1$。一开始每个房子里分别有一个村民。

现在所有村民都需要搬家（改变自己所在的点），搬家后依然需要满足每个房子里**有且只有一个**村民。也就是说，如果原本位于点 $i$ 的村民搬到了点 $v_i$，那么应当满足：

- 对于任意点 $i$，有 $i \neq v_i$。

- 对于任意两个不同的点 $i$ 与 $j$，有 $v_i \neq v_j$。

村民 $i$ 搬家的花费是点 $i$ 到点 $v_i$ 的树上距离（即树上二点间相隔的边数），总花费为所有村民花费之和。求总花费的**最小值**及其方案。

## 说明/提示

- $2 \leq n \leq 10^5$

- $1 \leq a,b \leq n$

## 样例 #1

### 输入

```
4
1 2
2 3
3 4```

### 输出

```
4
2 1 4 3```

## 样例 #2

### 输入

```
7
4 2
5 7
3 4
6 3
1 3
4 5```

### 输出

```
8
3 4 6 2 7 1 5```

# 题解

## 作者：Tarsal (赞：13)

## CF1387B1 题解

### 题目大意

给你一棵树，你可以把所有节点重排，不能回到原来的位置，移动一个点从 $a$ 到 $b$ 的代价是 $2$ 点之间的边数。

### 题解

贪心的思路很显然，因为要总移动最小，那么一个点肯定只会和自己相邻或者隔2个点的点连边。

接下来考虑对于一个节点，他有若干的子节点，那么他会有一个子节点和他互换，其他的子节点相互互换。

但是这个的奇偶之类的细节很难处理。麻烦的死。

那可以换一种思路去考虑，你考虑先把每个节点第一次遍历的子节点和他互换，并用 $flag[]$ 标记上。

最后从 $1 \to n$ 跑一遍，让所有的子节点围成一个环，不让他们彼此互换，把他们围成一个环就很好处理的，这个地方一看代码就懂了。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
// #define int long long
#define Rep(x, a, b) for(int x = a; x <= b; ++ x)
#define Dep(x, a, b) for(int x = a; x >= b; -- x)
#define Next(i, x) for(int i = head[x]; i; i = e[i].nxt)
int read() {
    char c = getchar(); int f = 1, x = 0;
    while(c < '0' || c > '9') { if(c == '-') f = -1; c = getchar(); }
    while(c >= '0' && c <= '9') { x = x * 10 + c - '0'; c = getchar(); }
    return x * f;
}
const int maxn = 1e5 + 10;
int head[maxn], cnt, flag[maxn];
struct node { int to, nxt; } e[maxn << 1];
void add(int x, int y) { e[++ cnt] = (node) {y, head[x]}; head[x] = cnt; }
void Dfs(int x, int fa) {
    Next(i, x) {
        int v = e[i].to;
        if(v == fa) continue ;
        Dfs(v, x);
        if(!flag[x] && !flag[v]) { flag[x] = v, flag[v] = x;}
    }
}
int main() {
    int n = read(), ans = 0;
    Rep(i, 2, n) { int u = read(), v = read(); add(u, v), add(v, u); }
    Dfs(1, 0);
    Rep(i, 1, n) {
        if(flag[i]) { ++ ans; continue; }
        int tmp = e[head[i]].to;
        flag[i] = flag[tmp];
        flag[tmp] = i; ans += 2;
    }
    printf("%d\n", ans);
    Rep(i, 1, n) printf("%d ", flag[i]);
    return 0;
}
```

---

## 作者：Tx_Lcy (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF1387B1)

一种树形 $\rm DP$ 做法，模拟赛时想到的，很适合像我这样没有脑子的选手写。

## 思路

首先，显然的，对于一颗 $n$ 个节点的树，我们一定可以构造出一组方案使得村民的花费之和为 $2(n-1)$。

然后，我们一定可以把这棵树划分成若干个连通块，使得这些连通块内的村民搬家也都搬到连通块内。

因为如果一个村民搬家搬到连通块外，那么这个村民搬家路途上的点一定都在连通块内（因为我们用相同的步数一定可以把这些点都包括到连通块内），而这样的操作可以视为连通块的扩展。

接下来我们就可以愉快地设 $\rm DP$ 状态了。

设 $f_{x,0}$ 表示以点 $x$ 为根的子树内，且点 $x$ 一个点形成一个连通块的最小花费。

$f_{x,1}$ 表示以点 $x$ 为根的子树内，点 $x$ 和另外的点拼成一个连通块的最小花费.

显然答案就是 $f_{1,1}$。

然后考虑怎么转移。

我们枚举 $x$ 的儿子，设为 $v$。

那么 $f_{x,0}=f_{x,0}+f_{v,1}$（因为如果 $v$ 也是一个点形成连通块就不合法了）。

$f_{x,1}=\min(f_{x.0}+\min(f_{v,0},f_{v,1})+2,f_{x,1}+\min(f_{v,0}+2,f_{v,1}))$。

解释一下这个转移，$f_{x,0}+\min(f_{v,0},f_{v,1})+2$ 的意思就是我前面都不与 $x$ 一个连通块，从 $v$ 开始跟 $x$ 连接，又因为我们上面说的，一棵树一定可以构造出花费为 $2(n-1)$ 的方案，所以我们这里的代价 $+2$。

$f_{x,1}+\min(f_{v,0}+2,f_{v,1})$ 的意思就是我前面已经有东西跟 $x$ 连接了，那么我当前的 $v$ 可以选择单独一个点，跟 $x$ 连起来，或者连子树，跟 $x$ 不连。

一通转移之后，我们还需要输出方案。

不难发现，我们可以根据 $\min$ 取在哪里分类一下，然后把原树划分成若干个连通块。我们在每个连通块里构造一下方案，因为每个连通块都是一颗树，所以我们就按照树的方法构造花费为 $2(n-1)$ 的方案即可。

## 代码

[提交记录](https://codeforces.com/problemset/submission/1387/211899131)

[一份稍微简洁一点的代码，删掉了一些没用的东西](https://codeforces.com/problemset/submission/1387/211955980)

---

## 作者：xujunlang2011 (赞：0)

## 题意

给定一棵以 $1$ 为根的树，现在将所有节点重排到其他位置，每个节点移动的代价是旧位置与新位置的距离，求重排后所有节点代价的最小值。

## 思路

首先一次交换只能交换相邻的两个节点：

```
（1）---（2）---（3）---（4）
```
在这里肯定要交换 $1$ 和 $2$ 与 $3$ 和 $4$，而不是交换 $1$ 和 $4$。

然后我们再来看树的情况：

```
  （1）
  /   \
（2）（3）
```

我们先 `dfs` 到了 $2$，发现可以和 $1$ 交换，那就直接交换。然后到了 $3$，发现他也要和 $1$ 交换，可是 $1$ 已经被 $2$ 换掉了，那就直接把在 $1$ 位置的 $2$ 给换下来，最后回到了 $1$，发现 $1$ 已经被换走了，最后这棵树长这样：

```
  （3）
  /   \
（1）（2）
```

因为每次交换都会将这个点和他的父节点各移动一次，所以一次交换的代价是 $2$。

我们发现， $1$ 是没有父节点的，所以我们如果要交换 $1$，只能和他的字节点交换。

最后，我们来总结一下策略。开一个数组存每个节点位置的当前所在节点，先 `dfs` 到叶子节点，然后从下往上交换未交换过的节点，每交换一次代价加 $2$，最后把代价总和与节点情况输出即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, x, y, cnt, num, b[200005], hc[200005];
struct node
{
    int u, v, h;
}a[200005];
void add(int p, int q)
{
    a[++cnt].u = p;
    a[cnt].v = q;
    a[cnt].h = hc[p];
    hc[p] = cnt;
}
void dfs(int k, int fa)
{
    for (int i = hc[k];i != 0;i = a[i].h)
    {
        if (a[i].v != fa)
        {
            dfs(a[i].v, k);
        }
    }
    if (b[k] == k)
    {
        if (k != 1)
        {
            swap(b[k], b[fa]);
        }
        else
        {
            swap(b[k], b[a[hc[k]].v]);
        }
        num += 2;
    }
}
int main()
{
    cin >> n;
    for (int i = 1;i <= n - 1;i++)
    {
        cin >> x >> y;
        b[i] = i;
        add(x, y);
        add(y, x);
    }
    b[n] = n;
    dfs(1, 1);
    cout << num << "\n";
    for (int i = 1;i <= n;i++)
    {
        cout << b[i] << " ";
    }
    return 0;
}
```


---

## 作者：lmy_2011 (赞：0)

### 首先说明
本文转载于[此](https://blog.csdn.net/qq_31805591/article/details/107768770)
### 题意简述
给定一个村庄，每个房子都有编号，每个村民也有个编号且住在对应的房子中，现在要求每个村民搬到其他房子，使得没有一个村村民住在原来的地方。输出路途和，以及搬家后每个房子住的村民。
### 题解思路
其实这个问题中的村庄可以转化成：一个 $n$ 个点的树，$n-1$ 条边，每条边边权为 $1$，所以我们将会以树的思路来讲。

我们知道，遍历二叉树是需要通过深度优先搜索来实现的，所以我们就深度优先搜索，枚举每个村庄。这个村庄能去的地方我们称之为子节点，能搬到这个村庄的，是村庄的父节点。
- 考虑每个村民都需要搬家，最优的搬家方式一定是与当前时刻下最近房子里面的人换家。

- 故可以将所有子节点数量为 $1$（只能向一个地方搬家）的人加入一个队列，并与其父节点房子里的的人进行交换。
 
 
计算完成后出队，并使得此父节点的子节点数量减 $1$。

如果当前的父节点被交换过且子节点数量为 $1$，则不进队列，并使其父亲的子节点数量减 $1$。
### 核心代码：
```cpp
void dfs(int ii, int fx, vector<vector<int>>&vec, int *fa, int *du, int *qq, int &qq_id)
{
	fa[ii] = fx;
	for (int i = 0; i < vec[ii].size(); i++)
	{
		int e = vec[ii][i];

		if (e == fx)
			continue;
		du[ii]++;
		dfs(e, ii, vec, fa, du, qq, qq_id);
	}
	if (!du[ii])
		qq[++qq_id] = ii;
}

void delFF(int ii, int *du, int *fa, bool* done, int *qq, int &qq_id)
{
	int ff = fa[ii];

	if (du[ii] == 0)
	{
		if (done[ii])
			du[ff]--,
			delFF(ff, du, fa, done, qq , qq_id);
		else
			qq[++qq_id] = ii;
	}
}

int main()
{
	int *fa = new int[maxn]();
	int *du = new int[maxn]();
	int *qq = new int[maxn]();
	int *rs = new int[maxn]();
	bool *done = new bool[maxn]();
	int special = 0;
	int qq_id = 0;

	int n;
	vector<vector<int>>&vec = *(new vector<vector<int>>(maxn));

	scanf("%d", &n);
	for (int i = 1; i <= n - 1; i++)
	{
		int x, y;

		scanf("%d%d", &x, &y);
		vec[x].push_back(y);
		vec[y].push_back(x);
		if (x == 1)
			special = y;
		if (y == 1)
			special = x;
		rs[i] = i;
	}
	rs[n] = n;
	dfs(1, 1, vec, fa, du, qq, qq_id);
	int res = 0;

#if _dd_
	printf("special=%d\n", special);
#endif
	for (int i = 1; i <= qq_id; i++)
	{
		int ii = qq[i];
		int ff = fa[ii];

		if (ii == 1)
			ff = special;
		done[ff] = 1;
		done[ii] = 1;
		du[ff]--;
		delFF(ff, du, fa, done, qq, qq_id);
		res += 2;

		swap(rs[ii], rs[ff]);
#if _dd_
		printf("ii=%d ff=%d\n", ii, ff);
		for (int i = 1; i <= n; i++)
			printf("-%d-%c", rs[i], i == n ? '\n' : ' ');
		for (int i = 1; i <= n; i++)
			printf("=%d=%c", du[i], i == n ? '\n' : ' ');
#endif
	}
	printf("%d\n", res);
	for (int i = 1; i <= n; i++)
		printf("%d%c", rs[i], i == n ? '\n' : ' ');
	return 0;
}

```

---

