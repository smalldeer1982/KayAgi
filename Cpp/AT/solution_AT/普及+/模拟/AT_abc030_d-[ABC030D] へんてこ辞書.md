# [ABC030D] へんてこ辞書

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc030/tasks/abc030_d

ミカミくんは怪しい英単語帳を使っています。その単語帳には $ N $ 個の単語の意味が載っており、単語 $ i $ の説明には「単語 $ b_i $ と同じ意味である」とだけ書いてあります。ここで、$ i $ 番目の単語を単語 $ i $ と呼ぶことにします。 ミカミくんはまだ一つの英単語も知らないので、単語 $ i $ の意味を調べようとしたとき、単語 $ b_i $ の意味を調べようとします。ミカミくんは真面目なので、今までにすでに調べようとしたことのある単語でも同じように単語帳をひき続けます。 しかし、残念ながらこの単語帳では英単語の意味自体はどこにも書いていないため、意味を知ることはできません。 ある単語 $ i $ を調べようとして、単語帳を参照し、単語 $ b_i $ を調べようとするまでを1ステップとします。

ミカミくんが単語 $ i $ を調べようとして、$ k $ ステップ経ったとき、ミカミくんはどの単語を調べようとしているでしょうか？

### Input &amp; Output Format

入力は以下の形式で標準入力から与えられる。

> $ N $ $ a $ $ k $ $ b_1 $ $ b_2 $ … $ b_N $

- $ 1 $ 行目には、単語の数 $ N\ (2\ ≦\ N\ ≦\ 10^5) $ とミカミくんが調べようとしている単語の番号 $ a\ (1\ ≦\ a\ ≦\ N) $ がスペース区切りで与えられる。
- $ 2 $ 行目には、ミカミくんが単語を調べるステップ数 $ k(1\ ≦\ k\ ≦\ 10^{100000}) $ が与えられる。
- $ 3 $ 行目には、各単語の説明を表す $ N $ 個の整数 $ b_1,...,b_N $ が空白区切りで与えられる。
- $ 1\ ≦\ b_i\ ≦\ N\ かつ\ b_i\ ≠\ i\ (1\ ≦\ i\ ≦\ N) $ であることが保証される。

## 说明/提示

### 部分点

この問題には部分点が設定されている。

- $ k\ ≦\ 10^{18} $ を満たすデータセットに正解した場合は $ 50 $ 点が与えられる。

### Sample Explanation 1

ミカミくんは、それぞれのステップで以下のように単語を調べます。 $ 1 $ ステップ目で、単語 $ 4 $ の意味を知るため、単語 $ 2 $ を調べようとします。 $ 2 $ ステップ目で、単語 $ 2 $ の意味を知るため、単語 $ 3 $ を調べようとします。 $ 3 $ ステップ目で、単語 $ 3 $ の意味を知るため、単語 $ 1 $ を調べようとします。 $ 4 $ ステップ目で、単語 $ 1 $ の意味を知るため、単語 $ 2 $ を調べようとします。 $ 5 $ ステップ目で、単語 $ 2 $ の意味を知るため、単語 $ 3 $ を調べようとします。 よって、$ 5 $ ステップ経ったとき、ミカミくんは単語 $ 3 $ を調べようとしています。

### Sample Explanation 2

$ k $ はたいへん大きくなることがあります。

## 样例 #1

### 输入

```
6 4
5
2 3 1 2 6 5```

### 输出

```
3```

## 样例 #2

### 输入

```
4 1
100000000000000000000
2 3 4 1```

### 输出

```
1```

## 样例 #3

### 输入

```
8 1
1
2 3 4 5 3 2 4 5```

### 输出

```
2```

# 题解

## 作者：_ckx_ (赞：2)

## 题目大意

给定一张有向图，求从 $a$ 点遍历 $k$ 次所到达的点。

每个点有且仅有有一条出边，无自环。

## 分析

因为每个点都有一条出边，所以这张图中必定存在至少一个环。

所以我们只需要 DFS 找到距离 $a$ 最近的一个环，通过取模就可以大大减少遍历次数。

### 一些细节

将所有下标 $-1$ 可以方便取模。

由于 $k$ 很大，我们可以先用 `string` 来存，计算出环长后，转化成整数的过程中不断模环长就行了。

当 $k$ 比较小时，可以直接暴力走，比如当 $k \le 10^5$ 时，不会超时，还能省略掉走 $k$ 步还到不了环的情况（因为 $n \le 10^5$）。

