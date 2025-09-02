# Funny Game

## 题目描述

Vanya has a graph with $ n $ vertices (numbered from $ 1 $ to $ n $ ) and an array $ a $ of $ n $ integers; initially, there are no edges in the graph. Vanya got bored, and to have fun, he decided to perform $ n - 1 $ operations.

Operation number $ x $ (operations are numbered in order starting from $ 1 $ ) is as follows:

- Choose $ 2 $ different numbers $ 1 \leq u,v \leq n $ , such that $ |a_u - a_v| $ is divisible by $ x $ .
- Add an undirected edge between vertices $ u $ and $ v $ to the graph.

Help Vanya get a connected $ ^{\text{∗}} $ graph using the $ n - 1 $ operations, or determine that it is impossible.

 $ ^{\text{∗}} $ A graph is called connected if it is possible to reach any vertex from any other by moving along the edges.

## 说明/提示

Let's consider the second test case.

- First operation $ (x = 1) $ : we can connect vertices $ 4 $ and $ 1 $ , since $ |a_4 - a_1| = |13 - 99| = |-86| = 86 $ , and $ 86 $ is divisible by $ 1 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1994D/f454bbc6f9e0e97455a35659663326d5f1b7732f.png)- Second operation $ (x = 2) $ : we can connect vertices $ 2 $ and $ 1 $ , since $ |a_2 - a_1| = |7 - 99| = |-92| = 92 $ , and $ 92 $ is divisible by $ 2 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1994D/9f40b6b2ea3eceff5de09b1a367a88713eeb53f7.png)- Third operation $ (x = 3) $ : we can connect vertices $ 3 $ and $ 2 $ , since $ |a_3 - a_2| = |1 - 7| = |-6| = 6 $ , and $ 6 $ is divisible by $ 3 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1994D/f0db9ab0c3e7fd24f5ff083e0932405157cd111f.png) From the picture, it can be seen that a connected graph is obtained.

## 样例 #1

### 输入

```
8
2
1 4
4
99 7 1 13
5
10 2 31 44 73
5
87 6 81 44 32
5
62 35 33 79 16
5
6 51 31 69 42
5
52 63 25 21 5
12
33 40 3 11 31 43 37 8 50 5 12 22```

### 输出

```
YES
2 1
YES
4 1
2 1
3 2
YES
5 1
4 1
3 1
2 1
YES
4 1
3 1
2 1
5 4
YES
3 1
5 1
2 1
4 2
YES
4 1
5 1
2 1
3 2
YES
2 1
5 2
3 1
4 3
YES
9 1
12 9
11 1
10 1
6 1
7 6
2 1
8 2
5 2
3 1
4 1```

# 题解

## 作者：BrotherCall (赞：15)

赛时思考路径是这样的：

一个数 $x$ 能整除 $y$，那 $x$ 的任意因子 $d$ 一定能整除 $y$。又由于这个图最终的形态和操作次序无关。

所以我们把题意中连边的顺序从大到小考虑，即从第 $n - 1$ 次操作考虑到第 $1$ 次操作（因为操作序号越小就更容易满足情况）。

通过手玩样例发现 $n$ 个点，貌似一定能找到一对 $(a_i , a_j)$ 满足 $\lvert a_i - a_j\rvert \equiv 0\pmod{(n-1)}$。

然后根据：若 $a \equiv b\pmod p$ 则 $\lvert a - b \rvert \equiv 0\pmod p$。再利用并查集就可 $O(n)$ 找出两个不在同一连通块的点满足 $\lvert a_i - a_j\rvert \equiv 0\pmod{(n-1)}$。

盲猜从大到小枚举操作次序 $x$ ，从第 $n - 1$ 次操作到第 $1$ 次操作都满足存在两个在不同集合中的点满足 $a_i \equiv a_j \pmod x$。

然后这么写就过了，时间复杂度 $O(n^2)$。

---

赛后想着怎么证明这个东西，看到有群里说鸽巢原理一下就豁然开朗了。

鸽巢原理又名抽屉原理，内容是 $n$ 个抽屉塞 $n + 1$ 本书的话，必然存在至少一个抽屉被塞了两本书。

放在这题里，什么边都不连的话是 $n$ 个连通块，每次连一条边相当于合并两个连通块，也就是使连通块个数减一。

也就是说按次序 $x$ 从大到小连边，第 $x$ 次操作的时候有 $x + 1$ 个连通块，每个连通块即使选一个数出来也一定存在两个数同余 $x$。

