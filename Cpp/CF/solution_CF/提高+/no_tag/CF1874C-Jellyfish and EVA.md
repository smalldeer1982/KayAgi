# Jellyfish and EVA

## 题目描述

Monsters have invaded the town again! Asuka invites her good friend, Jellyfish, to drive EVA with her.

There are $ n $ cities in the town. All the monsters are in city $ n $ . Jellyfish and Asuka are currently in city $ 1 $ and need to move to city $ n $ to defeat the monsters.

There are $ m $ roads. The $ i $ -th road allows one to travel from city $ a_i $ to city $ b_i $ . All the roads are directed. That is, one cannot travel from city $ b_i $ to $ a_i $ using the $ i $ -th road. Interestingly, all roads satisfy $ a_i<b_i $ .

Driving EVA requires two people to work together. However, Asuka and Jellyfish have not done any training together before.

Suppose that EVA is currently in city $ u $ . Jellyfish and Asuka will both choose an undestroyed road that starts at city $ u $ . Suppose Jellyfish and Asuka choose roads that end at cities $ v_1 $ and $ v_2 $ respectively. If $ v_1 = v_2 $ , EVA moves to city $ v_1 $ successfully. Otherwise, EVA stays in city $ u $ and both roads that they have chosen will be destroyed.

It is possible that EVA is currently in city $ u $ ( $ u \neq n $ ) and there are no undestroyed roads that start at city $ u $ . In that case, the mission will be a failure. Otherwise, if they reach city $ n $ in the end, the mission is considered a success.

Every time they choose the roads, Jellyfish knows that Asuka will choose a road randomly. Now, Jellyfish wants to know, if she chooses the roads optimally, what is the maximum probability of the mission being successful.

## 说明/提示

In the first test case, Jellyfish will choose $ v_1=3 $ , and Asuka will choose $ v_2=2 $ with a possibility of $ 0.5 $ and $ v_2=3 $ with a possibility of $ 0.5 $ . The mission is considered a success with a possibility of $ 0.5 $ .

## 样例 #1

### 输入

```
3
3 2
1 2
1 3
7 8
1 2
1 3
1 4
1 5
2 6
3 6
4 6
6 7
10 20
1 2
1 3
1 4
1 5
1 6
2 6
2 7
2 8
2 9
3 4
3 7
3 8
3 10
4 6
4 8
4 10
6 10
7 8
7 9
7 10```

### 输出

```
0.500000000000
0.625000000000
0.491666666667```

# 题解

## 作者：Ray662 (赞：16)