`int stoi(str)`：将 `string` 类型转化成 `int` 类型。

## code

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1e5 + 10;
int b[N] ,dis[N];

int dfs(int u)
{
	if (dis[b[u]] != -1)
	{
		return u; //搜过了就返回最后的节点 
	}
	dis[b[u]] = dis[u] + 1;
	return dfs(b[u]);
}

int main()
{
	int n ,a;
	string s;
	cin >> n >> a >> s;
	a--; //方便取模 
	int len = s.size();
	
	for (int i = 0;i < n;i++)
	{
		scanf("%d",&b[i]);
		b[i]--; //同上 
	}
	
	//如果小于等于1e5就直接暴力 
	if (len <= 5)
	{
		int ans = a;
		int k = stoi(s);
		while (k--)
		{
			ans = b[ans];
		}
		printf("%d\n",ans + 1); //别忘了+1 
		return 0;
	}
	
	memset(dis ,-1 ,sizeof(dis));
	dis[a] = 0;
	int pos = dfs(a);
	
	int rlen = dis[pos] - dis[b[pos]] + 1; //计算环的长度 
	
	int k = 0;
	for (int i = 0;i < len;i++)
	{
		k = (k * 10 + s[i] - '0') % rlen; //边转边模 
	}
	
	k = ((k - dis[b[pos]]) % rlen + rlen) % rlen; //减去a到入环点的距离，取非负整数 
	
	int ans = b[pos];
	for (int i = 0;i < k;i++) //暴力找最终答案 
	{
		ans = b[ans];
	}
	printf("%d\n",ans + 1); //别忘了+1 
	
	return 0;
}
```

---

## 作者：残阳如血 (赞：1)

### $\textbf{Description}$
给定一张每个点出度为 $1$ 的简单图，点数为 $n$。

求从点 $s$ 出发，经过 $k$ 条边后到达的点的编号。

$2\le n \le 10^5$，$1\le s\le n$，$1\le k\le10^{10^{5}}$。
### $\textbf{Solution}$
$k$ 如此大，一步一步枚举肯定是不现实的。

发现 $n\le10^5$，则图中**极有可能**存在一个可以由 $s$ 到达的环，如此大的 $k$ 只是在环里绕来绕去。

当然，如果 $k$ 非常小，则可能不存在环，但是此时直接模拟即可（详见代码）。

---

下面讨论图中存在环的情况。

如何找到一个环呢？考虑使用 DFS。

具体地，从 $s$ 开始 DFS，同时标记下每个点是否被访问。当第二次遍历到一个点 $u$ 时，这个点就是环上的点。

同时记录下遍历到点的顺序，从最后倒着回到第一次访问到 $u$ 时，这段区间就是环。

```cpp
// nodes 记录遍历到的点的顺序
// dis 记录 s->u 的距离（下面要用），开始赋特殊值，可用于判重
// ed 记录上文提到的访问两次的点
// cnt 记录当前访问了几个点
void dfs(int u, int f) {
	nodes[++cnt] = u;
	dis[u] = dis[f] + 1;
	for (auto v : g[u]) {
		if (flag) return ;
		if (dis[v] != INF) { // 环
			ed = v;
			flag = true; // 标记，直接一路返回主函数
			return ;
		}
		dfs(v, u);
	}
	if (flag) return ;
	--cnt; // 回溯
}
```

以样例 1 为例，图如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/sgk2nk07.png)

> P.S. $5,6$ 两点处于另外一个连通分量，故不考虑。

当遍历到点 $1$ 时，
$$
\begin{aligned}
\text{dis}&\gets\{4,2,3,1\}\\
\text{nodes}&\gets\{4,2,3,1\}\\
\text{cnt}&\gets4
\end{aligned}
$$

发现 $1$ 的后继为 $2$，而 $\text{dis}_2$ 已经有值了，故 $\text{ed}\gets2$。

在 $\text{nodes}$ 中找到 $2$，则
$$
\{4,\underlinesegment{2,3,1}\}
$$
下划线划起的一段就是循环节，长度 $l=3$。

```cpp
int id = -1; // nodes 中 ed 的位置
for (int i = 1; i <= cnt; ++i) // 遍历寻找
  if (nodes[i] == ed) {
    id = i;
    break;
  }