然后也证完了。

[提交记录。](https://codeforces.com/contest/1994/submission/271250042)

[视频讲解。](https://www.bilibili.com/video/BV1z2421Z7Tu)

---

## 作者：一只绝帆 (赞：5)

> 给定一个大小为 $n$ 的数组，需要进行 $n-1$ 次操作，第 $i$ 次操作需要选择 $u,v$ 满足 $i\mid|a_u-a_v|$，然后在 $u,v$ 之间连一条边。
> 
> 问能否通过恰当的选择使得 $n$ 个点最终联通，如果能需要构造方案。
> 
> $n\le 2000$。

想了好久，被鸽巢原理爆了。

观察样例发现根本没有 `No`，然后就考虑既然全都有解，从大往小每次找到一条合法边连上然后随便删一个点就可以了。

有了这个思路，你发现就豁然开朗了，合法边由于鸽巢原理一定存在，因为 $n$ 个点在 $\bmod\ n-1$ 的同余系里面必定有重复点。

---

## 作者：oliver326 (赞：3)

# CF1994D Funny Game 题解

## 题目大意

给定 $ n $ 个节点，第 $ i $ 个节点有一个权值 $ a_i $，进行 $ n - 1$ 次操作，对于第 $ x $ 个操作，两个节点 $u, v$ 间可以连边当且仅当 $ | a_u - a_v | $ 可以被 $ x $ 整除，求一种连边方案，使得所有操作结束后图连通。

## 分析

观察这个连边的条件：

$$x\mid(a_u-a_v)$$ 

等价于：

$$a_u \equiv a_v \pmod x$$

也就是说两点能在第 $i$ 次操作连边当且仅当两者的权值在模 $i$ 下的余数相等。

考场上的我发现编号为 $1$ 的边可以连接任意两个点，于是感性地想到编号较小的边似乎更容易被连接。于是我们来考虑最大的边，也就是编号 $n-1$ 应该连接哪两个点，我们将所有点根据模 $n-1$ 的余数分类，分到同一类的任意两个点都可以连接。注意：我们把 $n$ 个点放入了 $n-1$ 个集合，那么必然会有两个点在同一个集合，也就是说必然有可行的方案将两点连接。

我们随意选择符合要求的点连起来，此时这两个点已经连通，因此只要其中有一个点和外部点连通即可使图连通。因此只考虑两个点中的一个，另一个打上标记表示不需要和外部点再连接（不然就有环啦）。其实就相当于删掉了一个点。发现单次操作会让剩余的边数和点数都减少一，递归到了一个更简单的子问题。

所以从编号 $n-1$ 到 $1$  依次建边就行，上面的分析已经可以看出方案一定存在。

稍微注意下题目的输出顺序。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int t;

const int maxn = 2010;
int n, a[maxn];
int book[maxn], vis[maxn];
vector<pair<int, int>> ans;

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios::sync_with_stdio(false);
    cin >> t;
    while (t--) {
        cin >> n;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
        }
        cout << "YES\n";
        ans.clear();
        memset(vis, 0, sizeof(vis));
        for (int i = n - 1; i >= 1; i--) {
            memset(book, 0, sizeof(book));
            for (int j = 1; j <= n; j++) {
                if (!vis[j]) {
                    if (book[a[j] % i] == 0) {
                        book[a[j] % i] = j;
                    } else {
                        ans.push_back({book[a[j] % i], j});
                        vis[j] = 1;
                        break;
                    }
                }
            }
        }
        for (int i = ans.size() - 1; i >= 0; i--) {
            cout << ans[i].first << " " << ans[i].second << '\n';
        }
    }
}
```

---

## 作者：qian0715 (赞：2)

提示：[个人博客站观看更佳](https://moneygpt.site/archives/funny_game)

题目传送门：
[洛谷](https://www.luogu.com.cn/problem/CF1994D)
/ [codeforces](https://codeforces.com/problemset/problem/1994/D)
### 题意简述

翻译已经给的很明确了，实际上就是给定 $n$ 个点，然后 $x$ 个操作：

- 选择 2 个不同的数 $1≤u,v≤n$ ，使得 $|a_u−a_v|$ 能被 $x$ 整除。
- 在顶点 $u$ 和 $v$ 之间添加一条无向边。

最后问是否可以连通。

### 题目分析

这道题目要求我们构建一个连通图，条件是每一步操作可以在两个节点之间连一条边，当且仅当这两个节点的权值差能够被当前操作的编号整除。问题的核心是确保图在所有操作完成后是连通的，并且输出各个连线。

所以整个题目主要就是用**并查集**，以及**鸽巢原理**的理解和应用。

什么是并查集？[点我通过例题简单了解。](https://blog.moneygpt.site/archives/dfe0a50a-e1e4-4e7a-8a8e-f58fc695eddf)或自行查找资料。

### 解题思路

1. **并查集的使用**：由于我们需要确保最终图是连通的，所以可以使用并查集来检查图是否连通。

2. **操作方式**：从最后一步操作开始（即 $x = n-1$ ），我们尝试连接每一对节点。如果两个节点已经连通，或者其差值不能被当前的操作编号整除，则跳过；否则，连接这两个节点并进行并查集的合并操作。

3. **连通性检查**：最后，我们检查并查集是否所有节点已经连通（父节点是否一致）。如果存在未连通的节点，则无法通过该操作使图连通。

4. 最后判断+输出。

### 代码实现

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 2005;

int t, n, a[N], f[N];
// 用于存储连线的两点的结构体
struct Edge {
    int u, v;
} b[N];

// 查找并查集的根节点
int find(int x) {
    if (x == f[x]) {
        return x;
    }
    return f[x] = find(f[x]);
}

// 合并两个节点
void unionn(int x, int y) {
    x = find(x);
    y = find(y);
    if (x != y) {
        f[x] = y;
    }
}

int main() {
    cin >> t;
    while (t--) {
        int cnt = 0;  // 用于记录当前循环边的数量
        cin >> n;
        for (int i = 1; i <= n; i++) {
            f[i] = i;  // 初始化并查集
        }
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
        }
        for (int i = n - 1; i >= 1; i--) {
            vector<int> p(i, -1);  // 用于记录每个余数对应的节点
            for (int j = 1; j <= n; j++) {
                if (find(j) == j) {
                    int num = a[j] % i;  // 计算当前节点的权值对 i 的余数
                    if (p[num] == -1) {
                        p[num] = j;  // 如果该数没有出现过，记录当前节点
                    } else {
                        // 如果该数已经出现过，连接两个节点并合并
                        b[++cnt].u = p[num];
                        b[cnt].v = j;
                        unionn(p[num], j); // 并查集合并
                        break;
                    }
                }
            }
        }
        
        // 检查是否所有节点都连通
        bool flag = true;
        for (int i = 1; i <= n; i++) {
            if (find(i) != find(1)) {
                flag = false;
                break;
            }
        }
        
        // 输出结果
        if (!flag) {
            cout << "No" << endl;
        } else {
            cout << "Yes" << endl;
            for (int i = cnt; i >= 1; i--) { // 由于前面是逆向循环x个操作的，所以这里需要逆向输出
                cout << b[i].u << " " << b[i].v << endl;
            }
        }
    }
    return 0;
}
```

