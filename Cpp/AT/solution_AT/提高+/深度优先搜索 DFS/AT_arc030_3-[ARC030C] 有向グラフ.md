# [ARC030C] 有向グラフ

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc030/tasks/arc030_3

$ n $ 個の頂点と $ m $ 本の辺から成る有向グラフがあります．$ n $ 個の頂点は， $ 1 $ から $ n $ の相異なる整数で番号付けされています． 各頂点には，`a` から `z` のアルファベットが $ 1 $ つ書かれています．

あなたはこのグラフを好きな頂点から開始し，各頂点を任意の順番で訪問することで，ちょうど $ k $ 個のアルファベットを回収したいです． 頂点は何度も訪問することができ，その頂点にアルファベットが存在する場合は任意の訪問タイミングで回収することが出来ますが，アルファベットは一度回収すると無くなります．必要がなければ，回収しなくても良いです．

あなたは，ただ回収するだけでは退屈であると思ったので，それらの $ k $ 個のアルファベットを回収した順番に並べたときに辞書順最小になるように回収することにしました．

そのような回収方法を行ったときの，$ k $ 個のアルファベットを，回収した順番に出力しなさい． $ k $ 個のアルファベットを回収する方法が存在しない場合は，`-1` を出力しなさい．

## 说明/提示

### Sample Explanation 1

この入出力例を説明する図は以下の通りとなります．頂点 $ 4 $ → $ 3 $ → $ 1 $ → $ 2 $ と移動する過程で，頂点 $ 4 $ の `a`，頂点 $ 1 $ の `a`，そして頂点 $ 2 $ の `b` を順番に回収することで辞書順最小の答えとなります． !\[\](/img/arc/030/Csample1.png)

### Sample Explanation 4

$ 3 $ つの頂点は孤立しており，どの頂点から開始しても，ちょうど $ 2 $ 個のアルファベットを回収することはできません．

## 样例 #1

### 输入

```
4 4 3
a b b a
1 2
2 3
3 1
4 3```

### 输出

```
aab```

## 样例 #2

### 输入

```
5 4 4
d a b c a
1 2
2 3
3 4
2 5```

### 输出

```
dabc```

## 样例 #3

### 输入

```
5 4 3
d a b c a
1 2
2 3
3 4
2 5```

### 输出

```
abc```

## 样例 #4

### 输入

```
3 0 2
a b c```

### 输出

```
-1```

# 题解

## 作者：Conan15 (赞：1)

题目看错被硬控 $5$ 分钟，注意每次到一个点可以不选择这个点上的字母。\
洛谷上怎么没有题解？~~太邪恶了。~~

首先显然，在同一个 SCC 内的点可以以任意顺序选择，且一定是**从小到大**选择，因此先对这张有向图跑 tarjan 求出**缩点**后的图，后文将其称为“新图”。\
容易求出 $s_i$ 表示新图中 $i$ 号点包含的字母集合。由于从小到大选择，直接存储字母集合排序后的字符串即可。\
设 $t_{i,j}$ 表示新图中 $i$ 号点选了前 $j$ 个字母的字符串，这也是好处理的。

观察到新图是一张 DAG，容易想到**拓扑排序 DP**。\
设 $dp_{i,j}$ 表示新图到 $i$ 号点，选了 $j$ 个字符的字典序最小的字符串。\
在新图 DAG 上跑拓扑排序，然后每次枚举下一个点选择几个字符放入答案即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 315, M = 2015;
int n, m, k;
char a[N];
int h[N], e[M], ne[M], idx = 0;
void add(int a, int b) { e[idx] = b, ne[idx] = h[a], h[a] = idx++; }

int dfn[N], low[N], tot = 0;
int stk[N], top = 0;
bool in_stk[N];

int scc[N], cnt = 0;
void tarjan(int u) {
    dfn[u] = low[u] = ++tot;
    stk[++top] = u, in_stk[u] = 1;
    for (int i = h[u]; ~i; i = ne[i]) {
        int v = e[i];
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (in_stk[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if (dfn[u] == low[u]) {
        ++cnt;
        while (stk[top] != u) {
            int t = stk[top]; top--;
            scc[t] = cnt, in_stk[t] = 0;
        }
        int t = stk[top]; top--;
        scc[t] = cnt, in_stk[t] = 0;
    }
}

bool used[N][N];
vector<int> edge[N];
int in[N], sz[N];

string s[N], t[N][N];    // SCC 内有的字符集、SCC[i] 中前 j 小的字符集
string dp[N][N];    //到达 SCC[i]，有 j 个字符
bool vis[N];

queue<int> q;
void topsort() {
    for (int i = 1; i <= cnt; i++)
        if (!in[i]) q.push(i);
    while (q.size()) {
        int u = q.front(); q.pop();
        for (int v : edge[u]) {
            for (int i = 0; i <= k; i++) {
                if (dp[u][i].size() == 0) continue;
                if (dp[v][i].size() == 0) dp[v][i] = dp[u][i];  // 注意可以在一个 scc 内不选
                else dp[v][i] = min(dp[v][i], dp[u][i]);
                for (int j = 1; i + j <= k && j <= sz[v]; j++) {  //考虑在 scc[v] 加入 j 个字符
                    if (dp[v][i + j].size() == 0) dp[v][i + j] = dp[u][i] + t[v][j];
                    else dp[v][i + j] = min(dp[v][i + j], dp[u][i] + t[v][j]);
                }
            }
            if (!(--in[v])) q.push(v);
        }
    }
}

string ans;

int main() {
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= k + 5; i++) ans += 'z';    //ans = Max
    for (int i = 1; i <= n; i++) scanf(" %c", &a[i]), h[i] = -1;
    for (int i = 1, u, v; i <= m; i++) {
        scanf(" %d%d", &u, &v);
        add(u, v);
    }
    for (int i = 1; i <= n; i++)
        if (!dfn[i]) tarjan(i);

    for (int u = 1; u <= n; u++) {
        for (int i = h[u]; ~i; i = ne[i]) {
            int v = e[i];
            if (scc[v] == scc[u]) continue;
            if (used[scc[u]][scc[v]]) continue;
            used[scc[u]][scc[v]] = 1;
            edge[scc[u]].push_back(scc[v]), in[scc[v]]++;
        }
    }
    for (int i = 1; i <= n; i++) s[scc[i]] += a[i], sz[scc[i]]++;
    for (int i = 1; i <= cnt; i++) sort(s[i].begin(), s[i].end());
    for (int i = 1; i <= cnt; i++)
        for (int j = 1; j <= sz[i]; j++) dp[i][j] = t[i][j] = t[i][j - 1] + s[i][j - 1];    //初始化，即从本身 scc 出发
    topsort();
    for (int i = 1; i <= cnt; i++)
        if (dp[i][k].size() == k) ans = min(ans, dp[i][k]);
    if (ans.size() != k) puts("-1");
    else cout << ans << endl;
    return 0;
}
```

---

