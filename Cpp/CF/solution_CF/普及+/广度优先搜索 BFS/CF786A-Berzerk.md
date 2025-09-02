# Berzerk

## 题目描述

Rick 和 Morty 在玩一个版本的 Berzerk 游戏。这个游戏需要很大的空间，所以他们使用电脑玩这个游戏。

游戏中有 $n$ 个标号从 $1 \sim n$ 的物体围成一个圆圈（顺时针标号）， 物体 $1$ 表示黑洞，其它物体表示星
球，且某一个星球上有一个怪物，Rick 和 Morty 不知道这个怪物在哪个星球上，只知道这个怪物在游
戏开始时没有进入黑洞。但就目前而言，他们希望为每种可能的情况做好准备。

Rick 和 Monty 每人有一个数的集合，集合中的数在 $[1,n-1]$ 之间。Rick 的集合是 $s_1$，其中有 $k_1$ 个
数，Morty 的集合是 $s_2$，其中有 $k_2$ 个数。游戏开始后，两人轮流操作。在操作中，玩家必须从他的集
合中选出一个数 $x$，怪物将从当前位置顺时针移动 $x$ 个位置，如果怪物移动后进入了黑洞，则该玩家获胜。

你的任务是对于每一个怪物的位置以及玩家先后手顺序，判断游戏先手获胜、后手获胜、无限循环。（每个玩家都采取最优操作）

## 样例 #1

### 输入

```
5
2 3 2
3 1 2 3
```

### 输出

```
Lose Win Win Loop
Loop Win Win Win
```

## 样例 #2

### 输入

```
8
4 6 2 3 4
2 3 6
```

### 输出

```
Win Win Win Win Win Win Win
Lose Win Lose Lose Win Lose Lose
```

# 题解

## 作者：Siyuan (赞：26)