int len = cnt - id + 1; // 循环节长度
```

接下来直接求 $k\bmod l$ 吗？

不对。在进入环之前，我们会先经过一段不会重复的路径。

首先，进入 $\text{ed}$ 之前，我们会经过 $\text{dis}_\text{ed}-1$ 条边。

那么令 $k'=k-\text{dis}_\text{ed}+1$ 吗？

不对。假设 $k=3$，在上图中 $k'=0$。

在小学奥数中我们都学过，要让循环节第一位为 $1$，第二位为 $2$，……，最后一位为 $0$。

故可以发现令 $k'=k-\text{dis}_\text{ed}+2$ 即可。

（上面听起来很复杂，其实画个图找规律一下就可以发现了）

然后我们要求 $k'\bmod l=r$。

因为 $k$ 为高精度整数，其他部分都是单精度，那么可以将 $k'$ 拆分为 $k$ 和 $\text{dis}_\text{ed}-2$。

因为
$$
(a-b)\bmod m=(a\bmod m-b\bmod m)\bmod m
$$

所以 $k$ 可以按位拆分，不断迭代。

```cpp
lint mod(std::string a, lint b) { // 高精%单精
	lint res = 0;
	for (auto ch : a) res = (res * 10 + ch - '0') % b;
	return res;
}
```

最后输出 $\text{nodes}_{\text{id}+r-1}$（$\text{id}$ 意义见前文）。

当 $r=0$ 时，令 $r=l$ 即可。

> Q：为什么令 $r=l$？
> 
> A：在代码中，$l=\text{cnt}-\text{id}+1$，输出下标为 $\text{id}+r-1$，代入可得
> $$
> \begin{aligned}
> \text{id}+r-1&=\text{id}+l-1\\
> &=\text{id}+\text{cnt}-\text{id}+1-1\\
> &=\text{cnt}
> \end{aligned}
> $$
>
> 就是循环节最后一位的下标。

### $\textbf{Code}$

[record](https://atcoder.jp/contests/abc030/submissions/62480724)。

```cpp
#include <bits/stdc++.h>
using lint = long long;
const int N = 1e6 + 10;
const int INF = 0x3f3f3f3f;

std::string k;
std::vector<int> g[N];
int n, s;

bool flag;
int cnt, ed = -1, dis[N], nodes[N];
// dfn 记录遍历到的点

void dfs(int u, int f) {
	nodes[++cnt] = u;
	dis[u] = dis[f] + 1;
	for (auto v : g[u]) {
		if (flag) return ;
		if (dis[v] != INF) { // 环
			ed = v;
			flag = true;
			return ;
		}
		dfs(v, u);
	}
	if (flag) return ;
	--cnt;
}

lint mod(std::string a, lint b) {
	lint res = 0;
	for (auto ch : a) res = (res * 10 + ch - '0') % b;
	return res;
}

bool cmp(const std::string &a, const std::string &b) { // 返回 a<b 是否成立
	if (a.size() != b.size()) return a.size() < b.size();
	for (size_t i = 0; i < a.size(); ++i) {
		if (a[i] < b[i]) return true;
	}
	return false;
}

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> n >> s >> k;
	for (int u = 1, v; u <= n; ++u) {
		std::cin >> v;
		g[u].push_back(v);
	}
	memset(dis, 0x3f, sizeof(dis));
	dis[0] = 0;
	
	dfs(s, 0);
	
	//	 从 a 出发没有环，则 k 不可能很大，直接 DFS/ans 直接可以求出
	if (ed == -1 || (k.size() <= 10 && cmp(k, std::to_string(cnt))))
		return std::cout << nodes[stoi(k) + 1] << std::endl, 0;
	
	// 存在环, ed 就是环的起点，在 nodes 中找到 ed 就可确定长度
	int id = -1;
	for (int i = 1; i <= cnt; ++i)
		if (nodes[i] == ed) {
			id = i;
			break;
		}
	
	int len = cnt - id + 1;
	
	int r = (mod(k, len) - (dis[ed] - 2) % len + len) % len;
	
	if (r == 0) r = len; // r = 0 就取循环节中的最后一个
	
	std::cout << nodes[id + r - 1] << std::endl;
	
	return 0;
}
```

---

## 作者：ln001 (赞：0)

大水题，评不到绿。

对 $i$ 向 $b_i$ 连边，只需要从 $a$ 点开始走 $k$ 条边即可。其中考虑对环的部分进行优化，实现是典的。

要注意的是对于 $k$ 小于 $n$ 的情况，因为可能出现来不及进入环的情况，所以直接暴力搜索即可。

[Link](https://atcoder.jp/contests/abc030/submissions/58017671)

---

