# Pairing Pairs

## 题目背景

本题为赛时原始数据。如果想要测试 $O(n)$，可以参考[加强版](https://www.luogu.com.cn/problem/P10248)。

## 题目描述

你有 $m$ 个数对 $(u_i,v_i)$（保证 $1\le u_i<v_i\le n$ 且 $m$ 个数对两两不同），对于每个 $i$ 找一个 $j$ 使得 $u_i,v_i,u_j,v_j$ 四个数两两不同，或报告不存在。

## 说明/提示

【样例解释】

答案不唯一，例如 $i=4$ 时：
- $j$ 也可以是 $3$，因为 $2,5,1,3$ 四个数互不相同。所以输出 `5 0 4 3 1` 也可通过测试点。
- 然而 $j$ 不可以是 $1$，因为 $2,5,1,2$ 中存在相同数字。

【数据范围】

**本题采用捆绑测试。** 具体地，你只有通过一个子任务内所有测试点，才能拿到该子任务的分数。

|子任务编号|$n\le$|$m\le$|特殊性质|分值|
|:-:|:-:|:-:|:-:|:-:|
|$1$|$10^3$|$3\times 10^3$||$19$|
|$2$|$=10^3$|$=3\times 10^5$||$16$|
|$3$|$3\times 10^5$|$=n-1$|$u_i=i,v_i=i+1$|$3$|
|$4$|$3\times 10^5$|$=n-1$|$v_i=i+1$|$22$|
|$5$|$3\times 10^5$|$3\times 10^5$|数据随机|$11$|
|$6$|$3\times 10^5$|$3\times 10^5$||$29$|

子任务 $5$ 的具体生成过程：首先我**指定**一组 $n,m$，接下来执行 $m$ 次如下流程：
- 在 $1\sim n$ 内抽取 $x$，然后在 $1\sim n-1$ 内抽取 $y$。
- 若 $y\ge x$ 则把 $y$ 增加 $1$，否则交换 $x,y$。
- 判断数对 $(x,y)$ 是否出现过，若是，回到第一步。
- 输出 $(x,y)$。

对于全部数据，保证 $1\le u_i<v_i\le n\le 3\times 10^5$，$1\le m\le 3\times 10^5$。

## 样例 #1

### 输入

```
6 5
1 2
2 3
1 3
2 5
3 6
```

### 输出

```
5 0 4 5 1
```

# 题解

## 作者：irris (赞：24)

> 枚举，暴力，优化

## Solution

发现很多点的答案都可以是 $1$。

也就是说，只有 $x_i$ 或 $y_i$ 与 $x_1$ 或 $y_1$ 相等的 $i$ 才需要找到一个非 $1$ 的 $j$。

继续前行，不妨设其中一个值是与 $x_1$ 相等（与 $y_1$ 相等可以同理处理），我们把所有这样的元素单独拿出来。

对于其它的元素，显然没有一个值与 $x_1$ 相等。我们不妨在其中找到了一个元素 $(p, q)$（如果找不到，就退出即可，因为事实上这表明所有点的答案都是 $0$）。

那么又有很多点的答案可以是 $(p, q)$。只有最多两个点 $(\min(x_1, p), \max(x_1, p))$ 和 $(\min(x_1, q), \max(x_1, q))$ 不符合条件，我们 $\mathcal O(n)$ 扫一遍原数组即可。

时间复杂度 $\mathcal O(n)$。这玩意值域无关。

## Code

下面是一份参考实现。

```cpp
#include <bits/stdc++.h>

inline bool ok(int a, int b, int c, int d) {
	if (a == c || a == d || b == c || b == d) return false;
	return true;
}

#define MAXN 300001
int x[MAXN], y[MAXN], res[MAXN];
void solve(std::vector<std::pair<int, int>> &m, int n, int tar) {
	std::vector<int> pos;
	for (int i = 1; i <= n; ++i) if (x[i] != tar && y[i] != tar) pos.push_back(i);
	// for each m, try to find match tar.
	if (pos.empty()) return;
	int P = x[pos[0]], Q = y[pos[0]];
	for (auto [i, key] : m) if (key != P && key != Q) res[i] = pos[0];
	else /* O(1) * O(n) */ 
		for (int u : pos) if (x[u] != key && y[u] != key) res[i] = u;
}
int main() {
	int m, n; std::cin >> m >> n; std::vector<std::pair<int, int>> vX, vY;
	for (int i = 1; i <= n; ++i) std::cin >> x[i] >> y[i];
	for (int i = 2; i <= n; ++i) if (ok(x[1], y[1], x[i], y[i])) res[i] = 1, res[1] = i;
	else if (x[i] == x[1] || y[i] == x[1]) vX.push_back({i, x[i] ^ y[i] ^ x[1]});
	else vY.push_back({i, x[i] ^ y[i] ^ y[1]});
	solve(vX, n, x[1]), solve(vY, n, y[1]);
	for (int i = 1; i <= n; ++i) std::cout << res[i] << " \n"[i == n];
	return 0;
}
```

---

## 作者：yummy (赞：24)

# D. Pairing Pairs 官方题解

本题涉及的主要知识点：

- 【3】图的定义和相关概念
- 【4】图的表示与存储：邻接表

## 部分分做法

### 子任务 1

对于每个数对 $i$，枚举 $j$，并判断是否符合题意。时间复杂度 $O(m^2)$。

### 子任务 2

用一个二维数组记录数对 $(u,v)$ 是否存在以及其编号。接下来对于每个数对 $(u,v)$，随机抽一对 $(s,t)$，检查合法性以及是否存在，若不存在则重新抽。

因为该子任务的图相当稠密（完全图也只有约 $5\times 10^5$ 条边），所以平均每条边只要抽 $5/3$ 次。时间复杂度 $O(n^2+m\cdot \dfrac{n^2}{m})=O(n^2)$。

### 子任务 5

对于每个 $i$，随机抽一个 $j$ 并检查是否符合题意。

找一个数对的期望次数约为 $1+\dfrac{4}{n}$（这一部分不要求 J 组会计算，只要感性理解“从 $n$ 个数中抽四个，大概率是不重复的”即可），所以总时间复杂度约为 $O(m)$。

## 正解

看到数对，一个很合理的想法是把它转化成图论问题，也就是给出一张无向图，对于每一条边 $i$，找另一条边 $j$ 使得 $i,j$ 没有公共点。

根据直觉，限制条件只有几个不等式，是个很宽松的条件。我们能不能从图上找一些边，然后直接一劳永逸了呢？

（我估计具体的选法会非常多，我的做法很可能不是最简单的，仅供参考）

### Part 1 四点链

如果图上存在 $A-B-C-D$ 的结构（我称为四点链），那么对于每条边：

- 如果两端点都不是 $A,B,C,D$ 之一，那么随便挑一条边即可。
- 如果两端点中恰有一个是 $A$ 或 $B$，则选 $C-D$ 这条边即可。$C,D$ 同理。
- 如果两端点都是 $A,B,C,D$ 之一，那么**这样的边不超过 $6$ 条**，直接 $O(m)$ 做就行。

事实上哪怕 $A,D$ 重合了（三角形），我们也可以使用类似的方法进行推理，所以**只要**能找到三条不同的边 $P,Q,R$ 满足 $P,Q$ 和 $Q,R$ 分别交于 $Q$ 的两端点，**就能**在 $O(m)$ 的时间内找出答案。

---

寻找四点链，可以枚举边 $Q$。如果某条边 $Q$ 的两端**度数**均 $\ge 2$，那么我们一定能找出一对 $P,R$。

这里你需要使用邻接表或 `vector` 记录和每个点相邻的点和对应的边编号。

### Part 2 菊花图森林

如果很不幸，你没有找到四点链，怎么办？

一张图没有四点链，那么一定是若干个菊花图（也就是一个中心直接连接了若干个其它结点）放在一起。

如果整张图里只有一个菊花图，那么显然大家都无法成功配对（所有边都连接了中心）。

如果有至少两个菊花图，那么每条边都和**另一个菊花图**里的边配对即可。

写的时候留意一下只有两个点的菊花图，因为此时两个点的度数都是 $1$，无法通过度数来判定谁是中心。

### Part 3 参考代码

总时间复杂度是 $O(n+m)$。如果使用一些更先进的语法可以再简化一下。

判菊花图的时候如果用 DFS 可能会短一点，但是 DFS 是 5 级考点，可能对大家太困难了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,u[300005],v[300005];
vector<int> g[300005];
bool well(int x,int y){
	int a=u[x],b=v[x],c=u[y],d=v[y];
	return a!=c && b!=c && a!=d && b!=d;
}
int isc[300005];
vector<int> cen;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d%d",&u[i],&v[i]);
		g[u[i]].emplace_back(i);
		g[v[i]].emplace_back(i);
	}
	int P=-1,Q=-1,R=-1;
	for(int i=1;i<=m;i++)
		if(g[u[i]].size()>1 && g[v[i]].size()>1){
			Q=i;
			if(g[u[i]][0]==Q)P=g[u[i]][1];
			else P=g[u[i]][0];
			if(g[v[i]][0]==Q)R=g[v[i]][1];
			else R=g[v[i]][0];
		}
	if(Q>0){
		for(int i=1;i<=m;i++){
			if(well(i,P))printf("%d ",P);
			else if(well(i,Q))printf("%d ",Q);
			else if(well(i,R))printf("%d ",R);
			else{
				int res=0;
				for(int j=1;j<=m;j++){
					if(well(i,j)){
						res=j;
						break;
					}
				}
				printf("%d ",res);
			}
		}
	}
	else{
		for(Q=2;Q<=m;Q++)
			if(well(1,Q))break;
		if(Q>m)Q=0;
		for(int i=1;i<=m;i++){
			if(well(i,1))printf("%d ",1);
			else printf("%d ",Q);
		}
	}
	return 0;
}
```

以下是采用相同思路的 Python 3 代码，菊花图部分有所简化：

```python
def well(x,y):
    A=sorted(x+y)
    return A[0]!=A[1]!=A[2]!=A[3]