### 代码解释

- `find(int x)`：查找节点 `x` 所属的连通块（即并查集的根节点）。
- `unionn(int x, int y)`：将两个节点合并到同一个连通块中。
- 在主循环中，从 $x = n-1$ 开始，每次检查权值的模 $i$ 是否已经被记录，并合并具有相同模数的节点。
- 最终检查图的连通性，如果不连通则输出 "No"，否则输出 "Yes" 和相应的边。

### 时间复杂度和空间复杂度分析

- **时间复杂度**：总体时间复杂度为 $O(t \times n^2)$，其中 $t$ 为测试用例的数量，$n$ 为节点数量。
- **空间复杂度**：主要由数组 `a` 和 `f` 决定，空间复杂度为 $O(n)$。

---

喜欢的话不要忘记点赞哈！

---

## 作者：huangrenheluogu (赞：2)

被自己秀到了。

VP 的时候看到这个题，**猜**了一个结论：如果有解，那么一定存在一个大的点向小的点连边。

因为是 CF 比赛，所以手玩了几组在赛时就不证明了（证明在文末）。

考虑把题目看成大的点向小的点连某一条数字的边，提前预处理出大的点可以连出哪些数字的边使得有编号小的点接收，$\mathcal{O}(n^3)$ 是好做的。发现我们只需要看 $i$ 能否和数字 $x$ 连边，所以提前处理出 $tmp_{x,y}$ 表示模 $x$ 等于 $y$ 的编号，如果没有就是 $0$。这样就是 $\mathcal{O}(n^2)$ 了。

