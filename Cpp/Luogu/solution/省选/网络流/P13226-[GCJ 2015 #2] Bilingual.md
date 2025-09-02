# [GCJ 2015 #2] Bilingual

## 题目描述

Elliot 的父母在家里用法语和英语与他交流。他听过很多单词，但并不总是清楚每个单词来自哪种语言！Elliot 确定有一句话是英语句子，有一句话是法语句子，还有一些其他句子可能是英语也可能是法语。如果一个单词出现在英语句子中，那么它一定是英语单词。如果一个单词出现在法语句子中，那么它一定是法语单词。

考虑 Elliot 听过的所有句子，问他听到的单词中，最少有多少个单词必须同时属于英语和法语单词？

## 说明/提示

**样例解释**

在第 1 个测试用例中，Elliot 确定第一句是英语，第二句是法语，因此没有歧义；唯一必须同时属于英语和法语的单词是 “baguettes”。

在第 2 个测试用例中，最后两句可以分别是：英语 英语、英语 法语、法语 英语、法语 法语。第二种分配方式可以最小化同时属于英语和法语的单词数量；最终这个集合是 d、e、i 和 j。

**数据范围**

- $1 \leq T \leq 25$。
- 每个单词不超过 10 个字符。
- 两个“已知”句子各包含不超过 1000 个单词。
- “未知”句子各包含不超过 10 个单词。

**小数据范围**

- 时间限制：5 秒。
- $2 \leq N \leq 20$。

**大数据范围**

- 时间限制：10 秒。
- $2 \leq N \leq 200$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4
2
he loves to eat baguettes
il aime manger des baguettes
4
a b c d e
f g h i j
a b c i j
f g h d e
4
he drove into a cul de sac
elle a conduit sa voiture
il a conduit dans un cul de sac
il mange pendant que il conduit sa voiture
6
adieu joie de vivre je ne regrette rien
adieu joie de vivre je ne regrette rien
a b c d e
f g h i j
a b c i j
f g h d e```

### 输出

```
Case #1: 1
Case #2: 4
Case #3: 3
Case #4: 8```

# 题解

## 作者：alexbear103 (赞：0)

形式化一下就是对于未确定的句子，将其中所有词加入英语集合或法语集合，让这两个集合交最小。由此可以想到最小割：把 $S\cap T$ 里的点割掉。

将与 $S$ 联通的点视为英语单词，与 $T$ 联通的点视为法语单词。那如何刻画将句子整体划入某集合呢？可以建两个虚点 $cs$ 和 $ct$，连接 $S\rightarrow cs \rightarrow $ 当前句子中所有单词 $\rightarrow ct \rightarrow T$，并连接 $cs\rightarrow ct\space (cap=+\infty)$ 来强制割掉一条边。

code:

```cpp
#include <bits/stdc++.h>
#define int long long
#define endl '\n'
#define pii pair<int, int>
#define rep(x, y, z) for (int x = (y); x <= (z); ++x)
#define per(x, z, y) for (int x = (z); x >= (y); --x)
using namespace std;
constexpr int maxn = 5005, inf = 1e12;
#define stoi go_back_to_venus_fort
map<string, int> stoi; int n, ti = 2;
bool mark[maxn];
int ind(string s) {
    if (!stoi.count(s)) {ti += 2; stoi[s] = ti - 1;}
    return stoi[s];
}
int stop(string s, int d) {return ind(s) + d;}
struct node {int v, rm, rev;}; vector<node> g[maxn];
int S = 1, T = 2;
void add(int u, int v, int cap) {
    int s1 = g[u].size(), s2 = g[v].size();
    g[u].push_back({v, cap, s2}), g[v].push_back({u, 0, s1});
}
namespace DINIC {
    int dis[maxn]; bool vis[maxn];
    bool bfs() {
        memset(dis, 0x3f, sizeof dis);
        memset(vis, 0, sizeof vis);
        queue<int> q; q.push(S); dis[S] = 0, vis[S] = true;
        while (q.size()) {
            int p = q.front(); q.pop();
            for (auto &[v, rm, rev] : g[p]) {
                if (!rm || vis[v]) continue;
                dis[v] = dis[p] + 1;
                vis[v] = true;
                q.push(v);
            }
        }
        return dis[T] <= inf;
    }
    int cur[maxn];
    inline int dfs(int p, int flow) {
        if (p == T || !flow) return flow;
        int res = 0;
        for (int &i = cur[p]; i < (int)g[p].size(); ++i) {
            auto &[v, rm, rev] = g[p][i];
            if (!rm || dis[v] != dis[p] + 1) continue;
            int d = dfs(v, min(rm, flow - res));
            if (d) {
                rm -= d, g[v][rev].rm += d, res += d;
                if (res == flow) return res;
            }
        }
        return res;
    }
    int dinic() {
        int res = 0;
        while (bfs()) {
            memset(cur, 0, sizeof cur);
            res += dfs(S, inf);
        }
        return res;
    }
}
using DINIC::dinic;
void rd(stringstream &ss) {
    cout.flush(), cerr.flush(), ss.clear();
    string inp = "";
    while (!inp.size()) getline(cin, inp);
    ss << inp;
}
signed main() {
    int _T; cin >> _T;
    rep(_, 1, _T) {
        rep(i, 1, ti) vector<node>().swap(g[i]), mark[i] = false;
        map<string, int>().swap(stoi); ti = 2;
        cin >> n;
        string s; stringstream ss; 
        rd(ss);
        while (ss >> s) {
            add(S, stop(s, 0), inf);
            if (!mark[stop(s, 0)]) {
                add(stop(s, 0), stop(s, 1), 1);
                mark[stop(s, 0)] = true;
            }
        }
        rd(ss);
        while (ss >> s) {
            add(stop(s, 1), T, inf);
            if (!mark[stop(s, 0)]) {
                add(stop(s, 0), stop(s, 1), 1);
                mark[stop(s, 0)] = true;
            }
        }
        rep(i, 1, n - 2) {
            rd(ss);
            int cs = ++ti; int ct = ++ti;
            add(S, cs, 10), add(ct, T, 10);
            add(cs, ct, inf);
            while (ss >> s) {
                add(cs, stop(s, 0), inf);
                if (!mark[stop(s, 0)]) {
                    add(stop(s, 0), stop(s, 1), 1);
                    mark[stop(s, 0)] = true;
                }
                add(stop(s, 1), ct, inf);
            }
        }
        printf("Case #%lld: %lld\n", _, dinic() - (n - 2) * 10);
    }
    return 0;
}
```

---