n,m=map(int,input().split())
g=[[] for i in range(n+1)]
es=[]
for i in range(m):
    u,v=map(int,input().split())
    es.append((u,v))
    g[u].append(i)
    g[v].append(i)
for Q in range(m):
    u,v=es[Q]
    if len(g[u])>1 and len(g[v])>1:
        P,R=g[u][0],g[v][0]
        if P==Q:
            P=g[u][1]
        if R==Q:
            R=g[v][1]
        for i in es:
            for j in P,Q,R:
                if well(i,es[j]):
                    print(j+1,end=' ')
                    break
            else:
                for j in range(m):
                    if well(i,es[j]):
                        print(j+1,end=' ')
                        break
                else:
                    print(0,end=' ')
        break
else:
    for Q in range(m):
        if well(es[Q],es[0]):
            for i in es:
                if well(i,es[0]):
                    print(1,end=' ')
                else:
                    print(Q+1,end=' ')
            break
    else:
        for i in es:
            print(0,end=' ')
```

---

## 作者：szh_AK_all (赞：16)

### 题意
一共有 $m$ 对数对，要对于每个数对，找到一个数对，满足这两个数对中没有相同的数字。

[赛事记录](https://www.luogu.com.cn/record/150266082)

### 分析
与官方题解不一样的是，~~我万万没想到这题是道图论题。~~

咱们首先思考一个问题，对于某个数对，对于它来说能满足题意的数对的 $u$ 肯定与这个数对的 $u$ 不相同，也就是我们首先可以排除 $u$ 与这个数对相同的数对。

那么对于这个问题，我们可以想到什么？

当然是排序，以 $u$ 为第一关键字按照升序排序（降序也行）。

那么接下来，我们能得出的一点是，在排完序后，对于当前要判断的数对，我们可以用二分的方法找出最后一个数对的 $u$ 小于该数对的 $u$ 的位置，与第一个数对的 $u$ 大于该数对的 $u$ 的位置（也就是前驱与后缀）。接下来要找出前驱与后缀中满足题意的数对。

如果直接枚举前驱后缀复杂度肯定是错的，那么如何优化呢？

对于前驱后缀中的每一个数对，我们能保证的是，它的 $u$ 不等于当前数对的 $u$，且由题意可知，每个数对的 $u$ 和 $v$ 都不相同。

那么我们不能保证什么？

1. 前驱后缀中的数对的 $u$ 与该数对的 $v$ 是否相同;
2. 前驱后缀中的数对的 $v$ 与该数对的 $u$ 是否相同;
3. 前驱后缀中的数对的 $v$ 与该数对的 $v$ 是否相同;

也就是对于某个数对的 $u$，可能会与该数对的 $v$ 相同；对于某个数对的 $v$，可能会与该数对的 $u,v$ 相同。

但是！

如果我们有了两个不同的 $u$ 值，那么它们中至少有一个 $u$ 与该数对的 $v$ 不同；同理，如果我们有了三个不同的 $v$ 值，那么它们中至少有一个 $v$ 与该数对的 $v$ 不同。

所以，对于每个前缀、后缀，我们只需记录最多 $6$ 个数对，在判断时，枚举每个存下来的数对，看看其中有没有符合的。

容易知道，改复杂度绝对正确。

### Code
```cpp
#include <bits/stdc++.h>
using namespace std;

