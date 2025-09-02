# The Doctor Meets Vader (Medium)

## 题目描述

多亏了博士的帮助，叛军才偷到了足够的黄金，对帝国发动了全面进攻！然而，达斯-维德正在复仇，想要夺回他的黄金。

叛军把黄金藏在了银河系的各个基地。达斯-维达和帝国希望派出飞船攻击这些基地。

银河系可以表示为一个无向图，其中有 $ n $ 个星球（节点）和 $ m $ 个虫洞（边），每个虫洞连接两个星球。

共有 $ s $ 帝国飞船和 $ b $ 反叛军基地分布在银河系的不同星球上。

每艘飞船都有一个位置 $x$，表示所在星球的索引，一个攻击力 $a$，以及一定量的燃料 $f$。

每个基地都有一个位置 $ x $ 和一个防御强度 $ d $。

如果这两个条件都满足，飞船就可以攻击基地：

- 飞船的攻击力大于或等于基地的防御力
- 飞船的燃料大于或等于飞船所在星球与基地所在星球之间的最短距离（以虫洞数量计算）。

维达对他的攻击阵型非常讲究。他要求每艘飞船最多攻击一个基地，每个基地最多由一艘飞船攻击。

维达知道叛军在每个基地都藏有 $k$ 美元的黄金，因此他会分配飞船去攻击基地，使被攻击的基地数量最大化。

因此，每攻击一个基地，反叛军就会损失 $k$ 美元黄金。

不过，叛军有能力制造任意数量的假基地。在博士的帮助下，这些基地将超越时空存在，因此所有飞船都可以到达并攻击它们。此外，假基地的设计看起来似乎是不可抗拒的：也就是说，它总是会受到一些飞船的攻击。

当然，假基地不包含任何黄金，但创建这样一个假基地需要花费 $h$ 美元黄金。

如果叛军创建了最佳数量的假基地，他们最少会损失多少黄金？

## 说明/提示

使成本最小化的一种方法是建造 $4$ 个 $3$ 美元的虚拟基地，总成本为 $4\times 3 = 12$ 美元。

一艘帝国飞船将被分配去攻击每个假基地，结果是实际被攻击的基地为零。

## 样例 #1

### 输入

```
6 7
1 2
2 3
3 4
4 6
6 5
4 4
3 6
4 2 7 3
1 10 2
3 8 2
5 1 0
6 5 4
3 7
5 2
```

### 输出

```
12
```

# 题解

## 作者：huangrenheluogu (赞：0)

[洛谷题面](https://www.luogu.com.cn/problem/CF1184B2)。

[Codeforces 题面](https://codeforces.com/problemset/problem/1184/B2)。

发现 $n,s,b$ 都很小，属于 $\mathcal{O}(n^2)$ 可以通过的级别。

由于飞船相等，考虑已经有一个方案，包含 $A$ 个闲置的飞船和 $B$ 个攻击的飞船，对方建立了 $C$ 个假基地我方的改变方案。

- 首先，尽量用闲置的飞船攻击假基地。

- 其次，由于攻击每一个星球对方损失 $k$ 是一定的，所以如果在上面这一条不够的情况下，我方可以抽取任意的飞船攻打假基地。

这样，一个决策就变成了删边，这个证明应该比较显然，就是贪心。

所以，对于计算出的 $A,B$，给定 $C$，对方的总消耗这么表述：

- 如果 $C\le B$，为 $C\times h+A\times k$。

- 如果 $B<C\le A$，为 $C\times h+(A-(B-C))\times k$。

发现第一种情况不如不建，所以最后判断的时候可以略去。

考虑 $s,b$ 很小，所以我们可以使用 $\mathcal{O}(sb)$ 的复杂度计算哪个飞船可以攻击哪个基地，可以攻击就连边。

然后跑二分图最大匹配，算出对方不建假基地时的 $A,B$，二分图匹配的复杂度为 $\mathcal{O}(sM)$，其中 $M$ 是上面连的边数，不难发现，$M\le sb$，所以，二分图匹配的复杂度为 $\mathcal{O}(s^2b)$。

~~由于匹配已经浪费了太多的时间~~，为了简便，后面计算 $C$ 的值可以直接枚举，不用分类讨论。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 105, M = 1e4 + 5, C = 1e3 + 5;
int n, m, u, v, fir[C], nxt[C * C], son[C * C], tot, dist[N][N], k, h, sn, bn, cnt, mat[C], ans, tag[C];
struct Spaceship{
	int x, a, f;
}a[C];
struct Basement{
	int x, d;
}b[C];
inline void add(int x, int y){
	nxt[++tot] = fir[x];
	fir[x] = tot;
	son[tot] = y;
}
inline bool dfs(int x, int tg){
	if(tag[x] == tg) return 0;
	tag[x] = tg;
	for(int i = fir[x]; i ; i = nxt[i]){
		if(!mat[son[i]] || dfs(mat[son[i]], tg)){
			mat[son[i]] = x;
			return 1;
		}
	}
	return 0;
}
signed main(){
	memset(dist, 0x3f, sizeof(dist));
	ans = dist[0][0];
	scanf("%lld%lld", &n, &m);
	for(int i = 1; i <= m; i++){
		scanf("%lld%lld", &u, &v);
		dist[u][v] = dist[v][u] = 1;
	}
	for(int i = 1; i <= n; i++) dist[i][i] = 0;
	for(int k = 1; k <= n; k++){
		for(int i = 1; i <= n; i++){
			for(int j = 1; j <= n; j++){
				dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
			}
		}
	}
	scanf("%lld%lld%lld%lld", &sn, &bn, &k, &h);
	for(int i = 1; i <= sn; i++){
		scanf("%lld%lld%lld", &a[i].x, &a[i].a, &a[i].f);
	}
	for(int i = 1; i <= bn; i++){
		scanf("%lld%lld", &b[i].x, &b[i].d);
	}
	for(int i = 1; i <= sn; i++){
		for(int j = 1; j <= bn; j++){
			if(dist[a[i].x][b[j].x] <= a[i].f && a[i].a >= b[j].d){
				add(i, j);
			}
		}
	}
	for(int i = 1; i <= sn; i++){
		if(dfs(i, i)) cnt++;
	}
	ans = k * cnt;
	for(int i = 1; i <= cnt; i++){
		ans = min(ans, (sn - (cnt - i)) * h + (cnt - i) * k);
	}
	printf("%lld\n", ans);
	return 0;
}
```

[CF 评测记录](https://codeforces.com/contest/1184/submission/236160447)

---