[$$\Large\texttt{My Blog}$$](https://hydingsy.github.io/articles/problem-Codeforces-786A-Berzerk/)

---

## Description

> 题目链接：[Codeforces 786A](https://codeforces.com/contest/786/problem/A)

Rick 和 Morty 在玩一个版本的 Berzerk 游戏。这个游戏需要很大的空间，所以他们使用电脑玩这个游戏。

游戏中有 $n$ 个标号从 $1\sim n$ 的物体围成一个圆圈（顺时针标号）， 物体 $1$ 表示黑洞，其它物体表示星球，且某一个星球上有一个怪物，Rick 和 Morty 不知道这个怪物在哪个星球上，只知道这个怪物在游戏开始时没有进入黑洞。但就目前而言，他们希望为每种可能的情况做好准备。

Rick 和 Monty 每人有一个数的集合，集合中的数在 $[1,n-1]$ 之间。Rick 的集合是 $s_1$，其中有 $k_1$ 个数，Morty 的集合是 $s_2$，其中有 $k_2$ 个数。 游戏开始后，两人轮流操作。在操作中，玩家必须从他的集合中选出一个数 $x$， 怪物将从当前位置顺时针移动 $x$ 个位置，如果怪物移动后进入了黑洞，则该玩家获胜。

你的任务是对于每一个怪物的位置以及玩家先后手顺序，判断游戏先手获胜、后手获胜、无限循环。（每个玩家都采取最优操作）

数据范围：$2\le n\le 7000$，$1\le k_1,k_2\le n-1$，$1\le s_{i,j}\le n-1$

------

## Solution

**博弈论**有一个经典的结论：

> **能转移到必败态的状态就是必胜态，只能转移到必胜态的状态就是必败态。**

现在我们知道 $1$ 是**必败态**，那么我们通过 $\text{DFS}$ 可以判断每个点的胜负情况、是否有解。

我们考虑**逆向思维**，对每个玩家在 $1$ 时的先手状态向前转移，具体过程如下：

1. 定义 $\text{DFS}(v,now)$ 表示现在是 $now$ 的位置，玩家 $v$ 先手。
2. 枚举上一次玩家 $u$ 的操作 $x$，那么可以从 $now-x$ 的位置转移到 $now$ 的位置（注意这里的 $now-x$ 不能等于 $1$）。
3. 如果 $now$ 的位置是**必败态**，那么根据结论：**能转移到必败态的状态就是必胜态**，可以得到 $now-x$ 的位置是必胜态。
4. 如果 $now$ 的位置是**必胜态**，那么根据结论：**只能转移到必胜态的状态就是必败态**。我们记 $cnt_{u,i}$ 表示在 $i$ 这个位置且 $u$ 先手可以转移到的必胜态数量。当 $cnt_{u,now-x}+1=k_u$ 时，意味着从 $(u,now-x)$ 转移到的所有状态都是必胜态，那么意味着从 $(u,now-x)$ 这个状态为必败态。
5. 继续 $\text{DFS}(u,now-x)$ 进行转移即可。

**时间复杂度**：$O(n^2)$

------

## Code

```cpp
#include <cstdio>
#include <algorithm>

const int N=7e3+5;
int n,k[2],a[2][N],cnt[2][N];
bool vis[2][N],win[2][N];

void dfs(int v,int now) {
	if(vis[v][now]) return;
	vis[v][now]=1;
	int u=v^1;
	for(int i=1;i<=k[u];++i) {
		int pre=(now-a[u][i]+n-1)%n+1;
		if(pre==1) continue;
		if(!win[v][now]) {
			win[u][pre]=1;
			dfs(u,pre);
		} else if(++cnt[u][pre]==k[u]) {
			win[u][pre]=0;
			dfs(u,pre);
		}
	}
}
int main() {
	scanf("%d",&n);
	for(int o=0;o<=1;++o) {
		scanf("%d",&k[o]);
		for(int i=1;i<=k[o];++i) scanf("%d",&a[o][i]);
	}
	dfs(0,1),dfs(1,1);
	for(int o=0;o<=1;++o) {
		for(int i=2;i<=n;++i) {
			printf("%s%c",vis[o][i]?win[o][i]?"Win":"Lose":"Loop"," \n"[i==n]);
		}
	}
	return 0;
}
```



---

## 作者：_ZSR_ (赞：2)

### [ CF786A Berzerk](https://www.luogu.com.cn/problem/CF786A)

不同于一般的博弈论，这是一道非公平组合游戏的题。但是博弈论本身的一些特性还是没有改变。如果一个状态可以转移到必败态，那么它就是必胜态。如果一个状态只能转移到必胜态，那么它就是必败态。

显然，对于这道题来时，$1$ 是一个必败态。那么我们就可以从 $1$ 开始进行两遍搜索。令 $f_{i,j}$ 表示第 $i$ 个人在位置 $j$ 的状态。$f_{i,j}=0$ 表示循环态，$f_{i,j}=1$ 表示必胜态，$f_{i,j}=2$ 表示必败态。

假设当前的状态为 $f_{v,i}$，那么对于它的一个前驱状态 $f_{u,j}$，如果 $f_{v,i}=1$，那么就尽量不要让 $u$ 走过来，因为如果走过来 $v$ 就必胜了。如果 $u$ 无路可走了，也就是它只能转移到必胜态，那么它就是一个必败态。可以维护度数来实现这一系列操作。如果度数减到 $0$ 了就说明无路可走了。至于循环太，没有遍历到的就是循环态。

code
```
#include <bits/stdc++.h>
using namespace std;
const int N=7e3+10;
typedef pair<int,int> pii;
int n;
int a[2][N],b[2];
int f[2][N];
int deg[2][N];
inline int pre (int x, int y)
{
    return (x-y+n-1)%n+1;
}
void solve () {
	queue<pii> q;
	f[0][1]=f[1][1]=2;
	q.push({1,0});
	q.push({1,1});
	while (q.size()) 
    {
		auto it=q.front(); 
        q.pop();
		int u=it.first,d=it.second;
		for (int i=1;i<=b[!d];++i) 
        {
			int v=pre(u,a[!d][i]);
			if (f[!d][v]) continue;
			if (f[d][u]==1) 
            {
				if (--deg[!d][v]==0) 
                {
					f[!d][v]=2;
					q.push({v,!d});
				}
			}
			else 
            {
				f[!d][v]=1;
				q.push({v,!d});
			}
		}
	}
}
int main () 
{
	scanf("%d",&n);
	for (int i=0;i<2;++i) 
    {
		scanf("%d",&b[i]);
		for (int j=1;j<=b[i];++j)
		{
            scanf("%d",&a[i][j]);
        }
	}
	for (int i=0;i<2;++i)
    {
        for (int j=2;j<=n;++j)
        {
            deg[i][j]=b[i];
        }
    }
	solve();
	for (int i=0;i<2;++i)
    {
        for (int j=2;j<=n;++j) 
        {
			if (f[i][j]==0) printf("Loop ");
			if (f[i][j]==1) printf("Win ");
			if (f[i][j]==2) printf("Lose ");
		}
        puts("");
    }
	return 0;
}
```


---

## 作者：yimuhua (赞：2)

首先博弈论有结论：

**能转移到必败态的状态为必胜态，只能转移到必胜态的状态为必败态**。

#### 证明：

假设现在有一个必败态为玩家 $B$ 先手，则上一步为玩家 $A$。因为当前状态为必败态，玩家 $A$ 必然会走到当前状态，则玩家 $A$ 必胜。

若当前状态为玩家 $A$ 先手，且只能转移到必胜态，则玩家 $B$ 必胜，玩家 $A$ 必败。

#### 证毕。

然后因为 $1$ 是必败态，于是考虑倒推：

使用记忆化搜索，```dfs(x, f)``` 表示现在在 $x$ 位置，玩家 $f$ 先手。

枚举上一次操作选的数 $k$，可从 $x-k$ 转移至 $x\ (x-k\neq 1)$，依照结论转移即可。

时间复杂度为 $O(n^2)$。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
bool vis[2][7005], win[2][7005];
int n, b[2], a[2][7005], cnt[2][7005];
void dfs(bool f, int x) {
    if(vis[f][x])
        return;
    vis[f][x] = 1, f = !f;
    for(int i = 1; i <= b[f]; i++) {
        int pre = (x - a[f][i] + n - 1) % n + 1;
        if(pre ^ 1) {
            if(!win[!f][x])
                win[f][pre] = 1, dfs(f, pre);
            else if(++cnt[f][pre] == b[f])
                win[f][pre]= 0, dfs(f, pre);
        }
    }
    return;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    for(int i = 0; i < 2; i++) {
        cin >> b[i];
        for(int j = 1; j <= b[i]; j++)
            cin >> a[i][j];
    }
    dfs(0, 1), dfs(1, 1);
    for(int i = 0; i < 2; i++) {
        for(int j = 2; j <= n; j++)
            cout << (vis[i][j] ? win[i][j] ? "Win " : "Lose " : "Loop ");
        cout << '\n';
    }
    return 0;
}
```


---

## 作者：Hanx16Kira (赞：2)

# CF786A Berzerk

[Luogu CF786A](https://www.luogu.com.cn/problem/CF786A)

[Codeforces 786A](http://codeforces.com/problemset/problem/786/A)

## Solution

考虑从终止状态倒推回来。设 $f(i, 1/2)$ 表示某一个局面的胜负情况，$i$ 表示当前位置，$1/2$ 表示当前是 Alice 还是 Bob 先手（下面 $1$ 对应 Alice，简称 A，$2$ 对应 Bob，简称 B），定义如下：

$$
f(i,1/2) = 
\begin{cases}
-1 &,\text{先手当前必败} \\
0 &, \text{不确定，即循环} \\
1 &, \text{先手当前必胜}
\end{cases}
$$

会发现：

- 如果当前局面是必败局面，那可以转移到当前局面的上一个局面一定是必胜局面（既然可以获胜，那么先手就一定会选择走到这个局面）。
- 如果当前局面是必胜局面，那可以转移到当前局面的上一个局面不一定是必败局面，只当上一个局面所有可以转移到的局面都是必胜局面时才是必败局面。

这么说可能不好理解，画一下图会更好理解。

![](https://cdn.luogu.com.cn/upload/image_hosting/z4d7muan.png)

用样例来说，上面一行表示 A 先手，下面一行表示 B 先手，可以发现 $(1,1)$ 以及 $(2,1)$ 肯定是必败局面，那么可以转移到当前状态的 $(2,3),(2,4),(1,3),(1,4),(1,5)$ 就一定是必胜局面。接着发现 $(2,2)$ 的所有可能的下一种局面（$(1,4),(1,5)$）都是必胜局面，所以 $(2,2)$ 就是必败局面。这时候发现 $(1,2),(2,5)$ 没法计算，因此 $(1,2),(2,5)$ 对应的就是 Loop。

具体到代码实现上可以使用拓扑排序。如果当前是必败局面则把所有可能的上一个局面记录为必胜并加入队列，如果是必胜则减少入度，如果入度为 $0$ 则说明所有可能局面都是必胜的，标记为必败并加入队列。

另外此题不可以暴力连边，一是加边量大，约为 $2n^2$，用 `vector` 会直接超时，并且访问量也大，所以用链式前向星的内存访问不连续也会超时。而且 $2n^2$ 的数组会直接 MLE。所以可以不暴力连边，每次访问到的时候再计算即可，具体实现可以参考代码。

### Code

```cpp
#include<bits/stdc++.h>

using namespace std;

namespace Hanx16qwq {
constexpr int _SIZE = 7e3;
int n, k1, k2;
int m1[_SIZE + 5], m2[_SIZE + 5];
int deg[(_SIZE << 1) + 5];

int Num(int x, int type) {return (type - 1) * n + x;} 

int GetPre(int x, int step) {return (x - step + n - 1) % n + 1;} 

int flag[(_SIZE << 1) + 5]; 

void Topo() {
    queue<pair<int, int>> q;
    q.emplace(Num(1, 1), -1);
    q.emplace(Num(1, 2), -1);
    flag[Num(1, 1)] = flag[Num(1, 2)] = -1;

    while (!q.empty()) {
        int cur = q.front().first, wol = q.front().second; q.pop();

        if (cur <= n) { // 第一行
            for (int i = 1; i <= k2; i++) {
                int twd = Num(GetPre(cur, m2[i]), 2);
                --deg[twd];

                if (flag[twd] != 0) continue;

                if (wol == -1) flag[twd] = 1, q.emplace(twd, 1);
                else if (!deg[twd]) flag[twd] = -1, q.emplace(twd, -1);
            }
        } else { // 第二行
            for (int i = 1; i <= k1; i++) {
                int twd = Num(GetPre(cur, m1[i]), 1);
                --deg[twd];
                
                if (flag[twd] != 0) continue;

                if (wol == -1) flag[twd] = 1, q.emplace(twd, 1);
                else if (!deg[twd]) flag[twd] = -1, q.emplace(twd, -1);
            }
        }
    }
}
void main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n;
    cin >> k1;

    for (int i = 1; i <= k1; i++) cin >> m1[i];

    cin >> k2;

    for (int i = 1; i <= k2; i++) cin >> m2[i];

    fill(deg + 1, deg + n + 1, k1); // 第一行入度全为 k1
    fill(deg + n + 1, deg + (n << 1) + 1, k2); // 第二行入度全为 k2
    Topo();
    
    for (int i = 1; i <= 2; i++, cout << '\n')
        for (int j = 2; j <= n; j++)
            switch (flag[Num(j, i)]) {
                case -1 : cout << "Lose" << ' '; break;
                case 0  : cout << "Loop" << ' '; break;
                default : cout << "Win" << ' ';
            }
}

}
signed main() {
    Hanx16qwq::main();
    return 0;
}
```

---

## 作者：George_Je (赞：2)

首先需要明确的是，与经典的博弈论模型 $\text{Nim}$ 游戏、$\text{Wythoff}$ 游戏不同，这是一道 **非公平组合游戏（$\text{Partizan Game}$）**。但根据博弈论的基本知识，以下几点仍然成立：

- 每个局势要么是必胜态（对应题目中的 $\text{Win}$），要么是必败态（对应题目中的 $\text{Lose}$），要么是“循环态”（对应题目中的 $\text{Loop}$，指既不是必胜态也不是必败态的状态，游戏会一直进行）。
- 没有后继状态的状态是必败态。
- 如果后继状态存在必败态，那么此状态是必胜态。
- 如果后继状态不存在必败态但存在循环态，那么此状态是循环态。
- 如果后继状态不存在必败态也不存在循环态（全都是必胜态），那么此状态是必败态。

具体地，设 $f(i,j)$ 表示第 $j$ 个人在第 $i$ 个位置的状态：
$$
f(i,j)=\begin{cases}0&\text{循环态}\\1&\text{必胜态}\\2&\text{必败态}\end{cases}
$$
初始条件：
$$
f(i,j)=\begin{cases}2&i=1\\0&\text{otherwise.}\end{cases}
$$
考虑怎么转移。把整个游戏看作一张有向图，注意到这张图是有环存在的，所以不能正着搜索（因为这样会出现“自己依赖自己”的情况）。因此我们采取类似拓扑排序的方法。具体地，若 $f(u,i)=2$，那么 $u$ 的所有前驱状态 $v$ 都有 $f(v,\neg i)=1$；若 $f(u,i)=1$，那么我们就假设 $v$ 不会走到 $u$（在代码中就是 $v$ 的出度 $-1$），但是根据“**没有后继状态的状态是必败态**”，如果一个状态“无路可走”了，那么它就是必败态了，此时我们就要将它加入广搜队列里。最后没有入过队的就是循环态。看代码很好理解。
```cpp
#include <bits/stdc++.h>
using namespace std;
constexpr int N = 7e3, MAX_N = N + 3;
int n, a [MAX_N] [2], m [2];
int f [MAX_N] [2];
int deg [MAX_N] [2];
inline int pre (int x, int y)
	{return (x - y + n - 1) % n + 1;}
void solve () {
	static queue <pair <int, bool>> Q;
	f [1] [0] = f [1] [1] = 2;
	Q.push ({1, 0});
	Q.push ({1, 1});
	while (!Q.empty ()) {
		auto it = Q.front (); Q.pop ();
		int u = it.first; bool d = it.second;
		for (int i = 1; i <= m [!d]; ++i) {
			int v = pre (u, a [i] [!d]);
			if (f [v] [!d]) continue;
			if (f [u] [d] == 1) {
				if (--deg [v] [!d] == 0) {
					f [v] [!d] = 2;
					Q.push ({v, !d});
				}
			}
			else {
				f [v] [!d] = 1;
				Q.push ({v, !d});
			}
		}
	}
}
signed main () {
	ios::sync_with_stdio (false);
	cin.tie (nullptr);
	cout.tie (nullptr);
	cin >> n;
	for (int d = 0; d < 2; ++d) {
		cin >> m [d];
		for (int i = 1; i <= m [d]; ++i)
			cin >> a [i] [d];
	}
	for (int d = 0; d < 2; ++d)
		for (int i = 2; i <= n; ++i)
			deg [i] [d] = m [d];
	solve ();
	for (int d = 0; d < 2; ++d, cout << '\n')
		for (int i = 2; i <= n; ++i) {
			if (f [i] [d] == 0) cout << "Loop ";
			if (f [i] [d] == 1) cout << "Win ";
			if (f [i] [d] == 2) cout << "Lose ";
		}
}
```

---

## 作者：WZKQWQ (赞：0)

这题其实有点像[联合省选 2023D2T1 过河卒](https://www.luogu.com.cn/problem/P9169)，都是给可以接受的数量个状态，以及它们之间的转移，然后有一些已知的必败必胜态，求每个状态是必败态，必胜态，还是循环态。

我们知道如果一个状态是可以转移到必胜态，那么它就是必胜态，只能转移到必败态就是必败态，否则是循环态，所以照着这个 $\text{bfs}$ 即可，听谷群的说这个叫 $\text{min-max}$ 对抗搜索。

具体的说，如果一个状态被必胜态访问到那么直接设为必胜态加入队列，如果被必败态访问到那么计数器自增，如果计数器等于出度（反图上的入度），就设为必败态加入队列。操作结束后没设置的就是循环态。

ps：必败必胜态取决与当前的先手是谁。

复杂度 $O(n^2)$，代码不放了。

---

## 作者：xfrvq (赞：0)

[$\tt Link$](/problem/CF786A)，$\tt^{\ast}2000$。

博弈论基本常识：

+ 状态能且仅能分为（先手）必胜和必败两类。
+ 经过状态变化，必败 $\iff$ 一定只能变成必胜，必胜 $\iff$ 存在方案变成必败。

这个博弈对两个人而言并不对称，所以必胜和必败是针对一个人而言的。

$n$ 小，考虑暴力记忆化搜索，计算每个点对于两个人分别是必胜还是必败，记为 $f_i,g_i\in\{0,1\}$。

考虑转移，记当前的状态为 $cur$ 代表当前位置。

+ 我们只会从下一步走的人的集合 $S$ 里取出 $x\in S$，然后 $cur\to cur-x$，当然这个 $cur-x$ 需要对 $n$ 取模。
+ 如果 $cur$ 是必败，因为能到必败的就是必胜，所以 $cur-x$ 一定必胜。
+ 如果 $cur$ 是必胜，需要记 $cnt$ 代表有几个必胜能到这个状态，如果这个 $cnt$ 已经等于可能的状态总数，那么 $cur-x$ 必败。

[$\tt code$](https://codeforces.com/problemset/submission/786/168971556)。

---

## 作者：7KByte (赞：0)

博弈好题。

首先这道题不是组合游戏，SG 函数无法使用。

但是根据博弈常识我们可以知道。

如果当前状态能到达一个必败状态，则当前为必胜态。

如果当前状态能够到达的状态都是必胜态，则当前状态为必败态。

否则这个游戏无法结束。

所以我们设计状态 $f[i][0/1]$ ，表示第 $i$ 个位置，Rick 或 Morty 先手，必胜还是必败。

初始为 $f[1][0/1]=-1$，转移为$f[i][op]\to f[k][op\ \rm xor\ 1]$。

但是转移顺序我们不知道，直接顺序递推，记忆化搜索即可。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 7005
using namespace std;
int n,p,a[N],q,b[N],f[N][2];
inline int ck(int x){if(x<1)x+=n;return x;}
bool v[N][2];int c[N][2];
void dfs(int x,int op){
	if(v[x][op])return;
	v[x][op]=1;
	//cout<<x<<" "<<op<<" "<<f[x][op]<<endl;
	if(op==0){
		rep(i,1,q){
			int cur=ck(x-b[i]);
			//cout<<"ss "<<x<<" "<<cur<<endl;
			if(v[cur][op^1]||cur==1)continue; 
			if(f[x][op]==-1)f[cur][op^1]=1,dfs(cur,op^1);
			else if(f[x][op]==1){
				c[cur][op^1]++;
				if(c[cur][op^1]==q)f[cur][op^1]=-1,dfs(cur,op^1);
			}
		}
	}
	else {
		rep(i,1,p){
			int cur=ck(x-a[i]);
			//cout<<"tt "<<x<<" "<<cur<<endl;
			if(v[cur][op^1])continue;
			if(f[x][op]==-1)f[cur][op^1]=1,dfs(cur,op^1);
			else if(f[x][op]==1){
				c[cur][op^1]++;
				if(c[cur][op^1]==p)f[cur][op^1]=-1,dfs(cur,op^1);
			}
		}
	}
}
int main(){
	scanf("%d",&n);
	scanf("%d",&p);rep(i,1,p)scanf("%d",&a[i]);
	scanf("%d",&q);rep(i,1,q)scanf("%d",&b[i]);
	f[1][0]=f[1][1]=-1;dfs(1,0);dfs(1,1);
	rep(i,2,n){
		int cur=f[i][0];
		if(cur==1)printf("Win ");
		else if(cur==0)printf("Loop ");
		else printf("Lose ");
	}
	putchar('\n');
	rep(i,2,n){
		int cur=f[i][1];
		if(cur==1)printf("Win ");
		else if(cur==0)printf("Loop ");
		else printf("Lose ");
	}
	return 0;
}
```

---