struct node {
	int x;
	int y;
	int id;
	friend bool operator<(node l, node r) {
		if (l.x != r.x)
			return l.x < r.x;
		return l.y < r.y;
	}
} s[300005];
int tot;
int tmp[300005];
vector<int>qian[300005];
map<pair<int, int>, int>q;
map<int, int>qx, qy;
vector<int>hou[300005];
map<pair<int, int>, int>qq;
map<int, int>qqx, qqy;

int ch(int a, int b) {
	return (s[a].x != s[b].y && s[a].y != s[b].y && s[a].y != s[b].x);
}

int main() {
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		int x, y;
		cin >> x >> y;
		if (x != y)//其实这个判断没啥用
			s[++tot].id = i, s[tot].x = x, s[tot].y = y;
	}
	sort(s + 1, s + tot + 1);
	for (int i = 1; i <= tot; i++) {//重点
		qian[i] = qian[i - 1];
		if (qian[i].size() < 6) {
			if (!q[make_pair(s[i].x, s[i].y)] && qx[s[i].x] <= 1 && qy[s[i].y] <= 2) {
				q[make_pair(s[i].x, s[i].y)] = 1;
				qx[s[i].x]++;
				qy[s[i].y]++;
				qian[i].push_back(i);
			}
		}
	}
	for (int i = tot; i >= 1; i--) {
		hou[i] = hou[i + 1];
		if (hou[i].size() < 6) {
			if (!qq[make_pair(s[i].x, s[i].y)] && qqx[s[i].x] <= 1 && qqy[s[i].y] <= 2) {
				qq[make_pair(s[i].x, s[i].y)] = 1;
				qqx[s[i].x]++;
				qqy[s[i].y]++;
				hou[i].push_back(i);
			}
		}
	}
	for (int i = 1; i <= tot; i++) {
		if (s[i].x == s[i].y || tmp[s[i].id])
			continue;
		int ans = 0;
		int l = 1, r = i - 1;//手写二分
		while (l <= r) {
			int mid = (l + r) / 2;
			if (s[mid].x < s[i].x) {
				ans = mid;
				l = mid + 1;
			} else
				r = mid - 1;
		}
		if (ans != 0) {
			int f = 0;
			for (int j = 0; j < (int)qian[ans].size(); j++) {
				int u = qian[ans][j];
				if (ch(u, i)) {
					f = s[u].id;
					break;
				}
			}
			if (f) {
				tmp[s[i].id] = f;
				tmp[f] = s[i].id;
				continue;
			}
		}
		ans = 0;
		l = i + 1, r = tot;
		while (l <= r) {
			int mid = (l + r) / 2;
			if (s[mid].x > s[i].x) {
				ans = mid;
				r = mid - 1;
			} else
				l = mid + 1;
		}
		if (ans != 0) {
			int f = 0;
			for (int j = 0; j < (int)hou[ans].size(); j++) {
				int u = hou[ans][j];
				if (ch(u, i)) {
					f = s[u].id;
					break;
				}
			}
			if (f) {
				tmp[s[i].id] = f;
				tmp[f] = s[i].id;
				continue;
			}
		}
	}
	for (int i = 1; i <= m; i++)
		cout << tmp[i] << " ";
}
```

---

## 作者：tiger2005 (赞：5)

首先考虑对每个数对 $(x, y)$，在某个图上将点 $x$ 和点 $y$ 连在一起，那么读入的信息就转换到了图上，限制也变成了选择的边不“点相邻”。我们将要借助这个图论述一个重要性质：答案要么全是 `0`，要么只有不超过三个 `0`。

> 证明：假设有一个数对 $(a, b)$ 答案是 `0`，那么这代表了所有的边都和 $a$ 或者 $b$ 相连。首先，如果所有的边都连向了同一个点，那么自然每条边都和其他的边相邻，自然答案就都是 `0`。否则，假设一些边 $u \in S$ 挂在了 $a$ 点下，一些边 $v \in T$ 挂在了 $b$ 点下。考虑到三元环处理起来比较棘手，我们来专门论述这种情况：
> 
> 1. 这张图不存在包含 $(a, b)$ 的三元环，那么只需要随便找一个 $u_0 \in S$ 匹配 $T$ 集合的所有点，反之亦然。
> 2. 这张图存在恰好一个包含 $(a, b)$ 的三元环（假设第三个点是 $c$），那么图的形状变成了一个深度为 $2$ 的基环树，其中两个节点 $a, b$ 下挂了一些边。紧接着注意到这些边实际上都一定有答案，比如挂在 $a$ 点下的边就可以将 $(b, c)$ 作为答案，那么唯一有可能没有答案的就是三元环上的三条边。最劣情况自然就是 $m=3$ 时，三条边都没有答案，此时就达到了答案中 `0` 个数的最大值。
> 3. 这张图存在超过一个包含 $(a, b)$ 的三元环，那么它们自然形成了至少一个四元环（比如 $a - c - b - d - a$ ）。注意到四元环中每一条边都可以将对边作为答案，我们就可以利用 $(a, c)$ 和 $(b, d)$ 更新其他所有边的答案。具体方式参考 (1.)。

在这个性质的保证下，我们可以用极为暴力的方式在 $O(n+m)$ 的正确复杂度下完成这道题目。

- 首先，将每个点的度数记下，判断是否是菊花图的情况；
- 其次，按顺序枚举每条边并暴力找答案，直到找到了一组或者确定无解。我们理论上只需要枚举四次就能找到一组答案，而由于此时无解的情况只可能是整张图只有一个三元环，那么复杂度自然是正确的。
- 最后，假设我们找到了一组答案 $s = (a, b)$ 和 $t = (c, d)$，那么我们枚举其他所有的边，并优先将它们和这两条边匹配。如果一条边同时和这两条边相邻，那么其必然是一边接在 $a / b$ 上，一边接在 $c / d$ 上，只有 $4$ 种情况，那么我们只需要对它们进行暴力查找即可。

```cpp
int main() {
  int n, m; cin >> m >> n;
  vector<pair<int, int>> vp(n);
  vector<int> deg(m + 1);
  for (auto &[a, b]: vp)
    cin >> a >> b, ++ deg[a], ++ deg[b];

  for (int i = 1; i <= m; i ++) if (deg[i] == n) {
    for (int j = 0; j < n; j ++)
      printf("0 ");
    return 0;
  }

  vector<int> ans(n, -1);
  auto check = [&] (int i, int j) {
    auto [a, b] = vp[i];
    auto [c, d] = vp[j];
    return (a != c && a != d && b != c && b != d);
  };

  int s = 0, t = -1;
  while (s < n) {
    for (int i = s + 1; i < n; i ++)
      if (check(i, s))
        t = i;
    if (t != -1)
      break;
    ++ s;
  }

  if (s == n) {
    for (int j = 0; j < n; j ++)
      printf("0 ");
    return 0;
  }

  for (int i = 0; i < n; i ++) {
    if (check(s, i))
      ans[i] = s;
    else if (check(t, i))
      ans[i] = t;
    else {
      for (int j = 0; j < n; j ++) if (check(i, j))
        ans[i] = j;
    }
  }

  for (auto e: ans)
    cout << e + 1 << ' ';

  return 0;
}
```

---

## 作者：_•́へ•́╬_ (赞：4)

$\color{purple}\colorbox{white}{λnwwλ}\color{white}\colorbox{purple}{!n!cλ}$ 场谁敢打啊。

## 思路

首先连边。

对于一个度数超过 $\frac m4$ 的点，即一个出现次数超过 $\frac m4$ 的数字，我们以其为中心暴力处理涉及这个数字的数对的答案（即解决这个点的所有边的答案），这个暴力 `set` 维护即可。

如果一条边连接的两个点度数都不大，那么直接随，大概率能随到答案。

## code

```cpp
#include<stdio.h>
#include<random>
#include<vector>
#include<set>
#define N 300009
using namespace std;
inline char nc()
{
	static char buf[99999],*l,*r;
	return l==r&&(r=(l=buf)+fread(buf,1,99999,stdin),l==r)?EOF:*l++;
}
inline void read(int&x)
{
	char c=nc();for(;c<'0'||'9'<c;c=nc());
	for(x=0;'0'<=c&&c<='9';x=(x<<3)+(x<<1)+(c^48),c=nc());
}
int n,m,a[N],b[N],ans[N];vector<int>e[N],id[N];mt19937 rnd('ltcau');
main()
{
	read(n);read(m);
	for(int i=1;i<=m;++i)read(a[i]),read(b[i]),
		e[a[i]].emplace_back(b[i]),id[a[i]].emplace_back(i),
		e[b[i]].emplace_back(a[i]),id[b[i]].emplace_back(i);
	for(int i=1;i<=n;++i)if(e[i].size()>m>>2)
	{
		set<int>s;for(int j=1;j<=m;s.emplace(j++));
		for(int j=0;j<e[i].size();++j)s.erase(id[i][j]);
		for(int j=0;j<e[i].size();++j)
		{
			for(int k=0;k<e[e[i][j]].size();++k)if(e[e[i][j]][k]^i)
				s.erase(id[e[i][j]][k]);
			if(s.size())ans[id[i][j]]=*s.begin();
			for(int k=0;k<e[e[i][j]].size();++k)if(e[e[i][j]][k]^i)
				s.emplace(id[e[i][j]][k]);
		}
	}
	for(int i=1;i<=m;++i)if(e[a[i]].size()>m>>2||e[b[i]].size()>m>>2)
		printf("%d ",ans[i]);
	else for(int j;;)
	{
		j=rnd()%m+1;
		if(a[i]==a[j])continue;
		if(a[i]==b[j])continue;
		if(b[i]==a[j])continue;
		if(b[i]==b[j])continue;
		printf("%d ",j);break;
	}
}
```

---

## 作者：LiaoYF (赞：4)

## 做法

首先我们把 $u_i$ 和 $v_i$ 其中任意一个是 $x$ 的 $i$ 存在对应的 vector 中。显然对于一个数对 $(u_i,v_i)$，所有在 $u_i$ 和 $v_i$ 这两个 vector 里的数对都是不能选的。

对于 $(u_i,v_i)$，怎样计算是否有 $j \in [l,r]$ 使得数对 $(u_j,v_j)$ 能选呢？把所有 vector 排序，然后二分查找 $u_i$ 和 $v_i$ 对应的 vector 中有多少数在 $[l,r]$ 之中，因为数对两两不同，所以除了 $(u_i,v_i)$ 不会有一个数对同时在两个 vector 中，所以求和就是区间中不能选的数的个数，注意如果 $i$ 在 $[l,r]$ 之中要减 $1$。

然后进行二分，如果 $[l,mid]$ 有答案就在 $[l,mid]$ 中找，否则在 $[mid+1,r]$ 中找，当 $l=r$ 时输出，相信大家都会。

## 代码

代码很短。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,u[300005],v[300005];
vector<int> a[300005];
inline bool check(int l,int r,int x){
    int cnt=upper_bound(a[u[x]].begin(),a[u[x]].end(),r)-lower_bound(a[u[x]].begin(),a[u[x]].end(),l);
    int cnt2=upper_bound(a[v[x]].begin(),a[v[x]].end(),r)-lower_bound(a[v[x]].begin(),a[v[x]].end(),l);
    return cnt+cnt2-(x>=l&&x<=r)!=r-l+1;
}
void solve(int l,int r,int x){
    if(l==r){
        cout<<l<<" ";
        return;
    }
    int mid=(l+r)/2;
    if(check(l,mid,x)){
        solve(l,mid,x);
    }else{
        solve(mid+1,r,x);
    }
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>u[i]>>v[i];
        a[u[i]].push_back(i);
        a[v[i]].push_back(i);
    }
    for(int i=1;i<=n;i++){
        sort(a[i].begin(),a[i].end());
    }
    for(int i=1;i<=m;i++){
        if(a[u[i]].size()+a[v[i]].size()-1==m){
            cout<<"0 ";
        }else{
            solve(1,m,i);
        }
    }
    return 0;
}
```

