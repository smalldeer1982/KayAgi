# [BJWC2018] Kakuro

## 题目背景

首先介绍一下Kakuro(カックロ) 这个游戏。

游戏规则为：

• 方形空格中填入1 ~ 9 的整数。

• 被斜线分开的方格中，右上角的数字等于其右侧邻接之连续方格中数字之和，左下角的数字等于其下方邻接之连续方格中数字之和。

• 无论是横向还是纵向，连续方格中的数字不能重复。

![](https://cdn.luogu.com.cn/upload/pic/17946.png)
![](https://cdn.luogu.com.cn/upload/pic/17947.png)

左边为一个Kakuro 游戏，右边为这个游戏的唯一解。

我们称一开始给出的数字为线索，称需要填入数字的地方为空格。如果一个格子包含线索那么就不需要填入数字。我们约定所有的谜题都非空，即至少有一个空格需要被填入。

**注意：在以下题目中的游戏规则可能会有所不同，请认真阅读在每个
题目下的规则。**

## 题目描述

游戏规则：

• 空格中填入正整数。

• 被斜线分开的方格中，右上角的数字等于其右侧邻接之连续方格中数字之和，左下角的数字等于其下方邻接之连续方格中数字之和。

Apia 给了Rimbaud 一个Kakuro 谜题。心不灵手不巧的Rimbaud 根本不会做Kakuro，所以只在空格里面填上了一些随机的数字，称这个为一个局面，即包含了谜题一开始给出的线索和后面填入的数字。

现在Rimbaud 希望能修改这个局面使得她的答案是一个合法解。这个局面中有些数字(**包括一开始的给出线索和后面填入的数字**) 是可以修改的。每个数字都有个特定的代价，将这个数字加1 或者减1 都得付出这个数字对应的代价。注意对于一组合法解，必须满足游戏规则，也就是**空格中填的数字必须是正整数并且满足和的条件，但是不要求不重复**。

Rimbaud 希望用最少的代价让这个局面变得合法，如果不可能那么输出-1。

## 说明/提示

对于5% 的数据，保证所有的代价都为-1。

对于20% 的数据，保证所有空格中的数字代价都为-1。

对于另外30% 的数据，保证所有代表线索的数字的代价都为-1。

对于另外20% 的数据，保证只有第一行第一列包含线索，剩下的地方全都是空格。

对于100% 的数据，保证3 ≤ n,m ≤ 30，保证初始局面中的每个数字不超过$10^6$，保证每个数字的代价不超过$10^6$。

## 样例 #1

### 输入

```
8 8
0 1 1 0 0 1 1 1
2 4 4 0 3 4 4 4
2 4 4 3 4 4 4 4
2 4 4 4 4 4 1 0
0 2 4 4 3 4 4 1
0 1 3 4 4 4 4 4
2 4 4 4 4 2 4 4
2 4 4 4 0 2 4 4
23 30 27 12 16
16 9 7 17 24 8 7 9
17 8 9 15 29 8 9 5 7
35 6 8 5 9 7 12
7 6 1 7 8 2 6 7
11 10 16 4 6 1 3 2
21 8 9 3 1 5 1 4
6 3 1 2 3 2 1
-1 -1 -1 -1 -1
-1 -1 -1 -1 -1 -1 -1 -1
-1 -1 -1 -1 -1 -1 -1 -1 -1
-1 -1 -1 -1 -1 -1 -1
-1 -1 -1 -1 -1 -1 -1 -1
-1 -1 -1 -1 -1 -1 -1 -1
-1 -1 -1 -1 -1 -1 -1 -1
-1 -1 -1 -1 -1 -1 -1```

### 输出

```
0```

## 样例 #2

### 输入

```
5 5
0 1 1 1 1
2 4 4 4 4
2 4 4 3 4
2 4 4 4 4
2 4 4 4 4
16 8 6 8
4 4 9 5 4
12 8 4 19 10 4
14 2 3 3 6
1 7 9 4 5
17 5 10 13
11 15 16 4 14
20 20 15 5 16 3
4 3 19 2 4
19 19 13 15 20```

### 输出

```
822```

# 题解

## 作者：SkqLiiiao (赞：7)

# [BJWC2018]【最小费用最大流】 kakuro

## 题意

kakuro是一个神奇的数独游戏，大致规则如下：

- $N\times M$ 的网格图中，由一些格子为空格需要填数，一些格子填线索，一些格子什么都不填
- 线索有两个方向，分别为右和下，线索的值表示该方向连续空格所填数之和
- 对于任意一个空格，其左边与上边的一定存在一个格子为线
- 参考下图

![img](https://cdn.luogu.com.cn/upload/pic/17946.png)

游戏规则：

• 空格中填入正整数。

• 被斜线分开的方格中，右上角的数字等于其右侧邻接之连续方格中数字之和，左下角的数字等于其下方邻接之连续方格中数字之和。

Apia 给了Rimbaud 一个Kakuro 谜题。心不灵手不巧的Rimbaud 根本不会做Kakuro，所以只在空格里面填上了一些随机的数字，称这个为一个局面，即包含了谜题一开始给出的线索和后面填入的数字。

现在Rimbaud 希望能修改这个局面使得她的答案是一个合法解。这个局面中有些数字(**包括一开始的给出线索和后面填入的数字**) 是可以修改的。每个数字都有个特定的代价，将这个数字加 $1$ 或者减 $1$ 都得付出这个数字对应的代价。注意对于一组合法解，必须满足游戏规则，也就是**空格中填的数字必须是正整数并且满足和的条件，但是不要求不重复**。

Rimbaud 希望用最少的代价让这个局面变得合法，如果不可能那么输出`-1` 。

## 数据范围

对于$100\%$ 的数据，保证$3 \leq n,m \leq 30$，保证初始局面中的每个数字不超过 $10^6$ ，保证每个数字的代价不超过 $10^6$ 。

## 题解

### 致谢

感谢AloNE的讲解。

### 正题

一个思路就是先做出一个合法解，然后再去修改权值以减少总花费。

那么最简单的合法解，就是每个空格都填 $1$ ，线索填对应格子的个数。

如此保证了每个空格都是正整数，这是一个最小解。

记当前花费为 $Ans$ 。

记某个格子现在的值为 $A(x,y)$ ，原来的值为 $O(x,y)$ ，修改 $1$ 的价格为 $C(x,y)$ 。

那么每个空格和线索只能往大修改，那么有两种情况。

- $A(x,y) \leq O(x,y)$ ，那么当 $A(x,y)$ 最初变大直到 $O(x,y)$ 时，相当于对最开始的修改进行反悔，也就是说花费 $-C(x,y)$；当然对于超出 $O(x,y)$ 的部分继续花费 $C(x,y)$ 。
- $A(x,y) \geq O(x,y)$ ，那么修改继续增加花费 $C(x,y)$ 。

转化成网络流问题，将这些关系抽象成如下的边：

- 发现对于修改一个空格会对其左边和上边的两个线索产生影响，约束方法很简单，就是流量从其上面的线索流入，从其左边的线索流出，那么保证所有增加的流量都是合法的；也就是说空格本质就是一条连接横向和竖向线索的边；
- 根据上面的建模方法，$S$ 连接所有竖向线索，费用为 $C(x,y)$ ，流量不限；
- 所有横向线索连接 $T$ ，费用为 $C(x,y)$ ，流量不限；


- 对于所有空格，如果 $A(x,y) \leq O(x,y)$ ，连接费用为 $-C(x,y)$ 流量为 $O(x,y) - A(x,y)$ ，意为对最初的修改进行反悔；（对应的两个线索之间连边）
- 对于所有空格，连接费用为 $C(x,y)$ ，流量不限的边，因为每个格子都可以无限增大。

跑最小费用可行流，当前费用 $Cost \geq 0$ 时结束。

得到最小费用 $C$ ，那么最终结果 $Ans + C$ 。

那么如何判断无解的情况？

无解也就是说修改了不能修改的边。

那么将不能修改的边的费用置为 $INF$ ，跑完最小费用可行流之后检查残余网络是否存在费用为 $INF$ 的反向边流量不为 $0$ 或者费用为 $-INF$ 的边流量不为 $0$ 。

如果出现这种情况，说明了必须修改不能修改的格子权值以满足流量平衡，输出 `-1` 即可。 

### 参考代码

```cpp
// Copyright 2018, Skqliao
#include <bits/stdc++.h>

#define rg register
#define rep(i, l, r) for (rg int i = (l), _##i##_ = (r); i < _##i##_; ++i)
#define rof(i, l, r) for (rg int i = (l) - 1, _##i##_ = (r); i >= _##i##_; --i)
#define ALL(x) (x).begin(), (x).end()
#define SZ(x) static_cast<int>((x).size())
typedef long long ll;

const int MAXN = 30 + 5;
const int INF = 1e9 + 7;

namespace mcf {
const int MAXN = ::MAXN * ::MAXN * 4;
const int MAXM = MAXN;
struct Edge {
    int v, c, f, nxt;
}E[MAXM << 1];
int S, T;
ll C, F, Dis[MAXN];
int H[MAXN], cntE;
int Lp[MAXN], Le[MAXN];
void addEdge(int u, int v, int f, int c) {
    E[++cntE] = (Edge) {v, c, f, H[u]};
    H[u] = cntE;
    E[++cntE] = (Edge) {u, -c, 0, H[v]};
    H[v] = cntE;    
}
bool spfa() {
    static std::bitset<MAXN> Inq;
    static std::queue<int> Que;
    Inq = 0;
    memset(Dis, 0x3f, sizeof Dis);
    Dis[S] = 0;
    Que.push(S);
    while(!Que.empty()) {
        int x = Que.front(); Que.pop();
        Inq[x] = false;
        for(int i = H[x]; ~i; i = E[i].nxt) {
            int &v = E[i].v;
            if(E[i].f && Dis[v] > Dis[x] + E[i].c) {
                Dis[v] = Dis[x] + E[i].c;
                Lp[v] = x, Le[v] = i;
                if(!Inq[v]) {
                    Inq[v] = true;
                    Que.push(v);
                }
            }
        }
    }
    return Dis[T] < 0;
}
void mcf() {
    while(spfa()) {
        int f = INF;
        for(int i = T; i != S; i = Lp[i]) {
            f = std::min(f, E[Le[i]].f);
        }
        C += f * Dis[T];
        F += f;
        for(int i = T; i != S; i = Lp[i]) {
            E[Le[i]].f -= f;
            E[Le[i] ^ 1].f += f;
        }
    }
}
void init() {
    memset(H, -1, sizeof H);
    cntE = -1;
    C = F = 0;
}
bool check() {
    for(int i = 0; i <= cntE; i += 2) {
        if(E[i].c == INF && E[i ^ 1].f > 0) {
            return false;
        }
        if(E[i].c == -INF && E[i].f > 0) {
            return false;
        }
    }
    return true;
}
}

int N, M;
int Type[MAXN][MAXN];
int Column[MAXN][MAXN], Line[MAXN][MAXN], Ori[MAXN][MAXN];
int ChangeC[MAXN][MAXN], ChangeL[MAXN][MAXN], ChangeO[MAXN][MAXN];
int IdC[MAXN][MAXN], IdL[MAXN][MAXN];
int Left[MAXN][MAXN], Up[MAXN][MAXN];
int AfterC[MAXN][MAXN], AfterL[MAXN][MAXN], AfterO[MAXN][MAXN];

int main() {
    mcf::init();
    int cnt = 0;
    scanf("%d%d", &N, &M);
    rep(i, 1, N + 1) {
        rep(j, 1, M + 1) {
            scanf("%d", &Type[i][j]);
        }
    }
    rep(i, 1, N + 1) {
        rep(j, 1, M + 1) {
            if(Type[i][j] == 1 || Type[i][j] == 3) {
                scanf("%d", &Column[i][j]);
                IdC[i][j] = ++cnt;
            }
            if(Type[i][j] == 2 || Type[i][j] == 3) {
                scanf("%d", &Line[i][j]);
                IdL[i][j] = ++cnt;
            }
            if(Type[i][j] == 4) {
                scanf("%d", &Ori[i][j]);
            }
        }
    }
    mcf::S = 0, mcf::T = cnt + 1;
    rep(i, 1, N + 1) {
        rep(j, 1, M + 1) {
            if(Type[i][j] == 1 || Type[i][j] == 3) {
                scanf("%d", &ChangeC[i][j]);
                if(ChangeC[i][j] == -1) {
                    ChangeC[i][j] = INF;
                }
            }
            if(Type[i][j] == 2 || Type[i][j] == 3) {
                scanf("%d", &ChangeL[i][j]);
                if(ChangeL[i][j] == -1) {
                    ChangeL[i][j] = INF;
                }
            }
            if(Type[i][j] == 4) {
                scanf("%d", &ChangeO[i][j]);
                if(ChangeO[i][j] == -1) {
                    ChangeO[i][j] = INF;
                }
            }
        }
    }
    rep(i, 1, N + 1) {
        rep(j, 1, M + 1) {
            if(Type[i][j] == 1 || Type[i][j] == 3) {
                int k = i + 1;
                while(k <= N && Type[k][j] == 4) {
                    Up[k++][j] = IdC[i][j];
                }
                AfterC[i][j] = k - i - 1;
                mcf::C += 1ll * ChangeC[i][j] * std::abs(AfterC[i][j] - Column[i][j]);
            }
            if(Type[i][j] == 2 || Type[i][j] == 3) {
                int k = j + 1;
                while(k <= M && Type[i][k] == 4) {
                    Left[i][k++] = IdL[i][j];
                }
                AfterL[i][j] = k - j - 1;
                mcf::C += 1ll * ChangeL[i][j] * std::abs(AfterL[i][j] - Line[i][j]);
            }
            if(Type[i][j] == 4) {
                AfterO[i][j] = 1;
                mcf::C += 1ll * ChangeO[i][j] * std::abs(AfterO[i][j] - Ori[i][j]);
            }
        }
    }
    rep(i, 1, N + 1) {
        rep(j, 1, M + 1) {
            if(Type[i][j] == 1 || Type[i][j] == 3) {
                if(AfterC[i][j] < Column[i][j]) {
                    mcf::addEdge(mcf::S, IdC[i][j], Column[i][j] - AfterC[i][j], -ChangeC[i][j]);
                }
                mcf::addEdge(mcf::S, IdC[i][j], INF, ChangeC[i][j]);
            }
            if(Type[i][j] == 2 || Type[i][j] == 3) {
                if(AfterL[i][j] < Line[i][j]) {
                    mcf::addEdge(IdL[i][j], mcf::T, Line[i][j] - AfterL[i][j], -ChangeL[i][j]);
                }
                mcf::addEdge(IdL[i][j], mcf::T, INF, ChangeL[i][j]);
            }
            if(Type[i][j] == 4) {
                if(AfterO[i][j] < Ori[i][j]) {
                    mcf::addEdge(Up[i][j], Left[i][j], Ori[i][j] - AfterO[i][j], -ChangeO[i][j]);
                }
                mcf::addEdge(Up[i][j], Left[i][j], INF, ChangeO[i][j]);
            }
        }
    }
    mcf::mcf();
    if(!mcf::check()) {
        printf("-1\n");
    } else {
        printf("%lld\n", mcf::C);
    }
    return 0;
}
```



---

## 作者：ArisakaMashiro (赞：2)

首先，容易发现一个空格的值会且仅会影响其上、其左的两个线索，这启示我们将空格建模为边连接其影响的两个线索。

如果将线索分为纵向的与横向的两种线索，那么每个空格就相当于二分图上的边。不妨将纵向线索设为左部点、横向线索设为右部点，那么现在原局面就被我们建模为了一个二分图。

那么解决二分图上的最小费用问题，自然而然的选择费用流。

接下来解决费用流的建图问题：

手玩几把数据，可以发现在当前局面合法的情况下，如果我们令一个空格的数值 $+1$，为保持局面合法，则其上、其左的线索所对应的数值也要 $+1$。

于是我们可以这么建图（假设源点为 $S$，汇点为 $T$，修改对应节点数值的单价为 $C$）：

- 对于每个纵向线索，从 $S$ 向该点连一条容量为 $+\infin$，费用为 $C$ 的边。

- 对于每个横向线索，从该点向 $T$ 连一条容量为 $+\infin$，费用为 $C$ 的边。

- 对于每个空格，从它对应的纵向线索向它对应的横向线索连一条容量为 $+\infin$，费用为 $C$ 的边。

如此建模，我们可以模拟每一个修改操作，读者若无法理解也可以自己手推一下这些连边所代表的意思。

那么接下来的问题便变成了刚刚建模时的一个前提条件——“在当前局面合法的情况下”，我们需要在可接受的时间复杂度内找到一个合法局面才能进行如上的费用流操作。

观察游戏规则，注意到在每一个数字都可以自由修改的情况下，我们可以令每一个空格上的数字都为 $1$，而线索的数字则为其管辖的所有空格数，这个局面一定合法，我们称其为局面 $A$。

那么我们在跑费用流之前，先将整个局面修改为局面 $A$，并计算修改所需要的代价，记其为 $C_{frist}$。

但是还没有完，由于我们强制将原始局面变成了局面 $A$，对于每一个数值，在增加到原值的过程中我们实际上是在进行反悔操作。

于是我们需要在建模中增加代表反悔操作的边，具体建模如下：

- 对于每个线索和空格，边的起点和终点与其先前描述的边一致，但流量改为原始局面中的数值 $-$ 局面 $A$ 中的对应数值（若原始局面中的数值 $\le$ 局面 $A$ 中的对应数值，则可以不建此边），费用改为 $-C$。

对上面这张图跑费用流，当且仅当 SPFA 求出的到 $T$ 的最短路路程 $\ge 0$ 停止，如果此时费用流的费用为 $C_{second}$，那么原问题的最小费用即为 $C_{first} + C_{second}$，输出即可。

最后是无解的判断，我们可以将所有不准修改的点所建出的边的费用设为 $+\infin$，最后检查所有费用为 $\pm\infin$ 的边，若流量不为 $0$ 就代表费用流被逼迫使用这些不可修改的点去满足流量守恒，此时输出 $-1$ 即可。

代码如下：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct edge{
	int l, r, val, cost;
};
vector<int> nodes[6005];
vector<edge> alle;
int n, m, vis[6005], l, r, w, cnt, tim;
int s, t, ans, ecn, cur[6005];
int inf = 1e9, cost, dis[6005], v;
int spfa(){
	for(int i = 1; i <= t; i++){
		dis[i] = inf; vis[i] = 0;
		cur[i] = 0;
	}
	queue<int> spfa_q;
	dis[s] = 0, vis[s] = 1;
	spfa_q.push(s);
	while(spfa_q.size()){
		int nod = spfa_q.front();
		spfa_q.pop();
		vis[nod] = 0;
		for(int i = 0; i < nodes[nod].size(); i++){
			edge e = alle[nodes[nod][i]];
			if(e.val > 0 && dis[e.r] > dis[e.l] + e.cost){
				dis[e.r] = dis[e.l] + e.cost;
				if(vis[e.r] != t){
					spfa_q.push(e.r);
					vis[e.r] = t;
				}
			}
		}
	}
	return dis[t] < 0;
}
int dinic(int pos, int flow){
	if(pos == t){
		return flow;
	}
	vis[pos] = 1;
	int used = 0;
	for(int i = cur[pos]; i < nodes[pos].size(); i++){
		edge e = alle[nodes[pos][i]];
		cur[e.l] = i;
		if(e.val > 0 && dis[e.r] == dis[e.l] + e.cost && !vis[e.r]){
			int x = dinic(e.r, min(flow - used, e.val));
			if(x){
				cost += e.cost * x;
				alle[nodes[pos][i]].val -= x;
				alle[nodes[pos][i] ^ 1].val += x;
				used += x;
			}
			else{
			    dis[e.r] = inf;
			}
		}
		if(used == flow){
			return flow;
		}
	}
	vis[pos] = 0;
	return used;
}
void add_edge(int ll, int rr, int value, int cos_e){
	alle.push_back((edge){ll, rr, value, cos_e});
	nodes[ll].push_back(ecn);
	ecn++;
	alle.push_back((edge){rr, ll, 0, -cos_e});
	nodes[rr].push_back(ecn);
	ecn++;
}
int type[40][40], orijin[40][40][2], cost_change[40][40][2], hint_cnt[40][40];
int map_node[40][40], contain_node_cnt[2000], node_cnt, upper_parent[40][40], left_parent[40][40], C;
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    s = 2000, t = 2001;
    cin >> n >> m; 
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            cin >> type[i][j];
        }
    }
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            if(!type[i][j]) continue;
            cin >> orijin[i][j][0];
            if(type[i][j] == 3) cin >> orijin[i][j][1];
        }
    }
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            if(!type[i][j]) continue;
            cin >> cost_change[i][j][0];
            if(type[i][j] == 3) cin >> cost_change[i][j][1];
            if(cost_change[i][j][0] == -1) cost_change[i][j][0] = inf; 
            if(cost_change[i][j][1] == -1) cost_change[i][j][1] = inf; 
        }
    }
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            switch(type[i][j]){
                case 1:
                    node_cnt++; map_node[i][j] = node_cnt;
                    for(int k = i + 1; k <= n && type[k][j] == 4; k++){
                        contain_node_cnt[node_cnt]++;
                        upper_parent[k][j] = node_cnt;
                    }
                    if(contain_node_cnt[node_cnt] < orijin[i][j][0]){
                        add_edge(s, node_cnt, orijin[i][j][0] - contain_node_cnt[node_cnt], -cost_change[i][j][0]);
                    }
                    C += cost_change[i][j][0] * abs(orijin[i][j][0] - contain_node_cnt[node_cnt]);
                    add_edge(s, node_cnt, inf, cost_change[i][j][0]);
                    break;
                case 2:
                    node_cnt++; map_node[i][j] = node_cnt;
                    for(int k = j + 1; k <= n && type[i][k] == 4; k++){
                        contain_node_cnt[node_cnt]++;
                        left_parent[i][k] = node_cnt;
                    }
                    if(contain_node_cnt[node_cnt] < orijin[i][j][0]){
                        add_edge(node_cnt, t, orijin[i][j][0] - contain_node_cnt[node_cnt], -cost_change[i][j][0]);
                    }
                    C += cost_change[i][j][0] * abs(orijin[i][j][0] - contain_node_cnt[node_cnt]);
                    add_edge(node_cnt, t, inf, cost_change[i][j][0]);
                    break;
                case 3:
                    node_cnt++; map_node[i][j] = node_cnt;
                    for(int k = i + 1; k <= n && type[k][j] == 4; k++){
                        contain_node_cnt[node_cnt]++;
                        upper_parent[k][j] = node_cnt;
                    }
                    if(contain_node_cnt[node_cnt] < orijin[i][j][0]){
                        add_edge(s, node_cnt, orijin[i][j][0] - contain_node_cnt[node_cnt], -cost_change[i][j][0]);
                    }
                    C += cost_change[i][j][0] * abs(orijin[i][j][0] - contain_node_cnt[node_cnt]);
                    add_edge(s, node_cnt, inf, cost_change[i][j][0]);
                    node_cnt++; map_node[i][j] = node_cnt;
                    for(int k = j + 1; k <= n && type[i][k] == 4; k++){
                        contain_node_cnt[node_cnt]++;
                        left_parent[i][k] = node_cnt;
                    }
                    if(contain_node_cnt[node_cnt] < orijin[i][j][1]){
                        add_edge(node_cnt, t, orijin[i][j][1] - contain_node_cnt[node_cnt], -cost_change[i][j][1]);
                    }
                    C += cost_change[i][j][1] * abs(orijin[i][j][1] - contain_node_cnt[node_cnt]);
                    add_edge(node_cnt, t, inf, cost_change[i][j][1]);
                    break;
                case 4:
                    if(orijin[i][j][0] > 1){
                        add_edge(upper_parent[i][j], left_parent[i][j], orijin[i][j][0] - 1, -cost_change[i][j][0]);
                    }
                    C += cost_change[i][j][0] * abs(orijin[i][j][0] - 1);
                    add_edge(upper_parent[i][j], left_parent[i][j], inf, cost_change[i][j][0]);
                    break;
            }
        }
    }
    while(spfa()){
        ans += dinic(s, inf);
    }
    for(int i = 0; i < ecn; i += 2){
        if(alle[i].cost == inf && alle[i ^ 1].val) return cout << -1, 0;
        if(alle[i].cost == -inf && alle[i].val) return cout << -1, 0;
    }
    cout << cost + C << '\n';
}
``````

