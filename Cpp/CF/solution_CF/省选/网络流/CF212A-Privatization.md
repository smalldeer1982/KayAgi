# Privatization

## 题目描述

There is a developed network of flights between Berland and Beerland. All of them belong to the Berland state company BerAvia. Each flight connects some Berland city with some Beerland city. For each flight airplanes fly in both directions.

Changes are coming to Berland — the state decided to privatize BerAvia, namely, to sell out all flights to $ t $ private companies. Each of these companies wants to get the maximal number of flights, so if the Berland flights are sold unevenly, Berland can be accused of partiality. Berland Government decided to sell the flights as evenly as possible between the $ t $ companies.

The unevenness of the distribution of flights between companies is calculated as follows. For each city $ i $ (both Berland and Beerland) we'll calculate the value of

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF212A/8cb4dc3a97b60ddf7de9158fd0e56414b7e627be.png) where $ a_{ij} $ is the number of flights from city $ i $ , which belong to company $ j $ . The sum of $ w_{i} $ for all cities in both countries is called the unevenness of the distribution. The distribution with the minimal unevenness is the most even one.Help the Berland government come up with the most even distribution plan of selling flights.

## 样例 #1

### 输入

```
3 5 8 2
1 4
1 3
3 3
1 2
1 1
2 1
1 5
2 2
```

### 输出

```
4
2 1 2 1 2 1 2 2 ```

# 题解

## 作者：zghtyarecrenj (赞：8)

## CF212A Privatization

#### 题意简述

给定 $n+m$​ 个点 $k$​ 条边的二分图，左边 $n$​ 个点，右面 $m$​ 个点。现在要把每条边标号，标号为 $1\sim t$​​​。求出 对于每个点与之相邻的边中最多的标号与最少标号的数量差 的平均值。$n,m,t \le 200, k \le 5000$。

#### 题解

先上结论：

> 答案就是度数不为 $t$ 的倍数的点的个数除以 $n+m$。

首先，答案肯定不大于这个值（显然，如果度数不为 $t$ 的倍数那么 $\max - \min$ 至少为 $1$）。

然后考虑扔掉一些边使得每个点的度数都是 $t$ 的倍数。问题转化为给这个新的图标号使得每个点的标号数量都一致。

对于一个度数为 $d_i$ 的点（假设 $t|d_i$），我们应该把 $d_i$ 条边分成 $d_i/t$ 个块，每个块都有 $t$ 种标号各一个。

然后我们考虑如果新增一条边 $(u,v)$，那么我们应该给这条边标上怎样的编号。

显然在 $u$​ 的当前块中肯定至少还有一种标号没有使用。如果有多个标号没有使用，则我们可以使用任意一种。

如果这个标号在 $v$ 中也可用那么我们显然可以直接给这条边标上这个标号。但是如果 $u$ 当前块中所有可用的颜色在 $v$ 当前块中都用过了，那么我们怎么办呢？

其实已经标过号的边是可以换标号的。假设现在选取的标号是 $t_1$，令 $v$​ 中的任意一个未用的标号为 $t_2$。则我们可以把原来标号是 $t_1$ 的换成 $t_2$，如果产生冲突则继续调整（“交换”标号为 $t_1$ 和 $t_2$ 的边）。

当然，我们也能用这个结论建图网络流来构造。

```cpp
#include <bits/stdc++.h>

const int N = 405;
const int M = 1e4 + 5;

int n, m, k, t, res[M], deg[N], id[N], tot, u[M], v[M];
int f[M * 5][N];

inline int find(int x) {
    for (int i = 1; i <= t; ++i) if (!f[x][i]) return i;
}

void flip(int x, int s, int t) {
    int e = f[x][s], y = (x == u[e]) ? v[e] : u[e];
    f[x][s] = f[y][s] = 0;
    if (f[y][t]) flip(y, t, s);
    f[x][t] = f[y][t] = e, res[e] = t;
}

int main() {
    scanf("%d%d%d%d", &n, &m, &k, &t);
    for (int i = 1; i <= k; ++i) {
        scanf("%d%d", u + i, v + i); v[i] += n;
        if (deg[u[i]] % t == 0) id[u[i]] = ++tot;
        if (deg[v[i]] % t == 0) id[v[i]] = ++tot;
        ++deg[u[i]], ++deg[v[i]];
        u[i] = id[u[i]], v[i] = id[v[i]];
        int t1 = find(u[i]), t2 = find(v[i]);
        if (t1 == t2) f[u[i]][t1] = f[v[i]][t1] = i, res[i] = t1;
        else {
            if (f[u[i]][t2]) flip(u[i], t2, t1);
            f[u[i]][t2] = f[v[i]][t2] = i, res[i] = t2;
        }
    }
    int ans = 0;
    for (int i = 1; i <= n + m; ++i) if (deg[i] % t) ++ans;
    printf("%d\n", ans);
    for (int i = 1; i <= k; ++i) printf("%d ", res[i]);
    printf("\n");
    return 0;
}
```