---

## 作者：hgckythgcfhk (赞：4)

一个口胡做法，我们可以把数对看成一个坐标系上的点，树套树是可以维护二维信息的，比如板题，我们可以把值和下标各看成一维，对于这个题，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/4so2nhdk.png)

我们现在把整个平面分成 $5$ 个部分，其中包括 $4$ 个矩形和中间红色的线，$(x,y)$ 是当前正在求的元素，发现，题意相当于找一个红线以外的元素，做法显然，每一个矩形都找一遍看看有没有，有就随便输出一个并结束，都没有就输出 $0$，现在的问题是怎么判断有没有，我们发现，**随便**输出一个看上去并不是很好做，强行及加个限制，假设我们把 $x$ 轴看成下标，那么对应上图就是：

1. 绿色部分表示 $[1,x-1]$ 区间中 $y$ 的前驱。

2. 蓝色部分表示 $[1,x-1]$ 区间中 $y$ 的后继。

3. 黄色部分表示 $[x+1,n]$ 区间中 $y$ 的前驱。

4. 蓝色部分表示 $[x+1,n]$ 区间中 $y$ 的后继。

现在，直接套板子就能做了。

有个细节，考虑到 $x$ 可能为 $1$ 我们把值域的下界从 $0$ 开始，这样就不存在一些可能出问题的边界情况了。

