# [CEOI 2021] Newspapers

## 题目背景

译自 CEOI2021 Day1 T3. [Newspapers](https://hsin.hr/ceoi/competition/ceoi2021_day1_tasks.pdf)。


## 题目描述

Ankica 和 Branko 在一张无向连通图上玩追逐游戏，游戏分为若干个回合，每一回合有如下两步：

- **Ankica 猜测 Branko 现在在哪个结点**。具体地，她将猜测 Branko 在某个特定的结点，如果正确，Branko 被抓住，游戏将会结束，否则：
- **Branko 穿过一条边**。换句话说，Branko将移动到一个相邻的结点，注意他**不能**不移动。

给出这张图，请求出 Ankica 是否总能在有限步内抓到 Branko 且不论 Branko 初始位置在哪以及如何移动。

更形式化地，我们把 Ankica 猜测的策略用 $A=(a_1,a_2,\dots,a_k)$ 表示，其中 $a_i$ 代表她第 $i$ 次猜测 Branko 在 $a_i$ 结点。

相似地，我们把 Branko 的移动也用 $B=(b_1,b_2,\dots,b_k)$ 表示，其中 $b_i$ 代表他在第 $i$ 回合前的位置。此外，对于 $B$ 中任意两个相邻的元素 $b_i$ 和 $b_{i+1}$（$1\leq i<k$），$b_i$ 和 $b_{i+1}$ 之间必定有一条边。注意对于 $A$ 没有这样的限制。

我们认为 Ankica 的猜测策略 $A$ 是成功的，当且仅当对于任意合法的 $B$ ，都存在 $i\in[1,k]$ 使得 $a_i=b_i$。

如果存在这样的策略，请输出使得 $k$ 最小的一组策略。

## 说明/提示

#### 样例解释1

![捕获1.PNG](https://cdn.luogu.com.cn/upload/image_hosting/kajahhgy.png)

如果 Branko 初始位于 $1$ 号结点，则他会被抓住，否则他必定会移动到 $1$ 号结点，然后被抓住。

#### 样例解释2

![捕获2.PNG](https://cdn.luogu.com.cn/upload/image_hosting/rtcfz96j.png)

若 Branko 初始在环 $(1,2,3)$ 上且不与 $a_1$ 相同，则根据之后的 $a$ 必定能构造出使 $A$ 不合法的 $B$。

#### 子任务

所有测试点均满足 $1\leq N\leq 1000$，$N-1\leq M\leq \frac{N\times (N-1)}{2}$。

各子任务的约束条件如下：

| 子任务编号 | 分值 |                             限制                             |
| :--------: | :--: | :----------------------------------------------------------: |
|     $1$      |  $12$  |                       $1\leq N\leq 20$                       |
|     $2$      |  $8$   | $1\leq N\leq 1000$，$M=N-1$，且每个结点 $u\in[1，N-1]$ 都与 $u+1$ 有边 |
|     $3$      |  $80$  |                      $1\leq N\leq 1000$                      |

#### 评分细则

如果你仅能正确回答第一行，则你将得到该测试点 $50\%$ 的分数。

如果对于所有回答 `YES` 的测试点，你能提供一组 $k$ 非最小但正确的策略，你将得到该测试点 $75\%$ 的分数。注意，你提供的策略不能超过 $5N$ 轮，可以证明，任何一组最优策略都不会超出这个限制。

每个子任务的得分等于该子任务内得分最小的测试点得分。

## 样例 #1

### 输入

```
7 6
1 2
1 3
1 4
1 5
1 6
1 7
```

### 输出

```
YES
2
1 1
```

## 样例 #2

### 输入

```
6 6
1 2
2 3
3 1
1 4
2 5
3 6
```

### 输出

```
NO
```

# 题解

## 作者：Azazеl (赞：6)

## 「CEOI2021」 Newspapers 官方题解 翻译

$~~~~$ [没什么变化的阅读体验](https://www.cnblogs.com/Azazel/p/15558872.html)

$~~~~$ 看了一晚上终于勉强理解了。本质是精妙的构造。

$~~~~$ ~~我不生产题解，我只是题解的搬运工。~~

$~~~~$ 下面的翻译可能部分地方不太准确，还有部分可能会加入个人理解及勘误。也欢迎指正我的错误。

### 一、Branko 在存在环时不会被抓住

$~~~~$ 对该问题进行最简单的观察可以得到：若 Ankica 存在成功的策略，输入的图至少应该是一棵树。

$~~~~$ 为了证明这个结论，我们可以类推第二个样例。具体地，我们假定给出的图有一个环，我们可以假想 Branko 初始时在任意一个非 $a_1$ 的环上结点。由于每一个环上的结点都有两个相邻的环上结点，则第 $i$ 轮时 Branko 只需移动到与 $a_i$ 相异的结点上。

### 二、一种暴力方法

$~~~~$ 注意到 Ankica 只需掌握在每一回合前 Branko 可能存在的结点集合。当然，在游戏开始前，这个集合应该为这张图的点集。

$~~~~$ 这引导我们将游戏表示为一张所有结点都是 Branko 可能存在的点的有向图，而有向边 $(u,v)$ 则表示：若上一个回合 Branko 可能在 $u$ 结点，则下回合 Ankica 可能猜测的结点应包含 $v$ 结点。

$~~~~$ 显然，我们想找的是最短的使得这个集合从点集变为空集的路径。

$~~~~$ 这种方法的时间足以通过 Subtask1。

$~~~~$ （以下部分是译者的举例）

$~~~~$ 以样例 $1$ 为例，初始时 Branko 可能存在的结点是 $\{1,2,3,4,5,6,7\}$ ，当我们猜测 $1$ 后，相当于这一轮的集合应除去 $1$ ，然后变为其余点一步可能到达的集合，即 $\{1\}$ 。再猜测 $1$ ，集合变为空集，故该样例的最优策略为 $A=(1,1)$ 。

### 三、Branko 在链上会被抓住

$~~~~$ 现在我们将说明 Ankica 一定可以在链上抓住 Branko。

$~~~~$ 假设结点以 Subtask 2 的方式排列（即端点为 $1$ 和 $n$ 的链），现在我们将偶数点染为白色，奇数点染成黑色。

$~~~~$ 当 $N$ 为 $1$ 或 $2$ 时，我们可以轻松解决这个问题。在下面的部分我们假定 $N\geq 3$ 。

$~~~~$ 则 Ankica 有一种长为 $2N-4$ 的策略：$(2,3,\dots,N-2,N-1,N-1,N-2,\dots,3,2)$ 。不难看出若 Branko 初始时在白色结点则他会在前 $N-2$ 次猜测被抓住，否则会在后 $N-2$ 次猜测被抓住。

$~~~~$ 设想 Branko 初始时在白色结点。这样的话，在前 $N-2$ 轮 Ankica 会与 Branko 始终处于同色结点。很容易发现为了使 Branko 想在第 $i$ 回合不被抓住，必定有 $b_i>a_i$。这是由于 $b_1>a_1$ （否则 Branko 第一轮就会被抓住）而为使 $b_i$ 始终小于 $a_i$ ，必定有 $b_j=a_j+1(j<i)$ 存在（若始终保持 $b_i=a_i+2$ ，则在第 $N-2$ 轮时 Branko 无处可走——译者注），然而由于 $a_j$ 和 $b_j$ 的奇偶性始终应该是相同的，这是不可能存在的。而当 $a_{N-2}=N-1$ 时，没有在这个点之后的与 $N-1$ 同色的点，因此我们可以作出” Branko 在前 $N-2$ 轮必定会被抓住“的结论。

$~~~~$ 若 Branko 初始时在黑色结点上，前 $N-2$ 轮他会存在于与 Ankica 猜测结点颜色相异的结点上。由于第 $N-1$ 轮重复猜测同一个结点，之后 Branko 将存在于与 Ankica 猜测结点颜色相同的结点上，所以，最后 $N-2$ 轮会变为类似于前 $N-2$ 轮的情况，只是方向相反。

$~~~~$ 稍后我们将证明这个结论必定是最优的。

$~~~~$ 一种在提交中常见的策略是 $(1,2,\dots,N,N,\dots,1)$。

### 四、Branko 在一个有三叉且每条树枝长为 $3$ 的图（$S'$）上不会被抓住

$~~~~$ 在这里我们将说明 Ankica 在以下这种特定的十个结点的图上不能抓住 Branko。将中心结点记为 $10$ ，三条树枝为 $(1,2,3),(4,5,6),(7,8,9)$ ，如下图所示：

![Graph.PNG](https://i.loli.net/2021/11/16/M2hEDO7tVLigsAW.png)

$~~~~$ 我们可以说明 Branko 总可以通过偶数回合位于中心点 $10$ 或在三条树枝的中间 $(2,4,8)$ （此处疑似笔误，应为 $(2,5,8)$ ——译者注）而不被抓住。大体来说，Branko会在整场游戏中尝试尽可能靠近中心结点。

$~~~~$ 所以，如果 Branko 发现他在中心结点旁边，即 $1,4,7$ 号结点中的一个，若下回合 Ankica 不猜测 $10$ 号结点，他将移动到中心结点，否则他会移动到 $2,4,8$ （此处疑似笔误，应为 $2,5,8$ ——译者注）号结点中的一个。

$~~~~$ 如果 Branko 发现他在树枝的中间，他会向 $10$ 号结点移动，即到达 $1,4,7$ 号结点中的一个，除非 Ankica 下回合猜测的是他要移动的结点。这样的话，他不得不移动到叶子 $3,6,9$ 号结点中的一个。

$~~~~$ 显然，如果 Branko 发现他在 $3,6,9$ 号结点中的一个，依次地，他不得不移动到 $2,4,8$ 号结点。

$~~~~$ 核心想法在于，如果 Branko 发现他在中心结点，他将会移动到下一回合 Ankica 没有猜测的树枝或紧接着 Ankica 将连续猜测最靠近中心点的树枝，即 $(1,2),(4,5),(7,8)$ 。

$~~~~$ 注意到我们只需要说明当下回合 Branko 旁边的结点被猜测时他绝对不会在叶子结点即可。为了使 Branko 到达叶子结点，Ankica 必须猜测在同一树枝上的靠近中间结点的结点。如果下回合 Ankica 能抓住 Branko ，这就意味着她猜测了两个与上一次结点相邻的结点，为了实现这个目的，她本应在最后一次访问 $10$ 号结点后猜测其他树枝的一些连续结点。而这与她的猜测策略矛盾，Branko 可借此回到中心结点。 

 $~~~~$ （这两段可能翻译有点问题，下面放上原文）

> $~~~~$ The key idea is that if Branko finds himself in the central node, he will move to a branch which Ankica will not guess in the next turn, or the next branch in which Ankica wlil guess two closest nodes to the central in succession, i.e. $(1, 2)$,$ (4, 5)$, or $(7, 8)$.
>
> $~~~~$ Notice that we only need to show that Branko will never be at a leaf node when Ankica guesses its neighbour on the next turn. In order for Branko to visit a leaf node, that means that Ankica must guess the node of the same arm next to the central one in that turn. If Ankica catches Branko on the next turn, that would imply her guessing two successive nodes from the previous section. For that to be possible, she would have to have guessed such consecutive nodes of some other arm after his last visit to node $10$. This is in contradiction with the rules because during her guesses, he would have returned to the central node.

### 五、Branko 在不含 $S'$ 的图上会被抓住

$~~~~$ 总的来说，我们很好得出，若 Branko 在图 $G$ 上会被抓住，则他也会在含有导出子图 $G$ 的图 $H$ 上被抓住。（疑似有误，个人理解是在图 $G$ 上不会被抓住则在含有 $G$ 的图 $H$ 上也不会被抓住——译者注）换句话说，Branko 在不含 $S'$ 的图上不会被抓住。

$~~~~$ 有趣的是，事实证明 Ankica 在不含 $S'$ 的图上总能抓住 Branko。我们可以通过使用与解决链上问题相似的方法来解决这一点。

$~~~~$ 我们观察树上的最长路径（直径），假定其结点按顺序标号为 $1,2,\dots,l$ ，其中 $l$ 是直径的长度，我们同时也将在链上使用的染色方法进行扩展。当一个结点距离结点 $1$ 为偶数时染成白色，否则染成黑色。注意到这样会将数分成两个部分。

$~~~~$ 注意到 $2$ 和 $l-1$ 一定没有连接一条长度为 $2$ 的非直径上的链，否则这与直径定义矛盾。

$~~~~$ 最终，注意到其他结点一定没有连接长度为 $3$ 的非直径上的链，否则这要么与直径定义矛盾，要么会导致图上出现 $S'$.

$~~~~$ 这意味着所有的非叶子结点要么在直径上要么与直径上的结点相邻。这使得我们可以为 Ankica 构造出与适用于链的策略相似的一种策略。在此，Ankica 将从 $3$ 扫到 $l-2$ 并返回，但同时把所有相邻的非叶子结点计算在内。

$~~~~$ 具体来说，当她沿路线到达一个结点 $i$ 时，她会遍历所有 $i$ 的非叶子结点且非 $i+1$ 的相邻结点，在猜测 $i+1$ 前，她会在两次相邻的遍历间再次遍历结点 $i$ 。遍历结点 $l$ 后，她会返回至结点 $2$ 。

$~~~~$ 通过与在第三部分提出的相似的推理，我们可以归纳得出：当 Branko 初始在白色结点时， Ankica 总能在前半程抓住 Branko，否则她总能在后半程抓住 Branko.

### 六、最优策略

$~~~~$ 在前面部分所提到的最优策略中，我们可以把结点分为三类：叶子结点、内部结点（即 $3,\dots,l-2$）、与内部结点相邻的非叶子结点。

$~~~~$ Ankica 永远不会猜测叶子结点，会猜测两次与内部结点相邻的结点，猜测 $2f(v)-2$ 次内部结点，其中 $f(v)$ 是 $v$ 相邻的非叶结点个数。我们将会说明 Branko 在任何一个结点 $v$ 猜测次数减少时都不会被抓住。

$~~~~$ **情况1** 结点 $v$ 与内部结点相邻

$~~~~$ 由于 $a_i=v$ 只对最多 $1$ 个 $i$ 成立，$a_i\not= v$ 必定要么对所有偶数的 $i$ 成立，要么对奇数的 $i$ 成立。所以，总有一种方法使 Branko 任何时候在 $v$ 和与 $v$ 相邻的结点之间而不被抓住。

$~~~~$ **情况2** 结点 $v$ 是内部结点

$~~~~$ Branko 将会再次尝试尽可能靠近结点 $v$ 。令 $u_1,u_2,\dots,u_k$ 为 $v$ 所有相邻的结点，$u_i'$ 为 $u_i$ 与 $v$ 不同的相邻的点。

$~~~~$ 在减少次数的情况下，Ankica 最多能猜测 $2_k-3$ 次 $u$ 结点，所以她最多在偶数轮猜测 $k-2$ 次或奇数轮猜测 $k-2$ 次。我们假定她在偶数轮猜测了 $k-2$ 次，则我们让 Branko 在所有 $a_i\not=v$ 的奇数轮停留在 $v$ 结点。

$~~~~$ 现在，我们可以将 Ankica 的猜测以在奇数轮猜测 $v$ 为依据划分为最长序列。换句话说，我们关注一些 $a_i,a_{i+2},\dots,a_{i+2l}$ 且全部等于 $v$ ，但 $a_{i-2},a_{i+2}\not= v$ 的序列（疑似笔误，应为 $a_{i+2l+2}\not=v$——译者注）。

$~~~~$ 我们可以选择出与 $a_{i-1},a_{i+1},a_{i+3},\dots,a_{i+2l+1}$ 相异的结点 $u_j$，因为 $l<k-2$ 。故在所有奇数轮，Branko 移动到 $u_{j}'$ 。

$~~~~$ 我们现在知道了所有奇数轮时 Branko 的位置。

$~~~~$ 而对偶数轮来说，我们认为 Branko 在奇数轮所在位置的相邻结点。如果至少一回合他在 $u_j'$，他会在相应的偶数轮位于 $u_j$ 。如果在两个相邻的回合他都在 $v$ 结点，他可以简单地选择那个 Ankica 在偶数轮不会猜测的 $u_j$ 。

$~~~~$ 这说明了前文所述的策略的确是最优的。

$~~~~$ **声明：** 这篇题解内所有解释都是说明性的而不是严谨的。严谨地证明每种情况需要繁杂地对每种特殊情况（如 $l\leq 2$ 的树）和边界情况（如下标越界）等进行处理。我们相信这对掌握了主要思想的读者来说不难处理。

---

## 作者：Z1qqurat (赞：5)

这里直接从链入手而没有讲 $n\le 20$ 的那种暴力排除法是因为个人认为对正解启发性不大。首先容易排除 $m\ge n$ 的情况因为如果有环的话那么 B 可以反复横跳以至于 A 永远猜不到。

然后发现有链的特殊性质，考虑图是一条 $1\to n$ 的链的情况。不难想到的是 $1\to 2 \to 3 \to \cdots \to n-1 \to n \to n \to n-1\to \cdots \to3\to2\to1$ 的构造，因为它总能将 B 逼到无路可走。但是这一定是最优的策略吗？是否能在更少的步数内使 B 无路可走呢？我们先试着证明这种构造是怎么把 B 逼到无路可走的。将链黑白染色，偶数点为黑，奇数点为白，并且设 $a_{1\sim p}$ 表示 A 猜测的点形成的路径（由于要确定 B 的相对方向所以 A 一定是猜相邻的点，所以一定是一条路径），$b_{1\sim q}$ 表示 B 走的路径。发现本质就是通过同色异色点来抓住的，容易发现其实 $1,n$ 根本不用猜，那么策略简化为了 $2 \to 3 \to \cdots \to n-2 \to n-1 \to n-1 \to n-2\to \cdots \to3\to2$。

接下来证明为什么这个策略是正确的。如果 B 一开始在一个偶数点，那么它就和前 $n-2$ 轮（$2 \to 3 \to \cdots \to n-2 \to n-1$）中 A 的位置颜色相同。假如 $b_1\ne2$，那么 $b_1>a_1$。易得如果存在 $i<j,b_i>a_i,b_j<a_j$，那么一定存在时刻 $k\in (i,j)$ 使得 $a,b$ 相遇了，那么 B 就被抓住了。所以如果 B 不想被抓，那么它就一定满足这 $n-2$ 轮都有 $b_i>a_i$，而 $b_i,a_i$ 奇偶性相同，故 $b_i\ge a_i+2$，而如果要这么一直保持下去，在前 $n-2$ 轮中 B 一定会无路可走。而 $b_1$ 为奇数点的情况是同理的，因为 $n-1$ 会被连续问两次，所以在后 $n-2$ 轮，A，B 会在同奇偶的点上，证明同上。

接下来考虑链上挂一个点的情况：

![p1](https://pic.imgdb.cn/item/6593d08dc458853aefc089ce.jpg)

由于仍然满足染色奇偶性的情况，所以要么会在第一段（$2 \to 3 \to \cdots \to n-2 \to n-1$）中排除要么在第二段，对答案没有任何影响。

如果链上挂两个点？

![p1](https://pic.imgdb.cn/item/6593d08dc458853aefc08969.jpg)

如果不去这两个点中任何一个，那么 B 可以在这两个点上反复横跳不被抓到（因为这条附加链拥有了两种颜色了），所以必须将其加入询问段，问两遍，仍然是有解的（也就是说如果有附加链 $c\to x\to y$，那么在询问段中把 $c$ 改成问 $c\to x\to c$）。

如果链上挂了三个点？

![p3](https://pic.imgdb.cn/item/6593d08dc458853aefc088e7.jpg)

你会发现如果还往这个链上询问，那么要花去的额外步数已经足以让原先在主链一侧的 B 去到另一侧了，也就是说 A 无法确定 B 的方位，自然就无解了。当附加链长度 $\ge 3$ 时都无解。

但是还会发现有类似这样的情况：有多条交在一起的长为 $2$ 的附加链。

![p4](https://pic.imgdb.cn/item/6593d08bc458853aefc08493.jpg)

其实根据长为 $1$ 的附加链不影响策略的结论，我们容易发现只需要任取其中一个深度为 $2$ 的附加点去询问就可以了。实际上对做法影响不大。

然后具体实现就是将树的直径作为主链，对主链上点往外 dfs 判断即可。注意特判掉 $m\ge n,n=1,n=2$ 的情况（$n=2$ 的时候是询问 $1 \to 1$）。代码实现不难。

```cpp
#include <bits/stdc++.h>
#define ALL(v) begin(v), end(v)
#define All(v, l, r) &v[l], &v[(r) + 1]
#define NOSOL return cout << "NO\n", 0
using i64 = int64_t;
using std::cin;
using std::cout;
constexpr int N = 1005;

int n, m, s, t, ex;
std::array<std::vector<int>, N> G, ext; //extend points
std::array<int, N> dis, fa;
std::array<bool, N> vis; //on the diameter?
std::vector<int> dia, path; //diameter

auto dfs1(int u, int ff) -> void {
   fa[u] = ff;
   if (dis[u] > dis[t]) t = u;
   for (auto v : G[u]) 
      if (v != ff) dis[v] = dis[u] + 1, dfs1(v, u);
   return ;
}

auto dfs2(int u, int ff) -> bool {
   fa[u] = ff;
   if (dis[u] >= 3) return 0;
   else if (dis[u] == 2) ex = u;
   for (auto v : G[u]) {
      if (v != ff && !vis[v]) {
         dis[v] = dis[u] + 1;
         if (!dfs2(v, u)) return 0;
      }
   }
   return 1;
}

auto main() -> int {
   std::ios::sync_with_stdio(false);
   cin.tie(nullptr), cout.tie(nullptr);

   cin >> n >> m;
   for (auto i = 1, u = 0, v = 0; i <= m; ++i)
      cin >> u >> v, G[u].emplace_back(v), G[v].emplace_back(u);
   if (m != n - 1) NOSOL;
   if (n == 1) return cout << "YES\n1\n1\n", 0;
   if (n == 2) return cout << "YES\n2\n1 1\n", 0;
   dfs1(1, 0), s = t;
   dis[s] = 0, dfs1(s, 0);
   for (auto i = fa[t]; i && i != s; i = fa[i]) dia.emplace_back(i), vis[i] = 1;
   vis[s] = vis[t] = 1;

   for (auto x : dia) {
      for (auto y : G[x]) {
         if (vis[y]) continue;
         ex = 0, dis[y] = 1;
         if (!dfs2(y, x)) NOSOL;
         else if (ex) ext[x].emplace_back(y);
      }
   }
   for (auto x : dia) {
      path.emplace_back(x);
      for (auto y : ext[x])
         path.emplace_back(y), path.emplace_back(x);
   }

   cout << "YES\n" << 2 * path.size() << "\n";
   for (auto i : path) cout << i << ' ';
   reverse(ALL(path));
   for (auto i : path) cout << i << ' ';
   return 0;
}

---

## 作者：红黑树 (赞：4)

[可能更好的阅读体验](https://rbtr.ee/CEOI2021-Newspapers)

## [题意](https://www.luogu.com.cn/problem/P8173)
给定一张无向联通图，小 B 从某个点开始，每秒移动到一个相邻节点（不能不动）。小 A 每秒猜测小 B 所在的位置。若小 B 刚好在小 A 所猜的位置，小 A 就赢了。

问小 A 能否在有限步数内赢。如果可以，给出步数最小的构造方案。

$1 \leq n \leq 1000$

## 题解
首先考虑有环的情况。小 B 可以选择从环上一点开始，每次随机向左或向右移动。小 A 无法在有限步数内确保找到小 B。
因此，只有在树中，小 A 才可能赢。

接下来考虑链的情况。
假设，集合 $S$ 表示所有当前小 B 能站的点的集合。
考虑小 A 猜一个点 $x$ 之后会发生什么。
首先，从集合 $S$ 中删除 $x$，然后新的 $S$ 变为旧集合 $S$ 中所有点能到的点的集合（扩展 $1$ 步），也可以理解为 $S$ 中的点的邻域的并。
最终目标是让 $S$ 成为空集。

这里有一个通用做法：
下图中打钩的点为 $S$ 中的点。

初始时是这样的：
![](https://rbtr.ee/usr/uploads/2023/10/3575810043.png)
删去倒数第二个点，并扩展：
![](https://rbtr.ee/usr/uploads/2023/10/1871642753.png)
删去倒数第三个点，并扩展：
![](https://rbtr.ee/usr/uploads/2023/10/607961271.png)
删去倒数第四个点，并扩展：
![](https://rbtr.ee/usr/uploads/2023/10/3475039904.png)
删去倒数第五个点，并扩展：
![](https://rbtr.ee/usr/uploads/2023/10/205219271.png)
删去倒数第六个点，并扩展：
![](https://rbtr.ee/usr/uploads/2023/10/1361475931.png)

现在，这几个点不相邻了，不会互相影响。它们会在奇数点和偶数点中反复横跳，逐个删除即可。

在链中，小 A 必胜。

再看这样一颗树 $T$：
![](https://rbtr.ee/usr/uploads/2023/10/1650043850.png)

手玩一下会发现小 A 没有必胜策略。
这说明如果有点与链的距离达到或超过 $3$ 之后小 A 无法获胜。

考虑每个点与链的距离都不超过二（也就是不包含 $T$ 的树）。
以这个举例，框起来的是链上的点。
![](https://rbtr.ee/usr/uploads/2023/10/3543222648.png)
首先删打红叉的点，扩展：
![](https://rbtr.ee/usr/uploads/2023/10/1593557697.png)
再删打红叉的点，扩展：
![](https://rbtr.ee/usr/uploads/2023/10/3384079422.png)
再删打红叉的点，扩展：
![](https://rbtr.ee/usr/uploads/2023/10/2267886589.png)
再删打红叉的点，扩展：
![](https://rbtr.ee/usr/uploads/2023/10/1287723973.png)

我们发现，链上最右边的点的任务已经完成了。这几个点不相邻了，不会互相影响。它们会反复横跳，逐个删除即可。

所以，在每个点与链的距离都不超过二的树上，小 A 无法获胜。

现在我们需要找到一个最优的方案。其实上述方法已经是最优的了。首先我们可以把点分为三类：链上节点、叶子节点和中间节点。
设 $z\left(x\right)$ 表示与 $x$ 相邻的中间节点的个数。
那么链上节点 $x$ 会被猜测 $2\left(z\left(x\right) - 1\right)$ 次。
叶子节点不会被猜测。
中间节点会被猜测 $2$ 次。

显然，如果中间节点次数减少，小 A 就无法通过上述方法抓住小 B 了。

如果 $v$ 是链上节点（以下证明来自官方题解）：
设 $a$ 数组表示小 A 的猜测序列，设 $k = z\left(v\right)$。

小 B 将会再次尝试尽可能靠近结点 $v$ 。设 $u_1, u_2, \ldots, u_k$ 为 $v$ 所有相邻的结点，${u_i}'$ 为 $u_i$ 不是 $v$ 的相邻的点。

在减少次数的情况下，小 A 最多能猜测 $u$ 结点 $2k - 3$ 次，所以她最多在偶数轮猜测 $k - 2$ 次或奇数轮猜测 $k - 2$ 次。我们假定她在偶数轮猜测了 $k - 2$ 次，则我们让小 B 在所有 $a_i \neq v$ 的奇数轮停留在 $v$ 结点。

现在，我们关注一些 $a_i, a_{i + 2}, \ldots, a_{i + 2l}$ 且全部等于 $v$ ，但 $a_{i-2}, a_{i+2l+2} \neq v$ 的序列。

我们可以选择出与 $a_{i - 1}, a_{i + 1}, a_{i + 3}, \ldots, a_{i + 2l + 1}$ 不同的结点 $u_j$，因为 $l < k - 2$ 。故在所有奇数轮，小 B 移动到 ${u_j}'$ 。

我们现在知道了所有奇数轮时小 B 的位置。

而对偶数轮来说，我们认为小 B 在奇数轮所在位置的相邻结点。如果至少一回合他在 ${u_j}'$，他会在相应的偶数轮位于 $u_j$ 。如果在两个相邻的回合他都在 $v$ 结点，他可以简单地选择那个小 A 在偶数轮不会猜测的 $u_j$。

这也就意味着，我们无法减少猜测次数。因此，上述方案就是最优的。

## 代码
```cpp
#include <bits/stdc++.h>

#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)
#define ll long long

using namespace std;

const int MAXN = 1010;

vector <int> ve[MAXN];
int bio[MAXN];

void impossible() {
    cout << "NO\n";
    exit(0);
}

void dfs(int x, int par) {
    bio[x] = bio[par] + 1;

    for (int y : ve[x]) {
        if (y == par) continue;
        if (bio[y]) impossible();
        dfs(y, x);
    }

    return;
}

int main_path[MAXN];
vector <int> path;
int twig[MAXN];

int rek(int x, int par) {
    int ma = 0;
    for (int y : ve[x]) {
        if (y == par) continue;
        if (main_path[y]) continue;
        ma = max(ma, rek(y, x));
    }
    if (ma == 3) impossible();
    twig[x] = ma;
    return ma + 1;
}

vector <int> out;

void print() {
    cout << "YES\n";
    cout << out.size() << "\n";
    for (int x : out) cout << x + 1 << " ";
    cout << "\n";

    return;
}

int main() {
    int n, m;
    cin >> n >> m;

    if (n == 1) {
        out.push_back(0);
        print();
        return 0;
    }

    if (n == 2) {
        out.push_back(0);
        out.push_back(0);
        print();
        return 0;
    }

    REP(i, m) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        ve[a].push_back(b);
        ve[b].push_back(a);
    }

    dfs(0, 0);
    int A = -1, dist = -1;
    REP(i, n) {
        if (bio[i] > dist) {
            dist = bio[i];
            A = i;
        }
    }

    memset(bio, 0, sizeof bio);
    dfs(A, A);
    int B = -1;
    dist = -1;
    REP(i, n) {
        if (bio[i] > dist) {
            dist = bio[i];
            B = i;
        }
    }

    int x = B;
    while (x != A) {
        main_path[x] = 1;
        path.push_back(x);
        for (int y : ve[x]) {
            if (bio[y] == bio[x] - 1) {
                x = y;
                break;
            }
        }
    }
    path.push_back(A);
    main_path[A] = 1;

    memset(twig, 0, sizeof twig);
    REP(i, n) {
        if (main_path[i]) twig[i] = rek(i, i) - 1;
    }

    // remove first and last node of path to optimise
    if (path.size() > 1) {
        main_path[path[0]] = 0;
        path.erase(path.begin());

        twig[path[0]] = max(twig[path[0]], 1);
    }
    reverse(path.begin(), path.end());
    if (path.size() > 1) {
        main_path[path[0]] = 0;
        path.erase(path.begin());

        twig[path[0]] = max(twig[path[0]], 1);
    }

    for (int x : path) {
        out.push_back(x);
        if (twig[x] == 2) {
            for (int y : ve[x]) {
                if (main_path[y] || twig[y] == 0) continue;
                out.push_back(y);
                out.push_back(x);
            }
        }
    }

    reverse(path.begin(), path.end());

    for (int x : path) {
        out.push_back(x);
        if (twig[x] == 2) {
            for (int y : ve[x]) {
                if (main_path[y] || twig[y] == 0) continue;
                out.push_back(y);
                out.push_back(x);
            }
        }
    }

    print();

    return 0;
}
```

---

## 作者：lucky_baizq (赞：3)

## 题意

A 先行动，判断一个点 $x$ 是不是 B 所在的位置，是则结束

B 在行动，沿边走一步。

问：是否在有限步内找到 B，可以的话给出最小行动次数和方案。

## 做法

考虑链该怎么弄？

![](https://cdn.luogu.com.cn/upload/image_hosting/icq31lxh.png)

注意到在 $2$ 位置停留 $2$ 次可以把这种情况抓住，并且 $Q_1$ 也省略了，同理推得 $3,4,5,n-1$ 都一样，且边缘 $Q_1,Q_n$ 都可以省略

最优策略次数 $2 \times n-4$。 

构造方案有：

$$2,3.....n-2,n-1,n-1,n-2......3,2$$


另外的一个想法，到直径某端点的路径奇偶性分讨：

![](https://cdn.luogu.com.cn/upload/image_hosting/u9nqpmaz.png)

偶点会在回来那一次奇偶性改变，类似奇点一样被干掉。

预期 $8$ pts。

考虑其他的情况

![](https://cdn.luogu.com.cn/upload/image_hosting/00ksw2e3.png)

环（$m\ge n$）显然无解，直接输出 $\texttt{NO}$ 即可。

所以最终一定是一棵树。有了链的启发，想到可以先找一条最长链（直径）其他的就是挂在链上的神秘东西。

好！找到了链，考虑挂上的东西，来炒一炒。

![](https://cdn.luogu.com.cn/upload/image_hosting/krdx9eoy.png)

发现好像可行的东西不会太长，手玩发现 $\ge 3$ 时就失败了。

第一种：

![](https://cdn.luogu.com.cn/upload/image_hosting/8n2mcgdu.png)

第二种：

![](https://cdn.luogu.com.cn/upload/image_hosting/ofl7zdq3.png)

而在 $1,2$ 时都是显然有解。

![](https://cdn.luogu.com.cn/upload/image_hosting/o48gqhdw.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/hbvga999.png)

怎么证明是最优的呢，考虑我们在任意一个点上删除一些查询，则按照上面的分析，我们一定可以找到 B 的一种最坏情况，使得其逃起来，根本让人找不到，所以每个点必不可少查询，得感性证明。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N=200010;

int n,m,s,t,tp,dis[N],u,v,b[N];

int lu[N<<2],id,f1[N]; 

vector<int> f[N],g,ff[N];

void dfs(int p,int fa){
	dis[p]=dis[fa]+1;f1[p]=fa;
	if(dis[p]>dis[t])t=p;
	for(int v:f[p]){
		if(v==fa)continue;
		dfs(v,p);
	}
}

int dfs1(int p,int fa){
	dis[p]=dis[fa]+1;f1[p]=fa;
	if(dis[p]>=3)return 0;
	if(dis[p]==2)tp=p;
	for(int v:f[p]){
		if(v==fa||b[v])continue;
		if(dfs1(v,p)==0)return 0;
	}
	return 1;
}

int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>u>>v;
		f[u].push_back(v);
		f[v].push_back(u);
	}
	if(m!=n-1)cout<<"NO";
	else if(n==1){cout<<"YES\n1\n1\n";}
	else if(n==2){cout<<"YES\n2\n1 1";}
	else {
		int ans=0;
		dfs(1,0);s=t;dis[s]=0;dfs(s,0);
		for(int i=f1[t];i!=s;i=f1[i])b[i]=1,g.push_back(i),b[s]=b[t]=1;
		memset(dis,0,sizeof dis);
		for(int i:g){
			ans+=2;
			for(int v:f[i]){
				tp=0;
				if(b[v])continue;
				if(!dfs1(v,i)){
					cout<<"NO";return 0;
				}
				if(tp) ff[i].push_back(v),
				ans+=4;
			}
		}
		cout<<"YES\n";
		cout<<ans<<"\n"; 
		for(int i:g){
			cout<<i<<" ";
			for(int j:ff[i])
			cout<<j<<" "<<i<<" ";
		}
		reverse(g.begin(),g.end());
		for(int i:g){
			cout<<i<<" ";
			for(int j:ff[i])
			cout<<j<<" "<<i<<" ";
		}
	}
	return 0;
}
```

---

## 作者：7KByte (赞：3)

非常神的树上问题，和树上的数超现实树有的一拼。

样例非常小没有任何价值，考虑手算一下长度为 $5$ 的链。

不难发现最优策略就是 $2,3,4,4,3,2$，这给了我们很大的启发。

- 1.一定不能有环，否则任意情况对方都有两条路可走，永远无法抓住对方。

- 2.我们查询的过程类似于在树上移动，每次可以将路径上的点排除。一定是在相邻点上移动，否则如果对方在跳过的那个点上，你就永远不知道他的位置。

- 3.我们需要扫两遍，因为如果将树黑白染色，扫一遍只能排除一种颜色。

所以对于链的情况，一定有解且解为 $2\to n -1,n-1\to 2$，共 $2n-2$ 次询问，可以得到 $8$ 分。

扩展一下，如果链的某个节点上再接上一段会发生什么变化。

如果接上的是一个点，那么答案不会变化，因为该节点和连接的链上节点颜色相反，所以不是在第一遍被排除就是在第二遍被排除。

如果接上的链是两个点，那么我们只用多进行两次判断即可。

![](https://cdn.luogu.com.cn/upload/image_hosting/974k2uod.png)

就是 $1\to A\to3\to A\to 2$，$2\to A\to 3\to A\to 1$。

如果接更多的节点呢，惊奇的发现我们不能更深入 $4$ 号节点。

![](https://cdn.luogu.com.cn/upload/image_hosting/g8ci124j.png)

如果我们到达 $4$ 号，再回到 $A$，那么进行 $3\to 4\to 3$ 三次操作。这个时候如果对手在 $P$ 或者 $Q$ 号节点上，三次操作足够对方跨过 $A$ 到达另一边。那么自己回到 $A$ 的时候根本不知道对手在哪边，相当于前面的努力都白费了。

所以如果出现这种情况，两边都无法保全，只可能是无解。

这么分析后最优解应该很清晰了，我们找到直径，然后判断是否有长度 $\ge 3$ 的支链，然后对于长度为 $2$ 的支链要多进行两次操作进行覆盖。

时间复杂度 $\mathcal{O}(N)$，checker 的复杂度应该是 $\mathcal{O}(N^2)$ 的。

代码很短。

```cpp
#define N 1005
int n, m, d[N], fa[N], c[N], t, v[N]; vector<int>e[N], u[N], ans;
void dfs(int x,int f){
	d[x] = d[fa[x] = f] + 1;
	go(y, e[x])if(y != f)dfs(y, x);
}
void calc(int x,int f){
	go(y, e[x])if(y != f)calc(y, x), cmx(d[x], d[y]);
}
int main() {
	read(n, m);
	if(m >= n){puts("NO"); return 0;}
	if(n == 1){	puts("YES\n1\n1"); return 0;}
	if(n == 2){ puts("YES\n2\n1 1"); return 0;}
	rp(i, m){
		int x, y; read(x, y);
		e[x].pb(y), e[y].pb(x);
	}
	dfs(1, 0); int X = 1;
	rp(i, n)if(d[i] > d[X])X = i;
	dfs(X, 0); int Y = 1;
	rp(i, n)if(d[i] > d[Y])Y = i;
	int tem = Y;
	while(tem)v[c[++t] = tem] = 1, tem = fa[tem];
	rp(i, n)if(!v[i] && v[fa[i]]){
		calc(i, fa[i]);
		if(d[i] >= d[fa[i]] + 3){puts("NO"); return 0;}
		if(d[i] > d[fa[i]] + 1)u[fa[i]].pb(i);
	}
	puts("YES");
	rep(i, 2, t - 1){
		ans.pb(c[i]);
		go(x, u[c[i]])ans.pb(x), ans.pb(c[i]);
	}
	pre(i, t - 1, 2){
		ans.pb(c[i]);
		go(x, u[c[i]])ans.pb(x), ans.pb(c[i]);
	}
	printf("%d\n", si(ans));
	go(x, ans)printf("%d ", x); el;
	return 0;
}
```

---

## 作者：_wsq_ (赞：0)

更新于 2025/7/3：添加了一份更简单的代码（原代码判断是否有那个子图用的是换根 dp，这次换成了找直径并看子树深度，短一些）。



前言：4.15 和 [RDFZchenyy](https://www.luogu.com.cn/user/567610) 一起研究这道题，当时只研究出来一半。第二天，我利用上午的前两个课间思考这道题，结果竟然想出来了正解。这是我第一道不看题解做出来的黑题（我太菜了），因此写篇题解纪念。

___

记 Ankica 为 A，Branko 为 B。

___

首先我们不禁想到某经典谜题。

![](bilibili:BV18VpvehEaX)

虽然视频中只是一种特殊情况，但是这个视频给了我们一些启发。首先，从样例和视频中，我们可以猜测：当且仅当图是一棵树，有解。另外，视频给了我们一个启发：就是我们可以考虑黑白染色，先假定 B 初始在某个颜色的点，然后黑白交错猜测， B 初始在这个颜色的点猜完以后，使得猜测次数为奇数，然后再来一遍即可。

然后我们就要开始证结论了。

>结论 1：如果图中有环，则一定无解。

证明是很显然的，如果 B 初始在环上且 B 的初始位置没有被猜中，那么只要 B 一直在环上，他旁边就一定有至少两个点，其中就一定有一个是 A 下一步没有猜的。

但是，按照我们且仅当图是一棵树有解的猜测交上去后，[发现不对](https://www.luogu.com.cn/record/213865495)。于是我们 ~~[去 qoj 套数据](https://qoj.ac/submission/980479)~~ 尝试可得，下面这个图会不行。因为 B 可以呆在一个没有被猜完的子树里，然后在我们试图把一个子树猜完时占领根节点，然后 B 的活动区域就又变成了两个子树。那么显然，只要这棵树有子图长这个样子就不行。

![](https://cdn.luogu.com.cn/upload/image_hosting/fho6wykf.png)

进一步的，我们可以继续猜测。

>结论 2：当且仅当图是一棵树且这棵树没有子图长上面这个样子，有解。

我们暂时无法证明，但是[交上去，发现是对的](https://www.luogu.com.cn/record/213895213)。我们知道后续找方案的过程或许对证明这一点有帮助。

然后我们思考这样的图实际上是什么。

>结论 3：有解的图一定形如一条直径上面挂了一堆子树，而这些子树深度都不超过 $2$。

这个也不难想到。对于中间的点，如果超过 $2$，那么就会出现上面的情况；而对于两边的 $4$ 个点，如果超过 $2$，那你就会发现直径不是直径了。

那么现在就很明确了。因为这棵树大体上长成一条链，所以我们可以从链的一端开始逐渐排除。然后就很简单了，首先发现分奇偶是不必要的，因为从链的一端的开头开始操作一定比从链的一端的第二个点开始操作次数多 $1$，所以从链的一端的第二个点开始操作一定最优，操作完反着在来一遍即可。然后我们逐渐前进，如果挂着深度为 $1$ 的子树就不用考虑（因为另一遍时会把它们解决），挂着深度为 $2$ 的子树就要在该结点和其子节点之间来回操作，直到清空所有挂着的子树。细节看代码后半部分。当然，要特判 $n<3$ 的情况。

代码 1：

```cpp
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
#define maxn 1005
struct edge{
	int to,next;
}e[maxn<<1];
int n,m,h[maxn],tot,ext[maxn][5],up[maxn],dep[maxn],en,prv[maxn],li[maxn]={1},maxd,ans[maxn];
void addedge(int u,int v){
	e[++tot].to=v;
	e[tot].next=h[u];
	h[u]=tot;
	return;
}
//注：dfs1 和 dfs2 采用换根 dp 判断是否存在子图长成上面那个图，dfs1 和 dfs3 是找直径的
void dfs1(int x,int fa){
	for(int i=h[x];i;i=e[i].next){
		if(e[i].to==fa){
			continue;
		}
		if(dep[x]>=maxd){
			maxd=dep[x]+1;
			en=e[i].to;
		}
		dep[e[i].to]=dep[x]+1;
		dfs1(e[i].to,x);
		int cnt=ext[e[i].to][1]+1;
		if(cnt>ext[x][1]){
			swap(cnt,ext[x][1]);
		}
		if(cnt>ext[x][2]){
			swap(cnt,ext[x][2]);
		}
		if(cnt>ext[x][3]){
			swap(cnt,ext[x][3]);
		}
	}
	if(ext[x][3]>2){
		cout<<"NO";
		exit(0);
	}
	return;
}
void dfs2(int x,int fa){
	if(fa){
		up[x]=max(up[fa],(ext[x][1]+1==ext[fa][1])?ext[fa][2]:ext[fa][1])+1;
		if(up[x]>2&&ext[x][2]>2){
			cout<<"NO";
			exit(0);
		}
	}
	for(int i=h[x];i;i=e[i].next){
		if(e[i].to==fa){
			continue;
		}
		dfs2(e[i].to,x);
	}
	return;
}
void dfs3(int x,int fa){
	for(int i=h[x];i;i=e[i].next){
		if(e[i].to==fa){
			continue;
		}
		if(dep[x]>=maxd){
			maxd=dep[x]+1;
			li[1]=e[i].to;
		}
		dep[e[i].to]=dep[x]+1;
		prv[e[i].to]=x;
		dfs3(e[i].to,x);
	}
	return;
}
int main(){
	cin>>n>>m;
	if(m>=n){
		cout<<"NO";
		return 0;
	}
	if(n==1){
		cout<<"YES\n1\n1";
		return 0;
	}
	if(n==2){
		cout<<"YES\n2\n1 1";
		return 0;
	}
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		addedge(u,v);
		addedge(v,u);
	}
	dfs1(1,0);
	dfs2(1,0);
	cout<<"YES\n";
	memset(dep,0,sizeof(dep));
	maxd=0;
	dfs3(en,0);
//后面 li 存的是链里的所有结点，now 是当前判断的节点，ans 是答案
	int now=li[1];
	while(now!=en){
		now=prv[now];
		li[++li[0]]=now;
		if(now!=en){
			ans[++ans[0]]=now;
			for(int i=h[now];i;i=e[i].next){
				if(e[i].to==prv[now]||e[i].to==li[li[0]-1]){
					continue;
				}
				if(e[h[e[i].to]].next){
					ans[++ans[0]]=e[i].to;
					ans[++ans[0]]=now;
				}
			}
		}
	}
	cout<<(ans[0]<<1)<<'\n';
	for(int i=1;i<=ans[0];i++){
		cout<<ans[i]<<' ';
	}
	for(int i=ans[0];i;i--){
		cout<<ans[i]<<' ';
	}
	return 0;
}
```

代码 2：

```cpp
#include<iostream>
using namespace std;
struct edge{
	int to,next;
}e[2010];
int n,m,h[1005],tot,dep[1005],maxd,id,pre[1005],ans[5025];
bool vis[1005];
void addedge(int u,int v){
	e[++tot].to=v;
	e[tot].next=h[u];
	h[u]=tot;
	return;
}
void dfs(int x,int fa,bool b){
	dep[x]=dep[fa]+1;
	if(b){
		pre[x]=fa;
	}
	if(dep[x]>maxd){
		maxd=dep[x];
		id=x;
	}
	for(int i=h[x];i;i=e[i].next){
		if(e[i].to==fa||vis[e[i].to]){
			continue;
		}
		dfs(e[i].to,x,b);
	}
	return;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin>>n>>m;
	if(n==1){
		cout<<"YES\n1\n1";
		return 0;
	}
	if(n==2){
		cout<<"YES\n2\n1 1";
		return 0;
	}
	if(m>=n){
		cout<<"NO";
		return 0;
	}
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		addedge(u,v);
		addedge(v,u);
	}
	dfs(1,0,false);
	maxd=0;
	dfs(id,0,true);
	int cnt=id;
	while(pre[pre[cnt]]){
		vis[cnt]=true;
		vis[pre[pre[cnt]]]=true;
		maxd=0;
		dfs(pre[cnt],0,false);
		if(maxd>3){
			cout<<"NO";
			return 0;
		}
		ans[++ans[0]]=pre[cnt];
		for(int i=h[pre[cnt]];i;i=e[i].next){
			if(e[i].to!=cnt&&e[i].to!=pre[pre[cnt]]&&(e[h[e[i].to]].to!=pre[cnt]||(e[e[h[e[i].to]].next].to&&e[e[h[e[i].to]].next].to!=pre[cnt]))){
				ans[++ans[0]]=e[i].to;
				ans[++ans[0]]=pre[cnt];
			}
		}
		vis[cnt]=false;
		vis[pre[pre[cnt]]]=false;
		cnt=pre[cnt];
	}
	cout<<"YES\n"<<(ans[0]<<1)<<'\n';
	for(int i=1;i<=ans[0];i++){
		cout<<ans[i]<<' ';
	}
	for(int i=ans[0];i;i--){
		cout<<ans[i]<<' ';
	}
	return 0;
}
```

---