---

## 作者：Drind (赞：2)

### 题目解析

这题让我们修改一个 Kakuro 游戏的局面（大概率是错误的）。其中给出修改任意格子里的数小号的权值（包括限制也可以修改），而且数字不局限于一到九之间，只要是正整数就行。

首先，让我们先构造一个符合 Kakuro 游戏的局面，显然最简单的就是所有格子全是 1，然后限制条件是它限制的格子个数，先把他给的局面修改成这个吧。

但是这样太不好了，因为我们根本没考虑他给的局面，所以这个 naive 的构造需要修改。对于每次修改，我们显然要同时改三个值（格子里的数，左边限制条件和上边的限制条件）。而每次修改只会影响这些东西而不会影响别的。

所以我们建立费用流模型，我们把限制条件当成点，从源点向横向限制条件连边，横向限制条件向竖向限制条件连边，竖向限制条件向汇点连边，这样每条增广路就能同时修改三个值了。

然后我们发现有时候修改是更接近初始条件，而有的修改要离初始条件更远，具体地，每个边能让权值更小的修改次数只有初始条件的数减去 naive 构造中的数的次数。所以我们拿这个次数作为流量连一个费用负的边，然后连一个无限流量，费用正的边。

注意没法改的格子边权设为无限大。

最后跑最小费用可行流即可。