[Luogu](https://www.luogu.com.cn/problem/CF1874C) | [Codeforces](https://codeforces.com/problemset/problem/1874/C)

### 题目大意

有一张 $n$ 个点 $m$ 条边的有向图，任意一条边 $u\rightarrow v$ 满足 $u<v$。

你在点 $1$，可以进行若干次移动。对于每次从点 $u$ 开始的移动，你需要遵循以下规则：

首先，选择一个 $u$ 的出点 $v$。

然后，从所有 $u$ 未被销毁的出点中等概率随机选择一个出点 $w$。若 $v=w$，则移动到 $v$；否则销毁 $(u,v),(u,w)$ 两条边，之后不能再走也不会在任何情况下被考虑到。

从点 $1$ 开始走，在每个点 $u$ 选择最优的点 $v$，使得成功走到点 $n$ 的概率最大。输出此概率。

$n\leq 5\times 10^3,m\leq 2\times 10^5$。

### 思路

首先设 DP 状态。

我们不妨设 $f_i$ 表示在全局最优解下从节点 $i$ 走到 $n$ 的概率。

对于每个节点 $u$，它的每个后继节点 $v$ 都有 $f_v$ 属性，按照题目要求：

- 当 $u \to v$ 这条边仍然保留时：我们肯定会优先选择 $f_v$ 最大的 $v$。

- 否则如果 $u \to v$ 已被删除：将会在剩下的 $v$ 中选择最优的点（$f_v$ 最大）。

- 重复以上过程，直到前往下一个节点或者停止操作。

我们可以先写一个转移方程：

$$
f_u = \sum_{(u \to v) \in E} f_v \times p_{u \to v}
$$

其中 $p_{u \to v}$ 表示 $u$ 前往 $v$ 的概率。

为了表示 $p$，我们定义 $g_{i, j}$ 表示对于一个出度为 $i$ 的节点 $u$，前往第 $j$ 优的后继节点的概率。

那么上面的式子可以写成：

$$
f_u = \sum_{(u \to v_i) \in E} f_{v_i} \times g_{d_u, i}
$$

其中 $v$ 为 $u$ 的后继节点，$f_{v_1} \ge f_{v_2} \ge  \cdots \ge f_{v_{d_u}}$，$d_u$ 表示 $u$ 的后继节点个数。

那么为了推出答案 $f_1$，我们需要求出 $g$。

可以发现，$g$ 的取值和具体是哪个 $u$ 无关，只和出度以及优先度有关。因此它可以预处理出来。

考虑如何预处理 $g$。

对于优先度最高的后继节点，成功前往它的概率是 $\frac{1}{d}$。所以 $g_{i, 1} = \frac{1}{d}$。

那么对于 $g_{i, j}(j > 1)$，我们如何转移？

分类讨论，删除边存在两种情况：

- **情况一：**

![](https://cdn.luogu.com.cn/upload/image_hosting/z3qds6bu.png?x-oss-process=image/resize,m_lfit,h_680,w_900)

$k < j$，$u$ 的后继结点 $k$ 优于 $j$，此时我们可以从 $g_{i - 2, j - 2}$ 转移到 $g_{i, j}$（删去 $1$ 和 $k$ 后，$j$ 从原来的第 $j$ 优变为了 $j - 2$ 优）。

那么走这条边的概率是多少呢？

由于 $1 < k < j$，那么 $k$ 一共有 $j - 2$ 种选择，一共 $i$ 条出边，所以 $p_{u \to j} = \frac{j - 2}{i}$。

该情况对 $g_{i, j}$ 的贡献为：

$$
g_{i - 2, j - 2} \times \frac{j - 2}{i}
$$

- **情况二：**

![](https://cdn.luogu.com.cn/upload/image_hosting/3vrq62kp.png?x-oss-process=image/resize,m_lfit,h_680,w_900)

$k > j$，$k$ 的优先度低于 $j$。那么选择该边的概率为 $\frac{i - j}{i}$（$j$ 后面的点都可以选）。

原来的第 $j$ 优变为了第 $j - 1$ 优，故从 $g_{i - 2, j - 1}$ 转移过来。

所以该情况对 $g_{i, j}$ 的贡献为：

$$
g_{i - 2, j - 1} \times \frac{i - j}{i}
$$

综上：

$$
g_{i, j} = g_{i - 2, j - 2} \times \frac{j - 2}{i} + g_{i - 2, j - 1} \times \frac{i - j}{i}
$$

所以做完了。

**做法综述：**

1. 预处理 $g$。

2. 读入，根据给出的图算出 $f$。

3. 答案为 $f_1$。

时空复杂度 $O(n^2 + m \log m)$。

[AC CODE](https://codeforces.com/contest/1874/submission/277264411)

---

### 注意事项

- 多组数据，记得清空；

- 计算 $f$ 应当从 $n$ 到 $1$（每条边 $u \to v$ 满足 $u < v$）。

- 记得用 double，注意输出 double 的精度。

---

### 其他

希望这篇题解能给您带来帮助。

感谢 @[wjwWeiwei](https://www.luogu.com.cn/user/547295) 对本篇题解的巨大贡献。

---

## 作者：eastcloud (赞：14)

很好的概率 dp，爱来自瓷器。

题目要求我们求出到达终点概率的最大值，我们肯定先得考虑如何安排方案能使概率最大化。

一个显然的想法将能到达的点按照到达终点的概率从大到小排序，依次选择，但是这样会不会出现把它安排到后面，当竞争对手减少的时候再选择更优的情况呢？

假设当前有 $n$ 个数，那么我们安排其为第一个数且其被二者都选中的概率为 $\frac{1}{n}$，安排为第一个失败后第二个选且被选中的概率为 $\frac{n-2}{n} \times \frac{1}{n-2}$。

第三个及其之后的概率不太好算，但是我们可以发现这个概率式子是不依赖真实点值的，只与当前点的出度有关，我们完全可以先算出概率之后将其排序，第几个概率大就安排对应点在第几个即可。

考虑如何计算此概率，手推一下可以发现这个概率计算类似递归，不同的结果会归到不同的子问题上算，这启发我们使用 dp 解决。

设计 $f_{i,j}$ 表示当节点出度为 $i$ 且我要第 $j$ 个选择的节点被选上的概率是多少，初始条件为若 $j=1$ 那么 $f_{i,j}=\frac{1}{i}$，转移为 $f_{i,j}=f_{i-2,j-2}\times \frac{j-2}{i} + f_{i-2}{j-1} \times \frac{i-j}{i}$。

转移式子如上是因为我方肯定选备选序列中第一个节点，对方如果选了 $j$ 以前的节点那么贡献为前半段，否则为后半段，预处理出概率式子并拓扑 dp 就可以做到 $O(n^2 \log n + n \log m)$。

实际上，我们把概率的表打出来就可以发现它一定单调递减，可以免去 $n^2$ 后面那个 $\log$，但是具体证明我不是很会 /wul，有会的可以在评论区补充一下。

```cpp
// Problem: Jellyfish and EVA
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1874C
// Memory Limit: 500 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<vector> 
#define ll long long
#define N 5005
#define M 500005
using namespace std;
double prob[N][N],f[N];
int e,nex[M<<1],head[M<<1],to[M<<1],sta[N],tp;
void add(int u,int v){
	to[++e]=v;nex[e]=head[u];head[u]=e;
}
void init(){
	prob[1][1]=1;prob[2][1]=0.5;
	for(int i=3;i<N;i++){
		prob[i][1]=1.0/i;
		for(int j=2;j<=i;j++){
			prob[i][j]=(j-2)*1.0/i*prob[i-2][j-2]+(i-j)*1.0/i*prob[i-2][j-1];
		}
	}
}
bool cmp(int x,int y){
	return f[x]>f[y];
}
int main(){
	init();
	int t;cin>>t;
	while(t--){
		int n,m;cin>>n>>m;
		for(int i=1;i<=m;i++){
			int u,v;cin>>u>>v;
			add(u,v);
		}
		f[n]=1;
		for(int i=n-1;i>=1;i--){
			tp=0;f[i]=0;
			for(int j=head[i];j;j=nex[j])sta[++tp]=to[j];
			sort(sta+1,sta+tp+1,cmp);
			for(int j=1;j<=tp;j++)f[i]+=f[sta[j]]*prob[tp][j];
		}
		printf("%.12lf\n",f[1]);
		for(int i=1;i<=e;i++)to[i]=nex[i]=0;
		for(int i=1;i<=n;i++)head[i]=0;
	}
}

```


---

## 作者：User_Unauthorized (赞：12)

## 题意

给定一个有向无环图，对于任意一条边 $(u_i, v_i)$，有 $u_i < v_i$。

定义一次从节点 $u$ 开始的移动为如下过程：

1. $\tt{Alice}$ 选择从 $u$ 出发的且未被删除的一条边。

2. $\tt{Bob}$ 在从 $u$ 出发的且未被删除的边中等概率随机选择一条。

3. 若两人选择的边相同，则向这条边移动，否则继续选择。

如果不存在从当前节点 $u$ 出发且未被删除的边，那么定义此次移动是失败的。

若 $\tt{Alice}$ 采取最优策略，求他们实现移动 $1 \rightarrow n$ 的概率。

（$1 \le n \le 5000$）。

## 题解

[$\tt{cnblogs}$](https://www.cnblogs.com/User-Unauthorized/p/solution-CF1874C.html)


定义 $f_u$ 代表从节点 $u$ 实现移动 $u \rightarrow n$ 的最大化概率，那么可见答案为 $f_1$，由于特殊的边的限制，从 $1$ 到 $n$ 显然是一个合法的拓扑序，逆序遍历转移一定合法，下面考虑如何转移。

设 $d = \operatorname{degree}_u$，定义从 $u$ 出发的所有边的终点依次为 $v_1, v_2, \cdots, v_d$，将其按 $f_v$ 为关键字降序排列得到序列 $v$。

可以发现，若 $\tt{Alice}$ 选择边的方案钦定，那么可以得出移动到每个终点的概率，设有长度为 $d$ 的序列 $p$，其中 $p_1$ 表示移动到 $v_1$ 的概率，那么我们有

$$f_u = \sum\limits_{i = 1}^{d}f_{v_i} \cdot p_i$$

那么采取最优操作的实质即为通过改变操作序列来最大化上述和式的值。

由于在任意一次选择中，每个点被 $\tt{Bob}$ 选择的概率相等，那么显然选择 $f$ 值最大的终点可以获得更大的概率。这样我们就得到了最优操作的策略：选择 $f$ 值最大的终点。

设 $g_i$ 表示在有 $i$ 个点的情况下的最优 $p$ 序列，那么有

$$\begin{aligned}
g_1 &= \left[1.0\right] \\
g_1 &= \left[0.5, 0.0\right] \\
\end{aligned}$$

对于 $i > 2$ 的情况，根据上述策略，我们可以发现 $\tt{Alice}$ 第一次选择的点一定为 $v_1$，那么我们有

$$\begin{aligned}
g_{i, 1} &= \dfrac{1}{i} && (i > 1)
\end{aligned}$$

对于 $j > 1$，那么第一次显然不可能成功移动到 $v_j$。若最终成功移动到了 $v_j$，那么有第一次移动一定失败且 $v_j$ 没有被删除。那么此时我们可以从 $i - 2$ 个节点的状态转移答案。考虑通过枚举除 $v_1$ 外被删除的节点来实现转移，设另外一个被删除的节点为 $v_k$，那么有

- 若 $j < k$，那么 $v_j$ 从当前的第 $j$ 优节点转化为 第 $j - 1$ 优节点，有转移 $g_{i, j} \leftarrow g_{i - 2, j - 1} (j < k)$。

- 若 $k < j$，那么 $v_j$ 从当前的第 $j$ 优节点转化为 第 $j - 2$ 优节点，有转移 $g_{i, j} \leftarrow g_{i - 2, j - 2} (k < j)$。

发现具体的转移与 $k$ 无关，通过计算 $j < k$ 的概率和 $k > j$ 的概率即可完成转移，有转移式

$$g_{i, j} = 
\begin{cases}
\dfrac{1}{i} & j = 1 \\
\dfrac{j - 2}{i} \times g_{i - 2, j - 2} + \dfrac{i - j}{i} \times g_{i - 2, j - 1} & \text{otherwise.}
\end{cases}$$

预处理出 $g$ 数组即可实现转移，复杂度 $\mathcal{O}(n^2)$，可以通过本题。

## Code

```cpp
#include <bits/stdc++.h>

typedef long long valueType;
typedef std::vector<valueType> ValueVector;
typedef std::vector<ValueVector> ValueMatrix;
typedef long double realType;
typedef std::vector<realType> RealVector;
typedef std::vector<RealVector> RealMatrix;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    valueType T;

    std::cin >> T;

    for (int testcase = 0; testcase < T; ++testcase) {
        valueType N, M;

        std::cin >> N >> M;

        RealMatrix G(N + 1, RealVector(N + 1, 0));

        for (valueType i = 1; i <= N; ++i) {
            G[i][1] = (realType) 1 / i;

            for (valueType j = 2; j <= i && i - 2 > 0; ++j)
                G[i][j] = G[i - 2][j - 2] * (j - 2) / i + G[i - 2][j - 1] * (i - j) / i;
        }

        ValueMatrix Graph(N + 1);

        for (valueType i = 0; i < M; ++i) {
            valueType u, v;

            std::cin >> u >> v;

            Graph[u].push_back(v);
        }

        RealVector F(N + 1, 0);

        F[N] = 1;

        for (valueType i = N - 1; i >= 1; --i) {
            auto const degree = (valueType) Graph[i].size();

            RealVector to;

            to.reserve(degree);

            for (auto const &iter: Graph[i])
                to.push_back(F[iter]);

            std::sort(to.begin(), to.end(), std::greater<>());

            F[i] = 0;

            for (valueType j = 1; j <= degree; ++j)
                F[i] += G[degree][j] * to[j - 1];
        }

        std::cout << std::fixed << std::setprecision(10) << F[1] << std::endl;
    }

    return 0;
}
```

---

## 作者：SunsetGlow95 (赞：3)

# 题解 - CF1874C Jellyfish and EVA

## 题意简述

给定一个 $n$ 点 $m$ 边的 DAG，拓扑序为 $1\sim n$（无重边）。一个物体初始位置在点 $1$，目标是去到点 $n$。

每当这个物体不在终点而在点 $u$ 时，会分别选择 $u$ 的出边 $u\to v_1$ 和 $u\to v_2$。若 $v_1=v_2$ 则此物体移动到点 $v_1$，否则原地不动并毁去 $u\to v_1$ 和 $u\to v_2$ 两条边。其中 $v_1$ 总是随机选择，但是可以有策略地选择 $v_2$。

求这个物体成功到达点 $n$ 的最大概率。

$2\le n\le 5000$，$0\le m\le\min(\frac{n(n-1)}{2}, 2\times 10^5)$。

## 解法

不难想到令 $f_u$ 表示当前在点 $u$ 成功到达点 $n$ 的几率，然后做 DAG 上 dp。转移大概形如 $f_u=\sum a_vf_v$，其中 $a_v$ 表示某个系数。边界是 $f_n=1$。

这个系数似乎没有简单求法。但是对于每个出边数 $k$，都有一个唯一对应的系数序列 $a_k$。要最优化决策，实际上就是把最大的 $a_{k,i}$ 对应最大的 $f_v$，次大的对应次大的，依此类推。上面的递推式大概可以写成 $f_u=\sum_{i=0}^{k-1} a_{k,i}f_{v_i}$，其中将出点按 $f$ 值从大到小排序，$a_k$ 也按从大到小排序（下标从 $0$ 开始）。

我们想要求 $a_{i,j}(0\le j<i)$。

边界，有 $a_{1,0}=1$。$i=0$ 时即没有出路，$a_0$ 和为 $0$。

对于 $i>1$，第一次操作，有 $a_{i,0}=\frac{1}{i}$，即只要求随机选的出点恰好一致。

对于更大的 $j$，由于第一次操作失败才会考虑，这样的情况都化为 $i-2$ 的情景。转移的依据就是第一次操作中随机删的点在 $j$ 之前或之后。

有 $a_{i,j}=a_{i-2,j-2}\times\frac{j-1}{i} + a_{i-2,j-1}\times\frac{i-j-1}{i}$。（编写代码时注意边界）

时间复杂度：预处理 $a$ 的时间是 $O(n^2)$，每组数据对每个点都要做一次出边的排序，所以是 $O(n+m\log n)$。

启示：对于难求的系数，考虑 dp 预处理。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int MXN = 5005;
const int MXM = 200005;
double prob[MXN][MXN], dp[MXN];
int T, N, M;
int to[MXM], nxt[MXM], head[MXN], egsz;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  prob[1][0] = 1;
  for (int i(2); i != MXN; ++i) {
    prob[i][0] = 1.0 / i;
    for (int j(1); j != i; ++j) {
      if (j - 1 < i - 2) prob[i][j] += prob[i - 2][j - 1] * (i - j - 1) / i;
      if (j >= 2) prob[i][j] += prob[i - 2][j - 2] * (j - 1) / i;
    }
  }
  cin >> T;
  while (T--) {
    cin >> N >> M;
    fill(head, head + N, -1);
    egsz = 0;
    for (int x(0), y(0); M--;)
      cin >> x >> y, --x, --y, to[egsz] = y, nxt[egsz] = head[x],
                               head[x] = egsz++;
    dp[N - 1] = 1;
    for (int i(N - 2); ~i; --i) {
      dp[i] = 0;
      vector<double> vec;
      for (int j(head[i]); ~j; j = nxt[j]) vec.emplace_back(dp[to[j]]);
      sort(vec.begin(), vec.end(), greater<double>());
      for (int j(0); j != vec.size(); ++j)
        dp[i] += vec[j] * prob[vec.size()][j];
    }
    cout << setprecision(10) << fixed << dp[0] << endl;
  }
  return 0;
}
```

---

## 作者：晴空一鹤 (赞：2)

### 闲话

模拟赛能做出 *2800 的智慧题，做不出 *2300 的 dp 题。

### 题解

对手随机选取又让你制定策略，这很概率 dp。容易发现每次选道路的依据就是到达的那个点有多大概率跑到 $n$，因此考虑逆推。我们记 $f_i$ 表示 $i$ 点出发跑到 $n$ 的概率。

如何转移呢？根据直觉，我们给当前点可以走的边顺次排列起来，表示我们选边的顺序。我们记 $g_{i,j}$ 表示当前点度数为 $i$ 时走向第 $j$ 条边的概率。显然 $g_{i,1}=\frac{1}{i}$。其他情况考虑第一次我肯定选第 $1$ 条边，根据对方选的边转移：$g_{i,j}=\frac{j-2}{i}g_{i-2,j-2}+\frac{i-j}{i}g_{i-2,j-1}$。把这玩意预处理出来。

通过观察可以发现 $i$ 相等时 $g_{i,j}$ 的值单调不升，因此我们边的排列顺序即按出点的 $f$ 从大到小排列。求解时直接乘以对应概率转移即可。

---

## 作者：王熙文 (赞：2)

偶然回看这题，结果发现之前的证明思路假了。仔细想了想感觉对这题的理解加深了，所以来写一篇题解。

## 思路

首先图是一个 DAG，所以可以拓扑排序。接下来要解决下面一个问题：有 $n$ 个数，每个数有权值 $a_i$。每次需要选择一个数 $i$，系统会随机生成一个数 $j$，若 $i=j$ 则会得到 $a_i$ 的贡献并结束，否则会删除 $a_i,a_j$。求最大 $a_i$ 的期望。

结论：若 $n \not=2$，可以任选数，否则选择最大的数。

证明：当 $n=2$ 时，选择 $x$ 会得到 $\dfrac{a_x}{2}$ 的贡献，所以一定选择最大的数。否则，考虑邻项交换证明。对于操作顺序上的相邻两个数 $x,y$，满足它们不是最后两个。那么它们会产生贡献当且仅当前面没有把它们两个删除（如果删除了，因为系统是随机的，所以顺序无所谓）。设剩下的数有 $cnt$（$cnt>2$）个。如果 $x$ 在前面，贡献是 $\dfrac{1}{cnt} \cdot x + \dfrac{cnt-2}{cnt} \cdot \dfrac{1}{cnt-2} \cdot y=\dfrac{1}{cnt} \cdot (x+y)$。$y$ 在前面是一样的，所以顺序是无关的。但是上面的证明有一个问题，是默认了操作顺序一定（不会随着系统生成的数改变）。不过这个问题可以使用数学归纳法规避掉。

结合上面两种情况，一种最优的选数方案是每次选最大的数。这样就可以使用 dp 求出按这样的顺序，排名为某个数时的概率。设 $dp_{i,j}$ 表示共有 $i$ 个数，排名为 $j$ 的数产生贡献的概率是多少。对于第一个数，概率为 $\dfrac{1}{i}$。否则若系统生成的数排名小于 $j$，概率为 $\dfrac{j-2}{i} \cdot dp_{i-2,j-2}$；否则为 $\dfrac{i-j}{i} \cdot dp_{i-2,j-1}$。求出 dp 值后，将概率排序，并让每个位置乘上 dp 出来的系数即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
vector<int> e[5010];
double dp[5010];
double ycl[5010][5010];
bool cmp(int x,int y) { return dp[x]>dp[y]; }
int main()
{
	ycl[1][1]=1,ycl[2][1]=0.5;
	for(int i=3; i<=5e3; ++i)
	{
		ycl[i][1]=1.0/i;
		for(int j=2; j<=i; ++j) ycl[i][j]=1.0*(j-2)/i*ycl[i-2][j-2]+1.0*(i-j)/i*ycl[i-2][j-1];
	}
	int t; cin>>t; while(t--)
	{
		cin>>n>>m;
		for(int i=1; i<=n; ++i) e[i].clear();
		for(int i=1; i<=m; ++i)
		{
			int u,v; cin>>u>>v;
			e[u].push_back(v);
		}
		dp[n]=1;
		for(int i=n-1; i>=1; --i)
		{
			sort(e[i].begin(),e[i].end(),cmp);
			dp[i]=0;
			int cnt=0;
			for(int j:e[i]) dp[i]+=dp[j]*ycl[e[i].size()][++cnt];
		}
		printf("%.10f\n",dp[1]);
	}
	return 0;
}
```

---

## 作者：lyhqwq (赞：1)

# Solution

好题。

对于一个点的所有出边，第一个被选的数概率为 $\frac{1}{n}$，第二个被选的数的概率是 $\frac{n-2}{n(n-2)}$，第三个被选的数的概率为 $\frac{n-3}{n(n-2)}$。注意的越往后选的数概率越低，所以我们将出点走到 $n$ 的概率从大到小排序依次选即可。

令 $g_{i,j}$ 表示出度为 $i$，第 $j$ 个选的概率，有 $g_{i-2,j-2}\times\frac{j-2}{i}+g_{i-2,j-1}\times\frac{i-j}{i}$。

再令 $f_i$ 表示从 $i$ 走到 $n$ 的概率，有 $f_u=\sum\limits_{i=1}^{deg_u}f_{v_i}\times g_{deg_u,i}$。

# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e3+5;
int _;
int n,m;
vector<int> vec[N];
double f[N],g[N][N];
void init(){
    g[1][1]=1;
    for(int i=2;i<N;i++){
        g[i][1]=1.0/i;
        for(int j=2;j<=i;j++) g[i][j]=g[i-2][j-2]*(j-2)*1.0/i+g[i-2][j-1]*(i-j)*1.0/i;
    }
}
void solve(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) f[i]=0,vec[i].clear();
    for(int i=1,u,v;i<=m;i++){
        scanf("%d%d",&u,&v);
        vec[u].push_back(v);
    }

    f[n]=1;
    for(int u=n-1;u>=1;u--){
        sort(vec[u].begin(),vec[u].end(),[](int x,int y){return f[x]>f[y];});
        for(int i=0;i<vec[u].size();i++){
            int v=vec[u][i];
            f[u]+=f[v]*g[vec[u].size()][i+1];
        }
    }
    printf("%.12lf\n",f[1]);
}
int main(){
    scanf("%d",&_);
    init();
    while(_--) solve();
    return 0;
}

```

---

## 作者：Leasier (赞：1)

不难发现本题给出的图是一张 **DAG**。

考虑 dp，设 $dp_u$ 表示从 $u$ 出发到达 $n$ 的概率。

转移：设我们现在讨论 $dp_u$。

一个简单的想法是：

- 抓出所有出点 $v$。
- 将它们按照 $dp_v$ 递减排序。
- 贪心地，我们每次取 $dp_v$ 最大且可行的 $v$ 进行操作。
- 状压 dp《即可》。

看上去走不通了，考虑**算贡献**，即对于排名为 $i$ 的 $v$，我们有多大概率会走进它。

考虑递推，设 $f_{i, j}$ 表示一共有 $i$ 个选项，最终取到排名为 $j$ 的出点的概率。递推式较为简单，略去。

时间复杂度为 $O(\sum(n + m \log \min(n, m)) + N^2)$，其中 $N = 5 \times 10^3$。

代码：
```cpp
#include <iostream>
#include <algorithm>
#include <functional>
#include <cstdio>

using namespace std;

typedef struct {
	int nxt;
	int end;
} Edge;

const int N = 5e3, M = 2e5 + 7;
int cnt;
int head[N + 7];
double val[N + 7][N + 7], dp[N + 7], temp[N + 7];
Edge edge[M];

inline void init(int n){
	cnt = 0;
	for (int i = 1; i <= n; i++){
		head[i] = 0;
	}
}

inline void add_edge(int start, int end){
	cnt++;
	edge[cnt].nxt = head[start];
	head[start] = cnt;
	edge[cnt].end = end;
}

int main(){
	int t;
	cin >> t;
	for (int i = 1; i <= N; i++){
		val[i][1] = 1.0 / i;
		for (int j = 2; j <= i; j++){
			val[i][j] = (val[i - 2][j - 1] * (i - j) + val[i - 2][j - 2] * (j - 2)) / i;
		}
	}
	for (int i = 1; i <= t; i++){
		int n, m;
		cin >> n >> m;
		init(n);
		for (int j = 1; j <= m; j++){
			int a, b;
			cin >> a >> b;
			add_edge(a, b);
		}
		dp[n] = 1.0;
		for (int j = n - 1; j >= 1; j--){
			int cnt = 0;
			for (int k = head[j]; k != 0; k = edge[k].nxt){
				temp[++cnt] = dp[edge[k].end];
			}
			sort(temp + 1, temp + cnt + 1, greater<double>());
			dp[j] = 0.0;
			for (int k = 1; k <= cnt; k++){
				dp[j] += temp[k] * val[cnt][k];
			}
		}
		printf("%.12lf\n", dp[1]);
	}
	return 0;
}
```

---

## 作者：Saka_Noa (赞：1)

因为终点状态确定，所以考虑从终点往前 DP。


先解决一个小问题，如何求出对于每个点 $k$，出度为 $i$，选取第 $j$ 个点的概率。发现对于一个点 $k$，选取概率只与 $i$ 有关，我们先预处理。  
稍加思考，当我们选择第 $j$ 个点时，Asuka 可能选择前面 $j$ 个点中的一个，也可能选后 $i - j$ 个点中的一个，所以有递推式：
$$f_{i,j} = \sum_{2 \le j\le i} f_{i-2,j-1} \times \frac{i-j}{i} + f_{i-2,j-2} \times \frac{j-2}{i}$$  

然后我们贪心的让 $k$ 连向的点的期望值最大点对应上 $f_{i,j}$ 中最大的值。即我们可以构造出一个选择的顺序，使得 $f_{i,k}$ 与 $dp_{s \in son_k}$ 最大值两两对应，次大值两两对应 $\cdots$。


```cpp

#include<bits/stdc++.h>


using namespace std;
typedef double dl;

const int N = 5050;
const int M = 2e5 + 500;

int T, n, m;
dl as[N], f[N][N];
vector<int> E[N];
vector<dl> vc;


void solve() {
    for(int i = 1; i < N; ++i) as[i] = 0, E[i].clear();

    scanf("%d %d", &n, &m);
    for(int i = 1; i <=  m; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        E[u].push_back(v);
    }

    as[n] = 1;
    for(int i = n - 1; i; --i) {
        vc.clear();
        for(auto P : E[i]) vc.push_back(as[P]);
        sort(vc.begin(), vc.end(), greater<dl>());
        for(int j = 0; j < vc.size(); ++j) as[i] += vc[j] * f[vc.size()][j + 1];
    }

    printf("%.12lf\n", as[1]);
}

int main() {

    for(int i = 1; i < N; ++i) {
        f[i][1] = 1;
        for(int j = 2; j < i; ++j) {
            f[i][j] += f[i - 2][j - 1] * (i - j);
        }
        for(int j = 2; j <= i; ++j) {
            f[i][j] += f[i - 2][j - 2] * (j - 2);
        }
        for(int j = 1; j < N; ++j) f[i][j] /= i;
        
    }

    scanf("%d", &T);    
    while(T--) solve();


    return 0;
}

```

---

## 作者：鲤鱼江 (赞：0)

套路题。

首先发现题目中给了一个 DAG（有向且无环），又发现由终点走向终点的概率是 $1$（即终点状态确定），所以套路地想到建反边拓扑做 DP。

然后考虑在一个点选择怎样的方案到达终点的概率最大，不难发现每一次贪心地选择概率最大的点一定不劣。关于这个结论不知道也没关系，后面可以不用，只是用了之后代码更好写，不过感性理解的话，你这个节点越到后面越容易被替代掉，条件越到后面越苛刻。

现在我们发现，我们只需要知道每一个点的被选中的概率，就能解决问题了，这一部分考虑分开 DP。

具体地，我们设 $dp_{i,j}$ 表示有 $i$ 个节点，选择优先级为 $j$ 的节点的概率（即有 $j-1$ 个节点要比其优先选）。

$$
dp_{i,j}=\begin{cases}  	\frac 1i & j=1 \\
\frac{j-2}{i}dp_{i-2,j-2}+\frac{i-j}{i}dp_{i-2,j-1}& otherwise\end{cases}
$$

有如上 DP 式，$j=1$时组合意义显然，对于其他情况组合意义为：每次删去优先级最小点后，必然会多删一个点，这个点有 $\frac{j-2}{i}$ 的概率在当前点的前面，有 $\frac{i-j}{i}$ 的概率在后面。

以上 DP 式可以提前预处理出来 $O(n^2)$。

你可以为了求稳，把走到终点概率大的点与 $dp$ 数组中概率较大的点匹配起来，但是发现 $dp$ 数组中的值单调不增，正好应对了上面的结论，所以没必要。

```cpp
#include<bits/stdc++.h>

using namespace std;

namespace Fread {
	const int SIZE=1<<21;char buf[SIZE],*S,*T;
	inline char getchar() {if(S==T){T=(S=buf)+fread(buf,1,SIZE,stdin);if(S==T)return '\n';}return *S++;}
}
namespace Fwrite {
	const int SIZE=1<<21;
	char buf[SIZE],*S=buf,*T=buf+SIZE;
	inline void flush(){fwrite(buf,1,S-buf,stdout);S=buf;}
	inline void putchar(char c){*S++=c;if(S==T)flush();}
	struct POPOSSIBLE{~POPOSSIBLE(){flush();}}ztr;
}
#define getchar Fread :: getchar
#define putchar Fwrite :: putchar
namespace Fastio{
	struct Reader{
	    template<typename T>
    	Reader& operator >> (T& x) {
        	char c=getchar();T f=1;
        	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}x=0;
        	while(c>='0'&&c<='9'){x=x*10+(c-'0');c=getchar();}x*=f;
	        return *this;
    	}
	    Reader(){}
	}cin;
}
#define endl '\n'
#define cin Fastio :: cin

const int N=5e3+10;
struct edge{
	int to,ne;
	edge(int to=0,int ne=0):
		to(to),ne(ne){;}
}a[N<<1];
int n,T,m,cnt,h[N];
vector < double > v[N];
double dp[N][N],f[N];

inline void add(const int x,const int y){a[++cnt]=edge(y,h[x]);h[x]=cnt;}
inline void clear(){for(int i=1;i<=n;++i){v[i].clear();h[i]=0;f[i]=0.0;}cnt=0;}
inline void init(const int len){
	dp[1][1]=1;
	for(int i=2;i<=len;++i){
		dp[i][1]=1.0/i;
		for(int j=2;j<=i;++j){
			dp[i][j]=dp[i-2][j-2]*(j-2)/i+dp[i-2][j-1]*(i-j)/i;
		}
	}
}

int main(){
	init(5000);cin>>T;
	while(T--){
		cin>>n>>m;
		for(int i=1,x,y;i<=m;++i){cin>>x>>y;add(y,x);}
		f[n]=1;
		for(int x=n;x;--x){
			sort(v[x].begin(),v[x].end());
			reverse(v[x].begin(),v[x].end());
			for(int i=0;i<(int)v[x].size();++i) f[x]+=v[x][i]*dp[v[x].size()][i+1];
			for(int i=h[x];i;i=a[i].ne) v[a[i].to].emplace_back(f[x]);
		}
		cout<<fixed<<setprecision(12)<<f[1]<<endl;
		clear();
	}
	return 0;
}
```

---