然后跑一个二分图匹配，用 dinic 即可，然后就知道匹配边了，由于边数不超过 $\mathcal{O}(n^2)$，所以整个算法的复杂度是 $\mathcal{O}(n^{2.5})$ 的，比官解的 $\mathcal{O}(n^2\alpha(n))$ 慢了不少，但是可以过。

匹配完之后就知道每一个点和哪些颜色连边，就知道每一个点和哪一些点连边，这样再跑一遍前面计算 $tmp_{x,y}$ 的算法即可。

VP 的时候 dinic 写挂了，还是要多写板子。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2005, inf = 0x3f3f3f3f;
int T, n, a[N], tmp[N][N], to[N];
int fir[N << 1], nxt[N * N << 2], son[N * N << 2], edge[N * N << 2];
int Ss, Tt, maxflow, now[N << 1], d[N << 1];
int q[N << 1], h, t, tot;
int U[N], V[N];
inline void clr(){
	for(int i = 1; i <= n; i++){
		for(int j = 0; j < i; j++){
			tmp[i][j] = 0;
		}
	}
}
inline void add(int x, int y, int flow){
	nxt[++tot] = fir[x];
	fir[x] = tot;
	son[tot] = y;
	edge[tot] = flow;
}
inline void Add(int x, int y){
	add(x, y, 1);
	add(y, x, 0);
}
inline void init(){
	for(int i = Ss; i <= Tt; i++) fir[i] = 0;
	tot = 1;
}
inline bool bfs(){
	for(int i = Ss; i <= Tt; i++) d[i] = 0;
	for(int i = Ss; i <= Tt; i++) now[i] = fir[i];
	h = 0;
	q[t = 1] = Ss;
	d[Ss] = 1;
	while(h < t){
		h++;
		for(int i = now[q[h]]; i ; i = nxt[i]){
			if(edge[i] && !d[son[i]]){
				d[son[i]] = d[q[h]] + 1;
				q[++t] = son[i];
				if(son[i] == Tt) return 1;
			}
		}
	}
	return 0;
}
inline int dinic(int x, int flow){
	if(x == Tt) return flow;
	int res = flow, tt;
	for(int i = now[x]; i && res; i = nxt[i]){
		now[x] = i;
		if(edge[i] && d[son[i]] == d[x] + 1){
			tt = dinic(son[i], min(res, edge[i]));
			if(!tt) continue ;
			edge[i] -= tt;
			edge[i ^ 1] += tt;
			res -= tt;
		}
	}
	return flow - res;
}
int main(){
//	freopen("data.in", "r", stdin);
	scanf("%d", &T);
	while(T--){
		init();
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		for(int i = 1; i < n; i++){
			tmp[i][a[1] % i] = 1;
		}
		Tt = 2 * n;
		for(int i = 2; i <= n; i++){
			for(int j = 1; j < n; j++){
				if(tmp[j][a[i] % j]){
					Add(i, j + n);
//					printf("%d %d\n", i, j + n);
				}
			}
			for(int j = 1; j < n; j++){
				tmp[j][a[i] % j] = i;
			}
		}
		for(int i = 1; i <= n; i++){
			Add(Ss, i);
		}
		for(int i = 1; i < n; i++){
			Add(i + n, Tt);
		}
		maxflow = 0;
		while(bfs()){
			maxflow += dinic(Ss, inf);
//			cerr << maxflow << endl;
		}
		if(maxflow ^ n - 1){
			puts("NO");
			continue ;
		}
		for(int x = 2; x <= n; x++){
			for(int i = fir[x]; i ; i = nxt[i]){
				if(!edge[i] && son[i] > n) to[x] = son[i] - n;
			}
		}
		clr();
		for(int i = 1; i < n; i++) tmp[i][a[1] % i] = 1;
		for(int i = 2; i <= n; i++){
			U[to[i]] = tmp[to[i]][a[i] % to[i]];
			V[to[i]] = i;
			for(int j = 1; j < n; j++){
				tmp[j][a[i] % j] = i;
			}
		}
		puts("YES");
		for(int i = 1; i < n; i++){
			printf("%d %d\n", U[i], V[i]);
		}
		clr();
	}
	return 0;
}
```

最后是关于前面结论的证明：

因为这个结论真的是猜的，所以我也没有很好的证明，有知道比较自然的证明的大佬可以私信/评论 ~~（由于这个证明是我口胡的，有不严谨的地方请大佬私信/评论指出）~~。

考虑归纳证明，下面称 $n$ 是点数，$n=1,n=2$ 显然成立。

假设 $n=k$ 成立，下证 $n=k+1$ 成立。

此时，我们加入一条权值为 $k$ 的边，此时图上有 $k+1$ 个点，根据鸽巢原理，必然有两个点的权值在模 $k$ 意义下是相同的。如果这些组点中有一个是 $k+1$，不妨 $k+1,x$ 满足 $a_{k+1}\equiv a_x\pmod k$，那么令 $fa_{k+1}=x$ 即可。

否则，我们会找到两个点 $u,v$，满足 $1\le u\lt v\le k,a_u\equiv a_v\pmod k$，可以断开 $(v,fa_v)$ 的边然后连接 $(u,v)$，之后我们有一条限制更小的边。

设当前我们可以用边权为 $w$ 的边，那么，我们在前面取得点应该是 $1$ 号点，$k+1$ 号点，和连到父亲的边权 $\lt w$ 的点，这些点总共有 $w+1$ 个，可以继续进行类似上面的过程，直到 $k+1$ 号点被插入树中。由于 $w$ 是不断减小的，而 $w=1$ 的时候显然可行，此时随便挂在一个节点后面即可，因此，是肯定可行的。

证毕。

---

## 作者：mango2011 (赞：1)

这其实是一道诈骗题。

显然，我们发现当操作轮数比较靠后的时候我们很可能找不到合适的两数进行连边操作，所以我们把整个操作过程反过来：

第 $i(1\le i<n)$ 次操作可以选择两个数 $a_x,a_y$ 满足 $n-i$ 为 $|a_x-a_y|$ 的因数，然后在 $x$ 与 $y$ 之间连一条边。

在第 $i$ 次操作之前，我们需要保证有 $n-i+1$ 个连通块，当 $i=1$ 时显然可以。对于任意的 $i(1\le i<n-1)$，假设当前恰有 $n-i+1$ 个连通块，每个连通块选出一个数，根据模 $n-i$ 的余数可以得到 $n-i$ 个“抽屉”，于是由抽屉原理可以发现至少有两个数模 $n-i$ 的余数相同，将它们进行连边即可。这样不会出现环，还可以使连通块个数减少 $1$。特殊地，当 $i=n-1$ 时，操作完就会得到一棵树，符合题意。

综上，我们就完成了构造，总是存在解，解的构造方法就是上面的过程。

---

## 作者：MrPython (赞：0)

CF 的题还是一如既往的好玩！

题目要求我们执行 $n-1$ 次操作。对于第 $x$ 次操作（$1\le x\le n-1$），可以选择一对 $(u,v)$ 满足 $x\mid(\left|a_u-a_v\right|)$，在点 $u$ 与点 $v$ 之间建边。执行所有操作后，所得到的图应为一颗树。

方便起见，将 $x\mid(\left|a_u-a_v\right|)$ 转化为 $a_u\equiv a_v \pmod{x}$。从感觉上看，靠前的操作要靠后的操作容易得多，因此我们选择从后往前反着算。

第一次操作时，$x=n-1$。此时 $a_i\bmod x$ 最多只有 $n-1$ 种可能的结果，而一共有 $n$ 个相互独立的点。根据鸽巢原理，能找到至少一对 $(u,v)$ 之间可以建边。连边后，两个点缩成了一个连通块。图上还有 $n-1$ 个连通块。

第二次操作时，$x=n-2$。此时 $a_i\bmod x$ 最多只有 $n-1$ 种可能的结果。从刚才产生的连通块中任选一点，就相当于有 $n-1$ 个相互独立的点。根据鸽巢原理，仍可以从这些点中找到至少一对 $(u,v)$ 之间可以建边。连边后，图上还有 $n-2$ 个连通块。

……

第 $k$ 次操作时，$x=n-k$。此时 $a_i\bmod x$ 最多只有 $n-k$ 种可能的结果。从目前的 $n-k+1$ 个连通块中每个都任取一点，就相当于有 $n-k+1$ 个相互独立的点。根据鸽巢原理，仍可以从这些点中找到至少一对 $(u,v)$ 之间可以建边。连边后，图上还有 $n-k$ 个连通块。

由此，我们用数学归纳法证明了一定可以构造出这样的树来，因此先输出 `YES`。

具体的实现上，我使用了并查集。初始时所有节点均自成集合。在倒序枚举操作时，将“从每个连通块中任取一点”实现为取该集合在并查集中的根节点即可。拿一个 map 搞一下，如果为并查集树的根节点就以余数为键点编号为值扔到 set 里，同时判重。

```cpp
#include <bits/extc++.h>
using namespace std;
namespace pbds = __gnu_pbds;
using ui = unsigned int;
using uli = unsigned long long int;
using li = long long int;
struct DSU {
    vector<size_t> fa;
    DSU(size_t n) : fa(n) { iota(fa.begin(), fa.end(), size_t(0)); }
    size_t find(size_t x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
    bool check(size_t x, size_t y) { return find(x) == find(y); }
    void merge(size_t x, size_t y) { fa[find(x)] = find(y); }
};
int main(void) {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    size_t T;
    cin >> T;
    while (T--) {
        size_t n;
        cin >> n;
        vector<ui> a(n);
        for (ui &i : a)
            cin >> i;
        DSU ds(n);
        cout << "YES\n";
        vector<pair<size_t, size_t>> ans;
        for (ui x = n - 1; x >= 1; --x) {
            map<ui, size_t> d;
            for (size_t i = 0; i < n; ++i)
                if (ds.find(i) == i)
                    if (d.count(a[i] % x)) {
                        ans.emplace_back(d[a[i] % x], i);
                        ds.merge(d[a[i] % x], i);
                        goto next;
                    } else
                        d[a[i] % x] = i;
            throw;
        next:;
        }
        for_each(ans.rbegin(), ans.rend(), [](auto const &x) { cout << x.first + 1 << ' ' << x.second + 1 << '\n'; });
    }
    return 0;
}
```

---

## 作者：Exp10re (赞：0)

场上硬控一年。但是命题确实天才。

## 解题思路

不难证明，不论连边顺序如何，这个图一定是一个森林。

也就是说，如果已经连接了 $m$ 条边，那么图上一定会有恰好 $n-m+1$ 个连通块。

考虑第 $i$ 个操作使得点 $u$ 与 $v$ 之间连边的必要条件：题面所述的 $|a_u-a_v|$ 可以被 $i$ 整除，实际上这个条件与 $a_u \equiv a_v \pmod i$ 是等价的。

由于 $i$ 越大，直观感知到可连的边数越小，因此考虑倒序枚举所有操作，即枚举顺序为 $n-1$ 到 $1$。

在第 $i$ 次操作中，图上存在 $i+1$ 个连通块，而 $\bmod i$ 的不同余数个数只有 $i$ 种。根据鸽笼原理可以得出至少存在两个连通块 $C_1,C_2$，满足 $\exist u\in C_1,v\in C_2$，使得 $a_u \equiv a_v \pmod i$。

因此倒序枚举每一次操作必定能连接两个不同连通块得证，故必定有解。

证明后做法是简单的枚举余数，时间复杂度 $O(n^2)$。

---

## 作者：Bad_Luck_No_Fun (赞：0)

### 题目描述

每个点上有权值 $a_i$。对于第 $i$ 次操作，寻找 $|a_i-a_j|$ 为 $i$ 的倍数的 $i,j$，在两个点之间连边，判断做这个操作 $n-1$ 次能否连成一棵生成树。

### 思路

~~诈骗题。~~

答案总是 yes。倒过来模拟这 $n-1$ 次操作即可，赛场上完全没想到。

条件的束缚从 $1$ 到 $n$ 逐渐苛刻，所以很自然的倒过来操作。因为要做出一只生成树，在做倒过来后的第 $i$ 次操作之前一定有 $i+1$ 个连通块。根据抽屉原理，这 $i+1$ 个联通块中一定存在 $i,j$ 使得 $a_i-a_j$ 为 $i$ 的倍数！

所以证明出了答案必然为 yes，记录操作构造即可。

### $Code$

```cpp
# include<bits/stdc++.h>
using namespace std;
# define int long long
const int N = 2005;
int T, n;
int a[N];
int fa[N];
int b[N];
int getfa(int u)
{
	if(fa[u] == u)
	{
		return u;
	}
	fa[u] = getfa(fa[u]);
	return fa[u];
}

void init()
{
	for(int i = 1; i <= n; i++)
	{
		fa[i] = i;
	}
}

void clear()
{
	for(int i = 0; i <= n; i++)
	{
		b[i] = 0;
	}
}

void merge(int u, int v)
{
	fa[getfa(u)] = getfa(v);
}

struct Edge
{
	int u, v;
};

Edge e[N];

void solve()
{
	cin >> n;
	for(int i = 1; i <= n; i++)
	{
		cin >> a[i];
	}
	init();
	for(int i = n - 1; i >= 1; i--)
	{
		clear();
		for(int j = 1; j <= n; j++)
		{
			if(b[a[j] % i] && getfa(b[a[j] % i]) != getfa(j))
			{
				merge(j, b[a[j] % i]);
				e[i] = {j, b[a[j] % i]};
				break;
			}
			b[a[j] % i] = j;
		}
	}
	cout << "Yes" << endl;
	for(int i = 1; i <= n - 1; i++)
	{
		cout << e[i].u << " " << e[i].v << endl;
	}
}
signed main()
{
	cin >> T;
	while(T--)
	{
		solve();
	}
	return 0;
}


```

---

## 作者：RayAstRa_ (赞：0)

## Description

给出一个 $n$ 个点且没有边的图，每个点有一个权值 $a_i$。你可以依次执行 $n-1$ 次操作，第 $x$ 次操作中选择两个点 $i,j$ 满足 $|a_i-a_j|$ 能被 $x$ 整除，并在这两个点间连边。问在所有操作后能否使图连通并给出每次操作连接的点。

## Idea

因为只能连 $n-1$ 条边，每次连边必须选择两个不同连通块的点连接。将操作倒序考虑，第 $x$ 次操作时图中有 $x+1$ 个连通块，在每个连通块中选择一个点，则根据抽屉原理，这 $x+1$ 个点中一定有两个点满足 $a_i\equiv a_j\pmod x$。因此一定有解，只需将连接的点记录并顺序输出。

## Code

```
#include<bits/stdc++.h> 
#define reg register int
using namespace std;
template<class T>inline void read(T &k){
	char c=0;k=0;int t=1;
	while(!isdigit(c)){if(c=='-')t=-1;c=getchar();}
	while(isdigit(c))k=k*10+c-48,c=getchar();
	k*=t;
}
template<class T>inline void print(T k){
	if(k<0)putchar('-'),k=-k;
	if(k>9)print(k/10);
	putchar('0'+(k%10));
}
const int N=2005;
int n,a[N],z[N],mod[N],ans[N][2];
void solve(){
	read(n);
	for(reg i=1;i<=n;i++)
		read(a[i]),z[i]=1;
	puts("YES");
	for(reg x=n-1;x>=1;x--){
		for(reg i=1;i<=n;i++){
			if(z[i]){
				if(mod[a[i]%x]>0){
					ans[x][0]=i;
					ans[x][1]=mod[a[i]%x];
					z[i]=0;
					break;
				}
				mod[a[i]%x]=i;
			}			
		}
		for(reg i=0;i<x;i++)
			mod[i]=0;
	}
	for(reg i=1;i<n;i++)
		printf("%d %d\n",ans[i][0],ans[i][1]);
}
int T;
signed main(){
	read(T);
	while(T--)
		solve();
}
```

---

## 作者：Redshift_Shine (赞：0)

## 4. Funny Game / 绿

有一个拥有 $n$ 个节点的完全图。每个点有一个点权 $a_i$。点 $i$ 和点 $j$ 之间的边的边权为 $|a_i-a_j|$。要求找出图中的一个生成树，使得这个生成树中的第 $i$ 条边的边权整除 $i$。$i$ 从 $1$ 开始计数。

$i$ 越大期望被整除的边就越少，考虑贪心+并查集。具体来说从大到小枚举每个 $i$，计算每个 $a_j\bmod i$ 的结果，如果发现有两个 $a_j$ 余数相同但不在同一连通块内，就将这两个连通块合并。

时间复杂度 $O(n^2)$。

```c++
#include <iostream>
#include <list>
#include <cstring>
using namespace std;
const int N = 2e3 + 10;
int n, a[N], f[N], v[N], p;
bool fl;
using pii = pair<int, int>;
list<pii> ret;
inline int find(int x)
{
    return x == f[x] ? x : f[x] = find(f[x]);
}
inline void merge(int x, int y)
{
    f[find(y)] = find(x);
}
void run()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        f[i] = i;
        scanf("%d", a + i);
    }
    ret.clear();
    for (int i = n - 1; i; i--)
    {
        memset(v, 0, i << 2);
        fl = false;
        for (int j = 1; j <= n; j++)
        {
            p = a[j] % i;
            if (!v[p])
            {
                v[p] = j;
                continue;
            }
            if (find(j) == find(v[p]))
                continue;
            merge(j, v[p]);
            ret.push_front({j, v[p]});
            fl = true;
            break;
        }
        if (!fl)
            return puts("NO"), void();
    }
    puts("YES");
    for (auto &[tx, ty] : ret)
        printf("%d %d\n", tx, ty);
}
int main()
{
    int T = 1;
    scanf("%d", &T);
    while (T--)
        run();
}
```

---

## 作者：_fairytale_ (赞：0)

好题！场上卡了我一年导致 FG 没来得及写。/ll

一句话题解：

考虑倒序加边，加第 $(n-1)$ 条边的时候，图中有 $n$ 个点，由鸽巢原理，至少有一对点模 $(n-1)$ 同余，然后找出这对点，随便扔掉一个，就变成了 $(n-1)$ 个点的子问题。

```cpp
#include<bits/stdc++.h>
bool Mst;
#define pii pair<int,int>
#define fi first
#define se second
#define rep(x,qwq,qaq) for(int (x)=(qwq);(x)<=(qaq);++(x))
#define per(x,qwq,qaq) for(int (x)=(qwq);(x)>=(qaq);--(x))
using namespace std;
#define maxn 2010
#define inf 0x3f3f3f3f
int T;
int n,m,k;
int a[maxn];
int b[maxn];
pii stac[maxn];
void solve() {
	cin>>n;
	rep(i,1,n)cin>>a[i];
	int top=0;
	per(i,n-1,1) {
		rep(j,0,n)b[j]=0;
		rep(j,1,n) {
			if(a[j]==inf)continue;
			if(b[a[j]%i]){
				stac[++top]={j,b[a[j]%i]};
				a[j]=inf;
				break;
			}
			b[a[j]%i]=j;
		}
	}
	cout<<"yes\n";
	while(top){
		cout<<stac[top].fi<<" "<<stac[top].se<<'\n';
		top--;
    }
}
bool Med;
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--)solve();
	return 0;
}
```

---

## 作者：Vitamin_B (赞：0)

# 纪念
倒数 $3$ 分钟提交成功并成功上蓝：![](https://cdn.luogu.com.cn/upload/image_hosting/dlrt9tjh.png)
# 思路
先给出一句废话：$x$ 的所有真因子都比 $x$ 本身小。所以我们倒着贪心取一定不劣。

再给出一句废话：若 $(a-b)\bmod c=0$，则 $a\bmod c=b\bmod c$。所以，每一次贪心时只要开 $i$ 个桶，依次枚举 $a_1\sim a_n$，若桶里原先没有元素，则把这个元素塞进去；若桶里的元素和当前元素不在同一个集合，则直接把桶里这个元素和当前元素连边（并使用并查集合并这两个集合）。
# 代码
```cpp
# include <bits/stdc++.h>
# define I return
# define AK 0
# define IOI ;
using namespace std;
typedef long long ll;
typedef pair <int, int> pii;
int t, n, a[2005], ans1[2005], ans2[2005], f[2005], vis[2005];
int find (int x) {
	return x == f[x] ? x : f[x] = find (f[x]);
}
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> t;
	while (t --) {
		cin >> n;
		for (int i = 1; i <= n; ++ i)
			cin >> a[i], f[i] = i;
		for (int i = n - 1; i; -- i) {
			for (int j = 0; j < i; ++ j)
				vis[j] = 0;
			for (int j = 1; j <= n; ++ j)
				if (! vis[a[j] % i])
					vis[a[j] % i] = j;
				else if (find (j) != find (vis[a[j] % i])) {
					ans1[i] = j, ans2[i] = vis[a[j] % i];
					f[find (j)] = find (vis[a[j] % i]);
					goto can;
				}
			goto no;
can:
			;
		}
		cout << "Yes\n";
		for (int i = 1; i < n; ++ i)
			cout << ans1[i] << ' ' << ans2[i] << '\n';
		continue ;
no:
		cout << "No\n";
	}
	I AK IOI
}
```

---