如果费用被设为无限大的边被流过或费用无限小的边没流满即无解。

在程序的具体实现中，最小费用可行流意味着每次 spfa 发现到汇点的最短路大于 0 了就可以退出了（再增广不优）。

费用流模板依照上面稍微魔改一下，省略模板代码如下：


```cpp
int ty[31][31];//这个格子的类型
int dn[31][31];//如果是限制格子，那么向下限制
int rt[31][31];//如果是限制格子，那么向右限制
int val[31][31];//如果是普通格子，权值
int upbel[31][31];//普通格子的上方限制
int lfbel[31][31];//普通格子的左方限制
int countd[31][31];//限制格子下方有多少普通格子
int countr[31][31];//限制格子右方有多少普通格子
int id[2][31][31];//限制格子对应图中节点的映射

bool check(){//判断无解
	for(int i=0;i<=cnt;i+=2){
		if((edge[i].cost==inf&&edge[i^1].flow>0)||(edge[i].cost==-inf&&edge[i].flow>0))
			return false;
	}
	return true;
}

inline void fake_main(){
	memset(head,-1,sizeof head);
	int n,m; cin>>n>>m; int res=0;
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++){//初始化映射
		cin>>ty[i][j];
		if(ty[i][j]==1||ty[i][j]==3) id[0][i][j]=++res;
		if(ty[i][j]==2||ty[i][j]==3) id[1][i][j]=++res;
	} 
	s=++res; t=++res;
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++){
		if(ty[i][j]==0) continue;
		if(ty[i][j]==1||ty[i][j]==3) cin>>dn[i][j];
		if(ty[i][j]==2||ty[i][j]==3) cin>>rt[i][j];
		if(ty[i][j]==4) cin>>val[i][j]; 
	}
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++){//找限制格子的限制区间
		if(ty[i][j]==1||ty[i][j]==3){
			for(int r=i+1;r<=n;r++){
				if(ty[r][j]!=4) break;
				upbel[r][j]=id[0][i][j];
				countd[i][j]++;
			}
		}
		if(ty[i][j]==2||ty[i][j]==3){
			for(int r=j+1;r<=m;r++){
				if(ty[i][r]!=4) break;
				lfbel[i][r]=id[1][i][j];
				countr[i][j]++;
			}
		}
	}
	
	int ans=0;
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++){//加边，注意我们做成 naive 构造的时候也是需要费用的，先算出来，一会儿求出可行流费用再减掉。
		if(ty[i][j]==1||ty[i][j]==3){
			int val; cin>>val; if(val==-1) val=inf;
			ans+=abs(countd[i][j]-dn[i][j])*val;
			if(dn[i][j]>countd[i][j]) adde(s,id[0][i][j],dn[i][j]-countd[i][j],-val);
			adde(s,id[0][i][j],inf,val);
		}
		if(ty[i][j]==2||ty[i][j]==3){
			int val; cin>>val; if(val==-1) val=inf;
			ans+=abs(countr[i][j]-rt[i][j])*val;
			if(rt[i][j]>countr[i][j]) adde(id[1][i][j],t,rt[i][j]-countr[i][j],-val);
			adde(id[1][i][j],t,inf,val);
		}
		if(ty[i][j]==4){
			int tmp; cin>>tmp; if(tmp==-1) tmp=inf;
			ans+=abs(val[i][j]-1)*tmp;
			if(val[i][j]>1) adde(upbel[i][j],lfbel[i][j],val[i][j]-1,-tmp);
			adde(upbel[i][j],lfbel[i][j],inf,tmp);
		}
	}
	mncos=0; mcmf();
	if(!check()) cout<<"-1\n";
	else cout<<ans+mncos<<"\n";
}

signed main(){
	ios::sync_with_stdio(false);
	int t; t=1;
	while(t--) fake_main();
}
```