---

## 作者：Graygoo (赞：2)

>Idivas, evo nos sudoni  
Arhan asuvi varro  
Ave - ni mach fordena  
Avis, esu si surro  
In avis, in novas, farsoni  
Invere, vesu ves ni vox  
Ire vas sumeni doni  
Est vox menidis, varro  

猜结论题，有点没意思。一般的切入点肯定是从 $t=2$ 开始，发现可以先全部搞成 $1$，然后考虑刻画把 $1$ 改成 $2$ 的过程，跑一个流即可。尝试把这个东西复制到 $k$ 更大的情况，发现没法建模，炸完了。

发动技能大瞪眼，发现答案就是度数不整除 $t$ 的节点个数，也就是说，一个节点的不平衡度不会大于 1。

那么一个自然的思路是直接调整。可惜正确性对的调整写起来非常困难，可以想到使用随机调整，跑得飞快。

接下来讲一下确定性做法。

先假设所有节点度数都是 $t$ 倍数，这时候咋办？那么每个结点的边都可以被分成若干组大小为 $t$ 的边集，我们每次取所有点的第 $i$ 组作边染色即可。

不是 $t$ 倍数的最后再跑一遍边染色即可。

---

## 作者：User_Unauthorized (赞：1)

首先可以发现，答案一定不小于

$$\sum\limits_{x} \left[t \nmid \operatorname{degree}_x\right]$$

下面我们考虑构造出一组代价为此的方案。

现在问题转化为了：给定一个二分图，给边染色，使得对于每个节点与其相连的边集中颜色出现次数的极差之和最小。

而我们有希望构造出满足上式的答案，也就是所对于每个点，我们可以将与其相连的边集差分为若干子集，其中有若干个大小恰好为 $t$ 的和不超过一个大小小于 $t$ 的集合，满足集合内边的颜色互不相同。这启示我们直接将每个节点拆分为若干节点，满足拆分出的节点中有不超过一个节点度数小于 $t$，其余的节点度数均为 $t$。

现在我们的问题变为了对拆分后的节点进行边染色，直接使用二分图边染色即可。

复杂度为 $\mathcal{O}(\left(n + m + \frac{k}{t}\right)k)$。

---

## 作者：TianyiLemon (赞：0)

来一发网络流的题解，参考 [wxh 神的代码](https://codeforces.com/contest/212/submission/34274620)。

首先答案一个显然的下界是度数不为 $t$ 的倍数的点的个数，接下来通过构造证明答案恰好等于这个值。

倒序循环 $x=t,t-1,\dots,1$，依次调用 $\mathrm{solve}(x)$。

$\mathrm{solve}(x)$ 的流程如下：

令点 $i$ 匹配数的上下界为 $\left[\left\lfloor\frac{\mathrm{deg}_i}{x}\right\rfloor,\left\lceil\frac{\mathrm{deg}_i}{x}\right\rceil\right]$，将所有尚未染色的边拿出来，跑一遍有源汇上下界可行流。可以证明存在满足条件的匹配。

接着，将所有的匹配边染成颜色 $t$，更新每个点的度数。

可以发现，对于点 $i$，上述构造得出的 $a_{i,j}$ 一定满足 $a_{i,j}\in\left[\left\lfloor\frac{\mathrm{deg}_i}{t}\right\rfloor,\left\lceil\frac{\mathrm{deg}_i}{t}\right\rceil\right]$，这里的 $\mathrm{deg}_i$ 是 $i$ 的初始度数，$a_{i,j}$ 的含义如题目所述。

并且，由于最后调用的是 $\mathrm{solve}(1)$，所以每条边都会被染色。

总共需要调用 $t$ 次 dinic 算法，实际上还是很快的。

[提交记录](https://codeforces.com/contest/212/submission/195399041)

---