---

## 作者：DGH_Didi (赞：3)

### 简要题意

有 $m$ 个数对 $(u_i,v_i)$（两两不同），对于每个 $i$ 找一个 $j$ 使得 $u_i,v_i,u_j,v_j$ 四个数两两不同，或报告不存在。

$1\le u_i<v_i\le n\le 3\times 10^5$，$1\le m\le 3\times 10^5$。

### 简要思路
考虑根据数对的两个数为一条边的两个顶点建立有向图，在通过 dfs 遍历图的时候处理答案并存储下来，最后一并输出。

具体来说：在遍历到当前点（记作 $u$）的时候，我们标记与它相连接的所有边，再遍历它连接的下一个顶点（记作 $v$），首先标记 $v$ 的所有连边，再从所有未标记的边中任意选一条即可作为从 $u$ 到 $v$ 这条边的答案，之后取消标记 $v$ 的所有连边，重复上述操作。全部做完之后，取消标记 $u$ 的所有连边，继续搜索未搜索过的点。

对于标记的实现，`std::set` 可以满足这一需求，一开始插入所有可行的边，需要标记时删去即可，最后答案可以取其中最小的边。时间复杂度 $O(nlogm)$，但是由于一个点所连的边需要加入和从 set 中删除两次，加上 STL 本身的大常数，会 TLE。