---

## 作者：FutaRimeWoawaSete (赞：1)

**P4486 sol**

需要注意的题意上的理解：

- 任意一个空格会且仅会被两个线索约束；

- 空格内填的数是正整数就行，不需要确定范围在 $[0,9]$。

~~我刚开始就理解错了。~~

一道很基础的题，考察选手对于网络流基础建图套路的缝合利用。

首先我们有一个很直觉上的建图想法：一定要将图上的流量达到平衡。其他的 trick 我们可以先不想。

- 观察图中与“二”相关的信息；

于是我们有了建图的大致雏形：将 $S$ 一边作为左下角线索类型的流量，将 $T$ 一边作为右上角线索类型的流量。肯定是用跑最小费用流这样的结构。

- 对于两种操作，我们可以先暴力执行一种操作到底使我们需要的操作只有一种；

这个 trick 在[这道题](https://www.luogu.com.cn/problem/P6967)里也有所出现。

对于此题较为麻烦，我刚开始想用上下界套这个做发现建出来的图极其繁琐，后来发现我们可以直接令所有空格都填 $1$，然后更新出一个初始解，甚至可以直接扔掉上下界，就好建很多了。

- 费用流的凸性

书接上文，我们发现我们还需要处理一种情况：假如在最后构造的答案中你得到的一个点权值 $w$ 比初始给定的 $v$ 还大，你的最优构造方案显然不是 $v \rightarrow 1 \rightarrow w$ 而是 $v \rightarrow w$ 对吧，所以我们利用费用流的凸性，直接拆成两类连边，一类表示回退（显然它的费用应该是负数）一类表示正常的扩增。

然后我们发现，这个初始化也很有用处：因为流已经合法，所以直接跑最小费用可行流就好了！！！！

以上全是思路的讲解，接着我们梳理一下建图：

-----------------------------------------------------------

我们设 $v(x,y)$ 是初始方格 $(x,y)$ 的权值，$w(x,y)$ 是初始化（空格全填 $1$，线索各相应构造）时的权值；$id(x,y)$ 表示点 $(x,y)$ 在网络流上的对应节点；$d(x,y)$ 代表节点 $(x,y)$ 修改时所需的代价。

- 将左下角线索对应 $S$ 一侧，将右上角线索对应 $T$ 一侧；同时我们视空格为边；

- 以左下角线索 $(x,y)$ 为例，若 $w(x,y) \leq v(x,y)$，我们从 $S$ 向 $id(x,y)$ 连容量为 $v(x,y)-w(x,y)$，边权为 $-d(x,y)$ 的边；然后对所有左下角线索我们连容量为 $+\infty$，边权为 $d(x,y)$ 代表正常的扩增；

- 对于右上角线索同理，向 $T$ 连类似左下角线索的边即可；

- 对于空格 $(x,y)$，我们对于对应的两个线索 $id(a,b),id(c,d)$，若 $w(x,y) \leq v(x.y)$ 先将 $id(a,b),id(c,d)$ 之间连容量为 $v(x,y)-w(x,y)$ 边权为 $-d(x,y)$ 的边代表回退；然后连容量 $+\infty$ 边权为 $d(x,y)$ 的边代表正常扩增。

跑最小费用可行流，注意到此时我们没有上下界且要求费用最小，所以每次看到 $T$ 的最短路是否 $\geq 0$ 即可一直跑。

讲一下比较棘手的无解判断，我之前想的很复杂（当然其实复杂点也没什么这里已经不是最重点了），后来看到别人写了一种很简单的方法，就是我们可以考虑对于不能修改的点，我们根据费用流的凸性将其分为了回退边和扩增边，对于回退边我们强制令流量为 $-\infty$ 令扩增边的流量强制为 $+\infty$，这样就强制了每个不能修改的节点流量固定，只需要看最后的答案是否超过 $+\infty$ 或者检查这些边是否流满/流过就行了。

```cpp
/*
先套路地将数字+1-1转化为只加一
考虑将线索作为网络流的 S，T 一边。 
*/
#include "bits/stdc++.h"
using namespace std;
#define int ll
#define ll long long
const int Len = 2e4 + 5 , Inf = 1e9;
const ll inf = 1e18;
struct node
{
	int from,next,to,w,ww;
};
int pp[105][105],cc[105][105],v[105][105],rc[105][105],src[105][105],scr[105][105],cr[105][105],op[105][105],id[2][105][105],S,T;
struct Mg
{
	int x,y,w,ww;
	Mg(){x = y = w = ww = 0;}
	Mg(int X,int Y,int W,int WW){x = X , y = Y , w = W , ww = WW;}
}mg[Len << 3];int n,m,q,tp[105][105],tt;
struct maxflow
{
	int n,m,head[Len],cnt,dis[Len],cur[Len],flag[Len],flaw[Len],S,T,tt,mincost;
	node edge[Len << 1];
	maxflow(){cnt = 1;}
	inline void add(int from,int to,int w,int ww)
	{
		edge[++ cnt].to = to;
		edge[cnt].from = from;
		edge[cnt].next = head[from];
		edge[cnt].w = w;
		edge[cnt].ww = ww;
		head[from] = cnt;
	}
	inline void adeg(int from,int to,int w,int ww){add(from , to , w , ww);add(to , from , 0 , -ww);}
	inline int BFS()
	{
		queue<int> Q;
		for(int i = 1 ; i <= tt ; i ++) dis[i] = inf , cur[i] = flag[i] = flaw[i] = 0;
		dis[S] = 0 , cur[S] = head[S] , flaw[S] = 1 , Q.push(S);
		while(!Q.empty())
		{
			int p = Q.front();Q.pop();
			flaw[p] = 0;
			for(int e = head[p] ; e ; e = edge[e].next)
			{
				int to = edge[e].to;
				if(dis[to] > dis[p] + edge[e].ww && edge[e].w)
				{
					dis[to] = dis[p] + edge[e].ww;
					cur[to] = head[to];
					if(!flaw[to]) flaw[to] = 1 , Q.push(to);
				}
			}
		}
		return dis[T] < 0;
	}
	int dfs(int u,int In)
	{
		if(u == T) return In;
		flag[u] = 1;
		int Out = 0;
		for(int e = cur[u] ; e && In > 0 ; e = edge[e].next)
		{
			cur[u] = e;
			int to = edge[e].to;
			if(dis[to] == dis[u] + edge[e].ww && edge[e].w && !flag[to])
			{
				int res = dfs(to , min(In , edge[e].w));
				In -= res;
				Out += res;
				edge[e].w -= res;
				edge[e ^ 1].w += res;
				mincost += 1ll * res * edge[e].ww;
			}
		}
		flag[u] = 0;
		if(!Out) dis[u] = 0;
		return Out;
	}
	void work()
	{
		int res = 0;
		//for(int i = 1 ; i <= m ; i ++) adeg(mg[i].x , mg[i].y , mg[i].w , mg[i].ww);
		while(BFS()) res += dfs(S , Inf);
	}
	inline bool check(){for(int e = 2 ; e <= cnt ; e += 2)if((edge[e].ww == Inf && edge[e ^ 1].w > 0) || (edge[e].ww == -Inf && edge[e].w > 0))return 0;return 1;}
}M;
inline int Iabs(int x){if(x < 0) x = -x;return x;}
signed main()
{
	scanf("%lld %lld",&n,&m);
	for(int i = 1 ; i <= n ; i ++)
		for(int j = 1 ; j <= m ; j ++)
		{
			scanf("%lld",&op[i][j]);
			if(op[i][j] == 1 || op[i][j] == 3) id[0][i][j] = ++ tt;
			if(op[i][j] == 2 || op[i][j] == 3) id[1][i][j] = ++ tt;
		}
	S = ++ tt , T = ++ tt;
	for(int i = 1 ; i <= n ; i ++)
		for(int j = 1 ; j <= m ; j ++)
		{
			if(!op[i][j]) continue;
			if(op[i][j] == 1 || op[i][j] == 3) scanf("%lld",&rc[i][j]);
			if(op[i][j] == 2 || op[i][j] == 3) scanf("%lld",&cr[i][j]);
			if(op[i][j] == 4) scanf("%lld",&v[i][j]);
		}
	for(int i = 1 ; i <= n ; i ++)
		for(int j = 1 ; j <= m ; j ++) 
		{
			if(op[i][j] == 1 || op[i][j] == 3)
			{
				for(int k = i + 1 ; k <= n ; k ++)
				{
					if(op[k][j] != 4) break;
					pp[k][j] = id[0][i][j];
					src[i][j] ++;
				}
			}
			if(op[i][j] == 2 || op[i][j] == 3)
			{
				for(int k = j + 1 ; k <= m ; k ++) 
				{
					if(op[i][k] != 4) break;
					cc[i][k] = id[1][i][j];
					scr[i][j] ++;
				}
			}
		}
	ll as = 0;
	for(int i = 1 ; i <= n ; i ++)
		for(int j = 1 ; j <= m ; j ++)
		{
			if(op[i][j] == 1 || op[i][j] == 3)
			{
				int x;scanf("%lld",&x);if(x == -1) x = Inf;
				as += Iabs(src[i][j] - rc[i][j]) * x;
				if(rc[i][j] > src[i][j]) M.adeg(S , id[0][i][j] , rc[i][j] - src[i][j] , -x);
				M.adeg(S , id[0][i][j] , Inf , x);
			}
			if(op[i][j] == 2 || op[i][j] == 3)
			{
				int x;scanf("%lld",&x);if(x == -1) x = Inf;
				as += Iabs(scr[i][j] - cr[i][j]) * x;
				if(cr[i][j] > scr[i][j]) M.adeg(id[1][i][j] , T , cr[i][j] - scr[i][j] , -x);
				M.adeg(id[1][i][j] , T , Inf , x);
			}
			if(op[i][j] == 4)
			{
				int x;scanf("%lld",&x);if(x == -1) x = Inf;
				as += Iabs(v[i][j] - 1) * x;
				if(v[i][j] > 1) M.adeg(pp[i][j] , cc[i][j] , v[i][j] - 1 , -x);
				M.adeg(pp[i][j] , cc[i][j] , Inf , x);
			}
		} 
	M.S = S , M.T = T , M.tt = tt;
	M.work();
	if(!M.check()) return puts("-1") & 0;
	printf("%lld\n",as + M.mincost);
	return 0;
}
```

---

