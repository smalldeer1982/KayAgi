# Reverse a Road II

## 题目描述

反转道路2

某个陌生的国度JAG中有N座城市，城市之间用M条单向道路连接。N座城市的编号为1~N。在这个王国里面，每一天ICPC（某国际特色产品的公司）将其产品从市S中的工厂到城市T的仓库。为了提高效率，每一次运输会使用多个卡车。一辆卡车通过单向道路网络从 s通过一些城市（直接或间接）到达T。为了减少交通拥堵以及发生交通事故的风险，没有卡车会走同样的路。

现在，ICPC想提高日常运输的效率，它想在在上面的条件的约束下派出尽可能多的卡车。JAG国，这个财政状况受ICPC影响的国家，认为改变为单向道路的方向可以使ICPC每天派出的卡车数量增加。但因为逆转太多道路会造成混乱，JAG国决定只反转一条单向道路。

如果没有路反转后使运输效率提高，JAG国可以不反转任何道路。你需要检查反转一条道路是否可以提高每天派出卡车的数量。如果是这样的话，计算ICPC公司最多能派出多少辆卡车，以及为了达到这个最大值有多少种方案。

# 题解

## 作者：zerc (赞：1)

AT1031 Reverse a Road II [Luogu](https://www.luogu.com.cn/problem/AT1031) | [AtCoder](https://atcoder.jp/contests/jag2014autumn/tasks/icpc2014autumn_f)

前置知识：[P3376 【模板】网络最大流](https://www.luogu.com.cn/problem/P3376)

因为每条边最多只能走一遍，所以建一条容量为 $1$ 的边，跑一遍最大流。

考虑将 $s$ 能扩展到的节点扔进 $\text{set}_s$，将能扩展到 $t$ 的节点扔进 $\text{set}_t$，枚举残量网络上的边 $e$，如果 $u \in \text{set}_t \land v \in \text{set}_s$，那么反转这条边就能够构成一条 $s \to t$ 的合法路径，累加 $tot$。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int maxn = 2022;
const int maxm = 20222;

struct edge { int to, nxt, flow; }  e[maxm];
int cnt=1, head[maxn], dis[maxn], cur[maxn];
bool sets[maxn], sett[maxn];
int n, m, s, t, tot, ans;

void add(int u, int v, int w) {
    e[++cnt] = {v, head[u], w}; head[u] = cnt;
    e[++cnt] = {u, head[v], 0}; head[v] = cnt;
}

bool bfs(int s, int t) {
    memset(dis, 0, sizeof dis);
    memcpy(cur, head, sizeof head);
    int x;  queue<int> q;
    q.push (s); dis[s] = 1;
    while (!q.empty()) {
        x = q.front(); q.pop();
        for (int i = head[x]; i; i = e[i].nxt) {
            if (e[i].flow && !dis[e[i].to]) {
                dis[e[i].to] = dis[x] + 1;
                q.push(e[i].to);
                if (e[i].to == t) return 1;
            }
        }
    }
    return 0;
}

int dfs(int x, int flow) {
    if (x == t) return flow;
    int rest = flow; int i;
    for (i = cur[x]; i; i = e[i].nxt) {
        if (e[i].flow && dis[e[i].to] == dis[x] + 1) {
            int k = dfs(e[i].to, min(rest, (int)e[i].flow));
            if (!k) dis[e[i].to] = -1;
            e[ i ].flow -= k;
            e[i^1].flow += k;
            if (!(rest -= k)) break;
        }
    }
    cur[x] = i;
    return flow - rest;
}

int Dinic() {
    int maxflow = 0;
    while (bfs (s, t))
        maxflow += dfs(s, INT_MAX);
    return maxflow;
}

void calc() {
    queue<int> q;
    q.push(s); sets[s] = 1;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int i = head[u]; i; i = e[i].nxt) {
            int v = e[i].to;
            if (!sets[v] && e[i].flow) {
                sets[v] = 1, q.push(v);
            }
        }
    }
    q.push(t); sett[t] = 1;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int i = head[u]; i; i = e[i].nxt) {
            int v = e[i].to;
            if (!sett[v] && !e[i].flow) {
                sett[v] = 1, q.push(v);
            }
        }
    }
    for (int i = 2; i <= cnt; i += 2) {
        int u = e[i^1].to, v = e[i].to;
        if (e[i].flow && sets[v] && sett[u]) tot++;
    }
    if (tot) ans++;
}

void clear() {
    cnt = 1; ans = tot = 0;
    memset(head, 0, sizeof head);
    memset(sets, 0, sizeof sets);
    memset(sett, 0, sizeof sett);
}

int main() {
    while(1) {
        scanf("%d %d %d %d", &n, &m, &s, &t);
        if (!n && !m && !s && !t) return 0;
        clear();
        for (int i = 1; i <= m; i++) {
            int u, v; scanf("%d %d", &u, &v);
            add(u, v, 1);
        }
        ans = Dinic(), calc();
        printf("%d %d\n", ans, tot);
    }
}
```



---