因此我赛时考虑到了复杂度更优的做法：分块。记录每个块中可用边的个数，如果发现当前块可用边不为 0 直接在当前块中遍历即可。时间复杂度 $O(n\sqrt m)$，但是修改的时候是 $O(1)$ 的，查询 $O(n\sqrt m)$，因此可以通过本题。

### 参考代码
```cpp
#include <bits/stdc++.h>
#define endl '\n'

using namespace std;
using i64 = long long;

const int N = 3e5 + 5;
const int L = 550;
int n, m;
int ans[N];
bool vis[N];

struct Edge {
    int v, id;
};
vector<Edge> e[N];

struct Block {
    bool ok[N];
    int id[N], l[N], r[N], len[N], tot = 0, cnt[L], totOK = 0;
    void init(int n) {
        for (int i = 1; i <= n; i++) {
            id[i] = (i - 1) / L + 1;
        }
        tot = id[n];
        for (int i = 1; i <= tot; i++) {
            r[i] = i * L, l[i] = r[i] - L + 1;
            if (i == tot) {
                r[i] = n;
            }
            len[i] = r[i] - l[i] + 1;
        }
    }
    void unset(int pos) {
        int nowID = id[pos];
        if (ok[pos]) {
            ok[pos] = false;
            --cnt[nowID];
            --totOK;
        }
    }
    void set(int pos) {
        int nowID = id[pos];
        if (!ok[pos]) {
            ok[pos] = true;
            ++cnt[nowID];
            ++totOK;
        }
    }
    int query() {
        if (totOK == 0) {
            return 0;
        }
        for (int i = 1; i <= tot; i++) {
            if (cnt[i] != 0) {
                for (int j = l[i]; j <= r[i]; j++) {
                    if (ok[j]) {
                        return j;
                    }
                }
            }
        }
        return 0;
    }
} block;

void dfs(int x) {
    for (auto &[v, id] : e[x]) {
        block.unset(id);
    }
    for (auto &[v, id] : e[x]) {
        if (vis[v]) {
            continue;
        }
        for (auto &[vv, idd] : e[v]) {
            block.unset(idd);
        }
        ans[id] = block.query();
        for (auto &[vv, idd] : e[v]) {
            if (vv != x) {
                block.set(idd);
            }
        }
    }
    for (auto &[v, id] : e[x]) {
        block.set(id);
    }
    for (auto &[v, id] : e[x]) {
        if (vis[v]) {
            continue;
        }
        vis[v] = true;
        dfs(v);
    }
}

int main() {
    n = read(), m = read();
    block.init(m);
    for (int i = 1; i <= m; i++) {
        int u = read(), v = read();
        e[u].push_back({v, i});
        e[v].push_back({u, i});
        block.set(i);
    }
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            vis[i] = true;
            dfs(i);
        }
    }
    for (int i = 1; i <= m; i++) {
        cout << ans[i] << " ";
    }
    return 0;
}
```

---

## 作者：MrPython (赞：2)

来个愉快的扫描线。

我们先按照题意，把不合法的情况画到平面直角坐标系上：
![1710064201246.png](https://img2.imgtp.com/2024/03/10/hUc0jijC.png)
所有合法的情况都不应该出现在该直线上。另外，题目保证 $u_i<v_i$，所以所有的合法点都应该出现在直线 $y=x$ 上方。

所有的合法的点出现的地方可以分成 6 个部分。我们进行 3 次扫描线：
1. 沿 x 正方向，处理每个点 ➀➁➂ 的部分
2. 沿 y 负方向，处理每个点 ➂➃➄ 的部分
3. 沿 y 正方向，处理每个点 ➅ 的部分。

以第一次扫描为例，拿 multimap 存下所有扫过的点的 y 坐标和编号。使用 [`std::multimap::upper_bound`](https://zh.cppreference.com/w/cpp/container/multimap/upper_bound) 查找、判断三个区间内第一个点。接下来相信对于熟练掌握扫描线算法的同学没有任何难度了。

```
#include<bits/extc++.h>
using namespace std;
namespace pbds=__gnu_pbds;
using ui=unsigned int;
using uli=unsigned long long int;
using li=long long int;
int main(void){
    ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr);
    ui m;size_t n;cin>>m>>n;++m;
    vector<pair<ui,ui>> a(n);
    vector<size_t> ans(n,~0);
    for (pair<ui,ui>& i:a) cin>>i.first>>i.second;
    {   // 沿 x 轴方向从左到右扫，处理 ➀➁➂
        vector<vector<pair<ui,size_t>>> s(m);
        for (size_t i=0;i<n;++i) s[a[i].first].emplace_back(a[i].second,i);
        multimap<ui,size_t> vis;
        for (size_t i=0;i<m;++i){
            for (pair<ui,size_t> const& j:s[i]){
                // 当前点 x 坐标为 i, y 坐标为 j.first, 编号 j.second
                multimap<ui,size_t>::const_iterator it;
                it=vis.cbegin(); // ➀
                if (it!=vis.cend()&&it->first<i) ans[j.second]=it->second;
                it=vis.upper_bound(i); // ➁
                if (it!=vis.end()&&it->first<j.first) ans[j.second]=it->second;
                it=vis.upper_bound(j.first); // ➂
                if (it!=vis.end()) ans[j.second]=it->second;
            }
            for (pair<ui,size_t> const& j:s[i])
                vis.insert(j);
        }
    }{   // 沿 y 轴方向从上到下扫，处理 ➂➃➄
        vector<vector<pair<ui,size_t>>> s(m);
        for (size_t i=0;i<n;++i) s[a[i].second].emplace_back(a[i].first,i);
        multimap<ui,size_t> vis;
        for (size_t i=m-1;i<m;--i){
            for (pair<ui,size_t> const& j:s[i]){
                // 当前点 x 坐标为 j.first, y 坐标为 i, 编号 j.second
                multimap<ui,size_t>::const_iterator it;
                it=vis.cbegin(); // ➂
                if (it!=vis.cend()&&it->first<j.first) ans[j.second]=it->second;
                it=vis.upper_bound(j.first); // ➃
                if (it!=vis.end()&&it->first<i) ans[j.second]=it->second;
                it=vis.upper_bound(i); // ➄
                if (it!=vis.end()) ans[j.second]=it->second;
            }
            for (pair<ui,size_t> const& j:s[i])
                vis.insert(j);
        }
    }{   // 沿 y 轴方向从下到上扫，处理 ➅
        vector<vector<pair<ui,size_t>>> s(m);
        for (size_t i=0;i<n;++i) s[a[i].second].emplace_back(a[i].first,i);
        multimap<ui,size_t> vis;
        for (size_t i=0;i<m;++i){
            for (pair<ui,size_t> const& j:s[i]){
                // 当前点 x 坐标为 j.first, y 坐标为 i, 编号 j.second
                multimap<ui,size_t>::const_iterator it;
                it=vis.upper_bound(j.first); // ➅
                if (it!=vis.end()) ans[j.second]=it->second;
            }
            for (pair<ui,size_t> const& j:s[i])
                vis.insert(j);
        }
    }
    for (size_t i:ans) cout<<i+1<<' ';
    return 0;
}
```

---

## 作者：operator_ (赞：1)

# P10247 Pairing Pairs

[题目传送门](https://www.luogu.com.cn/problem/P10247)

**upd:修改了复杂度分析和代码。**

## 题解

随机化。

将其看成图（不用建出来），考虑每条边两端点的度数，则 $d_u+d_v-1$ 就是不可行的边的数量，若均不可行直接判掉。如果 $d_u\le\dfrac{m}{4},d_v\le\dfrac{m}{4}$，那么我们多次随机，$k$ 次还找不到正确答案的概率小于 $\dfrac{1}{2^k}$，可以计算出期望 $O(1)$。

否则，一定有一个端点的度数 $>\dfrac{m}{4}$，由于图上所有点的度数和是 $2m$，所以这样的点最多只有 $8$ 个，考虑拎出来特殊对待。假设当前在考虑 $u$，把不与 $u$ 直接相连的边拿出来，然后对于所有其它点 $v$，遍历这些边，那么最多 $d_v+1$ 次寻找到合法的边，总复杂度 $\sum d=O(m)$。

两个算法合一块儿就做完了。

这个 $\dfrac{m}{4}$ 只是用于复杂度分析，实际使用中好像 $50000$ 级别左右的数都有很好的表现（毕竟是乱搞嘛）

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int rd() {
    int s=0,m=0;char ch=getchar();
    while(!isdigit(ch)) {if(ch=='-')m=1;ch=getchar();}
    while( isdigit(ch)) s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
    return m?-s:s;
}
int T; 
int n,m,u[300005],v[300005],d[300005],ans[300005];
vector<int> tmp;
bool chk(int i,int j) {
    return u[i]!=u[j]&&u[i]!=v[j]&&v[i]!=u[j]&&v[i]!=v[j];
}
signed main(){
    srand(time(0));
    cin>>n>>m;T=m/4;
    for(int i=1;i<=m;i++) 
        d[u[i]=rd()]++,d[v[i]=rd()]++;
    for(int i=1;i<=n;i++) {
        if(d[i]>T) {
            tmp.clear();
            for(int j=1;j<=m;j++) if(u[j]!=i&v[j]!=i) 
                tmp.push_back(j);
            for(int j=1;j<=m;j++) {
                if(v[j]==i) swap(u[j],v[j]);
                if(u[j]==i) for(int k=0;k<tmp.size();k++)
                    if(u[tmp[k]]!=v[j]&&v[tmp[k]]!=v[j]) 
                        {ans[j]=tmp[k];break;}
            }
        }
    }
    for(int i=1;i<=m;i++) {
        if(d[u[i]]+d[v[i]]-1==m) printf("0 ");
        else if(ans[i]) printf("%lld ",ans[i]);
        else {
            int id=rand()%m+1;
            while(!chk(id,i)) id=rand()%m+1;
            printf("%lld ",id);
        }
    }
    return 0;
}
```

---

